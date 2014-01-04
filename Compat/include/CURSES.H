#ifndef h__CURSES_H__h

#define h__CURSES_H__h						1

#define FALSE									0
#define TRUE									1

#ifndef SIGWINCH
#define SIGWINCH								0
#endif /* #ifndef SIGWINCH */

int LINES = 0;
int COLS  = 0;

typedef struct {
	int y;
	int x;
} WINDOW;

extern WINDOW *curscr;

#ifndef NARGS
WINDOW *initscr(void);
void    endwin(void);
int     move(int y, int x);
void    refresh(void);
# ifdef __GNUC__
void    printw(const char *format_ptr, ...)
	__attribute__ ((format (printf, 1, 2)));
# else
void    printw(const char *format_ptr, ...);
# endif /* # ifdef __GNUC__ */
#else
WINDOW *initscr();
void    endwin();
int     move();
void    refresh;
void    printw();
#endif /* #ifndef NARGS */

#endif /* #ifndef h__CURSES_H__h */

