/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Support for library testing and debugging.

	Revision History	:	1999-11-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1999 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Required include files . . .														*/
/*	***********************************************************************	*/

#include <memory.h>

#include "pcffi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Internal testing and debugging data definitions (number one) . . .		*/
/*	***********************************************************************	*/
const char         *PCFF_TEST_LineList_1[] = {
	"#",
	"# OMS CONFIGURATION FILE",
	"#",
	"#location of the server: TOKYO HONGKONG SYDNEY...",
	"[SERVER_LOCATION]			[TOKYO]",
	"#",
	"#the name of the server",
	"[SERVER_NAME_TOKEN]		[TOKYO_OM1]",
	"#",
	"#the directory and the filename of the override file",
	"[OVERRIDE_FDIR]			[.\\]",
	"[OVERRIDE_FNAME]			[override_owner]",
	"#",
	"#the directory and the filename of the track owner file",
	"[TRACK_OWNER_FDIR]		[.\\]",
	"[TRACK_OWNER_FNAME]		[track_owner]",
	"#",
	"#the directory and the filename of the user information file",
	"[USER_FDIR]					[.\\]",
	"[USER_FNAME]				[user]",
	"#",
	"#the directory and the filename of the log file",
	"[LOG_FDIR]					[.\\]",
	"[LOG_FNAME]					[log]",
	"#",
	"#the location of the commission table",
	"[COMM_TABLE_FDIR]			[.\\]",
	"[COMM_TABLE_FNAME]		[COMSN_TABLE]",
	"#",
	"#account database",
	"#[ACCOUNT_DBASE]			[DATABASE:EOS_D,,,eostech,eostech]",
	"#",
	"#broker acct database",
	"[BROKER_ACCT_DBASE]		[FILE:.\\TokyoBroker.txt]",
	"#",
	"#the time to perform the batch process [HHMM]",
	"[BATCH_TIME]				[2100]",
	"#",
	"#is this server in test mode [Y] or [N]",
	"[IS_TEST_MODE]				[Y]",
	"#",
	"#is this server in production mode [Y] or [N]",
	"[IS_PRODUCTION]			[N]",
	"#",
	"#security master filename",
	"[SECMASTER_FNAME]			[SecurityTokyo.txt]",
	"[SECMASTER_DIRECTORY]	[.\\]",
	"#",
	"[FTP_ALIAS_NAME]			[ftp1.deveq.japan.ml.com]",
	"[FTP_DIRECTORY]			[/home/ftp/pub/eos/]",
	"[EXEC_DUMP_DIRECTORY]	[.\\]",
	"#",
	"#RV related config",
	"[CONTROL_SERVICE]			[9100]",
	"[CONTROL_NETWORK]			[NETWORK_A]",
	"[CONTROL_DAEMON]				[DAEMON_A]",
	"[EXCHANGE_SERVICE]			[9101]",
	"[EXCHANGE_NETWORK]			[NETWORK_A]",
	"[EXCHANGE_DAEMON]			[DAEMON_A]",
	"[DATA_SERVICE]				[9102]",
	"[DATA_NETWORK]				[NETWORK_A]",
	"[DATA_DAEMON]					[DAEMON_A]",
	"[FT_SERVICE]					[9103]",
	"[FT_NETWORK]					[NETWORK_A]",
	"[FT_DAEMON]					[DAEMON_A]",
	"#",
	"#OM SERVER ",
	"[OMS_ID]							[01]",
	"#",
	"#"
};
const unsigned int  PCFF_TEST_LineCount_1  =
	sizeof(PCFF_TEST_LineList_1) / sizeof(PCFF_TEST_LineList_1[0]);

const char         *PCFF_TEST_NameLeft_1       = "[";
const char         *PCFF_TEST_NameRight_1      = "]";
const char         *PCFF_TEST_ValueLeft_1      = "[";
const char         *PCFF_TEST_ValueRight_1     = "]";
const char         *PCFF_TEST_RequiredList_1[] = {
	"SERVER_LOCATION",
	"SERVER_NAME_TOKEN",
	"OVERRIDE_FDIR",
	"OVERRIDE_FNAME",
	"TRACK_OWNER_FDIR",
	"TRACK_OWNER_FNAME",
	"USER_FDIR",
	"USER_FNAME",
	"LOG_FDIR",
	"LOG_FNAME",
	"COMM_TABLE_FDIR",
	"COMM_TABLE_FNAME",
	"BROKER_ACCT_DBASE",
	"BATCH_TIME",
	"IS_TEST_MODE",
	"IS_PRODUCTION",
	"SECMASTER_FNAME",
	"SECMASTER_DIRECTORY",
	"FTP_ALIAS_NAME",
	"FTP_DIRECTORY",
	"EXEC_DUMP_DIRECTORY",
	"OMS_ID"
};
const unsigned int  PCFF_TEST_RequiredCount_1  =
	sizeof(PCFF_TEST_RequiredList_1) / sizeof(PCFF_TEST_RequiredList_1[0]);
const char         *PCFF_TEST_OptionalList_1[] = {
	"CONTROL_SERVICE",
	"CONTROL_NETWORK",
	"CONTROL_DAEMON",
	"EXCHANGE_SERVICE",
	"EXCHANGE_NETWORK",
	"EXCHANGE_DAEMON",
	"DATA_SERVICE",
	"DATA_NETWORK",
	"DATA_DAEMON",
	"FT_SERVICE",
	"FT_NETWORK",
	"FT_DAEMON"
};
const unsigned int  PCFF_TEST_OptionalCount_1  =
	sizeof(PCFF_TEST_OptionalList_1) / sizeof(PCFF_TEST_OptionalList_1[0]);
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Internal testing and debugging data definitions (number two) . . .		*/
/*	***********************************************************************	*/
const PCFF_PARAM   PCFF_TEST_ParamList[] = {
	PCFF_DEFINE_PARAM(PCFF_TEST_TARGET_DATA, "a.test.schar",
		a_schar, PCFF_FLD_TYPE_SCHAR,
		PCFF_PARAM_FLAG_NONE, 0,	"", ""),
	PCFF_DEFINE_PARAM(PCFF_TEST_TARGET_DATA, "a.test.uchar",
		a_uchar, PCFF_FLD_TYPE_UCHAR,
		PCFF_PARAM_FLAG_NONE, 0,	"", ""),
	PCFF_DEFINE_PARAM(PCFF_TEST_TARGET_DATA, "a.test.sshort",
		a_sshort, PCFF_FLD_TYPE_SSHORT,
		PCFF_PARAM_FLAG_NONE, 0,	"", ""),
	PCFF_DEFINE_PARAM(PCFF_TEST_TARGET_DATA, "a.test.ushort",
		a_ushort, PCFF_FLD_TYPE_USHORT,
		PCFF_PARAM_FLAG_NONE, 0,	"", ""),
	PCFF_DEFINE_PARAM(PCFF_TEST_TARGET_DATA, "a.test.sint",
		a_sint, PCFF_FLD_TYPE_SINT,
		PCFF_PARAM_FLAG_NONE, 0,	"", ""),
	PCFF_DEFINE_PARAM(PCFF_TEST_TARGET_DATA, "a.test.uint",
		a_uint, PCFF_FLD_TYPE_UINT,
		PCFF_PARAM_FLAG_NONE, 0,	"", ""),
	PCFF_DEFINE_PARAM(PCFF_TEST_TARGET_DATA, "a.test.slong",
		a_slong, PCFF_FLD_TYPE_SLONG,
		PCFF_PARAM_FLAG_NONE, 0,	"", ""),
	PCFF_DEFINE_PARAM(PCFF_TEST_TARGET_DATA, "a.test.ulong",
		a_ulong, PCFF_FLD_TYPE_ULONG,
		PCFF_PARAM_FLAG_NONE, 0,	"", ""),
	PCFF_DEFINE_PARAM(PCFF_TEST_TARGET_DATA, "a.test.float",
		a_float, PCFF_FLD_TYPE_FLOAT,
		PCFF_PARAM_FLAG_NONE, 0,	"", ""),
	PCFF_DEFINE_PARAM(PCFF_TEST_TARGET_DATA, "a.test.double",
		a_double, PCFF_FLD_TYPE_DOUBLE,
		PCFF_PARAM_FLAG_NONE, 0,	"", ""),
	PCFF_DEFINE_PARAM(PCFF_TEST_TARGET_DATA, "a.test.string.array",
		a_string_array, PCFF_FLD_TYPE_STRING,
		PCFF_PARAM_FLAG_NONE, 0,	"", ""),
	PCFF_DEFINE_PARAM(PCFF_TEST_TARGET_DATA, "a.test.boolean",
		a_boolean, PCFF_FLD_TYPE_BOOLEAN,
		PCFF_PARAM_FLAG_NONE, 0,	"", ""),
	PCFF_DEFINE_PARAM(PCFF_TEST_TARGET_DATA, "a.test.ip.host.service.protocol",
		a_hsp_spec, PCFF_FLD_TYPE_IP_HSP,
		PCFF_PARAM_FLAG_NONE, 0,	"", ""),
	PCFF_DEFINE_PARAM(PCFF_TEST_TARGET_DATA, "a.test.ip.protocol.host.service",
		a_phs_spec, PCFF_FLD_TYPE_IP_PHS,
		PCFF_PARAM_FLAG_NONE, 0,	"", ""),
	PCFF_DEFINE_PARAM(PCFF_TEST_TARGET_DATA, "a.test.date.string.array",
		a_date_string_array, PCFF_FLD_TYPE_DATE_STR,
		PCFF_PARAM_FLAG_NONE, 0,	"", ""),
	PCFF_DEFINE_PARAM(PCFF_TEST_TARGET_DATA, "a.test.time.string.array",
		a_time_string_array, PCFF_FLD_TYPE_TIME_STR,
		PCFF_PARAM_FLAG_NONE, 0,	"", ""),
	PCFF_DEFINE_PARAM(PCFF_TEST_TARGET_DATA, "a.test.timeval.string.array",
		a_timeval_string_array, PCFF_FLD_TYPE_TIMEVAL_STR,
		PCFF_PARAM_FLAG_NONE, 0,	"", ""),
	PCFF_DEFINE_PARAM(PCFF_TEST_TARGET_DATA, "a.test.timespec.string.array",
		a_timespec_string_array, PCFF_FLD_TYPE_TIMESPEC_STR,
		PCFF_PARAM_FLAG_NONE, 0,	"", ""),
	PCFF_DEFINE_PARAM(PCFF_TEST_TARGET_DATA, "a.test.string.pointer",
		a_string_pointer, PCFF_FLD_TYPE_STRING_PTR,
		PCFF_PARAM_FLAG_NONE, 0,	"", ""),
	PCFF_DEFINE_PARAM(PCFF_TEST_TARGET_DATA, "a.test.pathname.string.array",
		a_pathname_string_array, PCFF_FLD_TYPE_PATH_NAME,
		PCFF_PARAM_FLAG_NONE, 0,	"", ""),
	PCFF_DEFINE_PARAM(PCFF_TEST_TARGET_DATA, "a.test.pathname.string.pointer",
		a_pathname_string_pointer, PCFF_FLD_TYPE_PATH_NAME_PTR,
		PCFF_PARAM_FLAG_NONE, 0,	"", ""),
	PCFF_DEFINE_PARAM(PCFF_TEST_TARGET_DATA, "a.test.filename.string.array",
		a_filename_string_array, PCFF_FLD_TYPE_FILE_NAME,
		PCFF_PARAM_FLAG_NONE, 19,	"", ""),
	PCFF_DEFINE_PARAM(PCFF_TEST_TARGET_DATA, "a.test.filename.string.pointer",
		a_filename_string_pointer, PCFF_FLD_TYPE_FILE_NAME_PTR,
		PCFF_PARAM_FLAG_NONE, 20,	"", ""),
	PCFF_DEFINE_PARAM(PCFF_TEST_TARGET_DATA, "a.test.hostspec.string.array",
		a_hostspec_string_array, PCFF_FLD_TYPE_HOST_SPEC,
		PCFF_PARAM_FLAG_NONE, 0,	"", ""),
	PCFF_DEFINE_PARAM(PCFF_TEST_TARGET_DATA, "a.test.hostspec.string.pointer",
		a_hostspec_string_pointer, PCFF_FLD_TYPE_HOST_SPEC_PTR,
		PCFF_PARAM_FLAG_NONE, 0,	"", ""),
	PCFF_DEFINE_PARAM(PCFF_TEST_TARGET_DATA, "a.test.ip.service.array",
		a_ip_service_array, PCFF_FLD_TYPE_SERVICE,
		PCFF_PARAM_FLAG_NONE, 0,	"", ""),
	PCFF_DEFINE_PARAM(PCFF_TEST_TARGET_DATA, "a.test.ip.service.pointer",
		a_ip_service_pointer, PCFF_FLD_TYPE_SERVICE_PTR,
		PCFF_PARAM_FLAG_NONE, 0,	"", ""),
	PCFF_DEFINE_PARAM(PCFF_TEST_TARGET_DATA, "a.test.ip.protocol.array",
		a_ip_protocol_array, PCFF_FLD_TYPE_PROTOCOL,
		PCFF_PARAM_FLAG_NONE, 0,	"", ""),
	PCFF_DEFINE_PARAM(PCFF_TEST_TARGET_DATA, "a.test.ip.protocol.pointer",
		a_ip_protocol_pointer, PCFF_FLD_TYPE_PROTOCOL_PTR,
		PCFF_PARAM_FLAG_NONE, 0,	"", "")
};
const unsigned int PCFF_TEST_ParamCount  =
	sizeof(PCFF_TEST_ParamList) / sizeof(PCFF_TEST_ParamList[0]);

const char         *PCFF_TEST_LineList_2[] = {
	"[a.test.schar]                      [-127]",
	"[a.test.uchar]                      [255]",
	"[a.test.sshort]                     [-32768]",
	"[a.test.ushort]                     [65535]",
	"[a.test.sint]                       [-32768]",
	"[a.test.uint]                       [65535]",
	"[a.test.slong]                      [-2147483648]",
	"[a.test.ulong]                      [4294967295]",
	"[a.test.float]                      [-12345.67890]",
	"[a.test.double]                     [12345.67890E-7]",
	"[a.test.string.array]               [A String Array]",
	"[a.test.boolean]                    [YES]",
	"[a.test.ip.host.service.protocol]   [localhost:ftp:tcp]",
	"[a.test.ip.protocol.host.service]   [tcp:localhost:telnet]",
	"[a.test.date.string.array]          [2000-09-21]",
	"[a.test.time.string.array]          [12:34:56]",
	"[a.test.timeval.string.array]       [2000-09-21 12:34:56.123456]",
	"[a.test.timespec.string.array]      [2000-09-21 12:34:56.123456789]",
	"[a.test.string.pointer]             [This is a longish allocated string.]",
#ifdef _Windows
	"[a.test.pathname.string.array]      [\\dev]",
#else
	"[a.test.pathname.string.array]      [/dev]",
#endif /* #ifdef _Windows */
	"[a.test.pathname.string.pointer]    [.]",
	"[a.test.filename.string.array]      [file.name.1]",
	"[a.test.filename.string.pointer]    [file.name.2]",
	"[a.test.hostspec.string.array]      [localhost]",
	"[a.test.hostspec.string.pointer]    [127.0.0.1]",
	"[a.test.ip.service.array]           [ftp]",
	"[a.test.ip.service.pointer]         [telnet]",
	"[a.test.ip.protocol.array]          [tcp]",
	"[a.test.ip.protocol.pointer]        [udp]",
	"[ThisNameHasNoParameter]            [ThisValueHasNoParameter]"
};
const unsigned int  PCFF_TEST_LineCount_2  =
	sizeof(PCFF_TEST_LineList_2) / sizeof(PCFF_TEST_LineList_2[0]);

const char         *PCFF_TEST_NameLeft_2       = "[";
const char         *PCFF_TEST_NameRight_2      = "]";
const char         *PCFF_TEST_ValueLeft_2      = "[";
const char         *PCFF_TEST_ValueRight_2     = "]";
const char         *PCFF_TEST_RequiredList_2[] = {
	"a.test.schar"
};
const unsigned int  PCFF_TEST_RequiredCount_2  =
	sizeof(PCFF_TEST_RequiredList_2) / sizeof(PCFF_TEST_RequiredList_2[0]);
const char         *PCFF_TEST_OptionalList_2[] = {
	"a.test.uchar"
};
const unsigned int  PCFF_TEST_OptionalCount_2  =
	sizeof(PCFF_TEST_OptionalList_2) / sizeof(PCFF_TEST_OptionalList_2[0]);
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void PCFF_TEST_GetTestData(unsigned int *line_count, char ***line_list,
	PCFF_PARSE_SPEC *parse_spec_ptr)
{
	if (line_count != NULL)
		*line_count = PCFF_TEST_LineCount_1;

	if (line_list != NULL)
		*line_list = ((char **) PCFF_TEST_LineList_1);

	if (parse_spec_ptr != NULL) {
		PCFF_InitParse(parse_spec_ptr);
		parse_spec_ptr->name_left      = ((char *) PCFF_TEST_NameLeft_1);
		parse_spec_ptr->name_right     = ((char *) PCFF_TEST_NameRight_1);
		parse_spec_ptr->value_left     = ((char *) PCFF_TEST_ValueLeft_1);
		parse_spec_ptr->value_right    = ((char *) PCFF_TEST_ValueRight_1);
		parse_spec_ptr->required_count = PCFF_TEST_RequiredCount_1;
		parse_spec_ptr->required_list  = ((char **) PCFF_TEST_RequiredList_1);
		parse_spec_ptr->optional_count = PCFF_TEST_OptionalCount_1;
		parse_spec_ptr->optional_list  = ((char **) PCFF_TEST_OptionalList_1);
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void PCFF_TEST_GetTestDataParam(unsigned int *line_count, char ***line_list,
	PCFF_PARSE_SPEC *parse_spec_ptr, PCFF_PARAM_SPEC *param_spec_ptr)
{
	if (line_count != NULL)
		*line_count = PCFF_TEST_LineCount_2;

	if (line_list != NULL)
		*line_list = ((char **) PCFF_TEST_LineList_2);

	if (parse_spec_ptr != NULL) {
		PCFF_InitParse(parse_spec_ptr);
		parse_spec_ptr->name_left      = ((char *) PCFF_TEST_NameLeft_2);
		parse_spec_ptr->name_right     = ((char *) PCFF_TEST_NameRight_2);
		parse_spec_ptr->value_left     = ((char *) PCFF_TEST_ValueLeft_2);
		parse_spec_ptr->value_right    = ((char *) PCFF_TEST_ValueRight_2);
		parse_spec_ptr->required_count = PCFF_TEST_RequiredCount_2;
		parse_spec_ptr->required_list  = ((char **) PCFF_TEST_RequiredList_2);
		parse_spec_ptr->optional_count = PCFF_TEST_OptionalCount_2;
		parse_spec_ptr->optional_list  = ((char **) PCFF_TEST_OptionalList_2);
	}

	if (param_spec_ptr != NULL) {
		PCFF_InitParamSpec(param_spec_ptr);
		param_spec_ptr->structure_size = sizeof(PCFF_TEST_TARGET_DATA);
		param_spec_ptr->param_count    = PCFF_TEST_ParamCount;
		param_spec_ptr->param_list     = ((PCFF_PARAM *) PCFF_TEST_ParamList);
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void PCFF_TEST_ShowCfg(PCFF_CFG *cfg_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
{
	unsigned int count_1;
	unsigned int name_length;
	unsigned int value_length;
	unsigned int number_length;

	STR_EMIT_SetDefaults(&output_function, &output_control);

	name_length   = PCFF_GetLongestName(cfg_ptr);
	value_length  = PCFF_GetLongestValue(cfg_ptr);
	number_length = PCFF_GetLongestLineNumber(cfg_ptr);

	for (count_1 = 0; count_1 < cfg_ptr->item_count; count_1++)
		(*output_function)(output_control,
			"%-*.*s:%-*.*s:Line Number %*u:File Name:%s\n",
			name_length, name_length, cfg_ptr->item_list[count_1].name,
			value_length, value_length, cfg_ptr->item_list[count_1].value,
			number_length,
			cfg_ptr->item_list[count_1].src_list->line_number,
			cfg_ptr->item_list[count_1].src_list->file_name);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void PCFF_TEST_FreeData(PCFF_TEST_TARGET_DATA *ptr)
{
	if (ptr->a_string_pointer != NULL)
		free(ptr->a_string_pointer);

	if (ptr->a_pathname_string_pointer != NULL)
		free(ptr->a_pathname_string_pointer);

	if (ptr->a_filename_string_pointer != NULL)
		free(ptr->a_filename_string_pointer);

	if (ptr->a_hostspec_string_pointer != NULL)
		free(ptr->a_hostspec_string_pointer);

	PCFF_FreeCfg(&ptr->cfg_data);

	PCFF_TEST_InitData(ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void PCFF_TEST_InitData(PCFF_TEST_TARGET_DATA *ptr)
{
	memset(ptr, '\0', sizeof(*ptr));

	ptr->a_string_pointer = NULL;
}
/*	***********************************************************************	*/

