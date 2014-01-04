/* *********************************************************************** */
/* *********************************************************************** */
/*	GENFUNCS General Functions Library Source Module								*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Retrieves operating system error strings.

	Revision History	:	1992-06-09 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Include necessary header files . . .											*/
/* *********************************************************************** */

#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include <strfuncs.h>

#include "genfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/*		The list of error descriptions for various operating systems . . .	*/
/* *********************************************************************** */

#ifdef __MSDOS__
static const GEN_ERROR_SPEC GEN_ErrorList[] = {
	{  EZERO,				"EZERO",
		"Error 0 / No error detected",
		"No error encountered."
	},
	{	EINVFNC,				"EINVFNC",
		"Invalid function number",
		"Invalid function number."
	},
	{	ENOFILE,				"ENOFILE",
		"File not found",
		"File not found."
	},
	{	ENOPATH,				"ENOPATH",
		"Path not found",
		"Path not found."
	},
	{	ECONTR,				"ECONTR",
		"Memory blocks destroyed",
		"Memory blocks destroyed."
	},
	{	EINVMEM,				"EINVMEM",
		"Invalid memory block address",
		"Invalid memory block address."
	},
	{	EINVENV,				"EINVENV",
		"Invalid environment",
		"Invalid environment."
	},
	{	EINVFMT,				"EINVFMT",
		"Invalid format",
		"Invalid format."
	},
	{	EINVACC,				"EINVACC",
		"Invalid access code",
		"Invalid access code."
	},
	{	EINVDAT,				"EINVDAT",
		"Invalid data",
		"Invalid data."
	},
	{	EINVDRV,				"EINVDRV",
		"Invalid drive specified",
		"Invalid drive specified."
	},
	{	ECURDIR,				"ECURDIR",
		"Attempt to remove current directory",
		"Attempt to remove current directory."
	},
	{	ENOTSAM,				"ENOTSAM",
		"Not same device",
		"Not same device."
	},
	{	ENMFILE,				"ENMFILE",
		"No more files",
		"No more files."
	},
	{  ENOENT,				"ENOENT",
		"No such file or directory",
		"This error occurs when a file name is specified and the file should \
exist but does not, or when one of the directories in a path name does not \
exist."
	},
	{	EMFILE,				"EMFILE",
		"Too many open files",
		"A process tried to have more open files than the system allows a \
process to have. The customary configuration limit is 64 per process."
	},
	{	EACCES,				"EACCES",
		"Permission denied",
		"An attempt was made to access a file in a way forbidden by the \
protection system."
	},
	{  EBADF,				"EBADF",
		"Bad file number",
		"Either a file descriptor refers to no open file, or a read \
(respectively, write) request is made to a file that is open only for \
writing (respectively, reading)."
	},
	{	ENOMEM,				"ENOMEM",
		"Not enough memory",
		"During an execve(), sbrk(), or brk(), a program asks for more address \
space or swap space than the system is able to supply, or a process size \
limit would be exceeded. A lack of swap space is normally a temporary \
condition; however, a lack of address space is not a temporary condition. \
The maximum size of the text, data, and stack segments is a system \
parameter.  Soft limits may be increased to their corresponding hard limits."
	},
	{	EFAULT,				"EFAULT",
		"Bad address",
		"The system encountered a hardware fault in attempting to access the \
arguments of a system call."
	},
	{	ENODEV,				"ENODEV",
		"No such device",
		"An attempt was made to apply an inappropriate system call to a device \
(for example, an attempt to read a write-only device) or an attempt was made \
to use a device not configured by the system."
	},
	{	EINVAL,				"EINVAL",
		"Invalid argument",
		"A system call was made with an invalid argument; for example, \
dismounting a non-mounted file system, mentioning an unknown signal in \
sigvec() or kill(), reading or writing a file for which lseek() has \
generated a negative pointer, or some other argument inappropriate for the \
call. Also set by math functions, see 'man 3 intro'."
	},
	{  E2BIG,				"E2BIG",
		"Arg list too long",
		"An argument list longer than the maximum number of bytes was presented \
to execve() or a routine that called execve()."
	},
	{  ENOEXEC,				"ENOEXEC",
		"Exec format error",
		"A request is made to execute a file which, although it has the \
appropriate permissions, does not start with a valid magic number \
(see 'man 5 a.out')."
	},
	{	EXDEV,				"EXDEV",
		"Cross-device link",
		"A hard link to a file on another file system was attempted."
	},
	{	ENFILE,				"ENFILE",
		"File table overflow",
		"The system's table of open files is full, and temporarily no more \
open() calls can be accepted."
	},
	{	ECHILD,				"ECHILD",
		"No children",
		"A wait() was executed by a process that had no existing or \
unwaited-for child processes."
	},
	{	ENOTTY,				"ENOTTY",
		"Inappropriate ioctl for device",
		"The code used in an ioctl() call is not supported by the object that \
the file descriptor in the call refers to."
	},
	{	ETXTBSY,				"ETXTBSY",
		"Text file busy",
		"An attempt was made to execute a pure-procedure program that is \
currently open for writing, or an attempt was made to open for writing a \
pure-procedure program that is being executed."
	},
	{	EFBIG,				"EFBIG",
		"File too large",
		"The size of a file exceeded the maximum file size (1,082,201,088 \
bytes)."
	},
	{	ENOSPC,				"ENOSPC",
		"No space left on device",
		"A write() to an ordinary file, the creation of a directory or \
symbolic link, or the creation of a directory entry failed because no more \
disk blocks are available on the file system, or the allocation of an inode \
for a newly created file failed because no more inodes are available on the \
file system."
	},
	{	ESPIPE,				"ESPIPE",
		"Illegal seek",
		"An lseek() was issued to a socket or pipe. This error may also be \
issued for other non-seekable devices."
	},
	{	EROFS,				"EROFS",
		"Read-only file system",
		"An attempt to modify a file or directory was made on a file system \
mounted read-only."
	},
	{	EMLINK,				"EMLINK",
		"Too many links",
		"An attempt was made to make more than 32767 hard links to a file."
	},
	{	EPIPE,				"EPIPE",
		"Broken pipe",
		"An attempt was made to write on a pipe or socket for which there is \
no process to read the data. This condition normally generates a signal; the \
error is returned if the signal is caught or ignored."
	},
	{	EDOM,					"EDOM",
		"Argument too large",
		"The argument of a function in the math library (as described in \
section 3M) is out of the domain of the function."
	},
	{	ERANGE,				"ERANGE",
		"Result too large",
		"The value of a function in the math library (as described in section \
3M) is unrepresentable within machine precision."
	},
	{	EEXIST,				"EEXIST",
		"File exists",
		"An existing file was mentioned in an inappropriate context, for \
example, link()."
	},
	{	EDEADLOCK,			"EDEADLOCK",
		"Deadlock situation detected/avoided",
		"An attempt was made to lock a system resource that would have \
resulted in a deadlock situation."
	},
	{  EPERM,				"EPERM",
		"Not owner",
		"Typically this error indicates an attempt to modify a file in some \
way forbidden except to its owner or super-user. It is also returned for \
attempts by ordinary users to do things allowed only to the super-user."
	},
	{  ESRCH,				"ESRCH",
		"No such process",
		"The process or process group whose number was given does not exist, \
or any such process is already dead."
	},
	{  EINTR,				"EINTR",
		"Interrupted system call",
		"An asynchronous signal (such as interrupt or quit) that the process \
has elected to catch occurred during a system call. If execution is resumed \
after processing the signal, and the system call is not restarted, it will \
appear as if the interrupted system call returned this error condition."
	},
	{  EIO,					"EIO",
		"I/O error",
		"Some physical I/O error occurred. This error may in some cases occur \
on a call following the one to which it actually applies."
	},
	{  ENXIO,				"ENXIO",
		"No such device or address",
		"I/O on a special file refers to a subdevice that does not exist, or \
beyond the limits of the device. It may also occur when, for example, a tape \
drive is not on-line or no disk pack is loaded on a drive."
	},
	{	EAGAIN,				"EAGAIN",
		"No more processes",
		"A fork() failed because the system's process table is full or the \
user is not allowed to create any more processes, or a system call failed \
because of insufficient resources."
	},
	{	ENOTBLK,				"ENOTBLK",
		"Block device required",
		"A file that is not a block device was mentioned where a block device \
was required, for example, in mount()."
	},
	{	EBUSY,				"EBUSY",
		"Device busy",
		"An attempt was made to mount a file system that was already mounted \
or an attempt was made to dismount a file system on which there is an \
active file (open file, mapped file, current directory, or mounted-on \
directory)."
	},
	{	ENOTDIR,				"ENOTDIR",
		"Not a directory",
		"A non-directory was specified where a directory is required, for \
example, in a path prefix or as an argument to chdir()."
	},
	{	EISDIR,				"EISDIR",
		"Is a directory",
		"An attempt was made to write on a directory."
	},
	{	EUCLEAN,				"EUCLEAN",
		"*** UNKNOWN ***",
		"Unknown error."
	}
};
	/* ********** End of '#ifdef __MSDOS__' ********** */
#elif __SVR4
static const GEN_ERROR_SPEC GEN_ErrorList[] = {
	{  0,						"00000",
		"Error 0 / No error detected",
		"No error encountered."
	},
	{
		EPERM,	"EPERM",
		"Not super-user",
		"Typically this error indicates an attempt to modify a file in some \
way forbidden except to its owner or the super-user. It is also returned for \
attempts by ordinary users to do things allowed only to the super-user."
	},
	{
		ENOENT,	"ENOENT",
		"No such file or directory",
		"A file name is specified and the file should exist but doesn't, or \
one of the directories in a path name does not exist."
	},
	{
		ESRCH,	"ESRCH",
		"No such process, LWP, or thread",
		"No process can be found in the system that corresponds to the \
specified PID, LWPID_t, or thread_t."
	},
	{
		EINTR,	"EINTR",
		"Interrupted system call",
		"An asynchronous signal (such as interrupt or quit), which the user \
has elected to catch, occurred during a system service routine. If execution \
is resumed after processing the signal, it will appear as if the interrupted \
routine call returned this error condition."
	},
	{
		EIO,	"EIO",
		"I/O error",
		"Some physical I/O error has occurred. This error may in some cases \
occur on a call following the one to which it actually applies."
	},
	{
		ENXIO,	"ENXIO",
		"No such device or address",
		"I/O on a special file refers to a subdevice which does not exist, or \
exists beyond the limit of the device. It may also occur when, for example, \
a tape drive is not on-line or no disk pack is loaded on a drive."
	},
	{
		E2BIG,	"E2BIG",
		"Arg list too long",
		"An argument list longer than ARG_MAX bytes is presented to a member \
of the exec family of routines. The argument list limit is the sum of the \
size of the argument list plus the size of the environment's exported shell \
variables."
	},
	{
		ENOEXEC,	"ENOEXEC",
		"Exec format error",
		"A request is made to execute a file which, although it has the \
appropriate permissions, does not start with a valid format (see a.out(4))."
	},
	{
		EBADF,	"EBADF",
		"Bad file number",
		"Either a file descriptor refers to no open file, or a read \
(respectively, write) request is made to a file that is open only for \
writing (respectively, reading)."
	},
	{
		ECHILD,	"ECHILD",
		"No child processes",
		"A wait routine was executed by a process that had no existing or \
unwaited-for child processes."
	},
	{
		EAGAIN,	"EAGAIN",
		"No more processes, or no more LWPs",
		"For example, the fork routine failed because the system's process \
table is full or the user is not allowed to create any more processes, or a \
system call failed because of insufficient memory or swap space."
	},
	{
		ENOMEM,	"ENOMEM",
		"Not enough space",
		"During execution of an exec, brk, or sbrk routine, a program asks for \
more space than the system is able to supply. This is not a temporary \
condition; the maximum size is a system parameter. On some architectures, \
the error may also occur if the arrangement of text, data, and stack \
segments requires too many segmentation registers, or if there is not enough \
swap space during the fork routine. If this error occurs on a resource \
associated with Remote File Sharing (RFS), it indicates a memory depletion \
which may be temporary, dependent on system activity at the time the call \
was invoked."
	},
	{
		EACCES,	"EACCES",
		"Permission denied",
		"An attempt was made to access a file in a way forbidden by the \
protection system."
	},
	{
		EFAULT,	"EFAULT",
		"Bad address",
		"The system encountered a hardware fault in attempting to use an \
argument of a routine. For example, errno potentially may be set to EFAULT \
any time a routine that takes a pointer argument is passed an invalid \
address, if the system can detect the condition. Because systems will differ \
in their ability to reliably detect a bad address, on some implementations \
passing a bad address to a routine will result in undefined behavior."
	},
	{
		ENOTBLK,	"ENOTBLK",
		"Block device required",
		"A non-block device or file was mentioned where a block device was \
required (for example, in a call to the mount routine)."
	},
	{
		EBUSY,	"EBUSY",
		"Device busy",
		"An attempt was made to mount a device that was already mounted or an \
attempt was made to unmount a device on which there is an active file \
(open file, current directory, mounted-on file, active text segment). It \
will also occur if an attempt is made to enable accounting when it is \
already enabled. The device or resource is currently unavailable. EBUSY is \
also used by mutexs, semaphores, condition variables, and r/w locks, to \
indicate that a lock is held. And, EBUSY is also used by the processor \
control function P_ONLINE."
	},
	{
		EEXIST,	"EEXIST",
		"File exists",
		"An existing file was mentioned in an inappropriate context (for \
example, call to the link routine)."
	},
	{
		EXDEV,	"EXDEV",
		"Cross-device link",
		"A hard link to a file on another device was attempted."
	},
	{
		ENODEV,	"ENODEV",
		"No such device",
		"An attempt was made to apply an inappropriate operation to a device \
(for example, read a write-only device)."
	},
	{
		ENOTDIR,	"ENOTDIR",
		"Not a directory",
		"A non-directory was specified where a directory is required (for \
example, in a path prefix or as an argument to the chdir routine)."
	},
	{
		EISDIR,	"EISDIR",
		"Is a directory",
		"An attempt was made to write on a directory."
	},
	{
		EINVAL,	"EINVAL",
		"Invalid argument",
		"An invalid argument was specified (for example, unmounting a \
non-mounted device), mentioning an undefined signal in a call to the signal \
or kill routine."
	},
	{
		ENFILE,	"ENFILE",
		"File table overflow",
		"The system file table is full (that is, SYS_OPEN files are open, and \
temporarily no more files can be opened)."
	},
	{
		EMFILE,	"EMFILE",
		"Too many open files",
		"No process may have more than OPEN_MAX file descriptors open at a \
time."
	},
	{
		ENOTTY,	"ENOTTY",
		"Inappropriate ioctl for device",
		"A call was made to the ioctl routine specifying a file that is not a \
special character device."
	},
	{
		ETXTBSY,	"ETXTBSY",
		"Text file busy (obsolete)",
		"An attempt was made to execute a pure-procedure program that is \
currently open for writing. Also an attempt to open for writing or to remove \
a pure-procedure program that is being executed. (This message is obsolete.)"
	},
	{
		EFBIG,	"EFBIG",
		"File too large",
		"The size of the file exceeded the limit specified by resource \
RLIMIT_FSIZE; or, the file size exceeds the maximum supported by the file \
system."
	},
	{
		ENOSPC,	"ENOSPC",
		"No space left on device",
		"While writing an ordinary file or creating a directory entry, there \
is no free space left on the device. In the fcntl routine, the setting or \
removing of record locks on a file cannot be accomplished because there are \
no more record entries left on the system."
	},
	{
		ESPIPE,	"ESPIPE",
		"Illegal seek",
		"A call to the lseek routine was issued to a pipe."
	},
	{
		EROFS,	"EROFS",
		"Read-only file system",
		"An attempt to modify a file or directory was made on a device mounted \
read-only."
	},
	{
		EMLINK,	"EMLINK",
		"Too many links",
		"An attempt to make more than the maximum number of links, LINK_MAX, \
to a file."
	},
	{
		EPIPE,	"EPIPE",
		"Broken pipe",
		"A write on a pipe for which there is no process to read the data. \
This condition normally generates a signal; the error is returned if the \
signal is ignored."
	},
	{
		EDOM,	"EDOM",
		"Math argument out of domain of func",
		"The argument of a function in the math package (3M) is out of the \
domain of the function."
	},
	{
		ERANGE,	"ERANGE",
		"Math result not representable",
		"The value of a function in the math package (3M) is not representable \
within machine precision."
	},
	{
		ENOMSG,	"ENOMSG",
		"No message of desired type",
		"An attempt was made to receive a message of a type that does not \
exist on the specified message queue (see msgop(2))."
	},
	{
		EIDRM,	"EIDRM",
		"Identifier removed",
		"This error is returned to processes that resume execution due to the \
removal of an identifier from the file system's name space (see msgctl(2), \
semctl(2), and shmctl(2))."
	},
	{
		ECHRNG,	"ECHRNG",
		"Channel number out of range",
		"Channel number out of range."
	},
	{
		EL2NSYNC,	"EL2NSYNC",
		"Level 2 not synchronized",
		"Level 2 not synchronized."
	},
	{
		EL3HLT,	"EL3HLT",
		"Level 3 halted",
		"Level 3 halted."
	},
	{
		EL3RST,	"EL3RST",
		"Level 3 reset",
		"Level 3 reset."
	},
	{
		ELNRNG,	"ELNRNG",
		"Link number out of range",
		"Link number out of range."
	},
	{
		EUNATCH,	"EUNATCH",
		"Protocol driver not attached",
		"Protocol driver not attached."
	},
	{
		ENOCSI,	"ENOCSI",
		"No CSI structure available",
		"No CSI structure available."
	},
	{
		EL2HLT,	"EL2HLT",
		"Level 2 halted",
		"Level 2 halted."
	},
	{
		EDEADLK,	"EDEADLK",
		"Deadlock condition",
		"A deadlock situation was detected and avoided. This error pertains to \
file and record locking, and also applies to mutexs, semaphores, condition \
variables, and r/w locks."
	},
	{
		ENOLCK,	"ENOLCK",
		"No record locks available",
		"There are no more locks available. The system lock table is full (see \
fcntl(2))."
	},
	{
		ECANCELED,	"ECANCELED",
		"Operation canceled",
		"The associated asynchronous operation was canceled before completion."
	},
	{
		ENOTSUP,	"ENOTSUP",
		"Not supported",
		"This version of the system does not support this feature. Future \
versions of the system may provide support."
	},
	{
		49,	"Error 49",
		"Reserved",
		"Reserved."
	},
	{
		58,	"Error 58",
		"Reserved",
		"Reserved."
	},
	{
		59,	"Error 59",
		"Reserved",
		"Reserved."
	},
	{
		ENOSTR,	"ENOSTR",
		"Device not a stream",
		"A putmsg or getmsg system call was attempted on a file descriptor \
that is not a STREAMS device."
	},
	{
		ENODATA,	"ENODATA",
		"No data available",
		"No data available."
	},
	{
		ETIME,	"ETIME",
		"Timer expired",
		"The timer set for a STREAMS ioctl call has expired. The cause of this \
error is device specific and could indicate either a hardware or software \
failure, or perhaps a timeout value that is too short for the specific \
operation. The status of the ioctl operation is indeterminate. This is also \
returned in the case of _lwp_cond_timedwait() or cond_timedwait()."
	},
	{
		ENOSR,	"ENOSR",
		"Out of stream resources",
		"During a STREAMS open, either no STREAMS queues or no STREAMS head \
data structures were available. This is a temporary condition; one may \
recover from it if other processes release resources."
	},
	{
		ENONET,	"ENONET",
		"Machine is not on the network",
		"This error is Remote File Sharing (RFS) specific. It occurs when \
users try to advertise, unadvertise, mount, or unmount remote resources \
while the machine has not done the proper startup to connect to the network."
	},
	{
		ENOPKG,	"ENOPKG",
		"Package not installed",
		"This error occurs when users attempt to use a system call from a \
package which has not been installed."
	},
	{
		EREMOTE,	"EREMOTE",
		"Object is remote",
		"This error is RFS specific. It occurs when users try to advertise a \
resource which is not on the local machine, or try to mount/unmount a device \
(or pathname) that is on a remote machine."
	},
	{
		ENOLINK,	"ENOLINK",
		"Link has been severed",
		"This error is RFS specific. It occurs when the link (virtual circuit) \
connecting to a remote machine is gone."
	},
	{
		EADV,	"EADV",
		"Advertise error",
		"This error is RFS specific. It occurs when users try to advertise a \
resource which has been advertised already, or try to stop RFS while there \
are resources still advertised, or try to force unmount a resource when it \
is still advertised."
	},
	{
		ESRMNT,	"ESRMNT",
		"Srmount error",
		"This error is RFS specific. It occurs when an attempt is made to stop \
RFS while resources are still mounted by remote machines, or when a resource \
is readvertised with a client list that does not include a remote machine \
that currently has the resource mounted."
	},
	{
		ECOMM,	"ECOMM",
		"Communication error on send",
		"This error is RFS specific. It occurs when the current process is \
waiting for a message from a remote machine, and the virtual circuit fails."
	},
	{
		EPROTO,	"EPROTO",
		"Protocol error",
		"Some protocol error occurred. This error is device specific, but is \
generally not related to a hardware failure."
	},
	{
		EMULTIHOP,	"EMULTIHOP",
		"Multihop attempted",
		"This error is RFS specific. It occurs when users try to access remote \
resources which are not directly accessible."
	},
# ifdef EDOTDOT
	/*	***** Unable to locate manifest constant 'EDOTDOT' Solaris 2.4 ***** */
	{
		EDOTDOT,	"EDOTDOT",
		"Error 76",
		"This error is RFS specific. A way for the server to tell the client \
that a process has transferred back from mount point."
	},
#endif /* # ifdef EDOTDOT */
	{
		EBADMSG,	"EBADMSG",
		"Not a data message",
		"During a read, getmsg, or ioctl I_RECVFD system call to a STREAMS \
device, something has come to the head of the queue that can't be processed. \
That something depends on the system call --- read: control information or \
passed file descriptor --- getmsg: passed file descriptor --- ioctl: control \
or data information."
	},
	{
		ENAMETOOLONG,	"ENAMETOOLONG",
		"File name too long",
		"The length of the path argument exceeds PATH_MAX, or the length of a \
path component exceeds NAME_MAX while _POSIX_NO_TRUNC is in effect; see \
limits(4)."
	},
	{
		EOVERFLOW,	"EOVERFLOW",
		"Value too large for defined data type",
		"Value too large for defined data type."
	},
	{
		ENOTUNIQ,	"ENOTUNIQ",
		"Name not unique on network",
		"Given log name not unique."
	},
	{
		EBADFD,	"EBADFD",
		"File descriptor in bad state",
		"Either a file descriptor refers to no open file or a read request was \
made to a file that is open only for writing."
	},
	{
		EREMCHG,	"EREMCHG",
		"Remote address changed",
		"Remote address changed."
	},
	{
		ELIBACC,	"ELIBACC",
		"Cannot access a needed shared library",
		"Trying to exec an a.out that requires a static shared library and the \
static shared library doesn't exist or the user doesn't have permission to \
use it."
	},
	{
		ELIBBAD,	"ELIBBAD",
		"Accessing a corrupted shared library",
		"Trying to exec an a.out that requires a static shared library (to be \
linked in) and exec could not load the static shared library. The static \
shared library is probably corrupted."
	},
	{
		ELIBSCN,	"ELIBSCN",
		"lib section in a.out corrupted",
		"Trying to exec an a.out that requires a static shared library (to be \
linked in) and there was erroneous data in the .lib section of the a.out. \
The .lib section tells exec what static shared libraries are needed. The \
a.out is probably corrupted."
	},
	{
		ELIBMAX,	"ELIBMAX",
		"Attempting to link in more shared libraries than system limit",
		"Trying to exec an a.out that requires more static shared libraries \
than is allowed on the current configuration of the system. See NFS \
Administration Guide."
	},
	{
		ELIBEXEC,	"ELIBEXEC",
		"Cannot exec a shared library directly",
		"Attempting to exec a shared library directly."
	},
	{
		EILSEQ,	"EILSEQ",
		"Wide character encoding error",
		"Illegal byte sequence. Cannot handle multiple characters as a single \
character."
	},
	{
		ENOSYS,	"ENOSYS",
		"Operation not applicable",
		"Operation not applicable."
	},
	{
		ELOOP,	"ELOOP",
		"Too many levels of symbolic links",
		"Number of symbolic links encountered during path name traversal \
exceeds MAXSYMLINKS"
	},
# ifdef ESTART
	/*	***** Unable to locate manifest constant 'ESTART' Solaris 2.4 ******	*/
	{
		ESTART,	"ESTART",
		"Restartable system call",
		"Interrupted system call should be restarted."
	},
#endif /* # ifdef ESTART */
	{
		ESTRPIPE,	"ESTRPIPE",
		"If pipe/FIFO, don't sleep in stream head",
		"Streams pipe error (not externally visible)."
	},
	{
		ENOTEMPTY,	"ENOTEMPTY",
		"Directory not empty",
		"Directory not empty."
	},
	{
		EUSERS,	"EUSERS",
		"Too many users",
		"Too many users."
	},
	{
		ENOTSOCK,	"ENOTSOCK",
		"Socket operation on non-socket",
		"Socket operation on non-socket."
	},
	{
		EDESTADDRREQ,	"EDESTADDRREQ",
		"Destination address required",
		"A required address was omitted from an operation on a transport \
endpoint. Destination address required."
	},
	{
		EMSGSIZE,	"EMSGSIZE",
		"Message too long",
		"A message sent on a transport provider was larger than the internal \
message buffer or some other network limit."
	},
	{
		EPROTOTYPE,	"EPROTOTYPE",
		"Protocol wrong type for socket",
		"A protocol was specified that does not support the semantics of the \
socket type requested."
	},
	{
		ENOPROTOOPT,	"ENOPROTOOPT",
		"Protocol not available",
		"A bad option or level was specified when getting or setting options \
for a protocol."
	},
	{
		EPROTONOSUPPORT,	"EPROTONOSUPPORT",
		"Protocol not supported",
		"The protocol has not been configured into the system or no \
implementation for it exists."
	},
	{
		ESOCKTNOSUPPORT,	"ESOCKTNOSUPPORT",
		"Socket type not supported",
		"The support for the socket type has not been configured into the \
system or no implementation for it exists."
	},
	{
		EOPNOTSUPP,	"EOPNOTSUPP",
		"Operation not supported on transport endpoint",
		"For example, trying to accept a connection on a datagram transport \
endpoint."
	},
	{
		EPFNOSUPPORT,	"EPFNOSUPPORT",
		"Protocol family not supported",
		"The protocol family has not been configured into the system or no \
implementation for it exists. Used for the Internet protocols."
	},
	{
		EAFNOSUPPORT,	"EAFNOSUPPORT",
		"Address family not supported by protocol family",
		"An address incompatible with the requested protocol was used."
	},
	{
		EADDRINUSE,	"EADDRINUSE",
		"Address already in use",
		"User attempted to use an address already in use, and the protocol \
does not allow this."
	},
	{
		EADDRNOTAVAIL,	"EADDRNOTAVAIL",
		"Cannot assign requested address",
		"Results from an attempt to create a transport endpoint with an \
address not on the current machine."
	},
	{
		ENETDOWN,	"ENETDOWN",
		"Network is down",
		"Operation encountered a dead network."
	},
	{
		ENETUNREACH,	"ENETUNREACH",
		"Network is unreachable",
		"Operation was attempted to an unreachable network."
	},
	{
		ENETRESET,	"ENETRESET",
		"Network dropped connection because of reset",
		"The host you were connected to crashed and rebooted."
	},
	{
		ECONNABORTED,	"ECONNABORTED",
		"Software caused connection abort",
		"A connection abort was caused internal to your host machine."
	},
	{
		ECONNRESET,	"ECONNRESET",
		"Connection reset by peer",
		"A connection was forcibly closed by a peer. This normally results \
from a loss of the connection on the remote host due to a timeout or a \
reboot."
	},
	{
		ENOBUFS,	"ENOBUFS",
		"No buffer space available",
		"An operation on a transport endpoint or pipe was not performed \
because the system lacked sufficient buffer space or because a queue was \
full."
	},
	{
		EISCONN,	"EISCONN",
		"Transport endpoint is already connected",
		"A connect request was made on an already connected transport \
endpoint; or, a sendto or sendmsg request on a connected transport endpoint \
specified a destination when already connected."
	},
	{
		ENOTCONN,	"ENOTCONN",
		"Transport endpoint is not connected",
		"A request to send or receive data was disallowed because the \
transport endpoint is not connected and (when sending a datagram) no address \
was supplied."
	},
	{
		ESHUTDOWN,	"ESHUTDOWN",
		"Cannot send after transport endpoint shutdown",
		"A request to send data was disallowed because the transport endpoint \
has already been shut down."
	},
	{
		ETOOMANYREFS,	"ETOOMANYREFS",
		"Too many references: cannot splice",
		"Too many references: cannot splice."
	},
	{
		ETIMEDOUT,	"ETIMEDOUT",
		"Connection timed out",
		"A connect or send request failed because the connected party did not \
properly respond after a period of time. (The timeout period is dependent on \
the communication protocol.)"
	},
	{
		ECONNREFUSED,	"ECONNREFUSED",
		"Connection refused",
		"No connection could be made because the target machine actively \
refused it. This usually results from trying to connect to a service that is \
inactive on the remote host."
	},
	{
		EHOSTDOWN,	"EHOSTDOWN",
		"Host is down",
		"A transport provider operation failed because the destination host \
was down."
	},
	{
		EHOSTUNREACH,	"EHOSTUNREACH",
		"No route to host",
		"A transport provider operation was attempted to an unreachable host."
	},
	{
		EALREADY,	"EALREADY",
		"Operation already in progress",
		"An operation was attempted on a non-blocking object that already had \
an operation in progress."
	},
	{
		EINPROGRESS,	"EINPROGRESS",
		"Operation now in progress",
		"An operation that takes a long time to complete (such as a connect) \
was attempted on a non-blocking object."
	},
	{
		ESTALE,	"ESTALE",
		"Stale NFS file handle",
		"Stale NFS file handle."
	}
};
#elif _MSC_VER
static const GEN_ERROR_SPEC GEN_ErrorList[] = {
/*
	{  EZERO,				"EZERO",
		"Error 0 / No error detected",
		"No error encountered."
	},
	{	EINVFNC,				"EINVFNC",
		"Invalid function number",
		"Invalid function number."
	},
	{	ENOFILE,				"ENOFILE",
		"File not found",
		"File not found."
	},
	{	ENOPATH,				"ENOPATH",
		"Path not found",
		"Path not found."
	},
	{	ECONTR,				"ECONTR",
		"Memory blocks destroyed",
		"Memory blocks destroyed."
	},
	{	EINVMEM,				"EINVMEM",
		"Invalid memory block address",
		"Invalid memory block address."
	},
	{	EINVENV,				"EINVENV",
		"Invalid environment",
		"Invalid environment."
	},
	{	EINVFMT,				"EINVFMT",
		"Invalid format",
		"Invalid format."
	},
	{	EINVACC,				"EINVACC",
		"Invalid access code",
		"Invalid access code."
	},
	{	EINVDAT,				"EINVDAT",
		"Invalid data",
		"Invalid data."
	},
	{	EINVDRV,				"EINVDRV",
		"Invalid drive specified",
		"Invalid drive specified."
	},
	{	ECURDIR,				"ECURDIR",
		"Attempt to remove current directory",
		"Attempt to remove current directory."
	},
	{	ENOTSAM,				"ENOTSAM",
		"Not same device",
		"Not same device."
	},
	{	ENMFILE,				"ENMFILE",
		"No more files",
		"No more files."
	},
*/
	{  ENOENT,				"ENOENT",
		"No such file or directory",
		"This error occurs when a file name is specified and the file should \
exist but does not, or when one of the directories in a path name does not \
exist."
	},
	{	EMFILE,				"EMFILE",
		"Too many open files",
		"A process tried to have more open files than the system allows a \
process to have. The customary configuration limit is 64 per process."
	},
	{	EACCES,				"EACCES",
		"Permission denied",
		"An attempt was made to access a file in a way forbidden by the \
protection system."
	},
	{  EBADF,				"EBADF",
		"Bad file number",
		"Either a file descriptor refers to no open file, or a read \
(respectively, write) request is made to a file that is open only for \
writing (respectively, reading)."
	},
	{	ENOMEM,				"ENOMEM",
		"Not enough memory",
		"During an execve(), sbrk(), or brk(), a program asks for more address \
space or swap space than the system is able to supply, or a process size \
limit would be exceeded. A lack of swap space is normally a temporary \
condition; however, a lack of address space is not a temporary condition. \
The maximum size of the text, data, and stack segments is a system \
parameter.  Soft limits may be increased to their corresponding hard limits."
	},
	{	EFAULT,				"EFAULT",
		"Bad address",
		"The system encountered a hardware fault in attempting to access the \
arguments of a system call."
	},
	{	ENODEV,				"ENODEV",
		"No such device",
		"An attempt was made to apply an inappropriate system call to a device \
(for example, an attempt to read a write-only device) or an attempt was made \
to use a device not configured by the system."
	},
	{	EINVAL,				"EINVAL",
		"Invalid argument",
		"A system call was made with an invalid argument; for example, \
dismounting a non-mounted file system, mentioning an unknown signal in \
sigvec() or kill(), reading or writing a file for which lseek() has \
generated a negative pointer, or some other argument inappropriate for the \
call. Also set by math functions, see 'man 3 intro'."
	},
	{  E2BIG,				"E2BIG",
		"Arg list too long",
		"An argument list longer than the maximum number of bytes was presented \
to execve() or a routine that called execve()."
	},
	{  ENOEXEC,				"ENOEXEC",
		"Exec format error",
		"A request is made to execute a file which, although it has the \
appropriate permissions, does not start with a valid magic number \
(see 'man 5 a.out')."
	},
	{	EXDEV,				"EXDEV",
		"Cross-device link",
		"A hard link to a file on another file system was attempted."
	},
	{	ENFILE,				"ENFILE",
		"File table overflow",
		"The system's table of open files is full, and temporarily no more \
open() calls can be accepted."
	},
	{	ECHILD,				"ECHILD",
		"No children",
		"A wait() was executed by a process that had no existing or \
unwaited-for child processes."
	},
	{	ENOTTY,				"ENOTTY",
		"Inappropriate ioctl for device",
		"The code used in an ioctl() call is not supported by the object that \
the file descriptor in the call refers to."
	},
/*
	{	ETXTBSY,				"ETXTBSY",
		"Text file busy",
		"An attempt was made to execute a pure-procedure program that is \
currently open for writing, or an attempt was made to open for writing a \
pure-procedure program that is being executed."
	},
*/
	{	EFBIG,				"EFBIG",
		"File too large",
		"The size of a file exceeded the maximum file size (1,082,201,088 \
bytes)."
	},
	{	ENOSPC,				"ENOSPC",
		"No space left on device",
		"A write() to an ordinary file, the creation of a directory or \
symbolic link, or the creation of a directory entry failed because no more \
disk blocks are available on the file system, or the allocation of an inode \
for a newly created file failed because no more inodes are available on the \
file system."
	},
	{	ESPIPE,				"ESPIPE",
		"Illegal seek",
		"An lseek() was issued to a socket or pipe. This error may also be \
issued for other non-seekable devices."
	},
	{	EROFS,				"EROFS",
		"Read-only file system",
		"An attempt to modify a file or directory was made on a file system \
mounted read-only."
	},
	{	EMLINK,				"EMLINK",
		"Too many links",
		"An attempt was made to make more than 32767 hard links to a file."
	},
	{	EPIPE,				"EPIPE",
		"Broken pipe",
		"An attempt was made to write on a pipe or socket for which there is \
no process to read the data. This condition normally generates a signal; the \
error is returned if the signal is caught or ignored."
	},
	{	EDOM,					"EDOM",
		"Argument too large",
		"The argument of a function in the math library (as described in \
section 3M) is out of the domain of the function."
	},
	{	ERANGE,				"ERANGE",
		"Result too large",
		"The value of a function in the math library (as described in section \
3M) is unrepresentable within machine precision."
	},
	{	EEXIST,				"EEXIST",
		"File exists",
		"An existing file was mentioned in an inappropriate context, for \
example, link()."
	},
	{	EDEADLOCK,			"EDEADLOCK",
		"Deadlock situation detected/avoided",
		"An attempt was made to lock a system resource that would have \
resulted in a deadlock situation."
	},
	{  EPERM,				"EPERM",
		"Not owner",
		"Typically this error indicates an attempt to modify a file in some \
way forbidden except to its owner or super-user. It is also returned for \
attempts by ordinary users to do things allowed only to the super-user."
	},
	{  ESRCH,				"ESRCH",
		"No such process",
		"The process or process group whose number was given does not exist, \
or any such process is already dead."
	},
	{  EINTR,				"EINTR",
		"Interrupted system call",
		"An asynchronous signal (such as interrupt or quit) that the process \
has elected to catch occurred during a system call. If execution is resumed \
after processing the signal, and the system call is not restarted, it will \
appear as if the interrupted system call returned this error condition."
	},
	{  EIO,					"EIO",
		"I/O error",
		"Some physical I/O error occurred. This error may in some cases occur \
on a call following the one to which it actually applies."
	},
	{  ENXIO,				"ENXIO",
		"No such device or address",
		"I/O on a special file refers to a subdevice that does not exist, or \
beyond the limits of the device. It may also occur when, for example, a tape \
drive is not on-line or no disk pack is loaded on a drive."
	},
	{	EAGAIN,				"EAGAIN",
		"No more processes",
		"A fork() failed because the system's process table is full or the \
user is not allowed to create any more processes, or a system call failed \
because of insufficient resources."
	},
/*
	{	ENOTBLK,				"ENOTBLK",
		"Block device required",
		"A file that is not a block device was mentioned where a block device \
was required, for example, in mount()."
	},
*/
	{	EBUSY,				"EBUSY",
		"Device busy",
		"An attempt was made to mount a file system that was already mounted \
or an attempt was made to dismount a file system on which there is an \
active file (open file, mapped file, current directory, or mounted-on \
directory)."
	},
	{	ENOTDIR,				"ENOTDIR",
		"Not a directory",
		"A non-directory was specified where a directory is required, for \
example, in a path prefix or as an argument to chdir()."
	},
	{	EISDIR,				"EISDIR",
		"Is a directory",
		"An attempt was made to write on a directory."
	}
/*
	,
	{	EUCLEAN,				"EUCLEAN",
		"*** UNKNOWN ***",
		"Unknown error."
	}
*/
};
#elif __MWERKS__
static const GEN_ERROR_SPEC GEN_ErrorList[] = {
	{  ENOERR,				"ENOERR",
		"Error 0 / No error detected",
		"No error detected."
	},
# ifdef EINVFNC
   {	EINVFNC,				"EINVFNC",
		"Invalid function number",
		"Invalid function number."
	},
# endif /* # ifdef EINVFNC */
# ifdef ENOFILE
	{	ENOFILE,				"ENOFILE",
		"File not found",
		"File not found."
	},
# endif /* # ifdef ENOFILE */
# ifdef ENOPATH
	{	ENOPATH,				"ENOPATH",
		"Path not found",
		"Path not found."
	},
# endif /* # ifdef ENOPATH */
# ifdef ECONTR
	{	ECONTR,				"ECONTR",
		"Memory blocks destroyed",
		"Memory blocks destroyed."
	},
# endif /* # ifdef ECONTR */
# ifdef EINVMEM
	{	EINVMEM,				"EINVMEM",
		"Invalid memory block address",
		"Invalid memory block address."
	},
# endif /* # ifdef EINVMEM */
# ifdef EINVENV
	{	EINVENV,				"EINVENV",
		"Invalid environment",
		"Invalid environment."
	},
# endif /* # ifdef EINVENV */
# ifdef EINVFMT
	{	EINVFMT,				"EINVFMT",
		"Invalid format",
		"Invalid format."
	},
# endif /* # ifdef EINVFMT */
# ifdef EINVACC
	{	EINVACC,				"EINVACC",
		"Invalid access code",
		"Invalid access code."
	},
# endif /* # ifdef EINVACC */
# ifdef EINVDAT
	{	EINVDAT,				"EINVDAT",
		"Invalid data",
		"Invalid data."
	},
# endif /* # ifdef EINVDAT */
# ifdef EINVDRV
	{	EINVDRV,				"EINVDRV",
		"Invalid drive specified",
		"Invalid drive specified."
	},
# endif /* # ifdef EINVDRV */
# ifdef ECURDIR
	{	ECURDIR,				"ECURDIR",
		"Attempt to remove current directory",
		"Attempt to remove current directory."
	},
# endif /* # ifdef ECURDIR */
# ifdef ENOTSAM
	{	ENOTSAM,				"ENOTSAM",
		"Not same device",
		"Not same device."
	},
# endif /* # ifdef ENOTSAM */
# ifdef ENMFILE
	{	ENMFILE,				"ENMFILE",
		"No more files",
		"No more files."
	},
# endif /* # ifdef ENMFILE */
	{  ENOENT,				"ENOENT",
		"No such file or directory",
		"This error occurs when a file name is specified and the file should \
exist but does not, or when one of the directories in a path name does not \
exist."
	},
	{	EMFILE,				"EMFILE",
		"Too many open files",
		"A process tried to have more open files than the system allows a \
process to have. The customary configuration limit is 64 per process."
	},
	{	EACCES,				"EACCES",
		"Permission denied",
		"An attempt was made to access a file in a way forbidden by the \
protection system."
	},
	{  EBADF,				"EBADF",
		"Bad file descriptor",
		"Either a file descriptor refers to no open file, or a read \
(respectively, write) request is made to a file that is open only for \
writing (respectively, reading)."
	},
	{	ENOMEM,				"ENOMEM",
		"Not enough memory",
		"During an execve(), sbrk(), or brk(), a program asks for more address \
space or swap space than the system is able to supply, or a process size \
limit would be exceeded. A lack of swap space is normally a temporary \
condition; however, a lack of address space is not a temporary condition. \
The maximum size of the text, data, and stack segments is a system \
parameter.  Soft limits may be increased to their corresponding hard limits."
	},
	{	EFAULT,				"EFAULT",
		"Bad address",
		"The system encountered a hardware fault in attempting to access the \
arguments of a system call."
	},
	{	ENODEV,				"ENODEV",
		"Operation not supported by device / No such device",
		"An attempt was made to apply an inappropriate system call to a device \
(for example, an attempt to read a write-only device) or an attempt was made \
to use a device not configured by the system."
	},
	{	EINVAL,				"EINVAL",
		"Invalid argument",
		"A system call was made with an invalid argument; for example, \
dismounting a non-mounted file system, mentioning an unknown signal in \
sigvec() or kill(), reading or writing a file for which lseek() has \
generated a negative pointer, or some other argument inappropriate for the \
call. Also set by math functions, see 'man 3 intro'."
	},
	{  E2BIG,				"E2BIG",
		"Arg list too long",
		"An argument list longer than the maximum number of bytes was presented \
to execve() or a routine that called execve()."
	},
	{  ENOEXEC,				"ENOEXEC",
		"Exec format error",
		"A request is made to execute a file which, although it has the \
appropriate permissions, does not start with a valid magic number \
(see 'man 5 a.out')."
	},
	{	EXDEV,				"EXDEV",
		"Cross-device link",
		"A hard link to a file on another file system was attempted."
	},
	{	ENFILE,				"ENFILE",
		"Too many open files in system / File table overflow",
		"The system's table of open files is full, and temporarily no more \
open() calls can be accepted."
	},
	{	ECHILD,				"ECHILD",
		"No child processes",
		"A wait() was executed by a process that had no existing or \
unwaited-for child processes."
	},
	{	ENOTTY,				"ENOTTY",
		"Inappropriate ioctl for device",
		"The code used in an ioctl() call is not supported by the object that \
the file descriptor in the call refers to."
	},
# ifdef ETXTBSY
	{	ETXTBSY,				"ETXTBSY",
		"Text file busy",
		"An attempt was made to execute a pure-procedure program that is \
currently open for writing, or an attempt was made to open for writing a \
pure-procedure program that is being executed."
	},
# endif /* # ifdef ETXTBSY */
	{	EFBIG,				"EFBIG",
		"File too large",
		"The size of a file exceeded the maximum file size (1,082,201,088 \
bytes)."
	},
	{	ENOSPC,				"ENOSPC",
		"No space left on device",
		"A write() to an ordinary file, the creation of a directory or \
symbolic link, or the creation of a directory entry failed because no more \
disk blocks are available on the file system, or the allocation of an inode \
for a newly created file failed because no more inodes are available on the \
file system."
	},
	{	ESPIPE,				"ESPIPE",
		"Illegal seek",
		"An lseek() was issued to a socket or pipe. This error may also be \
issued for other non-seekable devices."
	},
	{	EROFS,				"EROFS",
		"Read-only file system",
		"An attempt to modify a file or directory was made on a file system \
mounted read-only."
	},
	{	EMLINK,				"EMLINK",
		"Too many links",
		"An attempt was made to make more than 32767 hard links to a file."
	},
	{	EPIPE,				"EPIPE",
		"Broken pipe",
		"An attempt was made to write on a pipe or socket for which there is \
no process to read the data. This condition normally generates a signal; the \
error is returned if the signal is caught or ignored."
	},
	{	EDOM,					"EDOM",
		"Numerical argument too large",
		"The argument of a function in the math library (as described in \
section 3M) is out of the domain of the function."
	},
	{	ERANGE,				"ERANGE",
		"Result too large",
		"The value of a function in the math library (as described in section \
3M) is unrepresentable within machine precision."
	},
	{	EEXIST,				"EEXIST",
		"File exists",
		"An existing file was mentioned in an inappropriate context, for \
example, link()."
	},
	{	EDEADLOCK,			"EDEADLOCK",
		"Deadlock situation detected/avoided",
		"An attempt was made to lock a system resource that would have \
resulted in a deadlock situation."
	},
	{  EPERM,				"EPERM",
		"Operation not permitted / Not owner",
		"Typically this error indicates an attempt to modify a file in some \
way forbidden except to its owner or super-user. It is also returned for \
attempts by ordinary users to do things allowed only to the super-user."
	},
	{  ESRCH,				"ESRCH",
		"No such process",
		"The process or process group whose number was given does not exist, \
or any such process is already dead."
	},
	{  EINTR,				"EINTR",
		"Interrupted system call",
		"An asynchronous signal (such as interrupt or quit) that the process \
has elected to catch occurred during a system call. If execution is resumed \
after processing the signal, and the system call is not restarted, it will \
appear as if the interrupted system call returned this error condition."
	},
	{  EIO,					"EIO",
		"I/O error",
		"Some physical I/O error occurred. This error may in some cases occur \
on a call following the one to which it actually applies."
	},
	{  ENXIO,				"ENXIO",
		"Device not configured / No such device or address",
		"I/O on a special file refers to a subdevice that does not exist, or \
beyond the limits of the device. It may also occur when, for example, a tape \
drive is not on-line or no disk pack is loaded on a drive."
	},
	{	EAGAIN,				"EAGAIN",
		"Resource temporarily unavailable / No more processes",
		"A fork() failed because the system's process table is full or the \
user is not allowed to create any more processes, or a system call failed \
because of insufficient resources."
	},
# ifdef ENOTBLK
	,{	ENOTBLK,				"ENOTBLK",
		"Block device required",
		"A file that is not a block device was mentioned where a block device \
was required, for example, in mount()."
	}
# endif /* # ifdef ENOTBLK */
	{	EBUSY,				"EBUSY",
		"Device busy",
		"An attempt was made to mount a file system that was already mounted \
or an attempt was made to dismount a file system on which there is an \
active file (open file, mapped file, current directory, or mounted-on \
directory)."
	},
	{	ENOTDIR,				"ENOTDIR",
		"Not a directory",
		"A non-directory was specified where a directory is required, for \
example, in a path prefix or as an argument to chdir()."
	},
	{	EISDIR,				"EISDIR",
		"Is a directory",
		"An attempt was made to write on a directory."
	},
# ifdef EUCLEAN
	,{	EUCLEAN,				"EUCLEAN",
		"*** UNKNOWN ***",
		"Unknown error."
	}
# endif /* # ifdef EUCLEAN */
	{
		EILSEQ,	"EILSEQ",
		"Wide character encoding error",
		"Illegal byte sequence. Cannot handle multiple characters as a single \
character."
	}
# ifdef ENAMETOOLONG
	,{
		ENAMETOOLONG,	"ENAMETOOLONG",
		"File name too long",
		"The length of the path argument exceeds PATH_MAX, or the length of a \
path component exceeds NAME_MAX while _POSIX_NO_TRUNC is in effect; see \
limits(4)."
	}
# endif /* # ifdef ENAMETOOLONG */
# ifdef ENOSYS
	,{
		ENOSYS,	"ENOSYS",
		"Function not implemented / Operation not applicable",
		"Operation not applicable."
	}
# endif /* # ifdef ENOSYS */
# ifdef ENOTEMPTY
	,{
		ENOTEMPTY,	"ENOTEMPTY",
		"Directory not empty",
		"Directory not empty."
	}
# endif /* # ifdef ENOTEMPTY */
# ifdef ENOLCK
	,{
		ENOLCK,	"ENOLCK",
		"No record locks available",
		"There are no more locks available. The system lock table is full (see \
fcntl(2))."
	}
# endif /* # ifdef ENOLCK */
# ifdef EFPOS
	,{	EFPOS,	"EFPOS",
		"File position error",
		"File position error."
	}
# endif /* # ifdef " */
# ifdef EMACOSERR
	,{	EMACOSERR,	"EMACOSERR",
		"Mac OS error",
		"Mac OS error."
	}
# endif /* # ifdef " */
# ifdef ESIGPARM
	,{	ESIGPARM,	"ESIGPARM",
		"Signal error",
		"Signal error."
	}
# endif /* # ifdef " */
# ifdef EUNKNOWN
	,{	EUNKNOWN,	"EUNKNOWN",
		"Unknown error",
		"Unknown error."
	}
# endif /* # ifdef " */
};
#elif _Windows
static const GEN_ERROR_SPEC GEN_ErrorList[] = {
	{  EZERO,				"EZERO",
		"Error 0 / No error detected",
		"No error encountered."
	},
	{	EINVFNC,				"EINVFNC",
		"Invalid function number",
		"Invalid function number."
	},
	{	ENOFILE,				"ENOFILE",
		"File not found",
		"File not found."
	},
	{	ENOPATH,				"ENOPATH",
		"Path not found",
		"Path not found."
	},
	{	ECONTR,				"ECONTR",
		"Memory blocks destroyed",
		"Memory blocks destroyed."
	},
	{	EINVMEM,				"EINVMEM",
		"Invalid memory block address",
		"Invalid memory block address."
	},
	{	EINVENV,				"EINVENV",
		"Invalid environment",
		"Invalid environment."
	},
	{	EINVFMT,				"EINVFMT",
		"Invalid format",
		"Invalid format."
	},
	{	EINVACC,				"EINVACC",
		"Invalid access code",
		"Invalid access code."
	},
	{	EINVDAT,				"EINVDAT",
		"Invalid data",
		"Invalid data."
	},
	{	EINVDRV,				"EINVDRV",
		"Invalid drive specified",
		"Invalid drive specified."
	},
	{	ECURDIR,				"ECURDIR",
		"Attempt to remove current directory",
		"Attempt to remove current directory."
	},
	{	ENOTSAM,				"ENOTSAM",
		"Not same device",
		"Not same device."
	},
	{	ENMFILE,				"ENMFILE",
		"No more files",
		"No more files."
	},
	{  ENOENT,				"ENOENT",
		"No such file or directory",
		"This error occurs when a file name is specified and the file should \
exist but does not, or when one of the directories in a path name does not \
exist."
	},
	{	EMFILE,				"EMFILE",
		"Too many open files",
		"A process tried to have more open files than the system allows a \
process to have. The customary configuration limit is 64 per process."
	},
	{	EACCES,				"EACCES",
		"Permission denied",
		"An attempt was made to access a file in a way forbidden by the \
protection system."
	},
	{  EBADF,				"EBADF",
		"Bad file number",
		"Either a file descriptor refers to no open file, or a read \
(respectively, write) request is made to a file that is open only for \
writing (respectively, reading)."
	},
	{	ENOMEM,				"ENOMEM",
		"Not enough memory",
		"During an execve(), sbrk(), or brk(), a program asks for more address \
space or swap space than the system is able to supply, or a process size \
limit would be exceeded. A lack of swap space is normally a temporary \
condition; however, a lack of address space is not a temporary condition. \
The maximum size of the text, data, and stack segments is a system \
parameter.  Soft limits may be increased to their corresponding hard limits."
	},
	{	EFAULT,				"EFAULT",
		"Bad address",
		"The system encountered a hardware fault in attempting to access the \
arguments of a system call."
	},
	{	ENODEV,				"ENODEV",
		"No such device",
		"An attempt was made to apply an inappropriate system call to a device \
(for example, an attempt to read a write-only device) or an attempt was made \
to use a device not configured by the system."
	},
	{	EINVAL,				"EINVAL",
		"Invalid argument",
		"A system call was made with an invalid argument; for example, \
dismounting a non-mounted file system, mentioning an unknown signal in \
sigvec() or kill(), reading or writing a file for which lseek() has \
generated a negative pointer, or some other argument inappropriate for the \
call. Also set by math functions, see 'man 3 intro'."
	},
	{  E2BIG,				"E2BIG",
		"Arg list too long",
		"An argument list longer than the maximum number of bytes was presented \
to execve() or a routine that called execve()."
	},
	{  ENOEXEC,				"ENOEXEC",
		"Exec format error",
		"A request is made to execute a file which, although it has the \
appropriate permissions, does not start with a valid magic number \
(see 'man 5 a.out')."
	},
	{	EXDEV,				"EXDEV",
		"Cross-device link",
		"A hard link to a file on another file system was attempted."
	},
	{	ENFILE,				"ENFILE",
		"File table overflow",
		"The system's table of open files is full, and temporarily no more \
open() calls can be accepted."
	},
	{	ECHILD,				"ECHILD",
		"No children",
		"A wait() was executed by a process that had no existing or \
unwaited-for child processes."
	},
	{	ENOTTY,				"ENOTTY",
		"Inappropriate ioctl for device",
		"The code used in an ioctl() call is not supported by the object that \
the file descriptor in the call refers to."
	},
	{	ETXTBSY,				"ETXTBSY",
		"Text file busy",
		"An attempt was made to execute a pure-procedure program that is \
currently open for writing, or an attempt was made to open for writing a \
pure-procedure program that is being executed."
	},
	{	EFBIG,				"EFBIG",
		"File too large",
		"The size of a file exceeded the maximum file size (1,082,201,088 \
bytes)."
	},
	{	ENOSPC,				"ENOSPC",
		"No space left on device",
		"A write() to an ordinary file, the creation of a directory or \
symbolic link, or the creation of a directory entry failed because no more \
disk blocks are available on the file system, or the allocation of an inode \
for a newly created file failed because no more inodes are available on the \
file system."
	},
	{	ESPIPE,				"ESPIPE",
		"Illegal seek",
		"An lseek() was issued to a socket or pipe. This error may also be \
issued for other non-seekable devices."
	},
	{	EROFS,				"EROFS",
		"Read-only file system",
		"An attempt to modify a file or directory was made on a file system \
mounted read-only."
	},
	{	EMLINK,				"EMLINK",
		"Too many links",
		"An attempt was made to make more than 32767 hard links to a file."
	},
	{	EPIPE,				"EPIPE",
		"Broken pipe",
		"An attempt was made to write on a pipe or socket for which there is \
no process to read the data. This condition normally generates a signal; the \
error is returned if the signal is caught or ignored."
	},
	{	EDOM,					"EDOM",
		"Argument too large",
		"The argument of a function in the math library (as described in \
section 3M) is out of the domain of the function."
	},
	{	ERANGE,				"ERANGE",
		"Result too large",
		"The value of a function in the math library (as described in section \
3M) is unrepresentable within machine precision."
	},
	{	EEXIST,				"EEXIST",
		"File exists",
		"An existing file was mentioned in an inappropriate context, for \
example, link()."
	},
	{	EDEADLOCK,			"EDEADLOCK",
		"Deadlock situation detected/avoided",
		"An attempt was made to lock a system resource that would have \
resulted in a deadlock situation."
	},
	{  EPERM,				"EPERM",
		"Not owner",
		"Typically this error indicates an attempt to modify a file in some \
way forbidden except to its owner or super-user. It is also returned for \
attempts by ordinary users to do things allowed only to the super-user."
	},
	{  ESRCH,				"ESRCH",
		"No such process",
		"The process or process group whose number was given does not exist, \
or any such process is already dead."
	},
	{  EINTR,				"EINTR",
		"Interrupted system call",
		"An asynchronous signal (such as interrupt or quit) that the process \
has elected to catch occurred during a system call. If execution is resumed \
after processing the signal, and the system call is not restarted, it will \
appear as if the interrupted system call returned this error condition."
	},
	{  EIO,					"EIO",
		"I/O error",
		"Some physical I/O error occurred. This error may in some cases occur \
on a call following the one to which it actually applies."
	},
	{  ENXIO,				"ENXIO",
		"No such device or address",
		"I/O on a special file refers to a subdevice that does not exist, or \
beyond the limits of the device. It may also occur when, for example, a tape \
drive is not on-line or no disk pack is loaded on a drive."
	},
	{	EAGAIN,				"EAGAIN",
		"No more processes",
		"A fork() failed because the system's process table is full or the \
user is not allowed to create any more processes, or a system call failed \
because of insufficient resources."
	},
	{	ENOTBLK,				"ENOTBLK",
		"Block device required",
		"A file that is not a block device was mentioned where a block device \
was required, for example, in mount()."
	},
	{	EBUSY,				"EBUSY",
		"Device busy",
		"An attempt was made to mount a file system that was already mounted \
or an attempt was made to dismount a file system on which there is an \
active file (open file, mapped file, current directory, or mounted-on \
directory)."
	},
	{	ENOTDIR,				"ENOTDIR",
		"Not a directory",
		"A non-directory was specified where a directory is required, for \
example, in a path prefix or as an argument to chdir()."
	},
	{	EISDIR,				"EISDIR",
		"Is a directory",
		"An attempt was made to write on a directory."
	},
	{	EUCLEAN,				"EUCLEAN",
		"*** UNKNOWN ***",
		"Unknown error."
	}
};
#elif __SVR4
static const GEN_ERROR_SPEC GEN_ErrorList[] = {
	{  0,						"00000",
		"Error 0 / No error detected",
		"No error encountered."
	},
	{
		EPERM,	"EPERM",
		"Not super-user",
		"Typically this error indicates an attempt to modify a file in some \
way forbidden except to its owner or the super-user. It is also returned for \
attempts by ordinary users to do things allowed only to the super-user."
	},
	{
		ENOENT,	"ENOENT",
		"No such file or directory",
		"A file name is specified and the file should exist but doesn't, or \
one of the directories in a path name does not exist."
	},
	{
		ESRCH,	"ESRCH",
		"No such process, LWP, or thread",
		"No process can be found in the system that corresponds to the \
specified PID, LWPID_t, or thread_t."
	},
	{
		EINTR,	"EINTR",
		"Interrupted system call",
		"An asynchronous signal (such as interrupt or quit), which the user \
has elected to catch, occurred during a system service routine. If execution \
is resumed after processing the signal, it will appear as if the interrupted \
routine call returned this error condition."
	},
	{
		EIO,	"EIO",
		"I/O error",
		"Some physical I/O error has occurred. This error may in some cases \
occur on a call following the one to which it actually applies."
	},
	{
		ENXIO,	"ENXIO",
		"No such device or address",
		"I/O on a special file refers to a subdevice which does not exist, or \
exists beyond the limit of the device. It may also occur when, for example, \
a tape drive is not on-line or no disk pack is loaded on a drive."
	},
	{
		E2BIG,	"E2BIG",
		"Arg list too long",
		"An argument list longer than ARG_MAX bytes is presented to a member \
of the exec family of routines. The argument list limit is the sum of the \
size of the argument list plus the size of the environment's exported shell \
variables."
	},
	{
		ENOEXEC,	"ENOEXEC",
		"Exec format error",
		"A request is made to execute a file which, although it has the \
appropriate permissions, does not start with a valid format (see a.out(4))."
	},
	{
		EBADF,	"EBADF",
		"Bad file number",
		"Either a file descriptor refers to no open file, or a read \
(respectively, write) request is made to a file that is open only for \
writing (respectively, reading)."
	},
	{
		ECHILD,	"ECHILD",
		"No child processes",
		"A wait routine was executed by a process that had no existing or \
unwaited-for child processes."
	},
	{
		EAGAIN,	"EAGAIN",
		"No more processes, or no more LWPs",
		"For example, the fork routine failed because the system's process \
table is full or the user is not allowed to create any more processes, or a \
system call failed because of insufficient memory or swap space."
	},
	{
		ENOMEM,	"ENOMEM",
		"Not enough space",
		"During execution of an exec, brk, or sbrk routine, a program asks for \
more space than the system is able to supply. This is not a temporary \
condition; the maximum size is a system parameter. On some architectures, \
the error may also occur if the arrangement of text, data, and stack \
segments requires too many segmentation registers, or if there is not enough \
swap space during the fork routine. If this error occurs on a resource \
associated with Remote File Sharing (RFS), it indicates a memory depletion \
which may be temporary, dependent on system activity at the time the call \
was invoked."
	},
	{
		EACCES,	"EACCES",
		"Permission denied",
		"An attempt was made to access a file in a way forbidden by the \
protection system."
	},
	{
		EFAULT,	"EFAULT",
		"Bad address",
		"The system encountered a hardware fault in attempting to use an \
argument of a routine. For example, errno potentially may be set to EFAULT \
any time a routine that takes a pointer argument is passed an invalid \
address, if the system can detect the condition. Because systems will differ \
in their ability to reliably detect a bad address, on some implementations \
passing a bad address to a routine will result in undefined behavior."
	},
	{
		ENOTBLK,	"ENOTBLK",
		"Block device required",
		"A non-block device or file was mentioned where a block device was \
required (for example, in a call to the mount routine)."
	},
	{
		EBUSY,	"EBUSY",
		"Device busy",
		"An attempt was made to mount a device that was already mounted or an \
attempt was made to unmount a device on which there is an active file \
(open file, current directory, mounted-on file, active text segment). It \
will also occur if an attempt is made to enable accounting when it is \
already enabled. The device or resource is currently unavailable. EBUSY is \
also used by mutexs, semaphores, condition variables, and r/w locks, to \
indicate that a lock is held. And, EBUSY is also used by the processor \
control function P_ONLINE."
	},
	{
		EEXIST,	"EEXIST",
		"File exists",
		"An existing file was mentioned in an inappropriate context (for \
example, call to the link routine)."
	},
	{
		EXDEV,	"EXDEV",
		"Cross-device link",
		"A hard link to a file on another device was attempted."
	},
	{
		ENODEV,	"ENODEV",
		"No such device",
		"An attempt was made to apply an inappropriate operation to a device \
(for example, read a write-only device)."
	},
	{
		ENOTDIR,	"ENOTDIR",
		"Not a directory",
		"A non-directory was specified where a directory is required (for \
example, in a path prefix or as an argument to the chdir routine)."
	},
	{
		EISDIR,	"EISDIR",
		"Is a directory",
		"An attempt was made to write on a directory."
	},
	{
		EINVAL,	"EINVAL",
		"Invalid argument",
		"An invalid argument was specified (for example, unmounting a \
non-mounted device), mentioning an undefined signal in a call to the signal \
or kill routine."
	},
	{
		ENFILE,	"ENFILE",
		"File table overflow",
		"The system file table is full (that is, SYS_OPEN files are open, and \
temporarily no more files can be opened)."
	},
	{
		EMFILE,	"EMFILE",
		"Too many open files",
		"No process may have more than OPEN_MAX file descriptors open at a \
time."
	},
	{
		ENOTTY,	"ENOTTY",
		"Inappropriate ioctl for device",
		"A call was made to the ioctl routine specifying a file that is not a \
special character device."
	},
	{
		ETXTBSY,	"ETXTBSY",
		"Text file busy (obsolete)",
		"An attempt was made to execute a pure-procedure program that is \
currently open for writing. Also an attempt to open for writing or to remove \
a pure-procedure program that is being executed. (This message is obsolete.)"
	},
	{
		EFBIG,	"EFBIG",
		"File too large",
		"The size of the file exceeded the limit specified by resource \
RLIMIT_FSIZE; or, the file size exceeds the maximum supported by the file \
system."
	},
	{
		ENOSPC,	"ENOSPC",
		"No space left on device",
		"While writing an ordinary file or creating a directory entry, there \
is no free space left on the device. In the fcntl routine, the setting or \
removing of record locks on a file cannot be accomplished because there are \
no more record entries left on the system."
	},
	{
		ESPIPE,	"ESPIPE",
		"Illegal seek",
		"A call to the lseek routine was issued to a pipe."
	},
	{
		EROFS,	"EROFS",
		"Read-only file system",
		"An attempt to modify a file or directory was made on a device mounted \
read-only."
	},
	{
		EMLINK,	"EMLINK",
		"Too many links",
		"An attempt to make more than the maximum number of links, LINK_MAX, \
to a file."
	},
	{
		EPIPE,	"EPIPE",
		"Broken pipe",
		"A write on a pipe for which there is no process to read the data. \
This condition normally generates a signal; the error is returned if the \
signal is ignored."
	},
	{
		EDOM,	"EDOM",
		"Math argument out of domain of func",
		"The argument of a function in the math package (3M) is out of the \
domain of the function."
	},
	{
		ERANGE,	"ERANGE",
		"Math result not representable",
		"The value of a function in the math package (3M) is not representable \
within machine precision."
	},
	{
		ENOMSG,	"ENOMSG",
		"No message of desired type",
		"An attempt was made to receive a message of a type that does not \
exist on the specified message queue (see msgop(2))."
	},
	{
		EIDRM,	"EIDRM",
		"Identifier removed",
		"This error is returned to processes that resume execution due to the \
removal of an identifier from the file system's name space (see msgctl(2), \
semctl(2), and shmctl(2))."
	},
	{
		ECHRNG,	"ECHRNG",
		"Channel number out of range",
		"Channel number out of range."
	},
	{
		EL2NSYNC,	"EL2NSYNC",
		"Level 2 not synchronized",
		"Level 2 not synchronized."
	},
	{
		EL3HLT,	"EL3HLT",
		"Level 3 halted",
		"Level 3 halted."
	},
	{
		EL3RST,	"EL3RST",
		"Level 3 reset",
		"Level 3 reset."
	},
	{
		ELNRNG,	"ELNRNG",
		"Link number out of range",
		"Link number out of range."
	},
	{
		EUNATCH,	"EUNATCH",
		"Protocol driver not attached",
		"Protocol driver not attached."
	},
	{
		ENOCSI,	"ENOCSI",
		"No CSI structure available",
		"No CSI structure available."
	},
	{
		EL2HLT,	"EL2HLT",
		"Level 2 halted",
		"Level 2 halted."
	},
	{
		EDEADLK,	"EDEADLK",
		"Deadlock condition",
		"A deadlock situation was detected and avoided. This error pertains to \
file and record locking, and also applies to mutexs, semaphores, condition \
variables, and r/w locks."
	},
	{
		ENOLCK,	"ENOLCK",
		"No record locks available",
		"There are no more locks available. The system lock table is full (see \
fcntl(2))."
	},
	{
		ECANCELED,	"ECANCELED",
		"Operation canceled",
		"The associated asynchronous operation was canceled before completion."
	},
	{
		ENOTSUP,	"ENOTSUP",
		"Not supported",
		"This version of the system does not support this feature. Future \
versions of the system may provide support."
	},
	{
		49,	"Error 49",
		"Reserved",
		"Reserved."
	},
	{
		58,	"Error 58",
		"Reserved",
		"Reserved."
	},
	{
		59,	"Error 59",
		"Reserved",
		"Reserved."
	},
	{
		ENOSTR,	"ENOSTR",
		"Device not a stream",
		"A putmsg or getmsg system call was attempted on a file descriptor \
that is not a STREAMS device."
	},
	{
		ENODATA,	"ENODATA",
		"No data available",
		"No data available."
	},
	{
		ETIME,	"ETIME",
		"Timer expired",
		"The timer set for a STREAMS ioctl call has expired. The cause of this \
error is device specific and could indicate either a hardware or software \
failure, or perhaps a timeout value that is too short for the specific \
operation. The status of the ioctl operation is indeterminate. This is also \
returned in the case of _lwp_cond_timedwait() or cond_timedwait()."
	},
	{
		ENOSR,	"ENOSR",
		"Out of stream resources",
		"During a STREAMS open, either no STREAMS queues or no STREAMS head \
data structures were available. This is a temporary condition; one may \
recover from it if other processes release resources."
	},
	{
		ENONET,	"ENONET",
		"Machine is not on the network",
		"This error is Remote File Sharing (RFS) specific. It occurs when \
users try to advertise, unadvertise, mount, or unmount remote resources \
while the machine has not done the proper startup to connect to the network."
	},
	{
		ENOPKG,	"ENOPKG",
		"Package not installed",
		"This error occurs when users attempt to use a system call from a \
package which has not been installed."
	},
	{
		EREMOTE,	"EREMOTE",
		"Object is remote",
		"This error is RFS specific. It occurs when users try to advertise a \
resource which is not on the local machine, or try to mount/unmount a device \
(or pathname) that is on a remote machine."
	},
	{
		ENOLINK,	"ENOLINK",
		"Link has been severed",
		"This error is RFS specific. It occurs when the link (virtual circuit) \
connecting to a remote machine is gone."
	},
	{
		EADV,	"EADV",
		"Advertise error",
		"This error is RFS specific. It occurs when users try to advertise a \
resource which has been advertised already, or try to stop RFS while there \
are resources still advertised, or try to force unmount a resource when it \
is still advertised."
	},
	{
		ESRMNT,	"ESRMNT",
		"Srmount error",
		"This error is RFS specific. It occurs when an attempt is made to stop \
RFS while resources are still mounted by remote machines, or when a resource \
is readvertised with a client list that does not include a remote machine \
that currently has the resource mounted."
	},
	{
		ECOMM,	"ECOMM",
		"Communication error on send",
		"This error is RFS specific. It occurs when the current process is \
waiting for a message from a remote machine, and the virtual circuit fails."
	},
	{
		EPROTO,	"EPROTO",
		"Protocol error",
		"Some protocol error occurred. This error is device specific, but is \
generally not related to a hardware failure."
	},
	{
		EMULTIHOP,	"EMULTIHOP",
		"Multihop attempted",
		"This error is RFS specific. It occurs when users try to access remote \
resources which are not directly accessible."
	},
# ifdef EDOTDOT
	/*	***** Unable to locate manifest constant 'EDOTDOT' Solaris 2.4 *****	*/
	{
		EDOTDOT,	"EDOTDOT",
		"Error 76",
		"This error is RFS specific. A way for the server to tell the client \
that a process has transferred back from mount point."
	},
# endif /* # ifdef EDOTDOT */
	{
		EBADMSG,	"EBADMSG",
		"Not a data message",
		"During a read, getmsg, or ioctl I_RECVFD system call to a STREAMS \
device, something has come to the head of the queue that can't be processed. \
That something depends on the system call --- read: control information or \
passed file descriptor --- getmsg: passed file descriptor --- ioctl: control \
or data information."
	},
	{
		ENAMETOOLONG,	"ENAMETOOLONG",
		"File name too long",
		"The length of the path argument exceeds PATH_MAX, or the length of a \
path component exceeds NAME_MAX while _POSIX_NO_TRUNC is in effect; see \
limits(4)."
	},
	{
		EOVERFLOW,	"EOVERFLOW",
		"Value too large for defined data type",
		"Value too large for defined data type."
	},
	{
		ENOTUNIQ,	"ENOTUNIQ",
		"Name not unique on network",
		"Given log name not unique."
	},
	{
		EBADFD,	"EBADFD",
		"File descriptor in bad state",
		"Either a file descriptor refers to no open file or a read request was \
made to a file that is open only for writing."
	},
	{
		EREMCHG,	"EREMCHG",
		"Remote address changed",
		"Remote address changed."
	},
	{
		ELIBACC,	"ELIBACC",
		"Cannot access a needed shared library",
		"Trying to exec an a.out that requires a static shared library and the \
static shared library doesn't exist or the user doesn't have permission to \
use it."
	},
	{
		ELIBBAD,	"ELIBBAD",
		"Accessing a corrupted shared library",
		"Trying to exec an a.out that requires a static shared library (to be \
linked in) and exec could not load the static shared library. The static \
shared library is probably corrupted."
	},
	{
		ELIBSCN,	"ELIBSCN",
		"lib section in a.out corrupted",
		"Trying to exec an a.out that requires a static shared library (to be \
linked in) and there was erroneous data in the .lib section of the a.out. \
The .lib section tells exec what static shared libraries are needed. The \
a.out is probably corrupted."
	},
	{
		ELIBMAX,	"ELIBMAX",
		"Attempting to link in more shared libraries than system limit",
		"Trying to exec an a.out that requires more static shared libraries \
than is allowed on the current configuration of the system. See NFS \
Administration Guide."
	},
	{
		ELIBEXEC,	"ELIBEXEC",
		"Cannot exec a shared library directly",
		"Attempting to exec a shared library directly."
	},
	{
		EILSEQ,	"EILSEQ",
		"Wide character encoding error",
		"Illegal byte sequence. Cannot handle multiple characters as a single \
character."
	},
	{
		ENOSYS,	"ENOSYS",
		"Operation not applicable",
		"Operation not applicable."
	},
	{
		ELOOP,	"ELOOP",
		"Too many levels of symbolic links",
		"Number of symbolic links encountered during path name traversal \
exceeds MAXSYMLINKS"
	},
# ifdef ESTART
	/*	***** Unable to locate manifest constant 'ESTART' Solaris 2.4 ******	*/
	{
		ESTART,	"ESTART",
		"Restartable system call",
		"Interrupted system call should be restarted."
	},
# endif /* # ifdef ESTART */
	{
		ESTRPIPE,	"ESTRPIPE",
		"If pipe/FIFO, don't sleep in stream head",
		"Streams pipe error (not externally visible)."
	},
	{
		ENOTEMPTY,	"ENOTEMPTY",
		"Directory not empty",
		"Directory not empty."
	},
	{
		EUSERS,	"EUSERS",
		"Too many users",
		"Too many users."
	},
	{
		ENOTSOCK,	"ENOTSOCK",
		"Socket operation on non-socket",
		"Socket operation on non-socket."
	},
	{
		EDESTADDRREQ,	"EDESTADDRREQ",
		"Destination address required",
		"A required address was omitted from an operation on a transport \
endpoint. Destination address required."
	},
	{
		EMSGSIZE,	"EMSGSIZE",
		"Message too long",
		"A message sent on a transport provider was larger than the internal \
message buffer or some other network limit."
	},
	{
		EPROTOTYPE,	"EPROTOTYPE",
		"Protocol wrong type for socket",
		"A protocol was specified that does not support the semantics of the \
socket type requested."
	},
	{
		ENOPROTOOPT,	"ENOPROTOOPT",
		"Protocol not available",
		"A bad option or level was specified when getting or setting options \
for a protocol."
	},
	{
		EPROTONOSUPPORT,	"EPROTONOSUPPORT",
		"Protocol not supported",
		"The protocol has not been configured into the system or no \
implementation for it exists."
	},
	{
		ESOCKTNOSUPPORT,	"ESOCKTNOSUPPORT",
		"Socket type not supported",
		"The support for the socket type has not been configured into the \
system or no implementation for it exists."
	},
	{
		EOPNOTSUPP,	"EOPNOTSUPP",
		"Operation not supported on transport endpoint",
		"For example, trying to accept a connection on a datagram transport \
endpoint."
	},
	{
		EPFNOSUPPORT,	"EPFNOSUPPORT",
		"Protocol family not supported",
		"The protocol family has not been configured into the system or no \
implementation for it exists. Used for the Internet protocols."
	},
	{
		EAFNOSUPPORT,	"EAFNOSUPPORT",
		"Address family not supported by protocol family",
		"An address incompatible with the requested protocol was used."
	},
	{
		EADDRINUSE,	"EADDRINUSE",
		"Address already in use",
		"User attempted to use an address already in use, and the protocol \
does not allow this."
	},
	{
		EADDRNOTAVAIL,	"EADDRNOTAVAIL",
		"Cannot assign requested address",
		"Results from an attempt to create a transport endpoint with an \
address not on the current machine."
	},
	{
		ENETDOWN,	"ENETDOWN",
		"Network is down",
		"Operation encountered a dead network."
	},
	{
		ENETUNREACH,	"ENETUNREACH",
		"Network is unreachable",
		"Operation was attempted to an unreachable network."
	},
	{
		ENETRESET,	"ENETRESET",
		"Network dropped connection because of reset",
		"The host you were connected to crashed and rebooted."
	},
	{
		ECONNABORTED,	"ECONNABORTED",
		"Software caused connection abort",
		"A connection abort was caused internal to your host machine."
	},
	{
		ECONNRESET,	"ECONNRESET",
		"Connection reset by peer",
		"A connection was forcibly closed by a peer. This normally results \
from a loss of the connection on the remote host due to a timeout or a \
reboot."
	},
	{
		ENOBUFS,	"ENOBUFS",
		"No buffer space available",
		"An operation on a transport endpoint or pipe was not performed \
because the system lacked sufficient buffer space or because a queue was \
full."
	},
	{
		EISCONN,	"EISCONN",
		"Transport endpoint is already connected",
		"A connect request was made on an already connected transport \
endpoint; or, a sendto or sendmsg request on a connected transport endpoint \
specified a destination when already connected."
	},
	{
		ENOTCONN,	"ENOTCONN",
		"Transport endpoint is not connected",
		"A request to send or receive data was disallowed because the \
transport endpoint is not connected and (when sending a datagram) no address \
was supplied."
	},
	{
		ESHUTDOWN,	"ESHUTDOWN",
		"Cannot send after transport endpoint shutdown",
		"A request to send data was disallowed because the transport endpoint \
has already been shut down."
	},
	{
		ETOOMANYREFS,	"ETOOMANYREFS",
		"Too many references: cannot splice",
		"Too many references: cannot splice."
	},
	{
		ETIMEDOUT,	"ETIMEDOUT",
		"Connection timed out",
		"A connect or send request failed because the connected party did not \
properly respond after a period of time. (The timeout period is dependent on \
the communication protocol.)"
	},
	{
		ECONNREFUSED,	"ECONNREFUSED",
		"Connection refused",
		"No connection could be made because the target machine actively \
refused it. This usually results from trying to connect to a service that is \
inactive on the remote host."
	},
	{
		EHOSTDOWN,	"EHOSTDOWN",
		"Host is down",
		"A transport provider operation failed because the destination host \
was down."
	},
	{
		EHOSTUNREACH,	"EHOSTUNREACH",
		"No route to host",
		"A transport provider operation was attempted to an unreachable host."
	},
	{
		EALREADY,	"EALREADY",
		"Operation already in progress",
		"An operation was attempted on a non-blocking object that already had \
an operation in progress."
	},
	{
		EINPROGRESS,	"EINPROGRESS",
		"Operation now in progress",
		"An operation that takes a long time to complete (such as a connect) \
was attempted on a non-blocking object."
	},
	{
		ESTALE,	"ESTALE",
		"Stale NFS file handle",
		"Stale NFS file handle."
	}
};
	/* ********** End of '#elif __SVR4' ********** */
#else
static const GEN_ERROR_SPEC GEN_ErrorList[] = {
	{  0,						"00000",
		"Error 0 / No error detected",
		"No error encountered."
	},
	{  EPERM,				"EPERM",
		"Not owner",
		"Typically this error indicates an attempt to modify a file in some \
way forbidden except to its owner or super-user. It is also returned for \
attempts by ordinary users to do things allowed only to the super-user."
	},
	{  ENOENT,				"ENOENT",
		"No such file or directory",
		"This error occurs when a file name is specified and the file should \
exist but does not, or when one of the directories in a path name does not \
exist."
	},
	{  ESRCH,				"ESRCH",
		"No such process",
		"The process or process group whose number was given does not exist, \
or any such process is already dead."
	},
	{  EINTR,				"EINTR",
		"Interrupted system call",
		"An asynchronous signal (such as interrupt or quit) that the process \
has elected to catch occurred during a system call. If execution is resumed \
after processing the signal, and the system call is not restarted, it will \
appear as if the interrupted system call returned this error condition."
	},
	{  EIO,					"EIO",
		"I/O error",
		"Some physical I/O error occurred. This error may in some cases occur \
on a call following the one to which it actually applies."
	},
	{  ENXIO,				"ENXIO",
		"No such device or address",
		"I/O on a special file refers to a subdevice that does not exist, or \
beyond the limits of the device. It may also occur when, for example, a tape \
drive is not on-line or no disk pack is loaded on a drive."
	},
	{  E2BIG,				"E2BIG",
		"Arg list too long",
		"An argument list longer than the maximum number of bytes was presented \
to execve() or a routine that called execve()."
	},
	{  ENOEXEC,				"ENOEXEC",
		"Exec format error",
		"A request is made to execute a file which, although it has the \
appropriate permissions, does not start with a valid magic number \
(see 'man 5 a.out')."
	},
	{  EBADF,				"EBADF",
		"Bad file number",
		"Either a file descriptor refers to no open file, or a read \
(respectively, write) request is made to a file that is open only for \
writing (respectively, reading)."
	},
	{	ECHILD,				"ECHILD",
		"No children",
		"A wait() was executed by a process that had no existing or \
unwaited-for child processes."
	},
	{	EAGAIN,				"EAGAIN",
		"No more processes",
		"A fork() failed because the system's process table is full or the \
user is not allowed to create any more processes, or a system call failed \
because of insufficient resources."
	},
	{	ENOMEM,				"ENOMEM",
		"Not enough memory",
		"During an execve(), sbrk(), or brk(), a program asks for more address \
space or swap space than the system is able to supply, or a process size \
limit would be exceeded. A lack of swap space is normally a temporary \
condition; however, a lack of address space is not a temporary condition. \
The maximum size of the text, data, and stack segments is a system \
parameter.  Soft limits may be increased to their corresponding hard limits."
	},
	{	EACCES,				"EACCES",
		"Permission denied",
		"An attempt was made to access a file in a way forbidden by the \
protection system."
	},
	{	EFAULT,				"EFAULT",
		"Bad address",
		"The system encountered a hardware fault in attempting to access the \
arguments of a system call."
	},
	{	ENOTBLK,				"ENOTBLK",
		"Block device required",
		"A file that is not a block device was mentioned where a block device \
was required, for example, in mount()."
	},
	{	EBUSY,				"EBUSY",
		"Device busy",
		"An attempt was made to mount a file system that was already mounted \
or an attempt was made to dismount a file system on which there is an \
active file (open file, mapped file, current directory, or mounted-on \
directory)."
	},
	{	EEXIST,				"EEXIST",
		"File exists",
		"An existing file was mentioned in an inappropriate context, for \
example, link()."
	},
	{	EXDEV,				"EXDEV",
		"Cross-device link",
		"A hard link to a file on another file system was attempted."
	},
	{	ENODEV,				"ENODEV",
		"No such device",
		"An attempt was made to apply an inappropriate system call to a device \
(for example, an attempt to read a write-only device) or an attempt was made \
to use a device not configured by the system."
	},
	{	ENOTDIR,				"ENOTDIR",
		"Not a directory",
		"A non-directory was specified where a directory is required, for \
example, in a path prefix or as an argument to chdir()."
	},
	{	EISDIR,				"EISDIR",
		"Is a directory",
		"An attempt was made to write on a directory."
	},
	{	EINVAL,				"EINVAL",
		"Invalid argument",
		"A system call was made with an invalid argument; for example, \
dismounting a non-mounted file system, mentioning an unknown signal in \
sigvec() or kill(), reading or writing a file for which lseek() has \
generated a negative pointer, or some other argument inappropriate for the \
call. Also set by math functions, see 'man 3 intro'."
	},
	{	ENFILE,				"ENFILE",
		"File table overflow",
		"The system's table of open files is full, and temporarily no more \
open() calls can be accepted."
	},
	{	EMFILE,				"EMFILE",
		"Too many open files",
		"A process tried to have more open files than the system allows a \
process to have. The customary configuration limit is 64 per process."
	},
	{	ENOTTY,				"ENOTTY",
		"Inappropriate ioctl for device",
		"The code used in an ioctl() call is not supported by the object that \
the file descriptor in the call refers to."
	},
	{	ETXTBSY,				"ETXTBSY",
		"Text file busy",
		"An attempt was made to execute a pure-procedure program that is \
currently open for writing, or an attempt was made to open for writing a \
pure-procedure program that is being executed."
	},
	{	EFBIG,				"EFBIG",
		"File too large",
		"The size of a file exceeded the maximum file size (1,082,201,088 \
bytes)."
	},
	{	ENOSPC,				"ENOSPC",
		"No space left on device",
		"A write() to an ordinary file, the creation of a directory or \
symbolic link, or the creation of a directory entry failed because no more \
disk blocks are available on the file system, or the allocation of an inode \
for a newly created file failed because no more inodes are available on the \
file system."
	},
	{	ESPIPE,				"ESPIPE",
		"Illegal seek",
		"An lseek() was issued to a socket or pipe. This error may also be \
issued for other non-seekable devices."
	},
	{	EROFS,				"EROFS",
		"Read-only file system",
		"An attempt to modify a file or directory was made on a file system \
mounted read-only."
	},
	{	EMLINK,				"EMLINK",
		"Too many links",
		"An attempt was made to make more than 32767 hard links to a file."
	},
	{	EPIPE,				"EPIPE",
		"Broken pipe",
		"An attempt was made to write on a pipe or socket for which there is \
no process to read the data. This condition normally generates a signal; the \
error is returned if the signal is caught or ignored."
	},
	{	EDOM,					"EDOM",
		"Argument too large",
		"The argument of a function in the math library (as described in \
section 3M) is out of the domain of the function."
	},
	{	ERANGE,				"ERANGE",
		"Result too large",
		"The value of a function in the math library (as described in section \
3M) is unrepresentable within machine precision."
	},
	{	EWOULDBLOCK,		"EWOULDBLOCK",
		"Operation would block",
		"An operation that would cause a process to block was attempted on an \
object in non-blocking mode (see ioctl())."
	},
	{	EINPROGRESS,		"EINPROGRESS",
		"Operation now in progress",
		"An operation that takes a long time to complete (such as a connect()) \
was attempted on a non-blocking object (see ioctl())."
	},
	{	EALREADY,			"EALREADY",
		"Operation already in progress",
		"An operation was attempted on a non-blocking object that already had \
an operation in progress."
	},
	{	ENOTSOCK,			"ENOTSOCK",
		"Socket operation on non-socket",
		"Self-explanatory."
	},
	{	EDESTADDRREQ,		"EDESTADDRREQ",
		"Destination address required",
		"A required address was omitted from an operation on a socket."
	},
	{	EMSGSIZE,			"EMSGSIZE",
		"Message too long",
		"A message sent on a socket was larger than the internal message \
buffer."
	},
	{	EPROTOTYPE,			"EPROTOTYPE",
		"Protocol wrong type for socket",
		"A protocol was specified that does not support the semantics of the \
socket type requested. For example, you cannot use the ARPA Internet UDP \
protocol with type SOCK_STREAM."
	},
	{	ENOPROTOOPT,		"ENOPROTOOPT",
		"Option not supported by protocol",
		"A bad option was specified in a setsockopt() or getsockopt() call."
	},
	{	EPROTONOSUPPORT,	"EPROTONOSUPPORT",
		"Protocol not supported",
		"The protocol has not been configured into the system or no \
implementation for it exists."
	},
	{	ESOCKTNOSUPPORT,	"ESOCKTNOSUPPORT",
		"Socket type not supported",
		"The support for the socket type has not been configured into the \
system or no implementation for it exists."
	},
	{	EOPNOTSUPP,			"EOPNOTSUPP",
		"Operation not supported on socket",
		"For example, trying to accept a connection on a datagram socket."
	},
	{	EPFNOSUPPORT,		"EPFNOSUPPORT",
		"Protocol family not supported",
		"The protocol family has not been configured into the system or no \
implementation for it exists."
	},
	{	EAFNOSUPPORT,		"EAFNOSUPPORT",
		"Address family not supported by protocol family",
		"An address incompatible with the requested protocol was used. For \
example, you should not necessarily expect to be able to use PUP Internet \
addresses with ARPA Internet protocols."
	},
	{	EADDRINUSE,			"EADDRINUSE",
		"Address already in use",
		"Only one usage of each address is normally permitted."
	},
	{	EADDRNOTAVAIL,		"EADDRNOTAVAIL",
		"Can't assign requested address",
		"Normally results from an attempt to create a socket with an address \
not on this machine."
	},
	{	ENETDOWN,			"ENETDOWN",
		"Network is down",
		"A socket operation encountered a dead network."
	},
	{	ENETUNREACH,		"ENETUNREACH",
		"Network is unreachable",
		"A socket operation was attempted to an unreachable network."
	},
	{	ENETRESET,			"ENETRESET",
		"Network dropped connection on reset",
		"The host you were connected to crashed and rebooted."
	},
	{	ECONNABORTED,		"ECONNABORTED",
		"Software caused connection abort",
		"A connection abort was caused internal to your host machine."
	},
	{	ECONNRESET,			"ECONNRESET",
		"Connection reset by peer",
		"A connection was forcibly closed by a peer. This normally results \
from the peer executing a shutdown() call."
	},
	{	ENOBUFS,				"ENOBUFS",
		"No buffer space available",
		"An operation on a socket or pipe was not performed because the system \
lacked sufficient buffer space."
	},
	{	EISCONN,				"EISCONN",
		"Socket is already connected",
		"A connect() request was made on an already connected socket; or, a \
sendto() or sendmsg() request on a connected socket specified a destination \
other than the connected party."
	},
	{	ENOTCONN,			"ENOTCONN",
		"Socket is not connected",
		"An request to send or receive data was disallowed because the socket \
is not connected."
	},
	{	ESHUTDOWN,			"ESHUTDOWN",
		"Can't send after socket shutdown",
		"A request to send data was disallowed because the socket had already \
been shut down with a previous shutdown call."
	},
	{	ETOOMANYREFS,		"ETOOMANYREFS",
		"Too many references: can't splice",
		""
	},
	{	ETIMEDOUT,			"ETIMEDOUT",
		"Connection timed out",
		"A connect request or an NFS request failed because the party to which \
the request was made did not properly respond after a period of time. The \
timeout period is dependent on the communication protocol"
	},
	{	ECONNREFUSED,		"ECONNNREFUSED",
		"Connection refused",
		"No connection could be made because the target machine actively \
refused it. This usually results from trying to connect to a service that \
is inactive on the foreign host."
	},
	{	ELOOP,				"ELOOP",
		"Too many levels of symbolic links",
		"A path name lookup involved more than 20 symbolic links."
	},
	{	ENAMETOOLONG,		"ENAMETOOLONG",
		"File name too long",
		"A component of a path name exceeded 255 characters, or an entire path \
name exceeded 1024 characters."
	},
	{	EHOSTDOWN,			"EHOSTDOWN",
		"Host is down",
		"A socket operation failed because the destination host was down."
	},
	{	EHOSTUNREACH,		"EHOSTUNREACH",
		"Host is unreachable",
		"A socket operation was attempted to an unreachable host."
	},
	{	ENOTEMPTY,			"ENOTEMPTY",
		"Directory not empty",
		"An attempt was made to remove a directory with entries other than \
'&.' and '&.|.' by performing a rmdir() system call or a rename() system \
call with that directory specified as the target directory."
	},
	{	EPROCLIM,			"EPROCLIM",
		"Too many processes",
		""
	},
	{	EUSERS,				"EUSERS",
		"Too many users",
		"An operation to read disk quota information for the user failed \
because the system quota table was full."
	},
	{	EDQUOT,				"EDQUOT",
		"Disc quota exceeded",
		"A write() to an ordinary file, the creation of a directory or \
symbolic link, or the creation of a directory entry failed because the \
user's quota of disk blocks was exhausted, or the allocation of an inode \
for a newly created file failed because the user's quota of inodes was \
exhausted."
	},
	{	ESTALE,				"ESTALE",
		"Stale NFS file handle",
		"An NFS client referenced a file that it had opened but that had since \
been deleted."
	},
	{	EREMOTE,				"EREMOTE",
		"Too many levels of remote in path",
		"An attempt was made to remotely mount a file system into a path that \
already has a remotely mounted component."
	},
	{	ENOSTR,				"ENOSTR",
		"Not a stream device",
		"A putmsg() or getmsg() system call was attempted on a file descriptor \
that is not a STREAMS device."
	},
	{	ETIME,				"ETIME",
		"Timer expired",
		"The timer set for a STREAMS ioctl() call has expired. The cause of \
this error is device specific and could indicate either a hardware or \
software failure, or perhaps a timeout value that is too short for the \
specific operation. The status of the ioctl() operation is indeterminate."
	},
	{	ENOSR,				"ENOSR",
		"Out of stream resources",
		"During a STREAMS open(), either no STREAMS queues or no STREAMS head \
data structures were available."
	},
	{	ENOMSG,				"ENOMSG",
		"No message of desired type",
		"An attempt was made to receive a message of a type that does not \
exist on the specified message queue; see msgop()."
	},
	{	EBADMSG,				"EBADMSG",
		"Not a data message",
		"During a read(), getmsg(), or ioctl() I_RECVFD system call to a \
STREAMS device, something has come to the head of the queue that cannot be \
processed.  That something depends on the system call: read() control \
information or a passed file descriptor. getmsg() passed file descriptor. \
ioctl() control or data information."
	},
	{	EIDRM,				"EIDRM",
		"Identifier removed",
		"This error is returned to processes that resume execution due to the \
removal of an identifier from the QUERY"
	},
	{	EDEADLK,				"EDEADLK",
		"Deadlock situation detected/avoided",
		"An attempt was made to lock a system resource that would have \
resulted in a deadlock situation."
	},
	{	ENOLCK,				"ENOLCK",
		"No record locks available",
		"A system-imposed limit on the number of simultaneous file and record \
locks was reached and no more were available at that time."
	},
	{	ENONET,				"ENONET",
		"Machine is not on the network",
		"A attempt was made to advertise, unadvertise, mount, or unmount \
remote resources while the machine has not done the proper startup to \
connect to the network.  This error is Remote File Sharing (RFS) specific."
	},
	{	ERREMOTE,			"ERREMOTE",
		"Object is remote",
		"An attempt was made to advertise a resource which is not on the local \
machine, or to mount/unmount a device (or pathname) that is on a remote \
machine. This error is RFS specific."
	},
	{	ENOLINK,				"ENOLINK",
		"Link has been severed",
		"The link (virtual circuit) connecting to a remote machine is gone. \
This error is RFS specific."
	},
	{	EADV,					"EADV",
		"Advertise error ",
		"An attempt was made to advertise a resource which has been advertised \
already, or to stop the RFS while there ENOSYS are resources still \
advertised, or to force unmount a resource when it is still advertised. \
This error is RFS specific."
	},
	{	ESRMNT,				"ESRMNT",
		"Srmount error ",
		"An attempt was made to stop RFS while there are resources still \
mounted by remote machines. This error is RFS specific."
	},
	{	ECOMM,				"ECOMM",
		"Communication error on send",
		"An attempt was made to send messages to a remote machine when no \
virtual circuit could be found. This error is RFS specific."
	},
	{	EPROTO,				"EPROTO",
		"Protocol error",
		"Some protocol error occurred.  This error is device specific, but is \
generally not related to a hardware failure."
	},
	{	EMULTIHOP,			"EMULTIHOP",
		"Multihop attempted",
		"An attempt was made to access remote resources which are not directly \
accessible.  This error is RFS specific."
	},
	{	EDOTDOT,				"EDOTDOT",
		"EDOTDOT Should never occur",
		""
	},
	{	EREMCHG,				"EREMCHG",
		"Remote address changed",
		""
	},
	{	ENOSYS,				"ENOSYS",
		"Function not implemented",
		"An attempt was made to use a function that is not available in this \
implementation."
	}
};
#endif /* #ifdef __MSDOS__ */

static const unsigned int GEN_ErrorCount =
	(sizeof(GEN_ErrorList) / sizeof(GEN_ErrorList[0]));

/* *********************************************************************** */

/*	***********************************************************************	*/
#ifndef NARGS
void GEN_GetErrorList(unsigned int *out_count, const GEN_ERROR_SPEC **out_list)
#else
void GEN_GetErrorList(out_count, out_list)
unsigned int          *out_count;
const GEN_ERROR_SPEC **out_list;
#endif /* #ifndef NARGS */
{
	*out_count = GEN_ErrorCount;
	*out_list  = GEN_ErrorList;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	GEN_GetErrorPtr

	SYNOPSIS		:	return_ptr = GEN_GetErrorPtr(errno_code);

						const GEN_ERROR_SPEC *return_ptr;

						int                   errno_code;

	DESCRIPTION	:	Gets a pointer the ''GEN_ERROR_SPEC'' error description
						structure corresponding to the specified error code.

   PARAMETERS  :  Parameters to this function are as follows:

						(.) ``errno_code`` is the error code for which the function
						is to return a pointer to the corresponding error
						description structure.

   RETURNS     :  Returns from this function are as follow:

						(.) If the error code specified by the ``errno_code``
						parameter is valid, a pointer to the ''GEN_ERROR_SPEC''
						error description structure corresponding to that error
						code is returned.

						(.) Otherwise, a ''NULL'' pointer is returned.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	GEN_GetLastErrorPtr

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2014 Michael L. Brock

	OUTPUT INDEX:	GEN_GetErrorPtr
						Error Description Functions:GEN_GetErrorPtr
						GENFUNCS:Functions:GEN_GetErrorPtr
						GENFUNCS:Error Description Functions:GEN_GetErrorPtr
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_GetErrorPtr

	PUBLISH NAME:	GEN_GetErrorPtr

	ENTRY CLASS	:	Error Description Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
const GEN_ERROR_SPEC *GEN_GetErrorPtr(int errno_code)
#else
const GEN_ERROR_SPEC *GEN_GetErrorPtr(errno_code)
int errno_code;
#endif /* #ifndef NARGS */
{
	unsigned int          count_1;
	const GEN_ERROR_SPEC *spec_ptr = NULL;

	if ((errno_code >= 0) && (errno_code < ((int) GEN_ErrorCount)) &&
		(errno_code == GEN_ErrorList[errno_code].error_code))
		spec_ptr = GEN_ErrorList + errno_code;
	else {
		for (count_1 = 0; count_1 < GEN_ErrorCount; count_1++) {
			if (errno_code == GEN_ErrorList[count_1].error_code) {
				spec_ptr = GEN_ErrorList + count_1;
				break;
         }
		}
	}

	return(spec_ptr);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	GEN_GetLastErrorPtr

	SYNOPSIS		:	return_ptr = GEN_GetLastErrorPtr();

						const GEN_ERROR_SPEC *return_ptr;

	DESCRIPTION	:	Gets a pointer the ''GEN_ERROR_SPEC'' error description
						structure corresponding to the last operating system
						error (as encoded in the global variable ``errno``).

   PARAMETERS  :  Void.

   RETURNS     :  Returns a pointer to the ''GEN_ERROR_SPEC'' error
						description structure corresponding to the current value
						of the global variable ``errno``.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	GEN_GetErrorPtr

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2014 Michael L. Brock

	OUTPUT INDEX:	GEN_GetLastErrorPtr
						Error Description Functions:GEN_GetLastErrorPtr
						GENFUNCS:Functions:GEN_GetLastErrorPtr
						GENFUNCS:Error Description Functions:GEN_GetLastErrorPtr
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_GetLastErrorPtr

	PUBLISH NAME:	GEN_GetLastErrorPtr

	ENTRY CLASS	:	Error Description Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
const GEN_ERROR_SPEC *GEN_GetLastErrorPtr(void)
#else
const GEN_ERROR_SPEC *GEN_GetLastErrorPtr()
#endif /* #ifndef NARGS */
{
	return(GEN_GetErrorPtr(errno));
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	GEN_AppendErrorString

	SYNOPSIS		:	return_ptr = char *GEN_AppendErrorString(errno_code,
							long_flag, max_text, error_text);

						char         *return_ptr;

						int           errno_code;

						int           long_flag;

						unsigned int  max_text;

						char         *error_text;

	DESCRIPTION	:	Appends text descriptive of the error corresponding to the
						specified error code to a string.

   PARAMETERS  :  Parameters to this function are as follows:

						(.) ``errno_code`` is the error code for which the function
						is to append a text description.

						(.) ``long_flag`` indicates to the function whether short
						or long error descriptions are to be used. If ``long_flag``
						is zero then only the short error description will be used.
						If ``long_flag`` is non-zero, then the long error
						description will be appended after the short error
						description.

						(-) Under SunOS 4.1.3 for example, if ``errno_code`` is
						equal to the manifest constant ''ENOENT'' and ``long_flag``
						is ''0'', the function will append the string:

						<|-|> Error code 2 (ENOENT --- No such file or directory)

						(-) If instead ``long_flag`` is non-zero, the function will
						append the string:

						<|-|> Error code 2 (ENOENT --- No such file or directory)
						This error occurs when a file name is specified and the
						file should exist but does not, or when one of the
						directories in a path name does not exist.

						(.) ``max_text`` is the maximum length to which the function
						is to permit the appended string ``error_text`` to grow.

						(.) ``error_text`` is a pointer to a string to which the
						function is to append text descriptive of the error.

   RETURNS     :	The ``error_text`` parameter is returned.

	NOTES			:	If ``errno_code`` is not a valid error code, the function
						will append the error description as follows:

						<|-|> Invalid error code (``error-code-number``)

	CAVEATS		:	

	SEE ALSO		:	GEN_AppendLastErrorString
						GEN_GetErrorString

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2014 Michael L. Brock

	OUTPUT INDEX:	GEN_AppendErrorString
						Error Description Functions:GEN_AppendErrorString
						GENFUNCS:Functions:GEN_AppendErrorString
						GENFUNCS:Error Description Functions:GEN_AppendErrorString
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_AppendErrorString

	PUBLISH NAME:	GEN_AppendErrorString

	ENTRY CLASS	:	Error Description Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *GEN_AppendErrorString(int errno_code, int long_flag,
	unsigned int max_text, char *error_text)
#else
char *GEN_AppendErrorString(errno_code, long_flag, max_text, error_text)
int           errno_code;
int           long_flag;
unsigned int  max_text;
char         *error_text;
#endif /* #ifndef NARGS */
{
	unsigned int error_length;

	if ((error_length = strlen(error_text)) < max_text)
		GEN_GetErrorString(errno_code, long_flag, max_text - error_length,
			error_text + error_length);

	return(error_text);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	GEN_AppendLastErrorString

	SYNOPSIS		:	return_ptr = GEN_AppendLastErrorString(long_flag, max_text,
							error_text);

						char         *return_ptr;

						int           long_flag;

						unsigned int  max_text;

						char         *error_text;

	DESCRIPTION	:	Appends text descriptive of the error corresponding to the
						last operating system error (as encoded in the global
						variable ``errno``).

   PARAMETERS  :  Parameters to this function are as follows:

						(.) ``long_flag`` indicates to the function whether short
						or long error descriptions are to be used. If ``long_flag``
						is zero then only the short error description will be used.
						If ``long_flag`` is non-zero, then the long error
						description will be appended after the short error
						description.

						(-) Under SunOS 4.1.3 for example, if ``errno`` is equal to
						the manifest constant ''ENOENT'' and ``long_flag`` is ''0'',
						the function will append the string:

						<|-|> Error code 2 (ENOENT --- No such file or directory)

						(-) If instead ``long_flag`` is non-zero, the function will
						append the string:

						<|-|> Error code 2 (ENOENT --- No such file or directory)
						This error occurs when a file name is specified and the
						file should exist but does not, or when one of the
						directories in a path name does not exist.

						(.) ``max_text`` is the maximum length to which the function
						is to permit the appended string ``error_text`` to grow.

						(.) ``error_text`` is a pointer to a string to which the
						function is to append text descriptive of the error.

   RETURNS     :	The ``error_text`` parameter is returned.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	GEN_AppendErrorString
						GEN_GetLastErrorString

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2014 Michael L. Brock

	OUTPUT INDEX:	GEN_AppendLastErrorString
						Error Description Functions:GEN_AppendLastErrorString
						GENFUNCS:Functions:GEN_AppendLastErrorString
						GENFUNCS:Error Description Functions:GEN_AppendLastErrorString
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_AppendLastErrorString

	PUBLISH NAME:	GEN_AppendLastErrorString

	ENTRY CLASS	:	Error Description Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *GEN_AppendLastErrorString(int long_flag, unsigned int max_text,
	char *error_text)
#else
char *GEN_AppendLastErrorString(long_flag, max_text, error_text)
int           long_flag;
unsigned int  max_text;
char         *error_text;
#endif /* #ifndef NARGS */
{
	return(GEN_AppendErrorString(errno, long_flag, max_text, error_text));
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	GEN_GetErrorString

	SYNOPSIS		:	return_ptr = GEN_GetErrorString(errno_code, long_flag,
							max_text, error_text);

						char         *return_ptr;

						int           errno_code;

						int           long_flag;

						unsigned int  max_text;

						char         *error_text;

	DESCRIPTION	:	Copies text descriptive of the error corresponding to the
						specified error code to a string.

   PARAMETERS  :  Parameters to this function are as follows:

						(.) ``errno_code`` is the error code for which the function
						is to copy a text description.

						(.) ``long_flag`` indicates to the function whether short
						or long error descriptions are to be used. If ``long_flag``
						is zero then only the short error description will be used.
						If ``long_flag`` is non-zero, then the long error
						description will be copied after the short error
						description.

						(-) Under SunOS 4.1.3 for example, if ``errno_code`` is
						equal to the manifest constant ''ENOENT'' and ``long_flag``
						is ''0'', the function will copy the string:

						<|-|> Error code 2 (ENOENT --- No such file or directory)

						(-) If instead ``long_flag`` is non-zero, the function will
						copy the string:

						<|-|> Error code 2 (ENOENT --- No such file or directory)
						This error occurs when a file name is specified and the
						file should exist but does not, or when one of the
						directories in a path name does not exist.

						(.) ``max_text`` is the maximum length to which the function
						is to permit the copied string ``error_text`` to grow.

						(.) ``error_text`` is a pointer to the string into which the
						function is to copy text descriptive of the error.

   RETURNS     :	The ``error_text`` parameter is returned.

	NOTES			:	If ``errno_code`` is not a valid error code, the function
						will copy the error description as follows:

						<|-|> Invalid error code (``error-code-number``)

	CAVEATS		:	

	SEE ALSO		:	GEN_GetLastErrorString
						GEN_AppendErrorString

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2014 Michael L. Brock

	OUTPUT INDEX:	GEN_GetErrorString
						Error Description Functions:GEN_GetErrorString
						GENFUNCS:Functions:GEN_GetErrorString
						GENFUNCS:Error Description Functions:GEN_GetErrorString
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_GetErrorString

	PUBLISH NAME:	GEN_GetErrorString

	ENTRY CLASS	:	Error Description Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *GEN_GetErrorString(int errno_code, int long_flag, unsigned int max_text,
	char *error_text)
#else
char *GEN_GetErrorString(errno_code, long_flag, max_text, error_text)
int           errno_code;
int           long_flag;
unsigned int  max_text;
char         *error_text;
#endif /* #ifndef NARGS */
{
	
	const GEN_ERROR_SPEC *spec_ptr;
	char                  buffer[4196];
	char                  number_buffer[STR_VAL2STR_MAX_LEN + 2];

	if ((spec_ptr = GEN_GetErrorPtr(errno_code)) != NULL) {
		strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcpy(buffer,
			"Error code "),
			val2str(((unsigned long) errno_code), 0, 10, NULL, number_buffer)),
			" ("), spec_ptr->error_name), " --- "),
			spec_ptr->short_description), ") "),
			(long_flag && *spec_ptr->long_description) ? " " : ""),
			(long_flag && *spec_ptr->long_description) ?
			spec_ptr->long_description : "");
	}
	else
		oneblank(strcat(strcat(strcpy(buffer, "Invalid error code ("),
			val2str(((unsigned long) abs(errno_code)), errno_code, 10, NULL,
			number_buffer)), ")"));

	if ((!max_text) || (max_text >= strlen(buffer)))
		strcpy(error_text, oneblank(buffer));
	else
		nstrcpy(error_text, oneblank(buffer), max_text);

	return(error_text);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	GEN_GetLastErrorString

	SYNOPSIS		:	return_ptr = GEN_GetLastErrorString(long_flag, max_text,
							error_text);

						char         *return_ptr;

						int           long_flag;

						unsigned int  max_text;

						char         *error_text;

	DESCRIPTION	:	Copies text descriptive of the error corresponding to the
						last operating system error (as encoded in the global
						variable ``errno``).

   PARAMETERS  :  Parameters to this function are as follows:

						(.) ``long_flag`` indicates to the function whether short
						or long error descriptions are to be used. If ``long_flag``
						is zero then only the short error description will be used.
						If ``long_flag`` is non-zero, then the long error
						description will be copied after the short error
						description.

						(-) Under SunOS 4.1.3 for example, if ``errno`` is equal to
						the manifest constant ''ENOENT'' and ``long_flag`` is ''0'',
						the function will copy the string:

						<|-|> Error code 2 (ENOENT --- No such file or directory)

						(-) If instead ``long_flag`` is non-zero, the function will
						copy the string:

						<|-|> Error code 2 (ENOENT --- No such file or directory)
						This error occurs when a file name is specified and the
						file should exist but does not, or when one of the
						directories in a path name does not exist.

						(.) ``max_text`` is the maximum length to which the function
						is to permit the copied string ``error_text`` to grow.

						(.) ``error_text`` is a pointer to the string into which the
						function is to copy text descriptive of the error.

   RETURNS     :	The ``error_text`` parameter is returned.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	GEN_GetErrorString
						GEN_AppendLastErrorString

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2014 Michael L. Brock

	OUTPUT INDEX:	GEN_GetLastErrorString
						Error Description Functions:GEN_GetLastErrorString
						GENFUNCS:Functions:GEN_GetLastErrorString
						GENFUNCS:Error Description Functions:GEN_GetLastErrorString
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_GetLastErrorString

	PUBLISH NAME:	GEN_GetLastErrorString

	ENTRY CLASS	:	Error Description Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *GEN_GetLastErrorString(int long_flag, unsigned int max_text,
	char *error_text)
#else
char *GEN_GetLastErrorString(long_flag, max_text, error_text)
int           long_flag;
unsigned int  max_text;
char         *error_text;
#endif /* #ifndef NARGS */
{
	return(GEN_GetErrorString(errno, long_flag, max_text, error_text));
}
/* *********************************************************************** */

#ifdef _Windows
/*	***********************************************************************	*/
static const GEN_ERROR_SPEC GEN_ErrorList_Win32[] = {
	{	ERROR_SUCCESS,			"ERROR_SUCCESS",
		"The operation completed successfully.",	"The operation completed successfully."	},
	{	ERROR_INVALID_FUNCTION,			"ERROR_INVALID_FUNCTION",
		"Incorrect function.",	"Incorrect function."	},
	{	ERROR_FILE_NOT_FOUND,			"ERROR_FILE_NOT_FOUND",
		"The system cannot find the file specified.",	"The system cannot find the file specified."	},
	{	ERROR_PATH_NOT_FOUND,			"ERROR_PATH_NOT_FOUND",
		"The system cannot find the path specified.",	"The system cannot find the path specified."	},
	{	ERROR_TOO_MANY_OPEN_FILES,			"ERROR_TOO_MANY_OPEN_FILES",
		"The system cannot open the file.",	"The system cannot open the file."	},
	{	ERROR_ACCESS_DENIED,			"ERROR_ACCESS_DENIED",
		"Access is denied.",	"Access is denied."	},
	{	ERROR_INVALID_HANDLE,			"ERROR_INVALID_HANDLE",
		"The handle is invalid.",	"The handle is invalid."	},
	{	ERROR_ARENA_TRASHED,			"ERROR_ARENA_TRASHED",
		"The storage control blocks were destroyed.",	"The storage control blocks were destroyed."	},
	{	ERROR_NOT_ENOUGH_MEMORY,			"ERROR_NOT_ENOUGH_MEMORY",
		"Not enough storage is available to process this command.",	"Not enough storage is available to process this command."	},
	{	ERROR_INVALID_BLOCK,			"ERROR_INVALID_BLOCK",
		"The storage control block address is invalid.",	"The storage control block address is invalid."	},
	{	ERROR_BAD_ENVIRONMENT,			"ERROR_BAD_ENVIRONMENT",
		"The environment is incorrect.",	"The environment is incorrect."	},
	{	ERROR_BAD_FORMAT,			"ERROR_BAD_FORMAT",
		"An attempt was made to load a program with an incorrect format.",	"An attempt was made to load a program with an incorrect format."	},
	{	ERROR_INVALID_ACCESS,			"ERROR_INVALID_ACCESS",
		"The access code is invalid.",	"The access code is invalid."	},
	{	ERROR_INVALID_DATA,			"ERROR_INVALID_DATA",
		"The data is invalid.",	"The data is invalid."	},
	{	ERROR_OUTOFMEMORY,			"ERROR_OUTOFMEMORY",
		"Not enough storage is available to complete this operation.",	"Not enough storage is available to complete this operation."	},
	{	ERROR_INVALID_DRIVE,			"ERROR_INVALID_DRIVE",
		"The system cannot find the drive specified.",	"The system cannot find the drive specified."	},
	{	ERROR_CURRENT_DIRECTORY,			"ERROR_CURRENT_DIRECTORY",
		"The directory cannot be removed.",	"The directory cannot be removed."	},
	{	ERROR_NOT_SAME_DEVICE,			"ERROR_NOT_SAME_DEVICE",
		"The system cannot move the file to a different disk drive.",	"The system cannot move the file to a different disk drive."	},
	{	ERROR_NO_MORE_FILES,			"ERROR_NO_MORE_FILES",
		"There are no more files.",	"There are no more files."	},
	{	ERROR_WRITE_PROTECT,			"ERROR_WRITE_PROTECT",
		"The media is write protected.",	"The media is write protected."	},
	{	ERROR_BAD_UNIT,			"ERROR_BAD_UNIT",
		"The system cannot find the device specified.",	"The system cannot find the device specified."	},
	{	ERROR_NOT_READY,			"ERROR_NOT_READY",
		"The device is not ready.",	"The device is not ready."	},
	{	ERROR_BAD_COMMAND,			"ERROR_BAD_COMMAND",
		"The device does not recognize the command.",	"The device does not recognize the command."	},
	{	ERROR_CRC,			"ERROR_CRC",
		"Data error (cyclic redundancy check).",	"Data error (cyclic redundancy check)"	},
	{	ERROR_BAD_LENGTH,			"ERROR_BAD_LENGTH",
		"The program issued a command but the command length is incorrect.",	"The program issued a command but the command length is incorrect."	},
	{	ERROR_SEEK,			"ERROR_SEEK",
		"The drive cannot locate a specific area or track on the disk.",	"The drive cannot locate a specific area or track on the disk."	},
	{	ERROR_NOT_DOS_DISK,			"ERROR_NOT_DOS_DISK",
		"The specified disk or diskette cannot be accessed.",	"The specified disk or diskette cannot be accessed."	},
	{	ERROR_SECTOR_NOT_FOUND,			"ERROR_SECTOR_NOT_FOUND",
		"The drive cannot find the sector requested.",	"The drive cannot find the sector requested."	},
	{	ERROR_OUT_OF_PAPER,			"ERROR_OUT_OF_PAPER",
		"The printer is out of paper.",	"The printer is out of paper."	},
	{	ERROR_WRITE_FAULT,			"ERROR_WRITE_FAULT",
		"The system cannot write to the specified device.",	"The system cannot write to the specified device."	},
	{	ERROR_READ_FAULT,			"ERROR_READ_FAULT",
		"The system cannot read from the specified device.",	"The system cannot read from the specified device."	},
	{	ERROR_GEN_FAILURE,			"ERROR_GEN_FAILURE",
		"A device attached to the system is not functioning.",	"A device attached to the system is not functioning."	},
	{	ERROR_SHARING_VIOLATION,			"ERROR_SHARING_VIOLATION",
		"The process cannot access the file because it is being used by another process.",	"The process cannot access the file because it is being used by another process."	},
	{	ERROR_LOCK_VIOLATION,			"ERROR_LOCK_VIOLATION",
		"The process cannot access the file because another process has locked a portion of the file.",	"The process cannot access the file because another process has locked a portion of the file."	},
	{	ERROR_WRONG_DISK,			"ERROR_WRONG_DISK",
		"The wrong diskette is in the drive.",	"The wrong diskette is in the drive."	},
	{	ERROR_SHARING_BUFFER_EXCEEDED,			"ERROR_SHARING_BUFFER_EXCEEDED",
		"Too many files opened for sharing.",	"Too many files opened for sharing."	},
	{	ERROR_HANDLE_EOF,			"ERROR_HANDLE_EOF",
		"Reached the end of the file.",	"Reached end of file."	},
	{	ERROR_HANDLE_DISK_FULL,			"ERROR_HANDLE_DISK_FULL",
		"The disk is full.",	"The disk is full."	},
	{	ERROR_NOT_SUPPORTED,			"ERROR_NOT_SUPPORTED",
		"The network request is not supported.",	"The network request is not supported."	},
	{	ERROR_REM_NOT_LIST,			"ERROR_REM_NOT_LIST",
		"The remote computer is not available.",	"The remote computer is not available."	},
	{	ERROR_DUP_NAME,			"ERROR_DUP_NAME",
		"A duplicate name exists on the network.",	"A duplicate name exists on the network."	},
	{	ERROR_BAD_NETPATH,			"ERROR_BAD_NETPATH",
		"The network path was not found.",	"The network path was not found."	},
	{	ERROR_NETWORK_BUSY,			"ERROR_NETWORK_BUSY",
		"The network is busy.",	"The network is busy."	},
	{	ERROR_DEV_NOT_EXIST,			"ERROR_DEV_NOT_EXIST",
		"The specified network resource or device is no longer available.",	"The specified network resource or device is no longer available."	},
	{	ERROR_TOO_MANY_CMDS,			"ERROR_TOO_MANY_CMDS",
		"The network BIOS command limit has been reached.",	"The network BIOS command limit has been reached."	},
	{	ERROR_ADAP_HDW_ERR,			"ERROR_ADAP_HDW_ERR",
		"A network adapter hardware error occurred.",	"A network adapter hardware error occurred."	},
	{	ERROR_BAD_NET_RESP,			"ERROR_BAD_NET_RESP",
		"The specified server cannot perform the requested operation.",	"The specified server cannot perform the requested operation."	},
	{	ERROR_UNEXP_NET_ERR,			"ERROR_UNEXP_NET_ERR",
		"An unexpected network error occurred.",	"An unexpected network error occurred."	},
	{	ERROR_BAD_REM_ADAP,			"ERROR_BAD_REM_ADAP",
		"The remote adapter is not compatible.",	"The remote adapter is not compatible."	},
	{	ERROR_PRINTQ_FULL,			"ERROR_PRINTQ_FULL",
		"The printer queue is full.",	"The printer queue is full."	},
	{	ERROR_NO_SPOOL_SPACE,			"ERROR_NO_SPOOL_SPACE",
		"Space to store the file waiting to be printed is not available on the server.",	"Space to store the file waiting to be printed is not available on the server."	},
	{	ERROR_PRINT_CANCELLED,			"ERROR_PRINT_CANCELLED",
		"Your file waiting to be printed was deleted.",	"Your file waiting to be printed was deleted."	},
	{	ERROR_NETNAME_DELETED,			"ERROR_NETNAME_DELETED",
		"The specified network name is no longer available.",	"The specified network name is no longer available."	},
	{	ERROR_NETWORK_ACCESS_DENIED,			"ERROR_NETWORK_ACCESS_DENIED",
		"Network access is denied.",	"Network access is denied."	},
	{	ERROR_BAD_DEV_TYPE,			"ERROR_BAD_DEV_TYPE",
		"The network resource type is not correct.",	"The network resource type is not correct."	},
	{	ERROR_BAD_NET_NAME,			"ERROR_BAD_NET_NAME",
		"The network name cannot be found.",	"The network name cannot be found."	},
	{	ERROR_TOO_MANY_NAMES,			"ERROR_TOO_MANY_NAMES",
		"The name limit for the local computer network adapter card was exceeded.",	"The name limit for the local computer network adapter card was exceeded."	},
	{	ERROR_TOO_MANY_SESS,			"ERROR_TOO_MANY_SESS",
		"The network BIOS session limit was exceeded.",	"The network BIOS session limit was exceeded."	},
	{	ERROR_SHARING_PAUSED,			"ERROR_SHARING_PAUSED",
		"The remote server has been paused or is in the process of being started.",	"The remote server has been paused or is in the process of being started."	},
	{	ERROR_REQ_NOT_ACCEP,			"ERROR_REQ_NOT_ACCEP",
		"No more connections can be made to this remote computer at this time because there are already as many connections as the computer can accept.",	"No more connections can be made to this remote computer at this time because there are already as many connections as the computer can accept."	},
	{	ERROR_REDIR_PAUSED,			"ERROR_REDIR_PAUSED",
		"The specified printer or disk device has been paused.",	"The specified printer or disk device has been paused."	},
	{	ERROR_FILE_EXISTS,			"ERROR_FILE_EXISTS",
		"The file exists.",	"The file exists."	},
	{	ERROR_CANNOT_MAKE,			"ERROR_CANNOT_MAKE",
		"The directory or file cannot be created.",	"The directory or file cannot be created."	},
	{	ERROR_FAIL_I24,			"ERROR_FAIL_I24",
		"Fail on INT 24.",	"Fail on INT 24"	},
	{	ERROR_OUT_OF_STRUCTURES,			"ERROR_OUT_OF_STRUCTURES",
		"Storage to process this request is not available.",	"Storage to process this request is not available."	},
	{	ERROR_ALREADY_ASSIGNED,			"ERROR_ALREADY_ASSIGNED",
		"The local device name is already in use.",	"The local device name is already in use."	},
	{	ERROR_INVALID_PASSWORD,			"ERROR_INVALID_PASSWORD",
		"The specified network password is not correct.",	"The specified network password is not correct."	},
	{	ERROR_INVALID_PARAMETER,			"ERROR_INVALID_PARAMETER",
		"The parameter is incorrect.",	"The parameter is incorrect."	},
	{	ERROR_NET_WRITE_FAULT,			"ERROR_NET_WRITE_FAULT",
		"A write fault occurred on the network.",	"A write fault occurred on the network."	},
	{	ERROR_NO_PROC_SLOTS,			"ERROR_NO_PROC_SLOTS",
		"The system cannot start another process at this time.",	"The system cannot start another process at this time."	},
	{	ERROR_TOO_MANY_SEMAPHORES,			"ERROR_TOO_MANY_SEMAPHORES",
		"Cannot create another system semaphore.",	"Cannot create another system semaphore."	},
	{	ERROR_EXCL_SEM_ALREADY_OWNED,			"ERROR_EXCL_SEM_ALREADY_OWNED",
		"The exclusive semaphore is owned by another process.",	"The exclusive semaphore is owned by another process."	},
	{	ERROR_SEM_IS_SET,			"ERROR_SEM_IS_SET",
		"The semaphore is set and cannot be closed.",	"The semaphore is set and cannot be closed."	},
	{	ERROR_TOO_MANY_SEM_REQUESTS,			"ERROR_TOO_MANY_SEM_REQUESTS",
		"The semaphore cannot be set again.",	"The semaphore cannot be set again."	},
	{	ERROR_INVALID_AT_INTERRUPT_TIME,			"ERROR_INVALID_AT_INTERRUPT_TIME",
		"Cannot request exclusive semaphores at interrupt time.",	"Cannot request exclusive semaphores at interrupt time."	},
	{	ERROR_SEM_OWNER_DIED,			"ERROR_SEM_OWNER_DIED",
		"The previous ownership of this semaphore has ended.",	"The previous ownership of this semaphore has ended."	},
	{	ERROR_SEM_USER_LIMIT,			"ERROR_SEM_USER_LIMIT",
		"Insert the diskette for drive.",	"The diskette must be inserted in the drive."	},
	{	ERROR_DISK_CHANGE,			"ERROR_DISK_CHANGE",
		"The program stopped because an alternate diskette was not inserted.",	"Program stopped because alternate diskette was not inserted."	},
	{	ERROR_DRIVE_LOCKED,			"ERROR_DRIVE_LOCKED",
		"The disk is in use or locked by another process.",	"The disk is in use or locked by another process."	},
	{	ERROR_BROKEN_PIPE,			"ERROR_BROKEN_PIPE",
		"The pipe has been ended.",	"The pipe has been ended."	},
	{	ERROR_OPEN_FAILED,			"ERROR_OPEN_FAILED",
		"The system cannot open the device or file specified.",	"The system cannot open the device or file specified."	},
	{	ERROR_BUFFER_OVERFLOW,			"ERROR_BUFFER_OVERFLOW",
		"The file name is too long.",	"The file name is too long."	},
	{	ERROR_DISK_FULL,			"ERROR_DISK_FULL",
		"There is not enough space on the disk.",	"There is not enough space on the disk."	},
	{	ERROR_NO_MORE_SEARCH_HANDLES,			"ERROR_NO_MORE_SEARCH_HANDLES",
		"No more internal file identifiers available.",	"No more internal file identifiers available."	},
	{	ERROR_INVALID_TARGET_HANDLE,			"ERROR_INVALID_TARGET_HANDLE",
		"The target internal file identifier is incorrect.",	"The target internal file identifier is incorrect."	},
	{	ERROR_INVALID_CATEGORY,			"ERROR_INVALID_CATEGORY",
		"The IOCTL call made by the application program is not correct.",	"The IOCTL call made by the application program is not correct."	},
	{	ERROR_INVALID_VERIFY_SWITCH,			"ERROR_INVALID_VERIFY_SWITCH",
		"The verify-on-write switch parameter value is not correct.",	"The verify-on-write switch parameter value is not correct."	},
	{	ERROR_BAD_DRIVER_LEVEL,			"ERROR_BAD_DRIVER_LEVEL",
		"The system does not support the command requested.",	"The system does not support the command requested."	},
	{	ERROR_CALL_NOT_IMPLEMENTED,			"ERROR_CALL_NOT_IMPLEMENTED",
		"This function is not supported on this system.",	"This function is only valid in Windows NT mode."	},
	{	ERROR_SEM_TIMEOUT,			"ERROR_SEM_TIMEOUT",
		"The semaphore timeout period has expired.",	"The semaphore timeout period has expired."	},
	{	ERROR_INSUFFICIENT_BUFFER,			"ERROR_INSUFFICIENT_BUFFER",
		"The data area passed to a system call is too small.",	"The data area passed to a system call is too small."	},
	{	ERROR_INVALID_NAME,			"ERROR_INVALID_NAME",
		"The filename, directory name, or volume label syntax is incorrect.",	"The filename, directory name, or volume label syntax is incorrect."	},
	{	ERROR_INVALID_LEVEL,			"ERROR_INVALID_LEVEL",
		"The system call level is not correct.",	"The system call level is not correct."	},
	{	ERROR_NO_VOLUME_LABEL,			"ERROR_NO_VOLUME_LABEL",
		"The disk has no volume label.",	"The disk has no volume label."	},
	{	ERROR_MOD_NOT_FOUND,			"ERROR_MOD_NOT_FOUND",
		"The specified module could not be found.",	"The specified module could not be found."	},
	{	ERROR_PROC_NOT_FOUND,			"ERROR_PROC_NOT_FOUND",
		"The specified procedure could not be found.",	"The specified procedure could not be found."	},
	{	ERROR_WAIT_NO_CHILDREN,			"ERROR_WAIT_NO_CHILDREN",
		"There are no child processes to wait for.",	"There are no child processes to wait for."	},
	{	ERROR_CHILD_NOT_COMPLETE,			"ERROR_CHILD_NOT_COMPLETE",
		"The application cannot be run in Win32 mode.",	"The application cannot be run in Win32 mode."	},
	{	ERROR_DIRECT_ACCESS_HANDLE,			"ERROR_DIRECT_ACCESS_HANDLE",
		"Attempt to use a file handle to an open disk partition for an operation other than raw disk I/O.",	"Attempt to use a file handle to an open disk partition for an operation other than raw disk I/O."	},
	{	ERROR_NEGATIVE_SEEK,			"ERROR_NEGATIVE_SEEK",
		"An attempt was made to move the file pointer before the beginning of the file.",	"An attempt was made to move the file pointer before the beginning of the file."	},
	{	ERROR_SEEK_ON_DEVICE,			"ERROR_SEEK_ON_DEVICE",
		"The file pointer cannot be set on the specified device or file.",	"The file pointer cannot be set on the specified device or file."	},
	{	ERROR_IS_JOIN_TARGET,			"ERROR_IS_JOIN_TARGET",
		"A JOIN or SUBST command cannot be used for a drive that contains previously joined drives.",	"A JOIN or SUBST command cannot be used for a drive that contains previously joined drives."	},
	{	ERROR_IS_JOINED,			"ERROR_IS_JOINED",
		"An attempt was made to use a JOIN or SUBST command on a drive that has already been joined.",	"An attempt was made to use a JOIN or SUBST command on a drive that has already been joined."	},
	{	ERROR_IS_SUBSTED,			"ERROR_IS_SUBSTED",
		"An attempt was made to use a JOIN or SUBST command on a drive that has already been substituted.",	"An attempt was made to use a JOIN or SUBST command on a drive that has already been substituted."	},
	{	ERROR_NOT_JOINED,			"ERROR_NOT_JOINED",
		"The system tried to delete the JOIN of a drive that is not joined.",	"The system tried to delete the JOIN of a drive that is not joined."	},
	{	ERROR_NOT_SUBSTED,			"ERROR_NOT_SUBSTED",
		"The system tried to delete the substitution of a drive that is not substituted.",	"The system tried to delete the substitution of a drive that is not substituted."	},
	{	ERROR_JOIN_TO_JOIN,			"ERROR_JOIN_TO_JOIN",
		"The system tried to join a drive to a directory on a joined drive.",	"The system tried to join a drive to a directory on a joined drive."	},
	{	ERROR_SUBST_TO_SUBST,			"ERROR_SUBST_TO_SUBST",
		"The system tried to substitute a drive to a directory on a substituted drive.",	"The system tried to substitute a drive to a directory on a substituted drive."	},
	{	ERROR_JOIN_TO_SUBST,			"ERROR_JOIN_TO_SUBST",
		"The system tried to join a drive to a directory on a substituted drive.",	"The system tried to join a drive to a directory on a substituted drive."	},
	{	ERROR_SUBST_TO_JOIN,			"ERROR_SUBST_TO_JOIN",
		"The system tried to SUBST a drive to a directory on a joined drive.",	"The system tried to SUBST a drive to a directory on a joined drive."	},
	{	ERROR_BUSY_DRIVE,			"ERROR_BUSY_DRIVE",
		"The system cannot perform a JOIN or SUBST at this time.",	"The system cannot perform a JOIN or SUBST at this time."	},
	{	ERROR_SAME_DRIVE,			"ERROR_SAME_DRIVE",
		"The system cannot join or substitute a drive to or for a directory on the same drive.",	"The system cannot join or substitute a drive to or for a directory on the same drive."	},
	{	ERROR_DIR_NOT_ROOT,			"ERROR_DIR_NOT_ROOT",
		"The directory is not a subdirectory of the root directory.",	"The directory is not a subdirectory of the root directory."	},
	{	ERROR_DIR_NOT_EMPTY,			"ERROR_DIR_NOT_EMPTY",
		"The directory is not empty.",	"The directory is not empty."	},
	{	ERROR_IS_SUBST_PATH,			"ERROR_IS_SUBST_PATH",
		"The path specified is being used in a substitute.",	"The path specified is being used in a substitute."	},
	{	ERROR_IS_JOIN_PATH,			"ERROR_IS_JOIN_PATH",
		"Not enough resources are available to process this command.",	"Not enough resources are available to process this command."	},
	{	ERROR_PATH_BUSY,			"ERROR_PATH_BUSY",
		"The path specified cannot be used at this time.",	"The path specified cannot be used at this time."	},
	{	ERROR_IS_SUBST_TARGET,			"ERROR_IS_SUBST_TARGET",
		"An attempt was made to join or substitute a drive for which a directory on the drive is the target of a previous substitute.",	"An attempt was made to join or substitute a drive for which a directory on the drive is the target of a previous substitute."	},
	{	ERROR_SYSTEM_TRACE,			"ERROR_SYSTEM_TRACE",
		"System trace information was not specified in your CONFIG.SYS file, or tracing is disallowed.",	"System trace information was not specified in your CONFIG.SYS file, or tracing is disallowed."	},
	{	ERROR_INVALID_EVENT_COUNT,			"ERROR_INVALID_EVENT_COUNT",
		"The number of specified semaphore events for DosMuxSemWait is not correct.",	"The number of specified semaphore events for DosMuxSemWait is not correct."	},
	{	ERROR_TOO_MANY_MUXWAITERS,			"ERROR_TOO_MANY_MUXWAITERS",
		"DosMuxSemWait did not execute; too many semaphores are already set.",	"DosMuxSemWait did not execute; too many semaphores are already set."	},
	{	ERROR_INVALID_LIST_FORMAT,			"ERROR_INVALID_LIST_FORMAT",
		"The DosMuxSemWait list is not correct.",	"The DosMuxSemWait list is not correct."	},
	{	ERROR_LABEL_TOO_LONG,			"ERROR_LABEL_TOO_LONG",
		"The volume label you entered exceeds the label character limit of the target file system.",	"The volume label you entered exceeds the label character limit of the target file system."	},
	{	ERROR_TOO_MANY_TCBS,			"ERROR_TOO_MANY_TCBS",
		"Cannot create another thread.",	"Cannot create another thread."	},
	{	ERROR_SIGNAL_REFUSED,			"ERROR_SIGNAL_REFUSED",
		"The recipient process has refused the signal.",	"The recipient process has refused the signal."	},
	{	ERROR_DISCARDED,			"ERROR_DISCARDED",
		"The segment is already discarded and cannot be locked.",	"The segment is already discarded and cannot be locked."	},
	{	ERROR_NOT_LOCKED,			"ERROR_NOT_LOCKED",
		"The segment is already unlocked.",	"The segment is already unlocked."	},
	{	ERROR_BAD_THREADID_ADDR,			"ERROR_BAD_THREADID_ADDR",
		"The address for the thread ID is not correct.",	"The address for the thread ID is not correct."	},
	{	ERROR_BAD_ARGUMENTS,			"ERROR_BAD_ARGUMENTS",
		"The argument string passed to DosExecPgm is not correct.",	"The argument string passed to DosExecPgm is not correct."	},
	{	ERROR_BAD_PATHNAME,			"ERROR_BAD_PATHNAME",
		"The specified path is invalid.",	"The specified path is invalid."	},
	{	ERROR_SIGNAL_PENDING,			"ERROR_SIGNAL_PENDING",
		"A signal is already pending.",	"A signal is already pending."	},
	{	ERROR_MAX_THRDS_REACHED,			"ERROR_MAX_THRDS_REACHED",
		"No more threads can be created in the system.",	"No more threads can be created in the system."	},
	{	ERROR_LOCK_FAILED,			"ERROR_LOCK_FAILED",
		"Unable to lock a region of a file.",	"Unable to lock a region of a file."	},
	{	ERROR_BUSY,			"ERROR_BUSY",
		"The requested resource is in use.",	"The requested resource is in use."	},
	{	ERROR_CANCEL_VIOLATION,			"ERROR_CANCEL_VIOLATION",
		"A lock request was not outstanding for the supplied cancel region.",	"A lock request was not outstanding for the supplied cancel region."	},
	{	ERROR_ATOMIC_LOCKS_NOT_SUPPORTED,			"ERROR_ATOMIC_LOCKS_NOT_SUPPORTED",
		"The file system does not support atomic changes to the lock type.",	"The file system does not support atomic changes to the lock type."	},
	{	ERROR_INVALID_SEGMENT_NUMBER,			"ERROR_INVALID_SEGMENT_NUMBER",
		"The system detected a segment number that was not correct.",	"The system detected a segment number that was not correct."	},
	{	ERROR_INVALID_ORDINAL,			"ERROR_INVALID_ORDINAL",
		"The operating system cannot run .",	"The operating system cannot run ."	},
	{	ERROR_ALREADY_EXISTS,			"ERROR_ALREADY_EXISTS",
		"Cannot create a file when that file already exists.",	"Cannot create a file when that file already exists."	},
	{	ERROR_INVALID_FLAG_NUMBER,			"ERROR_INVALID_FLAG_NUMBER",
		"The flag passed is not correct.",	"The flag passed is not correct."	},
	{	ERROR_SEM_NOT_FOUND,			"ERROR_SEM_NOT_FOUND",
		"The specified system semaphore name was not found.",	"The specified system semaphore name was not found."	},
	{	ERROR_INVALID_STARTING_CODESEG,			"ERROR_INVALID_STARTING_CODESEG",
		"The operating system cannot run the requested resource (invalid starting code seg).",	"The operating system cannot run the requested resource (invalid starting code seg)."	},
	{	ERROR_INVALID_STACKSEG,			"ERROR_INVALID_STACKSEG",
		"The operating system cannot run the requested resource (invalid starting stack seg).",	"The operating system cannot run the requested resource (invalid starting stack seg)."	},
	{	ERROR_INVALID_MODULETYPE,			"ERROR_INVALID_MODULETYPE",
		"The operating system cannot run the requested resource (invalid module type).",	"The operating system cannot run the requested resource (invalid module type)."	},
	{	ERROR_INVALID_EXE_SIGNATURE,			"ERROR_INVALID_EXE_SIGNATURE",
		"Cannot run EXE file in Win32 mode.",	"Cannot run EXE file in Win32 mode."	},
	{	ERROR_EXE_MARKED_INVALID,			"ERROR_EXE_MARKED_INVALID",
		"The operating system cannot run the requested resource (EXE marked as invalid).",	"The success status codes 256, 257, 258, and 258 are reserved for User APC, Kernel APC, Alerted, and Timeout."	},
	{	ERROR_BAD_EXE_FORMAT,			"ERROR_BAD_EXE_FORMAT",
		"Has a bad EXE format --- not a valid Win32 application.",	"Has a bad EXE format --- not a valid Win32 application."	},
	{	ERROR_ITERATED_DATA_EXCEEDS_64k,			"ERROR_ITERATED_DATA_EXCEEDS_64k",
		"The operating system cannot run the requested resource (iterated data exceeds 64K).",	"The operating system cannot run the requested resource (iterated data exceeds 64K)."	},
	{	ERROR_INVALID_MINALLOCSIZE,			"ERROR_INVALID_MINALLOCSIZE",
		"The operating system cannot run the requested resource (invalid min alloc size).",	"The operating system cannot run the requested resource (invalid min alloc size)."	},
	{	ERROR_DYNLINK_FROM_INVALID_RING,			"ERROR_DYNLINK_FROM_INVALID_RING",
		"The operating system cannot run this application program.",	"The operating system cannot run this application program."	},
	{	ERROR_IOPL_NOT_ENABLED,			"ERROR_IOPL_NOT_ENABLED",
		"The operating system is not presently configured to run this application.",	"The operating system is not presently configured to run this application."	},
	{	ERROR_INVALID_SEGDPL,			"ERROR_INVALID_SEGDPL",
		"The operating system cannot run the requested resource (invalid seg DPL).",	"The operating system cannot run the requested resource (invalid seg DPL)."	},
	{	ERROR_AUTODATASEG_EXCEEDS_64k,			"ERROR_AUTODATASEG_EXCEEDS_64k",
		"The operating system cannot run this application program.",	"The operating system cannot run this application program."	},
	{	ERROR_RING2SEG_MUST_BE_MOVABLE,			"ERROR_RING2SEG_MUST_BE_MOVABLE",
		"The code segment cannot be greater than or equal to 64K.",	"The code segment cannot be greater than or equal to 64KB."	},
	{	ERROR_RELOC_CHAIN_XEEDS_SEGLIM,			"ERROR_RELOC_CHAIN_XEEDS_SEGLIM",
		"The operating system cannot run the requested resource (reloc chain needs seg lim).",	"The operating system cannot run the requested resource (reloc chain needs seg lim)."	},
	{	ERROR_INFLOOP_IN_RELOC_CHAIN,			"ERROR_INFLOOP_IN_RELOC_CHAIN",
		"The operating system cannot run the requested resource (INFLOOP in reloc chain).",	"The operating system cannot run the requested resource (INFLOOP in reloc chain)."	},
	{	ERROR_ENVVAR_NOT_FOUND,			"ERROR_ENVVAR_NOT_FOUND",
		"The system could not find the environment option that was entered.",	"The system could not find the environment option that was entered."	},
	{	ERROR_NO_SIGNAL_SENT,			"ERROR_NO_SIGNAL_SENT",
		"No process in the command subtree has a signal handler.",	"No process in the command subtree has a signal handler."	},
	{	ERROR_FILENAME_EXCED_RANGE,			"ERROR_FILENAME_EXCED_RANGE",
		"The filename or extension is too long.",	"The filename or extension is too long."	},
	{	ERROR_RING2_STACK_IN_USE,			"ERROR_RING2_STACK_IN_USE",
		"The ring 2 stack is in use.",	"The ring 2 stack is in use."	},
	{	ERROR_META_EXPANSION_TOO_LONG,			"ERROR_META_EXPANSION_TOO_LONG",
		"The global filename characters, * or ?, are entered incorrectly or too many global filename characters are specified.",	"The global filename characters, * or ?, are entered incorrectly or too many global filename characters are specified."	},
	{	ERROR_INVALID_SIGNAL_NUMBER,			"ERROR_INVALID_SIGNAL_NUMBER",
		"The signal being posted is not correct.",	"The signal being posted is not correct."	},
	{	ERROR_THREAD_1_INACTIVE,			"ERROR_THREAD_1_INACTIVE",
		"The signal handler cannot be set.",	"The signal handler cannot be set."	},
	{	ERROR_LOCKED,			"ERROR_LOCKED",
		"The segment is locked and cannot be reallocated.",	"The segment is locked and cannot be reallocated."	},
	{	ERROR_TOO_MANY_MODULES,			"ERROR_TOO_MANY_MODULES",
		"Too many dynamic-link modules are attached to this program or dynamic-link module.",	"Too many dynamic link modules are attached to this program or dynamic link module."	},
	{	ERROR_NESTING_NOT_ALLOWED,			"ERROR_NESTING_NOT_ALLOWED",
		"Can't nest calls to LoadModule.",	"Can't nest calls to LoadModule."	},
	{	ERROR_EXE_MACHINE_TYPE_MISMATCH,			"ERROR_EXE_MACHINE_TYPE_MISMATCH",
		"The image file is valid, but is for a machine type other than the current machine.",	"The image file is valid, but is for a machine type other than the current machine."	},
	{	ERROR_BAD_PIPE,			"ERROR_BAD_PIPE",
		"The pipe state is invalid.",	"The pipe state is invalid."	},
	{	ERROR_PIPE_BUSY,			"ERROR_PIPE_BUSY",
		"All pipe instances are busy.",	"All pipe instances are busy."	},
	{	ERROR_NO_DATA,			"ERROR_NO_DATA",
		"The pipe is being closed.",	"The pipe is being closed."	},
	{	ERROR_PIPE_NOT_CONNECTED,			"ERROR_PIPE_NOT_CONNECTED",
		"No process is on the other end of the pipe.",	"No process is on the other end of the pipe."	},
	{	ERROR_MORE_DATA,			"ERROR_MORE_DATA",
		"More data is available.",	"More data is available."	},
	{	ERROR_VC_DISCONNECTED,			"ERROR_VC_DISCONNECTED",
		"The session was canceled.",	"The session was cancelled."	},
	{	ERROR_INVALID_EA_NAME,			"ERROR_INVALID_EA_NAME",
		"The specified extended attribute name was invalid.",	"The specified extended attribute name was invalid."	},
	{	ERROR_EA_LIST_INCONSISTENT,			"ERROR_EA_LIST_INCONSISTENT",
		"The extended attributes are inconsistent.",	"The extended attributes are inconsistent."	},
	{	ERROR_NO_MORE_ITEMS,			"ERROR_NO_MORE_ITEMS",
		"No more data is available.",	"The operation that was requested is pending completion."	},
	{	ERROR_CANNOT_COPY,			"ERROR_CANNOT_COPY",
		"The copy functions cannot be used.",	"This success level status indicates that the transaction state already exists for the registry sub-tree, but that a transaction commit was previously aborted. The commit has now been completed. This status value is returned by the runtime library (RTL) registry transaction package (RXact)."	},
	{	ERROR_DIRECTORY,			"ERROR_DIRECTORY",
		"The directory name is invalid.",	"This indicates that a notify change request has been completed due to closing the handle which made the notify change request."	},
	{	ERROR_EAS_DIDNT_FIT,			"ERROR_EAS_DIDNT_FIT",
		"The extended attributes did not fit in the buffer.",	"Page fault was a demand zero fault."	},
	{	ERROR_EA_FILE_CORRUPT,			"ERROR_EA_FILE_CORRUPT",
		"The extended attribute file on the mounted file system is corrupt.",	"Page fault was satisfied by reading from a secondary storage device."	},
	{	ERROR_EA_TABLE_FULL,			"ERROR_EA_TABLE_FULL",
		"The extended attribute table file is full.",	"Cached page was locked during operation."	},
	{	ERROR_INVALID_EA_HANDLE,			"ERROR_INVALID_EA_HANDLE",
		"The specified extended attribute handle is invalid.",	"Crash dump exists in paging file."	},
	{	ERROR_EAS_NOT_SUPPORTED,			"ERROR_EAS_NOT_SUPPORTED",
		"The mounted file system does not support extended attributes.",	"The mounted file system does not support extended attributes."	},
	{	ERROR_NOT_OWNER,			"ERROR_NOT_OWNER",
		"Attempt to release mutex not owned by caller.",	"Attempt to release mutex not owned by caller."	},
	{	ERROR_TOO_MANY_POSTS,			"ERROR_TOO_MANY_POSTS",
		"Too many posts were made to a semaphore.",	"Too many posts were made to a semaphore."	},
	{	ERROR_PARTIAL_COPY,			"ERROR_PARTIAL_COPY",
		"Only part of a ReadProcessMemoty or WriteProcessMemory request was completed.",	"Only part of a Read/WriteProcessMemory request was completed."	},
	{	ERROR_OPLOCK_NOT_GRANTED,			"ERROR_OPLOCK_NOT_GRANTED",
		"The oplock request is denied.",	"The oplock request is denied."	},
	{	ERROR_INVALID_OPLOCK_PROTOCOL,			"ERROR_INVALID_OPLOCK_PROTOCOL",
		"An invalid oplock acknowledgment was received by the system.",	"An invalid oplock acknowledgment was received by the system."	},
	{	ERROR_MR_MID_NOT_FOUND,			"ERROR_MR_MID_NOT_FOUND",
		"The system cannot find message text for message number in the message file.",	"The system cannot find message text for message number in the message file."	},
	{	ERROR_INVALID_ADDRESS,			"ERROR_INVALID_ADDRESS",
		"Attempt to access invalid address.",	"Attempt to access invalid address."	},
	{	ERROR_ARITHMETIC_OVERFLOW,			"ERROR_ARITHMETIC_OVERFLOW",
		"Arithmetic result exceeded 32 bits.",	"Arithmetic result exceeded 32 bits."	},
	{	ERROR_PIPE_CONNECTED,			"ERROR_PIPE_CONNECTED",
		"There is a process on other end of the pipe.",	"There is a process on other end of the pipe."	},
	{	ERROR_PIPE_LISTENING,			"ERROR_PIPE_LISTENING",
		"Waiting for a process to open the other end of the pipe.",	"Waiting for a process to open the other end of the pipe."	},
	{	ERROR_EA_ACCESS_DENIED,			"ERROR_EA_ACCESS_DENIED",
		"Access to the extended attribute was denied.",	"Access to the extended attribute was denied."	},
	{	ERROR_OPERATION_ABORTED,			"ERROR_OPERATION_ABORTED",
		"The I/O operation has been aborted because of either a thread exit or an application request.",	"The I/O operation has been aborted because of either a thread exit or an application request."	},
	{	ERROR_IO_INCOMPLETE,			"ERROR_IO_INCOMPLETE",
		"Overlapped I/O event is not in a signaled state.",	"Overlapped I/O event is not in a signalled state."	},
	{	ERROR_IO_PENDING,			"ERROR_IO_PENDING",
		"Overlapped I/O operation is in progress.",	"Overlapped I/O operation is in progress."	},
	{	ERROR_NOACCESS,			"ERROR_NOACCESS",
		"Invalid access to memory location.",	"Invalid access to memory location."	},
	{	ERROR_SWAPERROR,			"ERROR_SWAPERROR",
		"Error performing inpage operation.",	"Error performing inpage operation."	},
	{	ERROR_STACK_OVERFLOW,			"ERROR_STACK_OVERFLOW",
		"Recursion too deep; the stack overflowed.",	"Recursion too deep, stack overflowed."	},
	{	ERROR_INVALID_MESSAGE,			"ERROR_INVALID_MESSAGE",
		"The window cannot act on the sent message.",	"The window cannot act on the sent message."	},
	{	ERROR_CAN_NOT_COMPLETE,			"ERROR_CAN_NOT_COMPLETE",
		"Cannot complete this function.",	"Cannot complete this function."	},
	{	ERROR_INVALID_FLAGS,			"ERROR_INVALID_FLAGS",
		"Invalid flags.",	"Invalid flags."	},
	{	ERROR_UNRECOGNIZED_VOLUME,			"ERROR_UNRECOGNIZED_VOLUME",
		"The volume does not contain a recognized file system. Please make sure that all required file system drivers are loaded and that the volume is not corrupted.",	"The volume does not contain a recognized file system. Please make sure that all required file system drivers are loaded and that the volume is not corrupt."	},
	{	ERROR_FILE_INVALID,			"ERROR_FILE_INVALID",
		"The volume for a file has been externally altered so that the opened file is no longer valid.",	"The volume for a file has been externally altered such that the opened file is no longer valid."	},
	{	ERROR_FULLSCREEN_MODE,			"ERROR_FULLSCREEN_MODE",
		"The requested operation cannot be performed in full-screen mode.",	"The requested operation cannot be performed in full-screen mode."	},
	{	ERROR_NO_TOKEN,			"ERROR_NO_TOKEN",
		"An attempt was made to reference a token that does not exist.",	"An attempt was made to reference a token that does not exist."	},
	{	ERROR_BADDB,			"ERROR_BADDB",
		"The configuration registry database is corrupt.",	"The configuration registry database is corrupt."	},
	{	ERROR_BADKEY,			"ERROR_BADKEY",
		"The configuration registry key is invalid.",	"The configuration registry key is invalid."	},
	{	ERROR_CANTOPEN,			"ERROR_CANTOPEN",
		"The configuration registry key could not be opened.",	"The configuration registry key could not be opened."	},
	{	ERROR_CANTREAD,			"ERROR_CANTREAD",
		"The configuration registry key could not be read.",	"The configuration registry key could not be read."	},
	{	ERROR_CANTWRITE,			"ERROR_CANTWRITE",
		"The configuration registry key could not be written.",	"The configuration registry key could not be written."	},
	{	ERROR_REGISTRY_RECOVERED,			"ERROR_REGISTRY_RECOVERED",
		"One of the files in the registry database had to be recovered by use of a log or alternate copy. The recovery was successful.",	"One of the files in the Registry database had to be recovered by use of a log or alternate copy. The recovery was successful."	},
	{	ERROR_REGISTRY_CORRUPT,			"ERROR_REGISTRY_CORRUPT",
		"The registry is corrupted. The structure of one of the files that contains registry data is corrupted, or the system's image of the file in memory is corrupted, or the file could not be recovered because the alternate copy or log was absent or corrupted.",	"The Registry is corrupt. The structure of one of the files that contains Registry data is corrupt, or the system's image of the file in memory is corrupt, or the file could not be recovered because the alternate copy or log was absent or corrupt."	},
	{	ERROR_REGISTRY_IO_FAILED,			"ERROR_REGISTRY_IO_FAILED",
		"An I/O operation initiated by the registry failed unrecoverably. The registry could not read in, or write out, or flush, one of the files that contain the system's image of the registry.",	"An I/O operation initiated by the Registry failed unrecoverably. The Registry could not read in, or write out, or flush, one of the files that contain the system's image of the Registry."	},
	{	ERROR_NOT_REGISTRY_FILE,			"ERROR_NOT_REGISTRY_FILE",
		"The system has attempted to load or restore a file into the registry, but the specified file is not in a registry file format.",	"The system has attempted to load or restore a file into the Registry, but the specified file is not in a Registry file format."	},
	{	ERROR_KEY_DELETED,			"ERROR_KEY_DELETED",
		"Illegal operation attempted on a registry key that has been marked for deletion.",	"Illegal operation attempted on a Registry key which has been marked for deletion."	},
	{	ERROR_NO_LOG_SPACE,			"ERROR_NO_LOG_SPACE",
		"System could not allocate the required space in a registry log.",	"System could not allocate the required space in a Registry log."	},
	{	ERROR_KEY_HAS_CHILDREN,			"ERROR_KEY_HAS_CHILDREN",
		"Cannot create a symbolic link in a registry key that already has subkeys or values.",	"Cannot create a symbolic link in a Registry key that already has subkeys or values."	},
	{	ERROR_CHILD_MUST_BE_VOLATILE,			"ERROR_CHILD_MUST_BE_VOLATILE",
		"Cannot create a stable subkey under a volatile parent key.",	"Cannot create a stable subkey under a volatile parent key."	},
	{	ERROR_NOTIFY_ENUM_DIR,			"ERROR_NOTIFY_ENUM_DIR",
		"A notify change request is being completed and the information is not being returned in the caller's buffer. The caller now needs to enumerate the files to find the changes.",	"A notify change request is being completed and the information is not being returned in the caller's buffer. The caller now needs to enumerate the files to find the changes."	},
	{	ERROR_DEPENDENT_SERVICES_RUNNING,			"ERROR_DEPENDENT_SERVICES_RUNNING",
		"A stop control has been sent to a service that other running services are dependent on.",	"A stop control has been sent to a service which other running services are dependent on."	},
	{	ERROR_INVALID_SERVICE_CONTROL,			"ERROR_INVALID_SERVICE_CONTROL",
		"The requested control is not valid for this service.",	"The requested control is not valid for this service"	},
	{	ERROR_SERVICE_REQUEST_TIMEOUT,			"ERROR_SERVICE_REQUEST_TIMEOUT",
		"The service did not respond to the start or control request in a timely fashion.",	"The service did not respond to the start or control request in a timely fashion."	},
	{	ERROR_SERVICE_NO_THREAD,			"ERROR_SERVICE_NO_THREAD",
		"A thread could not be created for the service.",	"A thread could not be created for the service."	},
	{	ERROR_SERVICE_DATABASE_LOCKED,			"ERROR_SERVICE_DATABASE_LOCKED",
		"The service database is locked.",	"The service database is locked."	},
	{	ERROR_SERVICE_ALREADY_RUNNING,			"ERROR_SERVICE_ALREADY_RUNNING",
		"An instance of the service is already running.",	"An instance of the service is already running."	},
	{	ERROR_INVALID_SERVICE_ACCOUNT,			"ERROR_INVALID_SERVICE_ACCOUNT",
		"The account name is invalid or does not exist.",	"The account name is invalid or does not exist."	},
	{	ERROR_SERVICE_DISABLED,			"ERROR_SERVICE_DISABLED",
		"The service cannot be started, either because it is disabled or because it has no enabled devices associated with it.",	"The specified service is disabled and cannot be started."	},
	{	ERROR_CIRCULAR_DEPENDENCY,			"ERROR_CIRCULAR_DEPENDENCY",
		"Circular service dependency was specified.",	"Circular service dependency was specified."	},
	{	ERROR_SERVICE_DOES_NOT_EXIST,			"ERROR_SERVICE_DOES_NOT_EXIST",
		"The specified service does not exist as an installed service.",	"The specified service does not exist as an installed service."	},
	{	ERROR_SERVICE_CANNOT_ACCEPT_CTRL,			"ERROR_SERVICE_CANNOT_ACCEPT_CTRL",
		"The service cannot accept control messages at this time.",	"The service cannot accept control messages at this time."	},
	{	ERROR_SERVICE_NOT_ACTIVE,			"ERROR_SERVICE_NOT_ACTIVE",
		"The service has not been started.",	"The service has not been started."	},
	{	ERROR_FAILED_SERVICE_CONTROLLER_CONNECT,			"ERROR_FAILED_SERVICE_CONTROLLER_CONNECT",
		"The service process could not connect to the service controller.",	"The service process could not connect to the service controller."	},
	{	ERROR_EXCEPTION_IN_SERVICE,			"ERROR_EXCEPTION_IN_SERVICE",
		"An exception occurred in the service when handling the control request.",	"An exception occurred in the service when handling the control request."	},
	{	ERROR_DATABASE_DOES_NOT_EXIST,			"ERROR_DATABASE_DOES_NOT_EXIST",
		"The database specified does not exist.",	"The database specified does not exist."	},
	{	ERROR_SERVICE_SPECIFIC_ERROR,			"ERROR_SERVICE_SPECIFIC_ERROR",
		"The service has returned a service-specific error code.",	"The service has returned a service-specific error code."	},
	{	ERROR_PROCESS_ABORTED,			"ERROR_PROCESS_ABORTED",
		"The process terminated unexpectedly.",	"The process terminated unexpectedly."	},
	{	ERROR_SERVICE_DEPENDENCY_FAIL,			"ERROR_SERVICE_DEPENDENCY_FAIL",
		"The dependency service or group failed to start.",	"The dependency service or group failed to start."	},
	{	ERROR_SERVICE_LOGON_FAILED,			"ERROR_SERVICE_LOGON_FAILED",
		"The service did not start due to a logon failure.",	"The service did not start due to a logon failure."	},
	{	ERROR_SERVICE_START_HANG,			"ERROR_SERVICE_START_HANG",
		"After starting, the service hung in a start-pending state.",	"After starting, the service hung in a start-pending state."	},
	{	ERROR_INVALID_SERVICE_LOCK,			"ERROR_INVALID_SERVICE_LOCK",
		"The specified service database lock is invalid.",	"The specified service database lock is invalid."	},
	{	ERROR_SERVICE_MARKED_FOR_DELETE,			"ERROR_SERVICE_MARKED_FOR_DELETE",
		"The specified service has been marked for deletion.",	"The specified service has been marked for deletion."	},
	{	ERROR_SERVICE_EXISTS,			"ERROR_SERVICE_EXISTS",
		"The specified service already exists.",	"The specified service already exists."	},
	{	ERROR_ALREADY_RUNNING_LKG,			"ERROR_ALREADY_RUNNING_LKG",
		"The system is currently running with the last-known-good configuration.",	"The system is currently running with the last-known-good configuration."	},
	{	ERROR_SERVICE_DEPENDENCY_DELETED,			"ERROR_SERVICE_DEPENDENCY_DELETED",
		"The dependency service does not exist or has been marked for deletion.",	"The dependency service does not exist or has been marked for deletion."	},
	{	ERROR_BOOT_ALREADY_ACCEPTED,			"ERROR_BOOT_ALREADY_ACCEPTED",
		"The current boot has already been accepted for use as the last-known-good control set.",	"The current boot has already been accepted for use as the last-known-good control set."	},
	{	ERROR_SERVICE_NEVER_STARTED,			"ERROR_SERVICE_NEVER_STARTED",
		"No attempts to start the service have been made since the last boot.",	"No attempts to start the service have been made since the last boot."	},
	{	ERROR_DUPLICATE_SERVICE_NAME,			"ERROR_DUPLICATE_SERVICE_NAME",
		"The name is already in use as either a service name or a service display name.",	"The name is already in use as either a service name or a service display name."	},
	{	ERROR_DIFFERENT_SERVICE_ACCOUNT,			"ERROR_DIFFERENT_SERVICE_ACCOUNT",
		"The account specified for this service is different from the account specified for other services running in the same process.",	"The account specified for this service is different from the account specified for other services running in the same process."	},
	{	ERROR_CANNOT_DETECT_DRIVER_FAILURE,			"ERROR_CANNOT_DETECT_DRIVER_FAILURE",
		"Failure actions can only be set for Win32 services, not for drivers.",	"Failure actions can only be set for Win32 services, not for drivers."	},
	{	ERROR_CANNOT_DETECT_PROCESS_ABORT,			"ERROR_CANNOT_DETECT_PROCESS_ABORT",
		"This service runs in the same process as the service control manager. Therefore, the service control manager cannot take action if this service's process terminates unexpectedly.",	"This service runs in the same process as the service control manager. Therefore, the service control manager cannot take action if this service's process terminates unexpectedly."	},
	{	ERROR_NO_RECOVERY_PROGRAM,			"ERROR_NO_RECOVERY_PROGRAM",
		"No recovery program has been configured for this service.",	"No recovery program has been configured for this service."	},
	{	ERROR_END_OF_MEDIA,			"ERROR_END_OF_MEDIA",
		"The physical end of the tape has been reached.",	"The physical end of the tape has been reached."	},
	{	ERROR_FILEMARK_DETECTED,			"ERROR_FILEMARK_DETECTED",
		"A tape access reached a filemark.",	"A tape access reached a filemark."	},
	{	ERROR_BEGINNING_OF_MEDIA,			"ERROR_BEGINNING_OF_MEDIA",
		"The beginning of the tape or a partition was encountered.",	"Beginning of tape or partition was encountered."	},
	{	ERROR_SETMARK_DETECTED,			"ERROR_SETMARK_DETECTED",
		"A tape access reached the end of a set of files.",	"A tape access reached the end of a set of files."	},
	{	ERROR_NO_DATA_DETECTED,			"ERROR_NO_DATA_DETECTED",
		"No more data is on the tape.",	"No more data is on the tape."	},
	{	ERROR_PARTITION_FAILURE,			"ERROR_PARTITION_FAILURE",
		"Tape could not be partitioned.",	"Tape could not be partitioned."	},
	{	ERROR_INVALID_BLOCK_LENGTH,			"ERROR_INVALID_BLOCK_LENGTH",
		"When accessing a new tape of a multivolume partition, the current blocksize is incorrect.",	"When accessing a new tape of a multivolume partition, the current blocksize is incorrect."	},
	{	ERROR_DEVICE_NOT_PARTITIONED,			"ERROR_DEVICE_NOT_PARTITIONED",
		"Tape partition information could not be found when loading a tape.",	"Tape partition information could not be found when loading a tape."	},
	{	ERROR_UNABLE_TO_LOCK_MEDIA,			"ERROR_UNABLE_TO_LOCK_MEDIA",
		"Unable to lock the media eject mechanism.",	"Unable to lock the media eject mechanism."	},
	{	ERROR_UNABLE_TO_UNLOAD_MEDIA,			"ERROR_UNABLE_TO_UNLOAD_MEDIA",
		"Unable to unload the media.",	"Unable to unload the media."	},
	{	ERROR_MEDIA_CHANGED,			"ERROR_MEDIA_CHANGED",
		"The media in the drive may have changed.",	"Media in drive may have changed."	},
	{	ERROR_BUS_RESET,			"ERROR_BUS_RESET",
		"The I/O bus was reset.",	"The I/O bus was reset."	},
	{	ERROR_NO_MEDIA_IN_DRIVE,			"ERROR_NO_MEDIA_IN_DRIVE",
		"No media in drive.",	"No media in drive."	},
	{	ERROR_NO_UNICODE_TRANSLATION,			"ERROR_NO_UNICODE_TRANSLATION",
		"No mapping for the Unicode character exists in the target multi-byte code page.",	"No mapping for the Unicode character exists in the target multi-byte code page."	},
	{	ERROR_DLL_INIT_FAILED,			"ERROR_DLL_INIT_FAILED",
		"A dynamic link library (DLL) initialization routine failed.",	"A dynamic link library (DLL) initialization routine failed."	},
	{	ERROR_SHUTDOWN_IN_PROGRESS,			"ERROR_SHUTDOWN_IN_PROGRESS",
		"A system shutdown is in progress.",	"A system shutdown is in progress."	},
	{	ERROR_NO_SHUTDOWN_IN_PROGRESS,			"ERROR_NO_SHUTDOWN_IN_PROGRESS",
		"Unable to abort the system shutdown because no shutdown was in progress.",	"Unable to abort the system shutdown because no shutdown was in progress."	},
	{	ERROR_IO_DEVICE,			"ERROR_IO_DEVICE",
		"The request could not be performed because of an I/O device error.",	"The request could not be performed because of an I/O device error."	},
	{	ERROR_SERIAL_NO_DEVICE,			"ERROR_SERIAL_NO_DEVICE",
		"No serial device was successfully initialized. The serial driver will unload.",	"No serial device was successfully initialized. The serial driver will unload."	},
	{	ERROR_IRQ_BUSY,			"ERROR_IRQ_BUSY",
		"Unable to open a device that was sharing an interrupt request (IRQ) with other devices. At least one other device that uses that IRQ was already opened.",	"Unable to open a device that was sharing an interrupt request (IRQ) with other devices. At least one other device that uses that IRQ was already opened."	},
	{	ERROR_MORE_WRITES,			"ERROR_MORE_WRITES",
		"A serial I/O operation was completed by another write to the serial port. (The IOCTL_SERIAL_XOFF_COUNTER reached zero.)",	"A serial I/O operation was completed by another write to the serial port. (The IOCTL_SERIAL_XOFF_COUNTER reached zero.)"	},
	{	ERROR_COUNTER_TIMEOUT,			"ERROR_COUNTER_TIMEOUT",
		"A serial I/O operation completed because the timeout period expired. (The IOCTL_SERIAL_XOFF_COUNTER did not reach zero.)",	"A serial I/O operation completed because the time-out period expired. (The IOCTL_SERIAL_XOFF_COUNTER did not reach zero.)"	},
	{	ERROR_FLOPPY_ID_MARK_NOT_FOUND,			"ERROR_FLOPPY_ID_MARK_NOT_FOUND",
		"No ID address mark was found on the floppy disk.",	"No ID address mark was found on the floppy disk."	},
	{	ERROR_FLOPPY_WRONG_CYLINDER,			"ERROR_FLOPPY_WRONG_CYLINDER",
		"Mismatch between the floppy disk sector ID field and the floppy disk controller track address.",	"Mismatch between the floppy disk sector ID field and the floppy disk controller track address."	},
	{	ERROR_FLOPPY_UNKNOWN_ERROR,			"ERROR_FLOPPY_UNKNOWN_ERROR",
		"The floppy disk controller reported an error that is not recognized by the floppy disk driver.",	"The floppy disk controller reported an error that is not recognized by the floppy disk driver."	},
	{	ERROR_FLOPPY_BAD_REGISTERS,			"ERROR_FLOPPY_BAD_REGISTERS",
		"The floppy disk controller returned inconsistent results in its registers.",	"The floppy disk controller returned inconsistent results in its registers."	},
	{	ERROR_DISK_RECALIBRATE_FAILED,			"ERROR_DISK_RECALIBRATE_FAILED",
		"While accessing the hard disk, a recalibrate operation failed, even after retries.",	"While accessing the hard disk, a recalibrate operation failed, even after retries."	},
	{	ERROR_DISK_OPERATION_FAILED,			"ERROR_DISK_OPERATION_FAILED",
		"While accessing the hard disk, a disk operation failed even after retries.",	"While accessing the hard disk, a disk operation failed even after retries."	},
	{	ERROR_DISK_RESET_FAILED,			"ERROR_DISK_RESET_FAILED",
		"While accessing the hard disk, a disk controller reset was needed, but even that failed.",	"While accessing the hard disk, a disk controller reset was needed, but even that failed."	},
	{	ERROR_EOM_OVERFLOW,			"ERROR_EOM_OVERFLOW",
		"Physical end of tape encountered.",	"Physical end of tape encountered."	},
	{	ERROR_NOT_ENOUGH_SERVER_MEMORY,			"ERROR_NOT_ENOUGH_SERVER_MEMORY",
		"Not enough server storage is available to process this command.",	"Not enough server storage is available to process this command."	},
	{	ERROR_POSSIBLE_DEADLOCK,			"ERROR_POSSIBLE_DEADLOCK",
		"A potential deadlock condition has been detected.",	"A potential deadlock condition has been detected."	},
	{	ERROR_MAPPED_ALIGNMENT,			"ERROR_MAPPED_ALIGNMENT",
		"The base address or the file offset specified does not have the proper alignment.",	"The base address or the file offset specified does not have the proper alignment."	},
	{	ERROR_SET_POWER_STATE_VETOED,			"ERROR_SET_POWER_STATE_VETOED",
		"An attempt to change the system power state was vetoed by another application or driver.",	"An attempt to change the system power state was vetoed by another application or driver."	},
	{	ERROR_SET_POWER_STATE_FAILED,			"ERROR_SET_POWER_STATE_FAILED",
		"The system BIOS failed an attempt to change the system power state.",	"The system BIOS failed an attempt to change the system power state."	},
	{	ERROR_TOO_MANY_LINKS,			"ERROR_TOO_MANY_LINKS",
		"An attempt was made to create more links on a file than the file system supports.",	"An attempt was made to create more links on a file than the file system supports."	},
	{	ERROR_OLD_WIN_VERSION,			"ERROR_OLD_WIN_VERSION",
		"The specified program requires a newer version of Windows.",	"The specified program requires a newer version of Windows."	},
	{	ERROR_APP_WRONG_OS,			"ERROR_APP_WRONG_OS",
		"The specified program is not a Windows or MS-DOS program.",	"The specified program is not a Windows or MS-DOS program."	},
	{	ERROR_SINGLE_INSTANCE_APP,			"ERROR_SINGLE_INSTANCE_APP",
		"Cannot start more than one instance of the specified program.",	"Cannot start more than one instance of the specified program."	},
	{	ERROR_RMODE_APP,			"ERROR_RMODE_APP",
		"The specified program was written for an earlier version of Windows.",	"The specified program was written for an older version of Windows."	},
	{	ERROR_INVALID_DLL,			"ERROR_INVALID_DLL",
		"One of the library files needed to run this application is damaged.",	"One of the library files needed to run this application is damaged."	},
	{	ERROR_NO_ASSOCIATION,			"ERROR_NO_ASSOCIATION",
		"No application is associated with the specified file for this operation.",	"No application is associated with the specified file for this operation."	},
	{	ERROR_DDE_FAIL,			"ERROR_DDE_FAIL",
		"An error occurred in sending the command to the application.",	"An error occurred in sending the command to the application."	},
	{	ERROR_DLL_NOT_FOUND,			"ERROR_DLL_NOT_FOUND",
		"One of the library files needed to run this application cannot be found.",	"One of the library files needed to run this application cannot be found."	},
	{	ERROR_NO_MORE_USER_HANDLES,			"ERROR_NO_MORE_USER_HANDLES",
		"The current process has used all of its system allowance of handles for Window Manager objects.",	"The current process has used all of its system allowance of handles for Window Manager objects."	},
	{	ERROR_MESSAGE_SYNC_ONLY,			"ERROR_MESSAGE_SYNC_ONLY",
		"The message can be used only with synchronous operations.",	"The message can be used only with synchronous operations."	},
	{	ERROR_SOURCE_ELEMENT_EMPTY,			"ERROR_SOURCE_ELEMENT_EMPTY",
		"The indicated source element has no media.",	"The indicated source element has no media."	},
	{	ERROR_DESTINATION_ELEMENT_FULL,			"ERROR_DESTINATION_ELEMENT_FULL",
		"The indicated destination element already contains media.",	"The indicated destination element already contains media."	},
	{	ERROR_ILLEGAL_ELEMENT_ADDRESS,			"ERROR_ILLEGAL_ELEMENT_ADDRESS",
		"The indicated element does not exist.",	"The indicated element does not exist."	},
	{	ERROR_MAGAZINE_NOT_PRESENT,			"ERROR_MAGAZINE_NOT_PRESENT",
		"The indicated element is part of a magazine that is not present.",	"The indicated element is part of a magazine that is not present."	},
	{	ERROR_DEVICE_REINITIALIZATION_NEEDED,			"ERROR_DEVICE_REINITIALIZATION_NEEDED",
		"The indicated device requires reinitialization due to hardware errors.",	"The indicated device requires reinitialization due to hardware errors."	},
	{	ERROR_DEVICE_REQUIRES_CLEANING,			"ERROR_DEVICE_REQUIRES_CLEANING",
		"The device has indicated that cleaning is required before further operations are attempted.",	"The device has indicated that cleaning is required before further operations are attempted."	},
	{	ERROR_DEVICE_DOOR_OPEN,			"ERROR_DEVICE_DOOR_OPEN",
		"The device has indicated that its door is open.",	"The device has indicated that its door is open."	},
	{	ERROR_DEVICE_NOT_CONNECTED,			"ERROR_DEVICE_NOT_CONNECTED",
		"The device is not connected.",	"The device is not connected."	},
	{	ERROR_NOT_FOUND,			"ERROR_NOT_FOUND",
		"Element not found.",	"Element not found."	},
	{	ERROR_NO_MATCH,			"ERROR_NO_MATCH",
		"There was no match for the specified key in the index.",	"There was no match for the specified key in the index."	},
	{	ERROR_SET_NOT_FOUND,			"ERROR_SET_NOT_FOUND",
		"The property set specified does not exist on the object.",	"The property set specified does not exist on the object."	},
	{	ERROR_POINT_NOT_FOUND,			"ERROR_POINT_NOT_FOUND",
		"The point passed to GetMouseMovePoints is not in the buffer.",	"The point passed to GetMouseMovePoints is not in the buffer."	},
	{	ERROR_NO_TRACKING_SERVICE,			"ERROR_NO_TRACKING_SERVICE",
		"The tracking (workstation) service is not running.",	"The tracking (workstation) service is not running."	},
	{	ERROR_NO_VOLUME_ID,			"ERROR_NO_VOLUME_ID",
		"The Volume ID could not be found.",	"The Volume ID could not be found."	},
	{	ERROR_CONNECTED_OTHER_PASSWORD,			"ERROR_CONNECTED_OTHER_PASSWORD",
		"The network connection was made successfully, but the user had to be prompted for a password other than the one originally specified.",	"The network connection was made successfully but the user had to be prompted for a password other than the one originally specified."	},
	{	ERROR_BAD_USERNAME,			"ERROR_BAD_USERNAME",
		"The specified username is invalid.",	"The specified username is invalid."	},
	{	ERROR_NOT_CONNECTED,			"ERROR_NOT_CONNECTED",
		"This network connection does not exist.",	"This network connection does not exist."	},
	{	ERROR_OPEN_FILES,			"ERROR_OPEN_FILES",
		"This network connection has files open or requests pending.",	"This network connection has files open or requests pending."	},
	{	ERROR_ACTIVE_CONNECTIONS,			"ERROR_ACTIVE_CONNECTIONS",
		"Active connections still exist.",	"Active connections still exist."	},
	{	ERROR_DEVICE_IN_USE,			"ERROR_DEVICE_IN_USE",
		"The device is in use by an active process and cannot be disconnected.",	"The device is in use by an active process and cannot be disconnected."	},
	{	ERROR_BAD_DEVICE,			"ERROR_BAD_DEVICE",
		"The specified device name is invalid.",	"The specified device name is invalid."	},
	{	ERROR_CONNECTION_UNAVAIL,			"ERROR_CONNECTION_UNAVAIL",
		"The device is not currently connected but it is a remembered connection.",	"The device is not currently connected but it is a remembered connection."	},
	{	ERROR_DEVICE_ALREADY_REMEMBERED,			"ERROR_DEVICE_ALREADY_REMEMBERED",
		"An attempt was made to remember a device that had previously been remembered.",	"An attempt was made to remember a device that had previously been remembered."	},
	{	ERROR_NO_NET_OR_BAD_PATH,			"ERROR_NO_NET_OR_BAD_PATH",
		"No network provider accepted the given network path.",	"No network provider accepted the given network path."	},
	{	ERROR_BAD_PROVIDER,			"ERROR_BAD_PROVIDER",
		"The specified network provider name is invalid.",	"The specified network provider name is invalid."	},
	{	ERROR_CANNOT_OPEN_PROFILE,			"ERROR_CANNOT_OPEN_PROFILE",
		"Unable to open the network connection profile.",	"Unable to open the network connection profile."	},
	{	ERROR_BAD_PROFILE,			"ERROR_BAD_PROFILE",
		"The network connection profile is corrupted.",	"The network connection profile is corrupt."	},
	{	ERROR_NOT_CONTAINER,			"ERROR_NOT_CONTAINER",
		"Cannot enumerate a noncontainer.",	"Cannot enumerate a non-container."	},
	{	ERROR_EXTENDED_ERROR,			"ERROR_EXTENDED_ERROR",
		"An extended error has occurred.",	"An extended error has occurred."	},
	{	ERROR_INVALID_GROUPNAME,			"ERROR_INVALID_GROUPNAME",
		"The format of the specified group name is invalid.",	"The format of the specified group name is invalid."	},
	{	ERROR_INVALID_COMPUTERNAME,			"ERROR_INVALID_COMPUTERNAME",
		"The format of the specified computer name is invalid.",	"The format of the specified computer name is invalid."	},
	{	ERROR_INVALID_EVENTNAME,			"ERROR_INVALID_EVENTNAME",
		"The format of the specified event name is invalid.",	"The format of the specified event name is invalid."	},
	{	ERROR_INVALID_DOMAINNAME,			"ERROR_INVALID_DOMAINNAME",
		"The format of the specified domain name is invalid.",	"The format of the specified domain name is invalid."	},
	{	ERROR_INVALID_SERVICENAME,			"ERROR_INVALID_SERVICENAME",
		"The format of the specified service name is invalid.",	"The format of the specified service name is invalid."	},
	{	ERROR_INVALID_NETNAME,			"ERROR_INVALID_NETNAME",
		"The format of the specified network name is invalid.",	"The format of the specified network name is invalid."	},
	{	ERROR_INVALID_SHARENAME,			"ERROR_INVALID_SHARENAME",
		"The format of the specified share name is invalid.",	"The format of the specified share name is invalid."	},
	{	ERROR_INVALID_PASSWORDNAME,			"ERROR_INVALID_PASSWORDNAME",
		"The format of the specified password is invalid.",	"The format of the specified password is invalid."	},
	{	ERROR_INVALID_MESSAGENAME,			"ERROR_INVALID_MESSAGENAME",
		"The format of the specified message name is invalid.",	"The format of the specified message name is invalid."	},
	{	ERROR_INVALID_MESSAGEDEST,			"ERROR_INVALID_MESSAGEDEST",
		"The format of the specified message destination is invalid.",	"The format of the specified message destination is invalid."	},
	{	ERROR_SESSION_CREDENTIAL_CONFLICT,			"ERROR_SESSION_CREDENTIAL_CONFLICT",
		"The credentials supplied conflict with an existing set of credentials.",	"The credentials supplied conflict with an existing set of credentials."	},
	{	ERROR_REMOTE_SESSION_LIMIT_EXCEEDED,			"ERROR_REMOTE_SESSION_LIMIT_EXCEEDED",
		"An attempt was made to establish a session to a network server, but there are already too many sessions established to that server.",	"An attempt was made to establish a session to a network server, but there are already too many sessions established to that server."	},
	{	ERROR_DUP_DOMAINNAME,			"ERROR_DUP_DOMAINNAME",
		"The workgroup or domain name is already in use by another computer on the network.",	"The workgroup or domain name is already in use by another computer on the network."	},
	{	ERROR_NO_NETWORK,			"ERROR_NO_NETWORK",
		"The network is not present or not started.",	"The network is not present or not started."	},
	{	ERROR_CANCELLED,			"ERROR_CANCELLED",
		"The operation was canceled by the user.",	"The operation was cancelled by the user."	},
	{	ERROR_USER_MAPPED_FILE,			"ERROR_USER_MAPPED_FILE",
		"The requested operation cannot be performed on a file with a user-mapped section open.",	"The requested operation cannot be performed on a file with a user mapped section open."	},
	{	ERROR_CONNECTION_REFUSED,			"ERROR_CONNECTION_REFUSED",
		"The remote system refused the network connection.",	"The remote system refused the network connection."	},
	{	ERROR_GRACEFUL_DISCONNECT,			"ERROR_GRACEFUL_DISCONNECT",
		"The network connection was gracefully closed.",	"The network connection was gracefully closed."	},
	{	ERROR_ADDRESS_ALREADY_ASSOCIATED,			"ERROR_ADDRESS_ALREADY_ASSOCIATED",
		"The network transport endpoint already has an address associated with it.",	"The network transport endpoint already has an address associated with it."	},
	{	ERROR_ADDRESS_NOT_ASSOCIATED,			"ERROR_ADDRESS_NOT_ASSOCIATED",
		"An address has not yet been associated with the network endpoint.",	"An address has not yet been associated with the network endpoint."	},
	{	ERROR_CONNECTION_INVALID,			"ERROR_CONNECTION_INVALID",
		"An operation was attempted on a nonexistent network connection.",	"An operation was attempted on a non-existent network connection."	},
	{	ERROR_CONNECTION_ACTIVE,			"ERROR_CONNECTION_ACTIVE",
		"An invalid operation was attempted on an active network connection.",	"An invalid operation was attempted on an active network connection."	},
	{	ERROR_NETWORK_UNREACHABLE,			"ERROR_NETWORK_UNREACHABLE",
		"The remote network is not reachable by the transport.",	"The remote network is not reachable by the transport."	},
	{	ERROR_HOST_UNREACHABLE,			"ERROR_HOST_UNREACHABLE",
		"The remote system is not reachable by the transport.",	"The remote system is not reachable by the transport."	},
	{	ERROR_PROTOCOL_UNREACHABLE,			"ERROR_PROTOCOL_UNREACHABLE",
		"The remote system does not support the transport protocol.",	"The remote system does not support the transport protocol."	},
	{	ERROR_PORT_UNREACHABLE,			"ERROR_PORT_UNREACHABLE",
		"No service is operating at the destination network endpoint on the remote system.",	"No service is operating at the destination network endpoint on the remote system."	},
	{	ERROR_REQUEST_ABORTED,			"ERROR_REQUEST_ABORTED",
		"The request was aborted.",	"The request was aborted."	},
	{	ERROR_CONNECTION_ABORTED,			"ERROR_CONNECTION_ABORTED",
		"The network connection was aborted by the local system.",	"The network connection was aborted by the local system."	},
	{	ERROR_RETRY,			"ERROR_RETRY",
		"The operation could not be completed. A retry should be performed.",	"The operation could not be completed. A retry should be performed."	},
	{	ERROR_CONNECTION_COUNT_LIMIT,			"ERROR_CONNECTION_COUNT_LIMIT",
		"A connection to the server could not be made because the limit on the number of concurrent connections for this account has been reached.",	"A connection to the server could not be made because the limit on the number of concurrent connections for this account has been reached."	},
	{	ERROR_LOGIN_TIME_RESTRICTION,			"ERROR_LOGIN_TIME_RESTRICTION",
		"Attempting to log in during an unauthorized time of day for this account.",	"Attempting to login during an unauthorized time of day for this account."	},
	{	ERROR_LOGIN_WKSTA_RESTRICTION,			"ERROR_LOGIN_WKSTA_RESTRICTION",
		"The account is not authorized to log in from this station.",	"The account is not authorized to login from this station."	},
	{	ERROR_INCORRECT_ADDRESS,			"ERROR_INCORRECT_ADDRESS",
		"The network address could not be used for the operation requested.",	"The network address could not be used for the operation requested."	},
	{	ERROR_ALREADY_REGISTERED,			"ERROR_ALREADY_REGISTERED",
		"The service is already registered.",	"The service is already registered."	},
	{	ERROR_SERVICE_NOT_FOUND,			"ERROR_SERVICE_NOT_FOUND",
		"The specified service does not exist.",	"The specified service does not exist."	},
	{	ERROR_NOT_AUTHENTICATED,			"ERROR_NOT_AUTHENTICATED",
		"The operation being requested was not performed because the user has not been authenticated.",	"The operation being requested was not performed because the user has not been authenticated."	},
	{	ERROR_NOT_LOGGED_ON,			"ERROR_NOT_LOGGED_ON",
		"The operation being requested was not performed because the user has not logged on to the network. The specified service does not exist.",	"The operation being requested was not performed because the user has not logged on to the network. The specified service does not exist."	},
	{	ERROR_CONTINUE,			"ERROR_CONTINUE",
		"Continue with work in progress.",	"Return that wants caller to continue with work in progress."	},
	{	ERROR_ALREADY_INITIALIZED,			"ERROR_ALREADY_INITIALIZED",
		"An attempt was made to perform an initialization operation when initialization has already been completed.",	"An attempt was made to perform an initialization operation when initialization has already been completed."	},
	{	ERROR_NO_MORE_DEVICES,			"ERROR_NO_MORE_DEVICES",
		"No more local devices.",	"No more local devices."	},
	{	ERROR_NO_SUCH_SITE,			"ERROR_NO_SUCH_SITE",
		"The specified site does not exist.",	"The specified site does not exist."	},
	{	ERROR_DOMAIN_CONTROLLER_EXISTS,			"ERROR_DOMAIN_CONTROLLER_EXISTS",
		"A domain controller with the specified name already exists.",	"A domain controller with the specified name already exists."	},
	{	ERROR_DS_NOT_INSTALLED,			"ERROR_DS_NOT_INSTALLED",
		"An error occurred while installing the Windows NT directory service. Please view the event log for more information.",	"An error occurred while installing the Windows NT directory service. Please view the event log for more information."	},
	{	ERROR_NOT_ALL_ASSIGNED,			"ERROR_NOT_ALL_ASSIGNED",
		"Not all privileges referenced are assigned to the caller.",	"Not all privileges referenced are assigned to the caller."	},
	{	ERROR_SOME_NOT_MAPPED,			"ERROR_SOME_NOT_MAPPED",
		"Some mapping between account names and security IDs was not done.",	"Some mapping between account names and security IDs was not done."	},
	{	ERROR_NO_QUOTAS_FOR_ACCOUNT,			"ERROR_NO_QUOTAS_FOR_ACCOUNT",
		"No system quota limits are specifically set for this account.",	"No system quota limits are specifically set for this account."	},
	{	ERROR_LOCAL_USER_SESSION_KEY,			"ERROR_LOCAL_USER_SESSION_KEY",
		"No encryption key is available. A well-known encryption key was returned.",	"No encryption key is available. A well-known encryption key was returned."	},
	{	ERROR_NULL_LM_PASSWORD,			"ERROR_NULL_LM_PASSWORD",
		"The Windows NT password is too complex to be converted to a LAN Manager password. The LAN Manager password returned is a NULL string.",	"The NT password is too complex to be converted to a LAN Manager password. The LAN Manager password returned is a NULL string."	},
	{	ERROR_UNKNOWN_REVISION,			"ERROR_UNKNOWN_REVISION",
		"The revision level is unknown.",	"The revision level is unknown."	},
	{	ERROR_REVISION_MISMATCH,			"ERROR_REVISION_MISMATCH",
		"Indicates two revision levels are incompatible.",	"Indicates two revision levels are incompatible."	},
	{	ERROR_INVALID_OWNER,			"ERROR_INVALID_OWNER",
		"This security ID may not be assigned as the owner of this object.",	"This security ID may not be assigned as the owner of this object."	},
	{	ERROR_INVALID_PRIMARY_GROUP,			"ERROR_INVALID_PRIMARY_GROUP",
		"This security ID may not be assigned as the primary group of an object.",	"This security ID may not be assigned as the primary group of an object."	},
	{	ERROR_NO_IMPERSONATION_TOKEN,			"ERROR_NO_IMPERSONATION_TOKEN",
		"An attempt has been made to operate on an impersonation token by a thread that is not currently impersonating a client.",	"An attempt has been made to operate on an impersonation token by a thread that is not currently impersonating a client."	},
	{	ERROR_CANT_DISABLE_MANDATORY,			"ERROR_CANT_DISABLE_MANDATORY",
		"The group may not be disabled.",	"The group may not be disabled."	},
	{	ERROR_NO_LOGON_SERVERS,			"ERROR_NO_LOGON_SERVERS",
		"There are currently no logon servers available to service the logon request.",	"There are currently no logon servers available to service the logon request."	},
	{	ERROR_NO_SUCH_LOGON_SESSION,			"ERROR_NO_SUCH_LOGON_SESSION",
		"A specified logon session does not exist. It may already have been terminated.",	"A specified logon session does not exist. It may already have been terminated."	},
	{	ERROR_NO_SUCH_PRIVILEGE,			"ERROR_NO_SUCH_PRIVILEGE",
		"A specified privilege does not exist.",	"A specified privilege does not exist."	},
	{	ERROR_PRIVILEGE_NOT_HELD,			"ERROR_PRIVILEGE_NOT_HELD",
		"A required privilege is not held by the client.",	"A required privilege is not held by the client."	},
	{	ERROR_INVALID_ACCOUNT_NAME,			"ERROR_INVALID_ACCOUNT_NAME",
		"The name provided is not a properly formed account name.",	"The name provided is not a properly formed account name."	},
	{	ERROR_USER_EXISTS,			"ERROR_USER_EXISTS",
		"The specified user already exists.",	"The specified user already exists."	},
	{	ERROR_NO_SUCH_USER,			"ERROR_NO_SUCH_USER",
		"The specified user does not exist.",	"The specified user does not exist."	},
	{	ERROR_GROUP_EXISTS,			"ERROR_GROUP_EXISTS",
		"The specified group already exists.",	"The specified group already exists."	},
	{	ERROR_NO_SUCH_GROUP,			"ERROR_NO_SUCH_GROUP",
		"The specified group does not exist.",	"The specified group does not exist."	},
	{	ERROR_MEMBER_IN_GROUP,			"ERROR_MEMBER_IN_GROUP",
		"Either the specified user account is already a member of the specified group, or the specified group cannot be deleted because it contains a member.",	"Either the specified user account is already a member of the specified group, or the specified group cannot be deleted because it contains a member."	},
	{	ERROR_MEMBER_NOT_IN_GROUP,			"ERROR_MEMBER_NOT_IN_GROUP",
		"The specified user account is not a member of the specified group account.",	"The specified user account is not a member of the specified group account."	},
	{	ERROR_LAST_ADMIN,			"ERROR_LAST_ADMIN",
		"The last remaining administration account cannot be disabled or deleted.",	"The last remaining administration account cannot be disabled or deleted."	},
	{	ERROR_WRONG_PASSWORD,			"ERROR_WRONG_PASSWORD",
		"Unable to update the password. The value provided as the current password is incorrect.",	"Unable to update the password. The value provided as the current password is incorrect."	},
	{	ERROR_ILL_FORMED_PASSWORD,			"ERROR_ILL_FORMED_PASSWORD",
		"Unable to update the password. The value provided for the new password contains values that are not allowed in passwords.",	"Unable to update the password. The value provided for the new password contains values that are not allowed in passwords."	},
	{	ERROR_PASSWORD_RESTRICTION,			"ERROR_PASSWORD_RESTRICTION",
		"Unable to update the password because a password update rule has been violated.",	"Unable to update the password because a password update rule has been violated."	},
	{	ERROR_LOGON_FAILURE,			"ERROR_LOGON_FAILURE",
		"Logon failure: unknown user name or bad password.",	"Logon failure: unknown user name or bad password."	},
	{	ERROR_ACCOUNT_RESTRICTION,			"ERROR_ACCOUNT_RESTRICTION",
		"Logon failure: user account restriction.",	"Logon failure: user account restriction."	},
	{	ERROR_INVALID_LOGON_HOURS,			"ERROR_INVALID_LOGON_HOURS",
		"Logon failure: account logon time restriction violation.",	"Logon failure: account logon time restriction violation."	},
	{	ERROR_INVALID_WORKSTATION,			"ERROR_INVALID_WORKSTATION",
		"Logon failure: user not allowed to log on to this computer.",	"Logon failure: user not allowed to log on to this computer."	},
	{	ERROR_PASSWORD_EXPIRED,			"ERROR_PASSWORD_EXPIRED",
		"Logon failure: the specified account password has expired.",	"Logon failure: the specified account password has expired."	},
	{	ERROR_ACCOUNT_DISABLED,			"ERROR_ACCOUNT_DISABLED",
		"Logon failure: account currently disabled.",	"Logon failure: account currently disabled."	},
	{	ERROR_NONE_MAPPED,			"ERROR_NONE_MAPPED",
		"No mapping between account names and security IDs was done.",	"No mapping between account names and security IDs was done."	},
	{	ERROR_TOO_MANY_LUIDS_REQUESTED,			"ERROR_TOO_MANY_LUIDS_REQUESTED",
		"Too many local user identifiers (LUIDs) were requested at one time.",	"Too many local user identifiers (LUIDs) were requested at one time."	},
	{	ERROR_LUIDS_EXHAUSTED,			"ERROR_LUIDS_EXHAUSTED",
		"No more local user identifiers (LUIDs) are available.",	"No more local user identifiers (LUIDs) are available."	},
	{	ERROR_INVALID_SUB_AUTHORITY,			"ERROR_INVALID_SUB_AUTHORITY",
		"The subauthority part of a security ID is invalid for this particular use.",	"The subauthority part of a security ID is invalid for this particular use."	},
	{	ERROR_INVALID_ACL,			"ERROR_INVALID_ACL",
		"The access control list (ACL) structure is invalid.",	"The access control list (ACL) structure is invalid."	},
	{	ERROR_INVALID_SID,			"ERROR_INVALID_SID",
		"The security ID structure is invalid.",	"The security ID structure is invalid."	},
	{	ERROR_INVALID_SECURITY_DESCR,			"ERROR_INVALID_SECURITY_DESCR",
		"The security descriptor structure is invalid.",	"The security descriptor structure is invalid."	},
	{	ERROR_BAD_INHERITANCE_ACL,			"ERROR_BAD_INHERITANCE_ACL",
		"The inherited access control list (ACL) or access control entry (ACE) could not be built.",	"The inherited access control list (ACL) or access control entry (ACE) could not be built."	},
	{	ERROR_SERVER_DISABLED,			"ERROR_SERVER_DISABLED",
		"The server is currently disabled.",	"The server is currently disabled."	},
	{	ERROR_SERVER_NOT_DISABLED,			"ERROR_SERVER_NOT_DISABLED",
		"The server is currently enabled.",	"The server is currently enabled."	},
	{	ERROR_INVALID_ID_AUTHORITY,			"ERROR_INVALID_ID_AUTHORITY",
		"The value provided was an invalid value for an identifier authority.",	"The value provided was an invalid value for an identifier authority."	},
	{	ERROR_ALLOTTED_SPACE_EXCEEDED,			"ERROR_ALLOTTED_SPACE_EXCEEDED",
		"No more memory is available for security information updates.",	"No more memory is available for security information updates."	},
	{	ERROR_INVALID_GROUP_ATTRIBUTES,			"ERROR_INVALID_GROUP_ATTRIBUTES",
		"The specified attributes are invalid, or incompatible with the attributes for the group as a whole.",	"The specified attributes are invalid, or incompatible with the attributes for the group as a whole."	},
	{	ERROR_BAD_IMPERSONATION_LEVEL,			"ERROR_BAD_IMPERSONATION_LEVEL",
		"Either a required impersonation level was not provided, or the provided impersonation level is invalid.",	"Either a required impersonation level was not provided, or the provided impersonation level is invalid."	},
	{	ERROR_CANT_OPEN_ANONYMOUS,			"ERROR_CANT_OPEN_ANONYMOUS",
		"Cannot open an anonymous level security token.",	"Cannot open an anonymous level security token."	},
	{	ERROR_BAD_VALIDATION_CLASS,			"ERROR_BAD_VALIDATION_CLASS",
		"The validation information class requested was invalid.",	"The validation information class requested was invalid."	},
	{	ERROR_BAD_TOKEN_TYPE,			"ERROR_BAD_TOKEN_TYPE",
		"The type of the token is inappropriate for its attempted use.",	"The type of the token is inappropriate for its attempted use."	},
	{	ERROR_NO_SECURITY_ON_OBJECT,			"ERROR_NO_SECURITY_ON_OBJECT",
		"Unable to perform a security operation on an object that has no associated security.",	"Unable to perform a security operation on an object which has no associated security."	},
	{	ERROR_CANT_ACCESS_DOMAIN_INFO,			"ERROR_CANT_ACCESS_DOMAIN_INFO",
		"Indicates a Windows NT Server could not be contacted or that objects within the domain are protected such that necessary information could not be retrieved.",	"Indicates a Windows NT Server could not be contacted or that objects within the domain are protected such that necessary information could not be retrieved."	},
	{	ERROR_INVALID_SERVER_STATE,			"ERROR_INVALID_SERVER_STATE",
		"The security account manager (SAM) or local security authority (LSA) server was in the wrong state to perform the security operation.",	"The security account manager (SAM) or local security authority (LSA) server was in the wrong state to perform the security operation."	},
	{	ERROR_INVALID_DOMAIN_STATE,			"ERROR_INVALID_DOMAIN_STATE",
		"The domain was in the wrong state to perform the security operation.",	"The domain was in the wrong state to perform the security operation."	},
	{	ERROR_INVALID_DOMAIN_ROLE,			"ERROR_INVALID_DOMAIN_ROLE",
		"This operation is only allowed for the Primary Domain Controller of the domain.",	"This operation is only allowed for the Primary Domain Controller of the domain."	},
	{	ERROR_NO_SUCH_DOMAIN,			"ERROR_NO_SUCH_DOMAIN",
		"The specified domain did not exist.",	"The specified domain did not exist."	},
	{	ERROR_DOMAIN_EXISTS,			"ERROR_DOMAIN_EXISTS",
		"The specified domain already exists.",	"The specified domain already exists."	},
	{	ERROR_DOMAIN_LIMIT_EXCEEDED,			"ERROR_DOMAIN_LIMIT_EXCEEDED",
		"An attempt was made to exceed the limit on the number of domains per server.",	"An attempt was made to exceed the limit on the number of domains per server."	},
	{	ERROR_INTERNAL_DB_CORRUPTION,			"ERROR_INTERNAL_DB_CORRUPTION",
		"Unable to complete the requested operation because of either a catastrophic media failure or a data structure corruption on the disk.",	"Unable to complete the requested operation because of either a catastrophic media failure or a data structure corruption on the disk."	},
	{	ERROR_INTERNAL_ERROR,			"ERROR_INTERNAL_ERROR",
		"The security account database contains an internal inconsistency.",	"The security account database contains an internal inconsistency."	},
	{	ERROR_GENERIC_NOT_MAPPED,			"ERROR_GENERIC_NOT_MAPPED",
		"Generic access types were contained in an access mask which should already be mapped to nongeneric types.",	"Generic access types were contained in an access mask which should already be mapped to non-generic types."	},
	{	ERROR_BAD_DESCRIPTOR_FORMAT,			"ERROR_BAD_DESCRIPTOR_FORMAT",
		"A security descriptor is not in the right format (absolute or self-relative).",	"A security descriptor is not in the right format (absolute or self-relative)."	},
	{	ERROR_NOT_LOGON_PROCESS,			"ERROR_NOT_LOGON_PROCESS",
		"The requested action is restricted for use by logon processes only. The calling process has not registered as a logon process.",	"The requested action is restricted for use by logon processes only. The calling process has not registered as a logon process."	},
	{	ERROR_LOGON_SESSION_EXISTS,			"ERROR_LOGON_SESSION_EXISTS",
		"Cannot start a new logon session with an ID that is already in use.",	"Cannot start a new logon session with an ID that is already in use."	},
	{	ERROR_NO_SUCH_PACKAGE,			"ERROR_NO_SUCH_PACKAGE",
		"A specified authentication package is unknown.",	"A specified authentication package is unknown."	},
	{	ERROR_BAD_LOGON_SESSION_STATE,			"ERROR_BAD_LOGON_SESSION_STATE",
		"The logon session is not in a state that is consistent with the requested operation.",	"The logon session is not in a state that is consistent with the requested operation."	},
	{	ERROR_LOGON_SESSION_COLLISION,			"ERROR_LOGON_SESSION_COLLISION",
		"The logon session ID is already in use.",	"The logon session ID is already in use."	},
	{	ERROR_INVALID_LOGON_TYPE,			"ERROR_INVALID_LOGON_TYPE",
		"A logon request contained an invalid logon type value.",	"A logon request contained an invalid logon type value."	},
	{	ERROR_CANNOT_IMPERSONATE,			"ERROR_CANNOT_IMPERSONATE",
		"Unable to impersonate using a named pipe until data has been read from that pipe.",	"Unable to impersonate via a named pipe until data has been read from that pipe."	},
	{	ERROR_RXACT_INVALID_STATE,			"ERROR_RXACT_INVALID_STATE",
		"The transaction state of a registry subtree is incompatible with the requested operation.",	"The transaction state of a Registry subtree is incompatible with the requested operation."	},
	{	ERROR_RXACT_COMMIT_FAILURE,			"ERROR_RXACT_COMMIT_FAILURE",
		"An internal security database corruption has been encountered.",	"An internal security database corruption has been encountered."	},
	{	ERROR_SPECIAL_ACCOUNT,			"ERROR_SPECIAL_ACCOUNT",
		"Cannot perform this operation on built-in accounts.",	"Cannot perform this operation on built-in accounts."	},
	{	ERROR_SPECIAL_GROUP,			"ERROR_SPECIAL_GROUP",
		"Cannot perform this operation on this built-in special group.",	"Cannot perform this operation on this built-in special group."	},
	{	ERROR_SPECIAL_USER,			"ERROR_SPECIAL_USER",
		"Cannot perform this operation on this built-in special user.",	"Cannot perform this operation on this built-in special user."	},
	{	ERROR_MEMBERS_PRIMARY_GROUP,			"ERROR_MEMBERS_PRIMARY_GROUP",
		"The user cannot be removed from a group because the group is currently the user's primary group.",	"The user cannot be removed from a group because the group is currently the user's primary group."	},
	{	ERROR_TOKEN_ALREADY_IN_USE,			"ERROR_TOKEN_ALREADY_IN_USE",
		"The token is already in use as a primary token.",	"The token is already in use as a primary token."	},
	{	ERROR_NO_SUCH_ALIAS,			"ERROR_NO_SUCH_ALIAS",
		"The specified local group does not exist.",	"The specified local group does not exist."	},
	{	ERROR_MEMBER_NOT_IN_ALIAS,			"ERROR_MEMBER_NOT_IN_ALIAS",
		"The specified account name is not a member of the local group.",	"The specified account name is not a member of the local group."	},
	{	ERROR_MEMBER_IN_ALIAS,			"ERROR_MEMBER_IN_ALIAS",
		"The specified account name is already a member of the local group.",	"The specified account name is already a member of the local group."	},
	{	ERROR_ALIAS_EXISTS,			"ERROR_ALIAS_EXISTS",
		"The specified local group already exists.",	"The specified local group already exists."	},
	{	ERROR_LOGON_NOT_GRANTED,			"ERROR_LOGON_NOT_GRANTED",
		"Logon failure: the user has not been granted the requested logon type at this computer.",	"Logon failure: the user has not been granted the requested logon type at this computer."	},
	{	ERROR_TOO_MANY_SECRETS,			"ERROR_TOO_MANY_SECRETS",
		"The maximum number of secrets that may be stored in a single system has been exceeded.",	"The maximum number of secrets that may be stored in a single system has been exceeded."	},
	{	ERROR_SECRET_TOO_LONG,			"ERROR_SECRET_TOO_LONG",
		"The length of a secret exceeds the maximum length allowed.",	"The length of a secret exceeds the maximum length allowed."	},
	{	ERROR_INTERNAL_DB_ERROR,			"ERROR_INTERNAL_DB_ERROR",
		"The local security authority database contains an internal inconsistency.",	"The local security authority database contains an internal inconsistency."	},
	{	ERROR_TOO_MANY_CONTEXT_IDS,			"ERROR_TOO_MANY_CONTEXT_IDS",
		"During a logon attempt, the user's security context accumulated too many security IDs.",	"During a logon attempt, the user's security context accumulated too many security IDs."	},
	{	ERROR_LOGON_TYPE_NOT_GRANTED,			"ERROR_LOGON_TYPE_NOT_GRANTED",
		"Logon failure: the user has not been granted the requested logon type at this computer.",	"Logon failure: the user has not been granted the requested logon type at this computer."	},
	{	ERROR_NT_CROSS_ENCRYPTION_REQUIRED,			"ERROR_NT_CROSS_ENCRYPTION_REQUIRED",
		"A cross-encrypted password is necessary to change a user password.",	"A cross-encrypted password is necessary to change a user password."	},
	{	ERROR_NO_SUCH_MEMBER,			"ERROR_NO_SUCH_MEMBER",
		"A new member could not be added to a local group because the member does not exist.",	"A new member could not be added to a local group because the member does not exist."	},
	{	ERROR_INVALID_MEMBER,			"ERROR_INVALID_MEMBER",
		"A new member could not be added to a local group because the member has the wrong account type.",	"A new member could not be added to a local group because the member has the wrong account type."	},
	{	ERROR_TOO_MANY_SIDS,			"ERROR_TOO_MANY_SIDS",
		"Too many security IDs have been specified.",	"Too many security IDs have been specified."	},
	{	ERROR_LM_CROSS_ENCRYPTION_REQUIRED,			"ERROR_LM_CROSS_ENCRYPTION_REQUIRED",
		"A cross-encrypted password is necessary to change this user password.",	"A cross-encrypted password is necessary to change this user password."	},
	{	ERROR_NO_INHERITANCE,			"ERROR_NO_INHERITANCE",
		"Indicates an ACL contains no inheritable components.",	"Indicates an ACL contains no inheritable components"	},
	{	ERROR_FILE_CORRUPT,			"ERROR_FILE_CORRUPT",
		"The file or directory is corrupted and unreadable.",	"The file or directory is corrupt and non-readable."	},
	{	ERROR_DISK_CORRUPT,			"ERROR_DISK_CORRUPT",
		"The disk structure is corrupted and unreadable.",	"The disk structure is corrupt and non-readable."	},
	{	ERROR_NO_USER_SESSION_KEY,			"ERROR_NO_USER_SESSION_KEY",
		"There is no user session key for the specified logon session.",	"There is no user session key for the specified logon session."	},
	{	ERROR_LICENSE_QUOTA_EXCEEDED,			"ERROR_LICENSE_QUOTA_EXCEEDED",
		"The service being accessed is licensed for a particular number of connections. No more connections can be made to the service at this time because there are already as many connections as the service can accept.",	"The service being accessed is licensed for a particular number of connections. No more connections can be made to the service at this time because there are already as many connections as the service can accept."	},
	{	ERROR_INVALID_WINDOW_HANDLE,			"ERROR_INVALID_WINDOW_HANDLE",
		"Invalid window handle.",	"Invalid window handle."	},
	{	ERROR_INVALID_MENU_HANDLE,			"ERROR_INVALID_MENU_HANDLE",
		"Invalid menu handle.",	"Invalid menu handle."	},
	{	ERROR_INVALID_CURSOR_HANDLE,			"ERROR_INVALID_CURSOR_HANDLE",
		"Invalid cursor handle.",	"Invalid cursor handle."	},
	{	ERROR_INVALID_ACCEL_HANDLE,			"ERROR_INVALID_ACCEL_HANDLE",
		"Invalid accelerator table handle.",	"Invalid accelerator table handle."	},
	{	ERROR_INVALID_HOOK_HANDLE,			"ERROR_INVALID_HOOK_HANDLE",
		"Invalid hook handle.",	"Invalid hook handle."	},
	{	ERROR_INVALID_DWP_HANDLE,			"ERROR_INVALID_DWP_HANDLE",
		"Invalid handle to a multiple-window position structure.",	"Invalid handle to a multiple-window position structure."	},
	{	ERROR_TLW_WITH_WSCHILD,			"ERROR_TLW_WITH_WSCHILD",
		"Cannot create a top-level child window.",	"Cannot create a top-level child window."	},
	{	ERROR_CANNOT_FIND_WND_CLASS,			"ERROR_CANNOT_FIND_WND_CLASS",
		"Cannot find window class.",	"Cannot find window class."	},
	{	ERROR_WINDOW_OF_OTHER_THREAD,			"ERROR_WINDOW_OF_OTHER_THREAD",
		"Invalid window; it belongs to other thread.",	"Invalid window, belongs to other thread."	},
	{	ERROR_HOTKEY_ALREADY_REGISTERED,			"ERROR_HOTKEY_ALREADY_REGISTERED",
		"Hot key is already registered.",	"Hot key is already registered."	},
	{	ERROR_CLASS_ALREADY_EXISTS,			"ERROR_CLASS_ALREADY_EXISTS",
		"Class already exists.",	"Class already exists."	},
	{	ERROR_CLASS_DOES_NOT_EXIST,			"ERROR_CLASS_DOES_NOT_EXIST",
		"Class does not exist.",	"Class does not exist."	},
	{	ERROR_CLASS_HAS_WINDOWS,			"ERROR_CLASS_HAS_WINDOWS",
		"Class still has open windows.",	"Class still has open windows."	},
	{	ERROR_INVALID_INDEX,			"ERROR_INVALID_INDEX",
		"Invalid index.",	"Invalid index."	},
	{	ERROR_INVALID_ICON_HANDLE,			"ERROR_INVALID_ICON_HANDLE",
		"Invalid icon handle.",	"Invalid icon handle."	},
	{	ERROR_PRIVATE_DIALOG_INDEX,			"ERROR_PRIVATE_DIALOG_INDEX",
		"Using private DIALOG window words.",	"Using private DIALOG window words."	},
	{	ERROR_LISTBOX_ID_NOT_FOUND,			"ERROR_LISTBOX_ID_NOT_FOUND",
		"The list box identifier was not found.",	"The listbox identifier was not found."	},
	{	ERROR_NO_WILDCARD_CHARACTERS,			"ERROR_NO_WILDCARD_CHARACTERS",
		"No wildcards were found.",	"No wildcards were found."	},
	{	ERROR_CLIPBOARD_NOT_OPEN,			"ERROR_CLIPBOARD_NOT_OPEN",
		"Thread does not have a clipboard open.",	"Thread does not have a clipboard open."	},
	{	ERROR_HOTKEY_NOT_REGISTERED,			"ERROR_HOTKEY_NOT_REGISTERED",
		"Hot key is not registered.",	"Hot key is not registered."	},
	{	ERROR_WINDOW_NOT_DIALOG,			"ERROR_WINDOW_NOT_DIALOG",
		"The window is not a valid dialog window.",	"The window is not a valid dialog window."	},
	{	ERROR_CONTROL_ID_NOT_FOUND,			"ERROR_CONTROL_ID_NOT_FOUND",
		"Control ID not found.",	"Control ID not found."	},
	{	ERROR_INVALID_COMBOBOX_MESSAGE,			"ERROR_INVALID_COMBOBOX_MESSAGE",
		"Invalid message for a combo box because it does not have an edit control.",	"Invalid message for a combo box because it does not have an edit control."	},
	{	ERROR_WINDOW_NOT_COMBOBOX,			"ERROR_WINDOW_NOT_COMBOBOX",
		"The window is not a combo box.",	"The window is not a combo box."	},
	{	ERROR_INVALID_EDIT_HEIGHT,			"ERROR_INVALID_EDIT_HEIGHT",
		"Height must be less than 256.",	"Height must be less than 256."	},
	{	ERROR_DC_NOT_FOUND,			"ERROR_DC_NOT_FOUND",
		"Invalid device context (DC) handle.",	"Invalid device context (DC) handle."	},
	{	ERROR_INVALID_HOOK_FILTER,			"ERROR_INVALID_HOOK_FILTER",
		"Invalid hook procedure type.",	"Invalid hook procedure type."	},
	{	ERROR_INVALID_FILTER_PROC,			"ERROR_INVALID_FILTER_PROC",
		"Invalid hook procedure.",	"Invalid hook procedure."	},
	{	ERROR_HOOK_NEEDS_HMOD,			"ERROR_HOOK_NEEDS_HMOD",
		"Cannot set nonlocal hook without a module handle.",	"Cannot set non-local hook without a module handle."	},
	{	ERROR_GLOBAL_ONLY_HOOK,			"ERROR_GLOBAL_ONLY_HOOK",
		"This hook procedure can only be set globally.",	"This hook procedure can only be set globally."	},
	{	ERROR_JOURNAL_HOOK_SET,			"ERROR_JOURNAL_HOOK_SET",
		"The journal hook procedure is already installed.",	"The journal hook procedure is already installed."	},
	{	ERROR_HOOK_NOT_INSTALLED,			"ERROR_HOOK_NOT_INSTALLED",
		"The hook procedure is not installed.",	"The hook procedure is not installed."	},
	{	ERROR_INVALID_LB_MESSAGE,			"ERROR_INVALID_LB_MESSAGE",
		"Invalid message for single-selection list box.",	"Invalid message for single-selection listbox."	},
	{	ERROR_SETCOUNT_ON_BAD_LB,			"ERROR_SETCOUNT_ON_BAD_LB",
		"LB_SETCOUNT sent to non-lazy list box.",	"LB_SETCOUNT sent to non-lazy listbox."	},
	{	ERROR_LB_WITHOUT_TABSTOPS,			"ERROR_LB_WITHOUT_TABSTOPS",
		"This list box does not support tab stops.",	"This list box does not support tab stops."	},
	{	ERROR_DESTROY_OBJECT_OF_OTHER_THREAD,			"ERROR_DESTROY_OBJECT_OF_OTHER_THREAD",
		"Cannot destroy object created by another thread.",	"Cannot destroy object created by another thread."	},
	{	ERROR_CHILD_WINDOW_MENU,			"ERROR_CHILD_WINDOW_MENU",
		"Child windows cannot have menus.",	"Child windows cannot have menus."	},
	{	ERROR_NO_SYSTEM_MENU,			"ERROR_NO_SYSTEM_MENU",
		"The window does not have a system menu.",	"The window does not have a system menu."	},
	{	ERROR_INVALID_MSGBOX_STYLE,			"ERROR_INVALID_MSGBOX_STYLE",
		"Invalid message box style.",	"Invalid message box style."	},
	{	ERROR_INVALID_SPI_VALUE,			"ERROR_INVALID_SPI_VALUE",
		"Invalid system-wide (SPI_*) parameter.",	"Invalid system-wide (SPI_*) parameter."	},
	{	ERROR_SCREEN_ALREADY_LOCKED,			"ERROR_SCREEN_ALREADY_LOCKED",
		"Screen already locked.",	"Screen already locked."	},
	{	ERROR_HWNDS_HAVE_DIFF_PARENT,			"ERROR_HWNDS_HAVE_DIFF_PARENT",
		"All handles to windows in a multiple-window position structure must have the same parent.",	"All handles to windows in a multiple-window position structure must have the same parent."	},
	{	ERROR_NOT_CHILD_WINDOW,			"ERROR_NOT_CHILD_WINDOW",
		"The window is not a child window.",	"The window is not a child window."	},
	{	ERROR_INVALID_GW_COMMAND,			"ERROR_INVALID_GW_COMMAND",
		"Invalid GW_* command.",	"Invalid GW_* command."	},
	{	ERROR_INVALID_THREAD_ID,			"ERROR_INVALID_THREAD_ID",
		"Invalid thread identifier.",	"Invalid thread identifier."	},
	{	ERROR_NON_MDICHILD_WINDOW,			"ERROR_NON_MDICHILD_WINDOW",
		"Cannot process a message from a window that is not a multiple document interface (MDI) window.",	"Cannot process a message from a window that is not a multiple document interface (MDI) window."	},
	{	ERROR_POPUP_ALREADY_ACTIVE,			"ERROR_POPUP_ALREADY_ACTIVE",
		"Popup menu already active.",	"Popup menu already active."	},
	{	ERROR_NO_SCROLLBARS,			"ERROR_NO_SCROLLBARS",
		"The window does not have scroll bars.",	"The window does not have scroll bars."	},
	{	ERROR_INVALID_SCROLLBAR_RANGE,			"ERROR_INVALID_SCROLLBAR_RANGE",
		"Scroll bar range cannot be greater than 0x7FFF.",	"Scroll bar range cannot be greater than 0x7FFF."	},
	{	ERROR_INVALID_SHOWWIN_COMMAND,			"ERROR_INVALID_SHOWWIN_COMMAND",
		"Cannot show or remove the window in the way specified.",	"Cannot show or remove the window in the way specified."	},
	{	ERROR_NO_SYSTEM_RESOURCES,			"ERROR_NO_SYSTEM_RESOURCES",
		"Insufficient system resources exist to complete the requested service.",	"Insufficient system resources exist to complete the requested service."	},
	{	ERROR_NONPAGED_SYSTEM_RESOURCES,			"ERROR_NONPAGED_SYSTEM_RESOURCES",
		"Insufficient system resources exist to complete the requested service.",	"Insufficient system resources exist to complete the requested service."	},
	{	ERROR_PAGED_SYSTEM_RESOURCES,			"ERROR_PAGED_SYSTEM_RESOURCES",
		"Insufficient system resources exist to complete the requested service.",	"Insufficient system resources exist to complete the requested service."	},
	{	ERROR_WORKING_SET_QUOTA,			"ERROR_WORKING_SET_QUOTA",
		"Insufficient quota to complete the requested service.",	"Insufficient quota to complete the requested service."	},
	{	ERROR_PAGEFILE_QUOTA,			"ERROR_PAGEFILE_QUOTA",
		"Insufficient quota to complete the requested service.",	"Insufficient quota to complete the requested service."	},
	{	ERROR_COMMITMENT_LIMIT,			"ERROR_COMMITMENT_LIMIT",
		"The paging file is too small for this operation to complete.",	"The paging file is too small for this operation to complete."	},
	{	ERROR_MENU_ITEM_NOT_FOUND,			"ERROR_MENU_ITEM_NOT_FOUND",
		"A menu item was not found.",	"A menu item was not found."	},
	{	ERROR_INVALID_KEYBOARD_HANDLE,			"ERROR_INVALID_KEYBOARD_HANDLE",
		"Invalid keyboard layout handle.",	"Invalid keyboard layout handle."	},
	{	ERROR_HOOK_TYPE_NOT_ALLOWED,			"ERROR_HOOK_TYPE_NOT_ALLOWED",
		"Hook type not allowed.",	"Hook type not allowed."	},
	{	ERROR_REQUIRES_INTERACTIVE_WINDOWSTATION,			"ERROR_REQUIRES_INTERACTIVE_WINDOWSTATION",
		"This operation requires an interactive window station.",	"This operation requires an interactive windowstation."	},
	{	ERROR_TIMEOUT,			"ERROR_TIMEOUT",
		"This operation returned because the timeout period expired.",	"This operation returned because the timeout period expired."	},
	{	ERROR_INVALID_MONITOR_HANDLE,			"ERROR_INVALID_MONITOR_HANDLE",
		"Invalid monitor handle.",	"Invalid monitor handle."	},
	{	ERROR_EVENTLOG_FILE_CORRUPT,			"ERROR_EVENTLOG_FILE_CORRUPT",
		"The event log file is corrupted.",	"The event log file is corrupt."	},
	{	ERROR_EVENTLOG_CANT_START,			"ERROR_EVENTLOG_CANT_START",
		"No event log file could be opened, so the event logging service did not start.",	"No event log file could be opened, so the event logging service did not start."	},
	{	ERROR_LOG_FILE_FULL,			"ERROR_LOG_FILE_FULL",
		"The event log file is full.",	"The event log file is full."	},
	{	ERROR_EVENTLOG_FILE_CHANGED,			"ERROR_EVENTLOG_FILE_CHANGED",
		"The event log file has changed between read operations.",	"The event log file has changed between reads."	},
# ifdef ERROR_INSTALL_SERVICE
	{	ERROR_INSTALL_SERVICE,			"ERROR_INSTALL_SERVICE",
		"Failure accessing install service.",	"Failure accessing install service."	},
# endif /* # ifdef ERROR_INSTALL_SERVICE */
	{	ERROR_INSTALL_USEREXIT,			"ERROR_INSTALL_USEREXIT",
		"The user canceled the installation.",	"The user canceled the installation."	},
	{	ERROR_INSTALL_FAILURE,			"ERROR_INSTALL_FAILURE",
		"Fatal error during installation.",	"Fatal error during installation."	},
	{	ERROR_INSTALL_SUSPEND,			"ERROR_INSTALL_SUSPEND",
		"Installation suspended, incomplete.",	"Installation suspended, incomplete."	},
	{	ERROR_UNKNOWN_PRODUCT,			"ERROR_UNKNOWN_PRODUCT",
		"Product code not registered.",	"Product code not registered."	},
	{	ERROR_UNKNOWN_FEATURE,			"ERROR_UNKNOWN_FEATURE",
		"Feature ID not registered.",	"Feature ID not registered."	},
	{	ERROR_UNKNOWN_COMPONENT,			"ERROR_UNKNOWN_COMPONENT",
		"Component ID not registered.",	"Component ID not registered."	},
	{	ERROR_UNKNOWN_PROPERTY,			"ERROR_UNKNOWN_PROPERTY",
		"Unknown property.",	"Unknown property."	},
	{	ERROR_INVALID_HANDLE_STATE,			"ERROR_INVALID_HANDLE_STATE",
		"Handle is in an invalid state.",	"Handle is in an invalid state."	},
	{	ERROR_BAD_CONFIGURATION,			"ERROR_BAD_CONFIGURATION",
		"Configuration data corrupt.",	"Configuration data corrupt."	},
	{	ERROR_INDEX_ABSENT,			"ERROR_INDEX_ABSENT",
		"Language not available.",	"Language not available."	},
	{	ERROR_INSTALL_SOURCE_ABSENT,			"ERROR_INSTALL_SOURCE_ABSENT",
		"Install source unavailable.",	"Install source unavailable."	},
# ifdef ERROR_BAD_DATABASE_VERSION
	{	ERROR_BAD_DATABASE_VERSION,			"ERROR_BAD_DATABASE_VERSION",
		"Database version unsupported.",	"Database version unsupported."	},
# endif /* # ifdef ERROR_BAD_DATABASE_VERSION */
	{	ERROR_PRODUCT_UNINSTALLED,			"ERROR_PRODUCT_UNINSTALLED",
		"Product is uninstalled.",	"Product is uninstalled."	},
	{	ERROR_BAD_QUERY_SYNTAX,			"ERROR_BAD_QUERY_SYNTAX",
		"SQL query syntax invalid or unsupported.",	"SQL query syntax invalid or unsupported."	},
	{	ERROR_INVALID_FIELD,			"ERROR_INVALID_FIELD",
		"Record field does not exist.",	"Record field does not exist."	},
	{	RPC_S_INVALID_STRING_BINDING,			"RPC_S_INVALID_STRING_BINDING",
		"The string binding is invalid.",	"The string binding is invalid."	},
	{	RPC_S_WRONG_KIND_OF_BINDING,			"RPC_S_WRONG_KIND_OF_BINDING",
		"The binding handle is not the correct type.",	"The binding handle is not the correct type."	},
	{	RPC_S_INVALID_BINDING,			"RPC_S_INVALID_BINDING",
		"The binding handle is invalid.",	"The binding handle is invalid."	},
	{	RPC_S_PROTSEQ_NOT_SUPPORTED,			"RPC_S_PROTSEQ_NOT_SUPPORTED",
		"The RPC protocol sequence is not supported.",	"The RPC protocol sequence is not supported."	},
	{	RPC_S_INVALID_RPC_PROTSEQ,			"RPC_S_INVALID_RPC_PROTSEQ",
		"The RPC protocol sequence is invalid.",	"The RPC protocol sequence is invalid."	},
	{	RPC_S_INVALID_STRING_UUID,			"RPC_S_INVALID_STRING_UUID",
		"The string universal unique identifier (UUID) is invalid.",	"The string universal unique identifier (UUID) is invalid."	},
	{	RPC_S_INVALID_ENDPOINT_FORMAT,			"RPC_S_INVALID_ENDPOINT_FORMAT",
		"The endpoint format is invalid.",	"The endpoint format is invalid."	},
	{	RPC_S_INVALID_NET_ADDR,			"RPC_S_INVALID_NET_ADDR",
		"The network address is invalid.",	"The network address is invalid."	},
	{	RPC_S_NO_ENDPOINT_FOUND,			"RPC_S_NO_ENDPOINT_FOUND",
		"No endpoint was found.",	"No endpoint was found."	},
	{	RPC_S_INVALID_TIMEOUT,			"RPC_S_INVALID_TIMEOUT",
		"The timeout value is invalid.",	"The timeout value is invalid."	},
	{	RPC_S_OBJECT_NOT_FOUND,			"RPC_S_OBJECT_NOT_FOUND",
		"The object universal unique identifier (UUID) was not found.",	"The object universal unique identifier (UUID) was not found."	},
	{	RPC_S_ALREADY_REGISTERED,			"RPC_S_ALREADY_REGISTERED",
		"The object universal unique identifier (UUID) has already been registered.",	"The object universal unique identifier (UUID) has already been registered."	},
	{	RPC_S_TYPE_ALREADY_REGISTERED,			"RPC_S_TYPE_ALREADY_REGISTERED",
		"The type universal unique identifier (UUID) has already been registered.",	"The type universal unique identifier (UUID) has already been registered."	},
	{	RPC_S_ALREADY_LISTENING,			"RPC_S_ALREADY_LISTENING",
		"The RPC server is already listening.",	"The RPC server is already listening."	},
	{	RPC_S_NO_PROTSEQS_REGISTERED,			"RPC_S_NO_PROTSEQS_REGISTERED",
		"No protocol sequences have been registered.",	"No protocol sequences have been registered."	},
	{	RPC_S_NOT_LISTENING,			"RPC_S_NOT_LISTENING",
		"The RPC server is not listening.",	"The RPC server is not listening."	},
	{	RPC_S_UNKNOWN_MGR_TYPE,			"RPC_S_UNKNOWN_MGR_TYPE",
		"The manager type is unknown.",	"The manager type is unknown."	},
	{	RPC_S_UNKNOWN_IF,			"RPC_S_UNKNOWN_IF",
		"The interface is unknown.",	"The interface is unknown."	},
	{	RPC_S_NO_BINDINGS,			"RPC_S_NO_BINDINGS",
		"There are no bindings.",	"There are no bindings."	},
	{	RPC_S_NO_PROTSEQS,			"RPC_S_NO_PROTSEQS",
		"There are no protocol sequences.",	"There are no protocol sequences."	},
	{	RPC_S_CANT_CREATE_ENDPOINT,			"RPC_S_CANT_CREATE_ENDPOINT",
		"The endpoint cannot be created.",	"The endpoint cannot be created."	},
	{	RPC_S_OUT_OF_RESOURCES,			"RPC_S_OUT_OF_RESOURCES",
		"Not enough resources are available to complete this operation.",	"Not enough resources are available to complete this operation."	},
	{	RPC_S_SERVER_UNAVAILABLE,			"RPC_S_SERVER_UNAVAILABLE",
		"The RPC server is unavailable.",	"The RPC server is unavailable."	},
	{	RPC_S_SERVER_TOO_BUSY,			"RPC_S_SERVER_TOO_BUSY",
		"The RPC server is too busy to complete this operation.",	"The RPC server is too busy to complete this operation."	},
	{	RPC_S_INVALID_NETWORK_OPTIONS,			"RPC_S_INVALID_NETWORK_OPTIONS",
		"The network options are invalid.",	"The network options are invalid."	},
	{	RPC_S_NO_CALL_ACTIVE,			"RPC_S_NO_CALL_ACTIVE",
		"There are no remote procedure calls active on this thread.",	"There is not a remote procedure call active in this thread."	},
	{	RPC_S_CALL_FAILED,			"RPC_S_CALL_FAILED",
		"The remote procedure call failed.",	"The remote procedure call failed."	},
	{	RPC_S_CALL_FAILED_DNE,			"RPC_S_CALL_FAILED_DNE",
		"The remote procedure call failed and did not execute.",	"The remote procedure call failed and did not execute."	},
	{	RPC_S_PROTOCOL_ERROR,			"RPC_S_PROTOCOL_ERROR",
		"A remote procedure call (RPC) protocol error occurred.",	"A remote procedure call (RPC) protocol error occurred."	},
	{	RPC_S_UNSUPPORTED_TRANS_SYN,			"RPC_S_UNSUPPORTED_TRANS_SYN",
		"The transfer syntax is not supported by the RPC server.",	"The transfer syntax is not supported by the RPC server."	},
	{	RPC_S_UNSUPPORTED_TYPE,			"RPC_S_UNSUPPORTED_TYPE",
		"The universal unique identifier (UUID) type is not supported.",	"The universal unique identifier (UUID) type is not supported."	},
	{	RPC_S_INVALID_TAG,			"RPC_S_INVALID_TAG",
		"The tag is invalid.",	"The tag is invalid."	},
	{	RPC_S_INVALID_BOUND,			"RPC_S_INVALID_BOUND",
		"The array bounds are invalid.",	"The array bounds are invalid."	},
	{	RPC_S_NO_ENTRY_NAME,			"RPC_S_NO_ENTRY_NAME",
		"The binding does not contain an entry name.",	"The binding does not contain an entry name."	},
	{	RPC_S_INVALID_NAME_SYNTAX,			"RPC_S_INVALID_NAME_SYNTAX",
		"The name syntax is invalid.",	"The name syntax is invalid."	},
	{	RPC_S_UNSUPPORTED_NAME_SYNTAX,			"RPC_S_UNSUPPORTED_NAME_SYNTAX",
		"The name syntax is not supported.",	"The name syntax is not supported."	},
	{	RPC_S_UUID_NO_ADDRESS,			"RPC_S_UUID_NO_ADDRESS",
		"No network address is available to use to construct a universal unique identifier (UUID).",	"No network address is available to use to construct a universal unique identifier (UUID)."	},
	{	RPC_S_DUPLICATE_ENDPOINT,			"RPC_S_DUPLICATE_ENDPOINT",
		"The endpoint is a duplicate.",	"The endpoint is a duplicate."	},
	{	RPC_S_UNKNOWN_AUTHN_TYPE,			"RPC_S_UNKNOWN_AUTHN_TYPE",
		"The authentication type is unknown.",	"The authentication type is unknown."	},
	{	RPC_S_MAX_CALLS_TOO_SMALL,			"RPC_S_MAX_CALLS_TOO_SMALL",
		"The maximum number of calls is too small.",	"The maximum number of calls is too small."	},
	{	RPC_S_STRING_TOO_LONG,			"RPC_S_STRING_TOO_LONG",
		"The string is too long.",	"The string is too long."	},
	{	RPC_S_PROTSEQ_NOT_FOUND,			"RPC_S_PROTSEQ_NOT_FOUND",
		"The RPC protocol sequence was not found.",	"The RPC protocol sequence was not found."	},
	{	RPC_S_PROCNUM_OUT_OF_RANGE,			"RPC_S_PROCNUM_OUT_OF_RANGE",
		"The procedure number is out of range.",	"The procedure number is out of range."	},
	{	RPC_S_BINDING_HAS_NO_AUTH,			"RPC_S_BINDING_HAS_NO_AUTH",
		"The binding does not contain any authentication information.",	"The binding does not contain any authentication information."	},
	{	RPC_S_UNKNOWN_AUTHN_SERVICE,			"RPC_S_UNKNOWN_AUTHN_SERVICE",
		"The authentication service is unknown.",	"The authentication service is unknown."	},
	{	RPC_S_UNKNOWN_AUTHN_LEVEL,			"RPC_S_UNKNOWN_AUTHN_LEVEL",
		"The authentication level is unknown.",	"The authentication level is unknown."	},
	{	RPC_S_INVALID_AUTH_IDENTITY,			"RPC_S_INVALID_AUTH_IDENTITY",
		"The security context is invalid.",	"The security context is invalid."	},
	{	RPC_S_UNKNOWN_AUTHZ_SERVICE,			"RPC_S_UNKNOWN_AUTHZ_SERVICE",
		"The authorization service is unknown.",	"The authorization service is unknown."	},
	{	EPT_S_INVALID_ENTRY,			"EPT_S_INVALID_ENTRY",
		"The entry is invalid.",	"The entry is invalid."	},
	{	EPT_S_CANT_PERFORM_OP,			"EPT_S_CANT_PERFORM_OP",
		"The server endpoint cannot perform the operation.",	"The server endpoint cannot perform the operation."	},
	{	EPT_S_NOT_REGISTERED,			"EPT_S_NOT_REGISTERED",
		"There are no more endpoints available from the endpoint mapper.",	"There are no more endpoints available from the endpoint mapper."	},
	{	RPC_S_NOTHING_TO_EXPORT,			"RPC_S_NOTHING_TO_EXPORT",
		"No interfaces have been exported.",	"No interfaces have been exported."	},
	{	RPC_S_INCOMPLETE_NAME,			"RPC_S_INCOMPLETE_NAME",
		"The entry name is incomplete.",	"The entry name is incomplete."	},
	{	RPC_S_INVALID_VERS_OPTION,			"RPC_S_INVALID_VERS_OPTION",
		"The version option is invalid.",	"The version option is invalid."	},
	{	RPC_S_NO_MORE_MEMBERS,			"RPC_S_NO_MORE_MEMBERS",
		"There are no more members.",	"There are no more members."	},
	{	RPC_S_NOT_ALL_OBJS_UNEXPORTED,			"RPC_S_NOT_ALL_OBJS_UNEXPORTED",
		"There is nothing to unexport.",	"There is nothing to unexport."	},
	{	RPC_S_INTERFACE_NOT_FOUND,			"RPC_S_INTERFACE_NOT_FOUND",
		"The interface was not found.",	"The interface was not found."	},
	{	RPC_S_ENTRY_ALREADY_EXISTS,			"RPC_S_ENTRY_ALREADY_EXISTS",
		"The entry already exists.",	"The entry already exists."	},
	{	RPC_S_ENTRY_NOT_FOUND,			"RPC_S_ENTRY_NOT_FOUND",
		"The entry is not found.",	"The entry is not found."	},
	{	RPC_S_NAME_SERVICE_UNAVAILABLE,			"RPC_S_NAME_SERVICE_UNAVAILABLE",
		"The name service is unavailable.",	"The name service is unavailable."	},
	{	RPC_S_INVALID_NAF_ID,			"RPC_S_INVALID_NAF_ID",
		"The network address family is invalid.",	"The network address family is invalid."	},
	{	RPC_S_CANNOT_SUPPORT,			"RPC_S_CANNOT_SUPPORT",
		"The requested operation is not supported.",	"The requested operation is not supported."	},
	{	RPC_S_NO_CONTEXT_AVAILABLE,			"RPC_S_NO_CONTEXT_AVAILABLE",
		"No security context is available to allow impersonation.",	"No security context is available to allow impersonation."	},
	{	RPC_S_INTERNAL_ERROR,			"RPC_S_INTERNAL_ERROR",
		"An internal error occurred in a remote procedure call (RPC).",	"An internal error occurred in a remote procedure call (RPC)."	},
	{	RPC_S_ZERO_DIVIDE,			"RPC_S_ZERO_DIVIDE",
		"The RPC server attempted an integer division by zero.",	"The RPC server attempted an integer division by zero."	},
	{	RPC_S_ADDRESS_ERROR,			"RPC_S_ADDRESS_ERROR",
		"An addressing error occurred in the RPC server.",	"An addressing error occurred in the RPC server."	},
	{	RPC_S_FP_DIV_ZERO,			"RPC_S_FP_DIV_ZERO",
		"A floating-point operation at the RPC server caused a division by zero.",	"A floating-point operation at the RPC server caused a division by zero."	},
	{	RPC_S_FP_UNDERFLOW,			"RPC_S_FP_UNDERFLOW",
		"A floating-point underflow occurred at the RPC server.",	"A floating-point underflow occurred at the RPC server."	},
	{	RPC_S_FP_OVERFLOW,			"RPC_S_FP_OVERFLOW",
		"A floating-point overflow occurred at the RPC server.",	"A floating-point overflow occurred at the RPC server."	},
	{	RPC_X_NO_MORE_ENTRIES,			"RPC_X_NO_MORE_ENTRIES",
		"The list of RPC servers available for the binding of auto handles has been exhausted.",	"The list of RPC servers available for the binding of auto handles has been exhausted."	},
	{	RPC_X_SS_CHAR_TRANS_OPEN_FAIL,			"RPC_X_SS_CHAR_TRANS_OPEN_FAIL",
		"Unable to open the character translation table file.",	"Unable to open the character translation table file."	},
	{	RPC_X_SS_CHAR_TRANS_SHORT_FILE,			"RPC_X_SS_CHAR_TRANS_SHORT_FILE",
		"The file containing the character translation table has fewer than 512 bytes.",	"The file containing the character translation table has fewer than 512 bytes."	},
	{	RPC_X_SS_IN_NULL_CONTEXT,			"RPC_X_SS_IN_NULL_CONTEXT",
		"A null context handle was passed from the client to the host during a remote procedure call.",	"A null context handle was passed from the client to the host during a remote procedure call."	},
	{	RPC_X_SS_CONTEXT_DAMAGED,			"RPC_X_SS_CONTEXT_DAMAGED",
		"The context handle changed during a remote procedure call.",	"The context handle changed during a remote procedure call."	},
	{	RPC_X_SS_HANDLES_MISMATCH,			"RPC_X_SS_HANDLES_MISMATCH",
		"The binding handles passed to a remote procedure call do not match.",	"The binding handles passed to a remote procedure call do not match."	},
	{	RPC_X_SS_CANNOT_GET_CALL_HANDLE,			"RPC_X_SS_CANNOT_GET_CALL_HANDLE",
		"The stub is unable to get the remote procedure call handle.",	"The stub is unable to get the remote procedure call handle."	},
	{	RPC_X_NULL_REF_POINTER,			"RPC_X_NULL_REF_POINTER",
		"A null reference pointer was passed to the stub.",	"A null reference pointer was passed to the stub."	},
	{	RPC_X_ENUM_VALUE_OUT_OF_RANGE,			"RPC_X_ENUM_VALUE_OUT_OF_RANGE",
		"The enumeration value is out of range.",	"The enumeration value is out of range."	},
	{	RPC_X_BYTE_COUNT_TOO_SMALL,			"RPC_X_BYTE_COUNT_TOO_SMALL",
		"The byte count is too small.",	"The byte count is too small."	},
	{	RPC_X_BAD_STUB_DATA,			"RPC_X_BAD_STUB_DATA",
		"The stub received bad data.",	"The stub received bad data."	},
	{	ERROR_INVALID_USER_BUFFER,			"ERROR_INVALID_USER_BUFFER",
		"The supplied user buffer is not valid for the requested operation.",	"The supplied user buffer is not valid for the requested operation."	},
	{	ERROR_UNRECOGNIZED_MEDIA,			"ERROR_UNRECOGNIZED_MEDIA",
		"The disk media is not recognized. It may not be formatted.",	"The disk media is not recognized. It may not be formatted."	},
	{	ERROR_NO_TRUST_LSA_SECRET,			"ERROR_NO_TRUST_LSA_SECRET",
		"The workstation does not have a trust secret.",	"The workstation does not have a trust secret."	},
	{	ERROR_NO_TRUST_SAM_ACCOUNT,			"ERROR_NO_TRUST_SAM_ACCOUNT",
		"The SAM database on the Windows NT Server does not have a computer account for this workstation trust relationship.",	"The SAM database on the Windows NT Server does not have a computer account for this workstation trust relationship."	},
	{	ERROR_TRUSTED_DOMAIN_FAILURE,			"ERROR_TRUSTED_DOMAIN_FAILURE",
		"The trust relationship between the primary domain and the trusted domain failed.",	"The trust relationship between the primary domain and the trusted domain failed."	},
	{	ERROR_TRUSTED_RELATIONSHIP_FAILURE,			"ERROR_TRUSTED_RELATIONSHIP_FAILURE",
		"The trust relationship between this workstation and the primary domain failed.",	"The trust relationship between this workstation and the primary domain failed."	},
	{	ERROR_TRUST_FAILURE,			"ERROR_TRUST_FAILURE",
		"The network logon failed.",	"The network logon failed."	},
	{	RPC_S_CALL_IN_PROGRESS,			"RPC_S_CALL_IN_PROGRESS",
		"A remote procedure call is already in progress for this thread.",	"A remote procedure call is already in progress for this thread."	},
	{	ERROR_NETLOGON_NOT_STARTED,			"ERROR_NETLOGON_NOT_STARTED",
		"An attempt was made to logon, but the network logon service was not started.",	"An attempt was made to logon, but the network logon service was not started."	},
	{	ERROR_ACCOUNT_EXPIRED,			"ERROR_ACCOUNT_EXPIRED",
		"The user's account has expired.",	"The user's account has expired."	},
	{	ERROR_REDIRECTOR_HAS_OPEN_HANDLES,			"ERROR_REDIRECTOR_HAS_OPEN_HANDLES",
		"The redirector is in use and cannot be unloaded.",	"The redirector is in use and cannot be unloaded."	},
	{	ERROR_PRINTER_DRIVER_ALREADY_INSTALLED,			"ERROR_PRINTER_DRIVER_ALREADY_INSTALLED",
		"The specified printer driver is already installed.",	"The specified printer driver is already installed."	},
	{	ERROR_UNKNOWN_PORT,			"ERROR_UNKNOWN_PORT",
		"The specified port is unknown.",	"The specified port is unknown."	},
	{	ERROR_UNKNOWN_PRINTER_DRIVER,			"ERROR_UNKNOWN_PRINTER_DRIVER",
		"The printer driver is unknown.",	"The printer driver is unknown."	},
	{	ERROR_UNKNOWN_PRINTPROCESSOR,			"ERROR_UNKNOWN_PRINTPROCESSOR",
		"The print processor is unknown.",	"The print processor is unknown."	},
	{	ERROR_INVALID_SEPARATOR_FILE,			"ERROR_INVALID_SEPARATOR_FILE",
		"The specified separator file is invalid.",	"The specified separator file is invalid."	},
	{	ERROR_INVALID_PRIORITY,			"ERROR_INVALID_PRIORITY",
		"The specified priority is invalid.",	"The specified priority is invalid."	},
	{	ERROR_INVALID_PRINTER_NAME,			"ERROR_INVALID_PRINTER_NAME",
		"The printer name is invalid.",	"The printer name is invalid."	},
	{	ERROR_PRINTER_ALREADY_EXISTS,			"ERROR_PRINTER_ALREADY_EXISTS",
		"The printer already exists.",	"The printer already exists."	},
	{	ERROR_INVALID_PRINTER_COMMAND,			"ERROR_INVALID_PRINTER_COMMAND",
		"The printer command is invalid.",	"The printer command is invalid."	},
	{	ERROR_INVALID_DATATYPE,			"ERROR_INVALID_DATATYPE",
		"The specified datatype is invalid.",	"The specified datatype is invalid."	},
	{	ERROR_INVALID_ENVIRONMENT,			"ERROR_INVALID_ENVIRONMENT",
		"The environment specified is invalid.",	"The Environment specified is invalid."	},
	{	RPC_S_NO_MORE_BINDINGS,			"RPC_S_NO_MORE_BINDINGS",
		"There are no more bindings.",	"There are no more bindings."	},
	{	ERROR_NOLOGON_INTERDOMAIN_TRUST_ACCOUNT,			"ERROR_NOLOGON_INTERDOMAIN_TRUST_ACCOUNT",
		"The account used is an interdomain trust account. Use your global user account or local user account to access this server.",	"The account used is an interdomain trust account. Use your global user account or local user account to access this server."	},
	{	ERROR_NOLOGON_WORKSTATION_TRUST_ACCOUNT,			"ERROR_NOLOGON_WORKSTATION_TRUST_ACCOUNT",
		"The account used is a computer account. Use your global user account or local user account to access this server.",	"The account used is a Computer Account. Use your global user account or local user account to access this server."	},
	{	ERROR_NOLOGON_SERVER_TRUST_ACCOUNT,			"ERROR_NOLOGON_SERVER_TRUST_ACCOUNT",
		"The account used is a server trust account. Use your global user account or local user account to access this server.",	"The account used is an server trust account. Use your global user account or local user account to access this server."	},
	{	ERROR_DOMAIN_TRUST_INCONSISTENT,			"ERROR_DOMAIN_TRUST_INCONSISTENT",
		"The name or security ID (SID) of the domain specified is inconsistent with the trust information for that domain.",	"The name or security ID (SID) of the domain specified is inconsistent with the trust information for that domain."	},
	{	ERROR_SERVER_HAS_OPEN_HANDLES,			"ERROR_SERVER_HAS_OPEN_HANDLES",
		"The server is in use and cannot be unloaded.",	"The server is in use and cannot be unloaded."	},
	{	ERROR_RESOURCE_DATA_NOT_FOUND,			"ERROR_RESOURCE_DATA_NOT_FOUND",
		"The specified image file did not contain a resource section.",	"The specified image file did not contain a resource section."	},
	{	ERROR_RESOURCE_TYPE_NOT_FOUND,			"ERROR_RESOURCE_TYPE_NOT_FOUND",
		"The specified resource type cannot be found in the image file.",	"The specified resource type can not be found in the image file."	},
	{	ERROR_RESOURCE_NAME_NOT_FOUND,			"ERROR_RESOURCE_NAME_NOT_FOUND",
		"The specified resource name cannot be found in the image file.",	"The specified resource name can not be found in the image file."	},
	{	ERROR_RESOURCE_LANG_NOT_FOUND,			"ERROR_RESOURCE_LANG_NOT_FOUND",
		"The specified resource language ID cannot be found in the image file.",	"The specified resource language ID cannot be found in the image file."	},
	{	ERROR_NOT_ENOUGH_QUOTA,			"ERROR_NOT_ENOUGH_QUOTA",
		"Not enough quota is available to process this command.",	"Not enough quota is available to process this command."	},
	{	RPC_S_NO_INTERFACES,			"RPC_S_NO_INTERFACES",
		"No interfaces have been registered.",	"No interfaces have been registered."	},
	{	RPC_S_CALL_CANCELLED,			"RPC_S_CALL_CANCELLED",
		"The remote procedure call was cancelled.",	"The server was altered while processing this call."	},
	{	RPC_S_BINDING_INCOMPLETE,			"RPC_S_BINDING_INCOMPLETE",
		"The binding handle does not contain all required information.",	"The binding handle does not contain all required information."	},
	{	RPC_S_COMM_FAILURE,			"RPC_S_COMM_FAILURE",
		"A communications failure occurred during a remote procedure call.",	"Communications failure."	},
	{	RPC_S_UNSUPPORTED_AUTHN_LEVEL,			"RPC_S_UNSUPPORTED_AUTHN_LEVEL",
		"The requested authentication level is not supported.",	"The requested authentication level is not supported."	},
	{	RPC_S_NO_PRINC_NAME,			"RPC_S_NO_PRINC_NAME",
		"No principal name registered.",	"No principal name registered."	},
	{	RPC_S_NOT_RPC_ERROR,			"RPC_S_NOT_RPC_ERROR",
		"The error specified is not a valid Windows RPC error code.",	"The error specified is not a valid Windows NT RPC error code."	},
	{	RPC_S_UUID_LOCAL_ONLY,			"RPC_S_UUID_LOCAL_ONLY",
		"A UUID that is valid only on this computer has been allocated.",	"A UUID that is valid only on this computer has been allocated."	},
	{	RPC_S_SEC_PKG_ERROR,			"RPC_S_SEC_PKG_ERROR",
		"A security package specific error occurred.",	"A security package specific error occurred."	},
	{	RPC_S_NOT_CANCELLED,			"RPC_S_NOT_CANCELLED",
		"Thread is not canceled.",	"Thread is not cancelled."	},
	{	RPC_X_INVALID_ES_ACTION,			"RPC_X_INVALID_ES_ACTION",
		"Invalid operation on the encoding/decoding handle.",	"Invalid operation on the encoding/decoding handle."	},
	{	RPC_X_WRONG_ES_VERSION,			"RPC_X_WRONG_ES_VERSION",
		"Incompatible version of the serializing package.",	"Incompatible version of the serializing package."	},
	{	RPC_X_WRONG_STUB_VERSION,			"RPC_X_WRONG_STUB_VERSION",
		"Incompatible version of the RPC stub.",	"Incompatible version of the RPC stub."	},
	{	RPC_X_INVALID_PIPE_OBJECT,			"RPC_X_INVALID_PIPE_OBJECT",
		"The RPC pipe object is invalid or corrupted.",	"The idl pipe object is invalid or corrupted."	},
	{	RPC_X_WRONG_PIPE_ORDER,			"RPC_X_WRONG_PIPE_ORDER",
		"An invalid operation was attempted on an RPC pipe object.",	"The operation is invalid for a given idl pipe object."	},
	{	RPC_X_WRONG_PIPE_VERSION,			"RPC_X_WRONG_PIPE_VERSION",
		"Unsupported RPC pipe version.",	"The idl pipe version is not supported."	},
	{	RPC_S_GROUP_MEMBER_NOT_FOUND,			"RPC_S_GROUP_MEMBER_NOT_FOUND",
		"The group member was not found.",	"The group member was not found."	},
	{	EPT_S_CANT_CREATE,			"EPT_S_CANT_CREATE",
		"The endpoint mapper database entry could not be created.",	"The endpoint mapper database could not be created."	},
	{	RPC_S_INVALID_OBJECT,			"RPC_S_INVALID_OBJECT",
		"The object universal unique identifier (UUID) is the nil UUID.",	"The object universal unique identifier (UUID) is the nil UUID."	},
	{	ERROR_INVALID_TIME,			"ERROR_INVALID_TIME",
		"The specified time is invalid.",	"The specified time is invalid."	},
	{	ERROR_INVALID_FORM_NAME,			"ERROR_INVALID_FORM_NAME",
		"The specified form name is invalid.",	"The specified Form name is invalid."	},
	{	ERROR_INVALID_FORM_SIZE,			"ERROR_INVALID_FORM_SIZE",
		"The specified form size is invalid.",	"The specified Form size is invalid"	},
	{	ERROR_ALREADY_WAITING,			"ERROR_ALREADY_WAITING",
		"The specified printer handle is already being waited on",	"The specified Printer handle is already being waited on"	},
	{	ERROR_PRINTER_DELETED,			"ERROR_PRINTER_DELETED",
		"The specified printer has been deleted.",	"The specified Printer has been deleted"	},
	{	ERROR_INVALID_PRINTER_STATE,			"ERROR_INVALID_PRINTER_STATE",
		"The state of the printer is invalid.",	"The state of the Printer is invalid"	},
	{	ERROR_PASSWORD_MUST_CHANGE,			"ERROR_PASSWORD_MUST_CHANGE",
		"The user must change his password before he logs on the first time.",	"The user must change his password before he logs on the first time."	},
	{	ERROR_DOMAIN_CONTROLLER_NOT_FOUND,			"ERROR_DOMAIN_CONTROLLER_NOT_FOUND",
		"Could not find the domain controller for this domain.",	"Could not find the domain controller for this domain."	},
	{	ERROR_ACCOUNT_LOCKED_OUT,			"ERROR_ACCOUNT_LOCKED_OUT",
		"The referenced account is currently locked out and may not be logged on to.",	"The referenced account is currently locked out and may not be logged on to."	},
	{	OR_INVALID_OXID,			"OR_INVALID_OXID",
		"The object exporter specified was not found.",	"The object exporter specified was not found."	},
	{	OR_INVALID_OID,			"OR_INVALID_OID",
		"The object specified was not found.",	"The object specified was not found."	},
	{	OR_INVALID_SET,			"OR_INVALID_SET",
		"The object resolver set specified was not found.",	"The object resolver set specified was not found."	},
	{	RPC_S_SEND_INCOMPLETE,			"RPC_S_SEND_INCOMPLETE",
		"Some data remains to be sent in the request buffer.",	"Some data remains to be sent in the request buffer."	},
	{	RPC_S_INVALID_ASYNC_HANDLE,			"RPC_S_INVALID_ASYNC_HANDLE",
		"Invalid asynchronous remote procedure call handle.",	"Invalid asynchronous remote procedure call handle."	},
	{	RPC_S_INVALID_ASYNC_CALL,			"RPC_S_INVALID_ASYNC_CALL",
		"Invalid asynchronous RPC call handle for this operation.",	"Invalid asynchronous RPC call handle for this operation."	},
	{	RPC_X_PIPE_CLOSED,			"RPC_X_PIPE_CLOSED",
		"The RPC pipe object has already been closed.",	"The RPC pipe object has already been closed."	},
	{	RPC_X_PIPE_DISCIPLINE_ERROR,			"RPC_X_PIPE_DISCIPLINE_ERROR",
		"The RPC call completed before all pipes were processed.",	"The RPC call completed before all pipes were processed."	},
	{	RPC_X_PIPE_EMPTY,			"RPC_X_PIPE_EMPTY",
		"No more data is available from the RPC pipe.",	"No more data is available from the RPC pipe."	},
	{	ERROR_NO_SITENAME,			"ERROR_NO_SITENAME",
		"No site name is available for this machine.",	"No site name is available for this machine."	},
	{	ERROR_CANT_ACCESS_FILE,			"ERROR_CANT_ACCESS_FILE",
		"The file can not be accessed by the system.",	"The file can not be accessed by the system."	},
	{	ERROR_CANT_RESOLVE_FILENAME,			"ERROR_CANT_RESOLVE_FILENAME",
		"The name of the file cannot be resolved by the system.",	"The name of the file cannot be resolved by the system."	},
	{	ERROR_DS_MEMBERSHIP_EVALUATED_LOCALLY,			"ERROR_DS_MEMBERSHIP_EVALUATED_LOCALLY",
		"The directory service evaluated group memberships locally.",	"The directory service evaluated group memberships locally."	},
	{	ERROR_DS_NO_ATTRIBUTE_OR_VALUE,			"ERROR_DS_NO_ATTRIBUTE_OR_VALUE",
		"The specified directory service attribute or value does not exist.",	"The specified directory service attribute or value does not exist."	},
	{	ERROR_DS_INVALID_ATTRIBUTE_SYNTAX,			"ERROR_DS_INVALID_ATTRIBUTE_SYNTAX",
		"The attribute syntax specified to the directory service is invalid.",	"The attribute syntax specified to the directory service is invalid."	},
	{	ERROR_DS_ATTRIBUTE_TYPE_UNDEFINED,			"ERROR_DS_ATTRIBUTE_TYPE_UNDEFINED",
		"The attribute type specified to the directory service is not defined.",	"The attribute type specified to the directory service is not defined."	},
	{	ERROR_DS_ATTRIBUTE_OR_VALUE_EXISTS,			"ERROR_DS_ATTRIBUTE_OR_VALUE_EXISTS",
		"The specified directory service attribute or value already exists.",	"The specified directory service attribute or value already exists."	},
	{	ERROR_DS_BUSY,			"ERROR_DS_BUSY",
		"The directory service is busy.",	"The directory service is busy."	},
	{	ERROR_DS_UNAVAILABLE,			"ERROR_DS_UNAVAILABLE",
		"The directory service is unavailable.",	"The directory service is unavailable."	},
	{	ERROR_DS_NO_RIDS_ALLOCATED,			"ERROR_DS_NO_RIDS_ALLOCATED",
		"The directory service was unable to allocate a relative identifier.",	"The directory service was unable to allocate a relative identifier."	},
	{	ERROR_DS_NO_MORE_RIDS,			"ERROR_DS_NO_MORE_RIDS",
		"The directory service has exhausted the pool of relative identifiers.",	"The directory service has exhausted the pool of relative identifiers."	},
	{	ERROR_DS_INCORRECT_ROLE_OWNER,			"ERROR_DS_INCORRECT_ROLE_OWNER",
		"The requested operation could not be performed because the directory service is not the master for that type of operation.",	"The requested operation could not be performed because the directory service is not the master for that type of operation."	},
	{	ERROR_DS_RIDMGR_INIT_ERROR,			"ERROR_DS_RIDMGR_INIT_ERROR",
		"The directory service was unable to initialize the subsystem that allocates relative identifiers.",	"The directory service was unable to initialize the subsystem that allocates relative identifiers."	},
	{	ERROR_DS_OBJ_CLASS_VIOLATION,			"ERROR_DS_OBJ_CLASS_VIOLATION",
		"The requested operation did not satisfy one or more constraints associated with the class of the object.",	"The requested operation did not satisfy one or more constraints associated with the class of the object."	},
	{	ERROR_DS_CANT_ON_NON_LEAF,			"ERROR_DS_CANT_ON_NON_LEAF",
		"The directory service can perform the requested operation only on a leaf object.",	"The directory service can perform the requested operation only on a leaf object."	},
	{	ERROR_DS_CANT_ON_RDN,			"ERROR_DS_CANT_ON_RDN",
		"The directory service cannot perform the requested operation on the RDN attribute of an object.",	"The directory service cannot perform the requested operation on the RDN attribute of an object."	},
	{	ERROR_DS_CANT_MOD_OBJ_CLASS,			"ERROR_DS_CANT_MOD_OBJ_CLASS",
		"The directory service detected an attempt to modify the object class of an object.",	"The directory service detected an attempt to modify the object class of an object."	},
	{	ERROR_DS_CROSS_DOM_MOVE_ERROR,			"ERROR_DS_CROSS_DOM_MOVE_ERROR",
		"The requested cross domain move operation could not be performed.",	"The requested cross domain move operation could not be performed."	},
	{	ERROR_DS_GC_NOT_AVAILABLE,			"ERROR_DS_GC_NOT_AVAILABLE",
		"Unable to contact the global catalog server.",	"Unable to contact the global catalog server."	},
	{	ERROR_NO_BROWSER_SERVERS_FOUND,			"ERROR_NO_BROWSER_SERVERS_FOUND",
		"The list of servers for this workgroup is not currently available",	"The list of servers for this workgroup is not currently available"	},
	{	ERROR_INVALID_PIXEL_FORMAT,			"ERROR_INVALID_PIXEL_FORMAT",
		"The pixel format is invalid.",	"The pixel format is invalid."	},
	{	ERROR_BAD_DRIVER,			"ERROR_BAD_DRIVER",
		"The specified driver is invalid.",	"The specified driver is invalid."	},
	{	ERROR_INVALID_WINDOW_STYLE,			"ERROR_INVALID_WINDOW_STYLE",
		"The window style or class attribute is invalid for this operation.",	"The window style or class attribute is invalid for this operation."	},
	{	ERROR_METAFILE_NOT_SUPPORTED,			"ERROR_METAFILE_NOT_SUPPORTED",
		"The requested metafile operation is not supported.",	"The requested metafile operation is not supported."	},
	{	ERROR_TRANSFORM_NOT_SUPPORTED,			"ERROR_TRANSFORM_NOT_SUPPORTED",
		"The requested transformation operation is not supported.",	"The requested transformation operation is not supported."	},
	{	ERROR_CLIPPING_NOT_SUPPORTED,			"ERROR_CLIPPING_NOT_SUPPORTED",
		"The requested clipping operation is not supported.",	"The requested clipping operation is not supported."	},
	{	ERROR_INVALID_CMM,			"ERROR_INVALID_CMM",
		"The specified color management module is invalid.",	"The specified color management module is invalid."	},
	{	ERROR_INVALID_PROFILE,			"ERROR_INVALID_PROFILE",
		"The specified color profile is invalid.",	"The specified color profile is invalid."	},
	{	ERROR_TAG_NOT_FOUND,			"ERROR_TAG_NOT_FOUND",
		"The specified tag was not found.",	"The specified tag was not found."	},
	{	ERROR_TAG_NOT_PRESENT,			"ERROR_TAG_NOT_PRESENT",
		"A required tag is not present.",	"A required tag is not present."	},
	{	ERROR_DUPLICATE_TAG,			"ERROR_DUPLICATE_TAG",
		"The specified tag is already present.",	"The specified tag is already present."	},
	{	ERROR_PROFILE_NOT_ASSOCIATED_WITH_DEVICE,			"ERROR_PROFILE_NOT_ASSOCIATED_WITH_DEVICE",
		"The specified color profile is not associated with any device.",	"The specified color profile is not associated with any device."	},
	{	ERROR_PROFILE_NOT_FOUND,			"ERROR_PROFILE_NOT_FOUND",
		"The specified color profile was not found.",	"The specified color profile was not found."	},
	{	ERROR_INVALID_COLORSPACE,			"ERROR_INVALID_COLORSPACE",
		"The specified color space is invalid.",	"The specified color space is invalid."	},
	{	ERROR_ICM_NOT_ENABLED,			"ERROR_ICM_NOT_ENABLED",
		"Image Color Management is not enabled.",	"Image Color Management is not enabled."	},
	{	ERROR_DELETING_ICM_XFORM,			"ERROR_DELETING_ICM_XFORM",
		"There was an error while deleting the color transform.",	"There was an error while deleting the color transform."	},
	{	ERROR_INVALID_TRANSFORM,			"ERROR_INVALID_TRANSFORM",
		"The specified color transform is invalid.",	"The specified color transform is invalid."	},
	{	ERROR_UNKNOWN_PRINT_MONITOR,			"ERROR_UNKNOWN_PRINT_MONITOR",
		"The specified print monitor is unknown.",	"The specified print monitor is unknown."	},
	{	ERROR_PRINTER_DRIVER_IN_USE,			"ERROR_PRINTER_DRIVER_IN_USE",
		"The specified printer driver is currently in use.",	"The specified printer driver is currently in use."	},
	{	ERROR_SPOOL_FILE_NOT_FOUND,			"ERROR_SPOOL_FILE_NOT_FOUND",
		"The spool file was not found.",	"The spool file was not found."	},
	{	ERROR_SPL_NO_STARTDOC,			"ERROR_SPL_NO_STARTDOC",
		"A StartDocPrinter call was not issued.",	"A StartDocPrinter call was not issued."	},
	{	ERROR_SPL_NO_ADDJOB,			"ERROR_SPL_NO_ADDJOB",
		"An AddJob call was not issued.",	"An AddJob call was not issued."	},
	{	ERROR_PRINT_PROCESSOR_ALREADY_INSTALLED,			"ERROR_PRINT_PROCESSOR_ALREADY_INSTALLED",
		"The specified print processor has already been installed.",	"The specified print processor has already been installed."	},
	{	ERROR_PRINT_MONITOR_ALREADY_INSTALLED,			"ERROR_PRINT_MONITOR_ALREADY_INSTALLED",
		"The specified print monitor has already been installed.",	"The specified print monitor has already been installed."	},
	{	ERROR_INVALID_PRINT_MONITOR,			"ERROR_INVALID_PRINT_MONITOR",
		"The specified print monitor does not have the required functions.",	"The specified print monitor does not have the required functions."	},
	{	ERROR_PRINT_MONITOR_IN_USE,			"ERROR_PRINT_MONITOR_IN_USE",
		"The specified print monitor is currently in use.",	"The specified print monitor is currently in use."	},
	{	ERROR_PRINTER_HAS_JOBS_QUEUED,			"ERROR_PRINTER_HAS_JOBS_QUEUED",
		"The requested operation is not allowed when there are jobs queued to the printer.",	"The requested operation is not allowed when there are jobs queued to the printer."	},
	{	ERROR_SUCCESS_REBOOT_REQUIRED,			"ERROR_SUCCESS_REBOOT_REQUIRED",
		"The requested operation is successful. Changes will not be effective until the system is rebooted.",	"The requested operation is successful. Changes will not be effective until the system is rebooted."	},
	{	ERROR_SUCCESS_RESTART_REQUIRED,			"ERROR_SUCCESS_RESTART_REQUIRED",
		"The requested operation is successful. Changes will not be effective until the service is restarted.",	"The requested operation is successful. Changes will not be effective until the service is restarted."	},
	{	ERROR_WINS_INTERNAL,			"ERROR_WINS_INTERNAL",
		"WINS encountered an error while processing the command.",	"WINS encountered an error while processing the command."	},
	{	ERROR_CAN_NOT_DEL_LOCAL_WINS,			"ERROR_CAN_NOT_DEL_LOCAL_WINS",
		"The local WINS can not be deleted.",	"The local WINS can not be deleted."	},
	{	ERROR_STATIC_INIT,			"ERROR_STATIC_INIT",
		"The importation from the file failed.",	"The importation from the file failed."	},
	{	ERROR_INC_BACKUP,			"ERROR_INC_BACKUP",
		"The backup failed. Was a full backup done before?",	"The backup Failed. Was a full backup done before ?"	},
	{	ERROR_FULL_BACKUP,			"ERROR_FULL_BACKUP",
		"The backup failed. Check the directory to which you are backing the database.",	"The backup Failed. Check the directory that you are backing the database to."	},
	{	ERROR_REC_NON_EXISTENT,			"ERROR_REC_NON_EXISTENT",
		"The name does not exist in the WINS database.",	"The name does not exist in the WINS database."	},
	{	ERROR_RPL_NOT_ALLOWED,			"ERROR_RPL_NOT_ALLOWED",
		"Replication with a nonconfigured partner is not allowed.",	"Replication with a non-configured partner is not allowed."	},
	{	ERROR_DHCP_ADDRESS_CONFLICT,			"ERROR_DHCP_ADDRESS_CONFLICT",
		"The DHCP client has obtained an IP address that is already in use on the network. The local interface will be disabled until the DHCP client can obtain a new address.",	"The DHCP client has obtained an IP address that is already in use on the network. The local interface will be disabled until the DHCP client can obtain a new address."	},
	{	ERROR_WMI_GUID_NOT_FOUND,			"ERROR_WMI_GUID_NOT_FOUND",
		"The GUID passed was not recognized as valid by a WMI data provider.",	"The GUID passed was not recognized as valid by a WMI data provider."	},
	{	ERROR_WMI_INSTANCE_NOT_FOUND,			"ERROR_WMI_INSTANCE_NOT_FOUND",
		"The instance name passed was not recognized as valid by a WMI data provider.",	"The instance name passed was not recognized as valid by a WMI data provider."	},
	{	ERROR_WMI_ITEMID_NOT_FOUND,			"ERROR_WMI_ITEMID_NOT_FOUND",
		"The data item ID passed was not recognized as valid by a WMI data provider.",	"The data item ID passed was not recognized as valid by a WMI data provider."	},
	{	ERROR_WMI_TRY_AGAIN,			"ERROR_WMI_TRY_AGAIN",
		"The WMI request could not be completed and should be retried.",	"The WMI request could not be completed and should be retried."	},
	{	ERROR_WMI_DP_NOT_FOUND,			"ERROR_WMI_DP_NOT_FOUND",
		"The WMI data provider could not be located.",	"The WMI data provider could not be located."	},
	{	ERROR_WMI_UNRESOLVED_INSTANCE_REF,			"ERROR_WMI_UNRESOLVED_INSTANCE_REF",
		"The WMI data provider references an instance set that has not been registered.",	"The WMI data provider references an instance set that has not been registered."	},
	{	ERROR_WMI_ALREADY_ENABLED,			"ERROR_WMI_ALREADY_ENABLED",
		"The WMI data block or event notification has already been enabled.",	"The WMI data block or event notification has already been enabled."	},
	{	ERROR_WMI_GUID_DISCONNECTED,			"ERROR_WMI_GUID_DISCONNECTED",
		"The WMI data block is no longer available.",	"The WMI data block is no longer available."	},
	{	ERROR_WMI_SERVER_UNAVAILABLE,			"ERROR_WMI_SERVER_UNAVAILABLE",
		"The WMI data service is not available.",	"The WMI data service is not available."	},
	{	ERROR_WMI_DP_FAILED,			"ERROR_WMI_DP_FAILED",
		"The WMI data provider failed to carry out the request.",	"The WMI data provider failed to carry out the request."	},
	{	ERROR_WMI_INVALID_MOF,			"ERROR_WMI_INVALID_MOF",
		"The WMI MOF information is not valid.",	"The WMI MOF information is not valid."	},
	{	ERROR_WMI_INVALID_REGINFO,			"ERROR_WMI_INVALID_REGINFO",
		"The WMI registration information is not valid.",	"The WMI registration information is not valid."	},
	{	ERROR_INVALID_MEDIA,			"ERROR_INVALID_MEDIA",
		"The media identifier does not represent a valid medium.",	"The media identifier does not represent a valid medium."	},
	{	ERROR_INVALID_LIBRARY,			"ERROR_INVALID_LIBRARY",
		"The library identifier does not represent a valid library.",	"The library identifier does not represent a valid library."	},
	{	ERROR_INVALID_MEDIA_POOL,			"ERROR_INVALID_MEDIA_POOL",
		"The media pool identifier does not represent a valid media pool.",	"The media pool identifier does not represent a valid media pool."	},
	{	ERROR_DRIVE_MEDIA_MISMATCH,			"ERROR_DRIVE_MEDIA_MISMATCH",
		"The drive and medium are not compatible or exist in different libraries.",	"The drive and medium are not compatible or exist in different libraries."	},
	{	ERROR_MEDIA_OFFLINE,			"ERROR_MEDIA_OFFLINE",
		"The medium currently exists in an offline library and must be online to perform this operation.",	"The medium currently exists in an offline library and must be online to perform this operation."	},
	{	ERROR_LIBRARY_OFFLINE,			"ERROR_LIBRARY_OFFLINE",
		"The operation cannot be performed on an offline library.",	"The operation cannot be performed on an offline library."	},
	{	ERROR_EMPTY,			"ERROR_EMPTY",
		"The library, drive, or media pool is empty.",	"The library, drive, or media pool is empty."	},
	{	ERROR_NOT_EMPTY,			"ERROR_NOT_EMPTY",
		"The library, drive, or media pool must be empty to perform this operation.",	"The library, drive, or media pool must be empty to perform this operation."	},
	{	ERROR_MEDIA_UNAVAILABLE,			"ERROR_MEDIA_UNAVAILABLE",
		"No media is currently available in this media pool or library.",	"No media is currently available in this media pool or library."	},
	{	ERROR_RESOURCE_DISABLED,			"ERROR_RESOURCE_DISABLED",
		"A resource required for this operation is disabled.",	"A resource required for this operation is disabled."	},
	{	ERROR_INVALID_CLEANER,			"ERROR_INVALID_CLEANER",
		"The media identifier does not represent a valid cleaner.",	"The media identifier does not represent a valid cleaner."	},
	{	ERROR_UNABLE_TO_CLEAN,			"ERROR_UNABLE_TO_CLEAN",
		"The drive cannot be cleaned or does not support cleaning.",	"The drive cannot be cleaned or does not support cleaning."	},
	{	ERROR_OBJECT_NOT_FOUND,			"ERROR_OBJECT_NOT_FOUND",
		"The object identifier does not represent a valid object.",	"The object identifier does not represent a valid object."	},
	{	ERROR_DATABASE_FAILURE,			"ERROR_DATABASE_FAILURE",
		"Unable to read from or write to the database.",	"Unable to read from or write to the database."	},
	{	ERROR_DATABASE_FULL,			"ERROR_DATABASE_FULL",
		"The database is full.",	"The database is full."	},
	{	ERROR_MEDIA_INCOMPATIBLE,			"ERROR_MEDIA_INCOMPATIBLE",
		"The medium is not compatible with the device or media pool.",	"The medium is not compatible with the device or media pool."	},
	{	ERROR_RESOURCE_NOT_PRESENT,			"ERROR_RESOURCE_NOT_PRESENT",
		"The resource required for this operation does not exist.",	"The resource required for this operation does not exist."	},
	{	ERROR_INVALID_OPERATION,			"ERROR_INVALID_OPERATION",
		"The operation identifier is not valid.",	"The operation identifier is not valid."	},
	{	ERROR_MEDIA_NOT_AVAILABLE,			"ERROR_MEDIA_NOT_AVAILABLE",
		"The media is not mounted or ready for use.",	"The media is not mounted or ready for use."	},
	{	ERROR_DEVICE_NOT_AVAILABLE,			"ERROR_DEVICE_NOT_AVAILABLE",
		"The device is not ready for use.",	"The device is not ready for use."	},
	{	ERROR_REQUEST_REFUSED,			"ERROR_REQUEST_REFUSED",
		"The operator or administrator has refused the request.",	"The operator or administrator has refused the request."	},
	{	ERROR_FILE_OFFLINE,			"ERROR_FILE_OFFLINE",
		"The remote storage service was not able to recall the file.",	"The remote storage service was not able to recall the file."	},
	{	ERROR_REMOTE_STORAGE_NOT_ACTIVE,			"ERROR_REMOTE_STORAGE_NOT_ACTIVE",
		"The remote storage service is not operational at this time.",	"The remote storage service is not operational at this time."	},
	{	ERROR_REMOTE_STORAGE_MEDIA_ERROR,			"ERROR_REMOTE_STORAGE_MEDIA_ERROR",
		"The remote storage service encountered a media error.",	"The remote storage service encountered a media error."	},
	{	ERROR_NOT_A_REPARSE_POINT,			"ERROR_NOT_A_REPARSE_POINT",
		"The file or directory is not a reparse point.",	"The file or directory is not a reparse point."	},
	{	ERROR_REPARSE_ATTRIBUTE_CONFLICT,			"ERROR_REPARSE_ATTRIBUTE_CONFLICT",
		"The reparse point attribute cannot be set because it conflicts with an existing attribute.",	"The reparse point attribute cannot be set because it conflicts with an existing attribute."	},
	{	ERROR_DEPENDENT_RESOURCE_EXISTS,			"ERROR_DEPENDENT_RESOURCE_EXISTS",
		"The cluster resource cannot be moved to another group because other resources are dependent on it.",	"The cluster resource cannot be moved to another group because other resources are dependent on it."	},
	{	ERROR_DEPENDENCY_NOT_FOUND,			"ERROR_DEPENDENCY_NOT_FOUND",
		"The cluster resource dependency cannot be found.",	"The cluster resource dependency cannot be found."	},
	{	ERROR_DEPENDENCY_ALREADY_EXISTS,			"ERROR_DEPENDENCY_ALREADY_EXISTS",
		"The cluster resource cannot be made dependent on the specified resource because it is already dependent.",	"The cluster resource cannot be made dependent on the specified resource because it is already dependent."	},
	{	ERROR_RESOURCE_NOT_ONLINE,			"ERROR_RESOURCE_NOT_ONLINE",
		"The cluster resource is not online.",	"The cluster resource is not online."	},
	{	ERROR_HOST_NODE_NOT_AVAILABLE,			"ERROR_HOST_NODE_NOT_AVAILABLE",
		"A cluster node is not available for this operation.",	"A cluster node is not available for this operation."	},
	{	ERROR_RESOURCE_NOT_AVAILABLE,			"ERROR_RESOURCE_NOT_AVAILABLE",
		"The cluster resource is not available.",	"The cluster resource is not available."	},
	{	ERROR_RESOURCE_NOT_FOUND,			"ERROR_RESOURCE_NOT_FOUND",
		"The cluster resource could not be found.",	"The cluster resource could not be found."	},
	{	ERROR_SHUTDOWN_CLUSTER,			"ERROR_SHUTDOWN_CLUSTER",
		"The cluster is being shut down.",	"The cluster is being shut down."	},
	{	ERROR_CANT_EVICT_ACTIVE_NODE,			"ERROR_CANT_EVICT_ACTIVE_NODE",
		"A cluster node cannot be evicted from the cluster while it is online.",	"A cluster node cannot be evicted from the cluster while it is online."	},
	{	ERROR_OBJECT_ALREADY_EXISTS,			"ERROR_OBJECT_ALREADY_EXISTS",
		"The object already exists.",	"The object already exists."	},
	{	ERROR_OBJECT_IN_LIST,			"ERROR_OBJECT_IN_LIST",
		"The object is already in the list.",	"The object is already in the list."	},
	{	ERROR_GROUP_NOT_AVAILABLE,			"ERROR_GROUP_NOT_AVAILABLE",
		"The cluster group is not available for any new requests.",	"The cluster group is not available for any new requests."	},
	{	ERROR_GROUP_NOT_FOUND,			"ERROR_GROUP_NOT_FOUND",
		"The cluster group could not be found.",	"The cluster group could not be found."	},
	{	ERROR_GROUP_NOT_ONLINE,			"ERROR_GROUP_NOT_ONLINE",
		"The operation could not be completed because the cluster group is not online.",	"The operation could not be completed because the cluster group is not online."	},
	{	ERROR_HOST_NODE_NOT_RESOURCE_OWNER,			"ERROR_HOST_NODE_NOT_RESOURCE_OWNER",
		"The cluster node is not the owner of the resource.",	"The cluster node is not the owner of the resource."	},
	{	ERROR_HOST_NODE_NOT_GROUP_OWNER,			"ERROR_HOST_NODE_NOT_GROUP_OWNER",
		"The cluster node is not the owner of the group.",	"The cluster node is not the owner of the group."	},
	{	ERROR_RESMON_CREATE_FAILED,			"ERROR_RESMON_CREATE_FAILED",
		"The cluster resource could not be created in the specified resource monitor.",	"The cluster resource could not be created in the specified resource monitor."	},
	{	ERROR_RESMON_ONLINE_FAILED,			"ERROR_RESMON_ONLINE_FAILED",
		"The cluster resource could not be brought online by the resource monitor.",	"The cluster resource could not be brought online by the resource monitor."	},
	{	ERROR_RESOURCE_ONLINE,			"ERROR_RESOURCE_ONLINE",
		"The operation could not be completed because the cluster resource is online.",	"The operation could not be completed because the cluster resource is online."	},
	{	ERROR_QUORUM_RESOURCE,			"ERROR_QUORUM_RESOURCE",
		"The cluster resource could not be deleted or brought offline because it is the quorum resource.",	"The cluster resource could not be deleted or brought offline because it is the quorum resource."	},
	{	ERROR_NOT_QUORUM_CAPABLE,			"ERROR_NOT_QUORUM_CAPABLE",
		"The cluster could not make the specified resource a quorum resource because it is not capable of being a quorum resource.",	"The cluster could not make the specified resource a quorum resource because it is not capable of being a quorum resource."	},
	{	ERROR_CLUSTER_SHUTTING_DOWN,			"ERROR_CLUSTER_SHUTTING_DOWN",
		"The cluster software is shutting down.",	"The cluster software is shutting down."	},
	{	ERROR_INVALID_STATE,			"ERROR_INVALID_STATE",
		"The group or resource is not in the correct state to perform the requested operation.",	"The group or resource is not in the correct state to perform the requested operation."	},
	{	ERROR_RESOURCE_PROPERTIES_STORED,			"ERROR_RESOURCE_PROPERTIES_STORED",
		"The properties were stored but not all changes will take effect until the next time the resource is brought online.",	"The properties were stored but not all changes will take effect until the next time the resource is brought online."	},
	{	ERROR_NOT_QUORUM_CLASS,			"ERROR_NOT_QUORUM_CLASS",
		"The cluster could not make the specified resource a quorum resource because it does not belong to a shared storage class.",	"The cluster could not make the specified resource a quorum resource because it does not belong to a shared storage class."	},
	{	ERROR_CORE_RESOURCE,			"ERROR_CORE_RESOURCE",
		"The cluster resource could not be deleted since it is a core resource.",	"The cluster resource could not be deleted since it is a core resource."	},
	{	ERROR_QUORUM_RESOURCE_ONLINE_FAILED,			"ERROR_QUORUM_RESOURCE_ONLINE_FAILED",
		"The quorum resource failed to come online.",	"The quorum resource failed to come online."	},
	{	ERROR_QUORUMLOG_OPEN_FAILED,			"ERROR_QUORUMLOG_OPEN_FAILED",
		"The quorum log could not be created or mounted successfully.",	"The quorum log could not be created or mounted successfully."	},
	{	ERROR_CLUSTERLOG_CORRUPT,			"ERROR_CLUSTERLOG_CORRUPT",
		"The cluster log is corrupt.",	"The cluster log is corrupt."	},
	{	ERROR_CLUSTERLOG_RECORD_EXCEEDS_MAXSIZE,			"ERROR_CLUSTERLOG_RECORD_EXCEEDS_MAXSIZE",
		"The record could not be written to the cluster log since it exceeds the maximum size.",	"The record could not be written to the cluster log since it exceeds the maximum size."	},
	{	ERROR_CLUSTERLOG_EXCEEDS_MAXSIZE,			"ERROR_CLUSTERLOG_EXCEEDS_MAXSIZE",
		"The cluster log exceeds its maximum size.",	"The cluster log exceeds its maximum size."	},
	{	ERROR_CLUSTERLOG_CHKPOINT_NOT_FOUND,			"ERROR_CLUSTERLOG_CHKPOINT_NOT_FOUND",
		"No checkpoint record was found in the cluster log.",	"No checkpoint record was found in the cluster log."	},
	{	ERROR_CLUSTERLOG_NOT_ENOUGH_SPACE,			"ERROR_CLUSTERLOG_NOT_ENOUGH_SPACE",
		"The minimum required disk space needed for logging is not available.",	"The minimum required disk space needed for logging is not available."	},
	{	ERROR_ENCRYPTION_FAILED,			"ERROR_ENCRYPTION_FAILED",
		"The specified file could not be encrypted.",	"The specified file could not be encrypted."	},
	{	ERROR_DECRYPTION_FAILED,			"ERROR_DECRYPTION_FAILED",
		"The specified file could not be decrypted.",	"The specified file could not be decrypted."	},
	{	ERROR_FILE_ENCRYPTED,			"ERROR_FILE_ENCRYPTED",
		"The specified file is encrypted and the user does not have the ability to decrypt it.",	"The specified file is encrypted and the user does not have the ability to decrypt it."	},
	{	ERROR_NO_RECOVERY_POLICY,			"ERROR_NO_RECOVERY_POLICY",
		"There is no encryption recovery policy configured for this system.",	"There is no encryption recovery policy configured for this system."	},
	{	ERROR_NO_EFS,			"ERROR_NO_EFS",
		"The required encryption driver is not loaded for this system.",	"The required encryption driver is not loaded for this system."	},
	{	ERROR_WRONG_EFS,			"ERROR_WRONG_EFS",
		"The file was encrypted with a different encryption driver than is currently loaded.",	"The file was encrypted with a different encryption driver than is currently loaded."	},
	{	ERROR_NO_USER_KEYS,			"ERROR_NO_USER_KEYS",
		"There are no EFS keys defined for the user.",	"There are no EFS keys defined for the user."	},
	{	ERROR_FILE_NOT_ENCRYPTED,			"ERROR_FILE_NOT_ENCRYPTED",
		"The specified file is not encrypted.",	"The specified file is not encrypted."	},
	{	ERROR_NOT_EXPORT_FORMAT,			"ERROR_NOT_EXPORT_FORMAT",
		"The specified file is not in the defined EFS export format.",	"The specified file is not in the defined EFS export format."	},
};
static const unsigned int GEN_ErrorCount_Win32 =
	(sizeof(GEN_ErrorList_Win32) / sizeof(GEN_ErrorList_Win32[0]));
/*	***********************************************************************	*/

/*
START_HERE
*/

/*	***********************************************************************	*/
#ifndef NARGS
void GEN_GetErrorList_Win32(unsigned int *out_count,
	const GEN_ERROR_SPEC **out_list)
#else
void GEN_GetErrorList_Win32(out_count, out_list)
unsigned int          *out_count;
const GEN_ERROR_SPEC **out_list;
#endif /* #ifndef NARGS */
{
	*out_count = GEN_ErrorCount_Win32;
	*out_list  = GEN_ErrorList_Win32;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	GEN_GetErrorPtr_Win32

	SYNOPSIS		:	return_ptr = GEN_GetErrorPtr_Win32(win32_code);

						const GEN_ERROR_SPEC *return_ptr;

						int                   win32_code;

	DESCRIPTION	:	Gets a pointer the ''GEN_ERROR_SPEC'' error description
						structure corresponding to the specified Win32 error code.

   PARAMETERS  :  Parameters to this function are as follows:

						(.) ``win32_code`` is the Win32 error code for which the
						function is to return a pointer to the corresponding error
						description structure.

   RETURNS     :  Returns from this function are as follow:

						(.) If the Win32 error code specified by the ``win32_code``
						parameter is valid, a pointer to the ''GEN_ERROR_SPEC''
						error description structure corresponding to that error
						code is returned.

						(.) Otherwise, a ''NULL'' pointer is returned.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	GEN_GetErrorPtr
						GEN_GetLastErrorPtr_Win32

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2014 Michael L. Brock

	OUTPUT INDEX:	GEN_GetErrorPtr_Win32
						Error Description Functions:GEN_GetErrorPtr_Win32
						Windows Functions:GEN_GetErrorPtr_Win32
						GENFUNCS:Functions:GEN_GetErrorPtr_Win32
						GENFUNCS:Error Description Functions:GEN_GetErrorPtr_Win32
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_GetErrorPtr_Win32

	PUBLISH NAME:	GEN_GetErrorPtr_Win32

	ENTRY CLASS	:	Error Description Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
const GEN_ERROR_SPEC *GEN_GetErrorPtr_Win32(int win32_code)
#else
const GEN_ERROR_SPEC *GEN_GetErrorPtr_Win32(win32_code)
int win32_code;
#endif /* #ifndef NARGS */
{
	unsigned int          count_1;
	const GEN_ERROR_SPEC *spec_ptr = NULL;

	if ((win32_code >= 0) && (win32_code < ((int) GEN_ErrorCount_Win32)) &&
		(win32_code == GEN_ErrorList_Win32[win32_code].error_code))
		spec_ptr = GEN_ErrorList_Win32 + win32_code;
	else {
		for (count_1 = 0; count_1 < GEN_ErrorCount_Win32; count_1++) {
			if (win32_code == GEN_ErrorList_Win32[count_1].error_code) {
				spec_ptr = GEN_ErrorList_Win32 + count_1;
				break;
         }
		}
	}

	return(spec_ptr);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	GEN_GetLastErrorPtr_Win32

	SYNOPSIS		:	return_ptr = GEN_GetLastErrorPtr_Win32();

						const GEN_ERROR_SPEC *return_ptr;

	DESCRIPTION	:	Gets a pointer the ''GEN_ERROR_SPEC'' error description
						structure corresponding to the last Win32 operating system
						(as encoded in the return from the function
						``GetLastError()``).

   PARAMETERS  :  Void.

   RETURNS     :  Returns a pointer to the ''GEN_ERROR_SPEC'' error
						description structure corresponding to the return value of
						``GetLastError()``.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	GEN_GetLastErrorPtr
						GEN_GetErrorPtr_Win32

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2014 Michael L. Brock

	OUTPUT INDEX:	GEN_GetLastErrorPtr_Win32
						Error Description Functions:GEN_GetLastErrorPtr_Win32
						Windows Functions:GEN_GetLastErrorPtr_Win32
						GENFUNCS:Functions:GEN_GetLastErrorPtr_Win32
						GENFUNCS:Error Description Functions:GEN_GetLastErrorPtr_Win32
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_GetLastErrorPtr_Win32

	PUBLISH NAME:	GEN_GetLastErrorPtr_Win32

	ENTRY CLASS	:	Error Description Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
const GEN_ERROR_SPEC *GEN_GetLastErrorPtr_Win32(void)
#else
const GEN_ERROR_SPEC *GEN_GetLastErrorPtr_Win32()
#endif /* #ifndef NARGS */
{
	return(GEN_GetErrorPtr_Win32(GetLastError()));
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	GEN_AppendErrorString_Win32

	SYNOPSIS		:	return_ptr = char *GEN_AppendErrorString_Win32(win32_code,
							long_flag, max_text, error_text);

						char         *return_ptr;

						int           win32_code;

						int           long_flag;

						unsigned int  max_text;

						char         *error_text;

	DESCRIPTION	:	Appends text descriptive of the error corresponding to the
						specified Win32 error code to a string.

   PARAMETERS  :  Parameters to this function are as follows:

						(.) ``win32_code`` is the Win32 error code for which the
						function is to append a text description.

						(.) ``long_flag`` indicates to the function whether short
						or long error descriptions are to be used. If ``long_flag``
						is zero then only the short error description will be used.
						If ``long_flag`` is non-zero, then the long error
						description will be appended after the short error
						description.

						(.) ``max_text`` is the maximum length to which the function
						is to permit the appended string ``error_text`` to grow.

						(.) ``error_text`` is a pointer to a string to which the
						function is to append text descriptive of the error.

   RETURNS     :	The ``error_text`` parameter is returned.

	NOTES			:	If ``win32_code`` is not a valid Win32 error code, the
						function will append the error description as follows:

						<|-|> Invalid Win32 error code (``error-code-number``)

	CAVEATS		:	

	SEE ALSO		:	GEN_AppendErrorString
						GEN_AppendLastErrorString_Win32
						GEN_GetErrorString_Win32

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2014 Michael L. Brock

	OUTPUT INDEX:	GEN_AppendErrorString_Win32
						Error Description Functions:GEN_AppendErrorString_Win32
						Windows Functions:GEN_AppendErrorString_Win32
						GENFUNCS:Functions:GEN_AppendErrorString_Win32
						GENFUNCS:Error Description Functions:GEN_AppendErrorString_Win32
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_AppendErrorString_Win32

	PUBLISH NAME:	GEN_AppendErrorString_Win32

	ENTRY CLASS	:	Error Description Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *GEN_AppendErrorString_Win32(int win32_code, int long_flag,
	unsigned int max_text, char *error_text)
#else
char *GEN_AppendErrorString_Win32(win32_code, long_flag, max_text, error_text)
int           win32_code;
int           long_flag;
unsigned int  max_text;
char         *error_text;
#endif /* #ifndef NARGS */
{
	unsigned int error_length;

	if ((error_length = strlen(error_text)) < max_text)
		GEN_GetErrorString_Win32(win32_code, long_flag, max_text - error_length,
			error_text + error_length);

	return(error_text);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	GEN_AppendLastErrorString_Win32

	SYNOPSIS		:	return_ptr = GEN_AppendLastErrorString_Win32(long_flag,
							max_text, error_text);

						char         *return_ptr;

						int           long_flag;

						unsigned int  max_text;

						char         *error_text;

	DESCRIPTION	:	Appends text descriptive of the Win32 error corresponding
						to the last Windows operating system error (as encoded in
						the return value of the function ``GetLastError()``).

   PARAMETERS  :  Parameters to this function are as follows:

						(.) ``long_flag`` indicates to the function whether short
						or long error descriptions are to be used. If ``long_flag``
						is zero then only the short error description will be used.
						If ``long_flag`` is non-zero, then the long error
						description will be appended after the short error
						description.

						(.) ``max_text`` is the maximum length to which the function
						is to permit the appended string ``error_text`` to grow.

						(.) ``error_text`` is a pointer to a string to which the
						function is to append text descriptive of the error.

   RETURNS     :	The ``error_text`` parameter is returned.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	GEN_AppendLastErrorString
						GEN_AppendErrorString_Win32
						GEN_GetLastErrorString_Win32

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2014 Michael L. Brock

	OUTPUT INDEX:	GEN_AppendLastErrorString_Win32
						Error Description Functions:GEN_AppendLastErrorString_Win32
						Windows Functions:GEN_AppendLastErrorString_Win32
						GENFUNCS:Functions:GEN_AppendLastErrorString_Win32
						GENFUNCS:Error Description Functions:GEN_AppendLastErrorString_Win32
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_AppendLastErrorString_Win32

	PUBLISH NAME:	GEN_AppendLastErrorString_Win32

	ENTRY CLASS	:	Error Description Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *GEN_AppendLastErrorString_Win32(int long_flag, unsigned int max_text,
	char *error_text)
#else
char *GEN_AppendLastErrorString_Win32(long_flag, max_text, error_text)
int           long_flag;
unsigned int  max_text;
char         *error_text;
#endif /* #ifndef NARGS */
{
	return(GEN_AppendErrorString_Win32(GetLastError(), long_flag, max_text,
		error_text));
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	GEN_GetErrorString_Win32

	SYNOPSIS		:	return_ptr = GEN_GetErrorString_Win32(win32_code, long_flag,
							max_text, error_text);

						char         *return_ptr;

						int           win32_code;

						int           long_flag;

						unsigned int  max_text;

						char         *error_text;

	DESCRIPTION	:	Copies text descriptive of the error corresponding to the
						specified Win32 error code to a string.

   PARAMETERS  :  Parameters to this function are as follows:

						(.) ``win32_code`` is the Win32 error code for which the
						function is to copy a text description.

						(.) ``long_flag`` indicates to the function whether short
						or long error descriptions are to be used. If ``long_flag``
						is zero then only the short error description will be used.
						If ``long_flag`` is non-zero, then the long error
						description will be copied after the short error
						description.

						(.) ``max_text`` is the maximum length to which the function
						is to permit the copied string ``error_text`` to grow.

						(.) ``error_text`` is a pointer to the string into which the
						function is to copy text descriptive of the error.

   RETURNS     :	The ``error_text`` parameter is returned.

	NOTES			:	If ``win32_code`` is not a valid error code, the function
						will copy the error description as follows:

						<|-|> Invalid Win32 error code (``error-code-number``)

	CAVEATS		:	

	SEE ALSO		:	GEN_GetErrorString
						GEN_GetLastErrorString_Win32
						GEN_AppendErrorString_Win32

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2014 Michael L. Brock

	OUTPUT INDEX:	GEN_GetErrorString_Win32
						Error Description Functions:GEN_GetErrorString_Win32
						Windows Functions:GEN_GetErrorString_Win32
						GENFUNCS:Functions:GEN_GetErrorString_Win32
						GENFUNCS:Error Description Functions:GEN_GetErrorString_Win32
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_GetErrorString_Win32

	PUBLISH NAME:	GEN_GetErrorString_Win32

	ENTRY CLASS	:	Error Description Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *GEN_GetErrorString_Win32(int win32_code, int long_flag,
	unsigned int max_text, char *error_text)
#else
char *GEN_GetErrorString_Win32(win32_code, long_flag, max_text, error_text)
int           win32_code;
int           long_flag;
unsigned int  max_text;
char         *error_text;
#endif /* #ifndef NARGS */
{
	
	const GEN_ERROR_SPEC *spec_ptr;
	char                  buffer[4196];
	char                  number_buffer[STR_VAL2STR_MAX_LEN + 2];

	if ((spec_ptr = GEN_GetErrorPtr_Win32(win32_code)) != NULL) {
		strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcat(strcpy(buffer,
			"Win32 error code "),
			val2str(((unsigned long) win32_code), 0, 10, NULL, number_buffer)),
			" ("), spec_ptr->error_name), " --- "),
			spec_ptr->short_description), ") "),
			(long_flag && *spec_ptr->long_description) ? " " : ""),
			(long_flag && *spec_ptr->long_description) ?
			spec_ptr->long_description : "");
	}
	else
		oneblank(strcat(strcat(strcpy(buffer, "Invalid Win32 error code ("),
			val2str(((unsigned long) abs(win32_code)), win32_code, 10, NULL,
			number_buffer)), ")"));

	if ((!max_text) || (max_text >= strlen(buffer)))
		strcpy(error_text, oneblank(buffer));
	else
		nstrcpy(error_text, oneblank(buffer), max_text);

	return(error_text);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	GEN_GetLastErrorString_Win32

	SYNOPSIS		:	return_ptr = GEN_GetLastErrorString_Win32(long_flag, max_text,
							error_text);

						char         *return_ptr;

						int           long_flag;

						unsigned int  max_text;

						char         *error_text;

	DESCRIPTION	:	Copies text descriptive of the error corresponding to the
						last Win32 operating system error (as encoded in the return
						value of the function ``GetLastError()``).

   PARAMETERS  :  Parameters to this function are as follows:

						(.) ``long_flag`` indicates to the function whether short
						or long error descriptions are to be used. If ``long_flag``
						is zero then only the short error description will be used.
						If ``long_flag`` is non-zero, then the long error
						description will be copied after the short error
						description.

						(.) ``max_text`` is the maximum length to which the function
						is to permit the copied string ``error_text`` to grow.

						(.) ``error_text`` is a pointer to the string into which the
						function is to copy text descriptive of the error.

   RETURNS     :	The ``error_text`` parameter is returned.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	GEN_GetLastErrorString
						GEN_GetErrorString_Win32
						GEN_AppendLastErrorString_Win32

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2014 Michael L. Brock

	OUTPUT INDEX:	GEN_GetLastErrorString_Win32
						Error Description Functions:GEN_GetLastErrorString_Win32
						Windows Functions:GEN_GetLastErrorString_Win32
						GENFUNCS:Functions:GEN_GetLastErrorString_Win32
						GENFUNCS:Error Description Functions:GEN_GetLastErrorString_Win32
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_GetLastErrorString_Win32

	PUBLISH NAME:	GEN_GetLastErrorString_Win32

	ENTRY CLASS	:	Error Description Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *GEN_GetLastErrorString_Win32(int long_flag, unsigned int max_text,
	char *error_text)
#else
char *GEN_GetLastErrorString_Win32(long_flag, max_text, error_text)
int           long_flag;
unsigned int  max_text;
char         *error_text;
#endif /* #ifndef NARGS */
{
	return(GEN_GetErrorString_Win32(GetLastError(), long_flag, max_text,
		error_text));
}
/* *********************************************************************** */
#endif /* #ifdef _Windows */

#ifdef TEST_MAIN

#include <stdio.h>

#ifdef __MSDOS__
COMPAT_EXTERN_DATA_DECL unsigned int _stklen = 16384;
#endif /* __MSDOS__ */

COMPAT_FN_DECL(       int  main, (int, char **));
COMPAT_FN_DECL_STATIC(void DoUsage, (char *, char *, int));

#ifdef _Windows
COMPAT_FN_DECL_STATIC(int GEN_ERROR_CreateWin32List, (char *error_text));
#endif /* #ifdef _Windows */

/*	***********************************************************************	*/
#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int          return_code = GENFUNCS_SUCCESS;
	int          count_1     = 0;
	int          count_2     = 0;
	int          long_flag   = 0;
	unsigned int max_text    = 0;
	unsigned int longest_1   = 0;
	unsigned int longest_2   = 0;
	int          length;
	char         error_text[4096];

	fprintf(stderr, "Test routine for 'GEN_GetErrorString()'\n");
	fprintf(stderr, "---- ------- --- ----------------------\n\n");

	for (count_1 = 0; count_1 < GEN_ErrorCount; count_1++) {
		length    = strlen(GEN_GetErrorString(GEN_ErrorList[count_1].error_code,
			0, 0, error_text));
		longest_1 = (longest_1 > ((unsigned int) length)) ? longest_1 :
			((unsigned int) length);
		length    = strlen(GEN_GetErrorString(GEN_ErrorList[count_1].error_code,
			1, 0, error_text));
		longest_2 = (longest_2 > ((unsigned int) length)) ? longest_2 :
			((unsigned int) length);
		count_1++;
	}

#ifdef _Windows
	printf("Longest Short Message non-Win32: %u bytes\n", longest_1);
	printf("Longest Long Message  non-Win32: %u bytes\n", longest_2);
#else
	printf("Longest Short Message: %u bytes\n", longest_1);
	printf("Longest Long Message : %u bytes\n", longest_2);
#endif /* #ifdef _Windows */

	for (count_1 = 1; count_1 < argc; count_1++) {
		if (!strnicmp("-LONG=", argv[count_1], 6)) {
			if ((!stricmp(argv[count_1] + 6, "ON")) ||
				(!stricmp(argv[count_1] + 6, "YES")) ||
				(!stricmp(argv[count_1] + 6, "TRUE")))
				long_flag = 1;
			else if ((!stricmp(argv[count_1] + 6, "OFF")) ||
				(!stricmp(argv[count_1] + 6, "NO")) ||
				(!stricmp(argv[count_1] + 6, "FALSE")))
				long_flag = 0;
			else
				DoUsage(argv[0], "Invalid '-LONG=' toggle", 22);
		}
		else if ((!strnicmp("-MAX=", argv[count_1], 5)) &&
			(strlen(argv[count_1]) > 5) && isdigit(argv[count_1][5]))
			max_text = atoi(argv[count_1] + 5);
		else if (!stricmp("-ALL", argv[count_1])) {
			printf("-----------------------------------------------------\n");
			for (count_2 = 0; count_2 < GEN_ErrorCount; count_2++)
				printf("[%05u]:%s\n", count_2,
					GEN_GetErrorString(GEN_ErrorList[count_2].error_code,
					long_flag, max_text, error_text));
			printf("-----------------------------------------------------\n");
		}
		else if ((!stricmp("-HELP", argv[count_1])) ||
			(!stricmp("-H", argv[count_1])))
			DoUsage(argv[0], "Help request noted.", 0);
		else
			printf("%d ---> %s\n", atoi(argv[count_1]),
				GEN_GetErrorString(atoi(argv[count_1]), long_flag,
				max_text, error_text));
	}

#ifdef _Windows
	longest_1 = 0;
	longest_2 = 0;

	for (count_1 = 0; count_1 < GEN_ErrorCount; count_1++) {
		length    = strlen(GEN_GetErrorString_Win32(
			GEN_ErrorList_Win32[count_1].error_code, 0, 0, error_text));
		longest_1 = (longest_1 > ((unsigned int) length)) ? longest_1 :
			((unsigned int) length);
		length    = strlen(GEN_GetErrorString_Win32(
			GEN_ErrorList_Win32[count_1].error_code, 1, 0, error_text));
		longest_2 = (longest_2 > ((unsigned int) length)) ? longest_2 :
			((unsigned int) length);
		count_1++;
	}

	printf("Longest Short Message Win32    : %u bytes\n", longest_1);
	printf("Longest Long Message  Win32    : %u bytes\n", longest_2);

	for (count_1 = 1; count_1 < argc; count_1++) {
		if (!strnicmp("-LONG=", argv[count_1], 6)) {
			if ((!stricmp(argv[count_1] + 6, "ON")) ||
				(!stricmp(argv[count_1] + 6, "YES")) ||
				(!stricmp(argv[count_1] + 6, "TRUE")))
				long_flag = 1;
			else if ((!stricmp(argv[count_1] + 6, "OFF")) ||
				(!stricmp(argv[count_1] + 6, "NO")) ||
				(!stricmp(argv[count_1] + 6, "FALSE")))
				long_flag = 0;
			else
				DoUsage(argv[0], "Invalid '-LONG=' toggle", 22);
		}
		else if ((!strnicmp("-MAX=", argv[count_1], 5)) &&
			(strlen(argv[count_1]) > 5) && isdigit(argv[count_1][5]))
			max_text = atoi(argv[count_1] + 5);
		else if (!stricmp("-ALL", argv[count_1])) {
			printf("-----------------------------------------------------\n");
			for (count_2 = 0; count_2 < GEN_ErrorCount_Win32; count_2++)
				printf("[%05u]:%s\n", count_2,
					GEN_GetErrorString_Win32(GEN_ErrorList_Win32[count_2].error_code,
					long_flag, max_text, error_text));
			printf("-----------------------------------------------------\n");
		}
		else if ((!stricmp("-HELP", argv[count_1])) ||
			(!stricmp("-H", argv[count_1])))
			DoUsage(argv[0], "Help request noted.", 0);
		else
			printf("%d ---> %s\n", atoi(argv[count_1]),
				GEN_GetErrorString_Win32(atoi(argv[count_1]), long_flag,
				max_text, error_text));
	}
#endif /* #ifdef _Windows */

#ifdef _Windows
	return_code = GEN_ERROR_CreateWin32List(error_text);
#endif /* #ifdef _Windows */

	if (return_code != GENFUNCS_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void DoUsage(char *prog, char *exit_text, int exit_code)
#else
static void DoUsage(prog, exit_text, exit_code)
char *prog;
char *exit_text;
int   exit_code;
#endif /* #ifndef NARGS */
{
	prog = (strchr(prog, '\\')) ? strchr(prog, '\\') + 1 : prog;

	if (*exit_text)
		fprintf(stderr, "%s\n\n", exit_text);

	fprintf(stderr, "USAGE: %s %s %s %s %s [ %s . . . ]\n", prog,
		"[ -all ]",
		"[ -long={ON|OFF|YES|NO|TRUE|FALSE} ]",
		"[ -max=<max-length-of-string> ]",
		"<errno-number>", "<errno-number>");

	exit(exit_code);
}
/*	***********************************************************************	*/

#ifdef _Windows
/*	***********************************************************************	*/
static const GEN_ERROR_SPEC SRC_GEN_ErrorList_Win32[] = {
	{	ERROR_SUCCESS,						"ERROR_SUCCESS",
		"The operation completed successfully.", "The operation completed successfully."	},
	{	ERROR_INVALID_FUNCTION,			"ERROR_INVALID_FUNCTION",
		"Incorrect function.",	"Incorrect function."	},
	{	ERROR_FILE_NOT_FOUND,			"ERROR_FILE_NOT_FOUND",
		"The system cannot find the file specified.",	"The system cannot find the file specified."	},
	{	ERROR_PATH_NOT_FOUND,			"ERROR_PATH_NOT_FOUND",
		"The system cannot find the path specified.",	"The system cannot find the path specified."	},
	{	ERROR_TOO_MANY_OPEN_FILES,			"ERROR_TOO_MANY_OPEN_FILES",
		"The system cannot open the file.",	NULL	},
	{	ERROR_ACCESS_DENIED,			"ERROR_ACCESS_DENIED",
		"Access is denied.",	NULL	},
	{	ERROR_INVALID_HANDLE,			"ERROR_INVALID_HANDLE",
		"The handle is invalid.",	NULL	},
	{	ERROR_ARENA_TRASHED,			"ERROR_ARENA_TRASHED",
		"The storage control blocks were destroyed.",	NULL	},
	{	ERROR_NOT_ENOUGH_MEMORY,			"ERROR_NOT_ENOUGH_MEMORY",
		"Not enough storage is available to process this command.",	NULL	},
	{	ERROR_INVALID_BLOCK,			"ERROR_INVALID_BLOCK",
		"The storage control block address is invalid.",	NULL	},
	{	ERROR_BAD_ENVIRONMENT,			"ERROR_BAD_ENVIRONMENT",
		"The environment is incorrect.",	NULL	},
	{	ERROR_BAD_FORMAT,			"ERROR_BAD_FORMAT",
		"An attempt was made to load a program with an incorrect format.",	NULL	},
	{	ERROR_INVALID_ACCESS,			"ERROR_INVALID_ACCESS",
		"The access code is invalid.",	NULL	},
	{	ERROR_INVALID_DATA,			"ERROR_INVALID_DATA",
		"The data is invalid.",	NULL	},
	{	ERROR_OUTOFMEMORY,			"ERROR_OUTOFMEMORY",
		"Not enough storage is available to complete this operation.",	NULL	},
	{	ERROR_INVALID_DRIVE,			"ERROR_INVALID_DRIVE",
		"The system cannot find the drive specified.",	NULL	},
	{	ERROR_CURRENT_DIRECTORY,			"ERROR_CURRENT_DIRECTORY",
		"The directory cannot be removed.",	NULL	},
	{	ERROR_NOT_SAME_DEVICE,			"ERROR_NOT_SAME_DEVICE",
		"The system cannot move the file to a different disk drive.",	NULL	},
	{	ERROR_NO_MORE_FILES,			"ERROR_NO_MORE_FILES",
		"There are no more files.",	NULL	},
	{	ERROR_WRITE_PROTECT,			"ERROR_WRITE_PROTECT",
		"The media is write protected.",	NULL	},
	{	ERROR_BAD_UNIT,			"ERROR_BAD_UNIT",
		"The system cannot find the device specified.",	NULL	},
	{	ERROR_NOT_READY,			"ERROR_NOT_READY",
		"The device is not ready.",	NULL	},
	{	ERROR_BAD_COMMAND,			"ERROR_BAD_COMMAND",
		"The device does not recognize the command.",	NULL	},
	{	ERROR_CRC,			"ERROR_CRC",
		"Data error (cyclic redundancy check).",	NULL	},
	{	ERROR_BAD_LENGTH,			"ERROR_BAD_LENGTH",
		"The program issued a command but the command length is incorrect.",	NULL	},
	{	ERROR_SEEK,			"ERROR_SEEK",
		"The drive cannot locate a specific area or track on the disk.",	NULL	},
	{	ERROR_NOT_DOS_DISK,			"ERROR_NOT_DOS_DISK",
		"The specified disk or diskette cannot be accessed.",	NULL	},
	{	ERROR_SECTOR_NOT_FOUND,			"ERROR_SECTOR_NOT_FOUND",
		"The drive cannot find the sector requested.",	NULL	},
	{	ERROR_OUT_OF_PAPER,			"ERROR_OUT_OF_PAPER",
		"The printer is out of paper.",	NULL	},
	{	ERROR_WRITE_FAULT,			"ERROR_WRITE_FAULT",
		"The system cannot write to the specified device.",	NULL	},
	{	ERROR_READ_FAULT,			"ERROR_READ_FAULT",
		"The system cannot read from the specified device.",	NULL	},
	{	ERROR_GEN_FAILURE,			"ERROR_GEN_FAILURE",
		"A device attached to the system is not functioning.",	NULL	},
	{	ERROR_SHARING_VIOLATION,			"ERROR_SHARING_VIOLATION",
		"The process cannot access the file because it is being used by another process.",	NULL	},
	{	ERROR_LOCK_VIOLATION,			"ERROR_LOCK_VIOLATION",
		"The process cannot access the file because another process has locked a portion of the file.",	NULL	},
	{	ERROR_WRONG_DISK,			"ERROR_WRONG_DISK",
		"The wrong diskette is in the drive.",	NULL	},
	{	ERROR_SHARING_BUFFER_EXCEEDED,			"ERROR_SHARING_BUFFER_EXCEEDED",
		"Too many files opened for sharing.",	NULL	},
	{	ERROR_HANDLE_EOF,			"ERROR_HANDLE_EOF",
		"Reached the end of the file.",	NULL	},
	{	ERROR_HANDLE_DISK_FULL,			"ERROR_HANDLE_DISK_FULL",
		"The disk is full.",	NULL	},
	{	ERROR_NOT_SUPPORTED,			"ERROR_NOT_SUPPORTED",
		"The network request is not supported.",	NULL	},
	{	ERROR_REM_NOT_LIST,			"ERROR_REM_NOT_LIST",
		"The remote computer is not available.",	NULL	},
	{	ERROR_DUP_NAME,			"ERROR_DUP_NAME",
		"A duplicate name exists on the network.",	NULL	},
	{	ERROR_BAD_NETPATH,			"ERROR_BAD_NETPATH",
		"The network path was not found.",	NULL	},
	{	ERROR_NETWORK_BUSY,			"ERROR_NETWORK_BUSY",
		"The network is busy.",	NULL	},
	{	ERROR_DEV_NOT_EXIST,			"ERROR_DEV_NOT_EXIST",
		"The specified network resource or device is no longer available.",	NULL	},
	{	ERROR_TOO_MANY_CMDS,			"ERROR_TOO_MANY_CMDS",
		"The network BIOS command limit has been reached.",	NULL	},
	{	ERROR_ADAP_HDW_ERR,			"ERROR_ADAP_HDW_ERR",
		"A network adapter hardware error occurred.",	NULL	},
	{	ERROR_BAD_NET_RESP,			"ERROR_BAD_NET_RESP",
		"The specified server cannot perform the requested operation.",	NULL	},
	{	ERROR_UNEXP_NET_ERR,			"ERROR_UNEXP_NET_ERR",
		"An unexpected network error occurred.",	NULL	},
	{	ERROR_BAD_REM_ADAP,			"ERROR_BAD_REM_ADAP",
		"The remote adapter is not compatible.",	NULL	},
	{	ERROR_PRINTQ_FULL,			"ERROR_PRINTQ_FULL",
		"The printer queue is full.",	NULL	},
	{	ERROR_NO_SPOOL_SPACE,			"ERROR_NO_SPOOL_SPACE",
		"Space to store the file waiting to be printed is not available on the server.",	NULL	},
	{	ERROR_PRINT_CANCELLED,			"ERROR_PRINT_CANCELLED",
		"Your file waiting to be printed was deleted.",	"Your file waiting to be printed was deleted."	},
	{	ERROR_NETNAME_DELETED,			"ERROR_NETNAME_DELETED",
		"The specified network name is no longer available.",	NULL	},
	{	ERROR_NETWORK_ACCESS_DENIED,			"ERROR_NETWORK_ACCESS_DENIED",
		"Network access is denied.",	NULL	},
	{	ERROR_BAD_DEV_TYPE,			"ERROR_BAD_DEV_TYPE",
		"The network resource type is not correct.",	NULL	},
	{	ERROR_BAD_NET_NAME,			"ERROR_BAD_NET_NAME",
		"The network name cannot be found.",	NULL	},
	{	ERROR_TOO_MANY_NAMES,			"ERROR_TOO_MANY_NAMES",
		"The name limit for the local computer network adapter card was exceeded.",	NULL	},
	{	ERROR_TOO_MANY_SESS,			"ERROR_TOO_MANY_SESS",
		"The network BIOS session limit was exceeded.",	NULL	},
	{	ERROR_SHARING_PAUSED,			"ERROR_SHARING_PAUSED",
		"The remote server has been paused or is in the process of being started.",	NULL	},
	{	ERROR_REQ_NOT_ACCEP,			"ERROR_REQ_NOT_ACCEP",
		"No more connections can be made to this remote computer at this time because there are already as many connections as the computer can accept.",	NULL	},
	{	ERROR_REDIR_PAUSED,			"ERROR_REDIR_PAUSED",
		"The specified printer or disk device has been paused.",	NULL	},
	{	ERROR_FILE_EXISTS,			"ERROR_FILE_EXISTS",
		"The file exists.",	NULL	},
	{	ERROR_CANNOT_MAKE,			"ERROR_CANNOT_MAKE",
		"The directory or file cannot be created.",	NULL	},
	{	ERROR_FAIL_I24,			"ERROR_FAIL_I24",
		"Fail on INT 24.",	NULL	},
	{	ERROR_OUT_OF_STRUCTURES,			"ERROR_OUT_OF_STRUCTURES",
		"Storage to process this request is not available.",	NULL	},
	{	ERROR_ALREADY_ASSIGNED,			"ERROR_ALREADY_ASSIGNED",
		"The local device name is already in use.",	NULL	},
	{	ERROR_INVALID_PASSWORD,			"ERROR_INVALID_PASSWORD",
		"The specified network password is not correct.",	NULL	},
	{	ERROR_INVALID_PARAMETER,			"ERROR_INVALID_PARAMETER",
		"The parameter is incorrect.",	NULL	},
	{	ERROR_NET_WRITE_FAULT,			"ERROR_NET_WRITE_FAULT",
		"A write fault occurred on the network.",	NULL	},
	{	ERROR_NO_PROC_SLOTS,			"ERROR_NO_PROC_SLOTS",
		"The system cannot start another process at this time.",	NULL	},
	{	ERROR_TOO_MANY_SEMAPHORES,			"ERROR_TOO_MANY_SEMAPHORES",
		"Cannot create another system semaphore.",	NULL	},
	{	ERROR_EXCL_SEM_ALREADY_OWNED,			"ERROR_EXCL_SEM_ALREADY_OWNED",
		"The exclusive semaphore is owned by another process.",	NULL	},
	{	ERROR_SEM_IS_SET,			"ERROR_SEM_IS_SET",
		"The semaphore is set and cannot be closed.",	NULL	},
	{	ERROR_TOO_MANY_SEM_REQUESTS,			"ERROR_TOO_MANY_SEM_REQUESTS",
		"The semaphore cannot be set again.",	NULL	},
	{	ERROR_INVALID_AT_INTERRUPT_TIME,			"ERROR_INVALID_AT_INTERRUPT_TIME",
		"Cannot request exclusive semaphores at interrupt time.",	NULL	},
	{	ERROR_SEM_OWNER_DIED,			"ERROR_SEM_OWNER_DIED",
		"The previous ownership of this semaphore has ended.",	NULL	},
	{	ERROR_SEM_USER_LIMIT,			"ERROR_SEM_USER_LIMIT",
		"Insert the diskette for drive.",	"The diskette must be inserted in the drive."	},
	{	ERROR_DISK_CHANGE,			"ERROR_DISK_CHANGE",
		"The program stopped because an alternate diskette was not inserted.",	NULL	},
	{	ERROR_DRIVE_LOCKED,			"ERROR_DRIVE_LOCKED",
		"The disk is in use or locked by another process.",	NULL	},
	{	ERROR_BROKEN_PIPE,			"ERROR_BROKEN_PIPE",
		"The pipe has been ended.",	NULL	},
	{	ERROR_OPEN_FAILED,			"ERROR_OPEN_FAILED",
		"The system cannot open the device or file specified.",	NULL	},
	{	ERROR_BUFFER_OVERFLOW,			"ERROR_BUFFER_OVERFLOW",
		"The file name is too long.",	NULL	},
	{	ERROR_DISK_FULL,			"ERROR_DISK_FULL",
		"There is not enough space on the disk.",	NULL	},
	{	ERROR_NO_MORE_SEARCH_HANDLES,			"ERROR_NO_MORE_SEARCH_HANDLES",
		"No more internal file identifiers available.",	NULL	},
	{	ERROR_INVALID_TARGET_HANDLE,			"ERROR_INVALID_TARGET_HANDLE",
		"The target internal file identifier is incorrect.",	NULL	},
	{	ERROR_INVALID_CATEGORY,			"ERROR_INVALID_CATEGORY",
		"The IOCTL call made by the application program is not correct.",	NULL	},
	{	ERROR_INVALID_VERIFY_SWITCH,			"ERROR_INVALID_VERIFY_SWITCH",
		"The verify-on-write switch parameter value is not correct.",	NULL	},
	{	ERROR_BAD_DRIVER_LEVEL,			"ERROR_BAD_DRIVER_LEVEL",
		"The system does not support the command requested.",	NULL	},
	{	ERROR_CALL_NOT_IMPLEMENTED,			"ERROR_CALL_NOT_IMPLEMENTED",
		"This function is not supported on this system.",	NULL	},
	{	ERROR_SEM_TIMEOUT,			"ERROR_SEM_TIMEOUT",
		"The semaphore timeout period has expired.",	NULL	},
	{	ERROR_INSUFFICIENT_BUFFER,			"ERROR_INSUFFICIENT_BUFFER",
		"The data area passed to a system call is too small.",	NULL	},
	{	ERROR_INVALID_NAME,			"ERROR_INVALID_NAME",
		"The filename, directory name, or volume label syntax is incorrect.",	NULL	},
	{	ERROR_INVALID_LEVEL,			"ERROR_INVALID_LEVEL",
		"The system call level is not correct.",	NULL	},
	{	ERROR_NO_VOLUME_LABEL,			"ERROR_NO_VOLUME_LABEL",
		"The disk has no volume label.",	NULL	},
	{	ERROR_MOD_NOT_FOUND,			"ERROR_MOD_NOT_FOUND",
		"The specified module could not be found.",	NULL	},
	{	ERROR_PROC_NOT_FOUND,			"ERROR_PROC_NOT_FOUND",
		"The specified procedure could not be found.",	NULL	},
	{	ERROR_WAIT_NO_CHILDREN,			"ERROR_WAIT_NO_CHILDREN",
		"There are no child processes to wait for.",	"There are no child processes to wait for."	},
	{	ERROR_CHILD_NOT_COMPLETE,			"ERROR_CHILD_NOT_COMPLETE",
		"The application cannot be run in Win32 mode.",	"The application cannot be run in Win32 mode."	},
	{	ERROR_DIRECT_ACCESS_HANDLE,			"ERROR_DIRECT_ACCESS_HANDLE",
		"Attempt to use a file handle to an open disk partition for an operation other than raw disk I/O.",	NULL	},
	{	ERROR_NEGATIVE_SEEK,			"ERROR_NEGATIVE_SEEK",
		"An attempt was made to move the file pointer before the beginning of the file.",	NULL	},
	{	ERROR_SEEK_ON_DEVICE,			"ERROR_SEEK_ON_DEVICE",
		"The file pointer cannot be set on the specified device or file.",	NULL	},
	{	ERROR_IS_JOIN_TARGET,			"ERROR_IS_JOIN_TARGET",
		"A JOIN or SUBST command cannot be used for a drive that contains previously joined drives.",	NULL	},
	{	ERROR_IS_JOINED,			"ERROR_IS_JOINED",
		"An attempt was made to use a JOIN or SUBST command on a drive that has already been joined.",	NULL	},
	{	ERROR_IS_SUBSTED,			"ERROR_IS_SUBSTED",
		"An attempt was made to use a JOIN or SUBST command on a drive that has already been substituted.",	NULL	},
	{	ERROR_NOT_JOINED,			"ERROR_NOT_JOINED",
		"The system tried to delete the JOIN of a drive that is not joined.",	NULL	},
	{	ERROR_NOT_SUBSTED,			"ERROR_NOT_SUBSTED",
		"The system tried to delete the substitution of a drive that is not substituted.",	NULL	},
	{	ERROR_JOIN_TO_JOIN,			"ERROR_JOIN_TO_JOIN",
		"The system tried to join a drive to a directory on a joined drive.",	NULL	},
	{	ERROR_SUBST_TO_SUBST,			"ERROR_SUBST_TO_SUBST",
		"The system tried to substitute a drive to a directory on a substituted drive.",	NULL	},
	{	ERROR_JOIN_TO_SUBST,			"ERROR_JOIN_TO_SUBST",
		"The system tried to join a drive to a directory on a substituted drive.",	NULL	},
	{	ERROR_SUBST_TO_JOIN,			"ERROR_SUBST_TO_JOIN",
		"The system tried to SUBST a drive to a directory on a joined drive.",	NULL	},
	{	ERROR_BUSY_DRIVE,			"ERROR_BUSY_DRIVE",
		"The system cannot perform a JOIN or SUBST at this time.",	NULL	},
	{	ERROR_SAME_DRIVE,			"ERROR_SAME_DRIVE",
		"The system cannot join or substitute a drive to or for a directory on the same drive.",	NULL	},
	{	ERROR_DIR_NOT_ROOT,			"ERROR_DIR_NOT_ROOT",
		"The directory is not a subdirectory of the root directory.",	NULL	},
	{	ERROR_DIR_NOT_EMPTY,			"ERROR_DIR_NOT_EMPTY",
		"The directory is not empty.",	NULL	},
	{	ERROR_IS_SUBST_PATH,			"ERROR_IS_SUBST_PATH",
		"The path specified is being used in a substitute.",	NULL	},
	{	ERROR_IS_JOIN_PATH,			"ERROR_IS_JOIN_PATH",
		"Not enough resources are available to process this command.",	NULL	},
	{	ERROR_PATH_BUSY,			"ERROR_PATH_BUSY",
		"The path specified cannot be used at this time.",	NULL	},
	{	ERROR_IS_SUBST_TARGET,			"ERROR_IS_SUBST_TARGET",
		"An attempt was made to join or substitute a drive for which a directory on the drive is the target of a previous substitute.",	NULL	},
	{	ERROR_SYSTEM_TRACE,			"ERROR_SYSTEM_TRACE",
		"System trace information was not specified in your CONFIG.SYS file, or tracing is disallowed.",	NULL	},
	{	ERROR_INVALID_EVENT_COUNT,			"ERROR_INVALID_EVENT_COUNT",
		"The number of specified semaphore events for DosMuxSemWait is not correct.",	NULL	},
	{	ERROR_TOO_MANY_MUXWAITERS,			"ERROR_TOO_MANY_MUXWAITERS",
		"DosMuxSemWait did not execute; too many semaphores are already set.",	NULL	},
	{	ERROR_INVALID_LIST_FORMAT,			"ERROR_INVALID_LIST_FORMAT",
		"The DosMuxSemWait list is not correct.",	NULL	},
	{	ERROR_LABEL_TOO_LONG,			"ERROR_LABEL_TOO_LONG",
		"The volume label you entered exceeds the label character limit of the target file system.",	NULL	},
	{	ERROR_TOO_MANY_TCBS,			"ERROR_TOO_MANY_TCBS",
		"Cannot create another thread.",	NULL	},
	{	ERROR_SIGNAL_REFUSED,			"ERROR_SIGNAL_REFUSED",
		"The recipient process has refused the signal.",	NULL	},
	{	ERROR_DISCARDED,			"ERROR_DISCARDED",
		"The segment is already discarded and cannot be locked.",	NULL	},
	{	ERROR_NOT_LOCKED,			"ERROR_NOT_LOCKED",
		"The segment is already unlocked.",	NULL	},
	{	ERROR_BAD_THREADID_ADDR,			"ERROR_BAD_THREADID_ADDR",
		"The address for the thread ID is not correct.",	NULL	},
	{	ERROR_BAD_ARGUMENTS,			"ERROR_BAD_ARGUMENTS",
		"The argument string passed to DosExecPgm is not correct.",	NULL	},
	{	ERROR_BAD_PATHNAME,			"ERROR_BAD_PATHNAME",
		"The specified path is invalid.",	NULL	},
	{	ERROR_SIGNAL_PENDING,			"ERROR_SIGNAL_PENDING",
		"A signal is already pending.",	NULL	},
	{	ERROR_MAX_THRDS_REACHED,			"ERROR_MAX_THRDS_REACHED",
		"No more threads can be created in the system.",	NULL	},
	{	ERROR_LOCK_FAILED,			"ERROR_LOCK_FAILED",
		"Unable to lock a region of a file.",	NULL	},
	{	ERROR_BUSY,			"ERROR_BUSY",
		"The requested resource is in use.",	NULL	},
	{	ERROR_CANCEL_VIOLATION,			"ERROR_CANCEL_VIOLATION",
		"A lock request was not outstanding for the supplied cancel region.",	NULL	},
	{	ERROR_ATOMIC_LOCKS_NOT_SUPPORTED,			"ERROR_ATOMIC_LOCKS_NOT_SUPPORTED",
		"The file system does not support atomic changes to the lock type.",	NULL	},
	{	ERROR_INVALID_SEGMENT_NUMBER,			"ERROR_INVALID_SEGMENT_NUMBER",
		"The system detected a segment number that was not correct.",	NULL	},
	{	ERROR_INVALID_ORDINAL,			"ERROR_INVALID_ORDINAL",
		"The operating system cannot run .",	NULL	},
	{	ERROR_ALREADY_EXISTS,			"ERROR_ALREADY_EXISTS",
		"Cannot create a file when that file already exists.",	NULL	},
	{	ERROR_INVALID_FLAG_NUMBER,			"ERROR_INVALID_FLAG_NUMBER",
		"The flag passed is not correct.",	NULL	},
	{	ERROR_SEM_NOT_FOUND,			"ERROR_SEM_NOT_FOUND",
		"The specified system semaphore name was not found.",	NULL	},
	{	ERROR_INVALID_STARTING_CODESEG,			"ERROR_INVALID_STARTING_CODESEG",
		"The operating system cannot run the requested resource (invalid starting code seg).",	NULL	},
	{	ERROR_INVALID_STACKSEG,			"ERROR_INVALID_STACKSEG",
		"The operating system cannot run the requested resource (invalid starting stack seg).",	NULL	},
	{	ERROR_INVALID_MODULETYPE,			"ERROR_INVALID_MODULETYPE",
		"The operating system cannot run the requested resource (invalid module type).",	NULL	},
	{	ERROR_INVALID_EXE_SIGNATURE,			"ERROR_INVALID_EXE_SIGNATURE",
		"Cannot run EXE file in Win32 mode.",	"Cannot run EXE file in Win32 mode."	},
	{	ERROR_EXE_MARKED_INVALID,			"ERROR_EXE_MARKED_INVALID",
		"The operating system cannot run the requested resource (EXE marked as invalid).",	NULL	},
	{	ERROR_BAD_EXE_FORMAT,			"ERROR_BAD_EXE_FORMAT",
		"Has a bad EXE format --- not a valid Win32 application.",	NULL	},
	{	ERROR_ITERATED_DATA_EXCEEDS_64k,			"ERROR_ITERATED_DATA_EXCEEDS_64k",
		"The operating system cannot run the requested resource (iterated data exceeds 64K).",	NULL	},
	{	ERROR_INVALID_MINALLOCSIZE,			"ERROR_INVALID_MINALLOCSIZE",
		"The operating system cannot run the requested resource (invalid min alloc size).",	NULL	},
	{	ERROR_DYNLINK_FROM_INVALID_RING,			"ERROR_DYNLINK_FROM_INVALID_RING",
		"The operating system cannot run this application program.",	NULL	},
	{	ERROR_IOPL_NOT_ENABLED,			"ERROR_IOPL_NOT_ENABLED",
		"The operating system is not presently configured to run this application.",	NULL	},
	{	ERROR_INVALID_SEGDPL,			"ERROR_INVALID_SEGDPL",
		"The operating system cannot run the requested resource (invalid seg DPL).",	NULL	},
	{	ERROR_AUTODATASEG_EXCEEDS_64k,			"ERROR_AUTODATASEG_EXCEEDS_64k",
		"The operating system cannot run this application program.",	NULL	},
	{	ERROR_RING2SEG_MUST_BE_MOVABLE,			"ERROR_RING2SEG_MUST_BE_MOVABLE",
		"The code segment cannot be greater than or equal to 64K.",	NULL	},
	{	ERROR_RELOC_CHAIN_XEEDS_SEGLIM,			"ERROR_RELOC_CHAIN_XEEDS_SEGLIM",
		"The operating system cannot run the requested resource (reloc chain needs seg lim).",	NULL	},
	{	ERROR_INFLOOP_IN_RELOC_CHAIN,			"ERROR_INFLOOP_IN_RELOC_CHAIN",
		"The operating system cannot run the requested resource (INFLOOP in reloc chain).",	NULL	},
	{	ERROR_ENVVAR_NOT_FOUND,			"ERROR_ENVVAR_NOT_FOUND",
		"The system could not find the environment option that was entered.",	NULL	},
	{	ERROR_NO_SIGNAL_SENT,			"ERROR_NO_SIGNAL_SENT",
		"No process in the command subtree has a signal handler.",	NULL	},
	{	ERROR_FILENAME_EXCED_RANGE,			"ERROR_FILENAME_EXCED_RANGE",
		"The filename or extension is too long.",	NULL	},
	{	ERROR_RING2_STACK_IN_USE,			"ERROR_RING2_STACK_IN_USE",
		"The ring 2 stack is in use.",	NULL	},
	{	ERROR_META_EXPANSION_TOO_LONG,			"ERROR_META_EXPANSION_TOO_LONG",
		"The global filename characters, * or ?, are entered incorrectly or too many global filename characters are specified.",	NULL	},
	{	ERROR_INVALID_SIGNAL_NUMBER,			"ERROR_INVALID_SIGNAL_NUMBER",
		"The signal being posted is not correct.",	NULL	},
	{	ERROR_THREAD_1_INACTIVE,			"ERROR_THREAD_1_INACTIVE",
		"The signal handler cannot be set.",	NULL	},
	{	ERROR_LOCKED,			"ERROR_LOCKED",
		"The segment is locked and cannot be reallocated.",	NULL	},
	{	ERROR_TOO_MANY_MODULES,			"ERROR_TOO_MANY_MODULES",
		"Too many dynamic-link modules are attached to this program or dynamic-link module.",	NULL	},
	{	ERROR_NESTING_NOT_ALLOWED,			"ERROR_NESTING_NOT_ALLOWED",
		"Can't nest calls to LoadModule.",	NULL	},
	{	ERROR_EXE_MACHINE_TYPE_MISMATCH,			"ERROR_EXE_MACHINE_TYPE_MISMATCH",
		"The image file is valid, but is for a machine type other than the current machine.",	NULL	},
	{	ERROR_BAD_PIPE,			"ERROR_BAD_PIPE",
		"The pipe state is invalid.",	NULL	},
	{	ERROR_PIPE_BUSY,			"ERROR_PIPE_BUSY",
		"All pipe instances are busy.",	NULL	},
	{	ERROR_NO_DATA,			"ERROR_NO_DATA",
		"The pipe is being closed.",	NULL	},
	{	ERROR_PIPE_NOT_CONNECTED,			"ERROR_PIPE_NOT_CONNECTED",
		"No process is on the other end of the pipe.",	NULL	},
	{	ERROR_MORE_DATA,			"ERROR_MORE_DATA",
		"More data is available.",	NULL	},
	{	ERROR_VC_DISCONNECTED,			"ERROR_VC_DISCONNECTED",
		"The session was canceled.",	NULL	},
	{	ERROR_INVALID_EA_NAME,			"ERROR_INVALID_EA_NAME",
		"The specified extended attribute name was invalid.",	NULL	},
	{	ERROR_EA_LIST_INCONSISTENT,			"ERROR_EA_LIST_INCONSISTENT",
		"The extended attributes are inconsistent.",	NULL	},
	{	ERROR_NO_MORE_ITEMS,			"ERROR_NO_MORE_ITEMS",
		"No more data is available.",	NULL	},
	{	ERROR_CANNOT_COPY,			"ERROR_CANNOT_COPY",
		"The copy functions cannot be used.",	NULL	},
	{	ERROR_DIRECTORY,			"ERROR_DIRECTORY",
		"The directory name is invalid.",	NULL	},
	{	ERROR_EAS_DIDNT_FIT,			"ERROR_EAS_DIDNT_FIT",
		"The extended attributes did not fit in the buffer.",	NULL	},
	{	ERROR_EA_FILE_CORRUPT,			"ERROR_EA_FILE_CORRUPT",
		"The extended attribute file on the mounted file system is corrupt.",	NULL	},
	{	ERROR_EA_TABLE_FULL,			"ERROR_EA_TABLE_FULL",
		"The extended attribute table file is full.",	NULL	},
	{	ERROR_INVALID_EA_HANDLE,			"ERROR_INVALID_EA_HANDLE",
		"The specified extended attribute handle is invalid.",	NULL	},
	{	ERROR_EAS_NOT_SUPPORTED,			"ERROR_EAS_NOT_SUPPORTED",
		"The mounted file system does not support extended attributes.",	NULL	},
	{	ERROR_NOT_OWNER,			"ERROR_NOT_OWNER",
		"Attempt to release mutex not owned by caller.",	NULL	},
	{	ERROR_TOO_MANY_POSTS,			"ERROR_TOO_MANY_POSTS",
		"Too many posts were made to a semaphore.",	NULL	},
	{	ERROR_PARTIAL_COPY,			"ERROR_PARTIAL_COPY",
		"Only part of a ReadProcessMemoty or WriteProcessMemory request was completed.",	NULL	},
	{	ERROR_OPLOCK_NOT_GRANTED,			"ERROR_OPLOCK_NOT_GRANTED",
		"The oplock request is denied.",	NULL	},
	{	ERROR_INVALID_OPLOCK_PROTOCOL,			"ERROR_INVALID_OPLOCK_PROTOCOL",
		"An invalid oplock acknowledgment was received by the system.",	NULL	},
	{	ERROR_MR_MID_NOT_FOUND,			"ERROR_MR_MID_NOT_FOUND",
		"The system cannot find message text for message number in the message file.",	NULL	},
	{	ERROR_INVALID_ADDRESS,			"ERROR_INVALID_ADDRESS",
		"Attempt to access invalid address.",	NULL	},
	{	ERROR_ARITHMETIC_OVERFLOW,			"ERROR_ARITHMETIC_OVERFLOW",
		"Arithmetic result exceeded 32 bits.",	NULL	},
	{	ERROR_PIPE_CONNECTED,			"ERROR_PIPE_CONNECTED",
		"There is a process on other end of the pipe.",	NULL	},
	{	ERROR_PIPE_LISTENING,			"ERROR_PIPE_LISTENING",
		"Waiting for a process to open the other end of the pipe.",	NULL	},
	{	ERROR_EA_ACCESS_DENIED,			"ERROR_EA_ACCESS_DENIED",
		"Access to the extended attribute was denied.",	NULL	},
	{	ERROR_OPERATION_ABORTED,			"ERROR_OPERATION_ABORTED",
		"The I/O operation has been aborted because of either a thread exit or an application request.",	NULL	},
	{	ERROR_IO_INCOMPLETE,			"ERROR_IO_INCOMPLETE",
		"Overlapped I/O event is not in a signaled state.",	NULL	},
	{	ERROR_IO_PENDING,			"ERROR_IO_PENDING",
		"Overlapped I/O operation is in progress.",	NULL	},
	{	ERROR_NOACCESS,			"ERROR_NOACCESS",
		"Invalid access to memory location.",	NULL	},
	{	ERROR_SWAPERROR,			"ERROR_SWAPERROR",
		"Error performing inpage operation.",	NULL	},
	{	ERROR_STACK_OVERFLOW,			"ERROR_STACK_OVERFLOW",
		"Recursion too deep; the stack overflowed.",	NULL	},
	{	ERROR_INVALID_MESSAGE,			"ERROR_INVALID_MESSAGE",
		"The window cannot act on the sent message.",	NULL	},
	{	ERROR_CAN_NOT_COMPLETE,			"ERROR_CAN_NOT_COMPLETE",
		"Cannot complete this function.",	NULL	},
	{	ERROR_INVALID_FLAGS,			"ERROR_INVALID_FLAGS",
		"Invalid flags.",	NULL	},
	{	ERROR_UNRECOGNIZED_VOLUME,			"ERROR_UNRECOGNIZED_VOLUME",
		"The volume does not contain a recognized file system. Please make sure that all required file system drivers are loaded and that the volume is not corrupted.",	NULL	},
	{	ERROR_FILE_INVALID,			"ERROR_FILE_INVALID",
		"The volume for a file has been externally altered so that the opened file is no longer valid.",	NULL	},
	{	ERROR_FULLSCREEN_MODE,			"ERROR_FULLSCREEN_MODE",
		"The requested operation cannot be performed in full-screen mode.",	NULL	},
	{	ERROR_NO_TOKEN,			"ERROR_NO_TOKEN",
		"An attempt was made to reference a token that does not exist.",	NULL	},
	{	ERROR_BADDB,			"ERROR_BADDB",
		"The configuration registry database is corrupt.",	NULL	},
	{	ERROR_BADKEY,			"ERROR_BADKEY",
		"The configuration registry key is invalid.",	NULL	},
	{	ERROR_CANTOPEN,			"ERROR_CANTOPEN",
		"The configuration registry key could not be opened.",	NULL	},
	{	ERROR_CANTREAD,			"ERROR_CANTREAD",
		"The configuration registry key could not be read.",	NULL	},
	{	ERROR_CANTWRITE,			"ERROR_CANTWRITE",
		"The configuration registry key could not be written.",	NULL	},
	{	ERROR_REGISTRY_RECOVERED,			"ERROR_REGISTRY_RECOVERED",
		"One of the files in the registry database had to be recovered by use of a log or alternate copy.  The recovery was successful.",	NULL	},
	{	ERROR_REGISTRY_CORRUPT,			"ERROR_REGISTRY_CORRUPT",
		"The registry is corrupted. The structure of one of the files that contains registry data is corrupted, or the system's image of the file in memory is corrupted, or the file could not be recovered because the alternate copy or log was absent or corrupted.",	NULL	},
	{	ERROR_REGISTRY_IO_FAILED,			"ERROR_REGISTRY_IO_FAILED",
		"An I/O operation initiated by the registry failed unrecoverably. The registry could not read in, or write out, or flush, one of the files that contain the system's image of the registry.",	NULL	},
	{	ERROR_NOT_REGISTRY_FILE,			"ERROR_NOT_REGISTRY_FILE",
		"The system has attempted to load or restore a file into the registry, but the specified file is not in a registry file format.",	NULL	},
	{	ERROR_KEY_DELETED,			"ERROR_KEY_DELETED",
		"Illegal operation attempted on a registry key that has been marked for deletion.",	NULL	},
	{	ERROR_NO_LOG_SPACE,			"ERROR_NO_LOG_SPACE",
		"System could not allocate the required space in a registry log.",	NULL	},
	{	ERROR_KEY_HAS_CHILDREN,			"ERROR_KEY_HAS_CHILDREN",
		"Cannot create a symbolic link in a registry key that already has subkeys or values.",	NULL	},
	{	ERROR_CHILD_MUST_BE_VOLATILE,			"ERROR_CHILD_MUST_BE_VOLATILE",
		"Cannot create a stable subkey under a volatile parent key.",	NULL	},
	{	ERROR_NOTIFY_ENUM_DIR,			"ERROR_NOTIFY_ENUM_DIR",
		"A notify change request is being completed and the information is not being returned in the caller's buffer. The caller now needs to enumerate the files to find the changes.",	NULL	},
	{	ERROR_DEPENDENT_SERVICES_RUNNING,			"ERROR_DEPENDENT_SERVICES_RUNNING",
		"A stop control has been sent to a service that other running services are dependent on.",	NULL	},
	{	ERROR_INVALID_SERVICE_CONTROL,			"ERROR_INVALID_SERVICE_CONTROL",
		"The requested control is not valid for this service.",	NULL	},
	{	ERROR_SERVICE_REQUEST_TIMEOUT,			"ERROR_SERVICE_REQUEST_TIMEOUT",
		"The service did not respond to the start or control request in a timely fashion.",	NULL	},
	{	ERROR_SERVICE_NO_THREAD,			"ERROR_SERVICE_NO_THREAD",
		"A thread could not be created for the service.",	NULL	},
	{	ERROR_SERVICE_DATABASE_LOCKED,			"ERROR_SERVICE_DATABASE_LOCKED",
		"The service database is locked.",	NULL	},
	{	ERROR_SERVICE_ALREADY_RUNNING,			"ERROR_SERVICE_ALREADY_RUNNING",
		"An instance of the service is already running.",	NULL	},
	{	ERROR_INVALID_SERVICE_ACCOUNT,			"ERROR_INVALID_SERVICE_ACCOUNT",
		"The account name is invalid or does not exist.",	NULL	},
	{	ERROR_SERVICE_DISABLED,			"ERROR_SERVICE_DISABLED",
		"The service cannot be started, either because it is disabled or because it has no enabled devices associated with it.",	NULL	},
	{	ERROR_CIRCULAR_DEPENDENCY,			"ERROR_CIRCULAR_DEPENDENCY",
		"Circular service dependency was specified.",	NULL	},
	{	ERROR_SERVICE_DOES_NOT_EXIST,			"ERROR_SERVICE_DOES_NOT_EXIST",
		"The specified service does not exist as an installed service.",	NULL	},
	{	ERROR_SERVICE_CANNOT_ACCEPT_CTRL,			"ERROR_SERVICE_CANNOT_ACCEPT_CTRL",
		"The service cannot accept control messages at this time.",	NULL	},
	{	ERROR_SERVICE_NOT_ACTIVE,			"ERROR_SERVICE_NOT_ACTIVE",
		"The service has not been started.",	NULL	},
	{	ERROR_FAILED_SERVICE_CONTROLLER_CONNECT,			"ERROR_FAILED_SERVICE_CONTROLLER_CONNECT",
		"The service process could not connect to the service controller.",	NULL	},
	{	ERROR_EXCEPTION_IN_SERVICE,			"ERROR_EXCEPTION_IN_SERVICE",
		"An exception occurred in the service when handling the control request.",	NULL	},
	{	ERROR_DATABASE_DOES_NOT_EXIST,			"ERROR_DATABASE_DOES_NOT_EXIST",
		"The database specified does not exist.",	NULL	},
	{	ERROR_SERVICE_SPECIFIC_ERROR,			"ERROR_SERVICE_SPECIFIC_ERROR",
		"The service has returned a service-specific error code.",	NULL	},
	{	ERROR_PROCESS_ABORTED,			"ERROR_PROCESS_ABORTED",
		"The process terminated unexpectedly.",	NULL	},
	{	ERROR_SERVICE_DEPENDENCY_FAIL,			"ERROR_SERVICE_DEPENDENCY_FAIL",
		"The dependency service or group failed to start.",	NULL	},
	{	ERROR_SERVICE_LOGON_FAILED,			"ERROR_SERVICE_LOGON_FAILED",
		"The service did not start due to a logon failure.",	NULL	},
	{	ERROR_SERVICE_START_HANG,			"ERROR_SERVICE_START_HANG",
		"After starting, the service hung in a start-pending state.",	NULL	},
	{	ERROR_INVALID_SERVICE_LOCK,			"ERROR_INVALID_SERVICE_LOCK",
		"The specified service database lock is invalid.",	NULL	},
	{	ERROR_SERVICE_MARKED_FOR_DELETE,			"ERROR_SERVICE_MARKED_FOR_DELETE",
		"The specified service has been marked for deletion.",	NULL	},
	{	ERROR_SERVICE_EXISTS,			"ERROR_SERVICE_EXISTS",
		"The specified service already exists.",	NULL	},
	{	ERROR_ALREADY_RUNNING_LKG,			"ERROR_ALREADY_RUNNING_LKG",
		"The system is currently running with the last-known-good configuration.",	NULL	},
	{	ERROR_SERVICE_DEPENDENCY_DELETED,			"ERROR_SERVICE_DEPENDENCY_DELETED",
		"The dependency service does not exist or has been marked for deletion.",	NULL	},
	{	ERROR_BOOT_ALREADY_ACCEPTED,			"ERROR_BOOT_ALREADY_ACCEPTED",
		"The current boot has already been accepted for use as the last-known-good control set.",	NULL	},
	{	ERROR_SERVICE_NEVER_STARTED,			"ERROR_SERVICE_NEVER_STARTED",
		"No attempts to start the service have been made since the last boot.",	NULL	},
	{	ERROR_DUPLICATE_SERVICE_NAME,			"ERROR_DUPLICATE_SERVICE_NAME",
		"The name is already in use as either a service name or a service display name.",	NULL	},
	{	ERROR_DIFFERENT_SERVICE_ACCOUNT,			"ERROR_DIFFERENT_SERVICE_ACCOUNT",
		"The account specified for this service is different from the account specified for other services running in the same process.",	NULL	},
	{	ERROR_CANNOT_DETECT_DRIVER_FAILURE,			"ERROR_CANNOT_DETECT_DRIVER_FAILURE",
		"Failure actions can only be set for Win32 services, not for drivers.",	NULL	},
	{	ERROR_CANNOT_DETECT_PROCESS_ABORT,			"ERROR_CANNOT_DETECT_PROCESS_ABORT",
		"This service runs in the same process as the service control manager. Therefore, the service control manager cannot take action if this service's process terminates unexpectedly.",	NULL	},
	{	ERROR_NO_RECOVERY_PROGRAM,			"ERROR_NO_RECOVERY_PROGRAM",
		"No recovery program has been configured for this service.",	NULL	},
	{	ERROR_END_OF_MEDIA,			"ERROR_END_OF_MEDIA",
		"The physical end of the tape has been reached.",	NULL	},
	{	ERROR_FILEMARK_DETECTED,			"ERROR_FILEMARK_DETECTED",
		"A tape access reached a filemark.",	NULL	},
	{	ERROR_BEGINNING_OF_MEDIA,			"ERROR_BEGINNING_OF_MEDIA",
		"The beginning of the tape or a partition was encountered.",	NULL	},
	{	ERROR_SETMARK_DETECTED,			"ERROR_SETMARK_DETECTED",
		"A tape access reached the end of a set of files.",	NULL	},
	{	ERROR_NO_DATA_DETECTED,			"ERROR_NO_DATA_DETECTED",
		"No more data is on the tape.",	NULL	},
	{	ERROR_PARTITION_FAILURE,			"ERROR_PARTITION_FAILURE",
		"Tape could not be partitioned.",	NULL	},
	{	ERROR_INVALID_BLOCK_LENGTH,			"ERROR_INVALID_BLOCK_LENGTH",
		"When accessing a new tape of a multivolume partition, the current blocksize is incorrect.",	NULL	},
	{	ERROR_DEVICE_NOT_PARTITIONED,			"ERROR_DEVICE_NOT_PARTITIONED",
		"Tape partition information could not be found when loading a tape.",	NULL	},
	{	ERROR_UNABLE_TO_LOCK_MEDIA,			"ERROR_UNABLE_TO_LOCK_MEDIA",
		"Unable to lock the media eject mechanism.",	NULL	},
	{	ERROR_UNABLE_TO_UNLOAD_MEDIA,			"ERROR_UNABLE_TO_UNLOAD_MEDIA",
		"Unable to unload the media.",	NULL	},
	{	ERROR_MEDIA_CHANGED,			"ERROR_MEDIA_CHANGED",
		"The media in the drive may have changed.",	NULL	},
	{	ERROR_BUS_RESET,			"ERROR_BUS_RESET",
		"The I/O bus was reset.",	NULL	},
	{	ERROR_NO_MEDIA_IN_DRIVE,			"ERROR_NO_MEDIA_IN_DRIVE",
		"No media in drive.",	NULL	},
	{	ERROR_NO_UNICODE_TRANSLATION,			"ERROR_NO_UNICODE_TRANSLATION",
		"No mapping for the Unicode character exists in the target multi-byte code page.",	NULL	},
	{	ERROR_DLL_INIT_FAILED,			"ERROR_DLL_INIT_FAILED",
		"A dynamic link library (DLL) initialization routine failed.",	NULL	},
	{	ERROR_SHUTDOWN_IN_PROGRESS,			"ERROR_SHUTDOWN_IN_PROGRESS",
		"A system shutdown is in progress.",	NULL	},
	{	ERROR_NO_SHUTDOWN_IN_PROGRESS,			"ERROR_NO_SHUTDOWN_IN_PROGRESS",
		"Unable to abort the system shutdown because no shutdown was in progress.",	NULL	},
	{	ERROR_IO_DEVICE,			"ERROR_IO_DEVICE",
		"The request could not be performed because of an I/O device error.",	NULL	},
	{	ERROR_SERIAL_NO_DEVICE,			"ERROR_SERIAL_NO_DEVICE",
		"No serial device was successfully initialized.  The serial driver will unload.",	NULL	},
	{	ERROR_IRQ_BUSY,			"ERROR_IRQ_BUSY",
		"Unable to open a device that was sharing an interrupt request (IRQ) with other devices. At least one other device that uses that IRQ was already opened.",	NULL	},
	{	ERROR_MORE_WRITES,			"ERROR_MORE_WRITES",
		"A serial I/O operation was completed by another write to the serial port. (The IOCTL_SERIAL_XOFF_COUNTER reached zero.)",	NULL	},
	{	ERROR_COUNTER_TIMEOUT,			"ERROR_COUNTER_TIMEOUT",
		"A serial I/O operation completed because the timeout period expired. (The IOCTL_SERIAL_XOFF_COUNTER did not reach zero.)",	NULL	},
	{	ERROR_FLOPPY_ID_MARK_NOT_FOUND,			"ERROR_FLOPPY_ID_MARK_NOT_FOUND",
		"No ID address mark was found on the floppy disk.",	NULL	},
	{	ERROR_FLOPPY_WRONG_CYLINDER,			"ERROR_FLOPPY_WRONG_CYLINDER",
		"Mismatch between the floppy disk sector ID field and the floppy disk controller track address.",	NULL	},
	{	ERROR_FLOPPY_UNKNOWN_ERROR,			"ERROR_FLOPPY_UNKNOWN_ERROR",
		"The floppy disk controller reported an error that is not recognized by the floppy disk driver.",	NULL	},
	{	ERROR_FLOPPY_BAD_REGISTERS,			"ERROR_FLOPPY_BAD_REGISTERS",
		"The floppy disk controller returned inconsistent results in its registers.",	NULL	},
	{	ERROR_DISK_RECALIBRATE_FAILED,			"ERROR_DISK_RECALIBRATE_FAILED",
		"While accessing the hard disk, a recalibrate operation failed, even after retries.",	NULL	},
	{	ERROR_DISK_OPERATION_FAILED,			"ERROR_DISK_OPERATION_FAILED",
		"While accessing the hard disk, a disk operation failed even after retries.",	NULL	},
	{	ERROR_DISK_RESET_FAILED,			"ERROR_DISK_RESET_FAILED",
		"While accessing the hard disk, a disk controller reset was needed, but even that failed.",	NULL	},
	{	ERROR_EOM_OVERFLOW,			"ERROR_EOM_OVERFLOW",
		"Physical end of tape encountered.",	NULL	},
	{	ERROR_NOT_ENOUGH_SERVER_MEMORY,			"ERROR_NOT_ENOUGH_SERVER_MEMORY",
		"Not enough server storage is available to process this command.",	NULL	},
	{	ERROR_POSSIBLE_DEADLOCK,			"ERROR_POSSIBLE_DEADLOCK",
		"A potential deadlock condition has been detected.",	NULL	},
	{	ERROR_MAPPED_ALIGNMENT,			"ERROR_MAPPED_ALIGNMENT",
		"The base address or the file offset specified does not have the proper alignment.",	NULL	},
	{	ERROR_SET_POWER_STATE_VETOED,			"ERROR_SET_POWER_STATE_VETOED",
		"An attempt to change the system power state was vetoed by another application or driver.",	NULL	},
	{	ERROR_SET_POWER_STATE_FAILED,			"ERROR_SET_POWER_STATE_FAILED",
		"The system BIOS failed an attempt to change the system power state.",	NULL	},
	{	ERROR_TOO_MANY_LINKS,			"ERROR_TOO_MANY_LINKS",
		"An attempt was made to create more links on a file than the file system supports.",	NULL	},
	{	ERROR_OLD_WIN_VERSION,			"ERROR_OLD_WIN_VERSION",
		"The specified program requires a newer version of Windows.",	NULL	},
	{	ERROR_APP_WRONG_OS,			"ERROR_APP_WRONG_OS",
		"The specified program is not a Windows or MS-DOS program.",	NULL	},
	{	ERROR_SINGLE_INSTANCE_APP,			"ERROR_SINGLE_INSTANCE_APP",
		"Cannot start more than one instance of the specified program.",	NULL	},
	{	ERROR_RMODE_APP,			"ERROR_RMODE_APP",
		"The specified program was written for an earlier version of Windows.",	NULL	},
	{	ERROR_INVALID_DLL,			"ERROR_INVALID_DLL",
		"One of the library files needed to run this application is damaged.",	NULL	},
	{	ERROR_NO_ASSOCIATION,			"ERROR_NO_ASSOCIATION",
		"No application is associated with the specified file for this operation.",	NULL	},
	{	ERROR_DDE_FAIL,			"ERROR_DDE_FAIL",
		"An error occurred in sending the command to the application.",	NULL	},
	{	ERROR_DLL_NOT_FOUND,			"ERROR_DLL_NOT_FOUND",
		"One of the library files needed to run this application cannot be found.",	NULL	},
	{	ERROR_NO_MORE_USER_HANDLES,			"ERROR_NO_MORE_USER_HANDLES",
		"The current process has used all of its system allowance of handles for Window Manager objects.",	NULL	},
	{	ERROR_MESSAGE_SYNC_ONLY,			"ERROR_MESSAGE_SYNC_ONLY",
		"The message can be used only with synchronous operations.",	NULL	},
	{	ERROR_SOURCE_ELEMENT_EMPTY,			"ERROR_SOURCE_ELEMENT_EMPTY",
		"The indicated source element has no media.",	NULL	},
	{	ERROR_DESTINATION_ELEMENT_FULL,			"ERROR_DESTINATION_ELEMENT_FULL",
		"The indicated destination element already contains media.",	NULL	},
	{	ERROR_ILLEGAL_ELEMENT_ADDRESS,			"ERROR_ILLEGAL_ELEMENT_ADDRESS",
		"The indicated element does not exist.",	NULL	},
	{	ERROR_MAGAZINE_NOT_PRESENT,			"ERROR_MAGAZINE_NOT_PRESENT",
		"The indicated element is part of a magazine that is not present.",	NULL	},
	{	ERROR_DEVICE_REINITIALIZATION_NEEDED,			"ERROR_DEVICE_REINITIALIZATION_NEEDED",
		"The indicated device requires reinitialization due to hardware errors.",	NULL	},
	{	ERROR_DEVICE_REQUIRES_CLEANING,			"ERROR_DEVICE_REQUIRES_CLEANING",
		"The device has indicated that cleaning is required before further operations are attempted.",	NULL	},
	{	ERROR_DEVICE_DOOR_OPEN,			"ERROR_DEVICE_DOOR_OPEN",
		"The device has indicated that its door is open.",	NULL	},
	{	ERROR_DEVICE_NOT_CONNECTED,			"ERROR_DEVICE_NOT_CONNECTED",
		"The device is not connected.",	NULL	},
	{	ERROR_NOT_FOUND,			"ERROR_NOT_FOUND",
		"Element not found.",	NULL	},
	{	ERROR_NO_MATCH,			"ERROR_NO_MATCH",
		"There was no match for the specified key in the index.",	NULL	},
	{	ERROR_SET_NOT_FOUND,			"ERROR_SET_NOT_FOUND",
		"The property set specified does not exist on the object.",	NULL	},
	{	ERROR_POINT_NOT_FOUND,			"ERROR_POINT_NOT_FOUND",
		"The point passed to GetMouseMovePoints is not in the buffer.",	NULL	},
	{	ERROR_NO_TRACKING_SERVICE,			"ERROR_NO_TRACKING_SERVICE",
		"The tracking (workstation) service is not running.",	NULL	},
	{	ERROR_NO_VOLUME_ID,			"ERROR_NO_VOLUME_ID",
		"The Volume ID could not be found.",	NULL	},
	{	ERROR_CONNECTED_OTHER_PASSWORD,			"ERROR_CONNECTED_OTHER_PASSWORD",
		"The network connection was made successfully, but the user had to be prompted for a password other than the one originally specified.",	NULL	},
	{	ERROR_BAD_USERNAME,			"ERROR_BAD_USERNAME",
		"The specified username is invalid.",	NULL	},
	{	ERROR_NOT_CONNECTED,			"ERROR_NOT_CONNECTED",
		"This network connection does not exist.",	NULL	},
	{	ERROR_OPEN_FILES,			"ERROR_OPEN_FILES",
		"This network connection has files open or requests pending.",	NULL	},
	{	ERROR_ACTIVE_CONNECTIONS,			"ERROR_ACTIVE_CONNECTIONS",
		"Active connections still exist.",	NULL	},
	{	ERROR_DEVICE_IN_USE,			"ERROR_DEVICE_IN_USE",
		"The device is in use by an active process and cannot be disconnected.",	NULL	},
	{	ERROR_BAD_DEVICE,			"ERROR_BAD_DEVICE",
		"The specified device name is invalid.",	NULL	},
	{	ERROR_CONNECTION_UNAVAIL,			"ERROR_CONNECTION_UNAVAIL",
		"The device is not currently connected but it is a remembered connection.",	NULL	},
	{	ERROR_DEVICE_ALREADY_REMEMBERED,			"ERROR_DEVICE_ALREADY_REMEMBERED",
		"An attempt was made to remember a device that had previously been remembered.",	NULL	},
	{	ERROR_NO_NET_OR_BAD_PATH,			"ERROR_NO_NET_OR_BAD_PATH",
		"No network provider accepted the given network path.",	NULL	},
	{	ERROR_BAD_PROVIDER,			"ERROR_BAD_PROVIDER",
		"The specified network provider name is invalid.",	NULL	},
	{	ERROR_CANNOT_OPEN_PROFILE,			"ERROR_CANNOT_OPEN_PROFILE",
		"Unable to open the network connection profile.",	NULL	},
	{	ERROR_BAD_PROFILE,			"ERROR_BAD_PROFILE",
		"The network connection profile is corrupted.",	NULL	},
	{	ERROR_NOT_CONTAINER,			"ERROR_NOT_CONTAINER",
		"Cannot enumerate a noncontainer.",	NULL	},
	{	ERROR_EXTENDED_ERROR,			"ERROR_EXTENDED_ERROR",
		"An extended error has occurred.",	NULL	},
	{	ERROR_INVALID_GROUPNAME,			"ERROR_INVALID_GROUPNAME",
		"The format of the specified group name is invalid.",	NULL	},
	{	ERROR_INVALID_COMPUTERNAME,			"ERROR_INVALID_COMPUTERNAME",
		"The format of the specified computer name is invalid.",	NULL	},
	{	ERROR_INVALID_EVENTNAME,			"ERROR_INVALID_EVENTNAME",
		"The format of the specified event name is invalid.",	NULL	},
	{	ERROR_INVALID_DOMAINNAME,			"ERROR_INVALID_DOMAINNAME",
		"The format of the specified domain name is invalid.",	NULL	},
	{	ERROR_INVALID_SERVICENAME,			"ERROR_INVALID_SERVICENAME",
		"The format of the specified service name is invalid.",	NULL	},
	{	ERROR_INVALID_NETNAME,			"ERROR_INVALID_NETNAME",
		"The format of the specified network name is invalid.",	NULL	},
	{	ERROR_INVALID_SHARENAME,			"ERROR_INVALID_SHARENAME",
		"The format of the specified share name is invalid.",	NULL	},
	{	ERROR_INVALID_PASSWORDNAME,			"ERROR_INVALID_PASSWORDNAME",
		"The format of the specified password is invalid.",	NULL	},
	{	ERROR_INVALID_MESSAGENAME,			"ERROR_INVALID_MESSAGENAME",
		"The format of the specified message name is invalid.",	NULL	},
	{	ERROR_INVALID_MESSAGEDEST,			"ERROR_INVALID_MESSAGEDEST",
		"The format of the specified message destination is invalid.",	NULL	},
	{	ERROR_SESSION_CREDENTIAL_CONFLICT,			"ERROR_SESSION_CREDENTIAL_CONFLICT",
		"The credentials supplied conflict with an existing set of credentials.",	NULL	},
	{	ERROR_REMOTE_SESSION_LIMIT_EXCEEDED,			"ERROR_REMOTE_SESSION_LIMIT_EXCEEDED",
		"An attempt was made to establish a session to a network server, but there are already too many sessions established to that server.",	NULL	},
	{	ERROR_DUP_DOMAINNAME,			"ERROR_DUP_DOMAINNAME",
		"The workgroup or domain name is already in use by another computer on the network.",	NULL	},
	{	ERROR_NO_NETWORK,			"ERROR_NO_NETWORK",
		"The network is not present or not started.",	NULL	},
	{	ERROR_CANCELLED,			"ERROR_CANCELLED",
		"The operation was canceled by the user.",	NULL	},
	{	ERROR_USER_MAPPED_FILE,			"ERROR_USER_MAPPED_FILE",
		"The requested operation cannot be performed on a file with a user-mapped section open.",	NULL	},
	{	ERROR_CONNECTION_REFUSED,			"ERROR_CONNECTION_REFUSED",
		"The remote system refused the network connection.",	NULL	},
	{	ERROR_GRACEFUL_DISCONNECT,			"ERROR_GRACEFUL_DISCONNECT",
		"The network connection was gracefully closed.",	NULL	},
	{	ERROR_ADDRESS_ALREADY_ASSOCIATED,			"ERROR_ADDRESS_ALREADY_ASSOCIATED",
		"The network transport endpoint already has an address associated with it.",	NULL	},
	{	ERROR_ADDRESS_NOT_ASSOCIATED,			"ERROR_ADDRESS_NOT_ASSOCIATED",
		"An address has not yet been associated with the network endpoint.",	NULL	},
	{	ERROR_CONNECTION_INVALID,			"ERROR_CONNECTION_INVALID",
		"An operation was attempted on a nonexistent network connection.",	NULL	},
	{	ERROR_CONNECTION_ACTIVE,			"ERROR_CONNECTION_ACTIVE",
		"An invalid operation was attempted on an active network connection.",	NULL	},
	{	ERROR_NETWORK_UNREACHABLE,			"ERROR_NETWORK_UNREACHABLE",
		"The remote network is not reachable by the transport.",	NULL	},
	{	ERROR_HOST_UNREACHABLE,			"ERROR_HOST_UNREACHABLE",
		"The remote system is not reachable by the transport.",	NULL	},
	{	ERROR_PROTOCOL_UNREACHABLE,			"ERROR_PROTOCOL_UNREACHABLE",
		"The remote system does not support the transport protocol.",	NULL	},
	{	ERROR_PORT_UNREACHABLE,			"ERROR_PORT_UNREACHABLE",
		"No service is operating at the destination network endpoint on the remote system.",	NULL	},
	{	ERROR_REQUEST_ABORTED,			"ERROR_REQUEST_ABORTED",
		"The request was aborted.",	NULL	},
	{	ERROR_CONNECTION_ABORTED,			"ERROR_CONNECTION_ABORTED",
		"The network connection was aborted by the local system.",	NULL	},
	{	ERROR_RETRY,			"ERROR_RETRY",
		"The operation could not be completed.  A retry should be performed.",	NULL	},
	{	ERROR_CONNECTION_COUNT_LIMIT,			"ERROR_CONNECTION_COUNT_LIMIT",
		"A connection to the server could not be made because the limit on the number of concurrent connections for this account has been reached.",	NULL	},
	{	ERROR_LOGIN_TIME_RESTRICTION,			"ERROR_LOGIN_TIME_RESTRICTION",
		"Attempting to log in during an unauthorized time of day for this account.",	NULL	},
	{	ERROR_LOGIN_WKSTA_RESTRICTION,			"ERROR_LOGIN_WKSTA_RESTRICTION",
		"The account is not authorized to log in from this station.",	NULL	},
	{	ERROR_INCORRECT_ADDRESS,			"ERROR_INCORRECT_ADDRESS",
		"The network address could not be used for the operation requested.",	NULL	},
	{	ERROR_ALREADY_REGISTERED,			"ERROR_ALREADY_REGISTERED",
		"The service is already registered.",	NULL	},
	{	ERROR_SERVICE_NOT_FOUND,			"ERROR_SERVICE_NOT_FOUND",
		"The specified service does not exist.",	NULL	},
	{	ERROR_NOT_AUTHENTICATED,			"ERROR_NOT_AUTHENTICATED",
		"The operation being requested was not performed because the user has not been authenticated.",	NULL	},
	{	ERROR_NOT_LOGGED_ON,			"ERROR_NOT_LOGGED_ON",
		"The operation being requested was not performed because the user has not logged on to the network. The specified service does not exist.",	NULL	},
	{	ERROR_CONTINUE,			"ERROR_CONTINUE",
		"Continue with work in progress.",	NULL	},
	{	ERROR_ALREADY_INITIALIZED,			"ERROR_ALREADY_INITIALIZED",
		"An attempt was made to perform an initialization operation when initialization has already been completed.",	NULL	},
	{	ERROR_NO_MORE_DEVICES,			"ERROR_NO_MORE_DEVICES",
		"No more local devices.",	NULL	},
	{	ERROR_NO_SUCH_SITE,			"ERROR_NO_SUCH_SITE",
		"The specified site does not exist.",	NULL	},
	{	ERROR_DOMAIN_CONTROLLER_EXISTS,			"ERROR_DOMAIN_CONTROLLER_EXISTS",
		"A domain controller with the specified name already exists.",	NULL	},
	{	ERROR_DS_NOT_INSTALLED,			"ERROR_DS_NOT_INSTALLED",
		"An error occurred while installing the Windows NT directory service. Please view the event log for more information.",	NULL	},
	{	ERROR_NOT_ALL_ASSIGNED,			"ERROR_NOT_ALL_ASSIGNED",
		"Not all privileges referenced are assigned to the caller.",	NULL	},
	{	ERROR_SOME_NOT_MAPPED,			"ERROR_SOME_NOT_MAPPED",
		"Some mapping between account names and security IDs was not done.",	NULL	},
	{	ERROR_NO_QUOTAS_FOR_ACCOUNT,			"ERROR_NO_QUOTAS_FOR_ACCOUNT",
		"No system quota limits are specifically set for this account.",	NULL	},
	{	ERROR_LOCAL_USER_SESSION_KEY,			"ERROR_LOCAL_USER_SESSION_KEY",
		"No encryption key is available.  A well-known encryption key was returned.",	NULL	},
	{	ERROR_NULL_LM_PASSWORD,			"ERROR_NULL_LM_PASSWORD",
		"The Windows NT password is too complex to be converted to a LAN Manager password.  The LAN Manager password returned is a NULL string.",	NULL	},
	{	ERROR_UNKNOWN_REVISION,			"ERROR_UNKNOWN_REVISION",
		"The revision level is unknown.",	NULL	},
	{	ERROR_REVISION_MISMATCH,			"ERROR_REVISION_MISMATCH",
		"Indicates two revision levels are incompatible.",	NULL	},
	{	ERROR_INVALID_OWNER,			"ERROR_INVALID_OWNER",
		"This security ID may not be assigned as the owner of this object.",	NULL	},
	{	ERROR_INVALID_PRIMARY_GROUP,			"ERROR_INVALID_PRIMARY_GROUP",
		"This security ID may not be assigned as the primary group of an object.",	NULL	},
	{	ERROR_NO_IMPERSONATION_TOKEN,			"ERROR_NO_IMPERSONATION_TOKEN",
		"An attempt has been made to operate on an impersonation token by a thread that is not currently impersonating a client.",	NULL	},
	{	ERROR_CANT_DISABLE_MANDATORY,			"ERROR_CANT_DISABLE_MANDATORY",
		"The group may not be disabled.",	NULL	},
	{	ERROR_NO_LOGON_SERVERS,			"ERROR_NO_LOGON_SERVERS",
		"There are currently no logon servers available to service the logon request.",	NULL	},
	{	ERROR_NO_SUCH_LOGON_SESSION,			"ERROR_NO_SUCH_LOGON_SESSION",
		"A specified logon session does not exist.  It may already have been terminated.",	NULL	},
	{	ERROR_NO_SUCH_PRIVILEGE,			"ERROR_NO_SUCH_PRIVILEGE",
		"A specified privilege does not exist.",	NULL	},
	{	ERROR_PRIVILEGE_NOT_HELD,			"ERROR_PRIVILEGE_NOT_HELD",
		"A required privilege is not held by the client.",	NULL	},
	{	ERROR_INVALID_ACCOUNT_NAME,			"ERROR_INVALID_ACCOUNT_NAME",
		"The name provided is not a properly formed account name.",	NULL	},
	{	ERROR_USER_EXISTS,			"ERROR_USER_EXISTS",
		"The specified user already exists.",	NULL	},
	{	ERROR_NO_SUCH_USER,			"ERROR_NO_SUCH_USER",
		"The specified user does not exist.",	NULL	},
	{	ERROR_GROUP_EXISTS,			"ERROR_GROUP_EXISTS",
		"The specified group already exists.",	NULL	},
	{	ERROR_NO_SUCH_GROUP,			"ERROR_NO_SUCH_GROUP",
		"The specified group does not exist.",	NULL	},
	{	ERROR_MEMBER_IN_GROUP,			"ERROR_MEMBER_IN_GROUP",
		"Either the specified user account is already a member of the specified group, or the specified group cannot be deleted because it contains a member.",	NULL	},
	{	ERROR_MEMBER_NOT_IN_GROUP,			"ERROR_MEMBER_NOT_IN_GROUP",
		"The specified user account is not a member of the specified group account.",	NULL	},
	{	ERROR_LAST_ADMIN,			"ERROR_LAST_ADMIN",
		"The last remaining administration account cannot be disabled or deleted.",	NULL	},
	{	ERROR_WRONG_PASSWORD,			"ERROR_WRONG_PASSWORD",
		"Unable to update the password.  The value provided as the current password is incorrect.",	NULL	},
	{	ERROR_ILL_FORMED_PASSWORD,			"ERROR_ILL_FORMED_PASSWORD",
		"Unable to update the password.  The value provided for the new password contains values that are not allowed in passwords.",	NULL	},
	{	ERROR_PASSWORD_RESTRICTION,			"ERROR_PASSWORD_RESTRICTION",
		"Unable to update the password because a password update rule has been violated.",	NULL	},
	{	ERROR_LOGON_FAILURE,			"ERROR_LOGON_FAILURE",
		"Logon failure: unknown user name or bad password.",	NULL	},
	{	ERROR_ACCOUNT_RESTRICTION,			"ERROR_ACCOUNT_RESTRICTION",
		"Logon failure: user account restriction.",	NULL	},
	{	ERROR_INVALID_LOGON_HOURS,			"ERROR_INVALID_LOGON_HOURS",
		"Logon failure: account logon time restriction violation.",	NULL	},
	{	ERROR_INVALID_WORKSTATION,			"ERROR_INVALID_WORKSTATION",
		"Logon failure: user not allowed to log on to this computer.",	NULL	},
	{	ERROR_PASSWORD_EXPIRED,			"ERROR_PASSWORD_EXPIRED",
		"Logon failure: the specified account password has expired.",	NULL	},
	{	ERROR_ACCOUNT_DISABLED,			"ERROR_ACCOUNT_DISABLED",
		"Logon failure: account currently disabled.",	NULL	},
	{	ERROR_NONE_MAPPED,			"ERROR_NONE_MAPPED",
		"No mapping between account names and security IDs was done.",	NULL	},
	{	ERROR_TOO_MANY_LUIDS_REQUESTED,			"ERROR_TOO_MANY_LUIDS_REQUESTED",
		"Too many local user identifiers (LUIDs) were requested at one time.",	NULL	},
	{	ERROR_LUIDS_EXHAUSTED,			"ERROR_LUIDS_EXHAUSTED",
		"No more local user identifiers (LUIDs) are available.",	NULL	},
	{	ERROR_INVALID_SUB_AUTHORITY,			"ERROR_INVALID_SUB_AUTHORITY",
		"The subauthority part of a security ID is invalid for this particular use.",	NULL	},
	{	ERROR_INVALID_ACL,			"ERROR_INVALID_ACL",
		"The access control list (ACL) structure is invalid.",	NULL	},
	{	ERROR_INVALID_SID,			"ERROR_INVALID_SID",
		"The security ID structure is invalid.",	NULL	},
	{	ERROR_INVALID_SECURITY_DESCR,			"ERROR_INVALID_SECURITY_DESCR",
		"The security descriptor structure is invalid.",	NULL	},
	{	ERROR_BAD_INHERITANCE_ACL,			"ERROR_BAD_INHERITANCE_ACL",
		"The inherited access control list (ACL) or access control entry (ACE) could not be built.",	NULL	},
	{	ERROR_SERVER_DISABLED,			"ERROR_SERVER_DISABLED",
		"The server is currently disabled.",	NULL	},
	{	ERROR_SERVER_NOT_DISABLED,			"ERROR_SERVER_NOT_DISABLED",
		"The server is currently enabled.",	NULL	},
	{	ERROR_INVALID_ID_AUTHORITY,			"ERROR_INVALID_ID_AUTHORITY",
		"The value provided was an invalid value for an identifier authority.",	NULL	},
	{	ERROR_ALLOTTED_SPACE_EXCEEDED,			"ERROR_ALLOTTED_SPACE_EXCEEDED",
		"No more memory is available for security information updates.",	NULL	},
	{	ERROR_INVALID_GROUP_ATTRIBUTES,			"ERROR_INVALID_GROUP_ATTRIBUTES",
		"The specified attributes are invalid, or incompatible with the attributes for the group as a whole.",	NULL	},
	{	ERROR_BAD_IMPERSONATION_LEVEL,			"ERROR_BAD_IMPERSONATION_LEVEL",
		"Either a required impersonation level was not provided, or the provided impersonation level is invalid.",	NULL	},
	{	ERROR_CANT_OPEN_ANONYMOUS,			"ERROR_CANT_OPEN_ANONYMOUS",
		"Cannot open an anonymous level security token.",	NULL	},
	{	ERROR_BAD_VALIDATION_CLASS,			"ERROR_BAD_VALIDATION_CLASS",
		"The validation information class requested was invalid.",	NULL	},
	{	ERROR_BAD_TOKEN_TYPE,			"ERROR_BAD_TOKEN_TYPE",
		"The type of the token is inappropriate for its attempted use.",	NULL	},
	{	ERROR_NO_SECURITY_ON_OBJECT,			"ERROR_NO_SECURITY_ON_OBJECT",
		"Unable to perform a security operation on an object that has no associated security.",	NULL	},
	{	ERROR_CANT_ACCESS_DOMAIN_INFO,			"ERROR_CANT_ACCESS_DOMAIN_INFO",
		"Indicates a Windows NT Server could not be contacted or that objects within the domain are protected such that necessary information could not be retrieved.",	NULL	},
	{	ERROR_INVALID_SERVER_STATE,			"ERROR_INVALID_SERVER_STATE",
		"The security account manager (SAM) or local security authority (LSA) server was in the wrong state to perform the security operation.",	NULL	},
	{	ERROR_INVALID_DOMAIN_STATE,			"ERROR_INVALID_DOMAIN_STATE",
		"The domain was in the wrong state to perform the security operation.",	NULL	},
	{	ERROR_INVALID_DOMAIN_ROLE,			"ERROR_INVALID_DOMAIN_ROLE",
		"This operation is only allowed for the Primary Domain Controller of the domain.",	NULL	},
	{	ERROR_NO_SUCH_DOMAIN,			"ERROR_NO_SUCH_DOMAIN",
		"The specified domain did not exist.",	NULL	},
	{	ERROR_DOMAIN_EXISTS,			"ERROR_DOMAIN_EXISTS",
		"The specified domain already exists.",	NULL	},
	{	ERROR_DOMAIN_LIMIT_EXCEEDED,			"ERROR_DOMAIN_LIMIT_EXCEEDED",
		"An attempt was made to exceed the limit on the number of domains per server.",	NULL	},
	{	ERROR_INTERNAL_DB_CORRUPTION,			"ERROR_INTERNAL_DB_CORRUPTION",
		"Unable to complete the requested operation because of either a catastrophic media failure or a data structure corruption on the disk.",	NULL	},
	{	ERROR_INTERNAL_ERROR,			"ERROR_INTERNAL_ERROR",
		"The security account database contains an internal inconsistency.",	NULL	},
	{	ERROR_GENERIC_NOT_MAPPED,			"ERROR_GENERIC_NOT_MAPPED",
		"Generic access types were contained in an access mask which should already be mapped to nongeneric types.",	NULL	},
	{	ERROR_BAD_DESCRIPTOR_FORMAT,			"ERROR_BAD_DESCRIPTOR_FORMAT",
		"A security descriptor is not in the right format (absolute or self-relative).",	NULL	},
	{	ERROR_NOT_LOGON_PROCESS,			"ERROR_NOT_LOGON_PROCESS",
		"The requested action is restricted for use by logon processes only.  The calling process has not registered as a logon process.",	NULL	},
	{	ERROR_LOGON_SESSION_EXISTS,			"ERROR_LOGON_SESSION_EXISTS",
		"Cannot start a new logon session with an ID that is already in use.",	NULL	},
	{	ERROR_NO_SUCH_PACKAGE,			"ERROR_NO_SUCH_PACKAGE",
		"A specified authentication package is unknown.",	NULL	},
	{	ERROR_BAD_LOGON_SESSION_STATE,			"ERROR_BAD_LOGON_SESSION_STATE",
		"The logon session is not in a state that is consistent with the requested operation.",	NULL	},
	{	ERROR_LOGON_SESSION_COLLISION,			"ERROR_LOGON_SESSION_COLLISION",
		"The logon session ID is already in use.",	NULL	},
	{	ERROR_INVALID_LOGON_TYPE,			"ERROR_INVALID_LOGON_TYPE",
		"A logon request contained an invalid logon type value.",	NULL	},
	{	ERROR_CANNOT_IMPERSONATE,			"ERROR_CANNOT_IMPERSONATE",
		"Unable to impersonate using a named pipe until data has been read from that pipe.",	NULL	},
	{	ERROR_RXACT_INVALID_STATE,			"ERROR_RXACT_INVALID_STATE",
		"The transaction state of a registry subtree is incompatible with the requested operation.",	NULL	},
	{	ERROR_RXACT_COMMIT_FAILURE,			"ERROR_RXACT_COMMIT_FAILURE",
		"An internal security database corruption has been encountered.",	NULL	},
	{	ERROR_SPECIAL_ACCOUNT,			"ERROR_SPECIAL_ACCOUNT",
		"Cannot perform this operation on built-in accounts.",	NULL	},
	{	ERROR_SPECIAL_GROUP,			"ERROR_SPECIAL_GROUP",
		"Cannot perform this operation on this built-in special group.",	NULL	},
	{	ERROR_SPECIAL_USER,			"ERROR_SPECIAL_USER",
		"Cannot perform this operation on this built-in special user.",	NULL	},
	{	ERROR_MEMBERS_PRIMARY_GROUP,			"ERROR_MEMBERS_PRIMARY_GROUP",
		"The user cannot be removed from a group because the group is currently the user's primary group.",	NULL	},
	{	ERROR_TOKEN_ALREADY_IN_USE,			"ERROR_TOKEN_ALREADY_IN_USE",
		"The token is already in use as a primary token.",	NULL	},
	{	ERROR_NO_SUCH_ALIAS,			"ERROR_NO_SUCH_ALIAS",
		"The specified local group does not exist.",	NULL	},
	{	ERROR_MEMBER_NOT_IN_ALIAS,			"ERROR_MEMBER_NOT_IN_ALIAS",
		"The specified account name is not a member of the local group.",	NULL	},
	{	ERROR_MEMBER_IN_ALIAS,			"ERROR_MEMBER_IN_ALIAS",
		"The specified account name is already a member of the local group.",	NULL	},
	{	ERROR_ALIAS_EXISTS,			"ERROR_ALIAS_EXISTS",
		"The specified local group already exists.",	NULL	},
	{	ERROR_LOGON_NOT_GRANTED,			"ERROR_LOGON_NOT_GRANTED",
		"Logon failure: the user has not been granted the requested logon type at this computer.",	NULL	},
	{	ERROR_TOO_MANY_SECRETS,			"ERROR_TOO_MANY_SECRETS",
		"The maximum number of secrets that may be stored in a single system has been exceeded.",	NULL	},
	{	ERROR_SECRET_TOO_LONG,			"ERROR_SECRET_TOO_LONG",
		"The length of a secret exceeds the maximum length allowed.",	NULL	},
	{	ERROR_INTERNAL_DB_ERROR,			"ERROR_INTERNAL_DB_ERROR",
		"The local security authority database contains an internal inconsistency.",	NULL	},
	{	ERROR_TOO_MANY_CONTEXT_IDS,			"ERROR_TOO_MANY_CONTEXT_IDS",
		"During a logon attempt, the user's security context accumulated too many security IDs.",	NULL	},
	{	ERROR_LOGON_TYPE_NOT_GRANTED,			"ERROR_LOGON_TYPE_NOT_GRANTED",
		"Logon failure: the user has not been granted the requested logon type at this computer.",	NULL	},
	{	ERROR_NT_CROSS_ENCRYPTION_REQUIRED,			"ERROR_NT_CROSS_ENCRYPTION_REQUIRED",
		"A cross-encrypted password is necessary to change a user password.",	NULL	},
	{	ERROR_NO_SUCH_MEMBER,			"ERROR_NO_SUCH_MEMBER",
		"A new member could not be added to a local group because the member does not exist.",	NULL	},
	{	ERROR_INVALID_MEMBER,			"ERROR_INVALID_MEMBER",
		"A new member could not be added to a local group because the member has the wrong account type.",	NULL	},
	{	ERROR_TOO_MANY_SIDS,			"ERROR_TOO_MANY_SIDS",
		"Too many security IDs have been specified.",	NULL	},
	{	ERROR_LM_CROSS_ENCRYPTION_REQUIRED,			"ERROR_LM_CROSS_ENCRYPTION_REQUIRED",
		"A cross-encrypted password is necessary to change this user password.",	NULL	},
	{	ERROR_NO_INHERITANCE,			"ERROR_NO_INHERITANCE",
		"Indicates an ACL contains no inheritable components.",	NULL	},
	{	ERROR_FILE_CORRUPT,			"ERROR_FILE_CORRUPT",
		"The file or directory is corrupted and unreadable.",	NULL	},
	{	ERROR_DISK_CORRUPT,			"ERROR_DISK_CORRUPT",
		"The disk structure is corrupted and unreadable.",	NULL	},
	{	ERROR_NO_USER_SESSION_KEY,			"ERROR_NO_USER_SESSION_KEY",
		"There is no user session key for the specified logon session.",	NULL	},
	{	ERROR_LICENSE_QUOTA_EXCEEDED,			"ERROR_LICENSE_QUOTA_EXCEEDED",
		"The service being accessed is licensed for a particular number of connections. No more connections can be made to the service at this time because there are already as many connections as the service can accept.",	NULL	},
	{	ERROR_INVALID_WINDOW_HANDLE,			"ERROR_INVALID_WINDOW_HANDLE",
		"Invalid window handle.",	NULL	},
	{	ERROR_INVALID_MENU_HANDLE,			"ERROR_INVALID_MENU_HANDLE",
		"Invalid menu handle.",	NULL	},
	{	ERROR_INVALID_CURSOR_HANDLE,			"ERROR_INVALID_CURSOR_HANDLE",
		"Invalid cursor handle.",	NULL	},
	{	ERROR_INVALID_ACCEL_HANDLE,			"ERROR_INVALID_ACCEL_HANDLE",
		"Invalid accelerator table handle.",	NULL	},
	{	ERROR_INVALID_HOOK_HANDLE,			"ERROR_INVALID_HOOK_HANDLE",
		"Invalid hook handle.",	NULL	},
	{	ERROR_INVALID_DWP_HANDLE,			"ERROR_INVALID_DWP_HANDLE",
		"Invalid handle to a multiple-window position structure.",	NULL	},
	{	ERROR_TLW_WITH_WSCHILD,			"ERROR_TLW_WITH_WSCHILD",
		"Cannot create a top-level child window.",	NULL	},
	{	ERROR_CANNOT_FIND_WND_CLASS,			"ERROR_CANNOT_FIND_WND_CLASS",
		"Cannot find window class.",	NULL	},
	{	ERROR_WINDOW_OF_OTHER_THREAD,			"ERROR_WINDOW_OF_OTHER_THREAD",
		"Invalid window; it belongs to other thread.",	NULL	},
	{	ERROR_HOTKEY_ALREADY_REGISTERED,			"ERROR_HOTKEY_ALREADY_REGISTERED",
		"Hot key is already registered.",	NULL	},
	{	ERROR_CLASS_ALREADY_EXISTS,			"ERROR_CLASS_ALREADY_EXISTS",
		"Class already exists.",	NULL	},
	{	ERROR_CLASS_DOES_NOT_EXIST,			"ERROR_CLASS_DOES_NOT_EXIST",
		"Class does not exist.",	NULL	},
	{	ERROR_CLASS_HAS_WINDOWS,			"ERROR_CLASS_HAS_WINDOWS",
		"Class still has open windows.",	NULL	},
	{	ERROR_INVALID_INDEX,			"ERROR_INVALID_INDEX",
		"Invalid index.",	NULL	},
	{	ERROR_INVALID_ICON_HANDLE,			"ERROR_INVALID_ICON_HANDLE",
		"Invalid icon handle.",	NULL	},
	{	ERROR_PRIVATE_DIALOG_INDEX,			"ERROR_PRIVATE_DIALOG_INDEX",
		"Using private DIALOG window words.",	NULL	},
	{	ERROR_LISTBOX_ID_NOT_FOUND,			"ERROR_LISTBOX_ID_NOT_FOUND",
		"The list box identifier was not found.",	NULL	},
	{	ERROR_NO_WILDCARD_CHARACTERS,			"ERROR_NO_WILDCARD_CHARACTERS",
		"No wildcards were found.",	NULL	},
	{	ERROR_CLIPBOARD_NOT_OPEN,			"ERROR_CLIPBOARD_NOT_OPEN",
		"Thread does not have a clipboard open.",	NULL	},
	{	ERROR_HOTKEY_NOT_REGISTERED,			"ERROR_HOTKEY_NOT_REGISTERED",
		"Hot key is not registered.",	NULL	},
	{	ERROR_WINDOW_NOT_DIALOG,			"ERROR_WINDOW_NOT_DIALOG",
		"The window is not a valid dialog window.",	NULL	},
	{	ERROR_CONTROL_ID_NOT_FOUND,			"ERROR_CONTROL_ID_NOT_FOUND",
		"Control ID not found.",	NULL	},
	{	ERROR_INVALID_COMBOBOX_MESSAGE,			"ERROR_INVALID_COMBOBOX_MESSAGE",
		"Invalid message for a combo box because it does not have an edit control.",	NULL	},
	{	ERROR_WINDOW_NOT_COMBOBOX,			"ERROR_WINDOW_NOT_COMBOBOX",
		"The window is not a combo box.",	NULL	},
	{	ERROR_INVALID_EDIT_HEIGHT,			"ERROR_INVALID_EDIT_HEIGHT",
		"Height must be less than 256.",	NULL	},
	{	ERROR_DC_NOT_FOUND,			"ERROR_DC_NOT_FOUND",
		"Invalid device context (DC) handle.",	NULL	},
	{	ERROR_INVALID_HOOK_FILTER,			"ERROR_INVALID_HOOK_FILTER",
		"Invalid hook procedure type.",	NULL	},
	{	ERROR_INVALID_FILTER_PROC,			"ERROR_INVALID_FILTER_PROC",
		"Invalid hook procedure.",	NULL	},
	{	ERROR_HOOK_NEEDS_HMOD,			"ERROR_HOOK_NEEDS_HMOD",
		"Cannot set nonlocal hook without a module handle.",	NULL	},
	{	ERROR_GLOBAL_ONLY_HOOK,			"ERROR_GLOBAL_ONLY_HOOK",
		"This hook procedure can only be set globally.",	NULL	},
	{	ERROR_JOURNAL_HOOK_SET,			"ERROR_JOURNAL_HOOK_SET",
		"The journal hook procedure is already installed.",	NULL	},
	{	ERROR_HOOK_NOT_INSTALLED,			"ERROR_HOOK_NOT_INSTALLED",
		"The hook procedure is not installed.",	NULL	},
	{	ERROR_INVALID_LB_MESSAGE,			"ERROR_INVALID_LB_MESSAGE",
		"Invalid message for single-selection list box.",	NULL	},
	{	ERROR_SETCOUNT_ON_BAD_LB,			"ERROR_SETCOUNT_ON_BAD_LB",
		"LB_SETCOUNT sent to non-lazy list box.",	NULL	},
	{	ERROR_LB_WITHOUT_TABSTOPS,			"ERROR_LB_WITHOUT_TABSTOPS",
		"This list box does not support tab stops.",	NULL	},
	{	ERROR_DESTROY_OBJECT_OF_OTHER_THREAD,			"ERROR_DESTROY_OBJECT_OF_OTHER_THREAD",
		"Cannot destroy object created by another thread.",	NULL	},
	{	ERROR_CHILD_WINDOW_MENU,			"ERROR_CHILD_WINDOW_MENU",
		"Child windows cannot have menus.",	NULL	},
	{	ERROR_NO_SYSTEM_MENU,			"ERROR_NO_SYSTEM_MENU",
		"The window does not have a system menu.",	NULL	},
	{	ERROR_INVALID_MSGBOX_STYLE,			"ERROR_INVALID_MSGBOX_STYLE",
		"Invalid message box style.",	NULL	},
	{	ERROR_INVALID_SPI_VALUE,			"ERROR_INVALID_SPI_VALUE",
		"Invalid system-wide (SPI_*) parameter.",	NULL	},
	{	ERROR_SCREEN_ALREADY_LOCKED,			"ERROR_SCREEN_ALREADY_LOCKED",
		"Screen already locked.",	NULL	},
	{	ERROR_HWNDS_HAVE_DIFF_PARENT,			"ERROR_HWNDS_HAVE_DIFF_PARENT",
		"All handles to windows in a multiple-window position structure must have the same parent.",	NULL	},
	{	ERROR_NOT_CHILD_WINDOW,			"ERROR_NOT_CHILD_WINDOW",
		"The window is not a child window.",	NULL	},
	{	ERROR_INVALID_GW_COMMAND,			"ERROR_INVALID_GW_COMMAND",
		"Invalid GW_* command.",	NULL	},
	{	ERROR_INVALID_THREAD_ID,			"ERROR_INVALID_THREAD_ID",
		"Invalid thread identifier.",	NULL	},
	{	ERROR_NON_MDICHILD_WINDOW,			"ERROR_NON_MDICHILD_WINDOW",
		"Cannot process a message from a window that is not a multiple document interface (MDI) window.",	NULL	},
	{	ERROR_POPUP_ALREADY_ACTIVE,			"ERROR_POPUP_ALREADY_ACTIVE",
		"Popup menu already active.",	NULL	},
	{	ERROR_NO_SCROLLBARS,			"ERROR_NO_SCROLLBARS",
		"The window does not have scroll bars.",	NULL	},
	{	ERROR_INVALID_SCROLLBAR_RANGE,			"ERROR_INVALID_SCROLLBAR_RANGE",
		"Scroll bar range cannot be greater than 0x7FFF.",	NULL	},
	{	ERROR_INVALID_SHOWWIN_COMMAND,			"ERROR_INVALID_SHOWWIN_COMMAND",
		"Cannot show or remove the window in the way specified.",	NULL	},
	{	ERROR_NO_SYSTEM_RESOURCES,			"ERROR_NO_SYSTEM_RESOURCES",
		"Insufficient system resources exist to complete the requested service.",	NULL	},
	{	ERROR_NONPAGED_SYSTEM_RESOURCES,			"ERROR_NONPAGED_SYSTEM_RESOURCES",
		"Insufficient system resources exist to complete the requested service.",	NULL	},
	{	ERROR_PAGED_SYSTEM_RESOURCES,			"ERROR_PAGED_SYSTEM_RESOURCES",
		"Insufficient system resources exist to complete the requested service.",	NULL	},
	{	ERROR_WORKING_SET_QUOTA,			"ERROR_WORKING_SET_QUOTA",
		"Insufficient quota to complete the requested service.",	NULL	},
	{	ERROR_PAGEFILE_QUOTA,			"ERROR_PAGEFILE_QUOTA",
		"Insufficient quota to complete the requested service.",	NULL	},
	{	ERROR_COMMITMENT_LIMIT,			"ERROR_COMMITMENT_LIMIT",
		"The paging file is too small for this operation to complete.",	NULL	},
	{	ERROR_MENU_ITEM_NOT_FOUND,			"ERROR_MENU_ITEM_NOT_FOUND",
		"A menu item was not found.",	NULL	},
	{	ERROR_INVALID_KEYBOARD_HANDLE,			"ERROR_INVALID_KEYBOARD_HANDLE",
		"Invalid keyboard layout handle.",	NULL	},
	{	ERROR_HOOK_TYPE_NOT_ALLOWED,			"ERROR_HOOK_TYPE_NOT_ALLOWED",
		"Hook type not allowed.",	NULL	},
	{	ERROR_REQUIRES_INTERACTIVE_WINDOWSTATION,			"ERROR_REQUIRES_INTERACTIVE_WINDOWSTATION",
		"This operation requires an interactive window station.",	NULL	},
	{	ERROR_TIMEOUT,			"ERROR_TIMEOUT",
		"This operation returned because the timeout period expired.",	NULL	},
	{	ERROR_INVALID_MONITOR_HANDLE,			"ERROR_INVALID_MONITOR_HANDLE",
		"Invalid monitor handle.",	NULL	},
	{	ERROR_EVENTLOG_FILE_CORRUPT,			"ERROR_EVENTLOG_FILE_CORRUPT",
		"The event log file is corrupted.",	NULL	},
	{	ERROR_EVENTLOG_CANT_START,			"ERROR_EVENTLOG_CANT_START",
		"No event log file could be opened, so the event logging service did not start.",	NULL	},
	{	ERROR_LOG_FILE_FULL,			"ERROR_LOG_FILE_FULL",
		"The event log file is full.",	NULL	},
	{	ERROR_EVENTLOG_FILE_CHANGED,			"ERROR_EVENTLOG_FILE_CHANGED",
		"The event log file has changed between read operations.",	NULL	},
# ifdef ERROR_INSTALL_SERVICE
	{	ERROR_INSTALL_SERVICE,			"ERROR_INSTALL_SERVICE",
		"Failure accessing install service.",	NULL	},
# endif /* # ifdef ERROR_INSTALL_SERVICE */
	{	ERROR_INSTALL_USEREXIT,			"ERROR_INSTALL_USEREXIT",
		"The user canceled the installation.",	NULL	},
	{	ERROR_INSTALL_FAILURE,			"ERROR_INSTALL_FAILURE",
		"Fatal error during installation.",	NULL	},
	{	ERROR_INSTALL_SUSPEND,			"ERROR_INSTALL_SUSPEND",
		"Installation suspended, incomplete.",	NULL	},
	{	ERROR_UNKNOWN_PRODUCT,			"ERROR_UNKNOWN_PRODUCT",
		"Product code not registered.",	NULL	},
	{	ERROR_UNKNOWN_FEATURE,			"ERROR_UNKNOWN_FEATURE",
		"Feature ID not registered.",	NULL	},
	{	ERROR_UNKNOWN_COMPONENT,			"ERROR_UNKNOWN_COMPONENT",
		"Component ID not registered.",	NULL	},
	{	ERROR_UNKNOWN_PROPERTY,			"ERROR_UNKNOWN_PROPERTY",
		"Unknown property.",	NULL	},
	{	ERROR_INVALID_HANDLE_STATE,			"ERROR_INVALID_HANDLE_STATE",
		"Handle is in an invalid state.",	NULL	},
	{	ERROR_BAD_CONFIGURATION,			"ERROR_BAD_CONFIGURATION",
		"Configuration data corrupt.",	NULL	},
	{	ERROR_INDEX_ABSENT,			"ERROR_INDEX_ABSENT",
		"Language not available.",	NULL	},
	{	ERROR_INSTALL_SOURCE_ABSENT,			"ERROR_INSTALL_SOURCE_ABSENT",
		"Install source unavailable.",	NULL	},
# ifdef ERROR_BAD_DATABASE_VERSION
	{	ERROR_BAD_DATABASE_VERSION,			"ERROR_BAD_DATABASE_VERSION",
		"Database version unsupported.",	NULL	},
# endif /* # ifdef ERROR_BAD_DATABASE_VERSION */
	{	ERROR_PRODUCT_UNINSTALLED,			"ERROR_PRODUCT_UNINSTALLED",
		"Product is uninstalled.",	NULL	},
	{	ERROR_BAD_QUERY_SYNTAX,			"ERROR_BAD_QUERY_SYNTAX",
		"SQL query syntax invalid or unsupported.",	NULL	},
	{	ERROR_INVALID_FIELD,			"ERROR_INVALID_FIELD",
		"Record field does not exist.",	NULL	},
	{	RPC_S_INVALID_STRING_BINDING,			"RPC_S_INVALID_STRING_BINDING",
		"The string binding is invalid.",	NULL	},
	{	RPC_S_WRONG_KIND_OF_BINDING,			"RPC_S_WRONG_KIND_OF_BINDING",
		"The binding handle is not the correct type.",	NULL	},
	{	RPC_S_INVALID_BINDING,			"RPC_S_INVALID_BINDING",
		"The binding handle is invalid.",	NULL	},
	{	RPC_S_PROTSEQ_NOT_SUPPORTED,			"RPC_S_PROTSEQ_NOT_SUPPORTED",
		"The RPC protocol sequence is not supported.",	NULL	},
	{	RPC_S_INVALID_RPC_PROTSEQ,			"RPC_S_INVALID_RPC_PROTSEQ",
		"The RPC protocol sequence is invalid.",	NULL	},
	{	RPC_S_INVALID_STRING_UUID,			"RPC_S_INVALID_STRING_UUID",
		"The string universal unique identifier (UUID) is invalid.",	NULL	},
	{	RPC_S_INVALID_ENDPOINT_FORMAT,			"RPC_S_INVALID_ENDPOINT_FORMAT",
		"The endpoint format is invalid.",	NULL	},
	{	RPC_S_INVALID_NET_ADDR,			"RPC_S_INVALID_NET_ADDR",
		"The network address is invalid.",	NULL	},
	{	RPC_S_NO_ENDPOINT_FOUND,			"RPC_S_NO_ENDPOINT_FOUND",
		"No endpoint was found.",	NULL	},
	{	RPC_S_INVALID_TIMEOUT,			"RPC_S_INVALID_TIMEOUT",
		"The timeout value is invalid.",	NULL	},
	{	RPC_S_OBJECT_NOT_FOUND,			"RPC_S_OBJECT_NOT_FOUND",
		"The object universal unique identifier (UUID) was not found.",	NULL	},
	{	RPC_S_ALREADY_REGISTERED,			"RPC_S_ALREADY_REGISTERED",
		"The object universal unique identifier (UUID) has already been registered.",	NULL	},
	{	RPC_S_TYPE_ALREADY_REGISTERED,			"RPC_S_TYPE_ALREADY_REGISTERED",
		"The type universal unique identifier (UUID) has already been registered.",	NULL	},
	{	RPC_S_ALREADY_LISTENING,			"RPC_S_ALREADY_LISTENING",
		"The RPC server is already listening.",	NULL	},
	{	RPC_S_NO_PROTSEQS_REGISTERED,			"RPC_S_NO_PROTSEQS_REGISTERED",
		"No protocol sequences have been registered.",	NULL	},
	{	RPC_S_NOT_LISTENING,			"RPC_S_NOT_LISTENING",
		"The RPC server is not listening.",	NULL	},
	{	RPC_S_UNKNOWN_MGR_TYPE,			"RPC_S_UNKNOWN_MGR_TYPE",
		"The manager type is unknown.",	NULL	},
	{	RPC_S_UNKNOWN_IF,			"RPC_S_UNKNOWN_IF",
		"The interface is unknown.",	NULL	},
	{	RPC_S_NO_BINDINGS,			"RPC_S_NO_BINDINGS",
		"There are no bindings.",	NULL	},
	{	RPC_S_NO_PROTSEQS,			"RPC_S_NO_PROTSEQS",
		"There are no protocol sequences.",	NULL	},
	{	RPC_S_CANT_CREATE_ENDPOINT,			"RPC_S_CANT_CREATE_ENDPOINT",
		"The endpoint cannot be created.",	NULL	},
	{	RPC_S_OUT_OF_RESOURCES,			"RPC_S_OUT_OF_RESOURCES",
		"Not enough resources are available to complete this operation.",	NULL	},
	{	RPC_S_SERVER_UNAVAILABLE,			"RPC_S_SERVER_UNAVAILABLE",
		"The RPC server is unavailable.",	NULL	},
	{	RPC_S_SERVER_TOO_BUSY,			"RPC_S_SERVER_TOO_BUSY",
		"The RPC server is too busy to complete this operation.",	NULL	},
	{	RPC_S_INVALID_NETWORK_OPTIONS,			"RPC_S_INVALID_NETWORK_OPTIONS",
		"The network options are invalid.",	NULL	},
	{	RPC_S_NO_CALL_ACTIVE,			"RPC_S_NO_CALL_ACTIVE",
		"There are no remote procedure calls active on this thread.",	NULL	},
	{	RPC_S_CALL_FAILED,			"RPC_S_CALL_FAILED",
		"The remote procedure call failed.",	NULL	},
	{	RPC_S_CALL_FAILED_DNE,			"RPC_S_CALL_FAILED_DNE",
		"The remote procedure call failed and did not execute.",	NULL	},
	{	RPC_S_PROTOCOL_ERROR,			"RPC_S_PROTOCOL_ERROR",
		"A remote procedure call (RPC) protocol error occurred.",	NULL	},
	{	RPC_S_UNSUPPORTED_TRANS_SYN,			"RPC_S_UNSUPPORTED_TRANS_SYN",
		"The transfer syntax is not supported by the RPC server.",	NULL	},
	{	RPC_S_UNSUPPORTED_TYPE,			"RPC_S_UNSUPPORTED_TYPE",
		"The universal unique identifier (UUID) type is not supported.",	NULL	},
	{	RPC_S_INVALID_TAG,			"RPC_S_INVALID_TAG",
		"The tag is invalid.",	NULL	},
	{	RPC_S_INVALID_BOUND,			"RPC_S_INVALID_BOUND",
		"The array bounds are invalid.",	NULL	},
	{	RPC_S_NO_ENTRY_NAME,			"RPC_S_NO_ENTRY_NAME",
		"The binding does not contain an entry name.",	NULL	},
	{	RPC_S_INVALID_NAME_SYNTAX,			"RPC_S_INVALID_NAME_SYNTAX",
		"The name syntax is invalid.",	NULL	},
	{	RPC_S_UNSUPPORTED_NAME_SYNTAX,			"RPC_S_UNSUPPORTED_NAME_SYNTAX",
		"The name syntax is not supported.",	NULL	},
	{	RPC_S_UUID_NO_ADDRESS,			"RPC_S_UUID_NO_ADDRESS",
		"No network address is available to use to construct a universal unique identifier (UUID).",	NULL	},
	{	RPC_S_DUPLICATE_ENDPOINT,			"RPC_S_DUPLICATE_ENDPOINT",
		"The endpoint is a duplicate.",	NULL	},
	{	RPC_S_UNKNOWN_AUTHN_TYPE,			"RPC_S_UNKNOWN_AUTHN_TYPE",
		"The authentication type is unknown.",	NULL	},
	{	RPC_S_MAX_CALLS_TOO_SMALL,			"RPC_S_MAX_CALLS_TOO_SMALL",
		"The maximum number of calls is too small.",	NULL	},
	{	RPC_S_STRING_TOO_LONG,			"RPC_S_STRING_TOO_LONG",
		"The string is too long.",	NULL	},
	{	RPC_S_PROTSEQ_NOT_FOUND,			"RPC_S_PROTSEQ_NOT_FOUND",
		"The RPC protocol sequence was not found.",	NULL	},
	{	RPC_S_PROCNUM_OUT_OF_RANGE,			"RPC_S_PROCNUM_OUT_OF_RANGE",
		"The procedure number is out of range.",	NULL	},
	{	RPC_S_BINDING_HAS_NO_AUTH,			"RPC_S_BINDING_HAS_NO_AUTH",
		"The binding does not contain any authentication information.",	NULL	},
	{	RPC_S_UNKNOWN_AUTHN_SERVICE,			"RPC_S_UNKNOWN_AUTHN_SERVICE",
		"The authentication service is unknown.",	NULL	},
	{	RPC_S_UNKNOWN_AUTHN_LEVEL,			"RPC_S_UNKNOWN_AUTHN_LEVEL",
		"The authentication level is unknown.",	NULL	},
	{	RPC_S_INVALID_AUTH_IDENTITY,			"RPC_S_INVALID_AUTH_IDENTITY",
		"The security context is invalid.",	NULL	},
	{	RPC_S_UNKNOWN_AUTHZ_SERVICE,			"RPC_S_UNKNOWN_AUTHZ_SERVICE",
		"The authorization service is unknown.",	NULL	},
	{	EPT_S_INVALID_ENTRY,			"EPT_S_INVALID_ENTRY",
		"The entry is invalid.",	NULL	},
	{	EPT_S_CANT_PERFORM_OP,			"EPT_S_CANT_PERFORM_OP",
		"The server endpoint cannot perform the operation.",	NULL	},
	{	EPT_S_NOT_REGISTERED,			"EPT_S_NOT_REGISTERED",
		"There are no more endpoints available from the endpoint mapper.",	NULL	},
	{	RPC_S_NOTHING_TO_EXPORT,			"RPC_S_NOTHING_TO_EXPORT",
		"No interfaces have been exported.",	NULL	},
	{	RPC_S_INCOMPLETE_NAME,			"RPC_S_INCOMPLETE_NAME",
		"The entry name is incomplete.",	NULL	},
	{	RPC_S_INVALID_VERS_OPTION,			"RPC_S_INVALID_VERS_OPTION",
		"The version option is invalid.",	NULL	},
	{	RPC_S_NO_MORE_MEMBERS,			"RPC_S_NO_MORE_MEMBERS",
		"There are no more members.",	NULL	},
	{	RPC_S_NOT_ALL_OBJS_UNEXPORTED,			"RPC_S_NOT_ALL_OBJS_UNEXPORTED",
		"There is nothing to unexport.",	NULL	},
	{	RPC_S_INTERFACE_NOT_FOUND,			"RPC_S_INTERFACE_NOT_FOUND",
		"The interface was not found.",	NULL	},
	{	RPC_S_ENTRY_ALREADY_EXISTS,			"RPC_S_ENTRY_ALREADY_EXISTS",
		"The entry already exists.",	NULL	},
	{	RPC_S_ENTRY_NOT_FOUND,			"RPC_S_ENTRY_NOT_FOUND",
		"The entry is not found.",	NULL	},
	{	RPC_S_NAME_SERVICE_UNAVAILABLE,			"RPC_S_NAME_SERVICE_UNAVAILABLE",
		"The name service is unavailable.",	NULL	},
	{	RPC_S_INVALID_NAF_ID,			"RPC_S_INVALID_NAF_ID",
		"The network address family is invalid.",	NULL	},
	{	RPC_S_CANNOT_SUPPORT,			"RPC_S_CANNOT_SUPPORT",
		"The requested operation is not supported.",	NULL	},
	{	RPC_S_NO_CONTEXT_AVAILABLE,			"RPC_S_NO_CONTEXT_AVAILABLE",
		"No security context is available to allow impersonation.",	NULL	},
	{	RPC_S_INTERNAL_ERROR,			"RPC_S_INTERNAL_ERROR",
		"An internal error occurred in a remote procedure call (RPC).",	NULL	},
	{	RPC_S_ZERO_DIVIDE,			"RPC_S_ZERO_DIVIDE",
		"The RPC server attempted an integer division by zero.",	NULL	},
	{	RPC_S_ADDRESS_ERROR,			"RPC_S_ADDRESS_ERROR",
		"An addressing error occurred in the RPC server.",	NULL	},
	{	RPC_S_FP_DIV_ZERO,			"RPC_S_FP_DIV_ZERO",
		"A floating-point operation at the RPC server caused a division by zero.",	NULL	},
	{	RPC_S_FP_UNDERFLOW,			"RPC_S_FP_UNDERFLOW",
		"A floating-point underflow occurred at the RPC server.",	NULL	},
	{	RPC_S_FP_OVERFLOW,			"RPC_S_FP_OVERFLOW",
		"A floating-point overflow occurred at the RPC server.",	NULL	},
	{	RPC_X_NO_MORE_ENTRIES,			"RPC_X_NO_MORE_ENTRIES",
		"The list of RPC servers available for the binding of auto handles has been exhausted.",	NULL	},
	{	RPC_X_SS_CHAR_TRANS_OPEN_FAIL,			"RPC_X_SS_CHAR_TRANS_OPEN_FAIL",
		"Unable to open the character translation table file.",	NULL	},
	{	RPC_X_SS_CHAR_TRANS_SHORT_FILE,			"RPC_X_SS_CHAR_TRANS_SHORT_FILE",
		"The file containing the character translation table has fewer than 512 bytes.",	NULL	},
	{	RPC_X_SS_IN_NULL_CONTEXT,			"RPC_X_SS_IN_NULL_CONTEXT",
		"A null context handle was passed from the client to the host during a remote procedure call.",	NULL	},
	{	RPC_X_SS_CONTEXT_DAMAGED,			"RPC_X_SS_CONTEXT_DAMAGED",
		"The context handle changed during a remote procedure call.",	NULL	},
	{	RPC_X_SS_HANDLES_MISMATCH,			"RPC_X_SS_HANDLES_MISMATCH",
		"The binding handles passed to a remote procedure call do not match.",	NULL	},
	{	RPC_X_SS_CANNOT_GET_CALL_HANDLE,			"RPC_X_SS_CANNOT_GET_CALL_HANDLE",
		"The stub is unable to get the remote procedure call handle.",	NULL	},
	{	RPC_X_NULL_REF_POINTER,			"RPC_X_NULL_REF_POINTER",
		"A null reference pointer was passed to the stub.",	NULL	},
	{	RPC_X_ENUM_VALUE_OUT_OF_RANGE,			"RPC_X_ENUM_VALUE_OUT_OF_RANGE",
		"The enumeration value is out of range.",	NULL	},
	{	RPC_X_BYTE_COUNT_TOO_SMALL,			"RPC_X_BYTE_COUNT_TOO_SMALL",
		"The byte count is too small.",	NULL	},
	{	RPC_X_BAD_STUB_DATA,			"RPC_X_BAD_STUB_DATA",
		"The stub received bad data.",	NULL	},
	{	ERROR_INVALID_USER_BUFFER,			"ERROR_INVALID_USER_BUFFER",
		"The supplied user buffer is not valid for the requested operation.",	NULL	},
	{	ERROR_UNRECOGNIZED_MEDIA,			"ERROR_UNRECOGNIZED_MEDIA",
		"The disk media is not recognized.  It may not be formatted.",	NULL	},
	{	ERROR_NO_TRUST_LSA_SECRET,			"ERROR_NO_TRUST_LSA_SECRET",
		"The workstation does not have a trust secret.",	NULL	},
	{	ERROR_NO_TRUST_SAM_ACCOUNT,			"ERROR_NO_TRUST_SAM_ACCOUNT",
		"The SAM database on the Windows NT Server does not have a computer account for this workstation trust relationship.",	NULL	},
	{	ERROR_TRUSTED_DOMAIN_FAILURE,			"ERROR_TRUSTED_DOMAIN_FAILURE",
		"The trust relationship between the primary domain and the trusted domain failed.",	NULL	},
	{	ERROR_TRUSTED_RELATIONSHIP_FAILURE,			"ERROR_TRUSTED_RELATIONSHIP_FAILURE",
		"The trust relationship between this workstation and the primary domain failed.",	NULL	},
	{	ERROR_TRUST_FAILURE,			"ERROR_TRUST_FAILURE",
		"The network logon failed.",	NULL	},
	{	RPC_S_CALL_IN_PROGRESS,			"RPC_S_CALL_IN_PROGRESS",
		"A remote procedure call is already in progress for this thread.",	NULL	},
	{	ERROR_NETLOGON_NOT_STARTED,			"ERROR_NETLOGON_NOT_STARTED",
		"An attempt was made to logon, but the network logon service was not started.",	NULL	},
	{	ERROR_ACCOUNT_EXPIRED,			"ERROR_ACCOUNT_EXPIRED",
		"The user's account has expired.",	NULL	},
	{	ERROR_REDIRECTOR_HAS_OPEN_HANDLES,			"ERROR_REDIRECTOR_HAS_OPEN_HANDLES",
		"The redirector is in use and cannot be unloaded.",	NULL	},
	{	ERROR_PRINTER_DRIVER_ALREADY_INSTALLED,			"ERROR_PRINTER_DRIVER_ALREADY_INSTALLED",
		"The specified printer driver is already installed.",	NULL	},
	{	ERROR_UNKNOWN_PORT,			"ERROR_UNKNOWN_PORT",
		"The specified port is unknown.",	NULL	},
	{	ERROR_UNKNOWN_PRINTER_DRIVER,			"ERROR_UNKNOWN_PRINTER_DRIVER",
		"The printer driver is unknown.",	NULL	},
	{	ERROR_UNKNOWN_PRINTPROCESSOR,			"ERROR_UNKNOWN_PRINTPROCESSOR",
		"The print processor is unknown.",	NULL	},
	{	ERROR_INVALID_SEPARATOR_FILE,			"ERROR_INVALID_SEPARATOR_FILE",
		"The specified separator file is invalid.",	NULL	},
	{	ERROR_INVALID_PRIORITY,			"ERROR_INVALID_PRIORITY",
		"The specified priority is invalid.",	NULL	},
	{	ERROR_INVALID_PRINTER_NAME,			"ERROR_INVALID_PRINTER_NAME",
		"The printer name is invalid.",	NULL	},
	{	ERROR_PRINTER_ALREADY_EXISTS,			"ERROR_PRINTER_ALREADY_EXISTS",
		"The printer already exists.",	NULL	},
	{	ERROR_INVALID_PRINTER_COMMAND,			"ERROR_INVALID_PRINTER_COMMAND",
		"The printer command is invalid.",	NULL	},
	{	ERROR_INVALID_DATATYPE,			"ERROR_INVALID_DATATYPE",
		"The specified datatype is invalid.",	NULL	},
	{	ERROR_INVALID_ENVIRONMENT,			"ERROR_INVALID_ENVIRONMENT",
		"The environment specified is invalid.",	NULL	},
	{	RPC_S_NO_MORE_BINDINGS,			"RPC_S_NO_MORE_BINDINGS",
		"There are no more bindings.",	NULL	},
	{	ERROR_NOLOGON_INTERDOMAIN_TRUST_ACCOUNT,			"ERROR_NOLOGON_INTERDOMAIN_TRUST_ACCOUNT",
		"The account used is an interdomain trust account.  Use your global user account or local user account to access this server.",	NULL	},
	{	ERROR_NOLOGON_WORKSTATION_TRUST_ACCOUNT,			"ERROR_NOLOGON_WORKSTATION_TRUST_ACCOUNT",
		"The account used is a computer account.  Use your global user account or local user account to access this server.",	NULL	},
	{	ERROR_NOLOGON_SERVER_TRUST_ACCOUNT,			"ERROR_NOLOGON_SERVER_TRUST_ACCOUNT",
		"The account used is a server trust account. Use your global user account or local user account to access this server.",	NULL	},
	{	ERROR_DOMAIN_TRUST_INCONSISTENT,			"ERROR_DOMAIN_TRUST_INCONSISTENT",
		"The name or security ID (SID) of the domain specified is inconsistent with the trust information for that domain.",	NULL	},
	{	ERROR_SERVER_HAS_OPEN_HANDLES,			"ERROR_SERVER_HAS_OPEN_HANDLES",
		"The server is in use and cannot be unloaded.",	NULL	},
	{	ERROR_RESOURCE_DATA_NOT_FOUND,			"ERROR_RESOURCE_DATA_NOT_FOUND",
		"The specified image file did not contain a resource section.",	NULL	},
	{	ERROR_RESOURCE_TYPE_NOT_FOUND,			"ERROR_RESOURCE_TYPE_NOT_FOUND",
		"The specified resource type cannot be found in the image file.",	NULL	},
	{	ERROR_RESOURCE_NAME_NOT_FOUND,			"ERROR_RESOURCE_NAME_NOT_FOUND",
		"The specified resource name cannot be found in the image file.",	NULL	},
	{	ERROR_RESOURCE_LANG_NOT_FOUND,			"ERROR_RESOURCE_LANG_NOT_FOUND",
		"The specified resource language ID cannot be found in the image file.",	NULL	},
	{	ERROR_NOT_ENOUGH_QUOTA,			"ERROR_NOT_ENOUGH_QUOTA",
		"Not enough quota is available to process this command.",	NULL	},
	{	RPC_S_NO_INTERFACES,			"RPC_S_NO_INTERFACES",
		"No interfaces have been registered.",	NULL	},
	{	RPC_S_CALL_CANCELLED,			"RPC_S_CALL_CANCELLED",
		"The remote procedure call was cancelled.",	NULL	},
	{	RPC_S_BINDING_INCOMPLETE,			"RPC_S_BINDING_INCOMPLETE",
		"The binding handle does not contain all required information.",	NULL	},
	{	RPC_S_COMM_FAILURE,			"RPC_S_COMM_FAILURE",
		"A communications failure occurred during a remote procedure call.",	NULL	},
	{	RPC_S_UNSUPPORTED_AUTHN_LEVEL,			"RPC_S_UNSUPPORTED_AUTHN_LEVEL",
		"The requested authentication level is not supported.",	NULL	},
	{	RPC_S_NO_PRINC_NAME,			"RPC_S_NO_PRINC_NAME",
		"No principal name registered.",	NULL	},
	{	RPC_S_NOT_RPC_ERROR,			"RPC_S_NOT_RPC_ERROR",
		"The error specified is not a valid Windows RPC error code.",	NULL	},
	{	RPC_S_UUID_LOCAL_ONLY,			"RPC_S_UUID_LOCAL_ONLY",
		"A UUID that is valid only on this computer has been allocated.",	NULL	},
	{	RPC_S_SEC_PKG_ERROR,			"RPC_S_SEC_PKG_ERROR",
		"A security package specific error occurred.",	NULL	},
	{	RPC_S_NOT_CANCELLED,			"RPC_S_NOT_CANCELLED",
		"Thread is not canceled.",	NULL	},
	{	RPC_X_INVALID_ES_ACTION,			"RPC_X_INVALID_ES_ACTION",
		"Invalid operation on the encoding/decoding handle.",	NULL	},
	{	RPC_X_WRONG_ES_VERSION,			"RPC_X_WRONG_ES_VERSION",
		"Incompatible version of the serializing package.",	NULL	},
	{	RPC_X_WRONG_STUB_VERSION,			"RPC_X_WRONG_STUB_VERSION",
		"Incompatible version of the RPC stub.",	NULL	},
	{	RPC_X_INVALID_PIPE_OBJECT,			"RPC_X_INVALID_PIPE_OBJECT",
		"The RPC pipe object is invalid or corrupted.",	NULL	},
	{	RPC_X_WRONG_PIPE_ORDER,			"RPC_X_WRONG_PIPE_ORDER",
		"An invalid operation was attempted on an RPC pipe object.",	NULL	},
	{	RPC_X_WRONG_PIPE_VERSION,			"RPC_X_WRONG_PIPE_VERSION",
		"Unsupported RPC pipe version.",	NULL	},
	{	RPC_S_GROUP_MEMBER_NOT_FOUND,			"RPC_S_GROUP_MEMBER_NOT_FOUND",
		"The group member was not found.",	NULL	},
	{	EPT_S_CANT_CREATE,			"EPT_S_CANT_CREATE",
		"The endpoint mapper database entry could not be created.",	NULL	},
	{	RPC_S_INVALID_OBJECT,			"RPC_S_INVALID_OBJECT",
		"The object universal unique identifier (UUID) is the nil UUID.",	NULL	},
	{	ERROR_INVALID_TIME,			"ERROR_INVALID_TIME",
		"The specified time is invalid.",	NULL	},
	{	ERROR_INVALID_FORM_NAME,			"ERROR_INVALID_FORM_NAME",
		"The specified form name is invalid.",	NULL	},
	{	ERROR_INVALID_FORM_SIZE,			"ERROR_INVALID_FORM_SIZE",
		"The specified form size is invalid.",	NULL	},
	{	ERROR_ALREADY_WAITING,			"ERROR_ALREADY_WAITING",
		"The specified printer handle is already being waited on",	NULL	},
	{	ERROR_PRINTER_DELETED,			"ERROR_PRINTER_DELETED",
		"The specified printer has been deleted.",	NULL	},
	{	ERROR_INVALID_PRINTER_STATE,			"ERROR_INVALID_PRINTER_STATE",
		"The state of the printer is invalid.",	NULL	},
	{	ERROR_PASSWORD_MUST_CHANGE,			"ERROR_PASSWORD_MUST_CHANGE",
		"The user must change his password before he logs on the first time.",	NULL	},
	{	ERROR_DOMAIN_CONTROLLER_NOT_FOUND,			"ERROR_DOMAIN_CONTROLLER_NOT_FOUND",
		"Could not find the domain controller for this domain.",	NULL	},
	{	ERROR_ACCOUNT_LOCKED_OUT,			"ERROR_ACCOUNT_LOCKED_OUT",
		"The referenced account is currently locked out and may not be logged on to.",	NULL	},
	{	OR_INVALID_OXID,			"OR_INVALID_OXID",
		"The object exporter specified was not found.",	NULL	},
	{	OR_INVALID_OID,			"OR_INVALID_OID",
		"The object specified was not found.",	NULL	},
	{	OR_INVALID_SET,			"OR_INVALID_SET",
		"The object resolver set specified was not found.",	NULL	},
	{	RPC_S_SEND_INCOMPLETE,			"RPC_S_SEND_INCOMPLETE",
		"Some data remains to be sent in the request buffer.",	NULL	},
	{	RPC_S_INVALID_ASYNC_HANDLE,			"RPC_S_INVALID_ASYNC_HANDLE",
		"Invalid asynchronous remote procedure call handle.",	NULL	},
	{	RPC_S_INVALID_ASYNC_CALL,			"RPC_S_INVALID_ASYNC_CALL",
		"Invalid asynchronous RPC call handle for this operation.",	NULL	},
	{	RPC_X_PIPE_CLOSED,			"RPC_X_PIPE_CLOSED",
		"The RPC pipe object has already been closed.",	NULL	},
	{	RPC_X_PIPE_DISCIPLINE_ERROR,			"RPC_X_PIPE_DISCIPLINE_ERROR",
		"The RPC call completed before all pipes were processed.",	NULL	},
	{	RPC_X_PIPE_EMPTY,			"RPC_X_PIPE_EMPTY",
		"No more data is available from the RPC pipe.",	NULL	},
	{	ERROR_NO_SITENAME,			"ERROR_NO_SITENAME",
		"No site name is available for this machine.",	NULL	},
	{	ERROR_CANT_ACCESS_FILE,			"ERROR_CANT_ACCESS_FILE",
		"The file can not be accessed by the system.",	NULL	},
	{	ERROR_CANT_RESOLVE_FILENAME,			"ERROR_CANT_RESOLVE_FILENAME",
		"The name of the file cannot be resolved by the system.",	NULL	},
	{	ERROR_DS_MEMBERSHIP_EVALUATED_LOCALLY,			"ERROR_DS_MEMBERSHIP_EVALUATED_LOCALLY",
		"The directory service evaluated group memberships locally.",	NULL	},
	{	ERROR_DS_NO_ATTRIBUTE_OR_VALUE,			"ERROR_DS_NO_ATTRIBUTE_OR_VALUE",
		"The specified directory service attribute or value does not exist.",	NULL	},
	{	ERROR_DS_INVALID_ATTRIBUTE_SYNTAX,			"ERROR_DS_INVALID_ATTRIBUTE_SYNTAX",
		"The attribute syntax specified to the directory service is invalid.",	NULL	},
	{	ERROR_DS_ATTRIBUTE_TYPE_UNDEFINED,			"ERROR_DS_ATTRIBUTE_TYPE_UNDEFINED",
		"The attribute type specified to the directory service is not defined.",	NULL	},
	{	ERROR_DS_ATTRIBUTE_OR_VALUE_EXISTS,			"ERROR_DS_ATTRIBUTE_OR_VALUE_EXISTS",
		"The specified directory service attribute or value already exists.",	NULL	},
	{	ERROR_DS_BUSY,			"ERROR_DS_BUSY",
		"The directory service is busy.",	NULL	},
	{	ERROR_DS_UNAVAILABLE,			"ERROR_DS_UNAVAILABLE",
		"The directory service is unavailable.",	NULL	},
	{	ERROR_DS_NO_RIDS_ALLOCATED,			"ERROR_DS_NO_RIDS_ALLOCATED",
		"The directory service was unable to allocate a relative identifier.",	NULL	},
	{	ERROR_DS_NO_MORE_RIDS,			"ERROR_DS_NO_MORE_RIDS",
		"The directory service has exhausted the pool of relative identifiers.",	NULL	},
	{	ERROR_DS_INCORRECT_ROLE_OWNER,			"ERROR_DS_INCORRECT_ROLE_OWNER",
		"The requested operation could not be performed because the directory service is not the master for that type of operation.",	NULL	},
	{	ERROR_DS_RIDMGR_INIT_ERROR,			"ERROR_DS_RIDMGR_INIT_ERROR",
		"The directory service was unable to initialize the subsystem that allocates relative identifiers.",	NULL	},
	{	ERROR_DS_OBJ_CLASS_VIOLATION,			"ERROR_DS_OBJ_CLASS_VIOLATION",
		"The requested operation did not satisfy one or more constraints associated with the class of the object.",	NULL	},
	{	ERROR_DS_CANT_ON_NON_LEAF,			"ERROR_DS_CANT_ON_NON_LEAF",
		"The directory service can perform the requested operation only on a leaf object.",	NULL	},
	{	ERROR_DS_CANT_ON_RDN,			"ERROR_DS_CANT_ON_RDN",
		"The directory service cannot perform the requested operation on the RDN attribute of an object.",	NULL	},
	{	ERROR_DS_CANT_MOD_OBJ_CLASS,			"ERROR_DS_CANT_MOD_OBJ_CLASS",
		"The directory service detected an attempt to modify the object class of an object.",	NULL	},
	{	ERROR_DS_CROSS_DOM_MOVE_ERROR,			"ERROR_DS_CROSS_DOM_MOVE_ERROR",
		"The requested cross domain move operation could not be performed.",	NULL	},
	{	ERROR_DS_GC_NOT_AVAILABLE,			"ERROR_DS_GC_NOT_AVAILABLE",
		"Unable to contact the global catalog server.",	NULL	},
	{	ERROR_NO_BROWSER_SERVERS_FOUND,			"ERROR_NO_BROWSER_SERVERS_FOUND",
		"The list of servers for this workgroup is not currently available",	NULL	},
	{	ERROR_INVALID_PIXEL_FORMAT,			"ERROR_INVALID_PIXEL_FORMAT",
		"The pixel format is invalid.",	NULL	},
	{	ERROR_BAD_DRIVER,			"ERROR_BAD_DRIVER",
		"The specified driver is invalid.",	NULL	},
	{	ERROR_INVALID_WINDOW_STYLE,			"ERROR_INVALID_WINDOW_STYLE",
		"The window style or class attribute is invalid for this operation.",	NULL	},
	{	ERROR_METAFILE_NOT_SUPPORTED,			"ERROR_METAFILE_NOT_SUPPORTED",
		"The requested metafile operation is not supported.",	NULL	},
	{	ERROR_TRANSFORM_NOT_SUPPORTED,			"ERROR_TRANSFORM_NOT_SUPPORTED",
		"The requested transformation operation is not supported.",	NULL	},
	{	ERROR_CLIPPING_NOT_SUPPORTED,			"ERROR_CLIPPING_NOT_SUPPORTED",
		"The requested clipping operation is not supported.",	NULL	},
	{	ERROR_INVALID_CMM,			"ERROR_INVALID_CMM",
		"The specified color management module is invalid.",	NULL	},
	{	ERROR_INVALID_PROFILE,			"ERROR_INVALID_PROFILE",
		"The specified color profile is invalid.",	NULL	},
	{	ERROR_TAG_NOT_FOUND,			"ERROR_TAG_NOT_FOUND",
		"The specified tag was not found.",	NULL	},
	{	ERROR_TAG_NOT_PRESENT,			"ERROR_TAG_NOT_PRESENT",
		"A required tag is not present.",	NULL	},
	{	ERROR_DUPLICATE_TAG,			"ERROR_DUPLICATE_TAG",
		"The specified tag is already present.",	NULL	},
	{	ERROR_PROFILE_NOT_ASSOCIATED_WITH_DEVICE,			"ERROR_PROFILE_NOT_ASSOCIATED_WITH_DEVICE",
		"The specified color profile is not associated with any device.",	NULL	},
	{	ERROR_PROFILE_NOT_FOUND,			"ERROR_PROFILE_NOT_FOUND",
		"The specified color profile was not found.",	NULL	},
	{	ERROR_INVALID_COLORSPACE,			"ERROR_INVALID_COLORSPACE",
		"The specified color space is invalid.",	NULL	},
	{	ERROR_ICM_NOT_ENABLED,			"ERROR_ICM_NOT_ENABLED",
		"Image Color Management is not enabled.",	NULL	},
	{	ERROR_DELETING_ICM_XFORM,			"ERROR_DELETING_ICM_XFORM",
		"There was an error while deleting the color transform.",	NULL	},
	{	ERROR_INVALID_TRANSFORM,			"ERROR_INVALID_TRANSFORM",
		"The specified color transform is invalid.",	NULL	},
	{	ERROR_UNKNOWN_PRINT_MONITOR,			"ERROR_UNKNOWN_PRINT_MONITOR",
		"The specified print monitor is unknown.",	NULL	},
	{	ERROR_PRINTER_DRIVER_IN_USE,			"ERROR_PRINTER_DRIVER_IN_USE",
		"The specified printer driver is currently in use.",	NULL	},
	{	ERROR_SPOOL_FILE_NOT_FOUND,			"ERROR_SPOOL_FILE_NOT_FOUND",
		"The spool file was not found.",	NULL	},
	{	ERROR_SPL_NO_STARTDOC,			"ERROR_SPL_NO_STARTDOC",
		"A StartDocPrinter call was not issued.",	NULL	},
	{	ERROR_SPL_NO_ADDJOB,			"ERROR_SPL_NO_ADDJOB",
		"An AddJob call was not issued.",	NULL	},
	{	ERROR_PRINT_PROCESSOR_ALREADY_INSTALLED,			"ERROR_PRINT_PROCESSOR_ALREADY_INSTALLED",
		"The specified print processor has already been installed.",	NULL	},
	{	ERROR_PRINT_MONITOR_ALREADY_INSTALLED,			"ERROR_PRINT_MONITOR_ALREADY_INSTALLED",
		"The specified print monitor has already been installed.",	NULL	},
	{	ERROR_INVALID_PRINT_MONITOR,			"ERROR_INVALID_PRINT_MONITOR",
		"The specified print monitor does not have the required functions.",	NULL	},
	{	ERROR_PRINT_MONITOR_IN_USE,			"ERROR_PRINT_MONITOR_IN_USE",
		"The specified print monitor is currently in use.",	NULL	},
	{	ERROR_PRINTER_HAS_JOBS_QUEUED,			"ERROR_PRINTER_HAS_JOBS_QUEUED",
		"The requested operation is not allowed when there are jobs queued to the printer.",	NULL	},
	{	ERROR_SUCCESS_REBOOT_REQUIRED,			"ERROR_SUCCESS_REBOOT_REQUIRED",
		"The requested operation is successful.  Changes will not be effective until the system is rebooted.",	NULL	},
	{	ERROR_SUCCESS_RESTART_REQUIRED,			"ERROR_SUCCESS_RESTART_REQUIRED",
		"The requested operation is successful.  Changes will not be effective until the service is restarted.",	NULL	},
	{	ERROR_WINS_INTERNAL,			"ERROR_WINS_INTERNAL",
		"WINS encountered an error while processing the command.",	NULL	},
	{	ERROR_CAN_NOT_DEL_LOCAL_WINS,			"ERROR_CAN_NOT_DEL_LOCAL_WINS",
		"The local WINS can not be deleted.",	NULL	},
	{	ERROR_STATIC_INIT,			"ERROR_STATIC_INIT",
		"The importation from the file failed.",	NULL	},
	{	ERROR_INC_BACKUP,			"ERROR_INC_BACKUP",
		"The backup failed. Was a full backup done before?",	NULL	},
	{	ERROR_FULL_BACKUP,			"ERROR_FULL_BACKUP",
		"The backup failed. Check the directory to which you are backing the database.",	NULL	},
	{	ERROR_REC_NON_EXISTENT,			"ERROR_REC_NON_EXISTENT",
		"The name does not exist in the WINS database.",	NULL	},
	{	ERROR_RPL_NOT_ALLOWED,			"ERROR_RPL_NOT_ALLOWED",
		"Replication with a nonconfigured partner is not allowed.",	NULL	},
	{	ERROR_DHCP_ADDRESS_CONFLICT,			"ERROR_DHCP_ADDRESS_CONFLICT",
		"The DHCP client has obtained an IP address that is already in use on the network.  The local interface will be disabled until the DHCP client can obtain a new address.",	NULL	},
	{	ERROR_WMI_GUID_NOT_FOUND,			"ERROR_WMI_GUID_NOT_FOUND",
		"The GUID passed was not recognized as valid by a WMI data provider.",	NULL	},
	{	ERROR_WMI_INSTANCE_NOT_FOUND,			"ERROR_WMI_INSTANCE_NOT_FOUND",
		"The instance name passed was not recognized as valid by a WMI data provider.",	NULL	},
	{	ERROR_WMI_ITEMID_NOT_FOUND,			"ERROR_WMI_ITEMID_NOT_FOUND",
		"The data item ID passed was not recognized as valid by a WMI data provider.",	NULL	},
	{	ERROR_WMI_TRY_AGAIN,			"ERROR_WMI_TRY_AGAIN",
		"The WMI request could not be completed and should be retried.",	NULL	},
	{	ERROR_WMI_DP_NOT_FOUND,			"ERROR_WMI_DP_NOT_FOUND",
		"The WMI data provider could not be located.",	NULL	},
	{	ERROR_WMI_UNRESOLVED_INSTANCE_REF,			"ERROR_WMI_UNRESOLVED_INSTANCE_REF",
		"The WMI data provider references an instance set that has not been registered.",	NULL	},
	{	ERROR_WMI_ALREADY_ENABLED,			"ERROR_WMI_ALREADY_ENABLED",
		"The WMI data block or event notification has already been enabled.",	NULL	},
	{	ERROR_WMI_GUID_DISCONNECTED,			"ERROR_WMI_GUID_DISCONNECTED",
		"The WMI data block is no longer available.",	NULL	},
	{	ERROR_WMI_SERVER_UNAVAILABLE,			"ERROR_WMI_SERVER_UNAVAILABLE",
		"The WMI data service is not available.",	NULL	},
	{	ERROR_WMI_DP_FAILED,			"ERROR_WMI_DP_FAILED",
		"The WMI data provider failed to carry out the request.",	NULL	},
	{	ERROR_WMI_INVALID_MOF,			"ERROR_WMI_INVALID_MOF",
		"The WMI MOF information is not valid.",	NULL	},
	{	ERROR_WMI_INVALID_REGINFO,			"ERROR_WMI_INVALID_REGINFO",
		"The WMI registration information is not valid.",	NULL	},
	{	ERROR_INVALID_MEDIA,			"ERROR_INVALID_MEDIA",
		"The media identifier does not represent a valid medium.",	NULL	},
	{	ERROR_INVALID_LIBRARY,			"ERROR_INVALID_LIBRARY",
		"The library identifier does not represent a valid library.",	NULL	},
	{	ERROR_INVALID_MEDIA_POOL,			"ERROR_INVALID_MEDIA_POOL",
		"The media pool identifier does not represent a valid media pool.",	NULL	},
	{	ERROR_DRIVE_MEDIA_MISMATCH,			"ERROR_DRIVE_MEDIA_MISMATCH",
		"The drive and medium are not compatible or exist in different libraries.",	NULL	},
	{	ERROR_MEDIA_OFFLINE,			"ERROR_MEDIA_OFFLINE",
		"The medium currently exists in an offline library and must be online to perform this operation.",	NULL	},
	{	ERROR_LIBRARY_OFFLINE,			"ERROR_LIBRARY_OFFLINE",
		"The operation cannot be performed on an offline library.",	NULL	},
	{	ERROR_EMPTY,			"ERROR_EMPTY",
		"The library, drive, or media pool is empty.",	NULL	},
	{	ERROR_NOT_EMPTY,			"ERROR_NOT_EMPTY",
		"The library, drive, or media pool must be empty to perform this operation.",	NULL	},
	{	ERROR_MEDIA_UNAVAILABLE,			"ERROR_MEDIA_UNAVAILABLE",
		"No media is currently available in this media pool or library.",	NULL	},
	{	ERROR_RESOURCE_DISABLED,			"ERROR_RESOURCE_DISABLED",
		"A resource required for this operation is disabled.",	NULL	},
	{	ERROR_INVALID_CLEANER,			"ERROR_INVALID_CLEANER",
		"The media identifier does not represent a valid cleaner.",	NULL	},
	{	ERROR_UNABLE_TO_CLEAN,			"ERROR_UNABLE_TO_CLEAN",
		"The drive cannot be cleaned or does not support cleaning.",	NULL	},
	{	ERROR_OBJECT_NOT_FOUND,			"ERROR_OBJECT_NOT_FOUND",
		"The object identifier does not represent a valid object.",	NULL	},
	{	ERROR_DATABASE_FAILURE,			"ERROR_DATABASE_FAILURE",
		"Unable to read from or write to the database.",	NULL	},
	{	ERROR_DATABASE_FULL,			"ERROR_DATABASE_FULL",
		"The database is full.",	NULL	},
	{	ERROR_MEDIA_INCOMPATIBLE,			"ERROR_MEDIA_INCOMPATIBLE",
		"The medium is not compatible with the device or media pool.",	NULL	},
	{	ERROR_RESOURCE_NOT_PRESENT,			"ERROR_RESOURCE_NOT_PRESENT",
		"The resource required for this operation does not exist.",	NULL	},
	{	ERROR_INVALID_OPERATION,			"ERROR_INVALID_OPERATION",
		"The operation identifier is not valid.",	NULL	},
	{	ERROR_MEDIA_NOT_AVAILABLE,			"ERROR_MEDIA_NOT_AVAILABLE",
		"The media is not mounted or ready for use.",	NULL	},
	{	ERROR_DEVICE_NOT_AVAILABLE,			"ERROR_DEVICE_NOT_AVAILABLE",
		"The device is not ready for use.",	NULL	},
	{	ERROR_REQUEST_REFUSED,			"ERROR_REQUEST_REFUSED",
		"The operator or administrator has refused the request.",	NULL	},
	{	ERROR_FILE_OFFLINE,			"ERROR_FILE_OFFLINE",
		"The remote storage service was not able to recall the file.",	NULL	},
	{	ERROR_REMOTE_STORAGE_NOT_ACTIVE,			"ERROR_REMOTE_STORAGE_NOT_ACTIVE",
		"The remote storage service is not operational at this time.",	NULL	},
	{	ERROR_REMOTE_STORAGE_MEDIA_ERROR,			"ERROR_REMOTE_STORAGE_MEDIA_ERROR",
		"The remote storage service encountered a media error.",	NULL	},
	{	ERROR_NOT_A_REPARSE_POINT,			"ERROR_NOT_A_REPARSE_POINT",
		"The file or directory is not a reparse point.",	NULL	},
	{	ERROR_REPARSE_ATTRIBUTE_CONFLICT,			"ERROR_REPARSE_ATTRIBUTE_CONFLICT",
		"The reparse point attribute cannot be set because it conflicts with an existing attribute.",	NULL	},
	{	ERROR_DEPENDENT_RESOURCE_EXISTS,			"ERROR_DEPENDENT_RESOURCE_EXISTS",
		"The cluster resource cannot be moved to another group because other resources are dependent on it.",	NULL	},
	{	ERROR_DEPENDENCY_NOT_FOUND,			"ERROR_DEPENDENCY_NOT_FOUND",
		"The cluster resource dependency cannot be found.",	NULL	},
	{	ERROR_DEPENDENCY_ALREADY_EXISTS,			"ERROR_DEPENDENCY_ALREADY_EXISTS",
		"The cluster resource cannot be made dependent on the specified resource because it is already dependent.",	NULL	},
	{	ERROR_RESOURCE_NOT_ONLINE,			"ERROR_RESOURCE_NOT_ONLINE",
		"The cluster resource is not online.",	NULL	},
	{	ERROR_HOST_NODE_NOT_AVAILABLE,			"ERROR_HOST_NODE_NOT_AVAILABLE",
		"A cluster node is not available for this operation.",	NULL	},
	{	ERROR_RESOURCE_NOT_AVAILABLE,			"ERROR_RESOURCE_NOT_AVAILABLE",
		"The cluster resource is not available.",	NULL	},
	{	ERROR_RESOURCE_NOT_FOUND,			"ERROR_RESOURCE_NOT_FOUND",
		"The cluster resource could not be found.",	NULL	},
	{	ERROR_SHUTDOWN_CLUSTER,			"ERROR_SHUTDOWN_CLUSTER",
		"The cluster is being shut down.",	NULL	},
	{	ERROR_CANT_EVICT_ACTIVE_NODE,			"ERROR_CANT_EVICT_ACTIVE_NODE",
		"A cluster node cannot be evicted from the cluster while it is online.",	NULL	},
	{	ERROR_OBJECT_ALREADY_EXISTS,			"ERROR_OBJECT_ALREADY_EXISTS",
		"The object already exists.",	NULL	},
	{	ERROR_OBJECT_IN_LIST,			"ERROR_OBJECT_IN_LIST",
		"The object is already in the list.",	NULL	},
	{	ERROR_GROUP_NOT_AVAILABLE,			"ERROR_GROUP_NOT_AVAILABLE",
		"The cluster group is not available for any new requests.",	NULL	},
	{	ERROR_GROUP_NOT_FOUND,			"ERROR_GROUP_NOT_FOUND",
		"The cluster group could not be found.",	NULL	},
	{	ERROR_GROUP_NOT_ONLINE,			"ERROR_GROUP_NOT_ONLINE",
		"The operation could not be completed because the cluster group is not online.",	NULL	},
	{	ERROR_HOST_NODE_NOT_RESOURCE_OWNER,			"ERROR_HOST_NODE_NOT_RESOURCE_OWNER",
		"The cluster node is not the owner of the resource.",	NULL	},
	{	ERROR_HOST_NODE_NOT_GROUP_OWNER,			"ERROR_HOST_NODE_NOT_GROUP_OWNER",
		"The cluster node is not the owner of the group.",	NULL	},
	{	ERROR_RESMON_CREATE_FAILED,			"ERROR_RESMON_CREATE_FAILED",
		"The cluster resource could not be created in the specified resource monitor.",	NULL	},
	{	ERROR_RESMON_ONLINE_FAILED,			"ERROR_RESMON_ONLINE_FAILED",
		"The cluster resource could not be brought online by the resource monitor.",	NULL	},
	{	ERROR_RESOURCE_ONLINE,			"ERROR_RESOURCE_ONLINE",
		"The operation could not be completed because the cluster resource is online.",	NULL	},
	{	ERROR_QUORUM_RESOURCE,			"ERROR_QUORUM_RESOURCE",
		"The cluster resource could not be deleted or brought offline because it is the quorum resource.",	NULL	},
	{	ERROR_NOT_QUORUM_CAPABLE,			"ERROR_NOT_QUORUM_CAPABLE",
		"The cluster could not make the specified resource a quorum resource because it is not capable of being a quorum resource.",	NULL	},
	{	ERROR_CLUSTER_SHUTTING_DOWN,			"ERROR_CLUSTER_SHUTTING_DOWN",
		"The cluster software is shutting down.",	NULL	},
	{	ERROR_INVALID_STATE,			"ERROR_INVALID_STATE",
		"The group or resource is not in the correct state to perform the requested operation.",	NULL	},
	{	ERROR_RESOURCE_PROPERTIES_STORED,			"ERROR_RESOURCE_PROPERTIES_STORED",
		"The properties were stored but not all changes will take effect until the next time the resource is brought online.",	NULL	},
	{	ERROR_NOT_QUORUM_CLASS,			"ERROR_NOT_QUORUM_CLASS",
		"The cluster could not make the specified resource a quorum resource because it does not belong to a shared storage class.",	NULL	},
	{	ERROR_CORE_RESOURCE,			"ERROR_CORE_RESOURCE",
		"The cluster resource could not be deleted since it is a core resource.",	NULL	},
	{	ERROR_QUORUM_RESOURCE_ONLINE_FAILED,			"ERROR_QUORUM_RESOURCE_ONLINE_FAILED",
		"The quorum resource failed to come online.",	NULL	},
	{	ERROR_QUORUMLOG_OPEN_FAILED,			"ERROR_QUORUMLOG_OPEN_FAILED",
		"The quorum log could not be created or mounted successfully.",	NULL	},
	{	ERROR_CLUSTERLOG_CORRUPT,			"ERROR_CLUSTERLOG_CORRUPT",
		"The cluster log is corrupt.",	NULL	},
	{	ERROR_CLUSTERLOG_RECORD_EXCEEDS_MAXSIZE,			"ERROR_CLUSTERLOG_RECORD_EXCEEDS_MAXSIZE",
		"The record could not be written to the cluster log since it exceeds the maximum size.",	NULL	},
	{	ERROR_CLUSTERLOG_EXCEEDS_MAXSIZE,			"ERROR_CLUSTERLOG_EXCEEDS_MAXSIZE",
		"The cluster log exceeds its maximum size.",	NULL	},
	{	ERROR_CLUSTERLOG_CHKPOINT_NOT_FOUND,			"ERROR_CLUSTERLOG_CHKPOINT_NOT_FOUND",
		"No checkpoint record was found in the cluster log.",	NULL	},
	{	ERROR_CLUSTERLOG_NOT_ENOUGH_SPACE,			"ERROR_CLUSTERLOG_NOT_ENOUGH_SPACE",
		"The minimum required disk space needed for logging is not available.",	NULL	},
	{	ERROR_ENCRYPTION_FAILED,			"ERROR_ENCRYPTION_FAILED",
		"The specified file could not be encrypted.",	NULL	},
	{	ERROR_DECRYPTION_FAILED,			"ERROR_DECRYPTION_FAILED",
		"The specified file could not be decrypted.",	NULL	},
	{	ERROR_FILE_ENCRYPTED,			"ERROR_FILE_ENCRYPTED",
		"The specified file is encrypted and the user does not have the ability to decrypt it.",	NULL	},
	{	ERROR_NO_RECOVERY_POLICY,			"ERROR_NO_RECOVERY_POLICY",
		"There is no encryption recovery policy configured for this system.",	NULL	},
	{	ERROR_NO_EFS,			"ERROR_NO_EFS",
		"The required encryption driver is not loaded for this system.",	NULL	},
	{	ERROR_WRONG_EFS,			"ERROR_WRONG_EFS",
		"The file was encrypted with a different encryption driver than is currently loaded.",	NULL	},
	{	ERROR_NO_USER_KEYS,			"ERROR_NO_USER_KEYS",
		"There are no EFS keys defined for the user.",	NULL	},
	{	ERROR_FILE_NOT_ENCRYPTED,			"ERROR_FILE_NOT_ENCRYPTED",
		"The specified file is not encrypted.",	NULL	},
	{	ERROR_NOT_EXPORT_FORMAT,			"ERROR_NOT_EXPORT_FORMAT",
		"The specified file is not in the defined EFS export format.",	NULL	}
};
static const unsigned int   SRC_GEN_ErrorCount_Win32  =
	sizeof(SRC_GEN_ErrorList_Win32) / sizeof(SRC_GEN_ErrorList_Win32[0]);
/*	***********************************************************************	*/

#define GEN_ERROR_PERL_MERGE_FILE		"GenErrorList.c"

/*	***********************************************************************	*/
#ifndef NARGS
static int GEN_ERROR_CreateWin32List(char *error_text)
#else
static int GEN_ERROR_CreateWin32List(error_text)
char *error_text;
#endif /* #ifndef NARGS */
{
	int                   return_code = GENFUNCS_SUCCESS;
	FILE                 *file_ptr    = NULL;
	unsigned int          count_1;
	char                 *tmp_ptr_1;
	char                 *tmp_ptr_2;
	char                 *char_ptr;
	const GEN_ERROR_SPEC *spec_ptr;
	HMODULE               lib_handle;
   LPVOID                long_description;

   lib_handle = LoadLibrary("NTDLL.DLL");

	if ((file_ptr = fopen(GEN_ERROR_PERL_MERGE_FILE, "wb+")) == NULL) {
		sprintf(error_text, "%s '%-.500s' for writing --- ",
			"Unable to open the file", GEN_ERROR_PERL_MERGE_FILE);
		GEN_AppendLastErrorString(0, GENFUNCS_MAX_ERROR_TEXT - 1, error_text);
		return_code = GENFUNCS_SYSTEM_FAILURE;
		goto EXIT_FUNCTION;
	}

	printf("#ifdef _Windows\n");
	printf("/*\t%s\t*/\n",
"***********************************************************************");
	printf("static const GEN_ERROR_SPEC GEN_ErrorList_Win32[] = {\n");

	for (count_1 = 0, spec_ptr = SRC_GEN_ErrorList_Win32;
		count_1 < SRC_GEN_ErrorCount_Win32; count_1++, spec_ptr++) {
		tmp_ptr_1 = NULL;
		tmp_ptr_2 = NULL;
		if ((tmp_ptr_1 = strdup(spec_ptr->short_description)) == NULL) {
			strcpy(error_text, "Unable to copy the short description.");
			return_code = GENFUNCS_MEMORY_FAILURE;
			goto EXIT_FUNCTION;
		}
		if (spec_ptr->long_description == NULL) {
			if ((FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
				FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_FROM_HMODULE,
				lib_handle, ((DWORD) spec_ptr->error_code),
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				(LPTSTR) &long_description, 0, NULL) != 0) &&
				(long_description != NULL)) {
				if ((tmp_ptr_2 = strdup(((char *) long_description))) == NULL) {
					strcpy(error_text, "Unable to copy the long description.");
					return_code = GENFUNCS_MEMORY_FAILURE;
					goto EXIT_FUNCTION;
				}
				LocalFree(long_description);
				if (!(count_1 % 1000))
					Sleep(1L);
			}
		}
		else if ((tmp_ptr_2 = strdup(((char *) spec_ptr->long_description))) ==
			NULL) {
			strcpy(error_text, "Unable to copy the long description.");
			return_code = GENFUNCS_MEMORY_FAILURE;
			goto EXIT_FUNCTION;
		}
		trim(oneblank(ctltospc(tmp_ptr_1)));
		if (tmp_ptr_2 != NULL)
			trim(oneblank(ctltospc(tmp_ptr_2)));
		if (!iscsymf(*spec_ptr->error_name))
			printf("# ifdef %s\n", spec_ptr->error_name);
		printf("\t{\t%s,\t\t\t\"%s\",\n",
			spec_ptr->error_name, spec_ptr->error_name);
		printf("\t\t\"");
		char_ptr = tmp_ptr_1;
		while (*char_ptr) {
			if (*char_ptr == '\\')
				printf("\\\\");
			else if (*char_ptr == '\"')
				printf("\\\"");
			else
				printf("%c", *char_ptr);
			char_ptr++;
		}
		printf("\",\t\"");
		if (tmp_ptr_2 != NULL) {
			char_ptr = tmp_ptr_2;
			while (*char_ptr) {
				if (*char_ptr == '\\')
					printf("\\\\");
				else if (*char_ptr == '\"')
					printf("\\\"");
				else
					printf("%c", *char_ptr);
				char_ptr++;
			}
		}
		else
			printf("%s", tmp_ptr_2);
		printf("\"\t},\n");
		if (!iscsymf(*spec_ptr->error_name))
			printf("# endif /* # ifdef %s */ \n", spec_ptr->error_name);
		fprintf(file_ptr, "%s\t%s\n", spec_ptr->error_name, tmp_ptr_1);
		if (tmp_ptr_1 != NULL)
			free(tmp_ptr_1);
		if (tmp_ptr_2 != NULL)
			free(tmp_ptr_2);
	}

	printf("};\n");
	printf("static const unsigned int GEN_ErrorCount_Win32 =\n");
	printf("\t(sizeof(GEN_ErrorList_Win32) / sizeof(GEN_ErrorList_Win32[0]));\n");
	printf("/*\t%s\t*/\n",
"***********************************************************************");
	printf("#endif /* #ifdef _Windows */\n\n");

EXIT_FUNCTION:

   FreeLibrary(lib_handle);

	if (file_ptr != NULL)
		fclose(file_ptr);

	return(return_code);
}
/*	***********************************************************************	*/
# endif /* #ifdef _Windows */

#endif /* #ifdef TEST_MAIN */


