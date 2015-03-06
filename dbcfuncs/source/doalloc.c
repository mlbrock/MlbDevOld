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
								functionality using the C standard library memory
								allocation routines.

	Revision History	:	1993-07-11 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2015.
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
#include <stdlib.h>

#include "dbcfunci.h"

/*	***********************************************************************	*/

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
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

   COPYRIGHT   :	Copyright 1993 - 2015 Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DBC_MEMORY_ALLOC_Rows(void *alloc_control_ptr, void **memory_ptr,
	unsigned int alloc_size)
#else
int DBC_MEMORY_ALLOC_Rows(alloc_control_ptr, memory_ptr, alloc_size)
void          *alloc_control_ptr;
void         **memory_ptr;
unsigned int   alloc_size;
#endif /* #ifndef NARGS */
{
	int return_code = DBC_SUCCESS;

	if ((*memory_ptr = malloc(alloc_size)) == NULL)
		return_code = DBC_MEMORY_FAILURE;

	return(return_code);
}
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
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

   COPYRIGHT   :	Copyright 1993 - 2015 Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DBC_MEMORY_REALLOC_Rows(void *alloc_control_ptr, void **memory_ptr,
	unsigned int old_size, unsigned int alloc_size)
#else
int DBC_MEMORY_REALLOC_Rows(alloc_control_ptr, memory_ptr, old_size,
	alloc_size)
void          *alloc_control_ptr;
void         **memory_ptr;
unsigned int   old_size;
unsigned int   alloc_size;
#endif /* #ifndef NARGS */
{
	int   return_code = DBC_SUCCESS;
	void *tmp_ptr;

	if ((tmp_ptr = realloc(*memory_ptr, alloc_size)) != NULL)
		*memory_ptr = tmp_ptr;
	else
		return_code = DBC_MEMORY_FAILURE;

	return(return_code);
}
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
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

   COPYRIGHT   :	Copyright 1993 - 2015 Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
#ifndef NARGS
void DBC_MEMORY_FREE_Rows(void *alloc_control_ptr, void **memory_ptr,
	unsigned int free_size)
#else
void DBC_MEMORY_FREE_Rows(alloc_control_ptr, memory_ptr, free_size)
void          *alloc_control_ptr;
void         **memory_ptr;
unsigned int   free_size;
#endif /* #ifndef NARGS */
{
	if ((free_size) && (*memory_ptr != NULL))
		free(*memory_ptr);

	*memory_ptr = NULL;
}
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

