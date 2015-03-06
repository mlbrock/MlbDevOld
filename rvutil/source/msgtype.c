/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Maps an 'rvmsg_Type' to its string equivalent.

	Revision History	:	1996-01-20 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <strfuncs.h>

#include "rvutili.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
char *RVUTIL_GetMsgTypeName(rvmsg_Type msg_type, char *msg_type_name)
{
	return(nstrcpy(msg_type_name,
		(msg_type == RVMSG_BADDATA)   ? "RVMSG_BADDATA"   :
		(msg_type == RVMSG_RVMSG)     ? "RVMSG_RVMSG"     :
		(msg_type == RVMSG_SUBJECT)   ? "RVMSG_SUBJECT"   :
		(msg_type == RVMSG_DATETIME)  ? "RVMSG_DATETIME"  :
		(msg_type == RVMSG_OPAQUE)    ? "RVMSG_OPAQUE"    :
		(msg_type == RVMSG_STRING)    ? "RVMSG_STRING"    :
		(msg_type == RVMSG_BOOLEAN)   ? "RVMSG_BOOLEAN"   :
		(msg_type == RVMSG_IPDATA)    ? "RVMSG_IPDATA"    :
		(msg_type == RVMSG_INT)       ? "RVMSG_INT"       :
		(msg_type == RVMSG_UINT)      ? "RVMSG_UINT"      :
		(msg_type == RVMSG_REAL)      ? "RVMSG_REAL"      :
		(msg_type == RVMSG_NONE)      ? "RVMSG_NONE"      :
		(msg_type == RVMSG_ENCRYPTED) ? "RVMSG_ENCRYPTED" :
		"*** Invalid 'rvmsg_Type' ***", RVUTIL_MAX_RVMSG_TYPE_NAME));
}
/*	***********************************************************************	*/

