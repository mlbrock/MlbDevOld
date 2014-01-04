/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Microsoft SQL Server Support Functions Library Module					*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Formats various Microsoft SQL Server data-types.

	Revision History	:	1995-12-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2014.
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

#include "dbcmssql.h"

/*	***********************************************************************	*/

int DBC_MSSQL_FMT_Data(sybase_type, data_length, data_ptr, min_length,
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
{
	int return_code = DBC_SUCCESS;

	switch (sybase_type) {
		case SQLBINARY		:
			DBC_MSSQL_FMT_SQLBINARY(data_length, data_ptr, min_length, max_length,
				right_justify_flag, out_string);
			break;
		case SQLIMAGE		:
			DBC_MSSQL_FMT_SQLIMAGE(data_length, data_ptr, min_length, max_length,
				right_justify_flag, out_string);
			break;
		case SQLBIT			:
			DBC_MSSQL_FMT_SQLBIT(data_length, data_ptr, min_length, max_length,
				right_justify_flag, "1", "0", out_string);
			break;
		case SQLCHAR		:
			DBC_MSSQL_FMT_SQLCHAR(data_length, data_ptr, min_length, max_length,
				right_justify_flag, out_string);
			break;
		case SQLTEXT		:
			DBC_MSSQL_FMT_SQLTEXT(data_length, data_ptr, min_length, max_length,
				right_justify_flag, out_string);
			break;
		case SQLINT1		:
			DBC_MSSQL_FMT_SQLINT1(data_length, data_ptr, min_length, max_length,
				right_justify_flag, out_string);
			break;
		case SQLINT2		:
			DBC_MSSQL_FMT_SQLINT2(data_length, data_ptr, min_length, max_length,
				right_justify_flag, out_string);
			break;
		case SQLINT4		:
			DBC_MSSQL_FMT_SQLINT4(data_length, data_ptr, min_length, max_length,
				right_justify_flag, out_string);
			break;
		case SQLFLT4		:
			DBC_MSSQL_FMT_SQLREAL(data_length, data_ptr, min_length, max_length,
				right_justify_flag, decimal_places, out_string);
			break;
		case SQLFLT8		:
			DBC_MSSQL_FMT_SQLFLT8(data_length, data_ptr, min_length, max_length,
				right_justify_flag, decimal_places, out_string);
			break;
		case SQLMONEY		:
			DBC_MSSQL_FMT_SQLMONEY(data_length, data_ptr, min_length, max_length,
				right_justify_flag, decimal_places, out_string);
			break;
		case SQLMONEY4		:
			DBC_MSSQL_FMT_SQLMONEY4(data_length, data_ptr, min_length, max_length,
				right_justify_flag, decimal_places, out_string);
			break;
		case SQLDATETIME	:
			DBC_MSSQL_FMT_SQLDATETIME(data_length, data_ptr, min_length, max_length,
				right_justify_flag, NULL, out_string);
			break;
		case SQLDATETIM4	:
			DBC_MSSQL_FMT_SQLDATETIME4(data_length, data_ptr, min_length, max_length,
				right_justify_flag, NULL, out_string);
			break;
		default				:
			sprintf(error_text, "Unsupported Microsoft SQL Server type encountered (%d).",
				sybase_type);
			return_code = DBC_FAILURE;
			break;
	}

	return(return_code);
}
/*	***********************************************************************	*/

char *DBC_MSSQL_FMT_SQLBINARY(data_length, data_ptr, min_length, max_length,
	right_justify_flag, out_string)
unsigned int  data_length;
const void   *data_ptr;
unsigned int  min_length;
unsigned int  max_length;
int           right_justify_flag;
char         *out_string;
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

char *DBC_MSSQL_FMT_SQLIMAGE(data_length, data_ptr, min_length, max_length,
	right_justify_flag, out_string)
unsigned int  data_length;
const void   *data_ptr;
unsigned int  min_length;
unsigned int  max_length;
int           right_justify_flag;
char         *out_string;
{
	return(DBC_MSSQL_FMT_SQLBINARY(data_length, data_ptr, min_length,
		max_length, right_justify_flag, out_string));
}
/*	***********************************************************************	*/

char *DBC_MSSQL_FMT_SQLBIT(data_length, data_ptr, min_length, max_length,
	right_justify_flag, true_string, false_string, out_string)
unsigned int  data_length;
const void   *data_ptr;
unsigned int  min_length;
unsigned int  max_length;
int           right_justify_flag;
const char   *true_string;
const char   *false_string;
char         *out_string;
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

char *DBC_MSSQL_FMT_SQLCHAR(data_length, data_ptr, min_length, max_length,
	right_justify_flag, out_string)
unsigned int  data_length;
const void   *data_ptr;
unsigned int  min_length;
unsigned int  max_length;
int           right_justify_flag;
char         *out_string;
{
	unsigned int out_length;

	out_length = strlen(nstrcpy(out_string, data_ptr, max_length));

	return((min_length <= out_length) ? out_string : ((right_justify_flag) ?
		strpadr(out_string, min_length) : strpadl(out_string, min_length)));
}
/*	***********************************************************************	*/

char *DBC_MSSQL_FMT_SQLTEXT(data_length, data_ptr, min_length, max_length,
	right_justify_flag, out_string)
unsigned int  data_length;
const void   *data_ptr;
unsigned int  min_length;
unsigned int  max_length;
int           right_justify_flag;
char         *out_string;
{
	return(DBC_MSSQL_FMT_SQLCHAR(data_length, data_ptr, min_length, max_length,
		right_justify_flag, out_string));
}
/*	***********************************************************************	*/

char *DBC_MSSQL_FMT_SQLINT1(data_length, data_ptr, min_length, max_length,
	right_justify_flag, out_string)
unsigned int  data_length;
const void   *data_ptr;
unsigned int  min_length;
unsigned int  max_length;
int           right_justify_flag;
char         *out_string;
{
	unsigned int out_length;
	char         buffer[STR_VAL2STR_MAX_LEN + 1];

	out_length = strlen(nstrcpy(out_string, val2str(((unsigned long)
		*((unsigned char *) data_ptr)), 0, 10, NULL, buffer), max_length));

	return((min_length <= out_length) ? out_string : ((right_justify_flag) ?
		strpadr(out_string, min_length) : strpadl(out_string, min_length)));
}
/*	***********************************************************************	*/

char *DBC_MSSQL_FMT_SQLINT2(data_length, data_ptr, min_length, max_length,
	right_justify_flag, out_string)
unsigned int  data_length;
const void   *data_ptr;
unsigned int  min_length;
unsigned int  max_length;
int           right_justify_flag;
char         *out_string;
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

char *DBC_MSSQL_FMT_SQLINT4(data_length, data_ptr, min_length, max_length,
	right_justify_flag, out_string)
unsigned int  data_length;
const void   *data_ptr;
unsigned int  min_length;
unsigned int  max_length;
int           right_justify_flag;
char         *out_string;
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

char *DBC_MSSQL_FMT_SQLREAL(data_length, data_ptr, min_length, max_length,
	right_justify_flag, decimal_places, out_string)
unsigned int  data_length;
const void   *data_ptr;
unsigned int  min_length;
unsigned int  max_length;
int           right_justify_flag;
unsigned int  decimal_places;
char         *out_string;
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

char *DBC_MSSQL_FMT_SQLFLT8(data_length, data_ptr, min_length, max_length,
	right_justify_flag, decimal_places, out_string)
unsigned int  data_length;
const void   *data_ptr;
unsigned int  min_length;
unsigned int  max_length;
int           right_justify_flag;
unsigned int  decimal_places;
char         *out_string;
{
	unsigned int out_length;
	char         buffer[1024];

	sprintf(buffer, "%.*f", ((int) decimal_places), *((double *) data_ptr));

	out_length = strlen(nstrcpy(out_string, buffer, max_length));

	return((min_length <= out_length) ? out_string : ((right_justify_flag) ?
		strpadr(out_string, min_length) : strpadl(out_string, min_length)));
}
/*	***********************************************************************	*/

char *DBC_MSSQL_FMT_SQLMONEY(data_length, data_ptr, min_length, max_length,
	right_justify_flag, decimal_places, out_string)
unsigned int  data_length;
const void   *data_ptr;
unsigned int  min_length;
unsigned int  max_length;
int           right_justify_flag;
unsigned int  decimal_places;
char         *out_string;
{
	unsigned int out_length;
	char         buffer[1024];

	sprintf(buffer, "%.*f", ((int) decimal_places),
		DBC_MSSQL_DBMONEYToDouble(((DBMONEY *) data_ptr)));

	out_length = strlen(nstrcpy(out_string, buffer, max_length));

	return((min_length <= out_length) ? out_string : ((right_justify_flag) ?
		strpadr(out_string, min_length) : strpadl(out_string, min_length)));
}
/*	***********************************************************************	*/

char *DBC_MSSQL_FMT_SQLMONEY4(data_length, data_ptr, min_length, max_length,
	right_justify_flag, decimal_places, out_string)
unsigned int  data_length;
const void   *data_ptr;
unsigned int  min_length;
unsigned int  max_length;
int           right_justify_flag;
unsigned int  decimal_places;
char         *out_string;
{
	unsigned int out_length;
	char         buffer[1024];

	sprintf(buffer, "%.*f", ((int) decimal_places),
		DBC_MSSQL_DBMONEY4ToDouble(((DBMONEY4 *) data_ptr)));

	out_length = strlen(nstrcpy(out_string, buffer, max_length));

	return((min_length <= out_length) ? out_string : ((right_justify_flag) ?
		strpadr(out_string, min_length) : strpadl(out_string, min_length)));
}
/*	***********************************************************************	*/

char *DBC_MSSQL_FMT_SQLDATETIME(data_length, data_ptr, min_length, max_length,
	right_justify_flag, date_format, out_string)
unsigned int  data_length;
const void   *data_ptr;
unsigned int  min_length;
unsigned int  max_length;
int           right_justify_flag;
const char   *date_format;
char         *out_string;
{
	unsigned int out_length;
	DTIME        tmp_dtime;
	char         buffer[1024];

	out_length = strlen(nstrcpy(out_string,
		DTIME_FormatDate(DBC_MSSQL_MSSQL8ToDTIME(((DBDATETIME *) data_ptr),
		&tmp_dtime), date_format, buffer), max_length));

	return((min_length <= out_length) ? out_string : ((right_justify_flag) ?
		strpadr(out_string, min_length) : strpadl(out_string, min_length)));
}
/*	***********************************************************************	*/

char *DBC_MSSQL_FMT_SQLDATETIME4(data_length, data_ptr, min_length, max_length,
	right_justify_flag, date_format, out_string)
unsigned int  data_length;
const void   *data_ptr;
unsigned int  min_length;
unsigned int  max_length;
int           right_justify_flag;
const char   *date_format;
char         *out_string;
{
	unsigned int out_length;
	DTIME        tmp_dtime;
	char         buffer[1024];

	out_length = strlen(nstrcpy(out_string,
		DTIME_FormatDate(DBC_MSSQL_MSSQL4ToDTIME(((DBDATETIM4 *) data_ptr),
		&tmp_dtime), date_format, buffer), max_length));

	return((min_length <= out_length) ? out_string : ((right_justify_flag) ?
		strpadr(out_string, min_length) : strpadl(out_string, min_length)));
}
/*	***********************************************************************	*/

