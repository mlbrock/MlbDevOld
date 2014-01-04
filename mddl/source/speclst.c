/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Member Data Definition Library (MDDL) Source Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Constructs an array of MDDL structures from an
								array of pointers to strings.

	Revision History	:	1993-12-09 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <stdio.h>
#include <string.h>

#include "mddli.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MDDL_GetSpecMemberList

   SYNOPSIS    :	return_code = MDDL_GetSpecMemberList(spec_count,
							spec_list, in_member_count, in_member_list,
							out_member_count, out_member_list, error_text);

						int            return_code;

						unsigned int   spec_count;

						char         **spec_list;

						unsigned int   in_member_count;

						const MDDL    *in_member_list;

						unsigned int  *out_member_count;

						MDDL         **out_member_list;

						char          *error_text;

   DESCRIPTION :	Constructs a list of ''MDDL'' structures given a
						string containing the comma-separated member names.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``spec_count`` is the number of elements in the array
						``spec_list``.

						(.) ``spec_list`` is an array of ''char'' pointers of which
						each element contains the name of a member to be used to
						construct ``out_member_list``.

						(-) Member names may be specified multiple times within
						``spec_list`` and in any order. If a member is specified
						more that once, it will appear in the array
						``out_member_list`` more than once.

						(-) Elements of ``spec_list`` which contain a zero-length
						string will be ignored by this function.

						(.) ``in_member_count`` is the number of elements in the
						array ``in_member_list``.

						(.) ``in_member_list`` is the array of ''MDDL''
						structures which constitutes the list of members to be
						considered valid members by the program.

						(.) ``out_member_count`` is a pointer to an ''unsigned int''
						which this function will set to the number of elements in
						the array to which ``out_member_list`` points.

						(.) ``out_member_list`` is a pointer to an array of
						''MDDL'' structures which this function will
						allocate and populate for each member specified in the
						string ``member_spec_string``.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''MDDL_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	Returns from this function are as follow:

						(.) ''MDDL_SUCCESS'' if the function completes without
						error. ''MDDL_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero MDDL return codes
						indicative of error.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	MDDL_GetSpecMemberString

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2014 Michael L. Brock

   OUTPUT INDEX:	MDDL_GetSpecMemberList
						Member Description Functions:MDDL_GetSpecMemberList
						Member Data Definition Functions:see MDDL

   PUBLISH XREF:	MDDL_GetSpecMemberList

   PUBLISH NAME:	MDDL_GetSpecMemberList

	ENTRY CLASS	:	Member Description Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int MDDL_GetSpecMemberList(unsigned int spec_count, char **spec_list,
	unsigned int in_member_count, const MDDL *in_member_list,
	unsigned int *out_member_count, MDDL **out_member_list, char *error_text)
#else
int MDDL_GetSpecMemberList(spec_count, spec_list, in_member_count,
	in_member_list, out_member_count, out_member_list, error_text)
unsigned int   spec_count;
char         **spec_list;
unsigned int   in_member_count;
const MDDL    *in_member_list;
unsigned int  *out_member_count;
MDDL         **out_member_list;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code = MDDL_SUCCESS;
	unsigned int   count_1;
	unsigned int   count_2;
	int            found_flag;

	*out_member_count = 0;
	*out_member_list  = NULL;

	for (count_1 = 0; count_1 < spec_count; count_1++) {
		if (!spec_list[count_1][0])
			continue;
		for (count_2 = 0, found_flag = MDDL_FALSE;
			(count_2 < in_member_count) && (found_flag != MDDL_TRUE);
			count_2++) {
			if (!strcmp(spec_list[count_1], in_member_list[count_2].name)) {
				found_flag = MDDL_TRUE;
				break;
			}
		}
		if (found_flag != MDDL_TRUE) {
			sprintf(error_text,
				"The specified member name ('%.500s') is not valid.",
				spec_list[count_1]);
			return_code = MDDL_FAILURE;
			break;
		}
		else if ((return_code = MDDL_AppendMember(in_member_list + count_2,
			out_member_count, out_member_list, error_text)) != MDDL_SUCCESS)
			break;
	}

	if (return_code != MDDL_SUCCESS)
		mema_remove_all(out_member_count, ((void **) out_member_list));

	return(return_code);
}
/*	***********************************************************************	*/

