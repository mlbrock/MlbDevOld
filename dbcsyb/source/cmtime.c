/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Generic Sybase Support Functions Library Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Generic comparison of Sybase time types.

	Revision History	:	1993-08-14 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2015.
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
int DBC_SYB_CMP_Time(int dbc_type, const void *ptr_1, const void *ptr_2)
#else
int DBC_SYB_CMP_Time(dbc_type, ptr_1, ptr_2)
int         dbc_type;
const void *ptr_1;
const void *ptr_2;
#endif /* #ifndef NARGS */
{
	return(((dbc_type == SYBDATETIME4) ?
		DBC_SYB_CMP_DBDATETIME4(((const DBDATETIME4 *) ptr_1),
		((const DBDATETIME4 *) ptr_2)) : (dbc_type == SYBDATETIME) ?
		DBC_SYB_CMP_DBDATETIME(((const DBDATETIME *) ptr_1),
		((const DBDATETIME *) ptr_2)) : 0));
}
/*	***********************************************************************	*/

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
#ifndef NARGS
int DBC_SYB_SCMP_Time(void *control_ptr, const void *ptr_1,
	const void *ptr_2, size_t data_length)
#else
int DBC_SYB_SCMP_Time(control_ptr, ptr_1, ptr_2, data_length)
void       *control_ptr;
const void *ptr_1;
const void *ptr_2;
size_t      data_length;
#endif /* #ifndef NARGS */
{
	return(DBC_SYB_CMP_Time(((int) data_length), ptr_1, ptr_2));
}
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

