/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Member Data Definition Library (MDDL) Source Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Copies MDDL structures.

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

#include <stdlib.h>
#include <string.h>

#include "mddli.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MDDL_CopyMember

   SYNOPSIS    :	return_code = MDDL_CopyMember(in_ptr, out_ptr, error_text);

						int         return_code;

						const MDDL *in_ptr;

						MDDL       *out_ptr;

						char       *error_text;

   DESCRIPTION :	Copies a single ''MDDL'' structures.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_ptr`` is a pointer to the ''MDDL'' structure
						which is to be copied by this function.

						(.) ``out_ptr`` is a pointer to the ''MDDL''
						structure into which the copy is to be performed.

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

   SEE ALSO    :	MDDL_CopyMemberList
						MDDL_AppendMember

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2014 Michael L. Brock

   OUTPUT INDEX:	MDDL_CopyMember
						Copy Functions:MDDL_CopyMember
						Member Data Definition Functions:see MDDL

   PUBLISH XREF:	MDDL_CopyMember

   PUBLISH NAME:	MDDL_CopyMember

	ENTRY CLASS	:	Copy Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int MDDL_CopyMember(const MDDL *in_ptr, MDDL *out_ptr, char *error_text)
#else
int MDDL_CopyMember(in_ptr, out_ptr, error_text)
const MDDL *in_ptr;
MDDL       *out_ptr;
char       *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = MDDL_SUCCESS;

	*out_ptr = *in_ptr;

	if ((in_ptr->display_name != NULL) && ((out_ptr->display_name =
		strdup(in_ptr->display_name)) == NULL)) {
		MDDL_InitMember(out_ptr);
		STR_AllocMsgItem(strlen(in_ptr->display_name) + 1, error_text,
			"Unable to copy a 'MDDL' display name");
		return_code = MDDL_MEMORY_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MDDL_CopyMemberList

   SYNOPSIS    :	return_code = MDDL_CopyMemberList(in_count, in_list,
							out_count, out_list);

						int            return_code;

						unsigned int   in_count;

						const MDDL    *in_list;

						unsigned int  *out_count;

						MDDL         **out_list;

						char          *error_text;

   DESCRIPTION :	Copies an array of ''MDDL'' structures.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_count`` is the number of elements in the array
						``in_list``.

						(.) ``in_list`` is the array of ''MDDL'' structures
						which is to be copied by this function.

						(.) ``out_count`` is a pointer to an ''unsigned int'' into
						which this function will place the number of elements
						copied.

						(.) ``out_list`` is a pointer to the array of ''MDDL''
						structures which will be allocated and copied by this
						function.

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

   SEE ALSO    :	MDDL_CopyMember

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2014 Michael L. Brock

   OUTPUT INDEX:	MDDL_CopyMemberList
						Copy Functions:MDDL_CopyMemberList
						Member Data Definition Functions:see MDDL

   PUBLISH XREF:	MDDL_CopyMemberList

   PUBLISH NAME:	MDDL_CopyMemberList

	ENTRY CLASS	:	Copy Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int MDDL_CopyMemberList(unsigned int in_count, const MDDL *in_list,
	unsigned int *out_count, MDDL **out_list, char *error_text)
#else
int MDDL_CopyMemberList(in_count, in_list, out_count, out_list, error_text)
unsigned int   in_count;
const MDDL    *in_list;
unsigned int  *out_count;
MDDL         **out_list;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = MDDL_SUCCESS;
	unsigned int count_1;

	*out_count = 0;
	*out_list  = NULL;

	if (in_count) {
		if ((*out_list = ((MDDL *) calloc(in_count, sizeof(*in_list)))) ==
			NULL) {
			STR_AllocMsgList(in_count, sizeof(**out_list), error_text,
				"Unable to allocate memory for the 'MDDL' list copy");
			return_code = MDDL_MEMORY_FAILURE;
		}
		else {
			*out_count = in_count;
			MDDL_InitMemberList(*out_count, *out_list);
			for (count_1 = 0; count_1 < in_count; count_1++) {
				if ((return_code = MDDL_CopyMember(in_list + count_1,
					*out_list + count_1, error_text)) != MDDL_SUCCESS) {
					MDDL_FreeMemberList(out_count, out_list);
					break;
				}
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

