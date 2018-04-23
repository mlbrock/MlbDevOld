/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Frees 'KML_KEYWORD' structures.

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

	NAME			:	KML_FREE_Keyword

	SYNOPSIS		:	void KML_FREE_Keyword(ptr);

						KML_KEYWORD *ptr;

	DESCRIPTION	:	Frees the members of a ''KML_KEYWORD'' structure.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``ptr`` points to the ''KML_KEYWORD''
						structure to be freed by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_FREE_KeywordList
						KML_CMP_Keyword
						KML_COPY_Keyword
						KML_INIT_Keyword
						KML_SCMP_Keyword

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2018 Michael L. Brock

	OUTPUT INDEX:	KML_FREE_Keyword
						Memory Functions:KML_FREE_Keyword
						KML_KEYWORD Functions:KML_FREE_Keyword

	PUBLISH XREF:	KML_FREE_Keyword

	PUBLISH NAME:	KML_FREE_Keyword

	ENTRY CLASS	:	Memory Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_FREE_Keyword(KML_KEYWORD *ptr)
#else
void KML_FREE_Keyword(ptr)
KML_KEYWORD *ptr;
#endif /* #ifndef NARGS */
{
	if (ptr->keyword != NULL)
		free(ptr->keyword);

	KML_INIT_Keyword(ptr);
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	KML_FREE_KeywordList

	SYNOPSIS		:	void KML_FREE_KeywordList(in_count, in_list);

						unsigned int  *in_count;

						KML_KEYWORD  **in_list;

	DESCRIPTION	:	Frees the elements of an array of ''KML_KEYWORD''
						structures.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_count`` is a pointer to the ''unsigned int'' which
						contains the number of elements in the array to which
						the ``in_list`` parameter points.

						(.) ``in_list`` is a pointer to the array of ''KML_KEYWORD''
						structures to be freed by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_FREE_Keyword
						KML_COPY_KeywordList
						KML_INIT_KeywordList
						KML_SORT_KeywordList

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2018 Michael L. Brock

	OUTPUT INDEX:	KML_FREE_KeywordList
						Memory Functions:KML_FREE_KeywordList
						KML_KEYWORD Functions:KML_FREE_KeywordList

	PUBLISH XREF:	KML_FREE_KeywordList

	PUBLISH NAME:	KML_FREE_KeywordList

	ENTRY CLASS	:	Memory Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_FREE_KeywordList(unsigned int *in_count, KML_KEYWORD **in_list)
#else
void KML_FREE_KeywordList(in_count, in_list)
unsigned int  *in_count;
KML_KEYWORD  **in_list;
#endif /* #ifndef NARGS */
{
	while (*in_count)
		KML_FREE_Keyword(*in_list + --(*in_count));

	if (*in_list != NULL)
		free(*in_list);

	*in_count = 0;
	*in_list  = NULL;
}
/*	***********************************************************************	*/

