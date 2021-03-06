/*-
 * Copyright (c) 2006 Verdens Gang AS
 * Copyright (c) 2006-2011 Varnish Software AS
 * All rights reserved.
 *
 * Author: Dag-Erling Smørgrav <des@des.no>
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
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include "config.h"

#ifndef HAVE_SRANDOMDEV

#include <sys/time.h>

#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "compat/srandomdev.h"

static int
trydev(const char *fn, unsigned long *seed)
{
	int fd;
	ssize_t sz;

	fd = open(fn, O_RDONLY);
	if (fd < 0)
		return (-1);
	sz = read(fd, seed, sizeof *seed);
	(void)close(fd);
	if (sz != sizeof *seed)
		return (-1);
	return (0);
}

void
srandomdev(void)
{
	struct timeval tv;
	unsigned long seed;

	if (trydev("/dev/urandom", &seed)) {
		if (trydev("/dev/random", &seed)) {
			gettimeofday(&tv, NULL);
			seed = (getpid() << 16) ^ tv.tv_sec ^ tv.tv_usec;
		}
	}
	srandom(seed);
}
#endif
