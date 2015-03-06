/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	GENFUNCS General Functions Library Source Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Performs a 'sleep' with (approximately) microsecond
								granularity.

	Revision History	:	1996-06-15 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Required include files . . .														*/
/*	***********************************************************************	*/

#include <errno.h>

#include "genfunci.h"

#ifdef _Windows
# include <winbase.h>
#endif /* #ifdef _Windows */

#ifdef __BORLANDC__
# include <dos.h>
#else
# ifdef __BCPLUSPLUS
#  include <dos.h>
# endif /* #ifdef __BCPLUSPLUS */
#endif /* #if __BORLANDC__ */

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_usleep

   SYNOPSIS    :	void GEN_usleep(microseconds);

						unsigned long microseconds;

   DESCRIPTION :	Sleeps for a given number of microseconds.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``microseconds`` is the amount of time to sleep in
						microseconds (millionths of a second).

   RETURNS     :	Void.

   NOTES       :	

   CAVEATS     :	The exact quantums for which this function will sleep will,
						of course, vary with the operating system and compiler
						libraries available.

						For example, under the MS-DOS Borland C compiler, the
						sleep quantum is in milliseconds, not microseconds.

   SEE ALSO    :  GEN_nsleep
						GEN_nanosleep

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1996 - 2015 Michael L. Brock

   OUTPUT INDEX:	GEN_usleep
						Miscellaneous Functions:GEN_usleep
						GENFUNCS:Functions:GEN_usleep
						GENFUNCS:Miscellaneous Functions:GEN_usleep
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_usleep

   PUBLISH NAME:	GEN_usleep

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void GEN_usleep(unsigned long microseconds)
#else
void GEN_usleep(microseconds)
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

   NAME        :	GEN_nsleep

   SYNOPSIS    :	void GEN_nsleep(nanoseconds);

						unsigned long nanoseconds;

   DESCRIPTION :	Sleeps for a given number of nanoseconds.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``nanoseconds`` is the amount of time to sleep in
						nanoseconds (billionths of a second).

   RETURNS     :	Void.

   NOTES       :	

   CAVEATS     :	The exact quantums for which this function will sleep will,
						of course, vary with the operating system and compiler
						libraries available.

						For example, under the MS-DOS Borland C compiler, the
						sleep quantum is in milliseconds, not nanoseconds.

						Under non-System V SunOS, the sleep quantum is in
						microseconds.

   SEE ALSO    :	GEN_usleep
						GEN_nanosleep

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1996 - 2015 Michael L. Brock

   OUTPUT INDEX:	GEN_nsleep
						Miscellaneous Functions:GEN_nsleep
						GENFUNCS:Functions:GEN_nsleep
						GENFUNCS:Miscellaneous Functions:GEN_nsleep
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_nsleep

   PUBLISH NAME:	GEN_nsleep

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void GEN_nsleep(unsigned long nanoseconds)
#else
void GEN_nsleep(nanoseconds)
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

   NAME        :	GEN_nanosleep

   SYNOPSIS    :	int GEN_nanosleep(request_ptr, remainder_ptr);

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

   NOTES       :	

   CAVEATS     :	The exact quantums for which this function will sleep will,
						of course, vary with the operating system and compiler
						libraries available.

						For example, under the MS-DOS Borland C compiler, the
						sleep quantum is in milliseconds, not nanoseconds.

						Under non-System V SunOS, the sleep quantum is in
						microseconds.

   SEE ALSO    :	GEN_usleep
						GEN_nsleep

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1996 - 2015 Michael L. Brock

   OUTPUT INDEX:	GEN_nanosleep
						Miscellaneous Functions:GEN_nanosleep
						GENFUNCS:Functions:GEN_nanosleep
						GENFUNCS:Miscellaneous Functions:GEN_nanosleep
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_nanosleep

   PUBLISH NAME:	GEN_nanosleep

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int  GEN_nanosleep(const struct timespec *request_ptr,
	struct timespec *remainder_ptr)
#else
int GEN_nanosleep(request_ptr, remainder_ptr)
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
		GEN_nsleep((request_ptr->tv_sec * 1000000000L) + request_ptr->tv_nsec);
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

