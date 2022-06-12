#ifndef _CONIONIX_H
#define _CONIONIX_H

#include <stdio.h>
#include <termios.h>	/* for getch */
#include <unistd.h>		/* for wherexy */
#include <fcntl.h>		/* for wherexy */
#include <sys/ioctl.h>	/* for getscrnsize */

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

void textcolor(int color)
{
	if (color < 8)
		printf("\x1B[3%dm", color);
	else
		printf("\x1B[1;3%dm", color-8);
}

void textbackground(int color)
{
	if (color == WHITE) color = LIGHTGRAY;
	printf("\x1B[4%dm", color);	
}

void textblink(void)
{
	/* printf("\x1B[?12h");  this didn't work in windows or DOS, check linux */
	printf("\x1B[5m");
}

void normvideo(void)
{
	printf("\x1B[0m");
}

void showcursor(int show)
{
	if (show)
		printf("\x1B[?25h"); /* show cursor */
	else
		printf("\x1B[?25l"); /* hide cursor */
}

/* x = column, y = row*/
void gotoxy(int x, int y)
{
	printf("\x1B[%d;%df", y, x);
}

void cursorup(int rows)
{
	printf("\x1B[%dA", rows);
}

void cursordown(int rows)
{
	printf("\x1B[%dB", rows);
}

void cursorright(int columns)
{
	printf("\x1B[%dC", columns);
}

void cursorleft(int columns)
{
	printf("\x1b[%dD", columns);
}

void clrscr(void)
{
	printf("\x1B[2J");
}

void clearright(void)
{
	printf("\x1B[0K");
}

void clearleft(void)
{
	printf("\x1B[1K");
}

void delline(void)
{
	printf("\x1B[M");
}

void insline(void)
{
	printf("\x1B[L");
}

void clearline(void)
{
	printf("\x1B[2K");
}

void save_screen(void)
{
	printf("\x1B[?47h");
}

void restore_screen(void)
{
	printf("\x1B[?47l");
}

              /* change */
              /* int *rows, int *cols */
void getsrcnsize(int *cols, int *rows)
{
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	
	*rows = w.ws_row;
	*cols = w.ws_col;
}


static struct termios old, current;

/* Initialize new terminal i/o settings */
void initTermios(int echo) 
{
	tcgetattr(0, &old);					/* grab old terminal i/o settings */
	current = old;						/* make new settings same as old settings */
	current.c_lflag &= ~ICANON; 		/* disable buffered i/o */
	
	if (echo)
	{
		current.c_lflag |= ECHO; 		/* set echo mode */
	}
	else
	{
	    current.c_lflag &= ~ECHO; 		/* set no echo mode */
	}

	tcsetattr(0, TCSANOW, &current); 	/* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
	tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
{
	char ch;
	
	initTermios(echo);
	ch = getchar();
	resetTermios();
	
	return ch;
}

/* Read 1 character without echo */
char getch(void) 
{
	return getch_(0);
}

/* Read 1 character with echo */
char getche(void) 
{
	return getch_(1);
}

static int x;
static int y;
/* x = column, y = row*/
int wherexy(int *x, int *y)
{
	static int x_pos, y_pos;
	static int t = STDOUT_FILENO;
	static struct termios sav, opt;
	
	tcgetattr(t, &sav);
	opt = sav;
	
	opt.c_lflag &= ~(ECHO | ICANON);

	// but better just cfmakeraw(&opt);
	tcsetattr(t, TCSANOW, &opt);
	
	printf("\033[6n");
	fflush(stdout);

	scanf("\033[%d;%dR", &y_pos, &x_pos);
	tcsetattr(t, TCSANOW, &sav);

	*x = x_pos;
	*y = y_pos;

	return 0;
}

/* column */
int wherex(void)
{
	wherexy(&x, &y);

	return x;
}

/* row */
int wherey(void)
{
	wherexy(&x, &y);

	return y;
}

#endif /* _CONIONIX_H */
