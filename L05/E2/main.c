#include <stdio.h>
#include <stdlib.h>
int dim;
typedef struct{
	struct {
		char color;
		int n;
	}rig;
	struct {
		char color;
		int n;
	}col;
	int swap;
}tessera;
typedef tessera** tMat;

struct WRBOARD{
	//puntatore a matrice di puntatori
	tMat* mat;
	int val;
};
struct WRBEST{
	//puntatore a matrice di puntatori
	tMat mat;
	int val;
};

int leggifile(FILE* fileTessere,FILE* fileScac,tessera** vetTessere,int* dimR,int* dimC,int **vetScelte);
void gen_sol(int profR,int profC,int nTessere,int dimR,int dimC,tessera* vetTessere,int* vetScelte);
void calc_sol(int dimR,int dimC);
void eval_sol(void);
struct WRBOARD WrBoard;
struct WRBEST WrBest;
void stampa_mat(int dimR,int dimC);

int main(void){
	int dimR,dimC,nTessere;
	tessera	*vetTessere;
	FILE* fileTessere,*fileScac;
	int *vetScelte;
	nTessere=leggifile(fileTessere,fileScac,&vetTessere,&dimR,&dimC,&vetScelte);
	if(nTessere==-1) return -1;
	gen_sol(0,0,nTessere,dimR,dimC,vetTessere,vetScelte);
	stampa_mat(dimR,dimC);
	free(vetTessere);
	free(vetScelte);
	for(int i=0;i<dimR;i++){
		free(WrBoard.mat[i]);
		free(WrBest.mat[i]);
	}
	free(WrBoard.mat);
	free(WrBest.mat);
	return 0;
}


int leggifile(FILE* fileTessere,FILE* fileScac,tessera** vetTessere,int* dimR,int* dimC,int **vetScelte){
	int t=-1,s=-1,ind=-1;
	fileTessere=fopen("./tiles.txt","r");
	fileScac=fopen("./board.txt","r");
	if(fileScac==NULL||fileTessere==NULL) return -1;
	//free ar line 45 
	*vetTessere=(tessera*)malloc(9*sizeof(tessera));
	fscanf(fileTessere,"%d ",&t);
	//free ar line 46 
	*vetScelte=(int*)malloc(t*sizeof(int));
	//lettura di tutte le tessere
	for(int i=0;i<t;i++){
		fscanf(fileTessere,"%c ",&(((*vetTessere)[i]).rig.color));
		fscanf(fileTessere,"%d ",&((*vetTessere)[i].rig.n));
		fscanf(fileTessere,"%c ",&((*vetTessere)[i].col.color));
		fscanf(fileTessere,"%d ",&((*vetTessere)[i].col.n));
		(*vetTessere)[i].swap=0;
		(*vetScelte)[i]=1;
	}
	//leggo la board
	fscanf(fileScac,"%d %d ",dimR,dimC);
	//free at line 51 
	(WrBoard.mat)=(tessera***)malloc((*dimR)*sizeof(tessera**));
	for(int i=0;i<*dimR;i++){
		//free ar line 48
		WrBoard.mat[i]=(tessera**)malloc((*dimC)*sizeof(tessera*));
	}
	for(int i=0;i<*dimR;i++){
		for(int j=0;j<*dimC;j++){
			fscanf(fileScac,"%d/%d ",&ind,&s);
			if(ind==-1) WrBoard.mat[i][j]=NULL;
			else{
				WrBoard.mat[i][j]=&((*vetTessere)[ind]);
				(*vetScelte)[ind]=0;
				(*vetTessere)[ind].swap=s;
			}
		}
	}
	//free ar line 51
	WrBest.mat=(tMat)malloc((*dimR)*sizeof(*WrBest.mat));
	for(int i=0;i<*dimR;i++){
		//free ar line 49 
		WrBest.mat[i]=(tessera*)malloc((*dimC)*sizeof(**WrBest.mat));
	}
	
	WrBest.val=-1;
	return t;
}
void gen_sol(int profR,int profC,int nTessere,int dimR,int dimC,tessera* vetTessere,int* vetScelte){
	int tmp=profC;
	if(profR>=2&&profC>=3){
		calc_sol(dimR,dimC);
		return;
	}
	if(profC>=3){
		profR++;
		profC=0;
	}
	//tratto la matrice con un vettore contiguo
	if(WrBoard.mat[profR][profC]==NULL){
		//ciclo le tessere ancora disponibili
		for(int i=0;i<nTessere;i++){
			if(vetScelte[i]==1){
				vetScelte[i]=0;
				vetTessere[i].swap=1;
				WrBoard.mat[profR][profC]=&(vetTessere[i]);
				gen_sol(profR,profC+1,nTessere,dimR,dimC,vetTessere,vetScelte);
				vetTessere[i].swap=0;
				WrBoard.mat[profR][profC]=&(vetTessere[i]);
				gen_sol(profR,profC+1,nTessere,dimR,dimC,vetTessere,vetScelte);
				vetScelte[i]=1;
			}
		}
		WrBoard.mat[profR][profC]=NULL;
	}
	else{
		gen_sol(profR,profC+1,nTessere,dimR,dimC,vetTessere,vetScelte);
	}
		return;
}

void calc_sol(int dimR,int dimC){
	char cR,cC;
	int punti=-1,puntiT=0;
	int flag=0, j=0, i=0;
	tMat* board=WrBoard.mat;
	for(i=0;i<dimR;i++){
		if((board[i][0])->swap) cR=board[i][0]->col.color;
		else cR=board[i][0]->rig.color;
		flag=1;
		punti=0;
		for(j=0;j<dimC && flag;j++){
			if(board[i][j]->swap){
				if(board[i][j]->col.color!=cR){
					flag=0;
					punti=0;
				}
				else{
					punti=punti+board[i][j]->col.n;
				}
			}
			else{
				if(board[i][j]->rig.color!=cR){
					flag=0;
					punti=0;
				}
				else{
					punti=punti+board[i][j]->rig.n;
				}
			}
		}
		puntiT=puntiT+punti;
	}
	for(j=0;j<dimC;j++){
		if((board[0][j])->swap) cC=board[0][j]->rig.color;
		else cC=board[0][j]->col.color;
		flag=1;
		punti=0;
		for(i=0;i<dimR && flag;i++){
			if(board[i][j]->swap){
				if(board[i][j]->rig.color!=cC){
					flag=0;
					punti=0;
				}
				else{
					punti=punti+board[i][j]->rig.n;
				}
			}
			else{
				if(board[i][j]->col.color!=cC){
					flag=0;
					punti=0;
				}
				else{
					punti=punti+board[i][j]->col.n;
				}
			}
		}
		puntiT=puntiT+punti;
	}
	WrBoard.val=puntiT;
	eval_sol();
	return;
}
void eval_sol(void){
	if(WrBoard.val>WrBest.val){
		WrBest.val = WrBoard.val;
		for(int l=0;l<3;l++){
			for(int k=0;k<3;k++)
				WrBest.mat[l][k]=*(WrBoard.mat[l][k]);
		}
	}
	return ;
}
void stampa_mat(int dimR,int dimC){	
	printf("Punteggio massimo: %d\n\n", WrBest.val);
	printf("---------------------------\n");
	for(int i = 0; i < dimR; i++) {
		for (int j = 0; j < dimC; j++) {
			if(WrBest.mat[i][j].swap)
				printf("|%4c   |", WrBest.mat[i][j].rig.color);
			else
				printf("|%4c   |", WrBest.mat[i][j].col.color);
		}
		printf("\n");
		for (int j = 0; j < dimC; j++) {
			if(WrBest.mat[i][j].swap)
				printf("| %c %d %d |", WrBest.mat[i][j].col.color,WrBest.mat[i][j].swap,WrBest.mat[i][j].col.n);
			else
				printf("| %c %d %d |", WrBest.mat[i][j].rig.color,WrBest.mat[i][j].swap,WrBest.mat[i][j].rig.n);
		}
		printf("\n");
		for (int j = 0; j < dimC; j++) {
			if(WrBest.mat[i][j].swap)
				printf("|%4d   |",WrBest.mat[i][j].rig.n);
			else
				printf("|%4d   |",WrBest.mat[i][j].col.n);
		}
		printf("\n---------------------------\n");
	    }
}
