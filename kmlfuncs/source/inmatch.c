/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes 'KML_MATCH' structures.

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

	NAME			:	KML_INIT_Match

	SYNOPSIS		:	void KML_INIT_Match(ptr);

						KML_MATCH *ptr;

	DESCRIPTION	:	Initializes the members of a ''KML_MATCH''
						structure to their default values.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``ptr`` points to the ''KML_MATCH''
						structure to be initialized by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_INIT_MatchList
						KML_CMP_Match
						KML_COPY_Match
						KML_FREE_Match
						KML_SCMP_Match

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2015 Michael L. Brock

	OUTPUT INDEX:	KML_INIT_Match
						Initialization Functions:KML_INIT_Match
						KML_MATCH Functions:KML_INIT_Match

	PUBLISH XREF:	KML_INIT_Match

	PUBLISH NAME:	KML_INIT_Match

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_INIT_Match(KML_MATCH *ptr)
#else
void KML_INIT_Match(ptr)
KML_MATCH *ptr;
#endif /* #ifndef NARGS */
{
	memset(ptr, '\0', sizeof(*ptr));

	ptr->type              = KML_TYPE_NONE;
	ptr->type_value        = 0;
	ptr->type_ptr.void_ptr = NULL;
	ptr->length            = 0;
	ptr->ptr               = NULL;
	ptr->closure_ptr       = NULL;
	ptr->start_line        = 0L;
	ptr->end_line          = 0L;
	ptr->start_char        = 0L;
	ptr->end_char          = 0L;
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	KML_INIT_MatchList

	SYNOPSIS		:	void KML_INIT_MatchList(in_count, in_list);

						unsigned int  in_count;

						KML_MATCH    *in_list;

	DESCRIPTION	:	Initializes the elements of a array of ''KML_MATCH''
						structures to their default values.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_count`` is the number of elements in the array
						``in_list``.

						(.) ``in_list`` is the array of ''KML_MATCH''
						structures to be initialized by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_INIT_Match
						KML_COPY_MatchList
						KML_FREE_MatchList
						KML_SORT_MatchList

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2015 Michael L. Brock

	OUTPUT INDEX:	KML_INIT_MatchList
						Initialization Functions:KML_INIT_MatchList
						KML_MATCH Functions:KML_INIT_MatchList

	PUBLISH XREF:	KML_INIT_MatchList

	PUBLISH NAME:	KML_INIT_MatchList

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_INIT_MatchList(unsigned int in_count, KML_MATCH *in_list)
#else
void KML_INIT_MatchList(in_count, in_list)
unsigned int  in_count;
KML_MATCH    *in_list;
#endif /* #ifndef NARGS */
{
	while (in_count--)
		KML_INIT_Match(in_list++);
}
/*	***********************************************************************	*/

