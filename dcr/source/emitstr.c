/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:

	Revision History	:	1994-03-14 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include "dcr.h"

/*	***********************************************************************	*/

void DCR_EmitString(out_string, out_count, output_function,
	output_control)
char           *out_string;
unsigned int    out_count;
#ifndef NARGS
void          (*output_function)(void *, char *, ...);
#else
void          (*output_function)();
#endif /* #ifndef NARGS */
void           *output_control;
{
	unsigned int count_1;

	for (count_1 = 0; count_1 < out_count; count_1++)
		(*output_function)(output_control, "%s", out_string);
}
/*	***********************************************************************	*/

