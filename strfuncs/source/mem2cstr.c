/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Resolves a memory buffer to its string equivalent
								containing C/C++ escape sequences.

	Revision History	:	1994-06-03 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2016.
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
#include <stdlib.h>

#include "strfunci.h"

/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	mem2cstr

	SYNOPSIS		:	return_ptr = mem2cstr(in_length, in_string, flags,
											out_string);

						char         *return_ptr;

						unsigned int  in_length;

						const char   *in_string;

						int           flags;

						char         *out_string;

	DESCRIPTION	:	Converts a memory buffer into a string containing ANSI/ISO
						C/C++ escape sequences.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_length`` is the length of the memory buffer
						``in_string``.

						(.) ``in_string`` points to the memory buffer to be
						converted.

						(.) ``flags`` is an ''int'' which describes the particulars
						of the conversion to be undertaken by this function.

						(-) The only flag setting supported at the time of this
						writing is the manifest constant
						''STR_MEM2CSTR_NO_TRIGRAPHS''.

						(-) If ``flags`` does not have this value ''OR''ed in, the
						following characters will be converted by this function to
						their equivalent ANSI C trigraph sequences:

						(-) ''['' ''\'' '']'' ''^'' ''{'' ''|'' ''}'' ''~'' ''#''

						(.) ``out_string`` points the area of memory into which is
						to be written the converted string.

   RETURNS     :  The pointer ``out_string``.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	mem2cstr_alloc
						cstr2mem

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2016 Michael L. Brock
 
	OUTPUT INDEX:	mem2cstr
						String Conversion Functions:mem2cstr
						STRFUNCS:String Conversion Functions:mem2cstr
						String Functions:See STRFUNCS

	PUBLISH XREF:	mem2cstr

	PUBLISH NAME:	mem2cstr

	ENTRY CLASS	:	String Conversion Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *mem2cstr(unsigned int in_length, const char *in_string, int flags,
	char *out_string)
#else
char *mem2cstr(in_length, in_string, flags, out_string)
unsigned int  in_length;
const char   *in_string;
int           flags;
char         *out_string;
#endif /* #ifndef NARGS */
{
	unsigned int  count_1;
	int           tmp_index;
	const char   *in_ptr;
	char         *out_ptr;

	in_ptr  = in_string;
	out_ptr = out_string;

	for (count_1 = 0; count_1 < in_length; count_1++, in_ptr++) {
		if ((!(flags & STR_MEM2CSTR_NO_TRIGRAPHS)) &&
			((tmp_index = chrindx(*in_ptr, "[\\]^{|}~#")) > -1)) {
			*out_ptr++ = '?';
			*out_ptr++ = '?';
			*out_ptr++ = "(/)'<!>-="[tmp_index];
		}
		else if ((!(flags & STR_MEM2CSTR_NO_TRIGRAPHS)) && (*in_ptr == '?')) {
			*out_ptr++ = '\\';
			*out_ptr++ = '?';
		}
		else if ((tmp_index = idxchr("\"\\\a\b\f\n\r\t\v", *in_ptr)) > -1) {
			*out_ptr++ = '\\';
			*out_ptr++ = "\"\\abfnrtv"[tmp_index];
		}
		else if (isprint(*in_ptr))
			*out_ptr++ = *in_ptr;
		else if (!(*in_ptr)) {
			*out_ptr++ = '\\';
			*out_ptr++ = '0';
		}
		else {
			*out_ptr++ = '\\';
			*out_ptr++ = 'x';
			if (*in_ptr & 0XF0)
				*out_ptr++ = "0123456789abcdef"[(*in_ptr >> 4) & 0X0F];
			*out_ptr++ = "0123456789abcdef"[*in_ptr & 0X0F];
		}
	}

	*out_ptr = '\0';

	return(out_string);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	mem2cstr_alloc

	SYNOPSIS		:	return_ptr = mem2cstr_alloc(in_length, in_string, flags);

						char         *return_ptr;

						unsigned int  in_length;

						const char   *in_string;

						int           flags;

	DESCRIPTION	:	Converts a memory buffer into a string containing ANSI/ISO
						C/C++ escape sequences. Memory for the converted string is
						allocated by this function.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_length`` is the length of the memory buffer
						``in_string``.

						(.) ``in_string`` points to the memory buffer to be
						converted.

						(.) ``flags`` is an ''int'' which describes the particulars
						of the conversion to be undertaken by this function.

						(-) The only flag setting supported at the time of this
						writing is the manifest constant
						''STR_MEM2CSTR_NO_TRIGRAPHS''.

						(-) If ``flags`` does not have this value ''OR''ed in, the
						following characters will be converted by this function to
						their equivalent ANSI C trigraph sequences:

						(-) ''['' ''\'' '']'' ''^'' ''{'' ''|'' ''}'' ''~'' ''#''

   RETURNS     :  If memory could not be allocated for the converted string,
						this function returns ''NULL''.

						Otherwise, this function returns a pointer to the memory
						allocated for the converted string.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	mem2cstr
						mem2cstr_length
						cstr2mem_alloc

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2016 Michael L. Brock
 
	OUTPUT INDEX:	mem2cstr_alloc
						String Conversion Functions:mem2cstr_alloc
						STRFUNCS:String Conversion Functions:mem2cstr_alloc
						String Functions:See STRFUNCS

	PUBLISH XREF:	mem2cstr_alloc

	PUBLISH NAME:	mem2cstr_alloc

	ENTRY CLASS	:	String Conversion Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *mem2cstr_alloc(unsigned int in_length, const char *in_string, int flags)
#else
char *mem2cstr_alloc(in_length, in_string, flags)
unsigned int  in_length;
const char   *in_string;
int           flags;
#endif /* #ifndef NARGS */
{
	unsigned int  out_length;
	char         *out_string;

	out_length = mem2cstr_length(in_length, in_string, flags);

	if ((out_string = ((char *) calloc(out_length + 1, sizeof(char)))) != NULL)
		mem2cstr(in_length, in_string, flags, out_string);

	return(out_string);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	mem2cstr_length

	SYNOPSIS		:	return_length = mem2cstr_length(in_length, in_string,
							flags);

						unsigned int  return_length;

						unsigned int  in_length;

						const char   *in_string;

						int           flags;

	DESCRIPTION	:	Determines the length of a memory buffer when converted into
						a string containing ANSI/ISO C/C++ escape sequences.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_length`` is the length of the memory buffer
						``in_string``.

						(.) ``in_string`` points to the memory buffer to be
						converted.

						(.) ``flags`` is an ''int'' which describes the particulars
						of the conversion to be undertaken by this function.

						(-) The only flag setting supported at the time of this
						writing is the manifest constant
						''STR_MEM2CSTR_NO_TRIGRAPHS''.

						(-) If ``flags`` does not have this value ''OR''ed in, the
						following characters will be counted by this function as
						having the length of their trigraph equivalents (that is,
						three characters):

						(-) ''['' ''\'' '']'' ''^'' ''{'' ''|'' ''}'' ''~'' ''#''

   RETURNS     :  The length of the ``in_string`` if it were resolved by the
						function ``mem2cstr``. This value does not include the
						terminating ASCII ''0''.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	mem2cstr
						cstr2mem_length

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2016 Michael L. Brock
 
	OUTPUT INDEX:	mem2cstr_length
						String Conversion Functions:mem2cstr_length
						STRFUNCS:String Conversion Functions:mem2cstr_length
						String Functions:See STRFUNCS

	PUBLISH XREF:	mem2cstr_length

	PUBLISH NAME:	mem2cstr_length

	ENTRY CLASS	:	String Conversion Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
unsigned int mem2cstr_length(unsigned int in_length, const char *in_string,
	int flags)
#else
unsigned int mem2cstr_length(in_length, in_string, flags)
unsigned int  in_length;
const char   *in_string;
int           flags;
#endif /* #ifndef NARGS */
{
	unsigned int out_length = 0;

	if (flags & STR_MEM2CSTR_NO_TRIGRAPHS) {
		for ( ; in_length; in_length--, in_string++)
			out_length += (idxchr("\"\\\a\b\f\n\r\t\v", *in_string) > -1) ? 2 :
				(isprint(*in_string)) ? 1 : (!(*in_string)) ? 2 : (3 +
				((*in_string & 0XF0) ? 1 : 0));
	}
	else {
		for ( ; in_length; in_length--, in_string++)
			out_length += (chrindx(*in_string, "[\\]^{|}~#") > -1) ? 3 :
				(idxchr("\"\?\\\a\b\f\n\r\t\v", *in_string) > -1) ? 2 :
				(isprint(*in_string)) ? 1 : (!(*in_string)) ? 2 : (3 +
				((*in_string & 0XF0) ? 1 : 0));
	}

	return(out_length);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

COMPAT_FN_DECL(int main, (void));

static const char         *TEST_List[][3] = {
	{
		"End-\\101",
		"End-A",
		"End-A"
	},
	{
		"\\101-Begin",
		"A-Begin",
		"A-Begin"
	},
	{
		"Mid-\\101-Mid",
		"Mid-A-Mid",
		"Mid-A-Mid"
	},
	{
		"End-\\x41",
		"End-A",
		"End-A"
	},
	{
		"\\x41-Begin",
		"A-Begin",
		"A-Begin"
	},
	{
		"Mid-\\x41-Mid",
		"Mid-A-Mid",
		"Mid-A-Mid"
	},
	{
		"End-\\7",
		"End-\\a",
		"End-\\a"
	},
	{
		"\\7-Begin",
		"\\a-Begin",
		"\\a-Begin"
	},
	{
		"Mid-\\7-Mid",
		"Mid-\\a-Mid",
		"Mid-\\a-Mid"
	},
	{
		"End-[",
		"End-[",
		"End-?\?("
	},
	{
		"[-Begin",
		"[-Begin",
		"?\?(-Begin"
	},
	{
		"Mid-[-Mid",
		"Mid-[-Mid",
		"Mid-?\?(-Mid"
	},
	{
		"Ends in a back-slash \\",
		"Ends in a back-slash \\\\",
		"Ends in a back-slash \?\?/"
	},
	{
		"BigUChar=\xff",
		"BigUChar=\\xff",
		"BigUChar=\\xff"
	},
	{
		":\"\\\\",
		":\\\"\\\\",
		":\\\"\?\?/"
	},
	{
		":\"\\\\\a\b\f\n\r\t\v",
		":\\\"\\\\\\a\\b\\f\\n\\r\\t\\v",
		":\\\"?\?/\\a\\b\\f\\n\\r\\t\\v"
	},
	{
		":\"\\\\\a\b\f\n\r\t\v\?",
		":\\\"\\\\\\a\\b\\f\\n\\r\\t\\v?",
		":\\\"?\?/\\a\\b\\f\\n\\r\\t\\v\\?"
	},
	{
/*		 01  2345678  9 */
		": \\? ---> \\?",
		": ? ---> ?",
		": \\? ---> \\?"
	},
	{
		"Ends in a back-slash \\",
		"Ends in a back-slash \\\\",
		"Ends in a back-slash \?\?/"
	},
	{
		"Ends in an octal value \\101",
		"Ends in an octal value A",
		"Ends in an octal value A"
	},
	{
		"Ends in a hexadecimal value \\x41",
		"Ends in a hexadecimal value A",
		"Ends in a hexadecimal value A"
	},
	{
		"Also ends in a hexadecimal value \\xff",
		"Also ends in a hexadecimal value \\xff",
		"Also ends in a hexadecimal value \\xff"
	},
	{
/*		 01234567890123456789012 */
		"This is a simple test.",
		"This is a simple test.",
		"This is a simple test."
	},
	{
/*		 012345678901234567890123  456789012345678901234567890123 */
		"This has an embedded tab\\tin the middle of the string.",
		"This has an embedded tab\\tin the middle of the string.",
		"This has an embedded tab\\tin the middle of the string."
	},
	{
/*		 01234567890123456789012345    6    7    8901234  56789012 */
		"This has octal sequences: \\101\\102\\103 ---> \\8	(tab)",
		"This has octal sequences: ABC ---> 8\\t(tab)",
		"This has octal sequences: ABC ---> 8\\t(tab)"
	},
	{
/*		 01234567890123456789012345678901    2    3    4567890    1   23456789 */
		"This has hexadecimal sequences: \\x41\\x42\\x43 ---> \\x4a\\x9(tab)",
		"This has hexadecimal sequences: ABC ---> J\\t(tab)",
		"This has hexadecimal sequences: ABC ---> J\\t(tab)"
	},
	{
/*		 012345678901234567890123456789012345678  9012345  6 */
		"This does not have trigraph sequences: \\? ---> \\?",
		"This does not have trigraph sequences: ? ---> ?",
		"This does not have trigraph sequences: \\? ---> \\?"
	},
	{
/*		 01234567890123456789012345678  9012345  67 */
		"This has trigraph sequences: ?\?( ---> ?\?)",
		"This has trigraph sequences: ?\?( ---> ?\?)",
		"This has trigraph sequences: ?\?( ---> ?\?)"
	}
};

static const unsigned int  TEST_Count =
	sizeof(TEST_List) / sizeof(TEST_List[0]);

int main()
{
	int            return_code = 0;
	unsigned int   count_1;
	unsigned int   count_2;
	unsigned int   result_length_1;
	unsigned int   result_length_2;
	unsigned int   result_length_3;
	char           buffer_1[1024];
	char           buffer_2[1024];

	STR_EMIT_CharLine('=', 78, NULL, NULL);
	STR_EMIT_CharLine('=', 78, NULL, NULL);

	fprintf(stderr, "Test routine for 'mem2cstr()'\n");
	fprintf(stderr, "---- ------- --- ------------\n");

	STR_EMIT_CharLine('=', 78, NULL, NULL);
	printf("Test One: Built-In Test\n");
	for (count_1 = 0; count_1 < TEST_Count; count_1++) {
		for (count_2 = 0; count_2 < 2; count_2++) {
			result_length_1 = strlen(TEST_List[count_1][count_2 + 1]);
			cstr2mem(TEST_List[count_1][0],
				(count_2) ? 0 : STR_CSTR2MEM_NO_TRIGRAPHS, &result_length_2,
				buffer_1);
			result_length_3 = strlen(mem2cstr(result_length_2, buffer_1,
				(count_2) ? 0 : STR_MEM2CSTR_NO_TRIGRAPHS, buffer_2));
			if ((result_length_1 != result_length_3) ||
				memcmp(TEST_List[count_1][count_2 + 1], buffer_2,
					result_length_1 + 1)) {
				STR_EMIT_CharLine('-', 78, NULL, NULL);
				printf("ERROR IN TEST: cstr2mem ---> mem2cstr\n");
				STR_EMIT_CharLine('-', 78, NULL, NULL);
				printf("%05u:%05u:Original String:[%s] = %u\n",
					count_1, count_2, TEST_List[count_1][0],
					result_length_1);
				printf("           :Compare String :[%s] = %u\n",
					TEST_List[count_1][count_2 + 1],
					((unsigned int) strlen(TEST_List[count_1][count_2 + 1])));
				printf("           :Changed String :[%s] = %u\n",
					buffer_2, result_length_3);
				return_code = -1;
			}
			result_length_3 = mem2cstr_length(result_length_2, buffer_1,
				(count_2) ? 0 : STR_MEM2CSTR_NO_TRIGRAPHS);
			if (result_length_1 != result_length_3) {
				STR_EMIT_CharLine('-', 78, NULL, NULL);
				printf("ERROR IN TEST: cstr2mem ---> mem2cstr_length\n");
				STR_EMIT_CharLine('-', 78, NULL, NULL);
				printf("%05u:%05u:Original String:[%s] = %u\n",
					count_1, count_2, TEST_List[count_1][0],
					result_length_1);
				printf("           :Compare String :[%s] = %u\n",
					TEST_List[count_1][count_2 + 1],
					((unsigned int) strlen(TEST_List[count_1][count_2 + 1])));
				printf("           :Changed String :[%s] = %u\n",
					buffer_2, result_length_3);
				return_code = -1;
			}
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

