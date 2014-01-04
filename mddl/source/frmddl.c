/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Member Data Definition Library (MDDL) Source Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Frees the members of MDDL structures.

	Revision History	:	1993-12-09 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2014.
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

#include "mddli.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MDDL_FreeMember

   SYNOPSIS    :	void MDDL_FreeMember(ptr);

						MDDL *ptr;

   DESCRIPTION :	Frees the members of a ''MDDL'' structure and
						initializes them to their default values.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``ptr`` points to the ''MDDL'' structure to be
						freed by this function.

   RETURNS     :	Void.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	MDDL_InitMember
						MDDL_FreeMemberList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2014 Michael L. Brock

   OUTPUT INDEX:	MDDL_FreeMember
						Free Functions:MDDL_FreeMember
						Member Data Definition Functions:see MDDL

   PUBLISH XREF:	MDDL_FreeMember

   PUBLISH NAME:	MDDL_FreeMember

	ENTRY CLASS	:	Free Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MDDL_FreeMember(MDDL *ptr)
#else
void MDDL_FreeMember(ptr)
MDDL *ptr;
#endif /* #ifndef NARGS */
{
	if (ptr->display_name != NULL)
		free(ptr->display_name);

	MDDL_InitMember(ptr);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MDDL_FreeMemberList

   SYNOPSIS    :	void MDDL_FreeMemberList(count, list);

						unsigned int  *count;

						MDDL         **list;

   DESCRIPTION :	Frees an array of ''MDDL'' structures.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``count`` points to the ''unsigned int'' which contains
						the number of elements in the array to which the ``list``
						parameter points.

						(.) ``list`` points to the array of ''MDDL''
						structures to be freed by this function.

   RETURNS     :	Void.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	MDDL_FreeMember

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2014 Michael L. Brock

   OUTPUT INDEX:	MDDL_FreeMemberList
						Free Functions:MDDL_FreeMemberList
						Member Data Definition Functions:see MDDL

   PUBLISH XREF:	MDDL_FreeMemberList

   PUBLISH NAME:	MDDL_FreeMemberList

	ENTRY CLASS	:	Free Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MDDL_FreeMemberList(unsigned int *count, MDDL **list)
#else
void MDDL_FreeMemberList(count, list)
unsigned int  *count;
MDDL         **list;
#endif /* #ifndef NARGS */
{
	while (*count)
		MDDL_FreeMember(*list + --(*count));

	if (*list != NULL)
		free(*list);

	*count = 0;
	*list  = NULL;
}
/* *********************************************************************** */

