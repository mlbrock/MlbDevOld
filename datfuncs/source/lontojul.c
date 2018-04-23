/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Converts an unsigned long date to a JULIAN date.

	Revision History	:	1989-11-08 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1989 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <stdio.h>

#include "datfunci.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	lontojul

	SYNOPSIS		:	julian_date = lontojul(in_ulong);

						JULIAN        julian_date;

						unsigned long in_ulong;

	DESCRIPTION	:	Converts an ''unsigned long'' date to a ''JULIAN'' date.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_ulong`` is the ''unsigned long'' date to be
						converted by this function into its ''JULIAN'' date
						equivalent.

   RETURNS     :  Returns the ''JULIAN'' equivalent of the ``in_ulong``
						parameter.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	jultolon
						fixed_lontojul

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2018 Michael L. Brock

	OUTPUT INDEX:	lontojul
						Date Functions:Conversion Functions:lontojul
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	lontojul

	PUBLISH NAME:	lontojul

	ENTRY CLASS	:	Date Functions:Conversion Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
JULIAN lontojul(unsigned long in_ulong)
#else
JULIAN lontojul(in_ulong)
unsigned long in_ulong;
#endif /* #ifndef NARGS */
{
	return(ymdtojul(((int) ((in_ulong % 100000000L) / 10000L)),
		((int) ((in_ulong % 10000) / 100L)), ((int) (in_ulong % 100L))));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	fixed_lontojul

	SYNOPSIS		:	julian_date = fixed_lontojul(in_ulong, implied_century,
							implied_year_break);

						JULIAN        julian_date;

						unsigned long in_ulong;

						int           implied_century;

						int           implied_year_break;

	DESCRIPTION	:	Converts an ''unsigned long'' date to a ''JULIAN'' date.

						If the ''unsigned long'' date does not contain a century
						portion, this function will use the ``implied_century``
						and ``implied_year_break`` parameters to determine the
						century.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_ulong`` is the ''unsigned long'' date to be
						converted by this function into its ''JULIAN'' date
						equivalent.

						(.) ``implied_century`` is the century to be added to the
						date if the year is less than that specified by the
						``implied_year_break`` parameter.

						(.) ``implied_year_break`` specifies the fulcrum year at
						which the determination as to which century a date belongs.

						(-) Dates less than ``implied_year_break`` will be fixed so
						as to be in the century specified by ``implied_century``.

						(-) Dates greater than or equal to ``implied_year_break``
						will be fixed so as to be in the century before that
						specified by implied century.

   RETURNS     :  Returns the ''JULIAN'' equivalent of the ``in_ulong``
						parameter.

	NOTES			:	This function should check for the special case of
						February 29th as this could, in some cases, determine
						definitively the century to which a date belongs. This
						will be changed in a later release.

	CAVEATS		:	

	SEE ALSO		:	lontojul
						jultolon

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2018 Michael L. Brock

	OUTPUT INDEX:	fixed_lontojul
						Date Functions:Conversion Functions:fixed_lontojul
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	fixed_lontojul

	PUBLISH NAME:	fixed_lontojul

	ENTRY CLASS	:	Date Functions:Conversion Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
JULIAN fixed_lontojul(unsigned long in_ulong, int implied_century,
	int implied_year_break)
#else
JULIAN fixed_lontojul(in_ulong, implied_century, implied_year_break)
unsigned long in_ulong;
int           implied_century;
int           implied_year_break;
#endif /* #ifndef NARGS */
{
	return(lontojul(fixulong(in_ulong, implied_century, implied_year_break)));
}
/* *********************************************************************** */

#ifdef TEST_MAIN

typedef struct {
	unsigned long ulong_date;
	JDATE         jdate_date;
	JULIAN        expected_julian;
} TEST_STRUCT_1;

TEST_STRUCT_1 TestList_1[] = {
	{	19801231,	{	1980,	12,	31	},	29584L	},
	{	20801231,	{	1980,	12,	31	},	66109L	},
	{  19801232,	{     0,  0,    0	},	    0L	},
	{	19000228,	{	1900,	 2,	28	},	   58L	},
	{	19000229,	{	   0,	 0,	 0	},	    0L	},
	{	19040229,	{	1904,	 2,	29	},	 1519L	},
	{	19931202,	{	1993,	12,	 2	},	34303L	}
};

typedef struct {
	unsigned long ulong_date;
	JDATE         jdate_date;
	JULIAN        expected_julian;
	int           implied_century;
	int           implied_year_break;
} TEST_STRUCT_2;

TEST_STRUCT_2 TestList_2[] = {
	{	  801231,	{	1980,	12,	31	},	29584L,	2000,	50	},
	{	19801231,	{	1980,	12,	31	},	29584L,	2000,	50	},
	{	20801231,	{	1980,	12,	31	},	66109L,	2000,	50	},
	{    801232,	{     0,  0,    0	},	    0L,	2000,	50	},
	{	     228,	{	2000,	 2,	28	},	36582L,	2000,	50	},
	{	19000228,	{	2000,	 2,	28	},	   58L,	2000,	50	},
	{	20000228,	{	2000,	 2,	28	},	36582L,	2000,	50	},
	{	     229,	{	2000,	 0,	 0	},	36583L,	2000,	50	},
	{	19000229,	{	2000,	 0,	 0	},	    0L,	2000,	50	},
	{	20000229,	{	2000,	 0,	 0	},	36583L,	2000,	50	},
	{	   40229,	{	2004,	 2,	29	},	38044L,	2000,	50	},
	{	19040229,	{	2004,	 2,	29	},	 1519L,	2000,	50	},
	{	20040229,	{	2004,	 2,	29	},	38044L,	2000,	50	},
	{	  931202,	{	1993,	12,	02	},	34303L,	2000,	50	},
	{	19931202,	{	1993,	12,	02	},	34303L,	2000,	50	},
	{	20931202,	{	1993,	12,	02	},	70828L,	2000,	50	}
};

COMPAT_FN_DECL(int main, (void));

int main()
{
	int          return_code = DATFUNCS_SUCCESS;
	JULIAN       ok_julian;
	JDATE        tmp_jdate;
	unsigned int count_1;

	fprintf(stderr, "Test routine for function 'lontojul()'\n");
	fprintf(stderr, "---- ------- --- -------- ------------\n\n");

	for (count_1 = 0; count_1 < (sizeof(TestList_1) / sizeof(TestList_1[0]));
		count_1++) {
		ok_julian = lontojul(TestList_1[count_1].ulong_date);
		printf("[%05u] %08lu = %04u-%02u-%02u %10ld ---> ", count_1,
			TestList_1[count_1].ulong_date,
			TestList_1[count_1].jdate_date.year,
			TestList_1[count_1].jdate_date.month,
			TestList_1[count_1].jdate_date.day,
			ok_julian);
		if (ok_julian) {
			jultodat(ok_julian, &tmp_jdate);
			printf("%04u-%02u-%02u ---> ",
				tmp_jdate.year, tmp_jdate.month, tmp_jdate.day);
		}
		else
			printf("0000-00-00 ---> ");
		printf("%s", (ok_julian == TestList_1[count_1].expected_julian) ?
			"SUCCEEDED" : "FAILED  ");
		if (ok_julian != TestList_1[count_1].expected_julian)
			return_code = DATFUNCS_FAILURE;
		printf("\n");
	}
	fprintf(stderr, "\n");

	fprintf(stderr, "Test routine for function 'fixed_lontojul()'\n");
	fprintf(stderr, "---- ------- --- -------- ------------------\n\n");

	for (count_1 = 0; count_1 < (sizeof(TestList_2) / sizeof(TestList_2[0]));
		count_1++) {
		ok_julian = fixed_lontojul(TestList_2[count_1].ulong_date,
			TestList_2[count_1].implied_century,
			TestList_2[count_1].implied_year_break);
		printf("[%05u] %08lu = %04u-%02u-%02u %10ld ---> ", count_1,
			TestList_2[count_1].ulong_date,
			TestList_2[count_1].jdate_date.year,
			TestList_2[count_1].jdate_date.month,
			TestList_2[count_1].jdate_date.day,
			ok_julian);
		if (ok_julian) {
			jultodat(ok_julian, &tmp_jdate);
			printf("%04u-%02u-%02u ---> ",
				tmp_jdate.year, tmp_jdate.month, tmp_jdate.day);
		}
		else
			printf("0000-00-00 ---> ");
		printf("%s", (ok_julian == TestList_2[count_1].expected_julian) ?
			"SUCCEEDED" : "FAILED  ");
		if (ok_julian != TestList_2[count_1].expected_julian)
			return_code = DATFUNCS_FAILURE;
		printf("\n");
	}
	fprintf(stderr, "\n");

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */


