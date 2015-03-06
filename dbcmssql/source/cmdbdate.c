/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Microsoft SQL Server Support Functions Library Module					*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Compares Microsoft SQL Server date/time date types.

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
int DBC_MSSQL_CMP_DBDATETIME4(ptr_1, ptr_2)
const DBDATETIM4 *ptr_1;
const DBDATETIM4 *ptr_2;
{
	int cmp;

	if (!(cmp = ((ptr_1->numdays > ptr_2->numdays) ? 1 :
		(ptr_1->numdays < ptr_2->numdays) ? -1 : 0)))
		cmp = ((ptr_1->nummins > ptr_2->nummins) ? 1 :
			(ptr_1->nummins < ptr_2->nummins) ? -1 : 0);

	return(cmp);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int DBC_MSSQL_CMP_DBDATETIME(ptr_1, ptr_2)
const DBDATETIME *ptr_1;
const DBDATETIME *ptr_2;
{
	int cmp;

	if (!(cmp = ((ptr_1->dtdays > ptr_2->dtdays) ? 1 :
		(ptr_1->dtdays < ptr_2->dtdays) ? -1 : 0)))
		cmp = ((ptr_1->dttime > ptr_2->dttime) ? 1 :
			(ptr_1->dttime < ptr_2->dttime) ? -1 : 0);

	return(cmp);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int DBC_MSSQL_SCMP_DBDATETIME4(control_ptr, ptr_1, ptr_2, data_length)
void             *control_ptr;
const DBDATETIM4 *ptr_1;
const DBDATETIM4 *ptr_2;
size_t            data_length;
{
	int cmp;

	if (!(cmp = ((ptr_1->numdays > ptr_2->numdays) ? 1 :
		(ptr_1->numdays < ptr_2->numdays) ? -1 : 0)))
		cmp = ((ptr_1->nummins > ptr_2->nummins) ? 1 :
			(ptr_1->nummins < ptr_2->nummins) ? -1 : 0);

	return(cmp);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int DBC_MSSQL_SCMP_DBDATETIME(control_ptr, ptr_1, ptr_2, data_length)
void             *control_ptr;
const DBDATETIME *ptr_1;
const DBDATETIME *ptr_2;
size_t            data_length;
{
	int cmp;

	if (!(cmp = ((ptr_1->dtdays > ptr_2->dtdays) ? 1 :
		(ptr_1->dtdays < ptr_2->dtdays) ? -1 : 0)))
		cmp = ((ptr_1->dttime > ptr_2->dttime) ? 1 :
			(ptr_1->dttime < ptr_2->dttime) ? -1 : 0);

	return(cmp);
}
/*	***********************************************************************	*/

