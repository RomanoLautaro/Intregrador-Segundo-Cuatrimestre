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
void menuPrincipal();

usuario admin;

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
    while (band==true)
    {
        menuPrincipal();
    }
    
    return 0;
}
//user=iGNa23
//pass=aS15sO
void menuPrincipal(){
	
	bool band=true;
	int Op;
	const char *titulo= "Modulo de Asistentes";
	const char *opciones[]={"Registrar mascota", "Registrar turno","Listado de atenciones por veterinarios" , "Salir"};
	
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
		Op=menu(titulo, opciones, 4);
		switch(Op){
			case 1: system("cls"); registrarMascota();
				break;
			case 2: system("cls");registrarTurno();
				break;
			case 3: system("cls"); listadoAtenciones();
			case 4: system("exit");
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
            textbackground(BLACK);
            textcolor(WHITE);
            gotoxy(50-10, 15);printf("USUARIO: ");
            gotoxy(50-13, 17);printf("CONTRASE%cA: ", 165);
			fflush(stdin);
			gotoxy(58 - 10, 15);
			textbackground(WHITE);
			printf("                                 ");
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
                        gotoxy(26-7, 21+7); printf(" La contraseÃ±a no coincide con el usuario. ");
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

	printf("\n\t\tIngrese Nombre de la Mascota: ");
	fflush(stdin);
	gets(animal.apeNom );
    printf("\n\t\tIngrese DNI del duenio: ");
	scanf("%d",&animal.dniDuenio);
    printf("\n\t\tIngrese localidad: ");
	fflush(stdin);
	gets(animal.localidad);
    printf("\n\t\tIngrese domicilio: ");
    fflush(stdin);
	gets(animal.domicilio);
    printf("\n\t\tIngrese peso: ");
	scanf("%f", &animal.peso);
    printf("\n\t\tIngrese telefono: ");
	scanf("%d", &animal.telefono);
    printf("\n\t\tFecha nacimiento:");
    printf("\n\t\t\tDia: ");
    scanf("%d", &animal.fechaDeNac.dia);
    printf("\n\t\t\tMes: ");
    scanf("%d", &animal.fechaDeNac.mes);
    printf("\n\t\t\tAnio: ");
    scanf("%d", &animal.fechaDeNac.anio);

	//fseek(arch,sizeof(mascota),SEEK_END);
	fwrite(&animal, sizeof(mascota), 1, arch);
	printf("\n\t\tMascota registrada exitosamente...");
	system("pause>nul");
	fclose(arch);
}

void registrarTurno(){
	turnos tur;
	FILE *arch = fopen("Turnos.dat", "a+b");
	
	printf("\n\t\tIngrese matricula del veterinario: ");
	scanf("%d",&tur.matriculaVet);
    printf("\n\t\tIngrese DNI del duenio: ");
	scanf("%d",&tur.dni_duenio);
        
    printf("\n\t\tFecha:");
    printf("\n\t\t\tDia: ");
    scanf("%d", &tur.fec.dia);
    printf("\n\t\t\tMes: ");
    scanf("%d", &tur.fec.mes);
    printf("\n\t\t\tAnio: ");
    scanf("%d", &tur.fec.anio);
    tur.atendido=false;

	fwrite(&tur, sizeof(turnos), 1, arch);
	printf("\n\t\tTurno registrado exitosamente...");
	system("pause");
	fclose(arch);
}

void listadoAtenciones(){
	FILE *arch = fopen("Turnos.dat", "r+b");
	FILE *arch1 = fopen("Veterinarios.dat", "r+b");
    FILE *arch2 = fopen("Mascotas.dat", "r+b");
	if(arch==NULL){
        printf("\n\n\t\tNO SE ASIGNO NINGUN TURNO...");
    }
    turnos turno;
	veterinario vet;
	fecha fecTurno;
	mascota masc;
	char nombreMascota[50];

	printf("\n\nIngrese una fecha:\n\t\t\tDia: ");
	scanf("%d", &fecTurno.dia);
	printf("\t\t\tMes: ");
	scanf("%d", &fecTurno.mes);
    printf("\t\t\tAnio: ");
	scanf("%d", &fecTurno.anio);
	system("cls");

	rewind(arch);
	fread(&vet,sizeof(vet),1,arch1);
	while(!feof(arch1)){
		printf("\n\n\tVeterinario %s \n\t==================================", vet.apeNom);
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
				printf("\n\t\t---------------------------------");
				printf("\n\t\tNombre de la Mascota: %s", masc.apeNom);
				printf("\n\t\tDNI del duenio: %d", turno.dni_duenio);
                printf("\n\t\tFecha: %d/%d/%d", turno.fec.dia, turno.fec.mes, turno.fec.anio);
                printf("\n\t\tDetalle de la atencion: ");
                for(int i=0; i<strlen(turno.detalles) ; i++){
                    cout<<turno.detalles[i];
                    if(i>80 or i>160 or i>240 or i>320){
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
    system("pause<nul");
    fclose(arch);
    fclose(arch1);
    fclose(arch2);
}
