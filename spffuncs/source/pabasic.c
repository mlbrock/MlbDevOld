/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Specification Parse Facility (SPF) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Reads an ADF domain definition file.

	Revision History	:	1995-08-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <stdio.h>
#include <string.h>

#include <strfuncs.h>

#include "spffunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int SPF_PARSE_Basic(SPF_CONTEXT *context_ptr, const SPF_SPEC *spec_ptr,
	const SPF_PARSE *parse_ptr, void *parent_ptr, char *error_text)
#else
int SPF_PARSE_Basic(context_ptr, spec_ptr, parse_ptr, parent_ptr, error_text)
SPF_CONTEXT     *context_ptr;
const SPF_SPEC  *spec_ptr;
const SPF_PARSE *parse_ptr;
void            *parent_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	switch (spec_ptr->type) {
		case SPF_TYPE_CHAR_INT				:
			return_code = SPF_PARSE_CharInt(spec_ptr, parse_ptr,
				((char *) (((char *) parent_ptr) + spec_ptr->offset_1)),
				error_text);
			break;
		case SPF_TYPE_U_CHAR_INT			:
			return_code = SPF_PARSE_UCharInt(spec_ptr, parse_ptr,
				((unsigned char *) (((char *) parent_ptr) + spec_ptr->offset_1)),
				error_text);
			break;
		case SPF_TYPE_SHORT_INT				:
			return_code = SPF_PARSE_ShortInt(spec_ptr, parse_ptr,
				((short *) (((char *) parent_ptr) + spec_ptr->offset_1)),
				error_text);
			break;
		case SPF_TYPE_U_SHORT_INT			:
			return_code = SPF_PARSE_UShortInt(spec_ptr, parse_ptr,
				((unsigned short *) (((char *) parent_ptr) + spec_ptr->offset_1)),
				error_text);
			break;
		case SPF_TYPE_INT						:
			return_code = SPF_PARSE_Int(spec_ptr, parse_ptr,
				((int *) (((char *) parent_ptr) + spec_ptr->offset_1)),
				error_text);
			break;
		case SPF_TYPE_U_INT					:
			return_code = SPF_PARSE_UInt(spec_ptr, parse_ptr,
				((unsigned int *) (((char *) parent_ptr) + spec_ptr->offset_1)),
				error_text);
			break;
		case SPF_TYPE_LONG_INT				:
			return_code = SPF_PARSE_LongInt(spec_ptr, parse_ptr,
				((long *) (((char *) parent_ptr) + spec_ptr->offset_1)),
				error_text);
			break;
		case SPF_TYPE_U_LONG_INT			:
			return_code = SPF_PARSE_ULongInt(spec_ptr, parse_ptr,
				((unsigned long *) (((char *) parent_ptr) + spec_ptr->offset_1)),
				error_text);
			break;
		case SPF_TYPE_FLOAT					:
			return_code = SPF_PARSE_Float(spec_ptr, parse_ptr,
				((float *) (((char *) parent_ptr) + spec_ptr->offset_1)),
				error_text);
			break;
		case SPF_TYPE_DOUBLE					:
			return_code = SPF_PARSE_Double(spec_ptr, parse_ptr,
				((double *) (((char *) parent_ptr) + spec_ptr->offset_1)),
				error_text);
			break;
		case SPF_TYPE_BOOLEAN				:
			return_code = SPF_PARSE_Boolean(spec_ptr, parse_ptr,
				((int *) (((char *) parent_ptr) + spec_ptr->offset_1)),
				error_text);
			break;
		case SPF_TYPE_STR_VERSION			:
			return_code = SPF_PARSE_STRVersion(context_ptr, spec_ptr, parse_ptr,
				((STR_VERSION *) (((char *) parent_ptr) + spec_ptr->offset_1)),
				error_text);
			break;
		case SPF_TYPE_TEXT					:
			return_code = SPF_PARSE_Text(spec_ptr, parse_ptr,
				((char **) (((char *) parent_ptr) + spec_ptr->offset_1)),
				error_text);
			break;
		case SPF_TYPE_STRING					:
			return_code = SPF_PARSE_String(spec_ptr, parse_ptr,
				((char **) (((char *) parent_ptr) + spec_ptr->offset_1)),
				error_text);
			break;
		case SPF_TYPE_C_STRING				:
			return_code = SPF_PARSE_CString(spec_ptr, parse_ptr,
				((char **) (((char *) parent_ptr) + spec_ptr->offset_1)),
				error_text);
			break;
		case SPF_TYPE_TEXT_ML				:
			return_code = SPF_PARSE_TextML(spec_ptr, parse_ptr,
				((char **) (((char *) parent_ptr) + spec_ptr->offset_1)),
				error_text);
			break;
		case SPF_TYPE_STRING_ML				:
			return_code = SPF_PARSE_StringML(spec_ptr, parse_ptr,
				((char **) (((char *) parent_ptr) + spec_ptr->offset_1)),
				error_text);
			break;
		case SPF_TYPE_C_STRING_ML			:
			return_code = SPF_PARSE_CStringML(spec_ptr, parse_ptr,
				((char **) (((char *) parent_ptr) + spec_ptr->offset_1)),
				error_text);
			break;
		case SPF_TYPE_TEXT_LIST				:
			return_code = SPF_PARSE_TextList(spec_ptr, parse_ptr,
				((unsigned int *) (((char *) parent_ptr) + spec_ptr->offset_1)),
				((char ***) (((char *) parent_ptr) + spec_ptr->offset_2)),
				error_text);
			break;
		case SPF_TYPE_STRING_LIST			:
			return_code = SPF_PARSE_StringList(spec_ptr, parse_ptr,
				((unsigned int *) (((char *) parent_ptr) + spec_ptr->offset_1)),
				((char ***) (((char *) parent_ptr) + spec_ptr->offset_2)),
				error_text);
			break;
		case SPF_TYPE_C_STRING_LIST		:
			return_code = SPF_PARSE_CStringList(spec_ptr, parse_ptr,
				((unsigned int *) (((char *) parent_ptr) + spec_ptr->offset_1)),
				((char ***) (((char *) parent_ptr) + spec_ptr->offset_2)),
				error_text);
			break;

		case SPF_TYPE_TEXT_ML_LIST			:
			return_code = SPF_PARSE_TextMLList(spec_ptr, parse_ptr,
				((unsigned int *) (((char *) parent_ptr) + spec_ptr->offset_1)),
				((char ***) (((char *) parent_ptr) + spec_ptr->offset_2)),
				error_text);
			break;
		case SPF_TYPE_STRING_ML_LIST		:
			return_code = SPF_PARSE_StringMLList(spec_ptr, parse_ptr,
				((unsigned int *) (((char *) parent_ptr) + spec_ptr->offset_1)),
				((char ***) (((char *) parent_ptr) + spec_ptr->offset_2)),
				error_text);
			break;
		case SPF_TYPE_C_STRING_ML_LIST	:
			return_code = SPF_PARSE_CStringMLList(spec_ptr, parse_ptr,
				((unsigned int *) (((char *) parent_ptr) + spec_ptr->offset_1)),
				((char ***) (((char *) parent_ptr) + spec_ptr->offset_2)),
				error_text);
			break;
		default									:
			sprintf(error_text,
				"%s '%s()' %s (type = %u = 0X%08X) %s '%-.*s' %s ",
				"Invalid", spec_ptr->name, "definition encountered",
				spec_ptr->type, spec_ptr->type, "parse text",
				(parse_ptr->length > 500) ? 500 : ((int) parse_ptr->length),
				parse_ptr->text, "beginning");
			chrcat(SPF_GetLocationLineFile(parse_ptr, 500,
				error_text + strlen(error_text)), '.');
			return_code = SPF_PARSE_FAILURE;
			break;
	}

	return(return_code);
}
/*	***********************************************************************	*/

