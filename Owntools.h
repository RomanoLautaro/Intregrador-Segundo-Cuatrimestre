#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
#include <string.h>
#include <windows.h>
#include <iostream>

#define UP 80
#define DOWN 72
#define ENTER 13

text_info vActual = {0, 0, 79, 24, WHITE, WHITE, C80, 25, 80, 1, 1};

//DECLARACI?N DE FUNCIONES

void ocultarCursor();
void gotoxy(int x, int y);
void textcolor(int newcolor);
void textbackground(int newcolor);
void marco();
void titulo_Generico(const char *titulo[], int i, int x1, int y1, int x2, int y2);
void marcoGenerico(int x1, int x2, int y1, int y2);
void password(int x, int y, char contrasenia[]);
void barraPorcentaje(float Porcen, int x, int y);

//FUNCIONES

void ocultarCursor(){
	
	HANDLE hCon;
	hCon= GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize= 2;
	cci.bVisible= FALSE; 
	
	SetConsoleCursorInfo(hCon, &cci);
	
}

void gotoxy(int x, int y){
 HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X=x;
	dwPos.Y=y;
	SetConsoleCursorPosition(hcon, dwPos);
}

void textcolor(int newcolor){
   CONSOLE_SCREEN_BUFFER_INFO csbi;
   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
      (csbi.wAttributes & 0xf0) | newcolor);
   vActual.attribute = (csbi.wAttributes & 0xf0) | newcolor;
}

void textbackground(int newcolor){
   CONSOLE_SCREEN_BUFFER_INFO csbi;
   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
      (csbi.wAttributes & 0x0f) | (newcolor << 4));
   vActual.attribute = (csbi.wAttributes & 0x0f) | (newcolor << 4);
}

void marco(){
	for(int i=36; i<88; i++){
		gotoxy(i, 5); printf("%c", 219);
		gotoxy(i, 18); printf("%c", 219);
	}
	
	for(int i=5; i<19; i++){
		gotoxy(36, i); printf("%c", 219);
		gotoxy(35, i); printf("%c", 124);
		gotoxy(87, i); printf("%c", 219);
		gotoxy(88, i); printf("%c", 124);
	}
}

int menu(const char *titulo, const char *opciones[], int N){
	
	int opcSeleccionada=1, tecla;
	bool band=true;
	textcolor(LIGHTRED);
	marco();
	textcolor(BLACK);
	textbackground(WHITE);
	gotoxy(50, 5); printf("%s", titulo);
	textcolor(WHITE);
	gotoxy(49, 5); printf("%c", 219);
	gotoxy(50+strlen(titulo), 5); printf("%c", 219);
	//gotoxy(56, 5); printf("%cBIENVENIDO%c", 173, 33);
	textbackground(BLACK);
	// textcolor(WHITE);
	//gotoxy(50, 7); printf("%s", titulo);
	textcolor(WHITE);
	textbackground(LIGHTRED);
	gotoxy(19-8, 21+7); printf(" %cNOTA: ", 175);
	textcolor(BLACK);
	textbackground(WHITE);
	gotoxy(26-7, 21+7); printf(" Utilice las flechas direccionales para moverse en las opciones y ENTER para seleccionar. ");
	textbackground(BLACK);
	textcolor(WHITE);
	for(int i=0; i<N; i++){ 
		
		gotoxy(44, 10+i); printf(" %c %s", 175,opciones[i]);
	}
	do{
		gotoxy(40, 9+opcSeleccionada); textcolor(YELLOW); printf("==>"); textcolor(WHITE);
			
			do{
				ocultarCursor();
				gotoxy(119, 34);printf(" ");
				tecla= getch();  
			}while(tecla!=UP && tecla!=DOWN && tecla!=ENTER);
			switch(tecla){
				case UP:
						gotoxy(40, 9+opcSeleccionada); textcolor(CYAN); printf("   "); textcolor(WHITE);
						opcSeleccionada++;
						if(opcSeleccionada>N){
							opcSeleccionada=1;
						}
						Beep(1300, 50);
					break;
				case DOWN: 
						gotoxy(40, 9+opcSeleccionada); textcolor(CYAN); printf("   "); textcolor(WHITE);
						opcSeleccionada--;
						if(opcSeleccionada<1){
							opcSeleccionada=N;
						}
						Beep(1300, 50);
					break;
				case ENTER:
						band=false;
						Beep(800, 50); 
					break;
			}
	}while(band);
	return opcSeleccionada;
}

void titulo_Generico(const char *titulo[], int i, int x1, int y1, int x2, int y2){
	
	gotoxy(x1, y1); textcolor(WHITE); printf("%c", 177);
	textcolor(LIGHTRED);
		for(int z=20; z<102; z++){
			gotoxy(z, 4); printf("%c", 219);
		}
	gotoxy(x2, y2); textcolor(WHITE); printf("%c", 177);
	textbackground(WHITE); textcolor(BLACK); gotoxy(51, 4); printf(" %s ", titulo[i]); textcolor(WHITE); textbackground(BLACK);
}

void marcoGenerico(int x1, int x2, int y1, int y2){
	for(int i=x1; i<x2+1; i++){
		gotoxy(i, y1); printf("%c", 219);
		gotoxy(i, y2); printf("%c", 219);
	}
	
	for(int i=y1; i<y2+1; i++){
		gotoxy(x1, i); printf("%c", 219);
		gotoxy(x2, i); printf("%c", 219);
		gotoxy(x1-1, i); printf("%c", 124);
		gotoxy(x2+1, i); printf("%c", 124);
	}
}

void barraPorcentaje(float Porcen, int x, int y){
	int porcent;
	
	porcent=int(Porcen);
	textcolor(WHITE);
	gotoxy(x,y); printf("%c", 178);
	gotoxy(x+102,y); printf("%c", 178);
	
	
	textcolor(LIGHTRED);
	textbackground(LIGHTRED);
	for(int i=0; i<porcent+1; i++){
		gotoxy(x+i+1,y); printf("%c", 219);
	}
	textcolor(WHITE);

	gotoxy(x+(porcent/2),y); printf("%.2f%%", Porcen);
	textbackground(BLACK);

	printf("\n");
}

// // void password(int x, int y, char contrasenia[]){
// // 	int i=0;
// }
// // void password(int x, int y, char contrasenia[]){
// // 	int i=0;
// }
// // void password(int x, int y, char contrasenia[]){
// // 	int i=0;
// }
// // void password(int x, int y, char contrasenia[]){
// // 	int i=0;
// }
// // void password(int x, int y, char contrasenia[]){
// // 	int i=0;
// }
// // void password(int x, int y, char contrasenia[]){
// // 	int i=0;
// }
// // void password(int x, int y, char contrasenia[]){
// // 	int i=0;
// }
// // void password(int x, int y, char contrasenia[]){
// // 	int i=0;
// }
// // void password(int x, int y, char contrasenia[]){
// // 	int i=0;
// }
// // void password(int x, int y, char contrasenia[]){
// // 	int i=0;
// }
// // void password(int x, int y, char contrasenia[]){
// // 	int i=0;
// }
// // void password(int x, int y, char contrasenia[]){
// // 	int i=0;
// }
// // void password(int x, int y, char contrasenia[]){
// // 	int i=0;
// }
// // void password(int x, int y, char contrasenia[]){
// // 	int i=0;
// }
// // void password(int x, int y, char contrasenia[]){
// // 	int i=0;
// }
// // void password(int x, int y, char contrasenia[]){
// // 	int i=0;
// }
// // void password(int x, int y, char contrasenia[]){
// // 	int i=0;
// }
// // void password(int x, int y, char contrasenia[]){
// // 	int i=0;
// }
// // void password(int x, int y, char contrasenia[]){
// // 	int i=0;
// }
// // void password(int x, int y, char contrasenia[]){
// // 	int i=0;
// }
// // void password(int x, int y, char contrasenia[]){
// // 	int i=0;
// }
// // void password(int x, int y, char contrasenia[]){
// // 	int i=0;
// }
// // void password(int x, int y, char contrasenia[]){
// // 	int i=0;
// }
// // void password(int x, int y, char contrasenia[]){
// // 	int i=0;
// }
// // void password(int x, int y, char contrasenia[]){
// // 	int i=0;
// // 	char pass[32], caracter;
	
// // 	gotoxy(x,y);
// // 	caracter=getch();
// // 	while(caracter!=ENTER){
// // 		if (caracter==8)
// // 		{
// // 			if (i>0)
// // 			{
// // 				i--;
// // 				printf("\b \b");
				
// // 			}
			
// // 		}else if(i!=32)
// // 		{
// // 			printf("*");
// // 			pass[i]=caracter;
// // 			i++;
// // 		}
// // 		caracter=getch();	
// // 	}
// // 	pass[i]='\0';
// // 	strcpy(contrasenia,pass);
// // }
