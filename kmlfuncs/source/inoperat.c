/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes 'KML_OPERATOR' structures.

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

#include <memory.h>

#include "kmlfunci.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	KML_INIT_Operator

	SYNOPSIS		:	void KML_INIT_Operator(ptr);

						KML_OPERATOR *ptr;

	DESCRIPTION	:	Initializes the members of a ''KML_OPERATOR''
						structure to their default values.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``ptr`` points to the ''KML_OPERATOR''
						structure to be initialized by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_INIT_OperatorList
						KML_CMP_Operator
						KML_COPY_Operator
						KML_FREE_Operator
						KML_SCMP_Operator

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2015 Michael L. Brock

	OUTPUT INDEX:	KML_INIT_Operator
						Initialization Functions:KML_INIT_Operator
						KML_OPERATOR Functions:KML_INIT_Operator

	PUBLISH XREF:	KML_INIT_Operator

	PUBLISH NAME:	KML_INIT_Operator

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_INIT_Operator(KML_OPERATOR *ptr)
#else
void KML_INIT_Operator(ptr)
KML_OPERATOR *ptr;
#endif /* #ifndef NARGS */
{
	memset(ptr, '\0', sizeof(*ptr));

	ptr->ptr     = NULL;
	ptr->length  = 0;
	ptr->op_type = 0;
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	KML_INIT_OperatorList

	SYNOPSIS		:	void KML_INIT_OperatorList(in_count, in_list);

						unsigned int  in_count;

						KML_OPERATOR *in_list;

	DESCRIPTION	:	Initializes the elements of a array of ''KML_OPERATOR''
						structures to their default values.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_count`` is the number of elements in the array
						``in_list``.

						(.) ``in_list`` is the array of ''KML_OPERATOR''
						structures to be initialized by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_INIT_Operator
						KML_COPY_OperatorList
						KML_FREE_OperatorList
						KML_SORT_OperatorList

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2015 Michael L. Brock

	OUTPUT INDEX:	KML_INIT_OperatorList
						Initialization Functions:KML_INIT_OperatorList
						KML_OPERATOR Functions:KML_INIT_OperatorList

	PUBLISH XREF:	KML_INIT_OperatorList

	PUBLISH NAME:	KML_INIT_OperatorList

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_INIT_OperatorList(unsigned int in_count, KML_OPERATOR *in_list)
#else
void KML_INIT_OperatorList(in_count, in_list)
unsigned int  in_count;
KML_OPERATOR *in_list;
#endif /* #ifndef NARGS */
{
	while (in_count--)
		KML_INIT_Operator(in_list++);
}
/*	***********************************************************************	*/

