#ifndef h__sys_SOCKET_H__h

#define h__sys_SOCKET_H__h					1

struct sockaddr {
	unsigned short sa_family;
	char           sa_data[14];
};

#define AF_UNSPEC								0
#define AF_UNIX								1
#define AF_INET								2

#endif /* #ifndef h__sys_SOCKET_H__h */

