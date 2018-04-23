/* *********************************************************************** */
/* *********************************************************************** */
/*	Multi-Threading Interface Facility (MTIF) Library Source File				*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Manages thread priority.

	Revision History	:	2001-07-18 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2001 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/*	Necessary include files . . .															*/
/* *********************************************************************** */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <strfuncs.h>

#include "mtifi.h"

/* *********************************************************************** */

/* *********************************************************************** */
#ifdef _Windows
# ifdef MTIF_THR_PRIORITY_SEQUENTIAL
#  undef MTIF_THR_PRIORITY_SEQUENTIAL
# endif /* # ifdef MTIF_THR_PRIORITY_SEQUENTIAL */
#else
# ifndef MTIF_THR_PRIORITY_SEQUENTIAL
#  define MTIF_THR_PRIORITY_SEQUENTIAL	1
# endif /* # ifndef MTIF_THR_PRIORITY_SEQUENTIAL */
#endif /* #ifdef _Windows */
/* *********************************************************************** */

/* *********************************************************************** */
#ifdef _Windows
static const MTIF_THR_PRIORITY_MAP MTIF_THR_Win32PriorityMapList[] = {
	{	MTIF_THR_PRIORITY_LOWEST,	MTIF_THR_PRIORITY_LOWEST,	THREAD_PRIORITY_IDLE				},
	{	MTIF_THR_PRIORITY_LOWER,	MTIF_THR_PRIORITY_LOWER,	THREAD_PRIORITY_LOWEST			},
	{	MTIF_THR_PRIORITY_LOW,		MTIF_THR_PRIORITY_LOW,		THREAD_PRIORITY_BELOW_NORMAL	},
	{	MTIF_THR_PRIORITY_MEDIUM,	MTIF_THR_PRIORITY_MEDIUM,	THREAD_PRIORITY_NORMAL			},
	{	MTIF_THR_PRIORITY_HIGH,		MTIF_THR_PRIORITY_HIGH,		THREAD_PRIORITY_ABOVE_NORMAL	},
	{	MTIF_THR_PRIORITY_HIGHER,	MTIF_THR_PRIORITY_HIGHER,	THREAD_PRIORITY_HIGHEST			},
	{	MTIF_THR_PRIORITY_HIGHEST,	MTIF_THR_PRIORITY_HIGHEST,	THREAD_PRIORITY_TIME_CRITICAL	}
};
static const unsigned int          MTIF_THR_Win32PriorityMapCount  =
	sizeof(MTIF_THR_Win32PriorityMapList) /
	sizeof(MTIF_THR_Win32PriorityMapList[0]);
#endif /* #ifdef _Windows */
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Function prototypes for functions private to this module . . .				*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(int MTIF_THR_GetPriorityMapNativeInternal,
	(MTIF_THR_HANDLE *thr_handle_ptr, unsigned int allocated_count,
	MTIF_THR_PRIORITY_MAP *allocated_list, unsigned int *out_count,
	MTIF_THR_PRIORITY_MAP **out_list, char *error_text));
COMPAT_FN_DECL_STATIC(int MTIF_THR_CheckSetPriority,
	(MTIF_THR_HANDLE *thr_handle_ptr, MTIF_THR_PRIORITY mtif_priority,
	char *error_text));
COMPAT_FN_DECL_STATIC(int MTIF_THR_AllocPriorityMap,
	(unsigned int new_count, unsigned int *out_count,
	MTIF_THR_PRIORITY_MAP **out_list, char *error_text));
	/* ***************************************************************** */
#ifndef _Windows
COMPAT_FN_DECL_STATIC(int MTIF_THR_PriorityToNativeGeneric,
	(MTIF_THR_HANDLE *thr_handle_ptr, MTIF_THR_PRIORITY mtif_priority,
	MTIF_THR_PRIORITY_NATIVE *native_priority, char *error_text));
COMPAT_FN_DECL_STATIC(int MTIF_THR_PriorityFromNativeGeneric,
	(MTIF_THR_HANDLE *thr_handle_ptr, MTIF_THR_PRIORITY_NATIVE native_priority,
	MTIF_THR_PRIORITY *mtif_priority, char *error_text));
#endif /* #ifndef _Windows */
	/* ***************************************************************** */
#ifdef MTIF_THR_PRIORITY_SEQUENTIAL
COMPAT_FN_DECL_STATIC(int MTIF_THR_GetPriorityMapNativeGeneric,
	(MTIF_THR_HANDLE *thr_handle_ptr, unsigned int allocated_count,
	MTIF_THR_PRIORITY_MAP *allocated_list, unsigned int *out_count,
	MTIF_THR_PRIORITY_MAP **out_list, char *error_text));
#endif /* #ifdef MTIF_THR_PRIORITY_SEQUENTIAL */
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int MTIF_THR_GetPriority(MTIF_THR_HANDLE *thr_handle_ptr,
	MTIF_THR_PRIORITY *mtif_priority, char *error_text)
#else
int MTIF_THR_GetPriority(thr_handle_ptr, mtif_priority, error_text)
MTIF_THR_HANDLE   *thr_handle_ptr;
MTIF_THR_PRIORITY *mtif_priority;
char              *error_text;
#endif /* #ifndef NARGS */
{
	int                      return_code;
	MTIF_THR_PRIORITY_NATIVE native_priority;
	char                     thread_id_text[MTIF_THR_ID_TEXT_LENGTH + 1];
	char                     tmp_error_text[MTIF_MAX_ERROR_TEXT];

	if ((return_code = MTIF_THR_GetPriorityNative(thr_handle_ptr,
		&native_priority, (error_text != NULL) ? tmp_error_text : NULL)) ==
		MTIF_SUCCESS)
		return_code = MTIF_THR_PriorityFromNative(thr_handle_ptr, native_priority,
			mtif_priority, (error_text != NULL) ? tmp_error_text : NULL);

	if ((return_code != MTIF_SUCCESS) && (error_text != NULL))
		sprintf(error_text, "Attempt to get thread (%s) priority failed: %s",
			MTIF_THR_GetThreadText(thr_handle_ptr, thread_id_text),
			tmp_error_text);

	return(return_code);	
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int MTIF_THR_SetPriority(MTIF_THR_HANDLE *thr_handle_ptr,
	MTIF_THR_PRIORITY mtif_priority, char *error_text)
#else
int MTIF_THR_SetPriority(thr_handle_ptr, mtif_priority, error_text)
MTIF_THR_HANDLE   *thr_handle_ptr;
MTIF_THR_PRIORITY  mtif_priority;
char              *error_text;
#endif /* #ifndef NARGS */
{
	int                      return_code;
	MTIF_THR_PRIORITY_NATIVE native_priority;
	char                     thread_id_text[MTIF_THR_ID_TEXT_LENGTH + 1];
	char                     native_priority_text[127 + 1];
	char                     tmp_error_text[MTIF_MAX_ERROR_TEXT];

	if ((return_code = MTIF_THR_CheckSetPriority(thr_handle_ptr,
		mtif_priority, error_text)) == MTIF_SUCCESS) {
		if ((return_code = MTIF_THR_PriorityToNative(thr_handle_ptr, mtif_priority,
			&native_priority, (error_text != NULL) ? tmp_error_text : NULL)) ==
			MTIF_SUCCESS) {
			if ((return_code = MTIF_THR_SetPriorityNative(thr_handle_ptr,
				native_priority, (error_text != NULL) ? tmp_error_text : NULL)) !=
				MTIF_SUCCESS) {
				if (error_text != NULL)
					sprintf(native_priority_text, "%ld", ((long) native_priority));
			}
		}
		else if (error_text != NULL)
			strcpy(native_priority_text, "UNKNOWN");
		if ((return_code != MTIF_SUCCESS) && (error_text != NULL))
			sprintf(error_text,
				"%s (%s) priority to '%s%s' = %d (%s = %s) failed: %s",
				"Attempt to set thread",
				MTIF_THR_GetThreadText(thr_handle_ptr, thread_id_text),
				"MTIF_THR_PRIORITY_", MTIF_GET_THR_PRIORITY_NAME(mtif_priority),
				((int) mtif_priority), "native priority", native_priority_text,
				tmp_error_text);
	}

	return(return_code);	
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int MTIF_THR_GetPriorityMinMaxNative(MTIF_THR_HANDLE *thr_handle_ptr,
	MTIF_THR_PRIORITY_NATIVE *min_priority,
	MTIF_THR_PRIORITY_NATIVE *max_priority, char *error_text)
#else
int MTIF_THR_GetPriorityMinMaxNative(thr_handle_ptr, min_priority,
	max_priority, error_text)
MTIF_THR_HANDLE          *thr_handle_ptr;
MTIF_THR_PRIORITY_NATIVE *min_priority;
MTIF_THR_PRIORITY_NATIVE *max_priority;
char                     *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code;
	char thread_id_text[MTIF_THR_ID_TEXT_LENGTH + 1];
	char tmp_error_text[MTIF_MAX_ERROR_TEXT];

	if ((return_code = MTIF_THR_GetPriorityMinNative(thr_handle_ptr,
		min_priority, (error_text != NULL) ? tmp_error_text : NULL)) ==
		MTIF_SUCCESS) {
		if ((return_code = MTIF_THR_GetPriorityMaxNative(thr_handle_ptr,
			max_priority, (error_text != NULL) ? tmp_error_text : NULL)) ==
			MTIF_SUCCESS) {
			if (*min_priority > *max_priority) {
				if (error_text != NULL)
					sprintf(tmp_error_text, "%s (%ld) %s (%ld).",
						"The minimum thread priority", ((long) min_priority),
						"is greater than the maximum thread priority",
						((long) min_priority));
				return_code = MTIF_OP_FAILURE_THR;
			}
		}
	}

	if ((return_code != MTIF_SUCCESS) && (error_text != NULL))
		strcat(strcat(strcat(strcat(strcpy(error_text,
			"Error encountered on attempt to get the native threads "),
			"implementation minimum and maximum thread priorities for "),
			MTIF_THR_GetThreadText(thr_handle_ptr, thread_id_text)),
			": "), tmp_error_text);

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int MTIF_THR_GetPriorityMapNative(MTIF_THR_HANDLE *thr_handle_ptr,
	unsigned int *out_count, MTIF_THR_PRIORITY_MAP **out_list, char *error_text)
#else
int MTIF_THR_GetPriorityMapNative(thr_handle_ptr, out_count, out_list,
	error_text)
MTIF_THR_HANDLE        *thr_handle_ptr;
unsigned int           *out_count;
MTIF_THR_PRIORITY_MAP **out_list;
char                   *error_text;
#endif /* #ifndef NARGS */
{
	return(MTIF_THR_GetPriorityMapNativeBasic(thr_handle_ptr, 0, NULL,
		out_count, out_list, error_text));
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int MTIF_THR_GetPriorityMapNativeBasic(MTIF_THR_HANDLE *thr_handle_ptr,
	unsigned int allocated_count, MTIF_THR_PRIORITY_MAP *allocated_list,
	unsigned int *out_count, MTIF_THR_PRIORITY_MAP **out_list, char *error_text)
#else
int MTIF_THR_GetPriorityMapNativeBasic(thr_handle_ptr, allocated_count,
	allocated_list, out_count, out_list, error_text)
MTIF_THR_HANDLE        *thr_handle_ptr;
unsigned int            allocated_count;
MTIF_THR_PRIORITY_MAP  *allocated_list;
unsigned int           *out_count;
MTIF_THR_PRIORITY_MAP **out_list;
char                   *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code;
	char thread_id_text[MTIF_THR_ID_TEXT_LENGTH + 1];
	char tmp_error_text[MTIF_MAX_ERROR_TEXT];

	*out_count = 0;
	*out_list  = NULL;

	if (allocated_count && (allocated_list == NULL)) {
		if (error_text != NULL)
			sprintf(tmp_error_text,
				"The 'allocated_count' parameter is non-zero (%u), %s.",
				allocated_count, "but the 'allocated_list' parameter is 'NULL'");
		return_code = MTIF_BAD_ARGS_FAILURE;
	}
	else if ((!allocated_count) && (allocated_list != NULL)) {
		if (error_text != NULL)
			sprintf(tmp_error_text,
				"The 'allocated_count' parameter is zero, %s (0x%p).",
				"but the 'allocated_list' parameter is not 'NULL'", allocated_list);
		return_code = MTIF_BAD_ARGS_FAILURE;
	}
	else
		return_code = MTIF_THR_GetPriorityMapNativeInternal(thr_handle_ptr,
			allocated_count, allocated_list, out_count, out_list,
			(error_text != NULL) ? tmp_error_text : NULL);

	if ((return_code != MTIF_SUCCESS) && (error_text != NULL))
		strcat(strcat(strcat(strcat(strcpy(error_text,
			"Error encountered on attempt to get the native threads "),
			"implementation thread priority mapping for "),
			MTIF_THR_GetThreadText(thr_handle_ptr, thread_id_text)),
			": "), tmp_error_text);

	return(return_code);
}
/* *********************************************************************** */

/*
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	Windows threads
	|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
*/
#ifdef _Windows
/* *********************************************************************** */
#ifndef NARGS
int MTIF_THR_GetPriorityNative(MTIF_THR_HANDLE *thr_handle_ptr,
	MTIF_THR_PRIORITY_NATIVE *native_priority, char *error_text)
#else
int MTIF_THR_GetPriorityNative(thr_handle_ptr, native_priority, error_text)
MTIF_THR_HANDLE          *thr_handle_ptr;
MTIF_THR_PRIORITY_NATIVE *native_priority;
char                     *error_text;
#endif /* #ifndef NARGS */
{
	int    return_code;
	char   thread_id_text[MTIF_THR_ID_TEXT_LENGTH + 1];
	HANDLE win32_handle;

	win32_handle = MTIF_THR_GET_OS_HANDLE_DEFAULT(thr_handle_ptr);

	if ((*native_priority = GetThreadPriority(win32_handle)) !=
		THREAD_PRIORITY_ERROR_RETURN)
		return_code = MTIF_SUCCESS;
	else {
		if (error_text != NULL) {
			sprintf(error_text,
				"Call to 'GetThreadPriority(%s%s = 0x%0lp = %s)' failed: ",
				(thr_handle_ptr != NULL) ? "" : "current ", "thread handle",
				((unsigned long) win32_handle),
				MTIF_THR_GetThreadText(thr_handle_ptr, thread_id_text));
			MTIF_SUPP_AppendLastErrorString_Win32(error_text);
		}
		return_code = MTIF_OP_FAILURE_THR;
	}

	return(return_code);	
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int MTIF_THR_SetPriorityNative(MTIF_THR_HANDLE *thr_handle_ptr,
	MTIF_THR_PRIORITY_NATIVE native_priority, char *error_text)
#else
int MTIF_THR_SetPriorityNative(thr_handle_ptr, native_priority, error_text)
MTIF_THR_HANDLE          *thr_handle_ptr;
MTIF_THR_PRIORITY_NATIVE  native_priority;
char                     *error_text;
#endif /* #ifndef NARGS */
{
	int    return_code;
	char   thread_id_text[MTIF_THR_ID_TEXT_LENGTH + 1];
	HANDLE win32_handle;

	win32_handle = MTIF_THR_GET_OS_HANDLE_DEFAULT(thr_handle_ptr);

	if (SetThreadPriority(win32_handle, native_priority) != 0)
		return_code = MTIF_SUCCESS;
	else {
		if (error_text != NULL) {
			sprintf(error_text,
				"Call to 'SetThreadPriority(%s%s = 0x%0lp = %s, %s = %d)' failed: ",
				(thr_handle_ptr != NULL) ? "" : "current ", "thread handle",
				((unsigned long) win32_handle),
				MTIF_THR_GetThreadText(thr_handle_ptr, thread_id_text),
				"native thread priority", native_priority);
			MTIF_SUPP_AppendLastErrorString_Win32(error_text);
		}
		return_code = MTIF_OP_FAILURE_THR;
	}

	return(return_code);	
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int MTIF_THR_PriorityToNative(MTIF_THR_HANDLE *thr_handle_ptr,
	MTIF_THR_PRIORITY mtif_priority, MTIF_THR_PRIORITY_NATIVE *native_priority,
	char *error_text)
#else
int MTIF_THR_PriorityToNative(thr_handle_ptr, mtif_priority, native_priority,
	error_text)
MTIF_THR_HANDLE          *thr_handle_ptr;
MTIF_THR_PRIORITY         mtif_priority;
MTIF_THR_PRIORITY_NATIVE *native_priority;
char                     *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code = MTIF_SUCCESS;
	char thread_id_text[MTIF_THR_ID_TEXT_LENGTH + 1];

	switch (mtif_priority) {
		case MTIF_THR_PRIORITY_LOWEST	:
			*native_priority = THREAD_PRIORITY_IDLE;
			break;
		case MTIF_THR_PRIORITY_LOWER	:
			*native_priority = THREAD_PRIORITY_LOWEST;
			break;
		case MTIF_THR_PRIORITY_LOW		:
			*native_priority = THREAD_PRIORITY_BELOW_NORMAL;
			break;
		case MTIF_THR_PRIORITY_MEDIUM	:
			*native_priority = THREAD_PRIORITY_NORMAL;
			break;
		case MTIF_THR_PRIORITY_HIGH	:
			*native_priority = THREAD_PRIORITY_ABOVE_NORMAL;
			break;
		case MTIF_THR_PRIORITY_HIGHER	:
			*native_priority = THREAD_PRIORITY_HIGHEST;
			break;
		case MTIF_THR_PRIORITY_HIGHEST:
			*native_priority = THREAD_PRIORITY_TIME_CRITICAL;
			break;
		case MTIF_THR_PRIORITY_NONE	:
		default								:
			if (error_text != NULL)
				sprintf(error_text, "%s %d for %s %s %s: %d %s.",
					"Attempt to map the MTIF thread priority value", mtif_priority,
					MTIF_THR_GetThreadText(thr_handle_ptr, thread_id_text),
					"to the equivalent native threads implementation priority",
					"value failed", ((int) mtif_priority),
					"is an invalid MTIF thread priority value");
			return_code = MTIF_OP_FAILURE_THR;
			break;
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int MTIF_THR_PriorityFromNative(MTIF_THR_HANDLE *thr_handle_ptr,
	MTIF_THR_PRIORITY_NATIVE native_priority, MTIF_THR_PRIORITY *mtif_priority,
	char *error_text)
#else
int MTIF_THR_PriorityFromNative(thr_handle_ptr, native_priority, mtif_priority,
	error_text)
MTIF_THR_HANDLE          *thr_handle_ptr;
MTIF_THR_PRIORITY_NATIVE  native_priority;
MTIF_THR_PRIORITY        *mtif_priority;
char                     *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code = MTIF_SUCCESS;
	char thread_id_text[MTIF_THR_ID_TEXT_LENGTH + 1];

	switch (native_priority) {
		case THREAD_PRIORITY_IDLE				:
			*mtif_priority = MTIF_THR_PRIORITY_LOWEST;
			break;
		case THREAD_PRIORITY_LOWEST			:
			*mtif_priority = MTIF_THR_PRIORITY_LOWER;
			break;
		case THREAD_PRIORITY_BELOW_NORMAL	:
			*mtif_priority = MTIF_THR_PRIORITY_LOW;
			break;
		case THREAD_PRIORITY_NORMAL			:
			*mtif_priority = MTIF_THR_PRIORITY_MEDIUM;
			break;
		case THREAD_PRIORITY_ABOVE_NORMAL	:
			*mtif_priority = MTIF_THR_PRIORITY_HIGH;
			break;
		case THREAD_PRIORITY_HIGHEST			:
			*mtif_priority = MTIF_THR_PRIORITY_HIGHER;
			break;
		case THREAD_PRIORITY_TIME_CRITICAL	:
			*mtif_priority = MTIF_THR_PRIORITY_HIGHEST;
			break;
		default								:
			if (error_text != NULL)
				sprintf(error_text, "%s %ld for %s %s: %ld %s.",
					"Attempt to map the native thread implementation priority value",
					((long) native_priority),
					MTIF_THR_GetThreadText(thr_handle_ptr, thread_id_text),
					"to the equivalent MTIF thread priority value failed",
					((long) native_priority),
					"is an invalid native thread implementation priority value");
			return_code = MTIF_OP_FAILURE_THR;
			break;
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int MTIF_THR_GetPriorityMinNative(MTIF_THR_HANDLE *thr_handle_ptr,
	MTIF_THR_PRIORITY_NATIVE *min_priority, char *error_text)
#else
int MTIF_THR_GetPriorityMinNative(thr_handle_ptr, min_priority, error_text)
MTIF_THR_HANDLE          *thr_handle_ptr;
MTIF_THR_PRIORITY_NATIVE *min_priority;
char                     *error_text;
#endif /* #ifndef NARGS */
{
	*min_priority = THREAD_PRIORITY_IDLE;

	/*	To prevent unused parameter noise.	*/
	if ((error_text != NULL) && (((char *) thr_handle_ptr) != error_text))
		*error_text = '\0';

	return(MTIF_SUCCESS);
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int MTIF_THR_GetPriorityMaxNative(MTIF_THR_HANDLE *thr_handle_ptr,
	MTIF_THR_PRIORITY_NATIVE *max_priority, char *error_text)
#else
int MTIF_THR_GetPriorityMaxNative(thr_handle_ptr, max_priority, error_text)
MTIF_THR_HANDLE          *thr_handle_ptr;
MTIF_THR_PRIORITY_NATIVE *max_priority;
char                     *error_text;
#endif /* #ifndef NARGS */
{
	*max_priority = THREAD_PRIORITY_TIME_CRITICAL;

	/*	To prevent unused parameter noise.	*/
	if ((error_text != NULL) && (((char *) thr_handle_ptr) == error_text))
		*error_text = '\0';

	return(MTIF_SUCCESS);
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
static int MTIF_THR_GetPriorityMapNativeInternal(
	MTIF_THR_HANDLE *thr_handle_ptr, unsigned int allocated_count,
	MTIF_THR_PRIORITY_MAP *allocated_list, unsigned int *out_count,
	MTIF_THR_PRIORITY_MAP **out_list, char *error_text)
#else
static int MTIF_THR_GetPriorityMapNativeInternal(thr_handle_ptr,
	allocated_count, allocated_list, out_count, out_list, error_text)
MTIF_THR_HANDLE        *thr_handle_ptr;
unsigned int            allocated_count;
MTIF_THR_PRIORITY_MAP  *allocated_list;
unsigned int           *out_count;
MTIF_THR_PRIORITY_MAP **out_list;
char                   *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code;
	char thread_id_text[MTIF_THR_ID_TEXT_LENGTH + 1];
	char tmp_error_text[MTIF_MAX_ERROR_TEXT];

	if ((allocated_count >= MTIF_THR_Win32PriorityMapCount) ||
      ((return_code = MTIF_THR_AllocPriorityMap(MTIF_THR_Win32PriorityMapCount,
		out_count, out_list, (error_text != NULL) ? tmp_error_text : NULL)) ==
		MTIF_SUCCESS)) {
		*out_count  = MTIF_THR_Win32PriorityMapCount;
		*out_list   = (allocated_count >= MTIF_THR_Win32PriorityMapCount) ?
			allocated_list : *out_list;
		return_code = MTIF_SUCCESS;
		memcpy(*out_list, MTIF_THR_Win32PriorityMapList,
			sizeof(MTIF_THR_Win32PriorityMapList));
	}
	else if (error_text != NULL)
		strcat(strcat(strcat(strcat(strcpy(error_text,
			"Attempt to create a mapping between MTIF thread priorities and "),
			"the native thread implementation thread priorities for "),
			MTIF_THR_GetThreadText(thr_handle_ptr, thread_id_text)),
			" failed: "), tmp_error_text);

	return(return_code);
}
/* *********************************************************************** */

#elif MTIF_THR_UI_THREADS
	/* |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
		|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
		Unix International threads
		|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||	*/
/* *********************************************************************** */
#ifndef NARGS
int MTIF_THR_GetPriorityNative(MTIF_THR_HANDLE *thr_handle_ptr,
	MTIF_THR_PRIORITY_NATIVE *native_priority, char *error_text)
#else
int MTIF_THR_GetPriorityNative(thr_handle_ptr, native_priority,
	error_text)
MTIF_THR_HANDLE          *thr_handle_ptr;
MTIF_THR_PRIORITY_NATIVE *native_priority;
char                     *error_text;
#endif /* #ifndef NARGS */
{
	int      return_code;
	thread_t thread_id;
	char     thread_id_text[MTIF_THR_ID_TEXT_LENGTH + 1];

	thread_id = MTIF_THR_GET_OS_ID_DEFAULT(thr_handle_ptr);

	if (!(error_code = thr_getprio(thread_id, native_priority)))
		return_code = MTIF_SUCCESS;
	else {
		if (error_text != NULL) {
			sprintf(error_text, "%s %s failed: %s %s: ",
				"Attempt to retrieve the thread priority for",
				MTIF_THR_GetThreadText(thr_handle_ptr, thread_id_text),
				"Attempt to determine the current thread scheduling",
				"priority using 'thr_getprio()' failed");
			MTIF_SUPP_AppendSpecErrorString(error_code, error_text);
		}
		return_code = MTIF_SYSTEM_FAILURE;
	}

	return(return_code);	
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int MTIF_THR_SetPriorityNative(MTIF_THR_HANDLE *thr_handle_ptr,
	MTIF_THR_PRIORITY_NATIVE native_priority, char *error_text)
#else
int MTIF_THR_SetPriorityNative(thr_handle_ptr, native_priority, error_text)
MTIF_THR_HANDLE          *thr_handle_ptr;
MTIF_THR_PRIORITY_NATIVE  native_priority;
char                     *error_text;
#endif /* #ifndef NARGS */
{
	int      return_code;
	thread_t thread_id;
	char     thread_id_text[MTIF_THR_ID_TEXT_LENGTH + 1];

	thread_id = MTIF_THR_GET_OS_ID_DEFAULT(thr_handle_ptr);

	if (!(error_code = thr_setprio(thread_id, native_priority)))
		return_code = MTIF_SUCCESS;
	else {
		if (error_text != NULL) {
			sprintf(error_text, "%s %s failed: %s %s: ",
				"Attempt to set the thread priority for",
				MTIF_THR_GetThreadText(thr_handle_ptr, thread_id_text),
				"Attempt to set the thread scheduling",
				"priority using 'thr_setprio()' failed");
			MTIF_SUPP_AppendSpecErrorString(error_code, error_text);
		}
		return_code = MTIF_SYSTEM_FAILURE;
	}

	return(return_code);	
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int MTIF_THR_PriorityToNative(MTIF_THR_HANDLE *thr_handle_ptr,
	MTIF_THR_PRIORITY mtif_priority, MTIF_THR_PRIORITY_NATIVE *native_priority,
	char *error_text)
#else
int MTIF_THR_PriorityToNative(thr_handle_ptr, mtif_priority, native_priority,
	error_text)
MTIF_THR_HANDLE          *thr_handle_ptr;
MTIF_THR_PRIORITY         mtif_priority;
MTIF_THR_PRIORITY_NATIVE *native_priority;
char                     *error_text;
#endif /* #ifndef NARGS */
{
	return(MTIF_THR_PriorityToNativeGeneric(thr_handle_ptr, mtif_priority,
		native_priority, error_text));
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int MTIF_THR_PriorityFromNative(MTIF_THR_HANDLE *thr_handle_ptr,
	MTIF_THR_PRIORITY_NATIVE native_priority, MTIF_THR_PRIORITY *mtif_priority,
	char *error_text)
#else
int MTIF_THR_PriorityFromNative(thr_handle_ptr, native_priority, mtif_priority,
	error_text)
MTIF_THR_HANDLE          *thr_handle_ptr;
MTIF_THR_PRIORITY_NATIVE  native_priority;
MTIF_THR_PRIORITY        *mtif_priority;
char                     *error_text;
#endif /* #ifndef NARGS */
{
	return(MTIF_THR_PriorityFromNativeGeneric(thr_handle_ptr, native_priority,
		mtif_priority, error_text));
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int MTIF_THR_GetPriorityMinNative(MTIF_THR_HANDLE *thr_handle_ptr,
	MTIF_THR_PRIORITY_NATIVE *min_priority, char *error_text)
#else
int MTIF_THR_GetPriorityMinNative(thr_handle_ptr, min_priority, error_text)
MTIF_THR_HANDLE          *thr_handle_ptr;
MTIF_THR_PRIORITY_NATIVE *min_priority;
char                     *error_text;
#endif /* #ifndef NARGS */
{
	*min_priority = 0;

	/*	To prevent unused parameter noise.	*/
	if ((error_text != NULL) && (((char *) thr_handle_ptr) != error_text))
		*error_text = '\0';

	return(MTIF_SUCCESS);
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int MTIF_THR_GetPriorityMaxNative(MTIF_THR_HANDLE *thr_handle_ptr,
	MTIF_THR_PRIORITY_NATIVE *max_priority, char *error_text)
#else
int MTIF_THR_GetPriorityMaxNative(thr_handle_ptr, max_priority, error_text)
MTIF_THR_HANDLE          *thr_handle_ptr;
MTIF_THR_PRIORITY_NATIVE *max_priority;
char                     *error_text;
#endif /* #ifndef NARGS */
{
	*max_priority = 127;

	/*	To prevent unused parameter noise.	*/
	if ((error_text != NULL) && (((char *) thr_handle_ptr) == error_text))
		*error_text = '\0';

	return(MTIF_SUCCESS);
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
static int MTIF_THR_GetPriorityMapNativeInternal(
	MTIF_THR_HANDLE *thr_handle_ptr, unsigned int allocated_count,
	MTIF_THR_PRIORITY_MAP *allocated_list, unsigned int *out_count,
	MTIF_THR_PRIORITY_MAP **out_list, char *error_text)
#else
static int MTIF_THR_GetPriorityMapNativeInternal(thr_handle_ptr,
	allocated_count, allocated_list, out_count, out_list, error_text)
MTIF_THR_HANDLE        *thr_handle_ptr;
unsigned int            allocated_count;
MTIF_THR_PRIORITY_MAP  *allocated_list;
unsigned int           *out_count;
MTIF_THR_PRIORITY_MAP **out_list;
char                   *error_text;
#endif /* #ifndef NARGS */
{
	return(MTIF_THR_GetPriorityMapNativeGeneric(thr_handle_ptr, allocated_count,
		allocated_list, out_count, out_list, error_text));
}
/* *********************************************************************** */

#elif MTIF_THR_POSIX_THREADS
	/* |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
		|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
		POSIX threads
		|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||	*/
/* *********************************************************************** */
#ifndef NARGS
int MTIF_THR_GetPriorityNative(MTIF_THR_HANDLE *thr_handle_ptr,
	MTIF_THR_PRIORITY_NATIVE *native_priority, char *error_text)
#else
int MTIF_THR_GetPriorityNative(thr_handle_ptr, native_priority,
	error_text)
MTIF_THR_HANDLE          *thr_handle_ptr;
MTIF_THR_PRIORITY_NATIVE *native_priority;
char                     *error_text;
#endif /* #ifndef NARGS */
{
	int                return_code;
	int                error_code;
	pthread_t          thread_id;
	int                tmp_policy;
	struct sched_param tmp_sched_param;
	char               thread_id_text[MTIF_THR_ID_TEXT_LENGTH + 1];

	thread_id = MTIF_THR_GET_OS_ID_DEFAULT(thr_handle_ptr);

	if ((error_code = pthread_getschedparam(thread_id, &tmp_policy,
		&tmp_sched_param)) != 0) {
		if (error_text != NULL) {
			sprintf(error_text, "%s %s failed: %s %s %s: ",
				"Attempt to retrieve the thread priority for",
				MTIF_THR_GetThreadText(thr_handle_ptr, thread_id_text),
				"Attempt to determine the current Posix thread scheduling",
				"policy and scheduling policy parameters using",
				"'pthread_getschedparam()' failed");
			MTIF_SUPP_AppendSpecErrorString(error_code, error_text);
		}
		return_code = MTIF_SYSTEM_FAILURE;
	}
	else {
		*native_priority = tmp_sched_param.sched_priority;
		return_code      = MTIF_SUCCESS;
	}

	return(return_code);	
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int MTIF_THR_SetPriorityNative(MTIF_THR_HANDLE *thr_handle_ptr,
	MTIF_THR_PRIORITY_NATIVE native_priority, char *error_text)
#else
int MTIF_THR_SetPriorityNative(thr_handle_ptr, native_priority, error_text)
MTIF_THR_HANDLE          *thr_handle_ptr;
MTIF_THR_PRIORITY_NATIVE  native_priority;
char                     *error_text;
#endif /* #ifndef NARGS */
{
	int                return_code;
	int                error_code;
	pthread_t          thread_id;
	int                tmp_policy;
	struct sched_param tmp_sched_param;
	char               thread_id_text[MTIF_THR_ID_TEXT_LENGTH + 1];
	char               tmp_error_text[MTIF_MAX_ERROR_TEXT];

	thread_id = MTIF_THR_GET_OS_ID_DEFAULT(thr_handle_ptr);

	if ((error_code = pthread_getschedparam(thread_id, &tmp_policy,
		&tmp_sched_param)) != 0) {
		if (error_text != NULL)
			MTIF_SUPP_AppendSpecErrorString(error_code,
				strcat(strcat(strcpy(tmp_error_text,
				"Attempt to retrieve the current Posix thread scheduling "),
				"policy and scheduling policy parameters using "),
				"'pthread_getschedparam()' failed: "));
		return_code = MTIF_SYSTEM_FAILURE;
	}
	else {
		tmp_sched_param.sched_priority = native_priority;
		if ((error_code = pthread_setschedparam(thread_id, tmp_policy,
			&tmp_sched_param)) != 0) {
			if (error_text != NULL)
				MTIF_SUPP_AppendSpecErrorString(error_code,
					strcat(strcat(strcpy(tmp_error_text,
					"Attempt to specify the Posix thread scheduling "),
					"policy and scheduling policy parameters using "),
				"'pthread_setschedparam()' failed: "));
			return_code = MTIF_OP_FAILURE_THR;
		}
		else
			return_code = MTIF_SUCCESS;
	}

	if ((return_code != MTIF_SUCCESS) && (error_text != NULL))
		sprintf(error_text, "%s %s failed: %s.",
			"Attempt to change the thread priority for",
			MTIF_THR_GetThreadText(thr_handle_ptr, thread_id_text),
			tmp_error_text);

	return(return_code);	
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int MTIF_THR_PriorityToNative(MTIF_THR_HANDLE *thr_handle_ptr,
	MTIF_THR_PRIORITY mtif_priority, MTIF_THR_PRIORITY_NATIVE *native_priority,
	char *error_text)
#else
int MTIF_THR_PriorityToNative(thr_handle_ptr, mtif_priority, native_priority,
	error_text)
MTIF_THR_HANDLE          *thr_handle_ptr;
MTIF_THR_PRIORITY         mtif_priority;
MTIF_THR_PRIORITY_NATIVE *native_priority;
char                     *error_text;
#endif /* #ifndef NARGS */
{
	return(MTIF_THR_PriorityToNativeGeneric(thr_handle_ptr, mtif_priority,
		native_priority, error_text));
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int MTIF_THR_PriorityFromNative(MTIF_THR_HANDLE *thr_handle_ptr,
	MTIF_THR_PRIORITY_NATIVE native_priority, MTIF_THR_PRIORITY *mtif_priority,
	char *error_text)
#else
int MTIF_THR_PriorityFromNative(thr_handle_ptr, native_priority, mtif_priority,
	error_text)
MTIF_THR_HANDLE          *thr_handle_ptr;
MTIF_THR_PRIORITY_NATIVE  native_priority;
MTIF_THR_PRIORITY        *mtif_priority;
char                     *error_text;
#endif /* #ifndef NARGS */
{
	return(MTIF_THR_PriorityFromNativeGeneric(thr_handle_ptr, native_priority,
		mtif_priority, error_text));
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int MTIF_THR_GetPriorityMinNative(MTIF_THR_HANDLE *thr_handle_ptr,
	MTIF_THR_PRIORITY_NATIVE *min_priority, char *error_text)
#else
int MTIF_THR_GetPriorityMinNative(thr_handle_ptr, min_priority, error_text)
MTIF_THR_HANDLE          *thr_handle_ptr;
MTIF_THR_PRIORITY_NATIVE *min_priority;
char                     *error_text;
#endif /* #ifndef NARGS */
{
	int                      return_code;
	int                      error_code;
	pthread_t                thread_id;
	int                      tmp_policy;
	struct sched_param       tmp_sched_param;
	MTIF_THR_PRIORITY_NATIVE tmp_priority;
	char                     thread_id_text[MTIF_THR_ID_TEXT_LENGTH + 1];
	char                     tmp_error_text[MTIF_MAX_ERROR_TEXT];

	thread_id = MTIF_THR_GET_OS_ID_DEFAULT(thr_handle_ptr);

	if ((error_code = pthread_getschedparam(thread_id, &tmp_policy,
		&tmp_sched_param)) != 0) {
		if (error_text != NULL)
			MTIF_SUPP_AppendSpecErrorString(error_code, strcat(strcpy(error_text,
				"Attempt to get the thread scheduling policy with "),
				"'pthread_getschedparam()' failed: "));
		return_code = MTIF_SYSTEM_FAILURE;
	}
	else if ((tmp_priority = sched_get_priority_min(tmp_policy)) != -1) {
		*min_priority = tmp_priority;
		return_code   = MTIF_SUCCESS;
	}
	else {
		if (error_text != NULL)
			MTIF_SUPP_AppendLastErrorString(
				strcat(val2str_sint_cat(tmp_policy, 10, NULL, strcpy(error_text,
		"Attempt to get the minimum thread priority for scheduling policy ")),
				" with 'sched_get_priority_min()' failed: "));
		return_code = MTIF_SYSTEM_FAILURE;
	}

	if ((return_code != MTIF_SUCCESS) && (error_text != NULL))
		MTIF_SUPP_AppendSpecErrorString(error_code,
			strcat(strcat(strcat(strcpy(error_text,
			"Unable to determine the implementation minimum thread priority for "),
			MTIF_THR_GetThreadText(thr_handle_ptr, thread_id_text)), " failed: "),
			tmp_error_text));

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int MTIF_THR_GetPriorityMaxNative(MTIF_THR_HANDLE *thr_handle_ptr,
	MTIF_THR_PRIORITY_NATIVE *max_priority, char *error_text)
#else
int MTIF_THR_GetPriorityMaxNative(thr_handle_ptr, max_priority, error_text)
MTIF_THR_HANDLE          *thr_handle_ptr;
MTIF_THR_PRIORITY_NATIVE *max_priority;
char                     *error_text;
#endif /* #ifndef NARGS */
{
	int                      return_code;
	int                      error_code;
	pthread_t                thread_id;
	int                      tmp_policy;
	struct sched_param       tmp_sched_param;
	MTIF_THR_PRIORITY_NATIVE tmp_priority;
	char                     thread_id_text[MTIF_THR_ID_TEXT_LENGTH + 1];
	char                     tmp_error_text[MTIF_MAX_ERROR_TEXT];

	thread_id = MTIF_THR_GET_OS_ID_DEFAULT(thr_handle_ptr);

	if ((error_code = pthread_getschedparam(thread_id, &tmp_policy,
		&tmp_sched_param)) != 0) {
		if (error_text != NULL)
			MTIF_SUPP_AppendSpecErrorString(error_code, strcat(strcpy(error_text,
				"Attempt to get the thread scheduling policy with "),
				"'pthread_getschedparam()' failed: "));
		return_code = MTIF_SYSTEM_FAILURE;
	}
	else if ((tmp_priority = sched_get_priority_max(tmp_policy)) != -1) {
		*max_priority = tmp_priority;
		return_code   = MTIF_SUCCESS;
	}
	else {
		if (error_text != NULL)
			MTIF_SUPP_AppendLastErrorString(
				strcat(val2str_sint_cat(tmp_policy, 10, NULL, strcpy(error_text,
		"Attempt to get the maximum thread priority for scheduling policy ")),
				" with 'sched_get_priority_max()' failed: "));
		return_code = MTIF_SYSTEM_FAILURE;
	}

	if ((return_code != MTIF_SUCCESS) && (error_text != NULL))
		MTIF_SUPP_AppendSpecErrorString(error_code,
			strcat(strcat(strcat(strcpy(error_text,
			"Unable to determine the implementation maximum thread priority for "),
			MTIF_THR_GetThreadText(thr_handle_ptr, thread_id_text)), " failed: "),
			tmp_error_text));

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
static int MTIF_THR_GetPriorityMapNativeInternal(
	MTIF_THR_HANDLE *thr_handle_ptr, unsigned int allocated_count,
	MTIF_THR_PRIORITY_MAP *allocated_list, unsigned int *out_count,
	MTIF_THR_PRIORITY_MAP **out_list, char *error_text)
#else
static int MTIF_THR_GetPriorityMapNativeInternal(thr_handle_ptr,
	allocated_count, allocated_list, out_count, out_list, error_text)
MTIF_THR_HANDLE        *thr_handle_ptr;
unsigned int            allocated_count;
MTIF_THR_PRIORITY_MAP  *allocated_list;
unsigned int           *out_count;
MTIF_THR_PRIORITY_MAP **out_list;
char                   *error_text;
#endif /* #ifndef NARGS */
{
	return(MTIF_THR_GetPriorityMapNativeGeneric(thr_handle_ptr, allocated_count,
		allocated_list, out_count, out_list, error_text));
}
/* *********************************************************************** */
#else
#endif /* #ifdef _Windows */

/* *********************************************************************** */
#ifndef NARGS
static int MTIF_THR_CheckSetPriority(MTIF_THR_HANDLE *thr_handle_ptr,
	MTIF_THR_PRIORITY mtif_priority, char *error_text)
#else
static int MTIF_THR_CheckSetPriority(thr_handle_ptr, mtif_priority, error_text)
MTIF_THR_HANDLE   *thr_handle_ptr;
MTIF_THR_PRIORITY  mtif_priority;
char              *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code;
	char thread_id_text[MTIF_THR_ID_TEXT_LENGTH + 1];
	char tmp_error_text[MTIF_MAX_ERROR_TEXT];

	if (mtif_priority == MTIF_THR_PRIORITY_NONE) {
		if (error_text != NULL)
			sprintf(tmp_error_text, "Thread priority may not be set to '%s' (%d).",
				"MTIF_THR_PRIORITY_NONE", mtif_priority);
		return_code = MTIF_OP_FAILURE_THR;
	}
	else if ((mtif_priority < MTIF_THR_PRIORITY_MINIMUM) ||
		(mtif_priority > MTIF_THR_PRIORITY_MAXIMUM)) {
		if (error_text != NULL)
			sprintf(tmp_error_text,
				"%s (%d) --- %s %d ('%s%s') to %d ('%s%s'), inclusive.",
				"Invalid thread priority encountered", ((int) mtif_priority),
				"thread priorities must be in the range of",
				((int) MTIF_THR_PRIORITY_MINIMUM), "MTIF_THR_PRIORITY_",
				MTIF_GET_THR_PRIORITY_NAME(MTIF_THR_PRIORITY_MINIMUM),
				((int) MTIF_THR_PRIORITY_MAXIMUM), "MTIF_THR_PRIORITY_",
				MTIF_GET_THR_PRIORITY_NAME(MTIF_THR_PRIORITY_MAXIMUM));
		return_code = MTIF_OP_FAILURE_THR;
	}
	else
		return_code = MTIF_SUCCESS;

	if ((return_code != MTIF_SUCCESS) && (error_text != NULL))
		strcat(strcat(strcat(strcpy(error_text, "Attempt to set "),
			MTIF_THR_GetThreadText(thr_handle_ptr, thread_id_text)),
			" priority failed: "), tmp_error_text);

	return(return_code);	
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
static int MTIF_THR_AllocPriorityMap(unsigned int new_count,
	unsigned int *out_count, MTIF_THR_PRIORITY_MAP **out_list,
	char *error_text)
#else
static int MTIF_THR_AllocPriorityMap(new_count, out_count, out_list,
	error_text)
unsigned int            new_count;
unsigned int           *out_count;
MTIF_THR_PRIORITY_MAP **out_list; 
char                   *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((*out_list = ((MTIF_THR_PRIORITY_MAP *) calloc(new_count,
		sizeof(MTIF_THR_PRIORITY_MAP)))) != NULL) {
		*out_count  = new_count;
		return_code = MTIF_SUCCESS;
	}
	else {
		if (error_text != NULL)
			STR_AllocMsgList(new_count, sizeof(MTIF_THR_PRIORITY_MAP), error_text,
				"Unable to allocate native thread priority mapping list");
		return_code = MTIF_MEMORY_FAILURE;
	}

	return(return_code);
}
/* *********************************************************************** */

#ifndef _Windows
/*
	ADF NOTE:	The functions 'MTIF_THR_PriorityToNativeGeneric()' and
					'MTIF_THR_PriorityFromNativeGeneric()' within this 'if/endif'
					block aren't used for Windows NT. This is because the number
					of priorities available is known beforehand (7), so it has
					it's own private case statement.
*/
/* *********************************************************************** */
#ifndef NARGS
static int MTIF_THR_PriorityToNativeGeneric(MTIF_THR_HANDLE *thr_handle_ptr,
	MTIF_THR_PRIORITY mtif_priority, MTIF_THR_PRIORITY_NATIVE *native_priority,
	char *error_text)
#else
static int MTIF_THR_PriorityToNativeGeneric(thr_handle_ptr, mtif_priority,
	native_priority, error_text)
MTIF_THR_HANDLE          *thr_handle_ptr;
MTIF_THR_PRIORITY         mtif_priority;
MTIF_THR_PRIORITY_NATIVE *native_priority;
char                     *error_text;
#endif /* #ifndef NARGS */
{
	int                    return_code = MTIF_SUCCESS;
	int                    found_flag;
	unsigned int           count_1;
	unsigned int           tmp_count;
	MTIF_THR_PRIORITY_MAP *tmp_list;
	MTIF_THR_PRIORITY_MAP  allocated_list[256];

	if ((return_code = MTIF_THR_GetPriorityMapNativeInternal(thr_handle_ptr,
		sizeof(allocated_list) / sizeof(allocated_list[0]), allocated_list,
		&tmp_count, &tmp_list, error_text)) == MTIF_SUCCESS) {
		found_flag = MTIF_FALSE;
		for (count_1 = 0; count_1 < tmp_count; count_1++) {
			if (tmp_list[count_1].mtif_priority == mtif_priority) {
				*native_priority = tmp_list[count_1].native_priority;
				found_flag       = MTIF_TRUE;
				break;
			}
		}
		if (tmp_list != allocated_list)
			free(allocated_list);
		if (found_flag != MTIF_TRUE) {
			if (error_text != NULL)
				sprintf(error_text,
					"Unable to map MTIF thread priority value (%d).",
					((int) mtif_priority));
			return_code = MTIF_OP_FAILURE_THR;
		}
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
static int MTIF_THR_PriorityFromNativeGeneric(MTIF_THR_HANDLE *thr_handle_ptr,
	MTIF_THR_PRIORITY_NATIVE native_priority, MTIF_THR_PRIORITY *mtif_priority,
	char *error_text)
#else
static int MTIF_THR_PriorityFromNativeGeneric(thr_handle_ptr, native_priority,
	mtif_priority, error_text)
MTIF_THR_HANDLE          *thr_handle_ptr;
MTIF_THR_PRIORITY_NATIVE  native_priority;
MTIF_THR_PRIORITY        *mtif_priority;
char                     *error_text;
#endif /* #ifndef NARGS */
{
	int                    return_code = MTIF_SUCCESS;
	int                    found_flag;
	unsigned int           count_1;
	unsigned int           tmp_count;
	MTIF_THR_PRIORITY_MAP *tmp_list;
	MTIF_THR_PRIORITY_MAP  allocated_list[256];

	if ((return_code = MTIF_THR_GetPriorityMapNativeInternal(thr_handle_ptr,
		sizeof(allocated_list) / sizeof(allocated_list[0]), allocated_list,
		&tmp_count, &tmp_list, error_text)) == MTIF_SUCCESS) {
		found_flag = MTIF_FALSE;
		for (count_1 = 0; count_1 < tmp_count; count_1++) {
			if (tmp_list[count_1].native_priority == native_priority) {
				*mtif_priority = tmp_list[count_1].match_priority;
				found_flag     = MTIF_TRUE;
				break;
			}
		}
		if (tmp_list != allocated_list)
			free(allocated_list);
		if (found_flag != MTIF_TRUE) {
			if (error_text != NULL)
				sprintf(error_text,
					"Unable to map native thread priority value (%ld).",
					((long) native_priority));
			return_code = MTIF_OP_FAILURE_THR;
		}
	}

	return(return_code);
}
/* *********************************************************************** */
#endif /* #ifndef _Windows */

#ifdef MTIF_THR_PRIORITY_SEQUENTIAL
/*
	ADF NOTE:	The functions defined within this 'if/endif' block don't work
					for thread priorities which are not ordered sequentially.

					Win32, for example . . .
*/
/* *********************************************************************** */
#ifndef NARGS
static int MTIF_THR_GetPriorityMapNativeGeneric(
	MTIF_THR_HANDLE *thr_handle_ptr, unsigned int allocated_count,
	MTIF_THR_PRIORITY_MAP *allocated_list, unsigned int *out_count,
	MTIF_THR_PRIORITY_MAP **out_list, char *error_text)
#else
int MTIF_THR_GetPriorityMapNativeGeneric(thr_handle_ptr, allocated_count,
	allocated_list, out_count, out_list, error_text)
MTIF_THR_HANDLE        *thr_handle_ptr;
unsigned int            allocated_count;
MTIF_THR_PRIORITY_MAP  *allocated_list;
unsigned int           *out_count;
MTIF_THR_PRIORITY_MAP **out_list;
char                   *error_text;
#endif /* #ifndef NARGS */
{
	int                      return_code;
	unsigned int             count_1;
	unsigned int             priority_count;
	unsigned int             step_size;
	MTIF_THR_PRIORITY_NATIVE min_priority;
	MTIF_THR_PRIORITY_NATIVE max_priority;

	if ((return_code = MTIF_THR_GetPriorityMinMaxNative(thr_handle_ptr,
		&min_priority, &max_priority, error_text)) == MTIF_SUCCESS) {
		priority_count = (max_priority - min_priority) + 1;
		/*	Too much trouble to do this for fewer than 7 priorities.	*/
		if (priority_count < MTIF_THR_PRIORITY_COUNT) {
			if (error_text != NULL)
				sprintf(error_text, "%s (%u) %s --- %s is %d.",
					"The number of native implementation thread priorities",
					priority_count, "are too few to map to MTIF thread priorities",
					"the minimum number of native implementation thread priorities",
					((int) MTIF_THR_PRIORITY_COUNT));
			return_code = MTIF_FAILURE;
		}
		else if ((allocated_count >= priority_count) ||
			((return_code = MTIF_THR_AllocPriorityMap(priority_count,
			out_count, out_list, error_text)) == MTIF_SUCCESS)) {
			*out_count  = priority_count;
			*out_list   = (allocated_count >= priority_count) ? allocated_list :
				*out_list;
			return_code = MTIF_SUCCESS;
			for (count_1 = 0; count_1 < priority_count; count_1++) {
				(*out_list)[count_1].match_priority  = ((MTIF_THR_PRIORITY) (((int)
					floor((((((double) (count_1 + 1)) / ((double) priority_count)) *
					((double) (MTIF_THR_PRIORITY_COUNT - 1)) * 100.0) + 49.9) /
					100.0)) + 1));
				(*out_list)[count_1].native_priority = min_priority +
					((MTIF_THR_PRIORITY_NATIVE) count_1);
			}
			step_size                                                         =
				(priority_count / 2) / ((MTIF_THR_PRIORITY_COUNT - 1) / 2);
			(*out_list)[0].mtif_priority                                      =
				MTIF_THR_PRIORITY_LOWEST;
			(*out_list)[(priority_count / 2) - (step_size * 2)].mtif_priority =
				MTIF_THR_PRIORITY_LOWER;
			(*out_list)[(priority_count / 2) - step_size].mtif_priority       =
				MTIF_THR_PRIORITY_LOW;
			(*out_list)[priority_count / 2].mtif_priority                     =
				MTIF_THR_PRIORITY_MEDIUM;
			(*out_list)[(priority_count / 2) + step_size].mtif_priority       =
				MTIF_THR_PRIORITY_HIGH;
			(*out_list)[(priority_count / 2) + (step_size * 2)].mtif_priority =
				MTIF_THR_PRIORITY_HIGHER;
			(*out_list)[priority_count - 1].mtif_priority                     =
				MTIF_THR_PRIORITY_HIGHEST;
		}
	}

	return(return_code);
}
/* *********************************************************************** */
#endif /* #ifdef MTIF_THR_PRIORITY_SEQUENTIAL */

#ifdef TEST_MAIN

#include <stdio.h>

static int  MTIF_TEST_ErrorCode;
static char MTIF_TEST_ErrorText[MTIF_MAX_ERROR_TEXT];

COMPAT_FN_DECL(int          main, (int argc, char **argv));
COMPAT_FN_DECL_STATIC(int   TEST_RunTest,
	(const char *thr_name, MTIF_THR_HANDLE *thr_handle_ptr, char *error_text));
COMPAT_FN_DECL_STATIC(void *TEST_TestStartFunc, (void *start_data));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int                    return_code = MTIF_SUCCESS;
	unsigned int           map_count   = 0;
	MTIF_THR_PRIORITY_MAP *map_list    = NULL;
	unsigned int           count_1;
	MTIF_THR_HANDLE        test_thread;
	char                   error_text[MTIF_MAX_ERROR_TEXT];
	char                   tmp_error_text[MTIF_MAX_ERROR_TEXT];

	fprintf(stderr, "Test harness routine for 'MTIF_THR_GetPriority()'\n");
	fprintf(stderr, "                         'MTIF_THR_SetPriority()'\n");
	fprintf(stderr, "---- ------- ------- --- ------------------------\n\n");

	fprintf(stderr, "Threading implementation: %s\n\n",
		MTIF_THR_IMPLEMENTATION_NAME);

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if ((!stricmp(argv[count_1], "-HELP")) ||
			(!stricmp(argv[count_1], "-H"))) {
			fprintf(stderr, "\n\nUSAGE:\n   %s [ -h | -help ]", argv[0]);
			goto EXIT_FUNCTION;
		}
	}

	if (argc > 1) {
		strcpy(error_text, "Invalid command-line encountered --- use '-h'.");
		return_code = MTIF_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((return_code = MTIF_THR_GetPriorityMapNative(NULL, &map_count,
		&map_list, error_text)) != MTIF_SUCCESS)
		goto EXIT_FUNCTION;

	STR_EMIT_CharLine('*', 78, NULL, NULL);
	STR_EMIT_CharLine('*', 78, NULL, NULL);
	printf("MTIF/%s Thread Priority Mapping\n", MTIF_THR_IMPLEMENTATION_NAME);
	STR_EMIT_CharLine('*', 78, NULL, NULL);

	STR_EMIT_CharLine('=', 78, NULL, NULL);
	printf("%10.10s %-8.8s %11.11s %-8.8s %11.11s %11.11s\n",
		"Priority", "MTIF", "MTIF", "Match", "Match", "Native");
	printf("%10.10s %-8.8s %11.11s %-8.8s %11.11s %11.11s\n",
		"Index", "Name", "Value", "Name", "Value", "Value");
	STR_EMIT_CharSpace('-', 10, NULL, NULL);
	STR_EMIT_CharSpace('-',  8, NULL, NULL);
	STR_EMIT_CharSpace('-', 11, NULL, NULL);
	STR_EMIT_CharSpace('-',  8, NULL, NULL);
	STR_EMIT_CharSpace('-', 11, NULL, NULL);
	STR_EMIT_CharLine ('-', 11, NULL, NULL);
	for (count_1 = 0; count_1 < map_count; count_1++)
		printf("%10u %-8.8s %11d %-8.8s %11d %11ld\n", count_1,
			(map_list[count_1].mtif_priority != MTIF_THR_PRIORITY_NONE) ?
				MTIF_GET_THR_PRIORITY_NAME(map_list[count_1].mtif_priority) :
				"",
			map_list[count_1].mtif_priority,
			MTIF_GET_THR_PRIORITY_NAME(map_list[count_1].match_priority),
			map_list[count_1].match_priority,
			((long) map_list[count_1].native_priority));
	STR_EMIT_CharSpace('-', 10, NULL, NULL);
	STR_EMIT_CharSpace('-',  8, NULL, NULL);
	STR_EMIT_CharSpace('-', 11, NULL, NULL);
	STR_EMIT_CharSpace('-',  8, NULL, NULL);
	STR_EMIT_CharSpace('-', 11, NULL, NULL);
	STR_EMIT_CharLine ('-', 11, NULL, NULL);
	STR_EMIT_CharLine('=', 78, NULL, NULL);
	STR_EMIT_CharLine('*', 78, NULL, NULL);
	printf("\n");

	MTIF_TEST_ErrorCode    = MTIF_SUCCESS;
	MTIF_TEST_ErrorText[0] = '\0';
	printf("Starting unbound thread for priority setting test ");
	fflush(stdout);
	if ((return_code = MTIF_THR_Create(MTIF_THR_FLAG_NONE, 0,
		TEST_TestStartFunc, &test_thread, &test_thread,
		tmp_error_text)) != MTIF_SUCCESS) {
		sprintf(error_text,
	"Attempt to create new unbound thread for priority setting test failed: %s",
			tmp_error_text);
		goto EXIT_FUNCTION;
	}
	else if ((return_code = MTIF_THR_Join(&test_thread, NULL,
		tmp_error_text)) != MTIF_SUCCESS) {
		sprintf(error_text, "%s failed: %s",
	"Attempt to get status from unbound thread for priority setting test thread",
			tmp_error_text);
		goto EXIT_FUNCTION;
	}
	else if (MTIF_TEST_ErrorCode == MTIF_SUCCESS) {
		sprintf(error_text, "Unbound thread priority setting succeeded.");
		printf("***** EXPECTED BEHAVIOR *****\n\n");
	}
	else {
		sprintf(error_text,
			"Unbound thread priority setting failed with %d: %s\n",
			MTIF_TEST_ErrorCode, MTIF_TEST_ErrorText);
		printf("***** NOT EXPECTED BEHAVIOR *****\n\n");
		return_code = MTIF_OP_FAILURE_THR;
		goto EXIT_FUNCTION;
	}

	if ((return_code = TEST_RunTest("Main thread", NULL, error_text)) !=
		MTIF_SUCCESS)
		goto EXIT_FUNCTION;

EXIT_FUNCTION:

	if (map_list != NULL)
		free(map_list);

	if (return_code != MTIF_SUCCESS) {
		fflush(stdout);
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
static int TEST_RunTest(const char *thr_name, MTIF_THR_HANDLE *thr_handle_ptr,
	char *error_text)
#else
static int TEST_RunTest(thr_name, thr_handle_ptr, error_text)
const char      *thr_name;
MTIF_THR_HANDLE *thr_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int                       return_code = MTIF_SUCCESS;
	unsigned int              map_count   = 0;
	MTIF_THR_PRIORITY_MAP    *map_list    = NULL;
	unsigned int              count_1;
	MTIF_THR_PRIORITY         mtif_priority_1;
	MTIF_THR_PRIORITY         mtif_priority_2;
	MTIF_THR_PRIORITY_NATIVE  native_priority_1;
	MTIF_THR_PRIORITY_NATIVE  native_priority_2;
	char                      priority_name[127 + 1];
	char                      thread_id_text[MTIF_THR_ID_TEXT_LENGTH + 1];

	STR_EMIT_CharLine('*', 78, NULL, NULL);
	STR_EMIT_CharLine('*', 78, NULL, NULL);
	printf("Thread Name: %s\n", thr_name);
	printf("Thread Id  : %s\n",
		initcaps(MTIF_THR_GetThreadText(thr_handle_ptr, thread_id_text)));
	STR_EMIT_CharLine('*', 78, NULL, NULL);

	STR_EMIT_CharLine('=', 78, NULL, NULL);
	printf("Set/Get MTIF Priority (%s)\n", thr_name);
	printf("--- --- ---- --------\n");
	STR_EMIT_CharLine('-', 78, NULL, NULL);

	for (mtif_priority_1 = MTIF_THR_PRIORITY_MINIMUM;
		mtif_priority_1 <= MTIF_THR_PRIORITY_MAXIMUM;
		mtif_priority_1 = ((MTIF_THR_PRIORITY) (((int) mtif_priority_1) + 1))) {
		strcat(strcpy(priority_name, "MTIF_GET_THR_PRIORITY_"),
				MTIF_GET_THR_PRIORITY_NAME(mtif_priority_1));
		printf(">>> | %-8.8s = %6d | ",
			MTIF_GET_THR_PRIORITY_NAME(mtif_priority_1), ((int) mtif_priority_1));
		if ((return_code = MTIF_THR_SetPriority(thr_handle_ptr, mtif_priority_1,
			error_text)) != MTIF_SUCCESS)
			goto EXIT_FUNCTION;
		printf("Set = %6d | ", ((int) mtif_priority_1));
		if ((return_code = MTIF_THR_GetPriority(thr_handle_ptr, &mtif_priority_2,
			error_text)) != MTIF_SUCCESS)
			goto EXIT_FUNCTION;
		printf("Get = %6d | ", ((int) mtif_priority_2));
		if ((return_code = MTIF_THR_PriorityToNative(thr_handle_ptr,
			mtif_priority_2, &native_priority_2, error_text)) != MTIF_SUCCESS)
			goto EXIT_FUNCTION;
		printf("Native = %6ld |\n", ((long) native_priority_2));
	}
	STR_EMIT_CharLine('=', 78, NULL, NULL);
	printf("\n");

	STR_EMIT_CharLine('=', 78, NULL, NULL);
	STR_EMIT_CharLine('=', 78, NULL, NULL);
	printf("Set/Get Native Priority (%s)\n", thr_name);
	printf("--- --- ------ --------\n");
	STR_EMIT_CharLine('-', 78, NULL, NULL);

	if ((return_code = MTIF_THR_GetPriorityMapNative(thr_handle_ptr, &map_count,
		&map_list, error_text)) != MTIF_SUCCESS)
		goto EXIT_FUNCTION;

	for (count_1 = 0; count_1 < map_count; count_1++) {
		native_priority_1 = map_list[count_1].native_priority;
		sprintf(priority_name, "[%6ld]", ((long) native_priority_1));
		printf(">>> | %-8.8s = %6ld | ", priority_name,
			((long) native_priority_1));
		if ((return_code = MTIF_THR_SetPriorityNative(thr_handle_ptr,
			native_priority_1, error_text)) != MTIF_SUCCESS)
			goto EXIT_FUNCTION;
		printf("Set = %6ld | ", ((long) native_priority_1));
		if ((return_code = MTIF_THR_GetPriorityNative(thr_handle_ptr,
			&native_priority_2, error_text)) != MTIF_SUCCESS)
			goto EXIT_FUNCTION;
		printf("Get = %6ld | ", ((long) native_priority_2));
		if ((return_code = MTIF_THR_PriorityFromNative(thr_handle_ptr,
			native_priority_2, &mtif_priority_2, error_text)) != MTIF_SUCCESS)
			goto EXIT_FUNCTION;
		printf("MTIF   = %6d |\n", ((int) mtif_priority_2));
	}
	STR_EMIT_CharLine('=', 78, NULL, NULL);

	STR_EMIT_CharLine('*', 78, NULL, NULL);
	STR_EMIT_CharLine('*', 78, NULL, NULL);
	printf("\n");

EXIT_FUNCTION:

	if (map_list != NULL)
		free(map_list);

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
void *TEST_TestStartFunc(void *start_data)
#else
static void *TEST_TestStartFunc(start_data)
void *start_data;
#endif /* #ifndef NARGS */
{
	char tmp_error_text[MTIF_MAX_ERROR_TEXT];

	printf("--- started thread %lu.\n", ((unsigned long) MTIF_THR_Self()));
	printf(">>> Attempting priority setting ");
	fflush(stdout);

	if ((MTIF_TEST_ErrorCode = TEST_RunTest("Subsidiary thread",
		NULL, tmp_error_text)) != MTIF_SUCCESS)
		strcat(strcpy(MTIF_TEST_ErrorText, "Subsidiary thread test failed: "),
			tmp_error_text);

	return(start_data);
}
/* *********************************************************************** */

#endif /* #ifdef TEST_MAIN */


