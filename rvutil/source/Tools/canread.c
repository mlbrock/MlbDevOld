/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Executable Source Module									*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Plays back canned Rendezvous data.

	Revision History	:	1996-01-12 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <limits.h>
#include <string.h>

#include <genfuncs.h>

#include "rvutilcd.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
COMPAT_FN_DECL(       int  main,
	(int argc, char **argv));
COMPAT_FN_DECL_STATIC(void RVUTIL_CANR_ShowTickStats,
	(RVUTIL_CAN_CONTROL *control_ptr));
COMPAT_FN_DECL_STATIC(void RVUTIL_CANR_EventCallback,
	(rv_Session session, rv_Opaque closure, rvevm_EventType event_type,
	rvevm_EventId event_id));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int main(int argc, char **argv)
{
	int                  return_code    = RVUTIL_SUCCESS;
	const char          *file_name      = NULL;
	const char          *snd_service    = "";
	const char          *snd_network    = "";
	const char          *snd_daemon     = "";
	unsigned long        publish_period = 10L;
	unsigned long        delay_secs     = 10L;
	unsigned int         count_1;
	RVUTIL_ENV           env_data;
	RVUTIL_SIGNAL_SPEC   signal_spec;
	RVUTIL_CAN_CONTROL   control_data;
	struct timeval       start_time;
	char                 error_text[RVUTIL_MAX_ERROR_TEXT];

	RVUTIL_InitEnv(&env_data);
	RVUTIL_GetDefaultSignalSpec(&signal_spec);
	RVUTIL_CANR_InitCtl(&control_data);

	control_data.env_ptr            = &env_data;
	control_data.signal_ptr         = &signal_spec;
	control_data.mfile_ptr          = NULL;
	control_data.adj_type[0]        = '\0';
	control_data.adj_msecs          = 0L;
	control_data.loop_flag          = RVUTIL_FALSE;
	control_data.show_flag          = RVUTIL_FALSE;
	control_data.log_event_id       = NULL;
	control_data.sync_event_id      = NULL;
	control_data.periodic_event_id  = NULL;
	control_data.publish_event_id   = NULL;
	control_data.message_count      = 0;
	control_data.message_bytes      = 0.0;
	control_data.publish_tick_index = 0;
	control_data.exclude_count      = 0;
	control_data.exclude_list       = NULL;

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if ((!stricmp(argv[count_1], "-H")) ||
			(!stricmp(argv[count_1], "-HELP"))) {
			sprintf(error_text, "Help request with '%s' noted . . .",
				argv[count_1]);
			return_code = RVUTIL_BAD_ARGS_FAILURE;
			goto EXIT_FUNCTION;
		}
		else if (!stricmp(argv[count_1], "-FILE")) {
			if ((count_1 + 1) == ((unsigned int) argc)) {
				sprintf(error_text, "%s '%-.500s' parameter.",
					"Expected command-line qualifier to follow", argv[count_1]);
				return_code = RVUTIL_BAD_ARGS_FAILURE;
				goto EXIT_FUNCTION;
			}
			file_name = argv[++count_1];
		}
		else if (!stricmp(argv[count_1], "-SERVICE")) {
			if ((count_1 + 1) == ((unsigned int) argc)) {
				sprintf(error_text, "%s '%-.500s' parameter.",
					"Expected command-line qualifier to follow", argv[count_1]);
				return_code = RVUTIL_BAD_ARGS_FAILURE;
				goto EXIT_FUNCTION;
			}
			snd_service = argv[++count_1];
		}
		else if (!stricmp(argv[count_1], "-NETWORK")) {
			if ((count_1 + 1) == ((unsigned int) argc)) {
				sprintf(error_text, "%s '%-.500s' parameter.",
					"Expected command-line qualifier to follow", argv[count_1]);
				return_code = RVUTIL_BAD_ARGS_FAILURE;
				goto EXIT_FUNCTION;
			}
			snd_network = argv[++count_1];
		}
		else if (!stricmp(argv[count_1], "-DAEMON")) {
			if ((count_1 + 1) == ((unsigned int) argc)) {
				sprintf(error_text, "%s '%-.500s' parameter.",
					"Expected command-line qualifier to follow", argv[count_1]);
				return_code = RVUTIL_BAD_ARGS_FAILURE;
				goto EXIT_FUNCTION;
			}
			snd_daemon  = argv[++count_1];
		}
		else if (!stricmp(argv[count_1], "-PUBLISH")) {
			if ((count_1 + 1) == ((unsigned int) argc)) {
				sprintf(error_text, "%s '%-.500s' parameter.",
					"Expected command-line qualifier to follow", argv[count_1]);
				return_code = RVUTIL_BAD_ARGS_FAILURE;
				goto EXIT_FUNCTION;
			}
			else if (atoi(argv[++count_1]) > 0)
				publish_period = atoi(argv[count_1]);
		}
		else if (!stricmp(argv[count_1], "-ADJUST")) {
			if ((count_1 + 1) == ((unsigned int) argc)) {
				sprintf(error_text, "%s '%-.500s' parameter.",
					"Expected command-line qualifier to follow", argv[count_1]);
				return_code = RVUTIL_BAD_ARGS_FAILURE;
				goto EXIT_FUNCTION;
			}
			if ((strichr("CASMD", argv[++count_1][0]) == NULL) ||
				(!argv[count_1][1]) || (str_digit(argv[count_1] + 1, 0) != NULL) ||
				(atof(argv[count_1] + 1) < 1.0)) {
				sprintf(error_text, "Invalid '-ADJUST' parameter ('%-.500s').",
					argv[count_1]);
				return_code = RVUTIL_BAD_ARGS_FAILURE;
				goto EXIT_FUNCTION;
			}
			chrcpy(control_data.adj_type, argv[count_1][0]);
			control_data.adj_msecs = ((unsigned long) atof(argv[count_1] + 1));
		}
		else if (!stricmp(argv[count_1], "-SHOW"))
			control_data.show_flag = RVUTIL_TRUE;
		else if (!stricmp(argv[count_1], "-LOOP"))
			control_data.loop_flag = RVUTIL_TRUE;
	}

	if ((file_name == NULL) || (!(*file_name))) {
		strcpy(error_text, "No file name was specified on the command-line.");
		return_code = RVUTIL_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((control_data.mfile_ptr = mopen(file_name, "rb")) == NULL) {
		strcat(nstrcat(strcpy(error_text, "Unable to open canned data file '"),
			file_name, 500), "' for reading: ");
		GEN_AppendLastErrorString(0, RVUTIL_MAX_ERROR_TEXT, error_text);
		return_code = RVUTIL_SYSTEM_FAILURE;
		goto EXIT_FUNCTION;
	}

	fprintf(stderr, "Creating environment");
	if ((return_code = RVUTIL_CreateEnv(snd_service, snd_network,
		snd_daemon, NULL, NULL, &env_data, error_text)) != RVUTIL_SUCCESS)
		goto EXIT_FUNCTION;
	fprintf(stderr, "\n");

	fprintf(stderr, "Starting environment Rendezvous session");
	if ((return_code = RVUTIL_StartSessionEnv(&env_data, error_text)) !=
		RVUTIL_SUCCESS)
		goto EXIT_FUNCTION;
	fprintf(stderr, "\n");

	fprintf(stderr, "Initializing Rendezvous signal handling");
	if ((return_code = RVUTIL_StartSignalHandling(&signal_spec, &env_data,
		RVUTIL_CANR_EventCallback, &control_data, error_text)) != RVUTIL_SUCCESS)
		goto EXIT_FUNCTION;
	fprintf(stderr, "\n");

	fprintf(stderr, "Initializing Rendezvous publishing timer handling");
	if ((return_code = RVUTIL_rvevm_AddRepeatingTimer(env_data.session_handle,
		&control_data.publish_event_id, publish_period,
		RVUTIL_CANR_EventCallback, &control_data, NULL, error_text)) !=
		RVUTIL_SUCCESS)
		goto EXIT_FUNCTION;
	fprintf(stderr, "\n");

#ifdef _Windows
	fprintf(stderr, "Initializing Rendezvous periodic timer handling");
	if ((return_code = RVUTIL_rvevm_AddRepeatingTimer(env_data.session_handle,
		&control_data.periodic_event_id, 100L, RVUTIL_CANR_EventCallback,
		&control_data, NULL, error_text)) != RVUTIL_SUCCESS)
		goto EXIT_FUNCTION;
	fprintf(stderr, "\n");
#endif /* #ifdef _Windows */

/*
	fprintf(stderr, "*** ENTERING 'rv_MainLoop() ***\n");
	SDTIF_GetTimeUSecs(&start_time);
	rv_MainLoop(env_data.session_handle);
	fprintf(stderr, "*** RETURNED FROM 'rv_MainLoop() ***\n");

	fprintf(stderr, "%s:%10u messages, %20.0f bytes\n",
		SDTIF_Format_time_t(NULL, time_buffer),
		control_data.message_count, control_data.message_bytes);
*/


	if ((return_code = RVUTIL_CANR_BuildDirList(control_data.mfile_ptr, 0,
		&control_data.canr_tick_dir, error_text)) != RVUTIL_SUCCESS)
		goto EXIT_FUNCTION;
	RVUTIL_CANR_SetTickTimes(&control_data.canr_tick_dir, control_data.adj_type,
		control_data.adj_msecs, delay_secs);

/*
	for (count_1 = 0, tick_ptr = control_data.canr_tick_dir.tick_list;
		count_1 < control_data.canr_tick_dir.tick_count;
		count_1++, tick_ptr++) {
		if ((return_code = RVUTIL_CANR_GetTick(control_data.mfile_ptr, tick_ptr,
			&tick_data, control_data.canr_tick_dir.data_buffer, error_text)) !=
			RVUTIL_SUCCESS)
			goto EXIT_FUNCTION;
		printf("[%08u]:%s:%10lu / %10lu\n", count_1,
			SDTIF_Format_timeval(&tick_ptr-> tick_time, time_buffer),
			tick_ptr->msecs,
			tick_ptr->offset);
		fprintf(stderr,
	"          :%s:name=%s:reply=%s:msg_type=%d=%s:msg_size=%u:msg=[%s]\n",
			SDTIF_Format_timeval(&tick_data.header.tick_time, time_buffer),
			tick_data.name, tick_data.reply_name,
			tick_data.header.msg_type,
			RVUTIL_GetMsgTypeName(tick_data.header.msg_type, msg_type_name),
			((unsigned int) tick_data.header.msg_size),
			(tick_data.header.msg_type != RVMSG_STRING) ? "*** NOT A STRING ***" :
			((char *) tick_data.msg_data));
	}
*/

	if (control_data.canr_tick_dir.tick_list) {
		RVUTIL_CANR_ShowTickStats(&control_data);
		fprintf(stderr, "*** ENTERING 'rv_MainLoop() ***\n");
		SDTIF_GetTimeUSecs(&start_time);
		rv_MainLoop(env_data.session_handle);
		fprintf(stderr, "*** RETURNED FROM 'rv_MainLoop() ***\n");
	}

EXIT_FUNCTION:

	RVUTIL_CloseEnv(&env_data, RVUTIL_FALSE);

	if (control_data.mfile_ptr != NULL)
		mclose(control_data.mfile_ptr);

	RVUTIL_CANR_FreeTickDir(&control_data.canr_tick_dir);

	if (return_code == RVUTIL_BAD_ARGS_FAILURE)
		fprintf(stderr,
			"\n\n%s\n\nUSAGE: %s [ -h | -help ] %s %s %s %s %s %s %s\n\n",
			error_text,
			argv[0],
			"-file <message-file-name>",
			"[ -service <RV-service-string> ]",
			"[ -network <RV-network-string> ]",
			"[ -daemon <RV-daemon-string> ]",
			"[ -publish <publish-milliseconds> ]",
			"[ -loop ]",
			"[ -show ]");
	else if (return_code != RVUTIL_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return((return_code == RVUTIL_SUCCESS) ? EXIT_SUCCESS : EXIT_FAILURE);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static void RVUTIL_CANR_ShowTickStats(RVUTIL_CAN_CONTROL *control_ptr)
{
	char time_buffer[SDTIF_FMT_TIME_LEN_TIMEVAL + 1];

	STR_EMIT_CharLine('=', 78, NULL, stderr);

	fprintf(stderr, "Ticks Loaded   : %u\n",
		control_ptr->canr_tick_dir.tick_count);
	fprintf(stderr, "Current Time   : %s\n",
		SDTIF_Format_timeval(NULL, time_buffer));
	fprintf(stderr, "First Tick Time: %s\n",
		SDTIF_Format_timeval(&control_ptr->canr_tick_dir.tick_list
			[0].tick_time, time_buffer));
	fprintf(stderr, "Last Tick Time : %s\n",
		SDTIF_Format_timeval(&control_ptr->canr_tick_dir.tick_list
			[control_ptr->canr_tick_dir.tick_count - 1].tick_time,
			time_buffer));

	STR_EMIT_CharLine('=', 78, NULL, stderr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void RVUTIL_CANR_InitCtl(RVUTIL_CAN_CONTROL *ptr)
{
	memset(ptr, '\0', sizeof(*ptr));

	RVUTIL_CANR_InitTickDir(&ptr->canr_tick_dir);

	ptr->env_ptr            = NULL;
	ptr->signal_ptr         = NULL;
	ptr->mfile_ptr          = NULL;
	ptr->log_event_id       = NULL;
	ptr->sync_event_id      = NULL;
	ptr->message_count      = 0;
	ptr->message_bytes      = 0;
	ptr->publish_event_id   = NULL;
	ptr->publish_tick_index = 0;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void RVUTIL_CANR_InitTickDir(CANR_TICK_DIR *ptr)
{
	memset(ptr, '\0', sizeof(*ptr));

	ptr->max_size    = 0;
	ptr->data_buffer = NULL;
	ptr->tick_count  = 0;
	ptr->tick_list   = NULL;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void RVUTIL_CANR_FreeTickDir(CANR_TICK_DIR *ptr)
{
	if (ptr->data_buffer != NULL)
		free(ptr->data_buffer);

	if (ptr->tick_list != NULL)
		free(ptr->tick_list);

	RVUTIL_CANR_InitTickDir(ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_CANR_BuildDirList(MFILE *mfile_ptr, unsigned int tick_granularity,
	CANR_TICK_DIR *canr_tick_ptr, char *error_text)
{
	RVUTIL_CANR_InitTickDir(canr_tick_ptr);

	return(RVUTIL_CANR_BuildDirListBasic(mfile_ptr, tick_granularity,
		&canr_tick_ptr->max_size, &canr_tick_ptr->data_buffer,
		&canr_tick_ptr->tick_count, &canr_tick_ptr->tick_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_CANR_BuildDirListBasic(MFILE *mfile_ptr,
	unsigned int tick_granularity, unsigned int *max_size, char **data_buffer,
	unsigned int *tick_count, CANR_TICK **tick_list, char *error_text)
{
	int            return_code     = RVUTIL_SUCCESS;
	unsigned long  offset;
	unsigned long  file_size;
	const char    *file_name;
	CAN_DATA       can_data;
	CAN_DATA       last_can_data;
	CANR_TICK     *tmp_list;
	double         tmp_usecs;
	char           mfile_error_text[MFILE_MAX_ERROR_TEXT];

	*max_size        = 0;
	*data_buffer     = NULL;
	*tick_count      = 0;
	*tick_list       = NULL;

	tick_granularity = (tick_granularity) ? tick_granularity : 10000;

	mseek(mfile_ptr, 0, SEEK_SET);

	if ((return_code = MFILE_Lock(mfile_ptr, mfile_error_text)) ==
		MFILE_SUCCESS) {
		file_size   = MFILE_GetFileSize(mfile_ptr);
		offset      = MFILE_GetOffset(mfile_ptr);
		file_name   = MFILE_GetFileName(mfile_ptr);
		if ((return_code = MFILE_Unlock(mfile_ptr, mfile_error_text)) !=
			MFILE_SUCCESS) {
			nstrcpy(error_text, mfile_error_text, RVUTIL_MAX_ERROR_TEXT - 1);
			return_code = RVUTIL_MAP_ERROR_MFILE(return_code);
			goto EXIT_FUNCTION;
		}
		return_code = RVUTIL_MAP_ERROR_MFILE(return_code);
	}
	else {
		nstrcpy(error_text, mfile_error_text, RVUTIL_MAX_ERROR_TEXT - 1);
		return_code = RVUTIL_MAP_ERROR_MFILE(return_code);
		goto EXIT_FUNCTION;
	}

	memset(&last_can_data, '\0', sizeof(last_can_data));

	while ((offset + sizeof(CAN_DATA)) < file_size) {
		if (mread(&can_data, sizeof(can_data), 1, mfile_ptr) != 1) {
			sprintf(error_text, "%s %u %s '%-.500s'.",
				"Error occurred on attempt to read", sizeof(can_data),
				"bytes from the canned data file", file_name);
			return_code = RVUTIL_SYSTEM_FAILURE;
			goto EXIT_FUNCTION;
		}
		if (can_data.total_length < sizeof(CAN_DATA))
			break;
		if (can_data.total_length > *max_size)
			*max_size = can_data.total_length;
		if (!(*tick_count % tick_granularity)) {
			tmp_list = (!(*tick_count)) ?
				((CANR_TICK *) calloc(tick_granularity, sizeof(CANR_TICK))) :
				((CANR_TICK *) realloc(*tick_list,
				(*tick_count + tick_granularity) * sizeof(CANR_TICK)));
			if (tmp_list == NULL) {
				STR_AllocMsgList(*tick_count + tick_granularity,
					sizeof(CANR_TICK), error_text,
					"Unable to %sallocate the list of canned data entries",
					(!(*tick_count)) ? "" : "re-");
				return_code = RVUTIL_MEMORY_FAILURE;
				goto EXIT_FUNCTION;
			}
			*tick_list = tmp_list;
		}
		(*tick_list)[*tick_count].msecs  = 0;
		(*tick_list)[*tick_count].offset = offset;
		(*tick_list)[*tick_count].length = can_data.total_length;
		if (*tick_count) {
			tmp_usecs = (SDTIF_GET_TIMEVAL_USECS_DOUBLE(&can_data.tick_time) -
				SDTIF_GET_TIMEVAL_USECS_DOUBLE(&last_can_data.tick_time)) / 1000.0;
			(*tick_list)[*tick_count].msecs = (tmp_usecs <= 0.0) ? 0 :
				(tmp_usecs > ((double) ULONG_MAX)) ? ULONG_MAX :
				((unsigned long) tmp_usecs);
		}
		(*tick_count)++;
		last_can_data  = can_data;
		offset        += ((unsigned long) can_data.total_length);
		mseek(mfile_ptr, ((off_t) offset), SEEK_SET);
	}

	if (*tick_count) {
		if (*tick_count % tick_granularity)
			*tick_list = ((CANR_TICK *) realloc(*tick_list,
				*tick_count * sizeof(CANR_TICK)));
		if ((*data_buffer = ((char *) calloc(*max_size, sizeof(char)))) ==
			NULL) {
			STR_AllocMsgItem(*max_size, error_text,
				"Unable to allocate the canned data record buffer");
			return_code = RVUTIL_MEMORY_FAILURE;
			goto EXIT_FUNCTION;
		}
	}

EXIT_FUNCTION:

	if (return_code != RVUTIL_SUCCESS) {
		if (*tick_list != NULL)
			free(*tick_list);
		if (*data_buffer != NULL)
			free(*data_buffer);
		*max_size    = 0;
		*data_buffer = NULL;
		*tick_count  = 0;
		*tick_list   = NULL;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void RVUTIL_CANR_SetTickTimes(CANR_TICK_DIR *canr_tick_ptr,
	const char *adj_type, unsigned long adj_msecs, unsigned long delay_secs)
{
	unsigned int    count_1;
	char            tmp_adj_type;
	unsigned long   max_tick_msecs;
	struct timeval  this_time;
	CANR_TICK      *tick_ptr;

	if (!canr_tick_ptr->tick_count)
		return;

	if ((adj_type != NULL) && (strichr("CASMD", *adj_type) != NULL)) {
		tmp_adj_type = ((char) toupper(*adj_type));
		if (tmp_adj_type == 'A')
			max_tick_msecs = (ULONG_MAX - adj_msecs) / 1000L;
		else if (tmp_adj_type == 'M')
			max_tick_msecs = (ULONG_MAX / adj_msecs) / 1000L;
		else
			max_tick_msecs = 0L;
		for (count_1 = 1, tick_ptr = canr_tick_ptr->tick_list + 1;
			count_1 < canr_tick_ptr->tick_count; count_1++, tick_ptr++) {
			if (tmp_adj_type == 'C')
				tick_ptr->msecs = adj_msecs;
			else if (tmp_adj_type == 'A')
				tick_ptr->msecs = (tick_ptr->msecs > max_tick_msecs) ?
					max_tick_msecs : (tick_ptr->msecs + adj_msecs);
			else if (tmp_adj_type == 'S')
				tick_ptr->msecs = (tick_ptr->msecs < adj_msecs) ?
					0L : (tick_ptr->msecs - adj_msecs);
			else if (tmp_adj_type == 'M')
				tick_ptr->msecs = (tick_ptr->msecs > max_tick_msecs) ?
					max_tick_msecs : (tick_ptr->msecs * adj_msecs);
			else if (tmp_adj_type == 'D')
				tick_ptr->msecs /= adj_msecs;
		}
	}

	delay_secs = (delay_secs) ? delay_secs : 10L;
	SDTIF_GetTimeUSecs(&this_time);
	this_time.tv_sec                      += delay_secs;
	canr_tick_ptr->tick_list[0].tick_time  = this_time;

	for (count_1 = 1, tick_ptr = canr_tick_ptr->tick_list + 1;
		count_1 < canr_tick_ptr->tick_count; count_1++, tick_ptr++) {
		this_time.tv_usec   += tick_ptr->msecs * 1000L;
		this_time.tv_sec    += this_time.tv_usec  / 1000000L;
		this_time.tv_usec   %= 1000000L;
		tick_ptr->tick_time  = this_time;
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_CANR_GetTick(MFILE *mfile_ptr, const CANR_TICK *tick_ptr,
	CANR_DATA *tick_data, void *data_buffer, char *error_text)
{
	int return_code;

	mseek(mfile_ptr, ((off_t) tick_ptr->offset), SEEK_SET);

	if (mread(data_buffer, tick_ptr->length, 1, mfile_ptr) != 1) {
		sprintf(error_text, "%s %u %s '%-.500s'.",
			"Error occurred on attempt to read", tick_ptr->length,
			"bytes from the canned data file",
			MFILE_GetFileName(mfile_ptr));
		return_code = RVUTIL_SYSTEM_FAILURE;
	}
	else {
		memset(tick_data, '\0', sizeof(*tick_data));
		tick_data->header     = *((CAN_DATA *) data_buffer);
		tick_data->name       = ((rv_Name) (((char *) data_buffer) +
			sizeof(CAN_DATA)));
		tick_data->reply_name = ((rv_Name) (((char *) tick_data->name) +
			tick_data->header.name_length + 1));
		tick_data->msg_data   = ((rvmsg_Data) (((char *) tick_data->reply_name) +
			tick_data->header.reply_name_length + 1));
		return_code = RVUTIL_SUCCESS;
	}

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
static void RVUTIL_CANR_EventCallback(rv_Session session, rv_Opaque closure,
	rvevm_EventType event_type, rvevm_EventId event_id)
{
	int                 return_code;
	unsigned int        count_1;
	RVUTIL_SIGNAL      *signal_ptr;
	RVUTIL_CAN_CONTROL *control_ptr;
	struct timeval      this_time;
	CANR_TICK          *tick_ptr;
	CANR_DATA           tick_data;
	char                time_buffer[SDTIF_FMT_TIME_LEN_TIMEVAL + 1];
	char                msg_type_name[RVUTIL_MAX_RVMSG_TYPE_NAME + 1];
	char                error_text[RVUTIL_MAX_ERROR_TEXT];

	control_ptr = ((RVUTIL_CAN_CONTROL *) closure);

	if (event_type == RVEVM_SIGNAL_EVENT) {
		for (count_1 = 0, signal_ptr = control_ptr->signal_ptr->signal_list;
			count_1 < control_ptr->signal_ptr->signal_count;
			count_1++, signal_ptr++) {
			if (event_id == signal_ptr->signal_event_id) {
				if ((signal_ptr->action == RVUTIL_SIGNAL_ACTION_EXIT) ||
					(signal_ptr->action == RVUTIL_SIGNAL_ACTION_EXIT_FAST)) {
					fprintf(stderr,
						"********** Going down on signal '%s' (%d) . . .\n\n",
						signal_ptr->signal_name, signal_ptr->signal_number);
					RVUTIL_EndEnv(control_ptr->env_ptr,
						(signal_ptr->action == RVUTIL_SIGNAL_ACTION_EXIT_FAST) ?
						RVUTIL_TRUE : RVUTIL_FALSE);
					break;
				}
			}
		}
	}
	else if ((event_type == RVEVM_TIMER_EVENT) &&
		(event_id == control_ptr->publish_event_id)) {
		while (control_ptr->publish_tick_index <
			control_ptr->canr_tick_dir.tick_count) {
			tick_ptr = control_ptr->canr_tick_dir.tick_list +
				control_ptr->publish_tick_index;
			SDTIF_GetTimeUSecs(&this_time);
			if (SDTIF_COMPARE_TIMEVAL(&this_time, &tick_ptr->tick_time) <= 0)
				break;
			control_ptr->publish_tick_index++;
			if (RVUTIL_CANR_GetTick(control_ptr->mfile_ptr, tick_ptr,
				&tick_data, control_ptr->canr_tick_dir.data_buffer,
				error_text) != RVUTIL_SUCCESS) {
				fprintf(stderr,
					"********** Error on tick retrieval: %s **********\n\n",
					error_text);
				RVUTIL_EndEnv(control_ptr->env_ptr, RVUTIL_FALSE);
				return;
			}
			if (control_ptr->show_flag != RVUTIL_TRUE) {
				return_code = (!tick_data.header.reply_name_length) ?
					RVUTIL_rv_Send(control_ptr->env_ptr->session_handle,
					tick_data.name, tick_data.header.msg_type,
					tick_data.header.msg_size, tick_data.msg_data, NULL,
					error_text) :
					RVUTIL_rv_SendWithReply(control_ptr->env_ptr->session_handle,
					tick_data.name, tick_data.reply_name, tick_data.header.msg_type,
					tick_data.header.msg_size, tick_data.msg_data, NULL, error_text);
				if (return_code != RVUTIL_SUCCESS) {
					fprintf(stderr,
						"********** Error on tick publish: %s **********\n\n",
						error_text);
					RVUTIL_EndEnv(control_ptr->env_ptr, RVUTIL_FALSE);
					return;
				}
			}
			else {
				fprintf(stderr, "Real time: %s / ",
					SDTIF_Format_timeval(&this_time, time_buffer));
				fprintf(stderr, "Virtual time: %s\n",
					SDTIF_Format_timeval(&tick_data.header.tick_time, time_buffer));
				fprintf(stderr,
	"          :%s:name=%s:reply=%s:msg_type=%d=%s:msg_size=%u:msg=[%s]\n",
					SDTIF_Format_timeval(&tick_data.header.tick_time, time_buffer),
					tick_data.name, tick_data.reply_name,
					tick_data.header.msg_type,
					RVUTIL_GetMsgTypeName(tick_data.header.msg_type, msg_type_name),
					((unsigned int) tick_data.header.msg_size),
					(tick_data.header.msg_type != RVMSG_STRING) ?
					"*** NOT A STRING ***" : ((char *) tick_data.msg_data));
			}
		}
		if (control_ptr->publish_tick_index >=
			control_ptr->canr_tick_dir.tick_count) {
			fprintf(stderr, "\n\n");
			fprintf(stderr,
				"********** Publishing of canned data complete **********");
			if (control_ptr->loop_flag == RVUTIL_TRUE) {
				control_ptr->publish_tick_index = 0;
				fprintf(stderr,
					"\n********** Looping to start publishing again ***********\n");
				RVUTIL_CANR_SetTickTimes(&control_ptr->canr_tick_dir,
					control_ptr->adj_type, control_ptr->adj_msecs, 10L);
				RVUTIL_CANR_ShowTickStats(control_ptr);
			}
			else {
				RVUTIL_EndEnv(control_ptr->env_ptr, RVUTIL_FALSE);
				fprintf(stderr, "\n\n");
			}
		}
	}
}
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

