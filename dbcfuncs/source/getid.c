/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Generalized Support Functions Library Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Returns the facility id for a facility.

	Revision History	:	1993-07-07 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Required include files . . .														*/
/*	***********************************************************************	*/

#include "dbcfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_GetID

   SYNOPSIS    :	return_ptr = DBC_GetID(dbc_context_ptr, id_string);

						char              *return_ptr;

						const DBC_CONTEXT *dbc_context_ptr;

						char              *id_string;

   DESCRIPTION :	Returns a DBC facility name. This permits applications
						using a generic DBC facility attachment to determine the
						name of the underlying facility.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``dbc_context_ptr`` is a pointer to the
						''DBC_CONTEXT'' structure to be used as the facility
						upon which this function is to operate.

						(.) ``id_string`` is the string into which this
						function is to place the DBC facility name.

						(-) The length of the string to which ``id_string``
						points should be no less than the value of the manifest
						constant ''DBC_FACILITY_NAME_LENGTH'' + ''1''.

   RETURNS     :	Returns the ``id_string`` parameter.

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2016 Michael L. Brock

   OUTPUT INDEX:	DBC_GetID
						Database Functions:Facility Functions:DBC_GetID
						DBC Functions:Facility ID Functions:DBC_GetID

   PUBLISH XREF:	DBC_GetID

   PUBLISH NAME:	DBC_GetID

	ENTRY CLASS	:	Database Functions:Facility Functions
						DBC Functions:Facility ID Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *DBC_GetID(const DBC_CONTEXT *dbc_context_ptr, char *id_string)
#else
char *DBC_GetID(dbc_context_ptr, id_string)
const DBC_CONTEXT *dbc_context_ptr;
char              *id_string;
#endif /* #ifndef NARGS */
{
	return((DBC_CheckFunction(dbc_context_ptr,
		((const void **) &dbc_context_ptr->dbc_funcs.get_id), NULL) ==
		DBC_SUCCESS) ? (*dbc_context_ptr->dbc_funcs.get_id)(id_string) :
		nstrcpy(id_string, "* No facility name available *",
		DBC_FACILITY_NAME_LENGTH));
}
/*	***********************************************************************	*/

