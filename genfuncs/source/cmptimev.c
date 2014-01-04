/* *********************************************************************** */
/* *********************************************************************** */
/*	GENFUNCS General Functions Library Source Module								*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Compare two 'struct timeval' values.

	Revision History	:	1993-11-10 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2014.
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

	NAME			:	GEN_Compare_timeval

	SYNOPSIS		:	comparison_code = GEN_Compare_timeval(timeval_ptr_1,
							timeval_ptr_2);

						int                   comparison_code;

						const struct timeval *timeval_ptr_1;

						const struct timeval *timeval_ptr_2;

   DESCRIPTION :  Compares the two times (to which the parameters
						``timeval_ptr_1`` and ``timeval_ptr_2`` point) for equality.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``timeval_ptr_1`` points to the first of the ``struct
						timeval`` structures to be compared.

						(.) ``timeval_ptr_2`` points to the second of the ``struct
						timeval`` structures to be compared.

   RETURNS     :  Returns from this function are as follow:

						(.) negative if the first time is less than second.

						(.) positive if the first time is greater than second.

						(.) zero if the times are equal.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	GEN_Compare_timespec

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2014 Michael L. Brock

	OUTPUT INDEX:	GEN_Compare_timeval
						Date/Time Functions:GEN_Compare_timeval
						GENFUNCS:Functions:GEN_Compare_timeval
						GENFUNCS:Date/Time Functions:GEN_Compare_timeval
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_Compare_timeval

	PUBLISH NAME:	GEN_Compare_timeval

	ENTRY CLASS	:	Date/Time Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int GEN_Compare_timeval(const struct timeval *timeval_ptr_1,
	const struct timeval *timeval_ptr_2)
#else
int GEN_Compare_timeval(timeval_ptr_1, timeval_ptr_2)
const struct timeval *timeval_ptr_1;
const struct timeval *timeval_ptr_2;
#endif /* #ifndef NARGS */
{
	int cmp;
 
	if ((cmp = ((int) (timeval_ptr_1->tv_sec - timeval_ptr_2->tv_sec))) == 0)
		cmp = ((int) (timeval_ptr_1->tv_usec - timeval_ptr_2->tv_usec));
 
	return(cmp);
}
/* *********************************************************************** */

