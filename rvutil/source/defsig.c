/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	The default signal-handling definitions, and
								functions to manage them.

	Revision History	:	1996-01-12 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <string.h>

#include <genfuncs.h>

#include "rvutili.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Data private to this module . . .												*/
/*	***********************************************************************	*/
const RVUTIL_SIGNAL RVUTIL_DefaultSignalList[] = {
#ifndef _Windows
	{	SIGHUP,	"SIGHUP",	NULL,	RVUTIL_SIGNAL_ACTION_EXIT			},
	{	SIGINT,	"SIGINT",	NULL,	RVUTIL_SIGNAL_ACTION_EXIT			},
	{	SIGQUIT, "SIGQUIT",	NULL,	RVUTIL_SIGNAL_ACTION_EXIT_FAST	},
	{	SIGABRT, "SIGABRT",	NULL,	RVUTIL_SIGNAL_ACTION_IGNORE		},
	{	SIGTERM, "SIGTERM",	NULL,	RVUTIL_SIGNAL_ACTION_EXIT_FAST	},
	{	SIGUSR1, "SIGUSR1",	NULL,	RVUTIL_SIGNAL_ACTION_IGNORE		},
	{	SIGUSR2,	"SIGUSR2",	NULL,	RVUTIL_SIGNAL_ACTION_IGNORE		},
	{	SIGCHLD,	"SIGCHLD",	NULL,	RVUTIL_SIGNAL_ACTION_IGNORE		},
	{	SIGPWR,	"SIGPWR",	NULL,	RVUTIL_SIGNAL_ACTION_IGNORE		},
	{	SIGWINCH,"SIGWINCH",	NULL,	RVUTIL_SIGNAL_ACTION_IGNORE		}
#else
	{	SIGINT,	"SIGINT",	NULL,	RVUTIL_SIGNAL_ACTION_EXIT_FAST	},
	{	SIGABRT, "SIGABRT",	NULL,	RVUTIL_SIGNAL_ACTION_IGNORE		},
	{	SIGTERM, "SIGTERM",	NULL,	RVUTIL_SIGNAL_ACTION_EXIT_FAST	}
#endif /* #ifndef _Windows */
};

const unsigned int  RVUTIL_DefaultSignalCount  =
	sizeof(RVUTIL_DefaultSignalList) / sizeof(RVUTIL_DefaultSignalList[0]);
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_GetDefaultSignalList(unsigned int *signal_count,
	RVUTIL_SIGNAL **signal_list, char *error_text)
{
	int return_code = RVUTIL_SUCCESS;

	if (mema_copy(RVUTIL_DefaultSignalCount, RVUTIL_DefaultSignalList,
		sizeof(**signal_list), signal_count, ((void **) signal_list))
		!= STRFUNCS_SUCCESS) {
		STR_AllocMsgList(RVUTIL_DefaultSignalCount, sizeof(**signal_list),
			error_text, "Unable to copy the default Rendezvous signal list");
		return_code = RVUTIL_MEMORY_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void RVUTIL_GetDefaultSignalSpec(RVUTIL_SIGNAL_SPEC *signal_spec)
{
	unsigned int count_1;

	memset(signal_spec, '\0', sizeof(*signal_spec));

	signal_spec->signal_count = RVUTIL_DefaultSignalCount;

	for (count_1 = 0; count_1 < signal_spec->signal_count; count_1++)
		signal_spec->signal_list[count_1] = RVUTIL_DefaultSignalList[count_1];
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_StartSignalHandling(RVUTIL_SIGNAL_SPEC *signal_spec,
	RVUTIL_ENV *env_ptr, rvevm_EventCallback event_call_back,
	void *user_data_ptr, char *error_text)
{
	int                return_code = RVUTIL_SUCCESS;
	unsigned int       count_1;
	RVUTIL_SIGNAL_SPEC tmp_signal_spec;
	char               snd_text[RVUTIL_MAX_ERROR_TEXT];
	char               tmp_error_text[RVUTIL_MAX_ERROR_TEXT];

	if (signal_spec == NULL)
		RVUTIL_GetDefaultSignalSpec(signal_spec = &tmp_signal_spec);

	for (count_1 = 0; count_1 < signal_spec->signal_count; count_1++) {
		if ((return_code = RVUTIL_rvevm_AddSignal(env_ptr->session_handle,
			&signal_spec->signal_list[count_1].signal_event_id,
			signal_spec->signal_list[count_1].signal_number,
			event_call_back, user_data_ptr, NULL, tmp_error_text)) !=
			RVUTIL_SUCCESS) {
			sprintf(error_text,
				"%s %d ('%s') (on session %s, session handle = 0x%lx): %s",
				"Signal interception event registration failed for signal",
				signal_spec->signal_list[count_1].signal_number,
				signal_spec->signal_list[count_1].signal_name,
				RVUTIL_SNDToStr(env_ptr, snd_text),
				((unsigned long) env_ptr->session_handle),
				tmp_error_text);
			break;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

