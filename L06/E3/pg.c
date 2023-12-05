#include "pg.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct PG{
	char code[7];
	char nom1[50];
	char nom2[50];
	struct {
		int hp;
		int mp;
		int atk;
		int def;
		int mag;
		int spr;
	}stat;
	struct WR_equip *PWrEquip;
};
struct WR_equip{
	int InUse;
	struct OGG* VetInv[8];
};
typedef struct node {
	struct PG pg;
	struct node* next;
	struct node* prev;
}NODE,*HEAD;
HEAD head=NULL;

//crea e inserrisce in testa il nuova personaggi
NODE* PG_init(char* cod,char* nom1,char* nom2,int hp,int mp,int atk,int def,int mag,int spr);

void PG_Ins(char* cod,char* nom1,char* nom2,int hp,int mp,int atk,int def,int mag,int spr){
	NODE* PNewNode;
	NODE* tmp;
	PNewNode = PG_init(cod,nom1,nom2,hp,mp,atk,def,mag,spr);
	tmp=head;
	head=PNewNode;
	PNewNode->next=tmp;
	if(NULL!=PNewNode->next){
		PNewNode->next->prev=PNewNode;
	}

	/*for(NODE* link=head;link!=NULL;link=link->next){
		printf("nom1: %10s nom2:%10s\n",link->pg.nom1,link->pg.nom2);

	}
	printf("\n\n\n");*/
}

//L'appartenneza dei nodi è data alla lista
NODE* PG_init(char* cod,char* nom1,char* nom2,int hp,int mp,int atk,int def,int mag,int spr){
	NODE* NewNode=NULL;
	//dynamic allocation of NewNode, free at line: ##
	NewNode=(NODE*)malloc(sizeof(NODE));
	strcpy(NewNode->pg.code,cod);
	strcpy(NewNode->pg.nom1,nom1);
	strcpy(NewNode->pg.nom2,nom2);
	NewNode->pg.stat.hp=hp;
	NewNode->pg.stat.mp=mp;
	NewNode->pg.stat.atk=atk;
	NewNode->pg.stat.def=def;
	NewNode->pg.stat.mag=mag;
	NewNode->pg.stat.spr=spr;
	NewNode->next=NULL;
	NewNode->prev=NULL;
	NewNode->pg.PWrEquip=malloc(sizeof(struct WR_equip));
	NewNode->pg.PWrEquip->InUse=-1;
	for(int i=0;i<8;i++){
		NewNode->pg.PWrEquip->VetInv[i]=NULL;
	}
	return NewNode;
}
NODE* PG_Find(char* key){
	for(NODE* link=head;link!=NULL;link=link->next)
		if(strcmp(link->pg.code,key)==0)
			return link;
	return NULL;
}
NODE* PG_Pop(char* key){
	NODE* node;
	node=PG_Find(key);
	if(NULL==node->prev)
		head=node->next;
	else{
		node->next->prev=node->prev;
		node->prev->next=node->next;
	}
	/*for(NODE* link=head->next;link!=NULL;link=link->next){
		printf("curr: %10s prev:%10s\n",link->pg.nom1,link->prev->pg.nom1);

	}
	printf("\n\n\n");*/
	return node;
}
void PG_Print(char *key){
	NODE* node=NULL;
	node=PG_Find(key);
	char nome[50];
	printf("==%s==\n%s %15s\n",node->pg.code,node->pg.nom1,node->pg.nom2);
	printf("%10sSTAT:\n","");
	printf("%10s HP:%d\n","",node->pg.stat.hp);
	printf("%10s MP:%d\n","",node->pg.stat.mp);
	printf("%10s ATK:%d\n","",node->pg.stat.atk);
	printf("%10s DEF:%d\n","",node->pg.stat.def);
	printf("%10s MAG:%d\n","",node->pg.stat.mag);
	printf("%10s SPR:%d\n","",node->pg.stat.spr);
	for(int i=0;i<8;i++){
		printf("%10s","");
		EQ_GetName(node->pg.PWrEquip->VetInv[i],nome);
		EQ_Print(nome);

	}
}

void PG_FileRead(FILE* FPg){
	char cod[7],nom1[50],nom2[50];
	int hp=-1,mp=-1,atk=-1,def=-1,mag=-1,spr=-1;
	while(fscanf(FPg,"%s %s %s %d %d %d %d %d %d ",cod,nom1,nom2,&hp,&mp,&atk,&def,&mag,&spr)!=EOF){
		PG_Ins(cod,nom1,nom2,hp,mp,atk,def,mag,spr);
	}
}

void PG_InvIns(char *key,char* NomeOgg){
	int i=0;
	NODE* PNode=PG_Find(key);
	struct OGG *POgg=EQ_Find(NomeOgg);
	if(NULL==PNode||NULL==POgg){
		printf("FAIL");
		return;
	}
	for(;i<8&&NULL!=PNode->pg.PWrEquip->VetInv[i];i++){}
	if(8==i)
		printf("invetario pieno\n");
	else
		PNode->pg.PWrEquip->VetInv[i]=POgg;
}
void PG_InvPop(char *key,char* NomeOgg){
	int flag=1;
	NODE* PNode=PG_Find(key);
	struct OGG* POgg=EQ_Find(NomeOgg);
	for(int i=0;i<8&&flag;i++){
		if(PNode->pg.PWrEquip->VetInv[i]==POgg){
				flag=0;
				PNode->pg.PWrEquip->VetInv[i]=NULL;
		}
	}
}
