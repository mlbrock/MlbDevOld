/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Array non-search delta logic.

	Revision History	:	1992-03-17 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Include necessary header files . . .											*/
/* *********************************************************************** */

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  mema_delta

   SYNOPSIS    :  return_code = mema_delta(in_count_1, in_list_1, in_count_2,
							in_list_2, uniq_count_1, uniq_list_1, uniq_count_2,
							uniq_list_2, diff_count, diff_list, same_count,
							same_list, data_length);

						int            return_code;

						unsigned int   in_count_1;

						const void    *in_list_1;

						unsigned int   in_count_2;

						const void    *in_list_2;

						unsigned int  *uniq_count_1;

						unsigned int **uniq_list_1;

						unsigned int  *uniq_count_2;

						unsigned int **uniq_list_2;

						unsigned int  *diff_count;

						unsigned int **diff_list;

						unsigned int  *same_count;

						unsigned int **same_list;

						size_t         data_length;

   DESCRIPTION :  Determines the delta between the elements in two arrays
						using ``MEM_memcmp``.

						On return, the delta is represented by the contents of four
						arrays allocated and populated by this function:
						``uniq_list_1``, ``uniq_list_2``, ``diff_list``, and
						``same_list``.

						(.) An array element is considered ``uniq``ue if there is no
						corresponding element in the other array. That is to say,
						if one of the two arrays passed to this function has more
						elements than the other, the excess elements are considered
						by this function to be unique.

						(.) An array element is considered ``diff``erent if the
						comparison function ``MEM_memcmp`` returns a non-zero value.

						(.) Otherwise, the array element is considered by this
						function to be the ``same``.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_count_1`` is the number of elements in the array
						``in_list_1``.

						(.) ``in_list_1`` is the first array to be compared.

						(.) ``in_count_2`` is the number of elements in the array
						``in_list_2``.

						(.) ``in_list_2`` is the second array to be compared.

						(.) ``uniq_count_1`` points to an an ''unsigned int'' into
						which this function will place the number of elements in
						the array ``uniq_list_1``.

						(.) ``uniq_list_1`` points to a pointer to ''unsigned int''
						into which this function will place a pointer to an array
						which contains the array indices in ``in_list_1`` which
						were not found in ``in_list_2``.

						(.) ``uniq_count_2`` points to an an ''unsigned int'' into
						which this function will place the number of elements in
						the array ``uniq_list_2``.

						(.) ``uniq_list_2`` points to a pointer to ''unsigned int''
						into which this function will place a pointer to an array
						which contains the array indices in ``in_list_2`` which
						were not found in ``in_list_1``.

						(.) ``diff_count`` points to an an ''unsigned int'' into
						which this function will place the number of elements in
						the array ``diff_list``.

						(.) ``diff_list`` points to a pointer to ''unsigned int''
						into which this function will place a pointer to an array
						which contains the array indices of those elements in
						``in_list_1`` and ``in_list_2`` which the comparison
						function indicated were not identical.

						(.) ``same_count`` points to an an ''unsigned int'' into
						which this function will place the number of elements in
						the array ``same_list``.

						(.) ``same_list`` points to a pointer to ''unsigned int''
						into which this function will place a pointer to an array
						which contains the array indices of those elements in
						``in_list_1`` and ``in_list_2`` which the comparison
						function indicated were identical.

						(.) ``data_length`` is the length of the array elements in
						the array ``in_list_1`` and ``in_list_2``.

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_SUCCESS'' if no error occurred.

						(.) One of the non-zero STRFUNCS return codes if an error
						occurred.

   NOTES       :  This function may allocate memory for ``uniq_list_1``,
						``uniq_list_2``, ``diff_list``, and ``same_list``. It is
						the responsibility of the application programmer to test
						the pointers to see if they are ''NULL'' and, if they are
						not, to free the allocated memory by way of a call to the
						standard library function ``free()``.

						To compare arrays of structures, you should probably use
						the function ``MEM_ARRAY_delta``.

   CAVEATS     :  

   SEE ALSO    :  memai_delta
						MEM_ARRAY_delta
						mema_search_delta

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2016 Michael L. Brock

   OUTPUT INDEX:  mema_delta
						Memory Array Delta Functions:mema_delta
						STRFUNCS:Memory Array Delta Functions:mema_delta
						String Functions:See STRFUNCS

   PUBLISH XREF:  mema_delta

   PUBLISH NAME:	mema_delta

	ENTRY CLASS	:	Memory Array Delta Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int mema_delta(unsigned int in_count_1, const void *in_list_1,
	unsigned int in_count_2, const void *in_list_2,
	unsigned int *uniq_count_1, unsigned int **uniq_list_1,
	unsigned int *uniq_count_2, unsigned int **uniq_list_2,
	unsigned int *diff_count, unsigned int **diff_list,
	unsigned int *same_count, unsigned int **same_list, size_t data_length)
#else
int mema_delta(in_count_1, in_list_1, in_count_2, in_list_2, uniq_count_1,
	uniq_list_1, uniq_count_2, uniq_list_2, diff_count, diff_list, same_count,
	same_list, data_length)
unsigned int   in_count_1;
const void    *in_list_1;
unsigned int   in_count_2;
const void    *in_list_2;
unsigned int  *uniq_count_1;
unsigned int **uniq_list_1;
unsigned int  *uniq_count_2;
unsigned int **uniq_list_2;
unsigned int  *diff_count;
unsigned int **diff_list;
unsigned int  *same_count;
unsigned int **same_list;
size_t         data_length;
#endif /* #ifndef NARGS */
{
	return(MEM_ARRAY_delta(NULL, in_count_1, in_list_1, in_count_2, in_list_2,
		uniq_count_1, uniq_list_1, uniq_count_2, uniq_list_2, diff_count,
		diff_list, same_count, same_list, data_length, MEM_memcmp));
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_LENGTH	80

COMPAT_FN_DECL(int main, (int argc, char **argv));
COMPAT_FN_DECL_STATIC(int  GetFileList,
	(char *, unsigned int *, void **, char*));
COMPAT_FN_DECL_STATIC(void DoUsage,
	(char *, char *, int));

/* *********************************************************************** */
/* *********************************************************************** */
/* *********************************************************************** */
#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int           return_code  = 0;
	unsigned int  file_count_1 = 0;
	void         *file_list_1  = NULL;
	unsigned int  file_count_2 = 0;
	void         *file_list_2  = NULL;
	unsigned int  uniq_count_1 = 0;
	unsigned int *uniq_list_1  = NULL;
	unsigned int  uniq_count_2 = 0;
	unsigned int *uniq_list_2  = NULL;
	unsigned int  diff_count   = 0;
	unsigned int *diff_list    = NULL;
	unsigned int  same_count   = 0;
	unsigned int *same_list    = NULL;
	unsigned int  count_1;
	char          error_text[2048];

	fprintf(stderr, "Test of function 'mema_delta()'\n");
	fprintf(stderr, "---- -- -------- --------------\n\n");

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if ((!STRFUNCS_stricmp("-HELP", argv[count_1])) ||
			(!STRFUNCS_stricmp("-H", argv[count_1])))
			DoUsage(argv[0], "Help request noted.", 0);
	}

	if (argc != 3)
		DoUsage(argv[0], "Invalid command-line encountered.", -1);

	if ((return_code = GetFileList(argv[1], &file_count_1, &file_list_1,
		error_text)) != 0)
		fprintf(stderr, "ERROR READING FILE NUMBER 1: %s\n", error_text);
	else if ((return_code = GetFileList(argv[2], &file_count_2, &file_list_2,
		error_text)) != 0)
		fprintf(stderr, "ERROR READING FILE NUMBER 2: %s\n", error_text);
	else if ((return_code = mema_delta(file_count_1, file_list_1, file_count_2,
		file_list_2, &uniq_count_1, &uniq_list_1, &uniq_count_2, &uniq_list_2,
		&diff_count, &diff_list, &same_count, &same_list, DATA_LENGTH)) !=
		STRFUNCS_SUCCESS) {
		fprintf(stderr, "ERROR ON DELTA OCCURRED\n");
		return_code = -1;
	}
	else {
		printf("Unique to file '%s' --- %u elements:\n", argv[1],
			uniq_count_1);
		for (count_1 = 0; count_1 < uniq_count_1; count_1++)
			printf("[%05u][%05u][%s]\n", count_1, uniq_list_1[count_1],
				((char *) file_list_1) + (uniq_list_1[count_1] * DATA_LENGTH));
		printf("-----------------------------------------------------------\n");
		printf("Unique to file '%s' --- %u elements:\n", argv[2],
			uniq_count_2);
		for (count_1 = 0; count_1 < uniq_count_2; count_1++)
			printf("[%05u][%05u][%s]\n", count_1, uniq_list_2[count_1],
				((char *) file_list_2) + (uniq_list_2[count_1] * DATA_LENGTH));
		printf("-----------------------------------------------------------\n");
		printf("Different lines in files '%s' and '%s' --- %u elements:\n",
			argv[1], argv[2], diff_count);
		for (count_1 = 0; count_1 < diff_count; count_1++) {
			printf("[%05u][%05u][%s]\n", count_1, diff_list[count_1],
				((char *) file_list_1) + (diff_list[count_1] * DATA_LENGTH));
			printf("       [%05u][%s]\n", diff_list[count_1],
				((char *) file_list_2) + (diff_list[count_1] * DATA_LENGTH));
		}
		printf("-----------------------------------------------------------\n");
		printf("Same lines in files '%s' and '%s' --- %u elements:\n",
			argv[1], argv[2], same_count);
		for (count_1 = 0; count_1 < same_count; count_1++) {
			printf("[%05u][%05u][%s]\n", count_1, same_list[count_1],
				((char *) file_list_1) + (same_list[count_1] * DATA_LENGTH));
			printf("       [%05u][%s]\n", same_list[count_1],
				((char *) file_list_2) + (same_list[count_1] * DATA_LENGTH));
		}
		printf("-----------------------------------------------------------\n");
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
static int GetFileList(char *file_name, unsigned int *file_count,
	void **file_list, char *error_text)
#else
static int GetFileList(file_name, file_count, file_list, error_text)
char          *file_name;
unsigned int  *file_count;
void         **file_list;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int   return_code = 0;
	FILE *file_ptr = NULL;
	char  buffer[1024];

	*file_count = 0;
	*file_list  = NULL;

	if ((file_ptr = fopen(file_name, "r")) == NULL) {
		sprintf(error_text, "Unable to open '%s' for reading.", file_name);
		return_code = -1;
	}
	else {
		while ((!feof(file_ptr)) && (!ferror(file_ptr))) {
			*buffer = '\0';
			while (!(*buffer)) {
				memset(buffer, '\0', sizeof(buffer));
				if (fgets(buffer, sizeof(buffer) - 1, file_ptr) == NULL)
					break;
				while (strlen(buffer) && (buffer[strlen(buffer) - 1] == '\n'))
					buffer[strlen(buffer) - 1] = '\0';
			}
			if ((return_code = mema_append(file_count, file_list, buffer,
				DATA_LENGTH)) != STRFUNCS_SUCCESS) {
				sprintf(error_text, "%s %u from the file '%s',",
					"Unable to append line number", *file_count, file_name);
				break;
			}
		}
		fclose(file_ptr);
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
static void DoUsage(char *prog, char *exit_text, int exit_code)
#else
static void DoUsage(prog, exit_text, exit_code)
char *prog;
char *exit_text;
int   exit_code;
#endif /* #ifndef NARGS */
{
	prog = (strrchr(prog, '/'))  ? (strrchr(prog, '/') + 1)  : prog;
	prog = (strrchr(prog, '\\')) ? (strrchr(prog, '\\') + 1) : prog;

	if (*exit_text)
		fprintf(stderr, "%s\n\n", exit_text);

	fprintf(stderr, "USAGE: %s <file-name> <file-name>\n", prog);

	exit(exit_code);
}
/* *********************************************************************** */

#endif /* #ifdef TEST_MAIN */

