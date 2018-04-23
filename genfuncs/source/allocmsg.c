/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	GENFUNCS General Functions Library Source Module								*/
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

#include <string.h>

#include "genfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	GEN_AllocMsgItem

	SYNOPSIS		:	return_ptr = GEN_AllocMsgItem(size, buffer, in_format, ...);

						char         *return_ptr;

						unsigned int  size;

						char         *buffer;

						const char   *in_format;

						...

	DESCRIPTION	:	Constructs an error message describing a memory allocation
						error for a scalar.

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

						(-) Following the string constructed using ``in_format``,
						this function uses ``size`` to construct a string
						describing the size of the failed allocation attempt.

   RETURNS     :  Returns the ``buffer`` parameter.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	GEN_AllocMsgList
						GEN_AllocMsgPtrList

	EXAMPLES		:	If this function is invoked as follows:

{|@|}GEN_AllocMsgItem(100, error_text, "%s initialization memory",
	"Unable to allocate");

						Printing the contents of ``error_text`` upon return yields:

<|@|>Unable to allocate initialization memory --- 100 bytes required.

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2018 Michael L. Brock

	OUTPUT INDEX:	GEN_AllocMsgItem
						Error Description Functions:GEN_AllocMsgItem
						GENFUNCS:Functions:GEN_AllocMsgItem
						GENFUNCS:Error Description Functions:GEN_AllocMsgItem
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_AllocMsgItem

	PUBLISH NAME:	GEN_AllocMsgItem

	ENTRY CLASS	:	Error Description Functions

EOH */
/*	***********************************************************************	*/
/*VARARGS2*/
#ifndef NO_STDARGS
char *GEN_AllocMsgItem(unsigned int size, char *buffer,
	const char *in_format, ...)
#else
char *GEN_AllocMsgItem(size, buffer, in_format, va_list)
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

	vsprintf(buffer, in_format, argument_ptr);
	va_end(argument_ptr);

	sprintf(buffer + strlen(buffer), " --- %u bytes required.", size);

	return(buffer);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	GEN_AllocMsgList

	SYNOPSIS		:	return_ptr = GEN_AllocMsgList(element_count, element_size,
							buffer, in_format, ...);

						char         *return_ptr;

						unsigned int  element_count;

						unsigned int  element_size;

						char         *buffer;

						const char   *in_format;

						...

	DESCRIPTION	:	Constructs an error message describing a memory allocation
						error for an array.

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

						(-) Following the string constructed using ``in_format``,
						this function uses ``element_count`` and ``element_size``
						to construct a string describing the size of the failed
						allocation attempt.

   RETURNS     :  Returns the ``buffer`` parameter.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	GEN_AllocMsgItem
						GEN_AllocMsgPtrList

	EXAMPLES		:	If this function is invoked as follows:

{|@|}GEN_AllocMsgList(10, 35, error_text, "%s the storage array",
	"Unable to allocate");

						Printing the contents of ``error_text`` upon return yields:

<|@|>Unable to allocate the storage array --- 10 elements * 35 size = 350
bytes required.

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2018 Michael L. Brock

	OUTPUT INDEX:	GEN_AllocMsgList
						Error Description Functions:GEN_AllocMsgList
						GENFUNCS:Functions:GEN_AllocMsgList
						GENFUNCS:Error Description Functions:GEN_AllocMsgList
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_AllocMsgList

	PUBLISH NAME:	GEN_AllocMsgList

	ENTRY CLASS	:	Error Description Functions

EOH */
/*	***********************************************************************	*/
/*VARARGS2*/
#ifndef NO_STDARGS
char *GEN_AllocMsgList(unsigned int element_count, unsigned int element_size,
	char *buffer, const char *in_format, ...)
#else
char *GEN_AllocMsgList(element_count, element_size, buffer, in_format,
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

	vsprintf(buffer, in_format, argument_ptr);
	va_end(argument_ptr);

	sprintf(buffer + strlen(buffer),
		" --- %u elements * %u size = %u bytes required.",
		element_count, element_size, element_count * element_size);

	return(buffer);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	GEN_AllocMsgPtrList

	SYNOPSIS		:	return_ptr = GEN_AllocMsgPtrList(element_count, total_size,
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

						(-) Following the string constructed using ``in_format``,
						this function uses ``element_count``, ``total_size``,
						and the size of a ``void *`` to construct a string
						describing the size of the failed allocation attempt.

   RETURNS     :  Returns the ``buffer`` parameter.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	GEN_AllocMsgItem
						GEN_AllocMsgList

	EXAMPLES		:	If this function is invoked as follows:

{|@|}GEN_AllocMsgPtrList(10, 1024, error_text, "%s the string list",
	"Unable to allocate");

						Printing the contents of ``error_text`` upon return yields
						(where ``sizeof(void *)`` = ''4''):

<|@|>Unable to allocate the string list --- (10 pointer elements * 4
(sizeof(void *))) + 1024 memory pointed to = 40 + 1024 = 1064 bytes required.

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2018 Michael L. Brock

	OUTPUT INDEX:	GEN_AllocMsgPtrList
						Error Description Functions:GEN_AllocMsgPtrList
						GENFUNCS:Functions:GEN_AllocMsgPtrList
						GENFUNCS:Error Description Functions:GEN_AllocMsgPtrList
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_AllocMsgPtrList

	PUBLISH NAME:	GEN_AllocMsgPtrList

	ENTRY CLASS	:	Error Description Functions

EOH */
/*	***********************************************************************	*/
/*VARARGS2*/
#ifndef NO_STDARGS
char *GEN_AllocMsgPtrList(unsigned int element_count,
	unsigned int total_size, char *buffer, const char *in_format, ...)
#else
char *GEN_AllocMsgPtrList(element_count, total_size, buffer, in_format,
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

	vsprintf(buffer, in_format, argument_ptr);
	va_end(argument_ptr);

	sprintf(buffer + strlen(buffer),
		" --- (%u %s * %u %s) + %u %s = %u + %u = %u bytes required.",
		element_count, "pointer elements", sizeof(void *), "(sizeof(void *))",
		total_size, "memory pointed to", element_count * sizeof(void *),
		total_size, (element_count * sizeof(void *)) + total_size);

	return(buffer);
}
/*	***********************************************************************	*/

