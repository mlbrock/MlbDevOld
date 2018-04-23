/* *********************************************************************** */
/* *********************************************************************** */
/*	GENFUNCS General Functions Library Source Module								*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Manages general-purpose interactions with the
								operating system page mapping facilities.

	Revision History	:	1998-11-28 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#define  _STRUCTURED_PROC  1

#include <fcntl.h>
#include <limits.h>
#include <math.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>

#ifdef __SVR4
# define __EXTENSIONS__
# include <unistd.h>
# include <sys/types.h>
# include <sys/signal.h>
# include <sys/fault.h>
# include <sys/syscall.h>
# include <sys/procfs.h>
#endif /* #ifdef __SVR4 */

#include <strfuncs.h>

#include "genfunci.h"

/*	***********************************************************************	*/

#ifdef __SVR4
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Function prototypes for static functions . . .									*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(int GEN_PMAP_OpenPMapAccess, (int selector,
	int *file_handle, unsigned int *pmap_count, char *error_text));
COMPAT_FN_DECL_STATIC(int GEN_PMAP_GetNextPMap, (int file_handle,
	int *pmap_flag, GEN_PMAP_DESC *pmap_ptr, char *error_text));
/*	***********************************************************************	*/
#endif /* #ifdef __SVR4 */

/* *********************************************************************** */
#ifndef NARGS
int GEN_PMAP_GetPMapList(int selector, unsigned int *pmap_count,
	GEN_PMAP_DESC **pmap_list, char *error_text)
#else
int GEN_PMAP_GetPMapList(selector, pmap_count, pmap_list, error_text)
int             selector;
unsigned int   *pmap_count;
GEN_PMAP_DESC **pmap_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
#ifdef __SVR4
	int           return_code = GENFUNCS_SUCCESS;

	int          file_handle = -1;
	unsigned int count_1;
	int          pmap_flag;
	char         proc_file_name[1 + 4 + 1 + 5 + 1 + 8 + 1];
	char         tmp_error_text[GENFUNCS_MAX_ERROR_TEXT];

	*pmap_count = 0;
	*pmap_list  = NULL;

	selector    = (selector >= 0) ? selector : getpid();

	sprintf(proc_file_name, "/proc/%05d/map", selector);
	if ((return_code = GEN_PMAP_OpenPMapAccess(selector, &file_handle,
		pmap_count, error_text)) == GENFUNCS_SUCCESS) {
		if (*pmap_count) {
			if ((*pmap_list = ((GEN_PMAP_DESC *) calloc(*pmap_count,
				sizeof(**pmap_list)))) == NULL) {
				GEN_AllocMsgList(*pmap_count, sizeof(**pmap_list), error_text,
					"%s %s '%s'", "Unable to allocate the list of",
					"'GEN_PMAP_DESC' structures from the process control file",
					proc_file_name);
				return_code = GENFUNCS_MEMORY_FAILURE;
			}
			else {
				for (count_1 = 0; count_1 < *pmap_count; count_1++) {
					if ((return_code = GEN_PMAP_GetNextPMap(file_handle,
						&pmap_flag, *pmap_list + count_1, tmp_error_text)) !=
						GENFUNCS_SUCCESS) {
						sprintf(error_text,
							"Error reading process control file '%s': %s",
							proc_file_name, tmp_error_text);
						free(*pmap_list);
						*pmap_count = 0;
						*pmap_list  = NULL;
						break;
					}
					else if (pmap_flag != GENFUNCS_TRUE)
						break;
printf("Map Entry Index  : %10u\n", count_1);
printf("Mapping VAddress : 0x%lx\n",
	((unsigned long) (*pmap_list)[count_1].address));
printf("Mapping Size     : %u\n", (*pmap_list)[count_1].size);
printf("Mapping Offset   : %u\n", (*pmap_list)[count_1].offset);
printf("Sys Mapping Flags: %u (%04X)\n", (*pmap_list)[count_1].sys_flags,
	(*pmap_list)[count_1].sys_flags);
printf("Mapping Flags    : %u (%04X)\n", (*pmap_list)[count_1].flags,
	(*pmap_list)[count_1].flags);
printf("Mapping Page Size: %u\n", (*pmap_list)[count_1].page_size);
printf("------------------ ---------------------\n");
				}
			}
		}
		close(file_handle);
	}

	return(return_code);
#else
	*pmap_count = 0;
	*pmap_list  = NULL;

	return(GENFUNCS_SUCCESS);
#endif /* #ifdef __SVR4 */
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int GEN_PMAP_LocateByAddress(int selector, const void *address, int *pmap_flag,
	GEN_PMAP_DESC *pmap_ptr, char *error_text)
#else
int GEN_PMAP_LocateByAddress(selector, address, pmap_flag, pmap_ptr,
	error_text)
int            selector;
const void    *address;
int           *pmap_flag;
GEN_PMAP_DESC *pmap_ptr;
char          *error_text;
#endif /* #ifndef NARGS */
{
#ifdef __SVR4
	int           return_code = GENFUNCS_SUCCESS;
	int           file_handle = -1;
	unsigned int  count_1     = 0;
	unsigned int  pmap_count;
	int           tmp_pmap_flag;
	char          proc_file_name[1 + 4 + 1 + 5 + 1 + 8 + 1];
	GEN_PMAP_DESC pmap_data;
	char          tmp_error_text[GENFUNCS_MAX_ERROR_TEXT];

	*pmap_flag = GENFUNCS_FALSE;
	selector   = (selector >= 0) ? selector : getpid();

	sprintf(proc_file_name, "/proc/%05d/map", selector);
	if ((return_code = GEN_PMAP_OpenPMapAccess(selector, &file_handle,
		&pmap_count, error_text)) == GENFUNCS_SUCCESS) {
		for (count_1 = 0; count_1 < pmap_count; count_1++) {
			if ((return_code = GEN_PMAP_GetNextPMap(file_handle, &tmp_pmap_flag,
				&pmap_data, tmp_error_text)) != GENFUNCS_SUCCESS) {
				sprintf(error_text, "Error reading process control file '%s': %s",
					proc_file_name, tmp_error_text);
				break;
			}
			else if (tmp_pmap_flag != GENFUNCS_TRUE)
				break;
			if ((address >= pmap_data.address) && (((char *) address) <
				(((char *) pmap_data.address) + pmap_data.size))) {
				*pmap_ptr  = pmap_data;
				*pmap_flag = GENFUNCS_TRUE;
				break;
			}
		}
		close(file_handle);
	}

	return(return_code);
#else
	return(GENFUNCS_SUCCESS);
#endif /* #ifdef __SVR4 */
}
/* *********************************************************************** */

#ifdef __SVR4
/* *********************************************************************** */
#ifndef NARGS
static int GEN_PMAP_OpenPMapAccess(int selector, int *file_handle,
	unsigned int *pmap_count, char *error_text)
#else
static int GEN_PMAP_OpenPMapAccess(selector, file_handle, pmap_count,
	error_text)
int           selector;
int          *file_handle;
unsigned int *pmap_count;
char         *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code = GENFUNCS_SUCCESS;
	struct stat   stat_data;
	char          proc_file_name[1 + 4 + 1 + 5 + 1 + 8 + 1];

	*pmap_count = 0;
	selector    = (selector >= 0) ? selector : getpid();

	sprintf(proc_file_name, "/proc/%05d/map", selector);
	if ((*file_handle = open(proc_file_name, O_RDONLY)) == -1) {
		sprintf(error_text,
			"Unable to open process control file '%s' for reading: ",
			proc_file_name);
		GEN_AppendLastErrorString(0, GENFUNCS_MAX_ERROR_TEXT, error_text);
		return_code = GENFUNCS_SYSTEM_FAILURE;
	}
	else if (fstat(*file_handle, &stat_data)) {
		sprintf(error_text, "Error on attempt to 'fstat()' file '%s': ",
			proc_file_name);
		GEN_AppendLastErrorString(0, GENFUNCS_MAX_ERROR_TEXT, error_text);
		return_code = GENFUNCS_SYSTEM_FAILURE;
	}
	else if (stat_data.st_size % sizeof(prmap_t)) {
		sprintf(error_text, "%s '%s' (%lu) %s (%u).",
			"The size of the process control file", proc_file_name,
			((unsigned long) stat_data.st_size),
			"is not an integral multiple of the 'prmap_t' structure size",
			sizeof(prmap_t));
		return_code = GENFUNCS_FAILURE;
	}
	else
		*pmap_count = stat_data.st_size / sizeof(prmap_t);

	if (return_code != GENFUNCS_SUCCESS) {
		if (*file_handle != -1)
			close(*file_handle);
		*file_handle = -1;
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int GEN_PMAP_GetNextPMap(int file_handle, int *pmap_flag,
	GEN_PMAP_DESC *pmap_ptr, char *error_text)
#else
static int GEN_PMAP_GetNextPMap(file_handle, pmap_flag, pmap_ptr, error_text)
int            file_handle;
int           *pmap_flag;
GEN_PMAP_DESC *pmap_ptr;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = GENFUNCS_SUCCESS;
	unsigned int read_length;
	prmap_t      prmap_data;

	*pmap_flag = GENFUNCS_FALSE;

	if ((read_length = read(file_handle, &prmap_data,
		sizeof(prmap_data))) == sizeof(prmap_data)) {
		pmap_ptr->address   = ((void *) prmap_data.pr_vaddr);
		pmap_ptr->size      = prmap_data.pr_size;
#if _STRUCTURED_PROC
		pmap_ptr->offset    = prmap_data.pr_offset;
#else
		pmap_ptr->offset    = prmap_data.pr_off;
#endif /* #if _STRUCTURED_PROC */
		pmap_ptr->sys_flags = prmap_data.pr_mflags;
		pmap_ptr->flags     =
			((pmap_ptr->sys_flags & MA_READ)   ? GEN_PMAP_FLAG_READ    : 0) |
			((pmap_ptr->sys_flags & MA_WRITE)  ? GEN_PMAP_FLAG_WRITE   : 0) |
			((pmap_ptr->sys_flags & MA_EXEC)   ? GEN_PMAP_FLAG_EXEC    : 0) |
			((pmap_ptr->sys_flags & MA_SHARED) ? GEN_PMAP_FLAG_SHARED  : 0) |
#if _STRUCTURED_PROC
			((pmap_ptr->sys_flags & MA_ANON)   ? GEN_PMAP_FLAG_ANON    : 0) |
#endif /* #if _STRUCTURED_PROC */
			((pmap_ptr->sys_flags & MA_BREAK)  ? GEN_PMAP_FLAG_BREAK   : 0) |
			((pmap_ptr->sys_flags & MA_STACK)  ? GEN_PMAP_FLAG_STACK   : 0);
		pmap_ptr->page_size = prmap_data.pr_pagesize;
		*pmap_flag          = GENFUNCS_TRUE;
	}
	else if (read_length != 0) {
		sprintf(error_text, "Invalid read from the '/proc' file: %u bytes.",
			read_length);
		return_code = GENFUNCS_FAILURE;
	}

	return(return_code);
}
/* *********************************************************************** */
#endif /* #ifdef __SVR4 */

#ifdef TEST_MAIN

#if __SVR4
#include <errno.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#endif /* #if __SVR4 */

COMPAT_FN_DECL(int main, (void));

#define GEN_PMAP_TEST_SIZE			4096

int main()
{
	int            return_code;
	int            pmap_flag;
	GEN_PMAP_DESC  pmap_data;
	unsigned int   pmap_count;
	GEN_PMAP_DESC *pmap_list;
	char           error_text[GENFUNCS_MAX_ERROR_TEXT];

	void *tmp_ptr  = NULL;
#if __SVR4
	FILE *file_ptr = NULL;
#endif /* #if __SVR4 */

	fprintf(stderr, "Test routine for 'GEN_PMAP_GetPMapList()'\n");
	fprintf(stderr, "---- ------- --- ------------------------\n\n");


#if __SVR4
	if (!(file_ptr = fopen("ERASE.ME", "w+"))) {
		sprintf(error_text,
			"Unable to open test file 'ERASE.ME' for writing: ");
		GEN_AppendLastErrorString(0, GENFUNCS_MAX_ERROR_TEXT, error_text);
		return_code = GENFUNCS_SYSTEM_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if (ftruncate(fileno(file_ptr), GEN_PMAP_TEST_SIZE)) {
		sprintf(error_text,
			"Unable to 'ftruncate()' test file 'ERASE.ME' to %u bytes: ",
			GEN_PMAP_TEST_SIZE);
		GEN_AppendLastErrorString(0, GENFUNCS_MAX_ERROR_TEXT, error_text);
		return_code = GENFUNCS_SYSTEM_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if (((int) (tmp_ptr = ((char *) mmap(NULL, GEN_PMAP_TEST_SIZE,
		PROT_READ, MAP_SHARED, fileno(file_ptr), 0)))) == -1) {
		sprintf(error_text,
			"Unable to 'mmap()' test file 'ERASE.ME' for %u bytes: ",
			GEN_PMAP_TEST_SIZE);
		GEN_AppendLastErrorString(0, GENFUNCS_MAX_ERROR_TEXT, error_text);
		return_code = GENFUNCS_SYSTEM_FAILURE;
		goto EXIT_FUNCTION;
	}
#else
	if ((tmp_ptr = calloc(GEN_PMAP_TEST_SIZE, sizeof(char))) == NULL) {
		GEN_AllocMsgItem(GEN_PMAP_TEST_SIZE, error_text,
			"Unable to allocate test memory buffer");
		return_code = GENFUNCS_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}
#endif /* #if __SVR4 */

	if ((return_code = GEN_PMAP_GetPMapList(-1, &pmap_count, &pmap_list,
		error_text)) != GENFUNCS_SUCCESS)
		goto EXIT_FUNCTION;
	else if (pmap_list != NULL)
		free(pmap_list);

	if ((return_code = GEN_PMAP_LocateByAddress(-1, ((const void *) tmp_ptr),
		&pmap_flag, &pmap_data, error_text)) != GENFUNCS_SUCCESS)
		goto EXIT_FUNCTION;
	else {
		printf("\n\n'mmap()' mapping location:\n");
printf("Mapping VAddress : %X\n", ((unsigned long) pmap_data.address));
printf("Mapping Size     : %u\n", pmap_data.size);
printf("Mapping Offset   : %u\n", pmap_data.offset);
printf("Sys Mapping Flags: %u (%04X)\n", pmap_data.sys_flags,
	pmap_data.sys_flags);
printf("Mapping Flags    : %u (%04X)\n", pmap_data.flags,
	pmap_data.flags);
printf("Mapping Page Size: %u\n", pmap_data.page_size);
printf("------------------ ---------------------\n");
	}

#if __SVR4
printf("MAP ADDRESS = %X\n", ((unsigned long) tmp_ptr));
printf("PAGE SIZE   = %u\n", getpagesize());
#endif /* #if __SVR4 */

EXIT_FUNCTION:

#if __SVR4
	if (tmp_ptr != NULL)
		munmap(tmp_ptr, GEN_PMAP_TEST_SIZE);
	if (file_ptr != NULL)
		fclose(file_ptr);
#else
	if (tmp_ptr != NULL)
		free(tmp_ptr);
#endif /* #if __SVR4 */

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

