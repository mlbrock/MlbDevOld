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
/* 	Include necessary header files . . .											*/
/* *********************************************************************** */

#include <string.h>

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/*
*
* name		strins -- insert a string in front of another
*
* synopsis	strins(destination,insert_string);
*		char *insert_string;	source string
*		char *destination;	destination string
*
* description	This function inserts the source string in front of the
*		destination, pushing the destination up in memory.
*
**/
/* *********************************************************************** */
#ifndef NARGS
char *strins(char *destination, char *insert_string)
#else
char *strins(destination, insert_string)
char *destination;
char *insert_string;
#endif /* #ifndef NARGS */
{
	unsigned int  count_1;
	unsigned int  insert_length;
	unsigned int  destination_length;
	char         *tmp_ptr_1 = destination;
	char         *tmp_ptr_2;
	char         *tmp_ptr_3;

	if ((insert_length = strlen(insert_string)) > 0) {
		destination_length = strlen(destination);
		tmp_ptr_2          = destination + destination_length;
		tmp_ptr_3          = tmp_ptr_2 + insert_length;
		for (count_1 = 0; count_1 <= destination_length; count_1++)
			*tmp_ptr_3-- = *tmp_ptr_2--;
		while (*insert_string)
			*destination++ = *insert_string++;
	}

	return(tmp_ptr_1);
}
/* *********************************************************************** */

