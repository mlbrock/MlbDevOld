/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Fixes an unsigned long date value year component so
								as to include the century.

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

#include "datfunci.h"

/*	*********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	fixulong

	SYNOPSIS		:	fixed_ulong_date = fixulong(in_ulong, implied_century,
							implied_year_break);

						unsigned long fixed_ulong_date;

						unsigned long in_ulong;

						int           implied_century;

						int           implied_year_break;

	DESCRIPTION	:	Fixes an unsigned long date value so as to include the
						century.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_ulong`` is the unsigned long date to be fixed.

						(.) ``implied_century`` is the century to be added to the
						date if the year is less than that specified by the
						``implied_year_break`` parameter.

						(.) ``implied_year_break`` specifies the fulcrum year at
						which the determination as to which century a date belongs.

						(-) Dates less than ``implied_year_break`` will be fixed so
						as to be in the century specified by ``implied_century``.

						(-) Dates greater than or equal to ``implied_year_break``
						will be fixed so as to be in the century before that
						specified by implied century.

   RETURNS     :  Returns from this function are as follow:

						(.) If no error occurs, the fixed unsigned long date is
						returned.

						(.) Otherwise, zero is returned.

						If the date already includes the century, the date is
						returned unchanged.

	NOTES			:	This function should check for the special case of
						February 29th as this could, in some cases, determine
						definitively the century to which a date belongs. This
						will be changed in a later release.

	CAVEATS		:	

	SEE ALSO		:	fixed_ulongok

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2015 Michael L. Brock

	OUTPUT INDEX:	fixulong
						Date Functions:Date/Time Adjustment Functions:fixulong
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	fixulong

	PUBLISH NAME:	fixulong

	ENTRY CLASS	:	Date Functions:Date/Time Adjustment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
unsigned long fixulong(unsigned long in_ulong, int implied_century,
	int implied_year_break)
#else
unsigned long fixulong(in_ulong, implied_century, implied_year_break)
unsigned long in_ulong;
int           implied_century;
int           implied_year_break;
#endif /* #ifndef NARGS */
{
	return((fixed_ulongok(in_ulong, implied_century, implied_year_break) !=
		DATFUNCS_TRUE) ? 0L : ((((unsigned long)
		fixyear(((int) ((in_ulong % 100000000L) / 10000L)), implied_century,
		implied_year_break)) * 10000L) + (in_ulong % 10000L)));
}
/* *********************************************************************** */

