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

usuario admin;

int main(int argc, char const *argv[])
{
    if(login()==true) {
        
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
            fread(&admin,sizeof(usuario),1,arch);
            while(!feof(arch)){
                if(strcmp(user.usuario,admin.usuario)==0){
                    if(strcmp(user.contrasenia,admin.contrasenia)==0){
                        band=true;
                        break;
                    }else{
                        printf("\n\t\t* La contraseña no coincide con el usuario *");
                        system("pause");
                        system("cls");
                    }
                }else{
                    printf("\n\t\t* El usuario no existe *");
                    system("pause");
                    system("cls");
                }
                fread(&admin,sizeof(usuario),1,arch);
            }
        } while (band=false);
        return true;
    }
    
    
}

void registrarMascota(){
	mascota animal;
	FILE *arch = fopen("Mascotas.dat", "a+b");
	
	
	while(!feof(arch)){
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
	}
}

