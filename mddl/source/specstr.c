/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Member Data Definition Library (MDDL) Source Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Constructs an array of MDDL structures from a
								string.

	Revision History	:	1993-12-09 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <stdlib.h>
#include <string.h>

#include "mddli.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MDDL_GetSpecMemberString

   SYNOPSIS    :	return_code = MDDL_GetSpecMemberString(spec_string,
							in_member_count, in_member_list, out_member_count,
							out_member_list, error_text);

						int            return_code;

						const char    *spec_string;

						unsigned int   in_member_count;

						const MDDL    *in_member_list;

						unsigned int  *out_member_count;

						MDDL         **out_member_list;

						char          *error_text;

   DESCRIPTION :	Constructs a list of ''MDDL'' structures given a
						string containing the comma-separated member names.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``spec_string`` is a ''char'' string which contains the
						comma-separated names of the members to be used to construct
						``out_member_list``.

						(-) Member names may be specified multiple times within
						``spec_string`` and in any order. If a member is specified
						more that once, it will appear in the array
						``out_member_list`` more than once.

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
						string ``spec_string``.

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

   SEE ALSO    :	MDDL_GetSpecMemberList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	MDDL_GetSpecMemberString
						Member Description Functions:MDDL_GetSpecMemberString
						Member Data Definition Functions:see MDDL

   PUBLISH XREF:	MDDL_GetSpecMemberString

   PUBLISH NAME:	MDDL_GetSpecMemberString

	ENTRY CLASS	:	Member Description Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int MDDL_GetSpecMemberString(const char *spec_string,
	unsigned int in_member_count, const MDDL *in_member_list,
	unsigned int *out_member_count, MDDL **out_member_list, char *error_text)
#else
int MDDL_GetSpecMemberString(spec_string, in_member_count,
	in_member_list, out_member_count, out_member_list, error_text)
const char    *spec_string;
unsigned int   in_member_count;
const MDDL    *in_member_list;
unsigned int  *out_member_count;
MDDL         **out_member_list;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code;
	unsigned int   spec_count  = 0;
	char         **spec_list   = NULL;
	char          *tmp_string;

	*out_member_count = 0;
	*out_member_list  = NULL;

	if ((tmp_string = strdup(spec_string)) == NULL) {
		STR_AllocMsgItem(strlen(spec_string) + 1, error_text,
			"Unable to copy the member name specification string");
		return_code = MDDL_MEMORY_FAILURE;
	}
	else {
		if (sepwordx(trim(noblank(nocontrl(tmp_string))), ",", &spec_count,
			&spec_list) != STRFUNCS_SUCCESS) {
			STR_AllocMsgPtrList(chrcnt(tmp_string, ',') + 1,
				strlen(tmp_string) + (chrcnt(tmp_string, ',') + 1), error_text,
				"Unable to allocate the member name specification list");
			return_code = MDDL_MEMORY_FAILURE;
		}
		else {
			return_code = MDDL_GetSpecMemberList(spec_count, spec_list,
				in_member_count, in_member_list, out_member_count,
				out_member_list, error_text);
			strl_remove_all(&spec_count, &spec_list);
		}
		free(tmp_string);
	}

	return(return_code);
}
/*	***********************************************************************	*/

