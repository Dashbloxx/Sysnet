/*	$NetBSD: subr_interrupt.c,v 1.5 2021/12/10 20:36:04 andvar Exp $	*/

/*
 * Copyright (c) 2015 Internet Initiative Japan Inc.
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
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/cdefs.h>
__KERNEL_RCSID(0, "$NetBSD: subr_interrupt.c,v 1.5 2021/12/10 20:36:04 andvar Exp $");

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/errno.h>
#include <sys/cpu.h>
#include <sys/interrupt.h>
#include <sys/intr.h>
#include <sys/kcpuset.h>
#include <sys/kmem.h>
#include <sys/proc.h>
#include <sys/xcall.h>
#include <sys/sysctl.h>

#include <sys/conf.h>
#include <sys/intrio.h>
#include <sys/kauth.h>

#include <machine/limits.h>

#ifdef INTR_DEBUG
#define DPRINTF(msg) printf msg
#else
#define DPRINTF(msg)
#endif

static struct intrio_set kintrio_set = { "\0", NULL, 0 };

#define UNSET_NOINTR_SHIELD	0
#define SET_NOINTR_SHIELD	1

static void
interrupt_shield_xcall(void *arg1, void *arg2)
{
	struct cpu_info *ci;
	struct schedstate_percpu *spc;
	int s, shield;

	ci = arg1;
	shield = (int)(intptr_t)arg2;
	spc = &ci->ci_schedstate;

	s = splsched();
	if (shield == UNSET_NOINTR_SHIELD)
		spc->spc_flags &= ~SPCF_NOINTR;
	else if (shield == SET_NOINTR_SHIELD)
		spc->spc_flags |= SPCF_NOINTR;
	splx(s);
}

/*
 * Change SPCF_NOINTR flag of schedstate_percpu->spc_flags.
 */
static int
interrupt_shield(u_int cpu_idx, int shield)
{
	struct cpu_info *ci;
	struct schedstate_percpu *spc;

	KASSERT(mutex_owned(&cpu_lock));

	ci = cpu_lookup(cpu_idx);
	if (ci == NULL)
		return EINVAL;

	spc = &ci->ci_schedstate;
	if (shield == UNSET_NOINTR_SHIELD) {
		if ((spc->spc_flags & SPCF_NOINTR) == 0)
			return 0;
	} else if (shield == SET_NOINTR_SHIELD) {
		if ((spc->spc_flags & SPCF_NOINTR) != 0)
			return 0;
	}

	if (ci == curcpu() || !mp_online) {
		interrupt_shield_xcall(ci, (void *)(intptr_t)shield);
	} else {
		uint64_t where;
		where = xc_unicast(0, interrupt_shield_xcall, ci,
			(void *)(intptr_t)shield, ci);
		xc_wait(where);
	}

	spc->spc_lastmod = time_second;
	return 0;
}

/*
 * Move all assigned interrupts from "cpu_idx" to the other cpu as possible.
 * The destination cpu is the lowest cpuid of available cpus.
 * If there are no available cpus, give up to move interrupts.
 */
static int
interrupt_avert_intr(u_int cpu_idx)
{
	kcpuset_t *cpuset;
	struct intrids_handler *ii_handler;
	intrid_t *ids;
	int error = 0, i, nids;

	kcpuset_create(&cpuset, true);
	kcpuset_set(cpuset, cpu_idx);

	ii_handler = interrupt_construct_intrids(cpuset);
	if (ii_handler == NULL) {
		error = EINVAL;
		goto out;
	}
	nids = ii_handler->iih_nids;
	if (nids == 0) {
		error = 0;
		goto destruct_out;
	}

	interrupt_get_available(cpuset);
	kcpuset_clear(cpuset, cpu_idx);
	if (kcpuset_iszero(cpuset)) {
		DPRINTF(("%s: no available cpu\n", __func__));
		error = ENOENT;
		goto destruct_out;
	}

	ids = ii_handler->iih_intrids;
	for (i = 0; i < nids; i++) {
		error = interrupt_distribute_handler(ids[i], cpuset, NULL);
		if (error)
			break;
	}

 destruct_out:
	interrupt_destruct_intrids(ii_handler);
 out:
	kcpuset_destroy(cpuset);
	return error;
}

/*
 * Return actual intrio_list_line size.
 * intrio_list_line size is variable by ncpu.
 */
static size_t
interrupt_intrio_list_line_size(void)
{

	return sizeof(struct intrio_list_line) +
		sizeof(struct intrio_list_line_cpu) * (ncpu - 1);
}

/*
 * Return the size of interrupts list data on success.
 * Reterun 0 on failed.
 */
static int
interrupt_intrio_list_size(size_t *ilsize)
{
	struct intrids_handler *ii_handler;

	*ilsize = 0;

	/* buffer header */
	*ilsize += sizeof(struct intrio_list);

	/* il_line body */
	ii_handler = interrupt_construct_intrids(kcpuset_running);
	if (ii_handler == NULL)
		return EOPNOTSUPP;
	*ilsize += interrupt_intrio_list_line_size() * ii_handler->iih_nids;

	interrupt_destruct_intrids(ii_handler);
	return 0;
}

/*
 * Set intrctl list data to "il", and return list structure bytes.
 * If error occurred, return <0.
 * If "data" == NULL, simply return list structure bytes.
 */
static int
interrupt_intrio_list(struct intrio_list *il, size_t ilsize)
{
	struct intrio_list_line *illine;
	kcpuset_t *assigned, *avail;
	struct intrids_handler *ii_handler;
	intrid_t *ids;
	u_int cpu_idx;
	int nids, intr_idx, error, line_size;

	illine = (struct intrio_list_line *)
	    ((char *)il + sizeof(struct intrio_list));
	il->il_lineoffset = (off_t)((uintptr_t)illine - (uintptr_t)il);

	kcpuset_create(&avail, true);
	interrupt_get_available(avail);
	kcpuset_create(&assigned, true);

	ii_handler = interrupt_construct_intrids(kcpuset_running);
	if (ii_handler == NULL) {
		DPRINTF(("%s: interrupt_construct_intrids() failed\n",
		    __func__));
		error = EOPNOTSUPP;
		goto out;
	}

	line_size = interrupt_intrio_list_line_size();
	/* ensure interrupts are not added after interrupt_intrio_list_size() */
	nids = ii_handler->iih_nids;
	ids = ii_handler->iih_intrids;
	if (ilsize < sizeof(struct intrio_list) + line_size * nids) {
		DPRINTF(("%s: interrupts are added during execution.\n",
		    __func__));
		error = EAGAIN;
		goto destruct_out;
	}

	for (intr_idx = 0; intr_idx < nids; intr_idx++) {
		char devname[INTRDEVNAMEBUF];

		strncpy(illine->ill_intrid, ids[intr_idx], INTRIDBUF);
		interrupt_get_devname(ids[intr_idx], devname, sizeof(devname));
		strncpy(illine->ill_xname, devname, INTRDEVNAMEBUF);

		interrupt_get_assigned(ids[intr_idx], assigned);
		for (cpu_idx = 0; cpu_idx < ncpu; cpu_idx++) {
			struct intrio_list_line_cpu *illcpu =
			    &illine->ill_cpu[cpu_idx];

			illcpu->illc_assigned =
			    kcpuset_isset(assigned, cpu_idx);
			illcpu->illc_count =
			    interrupt_get_count(ids[intr_idx], cpu_idx);
		}

		illine = (struct intrio_list_line *)
		    ((char *)illine + line_size);
	}

	error = 0;
	il->il_version = INTRIO_LIST_VERSION;
	il->il_ncpus = ncpu;
	il->il_nintrs = nids;
	il->il_linesize = line_size;
	il->il_bufsize = ilsize;

 destruct_out:
	interrupt_destruct_intrids(ii_handler);
 out:
	kcpuset_destroy(assigned);
	kcpuset_destroy(avail);

	return error;
}

/*
 * "intrctl list" entry
 */
static int
interrupt_intrio_list_sysctl(SYSCTLFN_ARGS)
{
	int error;
	void *buf;
	size_t ilsize;

	if (oldlenp == NULL)
		return EINVAL;

	if ((error = interrupt_intrio_list_size(&ilsize)) != 0)
		return error;

	/*
	 * If oldp == NULL, the sysctl(8) caller process want to get the size of
	 * intrctl list data only.
	 */
	if (oldp == NULL) {
		*oldlenp = ilsize;
		return 0;
	}

	/*
	 * If oldp != NULL, the sysctl(8) caller process want to get both the
	 * size and the contents of intrctl list data.
	 */
	if (*oldlenp < ilsize)
		return ENOMEM;

	buf = kmem_zalloc(ilsize, KM_SLEEP);
	if ((error = interrupt_intrio_list(buf, ilsize)) != 0)
		goto out;

	error = copyout(buf, oldp, ilsize);
 out:
	kmem_free(buf, ilsize);
	return error;
}

/*
 * "intrctl affinity" entry
 */
static int
interrupt_set_affinity_sysctl(SYSCTLFN_ARGS)
{
	struct sysctlnode node;
	struct intrio_set *iset;
	cpuset_t *ucpuset;
	kcpuset_t *kcpuset;
	int error;

	error = kauth_authorize_system(l->l_cred, KAUTH_SYSTEM_INTR,
	    KAUTH_REQ_SYSTEM_INTR_AFFINITY, NULL, NULL, NULL);
	if (error)
		return EPERM;

	node = *rnode;
	iset = (struct intrio_set *)node.sysctl_data;

	error = sysctl_lookup(SYSCTLFN_CALL(&node));
	if (error != 0 || newp == NULL)
		return error;

	ucpuset = iset->cpuset;
	kcpuset_create(&kcpuset, true);
	error = kcpuset_copyin(ucpuset, kcpuset, iset->cpuset_size);
	if (error)
		goto out;
	if (kcpuset_iszero(kcpuset)) {
		error = EINVAL;
		goto out;
	}

	error = interrupt_distribute_handler(iset->intrid, kcpuset, NULL);

 out:
	kcpuset_destroy(kcpuset);
	return error;
}

/*
 * "intrctl intr" entry
 */
static int
interrupt_intr_sysctl(SYSCTLFN_ARGS)
{
	struct sysctlnode node;
	struct intrio_set *iset;
	cpuset_t *ucpuset;
	kcpuset_t *kcpuset;
	int error;
	u_int cpu_idx;

	error = kauth_authorize_system(l->l_cred, KAUTH_SYSTEM_CPU,
	    KAUTH_REQ_SYSTEM_CPU_SETSTATE, NULL, NULL, NULL);
	if (error)
		return EPERM;

	node = *rnode;
	iset = (struct intrio_set *)node.sysctl_data;

	error = sysctl_lookup(SYSCTLFN_CALL(&node));
	if (error != 0 || newp == NULL)
		return error;

	ucpuset = iset->cpuset;
	kcpuset_create(&kcpuset, true);
	error = kcpuset_copyin(ucpuset, kcpuset, iset->cpuset_size);
	if (error)
		goto out;
	if (kcpuset_iszero(kcpuset)) {
		error = EINVAL;
		goto out;
	}

	cpu_idx = kcpuset_ffs(kcpuset) - 1; /* support one CPU only */

	mutex_enter(&cpu_lock);
	error = interrupt_shield(cpu_idx, UNSET_NOINTR_SHIELD);
	mutex_exit(&cpu_lock);

 out:
	kcpuset_destroy(kcpuset);
	return error;
}

/*
 * "intrctl nointr" entry
 */
static int
interrupt_nointr_sysctl(SYSCTLFN_ARGS)
{
	struct sysctlnode node;
	struct intrio_set *iset;
	cpuset_t *ucpuset;
	kcpuset_t *kcpuset;
	int error;
	u_int cpu_idx;

	error = kauth_authorize_system(l->l_cred, KAUTH_SYSTEM_CPU,
	    KAUTH_REQ_SYSTEM_CPU_SETSTATE, NULL, NULL, NULL);
	if (error)
		return EPERM;

	node = *rnode;
	iset = (struct intrio_set *)node.sysctl_data;

	error = sysctl_lookup(SYSCTLFN_CALL(&node));
	if (error != 0 || newp == NULL)
		return error;

	ucpuset = iset->cpuset;
	kcpuset_create(&kcpuset, true);
	error = kcpuset_copyin(ucpuset, kcpuset, iset->cpuset_size);
	if (error)
		goto out;
	if (kcpuset_iszero(kcpuset)) {
		error = EINVAL;
		goto out;
	}

	cpu_idx = kcpuset_ffs(kcpuset) - 1; /* support one CPU only */

	mutex_enter(&cpu_lock);
	error = interrupt_shield(cpu_idx, SET_NOINTR_SHIELD);
	mutex_exit(&cpu_lock);
	if (error)
		goto out;

	error = interrupt_avert_intr(cpu_idx);

 out:
	kcpuset_destroy(kcpuset);
	return error;
}

SYSCTL_SETUP(sysctl_interrupt_setup, "sysctl interrupt setup")
{
	const struct sysctlnode *node = NULL;

	sysctl_createv(clog, 0, NULL, &node,
		       CTLFLAG_PERMANENT, CTLTYPE_NODE,
		       "intr", SYSCTL_DESCR("Interrupt options"),
		       NULL, 0, NULL, 0,
		       CTL_KERN, CTL_CREATE, CTL_EOL);

	sysctl_createv(clog, 0, &node, NULL,
		       CTLFLAG_PERMANENT, CTLTYPE_STRUCT,
		       "list", SYSCTL_DESCR("intrctl list"),
		       interrupt_intrio_list_sysctl, 0, NULL,
		        0, CTL_CREATE, CTL_EOL);

	sysctl_createv(clog, 0, &node, NULL,
		       CTLFLAG_PERMANENT|CTLFLAG_READWRITE, CTLTYPE_STRUCT,
		       "affinity", SYSCTL_DESCR("set affinity"),
		       interrupt_set_affinity_sysctl, 0, &kintrio_set,
		       sizeof(kintrio_set), CTL_CREATE, CTL_EOL);

	sysctl_createv(clog, 0, &node, NULL,
		       CTLFLAG_PERMANENT|CTLFLAG_READWRITE, CTLTYPE_STRUCT,
		       "intr", SYSCTL_DESCR("set intr"),
		       interrupt_intr_sysctl, 0, &kintrio_set,
		       sizeof(kintrio_set), CTL_CREATE, CTL_EOL);

	sysctl_createv(clog, 0, &node, NULL,
		       CTLFLAG_PERMANENT|CTLFLAG_READWRITE, CTLTYPE_STRUCT,
		       "nointr", SYSCTL_DESCR("set nointr"),
		       interrupt_nointr_sysctl, 0, &kintrio_set,
		       sizeof(kintrio_set), CTL_CREATE, CTL_EOL);
}
