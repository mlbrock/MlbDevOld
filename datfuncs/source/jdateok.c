/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Determines whether a 'JDATE' structure is valid.

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

#include "datfunci.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	jdateok

	SYNOPSIS		:	truth_flag = jdateok(in_jdate_ptr);

						int          truth_flag;

						const JDATE *in_jdate_ptr;

	DESCRIPTION	:	Determines whether a structure of type ''JDATE'' is valid.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_jdate_ptr`` points to the ''JDATE'' structure
						which is to be validated.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DATFUNCS_TRUE'' if the structure is valid.

						(.) ''DATFUNCS_FALSE'' if the structure is not valid.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2018 Michael L. Brock

	OUTPUT INDEX:	jdateok
						Date Functions:Check Date Functions:jdateok
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	jdateok

	PUBLISH NAME:	

	ENTRY CLASS	:	Date Functions:Check Date Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int jdateok(const JDATE *in_jdate_ptr)
#else
int jdateok(in_jdate_ptr)
const JDATE *in_jdate_ptr;
#endif /* #ifndef NARGS */
{
	return(ymdok(in_jdate_ptr->year, in_jdate_ptr->month, in_jdate_ptr->day));
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>

typedef struct {
	JDATE jdate_date;
	int   expected_return_code;
} TEST_STRUCT;

TEST_STRUCT TestList[] = {
	{	{	1980,	12,	31	},	DATFUNCS_TRUE	},
	{  {  1980, 12,   32	},	DATFUNCS_FALSE	},
	{	{	1900,	02,	28	},	DATFUNCS_TRUE	},
	{	{	1900,	02,	29	},	DATFUNCS_FALSE	},
	{	{	1904,	02,	29	},	DATFUNCS_TRUE	},
	{	{	1993,	12,	02	},	DATFUNCS_TRUE	}
};

COMPAT_FN_DECL(int main, (void));

int main()
{
	int          return_code = DATFUNCS_SUCCESS;
	int          ok_code;
	unsigned int count_1;

	fprintf(stderr, "Test routine for function 'jdateok()'\n\n");

	for (count_1 = 0; count_1 < (sizeof(TestList) / sizeof(TestList[0]));
		count_1++) {
		ok_code = jdateok(&TestList[count_1].jdate_date);
		printf("[%05u] %04u-%02u-%02u = %s ---> ", count_1,
			TestList[count_1].jdate_date.year,
			TestList[count_1].jdate_date.month,
			TestList[count_1].jdate_date.day,
			(ok_code == DATFUNCS_TRUE) ? "OK    " : "NOT OK");
		printf("%s\n", (ok_code == TestList[count_1].expected_return_code) ?
			"SUCCEEDED" : "FAILED");
		if (ok_code != TestList[count_1].expected_return_code)
			return_code = DATFUNCS_FAILURE;
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */


