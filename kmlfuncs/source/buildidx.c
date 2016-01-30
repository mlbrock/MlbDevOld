/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Builds an index of 'KML_CHAR_INDEX' structures.

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
#include <string.h>

#include "kmlfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*		Function prototypes for static functions . . .								*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(void KML_SORT_ItemList, (unsigned int count,
	KML_ITEM *list));
COMPAT_FN_DECL_STATIC(int  KML_SCMP_Item, (void *control_ptr,
	const KML_ITEM *ptr_1, const KML_ITEM *ptr_2, size_t data_length));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int KML_BuildIndex(KML_DOMAIN *domain_ptr, char *error_text)
#else
int KML_BuildIndex(domain_ptr, error_text)
KML_DOMAIN *domain_ptr;
char       *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code = KML_SUCCESS;
	unsigned int   count_1;
	unsigned int   alloc_count;
	unsigned int   item_count;
	KML_ITEM      *item_list;
	KML_ITEM       item_data;
	KML_ITEM      *tmp_item_list;
	const char    *tmp_ptr;
	unsigned char  tmp_char;
	unsigned int   tmp_uint;

	if (domain_ptr->item_list != NULL)
		free(domain_ptr->item_list);

	domain_ptr->item_count = 0;
	domain_ptr->item_list  = NULL;

	KML_INIT_IndexList(UCHAR_MAX + 1, domain_ptr->index_list);
	memset(domain_ptr->name_flag_list, '\0',
		sizeof(domain_ptr->name_flag_list));
	memset(domain_ptr->first_name_flag_list, '\0',
		sizeof(domain_ptr->first_name_flag_list));
	memset(domain_ptr->other_name_flag_list, '\0',
		sizeof(domain_ptr->other_name_flag_list));

	alloc_count = (domain_ptr->string_count + domain_ptr->comment_count +
		domain_ptr->keyword_count + domain_ptr->symbol_count +
		domain_ptr->block_count + domain_ptr->operator_count) * 2;
	for (count_1 = 0; count_1 < domain_ptr->name_count; count_1++)
		alloc_count += strlen(domain_ptr->name_list[count_1].first_char) * 2;

	if (!alloc_count) {
		strcpy(error_text, "No specification in domain.");
		return_code = KML_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if ((item_list = ((KML_ITEM *) calloc(alloc_count,
		sizeof(KML_ITEM)))) == NULL) {
		STR_AllocMsgList(alloc_count, sizeof(*item_list), error_text,
			"Unable to allocate the working list of 'KML_ITEM' structures");
		return_code = KML_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	item_count = 0;

	memset(&item_data, '\0', sizeof(item_data));

	/*
		*****************************************************************
		*****************************************************************
		Insert the string type specifiers to the item list . . .
		*****************************************************************
	*/
	for (count_1 = 0; count_1 < domain_ptr->string_count; count_1++) {
		tmp_ptr                       =
			((const char *) domain_ptr->string_list[count_1].start_ptr);
		tmp_char                      = *((unsigned char *) tmp_ptr);
		item_data.type                = KML_TYPE_STRING;
		item_data.type_ptr.string_ptr = domain_ptr->string_list + count_1;
		item_data.length              = strlen(tmp_ptr);
		item_data.ptr                 = tmp_ptr;
		item_data.first_char          = tmp_char;
		item_data.case_flag           = domain_ptr->string_case_flag;
		item_list[item_count++]       = item_data;
		if ((!(domain_ptr->string_case_flag)) && isalpha(tmp_char)) {
			tmp_char                = ((unsigned char)
				((islower(tmp_char)) ? toupper(tmp_char) : tolower(tmp_char)));
			item_data.first_char    = tmp_char;
			item_list[item_count++] = item_data;
		}  
	}
	/*	*****************************************************************	*/

	/*
		*****************************************************************
		*****************************************************************
		Insert the comment type specifiers to the item list . . .
		*****************************************************************
	*/
	for (count_1 = 0; count_1 < domain_ptr->comment_count; count_1++) {
		tmp_ptr                        =
			domain_ptr->comment_list[count_1].start_ptr;
		tmp_char                       = *((unsigned char *) tmp_ptr);
		item_data.type                 = KML_TYPE_COMMENT;
		item_data.type_ptr.comment_ptr = domain_ptr->comment_list + count_1;
		item_data.length               = strlen(tmp_ptr);
		item_data.ptr                  = tmp_ptr;
		item_data.first_char           = tmp_char;
		item_data.case_flag            = domain_ptr->comment_case_flag;
		item_list[item_count++]        = item_data;
		if ((!(domain_ptr->comment_case_flag)) && isalpha(tmp_char)) {
			tmp_char                = ((unsigned char)
				((islower(tmp_char)) ? toupper(tmp_char) : tolower(tmp_char)));
			item_data.first_char    = tmp_char;
			item_list[item_count++] = item_data;
		}  
	}
	/*	*****************************************************************	*/

	/*
		*****************************************************************
		*****************************************************************
		Insert the keyword type specifiers to the item list . . .
		*****************************************************************
	*/
	for (count_1 = 0; count_1 < domain_ptr->keyword_count; count_1++) {
		tmp_ptr                        =
			domain_ptr->keyword_list[count_1].keyword;
		tmp_char                       = *((unsigned char *) tmp_ptr);
		item_data.type                 = KML_TYPE_KEYWORD;
		item_data.type_ptr.keyword_ptr = domain_ptr->keyword_list + count_1;
		item_data.length               = strlen(tmp_ptr);
		item_data.ptr                  = tmp_ptr;
		item_data.first_char           = tmp_char;
		item_data.case_flag            = domain_ptr->keyword_case_flag;
		item_list[item_count++]        = item_data;
		if ((!(domain_ptr->keyword_case_flag)) && isalpha(tmp_char)) {
			tmp_char                = ((unsigned char)
				((islower(tmp_char)) ? toupper(tmp_char) : tolower(tmp_char)));
			item_data.first_char    = tmp_char;
			item_list[item_count++] = item_data;
		}  
	}
	/*	*****************************************************************	*/

	/*
		*****************************************************************
		*****************************************************************
		Insert the symbol type specifiers to the item list . . .
		*****************************************************************
	*/
	for (count_1 = 0; count_1 < domain_ptr->symbol_count; count_1++) {
		tmp_ptr                       =
			domain_ptr->symbol_list[count_1].ptr;
		tmp_char                      = *((unsigned char *) tmp_ptr);
		item_data.type                = KML_TYPE_SYMBOL;
		item_data.type_ptr.symbol_ptr = domain_ptr->symbol_list + count_1;
		item_data.length              = strlen(tmp_ptr);
		item_data.ptr                 = tmp_ptr;
		item_data.first_char          = tmp_char;
		item_data.case_flag           = domain_ptr->symbol_case_flag;
		item_list[item_count++]       = item_data;
		if ((!(domain_ptr->symbol_case_flag)) && isalpha(tmp_char)) {
			tmp_char                = ((unsigned char)
				((islower(tmp_char)) ? toupper(tmp_char) : tolower(tmp_char)));
			item_data.first_char    = tmp_char;
			item_list[item_count++] = item_data;
		}  
	}
	/*	*****************************************************************	*/

	/*
		*****************************************************************
		*****************************************************************
		Insert the block type specifiers to the item list . . .
		*****************************************************************
	*/
	for (count_1 = 0; count_1 < domain_ptr->block_count; count_1++) {
		tmp_ptr                      =
			domain_ptr->block_list[count_1].start_ptr;
		tmp_char                     = *((unsigned char *) tmp_ptr);
		item_data.type               = KML_TYPE_BLOCK;
		item_data.type_ptr.block_ptr = domain_ptr->block_list + count_1;
		item_data.length             = strlen(tmp_ptr);
		item_data.ptr                = tmp_ptr;
		item_data.first_char         = tmp_char;
		item_data.case_flag          = domain_ptr->block_case_flag;
		item_list[item_count++]      = item_data;
		if ((!(domain_ptr->block_case_flag)) && isalpha(tmp_char)) {
			tmp_char                = ((unsigned char)
				((islower(tmp_char)) ? toupper(tmp_char) : tolower(tmp_char)));
			item_data.first_char    = tmp_char;
			item_list[item_count++] = item_data;
		}  
	}
	/*	*****************************************************************	*/

	/*
		*****************************************************************
		*****************************************************************
		Insert the operator type specifiers to the item list . . .
		*****************************************************************
	*/
	for (count_1 = 0; count_1 < domain_ptr->operator_count; count_1++) {
		tmp_ptr                         =
			domain_ptr->operator_list[count_1].ptr;
		tmp_char                        = *((unsigned char *) tmp_ptr);
		item_data.type                  = KML_TYPE_OPERATOR;
		item_data.type_ptr.operator_ptr = domain_ptr->operator_list + count_1;
		item_data.length                = strlen(tmp_ptr);
		item_data.ptr                   = tmp_ptr;
		item_data.first_char            = tmp_char;
		item_data.case_flag             = domain_ptr->operator_case_flag;
		item_list[item_count++]         = item_data;  
		if ((!(domain_ptr->operator_case_flag)) && isalpha(tmp_char)) {
			tmp_char                = ((unsigned char)
				((islower(tmp_char)) ? toupper(tmp_char) : tolower(tmp_char)));
			item_data.first_char    = tmp_char;
			item_list[item_count++] = item_data;
		}  
	}
	/*	*****************************************************************	*/

	/*
		*****************************************************************
		*****************************************************************
		Insert the name type specifiers to the item list . . .
		*****************************************************************
	*/
	for (count_1 = 0; count_1 < domain_ptr->name_count; count_1++) {
		for (tmp_ptr = domain_ptr->name_list[count_1].first_char; *tmp_ptr;
			tmp_ptr++) {
			tmp_char                    = *((unsigned char *) tmp_ptr);
			item_data.type              = KML_TYPE_NAME;
			item_data.type_ptr.name_ptr = domain_ptr->name_list + count_1;
			item_data.length            = 1;
			item_data.ptr               = tmp_ptr;
			item_data.first_char        = tmp_char;
			item_data.case_flag         = domain_ptr->name_case_flag;
			item_list[item_count++]     = item_data;
/*
	CODE NOTE: ??? To be deleted ???
			if ((!(domain_ptr->name_case_flag)) && isalpha(tmp_char)) {
				tmp_char                = ((unsigned char)
					((islower(tmp_char)) ? toupper(tmp_char) : tolower(tmp_char)));
				item_data.first_char    = tmp_char;
				item_list[item_count++] = item_data;
			}
*/
		}  
	}
	/*	*****************************************************************	*/

	tmp_item_list = item_list;
	if ((item_count < alloc_count) &&
		((tmp_item_list = ((KML_ITEM *) realloc(item_list,
		item_count * sizeof(*item_list)))) == NULL)) {
		STR_AllocMsgList(item_count, sizeof(*item_list), error_text,
			"Unable to re-allocate the 'KML_ITEM' list");
		return_code = KML_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}
	item_list = tmp_item_list;

	KML_SORT_ItemList(item_count, item_list);
	STR_ARRAY_reverse(item_count, item_list, sizeof(*item_list));
	
	for (count_1 = 0; count_1 < item_count; count_1++) {
		tmp_uint = ((unsigned int) item_list[count_1].first_char);
		if (!domain_ptr->index_list[tmp_uint].count)
			domain_ptr->index_list[tmp_uint].item_ptr = item_list + count_1;
		domain_ptr->index_list[tmp_uint].count++;
	}

	/*
		*****************************************************************
		*****************************************************************
		Create the map of characters which constitute valid names . . .
		*****************************************************************
	*/
	if (domain_ptr->name_count && (domain_ptr->name_list != NULL)) {
		tmp_ptr = domain_ptr->name_list->first_char;
		while (*tmp_ptr)
			domain_ptr->first_name_flag_list
				[((unsigned int) *((unsigned char *) tmp_ptr++))] = 1;
		tmp_ptr = domain_ptr->name_list->other_chars;
		while (*tmp_ptr)
			domain_ptr->other_name_flag_list
				[((unsigned int) *((unsigned char *) tmp_ptr++))] = 2;
		for (count_1 = 0; count_1 <= UCHAR_MAX; count_1++)
			domain_ptr->name_flag_list[count_1] = ((unsigned char)
				(domain_ptr->first_name_flag_list[count_1] +
				domain_ptr->other_name_flag_list[count_1]));
	}
	/*	*****************************************************************	*/

	/*
		*****************************************************************
		*****************************************************************
		If each of the characters which may introduce a name is not also
		in the list of subsequent valid characters for names, then the
		minimum length of a name is two characters.
		*****************************************************************
	*/
	domain_ptr->min_name_length = 1;
	tmp_ptr                     = domain_ptr->name_list->first_char;
	while (*tmp_ptr) {
		if (strchr(domain_ptr->name_list->other_chars, *tmp_ptr) == NULL) {
			domain_ptr->min_name_length = 2;
			break;
		}
		tmp_ptr++;
	}
	/*	*****************************************************************	*/

	domain_ptr->item_count = item_count;
	domain_ptr->item_list  = item_list;

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME        :	KML_SORT_ItemList

	SYNOPSIS    :	void KML_SORT_ItemList(count, list);

						unsigned int  count;

						KML_ITEM     *list;

	DESCRIPTION :	Sorts an array of ''KML_ITEM'' structures using
						the comparison function ``KML_SCMP_Item``.

						The following members of the ''KML_ITEM''
						structure are used as the basis of comparison in the sort:

						(.) ``ptr``

						(.) ``type``

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``count`` is the number of elements in the array
						``list``.

						(.) ``list`` is the array of ''KML_ITEM'' structures
						which is to be sorted by this function.

	RETURNS     :	Void.

	NOTES       :	

	CAVEATS     :	

	SEE ALSO    :	KML_INIT_ItemList
						KML_SCMP_Item

	EXAMPLES    :	

	AUTHOR      :	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2016 Michael L. Brock

	OUTPUT INDEX:	KML_SORT_ItemList
						Sort Functions:Database:KML_SORT_ItemList
						KML_ITEM Functions:KML_SORT_ItemList

	PUBLISH XREF:	KML_SORT_ItemList

	PUBLISH NAME:	KML_SORT_ItemList

	ENTRY CLASS	:	Sort Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
static void KML_SORT_ItemList(unsigned int count, KML_ITEM *list)
#else
static void KML_SORT_ItemList(count, list)
unsigned int  count;
KML_ITEM     *list;
#endif /* #ifndef NARGS */
{
	STR_ARRAY_qsort(NULL, count, ((void *) list), sizeof(*list),
		((int (*)(void *, const void *, const void *, size_t))
		KML_SCMP_Item));
}
/*	***********************************************************************	*/

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME        :	KML_SCMP_Item

	SYNOPSIS    :	return_code = KML_SCMP_Item(control_ptr, ptr_1,
							ptr_2, data_length);

						int             return_code;

						void           *control_ptr;

						const KML_ITEM *ptr_1;

						const KML_ITEM *ptr_2;

						size_t          data_length;

	DESCRIPTION :	Compares two ''KML_ITEM'' structures to
						determine their equivalence.

						The following members of the ''KML_ITEM''
						structure are used as the basis of the comparison:

						(.) ``ptr``

						(.) ``type``

	PARAMETERS  :	Parameters to this function are as follow:

						(.) ``control_ptr`` points to a arbitrary user-defined
						structure which may be used to modify the comparison.
						Because it is unnecessary to the comparison of
						''KML_ITEM'' structures, it may be passed as a
						''NULL'' pointer.

						(.) ``ptr_1`` points to the first ''KML_ITEM''
						structure to be compared.

						(.) ``ptr_2`` points to the second ''KML_ITEM''
						structure to be compared.

						(.) ``data_length`` is the size the areas to which
						``ptr_1`` and ``ptr_2`` point. Because it is unnecessary
						to the comparison of ''KML_ITEM'' structures,
						it may be zero (''0'').

	RETURNS     :	Returns from this function are as follow:

						(.) negative if the first ''KML_ITEM'' structure
						is less than second.

						(.) positive if the first ''KML_ITEM'' structure
						is greater than second.

						(.) zero if the structures are equivalent.

	NOTES       :  The ``control_ptr`` and ``data_length`` parameters are
						present only because this function is used internally
						by the STRFUNCS list functions. These parameters provide
						function-call compatibility with other, more generic,
						functions such as ``KML_SORT_ItemList``.

	CAVEATS     :	

	SEE ALSO    :	

	EXAMPLES    :	

	AUTHOR      :	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2016 Michael L. Brock

	OUTPUT INDEX:	KML_SCMP_Item
						Comparison Functions:KML_SCMP_Item
						KML_ITEM Functions:KML_SCMP_Item

	PUBLISH XREF:	KML_SCMP_Item

	PUBLISH NAME:	KML_SCMP_Item

	ENTRY CLASS	:	Comparison Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
static int KML_SCMP_Item(void *control_ptr, const KML_ITEM *ptr_1,
	const KML_ITEM *ptr_2, size_t data_length)
#else
static int KML_SCMP_Item(control_ptr, ptr_1, ptr_2, data_length)
void           *control_ptr;
const KML_ITEM *ptr_1;
const KML_ITEM *ptr_2;
size_t          data_length;
#endif /* #ifndef NARGS */
{
	return((ptr_1->first_char > ptr_2->first_char) ? 1 :
		((ptr_1->first_char < ptr_2->first_char) ? -1 :
		((ptr_1->length > ptr_2->length) ? 1 :
		((ptr_1->length < ptr_2->length) ? -1 :
		((ptr_1->type > ptr_2->type) ? 1 : ((ptr_1->type < ptr_1->type) ? -1 :
		strcmp(ptr_1->ptr, ptr_2->ptr)))))));
}
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

