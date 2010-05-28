/*
 * $Id: errno.c,v 1.1 2005/11/16 20:01:45 sms Exp $
 * www.pccl.demon.co.uk
 *
 * Program to display errno values.
 */
#include	<errno.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<unistd.h>

extern char	*basename ();
static char*	sProgname;

static void usage (void)
{
	(void) printf ("Usage: %s [-h] errnum...\n", sProgname);
}

static void help (void)
{
	usage ();
	(void ) printf ("    -h      help.\n");
	(void ) printf ("    errnum  error codes of interest.\n");
}

main (int argc, char *argv[])
{
	int		c;

	sProgname	= basename (argv[0]);
	while ((c = getopt (argc, argv, "h")) != EOF)
	{
		switch (c)
		{
			case 'h':
			{
				help ();
				exit (0);;
			}
			case '?':
			{
				usage ();
				exit (EINVAL);
			}
		}
	}

	for (; optind < argc; optind++)
	{
		int	lErrCode	= strtoul (argv[optind], NULL, 0);
		char *lErrString	= strerror (lErrCode);
		if (lErrString == NULL)
		{
			lErrString	= "Unknown";
		}
		(void) printf ("errno = %d - %s\n", lErrCode, lErrString);
	}
}

