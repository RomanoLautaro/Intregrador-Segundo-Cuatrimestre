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
void listaDeEspera();
void registrarEvolucion();
void password(int x, int y, char contrasenia[]);
void menuPrincipal();

usuario admin;
veterinario datos;

int main(int argc, char const *argv[])
{
    bool band=false;
	system("mode 120,35");
    do
    {
        system("cls");
        if(login()==true) {
            band = true;
        }
    } while (band==false);
    menuPrincipal();
    return 0;
}

void menuPrincipal(){
	
	bool band=true;
	int Op;
	const char *titulo= "Modulo de Veterinarios";
	const char *opciones[]={"Visualizar Lista de Espera", "Registrar Evolucion de Mascota", "Salir"};
	
	do{
		
		system("cls");
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
		Op=menu(titulo, opciones, 3);
		switch(Op){
			case 1: system("cls"); listaDeEspera();
				break;
			case 2: system("cls");registrarEvolucion();
				break;
			case 3: band=false;
				break;
		}
	}while(band);
	system("cls");
	gotoxy(40, 12); printf("Se cerro el modulo de administracion. Adios...\n\n\n\n");
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
	FILE *arch1=fopen("Veterinarios.dat", "r+b");
    usuario user;
    bool band=false;
    system("mode 120,35");
    if (arch==NULL and arch1==NULL)
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
            textbackground(BLACK);
            textcolor(WHITE);
            gotoxy(50-10, 15);printf("USUARIO: ");
            gotoxy(50-13, 17);printf("CONTRASE%cA: ", 165);
            _flushall();
            gotoxy(58-10, 15); textbackground(WHITE); printf("                                 ");
            gotoxy(61-13, 17); textbackground(WHITE); printf("                                 ");
            textcolor(BLACK);
            gotoxy(58-10, 15); gets(user.usuario);
            password(61-13, 17 , user.contrasenia);
            //gotoxy(63, 17);gets(user.contrasenia);
            textcolor(WHITE);
            textbackground(BLACK);
            rewind(arch);
            fread(&admin,sizeof(usuario),1,arch);
            while(!feof(arch)){
                if(strcmp(user.usuario,admin.usuario)==0){
                    band=true;
                    break; 
                }
                //else{

                //     textcolor(WHITE);
                //     textbackground(LIGHTRED);
                //     gotoxy(19-8, 21+7); printf(" %cNOTA: ", 175);
                //     textcolor(BLACK);
                //     textbackground(WHITE);
                //     gotoxy(26-7, 21+7); printf(" El usuario no existe. ");
                //     textbackground(BLACK);
                //     textcolor(WHITE);
	            //     system("pause>nul");
	            //     system("cls");
	            //     return false;
                // }
                fread(&admin,sizeof(usuario),1,arch);
            }
            if(band==true){
                if(admin.tipoUsuario == 'V' || admin.tipoUsuario == 'v'){
                    if(strcmp(user.contrasenia,admin.contrasenia)==0){
                            band=true;
                            system("cls");
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
                    gotoxy(26-7, 21+7); printf(" Solo los veterinarios pueden ingresar a este modulo. ");
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
		fread(&datos,sizeof(veterinario),1,arch1);
        while(!feof(arch1)){
			if(admin.dni==datos.dni) break;
			fread(&datos,sizeof(veterinario),1,arch1);
		}
		
    }
    fclose(arch);
	fclose(arch1);
    return true;
    
}

void listaDeEspera(){
	turnos tur;
	veterinario vet;
	mascota masc;
	int dniduenio;
	bool band=false,turnoparavet=false;
	char opc;

	FILE *arch=fopen("Turnos.dat","r+b");
	FILE *arch1=fopen("Veterinarios.dat","r+b");
	FILE *arch2=fopen("Mascotas.dat","r+b");
	if(arch==NULL){
		printf("\n\t\tNo se registro ningun turno...");
		system("pause");
	}
	else if(arch1==NULL){
			printf("\n\t\tNo se registro ningun Veterinario...");
			system("pause");
		}
		else if(arch2==NULL){
			printf("\n\t\tNo se registro ninguna mascota...");
			system("pause");
		}
		else{
			printf("\n\t\tLista de espera\n\t==================================================\n");
			rewind(arch1);
			fread(&vet, sizeof(vet), 1, arch1);
			while (!feof(arch1))
			{
				if (admin.dni == vet.dni)
				{
					rewind(arch);
					fread(&tur, sizeof(tur), 1, arch);
					while (!feof(arch))
					{
						if (tur.matriculaVet == vet.matricula)
						{
							if (tur.atendido == false)
							{
								printf("\n\t\t=====================================================\n");
								printf("\t\tDNI del duenio: %d\n", tur.dni_duenio);
								printf("\t\tFecha en la que se otorgo el turno: %d-%d-%d\n", tur.fec.dia, tur.fec.mes, tur.fec.anio);
								turnoparavet = true;
								printf("\n\t\t=====================================================\n");
							}
						}
						fread(&tur, sizeof(tur), 1, arch);
					}
				}
				fread(&vet, sizeof(vet), 1, arch1);
			}
			if(turnoparavet==true){
				do{
					printf("\n\n\t\tDesea ver informacion de alguna mascota? [s/n]: ");
					fflush(stdin);
					scanf("%c",&opc);
					if(opc == 's' || opc == 'S'){
						printf("\n\t\tIngrese dni del duenio de la mascota: ");
						scanf("%d",&dniduenio);
						rewind(arch2);
						fread(&masc,sizeof(mascota),1,arch2);
						while(!feof(arch2) && band==false){
							if(dniduenio==masc.dniDuenio){
								printf("\n\n\t\tNombre y apellido: %s",masc.apeNom);
								printf("\n\t\tPeso: %.2f",masc.peso);
								printf("\n\t\tFecha de nacimiento: %d-%d-%d",masc.fechaDeNac.dia,masc.fechaDeNac.mes,masc.fechaDeNac.anio);
								printf("\n\t\tLocalidad: %s",masc.localidad);
								printf("\n\t\tDomicilio: %s",masc.domicilio);
								printf("\n\t\tDni del duenio: %d",masc.dniDuenio);
								printf("\n\t\tTelefono: %s",masc.telefono);
								band=true;
					
							}
							fread(&masc,sizeof(mascota),1,arch2);
						}
						if(band==false){
							printf("\n\t\tNo se registro ninguna mascota con dicho dni...");
						}
					}
				}while(opc == 's' || opc == 'S');
			}else{
				printf("\n\t\tNo hay turnos registrados...");
				system("pause");
			}
		}
	fclose(arch);
	fclose(arch1);
	fclose(arch2);
}

void registrarEvolucion(){
	turnos tur;
	int dniduenio;
	bool band=false;
	char  opc;
	
	FILE *arch = fopen("Turnos.dat", "a+b");
	if(arch==NULL){
		printf("\n\t\tNo hay turnos diaponibles para registrar evolucion...");
		system("pause");
	}else{
		do{
			printf("\n\t\tIngrese dni del duenio de la mascota: ");
			scanf("%d",&dniduenio);
			rewind(arch);
			fread(&tur,sizeof(turnos),1,arch);
			while(!feof(arch)&&band==false) {
				if(tur.dni_duenio==dniduenio){
					band=true;
					printf("\n\t\tEvolucion de la mascota: ");
					fflush(stdin);
					gets(tur.detalles);
				}
				fread(&tur,sizeof(turnos),1,arch);
			}
			if(band==false){
				printf("La mascota no pudo ser encontrada, desea intentar nuevamente? [s/n]: ");
				fflush(stdin);
				scanf("%c",&opc);
			}
			else{
				printf("\n\t\tEvolucion registrada con exito...");
				opc='n';
				system("pause");
			}
		
		}while(opc=='s' || opc=='S');
	}
	fclose(arch);
}




