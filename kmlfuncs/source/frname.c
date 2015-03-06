/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Frees 'KML_NAME' structures.

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

	NAME			:	KML_FREE_Name

	SYNOPSIS		:	void KML_FREE_Name(ptr);

						KML_NAME *ptr;

	DESCRIPTION	:	Frees the members of a ''KML_NAME'' structure.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``ptr`` points to the ''KML_NAME''
						structure to be freed by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_FREE_NameList
						KML_CMP_Name
						KML_COPY_Name
						KML_INIT_Name
						KML_SCMP_Name

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2015 Michael L. Brock

	OUTPUT INDEX:	KML_FREE_Name
						Memory Functions:KML_FREE_Name
						KML_NAME Functions:KML_FREE_Name

	PUBLISH XREF:	KML_FREE_Name

	PUBLISH NAME:	KML_FREE_Name

	ENTRY CLASS	:	Memory Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_FREE_Name(KML_NAME *ptr)
#else
void KML_FREE_Name(ptr)
KML_NAME *ptr;
#endif /* #ifndef NARGS */
{
	if (ptr->first_char != NULL)
		free(ptr->first_char);
	if (ptr->other_chars != NULL)
		free(ptr->other_chars);

	KML_INIT_Name(ptr);
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	KML_FREE_NameList

	SYNOPSIS		:	void KML_FREE_NameList(in_count, in_list);

						unsigned int  *in_count;

						KML_NAME     **in_list;

	DESCRIPTION	:	Frees the elements of an array of ''KML_NAME''
						structures.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_count`` is a pointer to the ''unsigned int'' which
						contains the number of elements in the array to which
						the ``in_list`` parameter points.

						(.) ``in_list`` is a pointer to the array of ''KML_NAME''
						structures to be freed by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_FREE_Name
						KML_COPY_NameList
						KML_INIT_NameList
						KML_SORT_NameList

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2015 Michael L. Brock

	OUTPUT INDEX:	KML_FREE_NameList
						Memory Functions:KML_FREE_NameList
						KML_NAME Functions:KML_FREE_NameList

	PUBLISH XREF:	KML_FREE_NameList

	PUBLISH NAME:	KML_FREE_NameList

	ENTRY CLASS	:	Memory Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_FREE_NameList(unsigned int *in_count, KML_NAME **in_list)
#else
void KML_FREE_NameList(in_count, in_list)
unsigned int  *in_count;
KML_NAME     **in_list;
#endif /* #ifndef NARGS */
{
	while (*in_count)
		KML_FREE_Name(*in_list + --(*in_count));

	if (*in_list != NULL)
		free(*in_list);

	*in_count = 0;
	*in_list  = NULL;
}
/*	***********************************************************************	*/

