#include <string.h>

#include "mfile.h"

#define PROT_READ								0
#define PROT_WRITE							0

static const MFILE_MODE_ITEM MFILE_ValidModesList[] = {
	{ "r",  "rb",	MFILE_MODE_READ,							PROT_READ					},
	{ "rb", "rb",	MFILE_MODE_READ,							PROT_READ					},
	{ "w",  "wb+",	MFILE_MODE_WRITE,							PROT_READ | PROT_WRITE	},
	{ "wb", "wb+",	MFILE_MODE_WRITE,							PROT_READ | PROT_WRITE	},
	{ "r+", "rb+",	MFILE_MODE_READ | MFILE_MODE_WRITE,	PROT_READ | PROT_WRITE	},
	{ "rb+","rb+",	MFILE_MODE_READ | MFILE_MODE_WRITE,	PROT_READ | PROT_WRITE	},
	{ "r+b","rb+",	MFILE_MODE_READ | MFILE_MODE_WRITE,	PROT_READ | PROT_WRITE	},
	{ "w+", "wb+",	MFILE_MODE_READ | MFILE_MODE_WRITE,	PROT_READ | PROT_WRITE	},
	{ "wb+","wb+",	MFILE_MODE_READ | MFILE_MODE_WRITE,	PROT_READ | PROT_WRITE	},
	{ "w+b","wb+",	MFILE_MODE_READ | MFILE_MODE_WRITE,	PROT_READ | PROT_WRITE	}
};

static unsigned int    MFILE_ValidModesCount  = sizeof(MFILE_ValidModesList) /
	sizeof(MFILE_ValidModesList[0]);

const MFILE_MODE_ITEM *MFILE_ValidateMFILEMode(file_mode)
const char *file_mode;
{
	unsigned int           count_1;
	const MFILE_MODE_ITEM *mode_ptr = NULL;

	for (count_1 = 0; count_1 < MFILE_ValidModesCount; count_1++) {
		if (!strcmp(file_mode, MFILE_ValidModesList[count_1].real_mode_name)) {
			mode_ptr = MFILE_ValidModesList + count_1;
			break;
		}
	}

	return(mode_ptr);
}

