#include <stdio.h>
#include <stdlib.h>


void crea_mat(int ***PuntaMat,int NRighe,int Ncolonne);
void separa(int **PuntaMat, int nr, int nc,int **VetBianchi,int **VetNeri);

int main(int argc,char* argv[]){
	int righe,colonne,**p_mat=NULL,*vet_b,*vet_n;
	FILE *Fin;
	Fin=fopen("mat.txt","r");
	if(Fin==NULL) return -1;
	fscanf(Fin,"%d %d",&righe,&colonne);
	crea_mat(&p_mat,righe,colonne);
	for(int i=0;i<righe;i++){
		for(int j=0;j<colonne;j++) fscanf(Fin,"%d ",&p_mat[i][j]);
	}
	separa(p_mat,righe,colonne,&vet_b,&vet_n);
	return 0;
}

void crea_mat(int ***PuntaMat,int NRighe,int NColonne){
	*PuntaMat = (int **)malloc(NRighe*sizeof(int *));
	for(int i=0;i<NColonne;i++){
		(*PuntaMat)[i]=(int*)malloc(NColonne*sizeof(int));
	}
}
void separa(int **PuntaMat, int nr, int nc,int **VetBianchi,int **VetNeri){
	int cont1=0,cont2=0;
	*VetBianchi=malloc((((nc*nr))/2)*sizeof(int));
	*VetNeri=malloc(((nc*nr)-1/2)*sizeof(int));
	for(int i=0;i<nr;i++){
		for(int j=0;j<nc;j++){
			if((i+j)%2==0){
				(*VetBianchi)[cont1]=PuntaMat[i][j];
				cont1++;
			}
			else{
				(*VetNeri)[cont2]=PuntaMat[i][j];
				cont2++;
			}
		
		}
	}
}

