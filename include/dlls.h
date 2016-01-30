/* *********************************************************************** */
/* *********************************************************************** */
/*	Doubly-Linked List Support (DLLS) Library Include File						*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the Doubly-Linked List Support
								(DLLS) library.

	Revision History	:	1987-03-11 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1987 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

#ifndef h__DLLS_H__h

#define h__DLLS_H__h							1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Necessary include files . . .															*/
/*	***********************************************************************	*/

#include <stddef.h>

#include <mbcompat.h>

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   BASE NAME   :  DLLS Truth Codes

   NAME        :  DLLS Truth Codes

   DESCRIPTION :  Manifest constants used within DLLS to specify the truth
						or falsity of expressions.

						(.) ''DLLS_TRUE''

						(.) ''DLLS_FALSE''

   NOTES       :  The manifest constant ''DLLS_TRUE'' should be defined as
						a non-zero value. Conversely, the manifest constant
						''DLLS_FALSE'' should be defined as zero (''0'').

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1987 - 2016 Michael L. Brock

   OUTPUT INDEX:  DLLS_TRUE
						DLLS_FALSE
						DLLS Truth Codes:DLLS_TRUE
						DLLS Truth Codes:DLLS_FALSE
						DLLS Manifest Constants:DLLS_TRUE
						DLLS Manifest Constants:DLLS_FALSE
						DLLS Defines:DLLS_TRUE
						DLLS Defines:DLLS_FALSE
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:  DLLS Truth Codes
						DLLS Truth Code
						DLLS truth codes
						DLLS truth code
						DLLS_TRUE
						DLLS_FALSE

   PUBLISH NAME:	DLLS Truth Codes
						DLLS_TRUE
						DLLS_FALSE

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define DLLS_TRUE								1
#define DLLS_FALSE							0
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   BASE NAME   :	DLLS Return Codes

   NAME        :  DLLS Return Codes

   DESCRIPTION :  The DLLS return codes have the following meanings:

						(.) ''DLLS_SUCCESS'' means that the function invoked
						completed without error. ''DLLS_SUCCESS'' is guaranteed to
						be equal to zero (''0'').

						(.) ''DLLS_FAILURE'' indicates that the function invoked
						encountered a general operation failure. This is the
						'catch-all' error code for those errors which do not fit
						into category of one the other DLLS error codes.

						(.) ''DLLS_BAD_ARGS_FAILURE'' indicates that the
						arguments passed to a function invoked were invalid.

						(.) ''DLLS_MEMORY_FAILURE'' indicates that the memory
						required for operation of the function invoked could not be
						allocated.

						(.) ''DLLS_SYSTEM_FAILURE'' indicates that the function
						invoked encountered a failure of a standard library
						function or a system call.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1987 - 2016 Michael L. Brock

   OUTPUT INDEX:  DLLS_SUCCESS
						DLLS_FAILURE
						DLLS_BAD_ARGS_FAILURE
						DLLS_MEMORY_FAILURE
						DLLS_SYSTEM_FAILURE
						DLLS Return Codes:DLLS_SUCCESS
						DLLS Return Codes:DLLS_FAILURE
						DLLS Return Codes:DLLS_BAD_ARGS_FAILURE
						DLLS Return Codes:DLLS_MEMORY_FAILURE
						DLLS Return Codes:DLLS_SYSTEM_FAILURE
						DLLS Manifest Constants:DLLS_SUCCESS
						DLLS Manifest Constants:DLLS_FAILURE
						DLLS Manifest Constants:DLLS_BAD_ARGS_FAILURE
						DLLS Manifest Constants:DLLS_MEMORY_FAILURE
						DLLS Manifest Constants:DLLS_SYSTEM_FAILURE
						DLLS Defines:DLLS_SUCCESS
						DLLS Defines:DLLS_FAILURE
						DLLS Defines:DLLS_BAD_ARGS_FAILURE
						DLLS Defines:DLLS_MEMORY_FAILURE
						DLLS Defines:DLLS_SYSTEM_FAILURE
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:  DLLS_SUCCESS
						DLLS_FAILURE
						DLLS_BAD_ARGS_FAILURE
						DLLS_MEMORY_FAILURE
						DLLS_SYSTEM_FAILURE
						DLLS Return Codes
						DLLS Return Code
						DLLS return codes
						DLLS return code
						DLLS Status Codes
						DLLS Status Code
						DLLS status codes
						DLLS status code
						DLLS Error Codes
						DLLS Error Code
						DLLS error codes
						DLLS error code

   PUBLISH NAME:	DLLS Return Codes
						DLLS return codes
						DLLS_SUCCESS
						DLLS_FAILURE
						DLLS_BAD_ARGS_FAILURE
						DLLS_MEMORY_FAILURE
						DLLS_SYSTEM_FAILURE

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define DLLS_SUCCESS							   0
#define DLLS_FAILURE							  -1
#define DLLS_BAD_ARGS_FAILURE				  -2
#define DLLS_MEMORY_FAILURE				  -3
#define DLLS_SYSTEM_FAILURE				  -4
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :  DLLS_MAX_ERROR_TEXT

   DESCRIPTION :  The manifest constant ''DLLS_MAX_ERROR_TEXT'' defines
						the minimum amount of storage which should be allocated to
						hold an error message returned by a DLLS function.

   CAVEATS     :  DLLS error messages can be quite lengthy. Therefore,
						attempting to save space by allocating less than
						''DLLS_MAX_ERROR_TEXT'' bytes to error message buffers
						passed to DLLS functions can lead to overwriting of the
						heap or the stack.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1987 - 2016 Michael L. Brock

   OUTPUT INDEX:  DLLS_MAX_ERROR_TEXT
						DLLS Manifest Constants:DLLS_MAX_ERROR_TEXT
						DLLS Defines:DLLS_MAX_ERROR_TEXT
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	DLLS_MAX_ERROR_TEXT

   PUBLISH NAME:	DLLS_MAX_ERROR_TEXT

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define DLLS_MAX_ERROR_TEXT				1024
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
typedef unsigned long DLLS_SIGNATURE;
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
typedef COMPAT_FN_TYPE(void (*DLLS_FreeFunc), (void *));
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#define DLLS_FreeFunc_CAST(fptr)       \
	COMPAT_FN_CAST(void, (void *), (fptr))
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
typedef struct tag_DLLS_NODE {
	struct tag_DLLS      *dlls_ptr;
	struct tag_DLLS_NODE *prev_ptr;
	struct tag_DLLS_NODE *next_ptr;
	void                 *data_ptr;
} DLLS_NODE;
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
typedef struct tag_DLLS {
	DLLS_SIGNATURE  signature;
	DLLS_NODE      *first_ptr;
	DLLS_NODE      *last_ptr;
	unsigned int    node_count;
	void           *data_ptr;
	DLLS_FreeFunc   free_func;
} DLLS;
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
typedef COMPAT_FN_TYPE(int (*DLLS_IterateFunc),
	(DLLS_NODE *node_ptr, void *user_data_ptr, char *error_text));
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
typedef COMPAT_FN_TYPE(int (*DLLS_CompareFunc),
	(void *control_ptr, const DLLS_NODE *ptr_1, const DLLS_NODE *ptr_2,
	size_t data_length));
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
typedef COMPAT_FN_TYPE(int (*DLLS_MatchFunc),
	(DLLS_NODE *node_ptr, void *user_data_ptr));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Functions provided in library 'dlls.{a|lib}' . . .								*/
/*	***********************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Add function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(DLLS_NODE *DLLS_AddFirst,
	(DLLS *dlls_ptr, DLLS_NODE *new_node_ptr));
COMPAT_FN_DECL(DLLS_NODE *DLLS_AddLast,
	(DLLS *dlls_ptr, DLLS_NODE *new_node_ptr));
COMPAT_FN_DECL(DLLS_NODE *DLLS_AddNext,
	(DLLS_NODE *ref_node_ptr, DLLS_NODE *new_node_ptr));
COMPAT_FN_DECL(DLLS_NODE *DLLS_AddPrevious,
	(DLLS_NODE *ref_node_ptr, DLLS_NODE *new_node_ptr));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Remove function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void DLLS_RemoveFirst, (DLLS *dlls_ptr));
COMPAT_FN_DECL(void DLLS_RemoveLast, (DLLS *dlls_ptr));
COMPAT_FN_DECL(void DLLS_RemoveNext, (DLLS_NODE *ref_node_ptr));
COMPAT_FN_DECL(void DLLS_RemovePrevious, (DLLS_NODE *ref_node_ptr));
COMPAT_FN_DECL(void DLLS_RemoveSelf, (DLLS_NODE *node_ptr));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Delete function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void DLLS_DeleteFirst, (DLLS *dlls_ptr));
COMPAT_FN_DECL(void DLLS_DeleteLast, (DLLS *dlls_ptr));
COMPAT_FN_DECL(void DLLS_DeleteNext, (DLLS_NODE *ref_node_ptr));
COMPAT_FN_DECL(void DLLS_DeletePrevious, (DLLS_NODE *ref_node_ptr));
COMPAT_FN_DECL(void DLLS_DeleteSelf, (DLLS_NODE *node_ptr));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Get function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(DLLS_NODE *DLLS_GetFirst, (DLLS *dlls_ptr));
COMPAT_FN_DECL(DLLS_NODE *DLLS_GetLast, (DLLS *dlls_ptr));
COMPAT_FN_DECL(DLLS_NODE *DLLS_GetNext, (DLLS_NODE *ref_node_ptr));
COMPAT_FN_DECL(DLLS_NODE *DLLS_GetPrevious, (DLLS_NODE *ref_node_ptr));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Get list function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DLLS_GetList,
	(DLLS *dlls_ptr, unsigned int *out_count, DLLS_NODE ***out_list,
	char *error_text));
COMPAT_FN_DECL(int DLLS_GetListBasic,
	(DLLS_NODE *ref_node_ptr, unsigned int max_count, int reverse_flag,
	unsigned int *out_count, DLLS_NODE ***out_list, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Match function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(DLLS_NODE    *DLLS_Match,
	(const DLLS *dlls_ptr, DLLS_MatchFunc match_func, void *control_ptr,
	size_t data_length));
COMPAT_FN_DECL(DLLS_NODE    *DLLS_MatchBasic,
	(const DLLS *dlls_ptr, DLLS_NODE *ref_node_ptr, unsigned int max_count,
	int reverse_flag, DLLS_MatchFunc match_func, void *control_ptr,
	size_t data_length));
COMPAT_FN_DECL(unsigned int  DLLS_MatchCount,
	(const DLLS *dlls_ptr, DLLS_MatchFunc match_func, void *control_ptr,
	size_t data_length));
COMPAT_FN_DECL(unsigned int  DLLS_MatchCountBasic,
	(const DLLS_NODE *ref_node_ptr, unsigned int max_count,
	DLLS_MatchFunc match_func, void *control_ptr, size_t data_length));
COMPAT_FN_DECL(int           DLLS_MatchList,
	(DLLS *dlls_ptr, DLLS_MatchFunc match_func, void *control_ptr,
	size_t data_length, unsigned int *out_count, DLLS_NODE ***out_list,
	char *error_text));
COMPAT_FN_DECL(int           DLLS_MatchListBasic, (DLLS_NODE *ref_node_ptr,
	unsigned int max_count, int reverse_flag, DLLS_MatchFunc match_func,
	void *control_ptr, size_t data_length, unsigned int *out_count,
	DLLS_NODE ***out_list, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Miscellaneous supporting function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int   DLLS_Check,
	(const DLLS *dlls_ptr, char *error_text));
COMPAT_FN_DECL(DLLS *DLLS_Create,
	(DLLS *dlls_ptr, DLLS_FreeFunc free_func));
COMPAT_FN_DECL(void  DLLS_Destroy,
	(DLLS *dlls_ptr));
COMPAT_FN_DECL(DLLS *DLLS_Init,
	(DLLS *dlls_ptr));
COMPAT_FN_DECL(int   DLLS_Iterate,
	(DLLS *dlls_ptr, DLLS_IterateFunc iterate_func, void *user_data_ptr,
	char *error_text));
COMPAT_FN_DECL(int   DLLS_IterateBasic,
	(DLLS_NODE *ref_node_ptr, unsigned int max_count, int reverse_flag,
	DLLS_IterateFunc iterate_func, void *user_data_ptr,
	unsigned int *iteration_count, char *error_text));
COMPAT_FN_DECL(DLLS *DLLS_Reverse,
	(DLLS *dlls_ptr));
COMPAT_FN_DECL(int  DLLS_Sort,
	(DLLS *dlls_ptr, DLLS_CompareFunc compare_func, void *control_ptr,
	size_t data_length, char *error_text));
COMPAT_FN_DECL(void  DLLS_Swap,
	(DLLS_NODE *node_ptr_1, DLLS_NODE *node_ptr_2));
	/*	*****************************************************************	*/

/*	***********************************************************************	*/

#endif /* #ifndef h__DLLS_H__h */

