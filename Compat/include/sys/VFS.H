/*
	sys/vfs.h
*/

#ifndef h__VFS_H__h

#define h__VFS_H__h							1

typedef struct {
	long val[2];
} fsid_t;

struct statfs {
	long   f_type;
	long   f_bsize;
	long   f_blocks;
	long   f_bfree;
	long   f_bavail;
	long   f_files;
	long   f_ffree;
	fsid_t f_fsid;
	long   f_spare[7];
};

#ifndef NARGS
int statfs(char *path, struct statfs *buf);
int fstatfs(int fd, struct statfs *buf);
#else
int statfs();
int fstatfs();
#endif /* #ifndef NARGS */

#endif /* #ifndef h__VFS_H__h */


