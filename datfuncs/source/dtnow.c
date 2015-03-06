/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets the current date/time value as a DTIME
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

	NAME			:	DTIME_NowUTC

	SYNOPSIS		:	dtime_ptr = DTIME_NowUTC(in_dtime_ptr)

						DTIME *dtime_ptr;

						DTIME *in_dtime_ptr;

	DESCRIPTION	:	Gets the current GMT/UTC date and time into a structure of
						type ''DTIME''

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_dtime_ptr`` points to the structure of type
						''DTIME'' into which the current date and time are to be
						placed.

   RETURNS     :  A pointer to the current date and time.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	DTIME_NowGMT
						DTIME_NowLocal
						DTIME_GMTToLocal

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2015 Michael L. Brock

	OUTPUT INDEX:	DTIME_NowUTC
						Date Functions:Current Date Functions:DTIME_NowUTC
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	DTIME_NowUTC

	PUBLISH NAME:	DTIME_NowUTC

	ENTRY CLASS	:	Date Functions:Current Date Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
DTIME *DTIME_NowUTC(DTIME *in_dtime_ptr)
#else
DTIME *DTIME_NowUTC(in_dtime_ptr)
DTIME *in_dtime_ptr;
#endif /* #ifndef NARGS */
{
	return(DTIME_timevalToDate(NULL, in_dtime_ptr));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	DTIME_NowGMT

	SYNOPSIS		:	dtime_ptr = DTIME_NowGMT(in_dtime_ptr)

						DTIME *dtime_ptr;

						DTIME *in_dtime_ptr;

	DESCRIPTION	:	Gets the current GMT/UTC date and time into a structure of
						type ''DTIME''

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_dtime_ptr`` points to the structure of type
						''DTIME'' into which the current date and time are to be
						placed.

   RETURNS     :  A pointer to the current date and time.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	DTIME_NowUTC
						DTIME_NowLocal
						DTIME_GMTToLocal

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2015 Michael L. Brock

	OUTPUT INDEX:	DTIME_NowGMT
						Date Functions:Current Date Functions:DTIME_NowGMT
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	DTIME_NowGMT

	PUBLISH NAME:	DTIME_NowGMT

	ENTRY CLASS	:	Date Functions:Current Date Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
DTIME *DTIME_NowGMT(DTIME *in_dtime_ptr)
#else
DTIME *DTIME_NowGMT(in_dtime_ptr)
DTIME *in_dtime_ptr;
#endif /* #ifndef NARGS */
{
	return(DTIME_timevalToDate(NULL, in_dtime_ptr));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	DTIME_NowLocal

	SYNOPSIS		:	dtime_ptr = DTIME_NowLocal(in_dtime_ptr)

						DTIME *dtime_ptr;

						DTIME *in_dtime_ptr;

	DESCRIPTION	:	Gets the current local date and time into a structure of
						type ''DTIME''.

						This behavior contrasts with that of the function
						``DTIME_Now`` which gets the current GMT/UTC date and time.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_dtime_ptr`` points to the structure of type
						''DTIME'' into which the current date and time are to be
						placed.

   RETURNS     :  A pointer to the current date and time.

	NOTES			:	

	CAVEATS		:	This function assumes that the structure of type ''DTIME''
						to which the ``in_dtime_ptr`` points contains the GMT/UTC
						date and time.

	SEE ALSO		:	DTIME_NowGMT
						DTIME_NowUTC
						DTIME_GMTToLocal

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2015 Michael L. Brock

	OUTPUT INDEX:	DTIME_NowLocal
						Date Functions:Current Date Functions:DTIME_NowLocal
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	DTIME_NowLocal

	PUBLISH NAME:	DTIME_NowLocal

	ENTRY CLASS	:	Date Functions:Current Date Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
DTIME *DTIME_NowLocal(DTIME *in_dtime_ptr)
#else
DTIME *DTIME_NowLocal(in_dtime_ptr)
DTIME *in_dtime_ptr;
#endif /* #ifndef NARGS */
{
	DTIME tmp_dtime;

	in_dtime_ptr = (in_dtime_ptr == NULL) ? &tmp_dtime : in_dtime_ptr;

	return(DTIME_GMTToLocal(DTIME_timevalToDate(NULL, in_dtime_ptr)));
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>

COMPAT_FN_DECL(int main, (void));

/*	*********************************************************************** */
/*	*********************************************************************** */
/*	*********************************************************************** */
int main()
{
	int   return_code = DATFUNCS_SUCCESS;
	DTIME tmp_dtime_1;
	DTIME tmp_dtime_2;
	char  buffer[100];

	fprintf(stderr, "Test routine for function 'DTIME_NowUTC()'\n");
	fprintf(stderr, "Test routine for function 'DTIME_NowLocal()'\n");
	fprintf(stderr, "---- ------- --- -------- ------------------\n\n");

	DTIME_NowUTC(&tmp_dtime_1);
	DTIME_NowLocal(&tmp_dtime_2);

	fprintf(stderr,
"GMT Now  : JULIAN = %11ld, milliseconds = %10lu\n           Time = [%s]\n",
		tmp_dtime_1.julian_date, tmp_dtime_1.milliseconds,
		DTIME_FormatDate(&tmp_dtime_1, NULL, buffer));
	fprintf(stderr,
"Local Now: JULIAN = %11ld, milliseconds = %10lu\n           Time = [%s]\n",
		tmp_dtime_2.julian_date, tmp_dtime_2.milliseconds,
		DTIME_FormatDate(&tmp_dtime_2, NULL, buffer));
	fprintf(stderr, "\n");

	return(return_code);
}
/*	*********************************************************************** */

#endif /* #ifdef TEST_MAIN */

