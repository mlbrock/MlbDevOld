/* *********************************************************************** */
/* *********************************************************************** */
/*	Data Type Alignment (DTA) Functions Library Source Module					*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Converts a string and instance count into an
								equivalent single string.

	Revision History	:	1992-02-23 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Include necessary header files . . .											*/
/* *********************************************************************** */

#include <stdlib.h>

#include "dtai.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  DTA_BASIC_CountStringToString

   SYNOPSIS    :  return_code = DTA_BASIC_CountStringToString(type_count,
							type_list, normalize_flag, adjust_char_flag,
							separator_list, in_spec_count, in_spec_string,
							out_spec_string, error_text);

						int              return_code;

						unsigned int     type_count;

						const DTA_TYPE  *type_list;

						int              normalize_flag;

						int              adjust_char_flag;

						const char      *separator_list;

						unsigned int     in_spec_count;

						const char      *in_spec_string;

						char           **out_spec_string;

						char            *error_text;

   DESCRIPTION :  Transforms a string specification (and associated instance
						count) of the members of a structure into an equivalent
						single string.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``type_count`` is the number of elements in the array
						represented by the ``type_list`` parameter.

						(.) ``type_list`` is an array of ''DTA_TYPE''
						structures which describe a machine architecture in terms
						of the primitive data types available on that architecture.

						(-) If ``type_count`` is ''0'' and ``type_list`` is
						''NULL'', the function will use the built-in primitive
						data type list compiled into the module ``dtadata.c``
						under the names ``DTA_TypeCount`` and ``DTA_TypeList``.

						(.) ``normalize_flag`` indicates whether the elements of
						the temporary ''DTA'' array used in the operation of
						this function are to be normalized vis-a-vis each other.

						(-) Normalization is the combination of like data types from
						adjacent ''DTA'' elements into a single element.

						(-) For example, if array of ''DTA'' elements contains
						the adjacent elements resulting from operation of this
						function on the string:

{|-|}c[10],c[3]

						(-) Normalization of those elements will result in a single
						element equivalent to the string:

{|-|}c[13]

						(-) The ``normalize_flag`` parameter may take on one of the
						following two values:

						(..) ``DTA_TRUE``, which indicates that the elements
						are to be normalized.

						(..) ``DTA_FALSE``, which indicates that the elements
						are not to be normalized.

						(.) ``adjust_char_flag`` specifies that ''char'' (and
						''unsigned char'') arrays are to be increased in length
						by a single byte. This is usually to accomodate the
						inclusion of the ''C'' language string null terminator byte.

						(-) The ``adjust_char_flag`` parameter may take on one of
						the following two values:

						(..) ``DTA_TRUE``, which indicates that ''char''
						elements are to be adjusted.

						(..) ``DTA_FALSE``, which indicates that ''char''
						elements are not to be adjusted.

						(.) ``separator_list`` is an ASCII NUL (ASCII 0) terminated
						string which lists the characters to be used to separate
						discrete specifications in ``spec_string``.

						(-) if ``separator_list`` is ''NULL'', the comma character
						('','') will be used to separate specifications in
						``spec_string``.

						(.) ``in_spec_count`` is the number of instances
						``in_spec_string`` is to be repeated to produce the
						temporary ''DTA'' array.

   					(.) ``in_spec_string`` is the string which contains a list
						of member definitions separated by some combination of the
						characters in ``separator_list``. Leading and trailing
						``separator_string`` characters are ignored.

						(-) Each member definition has the following format:

						(--) { ''b''|''c''|''C''|''s''|''S''|''i''|''I''|''l''|''L''|''f''|''d'' }

						(-) where each letter has the following meaning:

						(..)''b'' is an unsigned (binary) char. The upper-case
						letter ''B'' is also allowed.

						(..)''c'' is a signed char.

						(..)''C'' is an unsigned char.

						(..)''s'' is a signed short integer.

						(..)''S'' is an unsigned short integer.

						(..)''i'' is a signed integer.

						(..)''I'' is an unsigned integer.

						(..)''l'' is a long integer.

						(..)''L'' is an unsigned long integer

						(..)''f'' is a float. The upper-case letter ''F'' is also
						allowed.

						(..)''d'' is a double. The upper-case letter ''D'' is also
						allowed.

						(-) A member definition may be followed by an optional
						array specifier of the form:

						(--) ``member-definition``[``array-length``]

						(-) Note that ``array-length`` must be greater than zero.

						(.) ``out_spec_string`` is a pointer to a pointer to
						''char'' which will be set to the memory allocated to store
						the instanced string representation specified by the
						combination of ``in_spec_count`` and ``in_spec_string``.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at
						least ''DTA_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DTA_SUCCESS'' if no error occurs.

						(.) One of the non-zero DTA Return Codes if an error
						occurs.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  DTA_BASIC_CountStringToList
						DTA_CountStringToString

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2016 Michael L. Brock

   OUTPUT INDEX:	DTA_BASIC_CountStringToString
						Data Type Alignment Functions:DTA_BASIC_CountStringToString
						DTA:Functions:DTA_BASIC_CountStringToString
						DTA:Data Type Alignment Functions:DTA_BASIC_CountStringToString

   PUBLISH XREF:	DTA_BASIC_CountStringToString

   PUBLISH NAME:	DTA_BASIC_CountStringToString

	ENTRY CLASS	:	Data Type Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DTA_BASIC_CountStringToString(unsigned int type_count,
	const DTA_TYPE *type_list, int normalize_flag, int adjust_char_flag,
	const char *separator_list, unsigned int in_spec_count,
	const char *in_spec_string, char **out_spec_string, char *error_text)
#else
int DTA_BASIC_CountStringToString(type_count, type_list, normalize_flag,
	adjust_char_flag, separator_list, in_spec_count, in_spec_string,
	out_spec_string, error_text)
unsigned int     type_count;
const DTA_TYPE  *type_list;
int              normalize_flag;
int              adjust_char_flag;
const char      *separator_list;
unsigned int     in_spec_count;
const char      *in_spec_string;
char           **out_spec_string;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code;
	unsigned int  align_count;
	DTA          *align_list;

	if ((return_code = DTA_BASIC_CountStringToList(type_count,
		type_list, normalize_flag, adjust_char_flag, separator_list,
		in_spec_count, in_spec_string, NULL, &align_count, &align_list,
		error_text)) == DTA_SUCCESS) {
		return_code = DTA_BASIC_ListToStringAlloc(type_count, type_list,
			align_count, align_list, separator_list, out_spec_string,
			error_text);
		free(align_list);
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  DTA_CountStringToString

   SYNOPSIS    :  return_code = DTA_CountStringToString(normalize_flag,
							adjust_char_flag, separator_list, in_spec_count,
							in_spec_string, out_spec_string, error_text);

						int            return_code;

						int            normalize_flag;

						int            adjust_char_flag;

						const char    *separator_list;

						unsigned int   in_spec_count;

						const char    *in_spec_string;

						char         **out_spec_string;

						char          *error_text;

   DESCRIPTION :  Transforms a string specification (and associated instance
						count) of the members of a structure into an equivalent
						single string.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``normalize_flag`` indicates whether the elements of
						the temporary ''DTA'' array used in the operation of
						this function are to be normalized vis-a-vis each other.

						(-) Normalization is the combination of like data types from
						adjacent ''DTA'' elements into a single element.

						(-) For example, if array of ''DTA'' elements contains
						the adjacent elements resulting from operation of this
						function on the string:

{|-|}c[10],c[3]

						(-) Normalization of those elements will result in a single
						element equivalent to the string:

{|-|}c[13]

						(-) The ``normalize_flag`` parameter may take on one of the
						following two values:

						(..) ``DTA_TRUE``, which indicates that the elements
						are to be normalized.

						(..) ``DTA_FALSE``, which indicates that the elements
						are not to be normalized.

						(.) ``adjust_char_flag`` specifies that ''char'' (and
						''unsigned char'') arrays are to be increased in length
						by a single byte. This is usually to accomodate the
						inclusion of the ''C'' language string null terminator byte.

						(-) The ``adjust_char_flag`` parameter may take on one of
						the following two values:

						(..) ``DTA_TRUE``, which indicates that ''char''
						elements are to be adjusted.

						(..) ``DTA_FALSE``, which indicates that ''char''
						elements are not to be adjusted.

						(.) ``separator_list`` is an ASCII NUL (ASCII 0) terminated
						string which lists the characters to be used to separate
						discrete specifications in ``spec_string``.

						(-) if ``separator_list`` is ''NULL'', the comma character
						('','') will be used to separate specifications in
						``spec_string``.

						(.) ``in_spec_count`` is the number of instances
						``in_spec_string`` is to be repeated to produce the
						temporary ''DTA'' array.

   					(.) ``in_spec_string`` is the string which contains a list
						of member definitions separated by some combination of the
						characters in ``separator_list``. Leading and trailing
						``separator_string`` characters are ignored.

						(-) Each member definition has the following format:

						(--) { ''b''|''c''|''C''|''s''|''S''|''i''|''I''|''l''|''L''|''f''|''d'' }

						(-) where each letter has the following meaning:

						(..)''b'' is an unsigned (binary) char. The upper-case
						letter ''B'' is also allowed.

						(..)''c'' is a signed char.

						(..)''C'' is an unsigned char.

						(..)''s'' is a signed short integer.

						(..)''S'' is an unsigned short integer.

						(..)''i'' is a signed integer.

						(..)''I'' is an unsigned integer.

						(..)''l'' is a long integer.

						(..)''L'' is an unsigned long integer

						(..)''f'' is a float. The upper-case letter ''F'' is also
						allowed.

						(..)''d'' is a double. The upper-case letter ''D'' is also
						allowed.

						(-) A member definition may be followed by an optional
						array specifier of the form:

						(--) ``member-definition``[``array-length``]

						(-) Note that ``array-length`` must be greater than zero.

						(.) ``structure_size`` is a pointer to an ''unsigned int''
						into which will be placed the total size of the structure
						as determined by this function. The size will include
						any alignment bytes required by the implementation.

						(-) If ``structure_size`` is ''NULL'', it will not be
						de-referenced.

						(.) ``out_spec_string`` is a pointer to a pointer to
						''char'' which will be set to the memory allocated to store
						the instanced string representation specified by the
						combination of ``in_spec_count`` and ``in_spec_string``.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at
						least ''DTA_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DTA_SUCCESS'' if no error occurs.

						(.) One of the non-zero DTA Return Codes if an error
						occurs.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  DTA_CountStringToList
						DTA_BASIC_CountStringToString

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2016 Michael L. Brock

   OUTPUT INDEX:	DTA_CountStringToString
						Data Type Alignment Functions:DTA_CountStringToString
						DTA:Functions:DTA_CountStringToString
						DTA:Data Type Alignment Functions:DTA_CountStringToString

   PUBLISH XREF:	DTA_CountStringToString

   PUBLISH NAME:	DTA_CountStringToString

	ENTRY CLASS	:	Data Type Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DTA_CountStringToString(int normalize_flag, int adjust_char_flag,
	const char *separator_list, unsigned int in_spec_count,
	const char *in_spec_string, char **out_spec_string, char *error_text)
#else
int DTA_CountStringToString(normalize_flag, adjust_char_flag,
	separator_list, in_spec_count, in_spec_string, out_spec_string, error_text)
int            normalize_flag;
int            adjust_char_flag;
const char    *separator_list;
unsigned int   in_spec_count;
const char    *in_spec_string;
char         **out_spec_string;
char          *error_text;
#endif /* #ifndef NARGS */
{
	return(DTA_BASIC_CountStringToString(0, NULL, normalize_flag,
		adjust_char_flag, separator_list, in_spec_count, in_spec_string,
		out_spec_string, error_text));
}
/* *********************************************************************** */

