/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	System Date/Time Interface Facility (SDTIF) Module Source File				*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Compare two 'struct timespec' values.

	Revision History	:	1995-11-10 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* Include necessary header files . . .												*/
/*	***********************************************************************	*/

#include "sdtifi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	SDTIF_Compare_timespec

	SYNOPSIS		:	comparison_code = SDTIF_Compare_timespec(time_ptr_1,
							time_ptr_2);

						int                    comparison_code;

						const struct timespec *time_ptr_1;

						const struct timespec *time_ptr_2;

	DESCRIPTION :  Compares the two date/times (to which the parameters
						``time_ptr_1`` and ``time_ptr_2`` point) for
						equality.

	PARAMETERS  :  Parameters to this function are as follow:

						(.) ``time_ptr_1`` points to the first of the ``struct
						timespec`` structures to be compared.

						(.) ``time_ptr_2`` points to the second of the ``struct
						timespec`` structures to be compared.

	RETURNS     :  Returns from this function are as follow:

						(.) negative if the first time is less than second.

						(.) positive if the first time is greater than second.

						(.) zero if the times are equal.

	SEE ALSO		:	SDTIF_Compare_timeval
						SDTIF_Compare_time_t
						SDTIF_Compare_tm
						SDTIF_Compare_ulong
						SDTIF_SCompare_timespec

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2015 Michael L. Brock

	OUTPUT INDEX:	SDTIF_Compare_timespec
						Date/Time Functions:SDTIF_Compare_timespec
						SDTIF:Functions:SDTIF_Compare_timespec
						SDTIF:Date/Time Functions:SDTIF_Compare_timespec
						System Date/Time Interface Facility Functions:See SDTIF

	PUBLISH XREF:	SDTIF_Compare_timespec

	PUBLISH NAME:	SDTIF_Compare_timespec

	ENTRY CLASS	:	Date/Time Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int SDTIF_Compare_timespec(const struct timespec *time_ptr_1,
	const struct timespec *time_ptr_2)
#else
int SDTIF_Compare_timespec(time_ptr_1, time_ptr_2)
const struct timespec *time_ptr_1;
const struct timespec *time_ptr_2;
#endif /* #ifndef NARGS */
{
	return(SDTIF_COMPARE_TIMESPEC(time_ptr_1, time_ptr_2));
}
/*	***********************************************************************	*/

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	SDTIF_SCompare_timespec

	SYNOPSIS		:	comparison_code = SDTIF_SCompare_timespec(control_ptr,
							time_ptr_1, time_ptr_2, data_length);

						int                    comparison_code;

						void                  *control_ptr;

						const struct timespec *time_ptr_1;

						const struct timespec *time_ptr_2;

						size_t                 data_length;

	DESCRIPTION :  Compares the two date/times (to which the parameters
						``time_ptr_1`` and ``time_ptr_2`` point) for
						equality.

	PARAMETERS  :  Parameters to this function are as follow:

						(.) ``control_ptr`` points to a arbitrary user-defined
						structure which may be used to modify the comparison
						If unnecessary, it may be a NULL pointer.

						(.) ``time_ptr_1`` points to the first of the ``struct
						timespec`` structures to be compared.

						(.) ``time_ptr_2`` points to the second of the ``struct
						timespec`` structures to be compared.

						(.) ``data_length`` is the size the areas to which each
						strings point. If unnecessary, it may be zero (0).

	RETURNS     :  Returns from this function are as follow:

						(.) negative if the first time is less than second.

						(.) positive if the first time is greater than second.

						(.) zero if the times are equal.

	NOTES			:	The ``control_ptr`` and ``data_length`` parameters are
						present only because this function is used internally
						by other STRFUNCS list functions. They provide
						function-call compatibility with other, more generic,
						comparison functions.

	SEE ALSO		:	SDTIF_SCompare_timeval
						SDTIF_SCompare_time_t
						SDTIF_SCompare_tm
						SDTIF_SCompare_ulong
						SDTIF_Compare_timespec

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2015 Michael L. Brock

	OUTPUT INDEX:	SDTIF_SCompare_timespec
						Date/Time Functions:SDTIF_SCompare_timespec
						SDTIF:Functions:SDTIF_SCompare_timespec
						SDTIF:Date/Time Functions:SDTIF_SCompare_timespec
						System Date/Time Interface Facility Functions:See SDTIF

	PUBLISH XREF:	SDTIF_SCompare_timespec

	PUBLISH NAME:	SDTIF_SCompare_timespec

	ENTRY CLASS	:	Date/Time Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int SDTIF_SCompare_timespec(void *control_ptr,
	const struct timespec *time_ptr_1, const struct timespec *time_ptr_2,
	size_t data_length)
#else
int SDTIF_SCompare_timespec(control_ptr, time_ptr_1, time_ptr_2, data_length)
void                  *control_ptr;
const struct timespec *time_ptr_1;
const struct timespec *time_ptr_2;
size_t                 data_length;
#endif /* #ifndef NARGS */
{
	return(SDTIF_COMPARE_TIMESPEC(time_ptr_1, time_ptr_2));
}
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

