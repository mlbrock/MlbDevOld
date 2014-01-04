/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Removes ADF entries from a list of entries.

	Revision History	:	1996-01-10 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_RemoveExistingEntry(ADF_CONTROL *control_ptr, unsigned int entry_index)
#else
void ADF_RemoveExistingEntry(control_ptr, entry_index)
ADF_CONTROL  *control_ptr;
unsigned int  entry_index;
#endif /* #ifndef NARGS */
{
	ADF_RemoveHText(control_ptr->in_entry_list + entry_index,
		&control_ptr->in_htext_count, &control_ptr->in_htext_list);

	mema_remove(&control_ptr->in_entry_count,
		((void **) &control_ptr->in_entry_list), sizeof(ADF_ENTRY),
		entry_index, 1);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_RemoveHText(const ADF_ENTRY *entry_ptr, unsigned int *htext_count,
	ADF_HTEXT **htext_list)
#else
void ADF_RemoveHText(entry_ptr, htext_count, htext_list)
const ADF_ENTRY  *entry_ptr;
unsigned int     *htext_count;
ADF_HTEXT       **htext_list;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;

	for (count_1 = 0; count_1 < *htext_count; ) {
		if (((*htext_list)[count_1].file_index == entry_ptr->file_index) &&
			((*htext_list)[count_1].entry_index == entry_ptr->entry_index))
			mema_remove(htext_count, ((void **) htext_list),
				sizeof(**htext_list), count_1, 1);
		else
			count_1++;
	}
}
/*	***********************************************************************	*/

