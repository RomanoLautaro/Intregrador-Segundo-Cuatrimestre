#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
#include <string.h>
#include <windows.h>

text_info vActual = {0, 0, 79, 24, WHITE, WHITE, C80, 25, 80, 1, 1};

//DECLARACI�N DE FUNCIONES

void gotoxy(int x, int y);
void textcolor(int newcolor);
void textbackground(int newcolor);
void marco();

//FUNCIONES

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
	
	// gotoxy(36, 5); printf("%c", 219);
	// gotoxy(87, 5); printf("%c", 219);
	// gotoxy(36, 16); printf("%c", 219);
	// gotoxy(87, 16); printf("%c", 219);
}
