/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Converts a JULIAN date to a string.

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

#include <stdio.h>
#include <string.h>

#include <strfuncs.h>

#include "datfunci.h"

/*	*********************************************************************** */

/*	*********************************************************************** */
/*	*********************************************************************** */
/*	*********************************************************************** */

static int DATFUNCS_DateSpec = DATE_SPEC_DEFAULT;

/*	*********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	setjspec

	SYNOPSIS		:	old_date_spec = setjspec(date_spec);

						int old_date_spec;

						int date_spec;

	DESCRIPTION	:	Sets the current JULIAN-date-to-string formatting
						specification.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``date_spec`` is the JULIAN-date-to-string formatting
						specification to be set by this function.

   RETURNS     :  Returns the JULIAN-date-to-string formatting
						specification in effect before this function was invoked.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	getjspec
						jultostr

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2015 Michael L. Brock

	OUTPUT INDEX:	setjspec
						Date Functions:Formatting Functions:setjspec
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	setjspec

	PUBLISH NAME:	setjspec

	ENTRY CLASS	:	Date Functions:Formatting Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int setjspec(int date_spec)
#else
int setjspec(date_spec)
int date_spec;
#endif /* #ifndef NARGS */
{
	int old_date_spec = DATFUNCS_DateSpec;

	DATFUNCS_DateSpec = date_spec;

	return(old_date_spec);
}
/*	*********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	getjspec

	SYNOPSIS		:	date_spec = getjspec(void);

	DESCRIPTION	:	Returns the current JULIAN-date-to-string formatting
						specification.

   PARAMETERS  :  Parameters to this function are as follow:

   RETURNS     :  Returns the JULIAN-date-to-string formatting
						specification in effect at the time this function was
						invoked.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	setjspec
						jultostr

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2015 Michael L. Brock

	OUTPUT INDEX:	getjspec
						Date Functions:Formatting Functions:getjspec
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	getjspec

	PUBLISH NAME:	getjspec

	ENTRY CLASS	:	Date Functions:Formatting Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int getjspec(void)
#else
int getjspec()
#endif /* #ifndef NARGS */
{
	return(DATFUNCS_DateSpec);
}
/*	*********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	jultostr

	SYNOPSIS		:	return_ptr = jultostr(in_julian, text);

						char   *return_ptr;

						JULIAN  in_julian;

						char   *text;

	DESCRIPTION	:	Formats a ''JULIAN'' date as a string using the current
						JULIAN-date-to-string formatting specification.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_julian`` is the ''JULIAN'' date to be formatted
						as a string by this function.

						(.) ``text`` is the string into which this function is to
						place to formatted string.

   RETURNS     :  Returns the formatted string (that is, the parameter
						``text``).

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	setjspec
						getjspec

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2015 Michael L. Brock

	OUTPUT INDEX:	jultostr
						Date Functions:Formatting Functions:jultostr
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	jultostr

	PUBLISH NAME:	jultostr

	ENTRY CLASS	:	Date Functions:Formatting Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *jultostr(JULIAN in_julian, char *text)
#else
char *jultostr(in_julian, text)
JULIAN in_julian;
char   *text;
#endif /* #ifndef NARGS */
{
	char  year_spec[4 + 1];
	char  month_spec[20 + 1];
	char  day_spec[2 + 1];
	char  separator_spec[1 + 1];
	char  dow_separator_spec[1 + 1];
	char  dow_spec[20 + 1];
	char  ordinal_spec[2 + 1];
	char  comma_spec[1 + 1];
	JDATE temp_date;

	jultodat(in_julian, &temp_date);

	sprintf(year_spec, (DATFUNCS_DateSpec & DATE_SPEC_YEAR_2_DIGIT) ?
		"%02u" : "%04u", (DATFUNCS_DateSpec & DATE_SPEC_YEAR_2_DIGIT) ?
		(temp_date.year % 100) : temp_date.year);

	if ((DATFUNCS_DateSpec & DATE_SPEC_MONTH_LONG_NAME) ||
		(DATFUNCS_DateSpec & DATE_SPEC_MONTH_SHORT_NAME))
		getmname(temp_date.month, month_spec,
			(DATFUNCS_DateSpec & DATE_SPEC_MONTH_LONG_NAME) ?
			JDATE_NAME_TYPE_LONG : JDATE_NAME_TYPE_SHORT);
	else
		sprintf(month_spec, (DATFUNCS_DateSpec & DATE_SPEC_MONTH_BLANK_FILLED) ?
			"%2u" : "%02u", temp_date.month);

	sprintf(day_spec, (DATFUNCS_DateSpec & DATE_SPEC_DAY_BLANK_FILLED) ?
		"%2u" : "%02u", temp_date.day);

	strcpy(separator_spec,
		(DATFUNCS_DateSpec & DATE_SPEC_SEPARATOR_PERIOD) ? "." :
		(DATFUNCS_DateSpec & DATE_SPEC_SEPARATOR_DASH)   ? "-" :
		(DATFUNCS_DateSpec & DATE_SPEC_SEPARATOR_BLANK)  ? " " : "/");

	if ((DATFUNCS_DateSpec & DATE_SPEC_DOW_SHORT_NAME) ||
		(DATFUNCS_DateSpec & DATE_SPEC_DOW_LONG_NAME)) {
		downame(getdow(in_julian), dow_spec);
/*
		if (DATFUNCS_DateSpec & DATE_SPEC_DOW_SHORT_NAME) ?
			JDATE_NAME_TYPE_SHORT : JDATE_NAME_TYPE_LONG);
*/
		if (DATFUNCS_DateSpec & DATE_SPEC_DOW_SHORT_NAME)
			dow_spec[3] = '\0';
		strcpy(dow_separator_spec, " ");
	}
	else {
		*dow_spec           = '\0';
		*dow_separator_spec = '\0';
	}

	if (DATFUNCS_DateSpec & DATE_SPEC_ORDINAL_ON)
		ordinal(((unsigned int) dayofmon(in_julian)), ordinal_spec);
	else
		*ordinal_spec = '\0';

	strcpy(comma_spec, "");
	if ((DATFUNCS_DateSpec & DATE_SPEC_ORDER_DD_MM_YY) ||
		(!(DATFUNCS_DateSpec & DATE_SPEC_ORDER_YY_MM_DD))) {
		if ((DATFUNCS_DateSpec & DATE_SPEC_MONTH_SHORT_NAME) ||
			(DATFUNCS_DateSpec & DATE_SPEC_MONTH_LONG_NAME) || *dow_spec) {
			if (DATFUNCS_DateSpec & DATE_SPEC_SEPARATOR_BLANK)
				strcpy(comma_spec, ",");
		}
	}

	if (DATFUNCS_DateSpec & DATE_SPEC_CASE_LOWER) {
		lower(month_spec);
		lower(dow_spec);
	}
	else if (DATFUNCS_DateSpec & DATE_SPEC_CASE_UPPER) {
		upper(month_spec);
		upper(dow_spec);
		upper(ordinal_spec);
	}

	if (DATFUNCS_DateSpec & DATE_SPEC_ORDER_DD_MM_YY)      /* Wed 31st, Dec 1989 */
		sprintf(text, "%s%s%s%s%s%s%s%s%s",
			dow_spec,   dow_separator_spec,
			day_spec,   ordinal_spec,
			comma_spec, separator_spec,
			month_spec, separator_spec,
			year_spec);
	else if (DATFUNCS_DateSpec & DATE_SPEC_ORDER_YY_MM_DD) /* Wed 1989 Dec 31st */
		sprintf(text, "%s%s%s%s%s%s%s%s",
			dow_spec,   dow_separator_spec,
			year_spec,  separator_spec,
			month_spec, separator_spec,
			day_spec,   ordinal_spec);
	else
		sprintf(text, "%s%s%s%s%s%s%s%s%s",
			dow_spec,     dow_separator_spec,
			month_spec,   separator_spec,
			day_spec,     ordinal_spec,
			comma_spec,   separator_spec,
			year_spec);

	return(text);
}
/*	*********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>

COMPAT_FN_DECL(int main, (void));

typedef struct {
	JULIAN julian_date;
	JDATE  jdate_date;
} JULTODAT_TEST_STRUCT;

JULTODAT_TEST_STRUCT TestList[] = {
	{	31729, { 1986, 11, 15 } },
	{  32507, { 1989, 01, 01 } },
	{	32871, { 1989, 12, 31 } },
	{	32872, { 1990, 01, 01 } },
	{	42687, { 2016, 11, 15 } },
};

/*	*********************************************************************** */
/*	*********************************************************************** */
/*	*********************************************************************** */
int main()
{
	int  count_1;
	char buffer[512 + 1];

	fprintf(stderr, "Test routine for function 'jultostr()'\n\n");

	for (count_1 = 0; count_1 < (sizeof(TestList) / sizeof(TestList[0]));
		count_1++) {
		printf("%02u/%02u/%04u (%lu) = [%s]\n",
			TestList[count_1].jdate_date.month,
			TestList[count_1].jdate_date.day,
			TestList[count_1].jdate_date.year,
			TestList[count_1].julian_date,
			jultostr(TestList[count_1].julian_date, buffer));
	}

	return(1);
}
/*	*********************************************************************** */

#endif /* #ifdef TEST_MAIN */

