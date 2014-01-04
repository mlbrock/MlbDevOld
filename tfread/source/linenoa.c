/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	TFREAD Text File Reading Functions Library Source Module						*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Reads lines from a file without per-line allocation.

	Revision History	:	1991-04-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1991 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include "tfreadi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int TFREAD_ReadLinesNoAlloc(const char *file_name, unsigned int *line_count,
	char ***line_list, char *error_text)
#else
int TFREAD_ReadLinesNoAlloc(file_name, line_count, line_list, error_text)
const char     *file_name;
unsigned int   *line_count;
char         ***line_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	return(TFREAD_ReadLinesNoAllocFILE(file_name, line_count, line_list,
		error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int TFREAD_ReadLinesNoAllocBasic(const STR_CFILE_FUNCS *tfread_ptr,
	const char *file_name, unsigned int *line_count, char ***line_list,
	char *error_text)
#else
int TFREAD_ReadLinesNoAllocBasic(tfread_ptr, file_name, line_count,
	line_list, error_text)
const STR_CFILE_FUNCS   *tfread_ptr;
const char     *file_name;
unsigned int   *line_count;
char         ***line_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code;
	unsigned int   buffer_length;
	char          *buffer_ptr;
	unsigned int   alloced_line_count;
	unsigned int   eol_char_count;
	char          *tmp_ptr;
	char         **tmp_list;

	*line_count = 0;
	*line_list  = NULL;

	if (((return_code = TFREAD_ReadBufferRawBasic(tfread_ptr, file_name,
		&buffer_length, &buffer_ptr, error_text)) == TFREAD_SUCCESS) &&
		buffer_length) {
		if ((*line_list = ((char **) calloc(TFREAD_LINE_ALLOC_GRAN,
			sizeof(char *)))) == NULL) {
			STR_AllocMsgList(TFREAD_LINE_ALLOC_GRAN, sizeof(char *), error_text,
				"%s '%-.500s'",
				"Unable to allocate the list of pointers to lines for file",
				file_name);
			return_code = TFREAD_MEMORY_FAILURE;
		}
		else {
			alloced_line_count            = TFREAD_LINE_ALLOC_GRAN;
			tmp_ptr                       = buffer_ptr;
			(*line_list)[(*line_count)++] = tmp_ptr;
			while (buffer_length) {
				if (!(*tmp_ptr)) {
					*tmp_ptr++ = ' ';
					buffer_length--;
				}
				else if (STRFUNCS_CHAR_IS_EOL_CHAR(*tmp_ptr)) {
					eol_char_count = (STRFUNCS_CHAR_IS_EOL_CHAR(tmp_ptr[1]) &&
						(*tmp_ptr != tmp_ptr[1])) ? 2 : 1;
					buffer_length -= eol_char_count;
					while (eol_char_count--)
						*tmp_ptr++ = '\0';
					if (!buffer_length)
						break;
					if (*line_count == alloced_line_count) {
						if ((tmp_list = ((char **) realloc(*line_list,
							(alloced_line_count + TFREAD_LINE_ALLOC_GRAN) *
							sizeof(char *)))) == NULL) {
							free(*line_list);
							*line_count = 0;
							*line_list  = NULL;
							STR_AllocMsgList(alloced_line_count +
								TFREAD_LINE_ALLOC_GRAN, sizeof(char *), error_text,
								"%s '%-.500s'",
					"Unable to re-allocate the list of pointers to lines for file",
								file_name);
							return_code = TFREAD_MEMORY_FAILURE;
							break;
						}
						alloced_line_count += TFREAD_LINE_ALLOC_GRAN;
						*line_list          = tmp_list;
					}
					(*line_list)[(*line_count)++] = tmp_ptr;
				}
				else {
					tmp_ptr++;
					buffer_length--;
				}
			}
			if ((return_code == TFREAD_SUCCESS) &&
				(*line_count < alloced_line_count))
				*line_list = ((char **) realloc(*line_list,
					*line_count * sizeof(char *)));
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <stdio.h>

#include <sdtif.h>

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
	unsigned int   uniq_count_1;
	unsigned int  *uniq_list_1;
	unsigned int   uniq_count_2;
	unsigned int  *uniq_list_2;
	unsigned int   diff_count;
	unsigned int  *diff_list;
	unsigned int   same_count;
	unsigned int  *same_list;
	char           error_text[TFREAD_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'TFREAD_ReadLinesNoAlloc()'\n");
	fprintf(stderr, "                 'TFREAD_ReadLinesNoAllocMFILE()'\n");
	fprintf(stderr, "                 'TFREAD_ReadLinesNoAllocBasic()'\n");
	fprintf(stderr, "---- ------- --- --------------------------------\n\n");

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
			fprintf(stderr, " --- second load\n");
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
			strl_remove_all(&line_count_1, &line_list_1);
			free(*line_list_2);
			free(line_list_2);
			line_list_2 = NULL;
		}
	}

	strl_remove_all(&line_count_1, &line_list_1);
	if (line_list_2 != NULL) {
		free(*line_list_2);
		free(line_list_2);
	}

	if (return_code != TFREAD_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

