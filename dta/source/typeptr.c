/* *********************************************************************** */
/* *********************************************************************** */
/*	Data Type Alignment (DTA) Functions Library Source Module					*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets the pointer to the 'DTA_TYPE' structure
								associated with a specified type.

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

#include "dtai.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  DTA_BASIC_GetTypePtr

   SYNOPSIS    :  return_ptr = DTA_BASIC_GetTypePtr(type_count,
							type_list, type_index);

						const DTA_TYPE *return_ptr;

						unsigned int    type_count;

						const DTA_TYPE *type_list;

						unsigned int    type_index;

   DESCRIPTION :  Returns a pointer to ''DTA_TYPE''

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

						(.) ``type_index`` is the index into the array of primitive
						types for which a pointer is desired. It must be less than
						the total number of primitive types.

   RETURNS     :  Returns from this function are as follow:

						(.) If ``type_index`` is valid, a pointer to element
						indicated by ``type_index`` is returned.

						(.) Otherwise, this function returns ''NULL''.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  DTA_GetTypePtr

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2016 Michael L. Brock

   OUTPUT INDEX:	DTA_BASIC_GetTypePtr
						Data Type Alignment Functions:DTA_BASIC_GetTypePtr
						DTA:Functions:DTA_BASIC_GetTypePtr
						DTA:Data Type Alignment Functions:DTA_BASIC_GetTypePtr

   PUBLISH XREF:	DTA_BASIC_GetTypePtr

   PUBLISH NAME:	DTA_BASIC_GetTypePtr

	ENTRY CLASS	:	Data Type Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
const DTA_TYPE *DTA_BASIC_GetTypePtr(unsigned int type_count,
	const DTA_TYPE *type_list, unsigned int type_index)
#else
const DTA_TYPE *DTA_BASIC_GetTypePtr(type_count, type_list,
	type_index)
unsigned int    type_count;
const DTA_TYPE *type_list;
unsigned int    type_index;
#endif /* #ifndef NARGS */
{
	DTA_GetTypeInfo(&type_count, &type_list);

	return((type_index < type_count) ? (type_list + type_index) : NULL);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  DTA_GetTypePtr

   SYNOPSIS    :  return_ptr = DTA_GetTypePtr(type_index);

						const DTA_TYPE *return_ptr;

						unsigned int          type_index;

   DESCRIPTION :  Returns a pointer to ''DTA_TYPE''

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

   SEE ALSO    :  DTA_BASIC_GetTypePtr

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2016 Michael L. Brock

   OUTPUT INDEX:	DTA_GetTypePtr
						Data Type Alignment Functions:DTA_GetTypePtr
						DTA:Functions:DTA_GetTypePtr
						DTA:Data Type Alignment Functions:DTA_GetTypePtr

   PUBLISH XREF:	DTA_GetTypePtr

   PUBLISH NAME:	DTA_GetTypePtr

	ENTRY CLASS	:	Data Type Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
const DTA_TYPE *DTA_GetTypePtr(unsigned int type_index)
#else
const DTA_TYPE *DTA_GetTypePtr(type_index)
unsigned int type_index;
#endif /* #ifndef NARGS */
{
	return(DTA_BASIC_GetTypePtr(0, NULL, type_index));
}
/* *********************************************************************** */

