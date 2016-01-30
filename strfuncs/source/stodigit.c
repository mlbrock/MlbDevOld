/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	STRFUNCS String and Memory Functions Library Module							*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Octal digit character class functions.

	Revision History	:	1995-08-07 --- Creation
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

#include <stdio.h>

#include "strfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	str_odigit

	SYNOPSIS		:	return_ptr = str_odigit(in_string, sense_flag);

						char       *return_ptr;

						const char *in_string;

						int         sense_flag;

	DESCRIPTION	:	Returns a pointer to the first (non-) octal digit
						character within a string.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_string`` is the string in which the search is
						to be performed.

						(.) ``sense_flag`` specifies the sense of the search to
						be performed.

						(..) If ``sense_flag`` is non-zero, then this function will
						locate the first octal digit character in ``in_string``.

						(..) If ``sense_flag`` is zero, then this function will
						locate the first non-octal digit character in
						``in_string``.

	RETURNS		:	Returns from this function are as follow:

						(.) If a character of the desired type is within the string,
						a pointer to the first character of that type is returned.

						(.) Otherwise, a ''NULL'' pointer is returned.

	NOTES			:	An octal digit character is a digit in the inclusive range
						''0'' through ''7''. It is defined as:

						(-) (isdigit(chr) && (chr != '8') && (chr != '9'))

						An octal digit character is one for which the macro
						``isodigit`` returns a non-zero value.

	CAVEATS		:	

	SEE ALSO		:	strr_odigit
						idx_odigit
						str_alnum
						str_alpha
						str_ascii
						str_bdigit
						str_cntrl
						str_csym
						str_csymf
						str_digit
						str_graph
						str_lower
						str_print
						str_punct
						str_space
						str_upper
						str_xdigit

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2016 Michael L. Brock

	OUTPUT INDEX:	str_odigit
						Character Class Functions:Octal Digit Character Class Functions:str_odigit
						STRFUNCS:Character Class Functions:Octal Digit Character Class Functions:str_odigit
						Character Class Functions:Search Functions/Pointer:str_odigit
						STRFUNCS:Character Class Functions:Search Functions/Pointer:str_odigit
						String Functions:See STRFUNCS

	PUBLISH XREF:	str_odigit

	PUBLISH NAME:	str_odigit

	ENTRY CLASS	:	Character Class Functions:Octal Digit Character Class Functions
						Character Class Functions:Search Functions/Pointer

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *str_odigit(const char *in_string, int sense_flag)
#else
char *str_odigit(in_string, sense_flag)
const char *in_string;
int         sense_flag;
#endif /* #ifndef NARGS */
{
	sense_flag = (sense_flag) ? 1 : 0;

	while (*in_string) {
		if (((isodigit(*in_string)) ? 1 : 0) == sense_flag)
			return(((char *) in_string));
		in_string++;
	}

	return(NULL);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	strr_odigit

	SYNOPSIS		:	return_ptr = strr_odigit(in_string, sense_flag);

						char       *return_ptr;

						const char *in_string;

						int         sense_flag;

	DESCRIPTION	:	Returns a pointer to the last (non-) octal digit
						character within a string.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_string`` is the string in which the search is
						to be performed.

						(.) ``sense_flag`` specifies the sense of the search to
						be performed.

						(..) If ``sense_flag`` is non-zero, then this function will
						locate the last octal digit character in ``in_string``.

						(..) If ``sense_flag`` is zero, then this function will
						locate the last non-octal digit character in
						``in_string``.

	RETURNS		:	Returns from this function are as follow:

						(.) If a character of the desired type is within the string,
						a pointer to the last character of that type is returned.

						(.) Otherwise, a ''NULL'' pointer is returned.

	NOTES			:	An octal digit character is a digit in the inclusive range
						''0'' through ''7''. It is defined as:

						(-) (isdigit(chr) && (chr != '8') && (chr != '9'))

						An octal digit character is one for which the macro
						``isodigit`` returns a non-zero value.

	CAVEATS		:	

	SEE ALSO		:	str_odigit
						idxr_odigit
						strr_alnum
						strr_alpha
						strr_ascii
						strr_bdigit
						strr_cntrl
						strr_csym
						strr_csymf
						strr_digit
						strr_graph
						strr_lower
						strr_print
						strr_punct
						strr_space
						strr_upper
						strr_xdigit

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2016 Michael L. Brock

	OUTPUT INDEX:	strr_odigit
						Character Class Functions:Octal Digit Character Class Functions:strr_odigit
						STRFUNCS:Character Class Functions:Octal Digit Character Class Functions:strr_odigit
						Character Class Functions:Search Functions/Pointer:strr_odigit
						STRFUNCS:Character Class Functions:Search Functions/Pointer:strr_odigit
						String Functions:See STRFUNCS

	PUBLISH XREF:	strr_odigit

	PUBLISH NAME:	strr_odigit

	ENTRY CLASS	:	Character Class Functions:Octal Digit Character Class Functions
						Character Class Functions:Search Functions/Pointer

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *strr_odigit(const char *in_string, int sense_flag)
#else
char *strr_odigit(in_string, sense_flag)
const char *in_string;
int         sense_flag;
#endif /* #ifndef NARGS */
{
	char *tmp_ptr = NULL;

	sense_flag = (sense_flag) ? 1 : 0;

	while (*in_string) {
		if (((isodigit(*in_string)) ? 1 : 0) == sense_flag)
			tmp_ptr = ((char *) in_string);
		in_string++;
	}

	return(tmp_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	idx_odigit

	SYNOPSIS		:	return_index = idx_odigit(in_string, sense_flag);

						int         return_index;

						const char *in_string;

						int         sense_flag;

	DESCRIPTION	:	Returns the index of the first (non-) octal digit
						character within a string.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_string`` is the string in which the search is
						to be performed.

						(.) ``sense_flag`` specifies the sense of the search to
						be performed.

						(..) If ``sense_flag`` is non-zero, then this function will
						locate the first octal digit character in ``in_string``.

						(..) If ``sense_flag`` is zero, then this function will
						locate the first non-octal digit character in
						``in_string``.

	RETURNS		:	Returns from this function are as follow:

						(.) If a character of the desired type is within the string,
						the index of the first character of that type is returned.

						(.) Otherwise, ''-1'' is returned.

	NOTES			:	An octal digit character is a digit in the inclusive range
						''0'' through ''7''. It is defined as:

						(-) (isdigit(chr) && (chr != '8') && (chr != '9'))

						An octal digit character is one for which the macro
						``isodigit`` returns a non-zero value.

	CAVEATS		:	This function returns a ``signed int`` and therefore cannot
						accurately represent indices greater than that defined
						by the manifest constant ''INT_MAX''. You have been
						warned.

	SEE ALSO		:	str_odigit
						idxr_odigit
						idx_alnum
						idx_alpha
						idx_ascii
						idx_bdigit
						idx_cntrl
						idx_csym
						idx_csymf
						idx_digit
						idx_graph
						idx_lower
						idx_print
						idx_punct
						idx_space
						idx_upper
						idx_xdigit

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2016 Michael L. Brock

	OUTPUT INDEX:	idx_odigit
						Character Class Functions:Octal Digit Character Class Functions:idx_odigit
						STRFUNCS:Character Class Functions:Octal Digit Character Class Functions:idx_odigit
						Character Class Functions:Search Functions/Index:idx_odigit
						STRFUNCS:Character Class Functions:Search Functions/Index:idx_odigit
						String Functions:See STRFUNCS

	PUBLISH XREF:	idx_odigit

	PUBLISH NAME:	idx_odigit

	ENTRY CLASS	:	Character Class Functions:Octal Digit Character Class Functions
						Character Class Functions:Search Functions/Index

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int idx_odigit(const char *in_string, int sense_flag)
#else
int idx_odigit(in_string, sense_flag)
const char *in_string;
int         sense_flag;
#endif /* #ifndef NARGS */
{
	char *tmp_ptr;

	return(((tmp_ptr = str_odigit(in_string, sense_flag)) == NULL) ? -1 :
		((int) (((const char *) tmp_ptr) - in_string)));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	idxr_odigit

	SYNOPSIS		:	return_index = idxr_odigit(in_string, sense_flag);

						int         return_index;

						const char *in_string;

						int         sense_flag;

	DESCRIPTION	:	Returns the index of the last (non-) octal digit
						character within a string.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_string`` is the string in which the search is
						to be performed.

						(.) ``sense_flag`` specifies the sense of the search to
						be performed.

						(..) If ``sense_flag`` is non-zero, then this function will
						locate the last octal digit character in ``in_string``.

						(..) If ``sense_flag`` is zero, then this function will
						locate the last non-octal digit character in
						``in_string``.

	RETURNS		:	Returns from this function are as follow:

						(.) If a character of the desired type is within the string,
						the index of the last character of that type is returned.

						(.) Otherwise, ''-1'' is returned.

	NOTES			:	An octal digit character is a digit in the inclusive range
						''0'' through ''7''. It is defined as:

						(-) (isdigit(chr) && (chr != '8') && (chr != '9'))

						An octal digit character is one for which the macro
						``isodigit`` returns a non-zero value.

	CAVEATS		:	This function returns a ``signed int`` and therefore cannot
						accurately represent indices greater than that defined
						by the manifest constant ''INT_MAX''. You have been
						warned.

	SEE ALSO		:	strr_odigit
						idx_odigit
						idxr_alnum
						idxr_alpha
						idxr_ascii
						idxr_bdigit
						idxr_cntrl
						idxr_csym
						idxr_csymf
						idxr_digit
						idxr_graph
						idxr_lower
						idxr_print
						idxr_punct
						idxr_space
						idxr_upper
						idxr_xdigit

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2016 Michael L. Brock

	OUTPUT INDEX:	idxr_odigit
						Character Class Functions:Octal Digit Character Class Functions:idxr_odigit
						STRFUNCS:Character Class Functions:Octal Digit Character Class Functions:idxr_odigit
						Character Class Functions:Search Functions/Index:idxr_odigit
						STRFUNCS:Character Class Functions:Search Functions/Index:idxr_odigit
						String Functions:See STRFUNCS

	PUBLISH XREF:	idxr_odigit

	PUBLISH NAME:	idxr_odigit

	ENTRY CLASS	:	Character Class Functions:Octal Digit Character Class Functions
						Character Class Functions:Search Functions/Index

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int idxr_odigit(const char *in_string, int sense_flag)
#else
int idxr_odigit(in_string, sense_flag)
const char *in_string;
int         sense_flag;
#endif /* #ifndef NARGS */
{
	char *tmp_ptr;

	return(((tmp_ptr = strr_odigit(in_string, sense_flag)) == NULL) ? -1 :
		((int) (((const char *) tmp_ptr) - in_string)));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	cnt_odigit

	SYNOPSIS		:	return_count = cnt_odigit(in_string, sense_flag);

						unsigned int  return_count;

						const char   *in_string;

						int           sense_flag;

	DESCRIPTION	:	Returns the number of (non-) octal digit characters
						within a string.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_string`` is the string in which the count is
						to be performed.

						(.) ``sense_flag`` specifies the sense of the count to
						be performed.

						(..) If ``sense_flag`` is non-zero, then this function will
						count the number of octal digit characters in
						``in_string``.

						(..) If ``sense_flag`` is zero, then this function will
						count the number of non-octal digit characters in
						``in_string``.

	RETURNS		:	Returns the number of characters of the desired type within
						the string.

	NOTES			:	An octal digit character is a digit in the inclusive range
						''0'' through ''7''. It is defined as:

						(-) (isdigit(chr) && (chr != '8') && (chr != '9'))

						An octal digit character is one for which the macro
						``isodigit`` returns a non-zero value.

	CAVEATS		:	

	SEE ALSO		:	cnt_alnum
						cnt_alpha
						cnt_ascii
						cnt_bdigit
						cnt_cntrl
						cnt_csym
						cnt_csymf
						cnt_digit
						cnt_graph
						cnt_lower
						cnt_print
						cnt_punct
						cnt_space
						cnt_upper
						cnt_xdigit

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2016 Michael L. Brock

	OUTPUT INDEX:	cnt_odigit
						Character Class Functions:Octal Digit Character Class Functions:cnt_odigit
						STRFUNCS:Character Class Functions:Octal Digit Character Class Functions:cnt_odigit
						Character Class Functions:Count Functions:cnt_odigit
						STRFUNCS:Character Class Functions:Count Functions:cnt_odigit
						String Functions:See STRFUNCS

	PUBLISH XREF:	cnt_odigit

	PUBLISH NAME:	cnt_odigit

	ENTRY CLASS	:	Character Class Functions:Octal Digit Character Class Functions
						Character Class Functions:Count Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
unsigned int cnt_odigit(const char *in_string, int sense_flag)
#else
unsigned int cnt_odigit(in_string, sense_flag)
const char *in_string;
int         sense_flag;
#endif /* #ifndef NARGS */
{
	unsigned int count = 0;

	sense_flag = (sense_flag) ? 1 : 0;

	while (*in_string) {
		count += (((isodigit(*in_string)) ? 1 : 0) == sense_flag) ? 1 : 0;
		in_string++;
	}

	return(count);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	cvt_odigit

	SYNOPSIS		:	return_ptr = cvt_odigit(in_string, conversion_char,
							sense_flag);

						char       *return_ptr;

						const char *in_string;

						int         conversion_char;

						int         sense_flag;

	DESCRIPTION	:	Converts all (non-) octal digit characters within a
						string to a specified character.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_string`` is the string in which the conversion is
						to be performed.

						(.) ``conversion_char`` is the character to which those
						characters of the desired type within ``in_string`` are to
						be converted.

						(.) ``sense_flag`` specifies the sense of the conversion to
						be performed.

						(..) If ``sense_flag`` is non-zero, then this function will
						convert octal digit characters in ``in_string``.

						(..) If ``sense_flag`` is zero, then this function will
						convert non-octal digit characters in ``in_string``.

	RETURNS		:	A pointer to the string used as input.

	NOTES			:	An octal digit character is a digit in the inclusive range
						''0'' through ''7''. It is defined as:

						(-) (isdigit(chr) && (chr != '8') && (chr != '9'))

						An octal digit character is one for which the macro
						``isodigit`` returns a non-zero value.

	CAVEATS		:	

	SEE ALSO		:	cvt_alnum
						cvt_alpha
						cvt_ascii
						cvt_bdigit
						cvt_cntrl
						cvt_csym
						cvt_csymf
						cvt_digit
						cvt_graph
						cvt_lower
						cvt_print
						cvt_punct
						cvt_space
						cvt_upper
						cvt_xdigit

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2016 Michael L. Brock

	OUTPUT INDEX:	cvt_odigit
						Character Class Functions:Octal Digit Character Class Functions:cvt_odigit
						STRFUNCS:Character Class Functions:Octal Digit Character Class Functions:cvt_odigit
						Character Class Functions:Conversion Functions:cvt_odigit
						STRFUNCS:Character Class Functions:Conversion Functions:cvt_odigit
						String Functions:See STRFUNCS

	PUBLISH XREF:	cvt_odigit

	PUBLISH NAME:	cvt_odigit

	ENTRY CLASS	:	Character Class Functions:Octal Digit Character Class Functions
						Character Class Functions:Conversion Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *cvt_odigit(char *in_string, int conversion_char, int sense_flag)
#else
char *cvt_odigit(in_string, conversion_char, sense_flag)
char *in_string;
int   conversion_char;
int   sense_flag;
#endif /* #ifndef NARGS */
{
	char *tmp_ptr = in_string;

	sense_flag = (sense_flag) ? 1 : 0;

	while (*in_string) {
		if (((isodigit(*in_string)) ? 1 : 0) == sense_flag)
			*in_string = ((char) conversion_char);
		in_string++;
	}

	return(tmp_ptr);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <string.h>

COMPAT_FN_DECL(int main, (int argc, char **argv));

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int   return_code = -1;
	int   count_1;
	int   count_2;
	char *tmp_ptr;
	char  buffer[512];

	printf("Test of extended string odigit functions\n");
	printf("---- -- -------- ------ ------ ---------\n\n");

	if (argc < 2)
		printf(" --- command-line arguments are required for test.\n");
	else {
		printf("=================================================\n");
		for (count_1 = 1; count_1 < argc; count_1++) {
			for (count_2 = 1; count_2 >= 0; count_2--) {
				strcpy(buffer, argv[count_1]);
				printf("STRING:\"%s\"%s\n", buffer,
					(!count_2) ? " (reverse sense)" : "");
				printf(">>> 'str_odigit()'  = ");
				if ((tmp_ptr = str_odigit(buffer, count_2)) == NULL)
					printf("NOT FOUND\n");
				else
					printf("FOUND (beginning at '%s')\n", tmp_ptr);
				printf(">>> 'strr_odigit()' = ");
				if ((tmp_ptr = strr_odigit(buffer, count_2)) == NULL)
					printf("NOT FOUND\n");
				else
					printf("FOUND (beginning at '%s')\n", tmp_ptr);
				printf(">>> 'idx_odigit()'  = %d\n",
					idx_odigit(buffer, count_2));
				printf(">>> 'idxr_odigit()' = %d\n",
					idxr_odigit(buffer, count_2));
				printf(">>> 'cnt_odigit()'  = %u\n",
					cnt_odigit(buffer, count_2));
				printf(">>> 'cvt_odigit()'  = %s\n",
					cvt_odigit(buffer, '_', count_2));
				if (count_2)
					printf("-------------------------------------------------\n");
			}
			printf("=================================================\n");
		}
		return_code = 0;
	}

	return(return_code);
}
/*	***********************************************************************	*/

#endif /* #ifdef TEST_MAIN */

