/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* STRFUNCS String and Memory Functions Library Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Determines whether a given ASCII string can be
								converted to a RADIX-50 array.

	Revision History	:	1990-06-04 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1990 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Necessary include files . . .														*/
/* *********************************************************************** */

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Externally-defined data items . . .												*/
/* *********************************************************************** */
COMPAT_EXTERN_DATA_DECL unsigned char RADIX50_Radix50Table[];
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	RADIX50_checkrad

	SYNOPSIS		:	return_code = RADIX50_checkrad(in_string, bad_position);

						int           return_code;

						const char   *in_string;

						unsigned int *bad_position;

	DESCRIPTION	:	Checks the whether an ASCII string can be converted to a
						RADIX-50 array using the default ASCII-to-RADIX-50 mapping
						table.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_string`` is the string for which the checking is to
						be done.

						(.) ``bad_position`` is a pointer to an ``unsigned int``
						into which will be placed the index of the offending
						character.

						(-) If ``bad_position`` is ''NULL'', no attempt will be
						made to de-reference it. This permits the application
						programmer to check the validity of a string without
						having an ``unsigned int`` in scope as the target of the
						pointer.

	RETURNS		:	Returns from this function are as follow:

						(.) ''STRFUNCS_SUCCESS'' if ``in_string`` can be converted.

						(.) ''STRFUNCS_FAILURE'' if ``in_string`` can not be
						converted.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	RADIX50_checkrad_basic

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1990 - 2016 Michael L. Brock

	OUTPUT INDEX:	RADIX50_checkrad
						STRFUNCS:RADIX-50 Functions:RADIX50_checkrad
						RADIX-50 Functions:RADIX50_checkrad
						String Functions:See STRFUNCS

	PUBLISH XREF:	RADIX50_checkrad

	PUBLISH NAME:	RADIX50_checkrad

	ENTRY CLASS	:	RADIX-50 Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int RADIX50_checkrad(const char *in_string, unsigned int *bad_position)
#else
int RADIX50_checkrad(in_string, bad_position)
const char   *in_string;
unsigned int *bad_position;
#endif /* #ifndef NARGS */
{
	return(RADIX50_checkrad_basic(in_string, bad_position,
		RADIX50_Radix50Table));
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	RADIX50_checkrad_basic

	SYNOPSIS		:	return_code = RADIX50_checkrad_basic(in_string,
							bad_position, radix50_table);

						int                  return_code;

						const char          *in_string;

						unsigned int        *bad_position;

						const unsigned char *radix50_table;

	DESCRIPTION	:	Checks the whether an ASCII string can be converted to a
						RADIX-50 array using the RADIX-50-to-ASCII mapping table
						specified by the ``radix50_table`` parameter.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_string`` is the string for which the checking is to
						be done.

						(.) ``bad_position`` is a pointer to an ``unsigned int``
						into which will be placed the index of the offending
						character.

						(-) If ``bad_position`` is ''NULL'', no attempt will be
						made to de-reference it. This permits the application
						programmer to check the validity of a string without
						having an ``unsigned int`` in scope as the target of the
						pointer.

						(.) ``radix50_table`` points to RADIX-50-to-ASCII mapping
						table to be used to perform the check.

						(-) If ``radix50_table`` is ''NULL', the default
						RADIX-50-to-ASCII mapping table is used.

						(-) An RADIX-50-to-ASCII mapping table can be initialized
						using the function ``RADIX50_init_tables``.

	RETURNS		:	Returns from this function are as follow:

						(.) ''STRFUNCS_SUCCESS'' if ``in_string`` can be converted.

						(.) ''STRFUNCS_FAILURE'' if ``in_string`` can not be
						converted.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	RADIX50_checkrad

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1990 - 2016 Michael L. Brock

	OUTPUT INDEX:	RADIX50_checkrad_basic
						STRFUNCS:RADIX-50 Functions:RADIX50_checkrad_basic
						RADIX-50 Functions:RADIX50_checkrad_basic
						String Functions:See STRFUNCS

	PUBLISH XREF:	RADIX50_checkrad_basic

	PUBLISH NAME:	RADIX50_checkrad_basic

	ENTRY CLASS	:	RADIX-50 Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int RADIX50_checkrad_basic(const char *in_string, unsigned int *bad_position,
	const unsigned char *radix50_table)
#else
int RADIX50_checkrad_basic(in_string, bad_position, radix50_table)
const char          *in_string;
unsigned int        *bad_position;
const unsigned char *radix50_table;
#endif /* #ifndef NARGS */
{
	int           return_code = STRFUNCS_FAILURE;
	unsigned int  count_1;
	int           found_flag;
	unsigned char tmp_char;

	if (bad_position != NULL)
		*bad_position = 0;

	while (*in_string) {
		tmp_char   = ((unsigned char) *in_string);
		found_flag = STRFUNCS_FALSE;
		for (count_1 = 0; count_1 < 40; count_1++) {
			if (tmp_char == radix50_table[count_1]) {
				found_flag = STRFUNCS_TRUE;
				break;
			}
		}
		if (found_flag != STRFUNCS_TRUE)
			goto EXIT_FUNCTION;
		in_string++;
		if (bad_position != NULL)
			(*bad_position)++;
	}

	return_code = STRFUNCS_SUCCESS;

EXIT_FUNCTION:

	return(return_code);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>
#include <string.h>

#include "strfunci.h"

COMPAT_FN_DECL(int main, (int argc, char **argv));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int           return_code = STRFUNCS_SUCCESS;
	int           count_1;
	char         *str;
	unsigned int  str_len;
	unsigned int  rad_cnt;
	unsigned int  rad_len;

	fprintf(stderr, "Test routine for the RADIX-50 macros\n");
	fprintf(stderr, "---- ------- --- --- -------- ------\n\n");

	if (argc == 1) {
		fprintf(stderr, "%s: Arguments for RADIX-50 macros test expected.\n",
			argv[0]);
		return_code = STRFUNCS_FAILURE;
	}
	else {
		printf("%s\n",
"==========================================================================");
		for (count_1 = 1; count_1 < argc; count_1++) {
			str     = argv[count_1];
			str_len = strlen(str);
			rad_cnt = RADIX50_SLEN_TO_RCNT(str_len);
			rad_len = RADIX50_SLEN_TO_RLEN(str_len);
			printf("STRING              : '%s'\n", str);
			printf("STRING LENGTH       : %10u\n", str_len);
			printf("RADIX50_SLEN_TO_RCNT: %10u\n",
				RADIX50_SLEN_TO_RCNT(str_len));
			printf("RADIX50_SPTR_TO_RCNT: %10u\n",
				RADIX50_SPTR_TO_RCNT(str));
			printf("RADIX50_SLEN_TO_RLEN: %10u\n",
				RADIX50_SLEN_TO_RLEN(str_len));
			printf("RADIX50_SPTR_TO_RLEN: %10u\n",
				RADIX50_SPTR_TO_RLEN(str));
			printf("RADIX50_RCNT_TO_SLEN: %10u\n",
				RADIX50_RCNT_TO_SLEN(rad_cnt));
			printf("RADIX50_RLEN_TO_SLEN: %10u\n",
				RADIX50_RLEN_TO_SLEN(rad_len));
			if (count_1 < (argc - 1))
				printf("%s\n",
"--------------------------------------------------------------------------");
		}
		printf("%s\n",
"==========================================================================");
	}

	return(return_code);
}
/* *********************************************************************** */

#endif /* TEST_MAIN */

