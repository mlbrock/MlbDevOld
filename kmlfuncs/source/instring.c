/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes 'KML_STRING' structures.

	Revision History	:	1998-03-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2016.
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

	NAME			:	KML_INIT_String

	SYNOPSIS		:	void KML_INIT_String(ptr);

						KML_STRING *ptr;

	DESCRIPTION	:	Initializes the members of a ''KML_STRING''
						structure to their default values.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``ptr`` points to the ''KML_STRING''
						structure to be initialized by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_INIT_StringList
						KML_CMP_String
						KML_COPY_String
						KML_FREE_String
						KML_SCMP_String

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2016 Michael L. Brock

	OUTPUT INDEX:	KML_INIT_String
						Initialization Functions:KML_INIT_String
						KML_STRING Functions:KML_INIT_String

	PUBLISH XREF:	KML_INIT_String

	PUBLISH NAME:	KML_INIT_String

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_INIT_String(KML_STRING *ptr)
#else
void KML_INIT_String(ptr)
KML_STRING *ptr;
#endif /* #ifndef NARGS */
{
	memset(ptr, '\0', sizeof(*ptr));

	ptr->start_ptr  = NULL;
	ptr->end_ptr    = NULL;
	ptr->escape_ptr = NULL;
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	KML_INIT_StringList

	SYNOPSIS		:	void KML_INIT_StringList(in_count, in_list);

						unsigned int  in_count;

						KML_STRING   *in_list;

	DESCRIPTION	:	Initializes the elements of a array of ''KML_STRING''
						structures to their default values.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_count`` is the number of elements in the array
						``in_list``.

						(.) ``in_list`` is the array of ''KML_STRING''
						structures to be initialized by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_INIT_String
						KML_COPY_StringList
						KML_FREE_StringList
						KML_SORT_StringList

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2016 Michael L. Brock

	OUTPUT INDEX:	KML_INIT_StringList
						Initialization Functions:KML_INIT_StringList
						KML_STRING Functions:KML_INIT_StringList

	PUBLISH XREF:	KML_INIT_StringList

	PUBLISH NAME:	KML_INIT_StringList

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_INIT_StringList(unsigned int in_count, KML_STRING *in_list)
#else
void KML_INIT_StringList(in_count, in_list)
unsigned int  in_count;
KML_STRING   *in_list;
#endif /* #ifndef NARGS */
{
	while (in_count--)
		KML_INIT_String(in_list++);
}
/*	***********************************************************************	*/

