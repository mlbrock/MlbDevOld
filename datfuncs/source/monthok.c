/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Checks a month value for validity.

	Revision History	:	1994-02-06 --- Creation.
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

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	monthok

	SYNOPSIS		:	truth_flag = monthok(in_month);

						int truth_flag;

						int in_month;

	DESCRIPTION	:	Checks a month value for validity.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_month`` is the month value to be checked by this
						function.

						(-) Valid ``in_month`` values are in the range ''1'' to
						''12'', inclusive.

   RETURNS     :  Returns from this function are as follow:

						(.) The manifest constant ''DATFUNCS_TRUE'' if ``in_month``
						is valid.

						(.) Otherwise, the manifest constant ''DATFUNCS_FALSE'' is
						returned.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	yearok
						hourok
						minuteok
						secondok
						millisecondok

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2014 Michael L. Brock

	OUTPUT INDEX:	monthok
						Date Functions:Check Date Functions:monthok
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	monthok

	PUBLISH NAME:	monthok

	ENTRY CLASS	:	Date Functions:Check Date Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int monthok(int in_month)
#else
int monthok(in_month)
int in_month;
#endif /* #ifndef NARGS */
{
	return(((in_month < 1) || (in_month > 12)) ? DATFUNCS_FALSE :
		DATFUNCS_TRUE);
}
/* *********************************************************************** */

