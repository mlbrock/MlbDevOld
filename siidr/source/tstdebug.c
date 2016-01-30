/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Single Index Internal Data Repository Library Source Module					*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Contains support functions for SIIDR testing.

	Revision History	:	1996-04-11 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <strfuncs.h>

#include "siidri.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_TEST_FastInsertIdList(SIIDR *siidr_ptr, unsigned int start_id,
	unsigned int id_count, unsigned int id_increment, int random_flag,
	char *error_text)
{
	int             return_code = SIIDR_SUCCESS;
	unsigned int    count_1;
	SIIDR_TEST_DATA test_record;

	if (id_count) {
		if (siidr_ptr->record_count || random_flag)
			return_code = SIIDR_TEST_InsertIdList(siidr_ptr, start_id, id_count,
				id_increment, random_flag, error_text);
		else if ((return_code = SIIDR_AllocateIDRRaw(siidr_ptr, id_count,
			error_text)) == SIIDR_SUCCESS) {
			memset(&test_record, '\0', sizeof(test_record));
			for (count_1 = 0; count_1 < id_count;
				count_1++, start_id += id_increment) {
				SIIDR_TEST_SetRecord(start_id, &test_record);
				if ((siidr_ptr->record_list[count_1] =
					memdup(&test_record, siidr_ptr->record_size)) == NULL) {
					STR_AllocMsgItem(siidr_ptr->record_size, error_text,
						"%s %-.500s data record in the internal data repository",
						"Unable to allocate memory for a copied",
						siidr_ptr->idr_name);
					return_code = SIIDR_MEMORY_FAILURE;
					break;
				}
				siidr_ptr->record_count++;
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void SIIDR_TEST_GetIdList(unsigned int start_id, unsigned int id_count,
	unsigned int id_increment, unsigned int *id_list, int random_flag)
{
	unsigned int count_1;
	unsigned int tmp_index;
	unsigned int tmp_id;

	for (count_1 = 0; count_1 < id_count; count_1++, start_id += id_increment)
		id_list[count_1] = start_id;

	if (random_flag) {
		for (count_1 = 0; count_1 < id_count; count_1++) {
			while ((tmp_index = (rand() % id_count)) == count_1)
				;
			tmp_id             = id_list[count_1];
			id_list[count_1]   = id_list[tmp_index];
			id_list[tmp_index] = tmp_id;
		}
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_TEST_CreateIdList(unsigned int start_id, unsigned int id_count,
	unsigned int id_increment, int random_flag, unsigned int **id_list,
	char *error_text)
{
	int return_code = SIIDR_SUCCESS;

	*id_list = NULL;

	if (id_count) {
		if ((*id_list = ((unsigned int *) calloc(id_count,
			sizeof(unsigned int)))) == NULL) {
			STR_AllocMsgList(id_count, sizeof(unsigned int), error_text,
				"Unable to allocate IDR test identifier list");
			return_code = SIIDR_MEMORY_FAILURE;
		}
		else
			SIIDR_TEST_GetIdList(start_id, id_count, id_increment, *id_list,
				random_flag);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_TEST_InsertIdList(SIIDR *siidr_ptr, unsigned int start_id,
	unsigned int id_count, unsigned int id_increment, int random_flag,
	char *error_text)
{
	int              return_code = SIIDR_SUCCESS;
	unsigned int    *id_list;
	unsigned int     count_1;
	SIIDR_TEST_DATA  test_record;

	if (id_count && ((return_code = SIIDR_TEST_CreateIdList(start_id,
		id_count, id_increment, random_flag, &id_list, error_text)) ==
		SIIDR_SUCCESS)) {
		memset(&test_record, '\0', sizeof(test_record));
		for (count_1 = 0; count_1 < id_count; count_1++) {
			if ((return_code = SIIDR_Insert(siidr_ptr,
				SIIDR_TEST_SetRecord(id_list[count_1], &test_record),
				error_text)) != SIIDR_SUCCESS)
				break;
		}
		free(id_list);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_TEST_DeleteIdList(SIIDR *siidr_ptr, unsigned int start_id,
	unsigned int id_count, unsigned int id_increment, int random_flag,
	char *error_text)
{
	int              return_code = SIIDR_SUCCESS;
	unsigned int    *id_list;
	unsigned int     count_1;
	SIIDR_TEST_DATA  test_record;

	if ((id_count) && ((return_code = SIIDR_TEST_InsertIdList(siidr_ptr,
		start_id, id_count, id_increment, SIIDR_FALSE, error_text)) ==
		SIIDR_SUCCESS)) {
		if ((return_code = SIIDR_TEST_CreateIdList(start_id, id_count,
			id_increment, random_flag, &id_list, error_text)) ==
			SIIDR_SUCCESS) {
			memset(&test_record, '\0', sizeof(test_record));
			if (!random_flag)
				STR_ARRAY_reverse(id_count, id_list, sizeof(*id_list));
			for (count_1 = 0; count_1 < id_count; count_1++) {
				if ((return_code = SIIDR_Delete(siidr_ptr,
					SIIDR_TEST_SetRecord(id_list[count_1], &test_record),
					error_text)) != SIIDR_SUCCESS)
					break;
			}
			free(id_list);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_TEST_UpdateIdList(SIIDR *siidr_ptr, unsigned int start_id,
	unsigned int id_count, unsigned int id_increment, int random_flag,
	char *error_text)
{
	int              return_code = SIIDR_SUCCESS;
	unsigned int    *id_list;
	unsigned int     count_1;
	SIIDR_TEST_DATA  test_record;

	if ((id_count) && ((return_code = SIIDR_TEST_InsertIdList(siidr_ptr,
		start_id, id_count, id_increment, SIIDR_FALSE, error_text)) ==
		SIIDR_SUCCESS)) {
		if ((return_code = SIIDR_TEST_CreateIdList(start_id, id_count,
			id_increment, random_flag, &id_list, error_text)) ==
			SIIDR_SUCCESS) {
			memset(&test_record, '\0', sizeof(test_record));
			if (!random_flag)
				STR_ARRAY_reverse(id_count, id_list, sizeof(*id_list));
			for (count_1 = 0; count_1 < id_count; count_1++) {
				if ((return_code = SIIDR_Update(siidr_ptr,
					SIIDR_TEST_SetRecord(id_list[count_1], &test_record),
					error_text)) != SIIDR_SUCCESS)
					break;
			}
			free(id_list);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void SIIDR_TEST_EmitRecordList(const SIIDR *siidr_ptr)
{
	unsigned int count_1;

	for (count_1 = 0; count_1 < siidr_ptr->record_count; count_1++) {
		SIIDR_TEST_EmitRecord(count_1, ((SIIDR_TEST_DATA *)
			siidr_ptr->record_list[count_1]));
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void SIIDR_TEST_EmitRecord(unsigned int record_index,
	const SIIDR_TEST_DATA *record_ptr)
{
	printf("%8u: %-*.*s %8u %8u %17.6f\n", record_index,
		((int) (STR_sizeof(SIIDR_TEST_DATA, order_id) - 1)),
		((int) (STR_sizeof(SIIDR_TEST_DATA, order_id) - 1)),
		record_ptr->order_id,
		record_ptr->record_id,
		record_ptr->quantity,
		record_ptr->price);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void *SIIDR_TEST_SetRecord(unsigned int record_id,
	SIIDR_TEST_DATA *record_ptr)
{
	memset(record_ptr, '\0', sizeof(*record_ptr));

	SIIDR_TEST_SetRecordId(record_id, record_ptr);

	record_ptr->record_id = record_id;
	record_ptr->quantity  = record_id;
	record_ptr->price     = ((double) record_id);

	return(record_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
char *SIIDR_TEST_SetRecordId(unsigned int record_id,
	SIIDR_TEST_DATA *record_ptr)
{
	return(val2str_uint(record_id, 10, "0", record_ptr->order_id));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_TEST_CompareIDR(const SIIDR *siidr_ptr_1, const SIIDR *siidr_ptr_2,
	char *error_text)
{
	int          return_code = SIIDR_SUCCESS;
	unsigned int count_1;

	if (siidr_ptr_1->record_count != siidr_ptr_2->record_count) {
		if (error_text != NULL)
			sprintf(error_text, "Record counts differ (%u versus %u).",
				siidr_ptr_1->record_count, siidr_ptr_2->record_count);
		return_code = SIIDR_FAILURE;
	}
	else if (siidr_ptr_1->record_size != siidr_ptr_2->record_size) {
		if (error_text != NULL)
			sprintf(error_text, "Record sizes differ (%u versus %u).",
				siidr_ptr_1->record_size, siidr_ptr_2->record_size);
		return_code = SIIDR_FAILURE;
	}
	else {
		for (count_1 = 0; count_1 < siidr_ptr_1->record_count; count_1++) {
			if (memcmp(siidr_ptr_1->record_list[count_1],
				siidr_ptr_2->record_list[count_1], siidr_ptr_1->record_size)) {
				if (error_text != NULL)
					sprintf(error_text, "Records differ at index %u.", count_1);
				return_code = SIIDR_FAILURE;
				break;
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
int SIIDR_TEST_Compare(const SIIDR *siidr_ptr,
	const SIIDR_TEST_DATA *ptr_1, const SIIDR_TEST_DATA *ptr_2,
	size_t data_length)
{
	return(strcmp(ptr_1->order_id, ptr_2->order_id));
}
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
int SIIDR_TEST_CompareBucket100(const SIIDR *siidr_ptr,
	const SIIDR_TEST_DATA *ptr_1, const SIIDR_TEST_DATA *ptr_2,
	size_t data_length)
{
	unsigned int bucket_1 = ptr_1->record_id / 100;
	unsigned int bucket_2 = ptr_2->record_id / 100;

	return(((bucket_1 < bucket_2) ? -1 : ((bucket_1 > bucket_2) ? 1 : 0)));
}
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
int SIIDR_TEST_CompareBucket1000(const SIIDR *siidr_ptr,
	const SIIDR_TEST_DATA *ptr_1, const SIIDR_TEST_DATA *ptr_2,
	size_t data_length)
{
	unsigned int bucket_1 = ptr_1->record_id / 1000;
	unsigned int bucket_2 = ptr_2->record_id / 1000;

	return(((bucket_1 < bucket_2) ? -1 : ((bucket_1 > bucket_2) ? 1 : 0)));
}
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
int SIIDR_TEST_CompareAlwaysEqual(const SIIDR *siidr_ptr,
	const SIIDR_TEST_DATA *ptr_1, const SIIDR_TEST_DATA *ptr_2,
	size_t data_length)
{
	return(0);
}
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
int SIIDR_TEST_CompareAlwaysLessThan(const SIIDR *siidr_ptr,
	const SIIDR_TEST_DATA *ptr_1, const SIIDR_TEST_DATA *ptr_2,
	size_t data_length)
{
	return(-1);
}
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
int SIIDR_TEST_CompareAlwaysGreaterThan(const SIIDR *siidr_ptr,
	const SIIDR_TEST_DATA *ptr_1, const SIIDR_TEST_DATA *ptr_2,
	size_t data_length)
{
	return(1);
}
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
int SIIDR_TEST_CompareEquivalent(const SIIDR *siidr_ptr,
	const SIIDR_TEST_DATA *ptr_1, const SIIDR_TEST_DATA *ptr_2,
	size_t data_length)
{
	return(SIIDR_TEST_Compare(siidr_ptr, ptr_1, ptr_2, data_length));
}
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
int SIIDR_TEST_GetSpecQuantity(const SIIDR *siidr_ptr,
	unsigned int *user_data_ptr, const SIIDR_TEST_DATA *record_ptr)
{
	return((record_ptr->quantity == *user_data_ptr) ? SIIDR_TRUE : SIIDR_FALSE);
}
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
int SIIDR_TEST_GetSpecQuantityEven(const SIIDR *siidr_ptr,
	unsigned int *user_data_ptr, const SIIDR_TEST_DATA *record_ptr)
{
	return((record_ptr->quantity % 2) ? SIIDR_FALSE : SIIDR_TRUE);
}
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
int SIIDR_TEST_GetSpecQuantityOdd(const SIIDR *siidr_ptr,
	unsigned int *user_data_ptr, const SIIDR_TEST_DATA *record_ptr)
{
	return((record_ptr->quantity % 2) ? SIIDR_TRUE : SIIDR_FALSE);
}
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
int SIIDR_TEST_GetSpecPrice(const SIIDR *siidr_ptr,
	double *user_data_ptr, const SIIDR_TEST_DATA *record_ptr)
{
	return((record_ptr->price == *user_data_ptr) ? SIIDR_TRUE : SIIDR_FALSE);
}
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

/*	***********************************************************************	*/
void SIIDR_TEST_ShowStats(const SIIDR *siidr_ptr)
{
	unsigned int count_1;
	char         stat_name[SIIDR_STAT_NAME_LEN + 1];
	char         buffer[SDTIF_FMTI_TIME_LEN_STAT_TVAL + 1];

	printf("%-*.*s %-10.10s %-*.*s %-*.*s\n",
		SIIDR_STAT_NAME_LEN, SIIDR_STAT_NAME_LEN,
		"Statistic Name",
		"Count",
		SDTIF_FMTI_TIME_LEN_STAT_TVAL - 11, SDTIF_FMTI_TIME_LEN_STAT_TVAL - 11,
		"Total Interval",
		SDTIF_FMTI_TIME_LEN_STAT_TVAL - 11, SDTIF_FMTI_TIME_LEN_STAT_TVAL - 11,
		"Sample Interval");

	STR_EMIT_CharSpace('-', SIIDR_STAT_NAME_LEN, NULL, NULL);
	STR_EMIT_CharSpace('-', 10, NULL, NULL);
	STR_EMIT_CharSpace('-', SDTIF_FMTI_TIME_LEN_STAT_TVAL - 11, NULL, NULL);
	STR_EMIT_CharLine( '-', SDTIF_FMTI_TIME_LEN_STAT_TVAL - 11, NULL, NULL);

	for (count_1 = 0; count_1 < SIIDR_STAT_COUNT; count_1++) {
		printf("%-*.*s %10lu %s ",
			SIIDR_STAT_NAME_LEN, SIIDR_STAT_NAME_LEN,
			strcpy(stat_name, SIIDR_STAT_IDX_TO_NAME(count_1)),
			siidr_ptr->stat_list[count_1].sample_count,
			SDTIF_STAT_TVAL_FmtTotalInterval(siidr_ptr->stat_list + count_1,
			buffer) + 11);
		printf("%s\n",
			SDTIF_STAT_TVAL_FmtSampleAverage(siidr_ptr->stat_list + count_1,
			buffer) + 11);
	}

	STR_EMIT_CharSpace('-', SIIDR_STAT_NAME_LEN, NULL, NULL);
	STR_EMIT_CharSpace('-', 10, NULL, NULL);
	STR_EMIT_CharSpace('-', SDTIF_FMTI_TIME_LEN_STAT_TVAL - 11, NULL, NULL);
	STR_EMIT_CharLine( '-', SDTIF_FMTI_TIME_LEN_STAT_TVAL - 11, NULL, NULL);
}
/*	***********************************************************************	*/

