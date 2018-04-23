/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Canned Data Library Include File						*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the Tib/Rendezvous Utility Canned
								Data Library.

	Revision History	:	1996-01-02 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__RVUTLCD_H__h

#define h__RVUTLCD_H__h						1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*    Include necessary header files . . .                                 */
/*	***********************************************************************	*/

#include <sdtif.h>
#include <mfile.h>

#include "rvutili.h"

/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
typedef double CAN_PAD_TYPE;
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
typedef struct {
	struct timeval tick_time;
	unsigned int   name_length;
	unsigned int   reply_name_length;
	rvmsg_Type     msg_type;
	rvmsg_Size     msg_size;
	unsigned int   total_length;
} CAN_DATA;
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
typedef struct {
	CAN_DATA   header;
	rv_Name    name;
	rv_Name    reply_name;
	rvmsg_Data msg_data;
} CANR_DATA;
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
typedef struct {
	struct timeval tick_time;
	unsigned long  msecs;
	unsigned long  offset;
	unsigned int   length;
} CANR_TICK;
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
typedef struct {
	unsigned int  max_size;
	char         *data_buffer;
	unsigned int  tick_count;
	CANR_TICK    *tick_list;
} CANR_TICK_DIR;
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
typedef struct {
	RVUTIL_ENV         *env_ptr;
	RVUTIL_SIGNAL_SPEC *signal_ptr;
	MFILE              *mfile_ptr;
	char                adj_type[1 + 1];
	unsigned long       adj_msecs;
	int                 loop_flag;
	int                 show_flag;
	rvevm_EventId       log_event_id;
	rvevm_EventId       sync_event_id;
	rvevm_EventId       publish_event_id;
	rvevm_EventId       periodic_event_id;
	unsigned int        message_count;
	double              message_bytes;
	CANR_TICK_DIR       canr_tick_dir;
	unsigned int        publish_tick_index;
	unsigned int        exclude_count;
	RVUTIL_SNAME_FLAT  *exclude_list;
} RVUTIL_CAN_CONTROL;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Function prototypes for canned data functions . . .						*/
/*	***********************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Canned data playback function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void RVUTIL_CANR_InitCtl, (RVUTIL_CAN_CONTROL *can_ctl_ptr));
COMPAT_FN_DECL(void RVUTIL_CANR_InitTickDir, (CANR_TICK_DIR *ptr));
COMPAT_FN_DECL(void RVUTIL_CANR_FreeTickDir, (CANR_TICK_DIR *ptr));
COMPAT_FN_DECL(int  RVUTIL_CANR_BuildDirList, (MFILE *mfile_ptr,
	unsigned int tick_granularity, CANR_TICK_DIR *canr_tick_ptr,
	char *error_text));
COMPAT_FN_DECL(int  RVUTIL_CANR_BuildDirListBasic, (MFILE *mfile_ptr,
	unsigned int tick_granularity, unsigned int *max_size, char **data_buffer,
	unsigned int *tick_count, CANR_TICK **tick_list, char *error_text));
COMPAT_FN_DECL(void RVUTIL_CANR_SetTickTimes, (CANR_TICK_DIR *canr_tick_ptr,
	const char *adj_type, unsigned long adj_msecs, unsigned long delay_secs));
COMPAT_FN_DECL(int  RVUTIL_CANR_GetTick, (MFILE *mfile_ptr,
	const CANR_TICK *tick_ptr, CANR_DATA *tick_data, void *data_buffer,
	char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Canned data 'CAN_DATA' structure management function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int  RVUTIL_CAN_GetListCAN_DATA,
	(MFILE *mfile_ptr, unsigned int tick_granularity, unsigned int *tick_count,
	CAN_DATA **tick_list, char *error_text));
COMPAT_FN_DECL(int  RVUTIL_CAN_AppendListCAN_DATA,
	(MFILE *mfile_ptr, unsigned int tick_granularity, unsigned int *tick_count,
	CAN_DATA **tick_list, char *error_text));
COMPAT_FN_DECL(void RVUTIL_CAN_SortCAN_DATA,
	(unsigned int tick_count, CAN_DATA *tick_list));
COMPAT_FN_DECL(int RVUTIL_CAN_SCompareCAN_DATA,
	(void *control_ptr, const CAN_DATA *ptr_1, const CAN_DATA *ptr_2,
	size_t data_length));
COMPAT_FN_DECL(int  RVUTIL_CAN_CompareCAN_DATA,
	(const CAN_DATA *ptr_1, const CAN_DATA *ptr_2));
	/*	*****************************************************************	*/

/*	***********************************************************************	*/

#endif /* #ifndef h__RVUTLCD_H__h */

