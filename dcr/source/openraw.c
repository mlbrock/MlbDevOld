/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	

	Revision History	:	1994-03-14 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <errno.h>
#include <string.h>

#ifdef __MSDOS__
# include <io.h>
#endif /* #ifdef __MSDOS__ */

#include "dcr.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#ifndef NARGS
static int DCR_OpenRawForRead(const char *cache_file_name,
	int mmap_prot, const char *mmap_prot_text,
	int mmap_flag, const char *mmap_flag_text, int file_handle,
	volatile void **mmap_ptr, unsigned long *mmap_size, int *errno_code,
	int *mmap_failure_flag, char *error_text);
static int DCR_OpenRawForWrite(const char *cache_file_name,
	int mmap_prot, const char *mmap_prot_text,
	int mmap_flag, const char *mmap_flag_text, int file_handle,
	volatile void **mmap_ptr, unsigned long *mmap_size, int *errno_code,
	int *mmap_failure_flag, char *error_text);
#else
static int DCR_OpenRawForRead();
static int DCR_OpenRawForWrite();
#endif /* #ifndef NARGS */

/*	***********************************************************************	*/

int DCR_OpenRaw(cache_file_name, open_flag, open_mode, mmap_prot,
	mmap_flag, file_handle, mmap_ptr, mmap_size, errno_code,
	open_failure_flag, mmap_failure_flag, error_text)
const char     *cache_file_name;
int             open_flag;
int             open_mode;
int             mmap_prot;
int             mmap_flag;
int            *file_handle;
volatile void **mmap_ptr;
unsigned long  *mmap_size;
int            *errno_code;
int            *open_failure_flag;
int            *mmap_failure_flag;
char           *error_text;
{
	int   return_code = DCR_SUCCESS;
	char *open_flag_text;
	char *open_mode_text;
	char *mmap_prot_text;
	char *mmap_flag_text;

	*file_handle       = -1;
	*mmap_ptr          = NULL;
	*mmap_size         = 0L;
	*open_failure_flag = DCR_FALSE;
	*mmap_failure_flag = DCR_FALSE;

	open_flag_text     = (open_flag == O_RDWR) ? "binary read/write" :
		"binary read";
	open_mode_text     = (open_flag & (O_CREAT | O_TRUNC)) ? "create" :
		"existing";
	mmap_prot_text     = (mmap_prot == (PROT_READ | PROT_WRITE)) ?
		"PROT_READ | PROT_WRITE" : "PROT_READ";
	mmap_flag_text     = (mmap_flag == MAP_PRIVATE) ? "MAP_PRIVATE" :
		"MAP_SHARED";

	if ((open_flag != O_RDWR) && (open_flag != O_RDONLY) &&
		(open_flag != (O_RDWR | O_CREAT | O_TRUNC))) {
		sprintf(error_text, "Invalid cache open flags (0X%08lX = %010lu).",
			open_flag, open_flag);
		return_code = DCR_BAD_ARGS_FAILURE;
	}
	else if ((mmap_prot != (PROT_READ | PROT_WRITE)) &&
		(mmap_prot != PROT_READ)) {
		sprintf(error_text,
			"Invalid cache 'mmap()' protection (0X%08lX = %010lu) --- %s.",
			mmap_prot, mmap_prot,
			"expected either 'PROT_READ | PROT_WRITE' or 'PROT_READ'");
		return_code = DCR_BAD_ARGS_FAILURE;
	}
	else if ((mmap_flag != MAP_SHARED) && (mmap_flag != MAP_PRIVATE)) {
		sprintf(error_text,
			"Invalid cache 'mmap()' flags (0X%08lX = %010lu) --- %s.",
			mmap_flag, mmap_flag,
			"expected either 'MAP_SHARED' or 'MAP_PRIVATE'");
		return_code = DCR_BAD_ARGS_FAILURE;
	}
	else if ((*file_handle = open(cache_file_name, open_flag, open_mode)) ==
		-1) {
		sprintf(error_text,
			"%s '%-.500s' with flag '%s' (0X%08lX = %010lu), ",
			"Attempt to open the cache file", cache_file_name,
			open_flag_text, open_flag, open_flag);
		sprintf(error_text + strlen(error_text),
			"in mode '%s' (0X%08X = %010u) failed: ",
			open_mode_text, open_mode, open_mode);
		DCR_GEN_AppendLastErrorString(error_text);
		*errno_code        = errno;
		*open_failure_flag = DCR_TRUE;
		return_code        = DCR_SYSTEM_FAILURE;
	}
	else {
		return_code = (!(open_flag & O_RDWR)) ?
			DCR_OpenRawForRead(cache_file_name, mmap_prot, mmap_prot_text,
			mmap_flag, mmap_flag_text, *file_handle,
			mmap_ptr, mmap_size, errno_code, mmap_failure_flag, error_text) :
			DCR_OpenRawForWrite(cache_file_name, mmap_prot, mmap_prot_text,
			mmap_flag, mmap_flag_text, *file_handle,
			mmap_ptr, mmap_size, errno_code, mmap_failure_flag, error_text);
		if (return_code != DCR_SUCCESS) {
			close(*file_handle);
			*file_handle = -1;
			*mmap_size   = 0L;
			*mmap_ptr    = NULL;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

static int DCR_OpenRawForRead(cache_file_name, mmap_prot,
	mmap_prot_text, mmap_flag, mmap_flag_text, file_handle,
	mmap_ptr, mmap_size, errno_code, mmap_failure_flag, error_text)
const char     *cache_file_name;
int             mmap_prot;
const char     *mmap_prot_text;
int             mmap_flag;
const char     *mmap_flag_text;
int             file_handle;
volatile void **mmap_ptr;
unsigned long  *mmap_size;
int            *errno_code;
int            *mmap_failure_flag;
char           *error_text;
{
	int               return_code = DCR_SUCCESS;
	DCR_HEADER *header_mmap_ptr;

	if (((int) (header_mmap_ptr = ((DCR_HEADER *) mmap(NULL,
		sizeof(DCR_HEADER), mmap_prot, mmap_flag, file_handle,
		0)))) == -1) {
		sprintf(error_text,
			"%s '%-500s' %s = %lu, %s = '%s' = 0X%08lX = %010lu, ",
			"Attempt to 'mmap()' the cache file", cache_file_name,
			"for size", sizeof(DCR_HEADER), "mmap protection setting",
			mmap_prot_text, mmap_prot, mmap_prot);
		sprintf(error_text + strlen(error_text),
			"%s = '%s' = 0X%08lX = %010lu failed: ",
			"mmap access flags", mmap_flag_text, mmap_flag, mmap_flag);
		DCR_GEN_AppendLastErrorString(error_text);
		*errno_code        = errno;
		*mmap_failure_flag = DCR_TRUE;
		return_code        = DCR_SYSTEM_FAILURE;
	}
	else {
		*mmap_size = header_mmap_ptr->header_area_size;
		munmap(((void *) header_mmap_ptr), sizeof(DCR_HEADER));
		if (((int) (*mmap_ptr = mmap(NULL, ((long) *mmap_size), mmap_prot,
			mmap_flag, file_handle, 0))) == -1) {
			sprintf(error_text,
				"%s '%-500s' %s = %lu, %s = '%s' = 0X%08lX = %010lu, ",
				"Attempt to 'mmap()' the cache file", cache_file_name,
				"for size", *mmap_size, "mmap protection setting",
				mmap_prot_text, mmap_prot, mmap_prot);
			sprintf(error_text + strlen(error_text),
				"%s = '%s' = 0X%08lX = %010lu failed: ",
				"mmap access flags", mmap_flag_text, mmap_flag, mmap_flag);
			DCR_GEN_AppendLastErrorString(error_text);
			*errno_code        = errno;
			*mmap_failure_flag = DCR_TRUE;
			return_code        = DCR_SYSTEM_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

static int DCR_OpenRawForWrite(cache_file_name, mmap_prot,
	mmap_prot_text, mmap_flag, mmap_flag_text, file_handle,
	mmap_ptr, mmap_size, errno_code, mmap_failure_flag, error_text)
const char     *cache_file_name;
int             mmap_prot;
const char     *mmap_prot_text;
int             mmap_flag;
const char     *mmap_flag_text;
int             file_handle;
volatile void **mmap_ptr;
unsigned long  *mmap_size;
int            *errno_code;
int            *mmap_failure_flag;
char           *error_text;
{
	int return_code = DCR_SUCCESS;

	if (lseek(file_handle, 0L, SEEK_END) == -1L) {
		sprintf(error_text,
			"Attempt to 'seek()' on cache file '%-.500s' failed: ",
			cache_file_name);
		DCR_GEN_AppendLastErrorString(error_text);
		return_code = DCR_SYSTEM_FAILURE;
	}
	else if ((*mmap_size = ((unsigned long) lseek(file_handle, 0L,
		SEEK_END))) > 0) {
		if (((int) (*mmap_ptr = mmap(NULL, ((long) *mmap_size), mmap_prot,
			mmap_flag, file_handle, 0))) == -1) {
			sprintf(error_text,
				"%s '%-500s' %s = %lu, %s = '%s' = 0X%08lX = %010lu, ",
				"Attempt to 'mmap()' the cache file", cache_file_name,
				"for size", *mmap_size, "mmap protection setting",
				mmap_prot_text, mmap_prot, mmap_prot);
			sprintf(error_text + strlen(error_text),
				"%s = '%s' = 0X%08lX = %010lu failed: ",
				"mmap access flags", mmap_flag_text, mmap_flag, mmap_flag);
			DCR_GEN_AppendLastErrorString(error_text);
			*errno_code        = errno;
			*mmap_failure_flag = DCR_TRUE;
			return_code        = DCR_SYSTEM_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

