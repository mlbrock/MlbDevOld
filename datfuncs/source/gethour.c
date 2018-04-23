/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets the hours represented by a millisecond count.

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

	NAME			:	gethour

	SYNOPSIS		:	hour_of_day = gethour(in_milliseconds);

						int           hour_of_day;

						unsigned long in_milliseconds;

	DESCRIPTION	:	Determines the hours of a day represented by a
						millisecond count.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_milliseconds`` is the millisecond count upon which
						the calculation is to be based.

   RETURNS     :  The hour of the day represented by the ``in_milliseconds``
						parameter. It will fall in the inclusive range of 0 to 23.

	NOTES			:	The hour of the day is on a 24-hour clock basis.

	CAVEATS		:	

	SEE ALSO		:	gethour12
						gethour24

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	gethour
						Date Functions:Get Date/Time Component Functions:gethour
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	gethour

	PUBLISH NAME:	gethour

	ENTRY CLASS	:	Date Functions:Get Date/Time Component Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int gethour(unsigned long in_milliseconds)
#else
int gethour(in_milliseconds)
unsigned long in_milliseconds;
#endif /* #ifndef NARGS */
{
	return(((int) ((in_milliseconds % (60L * 60L * 24L * 1000L)) /
		(60L * 60L * 1000L))));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	gethour12

	SYNOPSIS		:	hour_of_day = gethour12(in_milliseconds);

						int           hour_of_day;

						unsigned long in_milliseconds;

	DESCRIPTION	:	Determines the hours of a day represented by a
						millisecond count on a 12-hour clock basis.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_milliseconds`` is the millisecond count upon which
						the calculation is to be based.

   RETURNS     :  The hour of the day represented by the ``in_milliseconds``
						parameter. It will fall in the inclusive range of 0 to 12.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	gethour
						gethour24

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	gethour12
						Date Functions:Get Date/Time Component Functions:gethour12
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	gethour12

	PUBLISH NAME:	gethour12

	ENTRY CLASS	:	Date Functions:Get Date/Time Component Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int gethour12(unsigned long in_milliseconds)
#else
int gethour12(in_milliseconds)
unsigned long in_milliseconds;
#endif /* #ifndef NARGS */
{
	int tmp_hour;

	return(((tmp_hour = gethour(in_milliseconds)) <= 12) ? tmp_hour :
		(tmp_hour - 12));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	gethour24

	SYNOPSIS		:	hour_of_day = gethour24(in_milliseconds);

						int           hour_of_day;

						unsigned long in_milliseconds;

	DESCRIPTION	:	Determines the hours of a day represented by a
						millisecond count on a 24-hour clock basis.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_milliseconds`` is the millisecond count upon which
						the calculation is to be based.

   RETURNS     :  The hour of the day represented by the ``in_milliseconds``
						parameter. It will fall in the inclusive range of 0 to 23.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	gethour
						gethour12

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	gethour24
						Date Functions:Get Date/Time Component Functions:gethour24
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	gethour24

	PUBLISH NAME:	gethour24

	ENTRY CLASS	:	Date Functions:Get Date/Time Component Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int gethour24(unsigned long in_milliseconds)
#else
int gethour24(in_milliseconds)
unsigned long in_milliseconds;
#endif /* #ifndef NARGS */
{
	return(gethour(in_milliseconds));
}
/* *********************************************************************** */

