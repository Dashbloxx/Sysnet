/*	$NetBSD: bif_3_0_d.h,v 1.2 2021/12/18 23:45:09 riastradh Exp $	*/

/*
 *
 * Copyright (C) 2016 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef BIF_3_0_D_H
#define BIF_3_0_D_H

#define ixPB0_DFT_DEBUG_CTRL_REG0 0x1300C
#define ixPB0_DFT_JIT_INJ_REG0 0x13000
#define ixPB0_DFT_JIT_INJ_REG1 0x13004
#define ixPB0_DFT_JIT_INJ_REG2 0x13008
#define ixPB0_GLB_CTRL_REG0 0x10004
#define ixPB0_GLB_CTRL_REG1 0x10008
#define ixPB0_GLB_CTRL_REG2 0x1000C
#define ixPB0_GLB_CTRL_REG3 0x10010
#define ixPB0_GLB_CTRL_REG4 0x10014
#define ixPB0_GLB_CTRL_REG5 0x10018
#define ixPB0_GLB_OVRD_REG0 0x10030
#define ixPB0_GLB_OVRD_REG1 0x10034
#define ixPB0_GLB_OVRD_REG2 0x10038
#define ixPB0_GLB_SCI_STAT_OVRD_REG0 0x1001C
#define ixPB0_GLB_SCI_STAT_OVRD_REG1 0x10020
#define ixPB0_GLB_SCI_STAT_OVRD_REG2 0x10024
#define ixPB0_GLB_SCI_STAT_OVRD_REG3 0x10028
#define ixPB0_GLB_SCI_STAT_OVRD_REG4 0x1002C
#define ixPB0_HW_DEBUG 0x12004
#define ixPB0_PIF_CNTL 0x0010
#define ixPB0_PIF_CNTL2 0x0014
#define ixPB0_PIF_HW_DEBUG 0x0002
#define ixPB0_PIF_PAIRING 0x0011
#define ixPB0_PIF_PDNB_OVERRIDE_0 0x0020
#define ixPB0_PIF_PDNB_OVERRIDE_10 0x0032
#define ixPB0_PIF_PDNB_OVERRIDE_1 0x0021
#define ixPB0_PIF_PDNB_OVERRIDE_11 0x0033
#define ixPB0_PIF_PDNB_OVERRIDE_12 0x0034
#define ixPB0_PIF_PDNB_OVERRIDE_13 0x0035
#define ixPB0_PIF_PDNB_OVERRIDE_14 0x0036
#define ixPB0_PIF_PDNB_OVERRIDE_15 0x0037
#define ixPB0_PIF_PDNB_OVERRIDE_2 0x0022
#define ixPB0_PIF_PDNB_OVERRIDE_3 0x0023
#define ixPB0_PIF_PDNB_OVERRIDE_4 0x0024
#define ixPB0_PIF_PDNB_OVERRIDE_5 0x0025
#define ixPB0_PIF_PDNB_OVERRIDE_6 0x0026
#define ixPB0_PIF_PDNB_OVERRIDE_7 0x0027
#define ixPB0_PIF_PDNB_OVERRIDE_8 0x0030
#define ixPB0_PIF_PDNB_OVERRIDE_9 0x0031
#define ixPB0_PIF_PWRDOWN_0 0x0012
#define ixPB0_PIF_PWRDOWN_1 0x0013
#define ixPB0_PIF_PWRDOWN_2 0x0017
#define ixPB0_PIF_PWRDOWN_3 0x0018
#define ixPB0_PIF_SC_CTL 0x0016
#define ixPB0_PIF_SCRATCH 0x0001
#define ixPB0_PIF_SEQ_STATUS_0 0x0028
#define ixPB0_PIF_SEQ_STATUS_10 0x003A
#define ixPB0_PIF_SEQ_STATUS_1 0x0029
#define ixPB0_PIF_SEQ_STATUS_11 0x003B
#define ixPB0_PIF_SEQ_STATUS_12 0x003C
#define ixPB0_PIF_SEQ_STATUS_13 0x003D
#define ixPB0_PIF_SEQ_STATUS_14 0x003E
#define ixPB0_PIF_SEQ_STATUS_15 0x003F
#define ixPB0_PIF_SEQ_STATUS_2 0x002A
#define ixPB0_PIF_SEQ_STATUS_3 0x002B
#define ixPB0_PIF_SEQ_STATUS_4 0x002C
#define ixPB0_PIF_SEQ_STATUS_5 0x002D
#define ixPB0_PIF_SEQ_STATUS_6 0x002E
#define ixPB0_PIF_SEQ_STATUS_7 0x002F
#define ixPB0_PIF_SEQ_STATUS_8 0x0038
#define ixPB0_PIF_SEQ_STATUS_9 0x0039
#define ixPB0_PIF_TXPHYSTATUS 0x0015
#define ixPB0_PLL_LC0_CTRL_REG0 0x14480
#define ixPB0_PLL_LC0_OVRD_REG0 0x14490
#define ixPB0_PLL_LC0_OVRD_REG1 0x14494
#define ixPB0_PLL_LC0_SCI_STAT_OVRD_REG0 0x14500
#define ixPB0_PLL_LC1_SCI_STAT_OVRD_REG0 0x14504
#define ixPB0_PLL_LC2_SCI_STAT_OVRD_REG0 0x14508
#define ixPB0_PLL_LC3_SCI_STAT_OVRD_REG0 0x1450C
#define ixPB0_PLL_RO0_CTRL_REG0 0x14440
#define ixPB0_PLL_RO0_OVRD_REG0 0x14450
#define ixPB0_PLL_RO0_OVRD_REG1 0x14454
#define ixPB0_PLL_RO0_SCI_STAT_OVRD_REG0 0x14460
#define ixPB0_PLL_RO1_SCI_STAT_OVRD_REG0 0x14464
#define ixPB0_PLL_RO2_SCI_STAT_OVRD_REG0 0x14468
#define ixPB0_PLL_RO3_SCI_STAT_OVRD_REG0 0x1446C
#define ixPB0_PLL_RO_GLB_CTRL_REG0 0x14000
#define ixPB0_PLL_RO_GLB_OVRD_REG0 0x14010
#define ixPB0_RX_GLB_CTRL_REG0 0x16000
#define ixPB0_RX_GLB_CTRL_REG1 0x16004
#define ixPB0_RX_GLB_CTRL_REG2 0x16008
#define ixPB0_RX_GLB_CTRL_REG3 0x1600C
#define ixPB0_RX_GLB_CTRL_REG4 0x16010
#define ixPB0_RX_GLB_CTRL_REG5 0x16014
#define ixPB0_RX_GLB_CTRL_REG6 0x16018
#define ixPB0_RX_GLB_CTRL_REG7 0x1601C
#define ixPB0_RX_GLB_CTRL_REG8 0x16020
#define ixPB0_RX_GLB_OVRD_REG0 0x16030
#define ixPB0_RX_GLB_OVRD_REG1 0x16034
#define ixPB0_RX_GLB_SCI_STAT_OVRD_REG0 0x16028
#define ixPB0_RX_LANE0_CTRL_REG0 0x16440
#define ixPB0_RX_LANE0_SCI_STAT_OVRD_REG0 0x16448
#define ixPB0_RX_LANE10_CTRL_REG0 0x17500
#define ixPB0_RX_LANE10_SCI_STAT_OVRD_REG0 0x17508
#define ixPB0_RX_LANE11_CTRL_REG0 0x17600
#define ixPB0_RX_LANE11_SCI_STAT_OVRD_REG0 0x17608
#define ixPB0_RX_LANE12_CTRL_REG0 0x17840
#define ixPB0_RX_LANE12_SCI_STAT_OVRD_REG0 0x17848
#define ixPB0_RX_LANE13_CTRL_REG0 0x17880
#define ixPB0_RX_LANE13_SCI_STAT_OVRD_REG0 0x17888
#define ixPB0_RX_LANE14_CTRL_REG0 0x17900
#define ixPB0_RX_LANE14_SCI_STAT_OVRD_REG0 0x17908
#define ixPB0_RX_LANE15_CTRL_REG0 0x17A00
#define ixPB0_RX_LANE15_SCI_STAT_OVRD_REG0 0x17A08
#define ixPB0_RX_LANE1_CTRL_REG0 0x16480
#define ixPB0_RX_LANE1_SCI_STAT_OVRD_REG0 0x16488
#define ixPB0_RX_LANE2_CTRL_REG0 0x16500
#define ixPB0_RX_LANE2_SCI_STAT_OVRD_REG0 0x16508
#define ixPB0_RX_LANE3_CTRL_REG0 0x16600
#define ixPB0_RX_LANE3_SCI_STAT_OVRD_REG0 0x16608
#define ixPB0_RX_LANE4_CTRL_REG0 0x16800
#define ixPB0_RX_LANE4_SCI_STAT_OVRD_REG0 0x16848
#define ixPB0_RX_LANE5_CTRL_REG0 0x16880
#define ixPB0_RX_LANE5_SCI_STAT_OVRD_REG0 0x16888
#define ixPB0_RX_LANE6_CTRL_REG0 0x16900
#define ixPB0_RX_LANE6_SCI_STAT_OVRD_REG0 0x16908
#define ixPB0_RX_LANE7_CTRL_REG0 0x16A00
#define ixPB0_RX_LANE7_SCI_STAT_OVRD_REG0 0x16A08
#define ixPB0_RX_LANE8_CTRL_REG0 0x17440
#define ixPB0_RX_LANE8_SCI_STAT_OVRD_REG0 0x17448
#define ixPB0_RX_LANE9_CTRL_REG0 0x17480
#define ixPB0_RX_LANE9_SCI_STAT_OVRD_REG0 0x17488
#define ixPB0_STRAP_GLB_REG0 0x12020
#define ixPB0_STRAP_PLL_REG0 0x12030
#define ixPB0_STRAP_RX_REG0 0x12028
#define ixPB0_STRAP_RX_REG1 0x1202C
#define ixPB0_STRAP_TX_REG0 0x12024
#define ixPB0_TX_GLB_COEFF_ACCEPT_TABLE_REG0 0x18014
#define ixPB0_TX_GLB_COEFF_ACCEPT_TABLE_REG1 0x18018
#define ixPB0_TX_GLB_COEFF_ACCEPT_TABLE_REG2 0x1801C
#define ixPB0_TX_GLB_COEFF_ACCEPT_TABLE_REG3 0x18020
#define ixPB0_TX_GLB_CTRL_REG0 0x18000
#define ixPB0_TX_GLB_LANE_SKEW_CTRL 0x18004
#define ixPB0_TX_GLB_OVRD_REG0 0x18030
#define ixPB0_TX_GLB_OVRD_REG1 0x18034
#define ixPB0_TX_GLB_OVRD_REG2 0x18038
#define ixPB0_TX_GLB_OVRD_REG3 0x1803C
#define ixPB0_TX_GLB_OVRD_REG4 0x18040
#define ixPB0_TX_GLB_SCI_STAT_OVRD_REG0 0x18010
#define ixPB0_TX_LANE0_CTRL_REG0 0x18440
#define ixPB0_TX_LANE0_OVRD_REG0 0x18444
#define ixPB0_TX_LANE0_SCI_STAT_OVRD_REG0 0x18448
#define ixPB0_TX_LANE10_CTRL_REG0 0x19500
#define ixPB0_TX_LANE10_OVRD_REG0 0x19504
#define ixPB0_TX_LANE10_SCI_STAT_OVRD_REG0 0x19508
#define ixPB0_TX_LANE11_CTRL_REG0 0x19600
#define ixPB0_TX_LANE11_OVRD_REG0 0x19604
#define ixPB0_TX_LANE11_SCI_STAT_OVRD_REG0 0x19608
#define ixPB0_TX_LANE12_CTRL_REG0 0x19840
#define ixPB0_TX_LANE12_OVRD_REG0 0x19844
#define ixPB0_TX_LANE12_SCI_STAT_OVRD_REG0 0x19848
#define ixPB0_TX_LANE13_CTRL_REG0 0x19880
#define ixPB0_TX_LANE13_OVRD_REG0 0x19884
#define ixPB0_TX_LANE13_SCI_STAT_OVRD_REG0 0x19888
#define ixPB0_TX_LANE14_CTRL_REG0 0x19900
#define ixPB0_TX_LANE14_OVRD_REG0 0x19904
#define ixPB0_TX_LANE14_SCI_STAT_OVRD_REG0 0x19908
#define ixPB0_TX_LANE15_CTRL_REG0 0x19A00
#define ixPB0_TX_LANE15_OVRD_REG0 0x19A04
#define ixPB0_TX_LANE15_SCI_STAT_OVRD_REG0 0x19A08
#define ixPB0_TX_LANE1_CTRL_REG0 0x18480
#define ixPB0_TX_LANE1_OVRD_REG0 0x18484
#define ixPB0_TX_LANE1_SCI_STAT_OVRD_REG0 0x18488
#define ixPB0_TX_LANE2_CTRL_REG0 0x18500
#define ixPB0_TX_LANE2_OVRD_REG0 0x18504
#define ixPB0_TX_LANE2_SCI_STAT_OVRD_REG0 0x18508
#define ixPB0_TX_LANE3_CTRL_REG0 0x18600
#define ixPB0_TX_LANE3_OVRD_REG0 0x18604
#define ixPB0_TX_LANE3_SCI_STAT_OVRD_REG0 0x18608
#define ixPB0_TX_LANE4_CTRL_REG0 0x18840
#define ixPB0_TX_LANE4_OVRD_REG0 0x18844
#define ixPB0_TX_LANE4_SCI_STAT_OVRD_REG0 0x18848
#define ixPB0_TX_LANE5_CTRL_REG0 0x18880
#define ixPB0_TX_LANE5_OVRD_REG0 0x18884
#define ixPB0_TX_LANE5_SCI_STAT_OVRD_REG0 0x18888
#define ixPB0_TX_LANE6_CTRL_REG0 0x18900
#define ixPB0_TX_LANE6_OVRD_REG0 0x18904
#define ixPB0_TX_LANE6_SCI_STAT_OVRD_REG0 0x18908
#define ixPB0_TX_LANE7_CTRL_REG0 0x18A00
#define ixPB0_TX_LANE7_OVRD_REG0 0x18A04
#define ixPB0_TX_LANE7_SCI_STAT_OVRD_REG0 0x18A08
#define ixPB0_TX_LANE8_CTRL_REG0 0x19440
#define ixPB0_TX_LANE8_OVRD_REG0 0x19444
#define ixPB0_TX_LANE8_SCI_STAT_OVRD_REG0 0x19448
#define ixPB0_TX_LANE9_CTRL_REG0 0x19480
#define ixPB0_TX_LANE9_OVRD_REG0 0x19484
#define ixPB0_TX_LANE9_SCI_STAT_OVRD_REG0 0x19488
#define ixPB1_DFT_DEBUG_CTRL_REG0 0x1300C
#define ixPB1_DFT_JIT_INJ_REG0 0x13000
#define ixPB1_DFT_JIT_INJ_REG1 0x13004
#define ixPB1_DFT_JIT_INJ_REG2 0x13008
#define ixPB1_GLB_CTRL_REG0 0x10004
#define ixPB1_GLB_CTRL_REG1 0x10008
#define ixPB1_GLB_CTRL_REG2 0x1000C
#define ixPB1_GLB_CTRL_REG3 0x10010
#define ixPB1_GLB_CTRL_REG4 0x10014
#define ixPB1_GLB_CTRL_REG5 0x10018
#define ixPB1_GLB_OVRD_REG0 0x10030
#define ixPB1_GLB_OVRD_REG1 0x10034
#define ixPB1_GLB_OVRD_REG2 0x10038
#define ixPB1_GLB_SCI_STAT_OVRD_REG0 0x1001C
#define ixPB1_GLB_SCI_STAT_OVRD_REG1 0x10020
#define ixPB1_GLB_SCI_STAT_OVRD_REG2 0x10024
#define ixPB1_GLB_SCI_STAT_OVRD_REG3 0x10028
#define ixPB1_GLB_SCI_STAT_OVRD_REG4 0x1002C
#define ixPB1_HW_DEBUG 0x12004
#define ixPB1_PIF_CNTL 0x0010
#define ixPB1_PIF_CNTL2 0x0014
#define ixPB1_PIF_HW_DEBUG 0x0002
#define ixPB1_PIF_PAIRING 0x0011
#define ixPB1_PIF_PDNB_OVERRIDE_0 0x0020
#define ixPB1_PIF_PDNB_OVERRIDE_10 0x0032
#define ixPB1_PIF_PDNB_OVERRIDE_1 0x0021
#define ixPB1_PIF_PDNB_OVERRIDE_11 0x0033
#define ixPB1_PIF_PDNB_OVERRIDE_12 0x0034
#define ixPB1_PIF_PDNB_OVERRIDE_13 0x0035
#define ixPB1_PIF_PDNB_OVERRIDE_14 0x0036
#define ixPB1_PIF_PDNB_OVERRIDE_15 0x0037
#define ixPB1_PIF_PDNB_OVERRIDE_2 0x0022
#define ixPB1_PIF_PDNB_OVERRIDE_3 0x0023
#define ixPB1_PIF_PDNB_OVERRIDE_4 0x0024
#define ixPB1_PIF_PDNB_OVERRIDE_5 0x0025
#define ixPB1_PIF_PDNB_OVERRIDE_6 0x0026
#define ixPB1_PIF_PDNB_OVERRIDE_7 0x0027
#define ixPB1_PIF_PDNB_OVERRIDE_8 0x0030
#define ixPB1_PIF_PDNB_OVERRIDE_9 0x0031
#define ixPB1_PIF_PWRDOWN_0 0x0012
#define ixPB1_PIF_PWRDOWN_1 0x0013
#define ixPB1_PIF_PWRDOWN_2 0x0017
#define ixPB1_PIF_PWRDOWN_3 0x0018
#define ixPB1_PIF_SC_CTL 0x0016
#define ixPB1_PIF_SCRATCH 0x0001
#define ixPB1_PIF_SEQ_STATUS_0 0x0028
#define ixPB1_PIF_SEQ_STATUS_10 0x003A
#define ixPB1_PIF_SEQ_STATUS_1 0x0029
#define ixPB1_PIF_SEQ_STATUS_11 0x003B
#define ixPB1_PIF_SEQ_STATUS_12 0x003C
#define ixPB1_PIF_SEQ_STATUS_13 0x003D
#define ixPB1_PIF_SEQ_STATUS_14 0x003E
#define ixPB1_PIF_SEQ_STATUS_15 0x003F
#define ixPB1_PIF_SEQ_STATUS_2 0x002A
#define ixPB1_PIF_SEQ_STATUS_3 0x002B
#define ixPB1_PIF_SEQ_STATUS_4 0x002C
#define ixPB1_PIF_SEQ_STATUS_5 0x002D
#define ixPB1_PIF_SEQ_STATUS_6 0x002E
#define ixPB1_PIF_SEQ_STATUS_7 0x002F
#define ixPB1_PIF_SEQ_STATUS_8 0x0038
#define ixPB1_PIF_SEQ_STATUS_9 0x0039
#define ixPB1_PIF_TXPHYSTATUS 0x0015
#define ixPB1_PLL_LC0_CTRL_REG0 0x14480
#define ixPB1_PLL_LC0_OVRD_REG0 0x14490
#define ixPB1_PLL_LC0_OVRD_REG1 0x14494
#define ixPB1_PLL_LC0_SCI_STAT_OVRD_REG0 0x14500
#define ixPB1_PLL_LC1_SCI_STAT_OVRD_REG0 0x14504
#define ixPB1_PLL_LC2_SCI_STAT_OVRD_REG0 0x14508
#define ixPB1_PLL_LC3_SCI_STAT_OVRD_REG0 0x1450C
#define ixPB1_PLL_RO0_CTRL_REG0 0x14440
#define ixPB1_PLL_RO0_OVRD_REG0 0x14450
#define ixPB1_PLL_RO0_OVRD_REG1 0x14454
#define ixPB1_PLL_RO0_SCI_STAT_OVRD_REG0 0x14460
#define ixPB1_PLL_RO1_SCI_STAT_OVRD_REG0 0x14464
#define ixPB1_PLL_RO2_SCI_STAT_OVRD_REG0 0x14468
#define ixPB1_PLL_RO3_SCI_STAT_OVRD_REG0 0x1446C
#define ixPB1_PLL_RO_GLB_CTRL_REG0 0x14000
#define ixPB1_PLL_RO_GLB_OVRD_REG0 0x14010
#define ixPB1_RX_GLB_CTRL_REG0 0x16000
#define ixPB1_RX_GLB_CTRL_REG1 0x16004
#define ixPB1_RX_GLB_CTRL_REG2 0x16008
#define ixPB1_RX_GLB_CTRL_REG3 0x1600C
#define ixPB1_RX_GLB_CTRL_REG4 0x16010
#define ixPB1_RX_GLB_CTRL_REG5 0x16014
#define ixPB1_RX_GLB_CTRL_REG6 0x16018
#define ixPB1_RX_GLB_CTRL_REG7 0x1601C
#define ixPB1_RX_GLB_CTRL_REG8 0x16020
#define ixPB1_RX_GLB_OVRD_REG0 0x16030
#define ixPB1_RX_GLB_OVRD_REG1 0x16034
#define ixPB1_RX_GLB_SCI_STAT_OVRD_REG0 0x16028
#define ixPB1_RX_LANE0_CTRL_REG0 0x16440
#define ixPB1_RX_LANE0_SCI_STAT_OVRD_REG0 0x16448
#define ixPB1_RX_LANE10_CTRL_REG0 0x17500
#define ixPB1_RX_LANE10_SCI_STAT_OVRD_REG0 0x17508
#define ixPB1_RX_LANE11_CTRL_REG0 0x17600
#define ixPB1_RX_LANE11_SCI_STAT_OVRD_REG0 0x17608
#define ixPB1_RX_LANE12_CTRL_REG0 0x17840
#define ixPB1_RX_LANE12_SCI_STAT_OVRD_REG0 0x17848
#define ixPB1_RX_LANE13_CTRL_REG0 0x17880
#define ixPB1_RX_LANE13_SCI_STAT_OVRD_REG0 0x17888
#define ixPB1_RX_LANE14_CTRL_REG0 0x17900
#define ixPB1_RX_LANE14_SCI_STAT_OVRD_REG0 0x17908
#define ixPB1_RX_LANE15_CTRL_REG0 0x17A00
#define ixPB1_RX_LANE15_SCI_STAT_OVRD_REG0 0x17A08
#define ixPB1_RX_LANE1_CTRL_REG0 0x16480
#define ixPB1_RX_LANE1_SCI_STAT_OVRD_REG0 0x16488
#define ixPB1_RX_LANE2_CTRL_REG0 0x16500
#define ixPB1_RX_LANE2_SCI_STAT_OVRD_REG0 0x16508
#define ixPB1_RX_LANE3_CTRL_REG0 0x16600
#define ixPB1_RX_LANE3_SCI_STAT_OVRD_REG0 0x16608
#define ixPB1_RX_LANE4_CTRL_REG0 0x16800
#define ixPB1_RX_LANE4_SCI_STAT_OVRD_REG0 0x16848
#define ixPB1_RX_LANE5_CTRL_REG0 0x16880
#define ixPB1_RX_LANE5_SCI_STAT_OVRD_REG0 0x16888
#define ixPB1_RX_LANE6_CTRL_REG0 0x16900
#define ixPB1_RX_LANE6_SCI_STAT_OVRD_REG0 0x16908
#define ixPB1_RX_LANE7_CTRL_REG0 0x16A00
#define ixPB1_RX_LANE7_SCI_STAT_OVRD_REG0 0x16A08
#define ixPB1_RX_LANE8_CTRL_REG0 0x17440
#define ixPB1_RX_LANE8_SCI_STAT_OVRD_REG0 0x17448
#define ixPB1_RX_LANE9_CTRL_REG0 0x17480
#define ixPB1_RX_LANE9_SCI_STAT_OVRD_REG0 0x17488
#define ixPB1_STRAP_GLB_REG0 0x12020
#define ixPB1_STRAP_PLL_REG0 0x12030
#define ixPB1_STRAP_RX_REG0 0x12028
#define ixPB1_STRAP_RX_REG1 0x1202C
#define ixPB1_STRAP_TX_REG0 0x12024
#define ixPB1_TX_GLB_COEFF_ACCEPT_TABLE_REG0 0x18014
#define ixPB1_TX_GLB_COEFF_ACCEPT_TABLE_REG1 0x18018
#define ixPB1_TX_GLB_COEFF_ACCEPT_TABLE_REG2 0x1801C
#define ixPB1_TX_GLB_COEFF_ACCEPT_TABLE_REG3 0x18020
#define ixPB1_TX_GLB_CTRL_REG0 0x18000
#define ixPB1_TX_GLB_LANE_SKEW_CTRL 0x18004
#define ixPB1_TX_GLB_OVRD_REG0 0x18030
#define ixPB1_TX_GLB_OVRD_REG1 0x18034
#define ixPB1_TX_GLB_OVRD_REG2 0x18038
#define ixPB1_TX_GLB_OVRD_REG3 0x1803C
#define ixPB1_TX_GLB_OVRD_REG4 0x18040
#define ixPB1_TX_GLB_SCI_STAT_OVRD_REG0 0x18010
#define ixPB1_TX_LANE0_CTRL_REG0 0x18440
#define ixPB1_TX_LANE0_OVRD_REG0 0x18444
#define ixPB1_TX_LANE0_SCI_STAT_OVRD_REG0 0x18448
#define ixPB1_TX_LANE10_CTRL_REG0 0x19500
#define ixPB1_TX_LANE10_OVRD_REG0 0x19504
#define ixPB1_TX_LANE10_SCI_STAT_OVRD_REG0 0x19508
#define ixPB1_TX_LANE11_CTRL_REG0 0x19600
#define ixPB1_TX_LANE11_OVRD_REG0 0x19604
#define ixPB1_TX_LANE11_SCI_STAT_OVRD_REG0 0x19608
#define ixPB1_TX_LANE12_CTRL_REG0 0x19840
#define ixPB1_TX_LANE12_OVRD_REG0 0x19844
#define ixPB1_TX_LANE12_SCI_STAT_OVRD_REG0 0x19848
#define ixPB1_TX_LANE13_CTRL_REG0 0x19880
#define ixPB1_TX_LANE13_OVRD_REG0 0x19884
#define ixPB1_TX_LANE13_SCI_STAT_OVRD_REG0 0x19888
#define ixPB1_TX_LANE14_CTRL_REG0 0x19900
#define ixPB1_TX_LANE14_OVRD_REG0 0x19904
#define ixPB1_TX_LANE14_SCI_STAT_OVRD_REG0 0x19908
#define ixPB1_TX_LANE15_CTRL_REG0 0x19A00
#define ixPB1_TX_LANE15_OVRD_REG0 0x19A04
#define ixPB1_TX_LANE15_SCI_STAT_OVRD_REG0 0x19A08
#define ixPB1_TX_LANE1_CTRL_REG0 0x18480
#define ixPB1_TX_LANE1_OVRD_REG0 0x18484
#define ixPB1_TX_LANE1_SCI_STAT_OVRD_REG0 0x18488
#define ixPB1_TX_LANE2_CTRL_REG0 0x18500
#define ixPB1_TX_LANE2_OVRD_REG0 0x18504
#define ixPB1_TX_LANE2_SCI_STAT_OVRD_REG0 0x18508
#define ixPB1_TX_LANE3_CTRL_REG0 0x18600
#define ixPB1_TX_LANE3_OVRD_REG0 0x18604
#define ixPB1_TX_LANE3_SCI_STAT_OVRD_REG0 0x18608
#define ixPB1_TX_LANE4_CTRL_REG0 0x18840
#define ixPB1_TX_LANE4_OVRD_REG0 0x18844
#define ixPB1_TX_LANE4_SCI_STAT_OVRD_REG0 0x18848
#define ixPB1_TX_LANE5_CTRL_REG0 0x18880
#define ixPB1_TX_LANE5_OVRD_REG0 0x18884
#define ixPB1_TX_LANE5_SCI_STAT_OVRD_REG0 0x18888
#define ixPB1_TX_LANE6_CTRL_REG0 0x18900
#define ixPB1_TX_LANE6_OVRD_REG0 0x18904
#define ixPB1_TX_LANE6_SCI_STAT_OVRD_REG0 0x18908
#define ixPB1_TX_LANE7_CTRL_REG0 0x18A00
#define ixPB1_TX_LANE7_OVRD_REG0 0x18A04
#define ixPB1_TX_LANE7_SCI_STAT_OVRD_REG0 0x18A08
#define ixPB1_TX_LANE8_CTRL_REG0 0x19440
#define ixPB1_TX_LANE8_OVRD_REG0 0x19444
#define ixPB1_TX_LANE8_SCI_STAT_OVRD_REG0 0x19448
#define ixPB1_TX_LANE9_CTRL_REG0 0x19480
#define ixPB1_TX_LANE9_OVRD_REG0 0x19484
#define ixPB1_TX_LANE9_SCI_STAT_OVRD_REG0 0x19488
#define ixPCIE_BUS_CNTL 0x0021
#define ixPCIE_CFG_CNTL 0x003C
#define ixPCIE_CI_CNTL 0x0020
#define ixPCIE_CNTL 0x0010
#define ixPCIE_CNTL2 0x001C
#define ixPCIE_CONFIG_CNTL 0x0011
#define ixPCIE_DEBUG_CNTL 0x0012
#define ixPCIE_ERR_CNTL 0x006A
#define ixPCIE_F0_DPA_CAP 0x00E0
#define ixPCIE_F0_DPA_CNTL 0x00E5
#define ixPCIE_F0_DPA_LATENCY_INDICATOR 0x00E4
#define ixPCIE_F0_DPA_SUBSTATE_PWR_ALLOC_0 0x00E7
#define ixPCIE_F0_DPA_SUBSTATE_PWR_ALLOC_1 0x00E8
#define ixPCIE_F0_DPA_SUBSTATE_PWR_ALLOC_2 0x00E9
#define ixPCIE_F0_DPA_SUBSTATE_PWR_ALLOC_3 0x00EA
#define ixPCIE_F0_DPA_SUBSTATE_PWR_ALLOC_4 0x00EB
#define ixPCIE_F0_DPA_SUBSTATE_PWR_ALLOC_5 0x00EC
#define ixPCIE_F0_DPA_SUBSTATE_PWR_ALLOC_6 0x00ED
#define ixPCIE_F0_DPA_SUBSTATE_PWR_ALLOC_7 0x00EE
#define ixPCIE_FC_CPL 0x0062
#define ixPCIE_FC_NP 0x0061
#define ixPCIE_FC_P 0x0060
#define ixPCIE_HW_DEBUG 0x0002
#define ixPCIE_I2C_REG_ADDR_EXPAND 0x003A
#define ixPCIE_I2C_REG_DATA 0x003B
#define ixPCIE_INT_CNTL 0x001A
#define ixPCIE_INT_STATUS 0x001B
#define ixPCIE_LC_BEST_EQ_SETTINGS 0x00B9
#define ixPCIE_LC_BW_CHANGE_CNTL 0x00B2
#define ixPCIE_LC_CDR_CNTL 0x00B3
#define ixPCIE_LC_CNTL 0x00A0
#define ixPCIE_LC_CNTL2 0x00B1
#define ixPCIE_LC_CNTL3 0x00B5
#define ixPCIE_LC_CNTL4 0x00B6
#define ixPCIE_LC_CNTL5 0x00B7
#define ixPCIE_LC_FORCE_COEFF 0x00B8
#define ixPCIE_LC_FORCE_EQ_REQ_COEFF 0x00BA
#define ixPCIE_LC_LANE_CNTL 0x00B4
#define ixPCIE_LC_LINK_WIDTH_CNTL 0x00A2
#define ixPCIE_LC_N_FTS_CNTL 0x00A3
#define ixPCIE_LC_SPEED_CNTL 0x00A4
#define ixPCIE_LC_STATE0 0x00A5
#define ixPCIE_LC_STATE10 0x0026
#define ixPCIE_LC_STATE1 0x00A6
#define ixPCIE_LC_STATE11 0x0027
#define ixPCIE_LC_STATE2 0x00A7
#define ixPCIE_LC_STATE3 0x00A8
#define ixPCIE_LC_STATE4 0x00A9
#define ixPCIE_LC_STATE5 0x00AA
#define ixPCIE_LC_STATE6 0x0022
#define ixPCIE_LC_STATE7 0x0023
#define ixPCIE_LC_STATE8 0x0024
#define ixPCIE_LC_STATE9 0x0025
#define ixPCIE_LC_STATUS1 0x0028
#define ixPCIE_LC_STATUS2 0x0029
#define ixPCIE_LC_TRAINING_CNTL 0x00A1
#define ixPCIE_P_BUF_STATUS 0x0041
#define ixPCIE_P_CNTL 0x0040
#define ixPCIE_P_DECODER_STATUS 0x0042
#define ixPCIE_PERF_CNTL_EVENT0_PORT_SEL 0x0093
#define ixPCIE_PERF_CNTL_EVENT1_PORT_SEL 0x0094
#define ixPCIE_PERF_CNTL_MST_C_CLK 0x0087
#define ixPCIE_PERF_CNTL_MST_R_CLK 0x0084
#define ixPCIE_PERF_CNTL_SLV_NS_C_CLK 0x0090
#define ixPCIE_PERF_CNTL_SLV_R_CLK 0x008A
#define ixPCIE_PERF_CNTL_SLV_S_C_CLK 0x008D
#define ixPCIE_PERF_CNTL_TXCLK 0x0081
#define ixPCIE_PERF_CNTL_TXCLK2 0x0095
#define ixPCIE_PERF_COUNT0_MST_C_CLK 0x0088
#define ixPCIE_PERF_COUNT0_MST_R_CLK 0x0085
#define ixPCIE_PERF_COUNT0_SLV_NS_C_CLK 0x0091
#define ixPCIE_PERF_COUNT0_SLV_R_CLK 0x008B
#define ixPCIE_PERF_COUNT0_SLV_S_C_CLK 0x008E
#define ixPCIE_PERF_COUNT0_TXCLK 0x0082
#define ixPCIE_PERF_COUNT0_TXCLK2 0x0096
#define ixPCIE_PERF_COUNT1_MST_C_CLK 0x0089
#define ixPCIE_PERF_COUNT1_MST_R_CLK 0x0086
#define ixPCIE_PERF_COUNT1_SLV_NS_C_CLK 0x0092
#define ixPCIE_PERF_COUNT1_SLV_R_CLK 0x008C
#define ixPCIE_PERF_COUNT1_SLV_S_C_CLK 0x008F
#define ixPCIE_PERF_COUNT1_TXCLK 0x0083
#define ixPCIE_PERF_COUNT1_TXCLK2 0x0097
#define ixPCIE_PERF_COUNT_CNTL 0x0080
#define ixPCIEP_HW_DEBUG 0x0002
#define ixPCIE_P_MISC_STATUS 0x0043
#define ixPCIEP_PORT_CNTL 0x0010
#define ixPCIE_P_PORT_LANE_STATUS 0x0050
#define ixPCIE_PRBS_CLR 0x00C8
#define ixPCIE_PRBS_ERRCNT_0 0x00D0
#define ixPCIE_PRBS_ERRCNT_10 0x00DA
#define ixPCIE_PRBS_ERRCNT_1 0x00D1
#define ixPCIE_PRBS_ERRCNT_11 0x00DB
#define ixPCIE_PRBS_ERRCNT_12 0x00DC
#define ixPCIE_PRBS_ERRCNT_13 0x00DD
#define ixPCIE_PRBS_ERRCNT_14 0x00DE
#define ixPCIE_PRBS_ERRCNT_15 0x00DF
#define ixPCIE_PRBS_ERRCNT_2 0x00D2
#define ixPCIE_PRBS_ERRCNT_3 0x00D3
#define ixPCIE_PRBS_ERRCNT_4 0x00D4
#define ixPCIE_PRBS_ERRCNT_5 0x00D5
#define ixPCIE_PRBS_ERRCNT_6 0x00D6
#define ixPCIE_PRBS_ERRCNT_7 0x00D7
#define ixPCIE_PRBS_ERRCNT_8 0x00D8
#define ixPCIE_PRBS_ERRCNT_9 0x00D9
#define ixPCIE_PRBS_FREERUN 0x00CB
#define ixPCIE_PRBS_HI_BITCNT 0x00CF
#define ixPCIE_PRBS_LO_BITCNT 0x00CE
#define ixPCIE_PRBS_MISC 0x00CC
#define ixPCIE_PRBS_STATUS1 0x00C9
#define ixPCIE_PRBS_STATUS2 0x00CA
#define ixPCIE_PRBS_USER_PATTERN 0x00CD
#define ixPCIE_P_RCV_L0S_FTS_DET 0x0050
#define ixPCIEP_RESERVED 0x0000
#define ixPCIEP_SCRATCH 0x0001
#define ixPCIEP_STRAP_LC 0x00C0
#define ixPCIEP_STRAP_MISC 0x00C1
#define ixPCIE_RESERVED 0x0000
#define ixPCIE_RX_CNTL 0x0070
#define ixPCIE_RX_CNTL2 0x001D
#define ixPCIE_RX_CNTL3 0x0074
#define ixPCIE_RX_CREDITS_ALLOCATED_CPL 0x0082
#define ixPCIE_RX_CREDITS_ALLOCATED_NP 0x0081
#define ixPCIE_RX_CREDITS_ALLOCATED_P 0x0080
#define ixPCIE_RX_EXPECTED_SEQNUM 0x0071
#define ixPCIE_RX_LAST_TLP0 0x0031
#define ixPCIE_RX_LAST_TLP1 0x0032
#define ixPCIE_RX_LAST_TLP2 0x0033
#define ixPCIE_RX_LAST_TLP3 0x0034
#define ixPCIE_RX_NUM_NAK 0x000E
#define ixPCIE_RX_NUM_NAK_GENERATED 0x000F
#define ixPCIE_RX_VENDOR_SPECIFIC 0x0072
#define ixPCIE_SCRATCH 0x0001
#define ixPCIE_STRAP_F0 0x00B0
#define ixPCIE_STRAP_F1 0x00B1
#define ixPCIE_STRAP_F2 0x00B2
#define ixPCIE_STRAP_F3 0x00B3
#define ixPCIE_STRAP_F4 0x00B4
#define ixPCIE_STRAP_F5 0x00B5
#define ixPCIE_STRAP_F6 0x00B6
#define ixPCIE_STRAP_F7 0x00B7
#define ixPCIE_STRAP_I2C_BD 0x00C4
#define ixPCIE_STRAP_MISC 0x00C0
#define ixPCIE_STRAP_MISC2 0x00C1
#define ixPCIE_STRAP_PI 0x00C2
#define ixPCIE_TX_ACK_LATENCY_LIMIT 0x0026
#define ixPCIE_TX_CNTL 0x0020
#define ixPCIE_TX_CREDITS_ADVT_CPL 0x0032
#define ixPCIE_TX_CREDITS_ADVT_NP 0x0031
#define ixPCIE_TX_CREDITS_ADVT_P 0x0030
#define ixPCIE_TX_CREDITS_FCU_THRESHOLD 0x0037
#define ixPCIE_TX_CREDITS_INIT_CPL 0x0035
#define ixPCIE_TX_CREDITS_INIT_NP 0x0034
#define ixPCIE_TX_CREDITS_INIT_P 0x0033
#define ixPCIE_TX_CREDITS_STATUS 0x0036
#define ixPCIE_TX_LAST_TLP0 0x0035
#define ixPCIE_TX_LAST_TLP1 0x0036
#define ixPCIE_TX_LAST_TLP2 0x0037
#define ixPCIE_TX_LAST_TLP3 0x0038
#define ixPCIE_TX_REPLAY 0x0025
#define ixPCIE_TX_REQUESTER_ID 0x0021
#define ixPCIE_TX_REQUEST_NUM_CNTL 0x0023
#define ixPCIE_TX_SEQ 0x0024
#define ixPCIE_TX_VENDOR_SPECIFIC 0x0022
#define ixPCIE_WPR_CNTL 0x0030
#define mmBACO_CNTL 0x14E5
#define mmBF_ANA_ISO_CNTL 0x14C7
#define mmBIF_BACO_DEBUG 0x14DF
#define mmBIF_BACO_DEBUG_LATCH 0x14DC
#define mmBIF_BACO_MSIC 0x14DE
#define mmBIF_BUSNUM_CNTL1 0x1525
#define mmBIF_BUSNUM_CNTL2 0x152B
#define mmBIF_BUSNUM_LIST0 0x1526
#define mmBIF_BUSNUM_LIST1 0x1527
#define mmBIF_BUSY_DELAY_CNTR 0x1529
#define mmBIF_CLK_PDWN_DELAY_TIMER 0x151F
#define mmBIF_DEBUG_CNTL 0x151C
#define mmBIF_DEBUG_MUX 0x151D
#define mmBIF_DEBUG_OUT 0x151E
#define mmBIF_DEVFUNCNUM_LIST0 0x14E8
#define mmBIF_DEVFUNCNUM_LIST1 0x14E7
#define mmBIF_FB_EN 0x1524
#define mmBIF_FEATURES_CONTROL_MISC 0x14C2
#define mmBIF_PERFCOUNTER0_RESULT 0x152D
#define mmBIF_PERFCOUNTER1_RESULT 0x152E
#define mmBIF_PERFMON_CNTL 0x152C
#define mmBIF_PIF_TXCLK_SWITCH_TIMER 0x152F
#define mmBIF_RESET_EN 0x1511
#define mmBIF_SCRATCH0 0x150E
#define mmBIF_SCRATCH1 0x150F
#define mmBIF_SSA_DISP_LOWER 0x14D2
#define mmBIF_SSA_DISP_UPPER 0x14D3
#define mmBIF_SSA_GFX0_LOWER 0x14CA
#define mmBIF_SSA_GFX0_UPPER 0x14CB
#define mmBIF_SSA_GFX1_LOWER 0x14CC
#define mmBIF_SSA_GFX1_UPPER 0x14CD
#define mmBIF_SSA_GFX2_LOWER 0x14CE
#define mmBIF_SSA_GFX2_UPPER 0x14CF
#define mmBIF_SSA_GFX3_LOWER 0x14D0
#define mmBIF_SSA_GFX3_UPPER 0x14D1
#define mmBIF_SSA_MC_LOWER 0x14D4
#define mmBIF_SSA_MC_UPPER 0x14D5
#define mmBIF_SSA_PWR_STATUS 0x14C8
#define mmBIF_XDMA_HI 0x14C1
#define mmBIF_XDMA_LO 0x14C0
#define mmBIOS_SCRATCH_0 0x05C9
#define mmBIOS_SCRATCH_10 0x05D3
#define mmBIOS_SCRATCH_1 0x05CA
#define mmBIOS_SCRATCH_11 0x05D4
#define mmBIOS_SCRATCH_12 0x05D5
#define mmBIOS_SCRATCH_13 0x05D6
#define mmBIOS_SCRATCH_14 0x05D7
#define mmBIOS_SCRATCH_15 0x05D8
#define mmBIOS_SCRATCH_2 0x05CB
#define mmBIOS_SCRATCH_3 0x05CC
#define mmBIOS_SCRATCH_4 0x05CD
#define mmBIOS_SCRATCH_5 0x05CE
#define mmBIOS_SCRATCH_6 0x05CF
#define mmBIOS_SCRATCH_7 0x05D0
#define mmBIOS_SCRATCH_8 0x05D1
#define mmBIOS_SCRATCH_9 0x05D2
#define mmBUS_CNTL 0x1508
#define mmCAPTURE_HOST_BUSNUM 0x153C
#define mmCLKREQB_PAD_CNTL 0x1521
#define mmCONFIG_APER_SIZE 0x150C
#define mmCONFIG_CNTL 0x1509
#define mmCONFIG_F0_BASE 0x150B
#define mmCONFIG_MEMSIZE 0x150A
#define mmCONFIG_REG_APER_SIZE 0x150D
#define mmHDP_MEM_COHERENCY_FLUSH_CNTL 0x1520
#define mmHDP_REG_COHERENCY_FLUSH_CNTL 0x1528
#define mmHOST_BUSNUM 0x153D
#define mmHW_DEBUG 0x1515
#define mmIMPCTL_RESET 0x14F5
#define mmINTERRUPT_CNTL 0x151A
#define mmINTERRUPT_CNTL2 0x151B
#define mmMASTER_CREDIT_CNTL 0x1516
#define mmMM_CFGREGS_CNTL 0x1513
#define mmMM_DATA 0x0001
#define mmMM_INDEX 0x0000
#define mmMM_INDEX_HI 0x0006
#define mmNEW_REFCLKB_TIMER 0x14EA
#define mmNEW_REFCLKB_TIMER_1 0x14E9
#define mmPCIE_DATA 0x000D
#define mmPCIE_INDEX 0x000C
#define mmPEER0_FB_OFFSET_HI 0x14F3
#define mmPEER0_FB_OFFSET_LO 0x14F2
#define mmPEER1_FB_OFFSET_HI 0x14F1
#define mmPEER1_FB_OFFSET_LO 0x14F0
#define mmPEER2_FB_OFFSET_HI 0x14EF
#define mmPEER2_FB_OFFSET_LO 0x14EE
#define mmPEER3_FB_OFFSET_HI 0x14ED
#define mmPEER3_FB_OFFSET_LO 0x14EC
#define mmPEER_REG_RANGE0 0x153E
#define mmPEER_REG_RANGE1 0x153F
#define mmSLAVE_HANG_ERROR 0x153B
#define mmSLAVE_HANG_PROTECTION_CNTL 0x1536
#define mmSLAVE_REQ_CREDIT_CNTL 0x1517
#define mmSMBCLK_PAD_CNTL 0x1523
#define mmSMBDAT_PAD_CNTL 0x1522
#define mmSMBUS_BACO_DUMMY 0x14C6

#endif