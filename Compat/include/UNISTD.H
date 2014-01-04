#ifndef h__UNISTD_H__h

#define h__UNISTD_H__h	1

#ifndef F_OK
#define F_OK									0
#endif /* #ifndef F_OK */

int access(const char *path, int access_mode);

#endif /* #ifndef h__UNISTD_H__h */
