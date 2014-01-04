/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MREGION Memory-mapped Interface Library Include File							*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the Memory-mapped Region Interface
								Library (MREGION).

	Revision History	:	1992-03-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__MREGION_H__h

#define h__MREGION_H__h						1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include <mmi.h>

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   BASE NAME   :  MREGION Truth Codes

   NAME        :  MREGION Truth Codes

	DESCRIPTION :  Manifest constants used within MREGION to specify the truth
						or falsity of expressions.

						(.) ''MRG_TRUE''

						(.) ''MRG_FALSE''

   NOTES       :  The manifest constant ''MRG_TRUE'' should be defined as
						a non-zero value. Conversely, the manifest constant
						''MRG_FALSE'' should be defined as zero (''0'').

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2014 Michael L. Brock

   OUTPUT INDEX:  MRG_TRUE
						MRG_FALSE
						MREGION Truth Codes:MRG_TRUE
						MREGION Truth Codes:MRG_FALSE
						MREGION Manifest Constants:MRG_TRUE
						MREGION Manifest Constants:MRG_FALSE
						MREGION Defines:MRG_TRUE
						MREGION Defines:MRG_FALSE
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:  MREGION Truth Codes
						MREGION Truth Code
						MREGION truth codes
						MREGION truth code
						MRG_TRUE
						MRG_FALSE

   PUBLISH NAME:	MREGION Truth Codes
						MRG_TRUE
						MRG_FALSE

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define MRG_TRUE							1
#define MRG_FALSE							0
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   BASE NAME   :	MREGION Return Codes

   NAME        :  MREGION Return Codes

   DESCRIPTION :  The MREGION return codes have the following meanings:

						(.) ''MRG_SUCCESS'' means that the function invoked
						completed without error. ''MRG_SUCCESS'' is guaranteed to
						be equal to zero (''0'').

						(.) ''MRG_FAILURE'' indicates that the function invoked
						encountered a general operation failure. This is the
						'catch-all' error code for those errors which do not fit
						into category of one the other MREGION error codes.

						(.) ''MRG_BAD_ARGS_FAILURE'' indicates that the
						arguments passed to a function invoked were invalid.

						(.) ''MRG_MEMORY_FAILURE'' indicates that the memory
						required for operation of the function invoked could not be
						allocated.

						(.) ''MRG_SYSTEM_FAILURE'' indicates that the function
						invoked encountered a failure of a standard library
						function or a system call.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2014 Michael L. Brock

   OUTPUT INDEX:  MRG_SUCCESS
						MRG_FAILURE
						MRG_BAD_ARGS_FAILURE
						MRG_MEMORY_FAILURE
						MRG_SYSTEM_FAILURE
						MREGION Return Codes:MRG_SUCCESS
						MREGION Return Codes:MRG_FAILURE
						MREGION Return Codes:MRG_BAD_ARGS_FAILURE
						MREGION Return Codes:MRG_MEMORY_FAILURE
						MREGION Return Codes:MRG_SYSTEM_FAILURE
						MREGION Manifest Constants:MRG_SUCCESS
						MREGION Manifest Constants:MRG_FAILURE
						MREGION Manifest Constants:MRG_BAD_ARGS_FAILURE
						MREGION Manifest Constants:MRG_MEMORY_FAILURE
						MREGION Manifest Constants:MRG_SYSTEM_FAILURE
						MREGION Defines:MRG_SUCCESS
						MREGION Defines:MRG_FAILURE
						MREGION Defines:MRG_BAD_ARGS_FAILURE
						MREGION Defines:MRG_MEMORY_FAILURE
						MREGION Defines:MRG_SYSTEM_FAILURE
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:  MRG_SUCCESS
						MRG_FAILURE
						MRG_BAD_ARGS_FAILURE
						MRG_MEMORY_FAILURE
						MRG_SYSTEM_FAILURE
						MREGION Return Codes
						MREGION Return Code
						MREGION return codes
						MREGION return code
						MREGION Status Codes
						MREGION Status Code
						MREGION status codes
						MREGION status code
						MREGION Error Codes
						MREGION Error Code
						MREGION error codes
						MREGION error code

   PUBLISH NAME:	MREGION Return Codes
						MREGION return codes
						MRG_SUCCESS
						MRG_FAILURE
						MRG_BAD_ARGS_FAILURE
						MRG_MEMORY_FAILURE
						MRG_SYSTEM_FAILURE

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define MRG_SUCCESS							 0
#define MRG_FAILURE							-1
#define MRG_BAD_ARGS_FAILURE				-2
#define MRG_MEMORY_FAILURE					-3
#define MRG_SYSTEM_FAILURE					-4
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :  MRG_MAX_ERROR_TEXT

   DESCRIPTION :  The manifest constant ''MRG_MAX_ERROR_TEXT'' defines
						the minimum amount of storage which should be allocated to
						hold an error message returned by a MREGION function.

   CAVEATS     :  MREGION error messages can be quite lengthy. Therefore,
						attempting to save space by allocating less than
						''MRG_MAX_ERROR_TEXT'' bytes to error message buffers
						passed to MREGION functions can lead to overwriting of the
						heap or the stack.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2014 Michael L. Brock

   OUTPUT INDEX:  MRG_MAX_ERROR_TEXT
						MREGION Manifest Constants:MRG_MAX_ERROR_TEXT
						MREGION Defines:MRG_MAX_ERROR_TEXT
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	MRG_MAX_ERROR_TEXT

   PUBLISH NAME:	MRG_MAX_ERROR_TEXT

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define MRG_MAX_ERROR_TEXT					1024
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define MRG_ARRAY_ALLOC_GRAN				100
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef unsigned long MRG_OPEN_MODE;
typedef int           MRG_OPEN_MODE_OS;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define MRG_OPEN_MODE_READ					((MRG_OPEN_MODE) 0x01)
#define MRG_OPEN_MODE_WRITE				((MRG_OPEN_MODE) 0x02)
#define MRG_OPEN_MODE_APPEND				((MRG_OPEN_MODE) 0x04)
#define MRG_OPEN_MODE_CREATE				((MRG_OPEN_MODE) 0x08)
#define MRG_OPEN_MODE_TRUNCATE			((MRG_OPEN_MODE) 0x10)
#define MRG_OPEN_MODE_RW					\
	(MRG_OPEN_MODE_READ | MRG_OPEN_MODE_WRITE)
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define MRG_FOPEN_MODE_A					\
	(MRG_OPEN_MODE_WRITE | MRG_OPEN_MODE_APPEND | MRG_OPEN_MODE_CREATE)
#define MRG_FOPEN_MODE_AP					\
	(MRG_OPEN_MODE_RW    | MRG_OPEN_MODE_APPEND | MRG_OPEN_MODE_CREATE)
#define MRG_FOPEN_MODE_R					MRG_OPEN_MODE_READ
#define MRG_FOPEN_MODE_RP					MRG_OPEN_MODE_RW
#define MRG_FOPEN_MODE_W					\
	(MRG_OPEN_MODE_WRITE | MRG_OPEN_MODE_CREATE | MRG_OPEN_MODE_TRUNCATE)
#define MRG_FOPEN_MODE_WP					\
	(MRG_OPEN_MODE_RW    | MRG_OPEN_MODE_CREATE | MRG_OPEN_MODE_TRUNCATE)
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef struct {
	char             *fopen_mode;
	MRG_OPEN_MODE     open_mode;
	MRG_OPEN_MODE_OS  os_open_mode;
	MMI_FLAG          mmap_flags;
	MMI_FLAG          prot_flags;
} MRG_MODE_ITEM;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef unsigned long MRG_SIGNATURE;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef struct {
	MRG_SIGNATURE       signature;
	MMI_ADDRESS         base_address;
	MMI_ADDRESS         mmap_ptr;
	MMI_LENGTH          mmap_length;
	MMI_OFFSET          mmap_offset;
	MMI_FLAG            mmap_flags;
	MMI_FLAG            prot_flags;
	MMI_MMAP_HANDLE_OS  os_mmap_handle;
	MMI_OFFSET          current_offset;	/* For API programmers; not used. */
	struct MRG_FIL     *parent_ptr;
} MRG_REG;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef struct MRG_FIL {
	MRG_SIGNATURE     signature;
	char             *file_name;
	MRG_OPEN_MODE     open_mode;
	MRG_OPEN_MODE_OS  os_open_mode;
	MMI_FLAG          mmap_flags;
	MMI_FLAG          prot_flags;
	MMI_FILE_HANDLE   file_handle;
	MMI_LENGTH        file_length;
	unsigned int      allocated_count;
	unsigned int      region_count;
	MRG_REG         **region_list;
	struct MRG_CTL   *parent_ptr;
} MRG_FIL;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef struct MRG_CTL {
	MRG_SIGNATURE   signature;
	unsigned int    allocated_count;
	unsigned int    file_count;
	MRG_FIL       **file_list;
} MRG_CTL;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define MRG_GET_REG_BASE_ADDR				((ptr)->base_address)
#define MRG_GET_REG_MMAP_PTR				((ptr)->mmap_ptr)
#define MRG_GET_REG_MMAP_LENGTH			((ptr)->mmap_length)
#define MRG_GET_REG_MMAP_OFFSET			((ptr)->mmap_offset)
#define MRG_GET_REG_MMAP_FLAGS			((ptr)->mmap_flags)
#define MRG_GET_REG_PROT_FLAGS			((ptr)->prot_flags)
#define MRG_GET_REG_OS_MMAP_HANDLE		((ptr)->os_mmap_handle)
#define MRG_GET_REG_CURR_OFFSET			((ptr)->current_offset)
#define MRG_GET_REG_ACTUAL_OFFSET		\
	(MRG_GET_REG_MMAP_OFFSET(ptr) + MRG_GET_REG_CURR_OFFSET(ptr))
#define MRG_GET_REG_MMAP_PTRC				((char *) ((ptr)->mmap_ptr))
#define MRG_GET_REG_OFFSET_PTRC			\
	(MRG_GET_REG_MMAP_PTRC(ptr) + MRG_GET_REG_CURR_OFFSET(ptr))
#define MRG_GET_REG_OFFSET_PTR			\
	((MMI_ADDRESS) MRG_GET_REG_OFFSET_PTRC(ptr))
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define MRG_GET_FIL_FILE_NAME				((ptr)->file_name)
#define MRG_GET_FIL_OPEN_MODE				((ptr)->open_mode)
#define MRG_GET_FIL_OS_OPEN_MODE			((ptr)->os_open_mode)
#define MRG_GET_FIL_MMAP_FLAGS			((ptr)->mmap_flags)
#define MRG_GET_FIL_PROT_FLAGS			((ptr)->prot_flags)
#define MRG_GET_FIL_FILE_HANDLE			((ptr)->file_handle)
#define MRG_GET_FIL_FILE_LENGTH			((ptr)->file_length)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Function prototypes for the MREGION functions . . .							*/
/*	***********************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		MREGION core function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int MRG_MapReg,
	(MMI_FILE_HANDLE file_handle, MMI_ADDRESS base_address,
	MMI_LENGTH mmap_length, MMI_OFFSET mmap_offset, MMI_FLAG mmap_flags,
	MMI_FLAG prot_flags, MRG_REG **reg_ptr, char *error_text));
COMPAT_FN_DECL(int MRG_MapRegToFil,
	(MRG_FIL *fil_ptr, MMI_ADDRESS base_address, MMI_LENGTH mmap_length,
	MMI_OFFSET mmap_offset, MMI_FLAG mmap_flags, MMI_FLAG prot_flags,
	char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		MREGION data type management function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void MRG_CloseCtl, (MRG_CTL *ctl_ptr));
COMPAT_FN_DECL(void MRG_CloseFil, (MRG_FIL *fil_ptr));
COMPAT_FN_DECL(void MRG_CloseReg, (MRG_REG *reg_ptr));

COMPAT_FN_DECL(void MRG_FreeCtl, (MRG_CTL *ctl_ptr));
COMPAT_FN_DECL(void MRG_FreeFil, (MRG_FIL *fil_ptr));
COMPAT_FN_DECL(void MRG_FreeReg, (MRG_REG *reg_ptr));

COMPAT_FN_DECL(void MRG_InitCtl, (MRG_CTL *ctl_ptr));
COMPAT_FN_DECL(void MRG_InitFil, (MRG_FIL *fil_ptr));
COMPAT_FN_DECL(void MRG_InitReg, (MRG_REG *reg_ptr));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Function prototypes for file open functions . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int MRG_FOpenFile,
	(const char *file_name, const char *fopen_mode, MRG_FIL **fil_ptr,
	char *error_text));
COMPAT_FN_DECL(int MRG_FOpenFileWithMap,
	(const char *file_name, const char *fopen_mode, MRG_FIL **fil_ptr,
	char *error_text));
COMPAT_FN_DECL(int MRG_OpenFile,
	(const char *file_name, MRG_OPEN_MODE open_mode, MRG_FIL **fil_ptr,
	char *error_text));
COMPAT_FN_DECL(int MRG_OpenFileWithMap,
	(const char *file_name, MRG_OPEN_MODE open_mode, MRG_FIL **fil_ptr,
	char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Function prototypes for file mode management functions . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int MRG_CopyModeList,
	(unsigned int *mode_count, MRG_MODE_ITEM **mode_list, char *error_text));
COMPAT_FN_DECL(int MRG_GetFlagsForFOpen,
	(const char *fopen_mode, MRG_OPEN_MODE *open_mode,
	MRG_OPEN_MODE_OS *os_open_mode, MMI_FLAG *mmap_flags, MMI_FLAG *prot_flags,
	char *error_text));
COMPAT_FN_DECL(int MRG_GetFlagsForOpen,
	(MRG_OPEN_MODE open_mode, MRG_OPEN_MODE_OS *os_open_mode,
	MMI_FLAG *mmap_flags, MMI_FLAG *prot_flags, char *error_text));
COMPAT_FN_DECL(int MRG_GetFlagsForOpenOS,
	(MRG_OPEN_MODE_OS os_open_mode, MRG_OPEN_MODE *open_mode,
	MMI_FLAG *mmap_flags, MMI_FLAG *prot_flags, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Function prototypes for memory allocation functions . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int MRG_AllocateArray,
	(const char *item_name, const char *element_name,
	unsigned int new_alloc_count, unsigned int *allocated_count,
	void ***alloc_list, char *error_text));
COMPAT_FN_DECL(int MRG_AllocateCtl,
	(MRG_CTL **ctl_ptr, char *error_text));
COMPAT_FN_DECL(int MRG_AllocateCtlArray,
	(MRG_CTL *ctl_ptr, unsigned int array_alloc_count, char *error_text));
COMPAT_FN_DECL(int MRG_AllocateFil,
	(MRG_FIL **fil_ptr, char *error_text));
COMPAT_FN_DECL(int MRG_AllocateFilArray,
	(MRG_FIL *fil_ptr, unsigned int array_alloc_count, char *error_text));
COMPAT_FN_DECL(int MRG_AllocateItem,
	(const char *item_name, unsigned int item_size, void **item_ptr,
	char *error_text));
COMPAT_FN_DECL(int MRG_AllocateReg,
	(MRG_REG **reg_ptr, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Function prototypes for structure close functions . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void MRG_CloseCtl, (MRG_CTL *ctl_ptr));
COMPAT_FN_DECL(void MRG_CloseFil, (MRG_FIL *fil_ptr));
COMPAT_FN_DECL(void MRG_CloseReg, (MRG_REG *reg_ptr));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Function prototypes for structure check functions . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int MRG_CheckCtl, (const MRG_CTL *ctl_ptr, char *error_text));
COMPAT_FN_DECL(int MRG_CheckFil, (const MRG_FIL *fil_ptr, char *error_text));
COMPAT_FN_DECL(int MRG_CheckReg, (const MRG_REG *reg_ptr, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Function prototypes for miscellaneous supporting functions . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int MRG_GetFileSize, (MRG_FIL *fil_ptr, char *error_text));
COMPAT_FN_DECL(char *MRG_GetVersionString, (char *version_string));
	/*	*****************************************************************	*/

/*	***********************************************************************	*/

#endif /* #ifndef h__MREGION_H__h */

