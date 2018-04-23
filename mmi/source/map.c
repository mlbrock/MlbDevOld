/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MMI Memory-mapped Interface Library Source Code Module						*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	

	Revision History	:	1992-03-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2018.
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

#include "mmii.h"

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

	COPYRIGHT	:	Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	
						Memory-mapped Interface Functions:See MMI Library Functions
						MMI Library Functions

   PUBLISH XREF:	

   PUBLISH NAME:	

	ENTRY CLASS	:	Memory-mapped Interface Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int MMI_Map(MMI_ADDRESS address, MMI_LENGTH length, MMI_FLAG prot_flags,
	MMI_FLAG mmap_flags, MMI_FILE_HANDLE file_handle, MMI_OFFSET offset,
	MMI_ADDRESS *out_address, MMI_MMAP_HANDLE_OS *os_mmap_handle,
	char *error_text)
#else
int MMI_Map(address, length, prot_flags, mmap_flags, file_handle, offset,
	out_address, os_mmap_handle, error_text)
MMI_ADDRESS         address;
MMI_LENGTH          length;
MMI_FLAG            prot_flags;
MMI_FLAG            mmap_flags;
MMI_FILE_HANDLE     file_handle;
MMI_OFFSET          offset;
MMI_ADDRESS        *out_address;
MMI_MMAP_HANDLE_OS *os_mmap_handle;
char               *error_text;
#endif /* #ifndef NARGS */
{
	int         return_code = MMI_SUCCESS;
	MMI_FLAG    os_prot_flags;
	MMI_FLAG    os_mmap_flags;
	MMI_ADDRESS tmp_ptr;
	char        mmap_string[MMI_FLAG_COMPLETE_MAX + 1];
	char        prot_string[MMI_FLAG_COMPLETE_MAX + 1];
	char        tmp_error_text[MMI_MAX_ERROR_TEXT];

	if (out_address == NULL) {
		if (error_text != NULL)
			strcpy(tmp_error_text,
				"Bad argument --- 'out_address' parameter is 'NULL'.");
		return_code = MMI_BAD_ARGS_FAILURE;
	}
	else if (((address == NULL) ||
		((return_code =
		MMI_CheckAddress(address, tmp_error_text))     == MMI_SUCCESS)) &&
		((return_code =
		MMI_CheckLength(length, tmp_error_text))       == MMI_SUCCESS)  &&
		((return_code =
		MMI_CheckProtect(prot_flags, tmp_error_text))  == MMI_SUCCESS)  &&
		((return_code =
		MMI_CheckMapFlags(mmap_flags, tmp_error_text)) == MMI_SUCCESS)) {
		os_prot_flags = MMI_MAP_FLAG_PROT_TO_OS(prot_flags);
		os_mmap_flags = MMI_MAP_FLAG_MMAP_TO_OS(mmap_flags);
#ifdef _Windows
		if ((tmp_ptr = MMI_WIN32_Map(address, length, os_prot_flags,
			os_mmap_flags, file_handle, offset, os_mmap_handle,
			tmp_error_text)) == ((void *) -1))
			return_code = MMI_SYSTEM_FAILURE;
#else
		if (os_mmap_handle != NULL)
			*os_mmap_handle = MMI_MMAP_HANDLE_OS_CLOSED;
		if ((tmp_ptr = MMI_mmap(address, length, os_prot_flags, os_mmap_flags,
			file_handle, offset)) == ((void *) -1)) {
			return_code = MMI_SYSTEM_FAILURE;
			if (error_text != NULL)
				GEN_GetLastErrorString(0, MMI_MAX_ERROR_TEXT, tmp_error_text);
		}
#endif /* #ifdef _Windows */
		else
			*out_address = tmp_ptr;
	}

	if ((return_code != MMI_SUCCESS) && (error_text != NULL))
		sprintf(error_text,
			"%s(%s = 0x%lx, %s = %lu, %s = 0x%lx = %s, %s = 0x%lx = %s, \
%s = 0x%lx, %s = %lu, %s = 0x%lx, %s = 0x%lx, %s = 0x%lx) failed: %s",
			"MMI_Map",
			"address", ((unsigned long) address),
			"length", length,
			"prot_flags", prot_flags, MMI_PROTFlags(prot_flags, prot_string),
			"mmap_flags", mmap_flags, MMI_MMAPFlags(mmap_flags, mmap_string),
			"file_handle", ((unsigned long) file_handle),
			"offset", offset,
			"out_address", ((unsigned long) out_address),
			"os_mmap_handle", ((unsigned long) os_mmap_handle),
			"error_text", ((unsigned long) error_text),
			tmp_error_text);

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#ifndef _Windows
#define MMI_TEST_COUNT				100
#define MMI_LOOP_COUNT				100
#else
#define MMI_TEST_COUNT				10
#define MMI_LOOP_COUNT				10
#endif /* #ifndef _Windows */

#define MMI_TEST_FILE_NAME		"ERASEME.TXT"

static char TEST_ZeroBuffer[8192];

COMPAT_FN_DECL(int main, (int argc, char **argv));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int            return_code = MMI_SUCCESS;
	unsigned int   test_count  = MMI_TEST_COUNT;
	unsigned int   loop_count  = MMI_LOOP_COUNT;
	unsigned int   mmap_count  = 0;
	void         **mmap_list   = NULL;
	unsigned long  total_size  = 0L;
	FILE          *file_ptr    = NULL;
	unsigned long  remaining_size;
	unsigned int   tmp_size;
	unsigned int   page_size;
	unsigned int   count_1;
	unsigned int   count_2;
	char           error_text[MMI_MAX_ERROR_TEXT];
	char           tmp_error_text[MMI_MAX_ERROR_TEXT];
	int            file_handle = -1;

	page_size = MMI_GetPageSize();

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

	for (count_1 = 0; count_1 < loop_count; count_1++)
		total_size += ((unsigned long) (count_1 + 1)) *
			((unsigned long) page_size);

	fprintf(stderr, "Creating backing store file '%s'",
		MMI_TEST_FILE_NAME);
	if ((file_ptr = fopen(MMI_TEST_FILE_NAME, "w+")) == NULL) {
		sprintf(error_text, "Unable to open test file '%s': ",
			MMI_TEST_FILE_NAME);
		GEN_AppendLastErrorString(0, MMI_MAX_ERROR_TEXT, error_text);
		return_code = MMI_SYSTEM_FAILURE;
		goto EXIT_FUNCTION;
	}
	fprintf(stderr, "\n");

	fprintf(stderr, "Initalizing backing store file '%s' to %lu bytes ",
		MMI_TEST_FILE_NAME, total_size);
	memset(TEST_ZeroBuffer, '\0', sizeof(TEST_ZeroBuffer));
	count_1        = 0;
	remaining_size = total_size;
	while (remaining_size) {
		tmp_size        =
			((unsigned int) ((remaining_size < sizeof(TEST_ZeroBuffer)) ?
			remaining_size : sizeof(TEST_ZeroBuffer)));
		remaining_size -= ((unsigned long) tmp_size);
		fwrite(TEST_ZeroBuffer, tmp_size, 1, file_ptr);
		fflush(file_ptr);
		if (!(++count_1 % 100))
			fprintf(stderr, ".");
	}
	fflush(file_ptr);

	fprintf(stderr, "\n");

	if ((mmap_list = ((void **) calloc(loop_count, sizeof(void *)))) == NULL) {
		STR_AllocMsgList(loop_count, sizeof(void *), error_text,
			"Unable to allocate a list of 'void *' pointers");
		return_code = MMI_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	file_handle = fileno(file_ptr);

	fprintf(stderr, "Test in progress ");
fprintf(stderr, "\n");
	for (count_1 = 0; count_1 < test_count; count_1++) {
		mmap_count = 0;
		for (count_2 = 0; count_2 < loop_count; count_2++) {
			if ((return_code = MMI_Map(NULL, (count_2 + 1) * page_size,
				MMI_FLAG_PROT_READ + MMI_FLAG_PROT_WRITE, MMI_FLAG_MMAP_SHARED,
				file_handle, count_2 * page_size, mmap_list + count_2, NULL,
				tmp_error_text)) != MMI_SUCCESS) {
				sprintf(error_text, "<MAP ATTEMPT>[%u][%u]  : %s\n",
					count_1, count_2, tmp_error_text);
				goto EXIT_FUNCTION;
			}
fprintf(stderr, "<MAP ATTEMPT>[%u][%u]  : %10u/%10u/%10u\n",
	count_1, count_2,
	(count_2 + 1) * page_size, count_2 * page_size,
	((count_2 + 1) * page_size) + (count_2 * page_size));
			mmap_count++;
		}
		for (count_2 = 0; count_2 < mmap_count; count_2++) {
			if ((return_code = MMI_Unmap(mmap_list[count_2],
				(count_2 + 1) * page_size, tmp_error_text)) != MMI_SUCCESS) {
				sprintf(error_text, "<UNMAP ATTEMPT>[%u][%u]: %s\n",
					count_1, count_2, tmp_error_text);
				goto EXIT_FUNCTION;
			}
fprintf(stderr, "<UNMAP ATTEMPT>[%u][%u]: %10u/%10u/%10u\n",
	count_1, count_2,
	(count_2 + 1) * page_size, count_2 * page_size,
	((count_2 + 1) * page_size) + (count_2 * page_size));
		}
#if 0
		fprintf(stderr, ".");
#endif /* #if 0 */
	}
	fprintf(stderr, "\n");

EXIT_FUNCTION:

	if (file_ptr != NULL)
		fclose(file_ptr);

	if (mmap_list != NULL)
		free(mmap_list);

	if (return_code != MMI_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

