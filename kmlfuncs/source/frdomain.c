/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Frees 'KML_DOMAIN' structures.

	Revision History	:	1998-03-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2016.
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

	NAME			:	KML_FREE_Domain

	SYNOPSIS		:	void KML_FREE_Domain(ptr);

						KML_DOMAIN *ptr;

	DESCRIPTION	:	Frees the members of a ''KML_DOMAIN'' structure.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``ptr`` points to the ''KML_DOMAIN''
						structure to be freed by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_FREE_DomainList
						KML_CMP_Domain
						KML_COPY_Domain
						KML_INIT_Domain
						KML_SCMP_Domain

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2016 Michael L. Brock

	OUTPUT INDEX:	KML_FREE_Domain
						Memory Functions:KML_FREE_Domain
						KML_DOMAIN Functions:KML_FREE_Domain

	PUBLISH XREF:	KML_FREE_Domain

	PUBLISH NAME:	KML_FREE_Domain

	ENTRY CLASS	:	Memory Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_FREE_Domain(KML_DOMAIN *ptr)
#else
void KML_FREE_Domain(ptr)
KML_DOMAIN *ptr;
#endif /* #ifndef NARGS */
{
	if (ptr->domain_name != NULL)
		free(ptr->domain_name);

	if (ptr->domain_description != NULL)
		free(ptr->domain_description);

	strl_remove_all(&ptr->type_count, &ptr->type_list);

	KML_FREE_StringList(&ptr->string_count, &ptr->string_list);
	KML_FREE_CommentList(&ptr->comment_count, &ptr->comment_list);
	KML_FREE_KeywordList(&ptr->keyword_count, &ptr->keyword_list);
	KML_FREE_SymbolList(&ptr->symbol_count, &ptr->symbol_list);
	KML_FREE_BlockList(&ptr->block_count, &ptr->block_list);
	KML_FREE_OperatorList(&ptr->operator_count, &ptr->operator_list);
	KML_FREE_NameList(&ptr->name_count, &ptr->name_list);

	if (ptr->item_count && (ptr->item_list != NULL))
		free(ptr->item_list);

	KML_INIT_Domain(ptr);
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	KML_FREE_DomainList

	SYNOPSIS		:	void KML_FREE_DomainList(in_count, in_list);

						unsigned int  *in_count;

						KML_DOMAIN   **in_list;

	DESCRIPTION	:	Frees the elements of an array of ''KML_DOMAIN''
						structures.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_count`` is a pointer to the ''unsigned int'' which
						contains the number of elements in the array to which
						the ``in_list`` parameter points.

						(.) ``in_list`` is a pointer to the array of ''KML_DOMAIN''
						structures to be freed by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_FREE_Domain
						KML_COPY_DomainList
						KML_INIT_DomainList
						KML_SORT_DomainList

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2016 Michael L. Brock

	OUTPUT INDEX:	KML_FREE_DomainList
						Memory Functions:KML_FREE_DomainList
						KML_DOMAIN Functions:KML_FREE_DomainList

	PUBLISH XREF:	KML_FREE_DomainList

	PUBLISH NAME:	KML_FREE_DomainList

	ENTRY CLASS	:	Memory Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_FREE_DomainList(unsigned int *in_count, KML_DOMAIN **in_list)
#else
void KML_FREE_DomainList(in_count, in_list)
unsigned int  *in_count;
KML_DOMAIN   **in_list;
#endif /* #ifndef NARGS */
{
	while (*in_count)
		KML_FREE_Domain(*in_list + --(*in_count));

	if (*in_list != NULL)
		free(*in_list);

	*in_count = 0;
	*in_list  = NULL;
}
/*	***********************************************************************	*/

