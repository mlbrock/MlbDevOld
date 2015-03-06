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
								two 'struct timeval' structures.

	Revision History	:	1994-05-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2015.
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

	NAME        :  SDTIF_GetInterval_timeval

	SYNOPSIS    :  interval_ptr = SDTIF_GetInterval_timeval(start_ptr,
							end_ptr, out_interval_ptr);

						struct timeval       *interval_ptr;

						const struct timeval *start_ptr;

						const struct timeval *end_ptr;

						struct timeval       *out_interval_ptr;

	DESCRIPTION :  Computes the interval between the times represented by the
						values in two structures of type ''timeval''.

	PARAMETERS  :  Parameters to this function are as follow:

						(.)``start_ptr`` points to the start time for which the
						interval is to be computed.

						(.)``end_ptr`` points to the end time for which the
						interval is to be computed.

						(-) If ``end_ptr`` is ''NULL'', the current time is used.

						(.)``out_interval_ptr`` points to the structure of type
						''timeval'' into which is to be placed the interval
						computed by this function.

	RETURNS     :  A pointer to the interval computed.

	SEE ALSO    :  SDTIF_GetInterval_timespec
						SDTIF_GetABSInterval_timeval
						SDTIF_GetPerInterval_timeval
						SDTIF_AddInterval_timeval

	AUTHOR      :  Michael L. Brock

	COPYRIGHT   :  Copyright 1994 - 2015 Michael L. Brock

	OUTPUT INDEX:	SDTIF_GetInterval_timeval
						Date/Time Functions:SDTIF_GetInterval_timeval
						SDTIF:Functions:SDTIF_GetInterval_timeval
						SDTIF:Date/Time Functions:SDTIF_GetInterval_timeval
						System Date/Time Interface Facility Functions:See SDTIF

	PUBLISH XREF:	SDTIF_GetInterval_timeval

	PUBLISH NAME:	SDTIF_GetInterval_timeval

	ENTRY CLASS	:	Date/Time Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
struct timeval *SDTIF_GetInterval_timeval(const struct timeval *start_ptr,
	const struct timeval *end_ptr, struct timeval *out_interval_ptr)
#else
struct timeval *SDTIF_GetInterval_timeval(start_ptr, end_ptr,
	out_interval_ptr)
const struct timeval *start_ptr;
const struct timeval *end_ptr;
struct timeval       *out_interval_ptr;
#endif /* #ifndef NARGS */
{
	struct timeval tmp_end_time;
	double         tmp_double;

	if (end_ptr == NULL) {
		SDTIF_GetTimeUSecs(&tmp_end_time);
		end_ptr = ((const struct timeval *) &tmp_end_time);
	}

	tmp_double                = SDTIF_GET_TIMEVAL_USECS_DOUBLE(end_ptr) -
		SDTIF_GET_TIMEVAL_USECS_DOUBLE(start_ptr);
	out_interval_ptr->tv_sec  = ((long) (tmp_double / 1000000.0));
	out_interval_ptr->tv_usec = ((long) fmod(tmp_double, 1000000.0));

	return(out_interval_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME        :  SDTIF_GetABSInterval_timeval

	SYNOPSIS    :  interval_ptr = SDTIF_GetABSInterval_timeval(start_ptr,
							end_ptr, out_interval_ptr);

						struct timeval       *interval_ptr;

						const struct timeval *start_ptr;

						const struct timeval *end_ptr;

						struct timeval       *out_interval_ptr;

	DESCRIPTION :  Computes the absolute interval between the times
						represented by the values in two structures of type
						''timeval''.

	PARAMETERS  :  Parameters to this function are as follow:

						(.)``start_ptr`` points to the start time for which the
						interval is to be computed.

						(.)``end_ptr`` points to the end time for which the
						interval is to be computed.

						(-) If ``end_ptr`` is ''NULL'', the current time is used.

						(.)``out_interval_ptr`` points to the structure of type
						''timeval'' into which is to be placed the interval
						computed by this function.

	RETURNS     :  A pointer to the interval computed.

	NOTES       :  The absolute interval is computed by comparing the times
						represented by ``start_ptr`` and ``end_ptr`` and calling
						the function ``SDTIF_GetInterval_timeval`` with the two
						parameters in chronological order.

	SEE ALSO    :  SDTIF_GetABSInterval_timespec
						SDTIF_GetInterval_timeval
						SDTIF_GetPerInterval_timeval
						SDTIF_AddInterval_timeval

	AUTHOR      :  Michael L. Brock

	COPYRIGHT   :  Copyright 1994 - 2015 Michael L. Brock

	OUTPUT INDEX:	SDTIF_GetABSInterval_timeval
						Date/Time Functions:SDTIF_GetABSInterval_timeval
						SDTIF:Functions:SDTIF_GetABSInterval_timeval
						SDTIF:Date/Time Functions:SDTIF_GetABSInterval_timeval
						System Date/Time Interface Facility Functions:See SDTIF

	PUBLISH XREF:	SDTIF_GetABSInterval_timeval

	PUBLISH NAME:	SDTIF_GetABSInterval_timeval

	ENTRY CLASS	:	Date/Time Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
struct timeval *SDTIF_GetABSInterval_timeval(const struct timeval *start_ptr,
	const struct timeval *end_ptr, struct timeval *out_interval_ptr)
#else
struct timeval *SDTIF_GetABSInterval_timeval(start_ptr, end_ptr,
	out_interval_ptr)
const struct timeval *start_ptr;
const struct timeval *end_ptr;
struct timeval       *out_interval_ptr;
#endif /* #ifndef NARGS */
{
	struct timeval tmp_end_time;

	if (end_ptr == NULL) {
		SDTIF_GetTimeUSecs(&tmp_end_time);
		end_ptr = ((struct timeval *) &tmp_end_time);
	}

	return((SDTIF_COMPARE_TIMEVAL(start_ptr, end_ptr) > 0) ?
		SDTIF_GetInterval_timeval(end_ptr, start_ptr, out_interval_ptr) :
		SDTIF_GetInterval_timeval(start_ptr, end_ptr, out_interval_ptr));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME        :  SDTIF_GetPerInterval_timeval

	SYNOPSIS    :  interval_ptr = SDTIF_GetPerInterval_timeval(in_interval_ptr,
							item_count, out_interval_ptr);

						struct timeval        interval_ptr;

						const struct timeval *in_interval_ptr;

						unsigned long         item_count;

						struct timeval       *out_interval_ptr;

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
						''timeval'' into which is to be placed the ``per-item``
						interval computed by this function.

	RETURNS     :  A pointer to the interval computed.

	NOTES       :  If the ``item_count`` parameter is equal to ''0'', the
						calculation will proceed as if it were ''1''.

	SEE ALSO    :  SDTIF_GetPerInterval_timespec
						SDTIF_GetInterval_timeval
						SDTIF_GetABSInterval_timeval
						SDTIF_AddInterval_timeval

	AUTHOR      :  Michael L. Brock

	COPYRIGHT   :  Copyright 1994 - 2015 Michael L. Brock

	OUTPUT INDEX:	SDTIF_GetPerInterval_timeval
						Date/Time Functions:SDTIF_GetPerInterval_timeval
						SDTIF:Functions:SDTIF_GetPerInterval_timeval
						SDTIF:Date/Time Functions:SDTIF_GetPerInterval_timeval
						System Date/Time Interface Facility Functions:See SDTIF

	PUBLISH XREF:	SDTIF_GetPerInterval_timeval

	PUBLISH NAME:	SDTIF_GetPerInterval_timeval

	ENTRY CLASS	:	Date/Time Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
struct timeval *SDTIF_GetPerInterval_timeval(
	const struct timeval *in_interval_ptr, unsigned long item_count,
	struct timeval *out_interval_ptr)
#else
struct timeval *SDTIF_GetPerInterval_timeval(in_interval_ptr, item_count,
	out_interval_ptr)
const struct timeval *in_interval_ptr;
unsigned long         item_count;
struct timeval       *out_interval_ptr;
#endif /* #ifndef NARGS */
{
	double tmp_double;

	if (!item_count)
		*out_interval_ptr = *in_interval_ptr;
	else {
		tmp_double                =
			SDTIF_GET_TIMEVAL_USECS_DOUBLE(in_interval_ptr) /
			((double) item_count);
		out_interval_ptr->tv_sec  = ((long) (tmp_double / 1000000.0));
		out_interval_ptr->tv_usec = ((long) fmod(tmp_double, 1000000.0));
	}

	return(out_interval_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME        :  SDTIF_AddInterval_timeval

	SYNOPSIS    :  interval_ptr = SDTIF_AddInterval_timeval(time_ptr_1,
							time_ptr_2, out_interval_ptr);

						struct timeval       *interval_ptr;

						const struct timeval *time_ptr_1;

						const struct timeval *time_ptr_2;

						struct timeval       *out_interval_ptr;

	DESCRIPTION :  Adds the two times in the structures of type ''timeval''
						to which the parameters ``time_ptr_1`` and ``time_ptr_2``
						point.

	PARAMETERS  :  Parameters to this function are as follow:

						(.)``time_ptr_1`` is the first of the two times to be added.

						(.)``time_ptr_2`` is the second of the two times to be
						added.

						(.)``out_interval_ptr`` points to the structure of type
						''timeval'' into which is to be placed the interval
						resulting from adding ``time_ptr_1`` and ``time_ptr_2``.

	RETURNS     :  A pointer to the interval computed.

	SEE ALSO    :  SDTIF_AddInterval_timespec
						SDTIF_GetInterval_timeval
						SDTIF_GetABSInterval_timeval
						SDTIF_GetPerInterval_timeval

	AUTHOR      :  Michael L. Brock

	COPYRIGHT   :  Copyright 1994 - 2015 Michael L. Brock

	OUTPUT INDEX:	SDTIF_AddInterval_timeval
						Date/Time Functions:SDTIF_AddInterval_timeval
						SDTIF:Functions:SDTIF_AddInterval_timeval
						SDTIF:Date/Time Functions:SDTIF_AddInterval_timeval
						System Date/Time Interface Facility Functions:See SDTIF

	PUBLISH XREF:	SDTIF_AddInterval_timeval

	PUBLISH NAME:	SDTIF_AddInterval_timeval

	ENTRY CLASS	:	Date/Time Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
struct timeval *SDTIF_AddInterval_timeval(const struct timeval *time_ptr_1,
	const struct timeval *time_ptr_2, struct timeval *out_interval_ptr)
#else
struct timeval *SDTIF_AddInterval_timeval(time_ptr_1, time_ptr_2,
	out_interval_ptr)
const struct timeval *time_ptr_1;
const struct timeval *time_ptr_2;
struct timeval       *out_interval_ptr;
#endif /* #ifndef NARGS */
{
	double tmp_double;

	tmp_double                = SDTIF_GET_TIMEVAL_USECS_DOUBLE(time_ptr_1) +
		SDTIF_GET_TIMEVAL_USECS_DOUBLE(time_ptr_2);
	out_interval_ptr->tv_sec  = ((long) (tmp_double / 1000000.0));
	out_interval_ptr->tv_usec = ((long) fmod(tmp_double, 1000000.0));

	return(out_interval_ptr);
}
/*	***********************************************************************	*/

