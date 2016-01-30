/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Reads a file.

	Revision History	:	1994-06-10 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include "adf.h"

#include <stdlib.h>
#include <string.h>

#ifndef _Windows
# include <unistd.h>
#endif /* #ifndef _Windows */

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_ReadFileBuffer(const char *file_name, unsigned int *buffer_length,
	char **buffer_ptr, char *error_text)
#else
int ADF_ReadFileBuffer(file_name, buffer_length, buffer_ptr, error_text)
const char    *file_name;
unsigned int  *buffer_length;
char         **buffer_ptr;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code = ADF_SUCCESS;
	unsigned int   count_1;
	unsigned long  file_size;
	ADF_FILE      *file_ptr;

	if (buffer_length != NULL)
		*buffer_length = 0;

	*buffer_ptr = NULL;

	if ((file_ptr = ADF_fopen(file_name, "rb")) == NULL) {
		sprintf(error_text, "%s '%-.500s' for reading --- ",
			"Unable to open the file", file_name);
		ADF_GetLastErrorString(error_text);
		return_code = ADF_FAILURE;
	}
	else {
		ADF_fseek(file_ptr, 0L, SEEK_END);
		file_size = ADF_ftell(file_ptr);
		ADF_fseek(file_ptr, 0L, SEEK_SET);
		if (file_size) {
#ifdef __MSDOS__
			file_size = (file_size > 65500L) ? 65500L : file_size;
#endif /* #ifdef __MSDOS__ */
			if ((*buffer_ptr = ((char *) calloc(((unsigned int) file_size) + 1,
				sizeof(char)))) == NULL) {
				STR_AllocMsgItem(((unsigned int) file_size) + 1, error_text,
					"%s '%-.500s'",
					"Unable to allocate memory for a buffered copy of the file",
					file_name);
				return_code = ADF_MEMORY_FAILURE;
			}
			else if ((return_code = ADF_FRead(*buffer_ptr, sizeof(char),
				((unsigned int) file_size), file_ptr, error_text)) !=
				ADF_SUCCESS) {
				free(*buffer_ptr);
				*buffer_ptr = NULL;
			}
			else {
				for (count_1 = 0; count_1 < ((unsigned int) file_size); count_1++)
					(*buffer_ptr)[count_1] = ((char) ((!(*buffer_ptr)[count_1]) ?
						((char) ' ') : (*buffer_ptr)[count_1]));
				if (buffer_length != NULL)
					*buffer_length = ((unsigned int) file_size);
			}
		}
		ADF_fclose(file_ptr);
	}

	return(return_code);
}
/*	***********************************************************************	*/

