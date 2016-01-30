/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLB Executable Module Source File													*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Performs a 'sleep' with up to nanosecond granularity.

	Revision History	:	1986-02-15 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1986 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Required include files . . .															*/
/*	***********************************************************************	*/

#include <stdio.h>

#include <sdtif.h>
#include <strfuncs.h>

/*	***********************************************************************	*/

/*	***********************************************************************	*/
COMPAT_FN_DECL(int main,
	(int argc, char **argv));
	/*	*****************************************************************	*/
COMPAT_FN_DECL_STATIC(unsigned long XSleep_GetTime,
	(int argc, char **argv, int argv_index, unsigned long max_sleep));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int main(int argc, char **argv)
{
	int          return_code = EXIT_SUCCESS;
	unsigned int count_1;

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if ((!stricmp(argv[count_1], "-help")) ||
			(!stricmp(argv[count_1], "-h"))) {
			fprintf(stderr, "USAGE:\n   %s %s %s %s %s %s\n\n",
				extract_file_name(argv[0]),
				"[ -h | -help ]",
				"[ [ -s ] <sleep-seconds> ]",
				"[ -k <sleep-milliseconds> ]",
				"[ -u <sleep-microseconds> ]",
				"[ -n <sleep-nanoseconds> ]");
			goto EXIT_FUNCTION;
		}
	}

	if (argc == 1)
		SDTIF_sleep(1);
	else if (str_digit(argv[1], 0) == NULL)
		SDTIF_sleep(((unsigned int) XSleep_GetTime(argc, argv, 1,
			((unsigned long) UINT_MAX))));
	else if (!stricmp(argv[1], "-s"))
		SDTIF_sleep(((unsigned int) XSleep_GetTime(argc, argv, 2,
			((unsigned long) UINT_MAX))));
	else if (!stricmp(argv[1], "-k"))
		SDTIF_msleep(XSleep_GetTime(argc, argv, 2, ULONG_MAX));
	else if (!stricmp(argv[1], "-u"))
		SDTIF_usleep(XSleep_GetTime(argc, argv, 2, ULONG_MAX));
	else if (!stricmp(argv[1], "-n"))
		SDTIF_nsleep(XSleep_GetTime(argc, argv, 2, ULONG_MAX));
	else {
		fprintf(stderr, "ERROR: Invalid command line --- use '-h' for help\n\n");
		return_code = EXIT_FAILURE;
	}

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static unsigned long XSleep_GetTime(int argc, char **argv, int argv_index,
	unsigned long max_sleep)
{
	double tmp_double;

	if (argc <= argv_index)
		return(1L);
	else if ((tmp_double = atof(argv[argv_index])) < 0.0)
		return(0L);
	else if (tmp_double > ((double) max_sleep))
		return(max_sleep);

	return(((unsigned long) tmp_double));
}
/*	***********************************************************************	*/

