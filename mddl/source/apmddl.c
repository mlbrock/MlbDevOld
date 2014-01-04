/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Member Data Definition Library (MDDL) Source Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Appends an MDDL structure to an array.

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

#include "mddli.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MDDL_AppendMember

   SYNOPSIS    :	return_code = MDDL_AppendMember(in_ptr, out_count, out_list,
							error_text);

						int            return_code;

						const MDDL    *in_ptr;

						unsigned int  *out_count;

						MDDL         **out_list;

						char          *error_text;

   DESCRIPTION :	Appends a single ''MDDL'' structure to a list of
						''MDDL'' structures.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_ptr`` is a pointer to the ''MDDL'' structure
						which is to be copied by this function.

						(.) ``out_count`` is a pointer to an ''unsigned int'' which
						contains the number of elements in the array ``out_list``.
						If the structure to which ``in_ptr`` points is successfully
						copied into the ``out_list``, this function will increment
						the ''unsigned int'' to which ``out_count`` points.

						(.) ``out_list`` is a pointer to the array of ''MDDL''
						structures into which ``in_ptr`` will be copied by this
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

   APPDRIGHT   :	Copyright 1993 - 2014 Michael L. Brock

   OUTPUT INDEX:	MDDL_AppendMember
						Copy Functions:MDDL_AppendMember
						Member Data Definition Functions:see MDDL

   PUBLISH XREF:	MDDL_AppendMember

   PUBLISH NAME:	MDDL_AppendMember

	ENTRY CLASS	:	Copy Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int MDDL_AppendMember(const MDDL *in_ptr, unsigned int *out_count,
	MDDL **out_list, char *error_text)
#else
int MDDL_AppendMember(in_ptr, out_count, out_list, error_text)
const MDDL    *in_ptr;
unsigned int  *out_count;
MDDL         **out_list;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code;
	MDDL member_data;

	if ((return_code = MDDL_CopyMember(in_ptr, &member_data, error_text)) ==
		MDDL_SUCCESS) {
		if (mema_append(out_count, ((void **) out_list), &member_data,
			sizeof(**out_list)) != STRFUNCS_SUCCESS) {
			MDDL_FreeMember(&member_data);
			STR_AllocMsgList(*out_count + 1, sizeof(**out_list), error_text,
				"Unable to allocate memory for the 'MDDL' list append");
			return_code = MDDL_MEMORY_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

