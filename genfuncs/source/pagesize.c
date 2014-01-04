/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	GENFUNCS General Functions Library Source Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Determines the system page size.

	Revision History	:	1994-02-25 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include "genfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_GetPageSize

   SYNOPSIS    :	page_size = GEN_GetPageSize();

						unsigned int page_size;

   DESCRIPTION :	Returns the operating system virtual memory sub-system page
						size.

   PARAMETERS  :	Void.

   RETURNS     :	Returns the system page size.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	GEN_GetAllocGranularity

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1994 - 2014 Michael L. Brock

   OUTPUT INDEX:	GEN_GetPageSize
						Miscellaneous Functions:GEN_GetPageSize
						GENFUNCS:Functions:GEN_GetPageSize
						GENFUNCS:Miscellaneous Functions:GEN_GetPageSize
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_GetPageSize

   PUBLISH NAME:	GEN_GetPageSize

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
unsigned int GEN_GetPageSize(void)
#else
unsigned int GEN_GetPageSize()
#endif /* #ifndef NARGS */
{
#ifdef __MSDOS__
	return(4096);
#elif _Windows
	SYSTEM_INFO system_data;

	GetSystemInfo(&system_data);

	return(((unsigned int) system_data.dwPageSize));
#elif __SVR4
#include <unistd.h>
	unsigned int page_size;

	return((((int) (page_size =
		((unsigned int) sysconf(_SC_PAGESIZE)))) == -1) ? 0 : page_size);
#else
#include <unistd.h>
	return(((unsigned int) getpagesize()));
#endif /* #ifdef __MSDOS__ */
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_GetAllocGranularity

   SYNOPSIS    :	alloc_gran = GEN_GetAllocGranularity();

						unsigned int alloc_gran;

   DESCRIPTION :	Returns the granularity with which the operating system
						allocates memory.

   PARAMETERS  :	Void.

   RETURNS     :	Returns the system page size.

   NOTES       :	In most environments, this function returns the same value
						as the related function ``GEN_GetPageSize``. Under Windows,
						it returns the ``dwAllocationGranularity`` member of the
						''SYSTEM_INFO'' structure.

   CAVEATS     :	

   SEE ALSO    :	GEN_GetPageSize

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1994 - 2014 Michael L. Brock

   OUTPUT INDEX:	GEN_GetAllocGranularity
						Miscellaneous Functions:GEN_GetAllocGranularity
						GENFUNCS:Functions:GEN_GetAllocGranularity
						GENFUNCS:Miscellaneous Functions:GEN_GetAllocGranularity
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_GetAllocGranularity

   PUBLISH NAME:	GEN_GetAllocGranularity

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
unsigned int GEN_GetAllocGranularity(void)
#else
unsigned int GEN_GetAllocGranularity()
#endif /* #ifndef NARGS */
{
#if _Windows
   SYSTEM_INFO system_data;

   GetSystemInfo(&system_data);

   return(((unsigned int) system_data.dwAllocationGranularity));
#else
   return(GEN_GetPageSize());
#endif /* #if _Windows */
}
/*	***********************************************************************	*/

