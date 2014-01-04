/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Basic string word-wrapping logic.

	Revision History	:	1986-10-27 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1986 - 2014.
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

	NAME			: 	wordwrap

   SYNOPSIS    :  return_code = wordwrap(in_text, out_list, max_cols,
							max_rows);

						int          return_code;

						const char  *in_text;

						char       **out_list;

						int          max_cols;

						int          max_rows;

	DESCRIPTION :  Separates a null-terminated string into a series of null-
						terminated lines no greater than the length specifed at
						function invocation.  The lines are placed in the memory
						areas prepared by the caller and pointed to by an array
						of pointers to char.

						Word-wrapping will preferentially be performed at certain
						natural "break" characters:  ' ' (space), ',' (comma),
						';' (semi-colon), ':' (colon), '.' period, '!' (exclamation
						point), '?' (question mark), and '-' (the hyphen, or dash).
						If no such breaking point is found in the line, the current
						word is broken at the letter which overruns the defined
						column width.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_text`` is a null-terminated string containing the
						text to be wrapped.

						(.) ``out_list`` is an array of pointers to strings in
						which each line of the output will be placed.

						(.) ``max_cols`` is the maximum number of columns of text
						to be placed on a line before forced word-wrapping occurs.

						(.) ``max_rows`` is the maximum number of ``out_list``
						elements to be used as repositories for the storage of
						lines resulting from the operation of this function.

   RETURNS     :  Returns from this function are as follow:

						(.) If non-negative, the number of lines resulting from
						the word-wrapping.

						(.) If -1, then either the ``max_cols`` parameter or the
						``max_rows' parameter was found to be less than 1 (one).

						(.) If -2, then the word-wrapping operation required more
						lines (rows) then were indicated as being available by
						the ``max_rows`` parameter.  In this case, ``max_rows``
						elements will contain the word-wrapped lines.

	NOTE(S)		:	The array ``out_list`` should have at least ``max_rows``
						elements.  Each string pointed to by the elements of
						``out_list`` must have been allocated to a minimum length
						of ``max_cols`` + 1 (the extra being, of course, for the
						null byte).  If these rules aren't followed, this function
						is likely to overwrite memory.

   CAVEATS     :  

   SEE ALSO    :  

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1986 - 2014 Michael L. Brock

   OUTPUT INDEX:  wordwrap
						String Justification Functions:wordwrap
						STRFUNCS:String Justification Functions:wordwrap
						String Functions:See STRFUNCS

   PUBLISH XREF:  wordwrap

   PUBLISH NAME:	wordwrap

	ENTRY CLASS	:	String Justification Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int  wordwrap(const char *in_text, char **out_list, int max_cols, int max_rows)
#else
int  wordwrap(in_text, out_list, max_cols, max_rows)
const char  *in_text;
char       **out_list;
int          max_cols;
int          max_rows;
#endif /* #ifndef NARGS */
{
	int   return_code = 0;
	int   curr_col    = 0;
	int   curr_row    = 0;
	int   break_col   = 0;
	char *break_ptr   = NULL;
	int   temp_row;

													/* Ensure parameters are reasonable	*/
	if ((max_cols < 1) || (max_rows < 1))
		return_code = -1;
	else {
		max_cols--;								/* Last allowed string position		*/
		while (*in_text) {
			switch (*in_text) {
				case	'\n'	:					/* LF, CR, and FF terminate the line*/
				case	'\r'	:
				case	'\f'	:
					out_list[curr_row++][curr_col] = '\0';
					curr_col   = 0;
					break_col  = 0;
					break;
				case	' '	:					/* These are the natural break chars*/
				case	','	:
				case	';'	:
				case	':'	:
				case	'.'	:
				case	'!'	:
				case	'?'	:
				case	'-'	:
					break_col = curr_col;
					break_ptr = ((char *) in_text);
					if (curr_col == max_cols) {
						out_list[curr_row][curr_col++] = *in_text;
						out_list[curr_row++][curr_col] = '\0';
						curr_col   = 0;
						break_col  = 0;
					}
					else
						out_list[curr_row][curr_col++] = *in_text;
					break;
				default		:					/* All other chars handled here		*/
					if (curr_col == max_cols) {
						if (!break_col) {
							out_list[curr_row][curr_col++] = *in_text;
							out_list[curr_row++][curr_col] = '\0';
						}
						else {
							out_list[curr_row++][break_col + 1 ] = '\0';
							in_text = break_ptr;
						}
						curr_col   = 0;
						break_col  = 0;
					}
					else
						out_list[curr_row][curr_col++] = *in_text;
			}
			if (curr_row >= max_rows) {	/* Out of array elements . . .		*/
				if (in_text[1])				/* If really more data, then error	*/
					return_code = -2;
				else								/* Otherwise, no problem				*/
					return_code = max_rows;
				break;
			}
			in_text++;
		}
		if (curr_row < max_rows) {
			out_list[curr_row++][curr_col] = '\0';
			temp_row = curr_row;
			while (temp_row < max_rows)
				out_list[temp_row++][0] = '\0';
			return_code = curr_row;
		}
	}

	return(return_code);	
}
/* *********************************************************************** */

