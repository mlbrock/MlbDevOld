/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Frees 'KML_SYMBOL' structures.

	Revision History	:	1998-03-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2015.
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

#include "kmlfunci.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	KML_FREE_Symbol

	SYNOPSIS		:	void KML_FREE_Symbol(ptr);

						KML_SYMBOL *ptr;

	DESCRIPTION	:	Frees the members of a ''KML_SYMBOL'' structure.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``ptr`` points to the ''KML_SYMBOL''
						structure to be freed by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_FREE_SymbolList
						KML_CMP_Symbol
						KML_COPY_Symbol
						KML_INIT_Symbol
						KML_SCMP_Symbol

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2015 Michael L. Brock

	OUTPUT INDEX:	KML_FREE_Symbol
						Memory Functions:KML_FREE_Symbol
						KML_SYMBOL Functions:KML_FREE_Symbol

	PUBLISH XREF:	KML_FREE_Symbol

	PUBLISH NAME:	KML_FREE_Symbol

	ENTRY CLASS	:	Memory Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_FREE_Symbol(KML_SYMBOL *ptr)
#else
void KML_FREE_Symbol(ptr)
KML_SYMBOL *ptr;
#endif /* #ifndef NARGS */
{
	if (ptr->ptr != NULL)
		free(ptr->ptr);

	KML_INIT_Symbol(ptr);
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	KML_FREE_SymbolList

	SYNOPSIS		:	void KML_FREE_SymbolList(in_count, in_list);

						unsigned int  *in_count;

						KML_SYMBOL   **in_list;

	DESCRIPTION	:	Frees the elements of an array of ''KML_SYMBOL''
						structures.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_count`` is a pointer to the ''unsigned int'' which
						contains the number of elements in the array to which
						the ``in_list`` parameter points.

						(.) ``in_list`` is a pointer to the array of ''KML_SYMBOL''
						structures to be freed by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_FREE_Symbol
						KML_COPY_SymbolList
						KML_INIT_SymbolList
						KML_SORT_SymbolList

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2015 Michael L. Brock

	OUTPUT INDEX:	KML_FREE_SymbolList
						Memory Functions:KML_FREE_SymbolList
						KML_SYMBOL Functions:KML_FREE_SymbolList

	PUBLISH XREF:	KML_FREE_SymbolList

	PUBLISH NAME:	KML_FREE_SymbolList

	ENTRY CLASS	:	Memory Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_FREE_SymbolList(unsigned int *in_count, KML_SYMBOL **in_list)
#else
void KML_FREE_SymbolList(in_count, in_list)
unsigned int  *in_count;
KML_SYMBOL   **in_list;
#endif /* #ifndef NARGS */
{
	while (*in_count)
		KML_FREE_Symbol(*in_list + --(*in_count));

	if (*in_list != NULL)
		free(*in_list);

	*in_count = 0;
	*in_list  = NULL;
}
/*	***********************************************************************	*/

