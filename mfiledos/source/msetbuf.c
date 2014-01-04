#include "mfile.h"

void msetbuf(mfile_ptr, buffer_size)
MFILE        *mfile_ptr;
unsigned int  buffer_size;
{
	if (!setvbuf(mfile_ptr->file_ptr, NULL, _IOFBF, buffer_size))
		mfile_ptr->buffer_size = buffer_size;
}

