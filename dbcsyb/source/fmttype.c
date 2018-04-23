/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Generic Sybase Support Functions Library Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Formats various Sybase data-types.

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
int DBC_SYB_FMT_Data(int sybase_type, unsigned int data_length,
	const void *data_ptr, unsigned int min_length, unsigned int max_length,
	int right_justify_flag, unsigned int decimal_places, char *out_string,
	char *error_text)
#else
int DBC_SYB_FMT_Data(sybase_type, data_length, data_ptr, min_length,
	max_length, right_justify_flag, decimal_places, out_string, error_text)
int           sybase_type;
unsigned int  data_length;
const void   *data_ptr;
unsigned int  min_length;
unsigned int  max_length;
int           right_justify_flag;
unsigned int  decimal_places;
char         *out_string;
char         *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = DBC_SUCCESS;

	switch (sybase_type) {
		case SYBBINARY		:
			DBC_SYB_FMT_SYBBINARY(data_length, data_ptr, min_length, max_length,
				right_justify_flag, out_string);
			break;
		case SYBIMAGE		:
			DBC_SYB_FMT_SYBIMAGE(data_length, data_ptr, min_length, max_length,
				right_justify_flag, out_string);
			break;
		case SYBBIT			:
			DBC_SYB_FMT_SYBBIT(data_length, data_ptr, min_length, max_length,
				right_justify_flag, "1", "0", out_string);
			break;
		case SYBCHAR		:
			DBC_SYB_FMT_SYBCHAR(data_length, data_ptr, min_length, max_length,
				right_justify_flag, out_string);
			break;
		case SYBTEXT		:
			DBC_SYB_FMT_SYBTEXT(data_length, data_ptr, min_length, max_length,
				right_justify_flag, out_string);
			break;
		case SYBINT1		:
			DBC_SYB_FMT_SYBINT1(data_length, data_ptr, min_length, max_length,
				right_justify_flag, out_string);
			break;
		case SYBINT2		:
			DBC_SYB_FMT_SYBINT2(data_length, data_ptr, min_length, max_length,
				right_justify_flag, out_string);
			break;
		case SYBINT4		:
			DBC_SYB_FMT_SYBINT4(data_length, data_ptr, min_length, max_length,
				right_justify_flag, out_string);
			break;
		case SYBREAL		:
			DBC_SYB_FMT_SYBREAL(data_length, data_ptr, min_length, max_length,
				right_justify_flag, decimal_places, out_string);
			break;
		case SYBFLT8		:
			DBC_SYB_FMT_SYBFLT8(data_length, data_ptr, min_length, max_length,
				right_justify_flag, decimal_places, out_string);
			break;
		case SYBMONEY		:
			DBC_SYB_FMT_SYBMONEY(data_length, data_ptr, min_length, max_length,
				right_justify_flag, decimal_places, out_string);
			break;
		case SYBMONEY4		:
			DBC_SYB_FMT_SYBMONEY4(data_length, data_ptr, min_length, max_length,
				right_justify_flag, decimal_places, out_string);
			break;
		case SYBDATETIME	:
			DBC_SYB_FMT_SYBDATETIME(data_length, data_ptr, min_length, max_length,
				right_justify_flag, NULL, out_string);
			break;
		case SYBDATETIME4	:
			DBC_SYB_FMT_SYBDATETIME4(data_length, data_ptr, min_length, max_length,
				right_justify_flag, NULL, out_string);
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
char *DBC_SYB_FMT_SYBBINARY(unsigned int data_length, const void *data_ptr,
	unsigned int min_length, unsigned int max_length, int right_justify_flag,
	char *out_string)
#else
char *DBC_SYB_FMT_SYBBINARY(data_length, data_ptr, min_length, max_length,
	right_justify_flag, out_string)
unsigned int  data_length;
const void   *data_ptr;
unsigned int  min_length;
unsigned int  max_length;
int           right_justify_flag;
char         *out_string;
#endif /* #ifndef NARGS */
{
	unsigned int  out_length;
	char         *string_ptr;

	string_ptr  = out_string;

	data_length = (max_length && (data_length > max_length)) ? max_length :
		data_length;
	out_length  = data_length * 2;

	while (data_length) {
		val2str(((unsigned long) *((unsigned char *) data_ptr)), 0, 16, NULL,
			string_ptr);
		data_ptr    = ((const void *) (((const char *) data_ptr) + 1));
		string_ptr += 2;
	}

	return((min_length <= out_length) ? out_string : ((right_justify_flag) ?
		strpadr(out_string, min_length) : strpadl(out_string, min_length)));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *DBC_SYB_FMT_SYBIMAGE(unsigned int data_length, const void *data_ptr,
	unsigned int min_length, unsigned int max_length, int right_justify_flag,
	char *out_string)
#else
char *DBC_SYB_FMT_SYBIMAGE(data_length, data_ptr, min_length, max_length,
	right_justify_flag, out_string)
unsigned int  data_length;
const void   *data_ptr;
unsigned int  min_length;
unsigned int  max_length;
int           right_justify_flag;
char         *out_string;
#endif /* #ifndef NARGS */
{
	return(DBC_SYB_FMT_SYBBINARY(data_length, data_ptr, min_length,
		max_length, right_justify_flag, out_string));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *DBC_SYB_FMT_SYBBIT(unsigned int data_length, const void *data_ptr,
	unsigned int min_length, unsigned int max_length, int right_justify_flag,
	const char *true_string, const char *false_string, char *out_string)
#else
char *DBC_SYB_FMT_SYBBIT(data_length, data_ptr, min_length, max_length,
	right_justify_flag, true_string, false_string, out_string)
unsigned int  data_length;
const void   *data_ptr;
unsigned int  min_length;
unsigned int  max_length;
int           right_justify_flag;
const char   *true_string;
const char   *false_string;
char         *out_string;
#endif /* #ifndef NARGS */
{
	unsigned int out_length;

	out_length = strlen(nstrcpy(out_string,
		(*((char *) data_ptr) && (true_string != NULL)) ? true_string :
		((!(*((char *) data_ptr))) && (false_string != NULL)) ? false_string :
		((*((char *) data_ptr)) ? "1" : "0"), max_length));

	return((min_length <= out_length) ? out_string : ((right_justify_flag) ?
		strpadr(out_string, min_length) : strpadl(out_string, min_length)));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *DBC_SYB_FMT_SYBCHAR(unsigned int data_length, const void *data_ptr,
	unsigned int min_length, unsigned int max_length, int right_justify_flag,
	char *out_string)
#else
char *DBC_SYB_FMT_SYBCHAR(data_length, data_ptr, min_length, max_length,
	right_justify_flag, out_string)
unsigned int  data_length;
const void   *data_ptr;
unsigned int  min_length;
unsigned int  max_length;
int           right_justify_flag;
char         *out_string;
#endif /* #ifndef NARGS */
{
	unsigned int out_length;

	out_length = strlen(nstrcpy(out_string, ((const char *) data_ptr),
		max_length));

	return((min_length <= out_length) ? out_string : ((right_justify_flag) ?
		strpadr(out_string, min_length) : strpadl(out_string, min_length)));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *DBC_SYB_FMT_SYBTEXT(unsigned int data_length, const void *data_ptr,
	unsigned int min_length, unsigned int max_length, int right_justify_flag,
	char *out_string)
#else
char *DBC_SYB_FMT_SYBTEXT(data_length, data_ptr, min_length, max_length,
	right_justify_flag, out_string)
unsigned int  data_length;
const void   *data_ptr;
unsigned int  min_length;
unsigned int  max_length;
int           right_justify_flag;
char         *out_string;
#endif /* #ifndef NARGS */
{
	return(DBC_SYB_FMT_SYBCHAR(data_length, data_ptr, min_length, max_length,
		right_justify_flag, out_string));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *DBC_SYB_FMT_SYBINT1(unsigned int data_length, const void *data_ptr,
	unsigned int min_length, unsigned int max_length, int right_justify_flag,
	char *out_string)
#else
char *DBC_SYB_FMT_SYBINT1(data_length, data_ptr, min_length, max_length,
	right_justify_flag, out_string)
unsigned int  data_length;
const void   *data_ptr;
unsigned int  min_length;
unsigned int  max_length;
int           right_justify_flag;
char         *out_string;
#endif /* #ifndef NARGS */
{
	unsigned int out_length;
	char         buffer[STR_VAL2STR_MAX_LEN + 1];

	out_length = strlen(nstrcpy(out_string, val2str(((unsigned long)
		*((unsigned char *) data_ptr)), 0, 10, NULL, buffer), max_length));

	return((min_length <= out_length) ? out_string : ((right_justify_flag) ?
		strpadr(out_string, min_length) : strpadl(out_string, min_length)));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *DBC_SYB_FMT_SYBINT2(unsigned int data_length, const void *data_ptr,
	unsigned int min_length, unsigned int max_length, int right_justify_flag,
	char *out_string)
#else
char *DBC_SYB_FMT_SYBINT2(data_length, data_ptr, min_length, max_length,
	right_justify_flag, out_string)
unsigned int  data_length;
const void   *data_ptr;
unsigned int  min_length;
unsigned int  max_length;
int           right_justify_flag;
char         *out_string;
#endif /* #ifndef NARGS */
{
	unsigned int out_length;
	char         buffer[STR_VAL2STR_MAX_LEN + 1];

	out_length = strlen(nstrcpy(out_string, val2str(((unsigned long)
		abs((int) *((short *) data_ptr))), (((int) *((short *) data_ptr)) < 0) ?
		-1 : 0, 10, NULL, buffer), max_length));

	return((min_length <= out_length) ? out_string : ((right_justify_flag) ?
		strpadr(out_string, min_length) : strpadl(out_string, min_length)));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *DBC_SYB_FMT_SYBINT4(unsigned int data_length, const void *data_ptr,
	unsigned int min_length, unsigned int max_length, int right_justify_flag,
	char *out_string)
#else
char *DBC_SYB_FMT_SYBINT4(data_length, data_ptr, min_length, max_length,
	right_justify_flag, out_string)
unsigned int  data_length;
const void   *data_ptr;
unsigned int  min_length;
unsigned int  max_length;
int           right_justify_flag;
char         *out_string;
#endif /* #ifndef NARGS */
{
	unsigned int out_length;
	char         buffer[STR_VAL2STR_MAX_LEN + 1];

	out_length = strlen(nstrcpy(out_string, val2str(((unsigned long)
		abs(*((long *) data_ptr))), (*((long *) data_ptr) < 0) ? -1 : 0, 10,
		NULL, buffer), max_length));

	return((min_length <= out_length) ? out_string : ((right_justify_flag) ?
		strpadr(out_string, min_length) : strpadl(out_string, min_length)));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *DBC_SYB_FMT_SYBREAL(unsigned int data_length, const void *data_ptr,
	unsigned int min_length, unsigned int max_length, int right_justify_flag,
	unsigned int decimal_places, char *out_string)
#else
char *DBC_SYB_FMT_SYBREAL(data_length, data_ptr, min_length, max_length,
	right_justify_flag, decimal_places, out_string)
unsigned int  data_length;
const void   *data_ptr;
unsigned int  min_length;
unsigned int  max_length;
int           right_justify_flag;
unsigned int  decimal_places;
char         *out_string;
#endif /* #ifndef NARGS */
{
	unsigned int out_length;
	char         buffer[1024];

	sprintf(buffer, "%.*f", ((int) decimal_places),
		((double) *((float *) data_ptr)));

	out_length = strlen(nstrcpy(out_string, buffer, max_length));

	return((min_length <= out_length) ? out_string : ((right_justify_flag) ?
		strpadr(out_string, min_length) : strpadl(out_string, min_length)));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *DBC_SYB_FMT_SYBFLT8(unsigned int data_length, const void *data_ptr,
	unsigned int min_length, unsigned int max_length, int right_justify_flag,
	unsigned int decimal_places, char *out_string)
#else
char *DBC_SYB_FMT_SYBFLT8(data_length, data_ptr, min_length, max_length,
	right_justify_flag, decimal_places, out_string)
unsigned int  data_length;
const void   *data_ptr;
unsigned int  min_length;
unsigned int  max_length;
int           right_justify_flag;
unsigned int  decimal_places;
char         *out_string;
#endif /* #ifndef NARGS */
{
	unsigned int out_length;
	char         buffer[1024];

	sprintf(buffer, "%.*f", ((int) decimal_places), *((double *) data_ptr));

	out_length = strlen(nstrcpy(out_string, buffer, max_length));

	return((min_length <= out_length) ? out_string : ((right_justify_flag) ?
		strpadr(out_string, min_length) : strpadl(out_string, min_length)));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *DBC_SYB_FMT_SYBMONEY(unsigned int data_length, const void *data_ptr,
	unsigned int min_length, unsigned int max_length, int right_justify_flag,
	unsigned int decimal_places, char *out_string)
#else
char *DBC_SYB_FMT_SYBMONEY(data_length, data_ptr, min_length, max_length,
	right_justify_flag, decimal_places, out_string)
unsigned int  data_length;
const void   *data_ptr;
unsigned int  min_length;
unsigned int  max_length;
int           right_justify_flag;
unsigned int  decimal_places;
char         *out_string;
#endif /* #ifndef NARGS */
{
	unsigned int out_length;
	char         buffer[1024];

	sprintf(buffer, "%.*f", ((int) decimal_places),
		DBC_SYB_DBMONEYToDouble(((DBMONEY *) data_ptr)));

	out_length = strlen(nstrcpy(out_string, buffer, max_length));

	return((min_length <= out_length) ? out_string : ((right_justify_flag) ?
		strpadr(out_string, min_length) : strpadl(out_string, min_length)));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *DBC_SYB_FMT_SYBMONEY4(unsigned int data_length, const void *data_ptr,
	unsigned int min_length, unsigned int max_length, int right_justify_flag,
	unsigned int decimal_places, char *out_string)
#else
char *DBC_SYB_FMT_SYBMONEY4(data_length, data_ptr, min_length, max_length,
	right_justify_flag, decimal_places, out_string)
unsigned int  data_length;
const void   *data_ptr;
unsigned int  min_length;
unsigned int  max_length;
int           right_justify_flag;
unsigned int  decimal_places;
char         *out_string;
#endif /* #ifndef NARGS */
{
	unsigned int out_length;
	char         buffer[1024];

	sprintf(buffer, "%.*f", ((int) decimal_places),
		DBC_SYB_DBMONEY4ToDouble(((DBMONEY4 *) data_ptr)));

	out_length = strlen(nstrcpy(out_string, buffer, max_length));

	return((min_length <= out_length) ? out_string : ((right_justify_flag) ?
		strpadr(out_string, min_length) : strpadl(out_string, min_length)));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *DBC_SYB_FMT_SYBDATETIME(unsigned int data_length, const void *data_ptr,
	unsigned int min_length, unsigned int max_length, int right_justify_flag,
	const char *date_format, char *out_string)
#else
char *DBC_SYB_FMT_SYBDATETIME(data_length, data_ptr, min_length, max_length,
	right_justify_flag, date_format, out_string)
unsigned int  data_length;
const void   *data_ptr;
unsigned int  min_length;
unsigned int  max_length;
int           right_justify_flag;
const char   *date_format;
char         *out_string;
#endif /* #ifndef NARGS */
{
	unsigned int out_length;
	DTIME        tmp_dtime;
	char         buffer[1024];

	out_length = strlen(nstrcpy(out_string,
		DTIME_FormatDate(DBC_SYB_Sybase8ToDTIME(((DBDATETIME *) data_ptr),
		&tmp_dtime), date_format, buffer), max_length));

	return((min_length <= out_length) ? out_string : ((right_justify_flag) ?
		strpadr(out_string, min_length) : strpadl(out_string, min_length)));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *DBC_SYB_FMT_SYBDATETIME4(unsigned int data_length, const void *data_ptr,
	unsigned int min_length, unsigned int max_length, int right_justify_flag,
	const char *date_format, char *out_string)
#else
char *DBC_SYB_FMT_SYBDATETIME4(data_length, data_ptr, min_length, max_length,
	right_justify_flag, date_format, out_string)
unsigned int  data_length;
const void   *data_ptr;
unsigned int  min_length;
unsigned int  max_length;
int           right_justify_flag;
const char   *date_format;
char         *out_string;
#endif /* #ifndef NARGS */
{
	unsigned int out_length;
	DTIME        tmp_dtime;
	char         buffer[1024];

	out_length = strlen(nstrcpy(out_string,
		DTIME_FormatDate(DBC_SYB_Sybase4ToDTIME(((DBDATETIME4 *) data_ptr),
		&tmp_dtime), date_format, buffer), max_length));

	return((min_length <= out_length) ? out_string : ((right_justify_flag) ?
		strpadr(out_string, min_length) : strpadl(out_string, min_length)));
}
/*	***********************************************************************	*/

