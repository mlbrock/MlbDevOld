/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Determines the day of the week for a JULIAN date.

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

#include "datfunci.h"

/*	*********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	getdow

	SYNOPSIS		:	day_of_week = getdow(in_julian);

						int    day_of_week;

						JULIAN in_julian;

	DESCRIPTION	:	Determines the day of the week for a specified JULIAN.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_julian`` is the JULIAN for which the day of the
						week is to be determined.

   RETURNS     :  The day-of-week number for the JULIAN specified by the
						``in_julian`` parameter. Day-of-week numbers have the
						following domain:

						(.) 0 --- Sunday

						(.) 1 --- Monday

						(.) 2 --- Tuesday

						(.) 3 --- Wednesday

						(.) 4 --- Thursday

						(.) 5 --- Friday

						(.) 6 --- Saturday

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2015 Michael L. Brock

	OUTPUT INDEX:	getdow
						Date Functions:Get Date/Time Component Functions:getdow
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	getdow

	PUBLISH NAME:	getdow

	ENTRY CLASS	:	Date Functions:Get Date/Time Component Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int getdow(JULIAN in_julian)
#else
int getdow(in_julian)
JULIAN in_julian;
#endif /* #ifndef NARGS */
{
	return(((int) ((in_julian >= ((JULIAN) 0)) ?
		((in_julian + ((JULIAN) DATFUNCS_EPOCH_DAY_OF_WEEK)) % ((JULIAN) 7)) :
		((((JULIAN) 7) - (((((JULIAN) 0) - in_julian) -
		DATFUNCS_EPOCH_DAY_OF_WEEK) % ((JULIAN) 7))) % ((JULIAN) 7)))));
}
/*	*********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>

COMPAT_FN_DECL(int main, (void));

typedef struct {
	int   day_of_week;
	JDATE jdate_date;
} GETDOW_TEST_STRUCT;

GETDOW_TEST_STRUCT TestList[] = {
	{	3,	{  100,  1,	 1	}	},
	{	2,	{ 1752,  9,  1	}	},
	{	3,	{ 1752,  9,  2	}	},
	{	0,	{ 1752,  9, 17	}	},
	{	4,	{ 1752,  9, 14	}	},
	{	6,	{ 1752,  9, 30	}	},
	{	5,	{ 1899, 12,  1	}	},
	{	6,	{ 1899, 12, 30	}	},
	{	0,	{ 1899, 12, 31	}	},
	{	1,	{ 1900,  1,  1	}	},
	{	6, { 1986, 11, 15 }	},
	{  0, { 1989,  1,  1 }	},
	{	0, { 1989, 12, 31 }	},
	{	1, { 1990,  1,  1 }	},
	{	2, { 2016, 11, 15 }	},
	{	5,	{ 9999, 12,	31	}	}
};

/*	*********************************************************************** */
/*	*********************************************************************** */
/*	*********************************************************************** */
int main()
{
	int    return_code = DATFUNCS_SUCCESS;
	int    count_1;
	int    tmp_dow;
	JULIAN tmp_julian;

	fprintf(stderr, "Test routine for function 'getdow()'\n\n");

	for (count_1 = 0; count_1 < (sizeof(TestList) / sizeof(TestList[0]));
		count_1++) {
		tmp_julian = dattojul(&TestList[count_1].jdate_date);
		printf("%04u-%02u-%02u (JULIAN = %10ld) = %d ---> ",
			TestList[count_1].jdate_date.year,
			TestList[count_1].jdate_date.month,
			TestList[count_1].jdate_date.day,
			tmp_julian, tmp_dow = getdow(tmp_julian));
			if (tmp_dow == TestList[count_1].day_of_week)
				printf("SUCCEEDED\n");
			else {
				printf("FAILED (expected %d)\n", TestList[count_1].day_of_week);
				return_code = DATFUNCS_FAILURE;
			}
	}

	return(return_code);
}
/*	*********************************************************************** */

#endif /* #ifdef TEST_MAIN */

