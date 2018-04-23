/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Reads a source file.

	Revision History	:	1995-04-27 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2018.
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

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define ADF_READ_SRC_MAX_BLOCK			65280L

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(int ADF_ReadSourceBuffer,
	(const char *file_name, unsigned long *buffer_length,
	ADF_BIG_char **buffer_ptr, char *error_text));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_ReadSourceFile(const char *file_name, unsigned int *line_count,
	char ***line_list, ADF_BIG_char **buffer_ptr, char *error_text)
#else
int ADF_ReadSourceFile(file_name, line_count, line_list, buffer_ptr,
	error_text)
const char      *file_name;
unsigned int    *line_count;
char          ***line_list;
ADF_BIG_char   **buffer_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code;
	unsigned int   in_lines = 1;
	unsigned long  tmp_buffer_length_1;
	unsigned long  tmp_buffer_length_2;
	ADF_BIG_char  *tmp_ptr_1;
	ADF_BIG_char  *tmp_ptr_2;

	*line_count = 0;
	*line_list  = NULL;

	if (((return_code = ADF_ReadSourceBuffer(file_name, &tmp_buffer_length_1,
		buffer_ptr, error_text)) == ADF_SUCCESS) && tmp_buffer_length_1) {
		tmp_buffer_length_2 = tmp_buffer_length_1;
		tmp_ptr_1           = *buffer_ptr;
		while (tmp_buffer_length_2) {
			in_lines += (*tmp_ptr_1++ == '\n') ? 1 : 0;
			tmp_buffer_length_2--;
		}
		if ((*line_list = ((char **) malloc(in_lines * sizeof(char *)))) ==
			NULL) {
			ADF_BIG_free(*buffer_ptr);
			*buffer_ptr = NULL;
			STR_AllocMsgList(in_lines, sizeof(char *), error_text,
				"%s '%-.500s'",
				"Unable to create the line pointer list from file", file_name);
			return_code = ADF_MEMORY_FAILURE;
		}
		else {
			/*	*****************************************************	*/
			/*	*****************************************************	*/
			/*		Clean ADF special formatting characters from the	*/
			/*	source file buffer . . .										*/
			/*	*****************************************************	*/
			tmp_ptr_1 = *buffer_ptr;
			while (*tmp_ptr_1) {
				if ((*tmp_ptr_1 == ADF_CFORMAT_MARKER_CHAR) ||
					(*tmp_ptr_1 == ADF_PFORMAT_MARKER_CHAR))
					*tmp_ptr_1 = ' ';
				tmp_ptr_1++;
			}
			/*	*****************************************************	*/
			/*	*****************************************************	*/
			/*		Set-up the array of pointers to the lines in the	*/
			/*	source file . . .													*/
			/*	*****************************************************	*/
			tmp_ptr_1 = *buffer_ptr;
			while (*tmp_ptr_1) {
				(*line_list)[(*line_count)++] = ((char *) tmp_ptr_1);
				if ((tmp_ptr_2 = strchr(((char *) tmp_ptr_1), '\n')) != NULL) {
					/*	*****************************************	*/
					/*	*****************************************	*/
					/*		Get rid of the MS-DOS CR-LF ('\r\n')	*/
					/*	line termination sequence . . .				*/
					/*	*****************************************	*/
					if ((tmp_ptr_2 > *buffer_ptr) && ((*(tmp_ptr_2 - 1)) == '\r'))
						tmp_ptr_2[-1] = '\0';
					/*	*****************************************	*/
					*tmp_ptr_2 = '\0';
					tmp_ptr_1  = tmp_ptr_2 + 1;
				}
				else
					break;
			}
			/*	*****************************************************	*/
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_ReadSourceBuffer(const char *file_name,
	unsigned long *buffer_length, ADF_BIG_char **buffer_ptr, char *error_text)
#else
static int ADF_ReadSourceBuffer(file_name, buffer_length, buffer_ptr,
	error_text)
const char     *file_name;
unsigned long  *buffer_length;
ADF_BIG_char  **buffer_ptr;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code = ADF_SUCCESS;
	unsigned long  file_size;
	ADF_FILE      *file_ptr;

#ifdef __MSDOS__
	unsigned long  read_file_size;
	unsigned long  tmp_file_size;
	ADF_BIG_char  *tmp_buffer_ptr;
#else
	unsigned int   count_1;
#endif /* #ifdef __MSDOS__ */

	if (buffer_length != NULL)
		*buffer_length = 0L;

	*buffer_ptr = NULL;

	if ((file_ptr = ADF_fopen(file_name, "rb")) == NULL) {
		sprintf(error_text, "%s '%-.500s' for reading --- ",
			"Unable to open the file", file_name);
		ADF_GetLastErrorString(error_text);
		return_code = ADF_FAILURE;
	}
	else {
		ADF_fseek(file_ptr, 0L, SEEK_END);
		file_size = ADF_ftell(file_ptr);
		ADF_fseek(file_ptr, 0L, SEEK_SET);
		if (file_size) {
#ifdef __MSDOS__
			if ((*buffer_ptr = ADF_BIG_calloc(file_size + 1L,
				((unsigned long) sizeof(char)))) == NULL) {
				sprintf(error_text, "%s '%-.500s' --- %lu bytes required",
					"Unable to allocate memory for a buffered copy of the file",
					file_name, file_size);
				return_code = ADF_MEMORY_FAILURE;
			}
			else {
				tmp_file_size  = file_size;
				tmp_buffer_ptr = *buffer_ptr;
				while (tmp_file_size) {
					read_file_size = (tmp_file_size > ADF_READ_SRC_MAX_BLOCK) ?
						ADF_READ_SRC_MAX_BLOCK : tmp_file_size;
					if ((return_code = ADF_FRead(tmp_buffer_ptr, sizeof(char),
						((unsigned int) read_file_size), file_ptr, error_text)) !=
						ADF_SUCCESS) {
						ADF_BIG_free(*buffer_ptr);
						*buffer_ptr = NULL;
						break;
					}
					tmp_file_size  -= read_file_size;
					tmp_buffer_ptr += ((unsigned int) read_file_size);
				}
				if (return_code == ADF_SUCCESS) {
            	*buffer_length = file_size;
					tmp_file_size  = file_size;
					tmp_buffer_ptr = *buffer_ptr;
					while (tmp_file_size) {
						if (!(*tmp_buffer_ptr))
							*tmp_buffer_ptr = ' ';
						tmp_file_size--;
						tmp_buffer_ptr++;
					}
					(*buffer_ptr)[file_size] = '\0';
				}
			}
#else
			if ((*buffer_ptr = ((char *) calloc(((unsigned int) file_size) + 1,
				sizeof(char)))) == NULL) {
				sprintf(error_text, "%s '%-.500s' --- %lu bytes required",
					"Unable to allocate memory for a buffered copy of the file",
					file_name, file_size);
				return_code = ADF_MEMORY_FAILURE;
			}
			else if ((return_code = ADF_FRead(*buffer_ptr, sizeof(char),
				((unsigned int) file_size), file_ptr, error_text)) !=
				ADF_SUCCESS) {
				free(*buffer_ptr);
				*buffer_ptr = NULL;
			}
			else {
				for (count_1 = 0; count_1 < ((unsigned int) file_size); count_1++)
					(*buffer_ptr)[count_1] = ((char) ((!(*buffer_ptr)[count_1]) ?
						((char) ' ') : (*buffer_ptr)[count_1]));
				if (buffer_length != NULL)
					*buffer_length = file_size;
			}
#endif /* #ifdef __MSDOS__ */
		}
		ADF_fclose(file_ptr);
	}

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#ifdef __MSDOS__
COMPAT_EXTERN_DATA_DECL unsigned int _stklen = 16384;
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
	int            return_code = ADF_SUCCESS;
	unsigned int   line_count  = 0;
	char         **line_list   = NULL;
	ADF_BIG_char  *line_buffer = NULL;
	unsigned int   count_1;
  	unsigned int   count_2;
	char           error_text[ADF_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for function 'ADF_ReadSourceFile()'\n");
	fprintf(stderr, "---- ------- --- -------- ----------------------\n\n");

	if (argc < 2) {
		fprintf(stderr,
			"USAGE:\n   %s <source-file-name> [<source-file-name>...]\n",
			argv[0]);
		return_code = ADF_BAD_ARGS_FAILURE;
	}
	else {
		for (count_1 = 1; count_1 < argc; count_1++) {
			fprintf(stderr, "File: %s", argv[count_1]);
			if ((return_code = ADF_ReadSourceFile(argv[1], &line_count,
				&line_list, &line_buffer, error_text)) != ADF_SUCCESS)
				break;
			for (count_2 = 0; count_2 < line_count; count_2++)
				printf("%s\n", line_list[count_2]);
			if (line_list != NULL)
				free(line_list);
			if (line_buffer != NULL)
				ADF_BIG_free(line_buffer);
			fprintf(stderr, "\n");
		}
	}

	if (return_code != ADF_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

