/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLB Executable Module Source File													*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Emits the hostname.

	Revision History	:	1993-04-08 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2018.
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

#include <npsl.h>

/*	***********************************************************************	*/

/*	***********************************************************************	*/
COMPAT_FN_DECL(int main, (void));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int main()
{
	int  return_code;
	char host_name[NPSL_MAX_HOST_NAME_LEN + 1];
	char error_text[NPSL_MAX_ERROR_TEXT];

	if ((return_code = NPSL_DetermineHostName(host_name, error_text)) ==
		NPSL_SUCCESS)
		printf("%s\n", host_name);
	else
		fprintf(stderr, "ERROR: %s\n", error_text);

	return((return_code == NPSL_SUCCESS) ? EXIT_SUCCESS : EXIT_FAILURE);
}
/*	***********************************************************************	*/


