/* *********************************************************************** */
/* *********************************************************************** */
/*	Multi-Threading Interface Facility (MTIF) Library Include File				*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the Multi-Threading Interface
								Facility (MTIF) library.

	Revision History	:	1994-09-01 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

#ifndef h__MTIF_H__h

#define h__MTIF_H__h							1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Necessary include files . . .															*/
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
#elif MTIF_THR_UI_THREADS
# include <thread.h>
#elif _POSIX_C_SOURCE
# include <pthread.h>
# define MTIF_THR_POSIX_THREADS			1
#elif _POSIX_PTHREAD_SEMANTICS
# include <pthread.h>
# define MTIF_THR_POSIX_THREADS			1
#elif _POSIX_THREADS
# include <pthread.h>
# define MTIF_THR_POSIX_THREADS			1
#elif _REENTRANT
# include <thread.h>
# define MTIF_THR_UI_THREADS				1
#endif /* #ifdef _Windows */

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   BASE NAME   :  MTIF Truth Codes

   NAME        :  MTIF Truth Codes

   DESCRIPTION :  Manifest constants used within MTIF to specify the truth
						or falsity of expressions.

						(.) ''MTIF_TRUE''

						(.) ''MTIF_FALSE''

   NOTES       :  The manifest constant ''MTIF_TRUE'' should be defined as
						a non-zero value. Conversely, the manifest constant
						''MTIF_FALSE'' should be defined as zero (''0'').

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2014 Michael L. Brock

   OUTPUT INDEX:  MTIF_TRUE
						MTIF_FALSE
						MTIF Truth Codes:MTIF_TRUE
						MTIF Truth Codes:MTIF_FALSE
						MTIF Manifest Constants:MTIF_TRUE
						MTIF Manifest Constants:MTIF_FALSE
						MTIF Defines:MTIF_TRUE
						MTIF Defines:MTIF_FALSE
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:  MTIF Truth Codes
						MTIF Truth Code
						MTIF truth codes
						MTIF truth code
						MTIF_TRUE
						MTIF_FALSE

   PUBLISH NAME:	MTIF Truth Codes
						MTIF_TRUE
						MTIF_FALSE

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define MTIF_TRUE								1
#define MTIF_FALSE							0
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   BASE NAME   :	MTIF Return Codes

   NAME        :  MTIF Return Codes

   DESCRIPTION :  The MTIF return codes have the following meanings:

						(.) ''MTIF_SUCCESS'' means that the function invoked
						completed without error. ''MTIF_SUCCESS'' is guaranteed to
						be equal to zero (''0'').

						(.) ''MTIF_FAILURE'' indicates that the function invoked
						encountered a general operation failure. This is the
						'catch-all' error code for those errors which do not fit
						into category of one the other MTIF error codes.

						(.) ''MTIF_BAD_ARGS_FAILURE'' indicates that the
						arguments passed to a function invoked were invalid.

						(.) ''MTIF_MEMORY_FAILURE'' indicates that the memory
						required for operation of the function invoked could not be
						allocated.

						(.) ''MTIF_SYSTEM_FAILURE'' indicates that the function
						invoked encountered a failure of a standard library
						function or a system call.

						(.) ''MTIF_LOCK_ACQ_FAILURE'' indicates that a lock
						could not be acquired on a resource.

						(-) ''MTIF_LOCK_ACQ_FAILURE'' is returned by the functions
						``MTIF_MTX_TryLock``, ``MTIF_MTR_TryLock``,
						``MTIF_RWL_TryLockReader`` and ``MTIF_RWL_TryLockWriter``
						when the lock is held by a thread other than the invoking
						thread.

						(.) ''MTIF_INVALID_OBJECT'' indicates that an MTIF object
						was not valid.

						(.) ''MTIF_OP_FAILURE_THR'' indicates that an operation
						on an MTIF thread could not be completed.

						(.) ''MTIF_OP_FAILURE_MTX'' indicates that an operation
						on an MTIF non-recusive mutex could not be completed.

						(.) ''MTIF_OP_FAILURE_MTR'' indicates that an operation
						on an MTIF recusive mutex could not be completed.

						(.) ''MTIF_OP_FAILURE_RWL'' indicates that an operation
						on an MTIF reader/writer lock could not be completed.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2014 Michael L. Brock

   OUTPUT INDEX:  MTIF_SUCCESS
						MTIF_FAILURE
						MTIF_BAD_ARGS_FAILURE
						MTIF_MEMORY_FAILURE
						MTIF_SYSTEM_FAILURE
						MTIF_LOCK_ACQ_FAILURE
						MTIF_INVALID_OBJECT
						MTIF_OP_FAILURE_THR
						MTIF_OP_FAILURE_MTX
						MTIF_OP_FAILURE_MTR
						MTIF_OP_FAILURE_RWL
						MTIF Return Codes:MTIF_SUCCESS
						MTIF Return Codes:MTIF_FAILURE
						MTIF Return Codes:MTIF_BAD_ARGS_FAILURE
						MTIF Return Codes:MTIF_MEMORY_FAILURE
						MTIF Return Codes:MTIF_SYSTEM_FAILURE
						MTIF Return Codes:MTIF_LOCK_ACQ_FAILURE
						MTIF Return Codes:MTIF_INVALID_OBJECT
						MTIF Return Codes:MTIF_OP_FAILURE_THR
						MTIF Return Codes:MTIF_OP_FAILURE_MTX
						MTIF Return Codes:MTIF_OP_FAILURE_MTR
						MTIF Return Codes:MTIF_OP_FAILURE_RWL
						MTIF Manifest Constants:MTIF_SUCCESS
						MTIF Manifest Constants:MTIF_FAILURE
						MTIF Manifest Constants:MTIF_BAD_ARGS_FAILURE
						MTIF Manifest Constants:MTIF_MEMORY_FAILURE
						MTIF Manifest Constants:MTIF_SYSTEM_FAILURE
						MTIF Manifest Constants:MTIF_LOCK_ACQ_FAILURE
						MTIF Manifest Constants:MTIF_INVALID_OBJECT
						MTIF Manifest Constants:MTIF_OP_FAILURE_THR
						MTIF Manifest Constants:MTIF_OP_FAILURE_MTX
						MTIF Manifest Constants:MTIF_OP_FAILURE_MTR
						MTIF Manifest Constants:MTIF_OP_FAILURE_RWL
						MTIF Defines:MTIF_SUCCESS
						MTIF Defines:MTIF_FAILURE
						MTIF Defines:MTIF_BAD_ARGS_FAILURE
						MTIF Defines:MTIF_MEMORY_FAILURE
						MTIF Defines:MTIF_SYSTEM_FAILURE
						MTIF Defines:MTIF_LOCK_ACQ_FAILURE
						MTIF Defines:MTIF_INVALID_OBJECT
						MTIF Defines:MTIF_OP_FAILURE_THR
						MTIF Defines:MTIF_OP_FAILURE_MTX
						MTIF Defines:MTIF_OP_FAILURE_MTR
						MTIF Defines:MTIF_OP_FAILURE_RWL
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:  MTIF_SUCCESS
						MTIF_FAILURE
						MTIF_BAD_ARGS_FAILURE
						MTIF_MEMORY_FAILURE
						MTIF_SYSTEM_FAILURE
						MTIF_LOCK_ACQ_FAILURE
						MTIF_INVALID_OBJECT
						MTIF_OP_FAILURE_THR
						MTIF_OP_FAILURE_MTX
						MTIF_OP_FAILURE_MTR
						MTIF_OP_FAILURE_RWL
						MTIF Return Codes
						MTIF Return Code
						MTIF return codes
						MTIF return code
						MTIF Status Codes
						MTIF Status Code
						MTIF status codes
						MTIF status code
						MTIF Error Codes
						MTIF Error Code
						MTIF error codes
						MTIF error code

   PUBLISH NAME:	MTIF Return Codes
						MTIF return codes
						MTIF_SUCCESS
						MTIF_FAILURE
						MTIF_BAD_ARGS_FAILURE
						MTIF_MEMORY_FAILURE
						MTIF_SYSTEM_FAILURE
						MTIF_LOCK_ACQ_FAILURE
						MTIF_INVALID_OBJECT
						MTIF_OP_FAILURE_THR
						MTIF_OP_FAILURE_MTX
						MTIF_OP_FAILURE_MTR
						MTIF_OP_FAILURE_RWL

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define MTIF_SUCCESS							   0
#define MTIF_FAILURE							  -1
#define MTIF_BAD_ARGS_FAILURE				  -2
#define MTIF_MEMORY_FAILURE				  -3
#define MTIF_SYSTEM_FAILURE				  -4
#define MTIF_LOCK_ACQ_FAILURE				  -5
#define MTIF_INVALID_OBJECT				  -6
#define MTIF_OP_FAILURE_THR				  -7
#define MTIF_OP_FAILURE_MTX				  -8
#define MTIF_OP_FAILURE_MTR				  -9
#define MTIF_OP_FAILURE_RWL				 -10
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :  MTIF_MAX_ERROR_TEXT

   DESCRIPTION :  The manifest constant ''MTIF_MAX_ERROR_TEXT'' defines
						the minimum amount of storage which should be allocated to
						hold an error message returned by a MTIF function.

   CAVEATS     :  MTIF error messages can be quite lengthy. Therefore,
						attempting to save space by allocating less than
						''MTIF_MAX_ERROR_TEXT'' bytes to error message buffers
						passed to MTIF functions can lead to overwriting of the
						heap or the stack.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2014 Michael L. Brock

   OUTPUT INDEX:  MTIF_MAX_ERROR_TEXT
						MTIF Manifest Constants:MTIF_MAX_ERROR_TEXT
						MTIF Defines:MTIF_MAX_ERROR_TEXT
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	MTIF_MAX_ERROR_TEXT

   PUBLISH NAME:	MTIF_MAX_ERROR_TEXT

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define MTIF_MAX_ERROR_TEXT					4096
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/* *********************************************************************** */
#ifdef _Windows
# define MTIF_THR_IMPLEMENTATION_NAME	"Windows"
#elif MTIF_THR_UI_THREADS
# define MTIF_THR_IMPLEMENTATION_NAME	"Unix International"
#elif MTIF_THR_POSIX_THREADS
# define MTIF_THR_IMPLEMENTATION_NAME	"Posix"
#else
# define MTIF_THR_IMPLEMENTATION_NAME	"None"
#endif /* #ifdef _Windows */
/* *********************************************************************** */

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
typedef unsigned long MTIF_FLAG;
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
typedef unsigned long MTIF_SIGNATURE;
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
typedef COMPAT_FN_TYPE(void (*MTIF_DestroyLockAction), (void *user_data_ptr));
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#define MTIF_SIGNATURE_NONE				((MTIF_SIGNATURE) 0)
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#define MTIF_THR_SIGNATURE					((MTIF_SIGNATURE) 0x2B46294A)
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
typedef MTIF_FLAG MTIF_THR_FLAG;
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#define MTIF_THR_FLAG_NONE					((MTIF_THR_FLAG) 0x0000)
#define MTIF_THR_FLAG_IGNORE_BAD			((MTIF_THR_FLAG) 0x0001)
#define MTIF_THR_FLAG_BOUND				((MTIF_THR_FLAG) 0x0002)
#define MTIF_THR_FLAG_DETACHED			((MTIF_THR_FLAG) 0x0004)
#define MTIF_THR_FLAG_NEW_LWP				((MTIF_THR_FLAG) 0x0008)
#define MTIF_THR_FLAG_SUSPENDED			((MTIF_THR_FLAG) 0x0010)
#define MTIF_THR_FLAG_DAEMON				((MTIF_THR_FLAG) 0x0020)
#define MTIF_THR_FLAG_MASK					\
	(MTIF_THR_FLAG_IGNORE_BAD | MTIF_THR_FLAG_BOUND |	\
	 MTIF_THR_FLAG_DETACHED | MTIF_THR_FLAG_NEW_LWP |	\
	 MTIF_THR_FLAG_SUSPENDED | MTIF_THR_FLAG_DAEMON)
/*	***********************************************************************	*/

/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#ifdef _Windows
typedef DWORD MTIF_THR_ID;
typedef struct {
	HANDLE      thread_handle;
	MTIF_THR_ID thread_id;
} MTIF_THR_HANDLE;
#define MTIF_THR_ID_NONE					((MTIF_THR_ID) 0)
#elif MTIF_THR_UI_THREADS
typedef thread_t MTIF_THR_ID;
typedef thread_t MTIF_THR_HANDLE;
#define MTIF_THR_ID_NONE					((MTIF_THR_ID) 0)
#elif MTIF_THR_POSIX_THREADS
typedef pthread_t MTIF_THR_ID;
typedef pthread_t MTIF_THR_HANDLE;
#define MTIF_THR_ID_NONE					((MTIF_THR_ID) 0)
#else
typedef unsigned long MTIF_THR_ID;
typedef unsigned long MTIF_THR_HANDLE;
#define MTIF_THR_ID_NONE					((MTIF_THR_ID) 0)
#endif /* #ifdef _Windows */
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#ifdef _Windows
# define MTIF_THR_GET_OS_HANDLE(thr_handle_ptr)										\
	(((MTIF_THR_HANDLE *) (thr_handle_ptr))->thread_handle)
# define MTIF_THR_GET_OS_HANDLE_DEFAULT(thr_handle_ptr)							\
	(((thr_handle_ptr) != NULL) ? MTIF_THR_GET_OS_HANDLE(thr_handle_ptr) :	\
	 GetCurrentThread())
# define MTIF_THR_GET_OS_ID(thr_handle_ptr)											\
	(((MTIF_THR_HANDLE *) (thr_handle_ptr))->thread_id)
#else
# define MTIF_THR_GET_OS_HANDLE(thr_handle_ptr)										\
	(*((MTIF_THR_HANDLE *) (thr_handle_ptr)))
# define MTIF_THR_GET_OS_HANDLE_DEFAULT(thr_handle_ptr)							\
	(((thr_handle_ptr) != NULL) ? MTIF_THR_GET_OS_HANDLE(thr_handle_ptr) :	\
	 MTIF_THR_Self())
# define MTIF_THR_GET_OS_ID(thr_handle_ptr)											\
	(*((MTIF_THR_HANDLE *) (thr_handle_ptr)))
#endif /* #ifdef _Windows */

#define MTIF_THR_GET_OS_ID_DEFAULT(thr_handle_ptr)									\
	(((thr_handle_ptr) != NULL) ? MTIF_THR_GET_OS_ID(thr_handle_ptr)     :	\
	 MTIF_THR_Self())
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#ifdef _Windows
# define MTIF_THR_FLAG_DEFAULT			MTIF_THR_FLAG_BOUND
# define MTIF_THR_FLAG_MASK_FACILITY	\
	(MTIF_THR_FLAG_IGNORE_BAD | MTIF_THR_FLAG_BOUND |	\
	 MTIF_THR_FLAG_DETACHED | MTIF_THR_FLAG_SUSPENDED)
#elif MTIF_THR_UI_THREADS
# define MTIF_THR_FLAG_DEFAULT			MTIF_THR_FLAG_NONE
# define MTIF_THR_FLAG_MASK_FACILITY	\
	(MTIF_THR_FLAG_IGNORE_BAD | MTIF_THR_FLAG_BOUND |	\
	 MTIF_THR_FLAG_DETACHED | MTIF_THR_FLAG_NEW_LWP |	\
	 MTIF_THR_FLAG_SUSPENDED | MTIF_THR_FLAG_DAEMON)
#elif MTIF_THR_POSIX_THREADS
# define MTIF_THR_FLAG_DEFAULT			MTIF_THR_FLAG_NONE
# define MTIF_THR_FLAG_MASK_FACILITY	\
	(MTIF_THR_FLAG_IGNORE_BAD | MTIF_THR_FLAG_BOUND |	\
	 MTIF_THR_FLAG_DETACHED)
#else
# define MTIF_THR_FLAG_DEFAULT			MTIF_THR_FLAG_NONE
# define MTIF_THR_FLAG_MASK_FACILITY   MTIF_THR_FLAG_IGNORE_BAD
#endif /* #ifdef _Windows */
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
typedef COMPAT_FN_TYPE(void *(*MTIF_THR_StartFunc), (void *user_data_ptr));
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/* *********************************************************************** */
typedef enum {
	MTIF_THR_PRIORITY_NONE		= 0,
	MTIF_THR_PRIORITY_MINIMUM	= 1,
	MTIF_THR_PRIORITY_LOWEST	= 1,
	MTIF_THR_PRIORITY_LOWER		= 2,
	MTIF_THR_PRIORITY_LOW		= 3,
	MTIF_THR_PRIORITY_MEDIUM	= 4,
	MTIF_THR_PRIORITY_HIGH		= 5,
	MTIF_THR_PRIORITY_HIGHER	= 6,
	MTIF_THR_PRIORITY_HIGHEST	= 7,
	MTIF_THR_PRIORITY_MAXIMUM	= 7,
	MTIF_THR_PRIORITY_COUNT		= 7
} MTIF_THR_PRIORITY;

typedef int MTIF_THR_PRIORITY_NATIVE;
/* *********************************************************************** */

/*
	ADF NOTE:	No ADF.
*/
/* *********************************************************************** */
typedef struct {
	MTIF_THR_PRIORITY        mtif_priority;
	MTIF_THR_PRIORITY        match_priority;
	MTIF_THR_PRIORITY_NATIVE native_priority;
} MTIF_THR_PRIORITY_MAP;
/* *********************************************************************** */

/*
	ADF NOTE:	No ADF.
*/
/* *********************************************************************** */
#define MTIF_GET_THR_PRIORITY_NAME(mtif_priority)						\
	(((mtif_priority) == MTIF_THR_PRIORITY_NONE)    ? "NONE"    :	\
	 ((mtif_priority) == MTIF_THR_PRIORITY_LOWEST)  ? "LOWEST"  :	\
	 ((mtif_priority) == MTIF_THR_PRIORITY_LOWER)   ? "LOWER"   :	\
	 ((mtif_priority) == MTIF_THR_PRIORITY_LOW)     ? "LOW"     :	\
	 ((mtif_priority) == MTIF_THR_PRIORITY_MEDIUM)  ? "MEDIUM"  :	\
	 ((mtif_priority) == MTIF_THR_PRIORITY_HIGH)    ? "HIGH"    :	\
	 ((mtif_priority) == MTIF_THR_PRIORITY_HIGHER)  ? "HIGHER"  :	\
	 ((mtif_priority) == MTIF_THR_PRIORITY_HIGHEST) ? "HIGHEST" :	\
	 NULL)
/* *********************************************************************** */

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#define MTIF_MTX_SIGNATURE					((MTIF_SIGNATURE) 0x13C30AD8)
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
typedef MTIF_FLAG MTIF_MTX_FLAG;
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#define MTIF_MTX_FLAG_NONE					((MTIF_MTX_FLAG) 0x0000)
#define MTIF_MTX_FLAG_IGNORE_BAD			((MTIF_MTX_FLAG) 0x0001)
#define MTIF_MTX_FLAG_SHARED				((MTIF_MTX_FLAG) 0x0002)
#define MTIF_MTX_FLAG_STATIC				((MTIF_MTX_FLAG) 0x0004)
#define MTIF_MTX_FLAG_RECURSIVE			((MTIF_MTX_FLAG) 0x0008)
#define MTIF_MTX_FLAG_MASK					\
	(MTIF_MTX_FLAG_IGNORE_BAD | MTIF_MTX_FLAG_SHARED)
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#ifdef _Windows
typedef struct {
	MTIF_SIGNATURE  signature;
	MTIF_MTX_FLAG   init_flags;
	int             static_flag;
	unsigned long   process_id;
	MTIF_THR_ID     thread_id;
	HANDLE          mtx_data;
	char           *mtx_name;
} MTIF_MTX_HANDLE;
#elif MTIF_THR_UI_THREADS
typedef struct {
	MTIF_SIGNATURE signature;
	MTIF_MTX_FLAG  init_flags;
	int            static_flag;
	unsigned long  process_id;
	MTIF_THR_ID    thread_id;
	mutex_t        mtx_data;
} MTIF_MTX_HANDLE;
#elif MTIF_THR_POSIX_THREADS
typedef struct {
	MTIF_SIGNATURE  signature;
	MTIF_MTX_FLAG   init_flags;
	int             static_flag;
	unsigned long   process_id;
	MTIF_THR_ID     thread_id;
	pthread_mutex_t mtx_data;
} MTIF_MTX_HANDLE;
#else
typedef struct {
	MTIF_SIGNATURE signature;
	MTIF_MTX_FLAG  init_flags;
	int            static_flag;
	unsigned long  process_id;
	MTIF_THR_ID    thread_id;
	unsigned long  mtx_data;
} MTIF_MTX_HANDLE;
#endif /* #ifdef _Windows */
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#ifdef _Windows
# define MTIF_MTX_FLAG_DEFAULT			MTIF_MTX_FLAG_NONE
# define MTIF_MTX_FLAG_MASK_FACILITY	\
	(MTIF_MTX_FLAG_IGNORE_BAD | MTIF_MTX_FLAG_RECURSIVE)
#elif MTIF_THR_UI_THREADS
# define MTIF_MTX_FLAG_DEFAULT			MTIF_MTX_FLAG_NONE
# define MTIF_MTX_FLAG_MASK_FACILITY	\
	(MTIF_MTX_FLAG_IGNORE_BAD | MTIF_MTX_FLAG_SHARED | MTIF_MTX_FLAG_RECURSIVE)
#elif MTIF_THR_POSIX_THREADS
# define MTIF_MTX_FLAG_DEFAULT			MTIF_MTX_FLAG_NONE
# define MTIF_MTX_FLAG_MASK_FACILITY	\
	(MTIF_MTX_FLAG_IGNORE_BAD | MTIF_MTX_FLAG_SHARED | MTIF_MTX_FLAG_RECURSIVE)
#else
# define MTIF_MTX_FLAG_DEFAULT			MTIF_MTX_FLAG_NONE
# define MTIF_MTX_FLAG_MASK_FACILITY	MTIF_MTX_FLAG_IGNORE_BAD
#endif /* #ifdef _Windows */
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#ifdef _Windows
# define MTIF_MTX_STATIC_INIT																	\
	{	MTIF_MTX_SIGNATURE,																		\
		MTIF_MTX_FLAG_DEFAULT | MTIF_MTX_FLAG_IGNORE_BAD | MTIF_MTX_FLAG_STATIC,\
		MTIF_TRUE, 0L, ((MTIF_THR_ID) 0), ((HANDLE) NULL)	}
#elif MTIF_THR_UI_THREADS
# define MTIF_MTX_STATIC_INIT																	\
	{	MTIF_MTX_SIGNATURE,																		\
		MTIF_MTX_FLAG_DEFAULT | MTIF_MTX_FLAG_IGNORE_BAD | MTIF_MTX_FLAG_STATIC,\
		MTIF_TRUE, 0L, ((MTIF_THR_ID) 0), DEFAULTMUTEX	}
#elif MTIF_THR_POSIX_THREADS
# define MTIF_MTX_STATIC_INIT																	\
	{	MTIF_MTX_SIGNATURE,																		\
		MTIF_MTX_FLAG_DEFAULT | MTIF_MTX_FLAG_IGNORE_BAD | MTIF_MTX_FLAG_STATIC,\
		MTIF_TRUE, 0L, ((MTIF_THR_ID) 0), PTHREAD_MUTEX_INITIALIZER	}
#else
# define MTIF_MTX_STATIC_INIT																	\
	{	MTIF_MTX_SIGNATURE,																		\
		MTIF_MTX_FLAG_DEFAULT | MTIF_MTX_FLAG_IGNORE_BAD | MTIF_MTX_FLAG_STATIC,\
		MTIF_TRUE, 0L, ((MTIF_THR_ID) 0), ((unsigned long) 0L)	}
#endif /* #ifdef _Windows */
/*	***********************************************************************	*/

/*
	ADF NOTE: Name: Basic Mutex Locked Data Types
*/
/*	***********************************************************************	*/
typedef struct {
	MTIF_MTX_HANDLE lock_data;
	int             value;
} MTIF_MTX_DATA_SINT;

typedef struct {
	MTIF_MTX_HANDLE lock_data;
	unsigned int    value;
} MTIF_MTX_DATA_UINT;

typedef struct {
	MTIF_MTX_HANDLE lock_data;
	long            value;
} MTIF_MTX_DATA_SLONG;

typedef struct {
	MTIF_MTX_HANDLE lock_data;
	unsigned long   value;
} MTIF_MTX_DATA_ULONG;

#if defined(_MSC_VER) && (_MSC_VER >= 1400)
# pragma warning(push)
# pragma warning(disable:4820)
#endif /* #if defined(_MSC_VER) && (_MSC_VER >= 1400) */

typedef struct {
	MTIF_MTX_HANDLE lock_data;
	double          value;
} MTIF_MTX_DATA_DOUBLE;

#if defined(_MSC_VER) && (_MSC_VER >= 1400)
# pragma warning(pop)
#endif /* #if defined(_MSC_VER) && (_MSC_VER >= 1400) */

/*	***********************************************************************	*/

/*
	ADF NOTE: Name: Basic Mutex Locked Data Type Static Initializers
*/
/*	***********************************************************************	*/
#define MTIF_MTX_DATA_SINT_STATIC_INIT(value)	\
	{	MTIF_MTX_STATIC_INIT, (value)	}
#define MTIF_MTX_DATA_UINT_STATIC_INIT(value)	\
	{	MTIF_MTX_STATIC_INIT, (value)	}
#define MTIF_MTX_DATA_ULONG_STATIC_INIT(value)	\
	{	MTIF_MTX_STATIC_INIT, (value)	}
#define MTIF_MTX_DATA_SLONG_STATIC_INIT(value)	\
	{	MTIF_MTX_STATIC_INIT, (value)	}
#define MTIF_MTX_DATA_DOUBLE_STATIC_INIT(value)	\
	{	MTIF_MTX_STATIC_INIT, (value)	}
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#define MTIF_MTR_SIGNATURE					((MTIF_SIGNATURE) 0x0DA03C31)
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
typedef MTIF_FLAG MTIF_MTR_FLAG;
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#define MTIF_MTR_FLAG_NONE					((MTIF_MTR_FLAG) 0x0000)
#define MTIF_MTR_FLAG_IGNORE_BAD			((MTIF_MTR_FLAG) 0x0001)
#define MTIF_MTR_FLAG_SHARED				((MTIF_MTR_FLAG) 0x0002)
#define MTIF_MTR_FLAG_STATIC				((MTIF_MTX_FLAG) 0x0004)
#define MTIF_MTR_FLAG_MASK					\
	(MTIF_MTR_FLAG_IGNORE_BAD | MTIF_MTR_FLAG_SHARED)
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#ifdef _Windows
typedef struct {
	MTIF_SIGNATURE  signature;
	MTIF_MTR_FLAG   init_flags;
	int             static_flag;
	unsigned long   process_id;
	MTIF_THR_ID     thread_id;
	unsigned long   lock_count;
	HANDLE          mtr_data;
	char           *mtr_name;
} MTIF_MTR_HANDLE;
#elif MTIF_THR_UI_THREADS
typedef struct {
	MTIF_SIGNATURE signature;
	MTIF_MTR_FLAG  init_flags;
	int            static_flag;
	unsigned long  process_id;
	MTIF_THR_ID    thread_id;
	unsigned long  lock_count;
	mutex_t        mtr_data;
} MTIF_MTR_HANDLE;
#elif MTIF_THR_POSIX_THREADS
typedef struct {
	MTIF_SIGNATURE  signature;
	MTIF_MTR_FLAG   init_flags;
	int             static_flag;
	unsigned long   process_id;
	MTIF_THR_ID     thread_id;
	unsigned long   lock_count;
	pthread_mutex_t mtr_data;
} MTIF_MTR_HANDLE;
#else
typedef struct {
	MTIF_SIGNATURE signature;
	MTIF_MTR_FLAG  init_flags;
	int            static_flag;
	unsigned long  process_id;
	MTIF_THR_ID    thread_id;
	unsigned long  lock_count;
	unsigned long  mtr_data;
} MTIF_MTR_HANDLE;
#endif /* #ifdef _Windows */
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#ifdef _Windows
# define MTIF_MTR_FLAG_DEFAULT			MTIF_MTR_FLAG_NONE
# define MTIF_MTR_FLAG_MASK_FACILITY	MTIF_MTR_FLAG_IGNORE_BAD
#elif MTIF_THR_UI_THREADS
# define MTIF_MTR_FLAG_DEFAULT			MTIF_MTR_FLAG_NONE
# define MTIF_MTR_FLAG_MASK_FACILITY	\
	(MTIF_MTR_FLAG_IGNORE_BAD | MTIF_MTR_FLAG_SHARED)
#elif MTIF_THR_POSIX_THREADS
# define MTIF_MTR_FLAG_DEFAULT			MTIF_MTR_FLAG_NONE
# define MTIF_MTR_FLAG_MASK_FACILITY	\
	(MTIF_MTR_FLAG_IGNORE_BAD | MTIF_MTR_FLAG_SHARED)
#else
# define MTIF_MTR_FLAG_DEFAULT			MTIF_MTR_FLAG_NONE
# define MTIF_MTR_FLAG_MASK_FACILITY	MTIF_MTR_FLAG_IGNORE_BAD
#endif /* #ifdef _Windows */
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#ifdef _Windows
# define MTIF_MTR_STATIC_INIT																	\
	{	MTIF_MTR_SIGNATURE,																		\
		MTIF_MTR_FLAG_DEFAULT | MTIF_MTR_FLAG_IGNORE_BAD | MTIF_MTR_FLAG_STATIC,\
		MTIF_TRUE, 0L, ((MTIF_THR_ID) 0), 0L, ((HANDLE) NULL)					}
#elif MTIF_THR_UI_THREADS
# define MTIF_MTR_STATIC_INIT																	\
	{	MTIF_MTR_SIGNATURE,																		\
		MTIF_MTR_FLAG_DEFAULT | MTIF_MTR_FLAG_IGNORE_BAD | MTIF_MTR_FLAG_STATIC,\
		MTIF_TRUE, 0L, ((MTIF_THR_ID) 0), 0L, DEFAULTMUTEX						}
#elif MTIF_THR_POSIX_THREADS
# define MTIF_MTR_STATIC_INIT																	\
	{	MTIF_MTR_SIGNATURE,																		\
		MTIF_MTR_FLAG_DEFAULT | MTIF_MTR_FLAG_IGNORE_BAD | MTIF_MTR_FLAG_STATIC,\
		MTIF_TRUE, 0L, ((MTIF_THR_ID) 0), 0L, PTHREAD_MUTEX_INITIALIZER	}
#else
# define MTIF_MTR_STATIC_INIT																	\
	{	MTIF_MTR_SIGNATURE,																		\
		MTIF_MTR_FLAG_DEFAULT | MTIF_MTR_FLAG_IGNORE_BAD | MTIF_MTR_FLAG_STATIC,\
		MTIF_TRUE, 0L, ((MTIF_THR_ID) 0), 0L, ((unsigned long) 0L)	}
#endif /* #ifdef _Windows */
/*	***********************************************************************	*/

/*
	ADF NOTE: Name: Recursive Mutex Locked Data Types
*/
/*	***********************************************************************	*/
typedef struct {
	MTIF_MTR_HANDLE lock_data;
	int             value;
} MTIF_MTR_DATA_SINT;

typedef struct {
	MTIF_MTR_HANDLE lock_data;
	unsigned int    value;
} MTIF_MTR_DATA_UINT;

typedef struct {
	MTIF_MTR_HANDLE lock_data;
	long            value;
} MTIF_MTR_DATA_SLONG;

typedef struct {
	MTIF_MTR_HANDLE lock_data;
	unsigned long   value;
} MTIF_MTR_DATA_ULONG;

typedef struct {
	MTIF_MTR_HANDLE lock_data;
	double          value;
} MTIF_MTR_DATA_DOUBLE;
/*	***********************************************************************	*/

/*
	ADF NOTE: Name: Recursive Mutex Locked Data Type Static Initializers
*/
/*	***********************************************************************	*/
#define MTIF_MTR_DATA_SINT_STATIC_INIT(value)	\
	{	MTIF_MTR_STATIC_INIT, (value)	}
#define MTIF_MTR_DATA_UINT_STATIC_INIT(value)	\
	{	MTIF_MTR_STATIC_INIT, (value)	}
#define MTIF_MTR_DATA_ULONG_STATIC_INIT(value)	\
	{	MTIF_MTR_STATIC_INIT, (value)	}
#define MTIF_MTR_DATA_SLONG_STATIC_INIT(value)	\
	{	MTIF_MTR_STATIC_INIT, (value)	}
#define MTIF_MTR_DATA_DOUBLE_STATIC_INIT(value)	\
	{	MTIF_MTR_STATIC_INIT, (value)	}
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#define MTIF_RWL_SIGNATURE					((MTIF_SIGNATURE) 0x73f9518d)
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
typedef MTIF_FLAG MTIF_RWL_FLAG;
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#define MTIF_RWL_FLAG_NONE					((MTIF_RWL_FLAG) 0x0000)
#define MTIF_RWL_FLAG_IGNORE_BAD			((MTIF_RWL_FLAG) 0x0001)
#define MTIF_RWL_FLAG_SHARED				((MTIF_RWL_FLAG) 0x0002)
#define MTIF_RWL_FLAG_STATIC				((MTIF_RWL_FLAG) 0x0004)
#define MTIF_RWL_FLAG_MASK					\
	(MTIF_RWL_FLAG_IGNORE_BAD | MTIF_RWL_FLAG_SHARED)
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
	CODE NOTE:	Earlier versions of the POSIX specification (such as Solaris 5.x)
					do not support the ``pthread_rw``''X''``()`` functions. This
					library will in those cases implement reader/writer locks using
					a mutex and condition variable.
*/
/*	***********************************************************************	*/
#ifdef _Windows
typedef struct {
	MTIF_SIGNATURE  signature;
	MTIF_RWL_FLAG   init_flags;
	int             static_flag;
	unsigned long   process_id;
	MTIF_THR_ID     thread_id;
	HANDLE          rwl_data;
	char           *rwl_name;
} MTIF_RWL_HANDLE;
#elif MTIF_THR_UI_THREADS
typedef struct {
	MTIF_SIGNATURE signature;
	MTIF_RWL_FLAG  init_flags;
	int            static_flag;
	unsigned long  process_id;
	MTIF_THR_ID    thread_id;
	rwlock_t       rwl_data;
} MTIF_RWL_HANDLE;
#elif MTIF_THR_POSIX_THREADS
typedef struct {
	MTIF_SIGNATURE  signature;
	MTIF_RWL_FLAG   init_flags;
	int             static_flag;
	unsigned long   process_id;
	MTIF_THR_ID     thread_id;
	pthread_mutex_t rwl_data;
} MTIF_RWL_HANDLE;
#else
typedef struct {
	MTIF_SIGNATURE signature;
	MTIF_RWL_FLAG  init_flags;
	int            static_flag;
	unsigned long  process_id;
	MTIF_THR_ID    thread_id;
	unsigned long  rwl_data;
} MTIF_RWL_HANDLE;
#endif /* #ifdef _Windows */
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#ifdef _Windows
# define MTIF_RWL_FLAG_DEFAULT			MTIF_RWL_FLAG_NONE
# define MTIF_RWL_FLAG_MASK_FACILITY	MTIF_RWL_FLAG_IGNORE_BAD
#elif MTIF_THR_UI_THREADS
# define MTIF_RWL_FLAG_DEFAULT			MTIF_RWL_FLAG_NONE
# define MTIF_RWL_FLAG_MASK_FACILITY	\
	(MTIF_RWL_FLAG_IGNORE_BAD | MTIF_RWL_FLAG_SHARED)
#elif MTIF_THR_POSIX_THREADS
# define MTIF_RWL_FLAG_DEFAULT			MTIF_RWL_FLAG_NONE
# define MTIF_RWL_FLAG_MASK_FACILITY	\
	(MTIF_RWL_FLAG_IGNORE_BAD | MTIF_RWL_FLAG_SHARED)
#else
# define MTIF_RWL_FLAG_DEFAULT			MTIF_RWL_FLAG_NONE
# define MTIF_RWL_FLAG_MASK_FACILITY	MTIF_RWL_FLAG_IGNORE_BAD
#endif /* #ifdef _Windows */
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#ifdef _Windows
# define MTIF_RWL_STATIC_INIT																	\
	{	MTIF_RWL_SIGNATURE,																		\
		MTIF_RWL_FLAG_DEFAULT | MTIF_RWL_FLAG_IGNORE_BAD | MTIF_RWL_FLAG_STATIC,\
		MTIF_TRUE, 0L, ((MTIF_THR_ID) 0), ((HANDLE) NULL)				}
#elif MTIF_THR_UI_THREADS
# define MTIF_RWL_STATIC_INIT																	\
	{	MTIF_RWL_SIGNATURE,																		\
		MTIF_RWL_FLAG_DEFAULT | MTIF_RWL_FLAG_IGNORE_BAD | MTIF_RWL_FLAG_STATIC,\
		MTIF_TRUE, 0L, ((MTIF_THR_ID) 0), DEFAULTRWLOCK					}
#elif MTIF_THR_POSIX_THREADS
# define MTIF_RWL_STATIC_INIT																	\
	{	MTIF_RWL_SIGNATURE,																		\
		MTIF_RWL_FLAG_DEFAULT | MTIF_RWL_FLAG_IGNORE_BAD | MTIF_RWL_FLAG_STATIC,\
		MTIF_TRUE, 0L, ((MTIF_THR_ID) 0), PTHREAD_MUTEX_INITIALIZER	}
#else
# define MTIF_RWL_STATIC_INIT																	\
	{	MTIF_RWL_SIGNATURE,																		\
		MTIF_RWL_FLAG_DEFAULT | MTIF_RWL_FLAG_IGNORE_BAD | MTIF_RWL_FLAG_STATIC,\
		MTIF_TRUE, 0L, ((MTIF_THR_ID) 0), ((unsigned long) 0L)	}
#endif /* #ifdef _Windows */
/*	***********************************************************************	*/

/*
	ADF NOTE: Name: Reader/Writer Lock Locked Data Types
*/
/*	***********************************************************************	*/
typedef struct {
	MTIF_RWL_HANDLE lock_data;
	int             value;
} MTIF_RWL_DATA_SINT;

typedef struct {
	MTIF_RWL_HANDLE lock_data;
	unsigned int    value;
} MTIF_RWL_DATA_UINT;

typedef struct {
	MTIF_RWL_HANDLE lock_data;
	long            value;
} MTIF_RWL_DATA_SLONG;

typedef struct {
	MTIF_RWL_HANDLE lock_data;
	unsigned long   value;
} MTIF_RWL_DATA_ULONG;

#if defined(_MSC_VER) && (_MSC_VER >= 1400)
# pragma warning(push)
# pragma warning(disable:4820)
#endif /* #if defined(_MSC_VER) && (_MSC_VER >= 1400) */

typedef struct {
	MTIF_RWL_HANDLE lock_data;
	double          value;
} MTIF_RWL_DATA_DOUBLE;

#if defined(_MSC_VER) && (_MSC_VER >= 1400)
# pragma warning(pop)
#endif /* #if defined(_MSC_VER) && (_MSC_VER >= 1400) */

/*	***********************************************************************	*/

/*
	ADF NOTE: Name: Reader/Writer Lock Locked Data Type Static Initializers
*/
/*	***********************************************************************	*/
#define MTIF_RWL_DATA_SINT_STATIC_INIT(value)	\
	{	MTIF_RWL_STATIC_INIT, (value)	}
#define MTIF_RWL_DATA_UINT_STATIC_INIT(value)	\
	{	MTIF_RWL_STATIC_INIT, (value)	}
#define MTIF_RWL_DATA_ULONG_STATIC_INIT(value)	\
	{	MTIF_RWL_STATIC_INIT, (value)	}
#define MTIF_RWL_DATA_SLONG_STATIC_INIT(value)	\
	{	MTIF_RWL_STATIC_INIT, (value)	}
#define MTIF_RWL_DATA_DOUBLE_STATIC_INIT(value)	\
	{	MTIF_RWL_STATIC_INIT, (value)	}
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#define MTIF_DATA_GET_RAW_VALUE(datum_ptr)		\
	((datum_ptr)->value)
#define MTIF_DATA_GET_RAW_VALUE_PTR(datum_ptr)	\
	(&(datum_ptr)->value)
#define MTIF_DATA_GET_RAW_LOCK_PTR(datum_ptr)	\
	(&(datum_ptr)->lock_data)
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#define MTIF_ONC_SIGNATURE					((MTIF_SIGNATURE) 0x2379d13)
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
typedef struct {
	MTIF_SIGNATURE  signature;
	int             once_flag;
	MTIF_MTX_HANDLE mtx_data;
} MTIF_ONC_HANDLE;
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#define MTIF_ONC_INIT						\
	{	MTIF_ONC_SIGNATURE, MTIF_FALSE, MTIF_MTX_STATIC_INIT	}
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
typedef COMPAT_FN_TYPE(int (*MTIF_ONC_OnceFunc),
	(void *user_data_ptr, char *error_text));
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#define MTIF_SPIN_ON_DATA_FOREVER		((unsigned int) 0)
#define MTIF_SPIN_ON_DATA_ONCE			((unsigned int) 1)
#define MTIF_SPIN_ON_DATA_LONGEST		((unsigned int) UINT_MAX)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Functions provided in library 'mtif.{a|lib}' . . .								*/
/*	***********************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Thread function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int           MTIF_THR_Check,
	(const MTIF_THR_HANDLE *thr_handle_ptr, char *error_text));
COMPAT_FN_DECL(int           MTIF_THR_Create,
	(MTIF_THR_FLAG flags, unsigned int stack_size,
	MTIF_THR_StartFunc start_func, void *start_data,
	MTIF_THR_HANDLE *thr_handle_ptr, char *error_text));
COMPAT_FN_DECL(int           MTIF_THR_Equal,
	(MTIF_THR_HANDLE *thr_handle_ptr_1, MTIF_THR_HANDLE *thr_handle_ptr_2));
COMPAT_FN_DECL(void          MTIF_THR_Exit,
	(void *exit_data));
COMPAT_FN_DECL(int           MTIF_THR_Join,
	(MTIF_THR_HANDLE *thr_handle_ptr, void **status_ptr, char *error_text));
COMPAT_FN_DECL(MTIF_THR_ID MTIF_THR_Self,
	(void));
COMPAT_FN_DECL(unsigned long MTIF_THR_SelfProcess,
	(void));
COMPAT_FN_DECL(int           MTIF_THR_Suspend,
	(MTIF_THR_HANDLE *thr_handle_ptr, char *error_text));
COMPAT_FN_DECL(int           MTIF_THR_Resume,
	(MTIF_THR_HANDLE *thr_handle_ptr, char *error_text));
COMPAT_FN_DECL(void          MTIF_THR_Yield,
	(void));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Non-recursive mutex function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int MTIF_MTX_Check,
	(const MTIF_MTX_HANDLE *mtx_handle_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_MTX_Destroy,
	(MTIF_MTX_HANDLE *mtx_handle_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_MTX_DestroyAction,
	(MTIF_MTX_HANDLE *mtx_handle_ptr, MTIF_DestroyLockAction action_func,
	char *error_text));
COMPAT_FN_DECL(int MTIF_MTX_DestroyStaticAlso,
	(MTIF_MTX_HANDLE *mtx_handle_ptr, int destroy_if_static_flag,
	char *error_text));
COMPAT_FN_DECL(int MTIF_MTX_Init,
	(MTIF_MTX_FLAG flags, const char *mtx_name,
	MTIF_MTX_HANDLE *mtx_handle_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_MTX_Lock,
	(MTIF_MTX_HANDLE *mtx_handle_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_MTX_LockReader,
	(MTIF_MTX_HANDLE *mtx_handle_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_MTX_LockWriter,
	(MTIF_MTX_HANDLE *mtx_handle_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_MTX_TryLock,
	(MTIF_MTX_HANDLE *mtx_handle_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_MTX_TryLockReader,
	(MTIF_MTX_HANDLE *mtx_handle_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_MTX_TryLockWriter,
	(MTIF_MTX_HANDLE *mtx_handle_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_MTX_Unlock,
	(MTIF_MTX_HANDLE *mtx_handle_ptr, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Recursive mutex function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int MTIF_MTR_Check,
	(const MTIF_MTR_HANDLE *mtr_handle_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_MTR_Destroy,
	(MTIF_MTR_HANDLE *mtr_handle_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_MTR_DestroyAction,
	(MTIF_MTR_HANDLE *mtr_handle_ptr, MTIF_DestroyLockAction action_func,
	char *error_text));
COMPAT_FN_DECL(int MTIF_MTR_DestroyStaticAlso,
	(MTIF_MTR_HANDLE *mtr_handle_ptr, int destroy_if_static_flag,
	char *error_text));
COMPAT_FN_DECL(int MTIF_MTR_Init,
	(MTIF_MTR_FLAG flags, const char *mtx_name,
	MTIF_MTR_HANDLE *mtr_handle_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_MTR_Lock,
	(MTIF_MTR_HANDLE *mtr_handle_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_MTR_LockReader,
	(MTIF_MTR_HANDLE *mtr_handle_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_MTR_LockWriter,
	(MTIF_MTR_HANDLE *mtr_handle_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_MTR_TryLock,
	(MTIF_MTR_HANDLE *mtr_handle_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_MTR_TryLockReader,
	(MTIF_MTR_HANDLE *mtr_handle_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_MTR_TryLockWriter,
	(MTIF_MTR_HANDLE *mtr_handle_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_MTR_Unlock,
	(MTIF_MTR_HANDLE *mtr_handle_ptr, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Reader/writer lock function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int MTIF_RWL_Check,
	(const MTIF_RWL_HANDLE *rwl_handle_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_RWL_Destroy,
	(MTIF_RWL_HANDLE *rwl_handle_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_RWL_DestroyAction,
	(MTIF_RWL_HANDLE *rwl_handle_ptr, MTIF_DestroyLockAction action_func,
	char *error_text));
COMPAT_FN_DECL(int MTIF_RWL_DestroyStaticAlso,
	(MTIF_RWL_HANDLE *rwl_handle_ptr, int destroy_if_static_flag,
	char *error_text));
COMPAT_FN_DECL(int MTIF_RWL_Init,
	(MTIF_RWL_FLAG flags, const char *rwl_name,
	MTIF_RWL_HANDLE *rwl_handle_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_RWL_Lock,
	(MTIF_RWL_HANDLE *rwl_handle_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_RWL_LockReader,
	(MTIF_RWL_HANDLE *rwl_handle_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_RWL_LockWriter,
	(MTIF_RWL_HANDLE *rwl_handle_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_RWL_TryLock,
	(MTIF_RWL_HANDLE *rwl_handle_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_RWL_TryLockReader,
	(MTIF_RWL_HANDLE *rwl_handle_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_RWL_TryLockWriter,
	(MTIF_RWL_HANDLE *rwl_handle_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_RWL_Unlock,
	(MTIF_RWL_HANDLE *rwl_handle_ptr, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Once-only initialization lock function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int MTIF_ONC_Check,
	(const MTIF_ONC_HANDLE *once_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_ONC_Once,
	(MTIF_ONC_HANDLE *once_ptr, MTIF_ONC_OnceFunc once_func, void *once_data,
	char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Priority management function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int MTIF_THR_GetPriority,
	(MTIF_THR_HANDLE *thr_handle_ptr, MTIF_THR_PRIORITY *mtif_priority,
	char *error_text));
COMPAT_FN_DECL(int MTIF_THR_GetPriorityNative,
	(MTIF_THR_HANDLE *thr_handle_ptr, MTIF_THR_PRIORITY_NATIVE *native_priority,
	char *error_text));
COMPAT_FN_DECL(int MTIF_THR_SetPriority,
	(MTIF_THR_HANDLE *thr_handle_ptr, MTIF_THR_PRIORITY mtif_priority,
	char *error_text));
COMPAT_FN_DECL(int MTIF_THR_SetPriorityNative,
	(MTIF_THR_HANDLE *thr_handle_ptr, MTIF_THR_PRIORITY_NATIVE native_priority,
	char *error_text));
COMPAT_FN_DECL(int MTIF_THR_PriorityToNative,
	(MTIF_THR_HANDLE *thr_handle_ptr, MTIF_THR_PRIORITY mtif_priority,
	MTIF_THR_PRIORITY_NATIVE *native_priority, char *error_text));
COMPAT_FN_DECL(int MTIF_THR_PriorityFromNative,
	(MTIF_THR_HANDLE *thr_handle_ptr, MTIF_THR_PRIORITY_NATIVE native_priority,
	MTIF_THR_PRIORITY *mtif_priority, char *error_text));
COMPAT_FN_DECL(int MTIF_THR_GetPriorityMinNative,
	(MTIF_THR_HANDLE *thr_handle_ptr, MTIF_THR_PRIORITY_NATIVE *min_priority,
	char *error_text));
COMPAT_FN_DECL(int MTIF_THR_GetPriorityMaxNative,
	(MTIF_THR_HANDLE *thr_handle_ptr, MTIF_THR_PRIORITY_NATIVE *max_priority,
	char *error_text));
COMPAT_FN_DECL(int MTIF_THR_GetPriorityMinMaxNative,
	(MTIF_THR_HANDLE *thr_handle_ptr, MTIF_THR_PRIORITY_NATIVE *min_priority,
	MTIF_THR_PRIORITY_NATIVE *max_priority, char *error_text));
COMPAT_FN_DECL(int MTIF_THR_GetPriorityMapNative,
	(MTIF_THR_HANDLE *thr_handle_ptr, unsigned int *out_count,
	MTIF_THR_PRIORITY_MAP **out_list, char *error_text));
COMPAT_FN_DECL(int MTIF_THR_GetPriorityMapNativeBasic,
	(MTIF_THR_HANDLE *thr_handle_ptr, unsigned int allocated_count,
	MTIF_THR_PRIORITY_MAP *allocated_list, unsigned int *out_count,
	MTIF_THR_PRIORITY_MAP **out_list, char *error_text));
	/*	*****************************************************************	*/

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data type access functions provided in library 'mtif.{a|lib}' . . .		*/
/*	***********************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Basic mutex data access function prototypes . . .
		*****************************************************************	*/
		/*
			Signed int data type function prototypes.
		*/
COMPAT_FN_DECL(int MTIF_MTX_InitDataSInt,
	(MTIF_MTX_DATA_SINT *data_ptr, MTIF_MTX_FLAG flags, const char *name,
	int new_value, char *error_text));
COMPAT_FN_DECL(int MTIF_MTX_DestroyDataSInt,
	(MTIF_MTX_DATA_SINT *data_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_MTX_GetDataSInt,
	(MTIF_MTX_DATA_SINT *data_ptr));
COMPAT_FN_DECL(int MTIF_MTX_GetDataSIntBasic,
	(MTIF_MTX_DATA_SINT *data_ptr, int *old_value_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_MTX_SetDataSInt,
	(MTIF_MTX_DATA_SINT *data_ptr, int new_value));
COMPAT_FN_DECL(int MTIF_MTX_SetDataSIntBasic,
	(MTIF_MTX_DATA_SINT *data_ptr, int new_value, int *old_value_ptr,
	char *error_text));
		/*
			Unsigned int data type function prototypes.
		*/
COMPAT_FN_DECL(int MTIF_MTX_InitDataUInt,
	(MTIF_MTX_DATA_UINT *data_ptr, MTIF_MTX_FLAG flags, const char *name,
	unsigned int new_value, char *error_text));
COMPAT_FN_DECL(int MTIF_MTX_DestroyDataUInt,
	(MTIF_MTX_DATA_UINT *data_ptr, char *error_text));
COMPAT_FN_DECL(unsigned int MTIF_MTX_GetDataUInt,
	(MTIF_MTX_DATA_UINT *data_ptr));
COMPAT_FN_DECL(int MTIF_MTX_GetDataUIntBasic,
	(MTIF_MTX_DATA_UINT *data_ptr, unsigned int *old_value_ptr,
	char *error_text));
COMPAT_FN_DECL(unsigned int MTIF_MTX_SetDataUInt,
	(MTIF_MTX_DATA_UINT *data_ptr, unsigned int new_value));
COMPAT_FN_DECL(int MTIF_MTX_SetDataUIntBasic,
	(MTIF_MTX_DATA_UINT *data_ptr, unsigned int new_value,
	unsigned int *old_value_ptr, char *error_text));
		/*
			Signed long data type function prototypes.
		*/
COMPAT_FN_DECL(int MTIF_MTX_InitDataSLong,
	(MTIF_MTX_DATA_SLONG *data_ptr, MTIF_MTX_FLAG flags, const char *name,
	long new_value, char *error_text));
COMPAT_FN_DECL(int MTIF_MTX_DestroyDataSLong,
	(MTIF_MTX_DATA_SLONG *data_ptr, char *error_text));
COMPAT_FN_DECL(long MTIF_MTX_GetDataSLong,
	(MTIF_MTX_DATA_SLONG *data_ptr));
COMPAT_FN_DECL(int MTIF_MTX_GetDataSLongBasic,
	(MTIF_MTX_DATA_SLONG *data_ptr, long *old_value_ptr, char *error_text));
COMPAT_FN_DECL(long MTIF_MTX_SetDataSLong,
	(MTIF_MTX_DATA_SLONG *data_ptr, long new_value));
COMPAT_FN_DECL(int MTIF_MTX_SetDataSLongBasic,
	(MTIF_MTX_DATA_SLONG *data_ptr, long new_value, long *old_value_ptr,
	char *error_text));
		/*
			Unsigned long data type function prototypes.
		*/
COMPAT_FN_DECL(int MTIF_MTX_InitDataULong,
	(MTIF_MTX_DATA_ULONG *data_ptr, MTIF_MTX_FLAG flags, const char *name,
	unsigned long new_value, char *error_text));
COMPAT_FN_DECL(int MTIF_MTX_DestroyDataULong,
	(MTIF_MTX_DATA_ULONG *data_ptr, char *error_text));
COMPAT_FN_DECL(unsigned long MTIF_MTX_GetDataULong,
	(MTIF_MTX_DATA_ULONG *data_ptr));
COMPAT_FN_DECL(int MTIF_MTX_GetDataULongBasic,
	(MTIF_MTX_DATA_ULONG *data_ptr, unsigned long *old_value_ptr,
	char *error_text));
COMPAT_FN_DECL(unsigned long MTIF_MTX_SetDataULong,
	(MTIF_MTX_DATA_ULONG *data_ptr, unsigned long new_value));
COMPAT_FN_DECL(int MTIF_MTX_SetDataULongBasic,
	(MTIF_MTX_DATA_ULONG *data_ptr, unsigned long new_value,
	unsigned long *old_value_ptr, char *error_text));
		/*
			Double data type function prototypes.
		*/
COMPAT_FN_DECL(int MTIF_MTX_InitDataDouble,
	(MTIF_MTX_DATA_DOUBLE *data_ptr, MTIF_MTX_FLAG flags, const char *name,
	double new_value, char *error_text));
COMPAT_FN_DECL(int MTIF_MTX_DestroyDataDouble,
	(MTIF_MTX_DATA_DOUBLE *data_ptr, char *error_text));
COMPAT_FN_DECL(double MTIF_MTX_GetDataDouble,
	(MTIF_MTX_DATA_DOUBLE *data_ptr));
COMPAT_FN_DECL(int MTIF_MTX_GetDataDoubleBasic,
	(MTIF_MTX_DATA_DOUBLE *data_ptr, double *old_value_ptr, char *error_text));
COMPAT_FN_DECL(double MTIF_MTX_SetDataDouble,
	(MTIF_MTX_DATA_DOUBLE *data_ptr, double new_value));
COMPAT_FN_DECL(int MTIF_MTX_SetDataDoubleBasic,
	(MTIF_MTX_DATA_DOUBLE *data_ptr, double new_value, double *old_value_ptr,
	char *error_text));
		/*
			Basic data type function prototypes.
		*/
COMPAT_FN_DECL(int MTIF_MTX_InitDataBasic,
	(MTIF_MTX_HANDLE *lock_ptr, MTIF_MTX_FLAG flags, const char *name,
	void *value_ptr, unsigned int value_length, const void *new_data_ptr,
	char *error_text));
COMPAT_FN_DECL(int MTIF_MTX_DestroyDataBasic,
	(MTIF_MTX_HANDLE *lock_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_MTX_GetDataBasic,
	(MTIF_MTX_HANDLE *lock_ptr, void *value_ptr, unsigned int value_length,
	void *old_value_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_MTX_SetDataBasic,
	(MTIF_MTX_HANDLE *lock_ptr, void *value_ptr, unsigned int value_length,
	const void *new_value_ptr, void *old_value_ptr, char *error_text));
		/*
			Some spin lock access function prototypes.
		*/
COMPAT_FN_DECL(int MTIF_MTX_SpinOnDataSIntUSecs,
	(MTIF_MTX_DATA_SINT *data_ptr, int test_value, unsigned int spin_count,
	unsigned long spin_usecs));
COMPAT_FN_DECL(int MTIF_MTX_SpinOnNotDataSIntUSecs,
	(MTIF_MTX_DATA_SINT *data_ptr, int test_value, unsigned int spin_count,
	unsigned long spin_usecs));
COMPAT_FN_DECL(int MTIF_MTX_SpinOnDataUSecsBasic, (MTIF_MTX_HANDLE *lock_ptr,
	const void *value_ptr, unsigned int value_length, const void *test_value_ptr,
	void *old_value_ptr, unsigned int spin_count, unsigned long spin_usecs,
	int not_flag, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Recursive mutex data access function prototypes . . .
		*****************************************************************	*/
		/*
			Signed int data type function prototypes.
		*/
COMPAT_FN_DECL(int MTIF_MTR_InitDataSInt,
	(MTIF_MTR_DATA_SINT *data_ptr, MTIF_MTR_FLAG flags, const char *name,
	int new_value, char *error_text));
COMPAT_FN_DECL(int MTIF_MTR_DestroyDataSInt,
	(MTIF_MTR_DATA_SINT *data_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_MTR_GetDataSInt,
	(MTIF_MTR_DATA_SINT *data_ptr));
COMPAT_FN_DECL(int MTIF_MTR_GetDataSIntBasic,
	(MTIF_MTR_DATA_SINT *data_ptr, int *old_value_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_MTR_SetDataSInt,
	(MTIF_MTR_DATA_SINT *data_ptr, int new_value));
COMPAT_FN_DECL(int MTIF_MTR_SetDataSIntBasic,
	(MTIF_MTR_DATA_SINT *data_ptr, int new_value, int *old_value_ptr,
	char *error_text));
		/*
			Unsigned int data type function prototypes.
		*/
COMPAT_FN_DECL(int MTIF_MTR_InitDataUInt,
	(MTIF_MTR_DATA_UINT *data_ptr, MTIF_MTR_FLAG flags, const char *name,
	unsigned int new_value, char *error_text));
COMPAT_FN_DECL(int MTIF_MTR_DestroyDataUInt,
	(MTIF_MTR_DATA_UINT *data_ptr, char *error_text));
COMPAT_FN_DECL(unsigned int MTIF_MTR_GetDataUInt,
	(MTIF_MTR_DATA_UINT *data_ptr));
COMPAT_FN_DECL(int MTIF_MTR_GetDataUIntBasic,
	(MTIF_MTR_DATA_UINT *data_ptr, unsigned int *old_value_ptr,
	char *error_text));
COMPAT_FN_DECL(unsigned int MTIF_MTR_SetDataUInt,
	(MTIF_MTR_DATA_UINT *data_ptr, unsigned int new_value));
COMPAT_FN_DECL(int MTIF_MTR_SetDataUIntBasic,
	(MTIF_MTR_DATA_UINT *data_ptr, unsigned int new_value,
	unsigned int *old_value_ptr, char *error_text));
		/*
			Signed long data type function prototypes.
		*/
COMPAT_FN_DECL(int MTIF_MTR_InitDataSLong,
	(MTIF_MTR_DATA_SLONG *data_ptr, MTIF_MTR_FLAG flags, const char *name,
	long new_value, char *error_text));
COMPAT_FN_DECL(int MTIF_MTR_DestroyDataSLong,
	(MTIF_MTR_DATA_SLONG *data_ptr, char *error_text));
COMPAT_FN_DECL(long MTIF_MTR_GetDataSLong,
	(MTIF_MTR_DATA_SLONG *data_ptr));
COMPAT_FN_DECL(int MTIF_MTR_GetDataSLongBasic,
	(MTIF_MTR_DATA_SLONG *data_ptr, long *old_value_ptr, char *error_text));
COMPAT_FN_DECL(long MTIF_MTR_SetDataSLong,
	(MTIF_MTR_DATA_SLONG *data_ptr, long new_value));
COMPAT_FN_DECL(int MTIF_MTR_SetDataSLongBasic,
	(MTIF_MTR_DATA_SLONG *data_ptr, long new_value, long *old_value_ptr,
	char *error_text));
		/*
			Unsigned long data type function prototypes.
		*/
COMPAT_FN_DECL(int MTIF_MTR_InitDataULong,
	(MTIF_MTR_DATA_ULONG *data_ptr, MTIF_MTR_FLAG flags, const char *name,
	unsigned long new_value, char *error_text));
COMPAT_FN_DECL(int MTIF_MTR_DestroyDataULong,
	(MTIF_MTR_DATA_ULONG *data_ptr, char *error_text));
COMPAT_FN_DECL(unsigned long MTIF_MTR_GetDataULong,
	(MTIF_MTR_DATA_ULONG *data_ptr));
COMPAT_FN_DECL(int MTIF_MTR_GetDataULongBasic,
	(MTIF_MTR_DATA_ULONG *data_ptr, unsigned long *old_value_ptr,
	char *error_text));
COMPAT_FN_DECL(unsigned long MTIF_MTR_SetDataULong,
	(MTIF_MTR_DATA_ULONG *data_ptr, unsigned long new_value));
COMPAT_FN_DECL(int MTIF_MTR_SetDataULongBasic,
	(MTIF_MTR_DATA_ULONG *data_ptr, unsigned long new_value,
	unsigned long *old_value_ptr, char *error_text));
		/*
			Double data type function prototypes.
		*/
COMPAT_FN_DECL(int MTIF_MTR_InitDataDouble,
	(MTIF_MTR_DATA_DOUBLE *data_ptr, MTIF_MTR_FLAG flags, const char *name,
	double new_value, char *error_text));
COMPAT_FN_DECL(int MTIF_MTR_DestroyDataDouble,
	(MTIF_MTR_DATA_DOUBLE *data_ptr, char *error_text));
COMPAT_FN_DECL(double MTIF_MTR_GetDataDouble,
	(MTIF_MTR_DATA_DOUBLE *data_ptr));
COMPAT_FN_DECL(int MTIF_MTR_GetDataDoubleBasic,
	(MTIF_MTR_DATA_DOUBLE *data_ptr, double *old_value_ptr, char *error_text));
COMPAT_FN_DECL(double MTIF_MTR_SetDataDouble,
	(MTIF_MTR_DATA_DOUBLE *data_ptr, double new_value));
COMPAT_FN_DECL(int MTIF_MTR_SetDataDoubleBasic,
	(MTIF_MTR_DATA_DOUBLE *data_ptr, double new_value, double *old_value_ptr,
	char *error_text));
		/*
			Basic data type function prototypes.
		*/
COMPAT_FN_DECL(int MTIF_MTR_InitDataBasic,
	(MTIF_MTR_HANDLE *lock_ptr, MTIF_MTR_FLAG flags, const char *name,
	void *value_ptr, unsigned int value_length, const void *new_data_ptr,
	char *error_text));
COMPAT_FN_DECL(int MTIF_MTR_DestroyDataBasic,
	(MTIF_MTR_HANDLE *lock_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_MTR_GetDataBasic,
	(MTIF_MTR_HANDLE *lock_ptr, void *value_ptr, unsigned int value_length,
	void *old_value_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_MTR_SetDataBasic,
	(MTIF_MTR_HANDLE *lock_ptr, void *value_ptr, unsigned int value_length,
	const void *new_value_ptr, void *old_value_ptr, char *error_text));
		/*
			Some spin lock access function prototypes.
		*/
COMPAT_FN_DECL(int MTIF_MTR_SpinOnDataSIntUSecs,
	(MTIF_MTR_DATA_SINT *data_ptr, int test_value, unsigned int spin_count,
	unsigned long spin_usecs));
COMPAT_FN_DECL(int MTIF_MTR_SpinOnNotDataSIntUSecs,
	(MTIF_MTR_DATA_SINT *data_ptr, int test_value, unsigned int spin_count,
	unsigned long spin_usecs));
COMPAT_FN_DECL(int MTIF_MTR_SpinOnDataUSecsBasic, (MTIF_MTR_HANDLE *lock_ptr,
	const void *value_ptr, unsigned int value_length, const void *test_value_ptr,
	void *old_value_ptr, unsigned int spin_count, unsigned long spin_usecs,
	int not_flag, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Reader/writer lock data access function prototypes . . .
		*****************************************************************	*/
		/*
			Signed int data type function prototypes.
		*/
COMPAT_FN_DECL(int MTIF_RWL_InitDataSInt,
	(MTIF_RWL_DATA_SINT *data_ptr, MTIF_RWL_FLAG flags, const char *name,
	int new_value, char *error_text));
COMPAT_FN_DECL(int MTIF_RWL_DestroyDataSInt,
	(MTIF_RWL_DATA_SINT *data_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_RWL_GetDataSInt,
	(MTIF_RWL_DATA_SINT *data_ptr));
COMPAT_FN_DECL(int MTIF_RWL_GetDataSIntBasic,
	(MTIF_RWL_DATA_SINT *data_ptr, int *old_value_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_RWL_SetDataSInt,
	(MTIF_RWL_DATA_SINT *data_ptr, int new_value));
COMPAT_FN_DECL(int MTIF_RWL_SetDataSIntBasic,
	(MTIF_RWL_DATA_SINT *data_ptr, int new_value, int *old_value_ptr,
	char *error_text));
		/*
			Unsigned int data type function prototypes.
		*/
COMPAT_FN_DECL(int MTIF_RWL_InitDataUInt,
	(MTIF_RWL_DATA_UINT *data_ptr, MTIF_RWL_FLAG flags, const char *name,
	unsigned int new_value, char *error_text));
COMPAT_FN_DECL(int MTIF_RWL_DestroyDataUInt,
	(MTIF_RWL_DATA_UINT *data_ptr, char *error_text));
COMPAT_FN_DECL(unsigned int MTIF_RWL_GetDataUInt,
	(MTIF_RWL_DATA_UINT *data_ptr));
COMPAT_FN_DECL(int MTIF_RWL_GetDataUIntBasic,
	(MTIF_RWL_DATA_UINT *data_ptr, unsigned int *old_value_ptr,
	char *error_text));
COMPAT_FN_DECL(unsigned int MTIF_RWL_SetDataUInt,
	(MTIF_RWL_DATA_UINT *data_ptr, unsigned int new_value));
COMPAT_FN_DECL(int MTIF_RWL_SetDataUIntBasic,
	(MTIF_RWL_DATA_UINT *data_ptr, unsigned int new_value,
	unsigned int *old_value_ptr, char *error_text));
		/*
			Signed long data type function prototypes.
		*/
COMPAT_FN_DECL(int MTIF_RWL_InitDataSLong,
	(MTIF_RWL_DATA_SLONG *data_ptr, MTIF_RWL_FLAG flags, const char *name,
	long new_value, char *error_text));
COMPAT_FN_DECL(int MTIF_RWL_DestroyDataSLong,
	(MTIF_RWL_DATA_SLONG *data_ptr, char *error_text));
COMPAT_FN_DECL(long MTIF_RWL_GetDataSLong,
	(MTIF_RWL_DATA_SLONG *data_ptr));
COMPAT_FN_DECL(int MTIF_RWL_GetDataSLongBasic,
	(MTIF_RWL_DATA_SLONG *data_ptr, long *old_value_ptr, char *error_text));
COMPAT_FN_DECL(long MTIF_RWL_SetDataSLong,
	(MTIF_RWL_DATA_SLONG *data_ptr, long new_value));
COMPAT_FN_DECL(int MTIF_RWL_SetDataSLongBasic,
	(MTIF_RWL_DATA_SLONG *data_ptr, long new_value, long *old_value_ptr,
	char *error_text));
		/*
			Unsigned long data type function prototypes.
		*/
COMPAT_FN_DECL(int MTIF_RWL_InitDataULong,
	(MTIF_RWL_DATA_ULONG *data_ptr, MTIF_RWL_FLAG flags, const char *name,
	unsigned long new_value, char *error_text));
COMPAT_FN_DECL(int MTIF_RWL_DestroyDataULong,
	(MTIF_RWL_DATA_ULONG *data_ptr, char *error_text));
COMPAT_FN_DECL(unsigned long MTIF_RWL_GetDataULong,
	(MTIF_RWL_DATA_ULONG *data_ptr));
COMPAT_FN_DECL(int MTIF_RWL_GetDataULongBasic,
	(MTIF_RWL_DATA_ULONG *data_ptr, unsigned long *old_value_ptr,
	char *error_text));
COMPAT_FN_DECL(unsigned long MTIF_RWL_SetDataULong,
	(MTIF_RWL_DATA_ULONG *data_ptr, unsigned long new_value));
COMPAT_FN_DECL(int MTIF_RWL_SetDataULongBasic,
	(MTIF_RWL_DATA_ULONG *data_ptr, unsigned long new_value,
	unsigned long *old_value_ptr, char *error_text));
		/*
			Double data type function prototypes.
		*/
COMPAT_FN_DECL(int MTIF_RWL_InitDataDouble,
	(MTIF_RWL_DATA_DOUBLE *data_ptr, MTIF_RWL_FLAG flags, const char *name,
	double new_value, char *error_text));
COMPAT_FN_DECL(int MTIF_RWL_DestroyDataDouble,
	(MTIF_RWL_DATA_DOUBLE *data_ptr, char *error_text));
COMPAT_FN_DECL(double MTIF_RWL_GetDataDouble,
	(MTIF_RWL_DATA_DOUBLE *data_ptr));
COMPAT_FN_DECL(int MTIF_RWL_GetDataDoubleBasic,
	(MTIF_RWL_DATA_DOUBLE *data_ptr, double *old_value_ptr, char *error_text));
COMPAT_FN_DECL(double MTIF_RWL_SetDataDouble,
	(MTIF_RWL_DATA_DOUBLE *data_ptr, double new_value));
COMPAT_FN_DECL(int MTIF_RWL_SetDataDoubleBasic,
	(MTIF_RWL_DATA_DOUBLE *data_ptr, double new_value, double *old_value_ptr,
	char *error_text));
		/*
			Basic data type function prototypes.
		*/
COMPAT_FN_DECL(int MTIF_RWL_InitDataBasic,
	(MTIF_RWL_HANDLE *lock_ptr, MTIF_RWL_FLAG flags, const char *name,
	void *value_ptr, unsigned int value_length, const void *new_data_ptr,
	char *error_text));
COMPAT_FN_DECL(int MTIF_RWL_DestroyDataBasic,
	(MTIF_RWL_HANDLE *lock_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_RWL_GetDataBasic,
	(MTIF_RWL_HANDLE *lock_ptr, void *value_ptr, unsigned int value_length,
	void *old_value_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_RWL_SetDataBasic,
	(MTIF_RWL_HANDLE *lock_ptr, void *value_ptr, unsigned int value_length,
	const void *new_value_ptr, void *old_value_ptr, char *error_text));
		/*
			Some spin lock access function prototypes.
		*/
COMPAT_FN_DECL(int MTIF_RWL_SpinOnDataSIntUSecs,
	(MTIF_RWL_DATA_SINT *data_ptr, int test_value, unsigned int spin_count,
	unsigned long spin_usecs));
COMPAT_FN_DECL(int MTIF_RWL_SpinOnNotDataSIntUSecs,
	(MTIF_RWL_DATA_SINT *data_ptr, int test_value, unsigned int spin_count,
	unsigned long spin_usecs));
COMPAT_FN_DECL(int MTIF_RWL_SpinOnDataUSecsBasic, (MTIF_RWL_HANDLE *lock_ptr,
	const void *value_ptr, unsigned int value_length, const void *test_value_ptr,
	void *old_value_ptr, unsigned int spin_count, unsigned long spin_usecs,
	int not_flag, char *error_text));
	/*	*****************************************************************	*/

/*	***********************************************************************	*/

#endif /* #ifndef h__MTIF_H__h */

