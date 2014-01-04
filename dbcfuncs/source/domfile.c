/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Generalized Support Functions Library Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Handles row allocation for the DBC 'get_rows_basic'
								functionality using the MFILE library routines.

	Revision History	:	1993-07-11 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include "dbcfunci.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	

	SYNOPSIS		:	

	DESCRIPTION	:	

	PARAMETERS	:	

	RETURNS		:	

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2014 Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DBC_MFILE_ALLOC_Rows(MFILE *alloc_control_ptr, void **memory_ptr,
	unsigned int alloc_size)
#else
int DBC_MFILE_ALLOC_Rows(alloc_control_ptr, memory_ptr, alloc_size)
MFILE         *alloc_control_ptr;
void         **memory_ptr;
unsigned int   alloc_size;
#endif /* #ifndef NARGS */
{
	int return_code = DBC_SUCCESS;

	if (!mtruncate_safe(alloc_control_ptr,
		MFILE_GetFileSize(alloc_control_ptr) + alloc_size))
		*memory_ptr = ((void *) MFILE_GetMMapPtr(alloc_control_ptr));
	else
		return_code = DBC_MEMORY_FAILURE;

	return(return_code);
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	

	SYNOPSIS		:	

	DESCRIPTION	:	

	PARAMETERS	:	

	RETURNS		:	

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2014 Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DBC_MFILE_REALLOC_Rows(MFILE *alloc_control_ptr, void **memory_ptr,
	unsigned int old_size, unsigned int alloc_size)
#else
int DBC_MFILE_REALLOC_Rows(alloc_control_ptr, memory_ptr, old_size,
	alloc_size)
MFILE         *alloc_control_ptr;
void         **memory_ptr;
unsigned int   old_size;
unsigned int   alloc_size;
#endif /* #ifndef NARGS */
{
	int          return_code = DBC_SUCCESS;
	unsigned int new_size;
	unsigned int file_size;

	file_size = ((unsigned int) MFILE_GetFileSize(alloc_control_ptr));
	new_size  = (alloc_size == old_size) ? file_size :
		(alloc_size > old_size) ?
		(file_size + (alloc_size - old_size)) :
		(file_size - (old_size - alloc_size));

	if (!mtruncate_safe(alloc_control_ptr, new_size))
		*memory_ptr = ((void *) MFILE_GetMMapPtr(alloc_control_ptr));
	else
		return_code = DBC_MEMORY_FAILURE;

	return(return_code);
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	

	SYNOPSIS		:	

	DESCRIPTION	:	

	PARAMETERS	:	

	RETURNS		:	

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2014 Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
#ifndef NARGS
void DBC_MFILE_FREE_Rows(MFILE *alloc_control_ptr, void **memory_ptr,
	unsigned int free_size)
#else
void DBC_MFILE_FREE_Rows(alloc_control_ptr, memory_ptr, free_size)
MFILE         *alloc_control_ptr;
void         **memory_ptr;
unsigned int   free_size;
#endif /* #ifndef NARGS */
{
	unsigned int file_size;

	file_size = ((unsigned int) MFILE_GetFileSize(alloc_control_ptr));

	if (free_size && (free_size >= file_size))
		mtruncate_safe(alloc_control_ptr, file_size - free_size);

	*memory_ptr = NULL;
}
/*	***********************************************************************	*/

