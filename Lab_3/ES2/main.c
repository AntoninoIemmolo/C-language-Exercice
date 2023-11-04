#include <stdio.h>
#include <stdlib.h>
#define MaxAmici 5
#define Maxlen 25

typedef struct {
	int NumScelte;
	char VetCan[MaxAmici][Maxlen];
}Amici;


void Crea_Playlist(Amici* VetAmici,int NumAmici,int ProfRic,int* tmp);
int main(int argn,char* argv[]){
	int num_amici;
	FILE* Fin;
	Amici vet_amici[MaxAmici];
	//File opening read only privilage 
	Fin=fopen("Brani.txt","r");
	if(Fin==NULL) return -1;
	fscanf(Fin,"%d ",&num_amici);
	for(int i=0;i<num_amici;i++){
		fscanf(Fin,"%d ",&vet_amici[i].NumScelte);
		for(int j=0;j<vet_amici[i].NumScelte;j++)
			fscanf(Fin,"%s ",(vet_amici[i]).VetCan[j]);
	}
	Crea_Playlist(vet_amici,num_amici,0,NULL);
	fclose(Fin);
	return 0;
}

void Crea_Playlist(Amici* VetAmici,int NumAmici,int ProfRic,int* tmp){
	if(ProfRic==0){
		//Dynamic allocation free at line 52
		tmp = (int*)malloc(NumAmici*sizeof(int));
	}
	if(tmp==NULL) printf("Malloc failed");
	//for cicle calls every ricursive iteretion 
	//it's ment to finish the cicle before return
	for(int i=0;i<VetAmici[ProfRic].NumScelte;i++){
		tmp[ProfRic]=i;
		if(ProfRic<NumAmici-1){
			Crea_Playlist(VetAmici,NumAmici,ProfRic+1,tmp);
		}
		else{ 
			tmp[ProfRic]=i;
			printf("=================================================\n");
			for(int j=0;j<NumAmici;j++)
				printf("%s\n",(VetAmici[j]).VetCan[tmp[j]]);
		}
	}
	if(ProfRic==0)
		free(tmp);
	return;
}









