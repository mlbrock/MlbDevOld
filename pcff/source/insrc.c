/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes 'PCFF_SRC' structures.

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

	NAME			:	PCFF_InitSrc

	SYNOPSIS		:	void PCFF_InitSrc(ptr);

						PCFF_SRC *ptr;

	DESCRIPTION	:	Initializes the members of a ''PCFF_SRC'' structure
						to their default values.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``ptr`` points to the ''PCFF_SRC'' structure
						to be initialized by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	PCFF_InitSrcList
						PCFF_CopySrc
						PCFF_FreeSrc

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

   COPYRIGHT   :	Copyright 1999 - 2018 Michael L. Brock

	OUTPUT INDEX:	PCFF_InitSrc
						Initialization Functions:Parse Configuration File Facility Functions:PCFF_InitSrc
						Parse Configuration File Facility Functions:Initialization Functions:PCFF_InitSrc

	PUBLISH XREF:	PCFF_InitSrc

	PUBLISH NAME:	PCFF_InitSrc

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
void PCFF_InitSrc(PCFF_SRC *ptr)
{
	memset(ptr, '\0', sizeof(*ptr));

	ptr->line_number = 0;
	ptr->file_name   = NULL;
	ptr->value       = NULL;
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	PCFF_InitSrcList

	SYNOPSIS		:	void PCFF_InitSrcList(in_list);

						unsigned int  in_count;

						PCFF_SRC     *in_list;

	DESCRIPTION	:	Initializes the members of the elements of a list of
						''PCFF_SRC'' structures to their default values.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_count`` is the ''unsigned int'' which contains the
						number of elements in the list of ''PCFF_SRC''
						structures to be initialized by this function.

						(.) ``in_list`` is a the list of ''PCFF_SRC''
						structures to be initialized by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	PCFF_InitSrc
						PCFF_CopySrcList
						PCFF_FreeSrcList

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

   COPYRIGHT   :	Copyright 1999 - 2018 Michael L. Brock

	OUTPUT INDEX:	PCFF_InitSrcList
						Initialization Functions:Parse Configuration File Facility Functions:PCFF_InitSrcList
						Parse Configuration File Facility Functions:Initialization Functions:PCFF_InitSrcList

	PUBLISH XREF:	PCFF_InitSrcList

	PUBLISH NAME:	PCFF_InitSrcList

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
void PCFF_InitSrcList(unsigned int in_count, PCFF_SRC *in_list)
{
	while (in_count)
		PCFF_InitSrc(in_list + --in_count);
}
/* *********************************************************************** */


