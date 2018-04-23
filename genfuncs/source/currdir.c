/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	GENFUNCS General Functions Library Source Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets the current directory name.

	Revision History	:	2000-01-22 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2000 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <mbcompat.h>

#include <string.h>

#ifdef __MSDOS__
# include <direct.h>
# include <dir.h>
#elif _Windows
# include <direct.h>
# ifndef _MSC_VER
#  ifndef __MWERKS__
#   include <dir.h>
#  endif /* #  ifndef __MWERKS__ */
# endif /* #ifndef _MSC_VER */
#else
# include <errno.h>
#endif /* #ifdef __MSDOS__ */

#include "genfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int GEN_DetermineCurrentDir(char *current_dir, char *error_text)
#else
int GEN_DetermineCurrentDir(current_dir, error_text)
char *current_dir;
char *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (current_dir == NULL) {
		strcpy(error_text, "Current directory pointer is 'NULL'.");
		return_code = GENFUNCS_FAILURE;
	}
	else if (GEN_GetCurrentDir(current_dir, GEN_MAX_PATH_NAME_LEN) != NULL)
		return_code = GENFUNCS_SUCCESS;
	else {
		strcpy(error_text, "Unable to determine the current directory name: ");
		GEN_AppendLastErrorString(0, GENFUNCS_MAX_ERROR_TEXT - 100, error_text);
		return_code = GENFUNCS_SYSTEM_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *GEN_GetCurrentDir(char *current_dir, unsigned int current_dir_length)
#else
char *GEN_GetCurrentDir(current_dir, current_dir_length)
char         *current_dir;
unsigned int  current_dir_length;
#endif /* #ifndef NARGS */
{
	char *return_ptr;

#ifdef __MSDOS__
	return_ptr = getcwd(current_dir, current_dir_length);
#elif _Windows
	return_ptr = getcwd(current_dir, current_dir_length);
#else
	char tmp_dir[GEN_MAX_PATH_NAME_LEN + 1];

	if ((return_ptr = GEN_GetCurrentDirBasic(tmp_dir)) != NULL) {
		if (current_dir_length < strlen(tmp_dir)) {
			errno      = ERANGE;
			return_ptr = NULL;
		}
		else if (current_dir != NULL)
			strcpy(current_dir, tmp_dir);
		else if ((return_ptr = ((char *) calloc(strlen(tmp_dir) + 1,
			sizeof(char)))) == NULL)
			errno = ENOMEM;

	}
#endif /* #ifdef __MSDOS__ */

	return(return_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *GEN_GetCurrentDirBasic(char *current_dir)
#else
char *GEN_GetCurrentDirBasic(current_dir)
char *current_dir;
#endif /* #ifndef NARGS */
{
#ifdef __MSDOS__
	return(getcwd(current_dir, GEN_MAX_PATH_NAME_LEN));
#elif _Windows
	return(getcwd(current_dir, GEN_MAX_PATH_NAME_LEN));
#else
	return(getwd(current_dir));
#endif /* #ifdef __MSDOS__ */
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

COMPAT_FN_DECL(int main, (void));

int main()
{
	int   return_code;
	char *current_dir_ptr = NULL;
	char  current_dir[GEN_MAX_PATH_NAME_LEN + 1];
	char  error_text[GENFUNCS_MAX_ERROR_TEXT];

	fprintf(stderr, "Test harness for function 'GEN_DetermineCurrentDir()'\n");
	fprintf(stderr, "---- ------- --- -------- ---------------------------\n\n");

	if ((return_code = GEN_DetermineCurrentDir(current_dir, error_text)) ==
		GENFUNCS_SUCCESS) {
		printf("GEN_DetermineCurrentDir(): %s\n", current_dir);
		if ((current_dir_ptr = GEN_GetCurrentDir(NULL,
			GEN_MAX_PATH_NAME_LEN)) == NULL) {
			strcat(strcpy(error_text,
				"Unable to determine the current directory name with "),
				"'GEN_GetCurrentDir()': ");
			GEN_AppendLastErrorString(0, GENFUNCS_MAX_ERROR_TEXT - 100,
				error_text);
			return_code = GENFUNCS_FAILURE;
		}
		else {
			printf("GEN_GetCurrentDir()      : %s\n", current_dir_ptr);
			free(current_dir_ptr);
			if ((current_dir_ptr = GEN_GetCurrentDirBasic(current_dir)) ==
				NULL) {
				strcat(strcpy(error_text,
					"Unable to determine the current directory name with "),
					"'GEN_GetCurrentDirBasic()': ");
				GEN_AppendLastErrorString(0, GENFUNCS_MAX_ERROR_TEXT - 100,
					error_text);
				return_code = GENFUNCS_FAILURE;
			}
			else
				printf("GEN_GetCurrentDirBasic() : %s\n", current_dir);
		}
	}

	if (return_code != GENFUNCS_SUCCESS)
		fprintf(stderr, "ERROR: %s\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

