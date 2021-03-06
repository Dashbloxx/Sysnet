/*	$NetBSD: mt8167-larb-port.h,v 1.1.1.1 2021/11/07 16:49:56 jmcneill Exp $	*/

/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2020 MediaTek Inc.
 * Copyright (c) 2020 BayLibre, SAS
 * Author: Honghui Zhang <honghui.zhang@mediatek.com>
 * Author: Fabien Parent <fparent@baylibre.com>
 */
#ifndef _DT_BINDINGS_MEMORY_MT8167_LARB_PORT_H_
#define _DT_BINDINGS_MEMORY_MT8167_LARB_PORT_H_

#include <dt-bindings/memory/mtk-memory-port.h>

#define M4U_LARB0_ID			0
#define M4U_LARB1_ID			1
#define M4U_LARB2_ID			2

/* larb0 */
#define M4U_PORT_DISP_OVL0		MTK_M4U_ID(M4U_LARB0_ID, 0)
#define M4U_PORT_DISP_RDMA0		MTK_M4U_ID(M4U_LARB0_ID, 1)
#define M4U_PORT_DISP_WDMA0		MTK_M4U_ID(M4U_LARB0_ID, 2)
#define M4U_PORT_DISP_RDMA1		MTK_M4U_ID(M4U_LARB0_ID, 3)
#define M4U_PORT_MDP_RDMA		MTK_M4U_ID(M4U_LARB0_ID, 4)
#define M4U_PORT_MDP_WDMA		MTK_M4U_ID(M4U_LARB0_ID, 5)
#define M4U_PORT_MDP_WROT		MTK_M4U_ID(M4U_LARB0_ID, 6)
#define M4U_PORT_DISP_FAKE		MTK_M4U_ID(M4U_LARB0_ID, 7)

/* larb1*/
#define M4U_PORT_CAM_IMGO		MTK_M4U_ID(M4U_LARB1_ID, 0)
#define M4U_PORT_CAM_IMG2O		MTK_M4U_ID(M4U_LARB1_ID, 1)
#define M4U_PORT_CAM_LSCI		MTK_M4U_ID(M4U_LARB1_ID, 2)
#define M4U_PORT_CAM_ESFKO		MTK_M4U_ID(M4U_LARB1_ID, 3)
#define M4U_PORT_CAM_AAO		MTK_M4U_ID(M4U_LARB1_ID, 4)
#define M4U_PORT_VENC_REC		MTK_M4U_ID(M4U_LARB1_ID, 5)
#define M4U_PORT_VENC_BSDMA		MTK_M4U_ID(M4U_LARB1_ID, 6)
#define M4U_PORT_VENC_RD_COMV		MTK_M4U_ID(M4U_LARB1_ID, 7)
#define M4U_PORT_CAM_IMGI		MTK_M4U_ID(M4U_LARB1_ID, 8)
#define M4U_PORT_VENC_CUR_LUMA		MTK_M4U_ID(M4U_LARB1_ID, 9)
#define M4U_PORT_VENC_CUR_CHROMA	MTK_M4U_ID(M4U_LARB1_ID, 10)
#define M4U_PORT_VENC_REF_LUMA		MTK_M4U_ID(M4U_LARB1_ID, 11)
#define M4U_PORT_VENC_REF_CHROMA	MTK_M4U_ID(M4U_LARB1_ID, 12)

/* larb2*/
#define M4U_PORT_HW_VDEC_MC_EXT		MTK_M4U_ID(M4U_LARB2_ID, 0)
#define M4U_PORT_HW_VDEC_PP_EXT		MTK_M4U_ID(M4U_LARB2_ID, 1)
#define M4U_PORT_HW_VDEC_VLD_EXT	MTK_M4U_ID(M4U_LARB2_ID, 2)
#define M4U_PORT_HW_VDEC_AVC_MV_EXT	MTK_M4U_ID(M4U_LARB2_ID, 3)
#define M4U_PORT_HW_VDEC_PRED_RD_EXT	MTK_M4U_ID(M4U_LARB2_ID, 4)
#define M4U_PORT_HW_VDEC_PRED_WR_EXT	MTK_M4U_ID(M4U_LARB2_ID, 5)
#define M4U_PORT_HW_VDEC_PPWRAP_EXT	MTK_M4U_ID(M4U_LARB2_ID, 6)

#endif
