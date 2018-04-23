/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* STRFUNCS String and Memory Functions Library Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes RADIX-50 conversion tables.

	Revision History	:	1990-06-04 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1990 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Necessary include files . . .														*/
/* *********************************************************************** */

#include <limits.h>

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	RADIX50_AsciiString

	DESCRIPTION	:	``RADIX50_AsciiString`` is the default RADIX-50
						initialization string used by ``RADIX50_init_tables``
						when the initialization string passed to that function is
						''NULL''.

						The string has the following value:

						(-) " ABCDEFGHIJKLMNOPQRSTUVWXYZ'.-0123456789";

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	RADIX50_AsciiTable
						RADIX50_Radix50Table

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1990 - 2018 Michael L. Brock

	OUTPUT INDEX:	RADIX50_AsciiString
						STRFUNCS:RADIX-50 Default Data:RADIX50_AsciiString
						RADIX-50 Default Data:RADIX50_AsciiString
						String Functions:See STRFUNCS

	PUBLISH XREF:	RADIX50_AsciiString
						default RADIX-50 initialization string

	PUBLISH NAME:	RADIX50_AsciiString

	ENTRY CLASS	:	RADIX-50 Default Data

EOH */
/* *********************************************************************** */
COMPAT_EXTERN_DATA_DEF const char *RADIX50_AsciiString =
	" ABCDEFGHIJKLMNOPQRSTUVWXYZ'.-0123456789";
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	RADIX50_AsciiTable

	DESCRIPTION	:	This is the default ASCII-to-RADIX-50 mapping table used
						by ``RADIX50_asctorad`` to convert ASCII strings to
						RADIX-50 values.

						The ASCII characters converted, and their associated
						RADIX-50 values are as follow:

{-}ASCII   RADIX-50  ASCII   RADIX-50
------- --------  ------- --------
<space>        0  T             20
A              1  U             21
B              2  V             22
C              3  W             23
D              4  X             24
E              5  Y             25
F              6  Z             26
G              7  '             27
H              8  .             28
I              9  -             29
J             10  0             30
K             11  1             31
L             12  2             32
M             13  3             33
N             14  4             34
O             15  5             35
P             16  6             36
Q             17  7             37
R             18  8             38
S             19  9             39

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	RADIX50_asctorad
						RADIX50_asctorad_basic
						RADIX50_Radix50Table

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1990 - 2018 Michael L. Brock

	OUTPUT INDEX:	RADIX50_AsciiTable
						STRFUNCS:RADIX-50 Default Data:RADIX50_AsciiTable
						RADIX-50 Default Data:RADIX50_AsciiTable
						String Functions:See STRFUNCS

	PUBLISH XREF:	RADIX50_AsciiTable
						default ASCII-to-RADIX-50 mapping
						default ASCII-to-RADIX-50 mapping table

	PUBLISH NAME:	RADIX50_AsciiTable

	ENTRY CLASS	:	RADIX-50 Default Data

EOH */
/* *********************************************************************** */
COMPAT_EXTERN_DATA_DEF const unsigned char RADIX50_AsciiTable[UCHAR_MAX + 1] = {
	0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
	0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
	0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
	0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
	0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X1B,
	0X00, 0X00, 0X00, 0X00, 0X00, 0X1D, 0X1C, 0X00,
	0X1E, 0X1F, 0X20, 0X21, 0X22, 0X23, 0X24, 0X25,
	0X26, 0X27, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
	0X00, 0X01, 0X02, 0X03, 0X04, 0X05, 0X06, 0X07,
	0X08, 0X09, 0X0A, 0X0B, 0X0C, 0X0D, 0X0E, 0X0F,
	0X10, 0X11, 0X12, 0X13, 0X14, 0X15, 0X16, 0X17,
	0X18, 0X19, 0X1A, 0X00, 0X00, 0X00, 0X00, 0X00,
	0X00, 0X01, 0X02, 0X03, 0X04, 0X05, 0X06, 0X07,
	0X08, 0X09, 0X0A, 0X0B, 0X0C, 0X0D, 0X0E, 0X0F,
	0X10, 0X11, 0X12, 0X13, 0X14, 0X15, 0X16, 0X17,
	0X18, 0X19, 0X1A, 0X00, 0X00, 0X00, 0X00, 0X00,
	0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
	0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
	0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
	0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
	0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
	0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
	0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
	0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
	0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
	0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
	0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
	0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
	0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
	0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
	0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
	0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00
};
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	RADIX50_Radix50Table

	DESCRIPTION	:	This is the default RADIX-50-to-ASCII mapping table used
						by ``RADIX50_radtoasc`` to convert RADIX-50 values to ASCII
						strings.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	RADIX50_radtoasc
						RADIX50_radtoasc_basic
						RADIX50_AsciiTable

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1990 - 2018 Michael L. Brock

	OUTPUT INDEX:	RADIX50_Radix50Table
						STRFUNCS:RADIX-50 Default Data:RADIX50_Radix50Table
						RADIX-50 Default Data:RADIX50_Radix50Table
						String Functions:See STRFUNCS

	PUBLISH XREF:	RADIX50_Radix50Table
						default RADIX-50-to-ASCII mapping
						default RADIX-50-to-ASCII mapping table

	PUBLISH NAME:	RADIX50_Radix50Table

	ENTRY CLASS	:	RADIX-50 Default Data

EOH */
/* *********************************************************************** */
COMPAT_EXTERN_DATA_DEF const unsigned char RADIX50_Radix50Table[40] = {
	0X20, 0X41, 0X42, 0X43, 0X44, 0X45, 0X46, 0X47,
	0X48, 0X49, 0X4A, 0X4B, 0X4C, 0X4D, 0X4E, 0X4F,
	0X50, 0X51, 0X52, 0X53, 0X54, 0X55, 0X56, 0X57,
	0X58, 0X59, 0X5A, 0X27, 0X2E, 0X2D, 0X30, 0X31,
	0X32, 0X33, 0X34, 0X35, 0X36, 0X37, 0X38, 0X39
};
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	RADIX50_init_tables

	SYNOPSIS		:	RADIX50_init_tables(in_string, lower_case_flag,
							out_ascii_table, out_radix_table);

						const char    *in_string;

						int            lower_case_flag;

						unsigned char *out_ascii_table;

						unsigned char *out_radix_table;

	DESCRIPTION	:	Initializes mapping tables for conversion between ASCII
						and RADIX-50.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_string`` is the string to be used to initialize
						the tables. It should be an array of ``char`` forty
						characters in length. Each character will be built into
						the mapping tables.

						(-) If ``in_string`` is ''NULL', the default RADIX-50
						initialization string ``RADIX50_AsciiString`` is used.
						That string has the following value:

						(--) " ABCDEFGHIJKLMNOPQRSTUVWXYZ'.-0123456789";

						(-) Note that the first character in the above string is a
						space (ASCII 32).

						(.) ``lower_case_flag`` specifies the case of the mapping
						to be used for alphabetic characters in ``in_string`` (if
						any).

						(-) If ``lower_case_flag`` is zero, then the
						RADIX-50-to-ASCII mapping table will be constructed
						so as to emit any alphabetic characters in upper-case.

						(-) If ``lower_case_flag`` is non-zero, then the
						RADIX-50-to-ASCII mapping table will be constructed
						so as to emit any alphabetic characters in lower-case.

						(.) ``out_ascii_table`` points the area of memory into
						which is to be placed the ASCII-to-RADIX-50 mapping table
						initialized by this function. The minimum length of this
						memory area must be:

						(-) (UCHAR_MAX + 1) * sizeof(unsigned char)

						(.) ``out_radix_table`` points the area of memory into
						which is to be placed the RADIX-50-to-ASCII mapping table
						initialized by this function. The minimum length of this
						memory area must be:

						(-) 40 * sizeof(unsigned char)

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	The functions which convert an ASCII string to a RADIX-50
						array (``RADIX50_asctorad`` and ``RADIX50_asctorad_basic``)
						do not check to ensure that all of the characters in the
						string to be converted are in the domain of the characters
						specified in the ``in_string`` parameter to this function.
						Characters not in domain are converted to the RADIX-50
						equivalent of the first character of ``in_string``.

	SEE ALSO		:	RADIX50_asctorad
						RADIX50_asctorad_basic

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1990 - 2018 Michael L. Brock

	OUTPUT INDEX:	RADIX50_init_tables
						STRFUNCS:RADIX-50 Functions:RADIX50_init_tables
						RADIX-50 Functions:RADIX50_init_tables
						String Functions:See STRFUNCS

	PUBLISH XREF:	RADIX50_init_tables

	PUBLISH NAME:	RADIX50_init_tables

	ENTRY CLASS	:	RADIX-50 Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void RADIX50_init_tables(const char *in_string, int lower_case_flag,
	unsigned char *out_ascii_table, unsigned char *out_radix_table)
#else
void RADIX50_init_tables(in_string, lower_case_flag, out_ascii_table,
	out_radix_table)
const char    *in_string;
int            lower_case_flag;
unsigned char *out_ascii_table;
unsigned char *out_radix_table;
#endif /* #ifndef NARGS */
{
	unsigned int   count_1;
	unsigned char *tmp_string;

	tmp_string = (in_string != NULL) ? ((unsigned char *) in_string) :
		((unsigned char *) RADIX50_AsciiString);

	for (count_1 = 0; count_1 < (UCHAR_MAX + 1); count_1++)
		out_ascii_table[count_1] = '\0';

	for (count_1 = 0; count_1 < 40; count_1++) {
		if (!isalpha(tmp_string[count_1]))
			out_ascii_table[tmp_string[count_1]] = ((unsigned char) count_1);
		else {
			out_ascii_table[strfmacs_tolower(tmp_string[count_1])] =
				((unsigned char) count_1);
			out_ascii_table[strfmacs_toupper(tmp_string[count_1])] =
				((unsigned char) count_1);
		}
	}

	for (count_1 = 0; count_1 < 40; count_1++)
		out_radix_table[count_1] = ((unsigned char)
			((!isalpha(tmp_string[count_1])) ? tmp_string[count_1] :
			((!lower_case_flag) ? strfmacs_toupper(tmp_string[count_1]) :
			strfmacs_tolower(tmp_string[count_1]))));
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>
#include <string.h>

#include "strfunci.h"

COMPAT_FN_DECL(int main, (int argc, char **argv));

COMPAT_FN_DECL_STATIC(void OUTPUT_Data,
	(const unsigned char *ascii_table, const unsigned char *radix_table));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int           return_code = STRFUNCS_SUCCESS;
	unsigned int  count_1;
	unsigned char ascii_table[UCHAR_MAX + 1];
	unsigned char radix_table[40];

	fprintf(stderr, "Test routine for function 'RADIX50_init_tables()'\n");
	fprintf(stderr, "---- ------- --- -------- -----------------------\n\n");

	if (argc == 1) {
		RADIX50_init_tables(RADIX50_AsciiString, 0, ascii_table, radix_table);
		if (memcmp(RADIX50_AsciiTable, ascii_table,
			(UCHAR_MAX + 1) * sizeof(unsigned char))) {
			OUTPUT_Data(RADIX50_AsciiTable, RADIX50_Radix50Table);
			OUTPUT_Data(ascii_table, radix_table);
			fprintf(stderr, "ERROR: %s.\n",
				"Calculated ASCII table differs from built-in");
			return_code = STRFUNCS_FAILURE;
		}
		else if (memcmp(RADIX50_Radix50Table, radix_table,
			40 * sizeof(unsigned char))) {
			OUTPUT_Data(RADIX50_AsciiTable, RADIX50_Radix50Table);
			OUTPUT_Data(ascii_table, radix_table);
			fprintf(stderr, "ERROR: %s.\n",
				"Calculated RADIX-50 table differs from built-in");
			return_code = STRFUNCS_FAILURE;
		}
		OUTPUT_Data(RADIX50_AsciiTable, RADIX50_Radix50Table);
	}
	else {
		for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
			RADIX50_init_tables(argv[count_1], 0, ascii_table, radix_table);
			OUTPUT_Data(ascii_table, radix_table);
		}
	}

	return(return_code);
}

#ifndef NARGS
static void OUTPUT_Data(const unsigned char *ascii_table,
	const unsigned char *radix_table)
#else
static void OUTPUT_Data(ascii_table, radix_table)
const unsigned char *ascii_table;
const unsigned char *radix_table;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;
	unsigned int count_2;

	printf("const unsigned char RADIX50_AsciiTable[UCHAR_MAX + 1] = {\n");
	for (count_1 = 0; count_1 <= UCHAR_MAX; ) {
		printf("\t");
		for (count_2 = 0; count_2 < 8; count_2++, count_1++)
			printf("0X%02X%s", ascii_table[count_1],
				(count_2 < 7) ? ", " : "");
		printf("%s\n", (count_1 < UCHAR_MAX) ? "," : "");
	}
	printf("};\n\n");

	printf("const unsigned char RADIX50_Radix50Table[40]          = {\n");
	for (count_1 = 0; count_1 < 40; ) {
		printf("\t");
		for (count_2 = 0; count_2 < 8; count_2++, count_1++)
			printf("0X%02X%s", radix_table[count_1],
				(count_2 < 7) ? ", " : "");
		printf("%s\n", (count_1 < 39) ? "," : "");
	}
	printf("};\n\n");
	printf("/* %s */\n\n",
"***********************************************************************");
}

#endif /* TEST_MAIN */


