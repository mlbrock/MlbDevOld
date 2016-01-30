/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Frees 'PCFF_SRC' structures.

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

	NAME			:	PCFF_FreeSrc

	SYNOPSIS		:	void PCFF_FreeSrc(ptr);

						PCFF_SRC *ptr;

	DESCRIPTION	:	Frees the members of a ''PCFF_SRC'' structure.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``ptr`` points to the ''PCFF_SRC'' structure
						to be freed by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	PCFF_FreeSrcList
						PCFF_InitSrc

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

   COPYRIGHT   :	Copyright 1999 - 2016 Michael L. Brock

	OUTPUT INDEX:	PCFF_FreeSrc
						Memory Free Functions:Parse Configuration File Facility Functions:PCFF_FreeSrc
						Parse Configuration File Facility Functions:Memory Free Functions:PCFF_FreeSrc

	PUBLISH XREF:	PCFF_FreeSrc

	PUBLISH NAME:	PCFF_FreeSrc

	ENTRY CLASS	:	Memory Free Functions

EOH */
/*	***********************************************************************	*/
void PCFF_FreeSrc(PCFF_SRC *ptr)
{
	if (ptr->file_name != NULL)
		free(ptr->file_name);

	if (ptr->value != NULL)
		free(ptr->value);

	PCFF_InitSrc(ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	PCFF_FreeSrcList

	SYNOPSIS		:	void PCFF_FreeSrcList(in_count, in_list);

						unsigned int  *in_count;

						PCFF_SRC     **in_list;

	DESCRIPTION	:	Frees a list of ''PCFF_SRC'' structures.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_count`` is a pointer to the ''unsigned int''
						which contains the number of elements in the list of
						''PCFF_SRC'' structures to be freed by this function.

						(.) ``in_list`` is a pointer to the list of
						''PCFF_SRC'' structures to be freed by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	PCFF_FreeSrc

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

   COPYRIGHT   :	Copyright 1999 - 2016 Michael L. Brock

	OUTPUT INDEX:	PCFF_FreeSrcList
						Memory Free Functions:Parse Configuration File Facility Functions:PCFF_FreeSrcList
						Parse Configuration File Facility Functions:Memory Free Functions:PCFF_FreeSrcList

	PUBLISH XREF:	PCFF_FreeSrcList

	PUBLISH NAME:	PCFF_FreeSrcList

	ENTRY CLASS	:	Memory Free Functions

EOH */
/*	***********************************************************************	*/
void PCFF_FreeSrcList(unsigned int *in_count, PCFF_SRC **in_list)
{
	while (*in_count)
		PCFF_FreeSrc(*in_list + --(*in_count));

	if (*in_list != NULL)
		free(*in_list);

	*in_count = 0;
	*in_list  = NULL;
}
/*	***********************************************************************	*/


