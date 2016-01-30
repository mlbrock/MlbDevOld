/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Specification Parse Facility (SPF) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Describes the location being parsed.

	Revision History	:	1995-08-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <limits.h>
#include <string.h>

#include <strfuncs.h>

#include "spffunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *SPF_GetLocationLine(const SPF_PARSE *parse_ptr, char *buffer)
#else
char *SPF_GetLocationLine(parse_ptr, buffer)
const SPF_PARSE *parse_ptr;
char            *buffer;
#endif /* #ifndef NARGS */
{
	char value_buffer[STR_VAL2STR_MAX_LEN + 1];

	return(strcat(strcpy(buffer, "on line number "),
		val2str(parse_ptr->line, 0, 10, NULL, value_buffer)));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *SPF_GetLocationFile(const SPF_PARSE *parse_ptr, unsigned int max_length,
   char *buffer)
#else
char *SPF_GetLocationFile(parse_ptr, max_length, buffer)
const SPF_PARSE *parse_ptr;
unsigned int     max_length;
char            *buffer;
#endif /* #ifndef NARGS */
{
	return(strcat(nstrcat(strcpy(buffer, "in file '"),
		(parse_ptr->file == NULL) ? SPF_PARSE_FILE_FAKE_NAME : parse_ptr->file,
		(!max_length) ? UINT_MAX : max_length), "'"));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *SPF_GetLocationLineFile(const SPF_PARSE *parse_ptr,
	unsigned int max_length, char *buffer)
#else
char *SPF_GetLocationLineFile(parse_ptr, max_length, buffer)
const SPF_PARSE *parse_ptr;
unsigned int     max_length;
char            *buffer;
#endif /* #ifndef NARGS */
{
	strcat(SPF_GetLocationLine(parse_ptr, buffer), " ");
	SPF_GetLocationFile(parse_ptr, max_length, buffer + strlen(buffer));

	return(buffer);
}
/*	***********************************************************************	*/

