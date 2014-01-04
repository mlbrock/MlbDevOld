#ifndef h__rpc_XDR_H__h

#define h__rpc_XDR_H__h						1

#include <rpc/types.h>

typedef struct {
	char stuff[10];
} XDR;

typedef bool_t (*xdrproc_t)();

struct xdr_discrim {
	int       value;
	xdrproc_t proc;
};

#ifndef NARGS
bool_t xdr_bool(XDR *xdrs, bool_t *data_ptr);
bool_t xdr_char(XDR *xdrs, char *data_ptr);
bool_t xdr_double(XDR *xdrs, double *data_ptr);
bool_t xdr_enum(XDR *xdrs, enum_t *data_ptr);
bool_t xdr_float(XDR *xdrs, float *data_ptr);
bool_t xdr_int(XDR *xdrs, int *data_ptr);
bool_t xdr_long(XDR *xdrs, long *data_ptr);
bool_t xdr_short(XDR *xdrs, short *data_ptr);
bool_t xdr_u_char(XDR *xdrs, unsigned char *data_ptr);
bool_t xdr_u_int(XDR *xdrs, unsigned int *data_ptr);
bool_t xdr_u_long(XDR *xdrs, unsigned long *data_ptr);
bool_t xdr_u_short(XDR *xdrs, unsigned short *data_ptr);
bool_t xdr_void(void);
#else
#endif /* #ifndef NARGS */

#ifndef NARGS
bool_t xdr_array(XDR *xdrs, char **arrp, u_int *sizep, u_int maxsize,
	u_int elsize, xdrproc_t elproc);
bool_t xdr_bytes(XDR *xdrs, char **arrp, u_int *sizep, u_int maxsize);
bool_t xdr_opaque(XDR *xdrs, char *cp, u_int cnt);
bool_t xdr_pointer(XDR *xdrs, char **objpp, u_int *objsize,
	xdrproc_t objproc);
bool_t xdr_reference(XDR *xdrs, char *pp, u_int size, xdrproc_t proc);
bool_t xdr_string(XDR *xdrs, char **strp, u_int maxsize);
bool_t xdr_union(XDR *xdrs, int *dscmp, char *unp,
	struct xdr_discrim *choices, bool_t (*defaultarm)());
bool_t xdr_vector(XDR *xdrs, char *arrp, u_int size, u_int elsize,
	xdrproc_t elproc);
bool_t xdr_wrapstring(XDR *xdrs, char **strp);
#else
#endif /* #ifndef NARGS */

#endif /* #ifndef h__rpc_XDR_H__h */

