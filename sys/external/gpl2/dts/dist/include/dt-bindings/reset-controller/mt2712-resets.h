/*	$NetBSD: mt2712-resets.h,v 1.1.1.1 2021/11/07 16:49:57 jmcneill Exp $	*/

/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2019 MediaTek Inc.
 * Author: Yong Liang <yong.liang@mediatek.com>
 */

#ifndef _DT_BINDINGS_RESET_CONTROLLER_MT2712
#define _DT_BINDINGS_RESET_CONTROLLER_MT2712

#define MT2712_TOPRGU_INFRA_SW_RST				0
#define MT2712_TOPRGU_MM_SW_RST					1
#define MT2712_TOPRGU_MFG_SW_RST				2
#define MT2712_TOPRGU_VENC_SW_RST				3
#define MT2712_TOPRGU_VDEC_SW_RST				4
#define MT2712_TOPRGU_IMG_SW_RST				5
#define MT2712_TOPRGU_INFRA_AO_SW_RST				8
#define MT2712_TOPRGU_USB_SW_RST				9
#define MT2712_TOPRGU_APMIXED_SW_RST				10

#define MT2712_TOPRGU_SW_RST_NUM				11

#endif  /* _DT_BINDINGS_RESET_CONTROLLER_MT2712 */
