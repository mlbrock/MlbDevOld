/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Sybase DB-Library Support Functions Library Module						*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Intercepts Sybase messages and errors for the Sybase
								DB-LIB facility.

	Revision History	:	1993-07-07 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2018.
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

#include "dbcdblii.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Data private to this module . . .												*/
/*	***********************************************************************	*/

static unsigned int   DBC_DBLIB_MSG_HandlerStackCount = 0;

static DBC_DBLIB_MSG *DBC_DBLIB_MSG_HandlerStackList  = NULL;

/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_DBLIB_MSG_DefaultHandler

   SYNOPSIS    :	return_code = DBC_DBLIB_MSG_DefaultHandler(dbc_control_ptr,
							error_text);

						int        return_code;

						DBC_DBLIB *dbc_control_ptr;

						char      *error_text;

   DESCRIPTION :	Pushes a ''DBC_DBLIB_MSG'' structure containing the default
						Sybase DB-LIB error and message handlers onto the stack.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``dbc_control_ptr`` is a pointer to the
						''DBC_DBLIB'' structure to be used to manage
						communication with the database. It is assumed by this
						function that the structure has been properly initialized
						by ``DBC_DBLIB_Initialize`` and that a connection to a
						Sybase database has been performed by ``DBC_DBLIB_Open``.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''DBC_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	This function returns a DBC return codes manifest constant:

						(.) ''DBC_SUCCESS'' if the function completes without
						error.

						(.) One of the defined non-zero DBC return codes indicative
						of error.

   NOTES       :	This function is called by the internal DBC Sybase DB-LIB
						facility functions. There is little need for application
						programmers to call it directly.

   CAVEATS     :	

   SEE ALSO    :	DBC_DBLIB_MSG_PushHandler

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	DBC_DBLIB_MSG_DefaultHandler
						DBC Sybase DB-LIB Functions:DBC_DBLIB_MSG_DefaultHandler
						DBC Functions:Message Handler Functions:DBC_DBLIB_MSG_DefaultHandler

   PUBLISH XREF:	DBC_DBLIB_MSG_DefaultHandler

   PUBLISH NAME:	DBC_DBLIB_MSG_DefaultHandler

	ENTRY CLASS	:	DBC Functions:Message Handler Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int DBC_DBLIB_MSG_DefaultHandler(DBC_DBLIB *dbc_control_ptr, char *error_text)
#else
int DBC_DBLIB_MSG_DefaultHandler(dbc_control_ptr, error_text)
DBC_DBLIB *dbc_control_ptr;
char      *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

#ifdef CS_PUBLIC
	if ((return_code =
		DBC_DBLIB_MSG_PushHandler(((EHANDLEFUNC) DBC_DBLIB_MSG_HandleERR),
		((MHANDLEFUNC) DBC_DBLIB_MSG_HandleMSG), error_text)) == DBC_SUCCESS) {
#else
	if ((return_code = DBC_DBLIB_MSG_PushHandler(DBC_DBLIB_MSG_HandleERR,
		DBC_DBLIB_MSG_HandleMSG, error_text)) == DBC_SUCCESS) {
#endif /* #ifdef CS_PUBLIC */
		DBC_DBLIB_MSG_HandlerStackList[DBC_DBLIB_MSG_HandlerStackCount - 1].
			mlog_ptr = dbc_control_ptr->mlog_ptr;
		DBC_DBLIB_MSG_HandlerStackList[DBC_DBLIB_MSG_HandlerStackCount - 1].
			db_debug_flag   = (dbc_control_ptr->flags & DBC_FLAG_DEBUG_NORMAL) ?
			DBC_TRUE : DBC_FALSE;
	}

	return(return_code);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_DBLIB_MSG_PushHandler

   SYNOPSIS    :	return_code = DBC_DBLIB_MSG_PushHandler(err_handler,
							msg_handler, error_text);

						#ifdef CS_PUBLIC

						EHANDLEFUNC   err_handler;

						MHANDLEFUNC   msg_handler;

						#else

						# ifndef NARGS

						int         (*err_handler)(DBPROCESS *, int, int, int,
											char *, char *);

						int         (*msg_handler)(DBPROCESS *, DBINT, int, int,
											char *, char *, char *, DBUSMALLINT);

						# else

						int         (*err_handler)();

						int         (*msg_handler)();

						# endif // #ifndef NARGS

						#endif // #ifdef CS_PUBLIC

						char         *error_text;

   DESCRIPTION :	Pushes the specified Sybase DB-LIB error and message
						handlers onto the ''DBC_DBLIB_MSG'' stack.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``err_handler`` is a pointer to the function which is
						to handle Sybase error call-backs. It is passed unexamined
						to the Sybase DB-LIB function ``dberrhandle()``.

						(.) ``msg_handler`` is a pointer to the function which is
						to handle Sybase message call-backs. It is passed unexamined
						to the Sybase DB-LIB function ``dbmsghandle()``.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''DBC_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	This function returns a DBC return codes manifest constant:

						(.) ''DBC_SUCCESS'' if the function completes without
						error.

						(.) One of the defined non-zero DBC return codes indicative
						of error.

   NOTES       :	Note the '#ifdef CS_PUBLIC' block. This is necessary
						because Sybase DB-LIB prior to Sybase System 10 (such as
						4.9.2) declared the last parameter of message handlers to
						be of type ''DBUSMALLINT'', whereas System 10 and subsequent
						releases declared it to be of type ''int''.

						This function is called by the internal DBC Sybase DB-LIB
						facility functions. There is little need for application
						programmers to call it directly.

   CAVEATS     :	

   SEE ALSO    :	

   EXAMPLES    :	DBC_DBLIB_MSG_PopHandler

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	DBC_DBLIB_MSG_PushHandler
						DBC Sybase DB-LIB Functions:DBC_DBLIB_MSG_PushHandler
						DBC Functions:Message Handler Functions:DBC_DBLIB_MSG_PushHandler

   PUBLISH XREF:	DBC_DBLIB_MSG_PushHandler

   PUBLISH NAME:	DBC_DBLIB_MSG_PushHandler

	ENTRY CLASS	:	DBC Functions:Message Handler Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
# ifdef CS_PUBLIC
int DBC_DBLIB_MSG_PushHandler(EHANDLEFUNC err_handler, MHANDLEFUNC msg_handler,
	char *error_text)
# else
int DBC_DBLIB_MSG_PushHandler(
	int (*err_handler)(DBPROCESS *, int, int, int, char *, char *),
	int (*msg_handler)(DBPROCESS *, DBINT, int, int, char *, char *, char *,
		DBUSMALLINT), char *error_text)
# endif /* # ifdef CS_PUBLIC */
#else
# ifdef CS_PUBLIC
int DBC_DBLIB_MSG_PushHandler(err_handler, msg_handler, error_text)
EHANDLEFUNC  err_handler;
MHANDLEFUNC  msg_handler;
char        *error_text;
# else
int DBC_DBLIB_MSG_PushHandler(err_handler, msg_handler, error_text)
int  (*err_handler)();
int  (*msg_handler)();
char  *error_text;
# endif /* # ifdef CS_PUBLIC */
#endif /* #ifndef NARGS */
{
	int           return_code = DBC_SUCCESS;
	DBC_DBLIB_MSG tmp_db_msg_stack;

	memset(&tmp_db_msg_stack, '\0', sizeof(tmp_db_msg_stack));

	tmp_db_msg_stack.err_handler   = dberrhandle(err_handler);
	tmp_db_msg_stack.msg_handler   = dbmsghandle(msg_handler);
	tmp_db_msg_stack.msg_text[0]   = '\0';
	tmp_db_msg_stack.err_text[0]   = '\0';
	tmp_db_msg_stack.mlog_ptr      = NULL;
	tmp_db_msg_stack.db_debug_flag = DBC_FALSE;

	if (mema_append(&DBC_DBLIB_MSG_HandlerStackCount,
		((void **) &DBC_DBLIB_MSG_HandlerStackList), &tmp_db_msg_stack,
		sizeof(tmp_db_msg_stack)) != STR_LIST_SUCCESS) {
		dberrhandle(tmp_db_msg_stack.err_handler);
		dbmsghandle(tmp_db_msg_stack.msg_handler);
		sprintf(error_text, "%s (%u stack items * %u size = %u total bytes).",
			"Unable to push a database message handler context onto the stack",
			DBC_DBLIB_MSG_HandlerStackCount + 1, sizeof(tmp_db_msg_stack),
			(DBC_DBLIB_MSG_HandlerStackCount + 1) * sizeof(tmp_db_msg_stack));
		return_code = DBC_MEMORY_FAILURE;
	}

	return(return_code);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_DBLIB_MSG_PopHandler

   SYNOPSIS    :	void DBC_DBLIB_MSG_PopHandler();

   DESCRIPTION :	Pops the top-most Sybase message handler stack
						''DBC_DBLIB_MSG''structure off the stack.

   PARAMETERS  :	None.

   RETURNS     :	Void.

   NOTES       :	This function is called by the internal DBC Sybase DB-LIB
						facility functions. There is little need for application
						programmers to call it directly.

   CAVEATS     :	

   SEE ALSO    :	DBC_DBLIB_MSG_PushHandler
						DBC_DBLIB_MSG_ClearHandler

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	DBC_DBLIB_MSG_PopHandler
						DBC Sybase DB-LIB Functions:DBC_DBLIB_MSG_PopHandler
						DBC Functions:Message Handler Functions:DBC_DBLIB_MSG_PopHandler

   PUBLISH XREF:	DBC_DBLIB_MSG_PopHandler

   PUBLISH NAME:	DBC_DBLIB_MSG_PopHandler

	ENTRY CLASS	:	DBC Functions:Message Handler Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void DBC_DBLIB_MSG_PopHandler(void)
#else
void DBC_DBLIB_MSG_PopHandler()
#endif /* #ifndef NARGS */
{
	if (DBC_DBLIB_MSG_HandlerStackCount) {
		dberrhandle(DBC_DBLIB_MSG_HandlerStackList
			[DBC_DBLIB_MSG_HandlerStackCount - 1].err_handler);
		dbmsghandle(DBC_DBLIB_MSG_HandlerStackList
			[DBC_DBLIB_MSG_HandlerStackCount - 1].msg_handler);
		mema_remove(&DBC_DBLIB_MSG_HandlerStackCount,
			((void **) &DBC_DBLIB_MSG_HandlerStackList), sizeof(DBC_DBLIB_MSG),
			DBC_DBLIB_MSG_HandlerStackCount - 1, 1);
	}
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_DBLIB_MSG_ClearHandler

   SYNOPSIS    :	void DBC_DBLIB_MSG_ClearHandler();

   DESCRIPTION :	Removes all Sybase message handler stack ''DBC_DBLIB_MSG''
						structures from the stack.

   PARAMETERS  :	None.

   RETURNS     :	Void.

   NOTES       :	This function is called by the internal DBC Sybase DB-LIB
						facility functions. There is little need for application
						programmers to call it directly.

   CAVEATS     :	

   SEE ALSO    :	

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	DBC_DBLIB_MSG_ClearHandler
						DBC Sybase DB-LIB Functions:DBC_DBLIB_MSG_ClearHandler
						DBC Functions:Message Handler Functions:DBC_DBLIB_MSG_ClearHandler

   PUBLISH XREF:	DBC_DBLIB_MSG_ClearHandler

   PUBLISH NAME:	DBC_DBLIB_MSG_ClearHandler

	ENTRY CLASS	:	DBC Functions:Message Handler Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void DBC_DBLIB_MSG_ClearHandler(void)
#else
void DBC_DBLIB_MSG_ClearHandler()
#endif /* #ifndef NARGS */
{
	if (DBC_DBLIB_MSG_HandlerStackCount) {
		mema_remove_all(&DBC_DBLIB_MSG_HandlerStackCount,
			((void **) &DBC_DBLIB_MSG_HandlerStackList));
		dberrhandle(NULL);
		dbmsghandle(NULL);
	}
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_DBLIB_MSG_GetHandlerPtr

   SYNOPSIS    :	return_ptr = DBC_DBLIB_MSG_GetHandlerPtr();

						DBC_DBLIB_MSG *return_ptr;

   DESCRIPTION :	Returns a pointer to the top-most ''DBC_DBLIB_MSG''
						structure on the stack.

   PARAMETERS  :	None.

   RETURNS     :	Returns a pointer to the top-most ''DBC_DBLIB_MSG''
						structure on the stack.

						Of course, if the stack is empty, this function will
						return a ''NULL'' pointer.

   NOTES       :	This function is called by the internal DBC Sybase DB-LIB
						facility functions. There is little need for application
						programmers to call it directly.

   CAVEATS     :	

   SEE ALSO    :	

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	DBC_DBLIB_MSG_GetHandlerPtr
						DBC Sybase DB-LIB Functions:DBC_DBLIB_MSG_GetHandlerPtr
						DBC Functions:Message Handler Functions:DBC_DBLIB_MSG_GetHandlerPtr

   PUBLISH XREF:	DBC_DBLIB_MSG_GetHandlerPtr

   PUBLISH NAME:	DBC_DBLIB_MSG_GetHandlerPtr

	ENTRY CLASS	:	DBC Functions:Message Handler Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
DBC_DBLIB_MSG *DBC_DBLIB_MSG_GetHandlerPtr(void)
#else
DBC_DBLIB_MSG *DBC_DBLIB_MSG_GetHandlerPtr()
#endif /* #ifndef NARGS */
{
	return((!DBC_DBLIB_MSG_HandlerStackCount) ? NULL :
		(DBC_DBLIB_MSG_HandlerStackList +
		(DBC_DBLIB_MSG_HandlerStackCount - 1)));
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_DBLIB_MSG_GetHandlerMessage

   SYNOPSIS    :	return_ptr = DBC_DBLIB_MSG_GetHandlerMessage(text_buffer);

						char *return_ptr;

						char *text_buffer;

   DESCRIPTION :	Concatenates the most-recent Sybase error and message into
						``text_buffer``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``text_buffer`` is the area of memory into which the
						message text is to be copied by this function.

   RETURNS     :	Returns the ``text_buffer`` parameter.

   NOTES       :	This function is called by the internal DBC Sybase DB-LIB
						facility functions. There is little need for application
						programmers to call it directly.

   CAVEATS     :	

   SEE ALSO    :	

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	DBC_DBLIB_MSG_GetHandlerMessage
						DBC Sybase DB-LIB Functions:DBC_DBLIB_MSG_GetHandlerMessage
						DBC Functions:Message Handler Functions:DBC_DBLIB_MSG_GetHandlerMessage

   PUBLISH XREF:	DBC_DBLIB_MSG_GetHandlerMessage

   PUBLISH NAME:	DBC_DBLIB_MSG_GetHandlerMessage

	ENTRY CLASS	:	DBC Functions:Message Handler Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *DBC_DBLIB_MSG_GetHandlerMessage(char *text_buffer)
#else
char *DBC_DBLIB_MSG_GetHandlerMessage(text_buffer)
char *text_buffer;
#endif /* #ifndef NARGS */
{
	DBC_DBLIB_MSG *tmp_ptr;

	tmp_ptr      = DBC_DBLIB_MSG_GetHandlerPtr();
	*text_buffer = '\0';

	if (*tmp_ptr->err_text)
		strcat(nstrcat(text_buffer, tmp_ptr->err_text, DBC_MAX_ERROR_TEXT / 3),
			(*tmp_ptr->msg_text) ? " --- " : "");

	if (*tmp_ptr->msg_text)
		nstrcat(text_buffer, tmp_ptr->msg_text, DBC_MAX_ERROR_TEXT / 3);

	return(text_buffer);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_DBLIB_MSG_GetHandlerMSGMessage

   SYNOPSIS    :	return_ptr =
							DBC_DBLIB_MSG_GetHandlerMSGMessage(text_buffer);

						char *return_ptr;

						char *text_buffer;

   DESCRIPTION :	Copies the most-recent Sybase message into ``text_buffer``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``text_buffer`` is the area of memory into which the
						message text is to be copied by this function.

   RETURNS     :	Returns the ``text_buffer`` parameter.

   NOTES       :	This function is called by the internal DBC Sybase DB-LIB
						facility functions. There is little need for application
						programmers to call it directly.

   CAVEATS     :	

   SEE ALSO    :	DBC_DBLIB_MSG_GetHandlerMessage
						DBC_DBLIB_MSG_GetHandlerERRMessage

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	DBC_DBLIB_MSG_GetHandlerMSGMessage
						DBC Sybase DB-LIB Functions:DBC_DBLIB_MSG_GetHandlerMSGMessage
						DBC Functions:Message Handler Functions:DBC_DBLIB_MSG_GetHandlerMSGMessage

   PUBLISH XREF:	DBC_DBLIB_MSG_GetHandlerMSGMessage

   PUBLISH NAME:	DBC_DBLIB_MSG_GetHandlerMSGMessage

	ENTRY CLASS	:	DBC Functions:Message Handler Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *DBC_DBLIB_MSG_GetHandlerMSGMessage(char *text_buffer)
#else
char *DBC_DBLIB_MSG_GetHandlerMSGMessage(text_buffer)
char *text_buffer;
#endif /* #ifndef NARGS */
{
	DBC_DBLIB_MSG *tmp_db_stack_ptr;

	return(strcpy(text_buffer,
		((tmp_db_stack_ptr = DBC_DBLIB_MSG_GetHandlerPtr()) != NULL) ?
		tmp_db_stack_ptr->msg_text : ""));
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_DBLIB_MSG_GetHandlerERRMessage

   SYNOPSIS    :	return_ptr =
							DBC_DBLIB_MSG_GetHandlerERRMessage(text_buffer);

						char *return_ptr;

						char *text_buffer;

   DESCRIPTION :	Copies the most-recent Sybase error into ``text_buffer``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``text_buffer`` is the area of memory into which the
						message text is to be copied by this function.

   RETURNS     :	Returns the ``text_buffer`` parameter.

   NOTES       :	This function is called by the internal DBC Sybase DB-LIB
						facility functions. There is little need for application
						programmers to call it directly.

   CAVEATS     :	

   SEE ALSO    :	DBC_DBLIB_MSG_GetHandlerMessage
						DBC_DBLIB_MSG_GetHandlerMSGMessage

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	DBC_DBLIB_MSG_GetHandlerERRMessage
						DBC Sybase DB-LIB Functions:DBC_DBLIB_MSG_GetHandlerERRMessage
						DBC Functions:Message Handler Functions:DBC_DBLIB_MSG_GetHandlerERRMessage

   PUBLISH XREF:	DBC_DBLIB_MSG_GetHandlerERRMessage

   PUBLISH NAME:	DBC_DBLIB_MSG_GetHandlerERRMessage

	ENTRY CLASS	:	DBC Functions:Message Handler Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *DBC_DBLIB_MSG_GetHandlerERRMessage(char *text_buffer)
#else
char *DBC_DBLIB_MSG_GetHandlerERRMessage(text_buffer)
char *text_buffer;
#endif /* #ifndef NARGS */
{
	DBC_DBLIB_MSG *tmp_db_stack_ptr;

	return(strcpy(text_buffer,
		((tmp_db_stack_ptr = DBC_DBLIB_MSG_GetHandlerPtr()) != NULL) ?
		tmp_db_stack_ptr->err_text : ""));
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_DBLIB_MSG_HandleERR

   SYNOPSIS    :	return_code = DBC_DBLIB_MSG_HandleERR(db_proc, severity,
							db_err, os_err, db_err_string, os_err_string);

						int        return_code;

						DBPROCESS *db_proc;

						int        severity;

						int        db_err;

						int        os_err;

						char      *db_err_string;

						char      *os_err_string;

   DESCRIPTION :	The default Sybase error handler.

						This function is called only from with the Sybase DB-LIB
						implementation.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``db_proc`` is a pointer to the affected ''DBPROCESS''.

						(.) ``severity`` is the severity of the error.

						(.) ``db_err`` is the identifying number of the error.

						(.) ``os_err`` is the operating-system-specific error
						number.

						(.) ``db_err_string`` is a text description of ``db_err``.

						(.) ``os_err_string`` is a text description of ``os_err``.

   RETURNS     :	Always returns ''INT_CANCEL''.

   NOTES       :	This function is called by the internal Sybase DB-LIB
						library functions. There is no need for application
						programmers to call it directly.

   CAVEATS     :	

   SEE ALSO    :	DBC_DBLIB_MSG_HandleMSG

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	DBC_DBLIB_MSG_HandleERR
						DBC Sybase DB-LIB Functions:DBC_DBLIB_MSG_HandleERR
						DBC Functions:Message Handler Functions:DBC_DBLIB_MSG_HandleERR

   PUBLISH XREF:	DBC_DBLIB_MSG_HandleERR

   PUBLISH NAME:	DBC_DBLIB_MSG_HandleERR

	ENTRY CLASS	:	DBC Functions:Message Handler Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int DBC_DBLIB_MSG_HandleERR(DBPROCESS *db_proc, int severity, int db_err,
	int os_err, char *db_err_string, char *os_err_string)
#else
int DBC_DBLIB_MSG_HandleERR(db_proc, severity, db_err, os_err, db_err_string,
	os_err_string)
DBPROCESS *db_proc;
int        severity;
int        db_err;
int        os_err;
char      *db_err_string;
char      *os_err_string;
#endif /* #ifndef NARGS */
{
	int            return_code = INT_CANCEL;
	DBC_DBLIB_MSG *handler_ptr;

	if ((handler_ptr = DBC_DBLIB_MSG_GetHandlerPtr()) != NULL) {
		sprintf(handler_ptr->err_text,
			"DB ERROR %d, severity %d on %s %p: %-.*s",
			db_err, severity, "'DBPROCESS' pointer", db_proc,
			DBC_MAX_ERROR_TEXT / 3, db_err_string);
		if ((os_err == DBNOERR) && (os_err_string != NULL))
			nstrcat(strcat(handler_ptr->err_text, " --- OS ERROR: "),
				os_err_string, DBC_MAX_ERROR_TEXT / 3);
		if ((handler_ptr->mlog_ptr != NULL) &&
			handler_ptr->db_debug_flag)
			MLOG_LogErr(handler_ptr->mlog_ptr, "DB Error  : %s\n",
				handler_ptr->err_text);
	}

	return(return_code);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_DBLIB_MSG_HandleMSG

   SYNOPSIS    :	return_code = DBC_DBLIB_MSG_HandleMSG(db_proc, msg_number,
							msg_state, severity, msg_text, server_name, proc_name,
							line_number);

						int          return_code;

						DBPROCESS   *db_proc;

						DBINT        msg_number;

						int          msg_state;

						int          severity;

						char        *msg_text;

						char        *server_name;

						char        *proc_name;

						// ***** Declarations differ across Sybase versions *****

						#ifdef CS_PUBLIC

						int          line_number;

						#else

						DBUSMALLINT  line_number;

						#endif // # ifdef CS_PUBLIC

   DESCRIPTION :	The default Sybase message handler.

						This function is called only from with the Sybase DB-LIB
						implementation.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``db_proc`` is a pointer to the affected ''DBPROCESS''.

						(.) ``msg_number`` is the message number of the message.

						(.) ``msg_state`` is the message error state number.

						(.) ``severity`` is the message information class or error
						severity.

						(.) ``msg_text`` is a text description of the message.

						(.) ``server_name`` is the name of the Sybase server which
						generated the message.

						(.) ``proc_name`` is the name of the stored procedure
						which generated the message. If the message was not
						generated by a stored procedure, this parameter will be
						an empty string.

						(.) ``line_number`` is the line number of the SQL command
						batch or stored procedure at which the message was
						generated.

   RETURNS     :	Always returns ''0''.

   NOTES       :	Note the '#ifdef CS_PUBLIC' block. This is necessary
						because Sybase DB-LIB prior to Sybase System 10 (such as
						4.9.2) declared the last parameter of message handlers to
						be of type ''DBUSMALLINT'', whereas System 10 and subsequent
						releases declared it to be of type ''int''.

						This function is called by the internal Sybase DB-LIB
						library functions. There is no need for application
						programmers to call it directly.

   CAVEATS     :	

   SEE ALSO    :	DBC_DBLIB_MSG_HandleERR

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	DBC_DBLIB_MSG_HandleMSG
						DBC Sybase DB-LIB Functions:DBC_DBLIB_MSG_HandleMSG
						DBC Functions:Message Handler Functions:DBC_DBLIB_MSG_HandleMSG

   PUBLISH XREF:	DBC_DBLIB_MSG_HandleMSG

   PUBLISH NAME:	DBC_DBLIB_MSG_HandleMSG

	ENTRY CLASS	:	DBC Functions:Message Handler Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
	/* ***** Declarations differ across Sybase versions . . . ***** */
# ifdef CS_PUBLIC
int DBC_DBLIB_MSG_HandleMSG(DBPROCESS *db_proc, DBINT msg_number,
	int msg_state, int severity, char *msg_text, char *server_name,
	char *proc_name, int line_number)
# else
int DBC_DBLIB_MSG_HandleMSG(DBPROCESS *db_proc, DBINT msg_number,
	int msg_state, int severity, char *msg_text, char *server_name,
	char *proc_name, DBUSMALLINT line_number)
# endif /* # ifdef CS_PUBLIC */
#else
	/* ***** Declarations differ across Sybase versions . . . ***** */
# ifdef CS_PUBLIC
int DBC_DBLIB_MSG_HandleMSG(db_proc, msg_number, msg_state, severity,
	msg_text, server_name, proc_name, line_number)
DBPROCESS   *db_proc;
DBINT        msg_number;
int          msg_state;
int          severity;
char        *msg_text;
char        *server_name;
char        *proc_name;
int          line_number;
# else
int DBC_DBLIB_MSG_HandleMSG(db_proc, msg_number, msg_state, severity,
	msg_text, server_name, proc_name, line_number)
DBPROCESS   *db_proc;
DBINT        msg_number;
int          msg_state;
int          severity;
char        *msg_text;
char        *server_name;
char        *proc_name;
DBUSMALLINT  line_number;
# endif /* # ifdef CS_PUBLIC */
#endif /* #ifndef NARGS */
{
	int            return_code = 0;
	unsigned int   msg_length;
	DBC_DBLIB_MSG *handler_ptr;

	if ((handler_ptr = DBC_DBLIB_MSG_GetHandlerPtr()) != NULL) {
		sprintf(handler_ptr->msg_text,
			"%s %ld, %s %d, %s %d, %s '%s', %s '%s', %s %d, %s %p: %-.*s",
			"Message", msg_number, "State", msg_state, "Severity Level",
			severity, "Server Name", server_name, "Procedure Name", proc_name,
			"Line Number", ((int) line_number), "'DBPROCESS' pointer",
			db_proc, DBC_MAX_ERROR_TEXT / 2, msg_text);
		if ((msg_number == 3621) && *handler_ptr->msg_text &&
			((msg_length = strlen(handler_ptr->msg_text)) < DBC_MAX_ERROR_TEXT))
			nstrcat(handler_ptr->msg_text, " --- Command has been aborted.",
				DBC_MAX_ERROR_TEXT - (msg_length + 1));
		if ((handler_ptr->mlog_ptr != NULL) &&
			handler_ptr->db_debug_flag)
			MLOG_LogInfo(handler_ptr->mlog_ptr, "DB Message: %s\n",
				handler_ptr->msg_text);
	}

	return(return_code);
}
/* *********************************************************************** */

