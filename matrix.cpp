#include <stdlib.h>
//#include "Menu.h"
#include "wking-envt.h"


	// system("title DECIMAL -""car"" TIP");
void menu(void);
void matrix(void);
void TablaRef(void);

//extern unsigned short int  tip;

int main()
{
	int op;
	double D; 					//Como se vera acepta Nros reales...
//	long double X;
	
	matrix();					//Llamo a la pantalla de inicio

	menu();						//Llamo al menu
	myscan("%i",&op);
	uncaught('\n');

	while(op != 0){
		 switch(op){
			case 0:	break;					//Bye, Bye...

				//<<-Binario->>

			case 1:	myprint("ingrese un numero en binario: ");
				myscan("%b",&D);
				myprint("\n-> %t \t<< Oct >>",D);
				break;

			case 2:	myprint("ingrese un numero en binario: ");
				myscan("%b",&D);	tip=10;
				myprint("\n-> %d \t<< Dec >>",D);
				break;

			case 3:	myprint("ingrese un numero en binario: ");
				myscan("%b",&D);
				myprint("\n-> %x\t<< Hex >>",D);
				break;

				//<<-Octal->>

			case 4:	myprint("ingrese un numero en octal: ");
				myscan("%t",&D);
				myprint("\n-> %b\t<< Bin >>",D);
				break;

			case 5:	myprint("ingrese un numero en octal: ");
				myscan("%t",&D);
				myprint("\n-> %d\t<< Dec >>",D);
				break;

			case 6:	myprint("ingrese un numero en octal: ");
				myscan("%t",&D);
				myprint("\n-> %x\t<< Hex >>",D);
				break;

				//<<-Decimal->>

			case 7:	myprint("ingrese un numero en decimal: ");
				myscan("%d",&D);
				myprint("\n-> %b\t<< Bin >>",D);
				break;

			case 8:	myprint("ingrese un numero en decimal: ");
				myscan("%d",&D);
				myprint("\n-> %t\t<< Oct >>",D);
				break;

			case 9:	myprint("ingrese un numero en decimal: ");
				myscan("%d",&D);
				myprint("\n-> %x\t<< Hex >>",D);
				break;

				//<<-Hexadecimal->>

			case 10:	myprint("ingrese un numero en hexadecimal: ");
				myscan("%x",&D);
				myprint("\n-> %b\t<< Bin >>",D);
				break;

			case 11:	myprint("ingrese un numero en hexadecimal: ");
				myscan("%x",&D);
				myprint("\n-> %t\t<< Oct >>",D);
				break;

			case 12:	myprint("ingrese un numero en hexadecimal: ");
				myscan("%x",&D);
				myprint("\n-> %d\t<< Dec >>",D);
				break;


			case 13:	TablaRef();	menu();	break;					//Muestro la tabla gral. de referencias

			case 14:	menu();	break;		//Limpio la pantalla...



			default:	menu();	
						myprint("\n\n\n Este programa no tiene poderes de SUPERVACA para leer la mente,\n");
						myprint(" por favor ingresa una opci¢n valida!\n");
						break;
		 }
		 myprint("\n\n\nReingrese opcion para continuar: ");
		 myscan("%i",&op);
		 uncaught('\n');
		 uncaught('\n');
	 }
return 0;
}


/*
	while(tip != 0){
		myscan("%x%i",&D,&tip);
	//	myprint("\n%p\n",&D);"%x",
		
		tprint(D);
	//	myprint("\t'%c' '%c' 'tm' no se encuentra disponible en MS-DOS\n",184, 169);
	}
    
    return 0;
}*/






void menu(void)
{
	
#ifdef __WIN32__ 
system("cls");
#endif
#ifdef __LINUX__
system("clear");
#endif


//system("color e");//"Conversi¢n de tipo NO SIGNADA"

   myprint( "	    CONVERSIóN DE SISTEMAS  V2.14%c\n",169);
   myprint(" ********************************************\n");
   myprint(" 1)De Binario a Octal\n");
   myprint(" 2)De Binario a Decimal\n");
   myprint(" 3)De Binario a Hexadecimal\n\n");

   myprint(" 4)De Octal a Binario\n");
   myprint(" 5)De Octal a Decimal\n");
   myprint(" 6)De Octal a Hexadecimal\n\n");

   myprint(" 7)De Decimal a Binario\n");
   myprint(" 8)De Decimal a Octal\n");
   myprint(" 9)De Decimal a Hexadecimal\n\n");

   myprint(" 10)De Hexadecimal a Binario\n");
   myprint(" 11)De Hexadecimal a Octal\n");
   myprint(" 12)De Hexadecimal a Decimal\n\n");

   myprint(" 13)Tabla de referencia\n");
   myprint(" 14)Limpiar Pantalla\n\n");

   myprint(" 0)Salir\n");
   myprint(" 			Ingrese Opci¢n: ");

return;
}




void TablaRef(void)
{
	
#ifdef __WIN32__ 
system("cls");
#endif
#ifdef __LINUX__
system("clear");
#endif

//system("color f0");
	
myprint(" ********************************************************************\n");
myprint("* Sist. Decimal * Sist. Binario * Sist. HexaDecimal *  Sist. Octal  *\n");
myprint(" ********************************************************************\n\n");
myprint("*       0       *      0000     *          0        *       0       *\n\n");
myprint("*       1       *      0001     *          1        *       1       *\n\n");
myprint("*       2       *      0010     *          2        *       2       *\n\n");
myprint("*       3       *      0011     *          3        *       3       *\n\n");
myprint(" ********************************************************************\n\n");
myprint("*       4       *      0100     *          4        *       4       *\n\n");
myprint("*       5       *      0101     *          5        *       5       *\n\n");
myprint("*       6       *      0110     *          6        *       6       *\n\n");
myprint("*       7       *      0111     *          7        *       7       *\n\n");
myprint(" ********************************************************************\n\n");
myprint("*       8       *      1000     *          8        *      10       *\n\n");
myprint("*       9       *      1001     *          9        *      11       *\n\n");
myprint("*      10       *      1010     *          A        *      12       *\n\n");
myprint("*      11       *      1011     *          B        *      13       *\n\n");
myprint(" ********************************************************************\n\n");
myprint("*      12       *      1100     *          C        *      14       *\n\n");
myprint("*      13       *      1101     *          D        *      15       *\n\n");
myprint("*      14       *      1110     *          E        *      16       *\n\n");
myprint("*      15       *      1111     *          F        *      17       *\n\n");
myprint(" ********************************************************************\n\n");

myprint("Presione cualquier tecla para continuar\n");
catchit();

return;
}





void matrix(void)
{
int i;

//system("color a");
//system("title Matrix");

for(i=1; i<81; i++)	uncaught('*');

uncaught('\n');

for(i=1; i<81; i++)	uncaught('*');
	
uncaught('\n');


myprint("             **         **\n");
myprint("            ***        ***         ****************\n");
myprint("           *****      ****        *****************\n");
myprint("          **** **    ** **               ***                  ***       **\n");
myprint("         ****   **  **  **   ********    ***   **  ****        ***     **\n");
myprint("        ****     ****   **          **   ***   ** **  **        ***   **\n");
myprint("       ****       **    **          **   ***   ***      @@       *** **\n");
myprint("      ****              **     *******   ***   **                 ****\n");
myprint("     ****               **   *      **   ***   **       **         ****\n");
myprint("    ****                **  **      **   ***   **       **        ** ***\n");
myprint("   ****                 ** ***      **   ***   **       **       **   ***\n");
myprint("  ****                  **  **      **   ***   **       **      **     ***\n");
myprint(" ****                   **   *      **   ***   **       **   * **       ***\n");
myprint("****                    **     *******   ***   **        **** **         *** %c\n\n", 64);//184 windows

for(i=1; i<81; i++)	uncaught('*');

uncaught('\n');

for(i=1; i<81; i++)	uncaught('*');

myprint("\nPresione cualquier tecla para continuar\n");
catchit();
//system("title Bienvenidos a la Matrix");

#ifdef __WIN32__ 
system("cls");
#endif
#ifdef __LINUX__
system("clear");
#endif


return;
}
