/* *********************************************************************** */
/* *********************************************************************** */
/*	GENFUNCS General Functions Library Source Module								*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Determines the validity of access for areas of memory.

	Revision History	:	1992-10-23 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/*    Include necessary header files . . .                                 */
/* *********************************************************************** */

#include <setjmp.h>
#include <signal.h>

#include "genfunci.h"

#ifdef _Windows
# include <limits.h>
# include <windows.h>
# include <winbase.h>
#endif /* #ifdef _Windows */

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Manifest constants, variables, and function prototypes used locally.	*/
/* *********************************************************************** */

#ifndef __MSDOS__
# ifndef _Windows
#  define GEN_VPTR_ACCESS_LONGJMP_SIG	0XAAAA

static jmp_buf GEN_VPTR_ACCESS_LongJmpEnv;

#  ifndef __SVR4
COMPAT_FN_DECL_STATIC(void GEN_VPTR_PtrAccessHandler, (int signal_number,
	int code, struct sigcontext *signal_context, char *address));
#  else
COMPAT_FN_DECL_STATIC(void GEN_VPTR_PtrAccessHandler, (int signal_number));
#  endif /* #   ifndef __SVR4 */
# endif /* # ifndef _Windows */
#endif /* #ifndef __MSDOS__ */

/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		If an attempt to access memory fails, we come here . . .					*/
/*	***********************************************************************	*/
#ifndef __MSDOS__
# ifndef _Windows
#  ifndef __SVR4
#    ifndef NARGS
static void GEN_VPTR_PtrAccessHandler(int signal_number, int code,
	struct sigcontext *signal_context, char *address)
#    else
static void GEN_VPTR_PtrAccessHandler(signal_number, code, signal_context,
	address)
int                signal_number;
int                code;
struct sigcontext *signal_context;
char              *address;
#    endif /* ifndef NARGS */
#  else
#   ifndef NARGS
static void GEN_VPTR_PtrAccessHandler(int signal_number)
#   else
static void GEN_VPTR_PtrAccessHandler(signal_number)
int signal_number;
#   endif /* ifndef NARGS */
#  endif /* #  ifndef __SVR4 */
{
	/* ********************************************************************	*/
	/* ********************************************************************	*/
	/* 	Restore the previous context . . .											*/
	/* ********************************************************************	*/
	longjmp(GEN_VPTR_ACCESS_LongJmpEnv, GEN_VPTR_ACCESS_LONGJMP_SIG);
	/* ********************************************************************	*/
}
# endif /* # ifndef _Windows */
#endif /* #ifndef __MSDOS__ */
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	GEN_VPTR_IsValidArea

	SYNOPSIS		:	return_code = GEN_VPTR_IsValidArea(area_ptr,
							area_length, access_mode, failure_ptr);

						int            return_code;

						void          *area_ptr;

						unsigned int   area_length;

						int            access_mode;

						void         **failure_ptr;

	DESCRIPTION	:	Determines the access validity of an area of memory.

   PARAMETERS  :  Parameters to this function are as follows:

						(.) ``area_ptr`` points to the area of memory to be
						validated.

						(.) ``area_length`` is the length of the area of memory to
						which the ``area_ptr`` parameter points.

						(-) if ``area_length`` is zero (''0'') it will be coerced
						to ''1''.

						(.) ``access_mode`` is the type of validity to be
						determined. The access mode is specified by using on of the
						following manifest constants:

						(..) ''GEN_VPTR_ACCESS_READ'' to specify that read access
						is to be determined.

						(..) ''GEN_VPTR_ACCESS_WRITE'' to specify that write access
						is to be determined.

						(..) ''GEN_VPTR_ACCESS_READ_WRITE'' to specify that both
						read and write access is to be determined.

						(-) If ``access_mode`` is not equal to one of the above
						manifest constants, it will be coerced to the value
						''GEN_VPTR_ACCESS_READ''.

						(.) ``failure_ptr`` points to a void pointer into which
						a pointer to the byte of memory at which the function
						detected a failed access attempt will be placed.

						(-) If ``failure_ptr`` is ''NULL'', no attempt will be
						made to dereference it.

   RETURNS     :  One of the following manifest constants:

						(.) ''GENFUNCS_TRUE'' if the specified area of memory can
						be accessed in the specified access mode.

						(.) ''GENFUNCS_FALSE'' if the specified area of memory can
						not be accessed in the specified access mode.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	GEN_VPTR_IsValidBoundary
						GEN_VPTR_IsValidPointer
						GEN_VPTR_IsValidSections
						GEN_VPTR_IsValidString

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2018 Michael L. Brock

	OUTPUT INDEX:	GEN_VPTR_IsValidArea
						Memory Validity Functions:GEN_VPTR_IsValidArea
						GENFUNCS:Functions:GEN_VPTR_IsValidArea
						GENFUNCS:Memory Validity Functions:GEN_VPTR_IsValidArea
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_VPTR_IsValidArea

	PUBLISH NAME:	GEN_VPTR_IsValidArea

	ENTRY CLASS	:	Memory Validity Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_VPTR_IsValidArea(void *area_ptr, unsigned int area_length,
	int access_mode, void **failure_ptr)
#else
int GEN_VPTR_IsValidArea(area_ptr, area_length, access_mode, failure_ptr)
void          *area_ptr;
unsigned int   area_length;
int            access_mode;
void         **failure_ptr;
#endif /* #ifndef NARGS */
{
#ifdef __MSDOS__
	return(GENFUNCS_TRUE);
#elif _Windows
	volatile int  return_code = GENFUNCS_TRUE;
	const char   *tmp_area_ptr;
	int           result;

	/* ********************************************************************	*/
	/* ********************************************************************	*/
	/* 	Rationalize the parameters by doing the following:						*/
	/*																								*/
	/*		1) Ensuring that the length of the area to be tested is at least	*/
	/*			one byte in length; and,													*/
	/*																								*/
	/*		2)	If no valid 'access_mode' parameter was passed, setting the		*/
	/*			access mode to be tested to 'GEN_VPTR_ACCESS_READ'.				*/
	/* ********************************************************************	*/
	area_length += (!area_length) ? 1 : 0;
	access_mode  = (!(access_mode & GEN_VPTR_ACCESS_READ_WRITE)) ?
		GEN_VPTR_ACCESS_READ : access_mode;
	/* ********************************************************************	*/

	/* ********************************************************************	*/
	/* ********************************************************************	*/
	/*		If we are checking for read access . . .								 	*/
	/* ********************************************************************	*/
	if (access_mode & GEN_VPTR_ACCESS_READ) {
		if (((result = IsBadReadPtr(area_ptr, area_length)) == FALSE) ||
			(failure_ptr == NULL))
			return_code = (result == FALSE) ? GENFUNCS_TRUE : GENFUNCS_FALSE;
		else {
			tmp_area_ptr = ((const char *) area_ptr);
			while (area_length--) {
				if (IsBadReadPtr(tmp_area_ptr, 1) != FALSE) {
					return_code = GENFUNCS_FALSE;
					break;
				}
				tmp_area_ptr++;
			}
		}
	}
	/* ********************************************************************	*/

	/* ********************************************************************	*/
	/* ********************************************************************	*/
	/*		If we are checking for write access . . .									*/
	/* ********************************************************************	*/
	if ((return_code == GENFUNCS_TRUE) &&
		(access_mode & GEN_VPTR_ACCESS_WRITE)) {
		if (((result = IsBadWritePtr(area_ptr, area_length)) == FALSE) ||
			(failure_ptr == NULL))
			return_code = (result == FALSE) ? GENFUNCS_TRUE : GENFUNCS_FALSE;
		else {
			tmp_area_ptr = ((const char *) area_ptr);
			while (area_length--) {
				if (IsBadWritePtr(((void  *) tmp_area_ptr), 1) != FALSE) {
					return_code = GENFUNCS_FALSE;
					break;
				}
				tmp_area_ptr++;
			}
		}
	}
	/* ********************************************************************	*/

	/* ********************************************************************	*/
	/* ********************************************************************	*/
	/*		If we do not have access to the area of memory, set 'failure_ptr'.*/
	/* ********************************************************************	*/
	if ((return_code == GENFUNCS_FAILURE) && (failure_ptr != NULL))
		*failure_ptr = ((void *) tmp_area_ptr);
	/* ********************************************************************	*/

	return(return_code);
#elif __SVR4
	int           return_code = GENFUNCS_TRUE;
	unsigned int  remaining_length;
	unsigned int  test_flags;
	int           pmap_flag;
	GEN_PMAP_DESC pmap_data;
	char          error_text[GENFUNCS_MAX_ERROR_TEXT];

	test_flags =
		((access_mode & GEN_VPTR_ACCESS_READ)  ? GEN_PMAP_FLAG_READ  : 0) |
		((access_mode & GEN_VPTR_ACCESS_WRITE) ? GEN_PMAP_FLAG_WRITE : 0);
	test_flags = (!test_flags) ? GEN_PMAP_FLAG_READ : test_flags;

	while (area_length) {
		if (((GEN_PMAP_LocateByAddress(-1, area_ptr, &pmap_flag, &pmap_data,
			error_text)) != GENFUNCS_SUCCESS) || (pmap_flag != GENFUNCS_TRUE) ||
			((pmap_data.flags & test_flags) != test_flags)) {
			if (failure_ptr != NULL)
				*failure_ptr = area_ptr;
			return_code = GENFUNCS_FALSE;
			break;
		}
		else if (area_length <= (remaining_length = (pmap_data.size -
			(((char *) area_ptr) - ((char *) pmap_data.address)))))
			break;
		area_ptr     = ((void *) (((char *) area_ptr) + remaining_length));
		area_length -= remaining_length;
	}

	return(return_code);
#else
	volatile int    return_code  = GENFUNCS_TRUE;
	volatile char   tmp_char     = 0;
	char           *tmp_area_ptr = ((char *) area_ptr);
#ifndef NARGS
	void          (*old_handler_1)(int);
	void          (*old_handler_2)(int);
#else
	void          (*old_handler_1)();
	void          (*old_handler_2)();
#endif /* #ifndef NARGS */

	old_handler_1 = signal(SIGBUS,  GEN_VPTR_PtrAccessHandler);
	old_handler_2 = signal(SIGSEGV, GEN_VPTR_PtrAccessHandler);

	/* ********************************************************************	*/
	/* ********************************************************************	*/
	/* 	Rationalize the parameters by doing the following:						*/
	/*																								*/
	/*		1) Ensuring that the length of the area to be tested is at least	*/
	/*			one byte in length; and,													*/
	/*																								*/
	/*		2)	If no valid 'access_mode' parameter was passed, setting the		*/
	/*			access mode to be tested to 'GEN_VPTR_ACCESS_READ'.				*/
	/* ********************************************************************	*/
	area_length += (!area_length) ? 1 : 0;
	access_mode  = (!(access_mode & GEN_VPTR_ACCESS_READ_WRITE)) ?
		GEN_VPTR_ACCESS_READ : access_mode;
	/* ********************************************************************	*/

	/* ********************************************************************	*/
	/* ********************************************************************	*/
	/* 	Save the current context with 'setjmp()' and probe the area to be	*/
	/* tested. An access violation will result in the 'else' clause being	*/
	/* executed.																				*/
	/* ********************************************************************	*/
	if (setjmp(GEN_VPTR_ACCESS_LongJmpEnv) != GEN_VPTR_ACCESS_LONGJMP_SIG) {
		while (area_length--) {
			tmp_char = *tmp_area_ptr;
			if (access_mode & GEN_VPTR_ACCESS_WRITE)
				*tmp_area_ptr = tmp_char;
			tmp_area_ptr++;
		}
	}
	else {
		if (failure_ptr != NULL)
			*failure_ptr = ((void *) tmp_area_ptr);
		return_code = GENFUNCS_FALSE;
	}

	/* ********************************************************************	*/
	/* ********************************************************************	*/
	/* 	Restore the previous signal handlers (if any).							*/
	/* ********************************************************************	*/
	signal(SIGBUS,  (old_handler_1) ? old_handler_1 : SIG_DFL);
	signal(SIGSEGV, (old_handler_2) ? old_handler_2 : SIG_DFL);
	/* ********************************************************************	*/

	return(return_code);
#endif /* #ifdef __MSDOS__ */
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	GEN_VPTR_IsValidBoundary

	SYNOPSIS		:	return_code = GEN_VPTR_IsValidBoundary(area_ptr,
							area_length, access_mode, failure_ptr);

						int            return_code;

						void          *area_ptr;

						unsigned int   area_length;

						int            access_mode;

						void         **failure_ptr;

	DESCRIPTION	:	Determines the access validity of the boundaries of an area
						of memory.

   PARAMETERS  :  Parameters to this function are as follows:

						(.) ``area_ptr`` points to the area of memory to be
						validated.

						(.) ``area_length`` is the length of the area of memory to
						which the ``area_ptr`` parameter points.

						(-) if ``area_length`` is zero (''0'') it will be coerced
						to ''1''.

						(.) ``access_mode`` is the type of validity to be
						determined. The access mode is specified by using on of the
						following manifest constants:

						(..) ''GEN_VPTR_ACCESS_READ'' to specify that read access
						is to be determined.

						(..) ''GEN_VPTR_ACCESS_WRITE'' to specify that write access
						is to be determined.

						(..) ''GEN_VPTR_ACCESS_READ_WRITE'' to specify that both
						read and write access is to be determined.

						(-) If ``access_mode`` is not equal to one of the above
						manifest constants, it will be coerced to the value
						''GEN_VPTR_ACCESS_READ''.

						(.) ``failure_ptr`` points to a void pointer into which
						a pointer to the byte of memory at which the function
						detected a failed access attempt will be placed.

						(-) If ``failure_ptr`` is ''NULL'', no attempt will be
						made to dereference it.

   RETURNS     :  One of the following manifest constants:

						(.) ''GENFUNCS_TRUE'' if the specified area of memory can
						be accessed in the specified access mode.

						(.) ''GENFUNCS_FALSE'' if the specified area of memory can
						not be accessed in the specified access mode.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	GEN_VPTR_IsValidArea
						GEN_VPTR_IsValidPointer
						GEN_VPTR_IsValidSections
						GEN_VPTR_IsValidString

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2018 Michael L. Brock

	OUTPUT INDEX:	GEN_VPTR_IsValidBoundary
						Memory Validity Functions:GEN_VPTR_IsValidBoundary
						GENFUNCS:Functions:GEN_VPTR_IsValidBoundary
						GENFUNCS:Memory Validity Functions:GEN_VPTR_IsValidBoundary
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_VPTR_IsValidBoundary

	PUBLISH NAME:	GEN_VPTR_IsValidBoundary

	ENTRY CLASS	:	Memory Validity Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_VPTR_IsValidBoundary(void *area_ptr, unsigned int area_length,
	int access_mode, void **failure_ptr)
#else
int GEN_VPTR_IsValidBoundary(area_ptr, area_length, access_mode,
	failure_ptr)
void          *area_ptr;
unsigned int   area_length;
int            access_mode;
void         **failure_ptr;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (((return_code = GEN_VPTR_IsValidArea(area_ptr, 1, access_mode,
		failure_ptr)) == GENFUNCS_TRUE) && (area_length > 1))
		return_code = GEN_VPTR_IsValidArea(((char *) area_ptr) +
			(area_length - 1), 1, access_mode, failure_ptr);

	return(return_code);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	GEN_VPTR_IsValidPointer

	SYNOPSIS		:	return_code = GEN_VPTR_IsValidPointer(area_ptr,
							access_mode, failure_ptr);

						int            return_code;

						void          *area_ptr;

						int            access_mode;

						void         **failure_ptr;

	DESCRIPTION	:	Determines the access validity of a byte of memory.

   PARAMETERS  :  Parameters to this function are as follows:

						(.) ``area_ptr`` points to the area of memory to be
						validated.

						(.) ``access_mode`` is the type of validity to be
						determined. The access mode is specified by using on of the
						following manifest constants:

						(..) ''GEN_VPTR_ACCESS_READ'' to specify that read access
						is to be determined.

						(..) ''GEN_VPTR_ACCESS_WRITE'' to specify that write access
						is to be determined.

						(..) ''GEN_VPTR_ACCESS_READ_WRITE'' to specify that both
						read and write access is to be determined.

						(-) If ``access_mode`` is not equal to one of the above
						manifest constants, it will be coerced to the value
						''GEN_VPTR_ACCESS_READ''.

						(.) ``failure_ptr`` points to a void pointer into which
						a pointer to the byte of memory at which the function
						detected a failed access attempt will be placed.

						(-) If ``failure_ptr`` is ''NULL'', no attempt will be
						made to dereference it.

	RETURNS     :  One of the following manifest constants:

						(.) ''GENFUNCS_TRUE'' if the specified area of memory can
						be accessed in the specified access mode.

						(.) ''GENFUNCS_FALSE'' if the specified area of memory can
						not be accessed in the specified access mode.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	GEN_VPTR_IsValidArea
						GEN_VPTR_IsValidBoundary
						GEN_VPTR_IsValidSections
						GEN_VPTR_IsValidString

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2018 Michael L. Brock

	OUTPUT INDEX:	GEN_VPTR_IsValidPointer
						Memory Validity Functions:GEN_VPTR_IsValidPointer
						GENFUNCS:Functions:GEN_VPTR_IsValidPointer
						GENFUNCS:Memory Validity Functions:GEN_VPTR_IsValidPointer
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_VPTR_IsValidPointer

	PUBLISH NAME:	GEN_VPTR_IsValidPointer

	ENTRY CLASS	:	Memory Validity Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_VPTR_IsValidPointer(void *area_ptr, int access_mode,
	void **failure_ptr)
#else
int GEN_VPTR_IsValidPointer(area_ptr, access_mode, failure_ptr)
void  *area_ptr;
int    access_mode;
void **failure_ptr;
#endif /* #ifndef NARGS */
{
	return(GEN_VPTR_IsValidArea(area_ptr, 1, access_mode, failure_ptr));
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	GEN_VPTR_IsValidSections

	SYNOPSIS		:	return_code = GEN_VPTR_IsValidSections(area_ptr,
							area_length, section_size, access_mode, failure_ptr);

						int            return_code;

						void          *area_ptr;

						unsigned int   area_length;

						unsigned int   section_size;

						int            access_mode;

						void         **failure_ptr;

	DESCRIPTION	:	Determines the access validity of an area of memory by
						checking the access validity of thew first byte of each of
						the sections which constitute that area of memory.

						It is assumed by this function if any part of a section is
						valid, the entire section is valid.

	PARAMETERS  :  Parameters to this function are as follows:

						(.) ``area_ptr`` points to the area of memory to be
						validated.

						(.) ``area_length`` is the length of the area of memory to
						which the ``area_ptr`` parameter points.

						(-) if ``area_length`` is zero (''0'') it will be coerced
						to ''1''.

						(.) ``section_size`` is the size of the sections which
						constitute the area of memory to which the ``area_ptr``
						parameter points.

						(.) ``access_mode`` is the type of validity to be
						determined. The access mode is specified by using on of the
						following manifest constants:

						(..) ''GEN_VPTR_ACCESS_READ'' to specify that read access
						is to be determined.

						(..) ''GEN_VPTR_ACCESS_WRITE'' to specify that write access
						is to be determined.

						(..) ''GEN_VPTR_ACCESS_READ_WRITE'' to specify that both
						read and write access is to be determined.

						(-) If ``access_mode`` is not equal to one of the above
						manifest constants, it will be coerced to the value
						''GEN_VPTR_ACCESS_READ''.

						(.) ``failure_ptr`` points to a void pointer into which
						a pointer to the byte of memory at which the function
						detected a failed access attempt will be placed.

						(-) If ``failure_ptr`` is ''NULL'', no attempt will be
						made to dereference it.

	RETURNS     :  One of the following manifest constants:

						(.) ''GENFUNCS_TRUE'' if the specified area of memory can
						be accessed in the specified access mode.

						(.) ''GENFUNCS_FALSE'' if the specified area of memory can
						not be accessed in the specified access mode.

	NOTES			:	Yeah, this function probably should be named
						``GEN_VPTR_AreValidSections``, but the naming consistency
						is nice.

	CAVEATS		:	

	SEE ALSO		:	GEN_VPTR_IsValidArea
						GEN_VPTR_IsValidBoundary
						GEN_VPTR_IsValidPointer
						GEN_VPTR_IsValidString

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2018 Michael L. Brock

	OUTPUT INDEX:	GEN_VPTR_IsValidSections
						Memory Validity Functions:GEN_VPTR_IsValidSections
						GENFUNCS:Functions:GEN_VPTR_IsValidSections
						GENFUNCS:Memory Validity Functions:GEN_VPTR_IsValidSections
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_VPTR_IsValidSections

	PUBLISH NAME:	GEN_VPTR_IsValidSections

	ENTRY CLASS	:	Memory Validity Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_VPTR_IsValidSections(void *area_ptr, unsigned int area_length,
	unsigned int section_size, int access_mode, void **failure_ptr)
#else
int GEN_VPTR_IsValidSections(area_ptr, area_length, section_size,
	access_mode, failure_ptr)
void          *area_ptr;
unsigned int   area_length;
unsigned int   section_size;
int            access_mode;
void         **failure_ptr;
#endif /* #ifndef NARGS */
{
	int          return_code = GENFUNCS_TRUE;
	unsigned int adj = 0;

	if ((area_length < 3) || (section_size < 2) ||
		(area_length < section_size))
		return_code = GEN_VPTR_IsValidArea(area_ptr, area_length,
			access_mode, failure_ptr);
	else {
		if ((!(((unsigned int) area_ptr) % section_size)) ||
			((return_code = GEN_VPTR_IsValidArea(area_ptr, adj =
			(section_size - (((unsigned int) area_ptr) % section_size)),
			access_mode, failure_ptr)) == GENFUNCS_TRUE)) {
			area_ptr  = ((char *) area_ptr) + adj;
			area_length  -= adj;
			while (area_length >= section_size) {
				if ((return_code = GEN_VPTR_IsValidArea(area_ptr, 1,
					access_mode, failure_ptr)) != GENFUNCS_TRUE)
					break;
				area_ptr  = ((char *) area_ptr) + section_size;
				area_length  -= section_size;
			}
			if (area_length && (return_code == GENFUNCS_TRUE))
				return_code = GEN_VPTR_IsValidArea(area_ptr, area_length,
					access_mode, failure_ptr);
		}
	}

	return(return_code);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	GEN_VPTR_IsValidString

	SYNOPSIS		:	return_code = GEN_VPTR_IsValidString(string_ptr,
							access_mode, failure_ptr);

						int    return_code;

						char  *string_ptr;

						int    access_mode;

						void **failure_ptr;

	DESCRIPTION	:	Determines the access validity of a string.

   PARAMETERS  :  Parameters to this function are as follows:

						(.) ``string_ptr`` points to the string to be validated.

						(.) ``access_mode`` is the type of validity to be
						determined. The access mode is specified by using on of the
						following manifest constants:

						(..) ''GEN_VPTR_ACCESS_READ'' to specify that read access
						is to be determined.

						(..) ''GEN_VPTR_ACCESS_WRITE'' to specify that write access
						is to be determined.

						(..) ''GEN_VPTR_ACCESS_READ_WRITE'' to specify that both
						read and write access is to be determined.

						(-) Note that ``access_mode`` will always be coerced to
						include the ''OR''ed value ''GEN_VPTR_ACCESS_READ''. This
						is because a NUL-terminated string must be readable in
						order to determine the location of the terminating
						ASCII NUL character.

						(.) ``failure_ptr`` points to a void pointer into which
						a pointer to the byte of memory at which the function
						detected a failed access attempt will be placed.

						(-) If ``failure_ptr`` is ''NULL'', no attempt will be
						made to dereference it.

   RETURNS     :  One of the following manifest constants:

						(.) ''GENFUNCS_TRUE'' if the specified string can be
						accessed in the specified access mode.

						(.) ''GENFUNCS_FALSE'' if the specified string can not be
						accessed in the specified access mode.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	GEN_VPTR_IsValidArea
						GEN_VPTR_IsValidBoundary
						GEN_VPTR_IsValidPointer
						GEN_VPTR_IsValidSections

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2018 Michael L. Brock

	OUTPUT INDEX:	GEN_VPTR_IsValidString
						Memory Validity Functions:GEN_VPTR_IsValidString
						GENFUNCS:Functions:GEN_VPTR_IsValidString
						GENFUNCS:Memory Validity Functions:GEN_VPTR_IsValidString
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_VPTR_IsValidString

	PUBLISH NAME:	GEN_VPTR_IsValidString

	ENTRY CLASS	:	Memory Validity Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_VPTR_IsValidString(char *string_ptr, int access_mode,
	void **failure_ptr)
#else
int GEN_VPTR_IsValidString(string_ptr, access_mode, failure_ptr)
char  *string_ptr;
int    access_mode;
void **failure_ptr;
#endif /* #ifndef NARGS */
{
#ifdef __MSDOS__
	return(GENFUNCS_TRUE);
#elif _Windows
	volatile int  return_code     = GENFUNCS_TRUE;
	unsigned int  tmp_area_length = 0;
	const char   *tmp_area_ptr;
	int           result;

	/* ********************************************************************	*/
	/* ********************************************************************	*/
	/* 	Strings must be readable in order to locate the terminating			*/
	/*	ASCII NUL character ('\0').														*/
	/* ********************************************************************	*/
	access_mode |= GEN_VPTR_ACCESS_READ;
	/* ********************************************************************	*/

	/* ********************************************************************	*/
	/* ********************************************************************	*/
	/*		Check for read access . . .								 					*/
	/* ********************************************************************	*/
	if (((result = IsBadStringPtr(string_ptr, UINT_MAX)) == FALSE) ||
		(failure_ptr == NULL))
		return_code = (result == FALSE) ? GENFUNCS_TRUE : GENFUNCS_FALSE;
	else {
		tmp_area_ptr = ((char *) string_ptr);
		while (1) {
			tmp_area_length++;
			if (IsBadReadPtr(tmp_area_ptr, 1) != FALSE) {
				if (failure_ptr != NULL)
					*failure_ptr = ((void *) tmp_area_ptr);
				return_code = GENFUNCS_FALSE;
				break;
			}
			else if (!(*tmp_area_ptr))
				break;
			tmp_area_ptr++;
		}
	}
	/* ********************************************************************	*/

	/* ********************************************************************	*/
	/* ********************************************************************	*/
	/*		If we are checking for write access . . .									*/
	/* ********************************************************************	*/
	if ((return_code == GENFUNCS_TRUE) &&
		(access_mode & GEN_VPTR_ACCESS_WRITE)) {
		if (tmp_area_length)
			return_code = GEN_VPTR_IsValidArea(string_ptr, tmp_area_length,
				GEN_VPTR_ACCESS_WRITE, failure_ptr);
		else {
			tmp_area_ptr = ((char *) string_ptr);
			while (1) {
				if (IsBadWritePtr(((void *) tmp_area_ptr), 1) != FALSE) {
					if (failure_ptr != NULL)
						*failure_ptr = ((void *) tmp_area_ptr);
					return_code = GENFUNCS_FALSE;
					break;
				}
				else if (!(*tmp_area_ptr))
					break;
				tmp_area_ptr++;
			}
		}
	}
	/* ********************************************************************	*/

	return(return_code);
#elif __SVR4
	int           return_code = GENFUNCS_TRUE;
	const char   *tmp_ptr;
	unsigned int  remaining_length;
	unsigned int  test_flags;
	int           pmap_flag;
	GEN_PMAP_DESC pmap_data;
	char          error_text[GENFUNCS_MAX_ERROR_TEXT];

	test_flags =
		((access_mode & GEN_VPTR_ACCESS_READ)  ? GEN_PMAP_FLAG_READ  : 0) |
		((access_mode & GEN_VPTR_ACCESS_WRITE) ? GEN_PMAP_FLAG_WRITE : 0);
	test_flags = (!test_flags) ? GEN_PMAP_FLAG_READ : test_flags;

	while (1) {
		if (((GEN_PMAP_LocateByAddress(-1, string_ptr, &pmap_flag, &pmap_data,
			error_text)) != GENFUNCS_SUCCESS) || (pmap_flag != GENFUNCS_TRUE) ||
			((pmap_data.flags & test_flags) != test_flags)) {
			if (failure_ptr != NULL)
				*failure_ptr = string_ptr;
			return_code = GENFUNCS_FALSE;
			break;
		}
		remaining_length = pmap_data.size -
			(string_ptr - ((char *) pmap_data.address));
		tmp_ptr     = string_ptr;
		string_ptr += remaining_length;
		while (remaining_length--) {
			if (!(*tmp_ptr))
				break;
			tmp_ptr++;
		}
		if (!(*tmp_ptr))
			break;
	}

	return(return_code);
#else
	volatile int   return_code = GENFUNCS_TRUE;
	volatile char  tmp_char    = 0;
#ifndef NARGS
	void          (*old_handler_1)(int);
	void          (*old_handler_2)(int);
#else
	void          (*old_handler_1)();
	void          (*old_handler_2)();
#endif /* #ifndef NARGS */

	old_handler_1 = signal(SIGBUS,  GEN_VPTR_PtrAccessHandler);
	old_handler_2 = signal(SIGSEGV, GEN_VPTR_PtrAccessHandler);

	/* ********************************************************************	*/
	/* ********************************************************************	*/
	/* 	Strings must be readable in order to locate the terminating			*/
	/*	ASCII NUL character ('\0').														*/
	/* ********************************************************************	*/
	access_mode |= GEN_VPTR_ACCESS_READ;
	/* ********************************************************************	*/

	/* ********************************************************************	*/
	/* ********************************************************************	*/
	/* 	Save the current context with 'setjmp()' and probe the area to be	*/
	/* tested. An access violation will result in the 'else' clause being	*/
	/* executed.																				*/
	/* ********************************************************************	*/
	if (setjmp(GEN_VPTR_ACCESS_LongJmpEnv) != GEN_VPTR_ACCESS_LONGJMP_SIG) {
		while (*string_ptr) {
			tmp_char = *string_ptr;
			if (access_mode & GEN_VPTR_ACCESS_WRITE)
				*string_ptr = tmp_char;
			string_ptr++;
		}
	}
	else {
		if (failure_ptr != NULL)
			*failure_ptr = string_ptr;
		return_code = GENFUNCS_FALSE;
	}

	/* ********************************************************************	*/
	/* ********************************************************************	*/
	/* 	Restore the previous signal handlers (if any).							*/
	/* ********************************************************************	*/
	signal(SIGBUS,  (old_handler_1) ? old_handler_1 : SIG_DFL);
	signal(SIGSEGV, (old_handler_2) ? old_handler_2 : SIG_DFL);
	/* ********************************************************************	*/

	return(return_code);
#endif /* #ifdef __MSDOS__ */
}
/* *********************************************************************** */

#ifdef TEST_MAIN

# ifdef _bsd
#  define GENFUNCS_VALIDPTR_TEST			1
# else
#  ifdef __SVR4
#   define GENFUNCS_VALIDPTR_TEST		1
#  else
#   define GENFUNCS_VALIDPTR_TEST		0
#  endif /* #  ifdef __SVR4 */
# endif /* #ifdef _bsd */

# if GENFUNCS_VALIDPTR_TEST

# include <errno.h>
# include <memory.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/mman.h>

COMPAT_FN_DECL(int main, (void));

int main()
{
	int     return_code = GENFUNCS_SUCCESS;
	void   *mmap_ptr    = NULL;
	FILE   *file_ptr    = NULL;
   double  tmp_double;
	char    error_text[GENFUNCS_MAX_ERROR_TEXT];

	printf("This PID = %lu\n", getpid());

	STR_EMIT_CharLine('=', 77, NULL, NULL);
	printf("Basic Memory Tests\n");
	STR_EMIT_CharLine('=', 77, NULL, NULL);
	printf("%-66.66s: %d\n",
		"GEN_VPTR_IsValidArea(((void *) 0), 1)",
		GEN_VPTR_IsValidArea(((void *) 0), 1, GEN_VPTR_ACCESS_READ, NULL));
	printf("%-66.66s: %d\n",
		"GEN_VPTR_IsValidArea(((void *) 1), 1)",
		GEN_VPTR_IsValidArea(((void *) 1), 1, GEN_VPTR_ACCESS_READ, NULL));
	printf("%-66.66s: %d\n",
		"GEN_VPTR_IsValidArea(&tmp_double, sizeof(tmp_double))",
		GEN_VPTR_IsValidArea(&tmp_double, sizeof(tmp_double),
		GEN_VPTR_ACCESS_READ, NULL));
	printf("%-66.66s: %d\n",
		"GEN_VPTR_IsValidArea(((void *) -1), 1)",
		GEN_VPTR_IsValidArea(((void *) -1), 1, GEN_VPTR_ACCESS_READ, NULL));
	STR_EMIT_CharLine('=', 77, NULL, NULL);

	if (!(file_ptr = fopen("ERASE.ME", "w+"))) {
		sprintf(error_text,
			"Unable to open test file 'ERASE.ME' for writing: ");
		GEN_AppendLastErrorString(0, GENFUNCS_MAX_ERROR_TEXT, error_text);
		return_code = GENFUNCS_SYSTEM_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if (ftruncate(fileno(file_ptr), getpagesize())) {
		sprintf(error_text,
			"Unable to 'ftruncate()' test file 'ERASE.ME' to %u bytes: ",
			getpagesize());
		GEN_AppendLastErrorString(0, GENFUNCS_MAX_ERROR_TEXT, error_text);
		return_code = GENFUNCS_SYSTEM_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if (((int) (mmap_ptr = ((char *) mmap(NULL, ((unsigned int) getpagesize()),
		PROT_READ, MAP_SHARED, fileno(file_ptr), 0)))) == -1) {
		sprintf(error_text,
			"Unable to 'mmap()' test file 'ERASE.ME' for %u bytes: ",
			getpagesize());
		GEN_AppendLastErrorString(0, GENFUNCS_MAX_ERROR_TEXT, error_text);
		return_code = GENFUNCS_SYSTEM_FAILURE;
		goto EXIT_FUNCTION;
	}

	STR_EMIT_CharLine('=', 77, NULL, NULL);
	printf("Mapped Area Tests\n");
	STR_EMIT_CharLine('-', 77, NULL, NULL);
	sprintf(error_text,
		"GEN_VPTR_IsValidArea(mmap_ptr, %u, GEN_VPTR_ACCESS_READ)",
		getpagesize());
	printf("%-66.66s: %d\n", error_text,
		GEN_VPTR_IsValidArea(mmap_ptr, ((unsigned int) getpagesize()),
		GEN_VPTR_ACCESS_READ, NULL));
	sprintf(error_text,
		"GEN_VPTR_IsValidArea(mmap_ptr, %u, GEN_VPTR_ACCESS_READ)",
		getpagesize() - 1);
	printf("%-66.66s: %d\n", error_text,
		GEN_VPTR_IsValidArea(mmap_ptr, ((unsigned int) getpagesize()) - 1,
		GEN_VPTR_ACCESS_READ, NULL));
	sprintf(error_text,
		"GEN_VPTR_IsValidArea(mmap_ptr, %u, GEN_VPTR_ACCESS_READ)",
		getpagesize() + 1);
	printf("%-66.66s: %d\n", error_text,
		GEN_VPTR_IsValidArea(mmap_ptr, ((unsigned int) getpagesize()) + 1,
		GEN_VPTR_ACCESS_READ, NULL));
	sprintf(error_text,
		"GEN_VPTR_IsValidArea(mmap_ptr, %u, GEN_VPTR_ACCESS_READ)",
		getpagesize() * 16);
	printf("%-66.66s: %d\n", error_text,
		GEN_VPTR_IsValidArea(mmap_ptr, ((unsigned int) getpagesize()) * 16 ,
		GEN_VPTR_ACCESS_READ, NULL));
	sprintf(error_text,
		"GEN_VPTR_IsValidArea(mmap_ptr, %u, GEN_VPTR_ACCESS_WRITE)",
		getpagesize());
	printf("%-66.66s: %d\n", error_text,
		GEN_VPTR_IsValidArea(mmap_ptr, ((unsigned int) getpagesize()),
		GEN_VPTR_ACCESS_WRITE, NULL));
	sprintf(error_text,
		"GEN_VPTR_IsValidArea(mmap_ptr, %u, GEN_VPTR_ACCESS_READ_WRITE)",
		getpagesize());
	printf("%-66.66s: %d\n", error_text,
		GEN_VPTR_IsValidArea(mmap_ptr, ((unsigned int) getpagesize()),
		GEN_VPTR_ACCESS_READ_WRITE, NULL));
	STR_EMIT_CharLine('=', 77, NULL, NULL);

	munmap(mmap_ptr, ((unsigned int) getpagesize()));
	fclose(file_ptr);
	mmap_ptr = NULL;
	file_ptr = NULL;

	STR_EMIT_CharLine('=', 77, NULL, NULL);
	printf("Mapped Area Tests (After Unmapping)\n");
	STR_EMIT_CharLine('-', 77, NULL, NULL);
	sprintf(error_text,
		"GEN_VPTR_IsValidArea(mmap_ptr, %u, GEN_VPTR_ACCESS_READ)",
		getpagesize());
	printf("%-66.66s: %d\n", error_text,
		GEN_VPTR_IsValidArea(mmap_ptr, ((unsigned int) getpagesize()),
		GEN_VPTR_ACCESS_READ, NULL));
	sprintf(error_text,
		"GEN_VPTR_IsValidArea(mmap_ptr, %u, GEN_VPTR_ACCESS_READ)",
		getpagesize() - 1);
	printf("%-66.66s: %d\n", error_text,
		GEN_VPTR_IsValidArea(mmap_ptr, ((unsigned int) getpagesize()) - 1,
		GEN_VPTR_ACCESS_READ, NULL));
	sprintf(error_text,
		"GEN_VPTR_IsValidArea(mmap_ptr, %u, GEN_VPTR_ACCESS_READ)",
		getpagesize() + 1);
	printf("%-66.66s: %d\n", error_text,
		GEN_VPTR_IsValidArea(mmap_ptr, ((unsigned int) getpagesize()) + 1,
		GEN_VPTR_ACCESS_READ, NULL));
	sprintf(error_text,
		"GEN_VPTR_IsValidArea(mmap_ptr, %u, GEN_VPTR_ACCESS_READ)",
		getpagesize() * 16);
	printf("%-66.66s: %d\n", error_text,
		GEN_VPTR_IsValidArea(mmap_ptr, ((unsigned int) getpagesize()) * 16 ,
		GEN_VPTR_ACCESS_READ, NULL));
	sprintf(error_text,
		"GEN_VPTR_IsValidArea(mmap_ptr, %u, GEN_VPTR_ACCESS_WRITE)",
		getpagesize());
	printf("%-66.66s: %d\n", error_text,
		GEN_VPTR_IsValidArea(mmap_ptr, ((unsigned int) getpagesize()),
		GEN_VPTR_ACCESS_WRITE, NULL));
	sprintf(error_text,
		"GEN_VPTR_IsValidArea(mmap_ptr, %u, GEN_VPTR_ACCESS_READ_WRITE)",
		getpagesize());
	printf("%-66.66s: %d\n", error_text,
		GEN_VPTR_IsValidArea(mmap_ptr, ((unsigned int) getpagesize()),
		GEN_VPTR_ACCESS_READ_WRITE, NULL));
	STR_EMIT_CharLine('=', 77, NULL, NULL);

/*
	printf("Now lets see if we still can cause a REAL segmentation fault:\n");
	tmp_double = *((double *) 0);
*/

EXIT_FUNCTION:

	if (mmap_ptr != NULL)
		munmap(mmap_ptr, ((unsigned int) getpagesize()));
	if (file_ptr != NULL)
		fclose(file_ptr);

	return(return_code);
}

# endif /* # if GENFUNCS_VALIDPTR_TEST */

#endif /* #ifdef TEST_MAIN */

