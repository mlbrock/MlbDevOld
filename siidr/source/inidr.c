/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Single Index Internal Data Repository Library Source Module					*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes an SIIDR structure.

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

#include <memory.h>

#include "siidri.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	SIIDR_InitIDR

	SYNOPSIS		:	void SIIDR_InitIDR(siidr_ptr);

						SIIDR *siidr_ptr;

	DESCRIPTION	:	Initializes the members of a ''SIIDR''
						structure to their default values.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``siidr_ptr`` points to the ''SIIDR'' structure
						to be initialized by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2016 Michael L. Brock

	OUTPUT INDEX:	SIIDR_InitIDR
						Initialization Functions:Internal Data Repository Library Functions:SIIDR_InitIDR
						Internal Data Repository Library Functions:Initialization Functions:SIIDR_InitIDR

	PUBLISH XREF:	SIIDR_InitIDR

	PUBLISH NAME:	SIIDR_InitIDR

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
void SIIDR_InitIDR(SIIDR *siidr_ptr)
{
	unsigned int count_1;

	memset(siidr_ptr, '\0', sizeof(*siidr_ptr));

	siidr_ptr->signature        = 0L;
	siidr_ptr->record_size      = 0;
	siidr_ptr->total_size       = 0;
	siidr_ptr->data_offset      = 0;
	siidr_ptr->allocation_size  = 0;
	siidr_ptr->allocated_count  = 0;
	siidr_ptr->compare_func     = NULL;
	siidr_ptr->record_count     = 0;
	siidr_ptr->record_list      = NULL;
	siidr_ptr->idr_name         = NULL;
	siidr_ptr->tmp_compare_func = NULL;

	for (count_1 = 0; count_1 < SIIDR_STAT_COUNT; count_1++)
		SDTIF_STAT_TVAL_Init(siidr_ptr->stat_list + count_1);
}
/*	***********************************************************************	*/

