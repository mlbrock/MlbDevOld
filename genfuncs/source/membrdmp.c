/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	GENFUNCS General Functions Library Source Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Manages the dump logic for 'GEN_MEMBER' structures.

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

#include "genfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_MEMBER_DMP_MemberHeader

   SYNOPSIS    :	void GEN_MEMBER_DMP_MemberHeader(member_count, member_list,
							index_flag, inter_field_sep, record_leader,
							record_trailer, output_function, output_control);

						unsigned int       member_count;

						const GEN_MEMBER  *member_list;

						int                index_flag;

						const char        *inter_field_sep;

						const char        *record_leader;

						const char        *record_trailer;

						void             (*output_function)(void *, char *, ...);

						void              *output_control;

   DESCRIPTION :	Dumps a column header suitable for use with the output
						which results from the function ``GEN_MEMBER_DMP_DumpText``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``member_count`` is the number of elements in the array
						``member_list``.

						(.) ``member_list`` is the array of ''GEN_MEMBER''
						structures which describes the member data of the header
						to be dumped by this function.

						(.) ``index_flag`` specifies whether the header should be
						dumped with a column for the record index.

						(..) If ``index_flag`` is zero, this function will not
						prepend the header with an index column.

						(..) If ``index_flag`` is not zero, this function will
						prepend the header with a 10 character column for the index.

						(.) ``inter_field_sep`` is the string to be used to
						separate columns in the dumped output.

						(-) If ``inter_field_sep`` is ''NULL'' or equal to
						zero-length string, columns will not be separated in the
						dumped output.

						(-) ``inter_field_sep`` is usually equal to a single space
						character.

						(.) ``record_leader`` is the string which is to be
						prepended to the header dumped by this function.

						(-) ``record_leader`` is usually equal to ''NULL''.

						(.) ``record_trailer`` is the string which is to be
						appended to the header dumped by this function.

						(-) ``record_trailer`` is usually equal to a line-feed
						(''\n'') character.

						(.) ``output_function`` is a pointer to the function which
						handles output. The function should take arguments of the
						general form:

						<->``output_function``(void *, ``format_string``, ``...``);

						(-) Functions of this form include the C standard library
						function ``fprintf``. The memory-mapped library function
						``mprintf`` may also be used.

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

   NOTES       :	You can dump a trailer by calling the related function
						``GEN_MEMBER_DMP_MemberTrailer``.

   CAVEATS     :	

   SEE ALSO    :	GEN_MEMBER_DMP_MemberTrailer

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2014 Michael L. Brock

   OUTPUT INDEX:	GEN_MEMBER_DMP_MemberHeader
						Dump Functions:GEN_MEMBER_DMP_MemberHeader
						General Functions:see GENFUNCS

   PUBLISH XREF:	GEN_MEMBER_DMP_MemberHeader

   PUBLISH NAME:	GEN_MEMBER_DMP_MemberHeader

	ENTRY CLASS	:	Dump Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void GEN_MEMBER_DMP_Header(unsigned int member_count,
	const GEN_MEMBER *member_list, int index_flag, const char *inter_field_sep,
	const char *record_leader, const char *record_trailer,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
void GEN_MEMBER_DMP_Header(member_count, member_list, index_flag,
	inter_field_sep, record_leader, record_trailer, output_function,
	output_control)
unsigned int           member_count;
const GEN_MEMBER      *member_list;
int                    index_flag;
const char            *inter_field_sep;
const char            *record_leader;
const char            *record_trailer;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	STR_EMIT_SetDefaults(&output_function, &output_control);

	if (record_leader != NULL)
		(*output_function)(output_control, "%s", record_leader);

	if (index_flag)
		(*output_function)(output_control, "%-*.*s%s", 10, 10, "Index",
			(inter_field_sep != NULL) ? inter_field_sep : "");

	while (member_count--) {
		(*output_function)(output_control, "%-*.*s%s",
			member_list->display_length, member_list->display_length,
			((member_list->display_name != NULL) && *member_list->display_name) ?
			member_list->display_name : member_list->name,
			(member_count && (inter_field_sep != NULL)) ? inter_field_sep : "");
		member_list++;
	}

	if (record_trailer != NULL)
		(*output_function)(output_control, "%s", record_trailer);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_MEMBER_DMP_MemberTrailer

   SYNOPSIS    :	void GEN_MEMBER_DMP_MemberTrailer(member_count, member_list,
							index_flag, inter_field_sep, record_leader,
							record_trailer, output_function, output_control);

						unsigned int       member_count;

						const GEN_MEMBER  *member_list;

						int                index_flag;

						const char        *inter_field_sep;

						const char        *record_leader;

						const char        *record_trailer;

						void             (*output_function)(void *, char *, ...);

						void              *output_control;

   DESCRIPTION :	Dumps a column trailer suitable for use with the output
						which results from the function ``GEN_MEMBER_DMP_DumpText``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``member_count`` is the number of elements in the array
						``member_list``.

						(.) ``member_list`` is the array of ''GEN_MEMBER''
						structures which describes the member data of the header
						to be dumped by this function.

						(.) ``index_flag`` specifies whether the header should be
						dumped with a column for the record index.

						(..) If ``index_flag`` is zero, this function will not
						prepend the header with an index column.

						(..) If ``index_flag`` is not zero, this function will
						prepend the header with a 10 character column for the index.

						(.) ``inter_field_sep`` is the string to be used to
						separate columns in the dumped output.

						(-) If ``inter_field_sep`` is ''NULL'' or equal to
						zero-length string, columns will not be separated in the
						dumped output.

						(-) ``inter_field_sep`` is usually equal to a single space
						character.

						(.) ``record_leader`` is the string which is to be
						prepended to the header dumped by this function.

						(-) ``record_leader`` is usually equal to ''NULL''.

						(.) ``record_trailer`` is the string which is to be
						appended to the header dumped by this function.

						(-) ``record_trailer`` is usually equal to a line-feed
						(''\n'') character.

						(.) ``output_function`` is a pointer to the function which
						handles output. The function should take arguments of the
						general form:

						<->``output_function``(void *, ``format_string``, ``...``);

						(-) Functions of this form include the C standard library
						function ``fprintf``. The memory-mapped library function
						``mprintf`` may also be used.

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

   NOTES       :	You can dump a header by calling the related function
						``GEN_MEMBER_DMP_MemberHeader``.

   CAVEATS     :	

   SEE ALSO    :	GEN_MEMBER_DMP_MemberHeader

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2014 Michael L. Brock

   OUTPUT INDEX:	GEN_MEMBER_DMP_MemberTrailer
						Dump Functions:GEN_MEMBER_DMP_MemberTrailer
						General Functions:see GENFUNCS

   PUBLISH XREF:	GEN_MEMBER_DMP_MemberTrailer

   PUBLISH NAME:	GEN_MEMBER_DMP_MemberTrailer

	ENTRY CLASS	:	Dump Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void GEN_MEMBER_DMP_Trailer(unsigned int member_count,
	const GEN_MEMBER *member_list, int index_flag, const char *inter_field_sep,
	const char *record_leader, const char *record_trailer,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
void GEN_MEMBER_DMP_Trailer(member_count, member_list, index_flag,
	inter_field_sep, record_leader, record_trailer, output_function,
	output_control)
unsigned int           member_count;
const GEN_MEMBER      *member_list;
int                    index_flag;
const char            *inter_field_sep;
const char            *record_leader;
const char            *record_trailer;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	STR_EMIT_SetDefaults(&output_function, &output_control);

	if (record_leader != NULL)
		(*output_function)(output_control, "%s", record_leader);

	if (index_flag) {
		STR_EMIT_Char('-', 10, output_function, output_control);
		(*output_function)(output_control, "%s",
			(inter_field_sep != NULL) ? inter_field_sep : "");
	}

	while (member_count--) {
		STR_EMIT_Char('-', member_list->display_length, output_function,
			output_control);
		(*output_function)(output_control, "%s",
			(member_count && (inter_field_sep != NULL)) ? inter_field_sep : "");
		member_list++;
	}

	if (record_trailer != NULL)
		(*output_function)(output_control, "%s", record_trailer);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_MEMBER_DMP_DumpText

   SYNOPSIS    :	return_code = GEN_MEMBER_DMP_DumpText(type_count, type_list,
							member_count, member_list, record_count, record_list,
							record_size, index_flag, reverse_flag, header_flag,
							max_records, lines_per_page, null_string,
							inter_field_sep, intra_field_sep, overflow_char,
							page_sep, record_leader, record_trailer,
							member_spec_string, page_count, format_line_count,
							data_line_count, user_data_ptr, output_function,
							output_control, error_text);

						int                    return_code;

						unsigned int           type_count;

						const GEN_ALIGN_SPEC  *type_list;

						unsigned int           member_count;

						const GEN_MEMBER      *member_list;

						unsigned int           record_count;

						const void            *record_list;

						unsigned int           record_size;

						int                    reverse_flag;

						int                    index_flag;

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

						void                 (*output_function)(void *, char *, ...);

						void                  *output_control;

						char                  *error_text;

   DESCRIPTION :	Dumps records in text format.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``type_count`` is the number of elements in the array
						represented by the ``type_list`` parameter.

						(.) ``type_list`` is an array of ''GEN_ALIGN_SPEC''
						structures which describe a machine architecture in terms
						of the primitive data types available on that architecture.

						(-) If ``type_count`` is ''0'' and ``type_list`` is
						''NULL'', the function will use the built-in primitive
						data type list compiled into the module ``genalign.c``
						under the names ``GEN_ALIGN_TypeCount`` and
						``GEN_ALIGN_TypeList``.

						(.) ``member_count`` is the number of elements in the array
						``member_list``.

						(.) ``member_list`` is the array of ''GEN_MEMBER''
						structures which describes the member data of the records
						to be dumped by this function.

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

						<->``output_function``(void *, ``format_string``, ``...``);

						(-) Functions of this form include the C standard library
						function ``fprintf``. The memory-mapped library function
						``mprintf`` may also be used.

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
						''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if the function completes without
						error. ''GENFUNCS_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero GENFUNCS return codes
						indicative of error.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	GEN_MEMBER_DMP_DumpTextBasic
						GEN_MEMBER_DMP_DumpBinary
						GEN_MEMBER_GetSpecMemberString

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2014 Michael L. Brock

   OUTPUT INDEX:	GEN_MEMBER_DMP_DumpText
						Dump Functions:GEN_MEMBER_DMP_DumpText
						General Functions:see GENFUNCS

   PUBLISH XREF:	GEN_MEMBER_DMP_DumpText

   PUBLISH NAME:	GEN_MEMBER_DMP_DumpText

	ENTRY CLASS	:	Dump Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_MEMBER_DMP_DumpText(unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, unsigned int member_count,
	const GEN_MEMBER *member_list, unsigned int record_count,
	const void *record_list, unsigned int record_size, int index_flag,
	int reverse_flag, int header_flag, unsigned int max_records,
	unsigned int lines_per_page, const char *null_string,
	const char *inter_field_sep, const char *intra_field_sep,
	const char *overflow_char, const char *page_sep, const char *record_leader,
	const char *record_trailer, const char *member_spec_string,
	unsigned int *page_count, unsigned int *format_line_count,
	unsigned int *data_line_count, void *user_data_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text)
#else
int GEN_MEMBER_DMP_DumpText(type_count, type_list, member_count, member_list,
	record_count, record_list, record_size, index_flag, reverse_flag,
	header_flag, max_records, lines_per_page, null_string, inter_field_sep,
	intra_field_sep, overflow_char, page_sep, record_leader, record_trailer,
	member_spec_string, page_count, format_line_count, data_line_count,
	user_data_ptr, output_function, output_control, error_text)
unsigned int           type_count;
const GEN_ALIGN_SPEC  *type_list;
unsigned int           member_count;
const GEN_MEMBER      *member_list;
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
	GEN_MEMBER   *tmp_member_list  = NULL;

	if ((member_spec_string == NULL) || (!(*member_spec_string))) {
		if ((return_code = GEN_COPY_MemberList(member_count, member_list,
			&tmp_member_count, &tmp_member_list, error_text)) !=
			GENFUNCS_SUCCESS)
			goto EXIT_FUNCTION;
	}
	else if ((return_code = GEN_MEMBER_GetSpecMemberString(member_spec_string,
		member_count, member_list, &tmp_member_count, &tmp_member_list,
		error_text)) != GENFUNCS_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = GEN_MEMBER_SetAlignArrayList(type_count, type_list,
		tmp_member_count, tmp_member_list, error_text)) != GENFUNCS_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = GEN_MEMBER_SetDisplayLengthList(type_count, type_list,
		tmp_member_count, tmp_member_list, header_flag,
		(null_string == NULL) ? 0 : strlen(null_string),
		(intra_field_sep == NULL) ? 0 : strlen(intra_field_sep), user_data_ptr,
		error_text)) != GENFUNCS_SUCCESS)
		goto EXIT_FUNCTION;

	GEN_MEMBER_DMP_DumpTextBasic(type_count, type_list, tmp_member_count,
		tmp_member_list, 0, record_count, record_list, record_size, index_flag,
		reverse_flag, header_flag, max_records, lines_per_page, null_string,
		inter_field_sep, intra_field_sep, overflow_char, page_sep,
		record_leader, record_trailer, page_count, format_line_count,
		data_line_count, user_data_ptr, output_function, output_control);

EXIT_FUNCTION:

	GEN_FREE_MemberList(&tmp_member_count, &tmp_member_list);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_MEMBER_DMP_DumpTextIndirect

   SYNOPSIS    :	return_code = GEN_MEMBER_DMP_DumpTextIndirect(type_count,
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

						const GEN_ALIGN_SPEC  *type_list;

						unsigned int           member_count;

						const GEN_MEMBER      *member_list;

						unsigned int           record_count;

						void                 **record_list;

						unsigned int           record_size;

						int                    reverse_flag;

						int                    index_flag;

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

						void                 (*output_function)(void *, char *, ...);

						void                  *output_control;

						char                  *error_text;

   DESCRIPTION :	Dumps the records in text format. The records are pointed
						to by the elements of an array of ''void *''.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``type_count`` is the number of elements in the array
						represented by the ``type_list`` parameter.

						(.) ``type_list`` is an array of ''GEN_ALIGN_SPEC''
						structures which describe a machine architecture in terms
						of the primitive data types available on that architecture.

						(-) If ``type_count`` is ''0'' and ``type_list`` is
						''NULL'', the function will use the built-in primitive
						data type list compiled into the module ``genalign.c``
						under the names ``GEN_ALIGN_TypeCount`` and
						``GEN_ALIGN_TypeList``.

						(.) ``member_count`` is the number of elements in the array
						``member_list``.

						(.) ``member_list`` is the array of ''GEN_MEMBER''
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

						<->``output_function``(void *, ``format_string``, ``...``);

						(-) Functions of this form include the C standard library
						function ``fprintf``. The memory-mapped library function
						``mprintf`` may also be used.

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
						''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if the function completes without
						error. ''GENFUNCS_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero GENFUNCS return codes
						indicative of error.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	GEN_MEMBER_DMP_DumpText
						GEN_MEMBER_DMP_DumpBinary
						GEN_MEMBER_GetSpecMemberString

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2014 Michael L. Brock

   OUTPUT INDEX:	GEN_MEMBER_DMP_DumpTextIndirect
						Dump Functions:GEN_MEMBER_DMP_DumpTextIndirect
						General Functions:see GENFUNCS

   PUBLISH XREF:	GEN_MEMBER_DMP_DumpTextIndirect

   PUBLISH NAME:	GEN_MEMBER_DMP_DumpTextIndirect

	ENTRY CLASS	:	Dump Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_MEMBER_DMP_DumpTextIndirect(unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, unsigned int member_count,
	const GEN_MEMBER *member_list, unsigned int record_count,
	void **record_list, unsigned int record_size, int index_flag,
	int reverse_flag, int header_flag, unsigned int max_records,
	unsigned int lines_per_page, const char *null_string,
	const char *inter_field_sep, const char *intra_field_sep,
	const char *overflow_char, const char *page_sep, const char *record_leader,
	const char *record_trailer, const char *member_spec_string,
	unsigned int *page_count, unsigned int *format_line_count,
	unsigned int *data_line_count, void *user_data_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text)
#else
int GEN_MEMBER_DMP_DumpTextIndirect(type_count, type_list, member_count, member_list,
	record_count, record_list, record_size, index_flag, reverse_flag,
	header_flag, max_records, lines_per_page, null_string, inter_field_sep,
	intra_field_sep, overflow_char, page_sep, record_leader, record_trailer,
	member_spec_string, page_count, format_line_count, data_line_count,
	user_data_ptr, output_function, output_control, error_text)
unsigned int           type_count;
const GEN_ALIGN_SPEC  *type_list;
unsigned int           member_count;
const GEN_MEMBER      *member_list;
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
	GEN_MEMBER   *tmp_member_list  = NULL;

	if ((member_spec_string == NULL) || (!(*member_spec_string))) {
		if ((return_code = GEN_COPY_MemberList(member_count, member_list,
			&tmp_member_count, &tmp_member_list, error_text)) !=
			GENFUNCS_SUCCESS)
			goto EXIT_FUNCTION;
	}
	else if ((return_code = GEN_MEMBER_GetSpecMemberString(member_spec_string,
		member_count, member_list, &tmp_member_count, &tmp_member_list,
		error_text)) != GENFUNCS_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = GEN_MEMBER_SetAlignArrayList(type_count, type_list,
		tmp_member_count, tmp_member_list, error_text)) != GENFUNCS_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = GEN_MEMBER_SetDisplayLengthList(type_count, type_list,
		tmp_member_count, tmp_member_list, header_flag,
		(null_string == NULL) ? 0 : strlen(null_string),
		(intra_field_sep == NULL) ? 0 : strlen(intra_field_sep), user_data_ptr,
		error_text)) != GENFUNCS_SUCCESS)
		goto EXIT_FUNCTION;

	GEN_MEMBER_DMP_DumpTextBasic(type_count, type_list, tmp_member_count,
		tmp_member_list, 1, record_count, ((void *) record_list), record_size, index_flag,
		reverse_flag, header_flag, max_records, lines_per_page, null_string,
		inter_field_sep, intra_field_sep, overflow_char, page_sep,
		record_leader, record_trailer, page_count, format_line_count,
		data_line_count, user_data_ptr, output_function, output_control);

EXIT_FUNCTION:

	GEN_FREE_MemberList(&tmp_member_count, &tmp_member_list);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_MEMBER_DMP_DumpTextBasic

   SYNOPSIS    :	void GEN_MEMBER_DMP_DumpTextBasic(type_count, type_list,
							member_count, member_list, record_ptr_flag, record_count, record_list,
							record_size, index_flag, reverse_flag, header_flag,
							max_records, lines_per_page, null_string,
							inter_field_sep, intra_field_sep, overflow_char,
							page_sep, record_leader, record_trailer,
							page_count, format_line_count, data_line_count,
							user_data_ptr, output_function, output_control,
							error_text);

						unsigned int           type_count;

						const GEN_ALIGN_SPEC  *type_list;

						unsigned int           member_count;

						const GEN_MEMBER      *member_list;

						int                    record_ptr_flag;

						unsigned int           record_count;

						const void            *record_list;

						unsigned int           record_size;

						int                    reverse_flag;

						int                    index_flag;

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

						void                 (*output_function)(void *, char *, ...);

						void                  *output_control;

   DESCRIPTION :	Dumps records in text format.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``type_count`` is the number of elements in the array
						represented by the ``type_list`` parameter.

						(.) ``type_list`` is an array of ''GEN_ALIGN_SPEC''
						structures which describe a machine architecture in terms
						of the primitive data types available on that architecture.

						(-) If ``type_count`` is ''0'' and ``type_list`` is
						''NULL'', the function will use the built-in primitive
						data type list compiled into the module ``genalign.c``
						under the names ``GEN_ALIGN_TypeCount`` and
						``GEN_ALIGN_TypeList``.

						(.) ``member_count`` is the number of elements in the array
						``member_list``.

						(.) ``member_list`` is the array of ''GEN_MEMBER''
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

						<->``output_function``(void *, ``format_string``, ``...``);

						(-) Functions of this form include the C standard library
						function ``fprintf``. The memory-mapped library function
						``mprintf`` may also be used.

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

   SEE ALSO    :	GEN_MEMBER_DMP_DumpText
						GEN_MEMBER_DMP_DumpBinary
						GEN_MEMBER_DMP_DumpRecord
						GEN_MEMBER_DMP_Header
						GEN_MEMBER_DMP_Trailer
						GEN_MEMBER_GetSpecMemberString

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2014 Michael L. Brock

   OUTPUT INDEX:	GEN_MEMBER_DMP_DumpTextBasic
						Dump Functions:GEN_MEMBER_DMP_DumpTextBasic
						General Functions:see GENFUNCS

   PUBLISH XREF:	GEN_MEMBER_DMP_DumpTextBasic

   PUBLISH NAME:	GEN_MEMBER_DMP_DumpTextBasic

	ENTRY CLASS	:	Dump Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void GEN_MEMBER_DMP_DumpTextBasic(unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, unsigned int member_count,
	const GEN_MEMBER *member_list, int record_ptr_flag,unsigned int record_count,
	const void *record_list, unsigned int record_size, int index_flag,
	int reverse_flag, int header_flag, unsigned int max_records,
	unsigned int lines_per_page, const char *null_string,
	const char *inter_field_sep, const char *intra_field_sep,
	const char *overflow_char, const char *page_sep, const char *record_leader,
	const char *record_trailer, unsigned int *page_count,
	unsigned int *format_line_count, unsigned int *data_line_count,
	void *user_data_ptr, STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
void GEN_MEMBER_DMP_DumpTextBasic(type_count, type_list, member_count,
	member_list, record_ptr_flag, record_count, record_list, record_size,
	index_flag, reverse_flag, header_flag, max_records, lines_per_page,
	null_string, inter_field_sep, intra_field_sep, overflow_char, page_sep,
	record_leader, record_trailer, page_count, format_line_count,
	data_line_count, user_data_ptr, output_function, output_control)
unsigned int           type_count;
const GEN_ALIGN_SPEC  *type_list;
unsigned int           member_count;
const GEN_MEMBER      *member_list;
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
		GEN_MEMBER_DMP_Header(member_count, member_list, index_flag,
			inter_field_sep, record_leader, record_trailer, output_function,
			output_control);
		GEN_MEMBER_DMP_Trailer(member_count, member_list, index_flag,
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
		GEN_MEMBER_DMP_DumpRecord(type_count, type_list, member_count,
			member_list, record_ptr, null_string, inter_field_sep,
			intra_field_sep, overflow_char, user_data_ptr, output_function,
			output_control);
		(*output_function)(output_control, "%s", record_trailer);
		if (lines_per_page && count_1 && (!(count_1 % lines_per_page)) &&
			((count_1 + 1) < record_count)) {
			if (header_flag) {
				GEN_MEMBER_DMP_Trailer(member_count, member_list, index_flag,
					inter_field_sep, record_leader, record_trailer,
					output_function, output_control);
				(*format_line_count)++;
				line_count++;
			}
			(*output_function)(output_control, "%s", page_sep);
			(*page_count)++;
			if (header_flag) {
				GEN_MEMBER_DMP_Header(member_count, member_list, index_flag,
					inter_field_sep, record_leader, record_trailer,
					output_function, output_control);
				GEN_MEMBER_DMP_Trailer(member_count, member_list, index_flag,
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
		GEN_MEMBER_DMP_Trailer(member_count, member_list, index_flag,
			inter_field_sep, record_leader, record_trailer,	output_function,
			output_control);
		(*format_line_count)++;
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_MEMBER_DMP_DumpRecord

   SYNOPSIS    :	void GEN_MEMBER_DMP_DumpRecord(type_count, type_list,
							member_count, member_list, record_ptr, null_string,
							inter_field_sep, intra_field_sep, overflow_char,
							user_data_ptr, output_function, output_control);

						unsigned int           type_count;

						const GEN_ALIGN_SPEC  *type_list;

						unsigned int           member_count;

						const GEN_MEMBER      *member_list;

						const void            *record_ptr;

						const char            *null_string;

						const char            *inter_field_sep;

						const char            *intra_field_sep;

						const char            *overflow_char;

						void                  *user_data_ptr;

						void                 (*output_function)(void *, char *, ...);

						void                  *output_control;

   DESCRIPTION :	Dumps a single record in text format.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``type_count`` is the number of elements in the array
						represented by the ``type_list`` parameter.

						(.) ``type_list`` is an array of ''GEN_ALIGN_SPEC''
						structures which describe a machine architecture in terms
						of the primitive data types available on that architecture.

						(-) If ``type_count`` is ''0'' and ``type_list`` is
						''NULL'', the function will use the built-in primitive
						data type list compiled into the module ``genalign.c``
						under the names ``GEN_ALIGN_TypeCount`` and
						``GEN_ALIGN_TypeList``.

						(.) ``member_count`` is the number of elements in the array
						``member_list``.

						(.) ``member_list`` is the array of ''GEN_MEMBER''
						structures which describes the member data of the record
						to be dumped by this function.

						(.) ``record_ptr`` points to the record to be dumped.

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

						(.) ``user_data_ptr`` is a pointer to ''void'' which the
						application programmer may use in order to attach
						application-specific knowledge to the structure.

						(.) ``output_function`` is a pointer to the function which
						handles output. The function should take arguments of the
						general form:

						<->``output_function``(void *, ``format_string``, ``...``);

						(-) Functions of this form include the C standard library
						function ``fprintf``. The memory-mapped library function
						``mprintf`` may also be used.

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

   NOTES       :	This function is usually called from
						''GEN_MEMBER_DMP_DumpTextBasic''.

   CAVEATS     :

   SEE ALSO    :	GEN_MEMBER_DMP_DumpField

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2014 Michael L. Brock

   OUTPUT INDEX:	GEN_MEMBER_DMP_DumpRecord
						Cache Functions:GEN_MEMBER_DMP_DumpRecord
						General Functions:see GENFUNCS

   PUBLISH XREF:	GEN_MEMBER_DMP_DumpRecord

   PUBLISH NAME:	GEN_MEMBER_DMP_DumpRecord

	ENTRY CLASS	:	Dump Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void GEN_MEMBER_DMP_DumpRecord(unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, unsigned int member_count,
	const GEN_MEMBER *member_list, const void *record_ptr,
	const char *null_string, const char *inter_field_sep,
	const char *intra_field_sep, const char *overflow_char,
	void *user_data_ptr, STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
void GEN_MEMBER_DMP_DumpRecord(type_count, type_list, member_count,
	member_list, record_ptr, null_string, inter_field_sep, intra_field_sep,
	overflow_char, user_data_ptr, output_function, output_control)
unsigned int           type_count;
const GEN_ALIGN_SPEC  *type_list;
unsigned int           member_count;
const GEN_MEMBER      *member_list;
const void            *record_ptr;
const char            *null_string;
const char            *inter_field_sep;
const char            *intra_field_sep;
const char            *overflow_char;
void                  *user_data_ptr;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;

	STR_EMIT_SetDefaults(&output_function, &output_control);

	for (count_1 = 0; count_1 < member_count; count_1++) {
		if (count_1 && (inter_field_sep != NULL) && *inter_field_sep)
			(*output_function)(output_control, "%s", inter_field_sep);
		GEN_MEMBER_DMP_DumpField(type_count, type_list, member_list + count_1,
			record_ptr, 0, null_string, intra_field_sep, overflow_char,
			user_data_ptr, output_function, output_control);
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_MEMBER_DMP_DumpField

   SYNOPSIS    :	void GEN_MEMBER_DMP_DumpField(type_count, type_list,
							member_ptr, record_ptr, null_flag, intra_field_sep,
							null_string, overflow_char, user_data_ptr,
							output_function, output_control);

						unsigned int           type_count;

						const GEN_ALIGN_SPEC  *type_list;

						const GEN_MEMBER      *member_ptr;

						const void            *record_ptr;

						int                    null_flag;

						const char            *null_string;

						const char            *intra_field_sep;

						const char            *overflow_char;

						void                  *user_data_ptr;

						void                 (*output_function)(void *, char *, ...);

						void                  *output_control;

   DESCRIPTION :	Dumps a single field in text format.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``type_count`` is the number of elements in the array
						represented by the ``type_list`` parameter.

						(.) ``type_list`` is an array of ''GEN_ALIGN_SPEC''
						structures which describe a machine architecture in terms
						of the primitive data types available on that architecture.

						(-) If ``type_count`` is ''0'' and ``type_list`` is
						''NULL'', the function will use the built-in primitive
						data type list compiled into the module ``genalign.c``
						under the names ``GEN_ALIGN_TypeCount`` and
						``GEN_ALIGN_TypeList``.

						(.) ``member_ptr`` points to the ''GEN_MEMBER'' structure
						which describes the member data within the record to be
						dumped by this function.

						(.) ``record_ptr`` points to the record which contains the
						member data to be dumped.

						(.) ``null_flag`` specifies how ''NULL'' fields are to be
						dumped by the program.

						(..) If ``null_flag`` is zero, ''NULL'' fields will have
						no special handling --- that is, character fields will be
						dumped as spaces and numeric fields will be dumped as the
						value ''0'' (or ''0.0000'' for floating-point numeric
						fields).

						(..) If ``null_flag`` is non-zero, this function will take
						one of the following actions:

						(...) If ``null_string`` is a not ''NULL'', ''NULL'' fields
						will be dumped as the string contained within
						``null_string``.

						(...) If ``null_string`` is ''NULL'', ''NULL'' fields will
						be dumped as a sufficient number of spaces to align the
						field with its neighbors.

						(.) ``null_string`` is the string to be used to indicate
						that a member of a record contains a ''NULL'' value. See
						the description of the ``null_flag`` parameter (above) for
						further details.

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

						(.) ``user_data_ptr`` is a pointer to ''void'' which the
						application programmer may use in order to attach
						application-specific knowledge to the structure.

						(.) ``output_function`` is a pointer to the function which
						handles output. The function should take arguments of the
						general form:

						<->``output_function``(void *, ``format_string``, ``...``);

						(-) Functions of this form include the C standard library
						function ``fprintf``. The memory-mapped library function
						``mprintf`` may also be used.

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

   NOTES       :	This function is usually called from
						''GEN_MEMBER_DMP_DumpRecord''.

   CAVEATS     :	

   SEE ALSO    :	GEN_MEMBER_DMP_DumpRecord

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2014 Michael L. Brock

   OUTPUT INDEX:	GEN_MEMBER_DMP_DumpField
						Dump Functions:GEN_MEMBER_DMP_DumpField
						General Functions:see GENFUNCS

   PUBLISH XREF:	GEN_MEMBER_DMP_DumpField

   PUBLISH NAME:	GEN_MEMBER_DMP_DumpField

	ENTRY CLASS	:	Dump Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void GEN_MEMBER_DMP_DumpField(unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, const GEN_MEMBER *member_ptr,
	const void *record_ptr, int null_flag, const char *null_string,
	const char *intra_field_sep, const char *overflow_char,
	void *user_data_ptr, STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
void GEN_MEMBER_DMP_DumpField(type_count, type_list, member_ptr, record_ptr,
	null_flag, null_string, intra_field_sep, overflow_char, user_data_ptr,
	output_function, output_control)
unsigned int           type_count;
const GEN_ALIGN_SPEC  *type_list;
const GEN_MEMBER      *member_ptr;
const void            *record_ptr;
int                    null_flag;
const char            *intra_field_sep;
const char            *null_string;
const char            *overflow_char;
void                  *user_data_ptr;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	unsigned int     output_length = 0;
	unsigned int     intra_sep_length;
	unsigned int     count_1;
	unsigned int     count_2;
	const void      *data_ptr;
	const GEN_ALIGN *align_ptr;
	char             printf_buffer[1024];

	STR_EMIT_SetDefaults(&output_function, &output_control);

	if ((!type_count) && (type_list == NULL)) {
		type_count = GEN_ALIGN_TypeCount;
		type_list  = GEN_ALIGN_TypeList;
	}

	intra_sep_length = ((intra_field_sep != NULL) && *intra_field_sep) ?
		strlen(intra_field_sep) : 0;

	overflow_char    = (overflow_char == NULL) ? "*" : overflow_char;

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		We may be instructed to handle NULL fields specially . . .		*/
	/*	*****************************************************************	*/
	if (null_flag) {
		(*output_function)(output_control, "%-*.*s",
			member_ptr->display_length, member_ptr->display_length,
			(null_string == NULL) ? "" : null_string);
		return;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		This member may have its own dump function . . .					*/
	/*	*****************************************************************	*/
	if ((member_ptr->dump_function != NULL) &&
		(member_ptr->dump_function != GEN_MEMBER_DMP_DumpField)) {
		(*member_ptr->dump_function)(type_count, type_list, member_ptr,
			record_ptr, null_flag, intra_field_sep, null_string, overflow_char,
			user_data_ptr, output_function, output_control);
		return;
	}
	/*	*****************************************************************	*/

	for (count_1 = 0, align_ptr = member_ptr->align_list;
		count_1 < member_ptr->align_count; count_1++, align_ptr++) {
		data_ptr = ((const void *) (((char *) record_ptr) + member_ptr->offset));
		if (count_1 && (intra_field_sep != NULL) && *intra_field_sep) {
			(*output_function)(output_control, "%s", intra_field_sep);
			output_length += intra_sep_length;
		}
		if (align_ptr->type == GEN_C_ALIGN_unsigned_byte) {
			(*output_function)(output_control, "0X");
			for (count_2 = 0; count_2 < align_ptr->array_length; count_2++)
				(*output_function)(output_control, "%02X",
					((unsigned int) ((unsigned char *) data_ptr)[count_2]));
			output_length += 2 + (align_ptr->array_length * 2);
		}
		else if ((align_ptr->type == GEN_C_ALIGN_unsigned_char) ||
			(align_ptr->type == GEN_C_ALIGN_char)) {
			(*output_function)(output_control, "%-*.*s",
				align_ptr->array_length - 1, align_ptr->array_length - 1,
				data_ptr);
			output_length += align_ptr->array_length - 1;
		}
		else if ((!count_1) && (member_ptr->align_count == 1) &&
			(align_ptr->array_length == 1)) {
			if ((member_ptr->display_length - output_length) >
				type_list[align_ptr->type].printf_length) {
				STR_EMIT_Char(' ',
					(member_ptr->display_length - output_length) -
					type_list[align_ptr->type].printf_length,
					output_function, output_control);
				output_length += (member_ptr->display_length - output_length) -
					type_list[align_ptr->type].printf_length;
			}
			switch (align_ptr->type) {
				case GEN_C_ALIGN_short				:
					(*output_function)(output_control,
						type_list[align_ptr->type].printf_format,
						((int) *((short *) data_ptr)));
					output_length += type_list[align_ptr->type].printf_length;
					break;
				case GEN_C_ALIGN_unsigned_short	:
					(*output_function)(output_control,
						type_list[align_ptr->type].printf_format,
						((unsigned int) *((unsigned short *) data_ptr)));
					output_length += type_list[align_ptr->type].printf_length;
					break;
				case GEN_C_ALIGN_int					:
					(*output_function)(output_control,
						type_list[align_ptr->type].printf_format,
						*((int *) data_ptr));
					output_length += type_list[align_ptr->type].printf_length;
					break;
				case GEN_C_ALIGN_unsigned_int		:
					(*output_function)(output_control,
						type_list[align_ptr->type].printf_format,
						*((unsigned int *) data_ptr));
					output_length += type_list[align_ptr->type].printf_length;
					break;
				case GEN_C_ALIGN_long				:
					(*output_function)(output_control,
						type_list[align_ptr->type].printf_format,
						*((long *) data_ptr));
					output_length += type_list[align_ptr->type].printf_length;
					break;
				case GEN_C_ALIGN_unsigned_long	:
					(*output_function)(output_control,
						type_list[align_ptr->type].printf_format,
						*((unsigned long *) data_ptr));
					output_length += type_list[align_ptr->type].printf_length;
					break;
				case GEN_C_ALIGN_float				:
					sprintf(printf_buffer,
						type_list[align_ptr->type].printf_format,
						*((float *) data_ptr));
					if (type_list[align_ptr->type].printf_length >=
						strlen(printf_buffer))
						(*output_function)(output_control, "%*.*s",
							type_list[align_ptr->type].printf_length,
							type_list[align_ptr->type].printf_length,
							printf_buffer);
					else
						STR_EMIT_Char(*overflow_char,
							type_list[align_ptr->type].printf_length,
							output_function, output_control);
					output_length += type_list[align_ptr->type].printf_length;
					break;
				case GEN_C_ALIGN_double				:
					sprintf(printf_buffer,
						type_list[align_ptr->type].printf_format,
						*((double *) data_ptr));
					if (type_list[align_ptr->type].printf_length >=
						strlen(printf_buffer))
						(*output_function)(output_control, "%*.*s",
							type_list[align_ptr->type].printf_length,
							type_list[align_ptr->type].printf_length,
							printf_buffer);
					else
						STR_EMIT_Char(*overflow_char,
							type_list[align_ptr->type].printf_length,
							output_function, output_control);
					output_length += type_list[align_ptr->type].printf_length;
					break;
				default									:
					break;
			}
		}
		else {
			for (count_2 = 0; count_2 < align_ptr->array_length; count_2++) {
				if (count_2 && (intra_field_sep != NULL) && *intra_field_sep) {
					(*output_function)(output_control, "%s", intra_field_sep);
					output_length += intra_sep_length;
				}
				switch (align_ptr->type) {
					case GEN_C_ALIGN_short				:
						(*output_function)(output_control,
							type_list[align_ptr->type].printf_format,
							((int) *((short *) data_ptr)));
						output_length += type_list[align_ptr->type].printf_length;
						break;
					case GEN_C_ALIGN_unsigned_short	:
						(*output_function)(output_control,
							type_list[align_ptr->type].printf_format,
							((unsigned int) *((unsigned short *) data_ptr)));
						output_length += type_list[align_ptr->type].printf_length;
						break;
					case GEN_C_ALIGN_int					:
						(*output_function)(output_control,
							type_list[align_ptr->type].printf_format,
							*((int *) data_ptr));
						output_length += type_list[align_ptr->type].printf_length;
						break;
					case GEN_C_ALIGN_unsigned_int		:
						(*output_function)(output_control,
							type_list[align_ptr->type].printf_format,
							*((unsigned int *) data_ptr));
						output_length += type_list[align_ptr->type].printf_length;
						break;
					case GEN_C_ALIGN_long				:
						(*output_function)(output_control,
							type_list[align_ptr->type].printf_format,
							*((long *) data_ptr));
						output_length += type_list[align_ptr->type].printf_length;
						break;
					case GEN_C_ALIGN_unsigned_long	:
						(*output_function)(output_control,
							type_list[align_ptr->type].printf_format,
							*((unsigned long *) data_ptr));
						output_length += type_list[align_ptr->type].printf_length;
						break;
					case GEN_C_ALIGN_float				:
						sprintf(printf_buffer,
							type_list[align_ptr->type].printf_format,
							*((float *) data_ptr));
						if (type_list[align_ptr->type].printf_length >=
							strlen(printf_buffer))
							(*output_function)(output_control, "%*.*s",
								type_list[align_ptr->type].printf_length,
								type_list[align_ptr->type].printf_length,
								printf_buffer);
						else
							STR_EMIT_Char(*overflow_char,
								type_list[align_ptr->type].printf_length,
								output_function, output_control);
						output_length += type_list[align_ptr->type].printf_length;
						break;
					case GEN_C_ALIGN_double				:
						sprintf(printf_buffer,
							type_list[align_ptr->type].printf_format,
							*((double *) data_ptr));
						if (type_list[align_ptr->type].printf_length >=
							strlen(printf_buffer))
							(*output_function)(output_control, "%*.*s",
								type_list[align_ptr->type].printf_length,
								type_list[align_ptr->type].printf_length,
								printf_buffer);
						else
							STR_EMIT_Char(*overflow_char,
								type_list[align_ptr->type].printf_length,
								output_function, output_control);
						output_length += type_list[align_ptr->type].printf_length;
						break;
					default									:
						break;
				}
				data_ptr = ((const void *) (((const char *) data_ptr) +
					type_list[align_ptr->type].type_length));
			}
		}
	}

	if (member_ptr->display_length > output_length)
		STR_EMIT_Char(' ', member_ptr->display_length - output_length,
			output_function, output_control);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

static const GEN_MEMBER   TEST_List[] = {
	{
		"name",
		STR_sizeof(GEN_MEMBER, name) - 1,
		STR_sizeof(GEN_MEMBER, name),
		offsetof(GEN_MEMBER, name),
		STR_sizeof(GEN_MEMBER, name) - 1,
		"c",
		0,
		GEN_MEMBER_ALIGN_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
	{
		"data_length",
		STR_sizeof(GEN_MEMBER, data_length),
		STR_sizeof(GEN_MEMBER, data_length),
		offsetof(GEN_MEMBER, data_length),
		1,
		"I",
		0,
		GEN_MEMBER_ALIGN_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
	{
		"length",
		STR_sizeof(GEN_MEMBER, length),
		STR_sizeof(GEN_MEMBER, length),
		offsetof(GEN_MEMBER, length),
		1,
		"I",
		0,
		GEN_MEMBER_ALIGN_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
	{
		"offset",
		STR_sizeof(GEN_MEMBER, offset),
		STR_sizeof(GEN_MEMBER, offset),
		offsetof(GEN_MEMBER, offset),
		1,
		"I",
		0,
		GEN_MEMBER_ALIGN_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
	{
		"type_count",
		STR_sizeof(GEN_MEMBER, type_count),
		STR_sizeof(GEN_MEMBER, type_count),
		offsetof(GEN_MEMBER, type_count),
		1,
		"I",
		0,
		GEN_MEMBER_ALIGN_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
	{
		"type_spec",
		STR_sizeof(GEN_MEMBER, type_spec) - 1,
		STR_sizeof(GEN_MEMBER, type_spec),
		offsetof(GEN_MEMBER, type_spec),
		STR_sizeof(GEN_MEMBER, type_spec) - 1,
		"c",
		0,
		GEN_MEMBER_ALIGN_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
	{
		"align_count",
		STR_sizeof(GEN_MEMBER, align_count),
		STR_sizeof(GEN_MEMBER, align_count),
		offsetof(GEN_MEMBER, align_count),
		1,
		"I",
		0,
		GEN_MEMBER_ALIGN_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
/*
	{
		"align_list",
		STR_sizeof(GEN_MEMBER, align_list),
		STR_sizeof(GEN_MEMBER, align_list),
		offsetof(GEN_MEMBER, align_list),
		GEN_MEMBER_MAX_ALIGN_COUNT,
		"I[4]",
		0,
		GEN_MEMBER_ALIGN_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
*/
	{
		"display_length",
		STR_sizeof(GEN_MEMBER, display_length),
		STR_sizeof(GEN_MEMBER, display_length),
		offsetof(GEN_MEMBER, display_length),
		1,
		"I",
		0,
		GEN_MEMBER_ALIGN_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
/*
	{
		"display_name",
		STR_sizeof(GEN_MEMBER, display_name),
		STR_sizeof(GEN_MEMBER, display_name),
		offsetof(GEN_MEMBER, display_name),
		STR_sizeof(GEN_MEMBER, display_name),
		"B",
		0,
		GEN_MEMBER_ALIGN_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
*/
	{
		"dbc_type",
		STR_sizeof(GEN_MEMBER, dbc_type),
		STR_sizeof(GEN_MEMBER, dbc_type),
		offsetof(GEN_MEMBER, dbc_type),
		1,
		"i",
		0,
		GEN_MEMBER_ALIGN_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
	{
		"length_function",
		STR_sizeof(GEN_MEMBER, length_function),
		STR_sizeof(GEN_MEMBER, length_function),
		offsetof(GEN_MEMBER, length_function),
		STR_sizeof(GEN_MEMBER, length_function),
		"B",
		0,
		GEN_MEMBER_ALIGN_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
	{
		"dump_function",
		STR_sizeof(GEN_MEMBER, dump_function),
		STR_sizeof(GEN_MEMBER, dump_function),
		offsetof(GEN_MEMBER, dump_function),
		STR_sizeof(GEN_MEMBER, dump_function),
		"B",
		0,
		GEN_MEMBER_ALIGN_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
	{
		"user_int_1",
		STR_sizeof(GEN_MEMBER, user_int_1),
		STR_sizeof(GEN_MEMBER, user_int_1),
		offsetof(GEN_MEMBER, user_int_1),
		1,
		"i",
		0,
		GEN_MEMBER_ALIGN_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
	{
		"user_int_2",
		STR_sizeof(GEN_MEMBER, user_int_2),
		STR_sizeof(GEN_MEMBER, user_int_2),
		offsetof(GEN_MEMBER, user_int_2),
		1,
		"i",
		0,
		GEN_MEMBER_ALIGN_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
	{
		"user_ptr_1",
		STR_sizeof(GEN_MEMBER, user_ptr_1),
		STR_sizeof(GEN_MEMBER, user_ptr_1),
		offsetof(GEN_MEMBER, user_ptr_1),
		STR_sizeof(GEN_MEMBER, user_ptr_1),
		"B",
		0,
		GEN_MEMBER_ALIGN_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
	{
		"user_ptr_2",
		STR_sizeof(GEN_MEMBER, user_ptr_2),
		STR_sizeof(GEN_MEMBER, user_ptr_2),
		offsetof(GEN_MEMBER, user_ptr_2),
		STR_sizeof(GEN_MEMBER, user_ptr_2),
		"B",
		0,
		GEN_MEMBER_ALIGN_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	}
};

static const unsigned int TEST_Count  =
	sizeof(TEST_List) / sizeof(TEST_List[0]);

COMPAT_FN_DECL(int main, (void));

int main()
{
	int           return_code;
	unsigned int  member_count = 0;
	GEN_MEMBER   *member_list  = NULL;
	char          error_text[GENFUNCS_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'GEN_MEMBER_DMP_DumpText()'\n");
	fprintf(stderr, "---- ------- --- ---------------------------\n\n");

	if ((return_code = GEN_COPY_MemberList(TEST_Count, TEST_List,
		&member_count, &member_list, error_text)) != GENFUNCS_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = GEN_MEMBER_SetAlignArrayList(0, NULL, member_count,
		member_list, error_text)) != GENFUNCS_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = GEN_MEMBER_CreateDisplayNameList(member_count,
		member_list, error_text)) != GENFUNCS_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = GEN_MEMBER_SetDisplayLengthList(0, NULL, member_count,
		member_list, GENFUNCS_TRUE, strlen("*NULL*"), strlen("-"), NULL,
		error_text)) != GENFUNCS_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = GEN_MEMBER_DMP_DumpText(0, NULL, member_count,
		member_list, member_count, ((const char *) member_list),
		sizeof(*member_list), GENFUNCS_TRUE, GENFUNCS_FALSE, GENFUNCS_TRUE, 0,
		64, "*NULL*", " ", "-", "*", "\f", NULL, "\n", NULL, NULL, NULL, NULL,
		NULL, NULL, NULL, error_text)) != GENFUNCS_SUCCESS)
		goto EXIT_FUNCTION;

	STR_EMIT_CharLine('=', 78, NULL, NULL);

	if ((return_code = GEN_MEMBER_SetDisplayLengthList(0, NULL, member_count,
		member_list, GENFUNCS_TRUE, strlen("*NULL*"), strlen("-"), NULL,
		error_text)) != GENFUNCS_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = GEN_MEMBER_DMP_DumpText(0, NULL, member_count,
		member_list, member_count, ((const char *) member_list),
		sizeof(*member_list), GENFUNCS_TRUE, GENFUNCS_FALSE, GENFUNCS_TRUE, 0,
		64, "*NULL*", " ", "-", "*", "\f", NULL, "\n",
		"name,data_length,length,offset",
		NULL, NULL, NULL, NULL, NULL, NULL, error_text)) != GENFUNCS_SUCCESS)
		goto EXIT_FUNCTION;

EXIT_FUNCTION:

	GEN_FREE_MemberList(&member_count, &member_list);

	if (return_code != GENFUNCS_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

