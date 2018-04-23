/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLB Executable Module Source File													*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Emits the current time with up to nanosecond
								granularity.

	Revision History	:	1985-10-31 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1985 - 2018.
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
COMPAT_FN_DECL(int main, (int argc, char **argv));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int main(int argc, char **argv)
{
	int          return_code = EXIT_SUCCESS;
	int          utc_flag    = 0;
	int          parse_flag  = 0;
	unsigned int count_1;
	char         time_buffer[SDTIF_FMT_TIME_LEN_TIMESPEC + 1];

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if ((!stricmp(argv[count_1], "-help")) ||
			(!stricmp(argv[count_1], "-h"))) {
			fprintf(stderr, "USAGE:\n   %s %s %s %s\n\n",
				extract_file_name(argv[0]),
				"[ -h | -help ]",
				"[ -gmt | -utc ]",
				"[ -parse ]");
			goto EXIT_FUNCTION;
		}
		else if ((!stricmp(argv[count_1], "-gmt")) ||
			(!stricmp(argv[count_1], "-utc")))
			utc_flag = 1;
		else if (!stricmp(argv[count_1], "-parse"))
			parse_flag = 1;
		else {
			fprintf(stderr,
				"ERROR: Invalid command line --- use '-h' for help\n\n");
			return_code = EXIT_FAILURE;
			goto EXIT_FUNCTION;
		}
	}

	if (!utc_flag)
		SDTIF_Format_timespec(NULL, time_buffer);
	else
		SDTIF_Format_timespec_GMT(NULL, time_buffer);

	if (parse_flag) {
		time_buffer[4]  = ' ';
		time_buffer[7]  = ' ';
		time_buffer[13] = ' ';
		time_buffer[16] = ' ';
		time_buffer[19] = ' ';
	}

	printf("%s\n", time_buffer);

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/


