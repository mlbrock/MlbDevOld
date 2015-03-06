/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Adjusts a JULIAN date.

	Revision History	:	1994-12-08 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	*********************************************************************** */
/*	*********************************************************************** */
/* 	Necessary include files . . .														*/
/*	*********************************************************************** */

#include "datfunci.h"

/*	*********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	jul_GMTToLocal

	SYNOPSIS		:	julian_date = jul_GMTToLocal(in_julian);

						JULIAN julian_date;

						JULIAN in_julian;

	DESCRIPTION	:	Converts a ''JULIAN'' date from GMT/UTC time to local time.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_julian`` is the ''JULIAN'' date which contains
						the date to be converted.

	RETURNS		:	The converted ''JULIAN'' date.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	DTIME_GMTToLocal

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2015 Michael L. Brock

	OUTPUT INDEX:	jul_GMTToLocal
						Date Functions:Date/Time Adjustment Functions:jul_GMTToLocal
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	jul_GMTToLocal

	PUBLISH NAME:	jul_GMTToLocal

	ENTRY CLASS	:	Date Functions:Date/Time Adjustment Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
JULIAN jul_GMTToLocal(JULIAN in_julian)
#else
JULIAN jul_GMTToLocal(in_julian)
JULIAN in_julian;
#endif /* #ifndef NARGS */
{
	DTIME tmp_dtime;

	return(DTIME_GMTToLocal(jultodt(in_julian, &tmp_dtime))->julian_date);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	jul_AdjustHours

	SYNOPSIS		:	julian_date = jul_AdjustHours(in_julian, adj_hours);

						JULIAN julian_date;

						JULIAN in_julian;

						long   adj_hours;

	DESCRIPTION	:	Adjust a given ''JULIAN'' date by the number of hours
						specified.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_julian`` is the ''JULIAN'' date which contains
						the date to be adjusted.

						(.) ``adj_hours`` is the number of hours for which the
						``julian_date`` parameter is to be adjusted. This
						value may be negative.

	RETURNS		:	The adjusted ''JULIAN'' date.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	DTIME_AdjustHours
						jul_AdjustMinutes
						jul_AdjustSeconds
						jul_AdjustMilliseconds

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2015 Michael L. Brock

	OUTPUT INDEX:	jul_AdjustHours
						Date Functions:Date/Time Adjustment Functions:jul_AdjustHours
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	jul_AdjustHours

	PUBLISH NAME:	jul_AdjustHours

	ENTRY CLASS	:	Date Functions:Date/Time Adjustment Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
JULIAN jul_AdjustHours(JULIAN in_julian, long adj_hours)
#else
JULIAN jul_AdjustHours(in_julian, adj_hours)
JULIAN in_julian;
long   adj_hours;
#endif /* #ifndef NARGS */
{
	DTIME tmp_dtime;

	return(DTIME_AdjustHours(jultodt(in_julian, &tmp_dtime),
		adj_hours)->julian_date);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	jul_AdjustMinutes

	SYNOPSIS		:	julian_date = jul_AdjustMinutes(in_julian, adj_minutes);

						JULIAN julian_date;

						JULIAN in_julian;

						long   adj_minutes;

	DESCRIPTION	:	Adjust a given ''JULIAN'' date by the number of minutes
						specified.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_julian`` is the ''JULIAN'' date which contains
						the date to be adjusted.

						(.) ``adj_minutes`` is the number of minutes for which the
						``julian_date`` parameter is to be adjusted. This
						value may be negative.

	RETURNS		:	The adjusted ''JULIAN'' date.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	DTIME_AdjustMinutes
						jul_AdjustHours
						jul_AdjustSeconds
						jul_AdjustMilliseconds

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2015 Michael L. Brock

	OUTPUT INDEX:	jul_AdjustMinutes
						Date Functions:Date/Time Adjustment Functions:jul_AdjustMinutes
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	jul_AdjustMinutes

	PUBLISH NAME:	jul_AdjustMinutes

	ENTRY CLASS	:	Date Functions:Date/Time Adjustment Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
JULIAN jul_AdjustMinutes(JULIAN in_julian, long adj_minutes)
#else
JULIAN jul_AdjustMinutes(in_julian, adj_minutes)
JULIAN in_julian;
long   adj_minutes;
#endif /* #ifndef NARGS */
{
	DTIME tmp_dtime;

	return(DTIME_AdjustMinutes(jultodt(in_julian, &tmp_dtime),
		adj_minutes)->julian_date);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	jul_AdjustSeconds

	SYNOPSIS		:	julian_date = jul_AdjustSeconds(in_julian, adj_seconds);

						JULIAN julian_date;

						JULIAN in_julian;

						long   adj_seconds;

	DESCRIPTION	:	Adjust a given ''JULIAN'' date by the number of seconds
						specified.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_julian`` is the ''JULIAN'' date which contains
						the date to be adjusted.

						(.) ``adj_seconds`` is the number of seconds for which the
						``julian_date`` parameter is to be adjusted. This
						value may be negative.

	RETURNS		:	The adjusted ''JULIAN'' date.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	DTIME_AdjustSeconds
						jul_AdjustHours
						jul_AdjustMinutes
						jul_AdjustMilliseconds

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2015 Michael L. Brock

	OUTPUT INDEX:	jul_AdjustSeconds
						Date Functions:Date/Time Adjustment Functions:jul_AdjustSeconds
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	jul_AdjustSeconds

	PUBLISH NAME:	jul_AdjustSeconds

	ENTRY CLASS	:	Date Functions:Date/Time Adjustment Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
JULIAN jul_AdjustSeconds(JULIAN in_julian, long adj_seconds)
#else
JULIAN jul_AdjustSeconds(in_julian, adj_seconds)
JULIAN in_julian;
long   adj_seconds;
#endif /* #ifndef NARGS */
{
	DTIME tmp_dtime;

	return(DTIME_AdjustSeconds(jultodt(in_julian, &tmp_dtime),
		adj_seconds)->julian_date);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	jul_AdjustMilliseconds

	SYNOPSIS		:	julian_date = jul_AdjustMilliseconds(in_julian,
							adj_milliseconds);

						JULIAN julian_date;

						JULIAN in_julian;

						long   adj_milliseconds;

	DESCRIPTION	:	Adjust a given ''JULIAN'' date by the number of milliseconds
						specified.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_julian`` is the ''JULIAN'' date which contains
						the date to be adjusted.

						(.) ``adj_milliseconds`` the number of milliseconds for
						which the ``julian_date`` parameter is to be adjusted. This
						value may be negative.

	RETURNS		:	The adjusted ''JULIAN'' date.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	DTIME_AdjustMilliseconds
						jul_AdjustHours
						jul_AdjustMinutes
						jul_AdjustSeconds

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2015 Michael L. Brock

	OUTPUT INDEX:	jul_AdjustMilliseconds
						Date Functions:Date/Time Adjustment Functions:jul_AdjustMilliseconds
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	jul_AdjustMilliseconds

	PUBLISH NAME:	jul_AdjustMilliseconds

	ENTRY CLASS	:	Date Functions:Date/Time Adjustment Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
JULIAN jul_AdjustMilliseconds(JULIAN in_julian, long adj_milliseconds)
#else
JULIAN jul_AdjustMilliseconds(in_julian, adj_milliseconds)
JULIAN in_julian;
long   adj_milliseconds;
#endif /* #ifndef NARGS */
{
	DTIME tmp_dtime;

	return(DTIME_AdjustMilliseconds(jultodt(in_julian, &tmp_dtime),
		adj_milliseconds)->julian_date);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>
#include <stdlib.h>

COMPAT_FN_DECL(int main, (int argc, char **argv));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int          return_code = DATFUNCS_SUCCESS;
	unsigned int count_1;
	DTIME        tmp_dtime_1;
	DTIME        tmp_dtime_2;
	char         buffer[100];

	fprintf(stderr, "Test routine for function 'jul_GMTToLocal()'\n");
	fprintf(stderr, "---- ------- --- -------- ------------------\n\n");

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		tmp_dtime_1.julian_date  = atoi(argv[count_1]);
		tmp_dtime_1.milliseconds = 0L;
		tmp_dtime_2              = tmp_dtime_1;
		tmp_dtime_2.julian_date  = jul_GMTToLocal(tmp_dtime_2.julian_date);
		fprintf(stderr,
			"GMT Now  : JULIAN = %11ld, Time = [%s]\n", tmp_dtime_1.julian_date,
			DTIME_FormatDate(&tmp_dtime_1, NULL, buffer));
		fprintf(stderr,
			"Local Now: JULIAN = %11ld, Time = [%s]\n", tmp_dtime_2.julian_date,
			DTIME_FormatDate(&tmp_dtime_2, NULL, buffer));
		fprintf(stderr, "\n");
	}

	return(return_code);
}
/*	*********************************************************************** */

#endif /* #ifdef TEST_MAIN */

