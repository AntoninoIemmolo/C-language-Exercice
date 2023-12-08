#include <stdio.h>
#define _STDIO
#include <stdlib.h>
#define _STDLIB 
#include "pg.h"

int main(){
	FILE* FPg=fopen("../input files-6/E3/pg.txt","r");
	FILE* FInv=fopen("../input files-6/E3/inventario.txt","r");
	int scelta=1,hp,mg,atk,def,mag,spr;
	char chiave[50], chiave2[50],codice[7],nom1[50],nom2[50];
	if(NULL==FPg||NULL==FInv)
		return -1;
	PG_FileRead(FPg);
	EQ_FileRead(FInv);
        while(scelta!=0){
        printf("\nOperazioni:\n");
        printf("1) stampa\n2) modifica equipaggiameti\n");
        printf("3) inserimeto/cancellazione di un personaggio\n==>");
        scanf("%d",&scelta);
        switch(scelta){
            //caso 1 stampa 
            case(1):
                printf("insire una chiave di ricerca dell'elemnto da stampare\n==>");
                scanf("%s",chiave);
                if(chiave[0]=='P'&&chiave[1]=='G')
                    PG_Print(chiave);
                else
                    EQ_Print(chiave);
                break;
            //caso 2 modifica equip.
            case(2):
                printf("insire il codice del personaggio al quale si vuole ");
                printf("modificare l equipaggiomento\n==>");
                scanf("%s",chiave);
                printf("insire il nome dell'arma che si vuole aggiugere al personaggio %s\n==>",chiave);
                scanf("%s",chiave2);
                printf("si vuole aggiungere o eliminare l'arma selezionata?\n");
                printf("1) aggiungere\n2) elinimare\n==>");
                scanf("%d",&scelta);
                if(1==scelta)
                    PG_InvIns(chiave,chiave2);
                else if(2==scelta)
                    PG_InvPop(chiave,chiave2);
                break;
            //caso 3 modifica personaggi. 
            case(3):                
                printf("si vuole aggiungere o eliminare il personaggio\n");
                printf("1) aggiungere\n2) elinimare\n==>");
                scanf("%d",&scelta);
                if(1==scelta){
                    printf("inserire le informazioni richieste\n");
                    printf("codice univoco personaggio\n==>");
                    scanf("%s",codice);
                    printf("nome1 personaggio\n==>");
                    scanf("%s",nom1);
                    printf("nome2 personaggio\n==>");
                    scanf("%s",nom2);
                    printf("HP\n==>");
                    scanf("%d",&hp);
                    printf("MG\n==>");
                    scanf("%d",&mg);
                    printf("ATK\n==>");
                    scanf("%d",&atk);
                    printf("DEF\n==>");
                    scanf("%d",&def);
                    printf("MAG\n==>");
                    scanf("%d",&mag);
                    printf("SPR\n==>");
                    scanf("%d",&spr);
                    PG_Ins(codice,nom1,nom2,hp,mg,atk,def,mag,spr);
                }
                else if(2==scelta){
                    printf("insire il codice del personaggio che si vuole ");
                    printf("eliminare\n==>");
                    scanf("%s",chiave);
                    PG_Pop(chiave);
                }
                break;
            default:
                scelta=0;
                break;
        }
    }
   PG_Free("\0");
   fclose(FPg);
   fclose(FInv);
	return 0;
}

