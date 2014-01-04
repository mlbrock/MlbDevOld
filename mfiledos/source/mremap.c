#include <errno.h>
#include <limits.h>
#include <sys/stat.h>

#include "mfile.h"

int mremap(mfile_ptr)
MFILE *mfile_ptr;
{
	int         return_code;
	struct stat stat_data;

	if (fstat(fileno(mfile_ptr->file_ptr), &stat_data))
		return_code = -1;
	else if (!(return_code = mremap_basic_1(mfile_ptr, 0,
		((unsigned long) stat_data.st_size))))
		mfile_ptr->file_size = stat_data.st_size;

	return(return_code);
}

int mremap_basic_1(mfile_ptr, offset, length)
MFILE         *mfile_ptr;
unsigned long  offset;
unsigned long  length;
{
	int return_code;
	int fatal_error_flag;

	if (((return_code = mremap_basic_2(fileno(mfile_ptr->file_ptr),
		&mfile_ptr->mmap_size, &mfile_ptr->mmap_ptr, &mfile_ptr->current_offset,
		mfile_ptr->mmap_prot, mfile_ptr->mmap_flags, offset, length,
		&fatal_error_flag)) != 0) && fatal_error_flag)
		mclose(mfile_ptr);

	return(return_code);
}

int mremap_basic_2(file_handle, mmap_size, mmap_ptr, current_offset,
	mmap_prot, mmap_flags, offset, length, fatal_error_flag)
int             file_handle;
unsigned long  *mmap_size;
volatile void **mmap_ptr;
unsigned long  *current_offset;
int             mmap_prot;
int             mmap_flags;
unsigned long   offset;
unsigned long   length;
int            *fatal_error_flag;
{
	int return_code = 0;

	*fatal_error_flag = 0;

	if ((offset > ((unsigned long) LONG_MAX)) ||
		 (length > ((unsigned long) LONG_MAX))) {
		errno       = EFBIG;
		return_code = -1;
		goto EXIT_FUNCTION;
	}

EXIT_FUNCTION:

	return(return_code);
}

