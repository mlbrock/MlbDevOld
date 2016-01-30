/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Executable Source Module									*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Cans Rendezvous data for later playback.

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

#include "rvutilcd.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
COMPAT_FN_DECL(int main, (int argc, char **argv));
COMPAT_FN_DECL_STATIC(void RVUTIL_CANW_DataCallback,
	(rv_Session session, rv_Name name, rv_Name reply_name, rvmsg_Type msg_type,
	rvmsg_Size msg_size, rvmsg_Data msg_data, rv_Opaque closure));
COMPAT_FN_DECL_STATIC(void RVUTIL_CANW_EventCallback,
	(rv_Session session, rv_Opaque closure, rvevm_EventType event_type,
	rvevm_EventId event_id));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int main(int argc, char **argv)
{
	int                  return_code   = RVUTIL_SUCCESS;
	const char          *file_name     = NULL;
	const char          *snd_service   = "";
	const char          *snd_network   = "";
	const char          *snd_daemon    = "";
	unsigned int         sync_period   = 60000;
	unsigned int         log_period    = 10000;
	unsigned int         subject_count = 0;
	char               **subject_list  = NULL;
	unsigned int         exclude_count = 0;
	char               **exclude_list  = NULL;
	unsigned int         count_1;
	RVUTIL_ENV           env_data;
	RVUTIL_SIGNAL_SPEC   signal_spec;
	RVUTIL_CAN_CONTROL   control_data;
	struct timeval       start_time;
	char                 time_buffer[SDTIF_FMT_TIME_LEN_TIME_T + 1];
	char                 error_text[RVUTIL_MAX_ERROR_TEXT];
	char                 tmp_error_text[RVUTIL_MAX_ERROR_TEXT];
	char                 mfile_error_text[MFILE_MAX_ERROR_TEXT];

	RVUTIL_InitEnv(&env_data);
	RVUTIL_GetDefaultSignalSpec(&signal_spec);

	memset(&control_data, '\0', sizeof(control_data));

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
		else if (!stricmp(argv[count_1], "-SYNC")) {
			if ((count_1 + 1) == ((unsigned int) argc)) {
				sprintf(error_text, "%s '%-.500s' parameter.",
					"Expected command-line qualifier to follow", argv[count_1]);
				return_code = RVUTIL_BAD_ARGS_FAILURE;
				goto EXIT_FUNCTION;
			}
			if (atoi(argv[++count_1]) > 0)
				sync_period = atoi(argv[count_1]);
		}
		else if (!stricmp(argv[count_1], "-LOG")) {
			if ((count_1 + 1) == ((unsigned int) argc)) {
				sprintf(error_text, "%s '%-.500s' parameter.",
					"Expected command-line qualifier to follow", argv[count_1]);
				return_code = RVUTIL_BAD_ARGS_FAILURE;
				goto EXIT_FUNCTION;
			}
			if (atoi(argv[++count_1]) > 0)
				log_period = atoi(argv[count_1]);
		}
		else if (!stricmp(argv[count_1], "-EXCLUDE")) {
			if ((count_1 + 1) == ((unsigned int) argc)) {
				sprintf(error_text, "%s '%-.500s' parameter.",
					"Expected command-line qualifier to follow", argv[count_1]);
				return_code = RVUTIL_BAD_ARGS_FAILURE;
				goto EXIT_FUNCTION;
			}
			else if ((return_code = RVUTIL_CheckSubjectName(argv[++count_1],
				tmp_error_text)) != RVUTIL_SUCCESS) {
				sprintf(error_text, "%s ('%-.500s') %s: %s",
					"Invalid command line parameter", argv[count_1],
					"an RV subject name pattern was expected", tmp_error_text);
				goto EXIT_FUNCTION;
			}
			else if (strl_append(&exclude_count, &exclude_list, argv[count_1]) !=
				STRFUNCS_SUCCESS) {
				STR_AllocMsgItem(strlen(argv[count_1]), error_text,
					"Unable to add an RV subject name pattern to the exclude list");
				return_code = RVUTIL_MEMORY_FAILURE;
				goto EXIT_FUNCTION;
			}
		}
		else if ((return_code = RVUTIL_CheckSubjectName(argv[count_1],
			tmp_error_text)) != RVUTIL_SUCCESS) {
			sprintf(error_text, "%s ('%-.500s') %s: %s",
				"Invalid command line parameter", argv[count_1],
				"an RV subject name pattern was expected", tmp_error_text);
			goto EXIT_FUNCTION;
		}
		else if (strl_append(&subject_count, &subject_list, argv[count_1]) !=
			STRFUNCS_SUCCESS) {
			STR_AllocMsgItem(strlen(argv[count_1]), error_text,
				"Unable to add an RV subject name pattern to the subject list");
			return_code = RVUTIL_MEMORY_FAILURE;
			goto EXIT_FUNCTION;
		}
	}

	if ((file_name == NULL) || (!(*file_name))) {
		strcpy(error_text, "No file name was specified on the command-line.");
		return_code = RVUTIL_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if (!subject_count) {
		strcpy(error_text,
			"No RV subject name patterns were specified on the command-line.");
		return_code = RVUTIL_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}

	strl_sort(subject_count, subject_list);
	strl_uniq(&subject_count, &subject_list);

	strl_sort(exclude_count, exclude_list);
	strl_uniq(&exclude_count, &exclude_list);

	if ((return_code = RVUTIL_MakeSubjectPatternList(exclude_count, exclude_list,
		&control_data.exclude_count, &control_data.exclude_list, error_text)) !=
		RVUTIL_SUCCESS)
		goto EXIT_FUNCTION;

	if ((control_data.mfile_ptr = mopen(file_name, "wb")) == NULL) {
		strcat(nstrcat(strcpy(error_text, "Unable to open file '"),
			file_name, 500), "': ");
		GEN_AppendLastErrorString(0, RVUTIL_MAX_ERROR_TEXT, error_text);
		goto EXIT_FUNCTION;
	}
	msetbuf(control_data.mfile_ptr, 0x100000);
	if ((return_code = MFILE_EnsureSpace(control_data.mfile_ptr,
		0x100000, 0x100000, mfile_error_text)) != MFILE_SUCCESS) {
		strcat(strcpy(error_text,
			"Unable to force truncation of the message data file: "),
			mfile_error_text);
		return_code = RVUTIL_MAP_ERROR_MFILE(return_code);
		goto EXIT_FUNCTION;
	}

	fprintf(stderr, "Creating environment");
	if ((return_code = RVUTIL_CreateEnv(snd_service, snd_network,
		snd_daemon, NULL, NULL, &env_data, error_text)) != RVUTIL_SUCCESS)
		goto EXIT_FUNCTION;
	fprintf(stderr, "\n");

	fprintf(stderr, "Adding subject name patterns to Rendezvous environment");
	if ((return_code = RVUTIL_AddSubList(&env_data, subject_count,
		subject_list, RVUTIL_CANW_DataCallback, error_text)) != RVUTIL_SUCCESS)
		goto EXIT_FUNCTION;
	fprintf(stderr, "\n");

	fprintf(stderr, "Starting environment Rendezvous session");
	if ((return_code = RVUTIL_StartSessionEnv(&env_data, error_text)) !=
		RVUTIL_SUCCESS)
		goto EXIT_FUNCTION;
	fprintf(stderr, "\n");

	fprintf(stderr, "Initializing Rendezvous signal handling");
	if ((return_code = RVUTIL_StartSignalHandling(&signal_spec, &env_data,
		RVUTIL_CANW_EventCallback, &control_data, error_text)) != RVUTIL_SUCCESS)
		goto EXIT_FUNCTION;
	fprintf(stderr, "\n");

	fprintf(stderr, "Initializing Rendezvous synchronization timer handling");
	if ((return_code = RVUTIL_rvevm_AddRepeatingTimer(env_data.session_handle,
		&control_data.sync_event_id, sync_period, RVUTIL_CANW_EventCallback,
		&control_data, NULL, error_text)) != RVUTIL_SUCCESS)
		goto EXIT_FUNCTION;
	fprintf(stderr, "\n");

	fprintf(stderr, "Initializing Rendezvous log timer handling");
	if ((return_code = RVUTIL_rvevm_AddRepeatingTimer(env_data.session_handle,
		&control_data.log_event_id, log_period, RVUTIL_CANW_EventCallback,
		&control_data, NULL, error_text)) != RVUTIL_SUCCESS)
		goto EXIT_FUNCTION;
	fprintf(stderr, "\n");

#ifdef _Windows
	fprintf(stderr, "Initializing Rendezvous periodic timer handling");
	if ((return_code = RVUTIL_rvevm_AddRepeatingTimer(env_data.session_handle,
		&control_data.periodic_event_id, 100L, RVUTIL_CANW_EventCallback,
		&control_data, NULL, error_text)) != RVUTIL_SUCCESS)
		goto EXIT_FUNCTION;
	fprintf(stderr, "\n");
#endif /* #ifdef _Windows */

	fprintf(stderr, "Beginning listen on %u subject name patterns",
		subject_count);
	if ((return_code = RVUTIL_BeginListenEnv(&env_data, &control_data,
		error_text)) != RVUTIL_SUCCESS)
		goto EXIT_FUNCTION;
	fprintf(stderr, "\n");

	fprintf(stderr, "*** ENTERING 'rv_MainLoop() ***\n");
	SDTIF_GetTimeUSecs(&start_time);
	rv_MainLoop(env_data.session_handle);
	fprintf(stderr, "*** RETURNED FROM 'rv_MainLoop() ***\n");

	fprintf(stderr, "%s:%10u messages, %20.0f bytes\n",
		SDTIF_Format_time_t(NULL, time_buffer),
		control_data.message_count, control_data.message_bytes);

EXIT_FUNCTION:

	strl_remove_all(&subject_count, &subject_list);
	strl_remove_all(&exclude_count, &exclude_list);

	RVUTIL_CloseEnv(&env_data, RVUTIL_FALSE);

	if (control_data.mfile_ptr != NULL)
		mclose(control_data.mfile_ptr);

	mema_remove_all(&control_data.exclude_count,
		((void **) &control_data.exclude_list));

	if (return_code == RVUTIL_BAD_ARGS_FAILURE)
		fprintf(stderr,
			"\n\n%s\n\nUSAGE: %s [ -h | -help ] %s %s %s %s %s %s %s %s\n\n",
			error_text,
			argv[0],
			"-file <message-file-name>",
			"[ -service <RV-service-string> ]",
			"[ -network <RV-network-string> ]",
			"[ -daemon <RV-daemon-string> ]",
			"[ -sync <sync-milliseconds> ]",
			"[ -log <log-milliseconds> ]",
			"[ -exclude <subject-pattern> . . . ]",
			"<subject-pattern> [ <subject-pattern> . . . ]");
	else if (return_code != RVUTIL_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return((return_code == RVUTIL_SUCCESS) ? EXIT_SUCCESS : EXIT_FAILURE);
}
/*	***********************************************************************	*/

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
static void RVUTIL_CANW_DataCallback(rv_Session session, rv_Name name,
	rv_Name reply_name, rvmsg_Type msg_type, rvmsg_Size msg_size,
	rvmsg_Data msg_data, rv_Opaque closure)
{
	unsigned long       current_offset;
	RVUTIL_CAN_CONTROL *control_ptr;
	CAN_DATA            can_data;
	unsigned int        total_length;
	unsigned int        pad_length;
	CAN_PAD_TYPE        pad_align;
	char                mfile_error_text[MFILE_MAX_ERROR_TEXT];

	control_ptr = ((RVUTIL_CAN_CONTROL *) closure);

	if (control_ptr->exclude_count &&
		(RVUTIL_MatchSubjectPerList(((const char *) name),
		control_ptr->exclude_count, control_ptr->exclude_list, NULL, NULL) ==
		RVUTIL_TRUE))
		return;

	memset(&can_data, '\0', sizeof(can_data));

	SDTIF_GetTimeUSecs(&can_data.tick_time);
	name                       = (name       == NULL) ? "" : name;
	reply_name                 = (reply_name == NULL) ? "" : reply_name;
	can_data.name_length       = strlen(name);
	can_data.reply_name_length = strlen(reply_name);
	can_data.msg_type          = msg_type;
	can_data.msg_size          = msg_size;
	can_data.total_length      = sizeof(can_data) + can_data.name_length + 1 +
		can_data.reply_name_length + 1 + msg_size + 1;
	total_length               = STRFUNCS_ADJUST_SIZE(can_data.total_length,
		sizeof(CAN_PAD_TYPE));
	pad_length                 = total_length - can_data.total_length;
	can_data.total_length      = total_length;

	if (MFILE_EnsureSpace(control_ptr->mfile_ptr, 0x100000,
		can_data.total_length, mfile_error_text) != MFILE_SUCCESS) {
		fprintf(stderr, "\n\nERROR: Unable to expand canned data file: %s\n",
			mfile_error_text);
		RVUTIL_EndEnv(control_ptr->env_ptr, RVUTIL_FALSE);
		return;
	}

	current_offset = mtell(control_ptr->mfile_ptr);
	mwrite(&can_data, sizeof(can_data), 1, control_ptr->mfile_ptr);
	mwrite(name, can_data.name_length + 1, 1, control_ptr->mfile_ptr);
	mwrite(reply_name, can_data.reply_name_length+1, 1, control_ptr->mfile_ptr);
	mwrite(msg_data, msg_size, 1, control_ptr->mfile_ptr);
	mwrite("\0", 1, 1, control_ptr->mfile_ptr);
	if (pad_length) {
		memset(&pad_align, '\0', sizeof(pad_align));
		mwrite(&pad_align, pad_length, 1, control_ptr->mfile_ptr);
	}
	mseek(control_ptr->mfile_ptr,
		((off_t) (current_offset + can_data.total_length)), SEEK_SET);

	control_ptr->message_count++;
	control_ptr->message_bytes += msg_size;
}
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
static void RVUTIL_CANW_EventCallback(rv_Session session, rv_Opaque closure,
	rvevm_EventType event_type, rvevm_EventId event_id)
{
	unsigned int        count_1;
	RVUTIL_SIGNAL      *signal_ptr;
	RVUTIL_CAN_CONTROL *control_ptr;
	char                time_buffer[SDTIF_FMT_TIME_LEN_TIME_T + 1];

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
					if (signal_ptr->action != RVUTIL_SIGNAL_ACTION_EXIT_FAST) {
						fprintf(stderr,
							"********** Flushing message file . . .\n\n");
						mflush(control_ptr->mfile_ptr);
					}
					RVUTIL_EndEnv(control_ptr->env_ptr,
						(signal_ptr->action == RVUTIL_SIGNAL_ACTION_EXIT_FAST) ?
						RVUTIL_TRUE : RVUTIL_FALSE);
					break;
				}
			}
		}
	}
	else if (event_type == RVEVM_TIMER_EVENT) {
		if (event_id == control_ptr->log_event_id)
			fprintf(stderr, "%s:%10u messages, %20.0f bytes\n",
				SDTIF_Format_time_t(NULL, time_buffer),
				control_ptr->message_count, control_ptr->message_bytes);
		else if (event_id == control_ptr->sync_event_id)
			mflush(control_ptr->mfile_ptr);
	}
}
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */


