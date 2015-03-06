/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module                  	*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Internal ADF definition file representation.

	Revision History	:	1996-01-13 --- Creation.

		Copyright Michael L. Brock 1996 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Required include files . . .                                           	*/
/*	***********************************************************************	*/

#include "adf.h"

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Initialize section pattern string lists for domain number 0.           	*/
/*	***********************************************************************	*/
static char *ADF_Def_DOM_000_SEC_000_MAT_STRL[1] = {
	" BASE NAME : "
};

static char *ADF_Def_DOM_000_SEC_001_MAT_STRL[1] = {
	" NAME : "
};

static char *ADF_Def_DOM_000_SEC_002_MAT_STRL[2] = {
	" SYNOPSIS : ",
	" SYNTAX : "
};

static char *ADF_Def_DOM_000_SEC_003_MAT_STRL[1] = {
	" DESCRIPTION : "
};

static char *ADF_Def_DOM_000_SEC_004_MAT_STRL[3] = {
	" MEMBER : ",
	" MEMBERS : ",
	" MEMBER(S) : "
};

static char *ADF_Def_DOM_000_SEC_005_MAT_STRL[3] = {
	" PARAMETER : ",
	" PARAMETERS : ",
	" PARAMETER(S) : "
};

static char *ADF_Def_DOM_000_SEC_006_MAT_STRL[2] = {
	" RETURNS : ",
	" RETURN(S) : "
};

static char *ADF_Def_DOM_000_SEC_007_MAT_STRL[6] = {
	" ENVIRONMENT : ",
	" ENVIRONMENTS : ",
	" ENVIRONMENT(S) : ",
	" ENVIRONMENT VARIABLE : ",
	" ENVIRONMENT VARIABLES : ",
	" ENVIRONMENT VARIABLE(S) : "
};

static char *ADF_Def_DOM_000_SEC_008_MAT_STRL[6] = {
	" NOTE : ",
	" NOTES : ",
	" NOTE(S) : ",
	" COMMENT : ",
	" COMMENTS : ",
	" COMMENT(S) : "
};

static char *ADF_Def_DOM_000_SEC_009_MAT_STRL[12] = {
	" CAVEAT : ",
	" CAVEATS : ",
	" CAVEAT(S) : ",
	" CAUTION : ",
	" CAUTIONS : ",
	" CAUTION(S) : ",
	" WARNING : ",
	" WARNINGS : ",
	" WARNING(S) : ",
	" DANGER : ",
	" DANGERS : ",
	" DANGER(S) : "
};

static char *ADF_Def_DOM_000_SEC_010_MAT_STRL[1] = {
	" SEE ALSO : "
};

static char *ADF_Def_DOM_000_SEC_011_MAT_STRL[3] = {
	" EXAMPLE : ",
	" EXAMPLES : ",
	" EXAMPLE(S) : "
};

static char *ADF_Def_DOM_000_SEC_012_MAT_STRL[3] = {
	" CODE EXAMPLE : ",
	" CODE EXAMPLES : ",
	" CODE EXAMPLE(S) : "
};

static char *ADF_Def_DOM_000_SEC_013_MAT_STRL[10] = {
	" AUTHOR : ",
	" AUTHORS : ",
	" AUTHOR(S) : ",
	" PROGRAMMER : ",
	" PROGRAMMERS : ",
	" PROGRAMMER(S) : ",
	" AUTHORED BY : ",
	" PROGRAMMED BY : ",
	" WRITTEN BY : ",
	" CREATED BY : "
};

static char *ADF_Def_DOM_000_SEC_014_MAT_STRL[4] = {
	" COPYRIGHT : ",
	" COPYRIGHTS : ",
	" COPYRIGHT(S) : ",
	" COPYRIGHTED BY : "
};

static char *ADF_Def_DOM_000_SEC_015_MAT_STRL[12] = {
	" SOURCE : ",
	" SOURCES : ",
	" SOURCE(S) : ",
	" SOURCE FILE : ",
	" SOURCE FILES : ",
	" SOURCE FILE(S) : ",
	" SOURCE NAME : ",
	" SOURCE NAMES : ",
	" SOURCE NAME(S) : ",
	" SOURCE FILE NAME : ",
	" SOURCE FILE NAMES : ",
	" SOURCE FILE NAME(S) : "
};

static char *ADF_Def_DOM_000_SEC_016_MAT_STRL[9] = {
	" DATE : ",
	" DATES : ",
	" DATE(S) : ",
	" SOURCE DATE : ",
	" SOURCE DATES : ",
	" SOURCE DATE(S) : ",
	" SOURCE FILE DATE : ",
	" SOURCE FILE DATES : ",
	" SOURCE FILE DATE(S) : "
};

static char *ADF_Def_DOM_000_SEC_017_MAT_STRL[12] = {
	" INDEX : ",
	" INDEXS : ",
	" INDEX(S) : ",
	" INDEXES : ",
	" INDEX(ES) : ",
	" INDICES : ",
	" OUTPUT INDEX : ",
	" OUTPUT INDEXS : ",
	" OUTPUT INDEX(S) : ",
	" OUTPUT INDEXES : ",
	" OUTPUT INDEX(ES) : ",
	" OUTPUT INDICES : "
};

static char *ADF_Def_DOM_000_SEC_018_MAT_STRL[6] = {
	" PUBLISH XREF : ",
	" PUBLISH XREFS : ",
	" PUBLISH XREF(S) : ",
	" PUBLISH X-REF : ",
	" PUBLISH X-REFS : ",
	" PUBLISH X-REF(S) : "
};

static char *ADF_Def_DOM_000_SEC_019_MAT_STRL[3] = {
	" PUBLISH NAME : ",
	" PUBLISH NAMES : ",
	" PUBLISH NAME(S) : "
};

static char *ADF_Def_DOM_000_SEC_020_MAT_STRL[6] = {
	" ENTRY CLASS : ",
	" ENTRY CLASSES : ",
	" ENTRY CLASS(ES) : ",
	" ENTRY CLASS NAME : ",
	" ENTRY CLASS NAMES : ",
	" ENTRY CLASS NAME(S) : "
};
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Initialize section lists for domain number 0.                          	*/
/*	***********************************************************************	*/
static ADF_SECTION ADF_Def_DOM_000_SEC[21] = {
	{
		"Base Name",
		"Base Name",
		0,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		{
			1,
			ADF_Def_DOM_000_SEC_000_MAT_STRL,
			"BASE"
		}
	},
	{
		"Name",
		"Name",
		1,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		{
			1,
			ADF_Def_DOM_000_SEC_001_MAT_STRL,
			"NAME"
		}
	},
	{
		"Synopsis",
		"Synopsis",
		3,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		{
			2,
			ADF_Def_DOM_000_SEC_002_MAT_STRL,
			":"
		}
	},
	{
		"Description",
		"Description",
		4,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		{
			1,
			ADF_Def_DOM_000_SEC_003_MAT_STRL,
			"DESCRIPTION"
		}
	},
	{
		"Members",
		"Members",
		10,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		{
			3,
			ADF_Def_DOM_000_SEC_004_MAT_STRL,
			"MEMBER"
		}
	},
	{
		"Parameters",
		"Parameters",
		8,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		{
			3,
			ADF_Def_DOM_000_SEC_005_MAT_STRL,
			"PARAMETER"
		}
	},
	{
		"Returns",
		"Returns",
		11,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		{
			2,
			ADF_Def_DOM_000_SEC_006_MAT_STRL,
			"RETURN"
		}
	},
	{
		"Environment",
		"Environment",
		13,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		{
			6,
			ADF_Def_DOM_000_SEC_007_MAT_STRL,
			"ENVIRONMENT"
		}
	},
	{
		"Notes",
		"Notes",
		18,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		{
			6,
			ADF_Def_DOM_000_SEC_008_MAT_STRL,
			":"
		}
	},
	{
		"Caveats",
		"Caveats",
		19,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		{
			12,
			ADF_Def_DOM_000_SEC_009_MAT_STRL,
			":"
		}
	},
	{
		"See Also",
		"See Also",
		25,
		ADF_FALSE,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		{
			1,
			ADF_Def_DOM_000_SEC_010_MAT_STRL,
			"ALSO"
		}
	},
	{
		"Examples",
		"Examples",
		26,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		{
			3,
			ADF_Def_DOM_000_SEC_011_MAT_STRL,
			"EXAMPLE"
		}
	},
	{
		"Code Examples",
		"Code Examples",
		27,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		{
			3,
			ADF_Def_DOM_000_SEC_012_MAT_STRL,
			"EXAMPLE"
		}
	},
	{
		"Authors",
		"Authors",
		28,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		{
			10,
			ADF_Def_DOM_000_SEC_013_MAT_STRL,
			":"
		}
	},
	{
		"Copyrights",
		"Copyrights",
		36,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		{
			4,
			ADF_Def_DOM_000_SEC_014_MAT_STRL,
			":"
		}
	},
	{
		"Source File Name",
		"Source File Name",
		38,
		ADF_FALSE,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		{
			12,
			ADF_Def_DOM_000_SEC_015_MAT_STRL,
			"SOURCE"
		}
	},
	{
		"Source File Date",
		"Source File Date",
		39,
		ADF_FALSE,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		{
			9,
			ADF_Def_DOM_000_SEC_016_MAT_STRL,
			"DATE"
		}
	},
	{
		"Output Index",
		"Output Index",
		42,
		ADF_FALSE,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		{
			12,
			ADF_Def_DOM_000_SEC_017_MAT_STRL,
			":"
		}
	},
	{
		"Publish Xref",
		"Publish Xref",
		43,
		ADF_FALSE,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		{
			6,
			ADF_Def_DOM_000_SEC_018_MAT_STRL,
			"PUBLISH"
		}
	},
	{
		"Publish Name",
		"Publish Name",
		44,
		ADF_FALSE,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		{
			3,
			ADF_Def_DOM_000_SEC_019_MAT_STRL,
			"PUBLISH"
		}
	},
	{
		"Entry Class",
		"Entry Class",
		46,
		ADF_FALSE,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		{
			6,
			ADF_Def_DOM_000_SEC_020_MAT_STRL,
			"ENTRY"
		}
	}
};
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Initialize section pattern string lists for domain number 1.           	*/
/*	***********************************************************************	*/
static char *ADF_Def_DOM_001_SEC_000_MAT_STRL[1] = {
	" BASE NAME : "
};

static char *ADF_Def_DOM_001_SEC_001_MAT_STRL[1] = {
	" NAME : "
};

static char *ADF_Def_DOM_001_SEC_002_MAT_STRL[2] = {
	" SYNOPSIS : ",
	" SYNTAX : "
};

static char *ADF_Def_DOM_001_SEC_003_MAT_STRL[1] = {
	" DESCRIPTION : "
};

static char *ADF_Def_DOM_001_SEC_004_MAT_STRL[3] = {
	" MEMBER : ",
	" MEMBERS : ",
	" MEMBER(S) : "
};

static char *ADF_Def_DOM_001_SEC_005_MAT_STRL[3] = {
	" PARAMETER : ",
	" PARAMETERS : ",
	" PARAMETER(S) : "
};

static char *ADF_Def_DOM_001_SEC_006_MAT_STRL[2] = {
	" RETURNS : ",
	" RETURN(S) : "
};

static char *ADF_Def_DOM_001_SEC_007_MAT_STRL[6] = {
	" ENVIRONMENT : ",
	" ENVIRONMENTS : ",
	" ENVIRONMENT(S) : ",
	" ENVIRONMENT VARIABLE : ",
	" ENVIRONMENT VARIABLES : ",
	" ENVIRONMENT VARIABLE(S) : "
};

static char *ADF_Def_DOM_001_SEC_008_MAT_STRL[6] = {
	" NOTE : ",
	" NOTES : ",
	" NOTE(S) : ",
	" COMMENT : ",
	" COMMENTS : ",
	" COMMENT(S) : "
};

static char *ADF_Def_DOM_001_SEC_009_MAT_STRL[12] = {
	" CAVEAT : ",
	" CAVEATS : ",
	" CAVEAT(S) : ",
	" CAUTION : ",
	" CAUTIONS : ",
	" CAUTION(S) : ",
	" WARNING : ",
	" WARNINGS : ",
	" WARNING(S) : ",
	" DANGER : ",
	" DANGERS : ",
	" DANGER(S) : "
};

static char *ADF_Def_DOM_001_SEC_010_MAT_STRL[1] = {
	" SEE ALSO : "
};

static char *ADF_Def_DOM_001_SEC_011_MAT_STRL[3] = {
	" EXAMPLE : ",
	" EXAMPLES : ",
	" EXAMPLE(S) : "
};

static char *ADF_Def_DOM_001_SEC_012_MAT_STRL[3] = {
	" CODE EXAMPLE : ",
	" CODE EXAMPLES : ",
	" CODE EXAMPLE(S) : "
};

static char *ADF_Def_DOM_001_SEC_013_MAT_STRL[10] = {
	" AUTHOR : ",
	" AUTHORS : ",
	" AUTHOR(S) : ",
	" PROGRAMMER : ",
	" PROGRAMMERS : ",
	" PROGRAMMER(S) : ",
	" AUTHORED BY : ",
	" PROGRAMMED BY : ",
	" WRITTEN BY : ",
	" CREATED BY : "
};

static char *ADF_Def_DOM_001_SEC_014_MAT_STRL[4] = {
	" COPYRIGHT : ",
	" COPYRIGHTS : ",
	" COPYRIGHT(S) : ",
	" COPYRIGHTED BY : "
};

static char *ADF_Def_DOM_001_SEC_015_MAT_STRL[12] = {
	" SOURCE : ",
	" SOURCES : ",
	" SOURCE(S) : ",
	" SOURCE FILE : ",
	" SOURCE FILES : ",
	" SOURCE FILE(S) : ",
	" SOURCE NAME : ",
	" SOURCE NAMES : ",
	" SOURCE NAME(S) : ",
	" SOURCE FILE NAME : ",
	" SOURCE FILE NAMES : ",
	" SOURCE FILE NAME(S) : "
};

static char *ADF_Def_DOM_001_SEC_016_MAT_STRL[9] = {
	" DATE : ",
	" DATES : ",
	" DATE(S) : ",
	" SOURCE DATE : ",
	" SOURCE DATES : ",
	" SOURCE DATE(S) : ",
	" SOURCE FILE DATE : ",
	" SOURCE FILE DATES : ",
	" SOURCE FILE DATE(S) : "
};

static char *ADF_Def_DOM_001_SEC_017_MAT_STRL[12] = {
	" INDEX : ",
	" INDEXS : ",
	" INDEX(S) : ",
	" INDEXES : ",
	" INDEX(ES) : ",
	" INDICES : ",
	" OUTPUT INDEX : ",
	" OUTPUT INDEXS : ",
	" OUTPUT INDEX(S) : ",
	" OUTPUT INDEXES : ",
	" OUTPUT INDEX(ES) : ",
	" OUTPUT INDICES : "
};

static char *ADF_Def_DOM_001_SEC_018_MAT_STRL[6] = {
	" PUBLISH XREF : ",
	" PUBLISH XREFS : ",
	" PUBLISH XREF(S) : ",
	" PUBLISH X-REF : ",
	" PUBLISH X-REFS : ",
	" PUBLISH X-REF(S) : "
};

static char *ADF_Def_DOM_001_SEC_019_MAT_STRL[3] = {
	" PUBLISH NAME : ",
	" PUBLISH NAMES : ",
	" PUBLISH NAME(S) : "
};

static char *ADF_Def_DOM_001_SEC_020_MAT_STRL[6] = {
	" ENTRY CLASS : ",
	" ENTRY CLASSES : ",
	" ENTRY CLASS(ES) : ",
	" ENTRY CLASS NAME : ",
	" ENTRY CLASS NAMES : ",
	" ENTRY CLASS NAME(S) : "
};
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Initialize section lists for domain number 1.                          	*/
/*	***********************************************************************	*/
static ADF_SECTION ADF_Def_DOM_001_SEC[21] = {
	{
		"Base Name",
		"Base Name",
		0,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		{
			1,
			ADF_Def_DOM_001_SEC_000_MAT_STRL,
			"BASE"
		}
	},
	{
		"Name",
		"Name",
		1,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		{
			1,
			ADF_Def_DOM_001_SEC_001_MAT_STRL,
			"NAME"
		}
	},
	{
		"Synopsis",
		"Synopsis",
		3,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		{
			2,
			ADF_Def_DOM_001_SEC_002_MAT_STRL,
			":"
		}
	},
	{
		"Description",
		"Description",
		4,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		{
			1,
			ADF_Def_DOM_001_SEC_003_MAT_STRL,
			"DESCRIPTION"
		}
	},
	{
		"Members",
		"Members",
		10,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		{
			3,
			ADF_Def_DOM_001_SEC_004_MAT_STRL,
			"MEMBER"
		}
	},
	{
		"Parameters",
		"Parameters",
		8,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		{
			3,
			ADF_Def_DOM_001_SEC_005_MAT_STRL,
			"PARAMETER"
		}
	},
	{
		"Returns",
		"Returns",
		11,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		{
			2,
			ADF_Def_DOM_001_SEC_006_MAT_STRL,
			"RETURN"
		}
	},
	{
		"Environment",
		"Environment",
		13,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		{
			6,
			ADF_Def_DOM_001_SEC_007_MAT_STRL,
			"ENVIRONMENT"
		}
	},
	{
		"Notes",
		"Notes",
		18,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		{
			6,
			ADF_Def_DOM_001_SEC_008_MAT_STRL,
			":"
		}
	},
	{
		"Caveats",
		"Caveats",
		19,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		{
			12,
			ADF_Def_DOM_001_SEC_009_MAT_STRL,
			":"
		}
	},
	{
		"See Also",
		"See Also",
		25,
		ADF_FALSE,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		{
			1,
			ADF_Def_DOM_001_SEC_010_MAT_STRL,
			"ALSO"
		}
	},
	{
		"Examples",
		"Examples",
		26,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		{
			3,
			ADF_Def_DOM_001_SEC_011_MAT_STRL,
			"EXAMPLE"
		}
	},
	{
		"Code Examples",
		"Code Examples",
		27,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		{
			3,
			ADF_Def_DOM_001_SEC_012_MAT_STRL,
			"EXAMPLE"
		}
	},
	{
		"Authors",
		"Authors",
		28,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		{
			10,
			ADF_Def_DOM_001_SEC_013_MAT_STRL,
			":"
		}
	},
	{
		"Copyrights",
		"Copyrights",
		36,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		{
			4,
			ADF_Def_DOM_001_SEC_014_MAT_STRL,
			":"
		}
	},
	{
		"Source File Name",
		"Source File Name",
		38,
		ADF_FALSE,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		{
			12,
			ADF_Def_DOM_001_SEC_015_MAT_STRL,
			"SOURCE"
		}
	},
	{
		"Source File Date",
		"Source File Date",
		39,
		ADF_FALSE,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		{
			9,
			ADF_Def_DOM_001_SEC_016_MAT_STRL,
			"DATE"
		}
	},
	{
		"Output Index",
		"Output Index",
		42,
		ADF_FALSE,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		{
			12,
			ADF_Def_DOM_001_SEC_017_MAT_STRL,
			":"
		}
	},
	{
		"Publish Xref",
		"Publish Xref",
		43,
		ADF_FALSE,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		{
			6,
			ADF_Def_DOM_001_SEC_018_MAT_STRL,
			"PUBLISH"
		}
	},
	{
		"Publish Name",
		"Publish Name",
		44,
		ADF_FALSE,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		{
			3,
			ADF_Def_DOM_001_SEC_019_MAT_STRL,
			"PUBLISH"
		}
	},
	{
		"Entry Class",
		"Entry Class",
		46,
		ADF_FALSE,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		{
			6,
			ADF_Def_DOM_001_SEC_020_MAT_STRL,
			"ENTRY"
		}
	}
};
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Initialize section pattern string lists for domain number 2.           	*/
/*	***********************************************************************	*/
static char *ADF_Def_DOM_002_SEC_000_MAT_STRL[1] = {
	" BASE NAME : "
};

static char *ADF_Def_DOM_002_SEC_001_MAT_STRL[1] = {
	" NAME : "
};

static char *ADF_Def_DOM_002_SEC_002_MAT_STRL[2] = {
	" SYNOPSIS : ",
	" SYNTAX : "
};

static char *ADF_Def_DOM_002_SEC_003_MAT_STRL[1] = {
	" DESCRIPTION : "
};

static char *ADF_Def_DOM_002_SEC_004_MAT_STRL[6] = {
	" OPTION : ",
	" OPTIONS : ",
	" OPTION(S) : ",
	" PARAMETER : ",
	" PARAMETERS : ",
	" PARAMETER(S) : "
};

static char *ADF_Def_DOM_002_SEC_005_MAT_STRL[2] = {
	" RETURNS : ",
	" RETURN(S) : "
};

static char *ADF_Def_DOM_002_SEC_006_MAT_STRL[6] = {
	" ENVIRONMENT : ",
	" ENVIRONMENTS : ",
	" ENVIRONMENT(S) : ",
	" ENVIRONMENT VARIABLE : ",
	" ENVIRONMENT VARIABLES : ",
	" ENVIRONMENT VARIABLE(S) : "
};

static char *ADF_Def_DOM_002_SEC_007_MAT_STRL[6] = {
	" NOTE : ",
	" NOTES : ",
	" NOTE(S) : ",
	" COMMENT : ",
	" COMMENTS : ",
	" COMMENT(S) : "
};

static char *ADF_Def_DOM_002_SEC_008_MAT_STRL[12] = {
	" CAVEAT : ",
	" CAVEATS : ",
	" CAVEAT(S) : ",
	" CAUTION : ",
	" CAUTIONS : ",
	" CAUTION(S) : ",
	" WARNING : ",
	" WARNINGS : ",
	" WARNING(S) : ",
	" DANGER : ",
	" DANGERS : ",
	" DANGER(S) : "
};

static char *ADF_Def_DOM_002_SEC_009_MAT_STRL[1] = {
	" SEE ALSO : "
};

static char *ADF_Def_DOM_002_SEC_010_MAT_STRL[3] = {
	" EXAMPLE : ",
	" EXAMPLES : ",
	" EXAMPLE(S) : "
};

static char *ADF_Def_DOM_002_SEC_011_MAT_STRL[10] = {
	" AUTHOR : ",
	" AUTHORS : ",
	" AUTHOR(S) : ",
	" PROGRAMMER : ",
	" PROGRAMMERS : ",
	" PROGRAMMER(S) : ",
	" AUTHORED BY : ",
	" PROGRAMMED BY : ",
	" WRITTEN BY : ",
	" CREATED BY : "
};

static char *ADF_Def_DOM_002_SEC_012_MAT_STRL[4] = {
	" COPYRIGHT : ",
	" COPYRIGHTS : ",
	" COPYRIGHT(S) : ",
	" COPYRIGHTED BY : "
};

static char *ADF_Def_DOM_002_SEC_013_MAT_STRL[12] = {
	" SOURCE : ",
	" SOURCES : ",
	" SOURCE(S) : ",
	" SOURCE FILE : ",
	" SOURCE FILES : ",
	" SOURCE FILE(S) : ",
	" SOURCE NAME : ",
	" SOURCE NAMES : ",
	" SOURCE NAME(S) : ",
	" SOURCE FILE NAME : ",
	" SOURCE FILE NAMES : ",
	" SOURCE FILE NAME(S) : "
};

static char *ADF_Def_DOM_002_SEC_014_MAT_STRL[9] = {
	" DATE : ",
	" DATES : ",
	" DATE(S) : ",
	" SOURCE DATE : ",
	" SOURCE DATES : ",
	" SOURCE DATE(S) : ",
	" SOURCE FILE DATE : ",
	" SOURCE FILE DATES : ",
	" SOURCE FILE DATE(S) : "
};

static char *ADF_Def_DOM_002_SEC_015_MAT_STRL[12] = {
	" INDEX : ",
	" INDEXS : ",
	" INDEX(S) : ",
	" INDEXES : ",
	" INDEX(ES) : ",
	" INDICES : ",
	" OUTPUT INDEX : ",
	" OUTPUT INDEXS : ",
	" OUTPUT INDEX(S) : ",
	" OUTPUT INDEXES : ",
	" OUTPUT INDEX(ES) : ",
	" OUTPUT INDICES : "
};

static char *ADF_Def_DOM_002_SEC_016_MAT_STRL[6] = {
	" PUBLISH XREF : ",
	" PUBLISH XREFS : ",
	" PUBLISH XREF(S) : ",
	" PUBLISH X-REF : ",
	" PUBLISH X-REFS : ",
	" PUBLISH X-REF(S) : "
};

static char *ADF_Def_DOM_002_SEC_017_MAT_STRL[3] = {
	" PUBLISH NAME : ",
	" PUBLISH NAMES : ",
	" PUBLISH NAME(S) : "
};

static char *ADF_Def_DOM_002_SEC_018_MAT_STRL[6] = {
	" ENTRY CLASS : ",
	" ENTRY CLASSES : ",
	" ENTRY CLASS(ES) : ",
	" ENTRY CLASS NAME : ",
	" ENTRY CLASS NAMES : ",
	" ENTRY CLASS NAME(S) : "
};
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Initialize section lists for domain number 2.                          	*/
/*	***********************************************************************	*/
static ADF_SECTION ADF_Def_DOM_002_SEC[19] = {
	{
		"Base Name",
		"Base Name",
		0,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		{
			1,
			ADF_Def_DOM_002_SEC_000_MAT_STRL,
			"BASE"
		}
	},
	{
		"Name",
		"Name",
		1,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		{
			1,
			ADF_Def_DOM_002_SEC_001_MAT_STRL,
			"NAME"
		}
	},
	{
		"Synopsis",
		"Synopsis",
		2,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		{
			2,
			ADF_Def_DOM_002_SEC_002_MAT_STRL,
			":"
		}
	},
	{
		"Description",
		"Description",
		4,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		{
			1,
			ADF_Def_DOM_002_SEC_003_MAT_STRL,
			"DESCRIPTION"
		}
	},
	{
		"Parameters",
		"Parameters",
		8,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		{
			6,
			ADF_Def_DOM_002_SEC_004_MAT_STRL,
			":"
		}
	},
	{
		"Returns",
		"Returns",
		11,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		{
			2,
			ADF_Def_DOM_002_SEC_005_MAT_STRL,
			"RETURN"
		}
	},
	{
		"Environment",
		"Environment",
		13,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		{
			6,
			ADF_Def_DOM_002_SEC_006_MAT_STRL,
			"ENVIRONMENT"
		}
	},
	{
		"Notes",
		"Notes",
		18,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		{
			6,
			ADF_Def_DOM_002_SEC_007_MAT_STRL,
			":"
		}
	},
	{
		"Caveats",
		"Caveats",
		19,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		{
			12,
			ADF_Def_DOM_002_SEC_008_MAT_STRL,
			":"
		}
	},
	{
		"See Also",
		"See Also",
		25,
		ADF_FALSE,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		{
			1,
			ADF_Def_DOM_002_SEC_009_MAT_STRL,
			"ALSO"
		}
	},
	{
		"Examples",
		"Examples",
		26,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		{
			3,
			ADF_Def_DOM_002_SEC_010_MAT_STRL,
			"EXAMPLE"
		}
	},
	{
		"Authors",
		"Authors",
		28,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		{
			10,
			ADF_Def_DOM_002_SEC_011_MAT_STRL,
			":"
		}
	},
	{
		"Copyrights",
		"Copyrights",
		36,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		{
			4,
			ADF_Def_DOM_002_SEC_012_MAT_STRL,
			":"
		}
	},
	{
		"Source File Name",
		"Source File Name",
		38,
		ADF_FALSE,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		{
			12,
			ADF_Def_DOM_002_SEC_013_MAT_STRL,
			"SOURCE"
		}
	},
	{
		"Source File Date",
		"Source File Date",
		39,
		ADF_FALSE,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		{
			9,
			ADF_Def_DOM_002_SEC_014_MAT_STRL,
			"DATE"
		}
	},
	{
		"Output Index",
		"Output Index",
		42,
		ADF_FALSE,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		{
			12,
			ADF_Def_DOM_002_SEC_015_MAT_STRL,
			":"
		}
	},
	{
		"Publish Xref",
		"Publish Xref",
		43,
		ADF_FALSE,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		{
			6,
			ADF_Def_DOM_002_SEC_016_MAT_STRL,
			"PUBLISH"
		}
	},
	{
		"Publish Name",
		"Publish Name",
		44,
		ADF_FALSE,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		{
			3,
			ADF_Def_DOM_002_SEC_017_MAT_STRL,
			"PUBLISH"
		}
	},
	{
		"Entry Class",
		"Entry Class",
		46,
		ADF_FALSE,
		ADF_FALSE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_TRUE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		ADF_FALSE,
		{
			6,
			ADF_Def_DOM_002_SEC_018_MAT_STRL,
			"ENTRY"
		}
	}
};
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Initialize domain file type lists.                                     	*/
/*	***********************************************************************	*/
static char *ADF_Def_DOM_000_FTYPE_STRL[1] = {
	"c"
};
static char *ADF_Def_DOM_001_FTYPE_STRL[1] = {
	"h"
};
static char *ADF_Def_DOM_002_FTYPE_STRL[1] = {
	"bin"
};
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Initialize domain pattern string lists.                                	*/
/*	***********************************************************************	*/
static char *ADF_Def_DOM_000_BOH_STRL[2] = {
	" /* BOH ",
	" // BOH "
};
static char *ADF_Def_DOM_000_EOH_STRL[2] = {
	" EOH */",
	" // EOH"
};
static char *ADF_Def_DOM_001_BOH_STRL[2] = {
	" /* BOH ",
	" // BOH "
};
static char *ADF_Def_DOM_001_EOH_STRL[2] = {
	" EOH */",
	" // EOH"
};
static char *ADF_Def_DOM_002_BOH_STRL[2] = {
	" /* BOH ",
	" // BOH "
};
static char *ADF_Def_DOM_002_EOH_STRL[2] = {
	" EOH */",
	" // EOH"
};
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Initialize the list of all domains.                                    	*/
/*	***********************************************************************	*/
static unsigned int ADF_DefaultDomainCount   = 3;
static ADF_DOMAIN   ADF_DefaultDomainList[3] = {
	{
		"C Language Domain",
		"This is the C language domain description.",
		1,
		ADF_Def_DOM_000_FTYPE_STRL,
		{
			2,
			ADF_Def_DOM_000_BOH_STRL,
			"BOH"
		},
		{
			2,
			ADF_Def_DOM_000_EOH_STRL,
			"EOH"
		},
		{
			0,
			NULL,
			NULL
		},
		{
			0,
			NULL,
			NULL
		},
		{
			0,
			NULL,
			NULL
		},
		{
			0,
			NULL,
			NULL
		},
		21,
		ADF_Def_DOM_000_SEC
	},
	{
		"C Language Header/Include File Domain",
		"This is the C language include file domain description.",
		1,
		ADF_Def_DOM_001_FTYPE_STRL,
		{
			2,
			ADF_Def_DOM_001_BOH_STRL,
			"BOH"
		},
		{
			2,
			ADF_Def_DOM_001_EOH_STRL,
			"EOH"
		},
		{
			0,
			NULL,
			NULL
		},
		{
			0,
			NULL,
			NULL
		},
		{
			0,
			NULL,
			NULL
		},
		{
			0,
			NULL,
			NULL
		},
		21,
		ADF_Def_DOM_001_SEC
	},
	{
		"Executable Program Domain",
		"This is the executable program domain description.",
		1,
		ADF_Def_DOM_002_FTYPE_STRL,
		{
			2,
			ADF_Def_DOM_002_BOH_STRL,
			"BOH"
		},
		{
			2,
			ADF_Def_DOM_002_EOH_STRL,
			"EOH"
		},
		{
			0,
			NULL,
			NULL
		},
		{
			0,
			NULL,
			NULL
		},
		{
			0,
			NULL,
			NULL
		},
		{
			0,
			NULL,
			NULL
		},
		19,
		ADF_Def_DOM_002_SEC
	}
};
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Copy the internal ADF definition.                                      	*/
/*	***********************************************************************	*/
#ifndef NARGS
int ADF_CopyDefaultDefSpec(unsigned int *domain_count,
	ADF_DOMAIN **domain_list, char *error_text)
#else
int ADF_CopyDefaultDefSpec(domain_count, domain_list, error_text)
unsigned int  *domain_count;
ADF_DOMAIN   **domain_list;
char          *error_text;
#endif /* #ifndef NARGS */
{
	return(ADF_COPY_DomainList(ADF_DefaultDomainCount, ADF_DefaultDomainList,
		domain_count, domain_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Get the internal ADF definition.                                       	*/
/*	***********************************************************************	*/
#ifndef NARGS
void ADF_GetDefaultDefSpec(unsigned int *domain_count,
	ADF_DOMAIN **domain_list)
#else
void ADF_GetDefaultDefSpec(domain_count, domain_list)
unsigned int  *domain_count;
ADF_DOMAIN   **domain_list;
#endif /* #ifndef NARGS */
{
	*domain_count = ADF_DefaultDomainCount;
	*domain_list  = ADF_DefaultDomainList;
}
/*	***********************************************************************	*/

