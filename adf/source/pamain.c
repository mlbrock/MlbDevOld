/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	

	Revision History	:	1990-06-27 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1990 - 2015.
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
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#define ADF_PARSE_ROOT_DEF_COUNT			2
static const SPF_SPEC ADF_PARSE_RootDefList[ADF_PARSE_ROOT_DEF_COUNT] = {
	{
		"@include",
		{	"@include_file"	},
		SPF_TYPE_INCLUDE_FILE,
		0,		UINT_MAX,
		0,		UINT_MAX,
		0.0,	0.0,
		0,
		0,
		{	NULL,
			NULL
		}
	},
	{
		"@domain",
		{	""	},
		ADF_PARSE_TYPE_DOMAIN,
		0,		UINT_MAX,
		0,		0,
		0.0,	0.0,
		0,
		0,
		{
			ADF_PARSE_Any,
			NULL
		}
	}
};
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_PARSE_Main(SPF_CONTEXT *context_ptr, const char *file_name,
	const char *def_string, char *error_text)
#else
int ADF_PARSE_Main(context_ptr, file_name, def_string, error_text)
SPF_CONTEXT *context_ptr;
const char  *file_name;
const char  *def_string;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code;
	SPF_SPEC_FUNCS funcs_data;

	SPF_INIT_SpecFuncs(&funcs_data);

	funcs_data.parse      = ADF_PARSE_Any;
	funcs_data.post_parse = NULL;

	return_code = SPF_PARSE_File(context_ptr, file_name, def_string,
		&funcs_data, ADF_PARSE_ROOT_DEF_COUNT, ADF_PARSE_RootDefList,
		error_text);

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
	int             return_code = ADF_SUCCESS;
	int             emit_flag   = ADF_FALSE;
	ADF_CONTROL     control_data;
	SPF_CONTEXT     context_data;
	unsigned int    count_1;
	SDTIF_STAT_TVAL stat_data_1;
	SDTIF_STAT_TVAL stat_data_2;
	SDTIF_STAT_TVAL stat_data_3;
	SDTIF_STAT_TVAL stat_data_4;
	char            time_buffer[512];
	char            error_text[ADF_MAX_ERROR_TEXT];

	fprintf(stderr,
		"Test routine for function 'ADF_PARSE_Main()'\n");
	fprintf(stderr,
		"---- ------- --- -------- ------------------\n");

	ADF_INIT_Control(&control_data);
	SPF_INIT_Context(&context_data);
	context_data.user_data_ptr       = &control_data;
	context_data.user_data_free_func = ((void *) ADF_FREE_Control);

	SDTIF_STAT_TVAL_Init(&stat_data_1);
	SDTIF_STAT_TVAL_Init(&stat_data_2);
	SDTIF_STAT_TVAL_Init(&stat_data_3);
	SDTIF_STAT_TVAL_Init(&stat_data_4);

	for (count_1 = 1; count_1 < argc; count_1++) {
		if (!stricmp(argv[count_1], "-EMIT=ON")) {
			emit_flag = ADF_TRUE;
			continue;
		}
		else if (!stricmp(argv[count_1], "-EMIT=OFF")) {
			emit_flag = ADF_FALSE;
			continue;
		}
		fprintf(stderr, "ADF Definition File: %s\n", argv[count_1]);
		STR_EMIT_CharLine('*', 78, NULL, NULL);
		STR_EMIT_CharLine('*', 78, NULL, NULL);
		printf("ADF Definition File: %s\n", argv[count_1]);
		STR_EMIT_CharLine('*', 78, NULL, NULL);
		SDTIF_STAT_TVAL_StartTime(&stat_data_1);
		if ((return_code = ADF_ReadDefinitionFile(&control_data, argv[count_1],
			error_text)) != ADF_SUCCESS)
			break;
		SDTIF_STAT_TVAL_EndTime(&stat_data_1, 1);
		SDTIF_STAT_TVAL_StartTime(&stat_data_2);
		SDTIF_STAT_TVAL_EndTime(&stat_data_2, 1);
		if (emit_flag == ADF_TRUE) {
			SDTIF_STAT_TVAL_StartTime(&stat_data_3);
			SDTIF_STAT_TVAL_EndTime(&stat_data_3, 1);
		}
		SDTIF_STAT_TVAL_StartTime(&stat_data_4);
		ADF_FREE_Control(&control_data);
		SDTIF_STAT_TVAL_EndTime(&stat_data_4, 1);
		STR_EMIT_CharLine('*', 78, NULL, NULL);
	}

	if (return_code == ADF_SUCCESS) {
		fprintf(stderr, "Create Time: %s\n",
			SDTIF_STAT_TVAL_FmtTotalInterval(&stat_data_1, time_buffer));
		fprintf(stderr, "Check Time : %s\n",
			SDTIF_STAT_TVAL_FmtTotalInterval(&stat_data_2, time_buffer));
		fprintf(stderr, "Emit Time  : %s\n",
			SDTIF_STAT_TVAL_FmtTotalInterval(&stat_data_3, time_buffer));
		fprintf(stderr, "Free Time  : %s\n",
			SDTIF_STAT_TVAL_FmtTotalInterval(&stat_data_4, time_buffer));
	}
	else
		fprintf(stderr, "ERROR: %s\n", error_text);

/*
	CODE NOTE: To be removed.
	ADF_FREE_Control(&control_data);
*/
	SPF_FREE_Context(&context_data);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

