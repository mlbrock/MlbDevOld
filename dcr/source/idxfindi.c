/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Finds the first or last cache record equal to the
								specified key using an indirect index.

	Revision History	:	1994-05-07 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include "dcr.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#ifndef NARGS
static int DCR_BSearchIndirect(DCR_CACHE *cache_ptr,
	unsigned int index_method, const void *record_ptr,
	unsigned int entry_count, const unsigned long *entry_list,
	unsigned int *found_index, int direction_flag);
#else
static int DCR_BSearchIndirect();
#endif /* #ifndef NARGS */

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	DCR_FindIndirect

	SYNOPSIS		:	found_flag = DCR_FindIndirect(cache_ptr, index_method,
							record_align_cmp_ptr, index_align_cmp_ptr, in_record_ptr,
							entry_count, entry_list, find_anchor, out_index_element,
							out_index_offset, out_record_element, out_record_offset);

						int            found_flag;

						DCR_CACHE     *cache_ptr;

						unsigned int   index_method;

						GEN_ALIGN_CMP *record_align_cmp_ptr;

						GEN_ALIGN_CMP *index_align_cmp_ptr;

						const void    *in_record_ptr;

						unsigned int   entry_count;

						const void    *entry_list;

						int            find_anchor;

						unsigned int  *out_index_element;

						unsigned long *out_index_offset;

						unsigned int  *out_record_element;

						unsigned long *out_record_offset;

	DESCRIPTION	:	Finds the first or last cache record equal to the
						specified key using an indirect index.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``cache_ptr`` is a pointer to the structure of type
						''DCR_CACHE'' in which are the records to be searched.

						(.) ``index_method`` is the index access path to be used
						to perform the search.

						(-) Note that unlike the high-level cache ``get`` functions,
						this function does not check the validity of the
						``index_method`` parameter. Passing an invalid
						``index_method`` to this function can therefore result in
						Unix segmentation faults (or equivalents for your
						operating system).

						(.) ``record_align_cmp_ptr`` is a pointer to a structure of
						type ''GEN_ALIGN_CMP'' to be used to manage the comparison
						of record entries. It is of particular use in performing
						partial-key searches.

						(-) If you do not intend to perform a partial-key search,
						this parameter may be passed as ''NULL'', in which case
						the record alignment comparison data built-in to the cache
						for the index ``index_method`` will be used.

						(.) ``index_align_cmp_ptr`` is a pointer to a structure of
						type ''GEN_ALIGN_CMP'' to be used to manage the comparison
						of index entries. It is of particular use in performing
						partial-key searches.

						(-) If you do not intend to perform a partial-key search,
						this parameter may be passed as ''NULL'', in which case
						the index alignment comparison data built-in to the cache
						for the index ``index_method`` will be used.

						(.) ``in_record_ptr`` points to the record containing the
						key for which the search is to be performed.

						(.) ``entry_count`` is the number of index entries in the
						index area to which the ``entry_list`` parameter points.

						(.) ``entry_list`` is the list of index entries in which
						the search is to be performed.

						(.) ``find_anchor`` specifies the anchor point for the
						search. This determines whether the unsigned integer to
						which the ``out_index_element`` parameter points will be
						set to the first element meeting the relational criterion
						or the last element meeting the relational criterion.

						(-) The following cache anchor flags should be used:

						(.) ''DCR_FIND_TOP'' to anchor the returned element
						at the top of the records meeting the relational criterion.

						(.) ''DCR_FIND_BOTTOM'' to anchor the returned element
						at the bottom of the records meeting the relational
						criterion.

						(.) ``out_index_element`` points to an unsigned integer
						into which will be placed the number of the first (or last)
						index element meeting the specified criteria.

						(-) ``out_index_element`` may be ''NULL'', in which case
						no action is taken.

						(.) ``out_index_offest`` points to an unsigned long
						into which will be placed the offset of the first (or last)
						index element meeting the specified criteria.

						(-) ``out_index_offset`` may be ''NULL'', in which case
						no action is taken.

						(.) ``out_record_element`` points to an unsigned integer
						into which will be placed the number of the first (or last)
						record element meeting the specified criteria.

						(-) ``out_record_element`` may be ''NULL'', in which case
						no action is taken.

						(.) ``out_record_offset`` points to an unsigned long
						into which will be placed the number of the first (or last)
						record offset meeting the specified criteria.

						(-) ``out_record_offset`` may be ''NULL'', in which case
						no action is taken.

	RETURNS		:	One of the following manifest constants:

						(.) ''DCR_RECORD_NOT_FOUND'' if no matching record
						is found.

						(.) ''DCR_RECORD_FOUND'' if a matching record is
						found.

	NOTES			:	

	CAVEATS		:	This function is part of the cache library low-level
						implementation and therefore makes a set of assumptions
						about the environment in which it is invoked.

						It's probably safer for application programmers to call
						the higher-level functional equivalent of this function:
						``DCR_GetEQ``.

	SEE ALSO		:	DCR_Find
						DCR_FindEmbedded

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	DCR_FindIndirect
						DCR Cache Find Functions:DCR_FindIndirect
						DCR Cache Functions:DCR_FindIndirect

	PUBLISH XREF:	DCR_FindIndirect

	PUBLISH NAME:	DCR_FindIndirect

EOH */
/* *********************************************************************** */
int DCR_FindIndirect(cache_ptr, index_method, record_align_cmp_ptr,
	index_align_cmp_ptr, in_record_ptr, entry_count, entry_list, find_anchor,
	out_index_element, out_index_offset, out_record_element, out_record_offset)
DCR_CACHE     *cache_ptr;
unsigned int   index_method;
GEN_ALIGN_CMP *record_align_cmp_ptr;
GEN_ALIGN_CMP *index_align_cmp_ptr;
const void    *in_record_ptr;
unsigned int   entry_count;
const void    *entry_list;
int            find_anchor;
unsigned int  *out_index_element;
unsigned long *out_index_offset;
unsigned int  *out_record_element;
unsigned long *out_record_offset;
{
   int          return_code;
	unsigned int found_index;

	cache_ptr->current_index_method                               =
		index_method;
	cache_ptr->index_data_list[index_method].record_align_cmp_ptr =
		(record_align_cmp_ptr != NULL) ? record_align_cmp_ptr :
		&cache_ptr->index_data_list[index_method].record_align_cmp_data;
	cache_ptr->index_data_list[index_method].index_align_cmp_ptr  =
		(index_align_cmp_ptr != NULL) ? index_align_cmp_ptr :
		&cache_ptr->index_data_list[index_method].index_align_cmp_data;

	return_code = DCR_BSearchIndirect(cache_ptr, index_method,
		in_record_ptr, entry_count, ((const unsigned long *) entry_list),
		&found_index, find_anchor);

	cache_ptr->index_data_list[index_method].record_align_cmp_ptr =
		&cache_ptr->index_data_list[index_method].record_align_cmp_data;
	cache_ptr->index_data_list[index_method].index_align_cmp_ptr  =
		&cache_ptr->index_data_list[index_method].index_align_cmp_data;

	if (out_index_element != NULL)
		*out_index_element = found_index;

	if (out_index_offset != NULL)
		*out_index_offset = found_index * sizeof(unsigned long);

	if (out_record_element != NULL)
		*out_record_element = DCR_IELE_TO_RELE_P(cache_ptr, index_method,
			entry_count, entry_list, found_index);

	if (out_record_offset != NULL)
		*out_record_offset = DCR_IELE_TO_ROFF_P(cache_ptr, index_method,
			entry_count, entry_list, found_index);

	return(return_code);
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  DCR_BSearchIndirect

   SYNOPSIS    :  return_code = DCR_BSearchIndirect(cache_ptr,
							index_method, record_ptr, entry_count, entry_list,
							found_index, direction_flag);

						int           return_code;

						void         *control_ptr;

						unsigned int  data_count;

						void         *data_list;

						const void   *key_data;

						size_t        data_length;

						unsigned int *found_index;

						int           direction_flag;

						int          (*compare_function)(void *, const void *,
							const void *, size_t);

   DESCRIPTION :  This function is a binary search routine generalized from
						Knuth (6.2.1) Algorithm B for use with arrays. The algorithm
						assumes that the array has been previously sorted in
						ascending order according to the provided comparison
						function ``compare_function``.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``control_ptr`` points to a arbitrary user-defined
						structure which may be used to modify the comparisons
						used to determine the relative equality of ``key_data``
						``vis-a-vis`` the elements in the array ``data_list``. It
						is passed unexamined to the comparison function
						``compare_function``. If unnecessary, it may be a NULL
						pointer.

						(.) ``data_count`` is the number of elements in the array
						``data_list``.

						(.) ``data_list`` is the array of pointers in which the
						search for ``key_data`` will be performed.

						(.) ``key_data`` points to the data for which the search
						is to occur.

						(.) ``data_length`` is the size each element of the array
						``data_list``. It is passed unexamined to the comparison
						function ``compare_function``. If unnecessary, it may be
						zero (0).

						(.) ``found_index`` points to an unsigned integer into
						which the index of ``key_data`` in ``data_list`` will be
						placed, if found.

						(.) ``compare_function`` is a pointer to the function
						which will determine equivalence of ``key_data``
						``vis-a-vis`` the elements in ``data_list``. The function
						to which ``compare_function`` points should accept the
						arguments indicated in the SYNOPSIS and return an integral
						result as follows:

						(.) negative if the first element is less than second.

						(.) positive if the first element is greater than second.

						(.) zero if the elements are equal.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DCR_RECORD_FOUND'' if ``record_ptr`` is found in
						the array ``entry_list``. In this case, the unsigned int to
						which the ``found_index`` parameter points will be set to
						the index of that element in the array.

						(.) ''DCR_RECORD_NOT_FOUND'' if ``record_ptr`` is not
						found in the array ``entry_list``. In this case, the
						unsigned int to which the ``found_index`` parameter points
						will be set to the index of the array into which
						``record_ptr`` should be inserted.

   NOTES       :  

   CAVEATS     :  The results of invoking this function with a ``entry_list``
						not in sorted order are undefined.

						If there are multiple elements in ``entry_list`` which
						compare equal, it is impossible to determine which of
						them will be returned by this function.

   SEE ALSO    :  

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2018 Michael L. Brock

   OUTPUT INDEX:  DCR_BSearchIndirect
						DCR Cache Functions:DCR_BSearchIndirect

   PUBLISH XREF:  DCR_BSearchIndirect

   PUBLISH NAME:	DCR_BSearchIndirect

EOH */
/* *********************************************************************** */
static int DCR_BSearchIndirect(cache_ptr, index_method, record_ptr,
	entry_count, entry_list, found_index, direction_flag)
DCR_CACHE           *cache_ptr;
unsigned int         index_method;
const void          *record_ptr;
unsigned int         entry_count;
const unsigned long *entry_list;
unsigned int        *found_index;
int                  direction_flag;
{
	int    return_code = DCR_RECORD_NOT_FOUND;
	int    compare_value;
	size_t start_index;
	size_t current_index;
	size_t end_index;

	if (!entry_count)
		*found_index = 0;
	else {
		start_index = 0;
		end_index   = entry_count - 1;
		while ((current_index =
			(start_index + end_index) / 2) != end_index) {
			compare_value = GEN_ALIGN_CompareList(cache_ptr->
			index_data_list[index_method].record_align_cmp_ptr,
			record_ptr, ((char *) cache_ptr->record_mmap_ptr) +
			((unsigned int) entry_list[current_index]),
			cache_ptr->header_ptr->data_record_size);
			if (!compare_value) {
				*found_index = current_index;
				return_code  = DCR_RECORD_FOUND;
				break;
			}
			else if (compare_value > 0)
				start_index = (start_index == current_index) ?
					(current_index + 1) : current_index;
			else
				end_index = current_index;
		}
		if (return_code == DCR_RECORD_FOUND) {
			if (direction_flag > 0) {
				while ((*found_index > 0) &&
					(!GEN_ALIGN_CompareList(cache_ptr->
					index_data_list[index_method].record_align_cmp_ptr,
					record_ptr, ((char *) cache_ptr->record_mmap_ptr) +
					((unsigned int) entry_list[*found_index - 1]),
					cache_ptr->header_ptr->data_record_size)))
					(*found_index)--;
			}
			else if (direction_flag < 0) {
				while ((*found_index < (entry_count - 1)) &&
					(!GEN_ALIGN_CompareList(cache_ptr->
					index_data_list[index_method].record_align_cmp_ptr,
					record_ptr, ((char *) cache_ptr->record_mmap_ptr) +
					((unsigned int) entry_list[*found_index + 1]),
					cache_ptr->header_ptr->data_record_size)))
					(*found_index)++;
			}
		}
		else {									/* Item not found							*/
			if (!(compare_value = GEN_ALIGN_CompareList(cache_ptr->
				index_data_list[index_method].record_align_cmp_ptr,
				record_ptr, ((char *) cache_ptr->record_mmap_ptr) +
				((unsigned int) entry_list[current_index]),
				cache_ptr->header_ptr->data_record_size)))
				return_code = DCR_RECORD_FOUND;
			else if (compare_value > 0)
				current_index = entry_count;
			*found_index = current_index;
		}
	}

	return(return_code);
}
/* *********************************************************************** */

