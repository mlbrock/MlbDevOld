/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	GENFUNCS General Functions Library Source Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Maps parameter values to their string equivalent.

	Revision History	:	1995-06-14 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2015.
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

#include <strfuncs.h>

#include "genfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_GetBooleanString

   SYNOPSIS    :	return_ptr = GEN_GetBooleanString(boolean_value,
							boolean_string);

						char *return_ptr;

						int   boolean_value;

						char *boolean_string;

   DESCRIPTION :	Returns a string descriptive of a GENFUNCS truth code.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``boolean_value`` is the GENFUNCS truth code which
						this function is to return as a string.

						(.) ``boolean_string`` is the string into which this
						function is to place the formatted boolean string.

						(..) If ``boolean_value`` is equal to ''GENFUNCS_TRUE'',
						the string ''TRUE'' will be placed into ``boolean_string``.

						(..) If ``boolean_value`` is equal to ''GENFUNCS_FALSE'',
						the string ''FALSE'' will be placed into ``boolean_string``.

						(..) Otherwise, the string ''*** INVALID ***'' will be
						placed into ``boolean_string``.

						(-) The memory allocated for ``boolean_string`` should be
						at least ''16'' characters in length.

   RETURNS     :	Returns a pointer to the formatted string
						``boolean_string``.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1995 - 2015 Michael L. Brock

   OUTPUT INDEX:	GEN_GetBooleanString
						Argument Parsing Functions:GEN_GetBooleanString
						GENFUNCS:Functions:GEN_GetBooleanString
						GENFUNCS:Argument Parsing Functions:GEN_GetBooleanString
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_GetBooleanString

   PUBLISH NAME:	GEN_GetBooleanString

	ENTRY CLASS	:	Argument Parsing Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *GEN_GetBooleanString(int boolean_value, char *boolean_string)
#else
char *GEN_GetBooleanString(boolean_value, boolean_string)
int   boolean_value;
char *boolean_string;
#endif /* #ifndef NARGS */
{
	return(nstrcpy(boolean_string, (boolean_value == GENFUNCS_TRUE) ? "TRUE" :
		(boolean_value == GENFUNCS_FALSE) ? "FALSE" : "*** INVALID ***", 15));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_GetDebugLevel

   SYNOPSIS    :	return_ptr = GEN_GetDebugLevel(debug_level,
							debug_level_string);

						char *return_ptr;

						int   debug_level;

						char *debug_level_string;

   DESCRIPTION :	Returns a string descriptive of a GENFUNCS debugging level.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``debug_level`` is the GENFUNCS debugging level which
						this function is to return as a string.

						(.) ``debug_level_string`` is the string into which this
						function is to place the formatted debug_level string.

						(..) If ``debug_level`` is equal to
						''GEN_DEBUG_LEVEL_NONE'', the string ''NONE'' will be
						placed into ``debug_level_string``.

						(..) If ``debug_level`` is equal to
						''GEN_DEBUG_LEVEL_BASIC'', the string ''BASIC'' will be
						placed into ``debug_level_string``.

						(..) If ``debug_level`` is equal to
						''GEN_DEBUG_LEVEL_COMPLETE'', the string ''COMPLETE''
						will be placed into ``debug_level_string``.

						(..) Otherwise, the string ''*** INVALID ***'' will be
						placed into ``debug_level_string``.

						(-) The memory allocated for ``debug_level_string`` should
						be at least ''16'' characters in length.

   RETURNS     :	Returns a pointer to the formatted string
						``debug_level_string``.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1995 - 2015 Michael L. Brock

   OUTPUT INDEX:	GEN_GetDebugLevel
						Argument Parsing Functions:GEN_GetDebugLevel
						GENFUNCS:Functions:GEN_GetDebugLevel
						GENFUNCS:Argument Parsing Functions:GEN_GetDebugLevel
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_GetDebugLevel

   PUBLISH NAME:	GEN_GetDebugLevel

	ENTRY CLASS	:	Argument Parsing Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *GEN_GetDebugLevel(int debug_level, char *debug_level_string)
#else
char *GEN_GetDebugLevel(debug_level, debug_level_string)
int   debug_level;
char *debug_level_string;
#endif /* #ifndef NARGS */
{
	return(nstrcpy(debug_level_string,
		(debug_level == GEN_DEBUG_LEVEL_NONE)     ? "NONE"     :
		(debug_level == GEN_DEBUG_LEVEL_BASIC)    ? "BASIC"    :
		(debug_level == GEN_DEBUG_LEVEL_COMPLETE) ? "COMPLETE" :
		"*** INVALID ***", 15));
}
/*	***********************************************************************	*/

