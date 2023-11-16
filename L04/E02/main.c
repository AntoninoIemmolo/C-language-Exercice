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
	int cap;
	int key;
	struct s_item* next;
}item,*link;

void File_Reader(char *file_path,link* head);
link Item_allocation(char* c_codie,char* c_nome,char* c_cognome,char* c_data,
		char* c_via,char* c_città,int c_cap);
void Item_Ord_Insertion(link* head,link* new_node);
int Conv_Data(char *c_data);
int Converti_Operazione(char* Operazione);
void Stdin_Reader(link *head);

int main(int argv,char* argc[]){
	link Head=NULL;
	link tmp=NULL;
	int code=1,flag=1;
	char FilePath[50]="../input files/E2/anag1.txt\0",string[50];
	File_Reader(FilePath,&Head);
	while(code!=0){
		printf("\niserire l'operazione chi si vuole svolgere\nacquisizione\nricerca\ncancellazione\n==>");
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
				break;	
			case(3):
				break;
		}
	}
	return 0;
}
//Dato un percorso file in ingresso ritorna il puntatore al primo elemento della lista
//conprensiva dei nuovi e dei vecchi elimenti già ordinata
void File_Reader(char *file_path,link* head){
	FILE* Fin;
	Fin=fopen(file_path,"r");
	char codice[6],nome[50],cognome[50],data[11],via[50],città[50];
	int cap;
	link p_new_node;
	if(Fin==NULL) return ;
	while(fscanf(Fin,"%s %s %s %s %s %s %d",codice,nome,cognome,data,via,città,&cap)!=EOF){
		p_new_node=Item_allocation(codice,nome,cognome,data,via,città,cap);
		printf("==============================\n");
		printf("i dati inseriti sono:\n%s %s %s %s %s %s %d\n",codice,nome,cognome,data,via,città,cap);
		//printf("head prima=%p\n",head);
		Item_Ord_Insertion(head,&p_new_node);
		//printf("head dopo=%p\n",head);
	}
	fclose(Fin);
	return;
}
void Stdin_Reader(link* head){
	char codice[6],nome[50],cognome[50],data[11],via[50],città[50];
	int cap;
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
	scanf("%s",via);
	printf("inserire città:");
	scanf("%s",città);
	printf("inserire cap:");
	scanf("%d",&cap);
	printf("i dati inseriti sono:\n%s %s %s %s %s %s %d",codice,nome,cognome,data,via,città,cap);
	p_new_node=Item_allocation(codice,nome,cognome,data,via,città,cap);
	Item_Ord_Insertion(head,&p_new_node);
	return ;
}

//ritorna il puntatore al nuovo nodo allocato a partire da campi
link Item_allocation(char* c_codice,char* c_nome,char* c_cognome,char* c_data,
			char* c_via,char* c_città,int c_cap){
	item* p_node;
	p_node=(item*)malloc(sizeof(item));
	strcpy(p_node->codice,c_codice);
	strcpy(p_node->nome,c_nome);
	strcpy(p_node->cognome,c_cognome);
	strcpy(p_node->data,c_data);
	strcpy(p_node->via,c_via);
	strcpy(p_node->città,c_città);
	p_node->cap=c_cap;
	p_node->key=Conv_Data(c_data);
	p_node->next=NULL;
	return p_node;
}
//inserisce in maniera ordinata (seconda chiave key) il nuovo nodo nella lista
//in caso di medesima chiave ordina secondo ansianità ultima nodo inserito nodo 
/*link Item_ord_insertion(link head,link new_node){
	link p_nodo=head,tmp;
	int flag=1;
	link tmp1;
	//ciclo che scorre da head fino all'ultimo elemento della lista, 
	//se trova tra gli elementi uno la cui chiave è superioro alla chiave del nuovo nodo 
	//esce dal ciclo puntando al nodo prima di quello che maggiora la chiave del nuovo nodo
	for(tmp1=head;tmp1!=NULL;tmp1=tmp1->next) printf("==%s \n",tmp1->nome);
	for(;p_nodo!=NULL&&p_nodo->next!=NULL&&flag;p_nodo=p_nodo->next){
		if(p_nodo->next->key<=new_node->key){
			flag=0;
		}
	}
	if(p_nodo==NULL) return new_node;
	//se p_node->next ==NULL allora non ho fatto alcuna averica sulle chiavi di p_nodo e new_node
	//allora p_node punta ad un item ma esso è l'unico della lista
	if(p_nodo->next==NULL) {
		if(p_nodo==head){
			//inserimento in coda a p_nodo
			if(p_nodo->key<new_node->key){
				p_nodo->next=new_node;
				return p_nodo;
			}
			//inserimemto in testa
			else{
				new_node->next=p_nodo;
				return new_node;
			}
		}
		//non sto modificando il valore di head
		//inserimento in testa
		else{
			//inserimento in coda a p_nodo
			if(p_nodo->key<new_node->key){
				p_nodo->next=new_node;
				return head;
			}
		}
	}
	//inserimemto in coda 
	else{
		tmp=p_nodo->next;
		p_nodo->next=new_node;
		new_node->next=tmp;
		return head;
	}
}*/
//item ord insetion ha l'autorità di modificare ogni nodo compreso head
void Item_Ord_Insertion(link* p_head,link* new_node){
	link* pnt=p_head;
	link tmp;
	int flag=0;
	for(;*pnt!=NULL;pnt=&((*pnt)->next)){
		if((*pnt)->key>(*new_node)->key){
			flag=1;
			break;
		}
	}
	//caso flag=1 allora ho trovato che la chive dell'item puntato da ciò a cui punta pnt è
	//minore della chiave dell'item puntat da new_node
	//Procedo con l'inserzione in testa "a cioò che rappresenta pnt"
	if(flag){
		tmp=(*pnt);
		(*pnt)=(*new_node);
		(*new_node)->next=tmp;
	}
	//ho finito la lista e non ho trovato la condizione sulle chiavi che stavo ricercando 
	//allora la chiave di new_node è la più grende della lista la inserico in coda a pnt
	//ove pnt punta al campo next dell'ultimo item
	else{
		(*pnt)=(*new_node);
	}
	for(tmp=(*p_head);tmp!=NULL;tmp=tmp->next) printf("==%s \n",tmp->nome);
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
	if(strcmp(Operazione,"fine")==0) return 0;
	if(strcmp(Operazione,"acquisizione")==0||strcmp(Operazione,"a")==0) return 1;
	if(strcmp(Operazione,"ricerca")==0||strcmp(Operazione,"r")==0) return 2;
	if(strcmp(Operazione,"cancellazione")==0) return 3;
	return 0;
}
