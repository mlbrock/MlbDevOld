/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Generic Sybase Support Functions Library Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Converts between DTIME structures and the various
								Sybase date/time structures.

	Revision History	:	1993-08-14 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	*********************************************************************** */
/*	*********************************************************************** */
/* 	Necessary include files . . .														*/
/*	*********************************************************************** */

#include "dbcsybi.h"

/*	*********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
DBDATETIME4 *DBC_SYB_DTIMEToSybase4(const DTIME *in_date,
	DBDATETIME4 *out_date)
#else
DBDATETIME4 *DBC_SYB_DTIMEToSybase4(in_date, out_date)
const DTIME *in_date;
DBDATETIME4 *out_date;
#endif /* #ifndef NARGS */
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
		out_date->days    = ((unsigned short) in_date->julian_date);
		out_date->minutes =
			((unsigned short) (in_date->milliseconds / (60L * 1000L)));
	}

	return(out_date);
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
DBDATETIME *DBC_SYB_DTIMEToSybase8(const DTIME *in_date, DBDATETIME *out_date)
#else
DBDATETIME *DBC_SYB_DTIMEToSybase8(in_date, out_date)
const DTIME *in_date;
DBDATETIME  *out_date;
#endif /* #ifndef NARGS */
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
#ifndef NARGS
DTIME *DBC_SYB_Sybase4ToDTIME(const DBDATETIME4 *in_date, DTIME *out_date)
#else
DTIME *DBC_SYB_Sybase4ToDTIME(in_date, out_date)
const DBDATETIME4 *in_date;
DTIME             *out_date;
#endif /* #ifndef NARGS */
{
	out_date->julian_date  = ((JULIAN) in_date->days);
	out_date->milliseconds = ((unsigned long) in_date->minutes) *
		(60L * 1000L);

	return(out_date);
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
DTIME *DBC_SYB_Sybase8ToDTIME(const DBDATETIME *in_date, DTIME *out_date)
#else
DTIME *DBC_SYB_Sybase8ToDTIME(in_date, out_date)
const DBDATETIME *in_date;
DTIME            *out_date;
#endif /* #ifndef NARGS */
{
	out_date->julian_date  = in_date->dtdays;
	out_date->milliseconds =
		((unsigned long) ((in_date->dttime / 300L) * 1000L)) +
		((unsigned long) (((in_date->dttime % 300L) * 1000L) / 300L));

	return(out_date);
}
/* *********************************************************************** */

