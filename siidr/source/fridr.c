/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Single Index Internal Data Repository Library Source Module					*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Frees the memory associated with an SIIDR
								structure.

	Revision History	:	1996-04-11 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2015.
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

#include "siidri.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	SIIDR_FreeIDR

	SYNOPSIS		:	void SIIDR_FreeIDR(siidr_ptr);

						SIIDR *siidr_ptr;

	DESCRIPTION	:	Frees the members of a ''SIIDR'' structure.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``siidr_ptr`` points to the ''SIIDR'' structure
						to be freed by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	SIIDR_InitIDR

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2015 Michael L. Brock

	OUTPUT INDEX:	SIIDR_FreeIDR
						Memory Free Functions:SIIDR_FreeIDR
						SIIDR:Memory Free Functions:SIIDR_FreeIDR
						SIIDR:SIIDR_FreeIDR
						SIIDR:SIIDR Library Functions:Memory Free Functions:SIIDR_FreeIDR
						SIIDR Library Functions:Memory Free Functions:SIIDR_FreeIDR
						Single Index Internal Data Repository:see SIIDR

	PUBLISH XREF:	SIIDR_FreeIDR

	PUBLISH NAME:	SIIDR_FreeIDR

	ENTRY CLASS	:	Memory Free Functions

EOH */
/*	***********************************************************************	*/
void SIIDR_FreeIDR(SIIDR *siidr_ptr)
{
	int          return_code;
	unsigned int count_1;

	if (SIIDR_CheckIDR(siidr_ptr, NULL) == SIIDR_SUCCESS) {
		return_code = SIIDR_LockWriterIDR(siidr_ptr, NULL);
		siidr_ptr->signature = 0L;
		for (count_1 = 0; count_1 < siidr_ptr->record_count; count_1++) {
			if (siidr_ptr->record_list[count_1] != NULL) {
				free(siidr_ptr->record_list[count_1]);
				siidr_ptr->record_list[count_1] = NULL;
			}
		}
		if (siidr_ptr->record_list != NULL) {
			free(siidr_ptr->record_list);
			siidr_ptr->record_list = NULL;
		}
		if (siidr_ptr->idr_name != NULL) {
			free(siidr_ptr->idr_name);
			siidr_ptr->idr_name = NULL;
		}
		siidr_ptr->signature       = 0L;
		siidr_ptr->allocated_count = 0;
		siidr_ptr->record_count    = 0;
		if (return_code == SIIDR_SUCCESS)
			MTIF_RWL_Unlock(&siidr_ptr->rwl_data, NULL);
		MTIF_RWL_Destroy(&siidr_ptr->rwl_data, NULL);
		SIIDR_InitIDR(siidr_ptr);
		free(siidr_ptr);
	}
}
/*	***********************************************************************	*/

