#include "mfile.h"

int mgetc(mfile_ptr)
MFILE *mfile_ptr;
{
	int return_char = EOF;

	if ((mfile_ptr->mfile_flags & MFILE_MODE_READ) &&
		(mfile_ptr->current_offset < mfile_ptr->file_size))
		return_char = fgetc(mfile_ptr->file_ptr);

	return(return_char);
}

