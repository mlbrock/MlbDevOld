/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Member Data Definition Library (MDDL) Source Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Dumps record data stored in an array of pointers as
								described by MDDL structures.

	Revision History	:	1993-12-09 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <string.h>

#include "mddli.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MDDL_DumpTextIndirect

   SYNOPSIS    :	return_code = MDDL_DumpTextIndirect(type_count,
							type_list, member_count, member_list, record_count,
							record_list,
							record_size, index_flag, reverse_flag, header_flag,
							max_records, lines_per_page, null_string,
							inter_field_sep, intra_field_sep, overflow_char,
							page_sep, record_leader, record_trailer,
							member_spec_string, page_count, format_line_count,
							data_line_count, user_data_ptr, output_function,
							output_control, error_text);

						int                    return_code;

						unsigned int           type_count;

						const DTA_TYPE        *type_list;

						unsigned int           member_count;

						const MDDL            *member_list;

						unsigned int           record_count;

						void                 **record_list;

						unsigned int           record_size;

						int                    index_flag;

						int                    reverse_flag;

						int                    header_flag;

						unsigned int           max_records;

						unsigned int           lines_per_page;

						const char            *null_string;

						const char            *inter_field_sep;

						const char            *intra_field_sep;

						const char            *overflow_char;

						const char            *page_sep;

						const char            *record_leader;

						const char            *record_trailer;

						const char            *member_spec_string;

						unsigned int          *page_count;

						unsigned int          *format_line_count;

						unsigned int          *data_line_count;

						void                  *user_data_ptr;

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;

						char                  *error_text;


   DESCRIPTION :	Dumps the records in text format. The records are pointed
						to by the elements of an array of ''void *''.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``type_count`` is the number of elements in the array
						represented by the ``type_list`` parameter.

						(.) ``type_list`` is an array of ''DTA_TYPE''
						structures which describe a machine architecture in terms
						of the primitive data types available on that architecture.

						(-) If ``type_count`` is ''0'' and ``type_list`` is
						''NULL'', the function will use the built-in primitive
						data type list compiled into the module ``dtadata.c``
						under the names ``DTA_TypeCount`` and
						``DTA_TypeList``.

						(.) ``member_count`` is the number of elements in the array
						``member_list``.

						(.) ``member_list`` is the array of ''MDDL''
						structures which describes the member data of the records
						to be dumped by this function.

						(.) ``record_count`` is the number of records to be dumped
						by this function.

						(.) ``record_list`` s an array po ''void *'' pointers
						to be dumped by this function.

						(.) ``record_size`` is the size of the records.

						(.) ``index_flag`` specifies whether each dumped record is
						to be prepended with its index within ``record_list``.

						(..) If ``index_flag`` is zero, this function will not
						prepend the dumped records with their indices.

						(..) If ``index_flag`` is not zero, this function will
						prepend each dumped record with the 10 character,
						zero-filled index of the record.

						(.) ``reverse_flag`` specifies the order in which
						``record_list`` is to be traversed by this function:

						(..) If ``reverse_flag`` is zero, this function will
						traverse ``record_list`` beginning with element ''0'' and
						ending with element ``record_count`` - ''1''.

						(..) If ``reverse_flag`` is not zero, this function will
						traverse ``record_list`` beginning with element
						``record_count`` - ''1'' and ending with element ''0''.

						(.) ``header_flag`` specifies whether the dumped records
						output by this function is to include a columnar header.

						(..) If ``header_flag`` is zero, this function will not
						include a header in the dumped output.

						(..) If ``header_flag`` is not zero, this function will
						include a header in the dumped output.

						(.) ``max_records`` is the maximum number of records
						to be dumped by this function.

						(-) If ``max_records`` is zero, all records specified by
						``order_dir_list`` will be dumped.

						(.) ``lines_per_page`` is the number of lines to be dumped
						before emitting a ``page_sep`` string to move to the next
						page.

						(-) If ``lines_per_page`` is zero, records will not be
						dumped on a per-page basis.

						(-) ``lines_per_page`` is usually equal to ''60''.

						(.) ``null_string`` is the string to be used to indicate
						that a member of a record contains a ''NULL'' value.

						(.) ``inter_field_sep`` is the string to be used to
						separate columns in the dumped output.

						(-) If ``inter_field_sep`` is ''NULL'' or equal to
						zero-length string, columns will not be separated in the
						dumped output.

						(-) ``inter_field_sep`` is usually equal to a single space
						character.

						(.) ``intra_field_sep`` is the string to be used to
						separate the elements of fields which have an array data
						type or which are comprised of more than one primitive
						data type.

						(-) If ``intra_field_sep`` is ''NULL'' or equal to
						zero-length string, array elements of fields will not be
						separated in the dumped output.

						(-) ``intra_field_sep`` is usually equal to a hyphen (''-'')
						character.

						(.) ``overflow_char`` points to the single character to be
						used if the emitted data should overflow its determined
						field width.

						(-) If ``overflow_char`` is ''NULL'' or is equal to the
						empty string (''""''), the asterisk character (''*'') will
						be used.

						(.) ``page_sep`` is the string to used between pages in
						dumped output.

						(-) If ``page_sep`` is ''NULL'' or equal to zero-length
						string, pages will not be separated in the dumped output.

						(-) ``page_sep`` is usually equal to a form-feed (''\f'')
						character.

						(.) ``record_leader`` is the string which is to be
						prepended to each record dumped by this function.

						(-) ``record_leader`` is usually equal to ''NULL''.

						(.) ``record_trailer`` is the string which is to be
						appended to each record dumped by this function.

						(-) ``record_trailer`` is usually equal to a line-feed
						(''\n'') character.

						(.) ``member_spec_string`` is a string containing a
						comma-separated list of member names to be dumped by this
						function.

						(-) If ``member_spec_string`` is not ''NULL'' it will be
						parsed in order to determine the members to be dumped. The
						members will be dumped in the order specified in the string.
						Member names may be specified more than once in
						``member_spec_string``, in which case they will occur more
						than once in the dumped output.

						(-) If ``member_spec_string`` is ''NULL'', all members in
						the record will be dumped by this function in the order
						they are specified in ``member_list``.

						(.) ``page_count`` points to an ''unsigned int'' into
						which this function will place the number of pages dumped.

						(-) If ``page_count`` is ''NULL'', it will not be
						de-referenced.

						(.) ``format_line_count`` points to an ''unsigned int'' into
						which this function will place the total number of lines
						dumped, including header and footer lines.

						(-) If ``format_line_count`` is ''NULL'', it will not be
						de-referenced.

						(.) ``data_line_count`` points to an ''unsigned int'' into
						which this function will place the number of records
						dumped.

						(-) If ``data_line_count`` is ''NULL'', it will not be
						de-referenced.

						(.) ``user_data_ptr`` is a pointer to ''void'' which the
						application programmer may use in order to attach
						application-specific knowledge to the structure.

						(.) ``output_function`` is a pointer to the function which
						handles output. The function should take arguments of the
						general form:

						<->''int'' ``output_function``(''void *'', ''const char'' ``format_string``, ``...``);

						(-) Functions of this form include the C standard library
						function ``fprintf``. The MFILE memory-mapped library
						function ``mprintf`` may also be used.

						(-) If the ``output_function`` parameter is ''NULL'', the
						function will set it to ``fprintf``.

						(.) ``output_control`` is the pointer which will be used by
						this function as the first parameter to the function
						specified by the ``output_function`` parameter.

						(-) For example, if ``output_function`` points to the
						function ``fprintf``, then ``output_control`` should be
						a pointer to a structure of type ''FILE''.

						(-) If the `` output_control`` parameter is ''NULL'', the
						function will set it to ``stdout``.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''MDDL_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	Returns from this function are as follow:

						(.) ''MDDL_SUCCESS'' if the function completes without
						error. ''MDDL_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero MDDL return codes
						indicative of error.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	MDDL_DumpText
						MDDL_DumpBinary
						MDDL_GetSpecMemberString

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2014 Michael L. Brock

   OUTPUT INDEX:	MDDL_DumpTextIndirect
						Dump Functions:MDDL_DumpTextIndirect
						Member Data Definition Functions:see MDDL

   PUBLISH XREF:	MDDL_DumpTextIndirect

   PUBLISH NAME:	MDDL_DumpTextIndirect

	ENTRY CLASS	:	Dump Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int MDDL_DumpTextIndirect(unsigned int type_count, const DTA_TYPE *type_list,
	unsigned int member_count, const MDDL *member_list,
	unsigned int record_count, void **record_list, unsigned int record_size,
	int index_flag, int reverse_flag, int header_flag, unsigned int max_records,
	unsigned int lines_per_page, const char *null_string,
	const char *inter_field_sep, const char *intra_field_sep,
	const char *overflow_char, const char *page_sep, const char *record_leader,
	const char *record_trailer, const char *member_spec_string,
	unsigned int *page_count, unsigned int *format_line_count,
	unsigned int *data_line_count, void *user_data_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text)
#else
int MDDL_DumpTextIndirect(type_count, type_list, member_count, member_list,
	record_count, record_list, record_size, index_flag, reverse_flag,
	header_flag, max_records, lines_per_page, null_string, inter_field_sep,
	intra_field_sep, overflow_char, page_sep, record_leader, record_trailer,
	member_spec_string, page_count, format_line_count, data_line_count,
	user_data_ptr, output_function, output_control, error_text)
unsigned int           type_count;
const DTA_TYPE        *type_list;
unsigned int           member_count;
const MDDL            *member_list;
unsigned int           record_count;
void                 **record_list;
unsigned int           record_size;
int                    index_flag;
int                    reverse_flag;
int                    header_flag;
unsigned int           max_records;
unsigned int           lines_per_page;
const char            *null_string;
const char            *inter_field_sep;
const char            *intra_field_sep;
const char            *overflow_char;
const char            *page_sep;
const char            *record_leader;
const char            *record_trailer;
const char            *member_spec_string;
unsigned int          *page_count;
unsigned int          *format_line_count;
unsigned int          *data_line_count;
void                  *user_data_ptr;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
char                  *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code;
	unsigned int  tmp_member_count = 0;
	MDDL   *tmp_member_list  = NULL;

	if ((member_spec_string == NULL) || (!(*member_spec_string))) {
		if ((return_code = MDDL_CopyMemberList(member_count, member_list,
			&tmp_member_count, &tmp_member_list, error_text)) !=
			MDDL_SUCCESS)
			goto EXIT_FUNCTION;
	}
	else if ((return_code = MDDL_GetSpecMemberString(member_spec_string,
		member_count, member_list, &tmp_member_count, &tmp_member_list,
		error_text)) != MDDL_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = MDDL_SetAlignArrayList(type_count, type_list,
		tmp_member_count, tmp_member_list, error_text)) != MDDL_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = MDDL_SetDisplayLengthList(type_count, type_list,
		tmp_member_count, tmp_member_list, header_flag,
		(null_string == NULL) ? 0 : strlen(null_string),
		(intra_field_sep == NULL) ? 0 : strlen(intra_field_sep), user_data_ptr,
		error_text)) != MDDL_SUCCESS)
		goto EXIT_FUNCTION;

	MDDL_DumpTextBasic(type_count, type_list, tmp_member_count,
		tmp_member_list, 1, record_count, ((void *) record_list), record_size, index_flag,
		reverse_flag, header_flag, max_records, lines_per_page, null_string,
		inter_field_sep, intra_field_sep, overflow_char, page_sep,
		record_leader, record_trailer, page_count, format_line_count,
		data_line_count, user_data_ptr, output_function, output_control);

EXIT_FUNCTION:

	MDDL_FreeMemberList(&tmp_member_count, &tmp_member_list);

	return(return_code);
}
/*	***********************************************************************	*/

