#include <stdio.h>
#include <stdlib.h>
typedef struct{
	int s;
	int f;
}att;


void Wrap_attSel(int N, att *v,int *dim);
int Calcola_Dim(int *VetS,int n,att* v);
int controlla_sol(int *VetS,int n,att* v);
void attSel(int prof,int N,att *v,int *VetS,int *dim,int* pSol);

int main (int argi,char* argv[]){
	FILE* Fin;
	att *v;
	int tmp,dim=-1;
	Fin=fopen("att.txt","r");
	fscanf(Fin,"%d ",&tmp);
	v=(att*)malloc(tmp*sizeof(att));
	for(int i=0;i<tmp;i++){
		fscanf(Fin,"%d %d ",&v[i].s,&v[i].f);
	}
	for(int i=0;i<tmp;i++){
		printf("(%d)(%d %d)    ",i,v[i].s, v[i].f);
	}
	printf("\n");
	Wrap_attSel(tmp,v,&dim);
	fclose(Fin);
	return dim;
}


void Wrap_attSel(int N, att *v,int *dim){
	int len=0;
	int VetS[N];
	int *pSol=NULL;
	for(int i=0;i<N;i++) VetS[i]=1;
	pSol=(int*)malloc(N*sizeof(int));
	attSel(0,N,v,VetS,dim,pSol);
	for(int i=0;i<N;i++){
		if(pSol[i]==0){
			printf("(%d,%d)",v[i].s,v[i].f);
		}
	}
	return;
}
void attSel(int prof,int N,att *v,int *VetS,int *dim,int* pSol){
	int nDim=-1;
	if(prof>=N){
		nDim=Calcola_Dim(VetS,prof,v);
		if(nDim>=*dim){
			*dim=nDim;
			for(int i=0;i<N;i++){
				pSol[i]=VetS[i];
			}
		}
		return;
	}
	if(controlla_sol(VetS,prof,v)==1){
		VetS[prof]=0;
		attSel(prof+1,N,v,VetS,dim,pSol);
	}
	VetS[prof]=1;
	attSel(prof+1,N,v,VetS,dim,pSol);
	return;
}
int controlla_sol(int *VetS,int n,att* v){
	if(n==0) return 1;
	for(int i=0;i<n;i++){
		if(VetS[i]==0){
			if(v[n].s<v[i].f&&v[i].s<v[n].f){
				return 0;
			}
		}
	}
	return 1;

}
int Calcola_Dim(int *VetS,int n,att* v){
	int dim=0;
	for(int i=0;i<n;i++){
		if(VetS[i]==0){
			dim=dim+(v[i].f-v[i].s);
		}
	}
	return dim;
}


