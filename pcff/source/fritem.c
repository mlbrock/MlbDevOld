/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Frees 'PCFF_ITEM' structures.

	Revision History	:	1999-11-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1999 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Required include files . . .														*/
/*	***********************************************************************	*/

#include "pcffi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	PCFF_FreeItem

	SYNOPSIS		:	void PCFF_FreeItem(ptr);

						PCFF_ITEM *ptr;

	DESCRIPTION	:	Frees the members of a ''PCFF_ITEM'' structure.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``ptr`` points to the ''PCFF_ITEM'' structure
						to be freed by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	PCFF_FreeItemList
						PCFF_InitItem

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

   COPYRIGHT   :	Copyright 1999 - 2016 Michael L. Brock

	OUTPUT INDEX:	PCFF_FreeItem
						Memory Free Functions:Parse Configuration File Facility Functions:PCFF_FreeItem
						Parse Configuration File Facility Functions:Memory Free Functions:PCFF_FreeItem

	PUBLISH XREF:	PCFF_FreeItem

	PUBLISH NAME:	PCFF_FreeItem

	ENTRY CLASS	:	Memory Free Functions

EOH */
/*	***********************************************************************	*/
void PCFF_FreeItem(PCFF_ITEM *ptr)
{
	if (ptr->name != NULL)
		free(ptr->name);

	if (ptr->value != NULL)
		free(ptr->value);

	PCFF_FreeSrcList(&ptr->src_count, &ptr->src_list);

	PCFF_InitItem(ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	PCFF_FreeItemList

	SYNOPSIS		:	void PCFF_FreeItemList(in_count, in_list);

						unsigned int  *in_count;

						PCFF_ITEM     **in_list;

	DESCRIPTION	:	Frees a list of ''PCFF_ITEM'' structures.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_count`` is a pointer to the ''unsigned int''
						which contains the number of elements in the list of
						''PCFF_ITEM'' structures to be freed by this function.

						(.) ``in_list`` is a pointer to the list of
						''PCFF_ITEM'' structures to be freed by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	PCFF_FreeItem

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

   COPYRIGHT   :	Copyright 1999 - 2016 Michael L. Brock

	OUTPUT INDEX:	PCFF_FreeItemList
						Memory Free Functions:Parse Configuration File Facility Functions:PCFF_FreeItemList
						Parse Configuration File Facility Functions:Memory Free Functions:PCFF_FreeItemList

	PUBLISH XREF:	PCFF_FreeItemList

	PUBLISH NAME:	PCFF_FreeItemList

	ENTRY CLASS	:	Memory Free Functions

EOH */
/*	***********************************************************************	*/
void PCFF_FreeItemList(unsigned int *in_count, PCFF_ITEM **in_list)
{
	while (*in_count)
		PCFF_FreeItem(*in_list + --(*in_count));

	if (*in_list != NULL)
		free(*in_list);

	*in_count = 0;
	*in_list  = NULL;
}
/*	***********************************************************************	*/


