/* *********************************************************************** */
/* *********************************************************************** */
/*	Parse Configuration File Facility (PCFF) Library Internal Include File	*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Internal include file for the PCFF library.

	Revision History	:	1999-11-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1999 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

#ifndef h__PCFFI_H__h

#define h__PCFFI_H__h						1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <stdlib.h>

#include "pcff.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	PCFF Truth Code Mappings

   NAME        :	PCFF Truth Code Mappings

	SYNOPSIS		:	truth_code = PCFF_MAP_TRUTH_STR(str_code);

						truth_code = PCFF_MAP_TRUTH_DAT(dat_code);

						truth_code = PCFF_MAP_TRUTH_GEN(gen_code);

						truth_code = PCFF_MAP_TRUTH_TFREAD(tfread_code);

						truth_code = PCFF_MAP_TRUTH_SDTIF(tfread_code);

	DESCRIPTION	:	The PCFF truth code mapping macros map truth codes from
						various low-level libraries to PCFF truth codes.

						(.) ''PCFF_MAP_TRUTH_STR'' maps a truth code
						from a STRFUNCS truth code to a PCFF truth code.

						(.) ''PCFF_MAP_TRUTH_DAT'' maps a truth code
						from a DATFUNCS truth code to a PCFF truth code.

						(.) ''PCFF_MAP_TRUTH_GEN'' maps a truth code
						from a GENFUNCS truth code to a PCFF truth code.

						(.) ''PCFF_MAP_TRUTH_TFREAD'' maps a truth code
						from a TFREAD truth code to a PCFF truth code.

						(.) ''PCFF_MAP_TRUTH_SDTIF'' maps a truth code
						from a SDTIF truth code to a PCFF truth code.

	PARAMETERS	:	The single parameter to these macros is the value of the
						truth code to be mapped to its equivalent PCFF truth
						code.

   NOTES       :	To map return codes from the libraries, use the related
						PCFF return code mapping macros.

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1999 - 2016 Michael L. Brock

   OUTPUT INDEX:	PCFF_MAP_TRUTH_STR
						PCFF_MAP_TRUTH_DAT
						PCFF_MAP_TRUTH_GEN
						PCFF_MAP_TRUTH_TFREAD
						PCFF_MAP_TRUTH_SDTIF
						Truth Code Mappings:PCFF_MAP_TRUTH_STR
						Truth Code Mappings:PCFF_MAP_TRUTH_DAT
						Truth Code Mappings:PCFF_MAP_TRUTH_GEN
						Truth Code Mappings:PCFF_MAP_TRUTH_TFREAD
						Truth Code Mappings:PCFF_MAP_TRUTH_SDTIF
						Macros and Manifest Constants:PCFF_MAP_TRUTH_STR
						Macros and Manifest Constants:PCFF_MAP_TRUTH_DAT
						Macros and Manifest Constants:PCFF_MAP_TRUTH_GEN
						Macros and Manifest Constants:PCFF_MAP_TRUTH_TFREAD
						Macros and Manifest Constants:PCFF_MAP_TRUTH_SDTIF
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	PCFF_MAP_TRUTH_STR
						PCFF_MAP_TRUTH_DAT
						PCFF_MAP_TRUTH_GEN
						PCFF_MAP_TRUTH_TFREAD
						PCFF_MAP_TRUTH_SDTIF
						PCFF Truth Code Mappings
						PCFF Truth Code Mapping
						PCFF truth code mappings
						PCFF truth code mapping

   PUBLISH NAME:	PCFF_MAP_TRUTH_STR
						PCFF_MAP_TRUTH_DAT
						PCFF_MAP_TRUTH_GEN
						PCFF_MAP_TRUTH_TFREAD
						PCFF_MAP_TRUTH_SDTIF

	ENTRY CLASS	:	Macros and Manifest Constants:Truth Code Mappings

EOH */
/*	***********************************************************************	*/
#define PCFF_MAP_TRUTH_STR(str_code)						\
	(((str_code) == STRFUNCS_TRUE) ? PCFF_TRUE : PCFF_FALSE)
#define PCFF_MAP_TRUTH_DAT(dat_code)						\
	(((dat_code) == DATFUNCS_TRUE) ? PCFF_TRUE : PCFF_FALSE)
#define PCFF_MAP_TRUTH_GEN(gen_code)						\
	(((gen_code) == GENFUNCS_TRUE) ? PCFF_TRUE : PCFF_FALSE)
#define PCFF_MAP_TRUTH_TFREAD(tfread_code)				\
	(((tfread_code) == TFREAD_TRUE) ? PCFF_TRUE : PCFF_FALSE)
#define PCFF_MAP_TRUTH_SDTIF(tfread_code)				\
	(((tfread_code) == SDTIF_TRUE) ? PCFF_TRUE : PCFF_FALSE)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	PCFF Return Code Mappings

   NAME        :	PCFF Return Code Mappings

	SYNOPSIS		:	return_code = PCFF_MAP_ERROR_STR(str_code);

						return_code = PCFF_MAP_ERROR_DAT(dat_code);

						return_code = PCFF_MAP_ERROR_GEN(gen_code);

						return_code = PCFF_MAP_ERROR_TFREAD(spf_code);

						return_code = PCFF_MAP_ERROR_SDTIF(spf_code);

	DESCRIPTION	:	The PCFF return code mapping macros map return codes from
						various low-level libraries to PCFF return codes.

						(.) ''PCFF_MAP_ERROR_STR'' maps a return code
						from a STRFUNCS return code to a PCFF return code.

						(.) ''PCFF_MAP_ERROR_DAT'' maps a return code
						from a DATFUNCS return code to a PCFF return code.

						(.) ''PCFF_MAP_ERROR_GEN'' maps a return code
						from a GENFUNCS return code to a PCFF return code.

						(.) ''PCFF_MAP_ERROR_TFREAD'' maps a return code
						from a TFREAD return code to a PCFF return code.

						(.) ''PCFF_MAP_ERROR_SDTIF'' maps a return code
						from a SDTIF return code to a PCFF return code.

	PARAMETERS	:	The single parameter to these macros is the value of the
						return code to be mapped to its equivalent PCFF return
						code.

   NOTES       :	To map truth codes from the libraries, use the related
						PCFF truth code mapping macros.

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1999 - 2016 Michael L. Brock

   OUTPUT INDEX:	PCFF_MAP_ERROR_STR
						PCFF_MAP_ERROR_DAT
						PCFF_MAP_ERROR_GEN
						PCFF_MAP_ERROR_TFREAD
						PCFF_MAP_ERROR_SDTIF
						Return Code Mappings:PCFF_MAP_ERROR_STR
						Return Code Mappings:PCFF_MAP_ERROR_GEN
						Return Code Mappings:PCFF_MAP_ERROR_DAT
						Return Code Mappings:PCFF_MAP_ERROR_TFREAD
						Return Code Mappings:PCFF_MAP_ERROR_SDTIF
						Macros and Manifest Constants:PCFF_MAP_ERROR_STR
						Macros and Manifest Constants:PCFF_MAP_ERROR_DAT
						Macros and Manifest Constants:PCFF_MAP_ERROR_GEN
						Macros and Manifest Constants:PCFF_MAP_ERROR_TFREAD
						Macros and Manifest Constants:PCFF_MAP_ERROR_SDTIF
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	PCFF_MAP_ERROR_STR
						PCFF_MAP_ERROR_DAT
						PCFF_MAP_ERROR_GEN
						PCFF_MAP_ERROR_TFREAD
						PCFF_MAP_ERROR_SDTIF
						PCFF Return Code Mappings
						PCFF Return Code Mapping
						PCFF return code mappings
						PCFF return code mapping
						PCFF Status Code Mappings
						PCFF Status Code Mapping
						PCFF status code mappings
						PCFF status code mapping
						PCFF Error Code Mappings
						PCFF Error Code Mapping
						PCFF error code mappings
						PCFF error code mapping

   PUBLISH NAME:	PCFF_MAP_ERROR_STR
						PCFF_MAP_ERROR_DAT
						PCFF_MAP_ERROR_GEN
						PCFF_MAP_ERROR_TFREAD
						PCFF_MAP_ERROR_SDTIF

	ENTRY CLASS	:	Macros and Manifest Constants:Return Code Mappings

EOH */
/*	***********************************************************************	*/
#define PCFF_MAP_ERROR_STR(str_code)										 			\
	(((str_code) == STRFUNCS_SUCCESS)          ? PCFF_SUCCESS           :	\
	 ((str_code) == STRFUNCS_FAILURE)          ? PCFF_FAILURE           :	\
	 ((str_code) == STRFUNCS_BAD_ARGS_FAILURE) ? PCFF_BAD_ARGS_FAILURE  :	\
	 ((str_code) == STRFUNCS_MEMORY_FAILURE)   ? PCFF_MEMORY_FAILURE    :	\
	 ((str_code) == STRFUNCS_SYSTEM_FAILURE)   ? PCFF_SYSTEM_FAILURE    :	\
	 PCFF_FAILURE)
#define PCFF_MAP_ERROR_DAT(dat_code)													\
	(((dat_code) == DATFUNCS_SUCCESS)          ? PCFF_SUCCESS           :	\
	 ((dat_code) == DATFUNCS_FAILURE)          ? PCFF_FAILURE           :	\
	 ((dat_code) == DATFUNCS_BAD_ARGS_FAILURE) ? PCFF_BAD_ARGS_FAILURE  :	\
	 ((dat_code) == DATFUNCS_MEMORY_FAILURE)   ? PCFF_MEMORY_FAILURE    :	\
	 ((dat_code) == DATFUNCS_SYSTEM_FAILURE)   ? PCFF_SYSTEM_FAILURE    :	\
	 PCFF_FAILURE)
#define PCFF_MAP_ERROR_GEN(gen_code)													\
	(((gen_code) == GENFUNCS_SUCCESS)          ? PCFF_SUCCESS           :	\
	 ((gen_code) == GENFUNCS_FAILURE)          ? PCFF_FAILURE           :	\
	 ((gen_code) == GENFUNCS_BAD_ARGS_FAILURE) ? PCFF_BAD_ARGS_FAILURE  :	\
	 ((gen_code) == GENFUNCS_MEMORY_FAILURE)   ? PCFF_MEMORY_FAILURE    :	\
	 ((gen_code) == GENFUNCS_SYSTEM_FAILURE)   ? PCFF_SYSTEM_FAILURE    :	\
	 PCFF_FAILURE)
#define PCFF_MAP_ERROR_TFREAD(tfread_code)											\
	(((tfread_code) == TFREAD_SUCCESS)          ? PCFF_SUCCESS          :	\
	 ((tfread_code) == TFREAD_FAILURE)          ? PCFF_FAILURE          :	\
	 ((tfread_code) == TFREAD_BAD_ARGS_FAILURE) ? PCFF_BAD_ARGS_FAILURE :	\
	 ((tfread_code) == TFREAD_MEMORY_FAILURE)   ? PCFF_MEMORY_FAILURE   :	\
	 ((tfread_code) == TFREAD_SYSTEM_FAILURE)   ? PCFF_SYSTEM_FAILURE   :	\
	 PCFF_FAILURE)
#define PCFF_MAP_ERROR_SDTIF(tfread_code)												\
	(((tfread_code) == SDTIF_SUCCESS)           ? PCFF_SUCCESS          :	\
	 ((tfread_code) == SDTIF_FAILURE)           ? PCFF_FAILURE          :	\
	 ((tfread_code) == SDTIF_BAD_ARGS_FAILURE)  ? PCFF_BAD_ARGS_FAILURE :	\
	 ((tfread_code) == SDTIF_MEMORY_FAILURE)    ? PCFF_MEMORY_FAILURE   :	\
	 ((tfread_code) == SDTIF_SYSTEM_FAILURE)    ? PCFF_SYSTEM_FAILURE   :	\
	 PCFF_FAILURE)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	PCFF Library Version Number

   NAME        :	PCFF Library Version Number

   DESCRIPTION :	The PCFF library version number manifest constants
						together define the current version number of the PCFF
						library as a whole.

						(.) ''PCFF_VERSION_MAJOR'' represents the major
						component of the library version number.

						(.) ''PCFF_VERSION_MINOR'' represents the minor
						component of the library version number.

						(.) ''PCFF_VERSION_RELEASE'' represents the release
						component of the library version number.

						(.) ''PCFF_VERSION_BUILD'' represents the build
						level component of the library version number.

   SEE ALSO    :	STR_VERSION

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1999 - 2016 Michael L. Brock

   OUTPUT INDEX:	PCFF_VERSION_MAJOR
						PCFF_VERSION_MINOR
						PCFF_VERSION_RELEASE
						PCFF_VERSION_BUILD
						PCFF Version Numbers:Library Version Number
						Library Version Number:PCFF_VERSION_MAJOR
						Library Version Number:PCFF_VERSION_MINOR
						Library Version Number:PCFF_VERSION_RELEASE
						Library Version Number:PCFF_VERSION_BUILD
						Macros and Manifest Constants:PCFF_VERSION_MAJOR
						Macros and Manifest Constants:PCFF_VERSION_MINOR
						Macros and Manifest Constants:PCFF_VERSION_RELEASE
						Macros and Manifest Constants:PCFF_VERSION_BUILD
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	PCFF_VERSION_MAJOR
						PCFF_VERSION_MINOR
						PCFF_VERSION_RELEASE
						PCFF_VERSION_BUILD
						PCFF Library Version Number
						PCFF library version number
						PCFF Library Version
						PCFF library version
						PCFF Version Number
						PCFF version number
						PCFF Version
						PCFF version

   PUBLISH NAME:	PCFF_VERSION_MAJOR
						PCFF_VERSION_MINOR
						PCFF_VERSION_RELEASE
						PCFF_VERSION_BUILD

	ENTRY CLASS	:	Macros and Manifest Constants:Library Version Number
						PCFF Version Numbers:Library Version Number

EOH */
/*	***********************************************************************	*/
#define PCFF_VERSION_MAJOR					((unsigned char) 2)
#define PCFF_VERSION_MINOR					((unsigned char) 0)
#define PCFF_VERSION_RELEASE				((unsigned char) 0)
#define PCFF_VERSION_BUILD					((unsigned char) 'A')
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#define PCFF_LINE_ALLOC_GRAN				1000
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Function prototypes for internal functions defined within 'pcff.a'.		*/
/*	***********************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Internal configuration processing function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int PCFF_ProcessFromFile,
	(PCFF_CFG *cfg_ptr, PCFF_FLAG flags, const char *in_file,
	unsigned int *include_stack_count, char ***include_stack_list,
	char *error_text));
COMPAT_FN_DECL(int PCFF_ProcessFromList,
	(PCFF_CFG *cfg_ptr, PCFF_FLAG flags, const char *source_name,
	unsigned int in_line_count, char **in_line_list,
	unsigned int *include_stack_count, char ***include_stack_list,
	char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Internal comparison function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int PCFF_ItemCompareName,
	(void *control_ptr, PCFF_ITEM *ptr_1, PCFF_ITEM *ptr_2,
	size_t data_length));
COMPAT_FN_DECL(int PCFF_ItemCompareOrder,
	(void *control_ptr, PCFF_ITEM *ptr_1, PCFF_ITEM *ptr_2,
	size_t data_length));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Internal miscellaneous function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int PCFF_AddItemSrc,
	(PCFF_ITEM *item_ptr, PCFF_FLAG flags, const char *file_name,
	unsigned int line_number, const char *value, char *error_text));
	/*	*****************************************************************	*/

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Type declarations for the library test and debugging functions . . .		*/
/*	***********************************************************************	*/
#if defined(_MSC_VER) && (_MSC_VER >= 1400)
# pragma warning(push)
# pragma warning(disable:4820)
#endif /* #if defined(_MSC_VER) && (_MSC_VER >= 1400) */

typedef struct {
	signed char     a_schar;
	unsigned char   a_uchar;
	signed short    a_sshort;
	unsigned short  a_ushort;
	signed int      a_sint;
	unsigned int    a_uint;
	signed long     a_slong;
	unsigned long   a_ulong;
	float           a_float;
	double          a_double;
	char            a_string_array[15 + 1];
	int             a_boolean;
	PCFF_IP_HSP     a_hsp_spec;
	PCFF_IP_HSP     a_phs_spec;
	char            a_date_string_array[63 + 1];
	char            a_time_string_array[63 + 1];
	char            a_timeval_string_array[63 + 1];
	char            a_timespec_string_array[63 + 1];
	char           *a_string_pointer;
	char            a_pathname_string_array[1023 + 1];
	char           *a_pathname_string_pointer;
	char            a_filename_string_array[(1023 * 2) + 1 + 1];
	char           *a_filename_string_pointer;
	char            a_hostspec_string_array[255 + 1];
	char           *a_hostspec_string_pointer;
	char            a_ip_service_array[127 + 1];
	char           *a_ip_service_pointer;
	char            a_ip_protocol_array[127 + 1];
	char           *a_ip_protocol_pointer;
	PCFF_CFG        cfg_data;
} PCFF_TEST_TARGET_DATA;

#if defined(_MSC_VER) && (_MSC_VER >= 1400)
# pragma warning(pop)
#endif /* #if defined(_MSC_VER) && (_MSC_VER >= 1400) */
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Function prototypes for the library test and debugging functions . . .	*/
/*	***********************************************************************	*/

COMPAT_FN_DECL(void PCFF_TEST_GetTestData,
	(unsigned int *line_count, char ***line_list,
	PCFF_PARSE_SPEC *parse_spec_ptr));
COMPAT_FN_DECL(void PCFF_TEST_GetTestDataParam,
	(unsigned int *line_count, char ***line_list,
	PCFF_PARSE_SPEC *parse_spec_ptr, PCFF_PARAM_SPEC *param_spec_ptr));

COMPAT_FN_DECL(void PCFF_TEST_FreeData,
	(PCFF_TEST_TARGET_DATA *ptr));
COMPAT_FN_DECL(void PCFF_TEST_InitData,
	(PCFF_TEST_TARGET_DATA *ptr));

COMPAT_FN_DECL(void PCFF_TEST_ShowCfg,
	(PCFF_CFG *cfg_ptr, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));

/*	***********************************************************************	*/

#endif /* #ifndef h__PCFFI_H__h */

