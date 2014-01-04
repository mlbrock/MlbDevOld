/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLB Executable Module Source File													*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Intercepts socket connections with logging.

	Revision History	:	1998-04-18 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Required include files . . .															*/
/*	***********************************************************************	*/

// #include <stdio.h>

#ifdef _Windows
# pragma warning(disable:4710 4786)
# if _MSC_VER >= 1300
#  pragma warning(disable:4217 4251 4555)
# endif /* # if _MSC_VER >= 1300 */
# pragma warning(disable:4018 4100 4146 4244 4245 4511 4512 4663)
# include <iomanip>
# include <iostream>
# include <sstream>
# include <vector>
# if _MSC_VER >= 1300
#  pragma warning(default:4217 4251 4555)
# endif /* # if _MSC_VER >= 1300 */
# pragma warning(default:4018 4100 4146 4244 4245 4511 4512 4663)
#else
# include <iomanip>
# include <iostream>
# include <sstream>
# include <vector>
#endif /* #ifdef _Windows */

#include <mfile.h>
#include <pcff.h>

#include "sockicpt.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
       int main(int argc, char **argv);
static int SOCICPT_EmitDataLogData(unsigned int read_length,
	const void *read_buffer_ptr, unsigned int *emit_buffer_length,
	void **emit_buffer_ptr, std::string *error_text);
/*	***********************************************************************	*/

/*	***********************************************************************	*/
typedef std::vector<SOCKICPT_LOG_ENTRY_HEADER> SOCKICPT_LogEntryDirVector;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SOCICPT_ReadDataLogDir(const char *file_name,
	SOCKICPT_LogEntryDirVector &dir_vector, std::string *error_text);
int SOCICPT_ReadDataLogDir(MFILE *mfile_ptr,
	SOCKICPT_LogEntryDirVector &dir_vector, std::string *error_text);
int SOCICPT_OpenDataLog(const char *file_name, MFILE **mfile_ptr,
	std::string *error_text);
int SOCICPT_ReadDataLogData(MFILE *mfile_ptr,
	const SOCKICPT_LOG_ENTRY_HEADER &log_entry, unsigned int *read_buffer_length,
	void **read_buffer_ptr, std::string *error_text);
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int main(int argc, char **argv)
{
	int                         return_code        = SOCKICPT_SUCCESS;
	bool                        socket_lib_open    = false;
	char                       *file_name          = NULL;
	bool                        log_detail_flag    = false;
	MFILE                      *mfile_ptr          = NULL;
	unsigned int                read_buffer_length = 0;
	void                       *read_buffer_ptr    = NULL;
	unsigned int                emit_buffer_length = 0;
	void                       *emit_buffer_ptr    = NULL;
	SOCKICPT_LogEntryDirVector  dir_vector;
	unsigned int                count_1;
	std::ostringstream          o_str;
	std::string                 error_text;
	char                        npsl_error_text[NPSL_MAX_ERROR_TEXT];
	char                        pcff_error_text[PCFF_MAX_ERROR_TEXT];

	/*	*****************************************************************
		*****************************************************************
		First, scan the command line parameters for a help request . . .
		*****************************************************************	*/
	if (PCFF_CMLPARAM_LocateHelp(argc, argv, NULL)) {
		std::cerr << std::endl << std::endl << "USAGE:" << std::endl <<
			"   " << extract_file_name(argv[0]) <<
			"[ -h | -help ] " <<
			"-file <data-log-file_name> " <<
			"[ -group ] " <<
			std::endl << std::endl;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Now scan the command line parameters to pick up the parameters . . .
		*****************************************************************	*/
	for (count_1 = 1; count_1 < ((unsigned int) argc); ++count_1) {
		if (PCFF_CMLPARAM_FindVA(argv[count_1], NULL, "-file", "-file_name",
			"-filename", NULL)) {
			if (PCFF_CMLPARAM_GetFollowing(argc, count_1, argv,
				PCFF_FLD_TYPE_PATH_NAME, (file_name != NULL), &file_name,
				pcff_error_text) != PCFF_SUCCESS) {
				error_text  = pcff_error_text;
				return_code = SOCKICPT_BAD_ARGS_FAILURE;
				goto EXIT_FUNCTION;
			}
			count_1++;
		}
		else if (PCFF_CMLPARAM_FindVA(argv[count_1], NULL, "-group", 
			"-grouping", NULL))
			log_detail_flag = true;
		else {
			o_str << "Invalid command line parameter encountered ('" <<
				argv[count_1] << "') --- use '-h' for help.";
			error_text  = o_str.str();
			return_code = SOCKICPT_FAILURE;
			goto EXIT_FUNCTION;
		}
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Ensure that the required parameters have been specified . . .
		*****************************************************************	*/
	if (file_name == NULL) {
		o_str << "The required parameter '-file' was not specified on the " <<
			"command line --- use '-h' for help.";
		error_text  = o_str.str();
		return_code = SOCKICPT_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Ensure the socket library is started (needed for Win32) . . .
		*****************************************************************	*/
	if (NPSL_SocketLibStartUp(NULL, npsl_error_text) != NPSL_SUCCESS) {
		error_text  = npsl_error_text;
		return_code = SOCKICPT_FAILURE;
		goto EXIT_FUNCTION;
	}
	socket_lib_open = true;
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Open and read the log file . . .
		*****************************************************************	*/
	if ((return_code = SOCICPT_OpenDataLog(file_name, &mfile_ptr,
		&error_text)) != SOCKICPT_SUCCESS)
		goto EXIT_FUNCTION;
	if ((return_code = SOCICPT_ReadDataLogDir(mfile_ptr, dir_vector,
		&error_text)) != SOCKICPT_SUCCESS)
		goto EXIT_FUNCTION;
	for (count_1 = 0; count_1 < dir_vector.size(); ++count_1) {
		std::cout <<
			std::setw(10) << count_1 << " " <<
			dir_vector[count_1] << std::endl;
		if ((return_code = SOCICPT_ReadDataLogData(mfile_ptr, dir_vector[count_1],
			&read_buffer_length, &read_buffer_ptr, &error_text)) !=
			SOCKICPT_SUCCESS)
			goto EXIT_FUNCTION;
		if ((return_code = SOCICPT_EmitDataLogData(dir_vector[count_1].data_length,
			read_buffer_ptr, &emit_buffer_length, &emit_buffer_ptr,
			&error_text)) != SOCKICPT_SUCCESS)
			goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

EXIT_FUNCTION:

	if (file_name != NULL)
		free(file_name);

	if (read_buffer_ptr != NULL)
		free(read_buffer_ptr);

	if (emit_buffer_ptr != NULL)
		free(emit_buffer_ptr);

	if (socket_lib_open)
		NPSL_SocketLibCleanUp(NULL, npsl_error_text);

	if (return_code != SOCKICPT_SUCCESS)
		std::cerr << std::endl << std::endl << "ERROR: " << error_text <<
			std::endl << std::endl;

	return((return_code == SOCKICPT_SUCCESS) ? EXIT_SUCCESS : EXIT_FAILURE);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SOCICPT_ReadDataLogDir(const char *file_name,
	SOCKICPT_LogEntryDirVector &dir_vector, std::string *error_text)
{
	int    return_code;
	MFILE *mfile_ptr;

	if ((return_code = SOCICPT_OpenDataLog(file_name, &mfile_ptr, error_text)) ==
		SOCKICPT_SUCCESS) {
		return_code = SOCICPT_ReadDataLogDir(mfile_ptr, dir_vector, error_text);
		mclose(mfile_ptr);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SOCICPT_ReadDataLogDir(MFILE *mfile_ptr,
	SOCKICPT_LogEntryDirVector &dir_vector, std::string *error_text)
{
	int                       return_code = SOCKICPT_SUCCESS;
	unsigned long             file_size;
	unsigned long             current_offset;
	SOCKICPT_LOG_ENTRY_HEADER tmp_entry;

	mseek(mfile_ptr, 0L, SEEK_END);
	file_size = mtell(mfile_ptr);
	mseek(mfile_ptr, 0L, SEEK_SET);

	current_offset = 0L;

	while ((file_size - current_offset) > sizeof(SOCKICPT_LOG_ENTRY_HEADER)) {
		if (mread(&tmp_entry, sizeof(tmp_entry), 1, mfile_ptr) != 1) {
			if (error_text != NULL) {
				std::ostringstream o_str;
				char               gen_error_text[GENFUNCS_MAX_ERROR_TEXT];
				o_str <<
					"Error occurred while attempting to read a SOCKICPT log" <<
					"entry at offset" << current_offset << "from file '" <<
					MFILE_GetFileName(mfile_ptr) << "': " <<
					GEN_GetLastErrorString(0, GENFUNCS_MAX_ERROR_TEXT,
						gen_error_text);
				*error_text = o_str.str();
			}
			return_code = SOCKICPT_SYSTEM_FAILURE;
			break;
		}
		dir_vector.push_back(tmp_entry);
		current_offset = tmp_entry.next_offset;
		if (current_offset >= file_size)
			break;
		mseek(mfile_ptr, current_offset, SEEK_SET);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SOCICPT_ReadDataLogData(MFILE *mfile_ptr,
	const SOCKICPT_LOG_ENTRY_HEADER &log_entry, unsigned int *read_buffer_length,
	void **read_buffer_ptr, std::string *error_text)
{
	int   return_code = SOCKICPT_SUCCESS;
	void *tmp_ptr;

	if (*read_buffer_length < log_entry.data_length) {
		tmp_ptr = (!(*read_buffer_length)) ?
			calloc(log_entry.data_length, sizeof(char)) :
			realloc(*read_buffer_ptr, log_entry.data_length * sizeof(char));
		if (tmp_ptr != NULL) {
			*read_buffer_length = log_entry.data_length;
			*read_buffer_ptr    = tmp_ptr;
		}
		else {
			if (error_text != NULL) {
				std::ostringstream o_str;
				o_str << "Unable to allocate " << log_entry.data_length <<
					" bytes of memory to read the log entry data from file '" <<
					MFILE_GetFileName(mfile_ptr) << "'.";
				*error_text = o_str.str();
			}
			return_code = SOCKICPT_MEMORY_FAILURE;
		}
	}

	if (return_code == SOCKICPT_SUCCESS) {
		mseek(mfile_ptr, log_entry.this_offset + sizeof(log_entry), SEEK_SET);
		if (mread(*read_buffer_ptr, log_entry.data_length * sizeof(char), 1,
			mfile_ptr) != 1) {
			if (error_text != NULL) {
				std::ostringstream o_str;
				char               gen_error_text[GENFUNCS_MAX_ERROR_TEXT];
				o_str <<
					"Error occurred while attempting to read SOCKICPT log" <<
					"entry data at offset" <<
					log_entry.this_offset + sizeof(log_entry) << "from file '" <<
					MFILE_GetFileName(mfile_ptr) << "': " <<
					GEN_GetLastErrorString(0, GENFUNCS_MAX_ERROR_TEXT,
						gen_error_text);
				*error_text = o_str.str();
			}
			return_code = SOCKICPT_SYSTEM_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SOCICPT_OpenDataLog(const char *file_name, MFILE **mfile_ptr,
	std::string *error_text)
{
	if ((*mfile_ptr = mopen(file_name, "rb")) != NULL)	
		return(SOCKICPT_SUCCESS);
	else {
		std::ostringstream o_str;
		char               gen_error_text[GENFUNCS_MAX_ERROR_TEXT];
		if (error_text != NULL) {
			o_str << "Unable to open SOCKICPT data log file '" << file_name <<
				"' for reading: " << GEN_GetLastErrorString(0,
				GENFUNCS_MAX_ERROR_TEXT, gen_error_text);
			*error_text = o_str.str();
		}
		return(SOCKICPT_FAILURE);
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static int SOCICPT_EmitDataLogData(unsigned int read_length,
	const void *read_buffer_ptr, unsigned int *emit_buffer_length,
	void **emit_buffer_ptr, std::string *error_text)
{
	int           return_code = SOCKICPT_SUCCESS;
	unsigned int  alloc_length;
	void         *tmp_ptr;

	alloc_length = 11 + (read_length * CHAR_BIT) + read_length + 1;

	if (*emit_buffer_length < alloc_length) {
		tmp_ptr = (!(*emit_buffer_length)) ? calloc(alloc_length, sizeof(char)) :
			realloc(*emit_buffer_ptr, alloc_length);
		if (tmp_ptr != NULL) {
			*emit_buffer_length = alloc_length;
			*emit_buffer_ptr    = tmp_ptr;
		}
		else {
			if (error_text != NULL) {
				std::ostringstream o_str;
				o_str << "Unable to allocate " << alloc_length <<
					" bytes of memory to emit the log entry data.";
				*error_text = o_str.str();
			}
			return_code = SOCKICPT_MEMORY_FAILURE;
		}
	}

	if (return_code == SOCKICPT_SUCCESS) {
		GEN_EmitBufferData(STR_FUNC_TYPE_fprintf_CAST(fprintf), stdout,
			NULL, 11, UINT_MAX, 1, 16, read_length, read_buffer_ptr);
	}

	return(return_code);
}
/*	***********************************************************************	*/


