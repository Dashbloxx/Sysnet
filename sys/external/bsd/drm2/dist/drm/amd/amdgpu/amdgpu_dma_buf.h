/*	$NetBSD: amdgpu_dma_buf.h,v 1.4 2021/12/19 12:01:48 riastradh Exp $	*/

/*
 * Copyright 2019 Advanced Micro Devices, Inc.
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
 */
#ifndef __AMDGPU_DMA_BUF_H__
#define __AMDGPU_DMA_BUF_H__

#include <drm/drm_gem.h>

struct dma_buf *amdgpu_gem_prime_export(struct drm_gem_object *gobj,
					int flags);
struct drm_gem_object *amdgpu_gem_prime_import(struct drm_device *dev,
					    struct dma_buf *dma_buf);
void *amdgpu_gem_prime_vmap(struct drm_gem_object *obj);
void amdgpu_gem_prime_vunmap(struct drm_gem_object *obj, void *vaddr);
#ifdef __NetBSD__
int amdgpu_gem_prime_mmap(struct drm_gem_object *, off_t *, size_t, int,
    int *, int *, struct uvm_object **, int *);
#else
int amdgpu_gem_prime_mmap(struct drm_gem_object *obj,
			  struct vm_area_struct *vma);
#endif

extern const struct dma_buf_ops amdgpu_dmabuf_ops;

#endif
