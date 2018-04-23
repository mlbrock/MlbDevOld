/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Inserts characters into a string.

	Revision History	:	1989-07-07 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1989 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Include necessary header files . . .											*/
/* *********************************************************************** */

#include <memory.h>
#include <string.h>

#include "strfunci.h"

/* **************************************************************************	*/

/* **************************************************************************	*/
/* **************************************************************************	*/
/* BOH

	NAME			:	strinst

	SYNOPSIS		:	string_ptr = strinst(base_string, insert_string, position);

						char         *string_ptr;

						char         *base_string;

  						const char   *insert_string;

  						unsigned int  position;

	DESCRIPTION	:	Inserts the string to which the ``insert_string`` parameter
						points into the the string to which the ``base_string``
						parameter points at the position specified by the
						``position`` parameter.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``base_string`` is the string into which the insertion
						is to be made.

  						(.) ``insert_string`` is the string to be inserted.

  						(.) ``position`` is the index at which the insertion is to
						be made.

	RETURNS		:	The parameter ``base_string`` --- that is, the text
						resulting from insertion ``insert_string`` into
						``base_string``.

	NOTES			:	If the ``position`` parameter is zero, ``insert_string``
						is inserted in front of ``base_string``.

						If the ``position`` parameter is greater than the length of
						``base_string``, ``insert_string`` is appended to
						``base_string``.

						If ``base_string`` is of zero length, ``insert_string`` is
						copied to ``base_string``.

	CAVEATS		:	

	SEE ALSO		:	strninst

	AUTHOR		:	Michael L. Brock

   COPYRIGHT   :  Copyright 1989 - 2018 Michael L. Brock

	OUTPUT INDEX:	strinst
						String Cut And Paste Functions:strinst
						STRFUNCS:String Cut And Paste Functions:strinst
						String Functions:See STRFUNCS

	PUBLISH XREF:	strinst

	PUBLISH NAME:	strinst

	ENTRY CLASS	:	String Cut And Paste Functions

EOH */
/* **************************************************************************	*/
#ifndef NARGS
char *strinst(char *base_string, const char *insert_string,
	unsigned int position)
#else
char *strinst(base_string, insert_string, position)
char         *base_string;
const char   *insert_string;
unsigned int  position;
#endif /* #ifndef NARGS */
{
	unsigned int base_length;
	unsigned int insert_length;
	char         *insert_ptr;
	char         *tmp_ptr_1;
	char         *tmp_ptr_2;

	if ((insert_length = strlen(insert_string)) > 0) {
		if ((base_length = strlen(base_string)) == 0)
			strcpy(base_string, insert_string);
		else {
			if (position >= base_length)
				strcat(base_string, insert_string);
			else {
				insert_ptr = base_string + position;
				for (tmp_ptr_1 = base_string + base_length,
					tmp_ptr_2 = tmp_ptr_1 + insert_length; 
					tmp_ptr_2 >= insert_ptr; tmp_ptr_1--, tmp_ptr_2--)
					*tmp_ptr_2 = *tmp_ptr_1;
				memcpy(base_string + position, insert_string, insert_length);
			}
		}
	}

	return(base_string);
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
	char         base_area[512 + 1];

	fprintf(stderr, "Test of function 'strinst()'\n");
	fprintf(stderr, "---- -- -------- -----------\n\n");

	for (count_1 = 0; count_1 < (sizeof(BaseList) / sizeof(BaseList[0]));
		count_1++) {
		for (count_2 = 0; count_2 < (sizeof(InsertList) / sizeof(InsertList[0]));
			count_2++) {
			for (count_3 = -1;
				count_3 <= ((int) (strlen(BaseList[count_1]) + 1));
				count_3++) {
				strcpy(base_area, BaseList[count_1]);
				printf("[BASE:%s|%02u][INSERT:%s|%02u][POSITION:%02d]",
					base_area, strlen(base_area), InsertList[count_2],
					strlen(InsertList[count_2]), count_3);
				strinst(base_area, InsertList[count_2], count_3);
				printf(" --- [NEW:%s|%02u]\n", base_area, strlen(base_area));
			}
		}
	}

	return(0);
}
/* **************************************************************************	*/

#endif /* TEST_MAIN */

