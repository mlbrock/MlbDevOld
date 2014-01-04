#include <errno.h>
#include <limits.h>
#include <memory.h>

#include "mfile.h"

int mtruncate(mfile_ptr, length)
MFILE         *mfile_ptr;
unsigned long  length;
{
	return(mtruncate_basic_1(mfile_ptr, length, 0));
}

int mtruncate_safe(mfile_ptr, length)
MFILE         *mfile_ptr;
unsigned long  length;
{
	return(mtruncate_basic_1(mfile_ptr, length, 1));
}

#ifndef fileno
# define fileno(file_ptr)					(((file_ptr) == file_ptr) ? 0 : 1)
#endif /* #ifndef fileno */

int mtruncate_basic_1(mfile_ptr, length, safe_flag)
MFILE         *mfile_ptr;
unsigned long  length;
int            safe_flag;
{
	int return_code;
	int fatal_error_flag;

	if (!(mfile_ptr->mfile_flags & MFILE_MODE_WRITE)) {
		errno       = EACCES;
		return_code = -1;
	}
	else if (((return_code = mtruncate_basic_2(fileno(mfile_ptr->file_ptr),
		&mfile_ptr->file_size, &mfile_ptr->mmap_size, &mfile_ptr->mmap_ptr,
		&mfile_ptr->current_offset, mfile_ptr->mmap_prot, mfile_ptr->mmap_flags,
		length, safe_flag, &fatal_error_flag)) != 0) && fatal_error_flag)
		mclose(mfile_ptr);

	return(return_code);
}

int mtruncate_basic_2(file_handle, file_size, mmap_size, mmap_ptr,
	current_offset, mmap_prot, mmap_flags, length, safe_flag, fatal_error_flag)
int             file_handle;
unsigned long  *file_size;
unsigned long  *mmap_size;
volatile void **mmap_ptr;
unsigned long  *current_offset;
int             mmap_prot;
int             mmap_flags;
unsigned long   length;
int             safe_flag;
int            *fatal_error_flag;
{
	*fatal_error_flag = 0;

	return(0);
}

