/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:

	Revision History	:	1994-05-14 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <memory.h>
#include <string.h>

#include <dbcsyb.h>

#include "dcr.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
COMPAT_EXTERN_DATA_DECL const GEN_ALIGN_DESCRIPTOR GEN_AlignList[];
/*	***********************************************************************	*/

void DCR_EmitField(field_ptr, field_align_count, field_align_list,
	data_length, total_length, intra_field_separator, record_ptr,
	output_function, output_control)
DCR_FIELD  *field_ptr;
unsigned int      field_align_count;
GEN_ALIGN        *field_align_list;
unsigned int      data_length;
unsigned int      total_length;
char             *intra_field_separator;
char             *record_ptr;
#ifndef NARGS
void            (*output_function)(void *, char *, ...);
#else
void            (*output_function)();
#endif /* #ifndef NARGS */
void             *output_control;
{
	unsigned int  count_1;
	unsigned int  count_2;
   unsigned int  real_length;
	char         *data_ptr;
   DTIME         tmp_dtime;
   GEN_ALIGN    *align_ptr;
	char          printf_buffer[1024];
	double        double_buffer[2];
	char          date_buffer[100];

	data_ptr = record_ptr + field_ptr->data_offset;
	switch (field_ptr->db_type) {
		case SYBBINARY		:
		case SYBIMAGE		:
			(*output_function)(output_control, "0X");
			for (count_1 = 0; count_1 < field_ptr->data_length; count_1++)
				(*output_function)(output_control, "%02X",
					((unsigned int) *(((unsigned char *) record_ptr) +
					field_ptr->data_offset + count_1)));
			if (total_length > data_length)
				(*output_function)(output_control, "%*.*s",
					total_length - data_length, total_length - data_length,
					" ");
			break;
		case SYBBIT			:
			(*output_function)(output_control, "%-*.*s", data_length,
				data_length, (*data_ptr) ? "TRUE" : "FALSE");
			if (total_length > data_length)
				(*output_function)(output_control, "%*.*s",
					total_length - data_length, total_length - data_length,
					" ");
			break;
		case SYBCHAR		:
		case SYBTEXT		:
			(*output_function)(output_control, "%-*.*s", data_length,
				data_length, data_ptr);
			break;
		case SYBINT1		:
			if (total_length > data_length)
				(*output_function)(output_control, "%*.*s",
					total_length - data_length, total_length - data_length,
					" ");
			(*output_function)(output_control, "%*u", data_length,
				((unsigned int) *((unsigned char *) data_ptr)));
			break;
		case SYBINT2		:
			if (total_length > data_length)
				(*output_function)(output_control, "%*.*s",
					total_length - data_length, total_length - data_length,
					" ");
			(*output_function)(output_control, "%*d", data_length,
				((int) *((short *) data_ptr)));
			break;
		case SYBINT4		:
			if (total_length > data_length)
				(*output_function)(output_control, "%*.*s",
					total_length - data_length, total_length - data_length,
					" ");
			(*output_function)(output_control, "%*ld", data_length,
				*((long *) data_ptr));
			break;
		case SYBREAL		:
			sprintf(printf_buffer,
				GEN_AlignList[field_align_list->type].printf_format,
				((double) *((float *) data_ptr)));
			if (total_length > (real_length = strlen(printf_buffer)))
				(*output_function)(output_control, "%*.*s",
					total_length - real_length, total_length - real_length,
					" ");
			else if (real_length > total_length) {
				memset(printf_buffer, '*', total_length);
				printf_buffer[total_length] = '\0';
			}
			(*output_function)(output_control, "%s", printf_buffer);
			break;
		case SYBFLT8		:
			sprintf(printf_buffer,
				GEN_AlignList[field_align_list->type].printf_format,
				*((double *) data_ptr));
			if (total_length > (real_length = strlen(printf_buffer)))
				(*output_function)(output_control, "%*.*s",
					total_length - real_length, total_length - real_length,
					" ");
			else if (real_length > total_length) {
				memset(printf_buffer, '*', total_length);
				printf_buffer[total_length] = '\0';
			}
			(*output_function)(output_control, "%s", printf_buffer);
			break;
		case SYBMONEY		:
			sprintf(printf_buffer,
				GEN_AlignList[GEN_C_ALIGN_double].printf_format,
				DBC_SYB_DBMONEYToDouble(((DBMONEY *) data_ptr)));
			if (total_length > (real_length = strlen(printf_buffer)))
				(*output_function)(output_control, "%*.*s",
					total_length - real_length, total_length - real_length,
					" ");
			else if (real_length > total_length) {
				memset(printf_buffer, '*', total_length);
				printf_buffer[total_length] = '\0';
			}
			(*output_function)(output_control, "%s", printf_buffer);
			break;
		case SYBMONEY4		:
			sprintf(printf_buffer,
				GEN_AlignList[GEN_C_ALIGN_double].printf_format,
				DBC_SYB_DBMONEY4ToDouble(((DBMONEY4 *) data_ptr)));
			if (total_length > (real_length = strlen(printf_buffer)))
				(*output_function)(output_control, "%*.*s",
					total_length - real_length, total_length - real_length,
					" ");
			else if (real_length > total_length) {
				memset(printf_buffer, '*', total_length);
				printf_buffer[total_length] = '\0';
			}
			(*output_function)(output_control, "%s", printf_buffer);
			break;
		case SYBDATETIME	:
			(*output_function)(output_control, "%-*.*s",
				data_length, data_length,
				DTIME_FormatDate(DBC_SYB_Sybase8ToDTIME(((DBDATETIME *) data_ptr),
					&tmp_dtime), NULL, date_buffer));
			break;
		case SYBDATETIME4	:
			(*output_function)(output_control, "%-*.*s",
				data_length, data_length,
				DTIME_FormatDate(DBC_SYB_Sybase4ToDTIME(((DBDATETIME4 *) data_ptr),
					&tmp_dtime), NULL, date_buffer));
			break;
		default				:
			for (count_1 = 0; count_1 < field_align_count; count_1++) {
				align_ptr = field_align_list + count_1;
				if ((align_ptr->type == GEN_C_ALIGN_char) ||
					(align_ptr->type == GEN_C_ALIGN_unsigned_char))
					(*output_function)(output_control, "%-*.*s", total_length,
						total_length, data_ptr);
				else {
					if (total_length > data_length)
						(*output_function)(output_control, "%*.*s",
							total_length - data_length,
							total_length - data_length, " ");
					for (count_2 = 0; count_2 < align_ptr->array_length;
						count_2++) {
						switch (align_ptr->type) {
							case GEN_C_ALIGN_short				:
								(*output_function)(output_control,
									GEN_AlignList[align_ptr->type].printf_format,
									((int) *((short *) data_ptr)));
								break;
							case GEN_C_ALIGN_unsigned_short	:
								(*output_function)(output_control,
									GEN_AlignList[align_ptr->type].printf_format,
									((unsigned int) *((unsigned short *) data_ptr)));
								break;
							case GEN_C_ALIGN_int					:
								(*output_function)(output_control,
									GEN_AlignList[align_ptr->type].printf_format,
									*((int *) data_ptr));
								break;
							case GEN_C_ALIGN_unsigned_int		:
								(*output_function)(output_control,
									GEN_AlignList[align_ptr->type].printf_format,
									*((unsigned int *) data_ptr));
								break;
							case GEN_C_ALIGN_long				:
								(*output_function)(output_control,
									GEN_AlignList[align_ptr->type].printf_format,
									*((long *) data_ptr));
								break;
							case GEN_C_ALIGN_unsigned_long	:
								(*output_function)(output_control,
									GEN_AlignList[align_ptr->type].printf_format,
									*((unsigned long *) data_ptr));
								break;
							case GEN_C_ALIGN_float				:
								(*output_function)(output_control,
									GEN_AlignList[align_ptr->type].printf_format,
									*((float *) data_ptr));
								break;
							case GEN_C_ALIGN_double				:
								(*output_function)(output_control,
									GEN_AlignList[align_ptr->type].printf_format,
									*((double *) data_ptr));
								break;
							default									:
								memcpy(double_buffer, data_ptr, align_ptr->length);
								(*output_function)(output_control,
									GEN_AlignList[GEN_C_ALIGN_double].printf_format,
									*double_buffer);
								break;
						}
						if ((count_2 < (align_ptr->array_length - 1)) &&
							*intra_field_separator)
							(*output_function)(output_control, "%s",
								intra_field_separator);
						data_ptr += align_ptr->length;
					}
				}
			}
			break;
	}
}
/*	***********************************************************************	*/

