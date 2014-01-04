/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	GENFUNCS General Functions Library Source Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Argument-parsing support for executables.

	Revision History	:	1995-05-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <stdlib.h>
#include <string.h>

#include <strfuncs.h>

#include "genfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_BARG_LogDir

   SYNOPSIS    :	truth_flag = GEN_BARG_LogDir(in_arg_ptr, in_arg_length,
							in_data_ptr, log_dir, error_code, error_text);

						int            truth_flag;

						const char    *in_arg_ptr;

						unsigned int  *in_arg_length;

						char         **in_data_ptr;

						char         **log_dir;

						int           *error_code;

						char          *error_text;

   DESCRIPTION :	Parses a string to determine if it specifies a log file
						directory name.

						Strings having the following syntax will be considered to
						have the appropriate format:

						<|@|>-LOG''[''GING'']''_DIR''[''ECTORY'']''=``log-file-dir-name``

						If this function finds a match, the ``log-file-dir-name``
						parameter component is expanded to its fully-qualified
						form and memory is allocated to hold it.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_arg_ptr`` points to the string to be parsed.

						(.) ``in_arg_length`` is a pointer to an ''unsigned int''
						into which will be placed the length of the parameter name
						(if found).

						(-) For example, if the string ``in_arg_ptr`` is:

						{|-|}-LOGGING_DIRECTORY=/log/file/directory/name

						(-) The ''unsigned int'' to which ``in_arg_length`` points
						will be set to ''19'', the length of the string
						''-LOGGING_DIRECTORY=''.

						(-) Note that if ``in_arg_length`` is a ''NULL'' pointer,
						it will not be de-referenced.

						(.) ``in_data_ptr`` points to a pointer to ''char'' into
						which will be placed a pointer to the first character of
						the ``log-file-dir-name`` parameter component.

						(-) In the example above, ``in_data_ptr`` would be set to
						point to the first character of the directory string
						''/log/file/directory/name''.

						(-) Note that if ``in_data_ptr`` is a ''NULL'' pointer,
						it will not be de-referenced.

						(.) ``log_dir`` points to a pointer to ''char'' into which
						will be placed a pointer to memory allocated to hold the
						string ``log-file-dir-name`` parameter component. It is the
						responsibility of the application programmer to free this
						memory with ``free()``.

						(-) The ``log_dir`` string will be expanded to its fully
						qualified name. Under Unix, this function performs tilde
						(''~'') expansion. Under MS-DOS and related operating
						systems such as Windows, This function prepends the drive
						letter (and associated colon character) to the
						fully-qualified name.

						(-) If the string to which the ``log_dir`` parameter points
						is not ''NULL'', it will be de-allocated using ``free()``
						before allocating memory for the new string.

						(-) If the ``log-file-dir-name`` parameter component is
						empty, ``log_dir`` will be set to a ''NULL'' pointer.

						(.) ``error_code`` points to an ''int'' into which will be
						placed the GENFUNCS status code which results from the
						operation of this function.

						(..) ''GENFUNCS_SUCCESS'' if the function completes without
						error.

						(..) ''GENFUNCS_SYSTEM_FAILURE'' indicates that a standard
						library 	function or a system call failed.

						(..) ''GENFUNCS_MEMORY_FAILURE'' indicates that the memory
						required for operation of the function could not be
						allocated.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	Returns from this function are as follow:

						(.) The manifest constant ''GENFUNCS_TRUE'' if the parameter
						was matched.

						(.) Otherwise, the manifest constant ''GENFUNCS_FALSE'' is
						returned.

   NOTES       :	This function uses ``GEN_ArgParse`` to perform the parse.

   CAVEATS     :	

   SEE ALSO    :	GEN_BARG_LogFlag
						GEN_BARG_LogQuiet
						GEN_BARG_BasicPathExpand
						GEN_ArgParse
						GEN_BUSE_LogDir

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1995 - 2014 Michael L. Brock

   OUTPUT INDEX:	GEN_BARG_LogDir
						Argument Parsing Functions:GEN_BARG_LogDir
						GENFUNCS:Functions:GEN_BARG_LogDir
						GENFUNCS:Argument Parsing Functions:GEN_BARG_LogDir
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_BARG_LogDir
						-LOGGING_DIRECTORY=
						-LOGGING_DIRECTORY= Parameter
						-LOGGING_DIRECTORY= parameter

   PUBLISH NAME:	GEN_BARG_LogDir

	ENTRY CLASS	:	Argument Parsing Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_BARG_LogDir(const char *in_arg_ptr, unsigned int *in_arg_length,
	char **in_data_ptr, char **log_dir, int *error_code, char *error_text)
#else
int GEN_BARG_LogDir(in_arg_ptr, in_arg_length, in_data_ptr, log_dir,
	error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
char         **log_dir;
int           *error_code;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;

	*error_code = GENFUNCS_SUCCESS;
	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	if ((return_code = GEN_ArgParse(in_arg_ptr, arg_length, data_ptr,
		"-LOG_DIR=", "-LOGGING_DIR=", "-LOG_DIRECTORY=", "-LOGGING_DIRECTORY=",
		NULL)) == GENFUNCS_TRUE) {
		if (*log_dir != NULL) {
			free(*log_dir);
			*log_dir = NULL;
		}
		*error_code = GEN_BARG_BasicPathExpand(in_arg_ptr, *arg_length,
			*data_ptr, log_dir, error_text);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_BARG_LogFlag

   SYNOPSIS    :	truth_flag = GEN_BARG_LogFlag(in_arg_ptr, in_arg_length,
							in_data_ptr, log_flag, error_code, error_text);

						int            truth_flag;

						const char    *in_arg_ptr;

						unsigned int  *in_arg_length;

						char         **in_data_ptr;

						int           *log_flag;

						int           *error_code;

						char          *error_text;

   DESCRIPTION :	Parses a string to determine if it specifies the logging
						state.

						Strings having the following syntax will be considered to
						have the appropriate format:

						<|@|>-LOG''[''GING''][''_FLAG'']''=``boolean``

						The ``boolean`` component of this parameter has the
						following syntax for the value ''TRUE'':

						<|@|>''{''TRUE''|''ON''|''YES''|''T''|''Y''|''1''}''

						and the following syntax for the value ''FALSE'':

						<|@|>''{''FALSE''|''OFF''|''NO''|''F''|''N''|''0''}''

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_arg_ptr`` points to the string to be parsed.

						(.) ``in_arg_length`` is a pointer to an ''unsigned int''
						into which will be placed the length of the parameter name
						(if found).

						(-) For example, if the string ``in_arg_ptr`` is:

						{|-|}-LOGGING_FLAG=ON

						(-) The ''unsigned int'' to which ``in_arg_length`` points
						will be set to ''14'', the length of the string
						''-LOGGING_FLAG=''.

						(-) Note that if ``in_arg_length`` is a ''NULL'' pointer,
						it will not be de-referenced.

						(.) ``in_data_ptr`` points to a pointer to ''char'' into
						which will be placed a pointer to the first character of
						the ``boolean`` parameter component.

						(-) In the example above, ``in_data_ptr`` would be set to
						point to the first character of the string ''ON''.

						(-) Note that if ``in_data_ptr`` is a ''NULL'' pointer,
						it will not be de-referenced.

						(.) ``log_flag`` points to an ''int'' into which will be
						placed one the GENFUNCS Truth Codes corresponding to the
						``boolean`` parameter component (if found).

						(-) If the ``boolean`` parameter component is ''ON'',
						''TRUE'', or ''YES'', the ''int'' to which ``log_flag``
						points will be set to ''GENFUNCS_TRUE''.

						(-) If the ``boolean`` parameter component is ''OFF'',
						''FALSE'', or ''NO'', the ''int'' to which ``log_flag``
						points will be set to ''GENFUNCS_FALSE''.

						(.) ``error_code`` points to an ''int'' into which will be
						placed the GENFUNCS status code which results from the
						operation of this function.

						(..) ''GENFUNCS_SUCCESS'' if the function completes without
						error.

						(..) ''GENFUNCS_SYSTEM_FAILURE'' indicates that a standard
						library 	function or a system call failed.

						(..) ''GENFUNCS_MEMORY_FAILURE'' indicates that the memory
						required for operation of the function could not be
						allocated.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	Returns from this function are as follow:

						(.) The manifest constant ''GENFUNCS_TRUE'' if the parameter
						was matched.

						(.) Otherwise, the manifest constant ''GENFUNCS_FALSE'' is
						returned.

   NOTES       :	This function uses ``GEN_ArgParseTruth`` to perform the
						parse.

   CAVEATS     :	

   SEE ALSO    :	GEN_BARG_LogDir
						GEN_BARG_LogQuiet
						GEN_ArgParseTruth
						GEN_BUSE_LogFlag

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1995 - 2014 Michael L. Brock

   OUTPUT INDEX:	GEN_BARG_LogFlag
						Argument Parsing Functions:GEN_BARG_LogFlag
						GENFUNCS:Functions:GEN_BARG_LogFlag
						GENFUNCS:Argument Parsing Functions:GEN_BARG_LogFlag
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_BARG_LogFlag
						-LOGGING_FLAG=
						-LOGGING_FLAG= Parameter
						-LOGGING_FLAG= parameter

   PUBLISH NAME:	GEN_BARG_LogFlag

	ENTRY CLASS	:	Argument Parsing Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_BARG_LogFlag(const char *in_arg_ptr, unsigned int *in_arg_length,
	char **in_data_ptr, int *log_flag, int *error_code, char *error_text)
#else
int GEN_BARG_LogFlag(in_arg_ptr, in_arg_length, in_data_ptr, log_flag,
	error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
int           *log_flag;
int           *error_code;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;
	int            error_flag;

	*error_code = GENFUNCS_SUCCESS;
	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	if ((return_code = GEN_ArgParseTruth(in_arg_ptr, &error_flag, log_flag,
		error_text, arg_length, data_ptr, "-LOG=", "-LOGGING=", "-LOG_FLAG=",
		"-LOGGING_FLAG=", NULL)) == GENFUNCS_TRUE) {
		if (error_flag == GENFUNCS_TRUE)
			*error_code = GENFUNCS_BAD_ARGS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_BARG_LogQuiet

   SYNOPSIS    :	truth_flag = GEN_BARG_LogQuiet(in_arg_ptr, in_arg_length,
							in_data_ptr, log_quiet_flag, error_code, error_text);

						int            truth_flag;

						const char    *in_arg_ptr;

						unsigned int  *in_arg_length;

						char         **in_data_ptr;

						int           *log_quiet_flag;

						int           *error_code;

						char          *error_text;

   DESCRIPTION :	Parses a string to determine if it specifies that program
						logging is to be ``quiet``.

						Strings having the following syntax will be considered to
						have the appropriate format:

						<|@|>-''[''LOG''[''GING'']''_'']''QUIET=``boolean``

						The ``boolean`` component of this parameter has the
						following syntax for the value ''TRUE'':

						<|@|>''{''TRUE''|''ON''|''YES''|''T''|''Y''|''1''}''

						and the following syntax for the value ''FALSE'':

						<|@|>''{''FALSE''|''OFF''|''NO''|''F''|''N''|''0''}''

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_arg_ptr`` points to the string to be parsed.

						(.) ``in_arg_length`` is a pointer to an ''unsigned int''
						into which will be placed the length of the parameter name
						(if found).

						(-) For example, if the string ``in_arg_ptr`` is:

						{|-|}-LOG_QUIET=ON

						(-) The ''unsigned int'' to which ``in_arg_length`` points
						will be set to ''11'', the length of the string
						''-LOG_QUIET=''.

						(-) Note that if ``in_arg_length`` is a ''NULL'' pointer,
						it will not be de-referenced.

						(.) ``in_data_ptr`` points to a pointer to ''char'' into
						which will be placed a pointer to the first character of
						the ``boolean`` parameter component.

						(-) In the example above, ``in_data_ptr`` would be set to
						point to the first character of the string ''ON''.

						(-) Note that if ``in_data_ptr`` is a ''NULL'' pointer,
						it will not be de-referenced.

						(.) ``log_quiet_flag`` points to an ''int'' into which will be
						placed one the GENFUNCS Truth Codes corresponding to the
						``boolean`` parameter component (if found).

						(-) If the ``boolean`` parameter component is ''ON'',
						''TRUE'', or ''YES'', the ''int'' to which ``log_quiet_flag``
						points will be set to ''GENFUNCS_TRUE''.

						(-) If the ``boolean`` parameter component is ''OFF'',
						''FALSE'', or ''NO'', the ''int'' to which ``log_quiet_flag``
						points will be set to ''GENFUNCS_FALSE''.

						(.) ``error_code`` points to an ''int'' into which will be
						placed the GENFUNCS status code which results from the
						operation of this function.

						(..) ''GENFUNCS_SUCCESS'' if the function completes without
						error.

						(..) ''GENFUNCS_SYSTEM_FAILURE'' indicates that a standard
						library 	function or a system call failed.

						(..) ''GENFUNCS_MEMORY_FAILURE'' indicates that the memory
						required for operation of the function could not be
						allocated.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	Returns from this function are as follow:

						(.) The manifest constant ''GENFUNCS_TRUE'' if the parameter
						was matched.

						(.) Otherwise, the manifest constant ''GENFUNCS_FALSE'' is
						returned.

   NOTES       :	This function uses ``GEN_ArgParseTruth`` to perform the
						parse.

   CAVEATS     :	

   SEE ALSO    :	GEN_BARG_LogFlag
						GEN_ArgParseTruth
						GEN_BUSE_LogQuiet

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1995 - 2014 Michael L. Brock

   OUTPUT INDEX:	GEN_BARG_LogQuiet
						Argument Parsing Functions:GEN_BARG_LogQuiet
						GENFUNCS:Functions:GEN_BARG_LogQuiet
						GENFUNCS:Argument Parsing Functions:GEN_BARG_LogQuiet
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_BARG_LogQuiet
						-LOGGING_QUIET=
						-LOGGING_QUIET= Parameter
						-LOGGING_QUIET= parameter

   PUBLISH NAME:	GEN_BARG_LogQuiet

	ENTRY CLASS	:	Argument Parsing Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_BARG_LogQuiet(const char *in_arg_ptr, unsigned int *in_arg_length,
	char **in_data_ptr, int *log_quiet_flag, int *error_code, char *error_text)
#else
int GEN_BARG_LogQuiet(in_arg_ptr, in_arg_length, in_data_ptr, log_quiet_flag,
	error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
int           *log_quiet_flag;
int           *error_code;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;
	int            error_flag;

	*error_code = GENFUNCS_SUCCESS;
	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	if ((return_code = GEN_ArgParseTruth(in_arg_ptr, &error_flag,
		log_quiet_flag, error_text, arg_length, data_ptr, "-LOG_QUIET=",
		"-LOGGING_QUIET=", "-QUIET=", NULL)) == GENFUNCS_TRUE) {
		if (error_flag == GENFUNCS_TRUE)
			*error_code = GENFUNCS_BAD_ARGS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_BARG_CheckOnly

   SYNOPSIS    :	truth_flag = GEN_BARG_CheckOnly(in_arg_ptr, in_arg_length,
							in_data_ptr, check_only_flag, error_code, error_text);

						int            truth_flag;

						const char    *in_arg_ptr;

						unsigned int  *in_arg_length;

						char         **in_data_ptr;

						int           *check_only_flag;

						int           *error_code;

						char          *error_text;

   DESCRIPTION :	Parses a string to determine if it specifies that program
						logging is to be ``quiet``.

						Strings having the following syntax will be considered to
						have the appropriate format:

						<|@|>-CHECK''[''ING''][''_ONLY'']''=``boolean``

						The ``boolean`` component of this parameter has the
						following syntax for the value ''TRUE'':

						<|@|>''{''TRUE''|''ON''|''YES''|''T''|''Y''|''1''}''

						and the following syntax for the value ''FALSE'':

						<|@|>''{''FALSE''|''OFF''|''NO''|''F''|''N''|''0''}''

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_arg_ptr`` points to the string to be parsed.

						(.) ``in_arg_length`` is a pointer to an ''unsigned int''
						into which will be placed the length of the parameter name
						(if found).

						(-) For example, if the string ``in_arg_ptr`` is:

						{|-|}-CHECK_ONLY=ON

						(-) The ''unsigned int'' to which ``in_arg_length`` points
						will be set to ''12'', the length of the string
						''-CHECK_ONLY=''.

						(-) Note that if ``in_arg_length`` is a ''NULL'' pointer,
						it will not be de-referenced.

						(.) ``in_data_ptr`` points to a pointer to ''char'' into
						which will be placed a pointer to the first character of
						the ``boolean`` parameter component.

						(-) In the example above, ``in_data_ptr`` would be set to
						point to the first character of the string ''ON''.

						(-) Note that if ``in_data_ptr`` is a ''NULL'' pointer,
						it will not be de-referenced.

						(.) ``check_only_flag`` points to an ''int'' into which will be
						placed one the GENFUNCS Truth Codes corresponding to the
						``boolean`` parameter component (if found).

						(-) If the ``boolean`` parameter component is ''ON'',
						''TRUE'', or ''YES'', the ''int'' to which ``check_only_flag``
						points will be set to ''GENFUNCS_TRUE''.

						(-) If the ``boolean`` parameter component is ''OFF'',
						''FALSE'', or ''NO'', the ''int'' to which ``check_only_flag``
						points will be set to ''GENFUNCS_FALSE''.

						(.) ``error_code`` points to an ''int'' into which will be
						placed the GENFUNCS status code which results from the
						operation of this function.

						(..) ''GENFUNCS_SUCCESS'' if the function completes without
						error.

						(..) ''GENFUNCS_SYSTEM_FAILURE'' indicates that a standard
						library 	function or a system call failed.

						(..) ''GENFUNCS_MEMORY_FAILURE'' indicates that the memory
						required for operation of the function could not be
						allocated.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	Returns from this function are as follow:

						(.) The manifest constant ''GENFUNCS_TRUE'' if the parameter
						was matched.

						(.) Otherwise, the manifest constant ''GENFUNCS_FALSE'' is
						returned.

   NOTES       :	This function uses ``GEN_ArgParseTruth`` to perform the
						parse.

   CAVEATS     :	

   SEE ALSO    :	GEN_ArgParseTruth
						GEN_BUSE_CheckOnly

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1995 - 2014 Michael L. Brock

   OUTPUT INDEX:	GEN_BARG_CheckOnly
						Argument Parsing Functions:GEN_BARG_CheckOnly
						GENFUNCS:Functions:GEN_BARG_CheckOnly
						GENFUNCS:Argument Parsing Functions:GEN_BARG_CheckOnly
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_BARG_CheckOnly
						-CHECK_ONLY=
						-CHECK_ONLY= Parameter
						-CHECK_ONLY= parameter

   PUBLISH NAME:	GEN_BARG_CheckOnly

	ENTRY CLASS	:	Argument Parsing Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_BARG_CheckOnly(const char *in_arg_ptr, unsigned int *in_arg_length,
	char **in_data_ptr, int *check_only_flag, int *error_code, char *error_text)
#else
int GEN_BARG_CheckOnly(in_arg_ptr, in_arg_length, in_data_ptr,
	check_only_flag, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
int           *check_only_flag;
int           *error_code;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;
	int            error_flag;

	*error_code = GENFUNCS_SUCCESS;
	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	if ((return_code = GEN_ArgParseTruth(in_arg_ptr, &error_flag,
		check_only_flag, error_text, arg_length, data_ptr, "-CHECK=",
		"-CHECKING=", "-CHECK_ONLY=", "CHECKING_ONLY=", NULL)) ==
		GENFUNCS_TRUE) {
		if (error_flag == GENFUNCS_TRUE)
			*error_code = GENFUNCS_BAD_ARGS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_BARG_DebugLevel

   SYNOPSIS    :	truth_flag = GEN_BARG_DebugLevel(in_arg_ptr, in_arg_length,
							in_data_ptr, debug_level, error_code, error_text);

						int            truth_flag;

						const char    *in_arg_ptr;

						unsigned int  *in_arg_length;

						char         **in_data_ptr;

						int           *debug_level;

						int           *error_code;

						char          *error_text;

   DESCRIPTION :	Parses a string to determine if it is a valid GENFUNCS
						debugging level parameter.

						Strings having the following syntax will be considered to
						have the appropriate format:

						<|@|>-DEBUG''[''GING''][''_LEVEL'']''=``debug-level``

						The ``debug-level`` component of this parameter has the
						following syntax:

						<|@|>''{''NONE''|''BASIC''|''COMPLETE''}''

						If this function finds a match, the value of the appropriate
						GENFUNCS debugging level manifest constant is copied to the
						''int'' to which the ``debug_level`` parameter points.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_arg_ptr`` points to the string to be parsed.

						(.) ``in_arg_length`` is a pointer to an ''unsigned int''
						into which will be placed the length of the parameter name
						(if found).

						(-) For example, if the string ``in_arg_ptr`` is:

						{|-|}-DEBUG_LEVEL=BASIC

						(-) The ''unsigned int'' to which ``in_arg_length`` points
						will be set to ''13'', the length of the string
						''-DEBUG_LEVEL=''.

						(-) Note that if ``in_arg_length`` is a ''NULL'' pointer,
						it will not be de-referenced.

						(.) ``in_data_ptr`` points to a pointer to ''char'' into
						which will be placed a pointer to the first character of
						the ``debug-level`` parameter component.

						(-) In the example above, ``in_data_ptr`` would be set to
						point to the first character of the string ''BASIC''.

						(-) Note that if ``in_data_ptr`` is a ''NULL'' pointer,
						it will not be de-referenced.

						(.) ``debug_level`` is a pointer to an ''int'' into which
						will be placed the value of the ``debug-level`` parameter
						component. This will be equal to one of the GENFUNCS
						debugging level manifest constants:

						(..) ''GEN_DEBUG_LEVEL_NONE'' if the ``debug-level``
						component of the parameter is ''NONE''.

						(..) ''GEN_DEBUG_LEVEL_BASIC'' if the ``debug-level``
						component of the parameter is ''BASIC''.

						(..) ''GEN_DEBUG_LEVEL_COMPLETE'' if the
						``debug-level`` component of the parameter is ''COMPLETE''
						or ''ALL''.

						(.) ``error_code`` points to an ''int'' into which will be
						placed the GENFUNCS status code which results from the
						operation of this function.

						(..) ''GENFUNCS_SUCCESS'' if the function completes without
						error.

						(..) ''GENFUNCS_SYSTEM_FAILURE'' indicates that a standard
						library function or a system call failed.

						(..) ''GENFUNCS_MEMORY_FAILURE'' indicates that the memory
						required for operation of the function could not be
						allocated.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	Returns from this function are as follow:

						(.) The manifest constant ''GENFUNCS_TRUE'' if the parameter
						was matched.

						(.) Otherwise, the manifest constant ''GENFUNCS_FALSE'' is
						returned.

   NOTES       :	This function uses ``GEN_ArgParse`` to perform the parse.

   CAVEATS     :	

   SEE ALSO    :	GEN_BUSE_DebugLevel
						GEN_ArgParse

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1995 - 2014 Michael L. Brock

   OUTPUT INDEX:	GEN_BARG_DebugLevel
						Argument Parsing Functions:GEN_BARG_DebugLevel
						GENFUNCS:Functions:GEN_BARG_DebugLevel
						GENFUNCS:Argument Parsing Functions:GEN_BARG_DebugLevel
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_BARG_DebugLevel
						-DEBUGGING_LEVEL=
						-DEBUGGING_LEVEL= Parameter
						-DEBUGGING_LEVEL= parameter

   PUBLISH NAME:	GEN_BARG_DebugLevel

	ENTRY CLASS	:	Argument Parsing Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_BARG_DebugLevel(const char *in_arg_ptr, unsigned int *in_arg_length,
	char **in_data_ptr, int *debug_level, int *error_code, char *error_text)
#else
int GEN_BARG_DebugLevel(in_arg_ptr, in_arg_length, in_data_ptr, debug_level,
	error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
int           *debug_level;
int           *error_code;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;

	*error_code = GENFUNCS_SUCCESS;
	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	if ((return_code = GEN_ArgParse(in_arg_ptr, arg_length, data_ptr,
		"-DEBUG_LEVEL=", "-DEBUGGING_LEVEL=", "-DEBUG=", "-DEBUGGING=",
		NULL)) == GENFUNCS_TRUE) {
		if (!stricmp(*data_ptr, "NONE"))
			*debug_level = GEN_DEBUG_LEVEL_NONE;
		else if (!stricmp(*data_ptr, "BASIC"))
			*debug_level = GEN_DEBUG_LEVEL_BASIC;
		else if ((!stricmp(*data_ptr, "ALL")) ||
			(!stricmp(*data_ptr, "COMPLETE")))
			*debug_level = GEN_DEBUG_LEVEL_COMPLETE;
		else {
			GEN_BARG_BadComponentMsg(in_arg_ptr, *arg_length, *data_ptr,
				"{NONE|BASIC|{COMPLETE|ALL}}", error_text);
			*error_code = GENFUNCS_BAD_ARGS_FAILURE;
      }
	}

	*error_code = (*error_code == GENFUNCS_FALSE) ? GENFUNCS_SUCCESS :
		GENFUNCS_BAD_ARGS_FAILURE;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_BARG_DBDebugFlag

   SYNOPSIS    :	truth_flag = GEN_BARG_DBDebugFlag(in_arg_ptr, in_arg_length,
							in_data_ptr, db_debug_flag, error_code, error_text);

						int            truth_flag;

						const char    *in_arg_ptr;

						unsigned int  *in_arg_length;

						char         **in_data_ptr;

						int           *db_debug_flag;

						int           *error_code;

						char          *error_text;

   DESCRIPTION :	Parses a string to determine if it is a valid GENFUNCS
						database debugging flag parameter.

						Strings having the following syntax will be considered to
						have the appropriate format:

						<|@|>-''{''DB''|''DATA''[''_'']''BASE''}''_DEBUG''[''GING'']''=``boolean``

						The ``boolean`` component of this parameter has the
						following syntax for the value ''TRUE'':

						<|@|>''{''TRUE''|''ON''|''YES''|''T''|''Y''|''1''}''

						and the following syntax for the value ''FALSE'':

						<|@|>''{''FALSE''|''OFF''|''NO''|''F''|''N''|''0''}''

						If this function finds a match, the value of the appropriate
						GENFUNCS truth code manifest constant is copied to the
						''int'' to which the ``db_debug_flag`` parameter points.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_arg_ptr`` points to the string to be parsed.

						(.) ``in_arg_length`` is a pointer to an ''unsigned int''
						into which will be placed the length of the parameter name
						(if found).

						(-) For example, if the string ``in_arg_ptr`` is:

						{|-|}-DB_DEBUG=ON

						(-) The ''unsigned int'' to which ``in_arg_length`` points
						will be set to ''10'', the length of the string
						''-DB_DEBUG=''.

						(-) Note that if ``in_arg_length`` is a ''NULL'' pointer,
						it will not be de-referenced.

						(.) ``in_data_ptr`` points to a pointer to ''char'' into
						which will be placed a pointer to the first character of
						the ``boolean`` parameter component.

						(-) In the example above, ``in_data_ptr`` would be set to
						point to the first character of the string ''ON''.

						(-) Note that if ``in_data_ptr`` is a ''NULL'' pointer,
						it will not be de-referenced.

						(.) ``db_debug_flag`` points to an ''int'' into which will
						be placed one the GENFUNCS Truth Codes corresponding to the
						``boolean`` parameter component (if found).

						(-) If the ``boolean`` parameter component is ''ON'',
						''TRUE'', or ''YES'', the ''int'' to which ``db_debug_flag``
						points will be set to ''GENFUNCS_TRUE''.

						(-) If the ``boolean`` parameter component is ''OFF'',
						''FALSE'', or ''NO'', the ''int'' to which ``db_debug_flag``
						points will be set to ''GENFUNCS_FALSE''.

						(.) ``error_code`` points to an ''int'' into which will be
						placed the GENFUNCS status code which results from the
						operation of this function.

						(..) ''GENFUNCS_SUCCESS'' if the function completes without
						error.

						(..) ''GENFUNCS_SYSTEM_FAILURE'' indicates that a standard
						library 	function or a system call failed.

						(..) ''GENFUNCS_MEMORY_FAILURE'' indicates that the memory
						required for operation of the function could not be
						allocated.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	Returns from this function are as follow:

						(.) The manifest constant ''GENFUNCS_TRUE'' if the parameter
						was matched.

						(.) Otherwise, the manifest constant ''GENFUNCS_FALSE'' is
						returned.

   NOTES       :	This function uses ``GEN_ArgParseTruth`` to perform the
						parse.

   CAVEATS     :	

   SEE ALSO    :	GEN_BUSE_DBDebugFlag
						GEN_BARG_SQLDebugFlag
						GEN_ArgParseTruth

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1995 - 2014 Michael L. Brock

   OUTPUT INDEX:	GEN_BARG_DBDebugFlag
						Argument Parsing Functions:GEN_BARG_DebugLevel
						GENFUNCS:Functions:GEN_BARG_DebugLevel
						GENFUNCS:Argument Parsing Functions:GEN_BARG_DebugLevel
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_BARG_DBDebugFlag
						-DATA_BASE_DEBUGGING=
						-DATA_BASE_DEBUGGING= Parameter
						-DATA_BASE_DEBUGGING= parameter

   PUBLISH NAME:	GEN_BARG_DBDebugFlag

	ENTRY CLASS	:	Argument Parsing Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_BARG_DBDebugFlag(const char *in_arg_ptr, unsigned int *in_arg_length,
	char **in_data_ptr, int *db_debug_flag, int *error_code, char *error_text)
#else
int GEN_BARG_DBDebugFlag(in_arg_ptr, in_arg_length, in_data_ptr,
	db_debug_flag, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
int           *db_debug_flag;
int           *error_code;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;

	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	return_code = GEN_ArgParseTruth(in_arg_ptr, error_code, db_debug_flag,
		error_text, arg_length, data_ptr, "-DB_DEBUG=", "-DB_DEBUGGING=",
		"-DATA_BASE_DEBUG=", "-DATA_BASE_DEBUGGING=", "-DATABASE_DEBUG=",
		"-DATABASE_DEBUGGING=", NULL);

	*error_code = (*error_code == GENFUNCS_FALSE) ? GENFUNCS_SUCCESS :
		GENFUNCS_BAD_ARGS_FAILURE;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_BARG_SQLDebugFlag

   SYNOPSIS    :	truth_flag = GEN_BARG_SQLDebugFlag(in_arg_ptr,
							in_arg_length, in_data_ptr, sql_debug_flag, error_code,
							error_text);

						int            truth_flag;

						const char    *in_arg_ptr;

						unsigned int  *in_arg_length;

						char         **in_data_ptr;

						int           *sql_debug_flag;

						int           *error_code;

						char          *error_text;

   DESCRIPTION :	Parses a string to determine if it is a valid GENFUNCS
						SQL debugging flag parameter.

						Strings having the following syntax will be considered to
						have the appropriate format:

						<|@|>-SQL_DEBUG''[''GING'']''=``boolean``

						The ``boolean`` component of this parameter has the
						following syntax for the value ''TRUE'':

						<|@|>''{''TRUE''|''ON''|''YES''|''T''|''Y''|''1''}''

						and the following syntax for the value ''FALSE'':

						<|@|>''{''FALSE''|''OFF''|''NO''|''F''|''N''|''0''}''

						If this function finds a match, the value of the appropriate
						GENFUNCS truth code manifest constant is copied to the
						''int'' to which the ``sql_debug_flag`` parameter points.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_arg_ptr`` points to the string to be parsed.

						(.) ``in_arg_length`` is a pointer to an ''unsigned int''
						into which will be placed the length of the parameter name
						(if found).

						(-) For example, if the string ``in_arg_ptr`` is:

						{|-|}-SQL_DEBUG=ON

						(-) The ''unsigned int'' to which ``in_arg_length`` points
						will be set to ''11'', the length of the string
						''-SQL_DEBUG=''.

						(-) Note that if ``in_arg_length`` is a ''NULL'' pointer,
						it will not be de-referenced.

						(.) ``in_data_ptr`` points to a pointer to ''char'' into
						which will be placed a pointer to the first character of
						the ``boolean`` parameter component.

						(-) In the example above, ``in_data_ptr`` would be set to
						point to the first character of the string ''ON''.

						(-) Note that if ``in_data_ptr`` is a ''NULL'' pointer,
						it will not be de-referenced.

						(.) ``sql_debug_flag`` points to an ''int'' into which will
						be placed one the GENFUNCS Truth Codes corresponding to the
						``boolean`` parameter component (if found).

						(-) If the ``boolean`` parameter component is ''ON'',
						''TRUE'', or ''YES'', the ''int'' to which ``sql_debug_flag``
						points will be set to ''GENFUNCS_TRUE''.

						(-) If the ``boolean`` parameter component is ''OFF'',
						''FALSE'', or ''NO'', the ''int'' to which ``sql_debug_flag``
						points will be set to ''GENFUNCS_FALSE''.

						(.) ``error_code`` points to an ''int'' into which will be
						placed the GENFUNCS status code which results from the
						operation of this function.

						(..) ''GENFUNCS_SUCCESS'' if the function completes without
						error.

						(..) ''GENFUNCS_SYSTEM_FAILURE'' indicates that a standard
						library 	function or a system call failed.

						(..) ''GENFUNCS_MEMORY_FAILURE'' indicates that the memory
						required for operation of the function could not be
						allocated.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	Returns from this function are as follow:

						(.) The manifest constant ''GENFUNCS_TRUE'' if the parameter
						was matched.

						(.) Otherwise, the manifest constant ''GENFUNCS_FALSE'' is
						returned.

   NOTES       :	This function uses ``GEN_ArgParse`` to perform the parse.

   CAVEATS     :	

   SEE ALSO    :	GEN_BUSE_SQLDebugFlag
						GEN_BARG_DBDebugFlag
						GEN_ArgParseTruth

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1995 - 2014 Michael L. Brock

   OUTPUT INDEX:	GEN_BARG_SQLDebugFlag
						Argument Parsing Functions:GEN_BARG_DebugLevel
						GENFUNCS:Functions:GEN_BARG_DebugLevel
						GENFUNCS:Argument Parsing Functions:GEN_BARG_DebugLevel
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_BARG_SQLDebugFlag
						-SQL_DEBUGGING=
						-SQL_DEBUGGING= Parameter
						-SQL_DEBUGGING= parameter

   PUBLISH NAME:	GEN_BARG_SQLDebugFlag

	ENTRY CLASS	:	Argument Parsing Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_BARG_SQLDebugFlag(const char *in_arg_ptr, unsigned int *in_arg_length,
	char **in_data_ptr, int *sql_debug_flag, int *error_code, char *error_text)
#else
int GEN_BARG_SQLDebugFlag(in_arg_ptr, in_arg_length, in_data_ptr,
	sql_debug_flag, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
int           *sql_debug_flag;
int           *error_code;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;

	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	return_code = GEN_ArgParseTruth(in_arg_ptr, error_code, sql_debug_flag,
		error_text, arg_length, data_ptr, "-SQL_DEBUG=", "-SQL_DEBUGGING=",
		NULL);

	*error_code = (*error_code == GENFUNCS_FALSE) ? GENFUNCS_SUCCESS :
		GENFUNCS_BAD_ARGS_FAILURE;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_BARG_BasicParamAlloc

   SYNOPSIS    :	return_code = GEN_BARG_BasicParamAlloc(in_arg_ptr,
							arg_length, data_ptr, alloc_ptr, error_text);

						int            return_code;

						const char    *in_arg_ptr;

						unsigned int   arg_length;

						const char    *data_ptr;

						char         **alloc_ptr;

						char          *error_text;

   DESCRIPTION :	Copies a string from a parsed parameter.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_arg_ptr`` points to the string to the parsed
						parameter.

						(.) ``in_arg_length`` is the length of the parameter name.

						(.) ``data_ptr`` points to the first character of the
						parameter to be copied.

						(.) ``alloc_ptr`` points to a pointer to ''char'' into which
						will be placed a pointer to memory allocated to hold the
						string to which ``data_ptr`` points. It is the
						responsibility of the application programmer to free this
						memory with ``free()``.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if the function completes without
						error. ''GENFUNCS_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero GENFUNCS return codes
						indicative of error.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1995 - 2014 Michael L. Brock

   OUTPUT INDEX:	GEN_BARG_BasicParamAlloc
						Argument Parsing Functions:GEN_BARG_BasicParamAlloc
						GENFUNCS:Functions:GEN_BARG_BasicParamAlloc
						GENFUNCS:Argument Parsing Functions:GEN_BARG_BasicParamAlloc
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_BARG_BasicParamAlloc

   PUBLISH NAME:	GEN_BARG_BasicParamAlloc

	ENTRY CLASS	:	Argument Parsing Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_BARG_BasicParamAlloc(const char *in_arg_ptr, unsigned int arg_length,
	const char *data_ptr, char **alloc_ptr, char *error_text)
#else
int GEN_BARG_BasicParamAlloc(in_arg_ptr, arg_length, data_ptr, alloc_ptr,
	error_text)
const char    *in_arg_ptr;
unsigned int   arg_length;
const char    *data_ptr;
char         **alloc_ptr;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = GENFUNCS_SUCCESS;

	if (!(*data_ptr))
		*alloc_ptr = NULL;
	else if ((*alloc_ptr = strdup(data_ptr)) == NULL) {
		sprintf(error_text,
			"%s '%-*.*s' parameter ('%-.500s') --- %u bytes required.",
			"Unable to allocate memory for the", ((int) arg_length),
			((int) arg_length), in_arg_ptr, data_ptr, strlen(data_ptr) + 1);
		return_code = GENFUNCS_MEMORY_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_BARG_BasicPathExpand

   SYNOPSIS    :	return_code = GEN_BARG_BasicPathExpand(in_arg_ptr,
							arg_length, data_ptr, alloc_ptr, error_text);

						int            return_code;

						const char    *in_arg_ptr;

						unsigned int   arg_length;

						const char    *data_ptr;

						char         **alloc_ptr;

						char          *error_text;

   DESCRIPTION :	Copies a string representing a file or directory name from
						a parsed parameter. The file or path name is expanded to
						its fully-qualified form and memory is allocated to hold it.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_arg_ptr`` points to the string to parsed parameter.

						(.) ``in_arg_length`` is the length of the parameter name.

						(.) ``data_ptr`` points to the first character of the
						parameter to be copied.

						(.) ``alloc_ptr`` points to a pointer to ''char'' into which
						will be placed a pointer to memory allocated to hold the
						fully-expanded form of the file or directory name to which
						``data_ptr`` points. It is the responsibility of the
						application programmer to free this memory with ``free()``.

						(-) This function uses ``GEN_ExpandToFullPathName`` to
						expand the file or directory name.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if the function completes without
						error. ''GENFUNCS_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero GENFUNCS return codes
						indicative of error.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	GEN_ExpandToFullPathName

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1995 - 2014 Michael L. Brock

   OUTPUT INDEX:	GEN_BARG_BasicPathExpand
						Argument Parsing Functions:GEN_BARG_BasicPathExpand
						GENFUNCS:Functions:GEN_BARG_BasicPathExpand
						GENFUNCS:Argument Parsing Functions:GEN_BARG_BasicPathExpand
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_BARG_BasicPathExpand

   PUBLISH NAME:	GEN_BARG_BasicPathExpand

	ENTRY CLASS	:	Argument Parsing Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_BARG_BasicPathExpand(const char *in_arg_ptr, unsigned int arg_length,
	const char *data_ptr, char **alloc_ptr, char *error_text)
#else
int GEN_BARG_BasicPathExpand(in_arg_ptr, arg_length, data_ptr, alloc_ptr,
	error_text)
const char    *in_arg_ptr;
unsigned int   arg_length;
const char    *data_ptr;
char         **alloc_ptr;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code = GENFUNCS_SUCCESS;
	char tmp_error_text[GENFUNCS_MAX_ERROR_TEXT];

	if (!(*data_ptr))
		*alloc_ptr = NULL;
	else if ((return_code = GEN_ExpandToFullPathName(data_ptr, alloc_ptr,
		tmp_error_text)) != GENFUNCS_SUCCESS)
		sprintf(error_text, "%s '%-*.*s' parameter ('%-.500s'): %-.400s",
			"Unable to determine the fully-qualified path name for the",
			((int) arg_length), ((int) arg_length), in_arg_ptr, data_ptr,
			tmp_error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_BARG_BadComponentMsg

   SYNOPSIS    :	GEN_BARG_BadComponentMsg(in_arg_ptr, arg_length, data_ptr,
							expected_string, error_text);

						const char    *in_arg_ptr;

						unsigned int   arg_length;

						const char    *data_ptr;

						const char    *expected_string;

						char          *error_text;

   DESCRIPTION :	Constructs an error message for parsed arguments with
						invalid components.

						The error message constructed takes the following form if
						the ``expected_string`` parameter is not ''NULL'':

						<|@|> Invalid '``in_arg_ptr``' parameter ('``data_ptr``')
						--- expected ``expected_string``

						If the ``expected_string`` parameter is ''NULL'', the
						error message will instead take the form:

						<|@|> Invalid '``in_arg_ptr``' parameter ('``data_ptr``')

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_arg_ptr`` points to the string to parsed parameter.

						(.) ``in_arg_length`` is the length of the parameter name.

						(.) ``data_ptr`` points to the first character of the
						parameter to be copied.

						(.) ``expected_string`` points to a string which describes
						the expected format of the invalid component.

						(-) If ``expected_string`` is ''NULL'', it will not be
						used in constructing the error message.

						(.) ``error_text`` points to a string into which this
						function will place the error message constructed.

						(-) The string allocated for this purpose should be at least
						''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	Void.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1995 - 2014 Michael L. Brock

   OUTPUT INDEX:	GEN_BARG_BadComponentMsg
						Argument Parsing Functions:GEN_BARG_BadComponentMsg
						GENFUNCS:Functions:GEN_BARG_BadComponentMsg
						GENFUNCS:Argument Parsing Functions:GEN_BARG_BadComponentMsg
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_BARG_BadComponentMsg

   PUBLISH NAME:	GEN_BARG_BadComponentMsg

	ENTRY CLASS	:	Argument Parsing Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void GEN_BARG_BadComponentMsg(const char *in_arg_ptr, unsigned int arg_length,
	const char *data_ptr, const char *expected_string, char *error_text)
#else
void GEN_BARG_BadComponentMsg(in_arg_ptr, arg_length, data_ptr,
	expected_string, error_text)
const char    *in_arg_ptr;
unsigned int   arg_length;
const char    *data_ptr;
const char    *expected_string;
char          *error_text;
#endif /* #ifndef NARGS */
{
	sprintf(error_text, "Invalid '%-*.*s' parameter ('%-.500s')",
		((int) arg_length), ((int) arg_length), in_arg_ptr, data_ptr);

	if (expected_string != NULL)
		strcat(strcat(error_text, " --- expected "), expected_string);
}
/*	***********************************************************************	*/

