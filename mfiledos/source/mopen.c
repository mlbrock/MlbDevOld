#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include "mfile.h"

#define MAP_SHARED							0

MFILE        *MFILE_EntryList  = NULL;
unsigned int  MFILE_EntryCount = 0;

MFILE *mopen(file_name, file_mode)
const char *file_name;
const char *file_mode;
{
	MFILE                 *return_ptr = NULL;
	MFILE                 *mfile_ptr  = NULL;
	unsigned int           count_1;
	const MFILE_MODE_ITEM *mode_ptr;
	struct stat            stat_data;

	for (count_1 = 0; count_1 < MFILE_EntryCount; count_1++) {
		if (!(MFILE_EntryList[count_1].mfile_flags & MFILE_FLAG_IN_USE)) {
			mfile_ptr = MFILE_EntryList + count_1;
			break;
		}
	}

	if (!mfile_ptr) {
		if (!MFILE_EntryList) {
			if ((MFILE_EntryList = ((MFILE *) calloc(64, sizeof(MFILE)))) !=
				NULL) {
				mfile_ptr        = MFILE_EntryList;
				MFILE_EntryCount = 64;
			}
		}
	}

	if (mfile_ptr && ((mode_ptr = MFILE_ValidateMFILEMode(file_mode)) !=
		NULL)) {
		mfile_ptr->mfile_flags = mode_ptr->mfile_mode;
		mfile_ptr->mmap_mode   = mode_ptr->mmap_mode;
		mfile_ptr->mmap_prot   = mode_ptr->mmap_mode;
		mfile_ptr->mmap_flags  = MAP_SHARED;
		if ((mfile_ptr->file_name = strdup(file_name)) != NULL) {
			if ((mfile_ptr->file_ptr = fopen(file_name,
				mode_ptr->real_mode_name)) != NULL) {
				if ((strcmp(mode_ptr->real_mode_name, mode_ptr->mode_name)) &&
					(fclose(mfile_ptr->file_ptr) || ((mfile_ptr->file_ptr =
					fopen(file_name, mode_ptr->mode_name)) == NULL)))
					mfile_ptr->file_ptr = NULL;
				else if (!stat(mfile_ptr->file_name, &stat_data)) {
					mfile_ptr->file_size = stat_data.st_size;
					return_ptr           = mfile_ptr;
				}
			}
		}
		if (return_ptr)
			return_ptr->mfile_flags = mode_ptr->mfile_mode | MFILE_FLAG_IN_USE;
		else {
			if (mfile_ptr->file_ptr) {
				fclose(mfile_ptr->file_ptr);
				if (strcmp(file_mode, "w"))
					unlink(mfile_ptr->file_name);
			}
			if (mfile_ptr->file_name)
				free(mfile_ptr->file_name);
			memset(mfile_ptr, '\0', sizeof(*mfile_ptr));
		}
	}

	return(return_ptr);
}

