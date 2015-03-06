/* *********************************************************************** */
/* *********************************************************************** */
/*	Data Type Alignment (DTA) Functions Library Source Module					*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Locates a 'DTA' structure within an array by its
								character specifier.

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

#include "dtai.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  DTA_BASIC_FindTypeCharIndex

   SYNOPSIS    :  return_code = DTA_BASIC_FindTypeCharIndex(type_count,
							type_list, type_char, type_index);

						int             return_code;

						unsigned int    type_count;

						const DTA_TYPE *type_list;

						int             type_char;

						unsigned int   *type_index;

   DESCRIPTION :  Attempts to find the type indicated by the ``type_char``
						parameter in the array of primitive types.

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

						(.) ``type_char`` is the character to be matched against
						the ``type_abbreviation`` member of the structure
						''DTA_TYPE''.

						(.) ``type_index`` is a pointer to an ''unsigned long'' into
						which this function will place the index matching
						''DTA_TYPE'' element.

						(-) If ``type_index`` is ''NULL'', however, it will not be
						dereferenced.

   RETURNS     :  Returns from this function are as follow:

						(.) If ``type_char`` is found in the array of primitive
						types, this function returns ''DTA_TRUE''.

						(.) Otherwise, this function returns ''DTA_FALSE''.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  DTA_BASIC_FindTypeCharPtr
						DTA_FindTypeCharIndex

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2015 Michael L. Brock

   OUTPUT INDEX:	DTA_BASIC_FindTypeCharIndex
						Data Type Alignment Functions:DTA_BASIC_FindTypeCharIndex
						DTA:Functions:DTA_BASIC_FindTypeCharIndex
						DTA:Data Type Alignment Functions:DTA_BASIC_FindTypeCharIndex

   PUBLISH XREF:	DTA_BASIC_FindTypeCharIndex

   PUBLISH NAME:	DTA_BASIC_FindTypeCharIndex

	ENTRY CLASS	:	Data Type Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DTA_BASIC_FindTypeCharIndex(unsigned int type_count,
	const DTA_TYPE *type_list, int type_char, unsigned int *type_index)
#else
int DTA_BASIC_FindTypeCharIndex(type_count, type_list, type_char,
	type_index)
unsigned int    type_count;
const DTA_TYPE *type_list;
int             type_char;
unsigned int   *type_index;
#endif /* #ifndef NARGS */
{
	int          found_flag = DTA_FALSE;
	unsigned int count_1;

	DTA_GetTypeInfo(&type_count, &type_list);

	for (count_1 = 0; count_1 < type_count; count_1++) {
		if ((type_char == type_list[count_1].type_abbreviation) ||
			((type_char == 'B') &&
			(type_list[count_1].type_abbreviation == 'b')) ||
			((type_char == 'F') &&
			(type_list[count_1].type_abbreviation == 'f')) ||
			((type_char == 'D') &&
			(type_list[count_1].type_abbreviation == 'd')) ||
			((type_char == 'f') &&
			(type_list[count_1].type_abbreviation == 'F')) ||
			((type_char == 'd') &&
			(type_list[count_1].type_abbreviation == 'D'))) {
			if (type_index != NULL)
				*type_index = count_1;
			found_flag = DTA_TRUE;
			break;
		}
	}

	return(found_flag);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  DTA_BASIC_FindTypeCharPtr

   SYNOPSIS    :  return_ptr = DTA_BASIC_FindTypeCharPtr(type_count,
							type_list, type_char, type_index);

						const DTA_TYPE *return_ptr;

						unsigned int    type_count;

						const DTA_TYPE *type_list;

						int             type_char;

						unsigned int   *type_index;

   DESCRIPTION :  Returns a pointer to the type indicated by the ``type_char``
						parameter in the array of primitive types.

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

						(.) ``type_char`` is the character to be matched against
						the ``type_abbreviation`` member of the structure
						''DTA_TYPE''.

						(.) ``type_index`` is a pointer to an ''unsigned long'' into
						which this function will place the index matching
						''DTA_TYPE'' element.

						(-) If ``type_index`` is ''NULL'', however, it will not be
						dereferenced.

   RETURNS     :  Returns from this function are as follow:

						(.) If ``type_char`` is found in the array of primitive
						types, a pointer to matching element in that array is
						returned.

						(.) Otherwise, this function returns ''NULL''.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  DTA_BASIC_FindTypeCharIndex
						DTA_FindTypeCharPtr

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2015 Michael L. Brock

   OUTPUT INDEX:	DTA_BASIC_FindTypeCharPtr
						Data Type Alignment Functions:DTA_BASIC_FindTypeCharPtr
						DTA:Functions:DTA_BASIC_FindTypeCharPtr
						DTA:Data Type Alignment Functions:DTA_BASIC_FindTypeCharPtr

   PUBLISH XREF:	DTA_BASIC_FindTypeCharPtr

   PUBLISH NAME:	DTA_BASIC_FindTypeCharPtr

	ENTRY CLASS	:	Data Type Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
const DTA_TYPE *DTA_BASIC_FindTypeCharPtr(unsigned int type_count,
	const DTA_TYPE *type_list, int type_char, unsigned int *type_index)
#else
const DTA_TYPE *DTA_BASIC_FindTypeCharPtr(type_count, type_list,
	type_char, type_index)
unsigned int    type_count;
const DTA_TYPE *type_list;
int             type_char;
unsigned int   *type_index;
#endif /* #ifndef NARGS */
{
	const DTA_TYPE *return_ptr = NULL;
	unsigned int          tmp_type_index;

	DTA_GetTypeInfo(&type_count, &type_list);

	if (DTA_BASIC_FindTypeCharIndex(type_count, type_list, type_char,
		&tmp_type_index) == DTA_TRUE) {
		if (type_index != NULL)
			*type_index = tmp_type_index;
		return_ptr = type_list + tmp_type_index;
	}

	return(return_ptr);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  DTA_FindTypeCharIndex

   SYNOPSIS    :  return_code = DTA_FindTypeCharIndex(type_char,
							type_index);

						int           return_code;

						int           type_char;

						unsigned int *type_index;

   DESCRIPTION :  Attempts to find the type indicated by the ``type_char``
						parameter in the array of primitive types.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``type_char`` is the character to be matched against
						the ``type_abbreviation`` member of the structure
						''DTA_TYPE''.

						(.) ``type_index`` is a pointer to an ''unsigned long'' into
						which this function will place the index matching
						''DTA_TYPE'' element.

						(-) If ``type_index`` is ''NULL'', however, it will not be
						dereferenced.

   RETURNS     :  Returns from this function are as follow:

						(.) If ``type_char`` is found in the array of primitive
						types, this function returns ''DTA_TRUE''.

						(.) Otherwise, this function returns ''DTA_FALSE''.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  DTA_FindTypeCharPtr
						DTA_BASIC_FindTypeCharIndex

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2015 Michael L. Brock

   OUTPUT INDEX:	DTA_FindTypeCharIndex
						Data Type Alignment Functions:DTA_FindTypeCharIndex
						DTA:Functions:DTA_FindTypeCharIndex
						DTA:Data Type Alignment Functions:DTA_FindTypeCharIndex

   PUBLISH XREF:	DTA_FindTypeCharIndex

   PUBLISH NAME:	DTA_FindTypeCharIndex

	ENTRY CLASS	:	Data Type Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DTA_FindTypeCharIndex(int type_char, unsigned int *type_index)
#else
int DTA_FindTypeCharIndex(type_char, type_index)
int           type_char;
unsigned int *type_index;
#endif /* #ifndef NARGS */
{
	return(DTA_BASIC_FindTypeCharIndex(0, NULL, type_char, type_index));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  DTA_FindTypeCharPtr

   SYNOPSIS    :  return_ptr = DTA_FindTypeCharPtr(type_char,
							type_index);

						const DTA_TYPE *return_ptr;

						int                   type_char;

						unsigned int         *type_index;

   DESCRIPTION :  Returns a pointer to the type indicated by the ``type_char``
						parameter in the array of primitive types.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``type_char`` is the character to be matched against
						the ``type_abbreviation`` member of the structure
						''DTA_TYPE''.

						(.) ``type_index`` is a pointer to an ''unsigned long'' into
						which this function will place the index matching
						''DTA_TYPE'' element.

						(-) If ``type_index`` is ''NULL'', however, it will not be
						dereferenced.

   RETURNS     :  Returns from this function are as follow:

						(.) If ``type_char`` is found in the array of primitive
						types, a pointer to matching element in that array is
						returned.

						(.) Otherwise, this function returns ''NULL''.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  DTA_FindTypeCharIndex
						DTA_BASIC_FindTypeCharPtr

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2015 Michael L. Brock

   OUTPUT INDEX:	DTA_FindTypeCharPtr
						Data Type Alignment Functions:DTA_FindTypeCharPtr
						DTA:Functions:DTA_FindTypeCharPtr
						DTA:Data Type Alignment Functions:DTA_FindTypeCharPtr

   PUBLISH XREF:	DTA_FindTypeCharPtr

   PUBLISH NAME:	DTA_FindTypeCharPtr

	ENTRY CLASS	:	Data Type Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
const DTA_TYPE *DTA_FindTypeCharPtr(int type_char, unsigned int *type_index)
#else
const DTA_TYPE *DTA_FindTypeCharPtr(type_char, type_index)
int           type_char;
unsigned int *type_index;
#endif /* #ifndef NARGS */
{
	return(DTA_BASIC_FindTypeCharPtr(0, NULL, type_char, type_index));
}
/* *********************************************************************** */

