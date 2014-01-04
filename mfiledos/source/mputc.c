#include "mfile.h"

int mputc(put_char, mfile_ptr)
int    put_char;
MFILE *mfile_ptr;
{
	int  return_value = EOF;
	char tmp_char     = ((char) put_char);

	if (mwrite(&tmp_char, sizeof(char), 1, mfile_ptr) == 1)
		return_value = put_char;

	return(return_value);
}

