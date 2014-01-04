#include "mfile.h"

MFILE *mtmpfile(dir_name, file_prefix)
const char *dir_name;
const char *file_prefix;
{
	MFILE *return_ptr = NULL;
	char  *file_name;

	if ((file_name = tempnam(((char *) dir_name), ((char *) file_prefix))) !=
		NULL) {
		return_ptr = mopen(file_name, "w");
		free(file_name);
	}

	return(return_ptr);
}

