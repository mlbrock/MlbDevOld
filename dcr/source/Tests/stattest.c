/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Test Module											*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	

	Revision History	:	1995-08-11 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#include <stdio.h>
#include <stdlib.h>

#include <genfuncs.h>

typedef struct {
	struct timeval last_start;
	struct timeval last_end;
	struct timeval last_interval;
	unsigned long  last_count;
	unsigned long  total_count;
	struct timeval total_interval;
} DCR_STAT;

#define DCR_STAT_COUNT	10

typedef struct {
	DCR_STAT stat_list[DCR_STAT_COUNT];
} DCR_HEADER;

typedef struct {
	DCR_HEADER *header_ptr;
} DCR_CACHE;

static DCR_HEADER HeaderData;

static DCR_CACHE        CacheData = { &HeaderData };

void DCR_StatStartTime(DCR_STAT *stat_ptr);
void DCR_StatEndTime(DCR_STAT *stat_ptr,
	unsigned long item_count);

void DCR_StatStartTime(stat_ptr)
DCR_STAT *stat_ptr;
{
	stat_ptr->last_count       = 0L;
	stat_ptr->last_end.tv_sec  = 0L;
	stat_ptr->last_end.tv_usec = 0L;
	SDTIF_GetTimeUSecs(&stat_ptr->last_start);
}

void DCR_StatEndTime(stat_ptr, item_count)
DCR_STAT *stat_ptr;
unsigned long   item_count;
{
	if (stat_ptr->last_start.tv_sec) {
		SDTIF_GetTimeUSecs(&stat_ptr->last_end);
		SDTIF_GetABSInterval_timeval(&stat_ptr->last_start, &stat_ptr->last_end,
			&stat_ptr->last_interval);
		stat_ptr->last_count   = item_count;
		stat_ptr->total_count += item_count;
		SDTIF_AddInterval_timeval(&stat_ptr->total_interval,
			&stat_ptr->last_interval, &stat_ptr->total_interval);
	}
}

#ifndef NARGS
int main(void);
#else
int main();
#endif /* #ifndef NARGS */

int main()
{
	unsigned int    count_1;
	unsigned int    count_2;
	unsigned int    this_count;
	DCR_CACHE      *cache_ptr;
	struct timeval  last_per_interval;
	struct timeval  total_per_interval;
	char            time_buffer_1[100];
	char            time_buffer_2[100];

	cache_ptr = &CacheData;

	for (count_1 = 0; count_1 < 10; count_1++) {
		DCR_StatStartTime(cache_ptr->header_ptr->stat_list);
		fprintf(stderr, "[%02u]:Sleeping for %u seconds", count_1,
			this_count = (rand() % 5) + 1);
		for (count_2 = 0; count_2 < this_count; count_2++) {
			sleep(1);
			fprintf(stderr, " .");
		}
		fprintf(stderr, "\n");
		DCR_StatEndTime(cache_ptr->header_ptr->stat_list,
			((unsigned long) this_count));
		SDTIF_GetPerInterval_timeval(&cache_ptr->header_ptr->stat_list[0].
			last_interval, cache_ptr->header_ptr->stat_list[0].last_count,
			&last_per_interval);
		SDTIF_GetPerInterval_timeval(&cache_ptr->header_ptr->stat_list[0].
			total_interval,
			cache_ptr->header_ptr->stat_list[0].total_count,
			&total_per_interval);
		printf("[Item %2u] Recap:[%s->%s]\n", count_1,
			SDTIF_Format_timeval(&cache_ptr->header_ptr->stat_list[0].last_start,
			time_buffer_1),
			SDTIF_Format_timeval(&cache_ptr->header_ptr->stat_list[0].last_end,
			time_buffer_2));
		printf("                [%s]\n",
			SDTIF_FormatInterval_timeval(
			&cache_ptr->header_ptr->stat_list[0].last_interval, time_buffer_1));
		printf("          Last :[%s / %2lu = %s]\n",
			SDTIF_FormatInterval_timeval(
			&cache_ptr->header_ptr->stat_list[0].last_interval, time_buffer_1),
			cache_ptr->header_ptr->stat_list[0].last_count,
			SDTIF_FormatInterval_timeval(&last_per_interval, time_buffer_2));
		printf("          Total:[%s / %2lu = %s]\n",
			SDTIF_FormatInterval_timeval(
			&cache_ptr->header_ptr->stat_list[0].total_interval,time_buffer_1),
			cache_ptr->header_ptr->stat_list[0].total_count,
			SDTIF_FormatInterval_timeval(&total_per_interval, time_buffer_2));
	}

	return(0);
}

