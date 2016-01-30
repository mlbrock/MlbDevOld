/* *********************************************************************** */
/* *********************************************************************** */
/*	GENFUNCS General Functions Library Source Module								*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Describes a signal context.

	Revision History	:	1992-10-10 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/*    Include necessary header files . . .                                 */
/* *********************************************************************** */

#include <limits.h>
#include <signal.h>
#include <string.h>

#include <strfuncs.h>

#include "genfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* *********************************************************************** */

typedef struct {
	char *signal_name;
	int   signal_number;
	char *signal_description;
} GENFUNCS_SIGNAL_DATA;

#ifdef __MSDOS__
static const GENFUNCS_SIGNAL_DATA GENFUNCS_SignalList[] = {
	{	"SIGINT",		SIGINT,
		"interrupt"															},
	{	"SIGTERM",		SIGTERM,
		"software termination signal from kill"					},
	{	"SIGABRT",		SIGABRT,
		"abnormal termination"											}
};
#elif _Windows
static const GENFUNCS_SIGNAL_DATA GENFUNCS_SignalList[] = {
	{	"SIGINT",		SIGINT,
		"interrupt"															},
	{	"SIGTERM",		SIGTERM,
		"software termination signal from kill"					},
	{	"SIGABRT",		SIGABRT,
		"abnormal termination"											}
};
#elif _MSC_VER
static const GENFUNCS_SIGNAL_DATA GENFUNCS_SignalList[] = {
	{	"SIGINT",		SIGINT,
		"interrupt"															},
	{	"SIGTERM",		SIGTERM,
		"software termination signal from kill"					},
	{	"SIGABRT",		SIGABRT,
		"abnormal termination"											}
};
#elif __SVR4
static const GENFUNCS_SIGNAL_DATA GENFUNCS_SignalList[] = {
	{	"SIGHUP",		SIGHUP,
		"controlling terminal hangup"									},
	{	"SIGINT",		SIGINT,
		"interactive interrupt"											},
	{	"SIGQUIT",		SIGQUIT,
		"interactive process abnormal termination"				},
	{	"SIGILL",		SIGILL,
		"illegal instruction exception"								},
	{	"SIGTRAP",		SIGTRAP,
		"trace trap (not reset when caught)"						},
	{	"SIGIOT",		SIGIOT,
		"IOT instruction ('abort()' calls this SIGABRT)"		},
	{	"SIGEMT",		SIGEMT,
		"EMT instruction"													},
	{	"SIGFPE",		SIGFPE,
		"floating point exception"										},
	{	"SIGKILL",		SIGKILL,
		"kill (unstoppable termination)"								},
	{	"SIGBUS",		SIGBUS,
		"bus error"															},
	{	"SIGSEGV",		SIGSEGV,
		"memory access / segmentation violation"					},
	{	"SIGSYS",		SIGSYS,
		"bad argument to system call"									},
	{	"SIGPIPE",		SIGPIPE,
		"write on a pipe with no one to read it"					},
	{	"SIGALRM",		SIGALRM,
		"alarm clock expired" 											},
	{	"SIGTERM",		SIGTERM,
		"software termination signal from kill"					},
	{	"SIGUSR1",		SIGUSR1,
		"user defined signal number 1"								},
	{	"SIGUSR2",		SIGUSR2,
		"user defined signal number 2"								},
	{	"SIGCHLD",		SIGCHLD,
		"to parent on child stop or exit (System V SIGCLD)"	},
	{	"SIGPWR",	SIGPWR,
		"power fail/re-start"											},
	{	"SIGWINCH",		SIGWINCH,
		"window changed"													},
	{	"SIGURG",		SIGURG,
		"urgent condition on IO channel"								},
	{	"SIGIO/SIGPOLL",SIGIO,
		"input/output possible signal (System V SIGPOLL)"		},
	{	"SIGSTOP",		SIGSTOP,
		"sendable stop signal not from tty"							},
	{	"SIGTSTP",		SIGTSTP,
		"stop signal from tty"											},
	{	"SIGCONT",		SIGCONT,
		"continue a stopped process"									},
	{	"SIGTTIN",		SIGTTIN,
		"to readers pgrp upon background tty read"				},
	{	"SIGTTOU",		SIGTTOU,
		"like TTIN for output if (tp->t_local&LTOSTOP)"			},
	{	"SIGVTALRM",	SIGVTALRM,
		"virtual time alarm"												},
	{	"SIGPROF",		SIGPROF,
		"profiling time alarm"											},
	{	"SIGXCPU",		SIGXCPU,
		"exceeded CPU time limit"										},
	{	"SIGXFSZ",		SIGXFSZ,
		"exceeded file size limit"										},
	{	"SIGWAITING",	SIGWAITING,
		"process light-weight processes are blocked"				},
	{	"SIGLWP",	SIGLWP,
		"thread library special exit signal"						},
	{	"SIGFREEZE",	SIGFREEZE,
		"check point freeze"												},
	{	"SIGTHAW",		SIGTHAW,
		"check point thaw"												},
	{	"SIGCANCEL",	SIGCANCEL,
		"cancellation signal reserved by the threads library"	},
	{	"SIGLOST",		SIGLOST,
		"resource lost"													}
};
#else
static const GENFUNCS_SIGNAL_DATA GENFUNCS_SignalList[] = {
	{	"SIGHUP",		SIGHUP,
		"controlling terminal hangup"									},
	{	"SIGINT",		SIGINT,
		"interactive interrupt"											},
	{	"SIGQUIT",		SIGQUIT,
		"interactive process abnormal termination"				},
	{	"SIGILL",		SIGILL,
		"illegal instruction exception"								},
	{	"SIGTRAP",		SIGTRAP,
		"trace trap (not reset when caught)"						},
	{	"SIGIOT",		SIGIOT,
		"IOT instruction ('abort()' calls this SIGABRT)"		},
/* Not present in Linux */
# ifdef SIGEMT
	{	"SIGEMT",		SIGEMT,
		"EMT instruction"													},
# endif /* # ifdef SIGEMT */
	{	"SIGFPE",		SIGFPE,
		"floating point exception"										},
	{	"SIGKILL",		SIGKILL,
		"kill (unstoppable termination)"								},
	{	"SIGBUS",		SIGBUS,
		"bus error"															},
	{	"SIGSEGV",		SIGSEGV,
		"memory access / segmentation violation"					},
	{	"SIGSYS",		SIGSYS,
		"bad argument to system call"									},
	{	"SIGPIPE",		SIGPIPE,
		"write on a pipe with no one to read it"					},
	{	"SIGALRM",		SIGALRM,
		"alarm clock expired" 											},
	{	"SIGTERM",		SIGTERM,
		"software termination signal from kill"					},
	{	"SIGURG",		SIGURG,
		"urgent condition on IO channel"								},
	{	"SIGSTOP",		SIGSTOP,
		"sendable stop signal not from tty"							},
	{	"SIGTSTP",		SIGTSTP,
		"stop signal from tty"											},
	{	"SIGCONT",		SIGCONT,
		"continue a stopped process"									},
	{	"SIGCHLD",		SIGCHLD,
		"to parent on child stop or exit (System V SIGCLD)"	},
	{	"SIGTTIN",		SIGTTIN,
		"to readers pgrp upon background tty read"				},
	{	"SIGTTOU",		SIGTTOU,
		"like TTIN for output if (tp->t_local&LTOSTOP)"			},
	{	"SIGIO/SIGPOLL",SIGIO,
		"input/output possible signal (System V SIGPOLL)"		},
	{	"SIGXCPU",		SIGXCPU,
		"exceeded CPU time limit"										},
	{	"SIGXFSZ",		SIGXFSZ,
		"exceeded file size limit"										},
	{	"SIGVTALRM",	SIGVTALRM,
		"virtual time alarm"												},
	{	"SIGPROF",		SIGPROF,
		"profiling time alarm"											},
	{	"SIGWINCH",		SIGWINCH,
		"window changed"													},
/* Not present in Linux */
# ifdef SIGLOST
	{	"SIGLOST",		SIGLOST,
		"resource lost (e.g., record-lock lost)"					},
# endif /* # ifdef SIGLOST */
	{	"SIGUSR1",		SIGUSR1,
		"user defined signal number 1"								},
	{	"SIGUSR2",		SIGUSR2,
		"user defined signal number 2"								}
};
#endif /* #ifdef __MSDOS__ */

static const unsigned int GENFUNCS_SignalCount =
	sizeof(GENFUNCS_SignalList) / sizeof(GENFUNCS_SignalList[0]);

#ifdef __SVR4
# undef sparc
#endif /* #ifdef __SVR4 */

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	GEN_GetSignalText

	SYNOPSIS		:	// For BSD Unix machines . . .

						//

						text_ptr = GEN_GetSignalText(signal_number, signal_code,
							signal_address, signal_text);

						char       *text_ptr;

						int         signal_number;

						int         signal_code;

						const void *signal_address;

						char       *signal_text;

						//

						// For System V Unix machines and MS-DOS machines . . .

						//

						text_ptr = GEN_GetSignalText(signal_number, signal_text);

						char       *text_ptr;

						int         signal_number;

						char       *signal_text;

	DESCRIPTION	:	Constructs a string which describes the context of a
						signal. Designed to be called from a signal handler.

   PARAMETERS  :  Parameters to this function are as follows:

						(.) ``signal_number`` is the number of the signal as passed
						to the signal handler.

						(.) ``signal_code`` is the signal code as passed to the
						signal handler.

						(-) The ``signal_code`` parameter is not provided under
						MS-DOS versions of this function.

						(.) ``signal_address`` is the offending address of the
						signal, as passed to the signal handler.

						(-) The ``signal_address`` parameter is not provided under
						MS-DOS versions of this function.

						(.) ``signal_text`` is the area into which the string
						describing the signal is to be placed.

						(-) The string allocated for this purpose should be at least
						''GENFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  A pointer to the text resulting from operation of the
						function. That is, ``signal_text`` is returned.

	NOTES			:	The functions not a part of the standard C library called
						by this function are guaranteed to be re-entrant. This
						function assumes that the C standard library functions
						``strcpy`` and ``strcat`` are also re-entrant. This is
						probably a valid assumption for any professional
						implementation of the C standard library.

	CAVEATS		:	This code purports to work under Motorola 68000 and VAX
						implementations of BSD, but has not been tested.

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2016 Michael L. Brock

	OUTPUT INDEX:	GEN_GetSignalText
						Signal Functions:GEN_GetSignalText
						GENFUNCS:Functions:GEN_GetSignalText
						GENFUNCS:Signal Functions:GEN_GetSignalText
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_GetSignalText

	PUBLISH NAME:	GEN_GetSignalText

	ENTRY CLASS	:	Signal Functions

EOH */
/* *********************************************************************** */
#ifdef __MSDOS__
# ifndef NARGS
char *GEN_GetSignalText(int signal_number, char *signal_text)
# else
char *GEN_GetSignalText(signal_number, signal_text)
int   signal_number;
char *signal_text;
# endif /* #ifndef NARGS */
{
	unsigned int  count_1;
	char         *signal_name_ptr = NULL;
	const char   *signal_code_ptr = NULL;
	const char   *signal_desc_ptr = NULL;
	char          signal_name_buffer[GENFUNCS_MAX_ERROR_TEXT / 4];
	char          number_buffer[STR_VAL2STR_MAX_LEN + 1];

	*signal_text = '\0';

	for (count_1 = 0; count_1 < GENFUNCS_SignalCount; count_1++) {
		if (signal_number == GENFUNCS_SignalList[count_1].signal_number) {
			signal_name_ptr = GENFUNCS_SignalList[count_1].signal_name;
			signal_desc_ptr = GENFUNCS_SignalList[count_1].signal_description;
			break;
		}
	}

	if (signal_name_ptr == NULL)
		strcat(strcat(strcpy(signal_name_ptr = signal_name_buffer,
			"Invalid signal number encountered ("),
			val2str(((unsigned long) signal_number), 0, 10, NULL,
			number_buffer)), ")");

	signal_code_ptr = (signal_code_ptr != NULL) ? signal_code_ptr : " ";
	signal_desc_ptr = (signal_desc_ptr != NULL) ? signal_desc_ptr :
		" *** UNABLE TO DESCRIBE SIGNAL ***";

	return(trim(oneblank(strcat(strcat(strcpy(signal_text,
		signal_name_ptr), signal_code_ptr), signal_desc_ptr))));
}
#elif _Windows
# ifndef NARGS
char *GEN_GetSignalText(int signal_number, char *signal_text)
# else
char *GEN_GetSignalText(signal_number, signal_text)
int   signal_number;
char *signal_text;
# endif /* #ifndef NARGS */
{
	unsigned int  count_1;
	char         *signal_name_ptr = NULL;
	const char   *signal_code_ptr = NULL;
	const char   *signal_desc_ptr = NULL;
	char          signal_name_buffer[GENFUNCS_MAX_ERROR_TEXT / 4];
	char          number_buffer[STR_VAL2STR_MAX_LEN + 1];

	*signal_text = '\0';

	for (count_1 = 0; count_1 < GENFUNCS_SignalCount; count_1++) {
		if (signal_number == GENFUNCS_SignalList[count_1].signal_number) {
			signal_name_ptr = GENFUNCS_SignalList[count_1].signal_name;
			signal_desc_ptr = GENFUNCS_SignalList[count_1].signal_description;
			break;
		}
	}

	if (signal_name_ptr == NULL)
		strcat(strcat(strcpy(signal_name_ptr = signal_name_buffer,
			"Invalid signal number encountered ("),
			val2str(((unsigned long) signal_number), 0, 10, NULL,
			number_buffer)), ")");

	signal_code_ptr = (signal_code_ptr != NULL) ? signal_code_ptr : " ";
	signal_desc_ptr = (signal_desc_ptr != NULL) ? signal_desc_ptr :
		" *** UNABLE TO DESCRIBE SIGNAL ***";

	return(trim(oneblank(strcat(strcat(strcpy(signal_text,
		signal_name_ptr), signal_code_ptr), signal_desc_ptr))));
}
#else
# ifdef __SVR4
#  ifndef NARGS
char *GEN_GetSignalText(int signal_number, siginfo_t *siginfo_ptr,
	void *signal_address, char *signal_text)
#  else
char *GEN_GetSignalText(signal_number, siginfo_ptr, signal_address,
	signal_text)
int        signal_number;
siginfo_t *siginfo_ptr;
void      *signal_address;
char      *signal_text;
#  endif /* #ifndef NARGS */
{
	unsigned int  count_1;
	char         *signal_name_ptr = NULL;
	const char   *signal_code_ptr = NULL;
	const char   *signal_desc_ptr = NULL;
	char         *signal_addr_ptr = NULL;
	char          signal_name_buffer[GENFUNCS_MAX_ERROR_TEXT / 4];
	char          signal_code_buffer[GENFUNCS_MAX_ERROR_TEXT / 4];
	char          signal_desc_buffer[GENFUNCS_MAX_ERROR_TEXT / 4];
	char          signal_addr_buffer[GENFUNCS_MAX_ERROR_TEXT / 4];
	char          number_buffer[STR_VAL2STR_MAX_LEN + 1];

	*signal_text = '\0';

	for (count_1 = 0; count_1 < GENFUNCS_SignalCount; count_1++) {
		if (signal_number == GENFUNCS_SignalList[count_1].signal_number) {
			signal_name_ptr = GENFUNCS_SignalList[count_1].signal_name;
			signal_desc_ptr = GENFUNCS_SignalList[count_1].signal_description;
			break;
		}
	}

	if (signal_name_ptr == NULL) {
		if ((signal_number >= SIGRTMIN) && (signal_number <= SIGRTMAX)) {
			strcat(strcpy(signal_name_ptr = signal_name_buffer, "SIGRTMIN+"),
				val2str(((unsigned long) (signal_number - SIGRTMIN)), 0,
				10, NULL, number_buffer));
			strcat(ordinal_full(((unsigned long) (signal_number - SIGRTMIN)) + 1L,
				signal_desc_ptr = signal_desc_buffer), " real time signal");
			*signal_desc_ptr = STRFUNCS_toupper(*signal_desc_ptr);
		}
		else
			strcat(strcat(strcpy(signal_name_ptr = signal_name_buffer,
				"Invalid signal number encountered ("),
				val2str(((unsigned long) signal_number), 0, 10, NULL,
				number_buffer)), ")");
	}
	else {
		switch (signal_number) {
			case SIGILL		:
				switch (siginfo_ptr->si_code) {
					case ILL_ILLOPC				:
						signal_code_ptr = " ILL_ILLOPC";
						signal_desc_ptr = " illegal opcode";
						break;
					case ILL_ILLOPN				:
						signal_code_ptr = " ILL_ILLOPN";
						signal_desc_ptr = " illegal operand";
						break;
					case ILL_ILLADR				:
						signal_code_ptr = " ILL_ILLADR";
						signal_desc_ptr = " illegal addressng mode";
						break;
					case ILL_ILLTRP				:
						signal_code_ptr = " ILL_ILLTRP";
						signal_desc_ptr = " illegal trap";
						break;
					case ILL_PRVOPC				:
						signal_code_ptr = " ILL_PRVOPC";
						signal_desc_ptr = " privileged opcode";
						break;
					case ILL_PRVREG				:
						signal_code_ptr = " ILL_PRVREG";
						signal_desc_ptr = " priviledged register";
						break;
					case ILL_COPROC				:
						signal_code_ptr = " ILL_COPROC";
						signal_desc_ptr = " co-processor error";
						break;
					case ILL_BADSTK				:
						signal_code_ptr = " ILL_BADSTK";
						signal_desc_ptr = " internal stack error";
						break;
					default							:
						strcat(strcpy(signal_code_buffer,
							" UNKNOWN SIGILL SIGNAL CODE "),
							val2str(((unsigned long) siginfo_ptr->si_code),
							0, 10, NULL, number_buffer));
						signal_code_ptr = signal_code_buffer;
						signal_desc_ptr = " ";
						break;
				}
				strcat(strcpy(signal_addr_ptr = signal_addr_buffer,
					" at address 0X"),
					val2str(((unsigned long) siginfo_ptr->si_addr), 0, 16,
					NULL, number_buffer));
				break;
			case SIGTRAP	:
				switch (siginfo_ptr->si_code) {
					case TRAP_BRKPT			:
						signal_code_ptr = " TRAP_BRKPT";
						signal_desc_ptr = " process breakpoint";
						break;
					case TRAP_TRACE			:
						signal_code_ptr = " TRAP_TRACE";
						signal_desc_ptr = " process trace trap";
						break;
					default							:
						strcat(strcpy(signal_code_buffer,
							" UNKNOWN SIGTRAP SIGNAL CODE "),
							val2str(((unsigned long) siginfo_ptr->si_code),
							0, 10, NULL, number_buffer));
						signal_code_ptr = signal_code_buffer;
						signal_desc_ptr = " ";
						break;
				}
				break;
			case SIGFPE		:
				switch (siginfo_ptr->si_code) {
					case FPE_INTDIV				:
						signal_code_ptr = " FPE_INTDIV";
						signal_desc_ptr = " integer divide by zero";
						break;
					case FPE_INTOVF				:
						signal_code_ptr = " FPE_INTOVF";
						signal_desc_ptr = " integer overflow";
						break;
					case FPE_FLTDIV				:
						signal_code_ptr = " FPE_FLTDIV";
						signal_desc_ptr = " floating point division by zero";
						break;
					case FPE_FLTOVF				:
						signal_code_ptr = " FPE_FLTOVF";
						signal_desc_ptr = " floating point overflow";
						break;
					case FPE_FLTUND				:
						signal_code_ptr = " FPE_FLTUND";
						signal_desc_ptr = " floating point underflow";
						break;
					case FPE_FLTRES				:
						signal_code_ptr = " FPE_FLTRES";
						signal_desc_ptr = " floating point inexact result";
						break;
					case FPE_FLTINV				:
						signal_code_ptr = " FPE_FLTINV";
						signal_desc_ptr = " invalid floating point operation";
						break;
					case FPE_FLTSUB				:
						signal_code_ptr = " FPE_FLTSUB";
						signal_desc_ptr = " subscript out of range";
						break;
					default						:
						strcat(strcpy(signal_code_buffer,
							" UNKNOWN SIGFPE SIGNAL CODE "),
							val2str(((unsigned long) siginfo_ptr->si_code),
							0, 10, NULL, number_buffer));
						signal_code_ptr = signal_code_buffer;
						signal_desc_ptr = " ";
						break;
				}
				strcat(strcpy(signal_addr_ptr = signal_addr_buffer,
					" at address 0X"),
					val2str(((unsigned long) siginfo_ptr->si_addr), 0, 16,
					NULL, number_buffer));
				break;
			case SIGBUS		:
				switch (siginfo_ptr->si_code) {
					case BUS_ADRALN:
						signal_code_ptr = " BUS_ADRALN";
						signal_desc_ptr = " invalid address alignment";
						break;
					case BUS_ADRERR:
						signal_code_ptr = " BUS_ADRERR";
						signal_desc_ptr = " non-existent physical address";
						break;
					case BUS_OBJERR:
						signal_code_ptr = " BUS_OBJERR";
						signal_desc_ptr = " object specific hardware error";
						break;
					default			:
						strcat(strcpy(signal_code_buffer,
							" UNKNOWN SIGBUS SIGNAL CODE "),
							val2str(((unsigned long) siginfo_ptr->si_code),
							0, 10, NULL, number_buffer));
						signal_code_ptr = signal_code_buffer;
						signal_desc_ptr = " ";
						break;
				}
				strcat(strcpy(signal_addr_ptr = signal_addr_buffer,
					" at address 0X"),
					val2str(((unsigned long) siginfo_ptr->si_addr), 0, 16,
					NULL, number_buffer));
				break;
			case SIGSEGV	:
				switch (siginfo_ptr->si_code) {
					case SEGV_MAPERR	:
						signal_code_ptr = " SEGV_MAPERR";
						signal_desc_ptr = " address not mapped to object";
						break;
					case SEGV_ACCERR	:
						signal_code_ptr = " SEGV_ACCERR";
						signal_desc_ptr = " invalid permissions for mapped object";
						break;
					default:
						strcat(strcpy(signal_code_buffer,
							" UNKNOWN SIGSEGV SIGNAL CODE "),
							val2str(((unsigned long) siginfo_ptr->si_code),
							0, 10, NULL, number_buffer));
						signal_code_ptr = signal_code_buffer;
						signal_desc_ptr = " ";
						break;
				}
				strcat(strcpy(signal_addr_ptr = signal_addr_buffer,
					" at address 0X"),
					val2str(((unsigned long) siginfo_ptr->si_addr), 0, 16,
					NULL, number_buffer));
				break;
			case SIGCHLD	:
				switch (siginfo_ptr->si_code) {
					case CLD_EXITED		:
						signal_code_ptr = " CLD_EXITED";
						signal_desc_ptr = " child has exited";
						break;
					case CLD_KILLED		:
						signal_code_ptr = " CLD_KILLED";
						signal_desc_ptr = " child was killed";
						break;
					case CLD_DUMPED		:
						signal_code_ptr = " CLD_DUMPED";
						signal_desc_ptr = " child terminated abnormally";
						break;
					case CLD_TRAPPED		:
						signal_code_ptr = " CLD_TRAPPED";
						signal_desc_ptr = " trace child has trapped";
						break;
					case CLD_STOPPED		:
						signal_code_ptr = " CLD_STOPPED";
						signal_desc_ptr = " child has stopped";
						break;
					case CLD_CONTINUED	:
						signal_code_ptr = " CLD_CONTINUED";
						signal_desc_ptr = " stopped child had continued";
						break;
					default:
						strcat(strcpy(signal_code_buffer,
							" UNKNOWN SIGCHLD SIGNAL CODE "),
							val2str(((unsigned long) siginfo_ptr->si_code),
							0, 10, NULL, number_buffer));
						signal_code_ptr = signal_code_buffer;
						signal_desc_ptr = " ";
						break;
				}
				break;
			case SIGPOLL	:
				switch (siginfo_ptr->si_code) {
					case POLL_IN	:
						signal_code_ptr = " POLL_IN";
						signal_desc_ptr = " data input available";
						break;
					case POLL_OUT	:
						signal_code_ptr = " POLL_OUT";
						signal_desc_ptr = " output buffers available";
						break;
					case POLL_MSG	:
						signal_code_ptr = " POLL_MSG";
						signal_desc_ptr = " input message available";
						break;
					case POLL_ERR	:
						signal_code_ptr = " POLL_ERR";
						signal_desc_ptr = " I/O error";
						break;
					case POLL_PRI	:
						signal_code_ptr = " POLL_PRI";
						signal_desc_ptr = " high priority input available";
						break;
					case POLL_HUP	:
						signal_code_ptr = " POLL_HUP";
						signal_desc_ptr = " device disconnected";
						break;
					default:
						strcat(strcpy(signal_code_buffer,
							" UNKNOWN SIGIO/SIGPOLL SIGNAL CODE "),
							val2str(((unsigned long) siginfo_ptr->si_code),
							0, 10, NULL, number_buffer));
						signal_code_ptr = signal_code_buffer;
						signal_desc_ptr = " ";
						break;
				}
				break;
			default			:
				break;
		}
	}

	signal_code_ptr = (signal_code_ptr != NULL) ? signal_code_ptr : " ";
	signal_desc_ptr = (signal_desc_ptr != NULL) ? signal_desc_ptr :
		" *** UNABLE TO DESCRIBE SIGNAL ***";
	signal_addr_ptr = (signal_addr_ptr != NULL) ? signal_addr_ptr : " ";

	return(trim(oneblank(strcat(strcat(strcat(strcpy(signal_text,
		signal_name_ptr), signal_code_ptr), signal_desc_ptr),
		signal_addr_ptr))));
}
# else
#  ifndef NARGS
char *GEN_GetSignalText(int signal_number, int signal_code,
	const void *signal_address, char *signal_text)
#  else
char *GEN_GetSignalText(signal_number, signal_code, signal_address,
	signal_text)
int         signal_number;
int         signal_code;
const void *signal_address;
char       *signal_text;
#  endif /* #ifndef NARGS */
{
	unsigned int  count_1;
	char         *signal_name_ptr = NULL;
	const char   *signal_code_ptr = NULL;
	const char   *signal_desc_ptr = NULL;
	char         *signal_addr_ptr = NULL;
	char          signal_name_buffer[GENFUNCS_MAX_ERROR_TEXT / 4];
	char          signal_code_buffer[GENFUNCS_MAX_ERROR_TEXT / 4];
	char          signal_desc_buffer[GENFUNCS_MAX_ERROR_TEXT / 4];
	char          signal_addr_buffer[GENFUNCS_MAX_ERROR_TEXT / 4];
	char          number_buffer[STR_VAL2STR_MAX_LEN + 1];

	*signal_text = '\0';

	for (count_1 = 0; count_1 < GENFUNCS_SignalCount; count_1++) {
		if (signal_number == GENFUNCS_SignalList[count_1].signal_number) {
			signal_name_ptr = GENFUNCS_SignalList[count_1].signal_name;
			signal_desc_ptr = GENFUNCS_SignalList[count_1].signal_description;
			break;
		}
	}

	if (signal_name_ptr == NULL)
		strcat(strcat(strcpy(signal_name_ptr = signal_name_buffer,
			"Invalid signal number encountered ("),
			val2str(((unsigned long) signal_number), 0, 10, NULL,
			number_buffer)), ")");
	else {
		switch (signal_number) {
			case SIGILL		:
				switch (signal_code) {
#ifdef sparc
					case ILL_STACK					:
						signal_code_ptr = " ILL_STACK";
						signal_desc_ptr = " bad stack";
						break;
					case ILL_ILLINSTR_FAULT		:
						signal_code_ptr = " ILL_ILLINSTR_FAULT";
						signal_desc_ptr = " illegal instruction";
						break;
					case ILL_PRIVINSTR_FAULT	:
						signal_code_ptr = " ILL_PRIVINSTR_FAULT";
						signal_desc_ptr = " privileged instruction violation";
						break;
#endif /* #ifdef sparc */
#ifdef mc68000
					case ILL_ILLINSTR_FAULT		:
						signal_code_ptr = " ILL_ILLINSTR_FAULT";
						signal_desc_ptr = " illegal instruction fault";
						break;
					case ILL_PRIVVIO_FAULT		:
						signal_code_ptr = " ILL_PRIVVIO_FAULT";
						signal_desc_ptr = " privilege violation fault";
						break;
					case ILL_COPROCERR_FAULT		:
						signal_code_ptr = " ILL_COPROCERR_FAULT";
						signal_desc_ptr = " coprocessor protocol error fault";
						break;
					case ILL_TRAP1_FAULT		:
						signal_code_ptr = " ILL_TRAP1_FAULT";
						signal_desc_ptr = " trap #1 fault";
						break;
					case ILL_TRAP2_FAULT		:
						signal_code_ptr = " ILL_TRAP2_FAULT";
						signal_desc_ptr = " trap #2 fault";
						break;
					case ILL_TRAP3_FAULT		:
						signal_code_ptr = " ILL_TRAP3_FAULT";
						signal_desc_ptr = " trap #3 fault";
						break;
					case ILL_TRAP4_FAULT		:
						signal_code_ptr = " ILL_TRAP4_FAULT";
						signal_desc_ptr = " trap #4 fault";
						break;
					case ILL_TRAP5_FAULT		:
						signal_code_ptr = " ILL_TRAP5_FAULT";
						signal_desc_ptr = " trap #5 fault";
						break;
					case ILL_TRAP6_FAULT		:
						signal_code_ptr = " ILL_TRAP6_FAULT";
						signal_desc_ptr = " trap #6 fault";
						break;
					case ILL_TRAP7_FAULT		:
						signal_code_ptr = " ILL_TRAP7_FAULT";
						signal_desc_ptr = " trap #7 fault";
						break;
					case ILL_TRAP8_FAULT		:
						signal_code_ptr = " ILL_TRAP8_FAULT";
						signal_desc_ptr = " trap #8 fault";
						break;
					case ILL_TRAP9_FAULT		:
						signal_code_ptr = " ILL_TRAP9_FAULT";
						signal_desc_ptr = " trap #9 fault";
						break;
					case ILL_TRAP10_FAULT		:
						signal_code_ptr = " ILL_TRAP10_FAULT";
						signal_desc_ptr = " trap #10 fault";
						break;
					case ILL_TRAP11_FAULT		:
						signal_code_ptr = " ILL_TRAP11_FAULT";
						signal_desc_ptr = " trap #11 fault";
						break;
					case ILL_TRAP12_FAULT		:
						signal_code_ptr = " ILL_TRAP12_FAULT";
						signal_desc_ptr = " trap #12 fault";
						break;
					case ILL_TRAP13_FAULT		:
						signal_code_ptr = " ILL_TRAP13_FAULT";
						signal_desc_ptr = " trap #13 fault";
						break;
					case ILL_TRAP14_FAULT		:
						signal_code_ptr = " ILL_TRAP14_FAULT";
						signal_desc_ptr = " trap #14 fault";
						break;
#endif /* #ifdef mc68000 */
#ifdef vax
					case ILL_RESAD_FAULT		:
						signal_code_ptr = " ILL_RESAD_FAULT";
						signal_desc_ptr = " reserved addressing fault";
						break;
					case ILL_PRIVIN_FAULT		:
						signal_code_ptr = " ILL_PRIVIN_FAULT";
						signal_desc_ptr = " privileged instruction fault";
						break;
					case ILL_RESOP_FAULT		:
						signal_code_ptr = " ILL_RESOP_FAULT";
						signal_desc_ptr = " reserved operand fault";
						break;
#endif /* #ifdef vax */
					default							:
						strcat(strcpy(signal_code_ptr = signal_code_buffer,
							" ILL_TRAP_FAULT_"),
							val2str(((unsigned long) signal_code), 0, 10, NULL,
							number_buffer));
						strcat(strcpy(signal_desc_ptr = signal_desc_buffer,
							" processor trap number "),
							val2str(((unsigned long) signal_code), 0, 10, NULL,
							number_buffer));
						break;
				}
				strcat(strcpy(signal_addr_ptr = signal_addr_buffer,
					" at address 0X"), val2str(((unsigned long) signal_address),
					0, 16, NULL, number_buffer));
				break;
#ifdef SIGEMT
			case SIGEMT		:
				switch (signal_code) {
# ifdef sparc
					case EMT_TAG	:
						signal_code_ptr = " EMT_TAG";
						signal_desc_ptr = " tag overflow";
						break;
# endif /* #ifdef sparc */
# ifdef mc68000
					case EMT_EMU1010		:
						signal_code_ptr = " EMT_EMU1010";
						signal_desc_ptr = " line 1010 emulator trap";
						break;
					case EMT_EMU1111		:
						signal_code_ptr = " EMT_EMU1111";
						signal_desc_ptr = " line 1111 emulator trap";
						break;
# endif /* #ifdef mc68000 */
					default			:
						strcat(strcpy(signal_code_buffer,
							" UNKNOWN SIGEMT SIGNAL CODE "),
							val2str(((unsigned long) signal_code), 0, 10, NULL,
							number_buffer));
						signal_code_ptr = signal_code_buffer;
						signal_desc_ptr = " ";
						break;
				}
				strcat(strcpy(signal_addr_ptr = signal_addr_buffer,
					" at address 0X"), val2str(((unsigned long) signal_address),
					0, 16, NULL, number_buffer));
				break;
#endif /* #ifdef SIGEMT */
			case SIGFPE		:
				switch (signal_code) {
#ifdef sparc
					case FPE_INTOVF_TRAP		:
						signal_code_ptr = " FPE_INTOVF_TRAP";
						signal_desc_ptr = " integer overflow";
						break;
					case FPE_STARTSIG_TRAP		:
						signal_code_ptr = " FPE_STARTSIG_TRAP";
						signal_desc_ptr = " process using fp";
						break;
					case FPE_INTDIV_TRAP		:
						signal_code_ptr = " FPE_INTDIV_TRAP";
						signal_desc_ptr = " integer division by zero";
						break;
					case FPE_FLTINEX_TRAP	:
						signal_code_ptr = " FPE_FLTINEX_TRAP";
						signal_desc_ptr = " IEEE floating point inexact";
						break;
					case FPE_FLTDIV_TRAP		:
						signal_code_ptr = " FPE_FLTDIV_TRAP";
						signal_desc_ptr = " IEEE floating point division by zero";
						break;
					case FPE_FLTUND_TRAP		:
						signal_code_ptr = " FPE_FLTUND_TRAP";
						signal_desc_ptr = " IEEE floating point underflow";
						break;
					case FPE_FLTOPERR_TRAP	:
						signal_code_ptr = " FPE_FLTOPERR_TRAP";
						signal_desc_ptr = " IEEE floating point operand error";
						break;
					case FPE_FLTOVF_TRAP		:
						signal_code_ptr = " FPE_FLTOVF_TRAP";
						signal_desc_ptr = " IEEE floating point overflow";
						break;
#endif /* #ifdef sparc */
#ifdef mc68000
					case FPE_INTDIV_TRAP		:
						signal_code_ptr = " FPE_INTDIV_TRAP";
						signal_desc_ptr = " integer divide by zero";
						break;
					case FPE_CHKINST_TRAP		:
						signal_code_ptr = " FPE_CHKINST_TRAP";
						signal_desc_ptr = " CHK [CHK2] instruction";
						break;
					case FPE_TRAPV_TRAP		:
						signal_code_ptr = " FPE_TRAPV_TRAP";
						signal_desc_ptr = " TRAPV [cpTRAPcc TRAPcc] instr";
						break;
					case FPE_FLTBSUN_TRAP		:
						signal_code_ptr = " FPE_FLTBSUN_TRAP";
						signal_desc_ptr = " branch or set on unordered cond";
						break;
					case FPE_FLTINEX_TRAP		:
						signal_code_ptr = " FPE_FLTINEX_TRAP";
						signal_desc_ptr = " [floating inexact result]";
						break;
					case FPE_FLTDIV_TRAP		:
						signal_code_ptr = " FPE_FLTDIV_TRAP";
						signal_desc_ptr = " [floating divide by zero]";
						break;
					case FPE_FLTUND_TRAP		:
						signal_code_ptr = " FPE_FLTUND_TRAP";
						signal_desc_ptr = " [floating underflow]";
						break;
					case FPE_FLTOPERR_TRAP		:
						signal_code_ptr = " FPE_FLTOPERR_TRAP";
						signal_desc_ptr = " [floating operand error]";
						break;
					case FPE_FLTOVF_TRAP		:
						signal_code_ptr = " FPE_FLTOVF_TRAP";
						signal_desc_ptr = " [floating overflow]";
						break;
					case FPE_FLTNAN_TRAP		:
						signal_code_ptr = " FPE_FLTNAN_TRAP";
						signal_desc_ptr = " [floating Not-A-Number]";
						break;
# ifdef sun
					case FPE_FPA_ENABLE		:
						signal_code_ptr = " FPE_FPA_ENABLE";
						signal_desc_ptr = " [FPA not enabled]";
						break;
					case FPE_FPA_ERROR		:
						signal_code_ptr = " FPE_FPA_ERROR";
						signal_desc_ptr = " [FPA arithmetic exception]";
						break;
# endif /* #endif sun */
#endif /* #ifdef mc68000 */
#ifdef vax
					case FPE_INTOVF_TRAP		:
						signal_code_ptr = " FPE_INTOVF_TRAP";
						signal_desc_ptr = " integer overflow";
						break;
					case FPE_INTDIV_TRAP		:
						signal_code_ptr = " FPE_INTDIV_TRAP";
						signal_desc_ptr = " integer divide by zero";
						break;
					case FPE_FLTOVF_TRAP		:
						signal_code_ptr = " FPE_FLTOVF_TRAP";
						signal_desc_ptr = " floating overflow";
						break;
					case FPE_FLTDIV_TRAP		:
						signal_code_ptr = " FPE_FLTDIV_TRAP";
						signal_desc_ptr = " floating/decimal divide by zero";
						break;
					case FPE_FLTUND_TRAP		:
						signal_code_ptr = " FPE_FLTUND_TRAP";
						signal_desc_ptr = " floating underflow";
						break;
					case FPE_DECOVF_TRAP		:
						signal_code_ptr = " FPE_DECOVF_TRAP";
						signal_desc_ptr = " decimal overflow";
						break;
					case FPE_SUBRNG_TRAP		:
						signal_code_ptr = " FPE_SUBRNG_TRAP";
						signal_desc_ptr = " subscript out of range";
						break;
					case FPE_FLTOVF_FAULT		:
						signal_code_ptr = " FPE_FLTOVF_FAULT";
						signal_desc_ptr = " floating overflow fault";
						break;
					case FPE_FLTDIV_FAULT		:
						signal_code_ptr = " FPE_FLTDIV_FAULT";
						signal_desc_ptr = " divide by zero floating fault";
						break;
					case FPE_FLTUND_FAULT		:
						signal_code_ptr = " FPE_FLTUND_FAULT";
						signal_desc_ptr = " floating underflow fault";
						break;
#endif /* #endif vax */
					default						:
						strcat(strcpy(signal_code_buffer,
							" UNKNOWN SIGFPE SIGNAL CODE "),
							val2str(((unsigned long) signal_code), 0, 10, NULL,
							number_buffer));
						signal_code_ptr = signal_code_buffer;
						signal_desc_ptr = " ";
						break;
				}
				strcat(strcpy(signal_addr_ptr = signal_addr_buffer,
					" at address 0X"), val2str(((unsigned long) signal_address),
					0, 16, NULL, number_buffer));
				break;
			case SIGBUS		:
				switch (signal_code) {
#ifdef sparc
					case BUS_HWERR	:
						signal_code_ptr = " BUS_HWERR";
						signal_desc_ptr = " miscellaneous hardware bus error \
(for example, timeout)";
						break;
					case BUS_ALIGN	:
						signal_code_ptr = " BUS_ALIGN";
						signal_desc_ptr = " hardware address alignment error";
						break;
#endif /* #ifdef sparc */
					default			:
#ifdef sparc
						if (BUS_CODE(signal_code) == BUS_OBJERR) {
							strcat(strcat(strcpy(signal_desc_buffer,
						" underlying file object mapped at the fault address 0X"),
								val2str(((unsigned long) signal_address), 0, 16,
								NULL, number_buffer)), " returned an error: ");
							GEN_GetErrorString(((int) BUS_ERRNO(signal_code)),
								GENFUNCS_FALSE, sizeof(signal_desc_buffer) -
								(strlen(signal_desc_buffer) + 1),
								signal_desc_buffer + strlen(signal_desc_buffer));
							signal_code_ptr = " BUS_OBJERR";
							signal_desc_ptr = signal_desc_buffer;
						}
						else {
#endif /* #ifdef sparc */
							strcat(strcpy(signal_code_buffer,
								" UNKNOWN SIGBUS SIGNAL CODE "),
								val2str(((unsigned long) signal_code), 0, 10, NULL,
								number_buffer));
							signal_code_ptr = signal_code_buffer;
							signal_desc_ptr = " ";
#ifdef sparc
						}
#endif /* #ifdef sparc */
						break;
				}
				strcat(strcpy(signal_addr_ptr = signal_addr_buffer,
					" at address 0X"), val2str(((unsigned long) signal_address),
					0, 16, NULL, number_buffer));
				break;
			case SIGSEGV	:
				switch (signal_code) {
#ifdef sparc
					case SEGV_NOMAP	:
						signal_code_ptr = " SEGV_NOMAP";
						signal_desc_ptr = " no mapping fault";
						break;
					case SEGV_PROT		:
						signal_code_ptr = " SEGV_PROT";
						signal_desc_ptr = " protection fault";
						break;
#endif /* #ifdef sparc */
					default:
#ifdef sparc
						if (SEGV_CODE(signal_code) == SEGV_OBJERR) {
							strcat(strcat(strcpy(signal_desc_buffer,
						" underlying file object mapped at the fault address 0X"),
								val2str(((unsigned long) signal_address), 0, 16,
								NULL, number_buffer)), " returned an error: ");
							signal_code_ptr = " SEGV_OBJERR";
							GEN_GetErrorString(((int) SEGV_ERRNO(signal_code)),
								GENFUNCS_FALSE, sizeof(signal_desc_buffer) -
								(strlen(signal_desc_buffer) + 1),
								signal_desc_buffer + strlen(signal_desc_buffer));
							signal_code_ptr = " SEGV_OBJERR";
							signal_desc_ptr = signal_desc_buffer;
						}
						else {
#endif /* #ifdef sparc */
							strcat(strcpy(signal_code_buffer,
								" UNKNOWN SIGSEGV SIGNAL CODE "),
								val2str(((unsigned long) signal_code), 0, 10, NULL,
								number_buffer));
							signal_code_ptr = signal_code_buffer;
							signal_desc_ptr = " ";
#ifdef sparc
						}
#endif /* #ifdef sparc */
						break;
				}
				strcat(strcpy(signal_addr_ptr = signal_addr_buffer,
					" at address 0X"), val2str(((unsigned long) signal_address),
					0, 16, NULL, number_buffer));
				break;
			default			:
				break;
		}
	}

	signal_code_ptr = (signal_code_ptr != NULL) ? signal_code_ptr : " ";
	signal_desc_ptr = (signal_desc_ptr != NULL) ? signal_desc_ptr :
		" *** UNABLE TO DESCRIBE SIGNAL ***";
	signal_addr_ptr = (signal_addr_ptr != NULL) ? signal_addr_ptr : " ";

	return(trim(oneblank(strcat(strcat(strcat(strcpy(signal_text,
		signal_name_ptr), signal_code_ptr), signal_desc_ptr),
		signal_addr_ptr))));
}
# endif /* # ifdef __SVR4 */
#endif /* #ifdef __MSDOS__ */

#ifdef TEST_MAIN

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static int ThisPID  = 0;
static int OnceFlag = 0;

#ifdef __MSDOS__
static const int TEST_SignalList[] = {
	0,
	SIGINT,
	SIGTERM,
	SIGABRT
};
#elif _Windows
static const int TEST_SignalList[] = {
	0,
	SIGINT,
	SIGTERM,
	SIGABRT
};
#else
#include <setjmp.h>

static int     TEST_LongJmpFlag = 0;

static jmp_buf TEST_LongJmpEnv;

typedef struct {
	int   signal_number;
	int   signal_code;
	void *signal_address;
} TEST_DATA;

# ifdef __SVR4
static const TEST_DATA *TEST_SignalPtr;
static const TEST_DATA  TEST_SignalList[] = {
	{	0,				1234567890,				((void *) 0X87654321)	},
	{	SIGHUP,		1234567890,				((void *) 0X87654321)	},
	{	SIGINT,		1234567890,				((void *) 0X87654321)	},
	{	SIGQUIT,		1234567890,				((void *) 0X87654321)	},
	{	SIGILL,		ILL_ILLOPC,				((void *) 0X87654321)	},
	{	SIGILL,		ILL_ILLOPN,				((void *) 0X87654321)	},
	{	SIGILL,		ILL_ILLADR,				((void *) 0X87654321)	},
	{	SIGILL,		ILL_ILLTRP,				((void *) 0X87654321)	},
	{	SIGILL,		ILL_PRVOPC,				((void *) 0X87654321)	},
	{	SIGILL,		ILL_PRVREG,				((void *) 0X87654321)	},
	{	SIGILL,		ILL_COPROC,				((void *) 0X87654321)	},
	{	SIGILL,		ILL_BADSTK,				((void *) 0X87654321)	},
	{	SIGILL,		1234567890,				((void *) 0X87654321)	},
	{	SIGTRAP,		TRAP_BRKPT,				((void *) 0X87654321)	},
	{	SIGTRAP,		TRAP_TRACE,				((void *) 0X87654321)	},
	{	SIGTRAP,		1234567890,				((void *) 0X87654321)	},
	{	SIGABRT,		1234567890,				((void *) 0X87654321)	},
	{	SIGEMT,		1234567890,				((void *) 0X87654321)	},
	{	SIGFPE,		FPE_INTDIV,				((void *) 0X87654321)	},
	{	SIGFPE,		FPE_INTOVF,				((void *) 0X87654321)	},
	{	SIGFPE,		FPE_FLTDIV,				((void *) 0X87654321)	},
	{	SIGFPE,		FPE_FLTOVF,				((void *) 0X87654321)	},
	{	SIGFPE,		FPE_FLTUND,				((void *) 0X87654321)	},
	{	SIGFPE,		FPE_FLTRES,				((void *) 0X87654321)	},
	{	SIGFPE,		FPE_FLTINV,				((void *) 0X87654321)	},
	{	SIGFPE,		FPE_FLTSUB,				((void *) 0X87654321)	},
	{	SIGFPE,		1234567890,				((void *) 0X87654321)	},
	{	SIGKILL,		1234567890,				((void *) 0X87654321)	},
	{	SIGBUS,		BUS_ADRALN,				((void *) 0X87654321)	},
	{	SIGBUS,		BUS_ADRERR,				((void *) 0X87654321)	},
	{	SIGBUS,		BUS_OBJERR,				((void *) 0X87654321)	},
	{	SIGBUS,		1234567890,				((void *) 0X87654321)	},
	{	SIGSEGV,		SEGV_MAPERR,			((void *) 0X87654321)	},
	{	SIGSEGV,		SEGV_ACCERR,			((void *) 0X87654321)	},
	{	SIGSEGV,		1234567890,				((void *) 0X87654321)	},
	{	SIGSYS,		1234567890,				((void *) 0X87654321)	},
	{	SIGPIPE,		1234567890,				((void *) 0X87654321)	},
	{	SIGALRM,		1234567890,				((void *) 0X87654321)	},
	{	SIGTERM,		1234567890,				((void *) 0X87654321)	},
	{	SIGUSR1,		1234567890,				((void *) 0X87654321)	},
	{	SIGUSR2,		1234567890,				((void *) 0X87654321)	},
	{	SIGCHLD,		CLD_EXITED,				((void *) 0X87654321)	},
	{	SIGCHLD,		CLD_KILLED,				((void *) 0X87654321)	},
	{	SIGCHLD,		CLD_DUMPED,				((void *) 0X87654321)	},
	{	SIGCHLD,		CLD_TRAPPED,			((void *) 0X87654321)	},
	{	SIGCHLD,		CLD_STOPPED,			((void *) 0X87654321)	},
	{	SIGCHLD,		CLD_CONTINUED,			((void *) 0X87654321)	},
	{	SIGCHLD,		1234567890,				((void *) 0X87654321)	},
	{	SIGPWR,		1234567890,				((void *) 0X87654321)	},
	{	SIGWINCH,	1234567890,				((void *) 0X87654321)	},
	{	SIGURG,		1234567890,				((void *) 0X87654321)	},
	{	SIGPOLL,		POLL_IN,					((void *) 0X87654321)	},
	{	SIGPOLL,		POLL_OUT,				((void *) 0X87654321)	},
	{	SIGPOLL,		POLL_MSG,				((void *) 0X87654321)	},
	{	SIGPOLL,		POLL_ERR,				((void *) 0X87654321)	},
	{	SIGPOLL,		POLL_PRI,				((void *) 0X87654321)	},
	{	SIGPOLL,		POLL_HUP,				((void *) 0X87654321)	},
	{	SIGPOLL,		1234567890,				((void *) 0X87654321)	},
	{	SIGSTOP,		1234567890,				((void *) 0X87654321)	},
	{	SIGTSTP,		1234567890,				((void *) 0X87654321)	},
	{	SIGCONT,		1234567890,				((void *) 0X87654321)	},
	{	SIGCHLD,		1234567890,				((void *) 0X87654321)	},
	{	SIGTTIN,		1234567890,				((void *) 0X87654321)	},
	{	SIGTTOU,		1234567890,				((void *) 0X87654321)	},
	{	SIGVTALRM,	1234567890,				((void *) 0X87654321)	},
	{	SIGPROF,		1234567890,				((void *) 0X87654321)	},
	{	SIGXCPU,		1234567890,				((void *) 0X87654321)	},
	{	SIGXFSZ,		1234567890,				((void *) 0X87654321)	},
	{	SIGWAITING,	1234567890,				((void *) 0X87654321)	},
	{	SIGLWP,		1234567890,				((void *) 0X87654321)	},
	{	SIGFREEZE,	1234567890,				((void *) 0X87654321)	},
	{	SIGTHAW,		1234567890,				((void *) 0X87654321)	},
	{	SIGCANCEL,	1234567890,				((void *) 0X87654321)	},
	{	SIGLOST,		1234567890,				((void *) 0X87654321)	},
	{	SIGLOST+1,	1234567890,				((void *) 0X87654321)	},
	{	SIGLOST+2,	1234567890,				((void *) 0X87654321)	},
	{	SIGLOST+3,	1234567890,				((void *) 0X87654321)	},
/*
	,
	{	SIGRTMIN,	1234567890,				((void *) 0X87654321)	},
	{	SIGRTMAX,	1234567890,				((void *) 0X87654321)	}
*/
};
# else
static const TEST_DATA TEST_SignalList[] = {
	{	0,				1234567890,				((void *) 0X87654321)	},
	{	SIGHUP,		1234567890,				((void *) 0X87654321)	},
	{	SIGINT,		1234567890,				((void *) 0X87654321)	},
	{	SIGQUIT,		1234567890,				((void *) 0X87654321)	},
#  ifdef sparc
	{	SIGILL,		ILL_STACK,				((void *) 0X87654321)	},
	{	SIGILL,		ILL_ILLINSTR_FAULT,	((void *) 0X87654321)	},
	{	SIGILL,		ILL_PRIVINSTR_FAULT,	((void *) 0X87654321)	},
#  endif /* #ifdef sparc */
#  ifdef mc68000
	{	SIGILL,		ILL_ILLINSTR_FAULT,	((void *) 0X87654321)	},
	{	SIGILL,		ILL_PRIVVIO_FAULT,	((void *) 0X87654321)	},
	{	SIGILL,		ILL_COPROCERR_FAULT,	((void *) 0X87654321)	},
	{	SIGILL,		ILL_TRAP1_FAULT,		((void *) 0X87654321)	},
	{	SIGILL,		ILL_TRAP2_FAULT,		((void *) 0X87654321)	},
	{	SIGILL,		ILL_TRAP3_FAULT,		((void *) 0X87654321)	},
	{	SIGILL,		ILL_TRAP4_FAULT,		((void *) 0X87654321)	},
	{	SIGILL,		ILL_TRAP5_FAULT,		((void *) 0X87654321)	},
	{	SIGILL,		ILL_TRAP6_FAULT,		((void *) 0X87654321)	},
	{	SIGILL,		ILL_TRAP7_FAULT,		((void *) 0X87654321)	},
	{	SIGILL,		ILL_TRAP8_FAULT,		((void *) 0X87654321)	},
	{	SIGILL,		ILL_TRAP9_FAULT,		((void *) 0X87654321)	},
	{	SIGILL,		ILL_TRAP10_FAULT,		((void *) 0X87654321)	},
	{	SIGILL,		ILL_TRAP11_FAULT,		((void *) 0X87654321)	},
	{	SIGILL,		ILL_TRAP12_FAULT,		((void *) 0X87654321)	},
	{	SIGILL,		ILL_TRAP13_FAULT,		((void *) 0X87654321)	},
	{	SIGILL,		ILL_TRAP14_FAULT,		((void *) 0X87654321)	},
#  endif /* #ifdef mc68000 */
#  ifdef vax
	{	SIGILL,		ILL_RESAD_FAULT,		((void *) 0X87654321)	},
	{	SIGILL,		ILL_PRIVIN_FAULT,		((void *) 0X87654321)	},
	{	SIGILL,		ILL_RESOP_FAULT,		((void *) 0X87654321)	},
#  endif /* #ifdef vax */
	{	SIGILL,		1234567890,				((void *) 0X87654321)	},
	{	SIGTRAP,		1234567890,				((void *) 0X87654321)	},
	{	SIGIOT,		1234567890,				((void *) 0X87654321)	},
#  ifdef sparc
	{	SIGEMT,		EMT_TAG,					((void *) 0X87654321)	},
#  endif /* #ifdef sparc */
#  ifdef mc68000
	{	SIGEMT,		EMT_EMU1010,			((void *) 0X87654321)	},
	{	SIGEMT,		EMT_EMU1111,			((void *) 0X87654321)	},
#  endif /* #ifdef mc68000 */
	{	SIGEMT,		1234567890,				((void *) 0X87654321)	},
#  ifdef sparc
	{	SIGFPE,		FPE_INTOVF_TRAP,		((void *) 0X87654321)	},
	{	SIGFPE,		FPE_STARTSIG_TRAP,	((void *) 0X87654321)	},
	{	SIGFPE,		FPE_INTDIV_TRAP,		((void *) 0X87654321)	},
	{	SIGFPE,		FPE_FLTINEX_TRAP,		((void *) 0X87654321)	},
	{	SIGFPE,		FPE_FLTDIV_TRAP,		((void *) 0X87654321)	},
	{	SIGFPE,		FPE_FLTUND_TRAP,		((void *) 0X87654321)	},
	{	SIGFPE,		FPE_FLTOPERR_TRAP,	((void *) 0X87654321)	},
	{	SIGFPE,		FPE_FLTOVF_TRAP,		((void *) 0X87654321)	},
	{	SIGFPE,		FPE_INTOVF_TRAP,		((void *) 0X87654321)	},
#  endif /* #ifdef sparc */
#  ifdef mc68000
	{	SIGFPE,		FPE_INTDIV_TRAP,		((void *) 0X87654321)	},
	{	SIGFPE,		FPE_CHKINST_TRAP,		((void *) 0X87654321)	},
	{	SIGFPE,		FPE_TRAPV_TRAP,		((void *) 0X87654321)	},
	{	SIGFPE,		FPE_FLTBSUN_TRAP,		((void *) 0X87654321)	},
	{	SIGFPE,		FPE_FLTINEX_TRAP,		((void *) 0X87654321)	},
	{	SIGFPE,		FPE_FLTDIV_TRAP,		((void *) 0X87654321)	},
	{	SIGFPE,		FPE_FLTUND_TRAP,		((void *) 0X87654321)	},
	{	SIGFPE,		FPE_FLTOPERR_TRAP,	((void *) 0X87654321)	},
	{	SIGFPE,		FPE_FLTOVF_TRAP,		((void *) 0X87654321)	},
	{	SIGFPE,		FPE_FLTNAN_TRAP,		((void *) 0X87654321)	},
#   ifdef sun
	{	SIGFPE,		FPE_FPA_ENABLE,		((void *) 0X87654321)	},
	{	SIGFPE,		FPE_FPA_ERROR,			((void *) 0X87654321)	},
#   endif /* #endif sun */
#  endif /* #ifdef mc68000 */
#  ifdef vax
	{	SIGFPE,		FPE_INTOVF_TRAP,		((void *) 0X87654321)	},
	{	SIGFPE,		FPE_INTDIV_TRAP,		((void *) 0X87654321)	},
	{	SIGFPE,		FPE_FLTOVF_TRAP,		((void *) 0X87654321)	},
	{	SIGFPE,		FPE_FLTDIV_TRAP,		((void *) 0X87654321)	},
	{	SIGFPE,		FPE_FLTUND_TRAP,		((void *) 0X87654321)	},
	{	SIGFPE,		FPE_DECOVF_TRAP,		((void *) 0X87654321)	},
	{	SIGFPE,		FPE_SUBRNG_TRAP,		((void *) 0X87654321)	},
	{	SIGFPE,		FPE_FLTOVF_FAULT,		((void *) 0X87654321)	},
	{	SIGFPE,		FPE_FLTDIV_FAULT,		((void *) 0X87654321)	},
	{	SIGFPE,		FPE_FLTUND_FAULT,		((void *) 0X87654321)	},
#  endif /* #endif vax */
	{	SIGFPE,		1234567890,				((void *) 0X87654321)	},
	{	SIGKILL,		1234567890,				((void *) 0X87654321)	},
	{	SIGBUS,		BUS_HWERR,				((void *) 0X87654321)	},
	{	SIGBUS,		BUS_ALIGN,				((void *) 0X87654321)	},
	{	SIGBUS,		FC_MAKE_ERR(EIO),		((void *) 0X87654321)	},
	{	SIGBUS,		1234567890,				((void *) 0X87654321)	},
	{	SIGSEGV,		SEGV_NOMAP,				((void *) 0X87654321)	},
	{	SIGSEGV,		SEGV_PROT,				((void *) 0X87654321)	},
	{	SIGSEGV,		FC_MAKE_ERR(EIO),		((void *) 0X87654321)	},
	{	SIGSEGV,		1234567890,				((void *) 0X87654321)	},
	{	SIGSYS,		1234567890,				((void *) 0X87654321)	},
	{	SIGPIPE,		1234567890,				((void *) 0X87654321)	},
	{	SIGALRM,		1234567890,				((void *) 0X87654321)	},
	{	SIGTERM,		1234567890,				((void *) 0X87654321)	},
	{	SIGURG,		1234567890,				((void *) 0X87654321)	},
	{	SIGSTOP,		1234567890,				((void *) 0X87654321)	},
	{	SIGTSTP,		1234567890,				((void *) 0X87654321)	},
	{	SIGCONT,		1234567890,				((void *) 0X87654321)	},
	{	SIGCHLD,		1234567890,				((void *) 0X87654321)	},
	{	SIGTTIN,		1234567890,				((void *) 0X87654321)	},
	{	SIGTTOU,		1234567890,				((void *) 0X87654321)	},
	{	SIGIO,		1234567890,				((void *) 0X87654321)	},
	{	SIGXCPU,		1234567890,				((void *) 0X87654321)	},
	{	SIGXFSZ,		1234567890,				((void *) 0X87654321)	},
	{	SIGVTALRM,	1234567890,				((void *) 0X87654321)	},
	{	SIGPROF,		1234567890,				((void *) 0X87654321)	},
	{	SIGWINCH,	1234567890,				((void *) 0X87654321)	},
	{	SIGLOST,		1234567890,				((void *) 0X87654321)	},
	{	SIGUSR1,		1234567890,				((void *) 0X87654321)	},
	{	SIGUSR2,		1234567890,				((void *) 0X87654321)	}
};
# endif /* # ifdef __SVR4 */
#endif /* #ifdef __MSDOS__ */

static const unsigned int TEST_SignalCount =
	sizeof(TEST_SignalList) / sizeof(TEST_SignalList[0]);

COMPAT_FN_DECL(int         main, (int, char **));
COMPAT_FN_DECL_STATIC(void do_test_list, (void));

#ifdef __MSDOS__
COMPAT_FN_DECL_STATIC(void catch_a_signal, (int));
#elif _Windows
COMPAT_FN_DECL_STATIC(void catch_a_signal, (int));
#else
# ifdef __SVR4
COMPAT_FN_DECL_STATIC(void catch_a_signal,
	(int sig, siginfo_t *siginfo_ptr, void *addr));
# else
COMPAT_FN_DECL_STATIC(void catch_a_signal,
	(int signal_number, int signal_code, struct sigcontext *signal_context,
	char *signal_address));
# endif /* # ifdef __SVR4 */
#endif /* #ifdef __MSDOS__ */
 
#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;
	unsigned int count_2;
#ifndef __MSDOS__
# ifndef _Windows
	unsigned int tmp_u_int;
# endif /* # ifndef _Windows */
#endif /* #ifndef __MSDOS__ */

	fprintf(stderr, "Test routine for function 'GEN_GetSignalText()'\n");
	fprintf(stderr, "---- ------- --- -------- ---------------------\n\n");

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if ((!stricmp(argv[count_1], "-HELP")) ||
			(!stricmp(argv[count_1], "-H"))) {
#ifdef __MSDOS__
			fprintf(stderr, "USAGE:\n   %s [ %s | %s ]\n\n", argv[0],
				"-H[ELP]", "<signal-name> [<signal-name> . . .]");
#elif _Windows
			fprintf(stderr, "USAGE:\n   %s [ %s | %s ]\n\n", argv[0],
				"-H[ELP]", "<signal-name> [<signal-name> . . .]");
#else
			fprintf(stderr, "USAGE:\n   %s [ %s | %s | %s ]\n\n", argv[0],
				"-H[ELP]", "-WAIT", "<signal-name> [<signal-name> . . .]");
#endif /* #ifdef __MSDOS__ */
			goto EXIT_FUNCTION;
		}
	}

#ifdef __MSDOS__
	for (count_1 = 0; count_1 < GENFUNCS_SignalCount; count_1++)
		signal(GENFUNCS_SignalList[count_1].signal_number, catch_a_signal);
#elif _Windows
	for (count_1 = 0; count_1 < GENFUNCS_SignalCount; count_1++)
		signal(GENFUNCS_SignalList[count_1].signal_number, catch_a_signal);
#elif __SVR4
	for (count_1 = 0; count_1 < GENFUNCS_SignalCount; count_1++)
		signal(GENFUNCS_SignalList[count_1].signal_number,
			((void (*)(int)) catch_a_signal));
#else
	for (count_1 = 0; count_1 < GENFUNCS_SignalCount; count_1++)
		signal(GENFUNCS_SignalList[count_1].signal_number, catch_a_signal);
#endif /* #ifdef __MSDOS__ */

#ifndef __MSDOS__
# ifndef _Windows
	ThisPID = getpid();
# endif /* # ifndef _Windows */
#endif /* #ifndef __MSDOS__ */

	if (argc == 1) {
		do_test_list();
		goto EXIT_FUNCTION;
	}
#ifndef __MSDOS__
# ifndef _Windows
	else if ((argc > 1) && (!stricmp(argv[1], "-WAIT"))) {
		fprintf(stderr,
			"\nProcess %u waiting for a signal (kill with 'kill -9 %u) . . .",
			ThisPID, ThisPID);
		while (1) pause();
	}
# endif /* # ifndef _Windows */
#endif /* #ifndef __MSDOS__ */

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		for (count_2 = 0; count_2 < GENFUNCS_SignalCount; count_2++) {
			if (!stricmp(argv[count_1],
				GENFUNCS_SignalList[count_2].signal_name)) {
#ifdef __MSDOS__
				raise(GENFUNCS_SignalList[count_2].signal_number);
#elif _Windows
				raise(GENFUNCS_SignalList[count_2].signal_number);
#else
				if (GENFUNCS_SignalList[count_2].signal_number == SIGSEGV) {
					fprintf(stderr, "Will force a SIGSEGV at address 0.\n");
					TEST_LongJmpFlag = 1;
					if (!setjmp(TEST_LongJmpEnv))
						tmp_u_int = *((unsigned int *) 0);
				}
				else if (GENFUNCS_SignalList[count_2].signal_number == SIGBUS) {
					fprintf(stderr,
						"Will force a SIGBUS at address %u (0X%08X).\n",
						1234567891, 1234567891);
					TEST_LongJmpFlag = 1;
					if (!setjmp(TEST_LongJmpEnv))
						tmp_u_int = *((unsigned int *) 1234567891);
				}
				else
					kill(ThisPID, GENFUNCS_SignalList[count_2].signal_number);
#endif /* #ifdef __MSDOS__ */
				break;
			}
		}
	}

EXIT_FUNCTION:

	return(0);
}

static void do_test_list()
{
	unsigned int count_1;
	char         signal_text[GENFUNCS_MAX_ERROR_TEXT];
#ifdef __SVR4
	siginfo_t    sig_data;

	memset(&sig_data, '\0', sizeof(sig_data));
#endif /* # ifdef __SVR4 */

	for (count_1 = 0; count_1 < TEST_SignalCount; count_1++) {
#ifdef __MSDOS__
		printf("[%05u]:%s\n", count_1,
			GEN_GetSignalText(TEST_SignalList[count_1], signal_text));
#elif _Windows
		printf("[%05u]:%s\n", count_1,
			GEN_GetSignalText(TEST_SignalList[count_1], signal_text));
#else
# ifdef __SVR4
		sig_data.si_signo           = TEST_SignalList[count_1].signal_number;
		sig_data.si_errno           = 0;
		sig_data.si_code            = TEST_SignalList[count_1].signal_code;
		sig_data.si_value.sival_ptr = TEST_SignalList[count_1].signal_address;
		TEST_SignalPtr = TEST_SignalList + count_1;
		printf("[%05u]:%s\n", count_1,
			GEN_GetSignalText(TEST_SignalList[count_1].signal_number,
			&sig_data, TEST_SignalList[count_1].signal_address, signal_text));
# else
		printf("[%05u]:%s\n", count_1,
			GEN_GetSignalText(TEST_SignalList[count_1].signal_number,
			TEST_SignalList[count_1].signal_code,
			TEST_SignalList[count_1].signal_address, signal_text));
# endif /* # ifdef __SVR4 */
#endif /* #ifdef __MSDOS__ */
	}
}

#ifdef __MSDOS__
# ifndef NARGS
static void catch_a_signal(int signal_number)
# else
static void catch_a_signal(signal_number)
int signal_number;
# endif /* #ifndef NARGS */
{
	char signal_text[GENFUNCS_MAX_ERROR_TEXT];

	fprintf(stderr, "PROCESS %u SIGNAL CATCHER REPORTS: %s\n", ThisPID,
		GEN_GetSignalText(signal_number, signal_text));

	if (OnceFlag) { fputs("Exiting . . .\n", stderr); exit(0); }
}
#elif _Windows
# ifndef NARGS
static void catch_a_signal(int signal_number)
# else
static void catch_a_signal(signal_number)
int signal_number;
# endif /* #ifndef NARGS */
{
	char signal_text[GENFUNCS_MAX_ERROR_TEXT];

	fprintf(stderr, "PROCESS %u SIGNAL CATCHER REPORTS: %s\n", ThisPID,
		GEN_GetSignalText(signal_number, signal_text));

	if (OnceFlag) { fputs("Exiting . . .\n", stderr); exit(0); }
}
#else
# ifdef __SVR4
#  ifndef NARGS
static void catch_a_signal(int signal_number, siginfo_t *siginfo_ptr,
	void *signal_address)
#  else
static void catch_a_signal(signal_number, siginfo_ptr, signal_address)
int        signal_number;
siginfo_t *siginfo_ptr;
void      *signal_address;
#  endif /* #ifndef NARGS */
{
	char signal_text[GENFUNCS_MAX_ERROR_TEXT];

	fprintf(stderr, "PROCESS %u SIGNAL CATCHER REPORTS: %s\n", ThisPID,
		GEN_GetSignalText(signal_number, siginfo_ptr, signal_address,
		signal_text));

	if (OnceFlag) { fputs("Exiting . . .\n", stderr); exit(0); }
}
/*
	CODE NOTE: To be removed.
static int sigaction(in_signal, in_action, out_action)
int                     in_signal;
const struct sigaction *in_action;
struct sigaction       *out_action;
{
	out_action->si_signo           = TEST_SignalPtr->signal_number;
	out_action->si_errno           = 0;
	out_action->si_code            = TEST_SignalPtr->signal_code;
	out_action->si_value.sival_ptr = TEST_SignalPtr->signal_address;
}
*/
# else
#  ifndef NARGS
static void catch_a_signal(int signal_number, int signal_code,
	struct sigcontext *signal_context, char *signal_address)
#  else
static void catch_a_signal(signal_number, signal_code, signal_context,
	signal_address)
int                signal_number;
int                signal_code;
struct sigcontext *signal_context;
char              *signal_address;
#  endif /* #ifndef NARGS */
{
	char signal_text[GENFUNCS_MAX_ERROR_TEXT];

	fprintf(stderr, "PROCESS %u SIGNAL CATCHER REPORTS: %s:%d\n", ThisPID,
		GEN_GetSignalText(signal_number, signal_code, signal_address,
		signal_text), OnceFlag);

	if (OnceFlag) { fputs("Exiting . . .\n", stderr); exit(0); }

	if (TEST_LongJmpFlag &&
		((signal_number == SIGSEGV) || (signal_number == SIGBUS)))
		longjmp(TEST_LongJmpEnv, -1);
}
# endif /* # ifdef __SVR4 */
#endif /* #ifdef __MSDOS__ */

#endif /* #ifdef TEST_MAIN */

