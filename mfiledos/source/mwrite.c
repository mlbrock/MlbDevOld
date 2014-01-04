#include <memory.h>

#include "mfile.h"

COMPAT_EXTERN_DATA_DECL MFILE        *MFILE_EntryList;
COMPAT_EXTERN_DATA_DECL unsigned int  MFILE_EntryCount;

int mwrite(data_ptr, element_size, element_count, mfile_ptr)
const void   *data_ptr;
unsigned int  element_size;
unsigned int  element_count;
MFILE        *mfile_ptr;
{
	unsigned long  byte_count;

	if (!(mfile_ptr->mfile_flags & MFILE_MODE_WRITE))
		byte_count = 0;
	else
		byte_count = fwrite(data_ptr, element_size, element_count,
			mfile_ptr->file_ptr) * element_size;

	mfile_ptr->current_offset += byte_count;

	return(((unsigned int) (byte_count / ((unsigned long) element_size))));
}

