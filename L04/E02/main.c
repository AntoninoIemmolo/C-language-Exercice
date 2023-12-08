#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct s_item{
	char codice[7];
	char nome[50];
	char cognome[50];
	char data[11];
	char via[50];
	char città[50];
	char cap[6];
	int key;
	struct s_item* next;
}item,*link;

void File_Reader(char *file_path,link* head);
link Item_allocation(char* c_codie,char* c_nome,char* c_cognome,char* c_data,
		char* c_via,char* c_città,char* c_cap);
void Item_Ord_Insertion(link* head,link new_node);
int Conv_Data(char *c_data);
int Converti_Operazione(char* Operazione);
void Stdin_Reader(link *head);
link LISTSearch(link head,char *string);
link LISTPop(link *PHead,char* string);
link LISTPopDate(link* Head,char* data1,char* data2);
int min(int a,int b);
int max(int a,int b);

int main(int argv,char* argc[]){
	link Head=NULL,ris=NULL;
	link tmp=NULL;
	int code=1,flag=1;
	char FilePath[50]="./anag1.txt",string[50];
	char data1[11], data2[11];
	FILE* FOut;
	File_Reader(FilePath,&Head);
	while(code!=0){
		printf("\niserire l'operazione chi si vuole svolgere\nquit\nacquisizione\nricerca\ncancellazione\nstampa\n==>");
		scanf("%s",string);
		code=Converti_Operazione(string);
		switch(code){
			case(0):
				break;
			case(1):
				printf("inserie da dove si vuole acquisire i dati\nfile\ntastiera\n==>");
				scanf("%s",string);
				if(strcmp(string,"file")==0){
					scanf("%*c");
					printf("inserire il percorso del file\n==>");
					fgets (string, 100, stdin);
					for(int i=0;i<100&&flag;i++){
						if(string[i]=='\n'){
							string[i]='\0';
							flag=0;
						}
					}
					File_Reader(string,&Head);
				}
				if(strcmp(string,"tastiera")==0){
					Stdin_Reader(&Head);
				}
				break;
			case(2):
				printf("insersci il codice\n==>");
				scanf("%s",string);
				ris=LISTSearch(Head,string);
				if(ris!=NULL){
					printf("elemento trovato\n");
					printf("codice:%s nome: %s cognome: %s data di nasciata: %s via: %s ",ris->codice,ris->nome, 
							ris->cognome, ris->data, ris->via);
					printf("città: %s cap: %s \n",ris->città, ris->cap);
				}
				else
					printf("elemento non trovato");
				break;	
			case(3):
				printf("secondo quale parametro si vogliono cancellare gli elemeti\ncodide\ndate\n==>");
				scanf("%s",string);
				if(strcmp(string,"codice")==0){
					printf("inserire il codice dell'elento da cancellare\n==>");
					scanf("%s",string);
					ris=LISTPop(&Head,string);
					if(ris!=NULL){
						printf("elemento cancellato\n");
						printf("codice:%s nome: %s cognome: %s data di nasciata: %s via: %s ",ris->codice,
								ris->nome, ris->cognome, ris->data, ris->via);
						printf("città: %s cap: %s \n",ris->città, ris->cap);
					}
					else
						printf("elemento non trovato");
				}
				else if(strcmp(string,"date")==0){
					printf("inserire la prima data nel formato gg/mm/aaaa\n==>");
					scanf("%s",data1);
					printf("inserire la seconda data nel formato gg/mm/aaaa\n==>");
					scanf("%s",data2);
					ris=LISTPopDate(&Head,data1,data2);
					while(ris!=NULL){
						printf("elemento cancellato\n");
						printf("codice:%s nome: %s cognome: %s data di nasciata: %s via: %s ",ris->codice,
								ris->nome, ris->cognome, ris->data, ris->via);
						printf("città: %s cap: %s \n",ris->città, ris->cap);
						ris=LISTPopDate(&Head,data1,data2);
					}
				}
				break;
            //caso stampa
			case(4):
                FOut=fopen("./out.txt","w");
				for(link x=Head;x!=NULL;x=x->next){
					fprintf(FOut,"codice:%s nome: %s cognome: %s data di nasciata: %s via: %s ",x->codice,
								x->nome, x->cognome, x->data, x->via);
					fprintf(FOut,"città: %s cap: %s \n",x->città, x->cap);
				}
				break;
			default:
				break;
		}
	}
	fclose(FOut);
	return 0;
}
//Dato un percorso file in ingresso ritorna il puntatore al primo elemento della lista
//conprensiva dei nuovi e dei vecchi elimenti già ordinata
void File_Reader(char *file_path,link* head){
	FILE* Fin;
	Fin=fopen(file_path,"r");
	char codice[6],nome[50],cognome[50],data[11],via[50],città[50];
	char cap[7];
	link p_new_node;
	if(Fin==NULL) return ;
	while(fscanf(Fin,"%s %s %s %s %s %s %s",codice,nome,cognome,data,via,città,cap)!=EOF){
		p_new_node=Item_allocation(codice,nome,cognome,data,via,città,cap);
		printf("==============================\n");
		printf("i dati inseriti sono:\n%s %s %s %s %s %s %s\n",codice,nome,cognome,data,via,città,cap);
		Item_Ord_Insertion(head,p_new_node);
	}
	fclose(Fin);
	return;
}
void Stdin_Reader(link* head){
	char codice[6],nome[50],cognome[50],data[11],via[50],città[50];
	char cap[6];
	int flag=0;
	link p_new_node;
	printf("inserira la stringa di input preformatta\n==>");
	printf("inserire codide:");
	scanf("%s",codice);
	printf("inserire nome:");
	scanf("%s",nome);
	printf("inserire cognome:");
	scanf("%s",cognome);
	printf("inserire data di nascita nel formato gg/mm/aaaa:");
	scanf("%s",data);
	printf("inserire via:");
	scanf("%*c ");
	fgets (via, 100, stdin);
	for(int i=0;i<100&&flag;i++){
		if(via[i]=='\n'){
			via[i]='\0';
			flag=0;
		}
	}
	printf("inserire città:");
	scanf("%s",città);
	printf("inserire cap:");
	scanf("%s",cap);
	printf("i dati inseriti sono:\n%s %s %s %s %s %s %s",codice,nome,cognome,data,via,città,cap);
	p_new_node=Item_allocation(codice,nome,cognome,data,via,città,cap);
	Item_Ord_Insertion(head,p_new_node);
	return ;
}

//ritorna il puntatore al nuovo nodo allocato a partire da campi
link Item_allocation(char* c_codice,char* c_nome,char* c_cognome,char* c_data,
			char* c_via,char* c_città,char* c_cap){
	item* p_node;
	p_node=(item*)malloc(sizeof(item));
	strcpy(p_node->codice,c_codice);
	strcpy(p_node->nome,c_nome);
	strcpy(p_node->cognome,c_cognome);
	strcpy(p_node->data,c_data);
	strcpy(p_node->via,c_via);
	strcpy(p_node->città,c_città);
	strcpy(p_node->cap,c_cap);
	p_node->key=Conv_Data(c_data);
	p_node->next=NULL;
	return p_node;
}
//item ord insetion ha l'autorità di modificare ogni nodo compreso head
void Item_Ord_Insertion(link* p_head,link new_node){
	link* pnt=p_head;
	link tmp;
	int flag=0;
	for(;*pnt!=NULL;pnt=&((*pnt)->next)){
		if((*pnt)->key>new_node->key){
			flag=1;
			break;
		}
	}
	//caso flag=1 allora ho trovato che la chive dell'item puntato da ciò a cui punta pnt è
	//minore della chiave dell'item puntat da new_node
	//Procedo con l'inserzione in testa "a cioò che rappresenta pnt"
	if(flag==1){
		tmp=(*pnt);
		(*pnt)=new_node;
		new_node->next=tmp;
	}
	//ho finito la lista e non ho trovato la condizione sulle chiavi che stavo ricercando 
	//allora la chiave di new_node è la più grende della lista la inserico in coda a pnt
	//ove pnt punta al campo next dell'ultimo item
	else{
		(*pnt)=new_node;
	}
	return;
}
int Conv_Data(char *c_data){
	int val=-1,gg,mm,aaaa;
	sscanf(c_data,"%d/%d/%d",&gg,&mm,&aaaa);
	val=aaaa*10000+mm*10+gg;
	return val;
}
//converte la stringa in ingresso in un dice univoco
int Converti_Operazione(char* Operazione){
	if(strcmp(Operazione,"quit")==0) return 0;
	if(strcmp(Operazione,"acquisizione")==0) return 1;
	if(strcmp(Operazione,"ricerca")==0) return 2;
	if(strcmp(Operazione,"cancellazione")==0) return 3;
	if(strcmp(Operazione,"stampa")==0) return 4;
	return 0;
}
link LISTSearch(link head,char *string){
	link x=head;
	int flag=1;
	for(;x!=NULL&&flag;x=x->next){
		if(strcmp(x->codice,string)==0){
			flag=0;
			break;
		}
	}
	return x;
}
link LISTPop(link *PHead,char* string){
	link ris,*x=PHead;
	int flag=1;
	ris=LISTSearch(*PHead,string);
	if(*PHead==NULL||ris==NULL) return NULL;
	if(*PHead==ris){
		flag=0;
		*PHead=ris->next;
	}
	for(;flag&&(*x)->next!=ris;x=&((*x)->next)){
		//printf("%s\n",(*x)->codice);
	}
	if(flag)
		(*x)->next=(*x)->next->next;
	return ris;
}
link LISTPopDate(link* PHead,char* data1,char* data2){
	int NData1=Conv_Data(data1), NData2=Conv_Data(data2);
	for(link x=*PHead;x!=NULL;x=x->next){
		if(x->key<=max(NData2,NData1)&&x->key>=min(NData1,NData2)){
			return LISTPop(PHead,x->codice);
		}
	}
	return NULL;
}
int min(int a,int b){
	if(a<=b)
		return a;
	return b;
}
int max(int a,int b){
	if(a>=b)
		return a;
	return b;
}
