/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Executable Source Module									*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Determines the statistics of canned Rendezvous data.

	Revision History	:	1996-01-12 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <limits.h>
#include <string.h>

#include <genfuncs.h>

#include "rvutilcd.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
COMPAT_FN_DECL(int main, (int argc, char **argv));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(void RVUTIL_CANSTAT_DoFills,
	(const time_t *start_time, const time_t *end_time, unsigned int granularity,
	int csv_flag));
COMPAT_FN_DECL_STATIC(void RVUTIL_CANSTAT_DoTotals,
	(unsigned int this_count, unsigned int this_size, unsigned int this_min,
	unsigned int this_max, unsigned int *total_count, unsigned int *total_size,
	unsigned int *total_min, unsigned int *total_max));
COMPAT_FN_DECL_STATIC(void RVUTIL_CANSTAT_EmitLine,
	(int csv_flag, const time_t *this_time, unsigned int this_count,
	unsigned int this_size, unsigned int this_min, unsigned int this_max));
COMPAT_FN_DECL_STATIC(void RVUTIL_CANSTAT_EmitHeader,
	(int csv_flag));
COMPAT_FN_DECL_STATIC(void RVUTIL_CANSTAT_EmitTrailer,
	(int csv_flag));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int main(int argc, char **argv)
{
	int            return_code    = RVUTIL_SUCCESS;
	unsigned int   granularity    = 1;
	int            fill_flag      = RVUTIL_FALSE;
	int            csv_flag       = RVUTIL_FALSE;
	unsigned int   file_count     = 0;
	char         **file_list      = NULL;
	unsigned int   tick_count     = 0;
	CAN_DATA      *tick_list      = NULL;
	unsigned int   old_tick_count = 0;
	MFILE         *mfile_ptr      = NULL;
	unsigned int   total_count    = 0;
	unsigned int   total_size     = 0;
	unsigned int   total_min      = UINT_MAX;
	unsigned int   total_max      = 0;
	CAN_DATA      *tick_ptr;
	time_t         fill_time;
	time_t         this_time;
	time_t         next_time;
	unsigned int   this_count;
	unsigned int   this_size;
	unsigned int   this_min;
	unsigned int   this_max;
	unsigned int   count_1;
	char           time_buffer[SDTIF_FMT_TIME_LEN_TIMEVAL + 1];
	char           error_text[RVUTIL_MAX_ERROR_TEXT];

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if ((!stricmp(argv[count_1], "-H")) ||
			(!stricmp(argv[count_1], "-HELP"))) {
			sprintf(error_text, "Help request with '%s' noted . . .",
				argv[count_1]);
			return_code = RVUTIL_BAD_ARGS_FAILURE;
			goto EXIT_FUNCTION;
		}
		else if (!stricmp(argv[count_1], "-GRANULARITY")) {
			if ((count_1 + 1) == ((unsigned int) argc)) {
				sprintf(error_text, "%s '%-.500s' parameter.",
					"Expected command-line qualifier to follow", argv[count_1]);
				return_code = RVUTIL_BAD_ARGS_FAILURE;
				goto EXIT_FUNCTION;
			}
			else if ((!argv[count_1 + 1][0]) ||
				(atof(argv[count_1 + 1]) < 1.0) ||
				(atof(argv[count_1 + 1]) > ((double) (60 * 60 * 24)))) {
				sprintf(error_text, "%s '%-.500s' %s %d, inclusive.",
					"Expected granularity in seconds to follow", argv[count_1],
					"parameter in the range of 1 to ", 60 * 60 * 24);
				return_code = RVUTIL_BAD_ARGS_FAILURE;
				goto EXIT_FUNCTION;
			}
			granularity  = ((unsigned int) atof(argv[++count_1]));
		}
		else if (!stricmp(argv[count_1], "-FILL"))
			fill_flag = RVUTIL_TRUE;
		else if (!stricmp(argv[count_1], "-CSV"))
			csv_flag = RVUTIL_TRUE;
		else if (strl_append(&file_count, &file_list, argv[count_1]) !=
			STRFUNCS_SUCCESS) {
			STR_AllocMsgItem(strlen(argv[count_1]), error_text,
				"Unable to add an canned data file name to the list");
			return_code = RVUTIL_MEMORY_FAILURE;
			goto EXIT_FUNCTION;
		}
	}

	if (!file_count) {
		strcpy(error_text, "No file name was specified on the command-line.");
		return_code = RVUTIL_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}

	for (count_1 = 0; count_1 < file_count; count_1++) {
		fprintf(stderr, "File: %s ", file_list[count_1]);
		if ((mfile_ptr = mopen(file_list[count_1], "rb")) == NULL) {
			strcat(nstrcat(strcpy(error_text, "Unable to open canned data file '"),
				file_list[count_1], 500), "' for reading: ");
			GEN_AppendLastErrorString(0, RVUTIL_MAX_ERROR_TEXT, error_text);
			return_code = RVUTIL_SYSTEM_FAILURE;
			goto EXIT_FUNCTION;
		}
		fprintf(stderr, "opened ");
		old_tick_count = tick_count;
		if ((return_code = RVUTIL_CAN_AppendListCAN_DATA(mfile_ptr, 0,
			&tick_count, &tick_list, error_text)) != RVUTIL_SUCCESS)
			goto EXIT_FUNCTION;
		fprintf(stderr, "read %u ticks", tick_count - old_tick_count);
		mclose(mfile_ptr);
		fprintf(stderr, "\n");
	}

	fprintf(stderr, "Total ticks read: %u\n", tick_count);

	if (tick_count) {
		fprintf(stderr, "Sorting %u ticks --- ", tick_count);
		RVUTIL_CAN_SortCAN_DATA(tick_count, tick_list);
		fprintf(stderr, "done\n\n");
		fprintf(stderr, "First Tick Time: %s\n",
			SDTIF_Format_timeval(&tick_list[0].tick_time, time_buffer));
		fprintf(stderr, "Last Tick Time : %s\n\n",
			SDTIF_Format_timeval(&tick_list[tick_count - 1].tick_time,
			time_buffer));
		this_time  = ((time_t) tick_list[0].tick_time.tv_sec);
		next_time  = this_time + ((time_t) granularity);
		this_count = 1;
		this_size  = ((unsigned int) tick_list[0].msg_size);
		this_min   = this_size;
		this_max   = this_size;
		RVUTIL_CANSTAT_EmitHeader(csv_flag);
		for (count_1 = 1, tick_ptr = (tick_list + 1); count_1 < tick_count;
			count_1++, tick_ptr++) {
			if (tick_ptr->tick_time.tv_sec < next_time) {
				this_count++;
				this_size  += ((unsigned int) tick_ptr->msg_size);
				this_min    = (this_min < ((unsigned int) tick_ptr->msg_size)) ?
					this_min : ((unsigned int) tick_ptr->msg_size);
				this_max    = (this_max > ((unsigned int) tick_ptr->msg_size)) ?
					this_max : ((unsigned int) tick_ptr->msg_size);
			}
			else {
				RVUTIL_CANSTAT_EmitLine(csv_flag, &this_time, this_count,
					this_size, this_min, this_max);
				RVUTIL_CANSTAT_DoTotals(this_count, this_size, this_min, this_max,
					&total_count, &total_size, &total_min, &total_max);
				fill_time  = next_time + ((time_t) granularity);
				this_time  = ((time_t) tick_ptr->tick_time.tv_sec);
				next_time  = this_time + ((time_t) granularity);
				this_count = 1;
				this_size  = ((unsigned int) tick_ptr->msg_size);
				this_min   = this_size;
				this_max   = this_size;
				if ((fill_flag) && (fill_time < next_time))
					RVUTIL_CANSTAT_DoFills(&fill_time, &this_time, granularity,
						csv_flag);
			}
		}
		RVUTIL_CANSTAT_EmitLine(csv_flag, &this_time, this_count, this_size,
			this_min, this_max);
		RVUTIL_CANSTAT_DoTotals(this_count, this_size, this_min, this_max,
			&total_count, &total_size, &total_min, &total_max);
		RVUTIL_CANSTAT_EmitTrailer(csv_flag);
		RVUTIL_CANSTAT_EmitLine(csv_flag, NULL, total_count, total_size,
			total_min, total_max);
		RVUTIL_CANSTAT_EmitTrailer(csv_flag);
	}

EXIT_FUNCTION:

	strl_remove_all(&file_count, &file_list);

	if (tick_list != NULL)
		free(tick_list);

	if (mfile_ptr != NULL)
		mclose(mfile_ptr);

	if (return_code == RVUTIL_BAD_ARGS_FAILURE)
		fprintf(stderr,
			"\n\n%s\n\nUSAGE: %s [ - h | -help ] %s %s %s %s %s\n\n",
			error_text,
			argv[0],
			"[ -granularity <statistic-granularity-in-seconds> ]",
			"[ -fill ]",
			"[ -csv ]",
			"<canned-data-file-name>",
			"[ <canned-data-file-name> . . . ]");
	else if (return_code != RVUTIL_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return((return_code == RVUTIL_SUCCESS) ? EXIT_SUCCESS : EXIT_FAILURE);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_CAN_GetListCAN_DATA(MFILE *mfile_ptr, unsigned int tick_granularity,
	unsigned int *tick_count, CAN_DATA **tick_list, char *error_text)
{
	*tick_count = 0;
	*tick_list  = NULL;

	return(RVUTIL_CAN_AppendListCAN_DATA(mfile_ptr, tick_granularity,
		tick_count, tick_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_CAN_AppendListCAN_DATA(MFILE *mfile_ptr,
	unsigned int tick_granularity,  unsigned int *tick_count,
	CAN_DATA **tick_list, char *error_text)
{
	int            return_code = RVUTIL_SUCCESS;
	unsigned int   new_count;
	unsigned long  offset;
	unsigned long  file_size;
	const char    *file_name;
	CAN_DATA       can_data;
	CAN_DATA      *tmp_list;
	char           mfile_error_text[MFILE_MAX_ERROR_TEXT];

	tick_granularity = (tick_granularity) ? tick_granularity : 10000;

	mseek(mfile_ptr, 0, SEEK_SET);

	if ((return_code = MFILE_Lock(mfile_ptr, mfile_error_text)) ==
		MFILE_SUCCESS) {
		file_size   = MFILE_GetFileSize(mfile_ptr);
		offset      = MFILE_GetOffset(mfile_ptr);
		file_name   = MFILE_GetFileName(mfile_ptr);
		if ((return_code = MFILE_Unlock(mfile_ptr, mfile_error_text)) !=
			MFILE_SUCCESS) {
			nstrcpy(error_text, mfile_error_text, RVUTIL_MAX_ERROR_TEXT - 1);
			return_code = RVUTIL_MAP_ERROR_MFILE(return_code);
			goto EXIT_FUNCTION;
		}
		return_code = RVUTIL_MAP_ERROR_MFILE(return_code);
	}
	else {
		nstrcpy(error_text, mfile_error_text, RVUTIL_MAX_ERROR_TEXT - 1);
		return_code = RVUTIL_MAP_ERROR_MFILE(return_code);
		goto EXIT_FUNCTION;
	}

	if (*tick_count && (*tick_count % tick_granularity)) {
		new_count = *tick_count +
			(tick_granularity - (*tick_count % tick_granularity));
		tmp_list  = ((CAN_DATA *) realloc(*tick_list,
			new_count * sizeof(CAN_DATA)));
		if (tmp_list == NULL) {
			STR_AllocMsgList(new_count, sizeof(CAN_DATA), error_text,
				"Unable to re-allocate the list of canned data entries");
			return_code = RVUTIL_MEMORY_FAILURE;
			goto EXIT_FUNCTION;
		}
		*tick_list = tmp_list;
	}

	while ((offset + sizeof(CAN_DATA)) < file_size) {
		if (mread(&can_data, sizeof(can_data), 1, mfile_ptr) != 1) {
			sprintf(error_text, "%s %u %s '%-.500s'.",
				"Error occurred on attempt to read", sizeof(can_data),
				"bytes from the canned data file", file_name);
			return_code = RVUTIL_SYSTEM_FAILURE;
			goto EXIT_FUNCTION;
		}
		if (can_data.total_length < sizeof(CAN_DATA))
			break;
		if (!(*tick_count % tick_granularity)) {
			tmp_list = (!(*tick_count)) ?
				((CAN_DATA *) calloc(tick_granularity, sizeof(CAN_DATA))) :
				((CAN_DATA *) realloc(*tick_list,
				(*tick_count + tick_granularity) * sizeof(CAN_DATA)));
			if (tmp_list == NULL) {
				STR_AllocMsgList(*tick_count + tick_granularity,
					sizeof(CAN_DATA), error_text,
					"Unable to %sallocate the list of canned data entries",
					(!(*tick_count)) ? "" : "re-");
				return_code = RVUTIL_MEMORY_FAILURE;
				goto EXIT_FUNCTION;
			}
			*tick_list = tmp_list;
		}
		(*tick_list)[(*tick_count)++] = can_data;
		offset += ((unsigned long) can_data.total_length);
		mseek(mfile_ptr, ((off_t) offset), SEEK_SET);
	}

	if (*tick_count) {
		if (*tick_count % tick_granularity)
			*tick_list = ((CAN_DATA *) realloc(*tick_list,
				*tick_count * sizeof(CAN_DATA)));
	}

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void RVUTIL_CAN_SortCAN_DATA(unsigned int tick_count, CAN_DATA *tick_list)
{
	STR_ARRAY_qsort(NULL, tick_count, tick_list, sizeof(*tick_list),
		STR_CMP_FUNC_CAST(RVUTIL_CAN_SCompareCAN_DATA));
}
/*	***********************************************************************	*/

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
int RVUTIL_CAN_SCompareCAN_DATA(void *control_ptr, const CAN_DATA *ptr_1,
	const CAN_DATA *ptr_2, size_t data_length)
{
	return(SDTIF_COMPARE_TIMEVAL(&ptr_1->tick_time, &ptr_2->tick_time));
}
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

/*	***********************************************************************	*/
int RVUTIL_CAN_CompareCAN_DATA(const CAN_DATA *ptr_1, const CAN_DATA *ptr_2)
{
	return(SDTIF_COMPARE_TIMEVAL(&ptr_1->tick_time, &ptr_2->tick_time));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static void RVUTIL_CANSTAT_DoFills(const time_t *start_time,
	const time_t *end_time, unsigned int granularity, int csv_flag)
{
	time_t next_time;

	next_time = *start_time;

	while (next_time < *end_time) {
		RVUTIL_CANSTAT_EmitLine(csv_flag, &next_time, 0, 0, 0, 0);
		next_time += ((time_t) granularity);
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static void RVUTIL_CANSTAT_DoTotals(unsigned int this_count,
	unsigned int this_size, unsigned int this_min, unsigned int this_max,
	unsigned int *total_count, unsigned int *total_size, unsigned int *total_min,
	unsigned int *total_max)
{
	*total_count += this_count;
	*total_size  += this_size;
	*total_min    = (*total_min < this_min) ? *total_min : this_min;
	*total_max    = (*total_max > this_max) ? *total_max : this_max;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static void RVUTIL_CANSTAT_EmitLine(int csv_flag, const time_t *this_time,
	unsigned int this_count, unsigned int this_size, unsigned int this_min,
	unsigned int this_max)
{
	char time_buffer[SDTIF_FMT_TIME_LEN_TIME_T + 1];

	if (this_time != NULL)
		SDTIF_Format_time_t(this_time, time_buffer);
	else
		strpadl(strcpy(time_buffer, ""), sizeof(time_buffer) - 1);

	printf("%-10.10s%s%-8.8s%s%10u%s%10u%s%10u%s%10u\n",
		time_buffer,      (csv_flag) ? "," : " ",
		time_buffer + 11,	(csv_flag) ? "," : " ",
		this_count,       (csv_flag) ? "," : " ",
		this_size,        (csv_flag) ? "," : " ",
		this_min,         (csv_flag) ? "," : " ",
		this_max);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static void RVUTIL_CANSTAT_EmitHeader(int csv_flag)
{
	printf("%-10.10s%s%-8.8s%s%-10.10s%s%-10.10s%s%-10.10s%s%-10.10s\n",
		"Date",    (csv_flag) ? "," : " ",
		"Time",	  (csv_flag) ? "," : " ",
		"Count",   (csv_flag) ? "," : " ",
		"Size",    (csv_flag) ? "," : " ",
		"Minimum", (csv_flag) ? "," : " ",
		"Maximum");
	RVUTIL_CANSTAT_EmitTrailer(csv_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static void RVUTIL_CANSTAT_EmitTrailer(int csv_flag)
{
	printf("%-10.10s%s%-8.8s%s%-10.10s%s%-10.10s%s%-10.10s%s%-10.10s\n",
		"----------", (csv_flag) ? "," : " ",
		"--------",	  (csv_flag) ? "," : " ",
		"----------", (csv_flag) ? "," : " ",
		"----------", (csv_flag) ? "," : " ",
		"----------", (csv_flag) ? "," : " ",
		"----------");
}
/*	***********************************************************************	*/


