#include "eq.h"
struct OGG{
	char nome[50];
	char tipo[50];
	struct {
		int hp;
		int mp;
		int atk;
		int def;
		int mag;
		int spr;
	}stat;
};
struct WRVETOGG{
	struct OGG *VetOgg;
	int dim;
}WR_VetOgg;

void EQ_FileRead(FILE* FEq){
	int NRig=-1;
	fscanf(FEq,"%d",&NRig);
    //free at line
	WR_VetOgg.VetOgg=malloc(NRig*sizeof(struct OGG));
	WR_VetOgg.dim=NRig;
	for(int i=0;i<NRig;i++){
		fscanf(FEq,"%s %s %d %d %d %d %d %d ",WR_VetOgg.VetOgg[i].nome,WR_VetOgg.VetOgg[i].tipo,&(WR_VetOgg.VetOgg[i].stat.hp),&(WR_VetOgg.VetOgg[i].stat.mp),&(WR_VetOgg.VetOgg[i].stat.atk),&(WR_VetOgg.VetOgg[i].stat.def),&(WR_VetOgg.VetOgg[i].stat.mag),&(WR_VetOgg.VetOgg[i].stat.spr));
	}
}

void EQ_GetName(ogg POgg,char* nome){
	if(NULL==POgg){
		nome[0]='\0';
	}
	else{
		strcpy(nome,POgg->nome);
	}
	return;	return;
}

ogg EQ_Find(char* nome){
	for(int i=0;i<WR_VetOgg.dim;i++)
		if(strcmp(WR_VetOgg.VetOgg[i].nome,nome)==0)
			return &(WR_VetOgg.VetOgg[i]);
	return NULL;
}

void EQ_Print(char* name){
	ogg target=EQ_Find(name);
	if(target!=NULL){
		printf("==%s %15s==\n",target->nome,target->tipo);
		printf("%10sSTAT:\n","");
		printf("%10s HP:%d\n","",target->stat.hp);
		printf("%10s MP:%d\n","",target->stat.mp);
		printf("%10s ATK:%d\n","",target->stat.atk);
		printf("%10s DEF:%d\n","",target->stat.def);
		printf("%10s MAG:%d\n","",target->stat.mag);
		printf("%10s SPR:%d\n","",target->stat.spr);
	}
}
void EQ_Free(void){
    free(WR_VetOgg.VetOgg);
    return;
}
