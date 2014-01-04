/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Manages use FrameMaker-specific data.

	Revision History	:	1996-09-08 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <memory.h>
#include <stdlib.h>

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_InitDataFRAME(ADF_FRAME_DATA *frame_data_ptr)
#else
void ADF_InitDataFRAME(frame_data_ptr)
ADF_FRAME_DATA *frame_data_ptr;
#endif /* #ifndef NARGS */
{
	memset(frame_data_ptr, '\0', sizeof(*frame_data_ptr));

	frame_data_ptr->document_name = NULL;
	frame_data_ptr->owner_name    = NULL;
	frame_data_ptr->copyright     = NULL;
	frame_data_ptr->document_name = NULL;
	frame_data_ptr->cover_name_1  = NULL;
	frame_data_ptr->cover_name_2  = NULL;
	frame_data_ptr->long_name     = NULL;
	frame_data_ptr->short_name    = NULL;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_FreeDataFRAME(ADF_FRAME_DATA *frame_data_ptr)
#else
void ADF_FreeDataFRAME(frame_data_ptr)
ADF_FRAME_DATA *frame_data_ptr;
#endif /* #ifndef NARGS */
{
	if (frame_data_ptr->document_name != NULL)
		free(frame_data_ptr->document_name);

	if (frame_data_ptr->owner_name != NULL)
		free(frame_data_ptr->owner_name);

	if (frame_data_ptr->copyright != NULL)
		free(frame_data_ptr->copyright);

	if (frame_data_ptr->cover_name_1 != NULL)
		free(frame_data_ptr->cover_name_1);

	if (frame_data_ptr->cover_name_2 != NULL)
		free(frame_data_ptr->cover_name_2);

	if (frame_data_ptr->long_name != NULL)
		free(frame_data_ptr->long_name);

	if (frame_data_ptr->short_name != NULL)
		free(frame_data_ptr->short_name);

	ADF_InitDataFRAME(frame_data_ptr);
}
/*	***********************************************************************	*/

