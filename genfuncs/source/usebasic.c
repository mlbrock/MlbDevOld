/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	GENFUNCS General Functions Library Source Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Argument usage description support for executables.

	Revision History	:	1995-05-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2015.
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

   NAME        :	GEN_BUSE_Help

   SYNOPSIS    :	return_code = GEN_BUSE_Help(base_arg_ptr, optional_flag,
							extra_usage_list, usage_count, usage_list, error_text);

						int             return_code;

						const char     *base_arg_ptr;

						int             optional_flag;

						char          **extra_usage_list;

						unsigned int   *usage_count;

						char         ***usage_list;

						char           *error_text;

   DESCRIPTION :	Appends the usage text for the ''-HELP'' parameter to an
						array of pointers to ''char''.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``base_arg_ptr`` points to a string which may be used
						to preface the parameter name. ``base_arg_ptr`` may be
						''NULL''.

						(.) ``optional_flag`` indicates whether the parameter is
						optional. It may take either of the values ''GENFUNCS_TRUE''
						or ''GENFUNCS_FALSE''.

						(-) If ``optional_flag`` is equal to ''GENFUNCS_TRUE'', this
						function will surround the parameter name with square
						brackets (''['' and '']'') to indicate optionality.

						(.) ``extra_usage_list`` is an array of pointers to ''char''
						which may be used add parameter usage text for the
						parameter.

						(-) If the application programmer does not desire added
						parameter text, ``extra_usage_text`` may be ''NULL''.

						(-) If added parameter text is desired, the last element
						in the array ``extra_usage_list`` must be a ''NULL''
						pointer. This is to indicate to the function that no
						further array elements are to be added.

						(.) ``usage_count`` is the number of elements in the
						array ``usage_list``.

						(.) ``usage_list`` is a pointer to an array of pointers
						to ''char'' into which this function will place lines
						added to the usage list.

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

   SEE ALSO    :	GEN_BUSE_BasicConstruct

   EXAMPLES    :	If this function is invoked with ``base_arg_ptr`` equal to
						''NULL'', ``optional_flag`` equal to ''GENFUNCS_FALSE'' and
						``extra_usage_list`` equal to ''NULL'', the following lines
						will be added to the array ``usage_list``:

{|@|}-H[ELP]
   Displays this text.

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1995 - 2015 Michael L. Brock

   OUTPUT INDEX:	GEN_BUSE_Help
						Argument Parsing Functions:GEN_BUSE_Help
						GENFUNCS:Functions:GEN_BUSE_Help
						GENFUNCS:Argument Parsing Functions:GEN_BUSE_Help
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_BUSE_Help
						-HELP
						-HELP Parameter
						-HELP parameter

   PUBLISH NAME:	GEN_BUSE_Help

	ENTRY CLASS	:	Argument Parsing Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_BUSE_Help(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count, char ***usage_list,
	char *error_text)
#else
int GEN_BUSE_Help(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char          **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	static const char *arg_name         = "-H[ELP]";
	static char       *arg_usage_list[] = {
	"		Displays this text.",
	"\n",
	NULL
};

	return(GEN_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_BUSE_LogDir

   SYNOPSIS    :	GEN_BUSE_LogDir

   DESCRIPTION :	return_code = GEN_BUSE_LogDir(base_arg_ptr, optional_flag,
							extra_usage_list, usage_count, usage_list, error_text);

						int             return_code;

						const char     *base_arg_ptr;

						int             optional_flag;

						char          **extra_usage_list;

						unsigned int   *usage_count;

						char         ***usage_list;

						char           *error_text;

   DESCRIPTION :	Appends the usage text for the ''-LOGGING_DIRECTORY=''
						parameter to an array of pointers to ''char''.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``base_arg_ptr`` points to a string which may be used
						to preface the parameter name. ``base_arg_ptr`` may be
						''NULL''.

						(.) ``optional_flag`` indicates whether the parameter is
						optional. It may take either of the values ''GENFUNCS_TRUE''
						or ''GENFUNCS_FALSE''.

						(-) If ``optional_flag`` is equal to ''GENFUNCS_TRUE'', this
						function will surround the parameter name with square
						brackets (''['' and '']'') to indicate optionality.

						(.) ``extra_usage_list`` is an array of pointers to ''char''
						which may be used add parameter usage text for the
						parameter.

						(-) If the application programmer does not desire added
						parameter text, ``extra_usage_text`` may be ''NULL''.

						(-) If added parameter text is desired, the last element
						in the array ``extra_usage_list`` must be a ''NULL''
						pointer. This is to indicate to the function that no
						further array elements are to be added.

						(.) ``usage_count`` is the number of elements in the
						array ``usage_list``.

						(.) ``usage_list`` is a pointer to an array of pointers
						to ''char'' into which this function will place lines
						added to the usage list.

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

   SEE ALSO    :	GEN_BUSE_LogFlag
						GEN_BUSE_LogQuiet
						GEN_BUSE_BasicConstruct
						GEN_BARG_LogDir

   EXAMPLES    :	If this function is invoked with ``base_arg_ptr`` equal to
						''NULL'', ``optional_flag`` equal to ''GENFUNCS_FALSE'' and
						``extra_usage_list`` equal to ''NULL'', the following lines
						will be added to the array ``usage_list``:

{|@|}-LOG[GING]_DIR[ECTORY]=<log-file-dir-name>
   Specifies the directory within which the log file is to be created.

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1995 - 2015 Michael L. Brock

   OUTPUT INDEX:	GEN_BUSE_LogDir
						Argument Parsing Functions:GEN_BUSE_LogDir
						GENFUNCS:Functions:GEN_BUSE_LogDir
						GENFUNCS:Argument Parsing Functions:GEN_BUSE_LogDir
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_BUSE_LogDir

   PUBLISH NAME:	GEN_BUSE_LogDir

	ENTRY CLASS	:	Argument Parsing Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_BUSE_LogDir(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count, char ***usage_list,
	char *error_text)
#else
int GEN_BUSE_LogDir(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char          **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	static const char *arg_name         =
		"-LOG[GING]_DIR[ECTORY]=<log-file-dir-name>";
	static char       *arg_usage_list[] = {
	"		Specifies the directory within which the log file is to be created.",
	"\n",
	NULL
};

	return(GEN_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_BUSE_LogFlag

   SYNOPSIS    :	return_code = GEN_BUSE_LogFlag(base_arg_ptr, optional_flag,
							extra_usage_list, usage_count, usage_list, error_text);

						int             return_code;

						const char     *base_arg_ptr;

						int             optional_flag;

						char          **extra_usage_list;

						unsigned int   *usage_count;

						char         ***usage_list;

						char           *error_text;

   DESCRIPTION :	Appends the usage text for the ''-LOGGING_FLAG=''
						parameter to an array of pointers to ''char''.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``base_arg_ptr`` points to a string which may be used
						to preface the parameter name. ``base_arg_ptr`` may be
						''NULL''.

						(.) ``optional_flag`` indicates whether the parameter is
						optional. It may take either of the values ''GENFUNCS_TRUE''
						or ''GENFUNCS_FALSE''.

						(-) If ``optional_flag`` is equal to ''GENFUNCS_TRUE'', this
						function will surround the parameter name with square
						brackets (''['' and '']'') to indicate optionality.

						(.) ``extra_usage_list`` is an array of pointers to ''char''
						which may be used add parameter usage text for the
						parameter.

						(-) If the application programmer does not desire added
						parameter text, ``extra_usage_text`` may be ''NULL''.

						(-) If added parameter text is desired, the last element
						in the array ``extra_usage_list`` must be a ''NULL''
						pointer. This is to indicate to the function that no
						further array elements are to be added.

						(.) ``usage_count`` is the number of elements in the
						array ``usage_list``.

						(.) ``usage_list`` is a pointer to an array of pointers
						to ''char'' into which this function will place lines
						added to the usage list.

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

   SEE ALSO    :	GEN_BUSE_LogDir
						GEN_BUSE_LogQuiet
						GEN_BUSE_BasicConstruct
						GEN_BARG_LogFlag

   EXAMPLES    :	If this function is invoked with ``base_arg_ptr`` equal to
						''NULL'', ``optional_flag`` equal to ''GENFUNCS_FALSE'' and
						``extra_usage_list`` equal to ''NULL'', the following lines
						will be added to the array ``usage_list``:

{|@|}-LOG[GING][_FLAG]=<boolean>
   Specifies whether the program is to emit its progress to a log file.
   
   The <boolean> component of this parameter has the following syntax
   for the value 'TRUE':
 
      { TRUE | ON | YES | T | Y | 1 }
 
   and the following syntax for the value 'FALSE':
 
      { FALSE | OFF | NO | F | N | 0 }

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1995 - 2015 Michael L. Brock

   OUTPUT INDEX:	GEN_BUSE_LogFlag
						Argument Parsing Functions:GEN_BUSE_LogFlag
						GENFUNCS:Functions:GEN_BUSE_LogFlag
						GENFUNCS:Argument Parsing Functions:GEN_BUSE_LogFlag
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_BUSE_LogFlag

   PUBLISH NAME:	GEN_BUSE_LogFlag

	ENTRY CLASS	:	Argument Parsing Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_BUSE_LogFlag(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count, char ***usage_list,
	char *error_text)
#else
int GEN_BUSE_LogFlag(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char          **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int                return_code;
	static const char *arg_name         = "-LOG[GING][_FLAG]=<boolean>";
	static char       *arg_usage_list[] = {
	"		Specifies whether the program is to emit its progress to a log \
file.",
	"\n",
	NULL
};

	if ((return_code = GEN_BUSE_BasicConstruct(base_arg_ptr, arg_name,
		optional_flag, arg_usage_list, extra_usage_list, usage_count,
		usage_list, error_text)) == GENFUNCS_SUCCESS)
		return_code = GEN_BUSE_AppendBooleanText(usage_count, usage_list, -1,
			error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_BUSE_LogQuiet

   SYNOPSIS    :	return_code = GEN_BUSE_LogQuiet(base_arg_ptr, optional_flag,
							extra_usage_list, usage_count, usage_list, error_text);

						int             return_code;

						const char     *base_arg_ptr;

						int             optional_flag;

						char          **extra_usage_list;

						unsigned int   *usage_count;

						char         ***usage_list;

						char           *error_text;

   DESCRIPTION :	Appends the usage text for the ''-LOGGING_QUIET=''
						parameter to an array of pointers to ''char''.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``base_arg_ptr`` points to a string which may be used
						to preface the parameter name. ``base_arg_ptr`` may be
						''NULL''.

						(.) ``optional_flag`` indicates whether the parameter is
						optional. It may take either of the values ''GENFUNCS_TRUE''
						or ''GENFUNCS_FALSE''.

						(-) If ``optional_flag`` is equal to ''GENFUNCS_TRUE'', this
						function will surround the parameter name with square
						brackets (''['' and '']'') to indicate optionality.

						(.) ``extra_usage_list`` is an array of pointers to ''char''
						which may be used add parameter usage text for the
						parameter.

						(-) If the application programmer does not desire added
						parameter text, ``extra_usage_text`` may be ''NULL''.

						(-) If added parameter text is desired, the last element
						in the array ``extra_usage_list`` must be a ''NULL''
						pointer. This is to indicate to the function that no
						further array elements are to be added.

						(.) ``usage_count`` is the number of elements in the
						array ``usage_list``.

						(.) ``usage_list`` is a pointer to an array of pointers
						to ''char'' into which this function will place lines
						added to the usage list.

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

   SEE ALSO    :	GEN_BUSE_LogFlag
						GEN_BUSE_BasicConstruct
						GEN_BARG_LogQuiet

   EXAMPLES    :	If this function is invoked with ``base_arg_ptr`` equal to
						''NULL'', ``optional_flag`` equal to ''GENFUNCS_FALSE'' and
						``extra_usage_list`` equal to ''NULL'', the following lines
						will be added to the array ``usage_list``:

{|@|}-LOG[GING]_QUIET=<boolean>
   Specifies whether the program is to emit log and status errors to
   'stderr'.
   
   The <boolean> component of this parameter has the following syntax
   for the value 'TRUE':
 
      { TRUE | ON | YES | T | Y | 1 }
 
   and the following syntax for the value 'FALSE':
 
      { FALSE | OFF | NO | F | N | 0 }

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1995 - 2015 Michael L. Brock

   OUTPUT INDEX:	GEN_BUSE_LogQuiet
						Argument Parsing Functions:GEN_BUSE_LogQuiet
						GENFUNCS:Functions:GEN_BUSE_LogQuiet
						GENFUNCS:Argument Parsing Functions:GEN_BUSE_LogQuiet
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_BUSE_LogQuiet

   PUBLISH NAME:	GEN_BUSE_LogQuiet

	ENTRY CLASS	:	Argument Parsing Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_BUSE_LogQuiet(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count, char ***usage_list,
	char *error_text)
#else
int GEN_BUSE_LogQuiet(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char          **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int                return_code;
	static const char *arg_name         = "-LOG[GING]_QUIET=<boolean>";
	static char       *arg_usage_list[] = {
	"		Specifies whether the program is to emit log and status errors to \
'stderr'.",
	"\n",
	NULL
};

	if ((return_code = GEN_BUSE_BasicConstruct(base_arg_ptr, arg_name,
		optional_flag, arg_usage_list, extra_usage_list, usage_count,
		usage_list, error_text)) == GENFUNCS_SUCCESS)
		return_code = GEN_BUSE_AppendBooleanText(usage_count, usage_list, -1,
			error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_BUSE_CheckOnly

   SYNOPSIS    :	return_code = GEN_BUSE_CheckOnly(base_arg_ptr, optional_flag,
							extra_usage_list, usage_count, usage_list, error_text);

						int             return_code;

						const char     *base_arg_ptr;

						int             optional_flag;

						char          **extra_usage_list;

						unsigned int   *usage_count;

						char         ***usage_list;

						char           *error_text;

   DESCRIPTION :	Appends the usage text for the ''-CHECK_ONLY=''
						parameter to an array of pointers to ''char''.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``base_arg_ptr`` points to a string which may be used
						to preface the parameter name. ``base_arg_ptr`` may be
						''NULL''.

						(.) ``optional_flag`` indicates whether the parameter is
						optional. It may take either of the values ''GENFUNCS_TRUE''
						or ''GENFUNCS_FALSE''.

						(-) If ``optional_flag`` is equal to ''GENFUNCS_TRUE'', this
						function will surround the parameter name with square
						brackets (''['' and '']'') to indicate optionality.

						(.) ``extra_usage_list`` is an array of pointers to ''char''
						which may be used add parameter usage text for the
						parameter.

						(-) If the application programmer does not desire added
						parameter text, ``extra_usage_text`` may be ''NULL''.

						(-) If added parameter text is desired, the last element
						in the array ``extra_usage_list`` must be a ''NULL''
						pointer. This is to indicate to the function that no
						further array elements are to be added.

						(.) ``usage_count`` is the number of elements in the
						array ``usage_list``.

						(.) ``usage_list`` is a pointer to an array of pointers
						to ''char'' into which this function will place lines
						added to the usage list.

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

   SEE ALSO    :	GEN_BUSE_BasicConstruct
						GEN_BARG_CheckOnly

   EXAMPLES    :	If this function is invoked with ``base_arg_ptr`` equal to
						''NULL'', ``optional_flag`` equal to ''GENFUNCS_FALSE'' and
						``extra_usage_list`` equal to ''NULL'', the following lines
						will be added to the array ``usage_list``:

{|@|}-CHECK[ING][_ONLY]=<boolean>
   Specifies whether the program is to initialize itself and exit. This
   option permits system administrators to check the validity of the
   command-line parameters used by the program.
   
   The <boolean> component of this parameter has the following syntax
   for the value 'TRUE':
 
      { TRUE | ON | YES | T | Y | 1 }
 
   and the following syntax for the value 'FALSE':
 
      { FALSE | OFF | NO | F | N | 0 }

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1995 - 2015 Michael L. Brock

   OUTPUT INDEX:	GEN_BUSE_CheckOnly
						Argument Parsing Functions:GEN_BUSE_CheckOnly
						GENFUNCS:Functions:GEN_BUSE_CheckOnly
						GENFUNCS:Argument Parsing Functions:GEN_BUSE_CheckOnly
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_BUSE_CheckOnly

   PUBLISH NAME:	GEN_BUSE_CheckOnly

	ENTRY CLASS	:	Argument Parsing Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_BUSE_CheckOnly(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count, char ***usage_list,
	char *error_text)
#else
int GEN_BUSE_CheckOnly(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char          **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int                return_code;
	static const char *arg_name         = "-CHECK[ING][_ONLY]=<boolean>";
	static char       *arg_usage_list[] = {
	"		Specifies whether the program is to initialize itself and exit. \
This option permits system administrators to check the validity of the \
command-line parameters used by the program.",
	"\n",
	NULL
};

	if ((return_code = GEN_BUSE_BasicConstruct(base_arg_ptr, arg_name,
		optional_flag, arg_usage_list, extra_usage_list, usage_count,
		usage_list, error_text)) == GENFUNCS_SUCCESS)
		return_code = GEN_BUSE_AppendBooleanText(usage_count, usage_list, -1,
			error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_BUSE_Version

   SYNOPSIS    :	return_code = GEN_BUSE_Version(base_arg_ptr, optional_flag,
							extra_usage_list, usage_count, usage_list, error_text);

						int             return_code;

						const char     *base_arg_ptr;

						int             optional_flag;

						char          **extra_usage_list;

						unsigned int   *usage_count;

						char         ***usage_list;

						char           *error_text;

   DESCRIPTION :	Appends the usage text for the ''-VERSION='' parameter to
						an array of pointers to ''char''.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``base_arg_ptr`` points to a string which may be used
						to preface the parameter name. ``base_arg_ptr`` may be
						''NULL''.

						(.) ``optional_flag`` indicates whether the parameter is
						optional. It may take either of the values ''GENFUNCS_TRUE''
						or ''GENFUNCS_FALSE''.

						(-) If ``optional_flag`` is equal to ''GENFUNCS_TRUE'', this
						function will surround the parameter name with square
						brackets (''['' and '']'') to indicate optionality.

						(.) ``extra_usage_list`` is an array of pointers to ''char''
						which may be used add parameter usage text for the
						parameter.

						(-) If the application programmer does not desire added
						parameter text, ``extra_usage_text`` may be ''NULL''.

						(-) If added parameter text is desired, the last element
						in the array ``extra_usage_list`` must be a ''NULL''
						pointer. This is to indicate to the function that no
						further array elements are to be added.

						(.) ``usage_count`` is the number of elements in the
						array ``usage_list``.

						(.) ``usage_list`` is a pointer to an array of pointers
						to ''char'' into which this function will place lines
						added to the usage list.

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

   SEE ALSO    :	GEN_BUSE_BasicConstruct

   EXAMPLES    :	If this function is invoked with ``base_arg_ptr`` equal to
						''NULL'', ``optional_flag`` equal to ''GENFUNCS_FALSE'' and
						``extra_usage_list`` equal to ''NULL'', the following lines
						will be added to the array ``usage_list``:

{|@|}-V[ER[SION][S]]]
   Displays the version of this program.

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1995 - 2015 Michael L. Brock

   OUTPUT INDEX:	GEN_BUSE_Version
						Argument Parsing Functions:GEN_BUSE_Version
						GENFUNCS:Functions:GEN_BUSE_Version
						GENFUNCS:Argument Parsing Functions:GEN_BUSE_Version
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_BUSE_Version
						-VERSION=
						-VERSION= Parameter
						-VERSION= parameter

   PUBLISH NAME:	GEN_BUSE_Version

	ENTRY CLASS	:	Argument Parsing Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_BUSE_Version(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count, char ***usage_list,
	char *error_text)
#else
int GEN_BUSE_Version(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char          **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	static const char *arg_name         = "-V[ER[SION][S]]";
	static char       *arg_usage_list[] = {
	"		Displays the version of this program.",
	"\n",
	NULL
};

	return(GEN_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_BUSE_DebugLevel

   SYNOPSIS    :	return_code = GEN_BUSE_DebugLevel(base_arg_ptr,
							optional_flag, extra_usage_list, usage_count, usage_list,
							error_text);

						int             return_code;

						const char     *base_arg_ptr;

						int             optional_flag;

						char          **extra_usage_list;

						unsigned int   *usage_count;

						char         ***usage_list;

						char           *error_text;

   DESCRIPTION :	Appends the usage text for the ''-DEBUGGING_LEVEL=''
						parameter to an array of pointers to ''char''.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``base_arg_ptr`` points to a string which may be used
						to preface the parameter name. ``base_arg_ptr`` may be
						''NULL''.

						(.) ``optional_flag`` indicates whether the parameter is
						optional. It may take either of the values ''GENFUNCS_TRUE''
						or ''GENFUNCS_FALSE''.

						(-) If ``optional_flag`` is equal to ''GENFUNCS_TRUE'', this
						function will surround the parameter name with square
						brackets (''['' and '']'') to indicate optionality.

						(.) ``extra_usage_list`` is an array of pointers to ''char''
						which may be used add parameter usage text for the
						parameter.

						(-) If the application programmer does not desire added
						parameter text, ``extra_usage_text`` may be ''NULL''.

						(-) If added parameter text is desired, the last element
						in the array ``extra_usage_list`` must be a ''NULL''
						pointer. This is to indicate to the function that no
						further array elements are to be added.

						(.) ``usage_count`` is the number of elements in the
						array ``usage_list``.

						(.) ``usage_list`` is a pointer to an array of pointers
						to ''char'' into which this function will place lines
						added to the usage list.

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

   SEE ALSO    :	GEN_BARG_DebugLevel
						GEN_BUSE_BasicConstruct

   EXAMPLES    :	If this function is invoked with ``base_arg_ptr`` equal to
						''NULL'', ``optional_flag`` equal to ''GENFUNCS_FALSE'' and
						``extra_usage_list`` equal to ''NULL'', the following lines
						will be added to the array ``usage_list``:

{|@|}-DEBUG[GING][_LEVEL]=<debug-level>
   Specifies the debugging detail to be emitted by the program.
 
   The <debug-level> component of the parameter has the following
   syntax:
 
      o NONE     --- specifies that no special debugging logging is to
      be performed.
 
      o BASIC    --- specifies that basic debugging logging is to be
      performed.
 
      o COMPLETE --- specifies that the maximum debugging logging is to
      be performed.

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1995 - 2015 Michael L. Brock

   OUTPUT INDEX:	GEN_BUSE_DebugLevel
						Argument Parsing Functions:GEN_BUSE_DebugLevel
						GENFUNCS:Functions:GEN_BUSE_DebugLevel
						GENFUNCS:Argument Parsing Functions:GEN_BUSE_DebugLevel
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_BUSE_DebugLevel

   PUBLISH NAME:	GEN_BUSE_DebugLevel

	ENTRY CLASS	:	Argument Parsing Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_BUSE_DebugLevel(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count, char ***usage_list,
	char *error_text)
#else
int GEN_BUSE_DebugLevel(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char          **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	static const char *arg_name         = "-DEBUG[GING][_LEVEL]=<debug-level>";
	static char       *arg_usage_list[] = {
	"		Specifies the debugging detail to be emitted by the program.",
	"\n",
	"		The <debug-level> component of the parameter has the following \
syntax:",
	"\n",
	"			o NONE     --- specifies that no special debugging logging is to \
be performed.",
	"\n",
	"			o BASIC    --- specifies that basic debugging logging is to be \
performed.",
	"\n",
	"			o COMPLETE --- specifies that the maximum debugging logging is \
to be performed.",
	"\n",
	NULL
};

	return(GEN_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_BUSE_DBDebugFlag

   SYNOPSIS    :	return_code = GEN_BUSE_DBDebugFlag(base_arg_ptr,
							optional_flag, extra_usage_list, usage_count, usage_list,
							error_text);

						int             return_code;

						const char     *base_arg_ptr;

						int             optional_flag;

						char          **extra_usage_list;

						unsigned int   *usage_count;

						char         ***usage_list;

						char           *error_text;

   DESCRIPTION :	Appends the usage text for the ''-DATA_BASE_DEBUGGING=''
						parameter to an array of pointers to ''char''.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``base_arg_ptr`` points to a string which may be used
						to preface the parameter name. ``base_arg_ptr`` may be
						''NULL''.

						(.) ``optional_flag`` indicates whether the parameter is
						optional. It may take either of the values ''GENFUNCS_TRUE''
						or ''GENFUNCS_FALSE''.

						(-) If ``optional_flag`` is equal to ''GENFUNCS_TRUE'', this
						function will surround the parameter name with square
						brackets (''['' and '']'') to indicate optionality.

						(.) ``extra_usage_list`` is an array of pointers to ''char''
						which may be used add parameter usage text for the
						parameter.

						(-) If the application programmer does not desire added
						parameter text, ``extra_usage_text`` may be ''NULL''.

						(-) If added parameter text is desired, the last element
						in the array ``extra_usage_list`` must be a ''NULL''
						pointer. This is to indicate to the function that no
						further array elements are to be added.

						(.) ``usage_count`` is the number of elements in the
						array ``usage_list``.

						(.) ``usage_list`` is a pointer to an array of pointers
						to ''char'' into which this function will place lines
						added to the usage list.

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

   SEE ALSO    :	GEN_BARG_DBDebugFlag
						GEN_BUSE_SQLDebugFlag
						GEN_BUSE_BasicConstruct

   EXAMPLES    :	If this function is invoked with ``base_arg_ptr`` equal to
						''NULL'', ``optional_flag`` equal to ''GENFUNCS_FALSE'' and
						``extra_usage_list`` equal to ''NULL'', the following lines
						will be added to the array ``usage_list``:

{|@|}-{DB|DATA[_]BASE}_DEBUG[GING]=<boolean>
   Specifies whether the program is to log all messages and errors
   returned from the database server in the log file.
 
   The <boolean> component of this parameter has the following syntax
   for the value 'TRUE':
 
      { TRUE | ON | YES | T | Y | 1 }
 
   and the following syntax for the value 'FALSE':
 
      { FALSE | OFF | NO | F | N | 0 }

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1995 - 2015 Michael L. Brock

   OUTPUT INDEX:	GEN_BUSE_DBDebugFlag
						Argument Parsing Functions:GEN_BUSE_DBDebugFlag
						GENFUNCS:Functions:GEN_BUSE_DBDebugFlag
						GENFUNCS:Argument Parsing Functions:GEN_BUSE_DBDebugFlag
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_BUSE_DBDebugFlag

   PUBLISH NAME:	GEN_BUSE_DBDebugFlag

	ENTRY CLASS	:	Argument Parsing Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_BUSE_DBDebugFlag(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count, char ***usage_list,
	char *error_text)
#else
int GEN_BUSE_DBDebugFlag(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char          **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int                return_code;
	static const char *arg_name         =
		"-{DB|DATA[_]BASE}_DEBUG[GING]=<boolean>";
	static char       *arg_usage_list[] = {
	"		Specifies whether the program is to log all messages and errors \
returned from the database server in the log file.",
	"\n",
	NULL
};

	if ((return_code = GEN_BUSE_BasicConstruct(base_arg_ptr, arg_name,
		optional_flag, arg_usage_list, extra_usage_list, usage_count,
		usage_list, error_text)) == GENFUNCS_SUCCESS)
		return_code = GEN_BUSE_AppendBooleanText(usage_count, usage_list, -1,
			error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_BUSE_SQLDebugFlag

   SYNOPSIS    :	return_code = GEN_BUSE_SQLDebugFlag(base_arg_ptr,
							optional_flag, extra_usage_list, usage_count, usage_list,
							error_text);

						int             return_code;

						const char     *base_arg_ptr;

						int             optional_flag;

						char          **extra_usage_list;

						unsigned int   *usage_count;

						char         ***usage_list;

						char           *error_text;

   DESCRIPTION :	Appends the usage text for the ''-SQL_DEBUGGING='' parameter
						to an array of pointers to ''char''.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``base_arg_ptr`` points to a string which may be used
						to preface the parameter name. ``base_arg_ptr`` may be
						''NULL''.

						(.) ``optional_flag`` indicates whether the parameter is
						optional. It may take either of the values ''GENFUNCS_TRUE''
						or ''GENFUNCS_FALSE''.

						(-) If ``optional_flag`` is equal to ''GENFUNCS_TRUE'', this
						function will surround the parameter name with square
						brackets (''['' and '']'') to indicate optionality.

						(.) ``extra_usage_list`` is an array of pointers to ''char''
						which may be used add parameter usage text for the
						parameter.

						(-) If the application programmer does not desire added
						parameter text, ``extra_usage_text`` may be ''NULL''.

						(-) If added parameter text is desired, the last element
						in the array ``extra_usage_list`` must be a ''NULL''
						pointer. This is to indicate to the function that no
						further array elements are to be added.

						(.) ``usage_count`` is the number of elements in the
						array ``usage_list``.

						(.) ``usage_list`` is a pointer to an array of pointers
						to ''char'' into which this function will place lines
						added to the usage list.

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

   SEE ALSO    :	GEN_BARG_SQLDebugFlag
						GEN_BUSE_DBDebugFlag
						GEN_BUSE_BasicConstruct

   EXAMPLES    :	If this function is invoked with ``base_arg_ptr`` equal to
						''NULL'', ``optional_flag`` equal to ''GENFUNCS_FALSE'' and
						``extra_usage_list`` equal to ''NULL'', the following lines
						will be added to the array ``usage_list``:

{|@|}-SQL_DEBUG[GING]=<boolean>
   Specifies whether the program is to log all SQL statements sent to
   the database server in the log file.
 
   The <boolean> component of this parameter has the following syntax
   for the value 'TRUE':
 
      { TRUE | ON | YES | T | Y | 1 }
 
   and the following syntax for the value 'FALSE':
 
      { FALSE | OFF | NO | F | N | 0 }

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1995 - 2015 Michael L. Brock

   OUTPUT INDEX:	GEN_BUSE_SQLDebugFlag
						Argument Parsing Functions:GEN_BUSE_SQLDebugFlag
						GENFUNCS:Functions:GEN_BUSE_SQLDebugFlag
						GENFUNCS:Argument Parsing Functions:GEN_BUSE_SQLDebugFlag
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_BUSE_SQLDebugFlag

   PUBLISH NAME:	GEN_BUSE_SQLDebugFlag

	ENTRY CLASS	:	Argument Parsing Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_BUSE_SQLDebugFlag(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count, char ***usage_list,
	char *error_text)
#else
int GEN_BUSE_SQLDebugFlag(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char          **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int                return_code;
	static const char *arg_name         = "-SQL_DEBUG[GING]=<boolean>";
	static char       *arg_usage_list[] = {
	"		Specifies whether the program is to log all SQL statements sent to \
the database server in the log file.",
	"\n",
	NULL
};

	if ((return_code = GEN_BUSE_BasicConstruct(base_arg_ptr, arg_name,
		optional_flag, arg_usage_list, extra_usage_list, usage_count,
		usage_list, error_text)) == GENFUNCS_SUCCESS)
		return_code = GEN_BUSE_AppendBooleanText(usage_count, usage_list, -1,
			error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_BUSE_AppendBooleanText

   SYNOPSIS    :	return_code = GEN_BUSE_AppendBooleanText(usage_count,
							usage_list, default_value, error_text);

						int             return_code;

						unsigned int   *usage_count;

						char         ***usage_list;

						int             default_value;

						char           *error_text;

   DESCRIPTION :	Appends the usage text which describes the syntax of
						``boolean`` parameters an array of pointers to ''char''.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``usage_count`` is the number of elements in the
						array ``usage_list``.

						(.) ``usage_list`` is a pointer to an array of pointers
						to ''char'' into which this function will place lines
						added to the usage list.

						(.) ``boolean_value`` indicates the default value of the
						parameter:

						(..) If ``boolean_value`` is ''0'', the default value will
						be described by this function as ''TRUE''.

						(..) If ``boolean_value`` is ''1'', the default value will
						be described by this function as ''FALSE''.

						(..) If ``boolean_value`` is any value other than ''0'' or
						''1'', this function wil not include the portion of the
						usage text which describes the default value.

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

   EXAMPLES    :	This function adds the following text to ``usage_list`` if
						the ``boolean_value`` parameter is ''0'':

{|@|}   The <boolean> component of this parameter has the following syntax
   for the value 'TRUE':
 
      { TRUE | ON | YES | T | Y | 1 }
 
   and the following syntax for the value 'FALSE':
 
      { FALSE | OFF | NO | F | N | 0 }
 
   The default for this parameter is 'FALSE'.

						This function adds the following text to ``usage_list`` if
						the ``boolean_value`` parameter is ''1'':

{|@|}   The <boolean> component of this parameter has the following syntax
   for the value 'TRUE':
 
      { TRUE | ON | YES | T | Y | 1 }
 
   and the following syntax for the value 'FALSE':
 
      { FALSE | OFF | NO | F | N | 0 }
 
   The default for this parameter is 'TRUE'.

						This function adds the following text to ``usage_list`` if
						the ``boolean_value`` parameter is ''-1'':

{|@|}   The <boolean> component of this parameter has the following syntax
   for the value 'TRUE':
 
      { TRUE | ON | YES | T | Y | 1 }
 
   and the following syntax for the value 'FALSE':
 
      { FALSE | OFF | NO | F | N | 0 }

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1995 - 2015 Michael L. Brock

   OUTPUT INDEX:	GEN_BUSE_AppendBooleanText
						Argument Parsing Functions:GEN_BUSE_AppendBooleanText
						GENFUNCS:Functions:GEN_BUSE_AppendBooleanText
						GENFUNCS:Argument Parsing Functions:GEN_BUSE_AppendBooleanText
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_BUSE_AppendBooleanText

   PUBLISH NAME:	GEN_BUSE_AppendBooleanText

	ENTRY CLASS	:	Argument Parsing Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_BUSE_AppendBooleanText(unsigned int *usage_count, char ***usage_list,
	int default_value, char *error_text)
#else
int GEN_BUSE_AppendBooleanText(usage_count, usage_list, default_value,
	error_text)
unsigned int   *usage_count;
char         ***usage_list;
int             default_value;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code = GENFUNCS_SUCCESS;
	char default_buffer[128];

	if (strlv_append(usage_count, usage_list,
		"\t\tThe <boolean> component of this parameter has the following \
syntax for the value 'TRUE':", "\n", "\t\t\t{ TRUE | ON | YES | T | Y | 1 }",
		"\n", "\t\tand the following syntax for the value 'FALSE':",
		"\n", "\t\t\t{ FALSE | OFF | NO | F | N | 0 }", "\n",
		((!default_value) || (default_value == 1)) ?
		strcat(strcpy(default_buffer,
		"\t\tThe default for this parameter is '"), (default_value) ? "TRUE'." :
		"FALSE'.") : NULL,
		((!default_value) || (default_value == 1)) ? "\n" : NULL,
		NULL) != STRFUNCS_SUCCESS) {
		strcpy(error_text, "Unable to allocate memory for the usage text.");
		return_code = GENFUNCS_MEMORY_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_BUSE_AppendParamText

   SYNOPSIS    :	return_code = GEN_BUSE_AppendParamText(usage_count,
							usage_list, error_text);

						int             return_code;

						unsigned int   *usage_count;

						char         ***usage_list;

						char           *error_text;

   DESCRIPTION :	Appends the usage text for parameter include files to an
						array of pointers to ''char''.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``usage_count`` is the number of elements in the
						array ``usage_list``.

						(.) ``usage_list`` is a pointer to an array of pointers
						to ''char'' into which this function will place lines
						added to the usage list.

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

   SEE ALSO    :	GEN_BUSE_BasicConstruct

   EXAMPLES    :	This function adds the following text to ``usage_list``:

{|@|}[@<parameter-include-file-name>]
   Specifies the name of a parameter include file from which parameters
   to this program are to be loaded. Parameter include files permit
   arguments to be stored in a text file for parsing by the program.
 
   Inclusion of a parameter include file is indicated by an argument of
   the form:
 
      @<parameter-include-file-name>
 
   However, note the following:
 
      o An argument which consists of a single at-sign ('@') is not
      considered to be a parameter include file specification. Instead,
      it will be parsed as a command-line parameter consisting of the
      single character '@'.
 
      o An argument which begins with two at-signs ('@@') is not
      considered to be a parameter include file specification, but an
      escaped parameter. It will be parsed as a command-line parameter
      which begins with the second '@'.
 
   When a parameter include file is encountered on the command line,
   the program will attempt to open it for reading. It is an error if
   the file so specified does not exist or can not be read.
 
   Each line of the parameter include file is parsed for its parameters
   just as if those parameters were entered on the command line except
   for the following rules:
 
      o A line in which the first non-whitespace character is a number-
      sign ('#') is considered to be the start of a comment and is
      ignored.
 
      o Blank lines (that is, lines which are empty or which consist
      wholly of whitespace) are ignored.
 
   Parameter include files may themselves contain parameter include
   file specifications. An include file may be included more than once,
   so long as any nested chain of includes from that file does not
   result in an attempt to include itself recursively.

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1995 - 2015 Michael L. Brock

   OUTPUT INDEX:	GEN_BUSE_AppendParamText
						Argument Parsing Functions:GEN_BUSE_AppendParamText
						GENFUNCS:Functions:GEN_BUSE_AppendParamText
						GENFUNCS:Argument Parsing Functions:GEN_BUSE_AppendParamText
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_BUSE_AppendParamText

   PUBLISH NAME:	GEN_BUSE_AppendParamText

	ENTRY CLASS	:	Argument Parsing Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_BUSE_AppendParamText(unsigned int *usage_count, char ***usage_list,
	char *error_text)
#else
int GEN_BUSE_AppendParamText(usage_count, usage_list, error_text)
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	static const char *arg_name         = "@<parameter-include-file-name>";
	static char *tmp_ptr                = NULL;
	static char       *arg_usage_list[] = {
	"		Specifies the name of a parameter include file from which \
parameters to this program are to be loaded. Parameter include files permit \
arguments to be stored in a text file for parsing by the program.",
	"\n",
	"		Inclusion of a parameter include file is indicated by an argument \
of the form:",
	"\n",
	"			@<parameter-include-file-name>",
	"\n",
	"		However, note the following:",
	"\n",
	"			o An argument which consists of a single at-sign ('@') is not \
considered to be a parameter include file specification. Instead, it will \
be parsed as a command-line parameter consisting of the single character '@'.",
	"\n",
	"			o An argument which begins with two at-signs ('@@') is not \
considered to be a parameter include file specification, but an escaped \
parameter. It will be parsed as a command-line parameter which begins with \
the second '@'.",
	"\n",
	"		When a parameter include file is encountered on the command line, \
the program will attempt to open it for reading. It is an error if the file \
so specified does not exist or can not be read.",
	"\n",
	"		Each line of the parameter include file is parsed for its \
parameters just as if those parameters were entered on the command line \
except for the following rules:",
	"\n",
	"			o A line in which the first non-whitespace character is a \
number-sign ('#') is considered to be the start of a comment and is ignored.",
	"\n",
	"			o Blank lines (that is, lines which are empty or which consist \
wholly of whitespace) are ignored.",
	"\n",
	"		Parameter include files may themselves contain parameter include \
file specifications. An include file may be included more than once, so long \
as any nested chain of includes from that file does not result in an attempt \
to include itself recursively.",
	"\n",
	NULL
};

	return(GEN_BUSE_BasicConstruct(NULL, arg_name, GENFUNCS_TRUE,
		arg_usage_list, &tmp_ptr, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_BUSE_AppendLineList

   SYNOPSIS    :	return_code = GEN_BUSE_AppendLineList(in_line_list,
							usage_count, usage_list, error_text);

						int             return_code;

						char          **in_line_list;

						unsigned int   *usage_count;

						char         ***usage_list;

						char           *error_text;

   DESCRIPTION :	Appends the array of pointers to ''char'' represented by
						``in_line_list`` parameter to the array of pointers to
						''char'' represented by the ``usage_list`` parameter.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_line_list`` is an array of pointers to ''char''
						which contains the strings which this function is to append
						to the array ``usage_list``.

						(.) ``usage_count`` is the number of elements in the
						array ``usage_list``.

						(.) ``usage_list`` is a pointer to an array of pointers
						to ''char'' into which this function will place the line
						added to the usage list.

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

   SEE ALSO    :	GEN_BUSE_AppendLine

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1995 - 2015 Michael L. Brock

   OUTPUT INDEX:	GEN_BUSE_AppendLineList
						Argument Parsing Functions:GEN_BUSE_AppendLineList
						GENFUNCS:Functions:GEN_BUSE_AppendLineList
						GENFUNCS:Argument Parsing Functions:GEN_BUSE_AppendLineList
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_BUSE_AppendLineList

   PUBLISH NAME:	GEN_BUSE_AppendLineList

	ENTRY CLASS	:	Argument Parsing Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_BUSE_AppendLineList(char **in_line_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
int GEN_BUSE_AppendLineList(in_line_list, usage_count, usage_list, error_text)
char          **in_line_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = GENFUNCS_SUCCESS;
	unsigned int old_usage_count;

	old_usage_count = *usage_count;

	while (*in_line_list != NULL) {
		if (strl_append(usage_count, usage_list, *in_line_list) !=
			STRFUNCS_SUCCESS) {
			strl_remove(usage_count, usage_list, old_usage_count, *usage_count);
			strcpy(error_text, "Unable to allocate memory for the usage text.");
			return_code = GENFUNCS_MEMORY_FAILURE;
			break;
		}
		in_line_list++;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_BUSE_AppendLine

   SYNOPSIS    :	return_code = GEN_BUSE_AppendLine(in_line, usage_count,
							usage_list, error_text);

						int             return_code;

						const char     *in_line;

						unsigned int   *usage_count;

						char         ***usage_list;

						char           *error_text;

   DESCRIPTION :	Appends a single line to an array of pointers to ''char''.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_line`` is the string to be appended.

						(.) ``usage_count`` is the number of elements in the
						array ``usage_list``.

						(.) ``usage_list`` is a pointer to an array of pointers
						to ''char'' into which this function will place the line
						added to the usage list.

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

   SEE ALSO    :	GEN_BUSE_AppendLineList
						GEN_BUSE_AppendNL
						GEN_BUSE_AppendNULL

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1995 - 2015 Michael L. Brock

   OUTPUT INDEX:	GEN_BUSE_AppendLine
						Argument Parsing Functions:GEN_BUSE_AppendLine
						GENFUNCS:Functions:GEN_BUSE_AppendLine
						GENFUNCS:Argument Parsing Functions:GEN_BUSE_AppendLine
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_BUSE_AppendLine

   PUBLISH NAME:	GEN_BUSE_AppendLine

	ENTRY CLASS	:	Argument Parsing Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_BUSE_AppendLine(const char *in_line, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
int GEN_BUSE_AppendLine(in_line, usage_count, usage_list, error_text)
const char     *in_line;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = GENFUNCS_SUCCESS;

	if (strl_append(usage_count, usage_list, in_line) != STRFUNCS_SUCCESS) {
		strcpy(error_text, "Unable to allocate memory for the usage text.");
		return_code = GENFUNCS_MEMORY_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_BUSE_AppendNL

   SYNOPSIS    :	return_code = GEN_BUSE_AppendNL(usage_count, usage_list,
							error_text);

						int             return_code;

						unsigned int   *usage_count;

						char         ***usage_list;

						char           *error_text;

   DESCRIPTION :	Appends a string containing a ``new-line`` character
						(''\n'') to an array of pointers to ''char''.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``usage_count`` is the number of elements in the
						array ``usage_list``.

						(.) ``usage_list`` is a pointer to an array of pointers
						to ''char'' into which this function will place the line
						added to the usage list.

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

   SEE ALSO    :	GEN_BUSE_AppendLine
						GEN_BUSE_AppendNULL

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1995 - 2015 Michael L. Brock

   OUTPUT INDEX:	GEN_BUSE_AppendNL
						Argument Parsing Functions:GEN_BUSE_AppendNL
						GENFUNCS:Functions:GEN_BUSE_AppendNL
						GENFUNCS:Argument Parsing Functions:GEN_BUSE_AppendNL
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_BUSE_AppendNL

   PUBLISH NAME:	GEN_BUSE_AppendNL

	ENTRY CLASS	:	Argument Parsing Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_BUSE_AppendNL(unsigned int *usage_count, char ***usage_list,
	char *error_text)
#else
int GEN_BUSE_AppendNL(usage_count, usage_list, error_text)
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = GENFUNCS_SUCCESS;

	if (strl_append(usage_count, usage_list, "\n") != STRFUNCS_SUCCESS) {
		strcpy(error_text, "Unable to allocate memory for the usage text.");
		return_code = GENFUNCS_MEMORY_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_BUSE_AppendNULL

   SYNOPSIS    :	return_code = GEN_BUSE_AppendNULL(usage_count, usage_list,
							error_text);

						int             return_code;

						unsigned int   *usage_count;

						char         ***usage_list;

						char           *error_text;

   DESCRIPTION :	Appends an array element containing a pointer to ''NULL''
						to an array of pointers to ''char''.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``usage_count`` is the number of elements in the
						array ``usage_list``.

						(.) ``usage_list`` is a pointer to an array of pointers
						to ''char'' into which this function will place the line
						added to the usage list.

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

   SEE ALSO    :	GEN_BUSE_AppendLine
						GEN_BUSE_AppendNL

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1995 - 2015 Michael L. Brock

   OUTPUT INDEX:	GEN_BUSE_AppendNULL
						Argument Parsing Functions:GEN_BUSE_AppendNULL
						GENFUNCS:Functions:GEN_BUSE_AppendNULL
						GENFUNCS:Argument Parsing Functions:GEN_BUSE_AppendNULL
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_BUSE_AppendNULL

   PUBLISH NAME:	GEN_BUSE_AppendNULL

	ENTRY CLASS	:	Argument Parsing Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_BUSE_AppendNULL(unsigned int *usage_count, char ***usage_list,
	char *error_text)
#else
int GEN_BUSE_AppendNULL(usage_count, usage_list, error_text)
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = GENFUNCS_SUCCESS;

	if (strl_append(usage_count, usage_list, "") != STRFUNCS_SUCCESS) {
		strcpy(error_text, "Unable to allocate memory for the usage text.");
		return_code = GENFUNCS_MEMORY_FAILURE;
	}
	else {
		free((*usage_list)[*usage_count - 1]);
		(*usage_list)[*usage_count - 1] = NULL;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_BUSE_BasicConstruct

   SYNOPSIS    :	return_code = GEN_BUSE_BasicConstruct(base_arg_ptr, arg_ptr,
							optional_flag, arg_usage_list, extra_usage_list,
							usage_count, usage_list, error_text);

						int             return_code;

						const char     *base_arg_ptr;

						const char     *arg_ptr;

						int             optional_flag;

						char          **arg_usage_list;

						char          **extra_usage_list;

						unsigned int   *usage_count;

						char         ***usage_list;

						char           *error_text;

   DESCRIPTION :	Low-level function for constructing parameter usage text.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``base_arg_ptr`` points to a string which may be used
						to preface the parameter name. ``base_arg_ptr`` may be
						''NULL''.

						(.) ``optional_flag`` indicates whether the parameter is
						optional. It may take either of the values ''GENFUNCS_TRUE''
						or ''GENFUNCS_FALSE''.

						(-) If ``optional_flag`` is equal to ''GENFUNCS_TRUE'', this
						function will surround the parameter name with square
						brackets (''['' and '']'') to indicate optionality.

						(.) ``arg_usage_list`` is an array of pointers to ''char''
						which contains the strings which constitute the basic
						usage text.

						(.) ``extra_usage_list`` is an array of pointers to ''char''
						which may be used add parameter usage text for the
						parameter.

						(-) If the application programmer does not desire added
						parameter text, ``extra_usage_text`` may be ''NULL''.

						(-) If added parameter text is desired, the last element
						in the array ``extra_usage_list`` must be a ''NULL''
						pointer. This is to indicate to the function that no
						further array elements are to be added.

						(.) ``usage_count`` is the number of elements in the
						array ``usage_list``.

						(.) ``usage_list`` is a pointer to an array of pointers
						to ''char'' into which this function will place lines
						added to the usage list.

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

   COPYRIGHT   :	Copyright 1995 - 2015 Michael L. Brock

   OUTPUT INDEX:	GEN_BUSE_BasicConstruct
						Argument Parsing Functions:GEN_BUSE_BasicConstruct
						GENFUNCS:Functions:GEN_BUSE_BasicConstruct
						GENFUNCS:Argument Parsing Functions:GEN_BUSE_BasicConstruct
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_BUSE_BasicConstruct

   PUBLISH NAME:	GEN_BUSE_BasicConstruct

	ENTRY CLASS	:	Argument Parsing Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_BUSE_BasicConstruct(const char *base_arg_ptr, const char *arg_ptr,
	int optional_flag, char **arg_usage_list, char **extra_usage_list,
	unsigned int *usage_count, char ***usage_list, char *error_text)
#else
int GEN_BUSE_BasicConstruct(base_arg_ptr, arg_ptr, optional_flag,
	arg_usage_list, extra_usage_list, usage_count, usage_list, error_text)
const char     *base_arg_ptr;
const char     *arg_ptr;
int             optional_flag;
char          **arg_usage_list;
char          **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code  = GENFUNCS_SUCCESS;
	char         *tmp_arg_data;
	unsigned int  old_usage_count;

	base_arg_ptr = (base_arg_ptr == NULL) ? "" : base_arg_ptr;

	if ((tmp_arg_data = ((char *) malloc((1 + 1 + strlen(base_arg_ptr) +
		strlen(arg_ptr) + 1 + 1) * sizeof(char)))) == NULL)
		return_code = GENFUNCS_MEMORY_FAILURE;
	else {
		old_usage_count = *usage_count;
		strcat(strcat(strcat(strcpy(tmp_arg_data,
			(optional_flag == GENFUNCS_TRUE) ? "\t[" : "\t"), base_arg_ptr),
			arg_ptr), (optional_flag == GENFUNCS_TRUE) ? "]" : "");
		if (strl_append(usage_count, usage_list, tmp_arg_data) !=
			STRFUNCS_SUCCESS)
			return_code = GENFUNCS_MEMORY_FAILURE;
		else {
			while (*arg_usage_list != NULL) {
				if (strl_append(usage_count, usage_list, *arg_usage_list) !=
					STRFUNCS_SUCCESS) {
					return_code = GENFUNCS_MEMORY_FAILURE;
					break;
				}
				arg_usage_list++;
			}
			if ((return_code == GENFUNCS_SUCCESS) && (extra_usage_list != NULL)) {
				while (*extra_usage_list != NULL) {
					if (strl_append(usage_count, usage_list, *extra_usage_list) !=
						STRFUNCS_SUCCESS) {
						return_code = GENFUNCS_MEMORY_FAILURE;
						break;
					}
					extra_usage_list++;
				}
			}
		}
		if (return_code != GENFUNCS_SUCCESS)
			strl_remove(usage_count, usage_list, old_usage_count, *usage_count);
		free(tmp_arg_data);
	}

	if (return_code != GENFUNCS_SUCCESS)
		strcpy(error_text, "Unable to allocate memory for the usage text.");

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_BUSE_CreateUsageList

   SYNOPSIS    :	return_code = GEN_BUSE_CreateUsageList(param_count,
							param_list, usage_count, usage_list, error_text);

						int                      return_code;

						unsigned int             param_count;

						const GEN_USAGE_PARAM   *param_list;

						unsigned int            *usage_count;

						char                  ***usage_list;

						char                    *error_text;

   DESCRIPTION :	Low-level function for constructing parameter usage text
						from a list of ''GEN_USAGE_PARAM'' parameter descriptors.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``param_count`` is the number of elements in the array
						``param_list``.

						(.) ``param_list`` is the array of ''GEN_USAGE_PARAM''
						structures from which the usage list is to be constructed
						by this function.

						(.) ``usage_count`` is a pointer to an ''unsigned int''
						which contains the number of elements in the array
						``usage_list``.

						(.) ``usage_list`` is a pointer to an array of pointers
						to ''char'' into which this function will place lines
						added to the usage list.

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

   COPYRIGHT   :	Copyright 1995 - 2015 Michael L. Brock

   OUTPUT INDEX:	GEN_BUSE_CreateUsageList
						Argument Parsing Functions:GEN_BUSE_CreateUsageList
						GENFUNCS:Functions:GEN_BUSE_CreateUsageList
						GENFUNCS:Argument Parsing Functions:GEN_BUSE_CreateUsageList
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_BUSE_CreateUsageList

   PUBLISH NAME:	GEN_BUSE_CreateUsageList

	ENTRY CLASS	:	Argument Parsing Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_BUSE_CreateUsageList(unsigned int param_count,
	const GEN_USAGE_PARAM *param_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
int GEN_BUSE_CreateUsageList(param_count, param_list, usage_count, usage_list,
	error_text)
unsigned int             param_count;
const GEN_USAGE_PARAM   *param_list;
unsigned int            *usage_count;
char                  ***usage_list;
char                    *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code     = GENFUNCS_SUCCESS;
	unsigned int old_usage_count = *usage_count;

	while (param_count) {
		if (((return_code = (*param_list->usage_function)(NULL,
			param_list->optional_flag, NULL, usage_count, usage_list,
			error_text)) != GENFUNCS_SUCCESS) ||
			((param_list->added_text != NULL) &&
			((return_code = GEN_BUSE_AppendLine(param_list->added_text,
			usage_count, usage_list, error_text)) != GENFUNCS_SUCCESS)) ||
			((param_list->added_text != NULL) &&
			((return_code = GEN_BUSE_AppendNL(usage_count, usage_list,
			error_text)) != GENFUNCS_SUCCESS))) {
			strl_remove(usage_count, usage_list, old_usage_count, *usage_count);
			break;
		}
		param_count--;
		param_list++;
	}

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

static const GEN_USAGE_PARAM TEST_ParamList[] = {
	{	GENFUNCS_FALSE,	GEN_BUSE_Help,				NULL	},
	{	GENFUNCS_FALSE,	GEN_BUSE_LogDir,			NULL	},
	{	GENFUNCS_FALSE,	GEN_BUSE_LogFlag,			NULL	},
	{	GENFUNCS_FALSE,	GEN_BUSE_LogQuiet,		NULL	},
	{	GENFUNCS_FALSE,	GEN_BUSE_CheckOnly,		NULL	},
	{	GENFUNCS_FALSE,	GEN_BUSE_Version,			NULL	},
   {	GENFUNCS_FALSE,	GEN_BUSE_DebugLevel,		NULL	},
   {	GENFUNCS_FALSE,	GEN_BUSE_DBDebugFlag,	NULL	},
   {	GENFUNCS_FALSE,	GEN_BUSE_SQLDebugFlag,	NULL	}
};

static const unsigned int    TEST_ParamCount  =
	sizeof(TEST_ParamList) / sizeof(TEST_ParamList[0]);

COMPAT_FN_DECL(int main, (int argc, char **argv));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int            return_code;
	unsigned int   usage_count = 0;
	char         **usage_list  = NULL;
	char           error_text[GENFUNCS_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'GEN_BUSE_CreateUsageList()'\n");
	fprintf(stderr, "---- ------- --- ----------------------------\n\n");

	if (((return_code = GEN_BUSE_CreateUsageList(TEST_ParamCount,
		TEST_ParamList, &usage_count, &usage_list, error_text)) ==
		GENFUNCS_SUCCESS) && ((return_code =
		GEN_BUSE_AppendParamText(&usage_count, &usage_list, error_text)) ==
		GENFUNCS_SUCCESS) && ((return_code = GEN_BUSE_AppendNULL(&usage_count,
		&usage_list, error_text)) == GENFUNCS_SUCCESS))
		GEN_DoFormatUsage(0, argv[0], "Usage construction successful.",
			usage_list);
	else
		fprintf(stderr, "ERROR: %s (%u parameters)\n", error_text, argc);

	strl_remove_all(&usage_count, &usage_list);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

