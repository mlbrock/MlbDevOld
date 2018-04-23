/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	STRFUNCS String and Memory Functions Library Module							*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Functions for the concatenation of human-readable
								function parameters into a string.

	Revision History	:	1995-05-01 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*    Include necessary header files . . .                                 */
/*	***********************************************************************	*/

#include <mbcompat.h>

#include <limits.h>
#include <string.h>

#ifdef _Windows
# ifdef _MSC_VER
#  if _MSC_VER >= 1310
#   pragma warning(disable:4820)
#   pragma warning(disable:4668)
#   include <windows.h>
#   pragma warning(default:4668)
#  elif _MSC_VER >= 1300
#   pragma warning(disable:4255 4668)
#   include <windows.h>
#   pragma warning(default:4255 4668)
#  elif _MSC_VER >= 1200
#   pragma warning(disable:4115)
#   include <windows.h>
#   pragma warning(default:4115)
#  else
#   pragma warning(disable:4115 4201 4214 4514)
#   include <windows.h>
#   pragma warning(default:4115 4201 4214)
# 	endif /* #  if _MSC_VER >= 1310 */
# else
#  include <windows.h>
# endif /* # ifdef _MSC_VER */
#endif /* #ifdef _Windows */

#include "strfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
char *STR_FormatParamAny(const char *in_type_name, const char *in_string,
	int flags, char *out_string)
{
	return(strcat(strcat(strcat(strcat(out_string,
		(in_type_name != NULL) ? in_type_name : "???"),
		" = "),
		(in_string != NULL) ? in_string : "NULL"),
		(flags) ? ", " : ") = "));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
char *STR_FormatParamString(const char *in_type_name, const char *in_string,
	unsigned int max_length, int flags, char *out_string)
{
	strcat(strcat(out_string, (in_type_name != NULL) ? in_type_name : "???"),
		" = ");

	if (in_string == NULL)
		strcat(out_string, "NULL");
#ifdef _Windows
	else if (IsBadStringPtr(((char *) in_string), UINT_MAX) != 0)
		strcat(val2str_ptr_cat(in_string, strcat(out_string, "0x")),
		" = <invalid address>");
#endif /* #ifdef _Windows */
	else
		strcat(chrcat(nstrcat(chrcat(out_string, '\"'), in_string, max_length),
			'\"'), (strlen(in_string) <= max_length) ? "" : "...");

	return(strcat(out_string, (flags) ? ", " : ") = "));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
char *STR_FormatParamHex(const char *in_type_name, unsigned long in_ulong,
	int flags, char *out_string)
{
	char number_buffer[STR_VAL2STR_MAX_LEN + 1];

	return(STR_FormatParamAny(in_type_name,
		lower(val2str_ulong(in_ulong, 16, "", number_buffer)), flags,
		out_string));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
char *STR_FormatParamULong(const char *in_type_name, unsigned long in_ulong,
	int flags, char *out_string)
{
	char number_buffer[STR_VAL2STR_MAX_LEN + 1];

	return(STR_FormatParamAny(in_type_name,
		val2str_ulong(in_ulong, 10, "", number_buffer), flags, out_string));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
char *STR_FormatParamSLong(const char *in_type_name, long in_slong,
	int flags, char *out_string)
{
	char number_buffer[STR_VAL2STR_MAX_LEN + 1];

	return(STR_FormatParamAny(in_type_name,
		nospace(val2str_slong(in_slong, 10, "", number_buffer)), flags,
		out_string));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
char *STR_FormatParamPtr(const char *in_type_name, const void *in_ptr,
	int flags, char *out_string)
{
	char number_buffer[2 + STR_VAL2STR_MAX_LEN + 1];

	return(STR_FormatParamAny(in_type_name, val2str_ptr(in_ptr, number_buffer),
		flags, out_string));
}
/*	***********************************************************************	*/

#ifdef _Windows
# ifdef _MSC_VER
#  if _MSC_VER >= 1310
#   pragma warning(default:4820)
# 	endif /* #  if _MSC_VER >= 1310 */
# endif /* # ifdef _MSC_VER */
#endif /* #ifdef _Windows */

