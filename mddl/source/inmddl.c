/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Member Data Definition Library (MDDL) Source Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes the members of an MDDL structure.

	Revision History	:	1993-12-09 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2016.
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

#include "mddli.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MDDL_InitMember

   SYNOPSIS    :	void MDDL_InitMember(ptr);

						MDDL *ptr;

   DESCRIPTION :	Initializes the members of a ''MDDL'' structure to
						their default values.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``ptr`` points to the ''MDDL'' structure to be
						initialized by this function.

   RETURNS     :	Void.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	MDDL_InitMemberList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2016 Michael L. Brock

   OUTPUT INDEX:	MDDL_InitMember
						Initialization Functions:MDDL_InitMember
						Member Data Definition Functions:see MDDL

   PUBLISH XREF:	MDDL_InitMember

   PUBLISH NAME:	MDDL_InitMember

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MDDL_InitMember(MDDL *ptr)
#else
void MDDL_InitMember(ptr)
MDDL *ptr;
#endif /* #ifndef NARGS */
{
	memset(ptr, '\0', sizeof(*ptr));

	ptr->name[0]        = 0;
	ptr->data_length    = 0;
	ptr->length         = 0;
	ptr->offset         = 0;
	ptr->type_count     = 0;
	ptr->type_spec[0]   = '\0';
	ptr->align_count    = 0;
	ptr->display_length = 0;
	ptr->display_name   = NULL;
	ptr->dbc_type       = 0;
	ptr->user_int_1     = 0;
	ptr->user_int_2     = 0;
	ptr->user_ptr_1     = 0;
	ptr->user_ptr_2     = 0;
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MDDL_InitMemberList

   SYNOPSIS    :	void MDDL_InitMemberList(count, list);

						unsigned int  count;

						MDDL         *list;

   DESCRIPTION :	Initializes the elements of a list of a ''MDDL''
						structures to their default values.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``count`` is the number of elements in the list
						``list``.

						(.) ``list`` is the list of ''MDDL'' structures to be
						initialized by this function.

   RETURNS     :	Void.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	MDDL_InitMember

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2016 Michael L. Brock

   OUTPUT INDEX:	MDDL_InitMemberList
						Initialization Functions:MDDL_InitMemberList
						Member Data Definition Functions:see MDDL

   PUBLISH XREF:	MDDL_InitMemberList

   PUBLISH NAME:	MDDL_InitMemberList

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MDDL_InitMemberList(unsigned int count, MDDL *list)
#else
void MDDL_InitMemberList(count, list)
unsigned int  count;
MDDL         *list;
#endif /* #ifndef NARGS */
{
	while (count--)
		MDDL_InitMember(list++);
}
/* *********************************************************************** */

