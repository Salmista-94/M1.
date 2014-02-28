/*																													*
*										"Cabecera de Algoritmos Variados"											*
*																													*/

#ifndef __Algorism_h
#define __Algorism_h

#include "mathematics.h"

bool es_abundante(int N);	/*Chequea la abundancia del Numero*/
bool es_primo(int N);		/*Chequea la primalidad del Numero*/
void divisores(int N);		/*Muestra por pantalla los divisores de un Numero*/



bool es_abundante(int N)
{
	register int M, div, S;
	short int inc;
	int j;

	if(N < 12) return false;
	else {
			if((N % 2)== 0){
				S= N/2 + 3;
				inc=1;
			}
			else {
				S=1;
				inc=2;
			}

			div=3;
			M=N/3;
			j=2;
			while(div < M){
				j++;
				if(M*div==N){
					S+= M + div;
					j++;
				}
				div+= inc;
				M=N/div;
			}

			if(div==M && M*div==N){
				S+= div;
				j++;
			}
			j++;
			if(S > N){myprint("	%i comparaciones,",j);	return true;}
			else return false;
	}
}





bool es_primo(int N)
{
	int  j/*, div*/;
	register int div, M;

	if(N < 2) return false;
	else {
			if(N==2 || N==3 || N==5 || N==7) return true;
			else {
					if((N % 2)!= 0 && (N % 3)!= 0 && (N % 5)!= 0 && (N % 7)!= 0){
							div=11;
							M=N/div;
							j=9;/**/
							while(div <= M){
									j++;/**/
									if(M*div == N){
										M=-1;
										j++;/**/
									}
									else {
										div+= 2;
										M=N/div;
									}
							}
					}

					else  return false;/* { printf("	10 comparaciones max,");	return true;}*/

					if(M==-1) return false;
					else {myprint("	%i comparaciones,",j);	return true;}
							
			}

	}
}



void divisores(int N)
{
	int I, div, M;

	if(N == 0)	return;
	
	myprint("\t    Divisible por:\t\t1\n");
	if((N % 2)==0){	myprint("\t    Divisible por:\t\t2\n");	I=1; M=N/2;}
	else {I=2; M=N/3;}

	div=3;
	while(div <= M){
		if((N % div)==0) myprint("\t    Divisible por:\t\t%i\n",div);
		div+=I;
	}
	
	myprint("\t    Divisible por:\t\t%i\n\n",N);

	return;
}


#endif
