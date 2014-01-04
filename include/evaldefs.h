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

	Revision History	:	1991-12-01 --- Creation.
									Michael L. Brock
								1993-04-04 --- Version 4 changes.
									Michael L. Brock
								1996-02-04 --- Version 5 changes.
									Michael L. Brock

		Copyright Michael L. Brock 1991 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__EVALDEFS_H__h

#define h__EVALDEFS_H__h					1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <setjmp.h>

#include "eecfuncs.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define EEC_EVAL_NEED_MORE_STACK(eval_ptr)										\
	(((eval_ptr)->eval_stack_count ==												\
		(eval_ptr)->eval_stack_alloc) ? EEC_TRUE : EEC_FALSE)

#define EEC_EVAL_ADD_STACK_INDEX(eval_ptr)										\
	((eval_ptr)->eval_stack_top =														\
		((eval_ptr)->eval_stack + (eval_ptr)->eval_stack_count++))			\

#define EEC_EVAL_SUB_STACK_INDEX(eval_ptr)										\
	((eval_ptr)->eval_stack_top =														\
		((eval_ptr)->eval_stack + ((--(eval_ptr)->eval_stack_count) ?		\
		((eval_ptr)->eval_stack_count - 1) : 0)))

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define EEC_EVAL_DATUM_IS_DATA(datum_ptr)											\
	(((datum_ptr)->flags & EEC_EVAL_FLAG_FLAGS_SPECIAL) ? EEC_FALSE : EEC_TRUE)

#define EEC_EVAL_DATUM_IS_SFLAG(datum_ptr)										\
	(((datum_ptr)->flags & EEC_EVAL_FLAG_FLAGS_SPECIAL) ? EEC_TRUE : EEC_FALSE)

#define EEC_EVAL_DATUM_IS_NULL(datum_ptr)											\
	(((datum_ptr)->flags & EEC_EVAL_FLAG_TYPE_NULL) ? EEC_TRUE : EEC_FALSE)

#define EEC_EVAL_DATUM_IS_NA(datum_ptr)											\
	(((datum_ptr)->flags & EEC_EVAL_FLAG_TYPE_NA) ? EEC_TRUE : EEC_FALSE)

#define EEC_EVAL_DATUM_IS_ERR(datum_ptr)											\
	(((datum_ptr)->flags & EEC_EVAL_FLAG_TYPE_ERR) ? EEC_TRUE : EEC_FALSE)

#define EEC_EVAL_DATUM_IS_NUMBER(datum_ptr)										\
	(((datum_ptr)->flags & EEC_EVAL_FLAG_TYPE_NUMBER) ? EEC_TRUE :			\
	EEC_FALSE)

#define EEC_EVAL_DATUM_IS_STRING(datum_ptr)										\
	((EEC_EVAL_DATUM_IS_NUMBER(datum_ptr)) ? EEC_FALSE : EEC_TRUE)

#define EEC_EVAL_DATUM_IS_EMPTY(datum_ptr)										\
	(((EEC_EVAL_DATUM_IS_NUMBER(datum_ptr) &&										\
	(!(datum_ptr)->datum.number)) ||													\
	(EEC_EVAL_DATUM_IS_STRING(datum_ptr) &&										\
	(!(datum_ptr)->datum.string.length))) ? EEC_TRUE : EEC_FALSE)

#define EEC_EVAL_DATUM_IS_NOT_EMPTY(datum_ptr)									\
	((EEC_EVAL_DATUM_IS_EMPTY(datum_ptr)) ? EEC_FALSE : EEC_TRUE)

#define EEC_EVAL_DATUM_IS_STATIC(datum_ptr)										\
	((EEC_EVAL_DATUM_IS_STRING(datum_ptr) &&										\
	(!((datum_ptr)->flags & EEC_EVAL_FLAG_ALLOCED))) ? EEC_TRUE : EEC_FALSE)

#define EEC_EVAL_DATUM_IS_ALLOCED(datum_ptr)										\
	((EEC_EVAL_DATUM_IS_STRING(datum_ptr) &&										\
	((datum_ptr)->flags & EEC_EVAL_FLAG_ALLOCED)) ? EEC_TRUE : EEC_FALSE)

#define EEC_EVAL_DATUM_GET_PTR(datum_ptr)											\
	(datum_ptr)

#define EEC_EVAL_DATUM_GET_NUMBER(datum_ptr)										\
	((datum_ptr)->datum.number)

#define EEC_EVAL_DATUM_GET_INT(datum_ptr)											\
	((int)																					\
		((EEC_EVAL_DATUM_GET_NUMBER(datum_ptr) < ((double) INT_MIN)) ?		\
		((double) INT_MIN) :																\
		(EEC_EVAL_DATUM_GET_NUMBER(datum_ptr) > ((double) INT_MAX)) ?		\
		((double) INT_MAX) : EEC_EVAL_DATUM_GET_NUMBER(datum_ptr)))

#define EEC_EVAL_DATUM_GET_UINT(datum_ptr)										\
	((unsigned int)																		\
		((EEC_EVAL_DATUM_GET_NUMBER(datum_ptr) < 0.0) ? 0.0 :					\
		(EEC_EVAL_DATUM_GET_NUMBER(datum_ptr) > ((double) UINT_MAX)) ?		\
		((double) UINT_MAX) : EEC_EVAL_DATUM_GET_NUMBER(datum_ptr)))

#define EEC_EVAL_DATUM_GET_STR_LEN(datum_ptr)									\
	((EEC_EVAL_DATUM_IS_STRING(datum_ptr)) ?										\
	(datum_ptr)->datum.string.length : 0)

#define EEC_EVAL_DATUM_GET_STR_PTR(datum_ptr)									\
	((EEC_EVAL_DATUM_IS_STRING(datum_ptr)) ?										\
	(datum_ptr)->datum.string.data : 0)

#define EEC_EVAL_DATUM_SET_NUMBER(datum_ptr, d_value)							\
	do {																						\
		(datum_ptr)->flags        = EEC_EVAL_FLAG_TYPE_NUMBER;				\
		(datum_ptr)->datum.number = (d_value);										\
		break;																				\
	} while ((datum_ptr) != NULL)

#define EEC_EVAL_DATUM_SET_STRING_STATIC(datum_ptr, str_len, str_ptr)	\
	do {																						\
		(datum_ptr)->flags               = EEC_EVAL_FLAG_TYPE_STRING;		\
		(datum_ptr)->datum.string.length = (str_len);							\
		(datum_ptr)->datum.string.data   = ((char *) str_ptr);				\
		break;																				\
	} while ((datum_ptr) != NULL)

#define EEC_EVAL_DATUM_SET_STRING_EMPTY(datum_ptr)								\
	do {																						\
		if ((datum_ptr)->flags & EEC_EVAL_FLAG_TYPE_STRING) {					\
			if ((datum_ptr)->flags & EEC_EVAL_FLAG_ALLOCED)						\
				free((datum_ptr)->datum.string.data);								\
			(datum_ptr)->datum.string.length = 0;									\
			(datum_ptr)->datum.string.data   = EEC_EVAL_EMPTY_STRING;		\
			(datum_ptr)->flags               = EEC_EVAL_FLAG_TYPE_STRING;	\
		}																						\
		break;																				\
	} while ((datum_ptr) != NULL)

#define EEC_EVAL_DATUM_SET_STR_LEN(datum_ptr, str_len)						\
	do {																						\
		(datum_ptr)->datum.string.length          = (str_len);				\
		(datum_ptr)->datum.string.data[(str_len)] = '\0';						\
		break;																				\
	} while ((datum_ptr) != NULL)

#define EEC_EVAL_DATUM_SET_SFLAG(datum_ptr, s_flag)							\
	do {																						\
		if ((datum_ptr)->flags & EEC_EVAL_FLAG_TYPE_STRING) {					\
			if ((datum_ptr)->flags & EEC_EVAL_FLAG_ALLOCED)						\
				free((datum_ptr)->datum.string.data);								\
			(datum_ptr)->datum.string.length = 0;									\
			(datum_ptr)->datum.string.data   = EEC_EVAL_EMPTY_STRING;		\
			(datum_ptr)->flags               = EEC_EVAL_FLAG_TYPE_STRING;	\
		}																						\
		else																					\
			(datum_ptr)->datum.number = 0.0;											\
			(datum_ptr)->flags |= (s_flag & EEC_EVAL_FLAG_FLAGS_SPECIAL);	\
		break;																				\
	} while ((datum_ptr) != NULL)

#define EEC_EVAL_DATUM_SET_NULL(datum_ptr)										\
	EEC_EVAL_DATUM_SET_SFLAG((datum_ptr), EEC_EVAL_FLAG_TYPE_NULL)

#define EEC_EVAL_DATUM_SET_NA(datum_ptr)											\
	EEC_EVAL_DATUM_SET_SFLAG((datum_ptr), EEC_EVAL_FLAG_TYPE_NA)

#define EEC_EVAL_DATUM_SET_ERR(datum_ptr)											\
	EEC_EVAL_DATUM_SET_SFLAG((datum_ptr), EEC_EVAL_FLAG_TYPE_ERR)

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define EEC_EVAL_TOP_IS_DATA(eval_ptr)												\
	EEC_EVAL_DATUM_IS_DATA((eval_ptr)->eval_stack_top)

#define EEC_EVAL_TOP_IS_SFLAG(eval_ptr)											\
	EEC_EVAL_DATUM_IS_SFLAG((eval_ptr)->eval_stack_top)

#define EEC_EVAL_TOP_IS_NULL(eval_ptr)												\
	EEC_EVAL_DATUM_IS_NULL((eval_ptr)->eval_stack_top)

#define EEC_EVAL_TOP_IS_NA(eval_ptr)												\
	EEC_EVAL_DATUM_IS_NA((eval_ptr)->eval_stack_top)

#define EEC_EVAL_TOP_IS_ERR(eval_ptr)												\
	EEC_EVAL_DATUM_IS_ERR((eval_ptr)->eval_stack_top)

#define EEC_EVAL_TOP_IS_NUMBER(eval_ptr)											\
	EEC_EVAL_DATUM_IS_NUMBER((eval_ptr)->eval_stack_top)

#define EEC_EVAL_TOP_IS_STRING(eval_ptr)											\
	EEC_EVAL_DATUM_IS_STRING((eval_ptr)->eval_stack_top)

#define EEC_EVAL_TOP_IS_EMPTY(eval_ptr)											\
	EEC_EVAL_DATUM_IS_STRING((eval_ptr)->eval_stack_top)

#define EEC_EVAL_TOP_IS_NOT_EMPTY(eval_ptr)										\
	EEC_EVAL_DATUM_IS_NOT_EMPTY((eval_ptr)->eval_stack_top)

#define EEC_EVAL_TOP_IS_STATIC(eval_ptr)											\
	EEC_EVAL_DATUM_IS_STATIC((eval_ptr)->eval_stack_top)

#define EEC_EVAL_TOP_IS_ALLOCED(eval_ptr)											\
	EEC_EVAL_DATUM_IS_ALLOCED((eval_ptr)->eval_stack_top)

#define EEC_EVAL_TOP_GET_PTR(eval_ptr)												\
	((eval_ptr)->eval_stack_top)

#define EEC_EVAL_TOP_GET_NUMBER(eval_ptr)											\
	EEC_EVAL_DATUM_GET_NUMBER((eval_ptr)->eval_stack_top)

#define EEC_EVAL_TOP_GET_INT(eval_ptr)												\
	EEC_EVAL_DATUM_GET_INT((eval_ptr)->eval_stack_top)

#define EEC_EVAL_TOP_GET_UINT(eval_ptr)											\
	EEC_EVAL_DATUM_GET_UINT((eval_ptr)->eval_stack_top)

#define EEC_EVAL_TOP_GET_STR_LEN(eval_ptr)										\
	EEC_EVAL_DATUM_GET_STR_LEN((eval_ptr)->eval_stack_top)

#define EEC_EVAL_TOP_GET_STR_PTR(eval_ptr)										\
	EEC_EVAL_DATUM_GET_STR_PTR((eval_ptr)->eval_stack_top)

#define EEC_EVAL_TOP_SET_NUMBER(eval_ptr, d_value)								\
	EEC_EVAL_DATUM_SET_NUMBER((eval_ptr)->eval_stack_top, d_value)

#define EEC_EVAL_TOP_SET_STRING_STATIC(eval_ptr, str_len, str_ptr)		\
	EEC_EVAL_DATUM_SET_STRING_STATIC((eval_ptr)->eval_stack_top,			\
		str_len, str_ptr)

#define EEC_EVAL_TOP_SET_STRING_EMPTY(eval_ptr)									\
	EEC_EVAL_DATUM_SET_STRING_EMPTY((eval_ptr)->eval_stack_top)

#define EEC_EVAL_TOP_SET_STR_LEN(eval_ptr, str_len)							\
	EEC_EVAL_DATUM_SET_STR_LEN((eval_ptr)->eval_stack_top, str_len)

#define EEC_EVAL_TOP_SET_SFLAG(eval_ptr, s_flag)								\
	EEC_EVAL_DATUM_SET_SFLAG((eval_ptr)->eval_stack_top, (s_flag))

#define EEC_EVAL_TOP_SET_NULL(eval_ptr)											\
	EEC_EVAL_DATUM_SET_NULL((eval_ptr)->eval_stack_top)

#define EEC_EVAL_TOP_SET_NA(eval_ptr)												\
	EEC_EVAL_DATUM_SET_NA((eval_ptr)->eval_stack_top)

#define EEC_EVAL_TOP_SET_ERR(eval_ptr)												\
	EEC_EVAL_DATUM_SET_ERR((eval_ptr)->eval_stack_top)

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define EEC_EVAL_STACK_IS_DATA(eval_ptr, stk_idx)								\
	EEC_EVAL_DATUM_IS_DATA((eval_ptr)->eval_stack + (stk_idx))

#define EEC_EVAL_STACK_IS_SFLAG(eval_ptr, stk_idx)								\
	EEC_EVAL_DATUM_IS_SFLAG((eval_ptr)->eval_stack + (stk_idx))

#define EEC_EVAL_STACK_IS_NULL(eval_ptr, stk_idx)								\
	EEC_EVAL_DATUM_IS_NULL((eval_ptr)->eval_stack + (stk_idx))

#define EEC_EVAL_STACK_IS_NA(eval_ptr, stk_idx)									\
	EEC_EVAL_DATUM_IS_NA((eval_ptr)->eval_stack + (stk_idx))

#define EEC_EVAL_STACK_IS_ERR(eval_ptr, stk_idx)								\
	EEC_EVAL_DATUM_IS_ERR((eval_ptr)->eval_stack + (stk_idx))

#define EEC_EVAL_STACK_IS_NUMBER(eval_ptr, stk_idx)							\
	EEC_EVAL_DATUM_IS_NUMBER((eval_ptr)->eval_stack + (stk_idx))

#define EEC_EVAL_STACK_IS_STRING(eval_ptr, stk_idx)							\
	EEC_EVAL_DATUM_IS_STRING((eval_ptr)->eval_stack + (stk_idx))

#define EEC_EVAL_STACK_IS_EMPTY(eval_ptr, stk_idx)								\
	EEC_EVAL_DATUM_IS_EMPTY((eval_ptr)->eval_stack + (stk_idx))

#define EEC_EVAL_STACK_IS_NOT_EMPTY(eval_ptr, stk_idx)						\
	EEC_EVAL_DATUM_IS_NOT_EMPTY((eval_ptr)->eval_stack + (stk_idx))

#define EEC_EVAL_STACK_IS_STATIC(eval_ptr, stk_idx)							\
	EEC_EVAL_DATUM_IS_STATIC((eval_ptr)->eval_stack + (stk_idx))

#define EEC_EVAL_STACK_IS_ALLOCED(eval_ptr, stk_idx)							\
	EEC_EVAL_DATUM_IS_ALLOCED((eval_ptr)->eval_stack + (stk_idx))

#define EEC_EVAL_STACK_GET_PTR(eval_ptr, stk_idx)								\
	((eval_ptr)->eval_stack + (stk_idx))

#define EEC_EVAL_STACK_GET_NUMBER(eval_ptr, stk_idx)							\
	EEC_EVAL_DATUM_GET_NUMBER((eval_ptr)->eval_stack + (stk_idx))

#define EEC_EVAL_STACK_GET_INT(eval_ptr, stk_idx)								\
	EEC_EVAL_DATUM_GET_INT((eval_ptr)->eval_stack + (stk_idx))

#define EEC_EVAL_STACK_GET_UINT(eval_ptr, stk_idx)								\
	EEC_EVAL_DATUM_GET_UINT((eval_ptr)->eval_stack + (stk_idx))

#define EEC_EVAL_STACK_GET_STR_LEN(eval_ptr, stk_idx)							\
	EEC_EVAL_DATUM_GET_STR_LEN((eval_ptr)->eval_stack + (stk_idx))

#define EEC_EVAL_STACK_GET_STR_PTR(eval_ptr, stk_idx)							\
	EEC_EVAL_DATUM_GET_STR_PTR((eval_ptr)->eval_stack + (stk_idx))

#define EEC_EVAL_STACK_SET_NUMBER(eval_ptr, stk_idx, d_value)				\
	EEC_EVAL_DATUM_SET_NUMBER((eval_ptr)->eval_stack + (stk_idx), d_value)

#define EEC_EVAL_STACK_SET_STRING_STATIC(eval_ptr, stk_idx, str_len,		\
	str_ptr)																					\
	EEC_EVAL_DATUM_SET_STRING_STATIC((eval_ptr)->eval_stack + (stk_idx),	\
		str_len, str_ptr)

#define EEC_EVAL_STACK_SET_STRING_EMPTY(eval_ptr, stk_idx)					\
	EEC_EVAL_DATUM_SET_STRING_EMPTY((eval_ptr)->eval_stack + (stk_idx))

#define EEC_EVAL_STACK_SET_STR_LEN(eval_ptr, stk_idx, str_len)				\
	EEC_EVAL_DATUM_SET_STR_LEN((eval_ptr)->eval_stack + (stk_idx), str_len)

#define EEC_EVAL_STACK_SET_SFLAG(eval_ptr, stk_idx, s_flag)					\
	EEC_EVAL_DATUM_SET_SFLAG((eval_ptr)->eval_stack + (stk_idx), (s_flag))

#define EEC_EVAL_STACK_SET_NULL(eval_ptr, stk_idx)								\
	EEC_EVAL_DATUM_SET_NULL((eval_ptr)->eval_stack + (stk_idx))

#define EEC_EVAL_STACK_SET_NA(eval_ptr, stk_idx)								\
	EEC_EVAL_DATUM_SET_NA((eval_ptr)->eval_stack + (stk_idx))

#define EEC_EVAL_STACK_SET_ERR(eval_ptr, stk_idx)								\
	EEC_EVAL_DATUM_SET_ERR((eval_ptr)->eval_stack + (stk_idx))
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define EEC_EVAL_TREF_IS_DATA(eval_ptr, tref_num)								\
	EEC_EVAL_DATUM_IS_DATA((eval_ptr)->eval_stack_top + (tref_num))

#define EEC_EVAL_TREF_IS_SFLAG(eval_ptr, tref_num)								\
	EEC_EVAL_DATUM_IS_SFLAG((eval_ptr)->eval_stack_top + (tref_num))

#define EEC_EVAL_TREF_IS_NULL(eval_ptr, tref_num)								\
	EEC_EVAL_DATUM_IS_NULL((eval_ptr)->eval_stack_top + (tref_num))

#define EEC_EVAL_TREF_IS_NA(eval_ptr, tref_num)									\
	EEC_EVAL_DATUM_IS_NA((eval_ptr)->eval_stack_top + (tref_num))

#define EEC_EVAL_TREF_IS_ERR(eval_ptr, tref_num)								\
	EEC_EVAL_DATUM_IS_ERR((eval_ptr)->eval_stack_top + (tref_num))

#define EEC_EVAL_TREF_IS_NUMBER(eval_ptr, tref_num)							\
	EEC_EVAL_DATUM_IS_NUMBER((eval_ptr)->eval_stack_top + (tref_num))

#define EEC_EVAL_TREF_IS_STRING(eval_ptr, tref_num)							\
	EEC_EVAL_DATUM_IS_STRING((eval_ptr)->eval_stack_top + (tref_num))

#define EEC_EVAL_TREF_IS_EMPTY(eval_ptr, tref_num)								\
	EEC_EVAL_DATUM_IS_EMPTY((eval_ptr)->eval_stack_top + (tref_num))

#define EEC_EVAL_TREF_IS_NOT_EMPTY(eval_ptr, tref_num)						\
	EEC_EVAL_DATUM_IS_NOT_EMPTY((eval_ptr)->eval_stack_top + (tref_num))

#define EEC_EVAL_TREF_IS_STATIC(eval_ptr, tref_num)							\
	EEC_EVAL_DATUM_IS_STATIC((eval_ptr)->eval_stack_top + (tref_num))

#define EEC_EVAL_TREF_IS_ALLOCED(eval_ptr, tref_num)							\
	EEC_EVAL_DATUM_IS_ALLOCED((eval_ptr)->eval_stack_top + (tref_num))

#define EEC_EVAL_TREF_GET_PTR(eval_ptr, tref_num)								\
	((eval_ptr)->eval_stack_top + (tref_num))

#define EEC_EVAL_TREF_GET_NUMBER(eval_ptr, tref_num)							\
	EEC_EVAL_DATUM_GET_NUMBER((eval_ptr)->eval_stack_top + (tref_num))

#define EEC_EVAL_TREF_GET_INT(eval_ptr, tref_num)								\
	EEC_EVAL_DATUM_GET_INT((eval_ptr)->eval_stack_top + (tref_num))

#define EEC_EVAL_TREF_GET_UINT(eval_ptr, tref_num)								\
	EEC_EVAL_DATUM_GET_UINT((eval_ptr)->eval_stack_top + (tref_num))

#define EEC_EVAL_TREF_GET_STR_LEN(eval_ptr, tref_num)							\
	EEC_EVAL_DATUM_GET_STR_LEN((eval_ptr)->eval_stack_top + (tref_num))

#define EEC_EVAL_TREF_GET_STR_PTR(eval_ptr, tref_num)							\
	EEC_EVAL_DATUM_GET_STR_PTR((eval_ptr)->eval_stack_top + (tref_num))

#define EEC_EVAL_TREF_SET_NUMBER(eval_ptr, tref_num, d_value)				\
	EEC_EVAL_DATUM_SET_NUMBER((eval_ptr)->eval_stack_top + (tref_num),	\
		d_value)

#define EEC_EVAL_TREF_SET_STRING_STATIC(eval_ptr, tref_num, str_len,		\
	str_ptr)																					\
	EEC_EVAL_DATUM_SET_STRING_STATIC((eval_ptr)->eval_stack_top +			\
		(tref_num), str_len, str_ptr)

#define EEC_EVAL_TREF_SET_STRING_EMPTY(eval_ptr, tref_num)					\
	EEC_EVAL_DATUM_SET_STRING_EMPTY((eval_ptr)->eval_stack_top + (tref_num))

#define EEC_EVAL_TREF_SET_STR_LEN(eval_ptr, tref_num, str_len)				\
	EEC_EVAL_DATUM_SET_STR_LEN((eval_ptr)->eval_stack_top + (tref_num),	\
	str_len)

#define EEC_EVAL_TREF_SET_SFLAG(eval_ptr, tref_num, s_flag)					\
	EEC_EVAL_DATUM_SET_SFLAG((eval_ptr)->eval_stack_top + (tref_num),		\
		(s_flag))

#define EEC_EVAL_TREF_SET_NULL(eval_ptr, tref_num)								\
	EEC_EVAL_DATUM_SET_NULL((eval_ptr)->eval_stack_top + (tref_num))

#define EEC_EVAL_TREF_SET_NA(eval_ptr, tref_num)								\
	EEC_EVAL_DATUM_SET_NA((eval_ptr)->eval_stack_top + (tref_num))

#define EEC_EVAL_TREF_SET_ERR(eval_ptr, tref_num)								\
	EEC_EVAL_DATUM_SET_ERR((eval_ptr)->eval_stack_top + (tref_num))

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define EEC_EVAL_POP(eval_ptr)														\
	do {																						\
		if ((eval_ptr)->eval_stack_count) {											\
			if (EEC_EVAL_TOP_IS_ALLOCED(eval_ptr) == EEC_TRUE)					\
				free((eval_ptr)->eval_stack_top->datum.string.data);			\
			EEC_EVAL_SUB_STACK_INDEX(eval_ptr);										\
		}																						\
		break;																				\
	} while ((eval_ptr) != NULL)

#define EEC_EVAL_POP_NUMBER(eval_ptr)												\
	EEC_EVAL_StackPopNumber(eval_ptr)

#define EEC_EVAL_POP_DOUBLE(eval_ptr)												\
	EEC_EVAL_POP_NUMBER(eval_ptr)

#define EEC_EVAL_POP_SINT(eval_ptr)													\
	((int) EEC_EVAL_POP_NUMBER(eval_ptr))

#define EEC_EVAL_POP_UINT(eval_ptr)													\
	((unsigned int) EEC_EVAL_POP_NUMBER(eval_ptr))

#define EEC_EVAL_POP_SLONG(eval_ptr)												\
	((long) EEC_EVAL_POP_NUMBER(eval_ptr))

#define EEC_EVAL_POP_ULONG(eval_ptr)												\
	((unsigned long) EEC_EVAL_POP_NUMBER(eval_ptr))

#define EEC_EVAL_PUSH_NUMBER(eval_ptr, d_value)									\
	do {																						\
		if (EEC_EVAL_NEED_MORE_STACK(eval_ptr) == EEC_TRUE)					\
			EEC_EVAL_StackAlloc(eval_ptr);											\
		EEC_EVAL_ADD_STACK_INDEX(eval_ptr);											\
		EEC_EVAL_DATUM_SET_NUMBER((eval_ptr)->eval_stack_top, d_value);	\
		break;																				\
	} while ((eval_ptr) != NULL)

#define EEC_EVAL_PUSH_STRING(eval_ptr, str_len, str_ptr)						\
	EEC_EVAL_StackPushString((eval_ptr), (str_ptr), (str_len))

#define EEC_EVAL_PUSH_STRING_STATIC(eval_ptr, str_len, str_ptr)			\
	do {																						\
		if (EEC_EVAL_NEED_MORE_STACK(eval_ptr) == EEC_TRUE)					\
			EEC_EVAL_StackAlloc(eval_ptr);											\
		EEC_EVAL_ADD_STACK_INDEX(eval_ptr);											\
		EEC_EVAL_DATUM_SET_STRING_STATIC((eval_ptr)->eval_stack_top,		\
			str_len, str_ptr);															\
		break;																				\
	} while ((eval_ptr) != NULL)

#define EEC_EVAL_PUSH_STRING_EMPTY(eval_ptr)										\
	EEC_EVAL_PUSH_STRING_STATIC(eval_ptr, 0, EEC_EVAL_EMPTY_STRING)

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Evaluation engine core supporting function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int     EEC_EVAL_StringCmp, (EEC_EVAL_DATA *eval_ptr));
COMPAT_FN_DECL(void    EEC_EVAL_StackExchange, (EEC_EVAL_DATA *eval_ptr,
	unsigned int index_1, unsigned int index_2));
COMPAT_FN_DECL(void    EEC_EVAL_StackSwap, (EEC_EVAL_DATA *eval_ptr));
COMPAT_FN_DECL(void    EEC_EVAL_StackPushNumberFlag,
	(EEC_EVAL_DATA *eval_ptr, unsigned int flags));
COMPAT_FN_DECL(void    EEC_EVAL_StackPushStringFlag,
	(EEC_EVAL_DATA *eval_ptr, unsigned int flags));
COMPAT_FN_DECL(void    EEC_EVAL_StackPushNumber, (EEC_EVAL_DATA *eval_ptr,
	double value));
COMPAT_FN_DECL(char   *EEC_EVAL_StackPushString, (EEC_EVAL_DATA *eval_ptr,
	const char *string_ptr, unsigned int string_length));
COMPAT_FN_DECL(char   *EEC_EVAL_StackPushStringZ, (EEC_EVAL_DATA *eval_ptr,
	const char *string_ptr));
COMPAT_FN_DECL(char   *EEC_EVAL_StackPushStringStatic,
	(EEC_EVAL_DATA *eval_ptr, const char *string_ptr,
	unsigned int string_length));
COMPAT_FN_DECL(char   *EEC_EVAL_StackPushStringZStatic,
	(EEC_EVAL_DATA *eval_ptr, const char *string_ptr));
COMPAT_FN_DECL(char   *EEC_EVAL_StackPushStringEmpty,
	(EEC_EVAL_DATA *eval_ptr));
COMPAT_FN_DECL(void    EEC_EVAL_StackPush, (EEC_EVAL_DATA *eval_ptr,
	int datum_type, const void *datum_ptr, unsigned int datum_length));
COMPAT_FN_DECL(void    EEC_EVAL_StackPushDatum, (EEC_EVAL_DATA *eval_ptr,
	EEC_DATUM *datum_ptr));
COMPAT_FN_DECL(void    EEC_EVAL_StackAlloc, (EEC_EVAL_DATA *eval_ptr));
COMPAT_FN_DECL(int     EEC_EVAL_StackAllocBasic, (EEC_EVAL_DATA *eval_ptr,
	char *error_text));
COMPAT_FN_DECL(int     EEC_EVAL_PopIfSFlagsNumber,
	(EEC_EVAL_DATA *eval_ptr, unsigned int datum_count));
COMPAT_FN_DECL(int     EEC_EVAL_PopIfSFlagsString,
	(EEC_EVAL_DATA *eval_ptr, unsigned int datum_count));
COMPAT_FN_DECL(int     EEC_EVAL_PopIfSFlags, (EEC_EVAL_DATA *eval_ptr,
	unsigned int datum_count, unsigned int datum_type));
COMPAT_FN_DECL(int     EEC_EVAL_FindSFlags, (EEC_EVAL_DATA *eval_ptr,
	unsigned int index_1, unsigned int index_2, unsigned int flags,
	int find_highest_flag, unsigned int *found_index));
COMPAT_FN_DECL(void    EEC_EVAL_StaticToAlloced, (EEC_EVAL_DATA *eval_ptr,
	EEC_DATUM *datum_ptr));
COMPAT_FN_DECL(char   *EEC_EVAL_StringAllocDatum, (EEC_EVAL_DATA *eval_ptr,
	unsigned int string_length, EEC_DATUM *datum_ptr));
COMPAT_FN_DECL(char   *EEC_EVAL_StringAlloc, (EEC_EVAL_DATA *eval_ptr,
	unsigned int string_length));
COMPAT_FN_DECL(EEC_DATUM *EEC_EVAL_StackPop, (EEC_EVAL_DATA *eval_ptr,
	unsigned int pop_count));
COMPAT_FN_DECL(EEC_DATUM *EEC_EVAL_StackPopTop, (EEC_EVAL_DATA *eval_ptr));
COMPAT_FN_DECL(double  EEC_EVAL_StackPopNumber, (EEC_EVAL_DATA *eval_ptr));
COMPAT_FN_DECL(void    EEC_EVAL_StackClear, (EEC_EVAL_DATA *eval_ptr));
COMPAT_FN_DECL(void    EEC_EVAL_ErrorJmp, (EEC_EVAL_DATA *eval_ptr,
	char *function, int return_code, char *descriptive_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Evaluation engine built-in function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void EEC_EVAL_FUNC_Ascii,
	(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count));
COMPAT_FN_DECL(void EEC_EVAL_FUNC_Center,
	(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count));
COMPAT_FN_DECL(void EEC_EVAL_FUNC_Char,
	(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count));
COMPAT_FN_DECL(void EEC_EVAL_FUNC_Choose,
	(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count));
COMPAT_FN_DECL(void EEC_EVAL_FUNC_Concatenate,
	(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count));
COMPAT_FN_DECL(void EEC_EVAL_FUNC_Err,
	(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count));
COMPAT_FN_DECL(void EEC_EVAL_FUNC_Fixed,
	(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count));
COMPAT_FN_DECL(void EEC_EVAL_FUNC_If,
	(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count));
COMPAT_FN_DECL(void EEC_EVAL_FUNC_Join,
	(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count));
COMPAT_FN_DECL(void EEC_EVAL_FUNC_Left,
	(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count));
COMPAT_FN_DECL(void EEC_EVAL_FUNC_LeftPad,
	(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count));
COMPAT_FN_DECL(void EEC_EVAL_FUNC_Len,
	(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count));
COMPAT_FN_DECL(void EEC_EVAL_FUNC_Lower,
	(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count));
COMPAT_FN_DECL(void EEC_EVAL_FUNC_LTrim,
	(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count));
COMPAT_FN_DECL(void EEC_EVAL_FUNC_Mid,
	(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count));
COMPAT_FN_DECL(void EEC_EVAL_FUNC_NA,
	(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count));
COMPAT_FN_DECL(void EEC_EVAL_FUNC_Null,
	(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count));
COMPAT_FN_DECL(void EEC_EVAL_FUNC_Pi,
	(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count));
COMPAT_FN_DECL(void EEC_EVAL_FUNC_Pow,
	(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count));
COMPAT_FN_DECL(void EEC_EVAL_FUNC_Rand,
	(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count));
COMPAT_FN_DECL(void EEC_EVAL_FUNC_Right,
	(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count));
COMPAT_FN_DECL(void EEC_EVAL_FUNC_RightPad,
	(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count));
COMPAT_FN_DECL(void EEC_EVAL_FUNC_RTrim,
	(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count));
COMPAT_FN_DECL(void EEC_EVAL_FUNC_Sqrt,
	(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count));
COMPAT_FN_DECL(void EEC_EVAL_FUNC_Trim,
	(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count));
COMPAT_FN_DECL(void EEC_EVAL_FUNC_Upper,
	(EEC_EVAL_DATA *eval_ptr, unsigned int arg_count));
	/*	*****************************************************************	*/

/*	***********************************************************************	*/

#endif /* #ifndef h__EVALDEFS_H__h */

