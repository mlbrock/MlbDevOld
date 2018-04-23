/* *********************************************************************** */
/* *********************************************************************** */
/*	Data Type Alignment (DTA) Functions Library Source Module					*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Converts an array of 'DTA' structures to its
								equivalent string representation.

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

#include <stdio.h>
#include <string.h>

#include "dtai.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  DTA_BASIC_ListToString

   SYNOPSIS    :  return_code = DTA_BASIC_ListToString(type_count,
							type_list, align_count, align_list, separator_char,
							spec_string, error_text);

						int             return_code;

						unsigned int    type_count;

						const DTA_TYPE *type_list;

						unsigned int    align_count;

						const DTA      *align_list;

						const char     *separator_char;

						char           *spec_string;

						char           *error_text;

   DESCRIPTION :  Converts an array of ''DTA'' structures to an
						equivalent string representation.

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

						(.) ``align_count`` is the number of elements in the array
						``align_list``.

						(.) ``align_list`` is the array of ''DTA'' structures
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
						least ''DTA_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DTA_SUCCESS'' if no error occurs.

						(.) One of the non-zero DTA Return Codes if an error
						occurs.

   NOTES       :  The string ``spec_string`` should be allocated with
						sufficient memory to store the string representation. The
						application programmer to determine the amount of memory
						required by calling the function
						``DTA_CalcListToStringLen`` to determine the memory
						needed and then ``malloc``ing that memory. Alternatively,
						the function related function
						``DTA_BASIC_ListToStringAlloc``, which allocates the
						proper amount of memory before performing the conversion
						could be used.

   CAVEATS     :  

   SEE ALSO    :  DTA_BASIC_ListToStringAlloc
						DTA_ListToString

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	DTA_BASIC_ListToString
						Data Type Alignment Functions:DTA_BASIC_ListToString
						DTA:Functions:DTA_BASIC_ListToString
						DTA:Data Type Alignment Functions:DTA_BASIC_ListToString

   PUBLISH XREF:	DTA_BASIC_ListToString

   PUBLISH NAME:	DTA_BASIC_ListToString

	ENTRY CLASS	:	Data Type Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DTA_BASIC_ListToString(unsigned int type_count, const DTA_TYPE *type_list,
	unsigned int align_count, const DTA *align_list, const char *separator_char,
	char *spec_string, char *error_text)
#else
int DTA_BASIC_ListToString(type_count, type_list, align_count,
	align_list, separator_char, spec_string, error_text)
unsigned int    type_count;
const DTA_TYPE *type_list;
unsigned int    align_count;
const DTA      *align_list;
const char     *separator_char;
char           *spec_string;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code = DTA_SUCCESS;
	unsigned int  count_1;
	char         *spec_ptr;

	*spec_string    = '\0';
	spec_ptr        = spec_string;

	separator_char  = (separator_char != NULL) ? separator_char : ",";

	DTA_GetTypeInfo(&type_count, &type_list);

	for (count_1 = 0; count_1 < align_count; count_1++) {
		if (align_list[count_1].type >= type_count) {
			sprintf(error_text, "%s (%u) %s 0 through %u, inclusive.",
				"Invalid data-type number", align_list[count_1].type,
				"should be in the range", type_count - 1);
			spec_ptr    = spec_string;
			return_code = DTA_FAILURE;
			break;
		}
		*spec_ptr++ = type_list[align_list[count_1].type].type_abbreviation;
		if (align_list[count_1].array_length > 1) {
			sprintf(spec_ptr, "[%u]", align_list[count_1].array_length);
			spec_ptr += strlen(spec_ptr);
		}
		if (count_1 < (align_count - 1))
			*spec_ptr++ = *separator_char;
	}

	*spec_ptr = '\0';

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  DTA_ListToString

   SYNOPSIS    :  return_code = DTA_ListToString(align_count,
							align_list, separator_char, spec_string, error_text);

						int              return_code;

						unsigned int     align_count;

						const DTA       *align_list;

						const char      *separator_char;

						char            *spec_string;

						char            *error_text;

   DESCRIPTION :  Converts an array of ''DTA'' structures to an
						equivalent string representation.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``align_count`` is the number of elements in the array
						``align_list``.

						(.) ``align_list`` is the array of ''DTA'' structures
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
						least ''DTA_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DTA_SUCCESS'' if no error occurs.

						(.) One of the non-zero DTA Return Codes if an error
						occurs.

   NOTES       :  The string ``spec_string`` should be allocated with
						sufficient memory to store the string representation. The
						application programmer to determine the amount of memory
						required by calling the function
						``DTA_CalcListToStringLen`` to determine the memory
						needed and then ``malloc``ing that memory. Alternatively,
						the function related function
						``DTA_ListToStringAlloc``, which allocates the
						proper amount of memory before performing the conversion
						could be used.

   CAVEATS     :  

   SEE ALSO    :  DTA_ListToStringAlloc
						DTA_BASIC_ListToString

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	DTA_ListToString
						Data Type Alignment Functions:DTA_ListToString
						DTA:Functions:DTA_ListToString
						DTA:Data Type Alignment Functions:DTA_ListToString

   PUBLISH XREF:	DTA_ListToString

   PUBLISH NAME:	DTA_ListToString

	ENTRY CLASS	:	Data Type Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DTA_ListToString(unsigned int align_count, const DTA *align_list,
	const char *separator_char, char *spec_string, char *error_text)
#else
int DTA_ListToString(align_count, align_list, separator_char,
	spec_string, error_text)
unsigned int     align_count;
const DTA       *align_list;
const char      *separator_char;
char            *spec_string;
char            *error_text;
#endif /* #ifndef NARGS */
{
	return(DTA_BASIC_ListToString(0, NULL, align_count, align_list,
		separator_char, spec_string, error_text));
}
/* *********************************************************************** */

