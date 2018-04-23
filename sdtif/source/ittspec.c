/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	System Date/Time Interface Facility (SDTIF) Module Source File				*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Support for the calculation of the interval between
								two 'struct timespec' structures.

	Revision History	:	1994-05-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* Include necessary header files . . .												*/
/*	***********************************************************************	*/

#include <math.h>

#include "sdtifi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME        :  SDTIF_GetInterval_timespec

	SYNOPSIS    :  interval_ptr = SDTIF_GetInterval_timespec(start_ptr,
							end_ptr, out_interval_ptr);

						struct timespec       *interval_ptr;

						const struct timespec *start_ptr;

						const struct timespec *end_ptr;

						struct timespec       *out_interval_ptr;

	DESCRIPTION :  Computes the interval between the times represented by the
						values in two structures of type ''timespec''.

	PARAMETERS  :  Parameters to this function are as follow:

						(.)``start_ptr`` points to the start time for which the
						interval is to be computed.

						(.)``end_ptr`` points to the end time for which the
						interval is to be computed.

						(-) If ``end_ptr`` is ''NULL'', the current time is used.

						(.)``out_interval_ptr`` points to the structure of type
						''timespec'' into which is to be placed the interval
						computed by this function.

	RETURNS     :  A pointer to the interval computed.

	SEE ALSO    :  SDTIF_GetInterval_timeval
						SDTIF_GetABSInterval_timespec
						SDTIF_GetPerInterval_timespec
						SDTIF_AddInterval_timespec

	AUTHOR      :  Michael L. Brock

	COPYRIGHT   :  Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	SDTIF_GetInterval_timespec
						Date/Time Functions:SDTIF_GetInterval_timespec
						SDTIF:Functions:SDTIF_GetInterval_timespec
						SDTIF:Date/Time Functions:SDTIF_GetInterval_timespec
						System Date/Time Interface Facility Functions:See SDTIF

	PUBLISH XREF:	SDTIF_GetInterval_timespec

	PUBLISH NAME:	SDTIF_GetInterval_timespec

	ENTRY CLASS	:	Date/Time Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
struct timespec *SDTIF_GetInterval_timespec(const struct timespec *start_ptr,
	const struct timespec *end_ptr, struct timespec *out_interval_ptr)
#else
struct timespec *SDTIF_GetInterval_timespec(start_ptr, end_ptr,
	out_interval_ptr)
const struct timespec *start_ptr;
const struct timespec *end_ptr;
struct timespec       *out_interval_ptr;
#endif /* #ifndef NARGS */
{
	struct timespec tmp_end_time;
	double         tmp_double;

	if (end_ptr == NULL) {
		SDTIF_GetTimeNSecs(&tmp_end_time);
		end_ptr = ((const struct timespec *) &tmp_end_time);
	}

	tmp_double                = SDTIF_GET_TIMESPEC_NSECS_DOUBLE(end_ptr) -
		SDTIF_GET_TIMESPEC_NSECS_DOUBLE(start_ptr);
	out_interval_ptr->tv_sec  = ((long) (tmp_double / 1000000000.0));
	out_interval_ptr->tv_nsec = ((long) fmod(tmp_double, 1000000000.0));

	return(out_interval_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME        :  SDTIF_GetABSInterval_timespec

	SYNOPSIS    :  interval_ptr = SDTIF_GetABSInterval_timespec(start_ptr,
							end_ptr, out_interval_ptr);

						struct timespec       *interval_ptr;

						const struct timespec *start_ptr;

						const struct timespec *end_ptr;

						struct timespec       *out_interval_ptr;

	DESCRIPTION :  Computes the absolute interval between the times
						represented by the values in two structures of type
						''timespec''.

	PARAMETERS  :  Parameters to this function are as follow:

						(.)``start_ptr`` points to the start time for which the
						interval is to be computed.

						(.)``end_ptr`` points to the end time for which the
						interval is to be computed.

						(-) If ``end_ptr`` is ''NULL'', the current time is used.

						(.)``out_interval_ptr`` points to the structure of type
						''timespec'' into which is to be placed the interval
						computed by this function.

	RETURNS     :  A pointer to the interval computed.

	NOTES       :  The absolute interval is computed by comparing the times
						represented by ``start_ptr`` and ``end_ptr`` and calling
						the function ``SDTIF_GetInterval_timespec`` with the two
						parameters in chronological order.

	SEE ALSO    :  SDTIF_GetABSInterval_timeval
						SDTIF_GetInterval_timespec
						SDTIF_GetPerInterval_timespec
						SDTIF_AddInterval_timespec

	AUTHOR      :  Michael L. Brock

	COPYRIGHT   :  Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	SDTIF_GetABSInterval_timespec
						Date/Time Functions:SDTIF_GetABSInterval_timespec
						SDTIF:Functions:SDTIF_GetABSInterval_timespec
						SDTIF:Date/Time Functions:SDTIF_GetABSInterval_timespec
						System Date/Time Interface Facility Functions:See SDTIF

	PUBLISH XREF:	SDTIF_GetABSInterval_timespec

	PUBLISH NAME:	SDTIF_GetABSInterval_timespec

	ENTRY CLASS	:	Date/Time Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
struct timespec *SDTIF_GetABSInterval_timespec(const struct timespec *start_ptr,
	const struct timespec *end_ptr, struct timespec *out_interval_ptr)
#else
struct timespec *SDTIF_GetABSInterval_timespec(start_ptr, end_ptr,
	out_interval_ptr)
const struct timespec *start_ptr;
const struct timespec *end_ptr;
struct timespec       *out_interval_ptr;
#endif /* #ifndef NARGS */
{
	struct timespec tmp_end_time;

	if (end_ptr == NULL) {
		SDTIF_GetTimeNSecs(&tmp_end_time);
		end_ptr = ((struct timespec *) &tmp_end_time);
	}

	return((SDTIF_COMPARE_TIMESPEC(start_ptr, end_ptr) > 0) ?
		SDTIF_GetInterval_timespec(end_ptr, start_ptr, out_interval_ptr) :
		SDTIF_GetInterval_timespec(start_ptr, end_ptr, out_interval_ptr));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME        :  SDTIF_GetPerInterval_timespec

	SYNOPSIS    :  interval_ptr = SDTIF_GetPerInterval_timespec(in_interval_ptr,
							item_count, out_interval_ptr);

						struct timespec        interval_ptr;

						const struct timespec *in_interval_ptr;

						unsigned long         item_count;

						struct timespec       *out_interval_ptr;

	DESCRIPTION :  Calculates the ``per-item`` interval. It does this by
						performing the following logical computation:

						(-) ''in_interval_ptr / item_count''

	PARAMETERS  :  Parameters to this function are as follow:

						(.)``in_interval_ptr`` the total time interval taken to
						process the number of items specified by the ``item_count``
						parameter.

						(.)``item_count`` the number of items processed within the
						time interval specified by the ``in_interval_ptr``
						parameter.

						(.)``out_interval_ptr`` points to the structure of type
						''timespec'' into which is to be placed the ``per-item``
						interval computed by this function.

	RETURNS     :  A pointer to the interval computed.

	NOTES       :  If the ``item_count`` parameter is equal to ''0'', the
						calculation will proceed as if it were ''1''.

	SEE ALSO    :  SDTIF_GetPerInterval_timeval
						SDTIF_GetInterval_timespec
						SDTIF_GetABSInterval_timespec
						SDTIF_AddInterval_timespec

	AUTHOR      :  Michael L. Brock

	COPYRIGHT   :  Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	SDTIF_GetPerInterval_timespec
						Date/Time Functions:SDTIF_GetPerInterval_timespec
						SDTIF:Functions:SDTIF_GetPerInterval_timespec
						SDTIF:Date/Time Functions:SDTIF_GetPerInterval_timespec
						System Date/Time Interface Facility Functions:See SDTIF

	PUBLISH XREF:	SDTIF_GetPerInterval_timespec

	PUBLISH NAME:	SDTIF_GetPerInterval_timespec

	ENTRY CLASS	:	Date/Time Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
struct timespec *SDTIF_GetPerInterval_timespec(
	const struct timespec *in_interval_ptr, unsigned long item_count,
	struct timespec *out_interval_ptr)
#else
struct timespec *SDTIF_GetPerInterval_timespec(in_interval_ptr, item_count,
	out_interval_ptr)
const struct timespec *in_interval_ptr;
unsigned long         item_count;
struct timespec       *out_interval_ptr;
#endif /* #ifndef NARGS */
{
	double tmp_double;

	if (!item_count)
		*out_interval_ptr = *in_interval_ptr;
	else {
		tmp_double                =
			SDTIF_GET_TIMESPEC_NSECS_DOUBLE(in_interval_ptr) /
			((double) item_count);
		out_interval_ptr->tv_sec  = ((long) (tmp_double / 1000000000.0));
		out_interval_ptr->tv_nsec = ((long) fmod(tmp_double, 1000000000.0));
	}

	return(out_interval_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME        :  SDTIF_AddInterval_timespec

	SYNOPSIS    :  interval_ptr = SDTIF_AddInterval_timespec(time_ptr_1,
							time_ptr_2, out_interval_ptr);

						struct timespec       *interval_ptr;

						const struct timespec *time_ptr_1;

						const struct timespec *time_ptr_2;

						struct timespec       *out_interval_ptr;

	DESCRIPTION :  Adds the two times in the structures of type ''timespec''
						to which the parameters ``time_ptr_1`` and ``time_ptr_2``
						point.

	PARAMETERS  :  Parameters to this function are as follow:

						(.)``time_ptr_1`` is the first of the two times to be added.

						(.)``time_ptr_2`` is the second of the two times to be
						added.

						(.)``out_interval_ptr`` points to the structure of type
						''timespec'' into which is to be placed the interval
						resulting from adding ``time_ptr_1`` and ``time_ptr_2``.

	RETURNS     :  A pointer to the interval computed.

	SEE ALSO    :  SDTIF_AddInterval_timeval
						SDTIF_GetInterval_timespec
						SDTIF_GetABSInterval_timespec
						SDTIF_GetPerInterval_timespec

	AUTHOR      :  Michael L. Brock

	COPYRIGHT   :  Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	SDTIF_AddInterval_timespec
						Date/Time Functions:SDTIF_AddInterval_timespec
						SDTIF:Functions:SDTIF_AddInterval_timespec
						SDTIF:Date/Time Functions:SDTIF_AddInterval_timespec
						System Date/Time Interface Facility Functions:See SDTIF

	PUBLISH XREF:	SDTIF_AddInterval_timespec

	PUBLISH NAME:	SDTIF_AddInterval_timespec

	ENTRY CLASS	:	Date/Time Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
struct timespec *SDTIF_AddInterval_timespec(const struct timespec *time_ptr_1,
	const struct timespec *time_ptr_2, struct timespec *out_interval_ptr)
#else
struct timespec *SDTIF_AddInterval_timespec(time_ptr_1, time_ptr_2,
	out_interval_ptr)
const struct timespec *time_ptr_1;
const struct timespec *time_ptr_2;
struct timespec       *out_interval_ptr;
#endif /* #ifndef NARGS */
{
	double tmp_double;

	tmp_double                = SDTIF_GET_TIMESPEC_NSECS_DOUBLE(time_ptr_1) +
		SDTIF_GET_TIMESPEC_NSECS_DOUBLE(time_ptr_2);
	out_interval_ptr->tv_sec  = ((long) (tmp_double / 1000000000.0));
	out_interval_ptr->tv_nsec = ((long) fmod(tmp_double, 1000000000.0));

	return(out_interval_ptr);
}
/*	***********************************************************************	*/

