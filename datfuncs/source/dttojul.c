/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Converts a DTIME date/time to a JULIAN date.

	Revision History	:	1994-12-08 --- Creation.
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

#include "datfunci.h"

/*	*********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	dttojul

	SYNOPSIS		:	julian_date = dttojul(in_dtime_ptr);

						JULIAN       julian_date;

						const DTIME *in_dtime_ptr;

	DESCRIPTION	:	Converts a ''DTIME'' date/time to a ''JULIAN'' date.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_dtime_ptr`` points to the structure of type
						''DTIME'' in which is the date/time to be converted.

	RETURNS		:	The converted ''JULIAN'' date.

	NOTES			:	The effective time-of-day of the converted ''JULIAN''
						structure is ''00:00:00.000''.

	CAVEATS		:	

	SEE ALSO		:	jultodt

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2014 Michael L. Brock

	OUTPUT INDEX:	dttojul
						Date Functions:Conversion Functions:dttojul
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	dttojul

	PUBLISH NAME:	dttojul

	ENTRY CLASS	:	Date Functions:Conversion Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
JULIAN dttojul(const DTIME *in_dtime_ptr)
#else
JULIAN dttojul(in_dtime_ptr)
const DTIME *in_dtime_ptr;
#endif /* #ifndef NARGS */
{
	return(in_dtime_ptr->julian_date);
}
/*	*********************************************************************** */

