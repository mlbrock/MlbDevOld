/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Sybase CT-Library Support Functions Library Module						*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Returns the facility id for the Sybase CT-LIB
								facility.

	Revision History	:	1996-06-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Required include files . . .														*/
/*	***********************************************************************	*/

#include "dbcctlii.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_CTLIB_GetID

   SYNOPSIS    :	return_ptr = DBC_CTLIB_GetID(id_string);

						char *return_ptr;

						char *id_string;

   DESCRIPTION :	Returns the DBC Sybase CT-LIB facility name. This permits
						applications using a generic DBC facility attachment to
						determine the name of the underlying facility.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``id_string`` is the string into which this
						function is to place the DBC Sybase CT-LIB facility name
						''DBC_CTLIB_FACILITY_NAME''.

						(-) The length of the string to which ``id_string``
						points should be no less than the value of the manifest
						constant ''DBC_FACILITY_NAME_LENGTH'' + ''1''.

   RETURNS     :	Returns the ``id_string`` parameter.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	DBC_DBLIB_GetID

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2015 Michael L. Brock

   OUTPUT INDEX:	DBC_CTLIB_GetID
						DBC Sybase CT-LIB Functions:DBC_CTLIB_GetID
						DBC Functions:Facility ID Functions:DBC_CTLIB_GetID

   PUBLISH XREF:	DBC_CTLIB_GetID

   PUBLISH NAME:	DBC_CTLIB_GetID

	ENTRY CLASS	:	DBC Functions:Facility ID Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *DBC_CTLIB_GetID(char *id_string)
#else
char *DBC_CTLIB_GetID(id_string)
char *id_string;
#endif /* #ifndef NARGS */
{
	return(nstrcpy(id_string, DBC_CTLIB_FACILITY_NAME,
		DBC_FACILITY_NAME_LENGTH));
}
/*	***********************************************************************	*/

