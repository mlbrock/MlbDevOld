/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Frees 'PCFF_PARAM' structures.

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

	NAME			:	PCFF_FreeParam

	SYNOPSIS		:	void PCFF_FreeParam(ptr);

						PCFF_PARAM *ptr;

	DESCRIPTION	:	Frees the members of a ''PCFF_PARAM'' structure.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``ptr`` points to the ''PCFF_PARAM'' structure
						to be freed by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	PCFF_FreeParamList
						PCFF_InitParam

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

   COPYRIGHT   :	Copyright 1999 - 2016 Michael L. Brock

	OUTPUT INDEX:	PCFF_FreeParam
						Memory Free Functions:Parse Configuration File Facility Functions:PCFF_FreeParam
						Parse Configuration File Facility Functions:Memory Free Functions:PCFF_FreeParam

	PUBLISH XREF:	PCFF_FreeParam

	PUBLISH NAME:	PCFF_FreeParam

	ENTRY CLASS	:	Memory Free Functions

EOH */
/*	***********************************************************************	*/
void PCFF_FreeParam(PCFF_PARAM *ptr)
{
	if (ptr->param_name)
		free(ptr->param_name);

	if (ptr->member_name)
		free(ptr->member_name);

	if (ptr->description != NULL)
		free(ptr->description);

	if (ptr->domain != NULL)
		free(ptr->domain);

	strl_remove_all(&ptr->domain_count, &ptr->domain_list);

	PCFF_InitParam(ptr);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	PCFF_FreeParamList

	SYNOPSIS		:	void PCFF_FreeParamList(in_count, in_list);

						unsigned int  *in_count;

						PCFF_PARAM   **in_list;

	DESCRIPTION	:	Frees a list of ''PCFF_PARAM'' structures.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_count`` is a pointer to the ''unsigned int''
						which contains the number of elements in the list of
						''PCFF_PARAM'' structures to be freed by this function.

						(.) ``in_list`` is a pointer to the list of
						''PCFF_PARAM'' structures to be freed by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	PCFF_FreeParam

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

   COPYRIGHT   :	Copyright 1999 - 2016 Michael L. Brock

	OUTPUT INDEX:	PCFF_FreeParamList
						Memory Free Functions:Parse Configuration File Facility Functions:PCFF_FreeParamList
						Parse Configuration File Facility Functions:Memory Free Functions:PCFF_FreeParamList

	PUBLISH XREF:	PCFF_FreeParamList

	PUBLISH NAME:	PCFF_FreeParamList

	ENTRY CLASS	:	Memory Free Functions

EOH */
/*	***********************************************************************	*/
void PCFF_FreeParamList(unsigned int *in_count, PCFF_PARAM **in_list)
{
	while (*in_count)
		PCFF_FreeParam(*in_list + --(*in_count));

	if (*in_list != NULL)
		free(*in_list);

	*in_count = 0;
	*in_list  = NULL;
}
/*	***********************************************************************	*/


