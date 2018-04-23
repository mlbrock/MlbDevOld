/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes data for the regression tests.

	Revision History	:	1998-03-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2018.
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

#include <tfread.h>

#include "kmlfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(void KML_TEST_InitializeDomainList,
	(KML_DOMAIN *domain_list));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#define TEST_DOMAIN_COUNT					4
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	The C test domain . . .																	*/
/*	***********************************************************************	*/
static const char         *C_DomainName    = "C Domain";
static const char         *C_DomainDescrip = "C Language Source File Domain";
static const char         *C_TypeList[]    = { "c", "h" };
static const unsigned int  C_TypeCount     =
	sizeof(C_TypeList) / sizeof(C_TypeList[0]);
	/*	*****************************************************************	*/
static const int          C_StringCaseFlag = KMLFUNCS_TRUE;
	/* This list of structures must be sorted by the first member. */
static const KML_STRING   C_StringList[]   = {
	{	"\"",		1,	"\\",	1,	"\"",	1	},
	{	"L\"",	2,	"\\",	1,	"\"",	1	},
	{	"\'",		1,	"\\",	1,	"\'",	1	},
	{	"L\'",	2,	"\\",	1,	"\'",	1	}
};
static const unsigned int C_StringCount    =
	sizeof(C_StringList) / sizeof(C_StringList[0]);
	/*	*****************************************************************	*/
static const int          C_CommentCaseFlag = KMLFUNCS_TRUE;
	/* This list of structures must be sorted by the first member. */
static const KML_COMMENT  C_CommentList[]   = {
	{	"/*",	2,	"*/",	2	},
	{	"//",	2,	"",	0	}
};
static const unsigned int C_CommentCount    =
	sizeof(C_CommentList) / sizeof(C_CommentList[0]);
	/*	*****************************************************************	*/
static const int          C_KeywordCaseFlag = KMLFUNCS_TRUE;
	/* This list of structures must be sorted by the first member. */
static const KML_KEYWORD  C_KeywordList[]   = {
	{	"auto",		4	},
	{	"break",		5	},
	{	"case",		4	},
	{	"char",		4	},
	{	"const",		5	},
	{	"continue",	8	},
	{	"default",	7	},
	{	"do",			2	},
	{	"double",	6	},
	{	"else",		4	},
	{	"enum",		4	},
	{	"extern",	6	},
	{	"float",		5	},
	{	"for",		3	},
	{	"goto",		4	},
	{	"if",			2	},
	{	"int",		3	},
	{	"long",		4	},
	{	"register",	8	},
	{	"return",	6	},
	{	"short",		5	},
	{	"signed",	6	},
	{	"sizeof",	6	},
	{	"static",	6	},
	{	"struct",	6	},
	{	"switch",	6	},
	{	"typedef",	7	},
	{	"union",		5	},
	{	"unsigned",	8	},
	{	"void",		4	},
	{	"volatile",	8	},
	{	"while",		5	}
};
static const unsigned int C_KeywordCount    =
	sizeof(C_KeywordList) / sizeof(C_KeywordList[0]);
	/*	*****************************************************************	*/
static const int         C_SymbolCaseFlag = KMLFUNCS_TRUE;
	/* This list of structures must be sorted by the first member. */
static const KML_SYMBOL  C_SymbolList[]   = {
	{	"...",	3	},
	{	"->",		2	},
	{	"(",		1	},
	{	")",		1	},
	{	":",		1	},
	{	";",		1	},
	{	",",		1	},
	{	".",		1	},
	{	"?",		1	},
	{	"[",		1	},
	{	"]",		1	},
	{	"{",		1	},
	{	"}",		1	}
};
static const unsigned int C_SymbolCount    =
	sizeof(C_SymbolList) / sizeof(C_SymbolList[0]);
	/*	*****************************************************************	*/
static const int          C_BlockCaseFlag = KMLFUNCS_TRUE;
	/* This list of structures must be sorted by the first member. */
static const KML_BLOCK    C_BlockList[]   = {
	{	"{",	1,	"}",	1	}
};
static const unsigned int C_BlockCount    =
	sizeof(C_BlockList) / sizeof(C_BlockList[0]);
	/*	*****************************************************************	*/
static const int          C_OperatorCaseFlag = KMLFUNCS_TRUE;
	/* This list of structures must be sorted by the first member. */
static const KML_OPERATOR C_OperatorList[]   = {
	{	"<<=",	3,	KML_OP_TYPE_ASSIGN	|	KML_OP_TYPE_SHIFT		},
	{	">>=",	3,	KML_OP_TYPE_ASSIGN	|	KML_OP_TYPE_SHIFT		},
	{	"!=",		2,	KML_OP_TYPE_EQUIV										},
	{	"%=",		2,	KML_OP_TYPE_ASSIGN									},
	{	"&&",		2,	KML_OP_TYPE_INFIX		|	KML_OP_TYPE_LOGICAL	},
	{	"&=",		2,	KML_OP_TYPE_ASSIGN	|	KML_OP_TYPE_BITWISE	},
	{	"*=",		2,	KML_OP_TYPE_ASSIGN									},
	{	"++",		2,	KML_OP_TYPE_OUTFIX									},
	{	"+=",		2,	KML_OP_TYPE_ASSIGN									},
	{	"--",		2,	KML_OP_TYPE_OUTFIX									},
	{	"-=",		2,	KML_OP_TYPE_ASSIGN									},
	{	"/=",		2,	KML_OP_TYPE_ASSIGN									},
	{	"<<",		2,	KML_OP_TYPE_INFIX		|	KML_OP_TYPE_SHIFT		},
	{	"<=",		2,	KML_OP_TYPE_EQUIV										},
	{	"==",		2,	KML_OP_TYPE_EQUIV										},
	{	">=",		2,	KML_OP_TYPE_EQUIV										},
	{	">>",		2,	KML_OP_TYPE_INFIX		|	KML_OP_TYPE_SHIFT		},
	{	"^=",		2,	KML_OP_TYPE_ASSIGN	|	KML_OP_TYPE_BITWISE	},
	{	"|=",		2,	KML_OP_TYPE_ASSIGN	|	KML_OP_TYPE_BITWISE	},
	{	"||",		2,	KML_OP_TYPE_INFIX		|	KML_OP_TYPE_LOGICAL	},
	{	"!",		1,	KML_OP_TYPE_PREFIX	|	KML_OP_TYPE_BITWISE	},
	{	"~",		1,	KML_OP_TYPE_PREFIX	|	KML_OP_TYPE_BITWISE	},
	{	"%",		1,	KML_OP_TYPE_INFIX										},
	{	"&",		1,	KML_OP_TYPE_INFIX		|	KML_OP_TYPE_BITWISE	},
	{	"*",		1,	KML_OP_TYPE_INFIX										},
	{	"+",		1,	KML_OP_TYPE_INFIX										},
	{	"-",		1,	KML_OP_TYPE_INFIX										},
	{	"/",		1,	KML_OP_TYPE_INFIX										},
	{	"<",		1,	KML_OP_TYPE_EQUIV										},
	{	"=",		1,	KML_OP_TYPE_ASSIGN									},
	{	">",		1,	KML_OP_TYPE_EQUIV										},
	{	"^",		1,	KML_OP_TYPE_INFIX		|	KML_OP_TYPE_BITWISE	},
	{	"|",		1,	KML_OP_TYPE_INFIX		|	KML_OP_TYPE_BITWISE	}
};
static const unsigned int C_OperatorCount    = 
	sizeof(C_OperatorList) / sizeof(C_OperatorList[0]);
	/*	*****************************************************************	*/
static const int          C_NameCaseFlag = KMLFUNCS_TRUE;
	/* This list of structures must be sorted by the first member. */
static const KML_NAME     C_NameList[]   = {
	{	"_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz",
		"_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"	}
};
static const unsigned int C_NameCount    = 
	sizeof(C_NameList) / sizeof(C_NameList[0]);
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	The C++ test domain . . .																*/
/*	***********************************************************************	*/
static const char         *Cpp_DomainName    = "C++ Domain";
static const char         *Cpp_DomainDescrip = "C++ Language Source File Domain";
static const char         *Cpp_TypeList[]    = { "cpp", "hpp", "cxx", "hxx" };
static const unsigned int  Cpp_TypeCount     =
	sizeof(Cpp_TypeList) / sizeof(Cpp_TypeList[0]);
	/*	*****************************************************************	*/
static const int          Cpp_StringCaseFlag = KMLFUNCS_TRUE;
	/* This list of structures must be sorted by the first member. */
static const KML_STRING   Cpp_StringList[]   = {
	{	"\"",		1,	"\\",	1,	"\"",	1	},
	{	"L\"",	2,	"\\",	1,	"\"",	1	},
	{	"\'",		1,	"\\",	1,	"\'",	1	},
	{	"L\'",	2,	"\\",	1,	"\'",	1	}
};
static const unsigned int Cpp_StringCount    =
	sizeof(Cpp_StringList) / sizeof(Cpp_StringList[0]);
	/*	*****************************************************************	*/
static const int          Cpp_CommentCaseFlag = KMLFUNCS_TRUE;
	/* This list of structures must be sorted by the first member. */
static const KML_COMMENT  Cpp_CommentList[]   = {
	{	"/*",	2,	"*/",	2	},
	{	"//",	2,	"",	0	}
};
static const unsigned int Cpp_CommentCount    =
	sizeof(Cpp_CommentList) / sizeof(Cpp_CommentList[0]);
	/*	*****************************************************************	*/
static const int          Cpp_KeywordCaseFlag = KMLFUNCS_TRUE;
	/* This list of structures must be sorted by the first member. */
static const KML_KEYWORD  Cpp_KeywordList[]   = {
	{	"asm",					 3	},
	{	"auto",					 4	},
	{	"bool",					 4	},
	{	"break",					 5	},
	{	"case",					 4	},
	{	"catch",					 5	},
	{	"char",					 4	},
	{	"class",					 5	},
	{	"const",					 5	},
	{	"const_cast",			10	},
	{	"continue",				 8	},
	{	"default",				 7	},
	{	"delete",				 6	},
	{	"do",						 2	},
	{	"double",				 6	},
	{	"dynamic_cast",		12	},
	{	"else",					 4	},
	{	"enum",					 4	},
	{	"explicit",				 8	},
	{	"export",				 6	},
	{	"extern",				 6	},
	{	"false",					 5	},
	{	"float",					 5	},
	{	"for",					 3	},
	{	"friend",				 6	},
	{	"goto",					 4	},
	{	"if",						 2	},
	{	"inline",				 6	},
	{	"int",					 3	},
	{	"long",					 4	},
	{	"mutable",				 7	},
	{	"namespace",		 	 9	},
	{	"new",					 3	},
	{	"operator",				 8	},
	{	"private",				 7	},
	{	"protected",			 9	},
	{	"public",				 6	},
	{	"register",				 8	},
	{	"reinterpret_cast",	16	},
	{	"return",				 6	},
	{	"short",					 5	},
	{	"signed",				 6	},
	{	"sizeof",				 6	},
	{	"static",				 6	},
	{	"static_cast",			11	},
	{	"struct",				 6	},
	{	"switch",				 6	},
	{	"template",				 8	},
	{	"this",					 4	},
	{	"throw",					 5	},
	{	"true",					 4	},
	{	"try",					 3	},
	{	"typedef",				 7	},
	{	"typeid",				 6	},
	{	"typename",				 8	},
	{	"union",					 5	},
	{	"unsigned",				 8	},
	{	"using",					 5	},
	{	"virtual",				 7	},
	{	"void",					 4	},
	{	"volatile",				 8	},
	{	"wchar_t",				 6	},
	{	"while",					 5	}
};
static const unsigned int Cpp_KeywordCount    =
	sizeof(Cpp_KeywordList) / sizeof(Cpp_KeywordList[0]);
	/*	*****************************************************************	*/
static const int         Cpp_SymbolCaseFlag = KMLFUNCS_TRUE;
	/* This list of structures must be sorted by the first member. */
static const KML_SYMBOL  Cpp_SymbolList[]   = {
	{	"...",	3	},
	{	"->",		2	},
	{	"(",		1	},
	{	")",		1	},
	{	":",		1	},
	{	";",		1	},
	{	",",		1	},
	{	".",		1	},
	{	"?",		1	},
	{	"[",		1	},
	{	"]",		1	},
	{	"{",		1	},
	{	"}",		1	}
};
static const unsigned int Cpp_SymbolCount    =
	sizeof(Cpp_SymbolList) / sizeof(Cpp_SymbolList[0]);
	/*	*****************************************************************	*/
static const int          Cpp_BlockCaseFlag = KMLFUNCS_TRUE;
	/* This list of structures must be sorted by the first member. */
static const KML_BLOCK    Cpp_BlockList[]   = {
	{	"{",	1,	"}",	1	}
};
static const unsigned int Cpp_BlockCount    =
	sizeof(Cpp_BlockList) / sizeof(Cpp_BlockList[0]);
	/*	*****************************************************************	*/
static const int          Cpp_OperatorCaseFlag = KMLFUNCS_TRUE;
	/* This list of structures must be sorted by the first member. */
static const KML_OPERATOR Cpp_OperatorList[]   = {
	{	"<<=",		3,	KML_OP_TYPE_ASSIGN	|	KML_OP_TYPE_SHIFT		},
	{	">>=",		3,	KML_OP_TYPE_ASSIGN	|	KML_OP_TYPE_SHIFT		},
	{	"!=",			2,	KML_OP_TYPE_EQUIV										},
	{	"%=",			2,	KML_OP_TYPE_ASSIGN									},
	{	"&&",			2,	KML_OP_TYPE_INFIX		|	KML_OP_TYPE_LOGICAL	},
	{	"&=",			2,	KML_OP_TYPE_ASSIGN	|	KML_OP_TYPE_BITWISE	},
	{	"*=",			2,	KML_OP_TYPE_ASSIGN									},
	{	"++",			2,	KML_OP_TYPE_OUTFIX									},
	{	"+=",			2,	KML_OP_TYPE_ASSIGN									},
	{	"--",			2,	KML_OP_TYPE_OUTFIX									},
	{	"-=",			2,	KML_OP_TYPE_ASSIGN									},
	{	"/=",			2,	KML_OP_TYPE_ASSIGN									},
	{	"<<",			2,	KML_OP_TYPE_INFIX		|	KML_OP_TYPE_SHIFT		},
	{	"<=",			2,	KML_OP_TYPE_EQUIV										},
	{	"==",			2,	KML_OP_TYPE_EQUIV										},
	{	">=",			2,	KML_OP_TYPE_EQUIV										},
	{	">>",			2,	KML_OP_TYPE_INFIX		|	KML_OP_TYPE_SHIFT		},
	{	"^=",			2,	KML_OP_TYPE_ASSIGN	|	KML_OP_TYPE_BITWISE	},
	{	"|=",			2,	KML_OP_TYPE_ASSIGN	|	KML_OP_TYPE_BITWISE	},
	{	"||",			2,	KML_OP_TYPE_INFIX		|	KML_OP_TYPE_LOGICAL	},
	{	"!",			1,	KML_OP_TYPE_PREFIX	|	KML_OP_TYPE_BITWISE	},
	{	"~",			1,	KML_OP_TYPE_PREFIX	|	KML_OP_TYPE_BITWISE	},
	{	"%",			1,	KML_OP_TYPE_INFIX										},
	{	"&",			1,	KML_OP_TYPE_INFIX		|	KML_OP_TYPE_BITWISE	},
	{	"*",			1,	KML_OP_TYPE_INFIX										},
	{	"+",			1,	KML_OP_TYPE_INFIX										},
	{	"-",			1,	KML_OP_TYPE_INFIX										},
	{	"/",			1,	KML_OP_TYPE_INFIX										},
	{	"<",			1,	KML_OP_TYPE_EQUIV										},
	{	"=",			1,	KML_OP_TYPE_ASSIGN									},
	{	">",			1,	KML_OP_TYPE_EQUIV										},
	{	"^",			1,	KML_OP_TYPE_INFIX		|	KML_OP_TYPE_BITWISE	},
	{	"|",			1,	KML_OP_TYPE_INFIX		|	KML_OP_TYPE_BITWISE	},
	{	"and",		3,	KML_OP_TYPE_INFIX		|	KML_OP_TYPE_LOGICAL	},
	{	"and_eq",	6,	KML_OP_TYPE_ASSIGN	|	KML_OP_TYPE_BITWISE	},
	{	"bitand",	6,	KML_OP_TYPE_INFIX		|	KML_OP_TYPE_BITWISE	},
	{	"bitor",		5,	KML_OP_TYPE_INFIX		|	KML_OP_TYPE_BITWISE	},
	{	"compl",		5,	KML_OP_TYPE_PREFIX	|	KML_OP_TYPE_BITWISE	},
	{	"not",		3,	KML_OP_TYPE_PREFIX	|	KML_OP_TYPE_BITWISE	},
	{	"not_eq",	6,	KML_OP_TYPE_EQUIV										},
	{	"or",			2,	KML_OP_TYPE_INFIX		|	KML_OP_TYPE_LOGICAL	},
	{	"or_eq",		5,	KML_OP_TYPE_ASSIGN	|	KML_OP_TYPE_BITWISE	},
	{	"xor",		3,	KML_OP_TYPE_INFIX		|	KML_OP_TYPE_BITWISE	},
	{	"xor_eq",	6,	KML_OP_TYPE_ASSIGN	|	KML_OP_TYPE_BITWISE	}
};
static const unsigned int Cpp_OperatorCount    = 
	sizeof(Cpp_OperatorList) / sizeof(Cpp_OperatorList[0]);
	/*	*****************************************************************	*/
static const int          Cpp_NameCaseFlag = KMLFUNCS_TRUE;
	/* This list of structures must be sorted by the first member. */
static const KML_NAME     Cpp_NameList[]   = {
	{	"_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz",
		"_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"	}
};
static const unsigned int Cpp_NameCount    = 
	sizeof(Cpp_NameList) / sizeof(Cpp_NameList[0]);
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	The Java test domain . . .																*/
/*	***********************************************************************	*/
static const char         *Java_DomainName    = "Java Domain";
static const char         *Java_DomainDescrip = "Java Language Source File Domain";
static const char         *Java_TypeList[]    = { "java" };
static const unsigned int  Java_TypeCount     =
	sizeof(Java_TypeList) / sizeof(Java_TypeList[0]);
	/*	*****************************************************************	*/
static const int          Java_StringCaseFlag = KMLFUNCS_TRUE;
	/* This list of structures must be sorted by the first member. */
static const KML_STRING   Java_StringList[]   = {
	{	"\"",	1,	"\\",	1,	"\"",	1	},
	{	"\'",	1,	"\\",	1,	"\'",	1	}
};
static const unsigned int Java_StringCount    =
	sizeof(Java_StringList) / sizeof(Java_StringList[0]);
	/*	*****************************************************************	*/
static const int          Java_CommentCaseFlag = KMLFUNCS_TRUE;
	/* This list of structures must be sorted by the first member. */
static const KML_COMMENT  Java_CommentList[]   = {
	{	"/*",		2,	"*/",	2	},
	{	"/**",	2,	"*/",	2	},
	{	"//",		2,	"",	0	}
};
static const unsigned int Java_CommentCount    =
	sizeof(Java_CommentList) / sizeof(Java_CommentList[0]);
	/*	*****************************************************************	*/
static const int          Java_KeywordCaseFlag = KMLFUNCS_TRUE;
	/* This list of structures must be sorted by the first member. */
static const KML_KEYWORD  Java_KeywordList[]   = {
	{	"abstract",		 8	},
	{	"boolean",		 7	},
	{	"break",			 5	},
	{	"byte",			 4	},
	{	"byvalue",		 7	},
	{	"case",			 4	},
	{	"cast",			 4	},
	{	"catch",			 5	},
	{	"char",			 4	},
	{	"class",			 5	},
	{	"const",			 5	},
	{	"continue",		 8	},
	{	"default",		 7	},
	{	"do",				 2	},
	{	"double",		 6	},
	{	"else",			 4	},
	{	"extends",		 7	},
	{	"false",			 5	},
	{	"final",			 5	},
	{	"finally",		 7	},
	{	"float",			 5	},
	{	"for",			 3	},
	{	"future",		 6	},
	{	"generic",		 7	},
	{	"goto",			 4	},
	{	"if",				 2	},
	{	"implements",	10	},
	{	"import",		 6	},
	{	"inner",			 5	},
	{	"instanceof",	10	},
	{	"int",			 3	},
	{	"interface",	 9	},
	{	"long",			 4	},
	{	"native",		 6	},
	{	"new",			 3	},
	{	"null",			 4	},
	{	"operator",		 8	},
	{	"outer",			 5	},
	{	"package",		 7	},
	{	"private",		 7	},
	{	"protected",	 9	},
	{	"public",		 6	},
	{	"rest",			 4	},
	{	"return",		 6	},
	{	"short",			 5	},
	{	"static",		 6	},
	{	"super",			 5	},
	{	"switch",		 6	},
	{	"sychronized",	11	},
	{	"this",			 4	},
	{	"throw",			 5	},
	{	"throws",		 6	},
	{	"transient",	 9	},
	{	"true",			 4	},
	{	"try",			 3	},
	{	"var",			 3	},
	{	"void",			 4	},
	{	"volatile",		 8	},
	{	"while",			 5	}
};
static const unsigned int Java_KeywordCount    =
	sizeof(Java_KeywordList) / sizeof(Java_KeywordList[0]);
	/*	*****************************************************************	*/
static const int         Java_SymbolCaseFlag = KMLFUNCS_TRUE;
	/* This list of structures must be sorted by the first member. */
static const KML_SYMBOL  Java_SymbolList[]   = {
	{	"(",		1	},
	{	")",		1	},
	{	":",		1	},
	{	";",		1	},
	{	",",		1	},
	{	".",		1	},
	{	"?",		1	},
	{	"[",		1	},
	{	"]",		1	},
	{	"{",		1	},
	{	"}",		1	}
};
static const unsigned int Java_SymbolCount    =
	sizeof(Java_SymbolList) / sizeof(Java_SymbolList[0]);
	/*	*****************************************************************	*/
static const int          Java_BlockCaseFlag = KMLFUNCS_TRUE;
	/* This list of structures must be sorted by the first member. */
static const KML_BLOCK    Java_BlockList[]   = {
	{	"{",	1,	"}",	1	}
};
static const unsigned int Java_BlockCount    =
	sizeof(Java_BlockList) / sizeof(Java_BlockList[0]);
	/*	*****************************************************************	*/
static const int          Java_OperatorCaseFlag = KMLFUNCS_TRUE;
	/* This list of structures must be sorted by the first member. */
static const KML_OPERATOR Java_OperatorList[]   = {
	{	"<<=",	3,	KML_OP_TYPE_ASSIGN	|	KML_OP_TYPE_SHIFT		},
	{	">>=",	3,	KML_OP_TYPE_ASSIGN	|	KML_OP_TYPE_SHIFT		},
	{	"!=",		2,	KML_OP_TYPE_EQUIV										},
	{	"%=",		2,	KML_OP_TYPE_ASSIGN									},
	{	"&&",		2,	KML_OP_TYPE_INFIX		|	KML_OP_TYPE_LOGICAL	},
	{	"&=",		2,	KML_OP_TYPE_ASSIGN	|	KML_OP_TYPE_BITWISE	},
	{	"*=",		2,	KML_OP_TYPE_ASSIGN									},
	{	"++",		2,	KML_OP_TYPE_OUTFIX									},
	{	"+=",		2,	KML_OP_TYPE_ASSIGN									},
	{	"--",		2,	KML_OP_TYPE_OUTFIX									},
	{	"-=",		2,	KML_OP_TYPE_ASSIGN									},
	{	"/=",		2,	KML_OP_TYPE_ASSIGN									},
	{	"<<",		2,	KML_OP_TYPE_INFIX		|	KML_OP_TYPE_SHIFT		},
	{	"<=",		2,	KML_OP_TYPE_EQUIV										},
	{	"==",		2,	KML_OP_TYPE_EQUIV										},
	{	">=",		2,	KML_OP_TYPE_EQUIV										},
	{	">>",		2,	KML_OP_TYPE_INFIX		|	KML_OP_TYPE_SHIFT		},
	{	"^=",		2,	KML_OP_TYPE_ASSIGN	|	KML_OP_TYPE_BITWISE	},
	{	"|=",		2,	KML_OP_TYPE_ASSIGN	|	KML_OP_TYPE_BITWISE	},
	{	"||",		2,	KML_OP_TYPE_INFIX		|	KML_OP_TYPE_LOGICAL	},
	{	"!",		1,	KML_OP_TYPE_PREFIX	|	KML_OP_TYPE_BITWISE	},
	{	"~",		1,	KML_OP_TYPE_PREFIX	|	KML_OP_TYPE_BITWISE	},
	{	"%",		1,	KML_OP_TYPE_INFIX										},
	{	"&",		1,	KML_OP_TYPE_INFIX		|	KML_OP_TYPE_BITWISE	},
	{	"*",		1,	KML_OP_TYPE_INFIX										},
	{	"+",		1,	KML_OP_TYPE_INFIX										},
	{	"-",		1,	KML_OP_TYPE_INFIX										},
	{	"/",		1,	KML_OP_TYPE_INFIX										},
	{	"<",		1,	KML_OP_TYPE_EQUIV										},
	{	"=",		1,	KML_OP_TYPE_ASSIGN									},
	{	">",		1,	KML_OP_TYPE_EQUIV										},
	{	"^",		1,	KML_OP_TYPE_INFIX		|	KML_OP_TYPE_BITWISE	},
	{	"|",		1,	KML_OP_TYPE_INFIX		|	KML_OP_TYPE_BITWISE	}
};
static const unsigned int Java_OperatorCount    = 
	sizeof(Java_OperatorList) / sizeof(Java_OperatorList[0]);
	/*	*****************************************************************	*/
static const int          Java_NameCaseFlag = KMLFUNCS_TRUE;
	/* This list of structures must be sorted by the first member. */
static const KML_NAME     Java_NameList[]   = {
	{	"_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz",
		"_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"	}
};
static const unsigned int Java_NameCount    = 
	sizeof(Java_NameList) / sizeof(Java_NameList[0]);
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	The Sybase test domain . . .															*/
/*	***********************************************************************	*/
static const char         *Sybase_DomainName    = "Sybase Domain";
static const char         *Sybase_DomainDescrip = "Sybase SQL Language Domain";
static const char         *Sybase_TypeList[]    = { "sql", "ddl", "prc" };
static const unsigned int  Sybase_TypeCount     =
	sizeof(Sybase_TypeList) / sizeof(Sybase_TypeList[0]);
	/*	*****************************************************************	*/
static const int          Sybase_StringCaseFlag = KMLFUNCS_FALSE;
	/* This list of structures must be sorted by the first member. */
static const KML_STRING   Sybase_StringList[]   = {
	{	"\"",	1,	"\"\"",	2,	"\"",	1	},
	{	"\'",	1,	"\'\'",	2,	"\'",	1	}
};
static const unsigned int Sybase_StringCount    =
	sizeof(Sybase_StringList) / sizeof(Sybase_StringList[0]);
	/*	*****************************************************************	*/
static const int          Sybase_CommentCaseFlag = KMLFUNCS_FALSE;
	/* This list of structures must be sorted by the first member. */
static const KML_COMMENT  Sybase_CommentList[]   = {
	{	"/*",	2,	"*/",	2	},
	{	"--",	2,	"",	0	}
};
static const unsigned int Sybase_CommentCount    =
	sizeof(Sybase_CommentList) / sizeof(Sybase_CommentList[0]);
	/*	*****************************************************************	*/
static const int          Sybase_KeywordCaseFlag = KMLFUNCS_FALSE;
	/* This list of structures must be sorted by the first member. */
static const KML_KEYWORD  Sybase_KeywordList[]   = {
	{	"begin transaction",		17	},
	{	"begin tran",				10	},
	{	"begin work",				10	},
	{	"add",						 3	},
	{	"all",						 3	},
	{	"alter",						 5	},
	{	"and",						 3	},
	{	"any",						 3	},
	{	"arith_overflow",		  	14	},
	{	"as",							 2	},
	{	"asc",						 3	},
	{	"at",							 2	},
	{	"authorization",		  	13	},
	{	"avg",						 3	},
	{	"begin",						 5	},
	{	"between",				  	 7	},
	{	"break",						 5	},
	{	"browse",				  	 6	},
	{	"bulk",						 4	},
	{	"by",							 2	},
	{	"cascade",				  	 7	},
	{	"char_convert",		  	12	},
	{	"check",						 5	},
	{	"checkpoint",			  	10	},
	{	"close",						 5	},
	{	"clustered",			  	 9	},
	{	"commit",				  	 6	},
	{	"compute",				  	 7	},
	{	"confirm",				  	 7	},
	{	"constraint",			  	10	},
	{	"continue",					 8	},
	{	"controlrow",				10	},
	{	"convert",				  	 7	},
	{	"count",						 5	},
	{	"create",				  	 6	},
	{	"current",				  	 7	},
	{	"cursor",				  	 6	},
	{	"data_pgs",				  	 8	},
	{	"database",				  	 8	},
	{	"dbcc",						 4	},
	{	"deallocate",			  	10	},
	{	"declare",				  	 7	},
	{	"default",				  	 7	},
	{	"delete",				  	 6	},
	{	"desc",						 4	},
	{	"disk",						 4	},
	{	"distinct",				  	 8	},
	{	"double",				  	 6	},
	{	"drop",						 4	},
	{	"dummy",						 5	},
	{	"dump",						 4	},
	{	"else",						 4	},
	{	"end",						 3	},
	{	"endtran",				  	 7	},
	{	"errlvl",				  	 6	},
	{	"errorexit",			  	 9	},
	{	"escape",				  	 6	},
	{	"except",				  	 6	},
	{	"exec",						 4	},
	{	"execute",				  	 7	},
	{	"exists",				  	 6	},
	{	"exit",						 4	},
	{	"fetch",						 5	},
	{	"fillfactor",			  	10	},
	{	"for",						 3	},
	{	"foreign",				  	 7	},
	{	"from",						 4	},
	{	"goto",						 4	},
	{	"grant",						 5	},
	{	"group",						 5	},
	{	"having",				  	 6	},
	{	"holdlock",				  	 8	},
	{	"identity",				  	 8	},
	{	"identity_insert",	  	15	},
	{	"if",							 2	},
	{	"in",							 2	},
	{	"index",						 5	},
	{	"insert",				  	 6	},
	{	"intersect",			  	 9	},
	{	"into",						 4	},
	{	"is",							 2	},
	{	"isolation",			  	 9	},
	{	"key",						 3	},
	{	"kill",						 4	},
	{	"level",						 5	},
	{	"like",						 4	},
	{	"lineno",				  	 6	},
	{	"load",						 4	},
	{	"max",						 3	},
	{	"min",						 3	},
	{	"mirror",				  	 6	},
	{	"mirrorexit",			  	10	},
	{	"national",				  	 8	},
	{	"noholdlock",			  	10	},
	{	"nonclustered",		  	12	},
	{	"not",						 3	},
	{	"null",						 4	},
	{	"numeric_truncation",  	18	},
	{	"of",							 2	},
	{	"off",						 3	},
	{	"offsets",					 7	},
	{	"on",							 2	},
	{	"once",						 4	},
	{	"only",						 4	},
	{	"open",						 4	},
	{	"option",					 6	},
	{	"or",							 2	},
	{	"order",						 5	},
	{	"over",						 4	},
	{	"perm",						 4	},
	{	"permanent",			  	 9	},
	{	"plan",						 4	},
	{	"precision",			  	 9	},
	{	"prepare",				  	 7	},
	{	"primary",				  	 7	},
	{	"print",						 5	},
	{	"privileges",			  	10	},
	{	"proc",						 4	},
	{	"procedure",			  	 9	},
	{	"processexit",			  	11	},
	{	"public",				  	 6	},
	{	"raiserror",			  	 9	},
	{	"read",						 4	},
	{	"readtext",				  	 8	},
	{	"reconfigure",			  	11	},
	{	"references",			  	10	},
	{	"replace",				  	 7	},
	{	"reserved_pgs",		  	12	},
	{	"return",				  	 6	},
	{	"revoke",				  	 6	},
	{	"role",						 4	},
	{	"rollback",				  	 8	},
	{	"rowcnt",				  	 6	},
	{	"rowcount",				  	 8	},
	{	"rows",						 4	},
	{	"rule",						 4	},
	{	"save",						 4	},
	{	"schema",				  	 6	},
	{	"select",				  	 6	},
	{	"set",						 3	},
	{	"setuser",				  	 7	},
	{	"shared",				  	 6	},
	{	"shutdown",				  	 8	},
	{	"some",						 4	},
	{	"statistics",			  	10	},
	{	"stripe",				  	 6	},
	{	"sum",						 3	},
	{	"syb_identity",		  	12	},
	{	"syb_restree",			  	11	},
	{	"table",						 5	},
	{	"temp",						 4	},
	{	"temporary",			  	 9	},
	{	"textsize",					 8	},
	{	"to",							 2	},
	{	"tran",						 4	},
	{	"transaction",			  	11	},
	{	"trigger",				  	 7	},
	{	"truncate",				  	 8	},
	{	"tsequal",				  	 7	},
	{	"union",						 5	},
	{	"unique",				  	 6	},
	{	"update",				  	 6	},
	{	"used_pgs",				  	 8	},
	{	"user",						 4	},
	{	"user_option",			  	11	},
	{	"using",						 5	},
	{	"values",				  	 6	},
	{	"varying",					 7	},
	{	"view",						 4	},
	{	"waitfor",					 7	},
	{	"where",						 5	},
	{	"while",						 5	},
	{	"with",						 4	},
	{	"work",						 4	},
	{	"writetext",				 9	},
	{	"tinyint",					 7	},
	{	"smallint",					 8	},
	{	"int",						 3	},
	{	"intn",						 4	},
	{	"numeric",					 7	},
	{	"numericn",					 8	},
	{	"decimal",					 7	},
	{	"decimaln",					 8	},
	{	"float",						 5	},
	{	"floatn",					 6	},
	{	"double precision",		16	},
	{	"real",						 4	},
	{	"smallmoney",				10	},
	{	"money",						 5	},
	{	"moneyn",					 6	},
	{	"smalldatetime",			13	},
	{	"datetimn",					 8	},
	{	"datetime",					 8	},
	{	"char",						 4	},
	{	"varchar",					 7	},
	{	"nchar",						 5	},
	{	"nvarchar",					 8	},
	{	"text",						 4	},
	{	"binary",					 6	},
	{	"varbinary",				 9	},
	{	"image",						 5	},
	{	"bit",						 3	},
	{	"sensitivity",				11	},
	{	"sensitivity_boundary",	20	},
	{	"timestamp",				 9	},
	{	"sysname",					 7	}
};
static const unsigned int Sybase_KeywordCount    =
	sizeof(Sybase_KeywordList) / sizeof(Sybase_KeywordList[0]);
	/*	*****************************************************************	*/
static const int         Sybase_SymbolCaseFlag = KMLFUNCS_TRUE;
	/* This list of structures must be sorted by the first member. */
static const KML_SYMBOL  Sybase_SymbolList[]   = {
	{	"(",		1	},
	{	")",		1	},
	{	":",		1	},
	{	";",		1	},
	{	",",		1	},
	{	".",		1	},
	{	"?",		1	},
};
static const unsigned int Sybase_SymbolCount    =
	sizeof(Sybase_SymbolList) / sizeof(Sybase_SymbolList[0]);
	/*	*****************************************************************	*/
static const int          Sybase_BlockCaseFlag = KMLFUNCS_FALSE;
	/* This list of structures must be sorted by the first member. */
static const KML_BLOCK    Sybase_BlockList[]   = {
	{	"BEGIN",	5,	"END",	3	}
};
static const unsigned int Sybase_BlockCount    =
	sizeof(Sybase_BlockList) / sizeof(Sybase_BlockList[0]);
	/*	*****************************************************************	*/
static const int          Sybase_OperatorCaseFlag = KMLFUNCS_TRUE;
	/* This list of structures must be sorted by the first member. */
static const KML_OPERATOR Sybase_OperatorList[]   = {
	{	"!=",		2,	KML_OP_TYPE_EQUIV										},
	{	"<>",		2,	KML_OP_TYPE_EQUIV										},
	{	"==",		2,	KML_OP_TYPE_EQUIV										},
	{	">=",		2,	KML_OP_TYPE_EQUIV										},
	{	"<=",		2,	KML_OP_TYPE_EQUIV										},
	{	"!>",		2,	KML_OP_TYPE_EQUIV										},
	{	"!<",		2,	KML_OP_TYPE_EQUIV										},
	{	"~",		1,	KML_OP_TYPE_PREFIX	|	KML_OP_TYPE_BITWISE	},
	{	"%",		1,	KML_OP_TYPE_INFIX										},
	{	"&",		1,	KML_OP_TYPE_INFIX		|	KML_OP_TYPE_BITWISE	},
	{	"*",		1,	KML_OP_TYPE_INFIX										},
	{	"+",		1,	KML_OP_TYPE_INFIX										},
	{	"-",		1,	KML_OP_TYPE_INFIX										},
	{	"/",		1,	KML_OP_TYPE_INFIX										},
	{	"<",		1,	KML_OP_TYPE_EQUIV										},
	{	"=",		1,	KML_OP_TYPE_ASSIGN									},
	{	">",		1,	KML_OP_TYPE_EQUIV										},
	{	"^",		1,	KML_OP_TYPE_INFIX		|	KML_OP_TYPE_BITWISE	},
	{	"|",		1,	KML_OP_TYPE_INFIX		|	KML_OP_TYPE_BITWISE	}
};
static const unsigned int Sybase_OperatorCount    = 
	sizeof(Sybase_OperatorList) / sizeof(Sybase_OperatorList[0]);
	/*	*****************************************************************	*/
static const int          Sybase_NameCaseFlag = KMLFUNCS_TRUE;
	/* This list of structures must be sorted by the first member. */
static const KML_NAME     Sybase_NameList[]   = {
	{	"@#_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz",
		"@#$_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"	}
};
static const unsigned int Sybase_NameCount    = 
	sizeof(Sybase_NameList) / sizeof(Sybase_NameList[0]);
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int KML_TEST_InitializeControl(KML_CONTROL *control_ptr, char *error_text)
#else
int KML_TEST_InitializeControl(control_ptr, error_text)
KML_CONTROL *control_ptr;
char        *error_text;
#endif /* #ifndef NARGS */
{
	KML_DOMAIN domain_list[TEST_DOMAIN_COUNT];

	KML_INIT_Control(control_ptr);
	KML_TEST_InitializeDomainList(domain_list);

	return(KML_COPY_DomainList(TEST_DOMAIN_COUNT, domain_list,
		&control_ptr->domain_count, &control_ptr->domain_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int KML_TEST_InitializeDomain(const char *file_type, KML_DOMAIN *domain_ptr,
	char *error_text)
#else
int KML_TEST_InitializeDomain(file_type, domain_ptr, error_text)
const char *file_type;
KML_DOMAIN *domain_ptr;
char       *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = KML_BAD_ARGS_FAILURE;
	unsigned int found_index;
	KML_DOMAIN   domain_list[TEST_DOMAIN_COUNT];

	strcat(nstrcat(strcpy(error_text, "File extension '"),
		file_type, 500), "' not found in the list of test domains.");

	KML_INIT_Domain(domain_ptr);
	KML_TEST_InitializeDomainList(domain_list);

	if (KML_FIND_DomainByType(TEST_DOMAIN_COUNT, domain_list, file_type,
		&found_index) == KML_TRUE)
		return_code = KML_COPY_Domain(domain_list + found_index, domain_ptr,
			error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void KML_TEST_InitializeDomainList(KML_DOMAIN *domain_list)
#else
static void KML_TEST_InitializeDomainList(domain_list)
KML_DOMAIN *domain_list;
#endif /* #ifndef NARGS */
{
	KML_INIT_DomainList(TEST_DOMAIN_COUNT, domain_list);

	domain_list[0].domain_name        = ((char *) C_DomainName);
	domain_list[0].domain_description = ((char *) C_DomainDescrip);
	domain_list[0].type_count         = C_TypeCount;
	domain_list[0].type_list          = ((char **) C_TypeList);
	domain_list[0].string_case_flag   = C_StringCaseFlag;
	domain_list[0].string_count       = C_StringCount;
	domain_list[0].string_list        = ((KML_STRING *) C_StringList);
	domain_list[0].comment_case_flag  = C_CommentCaseFlag;
	domain_list[0].comment_count      = C_CommentCount;
	domain_list[0].comment_list       = ((KML_COMMENT *) C_CommentList);
	domain_list[0].keyword_case_flag  = C_KeywordCaseFlag;
	domain_list[0].keyword_count      = C_KeywordCount;
	domain_list[0].keyword_list       = ((KML_KEYWORD *) C_KeywordList);
	domain_list[0].symbol_case_flag   = C_SymbolCaseFlag;
	domain_list[0].symbol_count       = C_SymbolCount;
	domain_list[0].symbol_list        = ((KML_SYMBOL *) C_SymbolList);
	domain_list[0].block_case_flag    = C_BlockCaseFlag;
	domain_list[0].block_count        = C_BlockCount;
	domain_list[0].block_list         = ((KML_BLOCK *) C_BlockList);
	domain_list[0].operator_case_flag = C_OperatorCaseFlag;
	domain_list[0].operator_count     = C_OperatorCount;
	domain_list[0].operator_list      = ((KML_OPERATOR *) C_OperatorList);
	domain_list[0].name_case_flag     = C_NameCaseFlag;
	domain_list[0].name_count         = C_NameCount;
	domain_list[0].name_list          = ((KML_NAME *) C_NameList);

	domain_list[1].domain_name        = ((char *) Cpp_DomainName);
	domain_list[1].domain_description = ((char *) Cpp_DomainDescrip);
	domain_list[1].type_count         = Cpp_TypeCount;
	domain_list[1].type_list          = ((char **) Cpp_TypeList);
	domain_list[1].string_case_flag   = Cpp_StringCaseFlag;
	domain_list[1].string_count       = Cpp_StringCount;
	domain_list[1].string_list        = ((KML_STRING *) Cpp_StringList);
	domain_list[1].comment_case_flag  = Cpp_CommentCaseFlag;
	domain_list[1].comment_count      = Cpp_CommentCount;
	domain_list[1].comment_list       = ((KML_COMMENT *) Cpp_CommentList);
	domain_list[1].keyword_case_flag  = Cpp_KeywordCaseFlag;
	domain_list[1].keyword_count      = Cpp_KeywordCount;
	domain_list[1].keyword_list       = ((KML_KEYWORD *) Cpp_KeywordList);
	domain_list[1].symbol_case_flag   = Cpp_SymbolCaseFlag;
	domain_list[1].symbol_count       = Cpp_SymbolCount;
	domain_list[1].symbol_list        = ((KML_SYMBOL *) Cpp_SymbolList);
	domain_list[1].block_case_flag    = Cpp_BlockCaseFlag;
	domain_list[1].block_count        = Cpp_BlockCount;
	domain_list[1].block_list         = ((KML_BLOCK *) Cpp_BlockList);
	domain_list[1].operator_case_flag = Cpp_OperatorCaseFlag;
	domain_list[1].operator_count     = Cpp_OperatorCount;
	domain_list[1].operator_list      = ((KML_OPERATOR *) Cpp_OperatorList);
	domain_list[1].name_case_flag     = Cpp_NameCaseFlag;
	domain_list[1].name_count         = Cpp_NameCount;
	domain_list[1].name_list          = ((KML_NAME *) Cpp_NameList);

	domain_list[2].domain_name        = ((char *) Java_DomainName);
	domain_list[2].domain_description = ((char *) Java_DomainDescrip);
	domain_list[2].type_count         = Java_TypeCount;
	domain_list[2].type_list          = ((char **) Java_TypeList);
	domain_list[2].string_case_flag   = Java_StringCaseFlag;
	domain_list[2].string_count       = Java_StringCount;
	domain_list[2].string_list        = ((KML_STRING *) Java_StringList);
	domain_list[2].comment_case_flag  = Java_CommentCaseFlag;
	domain_list[2].comment_count      = Java_CommentCount;
	domain_list[2].comment_list       = ((KML_COMMENT *) Java_CommentList);
	domain_list[2].keyword_case_flag  = Java_KeywordCaseFlag;
	domain_list[2].keyword_count      = Java_KeywordCount;
	domain_list[2].keyword_list       = ((KML_KEYWORD *) Java_KeywordList);
	domain_list[2].symbol_case_flag   = Java_SymbolCaseFlag;
	domain_list[2].symbol_count       = Java_SymbolCount;
	domain_list[2].symbol_list        = ((KML_SYMBOL *) Java_SymbolList);
	domain_list[2].block_case_flag    = Java_BlockCaseFlag;
	domain_list[2].block_count        = Java_BlockCount;
	domain_list[2].block_list         = ((KML_BLOCK *) Java_BlockList);
	domain_list[2].operator_case_flag = Java_OperatorCaseFlag;
	domain_list[2].operator_count     = Java_OperatorCount;
	domain_list[2].operator_list      = ((KML_OPERATOR *) Java_OperatorList);
	domain_list[2].name_case_flag     = Java_NameCaseFlag;
	domain_list[2].name_count         = Java_NameCount;
	domain_list[2].name_list          = ((KML_NAME *) Java_NameList);

	domain_list[3].domain_name        = ((char *) Sybase_DomainName);
	domain_list[3].domain_description = ((char *) Sybase_DomainDescrip);
	domain_list[3].type_count         = Sybase_TypeCount;
	domain_list[3].type_list          = ((char **) Sybase_TypeList);
	domain_list[3].string_case_flag   = Sybase_StringCaseFlag;
	domain_list[3].string_count       = Sybase_StringCount;
	domain_list[3].string_list        = ((KML_STRING *) Sybase_StringList);
	domain_list[3].comment_case_flag  = Sybase_CommentCaseFlag;
	domain_list[3].comment_count      = Sybase_CommentCount;
	domain_list[3].comment_list       = ((KML_COMMENT *) Sybase_CommentList);
	domain_list[3].keyword_case_flag  = Sybase_KeywordCaseFlag;
	domain_list[3].keyword_count      = Sybase_KeywordCount;
	domain_list[3].keyword_list       = ((KML_KEYWORD *) Sybase_KeywordList);
	domain_list[3].symbol_case_flag   = Sybase_SymbolCaseFlag;
	domain_list[3].symbol_count       = Sybase_SymbolCount;
	domain_list[3].symbol_list        = ((KML_SYMBOL *) Sybase_SymbolList);
	domain_list[3].block_case_flag    = Sybase_BlockCaseFlag;
	domain_list[3].block_count        = Sybase_BlockCount;
	domain_list[3].block_list         = ((KML_BLOCK *) Sybase_BlockList);
	domain_list[3].operator_case_flag = Sybase_OperatorCaseFlag;
	domain_list[3].operator_count     = Sybase_OperatorCount;
	domain_list[3].operator_list      = ((KML_OPERATOR *) Sybase_OperatorList);
	domain_list[3].name_case_flag     = Sybase_NameCaseFlag;
	domain_list[3].name_count         = Sybase_NameCount;
	domain_list[3].name_list          = ((KML_NAME *) Sybase_NameList);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int KML_TFREAD_ReadFileBuffer(const char *file_name,
	unsigned int *buffer_length, char **buffer_ptr, char *error_text)
#else
int KML_TFREAD_ReadFileBuffer(file_name, buffer_length, buffer_ptr,
	error_text)
const char     *file_name;
unsigned int   *buffer_length;
char          **buffer_ptr;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code;
	char tfread_error_text[TFREAD_MAX_ERROR_TEXT];

	if ((return_code = TFREAD_ReadBuffer(file_name, buffer_length,
		buffer_ptr, tfread_error_text)) != TFREAD_SUCCESS)
		nstrcpy(error_text, tfread_error_text, KML_MAX_ERROR_TEXT - 1);

	return(KML_MAP_ERROR_TFREAD(return_code));
}
/*	***********************************************************************	*/

