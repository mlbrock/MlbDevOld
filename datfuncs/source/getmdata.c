/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets data concerning months.

	Revision History	:	1989-11-08 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1989 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	*********************************************************************** */
/*	*********************************************************************** */
/* 	Necessary include files . . .														*/
/*	*********************************************************************** */

#include <string.h>

#include "datfunci.h"

/*	*********************************************************************** */

/*	*********************************************************************** */
/*	*********************************************************************** */
/*	*********************************************************************** */

typedef struct {
	char *short_name;
	char *long_name;
	int   days_in_month;
} MONTH_DATA_ARRAY;

/*	*********************************************************************** */

/*	*********************************************************************** */
/*	*********************************************************************** */
/*	*********************************************************************** */

static const MONTH_DATA_ARRAY DATFUNCS_MonthData[] = {
	{ "Jan",	"January",		31 },
	{ "Feb",	"February",		28 },
	{ "Mar",	"March",			31 },
	{ "Apr",	"April",			30 },
	{ "May",	"May",			31 },
	{ "Jun",	"June",			30 },
	{ "Jul",	"July",			31 },
	{ "Aug",	"August",		31 },
	{ "Sep",	"September",	30 },
	{ "Oct",	"October",		31 },
	{ "Nov",	"November",		30 },
	{ "Dec",	"December",		31 }
};

/*	*********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* NOTE:BOH

	NAME			:	getmname

	SYNOPSIS		:	month_name_ptr = getmname(month_number, month_name,
							name_length_flag);

						char *monh_name_ptr;

						int   month_number;

						char *month_name;

						int   name_length_flag;

	DESCRIPTION	:	

   PARAMETERS  :  Parameters to this function are as follow:

   RETURNS     :  Returns from this function are as follow:

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2016 Michael L. Brock

	OUTPUT INDEX:	getmname
						Date Functions:Get Date/Time Component Functions:getmname
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	getmname

	PUBLISH NAME:	getmname

	ENTRY CLASS	:	Date Functions:Get Date/Time Component Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *getmname(int month_number, char *month_name, int name_length_flag)
#else
char *getmname(month_number, month_name, name_length_flag)
int   month_number;
char *month_name;
int   name_length_flag;
#endif /* #ifndef NARGS */
{
	if ((month_number > 0) && (month_number <= MONTHS_IN_YEAR))
		strcpy(month_name, (!name_length_flag) ?
			DATFUNCS_MonthData[month_number - 1].short_name :
			DATFUNCS_MonthData[month_number - 1].long_name);
	else
		*month_name = '\0';

	return(month_name);
}
/*	*********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* NOTE:BOH

	NAME			:	getmnumb

	SYNOPSIS		:	days_in_month = getmnumb(month_number);

						int days_in_month;

						int month_number;

	DESCRIPTION	:	

   PARAMETERS  :  Parameters to this function are as follow:

   RETURNS     :  Returns from this function are as follow:

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2016 Michael L. Brock

	OUTPUT INDEX:	getmnumb
						Date Functions:Get Date/Time Component Functions:getmnumb
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	getmnumb

	PUBLISH NAME:	getmnumb

	ENTRY CLASS	:	Date Functions:Get Date/Time Component Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int getmnumb(int month_number)
#else
int getmnumb(month_number)
int month_number;
#endif /* #ifndef NARGS */
{
	return(((month_number > 0) && (month_number <= MONTHS_IN_YEAR)) ?
		DATFUNCS_MonthData[month_number - 1].days_in_month : 0);
}
/*	*********************************************************************** */

