/* *********************************************************************** */
/* *********************************************************************** */
/*	GENFUNCS General Functions Library Source Module								*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Compare two 'struct timespec' values.

	Revision History	:	1993-11-10 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include "genfunci.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	GEN_Compare_timespec

	SYNOPSIS		:	comparison_code = GEN_Compare_timespec(timespec_ptr_1,
							timespec_ptr_2);

						int                    comparison_code;

						const struct timespec *timespec_ptr_1;

						const struct timespec *timespec_ptr_2;

   DESCRIPTION :  Compares the two times (to which the parameters
						``timespec_ptr_1`` and ``timespec_ptr_2`` point) for
						equality.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``timespec_ptr_1`` points to the first of the ``struct
						timespec`` structures to be compared.

						(.) ``timespec_ptr_2`` points to the second of the ``struct
						timespec`` structures to be compared.

   RETURNS     :  Returns from this function are as follow:

						(.) negative if the first time is less than second.

						(.) positive if the first time is greater than second.

						(.) zero if the times are equal.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	GEN_Compare_timeval

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2018 Michael L. Brock

	OUTPUT INDEX:	GEN_Compare_timespec
						Date/Time Functions:GEN_Compare_timespec
						GENFUNCS:Functions:GEN_Compare_timespec
						GENFUNCS:Date/Time Functions:GEN_Compare_timespec
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_Compare_timespec

	PUBLISH NAME:	GEN_Compare_timespec

	ENTRY CLASS	:	Date/Time Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int GEN_Compare_timespec(const struct timespec *timespec_ptr_1,
	const struct timespec *timespec_ptr_2)
#else
int GEN_Compare_timespec(timespec_ptr_1, timespec_ptr_2)
const struct timespec *timespec_ptr_1;
const struct timespec *timespec_ptr_2;
#endif /* #ifndef NARGS */
{
	int cmp;
 
	if ((cmp = ((int) (timespec_ptr_1->tv_sec - timespec_ptr_2->tv_sec))) == 0)
		cmp = ((int) (timespec_ptr_1->tv_nsec - timespec_ptr_2->tv_nsec));
 
	return(cmp);
}
/* *********************************************************************** */

