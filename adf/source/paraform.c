/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Attempts to resolve an ADF paragraph format
								specification.

	Revision History	:	1995-04-29 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <stdlib.h>
#include <string.h>

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
static const ADF_PFORMAT_DEF ADF_ParaFormatList[ADF_PFORMAT_COUNT] = {
	{
		"(@)",		ADF_TRUE,	ADF_FALSE,	0,	ADF_PFORMAT_TYPE_NONE,
		ADF_FALSE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"(.)",		ADF_TRUE,	ADF_FALSE,	1,	ADF_PFORMAT_TYPE_BB,
		ADF_FALSE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"(..)",		ADF_TRUE,	ADF_FALSE,	2,	ADF_PFORMAT_TYPE_BB,
		ADF_FALSE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"(...)",		ADF_TRUE,	ADF_FALSE,	3,	ADF_PFORMAT_TYPE_BB,
		ADF_FALSE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"(-)",		ADF_TRUE,	ADF_FALSE,	1,	ADF_PFORMAT_TYPE_IN,
		ADF_FALSE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"(--)",		ADF_TRUE,	ADF_FALSE,	2,	ADF_PFORMAT_TYPE_IN,
		ADF_FALSE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"(---)",		ADF_TRUE,	ADF_FALSE,	3,	ADF_PFORMAT_TYPE_IN,
		ADF_FALSE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"(+)",		ADF_TRUE,	ADF_FALSE,	1,	ADF_PFORMAT_TYPE_NM,
		ADF_FALSE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"(++)",		ADF_TRUE,	ADF_FALSE,	2,	ADF_PFORMAT_TYPE_NM,
		ADF_FALSE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"(+++)",		ADF_TRUE,	ADF_FALSE,	3,	ADF_PFORMAT_TYPE_NM,
		ADF_FALSE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"(|@)",		ADF_TRUE,	ADF_FALSE,	0,	ADF_PFORMAT_TYPE_NONE,
		ADF_TRUE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"(|.)",		ADF_TRUE,	ADF_FALSE,	1,	ADF_PFORMAT_TYPE_BB,
		ADF_TRUE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"(|..)",		ADF_TRUE,	ADF_FALSE,	2,	ADF_PFORMAT_TYPE_BB,
		ADF_TRUE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"(|...)",	ADF_TRUE,	ADF_FALSE,	3,	ADF_PFORMAT_TYPE_BB,
		ADF_TRUE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"(|-)",		ADF_TRUE,	ADF_FALSE,	1,	ADF_PFORMAT_TYPE_IN,
		ADF_TRUE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"(|--)",		ADF_TRUE,	ADF_FALSE,	2,	ADF_PFORMAT_TYPE_IN,
		ADF_TRUE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"(|---)",	ADF_TRUE,	ADF_FALSE,	3,	ADF_PFORMAT_TYPE_IN,
		ADF_TRUE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"(|+)",		ADF_TRUE,	ADF_FALSE,	1,	ADF_PFORMAT_TYPE_NM,
		ADF_TRUE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"(|++)",		ADF_TRUE,	ADF_FALSE,	2,	ADF_PFORMAT_TYPE_NM,
		ADF_TRUE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"(|+++)",	ADF_TRUE,	ADF_FALSE,	3,	ADF_PFORMAT_TYPE_NM,
		ADF_TRUE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"(@|)",		ADF_TRUE,	ADF_FALSE,	0,	ADF_PFORMAT_TYPE_NONE,
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"(.|)",		ADF_TRUE,	ADF_FALSE,	1,	ADF_PFORMAT_TYPE_BB,
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"(..|)",		ADF_TRUE,	ADF_FALSE,	2,	ADF_PFORMAT_TYPE_BB,
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"(...|)",	ADF_TRUE,	ADF_FALSE,	3,	ADF_PFORMAT_TYPE_BB,
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"(-|)",		ADF_TRUE,	ADF_FALSE,	1,	ADF_PFORMAT_TYPE_IN,
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"(--|)",		ADF_TRUE,	ADF_FALSE,	2,	ADF_PFORMAT_TYPE_IN,
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"(---|)",	ADF_TRUE,	ADF_FALSE,	3,	ADF_PFORMAT_TYPE_IN,
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"(+|)",		ADF_TRUE,	ADF_FALSE,	1,	ADF_PFORMAT_TYPE_NM,
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"(++|)",		ADF_TRUE,	ADF_FALSE,	2,	ADF_PFORMAT_TYPE_NM,
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"(+++|)",	ADF_TRUE,	ADF_FALSE,	3,	ADF_PFORMAT_TYPE_NM,
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"(|@|)",		ADF_TRUE,	ADF_FALSE,	0,	ADF_PFORMAT_TYPE_NONE,
		ADF_TRUE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"(|.|)",		ADF_TRUE,	ADF_FALSE,	1,	ADF_PFORMAT_TYPE_BB,
		ADF_TRUE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"(|..|)",	ADF_TRUE,	ADF_FALSE,	2,	ADF_PFORMAT_TYPE_BB,
		ADF_TRUE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"(|...|)",	ADF_TRUE,	ADF_FALSE,	3,	ADF_PFORMAT_TYPE_BB,
		ADF_TRUE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"(|-|)",		ADF_TRUE,	ADF_FALSE,	1,	ADF_PFORMAT_TYPE_IN,
		ADF_TRUE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"(|--|)",	ADF_TRUE,	ADF_FALSE,	2,	ADF_PFORMAT_TYPE_IN,
		ADF_TRUE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"(|---|)",	ADF_TRUE,	ADF_FALSE,	3,	ADF_PFORMAT_TYPE_IN,
		ADF_TRUE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"(|+|)",		ADF_TRUE,	ADF_FALSE,	1,	ADF_PFORMAT_TYPE_NM,
		ADF_TRUE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"(|++|)",	ADF_TRUE,	ADF_FALSE,	2,	ADF_PFORMAT_TYPE_NM,
		ADF_TRUE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"(|+++|)",	ADF_TRUE,	ADF_FALSE,	3,	ADF_PFORMAT_TYPE_NM,
		ADF_TRUE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"[@]",		ADF_FALSE,	ADF_FALSE,	0,	ADF_PFORMAT_TYPE_NONE,
		ADF_FALSE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"[.]",		ADF_FALSE,	ADF_FALSE,	1,	ADF_PFORMAT_TYPE_BB,
		ADF_FALSE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"[..]",		ADF_FALSE,	ADF_FALSE,	2,	ADF_PFORMAT_TYPE_BB,
		ADF_FALSE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"[...]",		ADF_FALSE,	ADF_FALSE,	3,	ADF_PFORMAT_TYPE_BB,
		ADF_FALSE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"[-]",		ADF_FALSE,	ADF_FALSE,	1,	ADF_PFORMAT_TYPE_IN,
		ADF_FALSE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"[--]",		ADF_FALSE,	ADF_FALSE,	2,	ADF_PFORMAT_TYPE_IN,
		ADF_FALSE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"[---]",		ADF_FALSE,	ADF_FALSE,	3,	ADF_PFORMAT_TYPE_IN,
		ADF_FALSE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"[+]",		ADF_FALSE,	ADF_FALSE,	1,	ADF_PFORMAT_TYPE_NM,
		ADF_FALSE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"[++]",		ADF_FALSE,	ADF_FALSE,	2,	ADF_PFORMAT_TYPE_NM,
		ADF_FALSE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"[+++]",		ADF_FALSE,	ADF_FALSE,	3,	ADF_PFORMAT_TYPE_NM,
		ADF_FALSE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"[|@]",		ADF_FALSE,	ADF_FALSE,	0,	ADF_PFORMAT_TYPE_NONE,
		ADF_TRUE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"[|.]",		ADF_FALSE,	ADF_FALSE,	1,	ADF_PFORMAT_TYPE_BB,
		ADF_TRUE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"[|..]",		ADF_FALSE,	ADF_FALSE,	2,	ADF_PFORMAT_TYPE_BB,
		ADF_TRUE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"[|...]",	ADF_FALSE,	ADF_FALSE,	3,	ADF_PFORMAT_TYPE_BB,
		ADF_TRUE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"[|-]",		ADF_FALSE,	ADF_FALSE,	1,	ADF_PFORMAT_TYPE_IN,
		ADF_TRUE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"[|--]",		ADF_FALSE,	ADF_FALSE,	2,	ADF_PFORMAT_TYPE_IN,
		ADF_TRUE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"[|---]",	ADF_FALSE,	ADF_FALSE,	3,	ADF_PFORMAT_TYPE_IN,
		ADF_TRUE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"[|+]",		ADF_FALSE,	ADF_FALSE,	1,	ADF_PFORMAT_TYPE_NM,
		ADF_TRUE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"[|++]",		ADF_FALSE,	ADF_FALSE,	2,	ADF_PFORMAT_TYPE_NM,
		ADF_TRUE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"[|+++]",	ADF_FALSE,	ADF_FALSE,	3,	ADF_PFORMAT_TYPE_NM,
		ADF_TRUE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"[@|]",		ADF_FALSE,	ADF_FALSE,	0,	ADF_PFORMAT_TYPE_NONE,
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"[.|]",		ADF_FALSE,	ADF_FALSE,	1,	ADF_PFORMAT_TYPE_BB,
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"[..|]",		ADF_FALSE,	ADF_FALSE,	2,	ADF_PFORMAT_TYPE_BB,
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"[...|]",	ADF_FALSE,	ADF_FALSE,	3,	ADF_PFORMAT_TYPE_BB,
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"[-|]",		ADF_FALSE,	ADF_FALSE,	1,	ADF_PFORMAT_TYPE_IN,
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"[--|]",		ADF_FALSE,	ADF_FALSE,	2,	ADF_PFORMAT_TYPE_IN,
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"[---|]",	ADF_FALSE,	ADF_FALSE,	3,	ADF_PFORMAT_TYPE_IN,
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"[+|]",		ADF_FALSE,	ADF_FALSE,	1,	ADF_PFORMAT_TYPE_NM,
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"[++|]",		ADF_FALSE,	ADF_FALSE,	2,	ADF_PFORMAT_TYPE_NM,
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"[+++|]",	ADF_FALSE,	ADF_FALSE,	3,	ADF_PFORMAT_TYPE_NM,
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"[|@|]",		ADF_FALSE,	ADF_FALSE,	0,	ADF_PFORMAT_TYPE_NONE,
		ADF_TRUE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"[|.|]",		ADF_FALSE,	ADF_FALSE,	1,	ADF_PFORMAT_TYPE_BB,
		ADF_TRUE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"[|..|]",	ADF_FALSE,	ADF_FALSE,	2,	ADF_PFORMAT_TYPE_BB,
		ADF_TRUE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"[|...|]",	ADF_FALSE,	ADF_FALSE,	3,	ADF_PFORMAT_TYPE_BB,
		ADF_TRUE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"[|-|]",		ADF_FALSE,	ADF_FALSE,	1,	ADF_PFORMAT_TYPE_IN,
		ADF_TRUE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"[|--|]",	ADF_FALSE,	ADF_FALSE,	2,	ADF_PFORMAT_TYPE_IN,
		ADF_TRUE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"[|---|]",	ADF_FALSE,	ADF_FALSE,	3,	ADF_PFORMAT_TYPE_IN,
		ADF_TRUE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"[|+|]",		ADF_FALSE,	ADF_FALSE,	1,	ADF_PFORMAT_TYPE_NM,
		ADF_TRUE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"[|++|]",	ADF_FALSE,	ADF_FALSE,	2,	ADF_PFORMAT_TYPE_NM,
		ADF_TRUE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"[|+++|]",	ADF_FALSE,	ADF_FALSE,	3,	ADF_PFORMAT_TYPE_NM,
		ADF_TRUE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"<@>",		ADF_TRUE,	ADF_TRUE,	0,	ADF_PFORMAT_TYPE_NONE,
		ADF_FALSE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"<.>",		ADF_TRUE,	ADF_TRUE,	1,	ADF_PFORMAT_TYPE_BB,
		ADF_FALSE,	ADF_FALSE,	ADF_FALSE
	},
	{
		"<..>",		ADF_TRUE,	ADF_TRUE,	2,	ADF_PFORMAT_TYPE_BB,
		ADF_FALSE,	ADF_FALSE,	ADF_FALSE
	},
	{
		"<...>",		ADF_TRUE,	ADF_TRUE,	3,	ADF_PFORMAT_TYPE_BB,
		ADF_FALSE,	ADF_FALSE,	ADF_FALSE
	},
	{
		"<->",		ADF_TRUE,	ADF_TRUE,	1,	ADF_PFORMAT_TYPE_IN,
		ADF_FALSE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"<-->",		ADF_TRUE,	ADF_TRUE,	2,	ADF_PFORMAT_TYPE_IN,
		ADF_FALSE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"<--->",		ADF_TRUE,	ADF_TRUE,	3,	ADF_PFORMAT_TYPE_IN,
		ADF_FALSE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"<+>",		ADF_TRUE,	ADF_TRUE,	1,	ADF_PFORMAT_TYPE_NM,
		ADF_FALSE,	ADF_FALSE,	ADF_FALSE
	},
	{
		"<++>",		ADF_TRUE,	ADF_TRUE,	2,	ADF_PFORMAT_TYPE_NM,
		ADF_FALSE,	ADF_FALSE,	ADF_FALSE
	},
	{
		"<+++>",		ADF_TRUE,	ADF_TRUE,	3,	ADF_PFORMAT_TYPE_NM,
		ADF_FALSE,	ADF_FALSE,	ADF_FALSE
	},
	{
		"<|@>",		ADF_TRUE,	ADF_TRUE,	0,	ADF_PFORMAT_TYPE_NONE,
		ADF_TRUE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"<|.>",		ADF_TRUE,	ADF_TRUE,	1,	ADF_PFORMAT_TYPE_BB,
		ADF_TRUE,	ADF_FALSE,	ADF_FALSE
	},
	{
		"<|..>",		ADF_TRUE,	ADF_TRUE,	2,	ADF_PFORMAT_TYPE_BB,
		ADF_TRUE,	ADF_FALSE,	ADF_FALSE
	},
	{
		"<|...>",	ADF_TRUE,	ADF_TRUE,	3,	ADF_PFORMAT_TYPE_BB,
		ADF_TRUE,	ADF_FALSE,	ADF_FALSE
	},
	{
		"<|->",		ADF_TRUE,	ADF_TRUE,	1,	ADF_PFORMAT_TYPE_IN,
		ADF_TRUE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"<|-->",		ADF_TRUE,	ADF_TRUE,	2,	ADF_PFORMAT_TYPE_IN,
		ADF_TRUE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"<|--->",	ADF_TRUE,	ADF_TRUE,	3,	ADF_PFORMAT_TYPE_IN,
		ADF_TRUE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"<|+>",		ADF_TRUE,	ADF_TRUE,	1,	ADF_PFORMAT_TYPE_NM,
		ADF_TRUE,	ADF_FALSE,	ADF_FALSE
	},
	{
		"<|++>",		ADF_TRUE,	ADF_TRUE,	2,	ADF_PFORMAT_TYPE_NM,
		ADF_TRUE,	ADF_FALSE,	ADF_FALSE
	},
	{
		"<|+++>",	ADF_TRUE,	ADF_TRUE,	3,	ADF_PFORMAT_TYPE_NM,
		ADF_TRUE,	ADF_FALSE,	ADF_FALSE
	},
	{
		"<@|>",		ADF_TRUE,	ADF_TRUE,	0,	ADF_PFORMAT_TYPE_NONE,
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"<.|>",		ADF_TRUE,	ADF_TRUE,	1,	ADF_PFORMAT_TYPE_BB,
		ADF_FALSE,	ADF_TRUE,	ADF_FALSE
	},
	{
		"<..|>",		ADF_TRUE,	ADF_TRUE,	2,	ADF_PFORMAT_TYPE_BB,
		ADF_FALSE,	ADF_TRUE,	ADF_FALSE
	},
	{
		"<...|>",	ADF_TRUE,	ADF_TRUE,	3,	ADF_PFORMAT_TYPE_BB,
		ADF_FALSE,	ADF_TRUE,	ADF_FALSE
	},
	{
		"<-|>",		ADF_TRUE,	ADF_TRUE,	1,	ADF_PFORMAT_TYPE_IN,
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"<--|>",		ADF_TRUE,	ADF_TRUE,	2,	ADF_PFORMAT_TYPE_IN,
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"<---|>",	ADF_TRUE,	ADF_TRUE,	3,	ADF_PFORMAT_TYPE_IN,
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"<+|>",		ADF_TRUE,	ADF_TRUE,	1,	ADF_PFORMAT_TYPE_NM,
		ADF_FALSE,	ADF_TRUE,	ADF_FALSE
	},
	{
		"<++|>",		ADF_TRUE,	ADF_TRUE,	2,	ADF_PFORMAT_TYPE_NM,
		ADF_FALSE,	ADF_TRUE,	ADF_FALSE
	},
	{
		"<+++|>",	ADF_TRUE,	ADF_TRUE,	3,	ADF_PFORMAT_TYPE_NM,
		ADF_FALSE,	ADF_TRUE,	ADF_FALSE
	},
	{
		"<|@|>",		ADF_TRUE,	ADF_TRUE,	0,	ADF_PFORMAT_TYPE_NONE,
		ADF_TRUE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"<|.|>",		ADF_TRUE,	ADF_TRUE,	1,	ADF_PFORMAT_TYPE_BB,
		ADF_TRUE,	ADF_TRUE,	ADF_FALSE
	},
	{
		"<|..|>",	ADF_TRUE,	ADF_TRUE,	2,	ADF_PFORMAT_TYPE_BB,
		ADF_TRUE,	ADF_TRUE,	ADF_FALSE
	},
	{
		"<|...|>",	ADF_TRUE,	ADF_TRUE,	3,	ADF_PFORMAT_TYPE_BB,
		ADF_TRUE,	ADF_TRUE,	ADF_FALSE
	},
	{
		"<|-|>",		ADF_TRUE,	ADF_TRUE,	1,	ADF_PFORMAT_TYPE_IN,
		ADF_TRUE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"<|--|>",	ADF_TRUE,	ADF_TRUE,	2,	ADF_PFORMAT_TYPE_IN,
		ADF_TRUE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"<|---|>",	ADF_TRUE,	ADF_TRUE,	3,	ADF_PFORMAT_TYPE_IN,
		ADF_TRUE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"<|+|>",		ADF_TRUE,	ADF_TRUE,	1,	ADF_PFORMAT_TYPE_NM,
		ADF_TRUE,	ADF_TRUE,	ADF_FALSE
	},
	{
		"<|++|>",	ADF_TRUE,	ADF_TRUE,	2,	ADF_PFORMAT_TYPE_NM,
		ADF_TRUE,	ADF_TRUE,	ADF_FALSE
	},
	{
		"<|+++|>",	ADF_TRUE,	ADF_TRUE,	3,	ADF_PFORMAT_TYPE_NM,
		ADF_TRUE,	ADF_TRUE,	ADF_FALSE
	},
	{
		"{@}",		ADF_FALSE,	ADF_TRUE,	0,	ADF_PFORMAT_TYPE_NONE,
		ADF_FALSE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"{.}",		ADF_FALSE,	ADF_TRUE,	1,	ADF_PFORMAT_TYPE_BB,
		ADF_FALSE,	ADF_FALSE,	ADF_FALSE
	},
	{
		"{..}",		ADF_FALSE,	ADF_TRUE,	2,	ADF_PFORMAT_TYPE_BB,
		ADF_FALSE,	ADF_FALSE,	ADF_FALSE
	},
	{
		"{...}",		ADF_FALSE,	ADF_TRUE,	3,	ADF_PFORMAT_TYPE_BB,
		ADF_FALSE,	ADF_FALSE,	ADF_FALSE
	},
	{
		"{-}",		ADF_FALSE,	ADF_TRUE,	1,	ADF_PFORMAT_TYPE_IN,
		ADF_FALSE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"{--}",		ADF_FALSE,	ADF_TRUE,	2,	ADF_PFORMAT_TYPE_IN,
		ADF_FALSE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"{---}",		ADF_FALSE,	ADF_TRUE,	3,	ADF_PFORMAT_TYPE_IN,
		ADF_FALSE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"{+}",		ADF_FALSE,	ADF_TRUE,	1,	ADF_PFORMAT_TYPE_NM,
		ADF_FALSE,	ADF_FALSE,	ADF_FALSE
	},
	{
		"{++}",		ADF_FALSE,	ADF_TRUE,	2,	ADF_PFORMAT_TYPE_NM,
		ADF_FALSE,	ADF_FALSE,	ADF_FALSE
	},
	{
		"{+++}",		ADF_FALSE,	ADF_TRUE,	3,	ADF_PFORMAT_TYPE_NM,
		ADF_FALSE,	ADF_FALSE,	ADF_FALSE
	},
	{
		"{|@}",		ADF_FALSE,	ADF_TRUE,	0,	ADF_PFORMAT_TYPE_NONE,
		ADF_TRUE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"{|.}",		ADF_FALSE,	ADF_TRUE,	1,	ADF_PFORMAT_TYPE_BB,
		ADF_TRUE,	ADF_FALSE,	ADF_FALSE
	},
	{
		"{|..}",		ADF_FALSE,	ADF_TRUE,	2,	ADF_PFORMAT_TYPE_BB,
		ADF_TRUE,	ADF_FALSE,	ADF_FALSE
	},
	{
		"{|...}",	ADF_FALSE,	ADF_TRUE,	3,	ADF_PFORMAT_TYPE_BB,
		ADF_TRUE,	ADF_FALSE,	ADF_FALSE
	},
	{
		"{|-}",		ADF_FALSE,	ADF_TRUE,	1,	ADF_PFORMAT_TYPE_IN,
		ADF_TRUE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"{|--}",		ADF_FALSE,	ADF_TRUE,	2,	ADF_PFORMAT_TYPE_IN,
		ADF_TRUE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"{|---}",	ADF_FALSE,	ADF_TRUE,	3,	ADF_PFORMAT_TYPE_IN,
		ADF_TRUE,	ADF_FALSE,	ADF_TRUE
	},
	{
		"{|+}",		ADF_FALSE,	ADF_TRUE,	1,	ADF_PFORMAT_TYPE_NM,
		ADF_TRUE,	ADF_FALSE,	ADF_FALSE
	},
	{
		"{|++}",		ADF_FALSE,	ADF_TRUE,	2,	ADF_PFORMAT_TYPE_NM,
		ADF_TRUE,	ADF_FALSE,	ADF_FALSE
	},
	{
		"{|+++}",	ADF_FALSE,	ADF_TRUE,	3,	ADF_PFORMAT_TYPE_NM,
		ADF_TRUE,	ADF_FALSE,	ADF_FALSE
	},
	{
		"{@|}",		ADF_FALSE,	ADF_TRUE,	0,	ADF_PFORMAT_TYPE_NONE,
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"{.|}",		ADF_FALSE,	ADF_TRUE,	1,	ADF_PFORMAT_TYPE_BB,
		ADF_FALSE,	ADF_TRUE,	ADF_FALSE
	},
	{
		"{..|}",		ADF_FALSE,	ADF_TRUE,	2,	ADF_PFORMAT_TYPE_BB,
		ADF_FALSE,	ADF_TRUE,	ADF_FALSE
	},
	{
		"{...|}",	ADF_FALSE,	ADF_TRUE,	3,	ADF_PFORMAT_TYPE_BB,
		ADF_FALSE,	ADF_TRUE,	ADF_FALSE
	},
	{
		"{-|}",		ADF_FALSE,	ADF_TRUE,	1,	ADF_PFORMAT_TYPE_IN,
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"{--|}",		ADF_FALSE,	ADF_TRUE,	2,	ADF_PFORMAT_TYPE_IN,
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"{---|}",	ADF_FALSE,	ADF_TRUE,	3,	ADF_PFORMAT_TYPE_IN,
		ADF_FALSE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"{+|}",		ADF_FALSE,	ADF_TRUE,	1,	ADF_PFORMAT_TYPE_NM,
		ADF_FALSE,	ADF_TRUE,	ADF_FALSE
	},
	{
		"{++|}",		ADF_FALSE,	ADF_TRUE,	2,	ADF_PFORMAT_TYPE_NM,
		ADF_FALSE,	ADF_TRUE,	ADF_FALSE
	},
	{
		"{+++|}",	ADF_FALSE,	ADF_TRUE,	3,	ADF_PFORMAT_TYPE_NM,
		ADF_FALSE,	ADF_TRUE,	ADF_FALSE
	},
	{
		"{|@|}",		ADF_FALSE,	ADF_TRUE,	0,	ADF_PFORMAT_TYPE_NONE,
		ADF_TRUE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"{|.|}",		ADF_FALSE,	ADF_TRUE,	1,	ADF_PFORMAT_TYPE_BB,
		ADF_TRUE,	ADF_TRUE,	ADF_FALSE
	},
	{
		"{|..|}",	ADF_FALSE,	ADF_TRUE,	2,	ADF_PFORMAT_TYPE_BB,
		ADF_TRUE,	ADF_TRUE,	ADF_FALSE
	},
	{
		"{|...|}",	ADF_FALSE,	ADF_TRUE,	3,	ADF_PFORMAT_TYPE_BB,
		ADF_TRUE,	ADF_TRUE,	ADF_FALSE
	},
	{
		"{|-|}",		ADF_FALSE,	ADF_TRUE,	1,	ADF_PFORMAT_TYPE_IN,
		ADF_TRUE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"{|--|}",	ADF_FALSE,	ADF_TRUE,	2,	ADF_PFORMAT_TYPE_IN,
		ADF_TRUE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"{|---|}",	ADF_FALSE,	ADF_TRUE,	3,	ADF_PFORMAT_TYPE_IN,
		ADF_TRUE,	ADF_TRUE,	ADF_TRUE
	},
	{
		"{|+|}",		ADF_FALSE,	ADF_TRUE,	1,	ADF_PFORMAT_TYPE_NM,
		ADF_TRUE,	ADF_TRUE,	ADF_FALSE
	},
	{
		"{|++|}",	ADF_FALSE,	ADF_TRUE,	2,	ADF_PFORMAT_TYPE_NM,
		ADF_TRUE,	ADF_TRUE,	ADF_FALSE
	},
	{
		"{|+++|}",	ADF_FALSE,	ADF_TRUE,	3,	ADF_PFORMAT_TYPE_NM,
		ADF_TRUE,	ADF_TRUE,	ADF_FALSE
	}
};
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
typedef struct {
	char                   pformat_char;
	unsigned int           pformat_index;
	unsigned int           pformat_count;
	const ADF_PFORMAT_DEF *pformat_list;
} ADF_PFORMAT_DEF_INDEX;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static int ADF_ParaFormatListIndexDoneFlag = ADF_FALSE;
static ADF_PFORMAT_DEF_INDEX ADF_ParaFormatIndex
										[ADF_PFORMAT_BRACE_TYPE_COUNT];
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#ifdef TEST_MAIN
COMPAT_FN_DECL_STATIC(const ADF_PFORMAT_DEF *OLD_ADF_MatchParaFormat,
	(const char *in_string, char *para_format_ptr,
	unsigned int *para_format_index, unsigned int *pattern_end_index));
#endif /* #ifdef TEST_MAIN */
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#ifndef NARGS
const ADF_PFORMAT_DEF *ADF_MatchParaFormat(const char *in_string,
	char *para_format_ptr, unsigned int *para_format_index,
	unsigned int *pattern_end_index)
#else
const ADF_PFORMAT_DEF *ADF_MatchParaFormat(in_string, para_format_ptr,
	para_format_index, pattern_end_index)
const char   *in_string;
char         *para_format_ptr;
unsigned int *para_format_index;
unsigned int *pattern_end_index;
#endif /* #ifndef NARGS */
{
	const ADF_PFORMAT_DEF *return_ptr  = NULL;
	unsigned int           added_chars = 0;
	const ADF_PFORMAT_DEF *pformat_ptr;
	unsigned int           count_1;
	unsigned int           count_2;
	unsigned int           count_3;
	ADF_PFORMAT_DEF_INDEX *pformat_index_ptr;

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Create the index of paragraph formats if it doesn't already		*/
	/*	exist . . .																			*/
	/*	*****************************************************************	*/
	if (ADF_ParaFormatListIndexDoneFlag != ADF_TRUE) {
		pformat_index_ptr                = ADF_ParaFormatIndex;
		pformat_index_ptr->pformat_char  = *ADF_ParaFormatList->format_string;
		pformat_index_ptr->pformat_index = 0;
		pformat_index_ptr->pformat_count = 1;
		pformat_index_ptr->pformat_list  = ADF_ParaFormatList;
		for (count_1 = 0; count_1 < ADF_PFORMAT_COUNT; count_1++) {
			if (pformat_index_ptr->pformat_char !=
				*ADF_ParaFormatList[count_1].format_string) {
				pformat_index_ptr++;
				pformat_index_ptr->pformat_char  =
					*ADF_ParaFormatList[count_1].format_string;
				pformat_index_ptr->pformat_index = count_1;
				pformat_index_ptr->pformat_count = 1;
				pformat_index_ptr->pformat_list  = ADF_ParaFormatList + count_1;
			}
			else
				pformat_index_ptr->pformat_count++;
		}
		ADF_ParaFormatListIndexDoneFlag = ADF_TRUE;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Eat any initial white-space in the line to be examined . . .	*/
	/*	*****************************************************************	*/
	while (isspace(*in_string)) {
		in_string++;
		added_chars++;
	}
	/*	*****************************************************************	*/

	if (*in_string) {
		for (count_1 = 0; count_1 < ADF_PFORMAT_BRACE_TYPE_COUNT; count_1++) {
			if (*in_string == ADF_ParaFormatIndex[count_1].pformat_char) {
				pformat_ptr = ADF_ParaFormatIndex[count_1].pformat_list;
				for (count_2 = 0; count_2 <
					ADF_ParaFormatIndex[count_1].pformat_count; count_2++) {
					for (count_3 = 1;
						pformat_ptr->format_string[count_3] && in_string[count_3] &&
						(pformat_ptr->format_string[count_3] == in_string[count_3]);
						count_3++)
						;
					if (!pformat_ptr->format_string[count_3]) {
						if (pformat_ptr->supported_flag == ADF_TRUE) {
							ADF_MakeFormatString(ADF_ParaFormatIndex[count_1].
								pformat_index + count_2, para_format_ptr);
							if (pattern_end_index != NULL)
								*pattern_end_index =
									strlen(pformat_ptr->format_string) + added_chars;
							if (para_format_index != NULL)
								*para_format_index = ADF_ParaFormatIndex[count_1].
									pformat_index + count_2;
							return_ptr = ADF_ParaFormatList +
								ADF_ParaFormatIndex[count_1].pformat_index + count_2;
						}
						goto EXIT_FUNCTION;
					}
					pformat_ptr++;
				}
			}
		}
	}

EXIT_FUNCTION:

	return(return_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
const ADF_PFORMAT_DEF *ADF_GetParaFormat(unsigned int para_format_index)
#else
const ADF_PFORMAT_DEF *ADF_GetParaFormat(para_format_index)
unsigned int para_format_index;
#endif /* #ifndef NARGS */
{
	return((para_format_index <= ADF_PFORMAT_COUNT) ?
		(ADF_ParaFormatList + para_format_index) : NULL);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *ADF_MakeFormatString(unsigned int pformat_index, char *pformat_string)
#else
char *ADF_MakeFormatString(pformat_index, pformat_string)
unsigned int  pformat_index;
char         *pformat_string;
#endif /* #ifndef NARGS */
{
	*pformat_string = '\0';

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	Pack a paragraph format specifier into ADF database format.			*/
	/*	*****************************************************************	*/
	if (pformat_index < ADF_PFORMAT_COUNT)
		sprintf(pformat_string, "%c|%3.3u|%d|%d|%1.1u|%d|%d|%d|",
			ADF_PFORMAT_MARKER_CHAR,
			pformat_index,
			ADF_ParaFormatList[pformat_index].char_format_flag,
			ADF_ParaFormatList[pformat_index].small_font_flag,
			ADF_ParaFormatList[pformat_index].indent_level,
			ADF_ParaFormatList[pformat_index].format_type,
			ADF_ParaFormatList[pformat_index].begin_rule_flag,
			ADF_ParaFormatList[pformat_index].end_rule_flag);
	/*	*****************************************************************	*/

	return(pformat_string);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN
/*	***********************************************************************	*/
#ifndef NARGS
static const ADF_PFORMAT_DEF *OLD_ADF_MatchParaFormat(const char *in_string,
	char *para_format_ptr, unsigned int *para_format_index,
	unsigned int *pattern_end_index)
#else
static const ADF_PFORMAT_DEF *OLD_ADF_MatchParaFormat(in_string,
	para_format_ptr, para_format_index, pattern_end_index)
const char   *in_string;
char         *para_format_ptr;
unsigned int *para_format_index;
unsigned int *pattern_end_index;
#endif /* #ifndef NARGS */
{
	const ADF_PFORMAT_DEF *return_ptr  = NULL;
	unsigned int           added_chars = 0;
	unsigned int           count_1;

	while (isspace(*in_string)) {
		in_string++;
		added_chars++;
	}

	for (count_1 = 0; count_1 < ADF_PFORMAT_COUNT; count_1++) {
		if (ADF_MatchPattern(in_string,
			ADF_ParaFormatList[count_1].format_string, pattern_end_index) ==
			ADF_TRUE) {
			if (ADF_ParaFormatList[count_1].supported_flag == ADF_TRUE) {
				ADF_MakeFormatString(count_1, para_format_ptr);
				if (pattern_end_index != NULL)
					*pattern_end_index += added_chars;
				if (para_format_index != NULL)
					*para_format_index = count_1;
				return_ptr = ADF_ParaFormatList + count_1;
			}
			break;
		}
	}

	return(return_ptr);
}
/*	***********************************************************************	*/
#endif /* #ifdef TEST_MAIN */

#ifdef TEST_MAIN

COMPAT_FN_DECL(int main, (int argc, char **argv));

COMPAT_FN_DECL_STATIC(double TEST_RunSpeedTest,
	(unsigned int line_count, char **line_list,
	const ADF_PFORMAT_DEF *(*match_function)(const char *, char *,
	unsigned int *, unsigned int *)));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int                     return_code    = ADF_SUCCESS;
	int                     compare_test   = ADF_FALSE;
	unsigned int            line_count     = 0;
	char                  **line_list      = NULL;
	char                   *line_buffer    = NULL;
	unsigned long           total_files    = 0L;
	unsigned long           total_lines    = 0L;
	double                  total_time_1   = 0.0;
	double                  total_time_2   = 0.0;
	unsigned int            count_1;
	unsigned int            count_2;
	char                    para_format_buff_1[ADF_PFORMAT_LENGTH + 1];
	char                    para_format_buff_2[ADF_PFORMAT_LENGTH + 1];
	const ADF_PFORMAT_DEF  *para_format_def_ptr_1;
	const ADF_PFORMAT_DEF  *para_format_def_ptr_2;
	unsigned int            para_format_index_1;
	unsigned int            para_format_index_2;
	unsigned int            para_format_end_1;
	unsigned int            para_format_end_2;
   char                    error_text[ADF_MAX_ERROR_TEXT];

	fprintf(stderr, "Test of new versus old 'ADF_MatchParaFormat()'\n");
	fprintf(stderr, "---- -- --- ------ --- -----------------------\n\n");

	for (count_1 = 1; count_1 < argc; count_1++) {
		if ((!stricmp("-H", argv[count_1])) ||
			(!stricmp("-HELP", argv[count_1]))) {
			fprintf(stderr,
				"USAGE:\n   %s [-COMPARE] <file-name> [<file-name>...]\n",
				argv[0]);
			goto EXIT_FUNCTION;
		}
	}

	if (argc < 2) {
		sprintf(error_text, "Invalid command line encountered.");
		fprintf(stderr,
			"USAGE:\n   %s [-COMPARE] <file-name> [<file-name>...]\n", argv[0]);
		return_code = ADF_BAD_ARGS_FAILURE;
	}
	else {
		for (count_1 = 1; count_1 < argc; count_1++) {
			if (!stricmp("-COMPARE", argv[count_1])) {
				compare_test = ADF_TRUE;
				continue;
			}
			fprintf(stderr, "Reading file '%s' . . .", argv[count_1]);
			if ((return_code = ADF_ReadSourceFile(argv[count_1], &line_count,
				&line_list, &line_buffer, error_text)) != ADF_SUCCESS)
				goto EXIT_FUNCTION;
			fprintf(stderr, "\n");
			total_files++;
			total_lines += line_count;
			if (compare_test == ADF_TRUE) {
				fprintf(stderr, "Comparing %u lines . . .", line_count);
				for (count_2 = 0; count_2 < line_count; count_2++) {
					*para_format_buff_1   = '\0';
					*para_format_buff_2   = '\0';
					para_format_index_1   = 0;
					para_format_index_2   = 0;
					para_format_end_1     = 0;
					para_format_end_2     = 0;
					para_format_def_ptr_1 =
						OLD_ADF_MatchParaFormat(line_list[count_2],
						para_format_buff_1, &para_format_index_1,
						&para_format_end_1);
					para_format_def_ptr_2 =
						ADF_MatchParaFormat(line_list[count_2],
						para_format_buff_2, &para_format_index_2,
						&para_format_end_2);
					if (para_format_def_ptr_1 != para_format_def_ptr_2) {
						fprintf(stdout, "Line number %u difference: ", count_2 + 1);
						fprintf(stdout,
							"paragraph format definition pointer: %p != %p.\n",
							para_format_def_ptr_1, para_format_def_ptr_2);
						return_code = ADF_FAILURE;
					}
					if (strcmp(para_format_buff_1, para_format_buff_2)) {
						fprintf(stdout, "Line number %u difference: ", count_2 + 1);
						fprintf(stdout,
							"paragraph format ADF database string: [%s] != [%s].\n",
							para_format_buff_1, para_format_buff_2);
						return_code = ADF_FAILURE;
					}
					if (para_format_index_1 != para_format_index_2) {
						fprintf(stdout, "Line number %u difference: ", count_2 + 1);
						fprintf(stdout,
							"paragraph format index: %u != %u.\n",
							para_format_index_1, para_format_index_2);
						return_code = ADF_FAILURE;
					}
					if (para_format_end_1 != para_format_end_2) {
						fprintf(stdout, "Line number %u difference: ", count_2 + 1);
						fprintf(stdout,
							"paragraph format end index: %u != %u.\n",
							para_format_end_1, para_format_end_2);
						return_code = ADF_FAILURE;
					}
					if (return_code != ADF_SUCCESS) {
						fprintf(stderr, "Line Data:[%s]\n", line_list[count_2]);
						sprintf(error_text,
							"Differences encounted at line number %u.", count_2 + 1);
						goto EXIT_FUNCTION;
					}
				}
				fprintf(stderr, "\n");
			}
			fprintf(stderr, "Speed test .");
			total_time_1 += TEST_RunSpeedTest(line_count, line_list,
				OLD_ADF_MatchParaFormat);
			fprintf(stderr, " .");
			total_time_2 += TEST_RunSpeedTest(line_count, line_list,
				ADF_MatchParaFormat);
			fprintf(stderr, " .");
			fprintf(stderr, "\n");
			if (line_list != NULL) {
				free(line_list);
				line_list = NULL;
			}
			if (line_buffer != NULL) {
				ADF_BIG_free(line_buffer);
				line_buffer = NULL;
			}
		}
	}

	fprintf(stderr, "\n\nTests concluded successfully\n");
	fprintf(stderr, "----- --------- ------------\n");
	fprintf(stderr, "Total files           : %lu\n", total_files);
	fprintf(stderr, "Total lines           : %lu\n", total_lines);
	fprintf(stderr, "Old version total time: %10.6f seconds.\n",
		total_time_1 / 1000000.0);
	fprintf(stderr, "New version total time: %10.6f seconds.\n",
		total_time_2 / 1000000.0);
	fprintf(stderr, "\n");

EXIT_FUNCTION:

	if (line_list != NULL)
		free(line_list);
	if (line_buffer != NULL)
		ADF_BIG_free(line_buffer);

	if (return_code != ADF_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#ifndef NARGS
static double TEST_RunSpeedTest(unsigned int line_count, char **line_list,
	const ADF_PFORMAT_DEF *(*match_function)(const char *, char *,
		unsigned int *, unsigned int *))
#else
static double TEST_RunSpeedTest(line_count, line_list, match_function)
unsigned int             line_count;
char                   **line_list;
const ADF_PFORMAT_DEF *(*match_function)();
#endif /* #ifndef NARGS */
{
	unsigned int   count_1;
	char           para_format_buff[ADF_PFORMAT_LENGTH + 1];
	unsigned int   para_format_index;
	unsigned int   para_format_end;
	struct timeval start_time;
	struct timeval end_time;

	SDTIF_GetTimeUSecs(&start_time);

	for (count_1 = 0; count_1 < line_count; count_1++)
		(*match_function)(line_list[count_1], para_format_buff,
			&para_format_index, &para_format_end);

	SDTIF_GetTimeUSecs_GetTimeUSecs(&end_time);

	return(SDTIF_GET_TIMEVAL_USECS_DOUBLE(&end_time) -
		SDTIF_GET_TIMEVAL_USECS_DOUBLE(&start_time));
}

#endif /* #ifdef TEST_MAIN */

