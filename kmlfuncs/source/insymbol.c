/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes 'KML_SYMBOL' structures.

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

#include <memory.h>

#include "kmlfunci.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	KML_INIT_Symbol

	SYNOPSIS		:	void KML_INIT_Symbol(ptr);

						KML_SYMBOL *ptr;

	DESCRIPTION	:	Initializes the members of a ''KML_SYMBOL''
						structure to their default values.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``ptr`` points to the ''KML_SYMBOL''
						structure to be initialized by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_INIT_SymbolList
						KML_CMP_Symbol
						KML_COPY_Symbol
						KML_FREE_Symbol
						KML_SCMP_Symbol

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2018 Michael L. Brock

	OUTPUT INDEX:	KML_INIT_Symbol
						Initialization Functions:KML_INIT_Symbol
						KML_SYMBOL Functions:KML_INIT_Symbol

	PUBLISH XREF:	KML_INIT_Symbol

	PUBLISH NAME:	KML_INIT_Symbol

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_INIT_Symbol(KML_SYMBOL *ptr)
#else
void KML_INIT_Symbol(ptr)
KML_SYMBOL *ptr;
#endif /* #ifndef NARGS */
{
	memset(ptr, '\0', sizeof(*ptr));

	ptr->ptr    = NULL;
	ptr->length = 0;
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	KML_INIT_SymbolList

	SYNOPSIS		:	void KML_INIT_SymbolList(in_count, in_list);

						unsigned int  in_count;

						KML_SYMBOL   *in_list;

	DESCRIPTION	:	Initializes the elements of a array of ''KML_SYMBOL''
						structures to their default values.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_count`` is the number of elements in the array
						``in_list``.

						(.) ``in_list`` is the array of ''KML_SYMBOL''
						structures to be initialized by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_INIT_Symbol
						KML_COPY_SymbolList
						KML_FREE_SymbolList
						KML_SORT_SymbolList

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2018 Michael L. Brock

	OUTPUT INDEX:	KML_INIT_SymbolList
						Initialization Functions:KML_INIT_SymbolList
						KML_SYMBOL Functions:KML_INIT_SymbolList

	PUBLISH XREF:	KML_INIT_SymbolList

	PUBLISH NAME:	KML_INIT_SymbolList

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_INIT_SymbolList(unsigned int in_count, KML_SYMBOL *in_list)
#else
void KML_INIT_SymbolList(in_count, in_list)
unsigned int  in_count;
KML_SYMBOL   *in_list;
#endif /* #ifndef NARGS */
{
	while (in_count--)
		KML_INIT_Symbol(in_list++);
}
/*	***********************************************************************	*/

