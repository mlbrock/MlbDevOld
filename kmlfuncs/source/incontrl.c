/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes a 'KML_CONTROL' structure.

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

	NAME			:	KML_INIT_Control

	SYNOPSIS		:	void KML_INIT_Control(ptr);

						KML_CONTROL *ptr;

	DESCRIPTION	:	Initializes the members of a ''KML_CONTROL''
						structure to their default values.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``ptr`` points to the ''KML_CONTROL''
						structure to be initialized by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_FREE_Control

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2015 Michael L. Brock

	OUTPUT INDEX:	KML_INIT_Control
						Initialization Functions:KML_INIT_Control
						KML_CONTROL Functions:KML_INIT_Control

	PUBLISH XREF:	KML_INIT_Control

	PUBLISH NAME:	KML_INIT_Control

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_INIT_Control(KML_CONTROL *ptr)
#else
void KML_INIT_Control(ptr)
KML_CONTROL *ptr;
#endif /* #ifndef NARGS */
{
	memset(ptr, '\0', sizeof(*ptr));

	ptr->domain_count          = 0;
	ptr->domain_list           = NULL;
	ptr->match_count           = 0;
	ptr->match_list            = NULL;
	ptr->allocated_match_count = 0;
}
/*	***********************************************************************	*/

