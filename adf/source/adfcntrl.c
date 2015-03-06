/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Manages the initialization and freeing of the ADF
								control data structure.

	Revision History	:	1995-04-30 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2015.
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
#include <stdlib.h>
#include <string.h>

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_INIT_Control(ADF_CONTROL *control_ptr)
#else
void ADF_INIT_Control(control_ptr)
ADF_CONTROL *control_ptr;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;
	unsigned int count_2;

	memset(control_ptr, '\0', sizeof(*control_ptr));

	control_ptr->program_name              = NULL;
	control_ptr->short_program_name        = NULL;
	control_ptr->host_name[0]              = '\0';
	control_ptr->process_id                = 0;
	control_ptr->current_dir[0]            = '\0';
	control_ptr->start_time.tv_sec         = 0L;
	control_ptr->start_time.tv_usec        = 0L;
	control_ptr->end_time.tv_sec           = 0L;
	control_ptr->end_time.tv_usec          = 0L;
	control_ptr->overhead_end_time.tv_sec  = 0L;
	control_ptr->overhead_end_time.tv_usec = 0L;
	control_ptr->help_flag                 = ADF_FALSE;
	control_ptr->version_flag              = ADF_FALSE;
	control_ptr->shut_down_flag            = GENFUNCS_FALSE;
	control_ptr->signal_received_flag      = GENFUNCS_FALSE;
	control_ptr->queue_signal_flag         = GENFUNCS_FALSE;
	control_ptr->domain_count              = 0;
	control_ptr->domain_list               = NULL;
	control_ptr->adf_def_file_name         = NULL;
	control_ptr->prep_adf_file_name        = NULL;
	control_ptr->prep_adf_file             = NULL;
	control_ptr->prep_adf_file_mode        = ADF_PREP_FILE_MODE_EITHER;
	control_ptr->prep_tmp_file_name        = NULL;
	control_ptr->prep_src_file_length      = 0;
	control_ptr->prep_src_file             = NULL;
	control_ptr->prep_src_core_file_length = 0;
	control_ptr->prep_src_core_file        = NULL;
	control_ptr->in_file_name_count        = 0;
	control_ptr->in_file_name_list         = NULL;
	control_ptr->htext_ref_file_name_count = 0;
	control_ptr->htext_ref_file_name_list  = NULL;
	control_ptr->in_file_count             = 0;
	control_ptr->in_file_list              = NULL;
	control_ptr->prep_entry_count          = 0;
	control_ptr->prep_entry_list           = NULL;
	control_ptr->prep_htext_count          = 0;
	control_ptr->prep_htext_list           = NULL;
	control_ptr->in_entry_count            = 0;
	control_ptr->in_entry_list             = NULL;
	control_ptr->in_htext_count            = 0;
	control_ptr->in_htext_list             = NULL;
	control_ptr->in_entry_order_count      = 0;
	control_ptr->in_entry_order_list       = NULL;
	control_ptr->read_entry_buffer_length  = 0;
	control_ptr->read_entry_buffer         = NULL;
	control_ptr->current_para_line_count   = 0;
	control_ptr->in_para_line_count        = 0;
	control_ptr->in_para_line_list         = NULL;
	control_ptr->in_para_htext_ptr_count   = 0;
	control_ptr->in_para_htext_ptr_list    = NULL;
	control_ptr->out_para_buffer_length    = 0;
	control_ptr->out_para_buffer           = NULL;
	control_ptr->wrap_buffer_length        = 0;
	control_ptr->wrap_buffer               = NULL;
	control_ptr->in_entry_para_count       = 0;
	control_ptr->in_entry_para_list        = NULL;
	control_ptr->default_author            = NULL;
	control_ptr->default_copyright         = NULL;
	control_ptr->default_man_page          = NULL;
	control_ptr->log_dir                   = NULL;
	control_ptr->log_file_name             = NULL;
	control_ptr->mlog_ptr                  = NULL;
	control_ptr->output_dir                = NULL;
	control_ptr->output_dir_basic          = NULL;
	control_ptr->output_file_name_length   = 0;
	control_ptr->output_file_name          = NULL;
	control_ptr->output_file_ptr           = NULL;
	control_ptr->htext_link_name_length    = 0;
	control_ptr->htext_link_name           = NULL;
	control_ptr->duplicate_handling_type   = ADF_DUP_HANDLER_NONE;
	control_ptr->sort_order_type           = ADF_SORT_ENTRY_ENTRY;
	control_ptr->output_type               = ADF_OUTPUT_TYPE_ASCII;
	control_ptr->check_only_flag           = ADF_FALSE;
	control_ptr->cont_on_error_flag        = ADF_FALSE;
	control_ptr->ignore_bad_cmnt_flag      = ADF_FALSE;
	control_ptr->forced_author_flag        = ADF_FALSE;
	control_ptr->forced_copyright_flag     = ADF_FALSE;
	control_ptr->forced_man_page_flag      = ADF_FALSE;
	control_ptr->check_comment_flag        = ADF_FALSE;
	control_ptr->error_on_no_comment_flag  = ADF_FALSE;
	control_ptr->no_required_sections_flag = ADF_FALSE;
	control_ptr->ignore_bad_xrefs_flag     = ADF_FALSE;
	control_ptr->remove_bad_xrefs_flag     = ADF_FALSE;
	control_ptr->keep_bad_xrefs_flag       = ADF_FALSE;
	control_ptr->list_frame_xrefs_flag     = ADF_FALSE;
	control_ptr->xref_tree_flag            = ADF_FALSE;
	control_ptr->hyper_text_flag           = ADF_FALSE;
	control_ptr->generate_type             = ADF_GENERATE_TYPE_ENTRY;
	control_ptr->log_flag                  = ADF_FALSE;
	control_ptr->quiet_flag                = ADF_FALSE;
	control_ptr->output_comment_flag       = ADF_TRUE;
	control_ptr->output_by_file_flag       = ADF_FALSE;
	control_ptr->output_to_stdout_flag     = ADF_FALSE;
	control_ptr->keep_bad_see_also_flag    = ADF_FALSE;
	control_ptr->html_version              = ADF_HTML_VERSION_DEFAULT;
	control_ptr->area_name_type            = ADF_AREA_NAME_TYPE_DEF;
	control_ptr->area_order_type           = ADF_AREA_ORDER_TYPE_DEF;
	control_ptr->entry_include_count       = 0;
	control_ptr->entry_exclude_count       = 0;
	control_ptr->htext_include_count       = 0;
	control_ptr->htext_exclude_count       = 0;
	control_ptr->non_ref_index_count       = 0;
	control_ptr->non_ref_index_list        = NULL;
	control_ptr->rtf_para_style_list_flag  = ADF_FALSE;

	for (count_1 = 0; count_1 <= UCHAR_MAX; count_1++) {
		control_ptr->in_htext_lookup_list[count_1].count = 0;
		control_ptr->in_htext_lookup_list[count_1].list  = NULL;
	}

	for (count_1 = 0; count_1 < ADF_AREA_COUNT; count_1++)
		control_ptr->ignore_section_list[count_1] = ADF_FALSE;

	for (count_1 = 0; count_1 < ADF_CLUDE_BASIS_COUNT; count_1++) {
		for (count_2 = 0; count_2 < ADF_CLUDE_TYPE_COUNT; count_2++)
			ADF_INIT_CludeItem(&control_ptr->entry_clude[count_1][count_2]);
	}

	for (count_1 = 0; count_1 < ADF_CLUDE_BASIS_COUNT; count_1++)
		ADF_INIT_CludeItem(&control_ptr->htext_clude[count_1]);

	for (count_1 = 0; count_1 < ADF_AREA_COUNT; count_1++)
		control_ptr->area_name_list[count_1] = NULL;

	for (count_1 = 0; count_1 < ADF_PFORMAT_COUNT; count_1++)
		control_ptr->rtf_para_style_list[count_1] = NULL;

	ADF_InitDataFRAME(&control_ptr->frame_data);
	ADF_InitDataHTML(&control_ptr->html_data);
	ADF_InitDataMAN(&control_ptr->man_data);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_FREE_Control(ADF_CONTROL *control_ptr)
#else
void ADF_FREE_Control(control_ptr)
ADF_CONTROL *control_ptr;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;
	unsigned int count_2;

	if (control_ptr->program_name != NULL)
		free(control_ptr->program_name);

	if (control_ptr->short_program_name != NULL)
		free(control_ptr->short_program_name);

	if (control_ptr->adf_def_file_name != NULL)
		free(control_ptr->adf_def_file_name);

	if (control_ptr->prep_adf_file_name != NULL)
		free(control_ptr->prep_adf_file_name);

	if (control_ptr->prep_tmp_file_name != NULL)
		free(control_ptr->prep_tmp_file_name);

	ADF_CloseADFFilePrep(control_ptr);

	if (control_ptr->prep_src_file != NULL)
		free(control_ptr->prep_src_file);

	if (control_ptr->prep_src_core_file != NULL)
		free(control_ptr->prep_src_core_file);

	strl_remove_all(&control_ptr->in_file_name_count,
		&control_ptr->in_file_name_list);

	strl_remove_all(&control_ptr->htext_ref_file_name_count,
		&control_ptr->htext_ref_file_name_list);

	ADF_FreeInFileList(control_ptr);

	ADF_FREE_DomainList(&control_ptr->domain_count, &control_ptr->domain_list);

	ADF_FreeEntryListPrep(control_ptr);
	ADF_FreeHTextListPrep(control_ptr);
	ADF_FreeEntryListIn(control_ptr);
	ADF_FreeHTextListIn(control_ptr);

	if (control_ptr->in_entry_order_list != NULL)
		free(control_ptr->in_entry_order_list);

	if (control_ptr->read_entry_buffer != NULL)
		free(control_ptr->read_entry_buffer);

	mema_remove_all(&control_ptr->in_para_line_count,
		((void **) &control_ptr->in_para_line_list));

	mema_remove_all(&control_ptr->in_para_htext_ptr_count,
		((void **) &control_ptr->in_para_htext_ptr_list));

	if (control_ptr->out_para_buffer != NULL)
		free(control_ptr->out_para_buffer);

	if (control_ptr->wrap_buffer != NULL)
		free(control_ptr->wrap_buffer);

	if (control_ptr->in_entry_para_list != NULL)
		free(control_ptr->in_entry_para_list);

	if (control_ptr->default_author != NULL)
		free(control_ptr->default_author);

	if (control_ptr->default_copyright != NULL)
		free(control_ptr->default_copyright);

	if (control_ptr->default_man_page != NULL)
		free(control_ptr->default_man_page);

	if (control_ptr->log_dir != NULL)
		free(control_ptr->log_dir);

	if (control_ptr->log_file_name != NULL)
		free(control_ptr->log_file_name);

	if (control_ptr->mlog_ptr != NULL)
		MLOG_Close(control_ptr->mlog_ptr, NULL);

	if (control_ptr->output_dir != NULL)
		free(control_ptr->output_dir);

	if (control_ptr->output_dir_basic != NULL)
		free(control_ptr->output_dir_basic);

	if (control_ptr->output_file_name != NULL)
		free(control_ptr->output_file_name);

	if (control_ptr->htext_link_name != NULL)
		free(control_ptr->htext_link_name);

	if (control_ptr->output_file_ptr != NULL)
		fclose(control_ptr->output_file_ptr);

	for (count_1 = 0; count_1 < ADF_CLUDE_BASIS_COUNT; count_1++) {
		for (count_2 = 0; count_2 < ADF_CLUDE_TYPE_COUNT; count_2++)
			ADF_FREE_CludeItem(&control_ptr->entry_clude[count_1][count_2]);
	}

	for (count_1 = 0; count_1 < ADF_CLUDE_BASIS_COUNT; count_1++)
		ADF_FREE_CludeItem(&control_ptr->htext_clude[count_1]);

	for (count_1 = 0; count_1 < ADF_AREA_COUNT; count_1++) {
		if (control_ptr->area_name_list[count_1] != NULL)
			free(control_ptr->area_name_list[count_1]);
		control_ptr->area_name_list[count_1] = NULL;
	}

	if (control_ptr->non_ref_index_count)
		strl_remove_all(&control_ptr->non_ref_index_count,
			&control_ptr->non_ref_index_list);

	for (count_1 = 0; count_1 < ADF_PFORMAT_COUNT; count_1++) {
		if (control_ptr->rtf_para_style_list[count_1] != NULL)
			free(control_ptr->rtf_para_style_list[count_1]);
		control_ptr->rtf_para_style_list[count_1] = NULL;
	}

	ADF_FreeDataFRAME(&control_ptr->frame_data);
	ADF_FreeDataHTML(&control_ptr->html_data);
	ADF_FreeDataMAN(&control_ptr->man_data);

	ADF_INIT_Control(control_ptr);
}
/*	***********************************************************************	*/

