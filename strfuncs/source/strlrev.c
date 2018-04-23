/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Reverses the order of an array of pointers.

	Revision History	:	1991-09-26 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1991 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Include necessary header files . . .											*/
/* *********************************************************************** */

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  STR_LIST_reverse

   SYNOPSIS    :  STR_LIST_reverse(data_count, data_list);

						unsigned int   data_count;

						void         **data_list;

   DESCRIPTION :  Reverses the order of an array of pointers.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``data_count`` is the number of elements in the array
						of pointers ``data_list``.

						(.) ``data_list`` is the array of pointers to be reversed.

   RETURNS     :  Void.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2018 Michael L. Brock

   OUTPUT INDEX:  STR_LIST_reverse
						Memory List Functions:STR_LIST_reverse
						STRFUNCS:Memory List Functions:STR_LIST_reverse
						String Functions:See STRFUNCS

   PUBLISH XREF:  STR_LIST_reverse

   PUBLISH NAME:	STR_LIST_reverse

	ENTRY CLASS	:	Memory List Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
void STR_LIST_reverse(unsigned int data_count, void **data_list)
#else
void STR_LIST_reverse(data_count, data_list)
unsigned int   data_count;
void         **data_list;
#endif /* #ifndef NARGS */
{
	unsigned int  count_1;
	unsigned int  last_offset;
	void         *tmp_ptr;

	for (count_1 = 0; count_1 < (data_count / 2); count_1++) {
		last_offset            = data_count - (count_1 + 1);
		tmp_ptr                = data_list[count_1];
		data_list[count_1]     = data_list[last_offset];
		data_list[last_offset] = tmp_ptr;
	}
}
/*	*********************************************************************** */

