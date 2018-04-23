/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Copies an array of pointers.

	Revision History	:	1991-10-02 --- Creation
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

   NAME        :  meml_copy

   SYNOPSIS    :  return_code = meml_copy(in_data_count, in_data_list,
							data_length, out_data_count, out_data_list);

						int             return_code;

						unsigned int    in_data_count;

						void          **in_data_list;

						size_t          data_length;

						unsigned int   *out_data_count;

						void         ***out_data_list;

   DESCRIPTION :  Copies the records in the list ``in_data_list`` to the
						list ``out_data_list``.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_data_count`` is the number of records in the
						source list ``in_data_list``.

						(.) ``in_data_list`` is the list of records to be copied.

						(.) ``data_length`` is the size of the elements of the
						two lists ``in_data_list`` and ``out_data_list``.

						(.) ``out_data_count`` points to an integer which will
						contain the number of records the destination list
						``out_data_list`` if this function is successful.

						(.) ``out_data_list`` points to the destination array
						to which records from ``in_data_list`` are to be copied.
						Memory will be allocated for this list by the function.

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_SUCCESS'' if no error occurred.

						(.) One of the non-zero STRFUNCS return codes if an error
						occurred.

   NOTES       :  

	CAVEATS     :

   SEE ALSO    :  meml_add
						meml_append
						meml_insert
						meml_remove
						mema_copy

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2018 Michael L. Brock

   OUTPUT INDEX:  meml_copy
						Memory List Functions:meml_copy
						STRFUNCS:Memory List Functions:meml_copy
						String Functions:See STRFUNCS

   PUBLISH XREF:  meml_copy

   PUBLISH NAME:	meml_copy

	ENTRY CLASS	:	Memory List Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int meml_copy(unsigned int in_data_count, void **in_data_list,
	size_t data_length, unsigned int *out_data_count, void ***out_data_list)
#else
int meml_copy(in_data_count, in_data_list, data_length, out_data_count,
	out_data_list)
unsigned int    in_data_count;
void          **in_data_list;
size_t          data_length;
unsigned int   *out_data_count;
void         ***out_data_list;
#endif /* #ifndef NARGS */
{
	int          return_code = STRFUNCS_SUCCESS;
	unsigned int count_1;

	*out_data_count = 0;
	*out_data_list  = NULL;

	for (count_1 = 0; count_1 < in_data_count; count_1++) {
		if ((return_code = memlapp(out_data_count, out_data_list,
			in_data_list[count_1], data_length)) != STRFUNCS_SUCCESS) {
			meml_remove_all(out_data_count, out_data_list);
			break;
		}
	}

	return(return_code);
}
/*	*********************************************************************** */

