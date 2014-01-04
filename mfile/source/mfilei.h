/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MFILE Memory-mapped I/O Library Internal Include File							*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Internal include file for the Memory-mapped I/O
								Library (MFILE).

	Revision History	:	1992-03-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__MFILEI_H__h

#define h__MFILEI_H__h						1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include <mbcompat.h>

#ifdef _Windows
# ifdef _MSC_VER
#  pragma warning(push)
#  if _MSC_VER >= 1400
#    pragma warning(disable:4820)
#  endif /* #  if _MSC_VER >= 1400 */
#  if _MSC_VER >= 1300
#   pragma warning(disable:4255 4668)
#   include <windows.h>
#  elif _MSC_VER >= 1200
#   pragma warning(disable:4115)
#   include <windows.h>
#  else
#   pragma warning(disable:4115 4201 4214 4514)
#   include <windows.h>
# 	endif /* #  if _MSC_VER >= 1200 */
#  pragma warning(pop)
# else
#  include <windows.h>
# endif /* # ifdef _MSC_VER */
#elif __MSDOS__
#else
# include <unistd.h>
# include <sys/mman.h>
#endif /* #ifdef _Windows */

#include <mtif.h>

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* Temporary definition to get 'mfile.h' included . . .                    */
/*	***********************************************************************	*/
#define MFILE struct tag_MFILE
struct tag_MFILE;
# include "mfile.h"
#undef MFILE
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	MFILE Library Version Number

	NAME        :	MFILE Library Version Number

	DESCRIPTION :	The MFILE library version number manifest constants
						together define the current version number of the MFILE
						library as a whole.

						(.) ''MFILE_VERSION_MAJOR'' represents the major
						component of the library version number.

						(.) ''MFILE_VERSION_MINOR'' represents the minor
						component of the library version number.

						(.) ''MFILE_VERSION_RELEASE'' represents the release
						component of the library version number.

						(.) ''MFILE_VERSION_BUILD'' represents the build
						level component of the library version number.

	SEE ALSO    :	STR_VERSION

	AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2014 Michael L. Brock

	OUTPUT INDEX:	MFILE_VERSION_MAJOR
						MFILE_VERSION_MINOR
						MFILE_VERSION_RELEASE
						MFILE_VERSION_BUILD
						MFILE Version Numbers:Library Version Number
						Library Version Number:MFILE_VERSION_MAJOR
						Library Version Number:MFILE_VERSION_MINOR
						Library Version Number:MFILE_VERSION_RELEASE
						Library Version Number:MFILE_VERSION_BUILD
						Macros and Manifest Constants:MFILE_VERSION_MAJOR
						Macros and Manifest Constants:MFILE_VERSION_MINOR
						Macros and Manifest Constants:MFILE_VERSION_RELEASE
						Macros and Manifest Constants:MFILE_VERSION_BUILD
						Defines:See Macros and Manifest Constants

	PUBLISH XREF:	MFILE_VERSION_MAJOR
						MFILE_VERSION_MINOR
						MFILE_VERSION_RELEASE
						MFILE_VERSION_BUILD
						MFILE Library Version Number
						MFILE library version number
						MFILE Library Version
						MFILE library version
						MFILE Version Number
						MFILE version number
						MFILE Version
						MFILE version

	PUBLISH NAME:	MFILE_VERSION_MAJOR
						MFILE_VERSION_MINOR
						MFILE_VERSION_RELEASE
						MFILE_VERSION_BUILD

	ENTRY CLASS	:	Macros and Manifest Constants:Library Version Number
						MFILE Version Numbers:Library Version Number

EOH */
/*	***********************************************************************	*/
#define MFILE_VERSION_MAJOR				((unsigned char) 3)
#define MFILE_VERSION_MINOR				((unsigned char) 0)
#define MFILE_VERSION_RELEASE				((unsigned char) 0)
#define MFILE_VERSION_BUILD				((unsigned char) 'A')
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		This structure is used for storage of MFILE allowable mode settings.	*/
/*	***********************************************************************	*/
typedef struct {
	char *real_mode_name;
	char *mode_name;
	int   mfile_mode;
	int   mmap_mode;
} MFILE_MODE_ITEM;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME        :	MFILE

	DESCRIPTION :	The ''MFILE'' structure is a controlling structure for
						access to memory-mapped files in the same way that the
						''C'' standard library level 2 I/O ''FILE'' structure is
						a controlling structure for normal files.

						The ''MFILE'' structure is declared as follows:

{|@|}typedef struct {
	char          *file_name;
	volatile void *mmap_ptr;
	FILE          *file_ptr;
	unsigned long  file_size;
	unsigned long  mmap_size;
	unsigned long  current_offset;
	unsigned long  buffer_size;
	int            mfile_flags;
	int            mmap_prot;
	int            mmap_flags;
	int            mmap_mode;
} MFILE;

	MEMBERS		:	The members of this structure are as follow:

						(.) ``file_name`` is a ''char'' pointer which contains the
						name of the memory-mapped file.

						(.) ``mmap_ptr`` is a pointer to the memory-mapped file
						as mapped within the process address space.

						(.) ``file_ptr`` is a pointer to a ''FILE'' structure ''C''
						language level 2 I/O descriptor.

						(.) ``file_size`` is the size of the file.

						(.) ``mmap_size`` is the memory-mapped size of the file.

						(.) ``current_offset`` is the logical current offset within
						the memory-mapped file.

						(.) ``buffer_size`` is the allocation chunk buffering size
						as specified by a call to ``msetbuf``.

						(.) ``mfile_flags`` are the MFILE file open modes with
						which the file was opened. They are some (''OR''ed)
						combination of:

						(..) ''MFILE_MODE_READ''

						(..) ''MFILE_MODE_WRITE''

						(.) ``mmap_prot`` contains the ``mmap()`` protection flags
						to be used to re-mmap the file (the manifest constants
						''PROT_READ'' and ''PROT_WRITE'' are examples of these
						flags).

						(.) ``mmap_flags`` contains the ``mmap()`` access flags to
						be used to re-mmap the file (the manifest constants
						''MAP_SHARED'' and ''MAP_PRIVATE'' are examples of these
						flags).

						(.) ``mmap_prot`` contains the ``mmap()`` protection flags
						to be used to open the file (the manifest constants
						''PROT_READ'' and ''PROT_WRITE'' are examples of these
						flags).

	CAVEATS     :	You should not access any of these structures directly as
						they are subject to change in data type and name without
						notice. In particular, the ``file_ptr`` member will be
						changed in a later release of this library to be a level
						1 I/O file descriptor handle.

						If you need access to the values of these members, you
						use the MFILE structure access macros.

	AUTHOR      :	Michael L. Brock

	COPYRIGHT   :	Copyright 1992 - 2014 Michael L. Brock

	OUTPUT INDEX:	MFILE
						Structures and Data Types:MFILE

	PUBLISH XREF:	MFILE

	PUBLISH NAME:	MFILE

	ENTRY CLASS	:	Structures and Data Types

EOH */
/*	***********************************************************************	*/
typedef struct tag_MFILE {
	char            *file_name;
	volatile void   *mmap_ptr;
	FILE            *file_ptr;
	unsigned long    file_size;
	unsigned long    mmap_size;
	unsigned long    current_offset;
	unsigned long    buffer_size;
	int              mfile_flags;
	int              mmap_prot;
	int              mmap_flags;
	int              mmap_mode;
	MTIF_MTR_HANDLE  lock_data;
} MFILE;
/*	***********************************************************************	*/

/*
	ADF NOTE: NO_ADF
	BASE NAME:	MFILE Structure Access Macros
*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Macros to get the state of an 'MFILE' structure . . .						*/
/*	***********************************************************************	*/
#define MFILE_GET_FILE_NAME_I(mfile_ptr)			\
	((mfile_ptr)->file_name)
#define MFILE_GET_MMAP_PTR_I(mfile_ptr)			\
	((mfile_ptr)->mmap_ptr)
#define MFILE_GET_FILE_HANDLE_I(mfile_ptr)		\
	(fileno((mfile_ptr)->file_ptr))
#define MFILE_GET_FILE_DESCRIPTOR_I(mfile_ptr)	\
	((mfile_ptr)->file_ptr)
#define MFILE_GET_FILE_SIZE_I(mfile_ptr)		  	\
	((mfile_ptr)->file_size)
#define MFILE_GET_MMAP_SIZE_I(mfile_ptr)		  	\
	((mfile_ptr)->mmap_size)
#define MFILE_GET_CURRENT_OFFSET_I(mfile_ptr)	\
	((mfile_ptr)->current_offset)
#define MFILE_GET_BUFFER_SIZE_I(mfile_ptr)		\
	((mfile_ptr)->buffer_size)
#define MFILE_GET_MFILE_FLAGS_I(mfile_ptr)		\
	((mfile_ptr)->mfile_flags)
#define MFILE_GET_MMAP_PROT_I(mfile_ptr)			\
	((mfile_ptr)->mmap_prot)
#define MFILE_GET_MMAP_FLAGS_I(mfile_ptr)			\
	((mfile_ptr)->mmap_flags)
#define MFILE_GET_MMAP_MODE_I(mfile_ptr)			\
	((mfile_ptr)->mmap_mode)
/*	***********************************************************************	*/

/*
	ADF NOTE: NO_ADF
	BASE NAME:	MFILE Structure Access Macros
*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Macros to get the state of an 'MFILE' structure . . .						*/
/*	***********************************************************************	*/
/*
#define MFILE_GET_file_name(mfile_ptr)						\
	((mfile_ptr)->file_name)

#define MFILE_GET_mmap_ptr(mfile_ptr)						\
	((mfile_ptr)->mmap_ptr)

#define MFILE_GET_file_handle(mfile_ptr)					\
	(fileno((mfile_ptr)->file_ptr))

#define MFILE_GET_file_descriptor(mfile_ptr)				\
	((mfile_ptr)->file_ptr)

#define MFILE_GET_file_size(mfile_ptr)						\
	((mfile_ptr)->file_size)

#define MFILE_GET_mmap_size(mfile_ptr)						\
	((mfile_ptr)->mmap_size)

#define MFILE_GET_current_offset(mfile_ptr)				\
	((mfile_ptr)->current_offset)

#define MFILE_GET_buffer_size(mfile_ptr)					\
	((mfile_ptr)->buffer_size)

#define MFILE_GET_mfile_flags(mfile_ptr)					\
	((mfile_ptr)->mfile_flags)

#define MFILE_GET_mmap_prot(mfile_ptr)						\
	((mfile_ptr)->mmap_prot)

#define MFILE_GET_mmap_flags(mfile_ptr)					\
	((mfile_ptr)->mmap_flags)

#define MFILE_GET_mmap_mode(mfile_ptr)						\
	((mfile_ptr)->mmap_mode)
*/
/*	***********************************************************************	*/

/*
	ADF NOTE: NO_ADF
*/
/*	***********************************************************************	*/
#ifdef _POSIX_C_SOURCE
# define MFILEI_IS_POSIX_C_SOURCE		MFILE_TRUE
#else
# define MFILEI_IS_POSIX_C_SOURCE		MFILE_FALSE
#endif /* #ifdef _POSIX_C_SOURCE */
/*	***********************************************************************	*/

/*
	ADF NOTE: NO_ADF
*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Macros to access to operating system memory-mapping functions . . .	*/
/*	***********************************************************************	*/
#ifdef __SVR4
# define MFILE_madvise(address, length, advice)								\
	madvise(((caddr_t) (address)), ((size_t) (length)),					\
		((int) (advice)))
# define MFILE_mctl(address, length, function, arg)						\
	mctl(((caddr_t) (address)), ((size_t) (length)),						\
		((int) (function)), ((void *) (arg)))
# define MFILE_mlock(address, length)											\
	mlock(((void *) (address)), ((size_t) (length)))
# define MFILE_mlockall(flags)													\
	mlockall(((int) (flags)))
# define MFILE_mmap(address, length, protection, flags, fd, offset)	\
	mmap(((void *) (address)), ((size_t) (length)),							\
		((int) (protection)), ((int) (flags)), ((int) (fd)),				\
		((off_t) (offset)))
# define MFILE_mprotect(address, length, protection)						\
	mprotect(((void *) (address)), ((size_t) (length)),					\
		((int) (protection)))
# define MFILE_msync(address, length, flags)									\
	msync(((void *) (address)), ((size_t) (length)),						\
		((int) (flags)))
# define MFILE_munlock(address, length)										\
	munlock(((void *) (address)), ((size_t) (length)))
# define MFILE_munlockall()														\
	munlockall()
# define MFILE_munmap(address, length)											\
	munmap(((void *) (address)), ((size_t) (length)))
#elif MFILEI_IS_POSIX_C_SOURCE
# define MFILE_madvise(address, length, advice)								\
	madvise(((caddr_t) (address)), ((size_t) (length)),					\
		((int) (advice)))
# define MFILE_mctl(address, length, function, arg)						\
	mctl(((caddr_t) (address)), ((size_t) (length)),						\
		((int) (function)), ((void *) (arg)))
# define MFILE_mlock(address, length)											\
	mlock(((const void *) (address)), ((size_t) (length)))
# define MFILE_mlockall(flags)													\
	mlockall(((int) (flags)))
# define MFILE_mmap(address, length, protection, flags, fd, offset)	\
	mmap(((void *) (address)), ((size_t) (length)),							\
		((int) (protection)), ((int) (flags)), ((int) (fd)),				\
		((off_t) (offset)))
# define MFILE_mprotect(address, length, protection)						\
	mprotect(((const void *) (address)), ((size_t) (length)),			\
		((int) (protection)))
# define MFILE_msync(address, length, flags)									\
	msync(((const void *) (address)), ((size_t) (length)),				\
		((int) (flags)))
# define MFILE_munlock(address, length)										\
	munlock(((const void *) (address)), ((size_t) (length)))
# define MFILE_munlockall()														\
	munlockall()
# define MFILE_munmap(address, length)											\
	munmap(((const void *) (address)), ((size_t) (length)))
#else
# define MFILE_madvise(address, length, advice)								\
	madvise(((caddr_t) (address)), ((int) (length)), ((int) (advice)))
# define MFILE_mctl(address, length, function, arg)						\
	mctl(((caddr_t) (address)), ((size_t) (length)),						\
		((int) (function)), ((void *) (arg)))
# define MFILE_mlock(address, length)											\
	mlock(((caddr_t) (address)), ((size_t) (length)))
# define MFILE_mlockall(flags)													\
	mlockall(((int) (flags)))
# define MFILE_mmap(address, length, protection, flags, fd, offset)	\
	mmap(((caddr_t) (address)), ((int) (length)),							\
		((int) (protection)), ((int) (flags)), ((int) (fd)),				\
		((off_t) (offset)))
# define MFILE_mprotect(address, length, protection)						\
	mprotect(((caddr_t) (address)), ((int) (length)),						\
		((int) (protection)))
# define MFILE_msync(address, length, flags)									\
	msync(((caddr_t) (address)), ((int) (length)), ((int) (flags)))
# define MFILE_munlock(address, length)										\
	munlock(((caddr_t) (address)), ((size_t) (length)))
# define MFILE_munlockall()														\
	munlockall()
# define MFILE_munmap(address, length)											\
	munmap(((caddr_t) (address)), ((int) (length)))
#endif /* # ifdef __SVR4 */
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Function prototypes for the MFILE functions . . .							*/
/*	***********************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		MFILE global locking function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int MFILE_LockGlobal,    (unsigned int *mfile_count,
	MFILE ***mfile_list, char *error_text));
COMPAT_FN_DECL(int MFILE_TryLockGlobal, (unsigned int *mfile_count,
	MFILE ***mfile_list, char *error_text));
COMPAT_FN_DECL(int MFILE_UnlockGlobal,  (char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		MFILE validation function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(const MFILE_MODE_ITEM *MFILE_ValidateMFILEMode,
	(const char *file_mode));
COMPAT_FN_DECL(int                    MFILE_ValidateMFILEPtr,
	(MFILE *mfile_ptr));
	/*	*****************************************************************	*/

/*	***********************************************************************	*/

#endif /* #ifndef h__MFILEI_H__h */

