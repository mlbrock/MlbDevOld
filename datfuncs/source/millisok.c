/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Checks a millisecond value for validity.

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

	NAME			:	millisecondok

	SYNOPSIS		:	truth_flag = millisecondok(in_millisecond);

						int truth_flag;

						int in_millisecond;

	DESCRIPTION	:	Checks a millisecond value for validity.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_millisecond`` is the millisecond value to be
						checked by this function.

						(-) Valid ``in_millisecond`` values are in the range ''0''
						to ''999'', inclusive.

   RETURNS     :  Returns from this function are as follow:

						(.) The manifest constant ''DATFUNCS_TRUE'' if
						``in_millisecond`` is valid.

						(.) Otherwise, the manifest constant ''DATFUNCS_FALSE'' is
						returned.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	yearok
						monthok
						hourok
						minuteok
						secondok

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2015 Michael L. Brock

	OUTPUT INDEX:	millisecondok
						Date Functions:Check Date Functions:millisecondok
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	millisecondok

	PUBLISH NAME:	millisecondok

	ENTRY CLASS	:	Date Functions:Check Date Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int millisecondok(int in_millisecond)
#else
int millisecondok(in_millisecond)
int in_millisecond;
#endif /* #ifndef NARGS */
{
	return(((in_millisecond < 0) || (in_millisecond > 999)) ?
		DATFUNCS_FALSE : DATFUNCS_TRUE);
}
/* *********************************************************************** */

