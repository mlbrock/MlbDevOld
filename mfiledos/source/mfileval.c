#include "mfile.h"

COMPAT_EXTERN_DATA_DECL MFILE        *MFILE_EntryList;
COMPAT_EXTERN_DATA_DECL unsigned int  MFILE_EntryCount;

int MFILE_ValidateMFILEPtr(mfile_ptr)
MFILE *mfile_ptr;
{
	int return_code = 0;

	if ((MFILE_EntryList == NULL) || (mfile_ptr < MFILE_EntryList) ||
		(((((char *) mfile_ptr) - ((char *) MFILE_EntryList)) /
		sizeof(MFILE_EntryList[0])) > MFILE_EntryCount) ||
		((((char *) mfile_ptr) - ((char *) MFILE_EntryList)) %
		sizeof(MFILE_EntryList[0])))
		return_code = -1;
	else if (!(mfile_ptr->mfile_flags & MFILE_FLAG_IN_USE)) {
		return_code = -1;
	}

	return(return_code);
}

