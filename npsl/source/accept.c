/* *********************************************************************** */
/* *********************************************************************** */
/*	Network Programming Support Library (NPSL) Source Module						*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Accept a communication on a socket.

	Revision History	:	1993-04-12 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2018.
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
int NPSL_Accept(NPSL_SOCKET_HANDLE in_socket_handle,
	NPSL_SOCKET_HANDLE *out_socket_handle, NPSL_SOCKADDR *addr,
	NPSL_SOCKLEN_T *addrlen, char *error_text)
{
	int return_code;

	*out_socket_handle = NPSL_INVALID_SOCKET;

	if ((return_code = NPSL_SocketLibStartUp(NULL, error_text)) ==
		NPSL_SUCCESS) {
		if ((*out_socket_handle = accept(in_socket_handle, addr,
			addrlen)) == NPSL_INVALID_SOCKET) {
			if (error_text != NULL)
				NPSL_AppendLastErrorString(0, NPSL_MAX_ERROR_TEXT,
					strcpy(error_text,
		"Attempt to accept a socket connection with 'accept()' failed: "));
			return_code = NPSL_SUPP_MapLastError();
		}
		NPSL_SocketLibCleanUp(NULL, NULL);
	}

	return(return_code);
}
/* *********************************************************************** */


