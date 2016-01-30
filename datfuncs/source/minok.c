/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Checks a minute value for validity.

	Revision History	:	1994-02-06 --- Creation.
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

	NAME			:	minuteok

	SYNOPSIS		:	truth_flag = minuteok(in_minute);

						int truth_flag;

						int in_minute;

	DESCRIPTION	:	Checks a minute value for validity.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_minute`` is the minute value to be checked by
						this function.

						(-) Valid ``in_minute`` values are in the range ''0'' to
						''59'', inclusive.

   RETURNS     :  Returns from this function are as follow:

						(.) The manifest constant ''DATFUNCS_TRUE'' if ``in_minute``
						is valid.

						(.) Otherwise, the manifest constant ''DATFUNCS_FALSE'' is
						returned.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	yearok
						monthok
						hourok
						secondok
						millisecondok

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2016 Michael L. Brock

	OUTPUT INDEX:	minuteok
						Date Functions:Check Date Functions:minuteok
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	minuteok

	PUBLISH NAME:	minuteok

	ENTRY CLASS	:	Date Functions:Check Date Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int minuteok(int in_minute)
#else
int minuteok(in_minute)
int in_minute;
#endif /* #ifndef NARGS */
{
	return(((in_minute < 0) || (in_minute > 59)) ? DATFUNCS_FALSE :
		DATFUNCS_TRUE);
}
/* *********************************************************************** */

