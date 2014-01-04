#ifndef h__rpc_SVC_H__h

#define h__rpc_SVC_H__h	1

#include <rpc/types.h>
#include <rpc/xdr.h>

#define RPC_ANYSOCK							-1

extern int svc_fds;

extern fd_set svc_fdset;

typedef struct {
	int     xp_sock;
	u_short xp_port;
} SVCXPRT;

struct svc_req {
	u_long   rq_prog;
	u_long   rq_vers;
	u_long   rq_proc;
	SVCXPRT *rq_xprt;
};

#ifndef NARGS
void                svc_destroy(SVCXPRT *xprt);
bool_t              svc_freeargs(SVCXPRT *xprt, xdrproc_t inproc, void *in);
bool_t              svc_getargs(SVCXPRT *xprt, xdrproc_t inproc, void *in);
struct sockaddr_in *svc_getcaller(SVCXPRT *xprt);
void                svc_getreq(int rdfds);
void                svc_getreqset(fd_set *rdfdsp);
bool_t              svc_register(SVCXPRT *xprt, u_long prog, u_long vers,
	void (*dispatch)(), int protocol);
bool_t              svc_sendreply(SVCXPRT *xprt, xdrproc_t outproc,
	void *out);
SVCXPRT            *svctcp_create(int sock, u_int sendsz, u_int recvsz);
SVCXPRT            *svcudp_bufcreate(int sock, u_int sendsz, u_int recvsz);
SVCXPRT            *svcudp_create(int sock);
void                svc_run(void);
void                svc_unregister(u_long prog, u_long vers);
#else
#endif /* #ifndef NARGS */

#endif /* #ifndef h__rpc_SVC_H__h */

