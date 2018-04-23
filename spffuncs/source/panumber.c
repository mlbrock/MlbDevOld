/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Specification Parse Facility (SPF) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Parses numeric strings.

	Revision History	:	1995-08-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2018.
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
#include <stdlib.h>
#include <string.h>

#include <strfuncs.h>

#include "spffunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int SPF_PARSE_CharInt(const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	char *char_ptr, char *error_text)
#else
int SPF_PARSE_CharInt(spec_ptr, parse_ptr, char_ptr, error_text)
const SPF_SPEC  *spec_ptr;
const SPF_PARSE *parse_ptr;
char            *char_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int    return_code;
	double tmp_double;

	if ((return_code = SPF_PARSE_Double(spec_ptr, parse_ptr, &tmp_double,
		error_text)) == SPF_SUCCESS)
		*char_ptr = ((char) tmp_double);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int SPF_PARSE_UCharInt(const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	unsigned char  *u_char_ptr, char *error_text)
#else
int SPF_PARSE_UCharInt(spec_ptr, parse_ptr, u_char_ptr, error_text)
const SPF_SPEC  *spec_ptr;
const SPF_PARSE *parse_ptr;
unsigned char   *u_char_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int    return_code;
	double tmp_double;

	if ((return_code = SPF_PARSE_Double(spec_ptr, parse_ptr, &tmp_double,
		error_text)) == SPF_SUCCESS)
		*u_char_ptr = ((unsigned char) tmp_double);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int SPF_PARSE_ShortInt(const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	short *short_ptr, char *error_text)
#else
int SPF_PARSE_ShortInt(spec_ptr, parse_ptr, short_ptr, error_text)
const SPF_SPEC  *spec_ptr;
const SPF_PARSE *parse_ptr;
short           *short_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int    return_code;
	double tmp_double;

	if ((return_code = SPF_PARSE_Double(spec_ptr, parse_ptr, &tmp_double,
		error_text)) == SPF_SUCCESS)
		*short_ptr = ((short) tmp_double);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int SPF_PARSE_UShortInt(const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	unsigned short *u_short_ptr, char *error_text)
#else
int SPF_PARSE_UShortInt(spec_ptr, parse_ptr, u_short_ptr, error_text)
const SPF_SPEC  *spec_ptr;
const SPF_PARSE *parse_ptr;
unsigned short  *u_short_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int    return_code;
	double tmp_double;

	if ((return_code = SPF_PARSE_Double(spec_ptr, parse_ptr, &tmp_double,
		error_text)) == SPF_SUCCESS)
		*u_short_ptr = ((unsigned short) tmp_double);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int SPF_PARSE_Int(const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	int *int_ptr, char *error_text)
#else
int SPF_PARSE_Int(spec_ptr, parse_ptr, int_ptr, error_text)
const SPF_SPEC  *spec_ptr;
const SPF_PARSE *parse_ptr;
int             *int_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int    return_code;
	double tmp_double;

	if ((return_code = SPF_PARSE_Double(spec_ptr, parse_ptr, &tmp_double,
		error_text)) == SPF_SUCCESS)
		*int_ptr = ((int) tmp_double);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int SPF_PARSE_UInt(const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	unsigned int *u_int_ptr, char *error_text)
#else
int SPF_PARSE_UInt(spec_ptr, parse_ptr, u_int_ptr, error_text)
const SPF_SPEC  *spec_ptr;
const SPF_PARSE *parse_ptr;
unsigned int    *u_int_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int    return_code;
	double tmp_double;

	if ((return_code = SPF_PARSE_Double(spec_ptr, parse_ptr, &tmp_double,
		error_text)) == SPF_SUCCESS)
		*u_int_ptr = ((unsigned int) tmp_double);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int SPF_PARSE_LongInt(const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	long *long_ptr, char *error_text)
#else
int SPF_PARSE_LongInt(spec_ptr, parse_ptr, long_ptr, error_text)
const SPF_SPEC  *spec_ptr;
const SPF_PARSE *parse_ptr;
long            *long_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int    return_code;
	double tmp_double;

	if ((return_code = SPF_PARSE_Double(spec_ptr, parse_ptr, &tmp_double,
		error_text)) == SPF_SUCCESS)
		*long_ptr = ((long) tmp_double);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int SPF_PARSE_ULongInt(const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	unsigned long *u_long_ptr, char *error_text)
#else
int SPF_PARSE_ULongInt(spec_ptr, parse_ptr, u_long_ptr, error_text)
const SPF_SPEC  *spec_ptr;
const SPF_PARSE *parse_ptr;
unsigned long   *u_long_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int    return_code;
	double tmp_double;

	if ((return_code = SPF_PARSE_Double(spec_ptr, parse_ptr, &tmp_double,
		error_text)) == SPF_SUCCESS)
		*u_long_ptr = ((unsigned long) tmp_double);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int SPF_PARSE_Float(const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	float *float_ptr, char *error_text)
#else
int SPF_PARSE_Float(spec_ptr, parse_ptr, float_ptr, error_text)
const SPF_SPEC  *spec_ptr;
const SPF_PARSE *parse_ptr;
float           *float_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int    return_code;
	double tmp_double;

	if ((return_code = SPF_PARSE_Double(spec_ptr, parse_ptr, &tmp_double,
		error_text)) == SPF_SUCCESS)
		*float_ptr = ((float) tmp_double);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int SPF_PARSE_Double(const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	double *double_ptr, char *error_text)
#else
int SPF_PARSE_Double(spec_ptr, parse_ptr, double_ptr, error_text)
const SPF_SPEC  *spec_ptr;
const SPF_PARSE *parse_ptr;
double          *double_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code;
	SPF_PARSE    tmp_parse;
	unsigned int end_index;
	unsigned int point_index;
	char         double_buffer[256];
	char         min_buffer[256];
	char         max_buffer[256];
	char         tmp_error_text[SPF_MAX_ERROR_TEXT];

	if ((return_code = SPF_GetSubParse(parse_ptr, &tmp_parse, error_text)) ==
		SPF_SUCCESS) {
		if (((getnumstr_basic(tmp_parse.text, 0, tmp_parse.length - 1, ".",
			NULL, &end_index)) != STRFUNCS_TRUE) ||
			(end_index != (tmp_parse.length - 1))) {
			SPF_GetLocationLineFile(parse_ptr, 500, tmp_error_text);
			sprintf(error_text, "%s '%s()' %s ('%-.*s') %s %s.",
				"The number contained in the", spec_ptr->name, "definition",
				(tmp_parse.length > 500) ? 500 : ((int) tmp_parse.length),
				tmp_parse.text, tmp_error_text, "is invalid");
			return_code = SPF_PARSE_FAILURE;
		}
		else if (tmp_parse.length > (sizeof(double_buffer) - 1)) {
			SPF_GetLocationLineFile(parse_ptr, 500, tmp_error_text);
			sprintf(error_text, "%s '%s()' %s ('%-.*s') (%u) %s %s (%u).",
				"The length of the number contained in the", spec_ptr->name,
				"definition", (tmp_parse.length > 500) ? 500 :
				((int) tmp_parse.length), tmp_parse.text, tmp_parse.length,
				tmp_error_text, "exceeds the maximum length",
				sizeof(double_buffer) - 1);
			return_code = SPF_PARSE_FAILURE;
		}
		else {
			nstrcpy(double_buffer, tmp_parse.text, tmp_parse.length);
			*double_ptr = atof(double_buffer);
			if ((*double_ptr < spec_ptr->min_value) ||
				(*double_ptr > spec_ptr->max_value)) {
				SPF_GetLocationLineFile(parse_ptr, 500, tmp_error_text);
				sprintf(min_buffer, "%100.50f", spec_ptr->min_value);
				sprintf(max_buffer, "%100.50f", spec_ptr->max_value);
				if ((point_index = idxrchr(ltrim(rtrimx(min_buffer, "0")),
					'.')) == (strlen(min_buffer) - 1))
					min_buffer[point_index] = '\0';
				if ((point_index = idxrchr(ltrim(rtrimx(max_buffer, "0")),
					'.')) == (strlen(max_buffer) - 1))
					max_buffer[point_index] = '\0';
				sprintf(error_text,
					"%s '%s()' %s ('%-.500s') %s %s --- %s '%s' to '%s', %s.",
					"The number contained in the", spec_ptr->name, "definition",
					double_buffer, tmp_error_text, "is invalid",
					"should be in the range of", min_buffer, max_buffer,
					"inclusive");
				return_code = SPF_PARSE_FAILURE;
			}
		}
		SPF_FREE_Parse(&tmp_parse);
	}

	return(return_code);
}
/*	***********************************************************************	*/

