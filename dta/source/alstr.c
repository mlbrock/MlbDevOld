/* *********************************************************************** */
/* *********************************************************************** */
/*	Data Type Alignment (DTA) Functions Library Source Module					*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Transforms a single string descriptor into an array
								of 'DTA' structures.

	Revision History	:	1992-02-23 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2018.
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

   NAME        :  DTA_BASIC_AlignString

   SYNOPSIS    :  return_code = DTA_BASIC_AlignString(type_count,
							type_list, normalize_flag, adjust_char_flag,
							separator_list, spec_string, structure_size, align_count,
							align_list, error_text);

						int              return_code;

						unsigned int     type_count;

						const DTA_TYPE  *type_list;

						int              normalize_flag;

						int              adjust_char_flag;

						const char      *separator_list;

						char            *spec_string;

						unsigned int    *structure_size;

						unsigned int    *align_count;

						DTA            **align_list;

						char            *error_text;

   DESCRIPTION :  Transforms a string specification of the members of a
						structure into an array of structures of type
						''DTA'', the elements of which contain
						offset and length data for each member.

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
						discrete specifications in ``spec_string``.

						(-) if ``separator_list`` is ''NULL'', the comma character
						('','') will be used to separate specifications in
						``spec_string``.

   					(.) ``spec_string`` is the string which contains a list of
						member definitions separated by some combination of the
						characters in ``separator_list``. Leading and trailing
						``separator_string`` characters are ignored.

						(-) Each member definition has the following format:

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

   SEE ALSO    :  DTA_AlignString
						DTA_BASIC_CheckMember
						DTA_BASIC_AlignList

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	DTA_BASIC_AlignString
						Data Type Alignment Functions:DTA_BASIC_AlignString
						DTA:Functions:DTA_BASIC_AlignString
						DTA:Data Type Alignment Functions:DTA_BASIC_AlignString

   PUBLISH XREF:	DTA_BASIC_AlignString

   PUBLISH NAME:	DTA_BASIC_AlignString

	ENTRY CLASS	:	Data Type Alignment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DTA_BASIC_AlignString(unsigned int type_count, const DTA_TYPE *type_list,
	int normalize_flag, int adjust_char_flag, const char *separator_list,
	const char *spec_string, unsigned int *structure_size,
	unsigned int *align_count, DTA **align_list, char *error_text)
#else
int DTA_BASIC_AlignString(type_count, type_list, normalize_flag,
	adjust_char_flag, separator_list, spec_string, structure_size, align_count,
	align_list, error_text)
unsigned int     type_count;
const DTA_TYPE  *type_list;
int              normalize_flag;
int              adjust_char_flag;
const char      *separator_list;
const char      *spec_string;
unsigned int    *structure_size;
unsigned int    *align_count;
DTA            **align_list;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code;
	unsigned int   string_count = 0;
	char         **string_list  = NULL;
	unsigned int   count_1;
	char          *tmp_string;
	char          *tmp_ptr;

	*align_count    = 0;
	*align_list     = NULL;

	separator_list  = (separator_list != NULL) ? separator_list : ",";

	if ((tmp_string = strdup(spec_string)) == NULL) {
		strcpy(error_text, "Unable to copy string to temporary work area.");
		return_code = DTA_MEMORY_FAILURE;
   }
	else {
		tmp_ptr = tmp_string;
		while (*tmp_ptr) {
			if (strchr(separator_list, *tmp_ptr) != NULL)
				*tmp_ptr = ' ';
			tmp_ptr++;
      }
		oneblank(trim(ctltospc(tmp_string)));
		if (sepwordl(tmp_string, &string_count, &string_list)) {
			strcpy(error_text, "Unable to unpack string to list of data types.");
			return_code = DTA_MEMORY_FAILURE;
		}
		else if (!string_count) {
			strcpy(error_text, "No data types found in string.");
			return_code = DTA_FAILURE;
		}
		else {
			if ((*align_list = ((DTA *)
				calloc(string_count, sizeof(DTA)))) == NULL) {
				sprintf(error_text, "%s (data types = %u * size %u = %u).",
					"Unable to allocate storage for list", string_count,
					sizeof(DTA), string_count * sizeof(DTA));
				return_code = DTA_FAILURE;
			}
			else {
				*align_count = string_count;
				return_code  = 0;
				for (count_1 = 0; count_1 < string_count; count_1++) {
					if ((return_code =
						DTA_BASIC_CheckMember(type_count, type_list,
						string_list[count_1], *align_list + count_1,
						error_text)) != DTA_SUCCESS)
						break;
				}
				if (return_code == DTA_SUCCESS) {
					if (normalize_flag)
						DTA_NormalizeList(align_count, align_list);
					if (adjust_char_flag) {
						for (count_1 = 0; count_1 < string_count; count_1++) {
							if (((*align_list)[count_1].type == DTA_C_char) ||
								((*align_list)[count_1].type ==
								DTA_C_unsigned_char))
								(*align_list)[count_1].array_length++;
						}
					}
					return_code = DTA_BASIC_AlignList(type_count, type_list,
						structure_size, *align_count, *align_list, error_text);
				}
				if (return_code != DTA_SUCCESS) {
					if (*align_list)
						free(*align_list);
					*align_count = 0;
					*align_list  = NULL;
				}
			}
			strl_remove_all(&string_count, &string_list);
		}
		free(tmp_string);
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  DTA_AlignString

   SYNOPSIS    :  return_code = DTA_AlignString(normalize_flag,
							adjust_char_flag, separator_list, spec_string,
							structure_size, align_count, align_list, error_text);

						int            return_code;

						int            normalize_flag;

						int            adjust_char_flag;

						const char    *separator_list;

						char          *spec_string;

						unsigned int  *structure_size;

						unsigned int  *align_count;

						DTA          **align_list;

						char          *error_text;

   DESCRIPTION :  Transforms a string specification of the members of a
						structure into an array of structures of type
						''DTA'', the elements of which contain
						offset and length data for each member.

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

   					(.) ``spec_string`` is the string which contains a list of
						member definitions separated by some combination of the
						characters in ``separator_list``. Leading and trailing
						``separator_string`` characters are ignored.

						(-) Each member definition has the following format:

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

   SEE ALSO    :  DTA_BASIC_AlignString
						DTA_CheckMember
						DTA_AlignList

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	DTA_AlignString
						Data Type Alignment Functionss:DTA_AlignString
						DTA:Functions:DTA_AlignString
						DTA:Data Type Alignment Functionss:DTA_AlignString

   PUBLISH XREF:	DTA_AlignString

   PUBLISH NAME:	DTA_AlignString

	ENTRY CLASS	:	Data Type Alignment Functionss

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DTA_AlignString(int normalize_flag, int adjust_char_flag,
	const char *separator_list, const char *spec_string,
	unsigned int *structure_size, unsigned int *align_count, DTA **align_list,
	char *error_text)
#else
int DTA_AlignString(normalize_flag, adjust_char_flag, separator_list,
	spec_string, structure_size, align_count, align_list, error_text)
int            normalize_flag;
int            adjust_char_flag;
const char    *separator_list;
const char    *spec_string;
unsigned int  *structure_size;
unsigned int  *align_count;
DTA          **align_list;
char          *error_text;
#endif /* #ifndef NARGS */
{
	return(DTA_BASIC_AlignString(0, NULL, normalize_flag,
		adjust_char_flag, separator_list, spec_string, structure_size,
		align_count, align_list, error_text));
}
/* *********************************************************************** */

#ifdef TEST_MAIN

COMPAT_FN_DECL(int main, (void));

int main()
{
	int             return_code     = 0;
	unsigned int    align_count     = 0;
	DTA            *align_list      = NULL;
	unsigned long   line_count      = 0L;
	unsigned int    structure_count = 1;
	unsigned int    type_count;
	const DTA_TYPE *type_list;
	unsigned int    count_1;
	unsigned int    structure_size;
	char            buffer[512];
	char            error_text[DTA_MAX_ERROR_TEXT];
	FILE           *file_ptr;

#ifdef __MSDOS__
	char             *compile_string =
		"bcc -Ic:\borlandc\include -Lc:\borlandc\lib aligntst.c";
	char             *execute_string = "aligntst.exe";
#else
	char              compile_buffer[1024];
	char             *compile_string = compile_buffer;
	char             *execute_string = "a.out";

	strcpy(compile_string, "cc ");
#ifdef NARGS
	strcat(compile_string, "-DNARGS=1 ");
#endif /* #ifdef NARGS */
#ifdef NO_CONST
	strcat(compile_string, "-Dconst=\"\" ");
#endif /* #ifdef NO_CONST */
#ifdef NO_VOLATILE
	strcat(compile_string, "-Dvolatile=\"\" ");
#endif /* #ifdef NO_VOLATILE */
#ifdef NO_VOID
	strcat(compile_string, "-Dvoid=\"\" ");
#endif /* #ifdef NO_VOID */
#ifdef NO_SIZE_T
	strcat(compile_string, "-Dsize_t=\"unsigned int\" ");
#endif /* #ifdef NO_SIZE_T */
	strcat(compile_string, "aligntst.c");
#endif /* #ifdef __MSDOS__ */

	fprintf(stderr, "Test harness for function 'DTA_AlignString()'\n");
	fprintf(stderr, "Test harness for function 'DTA_BASIC_AlignString()'\n");
	fprintf(stderr, "---- ------- --- -------- -------------------------\n\n");

	DTA_GetDefaultTypeInfo(&type_count, &type_list);

	if ((file_ptr = fopen("aligntst.c", "w")) == NULL) {
		fprintf(stderr, "Unable to open file 'aligntst.c' for output.\n");
		exit(-1);
	}

	fprintf(file_ptr, "#include <stdio.h>\n\n");
	fprintf(file_ptr, "#ifndef NARGS\n");
	fprintf(file_ptr, "int main(void);\n");
	fprintf(file_ptr, "#else\n");
	fprintf(file_ptr, "int main();\n");
	fprintf(file_ptr, "#endif /* #ifndef NARGS */\n\n");
	fprintf(file_ptr, "#ifndef offsetof\n");
	fprintf(file_ptr, "# define offsetof(structure_name, member_name) \\\n");
	fprintf(file_ptr, "\t((size_t) &(((structure_name *) 0)->member_name))\n");
	fprintf(file_ptr, "#endif /* #ifndef offsetof */\n\n");

	while ((!feof(stdin)) && (!ferror(stdin))) {
		*buffer = '\0';
		while (!(*buffer)) {
			if (fgets(buffer, sizeof(buffer) - 1, stdin) == NULL) {
				strcpy(buffer, "QUIT");
				break;
			}
			while (strlen(buffer) && (buffer[strlen(buffer) - 1] == '\n'))
				buffer[strlen(buffer) - 1] = '\0';
			line_count++;
		}
		if ((!stricmp(buffer, "QUIT")) || (!stricmp(buffer, "EXIT")) ||
			(!stricmp(buffer, "END")))
			break;
		if ((return_code = DTA_AlignString(DTA_FALSE, DTA_FALSE, ",", buffer,
			&structure_size, &align_count, &align_list, error_text)) !=
			DTA_SUCCESS) {
			fprintf(stderr, "ERROR: %s\n", error_text);
			break;
		}
		else {
			fprintf(file_ptr, "/* STRUCTURE DEFINITION: %s */\n\n", buffer);
			fprintf(file_ptr, "/* sizeof(STRUCTURE_%05u) = %u */\n",
				structure_count, structure_size);
			fprintf(file_ptr, "typedef struct {\n");
			for (count_1 = 0; count_1 < align_count; count_1++) {
				fprintf(file_ptr, "\t%s member_%05u",
					type_list[align_list[count_1].type].type_name,
					count_1 + 1);
				if (align_list[count_1].array_length > 1)
					fprintf(file_ptr, "[%u]", align_list[count_1].array_length);
				fprintf(file_ptr, "; /* Offset = %u, length = %u */\n",
				align_list[count_1].offset, align_list[count_1].length);
			}
			fprintf(file_ptr, "} STRUCTURE_%05u;\n\n", structure_count);
			fprintf(file_ptr, "#ifndef NARGS\n");
			fprintf(file_ptr, "int Test_STRUCTURE_%05u(void);\n",
				structure_count);
			fprintf(file_ptr, "#else\n");
			fprintf(file_ptr, "int Test_STRUCTURE_%05u();\n",
				structure_count);
			fprintf(file_ptr, "#endif /* #ifndef NARGS */\n\n");
			fprintf(file_ptr, "int Test_STRUCTURE_%05u()\n{\n",
				structure_count);
			fprintf(file_ptr, "	int return_code = 1;\n\n");
			fprintf(file_ptr, "\tif (sizeof(STRUCTURE_%05u) != %u)\n",
				structure_count, structure_size);
			fprintf(file_ptr,
				"\t\tfprintf(stderr, \"Error on STRUCTURE_%05u: ",
				structure_count);
			fprintf(file_ptr, "size is %%u, should be %u.\\n\",\n",
				structure_size);
			fprintf(file_ptr, "\t\t\tsizeof(STRUCTURE_%05u));\n",
				structure_count);
			for (count_1 = 0; count_1 < align_count; count_1++) {
				fprintf(file_ptr,
"\telse if (offsetof(STRUCTURE_%05u, member_%05u) != %u)\n",
					structure_count, count_1 + 1, align_list[count_1].offset);
				fprintf(file_ptr,
					"\t\tfprintf(stderr, \"Error on member_%05u member ",
					count_1 + 1);
				fprintf(file_ptr,
					"of structure STRUCTURE_%05u (%s): ", structure_count,
					type_list[align_list[count_1].type].type_name);
				fprintf(file_ptr, "offset is %%u, should be %u.\\n\",\n",
					align_list[count_1].offset);
				fprintf(file_ptr,
					"\t\t\toffsetof(STRUCTURE_%05u, member_%05u));\n",
					structure_count, count_1 + 1);
			}
			fprintf(file_ptr, "\telse {\n");
			fprintf(file_ptr,
				"\t\tfprintf(stderr, \"STRUCTURE_%05u IS OK\\n\");\n",
				structure_count);
			fprintf(file_ptr, "\t\treturn_code = 0;\n\n");
			fprintf(file_ptr, "\t}\n\n");
			fprintf(file_ptr, "\treturn(return_code);\n");
			fprintf(file_ptr, "}\n\n");
			free(align_list);
			structure_count++;
			fprintf(stderr, "OK\n");
		}
	}

	if ((!return_code) && structure_count) {
		fprintf(file_ptr, "int main()\n{\n");
		fprintf(file_ptr, "\tint return_code = 0;\n\n");
		for (count_1 = 1; count_1 < structure_count; count_1++) {
			fprintf(file_ptr, "\tif (Test_STRUCTURE_%05u())\n", count_1);
			fprintf(file_ptr, "\t\treturn_code = 1;\n");
		}
		fprintf(file_ptr, "\n\treturn(return_code);\n}\n");
		fclose(file_ptr);
		fprintf(stderr, "Compiling test program . . .");
		system(compile_string);
		fprintf(stderr, "\n");
		fprintf(stderr, "Executing test program . . .\n");
		system(execute_string);
	}

	return(return_code);
}
/* *********************************************************************** */

#endif /* #ifdef TEST_MAIN */

