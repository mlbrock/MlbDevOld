/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Member Data Definition Library (MDDL) Source Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Sets the 'display_name' member.

	Revision History	:	1993-12-09 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2016.
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

   NAME        :	MDDL_SetDisplayName

   SYNOPSIS    :	return_code = MDDL_SetDisplayName(member_ptr,
							display_name, error_text);

						int         return_code;

						MDDL       *member_ptr;

						const char *display_name;

						char       *error_text;

   DESCRIPTION :	Sets the ``display_name`` member of a ''MDDL''
						structure to a specified string.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``member_ptr`` points to the ''MDDL'' structure
						for which the ``display_name`` member is to be modified by
						this function.

						(.) ``display_name`` is the string to which this function is
						set the ``display_name`` member.

						(-) If ``display_name`` is not ''NULL'', any memory
						associated with the ``display_name`` member will be freed
						and the member will be set to the newly-allocated copy of
						the ``display_name`` parameter.

						(-) If ``display_name`` is ''NULL'', any memory associated
						with the ``display_name`` member will be freed and the
						member will be set to ''NULL''.

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

   SEE ALSO    :	MDDL_CreateDisplayName
						MDDL_CreateDisplayNameList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2016 Michael L. Brock

   OUTPUT INDEX:	MDDL_SetDisplayName
						Member Description Functions:MDDL_SetDisplayName
						Member Data Definition Functions:see MDDL

   PUBLISH XREF:	MDDL_SetDisplayName

   PUBLISH NAME:	MDDL_SetDisplayName

	ENTRY CLASS	:	Member Description Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int MDDL_SetDisplayName(MDDL *member_ptr, const char *display_name,
	char *error_text)
#else
int MDDL_SetDisplayName(member_ptr, display_name, error_text)
MDDL       *member_ptr;
const char *display_name;
char       *error_text;
#endif /* #ifndef NARGS */
{
	int   return_code = MDDL_SUCCESS;
	char *tmp_ptr     = NULL;

	if ((display_name == NULL) || ((tmp_ptr = strdup(display_name)) != NULL)) {
		if (member_ptr->display_name != NULL)
			free(member_ptr->display_name);
		member_ptr->display_name = tmp_ptr;
	}
	else if (display_name != NULL) {
		STR_AllocMsgItem(strlen(display_name) + 1, error_text,
			"Unable to allocate for a 'MDDL' display name");
		return_code = MDDL_MEMORY_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MDDL_CreateDisplayNameList

   SYNOPSIS    :	return_code = MDDL_CreateDisplayNameList(member_count,
							member_list, error_text);

						int           return_code;

						unsigned int  member_count;

						MDDL         *member_ptr;

						char         *error_text;

   DESCRIPTION :	Initializes the ``display_name`` members of a list of
						''MDDL'' structures to a string derived from the
						``name`` members of the structures in the list.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``member_count`` is the number of elements in the
						array ``member_list``.

						(.) ``member_list`` is the array of ''MDDL''
						structures for which the ``display_name`` member is to be
						initialized by this function.

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

   NOTES       :	This function creates the ``display_member`` from the
						``name`` member by doing the following:

						(+) A copy is made of the string in the ``name`` member.

						(+) All underscores (''_'') in the copied ``name`` member
						are replaced by spaces.

						(+) Multiple spaces in the copied ``name`` member are
						replaced by a single space.

						(+) Leading and trailing spaces the copied ``name`` member
						are removed.

						(+) The initial character of each word in the copied
						``name`` member (where ``word``s are separated by a space
						character) is mapped to upper-case. All other characters are
						mapped to lower-case.

						(+) The resulting string is assigned to the ``display_name``
						member.

   CAVEATS     :	

   SEE ALSO    :	MDDL_CreateDisplayName

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2016 Michael L. Brock

   OUTPUT INDEX:	MDDL_CreateDisplayNameList
						Member Description Functions:MDDL_CreateDisplayNameList
						Member Data Definition Functions:see MDDL

   PUBLISH XREF:	MDDL_CreateDisplayNameList

   PUBLISH NAME:	MDDL_CreateDisplayNameList

	ENTRY CLASS	:	Member Description Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int MDDL_CreateDisplayNameList(unsigned int member_count, MDDL *member_list,
	char *error_text)
#else
int MDDL_CreateDisplayNameList(member_count, member_list, error_text)
unsigned int  member_count;
MDDL         *member_list;
char         *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = MDDL_SUCCESS;

	for ( ; member_count ; member_count--, member_list++) {
		if ((return_code = MDDL_CreateDisplayName(member_list,
			error_text)) != MDDL_SUCCESS)
			break;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MDDL_CreateDisplayName

   SYNOPSIS    :	return_code = MDDL_CreateDisplayName(member_ptr,
							error_text);

						int   return_code;

						MDDL *member_ptr;

						char *error_text;

   DESCRIPTION :	Initializes the ``display_name`` member of a ''MDDL''
						structure to a string derived from the ``name`` member of
						the structure.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``member_ptr`` points to to ''MDDL'' structure
						for which the ``display_name`` member is to be initialized
						by this function.

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

   NOTES       :	This function creates the ``display_member`` from the
						``name`` member by doing the following:

						(+) A copy is made of the string in the ``name`` member.

						(+) All underscores (''_'') in the copied ``name`` member
						are replaced by spaces.

						(+) Multiple spaces in the copied ``name`` member are
						replaced by a single space.

						(+) Leading and trailing spaces the copied ``name`` member
						are removed.

						(+) The initial character of each word in the copied
						``name`` member (where ``word``s are separated by a space
						character) is mapped to upper-case. All other characters are
						mapped to lower-case.

						(+) The resulting string is assigned to the ``display_name``
						member.

   CAVEATS     :	

   SEE ALSO    :	MDDL_CreateDisplayNameList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2016 Michael L. Brock

   OUTPUT INDEX:	MDDL_CreateDisplayName
						Member Description Functions:MDDL_CreateDisplayName
						Member Data Definition Functions:see MDDL

   PUBLISH XREF:	MDDL_CreateDisplayName

   PUBLISH NAME:	MDDL_CreateDisplayName

	ENTRY CLASS	:	Member Description Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int MDDL_CreateDisplayName(MDDL *member_ptr, char *error_text)
#else
int MDDL_CreateDisplayName(member_ptr, error_text)
MDDL *member_ptr;
char *error_text;
#endif /* #ifndef NARGS */
{
	char *tmp_ptr;
	char  display_name[sizeof(member_ptr->name)];

	nstrcpy(display_name, member_ptr->name, sizeof(display_name) - 1);

	while ((tmp_ptr = strchr(trim(oneblank(display_name)), '_')) != NULL)
		*tmp_ptr = ' ';

	return(MDDL_SetDisplayName(member_ptr, initcaps(display_name),
		error_text));
}
/*	***********************************************************************	*/

