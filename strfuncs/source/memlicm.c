/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Case-insensitive comparison of memory.

	Revision History	:	1991-10-02 --- Creation
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

#include "strfunci.h"

/* *********************************************************************** */

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  MEM_memicmp

   SYNOPSIS    :  return_code = MEM_memicmp(control_ptr, data_ptr_1,
							data_ptr_2, data_length);

						int         return_code;

						void       *control_ptr;

						const void *data_ptr_1;

						const void *data_ptr_2;

						size_t      data_length;

   DESCRIPTION :  Compares the two areas of memory (to which the parameters
						``data_ptr_1`` and ``data_ptr_2`` point) for equality.

						The memory areas are compared character-by-character until
						``data_length`` characters have been compared.

						The comparison is performed in a case-insensitive
						manner.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``control_ptr`` points to a arbitrary user-defined
						structure which may be used to modify the comparison
						If unnecessary, it may be a NULL pointer.

						(.) ``data_ptr_1`` points to the first of the memory areas
						to be compared.

						(.) ``data_ptr_2`` points to the second of the memory areas
						to be compared.

						(.) ``data_length`` is the size the memory areas which are
						to be compared.

   RETURNS     :  Returns from this function are as follow:

						(.) negative if the first memory area compares less than
						the second memory area.

						(.) positive if the first string compares greater than
						the second memory area.

						(.) zero if the two memory areas are equal.

   NOTES       :  The ``control_ptr`` and ``data_length`` parameters are
						present only because this function is used internally
						by other STRFUNCS list functions. They provide
						function-call compatibility with other, more generic,
						comparison functions.

   CAVEATS     :  

   SEE ALSO    :  STR_LIST_bsearch
						STR_LIST_qsort

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2016 Michael L. Brock

   OUTPUT INDEX:  MEM_memicmp
						Memory List Functions:MEM_memicmp
						STRFUNCS:Memory List Functions:MEM_memicmp
						String Functions:See STRFUNCS

   PUBLISH XREF:  MEM_memicmp

   PUBLISH NAME:	MEM_memicmp

	ENTRY CLASS	:	Memory List Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int MEM_memicmp(void *control_ptr, const void *data_ptr_1,
	const void *data_ptr_2, size_t data_length)
#else
int MEM_memicmp(control_ptr, data_ptr_1, data_ptr_2, data_length)
void       *control_ptr;
const void *data_ptr_1;
const void *data_ptr_2;
size_t      data_length;
#endif /* #ifndef NARGS */
{
#ifdef __GNUC__
	((void)(control_ptr));
#endif /* #ifdef __GNUC__ */

	return(STRFUNCS_memicmp(data_ptr_1, data_ptr_2, data_length));
}
/* *********************************************************************** */
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

