/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Constructs a human-readable description of the
								'service', 'network', and 'daemon' members of an
								RVUTIL_ENV structure.

	Revision History	:	1996-01-12 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <string.h>

#include <strfuncs.h>

#include "rvutili.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
char *RVUTIL_SNDToStr(const RVUTIL_ENV *env_ptr, char *out_string)
{
	return(chrcat(nstrcat(strcat(nstrcat(strcat(nstrcat(strcpy(out_string,
		"service '"),
		(!env_ptr->service[0]) ? "<default>" : env_ptr->service, 255),
		"', network '"),
		(!env_ptr->network[0]) ? "<default>" : env_ptr->network, 255),
		"', daemon '"),
		(!env_ptr->daemon[0])  ? "<default>" : env_ptr->daemon,  255),
		'\''));
}
/*	***********************************************************************	*/

