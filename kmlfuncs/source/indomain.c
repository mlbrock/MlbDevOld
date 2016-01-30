/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes 'KML_DOMAIN' structures.

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

#include <memory.h>

#include "kmlfunci.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	KML_INIT_Domain

	SYNOPSIS		:	void KML_INIT_Domain(ptr);

						KML_DOMAIN *ptr;

	DESCRIPTION	:	Initializes the members of a ''KML_DOMAIN''
						structure to their default values.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``ptr`` points to the ''KML_DOMAIN''
						structure to be initialized by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_INIT_DomainList
						KML_CMP_Domain
						KML_COPY_Domain
						KML_FREE_Domain
						KML_SCMP_Domain

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2016 Michael L. Brock

	OUTPUT INDEX:	KML_INIT_Domain
						Initialization Functions:KML_INIT_Domain
						KML_DOMAIN Functions:KML_INIT_Domain

	PUBLISH XREF:	KML_INIT_Domain

	PUBLISH NAME:	KML_INIT_Domain

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_INIT_Domain(KML_DOMAIN *ptr)
#else
void KML_INIT_Domain(ptr)
KML_DOMAIN *ptr;
#endif /* #ifndef NARGS */
{
	memset(ptr, '\0', sizeof(*ptr));

	ptr->domain_name           = NULL;
	ptr->domain_description    = NULL;
	ptr->type_count            = 0;
	ptr->type_list             = NULL;
	ptr->string_case_flag      = KMLFUNCS_TRUE;
	ptr->string_count          = 0;
	ptr->string_list           = NULL;
	ptr->comment_case_flag     = KMLFUNCS_TRUE;
	ptr->comment_count         = 0;
	ptr->comment_list          = NULL;
	ptr->keyword_case_flag     = KMLFUNCS_TRUE;
	ptr->keyword_count         = 0;
	ptr->keyword_list          = NULL;
	ptr->symbol_case_flag      = KMLFUNCS_TRUE;
	ptr->symbol_count          = 0;
	ptr->symbol_list           = NULL;
	ptr->block_case_flag       = KMLFUNCS_TRUE;
	ptr->block_count           = 0;
	ptr->block_list            = NULL;
	ptr->name_case_flag        = KMLFUNCS_TRUE;
	ptr->name_count            = 0;
	ptr->name_list             = NULL;
	ptr->operator_case_flag    = KMLFUNCS_TRUE;
	ptr->operator_count        = 0;
	ptr->operator_list         = NULL;
	ptr->item_count            = 0;
	ptr->item_list             = NULL;

	KML_INIT_IndexList(UCHAR_MAX + 1, ptr->index_list);

	memset(ptr->name_flag_list,       '\0', sizeof(ptr->name_flag_list));
	memset(ptr->first_name_flag_list, '\0', sizeof(ptr->first_name_flag_list));
	memset(ptr->other_name_flag_list, '\0', sizeof(ptr->other_name_flag_list));

	ptr->min_name_length       = 0;
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	KML_INIT_DomainList

	SYNOPSIS		:	void KML_INIT_DomainList(in_count, in_list);

						unsigned int  in_count;

						KML_DOMAIN   *in_list;

	DESCRIPTION	:	Initializes the elements of a array of ''KML_DOMAIN''
						structures to their default values.

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_count`` is the number of elements in the array
						``in_list``.

						(.) ``in_list`` is the array of ''KML_DOMAIN''
						structures to be initialized by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	KML_INIT_Domain
						KML_COPY_DomainList
						KML_FREE_DomainList
						KML_SORT_DomainList

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2016 Michael L. Brock

	OUTPUT INDEX:	KML_INIT_DomainList
						Initialization Functions:KML_INIT_DomainList
						KML_DOMAIN Functions:KML_INIT_DomainList

	PUBLISH XREF:	KML_INIT_DomainList

	PUBLISH NAME:	KML_INIT_DomainList

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void KML_INIT_DomainList(unsigned int in_count, KML_DOMAIN *in_list)
#else
void KML_INIT_DomainList(in_count, in_list)
unsigned int  in_count;
KML_DOMAIN   *in_list;
#endif /* #ifndef NARGS */
{
	while (in_count--)
		KML_INIT_Domain(in_list++);
}
/*	***********************************************************************	*/

