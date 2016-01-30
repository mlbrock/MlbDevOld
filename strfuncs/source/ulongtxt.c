/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	STRFUNCS String and Memory Functions Library Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Formats an unsigned long numeric value as a text
								string.

	Revision History	:	1995-02-14 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <limits.h>
#include <string.h>

#include "strfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*
	NOTE: We assume a 'long long' with a maximum value of (2 ^ 64) - 1 ---
			that is 18,446,744,073,709,551,615.
*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
COMPAT_EXTERN_DATA_DEF const STRFUNCS_VALUE_NAME STRFUNCS_NumberTextList[] = {
	{	                  0L,	"zero",			 0L	},
	{	                  1L,	"one",			 0L	},
	{	                  2L,	"two",			 0L	},
	{	                  3L,	"three",			 0L	},
	{	                  4L,	"four",			 0L	},
	{	                  5L,	"five",			 0L	},
	{	                  6L,	"six",			 0L	},
	{	                  7L,	"seven",			 0L	},
	{	                  8L,	"eight",			 0L	},
	{	                  9L,	"nine",			 0L	},
	{	                 10L,	"ten",			 0L	},
	{	                 11L,	"eleven",		 0L	},
	{	                 12L,	"twelve",		 0L	},
	{	                 13L,	"thirteen",		 0L	},
	{	                 14L,	"fourteen",		 0L	},
	{	                 15L,	"fifteen",		 0L	},
	{	                 16L,	"sixteen",		 0L	},
	{	                 17L,	"seventeen",	 0L	},
	{	                 18L,	"eighteen",		 0L	},
	{	                 19L,	"nineteen",		 0L	},
	{	                 20L,	"twenty",		10L	},
	{	                 30L,	"thirty",		10L	},
	{	                 40L,	"forty",			10L	},
	{	                 50L,	"fifty",			10L	},
	{	                 60L,	"sixty",			10L	},
	{	                 70L,	"seventy",		10L	},
	{	                 80L,	"eighty",		10L	},
	{	                 90L,	"ninety",		10L	},
	{	                100L,	"hundred",		 0L	},
	{	               1000L,	"thousand",		 0L	},
	{	            1000000L,	"million",	  	 0L	},
	{	         1000000000L,	"billion",	  	 0L	}
#if ULONG_MAX != 0XFFFFFFFFL
	,
	{	      1000000000000L,	"trillion",   	 0L	},
	{	   1000000000000000L,	"quadrillion",	 0L	},
	{	1000000000000000000L,	"quintillion",	 0L	}
#endif /* #if ULONG_MAX != 0XFFFFFFFFL */
};
COMPAT_EXTERN_DATA_DEF const unsigned int STRFUNCS_NumberTextCount =
	sizeof(STRFUNCS_NumberTextList) / sizeof(STRFUNCS_NumberTextList[0]);
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
COMPAT_EXTERN_DATA_DEF const STRFUNCS_VALUE_NAME
	STRFUNCS_MetricNumberTextList[] = {
	{	                  0L,	"zero",			 0L	},
	{	                  1L,	"one",			 0L	},
	{	                  2L,	"two",			 0L	},
	{	                  3L,	"three",			 0L	},
	{	                  4L,	"four",			 0L	},
	{	                  5L,	"five",			 0L	},
	{	                  6L,	"six",			 0L	},
	{	                  7L,	"seven",			 0L	},
	{	                  8L,	"eight",			 0L	},
	{	                  9L,	"nine",			 0L	},
	{	                 10L,	"ten",			 0L	},
	{	                 11L,	"eleven",		 0L	},
	{	                 12L,	"twelve",		 0L	},
	{	                 13L,	"thirteen",		 0L	},
	{	                 14L,	"fourteen",		 0L	},
	{	                 15L,	"fifteen",		 0L	},
	{	                 16L,	"sixteen",		 0L	},
	{	                 17L,	"seventeen",	 0L	},
	{	                 18L,	"eighteen",		 0L	},
	{	                 19L,	"nineteen",		 0L	},
	{	                 20L,	"twenty",		10L	},
	{	                 30L,	"thirty",		10L	},
	{	                 40L,	"forty",			10L	},
	{	                 50L,	"fifty",			10L	},
	{	                 60L,	"sixty",			10L	},
	{	                 70L,	"seventy",		10L	},
	{	                 80L,	"eighty",		10L	},
	{	                 90L,	"ninety",		10L	},
	{	                100L,	"hundred",		 0L	},
	{	               1000L,	"kilo",			 0L	},
	{	            1000000L,	"mega",			 0L	},
	{	         1000000000L,	"giga",			 0L	}
#if ULONG_MAX != 0XFFFFFFFFL
	,
	{	      1000000000000L,	"tera", 			 0L	},
	{	   1000000000000000L,	"peta",			 0L	},
	{	1000000000000000000L,	"exa",			 0L	}
#endif /* #if ULONG_MAX != 0XFFFFFFFFL */
};
COMPAT_EXTERN_DATA_DEF const unsigned int STRFUNCS_MetricNumberTextCount =
	sizeof(STRFUNCS_MetricNumberTextList) /
	sizeof(STRFUNCS_MetricNumberTextList[0]);
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
COMPAT_EXTERN_DATA_DEF const STRFUNCS_VALUE_NAME
	STRFUNCS_BritishNumberTextList[] = {
	{	                  0L,	"zero",			 0L	},
	{	                  1L,	"one",			 0L	},
	{	                  2L,	"two",			 0L	},
	{	                  3L,	"three",			 0L	},
	{	                  4L,	"four",			 0L	},
	{	                  5L,	"five",			 0L	},
	{	                  6L,	"six",			 0L	},
	{	                  7L,	"seven",			 0L	},
	{	                  8L,	"eight",			 0L	},
	{	                  9L,	"nine",			 0L	},
	{	                 10L,	"ten",			 0L	},
	{	                 11L,	"eleven",		 0L	},
	{	                 12L,	"twelve",		 0L	},
	{	                 13L,	"thirteen",		 0L	},
	{	                 14L,	"fourteen",		 0L	},
	{	                 15L,	"fifteen",		 0L	},
	{	                 16L,	"sixteen",		 0L	},
	{	                 17L,	"seventeen",	 0L	},
	{	                 18L,	"eighteen",		 0L	},
	{	                 19L,	"nineteen",		 0L	},
	{	                 20L,	"twenty",		10L	},
	{	                 30L,	"thirty",		10L	},
	{	                 40L,	"forty",			10L	},
	{	                 50L,	"fifty",			10L	},
	{	                 60L,	"sixty",			10L	},
	{	                 70L,	"seventy",		10L	},
	{	                 80L,	"eighty",		10L	},
	{	                 90L,	"ninety",		10L	},
	{	                100L,	"hundred",		 0L	},
	{	               1000L,	"thousand",		 0L	},
	{	            1000000L,	"million", 		 0L	},
	{	         1000000000L,	"milliard",		 0L	}
#if ULONG_MAX != 0XFFFFFFFFL
	,
	{	      1000000000000L,	"billion", 		 0L	},
	{	1000000000000000000L,	"trillion",		 0L	}
#endif /* #if ULONG_MAX != 0XFFFFFFFFL */
};
COMPAT_EXTERN_DATA_DEF const unsigned int STRFUNCS_BritishNumberTextCount =
	sizeof(STRFUNCS_BritishNumberTextList) /
	sizeof(STRFUNCS_BritishNumberTextList[0]);
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	get_ulong_text

	SYNOPSIS		:	result_text = get_ulong_text(in_ulong, out_string);

						char          *result_text;

						unsigned long  in_ulong;

						char          *out_string;

	DESCRIPTION	:	Formats an unsigned long numeric value as a text string
						using the American formatting specification.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_ulong`` is the unsigned long value to be formatted.

						(.) ``out_string`` points to the area into which the
						formatted string is to be placed.

	RETURNS		:	A pointer to the string used to store the formatted string
						(that is, ``out_string``).

	NOTES			:	Values larger than the manifest constant ''ULONG_MAX'', or
						which have fractional portions may be formatted using the
						function ``get_double_text``.

	CAVEATS		:	

	SEE ALSO		:	get_double_text
						get_ulong_text_basic

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2016 Michael L. Brock

	OUTPUT INDEX:	get_ulong_text
						Numeric Formatting Functions:get_ulong_text
						STRFUNCS:Numeric Formatting Functions:get_ulong_text
						String Functions:See STRFUNCS

	PUBLISH XREF:	get_ulong_text

	PUBLISH NAME:	get_ulong_text

	ENTRY CLASS	:	Numeric Formatting Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *get_ulong_text(unsigned long in_ulong, char *out_string)
#else
char *get_ulong_text(in_ulong, out_string)
unsigned long  in_ulong;
char          *out_string;
#endif /* #ifndef NARGS */
{
	return(get_ulong_text_basic(in_ulong, STRFUNCS_NumberTextCount,
		STRFUNCS_NumberTextList, out_string));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	get_ulong_text_basic

	SYNOPSIS		:	result_text = get_ulong_text_basic(in_ulong, name_count,
							name_list, out_string);

						char                      *result_text;

						unsigned long              in_ulong;

						unsigned int               name_count;

						const STRFUNCS_VALUE_NAME *name_list;

						char                      *out_string;

	DESCRIPTION	:	Formats an unsigned long numeric value as a text string
						using the formatting specification passed as parameters
						``name_count`` and ``name_list``.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_ulong`` is the unsigned long value to be formatted.

						(.) ``name_count`` is the number of elements in the
						formatting specification array ``name_list``.

						(.) ``name_list`` points to the array of structures of
						type ``STRFUNCS_VALUE_NAME`` to be used as the formatting
						specification array.

						(.) ``out_string`` points to the area into which the
						formatted string is to be placed.

	RETURNS		:	A pointer to the string used to store the formatted string
						(that is, ``out_string``).

	NOTES			:	If ``name_list`` is ``NULL`` then the numeric value will
						be formatted using American conventions.

						Values larger than the manifest constant ''ULONG_MAX'', or
						which have fractional portions may be formatted using the
						function ``get_double_text_basic``.

	CAVEATS		:	

	SEE ALSO		:	get_double_text_basic
						get_ulong_text

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2016 Michael L. Brock

	OUTPUT INDEX:	get_ulong_text_basic
						Numeric Formatting Functions:get_ulong_text_basic
						STRFUNCS:Numeric Formatting Functions:get_ulong_text_basic
						String Functions:See STRFUNCS

	PUBLISH XREF:	get_ulong_text_basic

	PUBLISH NAME:	get_ulong_text_basic

	ENTRY CLASS	:	Numeric Formatting Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *get_ulong_text_basic(unsigned long in_ulong, unsigned int name_count,
	const STRFUNCS_VALUE_NAME *name_list, char *out_string)
#else
char *get_ulong_text_basic(in_ulong, name_count, name_list, out_string)
unsigned long              in_ulong;
unsigned int               name_count;
const STRFUNCS_VALUE_NAME *name_list;
char                      *out_string;
#endif /* #ifndef NARGS */
{
	unsigned int               count_1;
	const STRFUNCS_VALUE_NAME *name_ptr;

	name_count = (name_list != NULL) ? name_count : STRFUNCS_NumberTextCount;
	name_list  = (name_list != NULL) ? name_list  : STRFUNCS_NumberTextList;

	if (!in_ulong)
		strcpy(out_string, name_list[0].name);
	else {
		*out_string = '\0';
		for (count_1 = name_count - 1; count_1 > 0; count_1--) {
			name_ptr = name_list + count_1;
			if (in_ulong >= name_ptr->value) {
				if (*out_string)
					strcat(out_string, " ");
				if (!name_ptr->basis) {
					if (in_ulong % name_ptr->value) {
						get_ulong_text_basic(in_ulong / name_ptr->value, name_count,
							name_list, out_string + strlen(out_string));
						strcat(strcat(out_string, " "), name_ptr->name);
					}
					else {
						if (in_ulong >= 100L) {
							get_ulong_text_basic(in_ulong / name_ptr->value,
								name_count, name_list,
								out_string + strlen(out_string));
							strcat(out_string, " ");
						}
						strcat(out_string, name_ptr->name);
					}
					in_ulong %= name_ptr->value;
				}
				else {
					if (!(in_ulong % name_ptr->basis)) {
						strcat(out_string, name_ptr->name);
						in_ulong %= name_ptr->basis;
					}
					else {
						strcat(strcat(strcat(out_string, name_ptr->name), "-"),
							name_list[((unsigned int) (in_ulong % name_ptr->basis))].
							name);
						in_ulong = 0L;
					}
				}
				if (!in_ulong)
					break;
			}
		}
	}

	return(out_string);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>
#include <stdlib.h>

COMPAT_FN_DECL(int main, (int argc, char **argv));

COMPAT_FN_DECL_STATIC(void TEST_DoTest, (int argc, char **argv));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int           return_code = STRFUNCS_SUCCESS;
	unsigned long count_1;
	char          buffer[1024];

	fprintf(stderr, "Test routine for function 'get_ulong_text()'\n");
	fprintf(stderr, "---- ------- --- -------- ------------------\n\n");

	if (argc > 1)
		TEST_DoTest(argc, argv);
	else {
		for (count_1 = 0L; count_1 <= ULONG_MAX; count_1++)
			printf("%10lu: %s\n", count_1, get_ulong_text(count_1, buffer));
	}


	return(return_code);
}

#ifndef NARGS
static void TEST_DoTest(int argc, char **argv)
#else
static void TEST_DoTest(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	
	unsigned int               name_count = STRFUNCS_NumberTextCount;
	const STRFUNCS_VALUE_NAME *name_list  = STRFUNCS_NumberTextList;
	unsigned long              count_1;
	unsigned long              tmp_ulong;
	char                       buffer[1024];

	for (count_1 = 1L; count_1 < ((unsigned long) argc); count_1++) {
		if ((!STRFUNCS_stricmp(argv[((int) count_1)], "AMERICAN")) ||
			(!STRFUNCS_stricmp(argv[((int) count_1)], "US"))) {
			name_count = STRFUNCS_NumberTextCount;
			name_list  = STRFUNCS_NumberTextList;
			fprintf(stderr, "---> Switched to '%s'\n", argv[((int) count_1)]);
		}
		else if (!STRFUNCS_stricmp(argv[((int) count_1)], "METRIC")) {
			name_count = STRFUNCS_MetricNumberTextCount;
			name_list  = STRFUNCS_MetricNumberTextList;
			fprintf(stderr, "---> Switched to '%s'\n", argv[((int) count_1)]);
		}
		else if ((!STRFUNCS_stricmp(argv[((int) count_1)], "BRITISH")) ||
			(!STRFUNCS_stricmp(argv[((int) count_1)], "UK"))) {
			name_count = STRFUNCS_BritishNumberTextCount;
			name_list  = STRFUNCS_BritishNumberTextList;
			fprintf(stderr, "---> Switched to '%s'\n", argv[((int) count_1)]);
		}
		else {
			tmp_ulong = strtoul(argv[((unsigned int) count_1)], NULL, 10);
			printf("%10lu: %s\n", tmp_ulong, get_ulong_text_basic(tmp_ulong,
				name_count, name_list, buffer));
		}
	}
}

#endif /* #ifdef TEST_MAIN */

