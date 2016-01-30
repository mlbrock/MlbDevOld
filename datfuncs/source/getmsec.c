/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets the milliseconds represented by a millisecond
								count.

	Revision History	:	1994-01-24 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2016.
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

	NAME			:	getmillisecond

	SYNOPSIS		:	milliseconds_of_second = getmillisecond(in_milliseconds);

						int           milliseconds_of_second;

						unsigned long in_milliseconds;

	DESCRIPTION	:	Determines the milliseconds of a second represented by a
						millisecond count.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_milliseconds`` is the millisecond count upon which
						the calculation is to be based.

	RETURNS     :  The milliseconds (thousandths of a second) represented by
						the ``in_milliseconds`` parameter. 	It will fall in the
						inclusive range of 0 to 999.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2016 Michael L. Brock

	OUTPUT INDEX:	getmillisecond
						Date Functions:Get Date/Time Component Functions:getmillisecond
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	getmillisecond

	PUBLISH NAME:	getmillisecond

	ENTRY CLASS	:	Date Functions:Get Date/Time Component Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int getmillisecond(unsigned long in_milliseconds)
#else
int getmillisecond(in_milliseconds)
unsigned long in_milliseconds;
#endif /* #ifndef NARGS */
{
	return(((int) (in_milliseconds % 1000L)));
}
/* *********************************************************************** */

