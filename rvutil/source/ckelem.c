/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Checks a subject name element to ensure that it is
								valid.

	Revision History	:	1996-01-20 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <string.h>

#include <strfuncs.h>

#include "rvutili.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_CheckElement(const char *element, char *error_text)
{
	int return_code = RVUTIL_SUCCESS;

	if ((element == NULL) || (!(*element))) {
		strcat(strcpy(error_text, "Rendezvous subject name element is "),
			(element == NULL) ? "'NULL'." : "an empty string (\"\").");
		return_code = RVUTIL_INVALID_SUBJECT_ELEMENT;
	}
	else if (strlen(element) > RVUTIL_MAX_ELEMENT_LEN) {
		sprintf(error_text, "%s '%-.500s' (%u) %s (%d).",
			"The length of the Rendezvous subject name element", element,
			strlen(element), "exceeds the maximum permitted",
			RVUTIL_MAX_ELEMENT_LEN);
		return_code = RVUTIL_INVALID_SUBJECT_ELEMENT;
	}
	else if (strchr(element, RVUTIL_ELEMENT_SEP_CHAR) != NULL) {
		sprintf(error_text, "Rendezvous subject name element '%s' %s '%c'.",
			element, "contains an element separator character",
			RVUTIL_ELEMENT_SEP_CHAR);
		return_code = RVUTIL_INVALID_SUBJECT_ELEMENT;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_CheckElementIsFull(const char *element, char *error_text)
{
	int   return_code = RVUTIL_SUCCESS;
	char *tmp_ptr;

	if ((return_code = RVUTIL_CheckElement(element, error_text)) ==
		RVUTIL_SUCCESS) {
		if ((tmp_ptr = chrinstr(element, RVUTIL_ELEMENT_PATTERNCHAR_STR)) !=
			NULL) {
			sprintf(error_text, "Rendezvous subject name element '%s' %s '%c'.",
				element, "contains an element pattern character", *tmp_ptr);
			return_code = RVUTIL_INVALID_SUBJECT_ELEMENT;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

