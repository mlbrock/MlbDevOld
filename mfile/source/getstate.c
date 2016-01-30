/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MFILE Memory-mapped I/O Library Source Code Module								*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets state members of an 'MFILE' structure.

	Revision History	:	1992-03-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/
 
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include "mfilei.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
#ifndef NARGS
const char *MFILE_GetFileName(MFILE *mfile_ptr)
#else
const char *MFILE_GetFileName(mfile_ptr)
MFILE *mfile_ptr;
#endif /* #ifndef NARGS */
{
	return(MFILE_GET_FILE_NAME_I(mfile_ptr));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
volatile void *MFILE_GetMMapPtr(MFILE *mfile_ptr)
#else
volatile void *MFILE_GetMMapPtr(mfile_ptr)
MFILE *mfile_ptr;
#endif /* #ifndef NARGS */
{
	return(MFILE_GET_MMAP_PTR_I(mfile_ptr));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MFILE_GetFileHandle(MFILE *mfile_ptr)
#else
int MFILE_GetFileHandle(mfile_ptr)
MFILE *mfile_ptr;
#endif /* #ifndef NARGS */
{
	return(MFILE_GET_FILE_HANDLE_I(mfile_ptr));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
FILE *MFILE_GetFileDescriptor(MFILE *mfile_ptr)
#else
FILE *MFILE_GetFileDescriptor(mfile_ptr)
MFILE *mfile_ptr;
#endif /* #ifndef NARGS */
{
	return(MFILE_GET_FILE_DESCRIPTOR_I(mfile_ptr));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
unsigned long MFILE_GetFileSize(MFILE *mfile_ptr)
#else
unsigned long MFILE_GetFileSize(mfile_ptr)
MFILE *mfile_ptr;
#endif /* #ifndef NARGS */
{
	return(MFILE_GET_FILE_SIZE_I(mfile_ptr));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
unsigned long MFILE_GetMMapSize(MFILE *mfile_ptr)
#else
unsigned long MFILE_GetMMapSize(mfile_ptr)
MFILE *mfile_ptr;
#endif /* #ifndef NARGS */
{
	return(MFILE_GET_MMAP_SIZE_I(mfile_ptr));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
unsigned long MFILE_GetOffset(MFILE *mfile_ptr)
#else
unsigned long MFILE_GetOffset(mfile_ptr)
MFILE *mfile_ptr;
#endif /* #ifndef NARGS */
{
	return(MFILE_GET_CURRENT_OFFSET_I(mfile_ptr));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
unsigned long MFILE_GetBufferSize(MFILE *mfile_ptr)
#else
unsigned long MFILE_GetBufferSize(mfile_ptr)
MFILE *mfile_ptr;
#endif /* #ifndef NARGS */
{
	return(MFILE_GET_BUFFER_SIZE_I(mfile_ptr));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MFILE_GetMFileFlags(MFILE *mfile_ptr)
#else
int MFILE_GetMFileFlags(mfile_ptr)
MFILE *mfile_ptr;
#endif /* #ifndef NARGS */
{
	return(MFILE_GET_MFILE_FLAGS_I(mfile_ptr));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MFILE_GetMMapProt(MFILE *mfile_ptr)
#else
int MFILE_GetMMapProt(mfile_ptr)
MFILE *mfile_ptr;
#endif /* #ifndef NARGS */
{
	return(MFILE_GET_MMAP_PROT_I(mfile_ptr));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MFILE_GetMMapFlags(MFILE *mfile_ptr)
#else
int MFILE_GetMMapFlags(mfile_ptr)
MFILE *mfile_ptr;
#endif /* #ifndef NARGS */
{
	return(MFILE_GET_MMAP_FLAGS_I(mfile_ptr));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MFILE_GetMMapMode(MFILE *mfile_ptr)
#else
int MFILE_GetMMapMode(mfile_ptr)
MFILE *mfile_ptr;
#endif /* #ifndef NARGS */
{
	return(MFILE_GET_MMAP_MODE_I(mfile_ptr));
}
/*	***********************************************************************	*/

