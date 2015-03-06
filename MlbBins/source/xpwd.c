/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLB Executable Module Source File													*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Emits the current directory name.

	Revision History	:	2000-01-22 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2000 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Required include files . . .															*/
/*	***********************************************************************	*/

#include <stdio.h>

#include <genfuncs.h>

/*	***********************************************************************	*/

/*	***********************************************************************	*/
COMPAT_FN_DECL(int main, (void));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int main()
{
	int  return_code;
	char current_dir[GEN_MAX_PATH_NAME_LEN + 1];
	char error_text[GENFUNCS_MAX_ERROR_TEXT];

	if ((return_code = GEN_DetermineCurrentDir(current_dir, error_text)) ==
		GENFUNCS_SUCCESS)
		printf("%s\n", current_dir);
	else
		fprintf(stderr, "ERROR: %s\n", error_text);

	return(return_code);
}
/*	***********************************************************************	*/


