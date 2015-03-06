/* *********************************************************************** */
/* *********************************************************************** */
/*	Single Index Internal Data Repository Library Internal Include File		*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Internal include file for the Single Index Internal
								Data Repository (SIIDR) Library.

	Revision History	:	1996-04-10 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

#ifndef h__SIIDRI_H__h

#define h__SIIDRI_H__h					1

/* *********************************************************************** */
/* *********************************************************************** */
/*		Include necessary header files . . .											*/
/* *********************************************************************** */

#include <mtif.h>

/* *********************************************************************** */

/*
	Temporary definition to get 'siidr.h' included . . .
*/
/* *********************************************************************** */
#define SIIDR struct tag_SIIDR
struct tag_SIIDR;
# include "siidr.h"
#undef SIIDR
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	SIIDR Truth Code Mappings

   NAME        :	SIIDR Truth Code Mappings

	SYNOPSIS		:	truth_code = SIIDR_MAP_TRUTH_STR(str_code);

						truth_code = SIIDR_MAP_TRUTH_GEN(gen_code);

						truth_code = SIIDR_MAP_TRUTH_MTIF(mtif_code);

	DESCRIPTION	:	The SIIDR truth code mapping macros map truth codes from
						various low-level libraries to SIIDR truth codes.

						(.) ''SIIDR_MAP_TRUTH_STR'' maps a truth code
						from a STRFUNCS truth code to a SIIDR truth code.

						(.) ''SIIDR_MAP_TRUTH_GEN'' maps a truth code
						from a GENFUNCS truth code to a SIIDR truth code.

						(.) ''SIIDR_MAP_TRUTH_MTIF'' maps a truth code
						from a MTIF truth code to a SIIDR truth code.

	PARAMETERS	:	The single parameter to these macros is the value of the
						truth code to be mapped to its equivalent SIIDR truth
						code.

   NOTES       :	To map return codes from the libraries, use the related
						SIIDR return code mapping macros.

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1996 - 2015 Michael L. Brock

   OUTPUT INDEX:	SIIDR_MAP_TRUTH_STR
						SIIDR_MAP_TRUTH_GEN
						SIIDR_MAP_TRUTH_MTIF
						Truth Code Mappings:SIIDR_MAP_TRUTH_STR
						Truth Code Mappings:SIIDR_MAP_TRUTH_GEN
						Truth Code Mappings:SIIDR_MAP_TRUTH_MTIF
						Macros and Manifest Constants:SIIDR_MAP_TRUTH_STR
						Macros and Manifest Constants:SIIDR_MAP_TRUTH_GEN
						Macros and Manifest Constants:SIIDR_MAP_TRUTH_MTIF
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	SIIDR_MAP_TRUTH_STR
						SIIDR_MAP_TRUTH_GEN
						SIIDR_MAP_TRUTH_MTIF
						SIIDR_MAP_TRUTH_STR_TO_SIIDR
						SIIDR_MAP_TRUTH_GEN_TO_SIIDR
						SIIDR_MAP_TRUTH_MTIF_TO_SIIDR
						SIIDR Truth Code Mappings
						SIIDR Truth Code Mapping
						SIIDR truth code mappings
						SIIDR truth code mapping

   PUBLISH NAME:	SIIDR_MAP_TRUTH_STR
						SIIDR_MAP_TRUTH_GEN
						SIIDR_MAP_TRUTH_MTIF

	ENTRY CLASS	:	Macros and Manifest Constants:Truth Code Mappings

EOH */
/*	***********************************************************************	*/
#define SIIDR_MAP_TRUTH_STR(str_code)					\
	(((str_code) == STRFUNCS_TRUE)  ? SIIDR_TRUE : SIIDR_FALSE)
#define SIIDR_MAP_TRUTH_GEN(gen_code)					\
	(((gen_code) == GENFUNCS_TRUE)  ? SIIDR_TRUE : SIIDR_FALSE)
#define SIIDR_MAP_TRUTH_MTIF(mtif_code)				\
	(((mtif_code) == MTIF_TRUE)     ? SIIDR_TRUE : SIIDR_FALSE)
	/*	*****************************************************************
		*****************************************************************
		For compatibility . . .
		*****************************************************************	*/
#define SIIDR_MAP_TRUTH_STR_TO_SIIDR(str_code)		\
	SIIDR_MAP_TRUTH_STR(str_code)
#define SIIDR_MAP_TRUTH_GEN_TO_SIIDR(gen_code)		\
	SIIDR_MAP_TRUTH_GEN(gen_code)
#define SIIDR_MAP_TRUTH_MTIF_TO_SIIDR(mtif_code)	\
	SIIDR_MAP_TRUTH_MTIF(mtif_code)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	SIIDR Return Code Mappings

   NAME        :	SIIDR Return Code Mappings

	SYNOPSIS		:	return_code = SIIDR_MAP_ERROR_STR(str_code);

						return_code = SIIDR_MAP_ERROR_GEN(gen_code);

						return_code = SIIDR_MAP_ERROR_MTIF(mtif_code);

	DESCRIPTION	:	The SIIDR return code mapping macros map return codes from
						various low-level libraries to SIIDR return codes.

						(.) ''SIIDR_MAP_ERROR_STR'' maps a return code
						from a STRFUNCS return code to a SIIDR return code.

						(.) ''SIIDR_MAP_ERROR_GEN'' maps a return code
						from a GENFUNCS return code to a SIIDR return code.

						(.) ''SIIDR_MAP_ERROR_MTIF'' maps a return code
						from a MTIF return code to a SIIDR return code.

	PARAMETERS	:	The single parameter to these macros is the value of the
						return code to be mapped to its equivalent SIIDR return
						code.

   NOTES       :	To map truth codes from the libraries, use the related
						SIIDR truth code mapping macros.

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1996 - 2015 Michael L. Brock

   OUTPUT INDEX:	SIIDR_MAP_ERROR_STR
						SIIDR_MAP_ERROR_GEN
						SIIDR_MAP_ERROR_MTIF
						Return Code Mappings:SIIDR_MAP_ERROR_STR
						Return Code Mappings:SIIDR_MAP_ERROR_GEN
						Return Code Mappings:SIIDR_MAP_ERROR_MTIF
						Macros and Manifest Constants:SIIDR_MAP_ERROR_STR
						Macros and Manifest Constants:SIIDR_MAP_ERROR_GEN
						Macros and Manifest Constants:SIIDR_MAP_ERROR_MTIF
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	SIIDR_MAP_ERROR_STR
						SIIDR_MAP_ERROR_GEN
						SIIDR_MAP_ERROR_MTIF
						SIIDR_MAP_ERROR_STR_TO_SIIDR
						SIIDR_MAP_ERROR_GEN_TO_SIIDR
						SIIDR_MAP_ERROR_MTIF_TO_SIIDR
						SIIDR Return Code Mappings
						SIIDR Return Code Mapping
						SIIDR return code mappings
						SIIDR return code mapping
						SIIDR Status Code Mappings
						SIIDR Status Code Mapping
						SIIDR status code mappings
						SIIDR status code mapping
						SIIDR Error Code Mappings
						SIIDR Error Code Mapping
						SIIDR error code mappings
						SIIDR error code mapping

   PUBLISH NAME:	SIIDR_MAP_ERROR_STR
						SIIDR_MAP_ERROR_GEN
						SIIDR_MAP_ERROR_MTIF

	ENTRY CLASS	:	Macros and Manifest Constants:Return Code Mappings

EOH */
/*	***********************************************************************	*/
#define SIIDR_MAP_ERROR_STR(str_code)										 			\
	(((str_code) == STRFUNCS_SUCCESS)          ? SIIDR_SUCCESS          :	\
	 ((str_code) == STRFUNCS_FAILURE)          ? SIIDR_FAILURE          :	\
	 ((str_code) == STRFUNCS_BAD_ARGS_FAILURE) ? SIIDR_BAD_ARGS_FAILURE :	\
	 ((str_code) == STRFUNCS_MEMORY_FAILURE)   ? SIIDR_MEMORY_FAILURE   :	\
	 ((str_code) == STRFUNCS_SYSTEM_FAILURE)   ? SIIDR_SYSTEM_FAILURE   :	\
	 SIIDR_FAILURE)
#define SIIDR_MAP_ERROR_GEN(gen_code)													\
	(((gen_code) == GENFUNCS_SUCCESS)          ? SIIDR_SUCCESS          :	\
	 ((gen_code) == GENFUNCS_FAILURE)          ? SIIDR_FAILURE          :	\
	 ((gen_code) == GENFUNCS_BAD_ARGS_FAILURE) ? SIIDR_BAD_ARGS_FAILURE :	\
	 ((gen_code) == GENFUNCS_MEMORY_FAILURE)   ? SIIDR_MEMORY_FAILURE   :	\
	 ((gen_code) == GENFUNCS_SYSTEM_FAILURE)   ? SIIDR_SYSTEM_FAILURE   :	\
	 ((gen_code) == GENFUNCS_LOCK_ACQ_FAILURE) ? SIIDR_LOCK_ACQ_FAILURE :	\
	 SIIDR_FAILURE)
#define SIIDR_MAP_ERROR_MTIF(mtif_code)												\
	(((mtif_code) == MTIF_SUCCESS)             ? SIIDR_SUCCESS          :	\
	 ((mtif_code) == MTIF_FAILURE)             ? SIIDR_FAILURE          :	\
	 ((mtif_code) == MTIF_BAD_ARGS_FAILURE)    ? SIIDR_BAD_ARGS_FAILURE :	\
	 ((mtif_code) == MTIF_MEMORY_FAILURE)      ? SIIDR_MEMORY_FAILURE   :	\
	 ((mtif_code) == MTIF_SYSTEM_FAILURE)      ? SIIDR_SYSTEM_FAILURE   :	\
	 ((mtif_code) == MTIF_LOCK_ACQ_FAILURE)    ? SIIDR_LOCK_ACQ_FAILURE :	\
	 SIIDR_FAILURE)
/*	***********************************************************************	*/

/*
	ADF NOTE:No ADF.
*/
/*	***********************************************************************	*/
#define SIIDR_RWL_FLAGS						MTIF_RWL_FLAG_DEFAULT
/*	***********************************************************************	*/

/*
	ADF NOTE:No ADF.
*/
/*	***********************************************************************	*/
#define SIIDR_SIGNATURE						((unsigned long) 0x273d72c)
/*	***********************************************************************	*/

/*
	ADF NOTE:No ADF.
*/
/*	***********************************************************************	*/
typedef struct tag_SIIDR {
	unsigned long       signature;
	MTIF_RWL_HANDLE     rwl_data;
	unsigned int        record_size;
	unsigned int        total_size;
	unsigned int        data_offset;
	unsigned int        allocation_size;
	unsigned int        allocated_count;
	SIIDR_CompareFunc   compare_func;
	unsigned int        record_count;
	void              **record_list;
	char               *idr_name;
	SIIDR_CompareFunc   tmp_compare_func;
	SDTIF_STAT_TVAL     stat_list[SIIDR_STAT_COUNT];
} SIIDR;
typedef SIIDR SIIDRI;
/*	***********************************************************************	*/

/*
	ADF NOTE:No ADF.
*/
/*	***********************************************************************	*/
typedef struct {
	unsigned int count;
	unsigned int first;
} SIIDR_MATCH_BLOCK;
/*	***********************************************************************	*/

/*
	ADF NOTE:No ADF.
*/
/*	***********************************************************************	*/
typedef struct {
	unsigned int  bulk_index;
	void         *bulk_ptr;
	unsigned int  record_index;
	void         *record_ptr;
	unsigned int  compare_index;
} SIIDR_BULK;
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* Internal function prototypes for functions defined within 'siidr.a'.		*/
/* *********************************************************************** */

	/*	*****************************************************************
		*****************************************************************
		Allocation support function prototype . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int SIIDR_AllocateIDRBasicRaw, (SIIDR *siidr_ptr,
	unsigned int allocation_count, unsigned int allocation_size,
	char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		List and array support function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int SIIDR_GetListPtrRaw, (SIIDR *siidr_ptr,
   void *user_data_ptr, SIIDR_GetSpecFunc get_spec_func,
	unsigned int *out_count, void ***out_list, char *error_text));
COMPAT_FN_DECL(int SIIDR_MatchListPtrRaw, (SIIDR *siidr_ptr,
	const void *in_record_ptr, SIIDR_REL_OP rel_op,
	SIIDR_CompareFunc compare_func, void *user_data_ptr,
	SIIDR_GetSpecFunc get_spec_func, unsigned int *out_count, void ***out_list,
	char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Generic match support function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int          SIIDR_TestMatchRaw, (SIIDR *siidr_ptr,
	const void *in_record_ptr_1, const void *in_record_ptr_2,
	SIIDR_REL_OP rel_op, SIIDR_CompareFunc compare_func, void *user_data_ptr,
	SIIDR_GetSpecFunc get_spec_func));
COMPAT_FN_DECL(unsigned int SIIDR_SetMatchBlockListRaw, (SIIDR *siidr_ptr,
	const void *in_record_ptr, SIIDR_REL_OP rel_op,
	SIIDR_MATCH_BLOCK *block_list));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Bulk insert support function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int  SIIDR_CompareBulk, (const SIIDR *siidr_ptr,
	const SIIDR_BULK *ptr_1, const SIIDR_BULK *ptr_2, size_t data_length));
COMPAT_FN_DECL(int  SIIDR_CompareBulkByOrder, (const SIIDR *siidr_ptr,
	const SIIDR_BULK *ptr_1, const SIIDR_BULK *ptr_2, size_t data_length));
COMPAT_FN_DECL(int  SIIDR_InitBulkListRaw, (SIIDR *siidr_ptr,
	unsigned int in_count, void **in_list, SIIDR_CompareFunc compare_func,
	unsigned int *bulk_count, SIIDR_BULK **bulk_list, char *error_text));
COMPAT_FN_DECL(void SIIDR_SortBulkListRaw, (SIIDR *siidr_ptr,
	unsigned int bulk_count, SIIDR_BULK *bulk_list,
	SIIDR_CompareFunc compare_func));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Sort support function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void SIIDR_SortBasicRaw, (SIIDR *siidr_ptr,
	unsigned int in_count, void **in_list, SIIDR_CompareFunc compare_func));
	/*	*****************************************************************	*/

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/*	Support for the test harness data . . .											*/
/* *********************************************************************** */

#define SIIDR_TEST_ID_COUNT		10000

typedef struct {
	char         order_id[31 + 1];
	unsigned int record_id;
	unsigned int quantity;
	double       price;
} SIIDR_TEST_DATA;

COMPAT_FN_DECL(int   SIIDR_TEST_FastInsertIdList, (SIIDR *siidr_ptr,
	unsigned int start_id, unsigned int id_count, unsigned int id_increment,
	int random_flag, char *error_text));
COMPAT_FN_DECL(void  SIIDR_TEST_GetIdList, (unsigned int start_id,
	unsigned int id_count, unsigned int id_increment, unsigned int *id_list,
	int random_flag));
COMPAT_FN_DECL(int SIIDR_TEST_CreateIdList, (unsigned int start_id,
	unsigned int id_count, unsigned int id_increment, int random_flag,
	unsigned int **id_list, char *error_text));
COMPAT_FN_DECL(void  SIIDR_TEST_EmitRecordList,
	(const SIIDR *siidr_ptr));
COMPAT_FN_DECL(void  SIIDR_TEST_EmitRecord, (unsigned int record_index,
	const SIIDR_TEST_DATA *record_ptr));
COMPAT_FN_DECL(void *SIIDR_TEST_SetRecord, (unsigned int record_id,
	SIIDR_TEST_DATA *record_ptr));
COMPAT_FN_DECL(char *SIIDR_TEST_SetRecordId, (unsigned int record_id,
	SIIDR_TEST_DATA *record_ptr));
COMPAT_FN_DECL(int   SIIDR_TEST_DeleteIdList, (SIIDR *siidr_ptr,
	unsigned int start_id, unsigned int id_count, unsigned int id_increment,
	int random_flag, char *error_text));
COMPAT_FN_DECL(int   SIIDR_TEST_UpdateIdList, (SIIDR *siidr_ptr,
	unsigned int start_id, unsigned int id_count, unsigned int id_increment,
	int random_flag, char *error_text));
COMPAT_FN_DECL(int   SIIDR_TEST_InsertIdList, (SIIDR *siidr_ptr,
	unsigned int start_id, unsigned int id_count, unsigned int id_increment,
	int random_flag, char *error_text));
COMPAT_FN_DECL(void  SIIDR_TEST_ShowStats, (const SIIDR *siidr_ptr));
COMPAT_FN_DECL(int   SIIDR_TEST_CompareIDR,
	(const SIIDR *siidr_ptr_1, const SIIDR *siidr_ptr_2, char *error_text));
COMPAT_FN_DECL(int   SIIDR_TEST_Compare, (const SIIDR *siidr_ptr,
	const SIIDR_TEST_DATA *ptr_1, const SIIDR_TEST_DATA *ptr_2,
	size_t data_length));
COMPAT_FN_DECL(int   SIIDR_TEST_CompareBucket100, (const SIIDR *siidr_ptr,
	const SIIDR_TEST_DATA *ptr_1, const SIIDR_TEST_DATA *ptr_2,
	size_t data_length));
COMPAT_FN_DECL(int   SIIDR_TEST_CompareBucket1000, (const SIIDR *siidr_ptr,
	const SIIDR_TEST_DATA *ptr_1, const SIIDR_TEST_DATA *ptr_2,
	size_t data_length));
COMPAT_FN_DECL(int   SIIDR_TEST_CompareAlwaysEqual, (const SIIDR *siidr_ptr,
	const SIIDR_TEST_DATA *ptr_1, const SIIDR_TEST_DATA *ptr_2,
	size_t data_length));
COMPAT_FN_DECL(int   SIIDR_TEST_CompareAlwaysLessThan, (const SIIDR *siidr_ptr,
	const SIIDR_TEST_DATA *ptr_1, const SIIDR_TEST_DATA *ptr_2,
	size_t data_length));
COMPAT_FN_DECL(int   SIIDR_TEST_CompareAlwaysGreaterThan, (const SIIDR *siidr_ptr,
	const SIIDR_TEST_DATA *ptr_1, const SIIDR_TEST_DATA *ptr_2,
	size_t data_length));
COMPAT_FN_DECL(int   SIIDR_TEST_CompareEquivalent, (const SIIDR *siidr_ptr,
	const SIIDR_TEST_DATA *ptr_1, const SIIDR_TEST_DATA *ptr_2,
	size_t data_length));
COMPAT_FN_DECL(int   SIIDR_TEST_GetSpecQuantity,
	(const SIIDR *siidr_ptr, unsigned int *user_data_ptr,
	const SIIDR_TEST_DATA *record_ptr));
COMPAT_FN_DECL(int   SIIDR_TEST_GetSpecQuantityEven,
	(const SIIDR *siidr_ptr, unsigned int *user_data_ptr,
	const SIIDR_TEST_DATA *record_ptr));
COMPAT_FN_DECL(int   SIIDR_TEST_GetSpecQuantityOdd,
	(const SIIDR *siidr_ptr, unsigned int *user_data_ptr,
	const SIIDR_TEST_DATA *record_ptr));
COMPAT_FN_DECL(int   SIIDR_TEST_GetSpecPrice,
	(const SIIDR *siidr_ptr, double *user_data_ptr,
	const SIIDR_TEST_DATA *record_ptr));
/* *********************************************************************** */

#endif /* #ifndef h__SIIDRI_H__h */

