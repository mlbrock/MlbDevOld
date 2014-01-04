/* *********************************************************************** */
/* *********************************************************************** */
/*	Parse Configuration File Facility (PCFF) Library Include File				*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the PCFF library.

	Revision History	:	1999-11-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1999 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

#ifndef h__PCFF_H__h

#define h__PCFF_H__h						1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <strfuncs.h>

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   BASE NAME   :  PCFF Truth Codes

   NAME        :  PCFF Truth Codes

   DESCRIPTION :  Manifest constants used within PCFF to specify the truth
						or falsity of expressions.

						(.) ''PCFF_TRUE''

						(.) ''PCFF_FALSE''

   NOTES       :  The manifest constant ''PCFF_TRUE'' should be defined as
						a non-zero value. Conversely, the manifest constant
						''PCFF_FALSE'' should be defined as zero (''0'').

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1999 - 2014 Michael L. Brock

   OUTPUT INDEX:  PCFF_TRUE
						PCFF_FALSE
						PCFF Truth Codes:PCFF_TRUE
						PCFF Truth Codes:PCFF_FALSE
						PCFF Manifest Constants:PCFF_TRUE
						PCFF Manifest Constants:PCFF_FALSE
						PCFF Defines:PCFF_TRUE
						PCFF Defines:PCFF_FALSE
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:  PCFF Truth Codes
						PCFF Truth Code
						PCFF truth codes
						PCFF truth code
						PCFF_TRUE
						PCFF_FALSE

   PUBLISH NAME:	PCFF Truth Codes
						PCFF_TRUE
						PCFF_FALSE

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define PCFF_TRUE								1
#define PCFF_FALSE							0
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   BASE NAME   :	PCFF Return Codes

   NAME        :  PCFF Return Codes

   DESCRIPTION :  The PCFF return codes have the following meanings:

						(.) ''PCFF_SUCCESS'' means that the function invoked
						completed without error. ''PCFF_SUCCESS'' is guaranteed to
						be equal to zero (''0'').

						(.) ''PCFF_FAILURE'' indicates that the function invoked
						encountered a general operation failure. This is the
						'catch-all' error code for those errors which do not fit
						into category of one the other PCFF error codes.

						(.) ''PCFF_BAD_ARGS_FAILURE'' indicates that the
						arguments passed to a function invoked were invalid.

						(.) ''PCFF_MEMORY_FAILURE'' indicates that the memory
						required for operation of the function invoked could not be
						allocated.

						(.) ''PCFF_SYSTEM_FAILURE'' indicates that the function
						invoked encountered a failure of a standard library
						function or a system call.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1999 - 2014 Michael L. Brock

   OUTPUT INDEX:  PCFF_SUCCESS
						PCFF_FAILURE
						PCFF_BAD_ARGS_FAILURE
						PCFF_MEMORY_FAILURE
						PCFF_SYSTEM_FAILURE
						PCFF Return Codes:PCFF_SUCCESS
						PCFF Return Codes:PCFF_FAILURE
						PCFF Return Codes:PCFF_BAD_ARGS_FAILURE
						PCFF Return Codes:PCFF_MEMORY_FAILURE
						PCFF Return Codes:PCFF_SYSTEM_FAILURE
						PCFF Manifest Constants:PCFF_SUCCESS
						PCFF Manifest Constants:PCFF_FAILURE
						PCFF Manifest Constants:PCFF_BAD_ARGS_FAILURE
						PCFF Manifest Constants:PCFF_MEMORY_FAILURE
						PCFF Manifest Constants:PCFF_SYSTEM_FAILURE
						PCFF Defines:PCFF_SUCCESS
						PCFF Defines:PCFF_FAILURE
						PCFF Defines:PCFF_BAD_ARGS_FAILURE
						PCFF Defines:PCFF_MEMORY_FAILURE
						PCFF Defines:PCFF_SYSTEM_FAILURE
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:  PCFF_SUCCESS
						PCFF_FAILURE
						PCFF_BAD_ARGS_FAILURE
						PCFF_MEMORY_FAILURE
						PCFF_SYSTEM_FAILURE
						PCFF Return Codes
						PCFF Return Code
						PCFF return codes
						PCFF return code
						PCFF Status Codes
						PCFF Status Code
						PCFF status codes
						PCFF status code
						PCFF Error Codes
						PCFF Error Code
						PCFF error codes
						PCFF error code

   PUBLISH NAME:	PCFF Return Codes
						PCFF return codes
						PCFF_SUCCESS
						PCFF_FAILURE
						PCFF_BAD_ARGS_FAILURE
						PCFF_MEMORY_FAILURE
						PCFF_SYSTEM_FAILURE

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define PCFF_SUCCESS							0
#define PCFF_FAILURE						  -1
#define PCFF_BAD_ARGS_FAILURE			  -2
#define PCFF_MEMORY_FAILURE			  -3
#define PCFF_SYSTEM_FAILURE			  -4
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :  PCFF_MAX_ERROR_TEXT

   DESCRIPTION :  The manifest constant ''PCFF_MAX_ERROR_TEXT'' defines
						the minimum amount of storage which should be allocated to
						hold an error message returned by a PCFF function.

   CAVEATS     :  PCFF error messages can be quite lengthy. Therefore,
						attempting to save space by allocating less than
						''PCFF_MAX_ERROR_TEXT'' bytes to error message buffers
						passed to PCFF functions can lead to overwriting of the
						heap or the stack.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1999 - 2014 Michael L. Brock

   OUTPUT INDEX:  PCFF_MAX_ERROR_TEXT
						PCFF Manifest Constants:PCFF_MAX_ERROR_TEXT
						PCFF Defines:PCFF_MAX_ERROR_TEXT
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	PCFF_MAX_ERROR_TEXT

   PUBLISH NAME:	PCFF_MAX_ERROR_TEXT

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define PCFF_MAX_ERROR_TEXT				2048
/*	***********************************************************************	*/

/*
	ADF NOTE:No ADF.
*/
/*	***********************************************************************	*/
#define PCFF_MAP_TRUTH(code)          ((code)  ? PCFF_TRUE : PCFF_FALSE)
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef unsigned long PCFF_FLAG;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define PCFF_FLAG_NONE						((PCFF_FLAG) 0x00000000)
#define PCFF_FLAG_NO_SRC_DEPTH			((PCFF_FLAG) 0x00000001)
#define PCFF_FLAG_NULL_VALUE				((PCFF_FLAG) 0x00000002)
#define PCFF_FLAG_NO_REQUIRE				((PCFF_FLAG) 0x00000004)
#define PCFF_FLAG_UNKNOWN_OK				((PCFF_FLAG) 0x00000008)
#define PCFF_FLAG_STR_TRUNC				((PCFF_FLAG) 0x00000010)
#define PCFF_FLAG_DOMAIN_NULL				((PCFF_FLAG) 0x00000020)
#define PCFF_FLAG_DOMAIN_BAD				((PCFF_FLAG) 0x00000040)
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef enum {
	PCFF_FLD_TYPE_NONE				=  0,
	PCFF_FLD_TYPE_SCHAR				=  1,
	PCFF_FLD_TYPE_UCHAR				=  2,
	PCFF_FLD_TYPE_SSHORT				=  3,
	PCFF_FLD_TYPE_USHORT				=  4,
	PCFF_FLD_TYPE_SINT				=  5,
	PCFF_FLD_TYPE_UINT				=  6,
	PCFF_FLD_TYPE_SLONG				=  7,
	PCFF_FLD_TYPE_ULONG				=  8,
	PCFF_FLD_TYPE_FLOAT				=  9,
	PCFF_FLD_TYPE_DOUBLE				= 10,
	PCFF_FLD_TYPE_BOOLEAN			= 11,
	PCFF_FLD_TYPE_IP_HSP				= 12,
	PCFF_FLD_TYPE_IP_PHS				= 13,
	PCFF_FLD_TYPE_STRING				= 0x00100000,
	PCFF_FLD_TYPE_STRING_PTR		= 0x01000000,
	PCFF_FLD_TYPE_DATE_STR			= 100 | PCFF_FLD_TYPE_STRING,
	PCFF_FLD_TYPE_TIME_STR			= 101 | PCFF_FLD_TYPE_STRING,
	PCFF_FLD_TYPE_TIMEVAL_STR		= 102 | PCFF_FLD_TYPE_STRING,
	PCFF_FLD_TYPE_TIMESPEC_STR		= 103 | PCFF_FLD_TYPE_STRING,
	PCFF_FLD_TYPE_PATH_NAME       = 104 | PCFF_FLD_TYPE_STRING,
	PCFF_FLD_TYPE_PATH_NAME_PTR   = 104 | PCFF_FLD_TYPE_STRING_PTR,
	PCFF_FLD_TYPE_FILE_NAME       = 105 | PCFF_FLD_TYPE_STRING,
	PCFF_FLD_TYPE_FILE_NAME_PTR   = 105 | PCFF_FLD_TYPE_STRING_PTR,
	PCFF_FLD_TYPE_HOST_SPEC       = 106 | PCFF_FLD_TYPE_STRING,
	PCFF_FLD_TYPE_HOST_SPEC_PTR   = 106 | PCFF_FLD_TYPE_STRING_PTR,
	PCFF_FLD_TYPE_SERVICE			= 107 | PCFF_FLD_TYPE_STRING,
	PCFF_FLD_TYPE_SERVICE_PTR		= 107 | PCFF_FLD_TYPE_STRING_PTR,
	PCFF_FLD_TYPE_PROTOCOL			= 108 | PCFF_FLD_TYPE_STRING,
	PCFF_FLD_TYPE_PROTOCOL_PTR		= 108 | PCFF_FLD_TYPE_STRING_PTR
} PCFF_FLD_TYPE;
/*	***********************************************************************	*/

/*
	CODE NOTE: To be moved into 'pcff.h'.
*/
/*	***********************************************************************	*/
/*
	ADF NOTE: Data Types for the PCFF field types

	PCFF_FLD_TYPE_SCHAR					signed char     
	PCFF_FLD_TYPE_UCHAR					unsigned char   
	PCFF_FLD_TYPE_SSHORT					signed short    
	PCFF_FLD_TYPE_USHORT					unsigned short  
	PCFF_FLD_TYPE_SINT					signed int      
	PCFF_FLD_TYPE_UINT					unsigned int    
	PCFF_FLD_TYPE_SLONG					signed long     
	PCFF_FLD_TYPE_ULONG					unsigned long   
	PCFF_FLD_TYPE_FLOAT					float           
	PCFF_FLD_TYPE_DOUBLE					double          
	PCFF_FLD_TYPE_BOOLEAN				int             
	PCFF_FLD_TYPE_STRING					char [???]      
	PCFF_FLD_TYPE_STRING_PTR			char *
	PCFF_FLD_TYPE_DATE_STR				char [SDTIF_DATE_YYYY_MM_DD_LEN + 1]      
	PCFF_FLD_TYPE_TIME_STR				char [SDTIF_TIME_HH_MM_SS_LEN + 1]      
	PCFF_FLD_TYPE_TIMEVAL_STR			char [SDTIF_DATE_TIME_TIMEVAL_LEN + 1]      
	PCFF_FLD_TYPE_TIMESPEC_STR			char [SDTIF_DATE_TIME_TIMESPEC_LEN + 1]      
	PCFF_FLD_TYPE_IP_HSP					PCFF_IP_HSP
	PCFF_FLD_TYPE_IP_PHS					PCFF_IP_HSP
	PCFF_FLD_TYPE_PATH_NAME				char [GEN_MAX_PATH_NAME_LEN + 1]      
	PCFF_FLD_TYPE_PATH_NAME_PTR		char *
	PCFF_FLD_TYPE_FILE_NAME				char [(GEN_MAX_PATH_NAME_LEN * 2) + 1 + 1]      
	PCFF_FLD_TYPE_FILE_NAME_PTR		char *
	PCFF_FLD_TYPE_HOST_SPEC				char [GEN_MAX_HOST_NAME_LEN + 1]      
	PCFF_FLD_TYPE_HOST_SPEC_PTR		char *
	PCFF_FLD_TYPE_SERVICE_STR			char [127 + 1]
	PCFF_FLD_TYPE_SERVICE_PTR			char *
	PCFF_FLD_TYPE_PROTOCOL_STR			char [127 + 1]
	PCFF_FLD_TYPE_PROTOCOL_PTR			char *
*/
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define PCFF_FLD_TYPE_IS_STR(fld_type)	\
	PCFF_MAP_TRUTH((fld_type) & PCFF_FLD_TYPE_STRING)
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define PCFF_FLD_TYPE_IS_PTR(fld_type)	\
	PCFF_MAP_TRUTH((fld_type) & PCFF_FLD_TYPE_STRING_PTR)
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define PCFF_FLD_TYPE_IS_SET(fld_type)											\
	PCFF_MAP_TRUTH(((fld_type) == PCFF_FLD_TYPE_SCHAR)					||	\
						((fld_type) == PCFF_FLD_TYPE_UCHAR)					||	\
						((fld_type) == PCFF_FLD_TYPE_SSHORT)				||	\
						((fld_type) == PCFF_FLD_TYPE_USHORT)				||	\
						((fld_type) == PCFF_FLD_TYPE_SINT)					||	\
						((fld_type) == PCFF_FLD_TYPE_UINT)					||	\
						((fld_type) == PCFF_FLD_TYPE_SLONG)					||	\
						((fld_type) == PCFF_FLD_TYPE_ULONG)					||	\
						((fld_type) == PCFF_FLD_TYPE_FLOAT)					||	\
						((fld_type) == PCFF_FLD_TYPE_DOUBLE)				||	\
						((fld_type) == PCFF_FLD_TYPE_BOOLEAN)				||	\
						((fld_type) == PCFF_FLD_TYPE_IP_HSP)				||	\
						((fld_type) == PCFF_FLD_TYPE_IP_PHS)				||	\
						((fld_type) == PCFF_FLD_TYPE_STRING)				||	\
						((fld_type) == PCFF_FLD_TYPE_STRING_PTR)			||	\
						((fld_type) == PCFF_FLD_TYPE_DATE_STR)				||	\
						((fld_type) == PCFF_FLD_TYPE_TIME_STR)				||	\
						((fld_type) == PCFF_FLD_TYPE_TIMEVAL_STR)			||	\
						((fld_type) == PCFF_FLD_TYPE_TIMESPEC_STR)		||	\
						((fld_type) == PCFF_FLD_TYPE_PATH_NAME)      	||	\
						((fld_type) == PCFF_FLD_TYPE_PATH_NAME_PTR)  	||	\
						((fld_type) == PCFF_FLD_TYPE_FILE_NAME)      	||	\
						((fld_type) == PCFF_FLD_TYPE_FILE_NAME_PTR)  	||	\
						((fld_type) == PCFF_FLD_TYPE_HOST_SPEC)      	||	\
						((fld_type) == PCFF_FLD_TYPE_HOST_SPEC_PTR)		||	\
						((fld_type) == PCFF_FLD_TYPE_SERVICE)				||	\
						((fld_type) == PCFF_FLD_TYPE_SERVICE_PTR)			||	\
						((fld_type) == PCFF_FLD_TYPE_PROTOCOL)				||	\
						((fld_type) == PCFF_FLD_TYPE_PROTOCOL_PTR))
#define PCFF_FLD_TYPE_IS_ANY(fld_type)											\
	PCFF_MAP_TRUTH(((fld_type) == PCFF_FLD_TYPE_NONE)					||	\
						PCFF_FLD_TYPE_IS_SET(fld_type))
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define PCFF_GET_FLD_TYPE_NAME(fld_type)												\
	(((fld_type) == PCFF_FLD_TYPE_NONE)					? "NONE"			   	:	\
	 ((fld_type) == PCFF_FLD_TYPE_SCHAR)				? "SCHAR"		   	:	\
	 ((fld_type) == PCFF_FLD_TYPE_UCHAR)				? "UCHAR"		   	:	\
	 ((fld_type) == PCFF_FLD_TYPE_SSHORT)				? "SSHORT"		   	:	\
	 ((fld_type) == PCFF_FLD_TYPE_USHORT)				? "USHORT"		   	:	\
	 ((fld_type) == PCFF_FLD_TYPE_SINT)					? "SINT"			   	:	\
	 ((fld_type) == PCFF_FLD_TYPE_UINT)					? "UINT"			   	:	\
	 ((fld_type) == PCFF_FLD_TYPE_SLONG)				? "SLONG"		   	:	\
	 ((fld_type) == PCFF_FLD_TYPE_ULONG)				? "ULONG"		   	:	\
	 ((fld_type) == PCFF_FLD_TYPE_FLOAT)				? "FLOAT"		   	:	\
	 ((fld_type) == PCFF_FLD_TYPE_DOUBLE)				? "DOUBLE"		   	:	\
	 ((fld_type) == PCFF_FLD_TYPE_BOOLEAN)				? "BOOLEAN"		   	:	\
	 ((fld_type) == PCFF_FLD_TYPE_IP_HSP)				? "IP_HSP"				:	\
	 ((fld_type) == PCFF_FLD_TYPE_IP_PHS)				? "IP_PHS"				:	\
	 ((fld_type) == PCFF_FLD_TYPE_STRING)				? "STRING"		   	:	\
	 ((fld_type) == PCFF_FLD_TYPE_STRING_PTR)			? "STRING_PTR"	   	:	\
	 ((fld_type) == PCFF_FLD_TYPE_DATE_STR)			? "DATE_STR"	   	:	\
	 ((fld_type) == PCFF_FLD_TYPE_TIME_STR)			? "TIME_STR"	   	:	\
	 ((fld_type) == PCFF_FLD_TYPE_TIMEVAL_STR)		? "TIMEVAL_STR"   	:	\
	 ((fld_type) == PCFF_FLD_TYPE_TIMESPEC_STR)		? "TIMESPEC_STR"  	:	\
	 ((fld_type) == PCFF_FLD_TYPE_PATH_NAME)     	? "PATH_NAME"     	:	\
	 ((fld_type) == PCFF_FLD_TYPE_PATH_NAME_PTR) 	? "PATH_NAME_PTR" 	:	\
	 ((fld_type) == PCFF_FLD_TYPE_FILE_NAME)     	? "FILE_NAME"     	:	\
	 ((fld_type) == PCFF_FLD_TYPE_FILE_NAME_PTR) 	? "FILE_NAME_PTR" 	:	\
	 ((fld_type) == PCFF_FLD_TYPE_HOST_SPEC)     	? "HOST_SPEC"     	:	\
	 ((fld_type) == PCFF_FLD_TYPE_HOST_SPEC_PTR)		? "HOST_SPEC_PTR" 	:	\
	 ((fld_type) == PCFF_FLD_TYPE_SERVICE)				? "SERVICE"				:	\
	 ((fld_type) == PCFF_FLD_TYPE_SERVICE_PTR)		? "SERVICE_PTR"		:	\
	 ((fld_type) == PCFF_FLD_TYPE_PROTOCOL)			? "PROTOCOL"			:	\
	 ((fld_type) == PCFF_FLD_TYPE_PROTOCOL_PTR)		? "PROTOCOL_PTR"		:	\
	 NULL)
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define PCFF_GET_FLD_TYPE_NAME_LONG(fld_type)																\
	(((fld_type) == PCFF_FLD_TYPE_NONE)          	? "none"                              :	\
	 ((fld_type) == PCFF_FLD_TYPE_SCHAR)         	? "signed char"                       :	\
	 ((fld_type) == PCFF_FLD_TYPE_UCHAR)         	? "unsigned char"                     :	\
	 ((fld_type) == PCFF_FLD_TYPE_SSHORT)        	? "signed short"	                    :	\
	 ((fld_type) == PCFF_FLD_TYPE_USHORT)				? "unsigned short"                    :	\
	 ((fld_type) == PCFF_FLD_TYPE_SINT)					? "signed int"                        :	\
	 ((fld_type) == PCFF_FLD_TYPE_UINT)					? "unsigned int"     	              :	\
	 ((fld_type) == PCFF_FLD_TYPE_SLONG)				? "signed long"                       :	\
	 ((fld_type) == PCFF_FLD_TYPE_ULONG)				? "unsigned long"                     :	\
	 ((fld_type) == PCFF_FLD_TYPE_FLOAT)				? "float"                             :	\
	 ((fld_type) == PCFF_FLD_TYPE_DOUBLE)				? "double"                            :	\
	 ((fld_type) == PCFF_FLD_TYPE_BOOLEAN)				? "boolean"                           :	\
	 ((fld_type) == PCFF_FLD_TYPE_IP_HSP)				? "ip host-service-protocol"			  :	\
	 ((fld_type) == PCFF_FLD_TYPE_IP_PHS)				? "ip protocol-host-service"			  :	\
	 ((fld_type) == PCFF_FLD_TYPE_STRING)				? "string array"                      :	\
	 ((fld_type) == PCFF_FLD_TYPE_STRING_PTR)			? "string pointer"                    :	\
	 ((fld_type) == PCFF_FLD_TYPE_DATE_STR)			? "date string array"                 :	\
	 ((fld_type) == PCFF_FLD_TYPE_TIME_STR)			? "time string array"                 :	\
	 ((fld_type) == PCFF_FLD_TYPE_TIMEVAL_STR)		? "struct timeval string array"       :	\
	 ((fld_type) == PCFF_FLD_TYPE_TIMESPEC_STR)		? "struct timespec string array"      :	\
	 ((fld_type) == PCFF_FLD_TYPE_PATH_NAME)     	? "path name string array"            :	\
	 ((fld_type) == PCFF_FLD_TYPE_PATH_NAME_PTR) 	? "path name string pointer"          :	\
	 ((fld_type) == PCFF_FLD_TYPE_FILE_NAME)     	? "file name string array"            :	\
	 ((fld_type) == PCFF_FLD_TYPE_FILE_NAME_PTR) 	? "file name string pointer"          :	\
	 ((fld_type) == PCFF_FLD_TYPE_HOST_SPEC)     	? "host specification string array"   :	\
	 ((fld_type) == PCFF_FLD_TYPE_HOST_SPEC_PTR)		? "host specification string pointer" :	\
	 ((fld_type) == PCFF_FLD_TYPE_SERVICE)				? "ip service"								  :	\
	 ((fld_type) == PCFF_FLD_TYPE_SERVICE_PTR)		? "ip service pointer"					  :	\
	 ((fld_type) == PCFF_FLD_TYPE_PROTOCOL)			? "ip protocol"							  :	\
	 ((fld_type) == PCFF_FLD_TYPE_PROTOCOL_PTR)		? "ip protocol pointer"					  :	\
	 NULL)
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef unsigned long PCFF_EMIT_ADF_FLAG;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define PCFF_EMIT_ADF_FLAG_NONE			((PCFF_EMIT_ADF_FLAG) 0x00000000)
#define PCFF_EMIT_ADF_FLAG_TYPE			((PCFF_EMIT_ADF_FLAG) 0x00000001)
#define PCFF_EMIT_ADF_FLAG_MEMBER		((PCFF_EMIT_ADF_FLAG) 0x00000002)
#define PCFF_EMIT_ADF_FLAG_STR_LEN		((PCFF_EMIT_ADF_FLAG) 0x00000004)
#define PCFF_EMIT_ADF_FLAG_STR_PTR_LEN	((PCFF_EMIT_ADF_FLAG) 0x00000008)
#define PCFF_EMIT_ADF_FLAG_RANGE			((PCFF_EMIT_ADF_FLAG) 0x00000010)
#define PCFF_EMIT_ADF_FLAG_DEFAULT		((PCFF_EMIT_ADF_FLAG) 0x00000020)
#define PCFF_EMIT_ADF_FLAG_OPT_REQ		((PCFF_EMIT_ADF_FLAG) 0x00000040)
#define PCFF_EMIT_ADF_FLAG_ALL			(PCFF_EMIT_ADF_FLAG_TYPE |	\
	PCFF_EMIT_ADF_FLAG_MEMBER | PCFF_EMIT_ADF_FLAG_STR_LEN | 		\
	PCFF_EMIT_ADF_FLAG_STR_PTR_LEN | PCFF_EMIT_ADF_FLAG_RANGE |		\
	PCFF_EMIT_ADF_FLAG_DEFAULT | PCFF_EMIT_ADF_FLAG_OPT_REQ)
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef unsigned long PCFF_PARAM_FLAG;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define PCFF_PARAM_FLAG_NONE				((PCFF_PARAM_FLAG) 0x00000000)
#define PCFF_PARAM_FLAG_STR_TRUNC		((PCFF_PARAM_FLAG) 0x00000001)
#define PCFF_PARAM_FLAG_DOMAIN_NULL		((PCFF_PARAM_FLAG) 0x00000002)
#define PCFF_PARAM_FLAG_DOMAIN_BAD		((PCFF_PARAM_FLAG) 0x00000004)
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef struct {
	unsigned int  line_number;
	char         *file_name;
	char         *value;
} PCFF_SRC;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef struct {
	char          *name;
	char          *value;
	unsigned long  order;
	unsigned int   src_count;
	PCFF_SRC      *src_list;
} PCFF_ITEM;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef struct {
	unsigned int  item_count;
	PCFF_ITEM    *item_list;
} PCFF_CFG;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef struct {
	PCFF_FLAG      flags;
	char          *name_left;
	char          *name_right;
	char          *value_left;
	char          *value_right;
	unsigned int   required_count;
	char         **required_list;
	unsigned int   optional_count;
	char         **optional_list;
} PCFF_PARSE_SPEC;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef struct {
	char           *param_name;
	char           *member_name;
	PCFF_FLD_TYPE   field_type;
	unsigned int    field_offset;
	unsigned int    field_length;
	PCFF_PARAM_FLAG flags;
	unsigned int    ref_index;
	char           *description;
	char           *domain;
	unsigned int    tmp_original_index;
	unsigned int    domain_count;
	char          **domain_list;
} PCFF_PARAM;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef struct {
	unsigned int  structure_size;
	unsigned int  param_count;
	PCFF_PARAM   *param_list;
} PCFF_PARAM_SPEC;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef struct {
	char *spec_string;
	char *host_name;
	char *service_name;
	int   service_number;
	char *protocol_name;
	int   protocol_number;
} PCFF_IP_HSP;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define PCFF_STATIC_INIT_IP_HSP(spec_string)	\
	{ (spec_string), NULL, NULL, 0, NULL, 0 }
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#ifdef NO_CPP_STRINGIZE
# define PCFF_DEFINE_PARAM(sname, pname, mname, ftype, flags, ref, descrip,	\
		fdomain)	\
	{ (pname), "*?MEMBER-NAME?*", (ftype), offsetof(sname, mname),					\
		STR_sizeof(sname, mname), (flags), (ref), (descrip), (fdomain), 0,		\
		0, NULL }
#else
# define PCFF_DEFINE_PARAM(sname, pname, mname, ftype, flags, ref, descrip,	\
		fdomain)	\
	{ (pname), #mname, (ftype), offsetof(sname, mname),								\
		STR_sizeof(sname, mname), (flags), (ref), (descrip), (fdomain), 0,		\
		0, NULL }
#endif /* #ifdef NO_CPP_STRINGIZE */
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define PCFF_ADF_SECTION_NAME				0
#define PCFF_ADF_SECTION_SYNOP			1
#define PCFF_ADF_SECTION_DESCRIP			2
#define PCFF_ADF_SECTION_PARAMS			3
#define PCFF_ADF_SECTION_ENVIRON			4
#define PCFF_ADF_SECTION_NOTES			5
#define PCFF_ADF_SECTION_CAVEATS			6
#define PCFF_ADF_SECTION_SEE_ALSO		7
#define PCFF_ADF_SECTION_EXAMPLES		8
#define PCFF_ADF_SECTION_AUTHOR			9
#define PCFF_ADF_SECTION_COPYRIGHT		10
#define PCFF_ADF_SECTION_OUT_INDEX		11
#define PCFF_ADF_SECTION_PUB_XREF		12
#define PCFF_ADF_SECTION_PUB_NAME		13
#define PCFF_ADF_SECTION_ENTRY_CLASS	14
#define PCFF_ADF_SECTION_COUNT			15
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Function prototypes for functions defined within 'tfread.a' . . .		*/
/*	***********************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Configuration load from file function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int PCFF_LoadFromFile,
	(PCFF_CFG *cfg_ptr, PCFF_FLAG flags, const char *in_file,
	char *error_text));
COMPAT_FN_DECL(int PCFF_AppendFromFile,
	(PCFF_CFG *cfg_ptr, PCFF_FLAG flags, const char *in_file,
	char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Configuration load from memory list function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int PCFF_LoadFromList,
	(PCFF_CFG *cfg_ptr, PCFF_FLAG flags, const char *in_source,
	unsigned int in_line_count, char **in_line_list, char *error_text));
COMPAT_FN_DECL(int PCFF_AppendFromList,
	(PCFF_CFG *cfg_ptr, PCFF_FLAG flags, const char *in_source,
	unsigned int in_line_count, char **in_line_list, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Post-processing function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int PCFF_PostProcess,
	(PCFF_CFG *cfg_ptr, PCFF_PARSE_SPEC *parse_spec_ptr, char *error_text));
COMPAT_FN_DECL(int PCFF_PostProcessBasic,
	(PCFF_CFG *cfg_ptr, PCFF_FLAG flags, const char *name_left,
	const char *name_right, const char *value_left, const char *value_right,
	unsigned int required_count, char **required_list,
	unsigned int optional_count, char **optional_list,char *error_text));
COMPAT_FN_DECL(int PCFF_FixDelimiters,
	(PCFF_CFG *cfg_ptr, PCFF_PARSE_SPEC *parse_spec_ptr, char *error_text));
COMPAT_FN_DECL(int PCFF_FixDelimitersBasic,
	(PCFF_CFG *cfg_ptr, const char *name_left, const char *name_right,
	const char *value_left, const char *value_right, char *error_text));
COMPAT_FN_DECL(int PCFF_CheckDelimiters,
	(PCFF_CFG *cfg_ptr, PCFF_PARSE_SPEC *parse_spec_ptr, char *error_text));
COMPAT_FN_DECL(int PCFF_CheckDelimitersBasic,
	(PCFF_CFG *cfg_ptr, const char *name_left, const char *name_right,
	const char *value_left, const char *value_right, char *error_text));
COMPAT_FN_DECL(void PCFF_FlattenItems,
	(PCFF_CFG *cfg_ptr));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Final parameter data function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int PCFF_CreateParamSpec,
	(unsigned int structure_size, unsigned int param_count,
	const PCFF_PARAM *param_list, PCFF_PARAM_SPEC *param_spec_ptr,
	char *error_text));
COMPAT_FN_DECL(int PCFF_DoParams,
	(const PCFF_CFG *cfg_ptr, PCFF_FLAG flags,
	const PCFF_PARAM_SPEC *param_spec_ptr, void *out_data_ptr,
	char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Emit parameter specification function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int PCFF_EmitADFParamSpec,
	(const PCFF_PARAM_SPEC *param_spec_ptr,
	const PCFF_PARSE_SPEC *parse_spec_ptr, const void *data_ptr,
	const char *structure_name, char **adf_section_list,
	PCFF_EMIT_ADF_FLAG emit_flags, char *error_text));
COMPAT_FN_DECL(int PCFF_EmitADFParamSpecBasic,
	(const PCFF_PARAM_SPEC *param_spec_ptr,
	const PCFF_PARSE_SPEC *parse_spec_ptr, const void *data_ptr,
	const char *structure_name, char **adf_section_list,
	PCFF_EMIT_ADF_FLAG emit_flags, STR_FUNC_TYPE_fprintf output_function,
	void *output_control, char *error_text));
COMPAT_FN_DECL(void PCFF_EmitParamSpecData,
	(const PCFF_CFG *cfg_ptr, const PCFF_PARAM_SPEC *param_spec_ptr,
	const void *data_ptr, int full_flag, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(void PCFF_EmitParamSpecDataBasic,
	(const PCFF_CFG *cfg_ptr, const PCFF_PARAM_SPEC *param_spec_ptr,
	const void *data_ptr, int full_flag, int (*output_function_lead)(void *),
	STR_FUNC_TYPE_fprintf output_function_text, void *output_control));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Check parameter and parameter specification function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int PCFF_CheckParamSpec,
	(const PCFF_PARAM_SPEC *param_spec_ptr, char *error_text));
COMPAT_FN_DECL(int PCFF_CheckParamList,
	(unsigned int param_count, const PCFF_PARAM *param_list, char *error_text));
COMPAT_FN_DECL(int PCFF_CheckParam,
	(const PCFF_PARAM *param_ptr, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Manage command line parameter parsing function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int PCFF_CMLPARAM_LocateHelp,
	(int argc, char **argv, const char **found_ptr));
COMPAT_FN_DECL(int PCFF_CMLPARAM_LocateVersion,
	(int argc, char **argv, const char **found_ptr));
#ifndef NO_STDARGS
COMPAT_FN_DECL(int PCFF_CMLPARAM_FindVA,
	(const char *arg_name, const char **found_ptr, ...));
#else
COMPAT_FN_DECL(int PCFF_CMLPARAM_FindVA,
	(const char *arg_name, const char **found_ptr, va_alist));
#endif /* #ifndef NO_STDARGS */
COMPAT_FN_DECL(int PCFF_CMLPARAM_FindOrdered,
	(unsigned int param_count, char **param_list, const char *arg_name,
	const char **found_ptr));
COMPAT_FN_DECL(int PCFF_CMLPARAM_FindOrderedIdx,
	(unsigned int param_count, char **param_list, const char *arg_name,
	unsigned int *found_index));
COMPAT_FN_DECL(int PCFF_CMLPARAM_FindUnordered,
	(unsigned int param_count, char **param_list, const char *arg_name,
	const char **found_ptr));
COMPAT_FN_DECL(int PCFF_CMLPARAM_FindUnorderedIdx,
	(unsigned int param_count, char **param_list, const char *arg_name,
	unsigned int *found_index));
COMPAT_FN_DECL(int PCFF_CMLPARAM_FindTerminated,
	(char **param_list, const char *arg_name, const char **found_ptr));
COMPAT_FN_DECL(int PCFF_CMLPARAM_FindTerminatedIdx,
	(char **param_list, const char *arg_name, unsigned int *found_index));
COMPAT_FN_DECL(int PCFF_CMLPARAM_FindFollowing,
	(int argc, char **argv, const char *param_name, PCFF_FLD_TYPE param_type,
	int required_flag, int is_multiple, unsigned int *found_index,
	char **out_ptr, char *error_text));
COMPAT_FN_DECL(int PCFF_CMLPARAM_Check,
	(int argc, unsigned int argv_index, char **argv, int is_multiple,
	char *error_text));
COMPAT_FN_DECL(int PCFF_CMLPARAM_CheckFollowing,
	(int argc, unsigned int argv_index, char **argv, char *error_text));
COMPAT_FN_DECL(int PCFF_CMLPARAM_IsMultiple,
	(unsigned int argv_index, char **argv, int is_multiple, char *error_text));
COMPAT_FN_DECL(int PCFF_CMLPARAM_GetFollowing,
	(int argc, unsigned int argv_index, char **argv, PCFF_FLD_TYPE param_type,
	int is_multiple, char **out_ptr, char *error_text));
COMPAT_FN_DECL(int PCFF_CMLPARAM_GetParam,
	(const char *param_name, const char *param_value, PCFF_FLD_TYPE param_type,
	char **out_ptr, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Get parameter descriptive text function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(char *PCFF_GetParamText,
	(const PCFF_PARAM *param_ptr, char *param_text));
COMPAT_FN_DECL(char *PCFF_GetParamTextIndex,
	(const PCFF_PARAM *param_ptr, unsigned int param_index, char *param_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Optional and required name checking function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int PCFF_CheckUnknownList,
	(const PCFF_CFG *cfg_ptr, PCFF_PARSE_SPEC *parse_spec_ptr,
	char *error_text));
COMPAT_FN_DECL(int PCFF_CheckUnknownListBasic,
	(const PCFF_CFG *cfg_ptr,  unsigned int required_count,
	char **required_list, unsigned int optional_count, char **optional_list,
	char *error_text));
COMPAT_FN_DECL(int PCFF_CheckRequiredList,
	(PCFF_CFG *cfg_ptr, PCFF_PARSE_SPEC *parse_spec_ptr, char *error_text));
COMPAT_FN_DECL(int PCFF_CheckRequiredListBasic,
	(PCFF_CFG *cfg_ptr, unsigned int required_count, char **required_list,
	char *error_text));
COMPAT_FN_DECL(int PCFF_CheckRequired,
	(PCFF_CFG *cfg_ptr, const char *name, char *error_text));
COMPAT_FN_DECL(int PCFF_GetUnknownList,
	(const PCFF_CFG *in_cfg_ptr, PCFF_PARSE_SPEC *parse_spec_ptr,
	PCFF_CFG *out_cfg_ptr, char *error_text));
COMPAT_FN_DECL(int PCFF_GetUnknownListBasic,
	(const PCFF_CFG *in_cfg_ptr, unsigned int required_count,
	char **required_list, unsigned int optional_count, char **optional_list,
	PCFF_CFG *out_cfg_ptr, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Add structure function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int PCFF_AddItem,
	(PCFF_CFG *cfg_ptr, PCFF_FLAG flags, const char *file_name,
	unsigned int line_number, const char *name, const char *value,
	char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Copy structure function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int PCFF_CopyCfg,
	(const PCFF_CFG *in_ptr, PCFF_CFG *out_ptr, char *error_text));
COMPAT_FN_DECL(int PCFF_CopyCfgList,
	(unsigned int in_count, const PCFF_CFG *in_list, unsigned int *out_count,
	PCFF_CFG **out_list, char *error_text));
COMPAT_FN_DECL(int PCFF_CopyHostServProto,
	(const PCFF_IP_HSP *in_ptr, PCFF_IP_HSP *out_ptr, char *error_text));
COMPAT_FN_DECL(int PCFF_CopyHostServProtoList,
	(unsigned int in_count, const PCFF_IP_HSP *in_list, unsigned int *out_count,
	PCFF_IP_HSP **out_list, char *error_text));
COMPAT_FN_DECL(int PCFF_CopyItem,
	(const PCFF_ITEM *in_ptr, PCFF_ITEM *out_ptr, char *error_text));
COMPAT_FN_DECL(int PCFF_CopyItemList,
	(unsigned int in_count, const PCFF_ITEM *in_list, unsigned int *out_count,
	PCFF_ITEM **out_list, char *error_text));
COMPAT_FN_DECL(int PCFF_CopyParam,
	(const PCFF_PARAM *in_ptr, PCFF_PARAM *out_ptr,
	char *error_text));
COMPAT_FN_DECL(int PCFF_CopyParamList,
	(unsigned int in_count, const PCFF_PARAM *in_list,
	unsigned int *out_count, PCFF_PARAM **out_list, char *error_text));
COMPAT_FN_DECL(int PCFF_CopyParamSpec,
	(const PCFF_PARAM_SPEC *in_ptr,
	PCFF_PARAM_SPEC *out_ptr, char *error_text));
COMPAT_FN_DECL(int PCFF_CopyParamSpecList,
	(unsigned int in_count,
	const PCFF_PARAM_SPEC *in_list, unsigned int *out_count,
	PCFF_PARAM_SPEC **out_list, char *error_text));
COMPAT_FN_DECL(int PCFF_CopySrc,
	(const PCFF_SRC *in_ptr, PCFF_SRC *out_ptr, char *error_text));
COMPAT_FN_DECL(int PCFF_CopySrcList,
	(unsigned int in_count, const PCFF_SRC *in_list, unsigned int *out_count,
	PCFF_SRC **out_list, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Delete structure element from list function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int PCFF_DeleteItem,
	(PCFF_CFG *cfg_ptr, unsigned int item_index, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Find structure element in list function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(const PCFF_ITEM *PCFF_FindItem,
	(const PCFF_CFG *cfg_ptr, const char *item_name,
	unsigned int *found_index));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Free structure function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void PCFF_FreeCfg,
	(PCFF_CFG *ptr));
COMPAT_FN_DECL(void PCFF_FreeCfgList,
	(unsigned int *in_count, PCFF_CFG **in_list));
COMPAT_FN_DECL(void PCFF_FreeHostServProto,
	(PCFF_IP_HSP *ptr));
COMPAT_FN_DECL(void PCFF_FreeHostServProtoList,
	(unsigned int *in_count, PCFF_IP_HSP **in_list));
COMPAT_FN_DECL(void PCFF_FreeItem,
	(PCFF_ITEM *ptr));
COMPAT_FN_DECL(void PCFF_FreeItemList,
	(unsigned int *in_count, PCFF_ITEM **in_list));
COMPAT_FN_DECL(void PCFF_FreeParam,
	(PCFF_PARAM *ptr));
COMPAT_FN_DECL(void PCFF_FreeParamList,
	(unsigned int *in_count, PCFF_PARAM **in_list));
COMPAT_FN_DECL(void PCFF_FreeParamSpec,
	(PCFF_PARAM_SPEC *ptr));
COMPAT_FN_DECL(void PCFF_FreeParamSpecList,
	(unsigned int *in_count, PCFF_PARAM_SPEC **in_list));
COMPAT_FN_DECL(void PCFF_FreeSrc,
	(PCFF_SRC *ptr));
COMPAT_FN_DECL(void PCFF_FreeSrcList,
	(unsigned int *in_count, PCFF_SRC **in_list));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Initialize structure function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void PCFF_InitCfg,
	(PCFF_CFG *ptr));
COMPAT_FN_DECL(void PCFF_InitCfgList,
	(unsigned int in_count, PCFF_CFG *in_list));
COMPAT_FN_DECL(void PCFF_InitHostServProto,
	(PCFF_IP_HSP *ptr));
COMPAT_FN_DECL(void PCFF_InitHostServProtoList,
	(unsigned int in_count, PCFF_IP_HSP *in_list));
COMPAT_FN_DECL(void PCFF_InitItem,
	(PCFF_ITEM *ptr));
COMPAT_FN_DECL(void PCFF_InitItemList,
	(unsigned int in_count, PCFF_ITEM *in_list));
COMPAT_FN_DECL(void PCFF_InitParam,
	(PCFF_PARAM *ptr));
COMPAT_FN_DECL(void PCFF_InitParamList,
	(unsigned int in_count, PCFF_PARAM *in_list));
COMPAT_FN_DECL(void PCFF_InitParamSpec,
	(PCFF_PARAM_SPEC *ptr));
COMPAT_FN_DECL(void PCFF_InitParamSpecList,
	(unsigned int in_count, PCFF_PARAM_SPEC *in_list));
COMPAT_FN_DECL(void PCFF_InitParse,
	(PCFF_PARSE_SPEC *ptr));
COMPAT_FN_DECL(void PCFF_InitParseList,
	(unsigned int in_count, PCFF_PARSE_SPEC *in_list));
COMPAT_FN_DECL(void PCFF_InitSrc,
	(PCFF_SRC *ptr));
COMPAT_FN_DECL(void PCFF_InitSrcList,
	(unsigned int in_count, PCFF_SRC *in_list));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Compare structure function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int PCFF_ParamCompare,
	(void *control_ptr, PCFF_PARAM *ptr_1, PCFF_PARAM *ptr_2,
	size_t data_length));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Sort structure list function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void PCFF_SortCfgByName,
	(PCFF_CFG *cfg_ptr));
COMPAT_FN_DECL(void PCFF_SortCfgByOrder,
	(PCFF_CFG *cfg_ptr));
COMPAT_FN_DECL(void PCFF_SortParamList,
	(unsigned int param_count, PCFF_PARAM *param_list));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Function prototypes for miscellaneous supporting functions . . .
		*****************************************************************	*/
COMPAT_FN_DECL(unsigned int PCFF_GetLongestName,
	(const PCFF_CFG *cfg_ptr));
COMPAT_FN_DECL(unsigned int PCFF_GetLongestValue,
	(const PCFF_CFG *cfg_ptr));
COMPAT_FN_DECL(unsigned int PCFF_GetLongestLineNumber,
	(const PCFF_CFG *cfg_ptr));
COMPAT_FN_DECL(unsigned int PCFF_GetLongestFileName,
	(const PCFF_CFG *cfg_ptr));
COMPAT_FN_DECL(unsigned int PCFF_GetLongestMemberName,
	(const PCFF_PARAM_SPEC *param_spec_ptr));
	/*	*****************************************************************	*/

/*	***********************************************************************	*/

#endif /* #ifndef h__PCFF_H__h */

