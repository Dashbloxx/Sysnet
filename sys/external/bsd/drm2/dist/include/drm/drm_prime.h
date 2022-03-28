/*	$NetBSD: drm_prime.h,v 1.7 2021/12/19 11:33:30 riastradh Exp $	*/

/*
 * Copyright © 2012 Red Hat
 * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.
 * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.
 * Copyright (c) 2009-2010, Code Aurora Forum.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Authors:
 *      Dave Airlie <airlied@redhat.com>
 *      Rob Clark <rob.clark@linaro.org>
 *
 */

#ifndef __DRM_PRIME_H__
#define __DRM_PRIME_H__

#include <linux/mutex.h>
#include <linux/rbtree.h>
#include <linux/scatterlist.h>

/**
 * struct drm_prime_file_private - per-file tracking for PRIME
 *
 * This just contains the internal &struct dma_buf and handle caches for each
 * &struct drm_file used by the PRIME core code.
 */
struct drm_prime_file_private {
/* private: */
	struct mutex lock;
	struct rb_root dmabufs;
	struct rb_root handles;
};

struct device;

struct dma_buf_export_info;
struct dma_buf;
struct dma_buf_attachment;

enum dma_data_direction;

struct drm_device;
struct drm_gem_object;
struct drm_file;

/* core prime functions */
struct dma_buf *drm_gem_dmabuf_export(struct drm_device *dev,
				      struct dma_buf_export_info *exp_info);
void drm_gem_dmabuf_release(struct dma_buf *dma_buf);

int drm_gem_prime_fd_to_handle(struct drm_device *dev,
			       struct drm_file *file_priv, int prime_fd, uint32_t *handle);
int drm_gem_prime_handle_to_fd(struct drm_device *dev,
			       struct drm_file *file_priv, uint32_t handle, uint32_t flags,
			       int *prime_fd);

/* helper functions for exporting */
int drm_gem_map_attach(struct dma_buf *dma_buf,
		       struct dma_buf_attachment *attach);
void drm_gem_map_detach(struct dma_buf *dma_buf,
			struct dma_buf_attachment *attach);
struct sg_table *drm_gem_map_dma_buf(struct dma_buf_attachment *attach,
				     enum dma_data_direction dir);
void drm_gem_unmap_dma_buf(struct dma_buf_attachment *attach,
			   struct sg_table *sgt,
			   enum dma_data_direction dir);
void *drm_gem_dmabuf_vmap(struct dma_buf *dma_buf);
void drm_gem_dmabuf_vunmap(struct dma_buf *dma_buf, void *vaddr);

#ifdef __NetBSD__
int drm_gem_prime_mmap(struct drm_gem_object *, off_t *, size_t, int, int *,
    int *, struct uvm_object **, int *);
int drm_gem_dmabuf_mmap(struct dma_buf *, off_t *, size_t, int, int *,
    int *, struct uvm_object **, int *);
#else
int drm_gem_prime_mmap(struct drm_gem_object *obj, struct vm_area_struct *vma);
int drm_gem_dmabuf_mmap(struct dma_buf *dma_buf, struct vm_area_struct *vma);
#endif

struct sg_table *drm_prime_pages_to_sg(struct page **pages, unsigned int nr_pages);
struct dma_buf *drm_gem_prime_export(struct drm_gem_object *obj,
				     int flags);

/* helper functions for importing */
#ifdef __NetBSD__
struct drm_gem_object *drm_gem_prime_import_dev(struct drm_device *dev,
						struct dma_buf *dma_buf,
						bus_dma_tag_t attach_dev);
#else
struct drm_gem_object *drm_gem_prime_import_dev(struct drm_device *dev,
						struct dma_buf *dma_buf,
						struct device *attach_dev);
#endif
struct drm_gem_object *drm_gem_prime_import(struct drm_device *dev,
					    struct dma_buf *dma_buf);

void drm_prime_gem_destroy(struct drm_gem_object *obj, struct sg_table *sg);

#ifdef __NetBSD__
extern struct sg_table *drm_prime_bus_dmamem_to_sg(bus_dma_tag_t, const bus_dma_segment_t *, int);
extern int drm_prime_sg_to_bus_dmamem(bus_dma_tag_t, bus_dma_segment_t *, int, int *, const struct sg_table *);
extern int drm_prime_bus_dmamap_load_sgt(bus_dma_tag_t, bus_dmamap_t, struct sg_table *);
extern bus_size_t drm_prime_sg_size(struct sg_table *);
extern void drm_prime_sg_free(struct sg_table *);
extern bool drm_prime_sg_importable(bus_dma_tag_t, struct sg_table *);
#else
int drm_prime_sg_to_page_addr_arrays(struct sg_table *sgt, struct page **pages,
				     dma_addr_t *addrs, int max_pages);
#endif


#endif /* __DRM_PRIME_H__ */