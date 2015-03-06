/* *********************************************************************** */
/* *********************************************************************** */
/*	Data Type Alignment (DTA) Functions Library Source Module					*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Determines the length of the string necessary to
								store the data types represented by an array of
								'DTA' structures.

	Revision History	:	1992-02-23 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Include necessary header files . . .											*/
/* *********************************************************************** */

#include <limits.h>
#include <string.h>

#include "dtai.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  DTA_CalcListToStringLen

   SYNOPSIS    :  string_length = DTA_CalcListToStringLen(align_count,
							align_list);

						unsigned int     string_count;

						unsigned int     align_count;

						const DTA       *align_list;

   DESCRIPTION :  Calculates the string length (including terminating ASCII
						0) required to store the string equivalent of an array
						of ''DTA'' structures.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``align_count`` is the number of elements in the array
						``align_list``.

						(.) ``align_list`` is the array of ''DTA'' structures
						for which the string length is to be calculated.

   RETURNS     :  Returns from this function are as follow:

   NOTES       :  This function is used by the functions
						``DTA_ListToStringAlloc`` and
						``DTA_BASIC_ListToStringAlloc`` to determine the
						amount of memory to allocate for storage of an array of
						''DTA'' structures as a string.

   CAVEATS     :  

   SEE ALSO    :  

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2015 Michael L. Brock

   OUTPUT INDEX:	DTA_CalcListToStringLen
						Data Type Alignment Functions:DTA_CalcListToStringLen
						DTA:Functions:DTA_CalcListToStringLen
						DTA:Data Type Alignment Functions:DTA_CalcListToStringLen

   PUBLISH XREF:	DTA_CalcListToStringLen

   PUBLISH NAME:	DTA_CalcListToStringLen

	ENTRY CLASS	:	Data Type Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
unsigned int DTA_CalcListToStringLen(unsigned int align_count,
	const DTA *align_list)
#else
unsigned int DTA_CalcListToStringLen(align_count, align_list)
unsigned int     align_count;
const DTA       *align_list;
#endif /* #ifndef NARGS */
{
	unsigned int string_length = 1;
	unsigned int count_1;
	char         buffer[STR_VAL2STR_MAX_LEN + 1];

	for (count_1 = 0; count_1 < align_count; count_1++)
		string_length += 1 + ((align_list[count_1].array_length <= 1) ? 0 : (1 +
			strlen(val2str(((unsigned long) align_list[count_1].array_length),
			0, 10, NULL, buffer)) + 1));

	return(string_length);
}
/* *********************************************************************** */

