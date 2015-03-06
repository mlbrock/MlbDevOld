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

	Revision History	:	1994-05-25 --- Creation.
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

#include <string.h>

#include "dcr.h"

/*	***********************************************************************	*/

void DCR_EmitStats(cache_ptr, cache_header_ptr, output_function,
	output_control)
DCR_CACHE         *cache_ptr;
DCR_HEADER  *cache_header_ptr;
#ifndef NARGS
void             (*output_function)(void *, char *, ...);
#else
void             (*output_function)();
#endif /* #ifndef NARGS */
void             *output_control;
{
	unsigned int      count_1;
	unsigned int      count_2;
	DCR_HEADER *tmp_header;
	char              tmp_buffer[256];
	char              tmp_stat_name[DCR_MAX_STAT_NAME + 1];

	tmp_header = (cache_header_ptr != NULL) ? cache_header_ptr :
		cache_ptr->saved_header_ptr;

	STR_EMIT_CharLine('=', 78, output_function, output_control);
	for (count_1 = 0; count_1 < DCR_STAT_COUNT; count_1++) {
		(*output_function)(output_control, "Cache %s Statistics\n",
			strcpy(tmp_buffer, initcaps(DCR_GetStatName(((int) count_1),
			tmp_stat_name))));
		STR_EMIT_CharLine('-', 78, output_function, output_control);
		DCR_EmitOneStat(tmp_header->stat_list + count_1, output_function,
			output_control);
		if (count_1 < (DCR_STAT_COUNT - 1))
			STR_EMIT_CharLine('-', 78, output_function, output_control);
	}
	STR_EMIT_CharLine('=', 78, output_function, output_control);

	for (count_1 = 0; count_1 < 2; count_1++) {
		STR_EMIT_CharLine('=', 78, output_function, output_control);
		for (count_2 = 0; count_2 < cache_ptr->index_count; count_2++) {
			(*output_function)(output_control,
				"Cache %s Statistics For Index Number %u\n",
				(!count_1) ? "Index" : "Sort", count_2);
			STR_EMIT_CharLine('-', 78, output_function, output_control);
			DCR_EmitOneStat((!count_1) ?
				&cache_ptr->index_list[count_2].index_stat :
				&cache_ptr->index_list[count_2].sort_stat, output_function,
				output_control);
			if (count_2 < (cache_ptr->index_count - 1))
				STR_EMIT_CharLine('-', 78, output_function, output_control);
		}
		STR_EMIT_CharLine('=', 78, output_function, output_control);
	}
}
/*	***********************************************************************	*/

void DCR_EmitOneStat(stat_ptr, output_function, output_control)
DCR_STAT  *stat_ptr;
#ifndef NARGS
void           (*output_function)(void *, char *, ...);
#else
void           (*output_function)();
#endif /* #ifndef NARGS */
void            *output_control;
{
	struct timeval tmp_timeval;
	char           tmp_buffer[256];

	(*output_function)(output_control, "Last Start Time : %s\n",
		SDTIF_Format_timeval(&stat_ptr->last_start, tmp_buffer));
	(*output_function)(output_control, "Last End Time   : %s\n",
		SDTIF_Format_timeval(&stat_ptr->last_end, tmp_buffer));
	(*output_function)(output_control, "Last Interval   : %s\n",
		SDTIF_FormatInterval_timeval(&stat_ptr->last_interval, tmp_buffer));
	(*output_function)(output_control, "Last Item Count : %10lu\n",
		stat_ptr->last_count);
	(*output_function)(output_control, "Last Mean Time  : %s\n",
		SDTIF_FormatInterval_timeval(SDTIF_GetPerInterval_timeval(
		&stat_ptr->last_interval, stat_ptr->last_count, &tmp_timeval),
		tmp_buffer));
	(*output_function)(output_control, "Total Interval  : %s\n",
		SDTIF_FormatInterval_timeval(&stat_ptr->total_interval, tmp_buffer));
	(*output_function)(output_control, "Total Item Count: %10lu\n",
		stat_ptr->total_count);
	(*output_function)(output_control, "Total Mean Time : %s\n",
		SDTIF_FormatInterval_timeval(SDTIF_GetPerInterval_timeval(
		&stat_ptr->total_interval, stat_ptr->total_count, &tmp_timeval),
		tmp_buffer));
}
/*	***********************************************************************	*/

