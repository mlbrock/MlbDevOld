/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Trading Technologies API Interface Library Include File						*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the TTAPI Library.

	Revision History	:	2001-09-08 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 2001 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef HH__ttapi_h__HH

#define HH__ttapi_h__HH						1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*    Include necessary header files . . .                                 */
/*	***********************************************************************	*/

#include <strfuncs.h>
#include <genfuncs.h>
#include <sdtif.h>
#include <mtif.h>
#include <mlog.h>
#include <RVUtilrvmsg_Msg_TC.h>

#ifdef _Windows
# if _MSC_VER >= 1300
#  pragma warning(disable:4217 4251 4555)
# endif /* # if _MSC_VER >= 1300 */
# pragma warning(disable:4710 4786)
# pragma warning(disable:4018 4100 4146 4244 4245 4511 4512 4663)
# include <tt_world.h>
# if _MSC_VER >= 1300
#  pragma warning(default:4217 4251 4555)
# endif /* # if _MSC_VER >= 1300 */
# pragma warning(default:4018 4100 4146 4244 4245 4511 4512 4663)
#else
# include <tt_world.h>
#endif /* #ifdef _Windows */

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   BASE NAME   :  TTAPI Truth Codes

   NAME        :  TTAPI Truth Codes

   DESCRIPTION :  Manifest constants used within TTAPI to specify the truth
						or falsity of expressions.

						(.) ''TTAPI_TRUE''

						(.) ''TTAPI_FALSE''

   NOTES       :  The manifest constant ''TTAPI_TRUE'' should be defined as
						a non-zero value. Conversely, the manifest constant
						''TTAPI_FALSE'' should be defined as zero (''0'').

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 2001 - 2016 Michael L. Brock

   OUTPUT INDEX:  TTAPI_TRUE
						TTAPI_FALSE
						TTAPI Truth Codes:TTAPI_TRUE
						TTAPI Truth Codes:TTAPI_FALSE
						TTAPI Manifest Constants:TTAPI_TRUE
						TTAPI Manifest Constants:TTAPI_FALSE
						TTAPI Defines:TTAPI_TRUE
						TTAPI Defines:TTAPI_FALSE
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:  TTAPI Truth Codes
						TTAPI Truth Code
						TTAPI truth codes
						TTAPI truth code
						TTAPI_TRUE
						TTAPI_FALSE

   PUBLISH NAME:	TTAPI Truth Codes
						TTAPI_TRUE
						TTAPI_FALSE

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define TTAPI_TRUE							1
#define TTAPI_FALSE							0
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   BASE NAME   :	TTAPI Return Codes

   NAME        :  TTAPI Return Codes

   DESCRIPTION :  The TTAPI return codes have the following meanings:

						(.) ''TTAPI_SUCCESS'' means that the function invoked
						completed without error. ''TTAPI_SUCCESS'' is guaranteed to
						be equal to zero (''0'').

						(.) ''TTAPI_FAILURE'' indicates that the function invoked
						encountered a general operation failure. This is the
						'catch-all' error code for those errors which do not fit
						into category of one the other TTAPI error codes.

						(.) ''TTAPI_BAD_ARGS_FAILURE'' indicates that the
						arguments passed to a function invoked were invalid.

						(.) ''TTAPI_MEMORY_FAILURE'' indicates that the memory
						required for operation of the function invoked could not be
						allocated.

						(.) ''TTAPI_SYSTEM_FAILURE'' indicates that the function
						invoked encountered a failure of a standard library
						function or a system call.

						(.) ''TTAPI_LOCK_ACQ_FAILURE'' indicates that a lock
						could not be acquired on a resource.

						(.) ''TTAPI_INVALID_SIDE_FAILURE'' indicates that a GL API
						side code is invalid or a message cannot be processed from
						or for the specified side.

						(.) ''TTAPI_INVALID_FACILITY_FAILURE'' indicates that
						a GL API facility code is invalid or a message cannot be
						processed from the specified facility.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 2001 - 2016 Michael L. Brock

   OUTPUT INDEX:  TTAPI_SUCCESS
						TTAPI_FAILURE
						TTAPI_BAD_ARGS_FAILURE
						TTAPI_MEMORY_FAILURE
						TTAPI_SYSTEM_FAILURE
						TTAPI_LOCK_ACQ_FAILURE
						TTAPI_INVALID_SIDE_FAILURE
						TTAPI_INVALID_FACILITY_FAILURE
						TTAPI Return Codes:TTAPI_SUCCESS
						TTAPI Return Codes:TTAPI_FAILURE
						TTAPI Return Codes:TTAPI_BAD_ARGS_FAILURE
						TTAPI Return Codes:TTAPI_MEMORY_FAILURE
						TTAPI Return Codes:TTAPI_SYSTEM_FAILURE
						TTAPI Return Codes:TTAPI_LOCK_ACQ_FAILURE
						TTAPI Return Codes:TTAPI_INVALID_SIDE_FAILURE
						TTAPI Return Codes:TTAPI_INVALID_FACILITY_FAILURE
						TTAPI Manifest Constants:TTAPI_SUCCESS
						TTAPI Manifest Constants:TTAPI_FAILURE
						TTAPI Manifest Constants:TTAPI_BAD_ARGS_FAILURE
						TTAPI Manifest Constants:TTAPI_MEMORY_FAILURE
						TTAPI Manifest Constants:TTAPI_SYSTEM_FAILURE
						TTAPI Manifest Constants:TTAPI_LOCK_ACQ_FAILURE
						TTAPI Manifest Constants:TTAPI_INVALID_SIDE_FAILURE
						TTAPI Manifest Constants:TTAPI_INVALID_FACILITY_FAILURE
						TTAPI Defines:TTAPI_SUCCESS
						TTAPI Defines:TTAPI_FAILURE
						TTAPI Defines:TTAPI_BAD_ARGS_FAILURE
						TTAPI Defines:TTAPI_MEMORY_FAILURE
						TTAPI Defines:TTAPI_SYSTEM_FAILURE
						TTAPI Defines:TTAPI_LOCK_ACQ_FAILURE
						TTAPI Defines:TTAPI_INVALID_SIDE_FAILURE
						TTAPI Defines:TTAPI_INVALID_FACILITY_FAILURE
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:  TTAPI_SUCCESS
						TTAPI_FAILURE
						TTAPI_BAD_ARGS_FAILURE
						TTAPI_MEMORY_FAILURE
						TTAPI_SYSTEM_FAILURE
						TTAPI_LOCK_ACQ_FAILURE
						TTAPI_INVALID_SIDE_FAILURE
						TTAPI_INVALID_FACILITY_FAILURE
						TTAPI Return Codes
						TTAPI Return Code
						TTAPI return codes
						TTAPI return code
						TTAPI Status Codes
						TTAPI Status Code
						TTAPI status codes
						TTAPI status code
						TTAPI Error Codes
						TTAPI Error Code
						TTAPI error codes
						TTAPI error code

   PUBLISH NAME:	TTAPI Return Codes
						TTAPI return codes
						TTAPI_SUCCESS
						TTAPI_FAILURE
						TTAPI_BAD_ARGS_FAILURE
						TTAPI_MEMORY_FAILURE
						TTAPI_SYSTEM_FAILURE
						TTAPI_LOCK_ACQ_FAILURE
						TTAPI_INVALID_SIDE_FAILURE
						TTAPI_INVALID_FACILITY_FAILURE

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define TTAPI_SUCCESS						   0
#define TTAPI_FAILURE						  -1
#define TTAPI_BAD_ARGS_FAILURE			  -2
#define TTAPI_MEMORY_FAILURE				  -3
#define TTAPI_SYSTEM_FAILURE				  -4
#define TTAPI_LOCK_ACQ_FAILURE			  -5
#define TTAPI_TT_SERVER_DOWN				  -6
#define TTAPI_TT_NO_LICENSE				  -7
#define TTAPI_TT_REQ_TIME_OUT				  -8
#define TTAPI_TT_ACCT_LOCK_OUT			  -9
#define TTAPI_TT_PASSWORD_EXPIRE			 -10
#define TTAPI_TT_LICENSE_EXPIRE			 -11
#define TTAPI_TT_SRV_LICENSE_EXPIRE		 -12
#define TTAPI_TT_REQ_FAILED				 -13
#define TTAPI_TT_LOGIN_REJECT				 -14
#define TTAPI_TT_COMM_INIT_FAILURE		 -15
#define TTAPI_TT_OTHER_ERROR				 -16
#define TTAPI_TT_GENERAL_FAILURE			 -17
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :  TTAPI_MAX_ERROR_TEXT

   DESCRIPTION :  The manifest constant ''TTAPI_MAX_ERROR_TEXT'' defines
						the minimum amount of storage which should be allocated to
						hold an error message returned by a TTAPI function.

   CAVEATS     :  TTAPI error messages can be quite lengthy. Therefore,
						attempting to save space by allocating less than
						''TTAPI_MAX_ERROR_TEXT'' bytes to error message buffers
						passed to TTAPI functions can lead to overwriting of the
						heap or the stack.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 2001 - 2016 Michael L. Brock

   OUTPUT INDEX:  TTAPI_MAX_ERROR_TEXT
						TTAPI Manifest Constants:TTAPI_MAX_ERROR_TEXT
						TTAPI Defines:TTAPI_MAX_ERROR_TEXT
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	TTAPI_MAX_ERROR_TEXT

   PUBLISH NAME:	TTAPI_MAX_ERROR_TEXT

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define TTAPI_MAX_ERROR_TEXT				4096
/*	***********************************************************************	*/

/*
	ADF NOTE:No ADF.
*/
/*	***********************************************************************	*/
#define TTAPI_MAP_TRUTH(code)          ((code)  ? TTAPI_TRUE : TTAPI_FALSE)
/*	***********************************************************************	*/

/*
	ADF NOTE:No ADF.
*/
/*	***********************************************************************	*/
#define TTAPI_MAX_EXCHANGE_NAME			(TT_MAX_EXCH_NAME - 1)
#define TTAPI_MAX_PRICE_TYPE_NAME		31
#define TTAPI_MAX_PRODUCT_TYPE_NAME		(TT_MAX_PROD_LEN - 1)
#define TTAPI_MAX_PRODUCT_GROUP_NAME	10
#define TTAPI_MAX_PRODUCT_STATUS_NAME	(TT_MAX_PROD_LEN - 1)
/*	***********************************************************************	*/

/*
	ADF NOTE:No ADF.
*/
/*	***********************************************************************	*/
#define TTAPI_TT_DATE_MAX_LEN				(4 + 1 + 2 + 1 + 2)
#define TTAPI_TT_DATE_CONTRACT_MAX_LEN	(4 + 1 + 2)
#define TTAPI_TT_TIME_BASIC_MAX_LEN		(2 + 1 + 2 + 1 + 2)
#define TTAPI_TT_TIME_MAX_LEN				(TTAPI_TT_TIME_BASIC_MAX_LEN + 1 + 3)
#define TTAPI_TT_DATE_TIME_MAX_LEN		\
	(TTAPI_TT_DATE_MAX_LEN + 1 + TTAPI_TT_TIME_MAX_LEN)
/*	***********************************************************************	*/

/*
	ADF NOTE:No ADF.
*/
/*	***********************************************************************	*/
#define TTAPI_SERVER_KEY_STRING_LEN		(TT_SERVER_KEY_LEN * 3)
/*	***********************************************************************	*/

/*
	ADF NOTE:No ADF.
*/
/*	***********************************************************************	*/
#define TTAPI_TT_MEMBER_ID_LEN			(TT_MEMBER_ID_LEN - 1)
#define TTAPI_TT_TRADER_GROUP_LEN		(TT_TRADER_GROUP_LEN - 1)
#define TTAPI_TT_TRADER_ID_LEN			(TT_TRADER_ID_LEN - 1)
#define TTAPI_TT_USER_PASS_LEN			(TT_USER_PASS_LEN - 1)
#define TTAPI_TT_ACCOUNT_LEN				(TT_ACCOUNT_LEN - 1)
#define TTAPI_TT_EXCH_ACCOUNT_LEN		(TT_EXCH_ACCOUNT_LEN - 1)
#define TTAPI_TT_COMPLETE_ID				\
	(TTAPI_TT_MEMBER_ID_LEN + TTAPI_TT_TRADER_GROUP_LEN + TTAPI_TT_TRADER_ID_LEN)
/*	***********************************************************************	*/

/*
	ADF NOTE:No ADF.
*/
/*	***********************************************************************	*/
#define TTAPI_FULL_USER_NAME_LEN			\
	(TTAPI_TT_MEMBER_ID_LEN + TTAPI_TT_TRADER_GROUP_LEN + TTAPI_TT_TRADER_ID_LEN)
/*	***********************************************************************	*/

/*
	ADF NOTE:No ADF.
*/
/*	***********************************************************************	*/
#define TTAPI_MAX_TICKER_ANY				63
/*	***********************************************************************	*/

/*
	ADF NOTE:No ADF.
*/
/*	***********************************************************************	*/
#define TTAPI_DEFAULT_SPIN_COUNT			((unsigned int) (30 * 10))
#define TTAPI_DEFAULT_SPIN_WAIT			((unsigned int) 100000L)
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define TTAPI_TT_PROD_GROUP_ID_CODE_NONE	((TT_PROD_GROUP_ID_CODE) INT_MAX)
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef enum {
	TTAPI_PROD_TYPE_NONE				=  0,
	TTAPI_PROD_TYPE_NOT_SPECIFIED =  0,
	TTAPI_PROD_TYPE_FUTURE			=  1,
	TTAPI_PROD_TYPE_FUT				=  1,
	TTAPI_PROD_TYPE_OPTION			=  2,
	TTAPI_PROD_TYPE_OPT				=  2,
	TTAPI_PROD_TYPE_SPREAD			=  3,
	TTAPI_PROD_TYPE_SPD				=  3,
	TTAPI_PROD_TYPE_EQUITY			=  4,
	TTAPI_PROD_TYPE_STOCK			=  4,
	TTAPI_PROD_TYPE_STK				=  4,
	TTAPI_PROD_TYPE_INDEX			=  5,
	TTAPI_PROD_TYPE_IDX				=  5,
	TTAPI_PROD_TYPE_DEBT				=  6,
	TTAPI_PROD_TYPE_BND				=  6,
	TTAPI_PROD_TYPE_INTEREST_RATE	=  7,
	TTAPI_PROD_TYPE_INT_RAT			=  7,
	TTAPI_PROD_TYPE_CB				=  8,
	TTAPI_PROD_TYPE_CNV_BND			=  8,
	TTAPI_PROD_TYPE_COMMODITY		=  9,
	TTAPI_PROD_TYPE_CMDY				=  9,
	TTAPI_PROD_TYPE_EB				= 10,
	TTAPI_PROD_TYPE_EXC_BND			= 10,
	TTAPI_PROD_TYPE_CURRENCY_RATE	= 11,
	TTAPI_PROD_TYPE_CUR_RAT			= 11,
	TTAPI_PROD_TYPE_SECTOR        = 12,
	TTAPI_PROD_TYPE_SCT           = 12
} TTAPI_PROD_TYPE;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define TTAPI_PROD_TYPE_IS_VALID(prod_type)							\
	(((prod_type) == TTAPI_PROD_TYPE_NONE)  	? TTAPI_TRUE	:	\
	 ((prod_type) == TTAPI_PROD_TYPE_FUTURE)	? TTAPI_TRUE	:	\
	 ((prod_type) == TTAPI_PROD_TYPE_OPTION)	? TTAPI_TRUE	:	\
	 ((prod_type) == TTAPI_PROD_TYPE_SPREAD)	? TTAPI_TRUE	:	\
	 ((prod_type) == TTAPI_PROD_TYPE_STK)		? TTAPI_TRUE	:	\
	 ((prod_type) == TTAPI_PROD_TYPE_IDX)		? TTAPI_TRUE	:	\
	 ((prod_type) == TTAPI_PROD_TYPE_DEBT)		? TTAPI_TRUE	:	\
	 ((prod_type) == TTAPI_PROD_TYPE_INT_RAT)	? TTAPI_TRUE	:	\
	 ((prod_type) == TTAPI_PROD_TYPE_CB)		? TTAPI_TRUE	:	\
	 ((prod_type) == TTAPI_PROD_TYPE_CMDY)		? TTAPI_TRUE	:	\
	 ((prod_type) == TTAPI_PROD_TYPE_EB)		? TTAPI_TRUE	:	\
	 ((prod_type) == TTAPI_PROD_TYPE_CUR_RAT)	? TTAPI_TRUE	:	\
	 ((prod_type) == TTAPI_PROD_TYPE_SCT)		? TTAPI_TRUE	:  TTAPI_FALSE)
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define TTAPI_PROD_TYPE_IS_BASE(prod_type)							\
	TTAPI_MAP_TRUTH(((prod_type) == TTAPI_PROD_TYPE_STK)		||	\
					  ((prod_type) == TTAPI_PROD_TYPE_IDX)			||	\
					  ((prod_type) == TTAPI_PROD_TYPE_DEBT)		||	\
					  ((prod_type) == TTAPI_PROD_TYPE_INT_RAT)	||	\
					  ((prod_type) == TTAPI_PROD_TYPE_CMDY)		||	\
					  ((prod_type) == TTAPI_PROD_TYPE_CUR_RAT)	||	\
					  ((prod_type) == TTAPI_PROD_TYPE_SCT))
#define TTAPI_PROD_TYPE_IS_DERIVED(prod_type)						\
	((TTAPI_PROD_TYPE_IS_BASE(prod_type) == TTAPI_TRUE) ?			\
	TTAPI_FALSE : TTAPI_TRUE)
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define TTAPI_PROD_TYPE_NAME_1(prod_type)									\
	(((prod_type) == TTAPI_PROD_TYPE_NONE)  	? "NONE"				:	\
	 ((prod_type) == TTAPI_PROD_TYPE_FUTURE)	? "FUTURE"			:	\
	 ((prod_type) == TTAPI_PROD_TYPE_OPTION)	? "OPTION"			:	\
	 ((prod_type) == TTAPI_PROD_TYPE_SPREAD)	? "SPREAD"			:	\
	 ((prod_type) == TTAPI_PROD_TYPE_STK)		? "STOCK"			:	\
	 ((prod_type) == TTAPI_PROD_TYPE_IDX)		? "INDEX"			:	\
	 ((prod_type) == TTAPI_PROD_TYPE_DEBT)		? "DEBT"				:	\
	 ((prod_type) == TTAPI_PROD_TYPE_INT_RAT)	? "INTEREST_RATE"	:	\
	 ((prod_type) == TTAPI_PROD_TYPE_CB)		? "CB"				:	\
	 ((prod_type) == TTAPI_PROD_TYPE_CMDY)		? "COMMODITY"		:	\
	 ((prod_type) == TTAPI_PROD_TYPE_EB)		? "EB"				:	\
	 ((prod_type) == TTAPI_PROD_TYPE_CUR_RAT)	? "CURRENCY_RATE"	:	\
	 ((prod_type) == TTAPI_PROD_TYPE_SCT)		? "SECTOR"			:	\
	 NULL)
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define TTAPI_PROD_TYPE_NAME_2(prod_type)									\
	(((prod_type) == TTAPI_PROD_TYPE_NONE)  	? "NONE"				:	\
	 ((prod_type) == TTAPI_PROD_TYPE_FUT)		? "FUT"				:	\
	 ((prod_type) == TTAPI_PROD_TYPE_OPT)		? "OPT"				:	\
	 ((prod_type) == TTAPI_PROD_TYPE_SPD)		? "SPD"				:	\
	 ((prod_type) == TTAPI_PROD_TYPE_STK)		? "STK"				:	\
	 ((prod_type) == TTAPI_PROD_TYPE_IDX)		? "IDX"				:	\
	 ((prod_type) == TTAPI_PROD_TYPE_BND)		? "BND"				:	\
	 ((prod_type) == TTAPI_PROD_TYPE_INT_RAT)	? "INT_RAT"			:	\
	 ((prod_type) == TTAPI_PROD_TYPE_CNV_BND)	? "CNV_BND"			:	\
	 ((prod_type) == TTAPI_PROD_TYPE_CMDY)		? "CMDY"				:	\
	 ((prod_type) == TTAPI_PROD_TYPE_EXC_BND)	? "EXC_BND"			:	\
	 ((prod_type) == TTAPI_PROD_TYPE_CUR_RAT)	? "CUR_RAT"			:	\
	 ((prod_type) == TTAPI_PROD_TYPE_SCT)		? "SCT"				:	\
	 NULL)
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define TTAPI_PROD_TYPE_TEXT(prod_type)										\
	(((prod_type) == TTAPI_PROD_TYPE_NONE)  	? "none"					:	\
	 ((prod_type) == TTAPI_PROD_TYPE_FUTURE)	? "future"				:	\
	 ((prod_type) == TTAPI_PROD_TYPE_OPTION)	? "option"				:	\
	 ((prod_type) == TTAPI_PROD_TYPE_SPREAD)	? "spread"				:	\
	 ((prod_type) == TTAPI_PROD_TYPE_STK)		? "stock"				:	\
	 ((prod_type) == TTAPI_PROD_TYPE_IDX)		? "index"				:	\
	 ((prod_type) == TTAPI_PROD_TYPE_DEBT)		? "bond"					:	\
	 ((prod_type) == TTAPI_PROD_TYPE_INT_RAT)	? "interest rate"		:	\
	 ((prod_type) == TTAPI_PROD_TYPE_CB)		? "convertible bond"	:	\
	 ((prod_type) == TTAPI_PROD_TYPE_CMDY)		? "commodity"			:	\
	 ((prod_type) == TTAPI_PROD_TYPE_EB)		? "exchangable bond"	:	\
	 ((prod_type) == TTAPI_PROD_TYPE_CUR_RAT)	? "currency rate"		:	\
	 ((prod_type) == TTAPI_PROD_TYPE_SCT)		? "sector"				:	\
	 NULL)
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define TTAPI_PROD_GROUP_NAME_1(prod_group)								\
	(((prod_group) == TT_FUT_IDX)    ? "FUTURE_INDEX"				:	\
	 ((prod_group) == TT_FUT_INT)    ? "FUTURE_INTEREST_RATE"	:	\
	 ((prod_group) == TT_FUT_COM)    ? "FUTURE_COMMODITY"			:	\
	 ((prod_group) == TT_OPT_IDX)    ? "OPTION_INDEX"				:	\
	 ((prod_group) == TT_OPT_INT)    ? "OPTION_INTEREST_RATE"	:	\
	 ((prod_group) == TT_OPT_COM)    ? "OPTION_COMMODITY"			:	\
	 ((prod_group) == TT_OPT_STK)    ? "OPTION_STOCK"				:	\
	 ((prod_group) == TT_OPT_BOND)   ? "OPTION_BOND"				:	\
	 ((prod_group) == TT_OPT_FUTURE) ? "OPTION_FUTURE"				:	\
	 NULL)
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define TTAPI_PROD_GROUP_NAME_2(prod_group)						\
	(((prod_group) == TT_FUT_IDX)    ? "FUT_IDX"				:	\
	 ((prod_group) == TT_FUT_INT)    ? "FUT_INT"				:	\
	 ((prod_group) == TT_FUT_COM)    ? "FUT_COM"				:	\
	 ((prod_group) == TT_OPT_IDX)    ? "OPT_IDX"				:	\
	 ((prod_group) == TT_OPT_INT)    ? "OPT_INT"				:	\
	 ((prod_group) == TT_OPT_COM)    ? "OPT_COM"				:	\
	 ((prod_group) == TT_OPT_STK)    ? "OPT_STK"				:	\
	 ((prod_group) == TT_OPT_BOND)   ? "OPT_BOND"			:	\
	 ((prod_group) == TT_OPT_FUTURE) ? "OPT_FUTURE"			:	\
	 NULL)
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define TTAPI_PROD_GROUP_NAME_TEXT(prod_group)							\
	(((prod_group) == TT_FUT_IDX)    ? "index future"				:	\
	 ((prod_group) == TT_FUT_INT)    ? "interest rate future"	:	\
	 ((prod_group) == TT_FUT_COM)    ? "commodity future"			:	\
	 ((prod_group) == TT_OPT_IDX)    ? "index option"				:	\
	 ((prod_group) == TT_OPT_INT)    ? "interest rate option"	:	\
	 ((prod_group) == TT_OPT_COM)    ? "commodity option"			:	\
	 ((prod_group) == TT_OPT_STK)    ? "stock option"				:	\
	 ((prod_group) == TT_OPT_BOND)   ? "bond option"				:	\
	 ((prod_group) == TT_OPT_FUTURE) ? "futures option"			:	\
	 NULL)
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef struct {
	int  tt_exchange_id;
	char tt_exchange_name[TTAPI_MAX_EXCHANGE_NAME + 1];
} TTAPI_EXCHANGE_DATA;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef struct {
	int  tt_price_type_id;
	char tt_price_type_name[TTAPI_MAX_PRICE_TYPE_NAME + 1];
} TTAPI_PRICE_TYPE_DATA;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef struct {
	int  tt_product_type_id;
	char tt_product_type_name[TTAPI_MAX_PRODUCT_TYPE_NAME + 1];
} TTAPI_PRODUCT_TYPE_DATA;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef struct {
	int  tt_product_group_id;
	char tt_product_group_name[TTAPI_MAX_PRODUCT_GROUP_NAME + 1];
	char tt_product_group_description[20 + 1];
} TTAPI_PRODUCT_GROUP_DATA;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef struct {
	int  tt_product_status_id;
	char tt_product_status_name[TTAPI_MAX_PRODUCT_STATUS_NAME + 1];
} TTAPI_PRODUCT_STATUS_DATA;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef struct {
	char member_id[TTAPI_TT_MEMBER_ID_LEN + 1];
	char group_id[TTAPI_TT_TRADER_GROUP_LEN + 1];
	char trader_id[TTAPI_TT_TRADER_ID_LEN + 1];
	char password[TTAPI_TT_USER_PASS_LEN + 1];
	char clearing_member[TTAPI_TT_ACCOUNT_LEN + 1];
	char default_account[TTAPI_TT_EXCH_ACCOUNT_LEN + 1];
	char hand_off_trader_id[TTAPI_TT_TRADER_ID_LEN + 1];
	char server_name[1023 + 1];
} TTAPI_ACCT_SPEC;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef struct {
	TTAPI_ACCT_SPEC acct_spec;
	char            exchange_name[TTAPI_MAX_EXCHANGE_NAME + 1];
	int             exchange_id;
	int             encrypt_flag;
} TTAPI_CONN_SPEC;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef unsigned long TTAPI_ReqTypeClass;
typedef unsigned long TTAPI_ReqType;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define TTAPI_ReqTypeClass_SET(in_name, in_value)	\
	static const TTAPI_ReqTypeClass in_name = (in_value);
TTAPI_ReqTypeClass_SET(TTAPI_ReqTypeClass___NONE,	0)
TTAPI_ReqTypeClass_SET(TTAPI_ReqTypeClass___MIN,	1)
TTAPI_ReqTypeClass_SET(TTAPI_ReqTypeClass___PRICE,	1)
TTAPI_ReqTypeClass_SET(TTAPI_ReqTypeClass___FILLS,	2)
TTAPI_ReqTypeClass_SET(TTAPI_ReqTypeClass___ORDER,	3)
TTAPI_ReqTypeClass_SET(TTAPI_ReqTypeClass___LIMIT,	4)
TTAPI_ReqTypeClass_SET(TTAPI_ReqTypeClass___MAX,	4)
#undef TTAPI_ReqTypeClass_SET
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define TTAPI_ReqType_SET(in_name, in_value)	\
	static const TTAPI_ReqType in_name = (in_value);
TTAPI_ReqType_SET(TTAPI_ReqType___NONE,											    0)
TTAPI_ReqType_SET(TTAPI_ReqType___MIN,												  	 1)

TTAPI_ReqType_SET(TTAPI_ReqType___PRICE_RequestExchangeList,					 1)
TTAPI_ReqType_SET(TTAPI_ReqType___PRICE_RequestGAL,								 2)
TTAPI_ReqType_SET(TTAPI_ReqType___PRICE_OpenExchangePrices,					    3)
TTAPI_ReqType_SET(TTAPI_ReqType___PRICE_CloseExchangePrices,					 4)
TTAPI_ReqType_SET(TTAPI_ReqType___PRICE_ReqServerApplStatus,					 5)
TTAPI_ReqType_SET(TTAPI_ReqType___PRICE_SubscribeTheoPrices,					 6)
TTAPI_ReqType_SET(TTAPI_ReqType___PRICE_UnsubscribeTheoPrices,				    7)
TTAPI_ReqType_SET(TTAPI_ReqType___PRICE_SubscribeProductPrices,				 8)
TTAPI_ReqType_SET(TTAPI_ReqType___PRICE_UnsubscribeProductPrices,				 9)
TTAPI_ReqType_SET(TTAPI_ReqType___PRICE_RequestAllProducts,						10)
TTAPI_ReqType_SET(TTAPI_ReqType___PRICE_RequestMktOverviewPrices,				11)
TTAPI_ReqType_SET(TTAPI_ReqType___PRICE_RequestAggregateMktOverviewPrices,	12)
TTAPI_ReqType_SET(TTAPI_ReqType___PRICE_RequestDetailMktOverviewPrices,		13)
TTAPI_ReqType_SET(TTAPI_ReqType___PRICE_AddStrikeCallback,						14)
TTAPI_ReqType_SET(TTAPI_ReqType___PRICE_RemoveStrikeCallback,					15)
TTAPI_ReqType_SET(TTAPI_ReqType___PRICE_QueryProducts,							16)
TTAPI_ReqType_SET(TTAPI_ReqType___PRICE_SubscribeRFQC,							17)
TTAPI_ReqType_SET(TTAPI_ReqType___PRICE_PublishTheoPrices,						18)

TTAPI_ReqType_SET(TTAPI_ReqType___FILLS_RequestExchangeList,					19)
TTAPI_ReqType_SET(TTAPI_ReqType___FILLS_ReqServerApplStatus,					20)
TTAPI_ReqType_SET(TTAPI_ReqType___FILLS_RequestGAL,								21)
TTAPI_ReqType_SET(TTAPI_ReqType___FILLS_OpenExchangeFills,						22)
TTAPI_ReqType_SET(TTAPI_ReqType___FILLS_CloseExchangeFills,						23)
TTAPI_ReqType_SET(TTAPI_ReqType___FILLS_RequestFillsToday,						24)
TTAPI_ReqType_SET(TTAPI_ReqType___FILLS_RequestFillsFromSeq,					25)
TTAPI_ReqType_SET(TTAPI_ReqType___FILLS_RequestStartOfDayPositions,			26)
TTAPI_ReqType_SET(TTAPI_ReqType___FILLS_ConfirmBofFill,							27)

TTAPI_ReqType_SET(TTAPI_ReqType___ORDER_RequestExchangeList,					28)
TTAPI_ReqType_SET(TTAPI_ReqType___ORDER_OpenExchangeOrders,						29)
TTAPI_ReqType_SET(TTAPI_ReqType___ORDER_CloseExchangeOrders,					30)
TTAPI_ReqType_SET(TTAPI_ReqType___ORDER_ReqServerApplStatus,					31)
TTAPI_ReqType_SET(TTAPI_ReqType___ORDER_RequestOrdersToday,						32)
TTAPI_ReqType_SET(TTAPI_ReqType___ORDER_SubmitRFQC,								33)
TTAPI_ReqType_SET(TTAPI_ReqType___ORDER_AddQuote,									34)
TTAPI_ReqType_SET(TTAPI_ReqType___ORDER_DeleteQuote,								35)
TTAPI_ReqType_SET(TTAPI_ReqType___ORDER_AddMassQuote,								36)
TTAPI_ReqType_SET(TTAPI_ReqType___ORDER_DeleteMassQuote,							37)
TTAPI_ReqType_SET(TTAPI_ReqType___ORDER_RequestSeriesCreate,					38)
TTAPI_ReqType_SET(TTAPI_ReqType___ORDER_RouteTTOrder,								39)
TTAPI_ReqType_SET(TTAPI_ReqType___ORDER_RouteTTCrossOrder,						40)
TTAPI_ReqType_SET(TTAPI_ReqType___ORDER_RequestGAL,								41)

TTAPI_ReqType_SET(TTAPI_ReqType___LIMIT_OpenLimitsAdmin,							42)
TTAPI_ReqType_SET(TTAPI_ReqType___LIMIT_RequestLoadAllData,						43)
TTAPI_ReqType_SET(TTAPI_ReqType___LIMIT_RequestDeleteLCTrader,					44)
TTAPI_ReqType_SET(TTAPI_ReqType___LIMIT_Publish,									44)

TTAPI_ReqType_SET(TTAPI_ReqType___MAX,													45)
#undef TTAPI_ReqType_SET
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef unsigned long TTAPI_RepClass;
typedef unsigned long TTAPI_RepType;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define TTAPI_RepType_SET(in_name, in_value)	\
	static const TTAPI_RepType in_name = (in_value);

TTAPI_RepType_SET(TTAPI_RepType___NONE,											    0)
TTAPI_RepType_SET(TTAPI_RepType___MIN,												  	 1)
TTAPI_RepType_SET(TTAPI_RepType___ORDER_OnOrderAccept,						  	 1)
TTAPI_RepType_SET(TTAPI_RepType___ORDER_OnOrderReject,						  	 2)
TTAPI_RepType_SET(TTAPI_RepType___ORDER_OnOrderReview,						  	 3)
TTAPI_RepType_SET(TTAPI_RepType___MAX,												  	 3)

#undef TTAPI_RepType_SET
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef struct {
	char ticker_core[STR_sizeof(TT_SERIES_ID_TYPE, prod.prod_chr)];
	char short_name[31 + 1];
	char long_name[63 + 1];
} TTAPI_TICKER_CORE;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef struct {
	char                  ticker_name[STR_sizeof(TT_SERIES_ID_TYPE, prod.prod_chr)];
	char                  ticker_core[STR_sizeof(TT_SERIES_ID_TYPE, prod.prod_chr)];
	TT_PROD_ID            prod_id;
	TT_PROD_GROUP_ID_CODE prod_group_id;
	TTAPI_PROD_TYPE       prod_type;
	TTAPI_PROD_TYPE       under_prod_type;
	TTAPI_PROD_TYPE       under_under_type;
	char                  prod_name[127 + 1];
} TTAPI_TICKER_PROD;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef struct {
	char              ticker[STR_sizeof(TT_SERIES_ID_TYPE, prod.prod_chr)];
	char              ticker_core[STR_sizeof(TT_SERIES_ID_TYPE, prod.prod_chr)];
	TTAPI_TICKER_CORE ticker_core_data;
	TTAPI_TICKER_PROD ticker_prod_data;
	unsigned int      exp_year_val;
	unsigned int      exp_month_val;
	char              exp_year_txt[4 + 1];
	char              exp_month_txt[2 + 1];
	double            strike_val;
	char              strike_txt[10 + 1 + 1];
	char              version[1 + 1];
	char              callput[1 + 1];
	double            tick_size;
	unsigned int      contr_exp_year_val;
	unsigned int      contr_exp_month_val;
	unsigned int      contr_exp_day_val;
	char              contr_exp_year_txt[4 + 1];
	char              contr_exp_month_txt[2 + 1];
	char              contr_exp_day_txt[2 + 1];
	char              near_ticker[STR_sizeof(TT_SERIES_ID_TYPE, prod.prod_chr)];
	char              near_ticker_core[STR_sizeof(TT_SERIES_ID_TYPE, prod.prod_chr)];
	unsigned int      near_year_val;
	unsigned int      near_month_val;
	char              near_year_txt[4 + 1];
	char              near_month_txt[2 + 1];
	char              far_ticker[STR_sizeof(TT_SERIES_ID_TYPE, prod.prod_chr)];
	char              far_ticker_core[STR_sizeof(TT_SERIES_ID_TYPE, prod.prod_chr)];
	unsigned int      far_year_val;
	unsigned int      far_month_val;
	char              far_year_txt[4 + 1];
	char              far_month_txt[2 + 1];
	unsigned int      spread_month_val;
	char              spread_month_txt[3 + 1];
	TT_SERIES_ID_TYPE series_id;
	int               user_sint_1;
	int               user_sint_2;
	int               user_sint_3;
	char              user_char_1[127 + 1];
	char              user_char_2[127 + 1];
	char              user_char_3[127 + 1];
} TTAPI_SERIES_ID_DATA;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
static const unsigned int TTAPI_ReqTypeClassShortName = 5;
static const unsigned int TTAPI_ReqTypeClassLongName  =
	(3 + TTAPI_ReqTypeClassShortName + 8);
static const unsigned int TTAPI_ReqTypeShortName      = 36;
static const unsigned int TTAPI_ReqTypeLongName       =
	(TTAPI_ReqTypeClassLongName + 2 + TTAPI_ReqTypeShortName);
/*	***********************************************************************	*/

/*
	ADF NOTE:No ADF.
*/
/*	***********************************************************************	*/
#define TTAPI_RVMSG_MAX_SUB_MSG			256
/*	***********************************************************************	*/

/*
	ADF NOTE:No ADF.
*/
/*	***********************************************************************	*/
#define TTAPI_RVMSG_SINT64					((rvmsg_Type) INT_MIN)
#define TTAPI_RVMSG_UINT64					((rvmsg_Type) INT_MAX)
/*	***********************************************************************	*/

/*
	ADF NOTE:No ADF.
*/
/*	***********************************************************************	*/
typedef struct {
	char         struct_name[63 + 1];
	char         rv_name[100 + 1];
	unsigned int member_offset;
	unsigned int member_length;
	rvmsg_Type   rv_data_type;
	rvmsg_Size   rv_data_size;
	char         member_name[63 + 1];
	char         rv_data_type_name[63 + 1];
	unsigned int inner_depth;
	unsigned int parent_index;
} TTAPI_RV_DATA_MAP;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* Function prototypes for functions defined within 'ttapi.a' . . .			*/
/*	***********************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Connection specification management function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void TTAPI_CONN_FreeSpec,
	(TTAPI_CONN_SPEC *ptr));
COMPAT_FN_DECL(void TTAPI_CONN_FreeSpecList,
	(unsigned int *in_count, TTAPI_CONN_SPEC **in_list));
COMPAT_FN_DECL(void TTAPI_CONN_InitSpec,
	(TTAPI_CONN_SPEC *ptr));
COMPAT_FN_DECL(void TTAPI_CONN_InitSpecList,
	(unsigned int in_count, TTAPI_CONN_SPEC *in_list));
COMPAT_FN_DECL(int  TTAPI_CONN_ParseAppendSpec,
	(const char *in_string, unsigned int *out_count, TTAPI_CONN_SPEC **out_list,
	char *error_text));
COMPAT_FN_DECL(int  TTAPI_CONN_ParseSpec,
	(const char *in_string, TTAPI_CONN_SPEC *spec_ptr, char *error_text));
COMPAT_FN_DECL(int  TTAPI_CONN_ParseSpecList,
	(unsigned int in_count, char **in_list, unsigned int *out_count,
	TTAPI_CONN_SPEC **out_list, char *error_text));
COMPAT_FN_DECL(int TTAPI_CONN_MakeSpec, (const char *exchange_name,
	int encrypt_flag, const char *acct_string, TTAPI_CONN_SPEC *spec_ptr,
	char *error_text));
COMPAT_FN_DECL(int TTAPI_CONN_MakeSpecList,
	(const char *exchange_name, int encrypt_flag, unsigned int in_count,
	char **in_list, unsigned int *out_count, TTAPI_CONN_SPEC **out_list,
	char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Account specification management function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void TTAPI_ACCT_FreeSpec,
	(TTAPI_ACCT_SPEC *ptr));
COMPAT_FN_DECL(void TTAPI_ACCT_FreeSpecList,
	(unsigned int *in_count, TTAPI_ACCT_SPEC **in_list));
COMPAT_FN_DECL(void TTAPI_ACCT_InitSpec,
	(TTAPI_ACCT_SPEC *ptr));
COMPAT_FN_DECL(void TTAPI_ACCT_InitSpecList,
	(unsigned int in_count, TTAPI_ACCT_SPEC *in_list));
COMPAT_FN_DECL(int  TTAPI_ACCT_ParseAppendSpec,
	(const char *in_string, const char *separator_list, unsigned int *out_count,
	TTAPI_ACCT_SPEC **out_list, char *error_text));
COMPAT_FN_DECL(int  TTAPI_ACCT_ParseSpec,
	(const char *in_string, const char *separator_list,
	TTAPI_ACCT_SPEC *spec_ptr, char *error_text));
COMPAT_FN_DECL(int  TTAPI_ACCT_ParseSpecList,
	(unsigned int in_count, char **in_list, const char *separator_list,
	unsigned int *out_count, TTAPI_ACCT_SPEC **out_list, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		TT exchange name/identifier conversion function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int TTAPI_GetTTExchangeId,
	(const char *tt_exchange_name));
COMPAT_FN_DECL(const char *TTAPI_GetTTExchangeName,
	(int tt_exchange_id));
COMPAT_FN_DECL(int TTAPI_GetTTExchangeIdBasic,
	(const char *tt_exchange_name));
COMPAT_FN_DECL(const char *TTAPI_GetTTExchangeNameBasic,
	(int tt_exchange_id));
COMPAT_FN_DECL(int         TTAPI_TTExchangeNameToTTExchangeId,
	(const char *tt_exchange_name));
COMPAT_FN_DECL(const char *TTAPI_TTExchangeIdToTTExchangeName,
	(int tt_exchange_id, char *tt_exchange_name));
COMPAT_FN_DECL(int         TTAPI_TTExchangeNameToTTExchangeIdBasic,
	(const char *tt_exchange_name, int *tt_exchange_id, char *error_text));
COMPAT_FN_DECL(int         TTAPI_TTExchangeIdToTTExchangeNameBasic,
	(int tt_exchange_id, char *tt_exchange_name, char *error_text));
COMPAT_FN_DECL(int         TTAPI_GetTTExchangeList,
	(unsigned int *exchange_count, TTAPI_EXCHANGE_DATA **exchange_list,
	char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		TT price type name/identifier conversion function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int TTAPI_GetTTPriceTypeId,
	(const char *tt_price_type_name));
COMPAT_FN_DECL(const char *TTAPI_GetTTPriceTypeName,
	(int tt_price_type_id));
COMPAT_FN_DECL(int TTAPI_GetTTPriceTypeIdBasic,
	(const char *tt_price_type_name));
COMPAT_FN_DECL(const char *TTAPI_GetTTPriceTypeNameBasic,
	(int tt_price_type_id));
COMPAT_FN_DECL(int         TTAPI_TTPriceTypeNameToTTPriceTypeId,
	(const char *tt_price_type_name));
COMPAT_FN_DECL(const char *TTAPI_TTPriceTypeIdToTTPriceTypeName,
	(int tt_price_type_id, char *tt_price_type_name));
COMPAT_FN_DECL(int         TTAPI_TTPriceTypeNameToTTPriceTypeIdBasic,
	(const char *tt_price_type_name, int *tt_price_type_id,
	char *error_text));
COMPAT_FN_DECL(int         TTAPI_TTPriceTypeIdToTTPriceTypeNameBasic,
	(int tt_price_type_id, char *tt_price_type_name, char *error_text));
COMPAT_FN_DECL(int         TTAPI_GetTTPriceTypeList,
	(unsigned int *price_type_count,
	TTAPI_PRICE_TYPE_DATA **price_type_list, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		TT product group name/identifier conversion function protogroups . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int TTAPI_GetTTProductGroupId,
	(const char *tt_product_type_name));
COMPAT_FN_DECL(const char *TTAPI_GetTTProductGroupName,
	(int tt_product_type_id));
COMPAT_FN_DECL(int TTAPI_GetTTProductGroupIdBasic,
	(const char *tt_product_type_name));
COMPAT_FN_DECL(const char *TTAPI_GetTTProductGroupNameBasic,
	(int tt_product_type_id));
COMPAT_FN_DECL(int         TTAPI_TTProductGroupNameToTTProductGroupId,
	(const char *tt_product_group_name));
COMPAT_FN_DECL(const char *TTAPI_TTProductGroupIdToTTProductGroupName,
	(int tt_product_group_id, char *tt_product_group_name));
COMPAT_FN_DECL(int         TTAPI_TTProductGroupNameToTTProductGroupIdBasic,
	(const char *tt_product_group_name, int *tt_product_group_id,
	char *error_text));
COMPAT_FN_DECL(int         TTAPI_TTProductGroupIdToTTProductGroupNameBasic,
	(int tt_product_group_id, char *tt_product_group_name, char *error_text));
COMPAT_FN_DECL(int         TTAPI_GetTTProductGroupList,
	(unsigned int *product_group_count,
	TTAPI_PRODUCT_GROUP_DATA **product_group_list, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		TT product status name/identifier conversion function protostatuss . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int TTAPI_GetTTProductStatusId,
	(const char *tt_product_status_name));
COMPAT_FN_DECL(const char *TTAPI_GetTTProductStatusName,
	(int tt_product_status_id));
COMPAT_FN_DECL(int TTAPI_GetTTProductStatusIdBasic,
	(const char *tt_product_status_name));
COMPAT_FN_DECL(const char *TTAPI_GetTTProductStatusNameBasic,
	(int tt_product_status_id));
COMPAT_FN_DECL(int         TTAPI_TTProductStatusNameToTTProductStatusId,
	(const char *tt_product_status_name));
COMPAT_FN_DECL(const char *TTAPI_TTProductStatusIdToTTProductStatusName,
	(int tt_product_status_id, char *tt_product_status_name));
COMPAT_FN_DECL(int         TTAPI_TTProductStatusNameToTTProductStatusIdBasic,
	(const char *tt_product_status_name, int *tt_product_status_id,
	char *error_text));
COMPAT_FN_DECL(int         TTAPI_TTProductStatusIdToTTProductStatusNameBasic,
	(int tt_product_status_id, char *tt_product_status_name, char *error_text));
COMPAT_FN_DECL(int         TTAPI_GetTTProductStatusList,
	(unsigned int *product_status_count,
	TTAPI_PRODUCT_STATUS_DATA **product_status_list, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		TT product type name/identifier conversion function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int TTAPI_GetTTProductTypeId,
	(const char *tt_product_type_name));
COMPAT_FN_DECL(const char *TTAPI_GetTTProductTypeName,
	(int tt_product_type_id));
COMPAT_FN_DECL(int TTAPI_GetTTProductTypeIdBasic,
	(const char *tt_product_type_name));
COMPAT_FN_DECL(const char *TTAPI_GetTTProductTypeNameBasic,
	(int tt_product_type_id));
COMPAT_FN_DECL(int         TTAPI_TTProductTypeNameToTTProductTypeId,
	(const char *tt_product_type_name));
COMPAT_FN_DECL(const char *TTAPI_TTProductTypeIdToTTProductTypeName,
	(int tt_product_type_id, char *tt_product_type_name));
COMPAT_FN_DECL(int         TTAPI_TTProductTypeNameToTTProductTypeIdBasic,
	(const char *tt_product_type_name, int *tt_product_type_id,
	char *error_text));
COMPAT_FN_DECL(int         TTAPI_TTProductTypeIdToTTProductTypeNameBasic,
	(int tt_product_type_id, char *tt_product_type_name, char *error_text));
COMPAT_FN_DECL(int         TTAPI_GetTTProductTypeList,
	(unsigned int *product_type_count,
	TTAPI_PRODUCT_TYPE_DATA **product_type_list, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		TT 'UserContext' structure management function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int TTAPI_CreateTTUserContextHandle,
	(void *app_handle, void *app_instance,
	UserContextHandle *user_context_handle, char *error_text));
COMPAT_FN_DECL(int TTAPI_CreateTTUserContext,
	(void *app_handle, void *app_instance, UserContext *user_context,
	char *error_text));
COMPAT_FN_DECL(int TTAPI_DestroyTTUserContextHandle,
	(UserContextHandle *user_context_handle, char *error_text));
COMPAT_FN_DECL(int TTAPI_DestroyTTUserContext,
	(UserContext *user_context, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Date and time data conversion function prototypes . . .
		*****************************************************************	*/
char         *TTAPI_TTDateTimeToTimevalString(const TT_DATE_STRUCT *tt_date_ptr,
	const TT_TIME_TYPE *tt_time_ptr, char *out_string);
char         *TTAPI_TTDateToTimevalString(const TT_DATE_STRUCT *tt_date_ptr,
	char *out_string);
char         *TTAPI_TTDateToContractDateString(
	const TT_DATE_STRUCT *tt_date_ptr, char *out_string);
char         *TTAPI_TTDateToDateString(const TT_DATE_TYPE *tt_date_ptr,
	char *out_string);
char         *TTAPI_TTTimeToTimeString(const TT_TIME_TYPE *tt_time_ptr,
	char *out_string);
char         *TTAPI_TTDateTimeToString(const TT_DATE_STRUCT *tt_date_ptr,
	const TT_TIME_TYPE *tt_time_ptr, char *out_string);
char         *TTAPI_TTTimeToTimeStringUSecs(const TT_TIME_TYPE *tt_time_ptr,
	char *out_string);
char         *TTAPI_TTTimeToTimeStringBasic(const TT_TIME_TYPE *tt_time_ptr,
	char *out_string);
TT_DATE_TYPE *TTAPI_GetCurrentDate(TT_DATE_TYPE *tt_date_ptr);
TT_TIME_TYPE *TTAPI_GetCurrentTime(TT_TIME_TYPE *tt_time_ptr);
void          TTAPI_GetCurrentDateTime(TT_DATE_TYPE *tt_date_ptr,
	TT_TIME_TYPE *tt_time_ptr);
TT_DATE_TYPE *TTAPI_GetDateFromTimeVal(const struct timeval *in_time,
	TT_DATE_TYPE *tt_date_ptr);
TT_TIME_TYPE *TTAPI_GetTimeFromTimeVal(const struct timeval *in_time,
	TT_TIME_TYPE *tt_time_ptr);
void          TTAPI_GetDateTimeFromTimeVal(const struct timeval *in_time,
	TT_DATE_TYPE *tt_date_ptr, TT_TIME_TYPE *tt_time_ptr);
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Request description function prototypes . . .
		*****************************************************************	*/
char *TTAPI_DescribeTTReqError(TTAPI_ReqType req_type, int tt_req_id,
	char *error_text);
char *TTAPI_DescribeTTReqError(const char *tt_object_name,
	const char *tt_req_name, int tt_req_id, char *error_text);
char *TTAPI_DescribeTTReqErrorPrice(const char *tt_req_name, int tt_req_id,
	char *error_text);
char *TTAPI_DescribeTTReqErrorFill(const char *tt_req_name, int tt_req_id,
	char *error_text);
char *TTAPI_DescribeTTReqErrorOrder(const char *tt_req_name, int tt_req_id,
	char *error_text);
char *TTAPI_DescribeTTReqErrorLimit(const char *tt_req_name, int tt_req_id,
	char *error_text);
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Request type management function prototypes . . .
		*****************************************************************	*/
int                 TTAPI_CheckReqTypeClass(TTAPI_ReqTypeClass req_type_class,
	char *error_text);
int                 TTAPI_CheckReqType(TTAPI_ReqType req_type,
	char *error_text);
int                 TTAPI_CheckReqTypeInClass(TTAPI_ReqTypeClass req_type_class,
	TTAPI_ReqType req_type, char *error_text);
int                 TTAPI_IsReqTypeClass(TTAPI_ReqTypeClass req_type_class);
int                 TTAPI_IsReqType(TTAPI_ReqType req_type);
int                 TTAPI_IsReqTypeInClass(TTAPI_ReqTypeClass req_type_class,
	TTAPI_ReqType req_type);
TTAPI_ReqTypeClass  TTAPI_GetReqTypeClassFromReqType(TTAPI_ReqType req_type);
char               *TTAPI_GetReqTypeClassNameShort(
	TTAPI_ReqTypeClass req_type_class, char *req_type_class_name);
char               *TTAPI_GetReqTypeNameShort(TTAPI_ReqType req_type,
	char *req_type_name);
char               *TTAPI_GetReqTypeClassNameLong(
	TTAPI_ReqTypeClass req_type_class, char *req_type_class_name);
char               *TTAPI_GetReqTypeNameLong(TTAPI_ReqType req_type,
	char *req_type_name);
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Request type management type detection function prototypes . . .
		*****************************************************************	*/
bool TTAPI_ReqTypeIsOpen(TTAPI_ReqType req_type);
bool TTAPI_ReqTypeIsClose(TTAPI_ReqType req_type);
bool TTAPI_ReqTypeIsAnytime(TTAPI_ReqType req_type);
bool TTAPI_ReqTypeIsMakeReady(TTAPI_ReqType req_type);
bool TTAPI_ReqTypeIsMakeNotReady(TTAPI_ReqType req_type);
bool TTAPI_ReqTypeIsSingleton(TTAPI_ReqType req_type);
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Price conversion function prototypes . . .
		*****************************************************************	*/
	// TTInt64 to double . . .
double TTAPI_PriceIntToDouble(TTInt64 in_value,
	const TT_SERIES_ID_TYPE *series_id);
double TTAPI_PriceIntToDouble(TTInt64 in_value, int precision, int decimals,
	const TT_SERIES_ID_TYPE *series_id = NULL);
double TTAPI_PriceIntToDouble(const TT_PRICE_TYPE *in_value,
	const TT_SERIES_ID_TYPE *series_id);
int    TTAPI_PriceIntToDouble(TTInt64 in_value,
	const TT_SERIES_ID_TYPE *series_id, double *out_value,
	char *error_text = NULL);
int    TTAPI_PriceIntToDouble(TTInt64 in_value, int precision, int decimals,
	const TT_SERIES_ID_TYPE *series_id, double *out_value,
	char *error_text = NULL);
int    TTAPI_PriceIntToDouble(const TT_PRICE_TYPE *in_value,
	const TT_SERIES_ID_TYPE *series_id, double *out_value, char *error_text);
	// Double to TTInt64 . . .
TTInt64 TTAPI_PriceDoubleToInt(double in_value,
	const TT_SERIES_ID_TYPE *series_id);
TTInt64 TTAPI_PriceDoubleToInt(double in_value, int precision,
	int decimals = 0, const TT_SERIES_ID_TYPE *series_id = NULL);
int     TTAPI_PriceDoubleToInt(double in_value,
	const TT_SERIES_ID_TYPE *series_id, TTInt64 *out_value,
	char *error_text = NULL);
int     TTAPI_PriceDoubleToInt(double in_value, int precision,
	int decimals, const TT_SERIES_ID_TYPE *series_id,
	TTInt64 *out_value, char *error_text = NULL);
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Consumer secondary thread startup and shutdown . . .
		*****************************************************************	*/
int  TTAPI_StartUpPrice(UserContext *user_context_ptr = NULL,
	int tt_api_version = TT_API_CURR_VERSION, char *error_text = NULL);
int  TTAPI_StartUpFill(UserContext *user_context_ptr = NULL,
	int tt_api_version = TT_API_CURR_VERSION, char *error_text = NULL);
int  TTAPI_StartUpOrder(UserContext *user_context_ptr = NULL,
	int tt_api_version = TT_API_CURR_VERSION, char *error_text = NULL);
int  TTAPI_StartUpLimit(UserContext *user_context_ptr = NULL,
	int tt_api_version = TT_API_CURR_VERSION, char *error_text = NULL);
void TTAPI_ShutDownPrice(void);
void TTAPI_ShutDownFill(void);
void TTAPI_ShutDownOrder(void);
void TTAPI_ShutDownLimit(void);
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Ticker product info lookup mapping function prototypes . . .
		*****************************************************************	*/
int TTAPI_GetTickerProdMap(const TT_PROD_ID_TYPE &prod_id,
	TTAPI_TICKER_PROD *prod_ptr = NULL, char *error_text = NULL);
int TTAPI_GetTickerProdMap(const TT_PROD_ID_TYPE *prod_id_ptr,
	TTAPI_TICKER_PROD *prod_ptr = NULL, char *error_text = NULL);
int TTAPI_GetTickerProdMap(int tt_exchange, const char *ticker_name,
	int prod_id, int prod_group_id, TTAPI_TICKER_PROD *prod_ptr = NULL,
	char *error_text = NULL);
int TTAPI_GetTickerProdMap(int tt_exchange, const char *ticker_name,
	TT_PROD_ID prod_id, TT_PROD_GROUP_ID_CODE prod_group_id,
	TTAPI_TICKER_PROD *prod_ptr = NULL, char *error_text = NULL);
int TTAPI_GetTickerProdMap(const char *tt_exchange, const char *ticker_name,
	int prod_id, int prod_group_id, TTAPI_TICKER_PROD *prod_ptr = NULL,
	char *error_text = NULL);
int TTAPI_GetTickerProdMap(const char *tt_exchange, const char *ticker_name,
	TT_PROD_ID prod_id, TT_PROD_GROUP_ID_CODE prod_group_id,
	TTAPI_TICKER_PROD *prod_ptr = NULL, char *error_text = NULL);
int TTAPI_GetTickerProdMap_CBOT(const TT_PROD_ID_TYPE &prod_id,
	TTAPI_TICKER_PROD *prod_ptr = NULL, char *error_text = NULL);
int TTAPI_GetTickerProdMap_CBOT(const TT_PROD_ID_TYPE *prod_id_ptr,
	TTAPI_TICKER_PROD *prod_ptr = NULL, char *error_text = NULL);
int TTAPI_GetTickerProdMap_CBOT(const char *ticker_name, int prod_id,
	int prod_group_id, TTAPI_TICKER_PROD *prod_ptr = NULL,
	char *error_text = NULL);
int TTAPI_GetTickerProdMap_CBOT(const char *ticker_name, TT_PROD_ID prod_id,
	TT_PROD_GROUP_ID_CODE prod_group_id, TTAPI_TICKER_PROD *prod_ptr = NULL,
	char *error_text = NULL);
int TTAPI_GetTickerProdMap_TTSIM(const TT_PROD_ID_TYPE &prod_id,
	TTAPI_TICKER_PROD *prod_ptr = NULL, char *error_text = NULL);
int TTAPI_GetTickerProdMap_TTSIM(const TT_PROD_ID_TYPE *prod_id_ptr,
	TTAPI_TICKER_PROD *prod_ptr = NULL, char *error_text = NULL);
int TTAPI_GetTickerProdMap_TTSIM(const char *ticker_name, int prod_id,
	int prod_group_id, TTAPI_TICKER_PROD *prod_ptr = NULL,
	char *error_text = NULL);
int TTAPI_GetTickerProdMap_TTSIM(const char *ticker_name, TT_PROD_ID prod_id,
	TT_PROD_GROUP_ID_CODE prod_group_id, TTAPI_TICKER_PROD *prod_ptr = NULL,
	char *error_text = NULL);
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Ticker core info lookup mapping function prototypes . . .
		*****************************************************************	*/
int TTAPI_GetTickerCoreMap(int tt_exchange, const char *ticker_core,
	TTAPI_TICKER_CORE *core_ptr = NULL, char *error_text = NULL);
int TTAPI_GetTickerCoreMap(const char *tt_exchange, const char *ticker_core,
	TTAPI_TICKER_CORE *core_ptr = NULL, char *error_text = NULL);
int TTAPI_GetTickerCoreMap_CBOT(const char *ticker_core,
	TTAPI_TICKER_CORE *core_ptr = NULL, char *error_text = NULL);
int TTAPI_GetTickerCoreMap_TTSIM(const char *ticker_core,
	TTAPI_TICKER_CORE *core_ptr = NULL, char *error_text = NULL);
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		RV data mapping function prototypes . . .
		*****************************************************************	*/
int        TTAPI_GetRVDataMapFill(unsigned int *out_map_count,
	TTAPI_RV_DATA_MAP **out_map_list, char *error_text = NULL);
int        TTAPI_GetRVDataMap(unsigned int in_map_count,
	const TTAPI_RV_DATA_MAP *in_map_list, unsigned int *out_map_count,
	TTAPI_RV_DATA_MAP **out_map_list, char *error_text = NULL);
int        TTAPI_GetRVDataMapInnerList(unsigned int in_map_count,
	const TTAPI_RV_DATA_MAP *in_map_list, unsigned int *sub_msg_count,
	char ***sub_msg_list, char *error_text);
rvmsg_Size TTAPI_GetRVDataMapLength(unsigned int in_map_count,
	const TTAPI_RV_DATA_MAP *in_map_list);
int        TTAPI_PublishRVDataFill(const char *subject_name,
	RVUtilrvmsg_Msg_TC &rv_msg_tc, RVUtilEnvO_TC &rv_env_tc,
	const TT_FILL_TYPE *out_data_ptr, unsigned int in_map_count,
	const TTAPI_RV_DATA_MAP *in_map_list, char *error_text = NULL);
int        TTAPI_PublishRVDataFill(const char *subject_name,
	rvmsg_Size msg_size, rvmsg_Msg msg_ptr, rv_Session session_handle,
	const TT_FILL_TYPE *out_data_ptr, unsigned int in_map_count,
	const TTAPI_RV_DATA_MAP *in_map_list, char *error_text = NULL);
int        TTAPI_PublishRVData(const char *subject_name,
	RVUtilrvmsg_Msg_TC &rv_msg_tc, RVUtilEnvO_TC &rv_env_tc,
	const char *out_data_name, const void *out_data_ptr,
	unsigned int in_map_count, const TTAPI_RV_DATA_MAP *in_map_list,
	char *error_text = NULL);
int        TTAPI_PublishRVData(const char *subject_name, rvmsg_Size msg_size,
	rvmsg_Msg msg_ptr, rv_Session session_handle, const char *out_data_name,
	const void *out_data_ptr, unsigned int in_map_count,
	const TTAPI_RV_DATA_MAP *in_map_list, char *error_text = NULL);
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		TT data structure check function prototypes . . .
		*****************************************************************	*/
int TTAPI_CheckTTSeriesId(const TT_SERIES_ID_TYPE *series_id_ptr,
	char *error_text);
int TTAPI_CheckTTProdId(const TT_PROD_ID_TYPE *prod_id_ptr, char *error_text);
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Data extraction function prototypes . . .
		*****************************************************************	*/
int TTAPI_ExtractSeriesIdData(const TT_SERIES_ID_TYPE *series_id_ptr,
	TTAPI_SERIES_ID_DATA *series_data, char *error_text);
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Miscellaneous data conversion function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(char *TTAPI_ServerKeyToString,
	(const TT_SERVER_KEY_TYPE server_key, char *out_string));
	/*	*****************************************************************	*/

/*	***********************************************************************	*/

#endif /* #ifndef HH__ttapi_h__HH */

