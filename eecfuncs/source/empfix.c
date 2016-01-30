/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Expression Evaluation Calculator Library (EECFUNCS) Library Module		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	

	Revision History	:	1991-12-12 --- Creation.
									Michael L. Brock
								1996-01-30 --- Version 5 initial cut.
									Michael L. Brock

		Copyright Michael L. Brock 1991 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <ctype.h>
#include <stdio.h>

#include "parsedat.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EMIT_PostFix(const EEC_POSTFIX *postfix_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
void EEC_EMIT_PostFix(postfix_ptr, output_function, output_control)
const EEC_POSTFIX     *postfix_ptr;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	unsigned int    stack_entry = 0;
	unsigned int    count_1;
	const char     *data_ptr;
	unsigned short  arg_count;
	unsigned short  tmp_short;
	unsigned int    tmp_int;
	unsigned long   tmp_long;
	double          tmp_double;
	const char     *tmp_ptr;
	unsigned int    size;

	STR_EMIT_SetDefaults(&output_function, &output_control);

	data_ptr = postfix_ptr->data;

	for (count_1 = 0; count_1 < postfix_ptr->length; count_1++, data_ptr++) {
		switch (*data_ptr) {
			case EEC_PFIX_TYPE_NUMBER		:
				ECC_GET_PFIX_NUMBER(data_ptr, &tmp_double);
				(*output_function)(output_control, "[%05u]:Number  : ",
					stack_entry++);
				(*output_function)(output_control, "%20.6f\n", tmp_double);
				size = sizeof(double);
				break;
			case EEC_PFIX_TYPE_STRING		:
				EEC_GET_PFIX_STRING(data_ptr, &tmp_int, &tmp_ptr);
				(*output_function)(output_control, "[%05u]:String  : ",
					stack_entry++);
				EEC_EMIT_HumanString(tmp_int, tmp_ptr, EEC_TRUE, 0,
					output_function, output_control);
				(*output_function)(output_control, " (length = %u)\n", tmp_int);
				size = sizeof(unsigned int) + tmp_int + 1;
				break;
			case EEC_PFIX_TYPE_FUNCTION	:
				EEC_GET_PFIX_FUNCTION(data_ptr, &tmp_long, &arg_count,
					&tmp_short, &tmp_ptr);
				stack_entry -= arg_count;
				(*output_function)(output_control, "[%05u]:Function: ",
					stack_entry++);
				if (tmp_short)
					(*output_function)(output_control,
						"@%-*.*s() (args=%u, id=%lu/0X%08lX)\n",
						((int) tmp_short), ((int) tmp_short), tmp_ptr, arg_count,
						tmp_long, tmp_long);
				else
					(*output_function)(output_control,
				"@<external-function-id-%010lu>() (args=%u, id=%lu/0X%08lX)\n",
						tmp_long, arg_count, tmp_long, tmp_long);
				size = sizeof(unsigned long) + (sizeof(unsigned short) * 2) +
					((unsigned int) tmp_short);
				break;
			case EEC_PFIX_TYPE_SYMBOL		:
				EEC_GET_PFIX_SYMBOL(data_ptr, &tmp_long, &tmp_short, &tmp_ptr);
				(*output_function)(output_control, "[%05u]:Symbol  : ",
					stack_entry++);
				if (tmp_short)
					(*output_function)(output_control, "%-*.*s (id=%lu/0X%08lX)\n",
						((int) tmp_short), ((int) tmp_short), tmp_ptr, tmp_long,
						tmp_long);
				else
					(*output_function)(output_control,
						"<external-symbol-id-%010lu> (id=%lu/0X%08lX)\n",
						tmp_long, tmp_long, tmp_long);
				size = sizeof(unsigned long) + sizeof(unsigned short) +
					((unsigned int) tmp_short);
				break;
			default								:
				if (*data_ptr < EEC_OPERATOR_COUNT) {
					stack_entry -= 2;
					(*output_function)(output_control,
						"[%05u]:Operator: %s\n", stack_entry++,
						EEC_OperatorList[((unsigned int) *data_ptr)].operator_name);
				}
				else
					(*output_function)(output_control,
						"[     ]:***UNKNOWN***: character = %3u (0X%02X hex)\n",
						((unsigned int) *((unsigned char *) data_ptr)),
						((unsigned int) *((unsigned char *) data_ptr)));
				size = 0;
				break;
		}
		count_1  += size;
		data_ptr += size;
	}
}
/*	***********************************************************************	*/

