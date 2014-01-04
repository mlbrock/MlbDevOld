/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Emits the C code equivalent to a combination of one
								or more ADF definitions files specified on the command
								line to 'stdout'.

								If no ADF definition files are specified on the
								command line, the current internal ADF definition
								is emitted instead.

	Revision History	:	1995-08-31 --- Creation.
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

#include <string.h>

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
COMPAT_FN_DECL(int main, (int argc, char **argv));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#ifdef __MSDOS__
COMPAT_EXTERN_DATA_DECL unsigned int _stklen = 32000;
#endif /* __MSDOS__ */
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int           return_code = ADF_SUCCESS;
	unsigned int  count_1;
	ADF_CONTROL   control_data;
	unsigned int  domain_count;
	ADF_DOMAIN   *domain_list;
	char          error_text[ADF_MAX_ERROR_TEXT];

	ADF_INIT_Control(&control_data);

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if ((!stricmp("-HELP", argv[count_1])) ||
			(!stricmp("-H", argv[count_1]))) {
			fprintf(stderr, "USAGE:\n   %s { -H[ELP] | %s }\n", argv[0],
				"[<adf-definition-file> [<adf-definition-file> . . .]]");
			goto EXIT_FUNCTION;
		}
	}

	if (argc == 1)
		ADF_GetDefaultDefSpec(&domain_count, &domain_list);
	else {
		for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
			if ((return_code = ADF_ReadDefinitionFile(&control_data,
				argv[count_1], error_text)) != ADF_SUCCESS)
				goto EXIT_FUNCTION;
		}
		domain_count = control_data.domain_count;
		domain_list  = control_data.domain_list;
	}

	return_code = ADF_EMIT_DefCDomainList(domain_count, domain_list, NULL,
		NULL, error_text);

EXIT_FUNCTION:

	ADF_FREE_Control(&control_data);

	if (return_code != ADF_SUCCESS)
		fprintf(stderr, "ERROR: %s\n", error_text);

	return(return_code);
}
/*	***********************************************************************	*/

