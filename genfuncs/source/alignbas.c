/* *********************************************************************** */
/* *********************************************************************** */
/*	GENFUNCS General Functions Library Source Module								*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Low-level functions used to determine the alignment
								of primitive data types and to manage access to those
								data types in run-time specified aggregations.

	Revision History	:	1992-02-23 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Include necessary header files . . .											*/
/* *********************************************************************** */

#include <limits.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <strfuncs.h>

#include "genfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* 	The macro 'offsetof' is defined by ANSI C. If it's not available on	*/
/* this system, define it . . .															*/
/* *********************************************************************** */

#ifndef offsetof
# define offsetof(structure_name, member_name) \
	((size_t) &(((structure_name *) 0)->member_name))
#endif /* #ifndef offsetof */

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* 	The structures below will tell us the alignment requirements for the	*/
/* environment under which this file is compiled. If your compiler has an	*/
/* option to turn alignment on and off, you'll need to compile this file	*/
/* using same options.																		*/
/* *********************************************************************** */

typedef struct { char spacing[1]; char member;   } GEN_byte;
typedef struct { char spacing[1]; char member;   } GEN_char;
typedef struct { char spacing[1]; short member;  } GEN_short;
typedef struct { char spacing[1]; int member;    } GEN_int;
typedef struct { char spacing[1]; long member;   } GEN_long;
typedef struct { char spacing[1]; float member;  } GEN_float;
typedef struct { char spacing[1]; double member; } GEN_double;

/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   NAME        :  GEN_ALIGN_TypeList

   DESCRIPTION :  ``GEN_ALIGN_TypeList`` is the built-in array of
						''GEN_ALIGN_SPEC'' structures which define the primitive
						data types available on the machine.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  GEN_ALIGN_TypeCount

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:  GEN_ALIGN_TypeList
						Alignment Data:GEN_ALIGN_TypeList
						GENFUNCS:Data:GEN_ALIGN_TypeList
						GENFUNCS:Alignment Data:GEN_ALIGN_TypeList
						General Functions:See GENFUNCS

   PUBLISH XREF:  GEN_ALIGN_TypeList

   PUBLISH NAME:	GEN_ALIGN_TypeList

	ENTRY CLASS	:	Alignment Data

EOH */
/*	***********************************************************************	*/
/* 	The array below describes the alignment requirements of the various	*/
/* primitive C data types. Note that although the 'signed' and 'unsigned'	*/
/* forms have separate entries in the array, it is assumed that they have	*/
/* the same alignment requirements. This is probably quite a reasonable		*/
/* assumption.																					*/
/* *********************************************************************** */
#ifndef NARGS
COMPAT_EXTERN_DATA_DEF const GEN_ALIGN_SPEC GEN_ALIGN_TypeList[] = {
	{	"unsigned byte",	"ubyte",	'b',	offsetof(GEN_byte, member),
		sizeof(unsigned char),	"%c",			 1,
		((int (*)(void *, const void *, const void *, size_t)) GEN_SCMP_ubyte),
		((bool_t (*)(XDR *, void *)) xdr_char)	},
	{	"signed char",		"schar",	'c',	offsetof(GEN_char, member),
		sizeof(char),				"%c",			 1,
		((int (*)(void *, const void *, const void *, size_t)) GEN_SCMP_char),
		((bool_t (*)(XDR *, void *)) xdr_char)		},
	{	"unsigned char",	"uchar",	'C',	offsetof(GEN_char, member),
		sizeof(unsigned char),	"%c",			 1,
		((int (*)(void *, const void *, const void *, size_t)) GEN_SCMP_uchar),
		((bool_t (*)(XDR *, void *)) xdr_u_char)	},
	{	"signed short",	"sshort",'s',	offsetof(GEN_short, member),
		sizeof(short),				"%6hd",		 6,
		((int (*)(void *, const void *, const void *, size_t)) GEN_SCMP_short),
		((bool_t (*)(XDR *, void *)) xdr_short)	},
	{	"unsigned short",	"ushort",'S',	offsetof(GEN_short, member),
		sizeof(unsigned short),	"%5hu",		 5,
		((int (*)(void *, const void *, const void *, size_t)) GEN_SCMP_ushort),
		((bool_t (*)(XDR *, void *)) xdr_u_short)	},
#ifndef __MSDOS__
	{	"signed int",		"sint",	'i',	offsetof(GEN_int, member),
		sizeof(int),				"%11d",		11,
		((int (*)(void *, const void *, const void *, size_t)) GEN_SCMP_int),
		((bool_t (*)(XDR *, void *)) xdr_int)		},
	{	"unsigned int",	"uint",	'I',	offsetof(GEN_int, member),
		sizeof(unsigned int),	"%10u",		10,
		((int (*)(void *, const void *, const void *, size_t)) GEN_SCMP_uint),
		((bool_t (*)(XDR *, void *)) xdr_u_int)	},
#else
	{	"signed int",		"sint",	'i',	offsetof(GEN_int, member),
		sizeof(int),				"%6d",		 6,
		((int (*)(void *, const void *, const void *, size_t)) GEN_SCMP_int),
		((bool_t (*)(XDR *, void *)) xdr_short)		},
	{	"unsigned int",	"uint",	'I',	offsetof(GEN_int, member),
		sizeof(unsigned int),	"%5u",		 5,
		((int (*)(void *, const void *, const void *, size_t)) GEN_SCMP_uint),
		((bool_t (*)(XDR *, void *)) xdr_u_short)		},
#endif /* #ifndef __MSDOS__ */
	{	"signed long",		"slong",	'l',	offsetof(GEN_long, member),
		sizeof(long),				"%11d",		11,
		((int (*)(void *, const void *, const void *, size_t)) GEN_SCMP_long),
		((bool_t (*)(XDR *, void *)) xdr_long)		},
	{	"unsigned long",	"ulong",	'L',	offsetof(GEN_long, member),
		sizeof(unsigned long),	"%10u",		10,
		((int (*)(void *, const void *, const void *, size_t)) GEN_SCMP_ulong),
		((bool_t (*)(XDR *, void *)) xdr_u_long)	},
	{	"float",				"float",	'f',	offsetof(GEN_float, member),
		sizeof(float),				"%14.4f",	14,
		((int (*)(void *, const void *, const void *, size_t)) GEN_SCMP_float),
		((bool_t (*)(XDR *, void *)) xdr_float)	},
	{	"double",			"double",'d',	offsetof(GEN_double, member),
		sizeof(double),			"%14.4lf",	14,
		((int (*)(void *, const void *, const void *, size_t)) GEN_SCMP_double),
		((bool_t (*)(XDR *, void *)) xdr_double)	}
};
#else
COMPAT_EXTERN_DATA_DEF const GEN_ALIGN_SPEC GEN_ALIGN_TypeList[] = {
	{	"unsigned byte",	"ubyte",	'b',	offsetof(GEN_byte, member),
		sizeof(unsigned char),	"%c",			 1,
		GEN_SCMP_ubyte,	xdr_char	},
	{	"signed char",		"schar",	'c',	offsetof(GEN_char, member),
		sizeof(char),				"%c",			 1,
		GEN_SCMP_char,		xdr_char		},
	{	"unsigned char",	"uchar",	'C',	offsetof(GEN_char, member),
		sizeof(unsigned char),	"%c",			 1,
		GEN_SCMP_uchar,	xdr_u_char	},
	{	"signed short",	"sshort",'s',	offsetof(GEN_short, member),
		sizeof(short),				"%6hd",		 6,
		GEN_SCMP_short,	xdr_short	},
	{	"unsigned short",	"ushort",'S',	offsetof(GEN_short, member),
		sizeof(unsigned short),	"%5hu",		 5,
		GEN_SCMP_ushort,	xdr_u_short	},
#ifndef __MSDOS__
	{	"signed int",		"sint",	'i',	offsetof(GEN_int, member),
		sizeof(int),				"%11d",		11,
		GEN_SCMP_int,		xdr_int		},
	{	"unsigned int",	"uint",	'I',	offsetof(GEN_int, member),
		sizeof(unsigned int),	"%10u",		10,
		GEN_SCMP_uint,		xdr_u_int	},
#else
	{	"signed int",		"sint",	'i',	offsetof(GEN_int, member),
		sizeof(int),				"%6d",		 6,
		GEN_SCMP_int,		xdr_short	},
	{	"unsigned int",	"uint",	'I',	offsetof(GEN_int, member),
		sizeof(unsigned int),	"%5u",		 5,
		GEN_SCMP_uint,		xdr_u_short	},
#endif /* #ifndef __MSDOS__ */
	{	"signed long",		"slong",	'l',	offsetof(GEN_long, member),
		sizeof(long),				"%11d",		11,
		GEN_SCMP_long,		xdr_long		},
	{	"unsigned long",	"ulong",	'L',	offsetof(GEN_long, member),
		sizeof(unsigned long),	"%10u",		10,
		GEN_SCMP_ulong,	xdr_u_long	},
	{	"float",				"float",	'f',	offsetof(GEN_float, member),
		sizeof(float),				"%14.4f",	14,
		GEN_SCMP_float,	xdr_float	},
	{	"double",			"double",'d',	offsetof(GEN_double, member),
		sizeof(double),			"%14.4lf",	14,
		GEN_SCMP_double,	xdr_double	}
};
#endif /* #ifndef NARGS */
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   NAME        :  GEN_ALIGN_TypeCount

   DESCRIPTION :  ``GEN_ALIGN_TypeCount`` is the number of elements in the
						array ``GEN_ALIGN_TypeList``, which is the built-in array of
						''GEN_ALIGN_SPEC'' structures defining the primitive data
						types available on the machine.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  GEN_ALIGN_TypeList

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:  GEN_ALIGN_TypeCount
						Alignment Data:GEN_ALIGN_TypeCount
						GENFUNCS:Data:GEN_ALIGN_TypeCount
						GENFUNCS:Alignment Data:GEN_ALIGN_TypeCount
						General Functions:See GENFUNCS

   PUBLISH XREF:  GEN_ALIGN_TypeCount

   PUBLISH NAME:	GEN_ALIGN_TypeCount

	ENTRY CLASS	:	Alignment Data

EOH */
/*	***********************************************************************	*/
COMPAT_EXTERN_DATA_DEF const unsigned int GEN_ALIGN_TypeCount =
	(sizeof(GEN_ALIGN_TypeList) / sizeof(GEN_ALIGN_TypeList[0]));
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_ALIGN_BASIC_AlignStringList

   SYNOPSIS    :  return_code = GEN_ALIGN_BASIC_AlignStringList(type_count,
							type_list, normalize_flag, adjust_char_flag,
							separator_list, spec_count, spec_list, count_list,
							index_list, size_list, structure_size, align_count,
							align_list, error_text);

						int                    return_code;

						unsigned int           type_count;

						const GEN_ALIGN_SPEC  *type_list;

						int                    normalize_flag;

						int                    adjust_char_flag;

						const char            *separator_list;

						unsigned int           spec_count;

						char                 **spec_list;

						unsigned int         **count_list;

						unsigned int         **index_list;

						unsigned int         **size_list;

						unsigned int          *structure_size;

						unsigned int          *align_count;

						GEN_ALIGN            **align_list;

						char                  *error_text;

   DESCRIPTION :	Transforms an array of pointers to string specifications of
						the primitive type members of a structure into an array of
						structures of type ''GEN_ALIGN'', the elements of which
						contain offset and length data for each member.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``type_count`` is the number of elements in the array
						represented by the ``type_list`` parameter.

						(.) ``type_list`` is an array of ''GEN_ALIGN_SPEC''
						structures which describe a machine architecture in terms
						of the primitive data types available on that architecture.

						(-) If ``type_count`` is ''0'' and ``type_list`` is
						''NULL'', the function will use the built-in primitive
						data type list compiled into the module ``genalign.c``
						under the names ``GEN_ALIGN_TypeCount`` and
						``GEN_ALIGN_TypeList``.

						(.) ``normalize_flag`` indicates whether the elements of
						the array ``align_list`` which results the operation of
						this function are to be normalized vis-a-vis each other.

						(-) Normalization is the combination of like data types from
						adjacent ``align_list`` elements into a single element.

						(-) For example, if ``align_list`` contains the adjacent
						elements resulting from operation of this function on the
						string:

{|-|}c[10],c[3]

						(-) Normalization of those elements will result in a single
						element equivalent to the string:

{|-|}c[13]

						(-) The ``normalize_flag`` parameter may take on one of the
						following two values:

						(..) ``GENFUNCS_TRUE``, which indicates that the elements
						are to be normalized.

						(..) ``GENFUNCS_FALSE``, which indicates that the elements
						are not to be normalized.

						(.) ``adjust_char_flag`` specifies that ''char'' (and
						''unsigned char'') arrays are to be increased in length
						by a single byte. This is usually to accomodate the
						inclusion of the ''C'' language string null terminator byte.

						(-) The ``adjust_char_flag`` parameter may take on one of
						the following two values:

						(..) ``GENFUNCS_TRUE``, which indicates that ''char''
						elements are to be adjusted.

						(..) ``GENFUNCS_FALSE``, which indicates that ''char''
						elements are not to be adjusted.

						(.) ``separator_list`` is an ASCII NUL (ASCII 0) terminated
						string which lists the characters to be used to separate
						discrete specifications in the elements of ``spec_list``.

						(-) if ``separator_list`` is ''NULL'', the comma character
						('','') will be used to separate specifications in
						the elements of ``spec_list``.

						(.) ``spec_count`` is the number of elements in the
						array ``spec_list``.

						(.) ``spec_list`` is a array of pointers to strings, each
						string of which is a primitive type specification having
						the following format:

						(--) { ''b''|''c''|''C''|''s''|''S''|''i''|''I''|''l''|''L''|''f''|''d'' }

						(-) where each letter has the following meaning:

						(..)''b'' is an unsigned (binary) char. The upper-case
						letter ''B'' is also allowed.

						(..)''c'' is a signed char.

						(..)''C'' is an unsigned char.

						(..)''s'' is a signed short integer.

						(..)''S'' is an unsigned short integer.

						(..)''i'' is a signed integer.

						(..)''I'' is an unsigned integer.

						(..)''l'' is a long integer.

						(..)''L'' is an unsigned long integer

						(..)''f'' is a float. The upper-case letter ''F'' is also
						allowed.

						(..)''d'' is a double. The upper-case letter ''D'' is also
						allowed.

						(-) A member definition may be followed by an optional
						array specifier of the form:

						(--) ``member-definition``[``array-length``]

						(-) Note that ``array-length`` must be greater than zero.

						(.) ``count_list`` is a pointer to an ''unsigned int'' into
						which this function will place a pointer to memory allocated
						to hold an array of ''unsigned int''s. Each element of the
						array will correspond to an element in the array
						``spec_list``, so the total number of elements allocated
						will be equal to ``spec_count``.

						(-) Each element of the allocated array represents the
						number of elements in the array ``align_list`` for the
						corresponding ``spec_list`` element.

						(.) ``index_list`` is a pointer to an ''unsigned int'' into
						which this function will place a pointer to memory allocated
						to hold an array of ''unsigned int''s. Each element of the
						array will correspond to an element in the array
						``spec_list``, so the total number of elements allocated
						will be equal to ``spec_count``.

						(-) Each element of the allocated array represents the
						first element of the array ``align_list`` for the
						corresponding ``spec_list`` element.

						(.) ``size_list`` is a pointer to an ''unsigned int'' into
						which this function will place a pointer to memory allocated
						to hold an array of ''unsigned int''s. Each element of the
						array will correspond to an element in the array
						``spec_list``, so the total number of elements allocated
						will be equal to ``spec_count``.

						(-) Each element of the allocated array represents the
						total size of all of the elements in the array
						``align_list`` for the 	corresponding ``spec_list`` element.
						This size will include any alignment bytes required by the
						implementation.

						(.) ``structure_size`` is a pointer to an ''unsigned int''
						into which will be placed the total size of the structure
						as determined by this function. The size will include
						any alignment bytes required by the implementation.

						(-) If ``structure_size`` is ''NULL'', it will not be
						de-referenced.

						(.) ``align_count`` is a pointer to an ''unsigned int'' into
						which will be placed the number of members which were
						parsed out of the string ``spec_string``.

						(.) ``align_list`` points to a pointer to a structure of
						type ''GEN_ALIGN''. If the function is
						successful, it will allocate memory sufficient to hold
						``align_count`` elements. Each element will describe the
						offset and length requirements for each member of the
						desired structure.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at
						least ''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if no error occurs.

						(.) One of the non-zero GENFUNCS return codes if an error
						occurs.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  GEN_ALIGN_AlignStringList
						GEN_ALIGN_BASIC_AlignString

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_ALIGN_BASIC_AlignStringList
						Alignment Functions:GEN_ALIGN_BASIC_AlignStringList
						GENFUNCS:Functions:GEN_ALIGN_BASIC_AlignStringList
						GENFUNCS:Alignment Functions:GEN_ALIGN_BASIC_AlignStringList
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_ALIGN_BASIC_AlignStringList

   PUBLISH NAME:	GEN_ALIGN_BASIC_AlignStringList

	ENTRY CLASS	:	Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int GEN_ALIGN_BASIC_AlignStringList(unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, int normalize_flag,
	int adjust_char_flag, const char *separator_list, unsigned int spec_count,
	char **spec_list, unsigned int **count_list, unsigned int **index_list,
	unsigned int **size_list, unsigned int *structure_size,
	unsigned int *align_count, GEN_ALIGN **align_list, char *error_text)
#else
int GEN_ALIGN_BASIC_AlignStringList(type_count, type_list, normalize_flag,
	adjust_char_flag, separator_list, spec_count, spec_list, count_list,
	index_list, size_list, structure_size, align_count, align_list,
	error_text)
unsigned int           type_count;
const GEN_ALIGN_SPEC  *type_list;
int                    normalize_flag;
int                    adjust_char_flag;
const char            *separator_list;
unsigned int           spec_count;
char                 **spec_list;
unsigned int         **count_list;
unsigned int         **index_list;
unsigned int         **size_list;
unsigned int          *structure_size;
unsigned int          *align_count;
GEN_ALIGN            **align_list;
char                  *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code;
	unsigned int  current_index   = 0;
	unsigned int  tmp_align_count = 0;
	GEN_ALIGN    *tmp_align_list  = NULL;
	unsigned int  count_1;
	unsigned int  tmp_structure_size;
	char          tmp_error_text[GENFUNCS_MAX_ERROR_TEXT + 1];

	structure_size  = (structure_size == NULL) ? &tmp_structure_size :
		structure_size;

	*count_list     = NULL;
	*index_list     = NULL;
	*size_list      = NULL;
	*structure_size = 0;
	*align_count    = 0;
	*align_list     = NULL;

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Make sure we have work to do . . .									*/
	/*	**************************************************************	*/
	if (!spec_count) {
		strcpy(error_text, "No primitive type specifications passed.");
		return_code = GENFUNCS_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Allocate space for the array of align structure counts.		*/
	/*	**************************************************************	*/
	if ((*count_list = ((unsigned int *) calloc(spec_count,
		sizeof(*count_list)))) == NULL) {
		GEN_AllocMsgList(spec_count, sizeof(*count_list), error_text,
			"Unable to allocate memory for the count array");
		return_code = GENFUNCS_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Allocate space for the array of align index elements.			*/
	/*	**************************************************************	*/
	if ((*index_list = ((unsigned int *) calloc(spec_count,
		sizeof(*index_list)))) == NULL) {
		GEN_AllocMsgList(spec_count, sizeof(*index_list), error_text,
			"Unable to allocate memory for the index array");
		return_code = GENFUNCS_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Allocate space for the array of align size elements.			*/
	/*	**************************************************************	*/
	if ((*size_list = ((unsigned int *) calloc(spec_count,
		sizeof(*size_list)))) == NULL) {
		GEN_AllocMsgList(spec_count, sizeof(*size_list), error_text,
			"Unable to allocate memory for the size array");
		return_code = GENFUNCS_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		For each specification, attempt to create an array of align	*/
	/*	elements. This array will be added to the cumulative array.		*/
	/*																						*/
	/*		You should note that we don't try to normalize across			*/
	/*	specifications. That is, if one specification is 'c[10]', and	*/
	/*	the specification which follows is 'c[3]', we don't replace		*/
	/*	the align elements corresponding to these two specifications	*/
	/*	with the equivalent of 'c[13]'. This is because we envision		*/
	/*	this routine as used to determine the size and offset of			*/
	/*	structure members.															*/
	/*																						*/
	/*		If you want your specifications normalized across array		*/
	/*	elements, you should perform a call to the associated function	*/
	/*	'GEN_ALIGN_NormalizeList()' after this function returns.			*/
	/*	**************************************************************	*/
	for (count_1 = 0; count_1 < spec_count; count_1++) {
		if ((return_code = GEN_ALIGN_BASIC_AlignString(type_count, type_list,
			normalize_flag, adjust_char_flag, separator_list, spec_list[count_1],
			*size_list + count_1, &tmp_align_count, &tmp_align_list,
			tmp_error_text)) != GENFUNCS_SUCCESS) {
			sprintf(error_text, "%s %u: %s",
				"Error processing primitive type specification index number",
				count_1, tmp_error_text);
			goto EXIT_FUNCTION;
		}
		else if (mema_add(tmp_align_count, tmp_align_list, sizeof(**align_list),
			align_count, ((void **) align_list)) != STRFUNCS_SUCCESS) {
			GEN_AllocMsgList(tmp_align_count, sizeof(**align_list), error_text,
				"%s for primitive type specification index number %u.",
				"Unable to allocate memory for the align array", count_1);
			return_code = GENFUNCS_MEMORY_FAILURE;
			goto EXIT_FUNCTION;
		}
		(*count_list)[count_1]  = tmp_align_count;
		(*index_list)[count_1]  = current_index;
		current_index          += tmp_align_count;
		if (tmp_align_list != NULL) {
			free(tmp_align_list);
			tmp_align_list = NULL;
		}
	}
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Now fix-up all of the offsets for the cumulative array.		*/
	/*	**************************************************************	*/
	return_code = GEN_ALIGN_BASIC_AlignList(type_count, type_list,
		structure_size, *align_count, *align_list, error_text);
	/*	**************************************************************	*/

EXIT_FUNCTION:

	if (return_code != GENFUNCS_SUCCESS) {
		if (*count_list != NULL)
			free(*count_list);
		if (*index_list != NULL)
			free(*index_list);
		if (*size_list != NULL)
			free(*size_list);
		if (*align_list != NULL)
			free(*align_list);
		*count_list     = NULL;
		*index_list     = NULL;
		*size_list      = NULL;
		*structure_size = 0;
		*align_count    = 0;
		*align_list     = NULL;
	}

	if (tmp_align_list != NULL) {
		free(tmp_align_list);
		tmp_align_list = NULL;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_ALIGN_BASIC_AlignString

   SYNOPSIS    :  return_code = GEN_ALIGN_BASIC_AlignString(type_count,
							type_list, normalize_flag, adjust_char_flag,
							separator_list, spec_string, structure_size, align_count,
							align_list, error_text);

						int                    return_code;

						unsigned int           type_count;

						const GEN_ALIGN_SPEC  *type_list;

						int                    normalize_flag;

						int                    adjust_char_flag;

						const char            *separator_list;

						char                  *spec_string;

						unsigned int          *structure_size;

						unsigned int          *align_count;

						GEN_ALIGN            **align_list;

						char                  *error_text;

   DESCRIPTION :  Transforms a string specification of the members of a
						structure into an array of structures of type
						''GEN_ALIGN'', the elements of which contain
						offset and length data for each member.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``type_count`` is the number of elements in the array
						represented by the ``type_list`` parameter.

						(.) ``type_list`` is an array of ''GEN_ALIGN_SPEC''
						structures which describe a machine architecture in terms
						of the primitive data types available on that architecture.

						(-) If ``type_count`` is ''0'' and ``type_list`` is
						''NULL'', the function will use the built-in primitive
						data type list compiled into the module ``genalign.c``
						under the names ``GEN_ALIGN_TypeCount`` and
						``GEN_ALIGN_TypeList``.

						(.) ``normalize_flag`` indicates whether the elements of
						the array ``align_list`` which results the operation of
						this function are to be normalized vis-a-vis each other.

						(-) Normalization is the combination of like data types from
						adjacent ``align_list`` elements into a single element.

						(-) For example, if ``align_list`` contains the adjacent
						elements resulting from operation of this function on the
						string:

{|-|}c[10],c[3]

						(-) Normalization of those elements will result in a single
						element equivalent to the string:

{|-|}c[13]

						(-) The ``normalize_flag`` parameter may take on one of the
						following two values:

						(..) ``GENFUNCS_TRUE``, which indicates that the elements
						are to be normalized.

						(..) ``GENFUNCS_FALSE``, which indicates that the elements
						are not to be normalized.

						(.) ``adjust_char_flag`` specifies that ''char'' (and
						''unsigned char'') arrays are to be increased in length
						by a single byte. This is usually to accomodate the
						inclusion of the ''C'' language string null terminator byte.

						(-) The ``adjust_char_flag`` parameter may take on one of
						the following two values:

						(..) ``GENFUNCS_TRUE``, which indicates that ''char''
						elements are to be adjusted.

						(..) ``GENFUNCS_FALSE``, which indicates that ''char''
						elements are not to be adjusted.

						(.) ``separator_list`` is an ASCII NUL (ASCII 0) terminated
						string which lists the characters to be used to separate
						discrete specifications in ``spec_string``.

						(-) if ``separator_list`` is ''NULL'', the comma character
						('','') will be used to separate specifications in
						``spec_string``.

   					(.) ``spec_string`` is the string which contains a list of
						member definitions separated by some combination of the
						characters in ``separator_list``. Leading and trailing
						``separator_string`` characters are ignored.

						(-) Each member definition has the following format:

						(--) { ''b''|''c''|''C''|''s''|''S''|''i''|''I''|''l''|''L''|''f''|''d'' }

						(-) where each letter has the following meaning:

						(..)''b'' is an unsigned (binary) char. The upper-case
						letter ''B'' is also allowed.

						(..)''c'' is a signed char.

						(..)''C'' is an unsigned char.

						(..)''s'' is a signed short integer.

						(..)''S'' is an unsigned short integer.

						(..)''i'' is a signed integer.

						(..)''I'' is an unsigned integer.

						(..)''l'' is a long integer.

						(..)''L'' is an unsigned long integer

						(..)''f'' is a float. The upper-case letter ''F'' is also
						allowed.

						(..)''d'' is a double. The upper-case letter ''D'' is also
						allowed.

						(-) A member definition may be followed by an optional
						array specifier of the form:

						(--) ``member-definition``[``array-length``]

						(-) Note that ``array-length`` must be greater than zero.

						(.) ``structure_size`` is a pointer to an ''unsigned int''
						into which will be placed the total size of the structure
						as determined by this function. The size will include
						any alignment bytes required by the implementation.

						(-) If ``structure_size`` is ''NULL'', it will not be
						de-referenced.

						(.) ``align_count`` is a pointer to an ''unsigned int'' into
						which will be placed the number of members which were
						parsed out of the string ``spec_string``.

						(.) ``align_list`` points to a pointer to a structure of
						type ''GEN_ALIGN''. If the function is
						successful, it will allocate memory sufficient to hold
						``align_count`` elements. Each element will describe the
						offset and length requirements for each member of the
						desired structure.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at
						least ''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if no error occurs.

						(.) One of the non-zero GENFUNCS Return Codes if an error
						occurs.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  GEN_ALIGN_AlignString
						GEN_ALIGN_BASIC_CheckMember
						GEN_ALIGN_BASIC_AlignList

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_ALIGN_BASIC_AlignString
						Alignment Functions:GEN_ALIGN_BASIC_AlignString
						GENFUNCS:Functions:GEN_ALIGN_BASIC_AlignString
						GENFUNCS:Alignment Functions:GEN_ALIGN_BASIC_AlignString
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_ALIGN_BASIC_AlignString

   PUBLISH NAME:	GEN_ALIGN_BASIC_AlignString

	ENTRY CLASS	:	Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int GEN_ALIGN_BASIC_AlignString(unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, int normalize_flag,
	int adjust_char_flag, const char *separator_list, const char *spec_string,
	unsigned int *structure_size, unsigned int *align_count,
	GEN_ALIGN **align_list, char *error_text)
#else
int GEN_ALIGN_BASIC_AlignString(type_count, type_list, normalize_flag,
	adjust_char_flag, separator_list, spec_string, structure_size, align_count,
	align_list, error_text)
unsigned int           type_count;
const GEN_ALIGN_SPEC  *type_list;
int                    normalize_flag;
int                    adjust_char_flag;
const char            *separator_list;
const char            *spec_string;
unsigned int          *structure_size;
unsigned int          *align_count;
GEN_ALIGN            **align_list;
char                  *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code;
	unsigned int   string_count = 0;
	char         **string_list  = NULL;
	unsigned int   count_1;
	char          *tmp_string;
	char          *tmp_ptr;

	*align_count    = 0;
	*align_list     = NULL;

	separator_list  = (separator_list != NULL) ? separator_list : ",";

	if ((tmp_string = strdup(spec_string)) == NULL) {
		strcpy(error_text, "Unable to copy string to temporary work area.");
		return_code = GENFUNCS_MEMORY_FAILURE;
   }
	else {
		tmp_ptr = tmp_string;
		while (*tmp_ptr) {
			if (strchr(separator_list, *tmp_ptr) != NULL)
				*tmp_ptr = ' ';
			tmp_ptr++;
      }
		oneblank(trim(ctltospc(tmp_string)));
		if (sepwordl(tmp_string, &string_count, &string_list)) {
			strcpy(error_text, "Unable to unpack string to list of data types.");
			return_code = GENFUNCS_MEMORY_FAILURE;
		}
		else if (!string_count) {
			strcpy(error_text, "No data types found in string.");
			return_code = GENFUNCS_FAILURE;
		}
		else {
			if ((*align_list = ((GEN_ALIGN *)
				calloc(string_count, sizeof(GEN_ALIGN)))) == NULL) {
				sprintf(error_text, "%s (data types = %u * size %u = %u).",
					"Unable to allocate storage for list", string_count,
					sizeof(GEN_ALIGN), string_count * sizeof(GEN_ALIGN));
				return_code = GENFUNCS_FAILURE;
			}
			else {
				*align_count = string_count;
				return_code  = 0;
				for (count_1 = 0; count_1 < string_count; count_1++) {
					if ((return_code =
						GEN_ALIGN_BASIC_CheckMember(type_count, type_list,
						string_list[count_1], *align_list + count_1,
						error_text)) != GENFUNCS_SUCCESS)
						break;
				}
				if (return_code == GENFUNCS_SUCCESS) {
					if (normalize_flag)
						GEN_ALIGN_NormalizeList(align_count, align_list);
					if (adjust_char_flag) {
						for (count_1 = 0; count_1 < string_count; count_1++) {
							if (((*align_list)[count_1].type == GEN_C_ALIGN_char) ||
								((*align_list)[count_1].type ==
								GEN_C_ALIGN_unsigned_char))
								(*align_list)[count_1].array_length++;
						}
					}
					return_code = GEN_ALIGN_BASIC_AlignList(type_count, type_list,
						structure_size, *align_count, *align_list, error_text);
				}
				if (return_code != GENFUNCS_SUCCESS) {
					if (*align_list)
						free(*align_list);
					*align_count = 0;
					*align_list  = NULL;
				}
			}
			strl_remove_all(&string_count, &string_list);
		}
		free(tmp_string);
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_ALIGN_BASIC_CountStringToList

   SYNOPSIS    :  return_code = GEN_ALIGN_BASIC_CountStringToList(type_count,
							type_list, normalize_flag, adjust_char_flag,
							separator_list, in_spec_count, in_spec_string,
							structure_size, align_count, align_list, error_text);

						int                    return_code;

						unsigned int           type_count;

						const GEN_ALIGN_SPEC  *type_list;

						int                    normalize_flag;

						int                    adjust_char_flag;

						const char            *separator_list;

						unsigned int           in_spec_count;

						const char            *in_spec_string;

						unsigned int          *structure_size;

						unsigned int          *align_count;

						GEN_ALIGN            **align_list;

						char                  *error_text;

   DESCRIPTION :  Transforms an string specification (and associated instance
						count) of the members of a structure into an array of
						structures of type ''GEN_ALIGN''.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``type_count`` is the number of elements in the array
						represented by the ``type_list`` parameter.

						(.) ``type_list`` is an array of ''GEN_ALIGN_SPEC''
						structures which describe a machine architecture in terms
						of the primitive data types available on that architecture.

						(-) If ``type_count`` is ''0'' and ``type_list`` is
						''NULL'', the function will use the built-in primitive
						data type list compiled into the module ``genalign.c``
						under the names ``GEN_ALIGN_TypeCount`` and
						``GEN_ALIGN_TypeList``.

						(.) ``normalize_flag`` indicates whether the elements of
						the array ``align_list`` which results the operation of
						this function are to be normalized vis-a-vis each other.

						(-) Normalization is the combination of like data types from
						adjacent ``align_list`` elements into a single element.

						(-) For example, if ``align_list`` contains the adjacent
						elements resulting from operation of this function on the
						string:

{|-|}c[10],c[3]

						(-) Normalization of those elements will result in a single
						element equivalent to the string:

{|-|}c[13]

						(-) The ``normalize_flag`` parameter may take on one of the
						following two values:

						(..) ``GENFUNCS_TRUE``, which indicates that the elements
						are to be normalized.

						(..) ``GENFUNCS_FALSE``, which indicates that the elements
						are not to be normalized.

						(.) ``adjust_char_flag`` specifies that ''char'' (and
						''unsigned char'') arrays are to be increased in length
						by a single byte. This is usually to accomodate the
						inclusion of the ''C'' language string null terminator byte.

						(-) The ``adjust_char_flag`` parameter may take on one of
						the following two values:

						(..) ``GENFUNCS_TRUE``, which indicates that ''char''
						elements are to be adjusted.

						(..) ``GENFUNCS_FALSE``, which indicates that ''char''
						elements are not to be adjusted.

						(.) ``separator_list`` is an ASCII NUL (ASCII 0) terminated
						string which lists the characters to be used to separate
						discrete specifications in ``spec_string``.

						(-) if ``separator_list`` is ''NULL'', the comma character
						('','') will be used to separate specifications in
						``spec_string``.

						(.) ``in_spec_count`` is the number of instances
						``in_spec_string`` is to be repeated to produce
						``align_list``.

   					(.) ``in_spec_string`` is the string which contains a list
						of member definitions separated by some combination of the
						characters in ``separator_list``. Leading and trailing
						``separator_string`` characters are ignored.

						(-) Each member definition has the following format:

						(--) { ''b''|''c''|''C''|''s''|''S''|''i''|''I''|''l''|''L''|''f''|''d'' }

						(-) where each letter has the following meaning:

						(..)''b'' is an unsigned (binary) char. The upper-case
						letter ''B'' is also allowed.

						(..)''c'' is a signed char.

						(..)''C'' is an unsigned char.

						(..)''s'' is a signed short integer.

						(..)''S'' is an unsigned short integer.

						(..)''i'' is a signed integer.

						(..)''I'' is an unsigned integer.

						(..)''l'' is a long integer.

						(..)''L'' is an unsigned long integer

						(..)''f'' is a float. The upper-case letter ''F'' is also
						allowed.

						(..)''d'' is a double. The upper-case letter ''D'' is also
						allowed.

						(-) A member definition may be followed by an optional
						array specifier of the form:

						(--) ``member-definition``[``array-length``]

						(-) Note that ``array-length`` must be greater than zero.

						(.) ``structure_size`` is a pointer to an ''unsigned int''
						into which will be placed the total size of the structure
						as determined by this function. The size will include
						any alignment bytes required by the implementation.

						(-) If ``structure_size`` is ''NULL'', it will not be
						de-referenced.

						(.) ``align_count`` is a pointer to an ''unsigned int'' into
						which will be placed the number of members which were
						parsed out of the string ``spec_string``.

						(.) ``align_list`` points to a pointer to a structure of
						type ''GEN_ALIGN''. If the function is
						successful, it will allocate memory sufficient to hold
						``align_count`` elements. Each element will describe the
						offset and length requirements for each member of the
						desired structure.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at
						least ''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if no error occurs.

						(.) One of the non-zero GENFUNCS Return Codes if an error
						occurs.

   NOTES       :  If you want to append members parsed out of the
						``in_spec_string`` parameter to the list represented by
						``align_count`` and ``align_list``, use the related function
						``GEN_ALIGN_BASIC_CountStringToLApp``.

   CAVEATS     :  

   SEE ALSO    :  GEN_ALIGN_BASIC_CountStringToString
						GEN_ALIGN_BASIC_CountStringToLApp
						GEN_ALIGN_CountStringToList

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_ALIGN_BASIC_CountStringToList
						Alignment Functions:GEN_ALIGN_BASIC_CountStringToList
						GENFUNCS:Functions:GEN_ALIGN_BASIC_CountStringToList
						GENFUNCS:Alignment Functions:GEN_ALIGN_BASIC_CountStringToList
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_ALIGN_BASIC_CountStringToList

   PUBLISH NAME:	GEN_ALIGN_BASIC_CountStringToList

	ENTRY CLASS	:	Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int GEN_ALIGN_BASIC_CountStringToList(unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, int normalize_flag, int adjust_char_flag,
	const char *separator_list, unsigned int in_spec_count,
	const char *in_spec_string, unsigned int *structure_size,
	unsigned int *align_count, GEN_ALIGN **align_list, char *error_text)
#else
int GEN_ALIGN_BASIC_CountStringToList(type_count, type_list, normalize_flag,
	adjust_char_flag, separator_list, in_spec_count, in_spec_string,
	structure_size, align_count, align_list, error_text)
unsigned int           type_count;
const GEN_ALIGN_SPEC  *type_list;
int                    normalize_flag;
int                    adjust_char_flag;
const char            *separator_list;
unsigned int           in_spec_count;
const char            *in_spec_string;
unsigned int          *structure_size;
unsigned int          *align_count;
GEN_ALIGN            **align_list;
char                  *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code;
	unsigned int  tmp_align_count = 0;
	GEN_ALIGN    *tmp_align_list  = NULL;
	unsigned int  tmp_structure_size;
	unsigned int  count_1;
	unsigned int  count_2;

	structure_size = (structure_size == NULL) ? &tmp_structure_size :
		structure_size;
	*align_count   = 0;
	*align_list    = NULL;

	if (!in_spec_count) {
		strcpy(error_text, "The number of type specifiers is zero ('0').");
		return_code = GENFUNCS_BAD_ARGS_FAILURE;
	}
	else if ((return_code = GEN_ALIGN_BASIC_AlignString(type_count, type_list,
		normalize_flag, GENFUNCS_FALSE, separator_list, in_spec_string,
		structure_size, &tmp_align_count, &tmp_align_list, error_text)) ==
		GENFUNCS_SUCCESS) {
		if (in_spec_count == 1) {
			*align_count   = tmp_align_count;
			*align_list    = tmp_align_list;
			tmp_align_list = NULL;
		}
		else if (tmp_align_count == 1) {
			*align_count                 = tmp_align_count;
			*align_list                  = tmp_align_list;
			(*align_list)->array_length  = in_spec_count;
			(*align_list)->length       *= in_spec_count;
			*structure_size             *= in_spec_count;
			tmp_align_list               = NULL;
		}
		else if ((*align_list = ((GEN_ALIGN *)
			calloc(tmp_align_count * in_spec_count,
			sizeof(**align_list)))) == NULL) {
			GEN_AllocMsgList(tmp_align_count * in_spec_count,
				sizeof(**align_list), error_text,
				"Unable to allocate the alignment list");
			return_code = GENFUNCS_MEMORY_FAILURE;
		}
		else {
			*structure_size *= in_spec_count;
			*align_count     = tmp_align_count * in_spec_count;
			for (count_1 = 0; count_1 < in_spec_count; count_1++) {
				for (count_2 = 0; count_2 < tmp_align_count; count_2++)
					(*align_list)[(count_1 * tmp_align_count) + count_2] =
						tmp_align_list[count_2];
			}
		}
		if (return_code == GENFUNCS_SUCCESS) {
			for (count_1 = 0; count_1 < *align_count; count_1++)
				(*align_list)[count_1].array_length +=
					(((*align_list)[count_1].type == GEN_C_ALIGN_char) ||
					((*align_list)[count_1].type == GEN_C_ALIGN_unsigned_char)) ?
					((adjust_char_flag == GENFUNCS_TRUE) ? 1 : 0) : 0;
			return_code = GEN_ALIGN_BASIC_AlignList(type_count, type_list,
				structure_size, *align_count, *align_list, error_text);
		}
		if (tmp_align_list != NULL)
			free(tmp_align_list);
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_ALIGN_BASIC_CountStringToLApp

   SYNOPSIS    :  return_code =
							GEN_ALIGN_BASIC_CountStringToLApp(type_count,
							type_list, normalize_flag, adjust_char_flag,
							separator_list, in_spec_count, in_spec_string,
							structure_size, align_count, align_list, error_text);

						int                    return_code;

						unsigned int           type_count;

						const GEN_ALIGN_SPEC  *type_list;

						int                    normalize_flag;

						int                    adjust_char_flag;

						const char            *separator_list;

						unsigned int           in_spec_count;

						const char            *in_spec_string;

						unsigned int          *structure_size;

						unsigned int          *align_count;

						GEN_ALIGN            **align_list;

						char                  *error_text;

   DESCRIPTION :  Transforms an string specification (and associated instance
						count) of the members of a structure into an array of
						structures of type ''GEN_ALIGN''. These structures are then
						appended to the list represented by the ``align_count`` and
						``align_list`` parameters.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``type_count`` is the number of elements in the array
						represented by the ``type_list`` parameter.

						(.) ``type_list`` is an array of ''GEN_ALIGN_SPEC''
						structures which describe a machine architecture in terms
						of the primitive data types available on that architecture.

						(-) If ``type_count`` is ''0'' and ``type_list`` is
						''NULL'', the function will use the built-in primitive
						data type list compiled into the module ``genalign.c``
						under the names ``GEN_ALIGN_TypeCount`` and
						``GEN_ALIGN_TypeList``.

						(.) ``normalize_flag`` indicates whether the elements of
						the array ``align_list`` which results the operation of
						this function are to be normalized vis-a-vis each other.

						(-) Normalization is the combination of like data types from
						adjacent ``align_list`` elements into a single element.

						(-) For example, if ``align_list`` contains the adjacent
						elements resulting from operation of this function on the
						string:

{|-|}c[10],c[3]

						(-) Normalization of those elements will result in a single
						element equivalent to the string:

{|-|}c[13]

						(-) The ``normalize_flag`` parameter may take on one of the
						following two values:

						(..) ``GENFUNCS_TRUE``, which indicates that the elements
						are to be normalized.

						(..) ``GENFUNCS_FALSE``, which indicates that the elements
						are not to be normalized.

						(.) ``adjust_char_flag`` specifies that ''char'' (and
						''unsigned char'') arrays are to be increased in length
						by a single byte. This is usually to accomodate the
						inclusion of the ''C'' language string null terminator byte.

						(-) The ``adjust_char_flag`` parameter may take on one of
						the following two values:

						(..) ``GENFUNCS_TRUE``, which indicates that ''char''
						elements are to be adjusted.

						(..) ``GENFUNCS_FALSE``, which indicates that ''char''
						elements are not to be adjusted.

						(.) ``separator_list`` is an ASCII NUL (ASCII 0) terminated
						string which lists the characters to be used to separate
						discrete specifications in ``spec_string``.

						(-) if ``separator_list`` is ''NULL'', the comma character
						('','') will be used to separate specifications in
						``spec_string``.

						(.) ``in_spec_count`` is the number of instances
						``in_spec_string`` is to be repeated to produce
						``align_list``.

   					(.) ``in_spec_string`` is the string which contains a list
						of member definitions separated by some combination of the
						characters in ``separator_list``. Leading and trailing
						``separator_string`` characters are ignored.

						(-) Each member definition has the following format:

						(--) { ''b''|''c''|''C''|''s''|''S''|''i''|''I''|''l''|''L''|''f''|''d'' }

						(-) where each letter has the following meaning:

						(..)''b'' is an unsigned (binary) char. The upper-case
						letter ''B'' is also allowed.

						(..)''c'' is a signed char.

						(..)''C'' is an unsigned char.

						(..)''s'' is a signed short integer.

						(..)''S'' is an unsigned short integer.

						(..)''i'' is a signed integer.

						(..)''I'' is an unsigned integer.

						(..)''l'' is a long integer.

						(..)''L'' is an unsigned long integer

						(..)''f'' is a float. The upper-case letter ''F'' is also
						allowed.

						(..)''d'' is a double. The upper-case letter ''D'' is also
						allowed.

						(-) A member definition may be followed by an optional
						array specifier of the form:

						(--) ``member-definition``[``array-length``]

						(-) Note that ``array-length`` must be greater than zero.

						(.) ``structure_size`` is a pointer to an ''unsigned int''
						into which will be placed the total size of the structure
						as determined by this function. The size will include
						any alignment bytes required by the implementation.

						(-) If ``structure_size`` is ''NULL'', it will not be
						de-referenced.

						(.) ``align_count`` is a pointer to an ''unsigned int''
						which will be increased by the number of members which were
						parsed out of the string ``spec_string``.

						(.) ``align_list`` points to a pointer to a structure of
						type ''GEN_ALIGN''. If the function is
						successful, it will allocate memory sufficient to hold
						``align_count`` elements. Each element will describe the
						offset and length requirements for each member of the
						desired structure.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at
						least ''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if no error occurs.

						(.) One of the non-zero GENFUNCS Return Codes if an error
						occurs.

   NOTES       :  This function appends members parsed out of the
						``in_spec_string`` parameter to the list represented by
						``align_count`` and ``align_list``. If you do not want
						this behavior, use the related function
						``GEN_ALIGN_BASIC_CountStringToList``.

   CAVEATS     :  

   SEE ALSO    :  GEN_ALIGN_BASIC_CountStringToList
						GEN_ALIGN_CountStringToLApp

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_ALIGN_BASIC_CountStringToLApp
						Alignment Functions:GEN_ALIGN_BASIC_CountStringToLApp
						GENFUNCS:Functions:GEN_ALIGN_BASIC_CountStringToLApp
						GENFUNCS:Alignment Functions:GEN_ALIGN_BASIC_CountStringToLApp
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_ALIGN_BASIC_CountStringToLApp

   PUBLISH NAME:	GEN_ALIGN_BASIC_CountStringToLApp

	ENTRY CLASS	:	Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int GEN_ALIGN_BASIC_CountStringToLApp(unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, int normalize_flag, int adjust_char_flag,
	const char *separator_list, unsigned int in_spec_count,
	const char *in_spec_string, unsigned int *structure_size,
	unsigned int *align_count, GEN_ALIGN **align_list, char *error_text)
#else
int GEN_ALIGN_BASIC_CountStringToLApp(type_count, type_list, normalize_flag,
	adjust_char_flag, separator_list, in_spec_count, in_spec_string,
	structure_size, align_count, align_list, error_text)
unsigned int           type_count;
const GEN_ALIGN_SPEC  *type_list;
int                    normalize_flag;
int                    adjust_char_flag;
const char            *separator_list;
unsigned int           in_spec_count;
const char            *in_spec_string;
unsigned int          *structure_size;
unsigned int          *align_count;
GEN_ALIGN            **align_list;
char                  *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code;
	unsigned int  tmp_align_count = 0;
	GEN_ALIGN    *tmp_align_list  = NULL;
	GEN_ALIGN    *tmp_new_list;
	unsigned int  tmp_structure_size;

	structure_size = (structure_size == NULL) ? &tmp_structure_size :
		structure_size;

	if ((return_code = GEN_ALIGN_BASIC_CountStringToList(type_count, type_list,
		normalize_flag, adjust_char_flag, separator_list, in_spec_count,
		in_spec_string, structure_size, &tmp_align_count, &tmp_align_list,
		error_text)) == GENFUNCS_SUCCESS) {
		if ((tmp_new_list = ((GEN_ALIGN *)
			calloc(*align_count + tmp_align_count, sizeof(GEN_ALIGN)))) == NULL){
			GEN_AllocMsgList(*align_count + tmp_align_count, sizeof(GEN_ALIGN),
				error_text, "Unable to allocate the alignment list");
			return_code = GENFUNCS_MEMORY_FAILURE;
		}
		else {
			memcpy(tmp_new_list, *align_list, *align_count * sizeof(GEN_ALIGN));
			memcpy(tmp_new_list + *align_count, tmp_align_list,
				tmp_align_count * sizeof(GEN_ALIGN));
			if ((return_code = GEN_ALIGN_BASIC_AlignList(type_count, type_list,
				structure_size, *align_count + tmp_align_count, tmp_new_list,
				error_text)) == GENFUNCS_SUCCESS) {
				free(*align_list);
				*align_count += tmp_align_count;
				*align_list   = tmp_new_list;
			}
			else
				free(tmp_new_list);
		}
		free(tmp_align_list);
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_ALIGN_BASIC_CountStringToString

   SYNOPSIS    :  return_code = GEN_ALIGN_BASIC_CountStringToString(type_count,
							type_list, normalize_flag, adjust_char_flag,
							separator_list, in_spec_count, in_spec_string,
							out_spec_string, error_text);

						int                    return_code;

						unsigned int           type_count;

						const GEN_ALIGN_SPEC  *type_list;

						int                    normalize_flag;

						int                    adjust_char_flag;

						const char            *separator_list;

						unsigned int           in_spec_count;

						const char            *in_spec_string;

						char                 **out_spec_string;

						char                  *error_text;

   DESCRIPTION :  Transforms an string specification (and associated instance
						count) of the members of a structure into an equivalent
						single string.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``type_count`` is the number of elements in the array
						represented by the ``type_list`` parameter.

						(.) ``type_list`` is an array of ''GEN_ALIGN_SPEC''
						structures which describe a machine architecture in terms
						of the primitive data types available on that architecture.

						(-) If ``type_count`` is ''0'' and ``type_list`` is
						''NULL'', the function will use the built-in primitive
						data type list compiled into the module ``genalign.c``
						under the names ``GEN_ALIGN_TypeCount`` and
						``GEN_ALIGN_TypeList``.

						(.) ``normalize_flag`` indicates whether the elements of
						the temporary ''GEN_ALIGN'' array used in the operation of
						this function are to be normalized vis-a-vis each other.

						(-) Normalization is the combination of like data types from
						adjacent ''GEN_ALIGN'' elements into a single element.

						(-) For example, if array of ''GEN_ALIGN'' elements contains
						the adjacent elements resulting from operation of this
						function on the string:

{|-|}c[10],c[3]

						(-) Normalization of those elements will result in a single
						element equivalent to the string:

{|-|}c[13]

						(-) The ``normalize_flag`` parameter may take on one of the
						following two values:

						(..) ``GENFUNCS_TRUE``, which indicates that the elements
						are to be normalized.

						(..) ``GENFUNCS_FALSE``, which indicates that the elements
						are not to be normalized.

						(.) ``adjust_char_flag`` specifies that ''char'' (and
						''unsigned char'') arrays are to be increased in length
						by a single byte. This is usually to accomodate the
						inclusion of the ''C'' language string null terminator byte.

						(-) The ``adjust_char_flag`` parameter may take on one of
						the following two values:

						(..) ``GENFUNCS_TRUE``, which indicates that ''char''
						elements are to be adjusted.

						(..) ``GENFUNCS_FALSE``, which indicates that ''char''
						elements are not to be adjusted.

						(.) ``separator_list`` is an ASCII NUL (ASCII 0) terminated
						string which lists the characters to be used to separate
						discrete specifications in ``spec_string``.

						(-) if ``separator_list`` is ''NULL'', the comma character
						('','') will be used to separate specifications in
						``spec_string``.

						(.) ``in_spec_count`` is the number of instances
						``in_spec_string`` is to be repeated to produce the
						temporary ''GEN_ALIGN'' array.

   					(.) ``in_spec_string`` is the string which contains a list
						of member definitions separated by some combination of the
						characters in ``separator_list``. Leading and trailing
						``separator_string`` characters are ignored.

						(-) Each member definition has the following format:

						(--) { ''b''|''c''|''C''|''s''|''S''|''i''|''I''|''l''|''L''|''f''|''d'' }

						(-) where each letter has the following meaning:

						(..)''b'' is an unsigned (binary) char. The upper-case
						letter ''B'' is also allowed.

						(..)''c'' is a signed char.

						(..)''C'' is an unsigned char.

						(..)''s'' is a signed short integer.

						(..)''S'' is an unsigned short integer.

						(..)''i'' is a signed integer.

						(..)''I'' is an unsigned integer.

						(..)''l'' is a long integer.

						(..)''L'' is an unsigned long integer

						(..)''f'' is a float. The upper-case letter ''F'' is also
						allowed.

						(..)''d'' is a double. The upper-case letter ''D'' is also
						allowed.

						(-) A member definition may be followed by an optional
						array specifier of the form:

						(--) ``member-definition``[``array-length``]

						(-) Note that ``array-length`` must be greater than zero.

						(.) ``out_spec_string`` is a pointer to a pointer to
						''char'' which will be set to the memory allocated to store
						the instanced string representation specified by the
						combination of ``in_spec_count`` and ``in_spec_string``.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at
						least ''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if no error occurs.

						(.) One of the non-zero GENFUNCS Return Codes if an error
						occurs.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  GEN_ALIGN_BASIC_CountStringToList
						GEN_ALIGN_CountStringToString

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_ALIGN_BASIC_CountStringToString
						Alignment Functions:GEN_ALIGN_BASIC_CountStringToString
						GENFUNCS:Functions:GEN_ALIGN_BASIC_CountStringToString
						GENFUNCS:Alignment Functions:GEN_ALIGN_BASIC_CountStringToString
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_ALIGN_BASIC_CountStringToString

   PUBLISH NAME:	GEN_ALIGN_BASIC_CountStringToString

	ENTRY CLASS	:	Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int GEN_ALIGN_BASIC_CountStringToString(unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, int normalize_flag, int adjust_char_flag,
	const char *separator_list, unsigned int in_spec_count,
	const char *in_spec_string, char **out_spec_string, char *error_text)
#else
int GEN_ALIGN_BASIC_CountStringToString(type_count, type_list, normalize_flag,
	adjust_char_flag, separator_list, in_spec_count, in_spec_string,
	out_spec_string, error_text)
unsigned int           type_count;
const GEN_ALIGN_SPEC  *type_list;
int                    normalize_flag;
int                    adjust_char_flag;
const char            *separator_list;
unsigned int           in_spec_count;
const char            *in_spec_string;
char                 **out_spec_string;
char                  *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code;
	unsigned int  align_count;
	GEN_ALIGN    *align_list;

	if ((return_code = GEN_ALIGN_BASIC_CountStringToList(type_count,
		type_list, normalize_flag, adjust_char_flag, separator_list,
		in_spec_count, in_spec_string, NULL, &align_count, &align_list,
		error_text)) == GENFUNCS_SUCCESS) {
		return_code = GEN_ALIGN_BASIC_ListToStringAlloc(type_count, type_list,
			align_count, align_list, separator_list, out_spec_string,
			error_text);
		free(align_list);
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_ALIGN_BASIC_AlignList

   SYNOPSIS    :  return_code = GEN_ALIGN_BASIC_AlignList(type_count,
							type_list, structure_size, align_count, align_list,
							error_text);

						int                   return_code;

						unsigned int          type_count;

						const GEN_ALIGN_SPEC *type_list;

						unsigned int         *structure_size;

						unsigned int          align_count;

						GEN_ALIGN            *align_list;

						char                 *error_text;

   DESCRIPTION :  Given an array of structures of type ''GEN_ALIGN''
						with the ``type`` and ``array_length`` members populated,
						calculates the total structure size and offset and length
						of each member.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``type_count`` is the number of elements in the array
						represented by the ``type_list`` parameter.

						(.) ``type_list`` is an array of ''GEN_ALIGN_SPEC''
						structures which describe a machine architecture in terms
						of the primitive data types available on that architecture.

						(-) If ``type_count`` is ''0'' and ``type_list`` is
						''NULL'', the function will use the built-in primitive
						data type list compiled into the module ``genalign.c``
						under the names ``GEN_ALIGN_TypeCount`` and
						``GEN_ALIGN_TypeList``.

						(.) ``structure_size`` is a pointer to an ''unsigned int''
						into which will be placed the total size of the structure
						as determined by this function. The size will include
						any alignment bytes required by the implementation.

						(-) If ``structure_size`` is ''NULL'', it will not be
						de-referenced.

						(.) ``align_count`` is an ''unsigned int'' which contains
						the number of elements in the array ``align_list``.

						(.) ``align_list`` is an array of structures of type
						''GEN_ALIGN'' which contains ``align_count``
						elements. The members ``type`` and ``array_length`` of
						each element should contain the values for the desired
						structure.

						(-) If this function is successful, the ``offset``
						and ``length`` members of each element will be updated to
						describe the offset and length requirements for each member
						of the desired structure.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at
						least ''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if no error occurs.

						(.) One of the non-zero GENFUNCS Return Codes if an error
						occurs.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  GEN_ALIGN_AlignList
						GEN_ALIGN_BASIC_AlignString

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_ALIGN_BASIC_AlignList
						Alignment Functions:GEN_ALIGN_BASIC_AlignList
						GENFUNCS:Functions:GEN_ALIGN_BASIC_AlignList
						GENFUNCS:Alignment Functions:GEN_ALIGN_BASIC_AlignList
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_ALIGN_BASIC_AlignList

   PUBLISH NAME:	GEN_ALIGN_BASIC_AlignList

	ENTRY CLASS	:	Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int GEN_ALIGN_BASIC_AlignList(unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, unsigned int *structure_size,
	unsigned int align_count, GEN_ALIGN *align_list, char *error_text)
#else
int GEN_ALIGN_BASIC_AlignList(type_count, type_list, structure_size,
	align_count, align_list, error_text)
unsigned int          type_count;
const GEN_ALIGN_SPEC *type_list;
unsigned int         *structure_size;
unsigned int          align_count;
GEN_ALIGN            *align_list;
char                 *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code              = GENFUNCS_SUCCESS;
	unsigned int current_offset           = 0;
	unsigned int largest_data_type_index  = 0;
	unsigned int largest_data_type_length = 0;
	unsigned int count_1;
	unsigned int align_adjust;
	unsigned int tmp_structure_size;

	structure_size  = (structure_size == NULL) ? &tmp_structure_size :
		structure_size;

	if ((!type_count) && (type_list == NULL)) {
		type_count = GEN_ALIGN_TypeCount;
		type_list  = GEN_ALIGN_TypeList;
	}

	if (!align_count) {
		strcpy(error_text, "No data types in list.");
		return_code = GENFUNCS_BAD_ARGS_FAILURE;
	}
	else {
		for (count_1 = 0; count_1 < align_count; count_1++) {
			if (align_list[count_1].type >= type_count) {
				sprintf(error_text, "%s (%u) %s 0 through %u, inclusive.",
					"Invalid data-type number", align_list[count_1].type,
					"should be in the range", type_count - 1);
				return_code = GENFUNCS_FAILURE;
				break;
			}
			align_list[count_1].array_length =
				(!align_list[count_1].array_length) ? 1 :
				align_list[count_1].array_length;
			if ((type_list[align_list[count_1].type].type_align > 1) &&
				(type_list[align_list[count_1].type].type_length >
				largest_data_type_length)) {
				largest_data_type_index  = align_list[count_1].type;
				largest_data_type_length =
					type_list[align_list[count_1].type].type_length;
			}
			if ((type_list[align_list[count_1].type].type_align > 1) &&
				current_offset && ((align_adjust = (current_offset %
				type_list[align_list[count_1].type].type_align)) > 0))
				current_offset +=
					type_list[align_list[count_1].type].type_align - align_adjust;
			align_list[count_1].offset  = current_offset;
			align_list[count_1].length  =
				type_list[align_list[count_1].type].type_length *
				align_list[count_1].array_length;
			current_offset             += align_list[count_1].length;
		}
		if (return_code == GENFUNCS_SUCCESS) {
			if (largest_data_type_length && ((align_adjust = (current_offset %
				type_list[largest_data_type_index].type_align)) > 0))
				current_offset += type_list[largest_data_type_index].type_align -
					align_adjust;
			*structure_size = current_offset;
		}
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_ALIGN_BASIC_CheckStringList

   SYNOPSIS    :  return_code = GEN_ALIGN_BASIC_CheckStringList(type_count,
							type_list, separator_list, spec_count, spec_list,
							error_text);

						int                    return_code;

						unsigned int           type_count;

						const GEN_ALIGN_SPEC  *type_list;

						const char            *separator_list;

						unsigned int           spec_count;

						char                 **spec_list;

						char                  *error_text;

   DESCRIPTION :	Checks to ensure that an array of pointers to strings
						are valid specifications of the primitive type members of
						a structure.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``type_count`` is the number of elements in the array
						represented by the ``type_list`` parameter.

						(.) ``type_list`` is an array of ''GEN_ALIGN_SPEC''
						structures which describe a machine architecture in terms
						of the primitive data types available on that architecture.

						(-) If ``type_count`` is ''0'' and ``type_list`` is
						''NULL'', the function will use the built-in primitive
						data type list compiled into the module ``genalign.c``
						under the names ``GEN_ALIGN_TypeCount`` and
						``GEN_ALIGN_TypeList``.

						(.) ``separator_list`` is an ASCII NUL (ASCII 0) terminated
						string which lists the characters to be used to separate
						discrete specifications in the elements of ``spec_list``.

						(-) if ``separator_list`` is ''NULL'', the comma character
						('','') will be used to separate specifications in
						``spec_string``.

						(.) ``spec_count`` is the number of elements in the
						array ``spec_list``.

						(.) ``spec_list`` is a array of pointers to strings, each
						string of which is a primitive type specification having
						the following format:

						(--) { ''b''|''c''|''C''|''s''|''S''|''i''|''I''|''l''|''L''|''f''|''d'' }

						(-) where each letter has the following meaning:

						(..)''b'' is an unsigned (binary) char. The upper-case
						letter ''B'' is also allowed.

						(..)''c'' is a signed char.

						(..)''C'' is an unsigned char.

						(..)''s'' is a signed short integer.

						(..)''S'' is an unsigned short integer.

						(..)''i'' is a signed integer.

						(..)''I'' is an unsigned integer.

						(..)''l'' is a long integer.

						(..)''L'' is an unsigned long integer

						(..)''f'' is a float. The upper-case letter ''F'' is also
						allowed.

						(..)''d'' is a double. The upper-case letter ''D'' is also
						allowed.

						(-) A member definition may be followed by an optional
						array specifier of the form:

						(--) ``member-definition``[``array-length``]

						(-) Note that ``array-length`` must be greater than zero.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at
						least ''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if no error occurs.

						(.) One of the non-zero GENFUNCS return codes if an error
						occurs.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  GEN_ALIGN_CheckStringList
						GEN_ALIGN_BASIC_CheckString
						GEN_ALIGN_BASIC_AlignStringList

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_ALIGN_BASIC_CheckStringList
						Alignment Functions:GEN_ALIGN_BASIC_CheckStringList
						GENFUNCS:Functions:GEN_ALIGN_BASIC_CheckStringList
						GENFUNCS:Alignment Functions:GEN_ALIGN_BASIC_CheckStringList
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_ALIGN_BASIC_CheckStringList

   PUBLISH NAME:	GEN_ALIGN_BASIC_CheckStringList

	ENTRY CLASS	:	Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int GEN_ALIGN_BASIC_CheckStringList(unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, const char *separator_list,
	unsigned int spec_count, char **spec_list, char *error_text)
#else
int GEN_ALIGN_BASIC_CheckStringList(type_count, type_list, separator_list,
	spec_count, spec_list, error_text)
unsigned int           type_count;
const GEN_ALIGN_SPEC  *type_list;
const char            *separator_list;
unsigned int           spec_count;
char                 **spec_list;
char                  *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code;
	unsigned int *count_list;
	unsigned int *index_list;
	unsigned int *size_list;
	unsigned int  align_count;
	GEN_ALIGN    *align_list;

	if ((return_code = GEN_ALIGN_BASIC_AlignStringList(type_count, type_list,
		GENFUNCS_FALSE, GENFUNCS_FALSE, separator_list, spec_count, spec_list,
		&count_list, &index_list, &size_list, NULL, &align_count, &align_list,
		error_text)) == GENFUNCS_SUCCESS) {
		if (count_list != NULL)
			free(count_list);
		if (index_list != NULL)
			free(index_list);
		if (size_list != NULL)
			free(size_list);
		if (align_list != NULL)
			free(align_list);
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_ALIGN_BASIC_CheckString

   SYNOPSIS    :  return_code = GEN_ALIGN_BASIC_CheckString(type_count,
							type_list, separator_list, spec_string, error_text);

						int                    return_code;

						unsigned int           type_count;

						const GEN_ALIGN_SPEC  *type_list;

						const char            *separator_list;

						char                  *spec_string;

						char                  *error_text;

   DESCRIPTION :  Checks to ensure that a string is a valid specification of
						the primitive type members of a structure.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``type_count`` is the number of elements in the array
						represented by the ``type_list`` parameter.

						(.) ``type_list`` is an array of ''GEN_ALIGN_SPEC''
						structures which describe a machine architecture in terms
						of the primitive data types available on that architecture.

						(-) If ``type_count`` is ''0'' and ``type_list`` is
						''NULL'', the function will use the built-in primitive
						data type list compiled into the module ``genalign.c``
						under the names ``GEN_ALIGN_TypeCount`` and
						``GEN_ALIGN_TypeList``.

						(.) ``separator_list`` is an ASCII NUL (ASCII 0) terminated
						string which lists the characters to be used to separate
						discrete specifications in ``spec_string``.

						(-) if ``separator_list`` is ''NULL'', the comma character
						('','') will be used to separate specifications in
						``spec_string``.

   					(.) ``spec_string`` is the string which contains a list of
						member definitions separated by some combination of the
						characters in ``separator_list``. Leading and trailing
						``separator_string`` characters are ignored.

						(-) Each member definition has the following format:

						(--) { ''b''|''c''|''C''|''s''|''S''|''i''|''I''|''l''|''L''|''f''|''d'' }

						(-) where each letter has the following meaning:

						(..)''b'' is an unsigned (binary) char. The upper-case
						letter ''B'' is also allowed.

						(..)''c'' is a signed char.

						(..)''C'' is an unsigned char.

						(..)''s'' is a signed short integer.

						(..)''S'' is an unsigned short integer.

						(..)''i'' is a signed integer.

						(..)''I'' is an unsigned integer.

						(..)''l'' is a long integer.

						(..)''L'' is an unsigned long integer

						(..)''f'' is a float. The upper-case letter ''F'' is also
						allowed.

						(..)''d'' is a double. The upper-case letter ''D'' is also
						allowed.

						(-) A member definition may be followed by an optional
						array specifier of the form:

						(--) ``member-definition``[``array-length``]

						(-) Note that ``array-length`` must be greater than zero.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at
						least ''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if no error occurs.

						(.) One of the non-zero GENFUNCS Return Codes if an error
						occurs.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  GEN_ALIGN_CheckString
						GEN_ALIGN_BASIC_CheckStringList
						GEN_ALIGN_BASIC_AlignString

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_ALIGN_BASIC_CheckString
						Alignment Functions:GEN_ALIGN_BASIC_CheckString
						GENFUNCS:Functions:GEN_ALIGN_BASIC_CheckString
						GENFUNCS:Alignment Functions:GEN_ALIGN_BASIC_CheckString
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_ALIGN_BASIC_CheckString

   PUBLISH NAME:	GEN_ALIGN_BASIC_CheckString

	ENTRY CLASS	:	Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int GEN_ALIGN_BASIC_CheckString(unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, const char *separator_list,
	const char *spec_string, char *error_text)
#else
int GEN_ALIGN_BASIC_CheckString(type_count, type_list, separator_list,
	spec_string, error_text)
unsigned int          type_count;
const GEN_ALIGN_SPEC *type_list;
const char           *separator_list;
const char           *spec_string;
char                 *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code;
	unsigned int  align_count;
	GEN_ALIGN    *align_list;

	if ((return_code = GEN_ALIGN_BASIC_AlignString(type_count, type_list,
		GENFUNCS_FALSE, GENFUNCS_FALSE, separator_list, spec_string,
		NULL, &align_count, &align_list, error_text)) == GENFUNCS_SUCCESS) {
		if (align_list != NULL)
			free(align_list);
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_ALIGN_BASIC_CheckMember

   SYNOPSIS    :  return_code = GEN_ALIGN_BASIC_CheckMember(type_count,
							type_list, spec_string, align_ptr, error_text);

						int                   return_code;

						unsigned int          type_count;

						const GEN_ALIGN_SPEC *type_list;

						char                 *spec_string;

						GEN_ALIGN            *align_ptr;

						char                 *error_text;

   DESCRIPTION :  Determines whether a string member definition is correct.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``type_count`` is the number of elements in the array
						represented by the ``type_list`` parameter.

						(.) ``type_list`` is an array of ''GEN_ALIGN_SPEC''
						structures which describe a machine architecture in terms
						of the primitive data types available on that architecture.

						(-) If ``type_count`` is ''0'' and ``type_list`` is
						''NULL'', the function will use the built-in primitive
						data type list compiled into the module ``genalign.c``
						under the names ``GEN_ALIGN_TypeCount`` and
						``GEN_ALIGN_TypeList``.

						(.) ``spec_string`` is the string which contains a member
						definitions. Leading and trailing white-space characters
						are ignored.

						(-) The member definition has the following format:

						(--) { ''b''|''c''|''C''|''s''|''S''|''i''|''I''|''l''|''L''|''f''|''d'' }

						(-) where each letter has the following meaning:

						(..)''b'' is an unsigned (binary) char. The upper-case
						letter ''B'' is also allowed.

						(..) ''c'' is a signed char.

						(..) ''C'' is an unsigned char.

						(..) ''s'' is a signed short integer.

						(..) ''S'' is an unsigned short integer.

						(..) ''i'' is a signed integer.

						(..) ''I'' is an unsigned integer.

						(..) ''l'' is a long integer.

						(..) ''L'' is an unsigned long integer

						(..) ''f'' is a float. The upper-case letter ''F'' is also
						allowed.

						(..) ''d'' is a double. The upper-case letter ''D'' is also
						allowed.

						(-) The member definition may be followed by an optional
						array specifier of the form:

						(--) ``member-definition``[``array-length``]

						(-) Note that ``array-length`` must be greater than zero.

						(.) ``align_ptr`` points to a structure of type
						''GEN_ALIGN''. If the function is successful, it
						will update the ``type``, ``length``, and ``array_length``
						members of the structure to which ``align_ptr`` points.

						(-) Note, however, that if ``align_ptr`` is passed as a
						''NULL'' pointer, it will not be de-referenced.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at
						least ''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if no error occurs.

						(.) One of the non-zero GENFUNCS Return Codes if an error
						occurs.

	NOTES       :

   CAVEATS     :  

   SEE ALSO    :  GEN_ALIGN_BASIC_AlignString
						GEN_ALIGN_CheckMember

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

	OUTPUT INDEX:	GEN_ALIGN_BASIC_CheckMember
						Alignment Functions:GEN_ALIGN_BASIC_CheckMember
						GENFUNCS:Functions:GEN_ALIGN_BASIC_CheckMember
						GENFUNCS:Alignment Functions:GEN_ALIGN_BASIC_CheckMember
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_ALIGN_BASIC_CheckMember

   PUBLISH NAME:	GEN_ALIGN_BASIC_CheckMember

	ENTRY CLASS	:	Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int GEN_ALIGN_BASIC_CheckMember(unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, const char *spec_string,
	GEN_ALIGN *align_ptr, char *error_text)
#else
int GEN_ALIGN_BASIC_CheckMember(type_count, type_list, spec_string, align_ptr,
	error_text)
unsigned int          type_count;
const GEN_ALIGN_SPEC *type_list;
const char           *spec_string;
GEN_ALIGN            *align_ptr;
char                 *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = GENFUNCS_SUCCESS;
	GEN_ALIGN    align_data;
	unsigned int count_1;
	int          qual_length;
	long         array_length;

	if ((!type_count) && (type_list == NULL)) {
		type_count = GEN_ALIGN_TypeCount;
		type_list  = GEN_ALIGN_TypeList;
	}

	if ((spec_string == NULL) || (!(*spec_string))) {
		strcpy(error_text, "Empty member specification encountered.");
		return_code = GENFUNCS_BAD_ARGS_FAILURE;
	}
	else {
		GEN_ALIGN_InitAlign(&align_data);
		if (GEN_ALIGN_BASIC_FindTypeCharIndex(type_count, type_list,
			*spec_string, &align_data.type) != GENFUNCS_TRUE) {
			sprintf(error_text, "%s ('%-.100s') --- should be one of '",
				"Unknown type specifier encountered", spec_string);
			for (count_1 = 0; count_1 < type_count; count_1++)
				strcat(chrcat(error_text, type_list[count_1].type_abbreviation),
					(count_1 == (type_count - 1)) ? "'." :
					(count_1 == (type_count - 2)) ? "', or '" : "', '");
			return_code = GENFUNCS_FAILURE;
		}
		else {
			if ((qual_length = strlen(spec_string)) == 1)
				align_data.array_length = 1;
			else if ((qual_length < 4) || (spec_string[1] != '[') ||
				(spec_string[qual_length - 1] != ']') ||
				((array_length = atol(spec_string + 2)) < 1L) ||
				(array_length > ((long) INT_MAX))) {
				sprintf(error_text,
					"Invalid array specification encountered ('%-.100s').",
					spec_string);
				return_code = GENFUNCS_FAILURE;
			}
			else
				align_data.array_length = ((unsigned int) array_length);
			if ((return_code == GENFUNCS_SUCCESS) && (align_ptr != NULL)) {
				align_data.length = align_data.array_length *
					type_list[align_data.type].type_length;
				*align_ptr        = align_data;
			}
		}
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_ALIGN_BASIC_ListToStringAlloc

   SYNOPSIS    :  return_code = GEN_ALIGN_BASIC_ListToStringAlloc(type_count,
							type_list, align_count, align_list, separator_char,
							spec_string, error_text);

						int                    return_code;

						unsigned int           type_count;

						const GEN_ALIGN_SPEC  *type_list;

						unsigned int           align_count;

						const GEN_ALIGN       *align_list;

						const char            *separator_char;

						char                 **spec_string;

						char                  *error_text;

   DESCRIPTION :  Converts an array of ''GEN_ALIGN'' structures to an
						equivalent string representation, for which this function
						allocates memory.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``type_count`` is the number of elements in the array
						represented by the ``type_list`` parameter.

						(.) ``type_list`` is an array of ''GEN_ALIGN_SPEC''
						structures which describe a machine architecture in terms
						of the primitive data types available on that architecture.

						(-) If ``type_count`` is ''0'' and ``type_list`` is
						''NULL'', the function will use the built-in primitive
						data type list compiled into the module ``genalign.c``
						under the names ``GEN_ALIGN_TypeCount`` and
						``GEN_ALIGN_TypeList``.

						(.) ``align_count`` is the number of elements in the array
						``align_list``.

						(.) ``align_list`` is the array of ''GEN_ALIGN'' structures
						which is to be converted to a string.

						(.) ``separator_char`` points to the character to be used
						to separated the string representations of each of the
						elements in ``align_list``.

						(-) if ``separator_char`` is ''NULL'', the comma character
						('','') will be used to separate the string representations.

						(.) ``spec_string`` is a pointer to a pointer to ''char''
						which will be set to the memory allocated to store the
						string representation of ``align_list``.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at
						least ''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if no error occurs.

						(.) One of the non-zero GENFUNCS Return Codes if an error
						occurs.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  GEN_ALIGN_BASIC_ListToString
						GEN_ALIGN_CalcListToStringLen
						GEN_ALIGN_ListToStringAlloc

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_ALIGN_BASIC_ListToStringAlloc
						Alignment Functions:GEN_ALIGN_BASIC_ListToStringAlloc
						GENFUNCS:Functions:GEN_ALIGN_BASIC_ListToStringAlloc
						GENFUNCS:Alignment Functions:GEN_ALIGN_BASIC_ListToStringAlloc
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_ALIGN_BASIC_ListToStringAlloc

   PUBLISH NAME:	GEN_ALIGN_BASIC_ListToStringAlloc

	ENTRY CLASS	:	Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int GEN_ALIGN_BASIC_ListToStringAlloc(unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, unsigned int align_count,
	const GEN_ALIGN *align_list, const char *separator_char,
	char **spec_string, char *error_text)
#else
int GEN_ALIGN_BASIC_ListToStringAlloc(type_count, type_list, align_count,
	align_list, separator_char, spec_string, error_text)
unsigned int           type_count;
const GEN_ALIGN_SPEC  *type_list;
unsigned int           align_count;
const GEN_ALIGN       *align_list;
const char            *separator_char;
char                 **spec_string;
char                  *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = GENFUNCS_SUCCESS;
	unsigned int string_length;

	*spec_string = NULL;

	if (align_count) {
		string_length = GEN_ALIGN_CalcListToStringLen(align_count, align_list);
		if ((*spec_string = ((char *) calloc(string_length, sizeof(char)))) ==
			NULL) {
			GEN_AllocMsgItem(string_length, error_text,
				"Unable to allocate the alignment specification string");
			return_code = GENFUNCS_MEMORY_FAILURE;
		}
		else if ((return_code = GEN_ALIGN_BASIC_ListToString(type_count,
			type_list, align_count, align_list, separator_char, *spec_string,
			error_text)) != GENFUNCS_SUCCESS) {
			free(*spec_string);
			*spec_string = NULL;
		}
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_ALIGN_BASIC_ListToString

   SYNOPSIS    :  return_code = GEN_ALIGN_BASIC_ListToString(type_count,
							type_list, align_count, align_list, separator_char,
							spec_string, error_text);

						int                   return_code;

						unsigned int          type_count;

						const GEN_ALIGN_SPEC *type_list;

						unsigned int          align_count;

						const GEN_ALIGN      *align_list;

						const char           *separator_char;

						char                 *spec_string;

						char                 *error_text;

   DESCRIPTION :  Converts an array of ''GEN_ALIGN'' structures to an
						equivalent string representation.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``type_count`` is the number of elements in the array
						represented by the ``type_list`` parameter.

						(.) ``type_list`` is an array of ''GEN_ALIGN_SPEC''
						structures which describe a machine architecture in terms
						of the primitive data types available on that architecture.

						(-) If ``type_count`` is ''0'' and ``type_list`` is
						''NULL'', the function will use the built-in primitive
						data type list compiled into the module ``genalign.c``
						under the names ``GEN_ALIGN_TypeCount`` and
						``GEN_ALIGN_TypeList``.

						(.) ``align_count`` is the number of elements in the array
						``align_list``.

						(.) ``align_list`` is the array of ''GEN_ALIGN'' structures
						which is to be converted to a string.

						(.) ``separator_char`` points to the character to be used
						to separated the string representations of each of the
						elements in ``align_list``.

						(-) if ``separator_char`` is ''NULL'', the comma character
						('','') will be used to separate the string representations.

						(.) ``spec_string`` is a pointer to the memory allocated by
						the invoking function to store the string representation of
						``align_list``.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at
						least ''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if no error occurs.

						(.) One of the non-zero GENFUNCS Return Codes if an error
						occurs.

   NOTES       :  The string ``spec_string`` should be allocated with
						sufficient memory to store the string representation. The
						application programmer to determine the amount of memory
						required by calling the function
						``GEN_ALIGN_CalcListToStringLen`` to determine the memory
						needed and then ``malloc``ing that memory. Alternatively,
						the function related function
						``GEN_ALIGN_BASIC_ListToStringAlloc``, which allocates the
						proper amount of memory before performing the conversion
						could be used.

   CAVEATS     :  

   SEE ALSO    :  GEN_ALIGN_BASIC_ListToStringAlloc
						GEN_ALIGN_ListToString

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_ALIGN_BASIC_ListToString
						Alignment Functions:GEN_ALIGN_BASIC_ListToString
						GENFUNCS:Functions:GEN_ALIGN_BASIC_ListToString
						GENFUNCS:Alignment Functions:GEN_ALIGN_BASIC_ListToString
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_ALIGN_BASIC_ListToString

   PUBLISH NAME:	GEN_ALIGN_BASIC_ListToString

	ENTRY CLASS	:	Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int GEN_ALIGN_BASIC_ListToString(unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, unsigned int align_count,
	const GEN_ALIGN *align_list, const char *separator_char, char *spec_string,
	char *error_text)
#else
int GEN_ALIGN_BASIC_ListToString(type_count, type_list, align_count,
	align_list, separator_char, spec_string, error_text)
unsigned int          type_count;
const GEN_ALIGN_SPEC *type_list;
unsigned int          align_count;
const GEN_ALIGN      *align_list;
const char           *separator_char;
char                 *spec_string;
char                 *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code = GENFUNCS_SUCCESS;
	unsigned int  count_1;
	char         *spec_ptr;

	*spec_string    = '\0';
	spec_ptr        = spec_string;

	separator_char  = (separator_char != NULL) ? separator_char : ",";

	if ((!type_count) && (type_list == NULL)) {
		type_count = GEN_ALIGN_TypeCount;
		type_list  = GEN_ALIGN_TypeList;
	}

	for (count_1 = 0; count_1 < align_count; count_1++) {
		if (align_list[count_1].type >= type_count) {
			sprintf(error_text, "%s (%u) %s 0 through %u, inclusive.",
				"Invalid data-type number", align_list[count_1].type,
				"should be in the range", type_count - 1);
			spec_ptr    = spec_string;
			return_code = GENFUNCS_FAILURE;
			break;
		}
		*spec_ptr++ = type_list[align_list[count_1].type].type_abbreviation;
		if (align_list[count_1].array_length > 1) {
			sprintf(spec_ptr, "[%u]", align_list[count_1].array_length);
			spec_ptr += strlen(spec_ptr);
		}
		if (count_1 < (align_count - 1))
			*spec_ptr++ = *separator_char;
	}

	*spec_ptr = '\0';

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_ALIGN_BASIC_CopyTypeList

   SYNOPSIS    :  return_code = GEN_ALIGN_BASIC_CopyTypeList(in_type_count,
							in_type_list, out_type_count, out_type_list, error_text);

						int                    return_code;

						unsigned int           in_type_count;

						const GEN_ALIGN_SPEC  *in_type_list;

						unsigned int          *out_type_count;

						GEN_ALIGN_SPEC       **out_type_list;

						char                  *error_text;

   DESCRIPTION :  Copies a list of ''GEN_ALIGN_SPEC'' primitive type
						specifications.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_type_count`` is the number of elements in the array
						represented by the ``in_type_list`` parameter.

						(.) ``in_type_list`` is an array of ''GEN_ALIGN_SPEC''
						structures which describe a machine architecture in terms
						of the primitive data types available on that architecture.

						(-) If ``in_type_count`` is ''0'' and ``in_type_list`` is
						''NULL'', the function will use the built-in primitive
						data type list compiled into the module ``genalign.c``
						under the names ``GEN_ALIGN_TypeCount`` and
						``GEN_ALIGN_TypeList``.

						(.) ``out_type_count`` points to an ''unsigned int'' into
						which this function will place the number of elements
						copied into the array to which the ``out_type_list``
						parameter points.

						(.) ``out_type_list`` points to a pointer to
						''GEN_ALIGN_SPEC''. Memory will be allocated by this
						function and the pointer to that memory placed in the
						pointer to which ``out_type_list`` points.

   RETURNS     :  Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if the list was copied without
						error.

						(.) ''GENFUNCS_MEMORY_FAILURE'' if memory could not be
						allocated for the copy.

   CAVEATS     :  

   SEE ALSO    :  GEN_ALIGN_CopyTypeList

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_ALIGN_BASIC_CopyTypeList
						Alignment Functions:GEN_ALIGN_BASIC_CopyTypeList
						GENFUNCS:Functions:GEN_ALIGN_BASIC_CopyTypeList
						GENFUNCS:Alignment Functions:GEN_ALIGN_BASIC_CopyTypeList
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_ALIGN_BASIC_CopyTypeList

   PUBLISH NAME:	GEN_ALIGN_BASIC_CopyTypeList

	ENTRY CLASS	:	Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int GEN_ALIGN_BASIC_CopyTypeList(unsigned int in_type_count,
	const GEN_ALIGN_SPEC *in_type_list, unsigned int *out_type_count,
	GEN_ALIGN_SPEC **out_type_list,  char *error_text)
#else
int GEN_ALIGN_BASIC_CopyTypeList(in_type_count, in_type_list, out_type_count,
	out_type_list, error_text)
unsigned int           in_type_count;
const GEN_ALIGN_SPEC  *in_type_list;
unsigned int          *out_type_count;
GEN_ALIGN_SPEC       **out_type_list;
char                  *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = GENFUNCS_SUCCESS;

	*out_type_count = 0;
	*out_type_list  = NULL;

	if ((!in_type_count) && (in_type_list == NULL)) {
		in_type_count = GEN_ALIGN_TypeCount;
		in_type_list  = GEN_ALIGN_TypeList;
	}

	if ((*out_type_list = ((GEN_ALIGN_SPEC *) memdup(in_type_list,
		in_type_count * sizeof(*in_type_list)))) == NULL) {
		GEN_AllocMsgList(in_type_count, sizeof(*in_type_list), error_text,
			"Unable to allocate memory for the primitive type array");
		return_code = GENFUNCS_MEMORY_FAILURE;
	}
	else
		*out_type_count = in_type_count;

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_ALIGN_BASIC_FindTypeCharIndex

   SYNOPSIS    :  return_code = GEN_ALIGN_BASIC_FindTypeCharIndex(type_count,
							type_list, type_char, type_index);

						int                   return_code;

						unsigned int          type_count;

						const GEN_ALIGN_SPEC *type_list;

						int                   type_char;

						unsigned int         *type_index;

   DESCRIPTION :  Attempts to find the type indicated by the ``type_char``
						parameter in the array of primitive types.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``type_count`` is the number of elements in the array
						represented by the ``type_list`` parameter.

						(.) ``type_list`` is an array of ''GEN_ALIGN_SPEC''
						structures which describe a machine architecture in terms
						of the primitive data types available on that architecture.

						(-) If ``type_count`` is ''0'' and ``type_list`` is
						''NULL'', the function will use the built-in primitive
						data type list compiled into the module ``genalign.c``
						under the names ``GEN_ALIGN_TypeCount`` and
						``GEN_ALIGN_TypeList``.

						(.) ``type_char`` is the character to be matched against
						the ``type_abbreviation`` member of the structure
						''GEN_ALIGN_SPEC''.

						(.) ``type_index`` is a pointer to an ''unsigned long'' into
						which this function will place the index matching
						''GEN_ALIGN_SPEC'' element.

						(-) If ``type_index`` is ''NULL'', however, it will not be
						dereferenced.

   RETURNS     :  Returns from this function are as follow:

						(.) If ``type_char`` is found in the array of primitive
						types, this function returns ''GENFUNCS_TRUE''.

						(.) Otherwise, this function returns ''GENFUNCS_FALSE''.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  GEN_ALIGN_BASIC_FindTypeCharPtr
						GEN_ALIGN_FindTypeCharIndex

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_ALIGN_BASIC_FindTypeCharIndex
						Alignment Functions:GEN_ALIGN_BASIC_FindTypeCharIndex
						GENFUNCS:Functions:GEN_ALIGN_BASIC_FindTypeCharIndex
						GENFUNCS:Alignment Functions:GEN_ALIGN_BASIC_FindTypeCharIndex
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_ALIGN_BASIC_FindTypeCharIndex

   PUBLISH NAME:	GEN_ALIGN_BASIC_FindTypeCharIndex

	ENTRY CLASS	:	Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int GEN_ALIGN_BASIC_FindTypeCharIndex(unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, int type_char, unsigned int *type_index)
#else
int GEN_ALIGN_BASIC_FindTypeCharIndex(type_count, type_list, type_char,
	type_index)
unsigned int          type_count;
const GEN_ALIGN_SPEC *type_list;
int                   type_char;
unsigned int         *type_index;
#endif /* #ifndef NARGS */
{
	int          found_flag = GENFUNCS_FALSE;
	unsigned int count_1;

	if ((!type_count) && (type_list == NULL)) {
		type_count = GEN_ALIGN_TypeCount;
		type_list  = GEN_ALIGN_TypeList;
	}

	for (count_1 = 0; count_1 < type_count; count_1++) {
		if ((type_char == type_list[count_1].type_abbreviation) ||
			((type_char == 'B') &&
			(type_list[count_1].type_abbreviation == 'b')) ||
			((type_char == 'F') &&
			(type_list[count_1].type_abbreviation == 'f')) ||
			((type_char == 'D') &&
			(type_list[count_1].type_abbreviation == 'd')) ||
			((type_char == 'f') &&
			(type_list[count_1].type_abbreviation == 'F')) ||
			((type_char == 'd') &&
			(type_list[count_1].type_abbreviation == 'D'))) {
			if (type_index != NULL)
				*type_index = count_1;
			found_flag = GENFUNCS_TRUE;
			break;
		}
	}

	return(found_flag);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_ALIGN_BASIC_FindTypeCharPtr

   SYNOPSIS    :  return_ptr = GEN_ALIGN_BASIC_FindTypeCharPtr(type_count,
							type_list, type_char, type_index);

						const GEN_ALIGN_SPEC *return_ptr;

						unsigned int          type_count;

						const GEN_ALIGN_SPEC *type_list;

						int                   type_char;

						unsigned int         *type_index;

   DESCRIPTION :  Returns a pointer to the type indicated by the ``type_char``
						parameter in the array of primitive types.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``type_count`` is the number of elements in the array
						represented by the ``type_list`` parameter.

						(.) ``type_list`` is an array of ''GEN_ALIGN_SPEC''
						structures which describe a machine architecture in terms
						of the primitive data types available on that architecture.

						(-) If ``type_count`` is ''0'' and ``type_list`` is
						''NULL'', the function will use the built-in primitive
						data type list compiled into the module ``genalign.c``
						under the names ``GEN_ALIGN_TypeCount`` and
						``GEN_ALIGN_TypeList``.

						(.) ``type_char`` is the character to be matched against
						the ``type_abbreviation`` member of the structure
						''GEN_ALIGN_SPEC''.

						(.) ``type_index`` is a pointer to an ''unsigned long'' into
						which this function will place the index matching
						''GEN_ALIGN_SPEC'' element.

						(-) If ``type_index`` is ''NULL'', however, it will not be
						dereferenced.

   RETURNS     :  Returns from this function are as follow:

						(.) If ``type_char`` is found in the array of primitive
						types, a pointer to matching element in that array is
						returned.

						(.) Otherwise, this function returns ''NULL''.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  GEN_ALIGN_BASIC_FindTypeCharIndex
						GEN_ALIGN_FindTypeCharPtr

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_ALIGN_BASIC_FindTypeCharPtr
						Alignment Functions:GEN_ALIGN_BASIC_FindTypeCharPtr
						GENFUNCS:Functions:GEN_ALIGN_BASIC_FindTypeCharPtr
						GENFUNCS:Alignment Functions:GEN_ALIGN_BASIC_FindTypeCharPtr
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_ALIGN_BASIC_FindTypeCharPtr

   PUBLISH NAME:	GEN_ALIGN_BASIC_FindTypeCharPtr

	ENTRY CLASS	:	Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
const GEN_ALIGN_SPEC *GEN_ALIGN_BASIC_FindTypeCharPtr(unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, int type_char, unsigned int *type_index)
#else
const GEN_ALIGN_SPEC *GEN_ALIGN_BASIC_FindTypeCharPtr(type_count, type_list,
	type_char, type_index)
unsigned int          type_count;
const GEN_ALIGN_SPEC *type_list;
int                   type_char;
unsigned int         *type_index;
#endif /* #ifndef NARGS */
{
	const GEN_ALIGN_SPEC *return_ptr = NULL;
	unsigned int          tmp_type_index;

	if ((!type_count) && (type_list == NULL)) {
		type_count = GEN_ALIGN_TypeCount;
		type_list  = GEN_ALIGN_TypeList;
	}

	if (GEN_ALIGN_BASIC_FindTypeCharIndex(type_count, type_list, type_char,
		&tmp_type_index) == GENFUNCS_TRUE) {
		if (type_index != NULL)
			*type_index = tmp_type_index;
		return_ptr = type_list + tmp_type_index;
	}

	return(return_ptr);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_ALIGN_BASIC_GetTypePtr

   SYNOPSIS    :  return_ptr = GEN_ALIGN_BASIC_GetTypePtr(type_count,
							type_list, type_index);

						const GEN_ALIGN_SPEC *return_ptr;

						unsigned int          type_count;

						const GEN_ALIGN_SPEC *type_list;

						unsigned int          type_index;

   DESCRIPTION :  Returns a pointer to ''GEN_ALIGN_SPEC''

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``type_count`` is the number of elements in the array
						represented by the ``type_list`` parameter.

						(.) ``type_list`` is an array of ''GEN_ALIGN_SPEC''
						structures which describe a machine architecture in terms
						of the primitive data types available on that architecture.

						(-) If ``type_count`` is ''0'' and ``type_list`` is
						''NULL'', the function will use the built-in primitive
						data type list compiled into the module ``genalign.c``
						under the names ``GEN_ALIGN_TypeCount`` and
						``GEN_ALIGN_TypeList``.

						(.) ``type_index`` is the index into the array of primitive
						types for which a pointer is desired. It must be less than
						the total number of primitive types.

   RETURNS     :  Returns from this function are as follow:

						(.) If ``type_index`` is valid, a pointer to element
						indicated by ``type_index`` is returned.

						(.) Otherwise, this function returns ''NULL''.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  GEN_ALIGN_GetTypePtr

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_ALIGN_BASIC_GetTypePtr
						Alignment Functions:GEN_ALIGN_BASIC_GetTypePtr
						GENFUNCS:Functions:GEN_ALIGN_BASIC_GetTypePtr
						GENFUNCS:Alignment Functions:GEN_ALIGN_BASIC_GetTypePtr
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_ALIGN_BASIC_GetTypePtr

   PUBLISH NAME:	GEN_ALIGN_BASIC_GetTypePtr

	ENTRY CLASS	:	Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
const GEN_ALIGN_SPEC *GEN_ALIGN_BASIC_GetTypePtr(unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, unsigned int type_index)
#else
const GEN_ALIGN_SPEC *GEN_ALIGN_BASIC_GetTypePtr(type_count, type_list,
	type_index)
unsigned int          type_count;
const GEN_ALIGN_SPEC *type_list;
unsigned int          type_index;
#endif /* #ifndef NARGS */
{
	const GEN_ALIGN_SPEC *type_ptr = NULL;

	if ((!type_count) && (type_list == NULL)) {
		if (type_index < GEN_ALIGN_TypeCount)
			type_ptr = GEN_ALIGN_TypeList + type_index;
	}
	else if (type_index < type_count)
		type_ptr = type_list + type_index;

	return(type_ptr);
}
/* *********************************************************************** */

