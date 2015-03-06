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
								equivalent string representation, with memory
								allocated for said string.

	Revision History	:	1992-02-23 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2015.
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

   NAME        :  DTA_BASIC_ListToStringAlloc

   SYNOPSIS    :  return_code = DTA_BASIC_ListToStringAlloc(type_count,
							type_list, align_count, align_list, separator_char,
							spec_string, error_text);

						int              return_code;

						unsigned int     type_count;

						const DTA_TYPE  *type_list;

						unsigned int     align_count;

						const DTA       *align_list;

						const char      *separator_char;

						char           **spec_string;

						char            *error_text;

   DESCRIPTION :  Converts an array of ''DTA'' structures to an
						equivalent string representation, for which this function
						allocates memory.

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

						(.) ``spec_string`` is a pointer to a pointer to ''char''
						which will be set to the memory allocated to store the
						string representation of ``align_list``.

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

   SEE ALSO    :  DTA_BASIC_ListToString
						DTA_CalcListToStringLen
						DTA_ListToStringAlloc

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2015 Michael L. Brock

   OUTPUT INDEX:	DTA_BASIC_ListToStringAlloc
						Data Type Alignment Functions:DTA_BASIC_ListToStringAlloc
						DTA:Functions:DTA_BASIC_ListToStringAlloc
						DTA:Data Type Alignment Functions:DTA_BASIC_ListToStringAlloc

   PUBLISH XREF:	DTA_BASIC_ListToStringAlloc

   PUBLISH NAME:	DTA_BASIC_ListToStringAlloc

	ENTRY CLASS	:	Data Type Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DTA_BASIC_ListToStringAlloc(unsigned int type_count,
	const DTA_TYPE *type_list, unsigned int align_count, const DTA *align_list,
	const char *separator_char, char **spec_string, char *error_text)
#else
int DTA_BASIC_ListToStringAlloc(type_count, type_list, align_count,
	align_list, separator_char, spec_string, error_text)
unsigned int     type_count;
const DTA_TYPE  *type_list;
unsigned int     align_count;
const DTA       *align_list;
const char      *separator_char;
char           **spec_string;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = DTA_SUCCESS;
	unsigned int string_length;

	*spec_string = NULL;

	if (align_count) {
		string_length = DTA_CalcListToStringLen(align_count, align_list);
		if ((*spec_string = ((char *) calloc(string_length, sizeof(char)))) ==
			NULL) {
			STR_AllocMsgItem(string_length, error_text,
				"Unable to allocate the alignment specification string");
			return_code = DTA_MEMORY_FAILURE;
		}
		else if ((return_code = DTA_BASIC_ListToString(type_count,
			type_list, align_count, align_list, separator_char, *spec_string,
			error_text)) != DTA_SUCCESS) {
			free(*spec_string);
			*spec_string = NULL;
		}
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  DTA_ListToStringAlloc

   SYNOPSIS    :  return_code = DTA_ListToStringAlloc(align_count,
							align_list, separator_char, spec_string, error_text);

						int               return_code;

						unsigned int      align_count;

						const DTA        *align_list;

						const char       *separator_char;

						char            **spec_string;

						char             *error_text;

   DESCRIPTION :  Converts an array of ''DTA'' structures to an
						equivalent string representation, for which this function
						allocates memory.

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

						(.) ``spec_string`` is a pointer to a pointer to ''char''
						which will be set to the memory allocated to store the
						string representation of ``align_list``.

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

   SEE ALSO    :  DTA_ListToString
						DTA_CalcListToStringLen
						DTA_BASIC_ListToStringAlloc

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2015 Michael L. Brock

   OUTPUT INDEX:	DTA_ListToStringAlloc
						Data Type Alignment Functions:DTA_ListToStringAlloc
						DTA:Functions:DTA_ListToStringAlloc
						DTA:Data Type Alignment Functions:DTA_ListToStringAlloc

   PUBLISH XREF:	DTA_ListToStringAlloc

   PUBLISH NAME:	DTA_ListToStringAlloc

	ENTRY CLASS	:	Data Type Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DTA_ListToStringAlloc(unsigned int align_count, const DTA *align_list,
	const char *separator_char, char **spec_string, char *error_text)
#else
int DTA_ListToStringAlloc(align_count, align_list, separator_char,
	spec_string, error_text)
unsigned int      align_count;
const DTA        *align_list;
const char       *separator_char;
char            **spec_string;
char             *error_text;
#endif /* #ifndef NARGS */
{
	return(DTA_BASIC_ListToStringAlloc(0, NULL, align_count, align_list,
		separator_char, spec_string, error_text));
}
/* *********************************************************************** */

