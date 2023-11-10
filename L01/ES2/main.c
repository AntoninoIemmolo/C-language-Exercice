//
//  main.c
//  LAB6_Esercizio1
//
//  Created by antonino iemmolo on 09/05/23.
//

#include <stdio.h>
#include <string.h>

typedef struct {
    char Cod_trat[30];
    char Part[30];
    char Dest[30];
    char Data[30];
    char Ora_Part[30];
    char Ora_Arri[30];
    int Rit;
}T_TRATTA;
int Cod_Operazione(char Oper[10]);
void Svolgi_Operazione(T_TRATTA V_Trat[1000], int Num_Tratte, int scelta);
int Conv_data(int anno, int mese, int gioro);



int main(int argc, const char * argv[]) {
    T_TRATTA Vet_Tratte[1000], t;
    
    int N_Tratte=0, Codice_Operazione = 0;
    FILE* Fin;
    char operazione[20];
    Fin = fopen("log.txt", "r");
    if(Fin==NULL) return -1;
    fscanf(Fin, "%d",&N_Tratte);

    for(int i=0;i<N_Tratte;i++){
        fscanf(Fin, "%s %s %s %s %s %s %d",t.Cod_trat,t.Part, t.Dest,t.Data,t.Ora_Part, t.Ora_Arri,&t.Rit);
        Vet_Tratte[i] = t;
    }
    while (Codice_Operazione != 6) {
        printf("inserire l'operazione che si vuole svolgere:");
        scanf("%s", operazione);
        Codice_Operazione = Cod_Operazione(operazione);
        Svolgi_Operazione(Vet_Tratte,N_Tratte,Codice_Operazione);
    }
    return 0;
}

int  Cod_Operazione(char Oper[]){
    if(strcmp(Oper, "data")==0) return 1;
    else if(strcmp(Oper, "partenza")==0) return 2;
    else if(strcmp(Oper, "capolinea")==0) return 3;
    else if(strcmp(Oper, "ritardo")==0) return 4;
    else if(strcmp(Oper, "ritardo_tot")==0) return 5;
    else if(strcmp(Oper, "fine")==0) return 6;
    else{ printf("errore operazione non riconosciuta\n"); return 0;}
}

int Conv_data(int anno, int mese, int giorno){
    int Data=0;
    Data = anno*10000+mese*100+giorno;
    return Data;
}



void Svolgi_Operazione(T_TRATTA V_Trat[], int Num_Tratte, int scelta){
    int anno=0,mese=0,giorno=0,DataI=0, DataF=0,tmp[3],Data=0, Ritardo = 0;
    char Partenza[20], Destinazione[20],C_Trat[30];
    switch (scelta) {

        case 1:
            printf("\ninserire le date nel formato giorno/mese/anno: ");
            printf("\n1) ");
            scanf("%d/%d/%d",&giorno,&mese,&anno);
            DataI = Conv_data(anno, mese, giorno);
            printf("\n2) ");
	    scanf("%d/%d/%d",&giorno,&mese,&anno);
            DataF = Conv_data(anno, mese, giorno);
            for (int i=0;i<Num_Tratte;i++){
                sscanf(V_Trat[i].Data, "%d/%d/%d",&tmp[0],&tmp[1],&tmp[2]);
                Data = Conv_data(tmp[0],tmp[1],tmp[2]);
                if(Data<=DataF && Data >=DataI ){
                    printf("%s\n", V_Trat[i].Cod_trat);
                }
            }
            
            break;
        case 2:
            printf("inserire la partenza di interesse:\n");
            scanf("%s", Partenza);
            for (int i=0;i<Num_Tratte;i++){
                if(strcmp(V_Trat[i].Part,Partenza)==0) printf("%s è partito da %s\n",V_Trat[i].Cod_trat, Partenza);
            }
            break;
        case 3:
            printf("inserire la destinazione di interesse:\n");
            scanf("%s", Destinazione);
            for (int i=0;i<Num_Tratte;i++){
                if(strcmp(V_Trat[i].Dest,Destinazione)==0) printf("%s è partito da %s\n",V_Trat[i].Cod_trat, Destinazione);
            }
            break;
        case 4:
            printf("\ninserire le date nel formato giorno/mese/anno: ");
            printf("\n1) ");
            scanf("%d/%d/%d",&anno,&mese,&giorno);
            DataI = Conv_data(anno, mese, giorno);
            printf("\n2) ");
            scanf("%d/%d/%d",&anno,&mese,&giorno);
            DataF = Conv_data(anno, mese, giorno);
            for (int i=0;i<Num_Tratte;i++){
                if(V_Trat[i].Rit==0) break;
                sscanf(V_Trat[i].Data, "%d/%d/%d",&tmp[0],&tmp[1],&tmp[2]);
                Data = Conv_data(tmp[0],tmp[1],tmp[2]);
                if(Data<=DataF && Data >=DataI){
                    printf("%s\n", V_Trat[i].Cod_trat);
                }
            }
            break;
            
        case 5:
            printf("Inserire il codice tratta: ");
            scanf("%s",C_Trat);
            for (int i=0; i<Num_Tratte; i++) {
                if(strcmp(V_Trat[i].Cod_trat, C_Trat) == 0 ){
                    Ritardo = Ritardo + V_Trat[i].Rit;
                }
            }
            printf("Il ritardo accumulato dalla tratta %s è: %d\n",C_Trat, Ritardo);

                break;
        case 6:
                printf("Grazie e arrivedereci\n");
                break;

        }
    }
