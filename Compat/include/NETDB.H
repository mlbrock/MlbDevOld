#ifndef h__NETDB_H__h

#define h__NETDB_H__h						1

struct hostent {
	char  *h_name;
	char **h_aliases;
	int    h_addrtype;
	int    h_length;
	char **h_addr_list;
#define h_addr h_addr_list[0];
};

struct hostent *gethostbyaddr(char *addr, int len, int type);
struct hostent *gethostbyname(char *name);

#endif /* #ifndef h__NETDB_H__h */

