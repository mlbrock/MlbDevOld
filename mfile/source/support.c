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

		Copyright Michael L. Brock 1992 - 2014.
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

#include "mfilei.h"

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

	COPYRIGHT	:	Copyright 1992 - 2014 Michael L. Brock

	OUTPUT INDEX:	MFILE_EnsureSpace
						Memory-mapped File Functions:Miscellaneous Functions:MFILE_EnsureSpace
						MFILE Functions:MFILE_EnsureSpace

	PUBLISH XREF:	MFILE_EnsureSpace

	PUBLISH NAME:	MFILE_EnsureSpace

	ENTRY CLASS	:	Memory-mapped File Functions:Miscellaneous Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int MFILE_EnsureSpace(MFILE *mfile_ptr, unsigned int in_buffer_size,
	unsigned int in_min_size, char *error_text)
#else
int MFILE_EnsureSpace(mfile_ptr, in_buffer_size, in_min_size, error_text)
MFILE        *mfile_ptr;
unsigned int  in_buffer_size;
unsigned int  in_min_size;
char         *error_text;
#endif /* #ifndef NARGS */
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
						MFILE_GET_FILE_NAME_I(mfile_ptr), "from an mmap size of",
						mfile_ptr->mmap_size, "to an mmap size of", new_size,
						"failed");
				return_code = MFILE_FAILURE;
			}
		}
	}

	return(return_code);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MFILE_EMIT_SetDefaults

   SYNOPSIS    :	void MFILE_EMIT_SetDefaults(output_function, output_control);

						STR_FUNC_TYPE_fprintf  *output_function;

						void                  **output_control;

   DESCRIPTION :	Sets an output handler function pointer and its associated
						control pointer to their default values if they are
						''NULL''.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``output_function`` points to a pointer to a function
						which handles output. If the pointer to which
						``output_function`` points is ''NULL'', the function will
						set it to ``fprintf``.

						(.) ``output_control`` points to a pointer to be used as
						the first parameter to the function specified by the
						``output_function`` parameter. If the pointer to which
						``output_control`` points is ''NULL'', the function will
						set it to ``stdout``.

   RETURNS     :	Void.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1992 - 2014 Michael L. Brock

   OUTPUT INDEX:	MFILE_EMIT_SetDefaults
						Memory-mapped File Functions:Miscellaneous Functions:MFILE_EMIT_SetDefaults
						Memory-mapped File Functions:Miscellaneous Functions:MFILE_EMIT_SetDefaults

   PUBLISH XREF:	MFILE_EMIT_SetDefaults

   PUBLISH NAME:	MFILE_EMIT_SetDefaults

	ENTRY CLASS	:	Memory-mapped File Functions:Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MFILE_EMIT_SetDefaults(STR_FUNC_TYPE_fprintf *output_function,
	void **output_control)
#else
void MFILE_EMIT_SetDefaults(output_function, output_control)
STR_FUNC_TYPE_fprintf  *output_function;
void                  **output_control;
#endif /* #ifndef NARGS */
{
	*output_function = (*output_function != NULL) ? *output_function :
		STR_FUNC_TYPE_fprintf_CAST(mprintf);
	*output_control  = (*output_control  != NULL) ? *output_control  : NULL;
}
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#ifndef NARGS
void MFILE_EMIT_SetDefaultsVA(STR_FUNC_TYPE_vfprintf *output_function,
	void **output_control)
#else
void MFILE_EMIT_SetDefaultsVA(output_function, output_control)
STR_FUNC_TYPE_vfprintf  *output_function;
void                   **output_control;
#endif /* #ifndef NARGS */
{
	*output_function = (*output_function != NULL) ? *output_function :
		STR_FUNC_TYPE_vfprintf_CAST(vmprintf);
	*output_control  = (*output_control  != NULL) ? *output_control  : NULL;
}
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#ifndef NARGS
STR_CFILE_FUNCS *MFILE_EMIT_SetDefaultsCFILE_FUNCS(
	STR_CFILE_FUNCS *cfile_funcs_ptr)
#else
STR_CFILE_FUNCS *MFILE_EMIT_SetDefaultsCFILE_FUNCS(cfile_funcs_ptr)
STR_CFILE_FUNCS *cfile_funcs_ptr;
#endif /* #ifndef NARGS */
{
	return(MFILE_EMIT_GetDefaultsCFILE_FUNCS(cfile_funcs_ptr));
}
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#ifndef NARGS
STR_CFILE_FUNCS *MFILE_EMIT_GetDefaultsCFILE_FUNCS(
	STR_CFILE_FUNCS *cfile_funcs_ptr)
#else
STR_CFILE_FUNCS *MFILE_EMIT_GetDefaultsCFILE_FUNCS(cfile_funcs_ptr)
STR_CFILE_FUNCS *cfile_funcs_ptr;
#endif /* #ifndef NARGS */
{
	cfile_funcs_ptr->fopen_func    = STR_FUNC_TYPE_fopen_CAST(mopen);
	cfile_funcs_ptr->fclose_func   = STR_FUNC_TYPE_fclose_CAST(mclose);
	cfile_funcs_ptr->fread_func    = STR_FUNC_TYPE_fread_CAST(mread);
	cfile_funcs_ptr->fwrite_func   = STR_FUNC_TYPE_fwrite_CAST(mwrite);
	cfile_funcs_ptr->fgets_func    = STR_FUNC_TYPE_fgets_CAST(mgets);
	cfile_funcs_ptr->fputs_func    = STR_FUNC_TYPE_fputs_CAST(mputs);
	cfile_funcs_ptr->fgetc_func    = STR_FUNC_TYPE_fgetc_CAST(mgetc);
	cfile_funcs_ptr->fputc_func    = STR_FUNC_TYPE_fputc_CAST(mputc);
	cfile_funcs_ptr->fseek_func    = STR_FUNC_TYPE_fseek_CAST(mseek);
	cfile_funcs_ptr->ftell_func    = STR_FUNC_TYPE_ftell_CAST(mtell);
	cfile_funcs_ptr->fflush_func   = STR_FUNC_TYPE_fflush_CAST(mflush);
	cfile_funcs_ptr->rewind_func   = STR_FUNC_TYPE_rewind_CAST(mrewind);
	cfile_funcs_ptr->fprintf_func  = STR_FUNC_TYPE_fprintf_CAST(mprintf);
	cfile_funcs_ptr->vfprintf_func = STR_FUNC_TYPE_vfprintf_CAST(vmprintf);

	return(cfile_funcs_ptr);
}
/*	***********************************************************************	*/

