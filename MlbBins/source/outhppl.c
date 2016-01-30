/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLB Executable Module Source File													*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Outputs matched string in HPPL (Hewlett Packard
								Printer Language) format.

	Revision History	:	1998-03-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include <genfuncs.h>
#include <pcff.h>

#include "kmlfuncs.h"

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
	int               return_code         = KMLFUNCS_SUCCESS;
	const char       *specified_file_type = NULL;
	const char       *default_file_type   = NULL;
	unsigned int      count_1;
	KML_CONTROL       control_data;
	const KML_DOMAIN *domain_ptr;
	const char       *file_type;
	char             *file_buffer;
	struct stat       stat_data;
	char              pcff_error_text[PCFF_MAX_ERROR_TEXT];
	char              error_text[KMLFUNCS_MAX_ERROR_TEXT];

	KML_INIT_Control(&control_data);

	/*	*****************************************************************
		*****************************************************************
		First, scan the command line parameters for a help request . . .
		*****************************************************************	*/
	if (PCFF_CMLPARAM_LocateHelp(argc, argv, NULL)) {
		fprintf(stderr, "USAGE:\n   %s %s %s %s %s %s\n\n",
			extract_file_name(argv[0]),
			"[ -h | -help ]"
			"[ -file_type <extension-type> ]",
			"[ -default_file_type <extension-type> ]",
			"<source-file-name> [ <source-file-name> . . . ]");
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Ensure we have at least one command line argument . . .
		*****************************************************************	*/
	if (argc == 1) {
		sprintf(error_text, "Invalid command line --- use '-h' for help");
		return_code = KMLFUNCS_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Set up the parsing control data . . .
		*****************************************************************	*/
	if ((return_code = KML_TEST_InitializeControl(&control_data,
		error_text)) != KMLFUNCS_SUCCESS)
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/


	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		/*	***********************************************************
			***********************************************************
			If a specified file type was requested, resolve it . . .
			***********************************************************	*/
		if (PCFF_CMLPARAM_FindVA(argv[count_1], NULL, "-file_type", "-filetype",
			"-type", "-specified_file_type", "-specified_filetype",
			"-specifiedfile_type", "-specifiedfiletype", "-specified_type",
			"-specifiedtype", "-spec_file_type", "-spec_filetype",
			"-specfile_type", "-specfiletype", "-spec_type", "-spectype", NULL)) {
			if (PCFF_CMLPARAM_CheckFollowing(argc, count_1, argv,
				pcff_error_text) != PCFF_SUCCESS) {
				nstrcpy(error_text, pcff_error_text, KMLFUNCS_MAX_ERROR_TEXT - 1);
				return_code = KMLFUNCS_BAD_ARGS_FAILURE;
				goto EXIT_FUNCTION;
			}
			else if ((domain_ptr = KML_FIND_ControlDomainByType(&control_data,
				argv[count_1 + 1])) == NULL) {
				strcat(nstrcat(strcat(strcat(strcpy(error_text,
					"Unable to locate a domain for the '"), argv[count_1]),
					"' parameter file extension '"), argv[count_1 + 1],
					KMLFUNCS_MAX_ERROR_TEXT - 100), "'.");
				return_code = KMLFUNCS_BAD_ARGS_FAILURE;
				goto EXIT_FUNCTION;
			}
			specified_file_type = argv[++count_1];
		}
		/*	***********************************************************	*/
		/*	***********************************************************
			***********************************************************
			If a default file type was requested, resolve it . . .
			***********************************************************	*/
		else if (PCFF_CMLPARAM_FindVA(argv[count_1], NULL, "-default_file_type",
			"-default_filetype", "-defaultfile_type", "-defaultfiletype",
			"-default_type", "-defaulttype", "-def_file_type", "-def_filetype",
			"-deffile_type", "-deffiletype", "-def_type", "-deftype", NULL)) {
			if (PCFF_CMLPARAM_CheckFollowing(argc, count_1, argv,
				pcff_error_text) != PCFF_SUCCESS) {
				nstrcpy(error_text, pcff_error_text, KMLFUNCS_MAX_ERROR_TEXT - 1);
				return_code = KMLFUNCS_BAD_ARGS_FAILURE;
				goto EXIT_FUNCTION;
			}
			else if ((domain_ptr = KML_FIND_ControlDomainByType(&control_data,
				argv[count_1 + 1])) == NULL) {
				strcat(nstrcat(strcat(strcat(strcpy(error_text,
					"Unable to locate a domain for the '"), argv[count_1]),
					"' parameter file extension '"), argv[count_1 + 1],
					KMLFUNCS_MAX_ERROR_TEXT - 100), "'.");
				return_code = KMLFUNCS_BAD_ARGS_FAILURE;
				goto EXIT_FUNCTION;
			}
			default_file_type = argv[++count_1];
		}
		/*	***********************************************************	*/
		else {
			fprintf(stderr, "File: %s ", argv[count_1]);
			if ((file_type = strrchr(argv[count_1], '.')) != NULL)
				file_type = (*file_type) ? file_type : NULL;
			if (specified_file_type != NULL) {
				fprintf(stderr, "(using specified type '%s') ",
					specified_file_type);
				file_type = specified_file_type;
			}
			else if (KML_FIND_ControlDomainByType(&control_data, file_type) ==
				NULL) {
				fprintf(stderr, "--- unable to resolve file extension '%s' --- ",
					file_type);
				file_type = NULL;
			}
			if (file_type == NULL) {
				if (default_file_type != NULL) {
					fprintf(stderr, "(using default type '%s') ", default_file_type);
					file_type = default_file_type;
				}
				else {
					fprintf(stderr, "(using file extension 'c') ");
					file_type = "c";
				}
			}
			if ((domain_ptr = KML_FIND_ControlDomainByType(&control_data,
				file_type)) == NULL) {
				fprintf(stderr,
					": Unable to locate a domain for file extension '%s'.\n",
					file_type);
				strcat(nstrcat(strcat(nstrcat(strcpy(error_text,
					"Unable to resolve a file extension for file '"), argv[count_1],
					(KMLFUNCS_MAX_ERROR_TEXT - 100) / 2),
					"': the domain for extension '"), file_type,
					(KMLFUNCS_MAX_ERROR_TEXT - 100) / 2), "' could not be resolved.");
				return_code = KMLFUNCS_BAD_ARGS_FAILURE;
				goto EXIT_FUNCTION;
			}
			else
				fprintf(stderr, ": Found domain name '%s', description '%s'.\n",
					domain_ptr->domain_name, domain_ptr->domain_description);
			if ((return_code = KML_TFREAD_ReadFileBuffer(argv[count_1], NULL,
				&file_buffer, error_text)) != KMLFUNCS_SUCCESS)
				break;
			if (stat(argv[count_1], &stat_data) != 0) {
				sprintf(error_text, "Unable to 'stat()' file '%-500s': ",
					argv[count_1]);
				GEN_AppendLastErrorString(0, KML_MAX_ERROR_TEXT - 1,
					error_text);
				return_code = KML_SYSTEM_FAILURE;
				break;
			}
			if ((domain_ptr != NULL) && ((return_code =
				KML_MatchAll(&control_data, domain_ptr, file_buffer,
				KML_TYPE_STRING | KML_TYPE_COMMENT | KML_TYPE_KEYWORD,
				error_text)) != KMLFUNCS_SUCCESS))
				break;
			KML_OutputHPPL(&control_data, argv[count_1], stat_data.st_mtime, 3,
				file_buffer, NULL, NULL);
			free(file_buffer);
			KML_ClearMatchList(&control_data);
		}              
	}

EXIT_FUNCTION:

	KML_FREE_Control(&control_data);

	if (return_code != KMLFUNCS_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n", error_text);

	return((return_code == KMLFUNCS_SUCCESS) ? EXIT_SUCCESS : EXIT_FAILURE);
}
/*	***********************************************************************	*/

