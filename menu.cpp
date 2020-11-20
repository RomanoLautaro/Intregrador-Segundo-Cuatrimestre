#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
#include "conio.c"
#include <string.h>
#include <iostream>

using namespace std;
void menu();

int main(int argc, char const *argv[])
{
    system("mode 120,35");
    menu();
    return 0;
}

void menu(){
    int op=0;
    char vd=219;
    do
    {   
        textcolor(LIGHTRED);	
        for(int j=10; j<109; j++){
            gotoxy(j,5);cout<<vd;
            gotoxy(j,29);cout<<vd;
        }
        textcolor(WHITE);
        for(int k=5; k<30; k++){
            gotoxy(9, k);cout<<vd;
            gotoxy(109, k);cout<<vd;
        }
        gotoxy(43, 23);
        switch (op)
        {
            case 1: break;
            case 2: break;
            case 3: break;
            case 4: break;
            
        }
    } while (op==0);
}
