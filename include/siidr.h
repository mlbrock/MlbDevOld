/* *********************************************************************** */
/* *********************************************************************** */
/*	Single Index Internal Data Repository Library Include File					*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the Single Index Internal
								Data Repository (SIIDR) Library.

	Revision History	:	1996-04-10 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

#ifndef h__SIIDR_H__h

#define h__SIIDR_H__h					1

/* *********************************************************************** */
/* *********************************************************************** */
/*		Include necessary header files . . .											*/
/* *********************************************************************** */

#include <stddef.h>

#include <sdtif.h>

#include <mbcompat.h>

/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   BASE NAME   :  SIIDR Truth Codes

   NAME        :  SIIDR Truth Codes

   DESCRIPTION :  Manifest constants used within SIIDR to specify the truth
						or falsity of expressions.

						(.) ''SIIDR_TRUE''

						(.) ''SIIDR_FALSE''

   NOTES       :  The manifest constant ''SIIDR_TRUE'' should be defined as
						a non-zero value. Conversely, the manifest constant
						''SIIDR_FALSE'' should be defined as zero (''0'').

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2016 Michael L. Brock

   OUTPUT INDEX:  SIIDR_TRUE
						SIIDR_FALSE
						SIIDR Truth Codes:SIIDR_TRUE
						SIIDR Truth Codes:SIIDR_FALSE
						SIIDR Manifest Constants:SIIDR_TRUE
						SIIDR Manifest Constants:SIIDR_FALSE
						SIIDR Defines:SIIDR_TRUE
						SIIDR Defines:SIIDR_FALSE
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:  SIIDR Truth Codes
						SIIDR Truth Code
						SIIDR truth codes
						SIIDR truth code
						SIIDR_TRUE
						SIIDR_FALSE

   PUBLISH NAME:	SIIDR Truth Codes
						SIIDR_TRUE
						SIIDR_FALSE

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define SIIDR_TRUE							1
#define SIIDR_FALSE							0
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   BASE NAME   :	SIIDR Return Codes

   NAME        :  SIIDR Return Codes

   DESCRIPTION :  The SIIDR return codes have the following meanings:

						(.) ''SIIDR_SUCCESS'' means that the function invoked
						completed without error. ''SIIDR_SUCCESS'' is guaranteed to
						be equal to zero (''0'').

						(.) ''SIIDR_FAILURE'' indicates that the function invoked
						encountered a general operation failure. This is the
						'catch-all' error code for those errors which do not fit
						into category of one the other SIIDR error codes.

						(.) ''SIIDR_BAD_ARGS_FAILURE'' indicates that the
						arguments passed to a function invoked were invalid.

						(.) ''SIIDR_MEMORY_FAILURE'' indicates that the memory
						required for operation of the function invoked could not be
						allocated.

						(.) ''SIIDR_SYSTEM_FAILURE'' indicates that the function
						invoked encountered a failure of a standard library
						function or a system call.

						(.) ''SIIDR_LOCK_ACQ_FAILURE'' indicates that a lock
						could not be acquired on a resource.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2016 Michael L. Brock

   OUTPUT INDEX:  SIIDR_SUCCESS
						SIIDR_FAILURE
						SIIDR_BAD_ARGS_FAILURE
						SIIDR_MEMORY_FAILURE
						SIIDR_SYSTEM_FAILURE
						SIIDR_LOCK_ACQ_FAILURE
						SIIDR Return Codes:SIIDR_SUCCESS
						SIIDR Return Codes:SIIDR_FAILURE
						SIIDR Return Codes:SIIDR_BAD_ARGS_FAILURE
						SIIDR Return Codes:SIIDR_MEMORY_FAILURE
						SIIDR Return Codes:SIIDR_SYSTEM_FAILURE
						SIIDR Return Codes:SIIDR_LOCK_ACQ_FAILURE
						SIIDR Manifest Constants:SIIDR_SUCCESS
						SIIDR Manifest Constants:SIIDR_FAILURE
						SIIDR Manifest Constants:SIIDR_BAD_ARGS_FAILURE
						SIIDR Manifest Constants:SIIDR_MEMORY_FAILURE
						SIIDR Manifest Constants:SIIDR_SYSTEM_FAILURE
						SIIDR Manifest Constants:SIIDR_LOCK_ACQ_FAILURE
						SIIDR Defines:SIIDR_SUCCESS
						SIIDR Defines:SIIDR_FAILURE
						SIIDR Defines:SIIDR_BAD_ARGS_FAILURE
						SIIDR Defines:SIIDR_MEMORY_FAILURE
						SIIDR Defines:SIIDR_SYSTEM_FAILURE
						SIIDR Defines:SIIDR_LOCK_ACQ_FAILURE
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:  SIIDR_SUCCESS
						SIIDR_FAILURE
						SIIDR_BAD_ARGS_FAILURE
						SIIDR_MEMORY_FAILURE
						SIIDR_SYSTEM_FAILURE
						SIIDR_LOCK_ACQ_FAILURE
						SIIDR Return Codes
						SIIDR Return Code
						SIIDR return codes
						SIIDR return code
						SIIDR Status Codes
						SIIDR Status Code
						SIIDR status codes
						SIIDR status code
						SIIDR Error Codes
						SIIDR Error Code
						SIIDR error codes
						SIIDR error code

   PUBLISH NAME:	SIIDR Return Codes
						SIIDR return codes
						SIIDR_SUCCESS
						SIIDR_FAILURE
						SIIDR_BAD_ARGS_FAILURE
						SIIDR_MEMORY_FAILURE
						SIIDR_SYSTEM_FAILURE
						SIIDR_LOCK_ACQ_FAILURE

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define SIIDR_SUCCESS						   0
#define SIIDR_FAILURE						  -1
#define SIIDR_BAD_ARGS_FAILURE			  -2
#define SIIDR_MEMORY_FAILURE				  -3
#define SIIDR_SYSTEM_FAILURE				  -4
#define SIIDR_LOCK_ACQ_FAILURE			  -5
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :  SIIDR_MAX_ERROR_TEXT

   DESCRIPTION :  The manifest constant ''SIIDR_MAX_ERROR_TEXT'' defines
						the minimum amount of storage which should be allocated to
						hold an error message returned by a SIIDR function.

   CAVEATS     :  SIIDR error messages can be quite lengthy. Therefore,
						attempting to save space by allocating less than
						''SIIDR_MAX_ERROR_TEXT'' bytes to error message buffers
						passed to SIIDR functions can lead to overwriting of the
						heap or the stack.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2016 Michael L. Brock

   OUTPUT INDEX:  SIIDR_MAX_ERROR_TEXT
						SIIDR Manifest Constants:SIIDR_MAX_ERROR_TEXT
						SIIDR Defines:SIIDR_MAX_ERROR_TEXT
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	SIIDR_MAX_ERROR_TEXT

   PUBLISH NAME:	SIIDR_MAX_ERROR_TEXT

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define SIIDR_MAX_ERROR_TEXT				4096
/*	***********************************************************************	*/

/*
	Provides compatibility between the external and internal versions of the
	SIIDR include files. Must be '#undef'ed at the end of this include file.
*/
/*	***********************************************************************	*/
#ifndef h__SIIDRI_H__h
typedef void *SIIDR;
#endif /* #ifndef h__SIIDRI_H__h */
/*	***********************************************************************	*/

/*
	ADF NOTE:No ADF.
*/
/*	***********************************************************************	*/
typedef enum {
	SIIDR_REL_OP_NONE	= 0,
	SIIDR_REL_OP_EQ	= 1,
	SIIDR_REL_OP_LT	= 2,
	SIIDR_REL_OP_GT	= 4,
	SIIDR_REL_OP_LE	= (SIIDR_REL_OP_EQ | SIIDR_REL_OP_LT),
	SIIDR_REL_OP_GE	= (SIIDR_REL_OP_EQ | SIIDR_REL_OP_GT),
	SIIDR_REL_OP_NE	= (SIIDR_REL_OP_LT | SIIDR_REL_OP_GT),
	SIIDR_REL_OP_MASK	= (SIIDR_REL_OP_EQ | SIIDR_REL_OP_LT | SIIDR_REL_OP_GT)
} SIIDR_REL_OP;
/*	***********************************************************************	*/

/*
	ADF NOTE:No ADF.
*/
/*	***********************************************************************	*/
#define SIIDR_STAT_ALLOC					0
#define SIIDR_STAT_DELETE					1
#define SIIDR_STAT_INSERT					2
#define SIIDR_STAT_UPDATE					3
#define SIIDR_STAT_COUNT					4
/*	***********************************************************************	*/

/*
	ADF NOTE:No ADF.
*/
/*	***********************************************************************	*/
#define SIIDR_STAT_NAME_LEN				31
/*	***********************************************************************	*/

/*
	ADF NOTE:No ADF.
*/
/*	***********************************************************************	*/
#define SIIDR_STAT_IDX_TO_NAME(stat_idx)								\
	(((stat_idx) == SIIDR_STAT_ALLOC)  ? "IDR Allocation"   :	\
	 ((stat_idx) == SIIDR_STAT_DELETE) ? "Record Deletion"  :	\
	 ((stat_idx) == SIIDR_STAT_INSERT) ? "Record Insertion" :	\
	 ((stat_idx) == SIIDR_STAT_UPDATE) ? "Record Update"    :	\
	 "*** INVALID IDR STAT ***")
/*	***********************************************************************	*/

/*
	ADF NOTE:No ADF.
*/
/*	***********************************************************************	*/
#define SIIDR_DEFAULT_ALLOC_SIZE			1000
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
typedef COMPAT_FN_TYPE(int (*SIIDR_CompareFunc),
	(const SIIDR *siidr_ptr, const void *ptr_1, const void *ptr_2,
		size_t data_length));
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
typedef COMPAT_FN_TYPE(int (*SIIDR_GetSpecFunc),
	(SIIDR *siidr_ptr, void *user_data_ptr, const void *record_ptr));
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Function prototypes for functions defined within 'siidr.a' . . .		*/
/* *********************************************************************** */

	/*	*****************************************************************
		*****************************************************************
		Core function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int  SIIDR_AllocateIDR, (SIIDR *siidr_ptr,
	unsigned int alloc_count, char *error_text));
COMPAT_FN_DECL(int  SIIDR_AllocateIDRRaw, (SIIDR *siidr_ptr,
	unsigned int alloc_count, char *error_text));
COMPAT_FN_DECL(int  SIIDR_CreateIDR, (const char *idr_name,
	unsigned int record_size, unsigned int allocation_size,
	SIIDR_CompareFunc compare_func, SIIDR **siidr_ptr, char *error_text));
COMPAT_FN_DECL(void SIIDR_FreeIDR, (SIIDR *siidr_ptr));
COMPAT_FN_DECL(void SIIDR_InitIDR, (SIIDR *siidr_ptr));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Check IDR function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int SIIDR_CheckControl, (SIIDR *siidr_ptr,
	char *error_text));
COMPAT_FN_DECL(int SIIDR_CheckControlRaw, (SIIDR *siidr_ptr,
	char *error_text));
COMPAT_FN_DECL(int SIIDR_CheckData, (SIIDR *siidr_ptr,
	char *error_text));
COMPAT_FN_DECL(int SIIDR_CheckDataRaw, (SIIDR *siidr_ptr,
	char *error_text));
COMPAT_FN_DECL(int SIIDR_CheckIDR, (SIIDR *siidr_ptr,
	char *error_text));
COMPAT_FN_DECL(int SIIDR_CheckRelOp, (SIIDR_REL_OP rel_op,
	char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Data modification with locking function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int SIIDR_Delete,   (SIIDR *siidr_ptr,
	const void *record_ptr, char *error_text));
COMPAT_FN_DECL(int SIIDR_DeleteAt, (SIIDR *siidr_ptr,
	unsigned int data_element, char *error_text));
COMPAT_FN_DECL(int SIIDR_Insert,   (SIIDR *siidr_ptr,
	const void *record_ptr, char *error_text));
COMPAT_FN_DECL(int SIIDR_InsertAt, (SIIDR *siidr_ptr,
	unsigned int data_element, const void *record_ptr, char *error_text));
COMPAT_FN_DECL(int SIIDR_Update,   (SIIDR *siidr_ptr,
	const void *record_ptr, char *error_text));
COMPAT_FN_DECL(int SIIDR_UpdateAt, (SIIDR *siidr_ptr,
	unsigned int data_element, const void *record_ptr, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Data modification without locking function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int SIIDR_DeleteRaw,   (SIIDR *siidr_ptr,
	const void *record_ptr, char *error_text));
COMPAT_FN_DECL(int SIIDR_DeleteAtRaw, (SIIDR *siidr_ptr,
	unsigned int data_element, char *error_text));
COMPAT_FN_DECL(int SIIDR_InsertRaw,   (SIIDR *siidr_ptr,
	const void *record_ptr, char *error_text));
COMPAT_FN_DECL(int SIIDR_InsertAtRaw, (SIIDR *siidr_ptr,
	unsigned int data_element, const void *record_ptr, char *error_text));
COMPAT_FN_DECL(int SIIDR_UpdateRaw,   (SIIDR *siidr_ptr,
	const void *record_ptr, char *error_text));
COMPAT_FN_DECL(int SIIDR_UpdateAtRaw, (SIIDR *siidr_ptr,
	unsigned int data_element, const void *record_ptr, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Record get with locking function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int SIIDR_GetRecordAt,          (SIIDR *siidr_ptr,
	unsigned int data_element, void *out_record_ptr));
COMPAT_FN_DECL(unsigned int SIIDR_GetCount,    (SIIDR *siidr_ptr,
	void *user_data_ptr, SIIDR_GetSpecFunc get_spec_func));
COMPAT_FN_DECL(int          SIIDR_GetFirst,    (SIIDR *siidr_ptr,
	unsigned int *out_index, void *out_record_ptr, void *user_data_ptr,
	SIIDR_GetSpecFunc get_spec_func));
COMPAT_FN_DECL(int          SIIDR_GetLast,     (SIIDR *siidr_ptr,
	unsigned int *out_index, void *out_record_ptr, void *user_data_ptr,
	SIIDR_GetSpecFunc get_spec_func));
COMPAT_FN_DECL(int          SIIDR_GetNext,     (SIIDR *siidr_ptr,
	const void *in_record_ptr, unsigned int *out_index, void *out_record_ptr,
	void *user_data_ptr, SIIDR_GetSpecFunc get_spec_func));
COMPAT_FN_DECL(int          SIIDR_GetPrevious, (SIIDR *siidr_ptr,
	const void *in_record_ptr, unsigned int *out_index, void *out_record_ptr,
	void *user_data_ptr, SIIDR_GetSpecFunc get_spec_func));
COMPAT_FN_DECL(int          SIIDR_GetRecord,   (SIIDR *siidr_ptr,
	const void *in_record_ptr, unsigned int *out_index, void *out_record_ptr));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Record get with locking and error return function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int SIIDR_GetRecordAtBasic, (SIIDR *siidr_ptr,
	unsigned int data_element, void *out_record_ptr, int *found_flag,
	char *error_text));
COMPAT_FN_DECL(int SIIDR_GetCountBasic,    (SIIDR *siidr_ptr,
	void *user_data_ptr, SIIDR_GetSpecFunc get_spec_func,
	unsigned int *found_count, char *error_text));
COMPAT_FN_DECL(int SIIDR_GetFirstBasic,    (SIIDR *siidr_ptr,
	unsigned int *out_index, void *out_record_ptr, void *user_data_ptr,
	SIIDR_GetSpecFunc get_spec_func, int *found_flag, char *error_text));
COMPAT_FN_DECL(int SIIDR_GetLastBasic,     (SIIDR *siidr_ptr,
	unsigned int *out_index, void *out_record_ptr, void *user_data_ptr,
	SIIDR_GetSpecFunc get_spec_func, int *found_flag, char *error_text));
COMPAT_FN_DECL(int SIIDR_GetNextBasic,     (SIIDR *siidr_ptr,
	const void *in_record_ptr, unsigned int *out_index, void *out_record_ptr,
	void *user_data_ptr, SIIDR_GetSpecFunc get_spec_func, int *found_flag,
	char *error_text));
COMPAT_FN_DECL(int SIIDR_GetPreviousBasic, (SIIDR *siidr_ptr,
	const void *in_record_ptr, unsigned int *out_index, void *out_record_ptr,
	void *user_data_ptr, SIIDR_GetSpecFunc get_spec_func, int *found_flag,
	char *error_text));
COMPAT_FN_DECL(int SIIDR_GetRecordBasic,   (SIIDR *siidr_ptr,
	const void *in_record_ptr, unsigned int *out_index,
	void *out_record_ptr, int *found_flag, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Record get without locking function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int SIIDR_GetRecordAtRaw, (SIIDR *siidr_ptr,
	unsigned int data_element, void *out_record_ptr));
COMPAT_FN_DECL(unsigned int SIIDR_GetCountRaw,    (SIIDR *siidr_ptr,
	void *user_data_ptr, SIIDR_GetSpecFunc get_spec_func));
COMPAT_FN_DECL(int          SIIDR_GetFirstRaw,    (SIIDR *siidr_ptr,
	unsigned int *out_index, void *out_record_ptr, void *user_data_ptr,
	SIIDR_GetSpecFunc get_spec_func));
COMPAT_FN_DECL(int          SIIDR_GetLastRaw,     (SIIDR *siidr_ptr,
	unsigned int *out_index, void *out_record_ptr, void *user_data_ptr,
	SIIDR_GetSpecFunc get_spec_func));
COMPAT_FN_DECL(int          SIIDR_GetNextRaw,     (SIIDR *siidr_ptr,
	const void *in_record_ptr, unsigned int *out_index, void *out_record_ptr,
	void *user_data_ptr, SIIDR_GetSpecFunc get_spec_func));
COMPAT_FN_DECL(int          SIIDR_GetPreviousRaw, (SIIDR *siidr_ptr,
	const void *in_record_ptr, unsigned int *out_index, void *out_record_ptr,
	void *user_data_ptr, SIIDR_GetSpecFunc get_spec_func));
COMPAT_FN_DECL(int          SIIDR_GetRecordRaw,   (SIIDR *siidr_ptr,
	const void *in_record_ptr, unsigned int *out_index, void *out_record_ptr));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Record list and array with locking function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int SIIDR_GetList, (SIIDR *siidr_ptr,
   void *user_data_ptr, SIIDR_GetSpecFunc get_spec_func,
	unsigned int *out_count, void ***out_list, char *error_text));
COMPAT_FN_DECL(int SIIDR_GetArray, (SIIDR *siidr_ptr,
   void *user_data_ptr, SIIDR_GetSpecFunc get_spec_func,
	unsigned int *out_count, void **out_array, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Record list and array without locking function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int SIIDR_GetListRaw, (SIIDR *siidr_ptr,
   void *user_data_ptr, SIIDR_GetSpecFunc get_spec_func,
	unsigned int *out_count, void ***out_list, char *error_text));
COMPAT_FN_DECL(int SIIDR_GetArrayRaw, (SIIDR *siidr_ptr,
   void *user_data_ptr, SIIDR_GetSpecFunc get_spec_func,
	unsigned int *out_count, void **out_array, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Record match with locking function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(unsigned int SIIDR_MatchCount, (SIIDR *siidr_ptr,
	const void *in_record_ptr, SIIDR_REL_OP rel_op,
	SIIDR_CompareFunc compare_func, void *user_data_ptr,
	SIIDR_GetSpecFunc get_spec_func));
COMPAT_FN_DECL(int          SIIDR_MatchCountBasic, (SIIDR *siidr_ptr,
	const void *in_record_ptr, SIIDR_REL_OP rel_op,
	SIIDR_CompareFunc compare_func, void *user_data_ptr,
	SIIDR_GetSpecFunc get_spec_func, unsigned int *found_count,
	char *error_text));
COMPAT_FN_DECL(int          SIIDR_MatchList, (SIIDR *siidr_ptr,
	const void *in_record_ptr, SIIDR_REL_OP rel_op,
	SIIDR_CompareFunc compare_func, void *user_data_ptr,
	SIIDR_GetSpecFunc get_spec_func, unsigned int *out_count, void ***out_list,
	char *error_text));
COMPAT_FN_DECL(int          SIIDR_MatchArray, (SIIDR *siidr_ptr,
	const void *in_record_ptr, SIIDR_REL_OP rel_op,
	SIIDR_CompareFunc compare_func, void *user_data_ptr,
	SIIDR_GetSpecFunc get_spec_func, unsigned int *out_count, void **out_array,
	char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Record match without locking function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(unsigned int SIIDR_MatchCountRaw, (SIIDR *siidr_ptr,
	const void *in_record_ptr, SIIDR_REL_OP rel_op,
	SIIDR_CompareFunc compare_func, void *user_data_ptr,
	SIIDR_GetSpecFunc get_spec_func));
COMPAT_FN_DECL(int          SIIDR_MatchListRaw, (SIIDR *siidr_ptr,
	const void *in_record_ptr, SIIDR_REL_OP rel_op,
	SIIDR_CompareFunc compare_func, void *user_data_ptr,
	SIIDR_GetSpecFunc get_spec_func, unsigned int *out_count, void ***out_list,
	char *error_text));
COMPAT_FN_DECL(int          SIIDR_MatchArrayRaw, (SIIDR *siidr_ptr,
	const void *in_record_ptr, SIIDR_REL_OP rel_op,
	SIIDR_CompareFunc compare_func, void *user_data_ptr,
	SIIDR_GetSpecFunc get_spec_func, unsigned int *out_count, void **out_array,
	char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Specialized delete with locking function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int SIIDR_DeleteAll,   (SIIDR *siidr_ptr, char *error_text));
COMPAT_FN_DECL(int SIIDR_DeleteSpec,  (SIIDR *siidr_ptr,
   void *user_data_ptr, SIIDR_GetSpecFunc get_spec_func, char *error_text));
COMPAT_FN_DECL(int SIIDR_DeleteMatch, (SIIDR *siidr_ptr,
	const void *in_record_ptr, SIIDR_REL_OP rel_op,
	SIIDR_CompareFunc compare_func, void *user_data_ptr,
	SIIDR_GetSpecFunc get_spec_func, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Specialized delete without locking function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void SIIDR_DeleteAllRaw, (SIIDR *siidr_ptr));
COMPAT_FN_DECL(void SIIDR_DeleteMatchRaw, (SIIDR *siidr_ptr,
	const void *in_record_ptr, SIIDR_REL_OP rel_op,
	SIIDR_CompareFunc compare_func, void *user_data_ptr,
	SIIDR_GetSpecFunc get_spec_func));
COMPAT_FN_DECL(void SIIDR_DeleteSpecRaw, (SIIDR *siidr_ptr,
   void *user_data_ptr, SIIDR_GetSpecFunc get_spec_func));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Bulk insert with locking function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int SIIDR_BulkInsertArray, (SIIDR *siidr_ptr,
	unsigned int in_count, const void *in_array, char *error_text));
COMPAT_FN_DECL(int SIIDR_BulkInsertList, (SIIDR *siidr_ptr,
	unsigned int in_count, void **in_list, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Bulk insert without locking function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int SIIDR_BulkInsertArrayRaw, (SIIDR *siidr_ptr,
	unsigned int in_count, const void *in_array, char *error_text));
COMPAT_FN_DECL(int SIIDR_BulkInsertListRaw, (SIIDR *siidr_ptr,
	unsigned int in_count, void **in_list, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Sort with locking function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int SIIDR_Sort, (SIIDR *siidr_ptr, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Sort without locking function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void SIIDR_SortRaw, (SIIDR *siidr_ptr));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Record find with locking function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(const void *SIIDR_FindRecord, (SIIDR *siidr_ptr,
	const void *record_ptr, unsigned int *found_index));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Record find without locking function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(const void *SIIDR_FindRecordRaw, (SIIDR *siidr_ptr,
	const void *record_ptr, unsigned int *found_index));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		IDR copy function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int SIIDR_CopyIDR,
	(SIIDR *in_siidr_ptr, SIIDR **out_siidr_ptr, char *error_text));
COMPAT_FN_DECL(int SIIDR_CopyIDRBasic,
	(SIIDR *in_siidr_ptr, const void *in_record_ptr,
	SIIDR_REL_OP rel_op, SIIDR_CompareFunc compare_func, void *user_data_ptr,
	SIIDR_GetSpecFunc get_spec_func, SIIDR **out_siidr_ptr, char *error_text));
COMPAT_FN_DECL(int SIIDR_CopyIDRRaw,
	(SIIDR *in_siidr_ptr, const void *in_record_ptr,
	SIIDR_REL_OP rel_op, SIIDR_CompareFunc compare_func, void *user_data_ptr,
	SIIDR_GetSpecFunc get_spec_func, SIIDR **out_siidr_ptr, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		IDR get state with locking function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(unsigned int       SIIDR_GetIDRAllocCount,
	(SIIDR *siidr_ptr));
COMPAT_FN_DECL(unsigned int       SIIDR_GetIDRAllocSize,
	(SIIDR *siidr_ptr));
COMPAT_FN_DECL(SIIDR_CompareFunc  SIIDR_GetIDRCompareFunc,
	(SIIDR *siidr_ptr));
COMPAT_FN_DECL(char              *SIIDR_GetIDRName,
	(SIIDR *siidr_ptr, char *idr_name, unsigned int max_size));
COMPAT_FN_DECL(unsigned int       SIIDR_GetIDRRecordCount,
	(SIIDR *siidr_ptr));
COMPAT_FN_DECL(unsigned int       SIIDR_GetIDRRecordSize,
	(SIIDR *siidr_ptr));
COMPAT_FN_DECL(SDTIF_STAT_TVAL   *SIIDR_GetIDRStatList,
	(SIIDR *siidr_ptr, SDTIF_STAT_TVAL *stat_list));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		IDR get state without locking function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(unsigned int       SIIDR_GetIDRAllocCountRaw,
	(SIIDR *siidr_ptr));
COMPAT_FN_DECL(unsigned int       SIIDR_GetIDRAllocSizeRaw,
	(SIIDR *siidr_ptr));
COMPAT_FN_DECL(SIIDR_CompareFunc  SIIDR_GetIDRCompareFuncRaw,
	(SIIDR *siidr_ptr));
COMPAT_FN_DECL(char              *SIIDR_GetIDRNameRaw,
	(SIIDR *siidr_ptr, char *idr_name, unsigned int max_size));
COMPAT_FN_DECL(unsigned int       SIIDR_GetIDRRecordCountRaw,
	(SIIDR *siidr_ptr));
COMPAT_FN_DECL(unsigned int       SIIDR_GetIDRRecordSizeRaw,
	(SIIDR *siidr_ptr));
COMPAT_FN_DECL(SDTIF_STAT_TVAL   *SIIDR_GetIDRStatListRaw,
	(SIIDR *siidr_ptr, SDTIF_STAT_TVAL *stat_list));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		IDR set state with locking function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int SIIDR_SetIDRAllocSize,
	(SIIDR *siidr_ptr, unsigned int allocation_size, char *error_text));
COMPAT_FN_DECL(int SIIDR_SetIDRCompareFunc,
	(SIIDR *siidr_ptr, SIIDR_CompareFunc compare_func, char *error_text));
COMPAT_FN_DECL(int SIIDR_SetIDRName,
	(SIIDR *siidr_ptr, const char *idr_name, char *error_text));
COMPAT_FN_DECL(int SIIDR_SetIDRRecordSize,
	(SIIDR *siidr_ptr, unsigned int record_size, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		IDR set state without locking function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int SIIDR_SetIDRAllocSizeRaw,
	(SIIDR *siidr_ptr, unsigned int allocation_size, char *error_text));
COMPAT_FN_DECL(int SIIDR_SetIDRCompareFuncRaw,
	(SIIDR *siidr_ptr, SIIDR_CompareFunc compare_func, char *error_text));
COMPAT_FN_DECL(int SIIDR_SetIDRNameRaw,
	(SIIDR *siidr_ptr, const char *idr_name, char *error_text));
COMPAT_FN_DECL(int SIIDR_SetIDRRecordSizeRaw,
	(SIIDR *siidr_ptr, unsigned int record_size, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Locking support function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int SIIDR_LockReaderIDR,    (SIIDR *siidr_ptr,
	char *error_text));
COMPAT_FN_DECL(int SIIDR_LockWriterIDR,    (SIIDR *siidr_ptr,
	char *error_text));
COMPAT_FN_DECL(int SIIDR_TryLockReaderIDR, (SIIDR *siidr_ptr,
	char *error_text));
COMPAT_FN_DECL(int SIIDR_TryLockWriterIDR, (SIIDR *siidr_ptr,
	char *error_text));
COMPAT_FN_DECL(int SIIDR_UnLockIDR,        (SIIDR *siidr_ptr,
	char *error_text));
COMPAT_FN_DECL(int SIIDR_UnLockReaderIDR,  (SIIDR *siidr_ptr,
	char *error_text));
COMPAT_FN_DECL(int SIIDR_UnLockWriterIDR,  (SIIDR *siidr_ptr,
	char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Miscellaneous function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int SIIDR_Compare, (const SIIDR *siidr_ptr,
	const void *ptr_1, const void *ptr_2, size_t data_length));
COMPAT_FN_DECL(int SIIDR_TouchCode, (const void *code_ptr,
	char *error_text));
COMPAT_FN_DECL(int SIIDR_TouchCodeOpt, (const void *code_ptr,
	char *error_text));
COMPAT_FN_DECL(int SIIDR_TouchError, (char *error_text));
COMPAT_FN_DECL(int SIIDR_TouchErrorOpt, (char *error_text));
COMPAT_FN_DECL(int SIIDR_ClearError, (char *error_text));
COMPAT_FN_DECL(int SIIDR_ClearErrorOpt, (char *error_text));
COMPAT_FN_DECL(int SIIDR_TouchRecordRead,
	(const SIIDR *siidr_ptr, const void *record_ptr, char *error_text));
COMPAT_FN_DECL(int SIIDR_TouchRecordReadOpt,
	(const SIIDR *siidr_ptr, const void *record_ptr, char *error_text));
COMPAT_FN_DECL(int SIIDR_TouchRecordWrite,
	(const SIIDR *siidr_ptr, void *record_ptr, char *error_text));
COMPAT_FN_DECL(int SIIDR_TouchRecordWriteOpt,
	(const SIIDR *siidr_ptr, void *record_ptr, char *error_text));
COMPAT_FN_DECL(int SIIDR_TouchRecordClear,
	(const SIIDR *siidr_ptr, void *record_ptr, char *error_text));
COMPAT_FN_DECL(int SIIDR_TouchRecordClearOpt,
	(const SIIDR *siidr_ptr, void *record_ptr, char *error_text));
COMPAT_FN_DECL(int SIIDR_TouchIDRRead,
	(const SIIDR *siidr_ptr, char *error_text));
COMPAT_FN_DECL(int SIIDR_TouchIDRWrite,
	(SIIDR *siidr_ptr, char *error_text));
COMPAT_FN_DECL(int SIIDR_TouchRead, (const void *data_ptr,
	unsigned int data_length, const char *data_name, char *error_text));
COMPAT_FN_DECL(int SIIDR_TouchWrite, (void *data_ptr,
	unsigned int data_length, const char *data_name, char *error_text));
COMPAT_FN_DECL(int SIIDR_TouchClear, (void *data_ptr,
	unsigned int data_length, const char *data_name, char *error_text));
COMPAT_FN_DECL(int SIIDR_TouchReadString, (const char *string_ptr,
	unsigned int string_length, const char *string_name, char *error_text));
	/*	*****************************************************************	*/

/* *********************************************************************** */

/*
	Provides compatibility between the external and internal versions of the
	SIIDR include files.
*/
/*	***********************************************************************	*/
#ifdef h__SIIDRI_H__h
# undef SIIDR
#endif /* #ifdef h__SIIDRI_H__h */
/*	***********************************************************************	*/

#endif /* #ifndef h__SIIDR_H__h */

