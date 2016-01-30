/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	To support debugging.

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

#include <sdtif.h>

#include "rvutili.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
void RVUTIL_TEST_Callback(rv_Session session, rv_Name name, rv_Name reply_name,
	rvmsg_Type msg_type, rvmsg_Size msg_size, rvmsg_Data msg_data,
	rv_Opaque closure)
{
	rv_Opaque func_result;

	fprintf(stderr,
		"%s : %s = '%s', %s = '%s', %s = %d, %s = %u, %s = '%s', \
%s = 0x%p, %s = 0x%p\n",
		"Callback [Data]           ",
		"name", (name != NULL) ? name : "<NULL>",
	 	"reply name", (reply_name != NULL) ? reply_name : "<NULL>",
		"msg type", msg_type,
		"msg_size", ((unsigned int) msg_size),
		"msg data", (msg_data != NULL) ? ((char *) msg_data) : "<NULL>",
		"session", session,
		"closure", closure);

	rvmsg_Apply(session, msg_data, NULL, RVUTIL_TEST_Apply,
		NULL, &func_result);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void RVUTIL_TEST_EventCallback(rv_Session session, rv_Opaque closure,
	rvevm_EventType event_type, rvevm_EventId event_id)
{
	if (event_type != RVEVM_TIMER_EVENT) {
		fprintf(stderr,
			"Callback [Event]          : session = 0x%p, type = '%d', id = %lu\n",
			session, event_type, ((unsigned long) event_id));
		if (event_type == RVEVM_SIGNAL_EVENT) {
			fprintf(stderr, "********** Going down on signal . . .\n\n");
			RVUTIL_EndEnv(((RVUTIL_ENV *) closure), RVUTIL_FALSE);
		}
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void RVUTIL_TEST_FTCallback(rv_Session session, rv_Name name,
	rvft_Action action, rvft_Id id, rv_Opaque closure)
{
	fprintf(stderr,
		"%s [%s]: %s = '%s', %s = %d (%s), %s = %lu, %s = 0x%p, %s = 0x%p\n",
		"Callback", "Fault-tolerance",
		"name", name,
		"action", action, (action == RVFT_PREPARE_TO_ACTIVATE) ?
		"RVFT_PREPARE_TO_ACTIVATE" : (action == RVFT_ACTIVATE) ?
		"RVFT_ACTIVATE" : (action == RVFT_DEACTIVATE) ? "RVFT_ACTIVATE" :
		"*** UNKNOWN ***",
		"id", ((unsigned long) id),
		"session", session,
		"closure", closure);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
rv_Opaque RVUTIL_TEST_Apply(rv_Session session, rv_Name name,
	rvmsg_Type data_type, rvmsg_Size data_size, rvmsg_Data data,
	rv_Opaque closure)
{
	unsigned int   count_1;
#ifdef _Windows
	time_t         tmp_time;
#else
	struct timeval tmp_time;
#endif /* #ifdef _Windows */
	char           time_buffer[SDTIF_FMT_TIME_LEN_TIMEVAL + 1];
	char           msg_type_name[RVUTIL_MAX_RVMSG_TYPE_NAME + 1];

	printf("%-15s:%-15s:%10u:0x%p", name,
		RVUTIL_GetMsgTypeName(data_type, msg_type_name),
		((unsigned int) data_size),
		closure);

	switch (data_type) {
		case RVMSG_BADDATA	:
			printf(" ??? RVMSG_BADDATA ???");
			break;
		case RVMSG_RVMSG		:
			printf(" ??? RVMSG_RVMSG ???");
			break;
		case RVMSG_SUBJECT	:
			printf(" ??? RVMSG_SUBJECT ???");
			break;
		case RVMSG_DATETIME	:
#ifdef _Windows
			if ((rvmsg_DatetimeToTime_t(session, data_type, data_size,
				data, &tmp_time)) == RVMSG_OK)
				printf("[%s]", SDTIF_Format_time_t(&tmp_time, time_buffer));
#else
			if ((rvmsg_DatetimeToTimeval(session, data_type, data_size,
				data, &tmp_time)) == RVMSG_OK)
				printf("[%s]", SDTIF_Format_timeval(&tmp_time, time_buffer));
#endif /* #ifdef _Windows */
			break;
		case RVMSG_OPAQUE		:
			printf("[");
			for (count_1 = 0; count_1 < data_size; count_1++)
				printf("%s%02X", (count_1) ? " " : "",
					((unsigned char *) data)[count_1]);
			printf("]");
			break;
		case RVMSG_STRING		:
			printf("[%s]", ((char *) data));
			break;
		case RVMSG_BOOLEAN	:
			printf("[%d]", ((int) ((data_size == 1) ? *((char *) data) :
				(data_size == 2) ? *((short *) data) : *((int *) data))));
			break;
		case RVMSG_IPDATA		:
			if (data_size == 2)
				printf("[%u]", ((unsigned int) *((unsigned short *) data)));
			else if (data_size == 4)
				printf("[%u.%u.%u.%u]",
					((unsigned int) ((unsigned char *) data)[0]),
					((unsigned int) ((unsigned char *) data)[1]),
					((unsigned int) ((unsigned char *) data)[2]),
					((unsigned int) ((unsigned char *) data)[3]));
			break;
		case RVMSG_INT			:
			printf("[%d]", ((int) ((data_size == 1) ? *((char *) data) :
				(data_size == 2) ? *((short *) data) : *((int *) data))));
			break;
		case RVMSG_UINT		:
			printf("[%u]", ((int) ((data_size == 1) ? *((unsigned char *) data) :
				(data_size == 2) ? *((unsigned short *) data) :
				*((unsigned int *) data))));
			break;
		case RVMSG_REAL		:
			printf("[%f]",
				(data_size == 4) ? *((float *) data) : *((double *) data));
			break;
		case RVMSG_NONE		:
			printf("??? RVMSG_NONE ???");
			break;
		case RVMSG_ENCRYPTED	:
			printf("[");
			for (count_1 = 0; count_1 < data_size; count_1++)
				printf("%s%02X", (count_1) ? " " : "",
					((unsigned char *) data)[count_1]);
			printf("]");
			break;
		default					:
			printf("*** INVALID RV MSG DATA TYPE ***");
			break;
	}

	printf("\n");
	fflush(stdout);

	return(NULL);
}
/*	***********************************************************************	*/

