/* *********************************************************************** */
/* *********************************************************************** */
/*	Data Type Alignment (DTA) Functions Library Source Module					*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Transforms a array of string descriptors into an
								array of 'DTA' structures.

	Revision History	:	1992-02-23 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Include necessary header files . . .											*/
/* *********************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dtai.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  DTA_BASIC_AlignStringList

   SYNOPSIS    :  return_code = DTA_BASIC_AlignStringList(type_count,
							type_list, normalize_flag, adjust_char_flag,
							separator_list, spec_count, spec_list, count_list,
							index_list, size_list, structure_size, align_count,
							align_list, error_text);

						int              return_code;

						unsigned int     type_count;

						const DTA_TYPE  *type_list;

						int              normalize_flag;

						int              adjust_char_flag;

						const char      *separator_list;

						unsigned int     spec_count;

						char           **spec_list;

						unsigned int   **count_list;

						unsigned int   **index_list;

						unsigned int   **size_list;

						unsigned int    *structure_size;

						unsigned int    *align_count;

						DTA            **align_list;

						char            *error_text;

   DESCRIPTION :	Transforms an array of pointers to string specifications of
						the primitive type members of a structure into an array of
						structures of type ''DTA'', the elements of which
						contain offset and length data for each member.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``type_count`` is the number of elements in the array
						represented by the ``type_list`` parameter.

						(.) ``type_list`` is an array of ''DTA_TYPE''
						structures which describe a machine architecture in terms
						of the primitive data types available on that architecture.

						(-) If ``type_count`` is ''0'' and ``type_list`` is
						''NULL'', the function will use the built-in primitive
						data type list compiled into the module ``dtadata.c``
						under the names ``DTA_TypeCount`` and ``DTA_TypeList``.

						(.) ``normalize_flag`` indicates whether the elements of
						the array ``align_list`` which results the operation of
						this function are to be normalized vis-a-vis each other.

						(-) Normalization is the combination of like data types from
						adjacent ``align_list`` elements into a single element.

						(-) For example, if ``align_list`` contains the adjacent
						elements resulting from operation of this function on the
						string:

{|-|}c[10],c[3]

						(-) Normalization of those elements will result in a single
						element equivalent to the string:

{|-|}c[13]

						(-) The ``normalize_flag`` parameter may take on one of the
						following two values:

						(..) ``DTA_TRUE``, which indicates that the elements
						are to be normalized.

						(..) ``DTA_FALSE``, which indicates that the elements
						are not to be normalized.

						(.) ``adjust_char_flag`` specifies that ''char'' (and
						''unsigned char'') arrays are to be increased in length
						by a single byte. This is usually to accomodate the
						inclusion of the ''C'' language string null terminator byte.

						(-) The ``adjust_char_flag`` parameter may take on one of
						the following two values:

						(..) ``DTA_TRUE``, which indicates that ''char''
						elements are to be adjusted.

						(..) ``DTA_FALSE``, which indicates that ''char''
						elements are not to be adjusted.

						(.) ``separator_list`` is an ASCII NUL (ASCII 0) terminated
						string which lists the characters to be used to separate
						discrete specifications in the elements of ``spec_list``.

						(-) if ``separator_list`` is ''NULL'', the comma character
						('','') will be used to separate specifications in
						the elements of ``spec_list``.

						(.) ``spec_count`` is the number of elements in the
						array ``spec_list``.

						(.) ``spec_list`` is a array of pointers to strings, each
						string of which is a primitive type specification having
						the following format:

						(--) { ''b''|''c''|''C''|''s''|''S''|''i''|''I''|''l''|''L''|''f''|''d'' }

						(-) where each letter has the following meaning:

						(..)''b'' is an unsigned (binary) char. The upper-case
						letter ''B'' is also allowed.

						(..)''c'' is a signed char.

						(..)''C'' is an unsigned char.

						(..)''s'' is a signed short integer.

						(..)''S'' is an unsigned short integer.

						(..)''i'' is a signed integer.

						(..)''I'' is an unsigned integer.

						(..)''l'' is a long integer.

						(..)''L'' is an unsigned long integer

						(..)''f'' is a float. The upper-case letter ''F'' is also
						allowed.

						(..)''d'' is a double. The upper-case letter ''D'' is also
						allowed.

						(-) A member definition may be followed by an optional
						array specifier of the form:

						(--) ``member-definition``[``array-length``]

						(-) Note that ``array-length`` must be greater than zero.

						(.) ``count_list`` is a pointer to an ''unsigned int'' into
						which this function will place a pointer to memory allocated
						to hold an array of ''unsigned int''s. Each element of the
						array will correspond to an element in the array
						``spec_list``, so the total number of elements allocated
						will be equal to ``spec_count``.

						(-) Each element of the allocated array represents the
						number of elements in the array ``align_list`` for the
						corresponding ``spec_list`` element.

						(.) ``index_list`` is a pointer to an ''unsigned int'' into
						which this function will place a pointer to memory allocated
						to hold an array of ''unsigned int''s. Each element of the
						array will correspond to an element in the array
						``spec_list``, so the total number of elements allocated
						will be equal to ``spec_count``.

						(-) Each element of the allocated array represents the
						first element of the array ``align_list`` for the
						corresponding ``spec_list`` element.

						(.) ``size_list`` is a pointer to an ''unsigned int'' into
						which this function will place a pointer to memory allocated
						to hold an array of ''unsigned int''s. Each element of the
						array will correspond to an element in the array
						``spec_list``, so the total number of elements allocated
						will be equal to ``spec_count``.

						(-) Each element of the allocated array represents the
						total size of all of the elements in the array
						``align_list`` for the 	corresponding ``spec_list`` element.
						This size will include any alignment bytes required by the
						implementation.

						(.) ``structure_size`` is a pointer to an ''unsigned int''
						into which will be placed the total size of the structure
						as determined by this function. The size will include
						any alignment bytes required by the implementation.

						(-) If ``structure_size`` is ''NULL'', it will not be
						de-referenced.

						(.) ``align_count`` is a pointer to an ''unsigned int'' into
						which will be placed the number of members which were
						parsed out of the string ``spec_string``.

						(.) ``align_list`` points to a pointer to a structure of
						type ''DTA''. If the function is
						successful, it will allocate memory sufficient to hold
						``align_count`` elements. Each element will describe the
						offset and length requirements for each member of the
						desired structure.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at
						least ''DTA_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DTA_SUCCESS'' if no error occurs.

						(.) One of the non-zero DTA return codes if an error
						occurs.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  DTA_AlignStringList
						DTA_BASIC_AlignString

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2014 Michael L. Brock

   OUTPUT INDEX:	DTA_BASIC_AlignStringList
						Data Type Alignment Functions:DTA_BASIC_AlignStringList
						DTA:Functions:DTA_BASIC_AlignStringList
						DTA:Data Type Alignment Functions:DTA_BASIC_AlignStringList

   PUBLISH XREF:	DTA_BASIC_AlignStringList

   PUBLISH NAME:	DTA_BASIC_AlignStringList

	ENTRY CLASS	:	Data Type Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DTA_BASIC_AlignStringList(unsigned int type_count,
	const DTA_TYPE *type_list, int normalize_flag,
	int adjust_char_flag, const char *separator_list, unsigned int spec_count,
	char **spec_list, unsigned int **count_list, unsigned int **index_list,
	unsigned int **size_list, unsigned int *structure_size,
	unsigned int *align_count, DTA **align_list, char *error_text)
#else
int DTA_BASIC_AlignStringList(type_count, type_list, normalize_flag,
	adjust_char_flag, separator_list, spec_count, spec_list, count_list,
	index_list, size_list, structure_size, align_count, align_list,
	error_text)
unsigned int     type_count;
const DTA_TYPE  *type_list;
int              normalize_flag;
int              adjust_char_flag;
const char      *separator_list;
unsigned int     spec_count;
char           **spec_list;
unsigned int   **count_list;
unsigned int   **index_list;
unsigned int   **size_list;
unsigned int    *structure_size;
unsigned int    *align_count;
DTA            **align_list;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code;
	unsigned int  current_index   = 0;
	unsigned int  tmp_align_count = 0;
	DTA          *tmp_align_list  = NULL;
	unsigned int  count_1;
	unsigned int  tmp_structure_size;
	char          tmp_error_text[DTA_MAX_ERROR_TEXT + 1];

	structure_size  = (structure_size == NULL) ? &tmp_structure_size :
		structure_size;

	*count_list     = NULL;
	*index_list     = NULL;
	*size_list      = NULL;
	*structure_size = 0;
	*align_count    = 0;
	*align_list     = NULL;

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Make sure we have work to do . . .									*/
	/*	**************************************************************	*/
	if (!spec_count) {
		strcpy(error_text, "No primitive type specifications passed.");
		return_code = DTA_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Allocate space for the array of align structure counts.		*/
	/*	**************************************************************	*/
	if ((*count_list = ((unsigned int *) calloc(spec_count,
		sizeof(*count_list)))) == NULL) {
		STR_AllocMsgList(spec_count, sizeof(*count_list), error_text,
			"Unable to allocate memory for the count array");
		return_code = DTA_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Allocate space for the array of align index elements.			*/
	/*	**************************************************************	*/
	if ((*index_list = ((unsigned int *) calloc(spec_count,
		sizeof(*index_list)))) == NULL) {
		STR_AllocMsgList(spec_count, sizeof(*index_list), error_text,
			"Unable to allocate memory for the index array");
		return_code = DTA_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Allocate space for the array of align size elements.			*/
	/*	**************************************************************	*/
	if ((*size_list = ((unsigned int *) calloc(spec_count,
		sizeof(*size_list)))) == NULL) {
		STR_AllocMsgList(spec_count, sizeof(*size_list), error_text,
			"Unable to allocate memory for the size array");
		return_code = DTA_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		For each specification, attempt to create an array of align	*/
	/*	elements. This array will be added to the cumulative array.		*/
	/*																						*/
	/*		You should note that we don't try to normalize across			*/
	/*	specifications. That is, if one specification is 'c[10]', and	*/
	/*	the specification which follows is 'c[3]', we don't replace		*/
	/*	the align elements corresponding to these two specifications	*/
	/*	with the equivalent of 'c[13]'. This is because we envision		*/
	/*	this routine as used to determine the size and offset of			*/
	/*	structure members.															*/
	/*																						*/
	/*		If you want your specifications normalized across array		*/
	/*	elements, you should perform a call to the associated function	*/
	/*	'DTA_NormalizeList()' after this function returns.			*/
	/*	**************************************************************	*/
	for (count_1 = 0; count_1 < spec_count; count_1++) {
		if ((return_code = DTA_BASIC_AlignString(type_count, type_list,
			normalize_flag, adjust_char_flag, separator_list, spec_list[count_1],
			*size_list + count_1, &tmp_align_count, &tmp_align_list,
			tmp_error_text)) != DTA_SUCCESS) {
			sprintf(error_text, "%s %u: %s",
				"Error processing primitive type specification index number",
				count_1, tmp_error_text);
			goto EXIT_FUNCTION;
		}
		else if (mema_add(tmp_align_count, tmp_align_list, sizeof(**align_list),
			align_count, ((void **) align_list)) != STRFUNCS_SUCCESS) {
			STR_AllocMsgList(tmp_align_count, sizeof(**align_list), error_text,
				"%s for primitive type specification index number %u.",
				"Unable to allocate memory for the align array", count_1);
			return_code = DTA_MEMORY_FAILURE;
			goto EXIT_FUNCTION;
		}
		(*count_list)[count_1]  = tmp_align_count;
		(*index_list)[count_1]  = current_index;
		current_index          += tmp_align_count;
		if (tmp_align_list != NULL) {
			free(tmp_align_list);
			tmp_align_list = NULL;
		}
	}
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Now fix-up all of the offsets for the cumulative array.		*/
	/*	**************************************************************	*/
	return_code = DTA_BASIC_AlignList(type_count, type_list,
		structure_size, *align_count, *align_list, error_text);
	/*	**************************************************************	*/

EXIT_FUNCTION:

	if (return_code != DTA_SUCCESS) {
		if (*count_list != NULL)
			free(*count_list);
		if (*index_list != NULL)
			free(*index_list);
		if (*size_list != NULL)
			free(*size_list);
		if (*align_list != NULL)
			free(*align_list);
		*count_list     = NULL;
		*index_list     = NULL;
		*size_list      = NULL;
		*structure_size = 0;
		*align_count    = 0;
		*align_list     = NULL;
	}

	if (tmp_align_list != NULL) {
		free(tmp_align_list);
		tmp_align_list = NULL;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  DTA_AlignStringList

   SYNOPSIS    :  return_code = DTA_AlignStringList(normalize_flag,
							adjust_char_flag, separator_list, spec_count, spec_list,
							count_list, index_list, size_list, structure_size,
							align_count, align_list, error_text);

						int            return_code;

						int            normalize_flag;

						int            adjust_char_flag;

						const char    *separator_list;

						unsigned int   spec_count;

						char         **spec_list;

						unsigned int **count_list;

						unsigned int **index_list;

						unsigned int **size_list;

						unsigned int  *structure_size;

						unsigned int  *align_count;

						DTA          **align_list;

						char          *error_text;

   DESCRIPTION :	Transforms an array of pointers to string specifications of
						the primitive type members of a structure into an array of
						structures of type ''DTA'', the elements of which
						contain offset and length data for each member.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``normalize_flag`` indicates whether the elements of
						the array ``align_list`` which results the operation of
						this function are to be normalized vis-a-vis each other.

						(-) Normalization is the combination of like data types from
						adjacent ``align_list`` elements into a single element.

						(-) For example, if ``align_list`` contains the adjacent
						elements resulting from operation of this function on the
						string:

{|-|}c[10],c[3]

						(-) Normalization of those elements will result in a single
						element equivalent to the string:

{|-|}c[13]

						(-) The ``normalize_flag`` parameter may take on one of the
						following two values:

						(..) ``DTA_TRUE``, which indicates that the elements
						are to be normalized.

						(..) ``DTA_FALSE``, which indicates that the elements
						are not to be normalized.

						(.) ``adjust_char_flag`` specifies that ''char'' (and
						''unsigned char'') arrays are to be increased in length
						by a single byte. This is usually to accomodate the
						inclusion of the ''C'' language string null terminator byte.

						(-) The ``adjust_char_flag`` parameter may take on one of
						the following two values:

						(..) ``DTA_TRUE``, which indicates that ''char''
						elements are to be adjusted.

						(..) ``DTA_FALSE``, which indicates that ''char''
						elements are not to be adjusted.

						(.) ``separator_list`` is an ASCII NUL (ASCII 0) terminated
						string which lists the characters to be used to separate
						discrete specifications in ``spec_string``.

						(-) if ``separator_list`` is ''NULL'', the comma character
						('','') will be used to separate specifications in
						``spec_string``.

						(.) ``spec_count`` is the number of elements in the
						array ``spec_list``.

						(.) ``spec_list`` is a array of pointers to strings, each
						string of which is a primitive type specification having
						the following format:

						(--) { ''b''|''c''|''C''|''s''|''S''|''i''|''I''|''l''|''L''|''f''|''d'' }

						(-) where each letter has the following meaning:

						(..)''b'' is an unsigned (binary) char. The upper-case
						letter ''B'' is also allowed.

						(..)''c'' is a signed char.

						(..)''C'' is an unsigned char.

						(..)''s'' is a signed short integer.

						(..)''S'' is an unsigned short integer.

						(..)''i'' is a signed integer.

						(..)''I'' is an unsigned integer.

						(..)''l'' is a long integer.

						(..)''L'' is an unsigned long integer

						(..)''f'' is a float. The upper-case letter ''F'' is also
						allowed.

						(..)''d'' is a double. The upper-case letter ''D'' is also
						allowed.

						(-) A member definition may be followed by an optional
						array specifier of the form:

						(--) ``member-definition``[``array-length``]

						(-) Note that ``array-length`` must be greater than zero.

						(.) ``count_list`` is a pointer to an ''unsigned int'' into
						which this function will place a pointer to memory allocated
						to hold an array of ''unsigned int''s. Each element of the
						array will correspond to an element in the array
						``spec_list``, so the total number of elements allocated
						will be equal to ``spec_count``.

						(-) Each element of the allocated array represents the
						number of elements in the array ``align_list`` for the
						corresponding ``spec_list`` element.

						(.) ``index_list`` is a pointer to an ''unsigned int'' into
						which this function will place a pointer to memory allocated
						to hold an array of ''unsigned int''s. Each element of the
						array will correspond to an element in the array
						``spec_list``, so the total number of elements allocated
						will be equal to ``spec_count``.

						(-) Each element of the allocated array represents the
						first element of the array ``align_list`` for the
						corresponding ``spec_list`` element.

						(.) ``size_list`` is a pointer to an ''unsigned int'' into
						which this function will place a pointer to memory allocated
						to hold an array of ''unsigned int''s. Each element of the
						array will correspond to an element in the array
						``spec_list``, so the total number of elements allocated
						will be equal to ``spec_count``.

						(-) Each element of the allocated array represents the
						total size of all of the elements in the array
						``align_list`` for the 	corresponding ``spec_list`` element.
						This size will include any alignment bytes required by the
						implementation.

						(.) ``structure_size`` is a pointer to an ''unsigned int''
						into which will be placed the total size of the structure
						as determined by this function. The size will include
						any alignment bytes required by the implementation.

						(-) If ``structure_size`` is ''NULL'', it will not be
						de-referenced.

						(.) ``align_count`` is a pointer to an ''unsigned int'' into
						which will be placed the number of members which were
						parsed out of the string ``spec_string``.

						(.) ``align_list`` points to a pointer to a structure of
						type ''DTA''. If the function is
						successful, it will allocate memory sufficient to hold
						``align_count`` elements. Each element will describe the
						offset and length requirements for each member of the
						desired structure.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at
						least ''DTA_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DTA_SUCCESS'' if no error occurs.

						(.) One of the non-zero DTA Return Codes if an error
						occurs.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  DTA_BASIC_AlignStringList
						DTA_AlignString

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2014 Michael L. Brock

   OUTPUT INDEX:	DTA_AlignStringList
						Data Type Alignment Functions:DTA_AlignStringList
						DTA:Functions:DTA_AlignStringList
						DTA:Data Type Alignment Functions:DTA_AlignStringList

   PUBLISH XREF:	DTA_AlignStringList

   PUBLISH NAME:	DTA_AlignStringList

	ENTRY CLASS	:	Data Type Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DTA_AlignStringList(int normalize_flag, int adjust_char_flag,
	const char *separator_list, unsigned int spec_count, char **spec_list,
	unsigned int **count_list, unsigned int **index_list,
	unsigned int **size_list, unsigned int *structure_size,
	unsigned int *align_count, DTA **align_list, char *error_text)
#else
int DTA_AlignStringList(normalize_flag, adjust_char_flag,
	separator_list, spec_count, spec_list, count_list, index_list, size_list,
	structure_size, align_count, align_list, error_text)
int            normalize_flag;
int            adjust_char_flag;
const char    *separator_list;
unsigned int   spec_count;
char         **spec_list;
unsigned int **count_list;
unsigned int **index_list;
unsigned int **size_list;
unsigned int  *structure_size;
unsigned int  *align_count;
DTA          **align_list;
char          *error_text;
#endif /* #ifndef NARGS */
{
	return(DTA_BASIC_AlignStringList(0, NULL, normalize_flag,
		adjust_char_flag, separator_list, spec_count, spec_list, count_list,
		index_list, size_list, structure_size, align_count, align_list,
		error_text));
}
/*	***********************************************************************	*/

