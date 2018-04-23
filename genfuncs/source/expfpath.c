/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	GENFUNCS General Functions Library Source Module								*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Logic to expand file and directory names to their
								fully-qualified equivalents.

	Revision History	:	1996-01-02 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*    Include necessary header files . . .                                 */
/*	***********************************************************************	*/

#include <mbcompat.h>

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#ifdef __MSDOS__
# include <direct.h>
# include <dos.h>
#elif _Windows
# include <direct.h>
# ifndef _MSC_VER
#  ifndef __MWERKS__
#   include <dir.h>
#  endif /* #  ifndef __MWERKS__ */
# endif /* #ifndef _MSC_VER */
#else
# include <pwd.h>
# include <sys/param.h>
# include <sys/types.h>
# include <unistd.h>
#endif /* #ifdef __MSDOS__ */

#include <strfuncs.h>

#include "genfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	GEN_ExpandToFullPathName

	SYNOPSIS		:	return_code = GEN_ExpandToFullPathName(in_path_name,
							out_path_name, error_text);

						int          return_code;

						const char  *in_path_name;

						char       **out_path_name;

						char        *error_text;

	DESCRIPTION	:	Expands directory and file names to their fully-qualified
						equivalents.

   PARAMETERS  :  Parameters to this function are as follows:

						(.) ``in_path_name`` is the name to be expanded.

						(.) ``out_path_name`` is a pointer to a pointer to char.
						The function, if successful, will allocate memory to
						store the expanded name and set the pointer to point to
						the allocated memory.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if the function completes without
						error. ''GENFUNCS_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero GENFUNCS return codes
						indicative of error as follows:

						(..) ''GENFUNCS_SYSTEM_FAILURE'' indicates that a standard
						library 	function or a system call failed.

						(..) ''GENFUNCS_MEMORY_FAILURE'' indicates that the memory
						required for operation of the function could not be
						allocated.

	NOTES			:	Under Unix this function performs tilde (''~'') expansion.

						Under MS-DOS and related operating systems such as Windows,
						this function prepends the drive letter (and associated
						colon character) to the fully-qualified name.

	CAVEATS		:	

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2018 Michael L. Brock

	OUTPUT INDEX:	GEN_ExpandToFullPathName
						Directory Functions:GEN_ExpandToFullPathName
						GENFUNCS:Functions:GEN_ExpandToFullPathName
						GENFUNCS:Directory Functions:GEN_ExpandToFullPathName
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_ExpandToFullPathName

	PUBLISH NAME:	GEN_ExpandToFullPathName

	ENTRY CLASS	:	Directory Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_ExpandToFullPathName(const char *in_path_name, char **out_path_name,
	char *error_text)
#else
int GEN_ExpandToFullPathName(in_path_name, out_path_name, error_text)
const char  *in_path_name;
char       **out_path_name;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code = GENFUNCS_SUCCESS;
	char          *tmp_path;
	unsigned int   alloc_length;
	char          *tmp_ptr_1;
	char          *tmp_ptr_2;
	char          *tmp_ptr_3;
	char          *begin_ptr;
	char           buffer[5];
#ifdef __MSDOS__
	int            drive_letter;
	unsigned int   drive_number;
#elif _Windows
	int            drive_letter;
	unsigned int   drive_number;
#elif _MSC_VER
	int            drive_letter;
	unsigned int   drive_number;
#else
	struct passwd *passwd_entry_ptr;
#endif /* #ifdef __MSDOS__ */

	*out_path_name = NULL;

	in_path_name   = (in_path_name == NULL) ? "" : in_path_name;

	alloc_length   = strlen(in_path_name) + 1 + (GEN_MAX_PATH_NAME_LEN * 2) + 1;

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Allocate memory in which to store the path name . . .				*/
	/*	*****************************************************************	*/
	if ((tmp_path = ((char *) calloc(alloc_length, sizeof(char)))) == NULL) {
		GEN_AllocMsgItem(alloc_length, error_text,
			"Unable to allocate full path name string: ");
		return_code = GENFUNCS_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

#ifdef __MSDOS__
	tmp_ptr_1 = ((char *) in_path_name);
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		If the programmer specified the drive letter as part of the		*/
	/*	path, that's what we'll use. Otherwise, we need to determine it.	*/
	/*	*****************************************************************	*/
	if (isalpha(*tmp_ptr_1) && (tmp_ptr_1[1] == ':')) {
		drive_letter  = STRFUNCS_toupper(*tmp_ptr_1);
		drive_number  = (drive_letter - 'A') + 1;
		tmp_ptr_1    += 2;
	}
	else {
		_dos_getdrive(&drive_number);          /* get current drive */
		drive_letter = drive_number + ('A' - 1);
	}
	/*	*****************************************************************	*/
	if (GEN_IsDirSlash(*tmp_ptr_1))
		/*	*****************************************************	*/
		/*	*****************************************************	*/
		/*		If the user passed us an absolute path, copy it.	*/
		/*	*****************************************************	*/
		strcat(tmp_path + 2, tmp_ptr_1);
		/*	*****************************************************	*/
	else {
		/*	*****************************************************	*/
		/*	*****************************************************	*/
		/*		Otherwise, it's a relative path. We'll need to		*/
		/*	determine the current working directory for the drive	*/
		/*	and prepend it to the string passed by the user.		*/
		/*	*****************************************************	*/
		/* Get drivename and its current directory.
		*/
		if (_getdcwd(drive_number, tmp_path, alloc_length - 2) == NULL) {
			strcpy(error_text, "Error getting the current working directory: ");
			GEN_AppendLastErrorString(0, GENFUNCS_MAX_ERROR_TEXT, error_text);
			return_code = GENFUNCS_SYSTEM_FAILURE;
			goto EXIT_FUNCTION;
		}
		if (!GEN_IsDirSlash(tmp_path[strlen(tmp_path) - 1]))
			chrcat(tmp_path, GEN_DirSlash);
		strcat(tmp_path, tmp_ptr_1);
		/*	*****************************************************	*/
	}
	tmp_path[0] = ((char) drive_letter);
	tmp_path[1] = ':';
	begin_ptr  = tmp_path + 2;
#elif _MSC_VER
	tmp_ptr_1 = ((char *) in_path_name);
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		If the programmer specified the drive letter as part of the		*/
	/*	path, that's what we'll use. Otherwise, we need to determine it.	*/
	/*	*****************************************************************	*/
	if (isalpha(*tmp_ptr_1) && (tmp_ptr_1[1] == ':')) {
		drive_letter  = STRFUNCS_toupper(*tmp_ptr_1);
		drive_number  = (drive_letter - 'A') + 1;
		tmp_ptr_1    += 2;
	}
	else {
		drive_number = _getdrive();		/* get current drive */
		drive_letter = (drive_number + 'A') - 1;
	}
	/*	*****************************************************************	*/
	if (GEN_IsDirSlash(*tmp_ptr_1))
		/*	*****************************************************	*/
		/*	*****************************************************	*/
		/*		If the user passed us an absolute path, copy it.	*/
		/*	*****************************************************	*/
		strcat(tmp_path + 2, tmp_ptr_1);
		/*	*****************************************************	*/
	else {
		/*	*****************************************************	*/
		/*	*****************************************************	*/
		/*		Otherwise, it's a relative path. We'll need to		*/
		/*	determine the current working directory for the drive	*/
		/*	and prepend it to the string passed by the user.		*/
		/*	*****************************************************	*/
		/* Get drivename and its current directory.
		*/
		if (_getdcwd(drive_number, tmp_path, alloc_length - 2) == NULL) {
			strcpy(error_text, "Error getting the current working directory: ");
			GEN_AppendLastErrorString(0, GENFUNCS_MAX_ERROR_TEXT, error_text);
			return_code = GENFUNCS_SYSTEM_FAILURE;
			goto EXIT_FUNCTION;
		}
		if (!GEN_IsDirSlash(tmp_path[strlen(tmp_path) - 1]))
			chrcat(tmp_path, GEN_DirSlash);
		strcat(tmp_path, tmp_ptr_1);
		/*	*****************************************************	*/
	}
	tmp_path[0] = ((char) drive_letter);
	tmp_path[1] = ':';
	begin_ptr  = tmp_path + 2;
#elif _Windows
	tmp_ptr_1 = ((char *) in_path_name);
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		If the programmer specified the drive letter as part of the		*/
	/*	path, that's what we'll use. Otherwise, we need to determine it.	*/
	/*	*****************************************************************	*/
	if (isalpha(*tmp_ptr_1) && (tmp_ptr_1[1] == ':')) {
		drive_letter  = STRFUNCS_toupper(*tmp_ptr_1);
		drive_number  = (drive_letter - 'A') + 1;
		tmp_ptr_1    += 2;
	}
	else {
		drive_number = _getdrive();		/* get current drive */
		drive_letter = drive_number + ('A' - 1);
	}
	/*	*****************************************************************	*/
	if (GEN_IsDirSlash(*tmp_ptr_1))
		/*	*****************************************************	*/
		/*	*****************************************************	*/
		/*		If the user passed us an absolute path, copy it.	*/
		/*	*****************************************************	*/
		strcat(tmp_path + 2, tmp_ptr_1);
		/*	*****************************************************	*/
	else {
		/*	*****************************************************	*/
		/*	*****************************************************	*/
		/*		Otherwise, it's a relative path. We'll need to		*/
		/*	determine the current working directory for the drive	*/
		/*	and prepend it to the string passed by the user.		*/
		/*	*****************************************************	*/
		/* Get drivename and its current directory.
		*/
		if (_getdcwd(drive_number, tmp_path, alloc_length - 2) == NULL) {
			strcpy(error_text, "Error getting the current working directory: ");
			GEN_AppendLastErrorString(0, GENFUNCS_MAX_ERROR_TEXT, error_text);
			return_code = GENFUNCS_SYSTEM_FAILURE;
			goto EXIT_FUNCTION;
		}
		if (!GEN_IsDirSlash(tmp_path[strlen(tmp_path) - 1]))
			chrcat(tmp_path, GEN_DirSlash);
		strcat(tmp_path, tmp_ptr_1);
		/*	*****************************************************	*/
	}
	tmp_path[0] = ((char) drive_letter);
	tmp_path[1] = ':';
	begin_ptr  = tmp_path + 2;
#else
	begin_ptr = tmp_path;
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		If the path name begins with a tilde ('~'), we'll need to		*/
	/*	expand it to the home directory of the appropriate user . . .		*/
	/*	*****************************************************************	*/
	if (*in_path_name == '~') {
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		If the user name is unspecified, process owner will do.	*/
		/*	***********************************************************	*/
		if ((!in_path_name[1]) || GEN_IsDirSlash(in_path_name[1])) {
			if ((passwd_entry_ptr = getpwuid(getuid())) == NULL) {
				strcpy(error_text,
					"Error getting the home directory for the current user: ");
				GEN_AppendLastErrorString(0, GENFUNCS_MAX_ERROR_TEXT, error_text);
				return_code = GENFUNCS_SYSTEM_FAILURE;
				goto EXIT_FUNCTION;
			}
			strcat(chrcat(strcpy(tmp_path, passwd_entry_ptr->pw_dir),
				GEN_DirSlash), in_path_name + 1);
		}
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		Otherwise, ask the OS to resolve the user name to their	*/
		/*	home directory . . .														*/
		/*	***********************************************************	*/
		else {
			if ((tmp_ptr_1 = strchr(strcpy(tmp_path, in_path_name),
				GEN_DirSlash)) != NULL) {
				*tmp_ptr_1 = '\0';
				tmp_ptr_2  = ((char *) in_path_name) + strlen(tmp_path) + 1;
			}
			else
				tmp_ptr_2 = "";
			if ((passwd_entry_ptr = getpwnam(tmp_path + 1)) == NULL) {
				sprintf(error_text,
					"Error getting the home directory for the user '%-.100s': ",
					tmp_path + 1);
				GEN_AppendLastErrorString(0, GENFUNCS_MAX_ERROR_TEXT, error_text);
				return_code = GENFUNCS_SYSTEM_FAILURE;
				goto EXIT_FUNCTION;
			}
			strcat(chrcat(strcpy(tmp_path, passwd_entry_ptr->pw_dir),
				GEN_DirSlash), tmp_ptr_2);
		}
		/*	***********************************************************	*/
	}
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		If the path name is absolute, just copy it . . .					*/
	/*	*****************************************************************	*/
	else if (GEN_IsDirSlash(*in_path_name))
		strcat(tmp_path, in_path_name);
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Otherwise, determine the current directory and prepend it to	*/
	/*	path name passed to the function . . .										*/
	/*	*****************************************************************	*/
	else if (getwd(tmp_path) == NULL) {
		strcpy(error_text, "Error getting the current working directory: ");
		GEN_AppendLastErrorString(0, GENFUNCS_MAX_ERROR_TEXT, error_text);
		return_code = GENFUNCS_SYSTEM_FAILURE;
		goto EXIT_FUNCTION;
	}
	else {
		if (!GEN_IsDirSlash(tmp_path[strlen(tmp_path) - 1]))
			chrcat(tmp_path, GEN_DirSlash);
		strcat(tmp_path, in_path_name);
	}
	/*	*****************************************************************	*/
#endif /* #ifdef __MSDOS__ */

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Canonicalize directory slashes . . .									*/
	/*	*****************************************************************	*/
	tmp_ptr_1 = tmp_path;
	while (*tmp_ptr_1) {
		*tmp_ptr_1 = ((char) ((GEN_IsDirSlash(*tmp_ptr_1)) ? GEN_DirSlash :
			*tmp_ptr_1));
		tmp_ptr_1++;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Remove redundant slashes . . .											*/
	/*	*****************************************************************	*/
	buffer[0] = GEN_DirSlash;
	buffer[1] = GEN_DirSlash;
	buffer[2] = '\0';
	while ((tmp_ptr_1 = strstr(tmp_path, buffer)) != NULL)
		strdele(tmp_ptr_1, 0, 1);
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Remove references to 'this' directory . . .							*/
	/*	*****************************************************************	*/
	tmp_ptr_1 = tmp_path;
	buffer[0] = GEN_DirSlash;
	buffer[1] = '.';
	buffer[2] = '\0';
	while ((tmp_ptr_2 = strstr(tmp_ptr_1, buffer)) != NULL) {
		if ((!(*(tmp_ptr_2 + 2))) || (*(tmp_ptr_2 + 2) == GEN_DirSlash))
			strdele(tmp_ptr_2, 0, 2);
		else
			tmp_ptr_1 = tmp_ptr_2 + 1;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Remove references to the parent directory . . .						*/
	/*	*****************************************************************	*/
	tmp_ptr_1 = begin_ptr;
	buffer[0] = GEN_DirSlash;
	buffer[1] = '.';
	buffer[2] = '.';
	buffer[3] = '\0';
	while ((tmp_ptr_2 = strstr(tmp_ptr_1, buffer)) != NULL) {
		if ((!(*(tmp_ptr_2 + 3))) || (*(tmp_ptr_2 + 3) == GEN_DirSlash)) {
			if (tmp_ptr_2 == begin_ptr) {
				strcpy(error_text, "Error getting the full path name.");
				return_code = GENFUNCS_SYSTEM_FAILURE;
				goto EXIT_FUNCTION;
			}
			tmp_ptr_3 = tmp_ptr_2 - 1;
			while (*tmp_ptr_3 != GEN_DirSlash)
				tmp_ptr_3--;
			if (tmp_ptr_3 == begin_ptr)
				tmp_ptr_3++;
			strdele(tmp_ptr_3, 0, ((unsigned int) (tmp_ptr_2 - tmp_ptr_3)) + 3);
		}
		else
			tmp_ptr_1 = tmp_ptr_2 + 1;
	}
	/*	*****************************************************************	*/

	*out_path_name = ((char *) realloc(tmp_path, strlen(tmp_path) + 1));

#ifdef __MSDOS__
	upper(*out_path_name);
#endif /* #ifdef __MSDOS__ */

EXIT_FUNCTION:

	if ((return_code != GENFUNCS_SUCCESS) && (tmp_path != NULL))
		free(tmp_path);

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#ifdef __MSDOS__
COMPAT_EXTERN_DATA_DECL unsigned int _stklen = 16384;
#endif /* __MSDOS__ */

COMPAT_FN_DECL(int main, (int argc, char **argv));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int           return_code = GENFUNCS_SUCCESS;
	char         *path_name;
	unsigned int  count_1;
	char          error_text[GENFUNCS_MAX_ERROR_TEXT];

	fprintf(stderr, "Test of function 'GEN_ExpandToFullPathName()'\n");
	fprintf(stderr, "---- -- -------- ----------------------------\n\n");

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if ((!stricmp("-H", argv[count_1])) ||
			(!stricmp("-HELP", argv[count_1]))) {
			fprintf(stderr,
				"USAGE:\n   %s <file-name-pattern> [<file-name-pattern>...]\n",
				argv[0]);
			goto EXIT_FUNCTION;
		}
	}

	if (argc < 2) {
		sprintf(error_text, "Invalid command line encountered.");
		sprintf(error_text, "Invalid invocation:\nUSAGE: %s %s",
			argv[0], "<file-name-pattern> [<file-name-pattern>...]");
		return_code = GENFUNCS_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		printf("[%s] ---> ", argv[count_1]);
		if ((return_code = GEN_ExpandToFullPathName(argv[count_1], &path_name,
			error_text)) != GENFUNCS_SUCCESS) {
			printf("ERROR: %s\n", error_text);
			break;
		}
		printf("[%s]\n", path_name);
		free(path_name);
		fflush(stdout);
	}

EXIT_FUNCTION:

	if (return_code != GENFUNCS_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}
#endif /* #ifdef TEST_MAIN */

