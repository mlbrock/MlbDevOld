/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MMAP Memory-mapped Interface Library Source Code Module						*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	

	Revision History	:	1992-03-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include <limits.h>

#include <genfuncs.h>

#include "mmap.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	

   SYNOPSIS    :	

   DESCRIPTION :	

   PARAMETERS  :	

   RETURNS     :	

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2015 Michael L. Brock

   OUTPUT INDEX:	
						Memory-mapped Interface Functions:See MMAP Library Functions
						MMAP Library Functions

   PUBLISH XREF:	

   PUBLISH NAME:	

	ENTRY CLASS	:	Memory-mapped Interface Functions

EOH */
/*	***********************************************************************	*/
#ifdef _Windows
void *MMAP_WIN32_Map(address, length, protect, map_flags, fd, offset)
void         *address;
unsigned int  length;
unsigned int  protect;
unsigned int  map_flags;
int           fd;
unsigned int  offset;
{
#if 1
	void   *out_address = ((void *) -1);
	DWORD   create_protect;
unsigned int offset_adj;
	HANDLE  file_handle;
	char    mapping_name[4 + 1 + 5 + 1 + 17 + 1 + 8 + 1 + 8 + 1 + 25 + 1];
	char    time_buffer[10 + 1 + 6 + 1 + 6 + 1];
	char    number_1[(sizeof(unsigned long) * CHAR_BIT) + 1 + 1];
	char    number_2[(sizeof(unsigned long) * CHAR_BIT) + 1 + 1];

	protect         = MMAP_ProtMapFlagsToWin32FileFlag(protect, map_flags);
	create_protect  = MMAP_ProtMapFlagsToWin32PageFlag(protect, map_flags);

protect        = FILE_MAP_WRITE | FILE_MAP_COPY;
create_protect = PAGE_READWRITE | PAGE_WRITECOPY;

offset_adj     = (offset % USHRT_MAX);

	strcat(strcat(strcat(strcat(strcat(strcpy(mapping_name,
		"MMAP_WIN32_CreateFileMapping_"),
		val2str(((unsigned long) fd), 0, 16, "0", number_1)),
		"_"),
		val2str(((unsigned long) &out_address), 0, 16, "0", number_2)),
		"_"),
		GEN_Format_timeval(NULL, time_buffer));

	if ((file_handle = CreateFileMapping(((HANDLE) fd), NULL,
		((DWORD) create_protect), ((DWORD) 0), ((DWORD) (length + offset_adj)),
		NULL)) != NULL)
/*
		((LPCTSTR) mapping_name))) != NULL)
*/
		out_address = MapViewOfFileEx(((HANDLE) file_handle),
			((DWORD) protect), ((DWORD) 0), ((DWORD) (offset - offset_adj)),
			((DWORD) length), ((LPVOID) address));
else
	fprintf(stderr, "\n ********** 'CreateFileMapping()' error: %d\n",
		GetLastError());
	return((out_address != NULL) ? out_address : ((void *) -1));
#else
	void *out_address;

	protect |= (map_flags & MMAP_MMAP_PRIVATE) ? FILE_MAP_COPY : 0;

	return(((out_address = MapViewOfFileEx(((HANDLE) fd), ((DWORD) protect),
		((DWORD) 0), ((DWORD) offset), ((DWORD) length), ((LPVOID) address))) !=
		NULL) ? out_address : ((void *) -1));
#endif /* #if 1 */
}
#endif /* #ifdef _Windows */
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	

   SYNOPSIS    :	

   DESCRIPTION :	

   PARAMETERS  :	

   RETURNS     :	

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2015 Michael L. Brock

   OUTPUT INDEX:	
						Memory-mapped Interface Functions:See MMAP Library Functions
						MMAP Library Functions

   PUBLISH XREF:	

   PUBLISH NAME:	

	ENTRY CLASS	:	Memory-mapped Interface Functions

EOH */
/*	***********************************************************************	*/
#ifdef _Windows
void *MMAP_WIN32_Protect(address, length, protect)
void         *address;
unsigned int  length;
unsigned int  protect;
{
	DWORD new_protect;
	DWORD old_protect;

	new_protect = MMAP_ProtFlagToWin32PageFlag(protect);

	return(((void *) ((VirtualProtect(((LPVOID) address), ((DWORD) length),
		new_protect, &old_protect)) ? 0 : -1)));
}
#endif /* #ifdef _Windows */
/*	***********************************************************************	*/

