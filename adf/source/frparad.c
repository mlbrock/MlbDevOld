/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Logic to support the freeing of 'ADF_PARA_DATA'
								structures.

	Revision History	:	1996-04-15 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <stdlib.h>

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_FREE_ParaDataList(unsigned int *para_count, ADF_PARA_DATA **para_list)
#else
void ADF_FREE_ParaDataList(para_count, para_list)
unsigned int   *para_count;
ADF_PARA_DATA **para_list;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;

	for (count_1 = 0; count_1 < *para_count; count_1++)
		ADF_FREE_ParaData(*para_list + count_1);

	if (*para_list != NULL)
		free(*para_list);

	*para_count = 0;
	*para_list  = NULL;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_FREE_ParaData(ADF_PARA_DATA *para_ptr)
#else
void ADF_FREE_ParaData(para_ptr)
ADF_PARA_DATA *para_ptr;
#endif /* #ifndef NARGS */
{
	if (para_ptr->text_ptr != NULL)
		free(para_ptr->text_ptr);

	ADF_INIT_ParaData(para_ptr);
}
/*	***********************************************************************	*/

