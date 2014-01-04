#include <limits.h>
#include <string.h>

#include "mfile.h"

/*VARARGS2*/
#ifndef NO_STDARGS
int mprintf(MFILE *mfile_ptr, const char *in_format, ...)
#else
int mprintf(mfile_ptr, in_format, va_alist)
MFILE      *mfile_ptr;
const char *in_format; 
va_dcl
#endif /* #ifndef NO_STDARGS */
{
	int     char_count = 0;
	va_list argument_ptr;

	if (mprintf_ensure_space(mfile_ptr) != 0) {
#ifndef NO_STDARGS
		va_start(argument_ptr, in_format);
#else
		va_start(argument_ptr);
#endif /* #ifndef NO_STDARGS */
		char_count = vfprintf(mfile_ptr->file_ptr, in_format, argument_ptr);
		va_end(argument_ptr);
		if (char_count > 0) {
			mfile_ptr->mfile_flags    |= MFILE_FLAG_WRITTEN;
			mfile_ptr->current_offset += char_count;
			mfile_ptr->file_size       =
				(mfile_ptr->current_offset > mfile_ptr->file_size) ?
				mfile_ptr->current_offset : mfile_ptr->file_size;
		}
	}

	return(char_count);
}
int mprintf_ensure_space(mfile_ptr)
MFILE *mfile_ptr;
{
	int           has_space_flag = 0;
	unsigned long buffer_size;
	unsigned long new_size;

	if ((mfile_ptr != NULL) && (!MFILE_ValidateMFILEPtr(mfile_ptr)) &&
		(mfile_ptr->mfile_flags & MFILE_MODE_WRITE)) {
		buffer_size = (mfile_ptr->buffer_size > MFILE_PRINTF_BUFFER_SIZE) ?
			mfile_ptr->buffer_size : MFILE_PRINTF_BUFFER_SIZE;
		if ((new_size = (mfile_ptr->mmap_size - mfile_ptr->current_offset)) <
			MFILE_PRINTF_BUFFER_SIZE_MIN) {
			new_size = mfile_ptr->mmap_size + buffer_size;
			if (!mtruncate_safe(mfile_ptr, new_size)) {
				mfile_ptr->file_size = mfile_ptr->current_offset;
 				has_space_flag       = 1;
			}
		}
		else
			has_space_flag = 1;
	}

	return(has_space_flag);
}

