/*																													*
*										"Cabecera de definiciones varias"											*
*																													*/

#ifndef __std_defined_h
#define __std_defined_h


#undef NULL
#undef Null

#define NULL 0						//Nulo
#define Null NULL

#define PNULL ((void *)0)		//Puntero a Null
#define PNull PNULL		//Puntero a Null



#define Cero 0
#define FCero 0.0

#define UNIT 1

#define NEXT(x) ++x
#define PREV(x) --x

#define OP(X) -X



#ifndef EOF
#define EOF -1					//Fin de archivo
#endif

#define Neg EOF

#endif
