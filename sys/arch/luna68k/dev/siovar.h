/* $NetBSD: siovar.h,v 1.9 2021/09/25 15:18:38 tsutsui Exp $ */

/*-
 * Copyright (c) 2000 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Tohru Nishimura.
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

struct sio_attach_args {
	int channel;
	int hwflags;
};

struct sioreg {
	volatile uint8_t sio_data;
	uint8_t	pad0;
	volatile uint8_t sio_cmd;
	uint8_t pad1;
#define sio_stat sio_cmd
};

struct sio_softc {
	device_t sc_dev;
	struct sioreg *sc_ctl;
	struct {
		void (*ih_func)(void *);
		void *ih_arg;
	} sc_intrhand[2];
};

static inline uint16_t getsiocsr(struct sioreg *);
static inline void setsioreg(struct sioreg *, int, int);

static inline int siogetc(struct sioreg *);
static inline void sioputc(struct sioreg *, int);

static inline uint16_t
getsiocsr(struct sioreg *sio)
{
	uint16_t val;

	val = sio->sio_stat << 8;
	sio->sio_cmd = RR1;
	val |= sio->sio_stat;

	return val;
}

static inline void
setsioreg(struct sioreg *sio, int regno, int val)
{

	if (regno != WR0)
		sio->sio_cmd = regno;
	sio->sio_cmd = val;
}

static inline int
siogetc(struct sioreg *sio)
{
	int s, c;

	s = splhigh();
	while ((getsiocsr(sio) & RR_RXRDY) == 0)
		continue;
	c = sio->sio_data;
	splx(s);

	return c;
}

static inline void
sioputc(struct sioreg *sio, int c)
{
	int s;

	s = splhigh();
	while ((getsiocsr(sio) & RR_TXRDY) == 0)
		continue;
	sio->sio_cmd = WR0_RSTPEND;
	sio->sio_data = c;
	splx(s);
}
