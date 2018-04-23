/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets the seconds represented by a millisecond count.

	Revision History	:	1994-01-24 --- Creation.
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

	NAME			:	getsecond

	SYNOPSIS		:	seconds_of_minute = getsecond(in_milliseconds);

						int           seconds_of_minute;

						unsigned long in_milliseconds;

	DESCRIPTION	:	Determines the seconds of an minute represented by a
						millisecond count.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_milliseconds`` is the millisecond count upon which
						the calculation is to be based.

   RETURNS     :  The seconds of a minute represented by the
						``in_milliseconds`` parameter. It will fall in the
						inclusive range of 0 to 59.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	getsecond
						Date Functions:Get Date/Time Component Functions:getsecond
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	getsecond

	PUBLISH NAME:	getsecond

	ENTRY CLASS	:	Date Functions:Get Date/Time Component Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int getsecond(unsigned long in_milliseconds)
#else
int getsecond(in_milliseconds)
unsigned long in_milliseconds;
#endif /* #ifndef NARGS */
{
	return(((int) ((in_milliseconds % (60L * 1000L)) / 1000L)));
}
/* *********************************************************************** */

