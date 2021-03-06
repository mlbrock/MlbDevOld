/* *********************************************************************** */
/* *********************************************************************** */
/*	Network Programming Support Library (NPSL) Source Module						*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Send a message on a socket.

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
int NPSL_Send(NPSL_SOCKET_HANDLE socket_handle, const char *buffer,
	unsigned int buffer_length, int flags, unsigned int *send_count,
	char *error_text)
{
	int                  return_code;
	NPSL_SEND_RECV_LEN_T data_length;

	*send_count = 0;

	if (buffer_length > ((unsigned int) INT_MAX)) {
		if (error_text != NULL)
			sprintf(error_text, "%s (%u) %s (%d).",
				"The specified buffer length", buffer_length,
				"exceeds the maximum permissible signed integer value", INT_MAX);
		return_code = NPSL_FAILURE;
	}
	else if ((return_code = NPSL_SocketLibStartUp(NULL, error_text)) ==
		NPSL_SUCCESS) {
		if ((data_length = send(socket_handle, buffer, ((int) buffer_length),
			flags)) != NPSL_SOCKET_ERROR)
			*send_count = ((unsigned int) data_length);
		else {
			if (error_text != NULL)
				NPSL_AppendLastErrorString(0, NPSL_MAX_ERROR_TEXT,
					strcpy(error_text,
"Attempt to send a message on a socket with 'send()' failed: "));
			return_code = NPSL_SUPP_MapLastError();
		}
		NPSL_SocketLibCleanUp(NULL, NULL);
	}

	return(return_code);
}
/* *********************************************************************** */

