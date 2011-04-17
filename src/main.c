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

#include "kswift.h"

#define KSWIFT_MAX_THREADS  30

/*
Show the help text for Gerphast
*/
static void kswift_show_help (const char *d)
{

	fprintf(stderr, "Usage: %s [OPTIONS]\n", d);
	fprintf(stderr, " -h <host>     Hostname or IP of php-fpm server\n");
	fprintf(stderr, " -p <port>     Port number of php-fpm server\n");
	fprintf(stderr, " -d <driver>   Driver to use (gearman, zmq)\n");
	fprintf(stderr, " -m <host>     Hostname/IP address of message server\n");
	fprintf(stderr, " -P <port>     Port number of message server\n");
	fprintf(stderr, " -f <handle>   Message queue handle\n");
	fprintf(stderr, " -n <number>   Number of kswift request threads\n");

}

/*
Main
*/
int main (int argc, char **argv)
{

	struct kswift_options options, *poptions;
	int c, runner_count;
	kswift_driver driver;

	poptions = &options;

	/* Initialise php-fpm and gearman defaults */
	poptions->fpm_host = "127.0.0.1";
	poptions->fpm_port = 9000;
	poptions->msg_host = "127.0.0.1";
	poptions->msg_port = 4730;
	poptions->msg_register  = "kswift_request_thread";

	/* Initialise request runners default */
	poptions->kswift_threads = 10;

	if (argc == 1)
	{
		kswift_show_help(argv[0]);
		exit(1);
	}

	// Get the arguments
	while ((c = getopt(argc, argv, "h:p:d:m:P:f:n:")) != -1 )
	{
		switch (c)
		{
			case 'h':
				poptions->fpm_host = optarg;
				printf(" DEBUG  php-fpm host set to: %s\n", poptions->fpm_host);
			break;
			case 'p':
				poptions->fpm_port = atoi(optarg);
				printf(" DEBUG  php-fpm port set to: %i\n", poptions->fpm_port);
			break;
			case 'd':
				

//				poptions->driver = optarg;
//				printf(" DEBUG  driver set to: %s\n", poptions->driver);
			break;
			case 'm':
				poptions->msg_host = optarg;
				printf(" DEBUG  message server host set to: %s\n", 
					poptions->msg_host);
			break;
			case 'P':
				poptions->msg_port = atoi(optarg);
				printf(" DEBUG  message server port set to: %i\n", 
					poptions->msg_port);
			break;
			case 'f':
				poptions->msg_register = optarg;
				printf(" DEBUG  callback function set: %s\n", 
					poptions->msg_register);
			break;
			case 'n':
				runner_count = atoi(optarg);
				if (runner_count > KSWIFT_MAX_THREADS)
				{
					runner_count = KSWIFT_MAX_THREADS;
				}
				else if (runner_count < 0)
				{
					runner_count = 1;
				}
				poptions->kswift_threads = runner_count;
				printf(" DEBUG  request runners: %i\n", poptions->kswift_threads);
			break;
			default:
				kswift_show_help(argv[0]);
				exit(1);
		}
	}

	/* Handle SIGPIPE */
	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
	{
		fprintf(stderr, "signal:%d\n", errno);
	}

	// Begin run loop
	while (1)
	{
		sleep(1);
	}

	exit(0);
}