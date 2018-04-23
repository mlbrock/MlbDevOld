/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Executable Module									*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Copies a cache, with optional re-indexing.

	Revision History	:	1995-09-25 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <limits.h>
#include <locale.h>
#include <math.h>
#include <memory.h>
#include <string.h>
#include <sys/param.h>

#include "dcr.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define DCR_CPY_VERSION_NUMBER "01.01.00A"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

static unsigned long DCR_CPY_CallBackMask =
	DCR_CB_BULK_INSERT   |
	DCR_CB_BULK_SEARCH   |
	DCR_CB_INDEX_CACHE   |
	DCR_CB_RESIZE_CACHE  |
	DCR_CB_INITIAL_LOAD  |
	DCR_CB_RELOAD        |
	DCR_CB_UPDATE        |
	DCR_CB_ALLOC_CHUNK   |
	DCR_CB_CHECK_INDEX_1 |
	DCR_CB_CHECK_INDEX_2;

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

typedef struct {
	char               *program_name;
	char               *short_program_name;
	char               *syslog_program_name;
	STR_VERSION         system_version_number;
	STR_VERSION         version_number;
	char                system_version_string[STR_VERSION_NUMBER_LENGTH + 1];
	char                version_string[STR_VERSION_NUMBER_LENGTH + 1];
	int                 process_id;
	char                host_name[MAXHOSTNAMELEN + 1];
	char                current_directory[MAXPATHLEN + 1];
	int                 help_flag;
	int                 version_flag;
	struct timeval      start_time;
	struct timeval      end_time;
	struct timeval      overhead_end_time;
	int                 signal_received_flag;
	int                 queue_signal_flag;
	int                 shut_down_flag;
	int                 re_index_flag;
	int                 check_index_flag;
	int                 force_overwrite_flag;
	DCR_CONTROL   cache_control_data;
	char               *in_cache_file_name;
	DCR_CACHE          *in_cache_ptr;
	unsigned int        in_cache_index;
	DCR_CACHE          *cache_ptr;
	unsigned int        cache_index;
	char               *cache_file_name;
	char               *log_file_directory;
	char               *log_file_name;
	MFILE              *log_file_mfile_ptr;
	MFILE_LOG_CONTEXT   log_context;
	unsigned int        index_spec_count;
	char              **index_spec_list;
	unsigned int        index_drop_count;
	char              **index_drop_list;
	unsigned int        kept_index_count;
	unsigned int       *kept_index_list;
} DCR_CPY_CONTROL;

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#ifndef NARGS
int main(int argc, char **argv);
#else
int main();
#endif /* #ifndef NARGS */

#ifndef NARGS
static int  DCR_CPY_OpenInputCache(DCR_CPY_CONTROL *control_ptr,
	char *error_text);
static int  DCR_CPY_DoCopy(DCR_CPY_CONTROL *control_ptr,
	const void **user_data_ptr_list, char *error_text);
static int  DCR_CPY_CreateOutputCache(DCR_CPY_CONTROL *control_ptr,
	const void **user_data_ptr_list, unsigned int added_field_count,
	char **added_field_list, unsigned int index_spec_count,
	char **index_spec_list, DCR_CACHE **out_cache_ptr,
	unsigned int *out_cache_index, char *error_text);
static int  DCR_CPY_GetParams(DCR_CPY_CONTROL *control_ptr,
	unsigned int argc, char **argv, char *error_text);
static int  DCR_CPY_CheckParams(DCR_CPY_CONTROL *control_ptr,
	char *error_text);
static int  DCR_CPY_OpenLogFile(DCR_CPY_CONTROL *control_ptr,
	char *error_text);
static void DCR_CPY_ShowSettings(DCR_CPY_CONTROL *control_ptr);
static int  DCR_CPY_Parse(DCR_CPY_CONTROL *control_ptr,
	unsigned int argc, char **argv, int init_flag, unsigned int current_arg,
	const char *this_arg, char *error_text);
static void DCR_CPY_Init(DCR_CPY_CONTROL *control_ptr);
static void DCR_CPY_End(DCR_CPY_CONTROL *control_ptr,
	int signal_number, int *exit_code_ptr, const char *message_buffer);
static int  DCR_CPY_CallBack(DCR_CACHE *cache_ptr,
	unsigned long call_back_type, int post_operation_flag,
	unsigned int index_method, int operation_flags,
	unsigned int operation_count, void *operation_ptr,
	DCR_STAT *stat_ptr, int return_code, char *error_text);
static int  DCR_CPY_CriticalCallBack(DCR_CACHE *cache_ptr,
	unsigned long call_back_type, int post_operation_flag, int operation_flags,
	unsigned int operation_count, void *operation_ptr, int return_code,
	char *error_text);
#else
static int  DCR_CPY_OpenInputCache();
static int  DCR_CPY_DoCopy();
static int  DCR_CPY_CreateOutputCache();
static int  DCR_CPY_GetParams();
static int  DCR_CPY_CheckParams();
static int  DCR_CPY_OpenLogFile();
static void DCR_CPY_ShowSettings();
static int  DCR_CPY_Parse();
static void DCR_CPY_Init();
static void DCR_CPY_End();
static int  DCR_CPY_CallBack();
static int  DCR_CPY_CriticalCallBack();
#endif /* #ifndef NARGS */

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

static const char *UsageList[] = {
	"Usage:",
	"------",
	"	cpycache [<a mixture of '-' options, and '@' commands]",
	"\n",
	"Description:",
	"------------",
	"	This program manages the copying of data records from an input cache \
to an output cache.",
	"\n",
	"	Invocation of the program may include any number of parameters \
which may be used to specify the nature of the resulting program operation. \
There are two types of parameters:",
	"\n",
	"		o  '-'-prefaced options, which specify any one of a number of \
options (which are described in the 'Options', below); and,",
	"\n",
	"		o  '@'-prefaced file names, which indicate that the indicated \
file name is to be parsed for parameters.",
	"\n",
	"Operation:",
	"----------",
	"	Program operation is as follows:",
	"\n",
	"		o The program initializes itself to the default settings.",
	"\n",
	"		o The command line is scanned for options.",
	"\n",
	"		o Every time a valid parameter is encountered, it immediately \
becomes active.  If the same parameter is encountered multiple times, \
the most-recent instance of the parameter becomes effective.",
"\n",
	"		o If an '@' option is encountered, the indicated file is read \
as if its lines had been placed on the command line UNLESS the \
indicated file is in the current hierarchy of '@' files, in which \
case it is ignored.",
	"\n",
	"Options:",
	"--------",
	"	[-H[ELP]]",
	"		Displays this text. Note that if this parameter appears on the \
command-line, the program will exit after displaying the help text.",
	"\n",
	"	[-V[ER[SION][S]]]]",
	"		Displays the version of this program.",
	"\n",
	"		If this parameter appears on the command line, any subsequent \
parameters will be parsed for validity and the program will exit.",
	"\n",
	"	-INPUT_CACHE_FILE[_NAME]=<cache-file-name>",
	"		Specifies the name of the cache file to be read as input.",
	"\n",
	"\n",
	"	-[OUTPUT_]CACHE_FILE[_NAME]=<cache-file-name>",
	"		Specifies the name of the cache file to be created as output.",
	"\n",
	"	[-LOG[GING]_DIR[RECTORY]=<log-file-dir-name>]",
	"		Specifies the directory within which the log file is to be created.",
	"\n",
	"		If this parameter is not specified, the log file will be created \
in the current directory ('./').",
	"\n",
	"	[-ADD_IND{EX[[E]S]|ICES}=<index-spec>]",
	"		Specifies the fields which are to be used to construct additional \
cache indices. The <index-spec> component of this parameter has the \
following structure:",
	"\n",
	"			<index-spec> := <index-name>=<field-name>[,<field-name> . . .]",
	"\n",
	"		This parameter may occur multiple times on the command-line; if it \
does, each instance is taken as specifing the creation of a different index.",
	"\n",
	"		Note that each <index-name> must be unique and must not be the name \
of an index in the input cache (unless that index is the target of a \
'-DROP_INDEX=' parameter).",
	"\n",
	"	[-DROP_IND{EX[[E]S]|ICES}=<index-name>]",
	"		Specifies indices which are to be dropped when creating the output \
cache. The <index-name> specified must exist in the input cache.",
	"\n",
	"	[-RE[_]INDEX=<boolean>]",
	"		Specifies that all indices will be re-created in the output cache, \
even if they are unchanged from the input cache.",
	"\n",
	"		The <boolean> component of this parameter has the following syntax:",
	"\n",
	"		{ ON | OFF | TRUE | FALSE | YES | NO }",
	"\n",
	"		The default for this parameter is 'OFF'.",
	"\n",
	"	[-CHECK[_]IND{EX[[E]S]|ICES}=<boolean>]",
	"		Specifies that all indices in the output cache will be checked for \
internal consistency after creation.",
	"\n",
	"		The <boolean> component of this parameter has the following syntax:",
	"\n",
	"		{ ON | OFF | TRUE | FALSE | YES | NO }",
	"\n",
	"		The default for this parameter is 'OFF'.",
	"\n",
	"	[-FORCE[D]_OVERWRITE=<boolean>]",
	"		Specifies the action to be taken if the output cache already exists.",
	"\n",
	"		The <boolean> component of this parameter has the following syntax:",
	"\n",
	"		{ ON | OFF | TRUE | FALSE | YES | NO }",
	"\n",
	"		If this parameter is set to 'OFF', then the program will abort \
if the output cache file exists. Otherwise, it will be overwritten.",
	"\n",
	"		The default for this parameter is 'OFF'.",
	"\n",
	"	[@<parameter-include-file-name>]",
	"		Specifies the name of a parameter include file from which are to \
be read parameters to this program. Parameter include files may themselves \
contain parameter include file specifications.",
	"\n",
	"		When a parameter include file is encountered on the command line, \
the program will attempt to open it for reading. It is an error if the file \
so specified does not exist or can not be read.",
	"\n",
	"		Each line of the parameter include file is parsed for its \
parameters just as if those parameters were entered on the command line \
except for the following rules:",
	"\n",
	"			o A line in which the first non-whitespace character is a \
number-sign ('#') is considered to be the start of a comment and is ignored.",
	"\n",
	"			o Blank lines (that is, lines which are empty or which consist \
wholly of whitespace) are ignored.",
	"\n",
	NULL
};

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH .bin,1

	BASE NAME	:	cpycache

	NAME			:	cpycache - copies records from an input cache to an output
						cache with optional additional or removal of cache indices

	SYNOPSIS		:	cpycache -h[elp]

						cpycache -v[er[sion]]

						cpycache -input_cache_file[_name]=''cache-file_name''
						-[output_]cache_file[_name]=''cache-file-name''
						[-log[ging]_dir[ectory]=''log-file-dir-name'']
						[-add_ind{ex[[e]s]|ices}=''index-spec'']
						[-drop_ind{ex[[e]s]|ices}=''index-name'']
						[-re[_]index=''boolean'']
						[-check[_]ind{ex[[e]s]|ices}=''boolean'']
						[-force[d]_overwrite=''boolean'']
						[@''parameter-include-file-name'']

	DESCRIPTION	:	This program manages the copying of data records from an
						input cache to an output cache.

						Invocation of the program may include any number of
						parameters which may be used to specify the nature of the
						resulting program operation.

						There are two types of parameters:

						(.) ''-''-prefaced options, which specify any one of a
						number of options (which are described in the ``Options``
						section, below); and,

						(.) ''@''-prefaced file names, which indicate that the
						indicated file name is to be parsed for parameters.

	OPTIONS		:	Parameters to this program are as follow:

						(.) [-h[elp]]

						(-) Displays this text. Note that if this parameter appears
						on the command-line, the program will exit after displaying
						the help text.

						(.) [-v[er[sion][s]]]]

						(-) Displays the version of this program.

						(-) If this parameter appears on the command line, any
						subsequent parameters will be parsed for validity and the
						program will exit.

						(.) -input_cache_file[_name]=''cache-file-name''

						(-) Specifies the name of the cache file to be read as
						input.

						(.) -[output_]cache_file[_name]=''cache-file-name''

						(-) Specifies the name of the cache file to be created as
						output.

						(.) [-log[ging]_dir[rectory]=''log-file-dir-name'']

						(-) Specifies the directory within which the log file is to
						be created.

						(-) If this parameter is not specified, the log file will
						be created in the current directory (''./'').

						(.) [-add_ind{ex[[e]s]|ices}=''index-spec'']

						(-) Specifies the fields which are to be used to construct
						additional cache indices. The ''index-spec'' component
						of this parameter has the following structure:

						(--) ``index-spec`` :=
							``index-name``''=''``field-name``''[,''``field-name``
							. . .'']''

						(-) This parameter may occur multiple times on the
						command-line; if it does, each instance is taken as
						specifing the creation of a different index.

						(-) Note that each ''index-name'' must be unique and
						must not be the name of an index in the input cache (unless
						that index is the target of a ''-DROP_INDEX='' parameter).

						(.) [-drop_ind{ex[[e]s]|ices}=''index-name'']

						(-) Specifies indices which are to be dropped when creating
						the output cache. The ''index-name'' specified must
						exist in the input cache.

						(.) [-re[_]index=''boolean'']

						(-) Specifies that all indices will be re-created in the
						output cache, even if they are unchanged from the input
						cache.

						(-) The ''boolean'' component of this parameter has the
						following syntax:

						(--) { ''ON'' | ''OFF'' | ''TRUE'' | ''FALSE'' | ''YES'' |
								''NO'' }

						(-) The default for this parameter is ''OFF''.

						(.) [-check[_]ind{ex[[e]s]|ices}=''boolean'']

						(-) Specifies that all indices in the output cache will be
						checked for internal consistency after creation.

						(-) The ''boolean'' component of this parameter has the
						following syntax:

						(--) { ''ON'' | ''OFF'' | ''TRUE'' | ''FALSE'' | ''YES'' |
								''NO'' }

						(-) The default for this parameter is ''OFF''.

						(.) [-force[d]_overwrite=''boolean'']

						(-) Specifies the action to be taken if the output cache
						already exists.

						(-) The ''boolean'' component of this parameter has the
						following syntax:

						(--) { ''ON'' | ''OFF'' | ''TRUE'' | ''FALSE'' | ''YES'' |
								''NO'' }

						(-) If this parameter is set to ''OFF'', then the program
						will abort if the output cache file exists. Otherwise, it
						will be overwritten.

						(-) The default for this parameter is ''OFF''.

						(.) [@''parameter-include-file-name'']

						(-) Specifies the name of a parameter include file from
						which are to be read parameters to this program. Parameter
						include files may themselves contain parameter include file
						specifications.

						(-) When a parameter include file is encountered on the
						command line, the program will attempt to open it for
						reading. It is an error if the file so specified does not
						exist or can not be read.

						(-) Each line of the parameter include file is parsed for
						its parameters just as if those parameters were entered on
						the command line except for the following rules:

						(..) A line in which the first non-whitespace character is
						a number-sign (''#'') is considered to be the start of a
						comment and is ignored.

						(..) Blank lines (that is, lines which are empty or which
						consist wholly of whitespace) are ignored.

	RETURNS		:	Return status codes from this program are as follow:

						(.) Zero if all parameters were valid and the input cache
						was copied to the output cache.

						(.) Non-zero if an error occurs.

	CAVEATS		:	

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2018 Michael L. Brock

	OUTPUT INDEX:	cpycache
						DCR Cache Utilities:cpycache

	PUBLISH XREF:	cpycache

	PUBLISH NAME:	cpycache

EOH */
/*	***********************************************************************	*/
int main(argc, argv)
int    argc;
char **argv;
{
	int                    return_code;
	DCR_CPY_CONTROL  control_data;
	void                  *user_data_ptr_list[DCR_USER_DATA_PTR_COUNT];
	char                   error_text[DCR_MAX_ERROR_TEXT];

	memset(&control_data,       '\0', sizeof(control_data));
	memset(&user_data_ptr_list, '\0', sizeof(user_data_ptr_list));

	if ((return_code = DCR_CPY_GetParams(&control_data,
		((unsigned int) argc), argv, error_text)) == DCR_SUCCESS) {
		user_data_ptr_list[0] = &control_data;
		SDTIF_GetTimeUSecs(&control_data.overhead_end_time);
		if (control_data.version_flag != DCR_TRUE) {
			if ((return_code = DCR_CPY_OpenInputCache(&control_data,
				error_text)) == DCR_SUCCESS) {
				return_code = DCR_CPY_DoCopy(&control_data,
					((const void **) user_data_ptr_list), error_text);
			}
			if ((return_code != DCR_SUCCESS) &&
				(control_data.cache_ptr != NULL)) {
				MFILE_LogMessageContext(&control_data.log_context, NULL, LOG_INFO,
					MFILE_FALSE, "Closing and unlinking the cache file '%s'.\n",
					control_data.cache_ptr->cache_file_name);
				DCR_CloseOneCache(control_data.cache_ptr);
				control_data.cache_ptr = NULL;
				unlink(control_data.cache_file_name);
			}
		}
		DCR_CPY_End(&control_data, 0, NULL, NULL);
		GEN_SIGNAL_SignalDefault();
	}

	if (return_code != DCR_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n%s", error_text,
			(return_code != DCR_BAD_ARGS_FAILURE) ? "" :
			"       Help is available with the '-HELP' parameter.\n\n");

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static int DCR_CPY_OpenInputCache(control_ptr, error_text)
DCR_CPY_CONTROL *control_ptr;
char                  *error_text;
{
	int          return_code;
	unsigned int count_1;
	unsigned int found_index;

	if ((return_code = DCR_OpenRead(&control_ptr->cache_control_data,
		control_ptr->in_cache_file_name, 0, 0, 0, 0, &control_ptr->in_cache_ptr,
		&control_ptr->in_cache_index, error_text)) != DCR_SUCCESS)
		MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_ERR,
			MFILE_FALSE, "%s\n", error_text);
	else if ((return_code =
		DCR_MapDataAndIndices(control_ptr->in_cache_ptr, error_text)) !=
		DCR_SUCCESS)
		MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_ERR,
			MFILE_FALSE, "%s\n", error_text);
	else if ((control_ptr->kept_index_list = ((unsigned int *)
		malloc(control_ptr->in_cache_ptr->index_count *
		sizeof(unsigned int)))) == NULL) {
		sprintf(error_text, "%s (%u elements * %u size = %u total bytes).",
			"Unable to allocate memory for the list of kept indices",
			control_ptr->in_cache_ptr->index_count, sizeof(unsigned int),
			control_ptr->in_cache_ptr->index_count * sizeof(unsigned int));
		MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_ERR,
			MFILE_FALSE, "%s\n", error_text);
		return_code = DCR_MEMORY_FAILURE;
	}
	else {
		control_ptr->kept_index_count =
			control_ptr->in_cache_ptr->index_count;
		for (count_1 = 0; count_1 < control_ptr->kept_index_count; count_1++)
			control_ptr->kept_index_list[count_1] = count_1 + 1;
		for (count_1 = 0; count_1 < control_ptr->index_drop_count; count_1++) {
			if (DCR_FIND_INDEX_NAME(
				control_ptr->in_cache_ptr->index_name_count,
				control_ptr->in_cache_ptr->index_name_list,
				control_ptr->index_drop_list[count_1], &found_index) ==
				STRFUNCS_ITEM_FOUND)
				control_ptr->kept_index_list[control_ptr->in_cache_ptr->
					index_name_list[found_index].index_number] = 0;
			else {
				MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_ERR,
					DCR_FALSE, "%s ('%s') %s '%s'.\n",
					"The index specified in a '-DROP_INDEX=' parameter",
					control_ptr->index_drop_list[count_1],
					"was not found in the input cache file",
					control_ptr->in_cache_file_name);
				return_code = DCR_FAILURE;
			}
		}
		if (return_code == DCR_SUCCESS) {
			for (count_1 = 0; count_1 < control_ptr->kept_index_count; ) {
				if (!control_ptr->kept_index_list[count_1])
					mema_remove(&control_ptr->kept_index_count,
						((void **) &control_ptr->kept_index_list),
						sizeof(unsigned int), count_1, 1);
				else
					control_ptr->kept_index_list[count_1++]--;
			}
		}
		else
			strcpy(error_text,
				"Indices to be dropped were not found in the input cache.");
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static int DCR_CPY_DoCopy(control_ptr, user_data_ptr_list,
	error_text)
DCR_CPY_CONTROL  *control_ptr;
const void            **user_data_ptr_list;
char                   *error_text;
{
	int              return_code;
	unsigned int     count_1;
	unsigned int     count_2;
	unsigned int     added_field_count = 0;
	char           **added_field_list  = NULL;
	unsigned int     index_spec_count  = 0;
	char           **index_spec_list   = NULL;
	DCR_CACHE       *in_cache_ptr      = NULL;
	DCR_CACHE       *out_cache_ptr     = NULL;
   unsigned int     index_method;
	long             data_area_diff;
	DCR_STAT   tmp_stat;
	struct timeval   tmp_timeval;
	char             tmp_buffer_1[100];
	char             tmp_buffer_2[100];

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Don't over-write an existing file . . .								*/
	/*	*****************************************************************	*/
	if (!access(control_ptr->cache_file_name, F_OK)) {
		if (control_ptr->force_overwrite_flag != DCR_TRUE) {
			sprintf(error_text, "The output cache file '%-.500s' already exists.",
				control_ptr->cache_file_name);
			return_code = DCR_FAILURE;
			goto EXIT_FUNCTION;
		}
		MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_WARNING,
			MFILE_FALSE, "The output cache file '%s' %s.\n",
			control_ptr->cache_file_name,
			"already exists --- will be over-written");
	}
	/*	*****************************************************************	*/

	in_cache_ptr = control_ptr->in_cache_ptr;

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Construct the added field list . . .									*/
	/*	*****************************************************************	*/
	for (count_1 = 0; count_1 < in_cache_ptr->field_count; count_1++) {
		if (!(*in_cache_ptr->field_list[count_1].db_column_name)) {
			if (meml_allocate(&added_field_count, ((void ***) &added_field_list),
				STR_sizeof(DCR_FIELD, field_name) + 1 +
				STR_sizeof(DCR_FIELD, type_name) + 1 +
				STR_VAL2STR_MAX_LEN + 1 + 1, 1) != STRFUNCS_SUCCESS) {
				strcpy(error_text,
					"Unable to allocate the temporary field list.");
				return_code = DCR_MEMORY_FAILURE;
				goto EXIT_FUNCTION;
			}
			sprintf(added_field_list[added_field_count - 1], "%s,%s,%u",
				in_cache_ptr->field_list[count_1].field_name,
				in_cache_ptr->meta_type_list[in_cache_ptr->field_list[count_1].
				mtype_index].type_name,
				in_cache_ptr->field_list[count_1].primitive_type_count);
		}
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Construct index specifications for any indices which we're		*/
	/*	going to keep in the output cache . . .									*/
	/*	*****************************************************************	*/
	for (count_1 = 0; count_1 < control_ptr->kept_index_count; count_1++) {
		index_method = control_ptr->kept_index_list[count_1];
		if (meml_allocate(&index_spec_count, ((void ***) &index_spec_list),
			DCR_MAX_INDEX_NAME + 1 + 1 +
			DCR_GetIndexStringLen(in_cache_ptr, index_method), 1) !=
			STRFUNCS_SUCCESS) {
			strcpy(error_text, "Unable to allocate the temporary index list.");
			return_code = DCR_MEMORY_FAILURE;
			goto EXIT_FUNCTION;
		}
		strcat(strcpy(index_spec_list[count_1],
			in_cache_ptr->index_list[index_method].index_name), "=");
		DCR_GetIndexString(in_cache_ptr, index_method,
			index_spec_list[count_1] + strlen(index_spec_list[count_1]));
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Add any additional indices specified on the command-line . . .	*/
	/*	*****************************************************************	*/
	if (strl_add(control_ptr->index_spec_count, control_ptr->index_spec_list,
		&index_spec_count, &index_spec_list) != STRFUNCS_SUCCESS) {
		strcpy(error_text, "Unable to allocate the temporary index list.");
		return_code = DCR_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Create the output cache . . .												*/
	/*	*****************************************************************	*/
	if ((return_code = DCR_CPY_CreateOutputCache(control_ptr,
		user_data_ptr_list, added_field_count, added_field_list,
		index_spec_count, index_spec_list, &control_ptr->cache_ptr,
		&control_ptr->cache_index, error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	out_cache_ptr = control_ptr->cache_ptr;

	if (in_cache_ptr->record_count) {
		MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
			MFILE_FALSE, "Copying %u records from '%s' to '%s'.\n",
			in_cache_ptr->record_count, control_ptr->in_cache_file_name,
			control_ptr->cache_file_name);
		memset(&tmp_stat, '\0', sizeof(tmp_stat));
		DCR_StatStartTime(&tmp_stat);
		memcpy(((char *) out_cache_ptr->mmap_ptr) +
			out_cache_ptr->data_area_offset,
			((char *) in_cache_ptr->record_mmap_ptr) +
			in_cache_ptr->data_area_offset,
			in_cache_ptr->record_count * out_cache_ptr->total_record_size);
		out_cache_ptr->record_count             = in_cache_ptr->record_count;
		out_cache_ptr->header_ptr->record_count = in_cache_ptr->record_count;
		DCR_StatEndTime(&tmp_stat,
			((unsigned long) out_cache_ptr->record_count));
		MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
			MFILE_FALSE, "Copied %u %s '%s' in %s time (%s %s).\n",
			out_cache_ptr->record_count, "records to the output cache file",
			control_ptr->cache_file_name, 
			SDTIF_FormatInterval_timeval(&tmp_stat.last_interval, tmp_buffer_1),
			SDTIF_FormatInterval_timeval(SDTIF_GetPerInterval_timeval(
			&tmp_stat.last_interval, tmp_stat.last_count, &tmp_timeval),
			tmp_buffer_2), "per record");
		data_area_diff                          =
			((long) out_cache_ptr->data_area_offset) -
			((long) in_cache_ptr->data_area_offset);
		if (control_ptr->re_index_flag == DCR_TRUE)
			control_ptr->kept_index_count = 0;
		for (count_1 = 0; count_1 < control_ptr->kept_index_count; count_1++) {
			index_method = control_ptr->kept_index_list[count_1];
			MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
				MFILE_FALSE,
				"Copying %u %s %u ('%s') %s '%s' to %s %u %s '%s'.\n",
				in_cache_ptr->record_count, "index elements from index number",
				index_method, in_cache_ptr->index_list[index_method].index_name,
				"in cache file", control_ptr->in_cache_file_name,
				"index number", count_1, "in cache file",
				control_ptr->cache_file_name);
			memcpy(out_cache_ptr->index_data_list[count_1].mmap_ptr,
				in_cache_ptr->index_data_list[index_method].mmap_ptr,
				out_cache_ptr->record_count *
				DCR_INDEX_ENTRY_SIZE(out_cache_ptr, count_1));
			MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
				MFILE_FALSE,
				"Copied %u %s %u ('%s') %s '%s' in %s time (%s %s).\n",
				out_cache_ptr->record_count,
				"index elements in index number", count_1,
				out_cache_ptr->index_list[count_1].index_name,
				"to the output cache file",
				control_ptr->cache_file_name, 
				SDTIF_FormatInterval_timeval(&tmp_stat.last_interval, tmp_buffer_1),
				SDTIF_FormatInterval_timeval(SDTIF_GetPerInterval_timeval(
				&tmp_stat.last_interval, tmp_stat.last_count, &tmp_timeval),
				tmp_buffer_2), "per record");
			if (data_area_diff) {
				MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
					MFILE_FALSE,
					"Fixing-up record offsets in index number %u ('%s').\n",
					count_1, control_ptr->cache_file_name);
				for (count_2 = 0; count_2 < in_cache_ptr->record_count; count_2++)
					*((unsigned long *) (DCR_IELE_TO_IPTR(out_cache_ptr,
						count_1, count_2) +
						DCR_INDEX_ENTRY_SIZE(out_cache_ptr, count_1))) +=
						data_area_diff;
				MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
					MFILE_FALSE, "Fixed-up %u %s %u ('%s') in %s time (%s %s).\n",
					out_cache_ptr->record_count,
					"index elements in index number", count_1,
					out_cache_ptr->index_list[count_1].index_name,
					SDTIF_FormatInterval_timeval(&tmp_stat.last_interval,
					tmp_buffer_1),
					SDTIF_FormatInterval_timeval(SDTIF_GetPerInterval_timeval(
					&tmp_stat.last_interval, tmp_stat.last_count, &tmp_timeval),
					tmp_buffer_2), "per record");
			}
		}
		for (count_1 = control_ptr->kept_index_count;
			count_1 < out_cache_ptr->index_count; count_1++) {
			if (DCR_INDEX_IS_INDIRECT(out_cache_ptr) == DCR_TRUE)
				DCR_IndexIndirect(out_cache_ptr, count_1,
					out_cache_ptr->index_data_list[count_1].index_entry_list);
			else
				DCR_IndexEmbedded(out_cache_ptr, count_1,
					out_cache_ptr->index_data_list[count_1].index_entry_list);
		}
	}

	if (control_ptr->check_index_flag == DCR_TRUE) {
		MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
			MFILE_FALSE, "Checking %u %s in cache file '%s'.\n",
			out_cache_ptr->index_count, (out_cache_ptr->index_count == 1) ?
			"index" : "indices", control_ptr->cache_file_name);
		return_code = DCR_CheckIndicesElements(out_cache_ptr, error_text);
	}

	if (return_code == DCR_SUCCESS) {
		out_cache_ptr->header_ptr->cache_lock_status.lock_count++;
		out_cache_ptr->header_ptr->cache_lock_status.lock_flag =
			DCR_STATUS_OK;
		out_cache_ptr->header_ptr->cache_status                =
			DCR_STATUS_OK;
		MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
			MFILE_FALSE, "Cache copy completed successfully.\n");
	}

EXIT_FUNCTION:

	strl_remove_all(&added_field_count, &added_field_list);
	strl_remove_all(&index_spec_count, &index_spec_list);

	if (return_code != DCR_SUCCESS)
		MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_ERR,
			MFILE_FALSE, "%s\n", error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static int DCR_CPY_CreateOutputCache(control_ptr, user_data_ptr_list,
	added_field_count, added_field_list, index_spec_count, index_spec_list,
	out_cache_ptr, out_cache_index, error_text)
DCR_CPY_CONTROL  *control_ptr;
const void            **user_data_ptr_list;
unsigned int            added_field_count;
char                  **added_field_list;
unsigned int            index_spec_count;
char                  **index_spec_list;
DCR_CACHE             **out_cache_ptr;
unsigned int           *out_cache_index;
char                   *error_text;
{
	int                return_code;
	DCR_CACHE         *in_cache_ptr      = NULL;
	DCR_HEADER  *cache_header_ptr  = NULL;
	DCR_CACHE         cache_data;
	int               errno_code;
	int               open_failure_flag;
	int               mmap_failure_flag;
	DCR_STAT    tmp_create_stat;

	in_cache_ptr = control_ptr->in_cache_ptr;

	memset(&tmp_create_stat, '\0', sizeof(tmp_create_stat));

	DCR_StatStartTime(&tmp_create_stat);

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	if ((return_code = DCR_MakeHeader(
		((char *) control_ptr->in_cache_ptr->header_ptr->cache_name),
		((char *) in_cache_ptr->header_ptr->db_spec_string),
		((char *) in_cache_ptr->header_ptr->server_name),
		((char *) in_cache_ptr->header_ptr->database_name),
		((char *) in_cache_ptr->header_ptr->owner_name),
		((char *) in_cache_ptr->header_ptr->table_name),
		((char *) in_cache_ptr->header_ptr->db_user_name),
		((char *) in_cache_ptr->header_ptr->db_pass_word),
		in_cache_ptr->header_ptr->initial_allocation_size,
		in_cache_ptr->header_ptr->allocation_size,
		in_cache_ptr->header_ptr->indirect_index_flag,
		0, NULL,
		added_field_count, added_field_list, index_spec_count, index_spec_list,
		&cache_header_ptr, error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	memset(&cache_data, '\0', sizeof(cache_data));

	cache_data.open_flag   = O_RDWR | O_CREAT | O_TRUNC;
	cache_data.mmap_prot   = PROT_READ | PROT_WRITE;
	cache_data.mmap_flag   = MAP_SHARED;
	cache_data.file_handle = -1;
	cache_data.mmap_ptr    = NULL;
	cache_data.mmap_size   = cache_header_ptr->header_area_size;

	if ((return_code = DCR_AddACache(&control_ptr->cache_control_data,
		control_ptr->cache_file_name, &cache_data, out_cache_ptr,
		out_cache_index, error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = DCR_AllocCache(*out_cache_ptr, cache_header_ptr,
		error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;

	(*out_cache_ptr)->cache_access_type                       =
		DCR_I_AM_WRITER;
	(*out_cache_ptr)->header_ptr->cache_lock_status.lock_flag =
		DCR_STATUS_BUILDING | DCR_STATUS_CRITICAL;
	(*out_cache_ptr)->header_ptr->cache_status                =
		DCR_STATUS_BUILDING | DCR_STATUS_CRITICAL;

	SDTIF_GetTimeUSecs(&((DCR_HEADER *) (*out_cache_ptr)->header_ptr)->
		cache_creation_time);

	if (user_data_ptr_list != NULL)
		memcpy(&(*out_cache_ptr)->user_data_ptr_list, user_data_ptr_list,
			sizeof((*out_cache_ptr)->user_data_ptr_list));

	DCR_SetUserCallBack(*out_cache_ptr,
		&DCR_CPY_CallBackMask, DCR_CPY_CallBack);
	DCR_SetCriticalCallBack(*out_cache_ptr,
		DCR_CPY_CriticalCallBack);

	if ((return_code = DCR_OpenRaw(control_ptr->cache_file_name,
		(*out_cache_ptr)->open_flag, DCR_CREATE_MODE,
		(*out_cache_ptr)->mmap_prot, (*out_cache_ptr)->mmap_flag,
		&(*out_cache_ptr)->file_handle, &(*out_cache_ptr)->mmap_ptr,
		&(*out_cache_ptr)->mmap_size, &errno_code, &open_failure_flag,
		&mmap_failure_flag, error_text)) == DCR_SUCCESS) {
		if ((return_code = DCR_TruncateCache(*out_cache_ptr,
			cache_header_ptr->header_area_size, error_text)) == DCR_SUCCESS) {
			memcpy(((void *) (*out_cache_ptr)->mmap_ptr), cache_header_ptr,
				((unsigned int) cache_header_ptr->header_area_size));
			DCR_BindHeader((*out_cache_ptr),
				(*out_cache_ptr)->header_ptr);
/* CODE NOTE: Should happen in header construction routine. */
(*out_cache_ptr)->header_ptr->allocated_record_count = 0;
			if ((return_code = DCR_ResizeCache(*out_cache_ptr,
				(*out_cache_ptr)->header_ptr->initial_allocation_size,
				DCR_FALSE, error_text)) == DCR_SUCCESS) {
				if ((return_code = DCR_ResizeCache(*out_cache_ptr,
					in_cache_ptr->record_count, DCR_FALSE, error_text)) ==
					DCR_SUCCESS)
					DCR_BindHeader((*out_cache_ptr),
						(*out_cache_ptr)->header_ptr);
			}
		}
	}

EXIT_FUNCTION:

	if (return_code != DCR_SUCCESS) {
		if (*out_cache_ptr != NULL)
			DCR_CloseOneCache(*out_cache_ptr);
		*out_cache_ptr   = NULL;
		*out_cache_index = 0;
	}

	if (cache_header_ptr != NULL)
		free(cache_header_ptr);

	if (return_code == DCR_SUCCESS) {
		DCR_StatEndTime(&tmp_create_stat, 1L);
		memset((*out_cache_ptr)->header_ptr->stat_list, '\0',
			sizeof((*out_cache_ptr)->header_ptr->stat_list));
		(*out_cache_ptr)->header_ptr->stat_list[DCR_STAT_CREATE] =
			tmp_create_stat;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static int DCR_CPY_GetParams(control_ptr, argc, argv, error_text)
DCR_CPY_CONTROL  *control_ptr;
unsigned int            argc;
char                  **argv;
char                   *error_text;
{
	int  return_code;
	char gen_error_text[GENFUNCS_MAX_ERROR_TEXT];

	DCR_CPY_Init(control_ptr);

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Catch signals . . .															*/
	/*	*****************************************************************	*/
#ifndef NARGS
	GEN_SIGNAL_SignalInit(&control_ptr->signal_received_flag,
		&control_ptr->queue_signal_flag, control_ptr,
		&control_ptr->log_context.mfile_ptr,
		((int (*)(const void *, size_t, size_t, void *)) mwrite),
		((void (*)(void *, int, int *, const char *)) DCR_CPY_End));
#else
	GEN_SIGNAL_SignalInit(&control_ptr->signal_received_flag,
		&control_ptr->queue_signal_flag, control_ptr,
		&control_ptr->log_context.mfile_ptr, mwrite, DCR_CPY_End);
#endif /* #ifndef NARGS */
	GEN_SIGNAL_SignalSet();
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Get the process start time (or an approximation thereof). We	*/
	/*	initially set the overhead end time to the start time so that a	*/
	/*	premature exit results in reasonable numbers . . .						*/
	/*	*****************************************************************	*/
	SDTIF_GetTimeUSecs(&control_ptr->start_time);
	control_ptr->overhead_end_time = control_ptr->start_time;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Operating system process identifier.									*/
	/*	*****************************************************************	*/
	control_ptr->process_id = getpid();
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		We want to start from a known state . . .								*/
	/*	*****************************************************************	*/
	if (setlocale(LC_ALL, "C") == NULL) {
		strcpy(error_text, "Attempt to 'setlocale(LC_ALL, \"C\")' failed.");
		return_code = DCR_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Don't want to run out of stack space, or something . . .			*/
	/*	*****************************************************************	*/
	if ((return_code = GEN_SetResourceLimitsToMax(gen_error_text)) !=
		GENFUNCS_SUCCESS) {
		nstrcpy(error_text, gen_error_text, DCR_MAX_ERROR_TEXT - 1);
		return_code = DCR_MAP_ERROR_GEN_TO_DCR(return_code);
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Here we get the full path name of the program --- if one has	*/
	/*	multiple versions lying about in your 'PATH', one might want to	*/
	/*	know from whence this instance came.										*/
	/*																							*/
	/*		We also get the 'short' name here --- that is, the program		*/
	/*	name without any directory information. This is useful for error	*/
	/*	messages and the like.															*/
	/*																							*/
	/*		Finally, we get the 'syslog()' program name. This value is the	*/
	/*	string which will be used by the program on calls to 'openlog()'.	*/
	/*	All messages sent to the operating 'syslog()' facility will be		*/
	/*	prefaced with this string.														*/
	/*	*****************************************************************	*/
	if ((return_code = GEN_ExpandToFullPathName(argv[0],
		&control_ptr->program_name, gen_error_text)) != GENFUNCS_SUCCESS) {
		sprintf(error_text, "Unable to expand the program name: %s.",
			gen_error_text);
		nstrcpy(error_text, gen_error_text, DCR_MAX_ERROR_TEXT - 1);
		return_code = DCR_MAP_ERROR_GEN_TO_DCR(return_code);
		goto EXIT_FUNCTION;
	}
	else if ((control_ptr->short_program_name =
		strdup(extract_file_name(control_ptr->program_name))) == NULL) {
		STR_AllocMsgItem(strlen(extract_file_name(control_ptr->program_name))+1,
			error_text, "Unable to allocate memory for the short program name");
		return_code = DCR_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if ((control_ptr->syslog_program_name = ((char *)
		calloc(strlen("DCR") + 1 +
		strlen(control_ptr->short_program_name) + 1, sizeof(char)))) == NULL) {
		STR_AllocMsgItem(strlen("DCR") + 1 +
			strlen(control_ptr->short_program_name) + 1, error_text,
			"Unable to allocate memory for the 'syslog()' program name");
		return_code = DCR_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}
	strcat(chrcat(strcpy(control_ptr->syslog_program_name, "DCR"),
		':'), control_ptr->short_program_name);
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Try to initialize operating system logging . . .					*/
	/*	*****************************************************************	*/
	openlog(control_ptr->syslog_program_name, LOG_PID | LOG_CONS | LOG_NDELAY,
		LOG_USER);
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		On what host is the program running?									*/
	/*	*****************************************************************	*/
	if ((return_code = GEN_DetermineHostName(control_ptr->host_name,
		gen_error_text)) != GENFUNCS_SUCCESS) {
		nstrcat(error_text, gen_error_text, DCR_MAX_ERROR_TEXT - 1);
		return_code = DCR_SYSTEM_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		What's our current working directory?									*/
	/*	*****************************************************************	*/
	if (getcwd(control_ptr->current_directory,
		sizeof(control_ptr->current_directory) - 2) == NULL) {
		strcpy(error_text, "Unable to determine the current directory: ");
		DCR_GEN_AppendLastErrorString(error_text);
		return_code = DCR_SYSTEM_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	if ((return_code =
		DCR_AllocCacheControl(&control_ptr->cache_control_data, 100,
		error_text)) == DCR_SUCCESS) {
#ifndef NARGS
		if ((return_code = GEN_GetParams(control_ptr, ((unsigned int) argc),
			argv, &control_ptr->help_flag, &control_ptr->version_flag,
			((int (*)(void *, unsigned int, char **, int, unsigned int,
			const char *, char *)) DCR_CPY_Parse), error_text)) == DCR_SUCCESS) {
#else
		if ((return_code = GEN_GetParams(control_ptr, ((unsigned int) argc),
			argv, &control_ptr->help_flag, &control_ptr->version_flag,
			DCR_CPY_Parse, error_text)) == DCR_SUCCESS) {
#endif /* #ifndef NARGS */
			if (control_ptr->help_flag == DCR_TRUE) {
				DCR_CPY_End(control_ptr, 0, NULL, NULL);
				GEN_DoFormatUsage(return_code, argv[0],
					"Help request with '-HELP' noted . . .", UsageList);
			}
			else if (control_ptr->version_flag == DCR_TRUE)
				fprintf(stderr, "%s Version Number %s\n", argv[0],
					DCR_CPY_VERSION_NUMBER);
			else if ((return_code = DCR_CPY_CheckParams(control_ptr,
				error_text)) == DCR_SUCCESS)
				return_code = DCR_CPY_OpenLogFile(control_ptr,
					error_text);
		}
		if (return_code != DCR_SUCCESS)
			DCR_CPY_End(control_ptr, 0, NULL, NULL);
	}

EXIT_FUNCTION:

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Now we know the real overhead end time . . .							*/
	/*	*****************************************************************	*/
	SDTIF_GetTimeUSecs(&control_ptr->overhead_end_time);
	/*	*****************************************************************	*/

	return(return_code);
}
/*	***********************************************************************	*/

static int DCR_CPY_CheckParams(control_ptr, error_text)
DCR_CPY_CONTROL *control_ptr;
char                  *error_text;
{
	int return_code = DCR_BAD_ARGS_FAILURE;

	if (control_ptr->in_cache_file_name == NULL)
		strcpy(error_text, "The input cache file name was not specified.");
	else if (control_ptr->cache_file_name == NULL)
		strcpy(error_text, "The output cache file name was not specified.");
	else if (!strcmp(control_ptr->in_cache_file_name,
		control_ptr->cache_file_name))
		sprintf(error_text, "%s ('%-.800s').",
			"The names of the input and output cache files are the same",
			control_ptr->cache_file_name);
	else
		return_code = DCR_SUCCESS;

	return(return_code);
}
/*	***********************************************************************	*/

static int DCR_CPY_OpenLogFile(control_ptr, error_text)
DCR_CPY_CONTROL *control_ptr;
char            *error_text;
{
	int          return_code = DCR_SUCCESS;
	char         time_buffer[100];
	char         buffer[4096 + STR_sizeof(DCR_HEADER, cache_name)];

	SDTIF_Format_time_t(&control_ptr->start_time.tv_sec, time_buffer);
	time_buffer[10] = '.';

	if ((control_ptr->log_file_directory == NULL) &&
		((control_ptr->log_file_directory = strdup(".")) == NULL)) {
		strcpy(error_text,
			"Unable to copy the default log file directory '.'.");
		return_code = DCR_MEMORY_FAILURE;
	}
	else {
		sprintf(buffer, "%s/%s.COPIED_DCR_LOG.%s.%u",
			control_ptr->log_file_directory, time_buffer, control_ptr->host_name,
			control_ptr->process_id);
		if ((control_ptr->log_file_name = strdup(buffer)) == NULL) {
			strcpy(error_text, "Unable to copy the name of the log file.");
			return_code = DCR_MEMORY_FAILURE;
		}
		else if ((control_ptr->log_context.mfile_ptr =
			mopen(control_ptr->log_file_name, "w")) == NULL) {
			sprintf(error_text, "%s '%-.500s' for writing --- ",
				"Unable to open the log file", control_ptr->log_file_name);
			DCR_GEN_GetLastErrorString(error_text);
			return_code = DCR_FAILURE;
		}
		else {
			control_ptr->log_file_mfile_ptr = 
				control_ptr->log_context.mfile_ptr;
			DCR_CPY_ShowSettings(control_ptr);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

static void DCR_CPY_ShowSettings(control_ptr)
DCR_CPY_CONTROL *control_ptr;
{
	unsigned int count_1;
	char         buffer[32];

	MFILE_LogSepStartLogContext(&control_ptr->log_context);

	MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
		MFILE_FALSE, "Program Name          : %s\n",
		control_ptr->program_name);
	MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
		MFILE_FALSE, "Version Number        : %s\n",
		DCR_CPY_VERSION_NUMBER);
	MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
		MFILE_FALSE, "Host Name             : %s\n",
		control_ptr->host_name);
	MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
		MFILE_FALSE, "Process ID            : %u\n",
		control_ptr->process_id);
	MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
		MFILE_FALSE, "Input Cache File Name : %s\n",
		control_ptr->in_cache_file_name);
	MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
		MFILE_FALSE, "Output Cache File Name: %s\n",
		control_ptr->cache_file_name);
	MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
		MFILE_FALSE, "Re-index Flag         : %s\n",
		GEN_GetBooleanString(control_ptr->re_index_flag, buffer));
	MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
		MFILE_FALSE, "Check Index Flag      : %s\n",
		GEN_GetBooleanString(control_ptr->check_index_flag, buffer));
	MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
		MFILE_FALSE, "Force Over-write Flag : %s\n",
		GEN_GetBooleanString(control_ptr->force_overwrite_flag, buffer));
	for (count_1 = 0; count_1 < control_ptr->index_spec_count; count_1++) {
		MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
			MFILE_FALSE, "Add Index             : %s\n",
			control_ptr->index_spec_list[count_1]);
	}
	for (count_1 = 0; count_1 < control_ptr->index_drop_count; count_1++) {
		MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
			MFILE_FALSE, "Drop Index            : %s\n",
			control_ptr->index_drop_list[count_1]);
	}
	MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
		MFILE_FALSE, "Current Dir           : %s\n",
		control_ptr->current_directory);
	MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
		MFILE_FALSE, "Log File Name         : %s\n",
		control_ptr->log_file_name);

	MFILE_LogSepEqualCharContext(&control_ptr->log_context);
}
/*	***********************************************************************	*/

static int DCR_CPY_Parse(control_ptr, argc, argv, call_flag, current_arg,
	this_arg, error_text)
DCR_CPY_CONTROL  *control_ptr;
unsigned int      argc;
char            **argv;
int               call_flag;
unsigned int      current_arg;
const char       *this_arg;
char             *error_text;
{
	int           return_code = DCR_SUCCESS;
	char         *data_ptr;
	unsigned int  arg_length;
	int           error_flag;
	char          gen_error_text[GENFUNCS_MAX_ERROR_TEXT];

	if (!call_flag) {
		if (GEN_ArgParse(this_arg, &arg_length, &data_ptr,
			"-INPUT_CACHE_FILE=", "-INPUT_CACHE_FILE_NAME=", NULL) ==
			GENFUNCS_TRUE) {
			if (control_ptr->in_cache_file_name != NULL) {
				fprintf(stderr, "WARNING: %s from '%s' to '%s'.\n",
					"The input cache file name specification has changed",
					control_ptr->in_cache_file_name, data_ptr);
				free(control_ptr->in_cache_file_name);
				control_ptr->in_cache_file_name = NULL;
			}
			if ((control_ptr->in_cache_file_name = strdup(data_ptr)) == NULL) {
				sprintf(error_text,
					"%s '%-*.*s' ('%-.500s') --- %u bytes required.",
					"Unable to allocate memory for the", ((int) arg_length),
					((int) arg_length), this_arg, data_ptr, strlen(data_ptr) + 1);
				return_code = DCR_MEMORY_FAILURE;
			}
		}
		else if (GEN_ArgParse(this_arg, &arg_length, &data_ptr,
			"-CACHE_FILE=", "-CACHE_FILE_NAME=", "-OUTPUT_CACHE_FILE=",
			"-OUTPUT_CACHE_FILE_NAME=", NULL) == GENFUNCS_TRUE) {
			if (control_ptr->cache_file_name != NULL) {
				fprintf(stderr, "WARNING: %s from '%s' to '%s'.\n",
					"The cache file name specification has changed",
					control_ptr->cache_file_name, data_ptr);
				free(control_ptr->cache_file_name);
				control_ptr->cache_file_name = NULL;
			}
			if ((control_ptr->cache_file_name = strdup(data_ptr)) == NULL) {
				sprintf(error_text,
					"%s '%-*.*s' ('%-.500s') --- %u bytes required.",
					"Unable to allocate memory for the", ((int) arg_length),
					((int) arg_length), this_arg, data_ptr, strlen(data_ptr) + 1);
				return_code = DCR_MEMORY_FAILURE;
			}
		}
		else if (GEN_ArgParse(this_arg, &arg_length, &data_ptr,
			"-LOG_DIR=", "-LOG_DIRECTORY=", "-LOGGING_DIR=",
			"-LOGGING_DIRECTORY=", NULL) == GENFUNCS_TRUE) {
			if (control_ptr->log_file_directory != NULL) {
				fprintf(stderr, "WARNING: %s from '%s' to '%s'.\n",
					"The log file directory name has changed",
					control_ptr->log_file_directory, this_arg + arg_length);
				free(control_ptr->log_file_directory);
				control_ptr->log_file_directory = NULL;
			}
			if ((control_ptr->log_file_directory =
				strdup(this_arg + arg_length)) == NULL) {
				sprintf(error_text,
					"%s '%-*.*s' ('%-.500s') --- %u bytes required.",
					"Unable to allocate memory for the", ((int) arg_length),
					((int) arg_length), this_arg, this_arg + arg_length,
					strlen(this_arg + arg_length) + 1);
				return_code = DCR_MEMORY_FAILURE;
			}
		}
		else if (GEN_ArgParse(this_arg, &arg_length, &data_ptr, "-ADD_INDEX=",
			"-ADD_INDEXS=", "-ADD_INDEXES=", "-ADD_INDICES=", NULL) ==
			GENFUNCS_TRUE) {
			if (!(*data_ptr))
				fprintf(stderr, "%s '%s' parameter encountered --- ignored.\n",
					"Empty index specification", this_arg);
			else if (strl_append(&control_ptr->index_spec_count,
				&control_ptr->index_spec_list, data_ptr) != STRFUNCS_SUCCESS) {
				sprintf(error_text,
					"%s '%-*.*s' ('%-.500s') --- %u bytes required.",
					"Unable to allocate memory for the", ((int) arg_length),
					((int) arg_length), this_arg, data_ptr, strlen(data_ptr) + 1);
				return_code = DCR_MEMORY_FAILURE;
			}
		}
		else if (GEN_ArgParse(this_arg, &arg_length, &data_ptr, "-DROP_INDEX=",
			"-DROP_INDEXS=", "-DROP_INDEXES=", "-DROP_INDICES=", NULL) ==
			GENFUNCS_TRUE) {
			if (!(*data_ptr))
				fprintf(stderr, "%s '%s' parameter encountered --- ignored.\n",
					"Empty index specification", this_arg);
			else if (strl_append(&control_ptr->index_drop_count,
				&control_ptr->index_drop_list, data_ptr) != STRFUNCS_SUCCESS) {
				sprintf(error_text,
					"%s '%-*.*s' ('%-.500s') --- %u bytes required.",
					"Unable to allocate memory for the", ((int) arg_length),
					((int) arg_length), this_arg, data_ptr, strlen(data_ptr) + 1);
				return_code = DCR_MEMORY_FAILURE;
			}
			else
				upper(control_ptr->index_drop_list
					[control_ptr->index_drop_count - 1]);
		}
		else if (GEN_ArgParseTruth(this_arg, &error_flag,
			&control_ptr->re_index_flag, gen_error_text, &arg_length,
			&data_ptr, "-RE_INDEX=", "-REINDEX=", NULL) == GENFUNCS_TRUE) {
			if (error_flag == GENFUNCS_TRUE) {
				nstrcpy(error_text, gen_error_text, DCR_MAX_ERROR_TEXT - 1);
				return_code = DCR_BAD_ARGS_FAILURE;
			}
		}
		else if (GEN_ArgParseTruth(this_arg, &error_flag,
			&control_ptr->check_index_flag, gen_error_text, &arg_length,
			&data_ptr, "-CHECK_INDEX=", "-CHECK_INDEXS=", "-CHECK_INDEXES=",
			"-CHECK_INDICES=", NULL) == GENFUNCS_TRUE) {
			if (error_flag == GENFUNCS_TRUE) {
				nstrcpy(error_text, gen_error_text, DCR_MAX_ERROR_TEXT - 1);
				return_code = DCR_BAD_ARGS_FAILURE;
			}
		}
		else if (GEN_ArgParseTruth(this_arg, &error_flag,
			&control_ptr->force_overwrite_flag, gen_error_text, &arg_length,
			&data_ptr, "-FORCE_WRITE=", "-FORCED_WRITE=", "-FORCE_OVERWRITE=",
			"-FORCED_OVERWRITE=", NULL) == GENFUNCS_TRUE) {
			if (error_flag == GENFUNCS_TRUE) {
				nstrcpy(error_text, gen_error_text, DCR_MAX_ERROR_TEXT - 1);
				return_code = DCR_BAD_ARGS_FAILURE;
			}
		}
		else {
			sprintf(error_text,
				"Invalid command-line argument encountered ('%-.500s%s').",
				this_arg, (strlen(this_arg) > 500) ? "<<<MORE>>>" : "");
			return_code = DCR_BAD_ARGS_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

static void DCR_CPY_Init(control_ptr)
DCR_CPY_CONTROL *control_ptr;
{
	memset(control_ptr, '\0', sizeof(*control_ptr));

	control_ptr->program_name             = NULL;
	control_ptr->short_program_name       = NULL;
	control_ptr->syslog_program_name      = NULL;
	control_ptr->system_version_number    = STR_VERSION_NUMBER_NULL;
	control_ptr->version_number           = STR_VERSION_NUMBER_NULL;
	control_ptr->system_version_string[0] = '\0';
	control_ptr->version_string[0]        = '\0';
	control_ptr->process_id               = 0;
	control_ptr->host_name[0]             = '\0';
	control_ptr->current_directory[0]     = '\0';
	control_ptr->help_flag                = DCR_FALSE;
	control_ptr->version_flag             = DCR_FALSE;
	control_ptr->signal_received_flag     = GENFUNCS_FALSE;
	control_ptr->queue_signal_flag        = GENFUNCS_FALSE;
	control_ptr->shut_down_flag           = GENFUNCS_FALSE;
	control_ptr->re_index_flag            = DCR_FALSE;
	control_ptr->check_index_flag         = DCR_FALSE;
	control_ptr->force_overwrite_flag     = DCR_FALSE;
	control_ptr->in_cache_file_name       = NULL;
	control_ptr->in_cache_ptr             = NULL;
	control_ptr->in_cache_index           = 0;
	control_ptr->cache_ptr                = NULL;
	control_ptr->cache_index              = 0;
	control_ptr->cache_file_name          = NULL;
	control_ptr->log_file_directory       = NULL;
	control_ptr->log_file_name            = NULL;
	control_ptr->log_file_mfile_ptr       = NULL;
	control_ptr->index_spec_count         = 0;
	control_ptr->index_spec_list          = NULL;
	control_ptr->index_drop_count         = 0;
	control_ptr->index_drop_list          = NULL;
	control_ptr->kept_index_count         = 0;
	control_ptr->kept_index_list          = NULL;
}
/*	***********************************************************************	*/

static void DCR_CPY_End(control_ptr, signal_number, exit_code_ptr,
	message_buffer)
DCR_CPY_CONTROL *control_ptr;
int                    signal_number;
int                   *exit_code_ptr;
const char            *message_buffer;
{
	unsigned int   count_1;
	unsigned long  total_usecs;
	struct timeval overhead_interval;
	struct timeval total_interval;
	struct rusage  rusage_data;
	char           tmp_buffer[512];
	char           tmp_interval[256];
	char           tmp_stat_name[DCR_MAX_STAT_NAME + 1];

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Get the end time of the program . . .								*/
	/*	**************************************************************	*/
	SDTIF_GetTimeUSecs(&control_ptr->end_time);
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Inform the user that we're bailing out . . .						*/
	/*	**************************************************************	*/
	if (control_ptr->log_context.mfile_ptr != NULL) {
		MFILE_LogSepEqualCharContext(&control_ptr->log_context);
		MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
			DCR_FALSE, "Exiting . . .\n");
	}
	else if ((control_ptr->log_context.file_flag != MFILE_TRUE) &&
		(control_ptr->help_flag != DCR_TRUE) &&
		(control_ptr->version_flag != DCR_TRUE))
		fprintf(stderr, "Exiting . . .\n");
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Show cache statistics . . .											*/
	/*	**************************************************************	*/
	if ((control_ptr->cache_ptr != NULL) &&
		(control_ptr->log_file_mfile_ptr != NULL)) {
		MFILE_LogSepEqualCharContext(&control_ptr->log_context);
		for (count_1 = 0; count_1 < DCR_STAT_COUNT; count_1++) {
			sprintf(tmp_buffer, "%s Time",
				strcpy(tmp_stat_name,
				initcaps(DCR_GetStatName(((int) count_1), tmp_stat_name))));
			MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
				MFILE_FALSE, "%-28.28s: %s\n", tmp_buffer,
				SDTIF_FormatInterval_timeval(&((DCR_HEADER *) control_ptr->
				cache_ptr->header_ptr)->stat_list[count_1].total_interval,
				tmp_interval));
		}
		MFILE_LogSepEqualCharContext(&control_ptr->log_context);
	}
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Show timing statistics . . .											*/
	/*	**************************************************************	*/
	MFILE_ShowExecTime(&control_ptr->start_time, &control_ptr->end_time,
		&control_ptr->overhead_end_time, &control_ptr->log_context);
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Show system resource usage . . .										*/
	/*	**************************************************************	*/
	MFILE_ShowExecRUsage(&control_ptr->log_context);
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Free the memory allocated to store the program name . . .	*/
	/*	**************************************************************	*/
	if (control_ptr->program_name != NULL) {
		free(control_ptr->program_name);
		control_ptr->program_name = NULL;
	}
	if (control_ptr->short_program_name != NULL) {
		free(control_ptr->short_program_name);
		control_ptr->short_program_name = NULL;
	}
	if (control_ptr->syslog_program_name != NULL) {
		free(control_ptr->syslog_program_name);
		control_ptr->syslog_program_name = NULL;
	}
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Free the list of added indices . . .								*/
	/*	**************************************************************	*/
	strl_remove_all(&control_ptr->index_spec_count,
		&control_ptr->index_spec_list);
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Free the list of dropped indices . . .								*/
	/*	**************************************************************	*/
	strl_remove_all(&control_ptr->index_drop_count,
		&control_ptr->index_drop_list);
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Free the list of kept indices . . .									*/
	/*	**************************************************************	*/
	if (control_ptr->kept_index_list != NULL)
		free(control_ptr->kept_index_list);
	control_ptr->kept_index_list = NULL;
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*	**************************************************************	*/
	if ((control_ptr->in_cache_ptr != NULL) ||
		(control_ptr->cache_ptr != NULL)) {
		if ((control_ptr->log_file_mfile_ptr != NULL) &&
			(control_ptr->in_cache_ptr != NULL))
			MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
				MFILE_FALSE, "Closing the input cache file '%s'.\n",
				control_ptr->cache_file_name);
		if ((control_ptr->log_file_mfile_ptr != NULL) &&
			(control_ptr->cache_ptr != NULL))
			MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
				MFILE_FALSE, "Closing the output cache file '%s'.\n",
				control_ptr->cache_file_name);
		DCR_CloseAllCaches(&control_ptr->cache_control_data);
		control_ptr->in_cache_ptr = NULL;
		control_ptr->cache_ptr    = NULL;
	}
	/*	**************************************************************	*/

	if (control_ptr->in_cache_file_name != NULL) {
		free(control_ptr->in_cache_file_name);
		control_ptr->in_cache_file_name = NULL;
	}

	if (control_ptr->cache_file_name != NULL) {
		free(control_ptr->cache_file_name);
		control_ptr->cache_file_name = NULL;
	}

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Close the log file (if open) and free-up any memory which	*/
	/*	associated with it . . .													*/
	/*	**************************************************************	*/
	if (control_ptr->log_context.mfile_ptr != NULL) {
		MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
			MFILE_FALSE, "Closing the log file '%s'.\n",
			control_ptr->log_file_name);
		MFILE_LogSepEndLogContext(&control_ptr->log_context);
		control_ptr->log_file_mfile_ptr->file_size =
			control_ptr->log_file_mfile_ptr->current_offset;
		mclose(control_ptr->log_context.mfile_ptr);
		control_ptr->log_context.mfile_ptr = NULL;
		control_ptr->log_context.file_ptr  = NULL;
	}
	if (control_ptr->log_file_directory != NULL) {
		free(control_ptr->log_file_directory);
		control_ptr->log_file_directory = NULL;
	}
	if (control_ptr->log_file_name != NULL) {
		free(control_ptr->log_file_name);
		control_ptr->log_file_name = NULL;
	}
	/*	**************************************************************	*/

	DCR_CPY_Init(control_ptr);
}
/*	***********************************************************************	*/

static int DCR_CPY_CallBack(cache_ptr, call_back_type,
	post_operation_flag, index_method, operation_flags, operation_count,
	operation_ptr, stat_ptr, return_code, error_text)
DCR_CACHE      *cache_ptr;
unsigned long   call_back_type;
int             post_operation_flag;
unsigned int    index_method;
int             operation_flags;
unsigned int    operation_count;
void           *operation_ptr;
DCR_STAT *stat_ptr;
int             return_code;
char           *error_text;
{
	DCR_CPY_CONTROL *control_ptr;
	struct timeval         tmp_timeval;
	char                   tmp_buffer_1[100];
	char                   tmp_buffer_2[100];

	control_ptr = DCR_GetUserDataPtr(cache_ptr, 0);

	if (call_back_type == DCR_CB_BULK_INSERT) {
		if ((post_operation_flag == DCR_TRUE) && (return_code == DCR_SUCCESS) &&
			(stat_ptr != NULL))
			MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
				MFILE_FALSE, "Bulk inserted %u records in %s time (%s %s).\n",
				operation_count,
				SDTIF_FormatInterval_timeval(&stat_ptr->last_interval,
				tmp_buffer_1),
				SDTIF_FormatInterval_timeval(SDTIF_GetPerInterval_timeval(
				&stat_ptr->last_interval, stat_ptr->last_count, &tmp_timeval),
				tmp_buffer_2), "per record");
	}
	else if (call_back_type == DCR_CB_BULK_SEARCH) {
		if ((post_operation_flag == DCR_TRUE) && (return_code == DCR_SUCCESS) &&
			(stat_ptr != NULL))
			MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
				MFILE_FALSE,
				"Bulk searched %u records (%u %s, %u %s) in %s time (%s %s).\n",
				operation_count, cache_ptr->last_search_update_count, "inserted",
				cache_ptr->last_search_insert_count, "updated",
				SDTIF_FormatInterval_timeval(&stat_ptr->last_interval,
				tmp_buffer_1),
				SDTIF_FormatInterval_timeval(SDTIF_GetPerInterval_timeval(
				&stat_ptr->last_interval, stat_ptr->last_count, &tmp_timeval),
				tmp_buffer_2), "per record");
	}
	else if (call_back_type == DCR_CB_INDEX_CACHE) {
		if ((post_operation_flag == DCR_TRUE) && (return_code == DCR_SUCCESS) &&
			(stat_ptr != NULL))
			MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
				MFILE_FALSE, "Indexed %u %s %u in %s time (%s %s).\n",
				operation_count, "records on index number", index_method,
				SDTIF_FormatInterval_timeval(&stat_ptr->last_interval,
				tmp_buffer_1),
				SDTIF_FormatInterval_timeval(SDTIF_GetPerInterval_timeval(
				&stat_ptr->last_interval, stat_ptr->last_count, &tmp_timeval),
				tmp_buffer_2), "per record");
	}
	else if (call_back_type == DCR_CB_SORT_CACHE) {
		if ((post_operation_flag == DCR_TRUE) && (return_code == DCR_SUCCESS) &&
			(stat_ptr != NULL))
			MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
				MFILE_FALSE, "Indexed %u %s %u in %s time (%s %s).\n",
				operation_count, "records on index number", index_method,
				SDTIF_FormatInterval_timeval(&stat_ptr->last_interval,
				tmp_buffer_1),
				SDTIF_FormatInterval_timeval(SDTIF_GetPerInterval_timeval(
				&stat_ptr->last_interval, stat_ptr->last_count, &tmp_timeval),
				tmp_buffer_2), "per record");
	}
	else if (call_back_type == DCR_CB_RESIZE_CACHE) {
		if ((post_operation_flag == DCR_TRUE) && (return_code == DCR_SUCCESS) &&
			(stat_ptr != NULL))
			MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
				MFILE_FALSE, "Re-sized the cache file to %lu bytes.\n",
				((DCR_HEADER *) cache_ptr->header_ptr)->total_cache_size);
	}
	else if (call_back_type == DCR_CB_INITIAL_LOAD) {
		if ((post_operation_flag == DCR_TRUE) && (return_code == DCR_SUCCESS) &&
			(stat_ptr != NULL))
			MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
				MFILE_FALSE, "Performed an database initial load of %u records.\n",
				operation_count);
	}
	else if (call_back_type == DCR_CB_RELOAD) {
		if ((post_operation_flag == DCR_TRUE) && (return_code == DCR_SUCCESS) &&
			(stat_ptr != NULL))
			MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
				MFILE_FALSE, "Performed an database re-load of %u records.\n",
				operation_count);
	}
	else if (call_back_type == DCR_CB_UPDATE) {
		if ((post_operation_flag == DCR_TRUE) && (return_code == DCR_SUCCESS) &&
			(stat_ptr != NULL))
			MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
				MFILE_FALSE, "Performed an database update load of %u records.\n",
				operation_count);
	}
	else if (call_back_type == DCR_CB_ALLOC_CHUNK) {
		;
	}
	else if (call_back_type == DCR_CB_CHECK_INDEX_1) {
		if ((post_operation_flag == DCR_TRUE) && (return_code == DCR_SUCCESS) &&
			(stat_ptr != NULL))
			MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
				MFILE_FALSE, "Checked %u %s %u in %s time (%s %s).\n",
				operation_count, "index entries on index number", index_method,
				SDTIF_FormatInterval_timeval(&stat_ptr->last_interval,
				tmp_buffer_1),
				SDTIF_FormatInterval_timeval(SDTIF_GetPerInterval_timeval(
				&stat_ptr->last_interval, stat_ptr->last_count, &tmp_timeval),
				tmp_buffer_2), "per record");
	}
	else if (call_back_type == DCR_CB_CHECK_INDEX_2) {
		if ((post_operation_flag == DCR_TRUE) && (return_code == DCR_SUCCESS) &&
			(stat_ptr != NULL))
			MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
				MFILE_FALSE, "Checked %u %s %u in %s time (%s %s).\n",
				operation_count, "index entries and records on index number",
				index_method, SDTIF_FormatInterval_timeval(&stat_ptr->last_interval,
				tmp_buffer_1),
				SDTIF_FormatInterval_timeval(SDTIF_GetPerInterval_timeval(
				&stat_ptr->last_interval, stat_ptr->last_count, &tmp_timeval),
				tmp_buffer_2), "per record");
	}

	return(DCR_SUCCESS);
}
/*	***********************************************************************	*/

static int DCR_CPY_CriticalCallBack(cache_ptr, call_back_type,
	post_operation_flag, operation_flags, operation_count, operation_ptr,
	return_code, error_text)
DCR_CACHE     *cache_ptr;
unsigned long  call_back_type;
int            post_operation_flag;
int            operation_flags;
unsigned int   operation_count;
void          *operation_ptr;
int            return_code;
char          *error_text;
{
	DCR_CPY_CONTROL *control_ptr;

	control_ptr = DCR_GetUserDataPtr(cache_ptr, 0);

	if (post_operation_flag == DCR_FALSE)
		control_ptr->queue_signal_flag = GENFUNCS_TRUE;
	else if (control_ptr->signal_received_flag ==  GENFUNCS_TRUE) {
		DCR_CPY_End(control_ptr, 0, NULL, error_text);
		exit(-1);
	}
	else
		control_ptr->queue_signal_flag = GENFUNCS_FALSE;

	return(DCR_SUCCESS);
}
/*	***********************************************************************	*/

