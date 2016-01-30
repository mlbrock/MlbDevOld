/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLOG Memory-mapped Logging Library Source Code Module							*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes an 'MLOG' structure.

	Revision History	:	1992-03-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include <memory.h>

#include "mlogi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	MLOG_Init

	SYNOPSIS		:	void MLOG_Init(mlog_ptr);

						MLOG *mlog_ptr;

	DESCRIPTION	:	Initializes the members of an ''MLOG'' structure
						to their default values.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``mlog_ptr`` points to the ''MLOG'' structure
						to be initialized by this function.

	RETURNS		:	Void.

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2016 Michael L. Brock

	OUTPUT INDEX:	MLOG_Init
						Initialization Functions:MLOG_Init

	PUBLISH XREF:	MLOG_Init

	PUBLISH NAME:	MLOG_Init

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MLOG_Init(MLOG *mlog_ptr)
#else
void MLOG_Init(mlog_ptr)
MLOG *mlog_ptr;
#endif /* #ifndef NARGS */
{
	memset(mlog_ptr, '\0', sizeof(*mlog_ptr));

	mlog_ptr->signature          = MLOG_SIGNATURE_NONE;
	mlog_ptr->mtr_data_init_flag = MLOG_FALSE;
	mlog_ptr->flags              = ((MLOG_FLAG) 0);
	mlog_ptr->mfile_mask         = ((MLOG_PRIORITY) 0);
	mlog_ptr->file_mask          = ((MLOG_PRIORITY) 0);
	mlog_ptr->syslog_mask        = ((MLOG_PRIORITY) 0);
	mlog_ptr->initial_alloc      = 0;
	mlog_ptr->added_alloc        = 0;
	mlog_ptr->log_format         = NULL;
	mlog_ptr->user_string        = NULL;
	mlog_ptr->format_count       = 0;
	mlog_ptr->format_list        = NULL;
	mlog_ptr->used_length        = 0;
	mlog_ptr->work_length        = 0;
	mlog_ptr->work_string        = NULL;
	mlog_ptr->mfile_ptr          = NULL;
	mlog_ptr->file_ptr           = NULL;
}
/*	***********************************************************************	*/

