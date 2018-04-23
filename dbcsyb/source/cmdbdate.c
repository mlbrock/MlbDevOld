/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Generic Sybase Support Functions Library Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Compares Sybase date/time date types.

	Revision History	:	1993-08-14 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include "dbcsybi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int DBC_SYB_CMP_DBDATETIME4(const DBDATETIME4 *ptr_1, const DBDATETIME4 *ptr_2)
#else
int DBC_SYB_CMP_DBDATETIME4(ptr_1, ptr_2)
const DBDATETIME4 *ptr_1;
const DBDATETIME4 *ptr_2;
#endif /* #ifndef NARGS */
{
	int cmp;

	if ((cmp = ((ptr_1->days > ptr_2->days) ? 1 :
		(ptr_1->days < ptr_2->days) ? -1 : 0)) == 0)
		cmp = ((ptr_1->minutes > ptr_2->minutes) ? 1 :
			(ptr_1->minutes < ptr_2->minutes) ? -1 : 0);

	return(cmp);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int DBC_SYB_CMP_DBDATETIME(const DBDATETIME *ptr_1, const DBDATETIME *ptr_2)
#else
int DBC_SYB_CMP_DBDATETIME(ptr_1, ptr_2)
const DBDATETIME *ptr_1;
const DBDATETIME *ptr_2;
#endif /* #ifndef NARGS */
{
	int cmp;

	if ((cmp = ((ptr_1->dtdays > ptr_2->dtdays) ? 1 :
		(ptr_1->dtdays < ptr_2->dtdays) ? -1 : 0)) == 0)
		cmp = ((ptr_1->dttime > ptr_2->dttime) ? 1 :
			(ptr_1->dttime < ptr_2->dttime) ? -1 : 0);

	return(cmp);
}
/*	***********************************************************************	*/

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
#ifndef NARGS
int DBC_SYB_SCMP_DBDATETIME4(void *control_ptr, const DBDATETIME4 *ptr_1,
	const DBDATETIME4 *ptr_2, size_t data_length)
#else
int DBC_SYB_SCMP_DBDATETIME4(control_ptr, ptr_1, ptr_2, data_length)
void              *control_ptr;
const DBDATETIME4 *ptr_1;
const DBDATETIME4 *ptr_2;
size_t             data_length;
#endif /* #ifndef NARGS */
{
	int cmp;

	if ((cmp = ((ptr_1->days > ptr_2->days) ? 1 :
		(ptr_1->days < ptr_2->days) ? -1 : 0)) == 0)
		cmp = ((ptr_1->minutes > ptr_2->minutes) ? 1 :
			(ptr_1->minutes < ptr_2->minutes) ? -1 : 0);

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
#ifndef NARGS
int DBC_SYB_SCMP_DBDATETIME(void *control_ptr, const DBDATETIME *ptr_1,
	const DBDATETIME *ptr_2, size_t data_length)
#else
int DBC_SYB_SCMP_DBDATETIME(control_ptr, ptr_1, ptr_2, data_length)
void             *control_ptr;
const DBDATETIME *ptr_1;
const DBDATETIME *ptr_2;
size_t            data_length;
#endif /* #ifndef NARGS */
{
	int cmp;

	if ((cmp = ((ptr_1->dtdays > ptr_2->dtdays) ? 1 :
		(ptr_1->dtdays < ptr_2->dtdays) ? -1 : 0)) == 0)
		cmp = ((ptr_1->dttime > ptr_2->dttime) ? 1 :
			(ptr_1->dttime < ptr_2->dttime) ? -1 : 0);

	return(cmp);
}
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

