/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Checks a subject name to ensure its validity.

	Revision History	:	1996-01-12 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2014.
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
int RVUTIL_CheckSubjectName(const char *in_name, char *error_text)
{
	int               return_code;
	RVUTIL_SNAME_WORK tmp_name;
	char              tmp_error_text[RVUTIL_MAX_ERROR_TEXT];

	if ((return_code = RVUTIL_CrackSubjectName(in_name, &tmp_name,
		tmp_error_text)) != RVUTIL_SUCCESS)
		nstrcat(strcpy(error_text, "Invalid Rendezvous subject name: "),
			tmp_error_text, RVUTIL_MAX_ERROR_TEXT - 50);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_CheckSubjectNameIsFull(const char *in_name, char *error_text)
{
	int                return_code;
	unsigned int       count_1;
	char              *tmp_ptr;
	RVUTIL_SNAME_WORK  tmp_name;
	char               tmp_error_text[RVUTIL_MAX_ERROR_TEXT];

	if ((return_code = RVUTIL_CrackSubjectName(in_name, &tmp_name,
		tmp_error_text)) != RVUTIL_SUCCESS)
		nstrcat(strcpy(error_text, "Invalid Rendezvous subject name: "),
			tmp_error_text, RVUTIL_MAX_ERROR_TEXT - 50);
	else {
		for (count_1 = 0; count_1 < tmp_name.element_count; count_1++) {
			if (!tmp_name.element_list[count_1]) {
				sprintf(error_text,
					"%s '%s' %s %u ('%s'): empty element encountered.",
					"Rendezvous subject name", in_name,
					"is not fully qualified in element", count_1 + 1,
					tmp_name.element_list[count_1]);
				return_code = RVUTIL_INVALID_FULL_SUBJECT;
				break;
			}
			else if ((tmp_ptr = chrinstr(tmp_name.element_list[count_1],
				RVUTIL_ELEMENT_PATTERNCHAR_STR)) != NULL) {
				sprintf(error_text,
					"%s '%s' %s %u ('%s'): pattern character '%c' encountered.",
					"Rendezvous subject name", in_name,
					"is not fully qualified in element", count_1 + 1,
					tmp_name.element_list[count_1], *tmp_ptr);
				return_code = RVUTIL_INVALID_FULL_SUBJECT;
				break;
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

