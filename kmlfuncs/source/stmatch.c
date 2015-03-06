/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Sorts an array of 'KML_MATCH' structures.

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

#include "kmlfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME        :	KML_SORT_MatchList

	SYNOPSIS    :	void KML_SORT_MatchList(in_count, in_list);

						unsigned int  in_count;

						KML_MATCH    *in_list;

	DESCRIPTION :	Sorts an array of ''KML_MATCH'' structures using
						the comparison function ``KML_SCMP_Match``.

						The following members of the ''KML_MATCH''
						structure are used as the basis of comparison in the sort:

						(.) ``ptr``

						(.) ``type``

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_count`` is the number of elements in the array
						``in_list``.

						(.) ``in_list`` is the array of ''KML_MATCH'' structures
						which is to be sorted by this function.

	RETURNS     :	Void.

	NOTES       :	

	CAVEATS     :	

	SEE ALSO    :	KML_FREE_MatchList
						KML_COPY_MatchList
						KML_INIT_MatchList
						KML_SCMP_Match

	EXAMPLES    :	

	AUTHOR      :	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2015 Michael L. Brock

	OUTPUT INDEX:	KML_SORT_MatchList
						Sort Functions:Database:KML_SORT_MatchList
						KML_MATCH Functions:KML_SORT_MatchList

	PUBLISH XREF:	KML_SORT_MatchList

	PUBLISH NAME:	KML_SORT_MatchList

	ENTRY CLASS	:	Sort Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_SORT_MatchList(unsigned int in_count, KML_MATCH *in_list)
#else
void KML_SORT_MatchList(in_count, in_list)
unsigned int  in_count;
KML_MATCH    *in_list;
#endif /* #ifndef NARGS */
{
	STR_ARRAY_qsort(NULL, in_count, ((void *) in_list), sizeof(KML_MATCH),
		((int (*)(void *, const void *, const void *, size_t))
		KML_SCMP_Match));
}
/*	***********************************************************************	*/

