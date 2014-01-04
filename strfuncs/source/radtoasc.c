/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	STRFUNCS String and Memory Functions Library Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Converts a RADIX-50 array to an ASCII string.

	Revision History	:	1990-06-04 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1990 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Necessary include files . . .														*/
/* *********************************************************************** */

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Externally-defined data items . . .												*/
/* *********************************************************************** */
COMPAT_EXTERN_DATA_DECL unsigned char RADIX50_Radix50Table[];
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	RADIX50_radtoasc

	SYNOPSIS		:	out_ascii_string = RADIX50_radtoasc(in_rad, out_asc,
							rad_len);

						char               *out_ascii_string;

						const RADIX50_ITEM *in_rad;

						char               *out_asc;

						unsigned int        rad_len;

	DESCRIPTION	:	Converts a RADIX-50 array to an ASCII string using the
						default RADIX-50-to-ASCII mapping table.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_rad`` is the RADIX-50 array to be converted.

						(.) ``out_asc`` points to area of memory into which is to
						be placed the ASCII string resulting from the conversion.

	RETURNS		:	Returns a pointer to string resulting from the conversion
						(that is, ``out_asc`` is returned).

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	RADIX50_radtoasc_basic
						RADIX50_asctorad

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1990 - 2014 Michael L. Brock

	OUTPUT INDEX:	RADIX50_radtoasc
						STRFUNCS:RADIX-50 Functions:RADIX50_radtoasc
						RADIX-50 Functions:RADIX50_radtoasc
						String Functions:See STRFUNCS

	PUBLISH XREF:	RADIX50_radtoasc

	PUBLISH NAME:	RADIX50_radtoasc

	ENTRY CLASS	:	RADIX-50 Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *RADIX50_radtoasc(const RADIX50_ITEM *in_rad, char *out_asc,
	unsigned int rad_len)
#else
char *RADIX50_radtoasc(in_rad, out_asc, rad_len)
const RADIX50_ITEM *in_rad;
char               *out_asc;
unsigned int        rad_len;
#endif /* #ifndef NARGS */
{
	return(RADIX50_radtoasc_basic(in_rad, out_asc, rad_len,
		RADIX50_Radix50Table));
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	RADIX50_radtoasc_basic

	SYNOPSIS		:	out_ascii_string = RADIX50_radtoasc_basic(in_rad, out_asc,
							rad_len, radix50_table);

						char                *out_ascii_string;

						const RADIX50_ITEM  *in_rad;

						char                *out_asc;

						unsigned int         rad_len;

						const unsigned char *radix50_table;

	DESCRIPTION	:	Converts a RADIX-50 array to an ASCII string using the
						RADIX-50-to-ASCII mapping table specified by the
						``radix50_table`` parameter.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_rad`` is the RADIX-50 array to be converted.

						(.) ``out_asc`` points to area of memory into which is to
						be placed the ASCII string resulting from the conversion.

						(.) ``radix50_table`` points to RADIX-50-to-ASCII mapping
						table to be used for the conversion.

						(-) If ``radix50_table`` is ''NULL'', the default
						RADIX-50-to-ASCII mapping table is used.

						(-) An RADIX-50-to-ASCII mapping table can be initialized
						using the function ``RADIX50_init_tables``.

	RETURNS		:	Returns a pointer to string resulting from the conversion
						(that is, ``out_asc`` is returned).

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	RADIX50_radtoasc
						RADIX50_asctorad_basic

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1990 - 2014 Michael L. Brock

	OUTPUT INDEX:	RADIX50_radtoasc_basic
						STRFUNCS:RADIX-50 Functions:RADIX50_radtoasc_basic
						RADIX-50 Functions:RADIX50_radtoasc_basic
						String Functions:See STRFUNCS

	PUBLISH XREF:	RADIX50_radtoasc_basic

	PUBLISH NAME:	RADIX50_radtoasc_basic

	ENTRY CLASS	:	RADIX-50 Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *RADIX50_radtoasc_basic(const RADIX50_ITEM *in_rad, char *out_asc,
	unsigned int rad_len, const unsigned char *radix50_table)
#else
char *RADIX50_radtoasc_basic(in_rad, out_asc, rad_len, radix50_table)
const RADIX50_ITEM  *in_rad;
char                *out_asc;
unsigned int         rad_len;
const unsigned char *radix50_table;
#endif /* #ifndef NARGS */
{
	unsigned int   count_1;
	unsigned char *temp_ptr = ((unsigned char *) out_asc);

	radix50_table = (radix50_table != NULL) ? radix50_table :
		RADIX50_Radix50Table;

	for (count_1 = 0; count_1 < rad_len; count_1++) {
		*temp_ptr++ =
			radix50_table[((int) ((unsigned short *) in_rad)[count_1]) /
				1600];
		*temp_ptr++ =
			radix50_table[(((int) ((unsigned short *) in_rad)[count_1]) %
				1600) / 40];
		*temp_ptr++ =
			radix50_table[((int) ((unsigned short *) in_rad)[count_1]) % 40];
	}

	*temp_ptr = '\0';

	return(out_asc);
}
/* *********************************************************************** */

