/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Converts an array to a list.

	Revision History	:	1991-08-22 --- Creation
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

#include <memory.h>
#include <stdlib.h>

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  mema_to_meml

   SYNOPSIS    :  return_code = mema_to_meml(in_data_count, in_data_array,
							data_length, out_data_count, out_data_list);

						int             return_code;

						unsigned int    in_data_count;

						const void     *in_data_array;

						size_t          data_length;

						unsigned int   *out_data_count;

						void         ***out_data_list;

   DESCRIPTION :  Converts the records in the array ``in_data_array`` to the
						list ``out_data_list``. That is, a ''void *'' array is
						converted to a ''void **'' list of pointers to memory.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_data_count`` is the number of records in the
						source ''const void *'' array ``in_data_array``.

						(.) ``in_data_array`` is the array of records to be copied.

						(.) ``data_length`` is the size of the elements of
						``in_data_array`` and ``out_data_list``.

						(.) ``out_data_count`` points to an integer which will
						contain the number of records the destination list
						``out_data_list`` if this function is successful.

						(.) ``out_data_list`` points to the destination list to
						which records from ``in_data_array`` are to be copied.
						Memory will be allocated for this array by the function.

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_SUCCESS'' if no error occurred.

						(.) One of the non-zero STRFUNCS return codes if an error
						occurred.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  meml_to_mema
						mema_copy

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2018 Michael L. Brock

   OUTPUT INDEX:  mema_to_meml
						Memory Array Functions:mema_to_meml
						STRFUNCS:Memory Array Functions:mema_to_meml
						String Functions:See STRFUNCS

   PUBLISH XREF:  mema_to_meml

   PUBLISH NAME:	mema_to_meml

	ENTRY CLASS	:	Memory Array Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int mema_to_meml(unsigned int in_data_count, const void *in_data_array,
	size_t data_length, unsigned int *out_data_count, void ***out_data_list)
#else
int mema_to_meml(in_data_count, in_data_array, data_length, out_data_count,
	out_data_list)
unsigned int    in_data_count;
const void     *in_data_array;
size_t          data_length;
unsigned int   *out_data_count;
void         ***out_data_list;
#endif /* #ifndef NARGS */
{
	int           return_code = STRFUNCS_SUCCESS;
	unsigned int  count_1;
	const char   *tmp_ptr;

	*out_data_count = 0;
	*out_data_list  = NULL;

	if (((!in_data_count) && (in_data_array != NULL)) ||
		(in_data_count && (in_data_array == NULL)) || (!data_length))
		return_code = STRFUNCS_FAILURE;
	else if (in_data_count) {
		if ((return_code = meml_allocate(out_data_count, out_data_list,
			data_length, in_data_count)) == STRFUNCS_SUCCESS) {
			for (count_1 = 0, tmp_ptr = ((const char *) in_data_array);
				count_1 < in_data_count; count_1++, tmp_ptr += data_length)
				memcpy((*out_data_list)[count_1], tmp_ptr, data_length);
		}
	}

	return(return_code);
}
/*	*********************************************************************** */

