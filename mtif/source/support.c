/* *********************************************************************** */
/* *********************************************************************** */
/*	Multi-Threading Interface Facility (MTIF) Library Source File				*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Miscellaneous MTIF supporting functions.

	Revision History	:	1994-09-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/*	Necessary include files . . .															*/
/* *********************************************************************** */

#include <errno.h>
#include <string.h>

#include <strfuncs.h>
#include <genfuncs.h>

#include "mtifi.h"

/* *********************************************************************** */

/*
	CODE NOTE:	To be removed when the Win32 error spec prototypes are
					moved into 'genfuncs.h'.
*/
COMPAT_FN_DECL(char                 *GEN_GetErrorString_Win32,
	(int win32_code, int long_flag, unsigned int max_text, char *error_text));

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  MTIF_SUPP_AppendSpecErrorString

   SYNOPSIS    :  error_ptr = MTIF_SUPP_AppendSpecErrorString(errno_code,
							error_text);

						char *error_ptr;

						int   errno_code;

						char *error_text;

   DESCRIPTION :  Appends text descriptive of the specified system error
						number to the string to which the ``error_string``
						parameter points.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``errno_code`` is the system error number (from the
						external variable defined in ''errno.h'') which is to be
						appended.

						(.) ``error_text`` points to a string into which this
						function will append text descriptive of the system error
						specified by the ``errno_code`` parameter. The string
						allocated for this purpose should be at least
						''MTIF_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  A pointer to the error string ``error_text``.

   NOTES       :  This function will append text to ``error_text`` only as
						far as to make the total length of the string equal to
						the value of the manifest constant
						''MTIF_MAX_ERROR_TEXT - 1''.

						This function calls ``GEN_GetErrorString`` to perform the
						actual work of constructing the error string.

   CAVEATS     :  

   SEE ALSO    :  MTIF_SUPP_AppendLastErrorString
						MTIF_SUPP_GetSpecErrorString

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	MTIF_SUPP_AppendSpecErrorString
						Utility Functions:Error Description Functions:MTIF_SUPP_AppendSpecErrorString

	PUBLISH XREF:	MTIF_SUPP_AppendSpecErrorString

	PUBLISH NAME:	MTIF_SUPP_AppendSpecErrorString

	ENTRY CLASS :	Error Description Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *MTIF_SUPP_AppendSpecErrorString(int errno_code, char *error_text)
#else
char *MTIF_SUPP_AppendSpecErrorString(errno_code, error_text)
int   errno_code;
char *error_text;
#endif /* #ifndef NARGS */
{
	unsigned int error_length;

	if ((error_length = strlen(error_text)) < MTIF_MAX_ERROR_TEXT)
		GEN_GetErrorString(errno_code, 0, MTIF_MAX_ERROR_TEXT - error_length,
			error_text + error_length);

	return(error_text);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  MTIF_SUPP_AppendLastErrorString

   SYNOPSIS    :  MTIF_SUPP_AppendLastErrorString(error_text);

						char *error_ptr;

						char *error_text;

   DESCRIPTION :  Appends text descriptive of the last occurrence of a system
						error to the string to which the ``error_string``
						parameter points.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``error_text`` points to a string into which this
						function will append text descriptive of the last system
						error. The string allocated for this purpose should be at
						least ''MTIF_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  A pointer to the error string ``error_text``.

   NOTES       :  This function will append text to ``error_text`` only as
						far as to make the total length of the string equal to
						the value of the manifest constant
						''MTIF_MAX_ERROR_TEXT - 1''.

   CAVEATS     :  

   SEE ALSO    :  MTIF_SUPP_AppendSpecErrorString
						MTIF_SUPP_GetLastErrorString

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	MTIF_SUPP_AppendLastErrorString
						Utility Functions:Error Description Functions:MTIF_SUPP_AppendLastErrorString

	PUBLISH XREF:	MTIF_SUPP_AppendLastErrorString

	PUBLISH NAME:	MTIF_SUPP_AppendLastErrorString

	ENTRY CLASS :	Error Description Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *MTIF_SUPP_AppendLastErrorString(char *error_text)
#else
char *MTIF_SUPP_AppendLastErrorString(error_text)
char *error_text;
#endif /* #ifndef NARGS */
{
	return(MTIF_SUPP_AppendSpecErrorString(errno, error_text));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  MTIF_SUPP_GetSpecErrorString

   SYNOPSIS    :  error_ptr = MTIF_SUPP_GetSpecErrorString(errno_code,
							error_text);

						char *error_ptr;

						int   errno_code;

						char *error_text;

   DESCRIPTION :  Gets text descriptive of the specified system error
						number and places it into the string to which the
						``error_string`` parameter points.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``errno_code`` is the system error number (from the
						external variable defined in ''errno.h'') which is to be
						appended.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of the system error
						specified by the ``errno_code`` parameter. The string
						allocated for this purpose should be at least
						''MTIF_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  A pointer to the error string ``error_text``.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  MTIF_SUPP_GetLastErrorString
						MTIF_SUPP_AppendSpecErrorString

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	MTIF_SUPP_GetSpecErrorString
						Utility Functions:Error Description Functions:MTIF_SUPP_GetSpecErrorString

	PUBLISH XREF:	MTIF_SUPP_GetSpecErrorString

	PUBLISH NAME:	MTIF_SUPP_GetSpecErrorString

	ENTRY CLASS :	Error Description Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *MTIF_SUPP_GetSpecErrorString(int errno_code, char *error_text)
#else
char *MTIF_SUPP_GetSpecErrorString(errno_code, error_text)
int   errno_code;
char *error_text;
#endif /* #ifndef NARGS */
{
	*error_text = '\0';

	return(MTIF_SUPP_AppendSpecErrorString(errno_code, error_text));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  MTIF_SUPP_GetLastErrorString

   SYNOPSIS    :  MTIF_SUPP_GetLastErrorString(error_text);

						char *error_ptr;

						char *error_text;

   DESCRIPTION :  Gets text descriptive of the last occurrence of a system
						error and places it into the string to which the
						``error_string`` parameter points.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of the last system
						error. The string allocated for this purpose should be at
						least ''MTIF_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  A pointer to the error string ``error_text``.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  MTIF_SUPP_GetSpecErrorString
						MTIF_SUPP_AppendLastErrorString

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	MTIF_SUPP_GetLastErrorString
						Utility Functions:Error Description Functions:MTIF_SUPP_GetLastErrorString

	PUBLISH XREF:	MTIF_SUPP_GetLastErrorString

	PUBLISH NAME:	MTIF_SUPP_GetLastErrorString

	ENTRY CLASS :	Error Description Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *MTIF_SUPP_GetLastErrorString(char *error_text)
#else
char *MTIF_SUPP_GetLastErrorString(error_text)
char *error_text;
#endif /* #ifndef NARGS */
{
	return(MTIF_SUPP_GetSpecErrorString(errno, error_text));
}
/* *********************************************************************** */

#ifdef _Windows
/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  MTIF_SUPP_AppendSpecErrorString_Win32

   SYNOPSIS    :  error_ptr = MTIF_SUPP_AppendSpecErrorString_Win32(win32_code,
							error_text);

						char *error_ptr;

						int   win32_code;

						char *error_text;

   DESCRIPTION :  Appends text descriptive of the specified Win32 system error
						number to the string to which the ``error_string``
						parameter points.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``win32_code`` is the Win32 system error number (from the
						return value of the function ``GetLastError()``) which is to
						be appended.

						(.) ``error_text`` points to a string into which this
						function will append text descriptive of the system error
						specified by the ``win32_code`` parameter. The string
						allocated for this purpose should be at least
						''MTIF_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  A pointer to the error string ``error_text``.

   NOTES       :  This function will append text to ``error_text`` only as
						far as to make the total length of the string equal to
						the value of the manifest constant
						''MTIF_MAX_ERROR_TEXT - 1''.

						This function calls ``GEN_GetErrorString_Win32`` to perform
						the actual work of constructing the error string.

   CAVEATS     :  

   SEE ALSO    :  MTIF_SUPP_AppendSpecErrorString
						MTIF_SUPP_AppendLastErrorString_Win32
						MTIF_SUPP_GetSpecErrorString_Win32

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	MTIF_SUPP_AppendSpecErrorString_Win32
						Windows Functions:MTIF_SUPP_AppendSpecErrorString_Win32
						Utility Functions:Error Description Functions:MTIF_SUPP_AppendSpecErrorString_Win32

	PUBLISH XREF:	MTIF_SUPP_AppendSpecErrorString_Win32

	PUBLISH NAME:	MTIF_SUPP_AppendSpecErrorString_Win32

	ENTRY CLASS :	Error Description Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *MTIF_SUPP_AppendSpecErrorString_Win32(int win32_code, char *error_text)
#else
char *MTIF_SUPP_AppendSpecErrorString_Win32(win32_code, error_text)
int   win32_code;
char *error_text;
#endif /* #ifndef NARGS */
{
	unsigned int error_length;

	if ((error_length = strlen(error_text)) < MTIF_MAX_ERROR_TEXT)
		GEN_GetErrorString_Win32(win32_code, 0,
			MTIF_MAX_ERROR_TEXT - error_length, error_text + error_length);

	return(error_text);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  MTIF_SUPP_AppendLastErrorString_Win32

   SYNOPSIS    :  MTIF_SUPP_AppendLastErrorString_Win32(error_text);

						char *error_ptr;

						char *error_text;

   DESCRIPTION :  Appends text descriptive of the last occurrence of a Win32
						system error to the string to which the ``error_string``
						parameter points.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``error_text`` points to a string into which this
						function will append text descriptive of the last system
						error. The string allocated for this purpose should be at
						least ''MTIF_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  A pointer to the error string ``error_text``.

   NOTES       :  This function will append text to ``error_text`` only as
						far as to make the total length of the string equal to
						the value of the manifest constant
						''MTIF_MAX_ERROR_TEXT - 1''.

   CAVEATS     :  

   SEE ALSO    :  MTIF_SUPP_AppendLastErrorString
						MTIF_SUPP_AppendSpecErrorString_Win32
						MTIF_SUPP_GetLastErrorString_Win32

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	MTIF_SUPP_AppendLastErrorString_Win32
						Windows Functions:MTIF_SUPP_AppendLastErrorString_Win32
						Utility Functions:Error Description Functions:MTIF_SUPP_AppendLastErrorString_Win32

	PUBLISH XREF:	MTIF_SUPP_AppendLastErrorString_Win32

	PUBLISH NAME:	MTIF_SUPP_AppendLastErrorString_Win32

	ENTRY CLASS :	Error Description Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *MTIF_SUPP_AppendLastErrorString_Win32(char *error_text)
#else
char *MTIF_SUPP_AppendLastErrorString_Win32(error_text)
char *error_text;
#endif /* #ifndef NARGS */
{
	return(MTIF_SUPP_AppendSpecErrorString_Win32(GetLastError(), error_text));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  MTIF_SUPP_GetSpecErrorString_Win32

   SYNOPSIS    :  error_ptr = MTIF_SUPP_GetSpecErrorString_Win32(win32_code,
							error_text);

						char *error_ptr;

						int   win32_code;

						char *error_text;

   DESCRIPTION :  Gets text descriptive of the specified Win32 system error
						number and places it into the string to which the
						``error_string`` parameter points.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``win32_code`` is the Win32 system error number (from the
						return value of the function ``GetLastError()``) which is to
						be appended.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of the system error
						specified by the ``win32_code`` parameter. The string
						allocated for this purpose should be at least
						''MTIF_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  A pointer to the error string ``error_text``.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  MTIF_SUPP_GetSpecErrorString
						MTIF_SUPP_GetLastErrorString_Win32
						MTIF_SUPP_AppendSpecErrorString_Win32

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	MTIF_SUPP_GetSpecErrorString_Win32
						Windows Functions:MTIF_SUPP_GetSpecErrorString_Win32
						Utility Functions:Error Description Functions:MTIF_SUPP_GetSpecErrorString_Win32

	PUBLISH XREF:	MTIF_SUPP_GetSpecErrorString_Win32

	PUBLISH NAME:	MTIF_SUPP_GetSpecErrorString_Win32

	ENTRY CLASS :	Error Description Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *MTIF_SUPP_GetSpecErrorString_Win32(int win32_code, char *error_text)
#else
char *MTIF_SUPP_GetSpecErrorString_Win32(win32_code, error_text)
int   win32_code;
char *error_text;
#endif /* #ifndef NARGS */
{
	*error_text = '\0';

	return(MTIF_SUPP_AppendSpecErrorString_Win32(win32_code, error_text));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  MTIF_SUPP_GetLastErrorString_Win32

   SYNOPSIS    :  MTIF_SUPP_GetLastErrorString_Win32(error_text);

						char *error_ptr;

						char *error_text;

   DESCRIPTION :  Gets text descriptive of the last occurrence of a Win32
						system error and places it into the string to which the
						``error_string`` parameter points.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of the last system
						error. The string allocated for this purpose should be at
						least ''MTIF_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  A pointer to the error string ``error_text``.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  MTIF_SUPP_GetLastErrorString
						MTIF_SUPP_GetSpecErrorString_Win32
						MTIF_SUPP_AppendLastErrorString_Win32

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	MTIF_SUPP_GetLastErrorString_Win32
						Windows Functions:MTIF_SUPP_GetLastErrorString_Win32
						Utility Functions:Error Description Functions:MTIF_SUPP_GetLastErrorString_Win32

	PUBLISH XREF:	MTIF_SUPP_GetLastErrorString_Win32

	PUBLISH NAME:	MTIF_SUPP_GetLastErrorString_Win32

	ENTRY CLASS :	Error Description Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *MTIF_SUPP_GetLastErrorString_Win32(char *error_text)
#else
char *MTIF_SUPP_GetLastErrorString_Win32(error_text)
char *error_text;
#endif /* #ifndef NARGS */
{
	return(MTIF_SUPP_GetSpecErrorString_Win32(GetLastError(), error_text));
}
/* *********************************************************************** */
#endif /* #ifdef _Windows */

/* *********************************************************************** */
#ifndef NARGS
int MTIF_SUPP_Check(const void *handle_ptr, const char *handle_name,
	unsigned int handle_size, unsigned int signature_offset,
	MTIF_SIGNATURE signature, char *error_text)
#else
int MTIF_SUPP_Check(handle_ptr, handle_name, handle_size, signature_offset,
	signature, error_text)
const void     *handle_ptr;
const char     *handle_name;
unsigned int    handle_size;
unsigned int    signature_offset;
MTIF_SIGNATURE  signature;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = MTIF_INVALID_OBJECT;

	if (handle_ptr == NULL) {
		if (error_text != NULL)
			strcat(strcat(strcpy(error_text, "MTIF "), handle_name),
				" handle pointer is 'NULL'.");
	}
#ifdef _Windows
	else if (IsBadWritePtr(((void *) handle_ptr), handle_size)) {
		if (error_text != NULL)
			strcat(val2str_ptr_cat(handle_ptr,
				strcat(strcat(strcpy(error_text, "MTIF "), handle_name),
				" handle pointer (")), ") is invalid.");
	}
#endif /* #ifdef _Windows */
	else if (*((MTIF_SIGNATURE *) ((const void *) (((const char *)
		handle_ptr) + signature_offset))) != signature) {
		if (error_text != NULL)
			strcat(strcat(strcpy(error_text, "MTIF "), handle_name),
				" handle pointer has an invalid signature.");
	}
	else
		return_code = MTIF_SUCCESS;

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
char *MTIF_THR_GetThreadText(const MTIF_THR_HANDLE *thr_handle_ptr,
	char *out_text)
#else
char *MTIF_THR_GetThreadText(thr_handle_ptr, out_text)
const MTIF_THR_HANDLE *thr_handle_ptr;
char                  *out_text;
#endif /* #ifndef NARGS */
{
	return(val2str_ulong_cat(((unsigned long)
		MTIF_THR_GET_OS_ID_DEFAULT(thr_handle_ptr)), 10, NULL,
		strcat(strcpy(out_text, (thr_handle_ptr == NULL) ? "current " : ""),
		"thread id ")));
}
/* *********************************************************************** */

#ifdef _Windows
/* *********************************************************************** */
#ifndef NARGS
int MTIF_SUPP_WIN32_CheckHandlePtr(const HANDLE *handle_ptr, char *error_text)
#else
int MTIF_SUPP_WIN32_CheckHandlePtr(handle_ptr, error_text)
const HANDLE *handle_ptr;
char         *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (handle_ptr == NULL) {
		if (error_text != NULL)
			strcpy(error_text, "WIN32 handle pointer is 'NULL'.");
		return_code = MTIF_BAD_ARGS_FAILURE;
	}
	else if (IsBadWritePtr(((void *) handle_ptr), sizeof(*handle_ptr))) {
		if (error_text != NULL)
			strcat(val2str_ptr0_cat(handle_ptr,
				strcpy(error_text, "WIN32 handle pointer (0x")), ") is invalid.");
		return_code = MTIF_BAD_ARGS_FAILURE;
	}
	else
		return_code = MTIF_SUCCESS;

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int MTIF_SUPP_WIN32_CheckHandlePtrAndValue(const HANDLE *handle_ptr,
	char *error_text)
#else
int MTIF_SUPP_WIN32_CheckHandlePtrAndValue(handle_ptr, error_text)
const HANDLE *handle_ptr;
char         *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = MTIF_SUPP_WIN32_CheckHandlePtr(handle_ptr,
		error_text)) == MTIF_SUCCESS)
		return_code = MTIF_SUPP_WIN32_CheckHandleValue(*handle_ptr, error_text);

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int MTIF_SUPP_WIN32_CheckHandleValue(HANDLE in_handle, char *error_text)
#else
int MTIF_SUPP_WIN32_CheckHandleValue(in_handle, error_text)
HANDLE  in_handle;
char   *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (in_handle == INVALID_HANDLE_VALUE) {
		if (error_text != NULL)
			strcpy(error_text,
				"Handle value is equal to 'INVALID_HANDLE_VALUE'.");
		return_code = MTIF_BAD_ARGS_FAILURE;
	}
	else if (in_handle == NULL) {
		if (error_text != NULL)
			strcpy(error_text, "Handle value is equal to 'NULL'.");
		return_code = MTIF_BAD_ARGS_FAILURE;
	}
	else
		return_code = MTIF_SUCCESS;

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int MTIF_SUPP_WIN32_CloseHandle(HANDLE *handle_ptr, char *error_text)
#else
int MTIF_SUPP_WIN32_CloseHandle(handle_ptr, error_text)
HANDLE *handle_ptr;
char   *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = MTIF_SUPP_WIN32_CheckHandlePtrAndValue(handle_ptr,
		error_text)) == MTIF_SUCCESS) {
		if (CloseHandle(*handle_ptr) != 0)
			*handle_ptr = ((HANDLE) 0);
		else {
			if (error_text != NULL)
				MTIF_SUPP_AppendLastErrorString_Win32(
					strcat(val2str_ptr0_cat(*handle_ptr,
					strcpy(error_text, "Call to 'CloseHandle(")), ")' failed: "));
			return_code = MTIF_SYSTEM_FAILURE;
		}
	}

	return(return_code);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
#ifndef NARGS
int MTIF_SUPP_WIN32_CreateMutex(int init_owner_flag, const char *mtr_name,
	HANDLE *handle_ptr, char *error_text)
#else
int MTIF_SUPP_WIN32_CreateMutex(init_owner_flag, mtr_name, handle_ptr,
	error_text)
int         init_owner_flag;
const char *mtr_name;
HANDLE     *handle_ptr;
char       *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((init_owner_flag != MTIF_TRUE) && (init_owner_flag != MTIF_FALSE)) {
		strcpy(error_text,
			"Initial owner flag must be either 'MTIF_TRUE' or 'MTIF_FALSE'.");
		return_code = MTIF_BAD_ARGS_FAILURE;
	}
	else if ((mtr_name != NULL) && IsBadStringPtr(mtr_name, UINT_MAX - 1)) {
		if (error_text != NULL)
			strcpy(error_text, "Mutex name is an invalid string.");
		return_code = MTIF_BAD_ARGS_FAILURE;
	}
	else if ((mtr_name != NULL) && (strlen(mtr_name) > MAX_PATH)) {
		sprintf(error_text, "Length of mutex name (%u) exceeds maximum (%u).",
			strlen(mtr_name), MAX_PATH);
		return_code = MTIF_BAD_ARGS_FAILURE;
	}
	else if ((return_code = MTIF_SUPP_WIN32_CheckHandlePtr(handle_ptr,
		error_text)) == MTIF_SUCCESS) {
		if ((*handle_ptr = CreateMutex(NULL,
			(init_owner_flag == MTIF_TRUE) ? TRUE : FALSE, mtr_name)) != NULL)
			return_code = MTIF_SUCCESS;
		else {
			if (error_text != NULL)
				MTIF_SUPP_AppendLastErrorString_Win32(strcat(nstrcat(strcat(strcat(
					strcpy(error_text, "Call to 'CreateMutex(NULL, "),
					(init_owner_flag == MTIF_TRUE) ? "TRUE, " : "FALSE, "),
					(mtr_name == NULL) ? "" : "\""),
					(mtr_name == NULL) ? "NULL" : mtr_name, 500),
					(mtr_name == NULL) ? ")' failed: " : "\")' failed: "));
			return_code = MTIF_SYSTEM_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/* *********************************************************************** */
#ifndef NARGS
int MTIF_SUPP_WIN32_ReleaseMutex(HANDLE in_handle, char *error_text)
#else
int MTIF_SUPP_WIN32_ReleaseMutex(in_handle, error_text)
HANDLE  in_handle;
char   *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = MTIF_SUPP_WIN32_CheckHandleValue(in_handle,
		error_text)) == MTIF_SUCCESS) {
		if (ReleaseMutex(in_handle) == 0) {
			if (error_text != NULL)
				MTIF_SUPP_AppendLastErrorString_Win32(strcat(
					val2str_ptr0_cat(in_handle,
					strcpy(error_text, "Call to 'ReleaseMutex(")), ")' failed: "));
			return_code = MTIF_SYSTEM_FAILURE;
		}
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int MTIF_SUPP_WIN32_WaitForSingleObject(HANDLE in_handle, DWORD time_out,
	char *error_text)
#else
int MTIF_SUPP_WIN32_WaitForSingleObject(in_handle, time_out, error_text)
HANDLE  in_handle;
DWORD   time_out;
char   *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code;
	char buffer[STR_VAL2STR_MAX_LEN + 1];

	if ((return_code = MTIF_SUPP_WIN32_CheckHandleValue(in_handle,
		error_text)) == MTIF_SUCCESS) {
		if (((return_code = WaitForSingleObject(in_handle, time_out)) ==
			WAIT_OBJECT_0) || (return_code == WAIT_ABANDONED))
			return_code = MTIF_SUCCESS;
		else if (return_code == WAIT_TIMEOUT) {
			if (time_out != INFINITE) {
				if (error_text != NULL)
					strcat(strcat(strcat(val2str_ptr0_cat(in_handle,
						strcpy(error_text, "Call to 'WaitForSingleObject(")), ", "),
						val2str_ulong(((unsigned long) time_out), 10, NULL, buffer)),
						")' timed-out.");
				return_code= MTIF_LOCK_ACQ_FAILURE;
			}
			else {
				if (error_text != NULL)
					strcat(strcat(val2str_ptr0_cat(in_handle,
						strcpy(error_text,
						"Error on call to 'WaitForSingleObject(")),
						", INFINITE)': time-out is 'INFINITE' but function "),
						"returned 'WAIT_TIMEOUT'.");
				return_code = MTIF_SYSTEM_FAILURE;
			}
		}
		else {
			if (error_text != NULL)
				MTIF_SUPP_AppendLastErrorString_Win32(strcat(strcat(strcat(
					val2str_ptr0_cat(in_handle,
					strcpy(error_text, "Call to 'WaitForSingleObject(")), ", "),
					(time_out == INFINITE) ? "INFINITE" :
					val2str_ulong(((unsigned long) time_out), 10, NULL, buffer)),
					")' failed: "));
			return_code = MTIF_SYSTEM_FAILURE;
		}
	}

	return(return_code);
}
/* *********************************************************************** */
#endif /* #ifdef _Windows */

#ifdef TEST_MAIN
 
#include <stdio.h>
#include <stdlib.h>

#ifdef __MSDOS__
COMPAT_EXTERN_DATA_DECL unsigned int _stklen = 16384;
#endif /* __MSDOS__ */

COMPAT_FN_DECL(int main, (int argc, char **argv));
 
char *UsageString = "<errno-number> [<errno-number> . . .]";

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int  count_1 = 0;
	char error_text[4096];

	fprintf(stderr, "Test routine for 'MTIF_SUPP_AppendSpecErrorString()'\n");
	fprintf(stderr, "---- ------- --- -----------------------------------\n\n");

	for (count_1 = 1; count_1 < argc; count_1++) {
		if (!stricmp("-HELP", argv[count_1]))
			GEN_DoSimpleUsage(MTIF_SUCCESS, argv[0], "Help request noted.",
				UsageString);
	}

	if (argc < 2)
		GEN_DoSimpleUsage(MTIF_FAILURE, argv[0],
			"Invalid command invocation", UsageString);

	for (count_1 = 1; count_1 < argc; count_1++) {
		strcpy(error_text, "START OF THE MTIF ERROR STRING: ");
		printf("%d ---> %s\n", atoi(argv[count_1]),
			MTIF_SUPP_AppendSpecErrorString(atoi(argv[count_1]), error_text));
	}

	return(0);
}

#endif /* #ifdef TEST_MAIN */


