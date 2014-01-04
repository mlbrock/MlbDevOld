/* *********************************************************************** */
/* *********************************************************************** */
/*	TFREAD Text File Reading Functions Library Include File						*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the TFREAD library.

	Revision History	:	1991-04-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1991 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

#ifndef h__TFREAD_H__h

#define h__TFREAD_H__h						1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <stdlib.h>

#include <strfuncs.h>

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   BASE NAME   :  TFREAD Truth Codes

   NAME        :  TFREAD Truth Codes

   DESCRIPTION :  Manifest constants used within TFREAD to specify the truth
						or falsity of expressions.

						(.) ''TFREAD_TRUE''

						(.) ''TFREAD_FALSE''

   NOTES       :  The manifest constant ''TFREAD_TRUE'' should be defined as
						a non-zero value. Conversely, the manifest constant
						''TFREAD_FALSE'' should be defined as zero (''0'').

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1991 - 2014 Michael L. Brock

   OUTPUT INDEX:  TFREAD_TRUE
						TFREAD_FALSE
						TFREAD Truth Codes:TFREAD_TRUE
						TFREAD Truth Codes:TFREAD_FALSE
						TFREAD Manifest Constants:TFREAD_TRUE
						TFREAD Manifest Constants:TFREAD_FALSE
						TFREAD Defines:TFREAD_TRUE
						TFREAD Defines:TFREAD_FALSE
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:  TFREAD Truth Codes
						TFREAD Truth Code
						TFREAD truth codes
						TFREAD truth code
						TFREAD_TRUE
						TFREAD_FALSE

   PUBLISH NAME:	TFREAD Truth Codes
						TFREAD_TRUE
						TFREAD_FALSE

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define TFREAD_TRUE							1
#define TFREAD_FALSE							0
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   BASE NAME   :	TFREAD Return Codes

   NAME        :  TFREAD Return Codes

   DESCRIPTION :  The TFREAD return codes have the following meanings:

						(.) ''TFREAD_SUCCESS'' means that the function invoked
						completed without error. ''TFREAD_SUCCESS'' is guaranteed to
						be equal to zero (''0'').

						(.) ''TFREAD_FAILURE'' indicates that the function invoked
						encountered a general operation failure. This is the
						'catch-all' error code for those errors which do not fit
						into category of one the other TFREAD error codes.

						(.) ''TFREAD_BAD_ARGS_FAILURE'' indicates that the
						arguments passed to a function invoked were invalid.

						(.) ''TFREAD_MEMORY_FAILURE'' indicates that the memory
						required for operation of the function invoked could not be
						allocated.

						(.) ''TFREAD_SYSTEM_FAILURE'' indicates that the function
						invoked encountered a failure of a standard library
						function or a system call.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1991 - 2014 Michael L. Brock

   OUTPUT INDEX:  TFREAD_SUCCESS
						TFREAD_FAILURE
						TFREAD_BAD_ARGS_FAILURE
						TFREAD_MEMORY_FAILURE
						TFREAD_SYSTEM_FAILURE
						TFREAD Return Codes:TFREAD_SUCCESS
						TFREAD Return Codes:TFREAD_FAILURE
						TFREAD Return Codes:TFREAD_BAD_ARGS_FAILURE
						TFREAD Return Codes:TFREAD_MEMORY_FAILURE
						TFREAD Return Codes:TFREAD_SYSTEM_FAILURE
						TFREAD Manifest Constants:TFREAD_SUCCESS
						TFREAD Manifest Constants:TFREAD_FAILURE
						TFREAD Manifest Constants:TFREAD_BAD_ARGS_FAILURE
						TFREAD Manifest Constants:TFREAD_MEMORY_FAILURE
						TFREAD Manifest Constants:TFREAD_SYSTEM_FAILURE
						TFREAD Defines:TFREAD_SUCCESS
						TFREAD Defines:TFREAD_FAILURE
						TFREAD Defines:TFREAD_BAD_ARGS_FAILURE
						TFREAD Defines:TFREAD_MEMORY_FAILURE
						TFREAD Defines:TFREAD_SYSTEM_FAILURE
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:  TFREAD_SUCCESS
						TFREAD_FAILURE
						TFREAD_BAD_ARGS_FAILURE
						TFREAD_MEMORY_FAILURE
						TFREAD_SYSTEM_FAILURE
						TFREAD Return Codes
						TFREAD Return Code
						TFREAD return codes
						TFREAD return code
						TFREAD Status Codes
						TFREAD Status Code
						TFREAD status codes
						TFREAD status code
						TFREAD Error Codes
						TFREAD Error Code
						TFREAD error codes
						TFREAD error code

   PUBLISH NAME:	TFREAD Return Codes
						TFREAD return codes
						TFREAD_SUCCESS
						TFREAD_FAILURE
						TFREAD_BAD_ARGS_FAILURE
						TFREAD_MEMORY_FAILURE
						TFREAD_SYSTEM_FAILURE

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define TFREAD_SUCCESS					   0
#define TFREAD_FAILURE					  -1
#define TFREAD_BAD_ARGS_FAILURE		  -2
#define TFREAD_MEMORY_FAILURE			  -3
#define TFREAD_SYSTEM_FAILURE			  -4
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :  TFREAD_MAX_ERROR_TEXT

   DESCRIPTION :  The manifest constant ''TFREAD_MAX_ERROR_TEXT'' defines
						the minimum amount of storage which should be allocated to
						hold an error message returned by a TFREAD function.

   CAVEATS     :  TFREAD error messages can be quite lengthy. Therefore,
						attempting to save space by allocating less than
						''TFREAD_MAX_ERROR_TEXT'' bytes to error message buffers
						passed to TFREAD functions can lead to overwriting of the
						heap or the stack.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1991 - 2014 Michael L. Brock

   OUTPUT INDEX:  TFREAD_MAX_ERROR_TEXT
						TFREAD Manifest Constants:TFREAD_MAX_ERROR_TEXT
						TFREAD Defines:TFREAD_MAX_ERROR_TEXT
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	TFREAD_MAX_ERROR_TEXT

   PUBLISH NAME:	TFREAD_MAX_ERROR_TEXT

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define TFREAD_MAX_ERROR_TEXT				1024
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Function prototypes for functions defined within 'tfread.a' . . .		*/
/*	***********************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Function prototypes for access based upon ISO/ANSI C level-2 I/O.
		*****************************************************************	*/
COMPAT_FN_DECL(int TFREAD_ReadLines,
	(const char *file_name, unsigned int *line_count, char ***line_list,
	char *error_text));
COMPAT_FN_DECL(int TFREAD_ReadLinesNoAlloc,
	(const char *file_name, unsigned int *line_count, char ***line_list,
	char *error_text));
COMPAT_FN_DECL(int TFREAD_ReadBufferXLateNL,
	(const char *file_name, const char *nl_string, unsigned int *buffer_length,
	char **buffer_ptr, char *error_text));
COMPAT_FN_DECL(int TFREAD_ReadBuffer,
	(const char *file_name, unsigned int *buffer_length, char **buffer_ptr,
	char *error_text));
COMPAT_FN_DECL(int TFREAD_ReadBufferRaw,
	(const char *file_name, unsigned int *buffer_length, char **buffer_ptr,
	char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Function prototypes for access based upon ISO/ANSI C level-2 I/O.
		*****************************************************************	*/
COMPAT_FN_DECL(int TFREAD_ReadLinesFILE,
	(const char *file_name, unsigned int *line_count, char ***line_list,
	char *error_text));
COMPAT_FN_DECL(int TFREAD_ReadLinesNoAllocFILE,
	(const char *file_name, unsigned int *line_count, char ***line_list,
	char *error_text));
COMPAT_FN_DECL(int TFREAD_ReadBufferXLateNLFILE,
	(const char *file_name, const char *nl_string, unsigned int *buffer_length,
	char **buffer_ptr, char *error_text));
COMPAT_FN_DECL(int TFREAD_ReadBufferFILE,
	(const char *file_name, unsigned int *buffer_length, char **buffer_ptr,
	char *error_text));
COMPAT_FN_DECL(int TFREAD_ReadBufferRawFILE,
	(const char *file_name, unsigned int *buffer_length, char **buffer_ptr,
	char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Function prototypes for MFILE-based access . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int TFREAD_ReadLinesMFILE,
	(const char *file_name, unsigned int *line_count, char ***line_list,
	char *error_text));
COMPAT_FN_DECL(int TFREAD_ReadLinesNoAllocMFILE,
	(const char *file_name, unsigned int *line_count, char ***line_list,
	char *error_text));
COMPAT_FN_DECL(int TFREAD_ReadBufferXLateNLMFILE,
	(const char *file_name, const char *nl_string, unsigned int *buffer_length,
	char **buffer_ptr, char *error_text));
COMPAT_FN_DECL(int TFREAD_ReadBufferMFILE,
	(const char *file_name, unsigned int *buffer_length, char **buffer_ptr,
	char *error_text));
COMPAT_FN_DECL(int TFREAD_ReadBufferRawMFILE,
	(const char *file_name, unsigned int *buffer_length, char **buffer_ptr,
	char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Function prototypes for generic access . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int TFREAD_ReadLinesBasic,
	(const STR_CFILE_FUNCS *tfread_ptr, const char *file_name, unsigned int *line_count,
	char ***line_list, char *error_text));
COMPAT_FN_DECL(int TFREAD_ReadLinesNoAllocBasic,
	(const STR_CFILE_FUNCS *tfread_ptr, const char *file_name, unsigned int *line_count,
	char ***line_list, char *error_text));
COMPAT_FN_DECL(int TFREAD_ReadBufferXLateNLBasic,
	(const STR_CFILE_FUNCS *tfread_ptr, const char *file_name, const char *nl_string,
	unsigned int *buffer_length, char **buffer_ptr, char *error_text));
COMPAT_FN_DECL(int TFREAD_ReadBufferBasic,
	(const STR_CFILE_FUNCS *tfread_ptr, const char *file_name,
	unsigned int *buffer_length, char **buffer_ptr, char *error_text));
COMPAT_FN_DECL(int TFREAD_ReadBufferRawBasic,
	(const STR_CFILE_FUNCS *tfread_ptr, const char *file_name,
	unsigned int *buffer_length, char **buffer_ptr, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Function prototypes for supporting functions . . .
		*****************************************************************	*/
COMPAT_FN_DECL(const STR_CFILE_FUNCS *TFREAD_GetDefDataFILE,
	(STR_CFILE_FUNCS *tfread_ptr));
COMPAT_FN_DECL(const STR_CFILE_FUNCS *TFREAD_GetDefDataMFILE,
	(STR_CFILE_FUNCS *tfread_ptr));
	/*	*****************************************************************	*/

/*	***********************************************************************	*/

#endif /* #ifndef h__TFREAD_H__h */

