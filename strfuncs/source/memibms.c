/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	STRFUNCS String and Memory Functions Library Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Implements case-insensitive Boyer-Moore string
								searching.

	Revision History	:	1995-08-27 --- Creation.
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

#include <limits.h>
#include <memory.h>
#include <stdlib.h>

#include "strfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	BoyerMoore_memi_init_jump

	SYNOPSIS		:	jump_array_ptr = BoyerMoore_memi_init_jump(target_length,
							target_area, jump_array);

						unsigned int *jump_array_ptr;

						unsigned int  target_length;

						const void   *target_area;

						unsigned int *jump_array;

	DESCRIPTION	:	Initializes a case-insensitive character jump table to the
						state necessary for subsequent use by the first heuristic of
						the Boyer-Moore string searching algorithm.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``target_length`` is the length of the memory area to
						which the ``target_area`` pointer points.

						(.) ``target_area`` points to the memory area for which the
						subsequent search will be performed.

						(.) ``jump_array`` points to an array of ``unsigned int``
						into which the case-insensitive Boyer-Moore jump data
						calculated by this function will be placed.

						(-) ``jump_array`` must be have an element for each
						character representable on the target architecture. It can
						be statically allocated with:

						(--) unsigned int jump_array[UCHAR_MAX + 1];

	RETURNS		:	A pointer to the calculated case-insensitive Boyer-Moore
						jump array (that is, the ``jump_array`` parameter is
						returned).

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	BoyerMoore_mem_init_jump
						BoyerMoore_memi_init_match

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2015 Michael L. Brock

	OUTPUT INDEX:	BoyerMoore_memi_init_jump
						String Functions:BoyerMoore_memi_init_jump
						String Search Functions:BoyerMoore_memi_init_jump
						Boyer-Moore String Search Functions:BoyerMoore_memi_init_jump

	PUBLISH XREF:	BoyerMoore_mem_initi_jump

	PUBLISH NAME:	BoyerMoore_mem_initi_jump

	ENTRY CLASS	:	Boyer-Moore String Search Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
unsigned int *BoyerMoore_memi_init_jump(unsigned int target_length,
	const void *target_area, unsigned int *jump_array)
#else
unsigned int *BoyerMoore_memi_init_jump(target_length, target_area,
	jump_array)
unsigned int  target_length;
const void   *target_area;
unsigned int *jump_array;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;

	for (count_1 = 0; count_1 < (UCHAR_MAX + 1); count_1++)
		jump_array[count_1] = target_length;

	for (count_1 = 0; count_1 < target_length; count_1++)
		jump_array[strfmacs_toupper(((const unsigned char *) target_area)
			[count_1])] = (target_length - count_1) - 1;

	return(jump_array);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	BoyerMoore_memi_init_match

	SYNOPSIS		:	match_array_ptr = BoyerMoore_memi_init_match(target_length,
							target_area, match_array);

						unsigned int *match_array_ptr;

						unsigned int  target_length;

						const void   *target_area;

						unsigned int *match_array;

	DESCRIPTION	:	Initializes a case-insensitive character match table to the
						state necessary for subsequent use by the second heuristic
						of the Boyer-Moore string searching algorithm.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``target_length`` is the length of the memory area to
						which the ``target_area`` pointer points.

						(.) ``target_area`` points to the memory area for which the
						subsequent search will be performed.

						(.) ``match_array`` points to an array of ``unsigned int``
						into which the case-insensitive Boyer-Moore match data
						calculated by this function will be placed.

						(-) Before invoking this function, ``match_array`` must
						be allocated to have ``((target_length + 1) * 2) + 1``
						number of elements. The related function
						``BoyerMoore_memi_alloc_match`` will both allocate a memory
						area of the appropriate size and then call this function
						to initialize that area.

	RETURNS		:	A pointer to the calculated case-insensitive Boyer-Moore
						match array (that is, the ``match_array`` parameter is
						returned).

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	BoyerMoore_mem_init_match
						BoyerMoore_memi_alloc_match
						BoyerMoore_memi_init_jump

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2015 Michael L. Brock

	OUTPUT INDEX:	BoyerMoore_memi_init_match
						String Functions:BoyerMoore_memi_init_match
						String Search Functions:BoyerMoore_memi_init_match
						Boyer-Moore String Search Functions:BoyerMoore_memi_init_match

	PUBLISH XREF:	BoyerMoore_memi_init_match

	PUBLISH NAME:	BoyerMoore_memi_init_match

	ENTRY CLASS	:	Boyer-Moore String Search Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
unsigned int *BoyerMoore_memi_init_match(unsigned int target_length,
	const void *target_area, unsigned int *match_array)
#else
unsigned int *BoyerMoore_memi_init_match(target_length, target_area,
	match_array)
unsigned int  target_length;
const void   *target_area;
unsigned int *match_array;
#endif /* #ifndef NARGS */
{
	unsigned int  count_1;
	unsigned int  tmp_index_1;
	unsigned int  tmp_index_2;
	unsigned int *match_ptr;

	if (target_length) {
		memset(match_array, '\0',
			(((target_length + 1) * 2) + 1) * sizeof(unsigned int));
		for (count_1 = 1; count_1 <= target_length; count_1++)
			match_array[count_1] = (target_length * 2) - count_1;
		count_1                        = target_length;
		tmp_index_1                    = target_length + 1;
		match_ptr                      = match_array + target_length + 1;
		match_array[target_length + 1] = 0;
		while (count_1) {
			match_ptr[count_1] = tmp_index_1;
			while ((tmp_index_1 <= target_length) &&
				(strfmacs_toupper(((const unsigned char *) target_area)
				[count_1 - 1]) != strfmacs_toupper(((const unsigned char *)
				target_area)[tmp_index_1 - 1]))) {
				if (match_array[tmp_index_1] > (target_length - count_1))
					match_array[tmp_index_1] = target_length - count_1;
				tmp_index_1 = match_ptr[tmp_index_1];
			}
			count_1--;
			tmp_index_1--;
		}
		for (count_1 = 1; count_1 <= tmp_index_1; count_1++) {
			if (match_array[count_1] > ((target_length + tmp_index_1) - count_1))
				match_array[count_1] = (target_length + tmp_index_1) - count_1;
		}
		tmp_index_2 = match_ptr[tmp_index_1];
		while (tmp_index_1 <= target_length) {
			while (tmp_index_1 <= tmp_index_2) {
				if (match_array[tmp_index_1] >
					((tmp_index_2 - tmp_index_1) + target_length))
					match_array[tmp_index_1] =
						(tmp_index_2 - tmp_index_1) + target_length;
				tmp_index_1++;
			}
			tmp_index_2 = match_ptr[tmp_index_2];
		}
	}

	return(match_array);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	BoyerMoore_memi_alloc_match

	SYNOPSIS		:	match_array_ptr = BoyerMoore_memi_alloc_match(target_length,
							target_area);

						unsigned int *match_array_ptr;

						unsigned int  target_length;

						const void   *target_area;

	DESCRIPTION	:	Allocates and then initializes a case-insensitive character
						match table to the state necessary for subsequent use by
						the second heuristic of the Boyer-Moore string searching
						algorithm.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``target_length`` is the length of the memory area to
						which the ``target_area`` pointer points.

						(.) ``target_area`` points to the memory area for which the
						subsequent search will be performed.

	RETURNS		:	Returns from this function are as follow:

						(.) If the ``target_length`` parameter is greater than zero
						and the required memory allocation succeeds, a pointer to
						the allocated case-insensitive Boyer-Moore match array is
						returned.

						(.) Otherwise, a ''NULL'' pointer is returned.

	NOTES			:	If this function returns a non-''NULL'' pointer, then
						a memory area equal in length to
						``(((target_length + 1) * 2) + 1) * sizeof(unsigned int)``
						has been allocated. It is the responsibility of the
						application programmer to free this memory.

	CAVEATS		:	

	SEE ALSO		:	BoyerMoore_mem_alloc_match
						BoyerMoore_memi_init_match

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2015 Michael L. Brock

	OUTPUT INDEX:	BoyerMoore_memi_alloc_match
						String Functions:BoyerMoore_memi_alloc_match
						String Search Functions:BoyerMoore_memi_alloc_match
						Boyer-Moore String Search Functions:BoyerMoore_memi_alloc_match

	PUBLISH XREF:	BoyerMoore_memi_alloc_match

	PUBLISH NAME:	BoyerMoore_memi_alloc_match

	ENTRY CLASS	:	Boyer-Moore String Search Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
unsigned int *BoyerMoore_memi_alloc_match(unsigned int target_length,
	const void *target_area)
#else
unsigned int *BoyerMoore_memi_alloc_match(target_length, target_area)
unsigned int  target_length;
const void   *target_area;
#endif /* #ifndef NARGS */
{
	unsigned int *match_array;

	return((target_length && ((match_array = ((unsigned int *)
		malloc((((target_length + 1) * 2) + 1) * sizeof(unsigned int)))) !=
		NULL)) ? BoyerMoore_memi_init_match(target_length, target_area,
		match_array) : NULL);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	BoyerMoore_memi_search

	SYNOPSIS		:	found_ptr = BoyerMoore_memi_search(search_length,
							search_area, target_length, target_area);

						void         *found_ptr;

						unsigned int  search_length;

						const void   *search_area;

						unsigned int  target_length;

						const void   *target_area;

	DESCRIPTION	:	Initializes the case-insensitive tables necessary to both
						Boyer-Moore heuristics and uses those tables to locate the
						first occurrence of the memory area to which the
						``target_area`` (ignoring the case of alphabetic characters)
						parameter points in the memory area to which the
						``search_area`` parameter points using the Boyer-Moore
						string searching algorithm.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``search_length`` is the length of the memory area to
						which the ``search_area`` parameter points.

						(.) ``search_area`` points to the memory area within which
						the search will be performed.

						(.) ``target_length`` is the length of the memory area to
						which the ``target_area`` pointer points.

						(.) ``target_area`` points to the memory area for which the
						search will be performed.

	RETURNS		:	Returns from this function are as follow:

						(.) If found, a pointer to the first occurrence of
						``target_area`` in the memory area``search_area``.

						(.) Otherwise, this function returns a ''NULL'' pointer.

	NOTES			:	This function initializes case-insensitive tables for both
						heuristics of the Boyer-Moore string searching algorithm.
						If you intend to perform multiple searchs using the same
						``target_length`` and ``target_area`` parameters, it will
						be much more efficient to initialize those tables once and
						to then use the related function
						``BoyerMoore_memi_search_basic``.

	CAVEATS		:	The behaviour of this function may differ from your
						expectations because it is implemented as a permutation
						of the functionality embodied in the standard C library
						function ``strstr``. Per the ISO C Standard 9899:1990
						(section 7.11.5.7) definition of ``strstr``, if
						``target_length`` is ''0'', a pointer to ``search_area`` is
						returned.

	SEE ALSO		:	BoyerMoore_memi_search_basic
						BoyerMoore_mem_search

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2015 Michael L. Brock

	OUTPUT INDEX:	BoyerMoore_memi_search
						String Functions:BoyerMoore_memi_search
						String Search Functions:BoyerMoore_memi_search
						Boyer-Moore String Search Functions:BoyerMoore_memi_search

	PUBLISH XREF:	BoyerMoore_memi_search

	PUBLISH NAME:	BoyerMoore_memi_search

	ENTRY CLASS	:	Boyer-Moore String Search Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void *BoyerMoore_memi_search(unsigned int search_length,
	const void *search_area, unsigned int target_length,
	const void *target_area)
#else
void *BoyerMoore_memi_search(search_length, search_area, target_length,
	target_area)
unsigned int  search_length;
const void   *search_area;
unsigned int  target_length;
const void   *target_area;
#endif /* #ifndef NARGS */
{
	void         *return_ptr = NULL;
	unsigned int  jump_array[UCHAR_MAX + 1];
	unsigned int *match_array;

	if (!target_length)
		return_ptr = ((void *) search_area);
	else if (search_length) {
		return_ptr = BoyerMoore_memi_search_basic(search_length, search_area,
			target_length, target_area, BoyerMoore_memi_init_jump(target_length,
			target_area, jump_array), match_array =
			BoyerMoore_memi_alloc_match(target_length, target_area));
		if (match_array != NULL)
			free(match_array);
	}

	return(return_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	BoyerMoore_memi_search_basic

	SYNOPSIS		:	found_ptr = BoyerMoore_memi_search_basic(search_length,
							search_area, target_length, target_area);

						void         *found_ptr;

						unsigned int  search_length;

						const void   *search_area;

						unsigned int  target_length;

						const void   *target_area;

						unsigned int *jump_array;

						unsigned int *match_array;

	DESCRIPTION	:	Locates the first occurrence of the memory area to which
						the ``target_area`` parameter points in the memory area to
						which the ``search_area`` parameter points using a
						case-insensitive version of the Boyer-Moore string searching
						algorithm. The tables necessary for use by the two heuristics
						of the algorithm are assumed to have been initialized by the
						invoking function.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``search_length`` is the length of the memory area to
						which the ``search_area`` parameter points.

						(.) ``search_area`` points to the memory area within which
						the search will be performed.

						(.) ``target_length`` is the length of the memory area to
						which the ``target_area`` pointer points.

						(.) ``target_area`` points to the memory area for which the
						search will be performed.

						(.) ``jump_array`` points to an array of ``unsigned int``
						which contains the case-insensitive Boyer-Moore jump data
						calculated by the invoking function.

						(.) ``match_array`` points to an array of ``unsigned int``
						which contains the case-insensitive Boyer-Moore match data
						calculated by the invoking function.

						(-) Alternatively, ``match_array`` may be ''NULL'', in which
						case the second Boyer-Moore heuristic will not be used in
						performing the search.

	RETURNS		:	Returns from this function are as follow:

						(.) If found, a pointer to the first occurrence of
						``target_area`` in the memory area``search_area``.

						(.) Otherwise, this function returns a ''NULL'' pointer.

	NOTES			:	

	CAVEATS		:	The behaviour of this function may differ from your
						expectations because it is implemented as a permutation
						of the functionality embodied in the standard C library
						function ``strstr``. Per the ISO C Standard 9899:1990
						(section 7.11.5.7) definition of ``strstr``, if
						``target_length`` is ''0'', a pointer to ``search_area`` is
						returned.

	SEE ALSO		:	BoyerMoore_memi_search
						BoyerMoore_mem_search_basic
						BoyerMoore_memi_init_jump
						BoyerMoore_memi_init_match
						BoyerMoore_memi_alloc_match

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2015 Michael L. Brock

	OUTPUT INDEX:	BoyerMoore_memi_search_basic
						String Functions:BoyerMoore_memi_search_basic
						String Search Functions:BoyerMoore_memi_search_basic
						Boyer-Moore String Search Functions:BoyerMoore_memi_search_basic

	PUBLISH XREF:	BoyerMoore_memi_search_basic

	PUBLISH NAME:	BoyerMoore_memi_search_basic

	ENTRY CLASS	:	Boyer-Moore String Search Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void *BoyerMoore_memi_search_basic(unsigned int search_length,
	const void *search_area, unsigned int target_length,
	const void *target_area, unsigned int *jump_array,
	unsigned int *match_array)
#else
void *BoyerMoore_memi_search_basic(search_length, search_area, target_length,
	target_area, jump_array, match_array)
unsigned int  search_length;
const void   *search_area;
unsigned int  target_length;
const void   *target_area;
unsigned int *jump_array;
unsigned int *match_array;
#endif /* #ifndef NARGS */
{
	unsigned int  search_index;
	unsigned int  target_index;
	unsigned int  tmp_index_1;
	unsigned int  tmp_index_2;

	search_index = target_length - 1;
	target_index = target_length;

	if (!target_length)
		return(((void *) search_area));
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		You may note that the sections of code in the two parts of the	*/
	/*	'if' differ only by the single line which determines the location	*/
	/*	of the next character to be examined within 'search_area' by		*/
	/*	assignment to 'tmp_index_2'.													*/
	/*																							*/
	/*		The  difference is that if 'match_array' is non-'NULL', then	*/
	/*	it is assumed to be an array properly initialized to the state		*/
	/*	required by the second Boyer-Moore heuristic. Otherwise, only the	*/
	/*	first Boyer-Moore heuristic is used.										*/
	/*																							*/
	/*		We might conceivably implement this code with a trenary 'if'	*/
	/*	statement and reduce code-bloat, but this would result in the 		*/
	/*	'if' expression being re-evaluated at every Boyer-Moore jump		*/
	/*	opportunity.																		*/
	/*																							*/
	/*		My decision at implementation was to accept larger code size	*/
	/*	as a trade-off against speed of operation. After all, one uses		*/
	/*	Boyer-Moore only when speed of operation is of primary concern.	*/
	/*	If it isn't, don't call this function --- use 'stristr()' instead.*/
	/*	*****************************************************************	*/
	else if (match_array != NULL) {
		while ((search_index < search_length) && target_index) {
			if (strfmacs_toupper(((const unsigned char *) search_area)
				[search_index]) == strfmacs_toupper(((const unsigned char *)
				target_area)[target_index - 1])) {
				search_index--;
				target_index--;
			}
			else {
				tmp_index_1   = jump_array
					[strfmacs_toupper(((const unsigned char *) search_area)
					[search_index])];
				tmp_index_2   = match_array[target_index];
				search_index += (tmp_index_1 > tmp_index_2) ? tmp_index_1 :
					tmp_index_2;
				target_index  = target_length;
			}
		}
	}
	else {
		while ((search_index < search_length) && target_index) {
			if (strfmacs_toupper(((const unsigned char *) search_area)
				[search_index]) == strfmacs_toupper(((const unsigned char *)
				target_area)[target_index - 1])) {
				search_index--;
				target_index--;
			}
			else {
				tmp_index_1   = jump_array
					[strfmacs_toupper(((const unsigned char *) search_area)
					[search_index])];
				tmp_index_2   = (target_length - target_index) + 1;
				search_index += (tmp_index_1 > tmp_index_2) ? tmp_index_1 :
					tmp_index_2;
				target_index  = target_length;
			}
		}
	}
	/*	*****************************************************************	*/

	return((target_index) ? NULL :
		(((unsigned char *) search_area) + (search_index + 1)));
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <stdio.h>
#include <string.h>

#include <sdtif.h>

COMPAT_FN_DECL(int main, (int argc, char **argv));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int            return_code        = STRFUNCS_SUCCESS;
	FILE          *file_ptr           = NULL;
	unsigned int   file_buffer_length = 0;
	char          *file_buffer        = NULL;
	unsigned int  *match_array        = NULL;
	unsigned long  total_bytes        = 0;
	unsigned long  total_found_count  = 0L;
	unsigned int   jump_array[UCHAR_MAX + 1];
	unsigned int   count_1;
	unsigned int   search_length;
	char          *search_area;
	unsigned int   target_length;
	char          *target_area;
	char          *tmp_ptr;
	unsigned int   found_count_0;
	unsigned int   found_count_1;
	unsigned int   found_count_2;
	unsigned int   found_count_3;
	unsigned long  check_sum_0;
	unsigned long  check_sum_1;
	unsigned long  check_sum_2;
	unsigned long  check_sum_3;
	struct timeval start_time;
	struct timeval end_time;
	unsigned long  total_time_0 = 0L;
	unsigned long  total_time_1 = 0L;
	unsigned long  total_time_2 = 0L;
	unsigned long  total_time_3 = 0L;
	unsigned long  file_size;
	unsigned long  tmp_file_size;

	fprintf(stderr,
		"Test routine for function 'BoyerMoore_memi_search_basic()'\n");
	fprintf(stderr,
		"---- ------- --- -------- --------------------------------\n\n");

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if ((!stricmp(argv[count_1], "-H")) ||
			(!stricmp(argv[count_1], "-HELP"))) {
			fprintf(stderr, "USAGE:\n   %s %s %s\n", argv[0],
				"<target-string>", "<input-file> [<input-file> . . .]");
			goto EXIT_FUNCTION;
		}
	}

	if (argc < 3) {
		fprintf(stderr, "ERROR: %s\n\nUse '%s -HELP' to get help\n",
			"command-line arguments are required for test.", argv[0]);
		return_code = STRFUNCS_FAILURE;
	}
	else if ((match_array = BoyerMoore_memi_alloc_match(target_length =
		strlen(argv[1]), target_area = argv[1])) == NULL) {
		fprintf(stderr, "ERROR: %s string '%s' (%u bytes required).\n",
			"Unable to allocate the Boyer-Moore match array for the",
			target_area, (target_length + 1) * 2 * sizeof(unsigned int));
		return_code = STRFUNCS_FAILURE;
		goto EXIT_FUNCTION;
	}
	else {
		BoyerMoore_memi_init_jump(target_length, target_area, jump_array);
		fprintf(stderr, "Target search string: [%s]\n", target_area);
		fprintf(stderr, "Search of %d files in progress: [", argc - 2);
		for (count_1 = 2; count_1 < ((unsigned int) argc); count_1++) {
			if ((file_ptr = fopen(argv[count_1], "rb")) == NULL) {
				fprintf(stderr,
					"\n\nERROR: Unable to open input file '%s' for reading.\n",
					argv[count_1]);
				return_code = STRFUNCS_FAILURE;
				goto EXIT_FUNCTION;
			}
			fseek(file_ptr, 0L, SEEK_END);
			file_size = ftell(file_ptr);
			fseek(file_ptr, 0L, SEEK_SET);
			if (!file_size) {
				fclose(file_ptr);
				file_ptr = NULL;
				continue;
			}
			if (file_size > ((unsigned long) (UINT_MAX - 15)))
				file_size = ((unsigned long) (UINT_MAX - 15));
			if (file_buffer_length < ((unsigned int) file_size)) {
				tmp_file_size = (file_size < 60000L) ? 60000L : file_size;
				tmp_ptr       = ((char *) ((!file_buffer_length) ?
					malloc((((unsigned int) tmp_file_size) + 1) * sizeof(char)) :
					realloc(file_buffer, (((unsigned int) tmp_file_size) + 1) *
						sizeof(char))));
				if (tmp_ptr != NULL) {
					file_buffer_length = ((unsigned int) tmp_file_size) + 1;
					file_buffer        = tmp_ptr;
				}
				else {
					fprintf(stderr, "\n\nERROR: %s '%s' (%lu bytes required).\n",
						"Unable to allocate a buffer for file", argv[count_1],
						tmp_file_size + 1L);
					return_code = STRFUNCS_FAILURE;
					goto EXIT_FUNCTION;
				}
			}
			if (fread(file_buffer, sizeof(char), ((unsigned int) file_size),
				file_ptr) != ((unsigned int) file_size)) {
				fprintf(stderr, "\n\nERROR: %s %lu bytes from input file '%s'.\n",
					"Unable to read", file_size, argv[count_1]);
				return_code = STRFUNCS_FAILURE;
				goto EXIT_FUNCTION;
			}
			file_buffer[((unsigned int) file_size)] = '\0';
			search_length = ((unsigned int) file_size);
			search_area   = file_buffer;
			found_count_0 = 0;
			check_sum_0   = 0L;
			SDTIF_GetTimeUSecs(&start_time);
			while ((tmp_ptr = stristr(search_area, target_area)) != NULL) {
				search_area  = tmp_ptr + 1;
				check_sum_0 += ((unsigned long) tmp_ptr);
				found_count_0++;
			}
			SDTIF_GetTimeUSecs(&end_time);
			total_time_0 += SDTIF_GET_TIMEVAL_USECS(&end_time) -
				SDTIF_GET_TIMEVAL_USECS(&start_time);
			search_length = ((unsigned int) file_size);
			search_area   = file_buffer;
			found_count_1 = 0;
			check_sum_1   = 0L;
			SDTIF_GetTimeUSecs(&start_time);
			while ((tmp_ptr =
				((char *) STRFUNCS_SHIM_memimem(search_length, search_area,
				target_length, target_area))) != NULL) {
				search_length -= ((unsigned int) (tmp_ptr - search_area)) + 1;
				search_area    = tmp_ptr + 1;
				check_sum_1   += ((unsigned long) tmp_ptr);
				found_count_1++;
			}
			SDTIF_GetTimeUSecs(&end_time);
			total_time_1 += SDTIF_GET_TIMEVAL_USECS(&end_time) -
				SDTIF_GET_TIMEVAL_USECS(&start_time);
			search_length = ((unsigned int) file_size);
			search_area   = file_buffer;
			found_count_2 = 0;
			check_sum_2   = 0L;
			SDTIF_GetTimeUSecs(&start_time);
			while ((tmp_ptr = ((char *) BoyerMoore_memi_search_basic(search_length,
				search_area, target_length, target_area, jump_array,
				match_array))) != NULL) {
				search_length -= ((unsigned int) (tmp_ptr - search_area)) + 1;
				search_area    = tmp_ptr + 1;
				check_sum_2   += ((unsigned long) tmp_ptr);
				found_count_2++;
			}
			SDTIF_GetTimeUSecs(&end_time);
			total_time_2 += SDTIF_GET_TIMEVAL_USECS(&end_time) -
				SDTIF_GET_TIMEVAL_USECS(&start_time);
			search_length = ((unsigned int) file_size);
			search_area   = file_buffer;
			found_count_3 = 0;
			check_sum_3   = 0L;
			SDTIF_GetTimeUSecs(&start_time);
			while ((tmp_ptr = ((char *) BoyerMoore_memi_search_basic(search_length,
				search_area, target_length, target_area, jump_array,
				NULL))) != NULL) {
				search_length -= ((unsigned int) (tmp_ptr - search_area)) + 1;
				search_area    = tmp_ptr + 1;
				check_sum_3   += ((unsigned long) tmp_ptr);
				found_count_3++;
			}
			SDTIF_GetTimeUSecs(&end_time);
			total_time_3 += SDTIF_GET_TIMEVAL_USECS(&end_time) -
				SDTIF_GET_TIMEVAL_USECS(&start_time);
			if ((found_count_0 != found_count_1) ||
				(found_count_0 != found_count_2)  ||
				(found_count_0 != found_count_3)  ||
				(check_sum_0 != check_sum_1)      ||
				(check_sum_0 != check_sum_2)      ||
				(check_sum_0 != check_sum_3)) {
				fprintf(stderr, "]");
				fprintf(stderr, "\n\nERROR: %s '%s':\n",
					"searches differ for file", argv[count_1]);
				fprintf(stderr, "stristr                          : %10u %10lu\n",
					found_count_0, check_sum_0);
				fprintf(stderr, "memimem                          : %10u %10lu\n",
					found_count_1, check_sum_1);
				fprintf(stderr, "Boyer-Moore (with match array)   : %10u %10lu\n",
					found_count_2, check_sum_2);
				fprintf(stderr, "Boyer-Moore (without match array): %10u %10lu\n",
					found_count_3, check_sum_3);
				return_code = STRFUNCS_FAILURE;
				goto EXIT_FUNCTION;
			}
			total_bytes       += file_size;
			total_found_count += ((unsigned long) found_count_0);
			fclose(file_ptr);
			file_ptr = NULL;
			fprintf(stderr, ".");
		}
		fprintf(stderr, "]\n");
		fprintf(stderr, "---------------------------------- ----------\n");
		fprintf(stderr, "Files examined                   : %10u\n",
			argc - 2);
		fprintf(stderr, "Bytes examined                   : %10lu\n",
			total_bytes);
		fprintf(stderr, "Instances found                  : %10lu\n",
			total_found_count);
		fprintf(stderr, "---------------------------------- ----------\n");
		fprintf(stderr, "stristr() seconds required       : %10.6f\n",
			((double) total_time_0) / 1000000.0);
		fprintf(stderr, "memimem() seconds required       : %10.6f\n",
			((double) total_time_1) / 1000000.0);
		fprintf(stderr, "Boyer-Moore (with match array)   : %10.6f\n",
			((double) total_time_2) / 1000000.0);
		fprintf(stderr, "Boyer-Moore (without match array): %10.6f\n",
			((double) total_time_3) / 1000000.0);
		fprintf(stderr, "---------------------------------- ----------\n");
	}

EXIT_FUNCTION:

	if (file_ptr != NULL)
		fclose(file_ptr);

	if (file_buffer != NULL)
		free(file_buffer);

	if (match_array != NULL)
		free(match_array);

	fprintf(stderr, "\n");

	return(return_code);
}

# if 0
#  ifndef NARGS
char *NEW_stristr(const char *search_string, const char *target_string)
#  else
char *NEW_stristr(search_string, target_string)
const char *search_string;
const char *target_string;
#  endif /* #ifndef NARGS */
{
	const char *tmp_ptr_1;
	const char *tmp_ptr_2;

	if (!(*target_string))
		return(((char *) search_string));
	else {
		for ( ;(search_string = strichr(search_string, *target_string)) != NULL;
			search_string++) {
			for (tmp_ptr_1 = search_string, tmp_ptr_2 = target_string; ; ) {
				if (!(*(++tmp_ptr_2)))
					return(((char *) search_string));
				else {
					++tmp_ptr_1;
					if (strfmacs_toupper(*tmp_ptr_1) !=
						strfmacs_toupper(*tmp_ptr_2))
					break;
				}
			}
		}
	}

	return(NULL);
}
# endif /* #if 0 */

#endif /* #ifdef TEST_MAIN */

