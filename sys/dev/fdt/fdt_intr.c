/* $NetBSD: fdt_intr.c,v 1.30 2021/11/07 17:13:53 jmcneill Exp $ */

/*-
 * Copyright (c) 2015-2018 Jared McNeill <jmcneill@invisible.ca>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>
__KERNEL_RCSID(0, "$NetBSD: fdt_intr.c,v 1.30 2021/11/07 17:13:53 jmcneill Exp $");

#include <sys/param.h>
#include <sys/atomic.h>
#include <sys/bus.h>
#include <sys/kmem.h>
#include <sys/queue.h>
#include <sys/mutex.h>
#include <sys/condvar.h>

#include <libfdt.h>
#include <dev/fdt/fdtvar.h>
#include <dev/fdt/fdt_private.h>

struct fdtbus_interrupt_controller {
	device_t ic_dev;
	int ic_phandle;
	const struct fdtbus_interrupt_controller_func *ic_funcs;

	LIST_ENTRY(fdtbus_interrupt_controller) ic_next;
};

static LIST_HEAD(, fdtbus_interrupt_controller) fdtbus_interrupt_controllers =
    LIST_HEAD_INITIALIZER(fdtbus_interrupt_controllers);

struct fdtbus_interrupt_cookie {
	struct fdtbus_interrupt_controller *c_ic;
	void *c_ih;

	LIST_ENTRY(fdtbus_interrupt_cookie) c_next;
	uint32_t c_refcnt;
};

static LIST_HEAD(, fdtbus_interrupt_cookie) fdtbus_interrupt_cookies =
    LIST_HEAD_INITIALIZER(fdtbus_interrupt_cookies);
static kmutex_t fdtbus_interrupt_cookie_mutex;
static kcondvar_t fdtbus_interrupt_cookie_wait;
static bool fdtbus_interrupt_cookies_wanted;

static const u_int *	get_specifier_by_index(int, int, int *);
static const u_int *	get_specifier_from_map(int, const u_int *, int *);

void
fdtbus_intr_init(void)
{

	mutex_init(&fdtbus_interrupt_cookie_mutex, MUTEX_DEFAULT, IPL_HIGH);
	cv_init(&fdtbus_interrupt_cookie_wait, "fdtintr");
}

/*
 * Find the interrupt controller for a given node. This function will either
 * return the phandle of the interrupt controller for this node, or the phandle
 * of a node containing an interrupt-map table that can be used to find the
 * real interrupt controller.
 */
static int
fdtbus_get_interrupt_parent(int phandle)
{
	int iparent = phandle;

	do {
		/*
		 * If the node is an interrupt-controller, we are done. Note that
		 * a node cannot be an interrupt-controller for itself, so we skip
		 * the leaf node here.
		 */
		if (phandle != iparent && of_hasprop(iparent, "interrupt-controller"))
			return iparent;

		/*
		 * If the node has an explicit interrupt-parent, follow the reference.
		 */
		if (of_hasprop(iparent, "interrupt-parent"))
			return fdtbus_get_phandle(iparent, "interrupt-parent");

		/*
		 * If the node has an interrupt-map, use it. The caller is responsible
		 * for parsing the interrupt-map and finding the real interrupt parent.
		 */
		if (phandle != iparent && of_hasprop(iparent, "interrupt-map"))
			return iparent;

		/*
		 * Continue searching up the tree.
		 */
		iparent = OF_parent(iparent);
	} while (iparent > 0);

	return 0;
}

static struct fdtbus_interrupt_controller *
fdtbus_get_interrupt_controller(int phandle)
{
	struct fdtbus_interrupt_controller * ic;
	LIST_FOREACH(ic, &fdtbus_interrupt_controllers, ic_next) {
		if (ic->ic_phandle == phandle)
			return ic;
	}
	return NULL;
}

int
fdtbus_register_interrupt_controller(device_t dev, int phandle,
    const struct fdtbus_interrupt_controller_func *funcs)
{
	struct fdtbus_interrupt_controller *ic;

	ic = kmem_alloc(sizeof(*ic), KM_SLEEP);
	ic->ic_dev = dev;
	ic->ic_phandle = phandle;
	ic->ic_funcs = funcs;

	LIST_INSERT_HEAD(&fdtbus_interrupt_controllers, ic, ic_next);

	return 0;
}

static struct fdtbus_interrupt_cookie *
fdtbus_get_interrupt_cookie(void *cookie)
{
	struct fdtbus_interrupt_cookie *c;

	mutex_enter(&fdtbus_interrupt_cookie_mutex);
	LIST_FOREACH(c, &fdtbus_interrupt_cookies, c_next) {
		if (c->c_ih == cookie) {
			c->c_refcnt++;
			KASSERT(c->c_refcnt > 0);
			break;
		}
	}
	mutex_exit(&fdtbus_interrupt_cookie_mutex);
	return c;
}

static void
fdtbus_put_interrupt_cookie(struct fdtbus_interrupt_cookie *c)
{

	mutex_enter(&fdtbus_interrupt_cookie_mutex);
	KASSERT(c->c_refcnt > 0);
	c->c_refcnt--;
	if (fdtbus_interrupt_cookies_wanted) {
		fdtbus_interrupt_cookies_wanted = false;
		cv_signal(&fdtbus_interrupt_cookie_wait);
	}
	mutex_exit(&fdtbus_interrupt_cookie_mutex);
}

int
fdtbus_intr_parent(int phandle)
{
	return fdtbus_get_interrupt_parent(phandle);
}

void *
fdtbus_intr_establish(int phandle, u_int index, int ipl, int flags,
    int (*func)(void *), void *arg)
{
	return fdtbus_intr_establish_xname(phandle, index, ipl, flags,
	    func, arg, NULL);
}

void *
fdtbus_intr_establish_xname(int phandle, u_int index, int ipl, int flags,
    int (*func)(void *), void *arg, const char *xname)
{
	const u_int *specifier;
	int ihandle;

	specifier = get_specifier_by_index(phandle, index, &ihandle);
	if (specifier == NULL)
		return NULL;

	return fdtbus_intr_establish_raw(ihandle, specifier, ipl,
	    flags, func, arg, xname);
}

void *
fdtbus_intr_establish_byname(int phandle, const char *name, int ipl,
    int flags, int (*func)(void *), void *arg, const char *xname)
{
	u_int index;
	int err;

	err = fdtbus_get_index(phandle, "interrupt-names", name, &index);
	if (err != 0)
		return NULL;

	return fdtbus_intr_establish_xname(phandle, index, ipl, flags, func,
	    arg, xname);
}

void *
fdtbus_intr_establish_raw(int ihandle, const u_int *specifier, int ipl,
    int flags, int (*func)(void *), void *arg, const char *xname)
{
	struct fdtbus_interrupt_controller *ic;
	struct fdtbus_interrupt_cookie *c;
	void *ih;

	ic = fdtbus_get_interrupt_controller(ihandle);
	if (ic == NULL) {
		printf("%s: ihandle %d is not a controller\n",__func__,ihandle);
		return NULL;
	}

	c = kmem_zalloc(sizeof(*c), KM_SLEEP);
	c->c_ic = ic;
	mutex_enter(&fdtbus_interrupt_cookie_mutex);
	LIST_INSERT_HEAD(&fdtbus_interrupt_cookies, c, c_next);
	mutex_exit(&fdtbus_interrupt_cookie_mutex);

	/*
	 * XXX This leaves a small window where the handler is registered
	 * (and thus could be called) before the cookie on the list has a
	 * valid lookup key (and thus can be found).  This will cause a
	 * panic in fdt_intr_mask() if that is called from the handler before
	 * this situation is resolved.  For now we just cross our fingers
	 * and hope that the device won't actually interrupt until we return.
	 */
	ih = ic->ic_funcs->establish(ic->ic_dev, __UNCONST(specifier),
	    ipl, flags, func, arg, xname);
	if (ih != NULL) {
		atomic_store_release(&c->c_ih, ih);
	} else {
		mutex_enter(&fdtbus_interrupt_cookie_mutex);
		LIST_REMOVE(c, c_next);
		mutex_exit(&fdtbus_interrupt_cookie_mutex);
		kmem_free(c, sizeof(*c));
	}

	return ih;
}

void
fdtbus_intr_disestablish(int phandle, void *cookie)
{
	struct fdtbus_interrupt_cookie *c;

	if ((c = fdtbus_get_interrupt_cookie(cookie)) == NULL) {
		panic("%s: interrupt handle not valid", __func__);
	}

	const struct fdtbus_interrupt_controller *ic = c->c_ic;
	ic->ic_funcs->disestablish(ic->ic_dev, cookie);

	/*
	 * Wait for any dangling references other than ours to
	 * drain away.
	 */
	mutex_enter(&fdtbus_interrupt_cookie_mutex);
	while (c->c_refcnt != 1) {
		KASSERT(c->c_refcnt > 0);
		fdtbus_interrupt_cookies_wanted = true;
		cv_wait(&fdtbus_interrupt_cookie_wait,
			&fdtbus_interrupt_cookie_mutex);
	}
	LIST_REMOVE(c, c_next);
	mutex_exit(&fdtbus_interrupt_cookie_mutex);

	kmem_free(c, sizeof(*c));
}

void
fdtbus_intr_mask(int phandle, void *cookie)
{
	struct fdtbus_interrupt_cookie *c;

	if ((c = fdtbus_get_interrupt_cookie(cookie)) == NULL) {
		panic("%s: interrupt handle not valid", __func__);
	}

	struct fdtbus_interrupt_controller * const ic = c->c_ic;

	if (ic->ic_funcs->mask == NULL) {
		panic("%s: no 'mask' method for %s", __func__,
		    device_xname(ic->ic_dev));
	}

	ic->ic_funcs->mask(ic->ic_dev, cookie);
	fdtbus_put_interrupt_cookie(c);
}

void
fdtbus_intr_unmask(int phandle, void *cookie)
{
	struct fdtbus_interrupt_cookie *c;

	if ((c = fdtbus_get_interrupt_cookie(cookie)) == NULL) {
		panic("%s: interrupt handle not valid", __func__);
	}

	struct fdtbus_interrupt_controller * const ic = c->c_ic;

	if (ic->ic_funcs->unmask == NULL) {
		panic("%s: no 'unmask' method for %s", __func__,
		    device_xname(ic->ic_dev));
	}

	ic->ic_funcs->unmask(ic->ic_dev, cookie);
	fdtbus_put_interrupt_cookie(c);
}

bool
fdtbus_intr_str(int phandle, u_int index, char *buf, size_t buflen)
{
	const u_int *specifier;
	int ihandle;

	specifier = get_specifier_by_index(phandle, index, &ihandle);
	if (specifier == NULL)
		return false;

	return fdtbus_intr_str_raw(ihandle, specifier, buf, buflen);
}

bool
fdtbus_intr_str_raw(int ihandle, const u_int *specifier, char *buf, size_t buflen)
{
	struct fdtbus_interrupt_controller *ic;

	ic = fdtbus_get_interrupt_controller(ihandle);
	if (ic == NULL)
		return false;

	return ic->ic_funcs->intrstr(ic->ic_dev, __UNCONST(specifier), buf, buflen);
}

static int
find_address_cells(int phandle)
{
	uint32_t cells;

	if (of_getprop_uint32(phandle, "#address-cells", &cells) != 0)
		cells = 2;

	return cells;
}

static int
find_interrupt_cells(int phandle)
{
	uint32_t cells;

	while (phandle > 0) {
		if (of_getprop_uint32(phandle, "#interrupt-cells", &cells) == 0)
			return cells;
		phandle = OF_parent(phandle);
	}
	return 0;
}

static const u_int *
get_specifier_from_map(int phandle, const u_int *interrupt_spec, int *piphandle)
{
	const u_int *result = NULL;
	int len, resid;

	const u_int *data = fdtbus_get_prop(phandle, "interrupt-map", &len);
	if (data == NULL || len <= 0)
		return NULL;
	resid = len;

	/* child unit address: #address-cells prop of child bus node */
	const int cua_cells = find_address_cells(phandle);
	/* child interrupt specifier: #interrupt-cells of the nexus node */
	const int cis_cells = find_interrupt_cells(phandle);

	/* Offset (in cells) from map entry to child unit address specifier */
	const u_int cua_off = 0;
	/* Offset (in cells) from map entry to child interrupt specifier */
	const u_int cis_off = cua_off + cua_cells;
	/* Offset (in cells) from map entry to interrupt parent phandle */
	const u_int ip_off = cis_off + cis_cells;
	/* Offset (in cells) from map entry to parent unit specifier */
	const u_int pus_off = ip_off + 1;

	const u_int *p = (const u_int *)data;
	while (resid > 0) {
		/* Interrupt parent phandle */
		const u_int iparent = fdtbus_get_phandle_from_native(be32toh(p[ip_off]));

		/* parent unit specifier: #address-cells of the interrupt parent */
		const u_int pus_cells = find_address_cells(iparent);
		/* parent interrupt specifier: #interrupt-cells of the interrupt parent */
		const u_int pis_cells = find_interrupt_cells(iparent);

		/* Offset (in cells) from map entry to parent interrupt specifier */
		const u_int pis_off = pus_off + pus_cells;

#ifdef FDT_INTR_DEBUG
		printf(" intr map (len %d):", pis_off + pis_cells);
		for (int i = 0; i < pis_off + pis_cells; i++)
			printf(" %08x", p[i]);
		printf("\n");
#endif

		if (memcmp(&p[cis_off], interrupt_spec, cis_cells * 4) == 0) {
#ifdef FDT_INTR_DEBUG
			const int slen = pus_cells + pis_cells;
			printf(" intr map match iparent %08x slen %d:", iparent, slen);
			for (int i = 0; i < slen; i++)
				printf(" %08x", p[pus_off + i]);
			printf("\n");
#endif
			result = &p[pus_off];
			*piphandle = iparent;
			goto done;
		}
		/* Determine the length of the entry and skip that many
		 * 32 bit words
		 */
		const u_int reclen = pis_off + pis_cells;
		resid -= reclen * sizeof(u_int);
		p += reclen;
	}

done:
	return result;
}


static const u_int *
get_specifier_from_extended(int phandle, int pindex, int *piphandle)
{
	const u_int *result = NULL;
	struct fdt_phandle_data data;

	if (fdtbus_get_phandle_with_data(phandle, "interrupts-extended",
		"#interrupt-cells", pindex, &data) == 0) {
		*piphandle = data.phandle;
		result = data.values;
	}

	return result;
}

static const u_int *
get_specifier_by_index(int phandle, int pindex, int *piphandle)
{
	const u_int *node_specifier;
	int interrupt_parent, interrupt_cells, len;

	if (of_hasprop(phandle, "interrupts-extended"))
		return get_specifier_from_extended(phandle, pindex, piphandle);

	interrupt_parent = fdtbus_get_interrupt_parent(phandle);
	if (interrupt_parent <= 0)
		return NULL;

	node_specifier = fdtbus_get_prop(phandle, "interrupts", &len);
	if (node_specifier == NULL)
		return NULL;

	interrupt_cells = find_interrupt_cells(interrupt_parent);
	if (interrupt_cells <= 0)
		return NULL;

	const u_int spec_length = len / 4;
	const u_int nintr = spec_length / interrupt_cells;
	if (pindex >= nintr)
		return NULL;

	node_specifier += (interrupt_cells * pindex);

	if (of_hasprop(interrupt_parent, "interrupt-map"))
		return get_specifier_from_map(interrupt_parent, node_specifier, piphandle);

	*piphandle = interrupt_parent;

	return node_specifier;
}
