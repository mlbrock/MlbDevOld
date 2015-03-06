/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Microsoft SQL Server Support Functions Library Module					*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Converts between DTIME structures and the various
								Microsoft SQL Server date/time structures.

	Revision History	:	1995-12-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	*********************************************************************** */
/*	*********************************************************************** */
/* 	Necessary include files . . .														*/
/*	*********************************************************************** */

#include "dbcmssql.h"

/*	*********************************************************************** */

/* *********************************************************************** */
DBDATETIM4 *DBC_MSSQL_DTIMEToMSSQL4(in_date, out_date)
const DTIME *in_date;
DBDATETIM4  *out_date;
{
	int tmp_year;
	int tmp_month;
	int tmp_day;

	/* CODE NOTE: Should calculate constants for this . . . */
	jultoymd(in_date->julian_date, &tmp_year, &tmp_month, &tmp_day);

	if ((tmp_year < 1900) || (tmp_year > 2079) ||
		((tmp_year == 2079) && (tmp_month == 6) && (tmp_day == 6)))
		out_date = NULL;
	else {
		out_date->numdays = ((unsigned short) in_date->julian_date);
		out_date->nummins =
			((unsigned short) (in_date->milliseconds / (60L * 1000L)));
	}

	return(out_date);
}
/* *********************************************************************** */

/* *********************************************************************** */
DBDATETIME *DBC_MSSQL_DTIMEToMSSQL8(in_date, out_date)
const DTIME *in_date;
DBDATETIME  *out_date;
{
	/* CODE NOTE: Should calculate constants for this . . . */
	if (getyear(in_date->julian_date) <= DATFUNCS_GREGORIAN_YEAR)
		out_date = NULL;
	else {
		out_date->dtdays = in_date->julian_date;
		out_date->dttime = ((in_date->milliseconds / 1000L) * 300L) +
			(((in_date->milliseconds % 1000L) * 1000L) / 3333L);
	}

	return(out_date);
}
/* *********************************************************************** */

/* *********************************************************************** */
DTIME *DBC_MSSQL_MSSQL4ToDTIME(in_date, out_date)
const DBDATETIM4 *in_date;
DTIME            *out_date;
{
	out_date->julian_date  = ((JULIAN) in_date->numdays);
	out_date->milliseconds = ((unsigned long) in_date->nummins) *
		(60L * 1000L);

	return(out_date);
}
/* *********************************************************************** */

/* *********************************************************************** */
DTIME *DBC_MSSQL_MSSQL8ToDTIME(in_date, out_date)
const DBDATETIME *in_date;
DTIME            *out_date;
{
	out_date->julian_date  = in_date->dtdays;
	out_date->milliseconds =
		((unsigned long) ((in_date->dttime / 300L) * 1000L)) +
		((unsigned long) (((in_date->dttime % 300L) * 1000L) / 300L));

	return(out_date);
}
/* *********************************************************************** */

