/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Test Include File									*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file used to support testing of the DCR
								memory-mapped cache library.

	Revision History	:	1995-08-11 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#include <dbcsyb.h>

#include <limits.h>
#include <math.h>
#include <string.h>

#include <dbcsyb.h>

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	The data defined in this file is used for testing the basic DCR		*/
/*	cache functionality. It should not be included in the production			*/
/*	distribution.																				*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		The structure of the test data and the data population . . .			*/
/*	***********************************************************************	*/

typedef struct {
	DBDATETIME insertdate;
	DBDATETIME updatedate;
	long       issue_key;
	char       issue_id_value[60 + 1];
	long       issue_id_type;
	long       issue_id_exchange;
} ISSUE_ID;

ISSUE_ID DataList[] = {
	{ { 0L, 0L }, { 0L, 0L }, 20, "ABCDE", 		1,		0	},
	{ { 0L, 0L }, { 0L, 0L }, 20, "ABCDE", 		2,		0	},
	{ { 0L, 0L }, { 0L, 0L }, 21, "ABCDE", 		3,		0	},
	{ { 0L, 0L }, { 0L, 0L }, 12, "ABCDE001",		4,		1	},
	{ { 0L, 0L }, { 0L, 0L }, 12, "ABCDE002",		4,		2	},
	{ { 0L, 0L }, { 0L, 0L }, 13, "ABCDE00A2",	9,		0	},
	{ { 0L, 0L }, { 0L, 0L }, 13, "ABCDE00A3",	7,		0	},
	{ { 0L, 0L }, { 0L, 0L }, 13, "ABCDE00A1",	5,		0	},
	{ { 0L, 0L }, { 0L, 0L }, 13, "ABCDE00A4",	6,		0	}
};

unsigned int DataCount = sizeof(DataList) / sizeof(DataList[0]);

static const GEN_MEMBER   MemberList[] = {
	{
		"insertdate",
		STR_sizeof(ISSUE_ID, insertdate),
		STR_sizeof(ISSUE_ID, insertdate),
		offsetof(ISSUE_ID, insertdate),
		1,
		"l,L",
		0,
		GEN_MEMBER_ALIGN_EMPTY_LIST,
		0,
		NULL,
		SYBDATETIME,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
	{
		"updatedate",
		STR_sizeof(ISSUE_ID, updatedate),
		STR_sizeof(ISSUE_ID, updatedate),
		offsetof(ISSUE_ID, updatedate),
		1,
		"l,L",
		0,
		GEN_MEMBER_ALIGN_EMPTY_LIST,
		0,
		NULL,
		SYBDATETIME,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
	{
		"issue_key",
		STR_sizeof(ISSUE_ID, issue_key),
		STR_sizeof(ISSUE_ID, issue_key),
		offsetof(ISSUE_ID, issue_key),
		1,
		"l",
		0,
		GEN_MEMBER_ALIGN_EMPTY_LIST,
		0,
		NULL,
		SYBINT4,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
	{
		"issue_id_value",
		STR_sizeof(ISSUE_ID, issue_id_value) - 1,
		STR_sizeof(ISSUE_ID, issue_id_value),
		offsetof(ISSUE_ID, issue_id_value),
		STR_sizeof(ISSUE_ID, issue_id_value) - 1,
		"c",
		0,
		GEN_MEMBER_ALIGN_EMPTY_LIST,
		0,
		NULL,
		SYBCHAR,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
	{
		"issue_id_type",
		STR_sizeof(ISSUE_ID, issue_id_type),
		STR_sizeof(ISSUE_ID, issue_id_type),
		offsetof(ISSUE_ID, issue_id_type),
		1,
		"l",
		0,
		GEN_MEMBER_ALIGN_EMPTY_LIST,
		0,
		NULL,
		SYBINT4,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
	{
		"issue_id_exchange",
		STR_sizeof(ISSUE_ID, issue_id_exchange),
		STR_sizeof(ISSUE_ID, issue_id_exchange),
		offsetof(ISSUE_ID, issue_id_exchange),
		1,
		"l",
		0,
		GEN_MEMBER_ALIGN_EMPTY_LIST,
		0,
		NULL,
		SYBINT4,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	}
};

static const unsigned int MemberCount  =
	sizeof(MemberList) / sizeof(MemberList[0]);

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Specification of the test data indices . . .									*/
/*	***********************************************************************	*/

char *IndexSpecList[] = {
	"FirstIndex=issue_id_value,issue_id_type,issue_id_exchange",
	"SecondIndex=issue_key",
	"ThirdIndex=issue_key,issue_id_type"
};

unsigned int IndexSpecCount =
	sizeof(IndexSpecList) / sizeof(IndexSpecList[0]);

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#include <datfuncs.h>

#ifndef NARGS
void PrintTestDataHeader(void);
void PrintTestDataLines(void);
void PrintTestDataList(unsigned int issue_id_count, ISSUE_ID *issue_id_list);
void PrintTestDataRow(ISSUE_ID *issue_id_ptr);
#else
void PrintTestDataHeader();
void PrintTestDataLines();
void PrintTestDataList();
void PrintTestDataRow();
#endif /* #ifndef NARGS */

/*	***********************************************************************	*/

/*	***********************************************************************	*/
void PrintTestDataHeader()
{
	printf("%-23.23s %-23.23s %-11.11s %-60.60s %-13.13s %-17.17s\n",
		"insertdate", "updatedate", "issue_key", "issue_id_value",
		"issue_id_type", "issue_id_exchange");

	PrintTestDataLines();
}

void PrintTestDataLines()
{
	printf("%-23.23s %-23.23s %-11.11s %-60.60s %-13.13s %-17.17s\n",
		"-----------------------", "-----------------------", "-----------",
		"------------------------------------------------------------",
		"-------------", "-----------------");
}

void PrintTestDataList(issue_id_count, issue_id_list)
unsigned int  issue_id_count;
ISSUE_ID     *issue_id_list;
{
	unsigned int count_1;

	PrintTestDataHeader();

	for (count_1 = 0; count_1 < issue_id_count; count_1++)
		PrintTestDataRow(issue_id_list + count_1);

	PrintTestDataLines();
}

void PrintTestDataRow(issue_id_ptr)
ISSUE_ID *issue_id_ptr;
{
	DTIME tmp_dtime;
	char  date_buffer[100];

	printf("%s ",
		DTIME_FormatDate(DBC_SYB_Sybase8ToDTIME(&issue_id_ptr->insertdate,
		&tmp_dtime), DATFUNCS_DEFAULT_DTIME_FORMAT, date_buffer));
	printf("%s ",
		DTIME_FormatDate(DBC_SYB_Sybase8ToDTIME(&issue_id_ptr->updatedate,
		&tmp_dtime), DATFUNCS_DEFAULT_DTIME_FORMAT, date_buffer));
	printf("%11ld ", issue_id_ptr->issue_key);
	printf("%-60.60s ", issue_id_ptr->issue_id_value);
	printf("%-13ld ", issue_id_ptr->issue_id_type);
	printf("%-17ld\n", issue_id_ptr->issue_id_exchange);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int DCR_MapData(cache_ptr, record_count, record_list, error_text)
DCR_CACHE     *cache_ptr;
unsigned int  *record_count;
void         **record_list;
char          *error_text;
{
	int return_code = DCR_FAILURE;

	if ((record_count == NULL) && (record_list != NULL)) {
		strcat(strcat(strcpy(error_text, "Bad cache refresh parameters: "),
			"the data area size pointer is 'NULL', "),
			"but the data area pointer is not 'NULL'.");
		return_code = DCR_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if ((record_count != NULL) && (record_list == NULL)) {
		strcat(strcat(strcpy(error_text, "Bad cache refresh parameters: "),
			"the data area size pointer is not 'NULL', "),
			"but the data area pointer is 'NULL'.");
		return_code = DCR_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}
	else
		return_code = DCR_SUCCESS;

	cache_ptr->record_mmap_size = ((unsigned int)
		(cache_ptr->header_area_size + cache_ptr->data_area_size));
	cache_ptr->record_mmap_ptr  = ((void *) cache_ptr->mmap_ptr);

	if (record_count != NULL)
		*record_count = cache_ptr->record_mmap_size;
	if (record_list != NULL)
		*record_list  = cache_ptr->record_mmap_ptr;

EXIT_FUNCTION:

	if (return_code != DCR_SUCCESS) {
		if (record_count != NULL)
			*record_count = 0;
		if (record_list != NULL)
			*record_list = NULL;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void DCR_UnMapData(cache_ptr)
DCR_CACHE *cache_ptr;
{
	cache_ptr->record_mmap_size = 0;
	cache_ptr->record_mmap_ptr  = NULL;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int DCR_MapAllIndices(cache_ptr, error_text)
DCR_CACHE *cache_ptr;
char      *error_text;
{
	int          return_code = DCR_SUCCESS;
	unsigned int count_1;

	for (count_1 = 0; count_1 < cache_ptr->index_count; count_1++) {
		if ((return_code = DCR_MapIndex(cache_ptr, count_1, NULL, NULL,
			error_text)) != DCR_SUCCESS)
			break;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int DCR_MapIndex(cache_ptr, index_method, entry_count, entry_list,
	error_text)
DCR_CACHE     *cache_ptr;
unsigned int   index_method;
unsigned int  *entry_count;
void         **entry_list;
char          *error_text;
{
	int return_code;

	if ((return_code = DCR_ValidateIndexMethod(cache_ptr, index_method,
		error_text)) == DCR_SUCCESS) {
		cache_ptr->index_data_list[index_method].mmap_size =
			((unsigned int) cache_ptr->index_list[index_method].index_area_size);
		cache_ptr->index_data_list[index_method].mmap_ptr  =
			cache_ptr->index_data_list[index_method].index_entry_list;
		if (entry_count != NULL)
			*entry_count = cache_ptr->record_count;
		if (entry_list != NULL)
			*entry_list  = cache_ptr->index_data_list[index_method].mmap_ptr;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void DCR_UnMapAllIndices(cache_ptr)
DCR_CACHE *cache_ptr;
{
	unsigned int count_1;
	char         tmp_error_text[DCR_MAX_ERROR_TEXT];

	for (count_1 = 0; count_1 < cache_ptr->index_count; count_1++)
		DCR_UnMapIndex(cache_ptr, count_1, tmp_error_text);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int DCR_UnMapIndex(cache_ptr, index_method, error_text)
DCR_CACHE    *cache_ptr;
unsigned int  index_method;
char         *error_text;
{
	int return_code;

	if ((return_code = DCR_ValidateIndexMethod(cache_ptr, index_method,
		error_text)) == DCR_SUCCESS) {
		cache_ptr->index_data_list[index_method].mmap_size = 0;
		cache_ptr->index_data_list[index_method].mmap_ptr  = NULL;
	}

	return(return_code);
}
/*	***********************************************************************	*/

int DCR_MapDataAndIndex(cache_ptr, record_count, record_list,
	index_method, entry_count, entry_list, error_text)
DCR_CACHE     *cache_ptr;
unsigned int  *record_count;
void         **record_list;
unsigned int   index_method;
unsigned int  *entry_count;
void         **entry_list;
char          *error_text;
{
	int return_code;

	if ((return_code = DCR_MapData(cache_ptr, record_count, record_list,
		error_text)) == DCR_SUCCESS)
		return_code = DCR_MapIndex(cache_ptr, index_method, entry_count,
			entry_list, error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int DCR_MapDataAndIndices(cache_ptr, error_text)
DCR_CACHE *cache_ptr;
char      *error_text;
{
	int          return_code;
	unsigned int count_1;

	if ((return_code = DCR_MapData(cache_ptr, NULL, NULL,
		error_text)) == DCR_SUCCESS) {
		for (count_1 = 0; count_1 < cache_ptr->index_count; count_1++) {
			if ((return_code = DCR_MapIndex(cache_ptr, count_1, NULL,
				NULL, error_text)) != DCR_SUCCESS)
				break;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef __MSDOS__
/*	***********************************************************************	*/
int msync(addr, len, flags)
char *addr;
int   len;
int   flags;
{
	flags = ((int) addr) + len;
	len   = ((int) addr) + flags;

	return(0);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void usleep(micro_seconds)
unsigned int micro_seconds;
{
	micro_seconds = micro_seconds;
}
/*	***********************************************************************	*/
#endif /* #ifdef __MSDOS__ */

