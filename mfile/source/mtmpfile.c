/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MFILE Memory-mapped I/O Library Source Code Module								*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Creates a temporary memory-mapped file.

	Revision History	:	1994-07-29 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/
 
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include "mfilei.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  mtmpfile

   SYNOPSIS    :  mfile_ptr = mtmpfile(dir_name, file_prefix);

						MFILE      *mfile_ptr;

						const char *dir_name;

						const char *file_prefix;

   DESCRIPTION :  Opens the file specified by the ``file_name`` parameter
						for memory-mapped access. If the file exists and has a
						file length greater than zero, the file is mapped into
						the address space of the invoking process.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``dir_name`` specifies the directory in which the
						temporary file is to be opened.

						(-) if ``dir_name`` is ''NULL'' or if it points to a string
						which is not an accessible directory, the directory name
						specified by the manifest constant ''P_tmpdir'' in the
						include file ``stdio.h`` is used. If that directory in turn
						is not accessible, the directory ``/tmp`` will be used.

						(-) Note, however, that if the environment variable
						''TMPDIR'' is defined, the value of that variable will be
						used as the fall-back directory when ``dir_name`` is
						''NULL'' or is not accessible.

						(.) ``file_prefix`` allows the application programmer to
						preface the temporary file with a string of up to five
						characters.

						(-) This parameter may be ''NULL'', in which case no
						prefix is prepended to the temporary file name.

   RETURNS     :  Returns from this function are as follow:

						(.) A pointer to the ''MFILE'' structure representing the
						file if the open succeeds.

						(.) ''NULL'' if an error occurred.

   NOTES       :  This function calls ``tempnam`` to construct the name of
						temporary file to be opened and the various fall-back
						behaviors are a result of the semantics of ``tempnam``.

   CAVEATS     :  

   SEE ALSO    :  mopen
						mclose
						munlink

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2015 Michael L. Brock

	OUTPUT INDEX:	mtmpfile
						Memory-mapped File Functions:Open Functions:mtmpfile
						MFILE Functions:mtmpfile

	PUBLISH XREF:	mtmpfile

	PUBLISH NAME:	mtmpfile

	ENTRY CLASS	:	Memory-mapped File Functions:Open Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
MFILE *mtmpfile(const char *dir_name, const char *file_prefix)
#else
MFILE *mtmpfile(dir_name, file_prefix)
const char *dir_name;
const char *file_prefix;
#endif /* #ifndef NARGS */
{
	MFILE *return_ptr = NULL;
	char  *file_name;

	if ((file_name = tempnam(((char *) dir_name), ((char *) file_prefix))) !=
		NULL) {
		return_ptr = mopen(file_name, "w");
		free(file_name);
	}

	return(return_ptr);
}
/* *********************************************************************** */

