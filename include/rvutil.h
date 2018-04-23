/* *********************************************************************** */
/* *********************************************************************** */
/*	Tib/Rendezvous Utility Library Include File										*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the Tib/Rendezvous Utility Library.

	Revision History	:	1996-01-02 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

#ifndef h__RVUTIL_H__h

#define h__RVUTIL_H__h						1

/* *********************************************************************** */
/* *********************************************************************** */
/*    Include necessary header files . . .                                 */
/* *********************************************************************** */

#include <rv.h>
#include <rvcm.h>
#include <rvft.h>
#include <rvevm.h>

#include <mbcompat.h>

/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   BASE NAME   :  RVUTIL Truth Codes

   NAME        :  RVUTIL Truth Codes

   DESCRIPTION :  Manifest constants used within RVUTIL to specify the truth
						or falsity of expressions.

						(.) ''RVUTIL_TRUE''

						(.) ''RVUTIL_FALSE''

   NOTES       :  The manifest constant ''RVUTIL_TRUE'' should be defined as
						a non-zero value. Conversely, the manifest constant
						''RVUTIL_FALSE'' should be defined as zero (''0'').

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2018 Michael L. Brock

   OUTPUT INDEX:  RVUTIL_TRUE
						RVUTIL_FALSE
						RVUTIL Truth Codes:RVUTIL_TRUE
						RVUTIL Truth Codes:RVUTIL_FALSE
						RVUTIL Manifest Constants:RVUTIL_TRUE
						RVUTIL Manifest Constants:RVUTIL_FALSE
						RVUTIL Defines:RVUTIL_TRUE
						RVUTIL Defines:RVUTIL_FALSE
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:  RVUTIL Truth Codes
						RVUTIL Truth Code
						RVUTIL truth codes
						RVUTIL truth code
						RVUTIL_TRUE
						RVUTIL_FALSE

   PUBLISH NAME:	RVUTIL Truth Codes
						RVUTIL_TRUE
						RVUTIL_FALSE

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define RVUTIL_TRUE								1
#define RVUTIL_FALSE								0
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   BASE NAME   :	RVUTIL Return Codes

   NAME        :  RVUTIL Return Codes

   DESCRIPTION :  The RVUTIL return codes have the following meanings:

						(.) ''RVUTIL_SUCCESS'' means that the function invoked
						completed without error. ''RVUTIL_SUCCESS'' is guaranteed to
						be equal to zero (''0'').

						(.) ''RVUTIL_FAILURE'' indicates that the function invoked
						encountered a general operation failure. This is the
						'catch-all' error code for those errors which do not fit
						into category of one the other RVUTIL error codes.

						(.) ''RVUTIL_BAD_ARGS_FAILURE'' indicates that the
						arguments passed to a function invoked were invalid.

						(.) ''RVUTIL_MEMORY_FAILURE'' indicates that the memory
						required for operation of the function invoked could not be
						allocated.

						(.) ''RVUTIL_SYSTEM_FAILURE'' indicates that the function
						invoked encountered a failure of a standard library
						function or a system call.

						(.) ''RVUTIL_LOCK_ACQ_FAILURE'' indicates that a lock
						could not be acquired on a resource.

						(.) ''RVUTIL_RENDEZVOUS_FAILURE'' indicates that a failure
						occurred in a call to a Rendezvous method.

						(.) ''RVUTIL_INVALID_SUBJECT'' indicates that a subject
						name is invalid.

						(.) ''RVUTIL_INVALID_FULL_SUBJECT'' indicates that a
						subject name is not correctly formed as a fully-qualified
						subject name.

						(.) ''RVUTIL_INVALID_SUBJECT_ELEMENT'' indicates that
						one or more elements of a subject are invalid.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2018 Michael L. Brock

   OUTPUT INDEX:  RVUTIL_SUCCESS
						RVUTIL_FAILURE
						RVUTIL_BAD_ARGS_FAILURE
						RVUTIL_MEMORY_FAILURE
						RVUTIL_SYSTEM_FAILURE
						RVUTIL_LOCK_ACQ_FAILURE
						RVUTIL_RENDEZVOUS_FAILURE
						RVUTIL_INVALID_SUBJECT
						RVUTIL_INVALID_FULL_SUBJECT
						RVUTIL_INVALID_SUBJECT_ELEMENT
						RVUTIL Return Codes:RVUTIL_SUCCESS
						RVUTIL Return Codes:RVUTIL_FAILURE
						RVUTIL Return Codes:RVUTIL_BAD_ARGS_FAILURE
						RVUTIL Return Codes:RVUTIL_MEMORY_FAILURE
						RVUTIL Return Codes:RVUTIL_SYSTEM_FAILURE
						RVUTIL Return Codes:RVUTIL_LOCK_ACQ_FAILURE
						RVUTIL Return Codes:RVUTIL_RENDEZVOUS_FAILURE
						RVUTIL Return Codes:RVUTIL_INVALID_SUBJECT
						RVUTIL Return Codes:RVUTIL_INVALID_FULL_SUBJECT
						RVUTIL Return Codes:RVUTIL_INVALID_SUBJECT_ELEMENT
						RVUTIL Manifest Constants:RVUTIL_SUCCESS
						RVUTIL Manifest Constants:RVUTIL_FAILURE
						RVUTIL Manifest Constants:RVUTIL_BAD_ARGS_FAILURE
						RVUTIL Manifest Constants:RVUTIL_MEMORY_FAILURE
						RVUTIL Manifest Constants:RVUTIL_SYSTEM_FAILURE
						RVUTIL Manifest Constants:RVUTIL_LOCK_ACQ_FAILURE
						RVUTIL Manifest Constants:RVUTIL_RENDEZVOUS_FAILURE
						RVUTIL Manifest Constants:RVUTIL_INVALID_SUBJECT
						RVUTIL Manifest Constants:RVUTIL_INVALID_FULL_SUBJECT
						RVUTIL Manifest Constants:RVUTIL_INVALID_SUBJECT_ELEMENT
						RVUTIL Defines:RVUTIL_SUCCESS
						RVUTIL Defines:RVUTIL_FAILURE
						RVUTIL Defines:RVUTIL_BAD_ARGS_FAILURE
						RVUTIL Defines:RVUTIL_MEMORY_FAILURE
						RVUTIL Defines:RVUTIL_SYSTEM_FAILURE
						RVUTIL Defines:RVUTIL_LOCK_ACQ_FAILURE
						RVUTIL Defines:RVUTIL_RENDEZVOUS_FAILURE
						RVUTIL Defines:RVUTIL_INVALID_SUBJECT
						RVUTIL Defines:RVUTIL_INVALID_FULL_SUBJECT
						RVUTIL Defines:RVUTIL_INVALID_SUBJECT_ELEMENT
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:  RVUTIL_SUCCESS
						RVUTIL_FAILURE
						RVUTIL_BAD_ARGS_FAILURE
						RVUTIL_MEMORY_FAILURE
						RVUTIL_SYSTEM_FAILURE
						RVUTIL_LOCK_ACQ_FAILURE
						RVUTIL_RENDEZVOUS_FAILURE
						RVUTIL_INVALID_SUBJECT
						RVUTIL_INVALID_FULL_SUBJECT
						RVUTIL_INVALID_SUBJECT_ELEMENT
						RVUTIL Return Codes
						RVUTIL Return Code
						RVUTIL return codes
						RVUTIL return code
						RVUTIL Status Codes
						RVUTIL Status Code
						RVUTIL status codes
						RVUTIL status code
						RVUTIL Error Codes
						RVUTIL Error Code
						RVUTIL error codes
						RVUTIL error code

   PUBLISH NAME:	RVUTIL Return Codes
						RVUTIL return codes
						RVUTIL_SUCCESS
						RVUTIL_FAILURE
						RVUTIL_BAD_ARGS_FAILURE
						RVUTIL_MEMORY_FAILURE
						RVUTIL_SYSTEM_FAILURE
						RVUTIL_LOCK_ACQ_FAILURE
						RVUTIL_RENDEZVOUS_FAILURE
						RVUTIL_INVALID_SUBJECT
						RVUTIL_INVALID_FULL_SUBJECT
						RVUTIL_INVALID_SUBJECT_ELEMENT

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define RVUTIL_SUCCESS							 0
#define RVUTIL_FAILURE							-1
#define RVUTIL_BAD_ARGS_FAILURE				-2
#define RVUTIL_MEMORY_FAILURE					-3
#define RVUTIL_SYSTEM_FAILURE					-4
#define RVUTIL_LOCK_ACQ_FAILURE				-5
#define RVUTIL_RENDEZVOUS_FAILURE			-6
#define RVUTIL_INVALID_SUBJECT				-7
#define RVUTIL_INVALID_FULL_SUBJECT			-8
#define RVUTIL_INVALID_SUBJECT_ELEMENT		-9
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :  RVUTIL_MAX_ERROR_TEXT

   DESCRIPTION :  The manifest constant ''RVUTIL_MAX_ERROR_TEXT'' defines
						the minimum amount of storage which should be allocated to
						hold an error message returned by a RVUTIL function.

   CAVEATS     :  RVUTIL error messages can be quite lengthy. Therefore,
						attempting to save space by allocating less than
						''RVUTIL_MAX_ERROR_TEXT'' bytes to error message buffers
						passed to RVUTIL functions can lead to overwriting of the
						heap or the stack.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2018 Michael L. Brock

   OUTPUT INDEX:  RVUTIL_MAX_ERROR_TEXT
						RVUTIL Manifest Constants:RVUTIL_MAX_ERROR_TEXT
						RVUTIL Defines:RVUTIL_MAX_ERROR_TEXT
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	RVUTIL_MAX_ERROR_TEXT

   PUBLISH NAME:	RVUTIL_MAX_ERROR_TEXT

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define RVUTIL_MAX_ERROR_TEXT					2048
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/* *********************************************************************** */
#define RVUTIL_MAX_SUB_NAME_LEN			((unsigned int) RV_MAX_NAME)
#define RVUTIL_MAX_ELEMENT_LEN			255
#define RVUTIL_MAX_SUB_NAME_ELEMENTS	100
/* *********************************************************************** */

/*
	ADF NOTE: No ADF.
*/
/* *********************************************************************** */
#define RVUTIL_ELEMENT_SEP_CHAR			'.'
#define RVUTIL_ELEMENT_SEP_STR			"."
#define RVUTIL_ELEMENT_PATTERNCHAR_STR	"*>"
#define RVUTIL_ELEMENT_PAT_ANY_CHAR		'*'
#define RVUTIL_ELEMENT_PAT_ANY_STR 		"*"
#define RVUTIL_ELEMENT_PAT_LAST_CHAR	'>'
#define RVUTIL_ELEMENT_PAT_LAST_STR		">"
/* *********************************************************************** */

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define RVUTIL_MAX_CODE_STR_TEXT			63
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/* *********************************************************************** */
#define RVUTIL_MAX_SND_NAME_LEN			511
#define RVUTIL_MAX_SERVICE_NAME_LEN		RVUTIL_MAX_SND_NAME_LEN
#define RVUTIL_MAX_NETWORK_NAME_LEN		RVUTIL_MAX_SND_NAME_LEN
#define RVUTIL_MAX_DAEMON_NAME_LEN		RVUTIL_MAX_SND_NAME_LEN
/* *********************************************************************** */

/*
	ADF NOTE: No ADF.
*/
/* *********************************************************************** */
#define RVUTIL_MAX_RVFT_ACT_NAME			63
#define RVUTIL_MAX_RVEVM_EVNT_NAME		63
#define RVUTIL_MAX_RVEVM_IO_EVNT_NAME	63
#define RVUTIL_MAX_RVMSG_TYPE_NAME		63
/* *********************************************************************** */

/*
	ADF NOTE: No ADF.
*/
/* *********************************************************************** */
#define RVUTIL_SIGNAL_ACTION_NONE		0
#define RVUTIL_SIGNAL_ACTION_EXIT		1
#define RVUTIL_SIGNAL_ACTION_EXIT_FAST	2
#define RVUTIL_SIGNAL_ACTION_USER		3
#define RVUTIL_SIGNAL_ACTION_IGNORE		RVUTIL_SIGNAL_ACTION_NONE

#define RVUTIL_SIGNAL_ACTION_COUNT		4
#define RVUTIL_SIGNAL_ACTION_MIN			0
#define RVUTIL_SIGNAL_ACTION_MAX			3
#define RVUTIL_SIGNAL_ACTION_NAME_MAX	15
/* *********************************************************************** */

/*
	ADF NOTE: No ADF.
*/
/* *********************************************************************** */
#define RVUTIL_MAX_SIGNAL_NAME_LEN		32
#define RVUTIL_MAX_SIGNAL_COUNT			64
/* *********************************************************************** */

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define RVUTIL_FT_WEIGHT_MIN				((unsigned long) 1L)
#define RVUTIL_FT_WEIGHT_MAX				((unsigned long) 65535L)
#define RVUTIL_FT_ACTIVE_GOAL_MIN		((unsigned long) 1L)
#define RVUTIL_FT_ACTIVE_GOAL_MAX		((unsigned long) 65535L)
#define RVUTIL_FT_HEARTBEAT_MIN			((unsigned long) 1L)
#define RVUTIL_FT_HEARTBEAT_MAX			((unsigned long) 1000000L)
#define RVUTIL_FT_PREPARATION_MIN		((unsigned long) 0L)
#define RVUTIL_FT_PREPARATION_MAX		((unsigned long) 1000000L)
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef struct {
	int  code_value;
	char code_text[RVUTIL_MAX_CODE_STR_TEXT + 1];
} RVUTIL_CODE_STR_MAP;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable:4820)
#endif /* #ifdef _MSC_VER */

typedef struct {
	unsigned int  element_count;
	char         *element_list[RVUTIL_MAX_SUB_NAME_ELEMENTS];
	char          subject_name[RVUTIL_MAX_SUB_NAME_LEN + 1];
} RVUTIL_SNAME_WORK;

#ifdef _MSC_VER
# pragma warning(pop)
#endif /* #ifdef _MSC_VER */

typedef struct {
	unsigned int element_count;
	char         element_list[RVUTIL_MAX_SUB_NAME_ELEMENTS]
						[RVUTIL_MAX_ELEMENT_LEN + 1];
} RVUTIL_SNAME_FLAT;

typedef struct {
	unsigned int   element_count;
	char         **element_list;
} RVUTIL_SNAME;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable:4820)
#endif /* #ifdef _MSC_VER */

typedef struct {
	char        subject_name[RVUTIL_MAX_SUB_NAME_LEN + 1];
	rv_Callback call_back_function;
	rv_ListenId listen_id;
} RVUTIL_SUB;

#ifdef _MSC_VER
# pragma warning(pop)
#endif /* #ifdef _MSC_VER */
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef struct {
	char           service[RVUTIL_MAX_SERVICE_NAME_LEN + 1];
	char           network[RVUTIL_MAX_NETWORK_NAME_LEN + 1];
	char           daemon[RVUTIL_MAX_DAEMON_NAME_LEN + 1];
	void          *user_data_ptr;
	rvevm_Context  context;
	rv_Session     session_handle;
	unsigned int   sub_count;
	RVUTIL_SUB    *sub_list;
} RVUTIL_ENV;
/* *********************************************************************** */

/*
	ADF NOTE: No ADF.
*/
/* *********************************************************************** */
#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable:4820)
#endif /* #ifdef _MSC_VER */

typedef struct {
	RVUTIL_ENV    env;
	char          group_name[RVUTIL_MAX_SUB_NAME_LEN + 1];
	unsigned long weight;
	unsigned long active_goal;
	unsigned long heart_beat_interval;
	unsigned long preparation_interval;
	unsigned long activation_interval;
	rvft_Callback call_back_function;
	rvft_Id       group_id;
} RVUTIL_FT_ENV;

#ifdef _MSC_VER
# pragma warning(pop)
#endif /* #ifdef _MSC_VER */
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable:4820)
#endif /* #ifdef _MSC_VER */

typedef struct {
	int           signal_number;
	char          signal_name[RVUTIL_MAX_SIGNAL_NAME_LEN + 1];
	rvevm_EventId signal_event_id;
	int           action;
} RVUTIL_SIGNAL;

#ifdef _MSC_VER
# pragma warning(pop)
#endif /* #ifdef _MSC_VER */
/* *********************************************************************** */

/*
	ADF NOTE: No ADF.
*/
/* *********************************************************************** */
typedef struct {
	unsigned int  signal_count;
	RVUTIL_SIGNAL signal_list[RVUTIL_MAX_SIGNAL_COUNT];
} RVUTIL_SIGNAL_SPEC;
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Function prototypes for functions defined within 'rvutil.a' . . .		*/
/* *********************************************************************** */

	/* *****************************************************************
		*****************************************************************
		Core function prototypes . . .
		***************************************************************** */
COMPAT_FN_DECL(int   RVUTIL_AddSub, (RVUTIL_ENV *env_ptr,
	const char *subject_name, rv_Callback call_back, unsigned int *sub_index,
	char *error_text));
COMPAT_FN_DECL(int   RVUTIL_AddSubListen, (RVUTIL_ENV *env_ptr,
	const char *subject_name, rv_Callback call_back, rv_Opaque closure,
	unsigned int *sub_index, char *error_text));
COMPAT_FN_DECL(int   RVUTIL_AddSubList, (RVUTIL_ENV *env_ptr,
	unsigned int subject_count, char **subject_list, rv_Callback call_back,
	char *error_text));
COMPAT_FN_DECL(int   RVUTIL_AddSubListListen, (RVUTIL_ENV *env_ptr,
	unsigned int subject_count, char **subject_list, rv_Callback call_back,
	rv_Opaque closure, char *error_text));
COMPAT_FN_DECL(int   RVUTIL_CheckElement, (const char *element,
	char *error_text));
COMPAT_FN_DECL(int   RVUTIL_CheckElementIsFull, (const char *element,
	char *error_text));
COMPAT_FN_DECL(int   RVUTIL_CheckEnv, (const RVUTIL_ENV *env_ptr,
	char *error_text));
COMPAT_FN_DECL(int   RVUTIL_CheckFTEnv, (const RVUTIL_FT_ENV *ft_env_ptr,
	char *error_text));
COMPAT_FN_DECL(int   RVUTIL_CheckSignalList, (unsigned int signal_count,
	const RVUTIL_SIGNAL *signal_list, char *error_text));
COMPAT_FN_DECL(int   RVUTIL_CheckSignalSpec,
	(const RVUTIL_SIGNAL_SPEC *signal_spec, char *error_text));
COMPAT_FN_DECL(int   RVUTIL_CheckSubjectName, (const char *in_name,
	char *error_text));
COMPAT_FN_DECL(int   RVUTIL_CheckSubjectNameIsFull, (const char *in_name,
	char *error_text));
COMPAT_FN_DECL(void  RVUTIL_CloseEnv,
	(RVUTIL_ENV *env_ptr, int expedite_flag));
COMPAT_FN_DECL(void  RVUTIL_CloseFTEnv, (RVUTIL_FT_ENV *env_ptr,
	int expedite_flag));
COMPAT_FN_DECL(int   RVUTIL_CloseSub, (RVUTIL_ENV *env_ptr,
	unsigned int sub_index, char *error_text));
COMPAT_FN_DECL(int   RVUTIL_CrackSubjectName, (const char *in_name,
	RVUTIL_SNAME_WORK *out_name, char *error_text));
COMPAT_FN_DECL(int   RVUTIL_CrackSubjectWork, (const char *in_name,
	RVUTIL_SNAME_WORK *out_name, char *error_text));
COMPAT_FN_DECL(int   RVUTIL_CrackSubjectFlat, (const char *in_name,
	RVUTIL_SNAME_FLAT *out_name, char *error_text));
COMPAT_FN_DECL(void  RVUTIL_EndEnv,
	(RVUTIL_ENV *env_ptr, int expedite_flag));
COMPAT_FN_DECL(void  RVUTIL_EndFTEnv, (RVUTIL_FT_ENV *env_ptr,
	int expedite_flag));
COMPAT_FN_DECL(int   RVUTIL_GetDefaultSignalList, (unsigned int *signal_count,
	RVUTIL_SIGNAL **signal_list, char *error_text));
COMPAT_FN_DECL(int RVUTIL_CreateEnv, (const char *service, const char *network,
	const char *daemon, const char *subject_name, rv_Callback call_back,
	RVUTIL_ENV *env_ptr, char *error_text));
COMPAT_FN_DECL(int RVUTIL_CreateFTEnv, (const char *service,
	const char *network, const char *daemon, const char *subject_name,
	rv_Callback call_back, const char *group_name, unsigned long weight,
	unsigned long active_goal, unsigned long heart_beat_interval,
	unsigned long preparation_interval, unsigned long activation_interval,
	rvft_Callback ft_call_back, RVUTIL_FT_ENV *ft_env_ptr, char *error_text));
COMPAT_FN_DECL(void  RVUTIL_GetDefaultSignalSpec,
	(RVUTIL_SIGNAL_SPEC *signal_spec));
COMPAT_FN_DECL(char *RVUTIL_GetSignalActionName,
	(int action, char *action_name));
COMPAT_FN_DECL(void  RVUTIL_FreeEnv, (RVUTIL_ENV *env_ptr));
COMPAT_FN_DECL(void  RVUTIL_FreeFTEnv, (RVUTIL_FT_ENV *env_ptr));
COMPAT_FN_DECL(void  RVUTIL_FreeSub, (RVUTIL_SUB *sub_ptr));
COMPAT_FN_DECL(void  RVUTIL_InitEnv, (RVUTIL_ENV *env_ptr));
COMPAT_FN_DECL(void  RVUTIL_InitFTEnv, (RVUTIL_FT_ENV *env_ptr));
COMPAT_FN_DECL(void  RVUTIL_InitSub, (RVUTIL_SUB *sub_ptr));
COMPAT_FN_DECL(int   RVUTIL_JoinGroupFTEnv, (RVUTIL_FT_ENV *env_ptr,
	void *user_data_ptr, char *error_text));
COMPAT_FN_DECL(int   RVUTIL_ListenSub, (RVUTIL_ENV *env_ptr, rv_Opaque closure,
	unsigned int sub_index, char *error_text));
COMPAT_FN_DECL(int   RVUTIL_BeginListenEnv, (RVUTIL_ENV *env_ptr,
	void *user_data_ptr, char *error_text));
COMPAT_FN_DECL(int   RVUTIL_BeginListenFTEnv, (RVUTIL_FT_ENV *env_ptr,
	void *user_data_ptr, char *error_text));
COMPAT_FN_DECL(int   RVUTIL_RemoveSub, (RVUTIL_ENV *env_ptr,
	unsigned int sub_index, char *error_text));
COMPAT_FN_DECL(char *RVUTIL_SNDToStr, (const RVUTIL_ENV *env_ptr,
	char *out_string));
COMPAT_FN_DECL(int   RVUTIL_StartSessionEnv, (RVUTIL_ENV *env_ptr,
	char *error_text));
COMPAT_FN_DECL(int   RVUTIL_StartSessionFTEnv, (RVUTIL_FT_ENV *env_ptr,
	char *error_text));
COMPAT_FN_DECL(int   RVUTIL_StartSessionEnvContext, (RVUTIL_ENV *env_ptr,
	rvevm_Context context, char *error_text));
COMPAT_FN_DECL(int   RVUTIL_StartSessionFTEnvContext, (RVUTIL_FT_ENV *env_ptr,
	rvevm_Context context, char *error_text));
COMPAT_FN_DECL(int   RVUTIL_StartSessionEnvMakeContext,
	(RVUTIL_ENV *env_ptr, char *error_text));
COMPAT_FN_DECL(int   RVUTIL_StartSessionFTEnvMakeContext,
	(RVUTIL_FT_ENV *env_ptr, char *error_text));
COMPAT_FN_DECL(int   RVUTIL_StartSignalHandling,
	(RVUTIL_SIGNAL_SPEC *signal_spec, RVUTIL_ENV *env_ptr,
	rvevm_EventCallback event_call_back, void *user_data_ptr,
	char *error_text));
COMPAT_FN_DECL(int RVUTIL_WithdrawFromGroupFTEnv,
	(RVUTIL_FT_ENV *env_ptr, char *error_text));
COMPAT_FN_DECL(int RVUTIL_WithdrawAndReJoinGroupFTEnv,
	(RVUTIL_FT_ENV *env_ptr, void *user_data_ptr, char *error_text));
	/*	*****************************************************************	*/

	/* *****************************************************************
		*****************************************************************
		Single Pattern-matching support function prototypes . . .
		***************************************************************** */
COMPAT_FN_DECL(int   RVUTIL_MakeSubjectPattern, (const char *in_name,
	RVUTIL_SNAME_FLAT *out_pattern, char *error_text));
COMPAT_FN_DECL(int   RVUTIL_MatchSubject,
	(const char *in_name, const RVUTIL_SNAME_FLAT *in_pattern,
	unsigned int *element_index));
COMPAT_FN_DECL(int   RVUTIL_MatchSubjectFlat,
	(const RVUTIL_SNAME_FLAT *in_name, const RVUTIL_SNAME_FLAT *in_pattern,
	unsigned int *element_index));
COMPAT_FN_DECL(int   RVUTIL_MatchSubjectWork,
	(const RVUTIL_SNAME_WORK *in_name, const RVUTIL_SNAME_FLAT *in_pattern,
	unsigned int *element_index));
	/*	*****************************************************************	*/

	/* *****************************************************************
		*****************************************************************
		Multiple pattern-matching support function prototypes . . .
		***************************************************************** */
COMPAT_FN_DECL(int RVUTIL_MakeSubjectPatternList,
	(unsigned int in_count, char **in_list, unsigned int *out_count,
	RVUTIL_SNAME_FLAT **out_list, char *error_text));
COMPAT_FN_DECL(int RVUTIL_MatchSubjectPerList,
	(const char *in_name, unsigned int pattern_count,
	const RVUTIL_SNAME_FLAT *pattern_list, unsigned int *pattern_index,
	unsigned int *element_index));
COMPAT_FN_DECL(int RVUTIL_MatchSubjectWorkPerList,
	(const RVUTIL_SNAME_WORK *in_name, unsigned int pattern_count,
	const RVUTIL_SNAME_FLAT *pattern_list, unsigned int *pattern_index,
	unsigned int *element_index));
COMPAT_FN_DECL(int RVUTIL_MatchSubjectFlatPerList,
	(const RVUTIL_SNAME_FLAT *in_name, unsigned int pattern_count,
	const RVUTIL_SNAME_FLAT *pattern_list, unsigned int *pattern_index,
	unsigned int *element_index));
	/*	*****************************************************************	*/

	/* *****************************************************************
		*****************************************************************
		Find and comparison function prototypes . . .
		***************************************************************** */
COMPAT_FN_DECL(int RVUTIL_CompareSubByName, (void *control_ptr,
	const RVUTIL_SUB *ptr_1, const RVUTIL_SUB *ptr_2, size_t data_length));
COMPAT_FN_DECL(RVUTIL_SUB *RVUTIL_FindSubByListenID,
	(const RVUTIL_ENV *env_ptr, rv_ListenId listen_id,
	unsigned int *found_index));
COMPAT_FN_DECL(RVUTIL_SUB *RVUTIL_FindSubByName, (const RVUTIL_ENV *env_ptr,
	const char *subject_name, unsigned int *found_index));
	/*	*****************************************************************	*/

	/* *****************************************************************
		*****************************************************************
		Subject name storage conversion function prototypes . . .
		***************************************************************** */
COMPAT_FN_DECL(RVUTIL_SNAME_FLAT *RVUTIL_WorkToFlat,
	(const RVUTIL_SNAME_WORK *work_ptr, RVUTIL_SNAME_FLAT *flat_ptr));
	/*	*****************************************************************	*/

	/* *****************************************************************
		*****************************************************************
		Prototypes for RV type/name mapping functions . . .
		***************************************************************** */
COMPAT_FN_DECL(char *RVUTIL_GetActionNameRVFT, (rvft_Action action,
	char *action_name));
COMPAT_FN_DECL(char *RVUTIL_GetEventNameRVEVM, (rvevm_EventType event_type,
	char *event_name));
COMPAT_FN_DECL(char *RVUTIL_GetIOEventTypeRVEVM,
	(rvevm_IoEventType io_event_type, char *io_event_name));
COMPAT_FN_DECL(char *RVUTIL_GetMsgTypeName, (rvmsg_Type msg_type,
	char *msg_type_name));
	/*	*****************************************************************	*/

	/* *****************************************************************
		*****************************************************************
		Prototypes for RV error and return code mapping functions . . .
		***************************************************************** */
COMPAT_FN_DECL(char *RVUTIL_CodeToString, (unsigned int in_count,
	const RVUTIL_CODE_STR_MAP *in_list, int in_code, char *out_text));
COMPAT_FN_DECL(char *RVUTIL_CodeToString_rv_Error, (rv_Error in_code,
	char *out_text));
COMPAT_FN_DECL(char *RVUTIL_CodeToString_rvadv_Error, (rvadv_Error in_code,
	char *out_text));
COMPAT_FN_DECL(char *RVUTIL_CodeToString_rvcm_Error, (rvcm_Error in_code,
	char *out_text));
COMPAT_FN_DECL(char *RVUTIL_CodeToString_rvevm_Error, (rvevm_Returns in_code,
	char *out_text));
COMPAT_FN_DECL(char *RVUTIL_CodeToString_rvft_Error, (rvft_Error in_code,
	char *out_text));
COMPAT_FN_DECL(char *RVUTIL_CodeToString_rvmsg_Error, (rvmsg_Error in_code,
	char *out_text));
	/*	*****************************************************************	*/

	/* *****************************************************************
		*****************************************************************
		Prototypes for RV error and return code formatting functions . . .
		***************************************************************** */
COMPAT_FN_DECL(char *RVUTIL_FormatString_rv_Error, (rv_Session in_session,
	rv_Error in_code, char *out_text));
COMPAT_FN_DECL(char *RVUTIL_FormatString_rvadv_Error, (rv_Session in_session,
	rvadv_Error in_code, char *out_text));
COMPAT_FN_DECL(char *RVUTIL_FormatString_rvcm_Error, (rv_Session in_session,
	rvcm_Error in_code, char *out_text));
COMPAT_FN_DECL(char *RVUTIL_FormatString_rvevm_Error, (rv_Session in_session,
	rvevm_Returns in_code, char *out_text));
COMPAT_FN_DECL(char *RVUTIL_FormatString_rvft_Error, (rv_Session in_session,
	rvft_Error in_code, char *out_text));
COMPAT_FN_DECL(char *RVUTIL_FormatString_rvmsg_Error, (rv_Session in_session,
	rvmsg_Error in_code, char *out_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		RV function wrappers prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int RVUTIL_rv_Close, (rv_Session session, rv_ListenId listen_id,
	rv_Error *rv_code_ptr, char *error_text));
COMPAT_FN_DECL(int RVUTIL_rv_Init, (rv_Session *session, char *service,
	char *network, char *daemon, rv_Error *rv_code_ptr, char *error_text));
COMPAT_FN_DECL(int RVUTIL_rv_InitSession, (rv_Session *session,
	rvevm_Context context, char *service, char *network, char *daemon,
	rv_Error *rv_code_ptr, char *error_text));
COMPAT_FN_DECL(int RVUTIL_rv_ListenSubject, (rv_Session session,
	rv_ListenId *listen_id, rv_Name subject, rv_Callback callback,
	rv_Opaque closure, rv_Error *rv_code_ptr, char *error_text));
COMPAT_FN_DECL(int RVUTIL_rv_Rpc, (rv_Session session, rv_ListenId *listen_id,
	rv_Name name, rvmsg_Type msgType, rvmsg_Size msgSize, rvmsg_Data msg,
	rv_Callback callback, rv_Opaque closure, rv_Error *rv_code_ptr,
	char *error_text));
COMPAT_FN_DECL(int RVUTIL_rv_Send, (rv_Session session, rv_Name name,
	rvmsg_Type msgType, rvmsg_Size msgSize, rvmsg_Data msg,
	rv_Error *rv_code_ptr, char *error_text));
COMPAT_FN_DECL(int RVUTIL_rv_SendWithReply, (rv_Session session, rv_Name name,
	rv_Name replyName, rvmsg_Type msgType, rvmsg_Size msgSize, rvmsg_Data msg,
	rv_Error *rv_code_ptr, char *error_text));
COMPAT_FN_DECL(int RVUTIL_rv_Term, (rv_Session session, rv_Error *rv_code_ptr,
	char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		RVMSG function wrappers prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int RVUTIL_rvmsg_Append, (rv_Session session, rvmsg_Msg msg,
	rvmsg_Size msgLimit, rv_Name name, rvmsg_Type dataType, rvmsg_Size dataSize,
	rvmsg_Data data, rvmsg_Error *rv_code_ptr, char *error_text));
COMPAT_FN_DECL(int RVUTIL_rvmsg_Init,   (rv_Session session, rvmsg_Msg msg,
	rvmsg_Size msgLimit, rvmsg_Error *rv_code_ptr, char *error_text));
COMPAT_FN_DECL(int RVUTIL_rvmsg_Length, (rv_Session session, rvmsg_Msg msg,
	rvmsg_Size *length, rvmsg_Error *rv_code_ptr, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		RVEVM function wrappers prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int RVUTIL_rvevm_AddIo, (rv_Session session,
	rvevm_EventId *event_id_ptr, int socket_number,
	rvevm_IoEventType io_event_type, rvevm_EventCallback proc,
	rv_Opaque closure, rvevm_Returns *rv_code_ptr, char *error_text));
COMPAT_FN_DECL(int RVUTIL_rvevm_AddRepeatingTimer, (rv_Session session,
	rvevm_EventId *event_id_ptr, unsigned long interval,
	rvevm_EventCallback proc, rv_Opaque closure, rvevm_Returns *rv_code_ptr,
	char *error_text));
COMPAT_FN_DECL(int RVUTIL_rvevm_AddSignal, (rv_Session session,
	rvevm_EventId *event_id_ptr, int signal_number, rvevm_EventCallback proc,
	rv_Opaque closure, rvevm_Returns *rv_code_ptr, char *error_text));
COMPAT_FN_DECL(int RVUTIL_rvevm_AddTimer, (rv_Session session,
	rvevm_EventId *event_id_ptr, unsigned long interval,
	rvevm_EventCallback proc, rv_Opaque closure, rvevm_Returns *rv_code_ptr,
	char *error_text));
COMPAT_FN_DECL(int RVUTIL_rvevm_Destroy,
	(rvevm_Context context, rvevm_Returns *rv_code_ptr, char *error_text));
COMPAT_FN_DECL(int RVUTIL_rvevm_Make,
	(rvevm_Context *context, rvevm_Returns *rv_code_ptr, char *error_text));
COMPAT_FN_DECL(int RVUTIL_rvevm_RemoveIo, (rv_Session session,
	rvevm_EventId event_id, rvevm_Returns *rv_code_ptr, char *error_text));
COMPAT_FN_DECL(int RVUTIL_rvevm_RemoveSignal, (rv_Session session,
	rvevm_EventId event_id, rvevm_Returns *rv_code_ptr, char *error_text));
COMPAT_FN_DECL(int RVUTIL_rvevm_RemoveTimer, (rv_Session session,
	rvevm_EventId event_id, rvevm_Returns *rv_code_ptr, char *error_text));
COMPAT_FN_DECL(int RVUTIL_rvevm_ResetTimer, (rv_Session session,
	rvevm_EventId event_id, unsigned long interval, rvevm_Returns *rv_code_ptr,
	char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		RVFT function wrappers prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int RVUTIL_rvft_Join, (rv_Session session, rvft_Id *groupId,
	rv_Name group_name, unsigned long weight, unsigned long activeGoal,
	unsigned long heartbeatInterval, unsigned long preparationInterval,
	unsigned long activationInterval, rvft_Callback ftCallbackFn,
	rv_Opaque closureArg, rvft_Error *rv_code_ptr, char *error_text));
COMPAT_FN_DECL(int RVUTIL_rvft_Withdraw, (rv_Session session, rvft_Id groupId,
	rvft_Error *rv_code_ptr, char *error_text));
	/*	*****************************************************************	*/

	/* *****************************************************************
		*****************************************************************
			Function prototypes for version functions . . .
		***************************************************************** */
COMPAT_FN_DECL(void  RVUTIL_GetVersionNumber, (unsigned int *major,
	unsigned int *minor, unsigned int *release, unsigned int *build));
COMPAT_FN_DECL(char *RVUTIL_GetVersionString, (char *version_string));
	/*	*****************************************************************	*/

/* *********************************************************************** */

#endif /* #ifndef h__RVUTIL_H__h */

