#include "Owntools.h"

#define UP 80
#define DOWN 72
#define ENTER 13

void menu_principal();
int menu(const char *titulo, const char *opciones[], int N);


int main(){
    menu_principal();
    return 0;
}

void menu_principal(){
	
	bool band=true;
	int Op;
	const char *titulo= "Modulo de Administracion";
	const char *opciones[]={"Registrar Veterinario", "Registrar Usuario Asistente", "Atenciones por Veterinarios", "Rankingde Veterinarios por Atenciones", "Salir"};
	int n=5;
	
	do{
		system("cls");
		Op=menu(titulo, opciones, n);
		switch(Op){
			case 1: system("cls");
				system("pause>nul");
				break;
			case 2: system("cls");
				system("pause>nul");
				break;
			case 3: system("cls");
				system("pause>nul");
				break;
			case 4: system("cls");
				system("pause>nul");
				break;
			case 5: band=false;
				break;
		}
	}while(band);
	system("cls");
	gotoxy(40, 12); printf("Se cerro el modulo de administracion. Adios...\n\n\n\n");
	system("pause>nul");
}

int menu(const char *titulo, const char *opciones[], int N){
	
	int opcSeleccionada=1, tecla;
	bool band=true;
		
	do{
		system("cls");
		marco();
		textcolor(YELLOW);
		gotoxy(56, 3); printf("%cBIENVENIDO%c", 173, 33);
		textcolor(WHITE);
		gotoxy(40, 9+opcSeleccionada); textcolor(CYAN); printf("==>"); textcolor(WHITE);
		gotoxy(50, 7); printf("%s", titulo);
		textcolor(RED);
		gotoxy(19, 19); printf("%cNOTA:", 175);
		textcolor(WHITE);
		gotoxy(26, 19); printf("Utilize las flechas direccionales para moverse en las opciones y ENTER para seleccionar.");
			for(int i=0; i<N; i++){
				gotoxy(44, 10+i); printf("%d- %s", i+1, opciones[i]);
			}
			do{
				tecla= getch();  
			}while(tecla!=UP && tecla!=DOWN && tecla!=ENTER);
			switch(tecla){
				case UP:
						opcSeleccionada++;
						if(opcSeleccionada>5){
							opcSeleccionada=1;
						}
						Beep(1300, 100);
					break;
				case DOWN: 
						opcSeleccionada--;
						if(opcSeleccionada<1){
							opcSeleccionada=N;
						}
						Beep(1300, 100);
					break;
				case ENTER:
						band=false;
						Beep(800, 100); 
					break;
			}
	}while(band);
	return opcSeleccionada;
}
