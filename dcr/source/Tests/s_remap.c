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

	Revision History	:	1994-10-04 --- Creation.
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

#include <limits.h>
#include <memory.h>

#include "dcr.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#ifndef NARGS
int main(int argc, char **argv);
#else
int main();
#endif /* #ifndef NARGS */

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
int main(argc, argv)
int    argc;
char **argv;
{
	int                return_code;
	DCR_CONTROL  cache_control_data;
	DCR_CACHE         *cache_ptr;
	unsigned int       cache_index;
	unsigned int       target_record_count;
	unsigned int       old_record_count = UINT_MAX;
	unsigned int       old_cache_size;
	char               error_text[DCR_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for the DCR cache re-map function\n");
	fprintf(stderr, "---- ------- --- --- --- ----- ------ --------\n\n");

	fprintf(stderr, "USAGE:\n%s %s %s\n\n", argv[0], "<cache-name>",
		"[<record-count>]");

	if ((argc < 2) || (argc > 3)) {
		sprintf(error_text, "%s parameters (%s).",
			"Expected a minimum of one and a maximum two command-line",
			"the cache file name and the optional record count");
		return_code = DCR_BAD_ARGS_FAILURE;
	}
	else if ((argc == 3) && ((target_record_count = atoi(argv[2])) < 1)) {
		sprintf(error_text, "Invalid record count parameter ('%-.500s').",
			argv[2]);
		return_code = DCR_BAD_ARGS_FAILURE;
	}
	else if ((return_code = DCR_AllocCacheControl(&cache_control_data,
		100, error_text)) == DCR_SUCCESS) {
		fprintf(stderr, "Allocated the cache control structure.\n");
		if ((return_code = DCR_OpenRead(&cache_control_data, argv[1],
			50, 10000, 0, 0, &cache_ptr, &cache_index, error_text)) ==
			DCR_SUCCESS) {
			fprintf(stderr, "Opened cache '%s' (%u records, cache size %u).\n",
				argv[1], cache_ptr->record_count, cache_ptr->total_cache_size);
			old_record_count = cache_ptr->record_count;
			old_cache_size   = cache_ptr->total_cache_size;
			while (cache_ptr->record_count < target_record_count) {
				if ((return_code = DCR_Refresh(cache_ptr, NULL, NULL, 0,
					NULL, NULL, error_text)) != DCR_SUCCESS)
					break;
				if ((old_record_count != cache_ptr->record_count) ||
					(old_cache_size != cache_ptr->total_cache_size)) {
					fprintf(stderr,
						"Current record count = %10u (cache size = %10u)\n",
						cache_ptr->record_count, cache_ptr->total_cache_size);
					old_record_count = cache_ptr->record_count;
					old_cache_size   = cache_ptr->total_cache_size;
				}
				sleep(1);
			}
		}
		DCR_CloseAllCaches(&cache_control_data);
	}

	if (return_code != DCR_SUCCESS)
		fprintf(stderr, "ERROR: %s\n", error_text);

	return(return_code);
}
/*	***********************************************************************	*/

