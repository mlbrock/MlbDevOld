/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Single Index Internal Data Repository Library Source Module					*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Compares IDR bulk record structures.

	Revision History	:	1996-04-12 --- Creation
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

#include "siidri.h"

/*	***********************************************************************	*/

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
int SIIDR_CompareBulk(const SIIDR *siidr_ptr, const SIIDR_BULK *ptr_1,
	const SIIDR_BULK *ptr_2, size_t data_length)
{
	int cmp;

	if ((cmp = (*siidr_ptr->tmp_compare_func)(siidr_ptr, ptr_1->bulk_ptr,
		ptr_2->bulk_ptr, siidr_ptr->record_size)) == 0)
		cmp = ((ptr_1->bulk_index < ptr_2->bulk_index) ? -1 :
			(ptr_1->bulk_index > ptr_2->bulk_index) ? 1 : 0);

	return(cmp);
}
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
int SIIDR_CompareBulkByOrder(const SIIDR *siidr_ptr, const SIIDR_BULK *ptr_1,
	const SIIDR_BULK *ptr_2, size_t data_length)
{
	int cmp;

	if ((cmp = ((ptr_1->record_index < ptr_2->record_index) ? -1 :
		(ptr_1->record_index > ptr_2->record_index) ? 1 : 0)) == 0) {
		if ((cmp = ((ptr_1->compare_index < ptr_2->compare_index) ? -1 :
			(ptr_1->compare_index > ptr_2->compare_index) ? 1 : 0)) == 0)
			cmp = ((ptr_1->bulk_index < ptr_2->bulk_index) ? -1 :
				(ptr_1->bulk_index > ptr_2->bulk_index) ? 1 : 0);
	}

	return(cmp);
}
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

