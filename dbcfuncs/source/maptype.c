/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Generalized Support Functions Library Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Maps a DBC basic type to an 'MDDL' structure which
								represents that type in the underlying DBC facility.

	Revision History	:	1993-08-13 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Include necessary header files . . .												*/
/*	***********************************************************************	*/

#include "dbcfunci.h"

/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/* *********************************************************************** */
#ifndef NARGS
int DBC_MapTypeToMDDL(const DBC_CONTEXT *dbc_context_ptr,
	DBC_BASIC_TYPE dbc_basic_type, MDDL *mddl_ptr, char *error_text)
#else
int DBC_MapTypeToMDDL(dbc_context_ptr, dbc_basic_type, mddl_ptr, error_text)
const DBC_CONTEXT *dbc_context_ptr;
DBC_BASIC_TYPE     dbc_basic_type;
MDDL              *mddl_ptr;
char              *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = DBC_CheckFunction(dbc_context_ptr,
		((const void **) &dbc_context_ptr->dbc_funcs.map_type_to_mddl),
		error_text)) == DBC_SUCCESS)
		return_code = (*dbc_context_ptr->dbc_funcs.map_type_to_mddl)
			(dbc_basic_type, mddl_ptr, error_text);

	return(return_code);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

COMPAT_FN_DECL(int main, (void));

int main()
{
	int          return_code = DBC_SUCCESS;
	unsigned int count_1;
	DBC_CONTEXT  dbc_context;
	unsigned int mddl_count;
	MDDL         mddl_list[DBC_BASIC_TYPE_COUNT];
	char         error_text[DBC_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'DBC_MapTypeToMDDL()'\n");
	fprintf(stderr, "---- ------- --- ---------------------\n\n");

	if ((return_code = DBC_Initialize(&dbc_context, NULL, NULL,
		0, NULL, error_text)) == DBC_SUCCESS) {
		mddl_count = 0;
		for (count_1 = 0; count_1 < DBC_BASIC_TYPE_COUNT; count_1++) {
			if (DBC_MapTypeToMDDL(&dbc_context, count_1, mddl_list + mddl_count,
				error_text) == DBC_SUCCESS)
				mddl_count++;
			else
				fprintf(stderr, "DBC basic type %u failed: %s\n",
					count_1, error_text);
		}
		if (mddl_count)
			MDDL_EmitMemberListIdx(mddl_count, mddl_list, NULL, NULL);
		DBC_Close(&dbc_context);
	}

	if (return_code != DBC_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

