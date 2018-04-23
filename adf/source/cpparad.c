/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Logic to support the copying of 'ADF_PARA_DATA'
								structures.

	Revision History	:	1996-04-15 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2018.
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

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_COPY_ParaDataList(unsigned int in_para_count,
	const ADF_PARA_DATA *in_para_list, unsigned int *out_para_count,
	ADF_PARA_DATA **out_para_list, char *error_text)
#else
int ADF_COPY_ParaDataList(in_para_count, in_para_list, out_para_count,
	out_para_list, error_text)
unsigned int          in_para_count;
const ADF_PARA_DATA  *in_para_list;
unsigned int         *out_para_count;
ADF_PARA_DATA       **out_para_list;
char                 *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = ADF_SUCCESS;
	unsigned int count_1;

	*out_para_count = 0;
	*out_para_list  = NULL;

	if (in_para_count && ((*out_para_list = ((ADF_PARA_DATA *)
		calloc(in_para_count, sizeof(ADF_PARA_DATA)))) == NULL)) {
		STR_AllocMsgList(in_para_count, sizeof(ADF_PARA_DATA), error_text,
			"Unable to copy an ADF entry area paragraph list");
		return_code = ADF_MEMORY_FAILURE;
	}
	else {
		*out_para_count = in_para_count;
		ADF_INIT_ParaDataList(*out_para_count, *out_para_list);
		for (count_1 = 0; count_1 < in_para_count; count_1++) {
			if ((return_code = ADF_COPY_ParaData(in_para_list + count_1,
				*out_para_list + count_1, error_text)) != ADF_SUCCESS)
				break;
		}
	}

	if (return_code != ADF_SUCCESS)
		ADF_FREE_ParaDataList(out_para_count, out_para_list);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_COPY_ParaData(const ADF_PARA_DATA *in_para_ptr,
	ADF_PARA_DATA *out_para_ptr, char *error_text)
#else
int ADF_COPY_ParaData(in_para_ptr, out_para_ptr, error_text)
const ADF_PARA_DATA *in_para_ptr;
ADF_PARA_DATA       *out_para_ptr;
char                *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = ADF_SUCCESS;

	*out_para_ptr = *in_para_ptr;

	if ((in_para_ptr->text_ptr != NULL) &&
		((out_para_ptr->text_ptr = strdup(in_para_ptr->text_ptr)) == NULL)) {
		ADF_INIT_ParaData(out_para_ptr);
		STR_AllocMsgItem(strlen(in_para_ptr->text_ptr) + 1, error_text,
			"Unable to copy an ADF entry area paragraph");
		return_code = ADF_MEMORY_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

