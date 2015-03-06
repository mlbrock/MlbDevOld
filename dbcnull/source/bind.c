/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Internal Null Support Functions Library Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Performs a Internal bind using a description of the
								structure to which the bind is to be made for the
								Internal NULL facility.

	Revision History	:	1993-07-07 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Required include files . . .														*/
/*	***********************************************************************	*/

#include <string.h>

#include "dbcnulli.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_NULL_BindMembers

   SYNOPSIS    :	return_code = DBC_NULL_BindMembers(dbc_control_ptr,
							member_count, member_list, table_name, bind_buffer,
							error_text);

						int                return_code;

						DBC_NULL *dbc_control_ptr;

						unsigned int       member_count;

						const MDDL  *member_list;

						const char        *table_name;

						void              *bind_buffer;

						char              *error_text;

   DESCRIPTION :	Binds one or more columns to a memory buffer.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``dbc_control_ptr`` is a pointer to the
						''DBC_NULL'' structure to be used to manage
						communication with the database. It is assumed by this
						function that the structure has been properly initialized
						by ``DBC_NULL_Initialize`` and that a connection to a
						Internal database has been performed by ``DBC_NULL_Open``.

						(.) ``member_count`` is the number of elements in the array
						``member_list``.

						(.) ``member_list`` is an array of ''MDDL'' structures
						which describe the columns to be bound by this function.

						(.) ``table_name`` is the name of the table (or view) for
						the bind. It is used only in error messages, so it may be
						passed as ''NULL''.

						(.) ``bind_buffer`` points to the area of memory to which
						the bind is to be performed. 

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''DBC_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	This function returns a DBC return codes manifest constant:

						(.) ''DBC_SUCCESS'' if the function completes without
						error.

						(.) One of the defined non-zero DBC return codes indicative
						of error.

   NOTES       :	This function is called by ``DBC_NULL_GetRows``. There is
						little need for application programmers to call it directly.

   CAVEATS     :	

   SEE ALSO    :	DBC_CTLIB_BindMembers

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2015 Michael L. Brock

   OUTPUT INDEX:	DBC_NULL_BindMembers
						DBC Internal NULL Functions:DBC_NULL_BindMembers
						DBC Functions:Bind Functions:DBC_NULL_BindMembers

   PUBLISH XREF:	DBC_NULL_BindMembers

   PUBLISH NAME:	DBC_NULL_BindMembers

	ENTRY CLASS	:	DBC Functions:Bind Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int DBC_NULL_BindMembers(DBC_NULL *dbc_control_ptr, unsigned int member_count,
	const MDDL *member_list, const char *table_name, void *bind_buffer,
	char *error_text)
#else
int DBC_NULL_BindMembers(dbc_control_ptr, member_count, member_list,
	table_name, bind_buffer, error_text)
DBC_NULL     *dbc_control_ptr;
unsigned int  member_count;
const MDDL   *member_list;
const char   *table_name;
void         *bind_buffer;
char         *error_text;
#endif /* #ifndef NARGS */
{
	strcat(strcpy(error_text, DBC_NULL_BASE_ERROR_TEXT),
		"'DBC_NULL_BindMembers()' failed.");

	return(DBC_FAILURE);
}
/*	***********************************************************************	*/

