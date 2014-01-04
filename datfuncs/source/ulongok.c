/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Determines whether an unsigned long date is valid.

	Revision History	:	1989-12-06 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1989 - 2014.
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

	NAME			:	ulongok

	SYNOPSIS		:	truth_flag = ulongok(in_ulong);

						int           truth_flag;

						unsigned long in_ulong;

	DESCRIPTION	:	Validates a date in the form of an unsigned long.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_ulong`` is the unsigned long date to be validated.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DATFUNCS_TRUE'' if the date is valid.

						(.) ''DATFUNCS_FALSE'' if the date is not valid.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	fixed_ulongok

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2014 Michael L. Brock

	OUTPUT INDEX:	ulongok
						Date Functions:Check Date Functions:ulongok
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	ulongok

	PUBLISH NAME:	ulongok

	ENTRY CLASS	:	Date Functions:Check Date Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int ulongok(unsigned long in_ulong)
#else
int ulongok(in_ulong)
unsigned long in_ulong;
#endif /* #ifndef NARGS */
{
	return(ymdok(((int) ((in_ulong % 100000000L) / 10000L)),
		((int) ((in_ulong % 10000L) / 100L)), ((int) (in_ulong % 100L))));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	fixed_ulongok

	SYNOPSIS		:	truth_flag = fixed_ulongok(in_ulong, implied_century,
							implied_year_break);

						int           truth_flag;

						unsigned long in_ulong;

						int           implied_century;

						int           implied_year_break;

	DESCRIPTION	:	Validates a date in the form of an unsigned long after
						fixing the year to include the century.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_ulong`` is the unsigned long date to be validated.

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

   RETURNS     :  Returns from this function are as follow:

						(.) ''DATFUNCS_TRUE'' if the date is valid.

						(.) ''DATFUNCS_FALSE'' if the date is not valid.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	ulongok

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2014 Michael L. Brock

	OUTPUT INDEX:	fixed_ulongok
						Date Functions:Check Date Functions:fixed_ulongok
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	fixed_ulongok

	PUBLISH NAME:	fixed_ulongok

	ENTRY CLASS	:	Date Functions:Check Date Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int fixed_ulongok(unsigned long in_ulong, int implied_century,
	int implied_year_break)
#else
int fixed_ulongok(in_ulong, implied_century, implied_year_break)
unsigned long in_ulong;
int           implied_century;
int           implied_year_break;
#endif /* #ifndef NARGS */
{
	return(fixed_ymdok(((int) ((in_ulong % 100000000L) / 10000L)),
		((int) ((in_ulong % 10000L) / 100L)), ((int) (in_ulong % 100L)),
		implied_century, implied_year_break));
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>

typedef struct {
	unsigned long ulong_date;
	JDATE         jdate_date;
} TEST_STRUCT_1;

TEST_STRUCT_1 TestList_1[] = {
	{	19801231L,	{	1980,	12,	31	},	},
	{  19801232L,	{     0,  0,    0	},	},
	{	19000228L,	{	1900,	 2,	28	},	},
	{	19000229L,	{	   0,	 0,	 0	},	},
	{	19040229L,	{	1904,	 2,	29	},	},
	{	19931202L,	{	1993,	12,	 2	},	}
};

typedef struct {
	unsigned long ulong_date;
	JDATE         jdate_date;
	int           implied_century;
	int           implied_year_break;
} TEST_STRUCT_2;

TEST_STRUCT_2 TestList_2[] = {
	{	801231L,	{	2080,	12,	31	},	2000,	50	},
	{  801232L,	{     0,  0,    0	},	2000,	50	},
	{	   228L,	{	2000,	 2,	28	},	2000,	50	},
	{	   229L,	{	2000,	 0,	 0	},	2000,	50	},
	{	 40229L,	{	2004,	 2,	29	},	2000,	50	},
	{	931202L,	{	1993,	12,	 2	},	2000,	50	}
};

COMPAT_FN_DECL(int main, (void));

int main()
{
	int           return_code = DATFUNCS_SUCCESS;
	int          ok_code;
	unsigned int count_1;

	fprintf(stderr, "Test routine for function 'ulongok()'\n");
	fprintf(stderr, "---- ------- --- -------- -----------\n\n");

	for (count_1 = 0; count_1 < (sizeof(TestList_1) / sizeof(TestList_1[0]));
		count_1++) {
		ok_code = ulongok(TestList_1[count_1].ulong_date);
		printf("[%05u] %08lu = %04u-%02u-%02u %s ---> ", count_1,
			TestList_1[count_1].ulong_date,
			TestList_1[count_1].jdate_date.year,
			TestList_1[count_1].jdate_date.month,
			TestList_1[count_1].jdate_date.day,
			(ok_code == DATFUNCS_TRUE) ? "OK    " : "NOT OK");
		printf("%s",
			(((ok_code == DATFUNCS_TRUE) && TestList_1[count_1].jdate_date.year) ||
			((ok_code != DATFUNCS_TRUE) &&
			(!TestList_1[count_1].jdate_date.year))) ?
			"SUCCEEDED" : "FAILED  ");
		if (((ok_code != DATFUNCS_TRUE) && TestList_1[count_1].jdate_date.year) ||
			((ok_code == DATFUNCS_TRUE) &&
			(!TestList_1[count_1].jdate_date.year)))
			return_code = DATFUNCS_FAILURE;
		printf("\n");
	}
	fprintf(stderr, "\n");

	fprintf(stderr, "Test routine for function 'fixed_ulongok()'\n");
	fprintf(stderr, "---- ------- --- -------- -----------------\n\n");

	for (count_1 = 0; count_1 < (sizeof(TestList_2) / sizeof(TestList_2[0]));
		count_1++) {
		ok_code = fixed_ulongok(TestList_2[count_1].ulong_date,
			TestList_2[count_1].implied_century,
			TestList_2[count_1].implied_year_break);
		printf("[%05u] %08lu = %04u-%02u-%02u %s ---> ", count_1,
			TestList_2[count_1].ulong_date,
			TestList_2[count_1].jdate_date.year,
			TestList_2[count_1].jdate_date.month,
			TestList_2[count_1].jdate_date.day,
			(ok_code == DATFUNCS_TRUE) ? "OK    " : "NOT OK");
		printf("%s",
			(((ok_code == DATFUNCS_TRUE) && TestList_2[count_1].jdate_date.year) ||
			((ok_code != DATFUNCS_TRUE) &&
			(!TestList_2[count_1].jdate_date.year))) ?
			"SUCCEEDED" : "FAILED  ");
		if (((ok_code != DATFUNCS_TRUE) && TestList_2[count_1].jdate_date.year) ||
			((ok_code == DATFUNCS_TRUE) &&
			(!TestList_2[count_1].jdate_date.year)))
			return_code = DATFUNCS_FAILURE;
		printf("\n");
	}
	fprintf(stderr, "\n");

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

