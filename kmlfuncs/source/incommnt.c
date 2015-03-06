/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes 'KML_COMMENT' structures.

	Revision History	:	1998-03-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2015.
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

#include "kmlfunci.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	KML_INIT_Comment

	SYNOPSIS		:	void KML_INIT_Comment(ptr);

						KML_COMMENT *ptr;

	DESCRIPTION	:	Initializes the members of a ''KML_COMMENT''
						structure to their default values.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``ptr`` points to the ''KML_COMMENT''
						structure to be initialized by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_INIT_CommentList
						KML_CMP_Comment
						KML_COPY_Comment
						KML_FREE_Comment
						KML_SCMP_Comment

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2015 Michael L. Brock

	OUTPUT INDEX:	KML_INIT_Comment
						Initialization Functions:KML_INIT_Comment
						KML_COMMENT Functions:KML_INIT_Comment

	PUBLISH XREF:	KML_INIT_Comment

	PUBLISH NAME:	KML_INIT_Comment

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_INIT_Comment(KML_COMMENT *ptr)
#else
void KML_INIT_Comment(ptr)
KML_COMMENT *ptr;
#endif /* #ifndef NARGS */
{
	memset(ptr, '\0', sizeof(*ptr));

	ptr->start_ptr    = NULL;
	ptr->start_length = 0;
	ptr->end_ptr      = NULL;
	ptr->end_length   = 0;
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	KML_INIT_CommentList

	SYNOPSIS		:	void KML_INIT_CommentList(in_count, in_list);

						unsigned int  in_count;

						KML_COMMENT  *in_list;

	DESCRIPTION	:	Initializes the elements of a array of ''KML_COMMENT''
						structures to their default values.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_count`` is the number of elements in the array
						``in_list``.

						(.) ``in_list`` is the array of ''KML_COMMENT''
						structures to be initialized by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_INIT_Comment
						KML_COPY_CommentList
						KML_FREE_CommentList
						KML_SORT_CommentList

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2015 Michael L. Brock

	OUTPUT INDEX:	KML_INIT_CommentList
						Initialization Functions:KML_INIT_CommentList
						KML_COMMENT Functions:KML_INIT_CommentList

	PUBLISH XREF:	KML_INIT_CommentList

	PUBLISH NAME:	KML_INIT_CommentList

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_INIT_CommentList(unsigned int in_count, KML_COMMENT *in_list)
#else
void KML_INIT_CommentList(in_count, in_list)
unsigned int  in_count;
KML_COMMENT  *in_list;
#endif /* #ifndef NARGS */
{
	while (in_count--)
		KML_INIT_Comment(in_list++);
}
/*	***********************************************************************	*/

