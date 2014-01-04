/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	TFREAD Text File Reading Functions Library Source Module						*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Reads lines from a file.

	Revision History	:	1991-04-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1991 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <string.h>

#include "tfreadi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int TFREAD_ReadLines(const char *file_name, unsigned int *line_count,
	char ***line_list, char *error_text)
#else
int TFREAD_ReadLines(file_name, line_count, line_list, error_text)
const char     *file_name;
unsigned int   *line_count;
char         ***line_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	return(TFREAD_ReadLinesFILE(file_name, line_count, line_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int TFREAD_ReadLinesBasic(const STR_CFILE_FUNCS *tfread_ptr, const char *file_name,
	unsigned int *line_count, char ***line_list, char *error_text)
#else
int TFREAD_ReadLinesBasic(tfread_ptr, file_name, line_count, line_list,
	error_text)
const STR_CFILE_FUNCS   *tfread_ptr;
const char     *file_name;
unsigned int   *line_count;
char         ***line_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code;
	unsigned int   tmp_count;
	char         **tmp_list;

	*line_count = 0;
	*line_list  = NULL;

	if (((return_code = TFREAD_ReadLinesNoAllocBasic(tfread_ptr, file_name,
		&tmp_count, &tmp_list, error_text)) == TFREAD_SUCCESS) && tmp_count) {
		if (strl_copy(tmp_count, tmp_list, line_count, line_list) !=
			STRFUNCS_SUCCESS) {
			STR_AllocMsgPtrList(tmp_count, strlen(*tmp_list) + 1, error_text,
				"%s '%-.500s'",
				"Unable to allocate the list of strings representing file",
				file_name);
			return_code = TFREAD_MEMORY_FAILURE;
		}
		free(*tmp_list);
		free(tmp_list);
	}

	return(return_code);
}
/*	***********************************************************************	*/

