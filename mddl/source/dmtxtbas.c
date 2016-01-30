/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Member Data Definition Library (MDDL) Source Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Dumps record data stored in an array described by
								MDDL structures.

	Revision History	:	1993-12-09 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include "mddli.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MDDL_DumpTextBasic

   SYNOPSIS    :	void MDDL_DumpTextBasic(type_count, type_list, member_count,
							member_list, record_ptr_flag, record_count, record_list,
							record_size, index_flag, reverse_flag, header_flag,
							max_records, lines_per_page, null_string,
							inter_field_sep, intra_field_sep, overflow_char,
							page_sep, record_leader, record_trailer,
							page_count, format_line_count, data_line_count,
							user_data_ptr, output_function, output_control,
							error_text);

						unsigned int           type_count;

						const DTA_TYPE        *type_list;

						unsigned int           member_count;

						const MDDL            *member_list;

						int                    record_ptr_flag;

						unsigned int           record_count;

						const void            *record_list;

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

						unsigned int          *page_count;

						unsigned int          *format_line_count;

						unsigned int          *data_line_count;

						void                  *user_data_ptr;

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;

   DESCRIPTION :	Dumps records in text format.

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

						(.) ``record_ptr_flag``, if non-zero, indicates that the
						``record_list`` parameter is to be treated as an array
						of ''void'' pointers.

						(.) ``record_count`` is the number of records to be dumped
						by this function.

						(.) ``record_list`` points to the first record to be dumped.

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

   RETURNS     :	Void.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	MDDL_DumpText
						MDDL_DumpBinary
						MDDL_DumpRecord
						MDDL_DumpHeader
						MDDL_DumpTrailer
						MDDL_GetSpecMemberString

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2016 Michael L. Brock

   OUTPUT INDEX:	MDDL_DumpTextBasic
						Dump Functions:MDDL_DumpTextBasic
						Member Data Definition Functions:see MDDL

   PUBLISH XREF:	MDDL_DumpTextBasic

   PUBLISH NAME:	MDDL_DumpTextBasic

	ENTRY CLASS	:	Dump Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MDDL_DumpTextBasic(unsigned int type_count, const DTA_TYPE *type_list,
	unsigned int member_count, const MDDL *member_list, int record_ptr_flag,
	unsigned int record_count, const void *record_list, unsigned int record_size,
	int index_flag, int reverse_flag, int header_flag, unsigned int max_records,
	unsigned int lines_per_page, const char *null_string,
	const char *inter_field_sep, const char *intra_field_sep,
	const char *overflow_char, const char *page_sep, const char *record_leader,
	const char *record_trailer, unsigned int *page_count,
	unsigned int *format_line_count, unsigned int *data_line_count,
	void *user_data_ptr, STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
void MDDL_DumpTextBasic(type_count, type_list, member_count,
	member_list, record_ptr_flag, record_count, record_list, record_size,
	index_flag, reverse_flag, header_flag, max_records, lines_per_page,
	null_string, inter_field_sep, intra_field_sep, overflow_char, page_sep,
	record_leader, record_trailer, page_count, format_line_count,
	data_line_count, user_data_ptr, output_function, output_control)
unsigned int           type_count;
const DTA_TYPE        *type_list;
unsigned int           member_count;
const MDDL            *member_list;
int                    record_ptr_flag;
unsigned int           record_count;
const void            *record_list;
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
unsigned int          *page_count;
unsigned int          *format_line_count;
unsigned int          *data_line_count;
void                  *user_data_ptr;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	unsigned int  line_count = 0;
	unsigned int  count_1;
	int           record_index;
	const void   *record_ptr;
	int           record_index_next;
	unsigned int  tmp_page_count;
	unsigned int  tmp_format_line_count;
	unsigned int  tmp_data_line_count;

	record_size            = (record_ptr_flag) ? sizeof(char *) : record_size;
	page_count             = (page_count        == NULL) ?
		&tmp_page_count : page_count;
	format_line_count      = (format_line_count == NULL) ?
		&tmp_format_line_count : format_line_count;
	data_line_count        = (data_line_count   == NULL) ?
		&tmp_data_line_count : data_line_count;

	*page_count            = 0;
	*format_line_count     = 0;
	*data_line_count       = 0;

	null_string            = (null_string     == NULL) ? "" : null_string;
	inter_field_sep        = (inter_field_sep == NULL) ? "" : inter_field_sep;
	intra_field_sep        = (intra_field_sep == NULL) ? "" : intra_field_sep;
	page_sep               = (page_sep        == NULL) ? "" : page_sep;
	record_leader          = (record_leader   == NULL) ? "" : record_leader;
	record_trailer         = (record_trailer  == NULL) ? "" : record_trailer;

	record_index           = (!reverse_flag) ? 0           : (record_count - 1);
	record_index_next      = (!reverse_flag) ? 1           : -1;

	STR_EMIT_SetDefaults(&output_function, &output_control);

	if (header_flag) {
		MDDL_DumpHeader(member_count, member_list, index_flag,
			inter_field_sep, record_leader, record_trailer, output_function,
			output_control);
		MDDL_DumpTrailer(member_count, member_list, index_flag,
			inter_field_sep, record_leader, record_trailer, output_function,
			output_control);
		(*format_line_count) += 2;
		line_count           += 2;
	}

	*page_count = 1;

	for (count_1 = 0; count_1 < record_count; count_1++,
		record_index += record_index_next) {
		record_ptr = (record_ptr_flag) ?
			((const void *) ((void **) record_list)[record_index]) :
			((const void *) (((char *) record_list) +
			(record_index * record_size)));
		(*output_function)(output_control, "%s", record_leader);
		if (index_flag)
			(*output_function)(output_control, "%010d%s", record_index,
				inter_field_sep);
		MDDL_DumpRecord(type_count, type_list, member_count,
			member_list, record_ptr, null_string, inter_field_sep,
			intra_field_sep, overflow_char, user_data_ptr, output_function,
			output_control);
		(*output_function)(output_control, "%s", record_trailer);
		if (lines_per_page && count_1 && (!(count_1 % lines_per_page)) &&
			((count_1 + 1) < record_count)) {
			if (header_flag) {
				MDDL_DumpTrailer(member_count, member_list, index_flag,
					inter_field_sep, record_leader, record_trailer,
					output_function, output_control);
				(*format_line_count)++;
				line_count++;
			}
			(*output_function)(output_control, "%s", page_sep);
			(*page_count)++;
			if (header_flag) {
				MDDL_DumpHeader(member_count, member_list, index_flag,
					inter_field_sep, record_leader, record_trailer,
					output_function, output_control);
				MDDL_DumpTrailer(member_count, member_list, index_flag,
					inter_field_sep, record_leader, record_trailer,
					output_function, output_control);
				(*format_line_count) += 2;
				line_count           += 2;
			}
		}
		++(*data_line_count);
		if (max_records && (*data_line_count >= max_records))
			break;
	}

	if (header_flag) {
		MDDL_DumpTrailer(member_count, member_list, index_flag,
			inter_field_sep, record_leader, record_trailer,	output_function,
			output_control);
		(*format_line_count)++;
	}
}
/*	***********************************************************************	*/

