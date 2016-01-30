/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Generic Sybase Support Functions Library Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Compares Sybase number types.

	Revision History	:	1993-08-14 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2016.
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
int DBC_SYB_CMP_Number(int dbc_type, const void *ptr_1, const void *ptr_2)
#else
int DBC_SYB_CMP_Number(dbc_type, ptr_1, ptr_2)
int         dbc_type;
const void *ptr_1;
const void *ptr_2;
#endif /* #ifndef NARGS */
{
	int cmp;

	switch (dbc_type) {
		case SYBINT1	:
			cmp = (*((const unsigned char *) ptr_1) >
				*((const unsigned char *) ptr_2)) ? 1 :
				(*((const unsigned char *) ptr_1) <
				*((const unsigned char *) ptr_1)) ? -1 : 0;
			break;
		case SYBINT2	:
			cmp = (*((const short *) ptr_1) > *((const short *) ptr_2)) ? 1 :
				(*((const short *) ptr_1) < *((const short *) ptr_1)) ? -1 : 0;
			break;
		case SYBINT4	:
			cmp = (*((const long *) ptr_1) > *((const long *) ptr_2)) ? 1 :
				(*((const long *) ptr_1) < *((const long *) ptr_1)) ? -1 : 0;
			break;
		case SYBREAL	:
			cmp = (*((const float *) ptr_1) > *((const float *) ptr_2)) ? 1 :
				(*((const float *) ptr_1) < *((const float *) ptr_1)) ? -1 : 0;
			break;
		case SYBFLT8	:
			cmp = (*((const double *) ptr_1) > *((const double *) ptr_2)) ? 1 :
				(*((const double *) ptr_1) < *((const double *) ptr_1)) ? -1 : 0;
			break;
		case SYBMONEY4	:
			cmp = (((const DBMONEY4 *) ptr_1)->mny4 >
				((const DBMONEY4 *) ptr_2)->mny4) ? 1 :
				(((const DBMONEY4 *) ptr_1)->mny4 <
				((const DBMONEY4 *) ptr_1)->mny4) ? -1 : 0;
			break;
		case SYBMONEY	:
			cmp = (((const DBMONEY *) ptr_1)->mnyhigh >
				((const DBMONEY *) ptr_2)->mnyhigh) ? 1 :
				(((const DBMONEY *) ptr_1)->mnyhigh <
				((const DBMONEY *) ptr_2)->mnyhigh) ? -1 :
				((((const DBMONEY *) ptr_1)->mnylow >
				((const DBMONEY *) ptr_2)->mnylow) ? 1 :
				(((const DBMONEY *) ptr_1)->mnylow <
				((const DBMONEY *) ptr_2)->mnylow) ? -1 : 0);
			break;
		default			:
			cmp = 0;
			break;
	}

	return(cmp);
}
/*	***********************************************************************	*/

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
#ifndef NARGS
int DBC_SYB_SCMP_Number(void *control_ptr, const void *ptr_1,
	const void *ptr_2, size_t data_length)
#else
int DBC_SYB_SCMP_Number(control_ptr, ptr_1, ptr_2, data_length)
void       *control_ptr;
const void *ptr_1;
const void *ptr_2;
size_t      data_length;
#endif /* #ifndef NARGS */
{
	return(DBC_SYB_CMP_Number(((int) data_length), ptr_1, ptr_2));
}
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

