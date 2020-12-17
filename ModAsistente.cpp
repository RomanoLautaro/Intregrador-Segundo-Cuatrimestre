#include "Owntools.h"

using namespace std;

struct usuario{
    char apeNom[60];
	char usuario[10];
	char contrasenia[32];
    char tipoUsuario;
	int dni;
};

struct veterinario{
	char apeNom[60];
    int matricula;
	int dni;
	char telefono[25];
};

struct fecha{
	int dia;
	int mes;
	int anio;
};

struct turnos{
	int matriculaVet;
	fecha fec;
	int dni_duenio;
    char detalles[382];
    bool atendido;
};

struct mascota{
	char apeNom[60];
	char domicilio[60];
	int dniDuenio;
	char localidad[60];
	fecha fechaDeNac;
	float peso;
	char telefono[25];
};

bool login();
void registrarMascota();
void registrarTurno();
void listadoAtenciones();
void password(int x, int y, char contrasenia[]);
void menuPrincipal(bool &b);

usuario admin;
const char *titulo[]={"REGISTRAR MASCOTA", "REGISTRAR TURNO"};

int main(int argc, char const *argv[])
{
    bool band=false, b=true;
    system("mode 120,35");
    do
    {
        system("cls");
        if(login()==true) {
            band = true;
        }
    } while (band==false);
    while (b)
    {
        menuPrincipal(b);
    }
    
    return 0;
}
//user=iGNa23
//pass=aS15sO
void menuPrincipal(bool &b){
	
	bool band=true;
	int Op;
	const char *titulo= "Modulo de Asistentes";
	const char *opciones[]={"Registrar mascota", "Registrar turno","Listado de atenciones por veterinarios" , "Salir"};
	
	do{
		
		system("cls");
		gotoxy(48, 32); printf("copyright%c 2020 GoldenCode\n\n",184);
		textcolor(WHITE);
		for(int i=35; i<88+1; i++){
		gotoxy(i, 20); printf("%c", 219);
		gotoxy(i, 25); printf("%c", 219);
		}    
		for(int i=20; i<25+1; i++){
			gotoxy(35, i); printf("%c", 178);
			gotoxy(88, i); printf("%c", 178);
		}
		textcolor(YELLOW);
		gotoxy(38, 22); printf("USUARIO: %s", admin.usuario);
		gotoxy(38, 23); printf("NOMBRE: %s", admin.apeNom);
		Op=menu(titulo, opciones, 4);
		switch(Op){
			case 1: system("cls"); registrarMascota();
				break;
			case 2: system("cls");registrarTurno();
				break;
			case 3: system("cls"); listadoAtenciones();
			case 4: band=false; b=false;
				break;
		}
	}while(band);
	system("cls");
	gotoxy(40, 12); printf("Se cerro el modulo de Asistente. Adios...\n\n\n\n");
	gotoxy(48, 32); printf("copyright%c 2020 GoldenCode\n\n",184);
	system("pause>nul");
}

void password(int x, int y, char contrasenia[]){
	int i=0;
	char pass[32], caracter;
	
	gotoxy(x,y);
	caracter=getch();
	while(caracter!=ENTER){
		if (caracter==8)
		{
			if (i>0)
			{
				i--;
				printf("\b \b");
				
			}
			
		}else if(i!=32)
		{
			printf("*");
			pass[i]=caracter;
			i++;
		}
		caracter=getch();	
	}
	pass[i]='\0';
	strcpy(contrasenia,pass);

}

bool login(){
    FILE *arch=fopen("Usuarios.dat", "r+b");
    usuario user;
    bool band=false;
    int error=0;
    system("mode 120,35");
    if (arch==NULL)
    {
        printf("\n\n\t\t No se ha registrado ningun usuario. Por favor solicite uno para poder continuar.");
        system("pause>nul");
        system("exit");
    
    }else{
        do{
            textcolor(YELLOW);
            marcoGenerico(25,95,9,23);
            textcolor(BLACK);
            textbackground(WHITE);
            gotoxy(50, 9); printf(" INGRESO DE USUARIO ");
			textbackground(BLACK); textcolor(WHITE);
            gotoxy(50-10, 15);printf("USUARIO: ");
            gotoxy(50-13, 17);printf("CONTRASE%cA: ", 165);
			fflush(stdin);
			gotoxy(58 - 10, 15); textbackground(WHITE); printf("                                 ");
			gotoxy(61-13, 17); textbackground(WHITE); printf("                                 ");
            textcolor(BLACK);
            gotoxy(58-10, 15); gets(user.usuario);
            password(61-13, 17 , user.contrasenia);
            textcolor(WHITE); textbackground(BLACK);
            rewind(arch);
            fread(&admin,sizeof(usuario),1,arch);
            while(!feof(arch)){
                if(strcmp(user.usuario,admin.usuario)==0){
                    band=true;
                    break; 
                }
                fread(&admin,sizeof(usuario),1,arch);
            }
            if(band==true){
                if(admin.tipoUsuario == 'A' || admin.tipoUsuario == 'a'){
                    if(strcmp(user.contrasenia,admin.contrasenia)==0){
                            band=true;
                            system("cls");
                            return true;
					}else{
                        textcolor(WHITE);
                        textbackground(LIGHTRED);
                        gotoxy(19-8, 21+7); printf(" %cNOTA: ", 175);
                        textcolor(BLACK);
                        textbackground(WHITE);
                        gotoxy(26-7, 21+7); printf(" La contrase%ca no coincide con el usuario. ", 164);
                        textbackground(BLACK);
                        system("pause>nul");
                        system("cls");	
                        band=false;	
					}
                }else{
                    textcolor(WHITE);
                    textbackground(LIGHTRED);
                    gotoxy(19-8, 21+7); printf(" %cNOTA: ", 175);
                    textcolor(BLACK);
                    textbackground(WHITE);
                    gotoxy(26-7, 21+7); printf(" Los veterinarios no pueden ingresar a este modulo. ");
                    textbackground(BLACK);
                    textcolor(WHITE);
                    system("pause>nul");
                    system("cls");
                    band=false;	
                }
            }else{
                textcolor(WHITE);
                textbackground(LIGHTRED);
                gotoxy(19-8, 21+7); printf(" %cNOTA: ", 175);
                textcolor(BLACK);
                textbackground(WHITE);
                gotoxy(26-7, 21+7); printf(" El usuario no existe. ");
                textbackground(BLACK);
                system("pause>nul");
                system("cls");
            }
        } while (band==false);
        fclose(arch);
        return true;
    }
    
    
}

void registrarMascota(){
	mascota animal;
	FILE *arch = fopen("Mascotas.dat", "a+b");

	titulo_Generico(titulo, 0, 19, 4, 101, 4);
	gotoxy(22, 7); textcolor(YELLOW); printf("%cIngrese Nombre de la Mascota y el Apellido del due%co:", 175, 164);
	gotoxy(77, 7); textbackground(WHITE); textcolor(BLACK); printf("                     "); 
	fflush(stdin); gotoxy(77, 7); gets(animal.apeNom ); textbackground(BLACK); textcolor(WHITE);
    gotoxy(22, 9); textcolor(YELLOW); printf("%cIngrese DNI del due%co:", 175, 164);
    gotoxy(46, 9); textbackground(WHITE); textcolor(BLACK); printf("                     ");
	gotoxy(46, 9); scanf("%d",&animal.dniDuenio); textbackground(BLACK); textcolor(WHITE);
    gotoxy(22, 11); textcolor(YELLOW); printf("%cIngrese localidad:", 175);
    gotoxy(43, 11); textbackground(WHITE); textcolor(BLACK); printf("                        ");
	fflush(stdin); gotoxy(43, 11); gets(animal.localidad); textbackground(BLACK); textcolor(WHITE);
    gotoxy(22, 13); textcolor(YELLOW); printf("%cIngrese domicilio:", 175);
    gotoxy(42, 13); textbackground(WHITE); textcolor(BLACK); printf("                          ");
    fflush(stdin); gotoxy(42, 13); gets(animal.domicilio); textbackground(BLACK); textcolor(WHITE);
    gotoxy(22, 15); textcolor(YELLOW); printf("%cIngrese peso:", 175);
    gotoxy(38, 15); textbackground(WHITE); textcolor(BLACK); printf("      ");
	gotoxy(38, 15); scanf("%f", &animal.peso); textbackground(BLACK); textcolor(WHITE);
    gotoxy(22, 17); textcolor(YELLOW); printf("%cIngrese telefono:", 175);
    gotoxy(41, 17); textbackground(WHITE); textcolor(BLACK); printf("                         ");
	gotoxy(41, 17); scanf("%d", &animal.telefono); textbackground(BLACK); textcolor(WHITE);
    gotoxy(22, 19); textcolor(YELLOW); printf("%cFecha nacimiento DD/MM/AAAA:", 175);
    gotoxy(52, 19); textbackground(WHITE); printf("  "); textbackground(BLACK); 
    gotoxy(54, 19); textcolor(YELLOW); printf("/");
    gotoxy(55, 19); textbackground(WHITE); printf("  "); textbackground(BLACK);
    gotoxy(57, 19); textcolor(YELLOW); printf("/");
    gotoxy(58, 19); textbackground(WHITE); printf("    "); textcolor(BLACK);
    gotoxy(52, 19); scanf("%d", &animal.fechaDeNac.dia); gotoxy(55, 19); scanf("%d", &animal.fechaDeNac.mes);
    gotoxy(58, 19); scanf("%d", &animal.fechaDeNac.anio); textbackground(BLACK); textcolor(WHITE);
	fwrite(&animal, sizeof(mascota), 1, arch);
	gotoxy(44, 25); printf("Mascota registrada exitosamente...");
	system("pause>nul");
	fclose(arch);
}

void registrarTurno(){ 

	turnos tur;
	FILE *arch = fopen("Turnos.dat", "a+b");
	
	titulo_Generico(titulo, 1, 19, 4, 101, 4);
	gotoxy(24, 7); textcolor(YELLOW); printf("%cIngrese matricula del veterinario:", 175);
	gotoxy(60, 7); textbackground(WHITE); textcolor(BLACK); printf("       ");
	gotoxy(60, 7); scanf("%d",&tur.matriculaVet); textbackground(BLACK); textcolor(WHITE);
    gotoxy(24, 9); textcolor(YELLOW); printf("%cIngrese DNI del due%co:", 175, 164);
    gotoxy(48, 9); textbackground(WHITE); textcolor(BLACK); printf("          ");
	gotoxy(48, 9); scanf("%d",&tur.dni_duenio); textbackground(BLACK); textcolor(WHITE);
    gotoxy(24, 11); textcolor(YELLOW); printf("%cIngrese la fecha del turno DD/MM/AAAA:", 175);
    gotoxy(65, 11); textbackground(WHITE); printf("  "); textbackground(BLACK); 
    gotoxy(67, 11); textcolor(YELLOW); printf("/"); textbackground(WHITE);
    gotoxy(68, 11); textbackground(WHITE); printf("  "); textbackground(BLACK); 
    gotoxy(70, 11); textcolor(YELLOW); printf("/"); textbackground(WHITE);
	gotoxy(71, 11); textbackground(WHITE); printf("    "); textcolor(BLACK);
	gotoxy(65, 11); scanf("%d", &tur.fec.dia); gotoxy(68, 11); scanf("%d", &tur.fec.mes); 
	gotoxy(71, 11); scanf("%d", &tur.fec.dia); textbackground(BLACK); textcolor(WHITE);
    tur.atendido=false;

	fwrite(&tur, sizeof(turnos), 1, arch);
	gotoxy(44, 17); printf("Turno registrado exitosamente...");
	system("pause>nul");
	fclose(arch);
}

void listadoAtenciones(){
	FILE *arch = fopen("Turnos.dat", "r+b");
	FILE *arch1 = fopen("Veterinarios.dat", "r+b");
    FILE *arch2 = fopen("Mascotas.dat", "r+b");
	if(arch==NULL){
        gotoxy(44, 14); printf("NO SE ASIGNO NINGUN TURNO...");
        system("pause>nul");
    }else{
    	turnos turno;
		veterinario vet;
		fecha fecTurno;
		mascota masc;
		char nombreMascota[50];

		gotoxy(1, 3); textcolor(YELLOW); printf("Ingrese una fecha DD/MM/AAAA:");
		gotoxy(31, 3); textbackground(WHITE); printf("  "); textbackground(BLACK);
		gotoxy(33, 3);textcolor(YELLOW); printf("/");
		gotoxy(34, 3); textbackground(WHITE); printf("  "); textbackground(BLACK);
		gotoxy(36, 3);textcolor(YELLOW); printf("/");
		gotoxy(37, 3); textbackground(WHITE); printf("    "); textcolor(BLACK);
		gotoxy(31, 3); scanf("%d", &fecTurno.dia); gotoxy(34, 3); scanf("%d", &fecTurno.mes); 
		gotoxy(37, 3); scanf("%d", &fecTurno.anio); textbackground(BLACK); textcolor(WHITE);
		system("cls");

		rewind(arch);
		fread(&vet,sizeof(vet),1,arch1);
			while(!feof(arch1)){
				gotoxy(20, 4); textbackground(LIGHTRED); textcolor(WHITE);
    			printf("%c                         Veterinario %s                           %c", 219, vet.apeNom, 219);
    			textbackground(BLACK);
				rewind(arch);
	    		fread(&turno,sizeof(turnos),1,arch);
	    			while(!feof(arch)){
	    				rewind(arch2);
	    				fread(&masc,sizeof(mascota),1,arch2);
            				if(vet.matricula == turno.matriculaVet && turno.atendido==true && turno.fec.dia == fecTurno.dia && turno.fec.mes == fecTurno.mes && turno.fec.anio == fecTurno.anio){
								while(!feof(arch2)){
										if(turno.dni_duenio == masc.dniDuenio){
											break;
										}
                    					fread(&masc,sizeof(mascota),1,arch2);
								}
								printf("\n\n\t\tNombre de la Mascota: %s", masc.apeNom);
								printf("\n\t\tDNI del due%co: %d", 164, turno.dni_duenio);
                				printf("\n\t\tFecha: %d/%d/%d", turno.fec.dia, turno.fec.mes, turno.fec.anio);
                				printf("\n\t\tDetalle de la atencion: ");
                					for(int i=0; i<strlen(turno.detalles) ; i++){
                    					cout<<turno.detalles[i];
                    						if(i==80-24 or i==160-24 or i==240-24 or i==320-24){
                        						cout<<"\n\t\t";
                    						}				
                					}
							}
						fread(&turno,sizeof(turnos),1,arch);
        			}
				system("pause>nul");
				system("cls");
				fread(&vet, sizeof(veterinario), 1, arch1);
			}
    	system("pause>nul");
    	fclose(arch);
    	fclose(arch1);
    	fclose(arch2);
	}
}
