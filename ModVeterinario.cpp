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
void listaDeEspera();
void registrarEvolucion();

usuario admin;

int main(int argc, char const *argv[])
{
    bool band=false;
    do
    {
        system("cls");
        if(login()==true) {
            band = true;
        }
    } while (band==false);
    
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
                if(user.tipoUsuario == 'V' || user.tipoUsuario == 'v'){
                    if(strcmp(user.usuario,admin.usuario)==0){
                        if(strcmp(user.contrasenia,admin.contrasenia)==0){
                            band=true;
                        	break;
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
                }else{
	                printf("\n\t\t*SOolo los veterinarios pueden ingresar a este modulo *");
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

void listaDeEspera(){
	turnos tur;
	veterinario vet;

	FILE *arch=fopen("Turnos.dat","r+b");
	FILE *arch1=fopen("Veterinario.dat","r+b");
	rewind(arch1);
	fread(&vet,sizeof(vet),1,arch1);
	while(!feof(arch1))
	{
			printf("\n\t\\tLista de espera\n\t==================================================\n")
			rewind(arch);
			fread(&tur,sizeof(tur),1,arch);
			while(!feof(arch)){
				if(tur.matriculaVet==vet.matricula){
					if(tur.atendido==false){
						printf("\n=====================================================\n");
						printf("\t\tDNI del duenio: %d\n",tur.dni_duenio);
						printf("\t\tFecha en la que se otorgo el turno: %d-%d-%d\n",tur.fec.dia,tur.fec.mes,tur.fec.anio);
					}
				}
				fread(&tur,sizeof(tur),1,arch);
			}
				
		fread(&vet,sizeof(vet),1,arch1);
	}
	
	fclose(arch);
	fclose(arch1);
	
}

void registrarEvolucion(){
	FILE *arch = fopen("Turnos.dat", "a+b");

}