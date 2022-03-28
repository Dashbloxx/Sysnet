/*
 * Copyright (c) 1988 University of Utah.
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * from: Utah $Hdr: iteioctl.h 1.1 90/07/09$
 *
 *	@(#)iteioctl.h	7.2 (Berkeley) 11/4/90
 *	$NetBSD: iteioctl.h,v 1.10 2021/11/01 21:28:02 andvar Exp $
 */

#ifndef _X68K_ITEIOCTL_H_
#define _X68K_ITEIOCTL_H_

#include <sys/ioccom.h>
#include <machine/kbdmap.h>

struct itewinsize {
	int x;			/* leftedge offset to the right */
	int y;			/* topedge offset down */
	u_int width;		/* width of ite display */
	u_int height;		/* height of ite display */
	u_int depth;		/* depth of ite display */
};

struct iterepeat {
	int start;		/* number of 100/s before repeat start */
	int next;		/* number of 100/s before next repeat */
};
#define ITEMINREPEAT	5	/* minimum number of 100/s for key repeat */

#define ITEIOCSKMAP	_IOW('Z',0x70, struct kbdmap)
#define ITEIOCGKMAP	_IOR('Z',0x71, struct kbdmap)
#ifdef notyet		/* could be implemented... */
#define ITEIOCGWINSZ	_IOR('Z',0x72, struct itewinsize)
#define ITEIOCSWINSZ	_IOW('Z',0x73, struct itewinsize)
#define ITEIOCDSPWIN	_IO('Z', 0x74)
#define ITEIOCREMWIN	_IO('Z', 0x75)
#endif
#define ITEIOCGREPT	_IOR('Z', 0x78, struct iterepeat)
#define ITEIOCSREPT	_IOW('Z', 0x79, struct iterepeat)

#ifdef notyet
#define ITESWITCH	_IOW('Z',0x69, int)	/* XXX */
#endif

#define ITELOADFONT	_IOW('Z',0x80, unsigned char [4096])

#define ITETVCTRL	_IOW('Z',0x81, unsigned char)
#define TVC_VOLUP	0x01
#define TVC_VOLDOWN	0x02
#define TVC_VOLNORM	0x03
#define TVC_CHCALL	0x04 /* toggle channel call */
#define TVC_RESET	0x05
#define TVC_VOLMUTE	0x06
#define TVC_POWERON	0x07
#define TVC_RGBTV	0x08 /* toggle rgb/TV */
#define TVC_EXTTV	0x09 /* toggle video/TV */
#define TVC_OVERSCAN	0x09 /* toggle normal/overscan (RGB) */
#define TVC_CONTNORM	0x0a
#define TVC_CHNLUP	0x0b
#define TVC_CHNLDOWN	0x0c
#define TVC_POWEROFF	0x0d
#define TVC_POWER	0x0e
#define TVC_TSUPER1	0x0f /* toggle super */
#define TVC_CHAN1	(0x0f + 1)
#define TVC_CHAN2	(0x0f + 2)
#define TVC_CHAN3	(0x0f + 3)
#define TVC_CHAN4	(0x0f + 4)
#define TVC_CHAN5	(0x0f + 5)
#define TVC_CHAN6	(0x0f + 6)
#define TVC_CHAN7	(0x0f + 7)
#define TVC_CHAN8	(0x0f + 8)
#define TVC_CHAN9	(0x0f + 9)
#define TVC_CHAN10	(0x0f + 10)
#define TVC_CHAN11	(0x0f + 11)
#define TVC_CHAN12	(0x0f + 12)
#define TVC_TV		(0x1c)
#define TVC_RGB		(0x1d)
#define TVC_SUPER1	(0x1e)
#define TVC_SUPER2	(0x1f)
#define TVC_PWON	(0x20) /* optional bits */

#endif