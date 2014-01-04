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
*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <memory.h>
#include <stdlib.h>
#include <string.h>

#include <genfuncs.h>

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

extern const ADF_AREA ADF_AreaNameList[];

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	NEW_001																						*/
/*	***********************************************************************	*/

static unsigned int   control_ptr__in_para_htext_ptr_count = 0;
static ADF_HTEXT    **control_ptr__in_para_htext_ptr_list  = NULL;

#ifndef NARGS
int                 NEW_001_ADF_FixParagraph(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_PARA_DATA *para_ptr,
	unsigned int cformat_flags, char *error_text);
static int          NEW_001_ADF_InsertHText(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_PARA_TEXT **current_para_ptr,
	ADF_PARA_TEXT *next_para_ptr, unsigned int *alloc_count, char *error_text);
static unsigned int NEW_001_ADF_FindHTextPointers(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, const ADF_PARA_TEXT *para_ptr);
static int          NEW_001_ADF_AllocInParaHTextList(ADF_CONTROL *control_ptr,
	const ADF_PARA_DATA *para_ptr, char *error_text);
#else
#endif /* #ifndef NARGS */

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	NEW_002																						*/
/*	***********************************************************************	*/

typedef struct {
	unsigned int  count;
	ADF_HTEXT    *list;
} ADF_HTEXT_MATCH;

static ADF_HTEXT_MATCH   control_ptr__in_htext_lookup_list[UCHAR_MAX + 1];
/*
static unsigned int      control_ptr__in_para_htext_ptr_count = 0;
static ADF_HTEXT       **control_ptr__in_para_htext_ptr_list  = NULL;
*/

#ifndef NARGS
static void         NEW_002_ADF_MakeHTextMatchList(ADF_CONTROL *control_ptr);
int                 NEW_002_ADF_FixParagraph(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_PARA_DATA *para_ptr,
	unsigned int cformat_flags, char *error_text);
static int          NEW_002_ADF_InsertHText(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_PARA_TEXT **current_para_ptr,
	ADF_PARA_TEXT *next_para_ptr, unsigned int *alloc_count, char *error_text);
static unsigned int NEW_002_ADF_FindHTextPointers(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, const ADF_PARA_TEXT *para_ptr);
static int          NEW_002_ADF_AllocInParaHTextList(ADF_CONTROL *control_ptr,
	const ADF_PARA_DATA *para_ptr, char *error_text);
#else
#endif /* #ifndef NARGS */

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	NEW_003																						*/
/*	***********************************************************************	*/

/*
typedef struct {
	unsigned int  count;
	ADF_HTEXT    *list;
} ADF_HTEXT_MATCH;

static ADF_HTEXT_MATCH   control_ptr__in_htext_lookup_list[UCHAR_MAX + 1];
static unsigned int      control_ptr__in_para_htext_ptr_count = 0;
static ADF_HTEXT       **control_ptr__in_para_htext_ptr_list  = NULL;
*/

#ifndef NARGS
static void         NEW_003_ADF_MakeHTextMatchList(ADF_CONTROL *control_ptr);
int                 NEW_003_ADF_FixParagraph(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_PARA_DATA *para_ptr,
	unsigned int cformat_flags, char *error_text);
static int          NEW_003_ADF_InsertHText(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_PARA_TEXT **current_para_ptr,
	ADF_PARA_TEXT *next_para_ptr, unsigned int *alloc_count, char *error_text);
static unsigned int NEW_003_ADF_FindHTextPointers(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, const ADF_PARA_TEXT *para_ptr);
static int          NEW_003_ADF_AllocInParaHTextList(ADF_CONTROL *control_ptr,
	const ADF_PARA_DATA *para_ptr, char *error_text);
#else
#endif /* #ifndef NARGS */

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	NEW_004																						*/
/*	***********************************************************************	*/

typedef struct {
	unsigned long  hash_key;
	char          *ptr;
	unsigned int   length;
} ADF_HTEXT_LOOKUP;

static ADF_HTEXT_LOOKUP *control_ptr__in_para_hash_key = NULL;

static unsigned long    *control_ptr__in_htext_hash_key_list = NULL;

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#ifndef NARGS
static int ADF_InsertHText(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, unsigned int htext_index,
	ADF_PARA_TEXT **current_para_ptr, ADF_PARA_TEXT *next_para_ptr,
	unsigned int *alloc_count, char *error_text);
static int ADF_AllocInParaLineList(ADF_CONTROL *control_ptr,
	unsigned int alloc_count, char *error_text);
static int ADF_AllocOutParaBuffer(ADF_CONTROL *control_ptr,
	const char *para_text, char *error_text);
#else
static int ADF_InsertHText();
static int ADF_AllocInParaLineList();
static int ADF_AllocOutParaBuffer();
#endif /* #ifndef NARGS */

#ifndef NARGS
static int   NEW_004_ADF_InsertHText(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, unsigned int htext_index,
	ADF_PARA_TEXT **current_para_ptr, ADF_PARA_TEXT *next_para_ptr,
	unsigned int *alloc_count, char *error_text);
static int   NEW_004_ADF_AllocInParaLineList(ADF_CONTROL *control_ptr,
	unsigned int alloc_count, char *error_text);
static char *ADF_FindHTextInPara(const ADF_CONTROL *control_ptr,
	unsigned int htext_index, const ADF_PARA_TEXT *para_ptr,
	const ADF_HTEXT_LOOKUP *para_hash_list);
#else
static int   NEW_004_ADF_InsertHText();
static int   NEW_004_ADF_AllocInParaLineList();
#endif /* #ifndef NARGS */

#ifndef NARGS
int           ADF_InitHTextHashList(ADF_CONTROL *control_ptr,
	char *error_text);
void          ADF_InitParaHashList(const ADF_PARA_TEXT *para_ptr);
unsigned long ADF_CalcHTextHashKey(unsigned int in_length,
	const char *in_ptr);
int           ADF_SCMP_ParaTextHashItem(void *control_ptr,
	const ADF_HTEXT_LOOKUP *ptr_1, const ADF_HTEXT_LOOKUP *ptr_2,
	size_t data_length);
#else
#endif /* #ifndef NARGS */

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int ADF_FixParagraph(control_ptr, entry_ptr, para_ptr, cformat_flags,
	error_text)
ADF_CONTROL     *control_ptr;
const ADF_ENTRY *entry_ptr;
ADF_PARA_DATA   *para_ptr;
unsigned int     cformat_flags;
char            *error_text;
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

	tmp_ptr_1                            = para_ptr->text_ptr;
	control_ptr->current_para_line_count = 0;
	current_ptr                          = control_ptr->in_para_line_list;

	while (*tmp_ptr_1) {
		if (*tmp_ptr_1 == ADF_CFORMAT_MARKER_CHAR) {
			tmp_char          = toupper(*(tmp_ptr_1 + 1));
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
				control_ptr->in_htext_count, &current_ptr, &tmp_para_line,
				&alloc_count, error_text)) != ADF_SUCCESS))
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
					control_ptr->in_htext_count, &current_ptr, &tmp_para_line,
					&alloc_count, error_text);
			break;
		}
	}

	return_code = ADF_AllocOutParaBuffer(control_ptr, para_ptr->text_ptr,
		error_text);

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static int ADF_InsertHText(control_ptr, entry_ptr, htext_index,
	current_para_ptr, next_para_ptr, alloc_count, error_text)
ADF_CONTROL      *control_ptr;
const ADF_ENTRY  *entry_ptr;
unsigned int      htext_index;
ADF_PARA_TEXT   **current_para_ptr;
ADF_PARA_TEXT    *next_para_ptr;
unsigned int     *alloc_count;
char             *error_text;
{
	int            return_code = ADF_SUCCESS;
   unsigned int   count_1;
	ADF_HTEXT     *htext_ptr;
	unsigned int  *boyer_moore_ptr;
	unsigned int   string_length;
	char          *string_ptr;
	char          *tmp_ptr_1;
	char          *tmp_ptr_2;
	ADF_PARA_TEXT  tmp_para_line;

	for (count_1 = htext_index; count_1; ) {
		htext_ptr = control_ptr->in_htext_list + --count_1;
		if ((next_para_ptr->length < htext_ptr->htext_length) ||
			((entry_ptr->file_index == htext_ptr->file_index) &&
			(entry_ptr->entry_index == htext_ptr->entry_index)))
			continue;
		string_length   = next_para_ptr->length;
		string_ptr      = next_para_ptr->ptr;
		boyer_moore_ptr = control_ptr->htext_boyer_moore_data +
			((UCHAR_MAX + 1) * count_1);
		while (string_length >= htext_ptr->htext_length) {
			if (control_ptr->htext_boyer_moore_data == NULL) {
				if ((tmp_ptr_1 = memmem(string_length, string_ptr,
					htext_ptr->htext_length, htext_ptr->hyper_text)) == NULL)
					break;
			}
			else if ((tmp_ptr_1 = BoyerMoore_mem_search_basic(string_length,
				string_ptr, htext_ptr->htext_length, htext_ptr->hyper_text,
				boyer_moore_ptr, NULL)) == NULL)
				break;
			tmp_ptr_2 = tmp_ptr_1 + htext_ptr->htext_length;
			if (((tmp_ptr_1 == next_para_ptr->ptr) ||
				isspace(*(tmp_ptr_1 - 1))) &&
				((string_length == htext_ptr->htext_length) ||
				(isspace(*tmp_ptr_2) || (!(*tmp_ptr_2))))) {
				if ((return_code = ADF_AllocInParaLineList(control_ptr,
					*alloc_count + 4, error_text)) != ADF_SUCCESS)
					goto EXIT_FUNCTION;
				if (tmp_ptr_1 != string_ptr) {
					tmp_para_line.cformat_type  = ADF_CFORMAT_CHAR_NONE;
					tmp_para_line.htext_index   = 0;
					tmp_para_line.length        =
						((unsigned int) (tmp_ptr_1 - string_ptr));
					tmp_para_line.ptr           = string_ptr;
					next_para_ptr->length      -= tmp_para_line.length;
					next_para_ptr->ptr         += tmp_para_line.length;
					if (!count_1) {
						**current_para_ptr = tmp_para_line;
						(*current_para_ptr)++;
						control_ptr->current_para_line_count++;
						(*alloc_count)++;
					}
					else if ((return_code = ADF_InsertHText(control_ptr, entry_ptr,
						count_1, current_para_ptr, &tmp_para_line, alloc_count,
						error_text)) != ADF_SUCCESS)
						break;
				}
				(*current_para_ptr)->cformat_type  = ADF_CFORMAT_CHAR_HTEXT_1;
				(*current_para_ptr)->htext_index   = count_1;
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
				string_length                      = next_para_ptr->length;
				string_ptr                         = next_para_ptr->ptr;
			}
			else {
				string_length -= htext_ptr->htext_length;
				string_ptr    += htext_ptr->htext_length;
			}
		}
		if (!next_para_ptr->length)
			goto EXIT_FUNCTION;
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
static int ADF_AllocInParaLineList(control_ptr, alloc_count, error_text)
ADF_CONTROL  *control_ptr;
unsigned int  alloc_count;
char         *error_text;
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
			GEN_AllocMsgList(alloc_count, sizeof(ADF_PARA_TEXT), error_text,
				"Unable to expand the area data line list");
			return_code = ADF_MEMORY_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int NEW_001_ADF_FixParagraph(control_ptr, entry_ptr, para_ptr, cformat_flags,
	error_text)
ADF_CONTROL     *control_ptr;
const ADF_ENTRY *entry_ptr;
ADF_PARA_DATA   *para_ptr;
unsigned int     cformat_flags;
char            *error_text;
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
	else if ((return_code = NEW_001_ADF_AllocInParaHTextList(control_ptr,
		para_ptr, error_text)) != ADF_SUCCESS)
		goto EXIT_FUNCTION;

	tmp_ptr_1                            = para_ptr->text_ptr;
	control_ptr->current_para_line_count = 0;
	current_ptr                          = control_ptr->in_para_line_list;

	while (*tmp_ptr_1) {
		if (*tmp_ptr_1 == ADF_CFORMAT_MARKER_CHAR) {
			tmp_char          = toupper(*(tmp_ptr_1 + 1));
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
				NEW_001_ADF_InsertHText(control_ptr, entry_ptr,
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
				return_code = NEW_001_ADF_InsertHText(control_ptr, entry_ptr,
					&current_ptr, &tmp_para_line, &alloc_count, error_text);
			break;
		}
	}

	return_code = ADF_AllocOutParaBuffer(control_ptr, para_ptr->text_ptr,
		error_text);

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static int NEW_001_ADF_InsertHText(control_ptr, entry_ptr, current_para_ptr,
	next_para_ptr, alloc_count, error_text)
ADF_CONTROL      *control_ptr;
const ADF_ENTRY  *entry_ptr;
ADF_PARA_TEXT   **current_para_ptr;
ADF_PARA_TEXT    *next_para_ptr;
unsigned int     *alloc_count;
char             *error_text;
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

	if ((found_count = NEW_001_ADF_FindHTextPointers(control_ptr,
		entry_ptr, next_para_ptr)) > 0) {
		tmp_para_line       = *next_para_ptr;
		para_htext_ptr_list = control_ptr__in_para_htext_ptr_list;
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
			if (((tmp_ptr_1 != next_para_ptr->ptr) &&
				(!isspace(*(tmp_ptr_1 - 1)))) ||
				((next_para_ptr->length != htext_ptr->htext_length) &&
				((!isspace(*tmp_ptr_2)) && (*tmp_ptr_2)))) {
				count_1 += htext_ptr->htext_length;
				continue;
			}
			if ((return_code = ADF_AllocInParaLineList(control_ptr,
				*alloc_count + 4, error_text)) != ADF_SUCCESS)
				goto EXIT_FUNCTION;
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
static unsigned int NEW_001_ADF_FindHTextPointers(control_ptr, entry_ptr,
	para_ptr)
ADF_CONTROL         *control_ptr;
const ADF_ENTRY     *entry_ptr;
const ADF_PARA_TEXT *para_ptr;
{
	unsigned int  found_count = 0;
	unsigned int  found_index;
   unsigned int  count_1;
	ADF_HTEXT    *htext_ptr;
	char         *tmp_ptr;

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Initialize the list of pointers to hyper-text elements for		*/
	/*	each character position in the paragraph . . .							*/
	/*	*****************************************************************	*/
	for (count_1 = 0; count_1 < para_ptr->length; count_1++)
		control_ptr__in_para_htext_ptr_list[count_1] = NULL;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		For each element in the hyper-text list, try to locate the		*/
	/*	hyper-text string in the paragraph.											*/
	/*																							*/
	/*		If the character position at which a particular hyper-text		*/
	/*	string is not one at which a previous hyper-text string has been	*/
	/*	found, (indicated by a 'NULL' value) set the hyper-text element	*/
	/*	pointer for that character position to the pointer to the hyper-	*/
	/*	text element in question.														*/
	/*																							*/
	/*		If a previous hyper-text string has been found at the character*/
	/*	position, replace the pointer to the hyper-text element if the		*/
	/*	hyper-text element is longer. This replaces any shorter hyper-		*/
	/*	text sub-strings.																	*/
	/*	*****************************************************************	*/
	for (count_1 = 0; count_1 < control_ptr->in_htext_count; count_1++) {
		htext_ptr = control_ptr->in_htext_list + count_1;
		if (para_ptr->length < htext_ptr->htext_length)
			continue;
		else if ((entry_ptr->file_index == htext_ptr->file_index) &&
			(entry_ptr->entry_index == htext_ptr->entry_index))
			continue;
		else if (control_ptr->htext_boyer_moore_data == NULL) {
			if ((tmp_ptr = memmem(para_ptr->length, para_ptr->ptr,
				htext_ptr->htext_length, htext_ptr->hyper_text)) == NULL)
				continue;
		}
		else if ((tmp_ptr = BoyerMoore_mem_search_basic(para_ptr->length,
			para_ptr->ptr, htext_ptr->htext_length, htext_ptr->hyper_text,
			control_ptr->htext_boyer_moore_data + ((UCHAR_MAX + 1) * count_1),
			NULL)) == NULL)
			continue;
		found_index = ((unsigned int) (tmp_ptr - para_ptr->ptr));
		if (control_ptr__in_para_htext_ptr_list[found_index] == NULL) {
			control_ptr__in_para_htext_ptr_list[found_index] = htext_ptr;
			found_count++;
		}
		else if (htext_ptr->htext_length >
			control_ptr__in_para_htext_ptr_list[found_index]->htext_length)
			control_ptr__in_para_htext_ptr_list[found_index] = htext_ptr;
	}
	/*	*****************************************************************	*/

	return(found_count);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static int NEW_001_ADF_AllocInParaHTextList(control_ptr, para_ptr, error_text)
ADF_CONTROL         *control_ptr;
const ADF_PARA_DATA *para_ptr;
char                *error_text;
{
	int             return_code = ADF_SUCCESS;
	unsigned int   alloc_count;
	ADF_HTEXT    **tmp_htext_list;

	alloc_count  = strlen(para_ptr->text_ptr) + 1;
	alloc_count += (alloc_count % 128) ? (128 - (alloc_count % 128)) : 0;

	if (alloc_count > control_ptr__in_para_htext_ptr_count) {
		tmp_htext_list = ((ADF_HTEXT **)
			((control_ptr__in_para_htext_ptr_list == NULL) ?
			malloc(alloc_count * sizeof(ADF_HTEXT *)) :
			realloc(control_ptr__in_para_htext_ptr_list,
			alloc_count * sizeof(ADF_HTEXT *))));
		if (tmp_htext_list != NULL) {
			control_ptr__in_para_htext_ptr_count = alloc_count;
			control_ptr__in_para_htext_ptr_list  = tmp_htext_list;
		}
		else {
			GEN_AllocMsgList(alloc_count, sizeof(ADF_HTEXT *), error_text,
				"Unable to expand the area data line hyper-text pointers");
			return_code = ADF_MEMORY_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int NEW_002_ADF_FixParagraph(control_ptr, entry_ptr, para_ptr, cformat_flags,
	error_text)
ADF_CONTROL     *control_ptr;
const ADF_ENTRY *entry_ptr;
ADF_PARA_DATA   *para_ptr;
unsigned int     cformat_flags;
char            *error_text;
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
	else if ((return_code = NEW_002_ADF_AllocInParaHTextList(control_ptr,
		para_ptr, error_text)) != ADF_SUCCESS)
		goto EXIT_FUNCTION;

	tmp_ptr_1                            = para_ptr->text_ptr;
	control_ptr->current_para_line_count = 0;
	current_ptr                          = control_ptr->in_para_line_list;

	while (*tmp_ptr_1) {
		if (*tmp_ptr_1 == ADF_CFORMAT_MARKER_CHAR) {
			tmp_char          = toupper(*(tmp_ptr_1 + 1));
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
				NEW_002_ADF_InsertHText(control_ptr, entry_ptr,
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
				return_code = NEW_002_ADF_InsertHText(control_ptr, entry_ptr,
					&current_ptr, &tmp_para_line, &alloc_count, error_text);
			break;
		}
	}

	return_code = ADF_AllocOutParaBuffer(control_ptr, para_ptr->text_ptr,
		error_text);

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static int NEW_002_ADF_InsertHText(control_ptr, entry_ptr, current_para_ptr,
	next_para_ptr, alloc_count, error_text)
ADF_CONTROL      *control_ptr;
const ADF_ENTRY  *entry_ptr;
ADF_PARA_TEXT   **current_para_ptr;
ADF_PARA_TEXT    *next_para_ptr;
unsigned int     *alloc_count;
char             *error_text;
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

	if ((found_count = NEW_002_ADF_FindHTextPointers(control_ptr,
		entry_ptr, next_para_ptr)) > 0) {
		tmp_para_line       = *next_para_ptr;
		para_htext_ptr_list = control_ptr__in_para_htext_ptr_list;
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
			if (((tmp_ptr_1 != next_para_ptr->ptr) &&
				(!isspace(*(tmp_ptr_1 - 1)))) ||
				((next_para_ptr->length != htext_ptr->htext_length) &&
				((!isspace(*tmp_ptr_2)) && (*tmp_ptr_2)))) {
				count_1 += htext_ptr->htext_length;
				continue;
			}
			if ((return_code = ADF_AllocInParaLineList(control_ptr,
				*alloc_count + 4, error_text)) != ADF_SUCCESS)
				goto EXIT_FUNCTION;
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
static unsigned int NEW_002_ADF_FindHTextPointers(control_ptr, entry_ptr,
	para_ptr)
ADF_CONTROL         *control_ptr;
const ADF_ENTRY     *entry_ptr;
const ADF_PARA_TEXT *para_ptr;
{
	unsigned int     found_count = 0;
	unsigned int     count_1;
	unsigned int     count_2;
	ADF_HTEXT       *htext_ptr;
	ADF_HTEXT_MATCH *lookup_ptr;

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Initialize the list of pointers to hyper-text elements for		*/
	/*	each character position in the paragraph . . .							*/
	/*	*****************************************************************	*/
	for (count_1 = 0; count_1 < para_ptr->length; count_1++)
		control_ptr__in_para_htext_ptr_list[count_1] = NULL;
	/*	*****************************************************************	*/

#if 0
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		For each element in the hyper-text list, try to locate the		*/
	/*	hyper-text string in the paragraph.											*/
	/*																							*/
	/*		If the character position at which a particular hyper-text		*/
	/*	string is not one at which a previous hyper-text string has been	*/
	/*	found, (indicated by a 'NULL' value) set the hyper-text element	*/
	/*	pointer for that character position to the pointer to the hyper-	*/
	/*	text element in question.														*/
	/*																							*/
	/*		If a previous hyper-text string has been found at the character*/
	/*	position, replace the pointer to the hyper-text element if the		*/
	/*	hyper-text element is longer. This replaces any shorter hyper-		*/
	/*	text sub-strings.																	*/
	/*	*****************************************************************	*/
	for (count_1 = 0; count_1 < control_ptr->in_htext_count; count_1++) {
		htext_ptr = control_ptr->in_htext_list + count_1;
		if (para_ptr->length < htext_ptr->htext_length)
			continue;
		else if ((entry_ptr->file_index == htext_ptr->file_index) &&
			(entry_ptr->entry_index == htext_ptr->entry_index))
			continue;
		else if (control_ptr->htext_boyer_moore_data == NULL) {
			if ((tmp_ptr = memmem(para_ptr->length, para_ptr->ptr,
				htext_ptr->htext_length, htext_ptr->hyper_text)) == NULL)
				continue;
		}
		else if ((tmp_ptr = BoyerMoore_mem_search_basic(para_ptr->length,
			para_ptr->ptr, htext_ptr->htext_length, htext_ptr->hyper_text,
			control_ptr->htext_boyer_moore_data + ((UCHAR_MAX + 1) * count_1),
			NULL)) == NULL)
			continue;
		found_index = ((unsigned int) (tmp_ptr - para_ptr->ptr));
		if (control_ptr__in_para_htext_ptr_list[found_index] == NULL) {
			control_ptr__in_para_htext_ptr_list[found_index] = htext_ptr;
			found_count++;
		}
		else if (htext_ptr->htext_length >
			control_ptr__in_para_htext_ptr_list[found_index]->htext_length)
			control_ptr__in_para_htext_ptr_list[found_index] = htext_ptr;
	}
	/*	*****************************************************************	*/
#endif /* #if 0 */

	for (count_1 = 0; count_1 < para_ptr->length; count_1++) {
		lookup_ptr = control_ptr__in_htext_lookup_list +
			((unsigned int) ((unsigned char) para_ptr->ptr[count_1]));
		for (count_2 = 0; count_2 < lookup_ptr->count; count_2++) {
			htext_ptr = lookup_ptr->list + count_2;
			if ((para_ptr->length - count_1) < htext_ptr->htext_length)
				continue;
			else if ((entry_ptr->file_index == htext_ptr->file_index) &&
				(entry_ptr->entry_index == htext_ptr->entry_index))
				continue;
			else if ((htext_ptr->htext_length == 1) ||
				(!memcmp(htext_ptr->hyper_text, para_ptr->ptr + count_1,
				htext_ptr->htext_length))) {
				if (control_ptr__in_para_htext_ptr_list[count_1] == NULL) {
					control_ptr__in_para_htext_ptr_list[count_1] = htext_ptr;
					found_count++;
				}
				else if (htext_ptr->htext_length >
					control_ptr__in_para_htext_ptr_list[count_1]->htext_length)
					control_ptr__in_para_htext_ptr_list[count_1] = htext_ptr;
			}
		}
	}

	return(found_count);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static int NEW_002_ADF_AllocInParaHTextList(control_ptr, para_ptr, error_text)
ADF_CONTROL         *control_ptr;
const ADF_PARA_DATA *para_ptr;
char                *error_text;
{
	int             return_code = ADF_SUCCESS;
	unsigned int   alloc_count;
	ADF_HTEXT    **tmp_htext_list;

	alloc_count  = strlen(para_ptr->text_ptr) + 1;
	alloc_count += (alloc_count % 128) ? (128 - (alloc_count % 128)) : 0;

	if (alloc_count > control_ptr__in_para_htext_ptr_count) {
		tmp_htext_list = ((ADF_HTEXT **)
			((control_ptr__in_para_htext_ptr_list == NULL) ?
			malloc(alloc_count * sizeof(ADF_HTEXT *)) :
			realloc(control_ptr__in_para_htext_ptr_list,
			alloc_count * sizeof(ADF_HTEXT *))));
		if (tmp_htext_list != NULL) {
			control_ptr__in_para_htext_ptr_count = alloc_count;
			control_ptr__in_para_htext_ptr_list  = tmp_htext_list;
		}
		else {
			GEN_AllocMsgList(alloc_count, sizeof(ADF_HTEXT *), error_text,
				"Unable to expand the area data line hyper-text pointers");
			return_code = ADF_MEMORY_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*
	Assumes 'control_ptr->in_htext_list' is sorted in ascending order.
*/
static void NEW_002_ADF_MakeHTextMatchList(control_ptr)
ADF_CONTROL *control_ptr;
{
	unsigned int  count_1;
	ADF_HTEXT    *htext_ptr;

	for (count_1 = 0; count_1 <= UCHAR_MAX; count_1++) {
		control_ptr__in_htext_lookup_list[count_1].count = 0;
		control_ptr__in_htext_lookup_list[count_1].list  = NULL;
	}

	for (count_1 = 0; count_1 < control_ptr->in_htext_count; count_1++) {
		htext_ptr = control_ptr->in_htext_list + count_1;
		if (control_ptr__in_htext_lookup_list
			[((unsigned char) *htext_ptr->hyper_text)].count == NULL)
			control_ptr__in_htext_lookup_list
				[((unsigned char) *htext_ptr->hyper_text)].list = htext_ptr;
		control_ptr__in_htext_lookup_list
			[((unsigned char) *htext_ptr->hyper_text)].count++;
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int NEW_003_ADF_FixParagraph(control_ptr, entry_ptr, para_ptr, cformat_flags,
	error_text)
ADF_CONTROL     *control_ptr;
const ADF_ENTRY *entry_ptr;
ADF_PARA_DATA   *para_ptr;
unsigned int     cformat_flags;
char            *error_text;
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
	else if ((return_code = NEW_003_ADF_AllocInParaHTextList(control_ptr,
		para_ptr, error_text)) != ADF_SUCCESS)
		goto EXIT_FUNCTION;

	tmp_ptr_1                            = para_ptr->text_ptr;
	control_ptr->current_para_line_count = 0;
	current_ptr                          = control_ptr->in_para_line_list;

	while (*tmp_ptr_1) {
		if (*tmp_ptr_1 == ADF_CFORMAT_MARKER_CHAR) {
			tmp_char          = toupper(*(tmp_ptr_1 + 1));
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
				NEW_003_ADF_InsertHText(control_ptr, entry_ptr,
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
				return_code = NEW_003_ADF_InsertHText(control_ptr, entry_ptr,
					&current_ptr, &tmp_para_line, &alloc_count, error_text);
			break;
		}
	}

	return_code = ADF_AllocOutParaBuffer(control_ptr, para_ptr->text_ptr,
		error_text);

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static int NEW_003_ADF_InsertHText(control_ptr, entry_ptr, current_para_ptr,
	next_para_ptr, alloc_count, error_text)
ADF_CONTROL      *control_ptr;
const ADF_ENTRY  *entry_ptr;
ADF_PARA_TEXT   **current_para_ptr;
ADF_PARA_TEXT    *next_para_ptr;
unsigned int     *alloc_count;
char             *error_text;
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

	if ((found_count = NEW_003_ADF_FindHTextPointers(control_ptr,
		entry_ptr, next_para_ptr)) > 0) {
		tmp_para_line       = *next_para_ptr;
		para_htext_ptr_list = control_ptr__in_para_htext_ptr_list;
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
			if ((return_code = ADF_AllocInParaLineList(control_ptr,
				*alloc_count + 4, error_text)) != ADF_SUCCESS)
				goto EXIT_FUNCTION;
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
static unsigned int NEW_003_ADF_FindHTextPointers(control_ptr, entry_ptr,
	para_ptr)
ADF_CONTROL         *control_ptr;
const ADF_ENTRY     *entry_ptr;
const ADF_PARA_TEXT *para_ptr;
{
	unsigned int     found_count = 0;
	unsigned int     count_1;
	unsigned int     count_2;
	unsigned int     increment_count;
	ADF_HTEXT       *htext_ptr;
	ADF_HTEXT_MATCH *lookup_ptr;
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
		control_ptr__in_para_htext_ptr_list[count_1] = NULL;
	/*	*****************************************************************	*/

	for (count_1 = 0; count_1 < para_ptr->length; ) {
		lookup_ptr      = control_ptr__in_htext_lookup_list +
			((unsigned int) ((unsigned char) para_ptr->ptr[count_1]));
		htext_ptr       = lookup_ptr->list + lookup_ptr->count - 1;
		increment_count = 1;
		for (count_2 = lookup_ptr->count; count_2; count_2--, htext_ptr--) {
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
					isspace(*(tmp_ptr_1 - 1))) &&
					(((para_ptr->length - count_1) == htext_ptr->htext_length) ||
					(isspace(*tmp_ptr_2) || (!(*tmp_ptr_2))))) {
					control_ptr__in_para_htext_ptr_list[count_1] = htext_ptr;
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
static int NEW_003_ADF_AllocInParaHTextList(control_ptr, para_ptr, error_text)
ADF_CONTROL         *control_ptr;
const ADF_PARA_DATA *para_ptr;
char                *error_text;
{
	int             return_code = ADF_SUCCESS;
	unsigned int   alloc_count;
	ADF_HTEXT    **tmp_htext_list;

	alloc_count  = strlen(para_ptr->text_ptr) + 1;
	alloc_count += (alloc_count % 128) ? (128 - (alloc_count % 128)) : 0;

	if (alloc_count > control_ptr__in_para_htext_ptr_count) {
		tmp_htext_list = ((ADF_HTEXT **)
			((control_ptr__in_para_htext_ptr_list == NULL) ?
			malloc(alloc_count * sizeof(ADF_HTEXT *)) :
			realloc(control_ptr__in_para_htext_ptr_list,
			alloc_count * sizeof(ADF_HTEXT *))));
		if (tmp_htext_list != NULL) {
			control_ptr__in_para_htext_ptr_count = alloc_count;
			control_ptr__in_para_htext_ptr_list  = tmp_htext_list;
		}
		else {
			GEN_AllocMsgList(alloc_count, sizeof(ADF_HTEXT *), error_text,
				"Unable to expand the area data line hyper-text pointers");
			return_code = ADF_MEMORY_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*
	Assumes 'control_ptr->in_htext_list' is sorted in ascending order.
*/
static void NEW_003_ADF_MakeHTextMatchList(control_ptr)
ADF_CONTROL *control_ptr;
{
	unsigned int  count_1;
	ADF_HTEXT    *htext_ptr;

	for (count_1 = 0; count_1 <= UCHAR_MAX; count_1++) {
		control_ptr__in_htext_lookup_list[count_1].count = 0;
		control_ptr__in_htext_lookup_list[count_1].list  = NULL;
	}

	for (count_1 = 0; count_1 < control_ptr->in_htext_count; count_1++) {
		htext_ptr = control_ptr->in_htext_list + count_1;
		if (control_ptr__in_htext_lookup_list
			[((unsigned char) *htext_ptr->hyper_text)].count == NULL)
			control_ptr__in_htext_lookup_list
				[((unsigned char) *htext_ptr->hyper_text)].list = htext_ptr;
		control_ptr__in_htext_lookup_list
			[((unsigned char) *htext_ptr->hyper_text)].count++;
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static int ADF_AllocOutParaBuffer(control_ptr, para_text, error_text)
ADF_CONTROL *control_ptr;
const char  *para_text;
char        *error_text;
{
	int           return_code = ADF_SUCCESS;
	unsigned int  alloc_length;
	char         *tmp_ptr;

	alloc_length = (strlen(para_text) * ADF_BASIC_CHAR_MULTIPLIER) +
		(control_ptr->current_para_line_count * ADF_CFORMAT_MULTIPLIER);

	if (alloc_length > control_ptr->out_para_buffer_length) {
		alloc_length = (alloc_length < 2048) ? 2048 : alloc_length;
		tmp_ptr      = (!control_ptr->out_para_buffer_length) ?
			malloc(alloc_length * sizeof(char)) :
			realloc(control_ptr->out_para_buffer, alloc_length * sizeof(char));
		if (tmp_ptr != NULL) {
			control_ptr->out_para_buffer_length = alloc_length;
			control_ptr->out_para_buffer        = tmp_ptr;
		}
		else {
			GEN_AllocMsgItem(alloc_length, error_text,
				"Unable to expand the output paragraph data buffer");
			return_code = ADF_MEMORY_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int NEW_004_ADF_FixParagraph(control_ptr, entry_ptr, para_ptr, cformat_flags,
	error_text)
ADF_CONTROL     *control_ptr;
const ADF_ENTRY *entry_ptr;
ADF_PARA_DATA   *para_ptr;
unsigned int     cformat_flags;
char            *error_text;
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

	if ((return_code = NEW_004_ADF_AllocInParaLineList(control_ptr, alloc_count,
		error_text)) != ADF_SUCCESS)
		goto EXIT_FUNCTION;

	tmp_ptr_1                            = para_ptr->text_ptr;
	control_ptr->current_para_line_count = 0;
	current_ptr                          = control_ptr->in_para_line_list;

	while (*tmp_ptr_1) {
		if (*tmp_ptr_1 == ADF_CFORMAT_MARKER_CHAR) {
			tmp_char          = toupper(*(tmp_ptr_1 + 1));
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
				NEW_004_ADF_InsertHText(control_ptr, entry_ptr,
				control_ptr->in_htext_count, &current_ptr, &tmp_para_line,
				&alloc_count, error_text)) != ADF_SUCCESS))
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
				return_code = NEW_004_ADF_InsertHText(control_ptr, entry_ptr,
					control_ptr->in_htext_count, &current_ptr, &tmp_para_line,
					&alloc_count, error_text);
			break;
		}
	}

	return_code = ADF_AllocOutParaBuffer(control_ptr, para_ptr->text_ptr,
		error_text);

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static int NEW_004_ADF_InsertHText(control_ptr, entry_ptr, htext_index,
	current_para_ptr, next_para_ptr, alloc_count, error_text)
ADF_CONTROL      *control_ptr;
const ADF_ENTRY  *entry_ptr;
unsigned int      htext_index;
ADF_PARA_TEXT   **current_para_ptr;
ADF_PARA_TEXT    *next_para_ptr;
unsigned int     *alloc_count;
char             *error_text;
{
	int            return_code = ADF_SUCCESS;
   unsigned int   count_1;
	ADF_HTEXT     *htext_ptr;
	unsigned int  *boyer_moore_ptr;
	unsigned int   string_length;
	char          *string_ptr;
	char          *tmp_ptr_1;
	char          *tmp_ptr_2;
	ADF_PARA_TEXT  tmp_para_line;

	for (count_1 = htext_index; count_1; ) {
		htext_ptr = control_ptr->in_htext_list + --count_1;
		if ((next_para_ptr->length < htext_ptr->htext_length) ||
			((entry_ptr->file_index == htext_ptr->file_index) &&
			(entry_ptr->entry_index == htext_ptr->entry_index)))
			continue;
		string_length   = next_para_ptr->length;
		string_ptr      = next_para_ptr->ptr;
		boyer_moore_ptr = control_ptr->htext_boyer_moore_data +
			((UCHAR_MAX + 1) * count_1);
		while (string_length >= htext_ptr->htext_length) {
			if (control_ptr->htext_boyer_moore_data == NULL) {
				if ((tmp_ptr_1 = memmem(string_length, string_ptr,
					htext_ptr->htext_length, htext_ptr->hyper_text)) == NULL)
					break;
			}
			else if ((tmp_ptr_1 = BoyerMoore_mem_search_basic(string_length,
				string_ptr, htext_ptr->htext_length, htext_ptr->hyper_text,
				boyer_moore_ptr, NULL)) == NULL)
				break;
			tmp_ptr_2 = tmp_ptr_1 + htext_ptr->htext_length;
			if (((tmp_ptr_1 == next_para_ptr->ptr) ||
				isspace(*(tmp_ptr_1 - 1))) &&
				((string_length == htext_ptr->htext_length) ||
				(isspace(*tmp_ptr_2) || (!(*tmp_ptr_2))))) {
				if ((return_code = NEW_004_ADF_AllocInParaLineList(control_ptr,
					*alloc_count + 4, error_text)) != ADF_SUCCESS)
					goto EXIT_FUNCTION;
				if (tmp_ptr_1 != string_ptr) {
					tmp_para_line.cformat_type  = ADF_CFORMAT_CHAR_NONE;
					tmp_para_line.htext_index   = 0;
					tmp_para_line.length        =
						((unsigned int) (tmp_ptr_1 - string_ptr));
					tmp_para_line.ptr           = string_ptr;
					next_para_ptr->length      -= tmp_para_line.length;
					next_para_ptr->ptr         += tmp_para_line.length;
					if (!count_1) {
						**current_para_ptr = tmp_para_line;
						(*current_para_ptr)++;
						control_ptr->current_para_line_count++;
						(*alloc_count)++;
					}
					else if ((return_code = NEW_004_ADF_InsertHText(control_ptr, entry_ptr,
						count_1, current_para_ptr, &tmp_para_line, alloc_count,
						error_text)) != ADF_SUCCESS)
						break;
				}
				(*current_para_ptr)->cformat_type  = ADF_CFORMAT_CHAR_HTEXT_1;
				(*current_para_ptr)->htext_index   = count_1;
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
				string_length                      = next_para_ptr->length;
				string_ptr                         = next_para_ptr->ptr;
			}
			else {
				string_length -= htext_ptr->htext_length;
				string_ptr    += htext_ptr->htext_length;
			}
		}
		if (!next_para_ptr->length)
			goto EXIT_FUNCTION;
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
static int NEW_004_ADF_AllocInParaLineList(control_ptr, alloc_count, error_text)
ADF_CONTROL  *control_ptr;
unsigned int  alloc_count;
char         *error_text;
{
	int               return_code = ADF_SUCCESS;
	ADF_PARA_TEXT    *tmp_p_text;
	ADF_HTEXT_LOOKUP *tmp_h_key;

	alloc_count += (alloc_count % 128) ? (128 - (alloc_count % 128)) : 0;

	if (alloc_count > control_ptr->in_para_line_count) {
		tmp_p_text = ((ADF_PARA_TEXT *) ((!control_ptr->in_para_line_count) ?
			malloc(alloc_count * sizeof(ADF_PARA_TEXT)) :
			realloc(control_ptr->in_para_line_list,
			alloc_count * sizeof(ADF_PARA_TEXT))));
		if (tmp_p_text == NULL) {
			GEN_AllocMsgList(alloc_count, sizeof(ADF_PARA_TEXT), error_text,
				"Unable to expand the area data line list");
			return_code = ADF_MEMORY_FAILURE;
		}
		else {
			control_ptr->in_para_line_count = alloc_count;
			control_ptr->in_para_line_list  = ((ADF_PARA_TEXT *) tmp_p_text);
			tmp_h_key = ((ADF_HTEXT_LOOKUP *) ((control_ptr__in_para_hash_key ==
				NULL) ? malloc(alloc_count * sizeof(ADF_HTEXT_LOOKUP)) :
				realloc(control_ptr__in_para_hash_key,
				alloc_count * sizeof(ADF_HTEXT_LOOKUP))));
			if (tmp_h_key == NULL) {
				GEN_AllocMsgList(alloc_count, sizeof(ADF_HTEXT_LOOKUP),
					error_text,
					"Unable to expand the area data line hash key list");
				return_code = ADF_MEMORY_FAILURE;
			}
			else
				control_ptr__in_para_hash_key = tmp_h_key;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int ADF_InitHTextHashList(control_ptr, error_text)
ADF_CONTROL *control_ptr;
char        *error_text;
{
	int          return_code = ADF_SUCCESS;
	unsigned int count_1;

	if (control_ptr__in_htext_hash_key_list != NULL) {
		free(control_ptr__in_htext_hash_key_list);
		control_ptr__in_htext_hash_key_list = NULL;
	}

	if (control_ptr->in_htext_count) {
		if ((control_ptr__in_htext_hash_key_list = ((unsigned long *)
			malloc(control_ptr->in_htext_count * sizeof(unsigned long)))) ==
			NULL) {
			GEN_AllocMsgList(control_ptr->in_htext_count, sizeof(unsigned long),
				error_text, "Unable to create the hyper-text hash list");
			return_code = ADF_MEMORY_FAILURE;
		}
		else {
			for (count_1 = 0; count_1 < control_ptr->in_htext_count; count_1++)
				control_ptr__in_htext_hash_key_list[count_1] =
					ADF_CalcHTextHashKey(control_ptr->in_htext_list[count_1].
					htext_length, control_ptr->in_htext_list[count_1].hyper_text);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void ADF_InitParaHashList(para_ptr)
const ADF_PARA_TEXT *para_ptr;
{
	unsigned int count_1;

	for (count_1 = 0; count_1 < para_ptr->length; count_1++) {
		control_ptr__in_para_hash_key[count_1].hash_key =
			ADF_CalcHTextHashKey(para_ptr->length - count_1,
			para_ptr->ptr + count_1);
		control_ptr__in_para_hash_key[count_1].ptr      =
			para_ptr->ptr + count_1;
		control_ptr__in_para_hash_key[count_1].length   =
			para_ptr->length - count_1;
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
unsigned long ADF_CalcHTextHashKey(in_length, in_ptr)
unsigned int  in_length;
const char   *in_ptr;
{
	unsigned long  tmp_u_long     = 0L;
	char          *tmp_u_long_ptr = ((char *) &tmp_u_long);

	in_length = (in_length <= 4) ? in_length : 4;

	while (in_length && *in_ptr) {
		*tmp_u_long_ptr++ = *in_ptr++;
		in_length--;
	}

	return(tmp_u_long);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static char *ADF_FindHTextInPara(control_ptr, htext_index, para_ptr,
	para_hash_list)
const ADF_CONTROL      *control_ptr;
unsigned int            htext_index;
const ADF_PARA_TEXT    *para_ptr;
const ADF_HTEXT_LOOKUP *para_hash_list;
{
	unsigned int  count_1;
	unsigned int  count_2;
	char         *found_ptr = NULL;

	for (count_1 = htext_index; count_1; ) {
		for (count_2 = 0; count_2 < para_ptr->length; count_2++) {
			if ((para_hash_list[count_2].hash_key ==
				control_ptr__in_htext_hash_key_list[count_1]) &&
				(control_ptr->in_htext_list[count_1].htext_length <=
				(para_ptr->length - count_2)) &&
				(!strcmp(para_ptr->ptr + count_2,
				control_ptr->in_htext_list[count_1].hyper_text))) {
				found_ptr = ((char *) para_ptr->ptr) + count_2;
				goto EXIT_FUNCTION;
			}
		}
	}

EXIT_FUNCTION:

	return(found_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int ADF_SCMP_ParaTextHashItem(control_ptr, ptr_1, ptr_2, data_length)
void                   *control_ptr;
const ADF_HTEXT_LOOKUP *ptr_1;
const ADF_HTEXT_LOOKUP *ptr_2;
size_t                  data_length;
{
	return((ptr_1->hash_key > ptr_2->hash_key) ? 1 :
		(ptr_1->hash_key < ptr_2->hash_key) ? -1 : 0);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <memory.h>

#include <genfuncs.h>

static const unsigned int TestCFormatFlags =
	(ADF_CFORMAT_TYPE_ALL ^ (ADF_CFORMAT_TYPE_HTEXT | ADF_CFORMAT_TYPE_EINDEX));

#ifdef __MSDOS__
extern unsigned int _stklen = 20000;
#endif /* __MSDOS__ */

#ifndef NARGS
int main(int argc, char **argv);
#else
int main();
#endif /* #ifndef NARGS */

#ifndef NARGS
static int TEST_DoParaOutputControl(ADF_CONTROL *control_ptr,
	char *error_text);
static int TEST_DoParaOutput(ADF_CONTROL *control_ptr,
	int (*fixpara_func)(ADF_CONTROL *, const ADF_ENTRY *, ADF_PARA_DATA *,
	unsigned int, char *), FILE *file_ptr, char *error_text);
static int TEST_DoParaCompare(ADF_CONTROL *control_ptr, char *error_text);
static int TEST_DoFixPara(ADF_CONTROL *control_ptr, ADF_ENTRY *entry_ptr,
	ADF_PARA_DATA *para_ptr, unsigned int cformat_flags,
	int (*fixpara_func)(ADF_CONTROL *, const ADF_ENTRY *, ADF_PARA_DATA *,
	unsigned int, char *), char *error_text);
#else
static int TEST_DoParaOutputControl();
static int TEST_DoParaOutput();
static int TEST_DoParaCompare();
static int TEST_DoFixPara();
#endif /* #ifndef NARGS */

#ifndef NARGS
static int          (*TEST_FixParaFuncList[])(ADF_CONTROL *,
	const ADF_ENTRY *, ADF_PARA_DATA *, unsigned int, char *)   = {
#else
static int          (*TEST_FixParaFuncList[])()          = {
#endif /* #ifndef NARGS */
/*
	ADF_FixParagraph,
	NEW_001_ADF_FixParagraph,
	NEW_002_ADF_FixParagraph,
*/
	NEW_003_ADF_FixParagraph
};
static const unsigned int   TEST_FixParaFuncCount =
	sizeof(TEST_FixParaFuncList) / sizeof(TEST_FixParaFuncList[0]);

static int TEST_OutputFlag = ADF_FALSE;

int main(argc, argv)
int    argc;
char **argv;
{
	int            return_code = ADF_SUCCESS;
	unsigned int   count_1;
	ADF_CONTROL    control_data;
	char           error_text[ADF_MAX_ERROR_TEXT];

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
			"USAGE:\n   %s %s <adf-db-file-name> [<adf-db-file-name>...]\n",
			argv[0], "[-OUTPUT]");
		return_code = ADF_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}

	for (count_1 = 1; count_1 < argc; count_1++) {
		if (!stricmp(argv[count_1], "-OUTPUT")) {
			TEST_OutputFlag = ADF_TRUE;
			continue;
		}
		fprintf(stderr, "File: %s\n", argv[count_1]);
		if ((return_code = ADF_OpenADFFileIn(&control_data, argv[count_1],
			error_text)) != ADF_SUCCESS) {
			if (return_code != ADF_PARSE_FAILURE)
				goto EXIT_FUNCTION;
			fprintf(stderr, "%s\n", error_text);
			return_code = ADF_SUCCESS;
		}
	}

	if ((return_code = ADF_FinalizeEntries(&control_data, error_text)) !=
		ADF_SUCCESS)
		goto EXIT_FUNCTION;

	NEW_002_ADF_MakeHTextMatchList(&control_data);

	if ((return_code = ADF_InitHTextHashList(&control_data, error_text)) !=
		ADF_SUCCESS)
		goto EXIT_FUNCTION;

	fprintf(stderr, "Boyer-Moore Searching: %s\n\n",
		(control_data.htext_boyer_moore_data != NULL) ? "ON" : "OFF");

	if ((TEST_OutputFlag == ADF_TRUE) &&
		((return_code = TEST_DoParaOutputControl(&control_data, error_text)) !=
		ADF_SUCCESS))
		goto EXIT_FUNCTION;

#if 0
	if ((return_code = TEST_DoParaCompare(&control_data, error_text)) !=
		ADF_SUCCESS)
		goto EXIT_FUNCTION;
#endif /* #if 0 */

EXIT_FUNCTION:

	fprintf(stderr, "\n\n");

	ADF_FREE_Control(&control_data);

	if (return_code != ADF_SUCCESS)
		fprintf(stderr, "ERROR: %s\n", error_text);

	return(return_code);
}

static int TEST_DoParaOutputControl(control_ptr, error_text)
ADF_CONTROL *control_ptr;
char        *error_text;
{
	int             return_code = ADF_SUCCESS;
	FILE           *file_ptr;
	unsigned int    count_1;
	struct timeval  start_time;
	struct timeval  end_time;
	char            buffer[100];

	for (count_1 = 0; count_1 < TEST_FixParaFuncCount; count_1++) {
		fprintf(stderr, "Test version %u of 'ADF_FixParagraph()' [", count_1);
		sprintf(buffer, "FIXPTEST.%03u", count_1);
		if ((file_ptr = fopen(buffer, "w")) == NULL) {
			sprintf(error_text,
				"Unable to open output test file '%-.500s' for writing: ",
				buffer);
			ADF_GetLastErrorString(error_text);
			return_code = ADF_SYSTEM_FAILURE;
			break;
		}
		gettimeofday(&start_time, NULL);
		return_code = TEST_DoParaOutput(control_ptr,
			TEST_FixParaFuncList[count_1], file_ptr, error_text);
		gettimeofday(&end_time, NULL);
		fclose(file_ptr);
		if (return_code != ADF_SUCCESS)
			break;
		fprintf(stderr, "]\n>>> Total Time For Version %3u: %10.6f\n",
			count_1, (((double) GEN_GET_TIMEVAL_USECS(&end_time)) -
			((double) GEN_GET_TIMEVAL_USECS(&start_time))) / 1000000.0);
	}

	return(return_code);
}

static int TEST_DoParaOutput(control_ptr, fixpara_func, file_ptr, error_text)
ADF_CONTROL   *control_ptr;
#ifndef NARGS
int          (*fixpara_func)(ADF_CONTROL *, const ADF_ENTRY *,
	ADF_PARA_DATA *, unsigned int, char *);
#else
int          (*fixpara_func)();
#endif /* #ifndef NARGS */
FILE          *file_ptr;
char          *error_text;
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
	ADF_ENTRY_DATA   entry_data_list[ADF_AREA_COUNT];
	ADF_PARA_DATA   *para_ptr;
	char             area_name[ADF_AREA_NAME_LENGTH + 1];
	char            *tmp_ptr;
	char             tmp_buffer[1024];

	for (count_1 = 0; count_1 < control_ptr->in_entry_order_count; count_1++) {
		if ((return_code = ADF_GetEntry(control_ptr,
			control_ptr->in_entry_order_list[count_1], entry_data_list,
			error_text)) != ADF_SUCCESS)
			goto EXIT_FUNCTION;
		STR_EMIT_CharLine('=', 78, NULL, file_ptr);
		for (count_2 = 0; count_2 < ADF_AREA_COUNT; count_2++) {
			if ((ADF_AreaNameList[count_2].output_flag != ADF_TRUE) ||
				(!entry_data_list[count_2].para_count))
				continue;
			fprintf(file_ptr, "%s:\n",
				initcaps(ADF_GetAreaName(count_2, area_name)));
			cformat_flags = TestCFormatFlags |
				((ADF_AreaNameList[count_2].htext_flag == ADF_TRUE) ?
				ADF_CFORMAT_TYPE_HTEXT : ADF_CFORMAT_TYPE_NONE);
			for (count_3 = 0;
				count_3 < entry_data_list[count_2].para_count; count_3++) {
				para_ptr = entry_data_list[count_2].para_list + count_3;
				if ((return_code = (*fixpara_func)(control_ptr,
					control_ptr->in_entry_order_list[count_1], para_ptr,
					cformat_flags, error_text)) != ADF_SUCCESS)
					goto EXIT_FUNCTION;
				current_col = 0;
				tab_count   = 0;
				tmp_ptr     = control_ptr->out_para_buffer;
				fprintf(file_ptr, "        ");
				for (count_4 = 0;
					count_4 < control_ptr->current_para_line_count;
					count_4++) {
					if (control_ptr->in_para_line_list[count_4].
						cformat_type != ADF_CFORMAT_CHAR_NONE) {
						*tmp_ptr++ = ADF_CFORMAT_MARKER_CHAR;
						*tmp_ptr++ = control_ptr->in_para_line_list[count_4].
							cformat_type;
						*tmp_ptr   = '\0';
					}
					else if (control_ptr->in_para_line_list[count_4].
						length) {
						nstrcpy(((char *) tmp_ptr),
							control_ptr->in_para_line_list[count_4].ptr,
							control_ptr->in_para_line_list[count_4].length);
						tmp_ptr +=
							control_ptr->in_para_line_list[count_4].length;
					}
				}
				tmp_ptr = control_ptr->out_para_buffer;
				while ((tmp_ptr = ((char *) strwrap(tmp_ptr, &current_col,
					70, &tab_count, 3, 1, &last_char, tmp_buffer))) != NULL)
					fprintf(file_ptr, "%s%s", tmp_buffer,
						(current_col) ? "" : "\n        ");
				fprintf(file_ptr, "%s\n", (current_col) ? "\n" : "");
			}
		}
		STR_EMIT_CharLine('=', 78, NULL, file_ptr);
		ADF_INIT_AreaDataList(entry_data_list);
		fprintf(stderr, ".");
	}

EXIT_FUNCTION:

	return(return_code);
}

static int TEST_DoParaCompare(control_ptr, error_text)
ADF_CONTROL *control_ptr;
char        *error_text;
{
	int              return_code = ADF_SUCCESS;
	unsigned int     count_1;
	unsigned int     count_2;
	unsigned int     count_3;
	unsigned int     cformat_flags;
	char             area_name[ADF_AREA_NAME_LENGTH + 1];
	ADF_ENTRY_DATA   entry_data_list[ADF_AREA_COUNT];
	ADF_PARA_DATA   *para_ptr;
	char            *tmp_para_string;

	fprintf(stderr, "Performing comparison [");

	for (count_1 = 0; count_1 < control_ptr->in_entry_order_count; count_1++) {
		if ((return_code = ADF_GetEntry(control_ptr,
			control_ptr->in_entry_order_list[count_1], entry_data_list,
			error_text)) != ADF_SUCCESS)
			goto EXIT_FUNCTION;
		for (count_2 = 0; count_2 < ADF_AREA_COUNT; count_2++) {
			if ((ADF_AreaNameList[count_2].output_flag != ADF_TRUE) ||
				(!entry_data_list[count_2].para_count))
				continue;
			cformat_flags = TestCFormatFlags |
				((ADF_AreaNameList[count_2].htext_flag == ADF_TRUE) ?
				ADF_CFORMAT_TYPE_HTEXT : ADF_CFORMAT_TYPE_NONE);
			for (count_3 = 0; count_3 < entry_data_list[count_2].para_count;
				count_3++) {
				para_ptr = entry_data_list[count_2].para_list + count_3;
				if ((return_code = TEST_DoFixPara(control_ptr,
					control_ptr->in_entry_order_list[count_1], para_ptr,
					cformat_flags, ADF_FixParagraph, error_text)) != ADF_SUCCESS) {
					ADF_INIT_AreaDataList(entry_data_list);
					goto EXIT_FUNCTION;
				}
				else if ((tmp_para_string =
					strdup(control_ptr->out_para_buffer)) == NULL) {
					GEN_AllocMsgItem(strlen(control_ptr->out_para_buffer) + 1,
						error_text, "Unable to allocate the test paragraph buffer");
					return_code = ADF_MEMORY_FAILURE;
					ADF_INIT_AreaDataList(entry_data_list);
					goto EXIT_FUNCTION;
				}
				else if ((return_code = TEST_DoFixPara(control_ptr,
					control_ptr->in_entry_order_list[count_1], para_ptr,
					cformat_flags, NEW_001_ADF_FixParagraph, error_text)) !=
					ADF_SUCCESS) {
					free(tmp_para_string);
					ADF_INIT_AreaDataList(entry_data_list);
					goto EXIT_FUNCTION;
				}
				if (strcmp(tmp_para_string, control_ptr->out_para_buffer)) {
					printf("%s '%s(%s)', area name '%s', paragraph number %u:\n",
						"Paragraph fix-up mis-match in entry",
						control_ptr->in_entry_order_list[count_1]->base_name,
						control_ptr->in_entry_order_list[count_1]->file_name,
						initcaps(ADF_GetAreaName(count_2, area_name)), count_3);
					printf(">>> [OLD][%s]\n", tmp_para_string);
					printf(">>> [NEW][%s]\n", control_ptr->out_para_buffer);
				}
				free(tmp_para_string);
			}
		}
		ADF_INIT_AreaDataList(entry_data_list);
		fprintf(stderr, ".");
	}

	fprintf(stderr, "]\n");

EXIT_FUNCTION:

	return(return_code);
}

static int TEST_DoFixPara(control_ptr, entry_ptr, para_ptr, cformat_flags,
	fixpara_func, error_text)
ADF_CONTROL     *control_ptr;
ADF_ENTRY       *entry_ptr;
ADF_PARA_DATA   *para_ptr;
unsigned int     cformat_flags;
#ifndef NARGS
int            (*fixpara_func)(ADF_CONTROL *, const ADF_ENTRY *,
						ADF_PARA_DATA *, unsigned int, char *);
#else
int            (*fixpara_func)();
#endif /* #ifndef NARGS */
char            *error_text;
{
	int           return_code = ADF_SUCCESS;
	unsigned int  count_1;
	char         *tmp_ptr;

	if ((return_code = (*fixpara_func)(control_ptr, entry_ptr, para_ptr,
		cformat_flags, error_text)) == ADF_SUCCESS) {
		tmp_ptr  = control_ptr->out_para_buffer;
		*tmp_ptr = '\0';
		for (count_1 = 0; count_1 < control_ptr->current_para_line_count;
			count_1++) {
			if (control_ptr->in_para_line_list[count_1].
				cformat_type != ADF_CFORMAT_CHAR_NONE) {
				*tmp_ptr++ = ADF_CFORMAT_MARKER_CHAR;
				*tmp_ptr++ = control_ptr->in_para_line_list[count_1].
					cformat_type;
				*tmp_ptr   = '\0';
			}
			else if (control_ptr->in_para_line_list[count_1].length) {
				nstrcpy(tmp_ptr,
					control_ptr->in_para_line_list[count_1].ptr,
					control_ptr->in_para_line_list[count_1].length);
				tmp_ptr +=
					control_ptr->in_para_line_list[count_1].length;
			}
		}
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

