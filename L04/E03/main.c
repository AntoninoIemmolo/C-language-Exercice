#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PERCORSO "../input files/E3/easy_test_set.txt"
typedef struct{
	struct {
		int z;
		int s;
		int r;
		int t;
	}next;
	//0=z	1=r	2=t	3=s
	char CPietra;
}pietra;
typedef struct{
	char* conf;
	int dim;
	int pnt;
}collana;

void wrap_ricerca(int* disp);
void ricerca(int prof,collana *col,int *disp,pietra* vetPietre,collana *best,int prec);
void terminaz(collana *col,collana *best);

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

void wrap_ricerca(int* disp){
	collana col,*sol;
	pietra vetPietre[4];
	col.dim=0;
	col.pnt=-1;
	//dynamic allocation of col.conf free at line: 74
	col.conf=(char*)malloc((disp[0]+disp[1]+disp[2]+disp[3])*sizeof(char));
	//dynamic allocation of sol free at line: 76
	sol=(collana*)malloc(sizeof(collana));
	//dynamic allocation of best free at line: 75
	sol->conf=(char*)malloc((disp[0]+disp[1]+disp[2]+disp[3])*sizeof(char));
	vetPietre[0].CPietra='z';
		vetPietre[0].next.z=1;
		vetPietre[0].next.s=0;
		vetPietre[0].next.r=1;
		vetPietre[0].next.t=0;
	vetPietre[1].CPietra='r';
		vetPietre[1].next.z=0;
		vetPietre[1].next.s=1;
		vetPietre[1].next.r=0;
		vetPietre[1].next.t=1;
	vetPietre[2].CPietra='t';
		vetPietre[2].next.z=1;
		vetPietre[2].next.s=0;
		vetPietre[2].next.r=1;
		vetPietre[2].next.t=0;
	vetPietre[3].CPietra='s';
		vetPietre[3].next.z=0;
		vetPietre[3].next.s=1;
		vetPietre[3].next.r=0;
		vetPietre[3].next.t=1;
	ricerca(0,&col,disp,vetPietre,sol,-1);
	free(col.conf);
	free(sol->conf);
	free(sol);
	return;
}

void ricerca(int prof,collana *col,int *disp,pietra* vetPietre,collana *best,int prec){
	int flag=0;
	//terminazione
	
	//ricorsione
	//printf("%d ",prof);
	if(0==prof||vetPietre[prec].next.z){
		if(disp[0]>0){
			col->conf[col->dim++]=vetPietre[0].CPietra;
			flag=1;
			disp[0]--;
			ricerca(prof+1,col,disp,vetPietre,best,0);
			//backtrack
			col->dim--;
			disp[0]++;
		}
	}
	if(0==prof||vetPietre[prec].next.r){
		if(disp[1]>0){
			col->conf[col->dim++]=vetPietre[1].CPietra;
			flag=1;
			disp[1]--;
			ricerca(prof+1,col,disp,vetPietre,best,1);
			//backtrack
			col->dim--;
			disp[1]++;
		}
	}
	if(0==prof||vetPietre[prec].next.t){
		if(disp[2]>0){
			col->conf[col->dim++]=vetPietre[2].CPietra;
			flag=1;
			disp[2]--;
			ricerca(prof+1,col,disp,vetPietre,best,2);
			//backtrack
			col->dim--;
			disp[2]++;
		}
	}
	if(0==prof||vetPietre[prec].next.s){
		if(disp[3]>0){
			col->conf[col->dim++]=vetPietre[3].CPietra;
			flag=1;
			disp[3]--;
			ricerca(prof+1,col,disp,vetPietre,best,3);
			//backtrack
			col->dim--;
			disp[3]++;
		}
	}
	if(0==flag){
		terminaz(col, best);
		//printf("prof: %d rimasti: %d %d %d %d\n",prof,disp[0],disp[1],disp[2],disp[3]);
		return;
	}
}
void terminaz(collana *col,collana *best){
	if(best->dim>=col->dim){
		return ;
	}
	best->dim=col->dim;
	strcpy(best->conf,col->conf);
	printf("nuove best:%d trovato:   ",col->dim);
	for(int i=0;i<col->dim;i++){
		printf("%c ",col->conf[i]);
	}
	printf("\n");
	return;
}
