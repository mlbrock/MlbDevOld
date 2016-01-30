/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	TFREAD Text File Reading Functions Library Source Module						*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Reads a buffer with new-line translation.

	Revision History	:	1991-04-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1991 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <memory.h>
#include <string.h>

#include "tfreadi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int TFREAD_ReadBufferXLateNL(const char *file_name, const char *nl_string,
	unsigned int *buffer_length, char **buffer_ptr, char *error_text)
#else
int TFREAD_ReadBufferXLateNL(file_name, nl_string, buffer_length,
	buffer_ptr, error_text)
const char    *file_name;
const char    *nl_string;
unsigned int  *buffer_length;
char         **buffer_ptr;
char          *error_text;
#endif /* #ifndef NARGS */
{
	return(TFREAD_ReadBufferXLateNLFILE(file_name, nl_string, buffer_length,
		buffer_ptr, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int TFREAD_ReadBufferXLateNLBasic(const STR_CFILE_FUNCS *tfread_ptr,
	const char *file_name, const char *nl_string, unsigned int *buffer_length,
	char **buffer_ptr, char *error_text)
#else
int TFREAD_ReadBufferXLateNLBasic(tfread_ptr, file_name, nl_string,
	buffer_length, buffer_ptr, error_text)
const STR_CFILE_FUNCS  *tfread_ptr;
const char    *file_name;
const char    *nl_string;
unsigned int  *buffer_length;
char         **buffer_ptr;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code;
	unsigned int  tmp_length;
	unsigned int  nl_length;
	unsigned int  eol_char_count;
	unsigned int  buffer_eol_char_count;
	unsigned int  buffer_eol_count;
	char         *tmp_ptr;
	char         *out_ptr;
	char         *tmp_buffer_ptr;
	unsigned int  new_buffer_length;

	buffer_length = (buffer_length != NULL) ? buffer_length : &tmp_length;

	if (((return_code = TFREAD_ReadBufferBasic(tfread_ptr, file_name,
		buffer_length, buffer_ptr, error_text)) == TFREAD_SUCCESS) &&
		*buffer_length) {
		nl_length             = strlen((nl_string != NULL) ? nl_string : "");
		tmp_ptr               = *buffer_ptr;
		buffer_eol_char_count = 0;
		buffer_eol_count      = 0;
		while (*tmp_ptr) {
			if ((eol_char_count = STRFUNCS_STRPTR_IS_EOL(tmp_ptr)) > 0) {
				tmp_ptr               += eol_char_count;
				buffer_eol_char_count += eol_char_count;
				buffer_eol_count++;
			}
			else
				tmp_ptr++;
		}
		if (buffer_eol_count) {
			new_buffer_length = (*buffer_length - buffer_eol_char_count) +
				(nl_length * buffer_eol_count);
			if ((tmp_buffer_ptr = ((char *) calloc(
				new_buffer_length + 1, sizeof(char)))) == NULL) {
				STR_AllocMsgItem(new_buffer_length + 1, error_text,
					"Unable to allocate memory for a %s '%.*s'",
					"working copy of the file", 500, file_name);
				return_code = TFREAD_MEMORY_FAILURE;
				goto EXIT_FUNCTION;
			}
			tmp_ptr = *buffer_ptr;
			out_ptr = tmp_buffer_ptr;
			while (*tmp_ptr) {
				if ((eol_char_count = STRFUNCS_STRPTR_IS_EOL(tmp_ptr)) > 0) {
					memcpy(out_ptr, nl_string, nl_length);
					tmp_ptr += eol_char_count;
					out_ptr += nl_length;
				}
				else
					*out_ptr++ = *tmp_ptr++;
			}
			free(*buffer_ptr);
			*out_ptr       = '\0';
			*buffer_ptr    = tmp_buffer_ptr;
			*buffer_length = new_buffer_length;
		}
/*
		nl_length = strlen((nl_string != NULL) ? nl_string : "");
		tmp_ptr   = *buffer_ptr;
		if (!nl_length) {
			while (*tmp_ptr) {
				if ((eol_char_count = STRFUNCS_STRPTR_IS_EOL(tmp_ptr)) > 0) {
					strdele(tmp_ptr, 0, eol_char_count);
					*buffer_length -= eol_char_count;
				}
				else
					tmp_ptr++;
			}
		}
		else if (nl_length == 1) {
			while (*tmp_ptr) {
				if ((eol_char_count = STRFUNCS_STRPTR_IS_EOL(tmp_ptr)) == 1)
					*tmp_ptr++ = *nl_string;
				else if (eol_char_count == 2) {
					*tmp_ptr++ = *nl_string;
					strdele(tmp_ptr, 0, 1);
					(*buffer_length)--;
				}
				else
					tmp_ptr++;
			}
		}
		else {
			buffer_eol_char_count = 0;
			buffer_eol_count      = 0;
			while (*tmp_ptr) {
				if ((eol_char_count = STRFUNCS_STRPTR_IS_EOL(tmp_ptr)) > 0) {
					tmp_ptr               += eol_char_count;
					buffer_eol_char_count += eol_char_count;
					buffer_eol_count++;
				}
				else
					tmp_ptr++;
			}
			if (buffer_eol_count) {
				new_buffer_length = *buffer_length +
					((nl_length * buffer_eol_count) - buffer_eol_char_count);
				if ((tmp_buffer_ptr = ((char *) calloc(
					new_buffer_length + 1, sizeof(char)))) == NULL) {
					STR_AllocMsgItem(new_buffer_length + 1, error_text,
						"Unable to allocate memory for a %s '%.*s'",
						"working copy of the file", 500, file_name);
					return_code = TFREAD_MEMORY_FAILURE;
					goto EXIT_FUNCTION;
				}
				tmp_ptr = *buffer_ptr;
				out_ptr = tmp_buffer_ptr;
				while (*tmp_ptr) {
					if ((eol_char_count = STRFUNCS_STRPTR_IS_EOL(tmp_ptr)) > 0) {
						memcpy(out_ptr, nl_string, nl_length);
						out_ptr += nl_length;
					}
					else
						*out_ptr++ = *tmp_ptr++;
				}
				free(*buffer_ptr);
				*out_ptr       = '\0';
				*buffer_ptr    = tmp_buffer_ptr;
				*buffer_length = new_buffer_length;
			}
		}
*/
	}

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <stdio.h>

#include <genfuncs.h>

COMPAT_FN_DECL(int main, (int argc, char **argv));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int            return_code;
	unsigned int   count_1;
	unsigned int   count_2;
	unsigned int   line_count_1 = 0;
	char         **line_list_1  = NULL;
	unsigned int   line_count_2 = 0;
	char         **line_list_2  = NULL;
	unsigned int   line_count_3 = 0;
	char         **line_list_3  = NULL;
	unsigned int   uniq_count_1;
	unsigned int  *uniq_list_1;
	unsigned int   uniq_count_2;
	unsigned int  *uniq_list_2;
	unsigned int   diff_count;
	unsigned int  *diff_list;
	unsigned int   same_count;
	unsigned int  *same_list;
	char          *buffer_ptr;
	char           error_text[TFREAD_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'TFREAD_ReadBufferXLateNL()'\n");
	fprintf(stderr, "---- ------- --- ----------------------------\n\n");

	if (argc == 1) {
		sprintf(error_text, "USAGE:\n   %s <text-file> [<text-file> ...]",
			argv[0]);
		return_code = TFREAD_BAD_ARGS_FAILURE;
	}
	else {
		return_code = TFREAD_SUCCESS;
		for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
			fprintf(stderr, "File: %s", argv[count_1]);
			if ((return_code = TFREAD_ReadLines(argv[count_1],
				&line_count_1, &line_list_1, error_text)) != TFREAD_SUCCESS)
				break;
			fprintf(stderr, " --- first load");
			if ((return_code = TFREAD_ReadLinesNoAlloc(argv[count_1],
				&line_count_2, &line_list_2, error_text)) != TFREAD_SUCCESS)
				break;
			fprintf(stderr, " --- second load");
			if ((return_code = TFREAD_ReadBufferXLateNL(argv[count_1],
				"\r", NULL, &buffer_ptr, error_text)) != TFREAD_SUCCESS)
				break;
			fprintf(stderr, " --- third load");
			if (sepwordx_keep(buffer_ptr, "\r", &line_count_3, &line_list_3) !=
				STRFUNCS_SUCCESS) {
				STR_AllocMsgPtrList(chrcnt(buffer_ptr, '\r') + 1,
					strlen(buffer_ptr) + 1, error_text, "%s '%-.*s'",
					"Unable to allocate the list of strings representing file",
					500, argv[count_1]);
				free(buffer_ptr);
				return_code = TFREAD_MEMORY_FAILURE;
				break;
			}
			free(buffer_ptr);
			fprintf(stderr, " --- third parse\n");
			fprintf(stderr,
				"Performing delta number one (first versus second load)");
			if (strl_delta(line_count_1, line_list_1, line_count_2, line_list_2,
				&uniq_count_1, &uniq_list_1, &uniq_count_2, &uniq_list_2,
				&diff_count, &diff_list, &same_count, &same_list) !=
				STRFUNCS_SUCCESS) {
				sprintf(error_text, "Error on delta of lines for file '%-.*s'.",
					500, argv[count_1]);
				return_code = TFREAD_MEMORY_FAILURE;
				break;
			}
			fprintf(stderr, "\n");
			fprintf(stderr, "Test one delta of loaded lines");
			if (uniq_count_1 || uniq_count_2 || diff_count) {
				fprintf(stderr, " (differences encountered)\n");
				STR_EMIT_CharLine('=', 78, NULL, NULL);
				printf("File: %s TEST ONE\n", argv[count_1]);
				STR_EMIT_CharLine('=', 78, NULL, NULL);
				STR_EMIT_CharLine('=', 78, NULL, NULL);
				printf("Unique List One:\n");
				STR_EMIT_CharLine('-', 78, NULL, NULL);
				for (count_2 = 0; count_2 < uniq_count_1; count_2++)
					printf("%10u:[%s]\n", uniq_list_1[count_2],
						line_list_1[uniq_list_1[count_2]]);
				STR_EMIT_CharLine('=', 78, NULL, NULL);
				printf("Unique List Two:\n");
				STR_EMIT_CharLine('-', 78, NULL, NULL);
				for (count_2 = 0; count_2 < uniq_count_2; count_2++)
					printf("%10u:[%s]\n", uniq_list_2[count_2],
						line_list_2[uniq_list_2[count_2]]);
				STR_EMIT_CharLine('=', 78, NULL, NULL);
				printf("Diff List:\n");
				STR_EMIT_CharLine('-', 78, NULL, NULL);
				for (count_2 = 0; count_2 < diff_count; count_2++)
					printf("%10u:[%s]\n          :[%s]\n", diff_list[count_2],
						line_list_1[diff_list[count_2]],
						line_list_2[diff_list[count_2]]);
				STR_EMIT_CharLine('=', 78, NULL, NULL);
				printf("Same List:\n");
				STR_EMIT_CharLine('-', 78, NULL, NULL);
				for (count_2 = 0; count_2 < same_count; count_2++)
					printf("%10u:[%s]\n          :[%s]\n", same_list[count_2],
						line_list_1[same_list[count_2]],
						line_list_2[same_list[count_2]]);
				STR_EMIT_CharLine('=', 78, NULL, NULL);
			}
			else
				fprintf(stderr, " (no differences encountered)");
			fprintf(stderr, " --- line count = %u / %u",
				line_count_1, line_count_2);
			if (uniq_list_1 != NULL)
				free(uniq_list_1);
			if (uniq_list_2 != NULL)
				free(uniq_list_2);
			if (diff_list != NULL)
				free(diff_list);
			if (same_list != NULL)
				free(same_list);
			fprintf(stderr, "\n");
			fprintf(stderr,
				"Performing delta number one (first versus third load)");
			if (strl_delta(line_count_1, line_list_1, line_count_3, line_list_3,
				&uniq_count_1, &uniq_list_1, &uniq_count_2, &uniq_list_2,
				&diff_count, &diff_list, &same_count, &same_list) !=
				STRFUNCS_SUCCESS) {
				sprintf(error_text, "Error on delta of lines for file '%-.*s'.",
					500, argv[count_1]);
				return_code = TFREAD_MEMORY_FAILURE;
				break;
			}
			if ((line_count_1 == (line_count_3 - 1)) && (!diff_count) &&
				(!uniq_count_1) && (uniq_count_2 == 1) &&
				(uniq_list_2[uniq_count_2 - 1] == (line_count_3 - 1)) &&
				(!(*line_list_3[uniq_list_2[uniq_count_2 - 1]]))) {
				uniq_count_1 = 0;
				uniq_count_2 = 0;
				diff_count   = 0;
				strl_remove(&line_count_3, &line_list_3, line_count_3 - 1, 1);
			}
			fprintf(stderr, "\n");
			fprintf(stderr, "Test two delta of loaded lines");
			if (uniq_count_1 || uniq_count_2 || diff_count) {
				fprintf(stderr, " (differences encountered)\n");
				STR_EMIT_CharLine('=', 78, NULL, NULL);
				printf("File: %s TEST TWO\n", argv[count_1]);
				STR_EMIT_CharLine('=', 78, NULL, NULL);
				STR_EMIT_CharLine('=', 78, NULL, NULL);
				printf("Unique List One:\n");
				STR_EMIT_CharLine('-', 78, NULL, NULL);
				for (count_2 = 0; count_2 < uniq_count_1; count_2++)
					printf("%10u:[%s]\n", uniq_list_1[count_2],
						line_list_1[uniq_list_1[count_2]]);
				STR_EMIT_CharLine('=', 78, NULL, NULL);
				printf("Unique List Two:\n");
				STR_EMIT_CharLine('-', 78, NULL, NULL);
				for (count_2 = 0; count_2 < uniq_count_2; count_2++)
					printf("%10u:[%s]\n", uniq_list_2[count_2],
						line_list_3[uniq_list_2[count_2]]);
				STR_EMIT_CharLine('=', 78, NULL, NULL);
				printf("Diff List:\n");
				STR_EMIT_CharLine('-', 78, NULL, NULL);
				for (count_2 = 0; count_2 < diff_count; count_2++)
					printf("%10u:[%s]\n          :[%s]\n", diff_list[count_2],
						line_list_1[diff_list[count_2]],
						line_list_3[diff_list[count_2]]);
				STR_EMIT_CharLine('=', 78, NULL, NULL);
				printf("Same List:\n");
				STR_EMIT_CharLine('-', 78, NULL, NULL);
				for (count_2 = 0; count_2 < same_count; count_2++)
					printf("%10u:[%s]\n          :[%s]\n", same_list[count_2],
						line_list_1[same_list[count_2]],
						line_list_3[same_list[count_2]]);
				STR_EMIT_CharLine('=', 78, NULL, NULL);
			}
			else
				fprintf(stderr, " (no differences encountered)");
			fprintf(stderr, " --- line count = %u / %u\n",
				line_count_1, line_count_3);
			if (uniq_list_1 != NULL)
				free(uniq_list_1);
			if (uniq_list_2 != NULL)
				free(uniq_list_2);
			if (diff_list != NULL)
				free(diff_list);
			if (same_list != NULL)
				free(same_list);
			strl_remove_all(&line_count_1, &line_list_1);
			free(*line_list_2);
			free(line_list_2);
			line_list_2 = NULL;
			strl_remove_all(&line_count_3, &line_list_3);
		}
	}

	strl_remove_all(&line_count_1, &line_list_1);
	if (line_list_2 != NULL) {
		free(*line_list_2);
		free(line_list_2);
	}
	strl_remove_all(&line_count_3, &line_list_3);

	if (return_code != TFREAD_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

