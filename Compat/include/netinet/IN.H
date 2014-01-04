#ifndef h__netinet_IN_H__h

#define h__netinet_IN_H__h					1

#define IPPROTO_TCP							6
#define IPPROTO_UDP							17

struct in_addr {
	union {
		struct {
			unsigned char s_b1;
			unsigned char s_b2;
			unsigned char s_b3;
			unsigned char s_b4;
		} S_un_b;
		struct {
			unsigned short s_w1;
			unsigned short s_w2;
		} S_un_w;
		unsigned long S_addr;
	} S_un;
};

struct sockaddr_in {
	short          sin_family;
	unsigned short sin_port;
	struct in_addr sin_addr;
	char           sin_zero[8];
};

#endif /* #ifndef h__netinet_IN_H__h */

