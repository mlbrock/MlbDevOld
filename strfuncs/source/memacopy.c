/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Copies an array.

	Revision History	:	1991-08-22 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1991 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Include necessary header files . . .											*/
/* *********************************************************************** */

#include <memory.h>
#include <stdlib.h>

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  mema_copy

   SYNOPSIS    :  return_code = mema_copy(in_data_count, in_data_list,
							data_length, out_data_count, out_data_list);

						int            return_code;

						unsigned int   in_data_count;

						const void    *in_data_list;

						size_t         data_length;

						unsigned int  *out_data_count;

						void         **out_data_list;

   DESCRIPTION :  Copies the records in the array ``in_data_list`` to the
						array ``out_data_list``.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_data_count`` is the number of records in the
						source array ``in_data_list``.

						(.) ``in_data_list`` is the array of records to be copied.

						(.) ``data_length`` is the size of the elements of the two
						arrays ``in_data_list`` and ``out_data_list``.

						(.) ``out_data_count`` points to an integer which will
						contain the number of records the destination array
						``out_data_list`` if this function is successful.

						(.) ``out_data_list`` points to the destination array to
						which records from ``in_data_list`` are to be copied.
						Memory will be allocated for this array by the function.

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_SUCCESS'' if no error occurred.

						(.) One of the non-zero STRFUNCS return codes if an error
						occurred.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  mema_add
						mema_append
						mema_insert
						mema_remove
						meml_copy

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2016 Michael L. Brock

   OUTPUT INDEX:  mema_copy
						Memory Array Functions:mema_copy
						STRFUNCS:Memory Array Functions:mema_copy
						String Functions:See STRFUNCS

   PUBLISH XREF:  mema_copy

   PUBLISH NAME:	mema_copy

	ENTRY CLASS	:	Memory Array Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int mema_copy(unsigned int in_data_count, const void *in_data_list,
	size_t data_length, unsigned int *out_data_count, void **out_data_list)
#else
int mema_copy(in_data_count, in_data_list, data_length, out_data_count,
	out_data_list)
unsigned int   in_data_count;
const void    *in_data_list;
size_t         data_length;
unsigned int  *out_data_count;
void         **out_data_list;
#endif /* #ifndef NARGS */
{
	int return_code = STRFUNCS_SUCCESS;

	*out_data_count = 0;
	*out_data_list  = NULL;

	if (in_data_count) {
		if ((*out_data_list = malloc(in_data_count * data_length)) == NULL)
			return_code = STRFUNCS_FAILURE;
		else {
			memcpy(*out_data_list, in_data_list, in_data_count * data_length);
			*out_data_count = in_data_count;
		}
	}

	return(return_code);
}
/*	*********************************************************************** */

