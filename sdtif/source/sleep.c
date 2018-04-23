/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	System Date/Time Interface Facility (SDTIF) Module Source File				*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Performs a 'sleep' with various granularities.

	Revision History	:	1986-02-15 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1986 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Required include files . . .														*/
/*	***********************************************************************	*/

#ifdef __MSDOS__
# if __BORLANDC__ || __BCPLUSPLUS
#  include <dos.h>
# endif /* # if __BORLANDC__  || __BCPLUSPLUS */
#else
# if _MSC_VER || _Windows
#  include <errno.h>
# elif __SVR4
#  include <sys/time.h>
# else
#  include <errno.h>
#  include <unistd.h>
# endif /* # if _MSC_VER || _Windows */
#endif /* #ifdef __MSDOS__ */

#include "sdtifi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	SDTIF_sleep

   SYNOPSIS    :	void SDTIF_sleep(seconds);

						unsigned int seconds;

   DESCRIPTION :	Sleeps for a given number of seconds.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``seconds`` is the amount of time to sleep in seconds.

   RETURNS     :	Void.

   CAVEATS     :	The exact quantums for which this function will sleep will,
						of course, vary with the operating system available.

   SEE ALSO    :  SDTIF_msleep
						SDTIF_usleep
						SDTIF_nsleep
						SDTIF_nanosleep

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1986 - 2018 Michael L. Brock

   OUTPUT INDEX:	SDTIF_sleep
						Miscellaneous Functions:SDTIF_sleep
						SDTIF:Functions:SDTIF_sleep
						SDTIF:Miscellaneous Functions:SDTIF_sleep
						System Date/Time Interface Facility Functions:See SDTIF

   PUBLISH XREF:	SDTIF_sleep

   PUBLISH NAME:	SDTIF_sleep

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void SDTIF_sleep(unsigned int seconds)
#else
void SDTIF_sleep(seconds)
unsigned int seconds;
#endif /* #ifndef NARGS */
{
#ifdef _Windows
	Sleep(((unsigned long) seconds) * 1000L);
#else
	SDTIF_usleep(((unsigned long) seconds) * 1000000L);
#endif /* #ifdef _Windows */
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	SDTIF_msleep

   SYNOPSIS    :	void SDTIF_msleep(milliseconds);

						unsigned long milliseconds;

   DESCRIPTION :	Sleeps for a given number of milliseconds.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``milliseconds`` is the amount of time to sleep in
						milliseconds (thousands of a second).

   RETURNS     :	Void.

   CAVEATS     :	The exact quantums for which this function will sleep will,
						of course, vary with the operating system and compiler
						libraries available.

   SEE ALSO    :  SDTIF_sleep
						SDTIF_usleep
						SDTIF_nsleep
						SDTIF_nanosleep

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1986 - 2018 Michael L. Brock

   OUTPUT INDEX:	SDTIF_msleep
						Miscellaneous Functions:SDTIF_msleep
						SDTIF:Functions:SDTIF_msleep
						SDTIF:Miscellaneous Functions:SDTIF_msleep
						System Date/Time Interface Facility Functions:See SDTIF

   PUBLISH XREF:	SDTIF_msleep

   PUBLISH NAME:	SDTIF_msleep

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void SDTIF_msleep(unsigned long milliseconds)
#else
void SDTIF_msleep(milliseconds)
unsigned long milliseconds;
#endif /* #ifndef NARGS */
{
	SDTIF_usleep(milliseconds * 1000L);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	SDTIF_usleep

   SYNOPSIS    :	void SDTIF_usleep(microseconds);

						unsigned long microseconds;

   DESCRIPTION :	Sleeps for a given number of microseconds.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``microseconds`` is the amount of time to sleep in
						microseconds (millionths of a second).

   RETURNS     :	Void.

   CAVEATS     :	The exact quantums for which this function will sleep will,
						of course, vary with the operating system and compiler
						libraries available.

						For example, under the MS-DOS Borland C compiler, the
						sleep quantum is in milliseconds, not microseconds.

   SEE ALSO    :  SDTIF_sleep
						SDTIF_msleep
						SDTIF_nsleep
						SDTIF_nanosleep

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1986 - 2018 Michael L. Brock

   OUTPUT INDEX:	SDTIF_usleep
						Miscellaneous Functions:SDTIF_usleep
						SDTIF:Functions:SDTIF_usleep
						SDTIF:Miscellaneous Functions:SDTIF_usleep
						System Date/Time Interface Facility Functions:See SDTIF

   PUBLISH XREF:	SDTIF_usleep

   PUBLISH NAME:	SDTIF_usleep

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void SDTIF_usleep(unsigned long microseconds)
#else
void SDTIF_usleep(microseconds)
unsigned long microseconds;
#endif /* #ifndef NARGS */
{
#ifdef __MSDOS__
# if __BORLANDC__ || __BCPLUSPLUS
	delay(((unsigned int) (microseconds / 1000L)));
# else
	sleep(((unsigned int) (microseconds / 1000000L)));
# endif /* # if __BORLANDC__  || __BCPLUSPLUS */
#elif _Windows
	Sleep(((DWORD) (microseconds / 1000L)));
#elif _MSC_VER
	Sleep(((DWORD) (microseconds / 1000L)));
#elif __SVR4
/*
	CODE NOTE:	I really should eventually implement code equivalent to BSD
					'usleep()' here.
*/
	struct timeval tmp_timeval;

	tmp_timeval.tv_sec  = ((long) (microseconds / 1000000L));
	tmp_timeval.tv_usec = ((long) (microseconds % 1000000L));

	select(0, NULL, NULL, NULL, &tmp_timeval);
#else
	usleep(microseconds);
#endif /* #ifdef __MSDOS__ */
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	SDTIF_nsleep

   SYNOPSIS    :	void SDTIF_nsleep(nanoseconds);

						unsigned long nanoseconds;

   DESCRIPTION :	Sleeps for a given number of nanoseconds.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``nanoseconds`` is the amount of time to sleep in
						nanoseconds (billionths of a second).

   RETURNS     :	Void.

   CAVEATS     :	The exact quantums for which this function will sleep will,
						of course, vary with the operating system and compiler
						libraries available.

						For example, under the MS-DOS Borland C compiler, the
						sleep quantum is in milliseconds, not nanoseconds.

						Under non-System V SunOS, the sleep quantum is in
						microseconds.

   SEE ALSO    :	SDTIF_sleep
						SDTIF_msleep
						SDTIF_usleep
						SDTIF_nanosleep

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1986 - 2018 Michael L. Brock

   OUTPUT INDEX:	SDTIF_nsleep
						Miscellaneous Functions:SDTIF_nsleep
						SDTIF:Functions:SDTIF_nsleep
						SDTIF:Miscellaneous Functions:SDTIF_nsleep
						System Date/Time Interface Facility Functions:See SDTIF

   PUBLISH XREF:	SDTIF_nsleep

   PUBLISH NAME:	SDTIF_nsleep

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void SDTIF_nsleep(unsigned long nanoseconds)
#else
void SDTIF_nsleep(nanoseconds)
unsigned long nanoseconds;
#endif /* #ifndef NARGS */
{
#ifdef __MSDOS__
# if __BORLANDC__ || __BCPLUSPLUS
	delay(((unsigned int) (nanoseconds / 1000000L)));
# else
	sleep(((unsigned int) (nanoseconds / 1000000000L)));
# endif /* # if __BORLANDC__  || __BCPLUSPLUS */
#elif _Windows
	Sleep(((DWORD) (nanoseconds / 1000000L)));
#elif _MSC_VER
	Sleep(((DWORD) (nanoseconds / 1000000L)));
#elif __SVR4
	struct timespec tmp_timespec;

	tmp_timespec.tv_sec  = ((long) (nanoseconds / 1000000000L));
	tmp_timespec.tv_nsec = ((long) (nanoseconds % 1000000000L));

	nanosleep(&tmp_timespec, NULL);
#else
	usleep(nanoseconds / 1000L);
#endif /* #ifdef __MSDOS__ */
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	SDTIF_nanosleep

   SYNOPSIS    :	int SDTIF_nanosleep(request_ptr, remainder_ptr);

						int                    return_code;

						const struct timespec *request_ptr;

						struct timespec       *remainder_ptr;

   DESCRIPTION :	Sleeps for a given number of nanoseconds.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``nanoseconds`` is the amount of time to sleep in
						nanoseconds (billionths of a second).

   RETURNS     :	Returns from this function are as follow:

						(.) Zero if the nanosecond sleep was performed without
						error.

						(.) Non-zero if an error occurs. In this case the system
						variable ``errno`` will be set to indicate the nature of
						the error condition.

   CAVEATS     :	The exact quantums for which this function will sleep will,
						of course, vary with the operating system and compiler
						libraries available.

						For example, under the MS-DOS Borland C compiler, the
						sleep quantum is in milliseconds, not nanoseconds.

						Under non-System V SunOS, the sleep quantum is in
						microseconds.

   SEE ALSO    :	SDTIF_usleep
						SDTIF_nsleep

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1986 - 2018 Michael L. Brock

   OUTPUT INDEX:	SDTIF_nanosleep
						Miscellaneous Functions:SDTIF_nanosleep
						SDTIF:Functions:SDTIF_nanosleep
						SDTIF:Miscellaneous Functions:SDTIF_nanosleep
						System Date/Time Interface Facility Functions:See SDTIF

   PUBLISH XREF:	SDTIF_nanosleep

   PUBLISH NAME:	SDTIF_nanosleep

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int SDTIF_nanosleep(const struct timespec *request_ptr,
	struct timespec *remainder_ptr)
#else
int SDTIF_nanosleep(request_ptr, remainder_ptr)
const struct timespec *request_ptr;
struct timespec       *remainder_ptr;
#endif /* #ifndef NARGS */
{
	int return_code;

#ifdef __SVR4
	return_code = nanosleep(request_ptr, remainder_ptr);
#else
	if ((request_ptr == NULL) ||
		(request_ptr->tv_sec < 0L) || (request_ptr->tv_nsec < 0L) ||
		(request_ptr->tv_nsec > 1000000000L)) {
		errno       = EINVAL;
		return_code = -1;
	}
	else {
		SDTIF_nsleep((request_ptr->tv_sec * 1000000000L) + request_ptr->tv_nsec);
		if (remainder_ptr != NULL) {
			remainder_ptr->tv_sec  = 0L;
			remainder_ptr->tv_nsec = 0L;
		}
		return_code = 0;
	}
#endif /* #ifdef __SVR4 */

	return(return_code);
}
/*	***********************************************************************	*/

