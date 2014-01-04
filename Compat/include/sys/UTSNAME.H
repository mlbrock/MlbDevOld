#ifndef H__utsname_h__H

#define H__utsname_h__H						1

struct utsname {
	char sysname[9];
	char nodename[9];
	char nodeext[65 - 9];
	char release[9];
	char version[9];
	char machine[9];
};

#ifndef NARGS
int uname(struct utsname *uts_data_ptr);
#else
int uname();
#endif /* #ifndef NARGS */

#endif /* #ifndef H__utsname_h__H */

