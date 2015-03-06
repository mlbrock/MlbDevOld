/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Reads an ADF domain definition file.

	Revision History	:	1994-06-10 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2015.
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

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_ReadDefinitionFile(ADF_CONTROL *control_ptr, const char *file_name,
	char *error_text)
#else
int ADF_ReadDefinitionFile(control_ptr, file_name, error_text)
ADF_CONTROL *control_ptr;
const char  *file_name;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code;
	char        *def_string;
	SPF_CONTEXT  context_data;

	if ((return_code = SPF_ReadDefFile(file_name, NULL, &def_string,
		error_text)) == SPF_SUCCESS) {
		SPF_INIT_Context(&context_data);
		context_data.user_data_ptr = control_ptr;
		return_code = ADF_PARSE_Main(&context_data, file_name, def_string,
			error_text);
		if (def_string != NULL)
			free(def_string);
		SPF_FREE_Context(&context_data);
	}

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <memory.h>
#include <stdlib.h>
#include <string.h>

#ifdef __MSDOS__
COMPAT_EXTERN_DATA_DECL unsigned int _stklen = 32000;
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
	int          return_code = ADF_SUCCESS;
	unsigned int count_1;
	ADF_CONTROL  control_data;
	char         error_text[ADF_MAX_ERROR_TEXT];

	fprintf(stderr,
		"Test routine for function 'ADF_ReadDefinitionFile()'\n");
	fprintf(stderr,
		"---- ------- --- -------- --------------------------\n\n");

	ADF_INIT_Control(&control_data);

	for (count_1 = 1; count_1 < argc; count_1++) {
		fprintf(stderr,
			"===============================================================\n");
		if ((return_code = ADF_ReadDefinitionFile(&control_data, argv[count_1],
			error_text)) != ADF_SUCCESS)
			break;
		fprintf(stderr,
			"---------------------------------------------------------------\n");
		ADF_EMIT_Def(control_data.domain_count, control_data.domain_list, NULL,
			NULL);
		fprintf(stderr,
			"---------------------------------------------------------------\n");
		ADF_FREE_Control(&control_data);
	}

EXIT_FUNCTION:

	if (return_code != ADF_SUCCESS)
		fprintf(stderr, "ERROR: %s\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

