/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Handles row allocation for the DCR library function
								'DCR_GetMultipleRowsGeneral()'.

	Revision History	:	1994-03-14 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include "dcr.h"

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

	COPYRIGHT	:	Copyright 1994 - 2015 Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
int DCR_ALLOC_Rows(cache_ptr, memory_ptr, alloc_size)
DCR_CACHE     *cache_ptr;
void         **memory_ptr;
unsigned int   alloc_size;
{
	int  return_code = DCR_SUCCESS;
	char error_text[DCR_MAX_ERROR_TEXT];

	if ((return_code = DCR_TruncateCache(cache_ptr,
		cache_ptr->mmap_size + alloc_size, error_text)) == DCR_SUCCESS)
		*memory_ptr = ((char *) cache_ptr->mmap_ptr) +
			cache_ptr->header_ptr->data_area_offset;
	else
		return_code = DCR_MEMORY_FAILURE;

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

	COPYRIGHT	:	Copyright 1994 - 2015 Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
int DCR_REALLOC_Rows(cache_ptr, memory_ptr, old_size, alloc_size)
DCR_CACHE     *cache_ptr;
void         **memory_ptr;
unsigned int   old_size;
unsigned int   alloc_size;
{
	int          return_code = DCR_SUCCESS;
	unsigned int new_size;
	char   error_text[DCR_MAX_ERROR_TEXT];

	new_size = (alloc_size == old_size) ? cache_ptr->mmap_size :
		(alloc_size > old_size) ?
		(cache_ptr->mmap_size + (alloc_size - old_size)) :
		(cache_ptr->mmap_size - (old_size - alloc_size));

	if ((return_code = DCR_TruncateCache(cache_ptr, new_size,
		error_text)) == DCR_SUCCESS)
		*memory_ptr = ((char *) cache_ptr->mmap_ptr) +
			cache_ptr->header_ptr->data_area_offset;
	else
		return_code = DCR_MEMORY_FAILURE;

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

	COPYRIGHT	:	Copyright 1994 - 2015 Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
void DCR_FREE_Rows(cache_ptr, memory_ptr, free_size)
DCR_CACHE     *cache_ptr;
void         **memory_ptr;
unsigned int   free_size;
{
	char error_text[DCR_MAX_ERROR_TEXT];

	if (free_size)
		DCR_TruncateCache(cache_ptr, cache_ptr->mmap_size - free_size,
			error_text);

	*memory_ptr = NULL;
}
/*	***********************************************************************	*/

