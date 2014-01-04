/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Generalized Support Functions Library Header File							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the DBC generalized support
								functions library.

	Revision History	:	1993-07-07 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__DBCFUNCS_H__h

#define h__DBCFUNCS_H__h					1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Include necessary header files . . .												*/
/*	***********************************************************************	*/

#include <strfuncs.h>
#include <datfuncs.h>
#include <mddl.h>
#include <mfile.h>
#include <mlog.h>

/*	***********************************************************************	*/

typedef unsigned long DBC_FLAG;
#define DBC_FLAG_NONE						((DBC_FLAG) 0)
#define DBC_FLAG_DEBUG_NORMAL				((DBC_FLAG) 1)
#define DBC_FLAG_DEBUG_SQL					((DBC_FLAG) 2)
#define DBC_FLAG_ALL							\
	(DBC_FLAG_DEBUG_NORMAL | DBC_FLAG_DEBUG_SQL)

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   BASE NAME   :  DBC Truth Codes

   NAME        :  DBC Truth Codes

   DESCRIPTION :  Manifest constants used within DBC to specify the truth
						or falsity of expressions.

						(.) ''DBC_TRUE'' is defined as ''1''.

						(.) ''DBC_FALSE'' is defined as ''0''.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2014 Michael L. Brock

   OUTPUT INDEX:  DBC_TRUE
						DBC_FALSE
						Truth Codes:DBC_TRUE
						Truth Codes:DBC_FALSE
						DBC Macros and Manifest Constants:DBC_TRUE
						DBC Macros and Manifest Constants:DBC_FALSE
						Macros and Manifest Constants:DBC_TRUE
						Macros and Manifest Constants:DBC_FALSE
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:  DBC_TRUE
						DBC_FALSE
						DBC Truth Codes
						DBC Truth Code
						DBC truth codes
						DBC truth code

   PUBLISH NAME:	DBC_TRUE
						DBC_FALSE

	ENTRY CLASS	:	Macros and Manifest Constants:Truth Codes

EOH */
/* *********************************************************************** */
#define DBC_TRUE								1
#define DBC_FALSE								0
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   BASE NAME   :	DBC Return Codes

   NAME        :  DBC Return Codes

   DESCRIPTION :  The DBC return codes have the following meanings:

						(.) ''DBC_SUCCESS'' means that the function invoked
						completed without error. ''DBC_SUCCESS'' is guaranteed to
						be equal to zero (''0'').

						(.) ''DBC_FAILURE'' indicates that the function invoked
						encountered a general operation failure. This is the
						'catch-all' error code for those errors which do not fit
						into category of one the other DBC error codes.

						(.) ''DBC_SYSTEM_FAILURE'' indicates that the function
						invoked encountered a failure of a standard library function
						or an operating system call.

						(.) ''DBC_DB_FAILURE'' indicates that the function
						invoked encountered a failure of a database operation.

						(.) ''DBC_BAD_ARGS_FAILURE'' indicates that the arguments
						passed to a function invoked were invalid.

						(.) ''DBC_BAD_TYPE_FAILURE'' indicates that the a DBC type
						used as an argument to a function or in the ``dbc_type``
						member of the ''DBC'' structure used as an argument
						to a function was invalid.

						(.) ''DBC_MEMORY_FAILURE'' indicates that the memory
						required for operation of the function invoked could not be
						allocated.

						(.) ''DBC_UNSUPPORTED_FUNC_FAILURE'' indicates that a
						function requested has not been implmented within the
						facility.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2014 Michael L. Brock

   OUTPUT INDEX:  DBC_SUCCESS
						DBC_FAILURE
						DBC_SYSTEM_FAILURE
						DBC_DB_FAILURE
						DBC_BAD_ARGS_FAILURE
						DBC_BAD_TYPE_FAILURE
						DBC_MEMORY_FAILURE
						DBC_UNSUPPORTED_FUNC_FAILURE
						Return Codes:DBC_SUCCESS
						Return Codes:DBC_FAILURE
						Return Codes:DBC_SYSTEM_FAILURE
						Return Codes:DBC_DB_FAILURE
						Return Codes:DBC_BAD_ARGS_FAILURE
						Return Codes:DBC_BAD_TYPE_FAILURE
						Return Codes:DBC_MEMORY_FAILURE
						Return Codes:DBC_UNSUPPORTED_FUNC_FAILURE
						DBC Macros and Manifest Constants:DBC_SUCCESS
						DBC Macros and Manifest Constants:DBC_FAILURE
						DBC Macros and Manifest Constants:DBC_SYSTEM_FAILURE
						DBC Macros and Manifest Constants:DBC_DB_FAILURE
						DBC Macros and Manifest Constants:DBC_BAD_ARGS_FAILURE
						DBC Macros and Manifest Constants:DBC_BAD_TYPE_FAILURE
						DBC Macros and Manifest Constants:DBC_MEMORY_FAILURE
						DBC Macros and Manifest Constants:DBC_UNSUPPORTED_FUNC_FAILURE
						Macros and Manifest Constants:DBC_SUCCESS
						Macros and Manifest Constants:DBC_FAILURE
						Macros and Manifest Constants:DBC_SYSTEM_FAILURE
						Macros and Manifest Constants:DBC_DB_FAILURE
						Macros and Manifest Constants:DBC_BAD_ARGS_FAILURE
						Macros and Manifest Constants:DBC_BAD_TYPE_FAILURE
						Macros and Manifest Constants:DBC_MEMORY_FAILURE
						Macros and Manifest Constants:DBC_UNSUPPORTED_FUNC_FAILURE
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:  DBC_SUCCESS
						DBC_FAILURE
						DBC_SYSTEM_FAILURE
						DBC_DB_FAILURE
						DBC_BAD_ARGS_FAILURE
						DBC_BAD_TYPE_FAILURE
						DBC_MEMORY_FAILURE
						DBC_UNSUPPORTED_FUNC_FAILURE
						DBC Return Codes
						DBC Return Code
						DBC return codes
						DBC return code
						DBC Status Codes
						DBC Status Code
						DBC status codes
						DBC status code
						DBC Error Codes
						DBC Error Code
						DBC error codes
						DBC error code

   PUBLISH NAME:	DBC_SUCCESS
						DBC_FAILURE
						DBC_SYSTEM_FAILURE
						DBC_DB_FAILURE
						DBC_BAD_ARGS_FAILURE
						DBC_BAD_TYPE_FAILURE
						DBC_MEMORY_FAILURE
						DBC_UNSUPPORTED_FUNC_FAILURE

	ENTRY CLASS	:	Macros and Manifest Constants:Return Codes

EOH */
/* *********************************************************************** */
#define DBC_SUCCESS						 	 0
#define DBC_FAILURE							-1
#define DBC_SYSTEM_FAILURE					-2
#define DBC_DB_FAILURE						-3
#define DBC_BAD_ARGS_FAILURE				-4
#define DBC_BAD_TYPE_FAILURE				-5
#define DBC_MEMORY_FAILURE					-6
#define DBC_UNSUPPORTED_FUNC_FAILURE	-7
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  DBC_MAX_ERROR_TEXT

   DESCRIPTION :  The manifest constant ''DBC_MAX_ERROR_TEXT'' defines the
						minimum amount of storage which should be allocated to
						hold an error message returned by a DBC function.

   CAVEATS     :  DBC error messages can be quite lengthy. Therefore,
						attempting to save space by allocating less than
						''DBC_MAX_ERROR_TEXT'' bytes to error message buffers
						passed to DBC functions can lead to overwriting of the
						heap or the stack.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2014 Michael L. Brock

   OUTPUT INDEX:  DBC_MAX_ERROR_TEXT
						DBC Macros and Manifest Constants:DBC_MAX_ERROR_TEXT
						Macros and Manifest Constants:DBC_MAX_ERROR_TEXT
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	DBC_MAX_ERROR_TEXT

   PUBLISH NAME:	DBC_MAX_ERROR_TEXT

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/* *********************************************************************** */
#define DBC_MAX_ERROR_TEXT					1024
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	DBC Truth Code Mappings

   NAME        :	DBC Truth Code Mappings

	SYNOPSIS		:	truth_code = DBC_MAP_TRUTH_STR(strfuncs_code);

						truth_code = DBC_MAP_TRUTH_GEN(genfuncs_code);

						truth_code = DBC_MAP_TRUTH_DAT(datfuncs_code);

						truth_code = DBC_MAP_TRUTH_DTA(dta_code);

						truth_code = DBC_MAP_TRUTH_MDDL(mddl_code);

						truth_code = DBC_MAP_TRUTH_MFILE(mfile_code);

						truth_code = DBC_MAP_TRUTH_MLOG(mlog_code);

	DESCRIPTION	:	The DBC truth code mapping macros map truth codes from
						various low-level libraries to DBC truth codes.

						(.) ''DBC_MAP_TRUTH_STR'' maps a truth code
						from a STRFUNCS truth code to a DBC truth code.

						(.) ''DBC_MAP_TRUTH_GEN'' maps a truth code
						from a GENFUNCS truth code to a DBC truth code.

						(.) ''DBC_MAP_TRUTH_DAT'' maps a truth code
						from a DATFUNCS truth code to a DBC truth code.

						(.) ''DBC_MAP_TRUTH_DTA'' maps a truth code
						from a DTA truth code to a DBC truth code.

						(.) ''DBC_MAP_TRUTH_MDDL'' maps a truth code
						from a MDDL truth code to a DBC truth code.

						(.) ''DBC_MAP_TRUTH_MFILE'' maps a truth code
						from a MFILE truth code to a DBC truth code.

						(.) ''DBC_MAP_TRUTH_MLOG'' maps a truth code
						from a MLOG truth code to a DBC truth code.

	PARAMETERS	:	The single parameter to these macros is the value of the
						truth code to be mapped to its equivalent DBC truth
						code.

   NOTES       :	To map return codes from the libraries, use the related
						DBC return code mapping macros.

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2014 Michael L. Brock

   OUTPUT INDEX:	DBC_MAP_TRUTH_STR
						DBC_MAP_TRUTH_GEN
						DBC_MAP_TRUTH_DAT
						DBC_MAP_TRUTH_DTA
						DBC_MAP_TRUTH_MDDL
						DBC_MAP_TRUTH_MFILE
						DBC_MAP_TRUTH_MLOG
						Truth Code Mappings:DBC_MAP_TRUTH_STR
						Truth Code Mappings:DBC_MAP_TRUTH_GEN
						Truth Code Mappings:DBC_MAP_TRUTH_DAT
						Truth Code Mappings:DBC_MAP_TRUTH_DTA
						Truth Code Mappings:DBC_MAP_TRUTH_MDDL
						Truth Code Mappings:DBC_MAP_TRUTH_MFILE
						Truth Code Mappings:DBC_MAP_TRUTH_MLOG
						Macros and Manifest Constants:DBC_MAP_TRUTH_STR
						Macros and Manifest Constants:DBC_MAP_TRUTH_GEN
						Macros and Manifest Constants:DBC_MAP_TRUTH_DAT
						Macros and Manifest Constants:DBC_MAP_TRUTH_DTA
						Macros and Manifest Constants:DBC_MAP_TRUTH_MDDL
						Macros and Manifest Constants:DBC_MAP_TRUTH_MFILE
						Macros and Manifest Constants:DBC_MAP_TRUTH_MLOG
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	DBC_MAP_TRUTH_STR
						DBC_MAP_TRUTH_GEN
						DBC_MAP_TRUTH_DAT
						DBC_MAP_TRUTH_DTA
						DBC_MAP_TRUTH_MDDL
						DBC_MAP_TRUTH_MFILE
						DBC_MAP_TRUTH_MLOG
						DBC Truth Code Mappings
						DBC Truth Code Mapping
						DBC truth code mappings
						DBC truth code mapping

   PUBLISH NAME:	DBC_MAP_TRUTH_STR
						DBC_MAP_TRUTH_GEN
						DBC_MAP_TRUTH_DAT
						DBC_MAP_TRUTH_DTA
						DBC_MAP_TRUTH_MDDL
						DBC_MAP_TRUTH_MFILE
						DBC_MAP_TRUTH_MLOG

	ENTRY CLASS	:	Macros and Manifest Constants:Truth Code Mappings

EOH */
/*	***********************************************************************	*/
#define DBC_MAP_TRUTH(code)							\
	((code) ? MLOG_TRUE : MLOG_FALSE)
#define DBC_MAP_TRUTH_STR(str_code)					\
	(((str_code) == STRFUNCS_TRUE) ? DBC_TRUE : DBC_FALSE)
#define DBC_MAP_TRUTH_GEN(gen_code)					\
	(((str_code) == GENFUNCS_TRUE) ? DBC_TRUE : DBC_FALSE)
#define DBC_MAP_TRUTH_DAT(dat_code)					\
	(((dat_code) == DATFUNCS_TRUE) ? DBC_TRUE : DBC_FALSE)
#define DBC_MAP_TRUTH_DTA(dta_code)					\
	(((dta_code) == DTA_TRUE)      ? DBC_TRUE : DBC_FALSE)
#define DBC_MAP_TRUTH_MDDL(mddl_code)				\
	(((mddl_code) == MDDL_TRUE)    ? DBC_TRUE : DBC_FALSE)
#define DBC_MAP_TRUTH_MFILE(mfile_code)			\
	(((mfile_code) == MFILE_TRUE)  ? DBC_TRUE : DBC_FALSE)
#define DBC_MAP_TRUTH_MLOG(mlog_code)				\
	(((mlog_code) == MLOG_TRUE)    ? DBC_TRUE : DBC_FALSE)
	/*	*****************************************************************
		*****************************************************************
		For compatibility . . .
		*****************************************************************	*/
#define DBC_MAP_TRUTH_STR_TO_DBC(str_code)		\
	DBC_MAP_TRUTH_STR(str_code)
#define DBC_MAP_TRUTH_GEN_TO_DBC(gen_code)		\
	DBC_MAP_TRUTH_GEN(gen_code)
#define DBC_MAP_TRUTH_DAT_TO_DBC(dat_code)		\
	DBC_MAP_TRUTH_DAT(dat_code)
#define DBC_MAP_TRUTH_DTA_TO_DBC(dta_code)		\
	DBC_MAP_TRUTH_DTA(dta_code)
#define DBC_MAP_TRUTH_MDDL_TO_DBC(mddl_code)		\
	DBC_MAP_TRUTH_MDDL(mddl_code)
#define DBC_MAP_TRUTH_MFILE_TO_DBC(mfile_code)	\
	DBC_MAP_TRUTH_MFILE(mfile_code)
#define DBC_MAP_TRUTH_MLOG_TO_DBC(mlog_code)		\
	DBC_MAP_TRUTH_MLOG(mlog_code)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	DBC Return Code Mappings

   NAME        :	DBC Return Code Mappings

	SYNOPSIS		:	return_code = DBC_MAP_ERROR_STR(strfuncs_code);

						return_code = DBC_MAP_ERROR_GEN(genfuncs_code);

						return_code = DBC_MAP_ERROR_DAT(datfuncs_code);

						return_code = DBC_MAP_ERROR_DTA(dta_code);

						return_code = DBC_MAP_ERROR_MDDL(mddl_code);

						return_code = DBC_MAP_ERROR_MFILE(mfile_code);

						return_code = DBC_MAP_ERROR_MLOG(mlog_code);

	DESCRIPTION	:	The DBC return code mapping macros map return codes from
						various low-level libraries to DBC return codes.

						(.) ''DBC_MAP_ERROR_STR'' maps a return code
						from a STRFUNCS return code to a DBC return code.

						(.) ''DBC_MAP_ERROR_GEN'' maps a return code
						from a GENFUNCS return code to a DBC return code.

						(.) ''DBC_MAP_ERROR_DAT'' maps a return code
						from a DATFUNCS return code to a DBC return code.

						(.) ''DBC_MAP_ERROR_DTA'' maps a return code
						from a DTA return code to a DBC return code.

						(.) ''DBC_MAP_ERROR_MDDL'' maps a return code
						from a MDDL return code to a DBC return code.

						(.) ''DBC_MAP_ERROR_MFILE'' maps a return code
						from a MFILE return code to a DBC return code.

						(.) ''DBC_MAP_ERROR_MLOG'' maps a return code
						from a MLOG return code to a DBC return code.

	PARAMETERS	:	The single parameter to these macros is the value of the
						return code to be mapped to its equivalent DBC return
						code.

   NOTES       :	To map truth codes from the libraries, use the related
						DBC truth code mapping macros.

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2014 Michael L. Brock

   OUTPUT INDEX:	DBC_MAP_ERROR_STR
						DBC_MAP_ERROR_GEN
						DBC_MAP_ERROR_DAT
						DBC_MAP_ERROR_DTA
						DBC_MAP_ERROR_MDDL
						DBC_MAP_ERROR_MFILE
						DBC_MAP_ERROR_MLOG
						Return Code Mappings:DBC_MAP_ERROR_STR
						Return Code Mappings:DBC_MAP_ERROR_GEN
						Return Code Mappings:DBC_MAP_ERROR_DAT
						Return Code Mappings:DBC_MAP_ERROR_DTA
						Return Code Mappings:DBC_MAP_ERROR_MDDL
						Return Code Mappings:DBC_MAP_ERROR_MFILE
						Return Code Mappings:DBC_MAP_ERROR_MLOG
						Macros and Manifest Constants:DBC_MAP_ERROR_STR
						Macros and Manifest Constants:DBC_MAP_ERROR_GEN
						Macros and Manifest Constants:DBC_MAP_ERROR_DAT
						Macros and Manifest Constants:DBC_MAP_ERROR_DTA
						Macros and Manifest Constants:DBC_MAP_ERROR_MDDL
						Macros and Manifest Constants:DBC_MAP_ERROR_MFILE
						Macros and Manifest Constants:DBC_MAP_ERROR_MLOG
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	DBC_MAP_ERROR_STR
						DBC_MAP_ERROR_GEN
						DBC_MAP_ERROR_DAT
						DBC_MAP_ERROR_DTA
						DBC_MAP_ERROR_MDDL
						DBC_MAP_ERROR_MFILE
						DBC_MAP_ERROR_MLOG
						DBC Return Code Mappings
						DBC Return Code Mapping
						DBC return code mappings
						DBC return code mapping
						DBC Status Code Mappings
						DBC Status Code Mapping
						DBC status code mappings
						DBC status code mapping
						DBC Error Code Mappings
						DBC Error Code Mapping
						DBC error code mappings
						DBC error code mapping

   PUBLISH NAME:	DBC_MAP_ERROR_STR
						DBC_MAP_ERROR_GEN
						DBC_MAP_ERROR_DAT
						DBC_MAP_ERROR_DTA
						DBC_MAP_ERROR_MDDL
						DBC_MAP_ERROR_MFILE
						DBC_MAP_ERROR_MLOG

	ENTRY CLASS	:	Macros and Manifest Constants:Return Code Mappings

EOH */
/*	***********************************************************************	*/
#define DBC_MAP_ERROR_STR(str_code)													\
	(((str_code) == STRFUNCS_SUCCESS)          ? DBC_SUCCESS          :	\
	 ((str_code) == STRFUNCS_FAILURE)          ? DBC_FAILURE          :	\
	 ((str_code) == STRFUNCS_BAD_ARGS_FAILURE) ? DBC_BAD_ARGS_FAILURE :	\
	 ((str_code) == STRFUNCS_MEMORY_FAILURE)   ? DBC_MEMORY_FAILURE   :	\
	 ((str_code) == STRFUNCS_SYSTEM_FAILURE)   ? DBC_SYSTEM_FAILURE   :	\
	 DBC_FAILURE)
#define DBC_MAP_ERROR_GEN(gen_code)													\
	(((gen_code) == GENFUNCS_SUCCESS)          ? DBC_SUCCESS          :	\
	 ((gen_code) == GENFUNCS_FAILURE)          ? DBC_FAILURE          :	\
	 ((gen_code) == GENFUNCS_BAD_ARGS_FAILURE) ? DBC_BAD_ARGS_FAILURE :	\
	 ((gen_code) == GENFUNCS_MEMORY_FAILURE)   ? DBC_MEMORY_FAILURE   :	\
	 ((gen_code) == GENFUNCS_SYSTEM_FAILURE)   ? DBC_SYSTEM_FAILURE   :	\
	 DBC_FAILURE)
#define DBC_MAP_ERROR_DAT(dat_code)													\
	(((dat_code) == DATFUNCS_SUCCESS) ? DBC_SUCCESS : DBC_FAILURE)
#define DBC_MAP_ERROR_DTA(dta_code)													\
	(((dta_code) == DTA_SUCCESS)               ? DBC_SUCCESS          :	\
	 ((dta_code) == DTA_FAILURE)               ? DBC_FAILURE          :	\
	 ((dta_code) == DTA_BAD_ARGS_FAILURE)      ? DBC_BAD_ARGS_FAILURE :	\
	 ((dta_code) == DTA_MEMORY_FAILURE)        ? DBC_MEMORY_FAILURE   :	\
	 ((dta_code) == DTA_SYSTEM_FAILURE)        ? DBC_SYSTEM_FAILURE   :	\
	 DBC_FAILURE)
#define DBC_MAP_ERROR_MDDL(mddl_code)												\
	(((mddl_code) == MDDL_SUCCESS)             ? DBC_SUCCESS          :	\
	 ((mddl_code) == MDDL_FAILURE)             ? DBC_FAILURE          :	\
	 ((mddl_code) == MDDL_BAD_ARGS_FAILURE)    ? DBC_BAD_ARGS_FAILURE :	\
	 ((mddl_code) == MDDL_MEMORY_FAILURE)      ? DBC_MEMORY_FAILURE   :	\
	 ((mddl_code) == MDDL_SYSTEM_FAILURE)      ? DBC_SYSTEM_FAILURE   :	\
	 DBC_FAILURE)
#define DBC_MAP_ERROR_MFILE(mfile_code)											\
	(((mfile_code) == MFILE_SUCCESS)           ? DBC_SUCCESS          :	\
	 ((mfile_code) == MFILE_FAILURE)           ? DBC_FAILURE          :	\
	 ((mfile_code) == MFILE_BAD_ARGS_FAILURE)  ? DBC_BAD_ARGS_FAILURE :	\
	 ((mfile_code) == MFILE_MEMORY_FAILURE)    ? DBC_MEMORY_FAILURE   :	\
	 ((mfile_code) == MFILE_SYSTEM_FAILURE)    ? DBC_SYSTEM_FAILURE   :	\
	 DBC_FAILURE)
#define DBC_MAP_ERROR_MLOG(mlog_code)												\
	(((mlog_code) == MLOG_SUCCESS)             ? DBC_SUCCESS          :	\
	 ((mlog_code) == MLOG_FAILURE)             ? DBC_FAILURE          :	\
	 ((mlog_code) == MLOG_BAD_ARGS_FAILURE)    ? DBC_BAD_ARGS_FAILURE :	\
	 ((mlog_code) == MLOG_MEMORY_FAILURE)      ? DBC_MEMORY_FAILURE   :	\
	 ((mlog_code) == MLOG_SYSTEM_FAILURE)      ? DBC_SYSTEM_FAILURE   :	\
	 DBC_FAILURE)
	/*	*****************************************************************
		*****************************************************************
		For compatibility . . .
		*****************************************************************	*/
#define DBC_MAP_ERROR_STR_TO_DBC(str_code)										\
	DBC_MAP_ERROR_STR(str_code)
#define DBC_MAP_ERROR_GEN_TO_DBC(gen_code)										\
	DBC_MAP_ERROR_GEN(gen_code)
#define DBC_MAP_ERROR_DAT_TO_DBC(dat_code)										\
	DBC_MAP_ERROR_DAT(dat_code)
#define DBC_MAP_ERROR_DTA_TO_DBC(dta_code)										\
	DBC_MAP_ERROR_DTA(dta_code)
#define DBC_MAP_ERROR_MDDL_TO_DBC(mddl_code)										\
	DBC_MAP_ERROR_MDDL(mddl_code)
#define DBC_MAP_ERROR_MFILE_TO_DBC(mfile_code)									\
	DBC_MAP_ERROR_MFILE(mfile_code)
#define DBC_MAP_ERROR_MLOG_TO_DBC(mlog_code)										\
	DBC_MAP_ERROR_MLOG(mlog_code)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_FACILITY_NAME_LENGTH

   DESCRIPTION :	The ''DBC_FACILITY_NAME_LENGTH'' manifest constant specifies
						the maximum length of a DBC facility name string.

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2014 Michael L. Brock

   OUTPUT INDEX:	DBC_FACILITY_NAME_LENGTH
						Macros and Manifest Constants:DBC_FACILITY_NAME_LENGTH
						DBC Macros and Manifest Constants:DBC_FACILITY_NAME_LENGTH
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	DBC_FACILITY_NAME_LENGTH

   PUBLISH NAME:	DBC_FACILITY_NAME_LENGTH

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define DBC_FACILITY_NAME_LENGTH			31
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_VENDOR_NAME_LENGTH

   DESCRIPTION :	The ''DBC_VENDOR_NAME_LENGTH'' manifest constant specifies
						the maximum length of a DBC facility name string.

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2014 Michael L. Brock

   OUTPUT INDEX:	DBC_VENDOR_NAME_LENGTH
						Macros and Manifest Constants:DBC_VENDOR_NAME_LENGTH
						DBC Macros and Manifest Constants:DBC_VENDOR_NAME_LENGTH
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	DBC_VENDOR_NAME_LENGTH

   PUBLISH NAME:	DBC_VENDOR_NAME_LENGTH

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define DBC_VENDOR_NAME_LENGTH			31
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/* *********************************************************************** */
typedef unsigned long DBC_SIGNATURE;
/* *********************************************************************** */

/*
	ADF NOTE: NO ADF
*/
/*	***********************************************************************	*/
typedef unsigned int DBC_BASIC_TYPE;
/*	***********************************************************************	*/

/*
	ADF NOTE: NO ADF
*/
/*	***********************************************************************	*/
#define DBC_BASIC_TYPE_BIT					((DBC_BASIC_TYPE) 0x00)
#define DBC_BASIC_TYPE_CHAR				((DBC_BASIC_TYPE) 0x01)
#define DBC_BASIC_TYPE_INT1				((DBC_BASIC_TYPE) 0x02)
#define DBC_BASIC_TYPE_INT2				((DBC_BASIC_TYPE) 0x03)
#define DBC_BASIC_TYPE_INT4				((DBC_BASIC_TYPE) 0x04)
#define DBC_BASIC_TYPE_INT8				((DBC_BASIC_TYPE) 0x05)
#define DBC_BASIC_TYPE_FLOAT				((DBC_BASIC_TYPE) 0x06)
#define DBC_BASIC_TYPE_DOUBLE				((DBC_BASIC_TYPE) 0x07)
#define DBC_BASIC_TYPE_DOUBLE_LONG		((DBC_BASIC_TYPE) 0x08)
#define DBC_BASIC_TYPE_MONEY_SHORT		((DBC_BASIC_TYPE) 0x09)
#define DBC_BASIC_TYPE_MONEY_LONG		((DBC_BASIC_TYPE) 0x0A)
#define DBC_BASIC_TYPE_DATE_SHORT		((DBC_BASIC_TYPE) 0x0B)
#define DBC_BASIC_TYPE_DATE_LONG			((DBC_BASIC_TYPE) 0x0C)
#define DBC_BASIC_TYPE_TIME_SHORT		((DBC_BASIC_TYPE) 0x0D)
#define DBC_BASIC_TYPE_TIME_LONG			((DBC_BASIC_TYPE) 0x0E)
#define DBC_BASIC_TYPE_BINARY				((DBC_BASIC_TYPE) 0x0F)
#define DBC_BASIC_TYPE_TEXT				((DBC_BASIC_TYPE) 0x10)
#define DBC_BASIC_TYPE_IMAGE				((DBC_BASIC_TYPE) 0x11)

#define DBC_BASIC_TYPE_COUNT				0x12
/*	***********************************************************************	*/

/*
	ADF NOTE: NO ADF
*/
/*	***********************************************************************	*/
typedef unsigned long DBC_ANYTYPE_DATE[2];
typedef unsigned long DBC_ANYTYPE_TIME[2];
typedef double        DBC_ANYTYPE_NUMBER;
/*	***********************************************************************	*/

/*
	ADF NOTE: NO ADF
*/
/*	***********************************************************************	*/
typedef struct tag_DBC_GETROWS {
	unsigned int   member_count;
	const MDDL    *member_list;
	const char    *sql_command;
	const char    *table_name;
	unsigned int   out_row_size;
	unsigned int   data_row_size;
	unsigned int   data_row_offset;
	unsigned int   max_row_count;
	unsigned int   alloc_granularity;
	void          *alloc_control_ptr;
	void          *user_data_ptr;
#ifndef NARGS
	int          (*per_row)(void *, const struct tag_DBC_GETROWS *,
						unsigned int, const void *, char *);
	int          (*alloc)(void *, void **, unsigned int);
	int          (*realloc)(void *, void **, unsigned int, unsigned int);
	void         (*free)(void *, void **, unsigned int);
	void         (*per_row_free)(void *, const struct tag_DBC_GETROWS *,
						unsigned int, void *);
#else
	int          (*per_row)();
	int          (*alloc)();
	int          (*realloc)();
	void         (*free)();
	void         (*per_row_free)();
#endif /* #ifndef NARGS */
} DBC_GETROWS;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_FUNCS

   DESCRIPTION :	The ''DBC_FUNCS'' structure contains the pointer to the
						functions which implement a DBC facility.

						The ''DBC_FUNCS'' structure is declared as follows:

{|@|}typedef struct tag_DBC_FUNCS {
	int          (*bind)(void *dbc_control_ptr, unsigned int member_count,
						const MDDL *member_list, const char *table_name,
						void *bind_buffer, char *error_text);
	int          (*cancel)(void *dbc_control_ptr, char *error_text);
	int          (*cancel_all)(void *dbc_control_ptr);
	int          (*cancel_query)(void *dbc_control_ptr, char *error_text);
	void         (*close)(void **dbc_control_ptr);
	int          (*do_sql)(void *dbc_control_ptr, const char *sql_command,
						char *error_text);
	char        *(*get_id)(char *);
	int          (*get_rows)(void *dbc_control_ptr, unsigned int member_count,
						const MDDL *member_list, const char *sql_command,
						const char *table_name, unsigned int *out_row_count,
						void **out_row_list, unsigned int out_row_size,
						unsigned int data_row_size, unsigned int data_row_offset,
						unsigned int max_row_count, unsigned int alloc_granularity,
						char *error_text);
	int          (*get_rows_basic)(void *dbc_control_ptr,
						const DBC_GETROWS *get_rows_ptr,
						unsigned int *out_row_count, void **out_row_list,
						char *error_text);
	char        *(*get_vendor_name)(char *vendor_name);
	STR_VERSION *(*get_version)(STR_VERSION *version_number);
	char        *(*get_version_string)(char *version_string);
	int   		 (*init)(void **dbc_control_ptr,
						MLOG *mlog_ptr, int db_debug_flag,
						int sql_debug_flag, char *error_text);
	int          (*parse_conn)(const char *conn_type, const char *conn_string,
						unsigned int *parsed_count, char ***parsed_list,
						char *error_text);
	int          (*table_to_members)(void *dbc_control_ptr,
						const char *table_name, unsigned int *structure_size,
						unsigned int *member_count, MDDL **member_list,
						char *error_text);
						//	///////////////////////////////////////////////	//
						//	///////////////////////////////////////////////	//
						//		These are ancilliary and support functions.	//
						//	///////////////////////////////////////////////	//
	int          (*set_display_length)(unsigned int type_count,
						const DTA_TYPE *type_list, MDDL *member_ptr,
						int header_flag, unsigned int null_string_length,
						unsigned int intra_field_sep_length, void *user_data_ptr,
						char *error_text);
	void         (*dump_field)(unsigned int type_count,
						const DTA_TYPE *type_list,
						const MDDL *member_ptr, const void *record_ptr,
						int null_flag, const char *null_string,
						const char *intra_field_sep, const char *overflow_char,
						void *user_data_ptr,
						STR_FUNC_TYPE_fprintf output_function,
						void *output_control);
						//	///////////////////////////////////////////////	//
						//	///////////////////////////////////////////////	//
						//		These are ancilliary and support functions.	//
						//	///////////////////////////////////////////////	//
	int          (*double_to_number)(int dbc_type, double double_value,
						void *number_ptr, char *error_text);
	int          (*number_to_double)(int dbc_type, const void *number_ptr,
						void *double_ptr, char *error_text);
	int          (*dtime_to_date)(int dbc_type, const DTIME *dtime_ptr,
						void *date_ptr, char *error_text);
	int          (*date_to_dtime)(int dbc_type, const void *date_ptr,
						DTIME *dtime_ptr, char *error_text);
	int          (*dtime_to_time)(int dbc_type, const DTIME *dtime_ptr,
						void *time_ptr, char *error_text);
	int          (*time_to_dtime)(int dbc_type, const void *time_ptr,
						DTIME *dtime_ptr, char *error_text);
	int          (*is_number)(int dbc_type);
	int          (*min_number)(int dbc_type, double *double_ptr,
						char *error_text);
	int          (*max_number)(int dbc_type, double *double_ptr,
						char *error_text);
	int          (*cmp_number)(int dbc_type, const void *ptr_1,
						const void *ptr_2);
	int          (*scmp_number)(void *control_ptr, const void *ptr_1,
						const void *ptr_2, size_t data_length);
	int          (*is_date)(int dbc_type);
	int          (*min_date)(int dbc_type, DTIME *dtime_ptr, char *error_text);
	int          (*max_date)(int dbc_type, DTIME *dtime_ptr, char *error_text);
	int          (*cmp_date)(int dbc_type, const void *ptr_1,
						const void *ptr_2);
	int          (*scmp_date)(void *control_ptr, const void *ptr_1,
						const void *ptr_2, size_t data_length);
	int          (*is_time)(int dbc_type);
	int          (*min_time)(int dbc_type, DTIME *dtime_ptr, char *error_text);
	int          (*max_time)(int dbc_type, DTIME *dtime_ptr, char *error_text);
	int          (*cmp_time)(int dbc_type, const void *ptr_1,
						const void *ptr_2);
	int          (*scmp_time)(void *control_ptr, const void *ptr_1,
						const void *ptr_2, size_t data_length);
						//	///////////////////////////////////////////////	//
} DBC_FUNCS;

	MEMBERS		:	The members of this structure are as follow:

						(.) ``bind`` is a pointer to the function which binds
						columns.

						(.) ``cancel`` is ''ADF NOTE HERE''.

						(.) ``cancel_all`` is ''ADF NOTE HERE''.

						(.) ``cancel_query`` is ''ADF NOTE HERE''.

						(.) ``close`` is a pointer to the function which closes
						a DBC facility and frees its resources.

						(.) ``do_sql`` is a pointer to the function which executes
						an SQL statement for a DBC facility.

						(.) ``get_id`` is a pointer to the function which gets the
						human-readable string which identifies a DBC facility.

						(.) ``get_rows`` is a pointer to the function which, given
						an SQL statement, returns a set of rows.

						(.) ``get_rows_basic`` is a pointer to the function which
						returns a set of rows. It is a lower-level function than
						the function to which the ``get_rows`` member points.

						(.) ``get_vendor_name`` is ''ADF NOTE HERE''.

						(.) ``get_version`` is ''ADF NOTE HERE''.

						(.) ``get_version_string`` is ''ADF NOTE HERE''.

						(.) ``init`` is a pointer to the function which initializes
						a DBC facility control structure.

						(.) ``parse_conn`` is ''ADF NOTE HERE''.

						(.) ``table_to_members`` is ''ADF NOTE HERE''.

						(.) ``set_display_length`` is ''ADF NOTE HERE''.

						(.) ``dump_field`` is ''ADF NOTE HERE''.

						(.) ``double_to_number`` is ''ADF NOTE HERE''.

						(.) ``number_to_double`` is ''ADF NOTE HERE''.

						(.) ``dtime_to_date`` is ''ADF NOTE HERE''.

						(.) ``date_to_dtime`` is ''ADF NOTE HERE''.

						(.) ``dtime_to_time`` is ''ADF NOTE HERE''.

						(.) ``time_to_dtime`` is ''ADF NOTE HERE''.

						(.) ``is_number`` is ''ADF NOTE HERE''.

						(.) ``min_number`` is ''ADF NOTE HERE''.

						(.) ``max_number`` is ''ADF NOTE HERE''.

						(.) ``cmp_number`` is ''ADF NOTE HERE''.

						(.) ``scmp_number`` is ''ADF NOTE HERE''.

						(.) ``is_date`` is ''ADF NOTE HERE''.

						(.) ``min_date`` is ''ADF NOTE HERE''.

						(.) ``max_date`` is ''ADF NOTE HERE''.

						(.) ``cmp_date`` is ''ADF NOTE HERE''.

						(.) ``scmp_date`` is ''ADF NOTE HERE''.

						(.) ``is_time`` is ''ADF NOTE HERE''.

						(.) ``min_time`` is ''ADF NOTE HERE''.

						(.) ``max_time`` is ''ADF NOTE HERE''.

						(.) ``cmp_time`` is ''ADF NOTE HERE''.

						(.) ``scmp_time`` is ''ADF NOTE HERE''.

   NOTES       :	A ''DBC_FUNCS'' structure can be initialized by a call to
						the function ``DBC_AttachFacility`` in the appropriate DBC
						facility library. As of the time of this writing, the only
						such libraries available are ``dbcdblib.a`` (the Sybase
						DB-LIB facility library) and ``dbcctlib.a`` (the Sybase
						CT-LIB facility library).

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2014 Michael L. Brock

   OUTPUT INDEX:	DBC_FUNCS
						Structures and Data Types:DBC_FUNCS
						DBC Structures and Data Types:DBC_FUNCS

   PUBLISH XREF:	DBC_FUNCS

   PUBLISH NAME:	DBC_FUNCS

	ENTRY CLASS	:	Structures and Data Types

EOH */
/*	***********************************************************************	*/
struct tag_DBC_CONTEXT;
typedef struct tag_DBC_FUNCS {
#ifndef NARGS
	int          (*bind)(void *dbc_control_ptr, unsigned int member_count,
						const MDDL *member_list, const char *table_name,
						void *bind_buffer, char *error_text);
	int          (*cancel)(void *dbc_control_ptr, char *error_text);
	int          (*cancel_all)(void *dbc_control_ptr, char *error_text);
	int          (*cancel_query)(void *dbc_control_ptr, char *error_text);
	void         (*close)(void **dbc_control_ptr);
	int          (*do_sql)(void *dbc_control_ptr, const char *sql_command,
						char *error_text);
	char        *(*get_id)(char *);
	int          (*get_rows)(void *dbc_control_ptr, unsigned int member_count,
						const MDDL *member_list, const char *sql_command,
						const char *table_name, unsigned int *out_row_count,
						void **out_row_list, unsigned int out_row_size,
						unsigned int data_row_size, unsigned int data_row_offset,
						unsigned int max_row_count, unsigned int alloc_granularity,
						char *error_text);
	int          (*get_rows_basic)(void *dbc_control_ptr,
						const DBC_GETROWS *get_rows_ptr,
						unsigned int *out_row_count, void **out_row_list,
						char *error_text);
	char        *(*get_vendor_name)(char *vendor_name);
	STR_VERSION *(*get_version)(STR_VERSION *version_number);
	char        *(*get_version_string)(char *version_string);
	int   		 (*init)(struct tag_DBC_CONTEXT *dbc_context_ptr,
						MLOG *mlog_ptr, DBC_FLAG flags, void *user_data_ptr,
						char *error_text);
	int          (*open)(void *dbc_control_ptr, const char *conn_type,
						const char *conn_string, MLOG *mlog_ptr, DBC_FLAG flags,
						void *user_data_ptr, char *error_text);
	int          (*parse_conn)(const char *conn_type, const char *conn_string,
						unsigned int *parsed_count, char ***parsed_list,
						char *error_text);
	int          (*table_to_members)(void *dbc_control_ptr,
						const char *table_name, unsigned int *structure_size,
						unsigned int *member_count, MDDL **member_list,
						char *error_text);
	int          (*set_display_length)(unsigned int type_count,
						const DTA_TYPE *type_list, MDDL *member_ptr,
						int header_flag, unsigned int null_string_length,
						unsigned int intra_field_sep_length, void *user_data_ptr,
						char *error_text);
	void         (*dump_field)(unsigned int type_count,
						const DTA_TYPE *type_list,
						const MDDL *member_ptr, const void *record_ptr,
						int null_flag, const char *null_string,
						const char *intra_field_sep, const char *overflow_char,
						void *user_data_ptr,
						STR_FUNC_TYPE_fprintf output_function,
						void *output_control);
	int          (*map_type_to_mddl)(DBC_BASIC_TYPE dbc_basic_type,
						MDDL *mddl_ptr, char *error_text);
	int          (*format_type)(int dbc_type, unsigned int data_length,
						const void *data_ptr, unsigned int min_length,
						unsigned int max_length, int right_justify_flag,
						unsigned int decimal_places, char *out_string,
						char *error_text);
	int          (*format_type_sql)(int dbc_type, unsigned int data_length,
						const void *data_ptr, char *out_string, char *error_text);
						/*	***********************************************	*/
						/*	***********************************************	*/
						/*		These are ancilliary and support functions.	*/
						/*	***********************************************	*/
	int          (*double_to_number)(int dbc_type, double double_value,
						void *number_ptr, char *error_text);
	int          (*number_to_double)(int dbc_type, const void *number_ptr,
						double *double_ptr, char *error_text);
	int          (*dtime_to_date)(int dbc_type, const DTIME *dtime_ptr,
						void *date_ptr, char *error_text);
	int          (*date_to_dtime)(int dbc_type, const void *date_ptr,
						DTIME *dtime_ptr, char *error_text);
	int          (*dtime_to_time)(int dbc_type, const DTIME *dtime_ptr,
						void *time_ptr, char *error_text);
	int          (*time_to_dtime)(int dbc_type, const void *time_ptr,
						DTIME *dtime_ptr, char *error_text);
	int          (*is_number)(int dbc_type);
	int          (*min_number)(int dbc_type, double *double_ptr,
						char *error_text);
	int          (*max_number)(int dbc_type, double *double_ptr,
						char *error_text);
	int          (*cmp_number)(int dbc_type, const void *ptr_1,
						const void *ptr_2);
	int          (*scmp_number)(void *control_ptr, const void *ptr_1,
						const void *ptr_2, size_t data_length);
	int          (*is_date)(int dbc_type);
	int          (*min_date)(int dbc_type, DTIME *dtime_ptr, char *error_text);
	int          (*max_date)(int dbc_type, DTIME *dtime_ptr, char *error_text);
	int          (*cmp_date)(int dbc_type, const void *ptr_1,
						const void *ptr_2);
	int          (*scmp_date)(void *control_ptr, const void *ptr_1,
						const void *ptr_2, size_t data_length);
	int          (*is_time)(int dbc_type);
	int          (*min_time)(int dbc_type, DTIME *dtime_ptr, char *error_text);
	int          (*max_time)(int dbc_type, DTIME *dtime_ptr, char *error_text);
	int          (*cmp_time)(int dbc_type, const void *ptr_1,
						const void *ptr_2);
	int          (*scmp_time)(void *control_ptr, const void *ptr_1,
						const void *ptr_2, size_t data_length);
						/*	***********************************************	*/
#else
	int          (*bind)();
	int          (*cancel)();
	void         (*cancel_all)();
	int          (*cancel_query)();
	void         (*close)();
	int          (*do_sql)();
	char        *(*get_id)();
	int          (*get_rows)();
	int          (*get_rows_basic)();
	char        *(*get_vendor_name)();
	STR_VERSION *(*get_version)();
	char        *(*get_version_string)();
	int   		 (*init)();
	int          (*parse_conn)();
	int          (*table_to_members)();
						/*	***********************************************	*/
						/*	***********************************************	*/
						/*		These are ancilliary and support functions.	*/
						/*	***********************************************	*/
	int          (*set_display_length)();
	void         (*dump_field)();
	int          (*double_to_number)();
	int          (*number_to_double)();
	int          (*dtime_to_date)();
	int          (*date_to_dtime)();
	int          (*dtime_to_time)();
	int          (*time_to_dtime)();
	int          (*is_number)();
	int          (*min_number)();
	int          (*max_number)();
	int          (*cmp_number)();
	int          (*scmp_number)();
	int          (*is_date)();
	int          (*min_date)();
	int          (*max_date)();
	int          (*cmp_date)();
	int          (*scmp_date)();
	int          (*is_time)();
	int          (*min_time)();
	int          (*max_time)();
	int          (*cmp_time)();
	int          (*scmp_time)();
						/*	***********************************************	*/
#endif /* #ifndef NARGS */
} DBC_FUNCS;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_CONTEXT

   DESCRIPTION :	The ''DBC_CONTEXT'' structure manages the data associated
						with a database connection.

						The ''DBC_CONTEXT'' structure is declared as follows:

{|@|}typedef struct {
	DBC_SIGNATURE  signature;
	void          *user_data_ptr;
	void          *dbc_control_ptr;
	DBC_FUNCS      dbc_funcs;
} DBC_CONTEXT;

	MEMBERS		:	The members of this structure are as follow:

						(.) ``server_name`` is the name of the database server to
						which the connection was made.

						(.) ``database_name`` is the name of the database to which
						the connection was made.

						(.) Note that if the connection string used as a parameter
						to ``DBC_OPEN_DBContext`` to initialize the database
						connection did not include a ``database-name`` component,
						this member will consist of a zero-length string.

						(.) ``owner_name`` is the name of the owner of the database
						to which the connection was made.

						(.) Note that if the connection string used as a parameter
						to ``DBC_OPEN_Context`` to initialize the database
						connection did not include a ``owner-name`` component,
						this member will consist of a zero-length string.

						(.) ``user_name`` is the name of the user used to login to
						the database server.

						(.) ``pass_word`` is the password used to login to the
						database server.

						(.) Note that if the connection string used as a parameter
						to ``DBC_OPEN_Context`` to initialize the database
						connection did not include a ``password`` component,
						this member will consist of a zero-length string.

						(.) ``db_debug_flag`` indicates whether database debuggging
						output is active.

						(.) ``sql_debug_flag`` indicates whether SQL debugging
						output is active.

						(.) ``user_data_ptr`` is a pointer to ''void'' which the
						application programmer may use in order to attach
						application-specific knowledge to the structure.

						(.) ``dbc_control_ptr`` points to the DBC library control
						data being used to manage connection to the database.

						(.) ``dbc_funcs`` is a ''DBC_FUNCS'' structure which
						contains pointers to the DBC library functions which manage
						connection to the database.

   NOTES       :	Use ``DBC_OPEN_DBContext`` to initialize a connection to the
						database and ````DBC_CLOSE_DBContext`` to close the
						connection.

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2014 Michael L. Brock

   OUTPUT INDEX:	DBC_CONTEXT
						Structures and Data Types:DBC_CONTEXT
						DBC Structures and Data Types:DBC_CONTEXT

   PUBLISH XREF:	DBC_CONTEXT

   PUBLISH NAME:	DBC_CONTEXT

	ENTRY CLASS	:	Structures and Data Types

EOH */
/*	***********************************************************************	*/
typedef struct tag_DBC_CONTEXT {
	DBC_SIGNATURE  signature;
	void          *user_data_ptr;
	void          *dbc_control_ptr;
	DBC_FUNCS      dbc_funcs;
} DBC_CONTEXT;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH .c,3

   NAME        :	DBC_AttachFacility

   SYNOPSIS    :	void DBC_AttachFacility(funcs_ptr);

						DBC_FUNCS *funcs_ptr;

   DESCRIPTION :	Populates a ''DBC_FUNCS'' structure with pointers to the
						functions which implement a DBC facility.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``funcs_ptr`` points to the ''DBC_FUNCS'' structure to
						be populated by this function.

						(-) It is valid to invoke this function with the
						``funcs_ptr`` parameter equal to ''NULL''. This behavior
						is intended to support the forcing of the linker to include
						the DBC facility functions in the executable.

   RETURNS     :	Void.

   NOTES       :	If the DBC DB-LIB facility library ``dbcdblib.a`` has been
						linked into an executable, then the ``DBC_AttachFacility``
						function in that library will be used. It in turn calls the
						function ``DBC_DBLIB_AttachFacility``.

						Alternatively, if the DBC DB-LIB facility library
						``dbcdblib.a`` has been linked into an executable, then the
						``DBC_AttachFacility`` function in that library will be
						used. It in turn calls the function
						``DBC_CTLIB_AttachFacility``.

   CAVEATS     :	Not all functions will be implemented in all facilities. It
						is, therefore, possible that some of the function pointers
						in the ``funcs_ptr`` parameter will be set to ''NULL''.
						The application programmer must be sure to test for this
						condition before invoking any facility function.

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2014 Michael L. Brock

   OUTPUT INDEX:	DBC_AttachFacility
						DBC Functions:Attach Functions:DBC_AttachFacility

   PUBLISH XREF:	DBC_AttachFacility

   PUBLISH NAME:	DBC_AttachFacility

	ENTRY CLASS	:	DBC Functions:Attach Functions

EOH */
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Function prototypes . . .															*/
/*	***********************************************************************	*/

typedef COMPAT_FN_TYPE(void (*DBC_AttachType), (DBC_FUNCS *funcs_ptr));

	/*	*****************************************************************
		*****************************************************************
		The generic DBC attach function prototype . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int  DBC_Attach, (DBC_CONTEXT *dbc_context_ptr,
	DBC_AttachType));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		The essential DBC facility function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_Cancel,
	(DBC_CONTEXT *dbc_context_ptr, char *error_text));
COMPAT_FN_DECL(int DBC_CancelAll,
	(DBC_CONTEXT *dbc_context_ptr, char *error_text));
COMPAT_FN_DECL(int DBC_CancelQuery,
	(DBC_CONTEXT *dbc_context_ptr, char *error_text));
COMPAT_FN_DECL(void DBC_Close, (DBC_CONTEXT *dbc_context_ptr));
COMPAT_FN_DECL(int  DBC_DoSQL, (DBC_CONTEXT *dbc_context_ptr,
	const char *sql_command, char *error_text));
COMPAT_FN_DECL(void DBC_DumpField, (const DBC_CONTEXT *dbc_context_ptr,
	unsigned int type_count, const DTA_TYPE *type_list, const MDDL *member_ptr,
	const void *record_ptr, int null_flag, const char *null_string,
	const char *intra_field_sep, const char *overflow_char,
	void *user_data_ptr, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(STR_VERSION *DBC_GetFacilityVersion,
	(const DBC_CONTEXT *dbc_context_ptr, STR_VERSION *version_number));
COMPAT_FN_DECL(char *DBC_GetFacilityVersionString,
	(const DBC_CONTEXT *dbc_context_ptr, char *version_string));
COMPAT_FN_DECL(char *DBC_GetID, (const DBC_CONTEXT *dbc_context_ptr,
	char *id_string));
COMPAT_FN_DECL(int  DBC_GetRows, (DBC_CONTEXT *dbc_context_ptr,
	unsigned int member_count, const MDDL *member_list, const char *sql_command,
	const char *table_name, unsigned int *out_row_count, void **out_row_list,
	unsigned int out_row_size, unsigned int data_row_size,
	unsigned int data_row_offset, unsigned int max_row_count,
	unsigned int alloc_granularity, char *error_text));
COMPAT_FN_DECL(int  DBC_GetRowsBasic, (DBC_CONTEXT *dbc_context_ptr,
	const DBC_GETROWS *get_rows_ptr, unsigned int *out_row_count,
	void **out_row_list, char *error_text));
COMPAT_FN_DECL(char *DBC_GetVendorName, (const DBC_CONTEXT *dbc_context_ptr,
	char *vendor_name));
COMPAT_FN_DECL(int  DBC_Initialize, (DBC_CONTEXT *dbc_context_ptr,
	void (*attach_func)(DBC_FUNCS *funcs_ptr),
	MLOG *mlog_ptr, DBC_FLAG flags, void *user_data_ptr, char *error_text));
COMPAT_FN_DECL(int  DBC_Open, (DBC_CONTEXT *dbc_context_ptr,
	void (*attach_func)(DBC_FUNCS *funcs_ptr),
	const char *connection_type, const char *connection_string,
	MLOG *mlog_ptr, DBC_FLAG flags, void *user_data_ptr, char *error_text));
COMPAT_FN_DECL(int DBC_ParseConn, (const DBC_CONTEXT *dbc_context_ptr,
	const char *conn_type, const char *conn_string, unsigned int *parsed_count,
	char ***parsed_list, char *error_text));
COMPAT_FN_DECL(int DBC_SetDisplayLength, (const DBC_CONTEXT *dbc_context_ptr,
	unsigned int type_count, const DTA_TYPE *type_list, MDDL *member_ptr,
	int header_flag, unsigned int null_string_length,
	unsigned int intra_field_sep_length, void *user_data_ptr,
	char *error_text));
COMPAT_FN_DECL(int DBC_TableToMembers, (DBC_CONTEXT *dbc_context_ptr,
	const char *in_table_name, unsigned int *structure_size,
	unsigned int *member_count, MDDL **member_list, char *error_text));
COMPAT_FN_DECL(int DBC_MapTypeToMDDL, (const DBC_CONTEXT *dbc_context_ptr,
	DBC_BASIC_TYPE dbc_basic_type, MDDL *mddl_ptr, char *error_text));
COMPAT_FN_DECL(int DBC_FormatType, (const DBC_CONTEXT *dbc_context_ptr,
	int dbc_type, unsigned int data_length, const void *data_ptr,
	unsigned int min_length, unsigned int max_length, int right_justify_flag,
	unsigned int decimal_places, char *out_string, char *error_text));
COMPAT_FN_DECL(int DBC_FormatTypeSQL, (const DBC_CONTEXT *dbc_context_ptr,
	int dbc_type, unsigned int data_length, const void *data_ptr,
	char *out_string, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Date ancilliary and support function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_CompareDate,
	(const DBC_CONTEXT *dbc_context_ptr, int dbc_type, const void *ptr_1,
	const void *ptr_2));
COMPAT_FN_DECL(int DBC_SCompareDate,
	(const DBC_CONTEXT *dbc_context_ptr, void *control_ptr, const void *ptr_1,
	const void *ptr_2, size_t data_length));
COMPAT_FN_DECL(int DBC_DateToDTIME,
	(const DBC_CONTEXT *dbc_context_ptr, int dbc_type, const void *date_ptr,
	DTIME *dtime_ptr, char *error_text));
COMPAT_FN_DECL(int DBC_DTIMEToDate,
	(const DBC_CONTEXT *dbc_context_ptr, int dbc_type, const DTIME *dtime_ptr,
	void  *date_ptr, char *error_text));
COMPAT_FN_DECL(int DBC_IsDate,
	(const DBC_CONTEXT *dbc_context_ptr, int dbc_type));
COMPAT_FN_DECL(int DBC_MinDate,
	(const DBC_CONTEXT *dbc_context_ptr, int dbc_type, DTIME *dtime_ptr,
	char *error_text));
COMPAT_FN_DECL(int DBC_MaxDate,
	(const DBC_CONTEXT *dbc_context_ptr, int dbc_type, DTIME *dtime_ptr,
	char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Time ancilliary and support function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_CompareTime,
	(const DBC_CONTEXT *dbc_context_ptr, int dbc_type, const void *ptr_1,
	const void *ptr_2));
COMPAT_FN_DECL(int DBC_SCompareTime,
	(const DBC_CONTEXT *dbc_context_ptr, void *control_ptr, const void *ptr_1,
	const void *ptr_2, size_t data_length));
COMPAT_FN_DECL(int DBC_TimeToDTIME,
	(const DBC_CONTEXT *dbc_context_ptr, int dbc_type, const void  *time_ptr,
	DTIME *dtime_ptr, char *error_text));
COMPAT_FN_DECL(int DBC_DTIMEToTime,
	(const DBC_CONTEXT *dbc_context_ptr, int dbc_type, const DTIME *dtime_ptr,
	void  *time_ptr, char *error_text));
COMPAT_FN_DECL(int DBC_IsTime,
	(const DBC_CONTEXT *dbc_context_ptr, int dbc_type));
COMPAT_FN_DECL(int DBC_MinTime,
	(const DBC_CONTEXT *dbc_context_ptr, int dbc_type, DTIME *dtime_ptr,
	char *error_text));
COMPAT_FN_DECL(int DBC_MaxTime,
	(const DBC_CONTEXT *dbc_context_ptr, int dbc_type, DTIME *dtime_ptr,
	char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Numeric ancilliary and support function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_CompareNumber,
	(const DBC_CONTEXT *dbc_context_ptr, int dbc_type, const void *ptr_1,
	const void *ptr_2));
COMPAT_FN_DECL(int DBC_SCompareNumber,
	(const DBC_CONTEXT *dbc_context_ptr, void *control_ptr, const void *ptr_1,
	const void *ptr_2, size_t data_length));
COMPAT_FN_DECL(int DBC_DoubleToNumber,
	(const DBC_CONTEXT *dbc_context_ptr, int dbc_type, double double_value,
	void *number_ptr, char *error_text));
COMPAT_FN_DECL(int DBC_NumberToDouble,
	(const DBC_CONTEXT *dbc_context_ptr, int dbc_type, const void *number_ptr,
	double *double_ptr, char *error_text));
COMPAT_FN_DECL(int DBC_IsNumber,
	(const DBC_CONTEXT *dbc_context_ptr, int dbc_type));
COMPAT_FN_DECL(int DBC_MinNumber,
	(const DBC_CONTEXT *dbc_context_ptr, int dbc_type, double *double_ptr,
	char *error_text));
COMPAT_FN_DECL(int DBC_MaxNumber,
	(const DBC_CONTEXT *dbc_context_ptr, int dbc_type, double *double_ptr,
	char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		The generic DBC attach function prototype . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void DBC_AttachFacility, (DBC_FUNCS *funcs_ptr));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		The context check function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_CheckContext, (const DBC_CONTEXT *dbc_context_ptr,
	char *error_text));
COMPAT_FN_DECL(int DBC_CheckFunction, (const DBC_CONTEXT *dbc_context_ptr,
	const void **func_ptr, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC_FUNCS function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void DBC_INIT_DBCFuncs, (DBC_FUNCS *funcs_ptr));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC_CONTEXT function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void DBC_FREE_DBContext, (DBC_CONTEXT *dbc_context_ptr));
COMPAT_FN_DECL(void DBC_INIT_DBContext, (DBC_CONTEXT *dbc_context_ptr));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC_GETROWS function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void DBC_INIT_DBCGetRows, (DBC_GETROWS *dbc_getrows_ptr));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Memory allocation function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int  DBC_MEMORY_ALLOC_Rows,
	(void *alloc_control_ptr, void **memory_ptr, unsigned int alloc_size));
COMPAT_FN_DECL(int  DBC_MEMORY_REALLOC_Rows,
	(void *alloc_control_ptr, void **memory_ptr, unsigned int old_size,
	unsigned int alloc_size));
COMPAT_FN_DECL(void DBC_MEMORY_FREE_Rows,
	(void *alloc_control_ptr, void **memory_ptr, unsigned int free_size));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		MFILE allocation function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int  DBC_MFILE_ALLOC_Rows,
	(MFILE *alloc_control_ptr, void **memory_ptr, unsigned int alloc_size));
COMPAT_FN_DECL(int  DBC_MFILE_REALLOC_Rows,
	(MFILE *alloc_control_ptr, void **memory_ptr, unsigned int old_size,
	unsigned int alloc_size));
COMPAT_FN_DECL(void DBC_MFILE_FREE_Rows,
	(MFILE *alloc_control_ptr, void **memory_ptr, unsigned int free_size));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Miscellaneous function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(STR_VERSION *DBC_GetVersion, (STR_VERSION *version_number));
COMPAT_FN_DECL(char        *DBC_GetVersionString, (char *version_string));
	/*	*****************************************************************	*/

/*	***********************************************************************	*/

#endif /* #ifndef h__DBCFUNCS_H__h */

