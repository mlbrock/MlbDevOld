/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Converts an Ingres date to a JULIAN date.

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

#include <stdlib.h>
#include <string.h>

#include <strfuncs.h>

#include "datfunci.h"

/*	*********************************************************************** */

/*	*********************************************************************** */
/*	*********************************************************************** */
/*	Data private to this module . . .													*/
/*	*********************************************************************** */
static int  IngresMonthListInitizalizedFlag = 0;

static char IngresMonthList[((1 + 3 + 1) * 12) + 1];
/*	*********************************************************************** */

/*	*********************************************************************** */
/*	*********************************************************************** */
/*	Function prototypes for functions private to this module . . .				*/
/*	*********************************************************************** */
COMPAT_FN_DECL_STATIC(void BuildIngresMonthList, (void));
/*	*********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	ingtojul

	SYNOPSIS		:	julian_date = ingtojul(ingres_date);

						JULIAN  julian_date;

						char   *ingres_date;

	DESCRIPTION	:	Converts an Ingres date to a JULIAN date.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``ingres_date`` is the Ingres date to be converted
						by this function.

   RETURNS     :  Returns from this function are as follow:

						(.) If ``ingres_date`` is a valid date, this function
						will return the ''JULIAN'' equivalent of that date.

						(.) Otherwise, this function returns the ''JULIAN'' date
						value ''0''.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	jultoing

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2015 Michael L. Brock

	OUTPUT INDEX:	ingtojul
						Date Functions:Conversion Functions:ingtojul
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	ingtojul

	PUBLISH NAME:	ingtojul

	ENTRY CLASS	:	Date Functions:Conversion Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
JULIAN ingtojul(char *ingres_date)
#else
JULIAN ingtojul(ingres_date)
char *ingres_date;
#endif /* #ifndef NARGS */
{
	int     month_index;
	JDATE   temp_date;
	JULIAN  temp_julian = (JULIAN) 0L;

	if (strlen(ingres_date) >= (SIZE_OF_INGRES_DATE)) {
		if (!IngresMonthListInitizalizedFlag)
			BuildIngresMonthList();
		if ((month_index = strniidx(IngresMonthList, ingres_date + 2, 5)) > -1) {
			temp_date.year  = atoi(ingres_date + 7);
			temp_date.month = (month_index / 5) + 1;
			temp_date.day   = atoi(ingres_date);
			temp_julian     = dattojul(&temp_date);
		}
	}

	return(temp_julian);
}
/*	*********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/*		Builds the static Ingres date conversion list . . .						*/
/* *********************************************************************** */
#ifndef NARGS
static void BuildIngresMonthList(void)
#else
static void BuildIngresMonthList()
#endif /* #ifndef NARGS */
{
	int count_1;
	char buffer[MAX_MONTH_NAME_LENGTH + 1];

	*IngresMonthList = '\0';

	for (count_1 = 0; count_1 < MONTHS_IN_YEAR; count_1++) {
		strcat(IngresMonthList, INGRES_DATE_SEPARATOR);
		strcat(IngresMonthList, lower(strcpy(buffer,
			getmname(count_1 + 1, buffer, JDATE_NAME_TYPE_SHORT))));
		strcat(IngresMonthList, INGRES_DATE_SEPARATOR);
		IngresMonthListInitizalizedFlag = 1;
	}
}
/*	*********************************************************************** */

