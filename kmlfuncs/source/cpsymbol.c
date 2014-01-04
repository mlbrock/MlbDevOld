/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Copies 'KML_SYMBOL' structures.

	Revision History	:	1998-03-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2014.
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

	NAME			:	KML_COPY_Symbol

	SYNOPSIS		:	return_code = KML_COPY_Symbol(in_ptr, out_ptr, error_text);

						int               return_code;

						const KML_SYMBOL *ptr;

						KML_SYMBOL       *out_ptr;

						char             *error_text;

	DESCRIPTION	:	Copies a ''KML_SYMBOL'' structure.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_ptr`` is a pointer to the ''KML_SYMBOL''
						structure which is to be copied by this function.

						(.) ``out_ptr`` is a pointer to the ''KML_SYMBOL''
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

	SEE ALSO		:	KML_COPY_SymbolList
						KML_FREE_Symbol
						KML_INIT_Symbol
						KML_SCMP_Symbol

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2014 Michael L. Brock

	OUTPUT INDEX:	KML_COPY_Symbol
						Copy Functions:KML_COPY_Symbol
						KML_SYMBOL Functions:KML_COPY_Symbol

	PUBLISH XREF:	KML_COPY_Symbol

	PUBLISH NAME:	KML_COPY_Symbol

	ENTRY CLASS	:	Copy Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int KML_COPY_Symbol(const KML_SYMBOL *in_ptr, KML_SYMBOL *out_ptr,
	char *error_text)
#else
int KML_COPY_Symbol(in_ptr, out_ptr, error_text)
const KML_SYMBOL *in_ptr;
KML_SYMBOL       *out_ptr;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = KML_MEMORY_FAILURE;

	KML_INIT_Symbol(out_ptr);

	if ((out_ptr->ptr =
		strdup(STRFUNCS_NULL_TO_STR(in_ptr->ptr))) == NULL)
		STR_AllocMsgItem(strlen(STRFUNCS_NULL_TO_STR(in_ptr->ptr)) + 1,
			error_text, "Unable to copy the 'KML_SYMBOL' member 'ptr'");
	else {
		out_ptr->length = strlen(out_ptr->ptr);
		return_code     = KML_SUCCESS;
	}

	if (return_code != KML_SUCCESS)
		KML_FREE_Symbol(out_ptr);

	return(return_code);
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	KML_COPY_SymbolList

	SYNOPSIS		:	return_code = KML_COPY_SymbolList(in_count, in_list,
							out_count, out_list, error_text);

						int                return_code;

						unsigned int       count;

						const KML_SYMBOL  *list;

						unsigned int      *out_count;

						KML_SYMBOL       **out_list;

						char              *error_text;

	DESCRIPTION	:	Copies an array of ''KML_SYMBOL'' structures.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_count`` is the number of elements in the array
						``in_list``.

						(.) ``in_list`` is the array of ''KML_SYMBOL'' structures
						which is to be copied by this function.

						(.) ``out_count`` is a pointer to an ''unsigned int'' into
						which this function will place the number of elements
						copied.

						(.) ``out_list`` is a pointer to the array of
						''KML_SYMBOL'' structures which will be allocated and
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

	SEE ALSO		:	KML_COPY_Symbol
						KML_FREE_SymbolList
						KML_INIT_SymbolList
						KML_SORT_SymbolList

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2014 Michael L. Brock

	OUTPUT INDEX:	KML_COPY_SymbolList
						Copy Functions:KML_COPY_SymbolList
						KML_SYMBOL Functions:KML_COPY_SymbolList

	PUBLISH XREF:	KML_COPY_SymbolList

	PUBLISH NAME:	KML_COPY_SymbolList

	ENTRY CLASS	:	Copy Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int KML_COPY_SymbolList(unsigned int in_count, const KML_SYMBOL *in_list,
	unsigned int *out_count, KML_SYMBOL **out_list, char *error_text)
#else
int KML_COPY_SymbolList(in_count, in_list, out_count, out_list, error_text)
unsigned int       in_count;
const KML_SYMBOL  *in_list;
unsigned int      *out_count;
KML_SYMBOL       **out_list;
char              *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = KML_SUCCESS;
	unsigned int count_1;

	*out_count = 0;
	*out_list  = NULL;

	if (in_count) {
		if ((*out_list = ((KML_SYMBOL *) calloc(in_count,
			sizeof(**out_list)))) == NULL) {
			STR_AllocMsgList(in_count, sizeof(**out_list), error_text,
				"Unable to copy a list of 'KML_SYMBOL' structures");
			return_code = KML_MEMORY_FAILURE;
		}
		else {
			*out_count = in_count;
			KML_INIT_SymbolList(*out_count, *out_list);
			for (count_1 = 0; count_1 < in_count; count_1++) {
				if ((return_code = KML_COPY_Symbol(in_list + count_1,
					*out_list + count_1, error_text)) != KML_SUCCESS) {
					KML_FREE_SymbolList(out_count, out_list);
					break;
				}
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

