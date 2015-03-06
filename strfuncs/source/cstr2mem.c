/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Resolves a string containing C/C++ escape sequences
								to its in-memory equivalent.

	Revision History	:	1994-06-03 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Include necessary header files . . .											*/
/* *********************************************************************** */

#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "strfunci.h"

/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	cstr2mem

	SYNOPSIS		:	return_ptr = cstr2mem(in_string, flags, out_length,
											out_string);

						char         *return_ptr;

						const char   *in_string;

						int           flags;

						unsigned int *out_length;

						char         *out_string;

	DESCRIPTION	:	Converts a string containing ANSI/ISO C/C++ escape sequences
						to a string with the escape sequences resolved.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_string`` points to the null-terminated string to
						be converted.

						(.) ``flags`` is an ''int'' which describes the particulars
						of the conversion to be undertaken by this function.

						(-) The only flag setting supported at the time of this
						writing is the manifest constant
						''STR_CSTR2MEM_NO_TRIGRAPHS''.

						(-) If ``flags`` has this value ''OR''ed in, ANSI C/C++
						trigraph sequences have no special meaning and will be
						copied to ``out_string`` unchanged.

						(.) ``out_length`` points to an ``unsigned int`` into
						which will be placed the number of characters converted by
						this function. If ``out_length`` is a ''NULL'' pointer,
						however, it will not be de-referenced.

						(.) ``out_string`` points the area of memory into which is
						to be written the converted string.

   RETURNS     :  The pointer ``out_string``.

	NOTES			:	This function supports the ANSI/ISO C/C++ standard escape
						sequences including trigraphs.

						This function permits the programmer to invoke it with
						``in_string`` and ``out_string`` parameters which may
						or may not point to the same string. This is done at the
						possible cost of some redundant stores.

	CAVEATS		:	Differences may be noted between the escape sequences
						emitted by this function and those emitted by compilers
						which are not ANSI-compliant.

	SEE ALSO		:	cstr2mem_alloc
						mem2cstr

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2015 Michael L. Brock
 
	OUTPUT INDEX:	cstr2mem
						String Conversion Functions:cstr2mem
						STRFUNCS:String Conversion Functions:cstr2mem
						String Functions:See STRFUNCS

	PUBLISH XREF:	cstr2mem

	PUBLISH NAME:	cstr2mem

	ENTRY CLASS	:	String Conversion Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *cstr2mem(const char *in_string, int flags, unsigned int *out_length,
	char *out_string)
#else
char *cstr2mem(in_string, flags, out_length, out_string)
const char   *in_string;
int           flags;
unsigned int *out_length;
char         *out_string;
#endif /* #ifndef NARGS */
{
#if 1
	return(cstr2mem_basic(strlen(in_string), in_string, flags, out_length,
		out_string));
#else
/*
	CODE NOTE: To be removed.
*/
	unsigned int  count_1;
	const char   *tmp_ptr_1;
	char         *tmp_ptr_2;
	unsigned int  escape_value;
	unsigned int  tmp_escape_value;
	int           trigraph_char;

	tmp_ptr_1 = in_string;
	tmp_ptr_2 = out_string;

	while (*tmp_ptr_1) {
		if (*tmp_ptr_1 == '\\') {
			if ((!(flags & STR_CSTR2MEM_NO_TRIGRAPHS)) && (tmp_ptr_1[1] == '?')){
				tmp_ptr_1++;
				*tmp_ptr_2 = '?';
			}
			else if (!tmp_ptr_1[1])
				*tmp_ptr_2 = '\\';
			else {
				tmp_ptr_1++;
				switch (*tmp_ptr_1) {
					case '\"'	:
						*tmp_ptr_2 = '\"';
						break;
					case '\''	:
						*tmp_ptr_2 = '\'';
						break;
					case '\\'	:
						*tmp_ptr_2 = '\\';
						break;
					case 'a'	:
						*tmp_ptr_2 = '\a';
						break;
					case 'b'	:
						*tmp_ptr_2 = '\b';
						break;
					case 'f'	:
						*tmp_ptr_2 = '\f';
						break;
					case 'n'	:
						*tmp_ptr_2 = '\n';
						break;
					case 'r'	:
						*tmp_ptr_2 = '\r';
						break;
					case 't'	:
						*tmp_ptr_2 = '\t';
						break;
					case 'v'	:
						*tmp_ptr_2 = '\v';
						break;
					default		:
						if ((isdigit(*tmp_ptr_1)) && (*tmp_ptr_1 < '8')) {
							escape_value = 0;
							for (count_1 = 0; count_1 < 3; count_1++, tmp_ptr_1++) {
								if ((!isdigit(*tmp_ptr_1)) || (*tmp_ptr_1 > '7') ||
									((tmp_escape_value = ((escape_value * 8) +
									(*tmp_ptr_1 - '0'))) > UCHAR_MAX))
									break;
								escape_value = tmp_escape_value;
							}
							tmp_ptr_1--;
							*tmp_ptr_2 = escape_value;
						}
						else if ((*tmp_ptr_1 == 'x') && isxdigit(tmp_ptr_1[1])) {
							tmp_ptr_1++;
							escape_value = 0;
							for (count_1 = 0; count_1 < 2; count_1++, tmp_ptr_1++) {
								if ((!isxdigit(*tmp_ptr_1)) || ((tmp_escape_value =
									((escape_value * 16) + ((isdigit(*tmp_ptr_1)) ?
									(*tmp_ptr_1 - '0') : (((isupper(*tmp_ptr_1)) ?
									(*tmp_ptr_1 - 'A') : (*tmp_ptr_1 - 'a')) + 10)))) >
									UCHAR_MAX))
									break;
								escape_value = tmp_escape_value;
							}
							tmp_ptr_1--;
							*tmp_ptr_2 = escape_value;
						}
						else
							*tmp_ptr_2 = *tmp_ptr_1;
						break;
				}
			}
		}
		else if ((!(flags & STR_CSTR2MEM_NO_TRIGRAPHS)) &&
			(*tmp_ptr_1 == '?') && (*(tmp_ptr_1 + 1) == '?') &&
			((trigraph_char = chrindx(tmp_ptr_1[2], "(/)'<!>-=")) > -1)) {
			*tmp_ptr_2  = "[\\]^{|}~#"[trigraph_char];
			tmp_ptr_1  += 2;
		}
		else
			*tmp_ptr_2 = *tmp_ptr_1;
		tmp_ptr_1++;
		tmp_ptr_2++;
	}

	if (out_length != NULL)
		*out_length = ((unsigned int) (tmp_ptr_2 - out_string));

	return(out_string);
#endif /* #if 1 */
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	cstr2mem_alloc

	SYNOPSIS		:	return_ptr = cstr2mem_alloc(in_string, flags, out_length);

						char         *return_ptr;

						const char   *in_string;

						int           flags;

						unsigned int *out_length;

	DESCRIPTION	:	Converts a string containing ANSI/ISO C/C++ escape sequences
						to a string with the escape sequences resolved. Memory for
						the converted string is allocated by this function.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_string`` points to the null-terminated string to
						be converted.

						(.) ``flags`` is an ''int'' which describes the particulars
						of the conversion to be undertaken by this function.

						(-) The only flag setting supported at the time of this
						writing is the manifest constant
						''STR_CSTR2MEM_NO_TRIGRAPHS''.

						(-) If ``flags`` has this value ''OR''ed in, ANSI C/C++
						trigraph sequences have no special meaning and will be
						copied to the converted string unchanged.

						(.) ``out_length`` points to an ``unsigned int`` into
						which will be placed the number of characters converted by
						this function. If ``out_length`` is a ''NULL'' pointer,
						however, it will not be de-referenced.

   RETURNS     :  If memory could not be allocated for the converted string,
						this function returns ''NULL''.

						Otherwise, this function returns a pointer to the memory
						allocated for the converted string.

	NOTES			:	This function supports the ANSI/ISO C/C++ standard escape
						sequences including trigraphs.

	CAVEATS		:	Differences may be noted between the escape sequences
						emitted by this function and those emitted by compilers
						which are not ANSI-compliant.

	SEE ALSO		:	cstr2mem
						cstr2mem_length
						mem2cstr_alloc

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2015 Michael L. Brock
 
	OUTPUT INDEX:	cstr2mem_alloc
						String Conversion Functions:cstr2mem_alloc
						STRFUNCS:String Conversion Functions:cstr2mem_alloc
						String Functions:See STRFUNCS

	PUBLISH XREF:	cstr2mem_alloc

	PUBLISH NAME:	cstr2mem_alloc

	ENTRY CLASS	:	String Conversion Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *cstr2mem_alloc(const char *in_string, int flags, unsigned int *out_length)
#else
char *cstr2mem_alloc(in_string, flags, out_length)
const char   *in_string;
int           flags;
unsigned int *out_length;
#endif /* #ifndef NARGS */
{
#if 1
	return(cstr2mem_basic_alloc(strlen(in_string), in_string, flags,
		out_length));
#else
/*
	CODE NOTE: To be removed.
*/
	unsigned int  tmp_length;
	char         *out_string;

	tmp_length = cstr2mem_length(in_string, flags);

	if ((out_string = ((char *) calloc(tmp_length, sizeof(char)))) != NULL)
		cstr2mem(in_string, flags, out_length, out_string);

	return(out_string);
#endif /* #if 1 */
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	cstr2mem_length

	SYNOPSIS		:	return_length = cstr2mem_length(in_string, flags);

						unsigned int  return_length;

						const char   *in_string;

						int           flags;

	DESCRIPTION	:	Determines the length of a string containing ANSI/ISO C/C++
						escape sequences when converted to a string with the escape
						sequences resolved.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_string`` points to the null-terminated string to
						be converted.

						(.) ``flags`` is an ''int'' which describes the particulars
						of the conversion to be undertaken by this function.

						(-) The only flag setting supported at the time of this
						writing is the manifest constant
						''STR_CSTR2MEM_NO_TRIGRAPHS''.

						(-) If ``flags`` has this value ''OR''ed in, ANSI C/C++
						trigraph sequences have no special meaning and will be
						counted as single characters.

   RETURNS     :  The length of the ``in_string`` if the escape sequences it
						contains were resolved by the function ``cstr2mem``. This
						value does not include the terminating ASCII ''0''.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	cstr2mem
						mem2cstr_length

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2015 Michael L. Brock
 
	OUTPUT INDEX:	cstr2mem_length
						String Conversion Functions:cstr2mem_length
						STRFUNCS:String Conversion Functions:cstr2mem_length
						String Functions:See STRFUNCS

	PUBLISH XREF:	cstr2mem_length

	PUBLISH NAME:	cstr2mem_length

	ENTRY CLASS	:	String Conversion Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
unsigned int cstr2mem_length(const char *in_string, int flags)
#else
unsigned int cstr2mem_length(in_string, flags)
const char *in_string;
int         flags;
#endif /* #ifndef NARGS */
{
#if 1
	return(cstr2mem_basic_length(strlen(in_string), in_string, flags));
#else
/*
	CODE NOTE: To be removed.
*/
	unsigned int  count_1;
	const char   *tmp_ptr_1;
	const char   *tmp_ptr_2;
	unsigned int  escape_value;
	unsigned int  tmp_escape_value;

	tmp_ptr_1 = in_string;
	tmp_ptr_2 = in_string;

	while (*tmp_ptr_1) {
		if (*tmp_ptr_1 == '\\') {
			if ((!(flags & STR_CSTR2MEM_NO_TRIGRAPHS)) && (tmp_ptr_1[1] == '?'))
				tmp_ptr_1++;
			else if (tmp_ptr_1[1]) {
				tmp_ptr_1++;
				if (idxchr("\"'\\abfnrtv", *tmp_ptr_1) > -1)
					;
				else if ((isdigit(*tmp_ptr_1)) && (*tmp_ptr_1 < '8')) {
					escape_value = 0;
					for (count_1 = 0; count_1 < 3; count_1++, tmp_ptr_1++) {
						if ((!isdigit(*tmp_ptr_1)) || (*tmp_ptr_1 > '7') ||
							((tmp_escape_value = ((escape_value * 8) +
							(*tmp_ptr_1 - '0'))) > UCHAR_MAX))
							break;
						escape_value = tmp_escape_value;
					}
					tmp_ptr_1--;
				}
				else if ((*tmp_ptr_1 == 'x') && isxdigit(tmp_ptr_1[1])) {
					tmp_ptr_1++;
					escape_value = 0;
					for (count_1 = 0; count_1 < 2; count_1++, tmp_ptr_1++) {
						if ((!isxdigit(*tmp_ptr_1)) || ((tmp_escape_value =
							((escape_value * 16) + ((isdigit(*tmp_ptr_1)) ?
							(*tmp_ptr_1 - '0') : (((isupper(*tmp_ptr_1)) ?
							(*tmp_ptr_1 - 'A') : (*tmp_ptr_1 - 'a')) + 10)))) >
							UCHAR_MAX))
							break;
						escape_value = tmp_escape_value;
					}
					tmp_ptr_1--;
				}
			}
		}
		else if ((!(flags & STR_CSTR2MEM_NO_TRIGRAPHS)) &&
			(*tmp_ptr_1 == '?') && (*(tmp_ptr_1 + 1) == '?') &&
			(chrindx(tmp_ptr_1[2], "(/)'<!>-=") > -1))
			tmp_ptr_1  += 2;
		tmp_ptr_1++;
		tmp_ptr_2++;
	}

	return(((unsigned int) (tmp_ptr_2 - in_string)));
#endif /* #if 1 */
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	cstr2mem_basic

	SYNOPSIS		:	return_ptr = cstr2mem_basic(in_length, in_string, flags,
							out_length, out_string);

						char         *return_ptr;

						unsigned int  in_length;

						const char   *in_string;

						int           flags;

						unsigned int *out_length;

						char         *out_string;

	DESCRIPTION	:	Converts a string containing ANSI/ISO C/C++ escape sequences
						to a string with the escape sequences resolved.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_length`` is the length of the string to which the
						``in_string`` parameter points.

						(.) ``in_string`` points to the string to be converted.

						(.) ``flags`` is an ''int'' which describes the particulars
						of the conversion to be undertaken by this function.

						(-) The only flag setting supported at the time of this
						writing is the manifest constant
						''STR_CSTR2MEM_NO_TRIGRAPHS''.

						(-) If ``flags`` has this value ''OR''ed in, ANSI C/C++
						trigraph sequences have no special meaning and will be
						copied to ``out_string`` unchanged.

						(.) ``out_length`` points to an ``unsigned int`` into
						which will be placed the number of characters converted by
						this function. If ``out_length`` is a ''NULL'' pointer,
						however, it will not be de-referenced.

						(.) ``out_string`` points the area of memory into which is
						to be written the converted string.

   RETURNS     :  The pointer ``out_string``.

	NOTES			:	This function supports the ANSI/ISO C/C++ standard escape
						sequences including trigraphs.

						This function permits the programmer to invoke it with
						``in_string`` and ``out_string`` parameters which may
						or may not point to the same string. This is done at the
						possible cost of some redundant stores.

	CAVEATS		:	Differences may be noted between the escape sequences
						emitted by this function and those emitted by compilers
						which are not ANSI-compliant.

	SEE ALSO		:	cstr2mem_basic_alloc
						cstr2mem
						mem2cstr

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2015 Michael L. Brock
 
	OUTPUT INDEX:	cstr2mem_basic
						String Conversion Functions:cstr2mem_basic
						STRFUNCS:String Conversion Functions:cstr2mem_basic
						String Functions:See STRFUNCS

	PUBLISH XREF:	cstr2mem_basic

	PUBLISH NAME:	cstr2mem_basic

	ENTRY CLASS	:	String Conversion Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *cstr2mem_basic(unsigned int in_length, const char *in_string,
	int flags, unsigned int *out_length, char *out_string)
#else
char *cstr2mem_basic(in_length, in_string, flags, out_length, out_string)
unsigned int  in_length;
const char   *in_string;
int           flags;
unsigned int *out_length;
char         *out_string;
#endif /* #ifndef NARGS */
{
	unsigned int  count_1;
	const char   *tmp_ptr_1;
	char         *tmp_ptr_2;
	unsigned int  escape_value;
	unsigned int  tmp_escape_value;
	int           trigraph_char;

	tmp_ptr_1 = in_string;
	tmp_ptr_2 = out_string;

	while (in_length && *tmp_ptr_1) {
		if (*tmp_ptr_1 == '\\') {
			in_length--;
			if (!in_length) {
				*tmp_ptr_2++ = '\\';
				break;
			}
			if ((!(flags & STR_CSTR2MEM_NO_TRIGRAPHS)) && (tmp_ptr_1[1] == '?')){
				tmp_ptr_1++;
				*tmp_ptr_2 = '?';
			}
			else if (tmp_ptr_1[1]) {
				tmp_ptr_1++;
				switch (*tmp_ptr_1) {
					case '\"'	:
						*tmp_ptr_2 = '\"';
						break;
					case '\''	:
						*tmp_ptr_2 = '\'';
						break;
					case '\\'	:
						*tmp_ptr_2 = '\\';
						break;
					case 'a'	:
						*tmp_ptr_2 = '\a';
						break;
					case 'b'	:
						*tmp_ptr_2 = '\b';
						break;
					case 'f'	:
						*tmp_ptr_2 = '\f';
						break;
					case 'n'	:
						*tmp_ptr_2 = '\n';
						break;
					case 'r'	:
						*tmp_ptr_2 = '\r';
						break;
					case 't'	:
						*tmp_ptr_2 = '\t';
						break;
					case 'v'	:
						*tmp_ptr_2 = '\v';
						break;
					default		:
						if ((isdigit(*tmp_ptr_1)) && (*tmp_ptr_1 < '8')) {
							escape_value = 0;
							for (count_1 = 0; count_1 < 3; count_1++, tmp_ptr_1++) {
								if ((!in_length) || (!isdigit(*tmp_ptr_1)) ||
									(*tmp_ptr_1 > '7') ||
									((tmp_escape_value = ((escape_value * 8) +
									(*tmp_ptr_1 - '0'))) > UCHAR_MAX))
									break;
								escape_value = tmp_escape_value;
								in_length--;
							}
							if (in_length) {
								tmp_ptr_1--;
								in_length++;
							}
							*tmp_ptr_2 = ((char) escape_value);
						}
						else if ((*tmp_ptr_1 == 'x') && (in_length > 1) &&
							isxdigit(tmp_ptr_1[1])) {
							tmp_ptr_1++;
							escape_value = 0;
							for (count_1 = 0; count_1 < 2; count_1++, tmp_ptr_1++) {
								if ((!in_length) || (!isxdigit(*tmp_ptr_1)) ||
									((tmp_escape_value =
									((escape_value * 16) + ((isdigit(*tmp_ptr_1)) ?
									(*tmp_ptr_1 - '0') : (((isupper(*tmp_ptr_1)) ?
									(*tmp_ptr_1 - 'A') : (*tmp_ptr_1 - 'a')) + 10)))) >
									UCHAR_MAX))
									break;
								escape_value = tmp_escape_value;
								in_length--;
							}
							if (in_length) {
								tmp_ptr_1--;
								in_length++;
							}
							*tmp_ptr_2 = ((char) escape_value);
						}
						else
							*tmp_ptr_2 = *tmp_ptr_1;
						break;
				}
			}
		}
		else if ((!(flags & STR_CSTR2MEM_NO_TRIGRAPHS)) && (in_length >= 3) &&
			(*tmp_ptr_1 == '?') && (*(tmp_ptr_1 + 1) == '?') &&
			((trigraph_char = chrindx(tmp_ptr_1[2], "(/)'<!>-=")) > -1)) {
			*tmp_ptr_2  = "[\\]^{|}~#"[trigraph_char];
			tmp_ptr_1  += 2;
			in_length  -= 2;
		}
		else
			*tmp_ptr_2 = *tmp_ptr_1;
		tmp_ptr_1++;
		tmp_ptr_2++;
		if (!in_length--)
			break;
	}

	if (out_length != NULL)
		*out_length = ((unsigned int) (tmp_ptr_2 - out_string));

	return(out_string);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	cstr2mem_basic_alloc

	SYNOPSIS		:	return_ptr = cstr2mem_basic_alloc(in_length, in_string,
							flags, out_length);

						char         *return_ptr;

						unsigned int  in_length;

						const char   *in_string;

						int           flags;

						unsigned int *out_length;

	DESCRIPTION	:	Converts a string containing ANSI/ISO C/C++ escape sequences
						to a string with the escape sequences resolved. Memory for
						the converted string is allocated by this function.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_length`` is the length of the string to which the
						``in_string`` parameter points.

						(.) ``in_string`` points to the string to be converted.

						(.) ``flags`` is an ''int'' which describes the particulars
						of the conversion to be undertaken by this function.

						(-) The only flag setting supported at the time of this
						writing is the manifest constant
						''STR_CSTR2MEM_NO_TRIGRAPHS''.

						(-) If ``flags`` has this value ''OR''ed in, ANSI C/C++
						trigraph sequences have no special meaning and will be
						copied to the converted string unchanged.

						(.) ``out_length`` points to an ``unsigned int`` into
						which will be placed the number of characters converted by
						this function. If ``out_length`` is a ''NULL'' pointer,
						however, it will not be de-referenced.

   RETURNS     :  If memory could not be allocated for the converted string,
						this function returns ''NULL''.

						Otherwise, this function returns a pointer to the memory
						allocated for the converted string.

	NOTES			:	This function supports the ANSI/ISO C/C++ standard escape
						sequences including trigraphs.

	CAVEATS		:	Differences may be noted between the escape sequences
						emitted by this function and those emitted by compilers
						which are not ANSI-compliant.

	SEE ALSO		:	cstr2mem_alloc
						cstr2mem_basic
						cstr2mem_basic_length
						mem2cstr_alloc

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2015 Michael L. Brock
 
	OUTPUT INDEX:	cstr2mem_basic_alloc
						String Conversion Functions:cstr2mem_basic_alloc
						STRFUNCS:String Conversion Functions:cstr2mem_basic_alloc
						String Functions:See STRFUNCS

	PUBLISH XREF:	cstr2mem_basic_alloc

	PUBLISH NAME:	cstr2mem_basic_alloc

	ENTRY CLASS	:	String Conversion Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *cstr2mem_basic_alloc(unsigned int in_length, const char *in_string,
	int flags, unsigned int *out_length)
#else
char *cstr2mem_basic_alloc(in_length, in_string, flags, out_length)
unsigned int  in_length;
const char   *in_string;
int           flags;
unsigned int *out_length;
#endif /* #ifndef NARGS */
{
	unsigned int  tmp_length;
	char         *out_string;

	tmp_length = cstr2mem_basic_length(in_length, in_string, flags);

	if ((out_string = ((char *) calloc(tmp_length, sizeof(char)))) != NULL)
		cstr2mem_basic(in_length, in_string, flags, out_length, out_string);

	return(out_string);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	cstr2mem_basic_length

	SYNOPSIS		:	return_length = cstr2mem_basic_length(in_length, in_string,
							flags);

						unsigned int  return_length;

						unsigned int  in_length;

						const char   *in_string;

						int           flags;

	DESCRIPTION	:	Determines the length of a string containing ANSI/ISO C/C++
						escape sequences when converted to a string with the escape
						sequences resolved.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_length`` is the length of the string to which the
						``in_string`` parameter points.

						(.) ``in_string`` points to the string to be converted.

						(.) ``flags`` is an ''int'' which describes the particulars
						of the conversion to be undertaken by this function.

						(-) The only flag setting supported at the time of this
						writing is the manifest constant
						''STR_CSTR2MEM_NO_TRIGRAPHS''.

						(-) If ``flags`` has this value ''OR''ed in, ANSI C/C++
						trigraph sequences have no special meaning and will be
						counted as single characters.

   RETURNS     :  The length of the ``in_string`` if the escape sequences it
						contains were resolved by the function ``cstr2mem_basic``.
						This value does not include the terminating ASCII ''0''.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	cstr2mem_length
						cstr2mem_basic
						mem2cstr_length

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2015 Michael L. Brock
 
	OUTPUT INDEX:	cstr2mem_basic_length
						String Conversion Functions:cstr2mem_basic_length
						STRFUNCS:String Conversion Functions:cstr2mem_basic_length
						String Functions:See STRFUNCS

	PUBLISH XREF:	cstr2mem_basic_length

	PUBLISH NAME:	cstr2mem_basic_length

	ENTRY CLASS	:	String Conversion Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
unsigned int cstr2mem_basic_length(unsigned int in_length,
	const char *in_string, int flags)
#else
unsigned int cstr2mem_basic_length(in_length, in_string, flags)
unsigned int  in_length;
const char   *in_string;
int           flags;
#endif /* #ifndef NARGS */
{
	unsigned int  count_1;
	const char   *tmp_ptr_1;
	const char   *tmp_ptr_2;
	unsigned int  escape_value;
	unsigned int  tmp_escape_value;

	tmp_ptr_1 = in_string;
	tmp_ptr_2 = in_string;

	while (in_length && *tmp_ptr_1) {
		if (*tmp_ptr_1 == '\\') {
			in_length--;
			if (!in_length) {
				tmp_ptr_2++;
				break;
			}
			if ((!(flags & STR_CSTR2MEM_NO_TRIGRAPHS)) && (tmp_ptr_1[1] == '?'))
				tmp_ptr_1++;
			else if (tmp_ptr_1[1]) {
				tmp_ptr_1++;
				if (idxchr("\"'\\abfnrtv", *tmp_ptr_1) > -1)
					;
				else if ((isdigit(*tmp_ptr_1)) && (*tmp_ptr_1 < '8')) {
					escape_value = 0;
					for (count_1 = 0; count_1 < 3; count_1++, tmp_ptr_1++) {
						if ((!in_length) || (!isdigit(*tmp_ptr_1)) ||
							(*tmp_ptr_1 > '7') ||
							((tmp_escape_value = ((escape_value * 8) +
							(*tmp_ptr_1 - '0'))) > UCHAR_MAX))
							break;
						escape_value = tmp_escape_value;
						in_length--;
					}
					if (in_length) {
						tmp_ptr_1--;
						in_length++;
					}
				}
				else if ((*tmp_ptr_1 == 'x') && (in_length > 1) &&
					isxdigit(tmp_ptr_1[1])) {
					tmp_ptr_1++;
					escape_value = 0;
					for (count_1 = 0; count_1 < 2; count_1++, tmp_ptr_1++) {
						if ((!in_length) || (!isxdigit(*tmp_ptr_1)) ||
							((tmp_escape_value =
							((escape_value * 16) + ((isdigit(*tmp_ptr_1)) ?
							(*tmp_ptr_1 - '0') : (((isupper(*tmp_ptr_1)) ?
							(*tmp_ptr_1 - 'A') : (*tmp_ptr_1 - 'a')) + 10)))) >
							UCHAR_MAX))
							break;
						escape_value = tmp_escape_value;
						in_length--;
					}
					if (in_length) {
						tmp_ptr_1--;
						in_length++;
					}
				}
			}
		}
		else if ((!(flags & STR_CSTR2MEM_NO_TRIGRAPHS)) && (in_length >= 3) &&
			(*tmp_ptr_1 == '?') && (*(tmp_ptr_1 + 1) == '?') &&
			(chrindx(tmp_ptr_1[2], "(/)'<!>-=") > -1)) {
			tmp_ptr_1  += 2;
			in_length  -= 2;
		}
		tmp_ptr_1++;
		tmp_ptr_2++;
		if (!in_length--)
			break;
	}

	return(((unsigned int) (tmp_ptr_2 - in_string)));
}
/* *********************************************************************** */

/*
	CODE NOTE: To be deleted.
char *NEW_cstring(in_string, out_string, out_length)
const char   *in_string;
char         *out_string;
unsigned int *out_length;
{
	unsigned int  count_1;
	const char   *tmp_ptr_1;
	char         *tmp_ptr_2;
	unsigned int  escape_value;
	unsigned int  tmp_escape_value;
	int           trigraph_char;

int flags = 0;

	tmp_ptr_1 = in_string;
	tmp_ptr_2 = out_string;

	while (*tmp_ptr_1) {
		if (*tmp_ptr_1 == '\\') {
			if ((!(flags & STR_CSTR2MEM_NO_TRIGRAPHS)) && (tmp_ptr_1[1] == '?')){
				tmp_ptr_1++;
				*tmp_ptr_2 = '?';
			}
			else if (!tmp_ptr_1[1])
				*tmp_ptr_2 = '\\';
			else {
				tmp_ptr_1++;
				switch (*tmp_ptr_1) {
					case '\"'	:
						*tmp_ptr_2 = '\"';
						break;
					case '\''	:
						*tmp_ptr_2 = '\'';
						break;
					case '\\'	:
						*tmp_ptr_2 = '\\';
						break;
					case 'a'	:
						*tmp_ptr_2 = '\a';
						break;
					case 'b'	:
						*tmp_ptr_2 = '\b';
						break;
					case 'f'	:
						*tmp_ptr_2 = '\f';
						break;
					case 'n'	:
						*tmp_ptr_2 = '\n';
						break;
					case 'r'	:
						*tmp_ptr_2 = '\r';
						break;
					case 't'	:
						*tmp_ptr_2 = '\t';
						break;
					case 'v'	:
						*tmp_ptr_2 = '\v';
						break;
					default		:
						if ((isdigit(*tmp_ptr_1)) && (*tmp_ptr_1 < '8')) {
							escape_value = 0;
							for (count_1 = 0; count_1 < 3; count_1++, tmp_ptr_1++) {
								if ((!isdigit(*tmp_ptr_1)) || (*tmp_ptr_1 > '7') ||
									((tmp_escape_value = ((escape_value * 8) +
									(*tmp_ptr_1 - '0'))) > UCHAR_MAX))
									break;
								escape_value = tmp_escape_value;
							}
							tmp_ptr_1--;
							*tmp_ptr_2 = escape_value;
						}
						else if ((*tmp_ptr_1 == 'x') && isxdigit(tmp_ptr_1[1])) {
							tmp_ptr_1++;
							escape_value = 0;
							for (count_1 = 0; count_1 < 2; count_1++, tmp_ptr_1++) {
								if ((!isxdigit(*tmp_ptr_1)) || ((tmp_escape_value =
									((escape_value * 16) + ((isdigit(*tmp_ptr_1)) ?
									(*tmp_ptr_1 - '0') : (((isupper(*tmp_ptr_1)) ?
									(*tmp_ptr_1 - 'A') : (*tmp_ptr_1 - 'a')) + 10)))) >
									UCHAR_MAX))
									break;
								escape_value = tmp_escape_value;
							}
							tmp_ptr_1--;
							*tmp_ptr_2 = escape_value;
						}
						else
							*tmp_ptr_2 = *tmp_ptr_1;
						break;
				}
			}
		}
		else if ((!(flags & STR_CSTR2MEM_NO_TRIGRAPHS)) &&
			(*tmp_ptr_1 == '?') && (*(tmp_ptr_1 + 1) == '?') &&
			((trigraph_char = chrindx(tmp_ptr_1[2], "(/)'<!>-=")) > -1)) {
			*tmp_ptr_2  = "[\\]^{|}~#"[trigraph_char];
			tmp_ptr_1  += 2;
		}
		else
			*tmp_ptr_2 = *tmp_ptr_1;
		tmp_ptr_1++;
		tmp_ptr_2++;
	}

	*tmp_ptr_2 = '\0';

	if (out_length != NULL)
		*out_length = ((unsigned int) (tmp_ptr_2 - out_string));

	return(out_string);
}
*/

#ifdef TEST_MAIN

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

COMPAT_FN_DECL(int main, (void));

static char *TestLineList[] = {
/*  01    2    345 */
	": \\101\\102 :",
/*  01    2    3    4567890  12345678 */
	": \\101\\102\\103 ---> \\8 (tab)",
/*  0123456789012345678901 */
	"Ends in a back-slash \\",
/*  012345678901234567890     1 */
	"Ends in a back-slash \?\?\/",
/*  01234567890123456789012 */
	"This is a simple test.",
/*  012345678901234567890123  456789012345678901234567890123 */
	"This has an embedded tab\\tin the middle of the string.",
/*  01234567890123456789012345    6    7    8901234  56789012 */
	"This has octal sequences: \\101\\102\\103 ---> \\8 (tab)",
/*  01234567890123456789012345678901    2    3    4567890    1   23456789 */
	"This has hexadecimal sequences: \\x41\\x42\\x43 ---> \\x4a\\x8 (tab)",
/*  012345678901234567890123456789012345678  9012345  6 */
	"This does not have trigraph sequences: \\? ---> \\?",
/*  01234567890123456789012345678   9012345   67 */
	"This has trigraph sequences: \??( ---> \??)"
};

static unsigned int TestLineCount =
	sizeof(TestLineList) / sizeof(TestLineList[0]);

int main()
{
	int            return_code = 0;
	unsigned int   count_1;
	unsigned int   result_length_1;
	unsigned int   result_length_2;
	char           buffer_1[1024];
	char           buffer_2[1024];

	STR_EMIT_CharLine('=', 78, NULL, NULL);
	STR_EMIT_CharLine('=', 78, NULL, NULL);

	fprintf(stderr, "Test routine for 'cstr2mem()'\n");
	fprintf(stderr, "---- ------- --- ------------\n");

	STR_EMIT_CharLine('=', 78, NULL, NULL);
	printf("Test One: Built-In Test\n");
	for (count_1 = 0; count_1 < TestLineCount; count_1++) {
		cstring(TestLineList[count_1], buffer_1, &result_length_1);
		cstr2mem_basic(strlen(TestLineList[count_1]), TestLineList[count_1],
			0, &result_length_2, buffer_2);
		if ((result_length_1 != result_length_2) ||
			memcmp(buffer_1, buffer_2, result_length_1)) {
			printf("ERROR IN TEST: cstring ---> cstr2mem_basic\n");
			STR_EMIT_CharLine('-', 78, NULL, NULL);
			printf("%05u:Original String:[%s]\n",
				count_1, TestLineList[count_1]);
			printf("     :cstring        :[%-*.*s] = %u\n",
				result_length_1, ((int) result_length_1), buffer_1, result_length_1);
			printf("     :NEW_cstring    :[%-*.*s] = %u\n",
				result_length_2, ((int) result_length_2), buffer_2, result_length_2);
			return_code = -1;
		}
		cstr2mem(TestLineList[count_1], 0, &result_length_2, buffer_2);
		if ((result_length_1 != result_length_2) ||
			memcmp(buffer_1, buffer_2, result_length_1)) {
			printf("ERROR IN TEST: cstring ---> cstr2mem\n");
			STR_EMIT_CharLine('-', 78, NULL, NULL);
			printf("%05u:Original String:[%s]\n",
				count_1, TestLineList[count_1]);
			printf("     :cstring        :[%-*.*s] = %u\n",
				result_length_1, ((int) result_length_1), buffer_2, result_length_1);
			printf("     :cstr2mem       :[%-*.*s] = %u\n",
				result_length_2, ((int) result_length_2), buffer_2, result_length_2);
			return_code = -1;
		}
		result_length_2 = cstr2mem_length(TestLineList[count_1], 0);
		if (result_length_1 != result_length_2) {
			printf("ERROR IN TEST: cstring ---> cstr2mem_length\n");
			STR_EMIT_CharLine('-', 78, NULL, NULL);
			printf("%05u:Original String:[%s]\n",
				count_1, TestLineList[count_1]);
			printf("     :cstring        :%u\n", result_length_1);
			printf("     :cstr2mem_length:%u\n", result_length_2);
			return_code = -1;
		}
	}
	STR_EMIT_CharLine('=', 78, NULL, NULL);
	printf("%s regression tests.\n",
		(return_code == STRFUNCS_SUCCESS) ? "Passed" : "Failed");
	STR_EMIT_CharLine('=', 78, NULL, NULL);
	printf("\n");

	fprintf(stderr, "\n\n%s regression tests.\n\n",
		(return_code == STRFUNCS_SUCCESS) ? "Passed" : "Failed");

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

