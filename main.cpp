#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
#include "conio.c"
#include <string.h>
#include <iostream>

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

bool registroUser(usuario user);
bool registroVet(usuario vet);
bool verificarPassword(usuario pass);
bool verifUser(usuario user);
void atencionesVeterinarios();
void rankingDeVeterinarios();

int main(int argc, char const *argv[])
{
    usuario user;
    registroUser(user);
    return 0;
}

bool registroUser(usuario user){
    FILE *arch=fopen("Usuarios.dat", "a+b");
    usuario aux;
    bool band=false, vBool;
	do
    {
        band=false;
        system("cls");
        printf("\n\n\t\tRegistro de usuario\n\t===============================================");
        printf("\n\n\t\tIngrese usuario: ");
        gets(user.usuario);
        vBool=verifUser(user);
        if (vBool == true)
        {
            rewind(arch);
            fread(&aux, sizeof(usuario), 1, arch);
            for (int i = 0; !feof(arch) ; i++)
            {
                if(strcmp(user.usuario, aux.usuario)==0){
                    band=true;
                    break;
                }
                fread(&aux, sizeof(usuario), 1, arch);
            }
            if (band)
            {
                printf("\n\t\t\tEL USUARIO INGRESADO YA EXISTE, VUELVA A INTENTAR.");
            }
            
        }else system("pause");	
		
        
    } while (band==true or vBool==false);
    
    _flushall();
    do
    {
        printf("\t\tIngrese contrasenia: ");
        gets(user.contrasenia);
        band=verificarPassword(user);
        
    } while (band==false);
    
    printf("\t\tIngrese apellido y nombre: ");
    gets(user.apeNom);
	printf("\t\tIngrese DNI: ");
	scanf("%d", &user.dni);
	printf("\t\tIngrese tipo de usuario [V=Veterinario;A=asistente]: ");
	_flushall();
	scanf("%c", &user.tipoUsuario);
	
    
    if(user.tipoUsuario=='V' || user.tipoUsuario == 'v'){
        registroVet(user);
    }
    fseek(arch, sizeof(usuario), SEEK_END);
    fwrite(&user, sizeof(usuario), 1, arch);
    printf("\n\t\t\tSE HA REGISTRADO DE FORMA EXITOSA.");

    
    fclose(arch);
}

bool registroVet(usuario user){
	veterinario vet, aux;
    bool band=false,bandnom=false;        

	FILE *arch = fopen("Veterinarios.dat", "a+b");

    system("cls");
	printf("\n\n\t\tRegistro de veterinario\n\t\t=====================\n\n");
    
    do{
	    printf("\t\tIngrese su matricula: ");
	    scanf("%d", &vet.matricula);
        if(vet.matricula==0){
                break;
        }
	    rewind(arch);
	    fread(&aux, sizeof(vet), 1, arch);
	    for (int i = 0; !feof(arch) ; i++)
        {
            if(vet.matricula==aux.matricula){
                band=true;
                break;
            }
            fread(&aux, sizeof(vet), 1, arch);
        }
        if(band){
            printf("\t\tLa matricula YA EXISTE. Ingrese una diferente para continuar o '0' para regresar a menu.");
        }
    }while(band);

    if(vet.matricula != 0){
	    strcpy(vet.apeNom,user.apeNom);
		vet.dni=user.dni;
        printf("\t\tIngrese su numero de telefono: ");
	    _flushall();
        gets(vet.telefono);
        fseek(arch, sizeof(veterinario), SEEK_END);
        fwrite(&vet, sizeof(veterinario), 1, arch);
	}
    fclose(arch);
}

bool verifUser(usuario user){
    int large, c=0;
    large=strlen(user.usuario);
    if(large>10 and large <6){
        printf("\n\t\tEl usuario debe tener entre 6 y 10 caracteres...");
        return false;
    } 
    if(user.usuario[0] > 122 or user.usuario[0] < 97) {
        printf("\n\t\tEl usuario debe comenzar con una minuscula...");
        return false;
    }
    for (int i = 0; i < large ; i++)
    {
        if (user.usuario[i]>=65 and user.usuario[i]<=90)
        {
            c++;
        }
        if(c>=2) break;
    }
    if(c<2) {
        printf("\n\t\tEl usuario debe tener como minimo dos mayusculas...");
        return false;
    }
    c=0;
    for (int i = 0; i < large ; i++)
    {
        if (user.usuario[i]>=33 and user.usuario[i]<=64)
        {
            c++;
        }
        if(c>3) {
            printf("\n\t\tEl usuario debe tener como maximo 3 digitos...");
            return false;
        }
    }
    return true;
}

bool verificarPassword(usuario pass){
    int contMay=0,contMin=0,contNum=0;
    char aux[2];
    if(strlen(pass.contrasenia)>32 or strlen(pass.contrasenia)<6){
        printf("\n\t\tLa Contrasenia debe tener entre 6 y 32 caracteres...");
        return false;
    }
	for (int i = 0; i < strlen(pass.contrasenia); i++)
	{
		if(pass.contrasenia[i] >= 65 && pass.contrasenia[i]<= 90) contMay++;
	    if(pass.contrasenia[i] >= 97 && pass.contrasenia[i]<= 122) contMin++;
        if(pass.contrasenia[i] >= 97 && pass.contrasenia[i]<= 122) contNum++;
    }
    if(contMay==0 || contMin==0 || contNum==0){
		printf("\n\t\tLa Contrasenia debe tener al menos una letra mayuscula, una letra minuscula y un numero...");
        return false;
	}

    for (int i = 0; i < strlen(pass.contrasenia); i++)
	{
		if(pass.contrasenia[i] >= 160 && pass.contrasenia[i]<= 163 || pass.contrasenia[i] == 130 || pass.contrasenia[i] == 181 || pass.contrasenia[i] == 144 ||
            pass.contrasenia[i] == 214 || pass.contrasenia[i] == 224 || pass.contrasenia[i] == 233 ){
            printf("\n\t\tLa Contrasenia No puede contener acentos. Solo caracteres alfanumericos...");
		}
		
    }

    for (int i = 0; i < strlen(pass.contrasenia); i++)
    {   
        if(pass.contrasenia[i]=='.' or pass.contrasenia[i]==',' or pass.contrasenia[i]==';' or pass.contrasenia[i]==' '){
            printf("\n\t\tLa Contrasenia NO debe contener ningun caracter de puntuacion y/o espacios, solo caracteres alfanumericos...");
            return false;
        }
    }

    for (int i = 0; i < strlen(pass.contrasenia); i++)
    {
       if (pass.contrasenia[i+2]!='\0')
       {
           if(pass.contrasenia[i] <=48 && pass.contrasenia[i]<=57){
                if(pass.contrasenia[i+1] <=48 && pass.contrasenia[i+1]<=57){
                    if(pass.contrasenia[i+2] <=48 && pass.contrasenia[i+2]<=57){
                        printf("\n\t\tLa Contrasenia no debe tener 3 caracteres numericos consecutivos... ");
                        return false;
                    }
			    }
            }
       }
       
    }
    for (int i = 0; i < strlen(pass.contrasenia); i++)
    {   
        if (pass.contrasenia[i+1]!='\0')
        {
            aux[0]=pass.contrasenia[i];
            aux[1]=pass.contrasenia[i+1];
            toupper(aux[0]);
            toupper(aux[1]);
            if(aux[0]>=65 && aux[0]<=90 && aux[1]>=65 && aux[1]<=90)
            {
                if(aux[0]+1==aux[1])
                {
                    printf("\n\t\tLa Contrasenia NO debe contener caracteres consecutivos que refieran a letras alfabeticamente consecutivas...");
                    return false;
                }
            }
        }
        
    }
    return true;
}

void atencionesVeterinarios(){
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

void rankingDeVeterinarios(){
	typedef char nombres[50];
	nombres nombre[50];
	int cont;
	int c = 0;
    float porcen;
	FILE *arch = fopen("Turnos.dat", "r+b");
	FILE *arch1 = fopen("Veterinarios.dat", "r+b");
    
    turnos turno;
	veterinario vet;
    fread(&turno,sizeof(turnos),1,arch);
	while(!feof(arch)){
		
		if(turno.atendido==true) c++;
		
		fread(&turno,sizeof(turnos),1,arch);
    }
    rewind(arch);
	fread(&vet,sizeof(vet),1,arch1);
	while(!feof(arch1)){
        cont=0;
		rewind(arch);
	    fread(&turno,sizeof(turnos),1,arch);
	    while(!feof(arch)){
            if(vet.matricula == turno.matriculaVet && turno.atendido==true){
				cont++;
			}
			fread(&turno,sizeof(turnos),1,arch);
        }
        porcen=(float)cont*100/c;
        printf("\n\t======================================================");
		printf("\n\t\tNombre Veterinario: %s", vet.apeNom);
		printf("\n\t\tCantidad de turnos: %d", cont);
		printf("\n\t\tPorcentaje de turnos: %.2f", porcen);
		cont = 0;
		fread(&vet, sizeof(veterinario), 1, arch1);
	}

}
