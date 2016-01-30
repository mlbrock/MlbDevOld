/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Keyword matching control logic.

	Revision History	:	1998-03-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <stdio.h>
#include <string.h>

#include "kmlfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Function prototypes for static functions . . .								*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(int KML_MatchAllBasic, (KML_CONTROL *control_ptr,
	const KML_DOMAIN *domain_ptr, const char *in_string,
	unsigned int type_mask, char *error_text));
COMPAT_FN_DECL_STATIC(int KML_MatchString, (const KML_ITEM *item_ptr,
	const char *in_string, const char *in_ptr, unsigned int in_length,
	int *match_flag, KML_MATCH *match_ptr, char *error_text));
COMPAT_FN_DECL_STATIC(int KML_MatchComment, (const KML_ITEM *item_ptr,
	const char *in_string, const char *in_ptr, unsigned int in_length,
	int *match_flag, KML_MATCH *match_ptr, char *error_text));
COMPAT_FN_DECL_STATIC(int KML_MatchKeyword, (const KML_ITEM *item_ptr,
	const char *in_string, const char *in_ptr, unsigned int in_length,
	const unsigned char *name_flag_list, int *match_flag, KML_MATCH *match_ptr,
	char *error_text));
COMPAT_FN_DECL_STATIC(int KML_MatchSymbol, (const KML_ITEM *item_ptr,
	const char *in_string, const char *in_ptr, unsigned int in_length,
	int *match_flag, KML_MATCH *match_ptr, char *error_text));
COMPAT_FN_DECL_STATIC(int KML_MatchBlock, (const KML_ITEM *item_ptr,
	const char *in_string, const char *in_ptr, unsigned int in_length,
	unsigned int match_count, const KML_MATCH *match_list,
	unsigned int match_index, int *match_flag, KML_MATCH *match_ptr,
	char *error_text));
COMPAT_FN_DECL_STATIC(int KML_MatchOperator, (const KML_ITEM *item_ptr,
	const char *in_string, const char *in_ptr, unsigned int in_length,
	int *match_flag, KML_MATCH *match_ptr, char *error_text));
COMPAT_FN_DECL_STATIC(int KML_MatchName, (const KML_ITEM *item_ptr,
	const char *in_string, const char *in_ptr, unsigned int in_length,
	unsigned int min_name_length, const unsigned char *other_name_flag_list,
	unsigned int match_count, const KML_MATCH *match_list,
	unsigned int match_index, int *match_flag, KML_MATCH *match_ptr,
	char *error_text));
COMPAT_FN_DECL_STATIC(int KML_MatchNoSpec, (KML_CONTROL *control_ptr,
	const char *in_string, char *error_text));
/*	***********************************************************************	*/
						 
/*	***********************************************************************	*/
#ifndef NARGS
int KML_MatchAll(KML_CONTROL *control_ptr, const KML_DOMAIN *domain_ptr,
	const char *in_string, unsigned int type_mask, char *error_text)
#else
int KML_MatchAll(control_ptr, domain_ptr, in_string, type_mask,
	error_text)
KML_CONTROL      *control_ptr;
const KML_DOMAIN *domain_ptr;
const char       *in_string;
unsigned int      type_mask;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = KML_SUCCESS;
	unsigned int tmp_mask;
	unsigned int remove_mask;

	type_mask &= KML_TYPE_MASK;

	KML_ClearMatchList(control_ptr);

	if (!type_mask)
		goto EXIT_FUNCTION;
	else if ((return_code = KML_MatchAllBasic(control_ptr, domain_ptr,
		in_string, KML_TYPE_STRING | KML_TYPE_COMMENT, error_text)) !=
		KML_SUCCESS)
		goto EXIT_FUNCTION;

	tmp_mask =
		type_mask & (~(KML_TYPE_STRING | KML_TYPE_COMMENT | KML_TYPE_NAME));
	if (tmp_mask) {
		if ((return_code = KML_MatchAllBasic(control_ptr, domain_ptr,
			in_string, tmp_mask, error_text)) != KML_SUCCESS)
			goto EXIT_FUNCTION;
		KML_SORT_MatchList(control_ptr->match_count, control_ptr->match_list);
		if (type_mask & KML_TYPE_NAME) {
			if ((return_code = KML_MatchAllBasic(control_ptr, domain_ptr,
				in_string, KML_TYPE_NAME, error_text)) != KML_SUCCESS)
				goto EXIT_FUNCTION;
			KML_SORT_MatchList(control_ptr->match_count, control_ptr->match_list);
		}
	}     

	remove_mask = ((!(type_mask & KML_TYPE_STRING)) ? KML_TYPE_STRING : 0) |
		((!(type_mask & KML_TYPE_COMMENT)) ? KML_TYPE_COMMENT : 0);
	if (remove_mask)
		KML_RemoveMatchTypes(control_ptr, remove_mask);
			
EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int KML_MatchAllBasic(KML_CONTROL *control_ptr,
	const KML_DOMAIN *domain_ptr, const char *in_string, unsigned int type_mask,
	char *error_text)
#else
static int KML_MatchAllBasic(control_ptr, domain_ptr, in_string, type_mask,
	error_text)
KML_CONTROL      *control_ptr;
const KML_DOMAIN *domain_ptr;
const char       *in_string;
unsigned int      type_mask;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int              return_code = KML_SUCCESS;
	unsigned int     count_1;
	const char      *in_ptr;
	unsigned int     in_length;
	const KML_INDEX *index_ptr;
	const KML_ITEM  *item_ptr;
	unsigned int     match_count;
	unsigned int     match_index;
	int              match_flag;
	KML_MATCH        match_data;
	const char      *line_ptr;
	unsigned long    line_number;
	unsigned int     eol_char_count;

	in_ptr      = in_string;
	in_length   = strlen(in_string);
	match_count = control_ptr->match_count;
	match_index = 0;
	line_ptr    = in_string;
	line_number = 1L;        
						  
	while (*in_ptr && in_length) {
		if ((eol_char_count = STRFUNCS_MEMPTR_IS_EOL(in_ptr, in_length)) > 0) {
			in_ptr    += eol_char_count;
			in_length -= eol_char_count;
			line_ptr   = in_ptr;
			line_number++;      
			continue;
		}                     
		else if ((match_index < match_count) &&
			(in_ptr == control_ptr->match_list[match_index].ptr)) {
			in_ptr      += control_ptr->match_list[match_index].length;
			in_length   -= control_ptr->match_list[match_index].length;
			line_number  = control_ptr->match_list[match_index].end_line;
			line_ptr     = control_ptr->match_list[match_index].ptr +
				(control_ptr->match_list[match_index].length -
				control_ptr->match_list[match_index].end_char);
			match_index++;
			continue;
		}
		else if (!((index_ptr = (domain_ptr->index_list +
			((unsigned int) *((unsigned char *) in_ptr))))->count)) {
			in_ptr++;
			in_length--;
			continue;
		}
		match_flag = KML_FALSE;
		KML_INIT_Match(&match_data);
		match_data.ptr        = in_ptr;
		match_data.start_line = line_number;
		match_data.start_char = ((unsigned int) (in_ptr - line_ptr)) + 1;
		for (count_1 = 0, item_ptr = index_ptr->item_ptr;
			count_1 < index_ptr->count; count_1++, item_ptr++) {
			if ((!(item_ptr->type & type_mask)) ||
				(item_ptr->length > in_length) ||
				((item_ptr->case_flag) ?
				strncmp(in_ptr, item_ptr->ptr, item_ptr->length) :
				strnicmp(in_ptr, item_ptr->ptr, item_ptr->length)) ||
				((match_index < match_count) &&
				((in_ptr + item_ptr->length) >
				control_ptr->match_list[match_index].ptr)))
				continue;
			switch (item_ptr->type) {
				case KML_TYPE_STRING		:
					return_code = KML_MatchString(item_ptr, in_string, in_ptr,
						in_length, &match_flag, &match_data, error_text);
					break;                
				case KML_TYPE_COMMENT	:
					return_code = KML_MatchComment(item_ptr, in_string, in_ptr,
						in_length, &match_flag, &match_data, error_text);
					break;
				case KML_TYPE_KEYWORD	:
					return_code = KML_MatchKeyword(item_ptr, in_string, in_ptr,
						in_length, domain_ptr->name_flag_list, &match_flag,
						&match_data, error_text);
					break;
				case KML_TYPE_SYMBOL		:
					return_code = KML_MatchSymbol(item_ptr, in_string, in_ptr,
						in_length, &match_flag, &match_data, error_text);
					break;
				case KML_TYPE_BLOCK		:
					return_code = KML_MatchBlock(item_ptr, in_string, in_ptr,
						in_length, match_count, control_ptr->match_list, match_index,
						&match_flag, &match_data, error_text);
					break;
				case KML_TYPE_OPERATOR	:
					return_code = KML_MatchOperator(item_ptr, in_string, in_ptr,
						in_length, &match_flag, &match_data, error_text);
					break;
				case KML_TYPE_NAME		:
					return_code = KML_MatchName(item_ptr, in_string, in_ptr,
						in_length, domain_ptr->min_name_length,
						domain_ptr->other_name_flag_list, match_count,
						control_ptr->match_list, match_index, &match_flag,
						&match_data, error_text);
					break;
				case KML_TYPE_NUMBER		:
					break;
				default						:
					sprintf(error_text, "Invalid KML type in item list (%u).",
						item_ptr->type);
					return_code = KML_PARSE_FAILURE;
					break;
			}
			if (return_code != KML_SUCCESS)
				goto EXIT_FUNCTION;
			if (match_flag == KML_TRUE) {
				if ((return_code = KML_AddMatch(control_ptr, &match_data,
					error_text)) != KMLFUNCS_SUCCESS)
					goto EXIT_FUNCTION;
				in_ptr      += match_data.length;
				in_length   -= match_data.length;
				line_number  = match_data.end_line;
				line_ptr     = match_data.ptr +
					(match_data.length - match_data.end_char);
				while ((match_index < match_count) &&
					(in_ptr > control_ptr->match_list[match_index].ptr)) {
					line_number = control_ptr->match_list[match_index].end_line;
					line_ptr    = control_ptr->match_list[match_index].ptr +
						(control_ptr->match_list[match_index].length -
						control_ptr->match_list[match_index].end_char);
					match_index++;
				}
				break;
			}
		}
		if (match_flag != KML_TRUE) {
			in_ptr++;
			in_length--;
		}
	}

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int KML_MatchString(const KML_ITEM *item_ptr, const char *in_string,
	const char *in_ptr, unsigned int in_length, int *match_flag,
	KML_MATCH *match_ptr, char *error_text)
#else
static int KML_MatchString(item_ptr, in_string, in_ptr, in_length, match_flag,
	match_ptr, error_text)
const KML_ITEM *item_ptr;
const char     *in_string;
const char     *in_ptr;
unsigned int    in_length;
int            *match_flag;
KML_MATCH      *match_ptr;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int                return_code = KMLFUNCS_SUCCESS;
	const KML_STRING  *string_ptr;
	const char        *line_ptr;
	unsigned long      line_number;
	unsigned int       eol_char_count;
#ifndef NARGS
	int              (*cmp_func)(const char *, const char *, size_t);
#else
	int              (*cmp_func)();
#endif /* #ifndef NARGS */

	string_ptr  = item_ptr->type_ptr.string_ptr;
	cmp_func    = (item_ptr->case_flag) ? strncmp : strnicmp;
	line_ptr    = match_ptr->ptr - (match_ptr->start_char - 1);
	line_number = match_ptr->start_line;
	*match_flag = KMLFUNCS_FALSE;

	if ((string_ptr->start_length <= in_length) &&
		(!(*cmp_func)(string_ptr->start_ptr, in_ptr,
		string_ptr->start_length))) {
		*match_flag                     = KMLFUNCS_TRUE;
		match_ptr->type                 = KML_TYPE_STRING;
		match_ptr->type_value           = 0L;
		match_ptr->type_ptr.string_ptr  = string_ptr;
		match_ptr->ptr                  = in_ptr;
		in_ptr                         += string_ptr->start_length;
		in_length                      -= string_ptr->start_length;
		while (*in_ptr) {
			if ((eol_char_count =
				STRFUNCS_MEMPTR_IS_EOL(in_ptr, in_length)) > 0) {
				in_ptr    += eol_char_count;
				in_length -= eol_char_count;
				line_ptr   = in_ptr;
				line_number++;      
			}
			else if ((string_ptr->escape_length <= in_length) &&
				(!(*cmp_func)(in_ptr, string_ptr->escape_ptr,
				string_ptr->escape_length))) {
				in_ptr    += string_ptr->escape_length;
				in_length -= string_ptr->escape_length;
			}
			else if ((string_ptr->end_length <= in_length) &&
				(!(*cmp_func)(in_ptr, string_ptr->end_ptr,
				string_ptr->end_length)))
				break;
			else {
				in_ptr++;
				in_length--;
			}
		}
		if (*in_ptr && in_length) {
			match_ptr->closure_ptr = in_ptr;
			match_ptr->length      = ((unsigned int)
				(in_ptr - match_ptr->ptr)) + string_ptr->end_length;
			match_ptr->end_line    = line_number;
			match_ptr->end_char    = ((unsigned int) (in_ptr - line_ptr)) +
				string_ptr->end_length;
		}
		else {
			sprintf(error_text,
				"%s '%.*s' %s %lu, %s %u: %s '%.*s' sequence.",
				"Unterminated string", 500, string_ptr->start_ptr,
				"encountered beginning on line number" , match_ptr->start_line,
				"character position", match_ptr->start_char,
				"unable to locate the terminating", 500, string_ptr->end_ptr);
			return_code = KML_PARSE_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int KML_MatchComment(const KML_ITEM *item_ptr, const char *in_string,
	const char *in_ptr, unsigned int in_length, int *match_flag,
	KML_MATCH *match_ptr, char *error_text)
#else
static int KML_MatchComment(item_ptr, in_string, in_ptr, in_length,
	match_flag, match_ptr, error_text)
const KML_ITEM *item_ptr;
const char     *in_string;
const char     *in_ptr;
unsigned int    in_length;
int            *match_flag;
KML_MATCH      *match_ptr;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int                 return_code = KMLFUNCS_SUCCESS;
	const char         *tmp_ptr;
	const KML_COMMENT  *comment_ptr;
	const char         *line_ptr;
	unsigned long       line_number;
	unsigned int        eol_char_count;
#ifndef NARGS
	int               (*cmp_func)(const char *, const char *, size_t);
#else
	int               (*cmp_func)();
#endif /* #ifndef NARGS */

	comment_ptr = item_ptr->type_ptr.comment_ptr;
	cmp_func    = (item_ptr->case_flag) ? strncmp : strnicmp;
	line_ptr    = match_ptr->ptr - (match_ptr->start_char - 1);
	line_number = match_ptr->start_line;
	*match_flag = KMLFUNCS_FALSE;

	if ((comment_ptr->start_length <= in_length) &&
		(!(*cmp_func)(comment_ptr->start_ptr, in_ptr,
		comment_ptr->start_length))) {
		*match_flag                     = KMLFUNCS_TRUE;
		match_ptr->type                 = KML_TYPE_COMMENT;
		match_ptr->type_value           = 0L;
		match_ptr->type_ptr.comment_ptr = comment_ptr;
		match_ptr->ptr                  = in_ptr;
		if (comment_ptr->end_length) {
			in_ptr    += comment_ptr->start_length;
			in_length -= comment_ptr->start_length;
			while (*in_ptr) {
				if ((eol_char_count =
					STRFUNCS_MEMPTR_IS_EOL(in_ptr, in_length)) > 0) {
					in_ptr    += eol_char_count;
					in_length -= eol_char_count;
					line_ptr   = in_ptr;
					line_number++;      
				}
				else if ((comment_ptr->end_length <= in_length) &&
					(!(*cmp_func)(comment_ptr->end_ptr, in_ptr,
					comment_ptr->end_length)))
					break;
				else {
					in_ptr++;
					in_length--;
				}
			}
			if (*in_ptr && in_length) {
				match_ptr->length      = ((unsigned int)
					(in_ptr - match_ptr->ptr)) + comment_ptr->end_length;
				match_ptr->closure_ptr = in_ptr + (comment_ptr->end_length - 1);
				match_ptr->end_line    = line_number;
				match_ptr->end_char    = ((unsigned int) (in_ptr - line_ptr)) +
					comment_ptr->end_length;
			}
			else {
				sprintf(error_text,
					"%s '%-.500s' %s %lu, %s %u: %s '%-.500s' sequence.",
					"Unterminated comment", comment_ptr->start_ptr,
					"encountered beginning on line number" , match_ptr->start_line,
					"character position", match_ptr->start_char,
					"unable to locate the terminating", comment_ptr->end_ptr);
				return_code = KML_PARSE_FAILURE;
			}
		}
		else if ((tmp_ptr =
			KML_GetEndOfLine(in_ptr + comment_ptr->start_length)) != NULL) {
			match_ptr->length      = ((unsigned int) (tmp_ptr - in_ptr)) +
				(((*tmp_ptr == '\r') && (*(tmp_ptr + 1) == '\n')) ? 2 : 1);
			match_ptr->closure_ptr = (tmp_ptr +
				(((*tmp_ptr == '\r') && (*(tmp_ptr + 1) == '\n')) ? 2 : 1)) - 1;
		}
		else {
			match_ptr->length      = in_length;
			match_ptr->closure_ptr = in_ptr;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int KML_MatchKeyword(const KML_ITEM *item_ptr, const char *in_string,
	const char *in_ptr, unsigned int in_length,
	const unsigned char *name_flag_list, int *match_flag, KML_MATCH *match_ptr,
	char *error_text)
#else
static int KML_MatchKeyword(item_ptr, in_string, in_ptr, in_length,
	name_flag_list, match_flag, match_ptr, error_text)
const KML_ITEM      *item_ptr;
const char          *in_string;
const char          *in_ptr;
unsigned int         in_length;
const unsigned char *name_flag_list;
int                 *match_flag;
KML_MATCH           *match_ptr;
char                *error_text;
#endif /* #ifndef NARGS */
{
	int                 return_code = KMLFUNCS_SUCCESS;
	const char         *tmp_ptr;
	const KML_KEYWORD  *keyword_ptr;
#ifndef NARGS
	int               (*cmp_func)(const char *, const char *, size_t);
#else
	int               (*cmp_func)();
#endif /* #ifndef NARGS */

	keyword_ptr = item_ptr->type_ptr.keyword_ptr;
	cmp_func    = (item_ptr->case_flag) ? strncmp : strnicmp;
	*match_flag = KMLFUNCS_FALSE;

	if ((keyword_ptr->length <= in_length) &&
		(!(*cmp_func)(keyword_ptr->keyword, in_ptr, keyword_ptr->length)) &&
		((in_ptr == in_string) || isspace(*(in_ptr - 1)) ||
		iscntrl(*(in_ptr - 1)) || (!name_flag_list
		[((unsigned int) *((unsigned char *) (in_ptr - 1)))])) &&
		((!(*(tmp_ptr = (in_ptr + keyword_ptr->length)))) ||
		isspace(*tmp_ptr) || iscntrl(*tmp_ptr) || (!name_flag_list
		[((unsigned int) *((unsigned char *) tmp_ptr))]))) {
		*match_flag                     = KMLFUNCS_TRUE;
		match_ptr->type                 = KML_TYPE_KEYWORD;
		match_ptr->type_value           = 0L;
		match_ptr->type_ptr.keyword_ptr = keyword_ptr;
		match_ptr->length               = keyword_ptr->length;
		match_ptr->ptr                  = in_ptr;
		match_ptr->closure_ptr          = in_ptr + (keyword_ptr->length - 1);
		match_ptr->end_line             = match_ptr->start_line;
		match_ptr->end_char             = match_ptr->start_char +
			(keyword_ptr->length - 1);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int KML_MatchSymbol(const KML_ITEM *item_ptr, const char *in_string,
	const char *in_ptr, unsigned int in_length, int *match_flag,
	KML_MATCH *match_ptr, char *error_text)
#else
static int KML_MatchSymbol(item_ptr, in_string, in_ptr, in_length,
	match_flag, match_ptr, error_text)
const KML_ITEM *item_ptr;
const char     *in_string;
const char     *in_ptr;
unsigned int    in_length;
int            *match_flag;
KML_MATCH      *match_ptr;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int                return_code = KMLFUNCS_SUCCESS;
	const KML_SYMBOL  *symbol_ptr;
#ifndef NARGS
	int              (*cmp_func)(const char *, const char *, size_t);
#else
	int              (*cmp_func)();
#endif /* #ifndef NARGS */

	symbol_ptr  = item_ptr->type_ptr.symbol_ptr;
	cmp_func    = (item_ptr->case_flag) ? strncmp : strnicmp;
	*match_flag = KMLFUNCS_FALSE;

	if ((symbol_ptr->length <= in_length) &&
		(!(*cmp_func)(symbol_ptr->ptr, in_ptr, symbol_ptr->length))) {
		*match_flag                     = KMLFUNCS_TRUE;
		match_ptr->type                 = KML_TYPE_SYMBOL;
		match_ptr->type_value           = 0L;
		match_ptr->type_ptr.symbol_ptr  = symbol_ptr;
		match_ptr->length               = symbol_ptr->length;
		match_ptr->ptr                  = in_ptr;
		match_ptr->closure_ptr          = in_ptr + (symbol_ptr->length - 1);
		match_ptr->end_line             = match_ptr->start_line;
		match_ptr->end_char             = match_ptr->start_char +
			(symbol_ptr->length - 1);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int KML_MatchBlock(const KML_ITEM *item_ptr, const char *in_string,
	const char *in_ptr, unsigned int in_length, unsigned int match_count,
	const KML_MATCH *match_list, unsigned int match_index, int *match_flag,
	KML_MATCH *match_ptr, char *error_text)
#else
static int KML_MatchBlock(item_ptr, in_string, in_ptr, in_length,
	match_count, match_list, match_index, match_flag, match_ptr, error_text)
const KML_ITEM  *item_ptr;
const char      *in_string;
const char      *in_ptr;
unsigned int     in_length;
unsigned int     match_count;
const KML_MATCH *match_list;
unsigned int     match_index;
int             *match_flag;
KML_MATCH       *match_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int               return_code = KMLFUNCS_SUCCESS;
	const KML_BLOCK  *block_ptr;
	const char       *line_ptr;
	unsigned long     line_number;
	unsigned int      eol_char_count;
	unsigned int      internal_count;
#ifndef NARGS
	int             (*cmp_func)(const char *, const char *, size_t);
#else
	int             (*cmp_func)();
#endif /* #ifndef NARGS */

	block_ptr   = item_ptr->type_ptr.block_ptr;
	cmp_func    = (item_ptr->case_flag) ? strncmp : strnicmp;
	line_ptr    = match_ptr->ptr - (match_ptr->start_char - 1);
	line_number = match_ptr->start_line;
	*match_flag = KMLFUNCS_FALSE;

	if ((block_ptr->start_length <= in_length) &&
		(!(*cmp_func)(block_ptr->start_ptr, in_ptr, block_ptr->start_length))) {
		*match_flag                    = KMLFUNCS_TRUE;
		match_ptr->type                = KML_TYPE_BLOCK;
		match_ptr->type_value          = 0L;
		match_ptr->type_ptr.block_ptr  = block_ptr;
		match_ptr->length              = block_ptr->start_length;
		match_ptr->ptr                 = in_ptr;
		match_ptr->closure_ptr         = in_ptr + (block_ptr->start_length - 1);
		internal_count                 = 0;
		in_ptr                        += block_ptr->start_length;
		in_length                     -= block_ptr->start_length;
/*
	CODE NOTE: The semantics of these members must be resolved --- see below.
*/
		match_ptr->end_line = line_number;
		match_ptr->end_char = match_ptr->start_char + (block_ptr->start_length - 1);
		while (*in_ptr) {
			if ((eol_char_count =
				STRFUNCS_MEMPTR_IS_EOL(in_ptr, in_length)) > 0) {
				in_ptr    += eol_char_count;
				in_length -= eol_char_count;
				line_ptr   = in_ptr;
				line_number++;      
			}
			else if ((match_index < match_count) &&
				(in_ptr == match_list[match_index].ptr)) {
				in_ptr    += match_list[match_index].length;
				in_length -= match_list[match_index].length;
				match_index++;
			}
			else if ((block_ptr->start_length <= in_length) &&
				(!(*cmp_func)(block_ptr->start_ptr, in_ptr,
				block_ptr->start_length)) &&
				((match_index > match_count) ||
				((in_ptr + block_ptr->start_length) <=
				match_list[match_index].ptr))) {
				in_ptr    += block_ptr->start_length;
				in_length -= block_ptr->start_length;
				internal_count++;
			}               
			else if ((block_ptr->end_length <= in_length) &&
				(!(*cmp_func)(block_ptr->end_ptr, in_ptr,
				block_ptr->end_length)) &&
				((match_index > match_count) ||
				((in_ptr + block_ptr->end_length) <=
				match_list[match_index].ptr))) {
				if (internal_count--) {
					in_ptr    += block_ptr->end_length;
					in_length -= block_ptr->end_length;
				}
				else {
					match_ptr->closure_ptr = in_ptr +
						(block_ptr->end_length - 1);
/*
	CODE NOTE: The semantics of these members must be resolved --- see above.
*/
/*
					match_ptr->end_line    = line_number;
					match_ptr->end_char    =
						((unsigned int) (in_ptr - line_ptr)) +
						block_ptr->end_length;
*/
					break;
				}
			}
			else {
				in_ptr++;
				in_length--;
			}
		}
		if (match_ptr->closure_ptr == NULL) {
			sprintf(error_text,
				"%s '%-.500s' %s %lu, %s %u: %s '%-.500s' sequence.",
				"Unterminated block", block_ptr->start_ptr,
				"encountered beginning on line number" , match_ptr->start_line,
				"character position", match_ptr->start_char,
				"unable to locate the terminating", block_ptr->end_ptr);
			return_code = KML_PARSE_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int KML_MatchOperator(const KML_ITEM *item_ptr, const char *in_string,
	const char *in_ptr, unsigned int in_length, int *match_flag,
	KML_MATCH *match_ptr, char *error_text)
#else
static int KML_MatchOperator(item_ptr, in_string, in_ptr, in_length,
	match_flag, match_ptr, error_text)
const KML_ITEM *item_ptr;
const char     *in_string;
const char     *in_ptr;
unsigned int    in_length;
int            *match_flag;
KML_MATCH      *match_ptr;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int                  return_code = KMLFUNCS_SUCCESS;
	const KML_OPERATOR  *operator_ptr;
#ifndef NARGS
	int                (*cmp_func)(const char *, const char *, size_t);
#else
	int                (*cmp_func)();
#endif /* #ifndef NARGS */

	operator_ptr = item_ptr->type_ptr.operator_ptr;
	cmp_func    = (item_ptr->case_flag) ? strncmp : strnicmp;
	*match_flag = KMLFUNCS_FALSE;

	if ((operator_ptr->length <= in_length) &&
		(!(*cmp_func)(operator_ptr->ptr, in_ptr, operator_ptr->length))) {
		*match_flag                      = KMLFUNCS_TRUE;
		match_ptr->type                  = KML_TYPE_OPERATOR;
		match_ptr->type_value            = 0L;
		match_ptr->type_ptr.operator_ptr = operator_ptr;
		match_ptr->length                = operator_ptr->length;
		match_ptr->ptr                   = in_ptr;
		match_ptr->closure_ptr           = in_ptr + (operator_ptr->length - 1);
		match_ptr->end_line              = match_ptr->start_line;
		match_ptr->end_char              = match_ptr->start_char +
			(operator_ptr->length - 1);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int KML_MatchName(const KML_ITEM *item_ptr, const char *in_string,
	const char *in_ptr, unsigned int in_length, unsigned int min_name_length,
	const unsigned char *other_name_flag_list, unsigned int match_count,
	const KML_MATCH *match_list, unsigned int match_index, int *match_flag,
	KML_MATCH *match_ptr, char *error_text)
#else
static int KML_MatchName(item_ptr, in_string, in_ptr, in_length,
	min_name_length, other_name_flag_list, match_count, match_list,
	match_index, match_flag, match_ptr, error_text)
const KML_ITEM      *item_ptr;
const char          *in_string;
const char          *in_ptr;
unsigned int         in_length;
unsigned int         min_name_length;
const unsigned char *other_name_flag_list;
unsigned int         match_count;
const KML_MATCH     *match_list;
unsigned int         match_index;
int                 *match_flag;
KML_MATCH           *match_ptr;
char                *error_text;
#endif /* #ifndef NARGS */
{
	int              return_code = KMLFUNCS_SUCCESS;
	const KML_NAME  *name_ptr;
	const char      *line_ptr;
	unsigned long    line_number;
	unsigned int     eol_char_count;

	name_ptr    = item_ptr->type_ptr.name_ptr;
	line_ptr    = match_ptr->ptr - (match_ptr->start_char - 1);
	line_number = match_ptr->start_line;
	*match_flag = KMLFUNCS_FALSE;

	if ((min_name_length == 1) || ((in_length > 1) && *(in_ptr + 1) &&
		((match_index >= match_count) ||
		((in_ptr + 1) < match_list[match_index].ptr)) &&
		(strchr(name_ptr->other_chars, *(in_ptr + 1)) != NULL))) {
		*match_flag                  = KMLFUNCS_TRUE;
		match_ptr->type              = KML_TYPE_NAME;                        
		match_ptr->type_value        = 0L;
		match_ptr->type_ptr.name_ptr = name_ptr;
		match_ptr->ptr               = in_ptr;
		in_ptr++;
		in_length--;
		while (*in_ptr && in_length &&
			other_name_flag_list[((unsigned int) *((unsigned char *) in_ptr))] &&
			((match_index >= match_count) ||
			(in_ptr < match_list[match_index].ptr))) {
			if ((eol_char_count =
				STRFUNCS_MEMPTR_IS_EOL(in_ptr, in_length)) > 0) {
				in_ptr    += eol_char_count;
				in_length -= eol_char_count;
				line_ptr   = in_ptr;
				line_number++;      
			}
			else {
				in_ptr++;
				in_length--;
			}
		}
		match_ptr->length      = ((unsigned int) (in_ptr - match_ptr->ptr));
		match_ptr->closure_ptr = in_ptr - 1;
		match_ptr->end_line    = line_number;
		match_ptr->end_char    = ((unsigned int) (in_ptr - line_ptr));
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int KML_MatchNoSpec(KML_CONTROL *control_ptr, const char *in_string,
	char *error_text)
#else
static int KML_MatchNoSpec(control_ptr, in_string, error_text)
KML_CONTROL *control_ptr;
const char  *in_string;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int              return_code = KML_SUCCESS;
	const char      *in_ptr;
	unsigned int     in_length;
	unsigned int     match_count;
	unsigned int     match_index;
	KML_MATCH        match_data;
	const char      *line_ptr;
	unsigned long    line_number;
	unsigned int     eol_char_count;

	in_ptr      = in_string;
	in_length   = strlen(in_string);
	match_count = control_ptr->match_count;
	match_index = 0;
	line_ptr    = in_string;
	line_number = 1L;        
						  
	while (*in_ptr && in_length) {
		if ((eol_char_count = STRFUNCS_MEMPTR_IS_EOL(in_ptr, in_length)) > 0) {
			in_ptr    += eol_char_count;
			in_length -= eol_char_count;
			line_ptr   = in_ptr;
			line_number++;      
			continue;
		}
		else if ((match_index < match_count) &&
			(in_ptr == control_ptr->match_list[match_index].ptr)) {
			in_ptr      += control_ptr->match_list[match_index].length;
			in_length   -= control_ptr->match_list[match_index].length;
			line_number  = control_ptr->match_list[match_index].end_line;
			line_ptr     = control_ptr->match_list[match_index].ptr +
				(control_ptr->match_list[match_index].length -
				control_ptr->match_list[match_index].end_char);
if (!strnicmp(control_ptr->match_list[match_index].ptr, "int", 3))
	fprintf(stderr, "*** PROBLEM START ***\n");
			if (++match_index < match_count)
				continue;
		}
		KML_INIT_Match(&match_data);
		match_data.type              = 12345;
		match_data.type_value        = 0L;
		match_data.type_ptr.void_ptr = NULL;
		match_data.ptr               = in_ptr;
		match_data.start_line        = line_number;
		match_data.start_char        = ((unsigned int) (in_ptr - line_ptr)) + 1;
		if (match_index < match_count) {
if (!strncmp(match_data.ptr, "onst char", strlen("onst char")))
	fprintf(stderr, "*** PROBLEM ***\n");
			match_data.length      = ((unsigned int)
				(control_ptr->match_list[match_index].ptr - in_ptr));
			match_data.closure_ptr = control_ptr->match_list[match_index].ptr - 1;
			while (in_ptr < match_data.closure_ptr) {
				if ((eol_char_count =
					STRFUNCS_MEMPTR_IS_EOL(in_ptr, in_length)) > 0) {
					in_ptr      += eol_char_count;
					in_length   -= eol_char_count;
					line_ptr  = in_ptr;
					line_number++;      
				}
				else {
					in_ptr++;
					in_length--;
				}
			}
			match_data.end_line = line_number;
			match_data.end_char = ((unsigned int)
				(match_data.closure_ptr - line_ptr)) + 1;
			in_ptr++;
			in_length--;
		}
		else {
			match_data.length       = in_length;
			match_data.closure_ptr  = in_ptr - in_length;
			match_data.end_line     = line_number;
			match_data.end_char     = ((unsigned int) (in_ptr - line_ptr)) + 1;
			in_ptr                 += match_data.length;
			in_length              -= match_data.length;
		}
		if ((return_code = KML_AddMatch(control_ptr, &match_data,
			error_text)) != KMLFUNCS_SUCCESS)
			break;
		while ((match_index < match_count) &&
			(in_ptr > control_ptr->match_list[match_index].ptr)) {
			line_number = control_ptr->match_list[match_index].end_line;
			line_ptr    = control_ptr->match_list[match_index].ptr +
				(control_ptr->match_list[match_index].length -
				control_ptr->match_list[match_index].end_char);
			match_index++;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <stdio.h>
#include <stdlib.h>

COMPAT_FN_DECL(int main, (int argc, char **argv));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int               return_code;
	unsigned int      count_1;
	unsigned int      count_2;
	KML_CONTROL       control_data;
	const KML_DOMAIN *domain_ptr;
	const char       *file_type;
	char             *file_buffer;
	char              buffer[16];
	char              error_text[KMLFUNCS_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'KML_MatchAll()'\n");
	fprintf(stderr, "---- ------- --- ----------------\n\n");


	if (argc == 1) {
		sprintf(error_text, "USAGE:\n   %s <source-file> [<source-file> ...]",
			argv[0]);
		return_code = KMLFUNCS_BAD_ARGS_FAILURE;
	}
	else if ((return_code = KML_TEST_InitializeControl(&control_data,
		error_text)) == KMLFUNCS_SUCCESS) {
		for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
			if (((file_type = strrchr(argv[count_1], '.')) != NULL) &&
				*file_type)
				fprintf(stderr, "File: %s (using extension '%s')",
					argv[count_1], ++file_type);
			else
				fprintf(stderr, "File: %s (no extension, using '%s')",
					argv[count_1], file_type = "c");
			if ((domain_ptr = KML_FIND_ControlDomainByType(&control_data,
				file_type)) == NULL) {
				sprintf(error_text,
					"Unable to locate a domain for file extension '%-.500s'.",
					file_type);
				return_code = KML_BAD_ARGS_FAILURE;
				break;
			}
			fprintf(stderr, ": Found domain name '%s', description '%s'.\n",
				domain_ptr->domain_name, domain_ptr->domain_description);
			STR_EMIT_CharLine('=', 78, NULL, NULL);
			printf("File: %s\n", argv[count_1]);
			STR_EMIT_CharLine('-', 78, NULL, NULL);
			if ((return_code = KML_TFREAD_ReadFileBuffer(argv[count_1], NULL,
				&file_buffer, error_text)) != KMLFUNCS_SUCCESS)
				break;
			if ((return_code = KML_MatchAll(&control_data, domain_ptr,
				file_buffer, KML_TYPE_MASK, error_text)) != KMLFUNCS_SUCCESS)
				break;
			for (count_2 = 0; count_2 < control_data.match_count; count_2++) {
				printf("%5.5lu@%5.5u - %5.5lu@%5.5u:%-8.8s:%-*.*s\n",
					control_data.match_list[count_2].start_line,
					control_data.match_list[count_2].start_char,
					control_data.match_list[count_2].end_line,
					control_data.match_list[count_2].end_char,
					KML_GetTypeName(control_data.match_list[count_2].type, buffer),
					((int) control_data.match_list[count_2].length),
					((int) control_data.match_list[count_2].length),
					control_data.match_list[count_2].ptr);
				STR_EMIT_CharLine('-', 78, NULL, NULL);
			}
			fprintf(stderr, "File: %s --- %u matches.\n", argv[count_1],
				control_data.match_count);
			free(file_buffer);
			KML_ClearMatchList(&control_data);
		}                    
		STR_EMIT_CharLine('=', 78, NULL, NULL);
		KML_FREE_Control(&control_data);
	}

	if (return_code != KMLFUNCS_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

