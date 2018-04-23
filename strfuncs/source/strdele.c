/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Removes characters from a string.

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

#include <string.h>

#include "strfunci.h"

/* **************************************************************************	*/

/* **************************************************************************	*/
/* **************************************************************************	*/
/* BOH

	NAME			: 	strdele

	SYNOPSIS		:	string_ptr = strdele(base_string, position, delete_length);

						char         *string_ptr;

						char         *base_string;

  						unsigned int  delete_length;

  						unsigned int  position;

	DESCRIPTION	:	Removes the characters in a specified portion of a string.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``base_string`` is the string from which characters
						are to be deleted.

						(.) ``delete_length`` is the number of characters to be
						deleted.

  						(.) ``position`` is the index at which the deletion is to
						be made.

	RETURNS		:	The parameter ``base_string``.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

   COPYRIGHT   :  Copyright 1989 - 2018 Michael L. Brock

	OUTPUT INDEX:	strdele
						String Cut And Paste Functions:strdele
						STRFUNCS:String Cut And Paste Functions:strdele
						String Functions:See STRFUNCS

	PUBLISH XREF:	strdele

	PUBLISH NAME:	strdele

	ENTRY CLASS	:	String Cut And Paste Functions

EOH */
/* **************************************************************************	*/
#ifndef NARGS
char *strdele(char *base_string, unsigned int position,
	unsigned int delete_length)
#else
char *strdele(base_string, position, delete_length)
char         *base_string;
unsigned int  position;
unsigned int  delete_length;
#endif /* #ifndef NARGS */
{
	unsigned int  base_length;
	char         *tmp_ptr_1;
	char         *tmp_ptr_2;

	if (((base_length = strlen(base_string)) > 0) && (delete_length > 0)) {
		if (position < base_length) {
			if ((position + delete_length) >= base_length)
				*(base_string + position) = '\0';
			else {
				tmp_ptr_1 = base_string + position;
				tmp_ptr_2 = base_string + position + delete_length;
				while (base_string) {
					*tmp_ptr_1 = *tmp_ptr_2;
					if (!(*tmp_ptr_2))
						break;
					tmp_ptr_1++;
					tmp_ptr_2++;
				}
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

/* **************************************************************************	*/
/* **************************************************************************	*/
/* **************************************************************************	*/
int main()
{
	unsigned int count_1;
	unsigned int count_2;
	unsigned int count_3;
	char         base_area[512 + 1];

	fprintf(stderr, "Test of function 'strdele()'\n");
	fprintf(stderr, "---- -- -------- -----------\n\n");

	for (count_1 = 0; count_1 < (sizeof(BaseList) / sizeof(BaseList[0]));
		count_1++) {
		for (count_2 = 0; count_2 < (strlen(BaseList[count_1]) + 1);
			count_2++) {
			for (count_3 = 0; count_3 <= (strlen(BaseList[count_1]) + 1);
				count_3++) {
				strcpy(base_area, BaseList[count_1]);
				printf("[BASE:%s|%02u][POSITION:%02u][DELETE:%02u]",
					base_area, strlen(base_area), count_2, count_3);
				strdele(base_area, count_2, count_3);
				printf(" --- [NEW:%s|%02u]\n", base_area, strlen(base_area));
			}
		}
	}

	return(0);
}
/* **************************************************************************	*/

#endif /* TEST_MAIN */

