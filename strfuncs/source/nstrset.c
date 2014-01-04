/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Creates a string containing the specified character.

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

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	nstrset

   SYNOPSIS    :	return_ptr = nstrset(string, char_value, count);

						char   *return_ptr;

						char   *string;

						int     char_value;

						size_t  count;

   DESCRIPTION :	Creates a string containing the character specified by
						the parameter ``char_value``.

						This function always sets ``count`` characters in ``string``
						to ``char_value``. Compare the behavior of the related
						function ``STRFUNCS_strnset``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``string`` is the string in which the characters are
						to be set.

						(.) ``char_value`` is the character to which characters in
						``string`` are to be set.

						(.) ``count`` is the number of characters in ``string`` to
						be set to ``char_value``.

   RETURNS     :	Returns the pointer ``string``.

   NOTES       :	

   CAVEATS     :	

	SEE ALSO    :	nstrset
						STRFUNCS_strnset
						STRFUNCS_strset

	EXAMPLES    :	

	AUTHOR      :	Michael L. Brock

	COPYRIGHT   :	Copyright 1986 - 2014 Michael L. Brock

	OUTPUT INDEX:	nstrset
						String Set Functions:nstrset
						STRFUNCS:String Set Functions:nstrset
						String Functions:See STRFUNCS

	PUBLISH XREF:	nstrset

	PUBLISH NAME:	nstrset

	ENTRY CLASS	:	String Set Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *nstrset(char *string, int char_value, size_t count)
#else
char *nstrset(string, char_value, count)
char   *string;
int     char_value;
size_t  count;
#endif /* #ifndef NARGS */
{
	register char *temp_ptr = string;

	for (; (count-- > 0); temp_ptr++)
		*temp_ptr = ((char) char_value);

	*temp_ptr = '\0';

	return(string);
}
/* *********************************************************************** */

