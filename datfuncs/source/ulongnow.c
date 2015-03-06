/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Returns the current system date as a unsigned long.

	Revision History	:	1995-01-12 --- Creation.
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

#include "datfunci.h"

/*	*********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	ulongnow

	SYNOPSIS		:	ulong_date = ulongnow();

						unsigned long ulong_date;

	DESCRIPTION	:	Returns the current GMT/UTC date as an ``unsigned long``.

   PARAMETERS  :  None.

   RETURNS     :  The current GMT/UTC date as an ``unsigned long``.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	ulongnow_local

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2015 Michael L. Brock

	OUTPUT INDEX:	ulongnow
						Date Functions:Current Date Functions:ulongnow
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	ulongnow

	PUBLISH NAME:	ulongnow

	ENTRY CLASS	:	Date Functions:Current Date Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
unsigned long ulongnow(void)
#else
unsigned long ulongnow()
#endif /* #ifndef NARGS */
{
	return(SDTIF_GetTime_ulong_GMT());
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	ulongnow_local

	SYNOPSIS		:	ulong_date = ulongnow_local();

						unsigned long ulong_date;

	DESCRIPTION	:	Gets the current local date as an ``unsigned long``.

   PARAMETERS  :  None.

   RETURNS     :  The current local date as an ``unsigned long``.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	ulongnow

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2015 Michael L. Brock

	OUTPUT INDEX:	ulongnow_local
						Date Functions:Current Date Functions:ulongnow_local
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	ulongnow_local

	PUBLISH NAME:	ulongnow_local

	ENTRY CLASS	:	Date Functions:Current Date Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
unsigned long ulongnow_local(void)
#else
unsigned long ulongnow_local()
#endif /* #ifndef NARGS */
{
	return(SDTIF_GetTime_ulong());
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
	int return_code = DATFUNCS_SUCCESS;

	fprintf(stderr, "Test routine for function 'ulongnow()'\n");
	fprintf(stderr, "Test routine for function 'ulongnow_local()'\n");
	fprintf(stderr, "---- ------- --- -------- ------------------\n\n");

	printf("GMT Now  : unsigned long = %11ld\n", ulongnow());
	printf("Local Now: unsigned long = %11ld\n", ulongnow_local());
	printf("\n");

	return(return_code);
}
/*	*********************************************************************** */

#endif /* #ifdef TEST_MAIN */

