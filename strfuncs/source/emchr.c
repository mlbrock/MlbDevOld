/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	STRFUNCS String and Memory Functions Library Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Emits one or more characters to the specified
								output handler.

	Revision History	:	1992-04-02 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2015.
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

   NAME        :	STR_EMIT_Char

   SYNOPSIS    :	void STR_EMIT_Char(out_character, out_count,
							output_function, output_control);

						int                    out_character;

						unsigned int           out_count;

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;

   DESCRIPTION :	Emits one or more characters to the specified output
						handler.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``out_character`` is the character to be emitted.

						(.) ``out_count`` is the number of times the character is
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

   NOTES       :	If you want the characters emitted by this function to be
						terminated by a line-feed, use the related function
						``STR_EMIT_CharLine``.

						If you want the characters emitted by this function to be
						terminated by a space character, use the related function
						``STR_EMIT_CharSpace``.

						If you want to emit strings instead of characters, use the
						related function ``STR_EMIT_String``.

   CAVEATS     :	

   SEE ALSO    :	STR_EMIT_CharSpace
						STR_EMIT_CharLine
						STR_EMIT_String

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1992 - 2015 Michael L. Brock

   OUTPUT INDEX:	STR_EMIT_Char
						Miscellaneous Functions:STR_EMIT_Char
						STRFUNCS:Functions:STR_EMIT_Char
						STRFUNCS Miscellaneous Functions:STR_EMIT_Char
						General Functions:See STRFUNCS

   PUBLISH XREF:	STR_EMIT_Char

   PUBLISH NAME:	STR_EMIT_Char

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void STR_EMIT_Char(int out_character, unsigned int out_count,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
void STR_EMIT_Char(out_character, out_count, output_function, output_control)
int                    out_character;
unsigned int           out_count;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	unsigned int this_count;
	char         buffer[1023 + 1];

	STR_EMIT_SetDefaults(&output_function, &output_control);

	if (out_count) {
		if (out_count < 3) {
			while (out_count--)
				(*output_function)(output_control, "%c", out_character);
		}
		else {
			nstrset(buffer, out_character, sizeof(buffer) - 1);
			while (out_count) {
				this_count          = (out_count <= (sizeof(buffer) - 1)) ?
					out_count : (sizeof(buffer) - 1);
				out_count          -= this_count;
				buffer[this_count]  = '\0';
				(*output_function)(output_control, "%s", buffer);
			}
		}
	}
/*
	CODE NOTE: To be removed.
	while (out_count--)
		(*output_function)(output_control, "%c", out_character);
*/
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	STR_EMIT_CharSpace

   SYNOPSIS    :	void STR_EMIT_CharSpace(out_character, out_count,
							output_function, output_control);

						int                    out_character;

						unsigned int           out_count;

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;

   DESCRIPTION :	Emits one or more characters to the specified output
						handler.

						After the function has emitted the specified number of
						characters, it will emit a single space (ASCII 32).

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``out_character`` is the character to be emitted.

						(.) ``out_count`` is the number of times the character is
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

   NOTES       :	If you want the characters emitted by this function to be
						terminated by a line-feed, use the related function
						``STR_EMIT_CharLine``.

						If you want to emit strings instead of characters, use the
						related function ``STR_EMIT_StringSpace``.

   CAVEATS     :	

   SEE ALSO    :	STR_EMIT_Char
						STR_EMIT_CharLine
						STR_EMIT_StringSpace

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1992 - 2015 Michael L. Brock

   OUTPUT INDEX:	STR_EMIT_CharSpace
						Miscellaneous Functions:STR_EMIT_CharSpace
						STRFUNCS:Functions:STR_EMIT_CharSpace
						STRFUNCS Miscellaneous Functions:STR_EMIT_CharSpace
						General Functions:See STRFUNCS

   PUBLISH XREF:	STR_EMIT_CharSpace

   PUBLISH NAME:	STR_EMIT_CharSpace

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void STR_EMIT_CharSpace(int out_character, unsigned int out_count,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
void STR_EMIT_CharSpace(out_character, out_count, output_function,
	output_control)
int                    out_character;
unsigned int           out_count;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	STR_EMIT_SetDefaults(&output_function, &output_control);

	STR_EMIT_Char(out_character, out_count, output_function, output_control);
	(*output_function)(output_control, " ");
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	STR_EMIT_CharLine

   SYNOPSIS    :	void STR_EMIT_CharLine(out_character, out_count,
							output_function, output_control);

						int                    out_character;

						unsigned int           out_count;

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;

   DESCRIPTION :	Emits one or more characters to the specified output
						handler.

						After the function has emitted the specified number of
						characters, it will emit a line-feed (ASCII 10).

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``out_character`` is the character to be emitted.

						(.) ``out_count`` is the number of times the character is
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

   NOTES       :	If you want the characters emitted by this function to be
						terminated by a space character, use the related function
						``STR_EMIT_CharSpace``.

						If you want to emit strings instead of characters, use the
						related function ``STR_EMIT_StringLine``.

   CAVEATS     :	

   SEE ALSO    :	STR_EMIT_Char
						STR_EMIT_CharSpace
						STR_EMIT_StringLine

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1992 - 2015 Michael L. Brock

   OUTPUT INDEX:	STR_EMIT_CharLine
						Miscellaneous Functions:STR_EMIT_CharLine
						STRFUNCS:Functions:STR_EMIT_CharLine
						STRFUNCS Miscellaneous Functions:STR_EMIT_CharLine
						General Functions:See STRFUNCS

   PUBLISH XREF:	STR_EMIT_CharLine

   PUBLISH NAME:	STR_EMIT_CharLine

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void STR_EMIT_CharLine(int out_character, unsigned int out_count,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
void STR_EMIT_CharLine(out_character, out_count, output_function,
	output_control)
int                    out_character;
unsigned int           out_count;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	STR_EMIT_SetDefaults(&output_function, &output_control);

	STR_EMIT_Char(out_character, out_count, output_function, output_control);
	(*output_function)(output_control, "\n");
}
/*	***********************************************************************	*/

