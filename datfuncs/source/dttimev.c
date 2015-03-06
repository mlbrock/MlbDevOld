/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Converts a struct timeval date/time to a DTIME
								structure.

	Revision History	:	1989-11-08 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1989 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	*********************************************************************** */
/*	*********************************************************************** */
/* 	Necessary include files . . .														*/
/*	*********************************************************************** */

#include <stdlib.h>

#include "datfunci.h"

/*	*********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	DTIME_timevalToDate

	SYNOPSIS		:	dtime_ptr = DTIME_timevalToDate(in_timeval_ptr,
							out_date_ptr);

						DTIME                *dtime_ptr;

						const struct timeval *in_timeval_ptr;

						DTIME                *out_date_ptr;

	DESCRIPTION	:	Converts a ''struct timeval'' to a ''DTIME''.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_timeval_ptr`` is a pointer to ''struct timeval''
						to be converted by this function.

						(.) ``out_date_ptr`` is a pointer to a ''DTIME'' structure
						into which this function is to place the converted date/time
						value.

   RETURNS     :  Returns a pointer to the converted ''DTIME'' structure
						(that is, the parameter ``out_date_ptr``).

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	DTIME_NowUTC
						DTIME_NowGMT

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2015 Michael L. Brock

	OUTPUT INDEX:	DTIME_timevalToDate
						Date Functions:Conversion Functions:DTIME_timevalToDate
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	DTIME_timevalToDate

	PUBLISH NAME:	DTIME_timevalToDate

	ENTRY CLASS	:	Date Functions:Conversion Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
DTIME *DTIME_timevalToDate(const struct timeval *in_timeval_ptr,
	DTIME *out_date_ptr)
#else
DTIME *DTIME_timevalToDate(in_timeval_ptr, out_date_ptr)
const struct timeval *in_timeval_ptr;
DTIME                *out_date_ptr;
#endif /* #ifndef NARGS */
{
	DTIME           tmp_dtime;
	struct timeval  tmp_timeval;

	out_date_ptr = (out_date_ptr == NULL) ? &tmp_dtime : out_date_ptr;

	if (in_timeval_ptr == NULL)
		in_timeval_ptr = SDTIF_GetTimeUSecs(&tmp_timeval);

	out_date_ptr->julian_date  = DATFUNCS_UNIX_EPOCH_JULIAN +
		(((JULIAN) in_timeval_ptr->tv_sec) / (60L * 60L * 24L));
	out_date_ptr->milliseconds = ((unsigned long)
		(((in_timeval_ptr->tv_sec % (60L * 60L * 24L)) * 1000L) +
		(in_timeval_ptr->tv_usec / 1000L)));

	return(out_date_ptr);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>

COMPAT_FN_DECL(int main, (void));

int main()
{
	int             return_code   = DATFUNCS_SUCCESS;
	struct timeval  tmp_timeval;
	DTIME           tmp_dtime;
	char            buffer[100];

	fprintf(stderr, "Test routine for function 'DTIME_timevalToDate()'\n\n");

	SDTIF_GetTimeUSecs(&tmp_timeval);
	DTIME_timevalToDate(&tmp_timeval, &tmp_dtime);

	printf("SDTIF_GetTimeUsecs: %11ld / %11ld\n",
		tmp_timeval.tv_sec, tmp_timeval.tv_usec);
	printf("DTIME             : %11ld / %11lu\n",
		tmp_dtime.julian_date, tmp_dtime.milliseconds);
	printf("STRING            : %s\n",
		DTIME_FormatDate(&tmp_dtime, NULL, buffer));

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

