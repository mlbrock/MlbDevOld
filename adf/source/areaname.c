/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Manages resolution of the names of ADF areas.

	Revision History	:	1994-06-15 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include "adf.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* *********************************************************************** */
COMPAT_EXTERN_DATA_DEF const ADF_AREA ADF_AreaNameList[ADF_AREA_COUNT] = {
	{ "base name",				"BASE_NAME",
		ADF_TRUE,	ADF_FALSE,	ADF_FALSE,	ADF_FALSE,	ADF_FALSE,	ADF_FALSE },
	{ "name",					"NAME",
		ADF_TRUE,	ADF_FALSE,	ADF_FALSE,	ADF_FALSE,	ADF_FALSE,	ADF_TRUE	 },
	{ "synopsis",				"SYNOPSIS",
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE,	ADF_FALSE,	ADF_TRUE,	ADF_TRUE	 },
	{ "code syntax",			"CODE_SYNTAX",
		ADF_FALSE,	ADF_FALSE,	ADF_FALSE,	ADF_FALSE,	ADF_TRUE,	ADF_TRUE	 },
	{ "description",			"DESCRIPTION",
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE	 },
	{ "definitions",			"DEFINITIONS",
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE	 },
	{ "terminology",			"TERMINOLOGY",
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE	 },
	{ "options",				"OPTIONS",
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE	 },
	{ "parameters",			"PARAMETERS",
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE	 },
	{ "commands",				"COMMANDS",
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE	 },
	{ "members",				"MEMBERS",
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE	 },
	{ "returns",				"RETURNS",
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE	 },
	{ "error messages",		"ERROR_MESSAGES",
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE	 },
	{ "environment",			"ENVIRONMENT",
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE	 },
	{ "files",					"FILES",
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE	 },
	{ "algorithms",			"ALGORITHMS",
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE	 },
	{ "debugging",				"DEBUGGING",
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE	 },
	{ "diagnostics",			"DIAGNOSTICS",
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE	 },
	{ "notes",					"NOTES",
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE	 },
	{ "caveats",				"CAVEATS",
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE	 },
	{ "defaults",				"DEFAULTS",
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE	 },
	{ "bugs",					"BUGS",
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE	 },
	{ "limitations",			"LIMITATIONS",
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE	 },
	{ "compatibility",		"COMPATIBILITY",
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE	 },
	{ "idiosyncracies",		"IDIOSYNCRACIES",
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE	 },
	{ "see also",				"SEE_ALSO",
		ADF_FALSE,	ADF_FALSE,	ADF_FALSE,	ADF_FALSE,	ADF_TRUE,	ADF_TRUE	 },
	{ "examples",				"EXAMPLES",
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE	 },
	{ "code examples",		"CODE_EXAMPLES",
		ADF_FALSE,	ADF_FALSE,	ADF_FALSE,	ADF_FALSE,	ADF_TRUE,	ADF_TRUE	 },
	{ "authors",				"AUTHORS",
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE	 },
	{ "contributors",			"CONTRIBUTORS",
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE	 },
	{ "acknowledgments",		"ACKNOWLEDGMENTS",
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE	 },
	{ "credits",				"CREDITS",
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE	 },
	{ "references",			"REFERENCES",
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE	 },
	{ "restrictions",			"RESTRICTIONS",
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE	 },
	{ "disclaimers",			"DISCLAIMERS",
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE	 },
	{ "copying",				"COPYING",
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE	 },
	{ "copyrights",			"COPYRIGHTS",
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE	 },
	{ "trademarks",			"TRADEMARKS",
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE,	ADF_TRUE	 },
	{ "source file name",	"SOURCE_FILE_NAME",
		ADF_FALSE,	ADF_FALSE,	ADF_FALSE,	ADF_FALSE,	ADF_FALSE,	ADF_TRUE	 },
	{ "source file date",	"SOURCE_FILE_DATE",
		ADF_FALSE,	ADF_FALSE,	ADF_FALSE,	ADF_FALSE,	ADF_FALSE,	ADF_TRUE	 },
	{ "man section",			"MAN_SECTION",
		ADF_FALSE,	ADF_FALSE,	ADF_FALSE,	ADF_FALSE,	ADF_FALSE,	ADF_FALSE },
	{ "tab setting",			"TAB_SETTING",
		ADF_FALSE,	ADF_FALSE,	ADF_FALSE,	ADF_FALSE,	ADF_FALSE,	ADF_FALSE },
	{ "output index",			"OUTPUT_INDEX",
		ADF_FALSE,	ADF_FALSE,	ADF_FALSE,	ADF_FALSE,	ADF_FALSE,	ADF_FALSE },
	{ "publish xref",			"PUBLISH_XREF",
		ADF_FALSE,	ADF_FALSE,	ADF_FALSE,	ADF_FALSE,	ADF_FALSE,	ADF_FALSE },
	{ "publish name",			"PUBLISH_NAME",
		ADF_FALSE,	ADF_FALSE,	ADF_FALSE,	ADF_FALSE,	ADF_FALSE,	ADF_FALSE },
	{ "source file full name",	"SOURCE_FILE_FULL_NAME",
		ADF_FALSE,	ADF_FALSE,	ADF_FALSE,	ADF_FALSE,	ADF_FALSE,	ADF_FALSE },
	{	"entry class name",		"ENTRY_CLASS_NAME",
		ADF_FALSE,	ADF_FALSE,	ADF_FALSE,	ADF_FALSE,	ADF_FALSE,	ADF_FALSE }
};
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	

	SYNOPSIS		:	

	DESCRIPTION	:	

	PARAMETERS	:	

	RETURNS		:	

	NOTES			:	

	CAVEATS		:	The buffer ``area_name`` into which the string representing
						the area name will be copied by this function should be at
						least the length of the manifest constant
						''ADF_AREA_NAME_LENGTH''. This will accomodate the string
						used for the case where the ``area_index`` parameter is
						invalid.

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994, Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *ADF_GetAreaName(unsigned int area_index, char *area_name)
#else
char *ADF_GetAreaName(area_index, area_name)
unsigned int  area_index;
char         *area_name;
#endif /* #ifndef NARGS */
{
	return(nstrcpy(area_name, (area_index >= ADF_AREA_COUNT) ?
		"*** INVALID ***" : ADF_AreaNameList[area_index].area_name,
		ADF_AREA_NAME_LENGTH));
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	

	SYNOPSIS		:	

	DESCRIPTION	:	

	PARAMETERS	:	

	RETURNS		:	

	NOTES			:	

	CAVEATS		:	The buffer ``area_name`` into which the string representing
						the area name will be copied by this function should be at
						least the length of the manifest constant
						''ADF_AREA_NAME_LENGTH''. This will accomodate the string
						used for the case where the ``area_index`` parameter is
						invalid.

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994, Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *ADF_GetParseAreaName(unsigned int area_index, char *area_name)
#else
char *ADF_GetParseAreaName(area_index, area_name)
unsigned int  area_index;
char         *area_name;
#endif /* #ifndef NARGS */
{
	if (area_index >= ADF_AREA_COUNT)
		area_name = NULL;
	else
		ADF_AreaToParseArea(ADF_GetAreaName(area_index, area_name));

	return(area_name);
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	

	SYNOPSIS		:	

	DESCRIPTION	:	

	PARAMETERS	:	

	RETURNS		:	

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994, Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *ADF_AreaToParseArea(char *area_name)
#else
char *ADF_AreaToParseArea(area_name)
char *area_name;
#endif /* #ifndef NARGS */
{
	char *tmp_ptr;

	tmp_ptr = upper(area_name);

	while (*tmp_ptr) {
		*tmp_ptr = ((char) ((!iscsym(*tmp_ptr)) ? ((char) '_') : *tmp_ptr));
		tmp_ptr++;
	}

	return(area_name);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *ADF_GetOutputAreaName(int area_name_type, unsigned int area_index,
	char **area_name_list, const char *section_name,
	unsigned int max_area_name_length, char *area_name)
#else
char *ADF_GetOutputAreaName(area_name_type, area_index, area_name_list,
	section_name, max_area_name_length, area_name)
int            area_name_type;
unsigned int   area_index;
char         **area_name_list;
const char    *section_name;
unsigned int   max_area_name_length;
char          *area_name;
#endif /* #ifndef NARGS */
{
	char tmp_area_name[ADF_AREA_NAME_LENGTH + 1];

	if (max_area_name_length) {
		if (area_index >= ADF_AREA_COUNT)
			*area_name = '\0';
		else if (area_name_list[area_index] != NULL)
			nstrcpy(area_name, area_name_list[area_index], max_area_name_length);
		else if ((area_name_type == ADF_AREA_NAME_TYPE_INTERNAL) ||
			(section_name == NULL) || (!(*section_name)))
			nstrcpy(area_name, initcaps(ADF_GetAreaName(area_index,
				tmp_area_name)), max_area_name_length);
		else
			nstrcpy(area_name, section_name, max_area_name_length);
	}
	else
		*area_name = '\0';

	return(area_name);
}
/*	***********************************************************************	*/

