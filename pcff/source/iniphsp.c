/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes 'PCFF_IP_HSP' structures.

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

	NAME			:	PCFF_InitHostServProto

	SYNOPSIS		:	void PCFF_InitHostServProto(ptr);

						PCFF_IP_HSP *ptr;

	DESCRIPTION	:	Initializes the members of a ''PCFF_IP_HSP''
						structure to their default values.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``ptr`` points to the ''PCFF_IP_HSP'' structure
						to be initialized by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	PCFF_InitHostServProtoList
						PCFF_CopyHostServProto
						PCFF_FreeHostServProto

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

   COPYRIGHT   :	Copyright 1999 - 2015 Michael L. Brock

	OUTPUT INDEX:	PCFF_InitHostServProto
						Initialization Functions:Parse Configuration File Facility Functions:PCFF_InitHostServProto
						Parse Configuration File Facility Functions:Initialization Functions:PCFF_InitHostServProto

	PUBLISH XREF:	PCFF_InitHostServProto

	PUBLISH NAME:	PCFF_InitHostServProto

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
void PCFF_InitHostServProto(PCFF_IP_HSP *ptr)
{
	memset(ptr, '\0', sizeof(*ptr));

	ptr->spec_string     = NULL;
	ptr->host_name       = NULL;
	ptr->service_name    = NULL;
	ptr->service_number  = 0;
	ptr->protocol_name   = NULL;
	ptr->protocol_number = 0;
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	PCFF_InitHostServProtoList

	SYNOPSIS		:	void PCFF_InitHostServProtoList(in_list);

						unsigned int  in_count;

						PCFF_IP_HSP  *in_list;

	DESCRIPTION	:	Initializes the members of the elements of a list of
						''PCFF_IP_HSP'' structures to their default values.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_count`` is the ''unsigned int'' which contains the
						number of elements in the list of ''PCFF_IP_HSP''
						structures to be initialized by this function.

						(.) ``in_list`` is a the list of ''PCFF_IP_HSP''
						structures to be initialized by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	PCFF_InitHostServProto
						PCFF_CopyHostServProtoList
						PCFF_FreeHostServProtoList

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

   COPYRIGHT   :	Copyright 1999 - 2015 Michael L. Brock

	OUTPUT INDEX:	PCFF_InitHostServProtoList
						Initialization Functions:Parse Configuration File Facility Functions:PCFF_InitHostServProtoList
						Parse Configuration File Facility Functions:Initialization Functions:PCFF_InitHostServProtoList

	PUBLISH XREF:	PCFF_InitHostServProtoList

	PUBLISH NAME:	PCFF_InitHostServProtoList

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
void PCFF_InitHostServProtoList(unsigned int in_count, PCFF_IP_HSP *in_list)
{
	while (in_count)
		PCFF_InitHostServProto(in_list + --in_count);
}
/* *********************************************************************** */


