/*	$NetBSD: linux32_signal.h,v 1.1 2021/11/25 03:08:04 ryo Exp $	*/

/*-
 * Copyright (c) 2021 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Ryo Shimizu.
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

#ifndef _AARCH64_LINUX32_SIGNAL_H_
#define _AARCH64_LINUX32_SIGNAL_H_

#define native_to_linux32_signo native_to_linux_signo
#define linux32_to_native_signo linux_to_native_signo

typedef netbsd32_pointer_t	linux32_handlerp_t;
typedef netbsd32_pointer_t	linux32_restorer_t;
typedef netbsd32_pointer_t	linux32_siginfop_t;
typedef netbsd32_pointer_t	linux32_ucontextp_t;
typedef netbsd32_pointer_t	linux32_sigcontextp_t;
typedef netbsd32_pointer_t	linux32_fpstatep_t;
typedef u_int32_t		linux32_old_sigset_t;

#define LINUX32__NSIG		64
#define LINUX32__NSIG_BPW	32
#define LINUX32__NSIG_WORDS	(LINUX32__NSIG / LINUX32__NSIG_BPW)

#define LINUX32_SIG_BLOCK	0
#define LINUX32_SIG_UNBLOCK	1
#define LINUX32_SIG_SETMASK	2

#define LINUX32_SA_NOCLDSTOP	0x00000001
#define LINUX32_SA_NOCLDWAIT	0x00000002
#define LINUX32_SA_SIGINFO	0x00000004
#define LINUX32_SA_ONSTACK	0x08000000
#define LINUX32_SA_RESTART	0x10000000
#define LINUX32_SA_INTERRUPT	0x20000000
#define LINUX32_SA_NOMASK	0x40000000
#define LINUX32_SA_ONESHOT	0x80000000
#define LINUX32_SA_ALLBITS	0xf8000007

#define LINUX32_SS_ONSTACK	1
#define LINUX32_SS_DISABLE	2

#define LINUX32_SIGILL		LINUX_SIGILL
#define LINUX32_SIGFPE		LINUX_SIGFPE
#define LINUX32_SIGSEGV		LINUX_SIGSEGV
#define LINUX32_SIGBUS		LINUX_SIGBUS
#define LINUX32_SIGTRAP		LINUX_SIGTRAP
#define LINUX32_SIGCHLD		LINUX_SIGCHLD
#define LINUX32_SIGIO		LINUX_SIGIO
#define LINUX32_SIGALRM		LINUX_SIGALRM
#define LINUX32_SIGRTMIN	LINUX_SIGRTMIN

typedef struct {
	uint32_t sig[LINUX32__NSIG_WORDS];
} linux32_sigset_t;

struct linux32_sigaction {
	linux32_handlerp_t linux_sa_handler;
	int linux_sa_flags;
	linux32_sigset_t linux_sa_mask;
	linux32_restorer_t linux_sa_restorer;
};

typedef struct linux32_sigaltstack {
	netbsd32_voidp ss_sp;
	int ss_flags;
	netbsd32_size_t ss_size;
} linux32_stack_t;

#endif /* _AARCH64_LINUX32_SIGNAL_H_ */
