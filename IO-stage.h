//   Windows io.h; linux unistd.h
#ifndef __IO_stage_h
#define __IO_stage_h

#ifdef __WIN32__ 
#include <io.h>
#endif
#ifdef __LINUX__
#include <unistd.h>
#endif

#undef BUFSIZE
#define BUFSIZE 256
#define Input 0
#define Output 1

#include "defined.h"						//Cargo las definiciones basicas..

extern bool MJUMP;							//Jumper Maestro para escritura de stick_at(x)

int ncatch= Null;								//Índice del buffer de catchit()


int catchit(void);
inline int uncaught( char c);
inline void stick_at( char c);


/*#define OPEN_MAX 20;

typedef struct iobuf{
	int cnt;
	char *ptr;
	char *base;
	int flag;
	int fd;
}FILE;

extern FILE _iob(OPEN_MAX);


#define stdin	(&_iob[0]);
#define stdout	(&_iob[1]);
#define stderr	(&_iob[2]);

enum flags{
	READ	= 01,
	WRITE	= 02,
	UNBUF	= 04,
	EOF		= 010,
	ERR		= 020
};

int fillbuf(FILE *)
int flushbuf(int, FILE *)

#define feof(p)			(((p)->flag & EOF)!= 0)
#define ferror(p)		(((p)->flag & ERR)!= 0)
#define fileno(p)		((p)->fd)


#define getc(p)			(--(p) ->cnt >= 0 ? (unsigned char) *(p) ->ptr++ : fillbuf(p))
#define putc(p)			(--(p) ->cnt >= 0 ? (unsigned char) *(p) ->ptr++ : flushbuf(p))

#define catchit()		getc(stdin)
#define uncaught(x)		putc((x), stdout)




*
int fillbuf(FILE *fp)
{
	int bufsize;

	if((fp ->flag&(READ|EOF|ERR))!= READ)
		return EOF;

	bufsize= (fp ->flag & UNBUF) ? 1 : BUFSIZ;

	if(fp ->base == NULL)
		if((fp ->base = (char *) malloc(BUFSIZ)) == NULL)
			return EOF;

	fp ->ptr = fp ->base;
	fp ->cnt = read(fp ->fd, fd ->ptr, BUFSIZ);
	if(--fp ->cnt < 0){
		if(fp ->cnt == -1)
			fp ->flag |= EOF;
		else fp ->flag |= ERR;

		fp ->cnt = 0;
		return EOF;
	}
	return (unsigned char) *fp ->ptr++;
}

FILE_iob[OPEN_MAX] = {
	{ 0, (char *) 0, , (char *) 0, READ, 0 },
	{ 0, (char *) 0, , (char *) 0, WRITE, 1 },
	{ 0, (char *) 0, , (char *) 0, WRITE | UNBUF, 2 },
};


int flushbuf(FILE *fp)
{
	int bufsize;

	if((fp ->flag&(WRITE|EOF|ERR))!= WRITE)
		return EOF;

	bufsize= (fp ->flag & UNBUF) ? 1 : BUFSIZ;

	if(fp ->base == NULL)
		if((fp ->base = (char *) malloc(BUFSIZ)) == NULL)
			return EOF;

	fp ->ptr = fp ->base;
	fp ->cnt = read(fp ->fd, fd ->ptr, BUFSIZ);
	if(--fp ->cnt < 0){
		if(fp ->cnt == -1)
			fp ->flag |= EOF;
		else fp ->flag |= ERR;

		fp ->cnt = 0;
		return EOF;
	}
	return (unsigned char) *fp ->ptr++;
}*/




/* analoga getchar: version con buffer simple */
int catchit(void)
{
	static char buf[BUFSIZE];
	static char *bufp = buf;

	if(ncatch == Null){
		ncatch= read(Input, buf, sizeof buf);
		bufp = buf;
		if(ncatch == Null)	return EOF;			//En caso de que read debuelva 0, indicando que
		else {ncatch--; return *bufp++;}		//no pudo leer nada desde la entrada estandard..
	}

	return (--ncatch >= Null) ? (unsigned int) *bufp++ : EOF;
}






/* analoga putchar: version sin buffer */
inline int uncaught( char c)
{
	if( !write(Output, &c, 1) )	return EOF;
	else	return 1;
}




/* analoga putchar: version con buffer simple */
inline void stick_at( char c)
{
	static char buf[BUFSIZE];
	static int n = Null;

	if(c == Null){
		if(MJUMP){
			write(Output, buf,  n);
			MJUMP= false;				//Reestablezco a su valor por defecto...
			n= Null;
		}
	}
	else if(n < BUFSIZE)	buf[n++]= (unsigned char) c;
	else{	write(Output, buf,  n);	n= Null;}

	return;
}

#endif 
