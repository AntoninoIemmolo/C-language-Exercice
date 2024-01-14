#include "Gr.h"
#include "ST.h"

#ifndef stdlib
#define stdlib
#include <stdlib.h>
#endif

#ifndef stdio
#define stdio
#include <stdio.h>
#endif

struct grp{
    SmbTab st;
    int **mat;
    int NNode;
    struct ad **AdLst;
};

struct ad{
    int id;
    int wh;
    struct ad* link;
};

Graph GR_init(int dim);
static void ED_insertL(Graph gr,int ed1,int ed2,int wh);
static int GR_Edge_Search(Graph gr,char* lab1,char* lab2);
static int FlagMatList;

//flagMatList=0 -> matrice, FlagMatList=1 -> lista adiacenze 
void GR_Load(Graph gr,char path[100],int flagMatList){
    int cont=0,id1=-1,id2=-1,wh=0;
    char lab1[30],lab2[30];
    char ret1[30],ret2[31];
    FlagMatList=flagMatList;
    FILE* fin=fopen(path,"r");
    while(fscanf(fin,"%s %s %s %s %*d ",lab1,ret1,lab2,ret2)==4){
        if(ST_insert(gr->st,lab1,ret1))
            cont++;
        if(ST_insert(gr->st,lab2,ret2))
            cont++;
    }
    fclose(fin);
    gr->NNode=cont;
    fin=fopen(path,"r");
    if(flagMatList){
        gr->AdLst=(struct ad**)malloc(cont*sizeof(struct ad*));
        for(int i=0;i<cont;i++)
            (gr->AdLst)[i]=NULL;
        while(fscanf(fin,"%s %*s %s %*s %d ",lab1,lab2,&wh)==3){
            id1=ST_search(gr->st,lab1);
            id2=ST_search(gr->st,lab2);
            ED_insertL(gr,id1,id2,wh);
            ED_insertL(gr,id2,id1,wh);
        }
    }
    else{
        gr->mat=(int**)malloc(cont*sizeof(int*));
        for(int i=0;i<cont;i++)
            gr->mat[i]=(int*)malloc(cont*sizeof(int));
        for(int i=0;i<cont;i++)
            for(int j=0;j<cont;j++)
                gr->mat[i][j]=-1;
        while(fscanf(fin,"%s %*s %s %*s %d ",lab1,lab2,&wh)==3){
            id1=ST_search(gr->st,lab1);
            id2=ST_search(gr->st,lab2);
            gr->mat[id1][id2]=wh;
            gr->mat[id2][id1]=wh;
        }
    }
    fclose(fin);
    return;
}

Graph GR_init(int dim){
    Graph gr;
    gr=(Graph)malloc(sizeof(*gr));
    gr->st=ST_init(dim);
    gr->NNode=dim;
    gr->mat=NULL;
    gr->AdLst=NULL;
    return gr;
}

static void ED_insertL(Graph gr,int id1,int id2,int wh){
    struct ad *tmp=gr->AdLst[id1];
    gr->AdLst[id1]=(struct ad*)malloc(sizeof(struct ad));
    gr->AdLst[id1]->wh=wh;
    gr->AdLst[id1]->id=id2;
    gr->AdLst[id1]->link=tmp;
}


void GR_Print_All_ord(Graph gr){
    char lab[30];
    ST_print(gr->st);
    int max=ST_getDim(gr->st),id=-1;
    for(int i=0;i<14;i++){
        ST_select(gr->st,i,lab);
        id=ST_get_Id(gr->st,lab);
        printf("(%d) %15s\t[",id,lab);
        if(FlagMatList){
            for(struct ad* p=gr->AdLst[id];p!=NULL;p=p->link){
                if(ST_search_by_index(gr->st,p->id,lab)){
                    printf("(%d)%s,",p->id,lab);
                }
            }
        }
        else{
            for(int j=0;j<max;j++){
                if(gr->mat[id][j]!=-1)
                    if(ST_search_by_index(gr->st,j,lab))
                        printf("(%d)%s,",j,lab);
            }
        }
        printf("]\n");

    }
}
int GR_Ad_Ver(Graph gr,char* lab1,char* lab2,char* lab3){
    if(GR_Edge_Search(gr,lab1,lab2)&&GR_Edge_Search(gr,lab1,lab3))
        if(GR_Edge_Search(gr,lab2,lab3))
            return 1;
    return 0;
}

static int GR_Edge_Search(Graph gr,char* lab1,char* lab2){
    int id1=ST_search(gr->st,lab1);
    int id2=ST_search(gr->st,lab2);
    if(id1<0||id2<0)
        return 0;
    if(FlagMatList){
        for(struct ad* p=gr->AdLst[id1];p!=NULL;p=p->link){
            if(p->id==id2)
                return 1;
        }
    }
    else{
        if(gr->mat[id1][id2]!=-1)
            return 1;
    }
    return 0;
}


void GR_Gen_List(Graph gr){
    int id1=-1,id2=-1,wh=-1;
    if(FlagMatList==0){
    FlagMatList=1;
    gr->AdLst=(struct ad**)malloc(gr->NNode*sizeof(struct ad*));
        for(int i=0;i<gr->NNode;i++){
            for(int j=0;j<gr->NNode;j++){
                if(gr->mat[i][j]!=-1){
                    wh=gr->mat[i][j];
                    ED_insertL(gr,i,j,wh);
                }
            }
        }
    }
}
void GR_free(Graph gr){
    struct ad* tmp=NULL;
    if(gr->mat!=NULL){
        for(int i=0;i<gr->NNode;i++){
            free(gr->mat[i]);
	}
    	free(gr->mat);
    }
    if(gr->AdLst!=NULL){
        for(int i=0;i<gr->NNode;i++){
            for(struct ad* p=gr->AdLst[i];p!=NULL;p=tmp){
                tmp=p->link;
                free(p);
            }
        }
	free(gr->AdLst);
    }
    ST_free(gr->st);
    free(gr->st);
    free(gr);
}






