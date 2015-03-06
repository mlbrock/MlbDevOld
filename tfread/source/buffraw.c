/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	TFREAD Text File Reading Functions Library Source Module						*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Reads raw buffers.

	Revision History	:	1991-04-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1991 - 2015.
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
#include <string.h>

#include <genfuncs.h>

#include "tfreadi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int TFREAD_ReadBufferRaw(const char *file_name, unsigned int *buffer_length,
	char **buffer_ptr, char *error_text)
#else
int TFREAD_ReadBufferRaw(file_name, buffer_length, buffer_ptr, error_text)
const char    *file_name;
unsigned int  *buffer_length;
char         **buffer_ptr;
char          *error_text;
#endif /* #ifndef NARGS */
{
	return(TFREAD_ReadBufferRawFILE(file_name, buffer_length, buffer_ptr,
		error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int TFREAD_ReadBufferRawBasic(const STR_CFILE_FUNCS *tfread_ptr, const char *file_name,
	unsigned int *buffer_length, char **buffer_ptr, char *error_text)
#else
int TFREAD_ReadBufferRawBasic(tfread_ptr, file_name, buffer_length,
	buffer_ptr, error_text)
const STR_CFILE_FUNCS  *tfread_ptr;
const char    *file_name;
unsigned int  *buffer_length;
char         **buffer_ptr;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code   = TFREAD_BAD_ARGS_FAILURE;
	char          *tmp_file_name = NULL;
	unsigned long  file_size;
	unsigned int   actual_count;
	void          *file_ptr;
	char           gen_error_text[GENFUNCS_MAX_ERROR_TEXT];

	if (buffer_length != NULL)
		*buffer_length = 0;

	*buffer_ptr = NULL;

	if (tfread_ptr == NULL)
		strcpy(error_text, "The 'TFREAD' pointer is 'NULL'.");
	else if (tfread_ptr->fopen_func == NULL)
		strcpy(error_text, "The 'fopen()' equivalent was not specified.");
	else if (tfread_ptr->fclose_func == NULL)
		strcpy(error_text, "The 'fclose()' equivalent was not specified.");
	else if (tfread_ptr->fread_func == NULL)
		strcpy(error_text, "The 'fread()' equivalent was not specified.");
	else if (tfread_ptr->fseek_func == NULL)
		strcpy(error_text, "The 'fseek()' equivalent was not specified.");
	else if (tfread_ptr->ftell_func == NULL)
		strcpy(error_text, "The 'ftell()' equivalent was not specified.");
	else if (file_name == NULL)
		strcpy(error_text, "The file name parameter is 'NULL'.");
	else if (!(*file_name))
		strcpy(error_text, "The file name parameter is an empty string.");
	else if ((return_code = GEN_ExpandToFullPathName(file_name, &tmp_file_name,
		gen_error_text)) != GENFUNCS_SUCCESS) {
		nstrcpy(error_text, gen_error_text, TFREAD_MAX_ERROR_TEXT - 1);
		return_code = TFREAD_MAP_ERROR_GEN(return_code);
	}
	else if ((file_ptr = (*tfread_ptr->fopen_func)(tmp_file_name, "rb")) ==
		NULL) {
		sprintf(error_text, "%s '%-.500s' for reading --- ",
			"Unable to open the file", tmp_file_name);
		GEN_AppendLastErrorString(0, TFREAD_MAX_ERROR_TEXT - 1, error_text);
		return_code = TFREAD_SYSTEM_FAILURE;
	}
	else {
		return_code = TFREAD_SUCCESS;
		(*tfread_ptr->fseek_func)(file_ptr, 0L, SEEK_END);
		file_size = (*tfread_ptr->ftell_func)(file_ptr);
		(*tfread_ptr->fseek_func)(file_ptr, 0L, SEEK_SET);
		if (!file_size) {
			if (buffer_length != NULL)
				*buffer_length = ((unsigned int) file_size);
		}
		else {
#ifdef __MSDOS__
			if (file_size > (((unsigned long) USHRT_MAX) - 16L))  {
				sprintf(error_text, "%s '%-.500s' --- %s (%lu), maximum is %lu.",
					"Unable to allocate memory for a buffered copy of the file",
					tmp_file_name, "the file size is too large", file_size,
					((unsigned long) USHRT_MAX) - 16L);
				return_code = TFREAD_MEMORY_FAILURE;
			}
			else if ((*buffer_ptr = calloc(((unsigned int) file_size) + 1,
				sizeof(char))) == NULL) {
				STR_AllocMsgItem(((unsigned int) file_size) + 1, error_text,
					"%s '%-.500s'",
					"Unable to allocate memory for a buffered copy of the file",
					tmp_file_name);
				return_code = TFREAD_MEMORY_FAILURE;
			}
#else
			if ((*buffer_ptr = ((char *) calloc(((unsigned int) file_size) + 1,
				sizeof(char)))) == NULL) {
				STR_AllocMsgItem(((unsigned int) file_size) + 1, error_text,
					"%s '%-.500s'",
					"Unable to allocate memory for a buffered copy of the file",
					tmp_file_name);
				return_code = TFREAD_MEMORY_FAILURE;
			}
#endif /* #ifdef __MSDOS__ */
			else if ((actual_count = (*tfread_ptr->fread_func)(*buffer_ptr,
				sizeof(char), ((unsigned int) file_size), file_ptr)) !=
				((unsigned int) file_size)) {
				free(*buffer_ptr);
				*buffer_ptr = NULL;
				sprintf(error_text,
					"%s %lu %s %u %s '%-.500s' %s %lu (%u %s): ",
					"Error occurred while attempting to read", file_size,
					"blocks of size", sizeof(char),
					"from the file", tmp_file_name, "at offset",
					(*tfread_ptr->ftell_func)(file_ptr), actual_count,
					"blocks were read");
				GEN_AppendLastErrorString(0, TFREAD_MAX_ERROR_TEXT - 1,
					error_text);
				return_code = TFREAD_SYSTEM_FAILURE;
			}
			else if (buffer_length != NULL)
				*buffer_length = ((unsigned int) file_size);
		}
		(*tfread_ptr->fclose_func)(file_ptr);
	}

	if (tmp_file_name != NULL)
		free(tmp_file_name);

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

COMPAT_FN_DECL(int main, (int argc, char **argv));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int           return_code;
	unsigned int  count_1;
	unsigned int  buffer_length_1 = 0;
	char         *buffer_ptr_1    = NULL;
	unsigned int  buffer_length_2 = 0;
	char         *buffer_ptr_2    = NULL;
	char          error_text[TFREAD_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'TFREAD_ReadBufferRaw()'\n");
	fprintf(stderr, "                 'TFREAD_ReadBufferRawMFILE()'\n");
	fprintf(stderr, "---- ------- --- -----------------------------\n\n");

	if (argc == 1) {
		sprintf(error_text, "USAGE:\n   %s <text-file> [<text-file> ...]",
			argv[0]);
		return_code = TFREAD_BAD_ARGS_FAILURE;
	}
	else {
		return_code = TFREAD_SUCCESS;
		for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
			fprintf(stderr, "File: %s", argv[count_1]);
			if ((return_code = TFREAD_ReadBufferRaw(argv[count_1],
				&buffer_length_1, &buffer_ptr_1, error_text)) != TFREAD_SUCCESS)
				break;
			fprintf(stderr, " --- first load");
			if ((return_code = TFREAD_ReadBufferRawMFILE(argv[count_1],
				&buffer_length_2, &buffer_ptr_2, error_text)) != TFREAD_SUCCESS)
				break;
			fprintf(stderr, " --- second load");
			if (buffer_length_1 != buffer_length_2)
				fprintf(stderr, " --- lengths differ (%u versus %u).",
					buffer_length_1, buffer_length_2);
			else if (buffer_length_1 &&
				(memcmp(buffer_ptr_1, buffer_ptr_2, buffer_length_1)))
				fprintf(stderr, " --- contents differ.");
			else
				fprintf(stderr, " --- OK.");
			if (buffer_ptr_1 != NULL)
				free(buffer_ptr_1);
			buffer_ptr_1 = NULL;
			if (buffer_ptr_2 != NULL)
				free(buffer_ptr_2);
			buffer_ptr_2 = NULL;
			fprintf(stderr, "\n");
		}
	}

	if (buffer_ptr_1 != NULL)
		free(buffer_ptr_1);
	if (buffer_ptr_2 != NULL)
		free(buffer_ptr_2);

	if (return_code != TFREAD_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

