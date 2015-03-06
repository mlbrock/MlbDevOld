/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Microsoft SQL Server Support Functions Library Module					*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Compares Microsoft SQL Server number types.

	Revision History	:	1995-12-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include "dbcmssql.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int DBC_MSSQL_CMP_Number(dbc_type, ptr_1, ptr_2)
int         dbc_type;
const void *ptr_1;
const void *ptr_2;
{
	int cmp;

	switch (dbc_type) {
		case SQLINT1	:
			cmp = (*((const unsigned char *) ptr_1) >
				*((const unsigned char *) ptr_2)) ? 1 :
				(*((const unsigned char *) ptr_1) <
				*((const unsigned char *) ptr_1)) ? -1 : 0;
			break;
		case SQLINT2	:
			cmp = (*((const short *) ptr_1) > *((const short *) ptr_2)) ? 1 :
				(*((const short *) ptr_1) < *((const short *) ptr_1)) ? -1 : 0;
			break;
		case SQLINT4	:
			cmp = (*((const long *) ptr_1) > *((const long *) ptr_2)) ? 1 :
				(*((const long *) ptr_1) < *((const long *) ptr_1)) ? -1 : 0;
			break;
		case SQLFLT4	:
			cmp = (*((const float *) ptr_1) > *((const float *) ptr_2)) ? 1 :
				(*((const float *) ptr_1) < *((const float *) ptr_1)) ? -1 : 0;
			break;
		case SQLFLT8	:
			cmp = (*((const double *) ptr_1) > *((const double *) ptr_2)) ? 1 :
				(*((const double *) ptr_1) < *((const double *) ptr_1)) ? -1 : 0;
			break;
		case SQLMONEY4	:
			cmp = (((const DBMONEY4 *) ptr_1) >
				((const DBMONEY4 *) ptr_2)) ? 1 :
				(((const DBMONEY4 *) ptr_1) <
				((const DBMONEY4 *) ptr_1)) ? -1 : 0;
			break;
		case SQLMONEY	:
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

/*	***********************************************************************	*/
int DBC_MSSQL_SCMP_Number(control_ptr, ptr_1, ptr_2, data_length)
void       *control_ptr;
const void *ptr_1;
const void *ptr_2;
size_t      data_length;
{
	return(DBC_MSSQL_CMP_Number(((int) data_length), ptr_1, ptr_2));
}
/*	***********************************************************************	*/

