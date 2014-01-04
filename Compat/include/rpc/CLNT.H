#ifndef h__rpc_CLIENT_H__h

#define h__rpc_CLIENT_H__h

#include <rpc/types.h>
#include <rpc/xdr.h>

typedef struct {
	char stuff[100];
} CLIENT;

enum clnt_stat {
	RPC_SUCCESS=0,
	RPC_CANTENCODEARGS,
	RPC_TIMEDOUT
};

#define NULLPROC								((u_long) 0)

#define CLSET_TIMEOUT						0
#define CLGET_TIMEOUT						0
#define CLGET_SERVER_ADDR					0
#define CLGET_FD								0
#define CLSET_FD_CLOSE						0
#define CLSET_FD_NCLOSE						0
#define CLSET_RETRY_TIMEOUT				0
#define CLGET_RETRY_TIMEOUT				0

#ifndef NARGS
enum clnt_stat  clnt_broadcast_exp(u_long prognum, u_long versnum,
	u_long procnum, xdrproc_t inproc, void *in, xdrproc_t outproc, void *out,
	int (*eachresult)(void *, struct sockaddr_in *addr), int bcast_init_time,
	int bcast_wait_time);
enum clnt_stat  clnt_call(CLIENT *clnt, u_long procnum, xdrproc_t inproc,
	void *in, xdrproc_t outproc, void *out, struct timeval timeout);
bool_t          clnt_control(CLIENT *clnt, int request, void *info);
CLIENT         *clnt_create(char *host, u_long prognum, u_long versnum,
	char *protocol);
void            clnt_destroy(CLIENT *clnt);
bool_t          clnt_freeres(CLIENT *clnt, xdrproc_t outproc, void *out);
char           *clnt_spcreateerror(char *str);
char           *clnt_sperror(CLIENT *clnt, char *str);
char           *clnt_sperrno(enum clnt_stat);
CLIENT         *clnttcp_create(struct sockaddr_in *addr, u_long prognum,
	u_long versnum, int *sockp, u_int sendsz, u_int recvsz);
CLIENT         *clntudp_bufcreate(struct sockaddr_in *addr, u_long prognum,
	u_long versnum, struct timeval wait, int *sockp, u_int sendsz,
	u_int recvsz);
CLIENT         *clntudp_create(struct sockaddr_in *addr, u_long prognum,
	u_long versnum, struct timeval wait, int *sockp);
#else
#endif /* #ifndef NARGS */
#endif /* #ifndef h__rpc_CLIENT_H__h */

