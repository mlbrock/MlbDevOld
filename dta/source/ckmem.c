/* *********************************************************************** */
/* *********************************************************************** */
/*	Data Type Alignment (DTA) Functions Library Source Module					*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Checks a single member DTA specifier string.

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

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dtai.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  DTA_BASIC_CheckMember

   SYNOPSIS    :  return_code = DTA_BASIC_CheckMember(type_count,
							type_list, spec_string, align_ptr, error_text);

						int             return_code;

						unsigned int    type_count;

						const DTA_TYPE *type_list;

						char           *spec_string;

						DTA            *align_ptr;

						char           *error_text;

   DESCRIPTION :  Determines whether a string member definition is correct.

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
						''DTA''. If the function is successful, it
						will update the ``type``, ``length``, and ``array_length``
						members of the structure to which ``align_ptr`` points.

						(-) Note, however, that if ``align_ptr`` is passed as a
						''NULL'' pointer, it will not be de-referenced.

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

   SEE ALSO    :  DTA_BASIC_AlignString
						DTA_CheckMember

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2015 Michael L. Brock

	OUTPUT INDEX:	DTA_BASIC_CheckMember
						Data Type Alignment Functions:DTA_BASIC_CheckMember
						DTA:Functions:DTA_BASIC_CheckMember
						DTA:Data Type Alignment Functions:DTA_BASIC_CheckMember

   PUBLISH XREF:	DTA_BASIC_CheckMember

   PUBLISH NAME:	DTA_BASIC_CheckMember

	ENTRY CLASS	:	Data Type Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DTA_BASIC_CheckMember(unsigned int type_count, const DTA_TYPE *type_list,
	const char *spec_string, DTA *align_ptr, char *error_text)
#else
int DTA_BASIC_CheckMember(type_count, type_list, spec_string, align_ptr,
	error_text)
unsigned int    type_count;
const DTA_TYPE *type_list;
const char     *spec_string;
DTA            *align_ptr;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = DTA_SUCCESS;
	DTA          align_data;
	unsigned int count_1;
	int          qual_length;
	long         array_length;

	DTA_GetTypeInfo(&type_count, &type_list);

	if ((spec_string == NULL) || (!(*spec_string))) {
		strcpy(error_text, "Empty member specification encountered.");
		return_code = DTA_BAD_ARGS_FAILURE;
	}
	else {
		DTA_InitAlign(&align_data);
		if (DTA_BASIC_FindTypeCharIndex(type_count, type_list,
			*spec_string, &align_data.type) != DTA_TRUE) {
			sprintf(error_text, "%s ('%-.100s') --- should be one of '",
				"Unknown type specifier encountered", spec_string);
			for (count_1 = 0; count_1 < type_count; count_1++)
				strcat(chrcat(error_text, type_list[count_1].type_abbreviation),
					(count_1 == (type_count - 1)) ? "'." :
					(count_1 == (type_count - 2)) ? "', or '" : "', '");
			return_code = DTA_FAILURE;
		}
		else {
			if ((qual_length = strlen(spec_string)) == 1)
				align_data.array_length = 1;
			else if ((qual_length < 4) || (spec_string[1] != '[') ||
				(spec_string[qual_length - 1] != ']') ||
				((array_length = atol(spec_string + 2)) < 1L) ||
				(array_length > ((long) INT_MAX))) {
				sprintf(error_text,
					"Invalid array specification encountered ('%-.100s').",
					spec_string);
				return_code = DTA_FAILURE;
			}
			else
				align_data.array_length = ((unsigned int) array_length);
			if ((return_code == DTA_SUCCESS) && (align_ptr != NULL)) {
				align_data.length = align_data.array_length *
					type_list[align_data.type].type_length;
				*align_ptr        = align_data;
			}
		}
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  DTA_CheckMember

   SYNOPSIS    :  return_code = DTA_CheckMember(spec_string, align_ptr,
							error_text);

						int        return_code;

						char      *spec_string;

						DTA       *align_ptr;

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
						''DTA''. If the function is successful, it
						will update the ``type``, ``length``, and ``array_length``
						members of the structure to which ``align_ptr`` points.

						(-) Note, however, that if ``align_ptr`` is passed as a
						''NULL'' pointer, it will not be de-referenced.

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

   SEE ALSO    :  DTA_AlignString
						DTA_BASIC_CheckMember

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2015 Michael L. Brock

	OUTPUT INDEX:	DTA_CheckMember
						Data Type Alignment Functions:DTA_CheckMember
						DTA:Functions:DTA_CheckMember
						DTA:Data Type Alignment Functions:DTA_CheckMember

   PUBLISH XREF:	DTA_CheckMember

   PUBLISH NAME:	DTA_CheckMember

	ENTRY CLASS	:	Data Type Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DTA_CheckMember(const char *spec_string, DTA *align_ptr, char *error_text)
#else
int DTA_CheckMember(spec_string, align_ptr, error_text)
const char *spec_string;
DTA        *align_ptr;
char       *error_text;
#endif /* #ifndef NARGS */
{
	return(DTA_BASIC_CheckMember(0, NULL, spec_string, align_ptr,
		error_text));
}
/* *********************************************************************** */

