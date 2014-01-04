/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Specification Parse Facility (SPF) Include File									*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the Specification Parse Facility.
								(SPFFUNCS) Library.

	Revision History	:	1995-08-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__SPFFUNCS_H__h

#define h__SPFFUNCS_H__h							1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <stddef.h>

#include <strfuncs.h>

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* 	The macro 'offsetof' is defined by ANSI C. If it's not available on	*/
/* this system, define it . . .															*/
/* *********************************************************************** */

#ifndef offsetof
# define offsetof(structure_name, member_name) \
	((size_t) &(((structure_name *) 0)->member_name))
#endif /* #ifndef offsetof */

/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define SPF_VERSION					"01.00.00"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define SPF_TRUE								1
#define SPF_FALSE								0

#define SPFFUNCS_TRUE						SPF_TRUE
#define SPFFUNCS_FALSE						SPF_FALSE

#define SPF_SUCCESS							0
#define SPF_FAILURE							-1
#define SPF_BAD_ARGS_FAILURE				-2
#define SPF_MEMORY_FAILURE					-3
#define SPF_SYSTEM_FAILURE					-4
#define SPF_PARSE_FAILURE					-5

#define SPFFUNCS_SUCCESS					SPF_SUCCESS
#define SPFFUNCS_FAILURE					SPF_FAILURE
#define SPFFUNCS_BAD_ARGS_FAILURE		SPF_BAD_ARGS_FAILURE
#define SPFFUNCS_MEMORY_FAILURE			SPF_MEMORY_FAILURE
#define SPFFUNCS_SYSTEM_FAILURE			SPF_SYSTEM_FAILURE
#define SPFFUNCS_PARSE_FAILURE			SPF_PARSE_FAILURE

#define SPF_MAX_ERROR_TEXT					2048

#define SPF_MAX_SPEC_NAME_LENGTH			31

#define SPF_MAX_SPEC_ALIASES				32

#define SPF_PARSE_FILE_FAKE_NAME			"*** BUFFER-FILE ***"

/*	***********************************************************************	*/

/*	***********************************************************************	*/

#define SPF_TYPE_ARRAY						((unsigned int) 0X4000)
#define SPF_TYPE_LIST						((unsigned int) 0X8000)

#define SPF_TYPE_NONE						((unsigned int) 0X0000)
#define SPF_TYPE_CHAR_INT					((unsigned int) 0X0001)
#define SPF_TYPE_U_CHAR_INT				((unsigned int) 0X0002)
#define SPF_TYPE_SHORT_INT					((unsigned int) 0X0003)
#define SPF_TYPE_U_SHORT_INT				((unsigned int) 0X0004)
#define SPF_TYPE_INT							((unsigned int) 0X0005)
#define SPF_TYPE_U_INT						((unsigned int) 0X0006)
#define SPF_TYPE_LONG_INT					((unsigned int) 0X0007)
#define SPF_TYPE_U_LONG_INT				((unsigned int) 0X0008)
#define SPF_TYPE_FLOAT						((unsigned int) 0X0009)
#define SPF_TYPE_DOUBLE						((unsigned int) 0X000A)
#define SPF_TYPE_BOOLEAN					((unsigned int) 0X000B)
#define SPF_TYPE_STR_VERSION				((unsigned int) 0X000C)
#define SPF_TYPE_TEXT						((unsigned int) 0X000D)
#define SPF_TYPE_STRING						((unsigned int) 0X000E)
#define SPF_TYPE_C_STRING					((unsigned int) 0X000F)
#define SPF_TYPE_TEXT_ML					((unsigned int) 0X0010)
#define SPF_TYPE_STRING_ML					((unsigned int) 0X0011)
#define SPF_TYPE_C_STRING_ML				((unsigned int) 0X0012)

#define SPF_TYPE_TEXT_LIST					\
	(SPF_TYPE_TEXT           | SPF_TYPE_LIST)
#define SPF_TYPE_STRING_LIST				\
	(SPF_TYPE_STRING         | SPF_TYPE_LIST)
#define SPF_TYPE_C_STRING_LIST			\
	(SPF_TYPE_C_STRING 		 | SPF_TYPE_LIST)
#define SPF_TYPE_TEXT_ML_LIST				\
	(SPF_TYPE_TEXT_ML        | SPF_TYPE_LIST)
#define SPF_TYPE_STRING_ML_LIST			\
	(SPF_TYPE_STRING_ML      | SPF_TYPE_LIST)
#define SPF_TYPE_C_STRING_ML_LIST		\
	(SPF_TYPE_C_STRING_ML    | SPF_TYPE_LIST)

#define SPF_TYPE_INCLUDE_FILE				((unsigned int) 0X00FF)

#define SPF_TYPE_MIN_USER_TYPE			((unsigned int) 0X0100)
#define SPF_TYPE_MAX_USER_TYPE			((unsigned int) 0X3FFF)

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#define SPF_USER_TYPE(user_number)		\
	(((unsigned int) (user_number)) + SPF_TYPE_MIN_USER_TYPE)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

/*
	ADF NOTE: The 'file' member is not allocated --- is a 'shallow' copy.
*/
typedef struct {
	const char    *file;
	unsigned long  line;
	unsigned int   length;
	char          *text;
	unsigned int   spec_type;
	unsigned int   spec_index;
	unsigned int   list_index;
	int            flags;
} SPF_PARSE;

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
typedef struct {
	unsigned int   file_count;
	char         **file_list;
	unsigned int   include_count;
	char         **include_list;
	unsigned int   current_file_index;
	void          *user_data_ptr;
#ifndef NARGS
	void         (*user_data_free_func)(void *user_data_ptr);
#else
	void         (*user_data_free_func)();
#endif /* #ifndef NARGS */
} SPF_CONTEXT;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

	/*	For the compiler . . .															*/
struct tag_SPF_SPEC;

typedef struct {
#ifndef NARGS
	int (*parse)(SPF_CONTEXT *context_ptr, const struct tag_SPF_SPEC *spec_ptr,
		const SPF_PARSE *parse_ptr, void *parent_ptr, char *error_text);
	int (*post_parse)(SPF_CONTEXT *context_ptr,
		const struct tag_SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
		void *parent_ptr, void *this_ptr, char *error_text);
#else
	int (*parse)();
	int (*post_parse)();
#endif /* #ifndef NARGS */
} SPF_SPEC_FUNCS;

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable:4820)
#endif /* #ifdef _MSC_VER */

typedef struct tag_SPF_SPEC {
	char           name[SPF_MAX_SPEC_NAME_LENGTH + 1];
	char           aliases[SPF_MAX_SPEC_ALIASES][SPF_MAX_SPEC_NAME_LENGTH + 1];
	unsigned int   type;
	unsigned int   min_count;
	unsigned int   max_count;
	unsigned int   min_length;
	unsigned int   max_length;
	double         min_value;
	double         max_value;
	unsigned int   offset_1;
	unsigned int   offset_2;
	SPF_SPEC_FUNCS funcs;
} SPF_SPEC;

#ifdef _MSC_VER
# pragma warning(pop)
#endif /* #ifdef _MSC_VER */

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

typedef struct {
	char          *text;
	unsigned long  value;
} SPF_ENUM;

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Function prototypes . . .															*/
/*	***********************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Parse function prototypes . . .											*/
	/*	*****************************************************************	*/
COMPAT_FN_DECL(int SPF_PARSE_Basic,
	(SPF_CONTEXT *context_ptr, const SPF_SPEC *spec_ptr,
	const SPF_PARSE *parse_ptr, void *parent_ptr, char *error_text));
COMPAT_FN_DECL(int SPF_PARSE_Complex,
	(SPF_CONTEXT *context_ptr, const SPF_SPEC *spec_ptr,
	const SPF_PARSE *parse_ptr, unsigned int spec_count,
	const SPF_SPEC *spec_list, void *parent_ptr, void *this_ptr,
	char *error_text));
COMPAT_FN_DECL(int SPF_PARSE_File,
	(SPF_CONTEXT *context_ptr, const char *file_name,
	const char *def_string, SPF_SPEC_FUNCS *funcs_ptr, unsigned int spec_count,
	const SPF_SPEC *spec_list, char *error_text));
COMPAT_FN_DECL(int SPF_PARSE_STRVersion,
	(SPF_CONTEXT *context_ptr, const SPF_SPEC *spec_ptr,
	const SPF_PARSE *parse_ptr, STR_VERSION *version_ptr, char *error_text));
COMPAT_FN_DECL(int SPF_PARSE_CharInt,
	(const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	char *char_ptr, char *error_text));
COMPAT_FN_DECL(int SPF_PARSE_UCharInt,
	(const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	unsigned char *u_char_ptr, char *error_text));
COMPAT_FN_DECL(int SPF_PARSE_ShortInt,
	(const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	short *short_ptr, char *error_text));
COMPAT_FN_DECL(int SPF_PARSE_UShortInt,
	(const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	unsigned short *u_short_ptr, char *error_text));
COMPAT_FN_DECL(int SPF_PARSE_Int,
	(const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	int *int_ptr, char *error_text));
COMPAT_FN_DECL(int SPF_PARSE_UInt,
	(const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	unsigned int *u_int_ptr, char *error_text));
COMPAT_FN_DECL(int SPF_PARSE_LongInt,
	(const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	long *long_ptr, char *error_text));
COMPAT_FN_DECL(int SPF_PARSE_ULongInt,
	(const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	unsigned long *u_long_ptr, char *error_text));
COMPAT_FN_DECL(int SPF_PARSE_Float,
	(const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	float *float_ptr, char *error_text));
COMPAT_FN_DECL(int SPF_PARSE_Double,
	(const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	double *double_ptr, char *error_text));
COMPAT_FN_DECL(int SPF_PARSE_Boolean,
	(const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	int *boolean_ptr, char *error_text));
COMPAT_FN_DECL(int SPF_PARSE_Enum,
	(const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	unsigned int enum_count, const SPF_ENUM *enum_list,
	unsigned int *found_index, char *error_text));
COMPAT_FN_DECL(int SPF_PARSE_Text,
	(const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	char **text_ptr, char *error_text));
COMPAT_FN_DECL(int SPF_PARSE_String,
	(const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	char **string_ptr, char *error_text));
COMPAT_FN_DECL(int SPF_PARSE_CString,
	(const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	char **string_ptr, char *error_text));
COMPAT_FN_DECL(int SPF_PARSE_TextML,
	(const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	char **text_ptr, char *error_text));
COMPAT_FN_DECL(int SPF_PARSE_StringML,
	(const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	char **string_ptr, char *error_text));
COMPAT_FN_DECL(int SPF_PARSE_CStringML,
	(const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	char **string_ptr, char *error_text));
COMPAT_FN_DECL(int SPF_PARSE_TextList,
	(const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	unsigned int *text_count, char ***text_list, char *error_text));
COMPAT_FN_DECL(int SPF_PARSE_StringList,
	(const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	unsigned int *string_count, char ***string_list, char *error_text));
COMPAT_FN_DECL(int SPF_PARSE_CStringList,
	(const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	unsigned int *string_count, char ***string_list, char *error_text));
COMPAT_FN_DECL(int SPF_PARSE_TextMLList,
	(const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	unsigned int *text_count, char ***text_list, char *error_text));
COMPAT_FN_DECL(int SPF_PARSE_StringMLList,
	(const SPF_SPEC *spec_ptr,
	const SPF_PARSE *parse_ptr, unsigned int *string_count,
	char ***string_list, char *error_text));
COMPAT_FN_DECL(int SPF_PARSE_CStringMLList,
	(const SPF_SPEC *spec_ptr,
	const SPF_PARSE *parse_ptr, unsigned int *string_count,
	char ***string_list, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Parse support function prototypes . . .								*/
	/*	*****************************************************************	*/
COMPAT_FN_DECL(int  SPF_FixMultiLineString,
	(SPF_PARSE *parse_ptr, char *error_text));
COMPAT_FN_DECL(int  SPF_GetListParseDef,
	(const SPF_PARSE *parse_ptr,
	unsigned long *current_line, unsigned int *parse_count,
	SPF_PARSE **parse_list, char *error_text));
COMPAT_FN_DECL(int  SPF_GetListParseString,
	(const char *def_string, const char *file_name,
	unsigned long *current_line, unsigned int *parse_count,
	SPF_PARSE **parse_list, char *error_text));
COMPAT_FN_DECL(int  SPF_GetListParse,
	(unsigned int def_length, const char *def_string,
	const char *file_name, unsigned long *current_line,
	unsigned int *parse_count, SPF_PARSE **parse_list, char *error_text));
COMPAT_FN_DECL(int  SPF_GetSubParse,
	(const SPF_PARSE *in_parse, SPF_PARSE *out_parse,
	char *error_text));
COMPAT_FN_DECL(int  SPF_OrderParseList,
	(unsigned int spec_count, const SPF_SPEC *spec_list,
	unsigned int parse_count, SPF_PARSE *parse_list, char *error_text));
COMPAT_FN_DECL(int  SPF_ReadDefFile,
	(const char *file_name, unsigned int *buffer_length,
	char **buffer_ptr, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Structure manipulation function prototypes . . .					*/
	/*	*****************************************************************	*/
COMPAT_FN_DECL(int  SPF_ALLC_Parse,
	(SPF_PARSE *ptr, char *error_text));
COMPAT_FN_DECL(int  SPF_ALLC_ParseList,
	(unsigned int count, SPF_PARSE *list, char *error_text));
COMPAT_FN_DECL(int  SPF_COPY_Parse,
	(const SPF_PARSE *in_ptr, SPF_PARSE *out_ptr,
	char *error_text));
COMPAT_FN_DECL(int  SPF_COPY_ParseList,
	(unsigned int in_count, const SPF_PARSE *in_list,
	unsigned int *out_count, SPF_PARSE **out_list, char *error_text));
COMPAT_FN_DECL(int  SPF_COPY_Spec,
	(const SPF_SPEC *in_ptr, SPF_SPEC *out_ptr,
	char *error_text));
COMPAT_FN_DECL(int  SPF_COPY_SpecList,
	(unsigned int in_count, const SPF_SPEC *in_list,
	unsigned int *out_count, SPF_SPEC **out_list, char *error_text));
COMPAT_FN_DECL(int  SPF_FIND_Spec,
	(const SPF_SPEC *spec, unsigned int parse_count,
	const SPF_PARSE *parse_list, unsigned int *found_index));
COMPAT_FN_DECL(int  SPF_FIND_SpecName,
	(const char *spec_name, unsigned int parse_count,
	const SPF_PARSE *parse_list, unsigned int *found_index));
COMPAT_FN_DECL(void SPF_FREE_Context,
	(SPF_CONTEXT *ptr));
COMPAT_FN_DECL(void SPF_FREE_ContextList,
	(unsigned int *count, SPF_CONTEXT **list));
COMPAT_FN_DECL(void SPF_FREE_Parse,
	(SPF_PARSE *ptr));
COMPAT_FN_DECL(void SPF_FREE_ParseList,
	(unsigned int *count, SPF_PARSE **list));
COMPAT_FN_DECL(void SPF_FREE_Spec,
	(SPF_SPEC *ptr));
COMPAT_FN_DECL(void SPF_FREE_SpecList,
	(unsigned int *count, SPF_SPEC **list));
COMPAT_FN_DECL(void SPF_INIT_Context,
	(SPF_CONTEXT *ptr));
COMPAT_FN_DECL(void SPF_INIT_ContextList,
	(unsigned int count, SPF_CONTEXT *list));
COMPAT_FN_DECL(void SPF_INIT_Parse,
	(SPF_PARSE *ptr));
COMPAT_FN_DECL(void SPF_INIT_ParseList,
	(unsigned int count, SPF_PARSE *list));
COMPAT_FN_DECL(void SPF_INIT_Spec,
	(SPF_SPEC *ptr));
COMPAT_FN_DECL(void SPF_INIT_SpecList,
	(unsigned int count, SPF_SPEC *list));
COMPAT_FN_DECL(void SPF_INIT_SpecFuncs,
	(SPF_SPEC_FUNCS *ptr));
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		'SPF_PARSE' location function prototypes . . .						*/
	/*	*****************************************************************	*/
COMPAT_FN_DECL(char *SPF_GetLocationLine,
	(const SPF_PARSE *parse_ptr, char *buffer));
COMPAT_FN_DECL(char *SPF_GetLocationFile,
	(const SPF_PARSE *parse_ptr,
	unsigned int max_length, char *buffer));
COMPAT_FN_DECL(char *SPF_GetLocationLineFile,
	(const SPF_PARSE *parse_ptr,
	unsigned int max_length, char *buffer));
COMPAT_FN_DECL(void  SPF_SetContextParse,
	(const SPF_CONTEXT *context_ptr,
	SPF_PARSE *parse_ptr));
COMPAT_FN_DECL(void  SPF_SetContextParseList,
	(const SPF_CONTEXT *context_ptr,
	unsigned int parse_count, SPF_PARSE *parse_list));
	/*	*****************************************************************	*/

/*	***********************************************************************	*/

#endif /* #ifndef h__SPFFUNCS_H__h */

