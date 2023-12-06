#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
struct INTER {
	int s;
	int f;
};

struct INTER *vInter;
void bubbleSort(int n){
    struct INTER tmp;
    int flag;
    for (int i = 0; i < n - 1; i++) {
        flag = 0;
        for (int j = 0; j < n-i-1; j++) {
            if (vInter[j].f > vInter[j+1].f) {
		tmp = vInter[j];
		vInter[j] = vInter[j+1];
		vInter[j+1] = tmp;
                flag=1;
            }
        }
        if (!flag)
            break;
    }
}

int* ind_gen(int len,int* PBest);
int calc_sol(int* vet_ind,int ind,int dim);

int main (int argi,char* argv[]){
	FILE* Fin;
	int tmp,dim=-1;
	int* vetScelte=NULL;
	int IndSol;
	//Opening od Fin close at line: 53
	Fin=fopen("./att1.txt","r");
	fscanf(Fin,"%d ",&dim);
	//Dynamic allocation of v, free at line: 51
	vInter=malloc(dim*sizeof(*vInter));
	for(int i=0;i<dim;i++){
		fscanf(Fin,"%d %d ",&vInter[i].s,&vInter[i].f);
	}
	bubbleSort(dim);
	vetScelte=ind_gen(dim,&IndSol);
	while(IndSol!=-1){
		printf("%d, %d",vInter[IndSol].s,vInter[IndSol].f);
		IndSol=vetScelte[IndSol];
		printf("||");
	}
	free(vInter);
	free(vetScelte);
	fclose(Fin);
	return 0;
}
int comp(int ind1,int ind2){
	if(vInter[ind1].s<vInter[ind2].f&&vInter[ind2].s<vInter[ind1].f){
		//0=NON compatibili
		return 0;
	}
	//1=compatibili
	return 1;
}

int* ind_gen(int len,int* PBest){
	int* vet_ind;
	int flag=0,dim=-1,LocBestDim=INT_MIN,BestDim=INT_MIN,tmp;
	//free at line: 52
	vet_ind=(int*)malloc(len*sizeof(int));
	for(int i=0;i<len;i++){
		flag=0;
		LocBestDim=INT_MIN;
		for(int j=0;j<i;j++){
			if(comp(i,j)){
				tmp=vet_ind[i];
				vet_ind[i]=j;
				dim=calc_sol(vet_ind,i,0);
				if(dim>LocBestDim)
					LocBestDim=dim;
				else
					vet_ind[i]=tmp;
				flag=1;
			}
		}
		if(LocBestDim>BestDim){
			BestDim=LocBestDim;
			*PBest=i;
		}
		if(!flag)
			vet_ind[i]=-1;
	}
	return vet_ind;
}

int calc_sol(int* vet_ind,int ind,int dim){
	if(-1==ind){
		return dim;
	}
	return calc_sol(vet_ind,vet_ind[ind],dim=dim+(vInter[ind].f-vInter[ind].s));
}	
