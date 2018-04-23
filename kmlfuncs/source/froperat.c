/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Frees 'KML_OPERATOR' structures.

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

#include <stdlib.h>

#include "kmlfunci.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	KML_FREE_Operator

	SYNOPSIS		:	void KML_FREE_Operator(ptr);

						KML_OPERATOR *ptr;

	DESCRIPTION	:	Frees the members of a ''KML_OPERATOR'' structure.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``ptr`` points to the ''KML_OPERATOR''
						structure to be freed by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_FREE_OperatorList
						KML_CMP_Operator
						KML_COPY_Operator
						KML_INIT_Operator
						KML_SCMP_Operator

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2018 Michael L. Brock

	OUTPUT INDEX:	KML_FREE_Operator
						Memory Functions:KML_FREE_Operator
						KML_OPERATOR Functions:KML_FREE_Operator

	PUBLISH XREF:	KML_FREE_Operator

	PUBLISH NAME:	KML_FREE_Operator

	ENTRY CLASS	:	Memory Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_FREE_Operator(KML_OPERATOR *ptr)
#else
void KML_FREE_Operator(ptr)
KML_OPERATOR *ptr;
#endif /* #ifndef NARGS */
{
	if (ptr->ptr != NULL)
		free(ptr->ptr);

	KML_INIT_Operator(ptr);
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	KML_FREE_OperatorList

	SYNOPSIS		:	void KML_FREE_OperatorList(in_count, in_list);

						unsigned int  *in_count;

						KML_OPERATOR **in_list;

	DESCRIPTION	:	Frees the elements of an array of ''KML_OPERATOR''
						structures.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_count`` is a pointer to the ''unsigned int'' which
						contains the number of elements in the array to which
						the ``in_list`` parameter points.

						(.) ``in_list`` is a pointer to the array of ''KML_OPERATOR''
						structures to be freed by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_FREE_Operator
						KML_COPY_OperatorList
						KML_INIT_OperatorList
						KML_SORT_OperatorList

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2018 Michael L. Brock

	OUTPUT INDEX:	KML_FREE_OperatorList
						Memory Functions:KML_FREE_OperatorList
						KML_OPERATOR Functions:KML_FREE_OperatorList

	PUBLISH XREF:	KML_FREE_OperatorList

	PUBLISH NAME:	KML_FREE_OperatorList

	ENTRY CLASS	:	Memory Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_FREE_OperatorList(unsigned int *in_count, KML_OPERATOR **in_list)
#else
void KML_FREE_OperatorList(in_count, in_list)
unsigned int  *in_count;
KML_OPERATOR **in_list;
#endif /* #ifndef NARGS */
{
	while (*in_count)
		KML_FREE_Operator(*in_list + --(*in_count));

	if (*in_list != NULL)
		free(*in_list);

	*in_count = 0;
	*in_list  = NULL;
}
/*	***********************************************************************	*/

