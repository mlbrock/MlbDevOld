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

	Revision History	:	1994-07-29 --- Creation.
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

#include "dcr.h"

/*	***********************************************************************	*/


void DCR_GetUserCallBack(cache_ptr, call_back_mask, call_back_function)
DCR_CACHE        *cache_ptr;
unsigned long    *call_back_mask;
#ifndef NARGS
int           (**call_back_function)(DCR_CACHE *, unsigned long, int,
	unsigned int, int, unsigned int, void *, DCR_STAT *, int, char *);
#else
int           (**call_back_function)();
#endif /* #ifndef NARGS */
{
	if (call_back_mask != NULL)
		*call_back_mask = cache_ptr->call_back_mask;

	if (call_back_function != NULL)
		*call_back_function = cache_ptr->call_back_function;
}
/*	***********************************************************************	*/

void DCR_SetUserCallBack(cache_ptr, call_back_mask, call_back_function)
DCR_CACHE             *cache_ptr;
const unsigned long   *call_back_mask;
#ifndef NARGS
int                  (*call_back_function)(DCR_CACHE *, unsigned long, int,
	unsigned int, int, unsigned int, void *, DCR_STAT *, int, char *);
#else
int                  (*call_back_function)();
#endif /* #ifndef NARGS */
{
	cache_ptr->call_back_mask     = (call_back_mask     != NULL) ?
		*call_back_mask    : cache_ptr->call_back_mask;
	cache_ptr->call_back_function = (call_back_function != NULL) ?
		call_back_function : cache_ptr->call_back_function;
}
/*	***********************************************************************	*/

void DCR_ClearUserCallBack(cache_ptr)
DCR_CACHE *cache_ptr;
{
	cache_ptr->call_back_function = NULL;
}
/*	***********************************************************************	*/

void DCR_GetCriticalCallBack(cache_ptr, critical_call_back_function)
DCR_CACHE        *cache_ptr;
#ifndef NARGS
int           (**critical_call_back_function)(DCR_CACHE *, unsigned long, int,
	int, unsigned int, void *, int, char *);
#else
int           (**critical_call_back_function)();
#endif /* #ifndef NARGS */
{
	*critical_call_back_function = cache_ptr->critical_call_back_function;
}
/*	***********************************************************************	*/

void DCR_SetCriticalCallBack(cache_ptr, critical_call_back_function)
DCR_CACHE       *cache_ptr;
#ifndef NARGS
int           (*critical_call_back_function)(DCR_CACHE *, unsigned long, int,
	int, unsigned int, void *, int, char *);
#else
int           (*critical_call_back_function)();
#endif /* #ifndef NARGS */
{
	cache_ptr->critical_call_back_function = critical_call_back_function;
}
/*	***********************************************************************	*/

