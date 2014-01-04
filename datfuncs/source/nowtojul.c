/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Returns the current system date as a JULIAN.

	Revision History	:	1989-11-08 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1989 - 2014.
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

	NAME			:	nowtojul

	SYNOPSIS		:	julian_date = nowtojul();

						JULIAN julian_date;

	DESCRIPTION	:	Gets the current GMT/UTC and time as an JULIAN.

   PARAMETERS  :  None.

   RETURNS     :  The current GMT/UTC date as an JULIAN.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	nowtojul_local

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2014 Michael L. Brock

	OUTPUT INDEX:	nowtojul
						Date Functions:Current Date Functions:nowtojul
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	nowtojul

	PUBLISH NAME:	nowtojul

	ENTRY CLASS	:	Date Functions:Current Date Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
JULIAN nowtojul(void)
#else
JULIAN nowtojul()
#endif /* #ifndef NARGS */
{
	return(DATFUNCS_UNIX_EPOCH_JULIAN +
		(((JULIAN) time(NULL)) / (60L * 60L * 24L)));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	nowtojul_local

	SYNOPSIS		:	julian_date = nowtojul_local();

						JULIAN julian_date;

	DESCRIPTION	:	Gets the current local date and time as an JULIAN.

   PARAMETERS  :  None.

   RETURNS     :  The current local date as an JULIAN.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	nowtojul

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2014 Michael L. Brock

	OUTPUT INDEX:	nowtojul_local
						Date Functions:Current Date Functions:nowtojul_local
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	nowtojul_local

	PUBLISH NAME:	nowtojul_local

	ENTRY CLASS	:	Date Functions:Current Date Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
JULIAN nowtojul_local(void)
#else
JULIAN nowtojul_local()
#endif /* #ifndef NARGS */
{
	DTIME tmp_dtime;

	return(DTIME_NowLocal(&tmp_dtime)->julian_date);
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
	int    return_code   = DATFUNCS_SUCCESS;
	JULIAN tmp_julian_1;
	JULIAN tmp_julian_2;
	char   buffer[100];

	fprintf(stderr, "Test routine for function 'nowtojul()'\n");
	fprintf(stderr, "Test routine for function 'nowtojul_local()'\n\n");

	tmp_julian_1 = nowtojul();
	tmp_julian_2 = nowtojul_local();

	printf("GMT Now  : JULIAN = %11ld = [%s]\n", tmp_julian_1,
		jultostr(tmp_julian_1, buffer));
	printf("Local Now: JULIAN = %11ld = [%s]\n", tmp_julian_2,
		jultostr(tmp_julian_2, buffer));
	printf("\n");

	return(return_code);
}
/*	*********************************************************************** */

#endif /* #ifdef TEST_MAIN */

