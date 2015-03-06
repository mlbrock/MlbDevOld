/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MFILE Memory-mapped I/O Library Source Code Module								*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Locks/unlocks a memory-mapped file.

	Revision History	:	1992-03-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2015.
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
int MFILE_Lock(MFILE *mfile_ptr, char *error_text)
#else
int MFILE_Lock(mfile_ptr, error_text)
MFILE *mfile_ptr;
char  *error_text;
#endif /* #ifndef NARGS */
{
	return(MFILE_SUCCESS);
}
/* *********************************************************************** */

/*
	ADF NOTE: No ADF.
*/
/* *********************************************************************** */
#ifndef NARGS
int MFILE_TryLock(MFILE *mfile_ptr, char *error_text)
#else
int MFILE_TryLock(mfile_ptr, error_text)
MFILE *mfile_ptr;
char  *error_text;
#endif /* #ifndef NARGS */
{
	return(MFILE_SUCCESS);
}
/* *********************************************************************** */

/*
	ADF NOTE: No ADF.
*/
/* *********************************************************************** */
#ifndef NARGS
int MFILE_Unlock(MFILE *mfile_ptr, char *error_text)
#else
int MFILE_Unlock(mfile_ptr, error_text)
MFILE *mfile_ptr;
char  *error_text;
#endif /* #ifndef NARGS */
{
	return(MFILE_SUCCESS);
}
/* *********************************************************************** */

