/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Checks the validity of a DTIME structure.

	Revision History	:	1989-11-08 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1989 - 2018.
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

	NAME			:	DTIME_Ok

	SYNOPSIS		:	truth_flag = DTIME_Ok(dtime_ptr);

						int    truth_flag;

						DTIME *dtime_ptr;

	DESCRIPTION	:	Determines whether a structure of type ''DTIME'' is valid.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``dtime_ptr`` points to the ''DTIME'' structure which
						is to be validated.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DATFUNCS_TRUE'' if the structure is valid.

						(.) ''DATFUNCS_FALSE'' if the structure is not valid.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2018 Michael L. Brock

	OUTPUT INDEX:	DTIME_Ok
						Date Functions:Check Date Functions:DTIME_Ok
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	DTIME_Ok

	PUBLISH NAME:	DTIME_Ok

	ENTRY CLASS	:	Date Functions:Check Date Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DTIME_Ok(const DTIME *dtime_ptr)
#else
int DTIME_Ok(dtime_ptr)
const DTIME *dtime_ptr;
#endif /* #ifndef NARGS */
{
	return(((julianok(dtime_ptr->julian_date) == DATFUNCS_TRUE) &&
		(dtime_ptr->milliseconds < (60L * 60L * 24L * 1000L))) ?
		DATFUNCS_TRUE : DATFUNCS_FALSE);
}
/* *********************************************************************** */

