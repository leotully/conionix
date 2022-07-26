#include <conionix.h>

#include <stdio.h>
#include <termios.h>	/* for getch */
#include <unistd.h>		/* for wherexy */
#include <fcntl.h>		/* for wherexy */
#include <sys/ioctl.h>	/* for getscrnsize */

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

/* set stdout buffer to 0 to auto flush output */
void autoflush()
{
	(void)setvbuf(stdout, NULL, _IONBF, 0);
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

