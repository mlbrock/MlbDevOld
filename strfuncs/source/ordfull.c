/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Determines the English language ordinal equivalent of
								a number.

	Revision History	:	1996-04-06 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Include necessary header files . . .											*/
/* *********************************************************************** */

#include <stdlib.h>
#include <string.h>

#include "strfunci.h"

/* *********************************************************************** */

/*	*********************************************************************** */
/*	*********************************************************************** */
/*	*********************************************************************** */

COMPAT_FN_DECL_STATIC(char *concatenate_ordinal_full, (char *ordinal_string));

/*	*********************************************************************** */

/*	*********************************************************************** */
/*	*********************************************************************** */
/*		A wee bit o' static data . . .													*/
/*	*********************************************************************** */
static const char         *STRFUNCS_FullOrdinalList[][2] = {
	{	"one",			"first"			},
	{	"two",			"second"			},
	{	"three",			"third"			},
	{	"five",			"fifth"			},
	{	"eight",			"eighth"			},
	{	"nine",			"ninth"			},
	{	"twelve",		"twelfth"		},
	{	"twenty",		"twentieth"		},
	{	"thirty",		"thirtieth"		},
	{	"forty",			"fortieth" 		},
	{	"fifty",			"fiftieth" 		},
	{	"sixty",			"sixtieth" 		},
	{	"seventy",		"seventieth"	},
	{	"eighty",		"eightieth"		},
	{	"ninety",		"ninetieth"		},
};
static const unsigned int  STRFUNCS_FullOrdinalCount     =
	sizeof(STRFUNCS_FullOrdinalList) / sizeof(STRFUNCS_FullOrdinalList[0]);
/*	*********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	ordinal_full

	SYNOPSIS		:	string_ptr = ordinal_full(number, text);

						char          *string_ptr;

						unsigned long  number;

						char          *text;

	DESCRIPTION	:	Determines the English language ordinal equivalent of the
						''unsigned long'' number passed as the parameter ``number``.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``number`` is the value for which the ordinal string
						is desired.

						(.) ``text`` is the string into which the ordinal string
						is to be copied by this function.

	RETURNS		: 	The ``text`` parameter is returned.

   NOTES       :  English language ordinals for numbers larger than the
						maximum representable within an ''unsigned long'' may be
						retrieved by invoking the function ``ordinal_double_full``.

						English language two-character ordinal abbreviations
						(''th'', ''st'', ''nd'', and ''rd'') may be retrieved by
						invoking the function ``ordinal``.

						English language cardinal strings may be retrieved by
						invoking the function ``cardinal``.

						If ``number`` is ''0'', then the resulting string will be
						''zeroth'', courtesy of Issac Asimov.

   CAVEATS     :  

   SEE ALSO    :  ordinal
						ordinal_double_full

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1996 - 2015 Michael L. Brock

   OUTPUT INDEX:  ordinal_full
						Numeric Formatting Functions:ordinal_full
						STRFUNCS:Numeric Formatting Functions:ordinal_full
						String Functions:See STRFUNCS

   PUBLISH XREF:  ordinal_full

   PUBLISH NAME:	ordinal_full

	ENTRY CLASS	:	Numeric Formatting Functions

EOH */
/*	*********************************************************************** */
#ifndef NARGS
char *ordinal_full(unsigned long number, char *text)
#else
char *ordinal_full(number, text)
unsigned long  number;
char          *text;
#endif /* #ifndef NARGS */
{
	return(concatenate_ordinal_full(get_ulong_text(number, text)));
}
/*	*********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	ordinal_double_full

	SYNOPSIS		:	string_ptr = ordinal_double_full(number, decimal_places,
							text);

						char          *string_ptr;

						double         number;

						unsigned int   decimal_places;

						char          *text;

	DESCRIPTION	:	Determines the English language ordinal equivalent of the
						''double'' number passed as the parameter ``number``.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``number`` is the value for which the ordinal string
						is desired.

						(.) ``decimal_places`` is the number of decimal places with
						which the number is to be formatted by this function.

						(.) ``text`` is the string into which the ordinal string
						is to be copied by this function.

	RETURNS		: 	The ``text`` parameter is returned.

   NOTES       :  English language two-character ordinal abbreviations
						(''th'', ''st'', ''nd'', and ''rd'') may be retrieved by
						invoking the function ``ordinal``.

						English language cardinal strings may be retrieved by
						invoking the function ``cardinal_double``.

						If ``number`` is ''0'', then the resulting string will be
						''zeroth'', courtesy of Issac Asimov.

   CAVEATS     :  

   SEE ALSO    :  ordinal
						ordinal_full

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1996 - 2015 Michael L. Brock

   OUTPUT INDEX:  ordinal_double_full
						Numeric Formatting Functions:ordinal_double_full
						STRFUNCS:Numeric Formatting Functions:ordinal_double_full
						String Functions:See STRFUNCS

   PUBLISH XREF:  ordinal_double_full

   PUBLISH NAME:	ordinal_double_full

	ENTRY CLASS	:	Numeric Formatting Functions

EOH */
/*	*********************************************************************** */
#ifndef NARGS
char *ordinal_double_full(double number, unsigned int decimal_points,
	char *text)
#else
char *ordinal_double_full(number, decimal_points, text)
double        number;
unsigned int  decimal_points;
char         *text;
#endif /* #ifndef NARGS */
{
	return(concatenate_ordinal_full(drop_double_text_zeroes(get_double_text(
		number, decimal_points, text))));
}
/*	*********************************************************************** */

/*	*********************************************************************** */
#ifndef NARGS
static char *concatenate_ordinal_full(char *ordinal_string)
#else
static char *concatenate_ordinal_full(ordinal_string)
char *ordinal_string;
#endif /* #ifndef NARGS */
{
	unsigned int  count_1;
	char         *tmp_ptr;

	tmp_ptr = (((tmp_ptr = strrchr(ordinal_string, '-')) != NULL) ||
		((tmp_ptr = strrchr(ordinal_string, ' ')) != NULL)) ? (tmp_ptr + 1) :
		ordinal_string;

	for (count_1 = 0; count_1 < STRFUNCS_FullOrdinalCount; count_1++) {
		if (!STRFUNCS_stricmp(STRFUNCS_FullOrdinalList[count_1][0], tmp_ptr)) {
			strcpy(tmp_ptr, STRFUNCS_FullOrdinalList[count_1][1]);
			tmp_ptr = NULL;
			break;
		}
	}

	return((tmp_ptr == NULL) ? ordinal_string : strcat(ordinal_string, "th"));
}
/*	*********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>

COMPAT_FN_DECL(       int main,        (int argc, char **argv));
COMPAT_FN_DECL_STATIC(int TEST_DoTest, (unsigned long number));

/*	*********************************************************************** */
/*	*********************************************************************** */
/*	*********************************************************************** */
#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int          return_code = STRFUNCS_SUCCESS;
	unsigned int count_1;

	fprintf(stderr, "Test routine for function 'ordinal_full()'\n");
	fprintf(stderr, "---- ------- --- -------- ----------------\n\n");

	if (argc > 1) {
		for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
			if ((return_code = TEST_DoTest(strtoul(argv[count_1], NULL, 10))) !=
				STRFUNCS_SUCCESS)
				break;
		}
	}
	else {
		for (count_1 = 0; count_1 <= 100; count_1++) {
			if ((return_code = TEST_DoTest(((unsigned long) count_1))) !=
				STRFUNCS_SUCCESS)
				break;
		}
	}

	return(return_code);
}
/*	*********************************************************************** */

#ifndef NARGS
static int TEST_DoTest(unsigned long number)
#else
static int TEST_DoTest(number)
unsigned long number;
#endif /* #ifndef NARGS */
{
	int  return_code = STRFUNCS_SUCCESS;
	char buffer_1[512 + 1];
	char buffer_2[512 + 1];
	char buffer_3[512 + 1];

	printf("%10lu: %s\n", number, ordinal(((unsigned int) number), buffer_1));
	printf("%10s: %s\n", " ", ordinal_full(number, buffer_2));
	printf("%10s: %s\n", " ", ordinal_double_full(((double) number), 0,
		buffer_3));

	if (strcmp(buffer_2, buffer_3)) {
		fprintf(stderr, "%s ('%s') %s ('%s').\n",
			"The returned string from 'ordinal_full()'", buffer_2,
			"does not equal the returned string from 'ordinal_double_full()'",
			buffer_3);
		return_code = STRFUNCS_FAILURE;
	}

	if (strcmp(buffer_1, buffer_2 + (strlen(buffer_2) - 2))) {
		fprintf(stderr, "%s ('%s') %s ('%s').\n",
			"The returned string from 'ordinal()'", buffer_1,
			"does not equal the end of the returned string from 'ordinal_full()'",
			buffer_2);
		return_code = STRFUNCS_FAILURE;
	}

	return(return_code);
}

#endif /* TEST_MAIN */

