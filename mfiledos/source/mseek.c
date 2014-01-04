#include "mfile.h"

int mseek(mfile_ptr, offset, position_type)
MFILE *mfile_ptr;
long   offset;
int    position_type;
{
	int return_code;

	if ((return_code = MFILE_ValidateMFILEPtr(mfile_ptr)) == 0) {
		fseek(mfile_ptr->file_ptr, offset, position_type);
		mfile_ptr->current_offset = ((long) ftell(mfile_ptr->file_ptr));
	}

	return(return_code);
}

