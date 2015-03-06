/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Basic management of RV code mapping to strings.

	Revision History	:	1996-01-12 --- Creation
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

#include <string.h>

#include "rvutili.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
char *RVUTIL_CodeToString(unsigned int in_count,
	const RVUTIL_CODE_STR_MAP *in_list, int in_code, char *out_text)
{
	const char   *tmp_ptr = "*** UNKNOWN RV ERROR ***";
	unsigned int  count_1;

	if ((in_code >= 0) && (in_code < ((int) in_count)) &&
		(in_code == in_list[in_code].code_value))
		tmp_ptr = in_list[in_code].code_text;
	else {
		for (count_1 = 0; count_1 < in_count; count_1++) {
			if (in_code == in_list[count_1].code_value) {
				tmp_ptr = in_list[count_1].code_text;
				break;
			}
		}
	}

	return(strcpy(out_text, tmp_ptr));
}
/*	***********************************************************************	*/

