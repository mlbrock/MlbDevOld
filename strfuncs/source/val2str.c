/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Converts an unsigned long to a string in the specified
								radix.

	Revision History	:	1993-10-02 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */
 
/* *********************************************************************** */
/* *********************************************************************** */
/*    Necessary include files . . .                                        */
/* *********************************************************************** */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/*	Data private to this module . . .													*/
/* *********************************************************************** */

static unsigned int  STRFUNCS_RadixCharCount = 64;
static const char   *STRFUNCS_RadixCharList  =
	"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz@#";

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	val2str

	SYNOPSIS		:	return_ptr = val2str(in_value, in_sign, in_radix,
							in_fill_char, out_string);

						char          *return_ptr;

						unsigned long  in_value;

						int            in_sign;

						unsigned int   in_radix;

						const char    *in_fill_char;

						char          *out_string;

	DESCRIPTION	:	Converts an ``unsigned long`` into a string using the
						specified radix.

						The resulting string is placed into the buffer to which the
						``out_string`` parameter points.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_value`` is the value to be converted. It is
						always passed as an ``unsigned long``, even for negative
						values.

						(.) ``in_sign`` is the sign to be used in the resulting
						conversion. If less than zero, then a minus sign (''-'')
						will be prepended to the resulting string.

						(.) ``in_radix`` is the radix to be used for the resulting
						string. It must be in the range of ''2'' through ''64'',
						inclusive.

						(.) ``in_fill_char`` points to the character to be used to
						left-pad the resulting string. If this parameter is ''NULL''
						or points to a zero-length string, the string will not be
						padded.

						(.) ``out_string`` points to the area into which the
						resulting string will be placed. Its minimum length to
						support an arbitrary ``in_radix`` and ``in_sign`` should be:

						(--) (sizeof(unsigned long) * CHAR_BIT) + 1 + 1

						(-) This permits the storage of the longest string returned
						by this function, including ASCII NULL-terminator.

   RETURNS     :  Returns from this function are as follow:

						(.) If no error occurs, a pointer to the string
						``out_string`` is returned.

						(.) If an error occurs, a ''NULL'' pointer is returned.

	NOTES			:	The only error which can occur in the operation of this
						function is the passing of an invalid ``in_radix``
						parameter.

	CAVEATS		:	Using a space as a fill character with a negative sign may
						results other than those intended. For example, the
						following invocation:

{|@|}printf("%s\n", val2str(1234L, -1, 10, ' ', out_string));

						results in:

{|@|}-       1234

	SEE ALSO		:	val2str_cat
						val2str_basic

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2014 Michael L. Brock

	OUTPUT INDEX:	val2str
						Miscellaneous Functions:val2str
						STRFUNCS:Miscellaneous Functions:val2str
						String Functions:See STRFUNCS

	PUBLISH XREF:	val2str

	PUBLISH NAME:	val2str

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *val2str(unsigned long in_value, int in_sign, unsigned int in_radix,
	const char *in_fill_char, char *out_string)
#else
char *val2str(in_value, in_sign, in_radix, in_fill_char, out_string)
unsigned long  in_value;
int            in_sign;
unsigned int   in_radix;
const char    *in_fill_char;
char          *out_string;
#endif /* #ifndef NARGS */
{
	return(val2str_basic(0, NULL, in_value, in_sign, in_radix, in_fill_char,
		out_string));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	val2str_cat

	SYNOPSIS		:	return_ptr = val2str_cat(in_value, in_sign, in_radix,
							in_fill_char, out_string);

						char          *return_ptr;

						unsigned long  in_value;

						int            in_sign;

						unsigned int   in_radix;

						const char    *in_fill_char;

						char          *out_string;

	DESCRIPTION	:	Converts an ``unsigned long`` into a string using the
						specified radix.

						The resulting string is concatenated onto the string to
						which the ``out_string`` parameter points.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_value`` is the value to be converted. It is
						always passed as an ``unsigned long``, even for negative
						values.

						(.) ``in_sign`` is the sign to be used in the resulting
						conversion. If less than zero, then a minus sign (''-'')
						will be prepended to the resulting string.

						(.) ``in_radix`` is the radix to be used for the resulting
						string. It must be in the range of ''2'' through ''64'',
						inclusive.

						(.) ``in_fill_char`` points to the character to be used to
						left-pad the resulting string. If this parameter is ''NULL''
						or points to a zero-length string, the string will not be
						padded.

						(.) ``out_string`` points to the area into which the
						resulting string will be placed. Its minimum length to
						support an arbitrary ``in_radix`` and ``in_sign`` should be:

						(--) (sizeof(unsigned long) * CHAR_BIT) + 1 + 1

						(-) This permits the storage of the longest string returned
						by this function, including ASCII NULL-terminator.

   RETURNS     :  Returns from this function are as follow:

						(.) If no error occurs, a pointer to the string
						``out_string`` is returned.

						(.) If an error occurs, a ''NULL'' pointer is returned.

	NOTES			:	The only error which can occur in the operation of this
						function is the passing of an invalid ``in_radix``
						parameter.

	CAVEATS		:	Using a space as a fill character with a negative sign may
						results other than those intended. For example, the
						following invocation:

{|@|}printf("%s\n", val2str_cat(1234L, -1, 10, ' ',
	strcpy(out_string, "The value is: ")));

						results in:

{|@|}The value is: -       1234

	SEE ALSO		:	val2str
						val2str_basic_cat

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2014 Michael L. Brock

	OUTPUT INDEX:	val2str_cat
						Miscellaneous Functions:val2str_cat
						STRFUNCS:Miscellaneous Functions:val2str_cat
						String Functions:See STRFUNCS

	PUBLISH XREF:	val2str_cat

	PUBLISH NAME:	val2str_cat

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *val2str_cat(unsigned long in_value, int in_sign, unsigned int in_radix,
	const char *in_fill_char, char *out_string)
#else
char *val2str_cat(in_value, in_sign, in_radix, in_fill_char, out_string)
unsigned long  in_value;
int            in_sign;
unsigned int   in_radix;
const char    *in_fill_char;
char          *out_string;
#endif /* #ifndef NARGS */
{
	return(val2str_basic_cat(0, NULL, in_value, in_sign, in_radix,
		in_fill_char, out_string));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	val2str_basic

	SYNOPSIS		:	return_ptr = val2str_basic(radix_char_count, radix_char_list,
							in_value, in_sign, in_radix, in_fill_char, out_string);

						char          *return_ptr;

						unsigned int   radix_char_count;

						const char    *radix_char_list;

						unsigned long  in_value;

						int            in_sign;

						unsigned int   in_radix;

						const char    *in_fill_char;

						char          *out_string;

	DESCRIPTION	:	Converts an ``unsigned long`` into a string using the
						specified radix.

						The resulting string is placed into the buffer to which the
						``out_string`` parameter points.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``radix_char_count`` is the number of characters in the
						array ``radix_char_list``. It represents the maximum radix
						which can be converted by this function.

						(-) If ``radix_char_count`` is ''0'', the value ''64'' will
						be used by this function.

						(.) ``radix_char_list`` is the list of characters to be
						used in the conversion.

						(-) If the ``radix_char_count`` parameter is ''0'', this
						function will use the following string:

{|-|}"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz@#"

						(-) If the ``radix_char_count`` parameter is less than or
						equal to ''64'' and ``radix_char_list`` is ''NULL'',
						``radix_char_list`` will be set to the string above.

						(.) ``in_value`` is the value to be converted. It is
						always passed as an ``unsigned long``, even for negative
						values.

						(.) ``in_sign`` is the sign to be used in the resulting
						conversion. If less than zero, then a minus sign (''-'')
						will be prepended to the resulting string.

						(.) ``in_radix`` is the radix to be used for the resulting
						string. It must be in the range of ''2'' through the value
						if the ``radix_char_count`` parameter, inclusive.

						(.) ``in_fill_char`` points to the character to be used to
						left-pad the resulting string. If this parameter is ''NULL''
						or points to a zero-length string, the string will not be
						padded.

						(.) ``out_string`` points to the area into which the
						resulting string will be placed. Its minimum length to
						support an arbitrary ``in_radix`` and ``in_sign`` should be:

						(--) 1 + (sizeof(unsigned long) * CHAR_BIT) + 1

						(-) This permits the storage of the longest string returned
						by this function, including ASCII NULL-terminator.

   RETURNS     :  Returns from this function are as follow:

						(.) If no error occurs, a pointer to the string
						``out_string`` is returned.

						(.) If an error occurs, a ''NULL'' pointer is returned.

	NOTES			:	The only error which can occur in the operation of this
						function is the passing of an invalid ``in_radix``
						parameter.

	CAVEATS		:	

	SEE ALSO		:	val2str
						val2str_basic_cat

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2014 Michael L. Brock

	OUTPUT INDEX:	val2str_basic
						Miscellaneous Functions:val2str_basic
						STRFUNCS:Miscellaneous Functions:val2str_basic
						String Functions:See STRFUNCS

	PUBLISH XREF:	val2str_basic

	PUBLISH NAME:	val2str_basic

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *val2str_basic(unsigned int radix_char_count, const char *radix_char_list,
	unsigned long in_value, int in_sign, unsigned int in_radix,
	const char *in_fill_char, char *out_string)
#else
char *val2str_basic(radix_char_count, radix_char_list, in_value, in_sign,
	in_radix, in_fill_char, out_string)
unsigned int   radix_char_count;
const char    *radix_char_list;
unsigned long  in_value;
int            in_sign;
unsigned int   in_radix;
const char    *in_fill_char;
char          *out_string;
#endif /* #ifndef NARGS */
{
	unsigned long  power_value;
	unsigned long  old_power_value;
	char          *tmp_ptr_1;
	char          *tmp_ptr_2;
	char           buffer[STR_VAL2STR_MAX_LEN + 1];

	if (!radix_char_count) {
		radix_char_count = STRFUNCS_RadixCharCount;
		radix_char_list  = STRFUNCS_RadixCharList;
	}
	else if ((radix_char_count <= STRFUNCS_RadixCharCount) &&
		(radix_char_list == NULL))
		radix_char_list = STRFUNCS_RadixCharList;

	power_value     = in_radix;
	old_power_value = 0;
	tmp_ptr_1       = out_string;
	tmp_ptr_2       = buffer + (sizeof(unsigned long) * CHAR_BIT) + 1;

	if ((in_radix < 2) || (in_radix > radix_char_count))
		out_string = NULL;
	else {
		*tmp_ptr_2-- = '\0';
		*tmp_ptr_2-- = radix_char_list[((unsigned int) (in_value %
			((unsigned long) in_radix)))];
		in_fill_char = ((in_fill_char != NULL) && (!(*in_fill_char))) ?
			NULL : in_fill_char;
		while (power_value > old_power_value) {
			if (in_value >= power_value)
				*tmp_ptr_2-- =
					radix_char_list[((unsigned int) ((in_value /
						power_value) % ((unsigned long) in_radix)))];
			else if (in_fill_char != NULL)
				*tmp_ptr_2-- = *in_fill_char;
			else
				break;
			if ((ULONG_MAX / power_value) < in_radix)
         	break;
			old_power_value  = power_value;
			power_value     *= in_radix;
		}
		if (in_sign < 0)
			*tmp_ptr_2-- = '-';
		tmp_ptr_2++;
		do { *tmp_ptr_1++ = *tmp_ptr_2; } while (*tmp_ptr_2++);
	}

	return(out_string);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	val2str_basic_cat

	SYNOPSIS		:	return_ptr = val2str_basic_cat(radix_char_count,
							radix_char_list, in_value, in_sign, in_radix,
							in_fill_char, out_string);

						char          *return_ptr;

						unsigned int   radix_char_count;

						const char    *radix_char_list;

						unsigned long  in_value;

						int            in_sign;

						unsigned int   in_radix;

						const char    *in_fill_char;

						char          *out_string;

	DESCRIPTION	:	Converts an ``unsigned long`` into a string using the
						specified radix.

						The resulting string is concatenated onto the string to
						which the ``out_string`` parameter points.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``radix_char_count`` is the number of characters in the
						array ``radix_char_list``. It represents the maximum radix
						which can be converted by this function.

						(-) If ``radix_char_count`` is ''0'', the value ''64'' will
						be used by this function.

						(.) ``radix_char_list`` is the list of characters to be
						used in the conversion.

						(-) If the ``radix_char_count`` parameter is ''0'', this
						function will use the following string:

{|-|}"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz@#"

						(-) If the ``radix_char_count`` parameter is less than or
						equal to ''64'' and ``radix_char_list`` is ''NULL'',
						``radix_char_list`` will be set to the string above.

						(.) ``in_value`` is the value to be converted. It is
						always passed as an ``unsigned long``, even for negative
						values.

						(.) ``in_sign`` is the sign to be used in the resulting
						conversion. If less than zero, then a minus sign (''-'')
						will be prepended to the resulting string.

						(.) ``in_radix`` is the radix to be used for the resulting
						string. It must be in the range of ''2'' through the value
						if the ``radix_char_count`` parameter, inclusive.

						(.) ``in_fill_char`` points to the character to be used to
						left-pad the resulting string. If this parameter is ''NULL''
						or points to a zero-length string, the string will not be
						padded.

						(.) ``out_string`` points to the area into which the
						resulting string will be placed. Its minimum length to
						support an arbitrary ``in_radix`` and ``in_sign`` should be:

						(--) 1 + (sizeof(unsigned long) * CHAR_BIT) + 1

						(-) This permits the storage of the longest string returned
						by this function, including ASCII NULL-terminator.

   RETURNS     :  Returns from this function are as follow:

						(.) If no error occurs, a pointer to the string
						``out_string`` is returned.

						(.) If an error occurs, a ''NULL'' pointer is returned.

	NOTES			:	The only error which can occur in the operation of this
						function is the passing of an invalid ``in_radix``
						parameter.

	CAVEATS		:	

	SEE ALSO		:	val2str_cat
						val2str_basic

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2014 Michael L. Brock

	OUTPUT INDEX:	val2str_basic_cat
						Miscellaneous Functions:val2str_basic_cat
						STRFUNCS:Miscellaneous Functions:val2str_basic_cat
						String Functions:See STRFUNCS

	PUBLISH XREF:	val2str_basic_cat

	PUBLISH NAME:	val2str_basic_cat

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *val2str_basic_cat(unsigned int radix_char_count,
	const char *radix_char_list, unsigned long in_value, int in_sign,
	unsigned int in_radix, const char *in_fill_char, char *out_string)
#else
char *val2str_basic_cat(radix_char_count, radix_char_list, in_value, in_sign,
	in_radix, in_fill_char, out_string)
unsigned int   radix_char_count;
const char    *radix_char_list;
unsigned long  in_value;
int            in_sign;
unsigned int   in_radix;
const char    *in_fill_char;
char          *out_string;
#endif /* #ifndef NARGS */
{
	val2str_basic(radix_char_count, radix_char_list, in_value, in_sign,
		in_radix, in_fill_char, out_string + strlen(out_string));

	return(out_string);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	val2str_ulong

	SYNOPSIS		:	return_ptr = val2str_ulong(in_value, in_radix, in_fill_char,
							out_string);

						char          *return_ptr;

						unsigned long  in_value;

						unsigned int   in_radix;

						const char    *in_fill_char;

						char          *out_string;

	DESCRIPTION	:	Converts an ``unsigned long`` into a string using the
						specified radix.

						The resulting string is placed into the buffer to which the
						``out_string`` parameter points.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_value`` is the ``unsigned long`` value to be
						converted.

						(.) ``in_radix`` is the radix to be used for the resulting
						string. It must be in the range of ''2'' through ''36'',
						inclusive.

						(.) ``in_fill_char`` points to the character to be used to
						left-pad the resulting string. If this parameter is ''NULL''
						or points to a zero-length string, the string will not be
						padded.

						(.) ``out_string`` points to the area into which the
						resulting string will be placed. Its minimum length to
						support an arbitrary ``in_radix`` should be:

						(--) (sizeof(unsigned long) * CHAR_BIT) + 1

						(-) This permits the storage of the longest string returned
						by this function, including ASCII NULL-terminator.

   RETURNS     :  Returns from this function are as follow:

						(.) If no error occurs, a pointer to the string
						``out_string`` is returned.

						(.) If an error occurs, a ''NULL'' pointer is returned.

	NOTES			:	The only error which can occur in the operation of this
						function is the passing of an invalid ``in_radix``
						parameter.

	CAVEATS		:	

	SEE ALSO		:	val2str_slong
						val2str_ulong_cat
						val2str_basic

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2014 Michael L. Brock

	OUTPUT INDEX:	val2str_ulong
						Miscellaneous Functions:val2str_ulong
						STRFUNCS:Miscellaneous Functions:val2str_ulong
						String Functions:See STRFUNCS

	PUBLISH XREF:	val2str_ulong

	PUBLISH NAME:	val2str_ulong

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *val2str_ulong(unsigned long in_value, unsigned int in_radix,
	const char *in_fill_char, char *out_string)
#else
char *val2str_ulong(in_value, in_radix, in_fill_char, out_string)
unsigned long  in_value;
unsigned int   in_radix;
const char    *in_fill_char;
char          *out_string;
#endif /* #ifndef NARGS */
{
	return(val2str_basic(0, NULL, in_value, 1, in_radix, in_fill_char,
		out_string));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	val2str_ulong_cat

	SYNOPSIS		:	return_ptr = val2str_ulong_cat(in_value, in_radix,
							in_fill_char, out_string);

						char          *return_ptr;

						unsigned long  in_value;

						unsigned int   in_radix;

						const char    *in_fill_char;

						char          *out_string;

	DESCRIPTION	:	Converts an ``unsigned long`` into a string using the
						specified radix.

						The resulting string is concatenated onto the string to
						which the ``out_string`` parameter points.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_value`` is the ``unsigned long`` value to be
						converted.

						(.) ``in_radix`` is the radix to be used for the resulting
						string. It must be in the range of ''2'' through ''64'',
						inclusive.

						(.) ``in_fill_char`` points to the character to be used to
						left-pad the resulting string. If this parameter is ''NULL''
						or points to a zero-length string, the string will not be
						padded.

						(.) ``out_string`` points to the area into which the
						resulting string will be placed. Its minimum length to
						support an arbitrary ``in_radix`` should be:

						(--) (sizeof(unsigned long) * CHAR_BIT) + 1

						(-) This permits the storage of the longest string returned
						by this function, including ASCII NULL-terminator.

   RETURNS     :  Returns from this function are as follow:

						(.) If no error occurs, a pointer to the string
						``out_string`` is returned.

						(.) If an error occurs, a ''NULL'' pointer is returned.

	NOTES			:	The only error which can occur in the operation of this
						function is the passing of an invalid ``in_radix``
						parameter.

	CAVEATS		:	

	SEE ALSO		:	val2str_slong_cat
						val2str_ulong
						val2str_basic_cat

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2014 Michael L. Brock

	OUTPUT INDEX:	val2str_ulong_cat
						Miscellaneous Functions:val2str_ulong_cat
						STRFUNCS:Miscellaneous Functions:val2str_ulong_cat
						String Functions:See STRFUNCS

	PUBLISH XREF:	val2str_ulong_cat

	PUBLISH NAME:	val2str_ulong_cat

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *val2str_ulong_cat(unsigned long in_value, unsigned int in_radix,
	const char *in_fill_char, char *out_string)
#else
char *val2str_ulong_cat(in_value, in_radix, in_fill_char, out_string)
unsigned long  in_value;
unsigned int   in_radix;
const char    *in_fill_char;
char          *out_string;
#endif /* #ifndef NARGS */
{
	return(val2str_basic_cat(0, NULL, in_value, 1, in_radix, in_fill_char,
		out_string));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	val2str_slong

	SYNOPSIS		:	return_ptr = val2str_slong(in_value, in_radix, in_fill_char,
							out_string);

						char         *return_ptr;

						signed long   in_value;

						unsigned int  in_radix;

						const char   *in_fill_char;

						char         *out_string;

	DESCRIPTION	:	Converts an ``signed long`` into a string using the
						specified radix.

						The resulting string is placed into the buffer to which the
						``out_string`` parameter points.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_value`` is the ``signed long`` value to be
						converted.

						(.) ``in_radix`` is the radix to be used for the resulting
						string. It must be in the range of ''2'' through ''36'',
						inclusive.

						(.) ``in_fill_char`` points to the character to be used to
						left-pad the resulting string. If this parameter is ''NULL''
						or points to a zero-length string, the string will not be
						padded.

						(.) ``out_string`` points to the area into which the
						resulting string will be placed. Its minimum length to
						support an arbitrary ``in_radix`` should be:

						(--) 1 + (sizeof(unsigned long) * CHAR_BIT) + 1

						(-) This permits the storage of the longest string returned
						by this function, including ASCII NULL-terminator.

   RETURNS     :  Returns from this function are as follow:

						(.) If no error occurs, a pointer to the string
						``out_string`` is returned.

						(.) If an error occurs, a ''NULL'' pointer is returned.

	NOTES			:	The only error which can occur in the operation of this
						function is the passing of an invalid ``in_radix``
						parameter.

	CAVEATS		:	

	SEE ALSO		:	val2str_ulong
						val2str_slong_cat
						val2str_basic

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2014 Michael L. Brock

	OUTPUT INDEX:	val2str_slong
						Miscellaneous Functions:val2str_slong
						STRFUNCS:Miscellaneous Functions:val2str_slong
						String Functions:See STRFUNCS

	PUBLISH XREF:	val2str_slong

	PUBLISH NAME:	val2str_slong

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *val2str_slong(signed long in_value, unsigned int in_radix,
	const char *in_fill_char, char *out_string)
#else
char *val2str_slong(in_value, in_radix, in_fill_char, out_string)
signed long   in_value;
unsigned int  in_radix;
const char   *in_fill_char;
char         *out_string;
#endif /* #ifndef NARGS */
{
	return(val2str_basic(0, NULL,
		((unsigned long) ((in_value < 0L) ? (0L - in_value) : in_value)),
		((int) in_value), in_radix, in_fill_char, out_string));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	val2str_slong_cat

	SYNOPSIS		:	return_ptr = val2str_slong_cat(in_value, in_radix,
							in_fill_char, out_string);

						char         *return_ptr;

						signed long   in_value;

						unsigned int  in_radix;

						const char   *in_fill_char;

						char         *out_string;

	DESCRIPTION	:	Converts an ``signed long`` into a string using the
						specified radix.

						The resulting string is concatenated onto the string to
						which the ``out_string`` parameter points.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_value`` is the ``signed long`` value to be
						converted.

						(.) ``in_radix`` is the radix to be used for the resulting
						string. It must be in the range of ''2'' through ''64'',
						inclusive.

						(.) ``in_fill_char`` points to the character to be used to
						left-pad the resulting string. If this parameter is ''NULL''
						or points to a zero-length string, the string will not be
						padded.

						(.) ``out_string`` points to the area into which the
						resulting string will be placed. Its minimum length to
						support an arbitrary ``in_radix`` should be:

						(--) 1 + (sizeof(unsigned long) * CHAR_BIT) + 1

						(-) This permits the storage of the longest string returned
						by this function, including ASCII NULL-terminator.

   RETURNS     :  Returns from this function are as follow:

						(.) If no error occurs, a pointer to the string
						``out_string`` is returned.

						(.) If an error occurs, a ''NULL'' pointer is returned.

	NOTES			:	The only error which can occur in the operation of this
						function is the passing of an invalid ``in_radix``
						parameter.

	CAVEATS		:	

	SEE ALSO		:	val2str_ulong_cat
						val2str_slong
						val2str_basic_cat

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2014 Michael L. Brock

	OUTPUT INDEX:	val2str_slong_cat
						Miscellaneous Functions:val2str_slong_cat
						STRFUNCS:Miscellaneous Functions:val2str_slong_cat
						String Functions:See STRFUNCS

	PUBLISH XREF:	val2str_slong_cat

	PUBLISH NAME:	val2str_slong_cat

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *val2str_slong_cat(signed long in_value, unsigned int in_radix,
	const char *in_fill_char, char *out_string)
#else
char *val2str_slong_cat(in_value, in_radix, in_fill_char, out_string)
signed long   in_value;
unsigned int  in_radix;
const char   *in_fill_char;
char         *out_string;
#endif /* #ifndef NARGS */
{
	return(val2str_basic_cat(0, NULL,
		((unsigned long) ((in_value < 0L) ? (0L - in_value) : in_value)),
		((int) in_value), in_radix, in_fill_char, out_string));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	val2str_uint

	SYNOPSIS		:	return_ptr = val2str_uint(in_value, in_radix, in_fill_char,
							out_string);

						char           *return_ptr;

						unsigned int    in_value;

						unsigned int    in_radix;

						const char     *in_fill_char;

						char           *out_string;

	DESCRIPTION	:	Converts an ``unsigned int`` into a string using the
						specified radix.

						The resulting string is placed into the buffer to which the
						``out_string`` parameter points.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_value`` is the ``unsigned int`` value to be
						converted.

						(.) ``in_radix`` is the radix to be used for the resulting
						string. It must be in the range of ''2'' through ''64'',
						inclusive.

						(.) ``in_fill_char`` points to the character to be used to
						left-pad the resulting string. If this parameter is ''NULL''
						or points to a zero-length string, the string will not be
						padded.

						(.) ``out_string`` points to the area into which the
						resulting string will be placed. Its minimum length to
						support an arbitrary ``in_radix`` should be:

						(--) (sizeof(unsigned long) * CHAR_BIT) + 1

						(-) This permits the storage of the longest string returned
						by this function, including ASCII NULL-terminator.

   RETURNS     :  Returns from this function are as follow:

						(.) If no error occurs, a pointer to the string
						``out_string`` is returned.

						(.) If an error occurs, a ''NULL'' pointer is returned.

	NOTES			:	The only error which can occur in the operation of this
						function is the passing of an invalid ``in_radix``
						parameter.

	CAVEATS		:	

	SEE ALSO		:	val2str_sint
						val2str_uint_cat
						val2str_basic

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2014 Michael L. Brock

	OUTPUT INDEX:	val2str_uint
						Miscellaneous Functions:val2str_uint
						STRFUNCS:Miscellaneous Functions:val2str_uint
						String Functions:See STRFUNCS

	PUBLISH XREF:	val2str_uint

	PUBLISH NAME:	val2str_uint

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *val2str_uint(unsigned int in_value, unsigned int in_radix,
	const char *in_fill_char, char *out_string)
#else
char *val2str_uint(in_value, in_radix, in_fill_char, out_string)
unsigned int  in_value;
unsigned int  in_radix;
const char   *in_fill_char;
char         *out_string;
#endif /* #ifndef NARGS */
{
	return(val2str_basic(0, NULL, ((unsigned long) in_value), 1, in_radix,
		in_fill_char, out_string));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	val2str_uint_cat

	SYNOPSIS		:	return_ptr = val2str_uint_cat(in_value, in_radix,
							in_fill_char, out_string);

						char           *return_ptr;

						unsigned int    in_value;

						unsigned int    in_radix;

						const char     *in_fill_char;

						char           *out_string;

	DESCRIPTION	:	Converts an ``unsigned int`` into a string using the
						specified radix.

						The resulting string is concatenated onto the string to
						which the ``out_string`` parameter points.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_value`` is the ``unsigned int`` value to be
						converted.

						(.) ``in_radix`` is the radix to be used for the resulting
						string. It must be in the range of ''2'' through ''64'',
						inclusive.

						(.) ``in_fill_char`` points to the character to be used to
						left-pad the resulting string. If this parameter is ''NULL''
						or points to a zero-length string, the string will not be
						padded.

						(.) ``out_string`` points to the area into which the
						resulting string will be placed. Its minimum length to
						support an arbitrary ``in_radix`` should be:

						(--) (sizeof(unsigned long) * CHAR_BIT) + 1

						(-) This permits the storage of the longest string returned
						by this function, including ASCII NULL-terminator.

   RETURNS     :  Returns from this function are as follow:

						(.) If no error occurs, a pointer to the string
						``out_string`` is returned.

						(.) If an error occurs, a ''NULL'' pointer is returned.

	NOTES			:	The only error which can occur in the operation of this
						function is the passing of an invalid ``in_radix``
						parameter.

	CAVEATS		:	

	SEE ALSO		:	val2str_sint_cat
						val2str_uint
						val2str_basic_cat

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2014 Michael L. Brock

	OUTPUT INDEX:	val2str_uint_cat
						Miscellaneous Functions:val2str_uint_cat
						STRFUNCS:Miscellaneous Functions:val2str_uint_cat
						String Functions:See STRFUNCS

	PUBLISH XREF:	val2str_uint_cat

	PUBLISH NAME:	val2str_uint_cat

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *val2str_uint_cat(unsigned int in_value, unsigned int in_radix,
	const char *in_fill_char, char *out_string)
#else
char *val2str_uint_cat(in_value, in_radix, in_fill_char, out_string)
unsigned int  in_value;
unsigned int  in_radix;
const char   *in_fill_char;
char         *out_string;
#endif /* #ifndef NARGS */
{
	return(val2str_basic_cat(0, NULL, ((unsigned long) in_value), 1, in_radix,
		in_fill_char, out_string));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	val2str_sint

	SYNOPSIS		:	return_ptr = val2str_sint(in_value, in_radix, in_fill_char,
							out_string);

						char          *return_ptr;

						signed int     in_value;

						unsigned int   in_radix;

						const char    *in_fill_char;

						char          *out_string;

	DESCRIPTION	:	Converts an ``signed int`` into a string using the
						specified radix.

						The resulting string is placed into the buffer to which the
						``out_string`` parameter points.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_value`` is the ``signed int`` value to be
						converted.

						(.) ``in_radix`` is the radix to be used for the resulting
						string. It must be in the range of ''2'' through ''64'',
						inclusive.

						(.) ``in_fill_char`` points to the character to be used to
						left-pad the resulting string. If this parameter is ''NULL''
						or points to a zero-length string, the string will not be
						padded.

						(.) ``out_string`` points to the area into which the
						resulting string will be placed. Its minimum length to
						support an arbitrary ``in_radix`` should be:

						(--) 1 + (sizeof(unsigned long) * CHAR_BIT) + 1

						(-) This permits the storage of the longest string returned
						by this function, including ASCII NULL-terminator.

   RETURNS     :  Returns from this function are as follow:

						(.) If no error occurs, a pointer to the string
						``out_string`` is returned.

						(.) If an error occurs, a ''NULL'' pointer is returned.

	NOTES			:	The only error which can occur in the operation of this
						function is the passing of an invalid ``in_radix``
						parameter.

	CAVEATS		:	

	SEE ALSO		:	val2str_uint
						val2str_sint_cat
						val2str_basic

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2014 Michael L. Brock

	OUTPUT INDEX:	val2str_sint
						Miscellaneous Functions:val2str_sint
						STRFUNCS:Miscellaneous Functions:val2str_sint
						String Functions:See STRFUNCS

	PUBLISH XREF:	val2str_sint

	PUBLISH NAME:	val2str_sint

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *val2str_sint(signed int in_value, unsigned int in_radix,
	const char *in_fill_char, char *out_string)
#else
char *val2str_sint(in_value, in_radix, in_fill_char, out_string)
signed int    in_value;
unsigned int  in_radix;
const char   *in_fill_char;
char         *out_string;
#endif /* #ifndef NARGS */
{
	return(val2str_basic(0, NULL,
		((unsigned long) ((in_value < 0) ? (0 - in_value) : in_value)),
		((int) in_value), in_radix, in_fill_char, out_string));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	val2str_sint_cat

	SYNOPSIS		:	return_ptr = val2str_sint_cat(in_value, in_radix,
							in_fill_char, out_string);

						char         *return_ptr;

						signed int    in_value;

						unsigned int  in_radix;

						const char   *in_fill_char;

						char         *out_string;

	DESCRIPTION	:	Converts an ``signed int`` into a string using the
						specified radix.

						The resulting string is concatenated onto the string to
						which the ``out_string`` parameter points.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_value`` is the ``signed int`` value to be
						converted.

						(.) ``in_radix`` is the radix to be used for the resulting
						string. It must be in the range of ''2'' through ''64'',
						inclusive.

						(.) ``in_fill_char`` points to the character to be used to
						left-pad the resulting string. If this parameter is ''NULL''
						or points to a zero-length string, the string will not be
						padded.

						(.) ``out_string`` points to the area into which the
						resulting string will be placed. Its minimum length to
						support an arbitrary ``in_radix`` should be:

						(--) 1 + (sizeof(unsigned long) * CHAR_BIT) + 1

						(-) This permits the storage of the longest string returned
						by this function, including ASCII NULL-terminator.

   RETURNS     :  Returns from this function are as follow:

						(.) If no error occurs, a pointer to the string
						``out_string`` is returned.

						(.) If an error occurs, a ''NULL'' pointer is returned.

	NOTES			:	The only error which can occur in the operation of this
						function is the passing of an invalid ``in_radix``
						parameter.

	CAVEATS		:	

	SEE ALSO		:	val2str_uint_cat
						val2str_sint
						val2str_basic_cat

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2014 Michael L. Brock

	OUTPUT INDEX:	val2str_sint_cat
						Miscellaneous Functions:val2str_sint_cat
						STRFUNCS:Miscellaneous Functions:val2str_sint_cat
						String Functions:See STRFUNCS

	PUBLISH XREF:	val2str_sint_cat

	PUBLISH NAME:	val2str_sint_cat

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *val2str_sint_cat(signed int in_value, unsigned int in_radix,
	const char *in_fill_char, char *out_string)
#else
char *val2str_sint_cat(in_value, in_radix, in_fill_char, out_string)
signed int    in_value;
unsigned int  in_radix;
const char   *in_fill_char;
char         *out_string;
#endif /* #ifndef NARGS */
{
	return(val2str_basic_cat(0, NULL,
		((unsigned long) ((in_value < 0) ? (0 - in_value) : in_value)),
		((int) in_value), in_radix, in_fill_char, out_string));
}
/* *********************************************************************** */

/*	***********************************************************************	*/
char *val2str_ptr(const void *in_value, char *out_string)
{
	return(lower(val2str_ulong_cat(((unsigned long) in_value), 16, NULL,
		strcpy(out_string, "0x"))));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
char *val2str_ptr_cat(const void *in_value, char *out_string)
{
	return(lower(val2str_ulong_cat(((unsigned long) in_value), 16, NULL,
		strcat(out_string, "0x"))));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
char *val2str_ptr0(const void *in_value, char *out_string)
{
	return(lower(val2str_ulong_cat(((unsigned long) in_value), 16, "0",
		strcpy(out_string, "0x"))));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
char *val2str_ptr0_cat(const void *in_value, char *out_string)
{
	return(lower(val2str_ulong_cat(((unsigned long) in_value), 16, "0",
		strcat(out_string, "0x"))));
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <float.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>

#ifdef _MSC_VER
# pragma warning(disable:4514)
#endif /* # ifdef _MSC_VER */
#include <math.h>

COMPAT_FN_DECL(int main, (int argc, char **argv));

COMPAT_FN_DECL_STATIC(char *val2str_double_basic,
	(unsigned int radix_char_count, const char *radix_char_list,
	double in_value, unsigned int in_radix, const char *in_fill_char,
	char *out_string));
COMPAT_FN_DECL_STATIC(char *val2str_double_basic_cat,
	(unsigned int radix_char_count, const char *radix_char_list,
	double in_value, unsigned int in_radix, const char *in_fill_char,
	char *out_string));
COMPAT_FN_DECL_STATIC(char *val2str_double,
	(double in_value, unsigned int in_radix, const char *in_fill_char,
	char *out_string));
COMPAT_FN_DECL_STATIC(char *val2str_double_cat,
	(double in_value, unsigned int in_radix, const char *in_fill_char,
	char *out_string));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	unsigned int   count_1;
	unsigned int   count_2;
	int            sign;
	double         tmp_double_1;
	double         tmp_double_2;
	long           tmp_long;
	unsigned long  tmp_u_long;
	long           out_long;
	unsigned long  out_u_long;
	char          *tmp_ptr;
	char           buffer[4096];
	char           dashes[100];

	fprintf(stderr, "Test routine for function 'val2str_basic()'\n");
	fprintf(stderr, "---- ------- --- -------- -----------------\n\n");

	if (argc == 1) {
		memset(dashes, '=', sizeof(dashes) - 1);
		dashes[sizeof(dashes) - 1] = '\0';
		printf("%-6.6s %-9.9s %-10.10s %-32.32s %-17.17s\n",
			"Radix", "Value 255", "Length 255", "Value 4294967295",
			"Length 4294967295");
		printf("%-6.6s %-9.9s %-10.10s %-32.32s %-17.17s\n",
			"Number", "For Radix", "For Radix", "For Radix", "For Radix");
		printf("%-6.6s %-9.9s %-10.10s %-32.32s %-17.17s\n",
			dashes, dashes, dashes, dashes, dashes);
		for (count_2 = 2; count_2 <= STRFUNCS_RadixCharCount; count_2++) {
			printf("%6u ", count_2);
			printf("%-9.9s ", val2str_basic(0, NULL,
				((unsigned long) 255), 1, count_2, NULL, buffer));
			printf("%10u ", strlen(buffer));
			printf("%-32.32s ", val2str_basic(0, NULL,
				4294967295UL, 1, count_2, NULL, buffer));
			printf("%17u\n", strlen(buffer));
		}
		printf("%-6.6s %-9.9s %-10.10s %-32.32s %-17.17s\n",
			dashes, dashes, dashes, dashes, dashes);
		goto EXIT_FUNCTION;
	}

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		tmp_double_1 = atof(argv[count_1]);
		sign         = ((int) ((tmp_double_1 < 0.0) ? -1 : 1));
		tmp_double_2 = fabs(tmp_double_1);
		if ((tmp_double_2 < ((double) ((long) LONG_MIN))) ||
			(tmp_double_2 > ((double) LONG_MAX))) {
			fprintf(stderr,
				"ERROR: %f is out-of-range (valid range is %f to %f).\n",
				tmp_double_1, ((double) ((long) LONG_MIN)), ((double) LONG_MAX));
			continue;
		}
		tmp_u_long = ((unsigned long) tmp_double_2);
		tmp_long   = ((long) tmp_double_1);
		printf("[%10ld][%10lu]:", tmp_long, tmp_u_long);
		printf("\n");
		for (count_2 = 2; count_2 <= STRFUNCS_RadixCharCount; count_2++) {
			if (sign >= 0) {
				printf("[%02u]", count_2);
				printf("[%s]", val2str_basic(0, NULL,
					tmp_u_long, sign, count_2, NULL, buffer));
				printf("[%s]",
					(tmp_u_long == strtol(buffer, &tmp_ptr, ((int) count_2))) ?
					"OK" : "BAD");
				printf("[%s]", val2str_basic(0, NULL,
					tmp_u_long, sign, count_2, " ", buffer));
				printf("[%s]",
					(tmp_u_long == strtol(buffer, &tmp_ptr, ((int) count_2))) ?
					"OK" : "BAD");
				printf("[%s]", val2str_basic(0, NULL,
					tmp_u_long, sign, count_2, "0", buffer));
				printf("[%s]",
					(tmp_u_long == strtol(buffer, &tmp_ptr, ((int) count_2))) ?
					"OK" : "BAD");
				if (tmp_u_long != (out_u_long = strtol(val2str_basic(0, NULL,
					tmp_u_long, sign, count_2, NULL, buffer), &tmp_ptr,
					((int) count_2))))	
					printf(" *** %lu", out_u_long);
			}
			else {
				printf("[%02u]", count_2);
				printf("[%s]", val2str_basic(0, NULL,
					tmp_u_long, sign, count_2, NULL, buffer));
				printf("[%s]",
					(tmp_long == strtol(nospace(buffer), &tmp_ptr,
					((int) count_2))) ? "OK" : "BAD");
				printf("[%s]", val2str_basic(0, NULL,
					tmp_u_long, sign, count_2, " ", buffer));
				printf("[%s]",
					(tmp_long == strtol(nospace(buffer), &tmp_ptr,
					((int) count_2))) ? "OK" : "BAD");
				printf("[%s]", val2str_basic(0, NULL,
					tmp_u_long, sign, count_2, "0", buffer));
				printf("[%s]",
					(tmp_long == strtol(nospace(buffer), &tmp_ptr,
					((int) count_2))) ? "OK" : "BAD");
				if (tmp_long != (out_long = strtol(nospace(val2str_basic(0, NULL,
					tmp_u_long, sign, count_2, NULL, buffer)), &tmp_ptr,
					((int) count_2))))	
					printf(" *** %ld ('strtol()'; ptr = %08lX = [%s])", out_long,
						((unsigned long) tmp_ptr), tmp_ptr);
			}
			printf("\n");
		}
		for (count_2 = 0; count_2 < 77; count_2++) 
			printf("-");
		printf("\n");
	}

EXIT_FUNCTION:

	printf("\n\n");
	STR_EMIT_CharLine('=', 78, NULL, NULL);
	STR_EMIT_CharLine('=', 78, NULL, NULL);
	printf("Other 'val2str()' lengths.\n");
	STR_EMIT_CharLine('=', 78, NULL, NULL);

	printf("Maximum length of 2^32 integral value  (radix  2): %u\n",
		strlen(val2str_double(pow(65536.0, 2.0) - 1.0,  2, NULL, buffer)));
	printf("Maximum length of 2^32 integral value  (radix  4): %u\n",
		strlen(val2str_double(pow(65536.0, 2.0) - 1.0,  4, NULL, buffer)));
	printf("Maximum length of 2^32 integral value  (radix  8): %u\n",
		strlen(val2str_double(pow(65536.0, 2.0) - 1.0,  8, NULL, buffer)));
	printf("Maximum length of 2^32 integral value  (radix 10): %u\n",
		strlen(val2str_double(pow(65536.0, 2.0) - 1.0, 10, NULL, buffer)));
	printf("Maximum length of 2^32 integral value  (radix 16): %u\n",
		strlen(val2str_double(pow(65536.0, 2.0) - 1.0, 16, NULL, buffer)));
	printf("Maximum length of 2^32 integral value  (radix 36): %u\n",
		strlen(val2str_double(pow(65536.0, 2.0) - 1.0, 36, NULL, buffer)));
	printf("Maximum length of 2^32 integral value  (radix 62): %u\n",
		strlen(val2str_double(pow(65536.0, 2.0) - 1.0, 62, NULL, buffer)));
	printf("Maximum length of 2^32 integral value  (radix 64): %u\n",
		strlen(val2str_double(pow(65536.0, 2.0) - 1.0, 64, NULL, buffer)));
	STR_EMIT_CharLine('-', 78, NULL, NULL);

	printf("Maximum length of 2^64 integral value  (radix  2): %u\n",
		strlen(val2str_double(18446744073709551615.0,  2, NULL, buffer)));
	printf("Maximum length of 2^64 integral value  (radix  4): %u\n",
		strlen(val2str_double(18446744073709551615.0,  4, NULL, buffer)));
	printf("Maximum length of 2^64 integral value  (radix  8): %u\n",
		strlen(val2str_double(18446744073709551615.0,  8, NULL, buffer)));
	printf("Maximum length of 2^64 integral value  (radix 10): %u\n",
		strlen(val2str_double(18446744073709551615.0, 10, NULL, buffer)));
	printf("Maximum length of 2^64 integral value  (radix 16): %u\n",
		strlen(val2str_double(18446744073709551615.0, 16, NULL, buffer)));
	printf("Maximum length of 2^64 integral value  (radix 36): %u\n",
		strlen(val2str_double(18446744073709551615.0, 36, NULL, buffer)));
	printf("Maximum length of 2^64 integral value  (radix 62): %u\n",
		strlen(val2str_double(18446744073709551615.0, 62, NULL, buffer)));
	printf("Maximum length of 2^64 integral value  (radix 64): %u\n",
		strlen(val2str_double(18446744073709551615.0, 64, NULL, buffer)));
	STR_EMIT_CharLine('-', 78, NULL, NULL);

	printf("Maximum length of 2^128 integral value (radix  2): %u\n",
		strlen(val2str_double(170141183460469231731687303715884105727.0,
		 2, NULL, buffer)));
	printf("Maximum length of 2^128 integral value (radix  4): %u\n",
		strlen(val2str_double(170141183460469231731687303715884105727.0,
		 4, NULL, buffer)));
	printf("Maximum length of 2^128 integral value (radix  8): %u\n",
		strlen(val2str_double(170141183460469231731687303715884105727.0,
		 8, NULL, buffer)));
	printf("Maximum length of 2^128 integral value (radix 10): %u\n",
		strlen(val2str_double(170141183460469231731687303715884105727.0,
		10, NULL, buffer)));
	printf("Maximum length of 2^128 integral value (radix 16): %u\n",
		strlen(val2str_double(170141183460469231731687303715884105727.0,
		16, NULL, buffer)));
	printf("Maximum length of 2^128 integral value (radix 36): %u\n",
		strlen(val2str_double(170141183460469231731687303715884105727.0,
		36, NULL, buffer)));
	printf("Maximum length of 2^128 integral value (radix 62): %u\n",
		strlen(val2str_double(170141183460469231731687303715884105727.0,
		62, NULL, buffer)));
	printf("Maximum length of 2^128 integral value (radix 64): %u\n",
		strlen(val2str_double(170141183460469231731687303715884105727.0,
		64, NULL, buffer)));
	STR_EMIT_CharLine('-', 78, NULL, NULL);

	printf("Maximum length of 'DBL_MAX'            (radix  2): %u\n",
		strlen(val2str_double(DBL_MAX,                 2, NULL, buffer)));
	printf("Maximum length of 'DBL_MAX'            (radix  4): %u\n",
		strlen(val2str_double(DBL_MAX,                 4, NULL, buffer)));
	printf("Maximum length of 'DBL_MAX'            (radix  8): %u\n",
		strlen(val2str_double(DBL_MAX,                 8, NULL, buffer)));
	printf("Maximum length of 'DBL_MAX'            (radix 10): %u\n",
		strlen(val2str_double(DBL_MAX,                10, NULL, buffer)));
	printf("Maximum length of 'DBL_MAX'            (radix 16): %u\n",
		strlen(val2str_double(DBL_MAX,                16, NULL, buffer)));
	printf("Maximum length of 'DBL_MAX'            (radix 36): %u\n",
		strlen(val2str_double(DBL_MAX,                36, NULL, buffer)));
	printf("Maximum length of 'DBL_MAX'            (radix 62): %u\n",
		strlen(val2str_double(DBL_MAX,                64, NULL, buffer)));
	printf("Maximum length of 'DBL_MAX'            (radix 64): %u\n",
		strlen(val2str_double(DBL_MAX,                64, NULL, buffer)));
	STR_EMIT_CharLine('=', 78, NULL, NULL);
	printf("\n");

	STR_EMIT_CharLine('=', 78, NULL, NULL);
	printf("Maximum length of 2^8  integral value  (radix 64): %u\n",
		strlen(val2str_ulong(((unsigned long) 0X000000FF), 64, NULL, buffer)));
	printf("Maximum length of 2^16 integral value  (radix 64): %u\n",
		strlen(val2str_ulong(((unsigned long) 0X0000FFFF), 64, NULL, buffer)));
	printf("Maximum length of 2^32 integral value  (radix 64): %u\n",
		strlen(val2str_ulong(((unsigned long) 0XFFFFFFFF), 64, NULL, buffer)));
	printf("Maximum length of 2^64 integral value  (radix 64): %u\n",
		strlen(val2str_double(18446744073709551615.0, 64, NULL, buffer)));
	STR_EMIT_CharLine('=', 78, NULL, NULL);

	printf("\n\n");

	return(0);
}

/* *********************************************************************** */
/* *********************************************************************** */
/* x_BOH

	NAME			:	val2str_double_basic

	SYNOPSIS		:	return_ptr = val2str_double_basic(radix_char_count,
							radix_char_list, in_value, in_radix, in_fill_char,
							out_string);

						char          *return_ptr;

						unsigned int   radix_char_count;

						const char    *radix_char_list;

						double         in_value;

						unsigned int   in_radix;

						const char    *in_fill_char;

						char          *out_string;

	DESCRIPTION	:	Converts a ``double`` into a string using the
						specified radix.

						The resulting string is placed into the buffer to which the
						``out_string`` parameter points.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``radix_char_count`` is the number of characters in the
						array ``radix_char_list``. It represents the maximum radix
						which can be converted by this function.

						(-) If ``radix_char_count`` is ''0'', the value ''64'' will
						be used by this function.

						(.) ``radix_char_list`` is the list of characters to be
						used in the conversion.

						(-) If the ``radix_char_count`` parameter is ''0'', this
						function will use the following string:

{|-|}"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz@#"

						(-) If the ``radix_char_count`` parameter is less than or
						equal to ''64'' and ``radix_char_list`` is ''NULL'',
						``radix_char_list`` will be set to the string above.

						(.) ``in_value`` is the value to be converted. It is
						always passed as a ``double``, even for negative
						values.

						(.) ``in_radix`` is the radix to be used for the resulting
						string. It must be in the range of ''2'' through the value
						if the ``radix_char_count`` parameter, inclusive.

						(.) ``in_fill_char`` points to the character to be used to
						left-pad the resulting string. If this parameter is ''NULL''
						or points to a zero-length string, the string will not be
						padded.

						(.) ``out_string`` points to the area into which the
						resulting string will be placed. Its minimum length to
						support an arbitrary ``in_radix`` should be:

						(--) 1 + (sizeof(unsigned long) * CHAR_BIT) + 1

						(-) This permits the storage of the longest string returned
						by this function, including ASCII NULL-terminator.

   RETURNS     :  Returns from this function are as follow:

						(.) If no error occurs, a pointer to the string
						``out_string`` is returned.

						(.) If an error occurs, a ''NULL'' pointer is returned.

	NOTES			:	The only error which can occur in the operation of this
						function is the passing of an invalid ``in_radix``
						parameter.

	CAVEATS		:	

	SEE ALSO		:	val2str_double
						val2str_double_basic_cat

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2014 Michael L. Brock

	OUTPUT INDEX:	val2str_double_basic
						Miscellaneous Functions:val2str_double_basic
						STRFUNCS:Miscellaneous Functions:val2str_double_basic
						String Functions:See STRFUNCS

	PUBLISH XREF:	val2str_double_basic

	PUBLISH NAME:	val2str_double_basic

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
static char *val2str_double_basic(unsigned int radix_char_count,
	const char *radix_char_list, double in_value, unsigned int in_radix,
	const char *in_fill_char, char *out_string)
#else
static char *val2str_double_basic(radix_char_count, radix_char_list, in_value,
	in_radix, in_fill_char, out_string)
unsigned int   radix_char_count;
const char    *radix_char_list;
double         in_value;
unsigned int   in_radix;
const char    *in_fill_char;
char          *out_string;
#endif /* #ifndef NARGS */
{
	double        power_value;
	double        old_power_value;
	int           in_sign;
	unsigned int  char_index;
	char         *tmp_ptr_1;
	char         *tmp_ptr_2;
	char          buffer[1 + 4096 + 1];

	if (!radix_char_count) {
		radix_char_count = STRFUNCS_RadixCharCount;
		radix_char_list  = STRFUNCS_RadixCharList;
	}
	else if ((radix_char_count <= STRFUNCS_RadixCharCount) &&
		(radix_char_list == NULL))
		radix_char_list = STRFUNCS_RadixCharList;

	if ((in_radix < 2) || (in_radix > radix_char_count))
		out_string = NULL;
	else {
		in_sign         = (in_value < 0.0) ? -1 : 1;
		in_value        = floor(fabs(in_value));
		power_value     = ((double) in_radix);
		old_power_value = 0.0;
		char_index      = ((unsigned int) fmod(in_value, ((double) in_radix)));
		tmp_ptr_1       = out_string;
		tmp_ptr_2       = buffer + (sizeof(buffer) - 1);
		*tmp_ptr_2--    = '\0';
		*tmp_ptr_2--    = radix_char_list[char_index];
		in_fill_char    = ((in_fill_char != NULL) && (!(*in_fill_char))) ?
			NULL : in_fill_char;
		while (power_value > old_power_value) {
			if (in_value >= power_value) {
				char_index   = ((unsigned int)
					floor(fmod(in_value / power_value, ((double) in_radix))));
				*tmp_ptr_2-- =
					radix_char_list[char_index];
			}
			else if (in_fill_char != NULL) {
				while (tmp_ptr_2 >= buffer)
					*tmp_ptr_2-- = *in_fill_char;
				tmp_ptr_2 += 1;
				break;
			}
			else
				break;
			if (floor(DBL_MAX / power_value) < ((double) in_radix))
         	break;
			old_power_value = power_value;
			power_value     = floor(power_value * ((double) in_radix));
		}
		if (in_sign < 0)
			*tmp_ptr_2-- = '-';
		tmp_ptr_2++;
		do { *tmp_ptr_1++ = *tmp_ptr_2; } while (*tmp_ptr_2++);
	}

	return(out_string);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* x_BOH

	NAME			:	val2str_double_basic_cat

	SYNOPSIS		:	return_ptr = val2str_double_basic_cat(radix_char_count,
							radix_char_list, in_value, in_radix, in_fill_char,
							out_string);

						char          *return_ptr;

						unsigned int   radix_char_count;

						const char    *radix_char_list;

						double         in_value;

						unsigned int   in_radix;

						const char    *in_fill_char;

						char          *out_string;

	DESCRIPTION	:	Converts a ``double`` into a string using the
						specified radix.

						The resulting string is concatenated onto the string to
						which the ``out_string`` parameter points.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``radix_char_count`` is the number of characters in the
						array ``radix_char_list``. It represents the maximum radix
						which can be converted by this function.

						(-) If ``radix_char_count`` is ''0'', the value ''64'' will
						be used by this function.

						(.) ``radix_char_list`` is the list of characters to be
						used in the conversion.

						(-) If the ``radix_char_count`` parameter is ''0'', this
						function will use the following string:

{|-|}"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz@#"

						(-) If the ``radix_char_count`` parameter is less than or
						equal to ''64'' and ``radix_char_list`` is ''NULL'',
						``radix_char_list`` will be set to the string above.

						(.) ``in_value`` is the value to be converted. It is
						always passed as a ``double``, even for negative
						values.

						(.) ``in_radix`` is the radix to be used for the resulting
						string. It must be in the range of ''2'' through the value
						if the ``radix_char_count`` parameter, inclusive.

						(.) ``in_fill_char`` points to the character to be used to
						left-pad the resulting string. If this parameter is ''NULL''
						or points to a zero-length string, the string will not be
						padded.

						(.) ``out_string`` points to the area into which the
						resulting string will be placed. Its minimum length to
						support an arbitrary ``in_radix`` should be:

						(--) 1 + (sizeof(unsigned long) * CHAR_BIT) + 1

						(-) This permits the storage of the longest string returned
						by this function, including ASCII NULL-terminator.

   RETURNS     :  Returns from this function are as follow:

						(.) If no error occurs, a pointer to the string
						``out_string`` is returned.

						(.) If an error occurs, a ''NULL'' pointer is returned.

	NOTES			:	The only error which can occur in the operation of this
						function is the passing of an invalid ``in_radix``
						parameter.

	CAVEATS		:	

	SEE ALSO		:	val2str_double_cat
						val2str_double_basic

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2014 Michael L. Brock

	OUTPUT INDEX:	val2str_double_basic_cat
						Miscellaneous Functions:val2str_double_basic_cat
						STRFUNCS:Miscellaneous Functions:val2str_double_basic_cat
						String Functions:See STRFUNCS

	PUBLISH XREF:	val2str_double_basic_cat

	PUBLISH NAME:	val2str_double_basic_cat

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
static char *val2str_double_basic_cat(unsigned int radix_char_count,
	const char *radix_char_list, double in_value, unsigned int in_radix,
	const char *in_fill_char, char *out_string)
#else
static char *val2str_double_basic_cat(radix_char_count, radix_char_list, in_value,
	in_radix, in_fill_char, out_string)
unsigned int   radix_char_count;
const char    *radix_char_list;
double         in_value;
unsigned int   in_radix;
const char    *in_fill_char;
char          *out_string;
#endif /* #ifndef NARGS */
{
	return(val2str_double_basic(radix_char_count, radix_char_list, in_value,
		in_radix, in_fill_char, out_string + strlen(out_string)));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* x_BOH

	NAME			:	val2str_double

	SYNOPSIS		:	return_ptr = val2str_double(in_value, in_radix, in_fill_char,
							out_string);

						char          *return_ptr;

						double         in_value;

						unsigned int   in_radix;

						const char    *in_fill_char;

						char          *out_string;

	DESCRIPTION	:	Converts a ``double`` into a string using the
						specified radix.

						The resulting string is placed into the buffer to which the
						``out_string`` parameter points.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_value`` is the ``double`` value to be
						converted.

						(.) ``in_radix`` is the radix to be used for the resulting
						string. It must be in the range of ''2'' through ''36'',
						inclusive.

						(.) ``in_fill_char`` points to the character to be used to
						left-pad the resulting string. If this parameter is ''NULL''
						or points to a zero-length string, the string will not be
						padded.

						(.) ``out_string`` points to the area into which the
						resulting string will be placed. Its minimum length to
						support an arbitrary ``in_radix`` should be:

						(--) (sizeof(unsigned long) * CHAR_BIT) + 1

						(-) This permits the storage of the longest string returned
						by this function, including ASCII NULL-terminator.

   RETURNS     :  Returns from this function are as follow:

						(.) If no error occurs, a pointer to the string
						``out_string`` is returned.

						(.) If an error occurs, a ''NULL'' pointer is returned.

	NOTES			:	The only error which can occur in the operation of this
						function is the passing of an invalid ``in_radix``
						parameter.

	CAVEATS		:	

	SEE ALSO		:	val2str_double_slong
						val2str_double_cat
						val2str_double_basic

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2014 Michael L. Brock

	OUTPUT INDEX:	val2str_double
						Miscellaneous Functions:val2str_double
						STRFUNCS:Miscellaneous Functions:val2str_double
						String Functions:See STRFUNCS

	PUBLISH XREF:	val2str_double

	PUBLISH NAME:	val2str_double

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
static char *val2str_double(double in_value, unsigned int in_radix,
	const char *in_fill_char, char *out_string)
#else
static char *val2str_double(in_value, in_radix, in_fill_char, out_string)
double         in_value;
unsigned int   in_radix;
const char    *in_fill_char;
char          *out_string;
#endif /* #ifndef NARGS */
{
	return(val2str_double_basic(0, NULL, in_value, in_radix, in_fill_char,
		out_string));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* x_BOH

	NAME			:	val2str_double_cat

	SYNOPSIS		:	return_ptr = val2str_double_cat(in_value, in_radix,
							in_fill_char, out_string);

						char          *return_ptr;

						double         in_value;

						unsigned int   in_radix;

						const char    *in_fill_char;

						char          *out_string;

	DESCRIPTION	:	Converts a ``double`` into a string using the
						specified radix.

						The resulting string is concatenated onto the string to
						which the ``out_string`` parameter points.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_value`` is the ``double`` value to be
						converted.

						(.) ``in_radix`` is the radix to be used for the resulting
						string. It must be in the range of ''2'' through ''64'',
						inclusive.

						(.) ``in_fill_char`` points to the character to be used to
						left-pad the resulting string. If this parameter is ''NULL''
						or points to a zero-length string, the string will not be
						padded.

						(.) ``out_string`` points to the area into which the
						resulting string will be placed. Its minimum length to
						support an arbitrary ``in_radix`` should be:

						(--) (sizeof(unsigned long) * CHAR_BIT) + 1

						(-) This permits the storage of the longest string returned
						by this function, including ASCII NULL-terminator.

   RETURNS     :  Returns from this function are as follow:

						(.) If no error occurs, a pointer to the string
						``out_string`` is returned.

						(.) If an error occurs, a ''NULL'' pointer is returned.

	NOTES			:	The only error which can occur in the operation of this
						function is the passing of an invalid ``in_radix``
						parameter.

	CAVEATS		:	

	SEE ALSO		:	val2str_double_slong_cat
						val2str_double
						val2str_double_basic_cat

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2014 Michael L. Brock

	OUTPUT INDEX:	val2str_double_cat
						Miscellaneous Functions:val2str_double_cat
						STRFUNCS:Miscellaneous Functions:val2str_double_cat
						String Functions:See STRFUNCS

	PUBLISH XREF:	val2str_double_cat

	PUBLISH NAME:	val2str_double_cat

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
static char *val2str_double_cat(double in_value, unsigned int in_radix,
	const char *in_fill_char, char *out_string)
#else
static char *val2str_double_cat(in_value, in_radix, in_fill_char, out_string)
double         in_value;
unsigned int   in_radix;
const char    *in_fill_char;
char          *out_string;
#endif /* #ifndef NARGS */
{
	return(val2str_double_basic_cat(0, NULL, in_value, in_radix, in_fill_char,
		out_string));
}
/* *********************************************************************** */

#endif /* #ifdef TEST_MAIN */

