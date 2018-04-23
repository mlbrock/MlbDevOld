/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Generalized Support Functions Library Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Returns the vendor name for a facility.

	Revision History	:	1993-07-07 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2018.
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

   NAME        :	DBC_GetVendorName

   SYNOPSIS    :	return_ptr = DBC_GetVendorName(dbc_context_ptr, vendor_name);

						char              *return_ptr;

						const DBC_CONTEXT *dbc_context_ptr;

						char              *vendor_name;

   DESCRIPTION :	Returns a DBC facility vendor name. This permits
						applications using a generic DBC facility attachment to
						determine the vendor name of the underlying facility.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``dbc_context_ptr`` is a pointer to the
						''DBC_CONTEXT'' structure to be used as the facility
						upon which this function is to operate.

						(.) ``vendor_name`` is the string into which this
						function is to place the DBC facility vendor name.

						(-) The length of the string to which ``vendor_name``
						points should be no less than the value of the manifest
						constant ''DBC_VENDOR_NAME_LENGTH'' + ''1''.

   RETURNS     :	Returns the ``vendor_name`` parameter.

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	DBC_GetVendorName
						Database Functions:DBC_GetVendorName
						DBC Functions:Facility Vendor Name Functions:DBC_GetVendorName

   PUBLISH XREF:	DBC_GetVendorName

   PUBLISH NAME:	DBC_GetVendorName

	ENTRY CLASS	:	Database Functions:Facility Functions
						DBC Functions:Facility Vendor Name Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *DBC_GetVendorName(const DBC_CONTEXT *dbc_context_ptr, char *vendor_name)
#else
char *DBC_GetVendorName(dbc_context_ptr, vendor_name)
const DBC_CONTEXT *dbc_context_ptr;
char              *vendor_name;
#endif /* #ifndef NARGS */
{
	return((DBC_CheckFunction(dbc_context_ptr,
		((const void **) &dbc_context_ptr->dbc_funcs.get_vendor_name), NULL) ==
		DBC_SUCCESS) ? (*dbc_context_ptr->dbc_funcs.get_vendor_name)
		(vendor_name) : nstrcpy(vendor_name, "* No vendor name available *",
		DBC_VENDOR_NAME_LENGTH));
}
/*	***********************************************************************	*/

