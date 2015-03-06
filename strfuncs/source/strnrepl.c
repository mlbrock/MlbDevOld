/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Replaces characters in a string.

	Revision History	:	1989-07-07 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1989 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Include necessary header files . . .											*/
/* *********************************************************************** */

#include <string.h>

#include "strfunci.h"

/* **************************************************************************	*/

/* **************************************************************************	*/
/* **************************************************************************	*/
/* BOH

	NAME			:	strnrepl

 	SYNOPSIS		:	string_ptr = strnrepl(base_string, insert_string, position,
							delete_length, insert_length);

						char         *string_ptr;

						char         *base_string;

  						const char   *insert_string;

  						unsigned int  position;

						unsigned int  delete_length;

						unsigned int  insert_length;

	DESCRIPTION	:	Replaces a portion of a string with part of another string.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``base_string`` is the string for which the replacement
						is to be made.

  						(.) ``insert_string`` is the string to be inserted.

  						(.) ``position`` is the index at which the replacement is to
						be made.

						(.) ``delete_length`` is the number of characters to be
						deleted from ``base_string``.

						(.) ``insert_length`` is the maximum number of characters to
						be used from ``insert_string`` in performing the insertion.

	RETURNS		:	The parameter ``base_string``.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	strrepl
						strdele
						strninst

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

   COPYRIGHT   :  Copyright 1989 - 2015 Michael L. Brock

	OUTPUT INDEX:	strnrepl
						String Cut And Paste Functions:strnrepl
						STRFUNCS:String Cut And Paste Functions:strnrepl
						String Functions:See STRFUNCS

	PUBLISH XREF:	strnrepl

	PUBLISH NAME:	strnrepl

	ENTRY CLASS	:	String Cut And Paste Functions

EOH */
/* **************************************************************************	*/
#ifndef NARGS
char *strnrepl(char *base_string, const char *insert_string,
	unsigned int position, unsigned int delete_length,
	unsigned int insert_length)
#else
char *strnrepl(base_string, insert_string, position, delete_length,
	insert_length)
char         *base_string;
const char   *insert_string;
unsigned int  position;
unsigned int  delete_length;
unsigned int  insert_length;
#endif /* #ifndef NARGS */
{
	return(strninst(strdele(base_string, position, delete_length),
		insert_string, position, insert_length));
}
/* **************************************************************************	*/

#ifdef TEST_MAIN

#include <stdio.h>

COMPAT_FN_DECL(int main, (void));

char *BaseList[] = {
	"This is a test",
	""
};

char *InsertList[] = {
	"INSERT-STRING",
	""
};

/* **************************************************************************	*/
int main()
{
	unsigned int count_1;
	unsigned int count_2;
	int          count_3;
	int          count_4;
	int          count_5;
	char         base_area[512 + 1];

	fprintf(stderr, "Test of function 'strnrepl()'\n");
	fprintf(stderr, "---- -- -------- ------------\n\n");

	for (count_1 = 0; count_1 < (sizeof(BaseList) / sizeof(BaseList[0]));
		count_1++) {
		for (count_2 = 0; count_2 < (sizeof(InsertList) / sizeof(InsertList[0]));
			count_2++) {
			for (count_3 = -1;
				count_3 <= ((int) (strlen(BaseList[count_1]) + 1));
				count_3++) {
				for (count_4 = -1;
					count_4 <= ((int) (strlen(BaseList[count_1]) + 1));
					count_4++) {
					for (count_5 = -1;
						count_5 <= ((int) (strlen(InsertList[count_2]) + 1));
						count_5++) {
						strcpy(base_area, BaseList[count_1]);
					 	printf("[BASE:%s|%02u][INSERT:%s|%02u][POSITION:%02u]",
							base_area, strlen(base_area), InsertList[count_2],
							strlen(InsertList[count_2]), count_3);
						printf("[DELETE:%02u][INSERT:%02u]", count_4, count_5);
						strnrepl(base_area, InsertList[count_2], count_3, count_4,
							count_5);
						printf(" --- [NEW:%s|%02u]\n", base_area, strlen(base_area));
					}
				}
			}
		}
	}

	return(0);
}
/* **************************************************************************	*/

#endif /* TEST_MAIN */

