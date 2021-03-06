/*	$NetBSD: tracepoint.h,v 1.4 2021/12/19 12:22:10 riastradh Exp $	*/

/*-
 * Copyright (c) 2020 The NetBSD Foundation, Inc.
 * All rights reserved.
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

#ifndef _LINUX_TRACEPOINT_H_
#define _LINUX_TRACEPOINT_H_

#include <sys/types.h>

#define	TRACE_EVENT(NAME, PROTOTYPE, ARGS, FIELDS, TRACE, PRINT)	      \
	static inline void trace_##NAME PROTOTYPE {}

#define	TP_PROTO(ARGS...)	(ARGS)

#define	DECLARE_EVENT_CLASS(NAME, PROTOTYPE, ARGS, FIELDS, TRACE, PRINT)      \
	/* nothing */

#define	DEFINE_EVENT(CLASS, NAME, PROTOTYPE, ARGS)			      \
	static inline void trace_##NAME PROTOTYPE {}			      \
	static inline bool trace_##NAME##_enabled(void) { return false; }

#endif	/* _LINUX_TRACEPOINT_H_ */
