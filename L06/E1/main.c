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
int* ind_gen(int dim);
int calc_sol(int* vet_ind,int ind,int dim,int* sol);
int* wr_calc_sol(int* vet_ind,int dim);

int main (int argi,char* argv[]){
	FILE* Fin;
	int tmp,dim=-1;
	int* vetScelte=NULL;
	int* sol=NULL;
	//Opening od Fin close at line: 
	Fin=fopen("./att1.txt","r");
	fscanf(Fin,"%d ",&dim);
	//Dynamic allocation of v, free at line:
	vInter=malloc(dim*sizeof(*vInter));
	for(int i=0;i<dim;i++){
		fscanf(Fin,"%d %d ",&vInter[i].s,&vInter[i].f);
	}
	bubbleSort(dim);
	vetScelte=ind_gen(dim);
	sol=wr_calc_sol(vetScelte,dim);

	for(int i=0;i<dim;i++){
		if(sol[i]!=-1)
			printf("%d %d\n",vInter[i].s,vInter[i].f);
	}
	
	free(vInter);
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

int* ind_gen(int dim){
	int* vet_ind;
	int flag=0;
	//free at line:
	vet_ind=(int*)malloc(dim*sizeof(int));
	for(int i=0;i<dim;i++){
		flag=0;
		for(int j=0;j<i;j++){
			if(comp(i,j)){
				vet_ind[i]=j;
				flag=1;
			}
		}
		if(!flag)
			vet_ind[i]=-1;
	}
	return vet_ind;
}
//per ogni elemento prende il suo indice corrispondente e calcola la dimensione della soluzione associata
//ritorna la soluzione a valore massimo
int *wr_calc_sol(int* vet_ind,int dim){
	int* sol=malloc(dim*sizeof(int));
	int* sol_parz=malloc(dim*sizeof(int));
	int val=INT_MIN,val_parz;
	for(int i=0;i<dim;i++){
		sol_parz[i]=-1;
		sol[i]=-1;
	}
	for(int i=dim-1;i>=0;i--){
		val_parz=calc_sol(vet_ind,i,0,sol_parz);
		if(val<val_parz){
			val=val_parz;
			for(int j=0;j<dim;j++){
				sol[j]=sol_parz[j];
				sol_parz[j]=-1;
			}
		}
	}
	return sol;
}
int calc_sol(int* vet_ind,int ind,int dim,int* sol){
	if(-1==ind){
		return dim;
	}
	sol[ind]=ind;
	return dim+calc_sol(vet_ind,vet_ind[ind],dim=dim+(vInter[ind].f-vInter[ind].s),sol);
}	
