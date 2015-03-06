/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Outputs matched string to a string buffer.

	Revision History	:	1998-03-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2015.
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
#include <stdlib.h>

#include "kmlfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Function prototypes for static functions . . .								*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(int KML_EmitString, (const char *in_ptr,
	unsigned int in_length, unsigned int tab_setting, char **buffer_ptr,
	char *error_text));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int KML_OutputString(KML_CONTROL *control_ptr, unsigned int tab_setting,
	const char *in_string, char **buffer_ptr, char *error_text)
#else
int KML_OutputString(control_ptr, tab_setting, in_string, buffer_ptr,
	error_text)
KML_CONTROL   *control_ptr;
unsigned int   tab_setting;
const char    *in_string;
char         **buffer_ptr;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int              return_code = KMLFUNCS_SUCCESS;
	const char      *in_ptr;
	unsigned int     in_length;
	unsigned int     tmp_length;
	const KML_MATCH *match_ptr;
	const KML_MATCH *old_match_ptr;

	*buffer_ptr = NULL;

	if (!(*in_string)) {
		if ((*buffer_ptr = ((char *) calloc(1, sizeof(char)))) == NULL) {
			STR_AllocMsgItem(1, error_text,
				"Unable to expand a string by an additional 1 byte");
			return_code = KMLFUNCS_MEMORY_FAILURE;
		}
		goto EXIT_FUNCTION;
	}

	in_ptr    = in_string;
	in_length = strlen(in_string);
	match_ptr = control_ptr->match_list;

	while (*in_ptr) {
		if (match_ptr == NULL) {
			return_code = KML_EmitString(in_ptr, in_length, tab_setting,
				buffer_ptr, error_text);
			break;
		}
		else if (in_ptr < match_ptr->ptr) {
			if ((return_code = KML_EmitString(in_ptr,
				tmp_length = ((unsigned int) (match_ptr->ptr - in_ptr)),
				tab_setting, buffer_ptr, error_text)) != KMLFUNCS_SUCCESS)
				break;
			in_ptr    += tmp_length;
			in_length -= tmp_length;
		}                                      
		else {
			if ((return_code = KML_EmitString(match_ptr->ptr, match_ptr->length,
				tab_setting, buffer_ptr, error_text)) != KMLFUNCS_SUCCESS)
				break;
			in_ptr        += match_ptr->length;
			in_length     -= match_ptr->length;
			old_match_ptr  = match_ptr;
			/*
				Just in case matches are contained within other matches.
			*/
			while ((match_ptr == old_match_ptr) || ((match_ptr != NULL) &&
				(match_ptr->ptr < (old_match_ptr->ptr + old_match_ptr->length))))
				match_ptr  = (match_ptr <
					(control_ptr->match_list + (control_ptr->match_count - 1))) ?
					(match_ptr + 1) : NULL;
		}
	}

EXIT_FUNCTION:

	if (return_code != KMLFUNCS_SUCCESS) {
		if (*buffer_ptr != NULL)
			free(*buffer_ptr);
		*buffer_ptr = NULL;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int KML_EmitString(const char *in_ptr, unsigned int in_length,
	unsigned int tab_setting, char **buffer_ptr, char *error_text)
#else
static int KML_EmitString(in_ptr, in_length, tab_setting, buffer_ptr,
	error_text)
const char    *in_ptr;
unsigned int   in_length;
unsigned int   tab_setting;
char         **buffer_ptr;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = KMLFUNCS_SUCCESS;
	unsigned int current_col = 0;
	unsigned int space_count;
	unsigned int space_length;  
	char         tab_buffer[512];

	if (tab_setting == UINT_MAX) {
		if (strnvacat(buffer_ptr, in_length, in_ptr, NULL) == NULL) {
			STR_AllocMsgItem(strlen(*buffer_ptr) + in_length + 1, error_text,
				"Unable to expand a string by an additional %u bytes",
				in_length);
			return_code = KMLFUNCS_MEMORY_FAILURE;
		}
	}
	else {
		while (*in_ptr && in_length) {
			if ((*in_ptr == '\n') || (*in_ptr == '\r')) {
				if ((*in_ptr == '\r') && ((in_length > 1) &&
					(*(in_ptr + 1) == '\n'))) {
					if (strnvacat(buffer_ptr, 2, in_ptr, NULL) ==
						NULL) {
						STR_AllocMsgItem(strlen(*buffer_ptr) + 2,
							error_text,
							"Unable to expand a string by an additional 2 bytes");
						return_code = KMLFUNCS_MEMORY_FAILURE;
						goto EXIT_FUNCTION;
					}
					in_ptr++;
					in_length--;
				}
				else if (strnvacat(buffer_ptr, 1, in_ptr, NULL) ==
					NULL) {
					STR_AllocMsgItem(strlen(*buffer_ptr) + 1,
						error_text,
						"Unable to expand a string by an additional 1 byte");
					return_code = KMLFUNCS_MEMORY_FAILURE;
					goto EXIT_FUNCTION;
				}
			}
			else if (*in_ptr == '\t') {
				if (tab_setting) {
					space_count = tab_setting - (current_col % tab_setting);
					while (space_count) {
						space_length = (space_count < sizeof(tab_buffer)) ?
							space_count : (sizeof(tab_buffer) - 1);
						memset(tab_buffer, ' ', space_length);
						if ((return_code = KML_EmitString(tab_buffer, space_length,
							tab_setting, buffer_ptr, error_text)) !=
							KMLFUNCS_SUCCESS)
							goto EXIT_FUNCTION;
						space_count -= space_length;
					}     
				}
			}
			else {
				if (strnvacat(buffer_ptr, 1, in_ptr, NULL) == NULL) {
					STR_AllocMsgItem(strlen(*buffer_ptr)  + 1, error_text,
					"Unable to expand a string by an additional 1 byte");
					return_code = KMLFUNCS_MEMORY_FAILURE;
					break;
				}
				current_col++;
			}
			in_ptr++;               
			in_length--;
		}
	}

EXIT_FUNCTION:

	return(return_code);
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
	int               return_code;
	unsigned int      count_1;
	unsigned int      count_2;
	KML_CONTROL       control_data;
	const KML_DOMAIN *domain_ptr;
	const char       *file_type;
	char             *file_buffer;
	char             *tmp_buffer;
	char             *tmp_ptr_1;
	char             *tmp_ptr_2;
	char              error_text[KMLFUNCS_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'KML_OutputString()'\n");
	fprintf(stderr, "---- ------- --- --------------------\n\n");

	if (argc == 1) {
		sprintf(error_text, "USAGE:\n   %s <source-file> [<source-file> ...]",
			argv[0]);
		return_code = KMLFUNCS_BAD_ARGS_FAILURE;
	}
	else if ((return_code = KML_TEST_InitializeControl(&control_data,
		error_text)) == KMLFUNCS_SUCCESS) {
		for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
			if (((file_type = strrchr(argv[count_1], '.')) != NULL) &&
				*file_type)
				fprintf(stderr, "File: %s (using extension '%s')",
					argv[count_1], ++file_type);
			else
				fprintf(stderr, "File: %s (no extension, using '%s')",
					argv[count_1], file_type = "c");
			if ((domain_ptr = KML_FIND_ControlDomainByType(&control_data,
				file_type)) == NULL)
				fprintf(stderr,
					": Unable to locate a domain for file extension '%s'.",
					file_type);
			else
				fprintf(stderr, ": Found domain name '%s', description '%s'.\n",
					domain_ptr->domain_name, domain_ptr->domain_description);
			if ((return_code = KML_TFREAD_ReadFileBuffer(argv[count_1], NULL,
				&file_buffer, error_text)) != KMLFUNCS_SUCCESS)
				break;
			if ((domain_ptr != NULL) && ((return_code =
				KML_MatchAll(&control_data, domain_ptr, file_buffer,
				KML_TYPE_MASK, error_text)) != KMLFUNCS_SUCCESS))
				break;
			if ((return_code = KML_OutputString(&control_data, UINT_MAX,
				file_buffer, &tmp_buffer, error_text)) != KMLFUNCS_SUCCESS) {
				fprintf(stderr, "String re-build failed for file '%s'.\n",
					argv[count_1]);
				break;
			}
			else {
				if (strlen(file_buffer) != strlen(tmp_buffer)) {
					STR_EMIT_CharLine('=', 78, NULL, NULL);
					printf("File              : %s\n", argv[count_1]);
					printf("Length differences: %u / %u\n",
						strlen(file_buffer), strlen(tmp_buffer));
					STR_EMIT_CharLine('=', 78, NULL, NULL);
				}
				if (strcmp(file_buffer, tmp_buffer)) {
					for (count_2 = 0, tmp_ptr_1 = file_buffer,
						tmp_ptr_2 = tmp_buffer;
						*tmp_ptr_1 && *tmp_ptr_2 && (*tmp_ptr_1 == *tmp_ptr_2);
						count_2++, tmp_ptr_1++, tmp_ptr_2++)
						;
					STR_EMIT_CharLine('=', 78, NULL, NULL);
					printf("File               : %s\n", argv[count_1]);
					printf("Content differences: at offset %u\n", count_2);
					STR_EMIT_CharLine('=', 78, NULL, NULL);
					printf("%s", tmp_ptr_1);
					STR_EMIT_CharLine('-', 78, NULL, NULL);
					printf("%s", tmp_ptr_2);
					STR_EMIT_CharLine('=', 78, NULL, NULL);
				}
				free(tmp_buffer);
			}
			free(file_buffer);
			KML_ClearMatchList(&control_data);
		}              
		KML_FREE_Control(&control_data);
	}

	if (return_code != KMLFUNCS_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */


