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

	Revision History	:	1994-07-30 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <string.h>

#include "dcr.h"

/*	***********************************************************************	*/

void DCR_EmitCallBacks(cache_ptr, output_function, output_control)
DCR_CACHE  *cache_ptr;
#ifndef NARGS
void      (*output_function)(void *, char *, ...);
#else
void      (*output_function)();
#endif /* #ifndef NARGS */
void       *output_control;
{
	unsigned int  count_1;
	unsigned long call_back_mask = 1L;
	char          tmp_description[256];
	char          tmp_buffer[256];
	char          tmp_cb_name[DCR_MAX_CB_NAME + 1];

	STR_EMIT_CharLine('=', 78, output_function, output_control);
	(*output_function)(output_control,
		"Call-back Mask Settings (decimal)    : %10lu\n",
		cache_ptr->call_back_mask);
	(*output_function)(output_control,
		"Call-back Mask Settings (hexadecimal): 0X%08lX\n",
		cache_ptr->call_back_mask);
	(*output_function)(output_control,
		"Call-back Mask Settings (binary)     : %s\n",
		val2str(cache_ptr->call_back_mask, 0, 2, "0", tmp_buffer));
	STR_EMIT_CharLine('-', 78, output_function, output_control);
	(*output_function)(output_control,
		"User Call-back Function Pointer      : ");
	if (cache_ptr->call_back_function == NULL)
		(*output_function)(output_control, "NOT REGISTERED\n");
	else
		(*output_function)(output_control, "0X%08lX\n",
			((unsigned long) cache_ptr->call_back_function));
	STR_EMIT_CharLine('-', 78, output_function, output_control);
	(*output_function)(output_control,
		"Critical Call-back Function Pointer  : ");
	if (cache_ptr->critical_call_back_function == NULL)
		(*output_function)(output_control, "NOT REGISTERED\n");
	else
		(*output_function)(output_control, "0X%08lX\n",
			((unsigned long) cache_ptr->critical_call_back_function));
	STR_EMIT_CharLine('=', 78, output_function, output_control);
	STR_EMIT_CharLine('=', 78, output_function, output_control);
	(*output_function)(output_control, "Call-back Type Settings\n");
	STR_EMIT_CharLine('-', 78, output_function, output_control);
	for (count_1 = 0; count_1 < DCR_CB_COUNT; count_1++) {
		sprintf(tmp_description, "Call-back %s Setting",
			strcpy(tmp_buffer, initcaps(DCR_GetCallBackName(call_back_mask,
			tmp_cb_name))));
		(*output_function)(output_control, "%-36.36s: %s\n", tmp_description,
			(cache_ptr->call_back_mask & call_back_mask) ? "ON" : "OFF");
		call_back_mask <<= 1L;
	}
	STR_EMIT_CharLine('=', 78, output_function, output_control);
}
/*	***********************************************************************	*/

