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
								1996-02-06 --- Version 5 changes.
									Michael L. Brock

		Copyright Michael L. Brock 1991 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "evaldefs.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	To avoid Visual C++ 6.0 warnings about removed inline functions . . .	*/
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(disable:4514)
#endif /* #ifdef _MSC_VER */
/*	***********************************************************************	*/

/*
	ADF NOTE:	<number> = @Ascii(<string>)
*/
/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EVAL_FUNC_Ascii(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count)
#else
void EEC_EVAL_FUNC_Ascii(eval_ptr, arg_count)
EEC_EVAL_DATA *eval_ptr;
unsigned int   arg_count;
#endif /* #ifndef NARGS */
{
	unsigned char this_char;

	if (!EEC_EVAL_PopIfSFlagsNumber(eval_ptr, arg_count)) {
		if (!EEC_EVAL_TOP_GET_STR_LEN(eval_ptr)) {
			EEC_EVAL_StackPop(eval_ptr, arg_count);
			EEC_EVAL_StackPushNumberFlag(eval_ptr, EEC_EVAL_FLAG_TYPE_ERR);
		}
		else {
			this_char = *EEC_EVAL_TOP_GET_STR_PTR(eval_ptr);
			EEC_EVAL_StackPop(eval_ptr, arg_count);
			EEC_EVAL_StackPushNumber(eval_ptr, ((double) this_char));
		}
	}
}
/*	***********************************************************************	*/

/*
	ADF NOTE:	@Center(<string>, <length> [, <pad-char> [, <ltrim-flag>,
						[<rtrim-flag>]]])
*/
/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EVAL_FUNC_Center(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count)
#else
void EEC_EVAL_FUNC_Center(eval_ptr, arg_count)
EEC_EVAL_DATA *eval_ptr;
unsigned int   arg_count;
#endif /* #ifndef NARGS */
{
	unsigned int length;
	char         pad_char   = ' ';
	int          ltrim_flag = 0;
	int          rtrim_flag = 0;
	EEC_DATUM    tmp_datum;

	if (!EEC_EVAL_PopIfSFlagsString(eval_ptr, arg_count)) {
		if (arg_count > 4)
			rtrim_flag = (EEC_EVAL_POP_NUMBER(eval_ptr)) ? 1 : 0;
		if (arg_count > 3)
			ltrim_flag = (EEC_EVAL_POP_NUMBER(eval_ptr)) ? 1 : 0;
		if (arg_count > 2) {
			pad_char = ((char) ((EEC_EVAL_TOP_GET_STR_LEN(eval_ptr)) ?
				*EEC_EVAL_TOP_GET_STR_PTR(eval_ptr) : ' '));
			EEC_EVAL_POP(eval_ptr);
		}
		if ((length = EEC_EVAL_POP_UINT(eval_ptr)) == 0) {
			EEC_EVAL_POP(eval_ptr);
			EEC_EVAL_StackPushStringEmpty(eval_ptr);
		}
		else {
			EEC_EVAL_StringAllocDatum(eval_ptr, length, &tmp_datum);
			center_basic_mem(EEC_EVAL_TOP_GET_STR_LEN(eval_ptr),
				EEC_EVAL_TOP_GET_STR_PTR(eval_ptr), &length,
				EEC_EVAL_DATUM_GET_STR_PTR(&tmp_datum), ltrim_flag, rtrim_flag,
				&pad_char, length);
			EEC_EVAL_POP(eval_ptr);
			EEC_EVAL_StackPushDatum(eval_ptr, &tmp_datum);
		}
	}
}
/*	***********************************************************************	*/

/*
	ADF NOTE:	<string> = @Char(<number>)
*/
/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EVAL_FUNC_Char(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count)
#else
void EEC_EVAL_FUNC_Char(eval_ptr, arg_count)
EEC_EVAL_DATA *eval_ptr;
unsigned int   arg_count;
#endif /* #ifndef NARGS */
{
	double        this_double;
	unsigned char this_char;

	if (!EEC_EVAL_PopIfSFlagsString(eval_ptr, arg_count)) {
		if (((this_double = EEC_EVAL_POP_NUMBER(eval_ptr)) < 0.0) ||
			(this_double > ((double) UCHAR_MAX)))
			 EEC_EVAL_StackPushStringFlag(eval_ptr, EEC_EVAL_FLAG_TYPE_ERR);
		else {
			this_char = ((unsigned char) this_double);
			EEC_EVAL_StackPushString(eval_ptr, ((char *) &this_char), 1);
		}
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EVAL_FUNC_Choose(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count)
#else
void EEC_EVAL_FUNC_Choose(eval_ptr, arg_count)
EEC_EVAL_DATA *eval_ptr;
unsigned int   arg_count;
#endif /* #ifndef NARGS */
{
	double number;

	number = floor(eval_ptr->eval_stack_top[1 - arg_count].datum.number);

	if ((number < 0.0) || (number >= ((double) (arg_count - 1))))
		EEC_EVAL_TREF_SET_ERR(eval_ptr, 1 - arg_count);
	else
		EEC_EVAL_StackExchange(eval_ptr,
			(eval_ptr->eval_stack_count - arg_count) + ((unsigned int) number)+1,
			eval_ptr->eval_stack_count - arg_count);

	EEC_EVAL_StackPop(eval_ptr, arg_count - 1);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EVAL_FUNC_Concatenate(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count)
#else
void EEC_EVAL_FUNC_Concatenate(eval_ptr, arg_count)
EEC_EVAL_DATA *eval_ptr;
unsigned int   arg_count;
#endif /* #ifndef NARGS */
{
	unsigned int  string_length = 0;
	unsigned int  count_1;
	EEC_DATUM    *datum_ptr;
	EEC_DATUM     tmp_datum;
	char         *tmp_ptr;

	if ((arg_count > 1) &&
		(!EEC_EVAL_PopIfSFlagsString(eval_ptr, arg_count))) {
		for (count_1 = 0, datum_ptr = eval_ptr->eval_stack_top;
			count_1 < arg_count; count_1++, datum_ptr--)
			string_length += EEC_EVAL_DATUM_GET_STR_LEN(datum_ptr);
		if (string_length) {
			tmp_ptr = EEC_EVAL_StringAllocDatum(eval_ptr, string_length,
				&tmp_datum);
			for (count_1 = 0, datum_ptr++; count_1 < arg_count;
				count_1++, datum_ptr++) {
				memcpy(tmp_ptr, EEC_EVAL_DATUM_GET_STR_PTR(datum_ptr),
					EEC_EVAL_DATUM_GET_STR_LEN(datum_ptr));
				tmp_ptr += EEC_EVAL_DATUM_GET_STR_LEN(datum_ptr);
			}
			EEC_EVAL_StackPop(eval_ptr, arg_count);
			EEC_EVAL_StackPushDatum(eval_ptr, &tmp_datum);
		}
		else {
			EEC_EVAL_StackPop(eval_ptr, arg_count);
			EEC_EVAL_StackPushStringEmpty(eval_ptr);
		}
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EVAL_FUNC_Err(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count)
#else
void EEC_EVAL_FUNC_Err(eval_ptr, arg_count)
EEC_EVAL_DATA *eval_ptr;
unsigned int   arg_count;
#endif /* #ifndef NARGS */
{
	if (!arg_count) {
		EEC_EVAL_PUSH_NUMBER(eval_ptr, 0.0);
		EEC_EVAL_TOP_SET_ERR(eval_ptr);
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EVAL_FUNC_Fixed(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count)
#else
void EEC_EVAL_FUNC_Fixed(eval_ptr, arg_count)
EEC_EVAL_DATA *eval_ptr;
unsigned int   arg_count;
#endif /* #ifndef NARGS */
{
	unsigned int  decimal_places;
	unsigned int  comma_places;
	char          decimal_char[2];
	char          comma_char[2];
	char         *tmp_ptr;
	char          buffer[512 * 2];

	if (!EEC_EVAL_PopIfSFlagsString(eval_ptr, arg_count)) {
		if (arg_count > 4) {
			chrcpy(comma_char,
				(eval_ptr->eval_stack_top->datum.string.data[0]) ?
				eval_ptr->eval_stack_top->datum.string.data[0] : ',');
			EEC_EVAL_POP(eval_ptr);
		}
		else
			chrcpy(comma_char, ',');
		if (arg_count > 3) {
			chrcpy(decimal_char,
				(eval_ptr->eval_stack_top->datum.string.data[0]) ?
				eval_ptr->eval_stack_top->datum.string.data[0] : '.');
			EEC_EVAL_POP(eval_ptr);
		}
		else
			chrcpy(decimal_char, '.');
		comma_places   = (arg_count > 2) ? EEC_EVAL_POP_UINT(eval_ptr) : 0;
		comma_places   = (comma_places <= 16)   ? comma_places   : 16;
		decimal_places = (arg_count > 1) ? EEC_EVAL_POP_UINT(eval_ptr) : 2;
		decimal_places = (decimal_places <= 15) ? decimal_places : 15;
		sprintf(buffer, "%.*f", ((int) decimal_places),
			EEC_EVAL_POP_DOUBLE(eval_ptr));
		if ((*decimal_char != '.') &&
			((tmp_ptr = strchr(buffer, '.')) != NULL))
			*tmp_ptr = *decimal_char;
		if (comma_places)
			insert_groups(buffer, decimal_char, comma_places, comma_char,
				buffer);
		EEC_EVAL_StackPushStringZ(eval_ptr, buffer);
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EVAL_FUNC_If(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count)
#else
void EEC_EVAL_FUNC_If(eval_ptr, arg_count)
EEC_EVAL_DATA *eval_ptr;
unsigned int   arg_count;
#endif /* #ifndef NARGS */
{
	if (arg_count > 2) {
		if ((EEC_EVAL_TREF_IS_SFLAG(eval_ptr, -2) == EEC_TRUE) ||
			(EEC_EVAL_TREF_IS_EMPTY(eval_ptr, -2) == EEC_TRUE))
			EEC_EVAL_StackExchange(eval_ptr, eval_ptr->eval_stack_count - 2,
				eval_ptr->eval_stack_count - 3);
		else
			EEC_EVAL_StackExchange(eval_ptr, eval_ptr->eval_stack_count - 1,
				eval_ptr->eval_stack_count - 3);
		EEC_EVAL_StackPop(eval_ptr, 2);
	}
}
/*	***********************************************************************	*/

/*
	<string> = @Join(<string>, <any>, <any> [,<any> . . .])
*/
/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EVAL_FUNC_Join(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count)
#else
void EEC_EVAL_FUNC_Join(eval_ptr, arg_count)
EEC_EVAL_DATA *eval_ptr;
unsigned int   arg_count;
#endif /* #ifndef NARGS */
{
	unsigned int  length;
	EEC_DATUM    *datum_ptr;
	EEC_DATUM    *join_datum_ptr;
	EEC_DATUM     tmp_datum;
	char         *tmp_ptr;
	char          buffer[512 * 2];

	if (!EEC_EVAL_PopIfSFlagsString(eval_ptr, arg_count)) {
		length         = 0;
		join_datum_ptr = EEC_EVAL_TREF_GET_PTR(eval_ptr, 1 - arg_count);
		for (datum_ptr = EEC_EVAL_TOP_GET_PTR(eval_ptr);
			datum_ptr > join_datum_ptr; datum_ptr--) {
			if (EEC_EVAL_DATUM_IS_NUMBER(datum_ptr)) {
				sprintf(buffer, "%.6f", EEC_EVAL_DATUM_GET_NUMBER(datum_ptr));
				EEC_EVAL_StringAllocDatum(eval_ptr, strlen(buffer), datum_ptr);
				memcpy(EEC_EVAL_DATUM_GET_STR_PTR(datum_ptr), buffer,
					EEC_EVAL_DATUM_GET_STR_LEN(datum_ptr));
			}
			length += EEC_EVAL_DATUM_GET_STR_LEN(datum_ptr);
		}
		length += (arg_count - 2) * EEC_EVAL_DATUM_GET_STR_LEN(join_datum_ptr);
		EEC_EVAL_StringAllocDatum(eval_ptr, length, &tmp_datum);
		for (datum_ptr++, tmp_ptr = EEC_EVAL_DATUM_GET_STR_PTR(&tmp_datum);
			datum_ptr <= EEC_EVAL_TOP_GET_PTR(eval_ptr); datum_ptr++) {
			memcpy(tmp_ptr, EEC_EVAL_DATUM_GET_STR_PTR(datum_ptr),
				EEC_EVAL_DATUM_GET_STR_LEN(datum_ptr));
			tmp_ptr += EEC_EVAL_DATUM_GET_STR_LEN(datum_ptr);
			if (datum_ptr < EEC_EVAL_TOP_GET_PTR(eval_ptr)) {
				memcpy(tmp_ptr, EEC_EVAL_DATUM_GET_STR_PTR(join_datum_ptr),
					EEC_EVAL_DATUM_GET_STR_LEN(join_datum_ptr));
				tmp_ptr += EEC_EVAL_DATUM_GET_STR_LEN(join_datum_ptr);
			}
		}
		EEC_EVAL_StackPop(eval_ptr, arg_count);
		EEC_EVAL_StackPushDatum(eval_ptr, &tmp_datum);
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EVAL_FUNC_Left(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count)
#else
void EEC_EVAL_FUNC_Left(eval_ptr, arg_count)
EEC_EVAL_DATA *eval_ptr;
unsigned int   arg_count;
#endif /* #ifndef NARGS */
{
	unsigned int length;

	if (!EEC_EVAL_PopIfSFlagsString(eval_ptr, arg_count)) {
		length = (arg_count == 2) ? EEC_EVAL_POP_UINT(eval_ptr) : 1;
		if (!length)
			EEC_EVAL_TOP_SET_STRING_EMPTY(eval_ptr);
		else if (length < EEC_EVAL_TOP_GET_STR_LEN(eval_ptr)) {
			EEC_EVAL_StackPushString(eval_ptr,
				eval_ptr->eval_stack_top->datum.string.data, length);
	 		EEC_EVAL_StackSwap(eval_ptr);
			EEC_EVAL_StackPop(eval_ptr, 1);
		}
	}
}
/*	***********************************************************************	*/

/*
	ADF NOTE:	@LeftPad(<string>, <length> [, <pad-char> [, <ltrim-flag>,
						[<rtrim-flag>]]])
*/
/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EVAL_FUNC_LeftPad(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count)
#else
void EEC_EVAL_FUNC_LeftPad(eval_ptr, arg_count)
EEC_EVAL_DATA *eval_ptr;
unsigned int   arg_count;
#endif /* #ifndef NARGS */
{
	unsigned int length;
	char         pad_char   = ' ';
	int          ltrim_flag = 0;
	int          rtrim_flag = 0;
	EEC_DATUM    tmp_datum;

	if (!EEC_EVAL_PopIfSFlagsString(eval_ptr, arg_count)) {
		if (arg_count > 4)
			rtrim_flag = (EEC_EVAL_POP_NUMBER(eval_ptr)) ? 1 : 0;
		if (arg_count > 3)
			ltrim_flag = (EEC_EVAL_POP_NUMBER(eval_ptr)) ? 1 : 0;
		if (arg_count > 2) {
			pad_char = ((char) ((EEC_EVAL_TOP_GET_STR_LEN(eval_ptr)) ?
				*EEC_EVAL_TOP_GET_STR_PTR(eval_ptr) : ' '));
			EEC_EVAL_POP(eval_ptr);
		}
		if ((length = EEC_EVAL_POP_UINT(eval_ptr)) == 0) {
			EEC_EVAL_POP(eval_ptr);
			EEC_EVAL_StackPushStringEmpty(eval_ptr);
		}
		else {
			EEC_EVAL_StringAllocDatum(eval_ptr, length, &tmp_datum);
			strpadl_basic_mem(EEC_EVAL_TOP_GET_STR_LEN(eval_ptr),
				EEC_EVAL_TOP_GET_STR_PTR(eval_ptr), &length,
				EEC_EVAL_DATUM_GET_STR_PTR(&tmp_datum), ltrim_flag, rtrim_flag,
				&pad_char, length);
			EEC_EVAL_POP(eval_ptr);
			EEC_EVAL_StackPushDatum(eval_ptr, &tmp_datum);
		}
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EVAL_FUNC_Len(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count)
#else
void EEC_EVAL_FUNC_Len(eval_ptr, arg_count)
EEC_EVAL_DATA *eval_ptr;
unsigned int   arg_count;
#endif /* #ifndef NARGS */
{
	unsigned int length;

	if (!EEC_EVAL_PopIfSFlagsNumber(eval_ptr, arg_count)) {
		length = EEC_EVAL_TOP_GET_STR_LEN(eval_ptr);
		EEC_EVAL_StackPopTop(eval_ptr);
		EEC_EVAL_StackPushNumber(eval_ptr, ((double) length));
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EVAL_FUNC_Lower(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count)
#else
void EEC_EVAL_FUNC_Lower(eval_ptr, arg_count)
EEC_EVAL_DATA *eval_ptr;
unsigned int   arg_count;
#endif /* #ifndef NARGS */
{
	if (arg_count) {
		if (EEC_EVAL_TOP_IS_DATA(eval_ptr) == EEC_TRUE) {
			if (EEC_EVAL_TOP_IS_STATIC(eval_ptr) == EEC_TRUE)
				EEC_EVAL_StaticToAlloced(eval_ptr, eval_ptr->eval_stack_top);
			lower_basic_mem(eval_ptr->eval_stack_top->datum.string.length,
				eval_ptr->eval_stack_top->datum.string.data,
				eval_ptr->eval_stack_top->datum.string.data);
		}
	}
}
/*	***********************************************************************	*/

/*
	ADF NOTE:	@LTrim(<string> [,<trim-char-list>])
*/
/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EVAL_FUNC_LTrim(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count)
#else
void EEC_EVAL_FUNC_LTrim(eval_ptr, arg_count)
EEC_EVAL_DATA *eval_ptr;
unsigned int   arg_count;
#endif /* #ifndef NARGS */
{
	unsigned int  char_len;
	char         *char_ptr;
	unsigned int  length;

	if (!EEC_EVAL_PopIfSFlagsString(eval_ptr, arg_count)) {
		if (arg_count == 1) {
			if (EEC_EVAL_TOP_IS_STATIC(eval_ptr) == EEC_TRUE)
				EEC_EVAL_StaticToAlloced(eval_ptr, eval_ptr->eval_stack_top);
			ltrim_basic_mem(EEC_EVAL_TOP_GET_STR_LEN(eval_ptr),
				EEC_EVAL_TOP_GET_STR_PTR(eval_ptr), &length,
				EEC_EVAL_TOP_GET_STR_PTR(eval_ptr));
			EEC_EVAL_TOP_SET_STR_LEN(eval_ptr, length);
			return;
		}
		else {
			if ((char_len = EEC_EVAL_TOP_GET_STR_LEN(eval_ptr)) > 0) {
				char_ptr = EEC_EVAL_TOP_GET_STR_PTR(eval_ptr);
				if (EEC_EVAL_TREF_IS_STATIC(eval_ptr, -1) == EEC_TRUE)
					EEC_EVAL_StaticToAlloced(eval_ptr,
						eval_ptr->eval_stack_top - 1);
				ltrimx_basic_mem(EEC_EVAL_TREF_GET_STR_LEN(eval_ptr, -1),
					EEC_EVAL_TREF_GET_STR_PTR(eval_ptr, -1), &length,
					EEC_EVAL_TREF_GET_STR_PTR(eval_ptr, -1), char_len, char_ptr);
				EEC_EVAL_TREF_SET_STR_LEN(eval_ptr, -1, length);
			}
			EEC_EVAL_StackPopTop(eval_ptr);
		}
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EVAL_FUNC_Mid(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count)
#else
void EEC_EVAL_FUNC_Mid(eval_ptr, arg_count)
EEC_EVAL_DATA *eval_ptr;
unsigned int   arg_count;
#endif /* #ifndef NARGS */
{
	unsigned int length;
	unsigned int start;
	unsigned int string_length;
	EEC_DATUM    tmp_datum;

	if (arg_count > 1) {
		if (arg_count == 2) {
			if (eval_ptr->eval_stack_top->datum.number < 0.0) {
				EEC_EVAL_StackPop(eval_ptr, 1);
				EEC_EVAL_TOP_SET_ERR(eval_ptr);
				return;
			}
			length = eval_ptr->eval_stack_top[-1].datum.string.length;
			start  = EEC_EVAL_TOP_GET_UINT(eval_ptr);
			EEC_EVAL_StackPop(eval_ptr, 1);
		}
		else if (arg_count == 3) {
			if ((eval_ptr->eval_stack_top->datum.number < 0.0) ||
				(eval_ptr->eval_stack_top[-1].datum.number < 0.0)) {
				EEC_EVAL_StackPop(eval_ptr, 2);
				EEC_EVAL_TOP_SET_ERR(eval_ptr);
				return;
			}
			length = EEC_EVAL_TOP_GET_UINT(eval_ptr);
			start  = EEC_EVAL_TREF_GET_UINT(eval_ptr, -1);
			EEC_EVAL_StackPop(eval_ptr, 2);
		}
		else {
			start  = 0;
			length = eval_ptr->eval_stack_top->datum.string.length;
		}
		if (start >= (string_length =
			eval_ptr->eval_stack_top->datum.string.length))
				EEC_EVAL_TOP_SET_STRING_EMPTY(eval_ptr);
		else {
			length                           =
				((string_length - start) > length) ? length :
				(string_length - start);
			tmp_datum                        = *eval_ptr->eval_stack_top;
			eval_ptr->eval_stack_top->flags -=
				(eval_ptr->eval_stack_top->flags & EEC_EVAL_FLAG_ALLOCED) ?
				EEC_EVAL_FLAG_ALLOCED : 0;
			EEC_EVAL_StackPop(eval_ptr, 1);
			EEC_EVAL_StackPushString(eval_ptr,
				tmp_datum.datum.string.data + start, length);
			if (tmp_datum.flags & EEC_EVAL_FLAG_ALLOCED)
				free(tmp_datum.datum.string.data);
		}
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EVAL_FUNC_NA(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count)
#else
void EEC_EVAL_FUNC_NA(eval_ptr, arg_count)
EEC_EVAL_DATA *eval_ptr;
unsigned int   arg_count;
#endif /* #ifndef NARGS */
{
	if (!arg_count) {
		EEC_EVAL_PUSH_NUMBER(eval_ptr, 0.0);
		EEC_EVAL_TOP_SET_NA(eval_ptr);
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EVAL_FUNC_Null(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count)
#else
void EEC_EVAL_FUNC_Null(eval_ptr, arg_count)
EEC_EVAL_DATA *eval_ptr;
unsigned int   arg_count;
#endif /* #ifndef NARGS */
{
	if (!arg_count) {
		EEC_EVAL_PUSH_NUMBER(eval_ptr, 0.0);
		EEC_EVAL_TOP_SET_NULL(eval_ptr);
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EVAL_FUNC_Pi(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count)
#else
void EEC_EVAL_FUNC_Pi(eval_ptr, arg_count)
EEC_EVAL_DATA *eval_ptr;
unsigned int   arg_count;
#endif /* #ifndef NARGS */
{
	if (!arg_count)
		EEC_EVAL_PUSH_NUMBER(eval_ptr, 3.14159265358979323846);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EVAL_FUNC_Pow(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count)
#else
void EEC_EVAL_FUNC_Pow(eval_ptr, arg_count)
EEC_EVAL_DATA *eval_ptr;
unsigned int   arg_count;
#endif /* #ifndef NARGS */
{
	if (arg_count > 1) {
		eval_ptr->eval_stack_top[-1].datum.number =
			pow(eval_ptr->eval_stack_top[-1].datum.number,
			eval_ptr->eval_stack_top->datum.number);
		EEC_EVAL_StackPop(eval_ptr, 1);
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EVAL_FUNC_Rand(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count)
#else
void EEC_EVAL_FUNC_Rand(eval_ptr, arg_count)
EEC_EVAL_DATA *eval_ptr;
unsigned int   arg_count;
#endif /* #ifndef NARGS */
{
	if (!arg_count)
		EEC_EVAL_PUSH_NUMBER(eval_ptr, ((double) rand()));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EVAL_FUNC_Right(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count)
#else
void EEC_EVAL_FUNC_Right(eval_ptr, arg_count)
EEC_EVAL_DATA *eval_ptr;
unsigned int   arg_count;
#endif /* #ifndef NARGS */
{
	unsigned int length;

	if (!EEC_EVAL_PopIfSFlagsString(eval_ptr, arg_count)) {
		length = (arg_count == 2) ? EEC_EVAL_POP_UINT(eval_ptr) : 1;
		if (!length)
			EEC_EVAL_TOP_SET_STRING_EMPTY(eval_ptr);
		else if (length < EEC_EVAL_TOP_GET_STR_LEN(eval_ptr)) {
			EEC_EVAL_StackPushString(eval_ptr,
				eval_ptr->eval_stack_top->datum.string.data +
				eval_ptr->eval_stack_top->datum.string.length - length, length);
			EEC_EVAL_StackSwap(eval_ptr);
			EEC_EVAL_StackPop(eval_ptr, 1);
		}
	}
}
/*	***********************************************************************	*/

/*
	ADF NOTE:	@RightPad(<string>, <length> [, <pad-char> [, <ltrim-flag>,
						[<rtrim-flag>]]])
*/
/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EVAL_FUNC_RightPad(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count)
#else
void EEC_EVAL_FUNC_RightPad(eval_ptr, arg_count)
EEC_EVAL_DATA *eval_ptr;
unsigned int   arg_count;
#endif /* #ifndef NARGS */
{
	unsigned int length;
	char         pad_char   = ' ';
	int          ltrim_flag = 0;
	int          rtrim_flag = 0;
	EEC_DATUM    tmp_datum;

	if (!EEC_EVAL_PopIfSFlagsString(eval_ptr, arg_count)) {
		if (arg_count > 4)
			rtrim_flag = (EEC_EVAL_POP_NUMBER(eval_ptr)) ? 1 : 0;
		if (arg_count > 3)
			ltrim_flag = (EEC_EVAL_POP_NUMBER(eval_ptr)) ? 1 : 0;
		if (arg_count > 2) {
			pad_char = ((char) ((EEC_EVAL_TOP_GET_STR_LEN(eval_ptr)) ?
				*EEC_EVAL_TOP_GET_STR_PTR(eval_ptr) : ' '));
			EEC_EVAL_POP(eval_ptr);
		}
		if ((length = EEC_EVAL_POP_UINT(eval_ptr)) == 0) {
			EEC_EVAL_POP(eval_ptr);
			EEC_EVAL_StackPushStringEmpty(eval_ptr);
		}
		else {
			EEC_EVAL_StringAllocDatum(eval_ptr, length, &tmp_datum);
			strpadr_basic_mem(EEC_EVAL_TOP_GET_STR_LEN(eval_ptr),
				EEC_EVAL_TOP_GET_STR_PTR(eval_ptr), &length,
				EEC_EVAL_DATUM_GET_STR_PTR(&tmp_datum), ltrim_flag, rtrim_flag,
				&pad_char, length);
			EEC_EVAL_POP(eval_ptr);
			EEC_EVAL_StackPushDatum(eval_ptr, &tmp_datum);
		}
	}
}
/*	***********************************************************************	*/

/*
	ADF NOTE:	@RTrim(<string> [,<trim-char-list>])
*/
/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EVAL_FUNC_RTrim(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count)
#else
void EEC_EVAL_FUNC_RTrim(eval_ptr, arg_count)
EEC_EVAL_DATA *eval_ptr;
unsigned int   arg_count;
#endif /* #ifndef NARGS */
{
	unsigned int  char_len;
	char         *char_ptr;
	unsigned int  length;

	if (!EEC_EVAL_PopIfSFlagsString(eval_ptr, arg_count)) {
		if (arg_count == 1) {
			if (EEC_EVAL_TOP_IS_STATIC(eval_ptr) == EEC_TRUE)
				EEC_EVAL_StaticToAlloced(eval_ptr, eval_ptr->eval_stack_top);
			rtrim_basic_mem(EEC_EVAL_TOP_GET_STR_LEN(eval_ptr),
				EEC_EVAL_TOP_GET_STR_PTR(eval_ptr), &length,
				EEC_EVAL_TOP_GET_STR_PTR(eval_ptr));
			EEC_EVAL_TOP_SET_STR_LEN(eval_ptr, length);
			return;
		}
		else {
			if ((char_len = EEC_EVAL_TOP_GET_STR_LEN(eval_ptr)) > 0) {
				char_ptr = EEC_EVAL_TOP_GET_STR_PTR(eval_ptr);
				if (EEC_EVAL_TREF_IS_STATIC(eval_ptr, -1) == EEC_TRUE)
					EEC_EVAL_StaticToAlloced(eval_ptr,
						eval_ptr->eval_stack_top - 1);
				rtrimx_basic_mem(EEC_EVAL_TREF_GET_STR_LEN(eval_ptr, -1),
					EEC_EVAL_TREF_GET_STR_PTR(eval_ptr, -1), &length,
					EEC_EVAL_TREF_GET_STR_PTR(eval_ptr, -1), char_len, char_ptr);
				EEC_EVAL_TREF_SET_STR_LEN(eval_ptr, -1, length);
			}
			EEC_EVAL_StackPopTop(eval_ptr);
		}
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EVAL_FUNC_Sqrt(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count)
#else
void EEC_EVAL_FUNC_Sqrt(eval_ptr, arg_count)
EEC_EVAL_DATA *eval_ptr;
unsigned int   arg_count;
#endif /* #ifndef NARGS */
{
	if (arg_count)
		eval_ptr->eval_stack_top->datum.number =
			sqrt(eval_ptr->eval_stack_top->datum.number);
}
/*	***********************************************************************	*/

/*
	ADF NOTE:	@Trim(<string> [,<trim-char-list>])
*/
/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EVAL_FUNC_Trim(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count)
#else
void EEC_EVAL_FUNC_Trim(eval_ptr, arg_count)
EEC_EVAL_DATA *eval_ptr;
unsigned int   arg_count;
#endif /* #ifndef NARGS */
{
	unsigned int  char_len;
	char         *char_ptr;
	unsigned int  length;

	if (!EEC_EVAL_PopIfSFlagsString(eval_ptr, arg_count)) {
		if (arg_count == 1) {
			if (EEC_EVAL_TOP_IS_STATIC(eval_ptr) == EEC_TRUE)
				EEC_EVAL_StaticToAlloced(eval_ptr, eval_ptr->eval_stack_top);
			trim_basic_mem(EEC_EVAL_TOP_GET_STR_LEN(eval_ptr),
				EEC_EVAL_TOP_GET_STR_PTR(eval_ptr), &length,
				EEC_EVAL_TOP_GET_STR_PTR(eval_ptr));
			EEC_EVAL_TOP_SET_STR_LEN(eval_ptr, length);
			return;
		}
		else {
			if ((char_len = EEC_EVAL_TOP_GET_STR_LEN(eval_ptr)) > 0) {
				char_ptr = EEC_EVAL_TOP_GET_STR_PTR(eval_ptr);
				if (EEC_EVAL_TREF_IS_STATIC(eval_ptr, -1) == EEC_TRUE)
					EEC_EVAL_StaticToAlloced(eval_ptr,
						eval_ptr->eval_stack_top - 1);
				trimx_basic_mem(EEC_EVAL_TREF_GET_STR_LEN(eval_ptr, -1),
					EEC_EVAL_TREF_GET_STR_PTR(eval_ptr, -1), &length,
					EEC_EVAL_TREF_GET_STR_PTR(eval_ptr, -1), char_len, char_ptr);
				EEC_EVAL_TREF_SET_STR_LEN(eval_ptr, -1, length);
			}
			EEC_EVAL_StackPopTop(eval_ptr);
		}
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EVAL_FUNC_Upper(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count)
#else
void EEC_EVAL_FUNC_Upper(eval_ptr, arg_count)
EEC_EVAL_DATA *eval_ptr;
unsigned int   arg_count;
#endif /* #ifndef NARGS */
{
	if (arg_count) {
		if (EEC_EVAL_TOP_IS_DATA(eval_ptr) == EEC_TRUE) {
			if (EEC_EVAL_TOP_IS_STATIC(eval_ptr) == EEC_TRUE)
				EEC_EVAL_StaticToAlloced(eval_ptr, eval_ptr->eval_stack_top);
			upper_basic_mem(eval_ptr->eval_stack_top->datum.string.length,
				eval_ptr->eval_stack_top->datum.string.data,
				eval_ptr->eval_stack_top->datum.string.data);
		}
	}
}
/*	***********************************************************************	*/

