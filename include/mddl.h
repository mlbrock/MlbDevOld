/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Member Data Definition Library (MDDL) Include File								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the MDDL library.

	Revision History	:	1993-12-09 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__MDDL_H__h

# define h__MDDL_H__h							1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <dta.h>

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   BASE NAME   :  MDDL Truth Codes

   NAME        :  MDDL Truth Codes

   DESCRIPTION :  Manifest constants used within MDDL to specify the truth
						or falsity of expressions.

						(.) ''MDDL_TRUE''

						(.) ''MDDL_FALSE''

   NOTES       :  The manifest constant ''MDDL_TRUE'' should be defined as
						a non-zero value. Conversely, the manifest constant
						''MDDL_FALSE'' should be defined as zero (''0'').

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:  MDDL_TRUE
						MDDL_FALSE
						MDDL Truth Codes:MDDL_TRUE
						MDDL Truth Codes:MDDL_FALSE
						MDDL Manifest Constants:MDDL_TRUE
						MDDL Manifest Constants:MDDL_FALSE
						MDDL Defines:MDDL_TRUE
						MDDL Defines:MDDL_FALSE
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:  MDDL Truth Codes
						MDDL Truth Code
						MDDL truth codes
						MDDL truth code
						MDDL_TRUE
						MDDL_FALSE

   PUBLISH NAME:	MDDL Truth Codes
						MDDL_TRUE
						MDDL_FALSE

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define MDDL_TRUE								1
#define MDDL_FALSE							0
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   BASE NAME   :	MDDL Return Codes

   NAME        :  MDDL Return Codes

   DESCRIPTION :  The MDDL return codes have the following meanings:

						(.) ''MDDL_SUCCESS'' means that the function invoked
						completed without error. ''MDDL_SUCCESS'' is guaranteed to
						be equal to zero (''0'').

						(.) ''MDDL_FAILURE'' indicates that the function invoked
						encountered a general operation failure. This is the
						'catch-all' error code for those errors which do not fit
						into category of one the other MDDL error codes.

						(.) ''MDDL_BAD_ARGS_FAILURE'' indicates that the
						arguments passed to a function invoked were invalid.

						(.) ''MDDL_MEMORY_FAILURE'' indicates that the memory
						required for operation of the function invoked could not be
						allocated.

						(.) ''MDDL_SYSTEM_FAILURE'' indicates that the function
						invoked encountered a failure of a standard library
						function or a system call.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:  MDDL_SUCCESS
						MDDL_FAILURE
						MDDL_BAD_ARGS_FAILURE
						MDDL_MEMORY_FAILURE
						MDDL_SYSTEM_FAILURE
						MDDL Return Codes:MDDL_SUCCESS
						MDDL Return Codes:MDDL_FAILURE
						MDDL Return Codes:MDDL_BAD_ARGS_FAILURE
						MDDL Return Codes:MDDL_MEMORY_FAILURE
						MDDL Return Codes:MDDL_SYSTEM_FAILURE
						MDDL Manifest Constants:MDDL_SUCCESS
						MDDL Manifest Constants:MDDL_FAILURE
						MDDL Manifest Constants:MDDL_BAD_ARGS_FAILURE
						MDDL Manifest Constants:MDDL_MEMORY_FAILURE
						MDDL Manifest Constants:MDDL_SYSTEM_FAILURE
						MDDL Defines:MDDL_SUCCESS
						MDDL Defines:MDDL_FAILURE
						MDDL Defines:MDDL_BAD_ARGS_FAILURE
						MDDL Defines:MDDL_MEMORY_FAILURE
						MDDL Defines:MDDL_SYSTEM_FAILURE
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:  MDDL_SUCCESS
						MDDL_FAILURE
						MDDL_BAD_ARGS_FAILURE
						MDDL_MEMORY_FAILURE
						MDDL_SYSTEM_FAILURE
						MDDL Return Codes
						MDDL Return Code
						MDDL return codes
						MDDL return code
						MDDL Status Codes
						MDDL Status Code
						MDDL status codes
						MDDL status code
						MDDL Error Codes
						MDDL Error Code
						MDDL error codes
						MDDL error code

   PUBLISH NAME:	MDDL Return Codes
						MDDL return codes
						MDDL_SUCCESS
						MDDL_FAILURE
						MDDL_BAD_ARGS_FAILURE
						MDDL_MEMORY_FAILURE
						MDDL_SYSTEM_FAILURE

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define MDDL_SUCCESS							 0
#define MDDL_FAILURE							-1
#define MDDL_BAD_ARGS_FAILURE				-2
#define MDDL_MEMORY_FAILURE				-3
#define MDDL_SYSTEM_FAILURE				-4
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :  MDDL_MAX_ERROR_TEXT

   DESCRIPTION :  The manifest constant ''MDDL_MAX_ERROR_TEXT'' defines
						the minimum amount of storage which should be allocated to
						hold an error message returned by a MDDL function.

   CAVEATS     :  MDDL error messages can be quite lengthy. Therefore,
						attempting to save space by allocating less than
						''MDDL_MAX_ERROR_TEXT'' bytes to error message buffers
						passed to MDDL functions can lead to overwriting of the
						heap or the stack.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:  MDDL_MAX_ERROR_TEXT
						MDDL Manifest Constants:MDDL_MAX_ERROR_TEXT
						MDDL Defines:MDDL_MAX_ERROR_TEXT
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	MDDL_MAX_ERROR_TEXT

   PUBLISH NAME:	MDDL_MAX_ERROR_TEXT

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define MDDL_MAX_ERROR_TEXT				1024
/*	***********************************************************************	*/

/*
	ADF NOTE: Need ADF comments.
*/
/*	***********************************************************************	*/
#define MDDL_MAX_NAME						31
#define MDDL_MAX_TYPE_SPEC					31
#define MDDL_MAX_DTA_COUNT					((MDDL_MAX_TYPE_SPEC + 1) / 2)

#define MDDL_DTA_EMPTY_LIST		\
	{ {0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0} }
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MDDL

   DESCRIPTION :	The ''MDDL'' structure defines a single datum of a
						structure or record.

						The ''MDDL'' structure is declared as follows:

{|@|}typedef struct tag_MDDL {
	char           name[MDDL_MAX_NAME + 1];
	unsigned int   data_length;
	unsigned int   length;
	unsigned int   offset;
	unsigned int   type_count;
	char           type_spec[MDDL_MAX_TYPE_SPEC + 1];
	unsigned int   align_count;
	DTA            align_list[MDDL_MAX_DTA_COUNT];
	unsigned int   display_length;
	char          *display_name;
	int            dbc_type;
	int          (*length_function)(unsigned int type_count,
							const DTA_TYPE *type_list,
							struct tag_MDDL *member_ptr,
							int header_flag, unsigned int intra_field_length,
							unsigned int null_string_length, void *user_data_ptr,
							char *error_text);
	void         (*dump_function)(unsigned int type_count,
							const DTA_TYPE *type_list,
							const struct tag_MDDL *member_ptr,
							const char *record_ptr, int null_flag,
							const char *intra_field_sep, const char *null_string,
							const char *overflow_char, void *user_data_ptr,
							STR_FUNC_TYPE_fprintf output_function,
							void *output_control);
	int            user_int_1;
	int            user_int_2;
	void          *user_ptr_1;
	void          *user_ptr_2;
} MDDL;

	MEMBERS		:	The members of this structure are as follow:

						(.) ``name`` is an array of ''char'' which contains the name
						of the datum. It is ''MDDL_MAX_NAME'' + ''1''
						characters in length.

						(.) ``data_length`` is an ''unsigned int'' which contains
						the length of the datum which is available for data storage.

						(.) ``length`` is an ''unsigned int'' which contains the
						actual length of the datum. For character columns (such as
						the Sybase ''char'' and ''varchar'' types), the ``length``
						value is ''1'' greater than the ``data_length`` value
						because a single character position is reserved for the
						terminating ASCII ''0'' byte.

						(.) ``offset`` is an ''unsigned int'' which contains
						the offset of the datum within its structure or record.

						(.) ``type_count`` is an ''unsigned int'' which contains
						the number of instantiations of the primitive types
						specified in the ``type_spec`` member which together
						constitute the datum.

						(.) ``type_spec`` is an array of ''char'' which contains
						the primitive alignment specification of the datum in
						string format. This specification may be converted into
						an array ''MDDL'' structures by using it as a parameter
						to such functions as ``MDDL_AlignString``.

						(-) ``type_spec`` is ''MDDL_MAX_TYPE_SPEC'' + ''1''
						characters in length.

						(.) ``align_count`` is an ''unsigned int'' which contains
						the number of elements in ``align_list``.

						(.) ``align_list`` is an array of ''MDDL'' structures.
						When populated with data derived from the ``type_spec``
						member, the elements of this array correspond to the type
						description encoded in the ``type_count`` and ``type_spec``
						members.

						(-) ``align_list`` has ''MDDL_MAX_DTA_COUNT''
						elements, which is sufficient to represent any description
						in ``type_spec``. ''MDDL_MAX_DTA_COUNT'' is defined
						as:

						{|@|}((MDDL_MAX_TYPE_SPEC + 1) / 2)

						This works because each type specification in the
						``type_spec`` member requires one character to represent a
						primitive type, and a single comma character to separate it
						from the next type specification character.

						(.) ``display_length`` ADF NOTE: ADF comment needed here

						(.) ``display_name`` ADF NOTE: ADF comment needed here

						(.) ``dbc_type`` is reserved for use by the DBCFUNCS
						library. It is used to store the facility-specific DBMS
						type.

						(.) ``length_function`` is a pointer to a function which
						ADF NOTE HERE

						(.) ``dump_function`` is a pointer to a function which
						ADF NOTE HERE

						(.) ``user_int_1`` is an ''int'' reserved for use by the
						implementation.

						(.) ``user_int_2`` is an ''int'' reserved for use by the
						implementation.

						(.) ``user_ptr_1`` is a pointer to ''void'' reserved for
						use by the implementation.

						(.) ``user_ptr_2`` is a pointer to ''void'' reserved for
						use by the implementation.

	AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	MDDL
						Alignment Structures:MDDL
						Structures:MDDL
						Data Type Alignment Structures:MDDL

   PUBLISH XREF:	MDDL

   PUBLISH NAME:	MDDL

	ENTRY CLASS	:	Structures and Data Types

EOH */
/*	***********************************************************************	*/
typedef struct tag_MDDL {
	char           name[MDDL_MAX_NAME + 1];
	unsigned int   data_length;
	unsigned int   length;
	unsigned int   offset;
	unsigned int   type_count;
	char           type_spec[MDDL_MAX_TYPE_SPEC + 1];
	unsigned int   align_count;
	DTA            align_list[MDDL_MAX_DTA_COUNT];
	unsigned int   display_length;
	char          *display_name;
	int            dbc_type;
#ifndef NARGS
	int          (*length_function)(unsigned int type_count,
							const DTA_TYPE *type_list,
							struct tag_MDDL *member_ptr,
							int header_flag, unsigned int intra_field_length,
							unsigned int null_string_length, void *user_data_ptr,
							char *error_text);
	void         (*dump_function)(unsigned int type_count,
							const DTA_TYPE *type_list,
							const struct tag_MDDL *member_ptr,
							const void *record_ptr, int null_flag,
							const char *intra_field_sep, const char *null_string,
							const char *overflow_char, void *user_data_ptr,
							STR_FUNC_TYPE_fprintf output_function,
							void *output_control);
#else
	int          (*length_function)();
	void         (*dump_function)();
#endif /* #ifndef NARGS */
	int            user_int_1;
	int            user_int_2;
	void          *user_ptr_1;
	void          *user_ptr_2;
} MDDL;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* Function prototypes for functions defined within 'mddl.a' . . .			*/
/*	***********************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Function prototypes for version functions . . .
		*****************************************************************	*/
COMPAT_FN_DECL(STR_VERSION *MDDL_GetVersion, (STR_VERSION *version_number));
COMPAT_FN_DECL(char        *MDDL_GetVersionString, (char *version_string));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		MDDL generic handling function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int  MDDL_AppendMember, (const MDDL *in_ptr,
	unsigned int *out_count, MDDL **out_list, char *error_text));
COMPAT_FN_DECL(int  MDDL_CopyMember, (const MDDL *in_ptr,
	MDDL *out_ptr, char *error_text));
COMPAT_FN_DECL(int  MDDL_CopyMemberList, (unsigned int in_count,
	const MDDL *in_list, unsigned int *out_count, MDDL **out_list,
	char *error_text));
COMPAT_FN_DECL(void MDDL_FreeMember, (MDDL *member_ptr));
COMPAT_FN_DECL(void MDDL_FreeMemberList, (unsigned int *member_count,
	MDDL **member_list));
COMPAT_FN_DECL(void MDDL_InitMember, (MDDL *member_ptr));
COMPAT_FN_DECL(void MDDL_InitMemberList, (unsigned int member_count,
	MDDL *member_list));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		MDDL emit function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void MDDL_EmitMemberList, (unsigned int count,
	const MDDL *list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(void MDDL_EmitMemberListIdx, (unsigned int count,
	const MDDL *list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(void MDDL_EmitMember, (const MDDL *ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void MDDL_EmitMemberHeader, (
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void MDDL_EmitMemberTrailer, (
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		MDDL manipulation function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int MDDL_GetSpecMemberList, (unsigned int spec_count,
	char **spec_list, unsigned int in_member_count,
	const MDDL *in_member_list, unsigned int *out_member_count,
	MDDL **out_member_list, char *error_text));
COMPAT_FN_DECL(int MDDL_GetSpecMemberString, (const char *spec_string,
	unsigned int in_member_count, const MDDL *in_member_list,
	unsigned int *out_member_count, MDDL **out_member_list,
	char *error_text));
COMPAT_FN_DECL(int MDDL_SetDisplayName, (MDDL *member_ptr,
	const char *display_name, char *error_text));
COMPAT_FN_DECL(int MDDL_CreateDisplayNameList,
	(unsigned int member_count, MDDL *member_list, char *error_text));
COMPAT_FN_DECL(int MDDL_CreateDisplayName, (MDDL *member_ptr,
	char *error_text));
COMPAT_FN_DECL(int MDDL_FixAlignArrayList, (unsigned int type_count,
	const DTA_TYPE *type_list, unsigned int member_count,
	MDDL *member_list, unsigned int *structure_size, char *error_text));
COMPAT_FN_DECL(int MDDL_SetAlignArrayList, (unsigned int type_count,
	const DTA_TYPE *type_list, unsigned int member_count,
	MDDL *member_list, char *error_text));
COMPAT_FN_DECL(int MDDL_SetAlignArray, (unsigned int type_count,
	const DTA_TYPE *type_list, MDDL *member_ptr, char *error_text));
COMPAT_FN_DECL(int MDDL_SetDisplayLengthList, (unsigned int type_count,
	const DTA_TYPE *type_list, unsigned int member_count,
	MDDL *member_list, int header_flag,
	unsigned int null_string_length, unsigned int intra_field_sep_length,
	void *user_data_ptr, char *error_text));
COMPAT_FN_DECL(int MDDL_SetDisplayLength, (unsigned int type_count,
	const DTA_TYPE *type_list, MDDL *member_ptr, int header_flag,
	unsigned int null_string_length, unsigned int intra_field_sep_length,
	void *user_data_ptr, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		MDDL dump function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void MDDL_DumpHeader, (unsigned int member_count,
	const MDDL *member_list, int index_flag, const char *inter_field_sep,
	const char *record_leader, const char *record_trailer,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void MDDL_DumpTrailer, (unsigned int member_count,
	const MDDL *member_list, int index_flag, const char *inter_field_sep,
	const char *record_leader, const char *record_trailer,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(int  MDDL_DumpText, (unsigned int type_count,
	const DTA_TYPE *type_list, unsigned int member_count,
	const MDDL *member_list, unsigned int record_count,
	const void *record_list, unsigned int record_size, int index_flag,
	int reverse_flag, int header_flag, unsigned int max_records,
	unsigned int lines_per_page, const char *null_string,
	const char *inter_field_sep, const char *intra_field_sep,
	const char *overflow_char, const char *page_sep, const char *record_leader,
	const char *record_trailer, const char *member_spec_string,
	unsigned int *page_count, unsigned int *format_line_count,
	unsigned int *data_line_count, void *user_data_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text));
COMPAT_FN_DECL(int  MDDL_DumpTextIndirect, (unsigned int type_count,
	const DTA_TYPE *type_list, unsigned int member_count,
	const MDDL *member_list, unsigned int record_count,
	void **record_list, unsigned int record_size, int index_flag,
	int reverse_flag, int header_flag, unsigned int max_records,
	unsigned int lines_per_page, const char *null_string,
	const char *inter_field_sep, const char *intra_field_sep,
	const char *overflow_char, const char *page_sep, const char *record_leader,
	const char *record_trailer, const char *member_spec_string,
	unsigned int *page_count, unsigned int *format_line_count,
	unsigned int *data_line_count, void *user_data_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text));
COMPAT_FN_DECL(void MDDL_DumpTextBasic, (unsigned int type_count,
	const DTA_TYPE *type_list, unsigned int member_count,
	const MDDL *member_list, int record_ptr_flag,unsigned int record_count,
	const void *record_list, unsigned int record_size, int index_flag,
	int reverse_flag, int header_flag, unsigned int max_records,
	unsigned int lines_per_page, const char *null_string,
	const char *inter_field_sep, const char *intra_field_sep,
	const char *overflow_char, const char *page_sep, const char *record_leader,
	const char *record_trailer, unsigned int *page_count,
	unsigned int *format_line_count, unsigned int *data_line_count,
	void *user_data_ptr, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(void MDDL_DumpRecord, (unsigned int type_count,
	const DTA_TYPE *type_list, unsigned int member_count,
	const MDDL *member_list, const void *record_ptr,
	const char *null_string, const char *inter_field_sep,
	const char *intra_field_sep, const char *overflow_char,
	void *user_data_ptr, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(void MDDL_DumpField, (unsigned int type_count,
	const DTA_TYPE *type_list, const MDDL *member_ptr,
	const void *record_ptr, int null_flag, const char *null_string,
	const char *intra_field_sep, const char *overflow_char,
	void *user_data_ptr, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
	/*	*****************************************************************	*/

/* *********************************************************************** */

#endif /* #ifndef h__MDDL_H__h */

