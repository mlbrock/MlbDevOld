#include "mfile.h"

long mtell(mfile_ptr)
MFILE *mfile_ptr;
{
	return((!MFILE_ValidateMFILEPtr(mfile_ptr)) ?
		((long) ftell(mfile_ptr->file_ptr)) : -1L);
}

