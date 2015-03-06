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
								specified key.

	Revision History	:	1994-05-07 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2015.
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

	NAME			:	DCR_Find

	SYNOPSIS		:	found_flag = DCR_Find(cache_ptr, index_method,
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
						specified key.

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

	SEE ALSO		:	DCR_FindEmbedded
						DCR_FindIndirect

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2015 Michael L. Brock

	OUTPUT INDEX:	DCR_Find
						DCR Cache Find Functions:DCR_Find
						DCR Cache Functions:DCR_Find

	PUBLISH XREF:	DCR_Find

	PUBLISH NAME:	DCR_Find

EOH */
/* *********************************************************************** */
int DCR_Find(cache_ptr, index_method, record_align_cmp_ptr,
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
	return((DCR_INDEX_IS_INDIRECT(cache_ptr) == DCR_TRUE) ?
		DCR_FindIndirect(cache_ptr, index_method, record_align_cmp_ptr,
		index_align_cmp_ptr, in_record_ptr, entry_count, entry_list,
		find_anchor, out_index_element, out_index_offset, out_record_element,
		out_record_offset) :
		DCR_FindEmbedded(cache_ptr, index_method, record_align_cmp_ptr,
		index_align_cmp_ptr, in_record_ptr, entry_count, entry_list,
		find_anchor, out_index_element, out_index_offset, out_record_element,
		out_record_offset));
}
/*	***********************************************************************	*/

