/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Basic array non-search delta logic.

	Revision History	:	1992-03-22 --- Creation
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

#include <memory.h>
#include <stdlib.h>

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  MEM_ARRAY_delta

   SYNOPSIS    :  return_code = MEM_ARRAY_delta(control_ptr, in_count_1,
							in_list_1, in_count_2, in_list_2, uniq_count_1,
							uniq_list_1, uniq_count_2, uniq_list_2, diff_count,
							diff_list, same_count, same_list, data_length,
							compare_function);

						int            return_code;

						void          *control_ptr;

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

						int          (*compare_function)(void *, const void *,
											const void *, size_t);

   DESCRIPTION :  Determines the delta between the elements in two arrays
						using a user-supplied comparison function.

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
						comparison function parameter ``compare_function`` returns
						a non-zero value.

						(.) Otherwise, the array element is considered by this
						function to be the ``same``.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``control_ptr`` points to a arbitrary user-defined
						structure which may be used to modify the comparisons
						used to determine the relative equality of the array
						elements. It is passed unexamined to the comparison
						function ``compare_function``. If unnecessary, it may be
						a ''NULL'' pointer.

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
						the arrays ``in_list_1`` and ``in_list_2``.

						(.) ``compare_function`` is a pointer to the function
						which will determine equivalence of the array elements.
						The function to which ``compare_function`` points should
						accept the arguments indicated in the SYNOPSIS and return
						an integral result as follows:

						(..) negative if the first element is less than second.

						(..) positive if the first element is greater than second.

						(..) zero if the elements are equal.

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

   CAVEATS     :  

   SEE ALSO    :  mema_delta
						memai_delta
						MEM_ARRAY_search_delta

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2016 Michael L. Brock

   OUTPUT INDEX:  MEM_ARRAY_delta
						Memory Array Delta Functions:MEM_ARRAY_delta
						STRFUNCS:Memory Array Delta Functions:MEM_ARRAY_delta
						String Functions:See STRFUNCS

   PUBLISH XREF:  MEM_ARRAY_delta

   PUBLISH NAME:	MEM_ARRAY_delta

	ENTRY CLASS	:	Memory Array Delta Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int MEM_ARRAY_delta(void *control_ptr,
	unsigned int in_count_1, const void *in_list_1,
	unsigned int in_count_2, const void *in_list_2,
	unsigned int *uniq_count_1, unsigned int **uniq_list_1,
	unsigned int *uniq_count_2, unsigned int **uniq_list_2,
	unsigned int *diff_count, unsigned int **diff_list,
	unsigned int *same_count, unsigned int **same_list, size_t data_length,
	int (*compare_function)(void *, const void *, const void *, size_t))
#else
int MEM_ARRAY_delta(control_ptr, in_count_1, in_list_1, in_count_2, in_list_2,
	uniq_count_1, uniq_list_1, uniq_count_2, uniq_list_2, diff_count,
	diff_list, same_count, same_list, data_length, compare_function)
void          *control_ptr;
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
int          (*compare_function)();
#endif /* #ifndef NARGS */
{
	int          return_code = STRFUNCS_SUCCESS;
	int          uniq_flag_1;
   int          uniq_flag_2;
	unsigned int count_1;
	unsigned int max_count;

	*uniq_count_1 = 0;
	*uniq_list_1  = NULL;
	*uniq_count_2 = 0;
	*uniq_list_2  = NULL;
	*diff_count   = 0;
	*diff_list    = NULL;
	*same_count   = 0;
	*same_list    = NULL;

	if (in_count_1 || in_count_2) {
		max_count = (in_count_1 >= in_count_2) ? in_count_1 : in_count_2;
		if ((!in_count_1) || (!in_count_2)) {
			if ((*uniq_list_1 = ((unsigned int *) malloc(max_count *
				sizeof(unsigned int)))) == NULL)
				return_code = STRFUNCS_FAILURE;
			else {
				for (count_1 = 0; count_1 < max_count; count_1++)
					(*uniq_list_1)[count_1] = count_1;
				*uniq_count_1 = max_count;
				if (!in_count_1) {
					uniq_count_2 = uniq_count_1;
					uniq_list_2  = uniq_list_1;
					uniq_count_1 = 0;
					uniq_list_1  = NULL;
				}
			}
		}
		else if ((in_count_1 == in_count_2) && (!memcmp(in_list_1, in_list_2,
			in_count_1 * data_length))) {
			if ((*same_list = ((unsigned int *) malloc(in_count_1 *
				sizeof(unsigned int)))) == NULL)
				return_code = STRFUNCS_FAILURE;
			else {
				for (count_1 = 0; count_1 < in_count_1; count_1++)
					(*same_list)[count_1] = count_1;
				*same_count = in_count_1;
			}
		}
		else {
			for (count_1 = 0; count_1 < max_count; count_1++) {
				if (((uniq_flag_1 = ((count_1 >= in_count_2) ? 1 : 0)) != 0) &&
					((return_code = mema_append(uniq_count_1,
					((void **) uniq_list_1), &count_1, sizeof(unsigned int))) !=
					STRFUNCS_SUCCESS))
					break;
				if (((uniq_flag_2 = ((count_1 >= in_count_1) ? 1 : 0)) != 0) &&
					((return_code = mema_append(uniq_count_2,
					((void **) uniq_list_2), &count_1, sizeof(unsigned int))) !=
					STRFUNCS_SUCCESS))
					break;
				if ((!uniq_flag_1) && (!uniq_flag_2)) {
					if ((*compare_function)(control_ptr,
						((char *) in_list_1) + (count_1 * data_length),
						((char *) in_list_2) + (count_1 * data_length),
						data_length)) {
						if ((return_code = mema_append(diff_count,
							((void **) diff_list), &count_1,
							sizeof(unsigned int))) != STRFUNCS_SUCCESS)
							break;
					}
					else if ((return_code = mema_append(same_count,
						((void **) same_list), &count_1,
						sizeof(unsigned int))) != STRFUNCS_SUCCESS)
						break;
				}
			}
		}
		if (return_code != STRFUNCS_SUCCESS) {
			mema_remove_all(uniq_count_1, ((void **) uniq_list_1));
			mema_remove_all(uniq_count_2, ((void **) uniq_list_2));
			mema_remove_all(diff_count, ((void **) diff_list));
			mema_remove_all(same_count, ((void **) same_list));
		}
	}

	return(return_code);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>
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

	fprintf(stderr, "Test of function 'MEM_ARRAY_delta()'\n");
	fprintf(stderr, "---- -- -------- -------------------\n\n");

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
#ifndef NARGS
	else if ((return_code = MEM_ARRAY_delta(NULL, file_count_1, file_list_1,
		file_count_2, file_list_2, &uniq_count_1, &uniq_list_1, &uniq_count_2,
		&uniq_list_2, &diff_count, &diff_list, &same_count, &same_list,
		DATA_LENGTH,
		((int (*)(void *, const void *, const void *, size_t)) STR_strcmp))) !=
		0) {
		fprintf(stderr, "ERROR ON DELTA OCCURRED\n");
		return_code = -1;
	}
#else
	else if ((return_code = MEM_ARRAY_delta(NULL, file_count_1, file_list_1,
		file_count_2, file_list_2, &uniq_count_1, &uniq_list_1, &uniq_count_2,
		&uniq_list_2, &diff_count, &diff_list, &same_count, &same_list,
		DATA_LENGTH, STR_strcmp)) != 0) {
		fprintf(stderr, "ERROR ON DELTA OCCURRED\n");
		return_code = -1;
	}
#endif /* #ifndef NARGS */
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
	char  buffer[DATA_LENGTH * 2];

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

