/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Type Alignment (DTA) Functions Library Include File						*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the Data Type Alignment (DTA)
								library.

	Revision History	:	1992-02-23 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__DTA_H__h

# define h__DTA_H__h							1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <mbcompat.h>

#ifdef __MSDOS__
# ifndef HAS_RPC
#  define NO_RPC
# endif /* # ifndef HAS_RPC */
#elif _Windows
# ifndef HAS_RPC
#  define NO_RPC
# endif /* # ifndef HAS_RPC */
#else
# include <sys/types.h>
#endif /* #ifdef __MSDOS__ */

#ifndef NO_RPC
# include <rpc/rpc.h>
#else
# ifndef NO_RPC___BOOL_T_DEFINED
#  define bool_t			int
#  define NO_RPC___BOOL_T_DEFINED
# endif /* # ifndef NO_RPC___BOOL_T_DEFINED */
# ifndef NO_RPC___XDR_DEFINED
#  define NO_RPC___XDR_DEFINED
typedef struct { char x; } XDR;
#  define xdr_byte		NULL
#  define xdr_char		NULL
#  define xdr_u_char	NULL
#  define xdr_short	NULL
#  define xdr_u_short	NULL
#  define xdr_int		NULL
#  define xdr_u_int	NULL
#  define xdr_long		NULL
#  define xdr_u_long	NULL
#  define xdr_float	NULL
#  define xdr_double	NULL
# endif /* # ifndef NO_RPC___XDR_DEFINED */
#endif /* #ifndef NO_RPC */

#include <strfuncs.h>

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   BASE NAME   :  DTA Truth Codes

   NAME        :  DTA Truth Codes

   DESCRIPTION :  Manifest constants used within DTA to specify the truth
						or falsity of expressions.

						(.) ''DTA_TRUE''

						(.) ''DTA_FALSE''

   NOTES       :  The manifest constant ''DTA_TRUE'' should be defined as
						a non-zero value. Conversely, the manifest constant
						''DTA_FALSE'' should be defined as zero (''0'').

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:  DTA_TRUE
						DTA_FALSE
						DTA Truth Codes:DTA_TRUE
						DTA Truth Codes:DTA_FALSE
						DTA Manifest Constants:DTA_TRUE
						DTA Manifest Constants:DTA_FALSE
						DTA Defines:DTA_TRUE
						DTA Defines:DTA_FALSE
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:  DTA Truth Codes
						DTA Truth Code
						DTA truth codes
						DTA truth code
						DTA_TRUE
						DTA_FALSE

   PUBLISH NAME:	DTA Truth Codes
						DTA_TRUE
						DTA_FALSE

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define DTA_TRUE								1
#define DTA_FALSE								0
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   BASE NAME   :	DTA Return Codes

   NAME        :  DTA Return Codes

   DESCRIPTION :  The DTA return codes have the following meanings:

						(.) ''DTA_SUCCESS'' means that the function invoked
						completed without error. ''DTA_SUCCESS'' is guaranteed to
						be equal to zero (''0'').

						(.) ''DTA_FAILURE'' indicates that the function invoked
						encountered a general operation failure. This is the
						'catch-all' error code for those errors which do not fit
						into category of one the other DTA error codes.

						(.) ''DTA_BAD_ARGS_FAILURE'' indicates that the
						arguments passed to a function invoked were invalid.

						(.) ''DTA_MEMORY_FAILURE'' indicates that the memory
						required for operation of the function invoked could not be
						allocated.

						(.) ''DTA_SYSTEM_FAILURE'' indicates that the function
						invoked encountered a failure of a standard library
						function or a system call.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:  DTA_SUCCESS
						DTA_FAILURE
						DTA_BAD_ARGS_FAILURE
						DTA_MEMORY_FAILURE
						DTA_SYSTEM_FAILURE
						DTA Return Codes:DTA_SUCCESS
						DTA Return Codes:DTA_FAILURE
						DTA Return Codes:DTA_BAD_ARGS_FAILURE
						DTA Return Codes:DTA_MEMORY_FAILURE
						DTA Return Codes:DTA_SYSTEM_FAILURE
						DTA Manifest Constants:DTA_SUCCESS
						DTA Manifest Constants:DTA_FAILURE
						DTA Manifest Constants:DTA_BAD_ARGS_FAILURE
						DTA Manifest Constants:DTA_MEMORY_FAILURE
						DTA Manifest Constants:DTA_SYSTEM_FAILURE
						DTA Defines:DTA_SUCCESS
						DTA Defines:DTA_FAILURE
						DTA Defines:DTA_BAD_ARGS_FAILURE
						DTA Defines:DTA_MEMORY_FAILURE
						DTA Defines:DTA_SYSTEM_FAILURE
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:  DTA_SUCCESS
						DTA_FAILURE
						DTA_BAD_ARGS_FAILURE
						DTA_MEMORY_FAILURE
						DTA_SYSTEM_FAILURE
						DTA Return Codes
						DTA Return Code
						DTA return codes
						DTA return code
						DTA Status Codes
						DTA Status Code
						DTA status codes
						DTA status code
						DTA Error Codes
						DTA Error Code
						DTA error codes
						DTA error code

   PUBLISH NAME:	DTA Return Codes
						DTA return codes
						DTA_SUCCESS
						DTA_FAILURE
						DTA_BAD_ARGS_FAILURE
						DTA_MEMORY_FAILURE
						DTA_SYSTEM_FAILURE

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define DTA_SUCCESS							 0
#define DTA_FAILURE							-1
#define DTA_BAD_ARGS_FAILURE				-2
#define DTA_MEMORY_FAILURE					-3
#define DTA_SYSTEM_FAILURE					-4
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :  DTA_MAX_ERROR_TEXT

   DESCRIPTION :  The manifest constant ''DTA_MAX_ERROR_TEXT'' defines
						the minimum amount of storage which should be allocated to
						hold an error message returned by a DTA function.

   CAVEATS     :  DTA error messages can be quite lengthy. Therefore,
						attempting to save space by allocating less than
						''DTA_MAX_ERROR_TEXT'' bytes to error message buffers
						passed to DTA functions can lead to overwriting of the
						heap or the stack.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:  DTA_MAX_ERROR_TEXT
						DTA Manifest Constants:DTA_MAX_ERROR_TEXT
						DTA Defines:DTA_MAX_ERROR_TEXT
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	DTA_MAX_ERROR_TEXT

   PUBLISH NAME:	DTA_MAX_ERROR_TEXT

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define DTA_MAX_ERROR_TEXT					1024
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	BASE NAME	:	DTA Align Types

   NAME        :  DTA Align Types

   DESCRIPTION :  Manifest constants used to define the primitive types
						available on an architecture.

						(.)''DTA_C_unsigned_byte'' defines the type of an
						``unsigned char``.

						(.)''DTA_C_char'' defines the type of a ``char``.

						(.)''DTA_C_unsigned_char'' defines the type of an
						``unsigned char``.

						(.)''DTA_C_short'' defines the type of a ``short``.

						(.)''DTA_C_unsigned_short'' defines the type of an
						``unsigned short``.

						(.)''DTA_C_int'' defines the type of an ``int``.

						(.)''DTA_C_unsigned_int'' defines the type of an
						``unsigned int``.

						(.)''DTA_C_long'' defines the type of a ``long``.

						(.)''DTA_C_unsigned_long'' defines the type of an
						``unsigned long``.

						(.)''DTA_C_float'' defines the type of a ``float``.

						(.)''DTA_C_double'' defines the type of a ``double``.

   NOTES       :  ''DTA_C_unsigned_byte'' is considered to be a type
						separate from ''DTA_C_unsigned_char'' for the
						purposes of comparison and display.

	CAVEATS     :  Note that these manifest constants are indices into the
						global array ``DTA_TypeList``. They should therefore
						always be numbered sequentially beginning at zero.

   SEE ALSO    :  DTA_TypeCount
						DTA_TypeList

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:  DTA_C_unsigned_byte
						DTA_C_char
						DTA_C_unsigned_char
						DTA_C_short
						DTA_C_unsigned_short
						DTA_C_int
						DTA_C_unsigned_int
						DTA_C_long
						DTA_C_unsigned_long
						DTA_C_float
						DTA_C_double
						DTA Align Types:DTA_C_unsigned_byte
						DTA Align Types:DTA_C_char
						DTA Align Types:DTA_C_unsigned_char
						DTA Align Types:DTA_C_short
						DTA Align Types:DTA_C_unsigned_short
						DTA Align Types:DTA_C_int
						DTA Align Types:DTA_C_unsigned_int
						DTA Align Types:DTA_C_long
						DTA Align Types:DTA_C_unsigned_long
						DTA Align Types:DTA_C_float
						DTA Align Types:DTA_C_double
						DTA Manifest Constants:DTA_C_unsigned_byte
						DTA Manifest Constants:DTA_C_char
						DTA Manifest Constants:DTA_C_unsigned_char
						DTA Manifest Constants:DTA_C_short
						DTA Manifest Constants:DTA_C_unsigned_short
						DTA Manifest Constants:DTA_C_int
						DTA Manifest Constants:DTA_C_unsigned_int
						DTA Manifest Constants:DTA_C_long
						DTA Manifest Constants:DTA_C_unsigned_long
						DTA Manifest Constants:DTA_C_float
						DTA Manifest Constants:DTA_C_double
						DTA Defines:DTA_C_unsigned_byte
						DTA Defines:DTA_C_char
						DTA Defines:DTA_C_unsigned_char
						DTA Defines:DTA_C_short
						DTA Defines:DTA_C_unsigned_short
						DTA Defines:DTA_C_int
						DTA Defines:DTA_C_unsigned_int
						DTA Defines:DTA_C_long
						DTA Defines:DTA_C_unsigned_long
						DTA Defines:DTA_C_float
						DTA Defines:DTA_C_double
						Defines:See Macros and Manifest Constants

	PUBLISH XREF:	DTA Align Types
						DTA align types
						DTA Align Type
						DTA align type
						DTA Alignment Types
						DTA alignment types
						DTA Alignment Type
						DTA alignment type
						DTA_C_unsigned_byte
						DTA_C_char
						DTA_C_unsigned_char
						DTA_C_short
						DTA_C_unsigned_short
						DTA_C_int
						DTA_C_unsigned_int
						DTA_C_long
						DTA_C_unsigned_long
						DTA_C_float
						DTA_C_double

	PUBLISH NAME:	DTA_C_unsigned_byte
						DTA_C_char
						DTA_C_unsigned_char
						DTA_C_short
						DTA_C_unsigned_short
						DTA_C_int
						DTA_C_unsigned_int
						DTA_C_long
						DTA_C_unsigned_long
						DTA_C_float
						DTA_C_double

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define DTA_C_unsigned_byte				((unsigned int) 0)
#define DTA_C_char							((unsigned int) 1)
#define DTA_C_unsigned_char				((unsigned int) 2)
#define DTA_C_short							((unsigned int) 3)
#define DTA_C_unsigned_short				((unsigned int) 4)
#define DTA_C_int								((unsigned int) 5)
#define DTA_C_unsigned_int					((unsigned int) 6)
#define DTA_C_long							((unsigned int) 7)
#define DTA_C_unsigned_long				((unsigned int) 8)
#define DTA_C_float							((unsigned int) 9)
#define DTA_C_double							((unsigned int) 10)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	BASE NAME	:	DTA Align Type Characters

   NAME        :  DTA Align Type Characters

   DESCRIPTION :  Manifest constants used to define the primitive types
						available on an architecture.

						(.)''DTA_C_char_unsigned_byte'' defines the type of an
						``unsigned char``.

						(.)''DTA_C_char_char'' defines the type of a ``char``.

						(.)''DTA_C_char_unsigned_char'' defines the type of an
						``unsigned char``.

						(.)''DTA_C_char_short'' defines the type of a ``short``.

						(.)''DTA_C_char_unsigned_short'' defines the type of an
						``unsigned short``.

						(.)''DTA_C_char_int'' defines the type of an ``int``.

						(.)''DTA_C_char_unsigned_int'' defines the type of an
						``unsigned int``.

						(.)''DTA_C_char_long'' defines the type of a ``long``.

						(.)''DTA_C_char_unsigned_long'' defines the type of an
						``unsigned long``.

						(.)''DTA_C_char_float'' defines the type of a ``float``.

						(.)''DTA_C_char_double'' defines the type of a ``double``.

   NOTES       :  ''DTA_C_char_unsigned_byte'' is considered to be a type
						separate from ''DTA_C_char_unsigned_char'' for the
						purposes of comparison and display.

   SEE ALSO    :  DTA Align Types
						DTA_TypeCount
						DTA_TypeList

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:  DTA_C_char_unsigned_byte
						DTA_C_char_char
						DTA_C_char_unsigned_char
						DTA_C_char_short
						DTA_C_char_unsigned_short
						DTA_C_char_int
						DTA_C_char_unsigned_int
						DTA_C_char_long
						DTA_C_char_unsigned_long
						DTA_C_char_float
						DTA_C_char_double
						DTA Align Type Characters:DTA_C_char_unsigned_byte
						DTA Align Type Characters:DTA_C_char_char
						DTA Align Type Characters:DTA_C_char_unsigned_char
						DTA Align Type Characters:DTA_C_char_short
						DTA Align Type Characters:DTA_C_char_unsigned_short
						DTA Align Type Characters:DTA_C_char_int
						DTA Align Type Characters:DTA_C_char_unsigned_int
						DTA Align Type Characters:DTA_C_char_long
						DTA Align Type Characters:DTA_C_char_unsigned_long
						DTA Align Type Characters:DTA_C_char_float
						DTA Align Type Characters:DTA_C_char_double
						DTA Manifest Constants:DTA_C_char_unsigned_byte
						DTA Manifest Constants:DTA_C_char_char
						DTA Manifest Constants:DTA_C_char_unsigned_char
						DTA Manifest Constants:DTA_C_char_short
						DTA Manifest Constants:DTA_C_char_unsigned_short
						DTA Manifest Constants:DTA_C_char_int
						DTA Manifest Constants:DTA_C_char_unsigned_int
						DTA Manifest Constants:DTA_C_char_long
						DTA Manifest Constants:DTA_C_char_unsigned_long
						DTA Manifest Constants:DTA_C_char_float
						DTA Manifest Constants:DTA_C_char_double
						DTA Defines:DTA_C_char_unsigned_byte
						DTA Defines:DTA_C_char_char
						DTA Defines:DTA_C_char_unsigned_char
						DTA Defines:DTA_C_char_short
						DTA Defines:DTA_C_char_unsigned_short
						DTA Defines:DTA_C_char_int
						DTA Defines:DTA_C_char_unsigned_int
						DTA Defines:DTA_C_char_long
						DTA Defines:DTA_C_char_unsigned_long
						DTA Defines:DTA_C_char_float
						DTA Defines:DTA_C_char_double
						Defines:See Macros and Manifest Constants

	PUBLISH XREF:	DTA Align Type Characters
						DTA align type characters
						DTA Align Type Character
						DTA align type character
						DTA Alignment Type Characters
						DTA alignment type characters
						DTA Alignment Type Character
						DTA alignment type character
						DTA_C_char_unsigned_byte
						DTA_C_char_char
						DTA_C_char_unsigned_char
						DTA_C_char_short
						DTA_C_char_unsigned_short
						DTA_C_char_int
						DTA_C_char_unsigned_int
						DTA_C_char_long
						DTA_C_char_unsigned_long
						DTA_C_char_float
						DTA_C_char_double

	PUBLISH NAME:	DTA_C_char_unsigned_byte
						DTA_C_char_char
						DTA_C_char_unsigned_char
						DTA_C_char_short
						DTA_C_char_unsigned_short
						DTA_C_char_int
						DTA_C_char_unsigned_int
						DTA_C_char_long
						DTA_C_char_unsigned_long
						DTA_C_char_float
						DTA_C_char_double

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define DTA_C_char_unsigned_byte			'b'
#define DTA_C_char_char						'c'
#define DTA_C_char_unsigned_char			'C'
#define DTA_C_char_short					's'
#define DTA_C_char_unsigned_short		'S'
#define DTA_C_char_int						'i'
#define DTA_C_char_unsigned_int			'I'
#define DTA_C_char_long						'l'
#define DTA_C_char_unsigned_long			'L'
#define DTA_C_char_float					'f'
#define DTA_C_char_double					'd'
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	DTA_TYPE

	DESCRIPTION	:	The ''DTA_TYPE'' structure supports the description
						of the size and alignment requirements of machine
						architecture primitive types.

						The ''DTA_TYPE'' structure is declared as follows:

{|@|}typedef struct {
	char          *type_name;
	char          *short_type_name;
	char           type_abbreviation;
	unsigned int   type_align;
	unsigned int   type_length;
	char          *printf_format;
	unsigned int   printf_length;
	int          (*compare_method)(void *data_ptr, const void *data_ptr_1,
						const void *data_ptr_2, size_t data_length);
	bool_t       (*xdr_method)(XDR *, void *);
} DTA_TYPE;

	MEMBERS		:	The members of this structure are as follow:

						(.) ``type_name`` is a ''char'' pointer which points to the
						string which contains the type name of the primitive data
						type.

						(-) Most implementations define an array of
						''DTA_TYPE'' structures with the following
						``type_name`` members:

{|@|}unsigned byte
signed char
unsigned char
signed short
unsigned short
signed int
unsigned int
signed long
unsigned long
float
double

						(.) ``short_type_name`` is a ''char'' pointer which points
						to the string which contains a short type name of the
						primitive data type.

						(-) Most implementations define an array of
						''DTA_TYPE'' structures with the following
						``short_type_name`` members:

{|@|}ubyte
schar
uchar
sshort
ushort
sint
uint
slong
ulong
float
double

						(.) ``type_abbreviation`` is a ''char'' which contains the
						single character abbreviation of the primitive data type.

						(-) Most implementations define an array of
						''DTA_TYPE'' structures with the following
						``type_abbreviation`` members:

{|@|}b
c
C
s
S
i
I
l
L
f
d

						(.) ``type_align`` is an ''unsigned int'' which contains the
						alignment requirement, in bytes, of the primitive data
						type.

						(-) For example, for code compiled with an MS-DOS compiler,
						the ``type_align`` member describing the ''double''
						primitive data type would (assuming no special compile-time
						options or pragmas were used) be ''1''. This indicates that
						the ''double'' primitive data type must be aligned on a
						memory address which is an integral multiple of ''1'' ---
						that is to say, any memory address.

						(-) Alternatively, for code compiled for the a SPARC
						architecture such as a Sun workstation, the ``type_align``
						member describing the ''double'' primitive data type would
						be ''8''. This indicates that the ''double'' primitive data
						type must be aligned on a memory address which is an
						integral multiple of ''8''

						(.) ``type_length`` is an ''unsigned int'' which contains
						the length, in bytes, of the primitive data type. This
						value should be the same as that returned by the ''C''
						language construct ``sizeof()``.

						(.) ``printf_format`` is a ''char'' pointer which points to
						the string which contains the default ``printf`` format
						for the primitive data type.

						(.) ``printf_length`` is an ''unsigned int'' which contains
						the length of the primitive data type when printed using the
						default ``printf`` format in ``printf_format``.

						(.) ``compare_method`` is a pointer to a comparison function
						for the primitive data type. This function has the
						following prototype:

{|-|}int (*compare_method)(void *data_ptr, const void *data_ptr_1,
	const void *data_ptr_2, size_t data_length);

						(.) ``xdr_method`` is a pointer to an XDR function for the
						primitive data type. This function has the following
						prototype:

{|-|}bool_t (*xdr_method)(XDR *, void *);

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2018 Michael L. Brock

	OUTPUT INDEX:	DTA_TYPE
						Alignment Structures:DTA_TYPE
						Structures:DTA_TYPE
						Data Type Alignment Structures:DTA_TYPE

	PUBLISH XREF:	DTA_TYPE

	PUBLISH NAME:	DTA_TYPE

	ENTRY CLASS	:	Structures and Data Types

EOH */
/*	***********************************************************************	*/
#if defined(_MSC_VER) && (_MSC_VER >= 1400)
# pragma warning(push)
# pragma warning(disable:4820)
#endif /* #if defined(_MSC_VER) && (_MSC_VER >= 1400) */

typedef struct {
	char          *type_name;
	char          *short_type_name;
	char           type_abbreviation;
	unsigned int   type_align;
	unsigned int   type_length;
	char          *printf_format;
	unsigned int   printf_length;
#ifndef NARGS
	int          (*compare_method)(void *data_ptr, const void *data_ptr_1,
						const void *data_ptr_2, size_t data_length);
	bool_t       (*xdr_method)(XDR *, void *);
#else
	int          (*compare_method)();
	bool_t       (*xdr_method)();
#endif /* #ifndef NARGS */
} DTA_TYPE;

#if defined(_MSC_VER) && (_MSC_VER >= 1400)
# pragma warning(pop)
#endif /* #if defined(_MSC_VER) && (_MSC_VER >= 1400) */
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	DTA

	DESCRIPTION	:	The ''DTA'' structure describes the size and offset
						of a datum as required by the alignment requirements and
						primitive type sizes of a processor architecture.

						The ''DTA'' structure is declared as follows:

{|@|}typedef struct {
	unsigned int type;
	unsigned int array_length;
	unsigned int offset;
	unsigned int length;
} DTA;

	MEMBERS		:	The members of this structure are as follow:

						(.) ``type`` is the primitive type of the datum. It takes
						the value of one of the defined DTA alignment types,
						specified as one of the following manifest constants:

						(..) ''DTA_C_unsigned_byte'' defines the type of an
						``unsigned char``.

						(..) ''DTA_C_char'' defines the type of a ``char``.

						(..) ''DTA_C_unsigned_char'' defines the type of an
						``unsigned char``.

						(..) ''DTA_C_short'' defines the type of a ``short``.

						(..) ''DTA_C_unsigned_short'' defines the type of an
						``unsigned short``.

						(..) ''DTA_C_int'' defines the type of an ``int``.

						(..) ''DTA_C_unsigned_int'' defines the type of an
						``unsigned int``.

						(..) ''DTA_C_long'' defines the type of a ``long``.

						(..) ''DTA_C_unsigned_long'' defines the type of an
						``unsigned long``.

						(..) ''DTA_C_float'' defines the type of a ``float``.

						(..) ''DTA_C_double'' defines the type of a ``double``.

						(.) ``array_length`` is the number of primitive types which
						constitute the datum. For scalar data, ``array_length`` is
						''1''.

						(.) ``offset`` is the offset of the datum.

						(.) ``length`` is the total length of the datum --- that is,
						the length of the primitive type multiplied by the
						``array_length`` member of this structure.

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2018 Michael L. Brock

	OUTPUT INDEX:	DTA
						Alignment Structures:DTA
						Structures:DTA
						Data Type Alignment Structures:DTA

	PUBLISH XREF:	DTA

	PUBLISH NAME:	DTA

	ENTRY CLASS	:	Structures and Data Types

EOH */
/*	***********************************************************************	*/
typedef struct {
	unsigned int type;
	unsigned int array_length;
	unsigned int offset;
	unsigned int length;
} DTA;
/*	***********************************************************************	*/

/*
	ADF_ NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef struct {
	unsigned int    type_count;
	const DTA_TYPE *type_list;
	int             ignore_case_flag;
	unsigned int    align_count;
	DTA            *align_list;
} DTA_CMP;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Function prototypes for functions defined within 'dta.a' . . .			*/
/*	***********************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Prototypes to get the default primitive type information . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void DTA_GetTypeInfo,
	(unsigned int *type_count, const DTA_TYPE **type_list));
COMPAT_FN_DECL(void DTA_GetDefaultTypeInfo,
	(unsigned int *type_count, const DTA_TYPE **type_list));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Function prototypes for version functions . . .
		*****************************************************************	*/
COMPAT_FN_DECL(STR_VERSION *DTA_GetVersion, (STR_VERSION *version_number));
COMPAT_FN_DECL(char        *DTA_GetVersionString, (char *version_string));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Architecture-independent alignment function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int             DTA_BASIC_AlignStringList,
	(unsigned int type_count,
	const DTA_TYPE *type_list, int normalize_flag,
	int adjust_char_flag, const char *separator_list, unsigned int spec_count,
	char **spec_list, unsigned int **count_list, unsigned int **index_list,
	unsigned int **size_list, unsigned int *structure_size,
	unsigned int *align_count, DTA **align_list, char *error_text));
COMPAT_FN_DECL(int             DTA_BASIC_AlignString,
	(unsigned int type_count,
	const DTA_TYPE *type_list, int normalize_flag,
	int adjust_char_flag, const char *separator_list, const char *spec_string,
	unsigned int *structure_size, unsigned int *align_count,
	DTA **align_list, char *error_text));
COMPAT_FN_DECL(int             DTA_BASIC_CountStringToList,
	(unsigned int type_count, const DTA_TYPE *type_list,
	int normalize_flag, int adjust_char_flag, const char *separator_list,
	unsigned int in_spec_count, const char *in_spec_string,
	unsigned int *structure_size, unsigned int *align_count,
	DTA **align_list, char *error_text));
COMPAT_FN_DECL(int             DTA_BASIC_CountStringToLApp,
	(unsigned int type_count, const DTA_TYPE *type_list,
	int normalize_flag, int adjust_char_flag, const char *separator_list,
	unsigned int in_spec_count, const char *in_spec_string,
	unsigned int *structure_size, unsigned int *align_count,
	DTA **align_list, char *error_text));
COMPAT_FN_DECL(int             DTA_BASIC_CountStringToString,
	(unsigned int type_count, const DTA_TYPE *type_list,
	int normalize_flag, int adjust_char_flag, const char *separator_list,
	unsigned int in_spec_count, const char *in_spec_string,
	char **out_spec_string, char *error_text));
COMPAT_FN_DECL(int             DTA_BASIC_AlignList,
	(unsigned int type_count,
	const DTA_TYPE *type_list, unsigned int *structure_size,
	unsigned int align_count, DTA *align_list, char *error_text));
COMPAT_FN_DECL(int             DTA_BASIC_CheckStringList,
	(unsigned int type_count,
	const DTA_TYPE *type_list, const char *separator_list,
	unsigned int spec_count, char **spec_list, char *error_text));
COMPAT_FN_DECL(int             DTA_BASIC_CheckString,
	(unsigned int type_count,
	const DTA_TYPE *type_list, const char *separator_list,
	const char *spec_string, char *error_text));
COMPAT_FN_DECL(int             DTA_BASIC_CheckMember,
	(unsigned int type_count,
	const DTA_TYPE *type_list, const char *spec_string,
	DTA *align_ptr, char *error_text));
COMPAT_FN_DECL(int             DTA_BASIC_ListToStringAlloc,
	(unsigned int type_count,
	const DTA_TYPE *type_list, unsigned int align_count,
	const DTA *align_list, const char *separator_char,
	char **spec_string, char *error_text));
COMPAT_FN_DECL(int             DTA_BASIC_ListToString,
	(unsigned int type_count,
	const DTA_TYPE *type_list, unsigned int align_count,
	const DTA *align_list, const char *separator_char, char *spec_string,
	char *error_text));
COMPAT_FN_DECL(int             DTA_BASIC_CopyTypeList,
	(unsigned int in_type_count,
	const DTA_TYPE *in_type_list, unsigned int *out_type_count,
	DTA_TYPE **out_type_list,  char *error_text));
COMPAT_FN_DECL(int             DTA_BASIC_FindTypeCharIndex,
	(unsigned int type_count, const DTA_TYPE *type_list, int type_char,
	unsigned int *type_index));
COMPAT_FN_DECL(const DTA_TYPE *DTA_BASIC_FindTypeCharPtr,
	(unsigned int type_count,
	const DTA_TYPE *type_list, int type_char, unsigned int *type_index));
COMPAT_FN_DECL(const DTA_TYPE *DTA_BASIC_GetTypePtr,
	(unsigned int type_count,
	const DTA_TYPE *type_list, unsigned int type_index));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Default architecture alignment function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int             DTA_AlignStringList,
	(int normalize_flag,
	int adjust_char_flag, const char *separator_list, unsigned int spec_count,
	char **spec_list, unsigned int **count_list, unsigned int **index_list,
	unsigned int **size_list, unsigned int *structure_size,
	unsigned int *align_count, DTA **align_list, char *error_text));
COMPAT_FN_DECL(int             DTA_AlignString,
	(int normalize_flag,
	int adjust_char_flag, const char *separator_list, const char *spec_string,
	unsigned int *structure_size, unsigned int *align_count,
	DTA **align_list, char *error_text));
COMPAT_FN_DECL(int             DTA_CountStringToList,
	(int normalize_flag,
	int adjust_char_flag, const char *separator_list,
	unsigned int in_spec_count, const char *in_spec_string,
	unsigned int *structure_size, unsigned int *align_count,
	DTA **align_list, char *error_text));
COMPAT_FN_DECL(int             DTA_CountStringToLApp,
	(int normalize_flag,
	int adjust_char_flag, const char *separator_list,
	unsigned int in_spec_count, const char *in_spec_string,
	unsigned int *structure_size, unsigned int *align_count,
	DTA **align_list, char *error_text));
COMPAT_FN_DECL(int             DTA_CountStringToString,
	(int normalize_flag,
	int adjust_char_flag, const char *separator_list,
	unsigned int in_spec_count, const char *in_spec_string,
	char **out_spec_string, char *error_text));
COMPAT_FN_DECL(int             DTA_AlignList,
	(unsigned int *structure_size,
	unsigned int align_count, DTA *align_list, char *error_text));
COMPAT_FN_DECL(int             DTA_CheckStringList,
	(const char *separator_list,
	unsigned int spec_count, char **spec_list, char *error_text));
COMPAT_FN_DECL(int             DTA_CheckString,
	(const char *separator_list,
	const char *spec_string, char *error_text));
COMPAT_FN_DECL(int             DTA_CheckMember,
	(const char *spec_string,
	DTA *align_ptr, char *error_text));
COMPAT_FN_DECL(int             DTA_ListToStringAlloc,
	(unsigned int align_count,
	const DTA *align_list, const char *separator_char,
	char **spec_string, char *error_text));
COMPAT_FN_DECL(int             DTA_ListToString,
	(unsigned int align_count,
	const DTA *align_list, const char *separator_char, char *spec_string,
	char *error_text));
COMPAT_FN_DECL(int             DTA_CopyTypeList,
	(unsigned int *out_type_count,
	DTA_TYPE **out_type_list,  char *error_text));
COMPAT_FN_DECL(int             DTA_FindTypeCharIndex,
	(int type_char,
	unsigned int *type_index));
COMPAT_FN_DECL(const DTA_TYPE *DTA_FindTypeCharPtr,
	(int type_char,
	unsigned int *type_index));
COMPAT_FN_DECL(const DTA_TYPE *DTA_GetTypePtr,
	(unsigned int type_index));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Support alignment function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void DTA_NormalizeList,
	(unsigned int *align_count, DTA **align_list));
COMPAT_FN_DECL(unsigned int DTA_CalcListToStringLen,
	(unsigned int align_count, const DTA *align_list));
COMPAT_FN_DECL(void DTA_InitAlign, (DTA *align_ptr));
COMPAT_FN_DECL(int  DTA_CompareList,
	(DTA_CMP *align_cmp_ptr, const void *data_ptr_1,
	const void *data_ptr_2, size_t data_length));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Alignment data comparison function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DTA_SCMP_ubyte, (DTA *align_ptr,
	const unsigned char *ptr_1, const unsigned char *ptr_2,
	size_t data_length));
COMPAT_FN_DECL(int DTA_SCMP_char, (DTA *align_ptr, const char *ptr_1,
	const char *ptr_2, size_t data_length));
COMPAT_FN_DECL(int DTA_SCMP_uchar, (DTA *align_ptr,
	const unsigned char *ptr_1, const unsigned char *ptr_2,
	size_t data_length));
COMPAT_FN_DECL(int DTA_SCMP_short, (DTA *align_ptr, const short *ptr_1,
	const short *ptr_2, size_t data_length));
COMPAT_FN_DECL(int DTA_SCMP_ushort, (DTA *align_ptr,
	const unsigned short *ptr_1, const unsigned short *ptr_2,
	size_t data_length));
COMPAT_FN_DECL(int DTA_SCMP_int, (DTA *align_ptr, const int *ptr_1,
	const int *ptr_2, size_t data_length));
COMPAT_FN_DECL(int DTA_SCMP_uint, (DTA *align_ptr,
	const unsigned int *ptr_1, const unsigned int *ptr_2, size_t data_length));
COMPAT_FN_DECL(int DTA_SCMP_long, (DTA *align_ptr, const long *ptr_1,
	const long *ptr_2, size_t data_length));
COMPAT_FN_DECL(int DTA_SCMP_ulong, (DTA *align_ptr,
	const unsigned long *ptr_1, const unsigned long *ptr_2,
	size_t data_length));
COMPAT_FN_DECL(int DTA_SCMP_float, (DTA *align_ptr, const float *ptr_1,
	const float *ptr_2, size_t data_length));
COMPAT_FN_DECL(int DTA_SCMP_double, (DTA *align_ptr,
	const double *ptr_1, const double *ptr_2, size_t data_length));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DTA emit function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void DTA_BASIC_EmitAlignList,
	(unsigned int type_count, const DTA_TYPE *type_list, unsigned int dta_count,
	const DTA *dta_list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(void DTA_BASIC_EmitAlignListIdx,
	(unsigned int type_count, const DTA_TYPE *type_list, unsigned int dta_count,
	const DTA *dta_list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(void DTA_BASIC_EmitAlign,
	(unsigned int type_count, const DTA_TYPE *type_list, const DTA *ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));

COMPAT_FN_DECL(void DTA_EmitAlignList, (unsigned int dta_count,
	const DTA *dta_list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(void DTA_EmitAlignListIdx, (unsigned int dta_count,
	const DTA *dta_list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(void DTA_EmitAlign, (const DTA *ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void DTA_EmitAlignHeader,
	(STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void DTA_EmitAlignTrailer,
	(STR_FUNC_TYPE_fprintf output_function, void *output_control));
	/*	*****************************************************************	*/

/*	***********************************************************************	*/

#endif /* #ifndef h__DTA_H__h */

