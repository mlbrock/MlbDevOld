/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	STRFUNCS String and Memory Functions Library Module							*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Determines which components of a string are a number.

	Revision History	:	1990-03-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1990 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*    Include necessary header files . . .                                 */
/*	***********************************************************************	*/

#include <string.h>

#include "strfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int STR_IsSIntString(const char *string_ptr)
#else
int STR_IsSIntString(string_ptr)
const char *string_ptr;
#endif /* #ifndef NARGS */
{
	return(STR_IsNumberStringBasic(string_ptr, strlen(string_ptr),
		STR_IS_NUMBER_FLAG_NEGATIVE, NULL));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int STR_IsUIntString(const char *string_ptr)
#else
int STR_IsUIntString(string_ptr)
const char *string_ptr;
#endif /* #ifndef NARGS */
{
	return(STR_IsNumberStringBasic(string_ptr, strlen(string_ptr),
		STR_IS_NUMBER_FLAG_NONE, NULL));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int STR_IsFloatString(const char *string_ptr, const char *decimal_point)
#else
int STR_IsFloatString(string_ptr, decimal_point)
const char *string_ptr;
const char *decimal_point;
#endif /* #ifndef NARGS */
{
	return(STR_IsNumberStringBasic(string_ptr, strlen(string_ptr),
		STR_IS_NUMBER_FLAG_ALL, decimal_point));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int STR_IsNumberString(const char *string_ptr, unsigned int flags,
	const char *decimal_point)
#else
int STR_IsNumberString(string_ptr, flags, decimal_point)
const char   *string_ptr;
unsigned int  flags;
const char   *decimal_point;
#endif /* #ifndef NARGS */
{
	return(STR_IsNumberStringBasic(string_ptr, strlen(string_ptr), flags,
		decimal_point));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int STR_IsNumberStringBasic(const char *string_ptr, unsigned int string_length,
	unsigned int flags, const char *decimal_point)
#else
int STR_IsNumberStringBasic(string_ptr, string_length, flags, decimal_point)
const char   *string_ptr;
unsigned int  string_length;
unsigned int  flags;
const char   *decimal_point;
#endif /* #ifndef NARGS */
{
	int          return_flag = STRFUNCS_FALSE;
	unsigned int new_end_index;

	if (string_length) {
		while (string_length && isspace(*string_ptr)) {
			string_ptr++;
			string_length--;
		}
		if (string_length) {
			if ((return_flag = STR_DetermineNumberString(string_ptr, flags,
				decimal_point, 0, string_length - 1, &new_end_index)) ==
				STRFUNCS_TRUE) {
				string_ptr    += new_end_index + 1;
				string_length -= new_end_index + 1;
				while (string_length) {
					if (!isspace(*string_ptr)) {
						return_flag = STRFUNCS_FALSE;
						break;
					}
					string_ptr++;
					string_length--;
				}
			}
		}
	}

	return(return_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int STR_DetermineNumberString(const char *string_ptr, unsigned int flags,
	const char *decimal_point, unsigned int start_index, unsigned int end_index,
	unsigned int *new_end_index)
#else
int STR_DetermineNumberString(string_ptr, flags, decimal_point, start_index,
	end_index, new_end_index)
const char   *string_ptr;
unsigned int  flags;
const char   *decimal_point;
unsigned int  start_index;
unsigned int  end_index;
unsigned int *new_end_index;
#endif /* #ifndef NARGS */
{
	int           return_flag = STRFUNCS_FALSE;
	const char   *current_ptr = string_ptr + start_index;
	unsigned int  tmp_end_index;

	if (end_index < start_index) {
		*new_end_index = start_index + 1;
		goto EXIT_FUNCTION;
	}

	decimal_point  = (decimal_point != NULL) ? decimal_point : ".";
	new_end_index  = (new_end_index != NULL) ? new_end_index : &tmp_end_index;
	*new_end_index = start_index;

	if ((*current_ptr == '+') ||
		((*current_ptr == '-') && (flags & STR_IS_NUMBER_FLAG_NEGATIVE))) {
		(*new_end_index)++;
		current_ptr++;
		if (*new_end_index > end_index)
			goto EXIT_FUNCTION;
	}
	else if (*current_ptr == '-')
		goto EXIT_FUNCTION;

	while (*new_end_index <= end_index) {
		if (!isdigit(*current_ptr))
			break;
		return_flag = STRFUNCS_TRUE;
		(*new_end_index)++;
		current_ptr++;
	}
	if (*new_end_index > end_index)
		goto EXIT_FUNCTION;

	if ((*current_ptr == *decimal_point) &&
		(flags & STR_IS_NUMBER_FLAG_FLOATING)) {
		if (++(*new_end_index) > end_index)
			goto EXIT_FUNCTION;
		current_ptr++;
	}
	else
		goto EXIT_FUNCTION;

	while (*new_end_index <= end_index) {
		if (!isdigit(*current_ptr))
			break;
		return_flag = STRFUNCS_TRUE;
		(*new_end_index)++;
		current_ptr++;
	}
	if ((*new_end_index > end_index) || (return_flag != STRFUNCS_TRUE))
		goto EXIT_FUNCTION;

	if ((flags & STR_IS_NUMBER_FLAG_SCIENTIFIC) &&
		((*new_end_index + 2) <= end_index) &&
		((*current_ptr == 'e') || (*current_ptr == 'E')) &&
		((current_ptr[1] == '+') || (current_ptr[1] == '-')) &&
		isdigit(current_ptr[2])) {
		*new_end_index += 3;
		current_ptr    += 3;
		while (*new_end_index <= end_index) {
			if (!isdigit(*current_ptr))
				break;
			(*new_end_index)++;
			current_ptr++;
		}
	}

EXIT_FUNCTION:

	(*new_end_index)--;

	return(return_flag);
}
/*	***********************************************************************	*/


#ifdef TEST_MAIN

#include <stdio.h>

typedef struct {
	char         *string_ptr;
	unsigned int  flags;
} TEST_DATA;

const TEST_DATA    TEST_StringList[] = {
	{	"+1234.5678",	STR_IS_NUMBER_FLAG_ALL			},
	{	"-1234",			STR_IS_NUMBER_FLAG_NEGATIVE	},
	{	"1234",			STR_IS_NUMBER_FLAG_NONE			},
	{	"123.456e+2",	STR_IS_NUMBER_FLAG_ALL			}
};
const unsigned int TEST_StringCount  =
	sizeof(TEST_StringList) / sizeof(TEST_StringList[0]);

COMPAT_FN_DECL(int        main, (int argc, char **argv));
COMPAT_FN_DECL_STATIC(int TEST_DoTest, (unsigned int count,
	const char *string_ptr, unsigned int flags));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int           return_code = STRFUNCS_SUCCESS;
	unsigned int  in_count    = 0;
	unsigned int  count_1;
	char         *fgets_return;
	char          buffer[512];

	fprintf(stderr, "Test harness for 'STR_IsSIntString()'\n");
	fprintf(stderr, "                 'STR_IsUIntString()'\n");
	fprintf(stderr, "                 'STR_IsFloatString()'\n");
	fprintf(stderr, "                 'STR_IsNumberString()'\n");
	fprintf(stderr, "                 'STR_IsNumberStringBasic()'\n");
	fprintf(stderr, "                 'STR_DetermineNumberString()'\n");
	fprintf(stderr, "---- ------- --- -----------------------------\n\n");

	if (argc > 1) {
		for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
			if ((!stricmp(argv[count_1], "-H")) ||
				(!stricmp(argv[count_1], "-HELP"))) {
				fprintf(stderr, "USAGE:\n%s\n%s\n",
					"   A command line argument of -h or -help gets this help",
					"   Any other command line argument lets you enter test data");
				goto EXIT_FUNCTION;
			}
		}
		while ((!feof(stdin)) && (!ferror(stdin))) {
			*buffer      = '\0';
			fgets_return = buffer;
			while (fgets_return && (!(*buffer))) {
				fgets_return = fgets(buffer, sizeof(buffer) - 1, stdin);
				while (strlen(buffer) && (buffer[strlen(buffer) - 1] == '\n'))
					buffer[strlen(buffer) - 1] = '\0';
			}
			if ((!fgets_return) || (!strnicmp(buffer, "END", 3))) {
				fprintf(stderr, "ENDING PROCESS: %s\n", (!fgets_return) ?
					"END-FILE-ENCOUNTERED" : "END IN INPUT ENCOUNTERED");
				break;
			}
			TEST_DoTest(in_count++, buffer, STR_IS_NUMBER_FLAG_ALL);
		}
	}
	else {
		for (count_1 = 0; count_1 < TEST_StringCount; count_1++) {
			TEST_DoTest(count_1, TEST_StringList[count_1].string_ptr,
				TEST_StringList[count_1].flags);
		}
	}

EXIT_FUNCTION:

	return(return_code);
}

#ifndef NARGS
static int TEST_DoTest(unsigned int count, const char *string_ptr,
	unsigned int flags)
#else
static int TEST_DoTest(count, string_ptr, flags)
unsigned int  count;
const char   *string_ptr;
unsigned int  flags;
#endif /* #ifndef NARGS */
{
	int return_flag;

	printf("%10u:[%s] = %s\n",
		count,
		string_ptr,
		((return_flag = STR_IsNumberString(string_ptr, flags, NULL)) ==
		STRFUNCS_TRUE) ? "TRUE" : "FALSE");

	return(return_flag);
}

#endif /* #ifdef TEST_MAIN */


