/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Sybase CT-Library Support Functions Library Module						*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Intercepts Sybase CT-LIB messages and errors.

	Revision History	:	1996-06-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Required include files . . .														*/
/*	***********************************************************************	*/

#include <memory.h>
#include <string.h>

#include "dbcctlii.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_CTLIB_MSG_ClearMsg

   SYNOPSIS    :	void DBC_CTLIB_MSG_ClearMsg(dbc_control_ptr);

						DBC_CTLIB *dbc_control_ptr;

   DESCRIPTION :	Clears the current server and client messages.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``dbc_control_ptr`` is a pointer to the
						''DBC_CTLIB'' structure to be used to manage
						communication with the database. It is assumed by this
						function that the structure has been properly initialized
						by ``DBC_CTLIB_Initialize`` and that a connection to a
						Sybase database has been performed by ``DBC_CTLIB_Open``.

   RETURNS     :	Returns from this function are as follow:

   NOTES       :	This function is called by the internal DBC Sybase CT-LIB
						facility functions. There is little need for application
						programmers to call it directly.

   CAVEATS     :	

   SEE ALSO    :	

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2015 Michael L. Brock

   OUTPUT INDEX:	DBC_CTLIB_MSG_ClearMsg
						DBC Sybase CT-LIB Functions:DBC_CTLIB_MSG_ClearMsg
						DBC Functions:Message Handler Functions:DBC_CTLIB_MSG_ClearMsg

   PUBLISH XREF:	DBC_CTLIB_MSG_ClearMsg

   PUBLISH NAME:	DBC_CTLIB_MSG_ClearMsg

	ENTRY CLASS	:	DBC Functions:Message Handler Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void DBC_CTLIB_MSG_ClearMsg(DBC_CTLIB *dbc_control_ptr)
#else
void DBC_CTLIB_MSG_ClearMsg(dbc_control_ptr)
DBC_CTLIB *dbc_control_ptr;
#endif /* #ifndef NARGS */
{
	dbc_control_ptr->server_msg[0] = '\0';
	dbc_control_ptr->client_msg[0] = '\0';
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_CTLIB_MSG_GetCombinedMsg

   SYNOPSIS    :	return_ptr = DBC_CTLIB_MSG_GetCombinedMsg(dbc_control_ptr,
							text_buffer);

						char      *return_ptr;

						DBC_CTLIB *dbc_control_ptr;

						char      *text_buffer;

   DESCRIPTION :	Concatenates the most-recent Sybase server and client
						message into ``text_buffer``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``dbc_control_ptr`` is a pointer to the
						''DBC_CTLIB'' structure to be used to manage
						communication with the database. It is assumed by this
						function that the structure has been properly initialized
						by ``DBC_CTLIB_Initialize`` and that a connection to a
						Sybase database has been performed by ``DBC_CTLIB_Open``.

						(.) ``text_buffer`` is the area of memory into which the
						message text is to be copied by this function.

   RETURNS     :	Returns the ``text_buffer`` parameter.

   NOTES       :	This function is called by the internal DBC Sybase CT-LIB
						facility functions. There is little need for application
						programmers to call it directly.

   CAVEATS     :	

   SEE ALSO    :	DBC_CTLIB_MSG_GetServerMsg
						DBC_CTLIB_MSG_GetClientMsg

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2015 Michael L. Brock

   OUTPUT INDEX:	DBC_CTLIB_MSG_GetCombinedMsg
						DBC Sybase CT-LIB Functions:DBC_CTLIB_MSG_GetCombinedMsg
						DBC Functions:Message Handler Functions:DBC_CTLIB_MSG_GetCombinedMsg

   PUBLISH XREF:	DBC_CTLIB_MSG_GetCombinedMsg

   PUBLISH NAME:	DBC_CTLIB_MSG_GetCombinedMsg

	ENTRY CLASS	:	DBC Functions:Message Handler Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *DBC_CTLIB_MSG_GetCombinedMsg(DBC_CTLIB *dbc_control_ptr,
	char *text_buffer)
#else
char *DBC_CTLIB_MSG_GetCombinedMsg(dbc_control_ptr, text_buffer)
DBC_CTLIB *dbc_control_ptr;
char      *text_buffer;
#endif /* #ifndef NARGS */
{
	*text_buffer = '\0';

	if (*dbc_control_ptr->server_msg)
		strcat(nstrcat(text_buffer, dbc_control_ptr->server_msg,
			(DBC_MAX_ERROR_TEXT / 2) - 10),
			(*dbc_control_ptr->client_msg) ? " --- " : "");

	if (*dbc_control_ptr->client_msg)
		nstrcat(text_buffer, dbc_control_ptr->client_msg,
			DBC_MAX_ERROR_TEXT - (strlen(text_buffer) + 1));

	return(text_buffer);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_CTLIB_MSG_GetServerMsg

   SYNOPSIS    :	return_ptr = DBC_CTLIB_MSG_GetServerMsg(dbc_control_ptr,
							text_buffer);

						char      *return_ptr;

						DBC_CTLIB *dbc_control_ptr;

						char      *text_buffer;

   DESCRIPTION :	Copies the most-recent Sybase server message into
						``text_buffer``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``dbc_control_ptr`` is a pointer to the
						''DBC_CTLIB'' structure to be used to manage
						communication with the database. It is assumed by this
						function that the structure has been properly initialized
						by ``DBC_CTLIB_Initialize`` and that a connection to a
						Sybase database has been performed by ``DBC_CTLIB_Open``.

						(.) ``text_buffer`` is the area of memory into which the
						message text is to be copied by this function.

   RETURNS     :	Returns the ``text_buffer`` parameter.

   NOTES       :	This function is called by the internal DBC Sybase CT-LIB
						facility functions. There is little need for application
						programmers to call it directly.

   CAVEATS     :	

   SEE ALSO    :	DBC_CTLIB_MSG_GetCombinedMsg
						DBC_CTLIB_MSG_GetClientMsg

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2015 Michael L. Brock

   OUTPUT INDEX:	DBC_CTLIB_MSG_GetServerMsg
						DBC Sybase CT-LIB Functions:DBC_CTLIB_MSG_GetServerMsg
						DBC Functions:Message Handler Functions:DBC_CTLIB_MSG_GetServerMsg

   PUBLISH XREF:	DBC_CTLIB_MSG_GetServerMsg

   PUBLISH NAME:	DBC_CTLIB_MSG_GetServerMsg

	ENTRY CLASS	:	DBC Functions:Message Handler Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *DBC_CTLIB_MSG_GetServerMsg(DBC_CTLIB *dbc_control_ptr,
	char *text_buffer)
#else
char *DBC_CTLIB_MSG_GetServerMsg(dbc_control_ptr, text_buffer)
DBC_CTLIB *dbc_control_ptr;
char      *text_buffer;
#endif /* #ifndef NARGS */
{
	return(nstrcpy(text_buffer, dbc_control_ptr->server_msg,
		DBC_MAX_ERROR_TEXT - 1));
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_CTLIB_MSG_GetClientMsg

   SYNOPSIS    :	return_ptr = DBC_CTLIB_MSG_GetClientMsg(dbc_control_ptr,
							text_buffer);

						char      *return_ptr;

						DBC_CTLIB *dbc_control_ptr;

						char      *text_buffer;

   DESCRIPTION :	Copies the most-recent Sybase client message into
						``text_buffer``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``dbc_control_ptr`` is a pointer to the
						''DBC_CTLIB'' structure to be used to manage
						communication with the database. It is assumed by this
						function that the structure has been properly initialized
						by ``DBC_CTLIB_Initialize`` and that a connection to a
						Sybase database has been performed by ``DBC_CTLIB_Open``.

						(.) ``text_buffer`` is the area of memory into which the
						message text is to be copied by this function.

   RETURNS     :	Returns the ``text_buffer`` parameter.

   NOTES       :	This function is called by the internal DBC Sybase CT-LIB
						facility functions. There is little need for application
						programmers to call it directly.

   CAVEATS     :	

   SEE ALSO    :	DBC_CTLIB_MSG_GetCombinedMsg
						DBC_CTLIB_MSG_GetServerMsg

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2015 Michael L. Brock

   OUTPUT INDEX:	DBC_CTLIB_MSG_GetClientMsg
						DBC Sybase CT-LIB Functions:DBC_CTLIB_MSG_GetClientMsg
						DBC Functions:Message Handler Functions:DBC_CTLIB_MSG_GetClientMsg

   PUBLISH XREF:	DBC_CTLIB_MSG_GetClientMsg

   PUBLISH NAME:	DBC_CTLIB_MSG_GetClientMsg

	ENTRY CLASS	:	DBC Functions:Message Handler Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *DBC_CTLIB_MSG_GetClientMsg(DBC_CTLIB *dbc_control_ptr,
	char *text_buffer)
#else
char *DBC_CTLIB_MSG_GetClientMsg(dbc_control_ptr, text_buffer)
DBC_CTLIB *dbc_control_ptr;
char      *text_buffer;
#endif /* #ifndef NARGS */
{
	return(nstrcpy(text_buffer, dbc_control_ptr->client_msg,
		DBC_MAX_ERROR_TEXT - 1));
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_CTLIB_ServerMsgCB

   SYNOPSIS    :	return_code = DBC_CTLIB_ServerMsgCB(context, connection,
							message);

						CS_RETCODE     return_code;

						CS_CONTEXT    *context;

						CS_CONNECTION *connection;

						CS_SERVERMSG  *message;

   DESCRIPTION :	The Sybase CT-LIB server message call-back function.

						This function is called only from with the Sybase DB-LIB
						implementation.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``context`` is a pointer to the ''CS_CONTEXT''
						structure associated with the message.

						(.) ``connection`` is a pointer to the ''CS_CONNECTION''
						structure associated with the message.

						(.) ``message`` is a pointer to the ''CS_SERVERMSG''
						structure which describes the message.

   RETURNS     :	Always returns ''CS_SUCCEED''.

   NOTES       :	This function is called by the internal Sybase CT-LIB
						library functions. There is no need for application
						programmers to call it directly.

   CAVEATS     :	

   SEE ALSO    :	DBC_CTLIB_ClientMsgCB

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2015 Michael L. Brock

   OUTPUT INDEX:	DBC_CTLIB_ServerMsgCB
						DBC Sybase CT-LIB Functions:DBC_CTLIB_ServerMsgCB
						DBC Functions:Message Handler Functions:DBC_CTLIB_ServerMsgCB

   PUBLISH XREF:	DBC_CTLIB_ServerMsgCB

   PUBLISH NAME:	DBC_CTLIB_ServerMsgCB

	ENTRY CLASS	:	DBC Functions:Message Handler Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
CS_RETCODE DBC_CTLIB_ServerMsgCB(CS_CONTEXT *context,
	CS_CONNECTION *connection, CS_SERVERMSG *message)
#else
CS_RETCODE DBC_CTLIB_ServerMsgCB(context, connection, message)
CS_CONTEXT    *context;
CS_CONNECTION *connection;
CS_SERVERMSG  *message;
#endif /* #ifndef NARGS */
{
	DBC_CTLIB    *dbc_control_ptr;
	CS_INT        out_length;
   unsigned int  msg_length;

	/*	*** Get user data ptr *** */
	if (ct_con_props(connection, CS_GET, CS_USERDATA, &dbc_control_ptr,
		sizeof(&dbc_control_ptr), &out_length) != CS_SUCCEED)
		goto EXIT_FUNCTION;

	sprintf(dbc_control_ptr->server_msg,
		"%s: %s %ld, %s %d, %s %d, %s '%-.*s', %s '%-.*s', %s %d: %s",
		"SERVER MESSAGE",
		"Message", message->msgnumber,
		"State", ((int) message->state),
		"Severity Level", ((int) message->severity),
		"Server Name", ((int) message->svrnlen), message->svrname,
		"Procedure Name", ((int) message->proclen), message->proc,
		"Line Number", ((int) message->line),
		message->text);

	/*	*****************************************************************
		*****************************************************************
		Sybase CT-LIB likes to add a trailing line feed to the message.
		*****************************************************************	*/
	if (dbc_control_ptr->server_msg[strlen(dbc_control_ptr->server_msg) - 1] ==
		'\n')
		dbc_control_ptr->server_msg[strlen(dbc_control_ptr->server_msg) - 1] =
			'\0';
	/*	*****************************************************************	*/

	if ((message->msgnumber == 3621) && *message->text &&
		((msg_length = strlen(dbc_control_ptr->server_msg)) <
		DBC_MAX_ERROR_TEXT))
		nstrcat(dbc_control_ptr->server_msg,
			" --- Command has been aborted.",
			DBC_MAX_ERROR_TEXT - (msg_length + 1));

	if ((dbc_control_ptr->mlog_ptr != NULL) &&
		(dbc_control_ptr->flags & DBC_FLAG_DEBUG_NORMAL))
		MLOG_LogInfo(dbc_control_ptr->mlog_ptr, "%s\n",
			dbc_control_ptr->server_msg);

EXIT_FUNCTION:

	return(CS_SUCCEED);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_CTLIB_ClientMsgCB

   SYNOPSIS    :	return_code = DBC_CTLIB_ClientMsgCB(context, connection,
							message);

						CS_RETCODE     return_code;

						CS_CONTEXT    *context;

						CS_CONNECTION *connection;

						CS_CLIENTMSG  *message;

   DESCRIPTION :	The Sybase CT-LIB client message call-back function.

						This function is called only from with the Sybase DB-LIB
						implementation.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``context`` is a pointer to the ''CS_CONTEXT''
						structure associated with the message.

						(.) ``connection`` is a pointer to the ''CS_CONNECTION''
						structure associated with the message.

						(.) ``message`` is a pointer to the ''CS_CLIENTMSG''
						structure which describes the message.

   RETURNS     :	Always returns ''CS_SUCCEED''.

   NOTES       :	This function is called by the internal Sybase CT-LIB
						library functions. There is no need for application
						programmers to call it directly.

   CAVEATS     :	

   SEE ALSO    :	DBC_CTLIB_ServerMsgCB

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2015 Michael L. Brock

   OUTPUT INDEX:	DBC_CTLIB_ClientMsgCB
						DBC Sybase CT-LIB Functions:DBC_CTLIB_ClientMsgCB
						DBC Functions:Message Handler Functions:DBC_CTLIB_ClientMsgCB

   PUBLISH XREF:	DBC_CTLIB_ClientMsgCB

   PUBLISH NAME:	DBC_CTLIB_ClientMsgCB

	ENTRY CLASS	:	DBC Functions:Message Handler Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
CS_RETCODE DBC_CTLIB_ClientMsgCB(CS_CONTEXT *context,
	CS_CONNECTION *connection, CS_CLIENTMSG *message)
#else
CS_RETCODE DBC_CTLIB_ClientMsgCB(context, connection, message)
CS_CONTEXT    *context;
CS_CONNECTION *connection;
CS_CLIENTMSG  *message;
#endif /* #ifndef NARGS */
{
	DBC_CTLIB *dbc_control_ptr;
   CS_INT     out_length;

	/*	*** Get user data ptr *** */
	if (ct_con_props(connection, CS_GET, CS_USERDATA, &dbc_control_ptr,
		sizeof(&dbc_control_ptr), &out_length) != CS_SUCCEED)
		goto EXIT_FUNCTION;

	sprintf(dbc_control_ptr->client_msg,
		"%s: %s %ld, %s %ld, %s %ld, %s %ld, %s: %s",
		"CLIENT MESSAGE",
		"message layer", CS_LAYER(message->msgnumber),
		"message origin", CS_ORIGIN(message->msgnumber),
		"message severity", CS_SEVERITY(message->msgnumber),
		"message number", CS_NUMBER(message->msgnumber),
		"message string", message->msgstring);

	if (message->osstringlen)
		nstrcat(strcat(dbc_control_ptr->client_msg, " --- OS ERROR: "),
			message->osstring, DBC_MAX_ERROR_TEXT -
			(strlen(dbc_control_ptr->client_msg) + 20));

	if ((dbc_control_ptr->mlog_ptr != NULL) &&
		(dbc_control_ptr->flags & DBC_FLAG_DEBUG_NORMAL))
		MLOG_LogErr(dbc_control_ptr->mlog_ptr, "%s\n",
			dbc_control_ptr->client_msg);

EXIT_FUNCTION:

	return(CS_SUCCEED);
}
/*	***********************************************************************	*/

