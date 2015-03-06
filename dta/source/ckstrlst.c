/* *********************************************************************** */
/* *********************************************************************** */
/*	Data Type Alignment (DTA) Functions Library Source Module					*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Checks an array of DTA specifier strings.

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

   NAME        :  DTA_BASIC_CheckStringList

   SYNOPSIS    :  return_code = DTA_BASIC_CheckStringList(type_count,
							type_list, separator_list, spec_count, spec_list,
							error_text);

						int              return_code;

						unsigned int     type_count;

						const DTA_TYPE  *type_list;

						const char      *separator_list;

						unsigned int     spec_count;

						char           **spec_list;

						char            *error_text;

   DESCRIPTION :	Checks to ensure that an array of pointers to strings
						are valid specifications of the primitive type members of
						a structure.

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
						least ''DTA_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DTA_SUCCESS'' if no error occurs.

						(.) One of the non-zero DTA return codes if an error
						occurs.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  DTA_CheckStringList
						DTA_BASIC_CheckString
						DTA_BASIC_AlignStringList

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2015 Michael L. Brock

   OUTPUT INDEX:	DTA_BASIC_CheckStringList
						Data Type Alignment Functions:DTA_BASIC_CheckStringList
						DTA:Functions:DTA_BASIC_CheckStringList
						DTA:Data Type Alignment Functions:DTA_BASIC_CheckStringList

   PUBLISH XREF:	DTA_BASIC_CheckStringList

   PUBLISH NAME:	DTA_BASIC_CheckStringList

	ENTRY CLASS	:	Data Type Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DTA_BASIC_CheckStringList(unsigned int type_count,
	const DTA_TYPE *type_list, const char *separator_list,
	unsigned int spec_count, char **spec_list, char *error_text)
#else
int DTA_BASIC_CheckStringList(type_count, type_list, separator_list,
	spec_count, spec_list, error_text)
unsigned int     type_count;
const DTA_TYPE  *type_list;
const char      *separator_list;
unsigned int     spec_count;
char           **spec_list;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code;
	unsigned int *count_list;
	unsigned int *index_list;
	unsigned int *size_list;
	unsigned int  align_count;
	DTA          *align_list;

	if ((return_code = DTA_BASIC_AlignStringList(type_count, type_list,
		DTA_FALSE, DTA_FALSE, separator_list, spec_count, spec_list,
		&count_list, &index_list, &size_list, NULL, &align_count, &align_list,
		error_text)) == DTA_SUCCESS) {
		if (count_list != NULL)
			free(count_list);
		if (index_list != NULL)
			free(index_list);
		if (size_list != NULL)
			free(size_list);
		if (align_list != NULL)
			free(align_list);
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  DTA_CheckStringList

   SYNOPSIS    :  return_code = DTA_CheckStringList(separator_list,
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
						least ''DTA_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DTA_SUCCESS'' if no error occurs.

						(.) One of the non-zero DTA return codes if an error
						occurs.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  DTA_BASIC_CheckStringList
						DTA_CheckString
						DTA_AlignStringList

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2015 Michael L. Brock

   OUTPUT INDEX:	DTA_CheckStringList
						Data Type Alignment Functions:DTA_CheckStringList
						DTA:Functions:DTA_CheckStringList
						DTA:Data Type Alignment Functions:DTA_CheckStringList

   PUBLISH XREF:	DTA_CheckStringList

   PUBLISH NAME:	DTA_CheckStringList

	ENTRY CLASS	:	Data Type Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DTA_CheckStringList(const char *separator_list, unsigned int spec_count,
	char **spec_list, char *error_text)
#else
int DTA_CheckStringList(separator_list, spec_count, spec_list,
	error_text)
const char    *separator_list;
unsigned int   spec_count;
char         **spec_list;
char          *error_text;
#endif /* #ifndef NARGS */
{
	return(DTA_BASIC_CheckStringList(0, NULL, separator_list,
		spec_count, spec_list, error_text));
}
/* *********************************************************************** */

