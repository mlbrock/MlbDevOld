/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MFILE Memory-mapped I/O Library Source Code Module								*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Validates the 'mopen' mode of a memory-mapped file.

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
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include <string.h>

#include "mfilei.h"
#ifdef MFILE_MMAP_NON_NATIVE
#define PROT_READ								0
#define PROT_WRITE							0
#endif /* #ifdef MFILE_MMAP_NON_NATIVE */

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	The mode validation variables below are required only to validate an	*/
/* ANSI C level 2 I/O 'fopen()' mode string.											*/
/*	***********************************************************************	*/

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

static const unsigned int    MFILE_ValidModesCount  =
	sizeof(MFILE_ValidModesList) / sizeof(MFILE_ValidModesList[0]);

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  MFILE_ValidateMFILEMode

   SYNOPSIS    :  mode_item_ptr = MFILE_ValidateMFILEMode(file_mode);

						const MFILE_MODE_ITEM *mode_item_ptr;

						const char            *file_mode;

   DESCRIPTION :  Validates the specified file-open mode against the list
						supported by the memory-mapped file library.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``file_mode`` points to the string which contains the
						file-open mode to validated.

   RETURNS     :  Returns from this function are as follow:

						(.) A pointer to the equivalent mode string if the mode
						is validated successfully.

						(.) ''NULL'' if the mode is not validated successfully.

   NOTES       :  This function is used internally by the memory-mapped file
						library and generally need not be invoked by application
						programmers.

   CAVEATS     :  

   SEE ALSO    :  

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2014 Michael L. Brock

	OUTPUT INDEX:	MFILE_ValidateMFILEMode
						Memory-mapped File Functions:Internal Functions:MFILE_ValidateMFILEMode
						MFILE Functions:MFILE_ValidateMFILEMode

	PUBLISH XREF:	MFILE_ValidateMFILEMode

	PUBLISH NAME:	MFILE_ValidateMFILEMode

	ENTRY CLASS	:	Memory-mapped File Functions:Internal Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
const MFILE_MODE_ITEM *MFILE_ValidateMFILEMode(const char *file_mode)
#else
const MFILE_MODE_ITEM *MFILE_ValidateMFILEMode(file_mode)
const char *file_mode;
#endif /* #ifndef NARGS */
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
/* *********************************************************************** */

