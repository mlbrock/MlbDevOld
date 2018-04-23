/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	STRFUNCS String and Memory Functions Library Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Outputs one or more strings to the specified output
								handler.

	Revision History	:	1992-04-02 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include "strfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	STR_EMIT_String

   SYNOPSIS    :	void STR_EMIT_String(out_string, out_count, output_function,
							output_control);

						const char            *out_string;

						unsigned int           out_count;

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;

   DESCRIPTION :	Emits one or more instances of a string to the specified
						output handler.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``out_string`` is the string to be emitted.

						(.) ``out_count`` is the number of times the string is
						to be emitted.

						(.) ``output_function`` is a pointer to the function which
						handles output. The function should take arguments of the
						general form:

						<->''int'' ``output_function``(''void *'', ''const char'' ``format_string``, ``...``);

						(-) Functions of this form include the C standard library
						function ``fprintf``. The MFILE memory-mapped library
						function ``mprintf`` may also be used.

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

   NOTES       :	If you want the strings emitted by this function to be
						terminated by a line-feed, use the related function
						``STR_EMIT_StringLine``.

						If you want the strings emitted by this function to be
						terminated by a space character, use the related function
						``STR_EMIT_StringSpace``.

						If you want to emit characters instead of string, use the
						related function ``STR_EMIT_Char``.

   CAVEATS     :	

   SEE ALSO    :	STR_EMIT_StringSpace
						STR_EMIT_StringLine
						STR_EMIT_Char

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	STR_EMIT_String
						Miscellaneous Functions:STR_EMIT_String
						STRFUNCS:Functions:STR_EMIT_String
						STRFUNCS Miscellaneous Functions:STR_EMIT_String
						General Functions:See STRFUNCS

   PUBLISH XREF:	STR_EMIT_String

   PUBLISH NAME:	STR_EMIT_String

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void STR_EMIT_String(const char *out_string, unsigned int out_count,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
void STR_EMIT_String(out_string, out_count, output_function, output_control)
const char            *out_string;
unsigned int           out_count;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	STR_EMIT_SetDefaults(&output_function, &output_control);

	while (out_count--)
		(*output_function)(output_control, "%s", out_string);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	STR_EMIT_StringSpace

   SYNOPSIS    :	void STR_EMIT_StringSpace(out_string, out_count,
							output_function, output_control);

						const char            *out_string;

						unsigned int           out_count;

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;

   DESCRIPTION :	Emits one or more instances of a string to the specified
						output handler.

						After the function has emitted the specified number of
						instances of the string, it will emit a single space
						(ASCII 32).

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``out_string`` is the string to be emitted.

						(.) ``out_count`` is the number of times the string is
						to be emitted.

						(.) ``output_function`` is a pointer to the function which
						handles output. The function should take arguments of the
						general form:

						<->''int'' ``output_function``(''void *'', ''const char'' ``format_string``, ``...``);

						(-) Functions of this form include the C standard library
						function ``fprintf``. The MFILE memory-mapped library
						function ``mprintf`` may also be used.

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

   NOTES       :	If you want the strings emitted by this function to be
						terminated by a line-feed, use the related function
						``STR_EMIT_StringLine``.

						If you want to emit characters instead of string, use the
						related function ``STR_EMIT_CharSpace``.

   CAVEATS     :	

   SEE ALSO    :	STR_EMIT_String
						STR_EMIT_StringLine
						STR_EMIT_CharSpace

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	STR_EMIT_StringSpace
						Miscellaneous Functions:STR_EMIT_StringSpace
						STRFUNCS:Functions:STR_EMIT_StringSpace
						STRFUNCS Miscellaneous Functions:STR_EMIT_StringSpace
						General Functions:See STRFUNCS

   PUBLISH XREF:	STR_EMIT_StringSpace

   PUBLISH NAME:	STR_EMIT_StringSpace

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void STR_EMIT_StringSpace(const char *out_string, unsigned int out_count,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
void STR_EMIT_StringSpace(out_string, out_count, output_function,
	output_control)
const char            *out_string;
unsigned int           out_count;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	STR_EMIT_SetDefaults(&output_function, &output_control);

	STR_EMIT_String(out_string, out_count, output_function,
		output_control);
	(*output_function)(output_control, " ");
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	STR_EMIT_StringLine

   SYNOPSIS    :	void STR_EMIT_StringLine(out_string, out_count,
							output_function, output_control);

						const char            *out_string;

						unsigned int           out_count;

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;

   DESCRIPTION :	Emits one or more instances of a string to the specified
						output handler.

						After the function has emitted the specified number of
						instances of the string, it will emit a line-feed
						(ASCII 10).

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``out_string`` is the string to be emitted.

						(.) ``out_count`` is the number of times the string is
						to be emitted.

						(.) ``output_function`` is a pointer to the function which
						handles output. The function should take arguments of the
						general form:

						<->''int'' ``output_function``(''void *'', ''const char'' ``format_string``, ``...``);

						(-) Functions of this form include the C standard library
						function ``fprintf``. The MFILE memory-mapped library
						function ``mprintf`` may also be used.

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

   NOTES       :	If you want the strings emitted by this function to be
						terminated by a space character, use the related function
						``STR_EMIT_StringSpace``.

						If you want to emit characters instead of string, use the
						related function ``STR_EMIT_CharLine``.

   CAVEATS     :	

   SEE ALSO    :	STR_EMIT_String
						STR_EMIT_CharSpace
						STR_EMIT_CharLine

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:	STR_EMIT_StringLine
						Miscellaneous Functions:STR_EMIT_StringLine
						STRFUNCS:Functions:STR_EMIT_StringLine
						STRFUNCS Miscellaneous Functions:STR_EMIT_StringLine
						General Functions:See STRFUNCS

   PUBLISH XREF:	STR_EMIT_StringLine

   PUBLISH NAME:	STR_EMIT_StringLine

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void STR_EMIT_StringLine(const char *out_string, unsigned int out_count,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
void STR_EMIT_StringLine(out_string, out_count, output_function,
	output_control)
const char            *out_string;
unsigned int           out_count;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	STR_EMIT_SetDefaults(&output_function, &output_control);

	STR_EMIT_String(out_string, out_count, output_function,
		output_control);
	(*output_function)(output_control, "\n");
}
/*	***********************************************************************	*/

