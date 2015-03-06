/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* STRFUNCS String and Memory Functions Library Include File					*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the STRFUNCS library.

	Revision History	:	1986-10-27 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1986 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__STRFUNCS_H__h

#define h__STRFUNCS_H__h					1

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Necessary include files . . .														*/
/* *********************************************************************** */

#include <mbcompat.h>

#include <ctype.h>
#include <limits.h>
#include <stddef.h>

#ifndef NO_STDARGS
# include <stdarg.h>
#else
# include <varargs.h>
#endif /* #ifndef NO_STDARGS */

/*
	CODE NOTE: To be removed.
#include "strregex.h"
*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#ifdef NO_STRCHR
# ifndef STRFUNCS_strchr
#  define STRFUNCS_strchr strchr
# endif /* #ifndef STRFUNCS_strchr */
#endif /* # ifdef NO_STRCHR */

#ifdef NO_STRRCHR
# ifndef STRFUNCS_strrchr
#  define STRFUNCS_strrchr strrchr
# endif /* #ifndef STRFUNCS_strrchr */
#endif /* # ifdef NO_STRRCHR */

#ifdef NO_STRSTR
# ifndef STRFUNCS_strstr
#  define STRFUNCS_strstr strstr
# endif /* #ifndef STRFUNCS_strstr */
#endif /* # ifdef NO_STRSTR */

#ifdef NO_MEMICMP
# ifndef STRFUNCS_memicmp
#  define STRFUNCS_memicmp memicmp
# endif /* # ifndef STRFUNCS_memicmp */
#endif /* # ifdef NO_MEMICMP */

#ifdef NO_STRDUP
# ifndef STRFUNCS_strdup
#  define STRFUNCS_strdup strdup
# endif /* # ifndef STRFUNCS_strdup */
#endif /* # ifdef NO_STRDUP */

#ifdef NO_STRSET
# ifndef STRFUNCS_strset
#  define STRFUNCS_strset strset
# endif /* # ifndef STRFUNCS_strset */
#endif /* # ifdef NO_STRSET */

#ifdef NO_STRNSET
# ifndef STRFUNCS_strnset
#  define STRFUNCS_strnset strnset
# endif /* # ifndef STRFUNCS_strnset */
#endif /* # ifdef NO_STRNSET */

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/*    The functions 'stricmp()' and 'strnicmp()' are not part of the			*/
/* ANSI/ISO C standard, but are present in most C implementations because	*/
/* of their general usefulness. The SunOS 4.X implementations, however,		*/
/* include these functions in the same compilation unit as other certain	*/
/* other functions, which can cause a problem when linking. Hence the		*/
/* manifest constants below.																*/
/* *********************************************************************** */

#ifdef NO_STRICMP
# ifndef STRFUNCS_stricmp
#  define STRFUNCS_stricmp stricmp
# endif /* #ifndef STRFUNCS_stricmp */
#endif /* # ifdef NO_STRICMP */

#ifdef NO_STRNICMP
# ifndef STRFUNCS_strnicmp
#  define STRFUNCS_strnicmp strnicmp
# endif /* #ifndef STRFUNCS_strnicmp */
#endif /* # ifdef NO_STRNICMP */

COMPAT_FN_DECL(int STRFUNCS_stricmp, (const char *, const char *));
COMPAT_FN_DECL(int STRFUNCS_strnicmp, (const char *, const char *, size_t));

/* *********************************************************************** */

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		How to get the 'sizeof()' something when you haven't one about . . .	*/
/*	***********************************************************************	*/
#define STR_sizeof(structure_name, member_name) \
	sizeof(((structure_name *) 0)->member_name)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   BASE NAME   :  STRFUNCS Truth Codes

   NAME        :  STRFUNCS Truth Codes

   DESCRIPTION :  Manifest constants used within STRFUNCS to specify the truth
						or falsity of expressions.

						(.) ''STRFUNCS_TRUE''

						(.) ''STRFUNCS_FALSE''

   NOTES       :  The manifest constant ''STRFUNCS_TRUE'' should be defined as
						a non-zero value. Conversely, the manifest constant
						''STRFUNCS_FALSE'' should be defined as zero (''0'').

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1986 - 2015 Michael L. Brock

   OUTPUT INDEX:  STRFUNCS_TRUE
						STRFUNCS_FALSE
						STRFUNCS Truth Codes:STRFUNCS_TRUE
						STRFUNCS Truth Codes:STRFUNCS_FALSE
						STRFUNCS Manifest Constants:STRFUNCS_TRUE
						STRFUNCS Manifest Constants:STRFUNCS_FALSE
						STRFUNCS Defines:STRFUNCS_TRUE
						STRFUNCS Defines:STRFUNCS_FALSE

   PUBLISH XREF:  STRFUNCS_TRUE
						STRFUNCS_FALSE
						STRFUNCS Truth Codes
						STRFUNCS Truth Code
						STRFUNCS truth codes
						STRFUNCS truth code

   PUBLISH NAME:	STRFUNCS_TRUE
						STRFUNCS_FALSE

	ENTRY CLASS	:	Manifest Constants

EOH */
/*	***********************************************************************	*/
#define STRFUNCS_TRUE						1
#define STRFUNCS_FALSE						0
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   BASE NAME   :	STRFUNCS Return Codes

   NAME        :  STRFUNCS Return Codes

   DESCRIPTION :  The STRFUNCS return codes have the following meanings:

						(.) ''STRFUNCS_SUCCESS'' means that the function invoked
						completed without error. ''STRFUNCS_SUCCESS'' is guaranteed to
						be equal to zero (''0'').

						(.) ''STRFUNCS_FAILURE'' indicates that the function invoked
						encountered a general operation failure. This is the
						'catch-all' error code for those errors which do not fit
						into category of one the other STRFUNCS error codes.

						(.) ''STRFUNCS_BAD_ARGS_FAILURE'' indicates that the
						arguments passed to a function invoked were invalid.

						(.) ''STRFUNCS_MEMORY_FAILURE'' indicates that the memory
						required for operation of the function invoked could not be
						allocated.

						(.) ''STRFUNCS_SYSTEM_FAILURE'' indicates that the function invoked
						encountered a failure of a standard library function or a
						system call.

   NOTES       :  The following synonyms to the STRFUNCS return codes are
						provided for reasons of backward-compatibility with older
						versions of the library:

						(.) ''STRFUNCS_ERROR'' is a synonym for
						''STRFUNCS_FAILURE''.

						(.) ''STR_LIST_FAILURE'' is a synonym for
						''STRFUNCS_FAILURE''.

						(.) ''STR_LIST_ERROR'' is a synonym for
						''STRFUNCS_FAILURE''.

						(.) ''STR_LIST_SUCCESS'' is a synonym for
						''STRFUNCS_SUCCESS''.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1986 - 2015 Michael L. Brock

   OUTPUT INDEX:  STRFUNCS_SUCCESS
						STRFUNCS_FAILURE
						STRFUNCS_BAD_ARGS_FAILURE
						STRFUNCS_MEMORY_FAILURE
						STRFUNCS_SYSTEM_FAILURE
						STRFUNCS Return Codes:STRFUNCS_SUCCESS
						STRFUNCS Return Codes:STRFUNCS_FAILURE
						STRFUNCS Return Codes:STRFUNCS_BAD_ARGS_FAILURE
						STRFUNCS Return Codes:STRFUNCS_MEMORY_FAILURE
						STRFUNCS Return Codes:STRFUNCS_SYSTEM_FAILURE
						STRFUNCS Manifest Constants:STRFUNCS_SUCCESS
						STRFUNCS Manifest Constants:STRFUNCS_FAILURE
						STRFUNCS Manifest Constants:STRFUNCS_BAD_ARGS_FAILURE
						STRFUNCS Manifest Constants:STRFUNCS_MEMORY_FAILURE
						STRFUNCS Manifest Constants:STRFUNCS_SYSTEM_FAILURE
						STRFUNCS Defines:STRFUNCS_SUCCESS
						STRFUNCS Defines:STRFUNCS_FAILURE
						STRFUNCS Defines:STRFUNCS_BAD_ARGS_FAILURE
						STRFUNCS Defines:STRFUNCS_MEMORY_FAILURE
						STRFUNCS Defines:STRFUNCS_SYSTEM_FAILURE

   PUBLISH XREF:  STRFUNCS_SUCCESS
						STRFUNCS_FAILURE
						STRFUNCS_BAD_ARGS_FAILURE
						STRFUNCS_MEMORY_FAILURE
						STRFUNCS_SYSTEM_FAILURE
						STRFUNCS_ERROR
						STR_LIST_FAILURE
						STR_LIST_ERROR
						STR_LIST_SUCCESS
						STRFUNCS Return Codes
						STRFUNCS Return Code
						STRFUNCS return codes
						STRFUNCS return code
						STRFUNCS Status Codes
						STRFUNCS Status Code
						STRFUNCS status codes
						STRFUNCS status code
						STRFUNCS Error Codes
						STRFUNCS Error Code
						STRFUNCS error codes
						STRFUNCS error code

	PUBLISH NAME:	STRFUNCS_SUCCESS
						STRFUNCS_FAILURE
						STRFUNCS_BAD_ARGS_FAILURE
						STRFUNCS_MEMORY_FAILURE
						STRFUNCS_SYSTEM_FAILURE

	ENTRY CLASS	:	Manifest Constants

EOH */
/*	***********************************************************************	*/
#define STRFUNCS_FAILURE					-1
#define STRFUNCS_SUCCESS					 0
#define STRFUNCS_BAD_ARGS_FAILURE		-2
#define STRFUNCS_MEMORY_FAILURE			-3
#define STRFUNCS_SYSTEM_FAILURE			-4
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		For backward-compatibility with older versions of the library.	*/
	/*	*****************************************************************	*/
#define STRFUNCS_ERROR						STRFUNCS_FAILURE
#define STR_LIST_FAILURE					STRFUNCS_FAILURE
#define STR_LIST_ERROR						STRFUNCS_FAILURE
#define STR_LIST_SUCCESS					STRFUNCS_SUCCESS
	/*	*****************************************************************	*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :  STRFUNCS_MAX_ERROR_TEXT

   DESCRIPTION :  The manifest constant ''STRFUNCS_MAX_ERROR_TEXT'' defines
						the minimum amount of storage which should be allocated to
						hold an error message returned by a STRFUNCS function.

   CAVEATS     :  STRFUNCS error messages can be quite lengthy. Therefore,
						attempting to save space by allocating less than
						''STRFUNCS_MAX_ERROR_TEXT'' bytes to error message buffers
						passed to STRFUNCS functions can lead to overwriting of the
						heap or the stack.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1986 - 2015 Michael L. Brock

   OUTPUT INDEX:  STRFUNCS_MAX_ERROR_TEXT
						STRFUNCS Manifest Constants:STRFUNCS_MAX_ERROR_TEXT
						STRFUNCS Defines:STRFUNCS_MAX_ERROR_TEXT
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	STRFUNCS_MAX_ERROR_TEXT

   PUBLISH NAME:	STRFUNCS_MAX_ERROR_TEXT

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define STRFUNCS_MAX_ERROR_TEXT			1024
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	BASE NAME	:	STRFUNCS Search Result Codes

   NAME        :  STRFUNCS Search Result Codes

   DESCRIPTION :  Manifest constants used to specify the results of searches.

						(.) ''STRFUNCS_ITEM_FOUND'' indicates the desired item was
						located.

						(.) ''STRFUNCS_ITEM_NOT_FOUND'' indicates the desired item
						was not located.

   NOTES       :  The following synonyms to the STRFUNCS search result codes
						are provided for reasons of backward-compatibility with
						older versions of the library:

						(.) ''STR_LIST_ITEM_FOUND'' is a synonym for
						''STRFUNCS_ITEM_FOUND''.

						(.) ''STR_LIST_ITEM_NOT_FOUND'' is a synonym for
						''STRFUNCS_ITEM_NOT_FOUND''.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1986 - 2015 Michael L. Brock

   OUTPUT INDEX:  STRFUNCS_ITEM_FOUND
						STRFUNCS_ITEM_NOT_FOUND
						STRFUNCS Search Result Codes:STRFUNCS_ITEM_FOUND
						STRFUNCS Search Result Codes:STRFUNCS_ITEM_NOT_FOUND
						STRFUNCS Manifest Constants:STRFUNCS_ITEM_FOUND
						STRFUNCS Manifest Constants:STRFUNCS_ITEM_NOT_FOUND
						STRFUNCS Defines:STRFUNCS_ITEM_FOUND
						STRFUNCS Defines:STRFUNCS_ITEM_NOT_FOUND

   PUBLISH XREF:	STRFUNCS_ITEM_FOUND
						STRFUNCS_ITEM_NOT_FOUND
						STR_LIST_ITEM_FOUND
						STR_LIST_ITEM_NOT_FOUND
						STRFUNCS Search Result Codes
						STRFUNCS search result codes

   PUBLISH NAME:	STRFUNCS_ITEM_FOUND
						STRFUNCS_ITEM_NOT_FOUND

	ENTRY CLASS	:	Manifest Constants

EOH */
/*	***********************************************************************	*/
#define STRFUNCS_ITEM_FOUND				0
#define STRFUNCS_ITEM_NOT_FOUND			1
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		For backward-compatibility with older versions of the library.	*/
	/*	*****************************************************************	*/
#define STR_LIST_ITEM_FOUND				STRFUNCS_ITEM_FOUND
#define STR_LIST_ITEM_NOT_FOUND			STRFUNCS_ITEM_NOT_FOUND
	/*	*****************************************************************	*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	BASE NAME	:	STRFUNCS Search Anchor Flags

   NAME        :  STRFUNCS Search Anchor Flags

   DESCRIPTION :  Manifest constants used to specify the anchor points for
						searches.

						(.) ''STRFUNCS_DIRECTION_NONE'' specifies that the search
						is not to be anchored --- that any item meeting the
						criterion is to be returned.

						(.) ''STRFUNCS_DIRECTION_TOP'' specifies that the search
						is to be anchored at the first of the items meeting the
						criterion.

						(.) ''STRFUNCS_DIRECTION_BOTTOM'' specifies that the search
						is to be anchored at the last of the items meeting the
						criterion.

	NOTES       :  The following synonyms to the STRFUNCS search anchor flags
						are provided for reasons of backward-compatibility with
						older versions of the library:

						(.) ''STR_LIST_DIRECTION_NONE'' is a synonym for
						''STRFUNCS_DIRECTION_NONE''.

						(.) ''STR_LIST_DIRECTION_TOP'' is a synonym for
						''STRFUNCS_DIRECTION_TOP''.

						(.) ''STR_LIST_DIRECTION_BOTTOM'' is a synonym for
						''STRFUNCS_DIRECTION_BOTTOM''.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1986 - 2015 Michael L. Brock

   OUTPUT INDEX:  STRFUNCS_DIRECTION_NONE
						STRFUNCS_DIRECTION_TOP
						STRFUNCS_DIRECTION_BOTTOM
						STRFUNCS Search Anchor Flags:STRFUNCS_DIRECTION_NONE
						STRFUNCS Search Anchor Flags:STRFUNCS_DIRECTION_TOP
						STRFUNCS Search Anchor Flags:STRFUNCS_DIRECTION_BOTTOM
						STRFUNCS Manifest Constants:STRFUNCS_DIRECTION_NONE
						STRFUNCS Manifest Constants:STRFUNCS_DIRECTION_TOP
						STRFUNCS Manifest Constants:STRFUNCS_DIRECTION_BOTTOM
						STRFUNCS Defines:STRFUNCS_DIRECTION_NONE
						STRFUNCS Defines:STRFUNCS_DIRECTION_TOP
						STRFUNCS Defines:STRFUNCS_DIRECTION_BOTTOM

   PUBLISH XREF:	STRFUNCS_DIRECTION_NONE
						STRFUNCS_DIRECTION_TOP
						STRFUNCS_DIRECTION_BOTTOM
						STR_LIST_DIRECTION_NONE
						STR_LIST_DIRECTION_TOP
						STR_LIST_DIRECTION_BOTTOM
						STRFUNCS Search Anchor Flags
						STRFUNCS search anchor flags

   PUBLISH NAME:	STRFUNCS_DIRECTION_NONE
						STRFUNCS_DIRECTION_TOP
						STRFUNCS_DIRECTION_BOTTOM

	ENTRY CLASS	:	Manifest Constants

EOH */
/*	***********************************************************************	*/
#define STRFUNCS_DIRECTION_NONE			 0
#define STRFUNCS_DIRECTION_TOP			 1
#define STRFUNCS_DIRECTION_BOTTOM		-1
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		For backward-compatibility with older versions of the library.	*/
	/*	*****************************************************************	*/
#define STR_LIST_DIRECTION_NONE			STRFUNCS_DIRECTION_NONE
#define STR_LIST_DIRECTION_TOP			STRFUNCS_DIRECTION_TOP
#define STR_LIST_DIRECTION_BOTTOM		STRFUNCS_DIRECTION_BOTTOM
	/*	*****************************************************************	*/
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	STR_VERSION

	DESCRIPTION	:	The ``typedef``ed data type ''STR_VERSION'' describes
						the storage of a STRFUNCS version number.

						The ''STR_VERSION'' structure is declared as follows:

{|@|}typedef struct {
	unsigned char major;
	unsigned char minor;
	unsigned char release;
	unsigned char build;
} STR_VERSION;

	MEMBERS		:	The members of this structure are as follow:

						(.) ``major`` represents the major component of the version
						number.

						(.) ``minor`` represents the minor component of the version
						number.

						(.) ``release`` represents the release component of the
						version number.

						(.) ``build`` represents the build level component of the
						version number.

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1986 - 2015 Michael L. Brock

	OUTPUT INDEX:	STR_VERSION

	PUBLISH XREF:	STR_VERSION

	PUBLISH NAME:	STR_VERSION

	ENTRY CLASS	:	Data Structures

EOH */
/*	***********************************************************************	*/
typedef struct {
	unsigned char major;
	unsigned char minor;
	unsigned char release;
	unsigned char build;
} STR_VERSION;
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  STR_VERSION_NUMBER_LENGTH

   DESCRIPTION :  The manifest constant ''STR_VERSION_NUMBER_LENGTH''
						defines the minimum amount of storage which should be
						allocated to hold a STRFUNCS version number as represented in
						a structure of type ''STR_VERSION''.

						As the ''STR_VERSION'' consists of four
						''unsigned char''s, a version number string needs to be
						not less than 16 characters in length (including the
						space for the terminating ASCII 0):

						(-) ``999``.``999``.``999``(``999``)

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2015 Michael L. Brock

   OUTPUT INDEX:  STR_VERSION_NUMBER_LENGTH
						Macros and Manifest Constants:STR_VERSION_NUMBER_LENGTH
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	STR_VERSION_NUMBER_LENGTH

   PUBLISH NAME:	STR_VERSION_NUMBER_LENGTH

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
/* ***** strlen("999.999.999(999)") = 16	*/
#define STR_VERSION_NUMBER_LENGTH		(16 + 1)
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  STR_VERSION_NUMBER_SET

   SYNOPSIS    :	STR_VERSION_NUMBER_SET(in_major, in_minor, in_release,
							in_build, version_ptr);

   DESCRIPTION :  The macro ''STR_VERSION_NUMBER_SET'' initializes a
						structure of type ''STR_VERSION''.

	PARAMETERS	:	Parameters to this macro are as follow:

						(.) ``in_major`` is an positive integral value in the range
						''0'' through ''255'', inclusive. It represents the major
						component of the version number.

						(.) ``in_minor`` is an positive integral value in the range
						''0'' through ''255'', inclusive.  It represents the minor
						component of the version number.

						(.) ``in_release`` is an positive integral value in the range
						''0'' through ''255'', inclusive.  It represents the release
						component of the version number.

						(.) ``in_build`` is an positive integral value in the range
						''0'' through ''255'', inclusive.  It represents the build
						level component of the version number.

						(.) ``version_ptr`` is a pointer to a structure of type
						''STR_VERSION'' into which this macro will place the
						values of ``in_major``, ``in_minor``, ``in_release``, and
						``in_build``.

	AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2015 Michael L. Brock

   OUTPUT INDEX:  STR_VERSION_NUMBER_SET
						Macros and Manifest Constants:STR_VERSION_NUMBER_SET
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	STR_VERSION_NUMBER_SET

   PUBLISH NAME:	STR_VERSION_NUMBER_SET

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define STR_VERSION_NUMBER_SET(in_major, in_minor, in_release,	\
	in_build, version_ptr)													\
	(((version_ptr) != NULL) ?												\
		((version_ptr)->major   = ((unsigned char) (in_major)),	\
		 (version_ptr)->minor   = ((unsigned char) (in_minor)),	\
		 (version_ptr)->release = ((unsigned char) (in_release)),\
		 (version_ptr)->build   = ((unsigned char) (in_build)),	\
		 (version_ptr))       :												\
		(NULL))
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	STR_VERSION_NUMBER_NULL

   DESCRIPTION :	The manifest constant ''STR_VERSION_NUMBER_NULL''
						defines the value of an empty structure of type
						''STR_VERSION''. It is defined as:

						<|@|>(*((STR_VERSION *) "\0\0\0"))

   NOTES       :	Note that a ''STR_VERSION'' structure consists of four
						''unsigned char'', while this macro consists only of three
						explicit ''0'' bytes. The fourth and last ASCII ''0'' is
						implied by the C language specification --- it terminates
						the string.

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2015 Michael L. Brock

	OUTPUT INDEX:	STR_VERSION_NUMBER_NULL
						Macros and Manifest Constants:STR_VERSION_NUMBER_NULL
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	STR_VERSION_NUMBER_NULL

   PUBLISH NAME:	STR_VERSION_NUMBER_NULL

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define STR_VERSION_NUMBER_NULL			(*((STR_VERSION *) "\0\0\0"))
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* *********************************************************************** */
#define STRFUNCS_ADJUST_SIZE(in_size, adjust)										\
	((unsigned long) (((((unsigned long) (in_size))) <								\
	(((unsigned long) (adjust)))) ? (((unsigned long) (adjust))) :				\
	(!((((unsigned long) (in_size))) % (((unsigned long) (adjust))))) ?		\
	(((unsigned long) (in_size))) :														\
	((((((unsigned long) (in_size))) /													\
	(((unsigned long) (adjust)))) + 1L) * (((unsigned long) (adjust))))))

#define STRFUNCS_ADJUST_SIZE_NO_MIN(in_size, adjust)								\
	((unsigned long) (((((unsigned long) (in_size))) <								\
	(((unsigned long) (adjust)))) ? 0L :												\
	(!((((unsigned long) (in_size))) % (((unsigned long) (adjust))))) ?		\
	(((unsigned long) (in_size))) :														\
	((((((unsigned long) (in_size))) /													\
	(((unsigned long) (adjust)))) + 1L) *												\
	(((unsigned long) (adjust))))))
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* *********************************************************************** */
/*
	ADF NOTE: ADF comments needed.
*/
#define STRFUNCS_NULL_TO_STR(in_ptr)							\
	(((in_ptr) == NULL) ? "" : (in_ptr))
#define STR_NULL_TO_STR(in_ptr)									\
	STRFUNCS_NULL_TO_STR(in_ptr)

#define STR_NULL_TO_EMPTY(in_ptr)								\
	STRFUNCS_NULL_TO_STR(in_ptr)
#define STR_NULL_TO_DEFAULT(in_ptr, in_default)				\
	(((in_ptr) == NULL) ? (in_default) : (in_ptr))

#define STR_EMPTY_TO_NULL(in_ptr)								\
	(((in_ptr) == NULL) ? NULL : ((*(in_ptr)) ? in_ptr : NULL))

#define STR_EMPTY_TO_DEFAULT(in_ptr, in_default)			\
	(((in_ptr) == NULL) ? NULL : ((*(in_ptr)) ? (in_ptr) : (in_default)))

#define STR_EMPTY_OR_NULL_TO_DEFAULT(in_ptr, in_default)	\
	(((in_ptr) == NULL) ? (in_default) : ((*(in_ptr)) ? (in_ptr) : (in_default)))
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/*
	ADF NOTE: ADF comments needed.
*/
/* *********************************************************************** */
#define STRFUNCS_CHAR_IS_EOL_CHAR(in_char)										\
	((((in_char) == '\n') || ((in_char) == '\r')) ? 1 : 0)

#define STRFUNCS_MEMPTR_IS_EOL_CHAR_1(in_ptr)									\
	(((in_ptr) == NULL) ? 0 :															\
	STRFUNCS_CHAR_IS_EOL_CHAR(*((const char *) (in_ptr))))

#define STRFUNCS_MEMPTR_IS_EOL_CHAR_2(in_ptr)									\
	((STRFUNCS_MEMPTR_IS_EOL_CHAR_1(in_ptr) &&									\
	STRFUNCS_CHAR_IS_EOL_CHAR(*(((const char *) (in_ptr)) + 1)) &&			\
	(*((const char *) (in_ptr)) != *(((const char *) (in_ptr)) + 1))) ?	\
	1 : 0)

/*
	If 1-character EOL, returns '1'.
	If 2-character EOL, returns '2'.
	Otherwise, returns '0'.
*/
#define STRFUNCS_MEMPTR_IS_EOL(in_ptr, in_length)								\
	((((in_length) < 1) || ((in_ptr) == NULL)) ? 0 :							\
	((((in_length) > 1) && STRFUNCS_MEMPTR_IS_EOL_CHAR_2(in_ptr)) ? 2 :	\
	STRFUNCS_CHAR_IS_EOL_CHAR(*((const char *) (in_ptr)))))

#define STRFUNCS_STRPTR_IS_EOL_CHAR_1(in_ptr)									\
	STRFUNCS_MEMPTR_IS_EOL_CHAR_1(in_ptr)

#define STRFUNCS_STRPTR_IS_EOL_CHAR_2(in_ptr)									\
	STRFUNCS_MEMPTR_IS_EOL_CHAR_2(in_ptr)

#define STRFUNCS_STRPTR_IS_EOL(in_ptr)												\
	((((in_ptr) == NULL) || (!(*(in_ptr)))) ? 0 :								\
	STRFUNCS_MEMPTR_IS_EOL(in_ptr, 2))
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/*		Some macros defined for use in 'ctype'-like functionality . . .		*/
/* *********************************************************************** */

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		These are safe equivalents of the 'ctype.h' case-conversions	*/
	/*	as not all compiler implementations perform them safely for those	*/
	/*	characters which are not alphabetic.										*/
	/*	*****************************************************************	*/
#define STRFUNCS_toupper(c)			((char) (islower(c) ? toupper(c) : (c)))
#define STRFUNCS_tolower(c)			((char) (isupper(c) ? tolower(c) : (c)))
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		For backward-compatibility with older versions of the library.	*/
	/*	*****************************************************************	*/
#define strfmacs_toupper				STRFUNCS_toupper
#define strfmacs_tolower				STRFUNCS_tolower
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Define symbol macros if not already defined . . .					*/
	/*	*****************************************************************	*/
#ifndef isascii
# define isascii(c)					(((c) >= 0) && ((c) <= 0x7f))
#endif /* #ifndef isascii */

#ifndef isbdigit
# define isbdigit(c)					(((c) == '0') || ((c) == '1'))
#endif /* #ifndef isbdigit */

#ifndef isodigit
# define isodigit(c)					(isdigit(c) && ((c) != '8') && ((c) != '9'))
#endif /* #ifndef isodigit */

#ifndef iscsymf
# define iscsymf(c)					(isalpha(c) || ((c) == '_'))
#endif /* #ifndef iscsymf */

#ifndef iscsym
# define iscsym(c)					(isalnum(c) || ((c) == '_'))
#endif /* #ifndef iscsym */
	/*	*****************************************************************	*/

/*	***********************************************************************	*/

/*	***********************************************************************	*/
	/*	*****************************************************************
		*****************************************************************
		The basic definitions, without sign . . .
		*****************************************************************	*/
#ifdef _MSC_VER
/*
	We do the following because Microsoft Visual C++ complains about
	anonymous structures within parenthetical expressions . . .
*/
#pragma warning(push)
#pragma warning(disable:4820)
struct STR_ALIGN_ANON_c { char c; char    m; };
struct STR_ALIGN_ANON_s { char c; short   m; };
struct STR_ALIGN_ANON_i { char c; int     m; };
struct STR_ALIGN_ANON_l { char c; long    m; };
struct STR_ALIGN_ANON_f { char c; float   m; };
struct STR_ALIGN_ANON_d { char c; double  m; };
struct STR_ALIGN_ANON_p { char c; void   *m; };
#pragma warning(pop)
#define STR_ALIGN_CHAR				\
	offsetof(struct STR_ALIGN_ANON_c, m)
#define STR_ALIGN_SHORT				\
	offsetof(struct STR_ALIGN_ANON_s, m)
#define STR_ALIGN_INT				\
	offsetof(struct STR_ALIGN_ANON_i, m)
#define STR_ALIGN_LONG				\
	offsetof(struct STR_ALIGN_ANON_l, m)
#define STR_ALIGN_FLOAT				\
	offsetof(struct STR_ALIGN_ANON_f, m)
#define STR_ALIGN_DOUBLE			\
	offsetof(struct STR_ALIGN_ANON_d, m)
#define STR_ALIGN_PTR				\
	offsetof(struct STR_ALIGN_ANON_p, m)
#else
#define STR_ALIGN_CHAR				offsetof(struct { char c; char    m; }, m)
#define STR_ALIGN_SHORT				offsetof(struct { char c; short   m; }, m)
#define STR_ALIGN_INT				offsetof(struct { char c; int     m; }, m)
#define STR_ALIGN_LONG				offsetof(struct { char c; long    m; }, m)
#define STR_ALIGN_FLOAT				offsetof(struct { char c; float   m; }, m)
#define STR_ALIGN_DOUBLE			offsetof(struct { char c; double  m; }, m)
#define STR_ALIGN_PTR				offsetof(struct { char c; void   *m; }, m)
#endif /* #ifdef _MSC_VER */
	/*	*****************************************************************
		*****************************************************************
		We assume here that the alignment requirements are the same
		regardless of sign . . .
		*****************************************************************	*/
#define STR_ALIGN_SCHAR				STR_ALIGN_CHAR
#define STR_ALIGN_UCHAR				STR_ALIGN_CHAR
#define STR_ALIGN_SSHORT			STR_ALIGN_SHORT
#define STR_ALIGN_USHORT			STR_ALIGN_SHORT
#define STR_ALIGN_SINT				STR_ALIGN_INT
#define STR_ALIGN_UINT				STR_ALIGN_INT
#define STR_ALIGN_SLONG				STR_ALIGN_LONG
#define STR_ALIGN_ULONG				STR_ALIGN_LONG
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Use these macros to get unaligned data from the 'src' pointer
		into the area of the appropriate type to which the 'dst' pointer
		points.
		*****************************************************************	*/
#define STR_ALIGN_GET_SCHAR(src, dst)							\
	((((unsigned int) (src)) % STR_ALIGN_SCHAR) ?			\
		memcpy((dst), (src), sizeof(signed char)) :			\
		((*(dst) = *((signed char *) ((void *) (src)))), (dst)))
#define STR_ALIGN_GET_UCHAR(src, dst)							\
	((((unsigned int) (src)) % STR_ALIGN_UCHAR) ?			\
		memcpy((dst), (src), sizeof(unsigned char)) :		\
		((*(dst) = *((unsigned char *) ((void *) (src)))), (dst)))
#define STR_ALIGN_GET_SSHORT(src, dst)							\
	((((unsigned int) (src)) % STR_ALIGN_SSHORT) ?			\
		memcpy((dst), (src), sizeof(signed short)) :			\
		((*(dst) = *((signed short *) ((void *) (src)))), (dst)))
#define STR_ALIGN_GET_USHORT(src, dst)							\
	((((unsigned int) (src)) % STR_ALIGN_USHORT) ?			\
		memcpy((dst), (src), sizeof(unsigned short)) :		\
		((*(dst) = *((unsigned short *) ((void *) (src)))), (dst)))
#define STR_ALIGN_GET_SINT(src, dst)							\
	((((unsigned int) (src)) % STR_ALIGN_SINT) ?				\
		memcpy((dst), (src), sizeof(signed int)) :			\
		((*(dst) = *((signed int *) ((void *) (src)))), (dst)))
#define STR_ALIGN_GET_UINT(src, dst)							\
	((((unsigned int) (src)) % STR_ALIGN_UINT) ?				\
		memcpy((dst), (src), sizeof(unsigned int)) :			\
		((*(dst) = *((unsigned int *) ((void *) (src)))), (dst)))
#define STR_ALIGN_GET_SLONG(src, dst)							\
	((((unsigned int) (src)) % STR_ALIGN_SLONG) ?			\
		memcpy((dst), (src), sizeof(signed long)) :			\
		((*(dst) = *((signed long *) ((void *) (src)))), (dst)))
#define STR_ALIGN_GET_ULONG(src, dst)							\
	((((unsigned int) (src)) % STR_ALIGN_ULONG) ?			\
		memcpy((dst), (src), sizeof(unsigned long)) :		\
		((*(dst) = *((unsigned long *) ((void *) (src)))), (dst)))
#define STR_ALIGN_GET_FLOAT(src, dst)							\
	((((unsigned int) (src)) % STR_ALIGN_FLOAT) ?			\
		memcpy((dst), (src), sizeof(float)) :					\
		((*(dst) = *((float *) ((void *) (src)))), (dst)))
#define STR_ALIGN_GET_DOUBLE(src, dst)							\
	((((unsigned int) (src)) % STR_ALIGN_DOUBLE) ?			\
		memcpy((dst), (src), sizeof(double)) :					\
		((*(dst) = *((double *) ((void *) (src)))), (dst)))
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Use these macros to set unaligned data into the 'dst' pointer
		from the area of the appropriate type to which the 'src' pointer
		points.
		*****************************************************************	*/
#define STR_ALIGN_SET_SCHAR(src, dst)							\
	((((unsigned int) (dst)) % STR_ALIGN_SCHAR) ?			\
		memcpy((dst), (src), sizeof(signed char)) :			\
		(*((signed char *) ((void *) (dst))) = *(src), (dst)))
#define STR_ALIGN_SET_UCHAR(src, dst)							\
	((((unsigned int) (dst)) % STR_ALIGN_UCHAR) ?			\
		memcpy((dst), (src), sizeof(unsigned char)) :		\
		(*((unsigned char *) ((void *) (dst))) = *(src), (dst)))
#define STR_ALIGN_SET_SSHORT(src, dst)							\
	((((unsigned int) (dst)) % STR_ALIGN_SSHORT) ?			\
		memcpy((dst), (src), sizeof(signed short)) :			\
		(*((signed short *) ((void *) (dst))) = *(src), (dst)))
#define STR_ALIGN_SET_USHORT(src, dst)							\
	((((unsigned int) (dst)) % STR_ALIGN_USHORT) ?			\
		memcpy((dst), (src), sizeof(unsigned short)) :		\
		(*((unsigned short *) ((void *) (dst))) = *(src), (dst)))
#define STR_ALIGN_SET_SINT(src, dst)							\
	((((unsigned int) (dst)) % STR_ALIGN_SINT) ?				\
		memcpy((dst), (src), sizeof(signed int)) :			\
		(*((signed int *) ((void *) (dst))) = *(src), (dst)))
#define STR_ALIGN_SET_UINT(src, dst)							\
	((((unsigned int) (dst)) % STR_ALIGN_UINT) ?				\
		memcpy((dst), (src), sizeof(unsigned int)) :			\
		(*((unsigned int *) ((void *) (dst))) = *(src), (dst)))
#define STR_ALIGN_SET_SLONG(src, dst)							\
	((((unsigned int) (dst)) % STR_ALIGN_SLONG) ?			\
		memcpy((dst), (src), sizeof(signed long)) :			\
		(*((signed long *) ((void *) (dst))) = *(src), (dst)))
#define STR_ALIGN_SET_ULONG(src, dst)							\
	((((unsigned int) (dst)) % STR_ALIGN_ULONG) ?			\
		memcpy((dst), (src), sizeof(unsigned long)) :		\
		(*((unsigned long *) ((void *) (dst))) = *(src), (dst)))
#define STR_ALIGN_SET_FLOAT(src, dst)							\
	((((unsigned int) (dst)) % STR_ALIGN_FLOAT) ?			\
		memcpy((dst), (src), sizeof(float)) :					\
		(*((float *) ((void *) (dst))) = *(src), (dst)))
#define STR_ALIGN_SET_DOUBLE(src, dst)							\
	((((unsigned int) (dst)) % STR_ALIGN_DOUBLE) ?			\
		memcpy((dst), (src), sizeof(double)) :					\
		(*((double *) ((void *) (dst))) = *(src), (dst)))
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		These get convenience macros assume signed quantities . . .
		*****************************************************************	*/
#define STR_ALIGN_GET_CHAR(src, dst)								\
	STR_ALIGN_GET_SCHAR((src), (dst))
#define STR_ALIGN_GET_SHORT(src, dst)								\
	STR_ALIGN_GET_SSHORT((src), (dst))
#define STR_ALIGN_GET_INT(src, dst)									\
	STR_ALIGN_GET_SINT((src), (dst))
#define STR_ALIGN_GET_LONG(src, dst)								\
	STR_ALIGN_GET_SLONG((src), (dst))
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		These set convenience macros assume signed quantities . . .
		*****************************************************************	*/
#define STR_ALIGN_SET_CHAR(src, dst)								\
	STR_ALIGN_SET_SCHAR((src), (dst))
#define STR_ALIGN_SET_SHORT(src, dst)								\
	STR_ALIGN_SET_SSHORT((src), (dst))
#define STR_ALIGN_SET_INT(src, dst)									\
	STR_ALIGN_SET_SINT((src), (dst))
#define STR_ALIGN_SET_LONG(src, dst)								\
	STR_ALIGN_SET_SLONG((src), (dst))
	/*	*****************************************************************	*/

/*	***********************************************************************	*/

/*	***********************************************************************	*/
typedef COMPAT_FN_TYPE(void * (*STR_FUNC_TYPE_fopen),
	(const char *file_name, const char *file_mode));
typedef COMPAT_FN_TYPE(int    (*STR_FUNC_TYPE_fclose),
	(void *fstream));
typedef COMPAT_FN_TYPE(int    (*STR_FUNC_TYPE_fread),
	(void *data, size_t size, size_t count, void *fstream));
typedef COMPAT_FN_TYPE(int    (*STR_FUNC_TYPE_fwrite),
	(const void *data, size_t size, size_t count, void *fstream));
typedef COMPAT_FN_TYPE(char * (*STR_FUNC_TYPE_fgets),
	(char *a_string, int length, void *fstream));
typedef COMPAT_FN_TYPE(int    (*STR_FUNC_TYPE_fputs),
	(const char *a_string, void *fstream));
typedef COMPAT_FN_TYPE(int    (*STR_FUNC_TYPE_fgetc),
	(void *fstream));
typedef COMPAT_FN_TYPE(int    (*STR_FUNC_TYPE_fputc),
	(int a_char, void *fstream));
typedef COMPAT_FN_TYPE(int    (*STR_FUNC_TYPE_fseek),
	(void *fstream, long offset, int whence));
typedef COMPAT_FN_TYPE(long   (*STR_FUNC_TYPE_ftell),
	(void *fstream));
typedef COMPAT_FN_TYPE(int    (*STR_FUNC_TYPE_fflush),
	(void *fstream));
typedef COMPAT_FN_TYPE(void   (*STR_FUNC_TYPE_rewind),
	(void *fstream));
typedef COMPAT_FN_TYPE(int    (*STR_FUNC_TYPE_fprintf),
	(void *, const char *, ...));
typedef COMPAT_FN_TYPE(int (*STR_FUNC_TYPE_fprintf_lead), (void *));
typedef COMPAT_FN_TYPE(int    (*STR_FUNC_TYPE_vfprintf),
	(void *, const char *, va_list arg_list));
typedef COMPAT_FN_TYPE(int    (*STR_FUNC_TYPE_vfprintf_lead), (void *));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#define STR_FUNC_TYPE_fopen_CAST(fptr)				\
	COMPAT_FN_CAST(void *, (const char *, const char *), (fptr))
#define STR_FUNC_TYPE_fclose_CAST(fptr)			\
	COMPAT_FN_CAST(int,    (void *), (fptr))
#define STR_FUNC_TYPE_fread_CAST(fptr)				\
	COMPAT_FN_CAST(int,    (void *, size_t, size_t, void *), (fptr))
#define STR_FUNC_TYPE_fwrite_CAST(fptr)			\
	COMPAT_FN_CAST(int,    (const void *, size_t, size_t, void *), (fptr))
#define STR_FUNC_TYPE_fgets_CAST(fptr)				\
	COMPAT_FN_CAST(char *, (char *a_string, int length, void *fstream), (fptr))
#define STR_FUNC_TYPE_fputs_CAST(fptr)				\
	COMPAT_FN_CAST(int,    (const char *a_string, void *fstream), (fptr))
#define STR_FUNC_TYPE_fgetc_CAST(fptr)				\
	COMPAT_FN_CAST(int,    (void *fstream), (fptr))
#define STR_FUNC_TYPE_fputc_CAST(fptr)				\
	COMPAT_FN_CAST(int,    (int a_char, void *fstream), (fptr))
#define STR_FUNC_TYPE_fseek_CAST(fptr)				\
	COMPAT_FN_CAST(int,    (void *, long, int), (fptr))
#define STR_FUNC_TYPE_ftell_CAST(fptr)				\
	COMPAT_FN_CAST(long,   (void *), (fptr))
#define STR_FUNC_TYPE_fflush_CAST(fptr)			\
	COMPAT_FN_CAST(int,    (void *fstream), (fptr))
#define STR_FUNC_TYPE_rewind_CAST(fptr)			\
	COMPAT_FN_CAST(void,   (void *fstream), (fptr))
#define STR_FUNC_TYPE_fprintf_CAST(fptr)			\
	COMPAT_FN_CAST(int,    (void *, const char *, ...), (fptr))
#define STR_FUNC_TYPE_fprintf_lead_CAST(fptr)	\
	COMPAT_FN_CAST(int,    (void *), (fptr))
#define STR_FUNC_TYPE_vfprintf_CAST(fptr)			\
	COMPAT_FN_CAST(int,    (void *, const char *, va_list arg_list), (fptr))
#define STR_FUNC_TYPE_vfprintf_lead_CAST(fptr)	\
	COMPAT_FN_CAST(int,    (void *), (fptr))
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef struct {
	STR_FUNC_TYPE_fopen    fopen_func;
	STR_FUNC_TYPE_fclose   fclose_func;
	STR_FUNC_TYPE_fread    fread_func;
	STR_FUNC_TYPE_fwrite   fwrite_func;
	STR_FUNC_TYPE_fgets    fgets_func;
	STR_FUNC_TYPE_fputs    fputs_func;
	STR_FUNC_TYPE_fgetc    fgetc_func;
	STR_FUNC_TYPE_fputc    fputc_func;
	STR_FUNC_TYPE_fseek    fseek_func;
	STR_FUNC_TYPE_ftell    ftell_func;
	STR_FUNC_TYPE_fflush   fflush_func;
	STR_FUNC_TYPE_rewind   rewind_func;
	STR_FUNC_TYPE_fprintf  fprintf_func;
	STR_FUNC_TYPE_vfprintf vfprintf_func;
} STR_CFILE_FUNCS;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#define STR_EMIT_LEAD_CAST(fptr)			STR_FUNC_TYPE_fprintf_lead_CAST(fptr)
#define STR_EMIT_TEXT_CAST(fptr)       STR_FUNC_TYPE_fprintf_CAST(fptr)

#define STR_EMIT_LEAD_CAST_VA(fptr)		STR_FUNC_TYPE_vfprintf_lead_CAST(fptr)
#define STR_EMIT_TEXT_CAST_VA(fptr)		STR_FUNC_TYPE_vfprintf_CAST(fptr)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
typedef COMPAT_FN_TYPE(int (*STR_CMP_FUNC_TYPE),
	(void *control_ptr, const void *ptr_1, const void *ptr_2, size_t d_length));
#define STR_CMP_FUNC_CAST(fptr)				\
	COMPAT_FN_CAST(int, (void *, const void *, const void *, size_t), (fptr))
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifdef _Windows
# define STR_CAST_FUNC_PTR(func_ptr)   ((void *) ((unsigned long) (func_ptr)))
#else
# define STR_CAST_FUNC_PTR(func_ptr)	((void *) (func_ptr))
#endif /* #ifdef _Windows */
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#define STR_CMP_PTR(ptr_1, ptr_2)											\
	((STR_CAST_FUNC_PTR(ptr_1) < STR_CAST_FUNC_PTR(ptr_2)) ? -1 :	\
	((STR_CAST_FUNC_PTR(ptr_1) > STR_CAST_FUNC_PTR(ptr_2)) ? 1  : 0))
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#define STR_IS_NUMBER_FLAG_NONE			((unsigned int) 0)
#define STR_IS_NUMBER_FLAG_NEGATIVE		((unsigned int) 1)
#define STR_IS_NUMBER_FLAG_FLOATING		((unsigned int) 2)
#define STR_IS_NUMBER_FLAG_SCIENTIFIC	((unsigned int) 4)
#define STR_IS_NUMBER_FLAG_ALL												\
	(STR_IS_NUMBER_FLAG_NEGATIVE | STR_IS_NUMBER_FLAG_FLOATING |	\
	 STR_IS_NUMBER_FLAG_SCIENTIFIC)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
COMPAT_FN_DECL(int STR_IsSIntString, (const char *string_ptr));
COMPAT_FN_DECL(int STR_IsUIntString, (const char *string_ptr));
COMPAT_FN_DECL(int STR_IsFloatString, (const char *string_ptr,
	const char *decimal_point));
COMPAT_FN_DECL(int STR_IsNumberString, (const char *string_ptr,
	unsigned int flags, const char *decimal_point));
COMPAT_FN_DECL(int STR_IsNumberStringBasic, (const char *string_ptr,
	unsigned int string_length, unsigned int flags, const char *decimal_point));
COMPAT_FN_DECL(int STR_DetermineNumberString, (const char *string_ptr,
	unsigned int flags, const char *decimal_point, unsigned int start_index,
	unsigned int end_index, unsigned int *new_end_index));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
COMPAT_FN_DECL(int STR_CheckValueSCharString,
	(const char *string_ptr, char *error_text));
COMPAT_FN_DECL(int STR_CheckValueUCharString,
	(const char *string_ptr, char *error_text));
COMPAT_FN_DECL(int STR_CheckValueSShortString,
	(const char *string_ptr, char *error_text));
COMPAT_FN_DECL(int STR_CheckValueUShortString,
	(const char *string_ptr, char *error_text));
COMPAT_FN_DECL(int STR_CheckValueSIntString,
	(const char *string_ptr, char *error_text));
COMPAT_FN_DECL(int STR_CheckValueUIntString,
	(const char *string_ptr, char *error_text));
COMPAT_FN_DECL(int STR_CheckValueSLongString,
	(const char *string_ptr, char *error_text));
COMPAT_FN_DECL(int STR_CheckValueULongString,
	(const char *string_ptr, char *error_text));
COMPAT_FN_DECL(int STR_CheckValueFloatString,
	(const char *string_ptr,
	const char *decimal_point, char *error_text));
COMPAT_FN_DECL(int STR_CheckValueDoubleString,
	(const char *string_ptr,
	const char *decimal_point, char *error_text));
COMPAT_FN_DECL(int STR_CheckSIntString,
	(const char *string_ptr, char *error_text));
COMPAT_FN_DECL(int STR_CheckUIntString,
	(const char *string_ptr, char *error_text));
COMPAT_FN_DECL(int STR_CheckFloatString,
	(const char *string_ptr, const char *decimal_point, char *error_text));
COMPAT_FN_DECL(int STR_CheckNumberString,
	(const char *string_ptr, unsigned int flags,
	const char *decimal_point, char *error_text));
COMPAT_FN_DECL(int STR_CheckNumberStringBasic,
	(const char *string_ptr,
	unsigned int string_length, unsigned int flags,
	const char *decimal_point, char *error_text));
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	RADIX50_ITEM

	DESCRIPTION	:	The ``typedef``ed data type ''RADIX50_ITEM'' describes an
						element of storage for RADIX-50 data.

	NOTES			:	The ''RADIX50_ITEM'' data type is declared as follows:

						(-) typedef unsigned short RADIX50_ITEM;

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1990 - 2015 Michael L. Brock

	OUTPUT INDEX:	RADIX50_ITEM

	PUBLISH XREF:	RADIX50_ITEM

	PUBLISH NAME:	RADIX50_ITEM

	ENTRY CLASS	:	Data Structures

EOH */
/* *********************************************************************** */
typedef unsigned short RADIX50_ITEM;
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	BASE NAME	:	RADIX-50 Macros

	NAME			:	RADIX-50 Macros

	DESCRIPTION	:	Macros associated with the STRFUNCS RADIX-50 facility.

						(.) ''RADIX50_CHARS_PER_RADIX50''

						(-) Is the number of characters which can be stored in a
						''RADIX50_ITEM''.

						(.) ''RADIX50_SLEN_TO_RCNT(''``str_len``'')''

						(-) Given the length of a string in ``str_len``, determines
						the number of ''RADIX50_ITEMS'' needed to store the
						RADIX-50 equivalent of the string.

						(.) ''RADIX50_SPTR_TO_RCNT(''``str``'')''

						(-) Given a string pointer in ``str``, determines
						the number of ''RADIX50_ITEMS'' needed to store the
						RADIX-50 equivalent of the string.

						(.) ''RADIX50_SLEN_TO_RLEN(''``str_len``'')''

						(-) Given the length of a string in ``str_len``, determines
						the total number of bytes used by ''RADIX50_ITEMS'' needed
						to store the RADIX-50 equivalent of the string.

						(.) ''RADIX50_SPTR_TO_RLEN(''``str``'')''

						(-) Given the string pointer in ``str``, determines
						the total number of bytes used by ''RADIX50_ITEMS'' needed
						to store the RADIX-50 equivalent of the string.

						(.) ''RADIX50_RCNT_TO_SLEN(''``rad_cnt``'')''

						(-) Given the number of ''RADIX50_ITEM'' elements in
						``rad_cnt``, determines the length of the string needed
						to store the ASCII equivalent of the RADIX-50 array (not
						including the terminating ASCII ''NULL'' byte).

						(.) ''RADIX50_RLEN_TO_SLEN(''``rad_len``'')''

						(-) Given the number of bytes used by ''RADIX50_ITEM''
						elements in ``rad_len``, determines the length of the string
						needed to store the ASCII equivalent of the RADIX-50 array
						(not including the terminating ASCII ''NULL'' byte).

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1990 - 2015 Michael L. Brock

	OUTPUT INDEX:	RADIX50_CHARS_PER_RADIX50
						RADIX50_SLEN_TO_RCNT
						RADIX50_SPTR_TO_RCNT
						RADIX50_SLEN_TO_RLEN
						RADIX50_SPTR_TO_RLEN
						RADIX50_RCNT_TO_SLEN
						RADIX50_RLEN_TO_SLEN
						RADIX-50 Macros:RADIX50_SLEN_TO_RCNT
						RADIX-50 Macros:RADIX50_SPTR_TO_RCNT
						RADIX-50 Macros:RADIX50_SLEN_TO_RLEN
						RADIX-50 Macros:RADIX50_SPTR_TO_RLEN
						RADIX-50 Macros:RADIX50_RCNT_TO_SLEN
						RADIX-50 Macros:RADIX50_RLEN_TO_SLEN
						STRFUNCS Manifest Constants:RADIX50_CHARS_PER_RADIX50
						STRFUNCS Defines:RADIX50_CHARS_PER_RADIX50
						STRFUNCS Defines:RADIX50_SLEN_TO_RCNT
						STRFUNCS Defines:RADIX50_SPTR_TO_RCNT
						STRFUNCS Defines:RADIX50_SLEN_TO_RLEN
						STRFUNCS Defines:RADIX50_SPTR_TO_RLEN
						STRFUNCS Defines:RADIX50_RCNT_TO_SLEN
						STRFUNCS Defines:RADIX50_RLEN_TO_SLEN


	PUBLISH XREF:	RADIX50_CHARS_PER_RADIX50
						RADIX50_SLEN_TO_RCNT
						RADIX50_SPTR_TO_RCNT
						RADIX50_SLEN_TO_RLEN
						RADIX50_SPTR_TO_RLEN
						RADIX50_RCNT_TO_SLEN
						RADIX50_RLEN_TO_SLEN

	PUBLISH NAME:	RADIX-50 Macros
						RADIX50_CHARS_PER_RADIX50
						RADIX50_SLEN_TO_RCNT
						RADIX50_SPTR_TO_RCNT
						RADIX50_SLEN_TO_RLEN
						RADIX50_SPTR_TO_RLEN
						RADIX50_RCNT_TO_SLEN
						RADIX50_RLEN_TO_SLEN

	ENTRY CLASS	:	Macro Definitions

EOH */
/* *********************************************************************** */
/*
	Number of characters which can be stored in a RADIX-50 item.
*/
#define RADIX50_CHARS_PER_RADIX50		3

/*
	How many RADIX-50 elements for a given ASCII string length ?
*/
#define RADIX50_SLEN_TO_RCNT(str_len)				\
	(((str_len) / RADIX50_CHARS_PER_RADIX50) +	\
	(((str_len) % RADIX50_CHARS_PER_RADIX50) ? 1 : 0))

/*
	How many RADIX-50 elements for a given ASCII string?
*/
#define RADIX50_SPTR_TO_RCNT(str)		\
	RADIX50_SLEN_TO_RCNT(strlen(str))

/*
	How many RADIX-50 bytes for a given ASCII string length ?
*/
#define RADIX50_SLEN_TO_RLEN(str_len)	\
	(RADIX50_SLEN_TO_RCNT(str_len) * sizeof(RADIX50_ITEM))

/*
	How many RADIX-50 bytes for a given ASCII string?
*/
#define RADIX50_SPTR_TO_RLEN(str)		\
	(RADIX50_SPTR_TO_RCNT(str) * sizeof(RADIX50_ITEM))

/*
	How long an ASCII string for a given number of RADIX-50 elements
	(exclusive of the ASCII ''NUL'' byte terminator).
*/
#define RADIX50_RCNT_TO_SLEN(rad_cnt)	\
	((rad_cnt) * RADIX50_CHARS_PER_RADIX50)

/*
	How long an ASCII string for a given number of RADIX-50 bytes
	(exclusive of the ASCII ''NUL'' byte terminator).
*/
#define RADIX50_RLEN_TO_SLEN(rad_len)	\
	RADIX50_RCNT_TO_SLEN(((rad_len) / sizeof(RADIX50_ITEM)) + \
	(((rad_len) % sizeof(RADIX50_ITEM)) ? 1 : 0))
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Function prototypes for RADIX-50 functions . . .								*/
/*	***********************************************************************	*/

COMPAT_FN_DECL(unsigned int  RADIX50_asctorad,
	(const char *in_asc, RADIX50_ITEM *out_rad));
COMPAT_FN_DECL(unsigned int  RADIX50_asctorad_basic,
	(const char *in_asc,
	RADIX50_ITEM *out_rad, const unsigned char *ascii_table));
COMPAT_FN_DECL(int           RADIX50_checkrad,
	(const char *in_string,
	unsigned int *bad_position));
COMPAT_FN_DECL(int           RADIX50_checkrad_basic,
	(const char *in_string,
	unsigned int *bad_position, const unsigned char *radix50_table));
COMPAT_FN_DECL(void          RADIX50_init_tables,
	(const char *in_string, int lower_case_flag,
	unsigned char *out_ascii_table, unsigned char *out_radix50_table));
COMPAT_FN_DECL(char         *RADIX50_radtoasc,
	(const RADIX50_ITEM *in_rad, char *out_asc,
	unsigned int rad_len));
COMPAT_FN_DECL(char         *RADIX50_radtoasc_basic,
	(const RADIX50_ITEM *in_rad,
	char *out_asc, unsigned int rad_len, const unsigned char *radix50_table));

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Function prototypes for the Boyer-Moore string search routines . . .	*/
/*	***********************************************************************	*/

COMPAT_FN_DECL(unsigned int *BoyerMoore_mem_init_jump,
	(unsigned int target_length,
	const void *target_area, unsigned int *jump_array));
COMPAT_FN_DECL(unsigned int *BoyerMoore_mem_init_match,
	(unsigned int target_length,
	const void *target_area, unsigned int *match_array));
COMPAT_FN_DECL(unsigned int *BoyerMoore_mem_alloc_match,
	(unsigned int target_length,
	const void *target_area));
COMPAT_FN_DECL(void         *BoyerMoore_mem_search,
	(unsigned int search_length,
	const void *search_area, unsigned int target_length,
	const void *target_area));
COMPAT_FN_DECL(void         *BoyerMoore_mem_search_basic,
	(unsigned int search_length,
	const void *search_area, unsigned int target_length,
	const void *target_area, unsigned int *jump_array,
	unsigned int *match_array));
COMPAT_FN_DECL(unsigned int *BoyerMoore_memi_init_jump,
	(unsigned int target_length,
	const void *target_area, unsigned int *jump_array));
COMPAT_FN_DECL(unsigned int *BoyerMoore_memi_init_match,
	(unsigned int target_length,
	const void *target_area, unsigned int *match_array));
COMPAT_FN_DECL(unsigned int *BoyerMoore_memi_alloc_match,
	(unsigned int target_length,
	const void *target_area));
COMPAT_FN_DECL(void         *BoyerMoore_memi_search,
	(unsigned int search_length,
	const void *search_area, unsigned int target_length,
	const void *target_area));
COMPAT_FN_DECL(void         *BoyerMoore_memi_search_basic,
	(unsigned int search_length,
	const void *search_area, unsigned int target_length,
	const void *target_area, unsigned int *jump_array,
	unsigned int *match_array));

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Declarations for STRFUNCS regex functions . . .								*/
/* *********************************************************************** */
/*
	CODE NOTE: To be removed.
COMPAT_FN_DECL(int   STR_re_set_syntax,
	(int syntax));
COMPAT_FN_DECL(char *STR_re_compile_pattern,
	(char *pattern,int size,struct re_pattern_buffer *bufp));
COMPAT_FN_DECL(void  STR_re_compile_fastmap,
	(struct re_pattern_buffer *bufp));
COMPAT_FN_DECL(int   STR_re_search,
	(struct re_pattern_buffer *pbufp,char *string,int size,int startpos,int range,struct re_registers *regs));
COMPAT_FN_DECL(int   STR_re_search_2,
	(struct re_pattern_buffer *pbufp,char *string1,int size1,char *string2,int size2,int startpos,int range,struct re_registers *regs,int mstop));
COMPAT_FN_DECL(int   STR_re_match,
	(struct re_pattern_buffer *pbufp,char *string,int size,int pos,struct re_registers *regs));
COMPAT_FN_DECL(int   STR_re_match_2,
	(struct re_pattern_buffer *pbufp,unsigned char *string1,int size1,unsigned char *string2,int size2,int pos,struct re_registers *regs,int mstop));
COMPAT_FN_DECL(char *STR_re_comp,
	(char *s));
COMPAT_FN_DECL(int   STR_re_exec,
	(char *s));

#ifdef SYNTAX_TABLE
COMPAT_EXTERN_DATA_DECL char *re_syntax_table;
#endif

*/
/* *********************************************************************** */

	/*	*****************************************************************
		*****************************************************************
		Minimum and maximum length manifest constants for the 'val2str()'
		family of functions . . .
		*****************************************************************	*/
#define STR_VAL2STR_MIN_LEN_UNSIGNED	\
	((sizeof(unsigned long) == 4) ? 6 :	\
	 ((sizeof(unsigned long) == 8) ? 11 : 22))
#define STR_VAL2STR_MIN_LEN_SIGNED		(STR_VAL2STR_MIN_LEN_UNSIGNED + 1)
#define STR_VAL2STR_MIN_LEN				STR_VAL2STR_MIN_LEN_SIGNED
#define STR_VAL2STR_MAX_LEN_UNSIGNED	(sizeof(unsigned long) * CHAR_BIT)
#define STR_VAL2STR_MAX_LEN_SIGNED		(1 + STR_VAL2STR_MAX_LEN_UNSIGNED)
#define STR_VAL2STR_MAX_LEN				STR_VAL2STR_MAX_LEN_SIGNED
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Some other general maximums . . .
		*****************************************************************	*/
#define STR_VAL2STR_MAX_LEN_UNSIGNED_02	STR_VAL2STR_MAX_LEN_UNSIGNED
#define STR_VAL2STR_MAX_LEN_SIGNED_02		(STR_VAL2STR_MAX_LEN_UNSIGNED_02 + 1)

#define STR_VAL2STR_MAX_LEN_UNSIGNED_04	\
	((sizeof(unsigned long) == 4) ? 16 :	\
	 ((sizeof(unsigned long) == 8) ? 32 : 64))
#define STR_VAL2STR_MAX_LEN_SIGNED_04		(STR_VAL2STR_MAX_LEN_UNSIGNED_04 + 1)

#define STR_VAL2STR_MAX_LEN_UNSIGNED_08	\
	((sizeof(unsigned long) == 4) ? 11 :	\
	 ((sizeof(unsigned long) == 8) ? 22 : 44))
#define STR_VAL2STR_MAX_LEN_SIGNED_08		(STR_VAL2STR_MAX_LEN_UNSIGNED_08 + 1)

#define STR_VAL2STR_MAX_LEN_UNSIGNED_10	\
	((sizeof(unsigned long) == 4) ? 10 :	\
	 ((sizeof(unsigned long) == 8) ? 20 : 40))
#define STR_VAL2STR_MAX_LEN_SIGNED_10		(STR_VAL2STR_MAX_LEN_UNSIGNED_10 + 1)

#define STR_VAL2STR_MAX_LEN_UNSIGNED_16	\
	((sizeof(unsigned long) == 4) ? 8 :	\
	 ((sizeof(unsigned long) == 8) ? 16 : 32))
#define STR_VAL2STR_MAX_LEN_SIGNED_16		(STR_VAL2STR_MAX_LEN_UNSIGNED_16 + 1)

#define STR_VAL2STR_MAX_LEN_UNSIGNED_36	\
	((sizeof(unsigned long) == 4) ? 7 :	\
	 ((sizeof(unsigned long) == 8) ? 13 : 25))
#define STR_VAL2STR_MAX_LEN_SIGNED_36		(STR_VAL2STR_MAX_LEN_UNSIGNED_36 + 1)

#define STR_VAL2STR_MAX_LEN_UNSIGNED_64	STR_VAL2STR_MIN_LEN_UNSIGNED
#define STR_VAL2STR_MAX_LEN_SIGNED_64		(STR_VAL2STR_MAX_LEN_UNSIGNED_64 + 1)
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Function prototypes for the conversion of numeric values to
		strings . . .
		*****************************************************************	*/
COMPAT_FN_DECL(char *val2str_uint,		  (unsigned int in_value,
	unsigned int in_radix, const char *in_fill_char, char *out_string));
COMPAT_FN_DECL(char *val2str_sint,		  (signed int in_value,
	unsigned int in_radix, const char *in_fill_char, char *out_string));
COMPAT_FN_DECL(char *val2str_uint_cat,	  (unsigned int in_value,
	unsigned int in_radix, const char *in_fill_char, char *out_string));
COMPAT_FN_DECL(char *val2str_sint_cat,	  (signed int in_value,
	unsigned int in_radix, const char *in_fill_char, char *out_string));

COMPAT_FN_DECL(char *val2str_ulong,		  (unsigned long in_value,
	unsigned int in_radix, const char *in_fill_char, char *out_string));
COMPAT_FN_DECL(char *val2str_slong,		  (signed long in_value,
	unsigned int in_radix, const char *in_fill_char, char *out_string));
COMPAT_FN_DECL(char *val2str_ulong_cat,  (unsigned long in_value,
	unsigned int in_radix, const char *in_fill_char, char *out_string));
COMPAT_FN_DECL(char *val2str_slong_cat,  (signed long in_value,
	unsigned int in_radix, const char *in_fill_char, char *out_string));

COMPAT_FN_DECL(char *val2str,            (unsigned long in_value,
	int in_sign, unsigned int in_radix, const char *in_fill_char,
	char *out_string));
COMPAT_FN_DECL(char *val2str_cat,        (unsigned long in_value,
	int in_sign, unsigned int in_radix, const char *in_fill_char,
	char *out_string));
COMPAT_FN_DECL(char *val2str_basic,      (unsigned int radix_char_count,
	const char *radix_char_list, unsigned long in_value, int in_sign,
	unsigned int in_radix, const char *in_fill_char, char *out_string));
COMPAT_FN_DECL(char *val2str_basic_cat,  (unsigned int radix_char_count,
	const char *radix_char_list, unsigned long in_value, int in_sign,
	unsigned int in_radix, const char *in_fill_char, char *out_string));

COMPAT_FN_DECL(char *val2str_ptr,
	(const void *in_value, char *out_string));
COMPAT_FN_DECL(char *val2str_ptr_cat,
	(const void *in_value, char *out_string));
COMPAT_FN_DECL(char *val2str_ptr0,
	(const void *in_value, char *out_string));
COMPAT_FN_DECL(char *val2str_ptr0_cat,
	(const void *in_value, char *out_string));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Function prototypes for the buffer-to-line conversion functions...
		*****************************************************************	*/
COMPAT_FN_DECL(int STR_BufferToLines, (unsigned int buffer_length,
	char *buffer_ptr, unsigned int *line_count, char ***line_list,
	char *error_text));
COMPAT_FN_DECL(int STR_BufferToLines_NoAlloc, (unsigned int buffer_length,
	char *buffer_ptr, unsigned int *line_count, char ***line_list,
	char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Function prototypes for the production of function parameters in
		human-readable form . . .
		*****************************************************************	*/
COMPAT_FN_DECL(char *STR_FormatParamAny,
	(const char *in_type_name, const char *in_string, int flags,
	char *out_string));
COMPAT_FN_DECL(char *STR_FormatParamString,
	(const char *in_type_name, const char *in_string, unsigned int max_length,
	int flags, char *out_string));
COMPAT_FN_DECL(char *STR_FormatParamPtr,
	(const char *in_type_name, const void *in_ptr, int flags,
	char *out_string));
COMPAT_FN_DECL(char *STR_FormatParamHex,
	(const char *in_type_name, unsigned long in_value, int flags,
	char *out_string));
COMPAT_FN_DECL(char *STR_FormatParamOct,
	(const char *in_type_name, unsigned long in_value, int flags,
	char *out_string));
COMPAT_FN_DECL(char *STR_FormatParamBin,
	(const char *in_type_name, unsigned long in_value, int flags,
	char *out_string));
COMPAT_FN_DECL(char *STR_FormatParamUChar,
	(const char *in_type_name, const unsigned char *in_value, int flags,
	char *out_string));
COMPAT_FN_DECL(char *STR_FormatParamSChar,
	(const char *in_type_name, const signed char *in_value, int flags,
	char *out_string));
COMPAT_FN_DECL(char *STR_FormatParamUInt,
	(const char *in_type_name, unsigned int in_value, int flags,
	char *out_string));
COMPAT_FN_DECL(char *STR_FormatParamSInt,
	(const char *in_type_name, signed int in_value, int flags,
	char *out_string));
COMPAT_FN_DECL(char *STR_FormatParamULong,
	(const char *in_type_name, unsigned long in_value, int flags,
	char *out_string));
COMPAT_FN_DECL(char *STR_FormatParamSLong,
	(const char *in_type_name, signed long in_value, int flags,
	char *out_string));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Memory movement deletion wrapper function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int memmove_delete_element,  (unsigned int in_count,
	void *in_list, unsigned int in_size, unsigned int in_position,
	unsigned int delete_count));
COMPAT_FN_DECL(int memmove_delete_voidptr, (unsigned int in_count,
	void **in_list, unsigned int in_position,
	unsigned int delete_count));
COMPAT_FN_DECL(int memmove_delete_charptr, (unsigned int in_count,
	char **in_list, unsigned int in_position,
	unsigned int delete_count));
COMPAT_FN_DECL(int memmove_delete_uint,    (unsigned int in_count,
	unsigned int *in_list, unsigned int in_position,
	unsigned int delete_count));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Memory movement insertion wrapper function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int memmove_insert_element,  (unsigned int in_count,
	void *in_list, unsigned int in_size, unsigned int in_position,
	const void *in_element));
COMPAT_FN_DECL(int memmove_insert_voidptr, (unsigned int in_count,
	void **in_list, unsigned int in_position,
	const void *in_element));
COMPAT_FN_DECL(int memmove_insert_charptr, (unsigned int in_count,
	char **in_list, unsigned int in_position,
	const char *in_element));
COMPAT_FN_DECL(int memmove_insert_uint,    (unsigned int in_count,
	unsigned int *in_list, unsigned int in_position,
	unsigned int in_element));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		General string list comparison function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int strl_CompareLists, (unsigned int in_count_1,
	char **in_list_1, unsigned int in_count_2, char **in_list_2,
	unsigned int *difference_index));
COMPAT_FN_DECL(int strli_CompareLists, (unsigned int in_count_1,
	char **in_list_1, unsigned int in_count_2, char **in_list_2,
	unsigned int *difference_index));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Limited string list comparison function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int strln_CompareLists, (unsigned int in_count_1,
	char **in_list_1, unsigned int in_count_2, char **in_list_2,
	size_t string_length, unsigned int *difference_index));
COMPAT_FN_DECL(int strlni_CompareLists, (unsigned int in_count_1,
	char **in_list_1, unsigned int in_count_2, char **in_list_2,
	size_t string_length, unsigned int *difference_index));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Memory buffer list comparison function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int meml_CompareLists, (unsigned int in_count_1,
	void **in_list_1, unsigned int in_count_2, void **in_list_2,
	size_t data_length, unsigned int *difference_index));
COMPAT_FN_DECL(int memli_CompareLists, (unsigned int in_count_1,
	void **in_list_1, unsigned int in_count_2, void **in_list_2,
	size_t data_length, unsigned int *difference_index));
COMPAT_FN_DECL(int meml_CompareListsBasic, (unsigned int in_count_1,
	void **in_list_1, unsigned int in_count_2, void **in_list_2,
	STR_CMP_FUNC_TYPE compare_func, void *control_ptr, size_t data_length,
	unsigned int *difference_index));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Memory buffer array comparison function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int mema_CompareArrays, (unsigned int in_count_1,
	const void *in_array_1, unsigned int in_count_2, const void *in_array_2,
	size_t data_length, unsigned int *difference_index));
COMPAT_FN_DECL(int memai_CompareArrays, (unsigned int in_count_1,
	const void *in_array_1, unsigned int in_count_2, const void *in_array_2,
	size_t data_length, unsigned int *difference_index));
COMPAT_FN_DECL(int mema_CompareArraysBasic, (unsigned int in_count_1,
	const void *in_array_1, unsigned int in_count_2, const void *in_array_2,
	STR_CMP_FUNC_TYPE compare_func, void *control_ptr, size_t data_length,
	unsigned int *difference_index));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Memory array and list conversion function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int mema_to_meml, (unsigned int in_data_count,
	const void *in_data_array, size_t data_length,
	unsigned int *out_data_count, void ***out_data_list));
COMPAT_FN_DECL(int meml_to_mema, (unsigned int in_data_count,
	void **in_data_list, size_t data_length, unsigned int *out_data_count,
	void **out_data_array));
	/*	*****************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/*	Character Case Function Prototypes . . .											*/
/* *********************************************************************** */

COMPAT_FN_DECL(char *initcaps,
	(char *in_text));
COMPAT_FN_DECL(char *initcaps_basic,
	(const char *in_text, char *out_text));
COMPAT_FN_DECL(char *initcaps_basic_mem,
	(unsigned int in_length, const char *in_text,
	char *out_text));
COMPAT_FN_DECL(char *lower,
	(char *in_text));
COMPAT_FN_DECL(char *lower_basic,
	(const char *in_text, char *out_text));
COMPAT_FN_DECL(char *lower_basic_mem,
	(unsigned int in_length, const char *in_text,
	char *out_text));
COMPAT_FN_DECL(char *upper,
	(char *in_text));
COMPAT_FN_DECL(char *upper_basic,
	(const char *in_text, char *out_text));
COMPAT_FN_DECL(char *upper_basic_mem,
	(unsigned int in_length, const char *in_text,
	char *out_text));

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/*	Justification Function Prototypes . . .											*/
/* *********************************************************************** */

COMPAT_FN_DECL(char *center,
	(char *in_text, unsigned int center_length));
COMPAT_FN_DECL(char *center_basic,
	(const char *in_text, char *out_text, int ltrim_flag,
	int rtrim_flag, const char *center_char, unsigned int center_length));
COMPAT_FN_DECL(char *center_basic_mem,
	(unsigned int in_length, const char *in_text,
	unsigned int *out_length, char *out_text, int ltrim_flag, int rtrim_flag,
	const char *center_char, unsigned int center_length));
COMPAT_FN_DECL(char *centerit,
	(const char *in_text, unsigned int width, char *out_text));
COMPAT_FN_DECL(char *ctltospc,
	(char *));
COMPAT_FN_DECL(char *ljust,
	(char *in_text));
COMPAT_FN_DECL(char *ltrim,
	(char *in_text));
COMPAT_FN_DECL(char *ltrim_basic,
	(const char *in_text, char *out_text));
COMPAT_FN_DECL(char *ltrim_basic_mem,
	(unsigned int in_length, const char *in_text,
	unsigned int *out_length, char *out_text));
COMPAT_FN_DECL(char *ltrimx,
	(char *in_text, const char *trim_string));
COMPAT_FN_DECL(char *ltrimx_basic,
	(const char *in_text, char *out_text,
	const char *trim_string));
COMPAT_FN_DECL(char *ltrimx_basic_mem,
	(unsigned int in_length, const char *in_text,
	unsigned int *out_length, char *out_text, unsigned int trim_length,
	const char *trim_string));
COMPAT_FN_DECL(char *lttrim,
	(char *));
COMPAT_FN_DECL(char *noblank,
	(char *));
COMPAT_FN_DECL(char *nocontrl,
	(char *));
COMPAT_FN_DECL(char *nospace,
	(char *));
COMPAT_FN_DECL(char *oneblank,
	(char *));
COMPAT_FN_DECL(char *rjust,
	(char *in_text));
COMPAT_FN_DECL(char *rtrim,
	(char *in_text));
COMPAT_FN_DECL(char *rtrim_basic,
	(const char *in_text, char *out_text));
COMPAT_FN_DECL(char *rtrim_basic_mem,
	(unsigned int in_length, const char *in_text,
	unsigned int *out_length, char *out_text));
COMPAT_FN_DECL(char *rtrimx,
	(char *in_text, const char *trim_string));
COMPAT_FN_DECL(char *rtrimx_basic,
	(const char *in_text, char *out_text,
	const char *trim_string));
COMPAT_FN_DECL(char *rtrimx_basic_mem,
	(unsigned int in_length, const char *in_text,
	unsigned int *out_length, char *out_text, unsigned int trim_length,
	const char *trim_string));
COMPAT_FN_DECL(char *rttrim,
	(char *));
COMPAT_FN_DECL(char *spctotab,
	(char *in_string, unsigned int tab_setting));
COMPAT_FN_DECL(char *strpadl,
	(char *in_text, unsigned int pad_length));
COMPAT_FN_DECL(char *strpadl_basic,
	(const char *in_text, char *out_text, int ltrim_flag,
	int rtrim_flag, const char *pad_char, unsigned int pad_length));
COMPAT_FN_DECL(char *strpadl_basic_mem,
	(unsigned int in_length, const char *in_text,
	unsigned int *out_length, char *out_text, int ltrim_flag,
	int rtrim_flag, const char *pad_char, unsigned int pad_length));
COMPAT_FN_DECL(char *strpadr,
	(char *in_text, unsigned int pad_length));
COMPAT_FN_DECL(char *strpadr_basic,
	(const char *in_text, char *out_text, int ltrim_flag,
	int rtrim_flag, const char *pad_char, unsigned int pad_length));
COMPAT_FN_DECL(char *strpadr_basic_mem,
	(unsigned int in_length, const char *in_text,
	unsigned int *out_length, char *out_text, int ltrim_flag,
	int rtrim_flag, const char *pad_char, unsigned int pad_length));
COMPAT_FN_DECL(char *tabtospc,
	(char *in_string, unsigned int tab_setting));
COMPAT_FN_DECL(char *trim,
	(char *in_text));
COMPAT_FN_DECL(char *trim_basic,
	(const char *in_text, char *out_text));
COMPAT_FN_DECL(char *trim_basic_mem,
	(unsigned int in_length, const char *in_text,
	unsigned int *out_length, char *out_text));
COMPAT_FN_DECL(char *trimx,
	(char *in_text, const char *trim_string));
COMPAT_FN_DECL(char *trimx_basic,
	(const char *in_text, char *out_text,
	const char *trim_string));
COMPAT_FN_DECL(char *trimx_basic_mem,
	(unsigned int in_length, const char *in_text,
	unsigned int *out_length, char *out_text, unsigned int trim_length,
	const char *trim_string));
COMPAT_FN_DECL(char *ttrim,
	(char *));

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/*		Function prototypes for version functions . . .								*/
/* *********************************************************************** */

COMPAT_FN_DECL(char        *vertostr,
	(const STR_VERSION *version_number, char *version_string));
COMPAT_FN_DECL(STR_VERSION *STRFUNCS_GetVersion,
	(STR_VERSION *version_number));
COMPAT_FN_DECL(char        *STRFUNCS_GetVersionString,
	(char *version_string));

COMPAT_FN_DECL(void         STR_GetVersionNumber,
	(const STR_VERSION *in_version, unsigned int *major, unsigned int *minor,
	unsigned int *release, unsigned int *build));
COMPAT_FN_DECL(STR_VERSION *STR_SetVersionNumber,
	(unsigned int major, unsigned int minor, unsigned int release,
	unsigned int build, STR_VERSION *version_number));

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/*		Function prototypes for emit functions . . .									*/
/* *********************************************************************** */

COMPAT_FN_DECL(void STR_EMIT_Char,
	(int out_character, unsigned int out_count,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void STR_EMIT_CharSpace,
	(int out_character, unsigned int out_count,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void STR_EMIT_CharLine,
	(int out_character, unsigned int out_count,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void STR_EMIT_String,
	(const char *out_string, unsigned int out_count,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void STR_EMIT_StringSpace,
	(const char *out_string, unsigned int out_count,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void STR_EMIT_StringLine,
	(const char *out_string, unsigned int out_count,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void STR_EMIT_SetDefaults,
	(STR_FUNC_TYPE_fprintf *output_function, void **output_control));
COMPAT_FN_DECL(void STR_EMIT_SetDefaultsVA,
	(STR_FUNC_TYPE_vfprintf *output_function, void **output_control));
COMPAT_FN_DECL(STR_CFILE_FUNCS *STR_EMIT_SetDefaultsCFILE_FUNCS,
	(STR_CFILE_FUNCS *cfile_funcs_ptr));
COMPAT_FN_DECL(STR_CFILE_FUNCS *STR_EMIT_GetDefaultsCFILE_FUNCS,
	(STR_CFILE_FUNCS *cfile_funcs_ptr));
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Function prototypes for functions defined within 'strfuncs' . . .		*/
/* *********************************************************************** */

COMPAT_FN_DECL(int mema_add,
	(unsigned int from_data_count, const void *from_data_list,
	size_t data_length, unsigned int *to_data_count, void **to_data_list));
COMPAT_FN_DECL(int mema_append,
	(unsigned int *data_count, void **data_list,
	const void *in_data, size_t data_length));
COMPAT_FN_DECL(int mema_copy,
	(unsigned int in_data_count, const void *in_data_list,
	size_t data_length, unsigned int *out_data_count, void **out_data_list));
COMPAT_FN_DECL(int mema_delta,
	(unsigned int in_count_1, const void *in_list_1,
	unsigned int in_count_2, const void *in_list_2, unsigned int *uniq_count_1,
	unsigned int **uniq_list_1, unsigned int *uniq_count_2,
	unsigned int **uniq_list_2, unsigned int *diff_count,
	unsigned int **diff_list, unsigned int *same_count,
	unsigned int **same_list, size_t data_length));
COMPAT_FN_DECL(int mema_insert,
	(unsigned int *data_count, void **data_list,
	const void *in_data, size_t data_length, unsigned int insert_position));
COMPAT_FN_DECL(int mema_remove,
	(unsigned int *, void **, size_t, unsigned int, unsigned int));
COMPAT_FN_DECL(int mema_remove_all,
	(unsigned int *, void **));
COMPAT_FN_DECL(int mema_search_delta,
	(unsigned int in_count_1, const void *in_list_1,
	unsigned int in_count_2, const void *in_list_2,
	unsigned int *uniq_count_1, unsigned int **uniq_list_1,
	unsigned int *uniq_count_2, unsigned int **uniq_list_2,
	unsigned int *same_count_1, unsigned int **same_list_1,
	unsigned int *same_count_2, unsigned int **same_list_2,
	size_t data_length));
COMPAT_FN_DECL(int memaapp,
	(unsigned int *, void **, const void *, size_t));
COMPAT_FN_DECL(int memacopy,
	(unsigned int, void *, size_t, unsigned int *, void **));
COMPAT_FN_DECL(int memadel,
	(unsigned int *, void **, size_t, unsigned int, unsigned int));
COMPAT_FN_DECL(int memains,
	(unsigned int *data_count, void **data_list,
	const void *in_data, size_t data_length, unsigned int insert_position));
COMPAT_FN_DECL(int memai_delta,
	(unsigned int in_count_1, const void *in_list_1,
	unsigned int in_count_2, const void *in_list_2, unsigned int *uniq_count_1,
	unsigned int **uniq_list_1, unsigned int *uniq_count_2,
	unsigned int **uniq_list_2, unsigned int *diff_count,
	unsigned int **diff_list, unsigned int *same_count,
	unsigned int **same_list, size_t data_length));
COMPAT_FN_DECL(int memai_search_delta,
	(unsigned int in_count_1, const void *in_list_1,
	unsigned int in_count_2, const void *in_list_2,
	unsigned int *uniq_count_1, unsigned int **uniq_list_1,
	unsigned int *uniq_count_2, unsigned int **uniq_list_2,
	unsigned int *same_count_1, unsigned int **same_list_1,
	unsigned int *same_count_2, unsigned int **same_list_2,
	size_t data_length));

COMPAT_FN_DECL(int  MEM_ARRAY_delta,
	(void *control_ptr, unsigned int in_count_1,
	const void *in_list_1, unsigned int in_count_2, const void *in_list_2,
	unsigned int *uniq_count_1, unsigned int **uniq_list_1,
	unsigned int *uniq_count_2, unsigned int **uniq_list_2,
	unsigned int *diff_count, unsigned int **diff_list,
	unsigned int *same_count, unsigned int **same_list, size_t data_length,
	int (*compare_function)(void *, const void *, const void *, size_t)));
COMPAT_FN_DECL(int  MEM_ARRAY_search_delta,
	(void *control_ptr, unsigned int in_count_1,
	const void *in_list_1, unsigned int in_count_2, const void *in_list_2,
	unsigned int *uniq_count_1, unsigned int **uniq_list_1,
	unsigned int *uniq_count_2, unsigned int **uniq_list_2,
	unsigned int *diff_count_1, unsigned int **diff_list_1,
	unsigned int *diff_count_2, unsigned int **diff_list_2,
	unsigned int *same_count_1, unsigned int **same_list_1,
	unsigned int *same_count_2, unsigned int **same_list_2,
	size_t data_length,
	int (*compare_func_1)(void *, const void *, const void *, size_t),
	int (*compare_func_2)(void *, const void *, const void *, size_t)));
COMPAT_FN_DECL(int  STR_ARRAY_bsearch,
	(void *control_ptr, unsigned int data_count,
	const void *data_list, const void *key_data, size_t data_length,
	unsigned int *found_index, int direction_flag,
	int (*compare_function)(void *, const void *, const void *, size_t)));
COMPAT_FN_DECL(int  STR_ARRAY_delete,
	(unsigned int *, void **, const void *, size_t,
	unsigned int *, int (*)(void *, const void *, const void *, size_t)));
COMPAT_FN_DECL(int  STR_ARRAY_find,
	(unsigned int data_count, const void *data_list,
	const void *key_data, size_t data_length, unsigned int *found_index,
	int (*compare_function)(void *, const void *, const void *, size_t)));
COMPAT_FN_DECL(void STR_ARRAY_reverse,
	(unsigned int, void *, size_t));
COMPAT_FN_DECL(int  STR_ARRAY_search,
	(unsigned int *, void **, const void *, size_t,
	unsigned int *, int (*)(void *, const void *, const void *, size_t),
	int (*)(unsigned int *, void **, const void *, size_t, unsigned int)));
COMPAT_FN_DECL(void STR_ARRAY_qsort,
	(void *, unsigned int, void *, size_t,
	int (*)(void *, const void *, const void *, size_t)));
COMPAT_FN_DECL(void STR_ARRAY_uniq,
	(void *, unsigned int *, void **, size_t,
	int (*)(void *, const void *, const void *, size_t)));

COMPAT_FN_DECL(int  MEM_LIST_delta,
	(void *control_ptr,
	unsigned int in_count_1, void **in_list_1,
	unsigned int in_count_2, void **in_list_2,
	unsigned int *uniq_count_1, unsigned int **uniq_list_1,
	unsigned int *uniq_count_2, unsigned int **uniq_list_2,
	unsigned int *diff_count, unsigned int **diff_list,
	unsigned int *same_count, unsigned int **same_list, size_t data_length,
	int (*compare_function)(void *, const void *, const void *, size_t)));
COMPAT_FN_DECL(int  MEM_LIST_search_delta,
	(void *control_ptr,
	unsigned int in_count_1, void **in_list_1,
	unsigned int in_count_2, void **in_list_2,
	unsigned int *uniq_count_1, unsigned int **uniq_list_1,
	unsigned int *uniq_count_2, unsigned int **uniq_list_2,
	unsigned int *diff_count_1, unsigned int **diff_list_1,
	unsigned int *diff_count_2, unsigned int **diff_list_2,
	unsigned int *same_count_1, unsigned int **same_list_1,
	unsigned int *same_count_2, unsigned int **same_list_2,
	size_t data_length,
	int (*compare_func_1)(void *, const void *, const void *, size_t),
	int (*compare_func_2)(void *, const void *, const void *, size_t)));
COMPAT_FN_DECL(int  MEM_memcmp,
	(void *, const void *, const void *, size_t));
COMPAT_FN_DECL(int  MEM_memicmp,
	(void *, const void *, const void *, size_t));
COMPAT_FN_DECL(int  STR_strcmp,
	(void *, const char *, const char *, size_t));
COMPAT_FN_DECL(int  STR_stricmp,
	(void *, const char *, const char *, size_t));
COMPAT_FN_DECL(int  STR_strncmp,
	(void *, const char *, const char *, size_t));
COMPAT_FN_DECL(int  STR_strnicmp,
	(void *, const char *, const char *, size_t));
COMPAT_FN_DECL(int  STR_LIST_bsearch,
	(void *control_ptr, unsigned int data_count,
	void **data_list, const void *key_data, size_t data_length,
	unsigned int *found_index, int direction_flag,
	int (*compare_function)(void *, const void *, const void *, size_t)));
COMPAT_FN_DECL(int  STR_LIST_delete,
	(unsigned int *, void ***, const void *, size_t,
	unsigned int *, int (*)(void *, const void *, const void *, size_t)));
COMPAT_FN_DECL(int  STR_LIST_find,
	(unsigned int data_count, void **data_list,
	const void *key_data, size_t data_length, unsigned int *found_index,
	int (*compare_function)(void *, const void *, const void *, size_t)));
COMPAT_FN_DECL(void STR_LIST_qsort,
	(void *control_ptr, unsigned int data_count,
	void **data_list, size_t data_length,
	int (*compare_function)(void *, const void *, const void *, size_t)));
COMPAT_FN_DECL(void STR_LIST_reverse,
	(unsigned int data_count, void **data_list));
COMPAT_FN_DECL(int  STR_LIST_search,
	(unsigned int *data_count, void ***data_list,
	const void *key_data, size_t data_length, unsigned int *found_index,
	int (*compare_function)(void *, const void *, const void *, size_t),
	int (*insert_function)(unsigned int *, void ***, const void *, size_t,
	unsigned int)));
COMPAT_FN_DECL(void STR_LIST_uniq,
	(void *control_ptr, unsigned int *data_count,
	void ***data_list, size_t data_length,
	int (*compare_function)(void *, const void *, const void *, size_t)));
COMPAT_FN_DECL(int  memlapp,
	(unsigned int *, void ***, const void *, size_t));
COMPAT_FN_DECL(int  memldel,
	(unsigned int *data_count, void ***data_list,
	unsigned int first_element, unsigned int element_count));
COMPAT_FN_DECL(int  memlins,
	(unsigned int *data_count, void ***data_list,
	const void *in_data, size_t data_length, unsigned int insert_position));
COMPAT_FN_DECL(int  meml_add,
	(unsigned int from_data_count, void **from_data_list,
	size_t data_length, unsigned int *to_data_count, void ***to_data_list));
COMPAT_FN_DECL(int  meml_append,
	(unsigned int *, void ***, const void *, size_t));
COMPAT_FN_DECL(int  meml_allocate,
	(unsigned int *, void ***, size_t, unsigned int));
COMPAT_FN_DECL(int  meml_copy,
	(unsigned int in_data_count, void **in_data_list,
	size_t data_length, unsigned int *out_data_count, void ***out_data_list));
COMPAT_FN_DECL(int  meml_delta,
	(unsigned int string_count_1, void **string_list_1,
	unsigned int string_count_2, void **string_list_2,
	unsigned int *uniq_count_1, unsigned int **uniq_list_1,
	unsigned int *uniq_count_2, unsigned int **uniq_list_2,
	unsigned int *diff_count, unsigned int **diff_list,
	unsigned int *same_count, unsigned int **same_list, size_t data_length));
COMPAT_FN_DECL(int  memli_delta,
	(unsigned int string_count_1, void **string_list_1,
	unsigned int string_count_2, void **string_list_2,
	unsigned int *uniq_count_1, unsigned int **uniq_list_1,
	unsigned int *uniq_count_2, unsigned int **uniq_list_2,
	unsigned int *diff_count, unsigned int **diff_list,
	unsigned int *same_count, unsigned int **same_list, size_t data_length));
COMPAT_FN_DECL(int  meml_insert,
	(unsigned int *data_count, void ***data_list,
	const void *in_data, size_t data_length, unsigned int insert_position));
COMPAT_FN_DECL(int  meml_remove,
	(unsigned int *data_count, void ***data_list,
	unsigned int first_element, unsigned int element_count));
COMPAT_FN_DECL(int  meml_remove_all,
	(unsigned int *data_count, void ***data_list));
COMPAT_FN_DECL(void meml_reverse,
	(unsigned int data_count, void **data_list));
COMPAT_FN_DECL(int  meml_search_delta,
	(unsigned int in_count_1, void **in_list_1,
	unsigned int in_count_2, void **in_list_2,
	unsigned int *uniq_count_1, unsigned int **uniq_list_1,
	unsigned int *uniq_count_2, unsigned int **uniq_list_2,
	unsigned int *same_count_1, unsigned int **same_list_1,
	unsigned int *same_count_2, unsigned int **same_list_2,
	size_t data_length));
COMPAT_FN_DECL(int  memli_search_delta,
	(unsigned int in_count_1, void **in_list_1,
	unsigned int in_count_2, void **in_list_2,
	unsigned int *uniq_count_1, unsigned int **uniq_list_1,
	unsigned int *uniq_count_2, unsigned int **uniq_list_2,
	unsigned int *same_count_1, unsigned int **same_list_1,
	unsigned int *same_count_2, unsigned int **same_list_2,
	size_t data_length));
COMPAT_FN_DECL(int  strlapp,
	(unsigned int *, char ***, const char *));
COMPAT_FN_DECL(int  strldel,
	(unsigned int *string_count, char ***string_list,
	unsigned int first_element, unsigned int element_count));
COMPAT_FN_DECL(int  strlins,
	(unsigned int *string_count, char ***string_list,
	const char *in_string, unsigned int insert_position));
COMPAT_FN_DECL(int  strlnapp,
	(unsigned int *string_count, char ***string_list,
	const char *in_string, size_t string_length));
COMPAT_FN_DECL(int  strlnins,
	(unsigned int *string_count, char ***string_list,
	const char *in_string, size_t string_length, unsigned int insert_position));
COMPAT_FN_DECL(int  strl_copy,
	(unsigned int in_string_count, char **in_string_list,
	unsigned int *out_string_count, char ***out_string_list));
COMPAT_FN_DECL(int  strl_add,
	(unsigned int, char **, unsigned int *, char ***));
COMPAT_FN_DECL(int  strl_append,
	(unsigned int *, char ***, const char *));
COMPAT_FN_DECL(int  strl_delete,
	(unsigned int *, char ***, const char *, unsigned int *));
COMPAT_FN_DECL(int  strl_delta,
	(unsigned int string_count_1, char **string_list_1,
	unsigned int string_count_2, char **string_list_2,
	unsigned int *uniq_count_1, unsigned int **uniq_list_1,
	unsigned int *uniq_count_2, unsigned int **uniq_list_2,
	unsigned int *diff_count, 	unsigned int **diff_list,
	unsigned int *same_count, unsigned int **same_list));
COMPAT_FN_DECL(int  strl_find,
	(unsigned int string_count, char **string_list,
	const char *key_string, unsigned int *found_index));
COMPAT_FN_DECL(int  strl_insert,
	(unsigned int *string_count, char ***string_list,
	const char *in_string, unsigned int insert_position));
COMPAT_FN_DECL(int  strl_remove,
	(unsigned int *string_count, char ***string_list,
	unsigned int first_element, unsigned int element_count));
COMPAT_FN_DECL(int  strl_remove_all,
	(unsigned int *string_count, char ***string_list));
COMPAT_FN_DECL(void strl_reverse,
	(unsigned int string_count, char **string_list));
COMPAT_FN_DECL(int  strl_search,
	(unsigned int *string_count, char ***string_list,
	const char *key_string, unsigned int *found_index));
COMPAT_FN_DECL(int  strl_search_delta,
	(unsigned int in_count_1, char **in_list_1,
	unsigned int in_count_2, char **in_list_2,
	unsigned int *uniq_count_1, unsigned int **uniq_list_1,
	unsigned int *uniq_count_2, unsigned int **uniq_list_2,
	unsigned int *same_count_1, unsigned int **same_list_1,
	unsigned int *same_count_2, unsigned int **same_list_2));
COMPAT_FN_DECL(void strl_sort,
	(unsigned int string_count, char **string_list));
COMPAT_FN_DECL(void strl_uniq,
	(unsigned int *string_count, char ***string_list));
COMPAT_FN_DECL(int  strli_delete,
	(unsigned int *string_count, char ***string_list,
	const char *key_string, unsigned int *found_index));
COMPAT_FN_DECL(int  strli_delta,
	(unsigned int string_count_1, char **string_list_1,
	unsigned int string_count_2, char **string_list_2,
	unsigned int *uniq_count_1, unsigned int **uniq_list_1,
	unsigned int *uniq_count_2, unsigned int **uniq_list_2,
	unsigned int *diff_count, unsigned int **diff_list,
	unsigned int *same_count, unsigned int **same_list));
COMPAT_FN_DECL(int  strli_find,
	(unsigned int string_count, char **string_list,
	const char *key_string, unsigned int *found_index));
COMPAT_FN_DECL(int  strli_search,
	(unsigned int *string_count, char ***string_list,
	const char *key_string, unsigned int *found_index));
COMPAT_FN_DECL(int  strli_search_delta,
	(unsigned int in_count_1, char **in_list_1,
	unsigned int in_count_2, char **in_list_2,
	unsigned int *uniq_count_1, unsigned int **uniq_list_1,
	unsigned int *uniq_count_2, unsigned int **uniq_list_2,
	unsigned int *same_count_1, unsigned int **same_list_1,
	unsigned int *same_count_2, unsigned int **same_list_2));
COMPAT_FN_DECL(void strli_sort,
	(unsigned int string_count, char **string_list));
COMPAT_FN_DECL(void strli_uniq,
	(unsigned int *string_count, char ***string_list));
COMPAT_FN_DECL(int  strln_add,
	(unsigned int from_string_count, char **from_string_list,
	unsigned int *to_string_count, char ***to_string_list,
	size_t string_length));
COMPAT_FN_DECL(int  strln_append,
	(unsigned int *string_count, char ***string_list,
	const char *in_string, size_t string_length));
COMPAT_FN_DECL(int  strln_delete,
	(unsigned int *string_count, char ***string_list,
	const char *key_string, size_t string_length, unsigned int *found_index));
COMPAT_FN_DECL(int  strln_delta,
	(unsigned int string_count_1, char **string_list_1,
	unsigned int string_count_2, char **string_list_2,
	unsigned int *uniq_count_1, unsigned int **uniq_list_1,
	unsigned int *uniq_count_2, unsigned int **uniq_list_2,
	unsigned int *diff_count, unsigned int **diff_list,
	unsigned int *same_count, unsigned int **same_list, size_t string_length));
COMPAT_FN_DECL(int  strln_find,
	(unsigned int string_count, char **string_list,
	const char *key_string, size_t string_length, unsigned int *found_index));
COMPAT_FN_DECL(int  strln_insert,
	(unsigned int *string_count, char ***string_list,
	const char *in_string, size_t string_length, unsigned int insert_position));
COMPAT_FN_DECL(int  strln_search,
	(unsigned int *string_count, char ***string_list,
	const char *key_string, size_t string_length, unsigned int *found_index));
COMPAT_FN_DECL(int  strln_search_delta,
	(unsigned int in_count_1, char **in_list_1,
	unsigned int in_count_2, char **in_list_2,
	unsigned int *uniq_count_1, unsigned int **uniq_list_1,
	unsigned int *uniq_count_2, unsigned int **uniq_list_2,
	unsigned int *same_count_1, unsigned int **same_list_1,
	unsigned int *same_count_2, unsigned int **same_list_2,
	size_t string_length));
COMPAT_FN_DECL(void strln_sort,
	(unsigned int string_count, char **string_list,
	size_t string_length));
COMPAT_FN_DECL(void strln_uniq,
	(unsigned int *string_count, char ***string_list,
	size_t string_length));
COMPAT_FN_DECL(int  strlni_delete,
	(unsigned int *string_count, char ***string_list,
	const char *key_string, size_t string_length, unsigned int *found_index));
COMPAT_FN_DECL(int  strlni_delta,
	(unsigned int string_count_1, char **string_list_1,
	unsigned int string_count_2, char **string_list_2,
	unsigned int *uniq_count_1, unsigned int **uniq_list_1,
	unsigned int *uniq_count_2, unsigned int **uniq_list_2,
	unsigned int *diff_count, unsigned int **diff_list,
	unsigned int *same_count, unsigned int **same_list, size_t string_length));
COMPAT_FN_DECL(int  strlni_find,
	(unsigned int string_count, char **string_list,
	const char *key_string, size_t string_length, unsigned int *found_index));
COMPAT_FN_DECL(int  strlni_search,
	(unsigned int *string_count, char ***string_list,
	const char *key_string, size_t string_length, unsigned int *found_index));
COMPAT_FN_DECL(int  strlni_search_delta,
	(unsigned int in_count_1, char **in_list_1,
	unsigned int in_count_2, char **in_list_2,
	unsigned int *uniq_count_1, unsigned int **uniq_list_1,
	unsigned int *uniq_count_2, unsigned int **uniq_list_2,
	unsigned int *same_count_1, unsigned int **same_list_1,
	unsigned int *same_count_2, unsigned int **same_list_2,
	size_t string_length));
COMPAT_FN_DECL(void strlni_sort,
	(unsigned int string_count, char **string_list,
	size_t string_length));
COMPAT_FN_DECL(void strlni_uniq,
	(unsigned int *string_count, char ***string_list,
	size_t string_length));

# ifndef NO_STDARGS
COMPAT_FN_DECL(int memlv_append,
	(unsigned int *, void ***, size_t, ...));
COMPAT_FN_DECL(int strlnv_append,
	(unsigned int *string_count, char ***string_list,
	size_t string_length, ...));
COMPAT_FN_DECL(int strlv_append,
	(unsigned int *string_count, char ***string_list, ...));
# else
COMPAT_FN_DECL(int memlv_append,
	(unsigned int *, void ***, size_t, va_alist));
COMPAT_FN_DECL(int strlnv_append,
	(unsigned int *string_count, char ***string_list,
	size_t string_length, va_alist));
COMPAT_FN_DECL(int strlv_append,
	(unsigned int *string_count, char ***string_list, va_alist));
# endif /* # ifndef NO_STDARGS */

# ifndef NO_STDARGS
COMPAT_FN_DECL(char *strnvcat,
	(char *target_string, size_t string_length, ...));
COMPAT_FN_DECL(char *strnv_padded_cat,
	(char *target_string, size_t string_length,
	const char *left_padding, const char *right_padding, ...));
COMPAT_FN_DECL(char *strnvacat,
	(char **target_string, size_t string_length, ...));
COMPAT_FN_DECL(char *strnva_padded_cat,
	(char **target_string, size_t string_length,
	const char *left_padding, const char *right_padding, ...));
COMPAT_FN_DECL(char *strnvcpy,
	(char *target_string, size_t string_length, ...));
COMPAT_FN_DECL(char *strnv_padded_cpy,
	(char *target_string, size_t string_length,
	const char *left_padding, const char *right_padding, ...));
COMPAT_FN_DECL(char *strnvacpy,
	(char **target_string, size_t string_length, ...));
COMPAT_FN_DECL(char *strnva_padded_cpy,
	(char **target_string, size_t string_length,
	const char *left_padding, const char *right_padding, ...));
COMPAT_FN_DECL(char *strvcat,
	(char *target_string, ...));
COMPAT_FN_DECL(char *strv_padded_cat,
	(char *target_string, const char *left_padding,
	const char *right_padding, ...));
COMPAT_FN_DECL(char *strvacat,
	(char **target_string, ...));
COMPAT_FN_DECL(char *strva_padded_cat,
	(char **target_string, const char *left_padding,
	const char *right_padding, ...));
COMPAT_FN_DECL(char *strvcpy,
	(char *target_string, ...));
COMPAT_FN_DECL(char *strv_padded_cpy,
	(char *target_string, const char *left_padding,
	const char *right_padding, ...));
COMPAT_FN_DECL(char *strvacpy,
	(char **target_string, ...));
COMPAT_FN_DECL(char *strva_padded_cpy,
	(char **target_string, const char *left_padding,
	const char *right_padding, ...));
# else
COMPAT_FN_DECL(char *strnvcat,
	(char *target_string, size_t string_length, va_alist));
COMPAT_FN_DECL(char *strnv_padded_cat,
	(char *target_string, size_t string_length,
	const char *left_padding, const char *right_padding, va_alist));
COMPAT_FN_DECL(char *strnvacat,
	(char **target_string, size_t string_length, va_alist));
COMPAT_FN_DECL(char *strnva_padded_cat,
	(char **target_string, size_t string_length,
	const char *left_padding, const char *right_padding, va_alist));
COMPAT_FN_DECL(char *strnvcpy,
	(char *target_string, size_t string_length, va_alist));
COMPAT_FN_DECL(char *strnv_padded_cpy,
	(char *target_string, size_t string_length,
	const char *left_padding, const char *right_padding, va_alist));
COMPAT_FN_DECL(char *strnvacpy,
	(char **target_string, size_t string_length, va_alist));
COMPAT_FN_DECL(char *strnva_padded_cpy,
	(char **target_string, size_t string_length,
	const char *left_padding, const char *right_padding, va_alist));
COMPAT_FN_DECL(char *strvcat,
	(char *target_string, va_alist));
COMPAT_FN_DECL(char *strv_padded_cat,
	(char *target_string, const char *left_padding,
	const char *right_padding, va_alist));
COMPAT_FN_DECL(char *strvacat,
	(char **target_string, va_alist));
COMPAT_FN_DECL(char *strva_padded_cat,
	(char **target_string, const char *left_padding,
	const char *right_padding, va_alist));
COMPAT_FN_DECL(char *strvcpy,
	(char *target_string, va_alist));
COMPAT_FN_DECL(char *strv_padded_cpy,
	(char *target_string, const char *left_padding,
	const char *right_padding, va_alist));
COMPAT_FN_DECL(char *strvacpy,
	(char **target_string, va_alist));
COMPAT_FN_DECL(char *strva_padded_cpy,
	(char **target_string, const char *left_padding,
	const char *right_padding, va_alist));
# endif /* # ifndef NO_STDARGS */

	/* In module 'stalnum.c'				*/
COMPAT_FN_DECL(char         *str_alnum,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(char         *strr_alnum,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(int           idx_alnum,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(int           idxr_alnum,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(unsigned int  cnt_alnum,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(char         *cvt_alnum,
	(char *in_string, int conversion_char, int sense_flag));
	/* In module 'stalpha.c'				*/
COMPAT_FN_DECL(char         *str_alpha,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(char         *strr_alpha,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(int           idx_alpha,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(int           idxr_alpha,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(unsigned int  cnt_alpha,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(char         *cvt_alpha,
	(char *in_string, int conversion_char, int sense_flag));
	/* In module 'stascii.c'				*/
COMPAT_FN_DECL(char         *str_ascii,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(char         *strr_ascii,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(int           idx_ascii,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(int           idxr_ascii,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(unsigned int  cnt_ascii,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(char         *cvt_ascii,
	(char *in_string, int conversion_char, int sense_flag));
	/* In module 'stbdigit.c'				*/
COMPAT_FN_DECL(char         *str_bdigit,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(char         *strr_bdigit,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(int           idx_bdigit,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(int           idxr_bdigit,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(unsigned int  cnt_bdigit,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(char         *cvt_bdigit,
	(char *in_string, int conversion_char, int sense_flag));
	/* In module 'stcntrl.c'				*/
COMPAT_FN_DECL(char         *str_cntrl,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(char         *strr_cntrl,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(int           idx_cntrl,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(int           idxr_cntrl,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(unsigned int  cnt_cntrl,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(char         *cvt_cntrl,
	(char *in_string, int conversion_char, int sense_flag));
	/* In module 'stcsym.c'					*/
COMPAT_FN_DECL(char         *str_csym,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(char         *strr_csym,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(int           idx_csym,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(int           idxr_csym,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(unsigned int  cnt_csym,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(char         *cvt_csym,
	(char *in_string, int conversion_char, int sense_flag));
	/* In module 'stcsymf.c'				*/
COMPAT_FN_DECL(char         *str_csymf,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(char         *strr_csymf,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(int           idx_csymf,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(int           idxr_csymf,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(unsigned int  cnt_csymf,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(char         *cvt_csymf,
	(char *in_string, int conversion_char, int sense_flag));
	/* In module 'stdigit.c'				*/
COMPAT_FN_DECL(char         *str_digit,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(char         *strr_digit,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(int           idx_digit,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(int           idxr_digit,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(unsigned int  cnt_digit,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(char         *cvt_digit,
	(char *in_string, int conversion_char, int sense_flag));
	/* In module 'stgraph.c'				*/
COMPAT_FN_DECL(char         *str_graph,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(char         *strr_graph,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(int           idx_graph,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(int           idxr_graph,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(unsigned int  cnt_graph,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(char         *cvt_graph,
	(char *in_string, int conversion_char, int sense_flag));
	/* In module 'stlower.c'				*/
COMPAT_FN_DECL(char         *str_lower,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(char         *strr_lower,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(int           idx_lower,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(int           idxr_lower,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(unsigned int  cnt_lower,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(char         *cvt_lower,
	(char *in_string, int conversion_char, int sense_flag));
	/* In module 'stodigit.c'				*/
COMPAT_FN_DECL(char         *str_odigit,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(char         *strr_odigit,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(int           idx_odigit,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(int           idxr_odigit,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(unsigned int  cnt_odigit,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(char         *cvt_odigit,
	(char *in_string, int conversion_char, int sense_flag));
	/* In module 'stprint.c'				*/
COMPAT_FN_DECL(char         *str_print,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(char         *strr_print,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(int           idx_print,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(int           idxr_print,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(unsigned int  cnt_print,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(char         *cvt_print,
	(char *in_string, int conversion_char, int sense_flag));
	/* In module 'stpunct.c'				*/
COMPAT_FN_DECL(char         *str_punct,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(char         *strr_punct,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(int           idx_punct,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(int           idxr_punct,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(unsigned int  cnt_punct,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(char         *cvt_punct,
	(char *in_string, int conversion_char, int sense_flag));
	/* In module 'stspace.c'				*/
COMPAT_FN_DECL(char         *str_space,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(char         *strr_space,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(int           idx_space,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(int           idxr_space,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(unsigned int  cnt_space,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(char         *cvt_space,
	(char *in_string, int conversion_char, int sense_flag));
	/* In module 'stupper.c'				*/
COMPAT_FN_DECL(char         *str_upper,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(char         *strr_upper,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(int           idx_upper,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(int           idxr_upper,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(unsigned int  cnt_upper,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(char         *cvt_upper,
	(char *in_string, int conversion_char, int sense_flag));
	/* In module 'stxdigit.c'				*/
COMPAT_FN_DECL(char         *str_xdigit,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(char         *strr_xdigit,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(int           idx_xdigit,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(int           idxr_xdigit,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(unsigned int  cnt_xdigit,
	(const char *in_string, int sense_flag));
COMPAT_FN_DECL(char         *cvt_xdigit,
	(char *in_string, int conversion_char, int sense_flag));

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
typedef struct {
	unsigned long  value;
	char          *name;
	unsigned long  basis;
} STRFUNCS_VALUE_NAME;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
COMPAT_FN_DECL(char *get_ulong_text,
	(unsigned long in_ulong, char *out_string));
COMPAT_FN_DECL(char *get_ulong_text_basic,
	(unsigned long in_ulong, unsigned int name_count,
	const STRFUNCS_VALUE_NAME *name_list, char *out_string));
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable:4820)
#endif /* #ifdef _MSC_VER */

typedef struct {
	double  value;
	char   *name;
} STRFUNCS_D_VALUE_NAME;

#ifdef _MSC_VER
# pragma warning(pop)
#endif /* #ifdef _MSC_VER */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
#define STRFUNCS_D_MAX_DECIMAL_PLACES	127
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
COMPAT_FN_DECL(char *get_double_text,
	(double in_double, unsigned int decimal_places,
	char *out_string));
COMPAT_FN_DECL(char *get_double_text_basic,
	(double in_double, unsigned int decimal_places,
	unsigned int name_count, const STRFUNCS_D_VALUE_NAME *name_list,
	unsigned int ulong_name_count, const STRFUNCS_VALUE_NAME *ulong_name_list,
	char *out_string));
COMPAT_FN_DECL(char *drop_double_text_zeroes,
	(char *out_string));
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
COMPAT_FN_DECL(char *cardinal,
	(unsigned long number, char *text));
COMPAT_FN_DECL(char *cardinal_double,
	(double number, unsigned int decimal_places, char *text));
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
COMPAT_FN_DECL(char *ordinal,
	(unsigned int number, char *text));
COMPAT_FN_DECL(char *ordinal_full,
	(unsigned long number, char *text));
COMPAT_FN_DECL(char *ordinal_double_full,
	(double number, unsigned int decimal_points,
	char *text));
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
COMPAT_FN_DECL(unsigned int  get_group_length,
	(const char *in_string,
	const char *decimal_point, unsigned int group_size,
	const char *group_separator));
COMPAT_FN_DECL(char         *insert_groups,
	(const char *in_string,
	const char *decimal_point, unsigned int group_size,
	const char *group_separator, char *out_string));
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
COMPAT_FN_DECL(int            asctobcd,
	(unsigned int in_ascii_length, const char *in_ascii_string,
	int start_at_nybble_flag, int nybble_pad_flag,
	unsigned char *out_bcd_string, unsigned int *out_nybble_count));
COMPAT_FN_DECL(unsigned char *ascii_to_COMP_3,
	(int sign, const char *in_ascii_ptr,
	unsigned char *out_bcd_ptr, unsigned int *out_bcd_length));
COMPAT_FN_DECL(unsigned char *ascii_n_to_COMP_3,
	(int sign, const char *in_ascii_ptr,
	unsigned int in_ascii_length, unsigned char *out_bcd_ptr,
	unsigned int *out_bcd_length));
COMPAT_FN_DECL(char          *bcdtoasc,
	(const char *in_bcd_ptr, char *out_ascii_ptr));
COMPAT_FN_DECL(char          *bcdtoasc_basic,
	(unsigned int in_bcd_length,
	const char *in_bcd_ptr, char *out_ascii_ptr));
COMPAT_FN_DECL(char          *bcdtoasc_basic_mem,
	(unsigned int in_bcd_length,
	const char *in_bcd_ptr, int start_at_nybble_flag,
	unsigned int *out_ascii_length, char *out_ascii_ptr, int *bcd_sign_value));
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
COMPAT_FN_DECL(char *zerotrim,
	(char *text));
COMPAT_FN_DECL(char *zerotrim_basic,
	(const char *in_text, char *out_text,
	int keep_last_zero_flag));
COMPAT_FN_DECL(char *zerotrim_basic_mem,
	(unsigned int in_length, const char *in_text,
	unsigned int *out_length, char *out_text, int keep_last_zero_flag));
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Flags for use in converting between C/C++ strings with escape	*/
	/*	characters and memory buffers . . .											*/
	/*	*****************************************************************	*/
#define STR_CSTR2MEM_NO_TRIGRAPHS	1
#define STR_MEM2CSTR_NO_TRIGRAPHS	STR_CSTR2MEM_NO_TRIGRAPHS
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		C/C++ string to memory buffer function prototypes . . .			*/
	/*	*****************************************************************	*/
COMPAT_FN_DECL(char         *cstr2mem,
	(const char *in_string, int flags,
	unsigned int *out_length, char *out_string));
COMPAT_FN_DECL(char         *cstr2mem_alloc,
	(const char *in_string, int flags,
	unsigned int *out_length));
COMPAT_FN_DECL(unsigned int  cstr2mem_length,
	(const char *in_string, int flags));
COMPAT_FN_DECL(char         *cstr2mem_basic,
	(unsigned int in_length, const char *in_string,
	int flags, unsigned int *out_length, char *out_string));
COMPAT_FN_DECL(char         *cstr2mem_basic_alloc,
	(unsigned int in_length,
	const char *in_string, int flags, unsigned int *out_length));
COMPAT_FN_DECL(unsigned int  cstr2mem_basic_length,
	(unsigned int in_length,
	const char *in_string, int flags));
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Memory buffer to C/C++ string function prototypes . . .			*/
	/*	*****************************************************************	*/
COMPAT_FN_DECL(char         *mem2cstr,
	(unsigned int in_length, const char *in_string,
	int flags, char *out_string));
COMPAT_FN_DECL(char         *mem2cstr_alloc,
	(unsigned int in_length, const char *in_string,
	int flags));
COMPAT_FN_DECL(unsigned int  mem2cstr_length,
	(unsigned int in_length, const char *in_string,
	int flags));
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Function prototypes for determining number strings . . .			*/
	/*	*****************************************************************	*/
COMPAT_FN_DECL(int getnumstr,
	(const char *in_string, const char *decimal_point,
	unsigned int *new_start_index, unsigned int *new_end_index));
COMPAT_FN_DECL(int getnumstr_basic,
	(const char *in_string, unsigned int start_index,
	unsigned int end_index, const char *decimal_point,
	unsigned int *new_start_index, unsigned int *new_end_index));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Allocation error message function prototypes . . .
		*****************************************************************	*/
#ifdef __GNUC__
COMPAT_FN_DECL(char *STR_AllocMsgItem, (unsigned int size, char *buffer,
	const char *in_format, ...) __attribute__ ((format (printf, 3, 4))));
COMPAT_FN_DECL(char *STR_AllocMsgList, (unsigned int element_count,
	unsigned int element_size, char *buffer, const char *in_format, ...)
	__attribute__ ((format (printf, 4, 5))));
COMPAT_FN_DECL(char *STR_AllocMsgPtrList, (unsigned int element_count,
	unsigned int total_size, char *buffer, const char *in_format, ...)
	__attribute__ ((format (printf, 4, 5))));
#else
# ifndef NO_STDARGS
COMPAT_FN_DECL(char *STR_AllocMsgItem, (unsigned int size, char *buffer,
	const char *in_format, ...));
COMPAT_FN_DECL(char *STR_AllocMsgList, (unsigned int element_count,
	unsigned int element_size, char *buffer, const char *in_format, ...));
COMPAT_FN_DECL(char *STR_AllocMsgPtrList, (unsigned int element_count,
	unsigned int total_size, char *buffer, const char *in_format, ...));
# else
COMPAT_FN_DECL(char *STR_AllocMsgItem, (unsigned int size, char *buffer,
	const char *in_format, va_alist));
COMPAT_FN_DECL(char *STR_AllocMsgList, (unsigned int element_count,
	unsigned int element_size, char *buffer, const char *in_format, va_alist));
COMPAT_FN_DECL(char *STR_AllocMsgPtrList, (unsigned int element_count,
	unsigned int total_size, char *buffer, const char *in_format, va_alist));
# endif /* # ifndef NO_STDARGS */
#endif /* #ifdef __GNUC__ */
COMPAT_FN_DECL(char *STR_AllocMsgItemVA, (unsigned int size, char *buffer,
	const char *in_format, va_list arg_list));
COMPAT_FN_DECL(char *STR_AllocMsgListVA, (unsigned int element_count,
	unsigned int element_size, char *buffer, const char *in_format,
	va_list arg_list));
COMPAT_FN_DECL(char *STR_AllocMsgPtrListVA, (unsigned int element_count,
	unsigned int total_size, char *buffer, const char *in_format,
	va_list arg_list));
	/*	*****************************************************************	*/

/*	***********************************************************************	*/
COMPAT_FN_DECL(char *STR_strrev, (char *string));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
COMPAT_FN_DECL(unsigned int STR_LIST_GetElementMinLength,
	(unsigned int string_count, char **string_list, unsigned int *max_index));
COMPAT_FN_DECL(unsigned int STR_LIST_GetElementMaxLength,
	(unsigned int string_count, char **string_list, unsigned int *max_index));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
COMPAT_FN_DECL(char *STR_Join,
	(char *out_string, const char *first_string, const char *middle_string,
	const char *last_string, ...));
COMPAT_FN_DECL(char *STR_JoinVA,
	(char *out_string, const char *first_string, const char *middle_string,
	const char *last_string, va_list arg_list));
COMPAT_FN_DECL(char *STR_JoinN,
	(char *out_string, unsigned int length, const char *first_string,
	const char *middle_string, const char *last_string, ...));
COMPAT_FN_DECL(char *STR_JoinNVA,
	(char *out_string, unsigned int length, const char *first_string,
	const char *middle_string, const char *last_string, va_list arg_list));

COMPAT_FN_DECL(char *STR_JoinAlloc,
	(char **out_string, const char *first_string, const char *middle_string,
	const char *last_string, ...));
COMPAT_FN_DECL(char *STR_JoinAllocVA,
	(char **out_string, const char *first_string, const char *middle_string,
	const char *last_string, va_list arg_list));
COMPAT_FN_DECL(char *STR_JoinNAlloc,
	(char **out_string, unsigned int length, const char *first_string,
	const char *middle_string, const char *last_string, ...));
COMPAT_FN_DECL(char *STR_JoinNAllocVA,
	(char **out_string, unsigned int length, const char *first_string,
	const char *middle_string, const char *last_string, va_list arg_list));

COMPAT_FN_DECL(unsigned int STR_JoinLength,
	(char *out_string, const char *first_string, const char *middle_string,
	const char *last_string, ...));
COMPAT_FN_DECL(unsigned int STR_JoinLengthVA,
	(char *out_string, const char *first_string, const char *middle_string,
	const char *last_string, va_list arg_list));
COMPAT_FN_DECL(unsigned int STR_JoinNLength,
	(char *out_string, unsigned int length, const char *first_string,
	const char *middle_string, const char *last_string, ...));
COMPAT_FN_DECL(unsigned int STR_JoinNLengthVA,
	(char *out_string, unsigned int length, const char *first_string,
	const char *middle_string, const char *last_string, va_list arg_list));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
COMPAT_FN_DECL(char          *ascii_to_ebcdic,
	(const char *in_ascii_ptr,
	size_t in_ascii_length, char *out_ebcdic_ptr, const char *missing_value));
COMPAT_FN_DECL(char          *ebcdic_to_ascii,
	(const char *in_ebcdic_ptr,
	size_t in_ebcdic_length, char *out_ascii_ptr, const char *missing_value));
COMPAT_FN_DECL(const char *ccmntend,
	(const char *string_ptr, int c_plus_plus_flag));
COMPAT_FN_DECL(int     charcnt,
	(int look_for_char, const char *search_string));
COMPAT_FN_DECL(int     charicnt,
	(int look_for_char, const char *search_string));
COMPAT_FN_DECL(int     charspan,
	(const char *text, int *low, int *high));
COMPAT_FN_DECL(char   *chrcat,
	(char *, int));
COMPAT_FN_DECL(size_t  chrcnt,
	(const char *search_string, int target_char));
COMPAT_FN_DECL(char   *chrcpy,
	(char *to_ptr, int in_char));
COMPAT_FN_DECL(size_t  chricnt,
	(const char *search_string, int target_char));
COMPAT_FN_DECL(int     chriindx,
	(int look_for_char, const char *search_string));
COMPAT_FN_DECL(int     chrindx,
	(int look_for_char, const char *search_string));
COMPAT_FN_DECL(char   *chrinstr,
	(const char *in_string, const char *in_char_list));
COMPAT_FN_DECL(size_t  chrncnt,
	(const char *, int, size_t));
COMPAT_FN_DECL(size_t  chrnicnt,
	(const char *, int, size_t));
COMPAT_FN_DECL(char   *cnormal,
	(char *));
COMPAT_FN_DECL(char   *cstring,
	(const char *in_string, char *out_string,
	unsigned int *out_length));
COMPAT_FN_DECL(const char *extract_file_name,
	(const char *in_path));
COMPAT_FN_DECL(int     idxchr,
	(const char *, int));
COMPAT_FN_DECL(int     idxichr,
	(const char *, int));
COMPAT_FN_DECL(int     idxistr,
	(const char *, const char *));
COMPAT_FN_DECL(int     idxistrn,
	(const char *, const char *, size_t));
COMPAT_FN_DECL(int     idxnchr,
	(const char *, int, size_t));
COMPAT_FN_DECL(int     idxnichr,
	(const char *, int, size_t));
COMPAT_FN_DECL(int     idxnistr,
	(const char *, const char *, size_t));
COMPAT_FN_DECL(int     idxnistrn,
	(const char *, const char *, size_t, size_t));
COMPAT_FN_DECL(int     idxnstr,
	(const char *, const char *, size_t));
COMPAT_FN_DECL(int     idxnstrn,
	(const char *, const char *, size_t, size_t));
COMPAT_FN_DECL(int     idxrchr,
	(const char *, int));
COMPAT_FN_DECL(int     idxrichr,
	(const char *, int));
COMPAT_FN_DECL(int     idxristrn,
	(const char *, const char *, size_t));
COMPAT_FN_DECL(int     idxristr,
	(const char *, const char *));
COMPAT_FN_DECL(int     idxrnchr,
	(const char *, int, size_t));
COMPAT_FN_DECL(int     idxrnichr,
	(const char *, int, size_t));
COMPAT_FN_DECL(int     idxrnistr,
	(const char *, const char *, size_t));
COMPAT_FN_DECL(int     idxrnistrn,
	(const char *, const char *, size_t, size_t));
COMPAT_FN_DECL(int     idxrnstr,
	(const char *, const char *, size_t));
COMPAT_FN_DECL(int     idxrnstrn,
	(const char *, const char *, size_t, size_t));
COMPAT_FN_DECL(int     idxrstr,
	(const char *, const char *));
COMPAT_FN_DECL(int     idxrstrn,
	(const char *, const char *, size_t));
COMPAT_FN_DECL(int     idxstr,
	(const char *, const char *));
COMPAT_FN_DECL(int     idxstrn,
	(const char *, const char *, size_t));
COMPAT_FN_DECL(size_t  memcnt,
	(size_t, const void *, size_t, const void *));
COMPAT_FN_DECL(void   *memdup,
	(const void *, size_t));
COMPAT_FN_DECL(int     STRFUNCS_memicmp,
	(const void *, const void *, size_t));
COMPAT_FN_DECL(size_t  memicnt,
	(size_t, const void *, size_t, const void *));
COMPAT_FN_DECL(void   *memimem,
	(size_t, const void *, size_t, const void *));
COMPAT_FN_DECL(void   *memmem,
	(size_t, const void *, size_t, const void *));
COMPAT_FN_DECL(void   *memrimem,
	(size_t, const void *, size_t, const void *));
COMPAT_FN_DECL(void   *memrmem,
	(size_t, const void *, size_t, const void *));
COMPAT_FN_DECL(char   *nstrcat,
	(char *, const char *, size_t));
COMPAT_FN_DECL(char   *nstrcpy,
	(char *, const char *, size_t));
COMPAT_FN_DECL(char   *nstrset,
	(char *, int, size_t));
COMPAT_FN_DECL(char   *qstrend,
	(char *));
COMPAT_FN_DECL(char   *sepwords,
	(char *text));
COMPAT_FN_DECL(int     sepwordl,
	(const char *in_string, unsigned int *string_count,
	char ***string_list));
COMPAT_FN_DECL(int     sepwordx,
	(const char *in_string, const char *separation_list,
	unsigned int *string_count, char ***string_list));
COMPAT_FN_DECL(int     sepwordx_keep,
	(const char *in_string, const char *separation_list,
	unsigned int *string_count, char ***string_list));
COMPAT_FN_DECL(int     sepwordc,
	(const char *in_string, int separation_char,
	unsigned int *string_count, char ***string_list));
COMPAT_FN_DECL(int     sepwordc_keep,
	(const char *in_string, int separation_char,
	unsigned int *string_count, char ***string_list));
COMPAT_FN_DECL(char   *STRFUNCS_strchr,
	(const char *, int));
COMPAT_FN_DECL(size_t  strcnt,
	(const char *, const char *));
COMPAT_FN_DECL(char   *strdele,
	(char *base_string, unsigned int position,
	unsigned int delete_length));
COMPAT_FN_DECL(char   *STRFUNCS_strdup,
	(const char *));
COMPAT_FN_DECL(char   *strescap,
	(char *, const char *, const char *));
COMPAT_FN_DECL(char   *strichr,
	(const char *, int));
COMPAT_FN_DECL(size_t  stricnt,
	(const char *, const char *));
COMPAT_FN_DECL(int     striindx,
	(const char *, const char *));
COMPAT_FN_DECL(int     strindx,
	(const char *, const char *));
COMPAT_FN_DECL(char   *strins,
	(char *, char *));
COMPAT_FN_DECL(char   *strinst,
	(char *base_string, const char *insert_string,
	unsigned int position));
COMPAT_FN_DECL(char   *stristr,
	(const char *, const char *));
COMPAT_FN_DECL(char   *stristrn,
	(const char *, const char *, size_t));
COMPAT_FN_DECL(int     strlwrap,
	(const char *in_string, int *current_col, int max_length,
	int *tab_count, int tab_setting, int strip_flag, char *last_char,
	unsigned int *string_count, char ***string_list));
COMPAT_FN_DECL(char   *strmask,
	(char *, int));
COMPAT_FN_DECL(char   *strnchr,
	(const char *, int, size_t));
COMPAT_FN_DECL(size_t  strncnt,
	(const char *, const char *, size_t));
COMPAT_FN_DECL(char   *strndup,
	(const char *, size_t));
COMPAT_FN_DECL(char   *strnichr,
	(const char *, int, size_t));
COMPAT_FN_DECL(size_t  strnicnt,
	(const char *, const char *, size_t));
COMPAT_FN_DECL(int     strniidx,
	(const char *, const char *, int));
COMPAT_FN_DECL(char   *strninst,
	(char *base_string, const char *insert_string,
	unsigned int position, unsigned int length));
COMPAT_FN_DECL(char   *strnistr,
	(const char *, const char *, size_t));
COMPAT_FN_DECL(char   *strnistrn,
	(const char *, const char *, size_t, size_t));
COMPAT_FN_DECL(char   *strnstr,
	(const char *, const char *, size_t));
COMPAT_FN_DECL(char   *strnrepl,
	(char *base_string, const char *insert_string,
	unsigned int position, unsigned int delete_length,
	unsigned int insert_length));
COMPAT_FN_DECL(char   *STRFUNCS_strnset,
	(char *, int, size_t));
COMPAT_FN_DECL(char   *strnstrn,
	(const char *, const char *, size_t, size_t));
COMPAT_FN_DECL(char   *STRFUNCS_strrchr,
	(const char *, int));
COMPAT_FN_DECL(char   *strrepl,
	(char *base_string, const char *insert_string,
	unsigned int position, unsigned int delete_length));
COMPAT_FN_DECL(char   *strrichr,
	(const char *, int));
COMPAT_FN_DECL(char   *strristr,
	(const char *, const char *));
COMPAT_FN_DECL(char   *strristrn,
	(const char *, const char *, size_t));
COMPAT_FN_DECL(char   *strrnchr,
	(const char *, int, size_t));
COMPAT_FN_DECL(char   *strrnichr,
	(const char *, int, size_t));
COMPAT_FN_DECL(char   *strrnistr,
	(const char *, const char *, size_t));
COMPAT_FN_DECL(char   *strrnistrn,
	(const char *, const char *, size_t, size_t));
COMPAT_FN_DECL(char   *strrnstr,
	(const char *, const char *, size_t));
COMPAT_FN_DECL(char   *strrnstrn,
	(const char *, const char *, size_t, size_t));
COMPAT_FN_DECL(char   *STRFUNCS_strset,
	(char *, int));
COMPAT_FN_DECL(char   *strrstr,
	(const char *, const char *));
COMPAT_FN_DECL(char   *strrstrn,
	(const char *, const char *, size_t));
COMPAT_FN_DECL(char   *STRFUNCS_strstr,
	(const char *, const char *));
COMPAT_FN_DECL(char   *strstrn,
	(const char *, const char *, size_t));
COMPAT_FN_DECL(const char *strwrap,
	(const char *in_string, int *current_col, int max_length,
	int *tab_count, int tab_setting, int strip_flag, char *last_char,
	char *out_string));
COMPAT_FN_DECL(int     wordwrap,
	(const char *in_text, char **out_list, int max_cols,
	int max_rows));

/* *********************************************************************** */

#endif /* #ifndef h__STRFUNCS_H__h */

