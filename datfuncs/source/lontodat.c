/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Converts an unsigned long date to a 'JDATE' structure.

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

	NAME			:	lontodat

	SYNOPSIS		:	jdate_ptr = lontodat(in_ulong, out_jdate_ptr);

						JDATE         *jdate_ptr;

						unsigned long  in_ulong;

						JDATE         *out_jdate_ptr;

	DESCRIPTION	:	Converts an ''unsigned long'' date to a ''JDATE'' structure.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_ulong`` is the ''unsigned long'' date which this
						function is to convert to its ''JDATE'' date equivalent.

						(.) ``out_jdate_ptr`` is a pointer to the ''JDATE''
						structure into which this function will place the
						equivalent of the ``in_ulong`` parameter.

   RETURNS     :  Returns a pointer to the converted ''JDATE'' structure
						(that is, the parameter ``out_jdate_ptr``).

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	jultodat
						lontojul

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2018 Michael L. Brock

	OUTPUT INDEX:	lontodat
						Date Functions:Conversion Functions:lontodat
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	lontodat

	PUBLISH NAME:	lontodat

	ENTRY CLASS	:	Date Functions:Conversion Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
JDATE *lontodat(unsigned long in_ulong, JDATE *out_jdate_ptr)
#else
JDATE *lontodat(in_ulong, out_jdate_ptr)
unsigned long  in_ulong;
JDATE         *out_jdate_ptr;
#endif /* #ifndef NARGS */
{
	JDATE tmp_jdate;

	if (ymdok(tmp_jdate.year = ((int) ((in_ulong % 100000000L) / 10000L)),
		tmp_jdate.month = ((int) ((in_ulong % 10000) / 100L)),
		tmp_jdate.day = ((int) (in_ulong % 100L))) != DATFUNCS_TRUE)
		out_jdate_ptr = NULL;
	else
		*out_jdate_ptr = tmp_jdate;

	return(out_jdate_ptr);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>

typedef struct {
	unsigned long ulong_date;
	JDATE         jdate_date;
} TEST_STRUCT;

TEST_STRUCT TestList[] = {
	{	19801231,	{	1980,	12,	31	},	},
	{  19801232,	{  0000, 00,   00	},	},
	{	19000228,	{	1900,	02,	28	},	},
	{	19000229,	{	0000,	00,	00	},	},
	{	19040229,	{	1904,	02,	29	},	},
	{	19931202,	{	1993,	12,	02	},	}
};

COMPAT_FN_DECL(int main, (void));

int main()
{
	int            return_code = DATFUNCS_SUCCESS;
	JDATE        *ok_code;
	unsigned int  count_1;

	fprintf(stderr, "Test routine for function 'lontodat()'\n\n");

	for (count_1 = 0; count_1 < (sizeof(TestList) / sizeof(TestList[0]));
		count_1++) {
		ok_code = lontodat(TestList[count_1].ulong_date,
			&TestList[count_1].jdate_date);
		printf("[%05u] %08lu = %04u-%02u-%02u %s ---> ", count_1,
			TestList[count_1].ulong_date,
			TestList[count_1].jdate_date.year,
			TestList[count_1].jdate_date.month,
			TestList[count_1].jdate_date.day,
			(ok_code != NULL) ? "OK    " : "NOT OK");
		printf("%s", (((ok_code != NULL) && TestList[count_1].jdate_date.year) ||
			((ok_code == NULL) && (!TestList[count_1].jdate_date.year))) ?
			"SUCCEEDED" : "FAILED  ");
		if (ok_code == NULL)
			return_code = DATFUNCS_FAILURE;
		printf("\n");
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */


