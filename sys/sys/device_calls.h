/*	$NetBSD: device_calls.h,v 1.1 2021/09/15 17:33:08 thorpej Exp $	*/

/*
 * THIS FILE IS AUTOMATICALLY GENERATED.  DO NOT EDIT.
 *
 * generated from:
 *	NetBSD: device_calls,v 1.1 2021/09/15 17:26:06 thorpej Exp
 */

/*-
 * Copyright (c) 2021 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Jason R. Thorpe.
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

/*
 * Device calls used by the device autoconfiguration subsystem
 */

#ifndef _DEVICE_CALLS_H_
#define _DEVICE_CALLS_H_

#include <sys/device.h>

/*
 * device-enumerate-children
 *
 * Enumerates the direct children of a device, invoking the callback for
 * each one.  The callback is passed the devhandle_t corresponding to the
 * child device, as well as a user-supplied argument.  If the callback
 * returns true, then enumeration continues.  If the callback returns false,
 * enumeration is stopped.
 */
struct device_enumerate_children_args {
	bool	(*callback)(device_t, devhandle_t, void *);
	void *	callback_arg;
};

union device_enumerate_children_binding {
	struct device_call_generic generic;
	struct {
		const char *name;
		struct device_enumerate_children_args *args;
	} binding;
};

#define DEVICE_ENUMERATE_CHILDREN_STR "device-enumerate-children"

#define DEVICE_ENUMERATE_CHILDREN(_args_) \
	&((const union device_enumerate_children_binding){ \
		.binding.name = "device-enumerate-children", \
		.binding.args = (_args_), \
	})

#endif /* _DEVICE_CALLS_H_ */
