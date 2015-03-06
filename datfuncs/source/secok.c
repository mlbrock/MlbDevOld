/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Checks a second value for validity.

	Revision History	:	1994-02-06 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2015.
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

	NAME			:	secondok

	SYNOPSIS		:	truth_flag = secondok(in_second);

						int truth_flag;

						int in_second;

	DESCRIPTION	:	Checks a second value for validity.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_second`` is the seconds value to be checked by this
						function.

						(-) Valid ``in_second`` values are in the range ''0'' to
						''59'', inclusive.

   RETURNS     :  Returns from this function are as follow:

						(.) The manifest constant ''DATFUNCS_TRUE'' if ``in_second``
						is valid.

						(.) Otherwise, the manifest constant ''DATFUNCS_FALSE'' is
						returned.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	yearok
						monthok
						hourok
						minuteok
						millisecondok

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2015 Michael L. Brock

	OUTPUT INDEX:	secondok
						Date Functions:Check Date Functions:secondok
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	secondok

	PUBLISH NAME:	secondok

	ENTRY CLASS	:	Date Functions:Check Date Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int secondok(int in_second)
#else
int secondok(in_second)
int in_second;
#endif /* #ifndef NARGS */
{
	return(((in_second < 0) || (in_second > 59)) ? DATFUNCS_FALSE :
		DATFUNCS_TRUE);
}
/* *********************************************************************** */

