/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MFILE Memory-mapped I/O Library Source Code Module								*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Validates a memory-mapped file pointer.

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

#include "mfilei.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Some external variables needed by this function . . .						*/
/*	***********************************************************************	*/
COMPAT_EXTERN_DATA_DECL MFILE        *MFILE_EntryList;
COMPAT_EXTERN_DATA_DECL unsigned int  MFILE_EntryCount;
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  MFILE_ValidateMFILEPtr

   SYNOPSIS    :  return_code = MFILE_ValidateMFILEPtr(mfile_ptr);

						int    return_code;

						MFILE *mfile_ptr;

   DESCRIPTION :  Determines whether the specified ''MFILE'' pointer is
						valid and open.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``mfile_ptr``, which is the pointer to a structure of
						type ''MFILE''.

   RETURNS     :  Returns from this function are as follow:

						(.) Zero (0) if the pointer points to a valid open ''MFILE''
						structure.

						(.) Non-zero if the pointer does not point to a valid open
						''MFILE'' structure.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2014 Michael L. Brock

	OUTPUT INDEX:	MFILE_ValidateMFILEPtr
						Memory-mapped File Functions:Internal Functions:MFILE_ValidateMFILEPtr
						MFILE Functions:MFILE_ValidateMFILEPtr

	PUBLISH XREF:	MFILE_ValidateMFILEPtr

	PUBLISH NAME:	MFILE_ValidateMFILEPtr

	ENTRY CLASS	:	Memory-mapped File Functions:Internal Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int MFILE_ValidateMFILEPtr(MFILE *mfile_ptr)
#else
int MFILE_ValidateMFILEPtr(mfile_ptr)
MFILE *mfile_ptr;
#endif /* #ifndef NARGS */
{
	int return_code = 0;

#ifdef TEST_MAIN
	printf(">>> MFILE master list allocated count       : %u\n",
		MFILE_EntryCount);
	printf(">>> MFILE master list address               : %08lX (%lu)\n",
		((unsigned long) MFILE_EntryList), ((unsigned long) MFILE_EntryList));
	printf(">>> Incoming MFILE pointer                  : %08lX (%lu)\n",
		((unsigned long) mfile_ptr), ((unsigned long) mfile_ptr));
	printf(">>> Less than master list pointer           : %s\n",
		(mfile_ptr < MFILE_EntryList) ? "TRUE" : "FALSE");
	printf(">>> Element index greater than maximum (%3u): %s (%u)\n",
		MFILE_EntryCount,
		((((char *) mfile_ptr) - ((char *) MFILE_EntryList)) /
		sizeof(MFILE_EntryList[0]) > MFILE_EntryCount) ? "TRUE" : "FALSE",
		(((char *) mfile_ptr) - ((char *) MFILE_EntryList)) /
		sizeof(MFILE_EntryList[0]));
	printf(">>> Element not on an MFILE-sized boundary  : %s (%u %% %u = %u)\n",
		((((char *) mfile_ptr) - ((char *) MFILE_EntryList)) %
		sizeof(MFILE_EntryList[0])) ? "TRUE" : "FALSE",
		((char *) mfile_ptr) - ((char *) MFILE_EntryList),
		sizeof(MFILE_EntryList[0]),
		(((char *) mfile_ptr) - ((char *) MFILE_EntryList)) %
		sizeof(MFILE_EntryList[0]));
#endif /* #ifdef TEST_MAIN */

	if ((MFILE_EntryList == NULL) || (mfile_ptr < MFILE_EntryList) ||
		(((((char *) mfile_ptr) - ((char *) MFILE_EntryList)) /
		sizeof(MFILE_EntryList[0])) > MFILE_EntryCount) ||
		((((char *) mfile_ptr) - ((char *) MFILE_EntryList)) %
		sizeof(MFILE_EntryList[0])))
		return_code = -1;
	else if (!(mfile_ptr->mfile_flags & MFILE_FLAG_IN_USE)) {
		return_code = -1;
#ifdef TEST_MAIN
	printf(">>> Specified MFILE pointer is not in use   : %s\n",
		(!(mfile_ptr->mfile_flags & MFILE_FLAG_IN_USE)) ? "TRUE" : "FALSE");
#endif /* #ifdef TEST_MAIN */
	}

	return(return_code);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#ifndef MFILE_MMAP_NON_NATIVE
# include <unistd.h>
#endif /* #ifndef MFILE_MMAP_NON_NATIVE */


COMPAT_FN_DECL(int main, (void));

int main()
{
	int    return_code = MFILE_SUCCESS;
	int    mfile_code;
	MFILE *mfile_ptr_1;
	MFILE *mfile_ptr_2;

	fprintf(stderr,
		"Test routine for function 'MFILE_ValidateMFILEPtr()'\n");
	fprintf(stderr,
		"---- ------- --- -------- --------------------------\n\n");

	printf("Test 1 (FAILURE expected): passed a NULL pointer  --->\n");
	mfile_code = MFILE_ValidateMFILEPtr(NULL);
	printf("Test results: %s\n\n", (!mfile_code) ? "SUCCESS" : "FAILURE");

	printf("Test 2 (FAILURE expected): Passed a bad pointer   --->\n");
	mfile_code = MFILE_ValidateMFILEPtr(((MFILE *) &mfile_code));
	printf("Test results: %s\n\n", (!mfile_code) ? "SUCCESS" : "FAILURE");

	if ((mfile_ptr_1 = mopen("MFILETST.001", "w")) == NULL) {
		fprintf(stderr, "Unable to open test file 'MFILETST.001'.\n\n");
		return_code = MFILE_FAILURE;
	}
	else if ((mfile_ptr_2 = mopen("MFILETST.002", "w")) == NULL) {
		mclose(mfile_ptr_1);
		unlink("MFILETST.001");
		fprintf(stderr, "Unable to open test file 'MFILETST.002'.\n\n");
		return_code = MFILE_FAILURE;
	}
	else {
		printf("Test 3 (FAILURE expected): passed a NULL pointer  --->\n");
		mfile_code = MFILE_ValidateMFILEPtr(NULL);
		printf("Test results: %s\n\n", (!mfile_code) ? "SUCCESS" : "FAILURE");
		printf("Test 4 (FAILURE expected): Passed a bad pointer   --->\n");
		mfile_code = MFILE_ValidateMFILEPtr(((MFILE *) &mfile_code));
		printf("Test results: %s\n\n", (!mfile_code) ? "SUCCESS" : "FAILURE");
		printf("Test 5 (SUCCESS expected): Pointer to file one    --->\n");
		mfile_code = MFILE_ValidateMFILEPtr(mfile_ptr_1);
		printf("Test results: %s\n\n", (!mfile_code) ? "SUCCESS" : "FAILURE");
		printf("Test 6 (SUCCESS expected): Pointer to file two    --->\n");
		mfile_code = MFILE_ValidateMFILEPtr(mfile_ptr_2);
		printf("Test results: %s\n\n", (!mfile_code) ? "SUCCESS" : "FAILURE");
		mclose(mfile_ptr_1);
		unlink("MFILETST.001");
		printf("Test 7 (FAILURE expected): Pointer to closed file --->\n");
		mfile_code = MFILE_ValidateMFILEPtr(mfile_ptr_1);
		printf("Test results: %s\n\n", (!mfile_code) ? "SUCCESS" : "FAILURE");
		mclose(mfile_ptr_2);
		unlink("MFILETST.002");
		printf("Test 8 (FAILURE expected): Pointer to closed file --->\n");
		mfile_code = MFILE_ValidateMFILEPtr(mfile_ptr_2);
		printf("Test results: %s\n\n", (!mfile_code) ? "SUCCESS" : "FAILURE");
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

