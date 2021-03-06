/*	$NetBSD: nouveau_nvkm_engine_disp_hdmigm200.c,v 1.2 2021/12/18 23:45:35 riastradh Exp $	*/

/*
 * Copyright 2018 Ilia Mirkin
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Ilia Mirkin
 */
#include <sys/cdefs.h>
__KERNEL_RCSID(0, "$NetBSD: nouveau_nvkm_engine_disp_hdmigm200.c,v 1.2 2021/12/18 23:45:35 riastradh Exp $");

#include "hdmi.h"

void
gm200_hdmi_scdc(struct nvkm_ior *ior, int head, u8 scdc)
{
	struct nvkm_device *device = ior->disp->engine.subdev.device;
	const u32 hoff = head * 0x800;
	const u32 ctrl = scdc & 0x3;

	nvkm_mask(device, 0x61c5bc + hoff, 0x00000003, ctrl);

	ior->tmds.high_speed = !!(scdc & 0x2);
}
