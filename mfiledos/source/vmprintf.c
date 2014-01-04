#include <limits.h>
#include <string.h>

#include "mfile.h"

int vmprintf(mfile_ptr, in_format, arg_list)
MFILE      *mfile_ptr;
const char *in_format; 
va_list     arg_list;
{
	int char_count = 0;

	if (mprintf_ensure_space(mfile_ptr) != MFILE_FALSE) {
		char_count = vfprintf(mfile_ptr->file_ptr, in_format, arg_list);
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

