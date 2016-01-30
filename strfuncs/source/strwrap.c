/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	Revision History:
		10/27/1986 --- Creation by Michael L. Brock

		Copyright Michael L. Brock 1986 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Necessary include files . . .														*/
/* *********************************************************************** */

#include <stdio.h>

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* *********************************************************************** */
#ifndef NARGS
const char *strwrap(const char *in_string, int *current_col, int max_length,
	int *tab_count, int tab_setting, int strip_flag, char *last_char,
	char *out_string)
#else
const char *strwrap(in_string, current_col, max_length, tab_count,
	tab_setting, strip_flag, last_char, out_string)
const char *in_string;
int        *current_col;
int         max_length;
int        *tab_count;
int         tab_setting;
int         strip_flag;
char       *last_char;
char       *out_string;
#endif /* #ifndef NARGS */
{
	int         break_col     = -1;
	const char *break_ptr_in  = NULL;
	const char *break_ptr_out = NULL;
	int         tab_type_indicator;
	char        break_char;
	char       *out_string_start = out_string;

	tab_type_indicator = tab_setting;
	tab_setting        = (tab_setting >= 0) ? tab_setting : (0 - tab_setting);

	if ((*current_col < 0) || (max_length < 1) ||
		((!tab_setting) && (max_length < 2)) || (*tab_count < 0) ||
		(*current_col >= max_length) || (!in_string) || (!(*in_string)))
		return(NULL);

	*out_string = '\0';

	if (*tab_count) {
		if (!tab_type_indicator) {
			*out_string++  = '\\';
			*out_string++  = 't';
			*current_col  += 2;
		}
		else if (tab_type_indicator < 0) {
			if (*tab_count >= max_length) {
				*tab_count -= max_length;
				goto EXIT_FUNCTION;
			}
			*current_col += *tab_count;
		}
		else {
			break_ptr_in  = in_string;
			break_char    = ' ';
			while (*tab_count) {
				if (*current_col == max_length) {
					*current_col = 0;
					*tab_count   = (strip_flag) ? 0 : *tab_count;
					*last_char   = ' ';
					goto EXIT_FUNCTION;
				}
				(*tab_count)--;
				break_ptr_out = out_string;
				break_col     = (*current_col)++;
				*out_string++ = ' ';
			}
		}
		*tab_count = 0;
	}

	while (*in_string) {
		*last_char = *in_string;
		switch (*in_string) {
			case	'\n'	:
			case	'\r'	:
			case	'\f'	:
			case	'\v'	:
				*current_col = 0;
				in_string++;
				goto EXIT_FUNCTION;
			case	' '	:						/* These are 'natural' break chars	*/
			case	'\t'	:
				if (*current_col == max_length) {
					*current_col = 0;
					goto EXIT_FUNCTION;
				}
				if (*in_string == '\t') {
					in_string++;
					if (!tab_type_indicator) {
						if (*current_col >= (max_length - 2)) {
							*tab_count   = 1;
							*current_col = 0;
							*last_char   = '\t';
							goto EXIT_FUNCTION;
						}
						*out_string++  = '\\';
						*out_string++  = 't';
						*current_col  += 2;
					}
					else if (tab_type_indicator < 0) {
						*out_string++ = '\t';
						*tab_count    = tab_setting - (*current_col % tab_setting);
						if (*tab_count >= (max_length - *current_col)) {
							*tab_count   -= max_length - *current_col;
							*current_col  = 0;
							*last_char    = '\t';
							goto EXIT_FUNCTION;
						}
						*current_col += *tab_count;
					}
					else {
						*tab_count    = tab_setting - (*current_col % tab_setting);
						(*current_col)++;
						break_ptr_in  = in_string;
						break_col     = *current_col;
						break_char    = ' ';
						*out_string++ = ' ';
						break_ptr_out = out_string;
						(*tab_count)--;
						while (*tab_count) {
							if (*current_col == max_length) {
								*current_col = 0;
								*tab_count   = (strip_flag) ? 0 : *tab_count;
								*last_char   = '\t';
								goto EXIT_FUNCTION;
							}
							(*tab_count)--;
							break_ptr_out = out_string;
							break_col     = (*current_col)++;
							*out_string++ = ' ';
						}
					}
					*tab_count = 0;
				}
				else {
					break_ptr_in  = in_string;
					break_ptr_out = out_string;
					break_char    = *in_string;
					break_col     = *current_col;
					*out_string++ = *in_string++;
					(*current_col)++;
				}
				break;
			case	','	:						/* More 'natural' break chars			*/
			case	';'	:
			case	':'	:
			case	'.'	:
			case	'!'	:
			case	'?'	:
			case	'-'	:
				if (*current_col == (max_length - 1)) {
					*out_string++ = *in_string++;
					*current_col  = 0;
					goto EXIT_FUNCTION;
				}
				else if (*current_col == max_length) {
					if (break_col > -1) {
						in_string     = break_ptr_in;
						out_string    = ((char *) break_ptr_out);
						*current_col  = break_col;
						*last_char    = *in_string;
						*out_string++ = *in_string++;
						(*current_col)++;
					}
					*current_col = 0;
					goto EXIT_FUNCTION;
				}
				break_ptr_in  = in_string;
				break_ptr_out = out_string;
				break_char    = *in_string;
				break_col     = *current_col;
				*out_string++ = *in_string++;
				(*current_col)++;
				break;
			default		:						/* All other chars handled here		*/
				if (*current_col < max_length) {
					*out_string++ = *in_string++;
					(*current_col)++;
				}
				else {
					if (break_col > -1) {
						in_string     = break_ptr_in;
						out_string    = ((char *) break_ptr_out);
						*current_col  = break_col;
						*last_char    = *in_string;
						*out_string++ = *in_string++;
						(*current_col)++;
					}
					*current_col = 0;
					goto EXIT_FUNCTION;
				}
		}
	}

EXIT_FUNCTION:

	*out_string = '\0';

	if (strip_flag) {
		rtrim(out_string_start);
		while ((*in_string == ' ') || (*in_string == '\t'))
			in_string++;
	}

	return(in_string);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

/* *********************************************************************** */
/* *********************************************************************** */
/* *********************************************************************** */


COMPAT_FN_DECL(int  main, (void));

COMPAT_FN_DECL_STATIC(void RunTest, (char *, int, char **, int));

/*
"         1         2         3         4"
"1234567890123456789012345678901234567890"
*/
char *Test_1[] = {
"This is a test of the strwrap() function\
 --- the last line ends exactly on the\
 boundary specified for wrapping.",

"This is a test, which requires that non-\
space character wrapping be performed.  \
(The first line is on the boundary).",

"This test checks multiple break chars---\
(The first line is on the boundary).",

"This test checks multiple break chars----\
(The first line is on the boundary).",

"This test checks multiple break chars-----\
(The first line is on the boundary).",

"This test checks multiple break chars --\
(The first line is on the boundary).",
};

char *Test_2[] = {

"You are in a narrow and dark alley which continues\
 north and south. Water drips slowly from the walls, forming shallow pools\
 on the floor. The walls of the alley are formed of rough-hewn stone.",

"You are in a darkened chute with exits leading north,\
 east, west, and south. A rather grimy-looking staircase leads up.",

"You are at the side of a shallow streambed. The\
 stream leads north through a hole too small to enter. The east bend,\
 however, enters a hole that looks large enough for you to enter.",

"You are following a shallow stream. The stream\
 continues west and bends to the north. From the north comes a loud noise,\
 as of water flowing.",

"There is a large waterfall here which makes so much\
 noise you can hardly hear yourself think. Exits are to the north, south,\
 east, and west.",

"There is an ancient stone bridge covered with ornate\
 and primitive markings. The bridge continues both north and south.",

"You are in the tastefully decorated living room\
 somewhere on the seventh floor of the Cairo. Paintings by old masters\
 grace all the walls but the southern one which is exposed brick, through\
 which a breathtaking view of the city is visible. Leather-covered Italian\
 furniture (probably from Roche-Bubios) is scattered throughout the\
 apartment."
};

/*
"         1         2         3         4"
"1234567890123456789012345678901234567890"
*/
char *Test_3[] = {

"You are in a narrow and dark alley\n\
which continues north and south. \n\
Water drips slowly from the walls,\
 forming shallow pools on the floor. The walls of the alley\
 are formed of rough-hewn stone.",

"You are in a darkened\f\
chute with exits leading north,\v\
east, west, and south. A rather\r\
grimy-looking staircase leads up."
};

char *TabTest_1[] = {
"This is a test of\tthe strwrap() function\
\t\t --- the last line ends exactly on the\
 boundary specified for wrapping.",

"This is a test,\twhich requires that non-\
space character wrapping be performed.  \
(The first line is on the boundary).",

"This test checks\tmultiple break chars---\
(The first line is on the boundary).",

"This test checks\tmultiple break chars----\
(The first line is on the boundary).",

"This test checks\tmultiple break chars-----\
(The first line is on the boundary).",

"This test checks\tmultiple break chars --\
(The first line is on the boundary).",

"This test checks trailing tab characters\t\
(The first line is on the boundary).",
};

char *TabTest_2[] = {

"You are in a narrow and dark alley\n\
which continues north and south. \n\
Water drips slowly from the walls,\
 forming shallow pools on the floor. The walls of the alley\
 are formed of rough-hewn stone.",

"You are in a darkened\f\
chute with exits leading north,\v\
east, west, and south. A rather\r\
grimy-looking staircase leads up."
};

int main()
{
	printf("TEST_MAIN for function strwrap()\n");
	printf("--------- --- -------- ---------\n");

	RunTest("TabTest_1", sizeof(TabTest_1) / sizeof(TabTest_1[0]),
		TabTest_1, 8);
	RunTest("TabTest_1", sizeof(TabTest_1) / sizeof(TabTest_1[0]),
		TabTest_1, -8);

	RunTest("Test_1", sizeof(Test_1) / sizeof(Test_1[0]), Test_1, 1);
	RunTest("Test_2", sizeof(Test_2) / sizeof(Test_2[0]), Test_2, 1);
	RunTest("Test_3", sizeof(Test_3) / sizeof(Test_3[0]), Test_3, 1);

	RunTest("TabTest_1", sizeof(TabTest_1) / sizeof(TabTest_1[0]),
		TabTest_1, 1);
	RunTest("TabTest_1", sizeof(TabTest_1) / sizeof(TabTest_1[0]),
		TabTest_1, 3);
	RunTest("TabTest_1", sizeof(TabTest_1) / sizeof(TabTest_1[0]),
		TabTest_1, 8);

	RunTest("TabTest_1", sizeof(TabTest_1) / sizeof(TabTest_1[0]),
		TabTest_1, -1);
	RunTest("TabTest_1", sizeof(TabTest_1) / sizeof(TabTest_1[0]),
		TabTest_1, -3);
	RunTest("TabTest_1", sizeof(TabTest_1) / sizeof(TabTest_1[0]),
		TabTest_1, -8);

	RunTest("TabTest_1", sizeof(TabTest_1) / sizeof(TabTest_1[0]),
		TabTest_1, 0);

	RunTest("TabTest_2", sizeof(TabTest_2) / sizeof(TabTest_2[0]),
		TabTest_2, 1);
	RunTest("TabTest_2", sizeof(TabTest_2) / sizeof(TabTest_2[0]),
		TabTest_2, 3);
	RunTest("TabTest_2", sizeof(TabTest_2) / sizeof(TabTest_2[0]),
		TabTest_2, 8);

	RunTest("TabTest_2", sizeof(TabTest_2) / sizeof(TabTest_2[0]),
		TabTest_2, -1);
	RunTest("TabTest_2", sizeof(TabTest_2) / sizeof(TabTest_2[0]),
		TabTest_2, -3);
	RunTest("TabTest_2", sizeof(TabTest_2) / sizeof(TabTest_2[0]),
		TabTest_2, -8);

	RunTest("TabTest_2", sizeof(TabTest_2) / sizeof(TabTest_2[0]),
		TabTest_2, 0);

	return(0);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* *********************************************************************** */
#ifndef NARGS
void RunTest(char *test_name, int string_count, char **string_list,
	int tab_setting)
#else
void RunTest(test_name, string_count, string_list, tab_setting)
char  *test_name;
int    string_count;
char **string_list;
int    tab_setting;
#endif /* #ifndef NARGS */
{
	int   count_1;
	int   count_2;
	int         current_col;
	int         tab_count;
	char        last_char;
	const char *current_ptr;
	char        buffer[1024 + 1];

	printf("TEST NAME: %s FOR TAB SETTING %d\n", test_name, tab_setting);
	printf("1234567890123456789012345678901234567890\n");
	
	for (count_1 = 0; count_1 < 2; count_1++) {
		printf(">>> ******** STRIP FLAG %s******* <<<\n",
			(!count_1) ? "OFF *" : "ON **");
		printf("%s\n", nstrset(buffer, '=', 40));
		for (count_2 = 0; count_2 < string_count; count_2++) {
			printf("%s\n", nstrset(buffer, '-', 40));
			current_ptr = string_list[count_2];
			current_col = 0;
			tab_count   = 0;
			while ((current_ptr = strwrap(current_ptr, &current_col, 40,
				&tab_count, tab_setting, count_1, &last_char, buffer)) != NULL)
				printf("%s   [LAST CHAR = '%c' (ASCII %u)]\n",
					buffer, (isprint(last_char)) ? last_char : ' ', last_char);
			printf("%s\n", nstrset(buffer, '-', 40));
		}
	}
	printf("1234567890123456789012345678901234567890\n");
	printf("****************************************\n");
}
/* *********************************************************************** */

#endif /* #ifdef TEST_MAIN */

