/* *********************************************************************** */
/* *********************************************************************** */
/*	Data Type Alignment (DTA) Functions Library Source Module					*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Contains the primitive type definitions for the
								current platform and functions to access those
								definitions.

	Revision History	:	1992-02-23 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Include necessary header files . . .											*/
/* *********************************************************************** */

#include "dtai.h"

/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   NAME        :  DTA_TypeList

   DESCRIPTION :  ``DTA_TypeList`` is the built-in array of
						''DTA_TYPE'' structures which define the primitive
						data types available on the machine.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  DTA_TypeCount

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2014 Michael L. Brock

   OUTPUT INDEX:  DTA_TypeList
						Data Type Alignment Data:DTA_TypeList
						DTA:Data:DTA_TypeList
						DTA:Data Type Alignment Data:DTA_TypeList

   PUBLISH XREF:  DTA_TypeList

   PUBLISH NAME:	DTA_TypeList

	ENTRY CLASS	:	Data Type Alignment Data

EOH */
/*	***********************************************************************	*/
typedef COMPAT_FN_TYPE(bool_t (*DTA_XDR_FUNC), (XDR *xdr_ptr, void *datum));
	/*	*****************************************************************
		*****************************************************************
		The array below describes the alignment requirements of the various
		primitive C data types.
		*****************************************************************	*/
const DTA_TYPE DTA_TypeList[] = {
	{	"unsigned byte",	"ubyte",	DTA_C_char_unsigned_byte,	STR_ALIGN_UCHAR,
		sizeof(unsigned char),	"%c",			 1,
		STR_CMP_FUNC_CAST(DTA_SCMP_ubyte), ((DTA_XDR_FUNC) xdr_char) 		},
	{	"signed char",		"schar",	DTA_C_char_char,				STR_ALIGN_SCHAR,
		sizeof(char),				"%c",			 1,
		STR_CMP_FUNC_CAST(DTA_SCMP_char), ((DTA_XDR_FUNC) xdr_char)			},
	{	"unsigned char",	"uchar",	DTA_C_char_unsigned_char,	STR_ALIGN_UCHAR,
		sizeof(unsigned char),	"%c",			 1,
		STR_CMP_FUNC_CAST(DTA_SCMP_uchar), ((DTA_XDR_FUNC) xdr_u_char)		},
	{	"signed short",	"sshort",DTA_C_char_short,				STR_ALIGN_SSHORT,
		sizeof(short),				"%6hd",		 6,
		STR_CMP_FUNC_CAST(DTA_SCMP_short), ((DTA_XDR_FUNC) xdr_short)		},
	{	"unsigned short",	"ushort",DTA_C_char_unsigned_short,	STR_ALIGN_USHORT,
		sizeof(unsigned short),	"%5hu",		 5,
		STR_CMP_FUNC_CAST(DTA_SCMP_ushort), ((DTA_XDR_FUNC) xdr_u_short)	},
#ifndef __MSDOS__
	{	"signed int",		"sint",	DTA_C_char_int,				STR_ALIGN_SINT,
		sizeof(int),				"%11d",		11,
		STR_CMP_FUNC_CAST(DTA_SCMP_int), ((DTA_XDR_FUNC) xdr_int)			},
	{	"unsigned int",	"uint",	DTA_C_char_unsigned_int,	STR_ALIGN_UINT,
		sizeof(unsigned int),	"%10u",		10,
		STR_CMP_FUNC_CAST(DTA_SCMP_uint), ((DTA_XDR_FUNC) xdr_u_int)		},
#else
	{	"signed int",		"sint",	DTA_C_char_int,				STR_ALIGN_SINT,
		sizeof(int),				"%6d",		 6,
		STR_CMP_FUNC_CAST(DTA_SCMP_int), ((DTA_XDR_FUNC) xdr_short)			},
	{	"unsigned int",	"uint",	DTA_C_char_unsigned_int,	STR_ALIGN_UINT,
		sizeof(unsigned int),	"%5u",		 5,
		STR_CMP_FUNC_CAST(DTA_SCMP_uint), ((DTA_XDR_FUNC) xdr_u_short)		},
#endif /* #ifndef __MSDOS__ */
	{	"signed long",		"slong",	DTA_C_char_long,				STR_ALIGN_SLONG,
		sizeof(long),				"%11d",		11,
		STR_CMP_FUNC_CAST(DTA_SCMP_long), ((DTA_XDR_FUNC) xdr_long)			},
	{	"unsigned long",	"ulong",	DTA_C_char_unsigned_long,	STR_ALIGN_ULONG,
		sizeof(unsigned long),	"%10u",		10,
		STR_CMP_FUNC_CAST(DTA_SCMP_ulong), ((DTA_XDR_FUNC) xdr_u_long)		},
	{	"float",				"float",	DTA_C_char_float,				STR_ALIGN_FLOAT,
		sizeof(float),				"%14.4f",	14,
		STR_CMP_FUNC_CAST(DTA_SCMP_float), ((DTA_XDR_FUNC) xdr_float)		},
	{	"double",			"double",DTA_C_char_double,			STR_ALIGN_DOUBLE,
		sizeof(double),			"%14.4lf",	14,
		STR_CMP_FUNC_CAST(DTA_SCMP_double), ((DTA_XDR_FUNC) xdr_double)	}
};
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   NAME        :  DTA_TypeCount

   DESCRIPTION :  ``DTA_TypeCount`` is the number of elements in the
						array ``DTA_TypeList``, which is the built-in array of
						''DTA_TYPE'' structures defining the primitive data
						types available on the machine.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  DTA_TypeList

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2014 Michael L. Brock

   OUTPUT INDEX:  DTA_TypeCount
						Data Type Alignment Data:DTA_TypeCount
						DTA:Data:DTA_TypeCount
						DTA:Data Type Alignment Data:DTA_TypeCount

   PUBLISH XREF:  DTA_TypeCount

   PUBLISH NAME:	DTA_TypeCount

	ENTRY CLASS	:	Data Type Alignment Data

EOH */
/*	***********************************************************************	*/
const unsigned int DTA_TypeCount =
	(sizeof(DTA_TypeList) / sizeof(DTA_TypeList[0]));
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
void DTA_GetTypeInfo(unsigned int *type_count, const DTA_TYPE **type_list)
#else
void DTA_GetTypeInfo(type_count, type_list)
unsigned int    *type_count;
const DTA_TYPE **type_list;
#endif /* #ifndef NARGS */
{
	if ((!(*type_count)) && (*type_list == NULL))
		DTA_GetDefaultTypeInfo(type_count, type_list);
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
void DTA_GetDefaultTypeInfo(unsigned int *type_count,
	const DTA_TYPE **type_list)
#else
void DTA_GetDefaultTypeInfo(type_count, type_list)
unsigned int    *type_count;
const DTA_TYPE **type_list;
#endif /* #ifndef NARGS */
{
	*type_count = DTA_TypeCount;
	*type_list  = DTA_TypeList;
}
/* *********************************************************************** */

