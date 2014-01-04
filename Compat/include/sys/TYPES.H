#ifndef h__sys_TYPES_H__h

#define h__sys_TYPES_H__h					1

typedef long fd_mask;

typedef struct fd_set {
	fd_mask fds_bits[8];
} fd_set;

#endif /* #ifndef h__sys_TYPES_H__h */

