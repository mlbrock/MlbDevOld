/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Test Module											*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	

	Revision History	:	1995-08-11 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include "dcr.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define TEST_CACHE_FILE                "TESTFILE.SCF"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#ifndef NARGS
int main(void);
#else
int main();
#endif /* #ifndef NARGS */

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
int main()
{
	int                return_code   = DCR_SUCCESS;
	unsigned int       deleted_count = 0;
	DCR_CONTROL  cache_control_data;
	DCR_CACHE         *cache_ptr;
	unsigned int       cache_index;
	char               error_text[DCR_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for the DCR cache delete function\n");
	fprintf(stderr, "---- ------- --- --- --- ----- ------ --------\n\n");

	fprintf(stderr, "Will delete all records in cache file '%s'.\n\n",
		TEST_CACHE_FILE);

	if ((return_code = DCR_AllocCacheControl(&cache_control_data,
		100, error_text)) == DCR_SUCCESS) {
		fprintf(stderr, "Allocated the cache control structure.\n");
		if ((return_code = DCR_OpenWrite(&cache_control_data,
			TEST_CACHE_FILE, &cache_ptr, &cache_index, error_text)) ==
			DCR_SUCCESS) {
			fprintf(stderr, "Opened cache '%s' (%u records, cache size %u).\n",
				TEST_CACHE_FILE, cache_ptr->record_count,
				cache_ptr->total_cache_size);
			while (cache_ptr->record_count) {
#if 0
				if ((return_code = DCR_DeleteRecordByElement(cache_ptr,
					0, error_text)) != DCR_SUCCESS)
					break;
#endif /* #if 0 */
#if 0
				if ((return_code = DCR_DeleteRecordByElement(cache_ptr,
					cache_ptr->record_count - 1, error_text)) != DCR_SUCCESS)
					break;
#endif /* #if 0 */
#if 1
				if ((return_code = DCR_DeleteRecordByElement(cache_ptr,
					(rand() >> 3) % cache_ptr->record_count, error_text)) !=
					DCR_SUCCESS)
					break;
#endif /* #if 0 */
				if ((!(++deleted_count % 1000)) && ((return_code =
					DCR_CheckIndicesElements(cache_ptr, error_text)) !=
					DCR_SUCCESS))
					break;
			}
		}
		DCR_CloseAllCaches(&cache_control_data);
		if (return_code == DCR_SUCCESS)
			fprintf(stderr, "Deleted %u records from the cache '%s'.\n",
				deleted_count, TEST_CACHE_FILE);
	}

	if (return_code != DCR_SUCCESS)
		fprintf(stderr, "ERROR: %s\n", error_text);

	return(return_code);
}
/*	***********************************************************************	*/

