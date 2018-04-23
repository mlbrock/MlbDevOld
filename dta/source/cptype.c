/* *********************************************************************** */
/* *********************************************************************** */
/*	Data Type Alignment (DTA) Functions Library Source Module					*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Copies an array of 'DTA' structures.

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

#include "dtai.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  DTA_BASIC_CopyTypeList

   SYNOPSIS    :  return_code = DTA_BASIC_CopyTypeList(in_type_count,
							in_type_list, out_type_count, out_type_list, error_text);

						int              return_code;

						unsigned int     in_type_count;

						const DTA_TYPE  *in_type_list;

						unsigned int    *out_type_count;

						DTA_TYPE       **out_type_list;

						char            *error_text;

   DESCRIPTION :  Copies a list of ''DTA_TYPE'' primitive type
						specifications.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_type_count`` is the number of elements in the array
						represented by the ``in_type_list`` parameter.

						(.) ``in_type_list`` is an array of ''DTA_TYPE''
						structures which describe a machine architecture in terms
						of the primitive data types available on that architecture.

						(-) If ``in_type_count`` is ''0'' and ``in_type_list`` is
						''NULL'', the function will use the built-in primitive
						data type list compiled into the module ``dtadata.c``
						under the names ``DTA_TypeCount`` and ``DTA_TypeList``.

						(.) ``out_type_count`` points to an ''unsigned int'' into
						which this function will place the number of elements
						copied into the array to which the ``out_type_list``
						parameter points.

						(.) ``out_type_list`` points to a pointer to
						''DTA_TYPE''. Memory will be allocated by this
						function and the pointer to that memory placed in the
						pointer to which ``out_type_list`` points.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DTA_SUCCESS'' if the list was copied without
						error.

						(.) ''DTA_MEMORY_FAILURE'' if memory could not be
						allocated for the copy.

   CAVEATS     :  

   SEE ALSO    :  DTA_CopyTypeList

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	DTA_BASIC_CopyTypeList
						Data Type Alignment Functions:DTA_BASIC_CopyTypeList
						DTA:Functions:DTA_BASIC_CopyTypeList
						DTA:Data Type Alignment Functions:DTA_BASIC_CopyTypeList

   PUBLISH XREF:	DTA_BASIC_CopyTypeList

   PUBLISH NAME:	DTA_BASIC_CopyTypeList

	ENTRY CLASS	:	Data Type Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DTA_BASIC_CopyTypeList(unsigned int in_type_count,
	const DTA_TYPE *in_type_list, unsigned int *out_type_count,
	DTA_TYPE **out_type_list, char *error_text)
#else
int DTA_BASIC_CopyTypeList(in_type_count, in_type_list, out_type_count,
	out_type_list, error_text)
unsigned int     in_type_count;
const DTA_TYPE  *in_type_list;
unsigned int    *out_type_count;
DTA_TYPE       **out_type_list;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = DTA_SUCCESS;

	*out_type_count = 0;
	*out_type_list  = NULL;

	DTA_GetTypeInfo(&in_type_count, &in_type_list);

	if ((*out_type_list = ((DTA_TYPE *) memdup(in_type_list, in_type_count *
		sizeof(*in_type_list)))) == NULL) {
		STR_AllocMsgList(in_type_count, sizeof(*in_type_list), error_text,
			"Unable to allocate memory for the primitive type array");
		return_code = DTA_MEMORY_FAILURE;
	}
	else
		*out_type_count = in_type_count;

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  DTA_CopyTypeList

   SYNOPSIS    :  return_code = DTA_CopyTypeList(out_type_count,
							out_type_list, error_text);

						int              return_code;

						unsigned int    *out_type_count;

						DTA_TYPE       **out_type_list;

						char            *error_text;

   DESCRIPTION :  Copies a list of ''DTA_TYPE'' primitive type
						specifications.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``out_type_count`` points to an ''unsigned int'' into
						which this function will place the number of elements
						copied into the array to which the ``out_type_list``
						parameter points.

						(.) ``out_type_list`` points to a pointer to
						''DTA_TYPE''. Memory will be allocated by this
						function and the pointer to that memory placed in the
						pointer to which ``out_type_list`` points.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DTA_SUCCESS'' if the list was copied without
						error.

						(.) ''DTA_MEMORY_FAILURE'' if memory could not be
						allocated for the copy.

   CAVEATS     :  

   SEE ALSO    :  DTA_BASIC_CopyTypeList

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	DTA_CopyTypeList
						Data Type Alignment Functions:DTA_CopyTypeList
						DTA:Functions:DTA_CopyTypeList
						DTA:Data Type Alignment Functions:DTA_CopyTypeList

   PUBLISH XREF:	DTA_CopyTypeList

   PUBLISH NAME:	DTA_CopyTypeList

	ENTRY CLASS	:	Data Type Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DTA_CopyTypeList(unsigned int *out_type_count, DTA_TYPE **out_type_list,
	char *error_text)
#else
int DTA_CopyTypeList(out_type_count, out_type_list, error_text)
unsigned int    *out_type_count;
DTA_TYPE       **out_type_list;
char            *error_text;
#endif /* #ifndef NARGS */
{
	return(DTA_BASIC_CopyTypeList(0, NULL, out_type_count, out_type_list,
		error_text));
}
/* *********************************************************************** */

