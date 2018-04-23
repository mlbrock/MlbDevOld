/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MREGION Memory-mapped Region Library Source Code Module						*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Opens a file using 'open()' semantics and maps
								the file as a region (if it doesn't have 0-length).

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
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include <genfuncs.h>

#include "mregioni.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MRG_OpenFileWithMap(const char *file_name, MRG_OPEN_MODE open_mode,
	MRG_FIL **fil_ptr, char *error_text)
#else
int MRG_OpenFileWithMap(file_name, open_mode, fil_ptr, error_text)
const char     *file_name;
MRG_OPEN_MODE   open_mode;
MRG_FIL       **fil_ptr;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = MRG_OpenFile(file_name, open_mode, fil_ptr,
		error_text)) == MRG_SUCCESS) {
		if ((*fil_ptr)->file_length) {
			if ((return_code = MRG_MapRegToFil(*fil_ptr, ((MMI_ADDRESS) 0),
				((*fil_ptr)->file_length) ? (*fil_ptr)->file_length :
				MMI_GetPageSize(), ((MMI_OFFSET) 0), (*fil_ptr)->mmap_flags,
				(*fil_ptr)->prot_flags, error_text)) != MRG_SUCCESS) {
				MRG_CloseFil(*fil_ptr);
				*fil_ptr = NULL;
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

