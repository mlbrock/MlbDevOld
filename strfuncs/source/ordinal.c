/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Determines the English language two-character
								abbreviation of the ordinal equivalent of a number.

	Revision History	:	1986-10-27 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1986 - 2016.
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
/*		A wee bit o' static data . . .													*/
/*	*********************************************************************** */

static const char *OrdinalNamesList[] = { "th", "st", "nd", "rd" };

/*	*********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	ordinal

	SYNOPSIS		:	string_ptr = ordinal(number, text);

						char         *string_ptr;

						unsigned int  number;

						char         *text;

	DESCRIPTION	:	Determines the English language two-character abbreviation
						of the ordinal equivalent of the number passed as the
						parameter ``number``.

						The English language two-character ordinal abbreviations
						are as follow:

						(.) ``th``

						(.) ``st``

						(.) ``nd``

						(.) ``rd``

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``number`` is the value for which the ordinal
						abbreviation string is desired.

						(.) ``text`` is the string into which the ordinal
						abbreviation string is to be copied by this function.

	RETURNS		: 	The ``text`` parameter is returned.

   NOTES       :  English language ordinal abbreviations for numbers larger
						than the maximum representable within an ''unsigned int''
						may be retrieved by invoking this function with the desired
						number modulus ''100'' as the ``number`` parameter.

						The complete ordinal text of a number may be retrieved by
						using the function ``ordinal_full`` or ``ordinal_double_full``.

						If ``number`` is ''0'', then the resulting string will be
						''th'' (as in ''zeroth''), courtesy of Issac Asimov.

   CAVEATS     :  

   SEE ALSO    :  ordinal_full
						ordinal_double_full

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1986 - 2016 Michael L. Brock

   OUTPUT INDEX:  ordinal
						Numeric Formatting Functions:ordinal
						STRFUNCS:Numeric Formatting Functions:ordinal
						String Functions:See STRFUNCS

   PUBLISH XREF:  ordinal

   PUBLISH NAME:	ordinal

	ENTRY CLASS	:	Numeric Formatting Functions

EOH */
/*	*********************************************************************** */
#ifndef NARGS
char *ordinal(unsigned int number, char *text)
#else
char *ordinal(number, text)
unsigned int  number;
char         *text;
#endif /* #ifndef NARGS */
{
	number = abs(((int) (number % 100)));
	number = (number > 20) ? (number % 10) : number;
	number = ((number >= 1) && (number <= 3)) ? number : 0;

	return(strcpy(text, OrdinalNamesList[number]));
}
/*	*********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>

COMPAT_FN_DECL(int main, (int argc, char **argv));

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
	unsigned int  count_1;
	unsigned long tmp_number;
	char          buffer[512 + 1];

	fprintf(stderr, "Test routine for function 'ordinal()'\n");
	fprintf(stderr, "---- ------- --- -------- -----------\n\n");

	if (argc > 1) {
		for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
			tmp_number = strtoul(argv[count_1], NULL, 10);
			printf("%10lu = %s\n", tmp_number,
				ordinal(((unsigned int) tmp_number), buffer));
		}
	}
	else {
		for (count_1 = 0; count_1 <= 100; count_1++)
			printf("%10u = %s\n", count_1, ordinal(count_1, buffer));
	}

	return(STRFUNCS_SUCCESS);
}
/*	*********************************************************************** */

#endif /* TEST_MAIN */

