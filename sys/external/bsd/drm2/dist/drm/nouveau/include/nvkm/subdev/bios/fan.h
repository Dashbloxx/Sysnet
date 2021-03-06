/*	$NetBSD: fan.h,v 1.3 2021/12/18 23:45:33 riastradh Exp $	*/

/* SPDX-License-Identifier: MIT */
#ifndef __NVBIOS_FAN_H__
#define __NVBIOS_FAN_H__
#include <subdev/bios/therm.h>

u32 nvbios_fan_parse(struct nvkm_bios *bios, struct nvbios_therm_fan *fan);
#endif
