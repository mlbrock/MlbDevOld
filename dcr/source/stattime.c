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

	Revision History	:	1994-05-21 --- Creation.
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

void DCR_StatStartTime(stat_ptr)
volatile DCR_STAT *stat_ptr;
{
	stat_ptr->last_count       = 0L;
	stat_ptr->last_end.tv_sec  = 0L;
	stat_ptr->last_end.tv_usec = 0L;
	SDTIF_GetTimeUSecs(&((DCR_STAT *) stat_ptr)->last_start);
}
/* *********************************************************************** */

void DCR_StatEndTime(stat_ptr, item_count)
volatile DCR_STAT *stat_ptr;
unsigned long            item_count;
{
	DCR_STAT tmp_stat;

	if (stat_ptr->last_start.tv_sec) {
		tmp_stat = *((DCR_STAT *) stat_ptr);
		SDTIF_GetTimeUSecs(&tmp_stat.last_end);
		SDTIF_GetABSInterval_timeval(&tmp_stat.last_start, &tmp_stat.last_end,
			&tmp_stat.last_interval);
		tmp_stat.last_count   = item_count;
		tmp_stat.total_count += item_count;
		SDTIF_AddInterval_timeval(&tmp_stat.total_interval,
			&tmp_stat.last_interval, &tmp_stat.total_interval);
		*stat_ptr = *((volatile DCR_STAT *) &tmp_stat);
	}
}
/* *********************************************************************** */

