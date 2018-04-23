/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	STRFUNCS String and Memory Functions Library Module							*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Constructs a memory allocation error message.

	Revision History	:	1995-05-01 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*    Include necessary header files . . .                                 */
/*	***********************************************************************	*/

#include <stdio.h>
#include <string.h>

#include "strfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	STR_AllocMsgItem

	SYNOPSIS		:	return_ptr = STR_AllocMsgItem(size, buffer, in_format, ...);

						char         *return_ptr;

						unsigned int  size;

						char         *buffer;

						const char   *in_format;

						...

	DESCRIPTION	:	Constructs an error message describing a memory allocation
						error for a scalar.

						Following the string constructed using the ``in_format``
						parameter, this function uses the ``size`` parameter to
						construct a string describing the size of the failed
						allocation attempt.

	PARAMETERS  :  Parameters to this function are as follows:

						(.) ``size`` is the amount of memory which could not be
						allocated.

						(.) ``buffer`` is the string in which the error message
						constructed is to be stored.

						(.) ``in_format`` is a ``sprintf``-type format to be used
						in formatting the subsequent function arguments represented
						by ``...``.

						(.) ``...`` represents a variable argument list to be used,
						in conjunction with the ``in_format`` parameter, to format
						the error message.

	RETURNS     :  Returns the ``buffer`` parameter.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	STR_AllocMsgItemVA
						STR_AllocMsgList
						STR_AllocMsgPtrList

	EXAMPLES		:	If this function is invoked as follows:

{|@|}STR_AllocMsgItem(100, error_text, "%s initialization memory",
	"Unable to allocate");

						Printing the contents of ``error_text`` upon return yields:

<|@|>Unable to allocate initialization memory --- 100 bytes required.

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2018 Michael L. Brock

	OUTPUT INDEX:	STR_AllocMsgItem
						Error Description Functions:STR_AllocMsgItem
						STRFUNCS:Functions:STR_AllocMsgItem
						STRFUNCS:Error Description Functions:STR_AllocMsgItem
						String Functions:See STRFUNCS

	PUBLISH XREF:	STR_AllocMsgItem

	PUBLISH NAME:	STR_AllocMsgItem

	ENTRY CLASS	:	Error Description Functions

EOH */
/*	***********************************************************************	*/
/*VARARGS2*/
#ifndef NO_STDARGS
char *STR_AllocMsgItem(unsigned int size, char *buffer,
	const char *in_format, ...)
#else
char *STR_AllocMsgItem(size, buffer, in_format, va_list)
unsigned int  size;
char         *buffer;
const char   *in_format;
va_dcl
#endif /* #ifndef NO_STDARGS */
{
	va_list argument_ptr;

#ifndef NO_STDARGS
	va_start(argument_ptr, in_format);
#else
	va_start(argument_ptr);
#endif /* #ifndef NO_STDARGS */

	STR_AllocMsgItemVA(size, buffer, in_format, argument_ptr);

	va_end(argument_ptr);

	return(buffer);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	STR_AllocMsgList

	SYNOPSIS		:	return_ptr = STR_AllocMsgList(element_count, element_size,
							buffer, in_format, ...);

						char         *return_ptr;

						unsigned int  element_count;

						unsigned int  element_size;

						char         *buffer;

						const char   *in_format;

						...

	DESCRIPTION	:	Constructs an error message describing a memory allocation
						error for an array.

						Following the string constructed using the ``in_format``
						parameter, this function uses the ``element_count`` and
						``element_size`` parameters to construct a string
						describing the size of the failed allocation attempt.

	PARAMETERS  :  Parameters to this function are as follows:

						(.) ``element_count`` is the number of elements in the
						array for which the allocation attempt failed.

						(.) ``element_size`` is the size of the individual array
						elements for which the allocation attempt failed.

						(.) ``buffer`` is the string in which the error message
						constructed is to be stored.

						(.) ``in_format`` is a ``sprintf``-type format to be used
						in formatting the subsequent function arguments represented
						by ``...``.

						(.) ``...`` represents a variable argument list to be used,
						in conjunction with the ``in_format`` parameter, to format
						the error message.

	RETURNS     :  Returns the ``buffer`` parameter.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	STR_AllocMsgListVA
						STR_AllocMsgItem
						STR_AllocMsgPtrList

	EXAMPLES		:	If this function is invoked as follows:

{|@|}STR_AllocMsgList(10, 35, error_text, "%s the storage array",
	"Unable to allocate");

						Printing the contents of ``error_text`` upon return yields:

<|@|>Unable to allocate the storage array --- 10 elements * 35 size = 350
bytes required.

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2018 Michael L. Brock

	OUTPUT INDEX:	STR_AllocMsgList
						Error Description Functions:STR_AllocMsgList
						STRFUNCS:Functions:STR_AllocMsgList
						STRFUNCS:Error Description Functions:STR_AllocMsgList
						String Functions:See STRFUNCS

	PUBLISH XREF:	STR_AllocMsgList

	PUBLISH NAME:	STR_AllocMsgList

	ENTRY CLASS	:	Error Description Functions

EOH */
/*	***********************************************************************	*/
/*VARARGS2*/
#ifndef NO_STDARGS
char *STR_AllocMsgList(unsigned int element_count, unsigned int element_size,
	char *buffer, const char *in_format, ...)
#else
char *STR_AllocMsgList(element_count, element_size, buffer, in_format,
	va_list)
unsigned int  element_count;
unsigned int  element_size;
char         *buffer;
const char   *in_format;
va_dcl
#endif /* #ifndef NO_STDARGS */
{
	va_list argument_ptr;

#ifndef NO_STDARGS
	va_start(argument_ptr, in_format);
#else
	va_start(argument_ptr);
#endif /* #ifndef NO_STDARGS */

	STR_AllocMsgListVA(element_count, element_size, buffer, in_format,
		argument_ptr);

	va_end(argument_ptr);

	return(buffer);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	STR_AllocMsgPtrList

	SYNOPSIS		:	return_ptr = STR_AllocMsgPtrList(element_count, total_size,
							buffer, in_format, ...);

						char         *return_ptr;

						unsigned int  element_count;

						unsigned int  total_size;

						char         *buffer;

						const char   *in_format;

						...

	DESCRIPTION	:	Constructs an error message describing a memory allocation
						error for an array of pointers to data, such as an array
						of pointers to strings.

						Following the string constructed using the ``in_format``
						parameter, this function uses the ``element_count``,
						``total_size`` parameters, and the size of a ``void *`` to
						construct a string describing the size of the failed
						allocation attempt.

	PARAMETERS  :  Parameters to this function are as follows:

						(.) ``element_count`` is the number of elements in the
						array for which the allocation attempt failed.

						(.) ``total_size`` is the total size of all elements in the
						array for which the allocation attempt failed.

						(.) ``buffer`` is the string in which the error message
						constructed is to be stored.

						(.) ``in_format`` is a ``sprintf``-type format to be used
						in formatting the subsequent function arguments represented
						by ``...``.

						(.) ``...`` represents a variable argument list to be used,
						in conjunction with the ``in_format`` parameter, to format
						the error message.

	RETURNS     :  Returns the ``buffer`` parameter.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	STR_AllocMsgPtrList
						STR_AllocMsgItem
						STR_AllocMsgList

	EXAMPLES		:	If this function is invoked as follows:

{|@|}STR_AllocMsgPtrList(10, 1024, error_text, "%s the string list",
	"Unable to allocate");

						Printing the contents of ``error_text`` upon return yields
						(where ``sizeof(void *)`` = ''4''):

<|@|>Unable to allocate the string list --- (10 pointer elements * 4
(sizeof(void *))) + 1024 memory pointed to = 40 + 1024 = 1064 bytes required.

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2018 Michael L. Brock

	OUTPUT INDEX:	STR_AllocMsgPtrList
						Error Description Functions:STR_AllocMsgPtrList
						STRFUNCS:Functions:STR_AllocMsgPtrList
						STRFUNCS:Error Description Functions:STR_AllocMsgPtrList
						String Functions:See STRFUNCS

	PUBLISH XREF:	STR_AllocMsgPtrList

	PUBLISH NAME:	STR_AllocMsgPtrList

	ENTRY CLASS	:	Error Description Functions

EOH */
/*	***********************************************************************	*/
/*VARARGS2*/
#ifndef NO_STDARGS
char *STR_AllocMsgPtrList(unsigned int element_count,
	unsigned int total_size, char *buffer, const char *in_format, ...)
#else
char *STR_AllocMsgPtrList(element_count, total_size, buffer, in_format,
	va_list)
unsigned int  element_count;
unsigned int  total_size;
char         *buffer;
const char   *in_format;
va_dcl
#endif /* #ifndef NO_STDARGS */
{
	va_list argument_ptr;

#ifndef NO_STDARGS
	va_start(argument_ptr, in_format);
#else
	va_start(argument_ptr);
#endif /* #ifndef NO_STDARGS */

	STR_AllocMsgPtrListVA(element_count, total_size, buffer, in_format,
		argument_ptr);

	va_end(argument_ptr);

	return(buffer);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	STR_AllocMsgItemVA

	SYNOPSIS		:	return_ptr = STR_AllocMsgItemVA(size, buffer, arg_list);

						char         *return_ptr;

						unsigned int  size;

						char         *buffer;

						va_list       arg_list;

	DESCRIPTION	:	Constructs an error message describing a memory allocation
						error for a scalar.

						Following the string constructed using the ``in_format``
						parameter, this function uses the ``size`` parameter to
						construct a string describing the size of the failed
						allocation attempt.

	PARAMETERS  :  Parameters to this function are as follows:

						(.) ``size`` is the amount of memory which could not be
						allocated.

						(.) ``buffer`` is the string in which the error message
						constructed is to be stored.

						(.) ``in_format`` is a ``sprintf``-type format to be used
						in formatting the subsequent function arguments represented
						by the ``arg_list`` parameter.

						(.) ``arg_list`` contains subsequent arguments to this
						function. They will be output in accordance with the
						specifications embedded in the ``in_format`` parameter.

	RETURNS     :  Returns the ``buffer`` parameter.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	STR_AllocMsgItem
						STR_AllocMsgListVA
						STR_AllocMsgPtrListVA

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2018 Michael L. Brock

	OUTPUT INDEX:	STR_AllocMsgItemVA
						Error Description Functions:STR_AllocMsgItemVA
						STRFUNCS:Functions:STR_AllocMsgItemVA
						STRFUNCS:Error Description Functions:STR_AllocMsgItemVA
						String Functions:See STRFUNCS

	PUBLISH XREF:	STR_AllocMsgItemVA

	PUBLISH NAME:	STR_AllocMsgItemVA

	ENTRY CLASS	:	Error Description Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *STR_AllocMsgItemVA(unsigned int size, char *buffer,
	const char *in_format, va_list arg_list)
#else
char *STR_AllocMsgItemVA(size, buffer, in_format, arg_list)
unsigned int  size;
char         *buffer;
const char   *in_format;
va_list       arg_list;
#endif /* #ifndef NARGS */
{
	vsprintf(buffer, in_format, arg_list);
	sprintf(buffer + strlen(buffer), " --- %u bytes required.", size);

	return(buffer);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	STR_AllocMsgListVA

	SYNOPSIS		:	return_ptr = STR_AllocMsgListVA(element_count, element_size,
							buffer, in_format, arg_list);

						char         *return_ptr;

						unsigned int  element_count;

						unsigned int  element_size;

						char         *buffer;

						const char   *in_format;

						va_list       arg_list;

	DESCRIPTION	:	Constructs an error message describing a memory allocation
						error for an array.

						Following the string constructed using the ``in_format``
						parameter, this function uses the ``element_count`` and
						``element_size`` parameters to construct a string
						describing the size of the failed allocation attempt.

	PARAMETERS  :  Parameters to this function are as follows:

						(.) ``element_count`` is the number of elements in the
						array for which the allocation attempt failed.

						(.) ``element_size`` is the size of the individual array
						elements for which the allocation attempt failed.

						(.) ``buffer`` is the string in which the error message
						constructed is to be stored.

						(.) ``in_format`` is a ``sprintf``-type format to be used
						in formatting the subsequent function arguments represented
						by the ``arg_list`` parameter.

						(.) ``arg_list`` contains subsequent arguments to this
						function. They will be output in accordance with the
						specifications embedded in the ``in_format`` parameter.

	RETURNS     :  Returns the ``buffer`` parameter.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	STR_AllocMsgList
						STR_AllocMsgItemVA
						STR_AllocMsgPtrListVA

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2018 Michael L. Brock

	OUTPUT INDEX:	STR_AllocMsgListVA
						Error Description Functions:STR_AllocMsgListVA
						STRFUNCS:Functions:STR_AllocMsgListVA
						STRFUNCS:Error Description Functions:STR_AllocMsgListVA
						String Functions:See STRFUNCS

	PUBLISH XREF:	STR_AllocMsgListVA

	PUBLISH NAME:	STR_AllocMsgListVA

	ENTRY CLASS	:	Error Description Functions

EOH */
/*	***********************************************************************	*/
/*VARARGS2*/
#ifndef NARGS
char *STR_AllocMsgListVA(unsigned int element_count, unsigned int element_size,
	char *buffer, const char *in_format, va_list arg_list)
#else
char *STR_AllocMsgListVA(element_count, element_size, buffer, in_format,
	arg_list)
unsigned int  element_count;
unsigned int  element_size;
char         *buffer;
const char   *in_format;
va_list       arg_list;
#endif /* #ifndef NARGS */
{
	vsprintf(buffer, in_format, arg_list);
	sprintf(buffer + strlen(buffer),
		" --- %u elements * %u size = %u bytes required.",
		element_count, element_size, element_count * element_size);

	return(buffer);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	STR_AllocMsgPtrListVA

	SYNOPSIS		:	return_ptr = STR_AllocMsgPtrListVA(element_count, total_size,
							buffer, in_format, arg_list);

						char         *return_ptr;

						unsigned int  element_count;

						unsigned int  total_size;

						char         *buffer;

						const char   *in_format;

						va_list       arg_list;

	DESCRIPTION	:	Constructs an error message describing a memory allocation
						error for an array of pointers to data, such as an array
						of pointers to strings.

						Following the string constructed using the ``in_format``
						parameter, this function uses the ``element_count``,
						``total_size`` parameters, and the size of a ``void *`` to
						construct a string describing the size of the failed
						allocation attempt.

	PARAMETERS  :  Parameters to this function are as follows:

						(.) ``element_count`` is the number of elements in the
						array for which the allocation attempt failed.

						(.) ``total_size`` is the total size of all elements in the
						array for which the allocation attempt failed.

						(.) ``buffer`` is the string in which the error message
						constructed is to be stored.

						(.) ``in_format`` is a ``sprintf``-type format to be used
						in formatting the subsequent function arguments represented
						by the ``arg_list`` parameter.

						(.) ``arg_list`` contains subsequent arguments to this
						function. They will be output in accordance with the
						specifications embedded in the ``in_format`` parameter.

	RETURNS     :  Returns the ``buffer`` parameter.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	STR_AllocMsgPtrList
						STR_AllocMsgItemVA
						STR_AllocMsgListVA

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2018 Michael L. Brock

	OUTPUT INDEX:	STR_AllocMsgPtrListVA
						Error Description Functions:STR_AllocMsgPtrListVA
						STRFUNCS:Functions:STR_AllocMsgPtrListVA
						STRFUNCS:Error Description Functions:STR_AllocMsgPtrListVA
						String Functions:See STRFUNCS

	PUBLISH XREF:	STR_AllocMsgPtrListVA

	PUBLISH NAME:	STR_AllocMsgPtrListVA

	ENTRY CLASS	:	Error Description Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *STR_AllocMsgPtrListVA(unsigned int element_count, unsigned int total_size,
	char *buffer, const char *in_format, va_list arg_list)
#else
char *STR_AllocMsgPtrListVA(element_count, total_size, buffer, in_format,
	arg_list)
unsigned int  element_count;
unsigned int  total_size;
char         *buffer;
const char   *in_format;
va_list       arg_list;
#endif /* #ifndef NARGS */
{
	vsprintf(buffer, in_format, arg_list);
	sprintf(buffer + strlen(buffer),
		" --- (%u %s * %u %s) + %u %s = %u + %u = %u bytes required.",
		element_count, "pointer elements", sizeof(void *), "(sizeof(void *))",
		total_size, "memory pointed to", element_count * sizeof(void *),
		total_size, (element_count * sizeof(void *)) + total_size);

	return(buffer);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

COMPAT_FN_DECL(int main, (void));

int main()
{
	char error_text[STRFUNCS_MAX_ERROR_TEXT];

	fprintf(stderr, "Test harness for function 'STR_AllocMsgItem()'\n");
	fprintf(stderr, "                          'STR_AllocMsgList()'\n");
	fprintf(stderr, "                          'STR_AllocMsgPtrList()'\n");
	fprintf(stderr, "---- ------- --- -------- -----------------------\n\n");

	printf("No arguments test:\n");
	STR_EMIT_CharLine('-', 78, NULL, NULL);
	printf("%s\n", STR_AllocMsgItem(12345, error_text,
		"STR_AllocMsgItem()   : No argument"));
	printf("%s\n", STR_AllocMsgList(12345, 1024, error_text,
		"STR_AllocMsgList()   : No argument"));
	printf("%s\n", STR_AllocMsgPtrList(12345, 100000, error_text,
		"STR_AllocMsgPtrList(): No argument"));

	printf("With arguments test:\n");
	STR_EMIT_CharLine('-', 78, NULL, NULL);
	printf("%s\n", STR_AllocMsgItem(12345, error_text,
		"STR_AllocMsgItem()   : %s", "With argument"));
	printf("%s\n", STR_AllocMsgList(12345, 1024, error_text,
		"STR_AllocMsgList()   : %s", "With argument"));
	printf("%s\n", STR_AllocMsgPtrList(12345, 100000, error_text,
		"STR_AllocMsgPtrList(): %s", "With argument"));
	STR_EMIT_CharLine('-', 78, NULL, NULL);
	printf("\n");

	return(STRFUNCS_SUCCESS);
}

#endif /* #ifdef TEST_MAIN */

