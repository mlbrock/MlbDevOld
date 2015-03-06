/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes 'PCFF_CFG' structures.

	Revision History	:	1999-11-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1999 - 2015.
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

	NAME			:	PCFF_InitCfg

	SYNOPSIS		:	void PCFF_InitCfg(ptr);

						PCFF_CFG *ptr;

	DESCRIPTION	:	Initializes the members of a ''PCFF_CFG'' structure
						to their default values.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``ptr`` points to the ''PCFF_CFG'' structure
						to be initialized by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	PCFF_InitCfgList
						PCFF_CopyCfg
						PCFF_FreeCfg

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

   COPYRIGHT   :	Copyright 1999 - 2015 Michael L. Brock

	OUTPUT INDEX:	PCFF_InitCfg
						Initialization Functions:Parse Configuration File Facility Functions:PCFF_InitCfg
						Parse Configuration File Facility Functions:Initialization Functions:PCFF_InitCfg

	PUBLISH XREF:	PCFF_InitCfg

	PUBLISH NAME:	PCFF_InitCfg

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
void PCFF_InitCfg(PCFF_CFG *ptr)
{
	memset(ptr, '\0', sizeof(*ptr));

	ptr->item_count = 0;
	ptr->item_list  = NULL;
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	PCFF_InitCfgList

	SYNOPSIS		:	void PCFF_InitCfgList(in_list);

						unsigned int  in_count;

						PCFF_CFG     *in_list;

	DESCRIPTION	:	Initializes the members of the elements of a list of
						''PCFF_CFG'' structures to their default values.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_count`` is the ''unsigned int'' which contains the
						number of elements in the list of ''PCFF_CFG''
						structures to be initialized by this function.

						(.) ``in_list`` is a the list of ''PCFF_CFG''
						structures to be initialized by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	PCFF_InitCfg
						PCFF_CopyCfgList
						PCFF_FreeCfgList

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

   COPYRIGHT   :	Copyright 1999 - 2015 Michael L. Brock

	OUTPUT INDEX:	PCFF_InitCfgList
						Initialization Functions:Parse Configuration File Facility Functions:PCFF_InitCfgList
						Parse Configuration File Facility Functions:Initialization Functions:PCFF_InitCfgList

	PUBLISH XREF:	PCFF_InitCfgList

	PUBLISH NAME:	PCFF_InitCfgList

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
void PCFF_InitCfgList(unsigned int in_count, PCFF_CFG *in_list)
{
	while (in_count)
		PCFF_InitCfg(in_list + --in_count);
}
/* *********************************************************************** */


