#include "Owntools.h"

using namespace std;

struct fecha{
	int dia;
	int mes;
	int anio;
};

struct usuario{
    char apeNom[60];
	char usuario[10];
	char contrasenia[32];
    char tipoUsuario;
	int dni;
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
struct veterinario{
	char apeNom[60];
    int matricula;
	int dni;
	char telefono[25];
};

struct turnos{
	int matriculaVet;
	fecha fec;
	int dni_duenio;
    char detalles[382];
    bool atendido;
};

struct atenciones{
	char apeNom[60];
	int cantAten;
	float porc;
};

void registroUser(usuario user);
void registroVet(usuario vet);
bool verificarPassword(usuario pass);
bool verifUser(usuario user);
void atencionesVeterinarios();
void rankingDeVeterinarios();
void menu_principal(usuario user);    
void barraPorcentaje(float Porcen, int x, int y);

const char *titulo[]={"REGISTRO DE USUARIO", "REGISTRO DE VETERINARIO"};
 
int main(int argc, char const *argv[]){
    system("mode 120,35");
    usuario user; 
    menu_principal(user);    
    return 0;
}

void menu_principal(usuario user){
	
	bool band=true;
	int Op;
	const char *titulo= "Modulo de Administracion";
	const char *opciones[]={"Registrar Usuario", "Atenciones por Veterinarios", "Ranking de Veterinarios por Atenciones", "Salir"};
	
	do{
		system("cls");
		gotoxy(48, 32); printf("copyright%c 2020 GoldenCode",184);
		Op=menu(titulo, opciones, 4);
		switch(Op){
			case 1: system("cls"); registroUser(user);
				break;
			case 2: system("cls");atencionesVeterinarios();
				break;
			case 3: system("cls");rankingDeVeterinarios();
				break;
			case 4: band=false;
				break;
		}
	}while(band);
	system("cls");
	gotoxy(40, 12); printf("Se cerro el modulo de administracion. Adios...\n\n\n\n");
	gotoxy(48, 32); printf("copyright%c 2020 GoldenCode\n\n",184);
	system("pause>nul");
}

void registroUser(usuario user){
    FILE *arch=fopen("Usuarios.dat", "a+b");
    usuario aux;
    bool band=false, vBool;
	do{
        band=false;
        system("cls");
        titulo_Generico(titulo, 0, 19, 4, 101, 4);
        gotoxy(22, 7); textcolor(YELLOW); printf("%cINGRESE USUARIO:", 175);
		gotoxy(40, 7); textbackground(WHITE); textcolor(BLACK); printf("                                 "); 
		gotoxy(40, 7); gets(user.usuario); textbackground(BLACK); textcolor(WHITE);
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
                system("pause>nul");
            }
            
        }else system("pause>nul");	
    } while (band==true or vBool==false);
    _flushall();
    do{
        system("cls");
    	titulo_Generico(titulo, 0, 19, 4, 101, 4);
		gotoxy(22, 7); textcolor(YELLOW); printf("%cINGRESE USUARIO:", 175);
		gotoxy(41, 7); textbackground(WHITE); textcolor(BLACK); printf("%s                               ", user.usuario);
		textbackground(BLACK); textcolor(WHITE);
		gotoxy(22, 9); textcolor(YELLOW); printf("%cINGRESE CONTRASENIA:", 175);
		gotoxy(44, 9); textbackground(WHITE); textcolor(BLACK); printf("                                  ");
		gotoxy(44, 9); gets(user.contrasenia); textbackground(BLACK); textcolor(WHITE);
        band=verificarPassword(user);
    } while (band==false);
    
   	gotoxy(22, 11); textcolor(YELLOW); printf("%cINGRESE APELLIDO Y NOMBRE:", 175);
	gotoxy(50, 11); textbackground(WHITE); textcolor(BLACK); printf("                                 "); 
	gotoxy(50, 11); gets(user.apeNom); textbackground(BLACK); textcolor(WHITE);
	gotoxy(22, 13); textcolor(YELLOW); printf("%cINGRESE DNI:", 175);
	gotoxy(36, 13); textbackground(WHITE); textcolor(BLACK); printf("                                 "); 
	gotoxy(36, 13); scanf("%d", &user.dni);textbackground(BLACK); textcolor(WHITE);
	gotoxy(22, 15); textcolor(YELLOW); printf("%cINGRESE TIPO DE USUARIO [V=Veterinario; A=asistente]:", 175);
	gotoxy(77, 15); textbackground(WHITE); textcolor(BLACK); printf("      ");  
	gotoxy(77, 15);_flushall(); scanf("%c", &user.tipoUsuario); textbackground(BLACK); textcolor(WHITE);
    
    if(user.tipoUsuario=='V' || user.tipoUsuario == 'v'){
        registroVet(user);
    }
    fseek(arch, sizeof(usuario), SEEK_END);
    fwrite(&user, sizeof(usuario), 1, arch);
    gotoxy(40, 21); printf("SE HA REGISTRADO DE FORMA EXITOSA.");
    fclose(arch);
    system("pause>nul");
}

void registroVet(usuario user){
	veterinario vet, aux;
    bool band=false,bandnom=false;        

	FILE *arch = fopen("Veterinarios.dat", "a+b");

    system("cls");
	titulo_Generico(titulo, 1, 19, 4, 101, 4);
    
    do{
	    gotoxy(22, 7); textcolor(YELLOW); printf("%cINGRESE SU MATRICULA:", 175);
		gotoxy(45, 7); textbackground(WHITE); textcolor(BLACK); printf("       "); 
		gotoxy(45, 7); scanf("%d", &vet.matricula); textbackground(BLACK); textcolor(WHITE);
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
            printf("\n\t\t\tLa matricula YA EXISTE. Ingrese una diferente para continuar o '0' para regresar a menu.");
        }
    }while(band);

    if(vet.matricula != 0){
	    strcpy(vet.apeNom,user.apeNom);
		vet.dni=user.dni;
        gotoxy(22, 9); textcolor(YELLOW); printf("%cINGRESE SU NUMERO DE TELEFONO:", 175);
		gotoxy(54, 9); textbackground(WHITE); textcolor(BLACK); printf("                       "); 
		gotoxy(54, 9); _flushall(); gets(vet.telefono); textbackground(BLACK); textcolor(WHITE);
        fseek(arch, sizeof(veterinario), SEEK_END);
        fwrite(&vet, sizeof(veterinario), 1, arch);
	}
    fclose(arch);
}

bool verifUser(usuario user){
    int large, c=0;
    large=strlen(user.usuario);
    if(large>10 and large <6){
        printf("\n\t\t\tEl usuario debe tener entre 6 y 10 caracteres...");
        system("pause>nul");
        return false;
    } 
    if(user.usuario[0] > 122 or user.usuario[0] < 97) {
        printf("\n\t\t\tEl usuario debe comenzar con una minuscula...");
        system("pause>nul");
        return false;
    }
    for (int i = 0; i < large ; i++)
    {
        if (user.usuario[i]>=65 and user.usuario[i]<=90){
            c++;
        }
        if(c>=2) break;
    }
    if(c<2) {
        printf("\n\t\t\tEl usuario debe tener como minimo dos mayusculas...");
        system("pause>nul");
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
            printf("\n\t\t\tEl usuario debe tener como maximo 3 digitos...");
            system("pause>nul");
            return false;
        }
    }
    return true;
}

bool verificarPassword(usuario pass){
    int contMay=0,contMin=0,contNum=0;
    char aux[2];
    if(strlen(pass.contrasenia)>32 or strlen(pass.contrasenia)<6){
        printf("\n\t\t\tLa Contrasenia debe tener entre 6 y 32 caracteres...");
        system("pause>nul");
        return false;
    }
	for (int i = 0; i < strlen(pass.contrasenia); i++){
		if(pass.contrasenia[i] >= 65 && pass.contrasenia[i]<= 90) contMay++;
	    if(pass.contrasenia[i] >= 97 && pass.contrasenia[i]<= 122) contMin++;
        if(pass.contrasenia[i] >= 97 && pass.contrasenia[i]<= 122) contNum++;
    }
    if(contMay==0 || contMin==0 || contNum==0){
		printf("\n\t\t\tLa Contrasenia debe tener al menos una letra mayuscula, una letra minuscula y un numero...");
		system("pause>nul");
        return false;
	}

    for (int i = 0; i < strlen(pass.contrasenia); i++){
		if(pass.contrasenia[i] >= 160 && pass.contrasenia[i]<= 163 || pass.contrasenia[i] == 130 || pass.contrasenia[i] == 181 || pass.contrasenia[i] == 144 ||
            pass.contrasenia[i] == 214 || pass.contrasenia[i] == 224 || pass.contrasenia[i] == 233 ){
            printf("\n\t\t\tLa Contrasenia No puede contener acentos. Solo caracteres alfanumericos...");
            system("pause>nul");
            return false;
		}
		
    }

    for (int i = 0; i < strlen(pass.contrasenia); i++){   
        if(pass.contrasenia[i]=='.' or pass.contrasenia[i]==',' or pass.contrasenia[i]==';' or pass.contrasenia[i]==' '){
            printf("\n\t\t\tLa Contrasenia NO debe contener ningun caracter de puntuacion y/o espacios, solo caracteres alfanumericos...");
            system("pause>nul");
            return false;
        }
    }

    for (int i = 0; i < strlen(pass.contrasenia); i++){
       if (pass.contrasenia[i+2]!='\0'){
           if(pass.contrasenia[i] <=48 && pass.contrasenia[i]<=57){
                if(pass.contrasenia[i+1] <=48 && pass.contrasenia[i+1]<=57){
                    if(pass.contrasenia[i+2] <=48 && pass.contrasenia[i+2]<=57){
                        printf("\n\t\t\tLa Contrasenia no debe tener 3 caracteres numericos consecutivos... ");
                        system("pause>nul");
                        return false;
                    }
			    }
            }
       }
       
    }
    for (int i = 0; i < strlen(pass.contrasenia); i++){   
        if (pass.contrasenia[i+1]!='\0'){
            aux[0]=pass.contrasenia[i];
            aux[1]=pass.contrasenia[i+1];
            toupper(aux[0]);
            toupper(aux[1]);
            if(aux[0]>=65 && aux[0]<=90 && aux[1]>=65 && aux[1]<=90){
                if(aux[0]+1==aux[1]){
                    printf("\n\t\t\tLa Contrasenia NO debe contener caracteres consecutivos que refieran a letras alfabeticamente consecutivas...");
                    system("pause>nul");
                    return false;
                }
            }
        }
        
    }
    return true;
}

void atencionesVeterinarios(){
	FILE *arch = fopen("Turnos.dat", "r+b");
	FILE *arch1 = fopen("Veterinarios.dat", "r+b");
    FILE *arch2 = fopen("Mascotas.dat", "r+b");
    if(arch==NULL){
    	system("cls");
        gotoxy(42, 12); printf("NO SE ASIGNO NINGUN TURNO...");
        system("pause>nul");
    }else{
    	turnos turno;
	veterinario vet;
    mascota masc;
	char nombreMascota[50];
    rewind(arch);
	fread(&vet,sizeof(vet),1,arch1);
	while(!feof(arch1)){
	
	gotoxy(20, 4);
    textbackground(LIGHTRED);
    textcolor(WHITE);
    printf("%c                         Veterinario %s                           %c", 219, vet.apeNom, 219);
    textbackground(BLACK);
	printf("\n");
		rewind(arch);
	    fread(&turno,sizeof(turnos),1,arch);
	    while(!feof(arch)){
	    	
	    	rewind(arch2);
	    	fread(&masc,sizeof(mascota),1,arch2);
        	while(!feof(arch2)){
		    	if(turno.dni_duenio == masc.dniDuenio){
               		strcpy(nombreMascota,masc.apeNom);
					break;
           		}
				fread(&masc,sizeof(mascota),1,arch2);
			}
			printf("\n");
            if(vet.matricula == turno.matriculaVet && turno.atendido==true){
				textcolor(YELLOW); printf("\n\t\t\t%c ", 175); textcolor(WHITE); printf("Nombre de la mascota: %s\n", nombreMascota);
				textcolor(YELLOW); printf("\t\t\t%c ", 175); textcolor(WHITE); printf("DNI del duenio: %d\n", turno.dni_duenio);
                textcolor(YELLOW); printf("\t\t\t%c ", 175); textcolor(WHITE); printf("Fecha en la que se otorgo el turno: %d/%d/%d\n", turno.fec.dia, turno.fec.mes, turno.fec.anio);
                textcolor(YELLOW); printf("\t\t\t%c ", 175); textcolor(WHITE); printf("Detalle de la atencion: ");
                for(int i=0; i<strlen(turno.detalles) ; i++){
                    cout<<turno.detalles[i];
                    if(i==47 or i==120 or i==240 or i==320){
                        cout<<"\n\t\t\t  ";
                    }
                }
                printf("\n\n\t\t     ==============================================================================\n");
			}
			fread(&turno,sizeof(turnos),1,arch);
        }
		system("pause>nul");
		system("cls");
		fread(&vet,sizeof(veterinario),1,arch1);
    }
    fclose(arch);
    fclose(arch1);
	}
}

void rankingDeVeterinarios(){
	typedef char nombres[50];
	nombres nombre[50];
	int cont, turnTotal=0, contLineas=0, N=0;
	int c = 0;
    float porcen;
	FILE *arch = fopen("Turnos.dat", "r+b");
	FILE *arch1 = fopen("Veterinarios.dat", "r+b");
    turnos turno;
	veterinario vet;
    atenciones atencion[50], aux;
    if (arch!=NULL and arch1!=NULL) {
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
            strcpy(atencion[N].apeNom, vet.apeNom);
            atencion[N].cantAten=cont;
            atencion[N].porc=porcen;
            N++;
            fread(&vet, sizeof(veterinario), 1, arch1);
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++){
                if (atencion[i].cantAten>atencion[j].cantAten){
                    strcpy(aux.apeNom, atencion[i].apeNom);
                    aux.cantAten=atencion[i].cantAten;
                    aux.porc=atencion[i].porc;
                    strcpy(atencion[i].apeNom, atencion[j].apeNom);
                    atencion[i].cantAten=atencion[j].cantAten;
                    atencion[i].porc=atencion[j].porc;
                    strcpy(atencion[j].apeNom, aux.apeNom);
                    atencion[j].cantAten=aux.cantAten;
                    atencion[j].porc=aux.porc;
                }
                
            }
            
        }
        gotoxy(24, 4);
        textbackground(LIGHTRED);
        textcolor(WHITE);
        printf("%c                  RANKING DE ATENCIONES POR VETERINARIOS                  %c", 219,219);
        textbackground(BLACK);
        for (int i = 0; i < N; i++){
            for (int j = 8; j < 114; j++){
                gotoxy(j,6+contLineas+1);printf("%c", 220);
            }
            textcolor(LIGHTRED);
            textbackground(WHITE);
            gotoxy(56,6+contLineas+1);printf("  Puesto %d  ", i+1);
            textcolor(WHITE);
            textbackground(BLACK);
            gotoxy(10,9+contLineas);printf("\t\tNombre Veterinario: %s", atencion[i].apeNom);
            gotoxy(10,10+contLineas);printf("\t\tCantidad de turnos: %d", atencion[i].cantAten);
            barraPorcentaje(atencion[i].porc,10,11+contLineas);
            contLineas+=6;
        }
        
        system("pause>nul");

        fclose(arch);
        fclose(arch1);
    }else{
    	system("cls");
        gotoxy(42, 12); printf("NO SE HAN AGREGADO TURNOS...");
        system("pause>nul");
    }
}
