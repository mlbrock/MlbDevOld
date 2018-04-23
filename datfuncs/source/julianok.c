/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Checks a JULIAN date value for validity.

	Revision History	:	1994-02-06 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2018.
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

	NAME			:	julianok

	SYNOPSIS		:	truth_flag = julianok(in_julian);

						int    truth_value;

						JULIAN in_julian;

	DESCRIPTION	:	Determines whether a JULIAN date is valid.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_julian`` is the JULIAN date to be validated.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DATFUNCS_TRUE'' if the JULIAN is valid.

						(.) ''DATFUNCS_FALSE'' if the JULIAN is not valid.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	julianok
						Date Functions:Check Date Functions:julianok
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	julianok

	PUBLISH NAME:	julianok

	ENTRY CLASS	:	Date Functions:Check Date Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int julianok(JULIAN in_julian)
#else
int julianok(in_julian)
JULIAN in_julian;
#endif /* #ifndef NARGS */
{
	return(((in_julian >= DATFUNCS_MIN_JULIAN) &&
		(in_julian <= DATFUNCS_MAX_JULIAN)) ? DATFUNCS_TRUE : DATFUNCS_FALSE);
}
/* *********************************************************************** */

