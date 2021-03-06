/*	$NetBSD: io.h,v 1.8 2021/12/19 12:30:05 riastradh Exp $	*/

/*-
 * Copyright (c) 2013 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Taylor R. Campbell.
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

#ifndef _LINUX_IO_H_
#define _LINUX_IO_H_

#include <linux/types.h>
#include <linux/err.h>

#include <asm/io.h>

#define	arch_phys_wc_add		linux_arch_phys_wc_add
#define	arch_phys_wc_del		linux_arch_phys_wc_del
#define	arch_phys_wc_index		linux_arch_phys_wc_index
#define	arch_io_reserve_memtype_wc	linux_arch_io_reserve_memtype_wc
#define	arch_io_free_memtype_wc		linux_arch_io_free_memtype_wc

int	linux_writecomb_init(void);
void	linux_writecomb_fini(void);

int	arch_phys_wc_add(unsigned long, unsigned long);
void	arch_phys_wc_del(int);
int	arch_phys_wc_index(int);

int	arch_io_reserve_memtype_wc(resource_size_t, resource_size_t);
void	arch_io_free_memtype_wc(resource_size_t, resource_size_t);

#endif  /* _LINUX_IO_H_ */
