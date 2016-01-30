/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Include File											*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the DCR memory-mapped cache library.

	Revision History	:	1994-03-12 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__DCR_H__h

#define h__DCR_H__h							1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Required include files . . .														*/
/*	***********************************************************************	*/

#include <fcntl.h>
#include <sys/mman.h>

#ifndef __MSDOS__
#include <sys/time.h>
#else
#include <time.h>
#endif /* __MSDOS__ */

#include <strfuncs.h>
#include <sdtif.h>
#include <genfuncs.h>
#include <datfuncs.h>
#include <mfile.h>
#include <dbcfuncs.h>

#include "dcrlock.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#ifdef NO_CONST
# ifndef const
#  define const
# endif /* #ifndef const */
#endif /* #ifdef NO_CONST */

#ifdef NO_VOLATILE
# ifndef volatile
#  define volatile
# endif /* #ifndef volatile */
#endif /* #ifndef NO_VOLATILE */

#ifdef NO_VOID
# ifndef void
#  define void char
# endif /* #ifndef void */
#endif /* #ifdef NO_VOID */

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* ***** strlen("99.99.99A") = 9	*/
#define DCR_VERSION_NUMBER_LENGTH		(9 + 1)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	DCR Library Version Number

   NAME        :	DCR Library Version Number

   DESCRIPTION :	The DCR library version number manifest constants
						together define the current version number of the DCR
						library as a whole.

						(.) ''DCR_VERSION_MAJOR'' represents the major
						component of the library version number.

						(.) ''DCR_VERSION_MINOR'' represents the minor
						component of the library version number.

						(.) ''DCR_VERSION_RELEASE'' represents the release
						component of the library version number.

						(.) ''DCR_VERSION_BUILD'' represents the build
						level component of the library version number.

   SEE ALSO    :	STR_VERSION

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2016 Michael L. Brock

   OUTPUT INDEX:	DCR_VERSION_MAJOR
						DCR_VERSION_MINOR
						DCR_VERSION_RELEASE
						DCR_VERSION_BUILD
						DCR Version Numbers:Library Version Number
						Library Version Number:DCR_VERSION_MAJOR
						Library Version Number:DCR_VERSION_MINOR
						Library Version Number:DCR_VERSION_RELEASE
						Library Version Number:DCR_VERSION_BUILD
						Macros and Manifest Constants:DCR_VERSION_MAJOR
						Macros and Manifest Constants:DCR_VERSION_MINOR
						Macros and Manifest Constants:DCR_VERSION_RELEASE
						Macros and Manifest Constants:DCR_VERSION_BUILD
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	DCR_VERSION_MAJOR
						DCR_VERSION_MINOR
						DCR_VERSION_RELEASE
						DCR_VERSION_BUILD
						DCR Library Version Number
						DCR library version number
						DCR Library Version
						DCR library version
						DCR Version Number
						DCR version number
						DCR Version
						DCR version

   PUBLISH NAME:	DCR_VERSION_MAJOR
						DCR_VERSION_MINOR
						DCR_VERSION_RELEASE
						DCR_VERSION_BUILD

	ENTRY CLASS	:	Macros and Manifest Constants:Library Version Number
						DCR Version Numbers:Library Version Number

EOH */
/*	***********************************************************************	*/
#define DCR_VERSION_MAJOR					((unsigned char) 1)
#define DCR_VERSION_MINOR					((unsigned char) 0)
#define DCR_VERSION_RELEASE				((unsigned char) 0)
#define DCR_VERSION_BUILD					((unsigned char) 'A')
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   BASE NAME   :  DCR Truth Codes

   NAME        :  DCR Truth Codes

   DESCRIPTION :  Manifest constants used within DCR to specify the truth
						or falsity of expressions.

						(.) ''DCR_TRUE'' is defined as ''1''.

						(.) ''DCR_FALSE'' is defined as ''0''.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2016 Michael L. Brock

   OUTPUT INDEX:  DCR_TRUE
						DCR_FALSE
						Truth Codes:DCR_TRUE
						Truth Codes:DCR_FALSE
						Macros and Manifest Constants:DCR_TRUE
						Macros and Manifest Constants:DCR_FALSE
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:  DCR_TRUE
						DCR_FALSE
						DCR Truth Codes
						DCR Truth Code
						DCR truth codes
						DCR truth code

   PUBLISH NAME:	DCR_TRUE
						DCR_FALSE

	ENTRY CLASS	:	Macros and Manifest Constants:Truth Codes

EOH */
/* *********************************************************************** */
#define DCR_TRUE								1
#define DCR_FALSE								0
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   BASE NAME   :	DCR Return Codes

   NAME        :  DCR Return Codes

   DESCRIPTION :  The DCR return codes have the following meanings:

						(.) ''DCR_SUCCESS'' means that the function invoked
						completed without error. ''DCR_SUCCESS'' is guaranteed to
						be equal to zero (''0'').

						(.) ''DCR_FAILURE'' indicates that the function invoked
						encountered a general operation failure. This is the
						'catch-all' error code for those errors which do not fit
						into category of one the other DCR error codes.

						(.) ''DCR_SYSTEM_FAILURE'' indicates that the function
						invoked encountered a failure of a standard library function
						or an operating system call.

						(.) ''DCR_DB_FAILURE'' indicates that the function
						invoked encountered a failure of a database operation.

						(.) ''DCR_BAD_ARGS_FAILURE'' indicates that the arguments
						passed to a function invoked were invalid.

						(.) ''DCR_MEMORY_FAILURE'' indicates that the memory
						required for operation of the function invoked could not be
						allocated.

						(.) ''DCR_LOCK_ACQ_FAILURE'' indicates that a
						lock could not be acquired on an DCR resource.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2016 Michael L. Brock

   OUTPUT INDEX:  DCR_SUCCESS
						DCR_FAILURE
						DCR_SYSTEM_FAILURE
						DCR_DB_FAILURE
						DCR_BAD_ARGS_FAILURE
						DCR_MEMORY_FAILURE
						DCR_LOCK_ACQ_FAILURE
						Return Codes:DCR_SUCCESS
						Return Codes:DCR_FAILURE
						Return Codes:DCR_SYSTEM_FAILURE
						Return Codes:DCR_DB_FAILURE
						Return Codes:DCR_BAD_ARGS_FAILURE
						Return Codes:DCR_MEMORY_FAILURE
						Return Codes:DCR_LOCK_ACQ_FAILURE
						Macros and Manifest Constants:DCR_SUCCESS
						Macros and Manifest Constants:DCR_FAILURE
						Macros and Manifest Constants:DCR_SYSTEM_FAILURE
						Macros and Manifest Constants:DCR_DB_FAILURE
						Macros and Manifest Constants:DCR_BAD_ARGS_FAILURE
						Macros and Manifest Constants:DCR_MEMORY_FAILURE
						Macros and Manifest Constants:DCR_LOCK_ACQ_FAILURE
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:  DCR_SUCCESS
						DCR_FAILURE
						DCR_SYSTEM_FAILURE
						DCR_DB_FAILURE
						DCR_BAD_ARGS_FAILURE
						DCR_MEMORY_FAILURE
						DCR_LOCK_ACQ_FAILURE
						DCR Return Codes
						DCR Return Code
						DCR return codes
						DCR return code
						DCR Status Codes
						DCR Status Code
						DCR status codes
						DCR status code
						DCR Error Codes
						DCR Error Code
						DCR error codes
						DCR error code

   PUBLISH NAME:	DCR_SUCCESS
						DCR_FAILURE
						DCR_SYSTEM_FAILURE
						DCR_DB_FAILURE
						DCR_BAD_ARGS_FAILURE
						DCR_MEMORY_FAILURE
						DCR_LOCK_ACQ_FAILURE

	ENTRY CLASS	:	Macros and Manifest Constants:Return Codes

EOH */
/* *********************************************************************** */
/* *********************************************************************** */
#define DCR_SUCCESS							 0
#define DCR_FAILURE							-1
#define DCR_BAD_ARGS_FAILURE				-2
#define DCR_MEMORY_FAILURE					-3
#define DCR_DB_FAILURE						-4
#define DCR_SYSTEM_FAILURE					-5
#define DCR_LOCK_ACQ_FAILURE				-6
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  DCR_MAX_ERROR_TEXT

   DESCRIPTION :  The manifest constant ''DCR_MAX_ERROR_TEXT'' defines the
						minimum amount of storage which should be allocated to
						hold an error message returned by a DCR function.

   CAVEATS     :  DCR error messages can be quite lengthy. Therefore,
						attempting to save space by allocating less than
						''DCR_MAX_ERROR_TEXT'' bytes to error message buffers
						passed to DCR functions can lead to overwriting of the
						heap or the stack.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2016 Michael L. Brock

   OUTPUT INDEX:  DCR_MAX_ERROR_TEXT
						Macros and Manifest Constants:DCR_MAX_ERROR_TEXT
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	DCR_MAX_ERROR_TEXT

   PUBLISH NAME:	DCR_MAX_ERROR_TEXT

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/* *********************************************************************** */
#define DCR_MAX_ERROR_TEXT					2048
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	DCR Default Maximum Name Lengths

   NAME        :	DCR Default Maximum Name Lengths

   DESCRIPTION :	DCR default maximum name lengths are manifest constants
						that define the lengths of a variety of ''char'' arrays
						members of DCR data structures.

						The following DCR default maximum name lengths are
						defined:

						(.) ''DCR_MAX_TINY_NAME'' is defined as ''7''.

						(.) ''DCR_MAX_SHORT_NAME'' is defined as ''15''.

						(.) ''DCR_MAX_SMALL_NAME'' is defined as ''31''.

						(.) ''DCR_MAX_MEDIUM_NAME'' is defined as ''63''.

						(.) ''DCR_MAX_LARGE_NAME'' is defined as ''127''.

						(.) ''DCR_MAX_GIANT_NAME'' is defined as ''255''.

   NOTES       :	You may notice that DCR default maximum name lengths,
						when ''1'' is added for the string ASCII 0 terminator,
						become powers of two.

   SEE ALSO    :	DCR Maximum Name Lengths

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2016 Michael L. Brock

   OUTPUT INDEX:	DCR_MAX_TINY_NAME
						DCR_MAX_SHORT_NAME
						DCR_MAX_SMALL_NAME
						DCR_MAX_MEDIUM_NAME
						DCR_MAX_LARGE_NAME
						DCR_MAX_GIANT_NAME
						Macros and Manifest Constants:DCR Default Maximum Name Lengths:DCR_MAX_TINY_NAME
						Macros and Manifest Constants:DCR Default Maximum Name Lengths:DCR_MAX_SHORT_NAME
						Macros and Manifest Constants:DCR Default Maximum Name Lengths:DCR_MAX_SMALL_NAME
						Macros and Manifest Constants:DCR Default Maximum Name Lengths:DCR_MAX_MEDIUM_NAME
						Macros and Manifest Constants:DCR Default Maximum Name Lengths:DCR_MAX_LARGE_NAME
						Macros and Manifest Constants:DCR Default Maximum Name Lengths:DCR_MAX_GIANT_NAME
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	DCR_MAX_TINY_NAME
						DCR_MAX_SHORT_NAME
						DCR_MAX_SMALL_NAME
						DCR_MAX_MEDIUM_NAME
						DCR_MAX_LARGE_NAME
						DCR_MAX_GIANT_NAME
						DCR Default Maximum Name Lengths
						DCR Default Maximum Name Length
						DCR default maximum name lengths
						DCR default maximum name length

   PUBLISH NAME:	DCR_MAX_TINY_NAME
						DCR_MAX_SHORT_NAME
						DCR_MAX_SMALL_NAME
						DCR_MAX_MEDIUM_NAME
						DCR_MAX_LARGE_NAME
						DCR_MAX_GIANT_NAME

	ENTRY CLASS	:	Macros and Manifest Constants:DCR Default Maximum Name Lengths

EOH */
/*	***********************************************************************	*/
/* You may notice that these values, when ''1'' is added for the string
	ASCII 0 terminator, are all powers of two.
*/
#define DCR_MAX_TINY_NAME					  7
#define DCR_MAX_SHORT_NAME					 15
#define DCR_MAX_SMALL_NAME					 31
#define DCR_MAX_MEDIUM_NAME				 63
#define DCR_MAX_LARGE_NAME					127
#define DCR_MAX_GIANT_NAME					255
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	DCR Maximum Name Lengths

   NAME        :	DCR Maximum Name Lengths

   DESCRIPTION :	The DCR maximum name lengths are manifest constants
						that define the lengths of a number of different ''char''
						array members of DCR data structures.

						(.) ''DCR_MAX_COLL_SPEC_NAME'' is the maximum length of
						a collection specification. It is defined as equal to the
						DCR default maximum name length manifest constant
						''DCR_MAX_MEDIUM_NAME''.

						(.) ''DCR_MAX_PRIMITIVE_TYPE'' is the maximum length of
						a primitive type string. It is defined as equal to the
						DCR default maximum name length manifest constant
						''DCR_MAX_MEDIUM_NAME''.

						(.) ''DCR_MAX_VENDOR_NAME'' is the maximum length of
						a vendor name. It is defined as equal to the DCR default
						maximum name length manifest constant
						''DCR_MAX_SMALL_NAME''.

						(.) ''DCR_MAX_DATA_PROTO'' is the maximum length of
						a data protocol. It is defined as equal to the DCR
						default maximum name length manifest constant
						''DCR_MAX_SMALL_NAME''.

						(.) ''DCR_MAX_DELIVERY_PROTO'' is the maximum length of
						a delivery protocol. It is defined as equal to the DCR
						default maximum name length manifest constant
						''DCR_MAX_SMALL_NAME''.

						(.) ''DCR_MAX_DATA_TYPE_NAME'' is the maximum length of
						a data type name. It is defined as equal to the DCR
						default maximum name length manifest constant
						''DCR_MAX_SMALL_NAME''.

						(.) ''DCR_MAX_FIELD_NAME'' is the maximum length of
						a field name. It is defined as equal to the DCR default
						maximum name length manifest constant
						''DCR_MAX_SMALL_NAME''.

						(.) ''DCR_MAX_RECORD_NAME'' is the maximum length of
						a record name. It is defined as equal to the DCR default
						maximum name length manifest constant
						''DCR_MAX_SMALL_NAME''.

						(.) ''DCR_MAX_INSTRUMENT_NAME'' is the maximum length of
						an instrument name. It is defined as equal to the DCR
						default maximum name length manifest constant
						''DCR_MAX_MEDIUM_NAME''.

						(.) ''DCR_MAX_DB_SPEC_LEN'' is the maximum length of
						a database specification connection string. It is defined
						as equal to the DCR default maximum name length manifest
						constant ''DCR_MAX_MEDIUM_NAME''.

						(.) ''DCR_MAX_FACILITY_NAME'' is the maximum length of
						a DCR delivery protocol facility name. It is defined
						as equal to the DCR default maximum name length manifest
						constant ''DCR_MAX_SMALL_NAME''.

   SEE ALSO    :	DCR Default Maximum Name Lengths

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2016 Michael L. Brock

   OUTPUT INDEX:	DCR_MAX_COLL_SPEC_NAME
						DCR_MAX_PRIMITIVE_TYPE
						DCR_MAX_VENDOR_NAME
						DCR_MAX_DATA_PROTO
						DCR_MAX_DELIVERY_PROTO
						DCR_MAX_DATA_TYPE_NAME
						DCR_MAX_FIELD_NAME
						DCR_MAX_RECORD_NAME
						DCR_MAX_INSTRUMENT_NAME
						DCR_MAX_DB_SPEC_LEN
						DCR_MAX_FACILITY_NAME
						Macros and Manifest Constants:DCR Maximum Name Lengths:DCR_MAX_COLL_SPEC_NAME
						Macros and Manifest Constants:DCR Maximum Name Lengths:DCR_MAX_PRIMITIVE_TYPE
						Macros and Manifest Constants:DCR Maximum Name Lengths:DCR_MAX_VENDOR_NAME
						Macros and Manifest Constants:DCR Maximum Name Lengths:DCR_MAX_DATA_PROTO
						Macros and Manifest Constants:DCR Maximum Name Lengths:DCR_MAX_DELIVERY_PROTO
						Macros and Manifest Constants:DCR Maximum Name Lengths:DCR_MAX_DATA_TYPE_NAME
						Macros and Manifest Constants:DCR Maximum Name Lengths:DCR_MAX_FIELD_NAME
						Macros and Manifest Constants:DCR Maximum Name Lengths:DCR_MAX_RECORD_NAME
						Macros and Manifest Constants:DCR Maximum Name Lengths:DCR_MAX_INSTRUMENT_NAME
						Macros and Manifest Constants:DCR Maximum Name Lengths:DCR_MAX_DB_SPEC_LEN
						Macros and Manifest Constants:DCR Maximum Name Lengths:DCR_MAX_FACILITY_NAME
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	DCR_MAX_COLL_SPEC_NAME
						DCR_MAX_PRIMITIVE_TYPE
						DCR_MAX_VENDOR_NAME
						DCR_MAX_DATA_PROTO
						DCR_MAX_DELIVERY_PROTO
						DCR_MAX_DATA_TYPE_NAME
						DCR_MAX_FIELD_NAME
						DCR_MAX_RECORD_NAME
						DCR_MAX_INSTRUMENT_NAME
						DCR_MAX_DB_SPEC_LEN
						DCR_MAX_FACILITY_NAME
						DCR Maximum Name Lengths
						DCR Maximum Name Length
						DCR maximum name lengths
						DCR maximum name length

   PUBLISH NAME:	DCR_MAX_COLL_SPEC_NAME
						DCR_MAX_PRIMITIVE_TYPE
						DCR_MAX_VENDOR_NAME
						DCR_MAX_DATA_PROTO
						DCR_MAX_DELIVERY_PROTO
						DCR_MAX_DATA_TYPE_NAME
						DCR_MAX_FIELD_NAME
						DCR_MAX_RECORD_NAME
						DCR_MAX_INSTRUMENT_NAME
						DCR_MAX_DB_SPEC_LEN
						DCR_MAX_FACILITY_NAME

	ENTRY CLASS	:	Macros and Manifest Constants:DCR Maximum Name Lengths

EOH */
/*	***********************************************************************	*/
#define DCR_MAX_INDEX_NAME					DCR_MAX_SMALL_NAME
#define DCR_MAX_ACCESS_NAME				DCR_MAX_SHORT_NAME
#define DCR_MAX_STATUS_NAME				DCR_MAX_SHORT_NAME
#define DCR_MAX_AREA_NAME					DCR_MAX_SMALL_NAME
#define DCR_MAX_STAT_NAME					DCR_MAX_SHORT_NAME
#define DCR_MAX_COMPARE_TYPE_NAME		DCR_MAX_SMALL_NAME
#define DCR_MAX_CB_NAME						DCR_MAX_SMALL_NAME
#define DCR_MAX_LOGICAL_NAME				DCR_MAX_SMALL_NAME
#define DCR_MAX_TYPE_NAME					DCR_MAX_SMALL_NAME
#define DCR_MAX_TYPE_SHORT_NAME			DCR_MAX_SMALL_NAME
#define DCR_MAX_TYPE_SPEC					DCR_MAX_MEDIUM_NAME
#define DCR_MAX_FIELD_NAME					DCR_MAX_SMALL_NAME
#define DCR_MAX_COLUMN_NAME				DCR_MAX_SMALL_NAME
#define DCR_MAX_SERVER_NAME				DCR_MAX_SMALL_NAME
#define DCR_MAX_DATABASE_NAME				DCR_MAX_SMALL_NAME
#define DCR_MAX_OWNER_NAME					DCR_MAX_SMALL_NAME
#define DCR_MAX_TABLE_NAME					DCR_MAX_SMALL_NAME
#define DCR_MAX_USER_NAME					DCR_MAX_SMALL_NAME
#define DCR_MAX_PASS_WORD					DCR_MAX_SMALL_NAME
#define DCR_MAX_DB_SPEC_STRING									\
	(DCR_MAX_SERVER_NAME + 1 + DCR_MAX_DATABASE_NAME + 1 + \
	DCR_MAX_OWNER_NAME + 1 + DCR_MAX_USER_NAME + 1 + DCR_MAX_PASS_WORD)

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	DCR Truth Code Mappings

   NAME        :	DCR Truth Code Mappings

	SYNOPSIS		:	truth_code = DCR_MAP_TRUTH_STR_TO_DCR(strfuncs_code);

						truth_code = DCR_MAP_TRUTH_GEN_TO_DCR(genfuncs_code);

						truth_code = DCR_MAP_TRUTH_DAT_TO_DCR(datfuncs_code);

						truth_code = DCR_MAP_TRUTH_MFILE_TO_DCR(mfile_code);

	DESCRIPTION	:	The DCR truth code mapping macros map truth codes from
						various low-level libraries to DCR truth codes.

						(.) ''DCR_MAP_TRUTH_STR_TO_DCR'' maps a truth code
						from a STRFUNCS truth code to a DCR truth code.

						(.) ''DCR_MAP_TRUTH_GEN_TO_DCR'' maps a truth code
						from a GENFUNCS truth code to a DCR truth code.

						(.) ''DCR_MAP_TRUTH_DAT_TO_DCR'' maps a truth code
						from a DATFUNCS truth code to a DCR truth code.

						(.) ''DCR_MAP_TRUTH_MFILE_TO_DCR'' maps a truth code
						from a MFILE truth code to a DCR truth code.

	PARAMETERS	:	The single parameter to these macros is the value of the
						truth code to be mapped to its equivalent DCR truth
						code.

   NOTES       :	To map return codes from the libraries, use the related
						DCR return code mapping macros.

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2016 Michael L. Brock

   OUTPUT INDEX:	DCR_MAP_TRUTH_STR_TO_DCR
						DCR_MAP_TRUTH_GEN_TO_DCR
						DCR_MAP_TRUTH_DAT_TO_DCR
						DCR_MAP_TRUTH_MFILE_TO_DCR
						Truth Code Mappings:DCR_MAP_TRUTH_STR_TO_DCR
						Truth Code Mappings:DCR_MAP_TRUTH_GEN_TO_DCR
						Truth Code Mappings:DCR_MAP_TRUTH_DAT_TO_DCR
						Truth Code Mappings:DCR_MAP_TRUTH_MFILE_TO_DCR
						Macros and Manifest Constants:DCR_MAP_TRUTH_STR_TO_DCR
						Macros and Manifest Constants:DCR_MAP_TRUTH_GEN_TO_DCR
						Macros and Manifest Constants:DCR_MAP_TRUTH_DAT_TO_DCR
						Macros and Manifest Constants:DCR_MAP_TRUTH_MFILE_TO_DCR
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	DCR_MAP_TRUTH_STR_TO_DCR
						DCR_MAP_TRUTH_GEN_TO_DCR
						DCR_MAP_TRUTH_DAT_TO_DCR
						DCR_MAP_TRUTH_MFILE_TO_DCR
						DCR Truth Code Mappings
						DCR Truth Code Mapping
						DCR truth code mappings
						DCR truth code mapping

   PUBLISH NAME:	DCR_MAP_TRUTH_STR_TO_DCR
						DCR_MAP_TRUTH_GEN_TO_DCR
						DCR_MAP_TRUTH_DAT_TO_DCR
						DCR_MAP_TRUTH_MFILE_TO_DCR

	ENTRY CLASS	:	Macros and Manifest Constants:Truth Code Mappings

EOH */
/*	***********************************************************************	*/
#define DCR_MAP_TRUTH_STR_TO_DCR(str_code)		\
	(((str_code) == STRFUNCS_TRUE) ? DCR_TRUE : DCR_FALSE)

#define DCR_MAP_TRUTH_GEN_TO_DCR(gen_code)		\
	(((gen_code) == GENFUNCS_TRUE) ? DCR_TRUE : DCR_FALSE)

#define DCR_MAP_TRUTH_DAT_TO_DCR(dat_code)		\
	(((dat_code) == DATFUNCS_TRUE) ? DCR_TRUE : DCR_FALSE)

#define DCR_MAP_TRUTH_MFILE_TO_DCR(mfile_code)	\
	(((mfile_code) == MFILE_TRUE) ? DCR_TRUE : DCR_FALSE)

#define DCR_MAP_TRUTH_DBC_TO_DCR(dbc_code)		\
	(((dbc_code) == DBC_TRUE) ? DCR_TRUE : DCR_FALSE)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	DCR Return Code Mappings

   NAME        :	DCR Return Code Mappings

	SYNOPSIS		:	return_code = DCR_MAP_ERROR_STR_TO_DCR(strfuncs_code);

						return_code = DCR_MAP_ERROR_GEN_TO_DCR(genfuncs_code);

						return_code = DCR_MAP_ERROR_DAT_TO_DCR(datfuncs_code);

	DESCRIPTION	:	The DCR return code mapping macros map return codes from
						various low-level libraries to DCR return codes.

						(.) ''DCR_MAP_ERROR_STR_TO_DCR'' maps a return code
						from a STRFUNCS return code to a DCR return code.

						(.) ''DCR_MAP_ERROR_GEN_TO_DCR'' maps a return code
						from a GENFUNCS return code to a DCR return code.

						(.) ''DCR_MAP_ERROR_DAT_TO_DCR'' maps a return code
						from a DATFUNCS return code to a DCR return code.

	PARAMETERS	:	The single parameter to these macros is the value of the
						return code to be mapped to its equivalent DCR return
						code.

   NOTES       :	To map truth codes from the libraries, use the related
						DCR truth code mapping macros.

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2016 Michael L. Brock

   OUTPUT INDEX:	DCR_MAP_ERROR_STR_TO_DCR
						DCR_MAP_ERROR_GEN_TO_DCR
						DCR_MAP_ERROR_DAT_TO_DCR
						Return Code Mappings:DCR_MAP_ERROR_STR_TO_DCR
						Return Code Mappings:DCR_MAP_ERROR_GEN_TO_DCR
						Return Code Mappings:DCR_MAP_ERROR_DAT_TO_DCR
						Macros and Manifest Constants:DCR_MAP_ERROR_STR_TO_DCR
						Macros and Manifest Constants:DCR_MAP_ERROR_GEN_TO_DCR
						Macros and Manifest Constants:DCR_MAP_ERROR_DAT_TO_DCR
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	DCR_MAP_ERROR_STR_TO_DCR
						DCR_MAP_ERROR_GEN_TO_DCR
						DCR_MAP_ERROR_DAT_TO_DCR
						DCR Return Code Mappings
						DCR Return Code Mapping
						DCR return code mappings
						DCR return code mapping
						DCR Status Code Mappings
						DCR Status Code Mapping
						DCR status code mappings
						DCR status code mapping
						DCR Error Code Mappings
						DCR Error Code Mapping
						DCR error code mappings
						DCR error code mapping

   PUBLISH NAME:	DCR_MAP_ERROR_STR_TO_DCR
						DCR_MAP_ERROR_GEN_TO_DCR
						DCR_MAP_ERROR_DAT_TO_DCR

	ENTRY CLASS	:	Macros and Manifest Constants:Return Code Mappings

EOH */
/*	***********************************************************************	*/
#define DCR_MAP_ERROR_STR_TO_DCR(str_code)										\
	(((str_code) == STRFUNCS_SUCCESS) ? DCR_SUCCESS : DCR_FAILURE)

#define DCR_MAP_ERROR_GEN_TO_DCR(gen_code)										\
	(((gen_code) == GENFUNCS_SUCCESS)          ? DCR_SUCCESS          :	\
	 ((gen_code) == GENFUNCS_FAILURE)          ? DCR_FAILURE          :	\
	 ((gen_code) == GENFUNCS_BAD_ARGS_FAILURE) ? DCR_BAD_ARGS_FAILURE :	\
	 ((gen_code) == GENFUNCS_MEMORY_FAILURE)   ? DCR_MEMORY_FAILURE   :	\
	 ((gen_code) == GENFUNCS_SYSTEM_FAILURE)   ? DCR_SYSTEM_FAILURE   :	\
	 ((gen_code) == GENFUNCS_LOCK_ACQ_FAILURE) ? DCR_LOCK_ACQ_FAILURE :	\
	 DCR_FAILURE)

#define DCR_MAP_ERROR_DAT_TO_DCR(dat_code)										\
	(((dat_code) == DATFUNCS_SUCCESS) ? DCR_SUCCESS : DCR_FAILURE)

#define DCR_MAP_ERROR_DBC_TO_DCR(dbc_code)										\
	(((dbc_code) == DBC_SUCCESS)          ? DCR_SUCCESS          :			\
	 ((dbc_code) == DBC_FAILURE)          ? DCR_FAILURE          :			\
	 ((dbc_code) == DBC_BAD_ARGS_FAILURE) ? DCR_BAD_ARGS_FAILURE :			\
	 ((dbc_code) == DBC_MEMORY_FAILURE)   ? DCR_MEMORY_FAILURE   :			\
	 ((dbc_code) == DBC_DB_FAILURE)       ? DCR_DB_FAILURE       :			\
	 ((dbc_code) == DBC_SYSTEM_FAILURE)   ? DCR_SYSTEM_FAILURE   :			\
	 DCR_FAILURE)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define DCR_SIGNATURE						((unsigned long) 0X4D4C4200L)

/*
#define DCR_VERSION_CACHE					((unsigned long) 0X01000041L)
*/
#define DCR_VERSION_CACHE					((((unsigned long) 0X01L) << 24L) |	\
													 (((unsigned long) 0X00L) << 16L) |	\
													 (((unsigned long) 0X00L) <<  8L) |	\
													  ((unsigned long) 0X41L))

#define DCR_VERSION_LIBRARY				"02.01.00A"


/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define DCR_USER_DATA_PTR_COUNT	16

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define DCR_RECORD_FOUND			DCR_TRUE
#define DCR_RECORD_NOT_FOUND		DCR_FALSE

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define DCR_I_AM_WRITER				((unsigned long) 0X55555555L)
#define DCR_I_AM_READER				((unsigned long) 0XAAAAAAAAL)

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	BASE NAME	:	DCR Compare Types

   NAME        :  DCR Compare Types

   DESCRIPTION :  Manifest constants used to specify the relational
						operators available for cache search routines.

						(.) ''DCR_COMPARE_TYPE_EQ'' specifies that only
						those records equal to the key are to participate in the
						search.

						(.) ''DCR_COMPARE_TYPE_GE'' specifies that only
						those records greater than or equal to the key are to
						participate in the search.

						(.) ''DCR_COMPARE_TYPE_GT'' specifies that only
						those records greater than the key are to participate in
						the search.

						(.) ''DCR_COMPARE_TYPE_LE'' specifies that only
						those records less than or equal to the key are to
						participate in the search.

						(.) ''DCR_COMPARE_TYPE_LT'' specifies that only
						those records less than the key are to participate in the
						search.

						(.) ''DCR_COMPARE_TYPE_NE'' specifies that only
						those records not equal to the key are to participate in
						the search.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2016 Michael L. Brock

   OUTPUT INDEX:  DCR_COMPARE_TYPE_EQ
						DCR_COMPARE_TYPE_GE
						DCR_COMPARE_TYPE_GT
						DCR_COMPARE_TYPE_LE
						DCR_COMPARE_TYPE_LT
						DCR_COMPARE_TYPE_NE
						DCR Compare Types:DCR_COMPARE_TYPE_EQ
						DCR Compare Types:DCR_COMPARE_TYPE_GE
						DCR Compare Types:DCR_COMPARE_TYPE_GT
						DCR Compare Types:DCR_COMPARE_TYPE_LE
						DCR Compare Types:DCR_COMPARE_TYPE_LT
						DCR Compare Types:DCR_COMPARE_TYPE_NE
						DCR Manifest Constants:DCR_COMPARE_TYPE_EQ
						DCR Manifest Constants:DCR_COMPARE_TYPE_GE
						DCR Manifest Constants:DCR_COMPARE_TYPE_GT
						DCR Manifest Constants:DCR_COMPARE_TYPE_LE
						DCR Manifest Constants:DCR_COMPARE_TYPE_LT
						DCR Manifest Constants:DCR_COMPARE_TYPE_NE
						DCR Defines:see DCR Macros
						DCR Defines:see DCR Manifest Constants

   PUBLISH XREF:	DCR_COMPARE_TYPE_EQ
						DCR_COMPARE_TYPE_GE
						DCR_COMPARE_TYPE_GT
						DCR_COMPARE_TYPE_LE
						DCR_COMPARE_TYPE_LT
						DCR_COMPARE_TYPE_NE

   PUBLISH NAME:	DCR Compare Types
						DCR_COMPARE_TYPE_EQ
						DCR_COMPARE_TYPE_GE
						DCR_COMPARE_TYPE_GT
						DCR_COMPARE_TYPE_LE
						DCR_COMPARE_TYPE_LT
						DCR_COMPARE_TYPE_NE

EOH */
/* *********************************************************************** */

#define DCR_COMPARE_TYPE_EQ		((unsigned int) 0)
#define DCR_COMPARE_TYPE_GE		((unsigned int) 1)
#define DCR_COMPARE_TYPE_GT		((unsigned int) 2)
#define DCR_COMPARE_TYPE_LE		((unsigned int) 3)
#define DCR_COMPARE_TYPE_LT		((unsigned int) 4)
#define DCR_COMPARE_TYPE_NE		((unsigned int) 5)

#define DCR_COMPARE_TYPE_COUNT	6

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	BASE NAME	:	DCR Anchor Flags

   NAME        :  DCR Anchor Flags

   DESCRIPTION :  Manifest constants used to specify the anchor points for
						record searches.

						(.) ''DCR_FIND_TOP'' specifies that the record search
						is to be anchored at the first of the records meeting the
						relational criterion.

						(.) ''DCR_FIND_BOTTOM'' specifies that the record
						search is to be anchored at the last of the records meeting
						the relational criterion.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2016 Michael L. Brock

   OUTPUT INDEX:  DCR_FIND_TOP
						DCR_FIND_BOTTOM
						DCR Anchor Flags:DCR_FIND_TOP
						DCR Anchor Flags:DCR_FIND_BOTTOM
						DCR Manifest Constants:DCR_FIND_TOP
						DCR Manifest Constants:DCR_FIND_BOTTOM
						DCR Defines:see DCR Macros
						DCR Defines:see DCR Manifest Constants

   PUBLISH XREF:	DCR_FIND_TOP
						DCR_FIND_BOTTOM

   PUBLISH NAME:	DCR Anchor Flags
						DCR_FIND_TOP
						DCR_FIND_BOTTOM

EOH */
/* *********************************************************************** */
#define DCR_FIND_TOP					STRFUNCS_DIRECTION_TOP
#define DCR_FIND_BOTTOM				STRFUNCS_DIRECTION_BOTTOM
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	BASE NAME	:	DCR Record Search Flags

   NAME        :  DCR Record Search Flags

   DESCRIPTION :  Manifest constants used to specify the types of records to
						which a search applies.

						(.) ''DCR_RECORD_FLAG_ALL'' specifies that the search
						is to be applied to all records in the cache.

						(.) ''DCR_RECORD_FLAG_KEPT'' specifies that the
						search is to be applied only to records in the cache which
						have not been deleted.

						(.) ''DCR_RECORD_FLAG_DELETED'' specifies that the
						search is to be applied only to records in the cache which
						have been deleted.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2016 Michael L. Brock

   OUTPUT INDEX:  DCR_RECORD_FLAG_ALL
						DCR_RECORD_FLAG_KEPT
						DCR_RECORD_FLAG_DELETED
						DCR Record Search Flags:DCR_RECORD_FLAG_ALL
						DCR Record Search Flags:DCR_RECORD_FLAG_KEPT
						DCR Record Search Flags:DCR_RECORD_FLAG_DELETED
						DCR Manifest Constants:DCR_RECORD_FLAG_ALL
						DCR Manifest Constants:DCR_RECORD_FLAG_KEPT
						DCR Manifest Constants:DCR_RECORD_FLAG_DELETED
						DCR Defines:see DCR Macros
						DCR Defines:see DCR Manifest Constants

   PUBLISH XREF:	DCR_RECORD_FLAG_ALL
						DCR_RECORD_FLAG_KEPT
						DCR_RECORD_FLAG_DELETED

   PUBLISH NAME:	DCR Record Search Flags
						DCR_RECORD_FLAG_ALL
						DCR_RECORD_FLAG_KEPT
						DCR_RECORD_FLAG_DELETED

EOH */
/* *********************************************************************** */

#define DCR_RECORD_FLAG_ALL		0
#define DCR_RECORD_FLAG_KEPT		1
#define DCR_RECORD_FLAG_DELETED	2

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	BASE NAME	:	DCR Record List Types

   NAME        :  DCR Record List Types

   DESCRIPTION :  Manifest constants used to specify the type of list to be
						returned by one of the cache record list creation routines.

						(.) ''DCR_GET_LIST_TYPE_RECORD'' is used to get a
						list of records as defined.

						(.) ''DCR_GET_LIST_TYPE_FULL'' is used to get a list
						of records which includes the flags and locking structure
						for each record.

						(.) ''DCR_GET_LIST_TYPE_ELE'' is used to get a
						list of record elements to each of the records within the
						cache. To use such a list in the invoking function cast it
						to a pointer to ``unsigned int``.

						(.) ''DCR_GET_LIST_TYPE_OFF'' is used to get a
						list of offsets to each of the records within the cache.
						To use such a list in the invoking function cast it to a
						pointer to ``unsigned long``.

						(-) The offsets are from the beginning of the cache.

						(.) ''DCR_GET_LIST_TYPE_PTR'' is used to get a list
						of pointers to each of the records within the cache. To use
						such a list in the invoking function cast it to
						``void **``. If the data portion of the cache records
						represent a structure, cast it to ``structure **''.

						(-) The pointers are relative to the ``mmap()``ed pointer
						to the beginning of the cache. If the cache is re-mapped,
						the pointers will probably be invalidated.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2016 Michael L. Brock

   OUTPUT INDEX:  DCR_GET_LIST_TYPE_RECORD
						DCR_GET_LIST_TYPE_FULL
						DCR_GET_LIST_TYPE_ELE
						DCR_GET_LIST_TYPE_OFF
						DCR_GET_LIST_TYPE_PTR
						DCR Record List Types:DCR_GET_LIST_TYPE_RECORD
						DCR Record List Types:DCR_GET_LIST_TYPE_FULL
						DCR Record List Types:DCR_GET_LIST_TYPE_ELE
						DCR Record List Types:DCR_GET_LIST_TYPE_OFF
						DCR Record List Types:DCR_GET_LIST_TYPE_PTR
						DCR Manifest Constants:DCR_GET_LIST_TYPE_RECORD
						DCR Manifest Constants:DCR_GET_LIST_TYPE_FULL
						DCR Manifest Constants:DCR_GET_LIST_TYPE_ELE
						DCR Manifest Constants:DCR_GET_LIST_TYPE_OFF
						DCR Manifest Constants:DCR_GET_LIST_TYPE_PTR
						DCR Defines:see DCR Macros
						DCR Defines:see DCR Manifest Constants

   PUBLISH XREF:	DCR_GET_LIST_TYPE_RECORD
						DCR_GET_LIST_TYPE_FULL
						DCR_GET_LIST_TYPE_ELE
						DCR_GET_LIST_TYPE_OFF
						DCR_GET_LIST_TYPE_PTR

   PUBLISH NAME:	DCR Record List Types
						DCR_GET_LIST_TYPE_RECORD
						DCR_GET_LIST_TYPE_FULL
						DCR_GET_LIST_TYPE_ELE
						DCR_GET_LIST_TYPE_OFF
						DCR_GET_LIST_TYPE_PTR

EOH */
/* *********************************************************************** */

#define DCR_GET_LIST_TYPE_RECORD	0
#define DCR_GET_LIST_TYPE_FULL	1
#define DCR_GET_LIST_TYPE_ELE		2
#define DCR_GET_LIST_TYPE_OFF		3
#define DCR_GET_LIST_TYPE_PTR		4

#define DCR_GET_LIST_TYPE_OFFSET	DCR_GET_LIST_TYPE_OFF

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define DCR_CB_REC_INSERT			((unsigned long) 0X000000001L)
#define DCR_CB_SEARCH				((unsigned long) 0X000000002L)
#define DCR_CB_DELETE				((unsigned long) 0X000000004L)
#define DCR_CB_BULK_INSERT			((unsigned long) 0X000000008L)
#define DCR_CB_BULK_SEARCH			((unsigned long) 0X000000010L)
#define DCR_CB_INDEX_CACHE			((unsigned long) 0X000000020L)
#define DCR_CB_SORT_CACHE			((unsigned long) 0X000000040L)
#define DCR_CB_RESIZE_CACHE		((unsigned long) 0X000000080L)
#define DCR_CB_INITIAL_LOAD		((unsigned long) 0X000000100L)
#define DCR_CB_RELOAD				((unsigned long) 0X000000200L)
#define DCR_CB_UPDATE				((unsigned long) 0X000000400L)
#define DCR_CB_ALLOC_CHUNK			((unsigned long) 0X000000800L)
#define DCR_CB_REC_UPDATE			((unsigned long) 0X000001000L)
#define DCR_CB_CHECK_INDEX_1		((unsigned long) 0X000002000L)
#define DCR_CB_CHECK_INDEX_2		((unsigned long) 0X000004000L)

#define DCR_CB_COUNT					15

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define DCR_CYCLE_RETRY_COUNT		50
#define DCR_CYCLE_RETRY_TIME_OUT	((unsigned int) 10000)
#define DCR_LOCK_RETRY_COUNT		50
#define DCR_LOCK_RETRY_TIME_OUT	((unsigned int) 10000)

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define DCR_MAX_INDEX_COUNT		512

#define DCR_MAX_CACHE_NAME					255

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define DCR_STATUS_OK				((unsigned long) 0L)
#define DCR_STATUS_BUILDING		((unsigned long) 1L)
#define DCR_STATUS_INDEXING		((unsigned long) 2L)
#define DCR_STATUS_ADDING			((unsigned long) 3L)
#define DCR_STATUS_RESIZING		((unsigned long) 4L)

#define DCR_STATUS_COUNT			5

#define DCR_STATUS_CRITICAL		((unsigned long) 0X80000000L)

#define DCR_STATUS_MASK				((unsigned long) 0X7FFFFFFFL)

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define DCR_AREA_FIELD						0
#define DCR_AREA_FIELD_NAME				1
#define DCR_AREA_COLUMN_NAME				2
#define DCR_AREA_FIELD_ALIGN				3
#define DCR_AREA_INDEX						4
#define DCR_AREA_INDEX_NAME				5
#define DCR_AREA_INDEX_FIELD				6
#define DCR_AREA_INDEX_ALIGN				7

#define DCR_AREA_COUNT						8

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* *********************************************************************** */

#define DCR_DEF_FS_BLOCK_SIZE		512

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* *********************************************************************** */

#define DCR_MTMPFILE_PREFIX		"CACHE"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* *********************************************************************** */

#define DCR_DEFAULT_TDS_SIZE		8192

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/*    The macro 'offsetof' is defined by ANSI C. If it's not available on  */
/* this system, define it . . .                                            */
/* *********************************************************************** */

#ifndef offsetof
#define offsetof(structure_name, member_name) \
	((unsigned int) &(((structure_name *) 0)->member_name))
#endif /* #ifndef offsetof */

/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define DCR_GET_AREA_COUNT(cache_header_ptr, area_type) 					\
	(cache_header_ptr)->area_list[(area_type)].count

#define DCR_GET_AREA_ITEM_SIZE(cache_header_ptr, area_type)				\
	(cache_header_ptr)->area_list[(area_type)].item_size

#define DCR_GET_AREA_OFFSET(cache_header_ptr, area_type) 				\
	(cache_header_ptr)->area_list[(area_type)].offset

#define DCR_GET_AREA_ACTUAL_SIZE(cache_header_ptr, area_type)			\
	(cache_header_ptr)->area_list[(area_type)].actual_size

#define DCR_GET_AREA_TOTAL_SIZE(cache_header_ptr, area_type)			\
	(cache_header_ptr)->area_list[(area_type)].total_size

#define DCR_GET_AREA_POINTER(cache_header_ptr, mmap_ptr, area_type)	\
	(((char *) (mmap_ptr)) + ((unsigned int)											\
	DCR_GET_AREA_OFFSET(cache_header_ptr, area_type)))

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define DCR_STAT_MAKE_HEADER		 0
#define DCR_STAT_CREATE				 1
#define DCR_STAT_META_DATA			 2
#define DCR_STAT_RECORD_INSERT	 3
#define DCR_STAT_SEARCH				 4
#define DCR_STAT_DELETE				 5
#define DCR_STAT_BULK_INSERT		 6
#define DCR_STAT_BULK_SEARCH		 7
#define DCR_STAT_INDEX				 8
#define DCR_STAT_SORT				 9
#define DCR_STAT_RESIZE				10
#define DCR_STAT_INITIAL_DB_LOAD	11
#define DCR_STAT_DB_RELOAD			12
#define DCR_STAT_DB_UPDATE			13

#define DCR_STAT_COUNT				14

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

typedef struct {
	unsigned int  record_offset;
	char         *record_ptr;
} DCR_INS_1;

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

typedef struct {
	unsigned int  index_element;
	unsigned int  record_offset;
	char         *record_ptr;
} DCR_INS_2;

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define DCR_INSERT_ALLOC_NONE		0
#define DCR_INSERT_ALLOC_PART		1
#define DCR_INSERT_ALLOC_FULL		2

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define DCR_CREATE_MODE				0666

#define DCR_DEFAULT_UPDATE_NAME	"updatedate"

	/* For use in allocating a chunk of heap. The actual number of bytes
		allocated for a chunk is this manifest constant multiplied by the
		'total_record_size' member of the structure 'DCR_HEADER'. */
#define DCR_DEFAULT_GRANULARITY	1000

	/* Usually equal to the value returned by 'getpagesize()', but must not
		be less than the size of the structure 'DCR_HEADER'. */
#define DCR_HEADER_PAGE_SIZE		8192

#define DCR_MAX_RECORD_SIZE		((unsigned int) 32768L)
#define DCR_MAX_FIELD_SIZE			((unsigned int) 32768L)
#define DCR_MAX_FIELD_COUNT		((unsigned int) 1024L)

#define DCR_MIN_ALLOC_SIZE			512
#define DCR_MAX_ALLOC_SIZE			((unsigned int) 32768L)

#define DCR_DEFAULT_ALLOC_SIZE	4096

	/* Must be the size of the largest integral primitive data type. */
#define DCR_ALIGNMENT_SIZE			sizeof(double)

	/* The cache will leave this many file handles available by default. */
#define DCR_RESERVED_HANDLES		(1 + 1 + 1 + 5)

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

/*
	Determines whether the cache is using indirect or embedded indices.
*/
#define DCR_INDEX_IS_INDIRECT(cache_ptr)	\
	((cache_ptr)->header_ptr->indirect_index_flag)

/*
	Gets the size of an index entry for the specified index.
*/
#define DCR_INDEX_ENTRY_SIZE(cache_ptr, idx_method) 	\
	((DCR_INDEX_IS_INDIRECT(cache_ptr) == DCR_TRUE) ?	\
	sizeof(unsigned long) :												\
	(cache_ptr)->index_list[(idx_method)].index_entry_size)

/*
	Gets the offset of the data record offset within index entries for the
	specified index.
*/
#define DCR_INDEX_REC_OFF(cache_ptr, idx_method)				\
	((DCR_INDEX_IS_INDIRECT(cache_ptr) == DCR_TRUE) ? 0L :	\
	((unsigned long)																\
	(cache_ptr)->index_list[(idx_method)].index_pointer_offset))

#if 0
/*
	CODE NOTE: To be removed.
*/
/*
	Returns a pointer to the specified index entry within the specified
	index.
*/
#define DCR_INDEX_ENTRY_PTR(cache_ptr, idx_method, entry_count,	\
	entry_list, idx_element) (((char *) (entry_list)) +						\
	(((unsigned long) (idx_element)) *												\
	DCR_INDEX_ENTRY_SIZE(cache_ptr, idx_method)))
#endif /* #if 0 */

#if 0
/*
	CODE NOTE: To be removed.
*/
/*
	Gets the offset of the data record from the specified index entry within
	the specified index.
*/
#define DCR_INDEX_ENTRY_REC_OFF(cache_ptr, idx_method, entry_count,	\
	entry_list, idx_element)																\
	*((unsigned long *)																		\
	(DCR_INDEX_ENTRY_PTR(cache_ptr, idx_method, entry_count,				\
	entry_list, idx_element) +	DCR_INDEX_REC_OFF(cache_ptr, idx_method)))
#endif /* #if 0 */

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

	/* Is the cache data area mapped? */
#define DCR_DATA_IS_MAPPED(cache_ptr)									\
	((((cache_ptr)->cache_access_type == DCR_I_AM_WRITER) ||		\
	((cache_ptr)->record_mmap_ptr != NULL)) ? DCR_TRUE : DCR_FALSE)

	/* Is the specified cache index area mapped? */
#define DCR_INDEX_IS_MAPPED(cache_ptr, index_method)				\
	((((cache_ptr)->cache_access_type == DCR_I_AM_WRITER) ||		\
	((cache_ptr)->index_data_list[(index_method)].mmap_ptr != NULL))	\
	? DCR_TRUE : DCR_FALSE)

	/* Is the specified cache index area mapped? */
#define DCR_BOTH_ARE_MAPPED(cache_ptr, index_method)				\
	((((cache_ptr)->cache_access_type == DCR_I_AM_WRITER) ||		\
	(((cache_ptr)->record_mmap_ptr != NULL) &&								\
	((cache_ptr)->index_data_list[(index_method)].mmap_ptr != NULL)))	\
	? DCR_TRUE : DCR_FALSE)

	/* Get a pointer to the cache header. */
#define DCR_HEADER_AREA_PTR(cache_ptr)									\
	((char *) ((cache_ptr)->mmap_ptr))

	/* Get a pointer to the cache data area. */
#define DCR_DATA_AREA_PTR(cache_ptr)									\
	(((char *) (cache_ptr)->record_mmap_ptr) +								\
	((unsigned int) (cache_ptr)->data_area_offset))

	/* Get a pointer to a cache index area. */
#define DCR_INDEX_AREA_PTR(cache_ptr, index_method)				\
	((char *) ((cache_ptr)->index_data_list[(index_method)].mmap_ptr))

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Primitive data access macros . . .												*/
/*	***********************************************************************	*/

	/* Given a record element, what is the record pointer? */
#define DCR_RELE_TO_RPTR_P(cache_ptr, record_mmap_ptr,					\
	record_element)																			\
	((void *) (((char *) (record_mmap_ptr)) +											\
	DCR_RELE_TO_ROFF_P(cache_ptr, record_element)))

	/* Given a record element, what is the record offset? */
#define DCR_RELE_TO_ROFF_P(cache_ptr, record_element)						\
	(((unsigned int) (cache_ptr)->data_area_offset) +								\
	((record_element) * (cache_ptr)->total_record_size))

	/* Given a record offset, what is the record pointer? */
#define DCR_ROFF_TO_RPTR_P(cache_ptr, record_mmap_ptr,					\
	record_offset)																				\
	((void *) (((char *) (record_mmap_ptr)) +											\
	((unsigned int) (record_offset))))

	/* Given a record offset, what is the record element? */
#define DCR_ROFF_TO_RELE_P(cache_ptr, record_offset) 						\
	(((record_offset) - (cache_ptr)->data_area_offset) /							\
	(cache_ptr)->total_record_size)

	/*	Given an element of an index, get the pointer to the index element. */
#define DCR_IELE_TO_IPTR_P(cache_ptr, index_method, entry_count,		\
	entry_list, index_element) (((char *) (entry_list)) +							\
	(((unsigned int) (index_element)) *													\
	DCR_INDEX_ENTRY_SIZE(cache_ptr, index_method)))

	/* Given an element of an index, what is the record offset? */
#define DCR_IELE_TO_ROFF_P(cache_ptr, index_method, entry_count,		\
	entry_list, index_element)																\
	*((unsigned int *) (DCR_IELE_TO_IPTR_P(cache_ptr, index_method,	\
	record_count, entry_list, index_element) +										\
	DCR_INDEX_REC_OFF(cache_ptr, index_method)))

	/* Given an element of an index, what is the record element? */
#define DCR_IELE_TO_RELE_P(cache_ptr, index_method, entry_count,		\
	entry_list, index_element)																\
	(DCR_ROFF_TO_RELE_P(cache_ptr, DCR_IELE_TO_ROFF_P(cache_ptr,\
	index_method, entry_count, entry_list, index_element)))

	/* Given an element of an index, what is the record pointer? */
#define DCR_IELE_TO_RPTR_P(cache_ptr, index_method, entry_count,		\
	entry_list, index_element,	record_mmap_ptr)										\
	DCR_RELE_TO_RPTR_P(cache_ptr, record_mmap_ptr,							\
	DCR_IELE_TO_RELE_P(cache_ptr, index_method, entry_count,				\
	entry_list, index_element))

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Application-level data access macros . . .									*/
/*	***********************************************************************	*/

	/* Given a record element, what is the record pointer? */
#define DCR_RELE_TO_RPTR(cache_ptr, record_element)						\
	DCR_RELE_TO_RPTR_P(cache_ptr, (cache_ptr)->record_mmap_ptr,			\
	record_element)

	/* Given a record element, what is the record offset? */
#define DCR_RELE_TO_ROFF(cache_ptr, record_element)						\
	DCR_RELE_TO_ROFF_P(cache_ptr, record_element)

	/* Given a record offset, what is the record pointer? */
#define DCR_ROFF_TO_RPTR(cache_ptr, record_offset)							\
	DCR_ROFF_TO_RPTR_P(cache_ptr, (cache_ptr)->record_mmap_ptr,			\
	record_offset)

	/* Given a record offset, what is the record element? */
#define DCR_ROFF_TO_RELE(cache_ptr, record_offset) 						\
	DCR_ROFF_TO_RELE_P(cache_ptr, record_offset)

	/*	Given an element of an index, get the pointer to the index element. */
#define DCR_IELE_TO_IPTR(cache_ptr, index_method, index_element)		\
	DCR_IELE_TO_IPTR_P(cache_ptr, index_method,								\
	(cache_ptr)->record_count,																\
	(cache_ptr)->index_data_list[(index_method)].mmap_ptr, index_element)	\

	/* Given an element of an index, what is the record offset? */
#define DCR_IELE_TO_ROFF(cache_ptr, index_method, index_element)		\
	DCR_IELE_TO_ROFF_P(cache_ptr, index_method,								\
	(cache_ptr)->record_count,																\
	(cache_ptr)->index_data_list[(index_method)].mmap_ptr, index_element)	\

	/* Given an element of an index, what is the record element? */
#define DCR_IELE_TO_RELE(cache_ptr, index_method, index_element)		\
	DCR_IELE_TO_RELE_P(cache_ptr, index_method,								\
	(cache_ptr)->record_count,																\
	(cache_ptr)->index_data_list[(index_method)].mmap_ptr, index_element)	\

	/* Given an element of an index, what is the record pointer? */
#define DCR_IELE_TO_RPTR(cache_ptr, index_method, index_element)		\
	DCR_IELE_TO_RPTR_P(cache_ptr, index_method,								\
	(cache_ptr)->record_count,																\
	(cache_ptr)->index_data_list[(index_method)].mmap_ptr, index_element,	\
	(cache_ptr)->record_mmap_ptr)

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Old-style application-level data access macros . . .						*/
/*	***********************************************************************	*/

	/* Given an element of an index, what is the record offset? */
#define DCR_REC_OFF_FROM_IDX_ELE(cache_ptr, index_method,				\
	index_element)																				\
	DCR_IELE_TO_ROFF(cache_ptr, index_method, index_element)

	/* Given an element of an index, what is the record element? */
#define DCR_REC_ELE_FROM_IDX_ELE(cache_ptr, index_method,				\
	index_element)																				\
	DCR_IELE_TO_RELE(cache_ptr, index_method, index_element)

	/* Given an element of an index, what is the record pointer? */
#define DCR_REC_PTR_FROM_IDX_ELE(cache_ptr, index_method, 				\
	index_element)																				\
	DCR_IELE_TO_RPTR(cache_ptr, index_method, index_element)

	/* Given a record element, what is the record pointer? */
#define DCR_REC_PTR_FROM_REC_ELE(cache_ptr, record_element)				\
	DCR_RELE_TO_RPTR(cache_ptr, record_element)

	/* Given a record offset, what is the record pointer? */
#define DCR_REC_PTR_FROM_REC_OFF(cache_ptr, record_offset)				\
	DCR_ROFF_TO_RPTR(cache_ptr, record_offset)

	/* Given a record offset, what is the record element? */
#define DCR_REC_ELE_FROM_REC_OFF(cache_ptr, record_offset) 				\
	DCR_ROFF_TO_RELE(cache_ptr, record_offset)

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define DCR_OP_READ					0
#define DCR_OP_CREATE				1
#define DCR_OP_RELOAD				2
#define DCR_OP_REFRESH				DCR_OP_RELOAD
#define DCR_OP_UPDATE				4
#define DCR_OP_CREATE_OR_RELOAD	\
	(DCR_OP_CREATE | DCR_OP_RELOAD)
#define DCR_OP_CREATE_OR_REFRESH	\
	(DCR_OP_CREATE | DCR_OP_REFRESH)
#define DCR_OP_CREATE_OR_UPDATE	\
	(DCR_OP_CREATE | DCR_OP_UPDATE)

#define DCR_OP_DEFAULT				DCR_OP_CREATE

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

typedef struct {
	unsigned int  count;
	unsigned int  item_size;
	unsigned long offset;
	unsigned long actual_size;
	unsigned long total_size;
} DCR_AREA;

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

typedef struct {
	struct timeval last_start;
	struct timeval last_end;
	struct timeval last_interval;
	unsigned long  last_count;
	unsigned long  total_count;
	struct timeval total_interval;
} DCR_STAT;

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

typedef struct {
	char         logical_name[DCR_MAX_LOGICAL_NAME + 1];
	int          primitive_type_count;
	char         primitive_type_spec[DCR_MAX_TYPE_SPEC + 1];
	int          db_table_order;
	char         field_name[DCR_MAX_FIELD_NAME + 1];
	char         db_column_name[DCR_MAX_COLUMN_NAME + 1];
	long         db_type;
	unsigned int primitive_list_index;
	unsigned int primitive_list_count;
	unsigned int data_offset;
	unsigned int data_length;
} DCR_FIELD;

typedef struct {
	char         field_name[DCR_MAX_FIELD_NAME + 1];
	unsigned int field_number;
} DCR_FIELD_NAME;

typedef struct {
	char         column_name[DCR_MAX_COLUMN_NAME + 1];
	unsigned int field_number;
} DCR_COLUMN_NAME;

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

typedef struct {
	char           index_name[DCR_MAX_INDEX_NAME + 1];
	unsigned int   field_count;
	unsigned int   field_index;
	unsigned int   record_align_count;
	unsigned int   record_align_index;
	unsigned int   index_align_count;
	unsigned int   index_align_index;
	unsigned int   index_entry_size;
	unsigned int   index_pointer_offset;
	unsigned long  index_area_offset;
	unsigned long  actual_index_area_size;
	unsigned long  index_area_size;
	unsigned long  tmp_index_area_offset;
	unsigned long  tmp_actual_index_area_size;
	unsigned long  tmp_index_area_size;
	DCR_STAT index_stat;
	DCR_STAT sort_stat;
} DCR_INDEX;

typedef struct {
	char         index_name[DCR_MAX_INDEX_NAME + 1];
	unsigned int index_number;
} DCR_INDEX_NAME;

typedef struct {
	GEN_ALIGN_CMP  record_align_cmp_data;
	GEN_ALIGN_CMP  index_align_cmp_data;
	GEN_ALIGN_CMP *record_align_cmp_ptr;
	GEN_ALIGN_CMP *index_align_cmp_ptr;
	unsigned long  index_entry_offset;
	unsigned long  index_entry_size;
	void          *index_entry_list;
	unsigned int   search_index;
	unsigned int   search_count;
	unsigned int   mmap_size;
	void          *mmap_ptr;
} DCR_INDEX_DATA;

typedef struct {
	unsigned int  index_element;
	unsigned long index_record_ptr;
} DCR_INDEX_LOCATION;

typedef struct {
	unsigned int  index_method;
	unsigned int  field_count;
	int           ignore_case_flag;
	GEN_ALIGN_CMP record_cmp;
	GEN_ALIGN_CMP index_cmp;
} DCR_INDEX_KEY;

typedef struct {
	unsigned int key_index;
	unsigned int key_count;
} DCR_KEY_COUNT;

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

typedef struct {
	char           cache_name[DCR_MAX_CACHE_NAME + 1];
	unsigned long  cache_check_sum;
	unsigned long  cache_version;
	unsigned int   cache_writer_pid;
	unsigned char  cache_writer_ip_address[4];
	struct timeval cache_creation_time;
	unsigned long  cache_status;
	DCR_LOCK			cache_lock_status;
	int            indirect_index_flag;
	unsigned int   max_entry_length;
	unsigned int   initial_allocation_size;
	unsigned int   allocation_size;
	unsigned int   max_records_in_cache;
	unsigned int   record_count;
	unsigned int   allocated_record_count;
	unsigned int   actual_data_record_size;
	unsigned int   data_record_size;
	unsigned int   total_record_size;
	unsigned int   allocation_granularity;
	char           db_spec_string[DCR_MAX_DB_SPEC_STRING + 1];
	char           server_name[DCR_MAX_SERVER_NAME + 1];
	char           database_name[DCR_MAX_DATABASE_NAME + 1];
	char           owner_name[DCR_MAX_OWNER_NAME + 1];
	char           table_name[DCR_MAX_TABLE_NAME + 1];
	char           db_user_name[DCR_MAX_USER_NAME + 1];
	char           db_pass_word[DCR_MAX_PASS_WORD + 1];
	unsigned long  basic_header_area_size;
	unsigned long  header_area_size;
	unsigned long  data_area_offset;
	unsigned long  data_area_size;
	unsigned long  index_area_offset;
	unsigned long  index_area_size;
	unsigned long  total_cache_size;
	unsigned long  total_used_cache_size;
	DCR_STAT stat_list[DCR_STAT_COUNT];
	DCR_AREA area_list[DCR_AREA_COUNT];
	unsigned long  cache_signature;
} DCR_HEADER;

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

typedef struct tag_DCR_CACHE {
	char                          *cache_file_name;
	unsigned int                   cache_index;
	unsigned long                  cache_access_type;
	int                            file_handle;
	int                            open_flag;
	unsigned long                  mmap_size;
	volatile void                 *mmap_ptr;
	int                            mmap_prot;
	int                            mmap_flag;
	unsigned int                   cache_block_size;
	MFILE                         *reload_mfile_ptr;
	unsigned int                   cycle_retry_count;
	unsigned int                   cycle_retry_time_out;
	unsigned int                   lock_retry_count;
	unsigned int                   lock_retry_time_out;
	unsigned int                   current_index_method;
	unsigned int                   record_count;
	unsigned int                   allocated_record_count;
	unsigned int                   actual_data_record_size;
	unsigned int                   data_record_size;
	unsigned int                   total_record_size;
	unsigned int                   basic_header_area_size;
	unsigned int                   header_area_size;
	unsigned long                  data_area_offset;
	unsigned long                  data_area_size;
	void                          *data_area_ptr;
	unsigned long                  index_area_offset;
	unsigned long                  index_area_size;
	void                          *index_area_ptr;
	unsigned long                  total_cache_size;
	unsigned long                  total_used_cache_size;
	unsigned int                   record_mmap_size;
	void                          *record_mmap_ptr;
	unsigned int                   field_count;
	DCR_FIELD               *field_list;
	unsigned int                   field_name_count;
	DCR_FIELD_NAME          *field_name_list;
	unsigned int                   column_name_count;
	DCR_COLUMN_NAME         *column_name_list;
	unsigned int                   field_align_count;
	GEN_ALIGN                     *field_align_list;
	unsigned int                   index_count;
	DCR_INDEX               *index_list;
	unsigned int                   index_name_count;
	DCR_INDEX_NAME          *index_name_list;
	unsigned int                   index_field_count;
	unsigned int                  *index_field_list;
	unsigned int                   index_align_count;
	GEN_ALIGN                     *index_align_list;
	unsigned int                   index_data_count;
	DCR_INDEX_DATA          *index_data_list;
	DCR_INDEX_LOCATION		*index_location_list;
	unsigned int                   index_key_count;
	DCR_INDEX_KEY           *index_key_list;
	unsigned int                   field_member_count;
	GEN_MEMBER              *field_member_list;
	unsigned int                   current_field_member_count;
	GEN_MEMBER              *current_field_member_list;
	void                          *search_record_buffer;
	void                          *found_record_buffer;
	void                          *embedded_index_buffer;
	char                          *sql_where_clause;
	char                          *sql_group_by_clause;
	char                          *sql_order_by_clause;
	int                            max_update_date_known;
	char                           update_date_field_name
												[DCR_MAX_FIELD_NAME + 1];
	unsigned int                   update_date_field_index;
	unsigned int                   update_date_field_offset;
	unsigned int                   max_update_date_record;
	DTIME                          max_update_date;
	DTIME                          old_max_update_date;
	unsigned int                   last_search_update_count;
	unsigned int                   last_search_insert_count;
	unsigned long                  call_back_mask;
#ifndef NARGS
	int                          (*call_back_function)
		(struct tag_DCR_CACHE *cache_ptr, unsigned long call_back_type,
		int post_operation_flag, unsigned int index_method, int operation_flags,
		unsigned int operation_count, void *operation_ptr,
		DCR_STAT *stat_ptr, int return_code, char *error_text);
#else
	int                          (*call_back_function)();
#endif /* #ifndef NARGS */
#ifndef NARGS
	int                          (*critical_call_back_function)
		(struct tag_DCR_CACHE *cache_ptr, unsigned long call_back_type,
		int post_operation_flag, int operation_flags,
		unsigned int operation_count, void *operation_ptr, int return_code,
		char *error_text);
#else
	int                          (*critical_call_back_function)();
#endif /* #ifndef NARGS */
	void                          *user_data_ptr_list[
		DCR_USER_DATA_PTR_COUNT];
	struct tag_DCR_CONTROL  *control_ptr;
	volatile DCR_HEADER     *header_ptr;
	DCR_HEADER              *saved_header_ptr;
	DCR_HEADER              *tmp_saved_header_ptr;
} DCR_CACHE;

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

typedef struct {
	struct timeval  last_access;
	DCR_CACHE      *cache_ptr;
} DCR_USAGE;

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

typedef struct tag_DCR_CONTROL {
	unsigned int      high_water_mark;
	unsigned int      allocation_granularity;
	unsigned int      allocated_cache_count;
	unsigned int      active_cache_count;
	DCR_CACHE       **cache_list;
	DCR_USAGE  *usage_list;
} DCR_CONTROL;

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#ifndef NARGS
#else
#endif /* #ifndef NARGS */

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
#ifndef NARGS
unsigned int  DCR_GetIndexStringLen(DCR_CACHE *cache_ptr,
	unsigned int index_method);
unsigned int  DCR_GetMaxIndexStringLen(DCR_CACHE *cache_ptr,
	unsigned int index_method);
char         *DCR_GetIndexString(DCR_CACHE *cache_ptr,
	unsigned int index_method, char *index_string);
#else
unsigned int  DCR_GetIndexStringLen();
unsigned int  DCR_GetMaxIndexStringLen();
char         *DCR_GetIndexString();
#endif /* #ifndef NARGS */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		These functions may be called only by the cache writer . . .	*/
	/*	*****************************************************************	*/
#ifndef NARGS
void DCR_IndexCache(DCR_CACHE *cache_ptr);
void DCR_IndexEmbedded(DCR_CACHE *cache_ptr, unsigned int index_method,
	void *entry_list);
void DCR_IndexIndirect(DCR_CACHE *cache_ptr, unsigned int index_method,
	void *entry_list);
int  DCR_IndexEntryLocate(DCR_CACHE *cache_ptr,
	unsigned int index_method, unsigned int entry_count,
	const void *entry_list, char *error_text);
void DCR_Sort(DCR_CACHE *cache_ptr, unsigned int index_method,
	unsigned int entry_count, void *entry_list);
void DCR_SortEmbedded(DCR_CACHE *cache_ptr, unsigned int index_method,
	unsigned int entry_count, void *entry_list);
void DCR_SortIndirect(DCR_CACHE *cache_ptr, unsigned int index_method,
	unsigned int entry_count, void *entry_list);
#else
void DCR_IndexCache();
void DCR_IndexEmbedded();
void DCR_IndexIndirect();
int  DCR_IndexEntryLocate();
void DCR_Sort();
void DCR_SortEmbedded();
void DCR_SortIndirect();
#endif /* #ifndef NARGS */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
#ifndef NARGS
int  DCR_CheckIndices(DCR_CACHE *cache_ptr, char *error_text);
int  DCR_CheckEmbedded(DCR_CACHE *cache_ptr, unsigned int index_method,
	unsigned int entry_count, const void *entry_list, char *error_text);
int  DCR_CheckIndirect(DCR_CACHE *cache_ptr, unsigned int index_method,
	unsigned int entry_count, const void *entry_list, char *error_text);
int  DCR_CheckIndicesElements(DCR_CACHE *cache_ptr, char *error_text);
int  DCR_CheckEmbeddedElements(DCR_CACHE *cache_ptr,
	unsigned int index_method, unsigned int entry_count,
	const void *entry_list, unsigned int *element_list, char *error_text);
int  DCR_CheckIndirectElements(DCR_CACHE *cache_ptr,
	unsigned int index_method, unsigned int entry_count,
	const void *entry_list,  unsigned int *element_list, char *error_text);
void DCR_CopyEmbedded(DCR_CACHE *cache_ptr, unsigned int index_method,
	unsigned long, const char *record_ptr, char *index_ptr);
#else
int  DCR_CheckIndices();
int  DCR_CheckEmbedded();
int  DCR_CheckIndirect();
int  DCR_CheckIndicesElements();
int  DCR_CheckEmbeddedElements();
int  DCR_CheckIndirectElements();
void DCR_CopyEmbedded();
#endif /* #ifndef NARGS */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Functions for getting cached data.										*/
	/*	*****************************************************************	*/
#ifndef NARGS
int DCR_GetRelation(DCR_CACHE *cache_ptr, unsigned int index_method,
	GEN_ALIGN_CMP *record_align_cmp_ptr, GEN_ALIGN_CMP *index_align_cmp_ptr,
	unsigned int compare_type, int compare_anchor, int record_search_flag,
	const void *in_record_ptr, int *found_flag,
	unsigned int *out_index_element, unsigned int *out_record_element,
	char *error_text);
int DCR_GetCount(DCR_CACHE *cache_ptr, unsigned int index_method,
	GEN_ALIGN_CMP *record_align_cmp_ptr, GEN_ALIGN_CMP *index_align_cmp_ptr,
	unsigned int compare_type, int compare_anchor, int record_search_flag,
	const void *in_record_ptr, unsigned int *out_count,
	unsigned int *out_index_element, unsigned int *out_record_element,
	char *error_text);
int DCR_GetDirect(DCR_CACHE *cache_ptr, unsigned long record_offset,
	char *error_text);
int DCR_GetEQ(DCR_CACHE *cache_ptr, unsigned int index_method,
	GEN_ALIGN_CMP *record_align_cmp_ptr, GEN_ALIGN_CMP *index_align_cmp_ptr,
	int compare_anchor, int record_search_flag, const void *in_record_ptr,
	int *found_flag, unsigned int *out_index_element,
	unsigned int *out_record_element, char *error_text);
int DCR_GetGT(DCR_CACHE *cache_ptr, unsigned int index_method,
	GEN_ALIGN_CMP *record_align_cmp_ptr, GEN_ALIGN_CMP *index_align_cmp_ptr,
	int compare_anchor, int record_search_flag, const void *in_record_ptr,
	int *found_flag, unsigned int *out_index_element,
	unsigned int *out_record_element, char *error_text);
int DCR_GetGE(DCR_CACHE *cache_ptr, unsigned int index_method,
	GEN_ALIGN_CMP *record_align_cmp_ptr, GEN_ALIGN_CMP *index_align_cmp_ptr,
	int compare_anchor, int record_search_flag, const void *in_record_ptr,
	int *found_flag, unsigned int *out_index_element,
	unsigned int *out_record_element, char *error_text);
int DCR_GetHighest(DCR_CACHE *cache_ptr, unsigned int index_method,
	int record_search_flag, int *found_flag, unsigned int *out_index_element,
	unsigned int *out_record_element, char *error_text);
int DCR_GetLT(DCR_CACHE *cache_ptr, unsigned int index_method,
	GEN_ALIGN_CMP *record_align_cmp_ptr, GEN_ALIGN_CMP *index_align_cmp_ptr,
	int compare_anchor, int record_search_flag, const void *in_record_ptr,
	int *found_flag, unsigned int *out_index_element,
	unsigned int *out_record_element, char *error_text);
int DCR_GetLE(DCR_CACHE *cache_ptr, unsigned int index_method,
	GEN_ALIGN_CMP *record_align_cmp_ptr, GEN_ALIGN_CMP *index_align_cmp_ptr,
	int compare_anchor, int record_search_flag, const void *in_record_ptr,
	int *found_flag, unsigned int *out_index_element,
	unsigned int *out_record_element, char *error_text);
int DCR_GetList(DCR_CACHE *cache_ptr, unsigned int index_method,
	GEN_ALIGN_CMP *record_align_cmp_ptr, GEN_ALIGN_CMP *index_align_cmp_ptr,
	unsigned int compare_type, int record_search_flag,
	const void *in_record_ptr, unsigned int max_record_count,
	unsigned int *out_count, void **out_list, char *error_text);
int DCR_GetListFull(DCR_CACHE *cache_ptr, unsigned int index_method,
	GEN_ALIGN_CMP *record_align_cmp_ptr, GEN_ALIGN_CMP *index_align_cmp_ptr,
	unsigned int compare_type, int record_search_flag,
	const void *in_record_ptr, unsigned int max_record_count,
	unsigned int *out_count, void **out_list, char *error_text);
int DCR_GetListElement(DCR_CACHE *cache_ptr, unsigned int index_method,
	GEN_ALIGN_CMP *record_align_cmp_ptr, GEN_ALIGN_CMP *index_align_cmp_ptr,
	unsigned int compare_type, int record_search_flag,
	const void *in_record_ptr, unsigned int max_record_count,
	unsigned int *out_count, unsigned int **out_list, char *error_text);
int DCR_GetListOffset(DCR_CACHE *cache_ptr, unsigned int index_method,
	GEN_ALIGN_CMP *record_align_cmp_ptr, GEN_ALIGN_CMP *index_align_cmp_ptr,
	unsigned int compare_type, int record_search_flag,
	const void *in_record_ptr, unsigned int max_record_count,
	unsigned int *out_count, unsigned long **out_list, char *error_text);
int DCR_GetListPointer(DCR_CACHE *cache_ptr, unsigned int index_method,
	GEN_ALIGN_CMP *record_align_cmp_ptr, GEN_ALIGN_CMP *index_align_cmp_ptr,
	unsigned int compare_type, int record_search_flag,
	const void *in_record_ptr, unsigned int max_record_count,
	unsigned int *out_count, void ***out_list, char *error_text);
int DCR_GetLowest(DCR_CACHE *cache_ptr, unsigned int index_method,
	int record_search_flag, int *found_flag, unsigned int *out_index_element,
	unsigned int *out_record_element, char *error_text);
int DCR_GetNE(DCR_CACHE *cache_ptr, unsigned int index_method,
	GEN_ALIGN_CMP *record_align_cmp_ptr, GEN_ALIGN_CMP *index_align_cmp_ptr,
	int compare_anchor, int record_search_flag, const void *in_record_ptr,
	int *found_flag, unsigned int *out_index_element,
	unsigned int *out_record_element, char *error_text);
int DCR_GetNext(DCR_CACHE *cache_ptr, unsigned int index_method,
	int record_search_flag, int *found_flag, unsigned int *out_index_element,
	unsigned int *out_record_element, char *error_text);
int DCR_GetPosition(DCR_CACHE *cache_ptr, unsigned int index_method,
	unsigned int *out_index_element, unsigned int *out_record_element,
	char *error_text);
int DCR_GetPrevious(DCR_CACHE *cache_ptr, unsigned int index_method,
	int record_search_flag, int *found_flag, unsigned int *out_index_element,
	unsigned int *out_record_element, char *error_text);
#else
int DCR_GetRelation();
int DCR_GetCount();
int DCR_GetDirect();
int DCR_GetEQ();
int DCR_GetGT();
int DCR_GetGE();
int DCR_GetHighest();
int DCR_GetLT();
int DCR_GetLE();
int DCR_GetList();
int DCR_GetListFull();
int DCR_GetListElement();
int DCR_GetListOffset();
int DCR_GetListPointer();
int DCR_GetLowest();
int DCR_GetNE();
int DCR_GetNext();
int DCR_GetPosition();
int DCR_GetPrevious();
#endif /* #ifndef NARGS */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Basic functions for getting cached data.								*/
	/*	*****************************************************************	*/
#ifndef NARGS
unsigned int DCR_BasicGetCount(DCR_CACHE *cache_ptr,
	unsigned int index_method, GEN_ALIGN_CMP *record_align_cmp_ptr,
	GEN_ALIGN_CMP *index_align_cmp_ptr, unsigned int compare_type,
	int compare_anchor, int record_search_flag, unsigned int entry_count,
	const void *entry_list, const void *in_record_ptr,
	unsigned int *out_index_element, unsigned int *out_record_element);
void         DCR_BasicGetHighest(DCR_CACHE *cache_ptr,
	unsigned int index_method, int record_search_flag,
	unsigned int entry_count, const void *entry_list, int *found_flag,
	unsigned int *out_index_element, unsigned int *out_record_element);
int          DCR_BasicGetList(DCR_CACHE *cache_ptr,
	unsigned int index_method, GEN_ALIGN_CMP *record_align_cmp_ptr,
	GEN_ALIGN_CMP *index_align_cmp_ptr, unsigned int compare_type,
	int record_search_flag, unsigned int entry_count, const void *entry_list,
	int record_list_type, const void *in_record_ptr,
	unsigned int max_record_count, unsigned int *out_count, void **out_list,
	char *error_text);
void         DCR_BasicGetLowest(DCR_CACHE *cache_ptr,
	unsigned int index_method, int record_search_flag,
	unsigned int entry_count, const void *entry_list, int *found_flag,
	unsigned int *out_index_element, unsigned int *out_record_element);
int          DCR_BasicGetNext(DCR_CACHE *cache_ptr,
	unsigned int index_method, int record_search_flag,
	unsigned int entry_count, const void *entry_list, int *found_flag,
	unsigned int *out_index_element, unsigned int *out_record_element,
	char *error_text);
int          DCR_BasicGetPosition(DCR_CACHE *cache_ptr,
	unsigned int index_method, unsigned int entry_count,
	const void *entry_list, unsigned int *out_index_element,
	unsigned int *out_record_element, char *error_text);
int          DCR_BasicGetPrevious(DCR_CACHE *cache_ptr,
	unsigned int index_method, int record_search_flag,
	unsigned int entry_count, const void *entry_list, int *found_flag,
	unsigned int *out_index_element, unsigned int *out_record_element,
	char *error_text);
#else
unsigned int DCR_BasicGetCount();
void         DCR_BasicGetHighest();
int          DCR_BasicGetList();
void         DCR_BasicGetLowest();
int          DCR_BasicGetNext();
int          DCR_BasicGetPosition();
int          DCR_BasicGetPrevious();
#endif /* #ifndef NARGS */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Finds a record unique on all cache indices . . .					*/
	/*	*****************************************************************	*/
#ifndef NARGS
int DCR_DeleteFromIndex(DCR_CACHE *cache_ptr, unsigned int index_method,
	unsigned int index_element, char *error_text);
int DCR_DeleteFromIndices(DCR_CACHE *cache_ptr,
	const unsigned int *index_element_list, char *error_text);
int DCR_FindRecordUnique(DCR_CACHE *cache_ptr,
	const void *in_record_ptr, int *found_flag,
	unsigned int *out_record_element, unsigned long *out_record_offset,
	char *error_text);
int DCR_GetUniqueKeys(DCR_CACHE *cache_ptr, unsigned int index_method,
	GEN_ALIGN_CMP *record_cmp_ptr, GEN_ALIGN_CMP *index_cmp_ptr,
	unsigned int alloc_granularity, unsigned int *unique_key_count,
	DCR_KEY_COUNT **unique_key_list, char *error_text);
#else
int DCR_DeleteFromIndex();
int DCR_DeleteFromIndices();
int DCR_FindRecordUnique();
int DCR_GetUniqueKeys();
#endif /* #ifndef NARGS */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Functions for locating cached data.										*/
	/*	*****************************************************************	*/
#ifndef NARGS
int DCR_Find(DCR_CACHE *cache_ptr, unsigned int index_method,
	GEN_ALIGN_CMP *record_align_cmp_ptr, GEN_ALIGN_CMP *index_align_cmp_ptr,
	const void *in_record_ptr, unsigned int entry_count,
	const void *entry_list, int find_anchor, unsigned int *out_index_element,
	unsigned long *out_index_offset, unsigned int *out_record_element,
	unsigned long *out_record_offset);
int DCR_FindEmbedded(DCR_CACHE *cache_ptr, unsigned int index_method,
	GEN_ALIGN_CMP *record_align_cmp_ptr, GEN_ALIGN_CMP *index_align_cmp_ptr,
	const void *in_record_ptr, unsigned int entry_count,
	const void *entry_list, int find_anchor, unsigned int *out_index_element,
	unsigned long *out_index_offset, unsigned int *out_record_element,
	unsigned long *out_record_offset);
int DCR_FindIndirect(DCR_CACHE *cache_ptr, unsigned int index_method,
	GEN_ALIGN_CMP *record_align_cmp_ptr, GEN_ALIGN_CMP *index_align_cmp_ptr,
	const void *in_record_ptr, unsigned int entry_count,
	const void *entry_list, int find_anchor, unsigned int *out_index_element,
	unsigned long *out_index_offset, unsigned int *out_record_element,
	unsigned long *out_record_offset);
#else
int DCR_Find();
int DCR_FindEmbedded();
int DCR_FindIndirect();
#endif /* #ifndef NARGS */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
#ifndef NARGS
int DCR_CompareRecords(DCR_CACHE *cache_ptr, const void *record_ptr_1,
	const void *record_ptr_2);
int DCR_FindRELEInIndices(DCR_CACHE *cache_ptr,
	unsigned int record_element, unsigned int *index_element_list,
	char *error_text);
int DCR_FindRPTRInIndices(DCR_CACHE *cache_ptr,
	unsigned int *record_element, const void *record_ptr,
	unsigned int *index_element_list, char *error_text);
#else
int DCR_CompareRecords();
int DCR_FindRELEInIndices();
int DCR_FindRPTRInIndices();
#endif /* #ifndef NARGS */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
#ifndef NARGS
int  DCR_DeleteRecordByElement(DCR_CACHE *cache_ptr,
	unsigned int record_element, char *error_text);
int  DCR_DeleteRecordByOffset(DCR_CACHE *cache_ptr,
	unsigned long record_offset, char *error_text);
int  DCR_DeleteRecordByKey(DCR_CACHE *cache_ptr,
	unsigned int index_method, GEN_ALIGN_CMP *record_align_cmp_ptr,
	GEN_ALIGN_CMP *index_align_cmp_ptr, unsigned int compare_type,
	const void *in_record_ptr, unsigned int max_record_count,
	unsigned int *deleted_count, char *error_text);
int  DCR_InsertRecord(DCR_CACHE *cache_ptr, const void *in_record_ptr,
	unsigned int *out_record_element, unsigned long *out_record_offset,
	char *error_text);
int  DCR_InsertBulk(DCR_CACHE *cache_ptr, unsigned int in_record_count,
	const void *in_record_list, unsigned int in_record_size, char *error_text);
int  DCR_InsListControl(DCR_CACHE *cache_ptr, int insert_method,
	unsigned int in_record_count, const void *in_record_list,
	unsigned int in_record_size, int assign_ins_list_flag,
	unsigned int ins_count, DCR_INS_2 *ins_list, char *error_text);
int  DCR_InsListAllocFull(DCR_CACHE *cache_ptr,
	unsigned int in_record_count, const void *in_record_list,
	unsigned int ins_count, const DCR_INS_2 *ins_list, char *error_text);
int  DCR_InsListAllocPart(DCR_CACHE *cache_ptr,
	unsigned int in_record_count, const void *in_record_list,
	unsigned int ins_count, const DCR_INS_2 *ins_list, char *error_text);
int  DCR_InsListAllocNone(DCR_CACHE *cache_ptr,
	unsigned int in_record_count, const void *in_record_list,
	unsigned int ins_count, const DCR_INS_2 *ins_list, char *error_text);
int  DCR_SearchRecord(DCR_CACHE *cache_ptr, const void *in_record_ptr,
	unsigned int *out_record_element, unsigned long *out_record_offset,
	char *error_text);
int  DCR_SearchBulk(DCR_CACHE *cache_ptr, unsigned int in_record_count,
	const void *in_record_list, unsigned int in_record_size,
	unsigned int *update_count, unsigned int *insert_count, char *error_text);
int  DCR_SearchBulkBasic(DCR_CACHE *cache_ptr, int insert_method,
	unsigned int in_record_count, const void *in_record_list,
	unsigned int in_record_size, unsigned int *update_count,
	unsigned int *insert_count, char *error_text);
void DCR_SortOne_INS_1(DCR_CACHE *cache_ptr, unsigned int index_method,
	unsigned int ins_count, DCR_INS_1 *ins_list);
void DCR_SortAll_INS_2(DCR_CACHE *cache_ptr,
	unsigned int in_record_count, unsigned int ins_count,
	DCR_INS_2 *ins_list);
void DCR_SortOne_INS_2(DCR_CACHE *cache_ptr, unsigned int index_method,
	unsigned int ins_count, DCR_INS_2 *ins_list);
int  DCR_UpdateRecord(DCR_CACHE *cache_ptr, unsigned int record_element,
	const void *new_record_ptr, char *error_text);
#else
int  DCR_DeleteRecordByElement();
int  DCR_DeleteRecordByOffset();
int  DCR_DeleteRecordByKey();
int  DCR_InsertRecord();
int  DCR_InsertBulk();
int  DCR_InsListControl();
int  DCR_InsListAllocFull();
int  DCR_InsListAllocPart();
int  DCR_InsListAllocNone();
int  DCR_SearchRecord();
int  DCR_SearchBulk();
int  DCR_SearchBulkBasic();
void DCR_SortOne_INS_1();
void DCR_SortAll_INS_2();
void DCR_SortOne_INS_2();
int  DCR_UpdateRecord();
#endif /* #ifndef NARGS */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Manage cache index key lists . . .										*/
	/*	*****************************************************************	*/
#ifndef NARGS
int                  DCR_AddIndexKeyList(DCR_CACHE *cache_ptr,
	unsigned int in_index_key_count,
	const DCR_INDEX_KEY *in_index_key_list, char *error_text);
int                  DCR_CopyIndexKeyList(
	unsigned int in_index_key_count,
	const DCR_INDEX_KEY *in_index_key_list,
	unsigned int *out_index_key_count,
	DCR_INDEX_KEY **out_index_key_list, char *error_text);
void                 DCR_FreeCacheIndexKeyList(DCR_CACHE *cache_ptr);
void                 DCR_FreeIndexKeyList(unsigned int index_key_count,
	DCR_INDEX_KEY *index_key_list);
DCR_INDEX_KEY *DCR_GetIndexKeyPtr(const DCR_CACHE *cache_ptr,
   unsigned int index_key_element);
#else
int                  DCR_AddIndexKeyList();
int                  DCR_CopyIndexKeyList();
void                 DCR_FreeCacheIndexKeyList();
void                 DCR_FreeIndexKeyList();
DCR_INDEX_KEY *DCR_GetIndexKeyPtr();
#endif /* #ifndef NARGS */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Cache open functions . . .													*/
	/*	*****************************************************************	*/
#ifndef NARGS
void DCR_CloseRaw(int *file_handle, volatile void **mmap_ptr,
	unsigned long *mmap_size);
int  DCR_OpenCache(const char *cache_file_name,
	unsigned long cache_access_type, int *open_flag, int *mmap_prot,
	int *mmap_flag, int *file_handle, volatile void **mmap_ptr,
	unsigned long *mmap_size, unsigned int *cache_block_size, int *errno_code,
	int *open_failure_flag, int *mmap_failure_flag, char *error_text);
int  DCR_OpenRaw(const char *cache_file_name, int open_flag,
	int open_mode, int mmap_prot, int mmap_flag, int *file_handle,
	volatile void **mmap_ptr, unsigned long *mmap_size, int *errno_code,
	int *open_failure_flag, int *mmap_failure_flag, char *error_text);
int  DCR_OpenRead(DCR_CONTROL *cache_control_ptr,
	const char *cache_file_name, unsigned int cycle_retry_count,
	unsigned int cycle_retry_time_out, unsigned int lock_retry_count,
	unsigned int lock_retry_time_out, DCR_CACHE **out_cache_ptr,
	unsigned int *out_cache_index, char *error_text);
int  DCR_OpenWrite(DCR_CONTROL *cache_control_ptr,
	const char *cache_file_name, DCR_CACHE **out_cache_ptr,
	unsigned int *out_cache_index, char *error_text);
#else
void DCR_CloseRaw();
int  DCR_OpenCache();
int  DCR_OpenRaw();
int  DCR_OpenRead();
int  DCR_OpenWrite();
#endif /* #ifndef NARGS */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
#ifndef NARGS
int  DCR_MapData(DCR_CACHE *cache_ptr, unsigned int *record_count,
	void **record_list, char *error_text);
int  DCR_MapAllIndices(DCR_CACHE *cache_ptr, char *error_text);
int  DCR_MapIndex(DCR_CACHE *cache_ptr, unsigned int index_method,
	unsigned int *entry_count, void **entry_list, char *error_text);
void DCR_UnMapData(DCR_CACHE *cache_ptr);
int  DCR_UnMapIndex(DCR_CACHE *cache_ptr, unsigned int index_method,
	char *error_text);
void DCR_UnMapAllIndices(DCR_CACHE *cache_ptr);
int  DCR_MapDataAndIndex(DCR_CACHE *cache_ptr,
	unsigned int *record_count, void **record_list, unsigned int index_method,
	unsigned int *entry_count, void **entry_list, char *error_text);
int  DCR_MapDataAndIndices(DCR_CACHE *cache_ptr, char *error_text);
int  DCR_Refresh(DCR_CACHE *cache_ptr, unsigned int *record_count,
	void **record_list, unsigned int index_method, unsigned int *entry_count,
	void **entry_list, char *error_text);
int  DCR_ReMapCache(DCR_CACHE *cache_ptr, char *error_text);
#else
int  DCR_MapData();
int  DCR_MapAllIndices();
int  DCR_MapIndex();
void DCR_UnMapData();
int  DCR_UnMapIndex();
void DCR_UnMapAllIndices();
int  DCR_MapDataAndIndex();
int  DCR_MapDataAndIndices();
int  DCR_Refresh();
int  DCR_ReMapCache();
#endif /* #ifndef NARGS */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Cache close functions . . .												*/
	/*	*****************************************************************	*/
#ifndef NARGS
void DCR_CloseAllCaches(DCR_CONTROL *cache_control_ptr);
void DCR_CloseBasicCache(DCR_CACHE *cache_ptr);
void DCR_CloseOneCache(DCR_CACHE *cache_ptr);
void DCR_FreeBasicCache(DCR_CACHE *cache_ptr);
#else
void DCR_CloseAllCaches();
void DCR_CloseBasicCache();
void DCR_CloseOneCache();
void DCR_FreeBasicCache();
#endif /* #ifndef NARGS */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Emit functions . . .															*/
	/*	*****************************************************************	*/
#ifndef NARGS
int  DCR_EmitBinaryData(DCR_CACHE *cache_ptr, unsigned int index_method,
	int reverse_flag, unsigned int max_records, unsigned int field_spec_count,
	char **field_spec_list, unsigned int *data_line_count,
	int (*output_function)(void *, unsigned int, unsigned int, void *),
	void *output_control, char *error_text);
void DCR_EmitCallBacks(DCR_CACHE *cache_ptr,
	void (*output_function)(void *, char *, ...), void *output_control);
int  DCR_EmitData(DCR_CACHE *cache_ptr, unsigned int index_method,
	int reverse_flag, int header_flag, unsigned int max_records,
	unsigned int lines_per_page, char *inter_field_separator,
	char *intra_field_separator, char *page_separator, char *record_leader,
	char *record_trailer, unsigned int field_spec_count,
	char **field_spec_list, unsigned int *page_count,
	unsigned int *format_line_count, unsigned int *data_line_count,
	void (*output_function)(void *, char *, ...), void *output_control,
	char *error_text);
void DCR_EmitField(DCR_FIELD *field_ptr,
	unsigned int field_align_count, GEN_ALIGN *field_align_list,
	unsigned int data_length_list, unsigned int total_length_list,
	char *intra_field_separator, char *record_ptr,
	void (*output_function)(void *, char *, ...), void *output_control);
void DCR_EmitHeader(DCR_CACHE *cache_ptr,
	DCR_HEADER *cache_header_ptr,
	void (*output_function)(void *, char *, ...), void *output_control);
void DCR_EmitOneStat(DCR_STAT *stat_ptr,
	void (*output_function)(void *, char *, ...), void *output_control);
void DCR_EmitRecord(unsigned int field_count,
	DCR_FIELD *field_list, GEN_ALIGN *field_align_list,
	unsigned int *data_length_list, unsigned int *total_length_list,
	char *inter_field_separator, char *intra_field_separator,
	char *record_ptr, void (*output_function)(void *, char *, ...),
	void *output_control);
void DCR_EmitStats(DCR_CACHE *cache_ptr,
	DCR_HEADER *cache_header_ptr,
	void (*output_function)(void *, char *, ...), void *output_control);
void DCR_EmitString(char *out_string, unsigned int out_count,
	void (*output_function)(void *, char *, ...), void *output_control);
int  DCR_GetEmitControlData(unsigned int field_count,
	DCR_FIELD *field_list, unsigned int field_align_count,
	GEN_ALIGN *field_align_list, int header_flag, char *inter_field_separator,
	char *intra_field_separator, unsigned int *header_length,
	unsigned int *header_count, char ***header_list,
	unsigned int **data_length_list, unsigned int **total_length_list,
	char *error_text);
#else
int  DCR_EmitBinaryData();
void DCR_EmitCallBacks();
int  DCR_EmitData();
void DCR_EmitField();
void DCR_EmitHeader();
void DCR_EmitOneStat();
void DCR_EmitRecord();
void DCR_EmitStats();
void DCR_EmitString();
int  DCR_GetEmitControlData();
#endif /* #ifndef NARGS */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Cache and record lock/unlock functions . . .							*/
	/*	*****************************************************************	*/
#ifndef NARGS
int DCR_LockCache(DCR_CACHE *cache_ptr, unsigned long cache_status,
	char *error_text);
int DCR_LockRecord(DCR_CACHE *cache_ptr, unsigned long record_offset,
	char *error_text);
int DCR_UnLockCache(DCR_CACHE *cache_ptr, char *error_text);
int DCR_UnLockRecord(DCR_CACHE *cache_ptr, unsigned long record_offset,
	char *error_text);
#else
int DCR_LockCache();
int DCR_LockRecord();
int DCR_UnLockCache();
int DCR_UnLockRecord();
#endif /* #ifndef NARGS */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		User data pointer functions . . .										*/
	/*	*****************************************************************	*/
#ifndef NARGS
void  *DCR_GetUserDataPtr(DCR_CACHE *cache_ptr,
	unsigned int user_data_ptr_index);
void **DCR_GetUserDataPtrList(DCR_CACHE *cache_ptr,
	void **user_data_ptr_list);
void  *DCR_SetUserDataPtr(DCR_CACHE *cache_ptr,
	unsigned int user_data_ptr_index, const void *user_data_ptr);
#else
void  *DCR_GetUserDataPtr();
void **DCR_GetUserDataPtrList();
void  *DCR_SetUserDataPtr();
#endif /* #ifndef NARGS */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
#ifndef NARGS
int   DCR_AddACache(DCR_CONTROL *cache_control_ptr,
	const char *cache_file_name, DCR_CACHE *in_cache_ptr,
	DCR_CACHE **out_cache_ptr, unsigned int *out_cache_index,
	char *error_text);
int   DCR_AllocCacheControl(DCR_CONTROL *cache_control_ptr,
	unsigned int allocation_granularity, char *error_text);
int   DCR_AllocCache(DCR_CACHE *cache_ptr,
	DCR_HEADER *cache_header_ptr, char *error_text);
int   DCR_AssertAccessType(const DCR_CACHE *cache_ptr,
	unsigned long cache_access_type, char *error_text);
void  DCR_BindHeader(DCR_CACHE *cache_ptr,
	volatile DCR_HEADER *cache_header_ptr);
void  DCR_BindInit(DCR_CACHE *cache_ptr,
	volatile DCR_HEADER *cache_header_ptr);
int   DCR_CalculateMaxRecords(unsigned long header_area_size,
	unsigned int total_record_size, int indirect_index_flag,
	unsigned int index_count, DCR_INDEX *index_list,
	unsigned int *allocation_size, unsigned int *max_records_in_cache,
	char *error_text);
int   DCR_CalculateSizes(unsigned long total_header_size,
	unsigned int allocation_size, unsigned int max_records_in_cache,
	unsigned int total_record_size, int indirect_index_flag,
	unsigned int index_count, DCR_INDEX *index_list,
	unsigned int *allocation_count, unsigned long *data_area_offset,
	unsigned long *data_area_size, unsigned long *index_area_offset,
	unsigned long *index_area_size, unsigned long *cache_size,
	char *error_text);
int   DCR_CheckHeader(DCR_HEADER *cache_header_ptr,
	unsigned long mmap_file_size, char *error_text);
int   DCR_CheckIndexElement(const DCR_CACHE *cache_ptr,
	unsigned int index_element, char *error_text);
int   DCR_CheckRecordElement(const DCR_CACHE *cache_ptr,
	unsigned int record_element, char *error_text);
int   DCR_CheckRecordOffset(const DCR_CACHE *cache_ptr,
	unsigned long record_offset, char *error_text);
int   DCR_CheckStructList(DCR_CACHE *cache_ptr,
	unsigned int struct_size, unsigned int struct_count,
	GEN_MEMBER *struct_list, char *error_text);
char *DCR_GetAccessTypeName(unsigned long cache_access_type,
	char *cache_access_type_name);
void  DCR_GetAreaCountOffset(unsigned int *area_count_offset);
void  DCR_GetAreaListOffset(unsigned int *area_list_offset);
char *DCR_GetAreaName(int area_type, char *area_type_name);
int   DCR_GetAddedFieldList(unsigned int field_spec_count,
	char **field_spec_list, unsigned int *out_field_count,
	DCR_FIELD **out_field_list, char *error_text);
char *DCR_GetCmpTypeName(unsigned int compare_type, char *compare_type_name);
int   DCR_GetSpecifiedFieldList(unsigned int field_count,
	DCR_FIELD *field_list, unsigned int field_name_count,
	DCR_FIELD_NAME *field_name_list, unsigned int field_spec_count,
	char **field_spec_list, unsigned int *out_field_count,
	DCR_FIELD **out_field_list, char *error_text);
char *DCR_GetStatName(int cache_stat, char *cache_stat_name);
char *DCR_GetStatusName(unsigned long cache_status,
	char *cache_status_name);
char *DCR_GetVersionCache(unsigned long version, char *version_string);
char *DCR_GetVersionLibrary(char *version_string);
int   DCR_IsValidAccessType(unsigned long cache_access_type);
int   DCR_IsValidStatus(unsigned long cache_status);
int   DCR_MakePartialKey(DCR_CACHE *cache_ptr,
	unsigned int index_method, unsigned int field_count,
	GEN_ALIGN_CMP *record_align_cmp_ptr, GEN_ALIGN_CMP *index_align_cmp_ptr,
	char *error_text);
int   DCR_ReSizeCache(DCR_CACHE *cache_ptr,
	unsigned int allocated_record_count, char *error_text);
int   DCR_ValidateCompareType(unsigned int compare_type,
	char *error_text);
int   DCR_ValidateIndexMethod(DCR_CACHE *cache_ptr,
	unsigned int index_method, char *error_text);
int   DCR_ValidateRecSearchFlag(int record_search_flag,
	char *error_text);
#else
int   DCR_AddACache();
int   DCR_AllocCacheControl();
int   DCR_AllocCache();
int   DCR_AssertAccessType();
void  DCR_BindHeader();
void  DCR_BindInit();
int   DCR_CalculateMaxRecords();
int   DCR_CalculateSizes();
int   DCR_CheckHeader();
int   DCR_CheckIndexElement();
int   DCR_CheckRecordElement();
int   DCR_CheckRecordOffset();
int   DCR_CheckStructList();
char *DCR_GetAccessTypeName();
void  DCR_GetAreaCountOffset();
void  DCR_GetAreaListOffset();
char *DCR_GetAreaName();
int   DCR_GetAddedFieldList();
char *DCR_GetCmpTypeName();
int   DCR_GetSpecifiedFieldList();
char *DCR_GetStatName();
char *DCR_GetStatusName();
char *DCR_GetVersionCache();
char *DCR_GetVersionLibrary();
int   DCR_IsValidAccessType();
int   DCR_IsValidStatus();
int   DCR_MakePartialKey();
int   DCR_ReSizeCache();
int   DCR_ValidateCompareType();
int   DCR_ValidateIndexMethod();
int   DCR_ValidateRecSearchFlag();
#endif /* #ifndef NARGS */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
#ifndef NARGS
int DCR_CheckPointBasic(const DCR_CACHE *cache_ptr,
	unsigned long check_point_offset, unsigned long check_point_length,
	int synchronous_flag, char *error_text);
int DCR_CheckPoint(const DCR_CACHE *cache_ptr, int synchronous_flag,
	char *error_text);
int DCR_CheckPointHeader(const DCR_CACHE *cache_ptr,
	int synchronous_flag, char *error_text);
int DCR_CheckPointData(const DCR_CACHE *cache_ptr,
	int synchronous_flag, char *error_text);
int DCR_CheckPointIndices(const DCR_CACHE *cache_ptr,
	int synchronous_flag, char *error_text);
int DCR_CheckPointRecord(const DCR_CACHE *cache_ptr,
	unsigned int record_element, int synchronous_flag, char *error_text);
#else
int DCR_CheckPointBasic();
int DCR_CheckPoint();
int DCR_CheckPointHeader();
int DCR_CheckPointData();
int DCR_CheckPointIndices();
int DCR_CheckPointRecord();
#endif /* #ifndef NARGS */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Functions to support call-backs . . .									*/
	/*	*****************************************************************	*/
#ifndef NARGS
char *DCR_GetCallBackName(unsigned long call_back,
	char *call_back_name);
void  DCR_GetUserCallBack(DCR_CACHE *cache_ptr,
	unsigned long *call_back_mask, int (**call_back_function)(DCR_CACHE *,
	unsigned long, int, unsigned int, int, unsigned int, void *,
	DCR_STAT *stat_ptr, int, char *));
void  DCR_SetUserCallBack(DCR_CACHE *cache_ptr,
	const unsigned long *call_back_mask, int (*call_back_function)(DCR_CACHE *,
	unsigned long, int, unsigned int, int, unsigned int, void *,
	DCR_STAT *stat_ptr, int, char *));
void  DCR_ClearUserCallBack(DCR_CACHE *cache_ptr);
void  DCR_GetCriticalCallBack(DCR_CACHE *cache_ptr,
	int (**critical_call_back_function)(DCR_CACHE *, unsigned long, int, int,
	unsigned int, void *, int, char *));
void  DCR_SetCriticalCallBack(DCR_CACHE *cache_ptr,
	int (*critical_call_back_function)(DCR_CACHE *, unsigned long, int, int,
	unsigned int, void *, int, char *));
#else
char *DCR_GetCallBackName();
void  DCR_GetUserCallBack();
void  DCR_SetUserCallBack();
void  DCR_ClearUserCallBack();
void  DCR_GetCriticalCallBack();
void  DCR_SetCriticalCallBack();
#endif /* #ifndef NARGS */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
#ifndef NARGS
int DCR_ClearSQLGroupByClause(DCR_CACHE *cache_ptr, char *error_text);
int DCR_ClearSQLOrderByClause(DCR_CACHE *cache_ptr, char *error_text);
int DCR_ClearSQLWhereClause(DCR_CACHE *cache_ptr, char *error_text);
int DCR_SetSQLGroupByClause(DCR_CACHE *cache_ptr,
   const char *sql_group_by_clause, char *error_text);
int DCR_SetSQLOrderByClause(DCR_CACHE *cache_ptr,
   const char *sql_order_by_clause, char *error_text);
int DCR_SetSQLWhereClause(DCR_CACHE *cache_ptr,
   const char *sql_where_clause, char *error_text);
#else
int DCR_ClearSQLGroupByClause();
int DCR_ClearSQLOrderByClause();
int DCR_ClearSQLWhereClause();
int DCR_SetSQLGroupByClause();
int DCR_SetSQLOrderByClause();
int DCR_SetSQLWhereClause();
#endif /* #ifndef NARGS */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
#ifndef NARGS
void DCR_ClearMaxUpdateDate(DCR_CACHE *cache_ptr);
int  DCR_FindMaxUpdateDate(DCR_CACHE *cache_ptr,
   const char *update_date_field_name, unsigned int *update_date_field_index,
   unsigned int *update_date_field_offset,
	unsigned int *max_update_date_record, DTIME *max_update_date,
	char *error_text);
int  DCR_GetMaxUpdateDate(DCR_CACHE *cache_ptr,
	const char *update_date_field_name, DTIME *max_update_date,
	char *error_text);
int  DCR_HasUpdateDate(DCR_CACHE *cache_ptr,
	const char *update_date_field_name);
int  DCR_SetMaxUpdateDate(DCR_CACHE *cache_ptr,
   unsigned int max_update_date_record, const DTIME *max_update_date,
   char *error_text);
#else
void DCR_ClearMaxUpdateDate();
int  DCR_FindMaxUpdateDate();
int  DCR_GetMaxUpdateDate();
int  DCR_HasUpdateDate();
int  DCR_SetMaxUpdateDate();
#endif /* #ifndef NARGS */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
#ifndef NARGS
int DCR_BARG_AddedFields(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr,
	unsigned int *added_field_count, char ***added_field_list, int *error_code,
	char *error_text);
int DCR_BARG_Alloc(const char *in_arg_ptr, unsigned int *in_arg_length,
	char **in_data_ptr, unsigned int *allocation_size, int *error_code,
	char *error_text);
int DCR_BARG_CacheFile(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, char **cache_file_name,
	int *error_code, char *error_text);
int DCR_BARG_CacheName(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, char **cache_name,
	int *error_code, char *error_text);
int DCR_BARG_ClearAddedFields(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr,
	unsigned int *added_field_count, char ***added_field_list, int *error_code,
	char *error_text);
int DCR_BARG_ClearIndexSpec(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr,
	unsigned int *index_spec_count, char ***index_spec_list, int *error_code,
	char *error_text);
int DCR_BARG_DBDatabaseName(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, char **db_database_name,
	int *error_code, char *error_text);
int DCR_BARG_DBLoadGran(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr,
	unsigned int *db_load_granularity, int *error_code, char *error_text);
int DCR_BARG_DBOwnerName(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, char **db_owner_name,
	int *error_code, char *error_text);
int DCR_BARG_DBPassword(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, char **db_pass_word,
	int *error_code, char *error_text);
int DCR_BARG_DBTableName(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, char **db_table_name,
	int *error_code, char *error_text);
int DCR_BARG_DBUserName(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, char **db_user_name,
	int *error_code, char *error_text);
int DCR_BARG_IndexSpec(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr,
	unsigned int *index_spec_count, char ***index_spec_list, int *error_code,
	char *error_text);
int DCR_BARG_IndexType(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, int *indirect_index_flag,
	int *error_code, char *error_text);
int DCR_BARG_IndirectIndex(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, int *indirect_index_flag,
	int *error_code, char *error_text);
int DCR_BARG_InitialAlloc(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr,
	unsigned int *initial_allocation_size, int *error_code, char *error_text);
int DCR_BARG_LoadFromDB(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, int *load_data_flag,
	int *error_code, char *error_text);
int DCR_BARG_MaxRows(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr,
	unsigned int *maximum_row_count, int *error_code, char *error_text);
int DCR_BARG_OperationMode(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, int *operating_mode,
	int *error_code, char *error_text);
int DCR_BARG_RefreshSeconds(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr,
	unsigned long *refresh_seconds, int *error_code, char *error_text);
int DCR_BARG_SQLGroupBy(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr,
	char **sql_group_by_clause, int *error_code, char *error_text);
int DCR_BARG_SQLOrderBy(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr,
	char **sql_order_by_clause, int *error_code, char *error_text);
int DCR_BARG_SQLWhere(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr,
	char **sql_where_clause, int *error_code, char *error_text);
int DCR_BARG_UpdateDateField(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr,
	char **update_date_field_name, int *error_code, char *error_text);
int DCR_BARG_UpdateMaxRows(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr,
	unsigned int *update_max_row_count, int *error_code, char *error_text);
#else
int DCR_BARG_AddedFields();
int DCR_BARG_Alloc();
int DCR_BARG_CacheFile();
int DCR_BARG_CacheName();
int DCR_BARG_ClearAddedFields();
int DCR_BARG_ClearIndexSpec();
int DCR_BARG_DBDatabaseName();
int DCR_BARG_DBLoadGran();
int DCR_BARG_DBOwnerName();
int DCR_BARG_DBPassword();
int DCR_BARG_DBTableName();
int DCR_BARG_DBUserName();
int DCR_BARG_IndexSpec();
int DCR_BARG_IndexType();
int DCR_BARG_IndirectIndex();
int DCR_BARG_InitialAlloc();
int DCR_BARG_LoadFromDB();
int DCR_BARG_MaxRows();
int DCR_BARG_OperationMode();
int DCR_BARG_RefreshSeconds();
int DCR_BARG_SQLGroupBy();
int DCR_BARG_SQLOrderBy();
int DCR_BARG_SQLWhere();
int DCR_BARG_UpdateDateField();
int DCR_BARG_UpdateMaxRows();
#endif /* #ifndef NARGS */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
#ifndef NARGS
int DCR_BUSE_AddedFields(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count, char ***usage_list,
	char *error_text);
int DCR_BUSE_Alloc(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count, char ***usage_list,
	char *error_text);
int DCR_BUSE_CacheFile(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count, char ***usage_list,
	char *error_text);
int DCR_BUSE_CacheName(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count, char ***usage_list,
	char *error_text);
int DCR_BUSE_ClearAddedFields(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count, char ***usage_list,
	char *error_text);
int DCR_BUSE_ClearIndexSpec(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count, char ***usage_list,
	char *error_text);
int DCR_BUSE_DBDatabaseName(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count, char ***usage_list,
	char *error_text);
int DCR_BUSE_DBLoadGran(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count, char ***usage_list,
	char *error_text);
int DCR_BUSE_DBOwnerName(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count, char ***usage_list,
	char *error_text);
int DCR_BUSE_DBPassword(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count, char ***usage_list,
	char *error_text);
int DCR_BUSE_DBTableName(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count, char ***usage_list,
	char *error_text);
int DCR_BUSE_DBUserName(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count, char ***usage_list,
	char *error_text);
int DCR_BUSE_IndexSpec(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count, char ***usage_list,
	char *error_text);
int DCR_BUSE_IndexType(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count, char ***usage_list,
	char *error_text);
int DCR_BUSE_IndirectIndex(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count, char ***usage_list,
	char *error_text);
int DCR_BUSE_InitialAlloc(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count, char ***usage_list,
	char *error_text);
int DCR_BUSE_LoadFromDB(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count, char ***usage_list,
	char *error_text);
int DCR_BUSE_MaxRows(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count, char ***usage_list,
	char *error_text);
int DCR_BUSE_OperationMode(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count, char ***usage_list,
	char *error_text);
int DCR_BUSE_RefreshSeconds(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count, char ***usage_list,
	char *error_text);
int DCR_BUSE_SQLGroupBy(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count, char ***usage_list,
	char *error_text);
int DCR_BUSE_SQLOrderBy(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count, char ***usage_list,
	char *error_text);
int DCR_BUSE_SQLWhere(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count, char ***usage_list,
	char *error_text);
int DCR_BUSE_UpdateDateField(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count, char ***usage_list,
	char *error_text);
int DCR_BUSE_UpdateMaxRows(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count, char ***usage_list,
	char *error_text);
#else
int DCR_BUSE_AddedFields();
int DCR_BUSE_Alloc();
int DCR_BUSE_CacheFile();
int DCR_BUSE_CacheName();
int DCR_BUSE_ClearAddedFields();
int DCR_BUSE_ClearIndexSpec();
int DCR_BUSE_DBDatabaseName();
int DCR_BUSE_DBLoadGran();
int DCR_BUSE_DBOwnerName();
int DCR_BUSE_DBPassword();
int DCR_BUSE_DBTableName();
int DCR_BUSE_DBUserName();
int DCR_BUSE_IndexSpec();
int DCR_BUSE_IndexType();
int DCR_BUSE_IndirectIndex();
int DCR_BUSE_InitialAlloc();
int DCR_BUSE_LoadFromDB();
int DCR_BUSE_MaxRows();
int DCR_BUSE_OperationMode();
int DCR_BUSE_RefreshSeconds();
int DCR_BUSE_SQLGroupBy();
int DCR_BUSE_SQLOrderBy();
int DCR_BUSE_SQLWhere();
int DCR_BUSE_UpdateDateField();
int DCR_BUSE_UpdateMaxRows();
#endif /* #ifndef NARGS */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
#ifndef NARGS
void DCR_StatStartTime(volatile DCR_STAT *stat_ptr);
void DCR_StatEndTime(volatile DCR_STAT *stat_ptr,
	unsigned long item_count);
#else
void DCR_StatStartTime();
void DCR_StatEndTime();
#endif /* #ifndef NARGS */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
#ifndef NARGS
int DCR_MakeSQL(DCR_CACHE *cache_ptr, int update_flag,
	char *update_column, DTIME *update_date, char **sql_command,
	char *error_text);
int DCR_CreateDBDeleteSQL(const DCR_CACHE *cache_ptr,
	const char *database_name, const char *owner_name, const char *table_name,
	const char *record_ptr, unsigned int primary_key_count,
	unsigned int *primary_key_list, char *sql_command, char *error_text);
int DCR_CreateDBInsertSQL(const DCR_CACHE *cache_ptr,
	const char *database_name, const char *owner_name, const char *table_name,
	const char *record_ptr, char *sql_command, char *error_text);
int DCR_CreateDBUpdateSQL(const DCR_CACHE *cache_ptr,
	const char *database_name, const char *owner_name, const char *table_name,
	const char *record_ptr, unsigned int primary_key_count,
	unsigned int *primary_key_list, char *sql_command, char *error_text);
int DCR_CreateDBWhereClause(const DCR_CACHE *cache_ptr,
	const char *record_ptr, unsigned int primary_key_count,
	unsigned int *primary_key_list, char *sql_command, char *error_text);
int DCR_AllocSQLString(const DCR_CACHE *cache_ptr, char **sql_command,
	char *error_text);
int DCR_GetSQLLength(const DCR_CACHE *cache_ptr,
	unsigned int *sql_length, char *error_text);
#else
int DCR_MakeSQL();
int DCR_CreateDBDeleteSQL();
int DCR_CreateDBInsertSQL();
int DCR_CreateDBUpdateSQL();
int DCR_CreateDBWhereClause();
int DCR_AllocSQLString();
int DCR_GetSQLLength();
#endif /* #ifndef NARGS */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
#ifndef NARGS
int  DCR_ALLOC_Rows(DCR_CACHE *cache_ptr, void **memory_ptr,
	unsigned int alloc_size);
int  DCR_REALLOC_Rows(DCR_CACHE *cache_ptr, void **memory_ptr,
	unsigned int old_size, unsigned int alloc_size);
void DCR_FREE_Rows(DCR_CACHE *cache_ptr, void **memory_ptr,
	unsigned int free_size);
int  DCR_CreateCache(DCR_CONTROL *cache_control_ptr,
	const char *cache_file_name, const char *cache_name,
	const char *db_spec_string, const char *table_name,
	unsigned int max_load_rows, unsigned int db_load_granularity,
	unsigned int initial_allocation_size, unsigned int allocation_size,
	int load_data_flag, int indirect_index_flag,
	unsigned int added_field_count, char **added_field_list,
	unsigned int index_spec_count, char **index_spec_list,
	const char *sql_group_by_clause, const char *sql_order_by_clause,
	const char *sql_where_clause, const unsigned long *call_back_mask,
	int (*call_back_function)(DCR_CACHE *, unsigned long, int, unsigned int,
	int, unsigned int, void *, DCR_STAT *, int, char *),
	const void **user_data_ptr_list, DCR_CACHE **out_cache_ptr,
	unsigned int *out_cache_index, char *error_text);
int  DCR_DoCacheLoad(DCR_CACHE *cache_ptr, const char *sql_command,
	unsigned int max_load_rows, unsigned int db_load_granularity,
	char *error_text);
int  DCR_DoCacheReload(DCR_CACHE *cache_ptr, int insert_method,
	int stat_capture_flag, int update_flag, char *update_column,
	DTIME *update_date, unsigned int max_load_rows,
	unsigned int db_load_granularity, char *error_text);
int  DCR_DoCacheUpdate(DCR_CACHE *cache_ptr, int insert_method,
	const char *update_date_field_name, unsigned int max_load_rows,
	unsigned int db_load_granularity, char *error_text);
int  DCR_MakeHeader(const char *cache_name, const char *db_spec_string,
	const char *server_name, const char *database_name, const char *owner_name,
	const char *user_name, const char *pass_word, const char *table_name,
	unsigned int initial_allocation_size,
	unsigned int allocation_size, int indirect_index_flag,
	unsigned int member_count, const GEN_MEMBER *member_list,
	unsigned int added_field_count, char **added_field_list,
	unsigned int in_index_spec_count, char **in_index_spec_list,
	DCR_HEADER **cache_header_ptr, char *error_text);
int  DCR_ResizeCache(DCR_CACHE *cache_ptr,
	unsigned int allocated_record_count, int move_index_flag,
	char *error_text);
int  DCR_TruncateCache(DCR_CACHE *cache_ptr, unsigned long length,
	char *error_text);
#else
int  DCR_ALLOC_Rows();
int  DCR_REALLOC_Rows();
void DCR_FREE_Rows();
int  DCR_CreateCache();
int  DCR_DoCacheLoad();
int  DCR_DoCacheReload();
int  DCR_DoCacheUpdate();
int  DCR_MakeHeader();
int  DCR_ResizeCache();
int  DCR_TruncateCache();
#endif /* #ifndef NARGS */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
#ifndef NARGS
int DCR_CompareEmbedded(DCR_CACHE *cache_ptr, const void *index_entry_1,
	const void *index_entry_2, size_t data_length);
int DCR_CompareIndirect(DCR_CACHE *cache_ptr,
	const unsigned long *index_entry_1, const unsigned long *index_entry_2,
	size_t data_length);
#else
int DCR_CompareEmbedded();
int DCR_CompareIndirect();
#endif /* #ifndef NARGS */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
#ifndef NARGS
int DCR_FindFieldByColumn(const DCR_CACHE *cache_ptr,
	const char *db_column_name, unsigned int *out_field_index,
	DCR_FIELD *out_field_ptr, char *error_text);
int DCR_FindFieldByName(const DCR_CACHE *cache_ptr,
	const char *field_name, unsigned int *out_field_index,
	DCR_FIELD *out_field_ptr, char *error_text);
#else
int DCR_FindFieldByColumn();
int DCR_FindFieldByName();
#endif /* #ifndef NARGS */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
#ifndef NARGS
int DCR_FIND_COLUMN_NAME(unsigned int column_name_count,
	const DCR_COLUMN_NAME *column_name_list, const char *column_name,
	unsigned int *found_index);
int DCR_FIND_FIELD_NAME(unsigned int field_name_count,
	const DCR_FIELD_NAME *field_name_list, const char *field_name,
	unsigned int *found_index);
int DCR_FIND_INDEX_NAME(unsigned int index_name_count,
	const DCR_INDEX_NAME *index_name_list, const char *index_name,
	unsigned int *found_index);
#else
int DCR_FIND_COLUMN_NAME();
int DCR_FIND_FIELD_NAME();
int DCR_FIND_INDEX_NAME();
#endif /* #ifndef NARGS */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
#ifndef NARGS
int DCR_CMP_COLUMN_NAME(void *control_ptr,
	const DCR_COLUMN_NAME *ptr_1, const DCR_COLUMN_NAME *ptr_2,
	size_t data_length);
int DCR_CMP_FIELD_ByOrder(void *control_ptr,
	const DCR_FIELD *ptr_1, const DCR_FIELD *ptr_2,
	size_t data_length);
int DCR_CMP_FIELD_NAME(void *control_ptr,
	const DCR_FIELD_NAME *ptr_1, const DCR_FIELD_NAME *ptr_2,
	size_t data_length);
int DCR_CMP_INDEX_NAME(void *control_ptr,
	const DCR_INDEX_NAME *ptr_1, const DCR_INDEX_NAME *ptr_2,
	size_t data_length);
#else
int DCR_CMP_COLUMN_NAME();
int DCR_CMP_FIELD_ByOrder();
int DCR_CMP_FIELD_NAME();
int DCR_CMP_INDEX_NAME();
#endif /* #ifndef NARGS */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Operating system error message function prototypes . . .			*/
	/*	*****************************************************************	*/
#ifndef NARGS
char *DCR_GEN_AppendSpecErrorString(int errno_code, char *error_text);
char *DCR_GEN_AppendLastErrorString(char *error_text);
#else
char *DCR_GEN_AppendSpecErrorString();
char *DCR_GEN_AppendLastErrorString();
#endif /* #ifndef NARGS */
	/*	*****************************************************************	*/

/*	***********************************************************************	*/

#endif /* #ifndef h__DCR_H__h */

