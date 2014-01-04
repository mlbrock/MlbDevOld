/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	Revision History:
		10/27/1986 --- Creation by Michael L. Brock

		Copyright Michael L. Brock 1986 - 2014.
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
#include <stdlib.h>

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* *********************************************************************** */
#ifndef NARGS
int strlwrap(const char *in_string, int *current_col, int max_length,
	int *tab_count, int tab_setting, int strip_flag, char *last_char,
	unsigned int *string_count, char ***string_list)
#else
int strlwrap(in_string, current_col, max_length, tab_count, tab_setting,
	strip_flag, last_char, string_count, string_list)
const char      *in_string;
int             *current_col;
int              max_length;
int             *tab_count;
int              tab_setting;
int              strip_flag;
char            *last_char;
unsigned int    *string_count;
char         ***string_list;
#endif /* #ifndef NARGS */
{
	int   return_code = 0;
	char *tmp_buffer  = NULL;

	*string_count = 0;
	*string_list  = NULL;

	if ((*current_col < 0) || (max_length < 1) ||
		((!tab_setting) && (max_length < 2)) || (*tab_count < 0) ||
		(*current_col >= max_length) || (!in_string))
		return_code = -1;
	else if (!(*in_string))
		return_code = strl_append(string_count, string_list, "");
	else if ((tmp_buffer =
		((char *) malloc((max_length + 1) * sizeof(char)))) == NULL)
		return_code = -1;
	else {
		while ((in_string = strwrap(in_string, current_col, max_length,
			tab_count, tab_setting, strip_flag, last_char, tmp_buffer)) !=
			NULL) {
			if ((return_code = strlapp(string_count, string_list,
				tmp_buffer)) != 0)
				break;
		}
	}

	if (tmp_buffer)
		free(tmp_buffer);

	if (return_code)
		strldel(string_count, string_list, 0, *string_count);

	return(return_code);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

/* *********************************************************************** */
/* *********************************************************************** */
/* *********************************************************************** */

COMPAT_FN_DECL(int main, (void));

char *TestList[] = {

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

int main()
{
	int            count_1;
	int            count_2;
	int            count_3;
	int            current_col;
	int            tab_count;
	char           last_char;
	unsigned int   string_count = 0;
	char         **string_list  = NULL;
	char           buffer[1024 + 1];

	printf("TEST_MAIN for function strlwrap()\n");
	printf("--------- --- -------- ----------\n");

	for (count_1 = 0; count_1 < 2; count_1++) {
		printf(">>> ******** STRIP FLAG %s******* <<<\n",
			(!count_1) ? "OFF *" : "ON **");
		printf("%s\n", nstrset(buffer, '=', 40));
		for (count_2 = 0; count_2 < (sizeof(TestList) / sizeof(TestList[0]));
			count_2++) {
			current_col = 0;
			tab_count   = 0;
			if (strlwrap(TestList[count_2], &current_col, 40, &tab_count, 8,
				count_1, &last_char, &string_count, &string_list)) {
				fprintf(stderr,
					"ERROR ON 'strwrap()' attempt:\n>>> '%.20s'.\n",
					TestList[count_2]);
				break;
			}
			else {
				printf("%s\n", nstrset(buffer, '-', 40));
				for (count_3 = 0; count_3 < ((int) string_count); count_3++)
					printf("%s\n", string_list[count_3]);
				printf("%s\n", nstrset(buffer, '-', 40));
				strldel(&string_count, &string_list, 0, string_count);
			}
		}
	}

	return(0);
}
/* *********************************************************************** */

#endif /* #ifdef TEST_MAIN */

