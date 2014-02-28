/*																													*
*									"Cabecera de abstracion de entrada/salida"												*
*																													*/

#ifndef __absttraction_IO_h
#define __absttraction_IO_h


#include "defined.h"						//Cargo las definiciones basicas..
#include "char-defined.h"

extern unsigned long long Ne;
extern double fr;
extern unsigned short int bas;
extern int  c;

/*--------------*/
inline char getop(char c, unsigned int tipe);
char getch(void);
void ungetch(void);
inline long double Nskan(unsigned int tipe);
inline long int number(unsigned int tipe);
inline long double fraction(unsigned int tipe);
/*--------------*/

#undef BUFSIZ
#define BUFSIZ 128
char buf[BUFSIZ];
int bufp = Null;




inline long int number(unsigned int tipe)
{
	Ne= Null;

	while( bas=numerical(tipe, (c=getch())) );
		Ne= Ne*tipe + (c -bas);

	ungetch();
	return Ne;
}



inline long double fraction(unsigned int tipe)
{
	fr= Null;
	double mul=1;

	while( bas=numerical(tipe, (c=getch())) ){
		mul/= tipe;
		fr+=(c -bas)*mul;
	}

	ungetch();
	return fr;
}



inline char getop(char c, unsigned int tipe)
{
	if(c== Punto || c== Coma)	return Fraccion;	//Solo fraccionario
	else if( !(bas=numerical(tipe, c)) )	return c;	//Posible operador
	else return Numero;				//No hace falta explicar
}



inline long double Nskan(unsigned int tipe)
{
	float S;

	while( spacer(c= getch()) )
		;

	switch(c){
		case SNeg:	S= -1.0;	c= getch();	break;
		case SPos:	c= getch();
		default: 	S= 1.0;	break;
	}

	Ne= number(tipe);				//para algo sirven las variables globales..
	if((c= getch())== Punto || c== Coma)	return (Ne + fraction(tipe))*S;
	else	return Ne*S;

}




char getch(void)			/*obtiene un posiblemente ya regresado caracter*/
{
	return (bufp > Null) ? buf[--bufp] : catchit();
}



void ungetch(void)			/*regresa el caracter a la entrada*/
{
	if(bufp >= BUFSIZ) return;//myprint("Ungetch: ¡Demasiados caracteres!\n");
	else buf[bufp++] = c;
}

#endif
