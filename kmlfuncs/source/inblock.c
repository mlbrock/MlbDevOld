/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes 'KML_BLOCK' structures.

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

	NAME			:	KML_INIT_Block

	SYNOPSIS		:	void KML_INIT_Block(ptr);

						KML_BLOCK *ptr;

	DESCRIPTION	:	Initializes the members of a ''KML_BLOCK''
						structure to their default values.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``ptr`` points to the ''KML_BLOCK''
						structure to be initialized by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_INIT_BlockList
						KML_CMP_Block
						KML_COPY_Block
						KML_FREE_Block
						KML_SCMP_Block

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2015 Michael L. Brock

	OUTPUT INDEX:	KML_INIT_Block
						Initialization Functions:KML_INIT_Block
						KML_BLOCK Functions:KML_INIT_Block

	PUBLISH XREF:	KML_INIT_Block

	PUBLISH NAME:	KML_INIT_Block

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_INIT_Block(KML_BLOCK *ptr)
#else
void KML_INIT_Block(ptr)
KML_BLOCK *ptr;
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

	NAME			:	KML_INIT_BlockList

	SYNOPSIS		:	void KML_INIT_BlockList(in_count, in_list);

						unsigned int  in_count;

						KML_BLOCK    *in_list;

	DESCRIPTION	:	Initializes the elements of a array of ''KML_BLOCK''
						structures to their default values.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_count`` is the number of elements in the array
						``in_list``.

						(.) ``in_list`` is the array of ''KML_BLOCK''
						structures to be initialized by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_INIT_Block
						KML_COPY_BlockList
						KML_FREE_BlockList
						KML_SORT_BlockList

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2015 Michael L. Brock

	OUTPUT INDEX:	KML_INIT_BlockList
						Initialization Functions:KML_INIT_BlockList
						KML_BLOCK Functions:KML_INIT_BlockList

	PUBLISH XREF:	KML_INIT_BlockList

	PUBLISH NAME:	KML_INIT_BlockList

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_INIT_BlockList(unsigned int in_count, KML_BLOCK *in_list)
#else
void KML_INIT_BlockList(in_count, in_list)
unsigned int  in_count;
KML_BLOCK    *in_list;
#endif /* #ifndef NARGS */
{
	while (in_count--)
		KML_INIT_Block(in_list++);
}
/*	***********************************************************************	*/

