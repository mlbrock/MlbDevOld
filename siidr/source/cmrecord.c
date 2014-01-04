/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Single Index Internal Data Repository Library Source Module					*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Compares IDR records.

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
int SIIDR_Compare(const SIIDR *siidr_ptr, const void *ptr_1,
	const void *ptr_2, size_t data_length)
{
	return((*siidr_ptr->compare_func)(siidr_ptr, ptr_1, ptr_2,
		siidr_ptr->record_size));
}
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */


