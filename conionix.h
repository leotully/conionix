#ifndef _CONIONIX_H
#define _CONIONIX_H

#define COLOR_NORMAL			"\x1B[0m"
#define COLOR_RED				"\x1B[31m"
#define COLOR_GREEN				"\x1B[32m"
#define COLOR_YELLOW			"\x1B[33m"
#define COLOR_BLUE				"\x1B[34m"
#define COLOR_MAGENTA			"\x1B[35m"
#define COLOR_CYAN				"\x1B[36m"
#define COLOR_WHITE				"\x1B[37m"

#define COLOR_BRIGHT_RED		"\x1B[1;31m"
#define COLOR_BRIGHT_GREEN		"\x1B[1;32m"
#define COLOR_BRIGHT_YELLOW		"\x1B[1;33m"
#define COLOR_BRIGHT_BLUE		"\x1B[1;34m"
#define COLOR_BRIGHT_MAGENTA	"\x1B[1;35m"
#define COLOR_BRIGHT_CYAN		"\x1B[1;36m"
#define COLOR_BRIGHT_WHITE		"\x1B[1;37m"

/* typedef enum {false, true} bool; */

typedef enum
{
	/* Dark Colors */
	BLACK,			RED,			GREEN,			BROWN,
	BLUE,			MAGENTA,		CYAN,			LIGHTGRAY,
    
	/* Light Colors */
	DARKGRAY,		LIGHTRED,		LIGHTGREEN,		YELLOW,
	LIGHTBLUE,		LIGHTMAGENTA,	LIGHTCYAN,		WHITE
} CONIO_COLORS;

void textcolor(int color);
void textbackground(int color);
void textblink(void);
void normvideo(void);
void showcursor(int show);

/* x = column, y = row*/
void gotoxy(int x, int y);
void cursorup(int rows);
void cursordown(int rows);
void cursorright(int columns);
void cursorleft(int columns);
void clrscr(void);
void clearright(void);
void clearleft(void);
void delline(void);
void insline(void);
void clearline(void);
void save_screen(void);
void restore_screen(void);

              /* int *rows, int *cols */
void getsrcnsize(int *cols, int *rows);

/* Read 1 character without echo */
char getch(void);

/* Read 1 character with echo */
char getche(void); 

/* x = column, y = row*/
int wherexy(int *x, int *y);

/* column */
int wherex(void);

/* row */
int wherey(void);

#endif /* _CONIONIX_H */
