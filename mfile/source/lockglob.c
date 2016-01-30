/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MFILE Memory-mapped I/O Library Source Code Module								*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Locks/unlocks the MFILE global data.

	Revision History	:	1992-03-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/
 
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include "mfilei.h"

/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/* *********************************************************************** */
#ifndef NARGS
int MFILE_LockGlobal(unsigned int *mfile_count, MFILE ***mfile_list,
	char *error_text)
#else
int MFILE_LockGlobal(mfile_count, mfile_list, error_text)
unsigned int   *mfile_count;
MFILE        ***mfile_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	*mfile_count = 0;
	*mfile_list  = NULL;

	return(MFILE_SUCCESS);
}
/* *********************************************************************** */

/*
	ADF NOTE: No ADF.
*/
/* *********************************************************************** */
#ifndef NARGS
int MFILE_TryLockGlobal(unsigned int *mfile_count, MFILE ***mfile_list,
	char *error_text)
#else
int MFILE_TryLockGlobal(mfile_count, mfile_list, error_text)
unsigned int   *mfile_count;
MFILE        ***mfile_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	*mfile_count = 0;
	*mfile_list  = NULL;

	return(MFILE_SUCCESS);
}
/* *********************************************************************** */

/*
	ADF NOTE: No ADF.
*/
/* *********************************************************************** */
#ifndef NARGS
int MFILE_UnlockGlobal(char *error_text)
#else
int MFILE_UnlockGlobal(error_text)
char *error_text;
#endif /* #ifndef NARGS */
{
	return(MFILE_SUCCESS);
}
/* *********************************************************************** */

