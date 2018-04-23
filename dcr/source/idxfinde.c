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
								specified key using an embedded index.

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

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	DCR_FindEmbedded

	SYNOPSIS		:	found_flag = DCR_FindEmbedded(cache_ptr, index_method,
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
						specified key using an embedded index.

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
						DCR_FindIndirect

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	DCR_FindEmbedded
						DCR Cache Find Functions:DCR_FindEmbedded
						DCR Cache Functions:DCR_FindEmbedded

	PUBLISH XREF:	DCR_FindEmbedded

	PUBLISH NAME:	DCR_FindEmbedded

EOH */
/* *********************************************************************** */
int DCR_FindEmbedded(cache_ptr, index_method, record_align_cmp_ptr,
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
   int          strfuncs_code;
	unsigned int found_index;

	DCR_CopyEmbedded(cache_ptr, index_method, 0L, in_record_ptr,
		cache_ptr->embedded_index_buffer);

	cache_ptr->current_index_method                               =
		index_method;
	cache_ptr->index_data_list[index_method].record_align_cmp_ptr =
		(record_align_cmp_ptr != NULL) ? record_align_cmp_ptr :
		&cache_ptr->index_data_list[index_method].record_align_cmp_data;
	cache_ptr->index_data_list[index_method].index_align_cmp_ptr  =
		(index_align_cmp_ptr != NULL) ? index_align_cmp_ptr :
		&cache_ptr->index_data_list[index_method].index_align_cmp_data;

#ifndef NARGS
	strfuncs_code = STR_ARRAY_bsearch(cache_ptr, entry_count, entry_list,
		cache_ptr->embedded_index_buffer,
		cache_ptr->index_list[index_method].index_entry_size, &found_index,
		find_anchor, ((int (*)(void *, const void *, const void *, size_t))
		DCR_CompareEmbedded));
#else
	strfuncs_code = STR_ARRAY_bsearch(cache_ptr, entry_count, entry_list,
		cache_ptr->embedded_index_buffer,
		cache_ptr->index_list[index_method].index_entry_size, &found_index,
		find_anchor, DCR_CompareEmbedded);
#endif /* #ifndef NARGS */

	cache_ptr->index_data_list[index_method].record_align_cmp_ptr =
		&cache_ptr->index_data_list[index_method].record_align_cmp_data;
	cache_ptr->index_data_list[index_method].index_align_cmp_ptr  =
		&cache_ptr->index_data_list[index_method].index_align_cmp_data;

	if (out_index_element != NULL)
		*out_index_element = found_index;

	if (out_index_offset != NULL)
		*out_index_offset =
			found_index * cache_ptr->index_list[index_method].index_entry_size;

	if (out_record_element != NULL)
		*out_record_element = DCR_IELE_TO_RELE_P(cache_ptr, index_method,
			entry_count, entry_list, found_index);

	if (out_record_offset != NULL)
		*out_record_offset = DCR_IELE_TO_ROFF_P(cache_ptr, index_method,
			entry_count, entry_list, found_index);

	return((strfuncs_code == STRFUNCS_ITEM_FOUND) ? DCR_RECORD_FOUND :
		DCR_RECORD_NOT_FOUND);
}
/*	***********************************************************************	*/

