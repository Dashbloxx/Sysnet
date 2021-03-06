/*	$NetBSD: bit.h,v 1.3 2021/12/18 23:45:33 riastradh Exp $	*/

/* SPDX-License-Identifier: MIT */
#ifndef __NVBIOS_BIT_H__
#define __NVBIOS_BIT_H__
struct bit_entry {
	u8  id;
	u8  version;
	u16 length;
	u16 offset;
};

int bit_entry(struct nvkm_bios *, u8 id, struct bit_entry *);
#endif
