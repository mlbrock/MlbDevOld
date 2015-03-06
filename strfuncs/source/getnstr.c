/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Determines the portion of a string which contains a
								valid numeric value.

	Revision History	:	1996-02-08 --- Creation
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

#include <ctype.h>
#include <string.h>

#include "strfunci.h"

/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	getnumstr

	SYNOPSIS		:	truth_flag = getnumstr(in_string, decimal_point,
							new_start_index, new_end_index);

						int           truth_flag;

						const char   *in_string;

						const char   *decimal_point;

						unsigned int *new_start_index;

						unsigned int *new_end_index;

	DESCRIPTION	:	Determines the portion of a null-terminated string which
						contains a valid numeric value.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_string`` is a pointer to the null-terminated string
						to be examined to determine the presence of a number.

						(.) ``decimal_point`` is points to the single character
						which is used to separate the whole portion of a number
						from its fractional portion.

						(-) If ``decimal_point`` is ''NULL'', the period character
						(''.'') will be used.

						(.) ``new_start_index`` is a pointer to an ''unsigned int''
						into which this function will place the position of the
						first character of ``in_string`` which constitutes the
						number.

						(-) ``new_start_index`` will not be de-referenced if it is
						''NULL''.

						(-) If, when this function returns, the ''unsigned int'' to
						which ``new_start_index`` points is not equal to the
						value ''0'', then the function encountered leading
						white-space.

						(.) ``new_end_index`` is a pointer to an ''unsigned int''
						into which this function will place the position of the last
						character of ``in_string`` which constitutes the number.

						(-) ``new_end_index`` will not be de-referenced if it is
						''NULL''.

   RETURNS     :  Returns from this function are as follow:

						(.) The manifest constant ''STRFUNCS_TRUE'' if the string
						contains a valid number.

						(.) Otherwise, the manifest constant ''STRFUNCS_FALSE'' is
						returned.

	NOTES			:	If the string you want to use as a parameter is not
						null-terminated, use the related function
						``getnumstr_basic``.

						In cases where this function returns ''STRFUNCS_FALSE'', the
						''unsigned int'' to which the ``new_end_index`` parameter
						points can be used to determing the offset of the offending
						character within ``in_string``.

	CAVEATS		:	

	SEE ALSO		:	getnumstr_basic

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2015 Michael L. Brock
 
	OUTPUT INDEX:	
						Miscellaneous Functions:getnumstr
						STRFUNCS:Miscellaneous Functions:getnumstr
						String Functions:See STRFUNCS

	PUBLISH XREF:	getnumstr

	PUBLISH NAME:	getnumstr

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int getnumstr(const char *in_string, const char *decimal_point,
	unsigned int *new_start_index, unsigned int *new_end_index)
#else
int getnumstr(in_string, decimal_point, new_start_index, new_end_index)
const char   *in_string;
const char   *decimal_point;
unsigned int *new_start_index;
unsigned int *new_end_index;
#endif /* #ifndef NARGS */
{
	return((*in_string) ? getnumstr_basic(in_string, 0, strlen(in_string) - 1,
		decimal_point, new_start_index, new_end_index) : STRFUNCS_FALSE);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	getnumstr_basic

	SYNOPSIS		:	truth_flag = getnumstr_basic(in_string, start_index,
							end_index, decimal_point, new_start_index,
							new_end_index);

						int           truth_flag;

						const char   *in_string;

						unsigned int  start_index;

						unsigned int  end_index;

						const char   *decimal_point;

						unsigned int *new_start_index;

						unsigned int *new_end_index;

	DESCRIPTION	:	Determines the portion of a string which contains a valid
						numeric value.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_string`` is a pointer to the string to be examined
						to determine the presence of a number.

						(.) ``start_index`` is the first position within
						``in_string`` this function is to examine.

						(.) ``end_index`` is the last position within ``in_string``
						this function is to examine.

						(.) ``decimal_point`` is points to the single character
						which is used to separate the whole portion of a number
						from its fractional portion.

						(-) If ``decimal_point`` is ''NULL'', the period character
						(''.'') will be used.

						(.) ``new_start_index`` is a pointer to an ''unsigned int''
						into which this function will place the position of the
						first character of ``in_string`` which constitutes the
						number.

						(-) ``new_start_index`` will not be de-referenced if it is
						''NULL''.

						(-) If, when this function returns, the ''unsigned int'' to
						which ``new_start_index`` points is not equal to the
						value passed in the ``start_index`` parameter, then the
						function encountered leading white-space.

						(.) ``new_end_index`` is a pointer to an ''unsigned int''
						into which this function will place the position of the last
						character of ``in_string`` which constitutes the number.

						(-) ``new_end_index`` will not be de-referenced if it is
						''NULL''.

   RETURNS     :  Returns from this function are as follow:

						(.) The manifest constant ''STRFUNCS_TRUE'' if the string
						contains a valid number.

						(.) Otherwise, the manifest constant ''STRFUNCS_FALSE'' is
						returned.

	NOTES			:	In cases where this function returns ''STRFUNCS_FALSE'', the
						''unsigned int'' to which the ``new_end_index`` parameter
						points can be used to determing the offset of the offending
						character within ``in_string``.

	CAVEATS		:	

	SEE ALSO		:	getnumstr

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2015 Michael L. Brock
 
	OUTPUT INDEX:	
						Miscellaneous Functions:getnumstr_basic
						STRFUNCS:Miscellaneous Functions:getnumstr_basic
						String Functions:See STRFUNCS

	PUBLISH XREF:	getnumstr_basic

	PUBLISH NAME:	getnumstr_basic

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int getnumstr_basic(const char *in_string, unsigned int start_index,
	unsigned int end_index, const char *decimal_point,
	unsigned int *new_start_index, unsigned int *new_end_index)
#else
int getnumstr_basic(in_string, start_index, end_index, decimal_point,
	new_start_index, new_end_index)
const char   *in_string;
unsigned int  start_index;
unsigned int  end_index;
const char   *decimal_point;
unsigned int *new_start_index;
unsigned int *new_end_index;
#endif /* #ifndef NARGS */
{
	int           number_flag = STRFUNCS_FALSE;
	const char   *current_ptr = in_string + start_index;
	unsigned int  tmp_start;
	unsigned int  tmp_end;

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Default parameter values:													*/
	/*																							*/
	/*			1)	If 'new_start_index' is 'NULL', use a local variable.		*/
	/*																							*/
	/*			2)	If 'new_end_index' is 'NULL', use a local variable.		*/
	/*																							*/
	/*			3) If 'decimal_point' is 'NULL', use '.'.							*/
	/*																							*/
	/*	*****************************************************************	*/
	new_start_index  = (new_start_index == NULL) ? &tmp_start : new_start_index;
	*new_start_index = start_index;
	new_end_index    = (new_end_index == NULL)   ? &tmp_end   : new_end_index;
	*new_end_index   = start_index;
	decimal_point    = (decimal_point == NULL) ? "." : decimal_point;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Skip over leading white-space . . .										*/
	/*	*****************************************************************	*/
	while ((*new_end_index <= end_index) && isspace(*current_ptr)) {
		(*new_start_index)++;
		(*new_end_index)++;
		current_ptr++;
	}
	if (*new_end_index > end_index)
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		A leading sign is permitted . . .										*/
	/*	*****************************************************************	*/
	if ((*new_end_index <= end_index) &&
		((*current_ptr == '+') || (*current_ptr == '-'))) {
		(*new_end_index)++;
		current_ptr++;
	}
	if (*new_end_index > end_index)
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		For as long as we have digits . . .										*/
	/*	*****************************************************************	*/
	while (*new_end_index <= end_index) {
		if (!isdigit(*current_ptr))
			break;
		number_flag = STRFUNCS_TRUE;
		(*new_end_index)++;
		current_ptr++;
	}
	if (*new_end_index > end_index)
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Might have a decimal point . . .											*/
	/*	*****************************************************************	*/
	if (*current_ptr == *decimal_point) {
		if (++(*new_end_index) > end_index)
			goto EXIT_FUNCTION;
		current_ptr++;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		This would be the fractional portion of the number . . .			*/
	/*	*****************************************************************	*/
	while (*new_end_index <= end_index) {
		if (!isdigit(*current_ptr))
			break;
		number_flag = STRFUNCS_TRUE;
		(*new_end_index)++;
		current_ptr++;
	}
	if ((*new_end_index > end_index) || (number_flag != STRFUNCS_TRUE))
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		There could, of course, be an exponential portion . . .			*/
	/*	*****************************************************************	*/
	if (((*new_end_index + 2) <= end_index) &&
		((*current_ptr == 'e') || (*current_ptr == 'E')) &&
		((current_ptr[1] == '+') || (current_ptr[1] == '-')) &&
		isdigit(current_ptr[2])) {
		*new_end_index += 3;
		current_ptr    += 3;
		while (*new_end_index <= end_index) {
			if (!isdigit(*current_ptr))
				break;
			(*new_end_index)++;
			current_ptr++;
		}
	}
	/*	*****************************************************************	*/

EXIT_FUNCTION:

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		This ends up pointing one beyond, so fix it . . .					*/
	/*	*****************************************************************	*/
	(*new_end_index)--;
	/*	*****************************************************************	*/

	return(number_flag);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <stdio.h>

COMPAT_FN_DECL(int main, (int argc, char **argv));

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
	unsigned int new_start_index;
	unsigned int new_end_index;

	STR_EMIT_CharLine('=', 78, NULL, NULL);
	STR_EMIT_CharLine('=', 78, NULL, NULL);

	fprintf(stderr, "Test routine for 'getnumstr_basic()'\n");
	fprintf(stderr, "---- ------- --- -------------------\n");

	STR_EMIT_CharLine('=', 78, NULL, NULL);

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		STR_EMIT_CharLine('=', 78, NULL, NULL);
		printf("STRING: [%s]\n", argv[count_1]);
		STR_EMIT_CharLine('-', 78, NULL, NULL);
		if (getnumstr(argv[count_1], ".", &new_start_index, &new_end_index) ==
			STRFUNCS_TRUE) {
			printf("NUMBER: ");
			if (new_start_index)
				printf("[%*.*s]",
					new_start_index, ((int) new_start_index), argv[count_1]);
			else
				printf("[]");
			printf("[%-*.*s]",
				((int) ((new_end_index - new_start_index) + 1)),
				((int) ((new_end_index - new_start_index) + 1)),
				argv[count_1] + new_start_index);
			if (new_end_index < (strlen(argv[count_1]) - 1))
				printf("[%s]\n", argv[count_1] + new_end_index + 1);
			else
				printf("[]\n");
		}
		else
			printf("Not a number.\n");
		STR_EMIT_CharLine('=', 78, NULL, NULL);
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

