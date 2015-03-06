/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Converts a JULIAN date to a human-readable Sybase
								date.

	Revision History	:	1993-12-02 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	*********************************************************************** */
/*	*********************************************************************** */
/* 	Necessary include files . . .														*/
/*	*********************************************************************** */

#include <stdio.h>
#include <string.h>

#include <strfuncs.h>

#include "datfunci.h"

/*	*********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	jultosyb

	SYNOPSIS		:	return_ptr = jultosyb(julian_date, sybase_date);

						char   *return_ptr;

						JULIAN  julian_date;

						char   *sybase_date;

	DESCRIPTION	:	Converts a ''JULIAN'' date to its character string date
						equivalent acceptable to Sybase.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``julian_date`` is the ''JULIAN'' date to be converted
						by this function.

						(.) ``sybase_date`` is a pointer to ''char'' into which
						this function will place the string equivalent of
						``julian_date``.

   RETURNS     :  Returns a pointer to the string equivalent of the
						``julian_date`` parameter. That is, this function returns
						the ``sybase_date`` parameter.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2015 Michael L. Brock

	OUTPUT INDEX:	jultosyb
						Date Functions:Conversion Functions:jultosyb
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	jultosyb

	PUBLISH NAME:	jultosyb

	ENTRY CLASS	:	Date Functions:Conversion Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *jultosyb(JULIAN julian_date, char *sybase_date)
#else
char *jultosyb(julian_date, sybase_date)
JULIAN  julian_date;
char   *sybase_date;
#endif /* #ifndef NARGS */
{
	JDATE temp_date;
	char  buffer[SIZE_OF_SYBASE_DATE + 1];

	jultodat(julian_date, &temp_date);
	sprintf(sybase_date, "%s %02u %04u 00:00:00.000",
		initcaps(strcpy(buffer, getmname(temp_date.month, buffer,
		JDATE_NAME_TYPE_SHORT))), temp_date.day, temp_date.year);

	return(sybase_date);
}
/*	*********************************************************************** */

