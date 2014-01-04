/*T=3*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLB Executable Module Source File													*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Searches for a 32-bit binary value within a file.

	Revision History	:	1989-02-17 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1989 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Required include files . . .															*/
/*	***********************************************************************	*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <strfuncs.h>
#include <genfuncs.h>
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#define QUANFIND_BLOCK_SIZE				8192
/*	***********************************************************************	*/

/*	***********************************************************************	*/
COMPAT_FN_DECL(int main,
	(int argc, char **argv));
COMPAT_FN_DECL_STATIC(int QUANFIND_Find,
	(const char *file_name, unsigned long quantity_long, char *error_text));
COMPAT_FN_DECL_STATIC(int QUANFIND_OpenFile,
	(const char *file_name, FILE **file_ptr, unsigned long *file_size,
	char *error_text));
COMPAT_FN_DECL_STATIC(int QUANFIND_ReadBlock,
	(FILE *file_ptr, unsigned long file_size, unsigned long file_offset,
	unsigned int *block_length, char *block_ptr));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int *max_flag_ptr;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifdef __MSDOS__
COMPAT_EXTERN_DATA_DECL unsigned int _stklen = 16384;
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
	int           return_code = GENFUNCS_SUCCESS;
	unsigned long quantity_long;
	unsigned int  count_1;
	char          error_text[GENFUNCS_MAX_ERROR_TEXT];

	if (argc < 3) {
		sprintf(error_text,
			"Expected %-.500s <quantity> <file-name> [<file-name> ...]",
			extract_file_name(argv[0]));
		return_code = GENFUNCS_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}

/*
	if ((str_digit(argv[1], 0) != NULL) ||
		(atof(argv[1]) < 0) || (atof(argv[1]) > ((double) ULONG_MAX))) {
		sprintf(error_text, "%s 0 to %lu, inclusive.",
			"Expected a numeric quantity in the range of", ULONG_MAX);
		return_code = GENFUNCS_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}
	quantity_long = ((unsigned long) atof(argv[1]));
*/

	if ((atof(argv[1]) < 0) || (atof(argv[1]) > ((double) ULONG_MAX))) {
		sprintf(error_text, "%s 0 to %lu, inclusive.",
			"Expected a numeric quantity in the range of", ULONG_MAX);
		return_code = GENFUNCS_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}
	quantity_long = strtoul(argv[1], NULL, 0);

	for (count_1 = 2; count_1 < ((unsigned int) argc); count_1++) {
		fprintf(stderr, "File Name: %s\n", argv[count_1]);
		if ((return_code = QUANFIND_Find(argv[count_1], quantity_long,
			error_text)) != GENFUNCS_SUCCESS)
			break;
	}

EXIT_FUNCTION:

	if (return_code != GENFUNCS_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int QUANFIND_Find(const char *file_name, unsigned long quantity_long,
	char *error_text)
#else
static int QUANFIND_Find(file_name, quantity_long, error_text)
const char    *file_name;
unsigned long  quantity_long;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code  = GENFUNCS_SUCCESS;
	FILE          *file_ptr     = NULL;
	unsigned long  file_size    = 0L;
	unsigned long  file_offset  = 0L;
	char          *block_ptr    = NULL;
	unsigned int   block_length = 0;
	unsigned int   found_length = 0;
	unsigned int   tmp_offset;
	char          *found_ptr;
	unsigned int   tmp_block_length;
	char          *tmp_block_ptr;
	unsigned int   quantity_int;
	unsigned int   quantity_size;
	char           quantity_data[sizeof(unsigned long)];

	if ((return_code = QUANFIND_OpenFile(file_name, &file_ptr, &file_size,
		error_text)) == GENFUNCS_SUCCESS) {
		if (file_size) {
			if ((block_ptr =
				((char *) malloc(QUANFIND_BLOCK_SIZE * sizeof(char)))) != NULL) {
				STR_EMIT_CharLine('=', 78, NULL, NULL);
				printf("File '%s': %lu bytes\n", file_name, file_size);
				printf("*** Searching for quantity %10lu (%08lX)\n",
					quantity_long, quantity_long);
				STR_EMIT_CharLine('-', 78, NULL, NULL);
				if (quantity_long > ((unsigned long) UINT_MAX)) {
					quantity_size = sizeof(quantity_long);
					memcpy(quantity_data, &quantity_long, quantity_size);
				}
				else {
					quantity_int  = ((unsigned int) quantity_long);
					quantity_size = sizeof(quantity_int);
					memcpy(quantity_data, &quantity_int, quantity_size);
				}
				while ((QUANFIND_ReadBlock(file_ptr, file_size, file_offset,
					&block_length, block_ptr) == GENFUNCS_TRUE) &&
					(block_length >= quantity_size)) {
					tmp_block_length = block_length;
					tmp_block_ptr    = block_ptr;
					if (!found_length) {
						while ((found_ptr = ((char *) memmem(tmp_block_length,
							tmp_block_ptr, quantity_size, quantity_data))) != NULL) {
							tmp_offset = ((unsigned int) (found_ptr - block_ptr));
							printf(">>> Found %10lu (%08lX) at offset %10lu (%08lX)\n",
								quantity_long, quantity_long,
								file_offset + ((unsigned long) tmp_offset),
								file_offset + ((unsigned long) tmp_offset));
							tmp_block_length = block_length -
								((unsigned int) (found_ptr - block_ptr));
							tmp_block_ptr    = found_ptr + 1;
						}
					}
/*
					else {
					}
*/
					file_offset += ((unsigned long) block_length);
					if (block_length == QUANFIND_BLOCK_SIZE)
						file_offset -= ((unsigned long) (quantity_size - 1));
				}
				STR_EMIT_CharLine('=', 78, NULL, NULL);
				free(block_ptr);
			}
			else {
				STR_AllocMsgItem(QUANFIND_BLOCK_SIZE, error_text,
					"Unable to allocate the file read block: ");
				return_code = GENFUNCS_MEMORY_FAILURE;
			}
		}
		fclose(file_ptr);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int QUANFIND_OpenFile(const char *file_name, FILE **file_ptr,
	unsigned long *file_size, char *error_text)
#else
static int QUANFIND_OpenFile(file_name, file_ptr, file_size, error_text)
const char     *file_name;
FILE          **file_ptr;
unsigned long  *file_size;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = GENFUNCS_SUCCESS;

	*file_ptr = NULL;

	if ((*file_ptr = fopen(file_name, "r+b")) == NULL) {
		sprintf(error_text, "Unable to open file '%-.500s' --- ", file_name);
		GEN_AppendLastErrorString(0, GENFUNCS_MAX_ERROR_TEXT, error_text);
		return_code = GENFUNCS_SYSTEM_FAILURE;
	}
	else {
		fseek(*file_ptr, 0L, SEEK_END);
		*file_size = ftell(*file_ptr);
		fseek(*file_ptr, 0L, SEEK_SET);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int QUANFIND_ReadBlock(FILE *file_ptr, unsigned long file_size,
	unsigned long file_offset, unsigned int *block_length, char *block_ptr)
#else
static int QUANFIND_ReadBlock(file_ptr, file_size, file_offset, block_length,
	block_ptr)
FILE          *file_ptr;
unsigned long  file_size;
unsigned long  file_offset;
unsigned int  *block_length;
char          *block_ptr;
#endif /* #ifndef NARGS */
{
	int return_flag = GENFUNCS_FALSE;

	if (file_size > file_offset) {
		fseek(file_ptr, 0L, SEEK_SET);
		fseek(file_ptr, file_offset, SEEK_SET);
		*block_length =
			((file_size - file_offset) >= ((unsigned int) QUANFIND_BLOCK_SIZE)) ?
			QUANFIND_BLOCK_SIZE : ((unsigned int) (file_size - file_offset));
		fread(block_ptr, 1, QUANFIND_BLOCK_SIZE, file_ptr);
		return_flag = GENFUNCS_TRUE;
	}
	else
		*block_length = 0;

	return(return_flag);
}
/*	***********************************************************************	*/

