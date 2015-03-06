/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Single Index Internal Data Repository Library Source Module					*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Internal supporting logic for the match functions.

	Revision History	:	1996-04-12 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Include necessary header files . . .												*/
/*	***********************************************************************	*/

#include "siidri.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Function prototypes for functions private to this module . . .				*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(int SIIDR_SetMatchBlockPtrRaw, (SIIDR *siidr_ptr,
	const void *in_record_ptr, SIIDR_REL_OP rel_op,
	SIIDR_MATCH_BLOCK *block_ptr));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_TestMatchRaw(SIIDR *siidr_ptr, const void *in_record_ptr_1,
	const void *in_record_ptr_2, SIIDR_REL_OP rel_op,
	SIIDR_CompareFunc compare_func, void *user_data_ptr,
	SIIDR_GetSpecFunc get_spec_func)
{
	int cmp;

	cmp = ((((cmp = (*compare_func)(siidr_ptr, in_record_ptr_1, in_record_ptr_2,
		siidr_ptr->record_size)) == 0) && (rel_op & SIIDR_REL_OP_EQ)) ||
		((cmp < 0) && (rel_op & SIIDR_REL_OP_LT)) ||
		((cmp > 0) && (rel_op & SIIDR_REL_OP_GT))) ? SIIDR_TRUE : SIIDR_FALSE;

	return(((cmp == SIIDR_TRUE) && (get_spec_func != NULL)) ?
		(*get_spec_func)(siidr_ptr, user_data_ptr, in_record_ptr_2) : cmp);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
unsigned int SIIDR_SetMatchBlockListRaw(SIIDR *siidr_ptr,
	const void *in_record_ptr, SIIDR_REL_OP rel_op,
	SIIDR_MATCH_BLOCK *block_list)
{
	unsigned int out_count;

	if (!siidr_ptr->record_count)
		out_count = 0;
	else {
		if (rel_op == SIIDR_REL_OP_NE) {
			if (SIIDR_SetMatchBlockPtrRaw(siidr_ptr, in_record_ptr,
				SIIDR_REL_OP_LT, block_list) == SIIDR_FALSE) {
				block_list[0].count = siidr_ptr->record_count;
				block_list[0].first = 0;
				out_count           = 1;
			}
			else {
				SIIDR_SetMatchBlockPtrRaw(siidr_ptr, in_record_ptr,
					SIIDR_REL_OP_GT, block_list + 1);
				out_count = 2;
			}
		}
		else {
			SIIDR_SetMatchBlockPtrRaw(siidr_ptr, in_record_ptr, rel_op,
				block_list);
			out_count = 1;
		}
	}

	return(out_count);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static int SIIDR_SetMatchBlockPtrRaw(SIIDR *siidr_ptr,
	const void *in_record_ptr, SIIDR_REL_OP rel_op,
	SIIDR_MATCH_BLOCK *block_ptr)
{
	int          found_flag;
	unsigned int found_index;

	if (SIIDR_FindRecordRaw(siidr_ptr, in_record_ptr, &found_index) == NULL) {
		if (rel_op & SIIDR_REL_OP_LT) {
			block_ptr->count = found_index;
			block_ptr->first = 0;
		}
		else if (rel_op & SIIDR_REL_OP_GT) {
			block_ptr->count = siidr_ptr->record_count - found_index;
			block_ptr->first = (block_ptr->count) ? found_index : 0;
		}
		else {
			block_ptr->count = 0;
			block_ptr->first = 0;
		}
		found_flag = SIIDR_FALSE;
	}
	else {
		if (rel_op == SIIDR_REL_OP_EQ) {
			block_ptr->count = 1;
			block_ptr->first = found_index;
		}
		else if (rel_op & SIIDR_REL_OP_LT) {
			block_ptr->count = found_index + ((rel_op & SIIDR_REL_OP_EQ) ? 1 : 0);
			block_ptr->first = 0;
		}
		else if (rel_op & SIIDR_REL_OP_GT) {
			block_ptr->count = ((siidr_ptr->record_count - found_index) - 1) +
				((rel_op & SIIDR_REL_OP_EQ) ? 1 : 0);
			block_ptr->first = (!block_ptr->count) ? 0 :
				((rel_op & SIIDR_REL_OP_EQ) ? found_index : (found_index + 1));
		}
		found_flag = SIIDR_TRUE;
	}

	return(found_flag);
}
/*	***********************************************************************	*/

