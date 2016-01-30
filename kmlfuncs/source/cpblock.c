/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Copies 'KML_BLOCK' structures.

	Revision History	:	1998-03-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2016.
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

	NAME			:	KML_COPY_Block

	SYNOPSIS		:	return_code = KML_COPY_Block(in_ptr, out_ptr, error_text);

						int              return_code;

						const KML_BLOCK *ptr;

						KML_BLOCK       *out_ptr;

						char            *error_text;

	DESCRIPTION	:	Copies a ''KML_BLOCK'' structure.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_ptr`` is a pointer to the ''KML_BLOCK''
						structure which is to be copied by this function.

						(.) ``out_ptr`` is a pointer to the ''KML_BLOCK''
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

	SEE ALSO		:	KML_COPY_BlockList
						KML_FREE_Block
						KML_INIT_Block
						KML_SCMP_Block

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2016 Michael L. Brock

	OUTPUT INDEX:	KML_COPY_Block
						Copy Functions:KML_COPY_Block
						KML_BLOCK Functions:KML_COPY_Block

	PUBLISH XREF:	KML_COPY_Block

	PUBLISH NAME:	KML_COPY_Block

	ENTRY CLASS	:	Copy Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int KML_COPY_Block(const KML_BLOCK *in_ptr, KML_BLOCK *out_ptr,
	char *error_text)
#else
int KML_COPY_Block(in_ptr, out_ptr, error_text)
const KML_BLOCK *in_ptr;
KML_BLOCK       *out_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = KML_MEMORY_FAILURE;

	KML_INIT_Block(out_ptr);

	if ((out_ptr->start_ptr =
		strdup(STRFUNCS_NULL_TO_STR(in_ptr->start_ptr))) == NULL)
		STR_AllocMsgItem(strlen(STRFUNCS_NULL_TO_STR(in_ptr->start_ptr)) + 1,
			error_text, "Unable to copy the 'KML_BLOCK' member 'start_ptr'");
	else if ((out_ptr->end_ptr =
		strdup(STRFUNCS_NULL_TO_STR(in_ptr->end_ptr))) == NULL)
		STR_AllocMsgItem(strlen(STRFUNCS_NULL_TO_STR(in_ptr->end_ptr)) + 1,
			error_text, "Unable to copy the 'KML_BLOCK' member 'end_ptr'");
	else {
		out_ptr->start_length = strlen(out_ptr->start_ptr);
		out_ptr->end_length   = strlen(out_ptr->end_ptr);
		return_code           = KML_SUCCESS;
	}

	if (return_code != KML_SUCCESS)
		KML_FREE_Block(out_ptr);

	return(return_code);
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	KML_COPY_BlockList

	SYNOPSIS		:	return_code = KML_COPY_BlockList(in_count, in_list,
							out_count, out_list, error_text);

						int               return_code;

						unsigned int      count;

						const KML_BLOCK  *list;

						unsigned int     *out_count;

						KML_BLOCK       **out_list;

						char             *error_text;

	DESCRIPTION	:	Copies an array of ''KML_BLOCK'' structures.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_count`` is the number of elements in the array
						``in_list``.

						(.) ``in_list`` is the array of ''KML_BLOCK'' structures
						which is to be copied by this function.

						(.) ``out_count`` is a pointer to an ''unsigned int'' into
						which this function will place the number of elements
						copied.

						(.) ``out_list`` is a pointer to the array of
						''KML_BLOCK'' structures which will be allocated and
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

	SEE ALSO		:	KML_COPY_Block
						KML_FREE_BlockList
						KML_INIT_BlockList
						KML_SORT_BlockList

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2016 Michael L. Brock

	OUTPUT INDEX:	KML_COPY_BlockList
						Copy Functions:KML_COPY_BlockList
						KML_BLOCK Functions:KML_COPY_BlockList

	PUBLISH XREF:	KML_COPY_BlockList

	PUBLISH NAME:	KML_COPY_BlockList

	ENTRY CLASS	:	Copy Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int KML_COPY_BlockList(unsigned int in_count, const KML_BLOCK *in_list,
	unsigned int *out_count, KML_BLOCK **out_list, char *error_text)
#else
int KML_COPY_BlockList(in_count, in_list, out_count, out_list, error_text)
unsigned int      in_count;
const KML_BLOCK  *in_list;
unsigned int     *out_count;
KML_BLOCK       **out_list;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = KML_SUCCESS;
	unsigned int count_1;

	*out_count = 0;
	*out_list  = NULL;

	if (in_count) {
		if ((*out_list = ((KML_BLOCK *) calloc(in_count,
			sizeof(**out_list)))) == NULL) {
			STR_AllocMsgList(in_count, sizeof(**out_list), error_text,
				"Unable to copy a list of 'KML_BLOCK' structures");
			return_code = KML_MEMORY_FAILURE;
		}
		else {
			*out_count = in_count;
			KML_INIT_BlockList(*out_count, *out_list);
			for (count_1 = 0; count_1 < in_count; count_1++) {
				if ((return_code = KML_COPY_Block(in_list + count_1,
					*out_list + count_1, error_text)) != KML_SUCCESS) {
					KML_FREE_BlockList(out_count, out_list);
					break;
				}
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

