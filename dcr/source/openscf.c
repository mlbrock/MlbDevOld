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

#include <sys/types.h>
#include <sys/vfs.h>

#include "dcr.h"

/*	***********************************************************************	*/

int DCR_OpenCache(cache_file_name, cache_access_type, open_flag,
	mmap_prot, mmap_flag, file_handle, mmap_ptr, mmap_size, cache_block_size,
	errno_code, open_failure_flag, mmap_failure_flag, error_text)
const char     *cache_file_name;
unsigned long   cache_access_type;
int            *open_flag;
int            *mmap_prot;
int            *mmap_flag;
int            *file_handle;
volatile void **mmap_ptr;
unsigned long  *mmap_size;
unsigned int   *cache_block_size;
int            *errno_code;
int            *open_failure_flag;
int            *mmap_failure_flag;
char           *error_text;
{
	int           return_code;
	unsigned int  page_size;
#ifdef __SVR4
# define fstatfs fstatvfs
	struct statvfs statfs_data;
#else
	struct statfs statfs_data;
#endif /* #ifdef __SVR4 */

	*open_flag         = (cache_access_type == DCR_I_AM_WRITER) ?
		O_RDWR : O_RDONLY;
	*mmap_prot         = (cache_access_type == DCR_I_AM_WRITER) ?
		(PROT_READ | PROT_WRITE) : PROT_READ;
	*mmap_flag         = MAP_SHARED;
	*file_handle       = -1;
	*mmap_ptr          = NULL;
	*mmap_size         = 0L;
	*cache_block_size  = 0;
	*open_failure_flag = DCR_FALSE;
	*mmap_failure_flag = DCR_FALSE;

	if (DCR_IsValidAccessType(cache_access_type) != DCR_TRUE) {
		sprintf(error_text,
			"Invalid cache access type specified (0X%08lX = %010lu)",
			cache_access_type, cache_access_type);
		return_code = DCR_BAD_ARGS_FAILURE;
	}
	else if (DCR_HEADER_PAGE_SIZE < (page_size = GEN_GetPageSize())) {
		sprintf(error_text, "The cache page size (%u) %s (%u).",
			DCR_HEADER_PAGE_SIZE, "is less than the cache page size",
			page_size);
		return_code = DCR_FAILURE;
	}
	else if (DCR_HEADER_PAGE_SIZE % page_size) {
		sprintf(error_text, "The cache page size (%u) %s (%u).",
			DCR_HEADER_PAGE_SIZE,
			"is not an integral multiple of the cache page size", page_size);
		return_code = DCR_FAILURE;
	}
	else if ((return_code = DCR_OpenRaw(cache_file_name, *open_flag, 0,
		*mmap_prot, *mmap_flag, file_handle, mmap_ptr, mmap_size, errno_code,
		open_failure_flag, mmap_failure_flag, error_text)) == DCR_SUCCESS) {
		*cache_block_size = (!fstatfs(*file_handle, &statfs_data)) ?
			((unsigned int) statfs_data.f_bsize) : DCR_DEF_FS_BLOCK_SIZE;
		if (*mmap_size <
			((DCR_HEADER *) *mmap_ptr)->header_area_size) {
			sprintf(error_text, "%s '%-.500s' (%lu) %s (%lu).",
				"The size of the cache file", cache_file_name, *mmap_size,
				"is less than the size of the cache header",
				((DCR_HEADER *) *mmap_ptr)->header_area_size);
			return_code = DCR_FAILURE;
			DCR_CloseRaw(file_handle, mmap_ptr, mmap_size);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

