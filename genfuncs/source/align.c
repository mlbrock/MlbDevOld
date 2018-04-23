/* *********************************************************************** */
/* *********************************************************************** */
/*	GENFUNCS General Functions Library Source Module								*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Functions used to determine the alignment of primitive
								data types and to manage access to those data types
								in run-time specified aggregations.

	Revision History	:	1992-02-23 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Include necessary header files . . .											*/
/* *********************************************************************** */

#include <limits.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>

#include <strfuncs.h>

#include "genfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_ALIGN_AlignStringList

   SYNOPSIS    :  return_code = GEN_ALIGN_AlignStringList(normalize_flag,
							adjust_char_flag, separator_list, spec_count, spec_list,
							count_list, index_list, size_list, structure_size,
							align_count, align_list, error_text);

						int            return_code;

						int            normalize_flag;

						int            adjust_char_flag;

						const char    *separator_list;

						unsigned int   spec_count;

						char         **spec_list;

						unsigned int **count_list;

						unsigned int **index_list;

						unsigned int **size_list;

						unsigned int  *structure_size;

						unsigned int  *align_count;

						GEN_ALIGN    **align_list;

						char          *error_text;

   DESCRIPTION :	Transforms an array of pointers to string specifications of
						the primitive type members of a structure into an array of
						structures of type ''GEN_ALIGN'', the elements of which
						contain offset and length data for each member.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``normalize_flag`` indicates whether the elements of
						the array ``align_list`` which results the operation of
						this function are to be normalized vis-a-vis each other.

						(-) Normalization is the combination of like data types from
						adjacent ``align_list`` elements into a single element.

						(-) For example, if ``align_list`` contains the adjacent
						elements resulting from operation of this function on the
						string:

{|-|}c[10],c[3]

						(-) Normalization of those elements will result in a single
						element equivalent to the string:

{|-|}c[13]

						(-) The ``normalize_flag`` parameter may take on one of the
						following two values:

						(..) ``GENFUNCS_TRUE``, which indicates that the elements
						are to be normalized.

						(..) ``GENFUNCS_FALSE``, which indicates that the elements
						are not to be normalized.

						(.) ``adjust_char_flag`` specifies that ''char'' (and
						''unsigned char'') arrays are to be increased in length
						by a single byte. This is usually to accomodate the
						inclusion of the ''C'' language string null terminator byte.

						(-) The ``adjust_char_flag`` parameter may take on one of
						the following two values:

						(..) ``GENFUNCS_TRUE``, which indicates that ''char''
						elements are to be adjusted.

						(..) ``GENFUNCS_FALSE``, which indicates that ''char''
						elements are not to be adjusted.

						(.) ``separator_list`` is an ASCII NUL (ASCII 0) terminated
						string which lists the characters to be used to separate
						discrete specifications in ``spec_string``.

						(-) if ``separator_list`` is ''NULL'', the comma character
						('','') will be used to separate specifications in
						``spec_string``.

						(.) ``spec_count`` is the number of elements in the
						array ``spec_list``.

						(.) ``spec_list`` is a array of pointers to strings, each
						string of which is a primitive type specification having
						the following format:

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

						(.) ``count_list`` is a pointer to an ''unsigned int'' into
						which this function will place a pointer to memory allocated
						to hold an array of ''unsigned int''s. Each element of the
						array will correspond to an element in the array
						``spec_list``, so the total number of elements allocated
						will be equal to ``spec_count``.

						(-) Each element of the allocated array represents the
						number of elements in the array ``align_list`` for the
						corresponding ``spec_list`` element.

						(.) ``index_list`` is a pointer to an ''unsigned int'' into
						which this function will place a pointer to memory allocated
						to hold an array of ''unsigned int''s. Each element of the
						array will correspond to an element in the array
						``spec_list``, so the total number of elements allocated
						will be equal to ``spec_count``.

						(-) Each element of the allocated array represents the
						first element of the array ``align_list`` for the
						corresponding ``spec_list`` element.

						(.) ``size_list`` is a pointer to an ''unsigned int'' into
						which this function will place a pointer to memory allocated
						to hold an array of ''unsigned int''s. Each element of the
						array will correspond to an element in the array
						``spec_list``, so the total number of elements allocated
						will be equal to ``spec_count``.

						(-) Each element of the allocated array represents the
						total size of all of the elements in the array
						``align_list`` for the 	corresponding ``spec_list`` element.
						This size will include any alignment bytes required by the
						implementation.

						(.) ``structure_size`` is a pointer to an ''unsigned int''
						into which will be placed the total size of the structure
						as determined by this function. The size will include
						any alignment bytes required by the implementation.

						(-) If ``structure_size`` is ''NULL'', it will not be
						de-referenced.

						(.) ``align_count`` is a pointer to an ''unsigned int'' into
						which will be placed the number of members which were
						parsed out of the string ``spec_string``.

						(.) ``align_list`` points to a pointer to a structure of
						type ''GEN_ALIGN''. If the function is
						successful, it will allocate memory sufficient to hold
						``align_count`` elements. Each element will describe the
						offset and length requirements for each member of the
						desired structure.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at
						least ''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if no error occurs.

						(.) One of the non-zero GENFUNCS Return Codes if an error
						occurs.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  GEN_ALIGN_BASIC_AlignStringList
						GEN_ALIGN_AlignString

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_ALIGN_AlignStringList
						Alignment Functions:GEN_ALIGN_AlignStringList
						GENFUNCS:Functions:GEN_ALIGN_AlignStringList
						GENFUNCS:Alignment Functions:GEN_ALIGN_AlignStringList
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_ALIGN_AlignStringList

   PUBLISH NAME:	GEN_ALIGN_AlignStringList

	ENTRY CLASS	:	Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int GEN_ALIGN_AlignStringList(int normalize_flag, int adjust_char_flag,
	const char *separator_list, unsigned int spec_count, char **spec_list,
	unsigned int **count_list, unsigned int **index_list,
	unsigned int **size_list, unsigned int *structure_size,
	unsigned int *align_count, GEN_ALIGN **align_list, char *error_text)
#else
int GEN_ALIGN_AlignStringList(normalize_flag, adjust_char_flag,
	separator_list, spec_count, spec_list, count_list, index_list, size_list,
	structure_size, align_count, align_list, error_text)
int            normalize_flag;
int            adjust_char_flag;
const char    *separator_list;
unsigned int   spec_count;
char         **spec_list;
unsigned int **count_list;
unsigned int **index_list;
unsigned int **size_list;
unsigned int  *structure_size;
unsigned int  *align_count;
GEN_ALIGN    **align_list;
char          *error_text;
#endif /* #ifndef NARGS */
{
	return(GEN_ALIGN_BASIC_AlignStringList(0, NULL, normalize_flag,
		adjust_char_flag, separator_list, spec_count, spec_list, count_list,
		index_list, size_list, structure_size, align_count, align_list,
		error_text));
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_ALIGN_AlignString

   SYNOPSIS    :  return_code = GEN_ALIGN_AlignString(normalize_flag,
							adjust_char_flag, separator_list, spec_string,
							structure_size, align_count, align_list, error_text);

						int            return_code;

						int            normalize_flag;

						int            adjust_char_flag;

						const char    *separator_list;

						char          *spec_string;

						unsigned int  *structure_size;

						unsigned int  *align_count;

						GEN_ALIGN    **align_list;

						char          *error_text;

   DESCRIPTION :  Transforms a string specification of the members of a
						structure into an array of structures of type
						''GEN_ALIGN'', the elements of which contain
						offset and length data for each member.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``normalize_flag`` indicates whether the elements of
						the array ``align_list`` which results the operation of
						this function are to be normalized vis-a-vis each other.

						(-) Normalization is the combination of like data types from
						adjacent ``align_list`` elements into a single element.

						(-) For example, if ``align_list`` contains the adjacent
						elements resulting from operation of this function on the
						string:

{|-|}c[10],c[3]

						(-) Normalization of those elements will result in a single
						element equivalent to the string:

{|-|}c[13]

						(-) The ``normalize_flag`` parameter may take on one of the
						following two values:

						(..) ``GENFUNCS_TRUE``, which indicates that the elements
						are to be normalized.

						(..) ``GENFUNCS_FALSE``, which indicates that the elements
						are not to be normalized.

						(.) ``adjust_char_flag`` specifies that ''char'' (and
						''unsigned char'') arrays are to be increased in length
						by a single byte. This is usually to accomodate the
						inclusion of the ''C'' language string null terminator byte.

						(-) The ``adjust_char_flag`` parameter may take on one of
						the following two values:

						(..) ``GENFUNCS_TRUE``, which indicates that ''char''
						elements are to be adjusted.

						(..) ``GENFUNCS_FALSE``, which indicates that ''char''
						elements are not to be adjusted.

						(.) ``separator_list`` is an ASCII NUL (ASCII 0) terminated
						string which lists the characters to be used to separate
						discrete specifications in ``spec_string``.

						(-) if ``separator_list`` is ''NULL'', the comma character
						('','') will be used to separate specifications in
						``spec_string``.

   					(.) ``spec_string`` is the string which contains a list of
						member definitions separated by some combination of the
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

						(.) ``align_count`` is a pointer to an ''unsigned int'' into
						which will be placed the number of members which were
						parsed out of the string ``spec_string``.

						(.) ``align_list`` points to a pointer to a structure of
						type ''GEN_ALIGN''. If the function is
						successful, it will allocate memory sufficient to hold
						``align_count`` elements. Each element will describe the
						offset and length requirements for each member of the
						desired structure.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at
						least ''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if no error occurs.

						(.) One of the non-zero GENFUNCS Return Codes if an error
						occurs.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  GEN_ALIGN_BASIC_AlignString
						GEN_ALIGN_CheckMember
						GEN_ALIGN_AlignList

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_ALIGN_AlignString
						Alignment Functions:GEN_ALIGN_AlignString
						GENFUNCS:Functions:GEN_ALIGN_AlignString
						GENFUNCS:Alignment Functions:GEN_ALIGN_AlignString
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_ALIGN_AlignString

   PUBLISH NAME:	GEN_ALIGN_AlignString

	ENTRY CLASS	:	Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int GEN_ALIGN_AlignString(int normalize_flag, int adjust_char_flag,
	const char *separator_list, const char *spec_string,
	unsigned int *structure_size, unsigned int *align_count,
	GEN_ALIGN **align_list, char *error_text)
#else
int GEN_ALIGN_AlignString(normalize_flag, adjust_char_flag, separator_list,
	spec_string, structure_size, align_count, align_list, error_text)
int            normalize_flag;
int            adjust_char_flag;
const char    *separator_list;
const char    *spec_string;
unsigned int  *structure_size;
unsigned int  *align_count;
GEN_ALIGN    **align_list;
char          *error_text;
#endif /* #ifndef NARGS */
{
	return(GEN_ALIGN_BASIC_AlignString(0, NULL, normalize_flag,
		adjust_char_flag, separator_list, spec_string, structure_size,
		align_count, align_list, error_text));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_ALIGN_CountStringToList

   SYNOPSIS    :  return_code = GEN_ALIGN_CountStringToList(normalize_flag,
							adjust_char_flag, separator_list, in_spec_count,
							in_spec_string, structure_size, align_count, align_list,
							error_text);

						int            return_code;

						int            normalize_flag;

						int            adjust_char_flag;

						const char    *separator_list;

						unsigned int   in_spec_count;

						const char    *in_spec_string;

						unsigned int  *structure_size;

						unsigned int  *align_count;

						GEN_ALIGN    **align_list;

						char          *error_text;

   DESCRIPTION :  Transforms an string specification (and associated instance
						count) of the members of a structure into an array of
						structures of type ''GEN_ALIGN''.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``normalize_flag`` indicates whether the elements of
						the array ``align_list`` which results the operation of
						this function are to be normalized vis-a-vis each other.

						(-) Normalization is the combination of like data types from
						adjacent ``align_list`` elements into a single element.

						(-) For example, if ``align_list`` contains the adjacent
						elements resulting from operation of this function on the
						string:

{|-|}c[10],c[3]

						(-) Normalization of those elements will result in a single
						element equivalent to the string:

{|-|}c[13]

						(-) The ``normalize_flag`` parameter may take on one of the
						following two values:

						(..) ``GENFUNCS_TRUE``, which indicates that the elements
						are to be normalized.

						(..) ``GENFUNCS_FALSE``, which indicates that the elements
						are not to be normalized.

						(.) ``adjust_char_flag`` specifies that ''char'' (and
						''unsigned char'') arrays are to be increased in length
						by a single byte. This is usually to accomodate the
						inclusion of the ''C'' language string null terminator byte.

						(-) The ``adjust_char_flag`` parameter may take on one of
						the following two values:

						(..) ``GENFUNCS_TRUE``, which indicates that ''char''
						elements are to be adjusted.

						(..) ``GENFUNCS_FALSE``, which indicates that ''char''
						elements are not to be adjusted.

						(.) ``separator_list`` is an ASCII NUL (ASCII 0) terminated
						string which lists the characters to be used to separate
						discrete specifications in ``spec_string``.

						(-) if ``separator_list`` is ''NULL'', the comma character
						('','') will be used to separate specifications in
						``spec_string``.

						(.) ``in_spec_count`` is the number of instances
						``in_spec_string`` is to be repeated to produce
						``align_list``.

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

						(.) ``align_count`` is a pointer to an ''unsigned int'' into
						which will be placed the number of members which were
						parsed out of the string ``spec_string``.

						(.) ``align_list`` points to a pointer to a structure of
						type ''GEN_ALIGN''. If the function is
						successful, it will allocate memory sufficient to hold
						``align_count`` elements. Each element will describe the
						offset and length requirements for each member of the
						desired structure.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at
						least ''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if no error occurs.

						(.) One of the non-zero GENFUNCS Return Codes if an error
						occurs.

   NOTES       :  If you want to append members parsed out of the
						``in_spec_string`` parameter to the list represented by
						``align_count`` and ``align_list``, use the related function
						``GEN_ALIGN_CountStringToLApp``.

   CAVEATS     :  

   SEE ALSO    :  GEN_ALIGN_CountStringToString
						GEN_ALIGN_CountStringToLApp
						GEN_ALIGN_BASIC_CountStringToList

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_ALIGN_CountStringToList
						Alignment Functions:GEN_ALIGN_CountStringToList
						GENFUNCS:Functions:GEN_ALIGN_CountStringToList
						GENFUNCS:Alignment Functions:GEN_ALIGN_CountStringToList
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_ALIGN_CountStringToList

   PUBLISH NAME:	GEN_ALIGN_CountStringToList

	ENTRY CLASS	:	Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int GEN_ALIGN_CountStringToList(int normalize_flag, int adjust_char_flag,
	const char *separator_list, unsigned int in_spec_count,
	const char *in_spec_string, unsigned int *structure_size,
	unsigned int *align_count, GEN_ALIGN **align_list, char *error_text)
#else
int GEN_ALIGN_CountStringToList(normalize_flag, adjust_char_flag,
	separator_list, in_spec_count, in_spec_string, structure_size, align_count,
	align_list, error_text)
int            normalize_flag;
int            adjust_char_flag;
const char    *separator_list;
unsigned int   in_spec_count;
const char    *in_spec_string;
unsigned int  *structure_size;
unsigned int  *align_count;
GEN_ALIGN    **align_list;
char          *error_text;
#endif /* #ifndef NARGS */
{
	return(GEN_ALIGN_BASIC_CountStringToList(0, NULL, normalize_flag,
		adjust_char_flag, separator_list, in_spec_count, in_spec_string,
		structure_size, align_count, align_list, error_text));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_ALIGN_CountStringToLApp

   SYNOPSIS    :  return_code = GEN_ALIGN_CountStringToLApp(normalize_flag,
							adjust_char_flag, separator_list, in_spec_count,
							in_spec_string, structure_size, align_count, align_list,
							error_text);

						int            return_code;

						int            normalize_flag;

						int            adjust_char_flag;

						const char    *separator_list;

						unsigned int   in_spec_count;

						const char    *in_spec_string;

						unsigned int  *structure_size;

						unsigned int  *align_count;

						GEN_ALIGN    **align_list;

						char          *error_text;

   DESCRIPTION :  Transforms an string specification (and associated instance
						count) of the members of a structure into an array of
						structures of type ''GEN_ALIGN''. These structures are then
						appended to the list represented by the ``align_count`` and
						``align_list`` parameters.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``normalize_flag`` indicates whether the elements of
						the array ``align_list`` which results the operation of
						this function are to be normalized vis-a-vis each other.

						(-) Normalization is the combination of like data types from
						adjacent ``align_list`` elements into a single element.

						(-) For example, if ``align_list`` contains the adjacent
						elements resulting from operation of this function on the
						string:

{|-|}c[10],c[3]

						(-) Normalization of those elements will result in a single
						element equivalent to the string:

{|-|}c[13]

						(-) The ``normalize_flag`` parameter may take on one of the
						following two values:

						(..) ``GENFUNCS_TRUE``, which indicates that the elements
						are to be normalized.

						(..) ``GENFUNCS_FALSE``, which indicates that the elements
						are not to be normalized.

						(.) ``adjust_char_flag`` specifies that ''char'' (and
						''unsigned char'') arrays are to be increased in length
						by a single byte. This is usually to accomodate the
						inclusion of the ''C'' language string null terminator byte.

						(-) The ``adjust_char_flag`` parameter may take on one of
						the following two values:

						(..) ``GENFUNCS_TRUE``, which indicates that ''char''
						elements are to be adjusted.

						(..) ``GENFUNCS_FALSE``, which indicates that ''char''
						elements are not to be adjusted.

						(.) ``separator_list`` is an ASCII NUL (ASCII 0) terminated
						string which lists the characters to be used to separate
						discrete specifications in ``spec_string``.

						(-) if ``separator_list`` is ''NULL'', the comma character
						('','') will be used to separate specifications in
						``spec_string``.

						(.) ``in_spec_count`` is the number of instances
						``in_spec_string`` is to be repeated to produce
						``align_list``.

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

						(.) ``align_count`` is a pointer to an ''unsigned int''
						which will be increased by the number of members which were
						parsed out of the string ``spec_string``.

						(.) ``align_list`` points to a pointer to a structure of
						type ''GEN_ALIGN''. If the function is
						successful, it will allocate memory sufficient to hold
						``align_count`` elements. Each element will describe the
						offset and length requirements for each member of the
						desired structure.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at
						least ''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if no error occurs.

						(.) One of the non-zero GENFUNCS Return Codes if an error
						occurs.

   NOTES       :  This function appends members parsed out of the
						``in_spec_string`` parameter to the list represented by
						``align_count`` and ``align_list``. If you do not want
						this behavior, use the related function
						``GEN_ALIGN_CountStringToList``.

   CAVEATS     :  

   SEE ALSO    :  GEN_ALIGN_CountStringToList
						GEN_ALIGN_BASIC_CountStringToLApp

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_ALIGN_CountStringToLApp
						Alignment Functions:GEN_ALIGN_CountStringToLApp
						GENFUNCS:Functions:GEN_ALIGN_CountStringToLApp
						GENFUNCS:Alignment Functions:GEN_ALIGN_CountStringToLApp
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_ALIGN_CountStringToLApp

   PUBLISH NAME:	GEN_ALIGN_CountStringToLApp

	ENTRY CLASS	:	Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int GEN_ALIGN_CountStringToLApp(int normalize_flag, int adjust_char_flag,
	const char *separator_list, unsigned int in_spec_count,
	const char *in_spec_string, unsigned int *structure_size,
	unsigned int *align_count, GEN_ALIGN **align_list, char *error_text)
#else
int GEN_ALIGN_CountStringToLApp(normalize_flag, adjust_char_flag,
	separator_list, in_spec_count, in_spec_string, structure_size, align_count,
	align_list, error_text)
int            normalize_flag;
int            adjust_char_flag;
const char    *separator_list;
unsigned int   in_spec_count;
const char    *in_spec_string;
unsigned int  *structure_size;
unsigned int  *align_count;
GEN_ALIGN    **align_list;
char          *error_text;
#endif /* #ifndef NARGS */
{
	return(GEN_ALIGN_BASIC_CountStringToLApp(0, NULL, normalize_flag,
		adjust_char_flag, separator_list, in_spec_count, in_spec_string,
		structure_size, align_count, align_list, error_text));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_ALIGN_CountStringToString

   SYNOPSIS    :  return_code = GEN_ALIGN_CountStringToString(normalize_flag,
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

   DESCRIPTION :  Transforms an string specification (and associated instance
						count) of the members of a structure into an equivalent
						single string.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``normalize_flag`` indicates whether the elements of
						the temporary ''GEN_ALIGN'' array used in the operation of
						this function are to be normalized vis-a-vis each other.

						(-) Normalization is the combination of like data types from
						adjacent ''GEN_ALIGN'' elements into a single element.

						(-) For example, if array of ''GEN_ALIGN'' elements contains
						the adjacent elements resulting from operation of this
						function on the string:

{|-|}c[10],c[3]

						(-) Normalization of those elements will result in a single
						element equivalent to the string:

{|-|}c[13]

						(-) The ``normalize_flag`` parameter may take on one of the
						following two values:

						(..) ``GENFUNCS_TRUE``, which indicates that the elements
						are to be normalized.

						(..) ``GENFUNCS_FALSE``, which indicates that the elements
						are not to be normalized.

						(.) ``adjust_char_flag`` specifies that ''char'' (and
						''unsigned char'') arrays are to be increased in length
						by a single byte. This is usually to accomodate the
						inclusion of the ''C'' language string null terminator byte.

						(-) The ``adjust_char_flag`` parameter may take on one of
						the following two values:

						(..) ``GENFUNCS_TRUE``, which indicates that ''char''
						elements are to be adjusted.

						(..) ``GENFUNCS_FALSE``, which indicates that ''char''
						elements are not to be adjusted.

						(.) ``separator_list`` is an ASCII NUL (ASCII 0) terminated
						string which lists the characters to be used to separate
						discrete specifications in ``spec_string``.

						(-) if ``separator_list`` is ''NULL'', the comma character
						('','') will be used to separate specifications in
						``spec_string``.

						(.) ``in_spec_count`` is the number of instances
						``in_spec_string`` is to be repeated to produce the
						temporary ''GEN_ALIGN'' array.

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
						least ''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if no error occurs.

						(.) One of the non-zero GENFUNCS Return Codes if an error
						occurs.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  GEN_ALIGN_CountStringToList
						GEN_ALIGN_BASIC_CountStringToString

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_ALIGN_CountStringToString
						Alignment Functions:GEN_ALIGN_CountStringToString
						GENFUNCS:Functions:GEN_ALIGN_CountStringToString
						GENFUNCS:Alignment Functions:GEN_ALIGN_CountStringToString
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_ALIGN_CountStringToString

   PUBLISH NAME:	GEN_ALIGN_CountStringToString

	ENTRY CLASS	:	Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int GEN_ALIGN_CountStringToString(int normalize_flag, int adjust_char_flag,
	const char *separator_list, unsigned int in_spec_count,
	const char *in_spec_string, char **out_spec_string, char *error_text)
#else
int GEN_ALIGN_CountStringToString(normalize_flag, adjust_char_flag,
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
	return(GEN_ALIGN_BASIC_CountStringToString(0, NULL, normalize_flag,
		adjust_char_flag, separator_list, in_spec_count, in_spec_string,
		out_spec_string, error_text));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_ALIGN_AlignList

   SYNOPSIS    :  return_code = GEN_ALIGN_AlignList(structure_size,
							align_count, align_list, error_text);

						int           return_code;

						unsigned int *structure_size;

						unsigned int  align_count;

						GEN_ALIGN    *align_list;

						char         *error_text;

   DESCRIPTION :  Given an array of structures of type ''GEN_ALIGN''
						with the ``type`` and ``array_length`` members populated,
						calculates the total structure size and offset and length
						of each member.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``structure_size`` is a pointer to an ''unsigned int''
						into which will be placed the total size of the structure
						as determined by this function. The size will include
						any alignment bytes required by the implementation.

						(-) If ``structure_size`` is ''NULL'', it will not be
						de-referenced.

						(.) ``align_count`` is an ''unsigned int'' which contains
						the number of elements in the array ``align_list``.

						(.) ``align_list`` is an array of structures of type
						''GEN_ALIGN'' which contains ``align_count``
						elements. The members ``type`` and ``array_length`` of
						each element should contain the values for the desired
						structure.

						(-) If this function is successful, the ``offset``
						and ``length`` members of each element will be updated to
						describe the offset and length requirements for each member
						of the desired structure.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at
						least ''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if no error occurs.

						(.) One of the non-zero GENFUNCS Return Codes if an error
						occurs.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  GEN_ALIGN_BASIC_AlignList
						GEN_ALIGN_AlignString

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_ALIGN_AlignList
						Alignment Functions:GEN_ALIGN_AlignList
						GENFUNCS:Functions:GEN_ALIGN_AlignList
						GENFUNCS:Alignment Functions:GEN_ALIGN_AlignList
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_ALIGN_AlignList

   PUBLISH NAME:	GEN_ALIGN_AlignList

	ENTRY CLASS	:	Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int GEN_ALIGN_AlignList(unsigned int *structure_size, unsigned int align_count,
	GEN_ALIGN *align_list, char *error_text)
#else
int GEN_ALIGN_AlignList(structure_size, align_count, align_list, error_text)
unsigned int *structure_size;
unsigned int  align_count;
GEN_ALIGN    *align_list;
char         *error_text;
#endif /* #ifndef NARGS */
{
	return(GEN_ALIGN_BASIC_AlignList(0, NULL, structure_size, align_count,
		align_list, error_text));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_ALIGN_CheckStringList

   SYNOPSIS    :  return_code = GEN_ALIGN_CheckStringList(separator_list,
							spec_count, spec_list, error_text);

						int            return_code;

						const char    *separator_list;

						unsigned int   spec_count;

						char         **spec_list;

						char          *error_text;

   DESCRIPTION :	Checks to ensure that an array of pointers to strings
						are valid specifications of the primitive type members of
						a structure.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``separator_list`` is an ASCII NUL (ASCII 0) terminated
						string which lists the characters to be used to separate
						discrete specifications in the elements of ``spec_list``.

						(-) if ``separator_list`` is ''NULL'', the comma character
						('','') will be used to separate specifications in
						``spec_string``.

						(.) ``spec_count`` is the number of elements in the
						array ``spec_list``.

						(.) ``spec_list`` is a array of pointers to strings, each
						string of which is a primitive type specification having
						the following format:

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

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at
						least ''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if no error occurs.

						(.) One of the non-zero GENFUNCS return codes if an error
						occurs.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  GEN_ALIGN_BASIC_CheckStringList
						GEN_ALIGN_CheckString
						GEN_ALIGN_AlignStringList

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_ALIGN_CheckStringList
						Alignment Functions:GEN_ALIGN_CheckStringList
						GENFUNCS:Functions:GEN_ALIGN_CheckStringList
						GENFUNCS:Alignment Functions:GEN_ALIGN_CheckStringList
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_ALIGN_CheckStringList

   PUBLISH NAME:	GEN_ALIGN_CheckStringList

	ENTRY CLASS	:	Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int GEN_ALIGN_CheckStringList(const char *separator_list,
	unsigned int spec_count, char **spec_list, char *error_text)
#else
int GEN_ALIGN_CheckStringList(separator_list, spec_count, spec_list,
	error_text)
const char    *separator_list;
unsigned int   spec_count;
char         **spec_list;
char          *error_text;
#endif /* #ifndef NARGS */
{
	return(GEN_ALIGN_BASIC_CheckStringList(0, NULL, separator_list,
		spec_count, spec_list, error_text));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_ALIGN_CheckString

   SYNOPSIS    :  return_code = GEN_ALIGN_CheckString(separator_list,
							spec_string, error_text);

						int         return_code;

						const char *separator_list;

						char       *spec_string;

						char       *error_text;

   DESCRIPTION :  Checks to ensure that a string is a valid specification of
						the primitive type members of a structure.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``separator_list`` is an ASCII NUL (ASCII 0) terminated
						string which lists the characters to be used to separate
						discrete specifications in ``spec_string``.

						(-) if ``separator_list`` is ''NULL'', the comma character
						('','') will be used to separate specifications in
						``spec_string``.

   					(.) ``spec_string`` is the string which contains a list of
						member definitions separated by some combination of the
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

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at
						least ''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if no error occurs.

						(.) One of the non-zero GENFUNCS Return Codes if an error
						occurs.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  GEN_ALIGN_BASIC_CheckString
						GEN_ALIGN_CheckStringList
						GEN_ALIGN_AlignString

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_ALIGN_CheckString
						Alignment Functions:GEN_ALIGN_CheckString
						GENFUNCS:Functions:GEN_ALIGN_CheckString
						GENFUNCS:Alignment Functions:GEN_ALIGN_CheckString
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_ALIGN_CheckString

   PUBLISH NAME:	GEN_ALIGN_CheckString

	ENTRY CLASS	:	Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int GEN_ALIGN_CheckString(const char *separator_list, const char *spec_string,
	char *error_text)
#else
int GEN_ALIGN_CheckString(separator_list, spec_string, error_text)
const char *separator_list;
const char *spec_string;
char       *error_text;
#endif /* #ifndef NARGS */
{
	return(GEN_ALIGN_BASIC_CheckString(0, NULL, separator_list, spec_string,
		error_text));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_ALIGN_CheckMember

   SYNOPSIS    :  return_code = GEN_ALIGN_CheckMember(spec_string, align_ptr,
							error_text);

						int        return_code;

						char      *spec_string;

						GEN_ALIGN *align_ptr;

						char      *error_text;

   DESCRIPTION :  Determines whether a string member definition is correct.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``spec_string`` is the string which contains a member
						definitions. Leading and trailing white-space characters
						are ignored.

						(-) The member definition has the following format:

						(--) { ''b''|''c''|''C''|''s''|''S''|''i''|''I''|''l''|''L''|''f''|''d'' }

						(-) where each letter has the following meaning:

						(..)''b'' is an unsigned (binary) char. The upper-case
						letter ''B'' is also allowed.

						(..) ''c'' is a signed char.

						(..) ''C'' is an unsigned char.

						(..) ''s'' is a signed short integer.

						(..) ''S'' is an unsigned short integer.

						(..) ''i'' is a signed integer.

						(..) ''I'' is an unsigned integer.

						(..) ''l'' is a long integer.

						(..) ''L'' is an unsigned long integer

						(..) ''f'' is a float. The upper-case letter ''F'' is also
						allowed.

						(..) ''d'' is a double. The upper-case letter ''D'' is also
						allowed.

						(-) The member definition may be followed by an optional
						array specifier of the form:

						(--) ``member-definition``[``array-length``]

						(-) Note that ``array-length`` must be greater than zero.

						(.) ``align_ptr`` points to a structure of type
						''GEN_ALIGN''. If the function is successful, it
						will update the ``type``, ``length``, and ``array_length``
						members of the structure to which ``align_ptr`` points.

						(-) Note, however, that if ``align_ptr`` is passed as a
						''NULL'' pointer, it will not be de-referenced.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at
						least ''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if no error occurs.

						(.) One of the non-zero GENFUNCS Return Codes if an error
						occurs.

	NOTES       :

   CAVEATS     :  

   SEE ALSO    :  GEN_ALIGN_AlignString
						GEN_ALIGN_BASIC_CheckMember

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

	OUTPUT INDEX:	GEN_ALIGN_CheckMember
						Alignment Functions:GEN_ALIGN_CheckMember
						GENFUNCS:Functions:GEN_ALIGN_CheckMember
						GENFUNCS:Alignment Functions:GEN_ALIGN_CheckMember
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_ALIGN_CheckMember

   PUBLISH NAME:	GEN_ALIGN_CheckMember

	ENTRY CLASS	:	Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int GEN_ALIGN_CheckMember(const char *spec_string, GEN_ALIGN *align_ptr,
	char *error_text)
#else
int GEN_ALIGN_CheckMember(spec_string, align_ptr, error_text)
const char *spec_string;
GEN_ALIGN  *align_ptr;
char       *error_text;
#endif /* #ifndef NARGS */
{
	return(GEN_ALIGN_BASIC_CheckMember(0, NULL, spec_string, align_ptr,
		error_text));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_ALIGN_ListToStringAlloc

   SYNOPSIS    :  return_code = GEN_ALIGN_ListToStringAlloc(align_count,
							align_list, separator_char, spec_string, error_text);

						int               return_code;

						unsigned int      align_count;

						const GEN_ALIGN  *align_list;

						const char       *separator_char;

						char            **spec_string;

						char             *error_text;

   DESCRIPTION :  Converts an array of ''GEN_ALIGN'' structures to an
						equivalent string representation, for which this function
						allocates memory.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``align_count`` is the number of elements in the array
						``align_list``.

						(.) ``align_list`` is the array of ''GEN_ALIGN'' structures
						which is to be converted to a string.

						(.) ``separator_char`` points to the character to be used
						to separated the string representations of each of the
						elements in ``align_list``.

						(-) if ``separator_char`` is ''NULL'', the comma character
						('','') will be used to separate the string representations.

						(.) ``spec_string`` is a pointer to a pointer to ''char''
						which will be set to the memory allocated to store the
						string representation of ``align_list``.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at
						least ''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if no error occurs.

						(.) One of the non-zero GENFUNCS Return Codes if an error
						occurs.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  GEN_ALIGN_ListToString
						GEN_ALIGN_CalcListToStringLen
						GEN_ALIGN_BASIC_ListToStringAlloc

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_ALIGN_ListToStringAlloc
						Alignment Functions:GEN_ALIGN_ListToStringAlloc
						GENFUNCS:Functions:GEN_ALIGN_ListToStringAlloc
						GENFUNCS:Alignment Functions:GEN_ALIGN_ListToStringAlloc
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_ALIGN_ListToStringAlloc

   PUBLISH NAME:	GEN_ALIGN_ListToStringAlloc

	ENTRY CLASS	:	Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int GEN_ALIGN_ListToStringAlloc(unsigned int align_count,
	const GEN_ALIGN *align_list, const char *separator_char, char **spec_string,
	char *error_text)
#else
int GEN_ALIGN_ListToStringAlloc(align_count, align_list, separator_char,
	spec_string, error_text)
unsigned int      align_count;
const GEN_ALIGN  *align_list;
const char       *separator_char;
char            **spec_string;
char             *error_text;
#endif /* #ifndef NARGS */
{
	return(GEN_ALIGN_BASIC_ListToStringAlloc(0, NULL, align_count, align_list,
		separator_char, spec_string, error_text));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_ALIGN_ListToString

   SYNOPSIS    :  return_code = GEN_ALIGN_ListToString(align_count,
							align_list, separator_char, spec_string, error_text);

						int              return_code;

						unsigned int     align_count;

						const GEN_ALIGN *align_list;

						const char      *separator_char;

						char            *spec_string;

						char            *error_text;

   DESCRIPTION :  Converts an array of ''GEN_ALIGN'' structures to an
						equivalent string representation.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``align_count`` is the number of elements in the array
						``align_list``.

						(.) ``align_list`` is the array of ''GEN_ALIGN'' structures
						which is to be converted to a string.

						(.) ``separator_char`` points to the character to be used
						to separated the string representations of each of the
						elements in ``align_list``.

						(-) if ``separator_char`` is ''NULL'', the comma character
						('','') will be used to separate the string representations.

						(.) ``spec_string`` is a pointer to the memory allocated by
						the invoking function to store the string representation of
						``align_list``.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at
						least ''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if no error occurs.

						(.) One of the non-zero GENFUNCS Return Codes if an error
						occurs.

   NOTES       :  The string ``spec_string`` should be allocated with
						sufficient memory to store the string representation. The
						application programmer to determine the amount of memory
						required by calling the function
						``GEN_ALIGN_CalcListToStringLen`` to determine the memory
						needed and then ``malloc``ing that memory. Alternatively,
						the function related function
						``GEN_ALIGN_ListToStringAlloc``, which allocates the
						proper amount of memory before performing the conversion
						could be used.

   CAVEATS     :  

   SEE ALSO    :  GEN_ALIGN_ListToStringAlloc
						GEN_ALIGN_BASIC_ListToString

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_ALIGN_ListToString
						Alignment Functions:GEN_ALIGN_ListToString
						GENFUNCS:Functions:GEN_ALIGN_ListToString
						GENFUNCS:Alignment Functions:GEN_ALIGN_ListToString
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_ALIGN_ListToString

   PUBLISH NAME:	GEN_ALIGN_ListToString

	ENTRY CLASS	:	Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int GEN_ALIGN_ListToString(unsigned int align_count,
	const GEN_ALIGN *align_list, const char *separator_char, char *spec_string,
	char *error_text)
#else
int GEN_ALIGN_ListToString(align_count, align_list, separator_char,
	spec_string, error_text)
unsigned int     align_count;
const GEN_ALIGN *align_list;
const char      *separator_char;
char            *spec_string;
char            *error_text;
#endif /* #ifndef NARGS */
{
	return(GEN_ALIGN_BASIC_ListToString(0, NULL, align_count, align_list,
		separator_char, spec_string, error_text));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_ALIGN_CopyTypeList

   SYNOPSIS    :  return_code = GEN_ALIGN_CopyTypeList(out_type_count,
							out_type_list, error_text);

						int              return_code;

						unsigned int    *out_type_count;

						GEN_ALIGN_SPEC **out_type_list;

						char            *error_text;

   DESCRIPTION :  Copies a list of ''GEN_ALIGN_SPEC'' primitive type
						specifications.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``out_type_count`` points to an ''unsigned int'' into
						which this function will place the number of elements
						copied into the array to which the ``out_type_list``
						parameter points.

						(.) ``out_type_list`` points to a pointer to
						''GEN_ALIGN_SPEC''. Memory will be allocated by this
						function and the pointer to that memory placed in the
						pointer to which ``out_type_list`` points.

   RETURNS     :  Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if the list was copied without
						error.

						(.) ''GENFUNCS_MEMORY_FAILURE'' if memory could not be
						allocated for the copy.

   CAVEATS     :  

   SEE ALSO    :  GEN_ALIGN_BASIC_CopyTypeList

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_ALIGN_CopyTypeList
						Alignment Functions:GEN_ALIGN_CopyTypeList
						GENFUNCS:Functions:GEN_ALIGN_CopyTypeList
						GENFUNCS:Alignment Functions:GEN_ALIGN_CopyTypeList
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_ALIGN_CopyTypeList

   PUBLISH NAME:	GEN_ALIGN_CopyTypeList

	ENTRY CLASS	:	Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int GEN_ALIGN_CopyTypeList(unsigned int *out_type_count,
	GEN_ALIGN_SPEC **out_type_list,  char *error_text)
#else
int GEN_ALIGN_CopyTypeList(out_type_count, out_type_list, error_text)
unsigned int    *out_type_count;
GEN_ALIGN_SPEC **out_type_list;
char            *error_text;
#endif /* #ifndef NARGS */
{
	return(GEN_ALIGN_BASIC_CopyTypeList(0, NULL, out_type_count, out_type_list,
		error_text));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_ALIGN_FindTypeCharIndex

   SYNOPSIS    :  return_code = GEN_ALIGN_FindTypeCharIndex(type_char,
							type_index);

						int           return_code;

						int           type_char;

						unsigned int *type_index;

   DESCRIPTION :  Attempts to find the type indicated by the ``type_char``
						parameter in the array of primitive types.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``type_char`` is the character to be matched against
						the ``type_abbreviation`` member of the structure
						''GEN_ALIGN_SPEC''.

						(.) ``type_index`` is a pointer to an ''unsigned long'' into
						which this function will place the index matching
						''GEN_ALIGN_SPEC'' element.

						(-) If ``type_index`` is ''NULL'', however, it will not be
						dereferenced.

   RETURNS     :  Returns from this function are as follow:

						(.) If ``type_char`` is found in the array of primitive
						types, this function returns ''GENFUNCS_TRUE''.

						(.) Otherwise, this function returns ''GENFUNCS_FALSE''.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  GEN_ALIGN_FindTypeCharPtr
						GEN_ALIGN_BASIC_FindTypeCharIndex

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_ALIGN_FindTypeCharIndex
						Alignment Functions:GEN_ALIGN_FindTypeCharIndex
						GENFUNCS:Functions:GEN_ALIGN_FindTypeCharIndex
						GENFUNCS:Alignment Functions:GEN_ALIGN_FindTypeCharIndex
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_ALIGN_FindTypeCharIndex

   PUBLISH NAME:	GEN_ALIGN_FindTypeCharIndex

	ENTRY CLASS	:	Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int GEN_ALIGN_FindTypeCharIndex(int type_char, unsigned int *type_index)
#else
int GEN_ALIGN_FindTypeCharIndex(type_char, type_index)
int           type_char;
unsigned int *type_index;
#endif /* #ifndef NARGS */
{
	return(GEN_ALIGN_BASIC_FindTypeCharIndex(0, NULL, type_char, type_index));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_ALIGN_FindTypeCharPtr

   SYNOPSIS    :  return_ptr = GEN_ALIGN_FindTypeCharPtr(type_char,
							type_index);

						const GEN_ALIGN_SPEC *return_ptr;

						int                   type_char;

						unsigned int         *type_index;

   DESCRIPTION :  Returns a pointer to the type indicated by the ``type_char``
						parameter in the array of primitive types.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``type_char`` is the character to be matched against
						the ``type_abbreviation`` member of the structure
						''GEN_ALIGN_SPEC''.

						(.) ``type_index`` is a pointer to an ''unsigned long'' into
						which this function will place the index matching
						''GEN_ALIGN_SPEC'' element.

						(-) If ``type_index`` is ''NULL'', however, it will not be
						dereferenced.

   RETURNS     :  Returns from this function are as follow:

						(.) If ``type_char`` is found in the array of primitive
						types, a pointer to matching element in that array is
						returned.

						(.) Otherwise, this function returns ''NULL''.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  GEN_ALIGN_FindTypeCharIndex
						GEN_ALIGN_BASIC_FindTypeCharPtr

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_ALIGN_FindTypeCharPtr
						Alignment Functions:GEN_ALIGN_FindTypeCharPtr
						GENFUNCS:Functions:GEN_ALIGN_FindTypeCharPtr
						GENFUNCS:Alignment Functions:GEN_ALIGN_FindTypeCharPtr
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_ALIGN_FindTypeCharPtr

   PUBLISH NAME:	GEN_ALIGN_FindTypeCharPtr

	ENTRY CLASS	:	Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
const GEN_ALIGN_SPEC *GEN_ALIGN_FindTypeCharPtr(int type_char,
	unsigned int *type_index)
#else
const GEN_ALIGN_SPEC *GEN_ALIGN_FindTypeCharPtr(type_char, type_index)
int           type_char;
unsigned int *type_index;
#endif /* #ifndef NARGS */
{
	return(GEN_ALIGN_BASIC_FindTypeCharPtr(0, NULL, type_char, type_index));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_ALIGN_GetTypePtr

   SYNOPSIS    :  return_ptr = GEN_ALIGN_GetTypePtr(type_index);

						const GEN_ALIGN_SPEC *return_ptr;

						unsigned int          type_index;

   DESCRIPTION :  Returns a pointer to ''GEN_ALIGN_SPEC''

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``type_index`` is the index into the array of primitive
						types for which a pointer is desired. It must be less than
						the total number of primitive types.

   RETURNS     :  Returns from this function are as follow:

						(.) If ``type_index`` is valid, a pointer to element
						indicated by ``type_index`` is returned.

						(.) Otherwise, this function returns ''NULL''.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  GEN_ALIGN_BASIC_GetTypePtr

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_ALIGN_GetTypePtr
						Alignment Functions:GEN_ALIGN_GetTypePtr
						GENFUNCS:Functions:GEN_ALIGN_GetTypePtr
						GENFUNCS:Alignment Functions:GEN_ALIGN_GetTypePtr
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_ALIGN_GetTypePtr

   PUBLISH NAME:	GEN_ALIGN_GetTypePtr

	ENTRY CLASS	:	Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
const GEN_ALIGN_SPEC *GEN_ALIGN_GetTypePtr(unsigned int type_index)
#else
const GEN_ALIGN_SPEC *GEN_ALIGN_GetTypePtr(type_index)
unsigned int type_index;
#endif /* #ifndef NARGS */
{
	return(GEN_ALIGN_BASIC_GetTypePtr(0, NULL, type_index));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_ALIGN_NormalizeList

   SYNOPSIS    :  GEN_ALIGN_NormalizeList(align_count, align_list);

						unsigned int  *align_count;

						GEN_ALIGN    **align_list;

   DESCRIPTION :  Normalizes an array of ''GEN_ALIGN'' structures by
						concatenating adjacent similar type specifications into
						a single type specification.

						For example, if ``align_list`` contains the adjacent
						elements equivalent to:

{|@|}c[10]c[3]

						Normalization of those elements will result in a single
						element equivalent to:

{|@|}c[13]

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``align_count`` is the number of elements in the array
						``align_list``.

						(.) ``align_list`` is the array of ''GEN_ALIGN'' structures
						which is to be normalized.

   RETURNS     :  Void.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  GEN_ALIGN_NormalizeList

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_ALIGN_NormalizeList
						Alignment Functions:GEN_ALIGN_NormalizeList
						GENFUNCS:Functions:GEN_ALIGN_NormalizeList
						GENFUNCS:Alignment Functions:GEN_ALIGN_NormalizeList
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_ALIGN_NormalizeList

   PUBLISH NAME:	GEN_ALIGN_NormalizeList

	ENTRY CLASS	:	Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
void GEN_ALIGN_NormalizeList(unsigned int *align_count, GEN_ALIGN **align_list)
#else
void GEN_ALIGN_NormalizeList(align_count, align_list)
unsigned int  *align_count;
GEN_ALIGN    **align_list;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;

	for (count_1 = 1; count_1 < *align_count; ) {
		if ((*align_list)[count_1].type == (*align_list)[count_1 - 1].type) {
			(*align_list)[count_1 - 1].array_length +=
				(*align_list)[count_1].array_length;
			(*align_list)[count_1 - 1].length       +=
				(*align_list)[count_1].length;
			mema_remove(align_count, ((void **) align_list),
				sizeof(**align_list), count_1, 1);
		}
		else
			count_1++;
	}
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_ALIGN_CalcListToStringLen

   SYNOPSIS    :  string_length = GEN_ALIGN_CalcListToStringLen(align_count,
							align_list);

						unsigned int     string_count;

						unsigned int     align_count;

						const GEN_ALIGN *align_list;

   DESCRIPTION :  Calculates the string length (including terminating ASCII
						0) required to store the string equivalent of an array
						of ''GEN_ALIGN'' structures.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``align_count`` is the number of elements in the array
						``align_list``.

						(.) ``align_list`` is the array of ''GEN_ALIGN'' structures
						for which the string length is to be calculated.

   RETURNS     :  Returns from this function are as follow:

   NOTES       :  This function is used by the functions
						``GEN_ALIGN_ListToStringAlloc`` and
						``GEN_ALIGN_BASIC_ListToStringAlloc`` to determine the
						amount of memory to allocate for storage of an array of
						''GEN_ALIGN'' structures as a string.

   CAVEATS     :  

   SEE ALSO    :  

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_ALIGN_CalcListToStringLen
						Alignment Functions:GEN_ALIGN_CalcListToStringLen
						GENFUNCS:Functions:GEN_ALIGN_CalcListToStringLen
						GENFUNCS:Alignment Functions:GEN_ALIGN_CalcListToStringLen
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_ALIGN_CalcListToStringLen

   PUBLISH NAME:	GEN_ALIGN_CalcListToStringLen

	ENTRY CLASS	:	Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
unsigned int GEN_ALIGN_CalcListToStringLen(unsigned int align_count,
	const GEN_ALIGN *align_list)
#else
unsigned int GEN_ALIGN_CalcListToStringLen(align_count, align_list)
unsigned int     align_count;
const GEN_ALIGN *align_list;
#endif /* #ifndef NARGS */
{
	unsigned int string_length = 1;
	unsigned int count_1;
	char         buffer[STR_VAL2STR_MAX_LEN + 1];

	for (count_1 = 0; count_1 < align_count; count_1++)
		string_length += 1 + ((align_list[count_1].array_length <= 1) ? 0 : (1 +
			strlen(val2str(((unsigned long) align_list[count_1].array_length),
			0, 10, NULL, buffer)) + 1));

	return(string_length);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_ALIGN_InitAlign

   SYNOPSIS    :  GEN_ALIGN_InitAlign(align_ptr);

						GEN_ALIGN *align_ptr;

   DESCRIPTION :  Initializes a ''GEN_ALIGN'' structure.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``align_ptr`` points to the ''GEN_ALIGN'' structure
						to be initialized.

   RETURNS     :  Void.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_ALIGN_InitAlign
						Alignment Functions:GEN_ALIGN_InitAlign
						GENFUNCS:Functions:GEN_ALIGN_InitAlign
						GENFUNCS:Alignment Functions:GEN_ALIGN_InitAlign
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_ALIGN_InitAlign

   PUBLISH NAME:	GEN_ALIGN_InitAlign

	ENTRY CLASS	:	Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
void GEN_ALIGN_InitAlign(GEN_ALIGN *align_ptr)
#else
void GEN_ALIGN_InitAlign(align_ptr)
GEN_ALIGN *align_ptr;
#endif /* #ifndef NARGS */
{
	align_ptr->type         = 0;
	align_ptr->array_length = 0;
	align_ptr->offset       = 0;
	align_ptr->length       = 0;
}
/* *********************************************************************** */

#ifndef NARGS
int GEN_ALIGN_CompareList(GEN_ALIGN_CMP *align_cmp_ptr, const void *data_ptr_1,
	const void *data_ptr_2, size_t data_length)
#else
int GEN_ALIGN_CompareList(align_cmp_ptr, data_ptr_1, data_ptr_2,
	data_length)
GEN_ALIGN_CMP *align_cmp_ptr;
const void    *data_ptr_1;
const void    *data_ptr_2;
size_t         data_length;
#endif /* #ifndef NARGS */
{
	int          cmp = 0;
	unsigned int count_1;

	for (count_1 = 0; count_1 < align_cmp_ptr->align_count; count_1++) {
		if ((align_cmp_ptr->align_list[count_1].type >= GEN_AlignCount) ||
			((cmp = (*GEN_AlignList[align_cmp_ptr->align_list[count_1].type].
			compare_method)(align_cmp_ptr->align_list + count_1,
			((char *) data_ptr_1) + align_cmp_ptr->align_list[count_1].offset,
			((char *) data_ptr_2) + align_cmp_ptr->align_list[count_1].offset,
			data_length)) != 0))
			break;
	}

	return(cmp);
}
/* *********************************************************************** */

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_SCMP_ubyte(GEN_ALIGN *align_ptr, const unsigned char *ptr_1,
	const unsigned char *ptr_2, size_t data_length)
#else
int GEN_SCMP_ubyte(align_ptr, ptr_1, ptr_2, data_length)
GEN_ALIGN           *align_ptr;
const unsigned char *ptr_1;
const unsigned char *ptr_2;
size_t               data_length;
#endif /* #ifndef NARGS */
{
	return(memcmp(ptr_1, ptr_2, align_ptr->array_length * sizeof(*ptr_1)));
}
/* *********************************************************************** */
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_SCMP_char(GEN_ALIGN *align_ptr, const char *ptr_1,
	const char *ptr_2, size_t data_length)
#else
int GEN_SCMP_char(align_ptr, ptr_1, ptr_2, data_length)
GEN_ALIGN  *align_ptr;
const char *ptr_1;
const char *ptr_2;
size_t      data_length;
#endif /* #ifndef NARGS */
{
	return(strncmp(ptr_1, ptr_2, align_ptr->array_length * sizeof(*ptr_1)));
}
/* *********************************************************************** */
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_SCMP_uchar(GEN_ALIGN *align_ptr, const unsigned char *ptr_1,
	const unsigned char *ptr_2, size_t data_length)
#else
int GEN_SCMP_uchar(align_ptr, ptr_1, ptr_2, data_length)
GEN_ALIGN           *align_ptr;
const unsigned char *ptr_1;
const unsigned char *ptr_2;
size_t               data_length;
#endif /* #ifndef NARGS */
{
	return(strncmp(((const char *) ptr_1), ((const char *) ptr_2),
		align_ptr->array_length * sizeof(*ptr_1)));
}
/* *********************************************************************** */
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_SCMP_short(GEN_ALIGN *align_ptr, const short *ptr_1,
	const short *ptr_2, size_t data_length)
#else
int GEN_SCMP_short(align_ptr, ptr_1, ptr_2, data_length)
GEN_ALIGN   *align_ptr;
const short *ptr_1;
const short *ptr_2;
size_t       data_length;
#endif /* #ifndef NARGS */
{
	int          cmp = 0;
	unsigned int count_1;

	for (count_1 = 0; count_1 < align_ptr->array_length; count_1++) {
		if ((cmp =
			((int) ((*ptr_1 > *ptr_2) ? 1 : (*ptr_1 < *ptr_2) ? -1 : 0))) != 0)
			break;
	}

	return(cmp);
}
/* *********************************************************************** */
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_SCMP_ushort(GEN_ALIGN *align_ptr, const unsigned short *ptr_1,
	const unsigned short *ptr_2, size_t data_length)
#else
int GEN_SCMP_ushort(align_ptr, ptr_1, ptr_2, data_length)
GEN_ALIGN            *align_ptr;
const unsigned short *ptr_1;
const unsigned short *ptr_2;
size_t                data_length;
#endif /* #ifndef NARGS */
{
	int          cmp = 0;
	unsigned int count_1;

	for (count_1 = 0; count_1 < align_ptr->array_length; count_1++) {
		if ((cmp =
			((int) ((*ptr_1 > *ptr_2) ? 1 : (*ptr_1 < *ptr_2) ? -1 : 0))) != 0)
			break;
	}

	return(cmp);
}
/* *********************************************************************** */
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_SCMP_int(GEN_ALIGN *align_ptr, const int *ptr_1, const int *ptr_2,
	size_t data_length)
#else
int GEN_SCMP_int(align_ptr, ptr_1, ptr_2, data_length)
GEN_ALIGN *align_ptr;
const int *ptr_1;
const int *ptr_2;
size_t     data_length;
#endif /* #ifndef NARGS */
{
	int          cmp = 0;
	unsigned int count_1;

	for (count_1 = 0; count_1 < align_ptr->array_length; count_1++) {
		if ((cmp =
			((int) ((*ptr_1 > *ptr_2) ? 1 : (*ptr_1 < *ptr_2) ? -1 : 0))) != 0)
			break;
	}

	return(cmp);
}
/* *********************************************************************** */
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_SCMP_uint(GEN_ALIGN *align_ptr, const unsigned int *ptr_1,
	const unsigned int *ptr_2, size_t data_length)
#else
int GEN_SCMP_uint(align_ptr, ptr_1, ptr_2, data_length)
GEN_ALIGN          *align_ptr;
const unsigned int *ptr_1;
const unsigned int *ptr_2;
size_t              data_length;
#endif /* #ifndef NARGS */
{
	int          cmp = 0;
	unsigned int count_1;

	for (count_1 = 0; count_1 < align_ptr->array_length; count_1++) {
		if ((cmp =
			((int) ((*ptr_1 > *ptr_2) ? 1 : (*ptr_1 < *ptr_2) ? -1 : 0))) != 0)
			break;
	}

	return(cmp);
}
/* *********************************************************************** */
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_SCMP_long(GEN_ALIGN *align_ptr, const long *ptr_1, const long *ptr_2,
	size_t data_length)
#else
int GEN_SCMP_long(align_ptr, ptr_1, ptr_2, data_length)
GEN_ALIGN  *align_ptr;
const long *ptr_1;
const long *ptr_2;
size_t      data_length;
#endif /* #ifndef NARGS */
{
	int          cmp = 0;
	unsigned int count_1;

	for (count_1 = 0; count_1 < align_ptr->array_length; count_1++) {
		if ((cmp =
			((int) ((*ptr_1 > *ptr_2) ? 1 : (*ptr_1 < *ptr_2) ? -1 : 0))) != 0)
			break;
	}

	return(cmp);
}
/* *********************************************************************** */
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_SCMP_ulong(GEN_ALIGN *align_ptr, const unsigned long *ptr_1,
	const unsigned long *ptr_2, size_t data_length)
#else
int GEN_SCMP_ulong(align_ptr, ptr_1, ptr_2, data_length)
GEN_ALIGN           *align_ptr;
const unsigned long *ptr_1;
const unsigned long *ptr_2;
size_t               data_length;
#endif /* #ifndef NARGS */
{
	int          cmp = 0;
	unsigned int count_1;

	for (count_1 = 0; count_1 < align_ptr->array_length; count_1++) {
		if ((cmp =
			((int) ((*ptr_1 > *ptr_2) ? 1 : (*ptr_1 < *ptr_2) ? -1 : 0))) != 0)
			break;
	}

	return(cmp);
}
/* *********************************************************************** */
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_SCMP_float(GEN_ALIGN *align_ptr, const float *ptr_1,
	const float *ptr_2, size_t data_length)
#else
int GEN_SCMP_float(align_ptr, ptr_1, ptr_2, data_length)
GEN_ALIGN   *align_ptr;
const float *ptr_1;
const float *ptr_2;
size_t       data_length;
#endif /* #ifndef NARGS */
{
	int          cmp = 0;
	unsigned int count_1;

	for (count_1 = 0; count_1 < align_ptr->array_length; count_1++) {
		if ((cmp =
			((int) ((*ptr_1 > *ptr_2) ? 1 : (*ptr_1 < *ptr_2) ? -1 : 0))) != 0)
			break;
	}

	return(cmp);
}
/* *********************************************************************** */
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_SCMP_double(GEN_ALIGN *align_ptr, const double *ptr_1,
	const double *ptr_2, size_t data_length)
#else
int GEN_SCMP_double(align_ptr, ptr_1, ptr_2, data_length)
GEN_ALIGN    *align_ptr;
const double *ptr_1;
const double *ptr_2;
size_t        data_length;
#endif /* #ifndef NARGS */
{
	int          cmp = 0;
	unsigned int count_1;

	for (count_1 = 0; count_1 < align_ptr->array_length; count_1++) {
		if ((cmp =
			((int) ((*ptr_1 > *ptr_2) ? 1 : (*ptr_1 < *ptr_2) ? -1 : 0))) != 0)
			break;
	}

	return(cmp);
}
/* *********************************************************************** */
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

/*
	CODE NOTE: Preserved for backards compatibility. To be removed.
*/
#ifndef NARGS
int GEN_ALIGN_GetFieldAlignList(unsigned int member_count,
	const char *member_spec, int adjust_char_flag, unsigned int *align_size,
	unsigned int *align_count, GEN_ALIGN **align_list, char *error_text)
#else
int GEN_ALIGN_GetFieldAlignList(member_count, member_spec, adjust_char_flag,
	align_size, align_count, align_list, error_text)
unsigned int     member_count;
const char      *member_spec;
int              adjust_char_flag;
unsigned int    *align_size;
unsigned int    *align_count;
GEN_ALIGN      **align_list;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code;
	unsigned int  tmp_align_count = 0;
	GEN_ALIGN    *tmp_align_list  = NULL;
	unsigned int  tmp_align_size;
	unsigned int  tmp_type_count;
	unsigned int  count_1;
	unsigned int  count_2;

	*align_size  = 0;
	*align_count = 0;
	*align_list  = NULL;

	if (!member_count) {
		strcpy(error_text, "The primitive type count is zero ('0').");
		return_code = GENFUNCS_FAILURE;
	}
	else if ((member_spec == NULL) || (!(*member_spec))) {
		strcpy(error_text,
			"The pointer to the meta-data type is 'NULL' or zero-length.");
		return_code = GENFUNCS_FAILURE;
	}
	else if ((return_code = GEN_ALIGN_AlignFromString(member_spec,
		&tmp_align_size, &tmp_align_count, &tmp_align_list, error_text)) ==
		GENFUNCS_SUCCESS) {
		tmp_type_count = member_count;
		tmp_type_count = (tmp_align_count == 1) ? 1 : tmp_type_count;
		if ((*align_list = ((GEN_ALIGN *) calloc(tmp_align_count *
			tmp_type_count, sizeof(GEN_ALIGN)))) == NULL) {
			sprintf(error_text, "%s (%u elements * %u size = %u total bytes).",
				"Unable to allocate memory for the array of field align elements",
				tmp_align_count * tmp_type_count, sizeof(GEN_ALIGN),
				tmp_align_count * tmp_type_count * sizeof(GEN_ALIGN));
			return_code = GENFUNCS_MEMORY_FAILURE;
		}
		else {
			if (tmp_align_count == 1) {
				tmp_align_list->array_length  =
					((int) ((!member_count) ? 1 : member_count));
				tmp_align_list->length       *= tmp_align_list->array_length;
				*align_count                  = 1;
				**align_list                  = *tmp_align_list;
				*align_size                   = tmp_align_list->length;
			}
			else {
				for (count_1 = 0; count_1 < tmp_type_count; count_1++) {
					for (count_2 = 0; count_2 < tmp_align_count; count_2++) {
						(*align_list)[(*align_count)]           =
							tmp_align_list[count_2];
						(*align_list)[(*align_count)++].offset +=
							(tmp_align_size * count_1);
					}
				}
			}
			for (count_1 = 0; count_1 < *align_count; count_1++)
				(*align_list)[count_1].array_length +=
					(((*align_list)[count_1].type == GEN_C_ALIGN_char) ||
					((*align_list)[count_1].type == GEN_C_ALIGN_unsigned_char)) ?
					((adjust_char_flag == GENFUNCS_TRUE) ? 1 : 0) : 0;
			if (GEN_ALIGN_Align(align_size, *align_count, *align_list,
				error_text) != GENFUNCS_SUCCESS) {
				free(*align_list);
				*align_count = 0;
				*align_list  = NULL;
				return_code  = GENFUNCS_FAILURE;
			}
		}
		mema_remove_all(&tmp_align_count, ((void **) &tmp_align_list));
	}

	return(return_code);
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_ALIGN_AlignFromString

   SYNOPSIS    :  return_code = GEN_ALIGN_AlignFromString(in_string,
							structure_size, align_count, align_list, error_text);

						int            return_code;

						char          *in_string;

						unsigned int  *structure_size;

						unsigned int  *align_count;

						GEN_ALIGN    **align_list;

						char          *error_text;

   DESCRIPTION :  Transforms a string description of the members of a
						structure into an array on structures of type
						''GEN_ALIGN'', the elements of which contain
						offset and length data for each member.

   PARAMETERS  :  Parameters to this function are as follow:

   					(.) ``in_string`` is the string which contains a list of
						member definitions separated by some combination of
						white-space and commas (``,``). Leading and trailing
						white-space characters or commas are ignored.

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

						(.) ``structure_size`` is a pointer to an unsigned int into
						which will be placed the total size of the structure
						as determined by this function. The size will include
						any alignment bytes required by the implementation.

						(-) If ``structure_size`` is ''NULL'', it will not be
						de-referenced.

						(.) ``align_count`` is a pointer to an unsigned int into
						which will be placed the number of members which were
						parsed out of the string ``in_string``.

						(.) ``align_list`` points to a pointer to a structure of
						type ''GEN_ALIGN''. If the function is
						successful, it will allocate memory sufficient to hold
						``align_count`` elements. Each element will describe the
						offset and length requirements for each member of the
						desired structure.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur. The string allocated for this purpose should
						be at least ''GENFUNCS_MAX_ERROR_TEXT'' characters in
						length.

   RETURNS     :  Returns from this function are as follow:

						(.) zero if no error occurs.

						(.) non-zero if an error occurs.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  GEN_ALIGN_CheckMember
						GEN_ALIGN_Align

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_ALIGN_AlignFromString
						Alignment Functions:GEN_ALIGN_AlignFromString
						GENFUNCS:Functions:GEN_ALIGN_AlignFromString
						GENFUNCS:Alignment Functions:GEN_ALIGN_AlignFromString
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_ALIGN_AlignFromString

   PUBLISH NAME:	GEN_ALIGN_AlignFromString

	ENTRY CLASS	:	Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int GEN_ALIGN_AlignFromString(const char *in_string,
	unsigned int *structure_size, unsigned int *align_count,
	GEN_ALIGN **align_list, char *error_text)
#else
int GEN_ALIGN_AlignFromString(in_string, structure_size, align_count,
	align_list, error_text)
const char    *in_string;
unsigned int  *structure_size;
unsigned int  *align_count;
GEN_ALIGN    **align_list;
char          *error_text;
#endif /* #ifndef NARGS */
{
	return(GEN_ALIGN_BASIC_AlignString(0, NULL, GENFUNCS_FALSE, GENFUNCS_FALSE,
		",", in_string, structure_size, align_count, align_list, error_text));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_ALIGN_Align

   SYNOPSIS    :  return_code = GEN_ALIGN_Align(structure_size, align_count,
							align_list, error_text);

						int           return_code;

						unsigned int *structure_size;

						unsigned int  align_count;

						GEN_ALIGN    *align_list;

						char         *error_text;

   DESCRIPTION :  Given an array of structures of type ''GEN_ALIGN''
						with the ``type`` and ``array_length`` members populated,
						calculates the total structure size and offset and length
						of each member.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``structure_size`` is a pointer to an unsigned int into
						which will be placed the total size of the structure
						as determined by this function. The size will include
						any alignment bytes required by the implementation.

						(-) If ``structure_size`` is ''NULL'', it will not be
						de-referenced.

						(.) ``align_count`` is an unsigned int which contains the number
						of elements in the array ``align_list``.

						(.) ``align_list`` is an array of structures of type
						''GEN_ALIGN'' which contains ``align_count``
						elements. The members ``type`` and ``array_length`` of
						each element should contain the values for the desired
						structure. If the function is successful, the ``offset``
						and ``length`` members of each element will describe the
						offset and length requirements for each member of the
						desired structure.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur. The string allocated for this purpose should
						be at least ''GENFUNCS_MAX_ERROR_TEXT'' characters in
						length.

   RETURNS     :  Returns from this function are as follow:

						(.) zero if no error occurs.

						(.) non-zero if an error occurs.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  GEN_ALIGN_AlignFromString

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_ALIGN_Align
						Alignment Functions:GEN_ALIGN_Align
						GENFUNCS:Functions:GEN_ALIGN_Align
						GENFUNCS:Alignment Functions:GEN_ALIGN_Align
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_ALIGN_Align

   PUBLISH NAME:	GEN_ALIGN_Align

	ENTRY CLASS	:	Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int GEN_ALIGN_Align(unsigned int *structure_size, unsigned int align_count,
	GEN_ALIGN *align_list, char *error_text)
#else
int GEN_ALIGN_Align(structure_size, align_count, align_list, error_text)
unsigned int *structure_size;
unsigned int  align_count;
GEN_ALIGN    *align_list;
char         *error_text;
#endif /* #ifndef NARGS */
{
	return(GEN_ALIGN_BASIC_AlignList(0, NULL, structure_size, align_count,
		align_list, error_text));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* *********************************************************************** */

#ifdef TEST_MAIN

COMPAT_FN_DECL(int main, (void));

int main()
{
	int            return_code     = 0;
	unsigned int   align_count     = 0;
	GEN_ALIGN     *align_list      = NULL;
	unsigned long  line_count      = 0L;
	unsigned int   structure_count = 1;
	unsigned int   count_1;
	unsigned int   structure_size;
	char           buffer[512];
	char           error_text[GENFUNCS_MAX_ERROR_TEXT];
	FILE          *file_ptr;

#ifdef __MSDOS__
	char             *compile_string =
		"bcc -Ic:\borlandc\include -Lc:\borlandc\lib aligntst.c";
	char             *execute_string = "aligntst.exe";
#else
	char              compile_buffer[1024];
	char             *compile_string = compile_buffer;
	char             *execute_string = "a.out";

	strcpy(compile_string, "cc ");
#ifdef NARGS
	strcat(compile_string, "-DNARGS=1 ");
#endif /* #ifdef NARGS */
#ifdef NO_CONST
	strcat(compile_string, "-Dconst=\"\" ");
#endif /* #ifdef NO_CONST */
#ifdef NO_VOLATILE
	strcat(compile_string, "-Dvolatile=\"\" ");
#endif /* #ifdef NO_VOLATILE */
#ifdef NO_VOID
	strcat(compile_string, "-Dvoid=\"\" ");
#endif /* #ifdef NO_VOID */
#ifdef NO_SIZE_T
	strcat(compile_string, "-Dsize_t=\"unsigned int\" ");
#endif /* #ifdef NO_SIZE_T */
	strcat(compile_string, "aligntst.c");
#endif /* #ifdef __MSDOS__ */

	fprintf(stderr, "Test of Function 'GEN_ALIGN_AlignFromString()'\n\n");

	if ((file_ptr = fopen("aligntst.c", "w")) == NULL) {
		fprintf(stderr, "Unable to open file 'aligntst.c' for output.\n");
		exit(-1);
	}

	fprintf(file_ptr, "#include <stdio.h>\n\n");
	fprintf(file_ptr, "#ifndef NARGS\n");
	fprintf(file_ptr, "int main(void);\n");
	fprintf(file_ptr, "#else\n");
	fprintf(file_ptr, "int main();\n");
	fprintf(file_ptr, "#endif /* #ifndef NARGS */\n\n");
	fprintf(file_ptr, "#ifndef offsetof\n");
	fprintf(file_ptr, "# define offsetof(structure_name, member_name) \\\n");
	fprintf(file_ptr, "\t((size_t) &(((structure_name *) 0)->member_name))\n");
	fprintf(file_ptr, "#endif /* #ifndef offsetof */\n\n");

	while ((!feof(stdin)) && (!ferror(stdin))) {
		*buffer = '\0';
		while (!(*buffer)) {
			if (fgets(buffer, sizeof(buffer) - 1, stdin) == NULL) {
				strcpy(buffer, "QUIT");
				break;
			}
			while (strlen(buffer) && (buffer[strlen(buffer) - 1] == '\n'))
				buffer[strlen(buffer) - 1] = '\0';
			line_count++;
		}
		if ((!stricmp(buffer, "QUIT")) || (!stricmp(buffer, "EXIT")) ||
			(!stricmp(buffer, "END")))
			break;
		if ((return_code = GEN_ALIGN_AlignFromString(buffer, &structure_size,
			&align_count, &align_list, error_text)) != 0) {
			fprintf(stderr, "ERROR: %s\n", error_text);
			break;
		}
		else {
			fprintf(file_ptr, "/* STRUCTURE DEFINITION: %s */\n\n", buffer);
			fprintf(file_ptr, "/* sizeof(STRUCTURE_%05u) = %u */\n",
				structure_count, structure_size);
			fprintf(file_ptr, "typedef struct {\n");
			for (count_1 = 0; count_1 < align_count; count_1++) {
				fprintf(file_ptr, "\t%s member_%05u",
					GEN_AlignList[align_list[count_1].type].type_name,
					count_1 + 1);
				if (align_list[count_1].array_length > 1)
					fprintf(file_ptr, "[%u]", align_list[count_1].array_length);
				fprintf(file_ptr, "; /* Offset = %u, length = %u */\n",
				align_list[count_1].offset, align_list[count_1].length);
			}
			fprintf(file_ptr, "} STRUCTURE_%05u;\n\n", structure_count);
			fprintf(file_ptr, "#ifndef NARGS\n");
			fprintf(file_ptr, "int Test_STRUCTURE_%05u(void);\n",
				structure_count);
			fprintf(file_ptr, "#else\n");
			fprintf(file_ptr, "int Test_STRUCTURE_%05u();\n",
				structure_count);
			fprintf(file_ptr, "#endif /* #ifndef NARGS */\n\n");
			fprintf(file_ptr, "int Test_STRUCTURE_%05u()\n{\n",
				structure_count);
			fprintf(file_ptr, "	int return_code = 1;\n\n");
			fprintf(file_ptr, "\tif (sizeof(STRUCTURE_%05u) != %u)\n",
				structure_count, structure_size);
			fprintf(file_ptr,
				"\t\tfprintf(stderr, \"Error on STRUCTURE_%05u: ",
				structure_count);
			fprintf(file_ptr, "size is %%u, should be %u.\\n\",\n",
				structure_size);
			fprintf(file_ptr, "\t\t\tsizeof(STRUCTURE_%05u));\n",
				structure_count);
			for (count_1 = 0; count_1 < align_count; count_1++) {
				fprintf(file_ptr,
"\telse if (offsetof(STRUCTURE_%05u, member_%05u) != %u)\n",
					structure_count, count_1 + 1, align_list[count_1].offset);
				fprintf(file_ptr,
					"\t\tfprintf(stderr, \"Error on member_%05u member ",
					count_1 + 1);
				fprintf(file_ptr,
					"of structure STRUCTURE_%05u (%s): ", structure_count,
					GEN_AlignList[align_list[count_1].type].type_name);
				fprintf(file_ptr, "offset is %%u, should be %u.\\n\",\n",
					align_list[count_1].offset);
				fprintf(file_ptr,
					"\t\t\toffsetof(STRUCTURE_%05u, member_%05u));\n",
					structure_count, count_1 + 1);
			}
			fprintf(file_ptr, "\telse {\n");
			fprintf(file_ptr,
				"\t\tfprintf(stderr, \"STRUCTURE_%05u IS OK\\n\");\n",
				structure_count);
			fprintf(file_ptr, "\t\treturn_code = 0;\n\n");
			fprintf(file_ptr, "\t}\n\n");
			fprintf(file_ptr, "\treturn(return_code);\n");
			fprintf(file_ptr, "}\n\n");
			free(align_list);
			structure_count++;
			fprintf(stderr, "OK\n");
		}
	}

	if ((!return_code) && structure_count) {
		fprintf(file_ptr, "int main()\n{\n");
		fprintf(file_ptr, "\tint return_code = 0;\n\n");
		for (count_1 = 1; count_1 < structure_count; count_1++) {
			fprintf(file_ptr, "\tif (Test_STRUCTURE_%05u())\n", count_1);
			fprintf(file_ptr, "\t\treturn_code = 1;\n");
		}
		fprintf(file_ptr, "\n\treturn(return_code);\n}\n");
		fclose(file_ptr);
		fprintf(stderr, "Compiling test program . . .");
		system(compile_string);
		fprintf(stderr, "\n");
		fprintf(stderr, "Executing test program . . .\n");
		system(execute_string);
	}

	return(return_code);
}
/* *********************************************************************** */

#endif /* #ifdef TEST_MAIN */

