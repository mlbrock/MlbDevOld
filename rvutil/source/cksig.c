/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Checks the Tib/Rendezvous Utility Library signal-
								management data structures.

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

#include "rvutili.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_CheckSignalList(unsigned int signal_count,
	const RVUTIL_SIGNAL *signal_list, char *error_text)
{
	int          return_code = RVUTIL_SUCCESS;
	unsigned int count_1;

	for (count_1 = 0; count_1 < signal_count; count_1++) {
		if (signal_list[count_1].signal_number < 1) {
			sprintf(error_text,
				"Invalid signal number in element number %u ('%d').",
				count_1, signal_list[count_1].signal_number);
			return_code = RVUTIL_BAD_ARGS_FAILURE;
			break;
		}
		else if (!signal_list[count_1].signal_name) {
			sprintf(error_text,
				"Invalid signal name in element number %u (name is empty).",
				count_1);
			return_code = RVUTIL_BAD_ARGS_FAILURE;
			break;
		}
		else if ((signal_list[count_1].action < RVUTIL_SIGNAL_ACTION_MIN) ||
			(signal_list[count_1].action > RVUTIL_SIGNAL_ACTION_MAX)) {
			sprintf(error_text,
				"%s (%d) %s %u (%s = %d, %s = '%s'): %s '%d' and %d, inclusive.",
				"Invalid signal action", signal_list[count_1].action,
				"in signal list element number", count_1,
				"signal number", signal_list[count_1].signal_number,
				"signal name", signal_list[count_1].signal_name,
				"signal action values must be between",
				RVUTIL_SIGNAL_ACTION_MIN, RVUTIL_SIGNAL_ACTION_MAX);
			return_code = RVUTIL_BAD_ARGS_FAILURE;
			break;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_CheckSignalSpec(const RVUTIL_SIGNAL_SPEC *signal_spec,
	char *error_text)
{
	return(RVUTIL_CheckSignalList(signal_spec->signal_count,
		signal_spec->signal_list, error_text));
}
/*	***********************************************************************	*/

