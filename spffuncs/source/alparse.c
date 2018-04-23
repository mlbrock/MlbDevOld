/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Specification Parse Facility (SPF) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Allocates 'SPF_PARSE' structures.

	Revision History	:	1995-08-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <memory.h>
#include <stdlib.h>
#include <string.h>

#include "spffunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int SPF_ALLC_Parse(SPF_PARSE *ptr, char *error_text)
#else
int SPF_ALLC_Parse(ptr, error_text)
SPF_PARSE *ptr;
char      *error_text;
#endif /* #ifndef NARGS */
{
	int   return_code = SPF_SUCCESS;
	char *tmp_ptr;
	char  tmp_error_text[SPF_MAX_ERROR_TEXT];

	if ((!ptr->flags) && ptr->length && (ptr->text != NULL)) {
		if ((tmp_ptr = ((char *) calloc(ptr->length + 1, sizeof(char)))) ==
			NULL) {
			STR_AllocMsgItem(ptr->length + 1, error_text,
				"Unable to allocate the parse item text %s",
				SPF_GetLocationFile(ptr, 500, tmp_error_text));
			return_code = SPF_MEMORY_FAILURE;
		}
		else {
			memcpy(tmp_ptr, ptr->text, ptr->length);
			ptr->text = tmp_ptr;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int SPF_ALLC_ParseList(unsigned int count, SPF_PARSE *list, char *error_text)
#else
int SPF_ALLC_ParseList(count, list, error_text)
unsigned int  count;
SPF_PARSE    *list;
char         *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = SPF_SUCCESS;
	unsigned int count_1;

	for (count_1 = 0; count_1 < count; count_1++) {
		if ((return_code = SPF_ALLC_Parse(list + count_1, error_text)) !=
			SPF_SUCCESS)
			break;
	}

	return(return_code);
}
/*	***********************************************************************	*/

