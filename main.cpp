#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
#include "conio.c"

struct usuario{
    char apeNom[60];
	char usuario[10];
	char contrasenia[10];
    char tipoUsuario;
};
struct veterinario{
	char apeNom[60];
    int matricula;
	int dni;
	char telefono[25];
};

bool registroUser(usuario user);
bool registroVet(usuario vet);

int main(int argc, char const *argv[])
{
    
    return 0;
}

bool registroUser(usuario user){
    FILE *arch=fopen("Usuarios.dat", "a+b");
    usuario aux;
    bool band=false;
	system("cls");
	printf("\n\n\t\tRegistro de usuario\n\t\t=====================");
	printf("\n\n\t\tIngrese usuario: ");
    _flushall();
    gets(user.usuario);
    printf("\\t\tIngrese contraseña: ");
    gets(user.contrasenia);
    printf("\t\tIngrese apellido y nombre: ");
    gets(user.apeNom);
    printf("\t\tIngrese tipo de usuario [V=Veterinario;A=asistente]: ");
	scanf("%c", &user.tipoUsuario);
	rewind(arch);
    fread(&aux, sizeof(usuario), 1, arch);
    for (int i = 0; !feof(arch) ; i++)
    {
        if(strcmp(user.usuario, aux.usuario)==0){
            band=true;
            break;
        }
    }
    if (band==false)
    {
        if(user.tipoUsuario=='V'){
            registroVet(user);
        }
        // fseek(arch, sizeof(usuario), SEEK_END);
        // fwrite(&user, sizeof(usuario), 1, arch);
        // printf("\n\t\t\tSE HA REGISTRADO DE FORMA EXITOSA.");
    }else{
        printf("\n\t\t\tEL USUARIO INGRESADO YA EXISTE, VUELVA A INTENTAR.");
    }
    
    
}

bool registroVet(usuario user){
	veterinario vet, aux;
    bool band=false,bandnom=false;        

	FILE *arch = fopen("Veterinarios.dat", "a+b");

    system("cls");
	printf("\n\n\t\tRegistro de veterinario\n\t\t=====================");
    
    do{
	    printf("\t\tIngrese su matricula: ");
	    scanf("%d", &vet.matricula);

	    rewind(arch);
	    fread(&aux, sizeof(vet), 1, arch);
	    for (int i = 0; !feof(arch) ; i++)
        {
            if(vet.matricula==aux.matricula){
                band=true;
                break;
            }
        }

        if(band){
            printf("\t\tLa matricula YA EXISTE. Ingrese una diferente para continuar o '0' para regresar a menu: ");
            scanf("%d", &vet.matricula);
        }//ya termine broder, me voy a dormir... cambia lo que quieras xd

    }while(vet.matricula!=0);

    if(vet.matricula != 0){
        do{
	        printf("\t\tIngrese apellido y nombre de usuario: ");
	        _flushall();
            gets(vet.apeNom);
            if(strcmp(vet.apeNom,user.apeNom)!=0){
				printf("\n\t\tEl nombre ingresado no es valido, por favor ingrese su apellido y nombre de usuario...\n");
				bandnom = false;
			}else{
				bandnom = true;
			}
		} while (bandnom == false);

		printf("\t\tIngrese su dni: ");
		scanf("%d",&vet.dni);
        printf("\t\tIngrese su numero de telefono: ");
	    _flushall();
        gets(vet.telefono);
        fread(&aux, sizeof(usuario), 1, arch);
	}
    
}

