/*	$NetBSD: dmub_psr.h,v 1.2 2021/12/18 23:45:02 riastradh Exp $	*/

/*
 * Copyright 2012-16 Advanced Micro Devices, Inc.
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
 * Authors: AMD
 *
 */

#ifndef _DMUB_PSR_H_
#define _DMUB_PSR_H_

#include "os_types.h"

struct dmub_psr {
	struct dc_context *ctx;
	const struct dmub_psr_funcs *funcs;
};

struct dmub_psr_funcs {
	void (*set_psr_enable)(struct dmub_psr *dmub, bool enable);
	bool (*setup_psr)(struct dmub_psr *dmub, struct dc_link *link, struct psr_context *psr_context);
	void (*get_psr_state)(uint32_t *psr_state);
	void (*set_psr_level)(struct dmub_psr *dmub, uint16_t psr_level);
};

struct dmub_psr *dmub_psr_create(struct dc_context *ctx);
void dmub_psr_destroy(struct dmub_psr **dmub);


#endif /* _DCE_DMUB_H_ */
