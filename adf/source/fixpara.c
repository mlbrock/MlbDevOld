/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Contains logic to support the expansion of paragraph
								data with the specified character formatting.

	Revision History	:	1995-05-22 --- Creation.
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

#include <stdlib.h>
#include <string.h>

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
COMPAT_EXTERN_DATA_DECL const ADF_AREA ADF_AreaNameList[];
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#define ADF_PARA_HTEXT_LEFT				"(){}[]<>.,:;~!%^&*-+=|?"
#define ADF_PARA_HTEXT_RIGHT				"(){}[]<>.,:;~!%^&*-+=|?"
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	NEW_003																						*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(int          ADF_InsertHText,
	(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_PARA_TEXT **current_para_ptr,
	ADF_PARA_TEXT *next_para_ptr, unsigned int *alloc_count, char *error_text));
COMPAT_FN_DECL_STATIC(unsigned int ADF_FindHTextPointers,
	(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, const ADF_PARA_TEXT *para_ptr));
COMPAT_FN_DECL_STATIC(int          ADF_AllocInParaLineList,
	(ADF_CONTROL *control_ptr,
	unsigned int alloc_count, char *error_text));
COMPAT_FN_DECL_STATIC(int          ADF_AllocInParaHTextList,
	(ADF_CONTROL *control_ptr,
	const ADF_PARA_DATA *para_ptr, char *error_text));
COMPAT_FN_DECL_STATIC(int          ADF_AllocOutParaBuffer,
	(ADF_CONTROL *control_ptr,
	unsigned int string_length, char *error_text));
COMPAT_FN_DECL_STATIC(int          ADF_AllocWrapBuffer,
	(ADF_CONTROL *control_ptr,
	unsigned int alloc_length, char *error_text));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_FixParagraph(ADF_CONTROL *control_ptr, const ADF_ENTRY *entry_ptr,
	ADF_PARA_DATA *para_ptr, unsigned int cformat_flags, char *error_text)
#else
int ADF_FixParagraph(control_ptr, entry_ptr, para_ptr, cformat_flags,
	error_text)
ADF_CONTROL     *control_ptr;
const ADF_ENTRY *entry_ptr;
ADF_PARA_DATA   *para_ptr;
unsigned int     cformat_flags;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code = ADF_SUCCESS;
	unsigned int   alloc_count;
	unsigned int   cformat_and_value;
	char           tmp_char;
	char          *tmp_ptr_1;
	char          *tmp_ptr_2;
	ADF_PARA_TEXT *current_ptr;
   ADF_PARA_TEXT  tmp_para_line;

	alloc_count =
		(chrcnt(para_ptr->text_ptr, ADF_CFORMAT_MARKER_CHAR) * 2) + 1;

	if ((return_code = ADF_AllocInParaLineList(control_ptr, alloc_count,
		error_text)) != ADF_SUCCESS)
		goto EXIT_FUNCTION;
	else if ((return_code = ADF_AllocInParaHTextList(control_ptr,
		para_ptr, error_text)) != ADF_SUCCESS)
		goto EXIT_FUNCTION;

	tmp_ptr_1                            = para_ptr->text_ptr;
	control_ptr->current_para_line_count = 0;
	current_ptr                          = control_ptr->in_para_line_list;

	while (*tmp_ptr_1) {
		if (*tmp_ptr_1 == ADF_CFORMAT_MARKER_CHAR) {
			tmp_char          = ((char) toupper(*(tmp_ptr_1 + 1)));
			cformat_and_value = 0;
			switch (tmp_char) {
				case ADF_CFORMAT_CHAR_BOLD				:
					cformat_and_value = ADF_CFORMAT_TYPE_BOLD;
					break;
				case ADF_CFORMAT_CHAR_ITALIC			:
					cformat_and_value = ADF_CFORMAT_TYPE_ITALIC;
					break;
				case ADF_CFORMAT_CHAR_ULINED			:
					cformat_and_value = ADF_CFORMAT_TYPE_ULINED;
					break;
				case ADF_CFORMAT_CHAR_OLINED			:
					cformat_and_value = ADF_CFORMAT_TYPE_OLINED;
					break;
				case ADF_CFORMAT_CHAR_STHRU			:
					cformat_and_value = ADF_CFORMAT_TYPE_STHRU;
					break;
				case ADF_CFORMAT_CHAR_EINDEX			:
					cformat_and_value = ADF_CFORMAT_TYPE_EINDEX;
					break;
				case ADF_CFORMAT_CHAR_SUBSCRIPT		:
					cformat_and_value = ADF_CFORMAT_TYPE_SUBSCRIPT;
					break;
				case ADF_CFORMAT_CHAR_SUPERSCRIPT	:
					cformat_and_value = ADF_CFORMAT_TYPE_SUPERSCRIPT;
					break;
				case ADF_CFORMAT_CHAR_HTEXT			:
					cformat_and_value = ADF_CFORMAT_TYPE_HTEXT;
					break;
				default										:
					break;
			}
			if (cformat_flags & cformat_and_value) {
				current_ptr->cformat_type = *(tmp_ptr_1 + 1);
				current_ptr->htext_index  = 0;
				current_ptr->length       = 0;
				current_ptr->ptr          = NULL;
				current_ptr++;
				control_ptr->current_para_line_count++;
			}
			tmp_ptr_1 += 2;
		}
		else if ((tmp_ptr_2 = strchr(tmp_ptr_1, ADF_CFORMAT_MARKER_CHAR)) !=
			NULL) {
			tmp_para_line.cformat_type = ADF_CFORMAT_CHAR_NONE;
			tmp_para_line.htext_index  = 0;
			tmp_para_line.length       = ((unsigned int) (tmp_ptr_2 - tmp_ptr_1));
			tmp_para_line.ptr          = tmp_ptr_1;
			tmp_ptr_1                  = tmp_ptr_2;
			if (!(cformat_flags & ADF_CFORMAT_TYPE_HTEXT)) {
				*current_ptr++ = tmp_para_line;
				control_ptr->current_para_line_count++;
			}
			else if (control_ptr->in_htext_count && ((return_code =
				ADF_InsertHText(control_ptr, entry_ptr,
				&current_ptr, &tmp_para_line, &alloc_count, error_text)) !=
				ADF_SUCCESS))
				break;
		}
		else {
			tmp_para_line.cformat_type = ADF_CFORMAT_CHAR_NONE;
			tmp_para_line.htext_index  = 0;
			tmp_para_line.length       = strlen(tmp_ptr_1);
			tmp_para_line.ptr          = tmp_ptr_1;
			if (!(cformat_flags & ADF_CFORMAT_TYPE_HTEXT)) {
				*current_ptr++ = tmp_para_line;
				control_ptr->current_para_line_count++;
			}
			else if (control_ptr->in_htext_count)
				return_code = ADF_InsertHText(control_ptr, entry_ptr,
					&current_ptr, &tmp_para_line, &alloc_count, error_text);
			break;
		}
	}

	return_code = ADF_AllocOutParaBuffer(control_ptr,
		strlen(para_ptr->text_ptr), error_text);

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_FixParagraphWrap(ADF_CONTROL *control_ptr, const ADF_ENTRY *entry_ptr,
	ADF_PARA_DATA *para_ptr, unsigned int cformat_flags,
	unsigned int output_width, unsigned int tab_setting,
	unsigned int left_padding, char *error_text)
#else
int ADF_FixParagraphWrap(control_ptr, entry_ptr, para_ptr, cformat_flags,
	output_width, tab_setting, left_padding, error_text)
ADF_CONTROL     *control_ptr;
const ADF_ENTRY *entry_ptr;
ADF_PARA_DATA   *para_ptr;
unsigned int     cformat_flags;
unsigned int     output_width;
unsigned int     tab_setting;
unsigned int     left_padding;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code;
   unsigned int   count_1;
	unsigned int   current_width;
	int            current_column;
	int            tab_count;
	char           last_character;
	const char    *in_ptr;
	ADF_PARA_DATA  tmp_para_data;

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Fix-up the paragraph without any formatting whatsoever. If		*/
	/*	fails, or if it succeeds but not formatting was requested by the	*/
	/*	calling function, exit . . .													*/
	/*	*****************************************************************	*/
	if (((return_code = ADF_FixParagraph(control_ptr, entry_ptr, para_ptr, 0,
		error_text)) != ADF_SUCCESS) || (cformat_flags == 0))
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Ensure that we've enough space in our working buffer . . .		*/
	/*	*****************************************************************	*/
	if ((return_code = ADF_AllocWrapBuffer(control_ptr, (output_width * 2) +
		(output_width * tab_setting) + 100, error_text)) != ADF_SUCCESS)
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Now concatenate the wrapped lines into a single string . . .	*/
	/*	*****************************************************************	*/
	current_width                 = output_width;
	current_column                = 0;
	tab_count                     = 0;
	in_ptr                        = control_ptr->in_para_line_list->ptr;
	*control_ptr->out_para_buffer = '\0';
	while ((in_ptr = strwrap(in_ptr, &current_column, current_width,
		&tab_count, tab_setting, 0, &last_character,
		control_ptr->wrap_buffer)) != NULL) {
		if ((return_code = ADF_AllocOutParaBuffer(control_ptr,
			strlen(control_ptr->out_para_buffer) + (output_width * 2) +
			left_padding + 100, error_text)) != ADF_SUCCESS)
			goto EXIT_FUNCTION;
		if ((current_width != output_width) && left_padding) {
			for (count_1 = 0; count_1 < left_padding; count_1++)
				chrcat(control_ptr->out_para_buffer, ' ');
		}
		strcat(strcat(control_ptr->out_para_buffer,
			rtrim(control_ptr->wrap_buffer)), (*in_ptr) ? "\n" : "");
		current_width = output_width - left_padding;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		We'll use the wrapped string as the paragraph to wrap in a		*/
	/*	fix-up attempt (with formatting this time) . . .						*/
	/*	*****************************************************************	*/
	tmp_para_data          = *para_ptr;
	tmp_para_data.text_ptr = control_ptr->out_para_buffer;
	return_code = ADF_FixParagraph(control_ptr, entry_ptr, &tmp_para_data,
		cformat_flags, error_text);
	/*	*****************************************************************	*/

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_InsertHText(ADF_CONTROL *control_ptr, const ADF_ENTRY *entry_ptr,
	ADF_PARA_TEXT **current_para_ptr, ADF_PARA_TEXT *next_para_ptr,
	unsigned int *alloc_count, char *error_text)
#else
static int ADF_InsertHText(control_ptr, entry_ptr, current_para_ptr,
	next_para_ptr, alloc_count, error_text)
ADF_CONTROL      *control_ptr;
const ADF_ENTRY  *entry_ptr;
ADF_PARA_TEXT   **current_para_ptr;
ADF_PARA_TEXT    *next_para_ptr;
unsigned int     *alloc_count;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int             return_code = ADF_SUCCESS;
	unsigned int    count_1;
   unsigned int    found_count;
	ADF_HTEXT      *htext_ptr;
	ADF_HTEXT     **para_htext_ptr_list;
	unsigned int    htext_index;
	char           *tmp_ptr_1;
	char           *tmp_ptr_2;
	ADF_PARA_TEXT   tmp_para_line;
	ADF_PARA_TEXT  *old_in_para_line_list;

	if ((found_count = ADF_FindHTextPointers(control_ptr,
		entry_ptr, next_para_ptr)) > 0) {
		tmp_para_line       = *next_para_ptr;
		para_htext_ptr_list = control_ptr->in_para_htext_ptr_list;
		for (count_1 = 0; found_count && (count_1 < next_para_ptr->length); ) {
			if (para_htext_ptr_list[count_1] == NULL) {
				count_1++;
				continue;
			}
			found_count--;
			htext_ptr   = para_htext_ptr_list[count_1];
			htext_index =
				((unsigned int) (htext_ptr - control_ptr->in_htext_list));
			tmp_ptr_1   = next_para_ptr->ptr + count_1;
			tmp_ptr_2   = tmp_ptr_1 + htext_ptr->htext_length;
			old_in_para_line_list = control_ptr->in_para_line_list;
			if ((return_code = ADF_AllocInParaLineList(control_ptr,
				*alloc_count + 4, error_text)) != ADF_SUCCESS)
				goto EXIT_FUNCTION;
			/*	*****************************************************
				*****************************************************
				The function 'ADF_AllocInParaLineList()' may have
				re-allocated the 'in_para_line_list' member of the
				control structure. If so, we'll need to adjust the
				pointer that we're using to insert the hyper-text
				information . . .
				*****************************************************	*/
			if (control_ptr->in_para_line_list != old_in_para_line_list)
				*current_para_ptr = control_ptr->in_para_line_list +
					((unsigned int) (*current_para_ptr - old_in_para_line_list));
			/*	*****************************************************	*/
			if (tmp_ptr_1 != next_para_ptr->ptr) {
				tmp_para_line.cformat_type  = ADF_CFORMAT_CHAR_NONE;
				tmp_para_line.htext_index   = 0;
				tmp_para_line.length        =
					((unsigned int) (tmp_ptr_1 - next_para_ptr->ptr));
				tmp_para_line.ptr           = next_para_ptr->ptr;
				next_para_ptr->length      -= tmp_para_line.length;
				next_para_ptr->ptr         += tmp_para_line.length;
				**current_para_ptr          = tmp_para_line;
				(*current_para_ptr)++;
				control_ptr->current_para_line_count++;
				(*alloc_count)++;
			}
			(*current_para_ptr)->cformat_type  = ADF_CFORMAT_CHAR_HTEXT_1;
			(*current_para_ptr)->htext_index   = htext_index;
			(*current_para_ptr)->length        = 0;
			(*current_para_ptr)->ptr           = NULL;
			(*current_para_ptr)++;
			control_ptr->current_para_line_count++;
			(*alloc_count)++;
			(*current_para_ptr)->cformat_type  = ADF_CFORMAT_CHAR_NONE;
			(*current_para_ptr)->htext_index   = 0;
			(*current_para_ptr)->length        = htext_ptr->htext_length;
			(*current_para_ptr)->ptr           = tmp_ptr_1;
			control_ptr->current_para_line_count++;
			(*current_para_ptr)++;
			(*alloc_count)++;
			(*current_para_ptr)->cformat_type  = ADF_CFORMAT_CHAR_HTEXT_2;
			(*current_para_ptr)->htext_index   = 0;
			(*current_para_ptr)->length        = 0;
			(*current_para_ptr)->ptr           = NULL;
			(*current_para_ptr)++;
			control_ptr->current_para_line_count++;
			(*alloc_count)++;
			next_para_ptr->length             -= htext_ptr->htext_length;
			next_para_ptr->ptr                += htext_ptr->htext_length;
			para_htext_ptr_list                = para_htext_ptr_list +
				count_1 + htext_ptr->htext_length;
			count_1                            = 0;
		}
	}

	if (next_para_ptr->length) {
		**current_para_ptr = *next_para_ptr;
		(*current_para_ptr)++;
		control_ptr->current_para_line_count++;
		(*alloc_count)++;
	}

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static unsigned int ADF_FindHTextPointers(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, const ADF_PARA_TEXT *para_ptr)
#else
static unsigned int ADF_FindHTextPointers(control_ptr, entry_ptr, para_ptr)
ADF_CONTROL         *control_ptr;
const ADF_ENTRY     *entry_ptr;
const ADF_PARA_TEXT *para_ptr;
#endif /* #ifndef NARGS */
{
	unsigned int     found_count = 0;
	unsigned int     count_1;
	unsigned int     count_2;
	unsigned int     increment_count;
	ADF_HTEXT       *htext_ptr;
	ADF_HTEXT_CHARS *lookup_ptr;
	char            *tmp_ptr_1;
	char            *tmp_ptr_2;
	char            *tst_ptr_1;
	char            *tst_ptr_2;

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Initialize the list of pointers to hyper-text elements for		*/
	/*	each character position in the paragraph . . .							*/
	/*	*****************************************************************	*/
	for (count_1 = 0; count_1 < para_ptr->length; count_1++)
		control_ptr->in_para_htext_ptr_list[count_1] = NULL;
	/*	*****************************************************************	*/

	for (count_1 = 0; count_1 < para_ptr->length; ) {
		lookup_ptr = control_ptr->in_htext_lookup_list +
			((unsigned int) ((unsigned char) para_ptr->ptr[count_1]));
      if (!lookup_ptr->count) {
      	count_1++;
      	continue;
      }
		htext_ptr       = lookup_ptr->list + lookup_ptr->count;
		increment_count = 1;
		for (count_2 = lookup_ptr->count; count_2; count_2--) {
      	htext_ptr--;
			if (((para_ptr->length - count_1) >= htext_ptr->htext_length) &&
				((htext_ptr->htext_length == 1) ||
				((para_ptr->ptr[(count_1 + htext_ptr->htext_length) - 1] ==
				htext_ptr->hyper_text[htext_ptr->htext_length - 1]) &&
				(para_ptr->ptr[count_1 + (htext_ptr->htext_length >> 1)] ==
				htext_ptr->hyper_text[htext_ptr->htext_length >> 1])))) {
				tmp_ptr_1 = para_ptr->ptr + count_1;
				tmp_ptr_2 = tmp_ptr_1 + htext_ptr->htext_length;
				tst_ptr_1 = tmp_ptr_1;
				tst_ptr_2 = htext_ptr->hyper_text;
				while ((tst_ptr_1 < tmp_ptr_2) && (*tst_ptr_1++ == *tst_ptr_2++))
					;
				if (tst_ptr_1 != tmp_ptr_2)
					continue;
				increment_count = htext_ptr->htext_length;
				if ((entry_ptr->file_index == htext_ptr->file_index) &&
					(entry_ptr->entry_index == htext_ptr->entry_index))
					break;
				else if (((tmp_ptr_1 == para_ptr->ptr) ||
					isspace(*(tmp_ptr_1 - 1)) ||
					(strchr(ADF_PARA_HTEXT_LEFT, *(tmp_ptr_1 - 1)) != NULL)) &&
					(((para_ptr->length - count_1) == htext_ptr->htext_length) ||
					isspace(*tmp_ptr_2) || (!(*tmp_ptr_2)) ||
					(strchr(ADF_PARA_HTEXT_RIGHT, *tmp_ptr_2) != NULL))) {
					control_ptr->in_para_htext_ptr_list[count_1] = htext_ptr;
					found_count++;
				}
				break;
			}
		}
		count_1 += increment_count;
	}

	return(found_count);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_AllocInParaLineList(ADF_CONTROL *control_ptr,
	unsigned int alloc_count, char *error_text)
#else
static int ADF_AllocInParaLineList(control_ptr, alloc_count, error_text)
ADF_CONTROL  *control_ptr;
unsigned int  alloc_count;
char         *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code = ADF_SUCCESS;
	ADF_PARA_TEXT *tmp_ptr;

	alloc_count += (alloc_count % 100) ? (100 - (alloc_count % 100)) : 0;

	if (alloc_count > control_ptr->in_para_line_count) {
		tmp_ptr = ((ADF_PARA_TEXT *) ((!control_ptr->in_para_line_count) ?
			malloc(alloc_count * sizeof(ADF_PARA_TEXT)) :
			realloc(control_ptr->in_para_line_list,
			alloc_count * sizeof(ADF_PARA_TEXT))));
		if (tmp_ptr != NULL) {
			control_ptr->in_para_line_count = alloc_count;
			control_ptr->in_para_line_list  = ((ADF_PARA_TEXT *) tmp_ptr);
		}
		else {
			STR_AllocMsgList(alloc_count, sizeof(ADF_PARA_TEXT), error_text,
				"Unable to expand the area data line list");
			return_code = ADF_MEMORY_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_AllocInParaHTextList(ADF_CONTROL *control_ptr,
	const ADF_PARA_DATA *para_ptr, char *error_text)
#else
static int ADF_AllocInParaHTextList(control_ptr, para_ptr, error_text)
ADF_CONTROL         *control_ptr;
const ADF_PARA_DATA *para_ptr;
char                *error_text;
#endif /* #ifndef NARGS */
{
	int             return_code = ADF_SUCCESS;
	unsigned int   alloc_count;
	ADF_HTEXT    **tmp_htext_list;

	alloc_count  = strlen(para_ptr->text_ptr) + 1;
	alloc_count += (alloc_count % 128) ? (128 - (alloc_count % 128)) : 0;

	if (alloc_count > control_ptr->in_para_htext_ptr_count) {
		tmp_htext_list = ((ADF_HTEXT **)
			((control_ptr->in_para_htext_ptr_list == NULL) ?
			malloc(alloc_count * sizeof(ADF_HTEXT *)) :
			realloc(control_ptr->in_para_htext_ptr_list,
			alloc_count * sizeof(ADF_HTEXT *))));
		if (tmp_htext_list != NULL) {
			control_ptr->in_para_htext_ptr_count = alloc_count;
			control_ptr->in_para_htext_ptr_list  = tmp_htext_list;
		}
		else {
			STR_AllocMsgList(alloc_count, sizeof(ADF_HTEXT *), error_text,
				"Unable to expand the area data line hyper-text pointers");
			return_code = ADF_MEMORY_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_AllocOutParaBuffer(ADF_CONTROL *control_ptr,
	unsigned int string_length, char *error_text)
#else
static int ADF_AllocOutParaBuffer(control_ptr, string_length, error_text)
ADF_CONTROL  *control_ptr;
unsigned int  string_length;
char         *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code = ADF_SUCCESS;
	unsigned int  alloc_length;
	char         *tmp_ptr;

	alloc_length = (string_length * ADF_BASIC_CHAR_MULTIPLIER) +
		(control_ptr->current_para_line_count * ADF_CFORMAT_MULTIPLIER);

	if (alloc_length > control_ptr->out_para_buffer_length) {
		alloc_length = (alloc_length < 2048) ? 2048 : alloc_length;
		tmp_ptr      = ((char *) ((!control_ptr->out_para_buffer_length) ?
			malloc(alloc_length * sizeof(char)) :
			realloc(control_ptr->out_para_buffer, alloc_length * sizeof(char))));
		if (tmp_ptr != NULL) {
			control_ptr->out_para_buffer_length = alloc_length;
			control_ptr->out_para_buffer        = tmp_ptr;
		}
		else {
			STR_AllocMsgItem(alloc_length, error_text,
				"Unable to expand the output paragraph data buffer");
			return_code = ADF_MEMORY_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_AllocWrapBuffer(ADF_CONTROL *control_ptr,
	unsigned int alloc_length, char *error_text)
#else
static int ADF_AllocWrapBuffer(control_ptr, alloc_length, error_text)
ADF_CONTROL  *control_ptr;
unsigned int  alloc_length;
char         *error_text;
#endif /* #ifndef NARGS */
{
	int   return_code = ADF_SUCCESS;
	char *tmp_ptr;

	if (alloc_length > control_ptr->wrap_buffer_length) {
		alloc_length = (alloc_length < 512) ? 512 : alloc_length;
		tmp_ptr      = ((char *) ((!control_ptr->wrap_buffer_length) ?
			malloc(alloc_length * sizeof(char)) :
			realloc(control_ptr->wrap_buffer, alloc_length * sizeof(char))));
		if (tmp_ptr != NULL) {
			control_ptr->wrap_buffer_length = alloc_length;
			control_ptr->wrap_buffer        = tmp_ptr;
		}
		else {
			STR_AllocMsgItem(alloc_length, error_text,
				"Unable to expand the paragraph wrap data buffer");
			return_code = ADF_MEMORY_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <memory.h>

static const unsigned int TestCFormatFlags =
	(ADF_CFORMAT_TYPE_ALL ^ (ADF_CFORMAT_TYPE_HTEXT | ADF_CFORMAT_TYPE_EINDEX));

#ifdef __MSDOS__
COMPAT_EXTERN_DATA_DECL unsigned int _stklen = 24000;
#endif /* __MSDOS__ */

COMPAT_FN_DECL(int main, (int argc, char **argv));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int              return_code = ADF_SUCCESS;
	unsigned int     count_1;
	unsigned int     count_2;
	unsigned int     count_3;
	unsigned int     count_4;
	int              current_col;
	int              tab_count;
	char             last_char;
	unsigned int     cformat_flags;
	ADF_CONTROL      control_data;
	ADF_ENTRY_DATA   entry_data_list[ADF_AREA_COUNT];
	ADF_PARA_DATA   *para_ptr;
	char             area_name[ADF_AREA_NAME_LENGTH + 1];
	char            *tmp_ptr;
	struct timeval   start_time;
	struct timeval   end_time;
	char             tmp_buffer[1024];
	char             error_text[ADF_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'ADF_FixParagraph()'\n");
	fprintf(stderr, "---- ------- --- --------------------\n\n");

	ADF_INIT_Control(&control_data);

	control_data.cont_on_error_flag                             = ADF_TRUE;
	control_data.sort_order_type                                =
		ADF_SORT_ENTRY_BASE_NAME;
	control_data.hyper_text_flag                                = ADF_TRUE;
	control_data.keep_bad_see_also_flag                         = ADF_TRUE;
	control_data.ignore_section_list[ADF_AREA_SOURCE_FILE_DATE] = ADF_TRUE;
	control_data.area_name_type                                 =
		ADF_AREA_NAME_TYPE_INTERNAL;
	control_data.area_order_type                                =
		ADF_AREA_ORDER_TYPE_INTERNAL;


	if (argc < 2) {
		sprintf(error_text, "Invalid command line encountered.");
		fprintf(stderr,
			"USAGE:\n   %s <adf-db-file-name> [<adf-db-file-name>...]\n",
			argv[0]);
		return_code = ADF_BAD_ARGS_FAILURE;
	}
	else {
		for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
			fprintf(stderr, "File: %s\n", argv[count_1]);
			if ((return_code = ADF_OpenADFFileIn(&control_data, argv[count_1],
				error_text)) != ADF_SUCCESS) {
				if (return_code != ADF_PARSE_FAILURE)
					break;
				fprintf(stderr, "%s\n", error_text);
				return_code = ADF_SUCCESS;
			}
		}
		if (return_code == ADF_SUCCESS) {
			if ((return_code = ADF_FinalizeEntries(&control_data, error_text)) !=
				ADF_SUCCESS)
				goto EXIT_FUNCTION;
			SDTIF_GetTimeUSecs(&start_time);
			for (count_1 = 0; count_1 < control_data.in_entry_order_count;
				count_1++) {
				if ((return_code = ADF_GetEntry(&control_data,
					control_data.in_entry_order_list[count_1], entry_data_list,
					error_text)) != ADF_SUCCESS)
					goto EXIT_FUNCTION;
				STR_EMIT_CharLine('=', 78, NULL, NULL);
				for (count_2 = 0; count_2 < ADF_AREA_COUNT; count_2++) {
					if ((ADF_AreaNameList[count_2].output_flag != ADF_TRUE) ||
						(!entry_data_list[count_2].para_count))
						continue;
               if (count_2 == ADF_AREA_SOURCE_FILE_DATE)
               	continue;
					printf("%s:\n",
						initcaps(ADF_GetAreaName(count_2, area_name)));
					cformat_flags = TestCFormatFlags |
						((ADF_AreaNameList[count_2].htext_flag == ADF_TRUE) ?
						ADF_CFORMAT_TYPE_HTEXT : ADF_CFORMAT_TYPE_NONE);
					for (count_3 = 0;
						count_3 < entry_data_list[count_2].para_count; count_3++) {
						para_ptr = entry_data_list[count_2].para_list + count_3;
						if ((return_code = ADF_FixParagraph(&control_data,
							control_data.in_entry_order_list[count_1], para_ptr,
							cformat_flags, error_text)) != ADF_SUCCESS)
							goto EXIT_FUNCTION;
						current_col = 0;
						tab_count   = 0;
						tmp_ptr     = control_data.out_para_buffer;
						printf("        ");
						for (count_4 = 0;
							count_4 < control_data.current_para_line_count;
							count_4++) {
							if (control_data.in_para_line_list[count_4].
								cformat_type != ADF_CFORMAT_CHAR_NONE) {
								*tmp_ptr++ = ADF_CFORMAT_MARKER_CHAR;
								*tmp_ptr++ = ((char)
									control_data.in_para_line_list[count_4].
									cformat_type);
								*tmp_ptr   = '\0';
							}
							else if (control_data.in_para_line_list[count_4].
								length) {
								nstrcpy(((char *) tmp_ptr),
									control_data.in_para_line_list[count_4].ptr,
									control_data.in_para_line_list[count_4].length);
								tmp_ptr +=
									control_data.in_para_line_list[count_4].length;
							}
						}
						tmp_ptr = control_data.out_para_buffer;
						while ((tmp_ptr = ((char *) strwrap(tmp_ptr, &current_col,
							70, &tab_count, 3, 1, &last_char, tmp_buffer))) != NULL)
							printf("%s%s", tmp_buffer,
								(current_col) ? "" : "\n        ");
						printf("%s\n", (current_col) ? "\n" : "");
					}
				}
				STR_EMIT_CharLine('=', 78, NULL, NULL);
				ADF_INIT_AreaDataList(entry_data_list);
				fprintf(stderr, ".");
			}
			SDTIF_GetTimeUSecs(&end_time);
			fprintf(stderr, "\n\n");
			fprintf(stderr, "Total Time: %10.6lf\n\n",
				(SDTIF_GET_TIMEVAL_USECS_DOUBLE(&end_time) -
				SDTIF_GET_TIMEVAL_USECS_DOUBLE(&start_time)) / 1000000.0);
		}
	}

EXIT_FUNCTION:

	ADF_FREE_Control(&control_data);

	if (return_code != ADF_SUCCESS)
		fprintf(stderr, "ERROR: %s\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

