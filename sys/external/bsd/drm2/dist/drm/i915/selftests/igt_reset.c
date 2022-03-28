/*	$NetBSD: igt_reset.c,v 1.2 2021/12/18 23:45:31 riastradh Exp $	*/

/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright © 2018 Intel Corporation
 */

#include <sys/cdefs.h>
__KERNEL_RCSID(0, "$NetBSD: igt_reset.c,v 1.2 2021/12/18 23:45:31 riastradh Exp $");

#include "igt_reset.h"

#include "gt/intel_engine.h"
#include "gt/intel_gt.h"

#include "../i915_drv.h"

void igt_global_reset_lock(struct intel_gt *gt)
{
	struct intel_engine_cs *engine;
	enum intel_engine_id id;

	pr_debug("%s: current gpu_error=%08lx\n", __func__, gt->reset.flags);

	while (test_and_set_bit(I915_RESET_BACKOFF, &gt->reset.flags))
		wait_event(gt->reset.queue,
			   !test_bit(I915_RESET_BACKOFF, &gt->reset.flags));

	for_each_engine(engine, gt, id) {
		while (test_and_set_bit(I915_RESET_ENGINE + id,
					&gt->reset.flags))
			wait_on_bit(&gt->reset.flags, I915_RESET_ENGINE + id,
				    TASK_UNINTERRUPTIBLE);
	}
}

void igt_global_reset_unlock(struct intel_gt *gt)
{
	struct intel_engine_cs *engine;
	enum intel_engine_id id;

	for_each_engine(engine, gt, id)
		clear_bit(I915_RESET_ENGINE + id, &gt->reset.flags);

	clear_bit(I915_RESET_BACKOFF, &gt->reset.flags);
	wake_up_all(&gt->reset.queue);
}

bool igt_force_reset(struct intel_gt *gt)
{
	intel_gt_set_wedged(gt);
	intel_gt_reset(gt, 0, NULL);

	return !intel_gt_is_wedged(gt);
}