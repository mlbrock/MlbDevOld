/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Frees 'KML_COMMENT' structures.

	Revision History	:	1998-03-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <stdlib.h>

#include "kmlfunci.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	KML_FREE_Comment

	SYNOPSIS		:	void KML_FREE_Comment(ptr);

						KML_COMMENT *ptr;

	DESCRIPTION	:	Frees the members of a ''KML_COMMENT'' structure.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``ptr`` points to the ''KML_COMMENT''
						structure to be freed by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_FREE_CommentList
						KML_CMP_Comment
						KML_COPY_Comment
						KML_INIT_Comment
						KML_SCMP_Comment

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2014 Michael L. Brock

	OUTPUT INDEX:	KML_FREE_Comment
						Memory Functions:KML_FREE_Comment
						KML_COMMENT Functions:KML_FREE_Comment

	PUBLISH XREF:	KML_FREE_Comment

	PUBLISH NAME:	KML_FREE_Comment

	ENTRY CLASS	:	Memory Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_FREE_Comment(KML_COMMENT *ptr)
#else
void KML_FREE_Comment(ptr)
KML_COMMENT *ptr;
#endif /* #ifndef NARGS */
{
	if (ptr->start_ptr != NULL)
		free(ptr->start_ptr);
	if (ptr->end_ptr != NULL)
		free(ptr->end_ptr);

	KML_INIT_Comment(ptr);
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	KML_FREE_CommentList

	SYNOPSIS		:	void KML_FREE_CommentList(in_count, in_list);

						unsigned int  *in_count;

						KML_COMMENT  **in_list;

	DESCRIPTION	:	Frees the elements of an array of ''KML_COMMENT''
						structures.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_count`` is a pointer to the ''unsigned int'' which
						contains the number of elements in the array to which
						the ``in_list`` parameter points.

						(.) ``in_list`` is a pointer to the array of ''KML_COMMENT''
						structures to be freed by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_FREE_Comment
						KML_COPY_CommentList
						KML_INIT_CommentList
						KML_SORT_CommentList

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2014 Michael L. Brock

	OUTPUT INDEX:	KML_FREE_CommentList
						Memory Functions:KML_FREE_CommentList
						KML_COMMENT Functions:KML_FREE_CommentList

	PUBLISH XREF:	KML_FREE_CommentList

	PUBLISH NAME:	KML_FREE_CommentList

	ENTRY CLASS	:	Memory Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_FREE_CommentList(unsigned int *in_count, KML_COMMENT **in_list)
#else
void KML_FREE_CommentList(in_count, in_list)
unsigned int  *in_count;
KML_COMMENT  **in_list;
#endif /* #ifndef NARGS */
{
	while (*in_count)
		KML_FREE_Comment(*in_list + --(*in_count));

	if (*in_list != NULL)
		free(*in_list);

	*in_count = 0;
	*in_list  = NULL;
}
/*	***********************************************************************	*/

