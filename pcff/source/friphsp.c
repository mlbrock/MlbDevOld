/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Frees 'PCFF_IP_HSP' structures.

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

#include "pcffi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	PCFF_FreeHostServProto

	SYNOPSIS		:	void PCFF_FreeHostServProto(ptr);

						PCFF_IP_HSP *ptr;

	DESCRIPTION	:	Frees the members of a ''PCFF_IP_HSP'' structure.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``ptr`` points to the ''PCFF_IP_HSP'' structure
						to be freed by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	PCFF_FreeHostServProtoList
						PCFF_InitHostServProto

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

   COPYRIGHT   :	Copyright 1999 - 2015 Michael L. Brock

	OUTPUT INDEX:	PCFF_FreeHostServProto
						Memory Free Functions:Parse Configuration File Facility Functions:PCFF_FreeHostServProto
						Parse Configuration File Facility Functions:Memory Free Functions:PCFF_FreeHostServProto

	PUBLISH XREF:	PCFF_FreeHostServProto

	PUBLISH NAME:	PCFF_FreeHostServProto

	ENTRY CLASS	:	Memory Free Functions

EOH */
/*	***********************************************************************	*/
void PCFF_FreeHostServProto(PCFF_IP_HSP *ptr)
{
	if (ptr->spec_string != NULL)
		free(ptr->spec_string);

	if (ptr->host_name != NULL)
		free(ptr->host_name);

	if (ptr->service_name != NULL)
		free(ptr->service_name);

	if (ptr->protocol_name != NULL)
		free(ptr->protocol_name);

	PCFF_InitHostServProto(ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	PCFF_FreeHostServProtoList

	SYNOPSIS		:	void PCFF_FreeHostServProtoList(in_count, in_list);

						unsigned int  *in_count;

						PCFF_IP_HSP  **in_list;

	DESCRIPTION	:	Frees a list of ''PCFF_IP_HSP'' structures.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_count`` is a pointer to the ''unsigned int''
						which contains the number of elements in the list of
						''PCFF_IP_HSP'' structures to be freed by this
						function.

						(.) ``in_list`` is a pointer to the list of
						''PCFF_IP_HSP'' structures to be freed by this
						function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	PCFF_FreeHostServProto

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

   COPYRIGHT   :	Copyright 1999 - 2015 Michael L. Brock

	OUTPUT INDEX:	PCFF_FreeHostServProtoList
						Memory Free Functions:Parse Configuration File Facility Functions:PCFF_FreeHostServProtoList
						Parse Configuration File Facility Functions:Memory Free Functions:PCFF_FreeHostServProtoList

	PUBLISH XREF:	PCFF_FreeHostServProtoList

	PUBLISH NAME:	PCFF_FreeHostServProtoList

	ENTRY CLASS	:	Memory Free Functions

EOH */
/*	***********************************************************************	*/
void PCFF_FreeHostServProtoList(unsigned int *in_count, PCFF_IP_HSP **in_list)
{
	while (*in_count)
		PCFF_FreeHostServProto(*in_list + --(*in_count));

	if (*in_list != NULL)
		free(*in_list);

	*in_count = 0;
	*in_list  = NULL;
}
/*	***********************************************************************	*/


