/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MMI Memory-mapped Interface Library Source Code Module						*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	

	Revision History	:	1992-03-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include <mbcompat.h>

#include <limits.h>

#ifdef _Windows
# include <io.h>
#endif /* #ifdef _Windows */

#include <sdtif.h>
#include <genfuncs.h>

#include "mmii.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Windows Page Flag Names																	*/
/*	***********************************************************************	*/
#ifdef _Windows
static const MMI_FLAG_DEF MMI_Win32Page_FlagList[] = {
	{	"PAGE_READONLY",				PAGE_READONLY				},
	{	"PAGE_READWRITE",				PAGE_READWRITE				},
	{	"PAGE_EXECUTE",				PAGE_EXECUTE				},
	{	"PAGE_NOACCESS",				PAGE_NOACCESS				},
	{	"PAGE_EXECUTE_READ",			PAGE_EXECUTE_READ			},
	{	"PAGE_EXECUTE_READWRITE",	PAGE_EXECUTE_READWRITE	},
	{	"PAGE_EXECUTE_WRITECOPY",	PAGE_EXECUTE_WRITECOPY	},
	{	"PAGE_WRITECOPY",				PAGE_WRITECOPY				}
};
static const unsigned int MMI_Win32Page_FlagCount  =
	sizeof(MMI_Win32Page_FlagList) / sizeof(MMI_Win32Page_FlagList[0]);
#endif /* #ifdef _Windows */
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Windows File Flag Names																	*/
/*	***********************************************************************	*/
#ifdef _Windows
static const MMI_FLAG_DEF MMI_Win32File_FlagList[] = {
	{	"FILE_MAP_READ",	FILE_MAP_READ	},
	{	"FILE_MAP_WRITE",	FILE_MAP_WRITE	},
	{	"FILE_MAP_COPY",	FILE_MAP_COPY	}
};
static const unsigned int MMI_Win32File_FlagCount  =
	sizeof(MMI_Win32File_FlagList) / sizeof(MMI_Win32File_FlagList[0]);
#endif /* #ifdef _Windows */
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	

   SYNOPSIS    :	

   DESCRIPTION :	

   PARAMETERS  :	

   RETURNS     :	

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2014 Michael L. Brock

   OUTPUT INDEX:	
						Memory-mapped Interface Functions:See MMI Library Functions
						MMI Library Functions

   PUBLISH XREF:	

   PUBLISH NAME:	

	ENTRY CLASS	:	Memory-mapped Interface Functions

EOH */
/*	***********************************************************************	*/
#ifdef _Windows
# ifndef NARGS
void *MMI_WIN32_Map(MMI_ADDRESS address, MMI_LENGTH length,
	MMI_FLAG prot_flags, MMI_FLAG mmap_flags, MMI_FILE_HANDLE file_handle,
	MMI_OFFSET offset, MMI_MMAP_HANDLE_OS *os_mmap_handle, char *error_text)
# else
void *MMI_WIN32_Map(address, length, prot_flags, mmap_flags, file_handle,
	offset, os_mmap_handle, error_text)
MMI_ADDRESS         address;
MMI_LENGTH          length;
MMI_FLAG            prot_flags;
MMI_FLAG            mmap_flags;
MMI_FILE_HANDLE     file_handle;
MMI_OFFSET          offset;
MMI_MMAP_HANDLE_OS *os_mmap_handle;
char               *error_text;
# endif /* # ifndef NARGS */
{
	return(MMI_WIN32_MapOS(address, length, prot_flags, mmap_flags,
		((HANDLE) _get_osfhandle(file_handle)), offset, os_mmap_handle,
		error_text));
}
#endif /* #ifdef _Windows */
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	

   SYNOPSIS    :	

   DESCRIPTION :	

   PARAMETERS  :	

   RETURNS     :	

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2014 Michael L. Brock

   OUTPUT INDEX:	
						Memory-mapped Interface Functions:See MMI Library Functions
						MMI Library Functions

   PUBLISH XREF:	

   PUBLISH NAME:	

	ENTRY CLASS	:	Memory-mapped Interface Functions

EOH */
/*	***********************************************************************	*/
#ifdef _Windows
# ifndef NARGS
void *MMI_WIN32_MapOS(MMI_ADDRESS address, MMI_LENGTH length,
	MMI_FLAG prot_flags, MMI_FLAG mmap_flags, MMI_FILE_HANDLE_OS os_file_handle,
   MMI_OFFSET offset, MMI_MMAP_HANDLE_OS *os_mmap_handle, char *error_text)
# else
void *MMI_WIN32_MapOS(address, length, prot_flags, mmap_flags, os_file_handle,
	offset, os_mmap_handle, error_text)
MMI_ADDRESS         address;
MMI_LENGTH          length;
MMI_FLAG            prot_flags;
MMI_FLAG            mmap_flags;
MMI_FILE_HANDLE_OS  os_file_handle;
MMI_OFFSET          offset;
MMI_MMAP_HANDLE_OS *os_mmap_handle;
char               *error_text;
# endif /* # ifndef NARGS */
{
	void   *out_address = ((void *) -1);
	DWORD   create_flags;
	DWORD   map_view_flags;
	HANDLE  create_handle;
	char    mapping_name[3 + 1 + 5 + 1 + 17 + 1 + 8 + 1 + 8 + 1 + 25 + 1];
	char    time_buffer[SDTIF_FMT_TIME_LEN_TIMEVAL + 1];
	char    prot_string[MMI_FLAG_COMPLETE_MAX + 1];
	char    number_buffer_1[STR_VAL2STR_MAX_LEN + 1];
	char    number_buffer_2[STR_VAL2STR_MAX_LEN + 1];

	os_mmap_handle = (os_mmap_handle != NULL) ? os_mmap_handle :
		&create_handle;

	create_flags   = (mmap_flags & MMI_FLAG_MMAP_PRIVATE) ? PAGE_WRITECOPY :
						  (prot_flags & MMI_FLAG_PROT_WRITE)   ? PAGE_READWRITE :
						  (prot_flags & MMI_FLAG_PROT_READ)    ? PAGE_READONLY  :
						  PAGE_NOACCESS;
	map_view_flags = (mmap_flags & MMI_FLAG_MMAP_PRIVATE) ? FILE_MAP_COPY  :
						  (prot_flags & MMI_FLAG_PROT_WRITE)   ? FILE_MAP_WRITE :
						  FILE_MAP_READ;

	strcat(strcat(strcat(strcat(strcat(strcpy(mapping_name,
		"MMI_WIN32_CreateFileMapping_"),
		val2str(((unsigned long) os_file_handle), 0, 16, "0", number_buffer_1)),
		"_"),
		val2str(((unsigned long) address), 0, 16, "0", number_buffer_2)),
		"_"),
		SDTIF_Format_timeval(NULL, time_buffer));

/*
	CODE NOTE: 'CreateFileMapping()' use to be resolved.
	if ((*os_mmap_handle = CreateFileMapping(os_file_handle, NULL,
		((DWORD) create_flags), ((DWORD) 0), ((DWORD) 0), NULL)) == NULL) {
*/
	if ((*os_mmap_handle = CreateFileMapping(os_file_handle, NULL,
		((DWORD) create_flags), ((DWORD) 0), ((DWORD) 0),
		((LPCTSTR) mapping_name))) == NULL) {
		if (error_text != NULL) {
			sprintf(error_text,
"%s(%s = 0x%lx, %s = %s, %s = 0x%lx = %s, %s = %lu, %s = %lu, %s = %s) %s: ",
				"CreateFileMapping",
				"hFile", ((unsigned long) os_file_handle),
				"lpFileMappingAttributes", "NULL",
				"flProtect", ((unsigned long) create_flags),
				MMI_Win32PageFlags(create_flags, prot_string),
				"dwMaximumSizeHigh", 0L,
				"dwMaximumSizeLow", 0L,
				"lpName", "NULL", "failed");
			GEN_AppendLastErrorString(0, MMI_MAX_ERROR_TEXT, error_text);
		}
	}
	else if ((out_address = MapViewOfFileEx(*os_mmap_handle,
		((DWORD) map_view_flags), ((DWORD) 0), ((DWORD) offset), ((DWORD) length),
		((LPVOID) address))) == NULL) {
		if (error_text != NULL) {
			sprintf(error_text,
				"%s(%s = 0x%lx, %s = 0x%lx = %s, %s = %lu, %s = %lu, %s = %lu, \
%s = 0x%lx) %s: ",
				"MapViewOfFileEx",
				"hFileMappingObject", ((unsigned long) *os_mmap_handle),
				"dwDesiredAccess", ((unsigned long) map_view_flags),
				MMI_Win32FileFlags(map_view_flags, prot_string),
				"dwFileOffsetHigh", 0L,
				"dwFileOffsetLow", offset,
				"dwNumberOfBytesToMap", length,
				"lpBaseAddress", ((unsigned long) address),
				"failed");
			GEN_AppendLastErrorString(0, MMI_MAX_ERROR_TEXT, error_text);
			sprintf(error_text + strlen(error_text),
"%s(%s = 0x%lx, %s = %s, %s = 0x%lx = %s, %s = %lu, %s = %lu, %s = %s) %s",
				" ********** CreateFileMapping",
				"hFile", ((unsigned long) os_file_handle),
				"lpFileMappingAttributes", "NULL",
				"flProtect", ((unsigned long) create_flags),
				MMI_Win32PageFlags(create_flags, prot_string),
				"dwMaximumSizeHigh", 0L,
				"dwMaximumSizeLow", 0L,
				"lpName", "NULL", "succeeded. **********");
		}
		CloseHandle(*os_mmap_handle);
		*os_mmap_handle = NULL;
	}
	return((out_address != NULL) ? out_address : ((void *) -1));
}
#endif /* #ifdef _Windows */
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	

   SYNOPSIS    :	

   DESCRIPTION :	

   PARAMETERS  :	

   RETURNS     :	

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2014 Michael L. Brock

   OUTPUT INDEX:	
						Memory-mapped Interface Functions:See MMI Library Functions
						MMI Library Functions

   PUBLISH XREF:	

   PUBLISH NAME:	

	ENTRY CLASS	:	Memory-mapped Interface Functions

EOH */
/*	***********************************************************************	*/
#ifdef _Windows
# ifndef NARGS
void *MMI_WIN32_Protect(MMI_ADDRESS address, MMI_LENGTH length,
	MMI_FLAG prot_flags)
# else
void *MMI_WIN32_Protect(address, length, prot_flags)
MMI_ADDRESS  address;
MMI_LENGTH   length;
MMI_FLAG     prot_flags;
# endif /* # ifndef NARGS */
{
	DWORD new_prot_flags;
	DWORD old_prot_flags;

	new_prot_flags = MMI_ProtFlagToWin32PageFlag(prot_flags);

	return(((void *) ((VirtualProtect(((LPVOID) address), ((DWORD) length),
		new_prot_flags, &old_prot_flags)) ? 0 : -1)));
}
#endif /* #ifdef _Windows */
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifdef _Windows
# ifndef NARGS
char *MMI_Win32PageFlags(MMI_FLAG in_flags, char *out_string)
# else
char *MMI_Win32PageFlags(in_flags, out_string)
MMI_FLAG  in_flags;
char     *out_string;
# endif /* # ifndef NARGS */
{
	return(MMI_GetORedFlag(in_flags, "MMI Win32Page", MMI_Win32Page_FlagCount,
		MMI_Win32Page_FlagList, out_string));
}
#endif /* #ifdef _Windows */
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifdef _Windows
# ifndef NARGS
char *MMI_Win32FileFlags(MMI_FLAG in_flags, char *out_string)
# else
char *MMI_Win32FileFlags(in_flags, out_string)
MMI_FLAG  in_flags;
char     *out_string;
# endif /* #ifndef NARGS */
{
	return(MMI_GetORedFlag(in_flags, "MMI Win32File", MMI_Win32File_FlagCount,
		MMI_Win32File_FlagList, out_string));
}
#endif /* #ifdef _Windows */
/*	***********************************************************************	*/

#ifdef TEST_MAIN

COMPAT_FN_DECL(int main, (void));

# ifdef _Windows

COMPAT_FN_DECL_STATIC(void TEST_DoEnumFlag,
	(const char *in_name, unsigned int count, const MMI_FLAG_DEF *list));
COMPAT_FN_DECL_STATIC(void TEST_DoORedFlag,
	(const char *in_name, unsigned int count, const MMI_FLAG_DEF *list));

/*	***********************************************************************	*/
int main()
{
	TEST_DoORedFlag("MMI Win32Page", MMI_Win32Page_FlagCount,
		MMI_Win32Page_FlagList);
	TEST_DoORedFlag("MMI Win32File", MMI_Win32File_FlagCount,
		MMI_Win32File_FlagList);

	return(MMI_SUCCESS);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#  ifndef NARGS
static void TEST_DoEnumFlag(const char *in_name, unsigned int count,
	const MMI_FLAG_DEF *list)
#  else
static void TEST_DoEnumFlag(in_name, count, list)
const char         *in_name;
unsigned int        count;
const MMI_FLAG_DEF *list;
#  endif /* #  ifndef NARGS */
{
	unsigned int count_1;
	char         buffer[512];

	for (count_1 = 0; count_1 < count; count_1++)
		printf("%10lu = 0x%08lx: %s\n",
			list[count_1].value, list[count_1].value,
			MMI_GetEnumFlag(list[count_1].value, in_name, count, list, buffer));

	printf("%10lu = 0x%08lx: %s\n",
		((unsigned long) 0XFFFFFFFF), ((unsigned long) 0XFFFFFFFF),
		MMI_GetEnumFlag(0xFFFFFFFF, in_name, count, list, buffer));

	STR_EMIT_CharLine('-', 78, NULL, NULL);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#  ifndef NARGS
static void TEST_DoORedFlag(const char *in_name, unsigned int count,
	const MMI_FLAG_DEF *list)
#  else
static void TEST_DoORedFlag(in_name, count, list)
const char         *in_name;
unsigned int        count;
const MMI_FLAG_DEF *list;
#  endif /* #  ifndef NARGS */
{
	unsigned int count_1;
	unsigned int count_2;
	unsigned int count_3;
	char         buffer[512];

	for (count_1 = 0; count_1 < count; count_1++) {
		printf("%10lu = 0x%08lx: %s\n",
			list[count_1].value, list[count_1].value,
			MMI_GetORedFlag(list[count_1].value, in_name, count, list, buffer));
		for (count_2 = 0; count_2 < count; count_2++) {
			if (count_1 == count_2)
				continue;
			printf("%10lu = 0x%08lx: %s\n",
				list[count_1].value | list[count_2].value,
				list[count_1].value | list[count_2].value,
				MMI_GetORedFlag(list[count_1].value | list[count_2].value,
				in_name, count, list, buffer));
		}
		if (count < 3)
			continue;
		for (count_2 = 0; count_2 < count; count_2++) {
			if (count_1 == count_2)
				continue;
			for (count_3 = 0; count_3 < count; count_3++) {
				if ((count_1 == count_3) || (count_2 == count_3))
					continue;
				printf("%10lu = 0x%08lx: %s\n",
			list[count_1].value | list[count_2].value | list[count_3].value,
			list[count_1].value | list[count_2].value | list[count_3].value,
			MMI_GetORedFlag(list[count_1].value | list[count_2].value |
				list[count_3].value,
					in_name, count, list, buffer));
			}
		}
	}

	printf("%10lu = 0x%08lx: %s\n",
		((unsigned long) 0XFFFFFFFF), ((unsigned long) 0XFFFFFFFF),
		MMI_GetORedFlag(0xFFFFFFFF, in_name, count, list, buffer));

	STR_EMIT_CharLine('-', 78, NULL, NULL);
}
/*	***********************************************************************	*/

# else

/*	***********************************************************************	*/
int main()
{
	return(MMI_SUCCESS);
}
/*	***********************************************************************	*/

# endif /* #ifdef _Windows */

#endif /* #ifdef TEST_MAIN */


