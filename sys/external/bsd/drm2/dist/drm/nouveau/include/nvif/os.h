/*	$NetBSD: os.h,v 1.8 2021/12/19 10:47:30 riastradh Exp $	*/

/* SPDX-License-Identifier: MIT */
#ifndef __NOUVEAU_OS_H__
#define __NOUVEAU_OS_H__

#include <linux/types.h>
#include <linux/slab.h>
#include <linux/mutex.h>
#include <linux/pci.h>
#include <linux/platform_device.h>
#include <linux/printk.h>
#include <linux/bitops.h>
#include <linux/firmware.h>
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/i2c-algo-bit.h>
#include <linux/delay.h>
#include <linux/io-mapping.h>
#include <linux/acpi.h>
#include <linux/vmalloc.h>
#include <linux/dmi.h>
#include <linux/reboot.h>
#include <linux/interrupt.h>
#include <linux/log2.h>
#include <linux/pm_runtime.h>
#include <linux/power_supply.h>
#include <linux/clk.h>
#include <linux/regulator/consumer.h>
#include <linux/agp_backend.h>
#include <linux/reset.h>
#include <linux/iommu.h>
#include <linux/of_device.h>
#include <linux/atomic.h>
#include <linux/bug.h>
#include <linux/kernel.h>
#include <linux/kref.h>
#include <linux/list.h>
#include <linux/math64.h>
#include <linux/errno.h>
#include <linux/workqueue.h>
#include <linux/device.h>
#include <linux/ktime.h>
#include <linux/err.h>
#include <linux/bitmap.h>
#include <linux/jiffies.h>
#include <linux/io.h>

#include <asm/barrier.h>
#include <asm/byteorder.h>
#include <asm/io.h>
#include <asm/unaligned.h>

#include <soc/tegra/fuse.h>
#include <soc/tegra/pmc.h>

#ifdef __NetBSD__
#include <drm/drm_irq_netbsd.h>
#include <drm/drm_wait_netbsd.h>
#endif

#endif
