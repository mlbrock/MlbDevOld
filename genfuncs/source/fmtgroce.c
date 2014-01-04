/* *********************************************************************** */
/* *********************************************************************** */
/*	GENFUNCS General Functions Library Source Module								*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Converts a Teknekron 'TSS_GROCERY' data value to
								a string.

	Revision History	:	1993-05-29 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/*    Include necessary header files . . .                                 */
/* *********************************************************************** */

#include <math.h>
#include <stdio.h>
#include <string.h>

#include <strfuncs.h>

#include "genfunci.h"

/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	GEN_FormatTSSGrocery

	SYNOPSIS		:	string_ptr = GEN_FormatTSSGrocery(in_double, in_char,
							out_string);

						char                *string_ptr;

						const double        *in_double;

						const unsigned char *in_char;

						char                *out_string;

	DESCRIPTION	:	Formats the components of a Teknekron ''tss_grocery'' type
						value as a string.

   PARAMETERS  :  Parameters to this function are as follows:

						(.) ``in_double`` points to the ''double'' portion of the
						grocery value to be formatted.

						(.) ``in_char`` points to the ''char'' portion of the
						grocery value to be formatted.

						(.) ``out_string`` points to the string allocated by the
						invoking function to hold the formatted grocery value.

	RETURNS		:	A pointer to the formatted grocery value.

	NOTES			:	No normalization of the fractional component of the
						formatted value is performed. That is, it is possible to
						have fractional components equal to ''0/2'' or ''4/8''.

						If the ''unsigned char'' portion of the grocery exceeds
						the value ''32'', this function will format the grocery
						string as:

<|@|>``double-value-portion``''space (ASCII 32)''``zero-filled-ASCII-value``

						For example, if the ''double'' portion of the grocery is
						''10.0'', and the ''unsigned char'' portion of the grocery
						is ''33'', this function will return the string:

<|@|>10.0 033

	CAVEATS		:	Because the ''double'' values involved in formatting could
						conceivably be very large, the buffer used for formatting
						(``out_string``) should be at least 1000 bytes in size or
						there is a possiblity of buffer overflow.

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2014 Michael L. Brock

   OUTPUT INDEX:	GEN_FormatTSSGrocery
						Miscellaneous Functions:GEN_FormatTSSGrocery
						GENFUNCS:Functions:GEN_FormatTSSGrocery
						GENFUNCS:Miscellaneous Functions:GEN_FormatTSSGrocery
						General Functions:See GENFUNCS
 
	PUBLISH XREF:	GEN_FormatTSSGrocery

	PUBLISH NAME:	GEN_FormatTSSGrocery

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *GEN_FormatTSSGrocery(const double *in_double,
	const unsigned char *in_char, char *out_string)
#else
char *GEN_FormatTSSGrocery(in_double, in_char, out_string)
const double        *in_double;
const unsigned char *in_char;
char                *out_string;
#endif /* #ifndef NARGS */
{
	double tmp_double;
	double fractional;
	double numerator;

	*out_string = '\0';

	if ((!(*in_char)) || (*in_char > 32)) {
		sprintf(out_string, "%256.50f", *in_double);
		rtrimx(out_string, "0");
		if (out_string[strlen(out_string) - 1] == '.')
			chrcat(out_string, '0');
		if (*in_char > 32)
			sprintf(out_string + strlen(out_string), " %03u",
				((unsigned int) *in_char));
		trim(out_string);
	}
	else {
		tmp_double = fabs(*in_double);
		fractional = modf(tmp_double, &tmp_double);
		numerator  = (*in_char < 17) ?
			((double) (((unsigned long) 1L) << ((unsigned long) *in_char))) :
			pow(10.0, ((double) (((int) *in_char) - 16)));
		sprintf(out_string, "%s%20.0f-%20.0f/%20.0f",
			(*in_double < 0.0) ? "-" : "", tmp_double,
			fractional * numerator, numerator);
		noblank(out_string);
	}

	return(out_string);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN
 
#include <stdlib.h>

#ifdef __MSDOS__
COMPAT_EXTERN_DATA_DECL unsigned int _stklen = 16384;
#endif /* __MSDOS__ */

typedef struct {
	double         value;
	unsigned char  fraction;
	char          *expected_result;
} TEST_TSS_GROCERY;

TEST_TSS_GROCERY TestList[] = {
	{	10.0,			0,		"10.0"												},
	{	10.5,			0,		"10.5"												},
	{	10.0,			1,		"10-0/2"												},
	{	10.5,			1,		"10-1/2"												},
	{	10.0,			2,		"10-0/4"												},
	{	10.25,		2,		"10-1/4"												},
	{	10.5,			2,		"10-2/4"												},
	{	10.75,		2,		"10-3/4"												},
	{	10.0,			3,		"10-0/8"												},
	{	10.125,		3,		"10-1/8"												},
	{	10.25,		3,		"10-2/8"												},
	{	10.5,			3,		"10-4/8"												},
	{	10.0,			16,	"10-0/65536"										},
	{	10.5,			16,	"10-32768/65536"									},
	{	10.0,			17,	"10-0/10"											},
	{	10.5,			17,	"10-5/10"											},
	{	10.0,			32,	"10-0/10000000000000000"						},
	{	10.5,			32,	"10-5000000000000000/10000000000000000"	},
	{	10.0,			33,	"10.0 033"											}
};

COMPAT_FN_DECL(int  main, (void));

int main()
{
	int          return_code = 0;
	unsigned int count_1;
	char         grocery_text[4096];

	fprintf(stderr, "Test routine for 'GEN_FormatTSSGrocery()'\n");
	fprintf(stderr, "---- ------- --- ------------------------\n\n");

	for (count_1 = 0; count_1 < (sizeof(TestList) / sizeof(TestList[0]));
		count_1++) {
		printf("[%03u] SENDING :[%20.6f %3u]\n", count_1,
			TestList[count_1].value, ((unsigned int) TestList[count_1].fraction));
		printf(">>>>> RETURNED:[%s]\n",
			GEN_FormatTSSGrocery(&TestList[count_1].value,
			&TestList[count_1].fraction, grocery_text));
		if (strcmp(grocery_text, TestList[count_1].expected_result)) {
			printf(">>>>> EXPECTED:[%s]\n", TestList[count_1].expected_result);
			return_code = 1;
		}
	}

	if (return_code)
		fprintf(stderr, "\n********** ERROR IN TESTED ROUTINE **********\n");

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

