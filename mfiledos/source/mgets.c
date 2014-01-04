#include "mfile.h"

char *mgets(buffer_ptr, buffer_max, mfile_ptr)
char  *buffer_ptr;
int    buffer_max;
MFILE *mfile_ptr;
{
	char *return_ptr = buffer_ptr;

	if (!(mfile_ptr->mfile_flags & MFILE_MODE_READ))
		return_ptr = NULL;
	else
		fgets(buffer_ptr, buffer_max, mfile_ptr->file_ptr);

	return(return_ptr);
}

