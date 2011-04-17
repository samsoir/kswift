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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

typedef enum
{
	KSWIFT_DRIVER_GEARMAN=0,
	KSWIFT_DRIVER_ZEROMQ=1
} kswift_driver;

struct kswift_options
{
	/* Hostname of php-fpm server */
	char *fpm_host;

	/* Port number of php-fpm server */
	int fpm_port;

	/* Message driver to use */
	enum kswift_dirver *driver;

	/* Message server host */
	char *msg_host;

	/* Message server port */
	int msg_port;

	/* Message server register name */
	char *msg_register;

	/* Number of request threads */
	int kswift_threads;
};