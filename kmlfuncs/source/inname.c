/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes 'KML_NAME' structures.

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

#include <memory.h>

#include "kmlfunci.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	KML_INIT_Name

	SYNOPSIS		:	void KML_INIT_Name(ptr);

						KML_NAME *ptr;

	DESCRIPTION	:	Initializes the members of a ''KML_NAME''
						structure to their default values.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``ptr`` points to the ''KML_NAME''
						structure to be initialized by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_INIT_NameList
						KML_CMP_Name
						KML_COPY_Name
						KML_FREE_Name
						KML_SCMP_Name

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2018 Michael L. Brock

	OUTPUT INDEX:	KML_INIT_Name
						Initialization Functions:KML_INIT_Name
						KML_NAME Functions:KML_INIT_Name

	PUBLISH XREF:	KML_INIT_Name

	PUBLISH NAME:	KML_INIT_Name

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_INIT_Name(KML_NAME *ptr)
#else
void KML_INIT_Name(ptr)
KML_NAME *ptr;
#endif /* #ifndef NARGS */
{
	memset(ptr, '\0', sizeof(*ptr));

	ptr->first_char  = NULL;
	ptr->other_chars = NULL;
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	KML_INIT_NameList

	SYNOPSIS		:	void KML_INIT_NameList(in_count, in_list);

						unsigned int  in_count;

						KML_NAME     *in_list;

	DESCRIPTION	:	Initializes the elements of a array of ''KML_NAME''
						structures to their default values.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_count`` is the number of elements in the array
						``in_list``.

						(.) ``in_list`` is the array of ''KML_NAME''
						structures to be initialized by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_INIT_Name
						KML_COPY_NameList
						KML_FREE_NameList
						KML_SORT_NameList

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2018 Michael L. Brock

	OUTPUT INDEX:	KML_INIT_NameList
						Initialization Functions:KML_INIT_NameList
						KML_NAME Functions:KML_INIT_NameList

	PUBLISH XREF:	KML_INIT_NameList

	PUBLISH NAME:	KML_INIT_NameList

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_INIT_NameList(unsigned int in_count, KML_NAME *in_list)
#else
void KML_INIT_NameList(in_count, in_list)
unsigned int  in_count;
KML_NAME     *in_list;
#endif /* #ifndef NARGS */
{
	while (in_count--)
		KML_INIT_Name(in_list++);
}
/*	***********************************************************************	*/

