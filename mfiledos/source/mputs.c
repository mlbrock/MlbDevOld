#include <string.h>

#include "mfile.h"

int mputs(put_string, mfile_ptr)
const char  *put_string;
MFILE       *mfile_ptr;
{
	int          return_value = EOF;
	unsigned int string_length;

	if (!(string_length = strlen(put_string)))
		return_value = 0;
	else if (mwrite(put_string, sizeof(char), string_length, mfile_ptr) ==
		((int) string_length))
		return_value = string_length;

	return(return_value);
}

