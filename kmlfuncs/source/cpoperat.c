/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Copies 'KML_OPERATOR' structures.

	Revision History	:	1998-03-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <stdlib.h>
#include <string.h>

#include "kmlfunci.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	KML_COPY_Operator

	SYNOPSIS		:	return_code = KML_COPY_Operator(in_ptr, out_ptr, error_text);

						int                 return_code;

						const KML_OPERATOR *ptr;

						KML_OPERATOR       *out_ptr;

						char               *error_text;

	DESCRIPTION	:	Copies a ''KML_OPERATOR'' structure.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_ptr`` is a pointer to the ''KML_OPERATOR''
						structure which is to be copied by this function.

						(.) ``out_ptr`` is a pointer to the ''KML_OPERATOR''
						structure into which the copy is to be performed.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''KMLFUNCS_MAX_ERROR_TEXT'' characters in length.

	RETURNS     :	Returns from this function are as follow:

						(.) ''KMLFUNCS_SUCCESS'' if the function completes without
						error. ''KMLFUNCS_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero KMLFUNCS return codes
						indicative of error.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_COPY_OperatorList
						KML_FREE_Operator
						KML_INIT_Operator
						KML_SCMP_Operator

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2018 Michael L. Brock

	OUTPUT INDEX:	KML_COPY_Operator
						Copy Functions:KML_COPY_Operator
						KML_OPERATOR Functions:KML_COPY_Operator

	PUBLISH XREF:	KML_COPY_Operator

	PUBLISH NAME:	KML_COPY_Operator

	ENTRY CLASS	:	Copy Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int KML_COPY_Operator(const KML_OPERATOR *in_ptr, KML_OPERATOR *out_ptr,
	char *error_text)
#else
int KML_COPY_Operator(in_ptr, out_ptr, error_text)
const KML_OPERATOR *in_ptr;
KML_OPERATOR       *out_ptr;
char               *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = KML_MEMORY_FAILURE;

	KML_INIT_Operator(out_ptr);

	if ((out_ptr->ptr =
		strdup(STRFUNCS_NULL_TO_STR(in_ptr->ptr))) == NULL)
		STR_AllocMsgItem(strlen(STRFUNCS_NULL_TO_STR(in_ptr->ptr)) + 1,
			error_text,
			"Unable to copy the 'KML_OPERATOR' member 'ptr'");
	else {
		out_ptr->length  = strlen(out_ptr->ptr);
		out_ptr->op_type = in_ptr->op_type;
		return_code      = KML_SUCCESS;
	}

	if (return_code != KML_SUCCESS)
		KML_FREE_Operator(out_ptr);

	return(return_code);
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	KML_COPY_OperatorList

	SYNOPSIS		:	return_code = KML_COPY_OperatorList(in_count, in_list,
							out_count, out_list, error_text);

						int                  return_code;

						unsigned int         count;

						const KML_OPERATOR  *list;

						unsigned int        *out_count;

						KML_OPERATOR       **out_list;

						char                *error_text;

	DESCRIPTION	:	Copies an array of ''KML_OPERATOR'' structures.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_count`` is the number of elements in the array
						``in_list``.

						(.) ``in_list`` is the array of ''KML_OPERATOR'' structures
						which is to be copied by this function.

						(.) ``out_count`` is a pointer to an ''unsigned int'' into
						which this function will place the number of elements
						copied.

						(.) ``out_list`` is a pointer to the array of
						''KML_OPERATOR'' structures which will be allocated and
						copied by this function.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''KMLFUNCS_MAX_ERROR_TEXT'' characters in length.

	RETURNS     :	Returns from this function are as follow:

						(.) ''KMLFUNCS_SUCCESS'' if the function completes without
						error. ''KMLFUNCS_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero KMLFUNCS return codes
						indicative of error.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_COPY_Operator
						KML_FREE_OperatorList
						KML_INIT_OperatorList
						KML_SORT_OperatorList

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2018 Michael L. Brock

	OUTPUT INDEX:	KML_COPY_OperatorList
						Copy Functions:KML_COPY_OperatorList
						KML_OPERATOR Functions:KML_COPY_OperatorList

	PUBLISH XREF:	KML_COPY_OperatorList

	PUBLISH NAME:	KML_COPY_OperatorList

	ENTRY CLASS	:	Copy Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int KML_COPY_OperatorList(unsigned int in_count, const KML_OPERATOR *in_list,
	unsigned int *out_count, KML_OPERATOR **out_list, char *error_text)
#else
int KML_COPY_OperatorList(in_count, in_list, out_count, out_list, error_text)
unsigned int         in_count;
const KML_OPERATOR  *in_list;
unsigned int        *out_count;
KML_OPERATOR       **out_list;
char                *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = KML_SUCCESS;
	unsigned int count_1;

	*out_count = 0;
	*out_list  = NULL;

	if (in_count) {
		if ((*out_list = ((KML_OPERATOR *) calloc(in_count,
			sizeof(**out_list)))) == NULL) {
			STR_AllocMsgList(in_count, sizeof(**out_list), error_text,
				"Unable to copy a list of 'KML_OPERATOR' structures");
			return_code = KML_MEMORY_FAILURE;
		}
		else {
			*out_count = in_count;
			KML_INIT_OperatorList(*out_count, *out_list);
			for (count_1 = 0; count_1 < in_count; count_1++) {
				if ((return_code = KML_COPY_Operator(in_list + count_1,
					*out_list + count_1, error_text)) != KML_SUCCESS) {
					KML_FREE_OperatorList(out_count, out_list);
					break;
				}
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

