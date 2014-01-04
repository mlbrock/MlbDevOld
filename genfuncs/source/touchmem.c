/* *********************************************************************** */
/* *********************************************************************** */
/*	GENFUNCS General Functions Library Source Module								*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Touches a specified area of memory to ensure that
								it is accessible.

	Revision History	:	1995-11-02 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/*    Include necessary header files . . .                                 */
/* *********************************************************************** */

#include <string.h>

#include "genfunci.h"

/* *********************************************************************** */

/*	***********************************************************************	*/
#ifndef NARGS
int GEN_TouchErrorText(char *error_text)
#else
int GEN_TouchErrorText(error_text)
char *error_text;
#endif /* #ifndef NARGS */
{
	return(GEN_TouchErrorTextBasic(error_text, GENFUNCS_MAX_ERROR_TEXT));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int GEN_ClearErrorText(char *error_text)
#else
int GEN_ClearErrorText(error_text)
char *error_text;
#endif /* #ifndef NARGS */
{
	return(GEN_ClearErrorTextBasic(error_text, GENFUNCS_MAX_ERROR_TEXT));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int GEN_TouchErrorTextBasic(char *error_text, unsigned int error_text_length)
#else
int GEN_TouchErrorTextBasic(error_text, error_text_length)
char         *error_text;
unsigned int  error_text_length;
#endif /* #ifndef NARGS */
{
	return(GEN_TouchWrite(error_text, error_text_length,
		"'error_text' parameter", NULL));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int GEN_ClearErrorTextBasic(char *error_text, unsigned int error_text_length)
#else
int GEN_ClearErrorTextBasic(error_text, error_text_length)
char         *error_text;
unsigned int  error_text_length;
#endif /* #ifndef NARGS */
{
	return(GEN_TouchClear(error_text, error_text_length,
		"'error_text' parameter", NULL));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int GEN_TouchRead(const void *data_ptr, unsigned int data_length,
	const char *data_name, char *error_text)
#else
int GEN_TouchRead(data_ptr, data_length, data_name, error_text)
const void   *data_ptr;
unsigned int  data_length;
const char   *data_name;
char         *error_text;
#endif /* #ifndef NARGS */
{
	int                    return_code = GENFUNCS_SUCCESS;
#ifndef _Windows
	volatile unsigned long tmp_value   = 0L;
#endif /* #ifndef _Windows */

	data_name = ((data_name != NULL) && *data_name) ? data_name :
		"*** UNKNOWN DATUM ***";

	if (!data_length) {
		if (error_text != NULL)
			chrcat(val2str_ptr_cat(data_ptr, strcat(nstrcat(strcpy(error_text,
				"Invalid "), data_name, 500),
				" memory touch data_length (0) for address 0x")), '.');
		return_code = GENFUNCS_FAILURE;
	}
	else if (data_ptr == NULL) {
		if (error_text != NULL)
			strcat(nstrcat(strcpy(error_text, "Invalid "), data_name, 500),
				" pointer ('NULL').");
		return_code = GENFUNCS_FAILURE;
	}
	else {
#ifdef _Windows
		if (IsBadReadPtr(((void *) data_ptr), data_length)) {
			if (error_text != NULL)
				strcat(val2str_uint_cat(data_length, 10, NULL,
					strcat(val2str_ptr_cat(data_ptr,
					strcat(nstrcat(strcpy(error_text, "Invalid "), data_name, 500),
					" memory access at 0x")),
					", length ")), ": memory is not readable.");
			return_code = GENFUNCS_FAILURE;
		}
#else
		while (data_length)
			tmp_value += ((volatile unsigned char *) data_ptr)[--data_length];
#endif /* #ifdef _Windows */
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int GEN_TouchWrite(void *data_ptr, unsigned int data_length,
	const char *data_name, char *error_text)
#else
int GEN_TouchWrite(data_ptr, data_length, data_name, error_text)
void         *data_ptr;
unsigned int  data_length;
const char   *data_name;
char         *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = GENFUNCS_SUCCESS;

#ifdef _Windows
	if (!data_length) {
		if (error_text != NULL)
			chrcat(val2str_ptr_cat(data_ptr, strcat(nstrcat(strcpy(error_text,
				"Invalid "), data_name, 500),
				" memory touch data_length (0) for address 0x")), '.');
		return_code = GENFUNCS_FAILURE;
	}
	else if (data_ptr == NULL) {
		if (error_text != NULL)
			strcat(nstrcat(strcpy(error_text, "Invalid "), data_name, 500),
				" pointer ('NULL').");
		return_code = GENFUNCS_FAILURE;
	}
	else if (IsBadWritePtr(data_ptr, data_length)) {
		if (error_text != NULL)
			strcat(val2str_uint_cat(data_length, 10, NULL,
				strcat(val2str_ptr_cat(data_ptr,
				strcat(nstrcat(strcpy(error_text, "Invalid "), data_name, 500),
				" memory access at ")),
				", length ")), ": memory is not writable.");
		return_code = GENFUNCS_FAILURE;
	}
#else
	return_code = GEN_TouchRead(data_ptr, data_length, data_name,
		error_text);
#endif /* #ifdef _Windows */

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int GEN_TouchClear(void *data_ptr, unsigned int data_length,
	const char *data_name, char *error_text)
#else
int GEN_TouchClear(data_ptr, data_length, data_name, error_text)
void         *data_ptr;
unsigned int  data_length;
const char   *data_name;
char         *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = GENFUNCS_SUCCESS;

	if (!data_length) {
		if (error_text != NULL)
			chrcat(val2str_ptr_cat(data_ptr, strcat(nstrcat(strcpy(error_text,
				"Invalid "), data_name, 500),
				" memory touch data_length (0) for address 0x")), '.');
		return_code = GENFUNCS_FAILURE;
	}
	else if (data_ptr == NULL) {
		if (error_text != NULL)
			strcat(nstrcat(strcpy(error_text, "Invalid "), data_name, 500),
				" pointer ('NULL').");
		return_code = GENFUNCS_FAILURE;
	}
	else {
#ifdef _Windows
		if (IsBadWritePtr(data_ptr, data_length)) {
			if (error_text != NULL)
				strcat(val2str_uint_cat(data_length, 10, NULL,
					strcat(val2str_ptr_cat(data_ptr,
					strcat(nstrcat(strcpy(error_text, "Invalid "), data_name, 500),
					" memory access at 0x")),
					", length ")), ": memory is not writable.");
			return_code = GENFUNCS_FAILURE;
		}
		else
#endif /* #ifdef _Windows */
			memset(data_ptr, '\0', data_length);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int GEN_TouchReadString(const char *string_ptr, unsigned int string_length,
	const char *string_name, char *error_text)
#else
int GEN_TouchReadString(const char *string_ptr, unsigned int string_length,
	const char *string_name, char *error_text)
#endif /* #ifndef NARGS */
{
	int                    return_code = GENFUNCS_SUCCESS;
#ifndef _Windows
	volatile unsigned long tmp_value   = 0L;
#endif /* #ifndef _Windows */

	string_name = ((string_name != NULL) && *string_name) ? string_name :
		"*** UNKNOWN DATUM ***";

	if (!string_length) {
		if (error_text != NULL)
			chrcat(val2str_ptr_cat(string_ptr, strcat(nstrcat(strcpy(error_text,
				"Invalid "), string_name, 500),
				" memory touch string length (0) for address 0x")), '.');
		return_code = GENFUNCS_FAILURE;
	}
	else if (string_ptr == NULL) {
		if (error_text != NULL)
			strcat(nstrcat(strcpy(error_text, "Invalid "), string_name, 500),
				" pointer ('NULL').");
		return_code = GENFUNCS_FAILURE;
	}
	else {
#ifdef _Windows
		if (IsBadStringPtr(string_ptr, string_length)) {
			if (error_text != NULL)
				strcat(val2str_uint_cat(string_length, 10, NULL,
					strcat(val2str_ptr_cat(string_ptr,
					strcat(nstrcat(strcpy(error_text, "Invalid "), string_name, 500),
					" string memory access at 0x")),
					", length ")), ": memory is not readable.");
			return_code = GENFUNCS_FAILURE;
		}
#else
		while (string_length && *string_ptr) {
			tmp_value = tmp_value +
         	((unsigned long) ((volatile unsigned char *) string_ptr));
			string_ptr++;
			string_length--;
		}
#endif /* #ifdef _Windows */
	}

	return(return_code);
}
/*	***********************************************************************	*/

