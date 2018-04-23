/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Converts JULIAN date to a DTIME date/time.

	Revision History	:	1994-12-08 --- Creation.
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

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	jultodt

	SYNOPSIS		:	dtime_ptr = jultodt(in_julian, out_dtime_ptr);

						DTIME  *dtime_ptr;

						JULIAN  in_julian;

						DTIME  *out_dtime_ptr;

	DESCRIPTION	:	Converts a ''JULIAN'' date to a ''DTIME'' date/time.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_julian`` is the ''JULIAN'' date which contains
						the date to be converted.

						(.) ``out_dtime_ptr`` points to the structure of type
						''DTIME'' into which the date/time resulting from the
						conversion will be placed.

	RETURNS		:	A pointer to the converted date/time structure (that is,
						the ``out_dtime_ptr`` parameter is returned).

	NOTES			:	The effective time-of-day of the converted ''DTIME''
						structure is ''00:00:00.000''.

	CAVEATS		:	

	SEE ALSO		:	dttojul

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	jultodt
						Date Functions:Conversion Functions:jultodt
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	jultodt

	PUBLISH NAME:	jultodt

	ENTRY CLASS	:	Date Functions:Conversion Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
DTIME *jultodt(JULIAN in_julian, DTIME *out_dtime_ptr)
#else
DTIME *jultodt(in_julian, out_dtime_ptr)
JULIAN  in_julian;
DTIME  *out_dtime_ptr;
#endif /* #ifndef NARGS */
{
	out_dtime_ptr->julian_date  = in_julian;
	out_dtime_ptr->milliseconds = 0L;

	return(out_dtime_ptr);
}
/*	*********************************************************************** */

