/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes 'KML_INDEX' structures.

	Revision History	:	1998-03-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2018.
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

	NAME			:	KML_INIT_Index

	SYNOPSIS		:	void KML_INIT_Index(ptr);

						KML_INDEX *ptr;

	DESCRIPTION	:	Initializes the members of a ''KML_INDEX''
						structure to their default values.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``ptr`` points to the ''KML_INDEX''
						structure to be initialized by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_INIT_IndexList

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2018 Michael L. Brock

	OUTPUT INDEX:	KML_INIT_Index
						Initialization Functions:KML_INIT_Index
						KML_INDEX Functions:KML_INIT_Index

	PUBLISH XREF:	KML_INIT_Index

	PUBLISH NAME:	KML_INIT_Index

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_INIT_Index(KML_INDEX *ptr)
#else
void KML_INIT_Index(ptr)
KML_INDEX *ptr;
#endif /* #ifndef NARGS */
{
	memset(ptr, '\0', sizeof(*ptr));

	ptr->item_ptr = NULL;
	ptr->count    = 0;
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	KML_INIT_IndexList

	SYNOPSIS		:	void KML_INIT_IndexList(in_count, in_list);

						unsigned int  in_count;

						KML_INDEX    *in_list;

	DESCRIPTION	:	Initializes the elements of a array of ''KML_INDEX''
						structures to their default values.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_count`` is the number of elements in the array
						``in_list``.

						(.) ``in_list`` is the array of ''KML_INDEX''
						structures to be initialized by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_INIT_Index

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2018 Michael L. Brock

	OUTPUT INDEX:	KML_INIT_IndexList
						Initialization Functions:KML_INIT_IndexList
						KML_INDEX Functions:KML_INIT_IndexList

	PUBLISH XREF:	KML_INIT_IndexList

	PUBLISH NAME:	KML_INIT_IndexList

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_INIT_IndexList(unsigned int in_count, KML_INDEX *in_list)
#else
void KML_INIT_IndexList(in_count, in_list)
unsigned int  in_count;
KML_INDEX    *in_list;
#endif /* #ifndef NARGS */
{
	while (in_count--)
		KML_INIT_Index(in_list++);
}
/*	***********************************************************************	*/

