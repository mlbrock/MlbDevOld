/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Internal Null Support Functions Library Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Returns the vendor name for the Internal NULL
								facility.

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

#include "dbcnulli.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_NULL_GetVendorName

   SYNOPSIS    :	return_ptr = DBC_NULL_GetVendorName(vendor_name);

						char *return_ptr;

						char *vendor_name;

   DESCRIPTION :	Returns the DBC Internal NULL facility name. This permits
						applications using a generic DBC facility attachment to
						determine the name of the underlying facility.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``vendor_name`` is the string into which this
						function is to place the DBC Internal NULL facility name
						''DBC_NULL_VENDOR_NAME''.

						(-) The length of the string to which ``vendor_name``
						points should be no less than the value of the manifest
						constant ''DBC_VENDOR_NAME_LENGTH'' + ''1''.

   RETURNS     :	Returns the ``vendor_name`` parameter.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	DBC_CTLIB_GetVendorName

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	DBC_NULL_GetVendorName
						DBC Internal NULL Functions:DBC_NULL_GetVendorName
						DBC Functions:Facility Vendor Name Functions:DBC_NULL_GetVendorName

   PUBLISH XREF:	DBC_NULL_GetVendorName

   PUBLISH NAME:	DBC_NULL_GetVendorName

	ENTRY CLASS	:	DBC Functions:Facility Vendor Name Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *DBC_NULL_GetVendorName(char *vendor_name)
#else
char *DBC_NULL_GetVendorName(vendor_name)
char *vendor_name;
#endif /* #ifndef NARGS */
{
	return(nstrcpy(vendor_name, DBC_NULL_VENDOR_NAME,
		DBC_VENDOR_NAME_LENGTH));
}
/*	***********************************************************************	*/

