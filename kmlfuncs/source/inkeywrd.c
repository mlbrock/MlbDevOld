/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes 'KML_KEYWORD' structures.

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

#include <memory.h>

#include "kmlfunci.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	KML_INIT_Keyword

	SYNOPSIS		:	void KML_INIT_Keyword(ptr);

						KML_KEYWORD *ptr;

	DESCRIPTION	:	Initializes the members of a ''KML_KEYWORD''
						structure to their default values.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``ptr`` points to the ''KML_KEYWORD''
						structure to be initialized by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_INIT_KeywordList
						KML_CMP_Keyword
						KML_COPY_Keyword
						KML_FREE_Keyword
						KML_SCMP_Keyword

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2014 Michael L. Brock

	OUTPUT INDEX:	KML_INIT_Keyword
						Initialization Functions:KML_INIT_Keyword
						KML_KEYWORD Functions:KML_INIT_Keyword

	PUBLISH XREF:	KML_INIT_Keyword

	PUBLISH NAME:	KML_INIT_Keyword

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_INIT_Keyword(KML_KEYWORD *ptr)
#else
void KML_INIT_Keyword(ptr)
KML_KEYWORD *ptr;
#endif /* #ifndef NARGS */
{
	memset(ptr, '\0', sizeof(*ptr));

	ptr->keyword = NULL;
	ptr->length  = 0;
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	KML_INIT_KeywordList

	SYNOPSIS		:	void KML_INIT_KeywordList(in_count, in_list);

						unsigned int  in_count;

						KML_KEYWORD  *in_list;

	DESCRIPTION	:	Initializes the elements of a array of ''KML_KEYWORD''
						structures to their default values.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_count`` is the number of elements in the array
						``in_list``.

						(.) ``in_list`` is the array of ''KML_KEYWORD''
						structures to be initialized by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_INIT_Keyword
						KML_COPY_KeywordList
						KML_FREE_KeywordList
						KML_SORT_KeywordList

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2014 Michael L. Brock

	OUTPUT INDEX:	KML_INIT_KeywordList
						Initialization Functions:KML_INIT_KeywordList
						KML_KEYWORD Functions:KML_INIT_KeywordList

	PUBLISH XREF:	KML_INIT_KeywordList

	PUBLISH NAME:	KML_INIT_KeywordList

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_INIT_KeywordList(unsigned int in_count, KML_KEYWORD *in_list)
#else
void KML_INIT_KeywordList(in_count, in_list)
unsigned int  in_count;
KML_KEYWORD  *in_list;
#endif /* #ifndef NARGS */
{
	while (in_count--)
		KML_INIT_Keyword(in_list++);
}
/*	***********************************************************************	*/

