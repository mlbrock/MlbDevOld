/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Logic to support the initialization of 'ADF_PARA_DATA'
								structures.

	Revision History	:	1996-04-15 --- Creation.
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

#include <memory.h>

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_INIT_ParaDataList(unsigned int para_count, ADF_PARA_DATA *para_list)
#else
void ADF_INIT_ParaDataList(para_count, para_list)
unsigned int   para_count;
ADF_PARA_DATA *para_list;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;

	memset(para_list, '\0', para_count * sizeof(*para_list));

	for (count_1 = 0; count_1 < para_count; count_1++)
		ADF_INIT_ParaData(para_list + count_1);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_INIT_ParaData(ADF_PARA_DATA *para_ptr)
#else
void ADF_INIT_ParaData(para_ptr)
ADF_PARA_DATA *para_ptr;
#endif /* #ifndef NARGS */
{
	para_ptr->para_format.pformat_flag    = ADF_FALSE;
	para_ptr->para_format.format_type     = 0;
	para_ptr->para_format.indent_level    = 0;
	para_ptr->para_format.numeric_value   = 0;
	para_ptr->para_format.small_font_flag = ADF_FALSE;
	para_ptr->para_format.first_count     = 0;
	para_ptr->para_format.last_count      = 0;
	para_ptr->text_ptr                    = NULL;
}
/*	***********************************************************************	*/

