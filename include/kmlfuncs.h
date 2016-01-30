/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Include File									*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the Keyword Matching Library.

	Revision History	:	1998-03-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__KMLFUNCS_H__h

#define h__KMLFUNCS_H__h					1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <limits.h>

#include <strfuncs.h>

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define KMLFUNCS_TRUE						1
#define KMLFUNCS_FALSE						0

#define KML_TRUE								KMLFUNCS_TRUE
#define KML_FALSE								KMLFUNCS_FALSE

#define KMLFUNCS_SUCCESS					0
#define KMLFUNCS_FAILURE					-1
#define KMLFUNCS_BAD_ARGS_FAILURE		-2
#define KMLFUNCS_MEMORY_FAILURE			-3
#define KMLFUNCS_SYSTEM_FAILURE			-4
#define KMLFUNCS_PARSE_FAILURE			-5

#define KML_SUCCESS							KMLFUNCS_SUCCESS
#define KML_FAILURE							KMLFUNCS_FAILURE
#define KML_BAD_ARGS_FAILURE				KMLFUNCS_BAD_ARGS_FAILURE
#define KML_MEMORY_FAILURE					KMLFUNCS_MEMORY_FAILURE
#define KML_SYSTEM_FAILURE					KMLFUNCS_SYSTEM_FAILURE
#define KML_PARSE_FAILURE					KMLFUNCS_PARSE_FAILURE

#define KMLFUNCS_MAX_ERROR_TEXT			2048
#define KML_MAX_ERROR_TEXT					KMLFUNCS_MAX_ERROR_TEXT

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define KML_TYPE_NONE						((unsigned int) 0X0000)
#define KML_TYPE_STRING						((unsigned int) 0X0001)
#define KML_TYPE_COMMENT				 	((unsigned int) 0X0002)
#define KML_TYPE_KEYWORD					((unsigned int) 0X0004)
#define KML_TYPE_SYMBOL						((unsigned int) 0X0008)
#define KML_TYPE_BLOCK						((unsigned int) 0X0010)
#define KML_TYPE_OPERATOR					((unsigned int) 0X0020)
#define KML_TYPE_NAME						((unsigned int) 0X0040)
#define KML_TYPE_NUMBER						((unsigned int) 0X0080)

#define KML_TYPE_MASK						\
	(KML_TYPE_STRING |						\
	KML_TYPE_COMMENT |						\
	KML_TYPE_KEYWORD |						\
	KML_TYPE_SYMBOL  |						\
	KML_TYPE_BLOCK   |						\
	KML_TYPE_NAME    |						\
	KML_TYPE_NUMBER  |						\
	KML_TYPE_OPERATOR)

#define KML_TYPE_ALL							KML_TYPE_MASK

#define KML_MATCH_ALLOCATION_GRAN		1000

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#define KML_OP_TYPE_OTHER					0X0000
#define KML_OP_TYPE_ASSIGN					0X0001
#define KML_OP_TYPE_EQUIV					0X0002
#define KML_OP_TYPE_INFIX					0X0004
#define KML_OP_TYPE_OUTFIX					0X0008
#define KML_OP_TYPE_PREFIX					0X0010
#define KML_OP_TYPE_LOGICAL				0X0020
#define KML_OP_TYPE_BITWISE				0X0040
#define KML_OP_TYPE_SHIFT					0X0080
/*	***********************************************************************	*/

typedef struct {
	char         *start_ptr;
	unsigned int  start_length;
	char         *escape_ptr;
	unsigned int  escape_length;
	char         *end_ptr;
	unsigned int  end_length;
} KML_STRING;

typedef struct {
	char         *start_ptr;
	unsigned int  start_length;
	char         *end_ptr;
	unsigned int  end_length;
} KML_COMMENT;

typedef struct {
	char         *keyword;
	unsigned int  length;
} KML_KEYWORD;

typedef struct {
	char         *ptr;
	unsigned int  length;
} KML_SYMBOL;

typedef struct {
	char         *start_ptr;
	unsigned int  start_length;
	char         *end_ptr;
	unsigned int  end_length;
} KML_BLOCK;

typedef struct {
	char         *ptr;
	unsigned int  length;
	unsigned int  op_type;
} KML_OPERATOR;

typedef struct {
	char *first_char;
	char *other_chars;
} KML_NAME;

typedef union {
	const KML_STRING   *string_ptr;
	const KML_COMMENT  *comment_ptr;
	const KML_KEYWORD  *keyword_ptr;
	const KML_SYMBOL   *symbol_ptr;
	const KML_BLOCK    *block_ptr;
	const KML_NAME     *name_ptr;
	const KML_OPERATOR *operator_ptr;
	const void         *void_ptr;
} KML_TYPE;

typedef struct {
	unsigned int   type;
	unsigned long  type_value;
	KML_TYPE       type_ptr;
	unsigned int   length;
	const char    *ptr;
	const char    *closure_ptr;
	unsigned long  start_line;
	unsigned long  end_line;
	unsigned int   start_char;
	unsigned int   end_char;
} KML_MATCH;

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable:4820)
#endif /* #ifdef _MSC_VER */

typedef struct {
	unsigned int   type;
	KML_TYPE       type_ptr;
	unsigned int   length;
	const char    *ptr;
	unsigned char  first_char;
	int            case_flag;
} KML_ITEM;

#ifdef _MSC_VER
# pragma warning(pop)
#endif /* #ifdef _MSC_VER */
/*	***********************************************************************	*/

/*	***********************************************************************	*/
typedef struct {
	KML_ITEM     *item_ptr;
	unsigned int  count;
} KML_INDEX;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
typedef struct {
	char          *domain_name;
	char          *domain_description;
	unsigned int   type_count;
	char         **type_list;
	int            string_case_flag;
	unsigned int   string_count;
	KML_STRING    *string_list;
	int            comment_case_flag;
	unsigned int   comment_count;
	KML_COMMENT   *comment_list;
	int            keyword_case_flag;
	unsigned int   keyword_count;
	KML_KEYWORD   *keyword_list;
	int            symbol_case_flag;
	unsigned int   symbol_count;
	KML_SYMBOL    *symbol_list;
	int            block_case_flag;
	unsigned int   block_count;
	KML_BLOCK     *block_list;
	int            name_case_flag;
	unsigned int   name_count;
	KML_NAME      *name_list;
	int            operator_case_flag;
	unsigned int   operator_count;
	KML_OPERATOR  *operator_list;
	unsigned int   item_count;
	KML_ITEM      *item_list;
	KML_INDEX      index_list[UCHAR_MAX + 1];
	unsigned char  name_flag_list[UCHAR_MAX + 1];
	unsigned char  first_name_flag_list[UCHAR_MAX + 1];
	unsigned char  other_name_flag_list[UCHAR_MAX + 1];
	unsigned int   min_name_length;
/*
	unsigned int   match_count;
	KML_MATCH     *match_list;
	unsigned int   allocated_match_count;
*/
} KML_DOMAIN;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
typedef struct {
	unsigned int  domain_count;
	KML_DOMAIN   *domain_list;
	unsigned int   match_count;
	KML_MATCH     *match_list;
	unsigned int   allocated_match_count;
} KML_CONTROL;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Function prototypes . . .															*/
/*	***********************************************************************	*/

COMPAT_FN_DECL(int KML_MatchAll,
	(KML_CONTROL *, const KML_DOMAIN *domain_ptr,
	const char *in_string, unsigned int type_mask, char *error_text));

COMPAT_FN_DECL(int         KML_BuildIndex,
	(KML_DOMAIN *domain_ptr, char *error_text));
COMPAT_FN_DECL(void        KML_ConcatenateKeywords,
	(KML_CONTROL *control_ptr));
COMPAT_FN_DECL(const char *KML_GetEndOfLine,
	(const char *in_string));
COMPAT_FN_DECL(void        KML_GetLineNumbers,
	(KML_CONTROL *control_ptr,
	const char *in_string));
COMPAT_FN_DECL(void        KML_GetLineNumbersFromList,
	(unsigned int match_count,
	KML_MATCH *match_list, const char *in_string));
COMPAT_FN_DECL(void        KML_OutputHPPL,
	(KML_CONTROL *control_ptr, const char *file_name, long file_time,
	unsigned int tab_setting, const char *in_string,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void        KML_OutputHTML,
	(KML_CONTROL *control_ptr, const char *file_name, unsigned int tab_setting,
	const char *in_string, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(int         KML_OutputString,
	(KML_CONTROL *control_ptr, unsigned int tab_setting, const char *in_string,
	char **buffer_ptr, char *error_text));

COMPAT_FN_DECL(char *KML_GetTypeName,
	(unsigned int in_type, char *out_name));
COMPAT_FN_DECL(char *KML_GetTypeNameExtended,
	(unsigned int in_type, char *out_name));

COMPAT_FN_DECL(const KML_DOMAIN *KML_FIND_ControlDomainByType,
	(const KML_CONTROL *control_ptr, const char *file_type));
COMPAT_FN_DECL(int               KML_FIND_DomainByType,
	(unsigned int in_count, const KML_DOMAIN *in_list, const char *file_type,
	unsigned int *found_index));

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
COMPAT_FN_DECL(int  KML_COPY_Block,
	(const KML_BLOCK *in_ptr, KML_BLOCK *out_ptr, char *error_text));
COMPAT_FN_DECL(int  KML_COPY_BlockList,
	(unsigned int in_count, const KML_BLOCK *in_list, unsigned int *out_count,
	KML_BLOCK **out_list, char *error_text));
COMPAT_FN_DECL(int  KML_COPY_Comment,
	(const KML_COMMENT *in_ptr, KML_COMMENT *out_ptr, char *error_text));
COMPAT_FN_DECL(int  KML_COPY_CommentList,
	(unsigned int in_count, const KML_COMMENT *in_list,
	unsigned int *out_count, KML_COMMENT **out_list, char *error_text));
COMPAT_FN_DECL(int  KML_COPY_Domain,
	(const KML_DOMAIN *in_ptr, KML_DOMAIN *out_ptr, char *error_text));
COMPAT_FN_DECL(int  KML_COPY_DomainList,
	(unsigned int in_count, const KML_DOMAIN *in_list,
	unsigned int *out_count, KML_DOMAIN **out_list, char *error_text));
COMPAT_FN_DECL(int  KML_COPY_Keyword,
	(const KML_KEYWORD *in_ptr, KML_KEYWORD *out_ptr, char *error_text));
COMPAT_FN_DECL(int  KML_COPY_KeywordList,
	(unsigned int in_count, const KML_KEYWORD *in_list,
	unsigned int *out_count, KML_KEYWORD **out_list, char *error_text));
COMPAT_FN_DECL(int  KML_COPY_Match,
	(const KML_MATCH *in_ptr, KML_MATCH *out_ptr, char *error_text));
COMPAT_FN_DECL(int  KML_COPY_MatchList,
	(unsigned int in_count, const KML_MATCH *in_list,
	unsigned int *out_count, KML_MATCH **out_list, char *error_text));
COMPAT_FN_DECL(int  KML_COPY_Name,
	(const KML_NAME *in_ptr, KML_NAME *out_ptr, char *error_text));
COMPAT_FN_DECL(int  KML_COPY_NameList,
	(unsigned int in_count, const KML_NAME *in_list,
	unsigned int *out_count, KML_NAME **out_list, char *error_text));
COMPAT_FN_DECL(int  KML_COPY_Operator,
	(const KML_OPERATOR *in_ptr, KML_OPERATOR *out_ptr, char *error_text));
COMPAT_FN_DECL(int  KML_COPY_OperatorList,
	(unsigned int in_count, const KML_OPERATOR *in_list,
	unsigned int *out_count, KML_OPERATOR **out_list, char *error_text));
COMPAT_FN_DECL(int  KML_COPY_String,
	(const KML_STRING *in_ptr, KML_STRING *out_ptr, char *error_text));
COMPAT_FN_DECL(int  KML_COPY_StringList,
	(unsigned int in_count, const KML_STRING *in_list,
	unsigned int *out_count, KML_STRING **out_list, char *error_text));
COMPAT_FN_DECL(int  KML_COPY_Symbol,
	(const KML_SYMBOL *in_ptr, KML_SYMBOL *out_ptr, char *error_text));
COMPAT_FN_DECL(int  KML_COPY_SymbolList,
	(unsigned int in_count, const KML_SYMBOL *in_list,
	unsigned int *out_count, KML_SYMBOL **out_list, char *error_text));
COMPAT_FN_DECL(void KML_FREE_Block,
	(KML_BLOCK *ptr));
COMPAT_FN_DECL(void KML_FREE_BlockList,
	(unsigned int *in_count, KML_BLOCK **in_list));
COMPAT_FN_DECL(void KML_FREE_Comment,
	(KML_COMMENT *ptr));
COMPAT_FN_DECL(void KML_FREE_CommentList,
	(unsigned int *in_count, KML_COMMENT **in_list));
COMPAT_FN_DECL(void KML_FREE_Control,
	(KML_CONTROL *ptr));
COMPAT_FN_DECL(void KML_FREE_Domain,
	(KML_DOMAIN *ptr));
COMPAT_FN_DECL(void KML_FREE_DomainList,
	(unsigned int *in_count, KML_DOMAIN **in_list));
COMPAT_FN_DECL(void KML_FREE_Keyword,
	(KML_KEYWORD *ptr));
COMPAT_FN_DECL(void KML_FREE_KeywordList,
	(unsigned int *in_count, KML_KEYWORD **in_list));
COMPAT_FN_DECL(void KML_FREE_Match,
	(KML_MATCH *ptr));
COMPAT_FN_DECL(void KML_FREE_MatchList,
	(unsigned int *in_count, KML_MATCH **in_list));
COMPAT_FN_DECL(void KML_FREE_Name,
	(KML_NAME *ptr));
COMPAT_FN_DECL(void KML_FREE_NameList,
	(unsigned int *in_count, KML_NAME **in_list));
COMPAT_FN_DECL(void KML_FREE_Operator,
	(KML_OPERATOR *ptr));
COMPAT_FN_DECL(void KML_FREE_OperatorList,
	(unsigned int *in_count, KML_OPERATOR **in_list));
COMPAT_FN_DECL(void KML_FREE_String,
	(KML_STRING *ptr));
COMPAT_FN_DECL(void KML_FREE_StringList,
	(unsigned int *in_count, KML_STRING **in_list));
COMPAT_FN_DECL(void KML_FREE_Symbol,
	(KML_SYMBOL *ptr));
COMPAT_FN_DECL(void KML_FREE_SymbolList,
	(unsigned int *in_count, KML_SYMBOL **in_list));
COMPAT_FN_DECL(void KML_INIT_Block,
	(KML_BLOCK *ptr));
COMPAT_FN_DECL(void KML_INIT_BlockList,
	(unsigned int in_count, KML_BLOCK *in_list));
COMPAT_FN_DECL(void KML_INIT_Index,
	(KML_INDEX *ptr));
COMPAT_FN_DECL(void KML_INIT_IndexList,
	(unsigned int in_count, KML_INDEX *in_list));
COMPAT_FN_DECL(void KML_INIT_Comment,
	(KML_COMMENT *ptr));
COMPAT_FN_DECL(void KML_INIT_CommentList,
	(unsigned int in_count, KML_COMMENT *in_list));
COMPAT_FN_DECL(void KML_INIT_Control,
	(KML_CONTROL *ptr));
COMPAT_FN_DECL(void KML_INIT_Domain,
	(KML_DOMAIN *ptr));
COMPAT_FN_DECL(void KML_INIT_DomainList,
	(unsigned int in_count, KML_DOMAIN *in_list));
COMPAT_FN_DECL(void KML_INIT_Keyword,
	(KML_KEYWORD *ptr));
COMPAT_FN_DECL(void KML_INIT_KeywordList,
	(unsigned int in_count, KML_KEYWORD *in_list));
COMPAT_FN_DECL(void KML_INIT_Match,
	(KML_MATCH *ptr));
COMPAT_FN_DECL(void KML_INIT_MatchList,
	(unsigned int in_count, KML_MATCH *in_list));
COMPAT_FN_DECL(void KML_INIT_Name,
	(KML_NAME *ptr));
COMPAT_FN_DECL(void KML_INIT_NameList,
	(unsigned int in_count, KML_NAME *in_list));
COMPAT_FN_DECL(void KML_INIT_Operator,
	(KML_OPERATOR *ptr));
COMPAT_FN_DECL(void KML_INIT_OperatorList,
	(unsigned int in_count, KML_OPERATOR *in_list));
COMPAT_FN_DECL(void KML_INIT_String,
	(KML_STRING *ptr));
COMPAT_FN_DECL(void KML_INIT_StringList,
	(unsigned int in_count, KML_STRING *in_list));
COMPAT_FN_DECL(void KML_INIT_Symbol,
	(KML_SYMBOL *ptr));
COMPAT_FN_DECL(void KML_INIT_SymbolList,
	(unsigned int in_count, KML_SYMBOL *in_list));
COMPAT_FN_DECL(int  KML_SCMP_Match,
	(void *control_ptr, const KML_MATCH *ptr_1,
	const KML_MATCH *ptr_2, size_t data_length));
COMPAT_FN_DECL(void KML_SORT_MatchList,
	(unsigned int in_count, KML_MATCH *in_list));
	/*	*****************************************************************	*/

COMPAT_FN_DECL(int  KML_AddMatch,
	(KML_CONTROL *control_ptr, const KML_MATCH *match_ptr,
	char *error_text));
COMPAT_FN_DECL(int  KML_AddMatchBasic,
	(const KML_MATCH *match_ptr, unsigned int *match_count,
	KML_MATCH **match_list, unsigned int *allocated_match_count,
	char *error_text));
COMPAT_FN_DECL(int  KML_AllocateMatchList,
	(KML_CONTROL *control_ptr, unsigned int add_count, char *error_text));
COMPAT_FN_DECL(int  KML_AllocateMatchListBasic,
	(unsigned int alloc_request,
	unsigned int *match_count, KML_MATCH **match_list,
	unsigned int *allocated_match_count, char *error_text));
COMPAT_FN_DECL(void KML_ClearMatchList,
	(KML_CONTROL *control_ptr));
COMPAT_FN_DECL(void KML_RemoveMatchTypes,
	(KML_CONTROL *control_ptr, unsigned int remove_mask));

COMPAT_FN_DECL(int KML_TEST_InitializeControl,
	(KML_CONTROL *control_ptr, char *error_text));
COMPAT_FN_DECL(int KML_TEST_InitializeDomain,
	(const char *file_type, KML_DOMAIN *domain_ptr,
	char *error_text));
COMPAT_FN_DECL(int KML_TFREAD_ReadFileBuffer,
	(const char *file_name, unsigned int *buffer_length, char **buffer_ptr,
	char *error_text));

/*	***********************************************************************	*/

#endif /* #ifndef h__KMLFUNCS_H__h */

