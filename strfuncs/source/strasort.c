/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Sorts an array.

	Revision History	:	1991-09-06 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1991 - 2016.
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
/* *********************************************************************** */
COMPAT_FN_DECL_STATIC(void STR_ARRAY_qsort_BASIC,
	(void *control_ptr, unsigned int data_count, void *data_list,
	size_t data_length,
	int (*compare_function)(void *, const void *, const void *, size_t)));
COMPAT_FN_DECL_STATIC(void STR_ARRAY_qsort_GNU,
	(void *control_ptr, unsigned int total_elems, void *pbase, size_t size,
	int (*cmp)(void *, const void *, const void *, size_t), void *pivot_buffer));
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  STR_ARRAY_qsort

   SYNOPSIS    :  void STR_ARRAY_qsort(control_ptr, data_count, data_list,
							data_length, compare_function);

						void          *control_ptr;

						unsigned int   data_count;

						void          *data_list;

						size_t         data_length;

						int          (*compare_function)(void *, const void *,
							const void *, size_t);

   DESCRIPTION :  This function sorts an array using the ACM 271 algorithm
						popularly known as Quicksort.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``control_ptr`` points to a arbitrary user-defined
						structure which may be used to modify the comparisons
						used to determine sort order. It is passed unexamined
						to the comparison function ``compare_function``. If
						unnecessary, it may be a ''NULL'' pointer.

						(.) ``data_count`` is the number of elements in the array
						``data_list``.

						(.) ``data_list`` is the array to be sorted.

						(.) ``data_length`` is the size of each element of the
						array ``data_list``.

						(.) ``compare_function`` is a pointer to the function which
						will determine sort order. The function to which
						``compare_function`` points should accept the arguments
						indicated in the SYNOPSIS and return an integral result
						as follows:

						(..) negative if the first element is less than second.

						(..) positive if the first element is greater than second.

						(..) zero if the elements are equal.

   RETURNS     :  Void.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2016 Michael L. Brock

   OUTPUT INDEX:  STR_ARRAY_qsort
						Memory Array Functions:STR_ARRAY_qsort
						STRFUNCS:Memory Array Functions:STR_ARRAY_qsort
						String Functions:See STRFUNCS

   PUBLISH XREF:  STR_ARRAY_qsort

   PUBLISH NAME:	STR_ARRAY_qsort

	ENTRY CLASS	:	Memory Array Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
void STR_ARRAY_qsort(void *control_ptr, unsigned int data_count,
	void *data_list, size_t data_length,
	int (*compare_function)(void *, const void *, const void *, size_t))
#else
void STR_ARRAY_qsort(control_ptr, data_count, data_list, data_length,
	compare_function)
void         *control_ptr;
unsigned int  data_count;
void         *data_list;
size_t        data_length;
int         (*compare_function)();
#endif /* #ifndef NARGS */
{
	void *data_buffer;

	if (data_count && (data_list != NULL) && data_length &&
		(compare_function != NULL)) {
		if ((data_count > 1024) &&
			((data_buffer = malloc(data_length)) != NULL)) {
			STR_ARRAY_qsort_GNU(control_ptr, data_count, data_list,
				data_length, compare_function, data_buffer);
			free(data_buffer);
		}
		else
			STR_ARRAY_qsort_BASIC(control_ptr, data_count, data_list,
				data_length, compare_function);
	}
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* *********************************************************************** */
#ifndef NARGS
static void STR_ARRAY_qsort_BASIC(void *control_ptr, unsigned int data_count,
	void *data_list, size_t data_length,
	int (*compare_function)(void *, const void *, const void *, size_t))
#else
static void STR_ARRAY_qsort_BASIC(control_ptr, data_count, data_list,
	data_length, compare_function)
void         *control_ptr;
unsigned int  data_count;
void         *data_list;
size_t        data_length;
int         (*compare_function)();
#endif /* #ifndef NARGS */
{
	unsigned int  count_1;
	unsigned int  count_2;
	unsigned int  count_3;
	char          tmp_char;
	void         *ptr_1;
	void         *ptr_2;
	char         *from_ptr;
	char         *to_ptr;

	if (data_count <= 1L)
		return;

	ptr_1 = ((char *) data_list) + data_length;

	if (data_count == 2) {
		if (((*compare_function)(control_ptr, data_list, ptr_1,
			data_length)) > 0) {
			from_ptr = ((char *) data_list);
			to_ptr   = ((char *) ptr_1);
			for (count_3 = 0; count_3 < data_length; count_3++) {
				tmp_char    = *from_ptr;
				*from_ptr++ = *to_ptr;
				*to_ptr++   =  tmp_char;
			}
		}
		return;
	}

	from_ptr = ((char *) data_list);
	to_ptr   = ((char *) data_list) + ((data_count / 2) * data_length);
	for (count_3 = 0; count_3 < data_length; count_3++) {
		tmp_char    = *from_ptr;
		*from_ptr++ = *to_ptr;
		*to_ptr++   =  tmp_char;
	}

	for (ptr_2 = data_list, count_2 = 0, count_1 = 1; count_1 < data_count;
		count_1++) {
		if (((*compare_function)(control_ptr, ptr_1, data_list,
			data_length)) < 0) {
			count_2++;
			ptr_2 = ((void *) (((char *) ptr_2) + data_length));
			if (ptr_1 != ptr_2) {
				from_ptr = ((char *) ptr_1);
				to_ptr   = ((char *) ptr_2);
				for (count_3 = 0; count_3 < data_length; count_3++) {
					tmp_char    = *from_ptr;
					*from_ptr++ = *to_ptr;
					*to_ptr++   =  tmp_char;
				}
			}
		}
		ptr_1 = ((void *) (((char *) ptr_1) + data_length));
	}

	if (ptr_2 != data_list) {
		from_ptr = ((char *) data_list);
		to_ptr   = ((char *) ptr_2);
		for (count_3 = 0; count_3 < data_length; count_3++) {
			tmp_char    = *from_ptr;
			*from_ptr++ = *to_ptr;
			*to_ptr++   =  tmp_char;
		}
	}

	STR_ARRAY_qsort(control_ptr, count_2, data_list, data_length,
		compare_function);

	STR_ARRAY_qsort(control_ptr, data_count - count_2 - 1,
		((void *) (((char *) ptr_2) + data_length)), data_length,
		compare_function);
}
/*	*********************************************************************** */

/*	*********************************************************************** */
/*	*********************************************************************** */
/*	*********************************************************************** */
/*	*********************************************************************** */

#define PTR									void *

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* Copyright (C) 1991, 1992 Free Software Foundation, Inc.
This file is part of the GNU C Library.
Written by Douglas C. Schmidt (schmidt@ics.uci.edu).

The GNU C Library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public License as
published by the Free Software Foundation; either version 2 of the
License, or (at your option) any later version.

The GNU C Library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with the GNU C Library; see the file COPYING.LIB.  If
not, write to the Free Software Foundation, Inc., 675 Mass Ave,
Cambridge, MA 02139, USA.  */

#include <stdlib.h>
#include <string.h>

#include "strfunci.h"

/* Byte-wise swap two items of size SIZE. */
#define SWAP(a, b, size)						      \
  do									      \
    {									      \
      register size_t __size = (size);					      \
      register char *__a = (a), *__b = (b);				      \
      do								      \
	{								      \
	  char __tmp = *__a;						      \
	  *__a++ = *__b;						      \
	  *__b++ = __tmp;						      \
	} while (--__size > 0);						      \
    } while (0)

/* Discontinue quicksort algorithm when partition gets below this size.
   This particular magic number was chosen to work best on a Sun 4/260. */
#define MAX_THRESH 4

/* Stack node declarations used to store unfulfilled partition obligations. */
typedef struct 
  {
    char *lo;
    char *hi;
  } stack_node;

/* The next 4 #defines implement a very fast in-line stack abstraction. */
#define STACK_SIZE	(8 * sizeof(unsigned long int))
#define PUSH(low, high)	((void) ((top->lo = (low)), (top->hi = (high)), ++top))
#define	POP(low, high)	((void) (--top, (low = top->lo), (high = top->hi)))
#define	STACK_NOT_EMPTY	(stack < top)                


/* Order size using quicksort.  This implementation incorporates
   four optimizations discussed in Sedgewick:

   1. Non-recursive, using an explicit stack of pointer that store the 
      next array partition to sort.  To save time, this maximum amount 
      of space required to store an array of MAX_INT is allocated on the 
      stack.  Assuming a 32-bit integer, this needs only 32 * 
      sizeof(stack_node) == 136 bits.  Pretty cheap, actually.

   2. Chose the pivot element using a median-of-three decision tree.
      This reduces the probability of selecting a bad pivot value and 
      eliminates certain extraneous comparisons.

   3. Only quicksorts TOTAL_ELEMS / MAX_THRESH partitions, leaving
      insertion sort to order the MAX_THRESH items within each partition.  
      This is a big win, since insertion sort is faster for small, mostly
      sorted array segements.

   4. The larger of the two sub-partitions is always pushed onto the
      stack first, with the algorithm then concentrating on the
      smaller partition.  This *guarantees* no more than log (n)
      stack size is needed (actually O(1) in this case)!  */

/*
void
DEFUN(qsort, (control_ptr, total_elems, pbase, size, cmp),
      PTR control_ptr AND size_t total_elems AND PTR CONST pbase AND size_t size AND
		int EXFUN((*cmp), (PTR, CONST PTR, CONST PTR, size_t)))
*/
#ifdef _MSC_VER
# pragma warning(disable:4127)
#endif /* # ifdef _MSC_VER */

#ifndef NARGS
static void STR_ARRAY_qsort_GNU(void *control_ptr, unsigned int total_elems,
	void *pbase, size_t size,
	int (*cmp)(void *, const void *, const void *, size_t), void *pivot_buffer)
#else
static void STR_ARRAY_qsort_GNU(control_ptr, total_elems, pbase, size, cmp,
	pivot_buffer)
void          *control_ptr;
unsigned int   total_elems;
void          *pbase;
size_t         size;
int          (*cmp)();
void          *pivot_buffer;
#endif /* #ifndef NARGS */
{
  register char *base_ptr = (char *) pbase;

  /* Allocating SIZE bytes for a pivot buffer facilitates a better
     algorithm below since we can do comparisons directly on the pivot. */
  const size_t max_thresh = MAX_THRESH * size;

  if (total_elems == 0)
    /* Avoid lossage with unsigned arithmetic below.  */
    return;

  if (total_elems > MAX_THRESH)
    {
      char *lo = base_ptr;
      char *hi = &lo[size * (total_elems - 1)];
      /* Largest size needed for 32-bit int!!! */
      stack_node stack[STACK_SIZE];
      stack_node *top = stack + 1;

      while (STACK_NOT_EMPTY)
        {
          char *left_ptr;
          char *right_ptr;

	  char *pivot = ((char *) pivot_buffer);

	  /* Select median value from among LO, MID, and HI. Rearrange
	     LO and HI so the three values are sorted. This lowers the 
		  probability of picking a pathological pivot value and 
		  skips a comparison for both the LEFT_PTR and RIGHT_PTR. */

	  char *mid = lo + size * ((hi - lo) / size >> 1);

	  if ((*cmp)(control_ptr, (PTR) mid, (PTR) lo, size) < 0)
	    SWAP(mid, lo, size);
	  if ((*cmp)(control_ptr, (PTR) hi, (PTR) mid, size) < 0)
	    SWAP(mid, hi, size);
	  else 
	    goto jump_over;
	  if ((*cmp)(control_ptr, (PTR) mid, (PTR) lo, size) < 0)
	    SWAP(mid, lo, size);
	jump_over:;
	  memcpy(pivot, mid, size);
	  pivot = ((char *) pivot_buffer);

	  left_ptr  = lo + size;
	  right_ptr = hi - size; 

	  /* Here's the famous ``collapse the walls'' section of quicksort.  
	     Gotta like those tight inner loops!  They are the main reason 
	     that this algorithm runs much faster than others. */
	  do 
	    {
	      while ((*cmp)(control_ptr, (PTR) left_ptr, (PTR) pivot, size) < 0)
		left_ptr += size;

	      while ((*cmp)(control_ptr, (PTR) pivot, (PTR) right_ptr, size) < 0)
		right_ptr -= size;

	      if (left_ptr < right_ptr) 
		{
		  SWAP(left_ptr, right_ptr, size);
		  left_ptr += size;
		  right_ptr -= size;
		}
	      else if (left_ptr == right_ptr) 
		{
		  left_ptr += size;
		  right_ptr -= size;
		  break;
		}
	    } 
	  while (left_ptr <= right_ptr);

          /* Set up pointers for next iteration.  First determine whether
             left and right partitions are below the threshold size.  If so, 
             ignore one or both.  Otherwise, push the larger partition's
             bounds on the stack and continue sorting the smaller one. */

          if ((size_t) (right_ptr - lo) <= max_thresh)
            {
              if ((size_t) (hi - left_ptr) <= max_thresh)
		/* Ignore both small partitions. */
                POP(lo, hi); 
              else
		/* Ignore small left partition. */  
                lo = left_ptr;
            }
          else if ((size_t) (hi - left_ptr) <= max_thresh)
	    /* Ignore small right partition. */
            hi = right_ptr;
          else if ((right_ptr - lo) > (hi - left_ptr))
            {                   
	      /* Push larger left partition indices. */
              PUSH(lo, right_ptr);
              lo = left_ptr;
            }
          else
            {                   
	      /* Push larger right partition indices. */
              PUSH(left_ptr, hi);
              hi = right_ptr;
            }
        }
    }

  /* Once the BASE_PTR array is partially sorted by quicksort the rest
     is completely sorted using insertion sort, since this is efficient 
     for partitions below MAX_THRESH size. BASE_PTR points to the beginning 
     of the array to sort, and END_PTR points at the very last element in
     the array (*not* one beyond it!). */

#ifdef min
# undef min
#endif /* #ifdef min */

#define min(x, y) ((x) < (y) ? (x) : (y))

  {
    char * const end_ptr = &base_ptr[size * (total_elems - 1)];
    char *tmp_ptr = base_ptr;
    char *thresh = min(end_ptr, base_ptr + max_thresh);
    register char *run_ptr;

    /* Find smallest element in first threshold and place it at the
       array's beginning.  This is the smallest array element,
       and the operation speeds up insertion sort's inner loop. */

    for (run_ptr = tmp_ptr + size; run_ptr <= thresh; run_ptr += size)
      if ((*cmp)(control_ptr, (PTR) run_ptr, (PTR) tmp_ptr, size) < 0)
        tmp_ptr = run_ptr;

    if (tmp_ptr != base_ptr)
      SWAP(tmp_ptr, base_ptr, size);

    /* Insertion sort, running from left-hand-side up to right-hand-side.  */

    run_ptr = base_ptr + size;
    while ((run_ptr += size) <= end_ptr)
      {
	tmp_ptr = run_ptr - size;
	while ((*cmp)(control_ptr, (PTR) run_ptr, (PTR) tmp_ptr, size) < 0)
	  tmp_ptr -= size;

	tmp_ptr += size;
        if (tmp_ptr != run_ptr)
          {
            char *trav;

	    trav = run_ptr + size;
	    while (--trav >= run_ptr)
              {
                char c = *trav;
                char *hi, *lo;

                for (hi = lo = trav; (lo -= size) >= tmp_ptr; hi = lo)
                  *hi = *lo;
                *hi = c;
              }
          }
      }
  }
}
/* *********************************************************************** */
#ifdef _MSC_VER
# pragma warning(default:4127)
#endif /* # ifdef _MSC_VER */

#ifdef TEST_MAIN

#include <stdio.h>
#include <string.h>

#include <sdtif.h>

COMPAT_FN_DECL(int main, (void));

int main()
{
	int             return_code = 0;
	unsigned int    test_count  = 0;
	char           *test_list   = NULL;
	unsigned int    count_1;
	struct timeval  start_time;
	struct timeval  end_time;
	char            buffer[81];

	fprintf(stderr, "Test of function 'STR_ARRAY_qsort()'\n");
	fprintf(stderr, "---- -- -------- -------------------\n\n");

	while ((!feof(stdin)) && (!ferror(stdin))) {
		*buffer = '\0';
		while (!(*buffer)) {
			fgets(buffer, sizeof(buffer) - 1, stdin);
			if (feof(stdin))
				break;
			while (strlen(buffer) && (buffer[strlen(buffer) - 1] == '\n'))
				buffer[strlen(buffer) - 1] = '\0';
		}
		if (!STRFUNCS_stricmp(buffer, "LIST")) {
			fprintf(stderr, "[HEAD] ---> [0X%08lX]\n",
				((unsigned long) test_list));
			for (count_1 = 0; count_1 < test_count; count_1++)
				fprintf(stderr, "[%05u][0X%08lX] ---> [%s]\n", count_1,
				((unsigned long) (test_list + (count_1 * sizeof(buffer)))),
				test_list + (count_1 * sizeof(buffer)));
		}
		else if ((!STRFUNCS_stricmp(buffer, "END")) ||
			(!STRFUNCS_stricmp(buffer, "QUIT")) ||
			(!STRFUNCS_stricmp(buffer, "EXIT")))
			break;
		else if ((return_code = mema_append(&test_count, ((void **) &test_list),
			buffer, sizeof(buffer))) == STRFUNCS_FAILURE) {
			fprintf(stderr, "\nERROR ON ATTEMPT TO APPEND STRING\n\n");
			break;
		}
		return_code = 0;
	}

	if (!return_code) {
		fprintf(stderr, "Sorting data . . . ");
		SDTIF_GetTimeUSecs(&start_time);
#ifndef NARGS
		STR_ARRAY_qsort(NULL, test_count, test_list, sizeof(buffer),
			((int (*)(void *, const void *, const void *, size_t)) STR_strcmp));
#else
		STR_ARRAY_qsort(NULL, test_count, test_list, sizeof(buffer),
			STR_strcmp);
#endif /* #ifndef NARGS */
		SDTIF_GetTimeUSecs(&end_time);
		fprintf(stderr, " %10.6f seconds.\n",
			(((double) SDTIF_GET_TIMEVAL_USECS(&end_time)) -
			((double) SDTIF_GET_TIMEVAL_USECS(&start_time))) / 1000000.0);
		fprintf(stdout, "[HEAD] ---> [0X%08lX]\n",
			((unsigned long) test_list));
		for (count_1 = 0; count_1 < test_count; count_1++)
			fprintf(stdout, "[%05u][0X%08lX] ---> [%s]\n", count_1,
				((unsigned long) (test_list + (count_1 * sizeof(buffer)))),
				test_list + (count_1 * sizeof(buffer)));
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

