/*																													*
*										"Cabecera de manejo de caracteres"											*
*																													*/

#ifndef __str_catch_h
#define __str_catch_h

#include "defined.h"						//Cargo las definiciones basicas..
#include "char-defined.h"

extern unsigned short int bas;				//ajusto segun el tipo de base, ej; 10, '0';	16 '0' ó 'w' ó '7'


inline bool alpha(char c)
{
	if((c > '`' && c < '{') || (c > '@' && c < '['))
		return true;
	else return false;
}

inline bool decimal(char c)
{
	if(c > '/' && c < ':')
		return true;
	else return false;
}

inline bool alphanumeric(char c)
{
	if((c > '/' && c < ':') || (c > '`' && c < '{') || (c > '@' && c < '['))
		return true;
	else return false;
}

inline int numerical(int tip, char c)
{
	switch(tip){
		case 2:	if(c > '/' && c < '2')	return (bas= BASE);
		else return false;
		break;

		case 8:	if(c > '/' && c < '8')	return (bas= BASE);
		else return false;
		break;

		case 10:	if(c > '/' && c < ':')	return (bas= BASE);
		else return false;
		break;

		case 16:	if(c > '/' && c < ':')	return (bas= BASE);
					else	if(c > '`' && c < 'g')	return (bas= 'W');
					else	if(c > '@' && c < 'G')	return (bas= '7');
					else return false;
		break;

		default:	return false;
	}
}

inline bool spacer(char c)
{
	if((c == Espacio) || (c == Tab) || (c == Newline))
		return true;
	else return false;
}

#endif
