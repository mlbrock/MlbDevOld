/* *********************************************************************** */
/* *********************************************************************** */
/*	Network Programming Support Library (NPSL) Source Module						*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initiate a connection on a socket.

	Revision History	:	1993-04-12 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/*    Include necessary header files . . .                                 */
/* *********************************************************************** */
 
#include <string.h>

#include "npsli.h"

/* *********************************************************************** */

/* *********************************************************************** */
int NPSL_Connect(NPSL_SOCKET_HANDLE socket_handle,
	const NPSL_SOCKADDR *name, NPSL_SOCKLEN_T addrlen, char *error_text)
{
	int return_code;

	if ((return_code = NPSL_SocketLibStartUp(NULL, error_text)) ==
		NPSL_SUCCESS) {
		if (connect(socket_handle, name, addrlen) != NPSL_SOCKET_OK) {
			if (error_text != NULL)
				NPSL_AppendLastErrorString(0, NPSL_MAX_ERROR_TEXT,
					strcpy(error_text,
	"Attempt to initiate a connection on a socket with 'connect()' failed: "));
			return_code = NPSL_SUPP_MapLastError();
		}
		NPSL_SocketLibCleanUp(NULL, NULL);
	}

	return(return_code);
}
/* *********************************************************************** */


