#include "mfile.h"

void mrewind(mfile_ptr)
MFILE *mfile_ptr;
{
	mseek(mfile_ptr, 0L, SEEK_SET);
}

