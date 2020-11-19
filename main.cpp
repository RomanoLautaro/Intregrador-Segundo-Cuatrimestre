#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
#include "conio.c"

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

bool registroUser(usuario user);
bool registroVet(usuario vet);
bool verificarPassword(usuario pass);
bool verifUser(usuario user);
int main(int argc, char const *argv[])
{
    
    return 0;
}

bool registroUser(usuario user){
    FILE *arch=fopen("Usuarios.dat", "a+b");
    usuario aux;
    bool band=false;
	system("cls");
	printf("\n\n\t\tRegistro de usuario\n\t===============================================");
	printf("\n\n\t\tIngrese usuario: ");
    gets(user.usuario);
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
    _flushall();
    printf("\\t\tIngrese contraseña: ");
    gets(user.contrasenia);
    printf("\t\tIngrese apellido y nombre: ");
    gets(user.apeNom);
	printf("\t\tIngrese DNI: ");
	scanf("%d", &user.dni);
	printf("\t\tIngrese tipo de usuario [V=Veterinario;A=asistente]: ");
	scanf("%c", &user.tipoUsuario);
	
    
    if (band==false)
    {
        if(user.tipoUsuario=='V'){
            registroVet(user);
        }
        fseek(arch, sizeof(usuario), SEEK_END);
        fwrite(&user, sizeof(usuario), 1, arch);
        printf("\n\t\t\tSE HA REGISTRADO DE FORMA EXITOSA.");
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
    
}

bool verifUser(usuario user){
    int large, c=0;
    large=strlen(user.usuario);
    if(large>10 and large <6) return false;
    if(user.usuario[0] > 122 or user.usuario[0] < 97) return false;
    for (int i = 0; i < large ; i++)
    {
        if (user.usuario[i]>=65 and user.usuario[i]<=90)
        {
            c++;
        }
        if(c>=2) break;
    }
    if(c<2) return false;
    c=0;
    for (int i = 0; i < large ; i++)
    {
        if (user.usuario[i]>=33 and user.usuario[i]<=64)
        {
            c++;
        }
        if(c>3) return false;
    }
    return true;
}

bool verificarPassword(usuario pass){
    int contMay=0,contMin=0,contNum=0;
    if(strlen(pass.contrasenia)>32 or strlen(pass.contrasenia)<6) return false;
	for (int i = 0; i < strlen(pass.contrasenia); i++)
	{
		if(pass.contrasenia[i] >= 65 && pass.contrasenia[i]<= 90) contMay++;
	    if(pass.contrasenia[i] >= 97 && pass.contrasenia[i]<= 122) contMin++;
        if(pass.contrasenia[i] >= 97 && pass.contrasenia[i]<= 122) contNum++;
    }
    if(contMay==0 || contMin==0 || contNum==0){
		printf("\n\t\tLa Contrasenia debe tener al menos una letra mayúscula, una letra minúscula y un número...");
        return false;
	}

    for (int i = 0; i < strlen(pass.contrasenia); i++)
	{
		if(pass.contrasenia[i] >= 160 && pass.contrasenia[i]<= 163){
            printf("\n\t\tLa Contrasenia No puede contener acentos. Sólo caracteres alfanuméricos...");
		}
		if(pass.contrasenia[i] == 130 || pass.contrasenia[i] == 181 || pass.contrasenia[i] == 144 || pass.contrasenia[i] == 214 || pass.contrasenia[i] == 224 || pass.contrasenia[i] == 233  )
        {

        }
    }

    for (int i = 0; i < strlen(pass.contrasenia); i++)
    {
        if(pass.contrasenia[i]=='.' or pass.contrasenia[i]==',' or pass.contrasenia[i]==';' or pass.contrasenia[i]==' '){
            printf("\n\t\tLa Contrasenia NO debe contener ningún carácter de puntuación y/o espacios, sólo caracteres alfanuméricos...");
            return false;
        }
    }
    

}