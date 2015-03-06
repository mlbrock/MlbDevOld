/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Determine if one of a set of characters occurs in
								a string.

	Revision History	:	1998-12-02 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/*	*********************************************************************** */
/*	*********************************************************************** */
/* 	Necessary include files . . .														*/
/*	*********************************************************************** */

#include <limits.h>
#include <memory.h>

#include "strfunci.h"

/*	*********************************************************************** */

/*
	ADF NOTE: No ADF.
*/
/*	*********************************************************************** */
#ifndef NARGS
char *chrinstr(const char *in_string, const char *in_char_list)
#else
char *chrinstr(in_string, in_char_list)
const char *in_string;
const char *in_char_list;
#endif /* #ifndef NARGS */
{
	unsigned const char *tmp_ptr = NULL;
	unsigned char        char_map[UCHAR_MAX + 1];

	if ((in_string != NULL) && (in_char_list != NULL)) {
		memset(char_map, '\0', sizeof(char_map));
		tmp_ptr = ((const unsigned char *) in_char_list);
		while (*tmp_ptr)
			char_map[((unsigned int) *tmp_ptr++)] = 1;
		tmp_ptr = ((const unsigned char *) in_string);
		while (*tmp_ptr && (!char_map[((unsigned int) *tmp_ptr)]))
			tmp_ptr++;
		tmp_ptr = (*tmp_ptr) ? tmp_ptr : NULL;
	}

	return(((char *) tmp_ptr));
}
/* *********************************************************************** */

