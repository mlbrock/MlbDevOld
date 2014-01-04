/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes 'PCFF_PARAM_SPEC' structures.

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

	NAME			:	PCFF_InitParamSpec

	SYNOPSIS		:	void PCFF_InitParamSpec(ptr);

						PCFF_PARAM_SPEC *ptr;

	DESCRIPTION	:	Initializes the members of a ''PCFF_PARAM_SPEC'' structure
						to their default values.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``ptr`` points to the ''PCFF_PARAM_SPEC'' structure
						to be initialized by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	PCFF_InitParamSpecList

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

   COPYRIGHT   :	Copyright 1999 - 2014 Michael L. Brock

	OUTPUT INDEX:	PCFF_InitParamSpec
						Initialization Functions:Parse Configuration File Facility Functions:PCFF_InitParamSpec
						Parse Configuration File Facility Functions:Initialization Functions:PCFF_InitParamSpec

	PUBLISH XREF:	PCFF_InitParamSpec

	PUBLISH NAME:	PCFF_InitParamSpec

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
void PCFF_InitParamSpec(PCFF_PARAM_SPEC *ptr)
{
	memset(ptr, '\0', sizeof(*ptr));

	ptr->structure_size = 0;
	ptr->param_count    = 0;
	ptr->param_list     = NULL;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	PCFF_InitParamSpecList

	SYNOPSIS		:	void PCFF_InitParamSpecList(in_list);

						unsigned int     in_count;

						PCFF_PARAM_SPEC *in_list;

	DESCRIPTION	:	Initializes the members of the elements of a list of
						''PCFF_PARAM_SPEC'' structures to their default values.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_count`` is the ''unsigned int'' which contains the
						number of elements in the list of ''PCFF_PARAM_SPEC''
						structures to be initialized by this function.

						(.) ``in_list`` is a the list of ''PCFF_PARAM_SPEC''
						structures to be initialized by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	PCFF_InitParamSpec

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

   COPYRIGHT   :	Copyright 1999 - 2014 Michael L. Brock

	OUTPUT INDEX:	PCFF_InitParamSpecList
						Initialization Functions:Parse Configuration File Facility Functions:PCFF_InitParamSpecList
						Parse Configuration File Facility Functions:Initialization Functions:PCFF_InitParamSpecList

	PUBLISH XREF:	PCFF_InitParamSpecList

	PUBLISH NAME:	PCFF_InitParamSpecList

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
void PCFF_InitParamSpecList(unsigned int in_count, PCFF_PARAM_SPEC *in_list)
{
	while (in_count)
		PCFF_InitParamSpec(in_list + --in_count);
}
/* *********************************************************************** */


