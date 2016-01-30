/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Converts a JULIAN date to an Ingres date.

	Revision History	:	1989-11-08 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1989 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	*********************************************************************** */
/*	*********************************************************************** */
/* 	Necessary include files . . .														*/
/*	*********************************************************************** */

#include <memory.h>
#include <stdio.h>
#include <string.h>

#include <strfuncs.h>

#include "datfunci.h"

/*	*********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	jultoing

	SYNOPSIS		:	ingres_date_ptr = jultoing(julian_date, ingres_date);

						char   *ingres_date_ptr;

						JULIAN  julian_date;

						char   *ingres_date;

	DESCRIPTION	:	Converts a ''JULIAN'' date to an Ingres date.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_julian`` is the ''JULIAN'' date to be converted
						by this function into an Ingres date.

						(.) ``ingres_date`` is a pointer to the string into which
						this function will place the Ingres date value equivalent of
						the ``in_julian`` parameter.

   RETURNS     :  Returns a pointer to the converted Ingres date (that is,
						the parameter ``ingres_date``).

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	ingtojul

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2016 Michael L. Brock

	OUTPUT INDEX:	jultoing
						Date Functions:Conversion Functions:jultoing
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	jultoing

	PUBLISH NAME:	jultoing

	ENTRY CLASS	:	Date Functions:Conversion Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *jultoing(JULIAN julian_date, char *ingres_date)
#else
char *jultoing(julian_date, ingres_date)
JULIAN  julian_date;
char   *ingres_date;
#endif /* #ifndef NARGS */
{
	JDATE temp_date;
	char  buffer[SIZE_OF_INGRES_DATE + 1];

	jultodat(julian_date, &temp_date);
	sprintf(ingres_date, "%02u-%s-%04u", temp_date.day,
		lower(strcpy(buffer, getmname(temp_date.month, buffer,
		JDATE_NAME_TYPE_SHORT))), temp_date.year);
	memset(buffer, ' ', SIZE_OF_INGRES_DATE);
	buffer[SIZE_OF_INGRES_DATE] = '\0';
	strncat(ingres_date, buffer, strlen(ingres_date) - SIZE_OF_INGRES_DATE);

	return(ingres_date);
}
/*	*********************************************************************** */

