#include <memory.h>

#include "mfile.h"

COMPAT_EXTERN_DATA_DECL MFILE        *MFILE_EntryList;
COMPAT_EXTERN_DATA_DECL unsigned int  MFILE_EntryCount;

int mclose(mfile_ptr)
MFILE *mfile_ptr;
{
	int return_code = 0;

	if (mfile_ptr->mfile_flags & MFILE_FLAG_IN_USE) {
		free(mfile_ptr->file_name);
		fclose(mfile_ptr->file_ptr);
		memset(mfile_ptr, '\0', sizeof(*mfile_ptr));
	}
	else
		return_code = EOF;

	return(return_code);
}

int mcloseall()
{
	unsigned int count_1;
	int          closed_count = 0;

	for (count_1 = 0; count_1 < MFILE_EntryCount; count_1++) {
		if (MFILE_EntryList[count_1].mfile_flags & MFILE_FLAG_IN_USE) {
			mclose(MFILE_EntryList + count_1);
			closed_count++;
		}
	}

	return(closed_count);
}

int mclose_no_unmap(mfile_ptr)
MFILE *mfile_ptr;
{
	int return_code = 0;

	if (mfile_ptr->mfile_flags & MFILE_FLAG_IN_USE) {
		free(mfile_ptr->file_name);
		fclose(mfile_ptr->file_ptr);
		memset(mfile_ptr, '\0', sizeof(*mfile_ptr));
	}
	else
		return_code = EOF;

	return(return_code);
}

int mclose_to_offset(mfile_ptr)
MFILE *mfile_ptr;
{
	if ((mfile_ptr->mfile_flags & MFILE_FLAG_IN_USE) &&
		(mfile_ptr->mfile_flags & MFILE_MODE_WRITE))
		mfile_ptr->file_size = mfile_ptr->current_offset;

	return(mclose(mfile_ptr));
}

