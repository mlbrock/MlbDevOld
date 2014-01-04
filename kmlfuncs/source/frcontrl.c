/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Frees a 'KML_CONTROL' structure.

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

	NAME			:	KML_FREE_Control

	SYNOPSIS		:	void KML_FREE_Control(ptr);

						KML_CONTROL *ptr;

	DESCRIPTION	:	Frees the members of a ''KML_CONTROL'' structure.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``ptr`` points to the ''KML_CONTROL''
						structure to be freed by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_INIT_Control

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2014 Michael L. Brock

	OUTPUT INDEX:	KML_FREE_Control
						Memory Functions:KML_FREE_Control
						KML_CONTROL Functions:KML_FREE_Control

	PUBLISH XREF:	KML_FREE_Control

	PUBLISH NAME:	KML_FREE_Control

	ENTRY CLASS	:	Memory Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_FREE_Control(KML_CONTROL *ptr)
#else
void KML_FREE_Control(ptr)
KML_CONTROL *ptr;
#endif /* #ifndef NARGS */
{
	KML_FREE_DomainList(&ptr->domain_count, &ptr->domain_list);

	KML_FREE_MatchList(&ptr->match_count, &ptr->match_list);

	KML_INIT_Control(ptr);
}
/*	***********************************************************************	*/

