/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Frees 'KML_STRING' structures.

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

#include <stdlib.h>

#include "kmlfunci.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	KML_FREE_String

	SYNOPSIS		:	void KML_FREE_String(ptr);

						KML_STRING *ptr;

	DESCRIPTION	:	Frees the members of a ''KML_STRING'' structure.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``ptr`` points to the ''KML_STRING''
						structure to be freed by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_FREE_StringList
						KML_CMP_String
						KML_COPY_String
						KML_INIT_String
						KML_SCMP_String

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2018 Michael L. Brock

	OUTPUT INDEX:	KML_FREE_String
						Memory Functions:KML_FREE_String
						KML_STRING Functions:KML_FREE_String

	PUBLISH XREF:	KML_FREE_String

	PUBLISH NAME:	KML_FREE_String

	ENTRY CLASS	:	Memory Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_FREE_String(KML_STRING *ptr)
#else
void KML_FREE_String(ptr)
KML_STRING *ptr;
#endif /* #ifndef NARGS */
{
	if (ptr->start_ptr != NULL)
		free(ptr->start_ptr);
	if (ptr->escape_ptr != NULL)
		free(ptr->escape_ptr);
	if (ptr->end_ptr != NULL)
		free(ptr->end_ptr);

	KML_INIT_String(ptr);
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	KML_FREE_StringList

	SYNOPSIS		:	void KML_FREE_StringList(in_count, in_list);

						unsigned int  *in_count;

						KML_STRING   **in_list;

	DESCRIPTION	:	Frees the elements of an array of ''KML_STRING''
						structures.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_count`` is a pointer to the ''unsigned int'' which
						contains the number of elements in the array to which
						the ``in_list`` parameter points.

						(.) ``in_list`` is a pointer to the array of ''KML_STRING''
						structures to be freed by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_FREE_String
						KML_COPY_StringList
						KML_INIT_StringList
						KML_SORT_StringList

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2018 Michael L. Brock

	OUTPUT INDEX:	KML_FREE_StringList
						Memory Functions:KML_FREE_StringList
						KML_STRING Functions:KML_FREE_StringList

	PUBLISH XREF:	KML_FREE_StringList

	PUBLISH NAME:	KML_FREE_StringList

	ENTRY CLASS	:	Memory Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_FREE_StringList(unsigned int *in_count, KML_STRING **in_list)
#else
void KML_FREE_StringList(in_count, in_list)
unsigned int  *in_count;
KML_STRING   **in_list;
#endif /* #ifndef NARGS */
{
	while (*in_count)
		KML_FREE_String(*in_list + --(*in_count));

	if (*in_list != NULL)
		free(*in_list);

	*in_count = 0;
	*in_list  = NULL;
}
/*	***********************************************************************	*/

