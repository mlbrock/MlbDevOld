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

		Copyright Michael L. Brock 1989 - 2016.
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

	NAME			:	strrepl

 	SYNOPSIS		:	string_ptr = strrepl(base_string, insert_string, position,
							delete_length);

						char         *string_ptr;

						char         *base_string;

  						const char   *insert_string;

  						unsigned int  position;

						unsigned int  delete_length;

	DESCRIPTION	:	Replaces a portion of a string with another string.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``base_string`` is the string for which the replacement
						is to be made.

  						(.) ``insert_string`` is the string to be inserted.

  						(.) ``position`` is the index at which the replacement is to
						be made.

						(.) ``delete_length`` is the number of characters to be
						deleted from ``base_string``.

	RETURNS		:	The parameter ``base_string``.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	strnrepl
						strdele
						strinst

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

   COPYRIGHT   :  Copyright 1989 - 2016 Michael L. Brock

	OUTPUT INDEX:	strrepl
						String Cut And Paste Functions:strrepl
						STRFUNCS:String Cut And Paste Functions:strrepl
						String Functions:See STRFUNCS

	PUBLISH XREF:	strrepl

	PUBLISH NAME:	strrepl

	ENTRY CLASS	:	String Cut And Paste Functions

EOH */
/* **************************************************************************	*/
#ifndef NARGS
char *strrepl(char *base_string, const char *insert_string,
	unsigned int position, unsigned int delete_length)
#else
char *strrepl(base_string, insert_string, position, delete_length)
char         *base_string;
const char   *insert_string;
unsigned int  position;
unsigned int  delete_length;
#endif /* #ifndef NARGS */
{
	return(strinst(strdele(base_string, position, delete_length),
		insert_string, position));
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
/* **************************************************************************	*/
/* **************************************************************************	*/
int main()
{
	unsigned int count_1;
	unsigned int count_2;
	int          count_3;
	int          count_4;
	char         base_area[512 + 1];

	fprintf(stderr, "Test of function 'strrepl()'\n");
	fprintf(stderr, "---- -- -------- -----------\n\n");

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
					strcpy(base_area, BaseList[count_1]);
					printf("[BASE:%s|%02u][INSERT:%s|%02u][POSITION:%02u]",
						base_area, strlen(base_area), InsertList[count_2],
						strlen(InsertList[count_2]), count_3);
					printf("[DELETE:%02u]", count_4);
					strrepl(base_area, InsertList[count_2], count_3, count_4);
					printf(" --- [NEW:%s|%02u]\n", base_area, strlen(base_area));
				}
			}
		}
	}

	return(0);
}
/* **************************************************************************	*/

#endif /* TEST_MAIN */

