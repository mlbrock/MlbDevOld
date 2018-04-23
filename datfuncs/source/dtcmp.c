/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Compares two DTIME structures.

	Revision History	:	1994-01-24 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	*********************************************************************** */
/*	*********************************************************************** */
/* 	Necessary include files . . .														*/
/*	*********************************************************************** */

#include "datfunci.h"

/*	*********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	DTIME_Compare

	SYNOPSIS		:	compare_value = DTIME_Compare(ptr_1, ptr_2);

						int          compare_value;

						const DTIME *ptr_1;

						const DTIME *ptr_2;

	DESCRIPTION	:	Compares two structures of type ''DTIME''.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``ptr_1`` points to the first ''DTIME'' structure
						to be compared.

						(.) ``ptr_2`` points to the second ''DTIME'' structure
						to be compared.

   RETURNS     :  Returns from this function are as follow:

						(.) negative if the first structure is less than second.

						(.) positive if the first structure is greater than second.

						(.) zero if the structures are equal.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	DTIME_STR_Compare

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	DTIME_Compare
						Date Functions:DTIME_Compare
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	DTIME_Compare

	PUBLISH NAME:	DTIME_Compare

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DTIME_Compare(const DTIME *ptr_1, const DTIME *ptr_2)
#else
int DTIME_Compare(ptr_1, ptr_2)
const DTIME *ptr_1;
const DTIME *ptr_2;
#endif /* #ifndef NARGS */
{
	int cmp;

	if ((cmp = ((ptr_1->julian_date > ptr_2->julian_date) ? 1 :
		(ptr_1->julian_date < ptr_2->julian_date) ? -1 : 0)) != 0)
		cmp = (ptr_1->milliseconds > ptr_2->milliseconds) ? 1 :
			(ptr_1->milliseconds < ptr_2->milliseconds) ? -1 : 0;

	return(cmp);
}
/* *********************************************************************** */

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	DTIME_STR_Compare

	SYNOPSIS		:	compare_value = DTIME_STR_Compare(control_ptr, ptr_1,
							ptr_2, data_length);

						int          compare_value;

						void        *control_ptr;

						const DTIME *ptr_1;

						const DTIME *ptr_2;

						size_t       data_length;

	DESCRIPTION	:	Compares two structures of type ''DTIME''.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``control_ptr`` points to a arbitrary user-defined
						structure which may be used to modify the comparison
						If unnecessary, it may be a NULL pointer.

						(.) ``ptr_1`` points to the first ''DTIME'' structure
						to be compared.

						(.) ``ptr_2`` points to the second ''DTIME'' structure
						to be compared.

						(.) ``data_length`` is the size the areas to which each
						''DTIME'' parameters point. If unnecessary, it may be
						zero (0).

   RETURNS     :  Returns from this function are as follow:

						(.) negative if the first structure is less than second.

						(.) positive if the first structure is greater than second.

						(.) zero if the structures are equal.

   NOTES       :  The ``control_ptr`` and ``string_length`` parameters are
						present only because this function is used internally
						by STRFUNCS list functions. They provide function-call
						compatibility with other, more generic, comparison
						functions.

	CAVEATS		:	

	SEE ALSO		:	DTIME_Compare

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	DTIME_STR_Compare
						Date Functions:DTIME_STR_Compare
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	DTIME_STR_Compare

	PUBLISH NAME:	DTIME_STR_Compare

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DTIME_STR_Compare(void *control_ptr, const DTIME *ptr_1,
	const DTIME *ptr_2, size_t data_length)
#else
int DTIME_STR_Compare(control_ptr, ptr_1, ptr_2, data_length)
void        *control_ptr;
const DTIME *ptr_1;
const DTIME *ptr_2;
size_t       data_length;
#endif /* #ifndef NARGS */
{
	int cmp;

	if ((cmp = ((ptr_1->julian_date > ptr_2->julian_date) ? 1 :
		(ptr_1->julian_date < ptr_2->julian_date) ? -1 : 0)) != 0)
		cmp = (ptr_1->milliseconds > ptr_2->milliseconds) ? 1 :
			(ptr_1->milliseconds < ptr_2->milliseconds) ? -1 : 0;

	return(cmp);
}
/* *********************************************************************** */
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

