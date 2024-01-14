#include "Gr.h"
#ifndef stdio
#define stdio
#include <stdio.h>
#endif
#ifndef stdlib 
#define stdlib 
#include <stdlib.h>
#endif
#ifndef string 
#define string 
#include <string.h>
#endif
int Act_Sel(void);

int main(int argc,char* argv[]){
    Graph gr=GR_init(30);
    int Act_Code;
    char str1[30],str2[30],str3[30];
    printf("Inserire -verifica- per verificare se 3 vertici sono adiacenti\n");
    printf("Inserire -stampa- per stampare tutte le informazioni\n");
    printf("Inserire -genera- per genrare la lista delle adiacenze\n");
    printf("==> ");
    Act_Code=Act_Sel();
    GR_Load(gr,"../input files/E2/grafo.txt"/*argv[1]*/,1);
    while(Act_Code){
        switch(Act_Code){
            case 1:
                printf("inserire primo vertice\n==> ");
                scanf("%s",str1);
                printf("inserire secondo vertice\n==> ");
                scanf("%s",str2);
                printf("inserire terzo vertice\n==> ");
                scanf("%s",str3);
                if(GR_Ad_Ver(gr,str1,str2,str3))
                    printf("\n==sono adiacenti==\n");
                else 
                    printf("\n==non sono adiacenti==\n");
                break;
            case 2:
                GR_Print_All_ord(gr);
                break;
            case 3:
                GR_Gen_List(gr);
                break;
            default:
                printf("operazione non riconosciuta\n");
                break;
        
        }
        printf("Inserire -verifica- per verificare se 3 vertici sono adiacenti\n");
        printf("Inserire -stampa- per stampare tutte le informazioni\n");
        printf("Inserire -genera- per genrare la lista delle adiacenze\n");
        printf("==> ");
        Act_Code=Act_Sel();
    }
    GR_free(gr);
    free(gr);
    return 0;
}

int Act_Sel(void){
    char str[30];
    scanf("%s",str);
    if(strcmp(str,"verifica")==0) return 1;
    else if(strcmp(str,"stampa")==0) return 2;
    else if(strcmp(str,"genera")==0) return 3;
    return 0;
}
