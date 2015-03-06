/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Support for the ADF library file logic.

	Revision History	:	1994-05-06 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <memory.h>
#include <stdlib.h>

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_FreeInFileList(ADF_CONTROL *control_ptr)
#else
void ADF_FreeInFileList(control_ptr)
ADF_CONTROL *control_ptr;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;

	for (count_1 = 0; count_1 < control_ptr->in_file_count; count_1++)
		ADF_FREE_InFileItem(control_ptr->in_file_list + count_1);

	mema_remove_all(&control_ptr->in_file_count,
		((void **) &control_ptr->in_file_list));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_FREE_InFileItem(ADF_IN_FILE *in_file_ptr)
#else
void ADF_FREE_InFileItem(in_file_ptr)
ADF_IN_FILE *in_file_ptr;
#endif /* #ifndef NARGS */
{
	if (in_file_ptr->file_ptr != NULL)
		ADF_fclose(in_file_ptr->file_ptr);

	if (in_file_ptr->file_name != NULL)
		free(in_file_ptr->file_name);

	if (in_file_ptr->href_string != NULL)
		free(in_file_ptr->href_string);

	if (in_file_ptr->entry_buffer != NULL)
		free(in_file_ptr->entry_buffer);

	if (in_file_ptr->htext_buffer != NULL)
		free(in_file_ptr->htext_buffer);

	ADF_INIT_InFilePtr(in_file_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_INIT_InFilePtr(ADF_IN_FILE *in_file_ptr)
#else
void ADF_INIT_InFilePtr(in_file_ptr)
ADF_IN_FILE *in_file_ptr;
#endif /* #ifndef NARGS */
{
	memset(in_file_ptr, '\0', sizeof(*in_file_ptr));

	in_file_ptr->file_name    = NULL;
	in_file_ptr->href_string  = NULL;
	in_file_ptr->href_flag    = ADF_FALSE;
	in_file_ptr->file_ptr     = NULL;
	in_file_ptr->entry_buffer = NULL;
	in_file_ptr->htext_buffer = NULL;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_PadFile(ADF_FILE *adf_file_ptr, char *error_text)
#else
int ADF_PadFile(adf_file_ptr, error_text)
ADF_FILE *adf_file_ptr;
char     *error_text;
#endif /* #ifndef NARGS */
{
	return(ADF_PadFileBasic(adf_file_ptr, ADF_FILE_PAD_LENGTH, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_PadFileBasic(ADF_FILE *adf_file_ptr, unsigned long pad_modulus,
	char *error_text)
#else
int ADF_PadFileBasic(adf_file_ptr, pad_modulus, error_text)
ADF_FILE      *adf_file_ptr;
unsigned long  pad_modulus;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code = ADF_SUCCESS;
	unsigned long pad_count;
	unsigned int  adj_count;
	char          buffer[ADF_FILE_PAD_LENGTH * ADF_FILE_PAD_LENGTH];

	if ((pad_count = (ADF_ftell(adf_file_ptr) % pad_modulus)) != 0) {
		memset(buffer, '\0', sizeof(buffer));
		pad_count = pad_modulus - pad_count;
		while (pad_count) {
			adj_count = (pad_count > sizeof(buffer)) ? sizeof(buffer) :
				((unsigned int) pad_count);
			if ((return_code = ADF_FWrite(buffer, 1, adj_count, adf_file_ptr,
				error_text)) != ADF_SUCCESS)
				break;
			pad_count -= adj_count;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_FRead(void *buffer, size_t size, size_t count, ADF_FILE *adf_file_ptr,
	char *error_text)
#else
int ADF_FRead(buffer, size, count, adf_file_ptr, error_text)
void     *buffer;
size_t    size;
size_t    count;
ADF_FILE *adf_file_ptr;
char     *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code = ADF_SUCCESS;
	int           actual_count;
	unsigned long current_offset;

	current_offset = ADF_ftell(adf_file_ptr);

	if ((actual_count = ADF_fread(buffer, size, count, adf_file_ptr)) !=
		count) {
		sprintf(error_text, "%s %u %s %u %s %lu (%u blocks were read): ",
			"Error occurred while attempting to read", count,
			"blocks of size", size, "from the ADF database file at offset",
			current_offset, actual_count);
		ADF_GetLastErrorString(error_text);
		return_code = ADF_SYSTEM_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_FWrite(const void *buffer, size_t size, size_t count,
	ADF_FILE *adf_file_ptr, char *error_text)
#else
int ADF_FWrite(buffer, size, count, adf_file_ptr, error_text)
const void *buffer;
size_t      size;
size_t      count;
ADF_FILE   *adf_file_ptr;
char       *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code = ADF_SUCCESS;
	int           actual_count;
	unsigned long current_offset;

	current_offset = ADF_ftell(adf_file_ptr);

	if ((actual_count = ADF_fwrite(buffer, size, count, adf_file_ptr)) !=
		count) {
		sprintf(error_text, "%s %u %s %u %s %lu (%u blocks were written): ",
			"Error occurred while attempting to write", count,
			"blocks of size", size, "to the ADF database file at offset",
			current_offset, actual_count);
		ADF_GetLastErrorString(error_text);
		return_code = ADF_SYSTEM_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

