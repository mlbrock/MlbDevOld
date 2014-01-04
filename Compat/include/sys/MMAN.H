#define PROT_READ		1
#define PROT_WRITE	2

#define MAP_SHARED	1
#define MAP_PRIVATE	2

#define MS_ASYNC		1

#define MADV_SEQUENTIAL	0
#define MADV_RANDOM		0
#define MADV_DONTNEED	0

#ifndef NARGS
void *mmap(void *, long, int, int, int, int);
int   munmap(void *, int);
int   msync(char *, int, int);
int   madvise(void *, long, int);
#else
#endif /* #ifndef NARGS */

