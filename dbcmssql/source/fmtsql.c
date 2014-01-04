/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Microsoft SQL Server Support Functions Library Module					*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Formats various Microsoft SQL Server data-types for
								use in SQL statements.

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

int DBC_MSSQL_FMT_Data_SQL(sybase_type, data_length, data_ptr, out_string,
	error_text)
int           sybase_type;
unsigned int  data_length;
const void   *data_ptr;
char         *out_string;
char         *error_text;
{
	int return_code = DBC_SUCCESS;

	switch (sybase_type) {
		case SQLBINARY		:
			DBC_MSSQL_FMT_SQLBINARY_SQL(data_length, data_ptr, out_string);
			break;
		case SQLIMAGE		:
			DBC_MSSQL_FMT_SQLIMAGE_SQL(data_length, data_ptr, out_string);
			break;
		case SQLBIT			:
			DBC_MSSQL_FMT_SQLBIT_SQL(data_ptr, out_string);
			break;
		case SQLCHAR		:
			DBC_MSSQL_FMT_SQLCHAR_SQL(data_ptr, out_string);
			break;
		case SQLTEXT		:
			DBC_MSSQL_FMT_SQLTEXT_SQL(data_ptr, out_string);
			break;
		case SQLINT1		:
			DBC_MSSQL_FMT_SQLINT1_SQL(data_ptr, out_string);
			break;
		case SQLINT2		:
			DBC_MSSQL_FMT_SQLINT2_SQL(data_ptr, out_string);
			break;
		case SQLINT4		:
			DBC_MSSQL_FMT_SQLINT4_SQL(data_ptr, out_string);
			break;
		case SQLFLT4		:
			DBC_MSSQL_FMT_SQLREAL_SQL(data_ptr, out_string);
			break;
		case SQLFLT8		:
			DBC_MSSQL_FMT_SQLFLT8_SQL(data_ptr, out_string);
			break;
		case SQLMONEY		:
			DBC_MSSQL_FMT_SQLMONEY_SQL(data_ptr, out_string);
			break;
		case SQLMONEY4		:
			DBC_MSSQL_FMT_SQLMONEY4_SQL(data_ptr, out_string);
			break;
		case SQLDATETIME	:
			DBC_MSSQL_FMT_SQLDATETIME_SQL(data_ptr, out_string);
			break;
		case SQLDATETIM4	:
			DBC_MSSQL_FMT_SQLDATETIME4_SQL(data_ptr, out_string);
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

char *DBC_MSSQL_FMT_SQLBINARY_SQL(data_length, data_ptr, out_string)
unsigned int  data_length;
const void   *data_ptr;
char         *out_string;
{
	return(strcat(strcpy(out_string, "0X"), DBC_MSSQL_FMT_SQLBINARY(data_length,
		data_ptr, 0, 0, 0, out_string + 2)));
}
/*	***********************************************************************	*/

char *DBC_MSSQL_FMT_SQLIMAGE_SQL(data_length, data_ptr, out_string)
unsigned int  data_length;
const void   *data_ptr;
char         *out_string;
{
	return(DBC_MSSQL_FMT_SQLBINARY_SQL(data_length, data_ptr, out_string));
}
/*	***********************************************************************	*/

char *DBC_MSSQL_FMT_SQLBIT_SQL(data_ptr, out_string)
const void *data_ptr;
char       *out_string;
{
	return(DBC_MSSQL_FMT_SQLBIT(1, data_ptr, 0, 0, 0, NULL, NULL, out_string));
}
/*	***********************************************************************	*/

char *DBC_MSSQL_FMT_SQLCHAR_SQL(data_ptr, out_string)
const void *data_ptr;
char       *out_string;
{
	return(strcat(strcat(strcpy(out_string, "\""),
		strescap(strcpy(++out_string, data_ptr), "\"", NULL)), "\""));
}
/*	***********************************************************************	*/

char *DBC_MSSQL_FMT_SQLTEXT_SQL(data_ptr, out_string)
const void *data_ptr;
char       *out_string;
{
	return(DBC_MSSQL_FMT_SQLCHAR_SQL(data_ptr, out_string));
}
/*	***********************************************************************	*/

char *DBC_MSSQL_FMT_SQLINT1_SQL(data_ptr, out_string)
const void *data_ptr;
char       *out_string;
{
	return(val2str(((unsigned long) *((unsigned char *) data_ptr)), 0, 10,
		NULL, out_string));
}
/*	***********************************************************************	*/

char *DBC_MSSQL_FMT_SQLINT2_SQL(data_ptr, out_string)
const void *data_ptr;
char       *out_string;
{
	return(val2str(((unsigned long) abs((int) *((short *) data_ptr))),
		(((int) *((short *) data_ptr)) < 0) ? -1 : 0, 10, NULL, out_string));
}
/*	***********************************************************************	*/

char *DBC_MSSQL_FMT_SQLINT4_SQL(data_ptr, out_string)
const void *data_ptr;
char       *out_string;
{
	return(val2str(((unsigned long) abs(*((long *) data_ptr))),
		(*((long *) data_ptr) < 0) ? -1 : 0, 10, NULL, out_string));
}
/*	***********************************************************************	*/

char *DBC_MSSQL_FMT_SQLREAL_SQL(data_ptr, out_string)
const void *data_ptr;
char       *out_string;
{
	return(DBC_MSSQL_FMT_SQLREAL(1, data_ptr, 0, 0, 0, 20, out_string));
}
/*	***********************************************************************	*/

char *DBC_MSSQL_FMT_SQLFLT8_SQL(data_ptr, out_string)
const void *data_ptr;
char       *out_string;
{
	return(DBC_MSSQL_FMT_SQLFLT8(1, data_ptr, 0, 0, 0, 20, out_string));
}
/*	***********************************************************************	*/

char *DBC_MSSQL_FMT_SQLMONEY_SQL(data_ptr, out_string)
const void *data_ptr;
char       *out_string;
{
	return(DBC_MSSQL_FMT_SQLMONEY(1, data_ptr, 0, 0, 0, 4, out_string));
}
/*	***********************************************************************	*/

char *DBC_MSSQL_FMT_SQLMONEY4_SQL(data_ptr, out_string)
const void *data_ptr;
char       *out_string;
{
	return(DBC_MSSQL_FMT_SQLMONEY4(1, data_ptr, 0, 0, 0, 4, out_string));
}
/*	***********************************************************************	*/

char *DBC_MSSQL_FMT_SQLDATETIME_SQL(data_ptr, out_string)
const void *data_ptr;
char       *out_string;
{
	DTIME tmp_dtime;

	return(DTIME_FormatDate(DBC_MSSQL_MSSQL8ToDTIME(((DBDATETIME *) data_ptr),
		&tmp_dtime), DATFUNCS_DEFAULT_DTIME_FORMAT, out_string));
}
/*	***********************************************************************	*/

char *DBC_MSSQL_FMT_SQLDATETIME4_SQL(data_ptr, out_string)
const void *data_ptr;
char       *out_string;
{
	DTIME tmp_dtime;

	return(DTIME_FormatDate(DBC_MSSQL_MSSQL4ToDTIME(((DBDATETIM4 *) data_ptr),
		&tmp_dtime), DATFUNCS_DEFAULT_DTIME_FORMAT, out_string));
}
/*	***********************************************************************	*/

