/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Single Index Internal Data Repository Library Source Module					*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Allocates an SIIDR structure.

	Revision History	:	1996-04-11 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include <stdlib.h>
#include <string.h>

#include <strfuncs.h>

#include "siidri.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_AllocateIDR(SIIDR *siidr_ptr, unsigned int alloc_count,
	char *error_text)
{
	int return_code;

	if (((return_code = SIIDR_ClearErrorOpt(error_text)) == SIIDR_SUCCESS) &&
		((return_code = SIIDR_CheckIDR(siidr_ptr, error_text)) ==
		SIIDR_SUCCESS)) {
		if ((return_code = SIIDR_LockWriterIDR(siidr_ptr, error_text)) ==
			SIIDR_SUCCESS) {
			if ((return_code = SIIDR_AllocateIDRRaw(siidr_ptr, alloc_count,
				error_text)) == SIIDR_SUCCESS)
				return_code = SIIDR_UnLockWriterIDR(siidr_ptr, error_text);
			else
				SIIDR_UnLockWriterIDR(siidr_ptr, NULL);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_AllocateIDRRaw(SIIDR *siidr_ptr, unsigned int alloc_count,
	char *error_text)
{
	int          return_code = SIIDR_SUCCESS;
	unsigned int new_count;

	alloc_count = (alloc_count) ? alloc_count : 1;

	if (alloc_count > (siidr_ptr->allocated_count - siidr_ptr->record_count)) {
		new_count = alloc_count -
			(siidr_ptr->allocated_count - siidr_ptr->record_count);
		return_code = SIIDR_AllocateIDRBasicRaw(siidr_ptr,
         siidr_ptr->allocated_count + new_count, siidr_ptr->allocation_size,
			error_text);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_AllocateIDRBasicRaw(SIIDR *siidr_ptr,
	unsigned int allocation_count, unsigned int allocation_size,
	char *error_text)
{
	int               return_code = SIIDR_SUCCESS;
	unsigned int      alloc_count;
	unsigned int      count_1;
	void            **tmp_list;
	SDTIF_STAT_TVAL   stat_data;

	stat_data = siidr_ptr->stat_list[SIIDR_STAT_ALLOC];
	SDTIF_STAT_TVAL_StartTime(&stat_data);

	if (allocation_count > siidr_ptr->allocated_count) {
		alloc_count = allocation_count +
			((allocation_count % allocation_size) ?
			(allocation_size - (allocation_count % allocation_size)) : 0);
		if ((tmp_list = ((void **) ((!siidr_ptr->allocated_count) ?
			calloc(alloc_count, sizeof(void *)) :
			realloc(siidr_ptr->record_list,
			alloc_count * sizeof(void *))))) == NULL) {
			if (error_text != NULL)
				STR_AllocMsgList(alloc_count, sizeof(void *), error_text,
					"%s %sallocate the %-.500s %s %u %s %u %s (%s %u) %s %u %s",
					"Unable to", (siidr_ptr->allocated_count) ? "re-" : "",
					siidr_ptr->idr_name,
					"internal data repository with", siidr_ptr->allocated_count,
					"initial record elements to add", allocation_count,
					"new IDR record elements",
					"rounding using an allocation size of", allocation_size,
					"for a total of", alloc_count, "record elements");
			return_code = SIIDR_MEMORY_FAILURE;
		}
		else {
			for (count_1 = siidr_ptr->allocated_count;
				count_1 < alloc_count; count_1++)
				tmp_list[count_1] = NULL;
			siidr_ptr->record_list                 = tmp_list;
			siidr_ptr->stat_list[SIIDR_STAT_ALLOC] =
				*SDTIF_STAT_TVAL_EndTime(&stat_data,
				((unsigned long) (alloc_count - siidr_ptr->allocated_count)));
			siidr_ptr->allocated_count             = alloc_count;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

