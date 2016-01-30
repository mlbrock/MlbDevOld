/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	STRFUNCS String and Memory Functions Library Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Formats a double numeric value as a text string.

	Revision History	:	1996-04-06 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <limits.h>
#include <stdio.h>
#include <string.h>

#ifdef _MSC_VER
# pragma warning(disable:4514)
#endif /* # ifdef _MSC_VER */
#include <math.h>

#include "strfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
COMPAT_EXTERN_DATA_DECL const STRFUNCS_VALUE_NAME
	STRFUNCS_NumberTextList[];
COMPAT_EXTERN_DATA_DECL const unsigned int       
	STRFUNCS_NumberTextCount;
COMPAT_EXTERN_DATA_DECL const STRFUNCS_VALUE_NAME
	STRFUNCS_MetricNumberTextList[];
COMPAT_EXTERN_DATA_DECL const unsigned int       
	STRFUNCS_MetricNumberTextCount;
COMPAT_EXTERN_DATA_DECL const STRFUNCS_VALUE_NAME
	STRFUNCS_BritishNumberTextList[];
COMPAT_EXTERN_DATA_DECL const unsigned int       
	STRFUNCS_BritishNumberTextCount;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Function prototypes for functions private to this module . . .				*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(char *get_double_text_basic_core, (double in_double,
	unsigned int name_count, const STRFUNCS_D_VALUE_NAME *name_list,
	unsigned int ulong_name_count, const STRFUNCS_VALUE_NAME *ulong_name_list,
	char *out_string));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
COMPAT_EXTERN_DATA_DEF const STRFUNCS_D_VALUE_NAME
	STRFUNCS_D_NumberTextList[] = {
	{	  1E+3,	"thousand",	 			},
	{	  1E+6,	"million",	 			},
	{	  1E+9,	"billion",	  			},
	{	 1E+12,	"trillion"				},
	{	 1E+15,	"quadrillion"			},
	{	 1E+18,	"quintillion"			},
	{	 1E+21,	"sextillion"			},
	{	 1E+24,	"septillion",			},
	{	 1E+27,	"octillion",			},
	{	 1E+30,	"nonillion",			},
	{	 1E+33,	"decillion",			},
	{	 1E+36,	"undecillion"			},
	{	 1E+39,	"duodecillion"			},
	{	 1E+42,	"tredecillion"			},
	{	 1E+45,	"quattuordecillion"	},
	{	 1E+48,	"quindecillion"		},
	{	 1E+51,	"sexdecillion"			},
	{	 1E+54,	"septendecillion"		},
	{	 1E+57,	"octodecillion",		},
	{	 1E+60,	"novemdecillion"		},
	{	 1E+63,	"vigintillion"			},
	{	1E+303,	"centillion"			}
};
COMPAT_EXTERN_DATA_DEF const unsigned int STRFUNCS_D_NumberTextCount =
	sizeof(STRFUNCS_D_NumberTextList) / sizeof(STRFUNCS_D_NumberTextList[0]);
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
COMPAT_EXTERN_DATA_DEF const STRFUNCS_D_VALUE_NAME
	STRFUNCS_D_MetricNumberTextList[] = {
	{	  1E+3,	"kilo",	 				},
	{	  1E+6,	"mega",	 				},
	{	  1E+9,	"giga",	  				},
	{	 1E+12,	"tera"					},
	{	 1E+15,	"peta"					},
	{	 1E+18,	"exa"						},
/*
	{	 1E+21,	"sextillion"			},
	{	 1E+24,	"septillion",			},
	{	 1E+27,	"octillion",			},
	{	 1E+30,	"nonillion",			}
	{	 1E+33,	"decillion",			}
	{	 1E+36,	"undecillion"			},
	{	 1E+39,	"duodecillion"			},
	{	 1E+42,	"tredecillion"			},
	{	 1E+45,	"quattuordecillion"	},
	{	 1E+48,	"quindecillion"		},
	{	 1E+51,	"sexdecillion"			},
	{	 1E+54,	"septendecillion"		},
	{	 1E+57,	"octodecillion",		},
	{	 1E+60,	"novemdecillion"		},
	{	 1E+63,	"vigintillion"			},
	{	1E+303,	"centillion"			}
*/
};
COMPAT_EXTERN_DATA_DEF const unsigned int STRFUNCS_D_MetricNumberTextCount =
	sizeof(STRFUNCS_D_MetricNumberTextList) /
	sizeof(STRFUNCS_D_MetricNumberTextList[0]);
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
COMPAT_EXTERN_DATA_DEF const STRFUNCS_D_VALUE_NAME
	STRFUNCS_D_BritishNumberTextList[] = {
	{	  1E+3,	"thousand",	 			},
	{	  1E+6,	"million",	 			},
	{	  1E+9,	"milliard",	  			},
	{	 1E+12,	"billion",	  			},
	{	 1E+18,	"trillion"				},
	{	 1E+24,	"quadrillion"			},
	{	 1E+30,	"quintillion"			},
	{	 1E+36,	"sextillion"			},
	{	 1E+42,	"septillion",			},
	{	 1E+48,	"octillion",			},
	{	 1E+54,	"nonillion",			},
	{	 1E+60,	"decillion",			},
	{	 1E+66,	"undecillion"			},
	{	 1E+72,	"duodecillion"			},
	{	 1E+78,	"tredecillion"			},
	{	 1E+84,	"quattuordecillion"	},
	{	 1E+90,	"quindecillion"		},
	{	 1E+96,	"sexdecillion"			},
	{	1E+102,	"septendecillion"		},
	{	1E+108,	"octodecillion",		},
	{	1E+114,	"novemdecillion"		},
	{	1E+120,	"vigintillion"			}
/*
	Can't include British centillion because IEEE permits a maximum of 10^308.
	{	1E+600,	"centillion"			}
*/
};
COMPAT_EXTERN_DATA_DEF const unsigned int STRFUNCS_D_BritishNumberTextCount =
	sizeof(STRFUNCS_D_BritishNumberTextList) /
	sizeof(STRFUNCS_D_BritishNumberTextList[0]);
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	get_double_text

	SYNOPSIS		:	result_text = get_double_text(in_double, out_string);

						char          *result_text;

						double         in_double;

						unsigned int   decimal_places;

						char          *out_string;

	DESCRIPTION	:	Formats an double numeric value as a text string using the
						American formatting specification.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_double`` is the double value to be formatted.

						(.) ``decimal_places`` is the number of decimal places with
						which the number is to be formatted by this function.

						(.) ``out_string`` points to the area into which the
						formatted string is to be placed.

	RETURNS		:	A pointer to the string used to store the formatted string
						(that is, ``out_string``).

	NOTES			:	This function performs formatting using the absolute value
						of ``in_double``. To format negative values as a string,
						first invoke this function then prepend to the resulting
						string the word ''minus'' or ''negative''.

						Integer values with a magnitude less than or equal to
						the C standard library ``stdlib`` manifest constant
						''ULONG_MAX'' may be formatted using the sister function
						``get_ulong_text``.

						You can remove trailing zeroes after the decimal point in
						the text which results from this function by using the
						function ``drop_double_text_zeroes``.

	CAVEATS		:	

	SEE ALSO		:	get_ulong_text
						get_double_text_basic

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2016 Michael L. Brock

	OUTPUT INDEX:	get_double_text
						Numeric Formatting Functions:get_double_text
						STRFUNCS:Numeric Formatting Functions:get_double_text
						String Functions:See STRFUNCS

	PUBLISH XREF:	get_double_text

	PUBLISH NAME:	get_double_text

	ENTRY CLASS	:	Numeric Formatting Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *get_double_text(double in_double, unsigned int decimal_places,
	char *out_string)
#else
char *get_double_text(in_double, decimal_places, out_string)
double        in_double;
unsigned int  decimal_places;
char         *out_string;
#endif /* #ifndef NARGS */
{
	return(get_double_text_basic(in_double, decimal_places,
		STRFUNCS_D_NumberTextCount, STRFUNCS_D_NumberTextList,
		STRFUNCS_NumberTextCount, STRFUNCS_NumberTextList, out_string));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	get_double_text_basic

	SYNOPSIS		:	result_text = get_double_text_basic(in_double, name_count,
							name_list, out_string);

						char                        *result_text;

						double                       in_double;

						unsigned int                 decimal_places;

						unsigned int                 name_count;

						const STRFUNCS_D_VALUE_NAME *name_list;

						unsigned int                 ulong_name_count;

						const STRFUNCS_VALUE_NAME   *ulong_name_list;

						char                        *out_string;

	DESCRIPTION	:	Formats an double numeric value as a text string
						using the formatting specification passed as parameters
						``name_count``, ``name_list``, ``ulong_name_count`` and
						``ulong_name_list``.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_double`` is the double value to be formatted.

						(.) ``decimal_places`` is the number of decimal places with
						which the number is to be formatted by this function.

						(.) ``name_count`` is the number of elements in the
						formatting specification array ``name_list``.

						(.) ``name_list`` points to the array of structures of
						type ``STRFUNCS_D_VALUE_NAME`` to be used as the formatting
						specification array.

						(.) ``ulong_name_count`` is the number of elements in the
						formatting specification array ``ulong_name_list``.

						(.) ``ulong_name_list`` points to the array of structures of
						type ``STRFUNCS_VALUE_NAME`` to be used as the formatting
						specification array.

						(.) ``out_string`` points to the area into which the
						formatted string is to be placed.

	RETURNS		:	A pointer to the string used to store the formatted string
						(that is, ``out_string``).

	NOTES			:	If ``name_list`` is ``NULL`` then the numeric value will
						be formatted using American conventions.

						This function performs formatting using the absolute value
						of ``in_double``. To format negative values as a string,
						first invoke this function then prepend to the resulting
						string the word ''minus'' or ''negative''.

						Integer values with a magnitude less than or equal to
						the C standard library ``stdlib`` manifest constant
						''ULONG_MAX'' may be formatted using the sister function
						``get_ulong_text_basic``.

						You can remove trailing zeroes after the decimal point in
						the text which results from this function by using the
						function ``drop_double_text_zeroes``.

	CAVEATS		:	

	SEE ALSO		:	get_ulong_text_basic
						get_double_text

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2016 Michael L. Brock

	OUTPUT INDEX:	get_double_text_basic
						Numeric Formatting Functions:get_double_text_basic
						STRFUNCS:Numeric Formatting Functions:get_double_text_basic
						String Functions:See STRFUNCS

	PUBLISH XREF:	get_double_text_basic

	PUBLISH NAME:	get_double_text_basic

	ENTRY CLASS	:	Numeric Formatting Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *get_double_text_basic(double in_double, unsigned int decimal_places,
	unsigned int name_count, const STRFUNCS_D_VALUE_NAME *name_list,
	unsigned int ulong_name_count, const STRFUNCS_VALUE_NAME *ulong_name_list,
	char *out_string)
#else
char *get_double_text_basic(in_double, decimal_places, name_count, name_list,
	ulong_name_count, ulong_name_list, out_string)
double                       in_double;
unsigned int                 decimal_places;
unsigned int                 name_count;
const STRFUNCS_D_VALUE_NAME *name_list;
unsigned int                 ulong_name_count;
const STRFUNCS_VALUE_NAME   *ulong_name_list;
char                        *out_string;
#endif /* #ifndef NARGS */
{
	double  integer;
	char   *tmp_ptr;
	char    buffer[STRFUNCS_D_MAX_DECIMAL_PLACES + 1];

	in_double      = fabs(in_double);
	decimal_places = (decimal_places > STRFUNCS_D_MAX_DECIMAL_PLACES) ?
		STRFUNCS_D_MAX_DECIMAL_PLACES : decimal_places;

	get_double_text_basic_core(floor(in_double), name_count, name_list,
		ulong_name_count, ulong_name_list, out_string);

	if (decimal_places) {
		strcat(out_string, " point");
		sprintf(buffer, "%*.*f", 0, ((int) decimal_places),
			modf(in_double, &integer));
		tmp_ptr = buffer + 2;
		while (*tmp_ptr) {
			strcat(out_string, " ");
			get_ulong_text_basic(((unsigned long) (*tmp_ptr++ - '0')),
				ulong_name_count, ulong_name_list,
				out_string + strlen(out_string));
		}
	}

	return(out_string);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	drop_double_text_zeroes

   SYNOPSIS    :	result_text = drop_double_text_zeroes(out_string);

						char *result_text;

						char *out_string;

   DESCRIPTION :	Removes trailing zeroes in the fractional portion of a
						number formatted as a text string.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``out_string`` points to the string from which the
						zeroes are to be removed.

	RETURNS		:	A pointer to the string used to store the formatted string
						(that is, ``out_string``).

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1996 - 2016 Michael L. Brock

   OUTPUT INDEX:	drop_double_text_zeroes
						Numeric Formatting Functions:drop_double_text_zeroes
						STRFUNCS:Numeric Formatting Functions:drop_double_text_zeroes
						String Functions:See STRFUNCS

   PUBLISH XREF:	drop_double_text_zeroes

   PUBLISH NAME:	drop_double_text_zeroes

	ENTRY CLASS	:	Numeric Formatting Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *drop_double_text_zeroes(char *out_string)
#else
char *drop_double_text_zeroes(out_string)
char *out_string;
#endif /* #ifndef NARGS */
{
	unsigned int length;

	if (strstr(out_string, " point ")) {
		length = strlen(out_string);
		while (!strcmp(out_string + (length - 5), " zero")) {
			length             -= 5;
			out_string[length]  = '\0';
		}
		if (!strcmp(out_string + (length - 6), " point"))
			out_string[length - 6]  = '\0';
	}

	return(out_string);
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
static char *get_double_text_basic_core(double in_double,
	unsigned int name_count, const STRFUNCS_D_VALUE_NAME *name_list,
	unsigned int ulong_name_count, const STRFUNCS_VALUE_NAME *ulong_name_list,
	char *out_string)
#else
static char *get_double_text_basic_core(in_double, name_count, name_list,
	ulong_name_count, ulong_name_list, out_string)
double                       in_double;
unsigned int                 name_count;
const STRFUNCS_D_VALUE_NAME *name_list;
unsigned int                 ulong_name_count;
const STRFUNCS_VALUE_NAME   *ulong_name_list;
char                        *out_string;
#endif /* #ifndef NARGS */
{
	unsigned int                 count_1;
   double                       tmp_double;
	const STRFUNCS_D_VALUE_NAME *name_ptr;

	name_count = (name_list != NULL) ? name_count : STRFUNCS_D_NumberTextCount;
	name_list  = (name_list != NULL) ? name_list  : STRFUNCS_D_NumberTextList;

	if (in_double <= ((double) ULONG_MAX))
		get_ulong_text_basic(((unsigned long) in_double), ulong_name_count,
			ulong_name_list, out_string);
	else {
		*out_string = '\0';
		for (count_1 = name_count - 1; count_1 > 0; count_1--) {
			if (in_double <= ((double) ULONG_MAX))
				break;
			name_ptr = name_list + count_1;
			if (in_double >= name_ptr->value) {
				if (*out_string)
					strcat(out_string, " ");
				if ((tmp_double = floor(fmod(in_double, name_ptr->value))) > 0.0) {
					get_double_text_basic_core(floor(in_double / name_ptr->value),
						name_count, name_list, ulong_name_count, ulong_name_list,
						out_string + strlen(out_string));
					strcat(strcat(out_string, " "), name_ptr->name);
				}
				else {
					get_double_text_basic_core(floor(in_double / name_ptr->value),
						name_count, name_list, ulong_name_count, ulong_name_list,
						out_string + strlen(out_string));
					strcat(strcat(out_string, " "), name_ptr->name);
            }
				in_double = tmp_double;
				if (!in_double)
					break;
			}
		}
		if (in_double && (in_double <= ((double) ULONG_MAX))) {
			strcat(out_string, " ");
			get_ulong_text_basic(((unsigned long) in_double),
				ulong_name_count, ulong_name_list,
				out_string + strlen(out_string));
		}
	}

	return(out_string);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char                        *name;
	const unsigned int          *ulong_count;
	const STRFUNCS_VALUE_NAME   *ulong_list;
	const unsigned int          *double_count;
	const STRFUNCS_D_VALUE_NAME *double_list;
} TEST_DATA;

static const unsigned long TEST_ULongList[]    = {
	0L,		1L,	2L,	3L,	4L,	5L,	10L,	100L,	1000L,	12345L,
	123456789L,	1234567890L
};
static const unsigned int  TEST_ULongCount     =
	sizeof(TEST_ULongList) / sizeof(TEST_ULongList[0]);

static const TEST_DATA     TEST_NameTypeList[] = {
	{	"American",
		&STRFUNCS_NumberTextCount,				STRFUNCS_NumberTextList,
		&STRFUNCS_D_NumberTextCount,			STRFUNCS_D_NumberTextList
	},
	{	"Metric",
		&STRFUNCS_MetricNumberTextCount,		STRFUNCS_MetricNumberTextList,
		&STRFUNCS_D_MetricNumberTextCount,	STRFUNCS_D_MetricNumberTextList
	},
	{	"British",
		&STRFUNCS_BritishNumberTextCount,	STRFUNCS_BritishNumberTextList,
		&STRFUNCS_D_BritishNumberTextCount,	STRFUNCS_D_BritishNumberTextList
	}
};
static const unsigned int  TEST_NameTypeCount  =
	sizeof(TEST_NameTypeList) / sizeof(TEST_NameTypeList[0]);

COMPAT_FN_DECL(       int  main,             (int argc, char **argv));
COMPAT_FN_DECL_STATIC(int  TEST_DoULongTest, (void));
COMPAT_FN_DECL_STATIC(void TEST_DoTest,      (int argc, char **argv));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int           return_code = STRFUNCS_SUCCESS;
	unsigned long count_1;
	char          buffer[1024];

	fprintf(stderr, "Test routine for function 'get_double_text()'\n");
	fprintf(stderr, "---- ------- --- -------- -------------------\n\n");

	if (argc > 1)
		TEST_DoTest(argc, argv);
	else if ((return_code = TEST_DoULongTest()) == STRFUNCS_SUCCESS) {
		for (count_1 = 0L; count_1 <= ULONG_MAX; count_1++)
			printf("%10lu: %s\n", count_1, get_double_text(((double) count_1),
				0, buffer));
	}

	return(return_code);
}

static int TEST_DoULongTest()
{
	
	int          return_code = STRFUNCS_SUCCESS;
	unsigned int count_1;
   unsigned int count_2;
	char         buffer_1[1024];
	char         buffer_2[1024];

	for (count_1 = 0; count_1 < TEST_ULongCount; count_1++) {
		for (count_2 = 0; count_2 < TEST_NameTypeCount; count_2++) {
			get_ulong_text_basic(TEST_ULongList[count_1],
				*TEST_NameTypeList[count_2].ulong_count,
				TEST_NameTypeList[count_2].ulong_list, buffer_1);
			get_double_text_basic(((double) TEST_ULongList[count_1]), 0,
				*TEST_NameTypeList[count_2].double_count,
				TEST_NameTypeList[count_2].double_list,
				*TEST_NameTypeList[count_2].ulong_count,
				TEST_NameTypeList[count_2].ulong_list, buffer_2);
			if (strcmp(buffer_1, buffer_2)) {
				fprintf(stderr,
					"%s '%lu' %s %s: ulong='%s' versus double='%s'.\n",
					"Attempt to compare the results of converting the value",
					TEST_ULongList[count_1], "to a string using the 'ulong' and",
					"'double' functions failed", buffer_1, buffer_2);
				return_code = STRFUNCS_FAILURE;
				goto EXIT_FUNCTION;
			}
		}
	}

EXIT_FUNCTION:

	return(return_code);
}

#ifndef NARGS
static void TEST_DoTest(int argc, char **argv)
#else
static void TEST_DoTest(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	
	unsigned int                 double_name_count = STRFUNCS_D_NumberTextCount;
	const STRFUNCS_D_VALUE_NAME *double_name_list  = STRFUNCS_D_NumberTextList;
	unsigned int                 ulong_name_count  = STRFUNCS_NumberTextCount;
	const STRFUNCS_VALUE_NAME   *ulong_name_list   = STRFUNCS_NumberTextList;
	unsigned long                count_1;
	double                       tmp_double;
	char                         buffer[1024];

	for (count_1 = 1L; count_1 < ((unsigned long) argc); count_1++) {
		if ((!STRFUNCS_stricmp(argv[((int) count_1)], "AMERICAN")) ||
			(!STRFUNCS_stricmp(argv[((int) count_1)], "US"))) {
			double_name_count = STRFUNCS_D_NumberTextCount;
			double_name_list  = STRFUNCS_D_NumberTextList;
			ulong_name_count  = STRFUNCS_NumberTextCount;
			ulong_name_list   = STRFUNCS_NumberTextList;
			fprintf(stderr, "---> Switched to '%s'\n", argv[((int) count_1)]);
		}
		else if (!STRFUNCS_stricmp(argv[((int) count_1)], "METRIC")) {
			double_name_count = STRFUNCS_D_MetricNumberTextCount;
			double_name_list  = STRFUNCS_D_MetricNumberTextList;
			ulong_name_count  = STRFUNCS_MetricNumberTextCount;
			ulong_name_list   = STRFUNCS_MetricNumberTextList;
			fprintf(stderr, "---> Switched to '%s'\n", argv[((int) count_1)]);
		}
		else if ((!STRFUNCS_stricmp(argv[((int) count_1)], "BRITISH")) ||
			(!STRFUNCS_stricmp(argv[((int) count_1)], "UK"))) {
			double_name_count = STRFUNCS_D_BritishNumberTextCount;
			double_name_list  = STRFUNCS_D_BritishNumberTextList;
			ulong_name_count  = STRFUNCS_BritishNumberTextCount;
			ulong_name_list   = STRFUNCS_BritishNumberTextList;
			fprintf(stderr, "---> Switched to '%s'\n", argv[((int) count_1)]);
		}
		else {
			tmp_double = strtod(argv[((unsigned int) count_1)], NULL);
			printf("%32.6f: %s\n", tmp_double, get_double_text_basic(tmp_double,
				6, double_name_count, double_name_list, ulong_name_count,
				ulong_name_list, buffer));
			printf("%32.32s: %s\n", " ", drop_double_text_zeroes(buffer));
		}
	}
}

#endif /* #ifdef TEST_MAIN */

