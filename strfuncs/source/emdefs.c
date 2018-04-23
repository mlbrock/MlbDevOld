/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	STRFUNCS String and Memory Functions Library Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Sets an output handler function pointer and its
								associated control pointer to their default values
								('fprintf()' and 'stdout', respectively) if they
								are 'NULL'.

	Revision History	:	1992-04-02 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <stdio.h>

#include "strfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	STR_EMIT_SetDefaults

   SYNOPSIS    :	void STR_EMIT_SetDefaults(output_function, output_control);

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

   COPYRIGHT   :	Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	STR_EMIT_SetDefaults
						Miscellaneous Functions:STR_EMIT_SetDefaults
						STRFUNCS:Functions:STR_EMIT_SetDefaults
						STRFUNCS Miscellaneous Functions:STR_EMIT_SetDefaults
						General Functions:See STRFUNCS

   PUBLISH XREF:	STR_EMIT_SetDefaults

   PUBLISH NAME:	STR_EMIT_SetDefaults

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void STR_EMIT_SetDefaults(STR_FUNC_TYPE_fprintf *output_function,
	void **output_control)
#else
void STR_EMIT_SetDefaults(output_function, output_control)
STR_FUNC_TYPE_fprintf  *output_function;
void                  **output_control;
#endif /* #ifndef NARGS */
{
	*output_function = (*output_function != NULL) ? *output_function :
		STR_FUNC_TYPE_fprintf_CAST(fprintf);
	*output_control  = (*output_control  != NULL) ? *output_control  : stdout;
}
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#ifndef NARGS
void STR_EMIT_SetDefaultsVA(STR_FUNC_TYPE_vfprintf *output_function,
	void **output_control)
#else
void STR_EMIT_SetDefaultsVA(output_function, output_control)
STR_FUNC_TYPE_vfprintf  *output_function;
void                   **output_control;
#endif /* #ifndef NARGS */
{
	*output_function = (*output_function != NULL) ? *output_function :
		STR_FUNC_TYPE_vfprintf_CAST(vfprintf);
	*output_control  = (*output_control  != NULL) ? *output_control  : stdout;
}
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#ifndef NARGS
STR_CFILE_FUNCS *STR_EMIT_SetDefaultsCFILE_FUNCS(
	STR_CFILE_FUNCS *cfile_funcs_ptr)
#else
STR_CFILE_FUNCS *STR_EMIT_SetDefaultsCFILE_FUNCS(cfile_funcs_ptr)
STR_CFILE_FUNCS *cfile_funcs_ptr;
#endif /* #ifndef NARGS */
{
	return(STR_EMIT_GetDefaultsCFILE_FUNCS(cfile_funcs_ptr));
}
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#ifndef NARGS
STR_CFILE_FUNCS *STR_EMIT_GetDefaultsCFILE_FUNCS(
	STR_CFILE_FUNCS *cfile_funcs_ptr)
#else
STR_CFILE_FUNCS *STR_EMIT_GetDefaultsCFILE_FUNCS(cfile_funcs_ptr)
STR_CFILE_FUNCS *cfile_funcs_ptr;
#endif /* #ifndef NARGS */
{
	cfile_funcs_ptr->fopen_func    = STR_FUNC_TYPE_fopen_CAST(fopen);
	cfile_funcs_ptr->fclose_func   = STR_FUNC_TYPE_fclose_CAST(fclose);
	cfile_funcs_ptr->fread_func    = STR_FUNC_TYPE_fread_CAST(fread);
	cfile_funcs_ptr->fwrite_func   = STR_FUNC_TYPE_fwrite_CAST(fwrite);
	cfile_funcs_ptr->fgets_func    = STR_FUNC_TYPE_fgets_CAST(fgets);
	cfile_funcs_ptr->fputs_func    = STR_FUNC_TYPE_fputs_CAST(fputs);
	cfile_funcs_ptr->fgetc_func    = STR_FUNC_TYPE_fgetc_CAST(fgetc);
	cfile_funcs_ptr->fputc_func    = STR_FUNC_TYPE_fputc_CAST(fputc);
	cfile_funcs_ptr->fseek_func    = STR_FUNC_TYPE_fseek_CAST(fseek);
	cfile_funcs_ptr->ftell_func    = STR_FUNC_TYPE_ftell_CAST(ftell);
	cfile_funcs_ptr->fflush_func   = STR_FUNC_TYPE_fflush_CAST(fflush);
	cfile_funcs_ptr->rewind_func   = STR_FUNC_TYPE_rewind_CAST(rewind);
	cfile_funcs_ptr->fprintf_func  = STR_FUNC_TYPE_fprintf_CAST(fprintf);
	cfile_funcs_ptr->vfprintf_func = STR_FUNC_TYPE_vfprintf_CAST(vfprintf);

	return(cfile_funcs_ptr);
}
/*	***********************************************************************	*/

