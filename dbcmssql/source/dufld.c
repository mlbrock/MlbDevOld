/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Microsoft SQL Server Support Functions Library Module					*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Dumps a single Microsoft SQL Server field in text
								format.

	Revision History	:	1995-12-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#include <string.h>

#include "dbcmssql.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_MSSQL_DumpField

   SYNOPSIS    :	void DBC_MSSQL_DumpField(type_count, type_list,
							member_ptr, record_ptr, null_flag, intra_field_sep,
							null_string, overflow_char, user_data_ptr,
							output_function, output_control);

						unsigned int           type_count;

						const DTA_TYPE        *type_list;

						const MDDL            *member_ptr;

						const void            *record_ptr;

						int                    null_flag;

						const char            *null_string;

						const char            *intra_field_sep;

						const char            *overflow_char;

						void                  *user_data_ptr;

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;

   DESCRIPTION :	Dumps a single Microsoft SQL Server field in text format.

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

						(.) ``member_ptr`` points to the ''MDDL'' structure
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

   SEE ALSO    :	MDDL_DumpField

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1995 - 2018 Michael L. Brock

   OUTPUT INDEX:	DBC_MSSQL_DumpField
						Dump Functions:DBC_MSSQL_DumpField
						DBC Microsoft SQL Server Functions:DBC_MSSQL_DumpField
						DBC Functions:Dump Functions:DBC_MSSQL_DumpField

   PUBLISH XREF:	DBC_MSSQL_DumpField

   PUBLISH NAME:	DBC_MSSQL_DumpField

	ENTRY CLASS	:	Dump Functions
						DBC Functions:Dump Functions

EOH */
/*	***********************************************************************	*/
void DBC_MSSQL_DumpField(type_count, type_list, member_ptr, record_ptr,
	null_flag, null_string, intra_field_sep, overflow_char, user_data_ptr,
	output_function, output_control)
unsigned int           type_count;
const DTA_TYPE        *type_list;
const MDDL            *member_ptr;
const void            *record_ptr;
int                    null_flag;
const char            *intra_field_sep;
const char            *null_string;
const char            *overflow_char;
void                  *user_data_ptr;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
{
	unsigned int  remaining_length;
	unsigned int  count_1;
	const void   *data_ptr;
	MDDL          tmp_member;
   DTIME         tmp_dtime;
	char          printf_buffer[1024];

	STR_EMIT_SetDefaults(&output_function, &output_control);

	DTA_GetTypeInfo(&type_count, &type_list);

	data_ptr         = ((const void *)
		(((const char *) record_ptr) + member_ptr->offset));
	overflow_char    = (overflow_char == NULL) ? "*" : overflow_char;
	remaining_length = member_ptr->display_length;

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
		(member_ptr->dump_function != DBC_MSSQL_DumpField)) {
		(*member_ptr->dump_function)(type_count, type_list, member_ptr,
			record_ptr, null_flag, intra_field_sep, null_string, overflow_char,
			user_data_ptr, output_function, output_control);
		return;
	}
	/*	*****************************************************************	*/

	switch (member_ptr->dbc_type) {
		case SQLBINARY		:
		case SQLIMAGE		:
			if (remaining_length < (2 + member_ptr->data_length))
				STR_EMIT_Char(*overflow_char, remaining_length,
					output_function, output_control);
			else {
				(*output_function)(output_control, "0X");
				for (count_1 = 0; count_1 < member_ptr->data_length; count_1++)
					(*output_function)(output_control, "%02X",
						((unsigned int) *(((unsigned char *) record_ptr) +
						member_ptr->offset + count_1)));
				remaining_length -= 2 + (member_ptr->data_length * 2);
			}
			if (remaining_length)
				STR_EMIT_Char(' ', remaining_length, output_function,
					output_control);
			break;
		case SQLBIT			:
			strcpy(printf_buffer, (*((const char *) data_ptr)) ?
				"TRUE" : "FALSE");
			if (strlen(trim(printf_buffer)) > remaining_length)
				STR_EMIT_Char(*overflow_char, remaining_length,
					output_function, output_control);
			else
				(*output_function)(output_control, "%*.*s",
					remaining_length, remaining_length, printf_buffer);
			break;
		case SQLCHAR		:
		case SQLTEXT		:
			if (remaining_length < member_ptr->data_length)
				STR_EMIT_Char(*overflow_char, remaining_length,
					output_function, output_control);
			else {
				(*output_function)(output_control, "%-*.*s", remaining_length,
					remaining_length, ((const char *) data_ptr));
				remaining_length -= member_ptr->data_length;
			}
			if (remaining_length)
				STR_EMIT_Char(' ', remaining_length, output_function,
					output_control);
			break;
		case SQLINT1		:
			sprintf(printf_buffer, "%u",
				((unsigned int) *((unsigned char *) data_ptr)));
			if (strlen(trim(printf_buffer)) > remaining_length)
				STR_EMIT_Char(*overflow_char, remaining_length,
					output_function, output_control);
			else
				(*output_function)(output_control, "%*.*s",
					remaining_length, remaining_length, printf_buffer);
			break;
		case SQLINT2		:
			sprintf(printf_buffer, "%d", ((int) *((short *) data_ptr)));
			if (strlen(trim(printf_buffer)) > remaining_length)
				STR_EMIT_Char(*overflow_char, remaining_length,
					output_function, output_control);
			else
				(*output_function)(output_control, "%*.*s",
					remaining_length, remaining_length, printf_buffer);
			break;
		case SQLINT4		:
			sprintf(printf_buffer, "%ld", *((long *) data_ptr));
			if (strlen(trim(printf_buffer)) > remaining_length)
				STR_EMIT_Char(*overflow_char, remaining_length,
					output_function, output_control);
			else
				(*output_function)(output_control, "%*.*s",
					remaining_length, remaining_length, printf_buffer);
			break;
		case SQLFLT4		:
			sprintf(printf_buffer,
				type_list[DTA_C_float].printf_format,
				((double) *((float *) data_ptr)));
			if (strlen(trim(printf_buffer)) > remaining_length)
				STR_EMIT_Char(*overflow_char, remaining_length,
					output_function, output_control);
			else
				(*output_function)(output_control, "%*.*s",
					remaining_length, remaining_length, printf_buffer);
			break;
		case SQLFLT8		:
			sprintf(printf_buffer,
				type_list[DTA_C_double].printf_format,
				*((double *) data_ptr));
			if (strlen(trim(printf_buffer)) > remaining_length)
				STR_EMIT_Char(*overflow_char, remaining_length,
					output_function, output_control);
			else
				(*output_function)(output_control, "%*.*s",
					remaining_length, remaining_length, printf_buffer);
			break;
		case SQLMONEY		:
			printf_buffer[0] = '$';
			sprintf(printf_buffer + 1,
				type_list[DTA_C_double].printf_format,
				DBC_MSSQL_DBMONEYToDouble(((DBMONEY *) data_ptr)));
			if (strlen(trim(printf_buffer)) > remaining_length)
				STR_EMIT_Char(*overflow_char, remaining_length,
					output_function, output_control);
			else
				(*output_function)(output_control, "%*.*s",
					remaining_length, remaining_length, printf_buffer);
			break;
		case SQLMONEY4		:
			printf_buffer[0] = '$';
			sprintf(printf_buffer + 1,
				type_list[DTA_C_double].printf_format,
				DBC_MSSQL_DBMONEY4ToDouble(((DBMONEY4 *) data_ptr)));
			if (strlen(trim(printf_buffer)) > remaining_length)
				STR_EMIT_Char(*overflow_char, remaining_length,
					output_function, output_control);
			else
				(*output_function)(output_control, "%*.*s",
					remaining_length, remaining_length, printf_buffer);
			break;
		case SQLDATETIME	:
			DTIME_FormatDate(DBC_MSSQL_MSSQL8ToDTIME(((DBDATETIME *) data_ptr),
				&tmp_dtime), NULL, printf_buffer);
			if (strlen(trim(printf_buffer)) > remaining_length)
				STR_EMIT_Char(*overflow_char, remaining_length,
					output_function, output_control);
			else
				(*output_function)(output_control, "%*.*s",
					remaining_length, remaining_length, printf_buffer);
			break;
		case SQLDATETIM4	:
			DTIME_FormatDate(DBC_MSSQL_MSSQL4ToDTIME(((DBDATETIM4 *) data_ptr),
				&tmp_dtime), NULL, printf_buffer);
			if (strlen(trim(printf_buffer)) > remaining_length)
				STR_EMIT_Char(*overflow_char, remaining_length,
					output_function, output_control);
			else
				(*output_function)(output_control, "%*.*s",
					remaining_length, remaining_length, printf_buffer);
			break;
		default				:
			tmp_member               = *member_ptr;
			tmp_member.dump_function = NULL;
			MDDL_DumpField(type_count, type_list, &tmp_member,
				record_ptr, null_flag, null_string, intra_field_sep,
				overflow_char, user_data_ptr, output_function, output_control);
			break;
	}
}
/*	***********************************************************************	*/

