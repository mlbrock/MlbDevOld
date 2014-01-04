#ifndef h__SYSLOG_H__h

#define h__SYSLOG_H__h	1

#define LOG_EMERG								0
#define LOG_ALERT								1
#define LOG_CRIT								2
#define LOG_ERR								3
#define LOG_WARNING							4
#define LOG_NOTICE							5
#define LOG_INFO								6
#define LOG_DEBUG								7

#define LOG_USER								(1 << 3)

#define LOG_PID								0X01
#define LOG_CONS								0X02
#define LOG_ODELAY							0X04
#define LOG_NDELAY							0X08
#define LOG_NOWAIT							0X10

#ifndef NARGS
void openlog(char *ident, int logopt, int facility);
void syslog(int priority, char *format, ...);
void closelog(void);
int  setlogmask(int maskpri);
#else
void openlog();
void syslog();
void closelog();
int  setlogmask();
#endif /* #ifndef NARGS */

#endif /* #ifndef h__SYSLOG_H__h */

