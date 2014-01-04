#include <memory.h>
#include <stdlib.h>

#include <mfile.h>

COMPAT_EXTERN_DATA_DECL MFILE        *MFILE_EntryList;
COMPAT_EXTERN_DATA_DECL unsigned int  MFILE_EntryCount;

int munlink(mfile_ptr)
MFILE *mfile_ptr;
{
	int return_code = 0;

	if (mfile_ptr->mfile_flags & MFILE_FLAG_IN_USE) {
		fclose(mfile_ptr->file_ptr);
		unlink(mfile_ptr->file_name);
		free(mfile_ptr->file_name);
		memset(mfile_ptr, '\0', sizeof(*mfile_ptr));
	}
	else
		return_code = EOF;

	return(return_code);
}

