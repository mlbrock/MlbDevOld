/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Generalized Support Functions Library Internal Header File				*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Internal include file for the DBC generalized
								support functions library.

	Revision History	:	1993-07-07 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__DBCFUNCI_H__h

#define h__DBCFUNCI_H__h					1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Include necessary header files . . .												*/
/*	***********************************************************************	*/

#include "dbcfuncs.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	DBC Library Version Number

   NAME        :	DBC Library Version Number

   DESCRIPTION :	The DBC library version number manifest constants together
						define the current version number of the DBC library as a
						whole.

						(.) ''DBC_VERSION_MAJOR'' represents the major component of
						the library version number.

						(.) ''DBC_VERSION_MINOR'' represents the minor component of
						the library version number.

						(.) ''DBC_VERSION_RELEASE'' represents the release component
						of the library version number.

						(.) ''DBC_VERSION_BUILD'' represents the build level
						component of the library version number.

   SEE ALSO    :	STR_VERSION

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2014 Michael L. Brock

   OUTPUT INDEX:	DBC_VERSION_MAJOR
						DBC_VERSION_MINOR
						DBC_VERSION_RELEASE
						DBC_VERSION_BUILD
						DBC Version Numbers:Library Version Number
						DBC Library Version Number:DBC_VERSION_MAJOR
						DBC Library Version Number:DBC_VERSION_MINOR
						DBC Library Version Number:DBC_VERSION_RELEASE
						DBC Library Version Number:DBC_VERSION_BUILD
						DBC Macros and Manifest Constants:DBC_VERSION_MAJOR
						DBC Macros and Manifest Constants:DBC_VERSION_MINOR
						DBC Macros and Manifest Constants:DBC_VERSION_RELEASE
						DBC Macros and Manifest Constants:DBC_VERSION_BUILD
						Macros and Manifest Constants:DBC_VERSION_MAJOR
						Macros and Manifest Constants:DBC_VERSION_MINOR
						Macros and Manifest Constants:DBC_VERSION_RELEASE
						Macros and Manifest Constants:DBC_VERSION_BUILD
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	DBC_VERSION_MAJOR
						DBC_VERSION_MINOR
						DBC_VERSION_RELEASE
						DBC_VERSION_BUILD
						DBC Library Version Number
						DBC library version number
						DBC Library Version
						DBC library version
						DBC Version Number
						DBC version number
						DBC Version
						DBC version

   PUBLISH NAME:	DBC_VERSION_MAJOR
						DBC_VERSION_MINOR
						DBC_VERSION_RELEASE
						DBC_VERSION_BUILD

	ENTRY CLASS	:	Macros and Manifest Constants:Library Version Number
						DBC Version Numbers:Library Version Number

EOH */
/*	***********************************************************************	*/
#define DBC_VERSION_MAJOR					((unsigned char) 1)
#define DBC_VERSION_MINOR					((unsigned char) 0)
#define DBC_VERSION_RELEASE				((unsigned char) 0)
#define DBC_VERSION_BUILD					((unsigned char) 'A')
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/* *********************************************************************** */
#define DBC_SIGNATURE_NONE					((DBC_SIGNATURE) 0X00000000UL)
#define DBC_SIGNATURE_OK					((DBC_SIGNATURE) 0X732502C1UL)

#define DBC_IS_SIG(ptr)						\
	DBC_MAP_TRUTH((ptr)->signature == DBC_SIGNATURE_OK)
/*
	CODE NOTE: Not used at present.
#define DBC_IS_VALID_PTR(ptr)				\
	DBC_MAP_TRUTH_GEN(GEN_VPTR_IsValidArea(((void *) (ptr)), sizeof(MLOG), \
	GEN_VPTR_ACCESS_READ_WRITE, NULL))
*/
#define DBC_IS_VALID_PTR(ptr)				DBC_MAP_TRUTH((ptr) != NULL)

#define DBC_IS_PTR(ptr)						\
	DBC_MAP_TRUTH(DBC_IS_VALID_PTR(ptr) && DBC_IS_SIG(ptr))
/* *********************************************************************** */

/*
	ADF NOTE: To be removed.
*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MDDL Notes

   DESCRIPTION :	The ''MDDL'' structure defines a single member column
						of a table to be accessed by a DBC facility ``get_rows``
						function.

	MEMBERS		:	The members of this structure are as follow:

						(.) ``member_name`` is an array of ''char'' which contains
						the name of the column. It is ''32'' characters in length.

						(.) ``member_data_length`` is an ''unsigned int'' which
						contains the length of the column area which is available
						for data storage.

						(.) ``member_length`` is an ''unsigned int'' which contains
						the actual length of the column area. For character columns
						(such as the Sybase ''char'' and ''varchar'' types), the
						``member_length`` value is ''1'' greater than the
						``member_data_length`` value because a single character
						position is reserved for the terminating ASCII ''0'' byte.

						(.) ``member_offset`` is an ''unsigned int'' which contains
						the offset of the column data within its structure or
						record.

						(.) ``type_count`` is an ''unsigned int'' which contains
						the number of instantiations of the primitive types
						specified in the ``type_spec`` member which together
						constitute the column.

						(.) ``type_spec`` is an array of ''char'' which contains
						the primitive alignment specification of the column in
						string format. This specification may be converted into
						an array ''DTA'' structures by using it as a parameter
						to such functions as ``DTA_AlignString``.

						(.) ``dbc_type`` is an ''int'' reserved for use by the
						DBCFUNCS library. It is used to store the facility-specific
						DBMS type. For Sybase DBC facilities such as ``DB-LIB`` and
						``CT-LIB``, is one of the following Sybase data types:

						(..) ''SYBBINARY''

						(..) ''SYBBIT''

						(..) ''SYBCHAR''

						(..) ''SYBTEXT''

						(..) ''SYBIMAGE''

						(..) ''SYBINT1''

						(..) ''SYBINT2''

						(..) ''SYBINT4''

						(..) ''SYBREAL''

						(..) ''SYBFLT8''

						(..) ''SYBMONEY''

						(..) ''SYBMONEY4''

						(..) ''SYBDATETIME''

						(..) ''SYBDATETIME4''


						(.) ``user_int_1`` is an ''int'' reserved for use by the
						implementation of the particular DBC facility.

						(.) ``user_int_2`` is an ''int'' reserved for use by the
						implementation of the particular DBC facility.

						(.) ``user_ptr_1`` is a pointer to ''void'' reserved for
						use by the implementation of the particular DBC facility.

						(.) ``user_ptr_2`` is a pointer to ''void'' reserved for
						use by the implementation of the particular DBC facility.

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2014 Michael L. Brock

   OUTPUT INDEX:	MDDL Notes
						Structures and Data Types:MDDL Notes
						DBC Structures and Data Types:MDDL Notes

   PUBLISH XREF:	MDDL Notes

   PUBLISH NAME:	MDDL Notes

	ENTRY CLASS	:	Structures and Data Types

EOH */
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#define DBC_GET_NAME_BY_FUNC_PTR(dbc_funcs, func_ptr)						\
	((STR_CMP_PTR((dbc_funcs)->bind,               func_ptr) == 0) ?	\
		"bind"               :	\
	 (STR_CMP_PTR((dbc_funcs)->cancel,             func_ptr) == 0) ?	\
		"cancel"             :	\
	 (STR_CMP_PTR((dbc_funcs)->cancel_all,         func_ptr) == 0) ?	\
		"cancel_all"         :	\
	 (STR_CMP_PTR((dbc_funcs)->cancel_query,       func_ptr) == 0) ?	\
		"cancel_query"       :	\
	 (STR_CMP_PTR((dbc_funcs)->close,              func_ptr) == 0) ?	\
		"close"              :	\
	 (STR_CMP_PTR((dbc_funcs)->do_sql,             func_ptr) == 0) ?	\
		"do_sql"             :	\
	 (STR_CMP_PTR((dbc_funcs)->get_id,             func_ptr) == 0) ?	\
		"get_id"             :	\
	 (STR_CMP_PTR((dbc_funcs)->get_rows,           func_ptr) == 0) ?	\
		"get_rows"           :	\
	 (STR_CMP_PTR((dbc_funcs)->get_rows_basic,     func_ptr) == 0) ?	\
		"get_rows_basic"     :	\
	 (STR_CMP_PTR((dbc_funcs)->get_vendor_name,    func_ptr) == 0) ?	\
		"get_vendor_name"    :	\
	 (STR_CMP_PTR((dbc_funcs)->get_version,        func_ptr) == 0) ?	\
		"get_version"        :	\
	 (STR_CMP_PTR((dbc_funcs)->get_version_string, func_ptr) == 0) ?	\
		"get_version_string" :	\
	 (STR_CMP_PTR((dbc_funcs)->init,               func_ptr) == 0) ?	\
		"init"               :	\
	 (STR_CMP_PTR((dbc_funcs)->open,               func_ptr) == 0) ?	\
		"open"               :	\
	 (STR_CMP_PTR((dbc_funcs)->parse_conn,         func_ptr) == 0) ?	\
		"parse_conn"         :	\
	 (STR_CMP_PTR((dbc_funcs)->table_to_members,   func_ptr) == 0) ?	\
		"table_to_members"   :	\
	 (STR_CMP_PTR((dbc_funcs)->set_display_length, func_ptr) == 0) ?	\
		"set_display_length" :	\
	 (STR_CMP_PTR((dbc_funcs)->dump_field,         func_ptr) == 0) ?	\
		"dump_field"         :	\
	 (STR_CMP_PTR((dbc_funcs)->map_type_to_mddl,   func_ptr) == 0) ?	\
		"map_type_to_mddl"   :	\
	 (STR_CMP_PTR((dbc_funcs)->format_type,        func_ptr) == 0) ?	\
		"format_type"        :	\
	 (STR_CMP_PTR((dbc_funcs)->format_type_sql,    func_ptr) == 0) ?	\
		"format_type_sql"    :	\
	 (STR_CMP_PTR((dbc_funcs)->double_to_number,   func_ptr) == 0) ?	\
		"double_to_number"   :	\
	 (STR_CMP_PTR((dbc_funcs)->number_to_double,   func_ptr) == 0) ?	\
		"number_to_double"   :	\
	 (STR_CMP_PTR((dbc_funcs)->dtime_to_date,      func_ptr) == 0) ?	\
		"dtime_to_date"      :	\
	 (STR_CMP_PTR((dbc_funcs)->date_to_dtime,      func_ptr) == 0) ?	\
		"date_to_dtime"      :	\
	 (STR_CMP_PTR((dbc_funcs)->dtime_to_time,      func_ptr) == 0) ?	\
		"dtime_to_time"      :	\
	 (STR_CMP_PTR((dbc_funcs)->time_to_dtime,      func_ptr) == 0) ?	\
		"time_to_dtime"      :	\
	 (STR_CMP_PTR((dbc_funcs)->is_number,          func_ptr) == 0) ?	\
		"is_number"          :	\
	 (STR_CMP_PTR((dbc_funcs)->min_number,         func_ptr) == 0) ?	\
		"min_number"         :	\
	 (STR_CMP_PTR((dbc_funcs)->max_number,         func_ptr) == 0) ?	\
		"max_number"         :	\
	 (STR_CMP_PTR((dbc_funcs)->cmp_number,         func_ptr) == 0) ?	\
		"cmp_number"         :	\
	 (STR_CMP_PTR((dbc_funcs)->scmp_number,        func_ptr) == 0) ?	\
		"scmp_number"        :	\
	 (STR_CMP_PTR((dbc_funcs)->is_date,            func_ptr) == 0) ?	\
		"is_date"            :	\
	 (STR_CMP_PTR((dbc_funcs)->min_date,           func_ptr) == 0) ?	\
		"min_date"           :	\
	 (STR_CMP_PTR((dbc_funcs)->max_date,           func_ptr) == 0) ?	\
		"max_date"           :	\
	 (STR_CMP_PTR((dbc_funcs)->cmp_date,           func_ptr) == 0) ?	\
		"cmp_date"           :	\
	 (STR_CMP_PTR((dbc_funcs)->scmp_date,          func_ptr) == 0) ?	\
		"scmp_date"          :	\
	 (STR_CMP_PTR((dbc_funcs)->is_time,            func_ptr) == 0) ?	\
		"is_time"            :	\
	 (STR_CMP_PTR((dbc_funcs)->min_time,           func_ptr) == 0) ?	\
		"min_time"           :	\
	 (STR_CMP_PTR((dbc_funcs)->max_time,           func_ptr) == 0) ?	\
		"max_time"           :	\
	 (STR_CMP_PTR((dbc_funcs)->cmp_time,           func_ptr) == 0) ?	\
		"cmp_time"           :	\
	 (STR_CMP_PTR((dbc_funcs)->scmp_time,          func_ptr) == 0) ?	\
		"scmp_time"          :	\
		NULL)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Function prototypes . . .															*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/

#endif /* #ifndef h__DBCFUNCI_H__h */

