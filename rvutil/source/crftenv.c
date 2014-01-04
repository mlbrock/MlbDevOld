/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Creates a fault tolerance environment from
								parameters.

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

#include <memory.h>
#include <string.h>

#include "rvutili.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_CreateFTEnv(const char *service, const char *network,
	const char *daemon, const char *subject_name, rv_Callback call_back,
	const char *group_name, unsigned long weight, unsigned long active_goal,
	unsigned long heart_beat_interval, unsigned long preparation_interval,
	unsigned long activation_interval, rvft_Callback ft_call_back,
	RVUTIL_FT_ENV *ft_env_ptr, char *error_text)
{
	int return_code = RVUTIL_BAD_ARGS_FAILURE;

	RVUTIL_InitFTEnv(ft_env_ptr);

	if (strlen(group_name) >= sizeof(ft_env_ptr->group_name))
		sprintf(error_text,
			"The length of the '%s' parameter (%u) exceeds the maximum (%u).",
			"fault tolerance group_name", strlen(group_name),
			sizeof(ft_env_ptr->group_name) - 1);
	else if (ft_call_back == NULL)
		strcpy(error_text,
			"The fault tolerance call-back function pointer is 'NULL'.");
	else if ((return_code = RVUTIL_CreateEnv(service, network, daemon,
		subject_name, call_back, &ft_env_ptr->env, error_text)) ==
		RVUTIL_SUCCESS) {
		strcpy(ft_env_ptr->group_name, group_name);
		ft_env_ptr->weight               = weight;
		ft_env_ptr->active_goal          = active_goal;
		ft_env_ptr->heart_beat_interval  = heart_beat_interval;
		ft_env_ptr->preparation_interval = preparation_interval;
		ft_env_ptr->activation_interval  = activation_interval;
		ft_env_ptr->call_back_function   = ft_call_back;
		if ((return_code = RVUTIL_CheckFTEnv(ft_env_ptr, error_text)) !=
			RVUTIL_SUCCESS)
			RVUTIL_FreeFTEnv(ft_env_ptr);
	}

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <stdlib.h>

#include <strfuncs.h>

#define TEST_ENV_COUNT				((unsigned int) 10000)

#define TEST_ENV_SERVICE			"env-service"
#define TEST_ENV_NETWORK			"env-network"
#define TEST_ENV_DAEMON				"env-daemon"
#define TEST_ENV_SUBJECT			"TEST.FTENV.SUBJECT.NAME"

COMPAT_FN_DECL(int main, (void));

int main()
{
	int              return_code = RVUTIL_SUCCESS;
	unsigned int     count_1;
	unsigned int     ft_env_count = 0;
	RVUTIL_FT_ENV   *ft_env_list  = NULL;
	char             error_text[RVUTIL_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'RVUTIL_CreateFTEnv()'\n");
	fprintf(stderr, "---- ------- --- ----------------------\n\n");

	fprintf(stderr, "Allocating memory for %u fault tolerance environments",
		TEST_ENV_COUNT);
	if ((ft_env_list = ((RVUTIL_FT_ENV *) calloc(TEST_ENV_COUNT,
		sizeof(RVUTIL_FT_ENV)))) == NULL) {
		STR_AllocMsgList(TEST_ENV_COUNT, sizeof(RVUTIL_FT_ENV), error_text,
			"Unable to allocate the list of fault tolerance environments");
		fprintf(stderr, "\n\nERROR: %s\n", error_text);
		return_code = RVUTIL_MEMORY_FAILURE;
	}
	else {
		fprintf(stderr, "\n");
		fprintf(stderr, "Creating %u fault tolerance environments",
			TEST_ENV_COUNT);
		for (count_1 = 0; count_1 < TEST_ENV_COUNT; count_1++) {
			if ((return_code = RVUTIL_CreateFTEnv(TEST_ENV_SERVICE,
				TEST_ENV_NETWORK, TEST_ENV_DAEMON, NULL, NULL,
				"TEST.FTENV.GROUP.NAME", 10L, 1L, 10000L, 0L, 15000L,
				((rvft_Callback) 0x12345678), ft_env_list + count_1,
				error_text)) != RVUTIL_SUCCESS) {
				fprintf(stderr, "\n\nERROR: %s %u of %u: %s\n",
					"Unable to create fault tolerance environment number",
					count_1 + 1, TEST_ENV_COUNT, error_text);
				break;
			}
			ft_env_count++;
		}
		fprintf(stderr, "\n");
		fprintf(stderr, "Freeing memory for %u fault tolerance environments",
			TEST_ENV_COUNT);
		for (count_1 = 0; count_1 < ft_env_count; count_1++)
			RVUTIL_CloseFTEnv(ft_env_list + count_1, RVUTIL_FALSE);
		free(ft_env_list);
		fprintf(stderr, "\n\n");
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

