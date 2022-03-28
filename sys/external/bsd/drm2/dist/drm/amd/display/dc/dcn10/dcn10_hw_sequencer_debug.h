/*	$NetBSD: dcn10_hw_sequencer_debug.h,v 1.2 2021/12/18 23:45:03 riastradh Exp $	*/

/*
 * Copyright 2016 Advanced Micro Devices, Inc.
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

#ifndef __DC_HWSS_DCN10_DEBUG_H__
#define __DC_HWSS_DCN10_DEBUG_H__

#include "core_types.h"

struct dc;

void dcn10_clear_status_bits(struct dc *dc, unsigned int mask);

void dcn10_log_hw_state(struct dc *dc,
		struct dc_log_buffer_ctx *log_ctx);

void dcn10_get_hw_state(struct dc *dc,
		char *pBuf,
		unsigned int bufSize,
		unsigned int mask);

#endif /* __DC_HWSS_DCN10_DEBUG_H__ */