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

	Revision History	:	1993-02-01 --- Creation.
									Michael L. Brock
								1996-02-03 ---- Version 5 changes.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include "eecfunci.h"
#include "evaldefs.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
const EEC_FUNC_DEF EEC_FunctionDefList[] = {
	{	"Ascii",				0L,	EEC_FUNC_ARG_TYPE_NUMBER,	0,		1,		1,
		{	EEC_FUNC_ARG_TYPE_STRING,
			0, 0, 0, 0  },
		EEC_FALSE,	EEC_EVAL_FUNC_Ascii
	},
	{	"Center",			0L,	EEC_FUNC_ARG_TYPE_STRING,	0,		2,		5,
		{	EEC_FUNC_ARG_TYPE_STRING,
			EEC_FUNC_ARG_TYPE_NUMBER,
			EEC_FUNC_ARG_TYPE_STRING,
			EEC_FUNC_ARG_TYPE_NUMBER,
			EEC_FUNC_ARG_TYPE_NUMBER	},
		EEC_FALSE,	EEC_EVAL_FUNC_Center
	},
	{	"Char",				0L,	EEC_FUNC_ARG_TYPE_STRING,	0,		1,		1,
		{	EEC_FUNC_ARG_TYPE_NUMBER,
			0, 0, 0, 0  },
		EEC_FALSE,	EEC_EVAL_FUNC_Char
	},
	{	"Choose",			0L,	EEC_FUNC_ARG_TYPE_ANY,		1,		3,		UINT_MAX,
		{	EEC_FUNC_ARG_TYPE_NUMBER,
			EEC_FUNC_ARG_TYPE_ANY,
			EEC_FUNC_ARG_TYPE_PREVIOUS,
			EEC_FUNC_ARG_TYPE_PREVIOUS,	0	},
		EEC_FALSE,	EEC_EVAL_FUNC_Choose
	},
	{	"Concatenate",		0L,	EEC_FUNC_ARG_TYPE_STRING,	0,		1,		UINT_MAX,
		{	EEC_FUNC_ARG_TYPE_STRING,
			0, 0, 0, 0  },
		EEC_FALSE,	EEC_EVAL_FUNC_Concatenate
	},
	{	"ERR",				0L,	EEC_FUNC_ARG_TYPE_NUMBER,	0,		0,		0,
		{	0,	0,	0,	0,	0	},
		EEC_FALSE,	EEC_EVAL_FUNC_Err
	},
	{	"Fixed",				0L,	EEC_FUNC_ARG_TYPE_STRING,	0,		1,		5,
		{	EEC_FUNC_ARG_TYPE_NUMBER,
			EEC_FUNC_ARG_TYPE_NUMBER,
			EEC_FUNC_ARG_TYPE_NUMBER,
			EEC_FUNC_ARG_TYPE_STRING,
			EEC_FUNC_ARG_TYPE_STRING	},
		EEC_FALSE,	EEC_EVAL_FUNC_Fixed
	},
	{	"If",					0L,	EEC_FUNC_ARG_TYPE_ANY,		1,		3,		3,
		{	EEC_FUNC_ARG_TYPE_ANY,
			EEC_FUNC_ARG_TYPE_ANY,
			EEC_FUNC_ARG_TYPE_PREVIOUS,
			0,	0	},
		EEC_FALSE,	EEC_EVAL_FUNC_If
	},
	{	"Join",				0L,	EEC_FUNC_ARG_TYPE_STRING,	1,		3,		UINT_MAX,
		{	EEC_FUNC_ARG_TYPE_STRING,
			EEC_FUNC_ARG_TYPE_ANY,
			EEC_FUNC_ARG_TYPE_ANY,
			0,	0	},
		EEC_FALSE,	EEC_EVAL_FUNC_Join
	},
	{	"Left",				0L,	EEC_FUNC_ARG_TYPE_STRING,	0,		1,		2,
		{	EEC_FUNC_ARG_TYPE_STRING,
			EEC_FUNC_ARG_TYPE_NUMBER,
			0,	0, 0	},
		EEC_FALSE,	EEC_EVAL_FUNC_Left
	},
	{	"LeftPad",			0L,	EEC_FUNC_ARG_TYPE_STRING,	0,		2,		5,
		{	EEC_FUNC_ARG_TYPE_STRING,
			EEC_FUNC_ARG_TYPE_NUMBER,
			EEC_FUNC_ARG_TYPE_STRING,
			EEC_FUNC_ARG_TYPE_NUMBER,
			EEC_FUNC_ARG_TYPE_NUMBER	},
		EEC_FALSE,	EEC_EVAL_FUNC_LeftPad
	},
	{	"Len",				0L,	EEC_FUNC_ARG_TYPE_NUMBER,	0,		1,		1,
		{	EEC_FUNC_ARG_TYPE_STRING,
			0, 0, 0, 0  },
		EEC_FALSE,	EEC_EVAL_FUNC_Len
	},
	{	"Lower",				0L,	EEC_FUNC_ARG_TYPE_STRING,	0,		1,		1,
		{	EEC_FUNC_ARG_TYPE_STRING,
			0,	0,	0, 0	},
		EEC_FALSE,	EEC_EVAL_FUNC_Lower
	},
	{	"LTrim",				0L,	EEC_FUNC_ARG_TYPE_STRING,	0,		1,		2,
		{	EEC_FUNC_ARG_TYPE_STRING,
			EEC_FUNC_ARG_TYPE_STRING,
			0,	0, 0	},
		EEC_FALSE,	EEC_EVAL_FUNC_LTrim
	},
	{	"Mid",				0L,	EEC_FUNC_ARG_TYPE_STRING,	0,		1,		3,
		{	EEC_FUNC_ARG_TYPE_STRING,
			EEC_FUNC_ARG_TYPE_NUMBER,
			EEC_FUNC_ARG_TYPE_NUMBER,
			0, 0	},
		EEC_FALSE,	EEC_EVAL_FUNC_Mid
	},
	{	"NA",					0L,	EEC_FUNC_ARG_TYPE_NUMBER,	0,		0,		0,
		{	0,	0,	0,	0,	0	},
		EEC_FALSE,	EEC_EVAL_FUNC_NA
	},
	{	"Null",				0L,	EEC_FUNC_ARG_TYPE_NUMBER,	0,		0,		0,
		{	0,	0,	0,	0,	0	},
		EEC_FALSE,	EEC_EVAL_FUNC_Null
	},
	{	"Pi",					0L,	EEC_FUNC_ARG_TYPE_NUMBER,	0,		0,		0,
		{	0,	0,	0,	0,	0	},
		EEC_FALSE,	EEC_EVAL_FUNC_Pi
	},
	{	"Pow", 				0L,	EEC_FUNC_ARG_TYPE_NUMBER,	0,		2,		2,
		{	EEC_FUNC_ARG_TYPE_NUMBER,
			EEC_FUNC_ARG_TYPE_NUMBER,
			0,	0, 0	},
		EEC_FALSE,	EEC_EVAL_FUNC_Pow
	},
	{	"Rand",				0L,	EEC_FUNC_ARG_TYPE_NUMBER,	0,		0,		0,
		{	0,	0,	0,	0,	0	},
		EEC_TRUE,	EEC_EVAL_FUNC_Rand
	},
	{	"Right",				0L,	EEC_FUNC_ARG_TYPE_STRING,	0,		1,		2,
		{	EEC_FUNC_ARG_TYPE_STRING,
			EEC_FUNC_ARG_TYPE_NUMBER,
			0,	0, 0	},
		EEC_FALSE,	EEC_EVAL_FUNC_Right
	},
	{	"RightPad",			0L,	EEC_FUNC_ARG_TYPE_STRING,	0,		2,		5,
		{	EEC_FUNC_ARG_TYPE_STRING,
			EEC_FUNC_ARG_TYPE_NUMBER,
			EEC_FUNC_ARG_TYPE_STRING,
			EEC_FUNC_ARG_TYPE_NUMBER,
			EEC_FUNC_ARG_TYPE_NUMBER	},
		EEC_FALSE,	EEC_EVAL_FUNC_RightPad
	},
	{	"RTrim",				0L,	EEC_FUNC_ARG_TYPE_STRING,	0,		1,		2,
		{	EEC_FUNC_ARG_TYPE_STRING,
			EEC_FUNC_ARG_TYPE_STRING,
			0,	0, 0	},
		EEC_FALSE,	EEC_EVAL_FUNC_RTrim
	},
	{	"Sqrt", 				0L,	EEC_FUNC_ARG_TYPE_NUMBER,	0,		1,		1,
		{	EEC_FUNC_ARG_TYPE_NUMBER,
			0,	0,	0, 0	},
		EEC_FALSE,	EEC_EVAL_FUNC_Sqrt
	},
	{	"Trim",				0L,	EEC_FUNC_ARG_TYPE_STRING,	0,		1,		2,
		{	EEC_FUNC_ARG_TYPE_STRING,
			EEC_FUNC_ARG_TYPE_STRING,
			0,	0, 0	},
		EEC_FALSE,	EEC_EVAL_FUNC_Trim
	},
	{	"Upper",				0L,	EEC_FUNC_ARG_TYPE_STRING,	0,		1,		1,
		{	EEC_FUNC_ARG_TYPE_STRING,
			0,	0,	0, 0	},
		EEC_FALSE,	EEC_EVAL_FUNC_Upper
	},
};
/*	***********************************************************************	*/

/*	***********************************************************************	*/
const unsigned int EEC_FunctionDefCount                           =
	sizeof(EEC_FunctionDefList) / sizeof(EEC_FunctionDefList[0]);
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_GetBuiltInFuncDefs(unsigned int *func_count,
	const EEC_FUNC_DEF **func_list)
#else
void EEC_GetBuiltInFuncDefs(func_count, func_list)
unsigned int        *func_count;
const EEC_FUNC_DEF **func_list;
#endif /* #ifndef NARGS */
{
	*func_count = EEC_FunctionDefCount;
	*func_list  = EEC_FunctionDefList;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int EEC_CopyBuiltInFuncDefs(unsigned int *func_count, EEC_FUNC_DEF **func_list,
	char *error_text)
#else
int EEC_CopyBuiltInFuncDefs(func_count, func_list, error_text)
unsigned int  *func_count;
EEC_FUNC_DEF **func_list;
char          *error_text;
#endif /* #ifndef NARGS */
{
	return(EEC_COPY_FuncDefList(EEC_FunctionDefCount, EEC_FunctionDefList,
		func_count, func_list, error_text));
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

COMPAT_FN_DECL(int main, (void));
COMPAT_FN_DECL_STATIC(void EEC_EMIT_CommentSep, (void));

int main()
{
	int                 return_code = EEC_SUCCESS;
	unsigned int        count_1;
	unsigned int        count_2;
	unsigned int        optional_count;
	unsigned int        func_count;
	const EEC_FUNC_DEF *func_list;
	const EEC_FUNC_DEF *func_ptr;
	char                error_text[EEC_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'EEC_GetBuiltInFuncDefs()'\n");
	fprintf(stderr, "---- ------- --- --------------------------\n\n");

	EEC_GetBuiltInFuncDefs(&func_count, &func_list);

	for (count_1 = 0, func_ptr = func_list; count_1 < func_count;
		count_1++, func_ptr++) {
		EEC_EMIT_CommentSep();
		EEC_EMIT_CommentSep();
		printf("/*\tBOH\n\n");
		printf("\tNAME\t\t\t:\t%s\n\n", func_ptr->func_name);
		printf("\tSYNOPSIS\t\t:\t");
		if (func_ptr->func_type == EEC_FUNC_ARG_TYPE_ANY)
			printf("``type-of-parameter-```'%u`'", func_ptr->func_type_arg + 1);
		else
			printf("``%s``",
				(func_ptr->func_type == EEC_FUNC_ARG_TYPE_NUMBER) ? "number" :
				"string");
		printf(" = @%s(", func_ptr->func_name);
		optional_count = 0;
		for (count_2 = 0; count_2 < EEC_FUNC_MAX_FIXED_ARGS; count_2++) {
			if (count_2 >= func_ptr->func_max_args)
				break;
			else if (count_2 >= func_ptr->func_min_args) {
				printf(" ''[''");
				optional_count++;
			}
			if (count_2)
				printf(", ");
			switch (func_ptr->func_args[count_2]) {
				case EEC_FUNC_ARG_TYPE_NUMBER		:
					printf("``number```'%u`'", count_2 + 1);
					break;
				case EEC_FUNC_ARG_TYPE_STRING		:
					printf("``string```'%u`'", count_2 + 1);
					break;
				case EEC_FUNC_ARG_TYPE_ANY			:
					printf("``number-or-string```'%u`'", count_2 + 1);
					break;
				case EEC_FUNC_ARG_TYPE_PREVIOUS	:
					printf("``same-as-parameter```'%u`'", count_2);
					break;
				default									:
					sprintf(error_text, "%s %u %s '%s' ('%d').",
						"Invalid parameter number", count_2 + 1,
						"specification for function", func_ptr->func_name,
						func_ptr->func_args[count_2]);
					return_code = EEC_FAILURE;
					goto EXIT_FUNCTION;
			}
			if (count_2 > func_ptr->func_min_args)
				break;
		}
		if (func_ptr->func_max_args == UINT_MAX) {
			optional_count++;
			printf("``same-as-parameter```'%u`'", func_ptr->func_min_args + 1);
		}
		if (optional_count) {
			printf("''");
			STR_EMIT_Char(']', optional_count, NULL, NULL);
			printf("''");
		}
		printf(")\n\n");
		printf("\tDESCRIPTION\t:\t\n\n");
		printf("\tPARAMETERS\t:\t%s:\n\n",
			"Parameters to this function are as follow");
		printf("EOH */\n");
		EEC_EMIT_CommentSep();
		printf("\n");
	}

EXIT_FUNCTION:

	if (return_code != EEC_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

static void EEC_EMIT_CommentSep()
{
	printf("/*\t");
	STR_EMIT_Char('*', 71, NULL, NULL);
	printf("\t*/\n");
}

#endif /* #ifdef TEST_MAIN */

