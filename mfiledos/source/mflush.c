#include "mfile.h"

COMPAT_EXTERN_DATA_DECL MFILE        *MFILE_EntryList;
COMPAT_EXTERN_DATA_DECL unsigned int  MFILE_EntryCount;

int mflush(mfile_ptr)
MFILE *mfile_ptr;
{
	int return_code = EOF;

   if (mfile_ptr->mfile_flags & MFILE_FLAG_IN_USE)
		return_code = 0;

	return(return_code);
}

int mflushall()
{
	unsigned int count_1;
	int          flushed_count = 0;

	for (count_1 = 0; count_1 < MFILE_EntryCount; count_1++) {
		if (MFILE_EntryList[count_1].mfile_flags & MFILE_FLAG_IN_USE) {
			if (MFILE_EntryList[count_1].mfile_flags & MFILE_MODE_WRITE)
				mflush(MFILE_EntryList + count_1);
			flushed_count++;
		}
	}

	return(flushed_count);
}

