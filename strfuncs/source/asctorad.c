/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* STRFUNCS String and Memory Functions Library Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Converts an ASCII string to a RADIX-50 array.

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
COMPAT_EXTERN_DATA_DECL unsigned char RADIX50_AsciiTable[];
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	RADIX50_asctorad

	SYNOPSIS		:	radix_50_count = RADIX50_asctorad(in_asc, out_rad);

						unsigned int    radix_50_count;

						const char     *in_asc;

						RADIX50_ITEM   *out_rad;

	DESCRIPTION	:	Converts an ASCII string to a RADIX-50 array using the
						default ASCII-to-RADIX-50 mapping table.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_asc`` is the string to be converted.

						(.) ``out_rad`` points to the array of ''RADIX50_ITEM''
						into which are to be placed the RADIX-50 array elements
						resulting from the conversion.

	RETURNS		:	The number of ''RADIX50_ITEM'' elements used to convert
						``in_asc``. To get the number of bytes used for the
						conversion, multiply the return value by
						''sizeof(unsigned short)''.

	NOTES			:	

	CAVEATS		:	Characters not in the mapping table will be converted to
						the RADIX-50 equivalent of the first character in the
						string used to create the mapping table. For the default
						ASCII-to-RADIX-50 mapping table, this character is a space
						(ASCII 32).

						If you want to check that a string can be converted prior
						to invoking this function, use ``RADIX50_checkrad``.

	SEE ALSO		:	RADIX50_asctorad_basic
						RADIX50_radtoasc
						RADIX50_checkrad

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1990 - 2016 Michael L. Brock

	OUTPUT INDEX:	RADIX50_asctorad
						STRFUNCS:RADIX-50 Functions:RADIX50_asctorad
						RADIX-50 Functions:RADIX50_asctorad
						String Functions:See STRFUNCS

	PUBLISH XREF:	RADIX50_asctorad

	PUBLISH NAME:	RADIX50_asctorad

	ENTRY CLASS	:	RADIX-50 Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
unsigned int RADIX50_asctorad(const char *in_asc, RADIX50_ITEM *out_rad)
#else
unsigned int RADIX50_asctorad(in_asc, out_rad)
const char   *in_asc;
RADIX50_ITEM *out_rad;
#endif /* #ifndef NARGS */
{
	return(RADIX50_asctorad_basic(in_asc, out_rad, RADIX50_AsciiTable));
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	RADIX50_asctorad_basic

	SYNOPSIS		:	radix_50_count = RADIX50_asctorad_basic(in_asc, out_rad,
							ascii_table);

						unsigned int          radix_50_count;

						const char           *in_asc;

						RADIX50_ITEM         *out_rad;

						const unsigned char  *ascii_table;

	DESCRIPTION	:	Converts an ASCII string to a RADIX-50 array using the
						ASCII-to-RADIX-50 mapping table specified by the
						``ascii_table`` parameter.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_asc`` is the string to be converted.

						(.) ``out_rad`` points to the array of ''RADIX50_ITEM''
						into which are to be placed the RADIX-50 array elements
						resulting from the conversion.

						(.) ``ascii_table`` points the ASCII-to-RADIX-50 mapping
						table to be used for the conversion.

						(-) If ``ascii_table`` is ''NULL'', the default
						ASCII-to-RADIX-50 mapping table is used.

						(-) An ASCII-to-RADIX-50 mapping table can be initialized
						using the function ``RADIX50_init_tables``.

	RETURNS		:	The number of ''RADIX50_ITEM'' elements used to convert
						``in_asc``.

	NOTES			:	

	CAVEATS		:	Characters not in the mapping table will be converted to
						the RADIX-50 equivalent of the first character in the
						string used to create the mapping table. For the default
						ASCII-to-RADIX-50 mapping table, this character is a space
						(ASCII 32).

						If you want to check that a string can be converted prior
						to invoking this function, use ``RADIX50_checkrad_basic``.

	SEE ALSO		:	RADIX50_asctorad
						RADIX50_radtoasc_basic
						RADIX50_checkrad_basic

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1990 - 2016 Michael L. Brock

	OUTPUT INDEX:	RADIX50_asctorad_basic
						STRFUNCS:RADIX-50 Functions:RADIX50_asctorad_basic
						RADIX-50 Functions:RADIX50_asctorad_basic
						String Functions:See STRFUNCS

	PUBLISH XREF:	RADIX50_asctorad_basic

	PUBLISH NAME:	RADIX50_asctorad_basic

	ENTRY CLASS	:	RADIX-50 Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
unsigned int RADIX50_asctorad_basic(const char *in_asc, RADIX50_ITEM *out_rad,
const unsigned char *ascii_table)
#else
unsigned int RADIX50_asctorad_basic(in_asc, out_rad, ascii_table)
const char          *in_asc;
RADIX50_ITEM        *out_rad;
const unsigned char *ascii_table;
#endif /* #ifndef NARGS */
{
	unsigned int         rad_count = 0;
	const unsigned char *tmp_asc   = ((unsigned char *) in_asc);

	ascii_table = (ascii_table != NULL) ? ascii_table : RADIX50_AsciiTable;

	while (*tmp_asc) {
		*out_rad = ((RADIX50_ITEM) 
			(((unsigned int) ascii_table[*(tmp_asc++)]) * ((unsigned int) 1600)));
		if (*tmp_asc) {
#ifdef _MSC_VER
			/*	*****************************************************
				*****************************************************
				The Microsoft C/C++ compiler returns a 'C4244' error
				for the '+=' operator, even with a correct cast.
				*****************************************************	*/
			*out_rad = ((RADIX50_ITEM) (((unsigned int) *out_rad) +
				(((unsigned int) ascii_table[*(tmp_asc++)]) * ((unsigned int) 40))));
			if (*tmp_asc)
				*out_rad = ((RADIX50_ITEM) (*out_rad * ascii_table[*(tmp_asc++)]));
			/*	*****************************************************	*/
#else
			*out_rad += ((RADIX50_ITEM)
				(((unsigned int) ascii_table[*(tmp_asc++)]) * ((unsigned int) 40)));
			if (*tmp_asc)
				*out_rad += ((RADIX50_ITEM) ascii_table[*(tmp_asc++)]);
#endif /* #ifdef _MSC_VER */
		}
		out_rad++;
		rad_count++;
	}

	return(rad_count);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>
#include <string.h>

#include "strfunci.h"

COMPAT_FN_DECL(int main, (int argc, char **argv));

#define MAX_RADIX	24

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int          return_code = STRFUNCS_SUCCESS;
	unsigned int count_1;
	unsigned int count_2;
	unsigned int check_rad;
	unsigned int out_length;
	char         asc_buffer[(MAX_RADIX * 3) + 1];
	RADIX50_ITEM rad_buffer[(MAX_RADIX * 2) + 1];

	fprintf(stderr, "Test routine for function 'RADIX50_asctorad()'\n");
	fprintf(stderr, "---- ------- --- -------- --------------------\n\n");

	if (argc == 1) {
		fprintf(stderr,
			"%s: Arguments for ASCII-to-Radix50 conversion expected.\n",
			argv[0]);
		return_code = STRFUNCS_FAILURE;
	}
	else {
		printf("%s\n",
"==========================================================================");
		for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
			if (strlen(trim(argv[count_1])) > (MAX_RADIX * 3)) {
				printf("---> Argument number %u '%s' truncated to ",
					count_1, argv[count_1]);
				argv[count_1][MAX_RADIX * 3] = '\0';
				trim(argv[count_1]);
				printf("'%s' --- ASCII length = %u\n", argv[count_1],
					strlen(argv[count_1]));
			}
			else
				printf("---> Argument number %u '%s' --- ASCII length = %u\n",
					count_1, argv[count_1], strlen(argv[count_1]));
			if (RADIX50_checkrad(argv[count_1], &check_rad) != STRFUNCS_SUCCESS)
				printf("---> Argument number %u (%s) has an %s %u (%s).\n",
					count_1, argv[count_1], "invalid character at position",
					check_rad, "comparison of string to RADIX-50 will fail");
			memset(rad_buffer, '\0', sizeof(rad_buffer));
			out_length = RADIX50_asctorad(argv[count_1], rad_buffer);
			printf("ASCTORAD(): ");
			for (count_2 = 0; count_2 < out_length; count_2++)
				printf("%03u|%03u%s",
					((unsigned int) (rad_buffer[count_2] >> 8)),
					((unsigned int) (rad_buffer[count_2] & 255)),
					(count_2 < (out_length - 1)) ? "|" : "");
			printf(" --- radix-50 length = %u\n", out_length);
			printf("ASCTORAD(): [%s] | ",
				RADIX50_radtoasc(rad_buffer, asc_buffer, out_length));
			printf("[%s] | [%s] --- %s\n", asc_buffer, argv[count_1],
				(STRFUNCS_stricmp(trim(asc_buffer), argv[count_1])) ? "FAILED" :
				"OK");
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

