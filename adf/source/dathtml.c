/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Manages use of the 'ADF_STRING_PAIR' structure.

	Revision History	:	1996-07-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2014.
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
#include <stdlib.h>

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_InitDataHTML(ADF_HTML_DATA *html_data_ptr)
#else
void ADF_InitDataHTML(html_data_ptr)
ADF_HTML_DATA *html_data_ptr;
#endif /* #ifndef NARGS */
{
	memset(html_data_ptr, '\0', sizeof(*html_data_ptr));

	html_data_ptr->author_link_count    = 0;
	html_data_ptr->author_link_list     = NULL;
	html_data_ptr->copyright_link_count = 0;
	html_data_ptr->copyright_link_list  = NULL;

	nstrcpy(html_data_ptr->html_heading_level, "1",
		sizeof(html_data_ptr->html_heading_level) - 1);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_FreeDataHTML(ADF_HTML_DATA *html_data_ptr)
#else
void ADF_FreeDataHTML(html_data_ptr)
ADF_HTML_DATA *html_data_ptr;
#endif /* #ifndef NARGS */
{
	ADF_StrPairListFree(&html_data_ptr->author_link_count,
		&html_data_ptr->author_link_list);
	ADF_StrPairListFree(&html_data_ptr->copyright_link_count,
		&html_data_ptr->copyright_link_list);

	ADF_InitDataHTML(html_data_ptr);
}
/*	***********************************************************************	*/

