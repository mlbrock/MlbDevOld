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

#include <memory.h>
#include <string.h>

#include "strfunci.h"

/* **************************************************************************	*/

/* **************************************************************************	*/
/* **************************************************************************	*/
/* BOH

	NAME			:	strninst

	SYNOPSIS		:	string_ptr = strninst(base_string, insert_string, position,
							length);

						char         *string_ptr;

						char         *base_string;

  						const char   *insert_string;

  						unsigned int  position;

						unsigned int  length;

	DESCRIPTION	:	Inserts the string to which the ``insert_string`` parameter
						points into the the string to which the ``base_string``
						parameter points at the position specified by the
						``position`` parameter.  No more than the number of
						characters specified by the parameter ``length`` are
						inserted from ``insert_string``.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``base_string`` is the string into which the insertion
						is to be made.

  						(.) ``insert_string`` is the string to be inserted.

  						(.) ``position`` is the index at which the insertion is to
						be made.

						(.) ``length`` is the maximum number of characters to be
						used from ``insert_string`` in performing the insertion.

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

	SEE ALSO		:	strinst

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

   COPYRIGHT   :  Copyright 1989 - 2015 Michael L. Brock

	OUTPUT INDEX:	strninst
						String Cut And Paste Functions:strninst
						STRFUNCS:String Cut And Paste Functions:strninst
						String Functions:See STRFUNCS

	PUBLISH XREF:	strninst

	PUBLISH NAME:	strninst

	ENTRY CLASS	:	String Cut And Paste Functions

EOH */
/* **************************************************************************	*/
#ifndef NARGS
char *strninst(char *base_string, const char *insert_string,
	unsigned int position, unsigned int length)
#else
char *strninst(base_string, insert_string, position, length)
char         *base_string;
const char   *insert_string;
unsigned int  position;
unsigned int  length;
#endif /* #ifndef NARGS */
{
	int          base_length;
	unsigned int insert_length;

	if (((insert_length = strlen(insert_string)) != 0) && (length > 0)) {
		insert_length = (length < insert_length) ? length : insert_length;
		if ((base_length = strlen(base_string)) == 0)
			nstrcpy(base_string, insert_string, insert_length);
		else {
			if (position >= ((unsigned int) base_length))
				strncat(base_string, insert_string, insert_length);
			else {
				while (base_length > -1) {
					*(base_string + position + insert_length + base_length) =
					*(base_string + position + base_length);
					base_length--;
				}
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
int main()
{
	unsigned int count_1;
	unsigned int count_2;
	int          count_3;
	int          count_4;
	char         base_area[512 + 1];

	fprintf(stderr, "Test of function 'strninst()'\n");
	fprintf(stderr, "---- -- -------- ------------\n\n");

	for (count_1 = 0; count_1 < (sizeof(BaseList) / sizeof(BaseList[0]));
		count_1++) {
		for (count_2 = 0; count_2 < (sizeof(InsertList) / sizeof(InsertList[0]));
			count_2++) {
			for (count_3 = -1;
				count_3 <= ((int) (strlen(BaseList[count_1]) + 1));
				count_3++) {
				for (count_4 = -1;
					count_4 <= ((int) (strlen(InsertList[count_2]) + 1));
					count_4++) {
					strcpy(base_area, BaseList[count_1]);
				 	printf("[BASE:%s|%02u][INSERT:%s|%02u][POSITION:%02u]",
						base_area, strlen(base_area), InsertList[count_2],
						strlen(InsertList[count_2]), count_3);
					printf("[LENGTH:%02u]", count_4);
					strninst(base_area, InsertList[count_2], count_3, count_4);
					printf(" --- [NEW:%s|%02u]\n", base_area, strlen(base_area));
				}
			}
		}
	}

	return(0);
}
/* **************************************************************************	*/

#endif /* TEST_MAIN */

