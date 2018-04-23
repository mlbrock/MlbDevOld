/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes 'PCFF_PARSE_SPEC' structures.

	Revision History	:	1999-11-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1999 - 2018.
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

	NAME			:	PCFF_InitParse

	SYNOPSIS		:	void PCFF_InitParse(ptr);

						PCFF_PARSE_SPEC *ptr;

	DESCRIPTION	:	Initializes the members of a ''PCFF_PARSE_SPEC'' structure
						to their default values.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``ptr`` points to the ''PCFF_PARSE_SPEC'' structure
						to be initialized by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	PCFF_InitParseList

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

   COPYRIGHT   :	Copyright 1999 - 2018 Michael L. Brock

	OUTPUT INDEX:	PCFF_InitParse
						Initialization Functions:Parse Configuration File Facility Functions:PCFF_InitParse
						Parse Configuration File Facility Functions:Initialization Functions:PCFF_InitParse

	PUBLISH XREF:	PCFF_InitParse

	PUBLISH NAME:	PCFF_InitParse

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
void PCFF_InitParse(PCFF_PARSE_SPEC *ptr)
{
	memset(ptr, '\0', sizeof(*ptr));

	ptr->flags          = PCFF_FLAG_NONE;
	ptr->name_left      = NULL;
	ptr->name_right     = NULL;
	ptr->value_left     = NULL;
	ptr->value_right    = NULL;
	ptr->required_count = 0;
	ptr->required_list  = NULL;
	ptr->optional_count = 0;
	ptr->optional_list  = NULL;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	PCFF_InitParseList

	SYNOPSIS		:	void PCFF_InitParseList(in_list);

						unsigned int  in_count;

						PCFF_PARSE_SPEC     *in_list;

	DESCRIPTION	:	Initializes the members of the elements of a list of
						''PCFF_PARSE_SPEC'' structures to their default values.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_count`` is the ''unsigned int'' which contains the
						number of elements in the list of ''PCFF_PARSE_SPEC''
						structures to be initialized by this function.

						(.) ``in_list`` is a the list of ''PCFF_PARSE_SPEC''
						structures to be initialized by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	PCFF_InitParse

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

   COPYRIGHT   :	Copyright 1999 - 2018 Michael L. Brock

	OUTPUT INDEX:	PCFF_InitParseList
						Initialization Functions:Parse Configuration File Facility Functions:PCFF_InitParseList
						Parse Configuration File Facility Functions:Initialization Functions:PCFF_InitParseList

	PUBLISH XREF:	PCFF_InitParseList

	PUBLISH NAME:	PCFF_InitParseList

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
void PCFF_InitParseList(unsigned int in_count, PCFF_PARSE_SPEC *in_list)
{
	while (in_count)
		PCFF_InitParse(in_list + --in_count);
}
/* *********************************************************************** */


