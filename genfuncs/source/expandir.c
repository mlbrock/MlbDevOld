/* *********************************************************************** */
/* *********************************************************************** */
/*	GENFUNCS General Functions Library Source Module								*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Expands a directory name, with '~' expansion.

	Revision History	:	1991-11-10 --- Creation.
									Minh Ton Ha

		Copyright Michael L. Brock 1991 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/*	Required include files . . .															*/
/* *********************************************************************** */

#include <stdlib.h>
#include <string.h>

#include "genfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  expandir

   SYNOPSIS    :  return_code = expandir(path_name, return_path_name);

                  int   return_code;

                  char *path_name;

                  char *return_path_name;

   DESCRIPTION :  This function returns the full path name if it is prefixed
                  by a tilde (''~''). Otherwise the pathname is unchanged.

   PARAMETERS  :  The parameters to this function are as follow:

                  (.) ``path_name`` is the path name of the directory to
						be expanded.

						(.) ``return_path_name`` is the expanded path name.

   RETURNS     :  Returns from this function are as follow:

                  (.)``return_code`` is set to ''GENFUNCS_SUCCESS'' on
						successful operation. Otherwise, it will be set to one
						of the defined non-zero GENFUNCS return codes indicative
						of error.

   NOTES       :  This function has been superseded by the function
						``GEN_ExpandToFullPathName``. It is maintained as part of
						the library only to avoid invalidating existing code.

   CAVEATS     :  

   SEE ALSO    :  GEN_ExpandToFullPathName

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2014 Michael L. Brock

	OUTPUT INDEX:	expandir
						Directory Functions:expandir
						GENFUNCS:Functions:expandir
						GENFUNCS:Directory Functions:expandir
						General Functions:See GENFUNCS

	PUBLISH XREF:	expandir

	PUBLISH NAME:	expandir

	ENTRY CLASS	:	Directory Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int expandir(char *path_name, char *return_path_name)
#else
int expandir(path_name, return_path_name)
char *path_name;
char *return_path_name;
#endif /* #ifndef NARGS */
{
	int   return_code;
	char *tmp_path;
	char  error_text[GENFUNCS_MAX_ERROR_TEXT];

	if ((return_code = GEN_ExpandToFullPathName(path_name, &tmp_path,
		error_text)) == GENFUNCS_SUCCESS) {
		strcpy(return_path_name, tmp_path);
		free(tmp_path);
	}
	else
		*return_path_name = '\0';

	return(return_code);
}

#ifdef TEST_MAIN

COMPAT_FN_DECL(int main, (int, char **));

/*=============================================================================
   test routine
  ===========================================================================*/

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int  return_code = 0;
	char return_path_name[256];


	/* start logic */
	fprintf(stderr, "This is a test of the 'expandir()' function\n");
	fprintf(stderr, "---- -- - ---- -- --- ------------ --------\n\n");

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
		exit(-1);
	}

	if (0 != (return_code = expandir(argv[1], return_path_name)))
		fprintf(stderr, "%s: Call to function 'expandir()' failed.\n", argv[0]);
	else {
		printf("%s\n", return_path_name);
	}

	fprintf(stderr, "%s: return_code = %d\n", argv[0], return_code);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

