/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Compares two 'KML_MATCH' structures.

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

#include "kmlfunci.h"

/*	***********************************************************************	*/

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME        :	KML_SCMP_Match

	SYNOPSIS    :	return_code = KML_SCMP_Match(control_ptr, ptr_1,
							ptr_2, data_length);

						int              return_code;

						void            *control_ptr;

						const KML_MATCH *ptr_1;

						const KML_MATCH *ptr_2;

						size_t           data_length;

	DESCRIPTION :	Compares two ''KML_MATCH'' structures to
						determine their equivalence.

						The following members of the ''KML_MATCH''
						structure are used as the basis of the comparison:

						(.) ``ptr``

						(.) ``type``

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``control_ptr`` points to a arbitrary user-defined
						structure which may be used to modify the comparison.
						Because it is unnecessary to the comparison of
						''KML_MATCH'' structures, it may be passed as a
						''NULL'' pointer.

						(.) ``ptr_1`` points to the first ''KML_MATCH''
						structure to be compared.

						(.) ``ptr_2`` points to the second ''KML_MATCH''
						structure to be compared.

						(.) ``data_length`` is the size the areas to which
						``ptr_1`` and ``ptr_2`` point. Because it is unnecessary
						to the comparison of ''KML_MATCH'' structures,
						it may be zero (''0'').

	RETURNS     :	Returns from this function are as follow:

						(.) negative if the first ''KML_MATCH'' structure
						is less than second.

						(.) positive if the first ''KML_MATCH'' structure
						is greater than second.

						(.) zero if the structures are equivalent.

	NOTES       :  The ``control_ptr`` and ``data_length`` parameters are
						present only because this function is used internally
						by the STRFUNCS list functions. These parameters provide
						function-call compatibility with other, more generic,
						functions such as ``KML_SORT_MatchList``.

	CAVEATS     :	

	SEE ALSO    :	

	EXAMPLES    :	

	AUTHOR      :	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2018 Michael L. Brock

	OUTPUT INDEX:	KML_SCMP_Match
						Comparison Functions:KML_SCMP_Match
						KML_MATCH Functions:KML_SCMP_Match

	PUBLISH XREF:	KML_SCMP_Match

	PUBLISH NAME:	KML_SCMP_Match

	ENTRY CLASS	:	Comparison Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int KML_SCMP_Match(void *control_ptr, const KML_MATCH *ptr_1,
	const KML_MATCH *ptr_2, size_t data_length)
#else
int KML_SCMP_Match(control_ptr, ptr_1, ptr_2, data_length)
void            *control_ptr;
const KML_MATCH *ptr_1;
const KML_MATCH *ptr_2;
size_t           data_length;
#endif /* #ifndef NARGS */
{
	return((ptr_1->ptr > ptr_2->ptr) ? 1 : (ptr_1->ptr < ptr_2->ptr) ? -1 :
		((ptr_1->type > ptr_2->type) ? 1 : (ptr_1->type < ptr_2->type) ? -1 :
		0));
}
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

