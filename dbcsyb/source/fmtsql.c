/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Generic Sybase Support Functions Library Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Formats various Sybase data-types for use in SQL
								statements.

	Revision History	:	1993-08-14 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#include <limits.h>
#include <string.h>

#include "dbcsybi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int DBC_SYB_FMT_Data_SQL(int sybase_type, unsigned int data_length,
	const void *data_ptr, char *out_string, char *error_text)
#else
int DBC_SYB_FMT_Data_SQL(sybase_type, data_length, data_ptr, out_string,
	error_text)
int           sybase_type;
unsigned int  data_length;
const void   *data_ptr;
char         *out_string;
char         *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = DBC_SUCCESS;

	switch (sybase_type) {
		case SYBBINARY		:
			DBC_SYB_FMT_SYBBINARY_SQL(data_length, data_ptr, out_string);
			break;
		case SYBIMAGE		:
			DBC_SYB_FMT_SYBIMAGE_SQL(data_length, data_ptr, out_string);
			break;
		case SYBBIT			:
			DBC_SYB_FMT_SYBBIT_SQL(data_ptr, out_string);
			break;
		case SYBCHAR		:
			DBC_SYB_FMT_SYBCHAR_SQL(data_ptr, out_string);
			break;
		case SYBTEXT		:
			DBC_SYB_FMT_SYBTEXT_SQL(data_ptr, out_string);
			break;
		case SYBINT1		:
			DBC_SYB_FMT_SYBINT1_SQL(data_ptr, out_string);
			break;
		case SYBINT2		:
			DBC_SYB_FMT_SYBINT2_SQL(data_ptr, out_string);
			break;
		case SYBINT4		:
			DBC_SYB_FMT_SYBINT4_SQL(data_ptr, out_string);
			break;
		case SYBREAL		:
			DBC_SYB_FMT_SYBREAL_SQL(data_ptr, out_string);
			break;
		case SYBFLT8		:
			DBC_SYB_FMT_SYBFLT8_SQL(data_ptr, out_string);
			break;
		case SYBMONEY		:
			DBC_SYB_FMT_SYBMONEY_SQL(data_ptr, out_string);
			break;
		case SYBMONEY4		:
			DBC_SYB_FMT_SYBMONEY4_SQL(data_ptr, out_string);
			break;
		case SYBDATETIME	:
			DBC_SYB_FMT_SYBDATETIME_SQL(data_ptr, out_string);
			break;
		case SYBDATETIME4	:
			DBC_SYB_FMT_SYBDATETIME4_SQL(data_ptr, out_string);
			break;
		default				:
			sprintf(error_text, "Unsupported Sybase type encountered (%d).",
				sybase_type);
			return_code = DBC_FAILURE;
			break;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *DBC_SYB_FMT_SYBBINARY_SQL(unsigned int data_length, const void *data_ptr,
	char *out_string)
#else
char *DBC_SYB_FMT_SYBBINARY_SQL(data_length, data_ptr, out_string)
unsigned int  data_length;
const void   *data_ptr;
char         *out_string;
#endif /* #ifndef NARGS */
{
	return(strcat(strcpy(out_string, "0X"), DBC_SYB_FMT_SYBBINARY(data_length,
		data_ptr, 0, 0, 0, out_string + 2)));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *DBC_SYB_FMT_SYBIMAGE_SQL(unsigned int data_length, const void *data_ptr,
	char *out_string)
#else
char *DBC_SYB_FMT_SYBIMAGE_SQL(data_length, data_ptr, out_string)
unsigned int  data_length;
const void   *data_ptr;
char         *out_string;
#endif /* #ifndef NARGS */
{
	return(DBC_SYB_FMT_SYBBINARY_SQL(data_length, data_ptr, out_string));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *DBC_SYB_FMT_SYBBIT_SQL(const void *data_ptr, char *out_string)
#else
char *DBC_SYB_FMT_SYBBIT_SQL(data_ptr, out_string)
const void *data_ptr;
char       *out_string;
#endif /* #ifndef NARGS */
{
	return(DBC_SYB_FMT_SYBBIT(1, data_ptr, 0, 0, 0, NULL, NULL, out_string));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *DBC_SYB_FMT_SYBCHAR_SQL(const void *data_ptr, char *out_string)
#else
char *DBC_SYB_FMT_SYBCHAR_SQL(data_ptr, out_string)
const void *data_ptr;
char       *out_string;
#endif /* #ifndef NARGS */
{
	return(strcat(strcat(strcpy(out_string, "\""),
		strescap(strcpy(++out_string, ((const char *) data_ptr)), "\"", NULL)),
		"\""));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *DBC_SYB_FMT_SYBTEXT_SQL(const void *data_ptr, char *out_string)
#else
char *DBC_SYB_FMT_SYBTEXT_SQL(data_ptr, out_string)
const void *data_ptr;
char       *out_string;
#endif /* #ifndef NARGS */
{
	return(DBC_SYB_FMT_SYBCHAR_SQL(data_ptr, out_string));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *DBC_SYB_FMT_SYBINT1_SQL(const void *data_ptr, char *out_string)
#else
char *DBC_SYB_FMT_SYBINT1_SQL(data_ptr, out_string)
const void *data_ptr;
char       *out_string;
#endif /* #ifndef NARGS */
{
	return(val2str(((unsigned long) *((unsigned char *) data_ptr)), 0, 10,
		NULL, out_string));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *DBC_SYB_FMT_SYBINT2_SQL(const void *data_ptr, char *out_string)
#else
char *DBC_SYB_FMT_SYBINT2_SQL(data_ptr, out_string)
const void *data_ptr;
char       *out_string;
#endif /* #ifndef NARGS */
{
	return(val2str(((unsigned long) abs((int) *((short *) data_ptr))),
		(((int) *((short *) data_ptr)) < 0) ? -1 : 0, 10, NULL, out_string));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *DBC_SYB_FMT_SYBINT4_SQL(const void *data_ptr, char *out_string)
#else
char *DBC_SYB_FMT_SYBINT4_SQL(data_ptr, out_string)
const void *data_ptr;
char       *out_string;
#endif /* #ifndef NARGS */
{
	return(val2str(((unsigned long) abs(*((long *) data_ptr))),
		(*((long *) data_ptr) < 0) ? -1 : 0, 10, NULL, out_string));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *DBC_SYB_FMT_SYBREAL_SQL(const void *data_ptr, char *out_string)
#else
char *DBC_SYB_FMT_SYBREAL_SQL(data_ptr, out_string)
const void *data_ptr;
char       *out_string;
#endif /* #ifndef NARGS */
{
	return(DBC_SYB_FMT_SYBREAL(1, data_ptr, 0, 0, 0, 20, out_string));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *DBC_SYB_FMT_SYBFLT8_SQL(const void *data_ptr, char *out_string)
#else
char *DBC_SYB_FMT_SYBFLT8_SQL(data_ptr, out_string)
const void *data_ptr;
char       *out_string;
#endif /* #ifndef NARGS */
{
	return(DBC_SYB_FMT_SYBFLT8(1, data_ptr, 0, 0, 0, 20, out_string));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *DBC_SYB_FMT_SYBMONEY_SQL(const void *data_ptr, char *out_string)
#else
char *DBC_SYB_FMT_SYBMONEY_SQL(data_ptr, out_string)
const void *data_ptr;
char       *out_string;
#endif /* #ifndef NARGS */
{
	return(DBC_SYB_FMT_SYBMONEY(1, data_ptr, 0, 0, 0, 4, out_string));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *DBC_SYB_FMT_SYBMONEY4_SQL(const void *data_ptr, char *out_string)
#else
char *DBC_SYB_FMT_SYBMONEY4_SQL(data_ptr, out_string)
const void *data_ptr;
char       *out_string;
#endif /* #ifndef NARGS */
{
	return(DBC_SYB_FMT_SYBMONEY4(1, data_ptr, 0, 0, 0, 4, out_string));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *DBC_SYB_FMT_SYBDATETIME_SQL(const void *data_ptr, char *out_string)
#else
char *DBC_SYB_FMT_SYBDATETIME_SQL(data_ptr, out_string)
const void *data_ptr;
char       *out_string;
#endif /* #ifndef NARGS */
{
	DTIME tmp_dtime;

	return(DTIME_FormatDate(DBC_SYB_Sybase8ToDTIME(((DBDATETIME *) data_ptr),
		&tmp_dtime), DATFUNCS_DEFAULT_DTIME_FORMAT, out_string));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *DBC_SYB_FMT_SYBDATETIME4_SQL(const void *data_ptr, char *out_string)
#else
char *DBC_SYB_FMT_SYBDATETIME4_SQL(data_ptr, out_string)
const void *data_ptr;
char       *out_string;
#endif /* #ifndef NARGS */
{
	DTIME tmp_dtime;

	return(DTIME_FormatDate(DBC_SYB_Sybase4ToDTIME(((DBDATETIME4 *) data_ptr),
		&tmp_dtime), DATFUNCS_DEFAULT_DTIME_FORMAT, out_string));
}
/*	***********************************************************************	*/

