/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLB Executable Module Source File													*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Performs word/line/character counts of text files.

	Revision History	:	2001-12-07 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2001 - 2018.
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
#include <stdlib.h>
#include <string.h>

#include <strfuncs.h>
#include <genfuncs.h>
#include <tfread.h>

#ifdef _Windows
# include <io.h>
# include <fcntl.h>
#endif /* #ifdef _Windows */

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#define XWC_FLAG_NONE			0
#define XWC_FLAG_CHAR			1
#define XWC_FLAG_LINE			2
#define XWC_FLAG_WORD			4
#define XWC_FLAG_ALL				(XWC_FLAG_CHAR | XWC_FLAG_LINE | XWC_FLAG_WORD)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#define XWC_STDIN_ALLOC_SIZE	32768
#define XWC_STDIN_READ_SIZE	 8092		// Must be less than XWC_STDIN_ALLOC_SIZE
/*	***********************************************************************	*/

/*	***********************************************************************	*/
COMPAT_FN_DECL(int main,
	(int argc, char **argv));
	/*	*****************************************************************	*/
COMPAT_FN_DECL_STATIC(int  GetWCFlags,
	(const char *in_string, int *count_flags, char *error_text));
COMPAT_FN_DECL_STATIC(int  ReadStdIn,
	(unsigned int *buffer_length, char **buffer_ptr, char *error_text));
COMPAT_FN_DECL_STATIC(void DoWCCounts,
	(const char *file_name, unsigned int buffer_length, const char *buffer_ptr,
	int count_flags, unsigned int *total_lines, unsigned int *total_words,
	unsigned int *total_chars));
COMPAT_FN_DECL_STATIC(void ShowWCCounts,
	(const char *file_name, int count_flags, unsigned int count_lines,
	unsigned int count_words, unsigned int count_chars));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int main(int argc, char **argv)
{
	int           return_code     = EXIT_SUCCESS;
	int           count_flags     = XWC_FLAG_ALL;
	unsigned int  file_name_count = 0;
	unsigned int  total_lines     = 0;
	unsigned int  total_words     = 0;
	unsigned int  total_chars     = 0;
	unsigned int  count_1;
	unsigned int  file_name_index;
	unsigned int  buffer_length;
	char         *buffer_ptr;
	char          tfread_error_text[TFREAD_MAX_ERROR_TEXT];

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if ((!stricmp(argv[count_1], "-help")) ||
			(!stricmp(argv[count_1], "-h"))) {
			fprintf(stderr, "USAGE:\n   %s %s %s %s\n\n",
				extract_file_name(argv[0]),
				"[ -h | -help ]",
				"[ -lwc ]",
				"[ <file-name> [ <file-name> . . . ] ]");
			goto EXIT_FUNCTION;
		}
	}

	if ((argc > 1) && (argv[1][0] == '-') && (argv[1][1] != '-')) {
		if ((return_code = GetWCFlags(argv[1], &count_flags,
			tfread_error_text)) != EXIT_SUCCESS)
			goto EXIT_FUNCTION;
		file_name_index = 2;
	}
	else
		file_name_index = 1;

	if (file_name_index >= ((unsigned int) argc)) {
		if (ReadStdIn(&buffer_length, &buffer_ptr, tfread_error_text) !=
			TFREAD_SUCCESS) {
			return_code = EXIT_FAILURE;
			goto EXIT_FUNCTION;
		}
		DoWCCounts(NULL, buffer_length, buffer_ptr, count_flags,
			&total_lines, &total_words, &total_chars);
		free(buffer_ptr);
	}
	else {
		for (count_1 = file_name_index; count_1 < ((unsigned int) argc);
			count_1++) {
			if (TFREAD_ReadBufferRaw(argv[count_1], &buffer_length,
				&buffer_ptr, tfread_error_text) == TFREAD_SUCCESS) {
				DoWCCounts(argv[count_1], buffer_length, buffer_ptr, count_flags,
					&total_lines, &total_words, &total_chars);
				free(buffer_ptr);
			}
			else
				fprintf(stderr, "%s: %s\n", argv[count_1], tfread_error_text);
			file_name_count++;
		}
		if (file_name_count > 1)
			ShowWCCounts("total", count_flags, total_lines, total_words,
				total_chars);
	}

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static int GetWCFlags(const char *in_string, int *count_flags, char *error_text)
{
	int return_code = EXIT_SUCCESS;

	*count_flags = XWC_FLAG_NONE;

	if (!(*in_string)) {
		strcpy(error_text, "Empty wc flags parameter encountered.");
		return_code = EXIT_SUCCESS;
	}
	else {
		while (*in_string) {
			switch (*in_string) {
				case 'c'	:
					*count_flags |= XWC_FLAG_CHAR;
					break;
				case 'l'	:
					*count_flags |= XWC_FLAG_LINE;
					break;
				case 'w'	:
					*count_flags |= XWC_FLAG_WORD;
					break;
				default	:
					strcat(chrcat(strcpy(error_text,
						"Invalid wc flags parameter encountered ('"),
						*in_string), "'.");
					return_code = EXIT_FAILURE;
					break;
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static int ReadStdIn(unsigned int *buffer_length, char **buffer_ptr,
	char *error_text)
{
	int           return_code    = EXIT_SUCCESS;
	unsigned int  current_length = 0;
	char         *tmp_ptr;
	unsigned int  tmp_length;
	char          tmp_buffer[XWC_STDIN_READ_SIZE];
#ifdef _Windows
	int           old_mode;
#endif /* #ifdef _Windows */

	*buffer_length = 0;
	*buffer_ptr    = NULL;

	if ((*buffer_ptr = ((char *) calloc(XWC_STDIN_ALLOC_SIZE,
		sizeof(char)))) == NULL) {
		STR_AllocMsgItem(XWC_STDIN_ALLOC_SIZE, error_text,
			"Unable to allocate the initial 'stdin' buffer");
		return_code = EXIT_FAILURE;
	}
#ifdef _Windows
	else if ((old_mode = setmode(fileno(stdin), _O_BINARY)) == -1) {
		sprintf(error_text, "%s (handle = %d) to binary mode (%d) --- ",
			"Unable to 'setmode()' 'stdin'", fileno(stdin), _O_BINARY);
		GEN_AppendLastErrorString(0, TFREAD_MAX_ERROR_TEXT - 1, error_text);
		return_code = EXIT_FAILURE;
	}
#endif /* #ifdef _Windows */
	else {
		*buffer_length = XWC_STDIN_ALLOC_SIZE;
		do {
			*tmp_buffer = '\0';
			fgets(tmp_buffer, sizeof(tmp_buffer) - 1, stdin);
			if (ferror(stdin)) {
				strcpy(error_text, "Error occurred reading from 'stdin'.");
				return_code = EXIT_FAILURE;
				break;
			}
			if ((tmp_length = strlen(tmp_buffer)) > 0) {
				if ((current_length + tmp_length) >= *buffer_length) {
					if ((tmp_ptr = ((char *) realloc(*buffer_ptr,
						*buffer_length + XWC_STDIN_ALLOC_SIZE))) == NULL) {
						STR_AllocMsgItem(*buffer_length + XWC_STDIN_ALLOC_SIZE,
							error_text, "Unable to re-allocate the 'stdin' buffer");
						return_code = EXIT_FAILURE;
						break;
					}
					*buffer_length += XWC_STDIN_ALLOC_SIZE;
					*buffer_ptr     = tmp_ptr;
				}
				memcpy(*buffer_ptr + current_length, tmp_buffer, tmp_length + 1);
				current_length += tmp_length;
			}
		} while (!feof(stdin));
#ifdef _Windows
		if ((old_mode = setmode(fileno(stdin), old_mode)) == -1) {
			sprintf(error_text, "%s (handle = %d) to its old mode (%d) --- ",
				"Unable to 'setmode()' to restore 'stdin'", fileno(stdin),
				old_mode);
			GEN_AppendLastErrorString(0, TFREAD_MAX_ERROR_TEXT - 1, error_text);
			return_code = EXIT_FAILURE;
		}
#endif /* #ifdef _Windows */
		if (return_code == EXIT_SUCCESS)
			*buffer_length = current_length;
		else {
			if (*buffer_ptr != NULL)
				free(*buffer_ptr);
			*buffer_length = 0;
			*buffer_ptr    = NULL;
		}
	}

	if (return_code != EXIT_SUCCESS) {
		if (*buffer_ptr != NULL)
			free(*buffer_ptr);
		*buffer_length = 0;
		*buffer_ptr    = NULL;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static void DoWCCounts(const char *file_name, unsigned int buffer_length,
	const char *buffer_ptr, int count_flags, unsigned int *total_lines,
	unsigned int *total_words, unsigned int *total_chars)
{
	const char   *tmp_ptr      = buffer_ptr;
	int           in_word_flag = 0;
	unsigned int  count_lines  = 0;
	unsigned int  count_words  = 0;
	unsigned int  eol_char_count;

	while (*tmp_ptr) {
		if ((eol_char_count = STRFUNCS_STRPTR_IS_EOL(tmp_ptr)) > 0) {
			if (in_word_flag) {
				count_words++;
				in_word_flag = 0;
			}
			tmp_ptr += eol_char_count;
			count_lines++;
		}
		else if (isspace(*tmp_ptr)) {
			if (in_word_flag) {
				count_words++;
				in_word_flag = 0;
			}
			tmp_ptr++;
		}
		else {
			in_word_flag = 1;
			tmp_ptr++;
		}
	}

	if (in_word_flag)
		count_words++;

	if (total_lines != NULL)
		*total_lines += count_lines;

	if (total_words != NULL)
		*total_words += count_words;

	if (total_chars != NULL)
		*total_chars += buffer_length;

	ShowWCCounts(file_name, count_flags, count_lines, count_words,
		buffer_length);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static void ShowWCCounts(const char *file_name, int count_flags,
	unsigned int count_lines, unsigned int count_words, unsigned int count_chars)
{
	if (count_flags & XWC_FLAG_LINE)
		printf("%*u ", STR_VAL2STR_MAX_LEN_UNSIGNED_10, count_lines);

	if (count_flags & XWC_FLAG_WORD)
		printf("%*u ", STR_VAL2STR_MAX_LEN_UNSIGNED_10, count_words);

	if (count_flags & XWC_FLAG_CHAR)
		printf("%*u ", STR_VAL2STR_MAX_LEN_UNSIGNED_10, count_chars);

	printf("%s\n", (file_name != NULL) ? file_name : "");
}
/*	***********************************************************************	*/

