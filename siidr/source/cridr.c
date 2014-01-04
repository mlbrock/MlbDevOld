/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Single Index Internal Data Repository Library Source Module					*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Creates an SIIDR structure.

	Revision History	:	1996-04-11 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Include necessary header files . . .												*/
/*	***********************************************************************	*/

#include <stdlib.h>
#include <string.h>

#include <strfuncs.h>

#include "siidri.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_CreateIDR(const char *idr_name, unsigned int record_size,
	unsigned int allocation_size, SIIDR_CompareFunc compare_func,
	SIIDR **siidr_ptr, char *error_text)
{
	int  return_code;
	char mtif_error_text[MTIF_MAX_ERROR_TEXT];
	char tmp_error_text[SIIDR_MAX_ERROR_TEXT];

	*siidr_ptr = NULL;
	idr_name = ((idr_name != NULL) && *idr_name) ? idr_name : "*** UNKNOWN ***";

	if (!record_size) {
		if (error_text != NULL)
			strcpy(error_text, "SIIDR structure size is '0'.");
		return_code = SIIDR_BAD_ARGS_FAILURE;
	}
	else if ((return_code = SIIDR_TouchCode(STR_CAST_FUNC_PTR(compare_func),
		tmp_error_text)) != SIIDR_SUCCESS) {
		if (error_text != NULL)
			strcat(strcpy(error_text,
				"Comparison function pointer is invalid: "), tmp_error_text);
	}
	else if ((*siidr_ptr = ((SIIDR *) calloc(1, sizeof(**siidr_ptr)))) ==
		NULL) {
		if (error_text != NULL)
			STR_AllocMsgItem(strlen(idr_name) + 1, error_text,
				"Unable to allocate the SIIDR internal data repository");
		return_code = SIIDR_MEMORY_FAILURE;
	}
	else {
		SIIDR_InitIDR(*siidr_ptr);
		if (((*siidr_ptr)->idr_name = strdup(idr_name)) == NULL) {
			if (error_text != NULL)
				STR_AllocMsgItem(strlen(idr_name) + 1, error_text,
					"Unable to copy SIIDR internal data repository name '%-.500s'",
					idr_name);
			return_code = SIIDR_MEMORY_FAILURE;
		}
		else {
			allocation_size               = (allocation_size) ? allocation_size :
				SIIDR_DEFAULT_ALLOC_SIZE;
			(*siidr_ptr)->record_size     = record_size;
			(*siidr_ptr)->total_size      = record_size;
			(*siidr_ptr)->data_offset     = 0;
			(*siidr_ptr)->allocation_size = allocation_size;
			(*siidr_ptr)->compare_func    = compare_func;
			if ((return_code = MTIF_RWL_Init(SIIDR_RWL_FLAGS,
				NULL, &(*siidr_ptr)->rwl_data, mtif_error_text)) != MTIF_SUCCESS) {
				if (error_text != NULL)
					nstrcat(strcat(nstrcat(strcpy(error_text, 
						"Unable to initialize reader/writer lock for "),
						(*siidr_ptr)->idr_name, 500), " internal data repository: "),
						mtif_error_text, SIIDR_MAX_ERROR_TEXT - 600);
				return_code = SIIDR_MAP_ERROR_MTIF(return_code);
				free((*siidr_ptr)->idr_name);
				SIIDR_InitIDR(*siidr_ptr);
			}
			else {
				(*siidr_ptr)->signature = SIIDR_SIGNATURE;
				if ((return_code = SIIDR_AllocateIDRRaw(*siidr_ptr,
					allocation_size, error_text)) != SIIDR_SUCCESS)
					SIIDR_FreeIDR(*siidr_ptr);
			}
		}
	}

	if (return_code != SIIDR_SUCCESS)
		*siidr_ptr = NULL;

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <stdio.h>

COMPAT_FN_DECL(int main, (void));

int main()
{
	int    return_code;
	SIIDR *siidr_ptr;
	char   error_text[SIIDR_MAX_ERROR_TEXT];

	fprintf(stderr, "Test harness for function 'SIIDR_CreateIDR()'\n");
	fprintf(stderr, "---- ------- --- -------- -------------------\n\n");

	memset(error_text, '\0', sizeof(error_text));

	if ((return_code = SIIDR_CreateIDR("order", 100, 0,
		((SIIDR_CompareFunc) main), &siidr_ptr, error_text)) == SIIDR_SUCCESS) {
		return_code = SIIDR_CheckData(siidr_ptr, error_text);
		SIIDR_FreeIDR(siidr_ptr);
	}

	if (return_code != SIIDR_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

