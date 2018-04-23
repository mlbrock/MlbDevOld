/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Sorts 'PCFF_PARAM' structures.

	Revision History	:	2001-05-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2001 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Required include files . . .														*/
/*	***********************************************************************	*/

#include "pcffi.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
void PCFF_SortParamList(unsigned int param_count, PCFF_PARAM *param_list)
{
	unsigned int count_1;
	unsigned int count_2;

	for (count_1 = 0; count_1 < param_count; count_1++)
		param_list[count_1].tmp_original_index = count_1;

	STR_ARRAY_qsort(NULL, param_count, param_list, sizeof(*param_list),
		STR_CMP_FUNC_CAST(PCFF_ParamCompare));

	for (count_1 = 0; count_1 < param_count; count_1++) {
		for (count_2 = 0; count_2 < param_count; count_2++) {
			if (param_list[count_1].ref_index ==
				param_list[count_2].tmp_original_index) {
				param_list[count_1].ref_index = count_2;
				break;
			}
		}
	}
}
/* *********************************************************************** */


