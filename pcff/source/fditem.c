/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Finds the named item in a configuration.

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

#include "pcffi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	PCFF_FindItem

   SYNOPSIS    :	found_ptr = PCFF_FindItem(cfg_ptr, item_name, found_index);

						const PCFF_ITEM *found_ptr;

						const PCFF_CFG  *cfg_ptr;

						const char      *item_name;

						unsigned int    *found_index;

   DESCRIPTION :  Performs a binary search in the array of ''PCFF_ITEM''
						structures in the ``item_list`` member of the ``cfg_ptr``
						''PCFF_CFG'' structure for an element with a ''name''
						member equal to the ``item_name`` parameter.

						If the desired element is found, its index in the item
						list is placed into the ''unsigned int'' to which
						``found_index`` points.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``cfg_ptr`` points to the ''PCFF_CFG'' structure in
						which is the array of ''PCFF_ITEM'' structures to be
						searched by this function.

						(.) ``item_name`` is the name of the item for which this
						function is to search.

						(.) ``found_index`` points to an ''unsigned int'' into
						which the index of the found element will be placed,
						if found.

						(-) Note, however, that ``found_index`` will not be
						de-referenced if it is ''NULL''.

   RETURNS     :	Returns from this function are as follow:

						(.) A pointer to the desired ''PCFF_ITEM'' structure if
						``item_name`` is found as an element in the list.

						(-) In this case, if the ``found_index`` parameter is not
						''NULL'', the ''unsigned int'' to which ``found_index``
						points will be set to the index of that element in the
						array.

						(.) ''NULL'' if the desired element is not found in the
						item list.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :	

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1999 - 2014 Michael L. Brock

   OUTPUT INDEX:	PCFF_FindItem
						Search Functions:Parse Configuration File Facility Functions:PCFF_FindItem
						Parse Configuration File Facility Functions:Search Functions:PCFF_FindItem

   PUBLISH XREF:	PCFF_FindItem

   PUBLISH NAME:	PCFF_FindItem

	ENTRY CLASS	:	Search Functions

EOH */
/*	***********************************************************************	*/
const PCFF_ITEM *PCFF_FindItem(const PCFF_CFG *cfg_ptr, const char *item_name,
	unsigned int *found_index)
{
	const PCFF_ITEM *tmp_ptr = NULL;
	PCFF_ITEM        tmp_item;
	unsigned int     tmp_found_index;

	PCFF_InitItem(&tmp_item);

	found_index   = (found_index != NULL) ? found_index : &tmp_found_index;
	tmp_item.name = ((char *) item_name);

	if (STR_ARRAY_bsearch(NULL, cfg_ptr->item_count, cfg_ptr->item_list,
		&tmp_item, sizeof(tmp_item), found_index, STRFUNCS_DIRECTION_TOP,
		STR_CMP_FUNC_CAST(PCFF_ItemCompareName)) == STRFUNCS_ITEM_FOUND)
		tmp_ptr = cfg_ptr->item_list + *found_index;

	return(tmp_ptr);
}
/* *********************************************************************** */


