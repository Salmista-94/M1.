/*																													*
*										"Cabecera de Ambiente local"												*
*																													*/
#ifndef __wking_envt_h
#define __wking_envt_h

#include "system.h"
#include "str-catch.h"//<F:\Editable\FACU\Infor\C--\Propias\>
#include "IO-stage.h"
#include "absttraction-IO.h"
#include "char-defined.h"
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>


unsigned short int  tip, bas, tipe, I, k, lim = Null;	//ajusto segun el tipo de base, ej; 10, '0';	16 '0' ó 'w' ó '7'; 'c' es generico!..
unsigned long long Ne = Null;
 double fr = Null;						//Cuando esta como 'unsigned', me ignora los reales...

bool MJUMP= false;					//Jumper Maestro para escritura 'stick_at()'

extern int ncatch;					//Definición en "IO - stage.h", índice del buffer


char pC = Espacio ;						//Por si llamaron a la funcion tprint() en vez de myprint()
  int  c;					
 

/* Var auxiliar de mytprint() y mytrprint() para achivos distintos uso extern y lo demas ==*/

/*Hay un error al pasar el parametro, esperandolo como long double, pero no com double en tprint, en compilador devc++*/
/*--------------*/
void tprint(long double Nro);               /* Es la encargada de enlazar a las verdaderas funciones de escritura*/
void mytprint(void);						/* Se encarga de la escritura de Nros enteros*/
void mytrprint(void);						/* Se encarga de la escritura de la parte fraccionaria de los Nros*/
void tipos(void);							/* Se encarga de verificar si el formato es entero o real*/
void step(void);							/* Encargada de prefijar un tope para la escritura de mytrprint(),*/

void myprint(char *fmt,...);
/*--------------*/



/*--------------*/
inline long double Nscan(void);
void myscan(char *fmt, ...);
/*--------------*/



// Funciones de escritura  <------------------------------------------------------------------------------

void tprint(long double Nro)
{
     c = 1;
	  
     tipos();
	 step();
	 
	 if(Nro < 0.0){	 		  		  
		  Nro= -Nro;
          if(tip == 10)	stick_at(SNeg);
     }      
     
     Ne= (unsigned long long) Nro;

	 fr= Nro - Ne;				//Me desago de Nro, llamo al destructor..
	
     mytprint();

	 if(fr > Null && k == 1){
		stick_at(Punto);
		
		/* Round correctly so that print(1.999, 2) prints as "2.00"
		int i, j=9;
		double rounding = 0.5;
		for (i=0; i<j; ++i)
			rounding /= 10.0;
  
		fr += rounding;
*/

		c= 1;
		if(lim > 0)   mytrprint();
		else stick_at(BASE);
	}
	 stick_at(Null);

	 return;
}


void mytprint(void)
{
     unsigned short int Ns;

     Ns = Ne % tip;
    if(Ne >= tip){
          Ne/= tip;
          c++;
          mytprint();
    }
    else if(tip == 2 || tip == 16){
				if( I= ((unsigned short int)(4 - c))%4 )
					do{
                      stick_at(BASE);
				  }while(--I > Null);
				  I=c;
	}
    
	if(tip ==16 || tip == 2) if(!(c%4) && (c < I)) stick_at(Espacio);
    
    if(Ns < 10)   stick_at(Ns + BASE);
	else stick_at(Ns + '7');
    
    c--;
}




void mytrprint(void)
{
     fr*=tip;
     I= (unsigned short int) fr;

     if(I < 10) stick_at(I + BASE);	/*Escribe el decimal correspondiente */
     else stick_at(I + '7');
     
     if((fr-=I) > Null){			/*Si aún quedan decimales por procesar */
          if(c < lim){		/*Si es que no ha llegado al tope de decimales... */

			  if(tip == 16 || tip == 2) if(!(c%4)) stick_at(Espacio);	/*Añade un espacio c/4 lugares para binario y hexadecimal */
              
              c++;			/*Incremeta 'c' para el control de decimales */
			  mytrprint();	/*Hace un llamado recursivo para los valores restantes */
          }
          else stick_at('~');/*En el caso en que halla llegado al tope y aún queden decimales, indico que es una aprox. */
     }
}



void tipos(void)
{
	 k = Null;
	 switch (pC){
		 case'b':k = 1;	tip = 2;	break;	//	<<--Binario-->>

		 case't':k = 1;
		 case'o':tip = 8;		break;	//	<<--Octal-->>

		 case Espacio:k = 1;	MJUMP=true;	break;		/*Por si llamaron a la funcion tprint() en vez de myprint(),
												ver valor por defecto de pC*/
		 case'L':
		 case'd':
		 case'f':k = 1;
		 case'u':
		 case'i':
		 case'l':tip = 10;		break;	//	<<--Decimal-->>

		 case'x':k = 1;
		 case'h':tip = 16;		break;	//	<<--Hexadecimal-->>
	 }
	 return;
}




void step(void)
{
	if(lim == Null)
            switch(tip){
                        case 2: lim = 25; break;
                             
                        case 8: lim = 5; break;
                             
                        case 10: lim = 32; break;
                             
                        case 16: lim = 7; break;
                             
                        default: myprint("\n~Error: '%i' Tipo invalido.~\n",tip);
								exit(tip);
								break;
            }
	else if(tip == 2) lim*= 4 + 1;

	return;
}












void myprint(char *fmt,...)
{
    va_list ap;                     /* Apunta a cada argumento sin nombre*/
   //
   union {
	    long long Nl;
		unsigned int Nu;
		long double Lr;
		double Nr;
		char *sval;
		void *pv;
	}state_value;
	
	unsigned short int i, j, cif, iform;
	char *p;

    j =0;
    
    va_start(ap, fmt);              /* Hace que ap apunte al primer arg sin nombre*/
    for(p = fmt; *p; p++){
          if(*p != '%'){			/*Escribo los caracteres que van llegando hasta encontrar formato */
                stick_at(*p);
                continue;
          }
          i=0;							/*<------				comentar ésta linea para ver falla*/

		  if(*++p == '%'){stick_at(*p);	continue;}
		  else	while( !alpha(*p) ){			//Me adelanto para encontrar primero
					*p++;					// el formato pertinente
                     i++; 
		  }
		  /*printf("\n%p\hello\n",p);		<------				...y descomentá tambien ésta*/
 
          pC = *p;					/*Guardo la marca de formato pertinente */
		  
          for(; i>Null; i--)
              p--;		/*Ya conosco el tipo de formato, ahora vuelvo hacia atras ... */

		  switch(pC){				/*Segun sea el formato ... */
					 case 'u': 
					 case 'o':
					 case 'h': Ne = va_arg(ap, unsigned long);	tprint(Ne);	break;
					 
					 case 'l':
                     case 'i':  /*Formateado como Entero */
							   state_value.Nl = va_arg(ap, int);
                               
                               if(*p == SNeg){	/*Tiene ajuste a Izquierda */
                                     *p++;		/*paso al siguiente caracter*/
                                     j = 1;		/*seteo ajuste Izq. */
                               }
                               if( decimal(*p) ){			/*<-----Tiene ajuste de escritura(Ej: '%-4i') */
                                     if(*p == BASE)     state_value.Nl = Null;		/*Suprimo la parte entera */
                                     else {
                                          if(state_value.Nl < Null) cif = (unsigned short int) log10((float) -state_value.Nl);	/*Calculo la cantidad de cifras ... */
                                          else if(state_value.Nl > Null) cif = (unsigned short int) log10((float) state_value.Nl) + 1; /* ... */
                                          
                                          if(j == 1) tprint(Ne);			/*Si hay ajuste a Izq. escribo 1° el Nro*/
                                          if((iform = *p++ - BASE - cif) > Null){
                                               for(i = Null; i< iform; i++)
                                                     stick_at(Espacio);			/*Completo con espacios hasta rellenar formato */
                                          }
                                          if(j != 1) tprint(state_value.Nl);		/*...Y si no lo hay lo escribo despues */
                                          										
                                     }
                               }else tprint(state_value.Nl);					/*<-----Nunca tubo un ajuste de escritura (Ej: '%x') */
							   break;
                               
					 
					 case 'L': state_value.Lr = va_arg(ap, long double); goto REAL;
					 case 'b':
					 case 'd':
					 case 'f':
					 case 't':
					 case 'x':	/*Formateado como Real */
							   state_value.Nr = va_arg(ap, double);
							   state_value.Lr= state_value.Nr;
                                
                               REAL:
                                   
                               //if(state_value.Lr < 0)exit(21);
                                    
                               if(*p == SNeg){	/*Tiene ajuste a Izquierda ---para reales se ignora---*/
                                     *p++;		/*paso al siguiente caracter*/
                                     //j = 1;		/*seteo ajuste Izq. */
                               }
                               if( decimal(*p) ){			/*<-----Tiene ajuste de escritura(Ej: '%-4i') */
                                     if(*p == BASE)     state_value.Nr -= (int) state_value.Nr;		/*Suprimo la parte entera */
                                     else {
                                          if(state_value.Lr < Null) cif = (unsigned short int) log10(-state_value.Lr);	/*Calculo la cantidad de cifras ... */
                                          else if(state_value.Lr > Null) cif = (unsigned short int) log10(state_value.Lr) + 1; /* ... */
                                          
                                      //    if(j == 1) tprint(Ne);			/*Si hay ajuste a Izq. escribo 1° el Nro*/
                                          if((iform = *p - BASE - cif) > Null){
                                               for(i = Null; i< iform; i++)
                                                     stick_at(Espacio);			/*Completo con espacios hasta rellenar formato */
                                          }
                                          //if(j != 1) tprint(Nr);    		/*...Y si no lo hay lo escribo despues */
                                          
                                          if(*++p == Punto)                            /* tiene formato fraccionario; aun no optimice este pedacito (para no matarme)*/
                                               if( decimal(*++p) )              /* obtengo el otro formato*/
                                                    lim = *p++ - BASE;
										  
										  tprint(state_value.Lr);
										
                                     }
                               }else tprint(state_value.Lr);					/*<-----Nunca tubo un ajuste de escritura (Ej: '%x') */
                               break;
                               

                     case 'c':  /*Formateado como caracter */  
								c = va_arg(ap, int);//aqui

								if( decimal(*p) )
                                         iform = *p - '1';
								else iform= 0;

                                for(j = 0; iform > j ; j++)
                                      stick_at(Espacio);

                                stick_at((char)c);
                                break;
                                                                    
                     case 's':  /*Formateado como cadena */
                                for(state_value.sval = va_arg(ap, char*); *state_value.sval; state_value.sval++)
                                         stick_at( *state_value.sval );
                                         
                                break;
                                                                    
                     case 'p':  /*Es un puntero */
                                state_value.pv = va_arg(ap, void*);

								myprint("'0x%h'", state_value.pv);//-llabs()
                                break;
                                
                     default:   /*Mal formateado! */
								 myprint("~Error: '%c' no es un formato valido.~",pC);
								 exit(12);
                                 break;
          }
    }
    va_end(ap);

	MJUMP=true;
	stick_at(Null);

	return;
}






// Funciones de lectura  <------------------------------------------------------------------------------




void myscan(char *fmt, ...)
{
	va_list ap;
	int *NP;
	long int *Nl;
	double *NR;
//	long double *NX;
	char *p, *pc;
//	void *arg;

//	j=1;
	ncatch= 0;				//Reestablesco el buffer para catchit()

	va_start(ap,fmt);
	for(p = fmt; *p; p++){
		while( !alphanumeric(*p) ){
          if(*p++ != '%')
			  continue;
		  //else j=0;
		}

		switch(*p){
			case 'b':	/*En Formato binario -> 'real' <-*/
				tipe= 2;
				NR = va_arg(ap, double *);
				*NR = Nscan(); // Se supone que le envio tip=10...
				break;

			case 'i':	/*En Formato decimal -> 'entero' <-*/
				tipe= 10;
				NP = va_arg(ap, int *);
				//while( spacer(c= getch()) )
				//	;
				
				*NP = (int) Nscan(); // Se supone que le envio tip=10...
				//myprint("\nI %i-",*NP);
				break;

			case 'l':	/*En Formato decimal -> 'entero largo' <-*/
				tipe= 10;
				Nl = va_arg(ap, long int *);
				//while( spacer(c= getch()) )
				//	;

				*Nl = (long int) Nscan();//number(); // Se supone que le envio tip=10...
				break;


			case 't':	/*En Formato octal -> 'real' <- */
				tipe= 8;
				NR = va_arg(ap, double *);
				*NR = Nscan(); // Se supone que le envio tip=10...
				break;

			case 'd':
			case 'f':	/*En Formato decimal -> 'real' <- */
				tipe= 10;
				NR = va_arg(ap, double *);
				*NR = Nscan(); // Se supone que le envio tip=10...
				break;

			case 'x':	/*En Formato hexadecimal -> 'real' <- */
				tipe= 16;
				NR = va_arg(ap, double *);
				*NR = Nscan(); // Se supone que le envio tip=10...
				//printf("%f",*NX); exit(99);if(== 4294967296.0 )
				break;

			case 'c':
				pc = va_arg(ap, char *);
				*pc = (char) catchit();
				break;

			case 's':
				pc = va_arg(ap, char *);
				while( (*pc = (char) catchit()) != '\n' )
					*pc++;
				*pc='\0';
				break;

			default: exit(11);	break;//reporto el fallo enviandole una direccion de memoria
		}
	}
//	ncatch= 0;				//Reestablesco el buffer para catchit()

	return;	
	
}

/*
for(P = fmt; *p; p++){
	if(*p == '%')	continue;
	else{if(*p > '/' && *p < ':')	f= *p -'0'; continue;}

	while((*p < 'a' || *p > 'z') && (*p < 'A' || *p > 'Z'))
		i++;

	switch(){
		'i':
		...

	}


*/



inline long double Nscan(void)// se supone que recibe como argumento a 'tip' ...
{
	int c, S;
	//unsigned long int N= Null;
	float mul=1.0;
	Ne= Null;
	fr= Null;

	while( spacer(c= catchit()) )
		;

	switch(c){
		case SNeg:	S= Neg;	c= catchit();	break;
		case SPos:	c= catchit();
		default: 	S= 1;	break;
	}
	
	while(bas=numerical(tipe, c)){
			Ne=Ne*tipe + (c - bas);
			c= catchit();
	}
	
	if(c== Punto || c== Coma)
		while( bas=numerical(tipe, (c= catchit())) ){
			mul/=tipe;
			fr+=(c -  bas)*mul;
		}
	
	return (Ne+fr)*S;
}



// ésta seccion seria para lectura de ficheros <------------------------------------------------------------------------------




/* for(;iform > 0; iform--){
              c = catchit();
              if(c > '/' && c < ':')  N*=10 + (c -'0');
              else if(c == EOF) break;
   }
   if((c = catchit()) == '.' || c == ',')
         for(;pform > 0; pform--){
                    c = catchit();
                    if(c > '/' && c < ':'){
                         mul*= 0.1;
                         fr+=(c -'0')* mul;
                    }
                    else if(c == EOF) break;
         }
   N*= S;
     
     
     
     
     
    
     
				//if(Ne > 9312.0 )exit(21);
				
		FILE *p;
		p=fopen("log.txt","a");
				fprintf(p,"%i\n",Ne);
				fclose(p);
*/


#endif
