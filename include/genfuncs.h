/* *********************************************************************** */
/* *********************************************************************** */
/*	GENFUNCS General Functions Library Include File									*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the GENFUNCS library.

	Revision History	:	1985-10-23 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1985 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

#ifndef h__GENFUNCS_H__h

# define h__GENFUNCS_H__h	1

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Necessary include files . . .														*/
/* *********************************************************************** */

#include <mbcompat.h>

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

#ifdef __MSDOS__
#elif _Windows
# ifdef _MSC_VER
#  if _MSC_VER >= 1310
#   pragma warning(disable:4668 4820)
#   include <windows.h>
#   pragma warning(default:4668)
#  elif _MSC_VER >= 1300
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
#else
# include <sys/time.h>
# include <netdb.h>
# include <unistd.h>
# include <sys/param.h>
# ifdef __SVR4
#  include <sys/siginfo.h>
# endif /* # ifdef __SVR4 */
#endif /* #ifdef __MSDOS__ */

#include <sys/types.h>
#include <sys/stat.h>

#ifdef __MSDOS__
# ifndef HAS_RPC
#  define NO_RPC
# endif /* # ifndef HAS_RPC */
#elif _Windows
# ifndef HAS_RPC
#  define NO_RPC
# endif /* # ifndef HAS_RPC */
#else
# include <sys/types.h>
#endif /* #ifdef __MSDOS__ */

#ifndef NO_STDARGS
# include <stdarg.h>
#else
# include <varargs.h>
#endif /* #ifndef NO_STDARGS */

#include <strfuncs.h>

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/*		An approximation of 'gettimeofday()' for MS-DOS and Windows . . .		*/
/* *********************************************************************** */
#ifdef __MSDOS__
# ifndef SDTIF_struct_timeval
#  define SDTIF_struct_timeval
	struct timeval { long tv_sec; long tv_usec; };
# endif /* # ifndef SDTIF_struct_timeval */
# ifndef SDTIF_struct_timespec
#  define SDTIF_struct_timespec
	struct timespec { time_t tv_sec; long tv_nsec; };
# endif /* # ifndef SDTIF_struct_timespec */
# ifndef SDTIF_struct_timezone
#  define SDTIF_struct_timezone
	struct timezone { char data; };
# endif /* # ifndef SDTIF_struct_timezone */
# ifndef gettimeofday
#  define gettimeofday(struct_timeval, time_zone)									\
		GEN_gettimeofday(struct_timeval, time_zone)
# endif /* #ifndef gettimeofday */
#elif _Windows
# ifndef SDTIF_struct_timespec
#  define SDTIF_struct_timespec
	struct timespec { time_t tv_sec; long tv_nsec; };
# endif /* # ifndef SDTIF_struct_timespec */
# ifndef SDTIF_struct_timezone
#  define SDTIF_struct_timezone
	struct timezone { char data; };
# endif /* # ifndef SDTIF_struct_timezone */
# ifndef gettimeofday
#  define gettimeofday(struct_timeval, time_zone)									\
		GEN_gettimeofday(struct_timeval, time_zone)
# endif /* #ifndef gettimeofday */
#endif /* #ifndef __MSDOS__ */
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/*    Include necessary RPC/XDR information . . .									*/
/* *********************************************************************** */
#ifndef NO_RPC
# include <rpc/rpc.h>
#else
# ifndef NO_RPC___BOOL_T_DEFINED
#  define bool_t			int
#  define NO_RPC___BOOL_T_DEFINED
# endif /* # ifndef NO_RPC___BOOL_T_DEFINED */
# ifndef NO_RPC___XDR_DEFINED
#  define NO_RPC___XDR_DEFINED
typedef struct { char x; } XDR;
#  define xdr_byte		NULL
#  define xdr_char		NULL
#  define xdr_u_char	NULL
#  define xdr_short	NULL
#  define xdr_u_short	NULL
#  define xdr_int		NULL
#  define xdr_u_int	NULL
#  define xdr_long		NULL
#  define xdr_u_long	NULL
#  define xdr_float	NULL
#  define xdr_double	NULL
# endif /* # ifndef NO_RPC___XDR_DEFINED */
#endif /* #ifndef NO_RPC */
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* *********************************************************************** */
/*
	ADF NOTE: Added 255 so as to ensure space to handle FQDNs.
*/
#ifdef _Windows
# define GEN_MAX_HOST_NAME_LEN			(MAX_COMPUTERNAME_LENGTH + 255)
# define GEN_MAX_PATH_NAME_LEN			_MAX_PATH
#elif __MSDOS__
# define GEN_MAX_HOST_NAME_LEN			64
# define GEN_MAX_PATH_NAME_LEN			255
#else
# define GEN_MAX_HOST_NAME_LEN			(MAXHOSTNAMELEN + 255)
# define GEN_MAX_PATH_NAME_LEN			MAXPATHLEN
#endif /* #ifdef _Windows */
	/*	*****************************************************************	*/

/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   BASE NAME   :  GENFUNCS Truth Codes

   NAME        :  GENFUNCS Truth Codes

   DESCRIPTION :  Manifest constants used within GENFUNCS to specify the truth
						or falsity of expressions.

						(.) ''GENFUNCS_TRUE''

						(.) ''GENFUNCS_FALSE''

   NOTES       :  The manifest constant ''GENFUNCS_TRUE'' should be defined as
						a non-zero value. Conversely, the manifest constant
						''GENFUNCS_FALSE'' should be defined as zero (''0'').

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1985 - 2018 Michael L. Brock

   OUTPUT INDEX:  GENFUNCS_TRUE
						GENFUNCS_FALSE
						GENFUNCS Truth Codes:GENFUNCS_TRUE
						GENFUNCS Truth Codes:GENFUNCS_FALSE
						GENFUNCS Manifest Constants:GENFUNCS_TRUE
						GENFUNCS Manifest Constants:GENFUNCS_FALSE
						GENFUNCS Defines:GENFUNCS_TRUE
						GENFUNCS Defines:GENFUNCS_FALSE
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:  GENFUNCS Truth Codes
						GENFUNCS Truth Code
						GENFUNCS truth codes
						GENFUNCS truth code
						GENFUNCS_TRUE
						GENFUNCS_FALSE

   PUBLISH NAME:	GENFUNCS Truth Codes
						GENFUNCS_TRUE
						GENFUNCS_FALSE

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define GENFUNCS_TRUE						1
#define GENFUNCS_FALSE						0
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   BASE NAME   :	GENFUNCS Return Codes

   NAME        :  GENFUNCS Return Codes

   DESCRIPTION :  The GENFUNCS return codes have the following meanings:

						(.) ''GENFUNCS_SUCCESS'' means that the function invoked
						completed without error. ''GENFUNCS_SUCCESS'' is guaranteed to
						be equal to zero (''0'').

						(.) ''GENFUNCS_FAILURE'' indicates that the function invoked
						encountered a general operation failure. This is the
						'catch-all' error code for those errors which do not fit
						into category of one the other GENFUNCS error codes.

						(.) ''GENFUNCS_BAD_ARGS_FAILURE'' indicates that the
						arguments passed to a function invoked were invalid.

						(.) ''GENFUNCS_MEMORY_FAILURE'' indicates that the memory
						required for operation of the function invoked could not be
						allocated.

						(.) ''GENFUNCS_SYSTEM_FAILURE'' indicates that the function invoked
						encountered a failure of a standard library function or a
						system call.

						(.) ''GENFUNCS_LOCK_ACQ_FAILURE'' indicates that a lock
						could not be acquired on a resource.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1985 - 2018 Michael L. Brock

   OUTPUT INDEX:  GENFUNCS_SUCCESS
						GENFUNCS_FAILURE
						GENFUNCS_BAD_ARGS_FAILURE
						GENFUNCS_MEMORY_FAILURE
						GENFUNCS_SYSTEM_FAILURE
						GENFUNCS_LOCK_ACQ_FAILURE
						GENFUNCS Return Codes:GENFUNCS_SUCCESS
						GENFUNCS Return Codes:GENFUNCS_FAILURE
						GENFUNCS Return Codes:GENFUNCS_BAD_ARGS_FAILURE
						GENFUNCS Return Codes:GENFUNCS_MEMORY_FAILURE
						GENFUNCS Return Codes:GENFUNCS_SYSTEM_FAILURE
						GENFUNCS Return Codes:GENFUNCS_LOCK_ACQ_FAILURE
						GENFUNCS Manifest Constants:GENFUNCS_SUCCESS
						GENFUNCS Manifest Constants:GENFUNCS_FAILURE
						GENFUNCS Manifest Constants:GENFUNCS_BAD_ARGS_FAILURE
						GENFUNCS Manifest Constants:GENFUNCS_MEMORY_FAILURE
						GENFUNCS Manifest Constants:GENFUNCS_SYSTEM_FAILURE
						GENFUNCS Manifest Constants:GENFUNCS_LOCK_ACQ_FAILURE
						GENFUNCS Defines:GENFUNCS_SUCCESS
						GENFUNCS Defines:GENFUNCS_FAILURE
						GENFUNCS Defines:GENFUNCS_BAD_ARGS_FAILURE
						GENFUNCS Defines:GENFUNCS_MEMORY_FAILURE
						GENFUNCS Defines:GENFUNCS_SYSTEM_FAILURE
						GENFUNCS Defines:GENFUNCS_LOCK_ACQ_FAILURE
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:  GENFUNCS_SUCCESS
						GENFUNCS_FAILURE
						GENFUNCS_BAD_ARGS_FAILURE
						GENFUNCS_MEMORY_FAILURE
						GENFUNCS_SYSTEM_FAILURE
						GENFUNCS_LOCK_ACQ_FAILURE
						GENFUNCS Return Codes
						GENFUNCS Return Code
						GENFUNCS return codes
						GENFUNCS return code
						GENFUNCS Status Codes
						GENFUNCS Status Code
						GENFUNCS status codes
						GENFUNCS status code
						GENFUNCS Error Codes
						GENFUNCS Error Code
						GENFUNCS error codes
						GENFUNCS error code

   PUBLISH NAME:	GENFUNCS Return Codes
						GENFUNCS return codes
						GENFUNCS_SUCCESS
						GENFUNCS_FAILURE
						GENFUNCS_BAD_ARGS_FAILURE
						GENFUNCS_MEMORY_FAILURE
						GENFUNCS_SYSTEM_FAILURE
						GENFUNCS_LOCK_ACQ_FAILURE

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define GENFUNCS_SUCCESS					 0
#define GENFUNCS_FAILURE					-1
#define GENFUNCS_BAD_ARGS_FAILURE		-2
#define GENFUNCS_MEMORY_FAILURE			-3
#define GENFUNCS_SYSTEM_FAILURE			-4
#define GENFUNCS_LOCK_ACQ_FAILURE		-5
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :  GENFUNCS_MAX_ERROR_TEXT

   DESCRIPTION :  The manifest constant ''GENFUNCS_MAX_ERROR_TEXT'' defines
						the minimum amount of storage which should be allocated to
						hold an error message returned by a GENFUNCS function.

   CAVEATS     :  GENFUNCS error messages can be quite lengthy. Therefore,
						attempting to save space by allocating less than
						''GENFUNCS_MAX_ERROR_TEXT'' bytes to error message buffers
						passed to GENFUNCS functions can lead to overwriting of the
						heap or the stack.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1985 - 2018 Michael L. Brock

   OUTPUT INDEX:  GENFUNCS_MAX_ERROR_TEXT
						GENFUNCS Manifest Constants:GENFUNCS_MAX_ERROR_TEXT
						GENFUNCS Defines:GENFUNCS_MAX_ERROR_TEXT
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	GENFUNCS_MAX_ERROR_TEXT

   PUBLISH NAME:	GENFUNCS_MAX_ERROR_TEXT

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define GENFUNCS_MAX_ERROR_TEXT			1024
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#ifdef __MSDOS__
# define GEN_IsDirSlash(in_char)		(((in_char) == '/') || ((in_char) == '\\'))
# define GEN_DirSlash					((char) '\\')
#elif _Windows
# define GEN_IsDirSlash(in_char)		(((in_char) == '/') || ((in_char) == '\\'))
# define GEN_DirSlash					((char) '\\')
#elif _MSC_VER
# define GEN_IsDirSlash(in_char)		(((in_char) == '/') || ((in_char) == '\\'))
# define GEN_DirSlash					((char) '\\')
#else
# define GEN_IsDirSlash(in_char)		((in_char) == '/')
# define GEN_DirSlash					((char) '/')
#endif /* #ifdef __MSDOS__ */
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	GEN_TVAL_STAT

	DESCRIPTION	:	The ''GEN_TVAL_STAT'' structure is designed to support
						application operational statistics gathering.

						The ''GEN_TVAL_STAT'' structure is declared as follows:

{|@|}typedef struct {
	int            maximum_stat_flag;
	unsigned long  sample_count;
	unsigned long  last_count;
	struct timeval last_start;
	struct timeval last_end;
	struct timeval last_interval;
	struct timeval tmp_last_start;
	unsigned long  total_count;
	struct timeval total_interval;
} GEN_TVAL_STAT;

	MEMBERS		:	The members of this structure are as follow:

						(.) ``maximum_stat_flag`` is an ''int'' which indicates
						whether the ''GEN_TVAL_STAT'' has stored the maximum
						number of statistics gathering passes, in which case
						it will be set to the value of the manifest constant
						''GENFUNCS_TRUE''. Otherwise, it will be set equal to the
						manifest constant ''GENFUNCS_FALSE''.

						(-) ``maximum_stat_flag`` will be set to ''GENFUNCS_TRUE''
						by the logic in the function ``GEN_TVAL_STAT_EndTimeSpecified``
						upon detection of any of the following conditions:

						(..) The ``sample_count`` member is equal to its maximum
						value of ''ULONG_MAX''.

						(..) An attempt to add the ``last_count`` member to the
						``total_count`` member results in a value greater than
						''ULONG_MAX''.

						(..) An attempt to add the ``last_interval`` member to the
						``total_interval`` member results in a number of seconds
						greater than ''ULONG_MAX''.

						(.) ``sample_count`` is an ''unsigned long'' in which is
						stored the number of statistics samples represented by
						the ''GEN_TVAL_STAT'' structure.

						(.) ``last_count`` is an ''unsigned long'' in which is
						stored the number of items processed in the last statistics
						gathering pass.

						(.) ``last_start`` is a ''struct timeval'' in which is
						stored the start time of the last statistics gathering pass.

						(.) ``last_end`` is a ''struct timeval'' in which is stored
						the end time of the last statistics gathering pass.

						(.) ``last_interval`` is a ''struct timeval'' in which is
						stored the total time taken by the last statistics gathering
						pass. That is, ``last_interval`` is equal to ``end_time``
						minus ``start_time``.

						(.) ``tmp_last_start`` is a ''struct timeval'' in which the
						start time of the current (last) statistics gathering pass
						is stored temporarily until the end of the statistics
						gathering pass.

						(.) ``total_count`` is an ''unsigned long'' in which is
						stored the total number of items processed in all
						statistics gathering passes.

						(.) ``total_interval`` is a ''struct timeval'' in which is
						stored the total time taken by all statistics gathering
						passes.

	NOTES			:	It is planned to implement (eventually) a structure
						equivalent to this one which uses the Posix ''struct
						timespec''.

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2018 Michael L. Brock

	OUTPUT INDEX:	GEN_TVAL_STAT
						Statistics Gathering Structures:GEN_TVAL_STAT
						GENFUNCS:Structures:GEN_TVAL_STAT
						GENFUNCS:Statistics Gathering Structures:GEN_TVAL_STAT
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_TVAL_STAT

	PUBLISH NAME:	GEN_TVAL_STAT

	ENTRY CLASS	:	Structures and Data Types

EOH */
/*	***********************************************************************	*/
typedef struct {
	int            maximum_stat_flag;
	unsigned long  sample_count;
	unsigned long  last_count;
	struct timeval last_start;
	struct timeval last_end;
	struct timeval last_interval;
	struct timeval tmp_last_start;
	unsigned long  total_count;
	struct timeval total_interval;
} GEN_TVAL_STAT;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define GEN_FMT_TIME_LEN_ULONG			10
#define GEN_FMT_TIME_LEN_TIME_T			19
#define GEN_FMT_TIME_LEN_TM				19
#define GEN_FMT_TIME_LEN_TIMEVAL			27
#define GEN_FMT_TIME_LEN_TIMESPEC		30
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Manifest constants used by the pointer validation routines . . .		*/
/* *********************************************************************** */

#define GEN_VPTR_ACCESS_READ				1
#define GEN_VPTR_ACCESS_WRITE				2
#define GEN_VPTR_ACCESS_READ_WRITE		\
	(GEN_VPTR_ACCESS_READ | GEN_VPTR_ACCESS_WRITE)

#define GEN_VPTR_ACCESS_BIT_READ			1
#define GEN_VPTR_ACCESS_BIT_WRITE		2
#define GEN_VPTR_ACCESS_BIT_READ_WRITE	\
	(GEN_VPTR_ACCESS_BIT_READ | GEN_VPTR_ACCESS_BIT_WRITE)

#define GEN_VPTR_ACCESS_BIT_ACCESS_MASK	(UCHAR_MAX & 1)
#define GEN_VPTR_ACCESS_BIT_MODE_MASK		(UCHAR_MAX & 3)

#define GEN_VPTR_ACCESS_BIT_ACCESS_BYTE(byte_offset)					\
	((byte_offset) / CHAR_BIT)
#define GEN_VPTR_ACCESS_BIT_MODE_BYTE(byte_offset)						\
	((byte_offset) / (CHAR_BIT / 2))

#define GEN_VPTR_ACCESS_BIT_ACCESS_SHIFT(byte_offset)					\
	((byte_offset) % CHAR_BIT)
#define GEN_VPTR_ACCESS_BIT_MODE_SHIFT(byte_offset) 					\
	(((byte_offset) % (CHAR_BIT / 2)) * 2)

#define GEN_VPTR_ACCESS_BIT_ACCESS_COLOR(byte_offset, bit_string)	\
	((bit_string[GEN_VPTR_ACCESS_BIT_ACCESS_BYTE(byte_offset)] >>	\
	GEN_VPTR_ACCESS_BIT_ACCESS_SHIFT(byte_offset)) & 					\
	GEN_VPTR_ACCESS_BIT_ACCESS_MASK)

#define GEN_VPTR_ACCESS_BIT_MODE_COLOR(byte_offset, bit_string)	\
	((bit_string[GEN_VPTR_ACCESS_BIT_MODE_BYTE(byte_offset)] >>		\
	GEN_VPTR_ACCESS_BIT_MODE_SHIFT(byte_offset)) &						\
	GEN_VPTR_ACCESS_BIT_MODE_MASK)

/* *********************************************************************** */

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define GEN_PMAP_FLAG_READ			0X01
#define GEN_PMAP_FLAG_WRITE		0X02
#define GEN_PMAP_FLAG_EXEC			0X04
#define GEN_PMAP_FLAG_SHARED		0X08
#define GEN_PMAP_FLAG_ANON			0X10
#define GEN_PMAP_FLAG_BREAK		0X20
#define GEN_PMAP_FLAG_STACK		0X40
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef struct {
	void         *address;
	unsigned int  size;
	unsigned int  offset;
	unsigned int  sys_flags;
	unsigned int  flags;
	unsigned int  page_size;
} GEN_PMAP_DESC;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/* *********************************************************************** */
/* *********************************************************************** */
/*		Macros used to manipulate structures of type 'timeval'.					*/
/* *********************************************************************** */
#define GEN_COMPARE_TIMEVAL(time_ptr_1, time_ptr_2)							\
	((int) ((time_ptr_1)->tv_sec > (time_ptr_2)->tv_sec) ? 1 :				\
		(((time_ptr_1)->tv_sec < (time_ptr_2)->tv_sec) ? -1 :					\
		(((time_ptr_1)->tv_usec > (time_ptr_2)->tv_usec) ? 1 :				\
		(((time_ptr_1)->tv_usec < (time_ptr_2)->tv_usec) ? -1 : 0))))

#define GEN_GET_TIMEVAL_USECS_DOUBLE(time_ptr)		\
	((((double) (time_ptr)->tv_sec) * 1000000.0) +	\
	((double) (time_ptr)->tv_usec))

#define GEN_GET_TIMEVAL_USECS(time_ptr)				\
	((unsigned long) GEN_GET_TIMEVAL_USECS_DOUBLE(time_ptr))
/* *********************************************************************** */

/*	***********************************************************************	*/
/* *********************************************************************** */
/* *********************************************************************** */
/*		Macros used to manipulate structures of type 'timespec'.					*/
/* *********************************************************************** */
#define GEN_COMPARE_TIMESPEC(time_ptr_1, time_ptr_2)							\
	((int) ((time_ptr_1)->tv_sec > (time_ptr_2)->tv_sec) ? 1 :				\
		(((time_ptr_1)->tv_sec < (time_ptr_2)->tv_sec) ? -1 :					\
		(((time_ptr_1)->tv_nsec > (time_ptr_2)->tv_nsec) ? 1 :				\
		(((time_ptr_1)->tv_nsec < (time_ptr_2)->tv_nsec) ? -1 : 0))))

#define GEN_GET_TIMESPEC_NSECS_DOUBLE(time_ptr)			\
	((((double) (time_ptr)->tv_sec) * 1000000000.0) +	\
	((double) (time_ptr)->tv_nsec))

#define GEN_GET_TIMESPEC_NSECS(time_ptr)					\
	((unsigned long) GEN_GET_TIMESPEC_NSECS_DOUBLE(time_ptr))
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	BASE NAME	:	GENFUNCS Align Types

   NAME        :  GENFUNCS Align Types

   DESCRIPTION :  Manifest constants used to define the primitive types
						available on an architecture.

						(.)''GEN_C_ALIGN_unsigned_byte'' defines the type of an
						``unsigned char``.

						(.)''GEN_C_ALIGN_char'' defines the type of a ``char``.

						(.)''GEN_C_ALIGN_unsigned_char'' defines the type of an
						``unsigned char``.

						(.)''GEN_C_ALIGN_short'' defines the type of a ``short``.

						(.)''GEN_C_ALIGN_unsigned_short'' defines the type of an
						``unsigned short``.

						(.)''GEN_C_ALIGN_int'' defines the type of an ``int``.

						(.)''GEN_C_ALIGN_unsigned_int'' defines the type of an
						``unsigned int``.

						(.)''GEN_C_ALIGN_long'' defines the type of a ``long``.

						(.)''GEN_C_ALIGN_unsigned_long'' defines the type of an
						``unsigned long``.

						(.)''GEN_C_ALIGN_float'' defines the type of a ``float``.

						(.)''GEN_C_ALIGN_double'' defines the type of a ``double``.

   NOTES       :  ''GEN_C_ALIGN_unsigned_byte'' is considered to be a type
						separate from ''GEN_C_ALIGN_unsigned_char'' for the
						purposes of comparison and display.

	CAVEATS     :  Note that these manifest constants are indices into the
						global array ``GEN_ALIGN_TypeList``. They should therefore
						always be numbered sequentially beginning at zero.

   SEE ALSO    :  GEN_ALIGN_TypeCount
						GEN_ALIGN_TypeList

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:  GEN_C_ALIGN_unsigned_byte
						GEN_C_ALIGN_char
						GEN_C_ALIGN_unsigned_char
						GEN_C_ALIGN_short
						GEN_C_ALIGN_unsigned_short
						GEN_C_ALIGN_int
						GEN_C_ALIGN_unsigned_int
						GEN_C_ALIGN_long
						GEN_C_ALIGN_unsigned_long
						GEN_C_ALIGN_float
						GEN_C_ALIGN_double
						GENFUNCS Align Types:GEN_C_ALIGN_unsigned_byte
						GENFUNCS Align Types:GEN_C_ALIGN_char
						GENFUNCS Align Types:GEN_C_ALIGN_unsigned_char
						GENFUNCS Align Types:GEN_C_ALIGN_short
						GENFUNCS Align Types:GEN_C_ALIGN_unsigned_short
						GENFUNCS Align Types:GEN_C_ALIGN_int
						GENFUNCS Align Types:GEN_C_ALIGN_unsigned_int
						GENFUNCS Align Types:GEN_C_ALIGN_long
						GENFUNCS Align Types:GEN_C_ALIGN_unsigned_long
						GENFUNCS Align Types:GEN_C_ALIGN_float
						GENFUNCS Align Types:GEN_C_ALIGN_double
						GENFUNCS Manifest Constants:GEN_C_ALIGN_unsigned_byte
						GENFUNCS Manifest Constants:GEN_C_ALIGN_char
						GENFUNCS Manifest Constants:GEN_C_ALIGN_unsigned_char
						GENFUNCS Manifest Constants:GEN_C_ALIGN_short
						GENFUNCS Manifest Constants:GEN_C_ALIGN_unsigned_short
						GENFUNCS Manifest Constants:GEN_C_ALIGN_int
						GENFUNCS Manifest Constants:GEN_C_ALIGN_unsigned_int
						GENFUNCS Manifest Constants:GEN_C_ALIGN_long
						GENFUNCS Manifest Constants:GEN_C_ALIGN_unsigned_long
						GENFUNCS Manifest Constants:GEN_C_ALIGN_float
						GENFUNCS Manifest Constants:GEN_C_ALIGN_double
						GENFUNCS Defines:GEN_C_ALIGN_unsigned_byte
						GENFUNCS Defines:GEN_C_ALIGN_char
						GENFUNCS Defines:GEN_C_ALIGN_unsigned_char
						GENFUNCS Defines:GEN_C_ALIGN_short
						GENFUNCS Defines:GEN_C_ALIGN_unsigned_short
						GENFUNCS Defines:GEN_C_ALIGN_int
						GENFUNCS Defines:GEN_C_ALIGN_unsigned_int
						GENFUNCS Defines:GEN_C_ALIGN_long
						GENFUNCS Defines:GEN_C_ALIGN_unsigned_long
						GENFUNCS Defines:GEN_C_ALIGN_float
						GENFUNCS Defines:GEN_C_ALIGN_double
						Defines:See Macros and Manifest Constants

	PUBLISH XREF:	GENFUNCS Align Types
						GENFUNCS align types
						GENFUNCS Align Type
						GENFUNCS align type
						GENFUNCS Alignment Types
						GENFUNCS alignment types
						GENFUNCS Alignment Type
						GENFUNCS alignment type
						GEN_C_ALIGN_unsigned_byte
						GEN_C_ALIGN_char
						GEN_C_ALIGN_unsigned_char
						GEN_C_ALIGN_short
						GEN_C_ALIGN_unsigned_short
						GEN_C_ALIGN_int
						GEN_C_ALIGN_unsigned_int
						GEN_C_ALIGN_long
						GEN_C_ALIGN_unsigned_long
						GEN_C_ALIGN_float
						GEN_C_ALIGN_double

	PUBLISH NAME:	GEN_C_ALIGN_unsigned_byte
						GEN_C_ALIGN_char
						GEN_C_ALIGN_unsigned_char
						GEN_C_ALIGN_short
						GEN_C_ALIGN_unsigned_short
						GEN_C_ALIGN_int
						GEN_C_ALIGN_unsigned_int
						GEN_C_ALIGN_long
						GEN_C_ALIGN_unsigned_long
						GEN_C_ALIGN_float
						GEN_C_ALIGN_double

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/* *********************************************************************** */
#define GEN_C_ALIGN_unsigned_byte	((unsigned int) 0)
#define GEN_C_ALIGN_char				((unsigned int) 1)
#define GEN_C_ALIGN_unsigned_char	((unsigned int) 2)
#define GEN_C_ALIGN_short				((unsigned int) 3)
#define GEN_C_ALIGN_unsigned_short	((unsigned int) 4)
#define GEN_C_ALIGN_int					((unsigned int) 5)
#define GEN_C_ALIGN_unsigned_int		((unsigned int) 6)
#define GEN_C_ALIGN_long				((unsigned int) 7)
#define GEN_C_ALIGN_unsigned_long	((unsigned int) 8)
#define GEN_C_ALIGN_float				((unsigned int) 9)
#define GEN_C_ALIGN_double				((unsigned int) 10)
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	GEN_ALIGN_SPEC

	DESCRIPTION	:	The ''GEN_ALIGN_SPEC'' structure supports the description
						of the size and alignment requirements of machine
						architecture primitive types.

						The ''GEN_ALIGN_SPEC'' structure is declared as follows:

{|@|}typedef struct {
	char          *type_name;
	char          *short_type_name;
	char           type_abbreviation;
	unsigned int   type_align;
	unsigned int   type_length;
	char          *printf_format;
	unsigned int   printf_length;
	int          (*compare_method)(void *data_ptr, const void *data_ptr_1,
						const void *data_ptr_2, size_t data_length);
	bool_t       (*xdr_method)(XDR *, void *);
} GEN_ALIGN_SPEC;

	MEMBERS		:	The members of this structure are as follow:

						(.) ``type_name`` is a ''char'' pointer which points to the
						string which contains the type name of the primitive data
						type.

						(-) Most implementations define an array of
						''GEN_ALIGN_SPEC'' structures with the following
						``type_name`` members:

{|@|}unsigned byte
signed char
unsigned char
signed short
unsigned short
signed int
unsigned int
signed long
unsigned long
float
double

						(.) ``short_type_name`` is a ''char'' pointer which points
						to the string which contains a short type name of the
						primitive data type.

						(-) Most implementations define an array of
						''GEN_ALIGN_SPEC'' structures with the following
						``short_type_name`` members:

{|@|}ubyte
schar
uchar
sshort
ushort
sint
uint
slong
ulong
float
double

						(.) ``type_abbreviation`` is a ''char'' which contains the
						single character abbreviation of the primitive data type.

						(-) Most implementations define an array of
						''GEN_ALIGN_SPEC'' structures with the following
						``type_abbreviation`` members:

{|@|}b
c
C
s
S
i
I
l
L
f
d

						(.) ``type_align`` is an ''unsigned int'' which contains the
						alignment requirement, in bytes, of the primitive data
						type.

						(-) For example, for code compiled with an MS-DOS compiler,
						the ``type_align`` member describing the ''double''
						primitive data type would (assuming no special compile-time
						options or pragmas were used) be ''1''. This indicates that
						the ''double'' primitive data type must be aligned on a
						memory address which is an integral multiple of ''1'' ---
						that is to say, any memory address.

						(-) Alternatively, for code compiled for the a SPARC
						architecture such as a Sun workstation, the ``type_align``
						member describing the ''double'' primitive data type would
						be ''8''. This indicates that the ''double'' primitive data
						type must be aligned on a memory address which is an
						integral multiple of ''8''

						(.) ``type_length`` is an ''unsigned int'' which contains
						the length, in bytes, of the primitive data type. This
						value should be the same as that returned by the ''C''
						language construct ``sizeof()``.

						(.) ``printf_format`` is a ''char'' pointer which points to
						the string which contains the default ``printf`` format
						for the primitive data type.

						(.) ``printf_length`` is an ''unsigned int'' which contains
						the length of the primitive data type when printed using the
						default ``printf`` format in ``printf_format``.

						(.) ``compare_method`` is a pointer to a comparison function
						for the primitive data type. This function has the
						following prototype:

{|-|}int (*compare_method)(void *data_ptr, const void *data_ptr_1,
	const void *data_ptr_2, size_t data_length);

						(.) ``xdr_method`` is a pointer to an XDR function for the
						primitive data type. This function has the following
						prototype:

{|-|}bool_t (*xdr_method)(XDR *, void *);

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2018 Michael L. Brock

	OUTPUT INDEX:	GEN_ALIGN_SPEC
						Alignment Structures:GEN_ALIGN_SPEC
						GENFUNCS:Structures:GEN_ALIGN_SPEC
						GENFUNCS:Alignment Structures:GEN_ALIGN_SPEC
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_ALIGN_SPEC

	PUBLISH NAME:	GEN_ALIGN_SPEC

	ENTRY CLASS	:	Structures and Data Types

EOH */
/*	***********************************************************************	*/
typedef struct {
	char          *type_name;
	char          *short_type_name;
	char           type_abbreviation;
	unsigned int   type_align;
	unsigned int   type_length;
	char          *printf_format;
	unsigned int   printf_length;
#ifndef NARGS
	int          (*compare_method)(void *data_ptr, const void *data_ptr_1,
						const void *data_ptr_2, size_t data_length);
	bool_t       (*xdr_method)(XDR *, void *);
#else
	int          (*compare_method)();
	bool_t       (*xdr_method)();
#endif /* #ifndef NARGS */
} GEN_ALIGN_SPEC;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		For compatibility with old code . . .											*/
/*	***********************************************************************	*/
#define GEN_ALIGN_DESCRIPTOR				GEN_ALIGN_SPEC
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		For compatibility with old code . . .											*/
/*	***********************************************************************	*/
#define GEN_AlignCount						GEN_ALIGN_TypeCount
#define GEN_AlignList						GEN_ALIGN_TypeList
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	GEN_ALIGN

	DESCRIPTION	:	The ''GEN_ALIGN'' structure describes the size and offset
						of a datum as required by the alignment requirements and
						primitive type sizes of a processor architecture.

						The ''GEN_ALIGN'' structure is declared as follows:

{|@|}typedef struct {
	unsigned int type;
	unsigned int array_length;
	unsigned int offset;
	unsigned int length;
} GEN_ALIGN;

	MEMBERS		:	The members of this structure are as follow:

						(.) ``type`` is the primitive type of the datum. It takes
						the value of one of the defined GENFUNCS alignment types,
						specified as one of the following manifest constants:

						(..) ''GEN_C_ALIGN_unsigned_byte'' defines the type of an
						``unsigned char``.

						(..) ''GEN_C_ALIGN_char'' defines the type of a ``char``.

						(..) ''GEN_C_ALIGN_unsigned_char'' defines the type of an
						``unsigned char``.

						(..) ''GEN_C_ALIGN_short'' defines the type of a ``short``.

						(..) ''GEN_C_ALIGN_unsigned_short'' defines the type of an
						``unsigned short``.

						(..) ''GEN_C_ALIGN_int'' defines the type of an ``int``.

						(..) ''GEN_C_ALIGN_unsigned_int'' defines the type of an
						``unsigned int``.

						(..) ''GEN_C_ALIGN_long'' defines the type of a ``long``.

						(..) ''GEN_C_ALIGN_unsigned_long'' defines the type of an
						``unsigned long``.

						(..) ''GEN_C_ALIGN_float'' defines the type of a ``float``.

						(..) ''GEN_C_ALIGN_double'' defines the type of a ``double``.

						(.) ``array_length`` is the number of primitive types which
						constitute the datum. For scalar data, ``array_length`` is
						''1''.

						(.) ``offset`` is the offset of the datum.

						(.) ``length`` is the total length of the datum --- that is,
						the length of the primitive type multiplied by the
						``array_length`` member of this structure.

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2018 Michael L. Brock

	OUTPUT INDEX:	GEN_ALIGN
						Alignment Structures:GEN_ALIGN
						GENFUNCS:Structures:GEN_ALIGN
						GENFUNCS:Alignment Structures:GEN_ALIGN
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_ALIGN

	PUBLISH NAME:	GEN_ALIGN

	ENTRY CLASS	:	Structures and Data Types

EOH */
/*	***********************************************************************	*/
typedef struct {
	unsigned int type;
	unsigned int array_length;
	unsigned int offset;
	unsigned int length;
} GEN_ALIGN;
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* *********************************************************************** */
typedef struct {
	int           ignore_case_flag;
	unsigned int  align_count;
	GEN_ALIGN    *align_list;
} GEN_ALIGN_CMP;
/* *********************************************************************** */

/*
	ADF NOTE: Need ADF comments.
*/
#define GEN_MEMBER_MAX_NAME				31
#define GEN_MEMBER_MAX_TYPE_SPEC			31
#define GEN_MEMBER_MAX_ALIGN_COUNT		((GEN_MEMBER_MAX_TYPE_SPEC + 1) / 2)

#define GEN_MEMBER_ALIGN_EMPTY_LIST		\
	{ {0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0} }

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_MEMBER

   DESCRIPTION :	The ''GEN_MEMBER'' structure defines a single datum of a
						structure or record.

						The ''GEN_MEMBER'' structure is declared as follows:

{|@|}typedef struct tag_GEN_MEMBER {
	char           name[GEN_MEMBER_MAX_NAME + 1];
	unsigned int   data_length;
	unsigned int   length;
	unsigned int   offset;
	unsigned int   type_count;
	char           type_spec[GEN_MEMBER_MAX_TYPE_SPEC + 1];
	unsigned int   align_count;
	GEN_ALIGN      align_list[GEN_MEMBER_MAX_ALIGN_COUNT];
	unsigned int   display_length;
	char          *display_name;
	int            dbc_type;
	int          (*length_function)(unsigned int type_count,
							const GEN_ALIGN_SPEC *type_list,
							struct tag_GEN_MEMBER *member_ptr,
							int header_flag, unsigned int intra_field_length,
							unsigned int null_string_length, void *user_data_ptr,
							char *error_text);
	void         (*dump_function)(unsigned int type_count,
							const GEN_ALIGN_SPEC *type_list,
							const struct tag_GEN_MEMBER *member_ptr,
							const char *record_ptr, int null_flag,
							const char *intra_field_sep, const char *null_string,
							const char *overflow_char, void *user_data_ptr,
							STR_FUNC_TYPE_fprintf output_function,
							void *output_control);
	int            user_int_1;
	int            user_int_2;
	void          *user_ptr_1;
	void          *user_ptr_2;
} GEN_MEMBER;

	MEMBERS		:	The members of this structure are as follow:

						(.) ``name`` is an array of ''char'' which contains the name
						of the datum. It is ''GEN_MEMBER_MAX_NAME'' + ''1''
						characters in length.

						(.) ``data_length`` is an ''unsigned int'' which contains
						the length of the datum which is available for data storage.

						(.) ``length`` is an ''unsigned int'' which contains the
						actual length of the datum. For character columns (such as
						the Sybase ''char'' and ''varchar'' types), the ``length``
						value is ''1'' greater than the ``data_length`` value
						because a single character position is reserved for the
						terminating ASCII ''0'' byte.

						(.) ``offset`` is an ''unsigned int'' which contains
						the offset of the datum within its structure or record.

						(.) ``type_count`` is an ''unsigned int'' which contains
						the number of instantiations of the primitive types
						specified in the ``type_spec`` member which together
						constitute the datum.

						(.) ``type_spec`` is an array of ''char'' which contains
						the primitive alignment specification of the datum in
						string format. This specification may be converted into
						an array ''GEN_ALIGN'' structures by using it as a parameter
						to such functions as ``GEN_ALIGN_AlignString``.

						(-) ``type_spec`` is ''GEN_MEMBER_MAX_TYPE_SPEC'' + ''1''
						characters in length.

						(.) ``align_count`` is an ''unsigned int'' which contains
						the number of elements in ``align_list``.

						(.) ``align_list`` is an array of ''GEN_ALIGN'' structures.
						When populated with data derived from the ``type_spec``
						member, the elements of this array correspond to the type
						description encoded in the ``type_count`` and ``type_spec``
						members.

						(-) ``align_list`` has ''GEN_MEMBER_MAX_ALIGN_COUNT''
						elements, which is sufficient to represent any description
						in ``type_spec``. ''GEN_MEMBER_MAX_ALIGN_COUNT'' is defined
						as:

						{|@|}((GEN_MEMBER_MAX_TYPE_SPEC + 1) / 2)

						This works because each type specification in the
						``type_spec`` member requires one character to represent a
						primitive type, and a single comma character to separate it
						from the next type specification character.

						(.) ``display_length`` ADF NOTE: ADF comment needed here

						(.) ``display_name`` ADF NOTE: ADF comment needed here

						(.) ``dbc_type`` is reserved for use by the DBCFUNCS
						library. It is used to store the facility-specific DBMS
						type.

						(.) ``length_function`` is a pointer to a function which
						ADF NOTE HERE

						(.) ``dump_function`` is a pointer to a function which
						ADF NOTE HERE

						(.) ``user_int_1`` is an ''int'' reserved for use by the
						implementation.

						(.) ``user_int_2`` is an ''int'' reserved for use by the
						implementation.

						(.) ``user_ptr_1`` is a pointer to ''void'' reserved for
						use by the implementation.

						(.) ``user_ptr_2`` is a pointer to ''void'' reserved for
						use by the implementation.

	AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_MEMBER
						Structures and Data Types:GEN_MEMBER
						GENFUNCS:Structures:GEN_MEMBER
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_MEMBER

   PUBLISH NAME:	GEN_MEMBER

	ENTRY CLASS	:	Structures and Data Types

EOH */
/*	***********************************************************************	*/
typedef struct tag_GEN_MEMBER {
	char           name[GEN_MEMBER_MAX_NAME + 1];
	unsigned int   data_length;
	unsigned int   length;
	unsigned int   offset;
	unsigned int   type_count;
	char           type_spec[GEN_MEMBER_MAX_TYPE_SPEC + 1];
	unsigned int   align_count;
	GEN_ALIGN      align_list[GEN_MEMBER_MAX_ALIGN_COUNT];
	unsigned int   display_length;
	char          *display_name;
	int            dbc_type;
#ifndef NARGS
	int          (*length_function)(unsigned int type_count,
							const GEN_ALIGN_SPEC *type_list,
							struct tag_GEN_MEMBER *member_ptr,
							int header_flag, unsigned int intra_field_length,
							unsigned int null_string_length, void *user_data_ptr,
							char *error_text);
	void         (*dump_function)(unsigned int type_count,
							const GEN_ALIGN_SPEC *type_list,
							const struct tag_GEN_MEMBER *member_ptr,
							const void *record_ptr, int null_flag,
							const char *intra_field_sep, const char *null_string,
							const char *overflow_char, void *user_data_ptr,
							STR_FUNC_TYPE_fprintf output_function,
							void *output_control);
#else
	int          (*length_function)();
	void         (*dump_function)();
#endif /* #ifndef NARGS */
	int            user_int_1;
	int            user_int_2;
	void          *user_ptr_1;
	void          *user_ptr_2;
} GEN_MEMBER;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
typedef struct {
	char          name[31 + 1];
	unsigned int  size;
	unsigned int  member_count;
	GEN_MEMBER   *member_list;
} GEN_ALIGN_STRUCT;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	GEN_ERROR_SPEC

	DESCRIPTION	:	The ''GEN_ERROR_SPEC'' structure is designed to
						store operating system error message description text.

						The ''GEN_ERROR_SPEC'' structure is declared as follows:

{|@|}typedef struct {
	int   error_code;
	char *error_name;
	char *short_description;
	char *long_description;
} GEN_ERROR_SPEC;

	MEMBERS		:	The members of this structure are as follow:

						(.) ``error_code`` is the operating system error code
						number. This value corresponds to the Unix C library
						variable ``errno``.

						(.) ``error_name`` is the symbolic name of error, such as
						''ENOENT'' and ''ENOFILE''.

						(.) ``short_description`` is a short text description of the
						error. Under SunOS 4.1.3, for example, if ``error_code``
						is ''2'', ``error_name`` will be ``ENOENT``, and
						``short_description`` will read:

						<|-|> No such file or directory

						(.) ``long_description`` is an extended text description
						of the error. Under SunOS 4.1.3, for example, if
						``error_code`` is ''2'', ``error_name`` will be ``ENOENT``,
						and ``long_description`` will read:

						<|-|> This error occurs when a file name is specified and
						the file should exist but does not, or when one of the
						directories in a path name does not exist.

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2018 Michael L. Brock

	OUTPUT INDEX:	GEN_ERROR_SPEC
						Error Description Structures:GEN_ERROR_SPEC
						GENFUNCS:Structures:GEN_ERROR_SPEC
						GENFUNCS:Error Description Structures:GEN_ERROR_SPEC
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_ERROR_SPEC

	PUBLISH NAME:	GEN_ERROR_SPEC

	ENTRY CLASS	:	Structures and Data Types

EOH */
/*	***********************************************************************	*/
typedef struct {
	int   error_code;
	char *error_name;
	char *short_description;
	char *long_description;
} GEN_ERROR_SPEC;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		For compatibility with old code . . .											*/
/*	***********************************************************************	*/
#define GEN_ERROR_DESCRIPTION				GEN_ERROR_SPEC
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   BASE NAME   :	GENFUNCS Reader Exclusion Lock Values

   NAME        :  GENFUNCS Reader Exclusion Lock Values

   DESCRIPTION :  The GENFUNCS reader exclusion lock values manifest constants
						provide values for the setting and testing of the
						reader-exclusion lock type ''GEN_LOCK_READEX''.

						The GENFUNCS reader exclusion lock values have the
						following meaning:

						(.) ''GEN_LOCK_READEX_FLAG_INIT'' is the value with which
						a ''GEN_LOCK_READEX'' is initialized.

						(.) ''GEN_LOCK_READEX_FLAG_MASK'' masks out all but the
						single high-order lock bit which indicates that the
						''GEN_LOCK_READEX'' is locked. The result of ''AND''ing
						a ''GEN_LOCK_READEX'' with this manifest constant is a
						non-zero value if it is locked.

						(.) ''GEN_LOCK_READEX_COUNT_MASK'' masks out the single
						high-order lock bit. The result of ''AND''ing a
						''GEN_LOCK_READEX'' with this manifest constant is the
						number of lock cycles.

   SEE ALSO    :  GEN_LOCK_READEX

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1991 - 2018 Michael L. Brock

   OUTPUT INDEX:  GEN_LOCK_READEX_FLAG_INIT
						GEN_LOCK_READEX_FLAG_MASK
						GEN_LOCK_READEX_COUNT_MASK
						GENFUNCS Reader Exclusion Lock Values:GEN_LOCK_READEX_FLAG_INIT
						GENFUNCS Reader Exclusion Lock Values:GEN_LOCK_READEX_FLAG_MASK
						GENFUNCS Reader Exclusion Lock Values:GEN_LOCK_READEX_COUNT_MASK
						GENFUNCS Manifest Constants:GEN_LOCK_READEX_FLAG_INIT
						GENFUNCS Manifest Constants:GEN_LOCK_READEX_FLAG_MASK
						GENFUNCS Manifest Constants:GEN_LOCK_READEX_COUNT_MASK
						GENFUNCS Defines:GEN_LOCK_READEX_FLAG_INIT
						GENFUNCS Defines:GEN_LOCK_READEX_FLAG_MASK
						GENFUNCS Defines:GEN_LOCK_READEX_COUNT_MASK
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:  GEN_LOCK_READEX_FLAG_INIT
						GEN_LOCK_READEX_FLAG_MASK
						GEN_LOCK_READEX_COUNT_MASK
						GENFUNCS Reader Exclusion Lock Values
						GENFUNCS reader exclusion lock values
						GENFUNCS Reader Exclusion Lock Value
						GENFUNCS reader exclusion lock value

   PUBLISH NAME:	GEN_LOCK_READEX_FLAG_INIT
						GEN_LOCK_READEX_FLAG_MASK
						GEN_LOCK_READEX_COUNT_MASK

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define GEN_LOCK_READEX_FLAG_INIT		((unsigned long) 0X0000000L)
#define GEN_LOCK_READEX_FLAG_MASK		((unsigned long) 0X8000000L)
#define GEN_LOCK_READEX_COUNT_MASK		((unsigned long) 0X7FFFFFFL)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	GENFUNCS Debugging Levels

   NAME        :	GENFUNCS Debugging Levels

   DESCRIPTION :	Manifest constants used by GENFUNCS to specify the degree of
						debugging logging to be performed.

						The following debugging levels are defined.

						(.) ''GEN_DEBUG_LEVEL_NONE'' indicates that no special
						debugging logging is to be performed.

						(.) ''GEN_DEBUG_LEVEL_BASIC'' indicates that basic
						debugging logging is to be performed.

						(.) ''GEN_DEBUG_LEVEL_COMPLETE'' indicates that the
						maximum debugging logging is to be performed.

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_DEBUG_LEVEL_NONE
						GEN_DEBUG_LEVEL_BASIC
						GEN_DEBUG_LEVEL_COMPLETE
						Debugging Levels:GEN_DEBUG_LEVEL_NONE
						Debugging Levels:GEN_DEBUG_LEVEL_BASIC
						Debugging Levels:GEN_DEBUG_LEVEL_COMPLETE
						Macros and Manifest Constants:GEN_DEBUG_LEVEL_NONE
						Macros and Manifest Constants:GEN_DEBUG_LEVEL_BASIC
						Macros and Manifest Constants:GEN_DEBUG_LEVEL_COMPLETE
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	GEN_DEBUG_LEVEL_NONE
						GEN_DEBUG_LEVEL_BASIC
						GEN_DEBUG_LEVEL_COMPLETE
						GENFUNCS Debugging Levels
						GENFUNCS Debugging Level
						GENFUNCS debugging levels
						GENFUNCS debugging level

   PUBLISH NAME:	GEN_DEBUG_LEVEL_NONE
						GEN_DEBUG_LEVEL_BASIC
						GEN_DEBUG_LEVEL_COMPLETE

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define GEN_DEBUG_LEVEL_NONE				0
#define GEN_DEBUG_LEVEL_BASIC				1
#define GEN_DEBUG_LEVEL_COMPLETE			2
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	GEN_LOCK_READEX

	DESCRIPTION	:	The ''GEN_LOCK_READEX'' structure is designed to support
						reader-exclusion locking.

						Reader-exclusion locking is designed for use where:

						(.) There is only one writer to a resource.

						(.) The writer must operate with minimum latency.

						(.) There can be one or more readers.

						The ''GEN_LOCK_READEX'' type is declared as follows:

{|@|}typedef unsigned long GEN_LOCK_READEX;

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1991 - 2018 Michael L. Brock

	OUTPUT INDEX:	GEN_LOCK_READEX
						Structures and Data Types:GEN_LOCK_READEX
						GENFUNCS:Structures and Data Types:GEN_LOCK_READEX
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_LOCK_READEX

	PUBLISH NAME:	GEN_LOCK_READEX

	ENTRY CLASS	:	Structures and Data Types

EOH */
/*	***********************************************************************	*/
typedef unsigned long GEN_LOCK_READEX;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/* *********************************************************************** */
typedef struct {
	int    optional_flag;
#ifndef NARGS
	int  (*usage_function)(const char *base_arg_ptr, int optional_flag,
		char **extra_usage_list, unsigned int *usage_count, char ***usage_list,
		char *error_text);
#else
	int  (*usage_function)();
#endif /* #ifndef NARGS */
	char  *added_text;
} GEN_USAGE_PARAM;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		How to format 'GEN_RUSAGE' NULL values . . .									*/
/*	***********************************************************************	*/
#define GEN_RUSAGE_NULL_FORMAT_NONE		0
#define GEN_RUSAGE_NULL_FORMAT_ZERO		1
#define GEN_RUSAGE_NULL_FORMAT_NULL		2
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	GEN_RUSAGE

	DESCRIPTION	:	The ''GEN_RUSAGE'' contains members which describe, in a
						fashion independent of the operating system, the resource
						usage of an executable.

						The ''GEN_RUSAGE'' is declared as follows:

{|@|}typedef struct {
	struct timeval user_cpu_time;
	struct timeval system_cpu_time;
	struct timeval trap_cpu_time;
	struct timeval text_pagef_time;
	struct timeval data_pagef_time;
	struct timeval kernel_pagef_time;
	struct timeval user_lock_time;
	struct timeval other_sleep_time;
	struct timeval wait_cpu_time;
	struct timeval stopped_time;
	unsigned long  minor_pagef;
	unsigned long  major_pagef;
	unsigned long  process_swaps;
	unsigned long  input_blocks;
	unsigned long  output_blocks;
	unsigned long  messages_sent;
	unsigned long  messages_received;
	unsigned long  signals_received;
	unsigned long  vol_context_switch;
	unsigned long  invol_context_switch;
	unsigned long  system_calls;
	unsigned long  chars_read_written;
} GEN_RUSAGE;

	MEMBERS		:	The members of this structure are populated by the function
						``GEN_GetRUsage`` depending upon the run-time operating
						system.

						The table below shows the mappings between the members of
						the ''GEN_RUSAGE'' structure, the BSD ''struct rusage''
						structure, and the System V ''struct prusage'' structure.

						You will note that all mappings are not available from all
						operating systems.

{|@|}	GENFUNCS                  SunOS/BSD               Solaris/SysV
	GEN_RUSAGE                struct rusage           struct prusage
	--------------------      ------------------      -------------------
	user_cpu_time        ---> rusage.ru_utime    ---> prusage.pr_utime
	system_cpu_time      ---> rusage.ru_stime    ---> prusage.pr_stime
	trap_cpu_time        --->                    ---> prusage.pr_ttime
	text_pagef_time      --->                    ---> prusage.pr_tftime
	data_pagef_time      --->                    ---> prusage.pr_dftime
	kernel_pagef_time    --->                    ---> prusage.pr_kftime
	user_lock_time       --->                    ---> prusage.pr_ltime
	other_sleep_time     --->                    ---> prusage.pr_slptime
	wait_cpu_time        --->                    ---> prusage.pr_wtime
	stopped_time         --->                    ---> prusage.pr_stoptime
	minor_pagef          ---> rusage.ru_minflt   ---> prusage.pr_minf
	major_pagef          ---> rusage.ru_majflt   ---> prusage.pr_majf
	process_swaps        ---> rusage.ru_nswap    ---> prusage.pr_nswap
	input_blocks         ---> rusage.ru_inblock  ---> prusage.pr_inblk
	output_blocks        ---> rusage.ru_oublock  ---> prusage.pr_oublk
	messages_sent        ---> rusage.ru_msgsnd   ---> prusage.pr_msnd
	messages_received    ---> rusage.ru_msgrcv   ---> prusage.pr_mrcv
	signals_received     ---> rusage.ru_nsignals ---> prusage.pr_sigs
	vol_context_switch   ---> rusage.ru_nvcsw    ---> prusage.pr_vctx
	invol_context_switch ---> rusage.ru_nivcsw   ---> prusage.pr_ictx
	system_calls         --->                    ---> prusage.sysc
	chars_read_written   --->                    ---> prusage.ioch
	--------------------      ------------------      -------------------

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2018 Michael L. Brock

	OUTPUT INDEX:	GEN_RUSAGE
						Usage Description Structures:GEN_RUSAGE
						GENFUNCS:Structures:GEN_RUSAGE
						GENFUNCS:Usage Description Structures:GEN_RUSAGE
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_RUSAGE

	PUBLISH NAME:	GEN_RUSAGE

	ENTRY CLASS	:	Structures and Data Types

EOH */
/*	***********************************************************************	*/
typedef struct {
	struct timeval user_cpu_time;
	struct timeval system_cpu_time;
	struct timeval trap_cpu_time;
	struct timeval text_pagef_time;
	struct timeval data_pagef_time;
	struct timeval kernel_pagef_time;
	struct timeval user_lock_time;
	struct timeval other_sleep_time;
	struct timeval wait_cpu_time;
	struct timeval stopped_time;
	unsigned long  minor_pagef;
	unsigned long  major_pagef;
	unsigned long  process_swaps;
	unsigned long  input_blocks;
	unsigned long  output_blocks;
	unsigned long  messages_sent;
	unsigned long  messages_received;
	unsigned long  signals_received;
	unsigned long  vol_context_switch;
	unsigned long  invol_context_switch;
	unsigned long  system_calls;
	unsigned long  chars_read_written;
} GEN_RUSAGE;
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
typedef struct {
	unsigned char octet[6];
} GEN_ADDR_MAC;
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Function prototypes for functions defined within 'genfuncs.a' . . .	*/
/* *********************************************************************** */

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Function prototypes for version functions . . .						*/
	/*	*****************************************************************	*/
COMPAT_FN_DECL(void  GENFUNCS_GetVersionNumber, (unsigned int *major,
	unsigned int *minor, unsigned int *release, unsigned int *build));
COMPAT_FN_DECL(char *GENFUNCS_GetVersionString, (char *version_string));
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Allocation message functions . . .										*/
	/*	*****************************************************************	*/
#ifdef __GNUC__
COMPAT_FN_DECL(char *GEN_AllocMsgItem, (unsigned int size, char *buffer,
   const char *in_format, ...) __attribute__ ((format (printf, 3, 4))));
COMPAT_FN_DECL(char *GEN_AllocMsgList, (unsigned int element_count,
   unsigned int element_size, char *buffer, const char *in_format, ...)
   __attribute__ ((format (printf, 4, 5))));
COMPAT_FN_DECL(char *GEN_AllocMsgPtrList, (unsigned int element_count,
   unsigned int total_size, char *buffer, const char *in_format, ...)
   __attribute__ ((format (printf, 4, 5))));
#else
# ifndef NO_STDARGS
COMPAT_FN_DECL(char *GEN_AllocMsgItem, (unsigned int size, char *buffer,
	const char *in_format, ...));
COMPAT_FN_DECL(char *GEN_AllocMsgList, (unsigned int element_count,
	unsigned int element_size, char *buffer, const char *in_format, ...));
COMPAT_FN_DECL(char *GEN_AllocMsgPtrList, (unsigned int element_count,
	unsigned int total_size, char *buffer, const char *in_format, ...));
# else
COMPAT_FN_DECL(char *GEN_AllocMsgItem, (unsigned int size, char *buffer,
	const char *in_format, va_alist));
COMPAT_FN_DECL(char *GEN_AllocMsgList, (unsigned int element_count,
	unsigned int element_size, char *buffer, const char *in_format, va_list));
COMPAT_FN_DECL(char *GEN_AllocMsgPtrList,
	(unsigned int element_count, unsigned int total_size, char *buffer,
	const char *in_format, va_list));
# endif /* # ifndef NO_STDARGS */
#endif /* #ifdef __GNUC__ */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		GENFUNCS statisitics gathering functions . . .						*/
	/*	*****************************************************************	*/
COMPAT_FN_DECL(GEN_TVAL_STAT  *GEN_TVAL_STAT_Init, (GEN_TVAL_STAT *stat_ptr));
COMPAT_FN_DECL(GEN_TVAL_STAT  *GEN_TVAL_STAT_StartTime,
	(GEN_TVAL_STAT *stat_ptr));
COMPAT_FN_DECL(GEN_TVAL_STAT  *GEN_TVAL_STAT_EndTime,
	(GEN_TVAL_STAT *stat_ptr, unsigned long item_count));
COMPAT_FN_DECL(GEN_TVAL_STAT  *GEN_TVAL_STAT_EndTimeSpecified,
	(GEN_TVAL_STAT *stat_ptr, unsigned long item_count,
	const struct timeval *last_end));
COMPAT_FN_DECL(struct timeval *GEN_TVAL_STAT_GetLastAverage,
	(const GEN_TVAL_STAT *stat_ptr, struct timeval *average_interval));
COMPAT_FN_DECL(struct timeval *GEN_TVAL_STAT_GetTotalAverage,
	(const GEN_TVAL_STAT *stat_ptr, struct timeval *average_interval));
COMPAT_FN_DECL(struct timeval *GEN_TVAL_STAT_GetSampleAverage,
	(const GEN_TVAL_STAT *stat_ptr, struct timeval *average_interval));
	/*	*****************************************************************	*/

# ifndef NO_STDARGS
COMPAT_FN_DECL(int GEN_ArgParse, (const char *in_param_ptr,
	unsigned int *out_param_length, char **out_data_ptr, ...));
COMPAT_FN_DECL(int GEN_ArgParseTruth, (const char *in_param_ptr,
	int *error_flag, int *truth_flag, char *error_text,
	unsigned int *out_param_length, char **out_data_ptr, ...));
# else
COMPAT_FN_DECL(int GEN_ArgParse, (const char *in_param_ptr,
	unsigned int *out_param_length, char **out_data_ptr, va_alist));
COMPAT_FN_DECL(int GEN_ArgParseTruth, (const char *in_param_ptr,
	int *error_flag, int *truth_flag, char *error_text,
	unsigned int *out_param_length, char **out_data_ptr, va_alist));
# endif /* # ifndef NO_STDARGS */
COMPAT_FN_DECL(int GEN_ArgParseList, (unsigned int parse_count,
	const char **parse_list, const char *in_param_ptr,
	unsigned int *out_param_length, char **out_data_ptr));
COMPAT_FN_DECL(int GEN_ArgParseListTruth, (unsigned int parse_count,
	const char **parse_list, const char *in_param_ptr, int *error_flag,
	int *truth_flag, char *error_text, unsigned int *out_param_length,
	char **out_data_ptr));

COMPAT_FN_DECL(int  GEN_BARG_LogDir, (const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, char **log_dir,
	int *error_code, char *error_text));
COMPAT_FN_DECL(int  GEN_BARG_LogFlag, (const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, int *log_flag,
	int *error_code, char *error_text));
COMPAT_FN_DECL(int  GEN_BARG_LogQuiet, (const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, int *log_quiet_flag,
	int *error_code, char *error_text));
COMPAT_FN_DECL(int  GEN_BARG_CheckOnly, (const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, int *check_only_flag,
	int *error_code, char *error_text));
COMPAT_FN_DECL(int  GEN_BARG_DebugLevel, (const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, int *debug_level,
	int *error_code, char *error_text));
COMPAT_FN_DECL(int  GEN_BARG_DBDebugFlag, (const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, int *db_debug_flag,
	int *error_code, char *error_text));
COMPAT_FN_DECL(int  GEN_BARG_SQLDebugFlag, (const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, int *sql_debug_flag,
	int *error_code, char *error_text));
COMPAT_FN_DECL(int  GEN_BARG_BasicParamAlloc, (const char *in_arg_ptr,
	unsigned int arg_length, const char *data_ptr, char **alloc_ptr,
	char *error_text));
COMPAT_FN_DECL(int  GEN_BARG_BasicPathExpand, (const char *in_arg_ptr,
	unsigned int arg_length, const char *data_ptr, char **alloc_ptr,
	char *error_text));
COMPAT_FN_DECL(void GEN_BARG_BadComponentMsg, (const char *in_arg_ptr,
	unsigned int arg_length, const char *data_ptr, const char *expected_string,
	char *error_text));

COMPAT_FN_DECL(int GEN_BUSE_Help, (const char *base_arg_ptr,
	int optional_flag, char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));
COMPAT_FN_DECL(int GEN_BUSE_LogDir, (const char *base_arg_ptr,
	int optional_flag, char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));
COMPAT_FN_DECL(int GEN_BUSE_LogFlag, (const char *base_arg_ptr,
	int optional_flag, char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));
COMPAT_FN_DECL(int GEN_BUSE_LogQuiet, (const char *base_arg_ptr,
	int optional_flag, char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));
COMPAT_FN_DECL(int GEN_BUSE_CheckOnly, (const char *base_arg_ptr,
	int optional_flag, char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));
COMPAT_FN_DECL(int GEN_BUSE_Version, (const char *base_arg_ptr,
	int optional_flag, char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));
COMPAT_FN_DECL(int GEN_BUSE_DebugLevel, (const char *base_arg_ptr,
	int optional_flag, char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));
COMPAT_FN_DECL(int GEN_BUSE_DBDebugFlag, (const char *base_arg_ptr,
	int optional_flag, char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));
COMPAT_FN_DECL(int GEN_BUSE_SQLDebugFlag, (const char *base_arg_ptr,
	int optional_flag, char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));
COMPAT_FN_DECL(int GEN_BUSE_AppendBooleanText, (unsigned int *usage_count,
	char ***usage_list, int default_value, char *error_text));
COMPAT_FN_DECL(int GEN_BUSE_AppendParamText, (unsigned int *usage_count,
	char ***usage_list, char *error_text));
COMPAT_FN_DECL(int GEN_BUSE_AppendLineList, (char **in_usage_list,
	unsigned int *usage_count, char ***usage_list, char *error_text));
COMPAT_FN_DECL(int GEN_BUSE_AppendLine, (const char *in_line,
	unsigned int *usage_count, char ***usage_list, char *error_text));
COMPAT_FN_DECL(int GEN_BUSE_AppendNL, (unsigned int *usage_count,
	char ***usage_list, char *error_text));
COMPAT_FN_DECL(int GEN_BUSE_AppendNULL, (unsigned int *usage_count,
	char ***usage_list, char *error_text));
COMPAT_FN_DECL(int GEN_BUSE_BasicConstruct, (const char *base_arg_ptr,
	const char *arg_ptr, int optional_flag, char **arg_usage_list,
	char **extra_usage_list, unsigned int *usage_count, char ***usage_list,
	char *error_text));
COMPAT_FN_DECL(int GEN_BUSE_CreateUsageList, (unsigned int param_count,
	const GEN_USAGE_PARAM *param_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));

COMPAT_FN_DECL(char *GEN_GetBooleanString, (int boolean_value,
	char *boolean_string));
COMPAT_FN_DECL(char *GEN_GetDebugLevel, (int debug_level,
	char *debug_level_string));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Thread-safe time conversion function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(struct tm       *GEN_GetTimeLocal,
	(const time_t *in_time, struct tm *time_buffer));
COMPAT_FN_DECL(struct tm       *GEN_GetTimeGMT,
	(const time_t *in_time, struct tm *time_buffer));
COMPAT_FN_DECL(int              GEN_gettimeofday,
	(struct timeval *timeval_ptr, struct timezone *timezone_ptr));
COMPAT_FN_DECL(struct timeval  *GEN_GetTimeUSecs,
	(struct timeval *timeval_ptr));
COMPAT_FN_DECL(struct timespec *GEN_GetTimeNSecs,
	(struct timespec *timespec_ptr));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Time interval function prototypes for 'struct timeval' . . .
		*****************************************************************	*/
COMPAT_FN_DECL(struct timeval *GEN_GetInterval_timeval,
	(const struct timeval *start_ptr, const struct timeval *end_ptr,
	struct timeval *out_interval_ptr));
COMPAT_FN_DECL(struct timeval *GEN_GetABSInterval_timeval,
	(const struct timeval *start_ptr, const struct timeval *end_ptr,
	struct timeval *out_interval_ptr));
COMPAT_FN_DECL(struct timeval *GEN_GetPerInterval_timeval,
	(const struct timeval *in_interval_ptr, unsigned long item_count,
	struct timeval *out_interval_ptr));
COMPAT_FN_DECL(struct timeval *GEN_AddInterval_timeval,
	(const struct timeval *time_ptr_1, const struct timeval *time_ptr_2,
	struct timeval *out_interval_ptr));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Time interval function prototypes for 'struct timespec' . . .
		*****************************************************************	*/
COMPAT_FN_DECL(struct timespec *GEN_GetInterval_timespec,
	(const struct timespec *start_ptr, const struct timespec *end_ptr,
	struct timespec *out_interval_ptr));
COMPAT_FN_DECL(struct timespec *GEN_GetABSInterval_timespec,
	(const struct timespec *start_ptr, const struct timespec *end_ptr,
	struct timespec *out_interval_ptr));
COMPAT_FN_DECL(struct timespec *GEN_GetPerInterval_timespec,
	(const struct timespec *in_interval_ptr, unsigned long item_count,
	struct timespec *out_interval_ptr));
COMPAT_FN_DECL(struct timespec *GEN_AddInterval_timespec,
	(const struct timespec *time_ptr_1, const struct timespec *time_ptr_2,
	struct timespec *out_interval_ptr));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Time formatting function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(char *GEN_Format_time_t, (const time_t *in_time, char *buffer));
COMPAT_FN_DECL(char *GEN_Format_time_t_GMT, (const time_t *in_time,
	char *buffer));
COMPAT_FN_DECL(char *GEN_Format_tm, (const struct tm *in_time, char *buffer));
COMPAT_FN_DECL(char *GEN_Format_tm_GMT, (const struct tm *in_time,
	char *buffer));
COMPAT_FN_DECL(char *GEN_Format_timeval, (const struct timeval *in_time,
	char *buffer));
COMPAT_FN_DECL(char *GEN_Format_timeval_GMT, (const struct timeval *in_time,
	char *buffer));
COMPAT_FN_DECL(char *GEN_Format_timespec, (const struct timespec *in_time,
	char *buffer));
COMPAT_FN_DECL(char *GEN_Format_timespec_GMT, (const struct timespec *in_time,
	char *buffer));
COMPAT_FN_DECL(char *GEN_Format_ulong_time, (const unsigned long *in_time,
	char *buffer));
COMPAT_FN_DECL(char *GEN_Format_ulong_time_GMT, (const unsigned long *in_time,
	char *buffer));
COMPAT_FN_DECL(char *GEN_FormatInterval_time_t, (const time_t *in_time,
	char *buffer));
COMPAT_FN_DECL(char *GEN_FormatInterval_timeval,
	(const struct timeval *in_time, char *buffer));
COMPAT_FN_DECL(char *GEN_FormatInterval_timespec,
	(const struct timespec *in_time, char *buffer));
COMPAT_FN_DECL(int   GEN_Compare_timeval,
	(const struct timeval *timeval_ptr_1,
	const struct timeval *timeval_ptr_2));
COMPAT_FN_DECL(int   GEN_Compare_timespec,
	(const struct timespec *timespec_ptr_1,
	const struct timespec *timespec_ptr_2));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Host name expansion functions . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int GEN_ExpandHostNameList, (unsigned int in_host_count,
	char **in_host_list, unsigned int *out_host_count, char ***out_host_list,
	char *error_text));
COMPAT_FN_DECL(int GEN_ExpandHostNameString, (const char *in_host_string,
	unsigned int *out_host_count, char ***out_host_list, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
			Function to get fully-qualified path names . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int GEN_ExpandToFullPathName, (const char *in_path_name,
	char **out_path_name, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
			Functions to get the current directory name . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int   GEN_DetermineCurrentDir,
	(char *current_dir, char *error_text));
COMPAT_FN_DECL(char *GEN_GetCurrentDirBasic,
	(char *current_dir));
COMPAT_FN_DECL(char *GEN_GetCurrentDir,
	(char *current_dir, unsigned int current_dir_length));
	/*	*****************************************************************	*/

	/* *****************************************************************
		*****************************************************************
		Generic memory touch function prototypes . . .
		***************************************************************** */
COMPAT_FN_DECL(int GEN_TouchErrorText, (char *error_text));
COMPAT_FN_DECL(int GEN_ClearErrorText, (char *error_text));
COMPAT_FN_DECL(int GEN_TouchErrorTextBasic, (char *error_text,
	unsigned int error_text_length));
COMPAT_FN_DECL(int GEN_ClearErrorTextBasic, (char *error_text,
	unsigned int error_text_length));
COMPAT_FN_DECL(int GEN_TouchRead, (const void *data_ptr,
	unsigned int data_length, const char *data_name, char *error_text));
COMPAT_FN_DECL(int GEN_TouchWrite, (void *data_ptr,
	unsigned int data_length, const char *data_name, char *error_text));
COMPAT_FN_DECL(int GEN_TouchClear, (void *data_ptr,
	unsigned int data_length, const char *data_name, char *error_text));
COMPAT_FN_DECL(int GEN_TouchReadString, (const char *string_ptr,
	unsigned int string_length, const char *string_name, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Error reporting for errno-based errors function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void                  GEN_GetErrorList,
	(unsigned int *out_count, const GEN_ERROR_SPEC **out_list));
COMPAT_FN_DECL(const GEN_ERROR_SPEC *GEN_GetErrorPtr, (int errno_code));
COMPAT_FN_DECL(const GEN_ERROR_SPEC *GEN_GetLastErrorPtr, (void));
COMPAT_FN_DECL(char                 *GEN_AppendErrorString, (int errno_code,
	int long_flag, unsigned int max_text, char *error_text));
COMPAT_FN_DECL(char                 *GEN_AppendLastErrorString, (int long_flag,
	unsigned int max_text, char *error_text));
COMPAT_FN_DECL(char                 *GEN_GetErrorString, (int errno_code,
	int long_flag, unsigned int max_text, char *error_text));
COMPAT_FN_DECL(char                 *GEN_GetLastErrorString, (int long_flag,
	unsigned int max_text, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Error reporting for Win32 function prototypes . . .
		*****************************************************************	*/
#ifdef _Windows
COMPAT_FN_DECL(void                  GEN_GetErrorList_Win32,
	(unsigned int *out_count, const GEN_ERROR_SPEC **out_list));
COMPAT_FN_DECL(const GEN_ERROR_SPEC *GEN_GetErrorPtr_Win32,
	(int win32_code));
COMPAT_FN_DECL(const GEN_ERROR_SPEC *GEN_GetLastErrorPtr_Win32,
	(void));
COMPAT_FN_DECL(char                 *GEN_AppendErrorString_Win32,
	(int win32_code, int long_flag, unsigned int max_text, char *error_text));
COMPAT_FN_DECL(char                 *GEN_AppendLastErrorString_Win32,
	(int long_flag, unsigned int max_text, char *error_text));
COMPAT_FN_DECL(char                 *GEN_GetErrorString_Win32,
	(int win32_code, int long_flag, unsigned int max_text, char *error_text));
COMPAT_FN_DECL(char                 *GEN_GetLastErrorString_Win32,
	(int long_flag, unsigned int max_text, char *error_text));
#endif /* #ifdef _Windows */
	/*	*****************************************************************	*/

# ifdef __MSDOS__
COMPAT_FN_DECL(char *GEN_GetSignalText,
	(int signal_number, char *signal_text));
# elif _Windows
COMPAT_FN_DECL(char *GEN_GetSignalText,
	(int signal_number, char *signal_text));
# elif _MSC_VER
COMPAT_FN_DECL(char *GEN_GetSignalText,
	(int signal_number, char *signal_text));
# else
#  ifdef __SVR4
COMPAT_FN_DECL(char *GEN_GetSignalText,
	(int signal_number, siginfo_t *siginfo_ptr, void *signal_address,
	char *signal_text));
#  else
COMPAT_FN_DECL(char *GEN_GetSignalText,
	(int signal_number, int signal_code, const void *signal_address,
	char *signal_text));
#  endif /* #ifndef __SVR4 */
# endif /* #ifndef __MSDOS__ */

COMPAT_FN_DECL(void GEN_SIGNAL_SignalInit, (int *signal_received_flag_ptr,
	int *queue_signal_flag_ptr, void *user_data_ptr, void *output_control_ptr,
	int (*output_function)(const void *, size_t, size_t, void *),
	void (*user_cleanup_function)(void *, int, int *, const char *)));
COMPAT_FN_DECL(void GEN_SIGNAL_SignalDefault, (void));
COMPAT_FN_DECL(void GEN_SIGNAL_SignalIgnore, (void));
COMPAT_FN_DECL(void GEN_SIGNAL_SignalSet, (void));
# ifdef __MSDOS__
COMPAT_FN_DECL(void GEN_SIGNAL_SignalHandler, (int signal_number));
# elif _Windows
COMPAT_FN_DECL(void GEN_SIGNAL_SignalHandler, (int signal_number));
# elif _MSC_VER
COMPAT_FN_DECL(void GEN_SIGNAL_SignalHandler, (int signal_number));
# else
#  ifdef __SVR4
COMPAT_FN_DECL(void GEN_SIGNAL_SignalHandler, (int signal_number,
	siginfo_t *siginfo_ptr, void *signal_address));
#  else
COMPAT_FN_DECL(void GEN_SIGNAL_SignalHandler, (int signal_number,
	int signal_code, struct sigcontext *signal_context, char *signal_address));
# endif /* #ifndef __SVR4 */
# endif /* ifdef __MSDOS__ */

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Memory validiation functions . . .										*/
	/*	*****************************************************************	*/
COMPAT_FN_DECL(int GEN_VPTR_IsValidArea, (void *area_pointer,
	unsigned int area_length, int access_mode, void **failure_ptr));
COMPAT_FN_DECL(int GEN_VPTR_IsValidBoundary, (void *area_pointer,
	unsigned int area_length, int access_mode, void **failure_ptr));
COMPAT_FN_DECL(int GEN_VPTR_IsValidPointer, (void *area_pointer,
	int access_mode, void **failure_ptr));
COMPAT_FN_DECL(int GEN_VPTR_IsValidSections, (void *area_pointer,
	unsigned int area_length, unsigned int section_size, int access_mode,
	void **failure_ptr));
COMPAT_FN_DECL(int GEN_VPTR_IsValidString, (char *string_pointer,
	int access_mode, void **failure_ptr));
	/*	*****************************************************************	*/

/*
	CODE NOTE: Are these obsolete?
*/
COMPAT_FN_DECL(int GEN_IsValidAreaBasic, (void *area_pointer,
	unsigned int area_length, int access_mode, void **failure_ptr));
COMPAT_FN_DECL(int GEN_IsValidBoundaryBasic, (void *area_pointer,
	unsigned int area_length, int access_mode, void **failure_ptr));
COMPAT_FN_DECL(int GEN_IsValidPointerBasic, (void *area_pointer,
	int access_mode, void **failure_ptr));
COMPAT_FN_DECL(int GEN_IsValidSectionsBasic, (void *area_pointer,
	unsigned int area_length, unsigned int section_size, int access_mode,
	void **failure_ptr));
COMPAT_FN_DECL(int GEN_IsValidStringBasic, (char *string_pointer,
	int access_mode, void **failure_ptr));

COMPAT_FN_DECL(void         GEN_GetMemoryAccessColor, (void *area_pointer,
	unsigned int area_length, int access_mode, unsigned char *bit_string));
COMPAT_FN_DECL(void         GEN_GetMemoryModeColor, (void *area_pointer,
	unsigned int area_length, unsigned char *bit_string));
COMPAT_FN_DECL(unsigned int GEN_GetMemoryAccessColorLength,
	(unsigned int area_length));
COMPAT_FN_DECL(unsigned int GEN_GetMemoryModeColorLength,
	(unsigned int area_length));

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Functions to manage interaction with the operating system page	*/
	/*	mapping facilities.																*/
	/*	*****************************************************************	*/
COMPAT_FN_DECL(int GEN_PMAP_GetPMapList, (int selector,
	unsigned int *pmap_count, GEN_PMAP_DESC **pmap_list, char *error_text));
COMPAT_FN_DECL(int GEN_PMAP_LocateByAddress, (int selector,
	const void *address, int *pmap_flag, GEN_PMAP_DESC *pmap_ptr,
	char *error_text));
	/*	*****************************************************************	*/

COMPAT_FN_DECL(int   expandir, (char *path_name, char *return_path_name));

COMPAT_FN_DECL(void GEN_EmitBufferData,
	(STR_FUNC_TYPE_fprintf output_function, void *output_control,
	const char *left_prefix, unsigned int left_padding, unsigned int max_length,
	int print_chars_flag, unsigned int in_radix, unsigned int data_length,
	const void *data_ptr));

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/*		Function prototypes for the 'GEN_MEMBER' functions . . .					*/
/* *********************************************************************** */

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		GEN_MEMBER generic handling function prototypes . . .				*/
	/*	*****************************************************************	*/
COMPAT_FN_DECL(int  GEN_APPD_Member, (const GEN_MEMBER *in_ptr,
	unsigned int *out_count, GEN_MEMBER **out_list, char *error_text));
COMPAT_FN_DECL(int  GEN_COPY_Member, (const GEN_MEMBER *in_ptr,
	GEN_MEMBER *out_ptr, char *error_text));
COMPAT_FN_DECL(int  GEN_COPY_MemberList, (unsigned int in_count,
	const GEN_MEMBER *in_list, unsigned int *out_count, GEN_MEMBER **out_list,
	char *error_text));
COMPAT_FN_DECL(void GEN_FREE_Member, (GEN_MEMBER *member_ptr));
COMPAT_FN_DECL(void GEN_FREE_MemberList, (unsigned int *member_count,
	GEN_MEMBER **member_list));
COMPAT_FN_DECL(void GEN_INIT_Member, (GEN_MEMBER *member_ptr));
COMPAT_FN_DECL(void GEN_INIT_MemberList, (unsigned int member_count,
	GEN_MEMBER *member_list));
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		GEN_MEMBER emit function prototypes . . .								*/
	/*	*****************************************************************	*/
COMPAT_FN_DECL(void GEN_EMIT_MemberList, (unsigned int member_count,
	const GEN_MEMBER *member_list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(void GEN_EMIT_MemberListIdx, (unsigned int member_count,
	const GEN_MEMBER *member_list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(void GEN_EMIT_Member, (const GEN_MEMBER *ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void GEN_EMIT_MemberHeader, (
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void GEN_EMIT_MemberTrailer, (
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		GEN_MEMBER manipulation function prototypes . . .					*/
	/*	*****************************************************************	*/
COMPAT_FN_DECL(int GEN_MEMBER_GetSpecMemberList, (unsigned int spec_count,
	char **spec_list, unsigned int in_member_count,
	const GEN_MEMBER *in_member_list, unsigned int *out_member_count,
	GEN_MEMBER **out_member_list, char *error_text));
COMPAT_FN_DECL(int GEN_MEMBER_GetSpecMemberString, (const char *spec_string,
	unsigned int in_member_count, const GEN_MEMBER *in_member_list,
	unsigned int *out_member_count, GEN_MEMBER **out_member_list,
	char *error_text));
COMPAT_FN_DECL(int GEN_MEMBER_SetDisplayName, (GEN_MEMBER *member_ptr,
	const char *display_name, char *error_text));
COMPAT_FN_DECL(int GEN_MEMBER_CreateDisplayNameList,
	(unsigned int member_count, GEN_MEMBER *member_list, char *error_text));
COMPAT_FN_DECL(int GEN_MEMBER_CreateDisplayName, (GEN_MEMBER *member_ptr,
	char *error_text));
COMPAT_FN_DECL(int GEN_MEMBER_FixAlignArrayList, (unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, unsigned int member_count,
	GEN_MEMBER *member_list, unsigned int *structure_size, char *error_text));
COMPAT_FN_DECL(int GEN_MEMBER_SetAlignArrayList, (unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, unsigned int member_count,
	GEN_MEMBER *member_list, char *error_text));
COMPAT_FN_DECL(int GEN_MEMBER_SetAlignArray, (unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, GEN_MEMBER *member_ptr, char *error_text));
COMPAT_FN_DECL(int GEN_MEMBER_SetDisplayLengthList, (unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, unsigned int member_count,
	GEN_MEMBER *member_list, int header_flag,
	unsigned int null_string_length, unsigned int intra_field_sep_length,
	void *user_data_ptr, char *error_text));
COMPAT_FN_DECL(int GEN_MEMBER_SetDisplayLength, (unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, GEN_MEMBER *member_ptr, int header_flag,
	unsigned int null_string_length, unsigned int intra_field_sep_length,
	void *user_data_ptr, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		GEN_MEMBER dump function prototypes . . .								*/
	/*	*****************************************************************	*/
COMPAT_FN_DECL(void GEN_MEMBER_DMP_Header, (unsigned int member_count,
	const GEN_MEMBER *member_list, int index_flag, const char *inter_field_sep,
	const char *record_leader, const char *record_trailer,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void GEN_MEMBER_DMP_Trailer, (unsigned int member_count,
	const GEN_MEMBER *member_list, int index_flag, const char *inter_field_sep,
	const char *record_leader, const char *record_trailer,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(int  GEN_MEMBER_DMP_DumpText, (unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, unsigned int member_count,
	const GEN_MEMBER *member_list, unsigned int record_count,
	const void *record_list, unsigned int record_size, int index_flag,
	int reverse_flag, int header_flag, unsigned int max_records,
	unsigned int lines_per_page, const char *null_string,
	const char *inter_field_sep, const char *intra_field_sep,
	const char *overflow_char, const char *page_sep, const char *record_leader,
	const char *record_trailer, const char *member_spec_string,
	unsigned int *page_count, unsigned int *format_line_count,
	unsigned int *data_line_count, void *user_data_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text));
COMPAT_FN_DECL(int  GEN_MEMBER_DMP_DumpTextIndirect, (unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, unsigned int member_count,
	const GEN_MEMBER *member_list, unsigned int record_count,
	void **record_list, unsigned int record_size, int index_flag,
	int reverse_flag, int header_flag, unsigned int max_records,
	unsigned int lines_per_page, const char *null_string,
	const char *inter_field_sep, const char *intra_field_sep,
	const char *overflow_char, const char *page_sep, const char *record_leader,
	const char *record_trailer, const char *member_spec_string,
	unsigned int *page_count, unsigned int *format_line_count,
	unsigned int *data_line_count, void *user_data_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text));
COMPAT_FN_DECL(void GEN_MEMBER_DMP_DumpTextBasic, (unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, unsigned int member_count,
	const GEN_MEMBER *member_list, int record_ptr_flag,unsigned int record_count,
	const void *record_list, unsigned int record_size, int index_flag,
	int reverse_flag, int header_flag, unsigned int max_records,
	unsigned int lines_per_page, const char *null_string,
	const char *inter_field_sep, const char *intra_field_sep,
	const char *overflow_char, const char *page_sep, const char *record_leader,
	const char *record_trailer, unsigned int *page_count,
	unsigned int *format_line_count, unsigned int *data_line_count,
	void *user_data_ptr, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(void GEN_MEMBER_DMP_DumpRecord, (unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, unsigned int member_count,
	const GEN_MEMBER *member_list, const void *record_ptr,
	const char *null_string, const char *inter_field_sep,
	const char *intra_field_sep, const char *overflow_char,
	void *user_data_ptr, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(void GEN_MEMBER_DMP_DumpField, (unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, const GEN_MEMBER *member_ptr,
	const void *record_ptr, int null_flag, const char *null_string,
	const char *intra_field_sep, const char *overflow_char,
	void *user_data_ptr, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
	/*	*****************************************************************	*/

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Function prototypes for the GENFUNCS alignment functions . . .			*/
/* *********************************************************************** */

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Architecture-independent alignment function prototypes . . .	*/
	/*	*****************************************************************	*/
COMPAT_FN_DECL(int                   GEN_ALIGN_BASIC_AlignStringList,
	(unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, int normalize_flag,
	int adjust_char_flag, const char *separator_list, unsigned int spec_count,
	char **spec_list, unsigned int **count_list, unsigned int **index_list,
	unsigned int **size_list, unsigned int *structure_size,
	unsigned int *align_count, GEN_ALIGN **align_list, char *error_text));
COMPAT_FN_DECL(int                   GEN_ALIGN_BASIC_AlignString,
	(unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, int normalize_flag,
	int adjust_char_flag, const char *separator_list, const char *spec_string,
	unsigned int *structure_size, unsigned int *align_count,
	GEN_ALIGN **align_list, char *error_text));
COMPAT_FN_DECL(int                   GEN_ALIGN_BASIC_CountStringToList,
	(unsigned int type_count, const GEN_ALIGN_SPEC *type_list,
	int normalize_flag, int adjust_char_flag, const char *separator_list,
	unsigned int in_spec_count, const char *in_spec_string,
	unsigned int *structure_size, unsigned int *align_count,
	GEN_ALIGN **align_list, char *error_text));
COMPAT_FN_DECL(int                   GEN_ALIGN_BASIC_CountStringToLApp,
	(unsigned int type_count, const GEN_ALIGN_SPEC *type_list,
	int normalize_flag, int adjust_char_flag, const char *separator_list,
	unsigned int in_spec_count, const char *in_spec_string,
	unsigned int *structure_size, unsigned int *align_count,
	GEN_ALIGN **align_list, char *error_text));
COMPAT_FN_DECL(int                   GEN_ALIGN_BASIC_CountStringToString,
	(unsigned int type_count, const GEN_ALIGN_SPEC *type_list,
	int normalize_flag, int adjust_char_flag, const char *separator_list,
	unsigned int in_spec_count, const char *in_spec_string,
	char **out_spec_string, char *error_text));
COMPAT_FN_DECL(int                   GEN_ALIGN_BASIC_AlignList,
	(unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, unsigned int *structure_size,
	unsigned int align_count, GEN_ALIGN *align_list, char *error_text));
COMPAT_FN_DECL(int                   GEN_ALIGN_BASIC_CheckStringList,
	(unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, const char *separator_list,
	unsigned int spec_count, char **spec_list, char *error_text));
COMPAT_FN_DECL(int                   GEN_ALIGN_BASIC_CheckString,
	(unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, const char *separator_list,
	const char *spec_string, char *error_text));
COMPAT_FN_DECL(int                   GEN_ALIGN_BASIC_CheckMember,
	(unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, const char *spec_string,
	GEN_ALIGN *align_ptr, char *error_text));
COMPAT_FN_DECL(int                   GEN_ALIGN_BASIC_ListToStringAlloc,
	(unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, unsigned int align_count,
	const GEN_ALIGN *align_list, const char *separator_char,
	char **spec_string, char *error_text));
COMPAT_FN_DECL(int                   GEN_ALIGN_BASIC_ListToString,
	(unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, unsigned int align_count,
	const GEN_ALIGN *align_list, const char *separator_char, char *spec_string,
	char *error_text));
COMPAT_FN_DECL(int                   GEN_ALIGN_BASIC_CopyTypeList,
	(unsigned int in_type_count,
	const GEN_ALIGN_SPEC *in_type_list, unsigned int *out_type_count,
	GEN_ALIGN_SPEC **out_type_list,  char *error_text));
COMPAT_FN_DECL(int                   GEN_ALIGN_BASIC_FindTypeCharIndex,
	(unsigned int type_count, const GEN_ALIGN_SPEC *type_list, int type_char,
	unsigned int *type_index));
COMPAT_FN_DECL(const GEN_ALIGN_SPEC *GEN_ALIGN_BASIC_FindTypeCharPtr,
	(unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, int type_char, unsigned int *type_index));
COMPAT_FN_DECL(const GEN_ALIGN_SPEC *GEN_ALIGN_BASIC_GetTypePtr,
	(unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, unsigned int type_index));
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Default architecture alignment function prototypes . . .			*/
	/*	*****************************************************************	*/
COMPAT_FN_DECL(int                   GEN_ALIGN_AlignStringList,
	(int normalize_flag,
	int adjust_char_flag, const char *separator_list, unsigned int spec_count,
	char **spec_list, unsigned int **count_list, unsigned int **index_list,
	unsigned int **size_list, unsigned int *structure_size,
	unsigned int *align_count, GEN_ALIGN **align_list, char *error_text));
COMPAT_FN_DECL(int                   GEN_ALIGN_AlignString,
	(int normalize_flag,
	int adjust_char_flag, const char *separator_list, const char *spec_string,
	unsigned int *structure_size, unsigned int *align_count,
	GEN_ALIGN **align_list, char *error_text));
COMPAT_FN_DECL(int                   GEN_ALIGN_CountStringToList,
	(int normalize_flag,
	int adjust_char_flag, const char *separator_list,
	unsigned int in_spec_count, const char *in_spec_string,
	unsigned int *structure_size, unsigned int *align_count,
	GEN_ALIGN **align_list, char *error_text));
COMPAT_FN_DECL(int                   GEN_ALIGN_CountStringToLApp,
	(int normalize_flag,
	int adjust_char_flag, const char *separator_list,
	unsigned int in_spec_count, const char *in_spec_string,
	unsigned int *structure_size, unsigned int *align_count,
	GEN_ALIGN **align_list, char *error_text));
COMPAT_FN_DECL(int                   GEN_ALIGN_CountStringToString,
	(int normalize_flag,
	int adjust_char_flag, const char *separator_list,
	unsigned int in_spec_count, const char *in_spec_string,
	char **out_spec_string, char *error_text));
COMPAT_FN_DECL(int                   GEN_ALIGN_AlignList,
	(unsigned int *structure_size,
	unsigned int align_count, GEN_ALIGN *align_list, char *error_text));
COMPAT_FN_DECL(int                   GEN_ALIGN_CheckStringList,
	(const char *separator_list,
	unsigned int spec_count, char **spec_list, char *error_text));
COMPAT_FN_DECL(int                   GEN_ALIGN_CheckString,
	(const char *separator_list,
	const char *spec_string, char *error_text));
COMPAT_FN_DECL(int                   GEN_ALIGN_CheckMember,
	(const char *spec_string,
	GEN_ALIGN *align_ptr, char *error_text));
COMPAT_FN_DECL(int                   GEN_ALIGN_ListToStringAlloc,
	(unsigned int align_count,
	const GEN_ALIGN *align_list, const char *separator_char,
	char **spec_string, char *error_text));
COMPAT_FN_DECL(int                   GEN_ALIGN_ListToString,
	(unsigned int align_count,
	const GEN_ALIGN *align_list, const char *separator_char, char *spec_string,
	char *error_text));
COMPAT_FN_DECL(int                   GEN_ALIGN_CopyTypeList,
	(unsigned int *out_type_count,
	GEN_ALIGN_SPEC **out_type_list,  char *error_text));
COMPAT_FN_DECL(int                   GEN_ALIGN_FindTypeCharIndex,
	(int type_char,
	unsigned int *type_index));
COMPAT_FN_DECL(const GEN_ALIGN_SPEC *GEN_ALIGN_FindTypeCharPtr,
	(int type_char,
	unsigned int *type_index));
COMPAT_FN_DECL(const GEN_ALIGN_SPEC *GEN_ALIGN_GetTypePtr,
	(unsigned int type_index));
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Support alignment function prototypes . . .							*/
	/*	*****************************************************************	*/
COMPAT_FN_DECL(void         GEN_ALIGN_NormalizeList,
	(unsigned int *align_count, GEN_ALIGN **align_list));
COMPAT_FN_DECL(unsigned int GEN_ALIGN_CalcListToStringLen,
	(unsigned int align_count, const GEN_ALIGN *align_list));
COMPAT_FN_DECL(void         GEN_ALIGN_InitAlign, (GEN_ALIGN *align_ptr));
COMPAT_FN_DECL(int          GEN_ALIGN_CompareList,
	(GEN_ALIGN_CMP *align_cmp_ptr, const void *data_ptr_1,
	const void *data_ptr_2, size_t data_length));
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Alignment data comparison function prototypes . . .				*/
	/*	*****************************************************************	*/
COMPAT_FN_DECL(int GEN_SCMP_ubyte, (GEN_ALIGN *align_ptr,
	const unsigned char *ptr_1, const unsigned char *ptr_2,
	size_t data_length));
COMPAT_FN_DECL(int GEN_SCMP_char, (GEN_ALIGN *align_ptr, const char *ptr_1,
	const char *ptr_2, size_t data_length));
COMPAT_FN_DECL(int GEN_SCMP_uchar, (GEN_ALIGN *align_ptr,
	const unsigned char *ptr_1, const unsigned char *ptr_2,
	size_t data_length));
COMPAT_FN_DECL(int GEN_SCMP_short, (GEN_ALIGN *align_ptr, const short *ptr_1,
	const short *ptr_2, size_t data_length));
COMPAT_FN_DECL(int GEN_SCMP_ushort, (GEN_ALIGN *align_ptr,
	const unsigned short *ptr_1, const unsigned short *ptr_2,
	size_t data_length));
COMPAT_FN_DECL(int GEN_SCMP_int, (GEN_ALIGN *align_ptr, const int *ptr_1,
	const int *ptr_2, size_t data_length));
COMPAT_FN_DECL(int GEN_SCMP_uint, (GEN_ALIGN *align_ptr,
	const unsigned int *ptr_1, const unsigned int *ptr_2, size_t data_length));
COMPAT_FN_DECL(int GEN_SCMP_long, (GEN_ALIGN *align_ptr, const long *ptr_1,
	const long *ptr_2, size_t data_length));
COMPAT_FN_DECL(int GEN_SCMP_ulong, (GEN_ALIGN *align_ptr,
	const unsigned long *ptr_1, const unsigned long *ptr_2,
	size_t data_length));
COMPAT_FN_DECL(int GEN_SCMP_float, (GEN_ALIGN *align_ptr, const float *ptr_1,
	const float *ptr_2, size_t data_length));
COMPAT_FN_DECL(int GEN_SCMP_double, (GEN_ALIGN *align_ptr,
	const double *ptr_1, const double *ptr_2, size_t data_length));
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Old alignment function prototypes . . .								*/
	/*	*****************************************************************	*/
COMPAT_FN_DECL(int GEN_ALIGN_GetFieldAlignList, (unsigned int member_count,
	const char *member_spec, int adjust_char_flag, unsigned int *align_size,
	unsigned int *align_count, GEN_ALIGN **align_list, char *error_text));
COMPAT_FN_DECL(int GEN_ALIGN_AlignFromString, (const char *in_string,
	unsigned int *structure_size, unsigned int *align_count,
	GEN_ALIGN **align_list, char *error_text));
COMPAT_FN_DECL(int GEN_ALIGN_CheckMember, (const char *in_string,
	GEN_ALIGN *align_ptr, char *error_text));
COMPAT_FN_DECL(int GEN_ALIGN_Align, (unsigned int *structure_size,
	unsigned int align_count, GEN_ALIGN *align_list, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		GEN_ALIGN emit function prototypes . . .								*/
	/*	*****************************************************************	*/
COMPAT_FN_DECL(void GEN_EMIT_AlignList, (unsigned int align_count,
	const GEN_ALIGN *align_list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(void GEN_EMIT_AlignListIdx, (unsigned int align_count,
	const GEN_ALIGN *align_list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(void GEN_EMIT_Align, (const GEN_ALIGN *ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void GEN_EMIT_AlignHeader,
	(STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void GEN_EMIT_AlignTrailer,
	(STR_FUNC_TYPE_fprintf output_function, void *output_control));
	/*	*****************************************************************	*/

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* *********************************************************************** */

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Parameter parsing control function prototypes . . .				*/
	/*	*****************************************************************	*/
COMPAT_FN_DECL(int GEN_GetParams, (void *control_ptr, unsigned int argc,
	char **argv, int *help_flag, int *version_flag,
	int (*parse_function)(void *parse_control_ptr, unsigned int parse_argc,
		char **parse_argv, int call_flag, unsigned int current_arg,
		const char *current_arg_ptr, char *parse_error_text), char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Reader-exclusion locking function prototypes . . .					*/
	/*	*****************************************************************	*/
COMPAT_FN_DECL(void GEN_LOCK_READEX_LockInit,
	(volatile GEN_LOCK_READEX *lock_ptr));
COMPAT_FN_DECL(void GEN_LOCK_READEX_StartLock,
	(volatile GEN_LOCK_READEX *lock_ptr));
COMPAT_FN_DECL(void GEN_LOCK_READEX_EndLock,
	(volatile GEN_LOCK_READEX *lock_ptr));
COMPAT_FN_DECL(void GEN_LOCK_READEX_IncrementLock,
	(volatile GEN_LOCK_READEX *lock_ptr));
COMPAT_FN_DECL(int  GEN_LOCK_READEX_TestLock,
	(const volatile GEN_LOCK_READEX *lock_ptr));
COMPAT_FN_DECL(int  GEN_LOCK_READEX_WaitLock,
	(const volatile GEN_LOCK_READEX *in_lock_ptr, unsigned int cycle_count,
	unsigned long cycle_time_out, GEN_LOCK_READEX *out_lock_ptr));
COMPAT_FN_DECL(int  GEN_LOCK_READEX_CheckLock,
	(const volatile GEN_LOCK_READEX *lock_ptr_1,
	const GEN_LOCK_READEX *lock_ptr_2));
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Microsecond sleep function prototype . . .							*/
	/*	*****************************************************************	*/
COMPAT_FN_DECL(void GEN_usleep, (unsigned long microseconds));
COMPAT_FN_DECL(void GEN_nsleep, (unsigned long nanoseconds));
COMPAT_FN_DECL(int  GEN_nanosleep, (const struct timespec *request_ptr,
	struct timespec *remaining_ptr));
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Get OS page size function prototype . . .								*/
	/*	*****************************************************************	*/
COMPAT_FN_DECL(unsigned int GEN_GetAllocGranularity, (void));
COMPAT_FN_DECL(unsigned int GEN_GetPageSize, (void));
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Usage output function prototypes . . .									*/
	/*	*****************************************************************	*/
COMPAT_FN_DECL(void GEN_DoSimpleUsage, (int exit_code,
	const char *program_name, const char *exit_message,
	const char *usage_string));
COMPAT_FN_DECL(void GEN_DoUsage, (int exit_code, const char *program_name,
	const char *exit_message, char **usage_string_list));
COMPAT_FN_DECL(void GEN_DoFormatUsage, (int exit_code,
	const char *program_name, const char *exit_message,
	char **usage_string_list));
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Teknekron grocery formatting function prototypes . . .			*/
	/*	*****************************************************************	*/
COMPAT_FN_DECL(char *GEN_FormatTSSGrocery, (const double *in_double,
	const unsigned char *in_char, char *out_string));
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Resource usage function prototypes . . .								*/
	/*	*****************************************************************	*/
COMPAT_FN_DECL(int GEN_GetRUsage, (int selector, GEN_RUSAGE *rusage_ptr,
	char *error_text));
COMPAT_FN_DECL(int GEN_GetRUsageDelta, (const GEN_RUSAGE *start_rusage_ptr,
	const GEN_RUSAGE *end_rusage_ptr, GEN_RUSAGE *delta_rusage_ptr,
	char *error_text));
COMPAT_FN_DECL(int GEN_FormatRUsageList, (const GEN_RUSAGE *rusage_ptr,
	unsigned int text_width, int null_format_type, unsigned int *rusage_count,
	char ***rusage_list, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Resource limit maximization function prototypes . . .				*/
	/*	*****************************************************************	*/
COMPAT_FN_DECL(int GEN_SetResourceLimitsToMax, (char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Test file reader function prototypes . . .							*/
	/*	*****************************************************************	*/
COMPAT_FN_DECL(int GEN_TFREAD_ReadLines, (const char *file_name,
	unsigned int *line_count, char ***line_list, char *error_text));
COMPAT_FN_DECL(int GEN_TFREAD_ReadLinesNoAlloc, (const char *file_name,
	unsigned int *line_count, char ***line_list, char *error_text));
COMPAT_FN_DECL(int GEN_TFREAD_ReadBufferXLateNL, (const char *file_name,
	const char *nl_string, unsigned int *buffer_length, char **buffer_ptr,
	char *error_text));
COMPAT_FN_DECL(int GEN_TFREAD_ReadBuffer, (const char *file_name,
	unsigned int *buffer_length, char **buffer_ptr, char *error_text));
COMPAT_FN_DECL(int GEN_TFREAD_ReadBufferRaw, (const char *file_name,
	unsigned int *buffer_length, char **buffer_ptr, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Host name function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int GEN_DetermineHostName, (char *host_name, char *error_text));
COMPAT_FN_DECL(int GEN_GetHostName, (char *host_name,
	unsigned int host_name_length));
COMPAT_FN_DECL(int GEN_SetHostName, (const char *host_name));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Process and thread ID function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(unsigned int GEN_GetProcessID, (void));
COMPAT_FN_DECL(unsigned int GEN_GetThreadID, (void));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Network address function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int GEN_GetMAC, (GEN_ADDR_MAC *ethernet_address,
	char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Miscellaneous function prototypes . . .								*/
	/*	*****************************************************************	*/
COMPAT_FN_DECL(const char *GEN_GetFileName, (const char *in_path));
	/*	*****************************************************************	*/

/* *********************************************************************** */

#endif /* #ifndef h__GENFUNCS_H__h */

