/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes 'PCFF_PARAM' structures.

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

	NAME			:	PCFF_InitParam

	SYNOPSIS		:	void PCFF_InitParam(ptr);

						PCFF_PARAM *ptr;

	DESCRIPTION	:	Initializes the members of a ''PCFF_PARAM'' structure
						to their default values.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``ptr`` points to the ''PCFF_PARAM'' structure
						to be initialized by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	PCFF_InitParamList

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

   COPYRIGHT   :	Copyright 1999 - 2015 Michael L. Brock

	OUTPUT INDEX:	PCFF_InitParam
						Initialization Functions:Parse Configuration File Facility Functions:PCFF_InitParam
						Parse Configuration File Facility Functions:Initialization Functions:PCFF_InitParam

	PUBLISH XREF:	PCFF_InitParam

	PUBLISH NAME:	PCFF_InitParam

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
void PCFF_InitParam(PCFF_PARAM *ptr)
{
	memset(ptr, '\0', sizeof(*ptr));

	ptr->param_name   = NULL;
	ptr->member_name  = NULL;
	ptr->field_type   = PCFF_FLD_TYPE_NONE;
	ptr->field_offset = 0;
	ptr->field_length = 0;
	ptr->flags        = PCFF_PARAM_FLAG_NONE;
	ptr->ref_index    = 0;
	ptr->description  = NULL;
	ptr->domain       = NULL;
	ptr->domain_count = 0;
	ptr->domain_list  = NULL;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	PCFF_InitParamList

	SYNOPSIS		:	void PCFF_InitParamList(in_list);

						unsigned int  in_count;

						PCFF_PARAM   *in_list;

	DESCRIPTION	:	Initializes the members of the elements of a list of
						''PCFF_PARAM'' structures to their default values.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_count`` is the ''unsigned int'' which contains the
						number of elements in the list of ''PCFF_PARAM''
						structures to be initialized by this function.

						(.) ``in_list`` is a the list of ''PCFF_PARAM''
						structures to be initialized by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	PCFF_InitParam

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

   COPYRIGHT   :	Copyright 1999 - 2015 Michael L. Brock

	OUTPUT INDEX:	PCFF_InitParamList
						Initialization Functions:Parse Configuration File Facility Functions:PCFF_InitParamList
						Parse Configuration File Facility Functions:Initialization Functions:PCFF_InitParamList

	PUBLISH XREF:	PCFF_InitParamList

	PUBLISH NAME:	PCFF_InitParamList

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
void PCFF_InitParamList(unsigned int in_count, PCFF_PARAM *in_list)
{
	while (in_count)
		PCFF_InitParam(in_list + --in_count);
}
/* *********************************************************************** */


