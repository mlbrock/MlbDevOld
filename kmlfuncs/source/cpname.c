/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Copies 'KML_NAME' structures.

	Revision History	:	1998-03-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2015.
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

	NAME			:	KML_COPY_Name

	SYNOPSIS		:	return_code = KML_COPY_Name(in_ptr, out_ptr, error_text);

						int             return_code;

						const KML_NAME *ptr;

						KML_NAME       *out_ptr;

						char           *error_text;

	DESCRIPTION	:	Copies a ''KML_NAME'' structure.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_ptr`` is a pointer to the ''KML_NAME''
						structure which is to be copied by this function.

						(.) ``out_ptr`` is a pointer to the ''KML_NAME''
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

	SEE ALSO		:	KML_COPY_NameList
						KML_FREE_Name
						KML_INIT_Name
						KML_SCMP_Name

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2015 Michael L. Brock

	OUTPUT INDEX:	KML_COPY_Name
						Copy Functions:KML_COPY_Name
						KML_NAME Functions:KML_COPY_Name

	PUBLISH XREF:	KML_COPY_Name

	PUBLISH NAME:	KML_COPY_Name

	ENTRY CLASS	:	Copy Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int KML_COPY_Name(const KML_NAME *in_ptr, KML_NAME *out_ptr, char *error_text)
#else
int KML_COPY_Name(in_ptr, out_ptr, error_text)
const KML_NAME *in_ptr;
KML_NAME       *out_ptr;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = KML_MEMORY_FAILURE;

	KML_INIT_Name(out_ptr);

	if ((out_ptr->first_char =
		strdup(STRFUNCS_NULL_TO_STR(in_ptr->first_char))) == NULL)
		STR_AllocMsgItem(strlen(STRFUNCS_NULL_TO_STR(in_ptr->first_char)) + 1,
			error_text, "Unable to copy the 'KML_NAME' member 'first_char'");
	else if ((out_ptr->other_chars =
		strdup(STRFUNCS_NULL_TO_STR(in_ptr->other_chars))) == NULL)
		STR_AllocMsgItem(strlen(STRFUNCS_NULL_TO_STR(in_ptr->other_chars)) + 1,
			error_text, "Unable to copy the 'KML_NAME' member 'other_chars'");
	else
		return_code = KML_SUCCESS;

	if (return_code != KML_SUCCESS)
		KML_FREE_Name(out_ptr);

	return(return_code);
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	KML_COPY_NameList

	SYNOPSIS		:	return_code = KML_COPY_NameList(in_count, in_list,
							out_count, out_list, error_text);

						int              return_code;

						unsigned int     count;

						const KML_NAME  *list;

						unsigned int    *out_count;

						KML_NAME       **out_list;

						char            *error_text;

	DESCRIPTION	:	Copies an array of ''KML_NAME'' structures.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_count`` is the number of elements in the array
						``in_list``.

						(.) ``in_list`` is the array of ''KML_NAME'' structures
						which is to be copied by this function.

						(.) ``out_count`` is a pointer to an ''unsigned int'' into
						which this function will place the number of elements
						copied.

						(.) ``out_list`` is a pointer to the array of
						''KML_NAME'' structures which will be allocated and
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

	SEE ALSO		:	KML_COPY_Name
						KML_FREE_NameList
						KML_INIT_NameList
						KML_SORT_NameList

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2015 Michael L. Brock

	OUTPUT INDEX:	KML_COPY_NameList
						Copy Functions:KML_COPY_NameList
						KML_NAME Functions:KML_COPY_NameList

	PUBLISH XREF:	KML_COPY_NameList

	PUBLISH NAME:	KML_COPY_NameList

	ENTRY CLASS	:	Copy Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int KML_COPY_NameList(unsigned int in_count, const KML_NAME *in_list,
	unsigned int *out_count, KML_NAME **out_list, char *error_text)
#else
int KML_COPY_NameList(in_count, in_list, out_count, out_list, error_text)
unsigned int     in_count;
const KML_NAME  *in_list;
unsigned int    *out_count;
KML_NAME       **out_list;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = KML_SUCCESS;
	unsigned int count_1;

	*out_count = 0;
	*out_list  = NULL;

	if (in_count) {
		if ((*out_list = ((KML_NAME *) calloc(in_count,
			sizeof(**out_list)))) == NULL) {
			STR_AllocMsgList(in_count, sizeof(**out_list), error_text,
				"Unable to copy a list of 'KML_NAME' structures");
			return_code = KML_MEMORY_FAILURE;
		}
		else {
			*out_count = in_count;
			KML_INIT_NameList(*out_count, *out_list);
			for (count_1 = 0; count_1 < in_count; count_1++) {
				if ((return_code = KML_COPY_Name(in_list + count_1,
					*out_list + count_1, error_text)) != KML_SUCCESS) {
					KML_FREE_NameList(out_count, out_list);
					break;
				}
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

