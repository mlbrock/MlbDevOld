/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MMI Memory-mapped Interface Library Internal Include File					*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Internal include file for the Memory-mapped Interface
								Library (MMI).

	Revision History	:	1992-03-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__MMII_H__h

#define h__MMII_H__h						1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include "mmi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	MMI Library Version Number

   NAME        :	MMI Library Version Number

   DESCRIPTION :	The MMI library version number manifest constants
						together define the current version number of the MMI
						library as a whole.

						(.) ''MMI_VERSION_MAJOR'' represents the major
						component of the library version number.

						(.) ''MMI_VERSION_MINOR'' represents the minor
						component of the library version number.

						(.) ''MMI_VERSION_RELEASE'' represents the release
						component of the library version number.

						(.) ''MMI_VERSION_BUILD'' represents the build
						level component of the library version number.

   SEE ALSO    :	STR_VERSION

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2014 Michael L. Brock

   OUTPUT INDEX:	MMI_VERSION_MAJOR
						MMI_VERSION_MINOR
						MMI_VERSION_RELEASE
						MMI_VERSION_BUILD
						MMI Version Numbers:Library Version Number
						Library Version Number:MMI_VERSION_MAJOR
						Library Version Number:MMI_VERSION_MINOR
						Library Version Number:MMI_VERSION_RELEASE
						Library Version Number:MMI_VERSION_BUILD
						Macros and Manifest Constants:MMI_VERSION_MAJOR
						Macros and Manifest Constants:MMI_VERSION_MINOR
						Macros and Manifest Constants:MMI_VERSION_RELEASE
						Macros and Manifest Constants:MMI_VERSION_BUILD
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	MMI_VERSION_MAJOR
						MMI_VERSION_MINOR
						MMI_VERSION_RELEASE
						MMI_VERSION_BUILD
						MMI Library Version Number
						MMI library version number
						MMI Library Version
						MMI library version
						MMI Version Number
						MMI version number
						MMI Version
						MMI version

   PUBLISH NAME:	MMI_VERSION_MAJOR
						MMI_VERSION_MINOR
						MMI_VERSION_RELEASE
						MMI_VERSION_BUILD

	ENTRY CLASS	:	Macros and Manifest Constants:Library Version Number
						MMI Version Numbers:Library Version Number

EOH */
/*	***********************************************************************	*/
#define MMI_VERSION_MAJOR					((unsigned char) 1)
#define MMI_VERSION_MINOR					((unsigned char) 0)
#define MMI_VERSION_RELEASE				((unsigned char) 0)
#define MMI_VERSION_BUILD					((unsigned char) 'A')
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
	BASE NAME	: MMI Flag To Operating System Macros
*/
/*	***********************************************************************	*/
#define MMI_FLAG_MMAP_TYPE(flag)       ((flag) & MMI_FLAG_MMAP_TYPE_MASK)
#define MMI_FLAG_MMAP_TYPE_OS(flag)													\
	((MMI_FLAG_MMAP_TYPE(flag) == MMI_FLAG_MMAP_SHARED)  ? MAP_SHARED  :	\
	 (MMI_FLAG_MMAP_TYPE(flag) == MMI_FLAG_MMAP_PRIVATE) ? MAP_PRIVATE : 0)

#define MMI_MAP_FLAG_MADV_TO_OS(flag)									\
	(((flag) == MMI_FLAG_MADV_NORMAL)     ? MADV_NORMAL     :	\
	 ((flag) == MMI_FLAG_MADV_RANDOM)     ? MADV_RANDOM     :	\
	 ((flag) == MMI_FLAG_MADV_SEQUENTIAL) ? MADV_SEQUENTIAL :	\
	 ((flag) == MMI_FLAG_MADV_WILLNEED)   ? MADV_WILLNEED   :	\
	 ((flag) == MMI_FLAG_MADV_DONTNEED)   ? MADV_DONTNEED   : 0)
#define MMI_MAP_FLAG_PROT_TO_OS(flag)									\
	((((flag) & MMI_FLAG_PROT_NONE)  ? PROT_NONE  : 0) |			\
	 (((flag) & MMI_FLAG_PROT_READ)  ? PROT_READ  : 0) |			\
	 (((flag) & MMI_FLAG_PROT_WRITE) ? PROT_WRITE : 0) |			\
	 (((flag) & MMI_FLAG_PROT_EXEC)  ? PROT_EXEC  : 0) |			\
	 (((flag) & MMI_FLAG_PROT_USER)  ? PROT_USER  : 0))
#define MMI_MAP_FLAG_MMAP_TO_OS(flag)									\
	(MMI_FLAG_MMAP_TYPE_OS(flag)                              |	\
	 (((flag) & MMI_FLAG_MMAP_FIXED)     ? MAP_FIXED     : 0) |	\
	 (((flag) & MMI_FLAG_MMAP_NORESERVE) ? MAP_NORESERVE : 0) |	\
	 (((flag) & MMI_FLAG_MMAP_RENAME)    ? MAP_RENAME    : 0))
#define MMI_MAP_FLAG_SYNC_TO_OS(flag)									\
	(((flag) == MMI_FLAG_SYNC_ASYNC)      ? MS_ASYNC      :		\
	 ((flag) == MMI_FLAG_SYNC_SYNC)       ? MS_SYNC       :		\
	 ((flag) == MMI_FLAG_SYNC_INVALIDATE) ? MS_INVALIDATE : 0);
#define MMI_MAP_FLAG_MCTL_TO_OS(flag)									\
	(((flag) == MMI_FLAG_MCTL_LOCK)     ? MC_LOCK     :			\
	 ((flag) == MMI_FLAG_MCTL_LOCKAS)   ? MC_LOCKAS   :			\
	 ((flag) == MMI_FLAG_MCTL_SYNC)     ? MC_SYNC     : 			\
	 ((flag) == MMI_FLAG_MCTL_UNLOCK)   ? MC_UNLOCK   :			\
	 ((flag) == MMI_FLAG_MCTL_UNLOCKAS) ? MC_UNLOCKAS : 0)

/*
	CODE NOTE: To be deleted.
#ifdef _Windows
# undef MMI_MAP_FLAG_PROT_TO_OS
# define MMI_MAP_FLAG_PROT_TO_OS(prot)									\
	(((prot) == MMI_FLAG_PROT_NONE)                         ?	\
	PAGE_NOACCESS          :	\
	 ((prot) == MMI_FLAG_PROT_READ)                         ? 	\
	PAGE_READONLY          :	\
	 ((prot) == MMI_FLAG_PROT_WRITE)                        ? 	\
	PAGE_READWRITE         :	\
	 ((prot) == MMI_FLAG_PROT_EXEC)                         ? 	\
	PAGE_EXECUTE           :	\
	 ((prot) == MMI_FLAG_PROT_NONE)                         ? 	\
	PAGE_NOACCESS          :	\
	 ((prot) == MMI_FLAG_PROT_RW)                           ? 	\
	PAGE_READWRITE         :	\
	 ((prot) == (MMI_FLAG_PROT_READ | MMI_FLAG_PROT_EXEC))  ? 	\
	PAGE_EXECUTE_READ      :	\
	 ((prot) == (MMI_FLAG_PROT_WRITE | MMI_FLAG_PROT_EXEC)) ? 	\
	PAGE_EXECUTE_READWRITE :	\
	 ((prot) == (MMI_FLAG_PROT_RW | MMI_FLAG_PROT_EXEC))    ? 	\
	PAGE_EXECUTE_READWRITE : PAGE_NOACCESS)
#endif // #ifdef _Windows
*/
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
	BASE NAME	: MMI Win32 Flag Mapping Access Macros
*/
/*	***********************************************************************	*/
#ifdef _Windows
# define MMI_ProtFlagToWin32PageFlag(prot)							\
	(((prot) == MMI_FLAG_PROT_READ)                         ?	\
		PAGE_READONLY          :											\
	 ((prot) == MMI_FLAG_PROT_WRITE)                        ?	\
		PAGE_READWRITE         :											\
	 ((prot) == MMI_FLAG_PROT_EXEC)                         ?	\
		PAGE_EXECUTE           :											\
	 ((prot) == MMI_FLAG_PROT_NONE)                         ?	\
		PAGE_NOACCESS          :											\
	 ((prot) == (MMI_FLAG_PROT_RW))                         ?	\
		PAGE_READWRITE         :											\
	 ((prot) == (MMI_FLAG_PROT_READ | MMI_FLAG_PROT_EXEC))  ?	\
		PAGE_EXECUTE_READ      :											\
	 ((prot) == (MMI_FLAG_PROT_WRITE | MMI_FLAG_PROT_EXEC)) ?	\
		PAGE_EXECUTE_READWRITE :											\
	 ((prot) == (MMI_FLAG_PROT_RW | MMI_FLAG_PROT_EXEC))    ?	\
		PAGE_EXECUTE_READWRITE : PAGE_NOACCESS)
# define MMI_ProtFlagToWin32FileFlag(prot)							\
	(((prot) == MMI_FLAG_PROT_READ)                         ?	\
		FILE_MAP_READ          :											\
	 ((prot) == MMI_FLAG_PROT_WRITE)                        ?	\
		FILE_MAP_WRITE         :											\
	 ((prot) == MMI_FLAG_PROT_EXEC)                         ?	\
		FILE_MAP_READ          :											\
	 ((prot) == MMI_FLAG_PROT_NONE)                         ?	\
		FILE_MAP_READ          :											\
	 ((prot) == (MMI_FLAG_PROT_RW))                         ?	\
		FILE_MAP_WRITE         :											\
	 ((prot) == (MMI_FLAG_PROT_READ | MMI_FLAG_PROT_EXEC))  ?	\
		FILE_MAP_READ		     :											\
	 ((prot) == (MMI_FLAG_PROT_WRITE | MMI_FLAG_PROT_EXEC)) ?	\
		FILE_MAP_WRITE			  :											\
	 ((prot) == (MMI_FLAG_PROT_RW | MMI_FLAG_PROT_EXEC))    ?	\
		FILE_MAP_WRITE			  : FILE_MAP_READ)
# define MMI_ProtMapFlagsToWin32PageFlag(prot, map)				\
	(MMI_ProtFlagToWin32PageFlag(prot) |								\
	(((map) & MMI_FLAG_MMAP_PRIVATE) ?									\
	(((prot) & MMI_FLAG_PROT_EXEC) ? PAGE_EXECUTE_WRITECOPY :	\
	(((prot) & MMI_FLAG_PROT_WRITE) ? PAGE_WRITECOPY : 0)) : 0))
# define MMI_ProtMapFlagsToWin32FileFlag(prot, map)				\
	(MMI_ProtFlagToWin32FileFlag(prot) |								\
	(((map) & MMI_FLAG_MMAP_PRIVATE) ? FILE_MAP_COPY : 0))
#endif /* #ifdef _Windows */
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Function prototypes for the internal MMI functions . . .						*/
/*	***********************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Windows support function prototypes . . .
		*****************************************************************	*/
#ifdef _Windows
COMPAT_FN_DECL(void *MMI_WIN32_Map,
	(MMI_ADDRESS address, MMI_LENGTH length, MMI_FLAG prot_flags,
	MMI_FLAG mmap_flags, MMI_FILE_HANDLE file_handle, MMI_OFFSET offset,
	MMI_MMAP_HANDLE_OS *os_mmap_handle, char *error_text));
COMPAT_FN_DECL(void *MMI_WIN32_MapOS,
	(MMI_ADDRESS address, MMI_LENGTH length, MMI_FLAG prot_flags,
	MMI_FLAG mmap_flags, MMI_FILE_HANDLE_OS os_file_handle, MMI_OFFSET offset,
	MMI_MMAP_HANDLE_OS *os_mmap_handle, char *error_text));
COMPAT_FN_DECL(void *MMI_WIN32_Protect,
	(MMI_ADDRESS address, MMI_LENGTH length, MMI_FLAG prot_flags));
COMPAT_FN_DECL(char *MMI_Win32PageFlags,
	(MMI_FLAG in_flags, char *out_string));
COMPAT_FN_DECL(char *MMI_Win32FileFlags,
	(MMI_FLAG in_flags, char *out_string));
#endif /* #ifdef _Windows */
	/*	*****************************************************************	*/

/*	***********************************************************************	*/

#endif /* #ifndef h__MMII_H__h */

