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
	int dniDuenio[10];
	char localidad[60];
	fecha fechaDeNac;
	float peso;
	char telefono[25];
};

bool login();
void registrarMascota();
void registrarTurno();
void listadoAtenciones();

usuario admin;

int main(int argc, char const *argv[])
{
    if(login()==true) {
        registrarMascota();
    }
    return 0;
}

bool login(){
    FILE *arch=fopen("Usuarios.dat", "r+b");
    usuario user;
    bool band=false;
    if (arch==NULL)
    {
        printf("\n\n\t\t No se ha registrado ningun usuario. Por favor solicite uno para poder continuar.");
        return false;
    }else{
        do{
            printf("\n\n\t\tUSUARIO: ");
            _flushall();
            gets(user.usuario);
            printf("\n\n\t\tCONTRASEÑA: ");
            gets(user.contrasenia);
            rewind(arch);
            fread(&admin,sizeof(usuario),1,arch);
            while(!feof(arch)){
                if(strcmp(user.usuario,admin.usuario)==0){
                    if(strcmp(user.contrasenia,admin.contrasenia)==0){
                        if(user.tipoUsuario == 'v' || user.tipoUsuario == 'V'){
                        	printf("\n\t\t*Los veterinarios no pueden ingresar a este modulo *");
                        	system("pause");
                        	system("cls");
                        	return false;
						}else{
							band=true;
                        	break;
						}
                    }else{
                        printf("\n\t\t* La contraseña no coincide con el usuario *");
                        system("pause");
                        system("cls");
                        return false;
                    }
                }else{
	                printf("\n\t\t* El usuario no existe *");
	                system("pause");
	                system("cls");
	                return false;
                }
                fread(&admin,sizeof(usuario),1,arch);
            }
            
        } while (band==false);
        return true;
    }
    fclose(arch);
    
}

void registrarMascota(){
	mascota animal;
	FILE *arch = fopen("Mascotas.dat", "a+b");
	fseek(arch,sizeof(mascota),SEEK_END);

	printf("\n\t\tIngrese apellido y nombre: ");
	fflush(stdin);
	gets(animal.apeNom );
    printf("\n\t\tIngrese DNI: ");
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
    printf("\n\t\tFecha:");
    printf("\n\t\t\tDia: ");
    scanf("%d", &animal.fechaDeNac.dia);
    printf("\n\t\t\tMes: ");
    scanf("%d", &animal.fechaDeNac.mes);
    printf("\n\t\t\tAnio: ");
    scanf("%d", &animal.fechaDeNac.anio);

	fwrite(&animal, sizeof(mascota), 1, arch);
	printf("\n\t\tTurno registrado exitosamente...");
	system("pause");
	fclose(arch);
}

void registrarTurno(){
	turnos tur;
	FILE *arch = fopen("Turnos.dat", "a+b");
	
	fseek(arch,sizeof(tur),SEEK_END);
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

	fwrite(&tur, sizeof(mascota), 1, arch);
	printf("\n\t\tTurno registrado exitosamente...");
	system("pause");
	fclose(arch);
}

void listadoAtenciones(){
	int c = 1;
	FILE *arch = fopen("Turnos.dat", "r+b");
	FILE *arch1 = fopen("Veterinarios.dat", "r+b");
    if(arch==NULL){
        printf("\n\n\t\tNO SE ASIGNO NINGUN TURNO...");
    }
    turnos turno;
	veterinario vet;
    
    rewind(arch);
	fread(&vet,sizeof(vet),1,arch1);
	while(!feof(arch1)){
		printf("\n\n\tVeterinario %s \n\t==================================", vet.apeNom);

		rewind(arch);
	    fread(&turno,sizeof(turnos),1,arch);
	    while(!feof(arch)){
            if(vet.matricula == turno.matriculaVet && turno.atendido==true){
				printf("\n\t\tAtencion Nro: %d", c);
				printf("\n\t\tDNI del duenio: %d", turno.dni_duenio);
                printf("\n\t\tFecha:");
                printf("\n\t\t\tDia: %d", turno.fec.dia);
                printf("\n\t\t\tMes: %d", turno.fec.mes);
                printf("\n\t\t\tAnio: %d", turno.fec.anio);
                printf("\n\t\tDetalle de la atencion: ");
                for(int i=0; i<strlen(turno.detalles) ; i++){
                    cout<<turno.detalles[i];
                    if(i>80 or i>160 or i>240 or i>320){
                        cout<<"\n";
                    }
                }
			}
			c++;
			fread(&turno,sizeof(turnos),1,arch);
        }    

        fread(&vet,sizeof(veterinario),1,arch1);
    }
    fclose(arch);
    fclose(arch1);
}
