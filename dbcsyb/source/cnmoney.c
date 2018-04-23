/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Generic Sybase Support Functions Library Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Converts between the Sybase 'money' types and the
								'C' primitive type 'double'.

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
#include <math.h>
#include <stdlib.h>

#include "dbcsybi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
double DBC_SYB_DBMONEYToDouble(const DBMONEY *in_dbmoney)
#else
double DBC_SYB_DBMONEYToDouble(in_dbmoney)
const DBMONEY *in_dbmoney;
#endif /* #ifndef NARGS */
{
	return((((((double) abs(in_dbmoney->mnyhigh)) *
		(((double) ULONG_MAX) + 1.0)) + ((double) in_dbmoney->mnylow)) /
		10000.0) * ((in_dbmoney->mnyhigh < 1) ? -1.0 : 1.0));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
double DBC_SYB_DBMONEY4ToDouble(const DBMONEY4 *in_dbmoney4)
#else
double DBC_SYB_DBMONEY4ToDouble(in_dbmoney4)
const DBMONEY4 *in_dbmoney4;
#endif /* #ifndef NARGS */
{
	return(((double) in_dbmoney4->mny4) / 10000.0);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
DBMONEY *DBC_SYB_DoubleToDBMONEY(double in_double, DBMONEY *out_dbmoney)
#else
DBMONEY *DBC_SYB_DoubleToDBMONEY(in_double, out_dbmoney)
double   in_double;
DBMONEY *out_dbmoney;
#endif /* #ifndef NARGS */
{
	in_double *= 10000.0;

	if ((in_double < (((((double) LONG_MAX) * (((double) ULONG_MAX) + 1.0)) +
		((double) ULONG_MAX)) * -1.0)) ||
		(in_double > ((((double) LONG_MAX) * (((double) ULONG_MAX) + 1.0)) +
		((double) ULONG_MAX))))
		out_dbmoney = NULL;
	else {
		out_dbmoney->mnyhigh = ((long) (fabs(in_double) /
			(((double) ULONG_MAX) + 1.0)));
		out_dbmoney->mnylow  = ((long) fmod(fabs(in_double),
			((double) ULONG_MAX)));
	}

	return(out_dbmoney);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
DBMONEY4 *DBC_SYB_DoubleToDBMONEY4(double in_double, DBMONEY4 *out_dbmoney4)
#else
DBMONEY4 *DBC_SYB_DoubleToDBMONEY4(in_double, out_dbmoney4)
double    in_double;
DBMONEY4 *out_dbmoney4;
#endif /* #ifndef NARGS */
{
	if ((in_double < (((double) LONG_MIN) / 10000.0)) ||
		(in_double > (((double) LONG_MAX) / 10000.0)))
		out_dbmoney4 = NULL;
	else
		out_dbmoney4->mny4 = ((long) (in_double * 10000.0));

	return(out_dbmoney4);
}
/*	***********************************************************************	*/

