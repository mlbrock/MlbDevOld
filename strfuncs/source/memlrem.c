/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Removes elements from an array of pointers.

	Revision History	:	1991-10-02 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1991 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Include necessary header files . . .											*/
/* *********************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  meml_remove

   SYNOPSIS    :  return_code = meml_remove(data_count, data_list,
							first_element, element_count);

						int             return_code;

						unsigned int   *data_count;

						void         ***data_list;

						unsigned int    first_element;

						unsigned int    element_count;

   DESCRIPTION :  Deletes an array element from an array of pointers.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``data_count`` points to integer which contains the
						number of elements in the array to which ``data_list``
						points.

						(-) If the function succeeds in deleting the specified
						elements then that integer will have subtracted from it
						the number of elements deleted.

						(.) ``data_list`` is a triply-indirect pointer to ``void``
						(``void ***``) which contains the array. If the function
						succeeds in deleting elements then the memory pointed to
						by ``data_list`` will be re-allocated to hold the new size
						of the array.

						(.) ``data_length`` is the length of the array elements.

						(.) ``first_element`` is the array index of the first
						element to be deleted.

						(-) If ``first_element`` exceeds the array index of the
						last array element (that is, if ``first_element`` is
						greater that or equal to ``*data_count``) no work will
						be performed by this function.

						(.) ``element_count`` is the number of elements to be
						deleted.

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_SUCCESS'' if no error occurred.

						(.) One of the non-zero STRFUNCS return codes if an error
						occurred.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  meml_add
						meml_append
						meml_copy
						meml_insert
						meml_remove_all
						mema_remove

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2014 Michael L. Brock

   OUTPUT INDEX:  meml_remove
						Memory List Functions:meml_remove
						STRFUNCS:Memory List Functions:meml_remove
						String Functions:See STRFUNCS

   PUBLISH XREF:  meml_remove

   PUBLISH NAME:	meml_remove

	ENTRY CLASS	:	Memory List Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int meml_remove(unsigned int *data_count, void ***data_list,
	unsigned int first_element, unsigned int element_count)
#else
int meml_remove(data_count, data_list, first_element, element_count)
unsigned int   *data_count;
void         ***data_list;
unsigned int    first_element;
unsigned int    element_count;
#endif /* #ifndef NARGS */
{
	int            return_code = STRFUNCS_FAILURE;
	unsigned int   count_1;
	unsigned int   data_index  = 0;
	void         **tmp_list    = NULL;

	if (((!(*data_count)) && (*data_list == NULL)) ||
		(*data_count && (*data_list != NULL))) {
		if ((!(*data_count)) || (!element_count) ||
			(first_element >= *data_count))
			return_code = STRFUNCS_SUCCESS;
		else {
			if ((first_element + element_count) > *data_count)
				element_count = *data_count - first_element;
			if (element_count < *data_count) {
				if ((tmp_list = ((void **)
					calloc(*data_count - element_count, sizeof(void *)))) == NULL)
					goto EXIT_FUNCTION;
				for (count_1 = 0; count_1 < *data_count; count_1++) {
					if ((count_1 < first_element) ||
						(count_1 >= (first_element + element_count)))
						tmp_list[data_index++] = (*data_list)[count_1];
				}
			}
			for (count_1 = 0; count_1 < element_count; count_1++) {
				if ((*data_list)[first_element + count_1])
					free((*data_list)[first_element + count_1]);
			}
			free(*data_list);
			*data_list  = tmp_list;
			*data_count = *data_count - element_count;
			return_code = STRFUNCS_SUCCESS;
		}
	}

EXIT_FUNCTION:

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  meml_remove_all

   SYNOPSIS    :  return_code = meml_remove_all(data_count, data_list);

						int             return_code;

						unsigned int   *data_count;

						void         ***data_list;

   DESCRIPTION :  Deletes all elements from an array of pointers.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``data_count`` points to integer which contains the
						number of elements in the array to which ``data_list``
						points.

						(.) ``data_list`` is a triply-indirect pointer to ``void``
						(``void ***``) which contains the array to be deleted.

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_SUCCESS'' if no error occurred.

						(.) One of the non-zero STRFUNCS return codes if an error
						occurred.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  meml_add
						meml_append
						meml_copy
						meml_insert
						meml_remove
						mema_remove_all

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2014 Michael L. Brock

   OUTPUT INDEX:  meml_remove_all
						Memory List Functions:meml_remove_all
						STRFUNCS:Memory List Functions:meml_remove_all
						String Functions:See STRFUNCS

   PUBLISH XREF:  meml_remove_all

   PUBLISH NAME:	meml_remove_all

	ENTRY CLASS	:	Memory List Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int meml_remove_all(unsigned int *data_count, void ***data_list)
#else
int meml_remove_all(data_count, data_list)
unsigned int   *data_count;
void         ***data_list;
#endif /* #ifndef NARGS */
{
	return(meml_remove(data_count, data_list, 0, *data_count));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  memldel

   SYNOPSIS    :  return_code = memldel(data_count, data_list, first_element,
							element_count);

						int             return_code;

						unsigned int   *data_count;

						void         ***data_list;

						unsigned int    first_element;

						unsigned int    element_count;

   DESCRIPTION :  Deletes an array element from an array of pointers.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``data_count`` points to integer which contains the
						number of elements in the array to which ``data_list``
						points.

						(-) If the function succeeds in deleting the specified
						elements then that integer will have subtracted from it
						the number of elements deleted.

						(.) ``data_list`` is a triply-indirect pointer to ``void``
						(``void ***``) which contains the array. If the function
						succeeds in deleting elements then the memory pointed to
						by ``data_list`` will be re-allocated to hold the new size
						of the array.

						(.) ``data_length`` is the length of the array elements.

						(.) ``first_element`` is the array index of the first
						element to be deleted.

						(-) If ``first_element`` exceeds the array index of the
						last array element (that is, if ``first_element`` is
						greater that or equal to ``*data_count``) no work will
						be performed by this function.

						(.) ``element_count`` is the number of elements to be
						deleted.

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_SUCCESS'' if no error occurred.

						(.) One of the non-zero STRFUNCS return codes if an error
						occurred.

   NOTES       :  This function does no more than call the function
						``meml_remove``. It is retained for purposes of
						compatibility with legacy code.

   CAVEATS     :  

   SEE ALSO    :  meml_remove

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2014 Michael L. Brock

   OUTPUT INDEX:  memldel
						Memory List Functions:memldel
						STRFUNCS:Memory List Functions:memldel
						String Functions:See STRFUNCS

   PUBLISH XREF:  memldel

   PUBLISH NAME:	memldel

	ENTRY CLASS	:	Memory List Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int memldel(unsigned int *data_count, void ***data_list,
	unsigned int first_element, unsigned int element_count)
#else
int memldel(data_count, data_list, first_element, element_count)
unsigned int   *data_count;
void         ***data_list;
unsigned int    first_element;
unsigned int    element_count;
#endif /* #ifndef NARGS */
{
	return(meml_remove(data_count, data_list, first_element, element_count));
}
/* *********************************************************************** */

