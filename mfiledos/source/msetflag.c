#include "mfile.h"

int msetflag(mfile_ptr, mmap_prot, mmap_flags)
MFILE *mfile_ptr;
int    mmap_prot;
int    mmap_flags;
{
	int return_code = 0;

	if ((mfile_ptr->mmap_prot != mmap_prot) ||
		(mfile_ptr->mmap_flags != mmap_flags)) {
		mfile_ptr->mmap_prot  = mmap_prot;
		mfile_ptr->mmap_flags = mmap_flags;
	}

	return(return_code);
}

