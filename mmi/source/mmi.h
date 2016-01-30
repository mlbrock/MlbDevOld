/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MMI Memory-mapped Interface Library Include File								*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the Memory-mapped Interface Library
								(MMI).

	Revision History	:	1992-03-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__MMI_H__h

#define h__MMI_H__h						1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include <mbcompat.h>

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>

#ifdef _Windows
# ifdef _MSC_VER
#  if _MSC_VER >= 1300
#   pragma warning(disable:4255 4668)
#   include <windows.h>
#   pragma warning(default:4255 4668)
#  elif _MSC_VER >= 1200
#   pragma warning(disable:4115)
#   include <windows.h>
#   pragma warning(default:4115)
#  else
#   pragma warning(disable:4115 4201 4214 4514)
#   include <windows.h>
#   pragma warning(default:4115 4201 4214)
# 	endif /* #  if _MSC_VER >= 1200 */
# else
#  include <windows.h>
# endif /* # ifdef _MSC_VER */
# include <windows.h>
#else
# include <sys/mman.h>
#endif /* #ifdef _Windows */

#include <mbcompat.h>

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   BASE NAME   :  MMI Truth Codes

   NAME        :  MMI Truth Codes

	DESCRIPTION :  Manifest constants used within MMI to specify the truth
						or falsity of expressions.

						(.) ''MMI_TRUE''

						(.) ''MMI_FALSE''

   NOTES       :  The manifest constant ''MMI_TRUE'' should be defined as
						a non-zero value. Conversely, the manifest constant
						''MMI_FALSE'' should be defined as zero (''0'').

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2016 Michael L. Brock

   OUTPUT INDEX:  MMI_TRUE
						MMI_FALSE
						MMI Truth Codes:MMI_TRUE
						MMI Truth Codes:MMI_FALSE
						MMI Manifest Constants:MMI_TRUE
						MMI Manifest Constants:MMI_FALSE
						MMI Defines:MMI_TRUE
						MMI Defines:MMI_FALSE
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:  MMI Truth Codes
						MMI Truth Code
						MMI truth codes
						MMI truth code
						MMI_TRUE
						MMI_FALSE

   PUBLISH NAME:	MMI Truth Codes
						MMI_TRUE
						MMI_FALSE

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define MMI_TRUE							1
#define MMI_FALSE							0
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   BASE NAME   :	MMI Return Codes

   NAME        :  MMI Return Codes

   DESCRIPTION :  The MMI return codes have the following meanings:

						(.) ''MMI_SUCCESS'' means that the function invoked
						completed without error. ''MMI_SUCCESS'' is guaranteed to
						be equal to zero (''0'').

						(.) ''MMI_FAILURE'' indicates that the function invoked
						encountered a general operation failure. This is the
						'catch-all' error code for those errors which do not fit
						into category of one the other MMI error codes.

						(.) ''MMI_BAD_ARGS_FAILURE'' indicates that the
						arguments passed to a function invoked were invalid.

						(.) ''MMI_MEMORY_FAILURE'' indicates that the memory
						required for operation of the function invoked could not be
						allocated.

						(.) ''MMI_SYSTEM_FAILURE'' indicates that the function
						invoked encountered a failure of a standard library
						function or a system call.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2016 Michael L. Brock

   OUTPUT INDEX:  MMI_SUCCESS
						MMI_FAILURE
						MMI_BAD_ARGS_FAILURE
						MMI_MEMORY_FAILURE
						MMI_SYSTEM_FAILURE
						MMI Return Codes:MMI_SUCCESS
						MMI Return Codes:MMI_FAILURE
						MMI Return Codes:MMI_BAD_ARGS_FAILURE
						MMI Return Codes:MMI_MEMORY_FAILURE
						MMI Return Codes:MMI_SYSTEM_FAILURE
						MMI Manifest Constants:MMI_SUCCESS
						MMI Manifest Constants:MMI_FAILURE
						MMI Manifest Constants:MMI_BAD_ARGS_FAILURE
						MMI Manifest Constants:MMI_MEMORY_FAILURE
						MMI Manifest Constants:MMI_SYSTEM_FAILURE
						MMI Defines:MMI_SUCCESS
						MMI Defines:MMI_FAILURE
						MMI Defines:MMI_BAD_ARGS_FAILURE
						MMI Defines:MMI_MEMORY_FAILURE
						MMI Defines:MMI_SYSTEM_FAILURE
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:  MMI_SUCCESS
						MMI_FAILURE
						MMI_BAD_ARGS_FAILURE
						MMI_MEMORY_FAILURE
						MMI_SYSTEM_FAILURE
						MMI Return Codes
						MMI Return Code
						MMI return codes
						MMI return code
						MMI Status Codes
						MMI Status Code
						MMI status codes
						MMI status code
						MMI Error Codes
						MMI Error Code
						MMI error codes
						MMI error code

   PUBLISH NAME:	MMI Return Codes
						MMI return codes
						MMI_SUCCESS
						MMI_FAILURE
						MMI_BAD_ARGS_FAILURE
						MMI_MEMORY_FAILURE
						MMI_SYSTEM_FAILURE

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define MMI_SUCCESS							 0
#define MMI_FAILURE							-1
#define MMI_BAD_ARGS_FAILURE				-2
#define MMI_MEMORY_FAILURE					-3
#define MMI_SYSTEM_FAILURE					-4
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :  MMI_MAX_ERROR_TEXT

   DESCRIPTION :  The manifest constant ''MMI_MAX_ERROR_TEXT'' defines
						the minimum amount of storage which should be allocated to
						hold an error message returned by a MMI function.

   CAVEATS     :  MMI error messages can be quite lengthy. Therefore,
						attempting to save space by allocating less than
						''MMI_MAX_ERROR_TEXT'' bytes to error message buffers
						passed to MMI functions can lead to overwriting of the
						heap or the stack.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2016 Michael L. Brock

   OUTPUT INDEX:  MMI_MAX_ERROR_TEXT
						MMI Manifest Constants:MMI_MAX_ERROR_TEXT
						MMI Defines:MMI_MAX_ERROR_TEXT
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	MMI_MAX_ERROR_TEXT

   PUBLISH NAME:	MMI_MAX_ERROR_TEXT

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define MMI_MAX_ERROR_TEXT					1024
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef void *MMI_ADDRESS;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef unsigned long MMI_LENGTH;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef unsigned long MMI_OFFSET;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef int MMI_FILE_HANDLE;
#define MMI_FILE_HANDLE_CLOSED				((MMI_FILE_HANDLE) -1)
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#ifdef _Windows
typedef HANDLE MMI_MMAP_HANDLE_OS;
# define MMI_MMAP_HANDLE_OS_CLOSED			((MMI_MMAP_HANDLE_OS) NULL)
#else
typedef void *MMI_MMAP_HANDLE_OS;
# define MMI_MMAP_HANDLE_OS_CLOSED			((MMI_MMAP_HANDLE_OS) NULL)
#endif /* #ifdef _Windows */
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#ifdef _Windows
typedef HANDLE MMI_FILE_HANDLE_OS;
# define MMI_FILE_HANDLE_OS_CLOSED			((MMI_FILE_HANDLE) NULL)
#else
typedef void *MMI_FILE_HANDLE_OS;
# define MMI_FILE_HANDLE_OS_CLOSED			((MMI_FILE_HANDLE) NULL)
#endif /* #ifdef _Windows */
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef unsigned long MMI_FLAG;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define MMI_GetPageSize()						GEN_GetAllocGranularity()
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
	BASE NAME	:	MMI Advice Flags
*/
/*	***********************************************************************	*/
#define MMI_FLAG_MADV_NORMAL				((MMI_FLAG) 0X01)
#define MMI_FLAG_MADV_RANDOM				((MMI_FLAG) 0X02)
#define MMI_FLAG_MADV_SEQUENTIAL			((MMI_FLAG) 0X03)
#define MMI_FLAG_MADV_WILLNEED			((MMI_FLAG) 0X04)
#define MMI_FLAG_MADV_DONTNEED			((MMI_FLAG) 0X05)

#ifdef _Windows
# define MADV_NORMAL							MMI_FLAG_MADV_NORMAL
# define MADV_RANDOM							MMI_FLAG_MADV_RANDOM
# define MADV_SEQUENTIAL					MMI_FLAG_MADV_SEQUENTIAL
# define MADV_WILLNEED						MMI_FLAG_MADV_WILLNEED
# define MADV_DONTNEED						MMI_FLAG_MADV_DONTNEED
#endif /* _Windows */

/*
	CODE NOTE: To be removed.
# define MMI_FLAG_MADV_OS_NORMAL			((MMI_FLAG) MADV_NORMAL)
# define MMI_FLAG_MADV_OS_RANDOM			((MMI_FLAG) MADV_RANDOM)
# define MMI_FLAG_MADV_OS_SEQUENTIAL	((MMI_FLAG) MADV_SEQUENTIAL)
# define MMI_FLAG_MADV_OS_WILLNEED		((MMI_FLAG) MADV_WILLNEED)
# define MMI_FLAG_MADV_OS_DONTNEED		((MMI_FLAG) MADV_DONTNEED)
*/
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
	BASE NAME	:	MMI Protection Flags
*/
/*	***********************************************************************	*/
#define MMI_FLAG_PROT_NONE					((MMI_FLAG) 0X01)
#define MMI_FLAG_PROT_READ					((MMI_FLAG) 0X02)
#define MMI_FLAG_PROT_WRITE				((MMI_FLAG) 0X04)
#define MMI_FLAG_PROT_EXEC					((MMI_FLAG) 0X08)
#define MMI_FLAG_PROT_USER					((MMI_FLAG) 0X10)
#define MMI_FLAG_PROT_RW					\
	(MMI_FLAG_PROT_READ | MMI_FLAG_PROT_WRITE)
#define MMI_FLAG_PROT_ALL					\
	(MMI_FLAG_PROT_RW | MMI_FLAG_PROT_EXEC | MMI_FLAG_PROT_USER)

#ifdef _Windows
# define PROT_NONE							MMI_FLAG_PROT_NONE
# define PROT_READ							MMI_FLAG_PROT_READ
# define PROT_WRITE							MMI_FLAG_PROT_WRITE
# define PROT_EXEC							MMI_FLAG_PROT_EXEC
#endif /* #ifdef _Windows */

#ifndef PROT_USER
# define PROT_USER							0
#endif /* #ifndef PROT_USER */

#ifndef PROT_RW
# define PROT_RW								(PROT_READ | PROT_WRITE)
#endif /* #ifdef PROT_RW */

#ifndef PROT_ALL
# define PROT_ALL								(PROT_RW | PROT_EXEC | PROT_USER)
#endif /* #ifndef PROT_ALL */

/*
	CODE NOTE: To be removed.
#define MMI_FLAG_OS_PROT_NONE				((MMI_FLAG) PROT_NONE)
#define MMI_FLAG_OS_PROT_READ				((MMI_FLAG) PROT_READ)
#define MMI_FLAG_OS_PROT_WRITE			((MMI_FLAG) PROT_WRITE)
#define MMI_FLAG_OS_PROT_EXEC				((MMI_FLAG) PROT_EXEC)
#define MMI_FLAG_OS_PROT_USER				((MMI_FLAG) PROT_USER)
#define MMI_FLAG_OS_PROT_RW				((MMI_FLAG) PROT_RW)
#define MMI_FLAG_OS_PROT_ALL				((MMI_FLAG) PROT_ALL)
*/
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
	BASE NAME	:	MMI Memory-Mapping Flags
*/
/*	***********************************************************************	*/
#define MMI_FLAG_MMAP_TYPE_MASK			((MMI_FLAG) 0X0F)

#define MMI_FLAG_MMAP_SHARED				((MMI_FLAG) 0X01)
#define MMI_FLAG_MMAP_PRIVATE				((MMI_FLAG) 0X02)
#define MMI_FLAG_MMAP_FIXED				((MMI_FLAG) 0X10)
#define MMI_FLAG_MMAP_NORESERVE			((MMI_FLAG) 0X20)
#define MMI_FLAG_MMAP_RENAME				((MMI_FLAG) 0X40)

#ifdef _Windows
# define MAP_SHARED							MMI_FLAG_MMAP_SHARED
# define MAP_PRIVATE							MMI_FLAG_MMAP_PRIVATE
# define MAP_FIXED	 						MMI_FLAG_MMAP_FIXED
# define MAP_NORESERVE						MMI_FLAG_MMAP_NORESERVE
# define MAP_RENAME							MMI_FLAG_MMAP_RENAME
#endif /* #ifdef _Windows */

#ifndef MAP_NORESERVE
# define MAP_NORESERVE						0X00
#endif /* #ifndef MAP_NORESERVE */

#ifndef MAP_RENAME
# define MAP_RENAME							0X00
#endif /* #ifndef MAP_RENAME */

/*
	CODE NOTE: To be removed.
#define MMI_FLAG_MMAP_OS_SHARED			((MMI_FLAG) MAP_SHARED)
#define MMI_FLAG_MMAP_OS_PRIVATE			((MMI_FLAG) MAP_PRIVATE)
#define MMI_FLAG_MMAP_OS_FIXED			((MMI_FLAG) MAP_FIXED)
#define MMI_FLAG_MMAP_OS_NORESERVE		((MMI_FLAG) MAP_NORESERVE)
#define MMI_FLAG_MMAP_OS_RENAME			((MMI_FLAG) MAP_RENAME)
*/
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
	BASE NAME	:	MMI Synchronization Flags
*/
/*	***********************************************************************	*/
#define MMI_FLAG_SYNC_ASYNC				((MMI_FLAG) 0X00)
#define MMI_FLAG_SYNC_SYNC					((MMI_FLAG) 0X01)
#define MMI_FLAG_SYNC_INVALIDATE			((MMI_FLAG) 0X02)

#ifdef _Windows
# define MS_ASYNC								MMI_FLAG_SYNC_ASYNC
# define MS_SYNC								MMI_FLAG_SYNC_SYNC
# define MS_INVALIDATE						MMI_FLAG_SYNC_INVALIDATE
#endif /* #ifdef _Windows */

/*
	CODE NOTE: To be removed.
#define MMI_FLAG_SYNC_OS_ASYNC			((MMI_FLAG) MS_ASYNC)
#define MMI_FLAG_SYNC_OS_SYNC				((MMI_FLAG) MS_SYNC)
#define MMI_FLAG_SYNC_OS_INVALIDATE		((MMI_FLAG) MS_INVALIDATE)
*/
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
	BASE NAME	:	MMI Control Flags
*/
/*	***********************************************************************	*/
#define MMI_FLAG_MCTL_LOCK					((MMI_FLAG) 0X01)
#define MMI_FLAG_MCTL_LOCKAS				((MMI_FLAG) 0X02)
#define MMI_FLAG_MCTL_SYNC					((MMI_FLAG) 0X03)
#define MMI_FLAG_MCTL_UNLOCK				((MMI_FLAG) 0X04)
#define MMI_FLAG_MCTL_UNLOCKAS			((MMI_FLAG) 0X05)

#ifdef _Windows
# define MC_LOCK								MMI_FLAG_MCTL_LOCK
# define MC_LOCKAS							MMI_FLAG_MCTL_LOCKAS
# define MC_SYNC								MMI_FLAG_MCTL_SYNC
# define MC_UNLOCK							MMI_FLAG_MCTL_UNLOCK
# define MC_UNLOCKAS							MMI_FLAG_MCTL_UNLOCKAS
#endif /* #ifdef _Windows */

/*
	CODE NOTE: To be removed.
#define MMI_FLAG_MCTL_OS_LOCK				((MMI_FLAG) MC_LOCK)
#define MMI_FLAG_MCTL_OS_LOCKAS			((MMI_FLAG) MC_LOCKAS)
#define MMI_FLAG_MCTL_OS_SYNC				((MMI_FLAG) MC_SYNC)
#define MMI_FLAG_MCTL_OS_UNLOCK			((MMI_FLAG) MC_UNLOCK)
#define MMI_FLAG_MCTL_OS_UNLOCKAS		((MMI_FLAG) MC_UNLOCKAS)
*/
/*	***********************************************************************	*/

/*
	ADF NOTE: NO_ADF
*/
/*	***********************************************************************	*/
#define MMI_FLAG_NAME_MAX					31
#define MMI_FLAG_COMPLETE_MAX				127
typedef struct {
	char     name[MMI_FLAG_NAME_MAX + 1];
	MMI_FLAG value;
} MMI_FLAG_DEF;
/*	***********************************************************************	*/

/*
	ADF NOTE: NO_ADF
*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Macros to access to operating system memory-mapping functions . . .	*/
/*	***********************************************************************	*/
#if _Windows
#define MMI_madvise(address, length, madv_flags)								\
	(-1)
#define MMI_mctl(address, length, function, arg)								\
	(-1)
#define MMI_mlock(address, length)													\
	(VirtualLock(((LPVOID) (address)), ((DWORD) (length))) ? 0 : -1)
#define MMI_mlockall(lock_flags)														\
	(-1)
#define MMI_mmap(address, length, prot_flags, mmap_flags, fd, offset)	\
	MMI_WIN32_Map(((void *) (address)), ((unsigned int) (length)),			\
		((unsigned int) (prot_flags)), ((unsigned int) (mmap_flags)),		\
		((int) (fd)), ((unsigned int) (offset)), NULL, NULL)
#define MMI_mprotect(address, length, prot_flags)								\
	MMI_WIN32_Protect(((void *) (address)), ((unsigned int) (length)),	\
		((unsigned int) (prot_flags)))
#define MMI_msync(address, length, sync_flags)									\
	((FlushViewOfFile(((LPCVOID) (address)), ((DWORD) (length))) ==		\
	TRUE) ? 0 : -1)
#define MMI_munlock(address, length)												\
	(VirtualUnlock(((LPVOID) (address)), ((DWORD) (length))) ? 0 : -1)
#define MMI_munlockall()																\
	(-1)
#define MMI_munmap(address, length)													\
	((UnmapViewOfFile(((LPVOID) (address)))) ? 0 : -1)
#elif __SVR4
#define MMI_madvise(address, length, madv_flags)								\
	madvise(((caddr_t) (address)), ((size_t) (length)),						\
		((int) (madv_flags)))
#define MMI_mctl(address, length, function, arg)								\
	mctl(((caddr_t) (address)), ((size_t) (length)),							\
		((int) (function)), ((void *) (arg)))
#define MMI_mlock(address, length)													\
	mlock(((void *) (address)), ((size_t) (length)))
#define MMI_mlockall(lock_flags)														\
	mlockall(((int) (lock_flags)))
#define MMI_mmap(address, length, prot_flags, mmap_flags, fd, offset)	\
	mmap(((void *) (address)), ((size_t) (length)),								\
		((int) (prot_flags)), ((int) (mmap_flags)), ((int) (fd)),			\
		((off_t) (offset)))
#define MMI_mprotect(address, length, prot_flags)								\
	mprotect(((void *) (address)), ((size_t) (length)),						\
		((int) (prot_flags)))
#define MMI_msync(address, length, sync_flags)									\
	msync(((void *) (address)), ((size_t) (length)),							\
		((int) (sync_flags)))
#define MMI_munlock(address, length)												\
	munlock(((void *) (address)), ((size_t) (length)))
#define MMI_munlockall()																\
	munlockall()
#define MMI_munmap(address, length)													\
	munmap(((void *) (address)), ((size_t) (length)))
#elif _POSIX_C_SOURCE
#define MMI_madvise(address, length, madv_flags)								\
	madvise(((caddr_t) (address)), ((size_t) (length)),						\
		((int) (madv_flags)))
#define MMI_mctl(address, length, function, arg)								\
	mctl(((caddr_t) (address)), ((size_t) (length)),							\
		((int) (function)), ((void *) (arg)))
#define MMI_mlock(address, length)													\
	mlock(((const void *) (address)), ((size_t) (length)))
#define MMI_mlockall(lock_flags)														\
	mlockall(((int) (lock_flags)))
#define MMI_mmap(address, length, prot_flags, mmap_flags, fd, offset)	\
	mmap(((void *) (address)), ((size_t) (length)),								\
		((int) (prot_flags)), ((int) (mmap_flags)), ((int) (fd)),			\
		((off_t) (offset)))
#define MMI_mprotect(address, length, prot_flags)								\
	mprotect(((const void *) (address)), ((size_t) (length)),				\
		((int) (prot_flags)))
#define MMI_msync(address, length, sync_flags)									\
	msync(((const void *) (address)), ((size_t) (length)),					\
		((int) (sync_flags)))
#define MMI_munlock(address, length)												\
	munlock(((const void *) (address)), ((size_t) (length)))
#define MMI_munlockall()																\
	munlockall()
#define MMI_munmap(address, length)													\
	munmap(((const void *) (address)), ((size_t) (length)))
#else
#define MMI_madvise(address, length, madv_flags)								\
	madvise(((caddr_t) (address)), ((int) (length)), ((int) (madv_flags)))
#define MMI_mctl(address, length, function, arg)								\
	mctl(((caddr_t) (address)), ((size_t) (length)),							\
		((int) (function)), ((void *) (arg)))
#define MMI_mlock(address, length)													\
	mlock(((caddr_t) (address)), ((size_t) (length)))
#define MMI_mlockall(lock_flags)														\
	mlockall(((int) (lock_flags)))
#define MMI_mmap(address, length, prot_flags, mmap_flags, fd, offset)	\
	mmap(((caddr_t) (address)), ((int) (length)),								\
		((int) (prot_flags)), ((int) (mmap_flags)), ((int) (fd)),			\
		((off_t) (offset)))
#define MMI_mprotect(address, length, prot_flags)								\
	mprotect(((caddr_t) (address)), ((int) (length)),							\
		((int) (prot_flags)))
#define MMI_msync(address, length, sync_flags)									\
	msync(((caddr_t) (address)), ((int) (length)), ((int) (sync_flags)))
#define MMI_munlock(address, length)												\
	munlock(((caddr_t) (address)), ((size_t) (length)))
#define MMI_munlockall()																\
	munlockall()
#define MMI_munmap(address, length)													\
	munmap(((caddr_t) (address)), ((int) (length)))
#endif /* # ifdef _Windows */
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Function prototypes for the MMI functions . . .							*/
/*	***********************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		MMI core function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int MMI_Advise,
	(MMI_ADDRESS address, MMI_LENGTH length, MMI_FLAG madv_flags,
	char *error_text));
COMPAT_FN_DECL(int MMI_Control,
	(MMI_ADDRESS address, MMI_LENGTH length, unsigned int function,
	void *arg, unsigned int attr, unsigned int mask, char *error_text));
COMPAT_FN_DECL(int MMI_Lock,
	(MMI_ADDRESS address, MMI_LENGTH length, char *error_text));
COMPAT_FN_DECL(int MMI_Map,
	(MMI_ADDRESS address, MMI_LENGTH length, MMI_FLAG prot_flags,
	MMI_FLAG mmap_flags, MMI_FILE_HANDLE file_handle, MMI_OFFSET offset,
	MMI_ADDRESS *out_address, MMI_MMAP_HANDLE_OS *os_mmap_handle,
	char *error_text));
COMPAT_FN_DECL(int MMI_Protect,
	(MMI_ADDRESS address, MMI_LENGTH length, MMI_FLAG prot_flags,
	char *error_text));
COMPAT_FN_DECL(int MMI_Sync,
	(MMI_ADDRESS address, MMI_LENGTH length, MMI_FLAG sync_flags,
	char *error_text));
COMPAT_FN_DECL(int MMI_Unlock,
	(MMI_ADDRESS address, MMI_LENGTH length, char *error_text));
COMPAT_FN_DECL(int MMI_Unmap,
	(MMI_ADDRESS address, MMI_LENGTH length, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Flag-to-string function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(char *MMI_MADVFlags, (MMI_FLAG in_flags, char *out_string));
COMPAT_FN_DECL(char *MMI_PROTFlags, (MMI_FLAG in_flags, char *out_string));
COMPAT_FN_DECL(char *MMI_MMAPFlags, (MMI_FLAG in_flags, char *out_string));
COMPAT_FN_DECL(char *MMI_SYNCFlags, (MMI_FLAG in_flags, char *out_string));
COMPAT_FN_DECL(char *MMI_MCTLFlags, (MMI_FLAG in_flags, char *out_string));
COMPAT_FN_DECL(char *MMI_GetEnumFlag,
	(MMI_FLAG in_flags, const char *in_name, unsigned int count,
	const MMI_FLAG_DEF *list, char *out_string));
COMPAT_FN_DECL(char *MMI_GetORedFlag,
	(MMI_FLAG in_flags, const char *in_name, unsigned int count,
	const MMI_FLAG_DEF *list, char *out_string));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Function prototypes for miscellaneous supporting functions . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int   MMI_CheckAddress,
	(const MMI_ADDRESS address, char *error_text));
COMPAT_FN_DECL(int   MMI_CheckLength,
	(MMI_LENGTH length, char *error_text));
COMPAT_FN_DECL(int   MMI_CheckAdvice,
	(MMI_FLAG madv_flags, char *error_text));
COMPAT_FN_DECL(int   MMI_CheckProtect,
	(MMI_FLAG prot_flags, char *error_text));
COMPAT_FN_DECL(int   MMI_CheckSyncFlags,
	(MMI_FLAG sync_flags, char *error_text));
COMPAT_FN_DECL(int   MMI_CheckMapFlags,
	(MMI_FLAG mmap_flags, char *error_text));
COMPAT_FN_DECL(void  MMI_GetVersionNumber, (unsigned int *major,
	unsigned int *minor, unsigned int *release, unsigned int *build));
COMPAT_FN_DECL(char *MMI_GetVersionString, (char *version_string));
	/*	*****************************************************************	*/

/*	***********************************************************************	*/

#endif /* #ifndef h__MMI_H__h */

