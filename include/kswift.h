/*
+----------------------------------------------------------------------------+
| kswift                                                                     |
| Copyright (c) 2011 Sam de Freyssinet <sam@def.reyssi.net>                  |
| All rights reserved.                                                       |
+----------------------------------------------------------------------------+
| Permission to use, copy, modify, and/or distribute this software for any   |
| purpose with or without fee is hereby granted, provided that the above     |
| copyright notice and this permission notice appear in all copies.          |
+----------------------------------------------------------------------------+
| THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES   |
| WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF           |
| MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR    |
| ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES     |
| WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN      |
| ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR |
| IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.                |
+----------------------------------------------------------------------------+
*/

#include <errno.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

struct kswift_options
{
	/* Hostname of php-fpm server */
	char *fcgi_host;

	/* Port number of php-fpm server */
	uint16_t fcgi_port;

	/* Message queue to use */
	char *queue;

	/* Message server host */
	char *msg_host;

	/* Message server port */
	uint16_t msg_port;

	/* Message server register name */
	char *msg_register;

	/* Number of request threads */
	uint16_t kswift_threads;
};

