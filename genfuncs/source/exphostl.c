/* *********************************************************************** */
/* *********************************************************************** */
/*	GENFUNCS General Functions Library Source Module								*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Expands a list of host names to a list of host names
								including any aliases.

	Revision History	:	1993-04-12 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/*    Include necessary header files . . .                                 */
/* *********************************************************************** */
 
#include <mbcompat.h>

#include <stdio.h>
#include <string.h>

#ifndef __MSDOS__
# ifndef _Windows
#  include <netdb.h>
#  include <sys/types.h>
#  include <sys/socket.h>
# endif /* # ifndef _Windows */
#endif /* #ifndef __MSDOS__ */ 

#include <strfuncs.h>

#include "genfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_ExpandHostNameList

   SYNOPSIS    :  return_code = GEN_ExpandHostNameList(in_host_count,
							in_host_list, out_host_count, out_host_list, error_text);

						unsigned int    in_host_count;

						char          **in_host_list;

						unsigned int   *out_host_count;

						char         ***out_host_list;

						char           *error_text;

   DESCRIPTION :  Expands the list of ``in_host_count`` host names listed in
						the array ``in_host_list`` to ``out_host_count`` host names
						and aliases in the array ``out_host_list``. Alises for
						the host names are procured by way of a call to the
						function ``gethostbyname``.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_host_count`` is the number of number of host names
						listed in the array ``in_host_list``.

						(.) ``in_host_list`` is a pointer to an array of char which
						contains the host names.

						(.) ``out_host_count`` is a pointer to an unsigned int into
						which will be placed the number of host names (and aliases)
						allocated by the function.

						(.) ``out_host_list`` is a pointer to a pointer to an array
						of char which will be allocated to store the host names and
						aliases resulting from the operation of the function.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if the function completes without
						error. ''GENFUNCS_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero GENFUNCS return codes
						indicative of error as follows:

						(..) ''GENFUNCS_SYSTEM_FAILURE'' indicates that a standard
						library 	function or a system call failed.

						(..) ''GENFUNCS_MEMORY_FAILURE'' indicates that the memory
						required for operation of the function could not be
						allocated.

   NOTES       :  The array ``out_host_list`` is in sorted order and contains
						no duplicates.

						The use of the term ``aliases`` in this description includes
						the primary host name as listed in ''/etc/hosts''.

   CAVEATS     :  

   SEE ALSO    :  GEN_ExpandHostNameString

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2014 Michael L. Brock

	OUTPUT INDEX:	GEN_ExpandHostNameList
						Host Name Functions:GEN_ExpandHostNameList
						GENFUNCS:Functions:GEN_ExpandHostNameList
						GENFUNCS:Host Name Functions:GEN_ExpandHostNameList
						General Functions:See GENFUNCS

	PUBLISH NAME:	GEN_ExpandHostNameList

	PUBLISH XREF:	GEN_ExpandHostNameList

	ENTRY CLASS	:	Host Name Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int GEN_ExpandHostNameList(unsigned int in_host_count, char **in_host_list,
	unsigned int *out_host_count, char ***out_host_list, char *error_text)
#else
int GEN_ExpandHostNameList(in_host_count, in_host_list, out_host_count,
	out_host_list, error_text)
unsigned int    in_host_count;
char          **in_host_list;
unsigned int   *out_host_count;
char         ***out_host_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int              return_code = GENFUNCS_SUCCESS;
#ifndef __MSDOS__
	unsigned int     count_1;
	struct hostent  *host_ptr;
	char           **this_ptr;
#endif /* #ifndef __MSDOS__ */

	if (strl_copy(in_host_count, in_host_list, out_host_count,
		out_host_list) != STRFUNCS_SUCCESS) {
		strcpy(error_text, "Unable to copy the host name list.");
		return_code = GENFUNCS_MEMORY_FAILURE;
	}
#ifndef __MSDOS__
	else {
		for (count_1 = 0; count_1 < in_host_count; count_1++) {
			if ((host_ptr = gethostbyname(in_host_list[count_1])) == NULL) {
				sprintf(error_text, "%s for host '%.300s'.",
					"Unable to get host name data with 'gethostbyname()'",
					in_host_list[count_1]);
				GEN_GetLastErrorString(0, GENFUNCS_MAX_ERROR_TEXT, error_text);
				return_code = GENFUNCS_SYSTEM_FAILURE;
				break;
			}
			this_ptr = host_ptr->h_aliases;
			while (*this_ptr != NULL) {
				if (strl_append(out_host_count, out_host_list, *this_ptr) !=
					STRFUNCS_SUCCESS) {
					sprintf(error_text, "%s '%.300s' to the host name list.",
						"Unable to add the host name alias", *this_ptr);
					return_code = GENFUNCS_MEMORY_FAILURE;
					break;
				}
				this_ptr++;
			}
			if (return_code != GENFUNCS_SUCCESS)
				break;
		}
		if (return_code != GENFUNCS_SUCCESS)
			strl_remove_all(out_host_count, out_host_list);
	}
#endif /* #ifndef __MSDOS__ */

	if (return_code == GENFUNCS_SUCCESS) {
		strl_sort(*out_host_count, *out_host_list);
		strl_uniq(out_host_count, out_host_list);
	}

	return(return_code);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

COMPAT_FN_DECL(int main, (int, char **));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int            return_code = GENFUNCS_FAILURE;
	unsigned int   count_1;
	unsigned int   count_2;
	unsigned int   host_count  = 0;
	char         **host_list   = NULL;
	char           error_text[GENFUNCS_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'GEN_ExpandHostNameList()'\n");
	fprintf(stderr, "---- ------- --- --------------------------\n\n");

	if (argc == 1)
		fprintf(stderr, "USAGE: %s <host-name> [<host-name> . . .]\n", argv[0]);
	else {
		for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
			printf("HOSTNAME: %s ---> ", argv[count_1]);
			if ((return_code = GEN_ExpandHostNameList(1, argv + count_1,
				&host_count, &host_list, error_text)) != GENFUNCS_SUCCESS) {
				fprintf(stderr, "Error on call to '%s': %s\n",
					"GEN_ExpandHostNameList()", error_text);
				break;
			}
			printf("%u aliases\n>>> ", host_count);
			for (count_2 = 0; count_2 < host_count; count_2++)
				printf("%s%s", host_list[count_2],
					(count_2 < (host_count - 1)) ? "," : "\n");
			printf("-----------------------------------------------------\n");
			strl_remove_all(&host_count, &host_list);
		}
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

