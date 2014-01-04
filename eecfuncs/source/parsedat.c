/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Expression Evaluation Calculator Library (EECFUNCS) Library Module		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	

	Revision History	:	1991-11-24 --- Creation.
									Michael L. Brock
								1993-04-04 --- Version 4 changes.
									Michael L. Brock
								1996-01-29 --- Version 5 initial cut.
									Michael L. Brock

		Copyright Michael L. Brock 1991 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include "parsedat.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
COMPAT_EXTERN_DATA_DEF const EEC_PARSE_CANON_OP
	EEC_OperatorList[EEC_OPERATOR_COUNT] = {
	{	"||",	"logical or",					0,
		EEC_TYPE_OPERATOR | EEC_TYPE_BOOL_OP							},
	{	"&&",	"logical and",					0,
		EEC_TYPE_OPERATOR | EEC_TYPE_BOOL_OP							},
	{	"!=",	"not equals",					1,
		EEC_TYPE_OPERATOR | EEC_TYPE_REL_OP								},
	{	"==",	"equals",						1,
		EEC_TYPE_OPERATOR | EEC_TYPE_REL_OP								},
	{	"<",	"less than",					2,
		EEC_TYPE_OPERATOR | EEC_TYPE_REL_OP								},
	{	"<=",	"less than or equals",		2,
		EEC_TYPE_OPERATOR | EEC_TYPE_REL_OP								},
	{	">",	"greater than",				2,
		EEC_TYPE_OPERATOR | EEC_TYPE_REL_OP								},
	{	">=",	"greater than or equals",	2,
		EEC_TYPE_OPERATOR | EEC_TYPE_REL_OP								},
	{	"-",	"subtraction (minus)",		3,
		EEC_TYPE_OPERATOR | EEC_TYPE_NUMBER_OP | EEC_TYPE_NUMBER	},
	{	"+",	"addition (plus)",			3,
		EEC_TYPE_OPERATOR | EEC_TYPE_NUMBER_OP | EEC_TYPE_NUMBER	},
	{	"%",	"modulus",						4,
		EEC_TYPE_OPERATOR | EEC_TYPE_NUMBER_OP | EEC_TYPE_NUMBER	},
	{	"&",	"concatenation",				4,
		EEC_TYPE_OPERATOR | EEC_TYPE_STRING_OP | EEC_TYPE_STRING	},
	{	"\\",	"integer division",			4,
		EEC_TYPE_OPERATOR | EEC_TYPE_NUMBER_OP | EEC_TYPE_NUMBER	},
	{	"/",	"division",						4,
		EEC_TYPE_OPERATOR | EEC_TYPE_NUMBER_OP | EEC_TYPE_NUMBER	},
	{	"*",	"multiplication",				4,
		EEC_TYPE_OPERATOR | EEC_TYPE_NUMBER_OP | EEC_TYPE_NUMBER	},
	{	"^",	"power",							5,
		EEC_TYPE_OPERATOR | EEC_TYPE_NUMBER_OP | EEC_TYPE_NUMBER	}
};
/*	***********************************************************************	*/

/*	***********************************************************************	*/
COMPAT_EXTERN_DATA_DEF const EEC_PARSE_OP_ALIAS
	EEC_OperatorAliasList[]              = {
	{	"^",		1,	EEC_OPERATOR_POWER			},
	{	"**",		2,	EEC_OPERATOR_POWER			},
	{	"*",		1,	EEC_OPERATOR_MULTIPLY		},
	{	"/",		1,	EEC_OPERATOR_DIVIDE			},
	{	"\\",		1,	EEC_OPERATOR_INT_DIVIDE		},
	{	"%",		1,	EEC_OPERATOR_MOD				},
	{	"#MOD#",	5,	EEC_OPERATOR_MOD				},
	{	"+",		1,	EEC_OPERATOR_PLUS				},
	{	"-",		1,	EEC_OPERATOR_MINUS			},
	{	">=",		2,	EEC_OPERATOR_GE				},
	{	"=>",		2,	EEC_OPERATOR_GE				},
	{	"#GE#",	4,	EEC_OPERATOR_GE				},
	{	"!=",		2,	EEC_OPERATOR_NE				},
	{	"=!",		2,	EEC_OPERATOR_NE				},
	{	"<>",		2,	EEC_OPERATOR_NE				},
	{	"><",		2,	EEC_OPERATOR_NE				},
	{	"#NE#",	4,	EEC_OPERATOR_NE				},
	{	">",		1,	EEC_OPERATOR_GT				},
	{	"#GT#",	4,	EEC_OPERATOR_GT				},
	{	"<=",		2,	EEC_OPERATOR_LE				},
	{	"=<",		2,	EEC_OPERATOR_LE				},
	{	"#LE#",	4,	EEC_OPERATOR_LE				},
	{	"<",		1,	EEC_OPERATOR_LT				},
	{	"#LT#",	4,	EEC_OPERATOR_LT				},
	{	"==",		2,	EEC_OPERATOR_EQ				},
	{	"=",		1,	EEC_OPERATOR_EQ				},
	{	"#EQ#",	4,	EEC_OPERATOR_EQ				},
	{	"&&",		2,	EEC_OPERATOR_AND				},
	{	"#AND#",	5,	EEC_OPERATOR_AND				},
	{	"||",		2,	EEC_OPERATOR_OR				},
	{	"#OR#",	4,	EEC_OPERATOR_OR				},
	{	"&",		1, EEC_OPERATOR_CONCAT			}
};
COMPAT_EXTERN_DATA_DEF const unsigned int EEC_OperatorAliasCount   =
	sizeof(EEC_OperatorAliasList) / sizeof(EEC_OperatorAliasList[0]);
/*	***********************************************************************	*/

/*	***********************************************************************	*/
COMPAT_EXTERN_DATA_DEF const EEC_EXPR_TYPE_LINKAGE
	EEC_ExprTypeLinkageList[]         = {
	{	"begin",								EEC_TYPE_BEGIN			},
	{	"number",							EEC_TYPE_NUMBER		},
	{	"string",							EEC_TYPE_STRING		},
	{	"numeric operator",				EEC_TYPE_NUMBER_OP	},
	{	"relational operator",			EEC_TYPE_REL_OP		},
	{	"boolean operator",				EEC_TYPE_BOOL_OP		},
	{	"string operator",				EEC_TYPE_STRING_OP	},
	{	"operator",							EEC_TYPE_OPERATOR		},
	{	"function",							EEC_TYPE_FUNCTION		},
	{	"symbol name",						EEC_TYPE_SYMBOL		},
	{	"parenthetical expression",	EEC_TYPE_PAREND		},
};
COMPAT_EXTERN_DATA_DEF const unsigned int EEC_ExprTypeLinkageCount =
	sizeof(EEC_ExprTypeLinkageList) / sizeof(EEC_ExprTypeLinkageList[0]);
/*	***********************************************************************	*/

