/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Determines whether a year is a leap year.

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

#include "datfunci.h"

/*	*********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	isleapyr

	SYNOPSIS		:	truth_flag = isleapyr(in_year);

						int truth_flag;

						int in_year;

	DESCRIPTION	:	Determines whether a year is a leap year.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_year`` is value to be checked by this function
						to determine whether it is a leap year.

   RETURNS     :  Returns from this function are as follow:

						(.) The manifest constant ''DATFUNCS_TRUE'' if ``in_year``
						is valid.

						(.) Otherwise, the manifest constant ''DATFUNCS_FALSE'' is
						returned.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	yearok
						fixed_yearok

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2014 Michael L. Brock

	OUTPUT INDEX:	isleapyr
						Date Functions:isleapyr
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	isleapyr

	PUBLISH NAME:	isleapyr

EOH */
/* *********************************************************************** */
#ifndef NARGS
int isleapyr(int in_year)
#else
int isleapyr(in_year)
int in_year;
#endif /* #ifndef NARGS */
{
	in_year = (in_year < 50) ? in_year + 1900 : in_year;

	return((((!(in_year % 4)) && (in_year <= DATFUNCS_GREGORIAN_YEAR)) ||
		((!(in_year % 4)) && (in_year % 100)) ||
		((!(in_year % 4)) && (!(in_year % 400)))) ? 1 : 0);
}
/*	*********************************************************************** */

