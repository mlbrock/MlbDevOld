/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Frees 'KML_MATCH' structures.

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

#include <stdlib.h>

#include "kmlfunci.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	KML_FREE_Match

	SYNOPSIS		:	void KML_FREE_Match(ptr);

						KML_MATCH *ptr;

	DESCRIPTION	:	Frees the members of a ''KML_MATCH'' structure.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``ptr`` points to the ''KML_MATCH''
						structure to be freed by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_FREE_MatchList
						KML_CMP_Match
						KML_COPY_Match
						KML_INIT_Match
						KML_SCMP_Match

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2015 Michael L. Brock

	OUTPUT INDEX:	KML_FREE_Match
						Memory Functions:KML_FREE_Match
						KML_MATCH Functions:KML_FREE_Match

	PUBLISH XREF:	KML_FREE_Match

	PUBLISH NAME:	KML_FREE_Match

	ENTRY CLASS	:	Memory Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_FREE_Match(KML_MATCH *ptr)
#else
void KML_FREE_Match(ptr)
KML_MATCH *ptr;
#endif /* #ifndef NARGS */
{
	KML_INIT_Match(ptr);
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	KML_FREE_MatchList

	SYNOPSIS		:	void KML_FREE_MatchList(in_count, in_list);

						unsigned int  *in_count;

						KML_MATCH    **in_list;

	DESCRIPTION	:	Frees the elements of an array of ''KML_MATCH''
						structures.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_count`` is a pointer to the ''unsigned int'' which
						contains the number of elements in the array to which
						the ``in_list`` parameter points.

						(.) ``in_list`` is a pointer to the array of ''KML_MATCH''
						structures to be freed by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_FREE_Match
						KML_COPY_MatchList
						KML_INIT_MatchList
						KML_SORT_MatchList

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2015 Michael L. Brock

	OUTPUT INDEX:	KML_FREE_MatchList
						Memory Functions:KML_FREE_MatchList
						KML_MATCH Functions:KML_FREE_MatchList

	PUBLISH XREF:	KML_FREE_MatchList

	PUBLISH NAME:	KML_FREE_MatchList

	ENTRY CLASS	:	Memory Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_FREE_MatchList(unsigned int *in_count, KML_MATCH **in_list)
#else
void KML_FREE_MatchList(in_count, in_list)
unsigned int  *in_count;
KML_MATCH    **in_list;
#endif /* #ifndef NARGS */
{
	while (*in_count)
		KML_FREE_Match(*in_list + --(*in_count));

	if (*in_list != NULL)
		free(*in_list);

	*in_count = 0;
	*in_list  = NULL;
}
/*	***********************************************************************	*/

