#ifndef h__rpc_PMAP_CLNT_H__h

#define h__rpc_PMAP_CLNT_H__h				1

#include <rpc/types.h>

#ifndef NARGS
bool_t pmap_set(u_long prognum, u_long versnum, int protocol,
	u_short port);
bool_t pmap_unset(u_long prognum, u_long versnum);
#else
#endif /* #ifndef NARGS */

#endif /* #ifndef h__rpc_PMAP_CLNT_H__h */

