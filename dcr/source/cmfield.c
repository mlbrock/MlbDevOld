/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	

	Revision History	:	1994-03-14 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2014.
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

int DCR_CMP_FIELD_ByOrder(control_ptr, ptr_1, ptr_2, data_length)
void            *control_ptr;
const DCR_FIELD *ptr_1;
const DCR_FIELD *ptr_2;
size_t           data_length;
{
	return((ptr_1->db_table_order > ptr_2->db_table_order) ? 1 :
		(ptr_1->db_table_order < ptr_2->db_table_order) ? -1 : 0);
}
/*	***********************************************************************	*/

