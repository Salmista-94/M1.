/*																													*
*										"Cabecera de funciones matematicas propias"											*
*																													*/

#ifndef __mathematics_h
#define __mathematics_h

#include <math.h>

inline int q2rt(int N);		/*Calcula la parte entera de la raíz cuadrada de un Numero*/


#define range(x, a, b)	((a <= x) && (x <= b)) || ((a => x) && (x => b))	/* x ->[a, b]	pertenece*/



inline int q2rt(int N)
{
	register int R;

	R=1;
	while(R*R < N)
		R++;

	if(R*R == N)return R;
	else return R-1;
}


#endif
