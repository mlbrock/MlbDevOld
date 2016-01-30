/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Checks an hour value for validity.

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

	NAME			:	hourok

	SYNOPSIS		:	truth_flag = hourok(in_hour);

						int truth_flag;

						int in_hour;

	DESCRIPTION	:	Checks an hour value for validity.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_hour`` is the hour value to be checked by this
						function.

						(-) Valid ``in_hour`` values are in the range ''0'' to
						''23'', inclusive.

   RETURNS     :  Returns from this function are as follow:

						(.) The manifest constant ''DATFUNCS_TRUE'' if ``in_hour``
						is valid.

						(.) Otherwise, the manifest constant ''DATFUNCS_FALSE'' is
						returned.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	yearok
						monthok
						minuteok
						secondok
						millisecondok

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2016 Michael L. Brock

	OUTPUT INDEX:	hourok
						Date Functions:Check Date Functions:hourok
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	hourok

	PUBLISH NAME:	hourok

	ENTRY CLASS	:	Date Functions:Check Date Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int hourok(int in_hour)
#else
int hourok(in_hour)
int in_hour;
#endif /* #ifndef NARGS */
{
	return(((in_hour < 0) || (in_hour > 23)) ? DATFUNCS_FALSE : DATFUNCS_TRUE);
}
/* *********************************************************************** */

