/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Expression Evaluation Calculator Library (EECFUNCS) Include File			*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the EECFUNCS library.

	Revision History	:	1991-11-17 --- Creation.
									Michael L. Brock
								1996-01-29 --- Version 5 initial cut.
									Michael L. Brock

		Copyright Michael L. Brock 1991 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__PARSEDAT_H__h

#define h__PARSEDAT_H__h					1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include "eecfuncs.h"

/*	***********************************************************************	*/

COMPAT_EXTERN_DATA_DECL const EEC_PARSE_CANON_OP	 EEC_OperatorList[];

COMPAT_EXTERN_DATA_DECL const EEC_PARSE_OP_ALIAS    EEC_OperatorAliasList[];
COMPAT_EXTERN_DATA_DECL const unsigned int          EEC_OperatorAliasCount;

COMPAT_EXTERN_DATA_DECL const EEC_EXPR_TYPE_LINKAGE EEC_ExprTypeLinkageList[];
COMPAT_EXTERN_DATA_DECL const unsigned int          EEC_ExprTypeLinkageCount;

COMPAT_EXTERN_DATA_DECL const EEC_FUNC_DEF          EEC_FunctionDefList[];
COMPAT_EXTERN_DATA_DECL const unsigned int          EEC_FunctionDefCount;

/*	***********************************************************************	*/

#endif /* #ifndef h__PARSEDAT_H__h */

