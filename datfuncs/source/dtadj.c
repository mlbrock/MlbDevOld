/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Adjusts a DTIME structure.

	Revision History	:	1994-11-28 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	*********************************************************************** */
/*	*********************************************************************** */
/* 	Necessary include files . . .														*/
/*	*********************************************************************** */

#include <limits.h>
#include <stdlib.h>

#include "datfunci.h"

/*	*********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	DTIME_GetGMTToLocalSeconds

	SYNOPSIS		:	adj_seconds = DTIME_GetGMTToLocalSeconds(in_dtime_ptr);

						long   adj_seconds;

						DTIME *in_dtime_ptr;

	DESCRIPTION	:	Determines the difference between GMT/UTC and local time
						for a specified date.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_dtime_ptr`` points to the structure of type
						''DTIME'' for which is the difference between GMT/UTC
						and local time is to be determined.

	RETURNS		:	The difference in seconds between the ``in_dtime_ptr`` date
						in GMT/UTC time and the ``in_dtime_ptr`` date in locale time.

	NOTES			:	

	CAVEATS		:	Dates before the minimum ANSI ''time_t'' date and after the
						maximum ''time_t'' date will not include any attempt to
						included the effects of Daylight Savings Time on the number
						of seconds returned.

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2014 Michael L. Brock

	OUTPUT INDEX:	DTIME_GetGMTToLocalSeconds
						Date Functions:Date/Time Adjustment Functions:DTIME_GetGMTToLocalSeconds
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	DTIME_GetGMTToLocalSeconds

	PUBLISH NAME:	DTIME_GetGMTToLocalSeconds

	ENTRY CLASS	:	Date Functions:Date/Time Adjustment Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
long DTIME_GetGMTToLocalSeconds(const DTIME *in_dtime_ptr)
#else
long DTIME_GetGMTToLocalSeconds(in_dtime_ptr)
const DTIME *in_dtime_ptr;
#endif /* #ifndef NARGS */
{
	time_t    tmp_time_t;
	struct tm tmp_tm;
	DTIME     tmp_dtime;
	double    tmp_double_1;
	double    tmp_double_2;

	tmp_double_1 = ((((double) in_dtime_ptr->julian_date) -
		((double) DATFUNCS_UNIX_EPOCH_JULIAN)) * (24.0 * 60.0 * 60.0)) +
		(((double) in_dtime_ptr->milliseconds) / 1000.0);

	if (tmp_double_1 < (((double) ((long) LONG_MIN)) + (24.0 * 60.0 * 60.0)))
		tmp_time_t = ((time_t) (((long) LONG_MIN) + (24L * 60L * 60L)));
	else if (tmp_double_1 > (((double) LONG_MAX) - (24.0 * 60.0 * 60.0)))
		tmp_time_t = ((time_t) (LONG_MAX - (24L * 60L * 60L)));
	else
		tmp_time_t = ((time_t) tmp_double_1);

	SDTIF_GetTimeGMT(&tmp_time_t, &tmp_tm);
	tmp_dtime.julian_date  = ymdtojul(1900 + tmp_tm.tm_year,
		tmp_tm.tm_mon + 1, tmp_tm.tm_mday);
	tmp_dtime.milliseconds =
		((((unsigned long) tmp_tm.tm_hour) * (60L * 60L)) +
		(((unsigned long) tmp_tm.tm_min) * 60L) +
		((unsigned long) tmp_tm.tm_sec)) * 1000L;
	tmp_double_1           = (((double) tmp_dtime.julian_date) *
		(24.0 * 60.0 * 60.0 * 1000.0)) + ((double) tmp_dtime.milliseconds);

	SDTIF_GetTimeLocal(&tmp_time_t, &tmp_tm);
	tmp_dtime.julian_date  = ymdtojul(1900 + tmp_tm.tm_year,
		tmp_tm.tm_mon + 1, tmp_tm.tm_mday);
	tmp_dtime.milliseconds =
		((((unsigned long) tmp_tm.tm_hour) * (60L * 60L)) +
		(((unsigned long) tmp_tm.tm_min) * 60L) +
		((unsigned long) tmp_tm.tm_sec)) * 1000L;
	tmp_double_2           = (((double) tmp_dtime.julian_date) *
		(24.0 * 60.0 * 60.0 * 1000.0)) + ((double) tmp_dtime.milliseconds);

	return(((long) ((tmp_double_2 - tmp_double_1) / 1000.0)));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	DTIME_GMTToLocal

	SYNOPSIS		:	dtime_ptr = DTIME_GMTToLocal(in_dtime_ptr);

						DTIME *dtime_ptr;

						DTIME *in_dtime_ptr;

	DESCRIPTION	:	Converts a ''DTIME'' structure from GMT/UTC time to local
						time.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_dtime_ptr`` points to the structure of type
						''DTIME'' in which is the GMT/UTC to be converted. The
						time resulting from the conversion to local time will
						be placed into this structure.

	RETURNS		:	A pointer to the converted date/time structure (that is,
						the ``in_dtime_ptr`` parameter is returned).

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	DTIME_LocalToGMT
						DTIME_GetGMTToLocalSeconds

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2014 Michael L. Brock

	OUTPUT INDEX:	DTIME_GMTToLocal
						Date Functions:Date/Time Adjustment Functions:DTIME_GMTToLocal
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	DTIME_GMTToLocal

	PUBLISH NAME:	DTIME_GMTToLocal

	ENTRY CLASS	:	Date Functions:Date/Time Adjustment Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
DTIME *DTIME_GMTToLocal(DTIME *in_dtime_ptr)
#else
DTIME *DTIME_GMTToLocal(in_dtime_ptr)
DTIME *in_dtime_ptr;
#endif /* #ifndef NARGS */
{
	return(DTIME_AdjustSeconds(in_dtime_ptr,
		DTIME_GetGMTToLocalSeconds(in_dtime_ptr)));
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	DTIME_LocalToGMT

	SYNOPSIS		:	dtime_ptr = DTIME_LocalToGMT(in_dtime_ptr);

						DTIME *dtime_ptr;

						DTIME *in_dtime_ptr;

	DESCRIPTION	:	Converts a ''DTIME'' structure from local time to GMT/UTC
						time.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_dtime_ptr`` points to the structure of type
						''DTIME'' in which is the local time to be converted. The
						time resulting from the conversion to GMT/UTC time will
						be placed into this structure.

	RETURNS		:	A pointer to the converted date/time structure (that is,
						the ``in_dtime_ptr`` parameter is returned).

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	DTIME_GMTToLocal
						DTIME_GetGMTToLocalSeconds

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2014 Michael L. Brock

	OUTPUT INDEX:	DTIME_LocalToGMT
						Date Functions:Date/Time Adjustment Functions:DTIME_LocalToGMT
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	DTIME_LocalToGMT

	PUBLISH NAME:	DTIME_LocalToGMT

	ENTRY CLASS	:	Date Functions:Date/Time Adjustment Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
DTIME *DTIME_LocalToGMT(DTIME *in_dtime_ptr)
#else
DTIME *DTIME_LocalToGMT(in_dtime_ptr)
DTIME *in_dtime_ptr;
#endif /* #ifndef NARGS */
{
	return(DTIME_AdjustSeconds(in_dtime_ptr,
		-DTIME_GetGMTToLocalSeconds(in_dtime_ptr)));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	DTIME_AdjustHours

	SYNOPSIS		:	dtime_ptr = DTIME_AdjustHours(in_dtime_ptr, adj_hours);

						DTIME *dtime_ptr;

						DTIME *in_dtime_ptr;

						long   adj_hours;

	DESCRIPTION	:	Adjust a given date/time by the number of hours specified.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_dtime_ptr`` points to the structure of type
						''DTIME'' in which is the date/time to be adjusted. The
						time resulting from the adjustment will be placed into
						this structure.

						(.) ``adj_hours`` is the number of hours for which the
						``in_dtime_ptr`` parameter is to be adjusted. This
						value may be negative.

	RETURNS		:	A pointer to the adjusted date/time structure (that is,
						the ``in_dtime_ptr`` parameter is returned).

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	DTIME_AdjustMinutes
						DTIME_AdjustSeconds
						DTIME_AdjustMilliseconds

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2014 Michael L. Brock

	OUTPUT INDEX:	DTIME_AdjustHours
						Date Functions:Date/Time Adjustment Functions:DTIME_AdjustHours
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	DTIME_AdjustHours

	PUBLISH NAME:	DTIME_AdjustHours

	ENTRY CLASS	:	Date Functions:Date/Time Adjustment Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
DTIME *DTIME_AdjustHours(DTIME *in_dtime_ptr, long adj_hours)
#else
DTIME *DTIME_AdjustHours(in_dtime_ptr, adj_hours)
DTIME *in_dtime_ptr;
long   adj_hours;
#endif /* #ifndef NARGS */
{
	long adj_sign;
	long abs_hours;

	if (adj_hours) {
		adj_sign                   = (adj_hours < 0L) ? -1L : 1L;
		abs_hours                  = (adj_hours < 0L) ? (0L - adj_hours) :
			adj_hours;
		in_dtime_ptr->julian_date += ((JULIAN) ((abs_hours / 24L) * adj_sign));
		DTIME_GetAdjustedMilliseconds(in_dtime_ptr,
			((abs_hours % 24L) * 60L * 60L * 1000L) * adj_sign, in_dtime_ptr);
	}

	return(in_dtime_ptr);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	DTIME_AdjustMinutes

	SYNOPSIS		:	dtime_ptr = DTIME_AdjustMinutes(in_dtime_ptr, adj_minutes);

						DTIME *dtime_ptr;

						DTIME *in_dtime_ptr;

						long   adj_minutes;

	DESCRIPTION	:	Adjust a given date/time by the number of minutes specified.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_dtime_ptr`` points to the structure of type
						''DTIME'' in which is the date/time to be adjusted. The
						time resulting from the adjustment will be placed into
						this structure.

						(.) ``adj_minutes`` is the number of minutes for which the
						``in_dtime_ptr`` parameter is to be adjusted. This
						value may be negative.

	RETURNS		:	A pointer to the adjusted date/time structure (that is,
						the ``in_dtime_ptr`` parameter is returned).

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	DTIME_AdjustHours
						DTIME_AdjustSeconds
						DTIME_AdjustMilliseconds

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2014 Michael L. Brock

	OUTPUT INDEX:	DTIME_AdjustMinutes
						Date Functions:Date/Time Adjustment Functions:DTIME_AdjustMinutes
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	DTIME_AdjustMinutes

	PUBLISH NAME:	DTIME_AdjustMinutes

	ENTRY CLASS	:	Date Functions:Date/Time Adjustment Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
DTIME *DTIME_AdjustMinutes(DTIME *in_dtime_ptr, long adj_minutes)
#else
DTIME *DTIME_AdjustMinutes(in_dtime_ptr, adj_minutes)
DTIME *in_dtime_ptr;
long   adj_minutes;
#endif /* #ifndef NARGS */
{
	long adj_sign;
	long abs_minutes;

	if (adj_minutes) {
		adj_sign                   = (adj_minutes < 0L) ? -1L : 1L;
		abs_minutes                = (adj_minutes < 0L) ? (0L - adj_minutes) :
			adj_minutes;
		in_dtime_ptr->julian_date +=
			((JULIAN) ((abs_minutes / (24L * 60L)) * adj_sign));
		DTIME_GetAdjustedMilliseconds(in_dtime_ptr,
			((abs_minutes % (24L * 60L)) * 60L * 1000L) * adj_sign,
			in_dtime_ptr);
	}

	return(in_dtime_ptr);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	DTIME_AdjustSeconds

	SYNOPSIS		:	dtime_ptr = DTIME_AdjustSeconds(in_dtime_ptr, adj_seconds);

						DTIME *dtime_ptr;

						DTIME *in_dtime_ptr;

						long   adj_seconds;

	DESCRIPTION	:	Adjust a given date/time by the number of seconds specified.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_dtime_ptr`` points to the structure of type
						''DTIME'' in which is the date/time to be adjusted. The
						time resulting from the adjustment will be placed into
						this structure.

						(.) ``adj_seconds`` is the number of seconds for which the
						``in_dtime_ptr`` parameter is to be adjusted. This
						value may be negative.

	RETURNS		:	A pointer to the adjusted date/time structure (that is,
						the ``in_dtime_ptr`` parameter is returned).

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	DTIME_AdjustHours
						DTIME_AdjustMinutes
						DTIME_AdjustMilliseconds

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2014 Michael L. Brock

	OUTPUT INDEX:	DTIME_AdjustSeconds
						Date Functions:Date/Time Adjustment Functions:DTIME_AdjustSeconds
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	DTIME_AdjustSeconds

	PUBLISH NAME:	DTIME_AdjustSeconds

	ENTRY CLASS	:	Date Functions:Date/Time Adjustment Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
DTIME *DTIME_AdjustSeconds(DTIME *in_dtime_ptr, long adj_seconds)
#else
DTIME *DTIME_AdjustSeconds(in_dtime_ptr, adj_seconds)
DTIME *in_dtime_ptr;
long   adj_seconds;
#endif /* #ifndef NARGS */
{
	long adj_sign;
	long abs_seconds;

	if (adj_seconds) {
		adj_sign                   = (adj_seconds < 0L) ? -1L : 1L;
		abs_seconds                = (adj_seconds < 0L) ? (0L - adj_seconds) :
			adj_seconds;
		in_dtime_ptr->julian_date +=
			((JULIAN) ((abs_seconds / (24L * 60L * 60L)) * adj_sign));
		DTIME_GetAdjustedMilliseconds(in_dtime_ptr,
			((abs_seconds % (24L * 60L * 60L)) * 1000L) * adj_sign,
			in_dtime_ptr);
	}

	return(in_dtime_ptr);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	DTIME_AdjustMilliseconds

	SYNOPSIS		:	dtime_ptr = DTIME_AdjustMilliseconds(in_dtime_ptr,
							adj_milliseconds);

						DTIME *dtime_ptr;

						DTIME *in_dtime_ptr;

						long   adj_milliseconds;

	DESCRIPTION	:	Adjust a given date/time by the number of milliseconds
						specified.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_dtime_ptr`` points to the structure of type
						''DTIME'' in which is the date/time to be adjusted. The
						time resulting from the adjustment will be placed into
						this structure.

						(.) ``adj_milliseconds`` is the number of milliseconds for
						which the ``in_dtime_ptr`` parameter is to be adjusted.
						This value may be negative.

	RETURNS		:	A pointer to the adjusted date/time structure (that is,
						the ``in_dtime_ptr`` parameter is returned).

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	DTIME_AdjustHours
						DTIME_AdjustMinutes
						DTIME_AdjustSeconds
						DTIME_GetAdjustedMilliseconds

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2014 Michael L. Brock

	OUTPUT INDEX:	DTIME_AdjustMilliseconds
						Date Functions:Date/Time Adjustment Functions:DTIME_AdjustMilliseconds
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	DTIME_AdjustMilliseconds

	PUBLISH NAME:	DTIME_AdjustMilliseconds

	ENTRY CLASS	:	Date Functions:Date/Time Adjustment Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
DTIME *DTIME_AdjustMilliseconds(DTIME *in_dtime_ptr, long adj_milliseconds)
#else
DTIME *DTIME_AdjustMilliseconds(in_dtime_ptr, adj_milliseconds)
DTIME *in_dtime_ptr;
long   adj_milliseconds;
#endif /* #ifndef NARGS */
{
	return(DTIME_GetAdjustedMilliseconds(in_dtime_ptr, adj_milliseconds,
		in_dtime_ptr));
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	DTIME_GetAdjustedMilliseconds

	SYNOPSIS		:	dtime_ptr = DTIME_GetAdjustedMilliseconds(in_dtime_ptr,
							adj_milliseconds, out_dtime_ptr);

						DTIME       *dtime_ptr;

						const DTIME *in_dtime_ptr;

						long         adj_milliseconds;

						DTIME       *out_dtime_ptr;

	DESCRIPTION	:	Calculates a new date/time adjusted by the number of
						milliseconds specified.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_dtime_ptr`` points to the structure of type
						''DTIME'' in which is the date/time to be adjusted. The
						time resulting from the adjustment will be placed into
						this structure.

						(.) ``adj_milliseconds`` is the number of milliseconds for
						which the ``in_dtime_ptr`` parameter is to be adjusted.
						This value may be negative.

						(.) ``out_dtime_ptr`` points to a structure of type
						''DTIME'' into which the time resulting from the adjustment
						will be placed.

	RETURNS		:	A pointer to the adjusted date/time structure (that is,
						the ``out_dtime_ptr`` parameter is returned).

	NOTES			:	This function works correctly in the case where the
						``in_dtime_ptr`` parameter and the ``out_dtime_ptr``
						parameter point to the same ''DTIME'' structure.

	CAVEATS		:	

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2014 Michael L. Brock

	OUTPUT INDEX:	DTIME_GetAdjustedMilliseconds
						Date Functions:Date/Time Adjustment Functions:DTIME_GetAdjustedMilliseconds
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	DTIME_GetAdjustedMilliseconds

	PUBLISH NAME:	DTIME_GetAdjustedMilliseconds

	ENTRY CLASS	:	Date Functions:Date/Time Adjustment Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
DTIME *DTIME_GetAdjustedMilliseconds(const DTIME *in_dtime_ptr,
	long adj_milliseconds, DTIME *out_dtime_ptr)
#else
DTIME *DTIME_GetAdjustedMilliseconds(in_dtime_ptr, adj_milliseconds,
	out_dtime_ptr)
const DTIME *in_dtime_ptr;
long         adj_milliseconds;
DTIME       *out_dtime_ptr;
#endif /* #ifndef NARGS */
{
	DTIME tmp_dtime;
	long  tmp_milliseconds;

	out_dtime_ptr    = (out_dtime_ptr == NULL) ? &tmp_dtime : out_dtime_ptr;
	*out_dtime_ptr   = *in_dtime_ptr;
	tmp_milliseconds =
		((long) out_dtime_ptr->milliseconds) + adj_milliseconds;

	if (tmp_milliseconds >= (24L * 60L * 60L * 1000L)) {
		out_dtime_ptr->julian_date  += tmp_milliseconds /
			(24L * 60L * 60L * 1000L);
		out_dtime_ptr->milliseconds  =
			((unsigned long) (tmp_milliseconds % (24L * 60L * 60L * 1000L)));
	}
	else if (tmp_milliseconds < 0L) {
		out_dtime_ptr->julian_date  += (tmp_milliseconds /
			(24L * 60L * 60L * 1000L)) - 1;
		out_dtime_ptr->milliseconds  =
			((unsigned long) ((24L * 60L * 60L * 1000L) -
			((0L - tmp_milliseconds) % (24L * 60L * 60L * 1000L))));
	}
	else
		out_dtime_ptr->milliseconds = ((unsigned long) tmp_milliseconds);

	return(out_dtime_ptr);
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
	DTIME        tmp_dtime_3;
	char         buffer[100];

	fprintf(stderr, "Test routine for function 'DTIME_GMTToLocal()'\n");
	fprintf(stderr, "---- ------- --- -------- --------------------\n\n");

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		tmp_dtime_1.julian_date  = atoi(argv[count_1]);
		tmp_dtime_1.milliseconds = 0L;
		tmp_dtime_2              = tmp_dtime_1;
		DTIME_GMTToLocal(&tmp_dtime_2);
		tmp_dtime_3              = tmp_dtime_2;
		DTIME_LocalToGMT(&tmp_dtime_3);
		fprintf(stderr,
			"GMT Now  : JULIAN = %11ld, milliseconds = %10lu, Time = [%s]\n",
			tmp_dtime_1.julian_date, tmp_dtime_1.milliseconds,
			DTIME_FormatDate(&tmp_dtime_1, NULL, buffer));
		fprintf(stderr,
			"Local Now: JULIAN = %11ld, milliseconds = %10lu, Time = [%s]\n",
			tmp_dtime_2.julian_date, tmp_dtime_2.milliseconds,
			DTIME_FormatDate(&tmp_dtime_2, NULL, buffer));
		fprintf(stderr,
			"GMT Now  : JULIAN = %11ld, milliseconds = %10lu, Time = [%s]\n",
			tmp_dtime_3.julian_date, tmp_dtime_3.milliseconds,
			DTIME_FormatDate(&tmp_dtime_3, NULL, buffer));
		fprintf(stderr, "\n");
	}

	return(return_code);
}
/*	*********************************************************************** */

#endif /* #ifdef TEST_MAIN */

