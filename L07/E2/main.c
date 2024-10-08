#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PATH "./elementi.txt"
#define DD 12
#define DP 30

struct accrob{
    char nome[100];
    int dif;
    int usct;
    int fin;
    int tipo;
    float val;
    struct accrob* link;
};

struct diag{
    struct{
        int avnt;
        int ind;
        int accrobSeq;
    }FAccrob;
    struct accrob VAccrob[5];
    int dif;
    float val;
    int dim;
};
struct NodeDiag{
    struct diag diag;
    struct NodeDiag* link;
};
//Mat[tipo][DirIng][DirUsc][ReqPrec]
struct accrob* MAT[3][2][2][2];
float conta=0;
int contaProg=0;

int LeggiFile();
struct diag Gen_Diag(struct NodeDiag** head);
void Gen_Diag_R(int prof,struct diag diag,int FlagFine,struct NodeDiag **head);
struct accrob* Gen_Posb(int last,struct diag diag);
void Diag_Store(struct diag diag,struct NodeDiag **head);
void Gen_Prog(struct NodeDiag* head,struct NodeDiag* sol);
void Gen_Prog_R(int prof,struct NodeDiag* head,struct NodeDiag* sol,
        struct NodeDiag* best,int dif,float *ValBest);
float Prog_Eval(struct NodeDiag* sol,struct NodeDiag* best,float ValBest);
void FreeMat();

int main(void){
    int cont=0,dif=0;
    if(LeggiFile()==-1)
        return -1;
    struct NodeDiag* head=NULL,*tmp=NULL; 
    struct NodeDiag* sol=(struct NodeDiag*)malloc(sizeof(struct NodeDiag)); 
    Gen_Diag(&head);
    Gen_Prog(head,sol);
    printf("===soluzione  val:%.2f ===\n",conta);
    for(struct NodeDiag* l=sol;l!=NULL;l=l->link,cont++){
        printf("diagonali %d ,",cont+1);
        dif=dif+l->diag.dif;
        printf("DIF :%d VAL:%.2f \n",l->diag.dif,l->diag.val);
        for(int j=0;j<l->diag.dim;j++){
            printf("%s, ",l->diag.VAccrob[j].nome);
        }
        printf("\n========================\n");
    }
    for(struct NodeDiag* l=head;l!=NULL;l=tmp){
        tmp=l->link;
        free(l);
	    //oree(l);
    }

    for(struct NodeDiag* l=sol;l!=NULL;l=tmp){
	    tmp=l->link;
	    free(l);
    }
    FreeMat();
    return 0;
}

int LeggiFile(){
    FILE* FIn=fopen(PATH,"r");
    char InBuff[400],nome[100];
    int FInLen;
    int tipo, DirIn, DirUs, ReqPrec, Fin, Dif;
    float val;
    struct accrob* PrevPoint;
    if(FIn==NULL)
        return -1;
    fscanf(FIn,"%d ",&FInLen);
    for(int i=0;i<FInLen;i++){
        fscanf(FIn,"%s %d %d %d %d %d %f %d",nome,&tipo,&DirIn,&DirUs,&ReqPrec,&Fin,&val,&Dif);
        PrevPoint=MAT[tipo][DirIn][DirUs][ReqPrec];
        MAT[tipo][DirIn][DirUs][ReqPrec]=malloc(sizeof(struct accrob));
        MAT[tipo][DirIn][DirUs][ReqPrec]->val=val;
        MAT[tipo][DirIn][DirUs][ReqPrec]->dif=Dif;
        MAT[tipo][DirIn][DirUs][ReqPrec]->fin=Fin;
        MAT[tipo][DirIn][DirUs][ReqPrec]->usct=DirUs;
        MAT[tipo][DirIn][DirUs][ReqPrec]->link=PrevPoint;
        MAT[tipo][DirIn][DirUs][ReqPrec]->tipo=tipo;
        strcpy(MAT[tipo][DirIn][DirUs][ReqPrec]->nome,nome);
    }
    fclose(FIn);
    return 0;
}

struct diag Gen_Diag(struct NodeDiag** head){
    struct diag diag;
    diag.val=0;
    diag.dim=0;
    Gen_Diag_R(0,diag,0,head);
    /*
    for(struct NodeDiag* l=*head;l!=NULL;l=l->link){
        if(strcmp(l->diag.VAccrob[0].nome,"rondata")==0)
            if(strcmp(l->diag.VAccrob[1].nome,"arabian")==0){
                if(strcmp(l->diag.VAccrob[2].nome,"front_tuck")==0){
                    for(int i=0;i<l->diag.dim;i++)
                        printf("%15s,",l->diag.VAccrob[i].nome);
                    printf("\n");
                }
            }
    }*/
    printf("FINE GENERAZIONE DIAGONALI\n");
    return diag;
}
void Gen_Diag_R(int prof,struct diag diag,int FlagFine,struct NodeDiag **head){
   struct accrob* PosList,*tmp;
   int FlagSeq=0;
    if(prof>=5||FlagFine){
        diag.dim=prof;
/*
        if(strcmp(diag.VAccrob[0].nome,"rondata")==0)
            if(strcmp(diag.VAccrob[1].nome,"arabian")==0){
                if(strcmp(diag.VAccrob[2].nome,"front_tuck")==0){
                    if(diag.dim==3)
                        printf("\n===generata===\n");
                }
            }
	    */
        Diag_Store(diag,head);
        return;
    }
    PosList=Gen_Posb(prof-1,diag); 
    //Ramo di ricorsione 
    for(struct accrob* l=PosList;l!=NULL;l=l->link){
        diag.VAccrob[prof] = *l;
        if(l->tipo==2){
            diag.FAccrob.avnt=1;
            if(prof>0&&((diag.VAccrob[prof-1].tipo==1)||(diag.VAccrob[prof-1].tipo==2))){
                diag.FAccrob.accrobSeq=1;
                FlagSeq=1;
            }
            else
                diag.FAccrob.accrobSeq=0;
        }
        if(l->tipo==1){
            diag.FAccrob.ind=1;
            if(prof>0&&((diag.VAccrob[prof-1].tipo==1)||(diag.VAccrob[prof-1].tipo==2))){
                diag.FAccrob.accrobSeq=1;
                FlagSeq=1;
            }
            else
                diag.FAccrob.accrobSeq=0;
        }

        //se la prossima ricorsione non sarà un caso terminale trattalo come 
        //caso terminale ritorna e continua con la genreazione 
        if(l->fin==0&&prof<4){
            Gen_Diag_R(prof+1,diag,1,head);
        }
        Gen_Diag_R(prof+1,diag,l->fin,head);
        if(diag.VAccrob[prof].tipo==2){
            diag.FAccrob.avnt=0;
            if(FlagSeq)
                diag.FAccrob.accrobSeq=0;
        }
        if(diag.VAccrob[prof].tipo==1){
            diag.FAccrob.ind=0;
            if(FlagSeq)
                diag.FAccrob.accrobSeq=0;
        }
        FlagSeq=0;
    }

    //ramo liberazione possibili accrobazie
    for(struct accrob* l=PosList;l!=NULL;l=tmp){
        tmp = l->link;
        free(l);
    }
    return;
}

void Diag_Store(struct diag diag,struct NodeDiag **head){
    float point=0;
    int dif=0;
    int i=0;
    struct NodeDiag* tmp;
    for(;i<diag.dim;i++){
        point=point+diag.VAccrob[i].val;
        dif=dif+diag.VAccrob[i].dif;
    } 
    if(dif>DD||(diag.FAccrob.ind==0&&diag.FAccrob.avnt==0))
        return;

    tmp=*head;
    *head=(struct NodeDiag*)malloc(sizeof(struct NodeDiag));
    (*head)->diag=diag;
    (*head)->diag.dif=dif;
    (*head)->diag.val=point;
    (*head)->link=tmp;

    return ;
}

//sulla base dell scelte delle accrobazie inserte nella diagonale valita qual'è la lista delle
//possibili scelte che sono possibili
//Mat[tipo][DirIng][DirUsc][ReqPrec]
struct accrob* Gen_Posb(int last,struct diag diag){
    struct accrob* head;
    struct accrob* tmp;
    head=NULL;
    for(int i=0;i<3;i++){
        for(int j=0;j<2;j++){
            if(last==-1){
                if(MAT[i][1][j][0]!=NULL){
                    for(struct accrob* l = MAT[i][1][j][0]; l!=NULL; l=l->link){
                        tmp=head;
                        head=(struct accrob*)malloc(sizeof(struct accrob));
                        *head=*l;
                        head->link=tmp;
                    }
                }
            }
            else
                for(int k=0;k<2;k++){
                    if(MAT[i][diag.VAccrob[last].usct][j][k]!=NULL){
                        for(struct accrob* l =MAT[i][diag.VAccrob[last].usct][j][k];
                                l!=NULL; l=l->link){
                            tmp=head;
                            head=(struct accrob*)malloc(sizeof(struct accrob));
                            *head=*l;
                            head->link=tmp;
                        }
                    }
                }
        }
    }
   return head;
}

void Gen_Prog(struct NodeDiag* head,struct NodeDiag* best){
    float ValBest=0;
    Gen_Prog_R(0,head,NULL,best,0,&ValBest);
    conta = ValBest;
    return;
}

void Gen_Prog_R(int prof,struct NodeDiag* head,struct NodeDiag* sol,
        struct NodeDiag* best,int dif,float *ValBest){
    struct NodeDiag* tmp;
    if(prof>=3){
        *ValBest=Prog_Eval(sol,best,*ValBest);
        return ;
    }

    for(struct NodeDiag* l=head;l!=NULL;l=l->link){
        //pruning sulla condizione di massima difficoltà del programma
        if(dif+l->diag.dif<=DP){
            //uso tmp per l'inserzione in testa
            tmp=sol;
            sol=malloc(sizeof(*sol));
            sol->link=tmp;
            sol->diag=l->diag;
            Gen_Prog_R(prof+1,l,sol,best,dif+l->diag.dif,ValBest);
            //uso tmp per la liberazione di sol
            sol->link=tmp;
            free(sol);
            sol=tmp;
        }
    }
    return;
}

float Prog_Eval(struct NodeDiag* sol,struct NodeDiag* best,float ValBest){
    int flagAvnt=0,flagInd=0,flagSeqAcc=0;
    float ValCurr=0;
    struct NodeDiag *tmp,*j;
    for(struct NodeDiag* l=sol;l!=NULL;l=l->link){
        ValCurr=ValCurr+l->diag.val;
        if(l->link==NULL&&l->diag.VAccrob[l->diag.dim-1].val>=8){
            ValCurr=ValCurr+l->diag.val*0.5;
        }
        if(l->diag.FAccrob.ind)
            flagInd=1;
        if(l->diag.FAccrob.avnt)
            flagAvnt=1;
        if(l->diag.FAccrob.accrobSeq==1)
            flagSeqAcc=1;
    }
    //se il progrmma è valido
    if(flagAvnt&&flagInd&&flagSeqAcc)
        if(ValBest<ValCurr){
            j=best;
            for(struct NodeDiag* l=best->link;l!=NULL;l=tmp){
                tmp=l->link;
                free(l);
	        }
            for(struct NodeDiag* l=sol;l!=NULL;l=l->link){
                j->diag=l->diag;
                if(l->link!=NULL){
                    j->link=(struct NodeDiag*)malloc(sizeof(struct NodeDiag));
                    j=j->link;
                }
            }
            
            ValBest=ValCurr;
        }
    return ValBest;
}

//Mat[tipo][DirIng][DirUsc][ReqPrec]
void FreeMat(){
	struct accrob* tmp;
	for(int i=0;i<3;i++)
		for(int j=0;j<2;j++)
			for(int k=0;k<2;k++)
				for(int p=0;p<2;p++)
            				for(struct accrob* l=MAT[i][j][k][p];l!=NULL;l=tmp){
						tmp=l->link;
						free(l);
					}
}





