#include "Owntools.h"

#define UP 80
#define DOWN 72
#define ENTER 13



void menu_principal();
int menu(const char *titulo, const char *opciones[], int N);


int main(){
	system("mode 120,35");
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
	textcolor(LIGHTRED);
	marco();
	textcolor(BLACK);
	textbackground(WHITE);
	gotoxy(50, 5); printf("%s", titulo);
	textcolor(WHITE);
	gotoxy(49, 5); printf("%c", 219);
	gotoxy(50+strlen(titulo), 5); printf("%c", 219);
	textbackground(BLACK);
	textcolor(WHITE);
	textbackground(LIGHTRED);
	gotoxy(19-8, 21+7); printf(" %cNOTA: ", 175);
	textcolor(BLACK);
	textbackground(WHITE);
	gotoxy(26-7, 21+7); printf(" Utilize las flechas direccionales para moverse en las opciones y ENTER para seleccionar. ");
	textbackground(BLACK);
	textcolor(WHITE);
	for(int i=0; i<N; i++){ 
		
		gotoxy(44, 10+i); printf("%d- %s", i+1, opciones[i]);
	}
	do{

		gotoxy(40, 9+opcSeleccionada); textcolor(YELLOW); printf("==>"); textcolor(WHITE);

			
			do{
				ocultarCursor();
			do{
				ocultarCursor();
				tecla= getch();  
			}while(tecla!=UP && tecla!=DOWN && tecla!=ENTER);
			switch(tecla){
				case UP:
						gotoxy(40, 9+opcSeleccionada); textcolor(CYAN); printf("   "); textcolor(WHITE);
						opcSeleccionada++;
						if(opcSeleccionada>5){
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
