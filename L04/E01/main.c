#include <stdio.h>
#include <stdlib.h>

int n=-1,e=-1;
typedef struct{
	int pnt;
	int *archi;
}type_node;

type_node** File_Reader(FILE* fin);
type_node* node_allocation();
void Cerca_Combin(type_node** vet_nodi,int* scelte,int prof,int *i);
void Stampa_Combinazione(int* scelte,int iniz);
void Wrap_Stampa_Combinazione(int* scelte,int iniz,int cnt);
int Verifica_Combinazione(type_node **vet_nodi,int* scelte);
void Node_Free(type_node *p_nodo);


int main(int argv, char* argc[]){	
	int i=0,*scelte;
	FILE* Fin;
	type_node **VetNodi;
	Fin=fopen("../input files/E1/grafo.txt","r");
	if(Fin==NULL) return -1;
	VetNodi=File_Reader(Fin);
	scelte=(int*)malloc(n*sizeof(int));
	//dynamic allocation of array scelte, free at line: 30
	Cerca_Combin(VetNodi,scelte,0,&i);
	free(scelte);
	for(int i=0;i<n;i++) {
		Node_Free(VetNodi[i]);
	}
	free(VetNodi);
	return 0;
}
//la struttura che contine i nodi appartien al programma chiamante
//i nodi sono posseduti dalla "classe" di funzioni Node
type_node** File_Reader(FILE* fin){
	int l1,l2;
	type_node **vet_nodi;
	fscanf(fin,"%d %d ",&n,&e);
	//dynamic allocation of array vet_nodi, free at line: 31
	vet_nodi=(type_node**)malloc(n*sizeof(type_node*));
	for(int i=0;i<n;i++) {
		vet_nodi[i]=NULL;
	}
	for(int i=0;i<n;i++){
		fscanf(fin,"%d %d ",&l1,&l2);
		if(vet_nodi[l1]==NULL){	
			vet_nodi[l1]=node_allocation();
			//una volta creato il nuovo nodo inizializzo pnt a 1
			//non a 0 perchè il solo fatto di aver inizializzato il nodo
			//deriva dal fatto che io abbia trovato un arco conteneto lo stessso
			vet_nodi[l1]->pnt=1;
			vet_nodi[l1]->archi[(vet_nodi[l1]->pnt)-1]=l2;
			if (vet_nodi[l2]==NULL){
				vet_nodi[l2]=node_allocation();
				//una volta creato il nuovo nodo inizializzo pnt a 1
				//non a 0 perchè il solo fatto di aver inizializzato il nodo
				//deriva dal fatto che io abbia trovato un arco conteneto lo stessso
				vet_nodi[l2]->pnt=1;
				vet_nodi[l2]->archi[(vet_nodi[l2]->pnt)-1]=l1;
			}
			else{
				vet_nodi[l2]->archi[(vet_nodi[l2]->pnt)-1]=l1;
				vet_nodi[l2]->pnt++;
			}
		}
		else{
			vet_nodi[l1]->archi[(vet_nodi[l1]->pnt)-1]=l2;
			vet_nodi[l1]->pnt++;
			if (vet_nodi[l2]==NULL){
				vet_nodi[l2]=node_allocation();
				vet_nodi[l2]->pnt=1;
				vet_nodi[l2]->archi[(vet_nodi[l2]->pnt)-1]=l1;
			}
			else{
				vet_nodi[l2]->archi[(vet_nodi[l2]->pnt)-1]=l1;
				vet_nodi[l2]->pnt++;
			}
		}
	}
	return vet_nodi;
}
//si assume che ogni nodo è posseduto da dalla classe di funzioni node
//la liberazione dell'heap spetta a loro
type_node* node_allocation(){
	type_node* stu_nodo;
	//dynamic allocation of stu_nodo, free have to be done by Node_Free function wich is
	//called by main and is defined at line: 139
	stu_nodo=(type_node*)malloc(sizeof(type_node));
	///dynamic allocation of archi in stu_nodo, free have to be done by Node_Free function wich is
	//called by main and is defined at line: 139
	stu_nodo->archi=calloc(n,sizeof(int));
	return stu_nodo;
}

void Cerca_Combin(type_node** vet_nodi,int* scelte,int prof,int *i){
	if(prof>=n){
		if(Verifica_Combinazione(vet_nodi,scelte)){
			Wrap_Stampa_Combinazione(scelte,0,*i);
			(*i)++;
		}
		return;
	}
	scelte[prof]=1;
	Cerca_Combin(vet_nodi,scelte,prof+1,i);
	scelte[prof]=0;
	Cerca_Combin(vet_nodi,scelte,prof+1,i);	
	return;
}
void Wrap_Stampa_Combinazione(int* scelte,int iniz,int cnt){
	printf("[%d]=>",cnt+1);
	printf("(");
	Stampa_Combinazione(scelte, iniz);
	printf(")\n");
	printf("----------------------------\n");
	return;
}
void Stampa_Combinazione(int* scelte,int iniz){
	if(iniz>=n) return;
	if(*(scelte+iniz))
		printf("%d ",iniz);
	Stampa_Combinazione(scelte, iniz+1);
	return;
}
int Verifica_Combinazione(type_node **vet_nodi,int* scelte){
	int *vet_tmp=NULL,f=-1;
	int cont=0;
	for(int i=0;i<n;i++){
		if(scelte[i]){
		cont=cont+vet_nodi[i]->pnt;
		}
	}
	if(cont>e) 
		return 1;
	return 0;
}
//La funzione Node_Free si occupa di liberare la memoria associata al nodo e la memoria allocata nel nodo stesso
void Node_Free(type_node *p_nodo){
	free(p_nodo->archi);
	free(p_nodo);
	return;
}
