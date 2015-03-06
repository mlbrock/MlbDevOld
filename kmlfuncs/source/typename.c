/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets the name of a KML type.

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

#include <string.h>

#include "kmlfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *KML_GetTypeName(unsigned int in_type, char *out_name)
#else
char *KML_GetTypeName(in_type, out_name)
unsigned int  in_type;
char         *out_name;
#endif /* #ifndef NARGS */
{
	switch (in_type) {
		case KML_TYPE_STRING		:
			strcpy(out_name, "string");
			break;
		case KML_TYPE_COMMENT	:
			strcpy(out_name, "comment");
			break;
		case KML_TYPE_KEYWORD	:
			strcpy(out_name, "keyword");
			break;
		case KML_TYPE_SYMBOL		:
			strcpy(out_name, "symbol");
			break;
		case KML_TYPE_BLOCK		:
			strcpy(out_name, "block");
			break;
		case KML_TYPE_NAME		:
			strcpy(out_name, "name");
			break;
		case KML_TYPE_NUMBER		:
			strcpy(out_name, "number");
			break;
		case KML_TYPE_OPERATOR	:
			strcpy(out_name, "operator");
			break;
		default						:
			*out_name = '\0';
			break;
	}                               

	return(out_name);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *KML_GetTypeNameExtended(unsigned int in_type, char *out_name)
#else
char *KML_GetTypeNameExtended(in_type, out_name)
unsigned int  in_type;
char         *out_name;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;
	char         buffer[16];

	*out_name  = '\0';
	in_type   &= KML_TYPE_MASK;

	for (count_1 = 1; count_1 <= KML_TYPE_MASK; count_1 <<= 1) {
		if (in_type & count_1)
			strcat(strcat(out_name, (*out_name) ? " " : ""),
				KML_GetTypeName(in_type & count_1, buffer));
	}

	return(out_name);
}
/*	***********************************************************************	*/

