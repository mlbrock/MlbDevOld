/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Logic to support the comparison of cache records.

	Revision History	:	1995-08-09 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include "dcr.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	DCR_CompareRecords

	SYNOPSIS		:	cmp_value = DCR_CompareRecords(cache_ptr,
							record_ptr_1, record_ptr_2);

						int         cmp_value;

						DCR_CACHE  *cache_ptr;

						const void *record_ptr_1;

						const void *record_ptr_2;

	DESCRIPTION	:	Compares the two cache data records (to which the parameters
						``ptr_1`` and ``ptr_2`` point) for equality.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``cache_ptr`` is a pointer to the structure of type
						''DCR_CACHE'' in which reside the records to be compared.

						(.) ``ptr_1`` points to the first record to be compared.

						(.) ``ptr_2`` points to the second record to be compared.

   RETURNS     :  Returns from this function are as follow:

						(.) negative if the first record is less than the second.

						(.) positive if the first record is greater than the second.

						(.) zero if the records are equal.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2015 Michael L. Brock

	OUTPUT INDEX:	DCR_CompareRecords
						DCR Cache Comparison Functions:DCR_CompareRecords
						DCR Cache Functions:DCR_CompareRecords

	PUBLISH XREF:	DCR_CompareRecords

	PUBLISH NAME:	DCR_CompareRecords

EOH */
/* *********************************************************************** */
int DCR_CompareRecords(cache_ptr, record_ptr_1, record_ptr_2)
DCR_CACHE  *cache_ptr;
const void *record_ptr_1;
const void *record_ptr_2;
{
	GEN_ALIGN_CMP align_cmp;

	align_cmp.ignore_case_flag = 0;
	align_cmp.align_count      = cache_ptr->field_align_count;
	align_cmp.align_list       = cache_ptr->field_align_list;

	return(GEN_ALIGN_CompareList(&align_cmp, record_ptr_1, record_ptr_2,
		cache_ptr->actual_data_record_size));
}
/*	***********************************************************************	*/

