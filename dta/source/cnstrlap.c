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
								equivalent array of 'DTA' structures and appends
								that new array to the specified array.

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

#include <memory.h>
#include <stdlib.h>

#include "dtai.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  DTA_BASIC_CountStringToLApp

   SYNOPSIS    :  return_code =
							DTA_BASIC_CountStringToLApp(type_count,
							type_list, normalize_flag, adjust_char_flag,
							separator_list, in_spec_count, in_spec_string,
							structure_size, align_count, align_list, error_text);

						int              return_code;

						unsigned int     type_count;

						const DTA_TYPE  *type_list;

						int              normalize_flag;

						int              adjust_char_flag;

						const char      *separator_list;

						unsigned int     in_spec_count;

						const char      *in_spec_string;

						unsigned int    *structure_size;

						unsigned int    *align_count;

						DTA            **align_list;

						char            *error_text;

   DESCRIPTION :  Transforms a string specification (and associated instance
						count) of the members of a structure into an array of
						structures of type ''DTA''. These structures are then
						appended to the list represented by the ``align_count`` and
						``align_list`` parameters.

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
						type ''DTA''. If the function is
						successful, it will allocate memory sufficient to hold
						``align_count`` elements. Each element will describe the
						offset and length requirements for each member of the
						desired structure.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at
						least ''DTA_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DTA_SUCCESS'' if no error occurs.

						(.) One of the non-zero DTA Return Codes if an error
						occurs.

   NOTES       :  This function appends members parsed out of the
						``in_spec_string`` parameter to the list represented by
						``align_count`` and ``align_list``. If you do not want
						this behavior, use the related function
						``DTA_BASIC_CountStringToList``.

   CAVEATS     :  

   SEE ALSO    :  DTA_BASIC_CountStringToList
						DTA_CountStringToLApp

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2016 Michael L. Brock

   OUTPUT INDEX:	DTA_BASIC_CountStringToLApp
						Data Type Alignment Functions:DTA_BASIC_CountStringToLApp
						DTA:Functions:DTA_BASIC_CountStringToLApp
						DTA:Data Type Alignment Functions:DTA_BASIC_CountStringToLApp

   PUBLISH XREF:	DTA_BASIC_CountStringToLApp

   PUBLISH NAME:	DTA_BASIC_CountStringToLApp

	ENTRY CLASS	:	Data Type Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DTA_BASIC_CountStringToLApp(unsigned int type_count,
	const DTA_TYPE *type_list, int normalize_flag, int adjust_char_flag,
	const char *separator_list, unsigned int in_spec_count,
	const char *in_spec_string, unsigned int *structure_size,
	unsigned int *align_count, DTA **align_list, char *error_text)
#else
int DTA_BASIC_CountStringToLApp(type_count, type_list, normalize_flag,
	adjust_char_flag, separator_list, in_spec_count, in_spec_string,
	structure_size, align_count, align_list, error_text)
unsigned int     type_count;
const DTA_TYPE  *type_list;
int              normalize_flag;
int              adjust_char_flag;
const char      *separator_list;
unsigned int     in_spec_count;
const char      *in_spec_string;
unsigned int    *structure_size;
unsigned int    *align_count;
DTA            **align_list;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code;
	unsigned int  tmp_align_count = 0;
	DTA          *tmp_align_list  = NULL;
	DTA          *tmp_new_list;
	unsigned int  tmp_structure_size;

	structure_size = (structure_size == NULL) ? &tmp_structure_size :
		structure_size;

	if ((return_code = DTA_BASIC_CountStringToList(type_count, type_list,
		normalize_flag, adjust_char_flag, separator_list, in_spec_count,
		in_spec_string, structure_size, &tmp_align_count, &tmp_align_list,
		error_text)) == DTA_SUCCESS) {
		if ((tmp_new_list = ((DTA *)
			calloc(*align_count + tmp_align_count, sizeof(DTA)))) == NULL){
			STR_AllocMsgList(*align_count + tmp_align_count, sizeof(DTA),
				error_text, "Unable to allocate the alignment list");
			return_code = DTA_MEMORY_FAILURE;
		}
		else {
			memcpy(tmp_new_list, *align_list, *align_count * sizeof(DTA));
			memcpy(tmp_new_list + *align_count, tmp_align_list,
				tmp_align_count * sizeof(DTA));
			if ((return_code = DTA_BASIC_AlignList(type_count, type_list,
				structure_size, *align_count + tmp_align_count, tmp_new_list,
				error_text)) == DTA_SUCCESS) {
				free(*align_list);
				*align_count += tmp_align_count;
				*align_list   = tmp_new_list;
			}
			else
				free(tmp_new_list);
		}
		free(tmp_align_list);
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  DTA_CountStringToLApp

   SYNOPSIS    :  return_code = DTA_CountStringToLApp(normalize_flag,
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

						DTA          **align_list;

						char          *error_text;

   DESCRIPTION :  Transforms a string specification (and associated instance
						count) of the members of a structure into an array of
						structures of type ''DTA''. These structures are then
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
						type ''DTA''. If the function is
						successful, it will allocate memory sufficient to hold
						``align_count`` elements. Each element will describe the
						offset and length requirements for each member of the
						desired structure.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at
						least ''DTA_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DTA_SUCCESS'' if no error occurs.

						(.) One of the non-zero DTA Return Codes if an error
						occurs.

   NOTES       :  This function appends members parsed out of the
						``in_spec_string`` parameter to the list represented by
						``align_count`` and ``align_list``. If you do not want
						this behavior, use the related function
						``DTA_CountStringToList``.

   CAVEATS     :  

   SEE ALSO    :  DTA_CountStringToList
						DTA_BASIC_CountStringToLApp

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2016 Michael L. Brock

   OUTPUT INDEX:	DTA_CountStringToLApp
						Data Type Alignment Functions:DTA_CountStringToLApp
						DTA:Functions:DTA_CountStringToLApp
						DTA:Data Type Alignment Functions:DTA_CountStringToLApp

   PUBLISH XREF:	DTA_CountStringToLApp

   PUBLISH NAME:	DTA_CountStringToLApp

	ENTRY CLASS	:	Data Type Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DTA_CountStringToLApp(int normalize_flag, int adjust_char_flag,
	const char *separator_list, unsigned int in_spec_count,
	const char *in_spec_string, unsigned int *structure_size,
	unsigned int *align_count, DTA **align_list, char *error_text)
#else
int DTA_CountStringToLApp(normalize_flag, adjust_char_flag,
	separator_list, in_spec_count, in_spec_string, structure_size, align_count,
	align_list, error_text)
int            normalize_flag;
int            adjust_char_flag;
const char    *separator_list;
unsigned int   in_spec_count;
const char    *in_spec_string;
unsigned int  *structure_size;
unsigned int  *align_count;
DTA          **align_list;
char          *error_text;
#endif /* #ifndef NARGS */
{
	return(DTA_BASIC_CountStringToLApp(0, NULL, normalize_flag,
		adjust_char_flag, separator_list, in_spec_count, in_spec_string,
		structure_size, align_count, align_list, error_text));
}
/* *********************************************************************** */

