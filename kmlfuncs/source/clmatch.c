/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Clears the 'KML_CONTROL list of 'KML_MATCH'
								structures.

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

#include "kmlfunci.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	KML_ClearMatchList

	SYNOPSIS		:	void KML_ClearMatchList(control_ptr);

						KML_CONTROL *control_ptr;

	DESCRIPTION	:	Clears the data in the the match list contained in a
						''KML_CONTROL'' structure.

						Specifically:

						(.) The elements of the array of ''KML_MATCH'' structures
						to which the ``match_list`` member points are initialized
						to their default values.

						(.) The ``match_count`` member is set to ''0''.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``control_ptr`` points to the ''KML_CONTROL'' for
						which the match list is to be cleared.

	RETURNS		:	Void.

	NOTES			:	The memory allocated to the ``match_list`` member is
						not freed by this function.

	CAVEATS		:	

	SEE ALSO		:	KML_INIT_MatchList

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2014 Michael L. Brock

	OUTPUT INDEX:	KML_ClearMatchList
						Initialization Functions:KML_ClearMatchList
						KML_MATCH Functions:KML_ClearMatchList

	PUBLISH XREF:	KML_ClearMatchList

	PUBLISH NAME:	KML_ClearMatchList

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_ClearMatchList(KML_CONTROL *control_ptr)
#else
void KML_ClearMatchList(control_ptr)
KML_CONTROL *control_ptr;
#endif /* #ifndef NARGS */
{
	KML_INIT_MatchList(control_ptr->match_count, control_ptr->match_list);

	control_ptr->match_count = 0;
}
/*	***********************************************************************	*/

