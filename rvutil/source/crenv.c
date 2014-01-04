/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Creates an environment from parameters.

	Revision History	:	1996-01-12 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <string.h>

#include <strfuncs.h>

#include "rvutili.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_CreateEnv(const char *service, const char *network,
	const char *daemon, const char *subject_name, rv_Callback call_back,
	RVUTIL_ENV *env_ptr, char *error_text)
{
	int return_code = RVUTIL_BAD_ARGS_FAILURE;

	RVUTIL_InitEnv(env_ptr);

	service      = (service != NULL) ? service : "";
	network      = (network != NULL) ? network : "";
	daemon       = (daemon  != NULL) ? daemon  : "";
	subject_name = ((subject_name != NULL) && *subject_name) ? subject_name :
		NULL;

	if (strlen(service) >= sizeof(env_ptr->service))
		sprintf(error_text,
			"The length of the '%s' parameter (%u) exceeds the maximum (%u).",
			"service", strlen(service), sizeof(env_ptr->service) - 1);
	else if (strlen(network) >= sizeof(env_ptr->network))
		sprintf(error_text,
			"The length of the '%s' parameter (%u) exceeds the maximum (%u).",
			"network", strlen(network), sizeof(env_ptr->network) - 1);
	else if (strlen(daemon) >= sizeof(env_ptr->daemon))
		sprintf(error_text,
			"The length of the '%s' parameter (%u) exceeds the maximum (%u).",
			"daemon", strlen(daemon), sizeof(env_ptr->daemon) - 1);
	else if ((subject_name != NULL) &&
		(strlen(subject_name) >= STR_sizeof(RVUTIL_SUB, subject_name)))
		sprintf(error_text,
			"The length of the '%s' parameter (%u) exceeds the maximum (%u).",
			"subject_name", strlen(subject_name),
			STR_sizeof(RVUTIL_SUB, subject_name) - 1);
	else if ((subject_name != NULL) && (call_back == NULL))
		strcpy(error_text,
			"Subject name is specified, but call-back function is 'NULL'.");
	else {
		strcpy(env_ptr->service, service);
		strcpy(env_ptr->network, network);
		strcpy(env_ptr->daemon,  daemon);
		if ((return_code = RVUTIL_CheckEnv(env_ptr, error_text)) ==
			RVUTIL_SUCCESS) {
			if ((subject_name != NULL) && (call_back != NULL) &&
				((return_code = RVUTIL_AddSub(env_ptr, subject_name, call_back,
				NULL, error_text)) != RVUTIL_SUCCESS))
				RVUTIL_FreeEnv(env_ptr);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <stdlib.h>

#define TEST_ENV_COUNT				((unsigned int) 10000)

#define TEST_ENV_SERVICE			"env-service"
#define TEST_ENV_NETWORK			"env-network"
#define TEST_ENV_DAEMON				"env-daemon"
#define TEST_ENV_SUBJECT			"TEST.ENV.SUBJECT.NAME"

COMPAT_FN_DECL(int main, (void));

int main()
{
	int           return_code = RVUTIL_SUCCESS;
	unsigned int  count_1;
	unsigned int  env_count = 0;
	RVUTIL_ENV   *env_list  = NULL;
	char          error_text[RVUTIL_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'RVUTIL_CreateEnv()'\n");
	fprintf(stderr, "---- ------- --- --------------------\n\n");

	fprintf(stderr, "Allocating memory for %u environments",
		TEST_ENV_COUNT);
	if ((env_list = ((RVUTIL_ENV *) calloc(TEST_ENV_COUNT,
		sizeof(RVUTIL_ENV)))) == NULL) {
		STR_AllocMsgList(TEST_ENV_COUNT, sizeof(RVUTIL_ENV), error_text,
			"Unable to allocate the list of environments");
		fprintf(stderr, "\n\nERROR: %s\n", error_text);
		return_code = RVUTIL_MEMORY_FAILURE;
	}
	else {
		fprintf(stderr, "\n");
		fprintf(stderr, "Creating %u environments", TEST_ENV_COUNT);
		for (count_1 = 0; count_1 < TEST_ENV_COUNT; count_1++) {
			if ((return_code = RVUTIL_CreateEnv(TEST_ENV_SERVICE,
				TEST_ENV_NETWORK, TEST_ENV_DAEMON, TEST_ENV_SUBJECT,
				((rv_Callback) 0x12345678), env_list + count_1, error_text)) !=
				RVUTIL_SUCCESS) {
				fprintf(stderr, "\n\nERROR: %s %u of %u: %s\n",
					"Unable to create environment number", count_1 + 1,
					TEST_ENV_COUNT, error_text);
				break;
			}
			env_count++;
		}
		fprintf(stderr, "\n");
		fprintf(stderr, "Freeing memory for %u environments",
			TEST_ENV_COUNT);
		for (count_1 = 0; count_1 < env_count; count_1++)
			RVUTIL_CloseEnv(env_list + count_1, RVUTIL_FALSE);
		free(env_list);
		fprintf(stderr, "\n\n");
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

