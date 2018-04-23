/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	GENFUNCS General Functions Library Source Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Manages 'GEN_MEMBER' structures.

	Revision History	:	1993-12-09 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2018.
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
#include <string.h>

#include "genfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_APPD_Member

   SYNOPSIS    :	return_code = GEN_APPD_Member(in_ptr, out_count, out_list,
							error_text);

						int                return_code;

						const GEN_MEMBER  *in_ptr;

						unsigned int      *out_count;

						GEN_MEMBER       **out_list;

						char              *error_text;

   DESCRIPTION :	Appends a single ''GEN_MEMBER'' structure to a list of
						''GEN_MEMBER'' structures.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_ptr`` is a pointer to the ''GEN_MEMBER'' structure
						which is to be copied by this function.

						(.) ``out_count`` is a pointer to an ''unsigned int'' which
						contains the number of elements in the array ``out_list``.
						If the structure to which ``in_ptr`` points is successfully
						copied into the ``out_list``, this function will increment
						the ''unsigned int'' to which ``out_count`` points.

						(.) ``out_list`` is a pointer to the array of ''GEN_MEMBER''
						structures into which ``in_ptr`` will be copied by this
						function.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if the function completes without
						error. ''GENFUNCS_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero GENFUNCS return codes
						indicative of error.

   NOTES       :	

   CAVEATS     :  

   SEE ALSO    :	GEN_COPY_Member

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   APPDRIGHT   :	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_APPD_Member
						Copy Functions:GEN_APPD_Member
						General Functions:see GENFUNCS

   PUBLISH XREF:	GEN_APPD_Member

   PUBLISH NAME:	GEN_APPD_Member

	ENTRY CLASS	:	Copy Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_APPD_Member(const GEN_MEMBER *in_ptr, unsigned int *out_count,
	GEN_MEMBER **out_list, char *error_text)
#else
int GEN_APPD_Member(in_ptr, out_count, out_list, error_text)
const GEN_MEMBER  *in_ptr;
unsigned int      *out_count;
GEN_MEMBER       **out_list;
char              *error_text;
#endif /* #ifndef NARGS */
{
	int        return_code;
	GEN_MEMBER member_data;

	if ((return_code = GEN_COPY_Member(in_ptr, &member_data, error_text)) ==
		GENFUNCS_SUCCESS) {
		if (mema_append(out_count, ((void **) out_list), &member_data,
			sizeof(**out_list)) != STRFUNCS_SUCCESS) {
			GEN_FREE_Member(&member_data);
			GEN_AllocMsgItem(sizeof(**out_list), error_text,
				"Unable to allocate memory for the 'GEN_MEMBER' list append");
			return_code = GENFUNCS_MEMORY_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_COPY_Member

   SYNOPSIS    :	return_code = GEN_COPY_Member(in_ptr, out_ptr, error_text);

						int               return_code;

						const GEN_MEMBER *in_ptr;

						GEN_MEMBER       *out_ptr;

						char             *error_text;

   DESCRIPTION :	Copies a single ''GEN_MEMBER'' structures.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_ptr`` is a pointer to the ''GEN_MEMBER'' structure
						which is to be copied by this function.

						(.) ``out_ptr`` is a pointer to the ''GEN_MEMBER''
						structure into which the copy is to be performed.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if the function completes without
						error. ''GENFUNCS_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero GENFUNCS return codes
						indicative of error.

   NOTES       :	

   CAVEATS     :  

   SEE ALSO    :	GEN_COPY_MemberList
						GEN_APPD_Member

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_COPY_Member
						Copy Functions:GEN_COPY_Member
						General Functions:see GENFUNCS

   PUBLISH XREF:	GEN_COPY_Member

   PUBLISH NAME:	GEN_COPY_Member

	ENTRY CLASS	:	Copy Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_COPY_Member(const GEN_MEMBER *in_ptr, GEN_MEMBER *out_ptr,
	char *error_text)
#else
int GEN_COPY_Member(in_ptr, out_ptr, error_text)
const GEN_MEMBER *in_ptr;
GEN_MEMBER       *out_ptr;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = GENFUNCS_SUCCESS;

	*out_ptr = *in_ptr;

	if ((in_ptr->display_name != NULL) && ((out_ptr->display_name =
		strdup(in_ptr->display_name)) == NULL)) {
		GEN_INIT_Member(out_ptr);
		GEN_AllocMsgItem(strlen(in_ptr->display_name) + 1, error_text,
			"Unable to copy a 'GEN_MEMBER' display name");
		return_code = GENFUNCS_MEMORY_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_COPY_MemberList

   SYNOPSIS    :	return_code = GEN_COPY_MemberList(in_count, in_list,
							out_count, out_list);

						int                return_code;

						unsigned int       in_count;

						const GEN_MEMBER  *in_list;

						unsigned int      *out_count;

						GEN_MEMBER       **out_list;

						char              *error_text;

   DESCRIPTION :	Copies an array of ''GEN_MEMBER'' structures.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_count`` is the number of elements in the array
						``in_list``.

						(.) ``in_list`` is the array of ''GEN_MEMBER'' structures
						which is to be copied by this function.

						(.) ``out_count`` is a pointer to an ''unsigned int'' into
						which this function will place the number of elements
						copied.

						(.) ``out_list`` is a pointer to the array of ''GEN_MEMBER''
						structures which will be allocated and copied by this
						function.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if the function completes without
						error. ''GENFUNCS_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero GENFUNCS return codes
						indicative of error.

   NOTES       :	

   CAVEATS     :  

   SEE ALSO    :	GEN_COPY_Member

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_COPY_MemberList
						Copy Functions:GEN_COPY_MemberList
						General Functions:see GENFUNCS

   PUBLISH XREF:	GEN_COPY_MemberList

   PUBLISH NAME:	GEN_COPY_MemberList

	ENTRY CLASS	:	Copy Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_COPY_MemberList(unsigned int in_count, const GEN_MEMBER *in_list,
	unsigned int *out_count, GEN_MEMBER **out_list, char *error_text)
#else
int GEN_COPY_MemberList(in_count, in_list, out_count, out_list, error_text)
unsigned int       in_count;
const GEN_MEMBER  *in_list;
unsigned int      *out_count;
GEN_MEMBER       **out_list;
char              *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = GENFUNCS_SUCCESS;
	unsigned int count_1;

	*out_count = 0;
	*out_list  = NULL;

	if (in_count) {
		if ((*out_list = ((GEN_MEMBER *) calloc(in_count, sizeof(*in_list)))) ==
			NULL) {
			GEN_AllocMsgList(in_count, sizeof(**out_list), error_text,
				"Unable to allocate memory for the 'GEN_MEMBER' list copy");
			return_code = GENFUNCS_MEMORY_FAILURE;
		}
		else {
			*out_count = in_count;
			GEN_INIT_MemberList(*out_count, *out_list);
			for (count_1 = 0; count_1 < in_count; count_1++) {
				if ((return_code = GEN_COPY_Member(in_list + count_1,
					*out_list + count_1, error_text)) != GENFUNCS_SUCCESS) {
					GEN_FREE_MemberList(out_count, out_list);
					break;
				}
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_FREE_Member

   SYNOPSIS    :	void GEN_FREE_Member(ptr);

						GEN_MEMBER *ptr;

   DESCRIPTION :	Frees the members of a ''GEN_MEMBER'' structure and
						initializes them to their default values.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``ptr`` points to the ''GEN_MEMBER'' structure to be
						freed by this function.

   RETURNS     :	Void.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	GEN_INIT_Member
						GEN_FREE_MemberList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_FREE_Member
						Free Functions:GEN_FREE_Member
						General Functions:see GENFUNCS

   PUBLISH XREF:	GEN_FREE_Member

   PUBLISH NAME:	GEN_FREE_Member

	ENTRY CLASS	:	Free Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void GEN_FREE_Member(GEN_MEMBER *ptr)
#else
void GEN_FREE_Member(ptr)
GEN_MEMBER *ptr;
#endif /* #ifndef NARGS */
{
	if (ptr->display_name != NULL)
		free(ptr->display_name);

	GEN_INIT_Member(ptr);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_FREE_MemberList

   SYNOPSIS    :	void GEN_FREE_MemberList(member_count, member_list);

						unsigned int  *member_count;

						GEN_MEMBER   **member_list;

   DESCRIPTION :	Frees an array of ''GEN_MEMBER'' structures.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``member_count`` points to the ''unsigned int'' which
						contains the number of elements in the array to which the
						``member_list`` parameter points.

						(.) ``member_list`` points to the array of ''GEN_MEMBER''
						structures to be freed by this function.

   RETURNS     :	Void.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	GEN_FREE_Member

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_FREE_MemberList
						Free Functions:GEN_FREE_MemberList
						General Functions:see GENFUNCS

   PUBLISH XREF:	GEN_FREE_MemberList

   PUBLISH NAME:	GEN_FREE_MemberList

	ENTRY CLASS	:	Free Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void GEN_FREE_MemberList(unsigned int *member_count, GEN_MEMBER **member_list)
#else
void GEN_FREE_MemberList(member_count, member_list)
unsigned int  *member_count;
GEN_MEMBER   **member_list;
#endif /* #ifndef NARGS */
{
	while (*member_count)
		GEN_FREE_Member(*member_list + --(*member_count));
		
	if (*member_list != NULL)
		free(*member_list);

	*member_count = 0;
	*member_list  = NULL;
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_INIT_Member

   SYNOPSIS    :	void GEN_INIT_Member(ptr);

						GEN_MEMBER *ptr;

   DESCRIPTION :	Initializes the members of a ''GEN_MEMBER'' structure to
						their default values.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``ptr`` points to the ''GEN_MEMBER'' structure to be
						initialized by this function.

   RETURNS     :	Void.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	GEN_INIT_MemberList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_INIT_Member
						Initialization Functions:GEN_INIT_Member
						General Functions:see GENFUNCS

   PUBLISH XREF:	GEN_INIT_Member

   PUBLISH NAME:	GEN_INIT_Member

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void GEN_INIT_Member(GEN_MEMBER *ptr)
#else
void GEN_INIT_Member(ptr)
GEN_MEMBER *ptr;
#endif /* #ifndef NARGS */
{
	memset(ptr, '\0', sizeof(*ptr));

	ptr->name[0]        = 0;
	ptr->data_length    = 0;
	ptr->length         = 0;
	ptr->offset         = 0;
	ptr->type_count     = 0;
	ptr->type_spec[0]   = '\0';
	ptr->align_count    = 0;
	ptr->display_length = 0;
	ptr->display_name   = NULL;
	ptr->dbc_type       = 0;
	ptr->user_int_1     = 0;
	ptr->user_int_2     = 0;
	ptr->user_ptr_1     = 0;
	ptr->user_ptr_2     = 0;
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_INIT_MemberList

   SYNOPSIS    :	void GEN_INIT_MemberList(count, list);

						unsigned int  count;

						GEN_MEMBER   *list;

   DESCRIPTION :	Initializes the elements of a list of a ''GEN_MEMBER''
						structures to their default values.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``count`` is the number of elements in the list
						``list``.

						(.) ``list`` is the list of ''GEN_MEMBER'' structures to be
						initialized by this function.

   RETURNS     :	Void.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	GEN_INIT_Member

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_INIT_MemberList
						Initialization Functions:GEN_INIT_MemberList
						General Functions:see GENFUNCS

   PUBLISH XREF:	GEN_INIT_MemberList

   PUBLISH NAME:	GEN_INIT_MemberList

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void GEN_INIT_MemberList(unsigned int member_count, GEN_MEMBER *member_list)
#else
void GEN_INIT_MemberList(member_count, member_list)
unsigned int  member_count;
GEN_MEMBER   *member_list;
#endif /* #ifndef NARGS */
{
	while (member_count--)
		GEN_INIT_Member(member_list++);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_EMIT_MemberList

   SYNOPSIS    :	void GEN_EMIT_MemberList(count, list, output_function,
							output_control);

						unsigned int       count;

						const GEN_MEMBER  *list;

						void             (*output_function)(void *, char *, ...);

						void              *output_control;

   DESCRIPTION :	Emits a list of ''GEN_MEMBER'' structures to the specified
						output handler. The structure members are emitted in
						human-readable columnar output.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``count`` is the number of elements in the array
						``list``.

						(.) ``list`` is the array of ''GEN_MEMBER'' structures which
						is to be emitted by this function.

						(.) ``output_function`` is a pointer to the function which
						handles output. The function should take arguments of the
						general form:

						<->``output_function``(void *, ``format_string``, ``...``);

						(-) Functions of this form include the C standard library
						function ``fprintf``. The memory-mapped library function
						``mprintf`` may also be used.

						(-) If the ``output_function`` parameter is ''NULL'', the
						function will set it to ``fprintf``.

						(.) ``output_control`` is the pointer which will be used by
						this function as the first parameter to the function
						specified by the ``output_function`` parameter.

						(-) For example, if ``output_function`` points to the
						function ``fprintf``, then ``output_control`` should be
						a pointer to a structure of type ''FILE''.

						(-) If the `` output_control`` parameter is ''NULL'', the
						function will set it to ``stdout``.

   RETURNS     :	Void.

   NOTES       :	This function emits the list of ''GEN_MEMBER'' structures
						with column headers and trailers. If you do not want this
						behavior, you must call the related function
						``GEN_EMIT_Member`` for each array element.

						You can emit the list of ''GEN_MEMBER'' structures prepended
						by the index within the list by using the related function
						``GEN_EMIT_MemberListIdx``.

   CAVEATS     :	

   SEE ALSO    :	GEN_EMIT_MemberListIdx
						GEN_EMIT_Member
						GEN_EMIT_MemberHeader
						GEN_EMIT_MemberTrailer

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_EMIT_MemberList
						Emit Functions:GEN_EMIT_MemberList
						General Functions:see GENFUNCS

   PUBLISH XREF:	GEN_EMIT_MemberList

   PUBLISH NAME:	GEN_EMIT_MemberList

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void GEN_EMIT_MemberList(unsigned int count, const GEN_MEMBER *list,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
void GEN_EMIT_MemberList(count, list, output_function, output_control)
unsigned int           count;
const GEN_MEMBER      *list;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	GEN_EMIT_MemberHeader(output_function, output_control);
	GEN_EMIT_MemberTrailer(output_function, output_control);

	while (count--)
		GEN_EMIT_Member(list++, output_function, output_control);

	GEN_EMIT_MemberTrailer(output_function, output_control);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_EMIT_MemberListIdx

   SYNOPSIS    :	void GEN_EMIT_MemberListIdx(count, list, output_function,
							output_control);

						unsigned int       count;

						const GEN_MEMBER  *list;

						void             (*output_function)(void *, char *, ...);

						void              *output_control;

   DESCRIPTION :	Emits a list of ''GEN_MEMBER'' structures to the specified
						output handler. The structure members are emitted in
						human-readable columnar output.

						Each element of ``list`` is emited by this function prepended
						by the six-digit, zero-filled index of the element in the
						``list``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``count`` is the number of elements in the array
						``list``.

						(.) ``list`` is the array of ''GEN_MEMBER'' structures which
						is to be emitted by this function.

						(.) ``output_function`` is a pointer to the function which
						handles output. The function should take arguments of the
						general form:

						<->``output_function``(void *, ``format_string``, ``...``);

						(-) Functions of this form include the C standard library
						function ``fprintf``. The memory-mapped library function
						``mprintf`` may also be used.

						(-) If the ``output_function`` parameter is ''NULL'', the
						function will set it to ``fprintf``.

						(.) ``output_control`` is the pointer which will be used by
						this function as the first parameter to the function
						specified by the ``output_function`` parameter.

						(-) For example, if ``output_function`` points to the
						function ``fprintf``, then ``output_control`` should be
						a pointer to a structure of type ''FILE''.

						(-) If the `` output_control`` parameter is ''NULL'', the
						function will set it to ``stdout``.

   RETURNS     :	Void.

   NOTES       :	You can emit the list of ''GEN_MEMBER'' structures without
						the prepended index by using the related function
						``GEN_EMIT_MemberList``.
	
   CAVEATS     :	

   SEE ALSO    :	GEN_EMIT_MemberList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_EMIT_MemberListIdx
						Emit Functions:GEN_EMIT_MemberListIdx
						General Functions:see GENFUNCS

   PUBLISH XREF:	GEN_EMIT_MemberListIdx

   PUBLISH NAME:	GEN_EMIT_MemberListIdx

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void GEN_EMIT_MemberListIdx(unsigned int count, const GEN_MEMBER *list,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
void GEN_EMIT_MemberListIdx(count, list, output_function, output_control)
unsigned int           count;
const GEN_MEMBER      *list;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;

	STR_EMIT_SetDefaults(&output_function, &output_control);

	(*output_function)(output_control, "Index  ");
	GEN_EMIT_MemberHeader(output_function, output_control);

	(*output_function)(output_control, "------ ");
	GEN_EMIT_MemberTrailer(output_function, output_control);

	for (count_1 = 0; count_1 < count; count_1++) {
		(*output_function)(output_control, "%06u ", count_1);
		GEN_EMIT_Member(list++, output_function, output_control);
	}

	(*output_function)(output_control, "------ ");
	GEN_EMIT_MemberTrailer(output_function, output_control);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_EMIT_Member

   SYNOPSIS    :	void GEN_EMIT_Member(ptr, output_function, output_control);

						const GEN_MEMBER  *ptr;

						void             (*output_function)(void *, char *, ...);

						void              *output_control;

   DESCRIPTION :	Emits a single ''GEN_MEMBER'' structure to the specified
						output handler. The structure members are emitted in
						human-readable columnar output.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``ptr`` is a pointer to the ''GEN_MEMBER'' structure
						which is to be emitted by this function.

						(.) ``output_function`` is a pointer to the function which
						handles output. The function should take arguments of the
						general form:

						<->``output_function``(void *, ``format_string``, ``...``);

						(-) Functions of this form include the C standard library
						function ``fprintf``. The memory-mapped library function
						``mprintf`` may also be used.

						(-) If the ``output_function`` parameter is ''NULL'', the
						function will set it to ``fprintf``.

						(.) ``output_control`` is the pointer which will be used by
						this function as the first parameter to the function
						specified by the ``output_function`` parameter.

						(-) For example, if ``output_function`` points to the
						function ``fprintf``, then ``output_control`` should be
						a pointer to a structure of type ''FILE''.

						(-) If the `` output_control`` parameter is ''NULL'', the
						function will set it to ``stdout``.

   RETURNS     :	Void.

   NOTES       :	To emit an array of ''GEN_MEMBER'' structures, use the
						related function ``GEN_EMIT_MemberList``.

   CAVEATS     :	

   SEE ALSO    :	GEN_EMIT_MemberList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_EMIT_Member
						Emit Functions:GEN_EMIT_Member
						General Functions:see GENFUNCS

   PUBLISH XREF:	GEN_EMIT_Member

   PUBLISH NAME:	GEN_EMIT_Member

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void GEN_EMIT_Member(const GEN_MEMBER *ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
void GEN_EMIT_Member(ptr, output_function, output_control)
const GEN_MEMBER      *ptr;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	STR_EMIT_SetDefaults(&output_function, &output_control);

	(*output_function)(output_control,
		"%-*.*s %10u %10u %10u %10u %-*.*s %11u %11u %11u %11u %08lX %08lX\n",
		sizeof(ptr->name) - 1,
		sizeof(ptr->name) - 1, ptr->name,
		ptr->data_length,
		ptr->length,
		ptr->offset,
		ptr->type_count,
		sizeof(ptr->type_spec) - 1,
		sizeof(ptr->type_spec) - 1, ptr->type_spec,
		ptr->align_count,
		ptr->dbc_type,
		ptr->user_int_1,
		ptr->user_int_2,
		((unsigned long) ptr->user_ptr_1),
		((unsigned long) ptr->user_ptr_2));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_EMIT_MemberHeader

   SYNOPSIS    :	void GEN_EMIT_MemberHeader(output_function,
							output_control);

						void (*output_function)(void *, char *, ...);

						void  *output_control;

   DESCRIPTION :	Emits a column header suitable for use with the output
						which results from the functions ``GEN_EMIT_Member``,
						``GEN_EMIT_MemberList`` and ``GEN_EMIT_MemberListIdx``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``output_function`` is a pointer to the function which
						handles output. The function should take arguments of the
						general form:

						<->``output_function``(void *, ``format_string``, ``...``);

						(-) Functions of this form include the C standard library
						function ``fprintf``. The memory-mapped library function
						``mprintf`` may also be used.

						(-) If the ``output_function`` parameter is ''NULL'', the
						function will set it to ``fprintf``.

						(.) ``output_control`` is the pointer which will be used by
						this function as the first parameter to the function
						specified by the ``output_function`` parameter.

						(-) For example, if ``output_function`` points to the
						function ``fprintf``, then ``output_control`` should be
						a pointer to a structure of type ''FILE''.

						(-) If the `` output_control`` parameter is ''NULL'', the
						function will set it to ``stdout``.

   RETURNS     :	Void.

   NOTES       :	You can emit a trailer by calling the related function
						``GEN_EMIT_MemberTrailer``.

   CAVEATS     :	

   SEE ALSO    :	GEN_EMIT_MemberTrailer

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_EMIT_MemberHeader
						Emit Functions:GEN_EMIT_MemberHeader
						General Functions:see GENFUNCS

   PUBLISH XREF:	GEN_EMIT_MemberHeader

   PUBLISH NAME:	GEN_EMIT_MemberHeader

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void GEN_EMIT_MemberHeader(STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
void GEN_EMIT_MemberHeader(output_function, output_control)
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	STR_EMIT_SetDefaults(&output_function, &output_control);

	(*output_function)(output_control,
		"%-*.*s %-10.10s %-10.10s %-10.10s %-10.10s %-*.*s %-11.11s %-11.11s \
%-11.11s %-11.11s %-8.8s %-8.8s\n",
		STR_sizeof(GEN_MEMBER, name) - 1,
		STR_sizeof(GEN_MEMBER, name) - 1, "Name",
		"Data Len",
		"Length",
		"Offset",
		"Type Count",
		STR_sizeof(GEN_MEMBER, type_spec) - 1,
		STR_sizeof(GEN_MEMBER, type_spec) - 1, "Type Spec",
		"Align Count",
		"DBC Type",
		"User Int 1",
		"User Int 2",
		"User Ptr 1",
		"User Ptr 2");
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_EMIT_MemberTrailer

   SYNOPSIS    :	void GEN_EMIT_MemberTrailer(output_function,
							output_control);

						void (*output_function)(void *, char *, ...);

						void  *output_control;

   DESCRIPTION :	Emits a column trailer suitable for use with the output
						which results from the functions ``GEN_EMIT_Member``,
						``GEN_EMIT_MemberList`` and ``GEN_EMIT_MemberListIdx``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``output_function`` is a pointer to the function which
						handles output. The function should take arguments of the
						general form:

						<->``output_function``(void *, ``format_string``, ``...``);

						(-) Functions of this form include the C standard library
						function ``fprintf``. The memory-mapped library function
						``mprintf`` may also be used.

						(-) If the ``output_function`` parameter is ''NULL'', the
						function will set it to ``fprintf``.

						(.) ``output_control`` is the pointer which will be used by
						this function as the first parameter to the function
						specified by the ``output_function`` parameter.

						(-) For example, if ``output_function`` points to the
						function ``fprintf``, then ``output_control`` should be
						a pointer to a structure of type ''FILE''.

						(-) If the `` output_control`` parameter is ''NULL'', the
						function will set it to ``stdout``.

   RETURNS     :	Void.

   NOTES       :	You can emit a header by calling the related function
						``GEN_EMIT_MemberHeader``.

   CAVEATS     :	

   SEE ALSO    :	GEN_EMIT_MemberHeader

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_EMIT_MemberTrailer
						Emit Functions:GEN_EMIT_MemberTrailer
						General Functions:see GENFUNCS

   PUBLISH XREF:	GEN_EMIT_MemberTrailer

   PUBLISH NAME:	GEN_EMIT_MemberTrailer

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void GEN_EMIT_MemberTrailer(STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
void GEN_EMIT_MemberTrailer(output_function, output_control)
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	STR_EMIT_CharSpace('-', STR_sizeof(GEN_MEMBER, name) - 1,
		output_function, output_control);
	STR_EMIT_CharSpace('-', 10, output_function, output_control);
	STR_EMIT_CharSpace('-', 10, output_function, output_control);
	STR_EMIT_CharSpace('-', 10, output_function, output_control);
	STR_EMIT_CharSpace('-', 10, output_function, output_control);
	STR_EMIT_CharSpace('-', STR_sizeof(GEN_MEMBER, type_spec) - 1,
		output_function, output_control);
	STR_EMIT_CharSpace('-', 11, output_function, output_control);
	STR_EMIT_CharSpace('-', 11, output_function, output_control);
	STR_EMIT_CharSpace('-', 11, output_function, output_control);
	STR_EMIT_CharSpace('-', 11, output_function, output_control);
	STR_EMIT_CharSpace('-',  8, output_function, output_control);
	STR_EMIT_CharLine('-',   8, output_function, output_control);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_MEMBER_GetSpecMemberList

   SYNOPSIS    :	return_code = GEN_MEMBER_GetSpecMemberList(spec_count,
							spec_list, in_member_count, in_member_list,
							out_member_count, out_member_list, error_text);

						int                return_code;

						unsigned int       spec_count;

						char             **spec_list;

						unsigned int       in_member_count;

						const GEN_MEMBER  *in_member_list;

						unsigned int      *out_member_count;

						GEN_MEMBER       **out_member_list;

						char              *error_text;

   DESCRIPTION :	Constructs a list of ''GEN_MEMBER'' structures given a
						string containing the comma-separated member names.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``spec_count`` is the number of elements in the array
						``spec_list``.

						(.) ``spec_list`` is an array of ''char'' pointers of which
						each element contains the name of a member to be used to
						construct ``out_member_list``.

						(-) Member names may be specified multiple times within
						``spec_list`` and in any order. If a member is specified
						more that once, it will appear in the array
						``out_member_list`` more than once.

						(-) Elements of ``spec_list`` which contain a zero-length
						string will be ignored by this function.

						(.) ``in_member_count`` is the number of elements in the
						array ``in_member_list``.

						(.) ``in_member_list`` is the array of ''GEN_MEMBER''
						structures which constitutes the list of members to be
						considered valid members by the program.

						(.) ``out_member_count`` is a pointer to an ''unsigned int''
						which this function will set to the number of elements in
						the array to which ``out_member_list`` points.

						(.) ``out_member_list`` is a pointer to an array of
						''GEN_MEMBER'' structures which this function will
						allocate and populate for each member specified in the
						string ``member_spec_string``.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if the function completes without
						error. ''GENFUNCS_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero GENFUNCS return codes
						indicative of error.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	GEN_MEMBER_GetSpecMemberString

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_MEMBER_GetSpecMemberList
						Member Description Functions:GEN_MEMBER_GetSpecMemberList
						General Functions:see GENFUNCS

   PUBLISH XREF:	GEN_MEMBER_GetSpecMemberList

   PUBLISH NAME:	GEN_MEMBER_GetSpecMemberList

	ENTRY CLASS	:	Member Description Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_MEMBER_GetSpecMemberList(unsigned int spec_count,
	char **spec_list, unsigned int in_member_count,
	const GEN_MEMBER *in_member_list, unsigned int *out_member_count,
	GEN_MEMBER **out_member_list, char *error_text)
#else
int GEN_MEMBER_GetSpecMemberList(spec_count, spec_list, in_member_count,
	in_member_list, out_member_count, out_member_list, error_text)
unsigned int       spec_count;
char             **spec_list;
unsigned int       in_member_count;
const GEN_MEMBER  *in_member_list;
unsigned int      *out_member_count;
GEN_MEMBER       **out_member_list;
char              *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code = GENFUNCS_SUCCESS;
	unsigned int   count_1;
	unsigned int   count_2;
	int            found_flag;

	*out_member_count = 0;
	*out_member_list  = NULL;

	for (count_1 = 0; count_1 < spec_count; count_1++) {
		if (!spec_list[count_1][0])
			continue;
		for (count_2 = 0, found_flag = GENFUNCS_FALSE;
			(count_2 < in_member_count) && (found_flag != GENFUNCS_TRUE);
			count_2++) {
			if (!strcmp(spec_list[count_1], in_member_list[count_2].name)){
				found_flag = GENFUNCS_TRUE;
				break;
			}
		}
		if (found_flag != GENFUNCS_TRUE) {
			sprintf(error_text,
				"The specified member name ('%.500s') is not valid.",
				spec_list[count_1]);
			return_code = GENFUNCS_FAILURE;
			break;
		}
		else if ((return_code = GEN_APPD_Member(in_member_list + count_2,
			out_member_count, out_member_list, error_text)) != GENFUNCS_SUCCESS)
			break;
	}

	if (return_code != GENFUNCS_SUCCESS)
		mema_remove_all(out_member_count, ((void **) out_member_list));

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_MEMBER_GetSpecMemberString

   SYNOPSIS    :	return_code = GEN_MEMBER_GetSpecMemberString(spec_string,
							in_member_count, in_member_list, out_member_count,
							out_member_list, error_text);

						int                return_code;

						const char        *spec_string;

						unsigned int       in_member_count;

						const GEN_MEMBER  *in_member_list;

						unsigned int      *out_member_count;

						GEN_MEMBER       **out_member_list;

						char              *error_text;

   DESCRIPTION :	Constructs a list of ''GEN_MEMBER'' structures given a
						string containing the comma-separated member names.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``spec_string`` is a ''char'' string which contains the
						comma-separated names of the members to be used to construct
						``out_member_list``.

						(-) Member names may be specified multiple times within
						``spec_string`` and in any order. If a member is specified
						more that once, it will appear in the array
						``out_member_list`` more than once.

						(.) ``in_member_count`` is the number of elements in the
						array ``in_member_list``.

						(.) ``in_member_list`` is the array of ''GEN_MEMBER''
						structures which constitutes the list of members to be
						considered valid members by the program.

						(.) ``out_member_count`` is a pointer to an ''unsigned int''
						which this function will set to the number of elements in
						the array to which ``out_member_list`` points.

						(.) ``out_member_list`` is a pointer to an array of
						''GEN_MEMBER'' structures which this function will
						allocate and populate for each member specified in the
						string ``spec_string``.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if the function completes without
						error. ''GENFUNCS_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero GENFUNCS return codes
						indicative of error.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	GEN_MEMBER_GetSpecMemberList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_MEMBER_GetSpecMemberString
						Member Description Functions:GEN_MEMBER_GetSpecMemberString
						General Functions:see GENFUNCS

   PUBLISH XREF:	GEN_MEMBER_GetSpecMemberString

   PUBLISH NAME:	GEN_MEMBER_GetSpecMemberString

	ENTRY CLASS	:	Member Description Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_MEMBER_GetSpecMemberString(const char *spec_string,
	unsigned int in_member_count, const GEN_MEMBER *in_member_list,
	unsigned int *out_member_count, GEN_MEMBER **out_member_list,
	char *error_text)
#else
int GEN_MEMBER_GetSpecMemberString(spec_string, in_member_count,
	in_member_list, out_member_count, out_member_list, error_text)
const char        *spec_string;
unsigned int       in_member_count;
const GEN_MEMBER  *in_member_list;
unsigned int      *out_member_count;
GEN_MEMBER       **out_member_list;
char              *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code;
	unsigned int   spec_count  = 0;
	char         **spec_list   = NULL;
	char          *tmp_string;

	*out_member_count = 0;
	*out_member_list  = NULL;

	if ((tmp_string = strdup(spec_string)) == NULL) {
		GEN_AllocMsgItem(strlen(spec_string) + 1, error_text,
			"Unable to copy the member name specification string");
		return_code = GENFUNCS_MEMORY_FAILURE;
	}
	else {
		if (sepwordx(trim(noblank(nocontrl(tmp_string))), ",", &spec_count,
			&spec_list) != STRFUNCS_SUCCESS) {
			GEN_AllocMsgPtrList(chrcnt(tmp_string, ',') + 1,
				strlen(tmp_string) + (chrcnt(tmp_string, ',') + 1), error_text,
				"Unable to allocate the member name specification list");
			return_code = GENFUNCS_MEMORY_FAILURE;
		}
		else {
			return_code = GEN_MEMBER_GetSpecMemberList(spec_count, spec_list,
				in_member_count, in_member_list, out_member_count,
				out_member_list, error_text);
			strl_remove_all(&spec_count, &spec_list);
		}
		free(tmp_string);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_MEMBER_SetDisplayName

   SYNOPSIS    :	return_code = GEN_MEMBER_SetDisplayName(member_ptr,
							display_name, error_text);

						int         return_code;

						GEN_MEMBER *member_ptr;

						const char *display_name;

						char       *error_text;

   DESCRIPTION :	Sets the ``display_name`` member of a ''GEN_MEMBER''
						structure to a specified string.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``member_ptr`` points to the ''GEN_MEMBER'' structure
						for which the ``display_name`` member is to be modified by
						this function.

						(.) ``display_name`` is the string to which this function is
						set the ``display_name`` member.

						(-) If ``display_name`` is not ''NULL'', any memory
						associated with the ``display_name`` member will be freed
						and the member will be set to the newly-allocated copy of
						the ``display_name`` parameter.

						(-) If ``display_name`` is ''NULL'', any memory associated
						with the ``display_name`` member will be freed and the
						member will be set to ''NULL''.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if the function completes without
						error. ''GENFUNCS_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero GENFUNCS return codes
						indicative of error.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	GEN_MEMBER_CreateDisplayName
						GEN_MEMBER_CreateDisplayNameList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_MEMBER_SetDisplayName
						Member Description Functions:GEN_MEMBER_SetDisplayName
						General Functions:see GENFUNCS

   PUBLISH XREF:	GEN_MEMBER_SetDisplayName

   PUBLISH NAME:	GEN_MEMBER_SetDisplayName

	ENTRY CLASS	:	Member Description Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_MEMBER_SetDisplayName(GEN_MEMBER *member_ptr, const char *display_name,
	char *error_text)
#else
int GEN_MEMBER_SetDisplayName(member_ptr, display_name, error_text)
GEN_MEMBER *member_ptr;
const char *display_name;
char       *error_text;
#endif /* #ifndef NARGS */
{
	int   return_code = GENFUNCS_SUCCESS;
	char *tmp_ptr     = NULL;

	if ((display_name == NULL) || ((tmp_ptr = strdup(display_name)) != NULL)) {
		if (member_ptr->display_name != NULL)
			free(member_ptr->display_name);
		member_ptr->display_name = tmp_ptr;
	}
	else if (display_name != NULL) {
		GEN_AllocMsgItem(strlen(display_name) + 1, error_text,
			"Unable to allocate for a 'GEN_MEMBER' display name");
		return_code = GENFUNCS_MEMORY_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_MEMBER_CreateDisplayNameList

   SYNOPSIS    :	return_code = GEN_MEMBER_CreateDisplayNameList(member_count,
							member_list, error_text);

						int           return_code;

						unsigned int  member_count;

						GEN_MEMBER   *member_ptr;

						char         *error_text;

   DESCRIPTION :	Initializes the ``display_name`` members of a list of
						''GEN_MEMBER'' structures to a string derived from the
						``name`` members of the structures in the list.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``member_count`` is the number of elements in the
						array ``member_list``.

						(.) ``member_list`` is the array of ''GEN_MEMBER''
						structures for which the ``display_name`` member is to be
						initialized by this function.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if the function completes without
						error. ''GENFUNCS_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero GENFUNCS return codes
						indicative of error.

   NOTES       :	This function creates the ``display_member`` from the
						``name`` member by doing the following:

						(+) A copy is made of the string in the ``name`` member.

						(+) All underscores (''_'') in the copied ``name`` member
						are replaced by spaces.

						(+) Multiple spaces in the copied ``name`` member are
						replaced by a single space.

						(+) Leading and trailing spaces the copied ``name`` member
						are removed.

						(+) The initial character of each word in the copied
						``name`` member (where ``word``s are separated by a space
						character) is mapped to upper-case. All other characters are
						mapped to lower-case.

						(+) The resulting string is assigned to the ``display_name``
						member.

   CAVEATS     :	

   SEE ALSO    :	GEN_MEMBER_CreateDisplayName

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_MEMBER_CreateDisplayNameList
						Member Description Functions:GEN_MEMBER_CreateDisplayNameList
						General Functions:see GENFUNCS

   PUBLISH XREF:	GEN_MEMBER_CreateDisplayNameList

   PUBLISH NAME:	GEN_MEMBER_CreateDisplayNameList

	ENTRY CLASS	:	Member Description Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_MEMBER_CreateDisplayNameList(unsigned int member_count,
	GEN_MEMBER *member_list, char *error_text)
#else
int GEN_MEMBER_CreateDisplayNameList(member_count, member_list, error_text)
unsigned int  member_count;
GEN_MEMBER   *member_list;
char         *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = GENFUNCS_SUCCESS;

	for ( ; member_count ; member_count--, member_list++) {
		if ((return_code = GEN_MEMBER_CreateDisplayName(member_list,
			error_text)) != GENFUNCS_SUCCESS)
			break;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_MEMBER_CreateDisplayName

   SYNOPSIS    :	return_code = GEN_MEMBER_CreateDisplayName(member_ptr,
							error_text);

						int         return_code;

						GEN_MEMBER *member_ptr;

						char       *error_text;

   DESCRIPTION :	Initializes the ``display_name`` member of a ''GEN_MEMBER''
						structure to a string derived from the ``name`` member of
						the structure.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``member_ptr`` points to to ''GEN_MEMBER'' structure
						for which the ``display_name`` member is to be initialized
						by this function.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if the function completes without
						error. ''GENFUNCS_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero GENFUNCS return codes
						indicative of error.

   NOTES       :	This function creates the ``display_member`` from the
						``name`` member by doing the following:

						(+) A copy is made of the string in the ``name`` member.

						(+) All underscores (''_'') in the copied ``name`` member
						are replaced by spaces.

						(+) Multiple spaces in the copied ``name`` member are
						replaced by a single space.

						(+) Leading and trailing spaces the copied ``name`` member
						are removed.

						(+) The initial character of each word in the copied
						``name`` member (where ``word``s are separated by a space
						character) is mapped to upper-case. All other characters are
						mapped to lower-case.

						(+) The resulting string is assigned to the ``display_name``
						member.

   CAVEATS     :	

   SEE ALSO    :	GEN_MEMBER_CreateDisplayNameList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_MEMBER_CreateDisplayName
						Member Description Functions:GEN_MEMBER_CreateDisplayName
						General Functions:see GENFUNCS

   PUBLISH XREF:	GEN_MEMBER_CreateDisplayName

   PUBLISH NAME:	GEN_MEMBER_CreateDisplayName

	ENTRY CLASS	:	Member Description Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_MEMBER_CreateDisplayName(GEN_MEMBER *member_ptr, char *error_text)
#else
int GEN_MEMBER_CreateDisplayName(member_ptr, error_text)
GEN_MEMBER *member_ptr;
char       *error_text;
#endif /* #ifndef NARGS */
{
	char *tmp_ptr;
	char  display_name[sizeof(member_ptr->name)];

	nstrcpy(display_name, member_ptr->name, sizeof(display_name) - 1);

	while ((tmp_ptr = strchr(trim(oneblank(display_name)), '_')) != NULL)
		*tmp_ptr = ' ';

	return(GEN_MEMBER_SetDisplayName(member_ptr, initcaps(display_name),
		error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_MEMBER_FixAlignArrayList

   SYNOPSIS    :	return_code = GEN_MEMBER_FixAlignArrayList(type_count,
							type_list, member_count, member_list, structure_size,
							error_text);

						int                   return_code;

						unsigned int          type_count;

						const GEN_ALIGN_SPEC *type_list;

						unsigned int           member_count;

						GEN_MEMBER            *member_list;

						unsigned int          *structure_size;

						char                  *error_text;

   DESCRIPTION :	Initializes the ``align_count`` and ``align_list`` members
						of a list of ''GEN_MEMBER'' structures to values determined
						from the ``type_count`` and ``type_spec`` members. The
						``offset`` member is also re-calculated for each element
						in the list.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``type_count`` is the number of elements in the array
						represented by the ``type_list`` parameter.

						(.) ``type_list`` is an array of ''GEN_ALIGN_SPEC''
						structures which describe a machine architecture in terms
						of the primitive data types available on that architecture.

						(-) If ``type_count`` is ''0'' and ``type_list`` is
						''NULL'', the function will use the built-in primitive
						data type list compiled into the module ``genalign.c``
						under the names ``GEN_ALIGN_TypeCount`` and
						``GEN_ALIGN_TypeList``.

						(.) ``member_count`` is the number of elements in the
						array ``member_list``.

						(.) ``member_list`` is the array of ''GEN_MEMBER''
						structures for which the align array data is to be
						calculated.

						(.) ``structure_size`` is a pointer to an ''unsigned int''
						into which will be placed the total size of the structure
						as determined by this function. The size will include
						any alignment bytes required by the implementation.

						(-) If ``structure_size`` is ''NULL'', it will not be
						de-referenced.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if the function completes without
						error. ''GENFUNCS_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero GENFUNCS return codes
						indicative of error.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	GEN_MEMBER_SetAlignArrayList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_MEMBER_FixAlignArrayList
						Member Description Functions:GEN_MEMBER_FixAlignArrayList
						General Functions:see GENFUNCS

   PUBLISH XREF:	GEN_MEMBER_FixAlignArrayList

   PUBLISH NAME:	GEN_MEMBER_FixAlignArrayList

	ENTRY CLASS	:	Member Description Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_MEMBER_FixAlignArrayList(unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, unsigned int member_count,
	GEN_MEMBER *member_list, unsigned int *structure_size, char *error_text)
#else
int GEN_MEMBER_FixAlignArrayList(type_count, type_list, member_count,
	member_list, structure_size, error_text)
unsigned int          type_count;
const GEN_ALIGN_SPEC *type_list;
unsigned int          member_count;
GEN_MEMBER           *member_list;
unsigned int         *structure_size;
char                 *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code = GENFUNCS_SUCCESS;
	unsigned int  align_count = 0;
	GEN_ALIGN    *align_list;
	unsigned int  count_1;
	unsigned int  count_2;

	if (member_count && ((return_code =
		GEN_MEMBER_SetAlignArrayList(type_count, type_list, member_count,
		member_list, error_text)) == GENFUNCS_SUCCESS)) {
		for (count_1 = 0; count_1 < member_count; count_1++)
			align_count += member_list[count_1].align_count;
		if ((align_list = ((GEN_ALIGN *) calloc(align_count,
			sizeof(GEN_ALIGN)))) == NULL) {
			GEN_AllocMsgList(align_count, sizeof(GEN_ALIGN), error_text,
				"Unable to allocate temporary 'GEN_ALIGN' list");
			return_code = GENFUNCS_MEMORY_FAILURE;
		}
		else {
			align_count = 0;
			for (count_1 = 0; count_1 < member_count; count_1++) {
				for (count_2 = 0; count_2 < member_list[count_1].align_count;
					count_2++)
					align_list[align_count++] =
						member_list[count_1].align_list[count_2];
			}
			if ((return_code = GEN_ALIGN_BASIC_AlignList(type_count, type_list,
				structure_size, align_count, align_list, error_text)) ==
				GENFUNCS_SUCCESS) {
				align_count = 0;
				for (count_1 = 0; count_1 < member_count; count_1++) {
					member_list[count_1].offset = align_list[align_count].offset;
					for (count_2 = 0; count_2 < member_list[count_1].align_count;
						count_2++)
						member_list[count_1].align_list[count_2] =
							align_list[align_count++];
				}
			}
			free(align_list);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_MEMBER_SetAlignArrayList

   SYNOPSIS    :	return_code = GEN_MEMBER_SetAlignArrayList(type_count,
							type_list, member_count, member_list, error_text);

						int                   return_code;

						unsigned int          type_count;

						const GEN_ALIGN_SPEC *type_list;

						unsigned int           member_count;

						GEN_MEMBER            *member_list;

						char                  *error_text;

   DESCRIPTION :	Initializes the ``align_count`` and ``align_list`` members
						of a list of ''GEN_MEMBER'' structures to values determined
						from the ``type_count`` and ``type_spec`` members.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``type_count`` is the number of elements in the array
						represented by the ``type_list`` parameter.

						(.) ``type_list`` is an array of ''GEN_ALIGN_SPEC''
						structures which describe a machine architecture in terms
						of the primitive data types available on that architecture.

						(-) If ``type_count`` is ''0'' and ``type_list`` is
						''NULL'', the function will use the built-in primitive
						data type list compiled into the module ``genalign.c``
						under the names ``GEN_ALIGN_TypeCount`` and
						``GEN_ALIGN_TypeList``.

						(.) ``member_count`` is the number of elements in the
						array ``member_list``.

						(.) ``member_list`` is the array of ''GEN_MEMBER''
						structures for which the align array data is to be
						calculated.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if the function completes without
						error. ''GENFUNCS_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero GENFUNCS return codes
						indicative of error.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	GEN_MEMBER_SetAlignArray
						GEN_MEMBER_FixAlignArrayList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_MEMBER_SetAlignArrayList
						Member Description Functions:GEN_MEMBER_SetAlignArrayList
						General Functions:see GENFUNCS

   PUBLISH XREF:	GEN_MEMBER_SetAlignArrayList

   PUBLISH NAME:	GEN_MEMBER_SetAlignArrayList

	ENTRY CLASS	:	Member Description Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_MEMBER_SetAlignArrayList(unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, unsigned int member_count,
	GEN_MEMBER *member_list, char *error_text)
#else
int GEN_MEMBER_SetAlignArrayList(type_count, type_list, member_count,
	member_list, error_text)
unsigned int          type_count;
const GEN_ALIGN_SPEC *type_list;
unsigned int          member_count;
GEN_MEMBER           *member_list;
char                 *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = GENFUNCS_SUCCESS;

	for ( ; member_count ; member_count--, member_list++) {
		if ((return_code = GEN_MEMBER_SetAlignArray(type_count, type_list,
			member_list, error_text)) != GENFUNCS_SUCCESS)
			break;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_MEMBER_SetAlignArray

   SYNOPSIS    :	return_code = GEN_MEMBER_SetAlignArray(type_count,
							type_list, member_ptr, error_text);

						int                   return_code;

						unsigned int          type_count;

						const GEN_ALIGN_SPEC *type_list;

						GEN_MEMBER            *member_ptr;

						char                  *error_text;

   DESCRIPTION :	Initializes the ``align_count`` and ``align_list`` members
						of a ''GEN_MEMBER'' structure to values determined from the
						``type_count`` and ``type_spec`` members.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``type_count`` is the number of elements in the array
						represented by the ``type_list`` parameter.

						(.) ``type_list`` is an array of ''GEN_ALIGN_SPEC''
						structures which describe a machine architecture in terms
						of the primitive data types available on that architecture.

						(-) If ``type_count`` is ''0'' and ``type_list`` is
						''NULL'', the function will use the built-in primitive
						data type list compiled into the module ``genalign.c``
						under the names ``GEN_ALIGN_TypeCount`` and
						``GEN_ALIGN_TypeList``.

						(.) ``member_ptr`` is the ''GEN_MEMBER'' structure for which
						the align array data is to be calculated.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if the function completes without
						error. ''GENFUNCS_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero GENFUNCS return codes
						indicative of error.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	GEN_MEMBER_SetAlignArrayList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_MEMBER_SetAlignArray
						Member Description Functions:GEN_MEMBER_SetAlignArray
						General Functions:see GENFUNCS

   PUBLISH XREF:	GEN_MEMBER_SetAlignArray

   PUBLISH NAME:	GEN_MEMBER_SetAlignArray

	ENTRY CLASS	:	Member Description Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_MEMBER_SetAlignArray(unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, GEN_MEMBER *member_ptr, char *error_text)
#else
int GEN_MEMBER_SetAlignArray(type_count, type_list, member_ptr, error_text)
unsigned int          type_count;
const GEN_ALIGN_SPEC *type_list;
GEN_MEMBER           *member_ptr;
char                 *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code;
	unsigned int  count_1;
	unsigned int  align_count;
	GEN_ALIGN    *align_list;

	if ((return_code = GEN_ALIGN_BASIC_CountStringToList(type_count, type_list,
		GENFUNCS_FALSE, GENFUNCS_TRUE, ",", member_ptr->type_count,
		member_ptr->type_spec, NULL, &align_count, &align_list, error_text)) ==
		GENFUNCS_SUCCESS) {
		if (align_count <= GEN_MEMBER_MAX_ALIGN_COUNT) {
			member_ptr->align_count = align_count;
			for (count_1 = 0; count_1 < align_count; count_1++) {
				member_ptr->align_list[count_1]         = align_list[count_1];
				member_ptr->align_list[count_1].offset += member_ptr->offset;
			}
			free(align_list);
		}
		else {
			free(align_list);
			sprintf(error_text,
				"%s '%-.*s' (type count=%u, type spec='%-.*s') (%u) %s (%u).",
				"The number of align elements returned for 'GEN_MEMBER'",
				((int) (sizeof(member_ptr->name) - 1)), member_ptr->name,
				member_ptr->type_count,
				((int) (sizeof(member_ptr->type_spec) - 1)), member_ptr->type_spec,
				align_count, "exceeds the maximum permissible",
				GEN_MEMBER_MAX_ALIGN_COUNT);
			return_code = GENFUNCS_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_MEMBER_SetDisplayLengthList

   SYNOPSIS    :	return_code = GEN_MEMBER_SetDisplayLengthList(type_count,
							type_list, member_count, member_list, header_flag,
							null_string_length, intra_field_sep_length,
							user_data_ptr, error_text);

						int                   return_code;

						unsigned int          type_count;

						const GEN_ALIGN_SPEC *type_list;

						unsigned int           member_count;

						GEN_MEMBER            *member_list;

						int                   header_flag;

						unsigned int          null_string_length;

						unsigned int          intra_field_sep_length;

						void                 *user_data_ptr;

						char                  *error_text;

   DESCRIPTION :	Initializes the ``display_length`` members of a list of
						''GEN_MEMBER'' structures.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``type_count`` is the number of elements in the array
						represented by the ``type_list`` parameter.

						(.) ``type_list`` is an array of ''GEN_ALIGN_SPEC''
						structures which describe a machine architecture in terms
						of the primitive data types available on that architecture.

						(-) If ``type_count`` is ''0'' and ``type_list`` is
						''NULL'', the function will use the built-in primitive
						data type list compiled into the module ``genalign.c``
						under the names ``GEN_ALIGN_TypeCount`` and
						``GEN_ALIGN_TypeList``.

						(.) ``member_count`` is the number of elements in the
						array ``member_list``.

						(.) ``member_list`` is the array of ''GEN_MEMBER''
						structures for which the ``display_length`` member is to be
						calculated.

						(.) ``header_flag`` indicates whether the length of the
						name of the member is to be used as the minimum length of
						the member.

						(-) If ``header_flag`` is not zero, then this function will
						consider the maximum length of the ``display_name`` member
						and the ``name`` member to be the minimum length of the
						member.

						(.) ``null_string_length`` is the length of the string to be
						used to indicate that a member of a record contains a
						''NULL'' value.

						(-) If ``null_string_length`` is greater than ''0'', it will
						be considered by this function to be the minimum length of
						the member.

						(.) ``intra_field_sep_length`` is the length of the string
						to be used to separate the elements of fields which have an
						array data type or which are comprised of more than one
						primitive data type.

						(.) ``user_data_ptr`` is a pointer to ''void'' which the
						application programmer may use in order to attach
						application-specific knowledge to the structure.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if the function completes without
						error. ''GENFUNCS_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero GENFUNCS return codes
						indicative of error.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	GEN_MEMBER_SetDisplayLength

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_MEMBER_SetDisplayLengthList
						Member Description Functions:GEN_MEMBER_SetDisplayLengthList
						General Functions:see GENFUNCS

   PUBLISH XREF:	GEN_MEMBER_SetDisplayLengthList

   PUBLISH NAME:	GEN_MEMBER_SetDisplayLengthList

	ENTRY CLASS	:	Member Description Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_MEMBER_SetDisplayLengthList(unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, unsigned int member_count,
	GEN_MEMBER *member_list, int header_flag,
	unsigned int null_string_length, unsigned int intra_field_sep_length,
	void *user_data_ptr, char *error_text)
#else
int GEN_MEMBER_SetDisplayLengthList(type_count, type_list, member_count,
	member_list, header_flag, null_string_length, intra_field_sep_length,
	user_data_ptr, error_text)
unsigned int          type_count;
const GEN_ALIGN_SPEC *type_list;
unsigned int          member_count;
GEN_MEMBER           *member_list;
int                   header_flag;
unsigned int          null_string_length;
unsigned int          intra_field_sep_length;
void                 *user_data_ptr;
char                 *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = GENFUNCS_SUCCESS;

	for ( ; member_count ; member_count--, member_list++) {
		if ((return_code = GEN_MEMBER_SetDisplayLength(type_count, type_list,
			member_list, header_flag, null_string_length, intra_field_sep_length,
			user_data_ptr, error_text)) != GENFUNCS_SUCCESS)
			break;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_MEMBER_SetDisplayLength

   SYNOPSIS    :	return_code = GEN_MEMBER_SetDisplayLength(type_count,
							type_list, member_ptr, header_flag, null_string_length,
							intra_field_sep_length, user_data_ptr, error_text);

						int                   return_code;

						unsigned int          type_count;

						const GEN_ALIGN_SPEC *type_list;

						GEN_MEMBER            *member_ptr;

						int                   header_flag;

						unsigned int          null_string_length;

						unsigned int          intra_field_sep_length;

						void                 *user_data_ptr;

						char                  *error_text;

   DESCRIPTION :	Initializes the ``display_length`` member of a
						''GEN_MEMBER'' structure.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``type_count`` is the number of elements in the array
						represented by the ``type_list`` parameter.

						(.) ``type_list`` is an array of ''GEN_ALIGN_SPEC''
						structures which describe a machine architecture in terms
						of the primitive data types available on that architecture.

						(-) If ``type_count`` is ''0'' and ``type_list`` is
						''NULL'', the function will use the built-in primitive
						data type list compiled into the module ``genalign.c``
						under the names ``GEN_ALIGN_TypeCount`` and
						``GEN_ALIGN_TypeList``.

						(.) ``member_ptr`` is the ''GEN_MEMBER'' structure for which
						the ``display_length`` member is to be calculated.

						(.) ``header_flag`` indicates whether the length of the
						name of the member is to be used as the minimum length of
						the member.

						(-) If ``header_flag`` is not zero, then this function will
						consider the maximum length of the ``display_name`` member
						and the ``name`` member to be the minimum length of the
						member.

						(.) ``null_string_length`` is the length of the string to be
						used to indicate that a member of a record contains a
						''NULL'' value.

						(-) If ``null_string_length`` is greater than ''0'', it will
						be considered by this function to be the minimum length of
						the member.

						(.) ``intra_field_sep_length`` is the length of the string
						to be used to separate the elements of fields which have an
						array data type or which are comprised of more than one
						primitive data type.

						(.) ``user_data_ptr`` is a pointer to ''void'' which the
						application programmer may use in order to attach
						application-specific knowledge to the structure.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	Returns from this function are as follow:

						(.) ''GENFUNCS_SUCCESS'' if the function completes without
						error. ''GENFUNCS_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero GENFUNCS return codes
						indicative of error.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	GEN_MEMBER_SetDisplayLengthList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_MEMBER_SetDisplayLength
						Member Description Functions:GEN_MEMBER_SetDisplayLength
						General Functions:see GENFUNCS

   PUBLISH XREF:	GEN_MEMBER_SetDisplayLength

   PUBLISH NAME:	GEN_MEMBER_SetDisplayLength

	ENTRY CLASS	:	Member Description Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_MEMBER_SetDisplayLength(unsigned int type_count,
	const GEN_ALIGN_SPEC *type_list, GEN_MEMBER *member_ptr, int header_flag,
	unsigned int null_string_length, unsigned int intra_field_sep_length,
	void *user_data_ptr, char *error_text)
#else
int GEN_MEMBER_SetDisplayLength(type_count, type_list, member_ptr,
	header_flag, null_string_length, intra_field_sep_length, user_data_ptr,
	error_text)
unsigned int          type_count;
const GEN_ALIGN_SPEC *type_list;
GEN_MEMBER           *member_ptr;
int                   header_flag;
unsigned int          null_string_length;
unsigned int          intra_field_sep_length;
void                 *user_data_ptr;
char                 *error_text;
#endif /* #ifndef NARGS */
{
	int              return_code = GENFUNCS_SUCCESS;
	unsigned int     this_length = 0;
	unsigned int     count_1;
	const GEN_ALIGN *align_ptr;

	if ((!type_count) && (type_list == NULL)) {
		type_count = GEN_ALIGN_TypeCount;
		type_list  = GEN_ALIGN_TypeList;
	}

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		This member may have its own length function . . .					*/
	/*	*****************************************************************	*/
	if ((member_ptr->length_function != NULL) &&
		(member_ptr->length_function != GEN_MEMBER_SetDisplayLength)) {
		return_code = (*member_ptr->length_function)(type_count, type_list,
			member_ptr, header_flag, null_string_length, intra_field_sep_length,
			user_data_ptr, error_text);
		this_length = member_ptr->display_length;
	}
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Otherwise, we determine the length based upon the primitive		*/
	/*	types which comprise the member . . .										*/
	/*	*****************************************************************	*/
	else {
		for (count_1 = 0, align_ptr = member_ptr->align_list;
			(count_1 < member_ptr->align_count) &&
			(return_code == GENFUNCS_SUCCESS); count_1++, align_ptr++) {
			this_length += (count_1) ? intra_field_sep_length : 0;
			if (align_ptr->type >= type_count) {
				sprintf(error_text,
					"%s (index = %u, name = '%s', type = %u, spec = '%s').",
					"Invalid type number in 'GEN_MEMBER' structure", count_1,
					member_ptr->name, align_ptr->type, member_ptr->type_spec);
				return_code = GENFUNCS_FAILURE;
				break;
			}
			switch (align_ptr->type) {
				case GEN_C_ALIGN_unsigned_byte	:
					this_length += 2 + (align_ptr->array_length * 2);
					break;
				case GEN_C_ALIGN_char				:
				case GEN_C_ALIGN_unsigned_char	:
					this_length += (align_ptr->array_length - 1);
					break;
				case GEN_C_ALIGN_short				:
				case GEN_C_ALIGN_unsigned_short	:
				case GEN_C_ALIGN_int					:
				case GEN_C_ALIGN_unsigned_int		:
				case GEN_C_ALIGN_long				:
				case GEN_C_ALIGN_unsigned_long	:
				case GEN_C_ALIGN_float				:
				case GEN_C_ALIGN_double				:
					this_length += (align_ptr->array_length *
						type_list[align_ptr->type].printf_length) +
						((align_ptr->array_length - 1) * intra_field_sep_length);
					break;
				default									:
					sprintf(error_text,
						"%s %s (index = %u, name = '%s', type = %u, spec = '%s').",
						"Error occurred while determining the length of a",
						"'GEN_MEMBER' structure", count_1, member_ptr->name,
						align_ptr->type, member_ptr->type_spec);
					return_code = GENFUNCS_FAILURE;
					break;
			}
		}
	}

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		We may need to adjust the field width:									*/
	/*																							*/
	/*		1)	If the length of the NULL string indicator is greater			*/
	/*			than the calculated length of the member.							*/
	/*																							*/
	/*		2) If headers are to be used and the length of the member		*/
	/*			name is greater than than the calculated length of the		*/
	/*			member.																		*/
	/*																							*/
	/*		3)	If headers are to be used and a display name has been			*/
	/*			specified for the member which is longer than the				*/
	/*			calculated length of the member.										*/
	/*	*****************************************************************	*/
	if (return_code == GENFUNCS_SUCCESS) {
		this_length = (this_length >= null_string_length) ? this_length :
			null_string_length;
		if (header_flag) {
			this_length = (this_length >= strlen(member_ptr->name)) ?
				this_length : strlen(member_ptr->name);
			this_length = ((member_ptr->display_name == NULL) ||
				(this_length >= strlen(member_ptr->display_name))) ?
				this_length : strlen(member_ptr->display_name);
		}
		member_ptr->display_length = this_length;
	}
	/*	*****************************************************************	*/

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

static const GEN_MEMBER   TEST_List[] = {
	{
		"name",
		STR_sizeof(GEN_MEMBER, name) - 1,
		STR_sizeof(GEN_MEMBER, name),
		offsetof(GEN_MEMBER, name),
		STR_sizeof(GEN_MEMBER, name) - 1,
		"c",
		0,
		GEN_MEMBER_ALIGN_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
	{
		"data_length",
		STR_sizeof(GEN_MEMBER, data_length),
		STR_sizeof(GEN_MEMBER, data_length),
		offsetof(GEN_MEMBER, data_length),
		1,
		"I",
		0,
		GEN_MEMBER_ALIGN_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
	{
		"length",
		STR_sizeof(GEN_MEMBER, length),
		STR_sizeof(GEN_MEMBER, length),
		offsetof(GEN_MEMBER, length),
		1,
		"I",
		0,
		GEN_MEMBER_ALIGN_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
	{
		"offset",
		STR_sizeof(GEN_MEMBER, offset),
		STR_sizeof(GEN_MEMBER, offset),
		offsetof(GEN_MEMBER, offset),
		1,
		"I",
		0,
		GEN_MEMBER_ALIGN_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
	{
		"type_count",
		STR_sizeof(GEN_MEMBER, type_count),
		STR_sizeof(GEN_MEMBER, type_count),
		offsetof(GEN_MEMBER, type_count),
		1,
		"I",
		0,
		GEN_MEMBER_ALIGN_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
	{
		"type_spec",
		STR_sizeof(GEN_MEMBER, type_spec) - 1,
		STR_sizeof(GEN_MEMBER, type_spec),
		offsetof(GEN_MEMBER, type_spec),
		STR_sizeof(GEN_MEMBER, type_spec) - 1,
		"c",
		0,
		GEN_MEMBER_ALIGN_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
	{
		"align_count",
		STR_sizeof(GEN_MEMBER, align_count),
		STR_sizeof(GEN_MEMBER, align_count),
		offsetof(GEN_MEMBER, align_count),
		1,
		"I",
		0,
		GEN_MEMBER_ALIGN_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
/*
	{
		"align_list",
		STR_sizeof(GEN_MEMBER, align_list),
		STR_sizeof(GEN_MEMBER, align_list),
		offsetof(GEN_MEMBER, align_list),
		GEN_MEMBER_MAX_ALIGN_COUNT,
		"I[4]",
		0,
		GEN_MEMBER_ALIGN_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
*/
	{
		"display_length",
		STR_sizeof(GEN_MEMBER, display_length),
		STR_sizeof(GEN_MEMBER, display_length),
		offsetof(GEN_MEMBER, display_length),
		1,
		"I",
		0,
		GEN_MEMBER_ALIGN_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
/*
	{
		"display_name",
		STR_sizeof(GEN_MEMBER, display_name),
		STR_sizeof(GEN_MEMBER, display_name),
		offsetof(GEN_MEMBER, display_name),
		STR_sizeof(GEN_MEMBER, display_name),
		"B",
		0,
		GEN_MEMBER_ALIGN_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
*/
	{
		"dbc_type",
		STR_sizeof(GEN_MEMBER, dbc_type),
		STR_sizeof(GEN_MEMBER, dbc_type),
		offsetof(GEN_MEMBER, dbc_type),
		1,
		"i",
		0,
		GEN_MEMBER_ALIGN_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
	{
		"length_function",
		STR_sizeof(GEN_MEMBER, length_function),
		STR_sizeof(GEN_MEMBER, length_function),
		offsetof(GEN_MEMBER, length_function),
		STR_sizeof(GEN_MEMBER, length_function),
		"B",
		0,
		GEN_MEMBER_ALIGN_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
	{
		"dump_function",
		STR_sizeof(GEN_MEMBER, dump_function),
		STR_sizeof(GEN_MEMBER, dump_function),
		offsetof(GEN_MEMBER, dump_function),
		STR_sizeof(GEN_MEMBER, dump_function),
		"B",
		0,
		GEN_MEMBER_ALIGN_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
	{
		"user_int_1",
		STR_sizeof(GEN_MEMBER, user_int_1),
		STR_sizeof(GEN_MEMBER, user_int_1),
		offsetof(GEN_MEMBER, user_int_1),
		1,
		"i",
		0,
		GEN_MEMBER_ALIGN_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
	{
		"user_int_2",
		STR_sizeof(GEN_MEMBER, user_int_2),
		STR_sizeof(GEN_MEMBER, user_int_2),
		offsetof(GEN_MEMBER, user_int_2),
		1,
		"i",
		0,
		GEN_MEMBER_ALIGN_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
	{
		"user_ptr_1",
		STR_sizeof(GEN_MEMBER, user_ptr_1),
		STR_sizeof(GEN_MEMBER, user_ptr_1),
		offsetof(GEN_MEMBER, user_ptr_1),
		STR_sizeof(GEN_MEMBER, user_ptr_1),
		"B",
		0,
		GEN_MEMBER_ALIGN_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
	{
		"user_ptr_2",
		STR_sizeof(GEN_MEMBER, user_ptr_2),
		STR_sizeof(GEN_MEMBER, user_ptr_2),
		offsetof(GEN_MEMBER, user_ptr_2),
		STR_sizeof(GEN_MEMBER, user_ptr_2),
		"B",
		0,
		GEN_MEMBER_ALIGN_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	}
};

static const unsigned int TEST_Count  =
	sizeof(TEST_List) / sizeof(TEST_List[0]);

COMPAT_FN_DECL(int main, (void));

int main()
{
	int           return_code;
	unsigned int  member_count = 0;
	GEN_MEMBER   *member_list  = NULL;
	char          error_text[GENFUNCS_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'GEN_MEMBER' Functions\n");
	fprintf(stderr, "---- ------- --- ------------ ---------\n\n");

	if ((return_code = GEN_COPY_MemberList(TEST_Count, TEST_List,
		&member_count, &member_list, error_text)) != GENFUNCS_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = GEN_MEMBER_SetAlignArrayList(0, NULL, member_count,
		member_list, error_text)) != GENFUNCS_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = GEN_MEMBER_CreateDisplayNameList(member_count,
		member_list, error_text)) != GENFUNCS_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = GEN_MEMBER_SetDisplayLengthList(0, NULL, member_count,
		member_list, GENFUNCS_TRUE, strlen("*NULL*"), strlen("-"), NULL,
		error_text)) != GENFUNCS_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = GEN_MEMBER_DMP_DumpText(0, NULL, member_count,
		member_list, member_count, ((const char *) member_list),
		sizeof(*member_list), GENFUNCS_TRUE, GENFUNCS_FALSE, GENFUNCS_TRUE, 0,
		64, "*NULL*", " ", "-", "*", "\f", NULL, "\n", NULL, NULL, NULL, NULL,
		NULL, NULL, NULL, error_text)) != GENFUNCS_SUCCESS)
		goto EXIT_FUNCTION;

	STR_EMIT_CharLine('=', 78, NULL, NULL);

EXIT_FUNCTION:

	GEN_FREE_MemberList(&member_count, &member_list);

	if (return_code != GENFUNCS_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

