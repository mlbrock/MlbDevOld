/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Frees 'KML_BLOCK' structures.

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

	NAME			:	KML_FREE_Block

	SYNOPSIS		:	void KML_FREE_Block(ptr);

						KML_BLOCK *ptr;

	DESCRIPTION	:	Frees the members of a ''KML_BLOCK'' structure.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``ptr`` points to the ''KML_BLOCK''
						structure to be freed by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_FREE_BlockList
						KML_CMP_Block
						KML_COPY_Block
						KML_INIT_Block
						KML_SCMP_Block

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2014 Michael L. Brock

	OUTPUT INDEX:	KML_FREE_Block
						Memory Functions:KML_FREE_Block
						KML_BLOCK Functions:KML_FREE_Block

	PUBLISH XREF:	KML_FREE_Block

	PUBLISH NAME:	KML_FREE_Block

	ENTRY CLASS	:	Memory Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_FREE_Block(KML_BLOCK *ptr)
#else
void KML_FREE_Block(ptr)
KML_BLOCK *ptr;
#endif /* #ifndef NARGS */
{
	if (ptr->start_ptr != NULL)
		free(ptr->start_ptr);
	if (ptr->end_ptr != NULL)
		free(ptr->end_ptr);

	KML_INIT_Block(ptr);
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	KML_FREE_BlockList

	SYNOPSIS		:	void KML_FREE_BlockList(in_count, in_list);

						unsigned int  *in_count;

						KML_BLOCK    **in_list;

	DESCRIPTION	:	Frees the elements of an array of ''KML_BLOCK''
						structures.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_count`` is a pointer to the ''unsigned int'' which
						contains the number of elements in the array to which
						the ``in_list`` parameter points.

						(.) ``in_list`` is a pointer to the array of ''KML_BLOCK''
						structures to be freed by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_FREE_Block
						KML_COPY_BlockList
						KML_INIT_BlockList
						KML_SORT_BlockList

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2014 Michael L. Brock

	OUTPUT INDEX:	KML_FREE_BlockList
						Memory Functions:KML_FREE_BlockList
						KML_BLOCK Functions:KML_FREE_BlockList

	PUBLISH XREF:	KML_FREE_BlockList

	PUBLISH NAME:	KML_FREE_BlockList

	ENTRY CLASS	:	Memory Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_FREE_BlockList(unsigned int *in_count, KML_BLOCK **in_list)
#else
void KML_FREE_BlockList(in_count, in_list)
unsigned int  *in_count;
KML_BLOCK    **in_list;
#endif /* #ifndef NARGS */
{
	while (*in_count)
		KML_FREE_Block(*in_list + --(*in_count));

	if (*in_list != NULL)
		free(*in_list);

	*in_count = 0;
	*in_list  = NULL;
}
/*	***********************************************************************	*/

