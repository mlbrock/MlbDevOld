/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MFILE Memory-mapped I/O Library Source Code Module								*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Ensures that there is sufficient space for an MFILE
								write operation.

	Revision History	:	1992-03-21 --- Creation.
									Michael L. Brock
*/
/*	***********************************************************************	*/
 
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include <genfuncs.h>

#include "mfile.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  MFILE_EnsureSpace

   SYNOPSIS    :  truth_flag = MFILE_EnsureSpace(mfile_ptr, in_buffer_size,
							in_min_size, error_text);

						int           return_code;

						MFILE        *mfile_ptr;

						unsigned int  in_buffer_size;

						unsigned int  in_min_size;

						char         *error_text;

   DESCRIPTION :  Ensures that there is sufficient space in the memory-mapped
						file to support a minimum buffer size.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``mfile_ptr``, which is the pointer to a structure of
						type ''MFILE''.

						(.) ``in_buffer_size`` is the chunk size in which
						allocations of the memory-mapped file should take place.

						(.) ``in_min_size`` is the minimum amount of space which
						must be available after this function returns.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''MFILE_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''MFILE_SUCCESS'' if the function completes without
						error. ''MFILE_SUCCESS'' is guaranteed to be equal to
						zero (0).

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  mprintf_ensure_space

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 1999
						Michael L. Brock

	OUTPUT INDEX:	MFILE_EnsureSpace
						Memory-mapped File Functions:Miscellaneous Functions:MFILE_EnsureSpace
						MFILE Functions:MFILE_EnsureSpace

	PUBLISH XREF:	MFILE_EnsureSpace

	PUBLISH NAME:	MFILE_EnsureSpace

	ENTRY CLASS	:	Memory-mapped File Functions:Miscellaneous Functions

EOH */
/* *********************************************************************** */
int MFILE_EnsureSpace(mfile_ptr, in_buffer_size, in_min_size, error_text)
MFILE        *mfile_ptr;
unsigned int  in_buffer_size;
unsigned int  in_min_size;
char         *error_text;
{
	int           return_code = MFILE_SUCCESS;
	unsigned long buffer_size;
	unsigned long new_size;

	if ((mfile_ptr != NULL) && (!MFILE_ValidateMFILEPtr(mfile_ptr)) &&
		(mfile_ptr->mfile_flags & MFILE_MODE_WRITE) && in_min_size) {
		buffer_size = (mfile_ptr->buffer_size > in_buffer_size) ?
			mfile_ptr->buffer_size : in_buffer_size;
		buffer_size = (buffer_size > in_min_size) ? buffer_size : in_min_size;
		if ((new_size = (mfile_ptr->mmap_size - mfile_ptr->current_offset)) <
			in_min_size) {
			new_size = mfile_ptr->mmap_size + buffer_size;
			STRFUNCS_ADJUST_SIZE(new_size, MFILE_getpagesize);
			if (!mtruncate_safe(mfile_ptr, new_size))
				mfile_ptr->file_size = mfile_ptr->current_offset;
			else {
				if (error_text != NULL)
					sprintf(error_text, "%s '%.500s' %s %lu %s %lu %s.",
						"Attempt to 'mtruncate_safe()' the file",
						MFILE_GET_file_name(mfile_ptr), "from an mmap size of",
						mfile_ptr->mmap_size, "to an mmap size of", new_size,
					"failed");
				return_code = MFILE_FAILURE;
			}
		}
	}

	return(return_code);
}
/* *********************************************************************** */

