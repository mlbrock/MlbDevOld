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

	Revision History	:	1993-04-04 --- Creation.
									Michael L. Brock
								1996-02-10 --- Working version 5 changes.
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

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parsedat.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
typedef struct tag_EEC_INFIX {
	unsigned int          type;
	unsigned int          length;
	char                 *data;
	unsigned int          arg_count;
	struct tag_EEC_INFIX *arg_ptr;
	int                   precedence;
} EEC_INFIX;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Function prototypes for functions private to this module . . .				*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(int EEC_AssembleInfix, (const EEC_POSTFIX *postfix_ptr,
	unsigned int *infix_count, EEC_INFIX **infix_list, char *error_text));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int EEC_GetInfixFormula(const EEC_POSTFIX *postfix_ptr, int space_flag,
	char **infix_ptr, char *error_text)
#else
int EEC_GetInfixFormula(postfix_ptr, space_flag, infix_ptr, error_text)
const EEC_POSTFIX  *postfix_ptr;
int                 space_flag;
char              **infix_ptr;
char               *error_text;
#endif /* #ifndef NARGS */
{
	int              return_code;
	unsigned int     infix_count = 0;
	EEC_INFIX       *infix_list  = NULL;
	unsigned int     tmp_length  = 0;
	EEC_INFIX       *infix_ptr_1;
	EEC_INFIX       *infix_ptr_2;
	unsigned int     count_1;
	unsigned int     count_2;
	unsigned int     first_arg;
	char            *tmp_string;

	*infix_ptr = NULL;

	if ((return_code = EEC_AssembleInfix(postfix_ptr, &infix_count,
		&infix_list, error_text)) != EEC_SUCCESS)
		goto EXIT_FUNCTION;

	*error_text = '\0';

	for (count_1 = 0; count_1 < infix_count; ) {
		switch (infix_list[count_1].type) {
			case EEC_TYPE_ANY			:
			case EEC_TYPE_NUMBER		:
			case EEC_TYPE_STRING		:
			case EEC_TYPE_SYMBOL		:
				count_1++;
				break;
			case EEC_TYPE_FUNCTION	:
				tmp_length = 1 + infix_list[count_1].length + 1 +
					(infix_list[count_1].arg_count * ((space_flag) ? 2 : 1)) + 1;
				first_arg  = count_1 - infix_list[count_1].arg_count;
				for (count_2 = first_arg; count_2 < count_1; count_2++)
					tmp_length += infix_list[count_2].length;
				if ((tmp_string = ((char *) calloc(tmp_length + 1,
					sizeof(char)))) == NULL) {
					return_code = EEC_MEMORY_FAILURE;
					goto EXIT_FUNCTION;
				}
				strcat(strcat(strcpy(tmp_string, "@"), infix_list[count_1].data),
					"(");
				free(infix_list[count_1].data);
				for (count_2 = first_arg; count_2 < count_1; count_2++) {
					strcat(strcat(tmp_string, infix_list[count_2].data),
						(count_2 < (count_1 - 1)) ? ((space_flag) ? ", " : ",") :
						"");
					free(infix_list[count_2].data);
				}
				strcat(tmp_string, ")");
				mema_remove(&infix_count, ((void **) &infix_list),
					sizeof(*infix_list), first_arg, infix_list[count_1].arg_count);
				infix_list[first_arg].type       = EEC_TYPE_ANY;
				infix_list[first_arg].length     = tmp_length;
				infix_list[first_arg].data       = tmp_string;
				infix_list[first_arg].arg_count  = 0;
				infix_list[first_arg].precedence = -1;
				count_1                          = first_arg + 1;
				break;
			case EEC_TYPE_OPERATOR	:
				infix_ptr_1 = infix_list + (count_1 - 2);
				infix_ptr_2 = infix_list + (count_1 - 1);
				if ((infix_ptr_1->precedence != -1) &&
					(infix_ptr_1->precedence < infix_list[count_1].precedence)) {
					tmp_length = 1 + infix_ptr_1->length + 1;
					if ((tmp_string = ((char *) calloc(tmp_length + 1,
						sizeof(char)))) == NULL) {
						return_code = EEC_MEMORY_FAILURE;
						goto EXIT_FUNCTION;
					}
					strcat(strcat(strcpy(tmp_string, "("), infix_ptr_1->data), ")");
					free(infix_ptr_1->data);
					infix_ptr_1->length = tmp_length;
					infix_ptr_1->data   = tmp_string;
				}
				if ((infix_ptr_2->precedence != -1) &&
					(infix_ptr_2->precedence <= infix_list[count_1].precedence)) {
					tmp_length = 1 + infix_ptr_2->length + 1;
					if ((tmp_string = ((char *) calloc(tmp_length + 1,
						sizeof(char)))) == NULL) {
						return_code = EEC_MEMORY_FAILURE;
						goto EXIT_FUNCTION;
					}
					strcat(strcat(strcpy(tmp_string, "("), infix_ptr_2->data), ")");
					free(infix_ptr_2->data);
					infix_ptr_2->length = tmp_length;
					infix_ptr_2->data   = tmp_string;
				}
				tmp_length = infix_ptr_1->length + infix_list[count_1].length +
					infix_ptr_2->length + ((space_flag) ? 2 : 0);
				if ((tmp_string = ((char *) calloc(tmp_length + 1,
					sizeof(char)))) == NULL) {
					return_code = EEC_MEMORY_FAILURE;
					goto EXIT_FUNCTION;
				}
				if (!space_flag)
					strcat(strcat(strcpy(tmp_string, infix_ptr_1->data),
						infix_list[count_1].data), infix_ptr_2->data);
				else
					strcat(strcat(strcat(strcat(strcpy(tmp_string,
						infix_ptr_1->data), " "), infix_list[count_1].data), " "),
						infix_ptr_2->data);
				free(infix_ptr_1->data);
				free(infix_ptr_2->data);
				free(infix_list[count_1].data);
				infix_ptr_1->type       = EEC_TYPE_ANY;
				infix_ptr_1->length     = tmp_length;
				infix_ptr_1->data       = tmp_string;
				infix_ptr_1->arg_count  = 0;
				infix_ptr_1->precedence =
					(infix_ptr_1->precedence > infix_list[count_1].precedence) ?
					infix_ptr_1->precedence : infix_list[count_1].precedence;
				infix_ptr_1->precedence =
					(infix_ptr_1->precedence > infix_ptr_2->precedence) ?
					infix_ptr_1->precedence : infix_ptr_2->precedence;
				mema_remove(&infix_count, ((void **) &infix_list),
					sizeof(*infix_list), count_1 - 1, 2);
				count_1--;
				break;
		}
	}

	if (infix_count == 1) {
		*infix_ptr       = infix_list->data;
		infix_list->data = NULL;
	}
	else {
		sprintf(error_text, "%s --- %s, actual remaining is %u item%s.",
			"Error in attempt to compose post-fix string as infix",
			"expected 1 infix token to remain", infix_count,
			(infix_count == 1) ? "" : "s");
		return_code = EEC_FAILURE;
	}

EXIT_FUNCTION:

	for (count_1 = 0; count_1 < infix_count; count_1++) {
		if (infix_list[count_1].data != NULL)
			free(infix_list[count_1].data);
	}
	mema_remove_all(&infix_count, ((void **) &infix_list));

	if ((return_code == EEC_MEMORY_FAILURE) && (!(*error_text)))
		STR_AllocMsgItem(tmp_length + 1, error_text,
			"Unable to allocate memory to concatenate infix tokens");

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int EEC_AssembleInfix(const EEC_POSTFIX *postfix_ptr,
	unsigned int *infix_count, EEC_INFIX **infix_list, char *error_text)
#else
static int EEC_AssembleInfix(postfix_ptr, infix_count, infix_list, error_text)
const EEC_POSTFIX  *postfix_ptr;
unsigned int       *infix_count;
EEC_INFIX         **infix_list;
char               *error_text;
#endif /* #ifndef NARGS */
{
	int                 return_code = EEC_SUCCESS;
	unsigned int        count_1;
	const char         *data_ptr;
	const char         *tmp_ptr;
	unsigned int        tmp_length;
	char               *tmp_string;
   unsigned short      arg_count;
	unsigned short      tmp_short;
	unsigned int        tmp_int;
	unsigned long       tmp_long;
	double              tmp_double;
	unsigned int        size;
	char                *buffer_ptr;
   EEC_INFIX           tmp_infix;
	char                buffer[EEC_MAX_NUMBER_LENGTH + 1];
	unsigned int        builtin_func_def_count;
	const EEC_FUNC_DEF *builtin_func_def_list;

	*infix_count = 0;
	*infix_list  = NULL;

	data_ptr     = postfix_ptr->data;

	EEC_GetBuiltInFuncDefs(&builtin_func_def_count, &builtin_func_def_list);

	for (count_1 = 0; count_1 < postfix_ptr->length; count_1++, data_ptr++) {
		tmp_infix.type       = *data_ptr;
		tmp_infix.length     = 0;
		tmp_infix.data       = NULL;
		tmp_infix.arg_count  = 0;
		tmp_infix.arg_ptr    = NULL;
		tmp_infix.precedence = -1;
		switch (*data_ptr) {
			case EEC_PFIX_TYPE_NUMBER		:
				tmp_infix.type = EEC_TYPE_NUMBER;
				ECC_GET_PFIX_NUMBER(data_ptr, &tmp_double);
				sprintf(buffer, "%*.16f", sizeof(buffer) - 1, tmp_double);
				noblank(buffer);
				if (((buffer_ptr = strchr(buffer, 'e')) == NULL) &&
					((buffer_ptr = strchr(buffer, 'E')) == NULL)) {
					while (*buffer &&
						(buffer[tmp_length = (strlen(buffer) - 1)] == '0'))
						buffer[tmp_length] = '\0';
					if (buffer[tmp_length = (strlen(buffer) - 1)] == '.')
						buffer[tmp_length] = '\0';
				}
				else {
					buffer_ptr--;
					while ((buffer_ptr >= buffer) && (*buffer_ptr == '0'))
						strdele(buffer_ptr--, 0, 1);
					if (*buffer_ptr == '.')
						strdele(buffer_ptr--, 0, 1);
				}
				tmp_length = strlen(buffer);
				if ((tmp_string = strdup(buffer)) == NULL) {
					STR_AllocMsgItem(tmp_length + 1, error_text,
						"Unable to allocate memory for infix number");
					return_code = EEC_MEMORY_FAILURE;
					goto EXIT_FUNCTION;
				}
				size = sizeof(double);
				break;
			case EEC_PFIX_TYPE_STRING		:
				tmp_infix.type = EEC_TYPE_STRING;
				EEC_GET_PFIX_STRING(data_ptr, &tmp_int, &tmp_ptr);
				if ((EEC_StringToHumanString(tmp_int, tmp_ptr, EEC_TRUE,
					&tmp_string, error_text)) != EEC_SUCCESS) {
					strinst(error_text,
						"Unable to allocate memory for infix string", 0);
					goto EXIT_FUNCTION;
				}
				tmp_length = strlen(tmp_string);
				size       = sizeof(unsigned int) + tmp_int + 1;
				break;
			case EEC_PFIX_TYPE_FUNCTION	:
				tmp_infix.type = EEC_TYPE_FUNCTION;
				EEC_GET_PFIX_FUNCTION(data_ptr, &tmp_long, &arg_count,
					&tmp_short, &tmp_ptr);
				tmp_infix.arg_count = arg_count;
				tmp_length          = ((unsigned int) tmp_short);
				if (tmp_length)
					buffer_ptr = ((char *) tmp_ptr);
				else if (tmp_long < ((unsigned long) USHRT_MAX)) {
					buffer_ptr = ((char *)
						builtin_func_def_list[((unsigned int) tmp_long)].func_name);
					tmp_length = strlen(buffer_ptr);
				}
				else {
					sprintf(buffer, "<external-function-id-%010lu>", tmp_long);
					buffer_ptr = buffer;
					tmp_length = strlen(buffer_ptr);
				}
				if ((tmp_string = strndup(buffer_ptr, tmp_length)) == NULL) {
					STR_AllocMsgItem(tmp_length + 1, error_text,
						"Unable to allocate memory for infix function");
					return_code = EEC_MEMORY_FAILURE;
					goto EXIT_FUNCTION;
				}
				size = sizeof(unsigned long) + (sizeof(unsigned short) * 2) +
					((unsigned int) tmp_short);
				break;
			case EEC_PFIX_TYPE_SYMBOL		:
				tmp_infix.type = EEC_TYPE_SYMBOL;
				EEC_GET_PFIX_SYMBOL(data_ptr, &tmp_long, &tmp_short, &tmp_ptr);
				tmp_length = ((unsigned int) tmp_short);
				if (tmp_length)
					buffer_ptr = ((char *) tmp_ptr);
				else {
					sprintf(buffer, "<external-symbol-id-%010lu>", tmp_long);
					buffer_ptr = buffer;
					tmp_length = strlen(buffer_ptr);
				}
				if ((tmp_string = strndup(buffer_ptr, tmp_length)) == NULL) {
					STR_AllocMsgItem(tmp_length + 1, error_text,
						"Unable to allocate memory for infix symbol");
					return_code = EEC_MEMORY_FAILURE;
					goto EXIT_FUNCTION;
				}
				size = sizeof(unsigned long) + sizeof(unsigned short) +
					((unsigned int) tmp_short);
				break;
			default								:
				if (*data_ptr >= EEC_OPERATOR_COUNT) {
					sprintf(error_text, "%s (character = %u).",
						"Unknown item encountered in post-fix string",
						((unsigned int) *((unsigned char *) data_ptr)));
					return_code = EEC_FAILURE;
					goto EXIT_FUNCTION;
				}
				tmp_infix.type       = EEC_TYPE_OPERATOR;
				tmp_infix.precedence =
					EEC_OperatorList[((unsigned int) *data_ptr)].precedence;
				tmp_length           =
					strlen(EEC_OperatorList[((unsigned int) *data_ptr)].
						preferred_operator);
				if ((tmp_string =
					strdup(EEC_OperatorList[((unsigned int) *data_ptr)].
					preferred_operator)) == NULL) {
					STR_AllocMsgItem(tmp_length + 1, error_text,
						"Unable to allocate memory for infix operator");
					return_code = EEC_MEMORY_FAILURE;
					goto EXIT_FUNCTION;
				}
				size = 0;
				break;
		}
		tmp_infix.length = tmp_length;
		tmp_infix.data   = tmp_string;
		if (mema_append(infix_count, ((void **) infix_list), &tmp_infix,
			sizeof(tmp_infix)) != STRFUNCS_SUCCESS) {
			free(tmp_string);
			STR_AllocMsgList(*infix_count + 1, sizeof(**infix_list), error_text,
				"Unable to add to the temporary working infix data list");
			return_code = EEC_MEMORY_FAILURE;
			goto EXIT_FUNCTION;
		}
		count_1  += size;
		data_ptr += size;
	}

EXIT_FUNCTION:

	if (return_code != EEC_SUCCESS) {
		for (count_1 = 0; count_1 < *infix_count; count_1++)
			free((*infix_list)[count_1].data);
		mema_remove_all(infix_count, ((void **) infix_list));
	}

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#ifdef __MSDOS__
COMPAT_EXTERN_DATA_DECL unsigned int _stklen = 16384;
#endif /* __MSDOS__ */

COMPAT_FN_DECL(int main, (void));

int main()
{
	int           return_code = EEC_SUCCESS;
	unsigned int  count_1;
	EEC_CONTROL   control_data;
	unsigned int  parse_index;
	EEC_POSTFIX   postfix_data;
	char         *infix_ptr;
	char          in_text[512];
	char          tmp_in_text[512];
	char          error_text[EEC_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'EEC_GetInfixFormula()'\n");
	fprintf(stderr, "---- ------- --- -----------------------\n\n");

	fprintf(stderr, "USAGE:\n------\n%s%s\n",
		"   Enter an expression to be parsed.\n",
		"   Enter 'QUIT' or 'EXIT' to exit.\n");

	EEC_INIT_EEC_CONTROL(&control_data);

	return_code = EEC_CreateControl(&control_data, error_text);

	while (return_code == EEC_SUCCESS) {
		do {
			*in_text = '\0';
			fprintf(stderr, ">");
			fgets(in_text, sizeof(in_text) - 1, stdin);
			while (*in_text && (in_text[strlen(in_text) - 1] == '\n'))
				in_text[strlen(in_text) - 1] = '\0';
		} while ((!(*in_text)) && (!feof(stdin)) && (!ferror(stdin)));
		trim(strcpy(tmp_in_text, in_text));
		if ((!stricmp(tmp_in_text, "QUIT")) ||
			(!stricmp(tmp_in_text, "EXIT")) || feof(stdin) || ferror(stdin))
			break;
		STR_EMIT_CharLine('=', 78, NULL, stderr);
		printf("[%s]\n", in_text);
		STR_EMIT_CharLine('-', 78, NULL, stderr);
		if ((return_code = EEC_ParseIt(&control_data, strlen(in_text), in_text,
			NULL, &postfix_data, &parse_index, error_text)) == EEC_SUCCESS) {
			EEC_EMIT_PostFix(&postfix_data, NULL, NULL);
			STR_EMIT_CharLine('-', 78, NULL, stderr);
			if ((return_code = EEC_GetInfixFormula(&postfix_data, EEC_FALSE,
				&infix_ptr, error_text)) == EEC_SUCCESS) {
				printf("[%s]\n", infix_ptr);
				free(infix_ptr);
				if ((return_code = EEC_GetInfixFormula(&postfix_data, EEC_TRUE,
					&infix_ptr, error_text)) == EEC_SUCCESS) {
					printf("[%s]\n", infix_ptr);
					free(infix_ptr);
				}
			}
			if (return_code != EEC_SUCCESS)
				fprintf(stderr, "INFIX ERROR: %s\n", error_text);
			EEC_FREE_PostFixPtr(&postfix_data);
		}
		else {
			for (count_1 = 0; count_1 < strlen(in_text); count_1++)
				tmp_in_text[count_1] = ((char)
					((strchr("\n\r\f\t\b", in_text[count_1]) == NULL) ? ' ' :
					in_text[count_1]));
			tmp_in_text[parse_index]     = '^';
			tmp_in_text[parse_index + 1] = '\0';
			fprintf(stderr, "[%s]\n", tmp_in_text);
			STR_EMIT_CharLine('-', 78, NULL, stderr);
			fprintf(stderr, "PARSE ERROR: %s\n", error_text);
		}
		STR_EMIT_CharLine('=', 78, NULL, stderr);
	}

	EEC_FREE_Control(&control_data);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

