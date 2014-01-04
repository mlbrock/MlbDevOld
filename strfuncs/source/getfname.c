/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Extracts the file name component from a path name.

	Revision History	:	1996-04-11 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include <string.h>

#include "strfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	extract_file_name

   SYNOPSIS    :	return_ptr = extract_file_name(in_path);

						const char *return_ptr;

						const char *in_path;


   DESCRIPTION :	Locates the file name portion of a path name.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_path`` is the path name in which the file name
						portion is to be located.

   RETURNS     :	A pointer to the file-name portion of ``in_path``.

						If ``in_path`` does not contain a file name, a pointer to
						terminating ASCII 0 of ``in_path`` is returned by this
						function.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1996 - 2014 Michael L. Brock

   OUTPUT INDEX:	extract_file_name
						Miscellaneous Functions:extract_file_name
						STRFUNCS:Miscellaneous Functions:extract_file_name
						String Functions:See STRFUNCS

   PUBLISH XREF:	extract_file_name

   PUBLISH NAME:	extract_file_name

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
const char *extract_file_name(const char *in_path)
#else
const char *extract_file_name(in_path)
const char *in_path;
#endif /* #ifndef NARGS */
{
	const char *ptr;

	/*	*****************************************************************
		*****************************************************************
		We need to get the file name without such things as the drive
		specification or directory hierarchy. Different for each OS . . .
		*****************************************************************	*/
#ifdef __MSDOS__
		in_path = ((ptr = strrchr(in_path, ':'))  != NULL) ? (ptr + 1) : in_path;
		in_path = ((ptr = strrchr(in_path, '\\')) != NULL) ? (ptr + 1) : in_path;
		in_path = ((ptr = strrchr(in_path, '/'))  != NULL) ? (ptr + 1) : in_path;
#else
# ifdef _Windows
		in_path = ((ptr = strrchr(in_path, ':'))  != NULL) ? (ptr + 1) : in_path;
		in_path = ((ptr = strrchr(in_path, '\\')) != NULL) ? (ptr + 1) : in_path;
		in_path = ((ptr = strrchr(in_path, '/'))  != NULL) ? (ptr + 1) : in_path;
# else
#  ifdef _VMS_
		in_path = ((ptr = strrchr(in_path, ']'))  != NULL) ? (ptr + 1) : in_path;
		in_path = ((ptr = strrchr(in_path, ':'))  != NULL) ? (ptr + 1) : in_path;
#  else
		in_path = ((ptr = strrchr(in_path, '/'))  != NULL) ? (ptr + 1) : in_path;
#  endif /* # ifdef _VMS_ */
# endif /* # ifdef _Windows */
#endif /* #ifdef __MSDOS__ */
	/*	*****************************************************************	*/

	return(in_path);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <stdio.h>
#include <stdlib.h>

COMPAT_FN_DECL(int main, (int argc, char **argv));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int           return_code = STRFUNCS_SUCCESS;
	unsigned int  count_1;
	unsigned int  start;

	fprintf(stderr, "Test routine for 'extract_file_name()'\n");
	fprintf(stderr, "---- ------- --- ---------------------\n\n");

	start = (argc == 1) ? 0 : 1;

	for (count_1 = start; count_1 < ((unsigned int) argc); count_1++)
		printf("[%05u]:[%s]\n       :[%s]\n", count_1, argv[count_1],
			extract_file_name(argv[count_1]));

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

