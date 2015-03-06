/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	STRFUNCS String and Memory Functions Library Module							*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Checks to determines if a string is a valid number.

	Revision History	:	1990-03-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1990 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*    Include necessary header files . . .                                 */
/*	***********************************************************************	*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int STR_CheckValueSCharString(const char *string_ptr, char *error_text)
#else
int STR_CheckValueSCharString(string_ptr, error_text)
const char *string_ptr;
char       *error_text;
#endif /* #ifndef NARGS */
{
	int    return_code;
	double tmp_double;

	if ((return_code = STR_CheckSIntString(string_ptr, error_text)) ==
		STRFUNCS_SUCCESS) {
		tmp_double = atof(string_ptr);
		if ((tmp_double < ((double) SCHAR_MIN)) ||
			 (tmp_double > ((double) SCHAR_MAX))) {
			if (error_text != NULL)
				sprintf(error_text,
					"String value ('%-.500s') exceeds range (%d to %d, inclusive).",
					string_ptr, SCHAR_MIN, SCHAR_MAX);
			return_code = STRFUNCS_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int STR_CheckValueUCharString(const char *string_ptr, char *error_text)
#else
int STR_CheckValueUCharString(string_ptr, error_text)
const char *string_ptr;
char       *error_text;
#endif /* #ifndef NARGS */
{
	int    return_code;
	double tmp_double;

	if ((return_code = STR_CheckUIntString(string_ptr, error_text)) ==
		STRFUNCS_SUCCESS) {
		tmp_double = atof(string_ptr);
		if ((tmp_double < 0.0) ||
			 (tmp_double > ((double) UCHAR_MAX))) {
			if (error_text != NULL)
				sprintf(error_text,
					"String value ('%-.500s') exceeds range (%u to %u, inclusive).",
					string_ptr, 0, UCHAR_MAX);
			return_code = STRFUNCS_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int STR_CheckValueSShortString(const char *string_ptr, char *error_text)
#else
int STR_CheckValueSShortString(string_ptr, error_text)
const char *string_ptr;
char       *error_text;
#endif /* #ifndef NARGS */
{
	int    return_code;
	double tmp_double;

	if ((return_code = STR_CheckSIntString(string_ptr, error_text)) ==
		STRFUNCS_SUCCESS) {
		tmp_double = atof(string_ptr);
		if ((tmp_double < ((double) SHRT_MIN)) ||
			 (tmp_double > ((double) SHRT_MAX))) {
			if (error_text != NULL)
				sprintf(error_text,
					"String value ('%-.500s') exceeds range (%d to %d, inclusive).",
					string_ptr, SHRT_MIN, SHRT_MAX);
			return_code = STRFUNCS_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int STR_CheckValueUShortString(const char *string_ptr, char *error_text)
#else
int STR_CheckValueUShortString(string_ptr, error_text)
const char *string_ptr;
char       *error_text;
#endif /* #ifndef NARGS */
{
	int    return_code;
	double tmp_double;

	if ((return_code = STR_CheckUIntString(string_ptr, error_text)) ==
		STRFUNCS_SUCCESS) {
		tmp_double = atof(string_ptr);
		if ((tmp_double < 0.0) ||
			 (tmp_double > ((double) USHRT_MAX))) {
			if (error_text != NULL)
				sprintf(error_text,
					"String value ('%-.500s') exceeds range (%u to %u, inclusive).",
					string_ptr, 0, USHRT_MAX);
			return_code = STRFUNCS_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int STR_CheckValueSIntString(const char *string_ptr, char *error_text)
#else
int STR_CheckValueSIntString(string_ptr, error_text)
const char *string_ptr;
char       *error_text;
#endif /* #ifndef NARGS */
{
	int    return_code;
	double tmp_double;

	if ((return_code = STR_CheckSIntString(string_ptr, error_text)) ==
		STRFUNCS_SUCCESS) {
		tmp_double = atof(string_ptr);
		if ((tmp_double < ((double) INT_MIN)) ||
			 (tmp_double > ((double) INT_MAX))) {
			if (error_text != NULL)
				sprintf(error_text,
					"String value ('%-.500s') exceeds range (%d to %d, inclusive).",
					string_ptr, INT_MIN, INT_MAX);
			return_code = STRFUNCS_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int STR_CheckValueUIntString(const char *string_ptr, char *error_text)
#else
int STR_CheckValueUIntString(string_ptr, error_text)
const char *string_ptr;
char       *error_text;
#endif /* #ifndef NARGS */
{
	int    return_code;
	double tmp_double;

	if ((return_code = STR_CheckUIntString(string_ptr, error_text)) ==
		STRFUNCS_SUCCESS) {
		tmp_double = atof(string_ptr);
		if ((tmp_double < 0.0) ||
			 (tmp_double > ((double) UINT_MAX))) {
			if (error_text != NULL)
				sprintf(error_text,
					"String value ('%-.500s') exceeds range (%u to %u, inclusive).",
					string_ptr, 0, UINT_MAX);
			return_code = STRFUNCS_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int STR_CheckValueSLongString(const char *string_ptr, char *error_text)
#else
int STR_CheckValueSLongString(string_ptr, error_text)
const char *string_ptr;
char       *error_text;
#endif /* #ifndef NARGS */
{
	int    return_code;
	double tmp_double;

	if ((return_code = STR_CheckSIntString(string_ptr, error_text)) ==
		STRFUNCS_SUCCESS) {
		tmp_double = atof(string_ptr);
		if ((tmp_double < ((double) LONG_MIN)) ||
			 (tmp_double > ((double) LONG_MAX))) {
			if (error_text != NULL)
				sprintf(error_text,
			"String value ('%-.500s') exceeds range (%ld to %ld, inclusive).",
					string_ptr, LONG_MIN, LONG_MAX);
			return_code = STRFUNCS_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int STR_CheckValueULongString(const char *string_ptr, char *error_text)
#else
int STR_CheckValueULongString(string_ptr, error_text)
const char *string_ptr;
char       *error_text;
#endif /* #ifndef NARGS */
{
	int    return_code;
	double tmp_double;

	if ((return_code = STR_CheckUIntString(string_ptr, error_text)) ==
		STRFUNCS_SUCCESS) {
		tmp_double = atof(string_ptr);
		if ((tmp_double < 0.0) ||
			 (tmp_double > ((double) ULONG_MAX))) {
			if (error_text != NULL)
				sprintf(error_text,
			"String value ('%-.500s') exceeds range (%u to %lu, inclusive).",
					string_ptr, 0, ULONG_MAX);
			return_code = STRFUNCS_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int STR_CheckValueFloatString(const char *string_ptr,
	const char *decimal_point, char *error_text)
#else
int STR_CheckValueFloatString(string_ptr, decimal_point, error_text)
const char *string_ptr;
const char *decimal_point;
char       *error_text;
#endif /* #ifndef NARGS */
{
	int    return_code;
#ifdef FLT_MIN
# ifdef FLT_MAX
	double tmp_double;
# endif /* # ifdef FLT_MAX */
#endif /* #ifdef FLT_MIN */

	if ((return_code = STR_CheckFloatString(string_ptr, decimal_point,
		error_text)) == STRFUNCS_SUCCESS) {
#ifdef FLT_MIN
# ifdef FLT_MAX
		tmp_double = atof(string_ptr);
		if ((tmp_double < ((double) FLT_MIN)) ||
			 (tmp_double > ((double) FLT_MAX))) {
			if (error_text != NULL)
				sprintf(error_text,
					"String value ('%-.500s') exceeds range (%f to %f, inclusive).",
					string_ptr, FLT_MIN, FLT_MAX);
			return_code = STRFUNCS_FAILURE;
		}
# else
		;
# endif /* # ifdef FLT_MAX */
#endif /* #ifdef FLT_MIN */
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int STR_CheckValueDoubleString(const char *string_ptr,
	const char *decimal_point, char *error_text)
#else
int STR_CheckValueDoubleString(string_ptr, decimal_point, error_text)
const char *string_ptr;
const char *decimal_point;
char       *error_text;
#endif /* #ifndef NARGS */
{
	return(STR_CheckFloatString(string_ptr, decimal_point, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int STR_CheckSIntString(const char *string_ptr, char *error_text)
#else
int STR_CheckSIntString(string_ptr, error_text)
const char *string_ptr;
char       *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (STR_IsSIntString(string_ptr) == STRFUNCS_TRUE)
		return_code = STRFUNCS_SUCCESS;
	else {
		if (error_text != NULL)
			strcat(strcat(nstrcat(strcpy(error_text, "The string '"),
				string_ptr, 500), (strlen(string_ptr) < 500) ? "" : "<<<MORE>>>"),
				"' is not a valid signed integer value.");
		return_code = STRFUNCS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int STR_CheckUIntString(const char *string_ptr, char *error_text)
#else
int STR_CheckUIntString(string_ptr, error_text)
const char *string_ptr;
char       *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (STR_IsUIntString(string_ptr) == STRFUNCS_TRUE)
		return_code = STRFUNCS_SUCCESS;
	else {
		if (error_text != NULL)
			strcat(strcat(nstrcat(strcpy(error_text, "The string '"),
				string_ptr, 500), (strlen(string_ptr) < 500) ? "" : "<<<MORE>>>"),
				"' is not a valid unsigned integer value.");
		return_code = STRFUNCS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int STR_CheckFloatString(const char *string_ptr, const char *decimal_point,
	char *error_text)
#else
int STR_CheckFloatString(string_ptr, decimal_point, error_text)
const char   *string_ptr;
const char   *decimal_point;
char         *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (STR_IsFloatString(string_ptr, decimal_point) == STRFUNCS_TRUE)
		return_code = STRFUNCS_SUCCESS;
	else {
		if (error_text != NULL)
			strcat(strcat(nstrcat(strcpy(error_text, "The string '"),
				string_ptr, 500), (strlen(string_ptr) < 500) ? "" : "<<<MORE>>>"),
				"' is not a valid floating-point value.");
		return_code = STRFUNCS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int STR_CheckNumberString(const char *string_ptr, unsigned int flags,
	const char *decimal_point, char *error_text)
#else
int STR_CheckNumberString(string_ptr, flags, decimal_point, error_text)
const char   *string_ptr;
unsigned int  flags;
const char   *decimal_point;
char         *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (STR_IsNumberString(string_ptr, flags, decimal_point) == STRFUNCS_TRUE)
		return_code = STRFUNCS_SUCCESS;
	else {
		if (error_text != NULL)
			strcat(strcat(nstrcat(strcpy(error_text, "The string '"),
				string_ptr, 500), (strlen(string_ptr) < 500) ? "" : "<<<MORE>>>"),
				"' is not a valid numeric value.");
		return_code = STRFUNCS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int STR_CheckNumberStringBasic(const char *string_ptr,
	unsigned int string_length, unsigned int flags, const char *decimal_point,
	char *error_text)
#else
int STR_CheckNumberStringBasic(string_ptr, string_length, flags,
	decimal_point, error_text)
const char   *string_ptr;
unsigned int  string_length;
unsigned int  flags;
const char   *decimal_point;
char         *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (STR_IsNumberStringBasic(string_ptr, string_length, flags,
		decimal_point) == STRFUNCS_TRUE)
		return_code = STRFUNCS_SUCCESS;
	else {
		if (error_text != NULL)
			strcat(strcat(nstrcat(strcpy(error_text, "The string '"),
				string_ptr, 500), (strlen(string_ptr) < 500) ? "" : "<<<MORE>>>"),
				"' is not a valid numeric value.");
		return_code = STRFUNCS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

