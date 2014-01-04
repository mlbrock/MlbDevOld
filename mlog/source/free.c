/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLOG Memory-mapped Logging Library Source Code Module							*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Frees the members of an 'MLOG' structure.

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

#include "mlogi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	MLOG_Free

	SYNOPSIS		:	void MLOG_Free(mlog_ptr);

						MLOG *mlog_ptr;

	DESCRIPTION	:	Frees the members of an ''MLOG'' structure.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``mlog_ptr`` points to the ''MLOG'' structure
						to be freed by this function.

	RETURNS		:	Void.

	SEE ALSO		:	MLOG_Init

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2014 Michael L. Brock

	OUTPUT INDEX:	MLOG_Free
						Memory Management Functions:MLOG_Free

	PUBLISH XREF:	MLOG_Free

	PUBLISH NAME:	MLOG_Free

	ENTRY CLASS	:	Memory Management Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MLOG_Free(MLOG *mlog_ptr)
#else
void MLOG_Free(mlog_ptr)
MLOG *mlog_ptr;
#endif /* #ifndef NARGS */
{
	if (mlog_ptr->log_format != NULL)
		free(mlog_ptr->log_format);

	if (mlog_ptr->user_string != NULL)
		free(mlog_ptr->user_string);

	if (mlog_ptr->format_list != NULL)
		free(mlog_ptr->format_list);

	if (mlog_ptr->work_string != NULL)
		free(mlog_ptr->work_string);

	MLOG_Init(mlog_ptr);

	free(mlog_ptr);
}
/*	***********************************************************************	*/

