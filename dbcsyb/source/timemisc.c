/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Generic Sybase Support Functions Library Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Miscellaneous Sybase time type functions.

	Revision History	:	1993-08-13 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#include <stdio.h>

#include "dbcsybi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int DBC_SYB_IsTime(int dbc_type)
#else
int DBC_SYB_IsTime(dbc_type)
int dbc_type;
#endif /* #ifndef NARGS */
{
	return(((dbc_type == SYBDATETIME4) || (dbc_type == SYBDATETIME)) ?
		DBC_TRUE : DBC_FALSE);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int DBC_SYB_MinTime(int dbc_type, DTIME *dtime_ptr, char *error_text)
#else
int DBC_SYB_MinTime(dbc_type, dtime_ptr, error_text)
int    dbc_type;
DTIME *dtime_ptr;
char  *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code = DBC_SUCCESS;
	char dat_error_text[DATFUNCS_MAX_ERROR_TEXT];

	switch (dbc_type) {
		case SYBDATETIME4	:
			if ((return_code = DTIME_YYYYMMDDhhmmsslllToDate(1900, 1, 1, 0, 0, 0,
				0, dtime_ptr, dat_error_text)) != DATFUNCS_SUCCESS) {
				nstrcpy(error_text, dat_error_text, DBC_MAX_ERROR_TEXT - 1);
				return_code = DBC_MAP_ERROR_DAT_TO_DBC(return_code);
			}
			break;
		case SYBDATETIME	:
			if ((return_code = DTIME_YYYYMMDDhhmmsslllToDate(1753, 1, 1, 0, 0, 0,
				0, dtime_ptr, dat_error_text)) != DATFUNCS_SUCCESS) {
				nstrcpy(error_text, dat_error_text, DBC_MAX_ERROR_TEXT - 1);
				return_code = DBC_MAP_ERROR_DAT_TO_DBC(return_code);
			}
			break;
		default				:
			sprintf(error_text, "Invalid DBC type (%d) %s.", dbc_type,
				"was passed to the DBC time 'minimum' function");
			return_code = DBC_BAD_TYPE_FAILURE;
			break;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int DBC_SYB_MaxTime(int dbc_type, DTIME *dtime_ptr, char *error_text)
#else
int DBC_SYB_MaxTime(dbc_type, dtime_ptr, error_text)
int    dbc_type;
DTIME *dtime_ptr;
char  *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code = DBC_SUCCESS;
	char dat_error_text[DATFUNCS_MAX_ERROR_TEXT];

	switch (dbc_type) {
		case SYBDATETIME4	:
			if ((return_code = DTIME_YYYYMMDDhhmmsslllToDate(2079, 6, 6, 23,
				59, 59, 999, dtime_ptr, dat_error_text)) != DATFUNCS_SUCCESS) {
				nstrcpy(error_text, dat_error_text, DBC_MAX_ERROR_TEXT - 1);
				return_code = DBC_MAP_ERROR_DAT_TO_DBC(return_code);
			}
			break;
		case SYBDATETIME	:
			if ((return_code = DTIME_YYYYMMDDhhmmsslllToDate(9999, 12, 31, 23,
				59, 59, 999, dtime_ptr, dat_error_text)) != DATFUNCS_SUCCESS) {
				nstrcpy(error_text, dat_error_text, DBC_MAX_ERROR_TEXT - 1);
				return_code = DBC_MAP_ERROR_DAT_TO_DBC(return_code);
			}
			break;
		default				:
			sprintf(error_text, "Invalid DBC type (%d) %s.", dbc_type,
				"was passed to the DBC time 'maximum' function");
			return_code = DBC_BAD_TYPE_FAILURE;
			break;
	}

	return(return_code);
}
/*	***********************************************************************	*/

