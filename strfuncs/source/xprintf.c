/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	STRFUNCS String and Memory Functions Library Module							*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Extended printf-like functionality.

	Revision History	:	2002-02-10 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 2002 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Include necessary header files . . .												*/
/*	***********************************************************************	*/

#include <mbcompat.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strfunci.h"

/*	***********************************************************************	*/

/*
	CODE NOTE: To be moved into 'strfuncs.h'.
*/
/*	***********************************************************************	*/
#ifdef __GNUC__
COMPAT_FN_DECL(unsigned int STR_XPrintf_GetLength,
	(const char *in_format, ...)
		__attribute__ ((format (printf, 1, 2))));
COMPAT_FN_DECL(unsigned int STR_XPrintf_GetLengthAlloc,
	(const char *in_format, ...)
		__attribute__ ((format (printf, 1, 2))));
COMPAT_FN_DECL(unsigned int STR_XPrintf_GetLengthBasic,
	(unsigned int *extra_length, const char *in_format, ...)
		__attribute__ ((format (printf, 1, 2))));
COMPAT_FN_DECL(int          STR_XPrintf_Alloc,
	(char **buffer_ptr, const char *in_format, ...)
		__attribute__ ((format (printf, 2, 3))));
COMPAT_FN_DECL(int          STR_XPrintf_Realloc,
	(unsigned int *buffer_length, char **buffer_ptr, const char *in_format, ...)
		 __attribute__ ((format (printf, 3, 4))));
#else
# ifndef NO_STDARGS
COMPAT_FN_DECL(unsigned int STR_XPrintf_GetLength,
	(const char *in_format, ...));
COMPAT_FN_DECL(unsigned int STR_XPrintf_GetLengthAlloc,
	(const char *in_format, ...));
COMPAT_FN_DECL(unsigned int STR_XPrintf_GetLengthBasic,
	(unsigned int *extra_length, const char *in_format, ...));
COMPAT_FN_DECL(int          STR_XPrintf_Alloc,
	(char **buffer_ptr, const char *in_format, ...));
COMPAT_FN_DECL(int          STR_XPrintf_Realloc,
	(unsigned int *buffer_length, char **buffer_ptr,
	const char *in_format, ...));
# else
COMPAT_FN_DECL(unsigned int STR_XPrintf_GetLength,
	(const char *in_format, va_alist));
COMPAT_FN_DECL(unsigned int STR_XPrintf_GetLengthAlloc,
	(const char *in_format, va_alist));
COMPAT_FN_DECL(unsigned int STR_XPrintf_GetLengthBasic,
	(unsigned int *extra_length, const char *in_format, va_alist));
COMPAT_FN_DECL(int          STR_XPrintf_Alloc,
	(char **buffer_ptr, const char *in_format, va_alist));
COMPAT_FN_DECL(int          STR_XPrintf_Realloc,
	(unsigned int *buffer_length, char **buffer_ptr,
	const char *in_format, va_alist));
# endif /* # ifndef NO_STDARGS */
#endif /* #ifdef __GNUC__ */
COMPAT_FN_DECL(unsigned int STR_XPrintf_GetLengthVA,
	(const char *in_format, va_list arg_list));
COMPAT_FN_DECL(unsigned int STR_XPrintf_GetLengthAllocVA,
	(const char *in_format, va_list arg_list));
COMPAT_FN_DECL(unsigned int STR_XPrintf_GetLengthBasicVA,
	(unsigned int *extra_length, const char *in_format, va_list arg_list));
COMPAT_FN_DECL(int          STR_XPrintf_AllocVA,
	(char **buffer_ptr, const char *in_format, va_list arg_list));
COMPAT_FN_DECL(int          STR_XPrintf_ReallocVA,
	(unsigned int *buffer_length, char **buffer_ptr, const char *in_format,
	va_list arg_list));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#define STR_XPRINTF_MIN_C_STD_MAX		509
#define STR_XPRINTF_MAX_WIDTH				1023
#define STR_XPRINTF_MAX_PRECISION		1023
#define STR_XPRINTF_MAX_FORMAT_SPEC		\
	(32 + (STR_VAL2STR_MAX_LEN * 2) + 1 + (32 * 2))

typedef union {
	unsigned char       uchar;
	signed int          sint;
	unsigned int        uint;
	signed long         slong;
	unsigned long       ulong;
	double              ddouble;
	long double         ldouble;
	const char         *char_ptr;
	const void         *void_ptr;
#ifdef _Windows
	signed __int64      slonglong;
	unsigned __int64    ulonglong;
#else
	signed long long    slonglong;
	unsigned long long  ulonglong;
#endif /* #ifdef _Windows */
} STR_XPRINTF_DATA;

typedef enum {
	STR_XPRINTF_TYPE_uchar,
	STR_XPRINTF_TYPE_sint,
	STR_XPRINTF_TYPE_uint,
	STR_XPRINTF_TYPE_slong,
	STR_XPRINTF_TYPE_ulong,
	STR_XPRINTF_TYPE_ddouble,
	STR_XPRINTF_TYPE_ldouble,
	STR_XPRINTF_TYPE_char_ptr,
	STR_XPRINTF_TYPE_void_ptr,
	STR_XPRINTF_TYPE_slonglong,
	STR_XPRINTF_TYPE_ulonglong
} STR_XPRINTF_TYPE;

typedef struct {
	char             *spec_type;
	unsigned int      spec_type_length;
	STR_XPRINTF_TYPE  base_type;
} STR_XPRINTF_SPEC;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static const STR_XPRINTF_SPEC STR_XprintfSpecList[] = {
	{	"c",		1,	STR_XPRINTF_TYPE_uchar		},
	{	"d",		1,	STR_XPRINTF_TYPE_sint		},
	{	"hd",		2,	STR_XPRINTF_TYPE_sint		},
	{	"ld",		2,	STR_XPRINTF_TYPE_slong		},
	{	"e",		1,	STR_XPRINTF_TYPE_ddouble	},
	{	"Le",		2,	STR_XPRINTF_TYPE_ldouble	},
	{	"E",		1,	STR_XPRINTF_TYPE_ddouble	},
	{	"LE",		2,	STR_XPRINTF_TYPE_ldouble	},
	{	"f",		1,	STR_XPRINTF_TYPE_ddouble	},
	{	"Lf",		2,	STR_XPRINTF_TYPE_ldouble	},
	{	"g",		1,	STR_XPRINTF_TYPE_ddouble	},
	{	"Lg",		2,	STR_XPRINTF_TYPE_ldouble	},
	{	"G",		1,	STR_XPRINTF_TYPE_ddouble	},
	{	"LG",		2,	STR_XPRINTF_TYPE_ldouble	},
	{	"i",		1,	STR_XPRINTF_TYPE_sint		},
	{	"hi",		2,	STR_XPRINTF_TYPE_sint		},
	{	"li",		2,	STR_XPRINTF_TYPE_slong		},
	{	"o",		1,	STR_XPRINTF_TYPE_uint		},
	{	"ho",		2,	STR_XPRINTF_TYPE_uint		},
	{	"lo",		2,	STR_XPRINTF_TYPE_ulong		},
	{	"p",		1,	STR_XPRINTF_TYPE_void_ptr	},
	{	"s",		1,	STR_XPRINTF_TYPE_char_ptr	},
	{	"u",		1,	STR_XPRINTF_TYPE_uint		},
	{	"hu",		2,	STR_XPRINTF_TYPE_uint		},
	{	"lu",		2,	STR_XPRINTF_TYPE_ulong		},
	{	"x",		1,	STR_XPRINTF_TYPE_uint		},
	{	"hx",		2,	STR_XPRINTF_TYPE_uint		},
	{	"lx",		2,	STR_XPRINTF_TYPE_ulong		},
	{	"X",		1,	STR_XPRINTF_TYPE_uint		},
	{	"hX",		2,	STR_XPRINTF_TYPE_uint		},
	{	"lX",		2,	STR_XPRINTF_TYPE_ulong		}
#ifdef _Windows
	,
	{	"C",		1,	STR_XPRINTF_TYPE_uchar		},
	{	"S",		1,	STR_XPRINTF_TYPE_char_ptr	},
	{	"hc",		2,	STR_XPRINTF_TYPE_uchar		},
	{	"hC",		2,	STR_XPRINTF_TYPE_uchar		},
	{	"lc",		2,	STR_XPRINTF_TYPE_uchar		},
	{	"lC",		2,	STR_XPRINTF_TYPE_uchar		},
	{	"hs",		2,	STR_XPRINTF_TYPE_char_ptr	},
	{	"hS",		2,	STR_XPRINTF_TYPE_char_ptr	},
	{	"ls",		2,	STR_XPRINTF_TYPE_char_ptr	},
	{	"LS",		2,	STR_XPRINTF_TYPE_char_ptr	},
	{	"I64d",	4,	STR_XPRINTF_TYPE_slonglong	},
	{	"I64i",	4,	STR_XPRINTF_TYPE_slonglong	},
	{	"I64o",	4,	STR_XPRINTF_TYPE_ulonglong	},
	{	"I64u",	4,	STR_XPRINTF_TYPE_ulonglong	},
	{	"I64x",	4,	STR_XPRINTF_TYPE_ulonglong	},
	{	"I64X",	4,	STR_XPRINTF_TYPE_ulonglong	}
#endif /* #ifdef _Windows */
};
static const unsigned int     STR_XprintfSpecCount  =
	sizeof(STR_XprintfSpecList) / sizeof(STR_XprintfSpecList[0]);
/*	***********************************************************************	*/

COMPAT_FN_DECL_STATIC(const STR_XPRINTF_SPEC *STR_XPrintf_GetSpecPtr,
	(const char *format_end_ptr));

/*	***********************************************************************	*/
/*VARARGS2*/
#ifndef NO_STDARGS
unsigned int STR_XPrintf_GetLength(const char *in_format, ...)
#else
unsigned int STR_XPrintf_GetLength(in_format, va_list)
const char *in_format;
va_dcl
#endif /* #ifndef NO_STDARGS */
{
	unsigned int out_length;
	va_list      arg_list;

#ifndef NO_STDARGS
	va_start(arg_list, in_format);
#else
	va_start(arg_list);
#endif /* #ifndef NO_STDARGS */

	out_length = STR_XPrintf_GetLengthVA(in_format, arg_list);

	va_end(arg_list);

	return(out_length);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*VARARGS2*/
#ifndef NO_STDARGS
unsigned int STR_XPrintf_GetLengthVA(const char *in_format, va_list arg_list)
#else
unsigned int STR_XPrintf_GetLengthVA(in_format, arg_list)
const char *in_format;
va_list     arg_list;
#endif /* #ifndef NO_STDARGS */
{
	return(STR_XPrintf_GetLengthBasicVA(NULL, in_format, arg_list));
}
/*	***********************************************************************	*/

/*
	ADF NOTE: If you are intending to allocate memory for a ``sprintf()``
	(or ``vsprintf()``) string, use this function to determine the total
	length required. The return value includes the space necessary for the
	the terminating ASCII NUL character (``\0``).

	More importantly, it also includes the space used by the local
	implementation beyond specified by the standard --- that is, it handles
	bugs in the local implementation.

	For example, under Microsoft Visual C++ 6.x, ``vsprintf()`` uses an
	extra character for each instance of ''%%'' in a format. Though the
	resulting string is correct. To illustrate:

	char buffer[21 + 1];
	vsprintf(buffer, "%%%s", "Simple string buffer");

	Should require a total of 21 characters for the string, with an additional
	character for the \0.

	The result of calling ``vsprintf()`` will be the following (correct) buffer
	of length 21 (not including the \0):

	%%Simple string buffer

	But BoundsChecker reports that the function temporarily uses 23 characters.
*/
/*	***********************************************************************	*/
/*VARARGS2*/
#ifndef NO_STDARGS
unsigned int STR_XPrintf_GetLengthAlloc(const char *in_format, ...)
#else
unsigned int STR_XPrintf_GetLengthAlloc(in_format, va_list)
const char *in_format;
va_dcl
#endif /* #ifndef NO_STDARGS */
{
	unsigned int out_length;
	va_list      arg_list;

#ifndef NO_STDARGS
	va_start(arg_list, in_format);
#else
	va_start(arg_list);
#endif /* #ifndef NO_STDARGS */

	out_length = STR_XPrintf_GetLengthAllocVA(in_format, arg_list);

	va_end(arg_list);

	return(out_length);
}
/*	***********************************************************************	*/

/*
	ADF NOTE: If you are intending to allocate memory for a ``sprintf()``
	(or ``vsprintf()``) string, use this function to determine the total
	length required. The return value includes the space necessary for the
	the terminating ASCII NUL character (``\0``).

	More importantly, it also includes the space used by the local
	implementation beyond specified by the standard --- that is, it handles
	bugs in the local implementation.

	For example, under Microsoft Visual C++ 6.x, ``vsprintf()`` uses an
	extra character for each instance of ''%%'' in a format. Though the
	resulting string is correct. To illustrate:

	char buffer[21 + 1];
	vsprintf(buffer, "%%%s", "Simple string buffer");

	Should require a total of 21 characters for the string, with an additional
	character for the \0.

	The result of calling ``vsprintf()`` will be the following (correct) buffer
	of length 21 (not including the \0):

	%%Simple string buffer

	But BoundsChecker reports that the function temporarily uses 23 characters.
*/
/*	***********************************************************************	*/
/*VARARGS2*/
#ifndef NO_STDARGS
unsigned int STR_XPrintf_GetLengthAllocVA(const char *in_format,
	va_list arg_list)
#else
unsigned int STR_XPrintf_GetLengthAllocVA(in_format, arg_list)
const char *in_format;
va_list     arg_list;
#endif /* #ifndef NO_STDARGS */
{
	unsigned int extra_length = 0;

	return(STR_XPrintf_GetLengthBasicVA(&extra_length, in_format, arg_list) +
		extra_length);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*VARARGS2*/
#ifndef NO_STDARGS
unsigned int STR_XPrintf_GetLengthBasic(unsigned int *extra_length,
	const char *in_format, ...)
#else
unsigned int STR_XPrintf_GetLengthBasic(extra_length, in_format, va_list)
unsigned int *extra_length;
const char   *in_format;
va_dcl
#endif /* #ifndef NO_STDARGS */
{
	unsigned int out_length;
	va_list      arg_list;

#ifndef NO_STDARGS
	va_start(arg_list, in_format);
#else
	va_start(arg_list);
#endif /* #ifndef NO_STDARGS */

	out_length = STR_XPrintf_GetLengthBasicVA(extra_length, in_format, arg_list);

	va_end(arg_list);

	return(out_length);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*VARARGS2*/
#ifndef NO_STDARGS
unsigned int STR_XPrintf_GetLengthBasicVA(unsigned int *extra_length,
	const char *in_format, va_list arg_list)
#else
unsigned int STR_XPrintf_GetLengthBasicVA(extra_length, in_format, arg_list)
unsigned int *extra_length;
const char   *in_format;
va_list       arg_list;
#endif /* #ifndef NO_STDARGS */
{
	unsigned int            out_length = 0;
	char                    format_char;
	const char             *format_spec_end;
	unsigned int            format_spec_length;
	char                    format_spec[STR_XPRINTF_MAX_FORMAT_SPEC + 1];
	STR_XPRINTF_DATA        arg_data;
	const STR_XPRINTF_SPEC *spec_ptr;
	int                     has_width;
	int                     has_precision;
	unsigned int            this_width;
	unsigned int            this_precision;
	unsigned int            string_length;
	char                    buffer[STR_XPRINTF_MAX_WIDTH + 1 +
										STR_XPRINTF_MAX_PRECISION + 2047 + 1];

	if (extra_length != NULL)
		*extra_length = 1;

	while ((format_char = *in_format) != '\0') {
		++in_format;
		if (format_char == '\\') {
			++out_length;
			if (!(*in_format))
				break;
			++in_format;
		}
		else if (format_char != '%')
			++out_length;
		else if (*in_format == '%') {
			++out_length;
			++in_format;
			if (extra_length != NULL)
				(*extra_length)++;
		}
		else if (*in_format == 'n') {
			arg_data.void_ptr = va_arg(arg_list, const void *);
			++in_format;
		}
		else if ((format_spec_end = str_alpha(in_format, 1)) == NULL) {
			out_length += strlen(in_format) + 1;
			break;
		}
		else if ((spec_ptr = STR_XPrintf_GetSpecPtr(format_spec_end)) == NULL) {
			out_length += ((unsigned int) (format_spec_end - in_format));
			in_format   = format_spec_end;
		}
		else {
			format_spec_end    += spec_ptr->spec_type_length;
			format_spec_length  = ((unsigned int) (format_spec_end - in_format));
			if (format_spec_length >= sizeof(format_spec)) {
				in_format   = format_spec_end;
				out_length += format_spec_length;
				continue;
			}
			has_width      = 0;
			has_precision  = 0;
			this_width     = 0;
			this_precision = 0;
			chrcpy(format_spec, '%');
			while (strchr("-+0 #", *in_format) != NULL)
				chrcat(format_spec, *in_format++);
			if (isdigit(*in_format)) {
				this_width = atoi(in_format);
				in_format  = str_digit(in_format, 0);
				has_width  = 1;
				val2str_uint_cat((this_width <= STR_XPRINTF_MAX_WIDTH) ?
					this_width : STR_XPRINTF_MAX_WIDTH, 10, NULL, format_spec);
			}
			else if (*in_format == '*') {
				++in_format;
				this_width = va_arg(arg_list, unsigned int);
				has_width  = 1;
				val2str_uint_cat((this_width <= STR_XPRINTF_MAX_WIDTH) ?
					this_width : STR_XPRINTF_MAX_WIDTH, 10, NULL, format_spec);
			}
			if (*in_format == '.') {
				++in_format;
				chrcat(format_spec, '.');
				if (isdigit(*in_format)) {
					this_precision = atoi(in_format);
					in_format      = str_digit(in_format, 0);
					has_precision  = 1;
					val2str_uint_cat((this_precision <= STR_XPRINTF_MAX_PRECISION) ?
						this_precision : STR_XPRINTF_MAX_PRECISION, 10, NULL,
						format_spec);
				}
				else if (*in_format == '*') {
					++in_format;
					this_precision = va_arg(arg_list, unsigned int);
					has_precision  = 1;
					val2str_uint_cat((this_precision <= STR_XPRINTF_MAX_PRECISION) ?
						this_precision : STR_XPRINTF_MAX_PRECISION, 10, NULL,
						format_spec);
				}
				else {
					out_length += format_spec_length;
					in_format   = format_spec_end;
					continue;
				}
			}
			if (in_format != (format_spec_end - spec_ptr->spec_type_length)) {
				out_length += format_spec_length;
				in_format   = format_spec_end;
				continue;
			}
			strcat(format_spec, spec_ptr->spec_type);
			in_format = format_spec_end;
			if (spec_ptr->base_type == STR_XPRINTF_TYPE_char_ptr) {
				if (has_width && has_precision)
					out_length += ((this_width >= this_precision) ? this_width :
						this_precision);
				else {
					arg_data.char_ptr = va_arg(arg_list, const char *);
					string_length     = strlen(arg_data.char_ptr);
					if (has_width)
						out_length += ((this_width >= string_length) ? this_width :
							string_length);
					else if (has_precision)
						out_length += ((this_precision <= string_length) ?
							this_precision : string_length);
					else
						out_length += string_length;
				}
			}
			else {
				switch (spec_ptr->base_type) {
					case STR_XPRINTF_TYPE_uchar		:
						arg_data.sint = va_arg(arg_list, signed int);
						sprintf(buffer, format_spec, arg_data.sint);
						break;
					case STR_XPRINTF_TYPE_sint			:
						arg_data.sint = va_arg(arg_list, signed int);
						sprintf(buffer, format_spec, arg_data.sint);
						break;
					case STR_XPRINTF_TYPE_uint			:
						arg_data.uint = va_arg(arg_list, unsigned int);
						sprintf(buffer, format_spec, arg_data.uint);
						break;
					case STR_XPRINTF_TYPE_slong		:
						arg_data.slong = va_arg(arg_list, signed long);
						sprintf(buffer, format_spec, arg_data.slong);
						break;
					case STR_XPRINTF_TYPE_ulong		:
						arg_data.ulong = va_arg(arg_list, unsigned long);
						sprintf(buffer, format_spec, arg_data.ulong);
						break;
					case STR_XPRINTF_TYPE_ddouble		:
						arg_data.ddouble = va_arg(arg_list, double);
						sprintf(buffer, format_spec, arg_data.ddouble);
						break;
					case STR_XPRINTF_TYPE_ldouble		:
						arg_data.ldouble = va_arg(arg_list, long double);
						sprintf(buffer, format_spec, arg_data.ldouble);
						break;
					case STR_XPRINTF_TYPE_char_ptr	:
					case STR_XPRINTF_TYPE_void_ptr	:
						arg_data.void_ptr = va_arg(arg_list, const void *);
						sprintf(buffer, format_spec, arg_data.void_ptr);
						break;
					case STR_XPRINTF_TYPE_slonglong	:
#ifdef _Windows
						arg_data.slonglong = va_arg(arg_list, signed __int64);
#else
						arg_data.slonglong = va_arg(arg_list, signed long long);
#endif /* #ifdef _Windows */
						sprintf(buffer, format_spec, arg_data.slonglong);
						break;
					case STR_XPRINTF_TYPE_ulonglong	:
#ifdef _Windows
						arg_data.ulonglong = va_arg(arg_list, unsigned __int64);
#else
						arg_data.ulonglong = va_arg(arg_list, unsigned long long);
#endif /* #ifdef _Windows */
						sprintf(buffer, format_spec, arg_data.ulonglong);
						break;
				}
				out_length += strlen(buffer);
			}
		}
	}

	return(out_length);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*VARARGS2*/
#ifndef NO_STDARGS
int STR_XPrintf_Alloc(char **buffer_ptr, const char *in_format, ...)
#else
int STR_XPrintf_Alloc(buffer_ptr, in_format, va_list)
char       **buffer_ptr;
const char  *in_format;
va_dcl
#endif /* #ifndef NO_STDARGS */
{
	int     return_code;
	va_list arg_list;

#ifndef NO_STDARGS
	va_start(arg_list, in_format);
#else
	va_start(arg_list);
#endif /* #ifndef NO_STDARGS */

	return_code = STR_XPrintf_AllocVA(buffer_ptr, in_format, arg_list);

	va_end(arg_list);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*VARARGS2*/
#ifndef NO_STDARGS
int STR_XPrintf_AllocVA(char **buffer_ptr, const char *in_format,
	va_list arg_list)
#else
int STR_XPrintf_AllocVA(buffer_ptr, in_format, arg_list)
char       **buffer_ptr;
const char  *in_format;
va_list      arg_list;
#endif /* #ifndef NO_STDARGS */
{
	int          return_code;
	unsigned int buffer_length;

	buffer_length = 0;
	*buffer_ptr   = NULL;

	return_code = STR_XPrintf_ReallocVA(&buffer_length, buffer_ptr, in_format,
		arg_list);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*VARARGS2*/
#ifndef NO_STDARGS
int STR_XPrintf_Realloc(unsigned int *buffer_length, char **buffer_ptr,
	const char *in_format, ...)
#else
int STR_XPrintf_Realloc(buffer_length, buffer_ptr, in_format, va_list)
unsigned int  *buffer_length;
char         **buffer_ptr;
const char    *in_format;
va_dcl
#endif /* #ifndef NO_STDARGS */
{
	int     return_code;
	va_list arg_list;

#ifndef NO_STDARGS
	va_start(arg_list, in_format);
#else
	va_start(arg_list);
#endif /* #ifndef NO_STDARGS */

	return_code = STR_XPrintf_ReallocVA(buffer_length, buffer_ptr, in_format,
		arg_list);

	va_end(arg_list);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*VARARGS2*/
#ifndef NO_STDARGS
int STR_XPrintf_ReallocVA(unsigned int *buffer_length, char **buffer_ptr,
	const char *in_format, va_list arg_list)
#else
int STR_XPrintf_ReallocVA(buffer_length, buffer_ptr, in_format, arg_list)
unsigned int  *buffer_length;
char         **buffer_ptr;
const char    *in_format;
va_list        arg_list;
#endif /* #ifndef NO_STDARGS */
{
	int           return_code = STRFUNCS_SUCCESS;
	unsigned int  out_length;
	char         *tmp_ptr;

	out_length = STR_XPrintf_GetLengthAllocVA(in_format, arg_list);

	if (out_length >= *buffer_length) {
		if ((tmp_ptr = ((char *) ((*buffer_length) ?
			realloc(*buffer_ptr, out_length * sizeof(char)) :
			calloc(out_length, sizeof(char))))) == NULL) {
			return_code = STRFUNCS_MEMORY_FAILURE;
			goto EXIT_FUNCTION;
		}
		*buffer_length = out_length;
		*buffer_ptr    = tmp_ptr;
	}

#ifdef _Windows
	_vsnprintf(*buffer_ptr, out_length - 1, in_format, arg_list);
#else
# ifdef STR_XPRINTF_HAS_VNSPRINTF
	vsnprintf(*buffer_ptr, out_length - 1, in_format, arg_list);
# else
	vsprintf(*buffer_ptr, in_format, arg_list);
# endif /* # ifdef STR_XPRINTF_HAS_VNSPRINTF */
#endif /* #ifdef _Windows */

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static const STR_XPRINTF_SPEC *STR_XPrintf_GetSpecPtr(
	const char *format_end_ptr)
#else
static const STR_XPRINTF_SPEC *STR_XPrintf_GetSpecPtr(format_end_ptr)
const char *format_end_ptr;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;

	for (count_1 = 0; count_1 < STR_XprintfSpecCount; count_1++) {
		if (!strncmp(STR_XprintfSpecList[count_1].spec_type, format_end_ptr,
			STR_XprintfSpecList[count_1].spec_type_length))
			return(STR_XprintfSpecList + count_1);
	}

	return(NULL);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(char *TEST_MakeDisplayFormat,
	(const char *in_format, char *out_format));
COMPAT_FN_DECL_STATIC(char *TEST_MakeDisplayFormat_01,
	(const char *in_format, char *out_format));
COMPAT_FN_DECL_STATIC(char *TEST_MakeDisplayFormat_02,
	(const char *in_format, int len_1, char *out_format));
COMPAT_FN_DECL_STATIC(char *TEST_MakeDisplayFormat_03,
	(const char *in_format, int len_1, int len_2, char *out_format));
	/*	*****************************************************************	*/
#define TEST_MAKE_FUNC_DECL(func_name)														\
	COMPAT_FN_DECL_STATIC(int func_name,													\
		(const char *func_name, unsigned int *buffer_length, char **buffer_ptr,	\
		int *return_code));
#define TEST_MAKE_FUNC_ENTRY(func_name)													\
	{	#func_name, func_name	}
	/*	*****************************************************************	*/
TEST_MAKE_FUNC_DECL(TEST_char_ptr_01)
TEST_MAKE_FUNC_DECL(TEST_char_ptr_02)
TEST_MAKE_FUNC_DECL(TEST_char_ptr_03)
TEST_MAKE_FUNC_DECL(TEST_sint_01)
TEST_MAKE_FUNC_DECL(TEST_sint_02)
TEST_MAKE_FUNC_DECL(TEST_sint_03)
	/*	*****************************************************************	*/
typedef struct {
	const char  *func_name;
	int        (*func_ptr)(const char *func_name, unsigned int *buffer_length,
						char **buffer_ptr, int *return_code);
} TEST_CONTROL;
static const TEST_CONTROL TEST_FuncList[] = {
	TEST_MAKE_FUNC_ENTRY(TEST_char_ptr_01),
	TEST_MAKE_FUNC_ENTRY(TEST_char_ptr_02),
	TEST_MAKE_FUNC_ENTRY(TEST_char_ptr_03),
	TEST_MAKE_FUNC_ENTRY(TEST_sint_01),
	TEST_MAKE_FUNC_ENTRY(TEST_sint_02),
	TEST_MAKE_FUNC_ENTRY(TEST_sint_03)
};
static const unsigned int TEST_FuncCount  =
	sizeof(TEST_FuncList) / sizeof(TEST_FuncList[0]);
/*	***********************************************************************	*/

/*	***********************************************************************	*/
typedef struct {
	char *format;
	int   len_1;
	int   len_2;
	char *arg;
} TEST_ITEM_char_ptr;
	/*	*****************************************************************	*/
#define TEST_MAKE_ITEM(format)			\
	{	format,	0, 0, "Simple string buffer"	}
static const TEST_ITEM_char_ptr TEST_TestList_char_ptr_01[] = {
	TEST_MAKE_ITEM("%s"),
	TEST_MAKE_ITEM("%10s"),
	TEST_MAKE_ITEM("%-10s"),
	TEST_MAKE_ITEM("%40s"),
	TEST_MAKE_ITEM("%-40s"),
	TEST_MAKE_ITEM("%.10s"),
	TEST_MAKE_ITEM("%-.10s"),
	TEST_MAKE_ITEM("%.40s"),
	TEST_MAKE_ITEM("%-.40s"),
	TEST_MAKE_ITEM("%10.10s"),
	TEST_MAKE_ITEM("%-10.10s"),
	TEST_MAKE_ITEM("%40.40s"),
	TEST_MAKE_ITEM("%-40.40s")
};
static const unsigned int       TEST_TestCount_char_ptr_01  =
	sizeof(TEST_TestList_char_ptr_01) / sizeof(TEST_TestList_char_ptr_01[0]);
#undef TEST_MAKE_ITEM
	/*	*****************************************************************	*/
#define TEST_MAKE_ITEM(format, len_1)	\
	{	format,	len_1, 0, "Simple string buffer"	}
static const TEST_ITEM_char_ptr TEST_TestList_char_ptr_02[] = {
	TEST_MAKE_ITEM("%*s",	10),
	TEST_MAKE_ITEM("%-*s",	10),
	TEST_MAKE_ITEM("%*s",	40),
	TEST_MAKE_ITEM("%-*s",	40),
	TEST_MAKE_ITEM("%.*s",	10),
	TEST_MAKE_ITEM("%-.*s",	10),
	TEST_MAKE_ITEM("%.*s",	40),
	TEST_MAKE_ITEM("%-.*s",	40)
};
static const unsigned int       TEST_TestCount_char_ptr_02  =
	sizeof(TEST_TestList_char_ptr_02) / sizeof(TEST_TestList_char_ptr_02[0]);
#undef TEST_MAKE_ITEM
	/*	*****************************************************************	*/
#define TEST_MAKE_ITEM(format, len_1, len_2)	\
	{	format,	len_1, len_2, "Simple string buffer"	}
static const TEST_ITEM_char_ptr TEST_TestList_char_ptr_03[] = {
	TEST_MAKE_ITEM("%*.*s",		10,	10),
	TEST_MAKE_ITEM("%-*.*s",	10,	10),
	TEST_MAKE_ITEM("%*.*s",		40,	40),
	TEST_MAKE_ITEM("%-*.*s",	40,	40)
};
static const unsigned int       TEST_TestCount_char_ptr_03  =
	sizeof(TEST_TestList_char_ptr_03) / sizeof(TEST_TestList_char_ptr_03[0]);
#undef TEST_MAKE_ITEM
	/*	*****************************************************************	*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
typedef struct {
	char *format;
	int   len_1;
	int   len_2;
	int   arg;
} TEST_ITEM_sint;
	/*	*****************************************************************	*/
#define TEST_MAKE_ITEM(format)			\
	{	format,	0, 0, 100 }
static const TEST_ITEM_sint TEST_TestList_sint_01[] = {
	TEST_MAKE_ITEM("%d"),
	TEST_MAKE_ITEM("%10d"),
	TEST_MAKE_ITEM("%-10d"),
	TEST_MAKE_ITEM("%+10d"),
	TEST_MAKE_ITEM("%40d"),
	TEST_MAKE_ITEM("%-40d"),
	TEST_MAKE_ITEM("%+40d"),
	TEST_MAKE_ITEM("%.10d"),
	TEST_MAKE_ITEM("%-.10d"),
	TEST_MAKE_ITEM("%+.10d"),
	TEST_MAKE_ITEM("%.40d"),
	TEST_MAKE_ITEM("%-.40d"),
	TEST_MAKE_ITEM("%+.40d"),
	TEST_MAKE_ITEM("%10.10d"),
	TEST_MAKE_ITEM("%-10.10d"),
	TEST_MAKE_ITEM("%+10.10d"),
	TEST_MAKE_ITEM("%40.40d"),
	TEST_MAKE_ITEM("%-40.40d"),
	TEST_MAKE_ITEM("%+40.40d"),

	TEST_MAKE_ITEM("%0d"),
	TEST_MAKE_ITEM("%010d"),
	TEST_MAKE_ITEM("%010d"),
	TEST_MAKE_ITEM("%040d"),
	TEST_MAKE_ITEM("%040d"),
	TEST_MAKE_ITEM("%0.10d"),
	TEST_MAKE_ITEM("%0.40d"),
	TEST_MAKE_ITEM("%010.10d"),
	TEST_MAKE_ITEM("%040.40d"),

	TEST_MAKE_ITEM("% d"),
	TEST_MAKE_ITEM("% 10d"),
	TEST_MAKE_ITEM("% 10d"),
	TEST_MAKE_ITEM("% 40d"),
	TEST_MAKE_ITEM("% 40d"),
	TEST_MAKE_ITEM("% .10d"),
	TEST_MAKE_ITEM("% .40d"),
	TEST_MAKE_ITEM("% 10.10d"),
	TEST_MAKE_ITEM("% 40.40d")
};
static const unsigned int   TEST_TestCount_sint_01  =
	sizeof(TEST_TestList_sint_01) / sizeof(TEST_TestList_sint_01[0]);
#undef TEST_MAKE_ITEM
	/*	*****************************************************************	*/
#define TEST_MAKE_ITEM(format, len_1)	\
	{	format,	len_1, 0, 100	}
static const TEST_ITEM_sint TEST_TestList_sint_02[] = {
	TEST_MAKE_ITEM("%*d",	10),
	TEST_MAKE_ITEM("%-*d",	10),
	TEST_MAKE_ITEM("%+*d",	10),
	TEST_MAKE_ITEM("%*d",	40),
	TEST_MAKE_ITEM("%-*d",	40),
	TEST_MAKE_ITEM("%+*d",	40),
	TEST_MAKE_ITEM("%.*d",	10),
	TEST_MAKE_ITEM("%-.*d",	10),
	TEST_MAKE_ITEM("%+.*d",	10),
	TEST_MAKE_ITEM("%.*d",	40),
	TEST_MAKE_ITEM("%-.*d",	40),
	TEST_MAKE_ITEM("%+.*d",	40),

	TEST_MAKE_ITEM("%0*d",	10),
	TEST_MAKE_ITEM("%0*d",	40),
	TEST_MAKE_ITEM("%0.*d",	10),
	TEST_MAKE_ITEM("%0.*d",	40),

	TEST_MAKE_ITEM("% *d",	10),
	TEST_MAKE_ITEM("% *d",	40),
	TEST_MAKE_ITEM("% .*d",	10),
	TEST_MAKE_ITEM("% .*d",	40),
};
static const unsigned int   TEST_TestCount_sint_02  =
	sizeof(TEST_TestList_sint_02) / sizeof(TEST_TestList_sint_02[0]);
#undef TEST_MAKE_ITEM
	/*	*****************************************************************	*/
#define TEST_MAKE_ITEM(format, len_1, len_2)	\
	{	format,	len_1, len_2, 100	}
static const TEST_ITEM_sint TEST_TestList_sint_03[] = {
	TEST_MAKE_ITEM("%*.*d",		10,	10),
	TEST_MAKE_ITEM("%-*.*d",	10,	10),
	TEST_MAKE_ITEM("%+*.*d",	10,	10),
	TEST_MAKE_ITEM("%*.*d",		40,	40),
	TEST_MAKE_ITEM("%-*.*d",	40,	40),
	TEST_MAKE_ITEM("%+*.*d",	40,	40),

	TEST_MAKE_ITEM("%0*.*d",	10,	10),
	TEST_MAKE_ITEM("%0*.*d",	40,	40),

	TEST_MAKE_ITEM("% *.*d",	10,	10),
	TEST_MAKE_ITEM("% *.*d",	40,	40),
	TEST_MAKE_ITEM("% *.*d",	STR_XPRINTF_MIN_C_STD_MAX,
										STR_XPRINTF_MIN_C_STD_MAX)
};
static const unsigned int   TEST_TestCount_sint_03  =
	sizeof(TEST_TestList_sint_03) / sizeof(TEST_TestList_sint_03[0]);
#undef TEST_MAKE_ITEM
	/*	*****************************************************************	*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int main()
{
	int           return_code   = STRFUNCS_SUCCESS;
	unsigned int  buffer_length = 0;
	char         *buffer_ptr    = NULL;
	unsigned int  failure_count = 0;
	unsigned int  count_1;

	fprintf(stderr,
		"Test routine for function 'STR_XPrintf_GetLength()'\n");
	fprintf(stderr,
		"                          'STR_XPrintf_GetLengthVA()'\n");
	fprintf(stderr,
		"                          'STR_XPrintf_GetLengthAlloc()'\n");
	fprintf(stderr,
		"                          'STR_XPrintf_GetLengthAllocVA()'\n");
	fprintf(stderr,
		"                          'STR_XPrintf_GetLengthBasic()'\n");
	fprintf(stderr,
		"                          'STR_XPrintf_GetLengthBasicVA()'\n");
	fprintf(stderr,
		"                          'STR_XPrintf_Alloc()'\n");
	fprintf(stderr,
		"                          'STR_XPrintf_AllocVA()'\n");
	fprintf(stderr,
		"                          'STR_XPrintf_Realloc()'\n");
	fprintf(stderr,
		"                          'STR_XPrintf_ReallocVA()'\n");
	fprintf(stderr,
		"---- ------- --- -------- --------------------------------\n\n");

	for (count_1 = 0; count_1 < TEST_FuncCount; count_1++) {
		if ((*TEST_FuncList[count_1].func_ptr)(TEST_FuncList[count_1].func_name,
			&buffer_length, &buffer_ptr, &return_code) != STRFUNCS_SUCCESS) {
			failure_count++;
			if (return_code == STRFUNCS_MEMORY_FAILURE)
				break;
		}
	}

	if (buffer_ptr != NULL)
		free(buffer_ptr);

	if (return_code != STRFUNCS_SUCCESS)
		fprintf(stderr, "\n\nERROR: A total of %u test%ss failed.\n\n",
			failure_count, (failure_count == 1) ? "" : "s");

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static char *TEST_MakeDisplayFormat(const char *in_format, char *out_format)
#else
static char *TEST_MakeDisplayFormat(in_format, out_format)
const char *in_format;
char       *out_format;
#endif /* #ifndef NARGS */
{
	const char *in_ptr  = in_format;
	char       *out_ptr = out_format;

	*out_ptr++ = '[';

	while (*in_ptr) {
		if (*in_ptr == '\\') {
			*out_ptr++ = *in_ptr++;
			if (!(*in_ptr))
				break;
			*out_ptr++ = *in_ptr++;
		}
		else if (*in_ptr == '%') {
			*out_ptr++ = *in_ptr++;
			*out_ptr++ = '%';
		}
		else
			*out_ptr++ = *in_ptr++;
	}

	chrcpy(out_ptr, ']');

	return(out_format);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static char *TEST_MakeDisplayFormat_01(const char *in_format, char *out_format)
#else
static char *TEST_MakeDisplayFormat_01(in_format, out_format)
const char *in_format;
char       *out_format;
#endif /* #ifndef NARGS */
{
	return(chrcat(strcat(strcat(TEST_MakeDisplayFormat(in_format, out_format),
		"=["), in_format), ']'));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static char *TEST_MakeDisplayFormat_02(const char *in_format, int len_1,
	char *out_format)
#else
static char *TEST_MakeDisplayFormat_02(in_format, len_1, out_format)
const char *in_format;
int         len_1;
char       *out_format;
#endif /* #ifndef NARGS */
{
	return(chrcat(strcat(strcat(val2str_sint_cat(len_1, 10, NULL,
		chrcat(TEST_MakeDisplayFormat(in_format, out_format), '[')),
		"]=["), in_format), ']'));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static char *TEST_MakeDisplayFormat_03(const char *in_format, int len_1,
	int len_2, char *out_format)
#else
static char *TEST_MakeDisplayFormat_03(in_format, len_1, len_2, out_format)
const char *in_format;
int         len_1;
int         len_2;
char       *out_format;
#endif /* #ifndef NARGS */
{
	return(chrcat(strcat(strcat(val2str_sint_cat(len_2, 10, NULL,
		strcat(val2str_sint_cat(len_1, 10, NULL,
		chrcat(TEST_MakeDisplayFormat(in_format, out_format), '[')), "][")),
		"]=["), in_format), ']'));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int TEST_char_ptr_01(const char *func_name, unsigned int *buffer_length,
	char **buffer_ptr, int *return_code)
#else
static int TEST_char_ptr_01(func_name, buffer_length, buffer_ptr, return_code)
const char    *func_name;
unsigned int  *buffer_length;
char         **buffer_ptr;
int           *return_code;
#endif /* #ifndef NARGS */
{
	char          format[1024];
	const char   *arg;
	unsigned int  s_length;
	unsigned int  x_length;
	unsigned int  r_length;
	unsigned int  count_1;
	char          buffer[4095 + 1];

	for (count_1 = 0; count_1 < TEST_TestCount_char_ptr_01; count_1++) {
		TEST_MakeDisplayFormat_01(TEST_TestList_char_ptr_01[count_1].format,
			format);
		arg = TEST_TestList_char_ptr_01[count_1].arg;
		sprintf(buffer, format, arg);
		s_length = strlen(buffer);
		x_length = STR_XPrintf_GetLength(format, arg);
		if (s_length == x_length) {
			printf("SUCCESS(length) :%s\n", buffer);
			if (STR_XPrintf_Realloc(buffer_length, buffer_ptr,
				format, arg) == STRFUNCS_SUCCESS) {
				if (!strcmp(buffer, *buffer_ptr))
					printf("SUCCESS(realloc):%s\n", buffer);
				else {
					r_length = strlen(*buffer_ptr);
					printf("FAILURE(realloc):%s/%s=%u/%u/%u --- %s\n", buffer,
						*buffer_ptr, s_length, x_length, r_length, func_name);
					*return_code = STRFUNCS_MEMORY_FAILURE;
				}
			}
			else {
				printf("FAILURE(memory) :%s=%u/%u --- %s\n", buffer, s_length,
					x_length, func_name);
				*return_code = STRFUNCS_MEMORY_FAILURE;
			}
		}
		else {
			printf("FAILURE(length) :%s=%u/%u --- %s\n", buffer, s_length,
				x_length, func_name);
			*return_code = STRFUNCS_FAILURE;
		}
	}

	return(*return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int TEST_char_ptr_02(const char *func_name, unsigned int *buffer_length,
	char **buffer_ptr, int *return_code)
#else
static int TEST_char_ptr_02(func_name, buffer_length, buffer_ptr, return_code)
const char    *func_name;
unsigned int  *buffer_length;
char         **buffer_ptr;
int           *return_code;
#endif /* #ifndef NARGS */
{
	char          format[1024];
	int           len_1;
	const char   *arg;
	unsigned int  s_length;
	unsigned int  x_length;
	unsigned int  r_length;
	unsigned int  count_1;
	char          buffer[4095 + 1];

	for (count_1 = 0; count_1 < TEST_TestCount_char_ptr_02; count_1++) {
		TEST_MakeDisplayFormat_02(TEST_TestList_char_ptr_02[count_1].format,
			TEST_TestList_char_ptr_02[count_1].len_1, format);
		len_1 = TEST_TestList_char_ptr_02[count_1].len_1;
		arg   = TEST_TestList_char_ptr_02[count_1].arg;
		sprintf(buffer, format, len_1, arg);
		s_length = strlen(buffer);
		x_length = STR_XPrintf_GetLength(format, len_1, arg);
		if (s_length == x_length) {
			printf("SUCCESS(length) :%s\n", buffer);
			if (STR_XPrintf_Realloc(buffer_length, buffer_ptr,
				format, len_1, arg) == STRFUNCS_SUCCESS) {
				if (!strcmp(buffer, *buffer_ptr))
					printf("SUCCESS(realloc):%s\n", buffer);
				else {
					r_length = strlen(*buffer_ptr);
					printf("FAILURE(realloc):%s/%s=%u/%u/%u --- %s\n", buffer,
						*buffer_ptr, s_length, x_length, r_length, func_name);
					*return_code = STRFUNCS_MEMORY_FAILURE;
				}
			}
			else {
				printf("FAILURE(memory) :%s=%u/%u --- %s\n", buffer, s_length,
					x_length, func_name);
				*return_code = STRFUNCS_MEMORY_FAILURE;
			}
		}
		else {
			printf("FAILURE(length) :%s=%u/%u --- %s\n", buffer, s_length,
				x_length, func_name);
			*return_code = STRFUNCS_FAILURE;
		}
	}

	return(*return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int TEST_char_ptr_03(const char *func_name, unsigned int *buffer_length,
	char **buffer_ptr, int *return_code)
#else
static int TEST_char_ptr_03(func_name, buffer_length, buffer_ptr, return_code)
const char    *func_name;
unsigned int  *buffer_length;
char         **buffer_ptr;
int           *return_code;
#endif /* #ifndef NARGS */
{
	char          format[1024];
	int           len_1;
	int           len_2;
	const char   *arg;
	unsigned int  s_length;
	unsigned int  x_length;
	unsigned int  r_length;
	unsigned int  count_1;
	char          buffer[4095 + 1];

	for (count_1 = 0; count_1 < TEST_TestCount_char_ptr_03; count_1++) {
		TEST_MakeDisplayFormat_03(TEST_TestList_char_ptr_03[count_1].format,
			TEST_TestList_char_ptr_03[count_1].len_1,
			TEST_TestList_char_ptr_03[count_1].len_2, format);
		len_1 = TEST_TestList_char_ptr_03[count_1].len_1;
		len_2 = TEST_TestList_char_ptr_03[count_1].len_2;
		arg   = TEST_TestList_char_ptr_03[count_1].arg;
		sprintf(buffer, format, len_1, len_2, arg);
		s_length = strlen(buffer);
		x_length = STR_XPrintf_GetLength(format, len_1, len_2, arg);
		if (s_length == x_length) {
			printf("SUCCESS(length) :%s\n", buffer);
			if (STR_XPrintf_Realloc(buffer_length, buffer_ptr,
				format, len_1, len_2, arg) == STRFUNCS_SUCCESS) {
				if (!strcmp(buffer, *buffer_ptr))
					printf("SUCCESS(realloc):%s\n", buffer);
				else {
					r_length = strlen(*buffer_ptr);
					printf("FAILURE(realloc):%s/%s=%u/%u/%u --- %s\n", buffer,
						*buffer_ptr, s_length, x_length, r_length, func_name);
					*return_code = STRFUNCS_MEMORY_FAILURE;
				}
			}
			else {
				printf("FAILURE(memory) :%s=%u/%u --- %s\n", buffer, s_length,
					x_length, func_name);
				*return_code = STRFUNCS_MEMORY_FAILURE;
			}
		}
		else {
			printf("FAILURE(length) :%s=%u/%u --- %s\n", buffer, s_length,
				x_length, func_name);
			*return_code = STRFUNCS_FAILURE;
		}
	}

	return(*return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int TEST_sint_01(const char *func_name, unsigned int *buffer_length,
	char **buffer_ptr, int *return_code)
#else
static int TEST_sint_01(func_name, buffer_length, buffer_ptr, return_code)
const char    *func_name;
unsigned int  *buffer_length;
char         **buffer_ptr;
int           *return_code;
#endif /* #ifndef NARGS */
{
	char          format[1024];
	int           arg;
	unsigned int  s_length;
	unsigned int  x_length;
	unsigned int  r_length;
	unsigned int  count_1;
	char          buffer[4095 + 1];

	for (count_1 = 0; count_1 < TEST_TestCount_sint_01; count_1++) {
		TEST_MakeDisplayFormat_01(TEST_TestList_sint_01[count_1].format,
			format);
		arg = TEST_TestList_sint_01[count_1].arg;
		sprintf(buffer, format, arg);
		s_length = strlen(buffer);
		x_length = STR_XPrintf_GetLength(format, arg);
		if (s_length == x_length) {
			printf("SUCCESS(length) :%s\n", buffer);
			if (STR_XPrintf_Realloc(buffer_length, buffer_ptr,
				format, arg) == STRFUNCS_SUCCESS) {
				if (!strcmp(buffer, *buffer_ptr))
					printf("SUCCESS(realloc):%s\n", buffer);
				else {
					r_length = strlen(*buffer_ptr);
					printf("FAILURE(realloc):%s/%s=%u/%u/%u --- %s\n", buffer,
						*buffer_ptr, s_length, x_length, r_length, func_name);
					*return_code = STRFUNCS_MEMORY_FAILURE;
				}
			}
			else {
				printf("FAILURE(memory) :%s=%u/%u --- %s\n", buffer, s_length,
					x_length, func_name);
				*return_code = STRFUNCS_MEMORY_FAILURE;
			}
		}
		else {
			printf("FAILURE(length) :%s=%u/%u --- %s\n", buffer, s_length,
				x_length, func_name);
			*return_code = STRFUNCS_FAILURE;
		}
	}

	return(*return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int TEST_sint_02(const char *func_name, unsigned int *buffer_length,
	char **buffer_ptr, int *return_code)
#else
static int TEST_sint_02(func_name, buffer_length, buffer_ptr, return_code)
const char    *func_name;
unsigned int  *buffer_length;
char         **buffer_ptr;
int           *return_code;
#endif /* #ifndef NARGS */
{
	char          format[1024];
	int           len_1;
	int           arg;
	unsigned int  s_length;
	unsigned int  x_length;
	unsigned int  r_length;
	unsigned int  count_1;
	char          buffer[4095 + 1];

	for (count_1 = 0; count_1 < TEST_TestCount_sint_02; count_1++) {
		TEST_MakeDisplayFormat_02(TEST_TestList_sint_02[count_1].format,
			TEST_TestList_sint_02[count_1].len_1, format);
		len_1 = TEST_TestList_sint_02[count_1].len_1;
		arg   = TEST_TestList_sint_02[count_1].arg;
		sprintf(buffer, format, len_1, arg);
		s_length = strlen(buffer);
		x_length = STR_XPrintf_GetLength(format, len_1, arg);
		if (s_length == x_length) {
			printf("SUCCESS(length) :%s\n", buffer);
			if (STR_XPrintf_Realloc(buffer_length, buffer_ptr,
				format, len_1, arg) == STRFUNCS_SUCCESS) {
				if (!strcmp(buffer, *buffer_ptr))
					printf("SUCCESS(realloc):%s\n", buffer);
				else {
					r_length = strlen(*buffer_ptr);
					printf("FAILURE(realloc):%s/%s=%u/%u/%u --- %s\n", buffer,
						*buffer_ptr, s_length, x_length, r_length, func_name);
					*return_code = STRFUNCS_MEMORY_FAILURE;
				}
			}
			else {
				printf("FAILURE(memory) :%s=%u/%u --- %s\n", buffer, s_length,
					x_length, func_name);
				*return_code = STRFUNCS_MEMORY_FAILURE;
			}
		}
		else {
			printf("FAILURE(length) :%s=%u/%u --- %s\n", buffer, s_length,
				x_length, func_name);
			*return_code = STRFUNCS_FAILURE;
		}
	}

	return(*return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int TEST_sint_03(const char *func_name, unsigned int *buffer_length,
	char **buffer_ptr, int *return_code)
#else
static int TEST_sint_03(func_name, buffer_length, buffer_ptr, return_code)
const char    *func_name;
unsigned int  *buffer_length;
char         **buffer_ptr;
int           *return_code;
#endif /* #ifndef NARGS */
{
	char          format[1024];
	int           len_1;
	int           len_2;
	int           arg;
	unsigned int  s_length;
	unsigned int  x_length;
	unsigned int  r_length;
	unsigned int  count_1;
	char          buffer[4095 + 1];

	for (count_1 = 0; count_1 < TEST_TestCount_sint_03; count_1++) {
		TEST_MakeDisplayFormat_03(TEST_TestList_sint_03[count_1].format,
			TEST_TestList_sint_03[count_1].len_1,
			TEST_TestList_sint_03[count_1].len_2, format);
		len_1 = TEST_TestList_sint_03[count_1].len_1;
		len_2 = TEST_TestList_sint_03[count_1].len_2;
		arg   = TEST_TestList_sint_03[count_1].arg;
		sprintf(buffer, format, len_1, len_2, arg);
		s_length = strlen(buffer);
		x_length = STR_XPrintf_GetLength(format, len_1, len_2, arg);
		if (s_length == x_length) {
			printf("SUCCESS(length) :%s\n", buffer);
			if (STR_XPrintf_Realloc(buffer_length, buffer_ptr,
				format, len_1, len_2, arg) == STRFUNCS_SUCCESS) {
				if (!strcmp(buffer, *buffer_ptr))
					printf("SUCCESS(realloc):%s\n", buffer);
				else {
					r_length = strlen(*buffer_ptr);
					printf("FAILURE(realloc):%s/%s=%u/%u/%u --- %s\n", buffer,
						*buffer_ptr, s_length, x_length, r_length, func_name);
					*return_code = STRFUNCS_MEMORY_FAILURE;
				}
			}
			else {
				printf("FAILURE(memory) :%s=%u/%u --- %s\n", buffer, s_length,
					x_length, func_name);
				*return_code = STRFUNCS_MEMORY_FAILURE;
			}
		}
		else {
			printf("FAILURE(length) :%s=%u/%u --- %s\n", buffer, s_length,
				x_length, func_name);
			*return_code = STRFUNCS_FAILURE;
		}
	}

	return(*return_code);
}
/*	***********************************************************************	*/

#endif /* #ifdef TEST_MAIN */


