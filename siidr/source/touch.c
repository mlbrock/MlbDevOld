/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Single Index Internal Data Repository Library Source Module					*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Touches a specified area of memory to ensure that
								it is accessible.

	Revision History	:	1996-04-11 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Include necessary header files . . .												*/
/*	***********************************************************************	*/

#include <string.h>

#include <strfuncs.h>
#include <genfuncs.h>

#include "siidri.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_TouchCode(const void *code_ptr, char *error_text)
{
	int return_code;

	if (code_ptr == NULL) {
		if (error_text != NULL)
			strcpy(error_text, "Code/function pointer is 'NULL'.");
		return_code = SIIDR_BAD_ARGS_FAILURE;
	}
#ifdef _Windows
	else if (IsBadCodePtr(((FARPROC) ((unsigned long) code_ptr)))) {
		if (error_text != NULL)
			strcat(val2str_ptr0_cat(code_ptr, strcpy(error_text,
				"Code/function pointer ")), " is invalid.");
		return_code = SIIDR_FAILURE;
	}
#endif /* #ifdef _Windows */
	else
		return_code = SIIDR_SUCCESS;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_TouchCodeOpt(const void *code_ptr, char *error_text)
{
	return((code_ptr != NULL) ? SIIDR_TouchCode(code_ptr, error_text) :
		SIIDR_SUCCESS);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_TouchError(char *error_text)
{
	return(SIIDR_MAP_ERROR_GEN(GEN_TouchErrorTextBasic(error_text,
		SIIDR_MAX_ERROR_TEXT)));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_TouchErrorOpt(char *error_text)
{
	return((error_text != NULL) ? SIIDR_TouchError(error_text) :
		SIIDR_SUCCESS);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_ClearError(char *error_text)
{
	return(SIIDR_MAP_ERROR_GEN(GEN_ClearErrorTextBasic(error_text,
		SIIDR_MAX_ERROR_TEXT)));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_ClearErrorOpt(char *error_text)
{
	return((error_text != NULL) ? SIIDR_ClearError(error_text) :
		SIIDR_SUCCESS);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_TouchIDRRead(const SIIDR *siidr_ptr, char *error_text)
{
	return(SIIDR_TouchRead(siidr_ptr, sizeof(*siidr_ptr),
		"internal data repository ('SIIDR') structure", error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_TouchIDRWrite(SIIDR *siidr_ptr, char *error_text)
{
	return(SIIDR_TouchWrite(siidr_ptr, sizeof(*siidr_ptr),
		"internal data repository ('SIIDR') structure", error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_TouchRecordRead(const SIIDR *siidr_ptr, const void *record_ptr,
	char *error_text)
{
	char buffer[512];

	return(SIIDR_TouchRead(record_ptr, siidr_ptr->record_size,
		strcat(nstrcat(strcpy(buffer, "SIIDR "), siidr_ptr->idr_name,
		sizeof(buffer) - 100), " data record"), error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_TouchRecordReadOpt(const SIIDR *siidr_ptr, const void *record_ptr,
	char *error_text)
{
	return((record_ptr == NULL) ? SIIDR_SUCCESS :
		SIIDR_TouchRecordRead(siidr_ptr, record_ptr, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_TouchRecordWrite(const SIIDR *siidr_ptr, void *record_ptr,
	char *error_text)
{
	char buffer[512];

	return(SIIDR_TouchWrite(record_ptr, siidr_ptr->record_size,
		strcat(nstrcat(strcpy(buffer, "SIIDR "), siidr_ptr->idr_name,
		sizeof(buffer) - 100), " data record"), error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_TouchRecordWriteOpt(const SIIDR *siidr_ptr, void *record_ptr,
	char *error_text)
{
	return((record_ptr == NULL) ? SIIDR_SUCCESS :
		SIIDR_TouchRecordWrite(siidr_ptr, record_ptr, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_TouchRecordClear(const SIIDR *siidr_ptr, void *record_ptr,
	char *error_text)
{
	char buffer[512];

	return(SIIDR_TouchClear(record_ptr, siidr_ptr->record_size,
		strcat(nstrcat(strcpy(buffer, "SIIDR "), siidr_ptr->idr_name,
		sizeof(buffer) - 100), " data record"), error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_TouchRecordClearOpt(const SIIDR *siidr_ptr, void *record_ptr,
	char *error_text)
{
	return((record_ptr == NULL) ? SIIDR_SUCCESS :
		SIIDR_TouchRecordClear(siidr_ptr, record_ptr, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_TouchRead(const void *data_ptr, unsigned int data_length,
	const char *data_name, char *error_text)
{
	int  return_code;
	char gen_error_text[GENFUNCS_MAX_ERROR_TEXT];

	if ((return_code = GEN_TouchRead(data_ptr, data_length, data_name,
		gen_error_text)) != GENFUNCS_SUCCESS) {
		if (error_text != NULL)
			nstrcpy(error_text, gen_error_text, SIIDR_MAX_ERROR_TEXT - 1);
		return_code = SIIDR_MAP_ERROR_GEN(return_code);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_TouchWrite(void *data_ptr, unsigned int data_length,
	const char *data_name, char *error_text)
{
	int  return_code;
	char gen_error_text[GENFUNCS_MAX_ERROR_TEXT];

	if ((return_code = GEN_TouchWrite(data_ptr, data_length, data_name,
		gen_error_text)) != GENFUNCS_SUCCESS) {
		if (error_text != NULL)
			nstrcpy(error_text, gen_error_text, SIIDR_MAX_ERROR_TEXT - 1);
		return_code = SIIDR_MAP_ERROR_GEN(return_code);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_TouchClear(void *data_ptr, unsigned int data_length,
	const char *data_name, char *error_text)
{
	int  return_code;
	char gen_error_text[GENFUNCS_MAX_ERROR_TEXT];

	if ((return_code = GEN_TouchClear(data_ptr, data_length, data_name,
		gen_error_text)) != GENFUNCS_SUCCESS) {
		if (error_text != NULL)
			nstrcpy(error_text, gen_error_text, SIIDR_MAX_ERROR_TEXT - 1);
		return_code = SIIDR_MAP_ERROR_GEN(return_code);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_TouchReadString(const char *string_ptr, unsigned int string_length,
	const char *string_name, char *error_text)
{
	int  return_code;
	char gen_error_text[GENFUNCS_MAX_ERROR_TEXT];

	if ((return_code = GEN_TouchReadString(string_ptr, string_length,
		string_name, gen_error_text)) != GENFUNCS_SUCCESS) {
		if (error_text != NULL)
			nstrcpy(error_text, gen_error_text, SIIDR_MAX_ERROR_TEXT - 1);
		return_code = SIIDR_MAP_ERROR_GEN(return_code);
	}

	return(return_code);
}
/*	***********************************************************************	*/


