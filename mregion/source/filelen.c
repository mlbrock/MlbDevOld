/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MRG Memory-mapped Region Library Source Code Module							*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Determines the length of an open file.

	Revision History	:	1992-03-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include <sdtif.h>		/* Win32 MWCW needs this included before sys/types.h */

#include <sys/types.h>
#include <sys/stat.h>

#include <genfuncs.h>

#include "mregioni.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MRG_GetFileSize(MRG_FIL *fil_ptr, char *error_text)
#else
int MRG_GetFileSize(fil_ptr, error_text)
MRG_FIL *fil_ptr;
char    *error_text;
#endif /* #ifndef NARGS */
{
	int         return_code;
	struct stat stat_data;

	if ((return_code = MRG_CheckFil(fil_ptr, error_text)) == MRG_SUCCESS) {
		if (!fstat(fil_ptr->file_handle, &stat_data))
			fil_ptr->file_length = ((MMI_LENGTH) stat_data.st_size);
		else {
			if (error_text != NULL) {
				sprintf(error_text, "Error on 'fstat(%d, 0x%lx): ",
					fil_ptr->file_handle, ((unsigned long) &stat_data));
				GEN_AppendLastErrorString(0, MRG_MAX_ERROR_TEXT / 2,
					error_text);
			}
			return_code = MRG_SYSTEM_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

