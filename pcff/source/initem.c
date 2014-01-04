/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes 'PCFF_ITEM' structures.

	Revision History	:	1999-11-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1999 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Required include files . . .														*/
/*	***********************************************************************	*/

#include <memory.h>

#include "pcffi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	PCFF_InitItem

	SYNOPSIS		:	void PCFF_InitItem(ptr);

						PCFF_ITEM *ptr;

	DESCRIPTION	:	Initializes the members of a ''PCFF_ITEM'' structure
						to their default values.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``ptr`` points to the ''PCFF_ITEM'' structure
						to be initialized by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	PCFF_InitItemList
						PCFF_CopyItem
						PCFF_FreeItem

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

   COPYRIGHT   :	Copyright 1999 - 2014 Michael L. Brock

	OUTPUT INDEX:	PCFF_InitItem
						Initialization Functions:Parse Configuration File Facility Functions:PCFF_InitItem
						Parse Configuration File Facility Functions:Initialization Functions:PCFF_InitItem

	PUBLISH XREF:	PCFF_InitItem

	PUBLISH NAME:	PCFF_InitItem

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
void PCFF_InitItem(PCFF_ITEM *ptr)
{
	memset(ptr, '\0', sizeof(*ptr));

	ptr->name      = NULL;
	ptr->value     = NULL;
	ptr->order     = 0L;
	ptr->src_count = 0;
	ptr->src_list  = NULL;
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	PCFF_InitItemList

	SYNOPSIS		:	void PCFF_InitItemList(in_list);

						unsigned int  in_count;

						PCFF_ITEM     *in_list;

	DESCRIPTION	:	Initializes the members of the elements of a list of
						''PCFF_ITEM'' structures to their default values.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_count`` is the ''unsigned int'' which contains the
						number of elements in the list of ''PCFF_ITEM''
						structures to be initialized by this function.

						(.) ``in_list`` is a the list of ''PCFF_ITEM''
						structures to be initialized by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	PCFF_InitItem
						PCFF_CopyItemList
						PCFF_FreeItemList

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

   COPYRIGHT   :	Copyright 1999 - 2014 Michael L. Brock

	OUTPUT INDEX:	PCFF_InitItemList
						Initialization Functions:Parse Configuration File Facility Functions:PCFF_InitItemList
						Parse Configuration File Facility Functions:Initialization Functions:PCFF_InitItemList

	PUBLISH XREF:	PCFF_InitItemList

	PUBLISH NAME:	PCFF_InitItemList

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
void PCFF_InitItemList(unsigned int in_count, PCFF_ITEM *in_list)
{
	while (in_count)
		PCFF_InitItem(in_list + --in_count);
}
/* *********************************************************************** */


