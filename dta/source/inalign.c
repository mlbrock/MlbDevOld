/* *********************************************************************** */
/* *********************************************************************** */
/*	Data Type Alignment (DTA) Functions Library Source Module					*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes the members of a 'DTA' structure.

	Revision History	:	1992-02-23 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Include necessary header files . . .											*/
/* *********************************************************************** */

#include "dtai.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  DTA_InitAlign

   SYNOPSIS    :  DTA_InitAlign(align_ptr);

						DTA *align_ptr;

   DESCRIPTION :  Initializes a ''DTA'' structure.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``align_ptr`` points to the ''DTA'' structure
						to be initialized.

   RETURNS     :  Void.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	DTA_InitAlign
						Data Type Alignment Functions:DTA_InitAlign
						DTA:Functions:DTA_InitAlign
						DTA:Data Type Alignment Functions:DTA_InitAlign

   PUBLISH XREF:	DTA_InitAlign

   PUBLISH NAME:	DTA_InitAlign

	ENTRY CLASS	:	Data Type Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
void DTA_InitAlign(DTA *align_ptr)
#else
void DTA_InitAlign(align_ptr)
DTA *align_ptr;
#endif /* #ifndef NARGS */
{
	align_ptr->type         = 0;
	align_ptr->array_length = 0;
	align_ptr->offset       = 0;
	align_ptr->length       = 0;
}
/* *********************************************************************** */

