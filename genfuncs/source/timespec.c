/* *********************************************************************** */
/* *********************************************************************** */
/*	GENFUNCS General Functions Library Source Module								*/
/* *********************************************************************** */
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
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Include necessary header files . . .											*/
/* *********************************************************************** */

#include <math.h>

#include "genfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_GetInterval_timespec

   SYNOPSIS    :  interval_ptr = GEN_GetInterval_timespec(start_ptr, end_ptr,
							out_interval_ptr);

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

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  GEN_GetInterval_timeval
						GEN_GetABSInterval_timespec
						GEN_GetPerInterval_timespec
						GEN_AddInterval_timespec

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1994 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_GetInterval_timespec
						Date/Time Functions:GEN_GetInterval_timespec
						GENFUNCS:Functions:GEN_GetInterval_timespec
						GENFUNCS:Date/Time Functions:GEN_GetInterval_timespec
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_GetInterval_timespec

   PUBLISH NAME:	GEN_GetInterval_timespec

	ENTRY CLASS	:	Date/Time Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
struct timespec *GEN_GetInterval_timespec(const struct timespec *start_ptr,
	const struct timespec *end_ptr, struct timespec *out_interval_ptr)
#else
struct timespec *GEN_GetInterval_timespec(start_ptr, end_ptr, out_interval_ptr)
const struct timespec *start_ptr;
const struct timespec *end_ptr;
struct timespec       *out_interval_ptr;
#endif /* #ifndef NARGS */
{
	struct timespec tmp_end_time;
	double         tmp_double;

	if (end_ptr == NULL) {
		GEN_GetTimeNSecs(&tmp_end_time);
		end_ptr = ((const struct timespec *) &tmp_end_time);
	}

	tmp_double                = GEN_GET_TIMESPEC_NSECS_DOUBLE(end_ptr) -
		GEN_GET_TIMESPEC_NSECS_DOUBLE(start_ptr);
	out_interval_ptr->tv_sec  = ((long) (tmp_double / 1000000000.0));
	out_interval_ptr->tv_nsec = ((long) fmod(tmp_double, 1000000000.0));

	return(out_interval_ptr);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_GetABSInterval_timespec

   SYNOPSIS    :  interval_ptr = GEN_GetABSInterval_timespec(start_ptr,
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
						the function ``GEN_GetInterval_timespec`` with the two
						parameters in chronological order.

   CAVEATS     :  

   SEE ALSO    :  GEN_GetABSInterval_timeval
						GEN_GetInterval_timespec
						GEN_GetPerInterval_timespec
						GEN_AddInterval_timespec

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1994 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_GetABSInterval_timespec
						Date/Time Functions:GEN_GetABSInterval_timespec
						GENFUNCS:Functions:GEN_GetABSInterval_timespec
						GENFUNCS:Date/Time Functions:GEN_GetABSInterval_timespec
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_GetABSInterval_timespec

   PUBLISH NAME:	GEN_GetABSInterval_timespec

	ENTRY CLASS	:	Date/Time Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
struct timespec *GEN_GetABSInterval_timespec(const struct timespec *start_ptr,
	const struct timespec *end_ptr, struct timespec *out_interval_ptr)
#else
struct timespec *GEN_GetABSInterval_timespec(start_ptr, end_ptr,
	out_interval_ptr)
const struct timespec *start_ptr;
const struct timespec *end_ptr;
struct timespec       *out_interval_ptr;
#endif /* #ifndef NARGS */
{
	struct timespec tmp_end_time;

	if (end_ptr == NULL) {
		GEN_GetTimeNSecs(&tmp_end_time);
		end_ptr = ((struct timespec *) &tmp_end_time);
	}

	return((GEN_COMPARE_TIMESPEC(start_ptr, end_ptr) > 0) ?
		GEN_GetInterval_timespec(end_ptr, start_ptr, out_interval_ptr) :
		GEN_GetInterval_timespec(start_ptr, end_ptr, out_interval_ptr));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_GetPerInterval_timespec

   SYNOPSIS    :  interval_ptr = GEN_GetPerInterval_timespec(in_interval_ptr,
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

   CAVEATS     :  

   SEE ALSO    :  GEN_GetPerInterval_timeval
						GEN_GetInterval_timespec
						GEN_GetABSInterval_timespec
						GEN_AddInterval_timespec

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1994 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_GetPerInterval_timespec
						Date/Time Functions:GEN_GetPerInterval_timespec
						GENFUNCS:Functions:GEN_GetPerInterval_timespec
						GENFUNCS:Date/Time Functions:GEN_GetPerInterval_timespec
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_GetPerInterval_timespec

   PUBLISH NAME:	GEN_GetPerInterval_timespec

	ENTRY CLASS	:	Date/Time Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
struct timespec *GEN_GetPerInterval_timespec(
	const struct timespec *in_interval_ptr, unsigned long item_count,
	struct timespec *out_interval_ptr)
#else
struct timespec *GEN_GetPerInterval_timespec(in_interval_ptr, item_count,
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
			GEN_GET_TIMESPEC_NSECS_DOUBLE(in_interval_ptr) /
			((double) item_count);
		out_interval_ptr->tv_sec  = ((long) (tmp_double / 1000000000.0));
		out_interval_ptr->tv_nsec = ((long) fmod(tmp_double, 1000000000.0));
	}

	return(out_interval_ptr);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_AddInterval_timespec

   SYNOPSIS    :  interval_ptr = GEN_AddInterval_timespec(time_ptr_1,
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

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  GEN_AddInterval_timeval
						GEN_GetInterval_timespec
						GEN_GetABSInterval_timespec
						GEN_GetPerInterval_timespec

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1994 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_AddInterval_timespec
						Date/Time Functions:GEN_AddInterval_timespec
						GENFUNCS:Functions:GEN_AddInterval_timespec
						GENFUNCS:Date/Time Functions:GEN_AddInterval_timespec
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_AddInterval_timespec

   PUBLISH NAME:	GEN_AddInterval_timespec

	ENTRY CLASS	:	Date/Time Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
struct timespec *GEN_AddInterval_timespec(const struct timespec *time_ptr_1,
	const struct timespec *time_ptr_2, struct timespec *out_interval_ptr)
#else
struct timespec *GEN_AddInterval_timespec(time_ptr_1, time_ptr_2,
	out_interval_ptr)
const struct timespec *time_ptr_1;
const struct timespec *time_ptr_2;
struct timespec       *out_interval_ptr;
#endif /* #ifndef NARGS */
{
	double tmp_double;

	tmp_double                = GEN_GET_TIMESPEC_NSECS_DOUBLE(time_ptr_1) +
		GEN_GET_TIMESPEC_NSECS_DOUBLE(time_ptr_2);
	out_interval_ptr->tv_sec  = ((long) (tmp_double / 1000000000.0));
	out_interval_ptr->tv_nsec = ((long) fmod(tmp_double, 1000000000.0));

	return(out_interval_ptr);
}
/* *********************************************************************** */

