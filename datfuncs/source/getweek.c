/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets the week number of the year for a given JULIAN
								date.

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

	NAME			:	getweek

	SYNOPSIS		:	week_of_year = getweek(in_julian);

						int    week_of_year;

						JULIAN in_julian;

	DESCRIPTION	:	Determines the week number month of a specified JULIAN date
						within its year.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_julian`` is the JULIAN for which the week number
						is to be determined.

   RETURNS     :  The week number of the JULIAN date ``in_julian``.

	NOTES			:	This routine calculates the actual week number of the
						year, ''NOT'' the ISO week number.

	CAVEATS		:	

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2018 Michael L. Brock

	OUTPUT INDEX:	getweek
						Date Functions:Get Date/Time Component Functions:getweek
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	getweek

	PUBLISH NAME:	getweek

	ENTRY CLASS	:	Date Functions:Get Date/Time Component Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int getweek(JULIAN in_julian)
#else
int getweek(in_julian)
JULIAN in_julian;
#endif /* #ifndef NARGS */
{
	JULIAN start_julian;
	int    dow_adjust;

	dow_adjust  = ((int) (in_julian - (start_julian = get0101(in_julian)))) + 1;
	dow_adjust += getdow(start_julian);

	return((dow_adjust / 7) + ((dow_adjust % 7) ? 1 : 0));
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>

COMPAT_FN_DECL(int main, (void));

typedef struct {
	int   week_number;
	JDATE jdate_date;
} GETWEEK_TEST_STRUCT;

GETWEEK_TEST_STRUCT TestList[] = {
	{	 1,	{  100,  1,	 1	}	},
	{	53,	{  100, 12,	31	}	},
	{	36,	{ 1752,  9,  1	}	},
	{	36,	{ 1752,  9,  2	}	},
	{	36,	{ 1752,  9, 14	}	},
	{	37,	{ 1752,  9, 17	}	},
	{	38,	{ 1752,  9, 30	}	},
	{	48,	{ 1899, 12,  1	}	},
	{	52,	{ 1899, 12, 30	}	},
	{	53,	{ 1899, 12, 31	}	},
	{	 1,	{ 1900,  1,  1	}	},
	{	 1,	{ 1900,  1,  6	}	},
	{	 2,	{ 1900,  1,  7	}	},
	{	 5,	{ 1900,  1, 31	}	},
	{	46,	{ 1986, 11, 15 }	},
	{   1,	{ 1989,  1,  1 }	},
	{	53,	{ 1989, 12, 31 }	},
	{	 1,	{ 1990,  1,  1 }	},
	{	47,	{ 2016, 11, 15 }	},
	{	 1,	{ 9999,  1,  1	}	},
	{	53,	{ 9999, 12,	31	}	}
};

/*	*********************************************************************** */
/*	*********************************************************************** */
/*	*********************************************************************** */
int main()
{
	int    return_code = DATFUNCS_SUCCESS;
	int    count_1;
	int    tmp_week_number;
	JULIAN tmp_julian;

	fprintf(stderr, "Test routine for function 'getweek()'\n\n");

	for (count_1 = 0; count_1 < (sizeof(TestList) / sizeof(TestList[0]));
		count_1++) {
		tmp_julian = dattojul(&TestList[count_1].jdate_date);
		printf("%04u-%02u-%02u (JULIAN = %10ld) = %2d ---> ",
			TestList[count_1].jdate_date.year,
			TestList[count_1].jdate_date.month,
			TestList[count_1].jdate_date.day,
			tmp_julian, tmp_week_number = getweek(tmp_julian));
			if (tmp_week_number == TestList[count_1].week_number)
				printf("SUCCEEDED\n");
			else {
				printf("FAILED (expected %d)\n", TestList[count_1].week_number);
				return_code = DATFUNCS_FAILURE;
			}
	}

	return(return_code);
}
/*	*********************************************************************** */

#endif /* #ifdef TEST_MAIN */

