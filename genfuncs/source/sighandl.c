/* *********************************************************************** */
/* *********************************************************************** */
/*	GENFUNCS General Functions Library Source Module								*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	The general functions library signal handler
								functions.

	Revision History	:	1994-07-28 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <strfuncs.h>

#include "genfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

static int   GEN_SIGNAL_SignalFlag             = GENFUNCS_FALSE;

static int   GEN_SIGNAL_QueueFlag              = GENFUNCS_FALSE;

static int   GEN_SIGNAL_InitializedFlag        = GENFUNCS_FALSE;

static int  *GEN_SIGNAL_SignalReceivedFlag     = &GEN_SIGNAL_SignalFlag;

static int  *GEN_SIGNAL_QueueSignalFlag        = &GEN_SIGNAL_QueueFlag;

void        *GEN_SIGNAL_UserDataPtr            = NULL;

void        *GEN_SIGNAL_OutputControlPtr       = NULL;

#ifndef NARGS
int        (*GEN_SIGNAL_OutputFunction)
	(const void *, size_t, size_t, void *)      = NULL;

void       (*GEN_SIGNAL_UserCleanUpFunction)
	(void *, int, int *, const char *)          = NULL;
#else
int        (*GEN_SIGNAL_OutputFunction)()      = NULL;

void       (*GEN_SIGNAL_UserCleanUpFunction)() = NULL;
#endif /* #ifndef NARGS */

/*	***********************************************************************	*/

#ifndef NARGS
void GEN_SIGNAL_SignalInit(int *signal_received_flag_ptr,
	int *queue_signal_flag_ptr, void *user_data_ptr, void *output_control_ptr,
	int (*output_function)(const void *, size_t, size_t, void *),
	void (*user_cleanup_function)(void *, int, int *, const char *))
#else
void GEN_SIGNAL_SignalInit(signal_received_flag_ptr, queue_signal_flag_ptr,
	user_data_ptr, output_control_ptr, output_function, user_cleanup_function)
int   *signal_received_flag_ptr;
int   *queue_signal_flag_ptr;
void  *user_data_ptr;
void  *output_control_ptr;
int  (*output_function)();
void (*user_cleanup_function)();
#endif /* #ifndef NARGS */
{
	GEN_SIGNAL_InitializedFlag     = GENFUNCS_TRUE;
	GEN_SIGNAL_SignalReceivedFlag  =
		(signal_received_flag_ptr == NULL) ? &GEN_SIGNAL_SignalFlag :
		signal_received_flag_ptr;
	GEN_SIGNAL_QueueSignalFlag     =
		(queue_signal_flag_ptr    == NULL) ? &GEN_SIGNAL_QueueFlag  :
		queue_signal_flag_ptr;
	GEN_SIGNAL_UserDataPtr         = user_data_ptr;
	GEN_SIGNAL_OutputControlPtr    = output_control_ptr;
	GEN_SIGNAL_OutputFunction      = output_function;
	GEN_SIGNAL_UserCleanUpFunction = user_cleanup_function;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void GEN_SIGNAL_SignalDefault(void)
#else
void GEN_SIGNAL_SignalDefault()
#endif /* #ifndef NARGS */
{
#ifdef __MSDOS__
	signal(SIGINT,    SIG_DFL);
	signal(SIGTERM,   SIG_DFL);
#elif _Windows
	signal(SIGINT,    SIG_DFL);
	signal(SIGTERM,   SIG_DFL);
#elif _MSC_VER
	signal(SIGINT,    SIG_DFL);
	signal(SIGTERM,   SIG_DFL);
#else
	signal(SIGHUP,    SIG_DFL);
	signal(SIGINT,    SIG_DFL);
	signal(SIGQUIT,   SIG_DFL);
	signal(SIGPIPE,   SIG_DFL);
	signal(SIGALRM,   SIG_DFL);
	signal(SIGTERM,   SIG_DFL);
	signal(SIGXCPU,   SIG_DFL);
	signal(SIGXFSZ,   SIG_DFL);
	signal(SIGVTALRM, SIG_DFL);
	signal(SIGUSR1,   SIG_DFL);
	signal(SIGUSR2,   SIG_DFL);
#endif /* #ifdef __MSDOS__ */
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void GEN_SIGNAL_SignalIgnore(void)
#else
void GEN_SIGNAL_SignalIgnore()
#endif /* #ifndef NARGS */
{
#ifdef __MSDOS__
	signal(SIGINT,    SIG_IGN);
	signal(SIGTERM,   SIG_IGN);
#elif _Windows
	signal(SIGINT,    SIG_IGN);
	signal(SIGTERM,   SIG_IGN);
#elif _MSC_VER
	signal(SIGINT,    SIG_IGN);
	signal(SIGTERM,   SIG_IGN);
#else
	signal(SIGHUP,    SIG_IGN);
	signal(SIGINT,    SIG_IGN);
	signal(SIGQUIT,   SIG_IGN);
	signal(SIGPIPE,   SIG_IGN);
	signal(SIGALRM,   SIG_IGN);
	signal(SIGTERM,   SIG_IGN);
	signal(SIGXCPU,   SIG_IGN);
	signal(SIGXFSZ,   SIG_IGN);
	signal(SIGVTALRM, SIG_IGN);
	signal(SIGWINCH,	SIG_IGN);
	signal(SIGUSR1,   SIG_IGN);
	signal(SIGUSR2,   SIG_IGN);
#endif /* #ifdef __MSDOS__ */
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void GEN_SIGNAL_SignalSet(void)
#else
void GEN_SIGNAL_SignalSet()
#endif /* #ifndef NARGS */
{
#ifdef __MSDOS__
	signal(SIGINT,    GEN_SIGNAL_SignalHandler);
	signal(SIGTERM,   GEN_SIGNAL_SignalHandler);
#elif _Windows
	signal(SIGINT,    GEN_SIGNAL_SignalHandler);
	signal(SIGTERM,   GEN_SIGNAL_SignalHandler);
#elif _MSC_VER
	signal(SIGINT,    GEN_SIGNAL_SignalHandler);
	signal(SIGTERM,   GEN_SIGNAL_SignalHandler);
#elif __SVR4
	signal(SIGHUP,    SIG_IGN);
	signal(SIGINT,    ((void (*)(int)) GEN_SIGNAL_SignalHandler));
	signal(SIGQUIT,   SIG_IGN);
	signal(SIGPIPE,   SIG_IGN);
	signal(SIGALRM,   SIG_IGN);
	signal(SIGTERM,   ((void (*)(int)) GEN_SIGNAL_SignalHandler));
	signal(SIGXCPU,   SIG_IGN);
	signal(SIGXFSZ,   SIG_IGN);
	signal(SIGVTALRM, SIG_IGN);
	signal(SIGUSR1,   SIG_IGN);
	signal(SIGUSR2,   SIG_IGN);
#else
	signal(SIGHUP,    SIG_IGN);
	signal(SIGINT,    GEN_SIGNAL_SignalHandler);
	signal(SIGQUIT,   SIG_IGN);
	signal(SIGPIPE,   SIG_IGN);
	signal(SIGALRM,   SIG_IGN);
	signal(SIGTERM,   GEN_SIGNAL_SignalHandler);
	signal(SIGXCPU,   SIG_IGN);
	signal(SIGXFSZ,   SIG_IGN);
	signal(SIGVTALRM, SIG_IGN);
	signal(SIGUSR1,   SIG_IGN);
	signal(SIGUSR2,   SIG_IGN);
#endif /* #ifdef __MSDOS__ */
}
/*	***********************************************************************	*/

/* *********************************************************************** */
#ifdef __MSDOS__
# ifndef NARGS
void GEN_SIGNAL_SignalHandler(int signal_number)
# else
void GEN_SIGNAL_SignalHandler(signal_number)
int                signal_number;
# endif /* # ifndef NARGS */
#elif _Windows
# ifndef NARGS
void GEN_SIGNAL_SignalHandler(int signal_number)
# else
void GEN_SIGNAL_SignalHandler(signal_number)
int                signal_number;
# endif /* # ifndef NARGS */
#elif _MSC_VER
# ifndef NARGS
void GEN_SIGNAL_SignalHandler(int signal_number)
# else
void GEN_SIGNAL_SignalHandler(signal_number)
int                signal_number;
# endif /* # ifndef NARGS */
#else
# ifdef __SVR4
#  ifndef NARGS
void GEN_SIGNAL_SignalHandler(int signal_number, siginfo_t *siginfo_ptr,
	void *signal_address)
#  else
void GEN_SIGNAL_SignalHandler(signal_number, siginfo_ptr, signal_address)
int        signal_number;
siginfo_t *siginfo_ptr;
void      *signal_address;
#  endif /* #  ifndef NARGS */
# else
#  ifndef NARGS
void GEN_SIGNAL_SignalHandler(int signal_number, int signal_code,
	struct sigcontext *signal_context, char *signal_address)
#  else
void GEN_SIGNAL_SignalHandler(signal_number, signal_code, signal_context,
	signal_address)
int                signal_number;
int                signal_code;
struct sigcontext *signal_context;
char              *signal_address;
#  endif /* #  ifndef NARGS */
# endif /* # ifdef __SVR4 */
#endif /* ifdef __MSDOS__ */
{
	int  exit_code = -1;
	char message_buffer[GENFUNCS_MAX_ERROR_TEXT];
	char signal_buffer[STR_VAL2STR_MAX_LEN + 1];

	*GEN_SIGNAL_SignalReceivedFlag = GENFUNCS_TRUE;

	if (GEN_SIGNAL_InitializedFlag == GENFUNCS_TRUE) {
		trim(oneblank(val2str(((unsigned long) signal_number), 1, 10, " ",
			signal_buffer)));
		strcat(strcat(strcpy(message_buffer, "\n\n***** Signal number "),
			signal_buffer), " received --- ");
		if (*GEN_SIGNAL_QueueSignalFlag == GENFUNCS_TRUE) {
			strcat(message_buffer,
				"will exit after the current processing is completed. *****\n\n");
			if (GEN_SIGNAL_OutputControlPtr != NULL)
				(*GEN_SIGNAL_OutputFunction)(message_buffer, 1,
					strlen(message_buffer), GEN_SIGNAL_OutputControlPtr);
			if (GEN_SIGNAL_OutputFunction !=
				((int (*)(const void *, size_t, size_t, void *)) fwrite))
				fputs(message_buffer, stderr);
			return;
		}
		else {
			strcat(message_buffer, "exiting . . . *****\n\n");
			if ((GEN_SIGNAL_OutputFunction != NULL) &&
				(GEN_SIGNAL_OutputControlPtr != NULL))
				(*GEN_SIGNAL_OutputFunction)(message_buffer, 1,
					strlen(message_buffer), GEN_SIGNAL_OutputControlPtr);
			if (GEN_SIGNAL_OutputFunction !=
				((int (*)(const void *, size_t, size_t, void *)) fwrite))
				fputs(message_buffer, stderr);
			if (GEN_SIGNAL_UserCleanUpFunction != NULL) {
				strcat(strcat(strcpy(message_buffer, "Signal number "),
					signal_buffer), " received: ");
#ifdef __MSDOS__
				GEN_GetSignalText(signal_number,
					message_buffer + strlen(message_buffer));
#elif _Windows
				GEN_GetSignalText(signal_number,
					message_buffer + strlen(message_buffer));
#elif _MSC_VER
				GEN_GetSignalText(signal_number,
					message_buffer + strlen(message_buffer));
#else
# ifdef __SVR4
				GEN_GetSignalText(signal_number, siginfo_ptr, signal_address,
					message_buffer + strlen(message_buffer));
# else
				GEN_GetSignalText(signal_number, signal_code, signal_address,
					message_buffer + strlen(message_buffer));
# endif /* # ifdef __SVR4 */
#endif /* ifdef __MSDOS__ */
				(*GEN_SIGNAL_UserCleanUpFunction)(GEN_SIGNAL_UserDataPtr,
					signal_number, &exit_code, message_buffer);
			}
			exit(exit_code);
		}
	}
}
/*	***********************************************************************	*/

