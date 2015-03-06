/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Expression Evaluation Calculator Library (EECFUNCS) Include File			*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the EECFUNCS library.

	Revision History	:	1991-11-03 --- Creation.
									Michael L. Brock
								1993-04-04 --- Version 4 changes.
									Michael L. Brock
								1996-01-28 --- Version 5 changes.
									Michael L. Brock

		Copyright Michael L. Brock 1991 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__EECFUNCS_H__h

#define h__EECFUNCS_H__h					1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <limits.h>
#include <memory.h>
#include <setjmp.h>
#include <stdio.h>

#include <strfuncs.h>

/*	***********************************************************************	*/

#if defined(_MSC_VER) && (_MSC_VER >= 1400)
# pragma warning(push)
# pragma warning(disable:4820)
#endif /* #if defined(_MSC_VER) && (_MSC_VER >= 1400) */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   BASE NAME   :  EEC Truth Codes

   NAME        :  EEC Truth Codes

   DESCRIPTION :  Manifest constants used within EEC to specify the truth
						or falsity of expressions.

						(.) ''EEC_TRUE''

						(.) ''EEC_FALSE''

   NOTES       :  The manifest constant ''EEC_TRUE'' should be defined as
						a non-zero value. Conversely, the manifest constant
						''EEC_FALSE'' should be defined as zero (''0'').

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1991 - 2015 Michael L. Brock

   OUTPUT INDEX:  EEC_TRUE
						EEC_FALSE
						EEC Truth Codes:EEC_TRUE
						EEC Truth Codes:EEC_FALSE
						EEC Manifest Constants:EEC_TRUE
						EEC Manifest Constants:EEC_FALSE
						EEC Defines:EEC_TRUE
						EEC Defines:EEC_FALSE
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:  EEC Truth Codes
						EEC Truth Code
						EEC truth codes
						EEC truth code
						EEC_TRUE
						EEC_FALSE

   PUBLISH NAME:	EEC Truth Codes
						EEC_TRUE
						EEC_FALSE

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define EEC_TRUE								1
#define EEC_FALSE								0
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   BASE NAME   :	EEC Return Codes

   NAME        :  EEC Return Codes

   DESCRIPTION :  The EEC return codes have the following meanings:

						(.) ''EEC_SUCCESS'' means that the function invoked
						completed without error. ''EEC_SUCCESS'' is guaranteed to
						be equal to zero (''0'').

						(.) ''EEC_FAILURE'' indicates that the function invoked
						encountered a general operation failure. This is the
						'catch-all' error code for those errors which do not fit
						into category of one the other EEC error codes.

						(.) ''EEC_BAD_ARGS_FAILURE'' indicates that the
						arguments passed to a function invoked were invalid.

						(.) ''EEC_MEMORY_FAILURE'' indicates that the memory
						required for operation of the function invoked could not be
						allocated.

						(.) ''EEC_SYSTEM_FAILURE'' indicates that the function
						invoked encountered a failure of a standard library
						function or a system call.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1991 - 2015 Michael L. Brock

   OUTPUT INDEX:  EEC_SUCCESS
						EEC_FAILURE
						EEC_BAD_ARGS_FAILURE
						EEC_MEMORY_FAILURE
						EEC_SYSTEM_FAILURE
						EEC Return Codes:EEC_SUCCESS
						EEC Return Codes:EEC_FAILURE
						EEC Return Codes:EEC_BAD_ARGS_FAILURE
						EEC Return Codes:EEC_MEMORY_FAILURE
						EEC Return Codes:EEC_SYSTEM_FAILURE
						EEC Manifest Constants:EEC_SUCCESS
						EEC Manifest Constants:EEC_FAILURE
						EEC Manifest Constants:EEC_BAD_ARGS_FAILURE
						EEC Manifest Constants:EEC_MEMORY_FAILURE
						EEC Manifest Constants:EEC_SYSTEM_FAILURE
						EEC Defines:EEC_SUCCESS
						EEC Defines:EEC_FAILURE
						EEC Defines:EEC_BAD_ARGS_FAILURE
						EEC Defines:EEC_MEMORY_FAILURE
						EEC Defines:EEC_SYSTEM_FAILURE
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:  EEC_SUCCESS
						EEC_FAILURE
						EEC_BAD_ARGS_FAILURE
						EEC_MEMORY_FAILURE
						EEC_SYSTEM_FAILURE
						EEC Return Codes
						EEC Return Code
						EEC return codes
						EEC return code
						EEC Status Codes
						EEC Status Code
						EEC status codes
						EEC status code
						EEC Error Codes
						EEC Error Code
						EEC error codes
						EEC error code

   PUBLISH NAME:	EEC Return Codes
						EEC return codes
						EEC_SUCCESS
						EEC_FAILURE
						EEC_BAD_ARGS_FAILURE
						EEC_MEMORY_FAILURE
						EEC_SYSTEM_FAILURE

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define EEC_SUCCESS							 0
#define EEC_FAILURE							-1
#define EEC_BAD_ARGS_FAILURE				-2
#define EEC_MEMORY_FAILURE					-3
#define EEC_SYSTEM_FAILURE					-4
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :  EEC_MAX_ERROR_TEXT

   DESCRIPTION :  The manifest constant ''EEC_MAX_ERROR_TEXT'' defines
						the minimum amount of storage which should be allocated to
						hold an error message returned by a EEC function.

   CAVEATS     :  EEC error messages can be quite lengthy. Therefore,
						attempting to save space by allocating less than
						''EEC_MAX_ERROR_TEXT'' bytes to error message buffers
						passed to EEC functions can lead to overwriting of the
						heap or the stack.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1991 - 2015 Michael L. Brock

   OUTPUT INDEX:  EEC_MAX_ERROR_TEXT
						EEC Manifest Constants:EEC_MAX_ERROR_TEXT
						EEC Defines:EEC_MAX_ERROR_TEXT
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	EEC_MAX_ERROR_TEXT

   PUBLISH NAME:	EEC_MAX_ERROR_TEXT

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define EEC_MAX_ERROR_TEXT					1024
/*	***********************************************************************	*/

#define EEC_EXPR_LIST_GRAN					100

#define EEC_POSTFIX_GRAN					1000

#define EEC_OPERATOR_OR						 0
#define EEC_OPERATOR_AND					 1
#define EEC_OPERATOR_NE						 2
#define EEC_OPERATOR_EQ						 3
#define EEC_OPERATOR_LT						 4
#define EEC_OPERATOR_LE						 5
#define EEC_OPERATOR_GT						 6
#define EEC_OPERATOR_GE						 7
#define EEC_OPERATOR_MINUS					 8
#define EEC_OPERATOR_PLUS					 9
#define EEC_OPERATOR_MOD					10
#define EEC_OPERATOR_CONCAT				11
#define EEC_OPERATOR_INT_DIVIDE			12
#define EEC_OPERATOR_DIVIDE				13
#define EEC_OPERATOR_MULTIPLY				14
#define EEC_OPERATOR_POWER					15

#define EEC_OPERATOR_COUNT					16

#define EEC_OPERATOR_PRECEDENCE_HIGH	5
#define EEC_OPERATOR_PRECEDENCE_LOW		0

#define EEC_TYPE_NONE						   0
#define EEC_TYPE_BEGIN						   EEC_TYPE_NONE
#define EEC_TYPE_NUMBER						   1
#define EEC_TYPE_STRING						   2
#define EEC_TYPE_NUMBER_OP					   4
#define EEC_TYPE_REL_OP						   8
#define EEC_TYPE_BOOL_OP					  16
#define EEC_TYPE_STRING_OP					  32
#define EEC_TYPE_OPERATOR					  64
#define EEC_TYPE_FUNCTION					 128
#define EEC_TYPE_SYMBOL						 256
#define EEC_TYPE_PAREND						 512
#define EEC_TYPE_POSTFIX					1024
#define EEC_TYPE_ANY							2048

#define EEC_TYPE_BASE_TYPE_MASK			(EEC_TYPE_NUMBER | EEC_TYPE_STRING)

#define EEC_FUNC_ARG_TYPE_NUMBER			EEC_TYPE_NUMBER
#define EEC_FUNC_ARG_TYPE_STRING			EEC_TYPE_STRING
#define EEC_FUNC_ARG_TYPE_ANY				(EEC_TYPE_NUMBER + EEC_TYPE_STRING)
#define EEC_FUNC_ARG_TYPE_PREVIOUS		(EEC_FUNC_ARG_TYPE_ANY + 1)

#define EEC_SUB_EXPR_FLAG_NONE			0
#define EEC_SUB_EXPR_FLAG_DONE			1
#define EEC_SUB_EXPR_FLAG_VOLATILE		128

#define EEC_SUB_EXPR_DONE_FLAG			128

#define EEC_MAX_FUNC_NAME_LENGTH			127

#define EEC_FUNC_MAX_FIXED_ARGS			5

#define EEC_MAX_NUMBER_LENGTH				255

#define EEC_EVAL_FLAG_TYPE_NONE			   EEC_TYPE_NONE
#define EEC_EVAL_FLAG_TYPE_NUMBER		   EEC_TYPE_NUMBER
#define EEC_EVAL_FLAG_TYPE_STRING		   EEC_TYPE_STRING
#define EEC_EVAL_FLAG_TYPE_NULL			   4
#define EEC_EVAL_FLAG_TYPE_NA				   8
#define EEC_EVAL_FLAG_TYPE_ERR			  16
#define EEC_EVAL_FLAG_ALLOCED				1024

#define EEC_EVAL_FLAG_FLAGS_TYPE			\
	(EEC_EVAL_FLAG_TYPE_NUMBER | EEC_EVAL_FLAG_TYPE_STRING)

#define EEC_EVAL_FLAG_FLAGS_SPECIAL		\
	(EEC_EVAL_FLAG_TYPE_NULL | EEC_EVAL_FLAG_TYPE_NA | EEC_EVAL_FLAG_TYPE_ERR)

#define EEC_EVAL_EMPTY_STRING				""

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define EEC_PFIX_TYPE_NUMBER				'N'
#define EEC_PFIX_TYPE_STRING				'"'
#define EEC_PFIX_TYPE_FUNCTION			'@'
#define EEC_PFIX_TYPE_SYMBOL				'S'

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define EEC_INIT_EEC_PARSE_OP_ALIAS(op_alias_ptr)						\
	(((op_alias_ptr) != NULL) ?												\
		((op_alias_ptr)->operator_alias        = NULL,					\
		 (op_alias_ptr)->operator_alias_length = 0,						\
		 (op_alias_ptr)->operator_index        = 0,						\
		 (op_alias_ptr))       : (NULL))

/*
	ADF NOTE: Need 'memset()' here to prevent Purify UMR warning.
*/
#define EEC_INIT_EEC_SUB_EXPR(sub_expr_ptr)								\
	(((sub_expr_ptr) != NULL) ?												\
		(memset((sub_expr_ptr), '\0', sizeof(*(sub_expr_ptr))),		\
		 (sub_expr_ptr)->start_index    = 0,						 		\
		 (sub_expr_ptr)->end_index      = 0,						 		\
		 (sub_expr_ptr)->expr_type      = 0,						 		\
		 (sub_expr_ptr)->expr_spec      = 0L,						 		\
		 (sub_expr_ptr)->postfix.length = 0,						 		\
		 (sub_expr_ptr)->postfix.data   = NULL,					 		\
		 (sub_expr_ptr)->expr_flags     = EEC_SUB_EXPR_FLAG_NONE,	\
		 (sub_expr_ptr))       : (NULL))

#define EEC_INIT_EEC_POSTFIX(postfix_ptr)									\
	(((postfix_ptr) != NULL) ?													\
		((postfix_ptr)->type   = EEC_TYPE_NONE,							\
		 (postfix_ptr)->length = 0,											\
		 (postfix_ptr)->data   = NULL,										\
		 (postfix_ptr))       : (NULL))

#define EEC_INIT_EEC_FUNC_DEF(func_def_ptr)								\
	(((func_def_ptr) != NULL) ?                                    \
		((func_def_ptr)->func_name     = NULL,								\
		 (func_def_ptr)->func_spec     = 0L,								\
		 (func_def_ptr)->func_type     = EEC_TYPE_NONE,					\
		 (func_def_ptr)->func_min_args = 0,									\
		 (func_def_ptr)->func_max_args = 0,									\
		 (func_def_ptr)->func_args[0]  = 0,									\
		 (func_def_ptr)->volatile_flag = EEC_FALSE,						\
		 (func_def_ptr)->func_ptr      = NULL,								\
		 (func_def_ptr))       : (NULL))

#define EEC_INIT_EEC_DATUM(datum_ptr)										\
	(((datum_ptr) != NULL) ?													\
		(memset((datum_ptr), '\0', sizeof(*(datum_ptr))),				\
		 (datum_ptr)->datum.string.length = 0,								\
		 (datum_ptr)->datum.string.data   = NULL,							\
		 (datum_ptr)->datum.number        = 0.0,							\
		 (datum_ptr)->flags               = EEC_EVAL_FLAG_TYPE_NONE,\
		 (datum_ptr))       : (NULL))

#define EEC_INIT_EEC_EVAL_DATA(eval_ptr)									\
	(((eval_ptr) != NULL) ?														\
		((eval_ptr)->eval_stack         = NULL,							\
		 (eval_ptr)->eval_stack_top     = NULL,							\
		 (eval_ptr)->eval_stack_alloc   = 0,								\
		 (eval_ptr)->eval_stack_count   = 0,								\
		 (eval_ptr)->postfix_ptr        = NULL,							\
		 (eval_ptr)->postfix_data_index = 0,								\
		 (eval_ptr)->postfix_data_ptr   = NULL,							\
		 (eval_ptr)->symbol_eval_data   = NULL,							\
		 (eval_ptr)->symbol_eval_func   = NULL,							\
		 (eval_ptr)->return_code        = EEC_SUCCESS,					\
		 (eval_ptr)->error_text[0]      = '\0',							\
		 (eval_ptr))       : (NULL))

#define EEC_INIT_EEC_SYMBOL(symbol_ptr)									\
	(((symbol_ptr) != NULL) ?													\
		((symbol_ptr)->length = 0,												\
		 (symbol_ptr)->name   = NULL,											\
		 EEC_INIT_EEC_POSTFIX(&(symbol_ptr)->postfix),					\
		 EEC_INIT_EEC_DATUM(&(symbol_ptr)->value),						\
		 (symbol_ptr))       : (NULL))

#define EEC_INIT_EEC_FUNC_RESOLVE(func_resolve_ptr)					\
	(((func_resolve_ptr) != NULL) ?											\
		((func_resolve_ptr)->user_count    = 0,							\
		 (func_resolve_ptr)->user_list     = NULL,						\
		 (func_resolve_ptr)->builtin_count = 0,							\
		 (func_resolve_ptr)->builtin_list  = NULL,						\
		 (func_resolve_ptr))       : (NULL))

#define EEC_INIT_EEC_SYMBOL_RESOLVE(symbol_resolve_ptr)				\
	(((symbol_resolve_ptr) != NULL) ?										\
		((symbol_resolve_ptr)->count               = 0,					\
		 (symbol_resolve_ptr)->list                = NULL,				\
		 (symbol_resolve_ptr)->symbol_resolve_func = NULL,				\
		 (symbol_resolve_ptr))       : (NULL))

/*
	ADF NOTE: Need 'memset()' here to prevent Purify UMR warning.
*/
#define EEC_INIT_EEC_CONTROL(control_ptr)									\
	(((control_ptr) != NULL) ?													\
		(memset((control_ptr), '\0', sizeof(*(control_ptr))),			\
		 (control_ptr)->init_head           = 0L,							\
		 (control_ptr)->optimize_flag       = EEC_FALSE,				\
		 (control_ptr)->decimal_point       = '\0',						\
		 (control_ptr)->decimal_point_ptr   = NULL,						\
		 (control_ptr)->sub_expr_alloc      = 0,							\
		 (control_ptr)->sub_expr_list       = NULL,						\
		 (control_ptr)->sub_expr_gran       = 0,							\
		 (control_ptr)->op_alias_count      = 0,							\
		 (control_ptr)->op_alias_list       = NULL,						\
		 (control_ptr)->func_def_count      = 0,							\
		 (control_ptr)->func_def_list       = NULL,						\
		 (control_ptr)->func_resolve_func   = NULL,						\
		 (control_ptr)->symbol_resolve_func = NULL,						\
		 (control_ptr)->symbol_parse_data   = NULL,						\
		 (control_ptr)->symbol_parse_func   = NULL,						\
		 (control_ptr)->symbol_eval_data    = NULL,						\
		 (control_ptr)->symbol_eval_func    = NULL,						\
		 (control_ptr)->init_tail           = 0L,							\
		 EEC_INIT_EEC_EVAL_DATA(&(control_ptr)->eval_data),			\
		 (control_ptr))       : (NULL))

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#define EEC_GET_PACKED_USHORT(ptr, value)	\
	STR_ALIGN_GET_USHORT(ptr, value)
#define EEC_GET_PACKED_UINT(ptr, value)	\
	STR_ALIGN_GET_UINT(ptr, value)
#define EEC_GET_PACKED_ULONG(ptr, value)	\
	STR_ALIGN_GET_ULONG(ptr, value)
#define EEC_GET_PACKED_DOUBLE(ptr, value)	\
	STR_ALIGN_GET_DOUBLE(ptr, value)

#define EEC_SET_PACKED_USHORT(ptr, value)	\
	STR_ALIGN_SET_USHORT(value, ptr)
#define EEC_SET_PACKED_UINT(ptr, value)	\
	STR_ALIGN_SET_UINT(value, ptr)
#define EEC_SET_PACKED_ULONG(ptr, value)	\
	STR_ALIGN_SET_ULONG(value, ptr)
#define EEC_SET_PACKED_DOUBLE(ptr, value)	\
	STR_ALIGN_SET_DOUBLE(value, ptr)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#define ECC_GET_PFIX_NUMBER(ptr, value)									\
	EEC_GET_PACKED_DOUBLE((ptr) + 1, (value))

#define EEC_GET_PFIX_STRING(ptr, length, string)  						\
	(((ptr) != NULL) ?															\
		(EEC_GET_PACKED_UINT((ptr) + 1, (length)),						\
		 *(string) = (ptr) + 1 + sizeof(unsigned int),					\
		 (ptr))       :															\
		(*(length) = 0,															\
		 *(string) = NULL,														\
		 *(string)))

#define EEC_GET_PFIX_FUNCTION(ptr, id, arg_count, length, name)	\
	(((ptr) != NULL) ?															\
		(EEC_GET_PACKED_ULONG((ptr) + 1, (id)),							\
		 EEC_GET_PACKED_USHORT((ptr) + 1 + sizeof(unsigned long), 	\
			(arg_count)),															\
		 EEC_GET_PACKED_USHORT((ptr) + 1 + sizeof(unsigned long) +	\
			sizeof(unsigned short), (length)),								\
		 *(name) = (ptr) + 1 + sizeof(unsigned long) +					\
			sizeof(unsigned short) + sizeof(unsigned short),			\
		 (ptr))       :															\
		(*(id)        = 0L,														\
		 *(arg_count) = 0,														\
		 *(length)    = 0,														\
		 *(name)      = NULL,													\
		 *(name)))

#define EEC_GET_PFIX_SYMBOL(ptr, id, length, name)						\
	(((ptr) != NULL) ?															\
		(EEC_GET_PACKED_ULONG((ptr) + 1, (id)),							\
		 EEC_GET_PACKED_USHORT((ptr) + 1 + sizeof(unsigned long),	\
			(length)),																\
		 *(name) = (ptr) + 1 + sizeof(unsigned long) +					\
			sizeof(unsigned short),												\
		 (ptr))       :															\
		(*(id)        = 0L,														\
		 *(length)    = 0,														\
		 *(name)      = NULL,													\
		 *(name)))
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

typedef struct {
	unsigned int  type;
	unsigned int  length;
	char         *data;
} EEC_POSTFIX;

typedef struct {
	unsigned long expr_spec;
	unsigned int  start_index;
	unsigned int  end_index;
	unsigned int  expr_type;
	EEC_POSTFIX   postfix;
	unsigned char expr_flags;
} EEC_SUB_EXPR;

typedef struct {
	char         *preferred_operator;
	char         *operator_name;
	unsigned int  precedence;
	unsigned int  operator_type;
} EEC_PARSE_CANON_OP;

typedef struct {
	char         *operator_alias;
	unsigned int  operator_alias_length;
	unsigned int  operator_index;
} EEC_PARSE_OP_ALIAS;

typedef struct {
	char         *name;
	unsigned int  value;
} EEC_EXPR_TYPE_LINKAGE;

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define EEC_STACK_GRANULARITY				100

typedef struct {
	unsigned int  length;
	char         *data;
} EEC_DATUM_STRING;

typedef union {
	EEC_DATUM_STRING string;
	double           number;
} EEC_DATUM_VALUE;

typedef struct {
	EEC_DATUM_VALUE datum;
	unsigned int    flags;
} EEC_DATUM;

/*	***********************************************************************	*/

/*	***********************************************************************	*/
struct tag_EEC_EVAL_DATA;
typedef COMPAT_FN_TYPE(int (*EEC_SymbolEvalFunc),
	(struct tag_EEC_EVAL_DATA *eval_ptr, unsigned long symbol_id,
	unsigned int name_length, const char *name_ptr, void *user_data_ptr,
	char *error_text));
typedef COMPAT_FN_TYPE(int (*EEC_SymbolParseFunc),
	(const char *symbol_ptr, unsigned int max_length, void *symbol_parse_data,
	unsigned int *expr_type, unsigned long *expr_spec,
	unsigned int *symbol_length, char *error_text));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/

typedef struct tag_EEC_EVAL_DATA {
	EEC_DATUM          *eval_stack;
	EEC_DATUM          *eval_stack_top;
	jmp_buf             jump_context;
	unsigned int        eval_stack_alloc;
	unsigned int        eval_stack_count;
	const EEC_POSTFIX  *postfix_ptr;
	unsigned int        postfix_data_index;
	char               *postfix_data_ptr;
	void               *symbol_eval_data;
	EEC_SymbolEvalFunc  symbol_eval_func;
	int                 return_code;
	char                error_text[EEC_MAX_ERROR_TEXT];
} EEC_EVAL_DATA;

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

typedef struct {
	char           *func_name;
	unsigned long   func_spec;
	unsigned int    func_type;
	unsigned int    func_type_arg;
	unsigned int    func_min_args;
	unsigned int    func_max_args;
	unsigned int    func_args[EEC_FUNC_MAX_FIXED_ARGS];
	int             volatile_flag;
	void          (*func_ptr)(EEC_EVAL_DATA *control_ptr,
							unsigned int arg_count);
} EEC_FUNC_DEF;

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

typedef struct {
	unsigned int  length;
	char         *name;
	EEC_POSTFIX   postfix;
	EEC_DATUM     value;
} EEC_SYMBOL;

typedef struct {
	unsigned int   count;
	EEC_SYMBOL    *list;
#ifndef NARGS
	int          (*symbol_resolve_func)(const char *formula_ptr,
						unsigned int start_index, unsigned int end_index,
						unsigned int *expr_type,
						unsigned long *expr_spec, unsigned int *current_index,
						char *error_text);
#else
	int          (*symbol_resolve_func)();
#endif /* #ifndef NARGS */
} EEC_SYMBOL_RESOLVE;

typedef struct {
	unsigned int  user_count;
	EEC_FUNC_DEF *user_list;
	unsigned int  builtin_count;
	EEC_FUNC_DEF *builtin_list;
} EEC_FUNC_RESOLVE;

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define EEC_CONTROL_INIT_HEAD				((unsigned long) 1234567890L)
#define EEC_CONTROL_INIT_TAIL				((unsigned long)  987654321L)

typedef struct {
	unsigned long         init_head;
	int                   optimize_flag;
	char                  decimal_point;
	char                 *decimal_point_ptr;
	unsigned int          sub_expr_alloc;
	EEC_SUB_EXPR         *sub_expr_list;
	unsigned int          sub_expr_gran;
	unsigned int          op_alias_count;
	EEC_PARSE_OP_ALIAS   *op_alias_list;
#if 0
/*
	CODE NOTE: To be removed.
*/
	EEC_FUNC_RESOLVE      func_resolve;
	EEC_SYMBOL_RESOLVE    symbol_resolve;
#else
/*
	CODE NOTE: To be removed.
*/
	int                 (*symbol_resolve_func)(const char *formula_ptr,
									unsigned int start_index, unsigned int end_index,
									unsigned int *expr_type,
									unsigned long *expr_spec,
									unsigned int *current_index, char *error_text);
	/* **** */
	unsigned int          func_def_count;
	EEC_FUNC_DEF         *func_def_list;
	int                 (*func_resolve_func)(const char *, const EEC_FUNC_DEF *,
									unsigned int, unsigned int, unsigned int,
									unsigned int *, char *);
#endif /* #if 0 */
	void                 *symbol_parse_data;
	EEC_SymbolParseFunc   symbol_parse_func;
	void                 *symbol_eval_data;
	EEC_SymbolEvalFunc    symbol_eval_func;
	EEC_EVAL_DATA         eval_data;
	unsigned long         init_tail;
} EEC_CONTROL;

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Parse and evaluate function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int EEC_FormulaToValue,
	(unsigned int formula_length, const char *formula_ptr,
	EEC_DATUM *result_ptr, unsigned int *parse_index, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Parse function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int EEC_ParseIt, (EEC_CONTROL *control_ptr,
	unsigned int formula_length, const char *formula_ptr,
	unsigned int *expr_type, EEC_POSTFIX *postfix_ptr,
	unsigned int *parse_index, char *error_text));
COMPAT_FN_DECL(int EEC_ParseItBasic, (unsigned int formula_length,
	const char *formula_ptr, int optimize_flag, const char *decimal_point,
	unsigned int op_alias_count, const EEC_PARSE_OP_ALIAS *op_alias_list,
	unsigned int func_def_count, const EEC_FUNC_DEF *func_def_list,
	int (*func_resolve_func)(const char *, const EEC_FUNC_DEF *, unsigned int,
		unsigned int, unsigned int, unsigned int *, char *),
	EEC_SymbolParseFunc symbol_parse_func, void *symbol_parse_data,
	unsigned int *sub_expr_alloc, EEC_SUB_EXPR **sub_expr_list,
	unsigned int sub_expr_gran, EEC_EVAL_DATA *eval_ptr,
	unsigned int *expr_type, EEC_POSTFIX *postfix_ptr,
	unsigned int *parse_index, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Evaluate function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int EEC_EvalIt, (EEC_CONTROL *control_ptr,
	const EEC_POSTFIX *postfix_ptr, EEC_DATUM *result_ptr, char *error_text));
COMPAT_FN_DECL(int EEC_EvalControl, (const EEC_POSTFIX *postfix_ptr,
	EEC_DATUM *result_ptr, char *error_text));
COMPAT_FN_DECL(int EEC_EvalLoop, (EEC_EVAL_DATA *eval_ptr,
	EEC_DATUM *result_ptr));
COMPAT_FN_DECL(int EEC_EvalBasic, (EEC_EVAL_DATA *eval_ptr));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Basic supporting function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int EEC_GetInfixFormula, (const EEC_POSTFIX *postfix_ptr,
	int space_flag, char **infix_ptr, char *error_text));
COMPAT_FN_DECL(int EEC_StringToHumanString, (unsigned int string_length,
	const char *string_ptr, int quotes_flag, char **out_string,
	char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Built-in function definition prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void EEC_GetBuiltInFuncDefs,
	(unsigned int *func_count, const EEC_FUNC_DEF **func_list));
COMPAT_FN_DECL(int EEC_CopyBuiltInFuncDefs,
	(unsigned int *func_count, EEC_FUNC_DEF **func_list, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Control structure initialization function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int EEC_CreateControl, (EEC_CONTROL *control_ptr,
	char *error_text));
COMPAT_FN_DECL(int EEC_CreateControlBasic, (EEC_CONTROL *control_ptr,
	int optimize_flag, const char *decimal_point, unsigned int sub_expr_gran,
	unsigned int op_alias_count, const EEC_PARSE_OP_ALIAS *op_alias_list,
	unsigned int func_def_count, const EEC_FUNC_DEF *func_def_list,
	int (*func_resolve_func)(const char *, const EEC_FUNC_DEF *, unsigned int,
		unsigned int, unsigned int, unsigned int *, char *),
	EEC_SymbolParseFunc symbol_parse_func, char *error_text));
COMPAT_FN_DECL(int EEC_ControlIsInit, (const EEC_CONTROL *control_ptr));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Copy function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int EEC_COPY_DatumPtr, (const EEC_DATUM *in_ptr,
	EEC_DATUM *out_ptr, char *error_text));
COMPAT_FN_DECL(int EEC_COPY_DatumList, (unsigned int in_count,
	const EEC_DATUM *in_list, unsigned int *out_count, EEC_DATUM **out_list,
	char *error_text));
COMPAT_FN_DECL(int EEC_COPY_FuncDefPtr, (const EEC_FUNC_DEF *in_ptr,
	EEC_FUNC_DEF *out_ptr, char *error_text));
COMPAT_FN_DECL(int EEC_COPY_FuncDefList, (unsigned int in_count,
	const EEC_FUNC_DEF *in_list, unsigned int *out_count,
	EEC_FUNC_DEF **out_list, char *error_text));
COMPAT_FN_DECL(int EEC_COPY_FuncResolvePtr, (const EEC_FUNC_RESOLVE *in_ptr,
	EEC_FUNC_RESOLVE *out_ptr, char *error_text));
COMPAT_FN_DECL(int EEC_COPY_OpAliasPtr, (const EEC_PARSE_OP_ALIAS *in_ptr,
	EEC_PARSE_OP_ALIAS *out_ptr, char *error_text));
COMPAT_FN_DECL(int EEC_COPY_OpAliasList, (unsigned int in_count,
	const EEC_PARSE_OP_ALIAS *in_list, unsigned int *out_count,
	EEC_PARSE_OP_ALIAS **out_list, char *error_text));
COMPAT_FN_DECL(int EEC_COPY_PostFixPtr, (const EEC_POSTFIX *in_ptr,
	EEC_POSTFIX *out_ptr, char *error_text));
COMPAT_FN_DECL(int EEC_COPY_PostFixList, (unsigned int in_count,
	const EEC_POSTFIX *in_list, unsigned int *out_count,
	EEC_POSTFIX **out_list, char *error_text));
COMPAT_FN_DECL(int EEC_COPY_SymbolPtr, (const EEC_SYMBOL *in_ptr,
	EEC_SYMBOL *out_ptr, char *error_text));
COMPAT_FN_DECL(int EEC_COPY_SymbolList, (unsigned int in_count,
	const EEC_SYMBOL *in_list, unsigned int *out_count, EEC_SYMBOL **out_list,
	char *error_text));
COMPAT_FN_DECL(int EEC_COPY_SymbolResolvePtr,
	(const EEC_SYMBOL_RESOLVE *in_ptr, EEC_SYMBOL_RESOLVE *out_ptr,
	char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Clear function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void EEC_CLEAR_SubExprList, (unsigned int sub_expr_count,
	EEC_SUB_EXPR *sub_expr_list));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Free function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void EEC_FREE_Control, (EEC_CONTROL *control_ptr));
COMPAT_FN_DECL(void EEC_FREE_DatumPtr, (EEC_DATUM *ptr));
COMPAT_FN_DECL(void EEC_FREE_DatumList,
	(unsigned int *this_count, EEC_DATUM **this_list));
COMPAT_FN_DECL(void EEC_FREE_EvalData, (EEC_EVAL_DATA *eval_ptr));
COMPAT_FN_DECL(void EEC_FREE_FuncDefPtr, (EEC_FUNC_DEF *ptr));
COMPAT_FN_DECL(void EEC_FREE_FuncDefList,
	(unsigned int *this_count, EEC_FUNC_DEF **this_list));
COMPAT_FN_DECL(void EEC_FREE_FuncResolvePtr, (EEC_FUNC_RESOLVE *ptr));
COMPAT_FN_DECL(void EEC_FREE_OpAliasPtr, (EEC_PARSE_OP_ALIAS *ptr));
COMPAT_FN_DECL(void EEC_FREE_OpAliasList,
	(unsigned int *this_count, EEC_PARSE_OP_ALIAS **this_list));
COMPAT_FN_DECL(void EEC_FREE_PostFixPtr, (EEC_POSTFIX *ptr));
COMPAT_FN_DECL(void EEC_FREE_PostFixList,
	(unsigned int *this_count, EEC_POSTFIX **this_list));
COMPAT_FN_DECL(void EEC_FREE_SymbolPtr, (EEC_SYMBOL *ptr));
COMPAT_FN_DECL(void EEC_FREE_SymbolList,
	(unsigned int *this_count, EEC_SYMBOL **this_list));
COMPAT_FN_DECL(void EEC_FREE_SubExprPtr, (EEC_SUB_EXPR *ptr));
COMPAT_FN_DECL(void EEC_FREE_SubExprList,
	(unsigned int *this_count, EEC_SUB_EXPR **this_list));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Sub-expression emit function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void EEC_EMIT_SubExprList,
	(unsigned int this_count, const EEC_SUB_EXPR *this_list,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void EEC_EMIT_SubExpr, (const EEC_SUB_EXPR *ptr,
	STR_FUNC_TYPE_fprintf  output_function, void *output_control));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Datum emit function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void EEC_EMIT_DatumPtr, (const EEC_DATUM *datum_ptr,
	STR_FUNC_TYPE_fprintf  output_function, void *output_control));
COMPAT_FN_DECL(void EEC_EMIT_DatumStack, (unsigned int datum_count,
	const EEC_DATUM *datum_list, STR_FUNC_TYPE_fprintf  output_function,
	void *output_control));
COMPAT_FN_DECL(void EEC_EMIT_DatumList, (unsigned int datum_count,
	const EEC_DATUM *datum_list, STR_FUNC_TYPE_fprintf  output_function,
	void *output_control));
COMPAT_FN_DECL(void EEC_EMIT_DatumHeader,
	(STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void EEC_EMIT_DatumTrailer,
	(STR_FUNC_TYPE_fprintf output_function, void *output_control));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Post-fix emit function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void EEC_EMIT_PostFix, (const EEC_POSTFIX *postfix_ptr,
	STR_FUNC_TYPE_fprintf  output_function, void *output_control));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Human-readable string emit function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void EEC_EMIT_HumanString, (unsigned int string_length,
	const char *string_ptr, int quotes_flag, unsigned int max_output_chars,
	STR_FUNC_TYPE_fprintf  output_function, void *output_control));
	/*	*****************************************************************	*/

/*	***********************************************************************	*/

#if defined(_MSC_VER) && (_MSC_VER >= 1400)
# pragma warning(pop)
#endif /* #if defined(_MSC_VER) && (_MSC_VER >= 1400) */

#endif /* #ifndef h__EECFUNCS_H__h */

