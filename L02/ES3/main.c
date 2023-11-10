#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
void Svolgi_Operazione(T_TRATTA *V_Trat, int Num_Tratte, int scelta,int n_tratte);
int Conv_data(int anno, int mese, int gioro);
void Ordina (T_TRATTA** Vet_ord,int campo,int n_tratte);
void Converti(T_TRATTA* Corsa1,T_TRATTA* Corsa2,int campo,unsigned long long Vet_tmp[2]);
int  Cod_Operazione_Ordinamento(char Oper[]);
T_TRATTA*** ricerca_tratta(T_TRATTA** PuntIn,T_TRATTA** PuntFin,char target[],T_TRATTA*** VetPunt,int cont,int n_tratte);
int Leggi_File(T_TRATTA** vet_tratte,T_TRATTA**** punta_multi_ord,char *NomeFile);


int main(int argc, const char * argv[]) {
    T_TRATTA *Vet_Tratte, t,**VetPunt[2]={NULL,NULL},***PuntaMultiOrd; 
    int N_Tratte=0, Codice_Operazione = 0,Codice_Operazione2=-1,c=0,ContMulti=0,FlagMulti;
    FILE *Fout; 
    char operazione[20],tmp[10],stringTarg[15],PercorsoFileLettura[100];
	while(N_Tratte<=0){
		printf("===========================================================================================================\n");
		printf("inserire il nome file che si vuole aprire\n==>");
		scanf("%s",PercorsoFileLettura);
		N_Tratte=Leggi_File(&Vet_Tratte,&PuntaMultiOrd,PercorsoFileLettura);
		if(N_Tratte<0) printf("File non trovato\n");
	}
	Fout = fopen("stampa.txt","w");
	for (int i=0;i<5;i++){
		for (int j=0;j<N_Tratte;j++){
			(PuntaMultiOrd[i])[j]=&Vet_Tratte[j];
	}
}

    printf("Inserire 'stampa' se si vuole stampare qualcosa a video\nScrivere 'ordina' se si vogliono ordinare i dati\n ===>");
    scanf("%s",operazione);
    if(strcmp(operazione,"stampa")==0){
    while (Codice_Operazione != 6) {
        printf("===========================================================================================================\n");
        printf("inserire l'operazione che si vuole svolgere tra:\ndata\npartenza\ncapolinea\nritardo\nritardo_tot\nfine\n==>");
        scanf("%s", operazione);
	printf("===========================================================================================================\n");
        Codice_Operazione = Cod_Operazione(operazione);
        Svolgi_Operazione(Vet_Tratte,N_Tratte,Codice_Operazione,N_Tratte);
    	}
    }
	else if(strcmp(operazione,"ordina")==0){
	    while (Codice_Operazione2 != 0) {
		c=0;
		printf("===========================================================================================================\n");
		printf("inserire l'oridinamento che si vuole svolgere tra: \ndata\ntratta\n");
		printf("partenza\narrivo\nstampa\nricerca\nmultiord\ncambiofile\nfine\n==>");
		scanf("%s", operazione);
		printf("===========================================================================================================\n");
		Codice_Operazione2 = Cod_Operazione_Ordinamento(operazione);
		if(Codice_Operazione2==7){
			printf("Opzione Multi ordinamento attiva\n");
			printf("Da ora in poi tutti gli ordinamenti richiesti saranno salvati \n");
		printf("===========================================================================================================\n");
		printf("inserire l'oridinamento che si vuole svolgere tra: \ndata\ntratta\n");
		printf("partenza\narrivo\nstampa\nricerca\nmultiord\ncambiofile\nfine\n==>");
		scanf("%s", operazione);
		printf("===========================================================================================================\n");
		FlagMulti=1;
		Codice_Operazione2 = Cod_Operazione_Ordinamento(operazione);
		}
		if(Codice_Operazione2==5){
			printf("si vuole stampare a video o su file?\n");
			scanf("%s",tmp);
			for (int i=0;i<N_Tratte;i++){
				if(strcmp(tmp,"video")==0){
					printf("(Cod_trat = %s, Part = %s, Dest = %s,",Vet_Tratte[i].Cod_trat,Vet_Tratte[i].Part,Vet_Tratte[i].Dest); 
					printf("Data = %s, Ora Part = %s,",Vet_Tratte[i].Data,Vet_Tratte[i].Ora_Part); 
					printf("Ora Arrivo = %s, Rit = %d)\n",Vet_Tratte[i].Ora_Arri,Vet_Tratte[i].Rit);
				}
				else if(strcmp(tmp,"file")==0){
					fprintf(Fout,"(Cod_trat = %s, Part = %s, Dest = %s,",Vet_Tratte[i].Cod_trat,Vet_Tratte[i].Part,Vet_Tratte[i].Dest); 
					fprintf(Fout,"Data = %s, Ora Part = %s,",Vet_Tratte[i].Data,Vet_Tratte[i].Ora_Part); 
					fprintf(Fout,"Ora Arrivo = %s, Rit = %d)\n",Vet_Tratte[i].Ora_Arri,Vet_Tratte[i].Rit);
				}
			}
		}
		else if(Codice_Operazione2==6){
			Ordina(PuntaMultiOrd[ContMulti],2,N_Tratte);
			VetPunt[0]=NULL;VetPunt[1]=NULL;
			for(int i=0;i<15;i++){
				stringTarg[i]='\0';
			}
			printf("inserire la stringa di recerca:\n==>");
			scanf("%s",stringTarg);
			ricerca_tratta(PuntaMultiOrd[ContMulti],&(PuntaMultiOrd[ContMulti])[N_Tratte-1],stringTarg,VetPunt,0,N_Tratte);
			while(VetPunt[0]+c<=VetPunt[1]&&*(VetPunt)!=NULL){
				printf("(Cod_trat = %s, Part = %s,",(*(VetPunt[0]+c))->Cod_trat,(*(VetPunt[0]+c))->Part);
				printf("Dest = %s",(*(VetPunt[0]+c))->Dest);
				printf(" Data = %s, Ora Part = %s,", (*(VetPunt[0]+c))->Data,(*(VetPunt[0]+c))->Ora_Part);
				printf("Ora Arrivo = %s, Rit = %d)\n",(*(VetPunt[0]+c))->Ora_Arri,(*(VetPunt[0]+c))->Rit);
				c++;
			}
		}
		else if(Codice_Operazione2==8){
			N_Tratte=0;
			while(N_Tratte<=0){
				printf("inserire il nome file che si vuole aprire\n==>");
				scanf("%s",PercorsoFileLettura);
				N_Tratte=Leggi_File(&Vet_Tratte,&PuntaMultiOrd,PercorsoFileLettura);
				if(N_Tratte<0)
					printf("File non trovato\n");	
			}
		}
		else Ordina (PuntaMultiOrd[ContMulti],Codice_Operazione2,N_Tratte);
		if(FlagMulti==1){
			if(ContMulti>=4){
				printf("Numero massimo di ordinameti in paralleto (5) è stato ragiunto\n");
				printf("L'ultimo ordimento è stato sovrascritto dal corrente\n");
			}
			else ContMulti++;
		}
		
		if(Codice_Operazione2!=0) printf("Operazione avvenuta con sucesso\n");
	    }
	}
	fclose(Fout);
	free(Vet_Tratte);
	for(int i=0;i<5;i++)
		free(PuntaMultiOrd[i]);
	free(PuntaMultiOrd);
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
    else if(strcmp(Oper, "multiord")==0) return 7;
    else if(strcmp(Oper, "cambiofile")==0) return 8;
    else if(strcmp(Oper, "fine")==0) return 0;
    else{ printf("errore operazione non riconosciuta\n"); return -1;}
}
int Conv_data(int anno,int mese,int giorno){
    int Data=0;
    Data = anno*10000+mese*100+giorno;
	    return Data;
}



void Svolgi_Operazione(T_TRATTA *V_Trat, int Num_Tratte, int scelta, int n_tratte){
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
void Ordina (T_TRATTA** Vet_ord,int campo,int n_tratte){
	T_TRATTA *tmp;
	unsigned long long Vet_tmp[2];
	for(int i=0;i<n_tratte;i++){
		for (int j=1;j<n_tratte-i;j++){
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
	while(str1[i]==str2[i]){
		i++;
		if((int)(str1[i])<95&&str1[i]!='\0') str1[i]=str1[i]+32;
		if((int)(str2[i])<95&&str2[i]!='\0') str2[i]=str2[i]+32;
		if(str1[i]=='\0'||str2[i]=='\0') return i;
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
//si assume che la funzione ricerca posse essere chiamata pure se i dati non sono già odinati
//cioè il main riordini i dati sempre prima di chiamare la funzione.
T_TRATTA*** ricerca_tratta(T_TRATTA** PuntIn,T_TRATTA** PuntFin,char target[],T_TRATTA*** VetPunt,int cont,int n_tratte){
	cont++;
	int i=0,retVal;	
	T_TRATTA** Punt=PuntIn+(n_tratte/(2*cont));
	retVal=ComparaStringhe((*Punt)->Part,target);
	if(retVal==strlen(target)){
		while(Punt-(i+1)>PuntIn&&ComparaStringhe((*(Punt-(i+1)))->Part,target)==strlen(target)){
			i++;
		}
		VetPunt[0]=Punt-i;
		i=0;
		while(Punt+(i+1)<PuntFin&&ComparaStringhe((*(Punt+(i+1)))->Part,target)==strlen(target)){
			i++;
		}
		VetPunt[1]=Punt+i;
		return VetPunt;
	}
	if(Punt==PuntIn||Punt==PuntFin) return VetPunt;
	if((int)((*Punt)->Part)[retVal]<(int)target[retVal])
		return ricerca_tratta(Punt,PuntFin,target,VetPunt,cont,n_tratte);
	if((int)((*Punt)->Part)[retVal]>(int)target[retVal])
		return ricerca_tratta(PuntIn,Punt,target,VetPunt,cont,n_tratte);
}

int Leggi_File(T_TRATTA** p_vet_tratte,T_TRATTA**** punta_multi_ord,char *NomeFile){
	FILE* Fin=NULL;
	int n_tratte=0;
	T_TRATTA t,***PuntaMultiOrd;
	Fin=fopen(NomeFile,"r");
	if(Fin==NULL) 
		return -1;
	fscanf(Fin, "%d",&n_tratte);
	//free wich clear any previous allocation of p_vet_tratte
	if(p_vet_tratte == NULL) free(p_vet_tratte);
	//dynaminc allocation of p_vet_tratte free at line: 110
	*p_vet_tratte = (T_TRATTA*)malloc(n_tratte*sizeof(T_TRATTA));
	//Dynamic allocation of punta_multi_ord free at line: 113
	*punta_multi_ord = (T_TRATTA***)malloc(5*sizeof(T_TRATTA**));
	for(int i=0;i<n_tratte;i++){
		fscanf(Fin, "%s %s %s %s %s %s %d ",t.Cod_trat,t.Part, t.Dest,t.Data,t.Ora_Part, t.Ora_Arri,&t.Rit);
		(*p_vet_tratte)[i] = t;
	}
	for(int i=0;i<5;i++)
		//dynamic allocatoon of multiple vetctor of T_TRATTA* variable free at line: 112
		(*punta_multi_ord)[i]=(T_TRATTA**)malloc(n_tratte*sizeof(T_TRATTA*));
	fclose(Fin);
	return n_tratte;
}
