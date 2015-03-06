/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Removes elements from an array.

	Revision History	:	1991-08-22 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1991 - 2015.
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
#include <stdio.h>
#include <stdlib.h>

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  mema_remove

   SYNOPSIS    :  return_code = mema_remove(data_count, data_list,
							data_length, first_element, element_count);

						int            return_code;

						unsigned int  *data_count;

						void         **data_list;

						size_t         data_length;

						unsigned int   first_element;

						unsigned int   element_count;

   DESCRIPTION :  Deletes an array element from an array.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``data_count`` points to integer which contains the
						number of elements in the array to which ``data_list``
						points.

						(-) If the function succeeds in deleting the specified
						elements then that integer will have subtracted from it
						the number of elements deleted.

						(.) ``data_list`` points to a pointer to ``void`` which
						contains the array. If the function succeeds in deleting
						elements then the memory pointed to by ``data_list`` will
						be re-allocated to hold the new size of the array.

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

   SEE ALSO    :  mema_add
						mema_append
						mema_copy
						mema_insert
						mema_remove_all
						meml_remove

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2015 Michael L. Brock

   OUTPUT INDEX:  mema_remove
						Memory Array Functions:mema_remove
						STRFUNCS:Memory Array Functions:mema_remove
						String Functions:See STRFUNCS

   PUBLISH XREF:  mema_remove

   PUBLISH NAME:	mema_remove

	ENTRY CLASS	:	Memory Array Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int mema_remove(unsigned int *data_count, void **data_list,
	size_t data_length, unsigned int first_element, unsigned int element_count)
#else
int mema_remove(data_count, data_list, data_length, first_element,
	element_count)
unsigned int  *data_count;
void         **data_list;
size_t         data_length;
unsigned int   first_element;
unsigned int   element_count;
#endif /* #ifndef NARGS */
{
	int            return_code = -1;
	unsigned int   count_1;

	if ((data_length > 0) && (((!(*data_count)) && (!(*data_list))) ||
		 ((*data_count > 0)    && *data_list))) {
		if ((!(*data_count)) || (!element_count) ||
			(first_element >= *data_count))
			return_code = 0;
		else {
			if ((first_element + element_count) > *data_count)
				element_count = *data_count - first_element;
			if (!(*data_count - element_count)) {
				free(*data_list);
				*data_list = NULL;
			}
			else {
				for (count_1 = (first_element + element_count);
					count_1 < *data_count; count_1++)
					memcpy(((char *) *data_list) + ((count_1 - element_count) *
						data_length), ((char*) *data_list) +
						(count_1 * data_length), data_length);
				*data_list = realloc(*data_list, (*data_count - element_count) *
					data_length);
			}
			*data_count = *data_count - element_count;
			return_code = 0;
		}
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  mema_remove_all

   SYNOPSIS    :  return_code = mema_remove_all(data_count, data_list)

						int            return_code;

						unsigned int  *data_count;

						void         **data_list;

   DESCRIPTION :  Deletes all elements from an array.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``data_count`` points to integer which contains the
						number of elements in the array to which ``data_list``
						points.

						(.) ``data_list`` points to a pointer to ``void`` which
						contains the array to be deleted.

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_SUCCESS'' if no error occurred.

						(.) One of the non-zero STRFUNCS return codes if an error
						occurred.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  mema_add
						mema_append
						mema_copy
						mema_insert
						mema_remove
						meml_remove_all

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2015 Michael L. Brock

   OUTPUT INDEX:  mema_remove_all
						Memory Array Functions:mema_remove_all
						STRFUNCS:Memory Array Functions:mema_remove_all
						String Functions:See STRFUNCS

   PUBLISH XREF:  mema_remove_all

   PUBLISH NAME:	mema_remove_all

	ENTRY CLASS	:	Memory Array Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int mema_remove_all(unsigned int *data_count, void **data_list)
#else
int mema_remove_all(data_count, data_list)
unsigned int  *data_count;
void         **data_list;
#endif /* #ifndef NARGS */
{
	int return_code = STRFUNCS_SUCCESS;

	if ((*data_count && (!(*data_list))) || ((!(*data_count)) && *data_list))
		return_code = STRFUNCS_FAILURE;
	else {
		if (*data_count)
			free(*data_list);
		*data_count = 0;
		*data_list  = NULL;
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  memadel

   SYNOPSIS    :  return_code = memadel(data_count, data_list,
							data_length, first_element, element_count);

						int            return_code;

						unsigned int  *data_count;

						void         **data_list;

						size_t         data_length;

						unsigned int   first_element;

						unsigned int   element_count;

   DESCRIPTION :  Deletes an array element from an array.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``data_count`` points to integer which contains the
						number of elements in the array to which ``data_list``
						points.

						(-) If the function succeeds in deleting the specified
						elements then that integer will have subtracted from it
						the number of elements deleted.

						(.) ``data_list`` points to a pointer to ``void`` which
						contains the array. If the function succeeds in deleting
						elements then the memory pointed to by ``data_list`` will
						be re-allocated to hold the new size of the array.

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
						``mema_remove``. It is retained for purposes of
						compatibility with legacy code.

   CAVEATS     :  

   SEE ALSO    :  mema_remove

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2015 Michael L. Brock

   OUTPUT INDEX:  memadel
						Memory Array Functions:memadel
						STRFUNCS:Memory Array Functions:memadel
						String Functions:See STRFUNCS

   PUBLISH XREF:  memadel

   PUBLISH NAME:	memadel

	ENTRY CLASS	:	Memory Array Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int memadel(unsigned int *data_count, void **data_list,
	size_t data_length, unsigned int first_element, unsigned int element_count)
#else
int memadel(data_count, data_list, data_length, first_element, element_count)
unsigned int  *data_count;
void         **data_list;
size_t         data_length;
unsigned int   first_element;
unsigned int   element_count;
#endif /* #ifndef NARGS */
{
	return(mema_remove(data_count, data_list, data_length, first_element,
		element_count));
}
/* *********************************************************************** */

