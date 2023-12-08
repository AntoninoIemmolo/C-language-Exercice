#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PERCORSO "./easy_test_set.txt"

//struttura collana contenente la configurazion della collana e la dimensione della stessa
typedef struct{
	char* conf;
	int dim;
}collana;

void wrap_ricerca(int* disp);
int ricerca(int prof,collana *col,int *disp,int** matPietre,collana *best,int prec,int target);
void terminaz(collana *col,collana *best);

//genero il file out.txt solo per confrontare la soluzione generata con i risultati attesi usando un programma esterno
int main(void){
	FILE* fin=fopen(PERCORSO,"r");
	int NRighe=-1;
	int Disp[4];
	if(NULL==fin)
		return -1;
	fscanf(fin,"%d ",&NRighe);
	for(int i=0;i<NRighe;i++){
		printf("======TEST:%d=======\n",i+1);
		fscanf(fin,"%d %d %d %d ",&Disp[0],&Disp[1],&Disp[2],&Disp[3]);
		printf("Z:%d R:%d T:%d S:%d \n",Disp[0],Disp[1],Disp[2],Disp[3]);
		wrap_ricerca(Disp);
		printf("===================\n");
	}
	fclose(fin);
	return 0;
}
//inizializza tutte le strutture necessaria per la corretta generazione della solizione
void wrap_ricerca(int* disp){
	collana col,*sol;
	int **matPietre;
	col.dim=0;
	int dimMax=disp[0]+disp[1]+disp[2]+disp[3];
	//dynamic allocation of col.conf free at line: 74
	col.conf=(char*)malloc(dimMax*sizeof(char));
	//dynamic allocation of sol free at line: 76
	sol=(collana*)malloc(sizeof(collana));
	//dynamic allocation of sol->conf free at line: 75
	sol->conf=(char*)malloc(dimMax*sizeof(char));
	sol->dim=0;
	matPietre=(int**)malloc(4*sizeof(int*));
	for(int i=0;i<4;i++){
		matPietre[i]=(int*)calloc(4,sizeof(int));
	}
	//corrispondenza indici di disp con le pietre 
	//0=>z	1=>r	2=>t	3=>s
	
	//rub
	matPietre[0][0]=1;
	matPietre[0][1]=1;
	//tub
	matPietre[1][3]=1;
	matPietre[1][2]=1;
	//top
	matPietre[2][0]=1;
	matPietre[2][1]=1;
	//smer
	matPietre[3][3]=1;
	matPietre[3][2]=1;

	//generazione delle regole per ogni regola 
	for(int i=1;i<=dimMax;i++){
		if(ricerca(0,&col,disp,matPietre,sol,-1,i)==0)
			break;

	}
	printf("SOLUZIONE MIGLIORE:\nDIM: %d\n",sol->dim);
	for(int i=0;i<sol->dim;i++){
		printf("%c ",sol->conf[i]);
	}
	printf("\n");
	free(col.conf);
	free(sol->conf);
	free(sol);
	return;
}
//la funzione ritorna 1 se ha generato la collan di dimensione target altrimenti ritorna 0
//se la funzione ritorna 1 ritorna subito al programma chiamante, altrimenti continua la ricerca 
//di soluzione di dimensione maggiore a quella generata
int ricerca(int prof,collana *col,int *disp,int** matPietre,collana *best,int prec,int target){
	//corrispondenza indici di disp con le pietre 
	//0=>z	1=>r	2=>t	3=>s
	int flag=0;
	if(prof>=target){
		terminaz(col, best);
		return 1;
	}
	for (int i=0;i<4;i++){
		if(prof==0||matPietre[prec][i]){
			if(prof==0||disp[i]>0){
				flag=1;
				col->conf[col->dim++]=(char)((char)'0'+i);
				disp[i]--;
				if(ricerca(prof+1,col,disp,matPietre,best,i,target)==1){
					col->dim--;
					disp[i]++;
					return 1;
				}
				col->dim--;
				disp[i]++;
			}
		}
	}
	return 0;
}
//confronta ed eventualmente sostituisce i dati della migliore soluzion fino ad ora generata 
//con i dati della collana appena generata
void terminaz(collana *col,collana *best){
	//in caso di parità di dimensione si mantiene come migliore la prima generata in ordina temporale 
	if(best->dim>=col->dim){
		return;
	}
	best->dim=col->dim;
	strcpy(best->conf,col->conf);
	return;
}
