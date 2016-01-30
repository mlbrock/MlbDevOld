/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Logic to manage the update of databases from caches.

	Revision History	:	1995-01-28 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <limits.h>
#include <memory.h>
#include <string.h>

#include "dcr.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define DCR_UPD_OP_DELETE			1
#define DCR_UPD_OP_INSERT			2
#define DCR_UPD_OP_UPDATE			3
#define DCR_UPD_OP_INS_OR_UPD		4
#define DCR_UPD_OP_UPD_OR_INS		5

typedef struct {
	int            operation_mode;
	unsigned int   primary_key_count;
	unsigned int  *primary_key_list;
	char         **primary_key_name_list;
	DBC_CONTEXT    dbc_context_data;
} DCR_DB_SPEC;

typedef struct tag_DCR_UPD_CONTROL {
	DCR_CACHE          *cache_ptr;
	unsigned int        first_element;
	int                 by_index_flag;
	unsigned int        index_method;
	unsigned int        log_block_size;
	unsigned int        maximum_row_count;
	unsigned int        db_spec_count;
	DCR_DB_SPEC  *db_spec_list;
	MFILE              *log_mfile_ptr;
	MFILE              *reject_mfile_ptr;
	void               *user_data_ptr;
#ifndef NARGS
	int               (*pre_record_function)(
								struct tag_DCR_UPD_CONTROL *upd_control_ptr,
								unsigned int current_index,
								unsigned int record_element, void *in_record_ptr,
								void **out_record_ptr, int *skip_record_flag,
								int *cancel_flag, char *error_text);
	int               (*pre_operation_function)(
								struct tag_DCR_UPD_CONTROL *upd_control_ptr,
								int *cancel_flag, char *error_text);
	int               (*post_operation_function)(
								struct tag_DCR_UPD_CONTROL *upd_control_ptr,
								char *error_text);
#else
	int               (*pre_record_function)();
	int               (*pre_operation_function)();
	int               (*post_operation_function)();
#endif /* #ifndef NARGS */
	unsigned int        update_count;
	unsigned int        insert_count;
	unsigned int        skip_count;
	unsigned int        cancel_count;
	unsigned int        reject_count;
	unsigned int        this_pass_update_count;
	unsigned int        this_pass_insert_count;
	unsigned int        this_pass_skip_count;
	unsigned int        this_pass_cancel_count;
	unsigned int        this_pass_reject_count;
} DCR_UPD_CONTROL;

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#ifndef NARGS
void DCR_UPD_InitControl(DCR_UPD_CONTROL *upd_control_ptr);
int  DCR_UPD_Run(DCR_UPD_CONTROL *upd_control_ptr,
	char *error_text);
#else
void DCR_UPD_InitControl();
int  DCR_UPD_Run();
#endif /* #ifndef NARGS */
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define DCR_UPD_VERSION_NUMBER "01.00.00A"

/*	***********************************************************************	*/

void DCR_UPD_InitControl(upd_control_ptr)
DCR_UPD_CONTROL *upd_control_ptr;
{
	memset(upd_control_ptr, '\0', sizeof(*upd_control_ptr));

	upd_control_ptr->cache_ptr               = NULL;
	upd_control_ptr->first_element           = 0;
	upd_control_ptr->by_index_flag           = DCR_FALSE;
	upd_control_ptr->index_method            = 0;
	upd_control_ptr->log_block_size          = 0;
	upd_control_ptr->maximum_row_count       = 0;
	upd_control_ptr->db_spec_count           = 0;
	upd_control_ptr->db_spec_list            = NULL;
	upd_control_ptr->log_mfile_ptr           = NULL;
	upd_control_ptr->reject_mfile_ptr        = NULL;
	upd_control_ptr->user_data_ptr           = NULL;
	upd_control_ptr->pre_operation_function  = NULL;
	upd_control_ptr->pre_record_function     = NULL;
	upd_control_ptr->post_operation_function = NULL;
	upd_control_ptr->update_count            = 0;
	upd_control_ptr->insert_count            = 0;
	upd_control_ptr->skip_count              = 0;
	upd_control_ptr->cancel_count            = 0;
	upd_control_ptr->reject_count            = 0;
	upd_control_ptr->this_pass_update_count  = 0;
	upd_control_ptr->this_pass_insert_count  = 0;
	upd_control_ptr->this_pass_skip_count    = 0;
	upd_control_ptr->this_pass_cancel_count  = 0;
	upd_control_ptr->this_pass_reject_count  = 0;
}
/*	***********************************************************************	*/

int DCR_UPD_Run(upd_control_ptr, error_text)
DCR_UPD_CONTROL *upd_control_ptr;
char                  *error_text;
{
	int           return_code = DCR_SUCCESS;
	char         *sql_command = NULL;
	unsigned int  count_1;
	unsigned int  count_2;
	unsigned int  record_element;
	int           skip_record_flag;
   int           cancel_flag;
	char         *record_ptr_1;
	char         *record_ptr_2;

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	upd_control_ptr->this_pass_update_count = 0;
	upd_control_ptr->this_pass_insert_count = 0;
	upd_control_ptr->this_pass_skip_count   = 0;
	upd_control_ptr->this_pass_cancel_count = 0;
	upd_control_ptr->this_pass_reject_count = 0;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	if (upd_control_ptr->cache_ptr == NULL) {
		strcpy(error_text, "The cache pointer is 'NULL'.");
		return_code = DCR_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	if ((upd_control_ptr->by_index_flag == DCR_TRUE) &&
		(upd_control_ptr->index_method >=
		upd_control_ptr->cache_ptr->index_count)) {
		sprintf(error_text, "%s (%u) %s (%u).",
			"The specified index method", upd_control_ptr->index_method,
			"is greater than or equal to the number of indices in the cache",
			upd_control_ptr->cache_ptr->index_count);
		return_code = DCR_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	if (upd_control_ptr->first_element &&
		(upd_control_ptr->first_element >=
		upd_control_ptr->cache_ptr->record_count)) {
		sprintf(error_text, "%s (%u) %s (%u).",
			"The specified first element", upd_control_ptr->first_element,
			"is greater than or equal to the number of records in the cache",
			upd_control_ptr->cache_ptr->record_count);
		return_code = DCR_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	if (upd_control_ptr->log_block_size &&
		(upd_control_ptr->log_mfile_ptr == NULL)) {
		sprintf(error_text, "%s (%u), but no log file pointer was initialized.",
			"The cache update log block size is non-zero",
			upd_control_ptr->log_block_size);
		return_code = DCR_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	if ((return_code = DCR_AllocSQLString(upd_control_ptr->cache_ptr,
		&sql_command, error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	if ((upd_control_ptr->by_index_flag == DCR_TRUE) &&
		(DCR_INDEX_IS_MAPPED(upd_control_ptr->cache_ptr,
		upd_control_ptr->index_method) != DCR_TRUE)) {
		if ((return_code = DCR_MapDataAndIndex(upd_control_ptr->cache_ptr,
			NULL, NULL, upd_control_ptr->index_method, NULL, NULL,
			error_text)) != DCR_SUCCESS)
			goto EXIT_FUNCTION;
	}
	else if (DCR_DATA_IS_MAPPED(upd_control_ptr->cache_ptr) !=
		DCR_TRUE) {
		if ((return_code = DCR_MapData(upd_control_ptr->cache_ptr,
			NULL, NULL, error_text)) != DCR_SUCCESS)
			goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	if (upd_control_ptr->cache_ptr->record_count)
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	for (count_1 = upd_control_ptr->first_element;
		count_1 < upd_control_ptr->cache_ptr->record_count; count_1++) {
		record_element   = (upd_control_ptr->by_index_flag == DCR_TRUE) ?
			DCR_IELE_TO_RELE(upd_control_ptr->cache_ptr,
			upd_control_ptr->index_method, count_1) : count_1;
		record_ptr_1     =
			DCR_RELE_TO_RPTR(upd_control_ptr->cache_ptr, record_element);
		record_ptr_2     = record_ptr_1;
		skip_record_flag = DCR_FALSE;
		cancel_flag      = DCR_FALSE;
		if (upd_control_ptr->pre_record_function != NULL) {
			if ((return_code = (*upd_control_ptr->pre_record_function)
				(upd_control_ptr, count_1, record_element, record_ptr_1,
				((void **) &record_ptr_2), &skip_record_flag, &cancel_flag,
				error_text)) != DCR_SUCCESS)
				break;
			else if (skip_record_flag == DCR_TRUE) {
				upd_control_ptr->this_pass_skip_count++;
				continue;
			}
			else if (cancel_flag == DCR_TRUE) {
				upd_control_ptr->this_pass_cancel_count++;
				break;
			}
		}
		for (count_2 = 0; count_2 < upd_control_ptr->db_spec_count; count_2++) {
			;
		}
	}
	/*	*****************************************************************	*/

EXIT_FUNCTION:

	if (sql_command != NULL)
		free(sql_command);

	upd_control_ptr->update_count += upd_control_ptr->this_pass_update_count;
	upd_control_ptr->insert_count += upd_control_ptr->this_pass_insert_count;
	upd_control_ptr->skip_count   += upd_control_ptr->this_pass_skip_count;
	upd_control_ptr->cancel_count += upd_control_ptr->this_pass_cancel_count;
	upd_control_ptr->reject_count += upd_control_ptr->this_pass_reject_count;

	return(return_code);
}
/*	***********************************************************************	*/

