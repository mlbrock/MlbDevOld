/* *********************************************************************** */
/* *********************************************************************** */
/*	GENFUNCS General Functions Library Source Module								*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Sets the operating system resource limits to their
								maximum possible values.

	Revision History	:	1994-12-04 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include <strfuncs.h>

#include "genfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Structure used internal to this function . . .								*/
/*	***********************************************************************	*/
typedef struct {
	char *name;
	int   selector;
} GEN_RLIMIT_DEF;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		We map names to the resource limits here . . .								*/
/*	***********************************************************************	*/
#ifdef __MSDOS__
#elif _Windows
#elif __SVR4
#include <sys/resource.h>
static const GEN_RLIMIT_DEF GEN_RLimitsList[RLIM_NLIMITS] = {
	{	"maximum core file size", 			RLIMIT_CORE		},
	{	"maximum cpu milliseconds",		RLIMIT_CPU		},
	{	"maximum data size", 				RLIMIT_DATA		},
	{	"maximum file size", 				RLIMIT_FSIZE	},
	{	"maximum descriptor count", 		RLIMIT_NOFILE	},
	{	"maximum stack size", 				RLIMIT_STACK	},
	{	"maximum mapped address size", 	RLIMIT_VMEM		},
};
#else
#include <sys/resource.h>
static const GEN_RLIMIT_DEF GEN_RLimitsList[RLIM_NLIMITS] = {
	{	"maximum cpu milliseconds",		RLIMIT_CPU		},
	{	"maximum file size", 				RLIMIT_FSIZE	},
	{	"maximum data size", 				RLIMIT_DATA		},
	{	"maximum stack size", 				RLIMIT_STACK	},
	{	"maximum core file size", 			RLIMIT_CORE		},
	{	"maximum resident set size", 		RLIMIT_RSS		},
	{	"maximum descriptor count", 		RLIMIT_NOFILE	}
};
#endif /* #ifdef __MSDOS__ */
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_SetResourceLimitsToMax

   SYNOPSIS    :	return_code = GEN_SetResourceLimitsToMax(error_text);

						int   return_code;

						char *error_text;

   DESCRIPTION :	Sets all operating system resource limits to their maximum
						possible values.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if the function completes without
						error. ''GENFUNCS_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero GENFUNCS return codes
						indicative of error.

   NOTES       :	Of course, this function does nothing whatsoever when
						executed under operating systems other than Unix.

   CAVEATS     :	

   SEE ALSO    :	

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1994 - 2014 Michael L. Brock

   OUTPUT INDEX:	GEN_SetResourceLimitsToMax
						Miscellaneous Functions:GEN_SetResourceLimitsToMax
						GENFUNCS:Functions:GEN_SetResourceLimitsToMax
						GENFUNCS:Miscellaneous Functions:GEN_SetResourceLimitsToMax
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_SetResourceLimitsToMax

   PUBLISH NAME:	GEN_SetResourceLimitsToMax

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_SetResourceLimitsToMax(char *error_text)
#else
int GEN_SetResourceLimitsToMax(error_text)
char *error_text;
#endif /* #ifndef NARGS */
{
#ifdef __MSDOS__
	int return_code = GENFUNCS_SUCCESS;

	if (error_text != NULL)
		*error_text = '\0';
#elif _Windows
	int return_code = GENFUNCS_SUCCESS;

	if (error_text != NULL)
		*error_text = '\0';
#else

	int           return_code = GENFUNCS_SUCCESS;
	unsigned int  count_1;
	struct rlimit rlimit_data;

	for (count_1 = 0; count_1 < RLIM_NLIMITS; count_1++) {
		if (getrlimit(GEN_RLimitsList[count_1].selector, &rlimit_data)) {
			sprintf(error_text, "%s %d ('%s') failed: ",
				"Attempt to get the operating system resource limit number",
				GEN_RLimitsList[count_1].selector, GEN_RLimitsList[count_1].name);
			GEN_AppendLastErrorString(0, GENFUNCS_MAX_ERROR_TEXT, error_text);
			return_code = GENFUNCS_SYSTEM_FAILURE;
			break;
		}
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		First try to set the 'soft' resource limit to its 'hard'	*/
		/*	(or maximum) value . . .												*/
		/*	***********************************************************	*/
		rlimit_data.rlim_cur = rlimit_data.rlim_max;
		if (setrlimit(GEN_RLimitsList[count_1].selector, &rlimit_data)) {
			sprintf(error_text, "%s %d ('%s') %s ('%u') %s ('%u') failed: ",
				"Attempt to change the operating system resource limit number",
				GEN_RLimitsList[count_1].selector, GEN_RLimitsList[count_1].name,
				"from its 'soft' limit", ((unsigned int) rlimit_data.rlim_cur),
				"to its 'hard' limit", ((unsigned int) rlimit_data.rlim_max));
			GEN_AppendLastErrorString(0, GENFUNCS_MAX_ERROR_TEXT, error_text);
			return_code = GENFUNCS_SYSTEM_FAILURE;
			break;
		}
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		Now try to set both the 'soft' and 'hard' limits to their*/
		/*	maximum values --- just in case the process is executing		*/
		/*	with 'root' privilege.													*/
		/*																					*/
		/*		If the process isn't running as 'root', we ignore the		*/
		/*	return status from 'setrlimit()', so no harm is done.			*/
		/*	***********************************************************	*/
		rlimit_data.rlim_cur = RLIM_INFINITY;
		rlimit_data.rlim_max = RLIM_INFINITY;
		setrlimit(GEN_RLimitsList[count_1].selector, &rlimit_data);
		/*	***********************************************************	*/
	}
#endif /* #ifdef __MSDOS__ */

	return(return_code);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

COMPAT_FN_DECL(int main, (void));

int main()
{
	int  return_code;
	char error_text[GENFUNCS_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'GEN_SetResourceLimitsToMax()'\n");
	fprintf(stderr, "---- ------- --- ------------------------------\n\n");

	if ((return_code = GEN_SetResourceLimitsToMax(error_text)) !=
		GENFUNCS_SUCCESS)
		fprintf(stderr, "ERROR: %s\n", error_text);
	else
		fprintf(stderr, "Resource limits set to maximum values.\n");

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

