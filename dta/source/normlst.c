/* *********************************************************************** */
/* *********************************************************************** */
/*	Data Type Alignment (DTA) Functions Library Source Module					*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Normalizes an array of 'DTA' structures.

	Revision History	:	1992-02-23 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2016.
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

   NAME        :  DTA_NormalizeList

   SYNOPSIS    :  DTA_NormalizeList(align_count, align_list);

						unsigned int  *align_count;

						DTA          **align_list;

   DESCRIPTION :  Normalizes an array of ''DTA'' structures by
						concatenating adjacent similar type specifications into
						a single type specification.

						For example, if ``align_list`` contains the adjacent
						elements equivalent to:

{|@|}c[10]c[3]

						Normalization of those elements will result in a single
						element equivalent to:

{|@|}c[13]

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``align_count`` is the number of elements in the array
						``align_list``.

						(.) ``align_list`` is the array of ''DTA'' structures
						which is to be normalized.

   RETURNS     :  Void.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  DTA_NormalizeList

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2016 Michael L. Brock

   OUTPUT INDEX:	DTA_NormalizeList
						Data Type Alignment Functions:DTA_NormalizeList
						DTA:Functions:DTA_NormalizeList
						DTA:Data Type Alignment Functions:DTA_NormalizeList

   PUBLISH XREF:	DTA_NormalizeList

   PUBLISH NAME:	DTA_NormalizeList

	ENTRY CLASS	:	Data Type Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
void DTA_NormalizeList(unsigned int *align_count, DTA **align_list)
#else
void DTA_NormalizeList(align_count, align_list)
unsigned int  *align_count;
DTA          **align_list;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;

	for (count_1 = 1; count_1 < *align_count; ) {
		if ((*align_list)[count_1].type == (*align_list)[count_1 - 1].type) {
			(*align_list)[count_1 - 1].array_length +=
				(*align_list)[count_1].array_length;
			(*align_list)[count_1 - 1].length       +=
				(*align_list)[count_1].length;
			mema_remove(align_count, ((void **) align_list),
				sizeof(**align_list), count_1, 1);
		}
		else
			count_1++;
	}
}
/* *********************************************************************** */

