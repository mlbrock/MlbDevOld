/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Formats an 'rvevm_Error' code with the value, its
								equivalent string, and an error message.

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

#include <limits.h>
#include <string.h>

#include <strfuncs.h>

#include "rvutili.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
char *RVUTIL_FormatString_rvevm_Error(rv_Session in_session,
	rvevm_Returns in_code, char *out_text)
{
	char buffer[RVUTIL_MAX_CODE_STR_TEXT + 1];

	return(chrcat(strcat(strcat(strcat(strcat(
		val2str(((unsigned long) ((in_code < 0) ? (0 - in_code) : in_code)),
		((int) in_code), 10, NULL, out_text),
		" = '"),
		RVUTIL_CodeToString_rvevm_Error(in_code, buffer)),
		"' = '"),
		rvevm_ErrorText(in_session, in_code)),
		'\''));
}
/*	***********************************************************************	*/

