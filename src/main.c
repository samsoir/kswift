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

	fprintf(stderr, "\nUsage: %s [OPTIONS]\n", d);
	fprintf(stderr, "\t-h <host>     Hostname or IP of fast-cgi server\n");
	fprintf(stderr, "\t-p <port>     Port number of fast-cgi server\n");
	fprintf(stderr, "\t-q <queue>    Message queue use (gearman, zmq)\n");
	fprintf(stderr, "\t-d            Daemonize the process\n");
	fprintf(stderr, "\t-m <host>     Hostname/IP address of message server\n");
	fprintf(stderr, "\t-P <port>     Port number of message server\n");
	fprintf(stderr, "\t-f <handle>   Message queue handle\n");
	fprintf(stderr, "\t-n <number>   Number of kswift request threads\n");

}

/*
Handle the background running of kswift
*/
static bool kswift_background()
{
	pid_t pid, sid;

	fprintf(stderr, " DEBUG  forking process...\n");

	pid = fork();

	if (pid < 0)
	{
		/* Fork failed */
		fprintf(stderr, "Failed to create background process!\n");
		return false;
	}

	if (pid > 0)
	{
		/* Exit parent process */
		return false;
	}

	/* Change the file mode */
	umask(0);

	/* Create the SID for the child process */
	sid = setsid();

	if (sid < 0)
	{
		/* Child process SID failed initialization */
		fprintf(stderr, "setsid failed with error: %s\n", strerror(errno));
		return false;
	}

	/* Reopen standard I/O */
	(void) freopen("/dev/null", "r", stdin);
	(void) freopen("/dev/null", "w", stdout);
	(void) freopen("/dev/null", "w", stderr);

	return true;
}

/*
Main
*/
int main (int argc, char **argv)
{

	struct kswift_options options, *poptions;
	int c;
	uint16_t runner_count;
	bool daemonize = false;

	poptions = &options;

	/* Initialise fastcgi and gearman defaults */
	poptions->fcgi_host = "localhost";
	poptions->fcgi_port = (uint16_t) 9000;
	poptions->msg_host = "localhost";
	poptions->msg_port = (uint16_t) 4730;
	poptions->msg_register  = "kswift_request_thread";

	/* Initialise request runners default */
	poptions->kswift_threads = 10;

	if (argc == 1)
	{
		kswift_show_help(argv[0]);
		exit(1);
	}

	/* Get and set arguments */
	while ((c = getopt(argc, argv, "h:p:dq:m:P:f:n:")) != -1 )
	{
		switch (c)
		{
			case 'h':
				poptions->fcgi_host = optarg;
				fprintf(stderr, " DEBUG  fast-cgi host set to: %s\n", poptions->fcgi_host);
			break;
			case 'p':
				poptions->fcgi_port = (uint16_t) atoi(optarg);
				fprintf(stderr, " DEBUG  fast-cgi port set to: %i\n", poptions->fcgi_port);
			break;
			case 'd':
				daemonize = true;
			break;
			case 'q':
				poptions->queue = optarg;

				if (strcmp(poptions->queue, "zmq") != 0 && strcmp(poptions->queue, "gearman") != 0)
				{
					fprintf(stderr, " ERROR  driver not known: %s\n", optarg);
					kswift_show_help(argv[0]);
					exit;
				}
				fprintf(stderr, " DEBUG  driver set to: %s\n", poptions->queue);
			break;
			case 'm':
				poptions->msg_host = optarg;
				fprintf(stderr, " DEBUG  message server host set to: %s\n", 
					poptions->msg_host);
			break;
			case 'P':
				poptions->msg_port = (uint16_t) atoi(optarg);
				fprintf(stderr, " DEBUG  message server port set to: %i\n", 
					poptions->msg_port);
			break;
			case 'f':
				poptions->msg_register = optarg;
				fprintf(stderr, " DEBUG  callback function set: %s\n", 
					poptions->msg_register);
			break;
			case 'n':
				runner_count = (uint16_t) atoi(optarg);
				if (runner_count > KSWIFT_MAX_THREADS)
				{
					runner_count = KSWIFT_MAX_THREADS;
				}
				else
				{
					runner_count = 1;
				}
				poptions->kswift_threads = runner_count;
				fprintf(stderr, " DEBUG  request runners: %i\n", poptions->kswift_threads);
			break;
			default:
				kswift_show_help(argv[0]);
				exit(1);
			break;
		}
	}

	/* Handle SIGPIPE */
	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
	{
		fprintf(stderr, "signal:%d\n", errno);
	}

	/* If run in background */
	if (daemonize)
	{
		if (kswift_background() == false)
		{
			exit(1);
		}
	}

	

	exit(0);
}