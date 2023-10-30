
//  main.c
//  LAB6_Esercizio1
//
//  Created by antonino iemmolo on 09/05/23.
//

#include <stdio.h>
#include <string.h>
#define MaxDati 10
typedef struct {
    char Cod_trat[7];
    char Part[15];
    char Dest[15];
    char Data[11];
    char Ora_Part[11];
    char Ora_Arri[11];
    int Rit;
}T_TRATTA;
int Cod_Operazione(char Oper[10]);
void Svolgi_Operazione(T_TRATTA V_Trat[MaxDati], int Num_Tratte, int scelta);
int Conv_data(int anno, int mese, int gioro);
void Ordina (T_TRATTA* V_Trat, T_TRATTA** Vet_ord,int campo);
void Converti(T_TRATTA* Corsa1,T_TRATTA* Corsa2,int campo,unsigned long long Vet_tmp[2]);
int  Cod_Operazione_Ordinamento(char Oper[]);


int main(int argc, const char * argv[]) {
    T_TRATTA Vet_Tratte[MaxDati]={0}, t,*Vet_ord[MaxDati]; 
    int N_Tratte=0, Codice_Operazione = 0,Codice_Operazione2=-1;
    FILE* Fin,*Fout;
    char operazione[20],tmp[10];
	Fout = fopen("stampa.txt","w");
    Fin = fopen("log.txt", "r");
    fscanf(Fin, "%d",&N_Tratte);

    for(int i=0;i<N_Tratte;i++){
        fscanf(Fin, "%s %s %s %s %s %s %d",t.Cod_trat,t.Part, t.Dest,t.Data,t.Ora_Part, t.Ora_Arri,&t.Rit);
        Vet_Tratte[i] = t;
    }
    while (Codice_Operazione != 6) {
        printf("inserire l'operazione che si vuole svolgere: ");
        scanf("%s", operazione);
        Codice_Operazione = Cod_Operazione(operazione);
        Svolgi_Operazione(Vet_Tratte,N_Tratte,Codice_Operazione);
    }
	for (int i=0;i<MaxDati;i++){
		Vet_ord[i]=&Vet_Tratte[i];
	}
    while (Codice_Operazione2 != 0) {
        printf("inserire l'oridinamento che si vuole svolgere: ");
        scanf("%s", operazione);
        Codice_Operazione2 = Cod_Operazione_Ordinamento(operazione);
	if(Codice_Operazione2==5){
		printf("si vuole stampare a video o su file?\n");
		scanf("%s",tmp);
		for (int i=0;i<MaxDati;i++){
			if(strcmp(tmp,"video")==0)
			printf("[%d] = (Cod_trat = %s, Part = %s, Dest = %s, Data = %s, Ora Part = %s, Ora Arrivo = %s, Rit = %d)\n",i,Vet_Tratte[i].Cod_trat,Vet_Tratte[i].Part,Vet_Tratte[i].Dest,Vet_Tratte[i].Data,Vet_Tratte[i].Ora_Part,Vet_Tratte[i].Ora_Arri,Vet_Tratte[i].Rit);
			else if(strcmp(tmp,"file")==0){
				fprintf(Fout,"[%d] = (Cod_trat = %s, Part = %s, Dest = %s, Data = %s, Ora Part = %s, Ora Arrivo = %s, Rit = %d)\n",i,Vet_Tratte[i].Cod_trat,Vet_Tratte[i].Part,Vet_Tratte[i].Dest,Vet_Tratte[i].Data,Vet_Tratte[i].Ora_Part,Vet_Tratte[i].Ora_Arri,Vet_Tratte[i].Rit);

			}
		}

	}
	else Ordina (Vet_Tratte,Vet_ord,Codice_Operazione2);

    }

	fclose(Fout); fclose(Fin);
    return 0;
}

int  Cod_Operazione(char Oper[]){
    if(strcmp(Oper, "data")==0) return 1;
    else if(strcmp(Oper, "partenza")==0) return 2;
    else if(strcmp(Oper, "capolinea")==0) return 3;
    else if(strcmp(Oper, "ritardo")==0) return 4;
    else if(strcmp(Oper, "ritardo_tot")==0) return 5;
    else if(strcmp(Oper, "fine")==0) return 6;
    else{ printf("errore operazione no nriconosciuta\n"); return 0;}
}
int  Cod_Operazione_Ordinamento(char Oper[]){
    if(strcmp(Oper, "data")==0) return 1;
    else if(strcmp(Oper, "tratta")==0) return 2;
    else if(strcmp(Oper, "partenza")==0) return 3;
    else if(strcmp(Oper, "arrivo")==0) return 4;
    else if(strcmp(Oper, "stampa")==0) return 5;
    else if(strcmp(Oper, "ricerca")==0) return 6;
    else if(strcmp(Oper, "fine")==0) return 0;
    else{ printf("errore operazione non riconosciuta\n"); return -1;}
}
int Conv_data(int anno,int mese,int giorno){
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
            scanf("%d/%d/%d",&anno,&mese,&giorno);
            DataI = Conv_data(anno, mese, giorno);
            printf("\n2) ");
            scanf("%d/%d/%d",&anno,&mese,&giorno);
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
                if(strcmp(V_Trat[i].Part,Partenza)==0) 
			printf("%s è partito da %s\n",V_Trat[i].Cod_trat, Partenza);
            }
            break;
        case 3:
            printf("inserire la destinazione di interesse:\n");
            scanf("%s", Destinazione);
            for (int i=0;i<Num_Tratte;i++){
                if(strcmp(V_Trat[i].Dest,Destinazione)==0)
			printf("%s è partito da %s\n",V_Trat[i].Cod_trat, Destinazione);
            }
            break;
        case 4:
            printf("\ninserire le date nel formato anno/mese/giorno: ");
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
void Ordina (T_TRATTA* V_Trat,T_TRATTA** Vet_ord,int campo){
	T_TRATTA *tmp;
	unsigned long long Vet_tmp[2];
	for(int i=0;i<MaxDati;i++){
		for (int j=1;j<MaxDati-i;j++){
			Converti(Vet_ord[j-1],Vet_ord[j],campo,Vet_tmp);
			if (Vet_tmp[0]>Vet_tmp[1]){
				tmp = Vet_ord[j];
				Vet_ord[j]=Vet_ord[j-1];
				Vet_ord[j-1]=tmp;
			}
		}
	}
}
//ritorna l'indece del primo carattere che differisce tra str1 e str2
int ComparaStringhe(char* string1,char* string2){
	int i=0;
	char str1[15],str2[15];
	strcpy(str1,string1);
	strcpy(str2,string2);
	if((int)(str1[i])<95&&str1[i]!='\0') str1[i]=str1[i]+32;
	if((int)(str2[i])<95&&str2[i]!='\0') str2[i]=str2[i]+32;
	while(str1[i]==str2[i]&&(str1[i]!='\0'&&str2[i]!='\0')){
		if((int)(str1[i+1])<95&&str1[i+1]!='\0') str1[i+1]=str1[i+1]+32;
		if((int)(str2[i+1])<95&&str2[i+1]!='\0') str2[i+1]=str2[i+1]+32;
		i++;
	}
	return i;
}
void Converti(T_TRATTA* corsa1,T_TRATTA* corsa2,int campo,unsigned long long Vet_tmp[2]){
	int Data_vet[3],indice;
	switch(campo){
		//Data+ora
		case(1):
			sscanf(corsa1->Data, "%d/%d/%d",&Data_vet[0],&Data_vet[1],&Data_vet[2]);
			Vet_tmp[0]=Conv_data(Data_vet[0],Data_vet[1],Data_vet[2]);
			sscanf(corsa1->Ora_Part, "%d:%d:%d",&Data_vet[0],&Data_vet[1],&Data_vet[2]);
			Vet_tmp[0]=Vet_tmp[0]*1000000+Conv_data(Data_vet[0],Data_vet[1],Data_vet[2]);
			sscanf(corsa2->Data, "%d/%d/%d",&Data_vet[0],&Data_vet[1],&Data_vet[2]);
			Vet_tmp[1]=Conv_data(Data_vet[0],Data_vet[1],Data_vet[2]);
			sscanf(corsa2->Ora_Part, "%d:%d:%d",&Data_vet[0],&Data_vet[1],&Data_vet[2]);
			Vet_tmp[1]=Vet_tmp[1]*1000000+Conv_data(Data_vet[0],Data_vet[1],Data_vet[2]);
			break;
		
		//Cod Tratta
		case(2):
			sscanf(corsa1->Cod_trat,"GTT%lld",&Vet_tmp[0]);
			sscanf(corsa2->Cod_trat,"GTT%lld",&Vet_tmp[1]);
			if(strcmp(corsa1->Cod_trat,"")==0) Vet_tmp[0]=0;
			if(strcmp(corsa2->Cod_trat,"")==0) Vet_tmp[1]=0;
			break;
		
		//ordine alfabetico Partenza
		case(3):
			indice = ComparaStringhe(corsa1->Part,corsa2->Part);
			Vet_tmp[0]=(int)(corsa1->Part[indice]);
			Vet_tmp[1]=(int)(corsa2->Part[indice]);
			break;
		
		case(4):
			indice = ComparaStringhe(corsa1->Dest,corsa2->Dest);
			Vet_tmp[0]=(int)(corsa1->Dest[indice]);
			Vet_tmp[1]=(int)(corsa2->Dest[indice]);
			break;
		
		case(0):
			break;
		

	}
}
