#include <memory.h>

#include "mfile.h"

COMPAT_EXTERN_DATA_DECL MFILE        *MFILE_EntryList;
COMPAT_EXTERN_DATA_DECL unsigned int  MFILE_EntryCount;

int mread(data_ptr, element_size, element_count, mfile_ptr)
void         *data_ptr;
unsigned int  element_size;
unsigned int  element_count;
MFILE        *mfile_ptr;
{
	if (!(mfile_ptr->mfile_flags & MFILE_MODE_READ))
		element_count = 0;
	else
		element_count = fread(data_ptr, element_size, element_count,
			mfile_ptr->file_ptr);

	return(element_count);
}

