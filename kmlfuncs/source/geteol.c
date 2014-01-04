/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Locates the end-of-line character in a string.

	Revision History	:	1998-03-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <memory.h>
#include <stdlib.h>
#include <string.h>

#include <genfuncs.h>

#include "kmlfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
const char *KML_GetEndOfLine(const char *in_string)
#else
const char *KML_GetEndOfLine(in_string)
const char *in_string;
#endif /* #ifndef NARGS */
{
	const char *nl_ptr_1;
	const char *nl_ptr_2;
	const char *end_of_line;

	nl_ptr_1 = strchr(in_string, '\r');
	nl_ptr_2 = strchr(in_string, '\n');

	if ((nl_ptr_1 != NULL) &&
		((nl_ptr_2 == NULL) || (nl_ptr_2 >= nl_ptr_1)))
		end_of_line = nl_ptr_1;
	else if (nl_ptr_2 != NULL)
		end_of_line = nl_ptr_2;
	else
		end_of_line = NULL;

	return(end_of_line);
}
/*	***********************************************************************	*/


