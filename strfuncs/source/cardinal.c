/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Determines the English language cardinal equivalent of
								a number.

	Revision History	:	1996-04-06 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Include necessary header files . . .											*/
/* *********************************************************************** */

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	cardinal

	SYNOPSIS		:	string_ptr = cardinal(number, text);

						char          *string_ptr;

						unsigned long  number;

						char          *text;

	DESCRIPTION	:	Determines the English language cardinal equivalent of the
						''unsigned long'' number passed as the parameter ``number``.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``number`` is the value for which the cardinal string
						is desired.

						(.) ``text`` is the string into which the cardinal string
						is to be copied by this function.

	RETURNS		: 	The ``text`` parameter is returned.

   NOTES       :  English language cardinals for numbers larger than the
						maximum representable within an ''unsigned long'' may be
						retrieved by invoking the function ``cardinal_double``.

						English language ordinal strings may be retrieved by
						invoking the function ``ordinal_full``.

   CAVEATS     :  

   SEE ALSO    :  cardinal_double
						get_ulong_text

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1996 - 2018 Michael L. Brock

   OUTPUT INDEX:  cardinal
						Numeric Formatting Functions:cardinal
						STRFUNCS:Numeric Formatting Functions:cardinal
						String Functions:See STRFUNCS

   PUBLISH XREF:  cardinal

   PUBLISH NAME:	cardinal

	ENTRY CLASS	:	Numeric Formatting Functions

EOH */
/*	*********************************************************************** */
#ifndef NARGS
char *cardinal(unsigned long number, char *text)
#else
char *cardinal(number, text)
unsigned long  number;
char          *text;
#endif /* #ifndef NARGS */
{
	return(get_ulong_text(number, text));
}
/*	*********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	cardinal_double

	SYNOPSIS		:	string_ptr = cardinal_double(number, decimal_places, text);

						char          *string_ptr;

						double         number;

						unsigned int   decimal_places;

						char          *text;

	DESCRIPTION	:	Determines the English language cardinal equivalent of the
						''double'' number passed as the parameter ``number``.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``number`` is the value for which the cardinal string
						is desired.

						(.) ``decimal_places`` is the number of decimal places with
						which the number is to be formatted by this function.

						(.) ``text`` is the string into which the cardinal string
						is to be copied by this function.

	RETURNS		: 	The ``text`` parameter is returned.

   NOTES       :  English language ordinal strings may be retrieved by
						invoking the function ``orrdinal_double_full``.

   CAVEATS     :  

   SEE ALSO    :  cardinal
						get_double_text

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1996 - 2018 Michael L. Brock

   OUTPUT INDEX:  cardinal_double
						Numeric Formatting Functions:cardinal_double
						STRFUNCS:Numeric Formatting Functions:cardinal_double
						String Functions:See STRFUNCS

   PUBLISH XREF:  cardinal_double

   PUBLISH NAME:	cardinal_double

	ENTRY CLASS	:	Numeric Formatting Functions

EOH */
/*	*********************************************************************** */
#ifndef NARGS
char *cardinal_double(double number, unsigned int decimal_places, char *text)
#else
char *cardinal_double(number, decimal_places, text)
double        number;
unsigned int  decimal_places;
char         *text;
#endif /* #ifndef NARGS */
{
	return(drop_double_text_zeroes(get_double_text(number, decimal_places,
		text)));
}
/*	*********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

COMPAT_FN_DECL(int main, (int argc, char **argv));

COMPAT_FN_DECL_STATIC(int TEST_DoTest,
	(unsigned long number));

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

	fprintf(stderr, "Test routine for function 'cardinal_full()'\n");
	fprintf(stderr, "---- ------- --- -------- -----------------\n\n");

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

	printf("%10lu: %s\n", number, cardinal(number, buffer_1));
	printf("%10s: %s\n", " ", cardinal_double(((double) number), 0,
		buffer_2));

	if (strcmp(buffer_1, buffer_2)) {
		fprintf(stderr, "%s ('%s') %s ('%s').\n",
			"The returned string from 'cardinal()'", buffer_1,
			"does not equal the returned string from 'cardinal_double()'",
			buffer_2);
		return_code = STRFUNCS_FAILURE;
	}

	return(return_code);
}

#endif /* TEST_MAIN */

