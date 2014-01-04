/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Network Programming Support Library (NPSL) Source Module						*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets/sets the host name.

	Revision History	:	1993-04-08 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <string.h>

#include "npsli.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int NPSL_DetermineHostName(char *host_name, char *error_text)
{
	int return_code;

	if (!NPSL_GetHostName(host_name, NPSL_MAX_HOST_NAME_LEN))
		return_code = NPSL_SUCCESS;
	else {
		strcpy(error_text, "Unable to determine the current host-name: ");
		GEN_AppendLastErrorString(0, NPSL_MAX_ERROR_TEXT - 100, error_text);
		return_code = NPSL_SYSTEM_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int NPSL_GetHostName(char *host_name, unsigned int host_name_length)
{
#ifdef _Windows
/*
	Under Windows, the length must include space for the ASCII 0
*/
	unsigned int out_host_name_length = host_name_length + 1;
	return((GetComputerName(((LPTSTR) host_name),
		((LPDWORD) &out_host_name_length))) ? 0 : -1);
#else
# ifndef __MSDOS__
	return(gethostname(host_name, ((int) host_name_length)));
# else
	if (host_name_length < strlen("MS-DOS-Machine"))
		return(-1);
	else {
		strcpy(host_name, "MS-DOS-Machine");
		return(0);
	}
# endif /* # ifndef __MSDOS__ */
#endif /* #ifdef _Windows */
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int NPSL_SetHostName(const char *host_name)
{
#ifdef _Windows
	return((SetComputerName(((LPCSTR) host_name))) ? 0 : -1);
#else
# ifndef __MSDOS__
	return(sethostname(host_name, strlen(host_name)));
# else
	return(0);
# endif /* # ifndef __MSDOS__ */
#endif /* #ifdef _Windows */
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

COMPAT_FN_DECL(int main, (void));

int main()
{
	int  return_code;
	char host_name[NPSL_MAX_HOST_NAME_LEN + 1];
	char error_text[NPSL_MAX_ERROR_TEXT];

	fprintf(stderr, "Test harness for function 'NPSL_GetHostName()'\n");
	fprintf(stderr, "---- ------- --- -------- --------------------\n\n");

	if ((return_code = NPSL_DetermineHostName(host_name, error_text)) ==
		NPSL_SUCCESS)
		printf("Host Name: %s\n", host_name);
	else
		fprintf(stderr, "ERROR: %s\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

