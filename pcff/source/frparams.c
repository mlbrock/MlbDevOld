/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Frees 'PCFF_PARAM_SPEC' structures.

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

	NAME			:	PCFF_FreeParamSpec

	SYNOPSIS		:	void PCFF_FreeParamSpec(ptr);

						PCFF_PARAM_SPEC *ptr;

	DESCRIPTION	:	Frees the members of a ''PCFF_PARAM_SPEC'' structure.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``ptr`` points to the ''PCFF_PARAM_SPEC'' structure
						to be freed by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	PCFF_FreeParamSpecList
						PCFF_InitParamSpec
						PCFF_FreeParamList

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

   COPYRIGHT   :	Copyright 1999 - 2016 Michael L. Brock

	OUTPUT INDEX:	PCFF_FreeParamSpec
						Memory Free Functions:Parse Configuration File Facility Functions:PCFF_FreeParamSpec
						Parse Configuration File Facility Functions:Memory Free Functions:PCFF_FreeParamSpec

	PUBLISH XREF:	PCFF_FreeParamSpec

	PUBLISH NAME:	PCFF_FreeParamSpec

	ENTRY CLASS	:	Memory Free Functions

EOH */
/*	***********************************************************************	*/
void PCFF_FreeParamSpec(PCFF_PARAM_SPEC *ptr)
{
	PCFF_FreeParamList(&ptr->param_count, &ptr->param_list);

	PCFF_InitParamSpec(ptr);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	PCFF_FreeParamSpecList

	SYNOPSIS		:	void PCFF_FreeParamSpecList(in_count, in_list);

						unsigned int     *in_count;

						PCFF_PARAM_SPEC **in_list;

	DESCRIPTION	:	Frees a list of ''PCFF_PARAM_SPEC'' structures.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_count`` is a pointer to the ''unsigned int''
						which contains the number of elements in the list of
						''PCFF_PARAM_SPEC'' structures to be freed by this function.

						(.) ``in_list`` is a pointer to the list of
						''PCFF_PARAM_SPEC'' structures to be freed by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	PCFF_FreeParamSpec

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

   COPYRIGHT   :	Copyright 1999 - 2016 Michael L. Brock

	OUTPUT INDEX:	PCFF_FreeParamSpecList
						Memory Free Functions:Parse Configuration File Facility Functions:PCFF_FreeParamSpecList
						Parse Configuration File Facility Functions:Memory Free Functions:PCFF_FreeParamSpecList

	PUBLISH XREF:	PCFF_FreeParamSpecList

	PUBLISH NAME:	PCFF_FreeParamSpecList

	ENTRY CLASS	:	Memory Free Functions

EOH */
/*	***********************************************************************	*/
void PCFF_FreeParamSpecList(unsigned int *in_count, PCFF_PARAM_SPEC **in_list)
{
	while (*in_count)
		PCFF_FreeParamSpec(*in_list + --(*in_count));

	if (*in_list != NULL)
		free(*in_list);

	*in_count = 0;
	*in_list  = NULL;
}
/*	***********************************************************************	*/


