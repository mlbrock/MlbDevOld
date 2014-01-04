/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Frees 'PCFF_CFG' structures.

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

	NAME			:	PCFF_FreeCfg

	SYNOPSIS		:	void PCFF_FreeCfg(ptr);

						PCFF_CFG *ptr;

	DESCRIPTION	:	Frees the members of a ''PCFF_CFG'' structure.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``ptr`` points to the ''PCFF_CFG'' structure
						to be freed by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	PCFF_FreeCfgList
						PCFF_InitCfg

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

   COPYRIGHT   :	Copyright 1999 - 2014 Michael L. Brock

	OUTPUT INDEX:	PCFF_FreeCfg
						Memory Free Functions:Parse Configuration File Facility Functions:PCFF_FreeCfg
						Parse Configuration File Facility Functions:Memory Free Functions:PCFF_FreeCfg

	PUBLISH XREF:	PCFF_FreeCfg

	PUBLISH NAME:	PCFF_FreeCfg

	ENTRY CLASS	:	Memory Free Functions

EOH */
/*	***********************************************************************	*/
void PCFF_FreeCfg(PCFF_CFG *ptr)
{
	PCFF_FreeItemList(&ptr->item_count, &ptr->item_list);

	PCFF_InitCfg(ptr);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	PCFF_FreeCfgList

	SYNOPSIS		:	void PCFF_FreeCfgList(in_count, in_list);

						unsigned int  *in_count;

						PCFF_CFG     **in_list;

	DESCRIPTION	:	Frees a list of ''PCFF_CFG'' structures.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_count`` is a pointer to the ''unsigned int''
						which contains the number of elements in the list of
						''PCFF_CFG'' structures to be freed by this function.

						(.) ``in_list`` is a pointer to the list of
						''PCFF_CFG'' structures to be freed by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	PCFF_FreeCfg

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

   COPYRIGHT   :	Copyright 1999 - 2014 Michael L. Brock

	OUTPUT INDEX:	PCFF_FreeCfgList
						Memory Free Functions:Parse Configuration File Facility Functions:PCFF_FreeCfgList
						Parse Configuration File Facility Functions:Memory Free Functions:PCFF_FreeCfgList

	PUBLISH XREF:	PCFF_FreeCfgList

	PUBLISH NAME:	PCFF_FreeCfgList

	ENTRY CLASS	:	Memory Free Functions

EOH */
/*	***********************************************************************	*/
void PCFF_FreeCfgList(unsigned int *in_count, PCFF_CFG **in_list)
{
	while (*in_count)
		PCFF_FreeCfg(*in_list + --(*in_count));

	if (*in_list != NULL)
		free(*in_list);

	*in_count = 0;
	*in_list  = NULL;
}
/*	***********************************************************************	*/


