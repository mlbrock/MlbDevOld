/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MMAP Memory-mapped Interface Library Source Code Module						*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	

	Revision History	:	1992-03-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include <string.h>

#include <genfuncs.h>

#include "mmap.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	

   SYNOPSIS    :	

   DESCRIPTION :	

   PARAMETERS  :	

   RETURNS     :	

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2014 Michael L. Brock

   OUTPUT INDEX:	
						Memory-mapped Interface Functions:See MMAP Library Functions
						MMAP Library Functions

   PUBLISH XREF:	

   PUBLISH NAME:	

	ENTRY CLASS	:	Memory-mapped Interface Functions

EOH */
/*	***********************************************************************	*/
int MMAP_Map(address, length, protect, map_flags, fd, offset, out_address,
	error_text)
void          *address;
unsigned int   length;
unsigned int   protect;
unsigned int   map_flags;
int            fd;
unsigned int   offset;
void         **out_address;
char          *error_text;
{
	int   return_code = MMAP_SUCCESS;
	void *tmp_ptr;
	char  tmp_error_text[MMAP_MAX_ERROR_TEXT];

	if (out_address == NULL) {
		if (error_text != NULL)
			strcpy(tmp_error_text,
				"Bad argument --- 'out_address' parameter is 'NULL'.");
		return_code = MMAP_BAD_ARGS_FAILURE;
	}
	else if (((address == NULL) || ((return_code =
		MMAP_CheckAddress(address, tmp_error_text))    == MMAP_SUCCESS)) &&
		 ((return_code =
		MMAP_CheckLength(length, tmp_error_text))      == MMAP_SUCCESS)  &&
		((return_code =
		MMAP_CheckProtect(protect, tmp_error_text))    == MMAP_SUCCESS)  &&
		((return_code =
		MMAP_CheckMapFlags(map_flags, tmp_error_text)) == MMAP_SUCCESS)) {
		if ((tmp_ptr = MMAP_mmap(address, length, protect, map_flags, fd,
			offset)) != ((void *) -1))
			*out_address = tmp_ptr;
		else
			return_code = MMAP_SYSTEM_FAILURE;
		if ((return_code != MMAP_SUCCESS) && (error_text != NULL))
			GEN_GetLastErrorString(0, MMAP_MAX_ERROR_TEXT, tmp_error_text);
	}

	if ((return_code != MMAP_SUCCESS) && (error_text != NULL))
		sprintf(error_text,
			"MMAP_Map(%08lX, %u, %u, %u, %d, %u, %08lX) failed: %s",
			((unsigned long) address), length, protect, map_flags, fd, offset,
			((unsigned long) error_text), tmp_error_text);

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#define MMAP_TEST_COUNT				100
#define MMAP_LOOP_COUNT				100
#define MMAP_TEST_FILE_NAME		"ERASEME.TXT"

static char TEST_ZeroBuffer[8192];

int main(argc, argv)
int    argc;
char **argv;
{
	int            return_code = MMAP_SUCCESS;
	unsigned int   test_count  = MMAP_TEST_COUNT;
	unsigned int   loop_count  = MMAP_LOOP_COUNT;
	unsigned int   mmap_count  = 0;
	void         **mmap_list   = NULL;
	unsigned long  total_size  = 0L;
	FILE          *file_ptr    = NULL;
	unsigned long  remaining_size;
	unsigned int   tmp_size;
	unsigned int   page_size;
	unsigned int   count_1;
	unsigned int   count_2;
	char           error_text[MMAP_MAX_ERROR_TEXT];
#ifdef _Windows
	HANDLE         file_handle = NULL;
	SYSTEM_INFO system_data;
#else
	int            file_handle = -1;
#endif /* #ifdef _Windows */

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if ((!stricmp(argv[count_1], "-HELP")) ||
			(!stricmp(argv[count_1], "-H"))) {
			fprintf(stderr, "\nUSAGE:\n   %s [-H[ELP] | <test-count>]\n\n",
				argv[0]);
			goto EXIT_FUNCTION;
		}
	}

	if ((argc > 1) && (atoi(argv[1]) > 0))
		test_count = ((unsigned int) atoi(argv[1]));

	if ((argc > 2) && (atoi(argv[2]) > 0))
		loop_count = ((unsigned int) atoi(argv[2]));

	page_size  = GEN_GetPageSize();
	for (count_1 = 0; count_1 < loop_count; count_1++)
		total_size += ((unsigned long) (count_1 + 1)) *
			((unsigned long) page_size);

	fprintf(stderr, "Creating backing store file '%s'",
		MMAP_TEST_FILE_NAME);
	if ((file_ptr = fopen(MMAP_TEST_FILE_NAME, "w+")) == NULL) {
		sprintf(error_text, "Unable to open test file '%s': ",
			MMAP_TEST_FILE_NAME);
		GEN_AppendLastErrorString(0, MMAP_MAX_ERROR_TEXT, error_text);
		return_code = MMAP_SYSTEM_FAILURE;
		goto EXIT_FUNCTION;
	}
	fprintf(stderr, "\n");

	fprintf(stderr, "Initalizing backing store file '%s' to %lu bytes ",
		MMAP_TEST_FILE_NAME, total_size);
	memset(TEST_ZeroBuffer, '\0', sizeof(TEST_ZeroBuffer));
	count_1        = 0;
	remaining_size = total_size;
	while (remaining_size) {
		tmp_size        =
			((unsigned int) ((remaining_size < sizeof(TEST_ZeroBuffer)) ?
			remaining_size : sizeof(TEST_ZeroBuffer)));
		remaining_size -= ((unsigned long) tmp_size);
		fwrite(TEST_ZeroBuffer, tmp_size, 1, file_ptr);
		if (!(++count_1 % 100))
			fprintf(stderr, ".");
	}
	fflush(file_ptr);
	fprintf(stderr, "\n");

	if ((mmap_list = ((void **) calloc(loop_count, sizeof(void *)))) == NULL) {
		GEN_AllocMsgList(loop_count, sizeof(void *), error_text,
			"Unable to allocate a list of 'void *' pointers");
		return_code = GENFUNCS_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

#ifdef _Windows
	fclose(file_ptr);
	file_ptr = NULL;
	GetSystemInfo(&system_data);
	fprintf(stderr, "\n");
	fprintf(stderr, "Alloc Granular : %u\n",
		system_data.dwAllocationGranularity);
	fprintf(stderr, "Handle 'stdin' : 0X%08X\n", GetStdHandle(STD_INPUT_HANDLE));
	fprintf(stderr, "Handle 'stdout': 0X%08X\n", GetStdHandle(STD_OUTPUT_HANDLE));
   fprintf(stderr, "Handle 'stderr': 0X%08X\n", GetStdHandle(STD_ERROR_HANDLE));
	if ((file_handle = CreateFile(MMAP_TEST_FILE_NAME,
		GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL))
		== INVALID_HANDLE_VALUE) {
		sprintf(error_text, "Unable to open test file '%s': ",
			MMAP_TEST_FILE_NAME);
		GEN_AppendLastErrorString(0, MMAP_MAX_ERROR_TEXT, error_text);
		return_code = MMAP_SYSTEM_FAILURE;
		goto EXIT_FUNCTION;
	}
	fprintf(stderr, "Handle for mmap: 0X%08X\n", file_handle);
#else
	file_handle = fileno(file_ptr);
#endif /* #ifdef _Windows */

	fprintf(stderr, "Test in progress ");
	for (count_1 = 0; count_1 < test_count; count_1++) {
		mmap_count = 0;
		for (count_2 = 0; count_2 < loop_count; count_2++) {
			if ((return_code = MMAP_Map(NULL, (count_2 + 1) * page_size,
				MMAP_PROT_READ + MMAP_PROT_WRITE, MMAP_MMAP_SHARED,
				file_handle, count_2 * page_size, mmap_list + count_2,
				error_text)) != MMAP_SUCCESS)
				goto EXIT_FUNCTION;
			mmap_count++;
		}
		for (count_2 = 0; count_2 < mmap_count; count_2++) {
			if ((return_code = MMAP_Unmap(mmap_list[count_2],
				(count_2 + 1) * page_size, error_text)) != MMAP_SUCCESS)
				goto EXIT_FUNCTION;
		}
		fprintf(stderr, ".");
	}
	fprintf(stderr, "\n");

EXIT_FUNCTION:

	if (file_ptr != NULL)
		fclose(file_ptr);

	if (mmap_list != NULL)
		free(mmap_list);

	if (return_code != MMAP_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

