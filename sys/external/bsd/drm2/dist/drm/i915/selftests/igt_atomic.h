/*	$NetBSD: igt_atomic.h,v 1.2 2021/12/18 23:45:31 riastradh Exp $	*/

/* SPDX-License-Identifier: MIT */
/*
 * Copyright © 2018 Intel Corporation
 */

#ifndef IGT_ATOMIC_H
#define IGT_ATOMIC_H

struct igt_atomic_section {
	const char *name;
	void (*critical_section_begin)(void);
	void (*critical_section_end)(void);
};

extern const struct igt_atomic_section igt_atomic_phases[];

#endif /* IGT_ATOMIC_H */
