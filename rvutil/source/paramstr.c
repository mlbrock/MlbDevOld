/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Functions for concatenated function parameters to
								a string.

	Revision History	:	1996-02-05 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <limits.h>
#include <string.h>

#include <genfuncs.h>

#include "rvutili.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
char *RVUTIL_ParamANY(const char *in_type_name, const char *in_string,
	int more_flag, char *out_string)
{
	return(strcat(strcat(strcat(strcat(out_string,
		(in_type_name != NULL) ? in_type_name : "???"),
		" = "),
		(in_string != NULL) ? in_string : "NULL"),
		(more_flag) ? ", " : ") = "));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
char *RVUTIL_ParamSTR(const char *in_type_name, const char *in_string,
	unsigned int max_length, int more_flag, char *out_string)
{
	char number_buffer[STR_VAL2STR_MAX_LEN + 1];

	strcat(strcat(out_string, (in_type_name != NULL) ? in_type_name : "???"),
		" = ");

	if (in_string == NULL)
		strcat(out_string, "NULL");
	else if (GEN_VPTR_IsValidString(((char *) in_string),
		GEN_VPTR_ACCESS_READ, NULL) != GENFUNCS_TRUE)
		strcat(strcat(strcat(out_string, "0x"),
			lower(val2str(((unsigned long) in_string), 0, 16, "",
			number_buffer))), " = <invalid address>");
	else
		strcat(chrcat(nstrcat(chrcat(out_string, '\"'), in_string, max_length),
			'\"'), (strlen(in_string) <= max_length) ? "" : "...");

	return(strcat(out_string, (more_flag) ? ", " : ") = "));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
char *RVUTIL_ParamHEX(const char *in_type_name, unsigned long in_ulong,
	int more_flag, char *out_string)
{
	char number_buffer[STR_VAL2STR_MAX_LEN + 1];

	return(RVUTIL_ParamANY(in_type_name,
		lower(val2str(in_ulong, 0, 16, "", number_buffer)), more_flag,
		out_string));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
char *RVUTIL_ParamULD(const char *in_type_name, unsigned long in_ulong,
	int more_flag, char *out_string)
{
	char number_buffer[STR_VAL2STR_MAX_LEN + 1];

	return(RVUTIL_ParamANY(in_type_name,
		val2str(in_ulong, 0, 10, "", number_buffer), more_flag, out_string));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
char *RVUTIL_ParamSLD(const char *in_type_name, long in_slong,
	int more_flag, char *out_string)
{
	char number_buffer[STR_VAL2STR_MAX_LEN + 1];

	return(RVUTIL_ParamANY(in_type_name,
		nospace(val2str(((unsigned long) ((in_slong < 0L) ? (0L - in_slong) :
		in_slong)), ((int) in_slong), 10, "", number_buffer)), more_flag,
		out_string));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
char *RVUTIL_ParamPTR(const char *in_type_name, void *in_ptr, int more_flag,
	char *out_string)
{
	char number_buffer[2 + STR_VAL2STR_MAX_LEN + 1];

	strcpy(number_buffer, "0x");
	lower(val2str(((unsigned long) in_ptr), 0, 16, "", number_buffer + 2));

	return(RVUTIL_ParamANY(in_type_name, number_buffer, more_flag,
		out_string));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
char *RVUTIL_ParamSUB(const char *in_type_name, const char *in_subject,
	int more_flag, char *out_string)
{
	return(RVUTIL_ParamSTR(in_type_name, in_subject, RVUTIL_MAX_SUB_NAME_LEN,
		more_flag, out_string));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
char *RVUTIL_ParamSND(const char *in_type_name, const char *in_snd,
	int more_flag, char *out_string)
{
	return(RVUTIL_ParamSTR(in_type_name, in_snd, RVUTIL_MAX_SND_NAME_LEN,
		more_flag, out_string));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
char *RVUTIL_ParamFNC(const char *in_type_name, int (*in_ptr)(void),
	int more_flag, char *out_string)
{
	return(RVUTIL_ParamPTR(in_type_name, STR_CAST_FUNC_PTR(in_ptr), more_flag,
		out_string));
}
/*	***********************************************************************	*/

