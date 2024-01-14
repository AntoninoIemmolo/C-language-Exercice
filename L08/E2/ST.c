#include "ST.h"

#ifndef stdio
#define stdio
#include <stdio.h>
#endif

#ifndef stdlib 
#define stdlib 
#include <stdlib.h>
#endif

#ifndef string 
#define string 
#include <string.h>
#endif



struct SymbolTable{
    //composto per valore
    struct BSTnode *BST;
    int usd;
    int max;
};
//the simpletst version of BST is used becouse of problem requirements wich 
//doesn't execeed the labels->key key->labels operetion
typedef struct BSTnode{
    char lab[30];
    char rete[30];
    int id;
    struct BSTnode* right;
    struct BSTnode* left;
}BST;


static BST* BST_searchR(BST* head,char lab[30]);
static BST* BST_Node_Init(char lab[30],char LabRet[30],int id);
static void BST_printR(BST* head);
static void ST_realloc(SmbTab st,int NewMax);
static BST* ST_search_by_indexR(BST* head,int id);
static BST* ST_selectR(BST* head,int *pos);

SmbTab ST_init(int MaxDim){
    SmbTab st;
    st=(SmbTab)malloc(sizeof(*st));
    st->max=MaxDim;
    st->usd=0;
    return st;
}
int ST_insert(SmbTab st,char lab[30],char LabRet[30]){
    BST* RetVal=NULL;
    if(st->usd==0){
        st->BST=(BST*)malloc(sizeof(BST));
        strcpy(st->BST->lab,lab);
        strcpy(st->BST->rete,LabRet);
        st->BST->id=(st->usd)++;
        st->BST->left=NULL;
        st->BST->right=NULL;
        return 1;
    }
    RetVal=BST_searchR(st->BST,lab);
    if(strcmp(RetVal->lab,lab)==0)
        return 0;
    if(strcmp(lab,RetVal->lab)>0){
        if(st->usd>=st->max)
            ST_realloc(st,st->max*2);
        RetVal->right=BST_Node_Init(lab,LabRet,(st->usd++));
    }
    else if(strcmp(lab,RetVal->lab)<0){
        if(st->usd>=st->max)
            ST_realloc(st,st->max*2);
        RetVal->left=BST_Node_Init(lab,LabRet,(st->usd++));
    }
    return 1;
}
static BST* BST_Node_Init(char lab[30],char LabRet[30],int id){
    BST* new=NULL;
    new=(BST*)malloc(sizeof(BST));
    strcpy(new->lab,lab);
    strcpy(new->rete,LabRet);
    new->id=id;
    new->left=NULL;
    new->right=NULL;
    return new;
}


int ST_search(SmbTab st,char lab[30]){
    BST* RetVal;
    RetVal=BST_searchR(st->BST,lab);
    if(strcmp(RetVal->lab,lab)==0)
        return RetVal->id;
    return -1;
}

static BST* BST_searchR(BST* head,char lab[30]){
    BST* RetVal=NULL;
    if(head==NULL){
        return NULL;
    }
    if(strcmp(head->lab,lab)==0){
        return head;
    }
    //strcmp(str1,str2)
    //return >0 if str1>str2 (first non matching char) 
    if(strcmp(lab,head->lab)>0)
        RetVal=BST_searchR(head->right,lab);
    else if(strcmp(lab,head->lab)<0)
        RetVal=BST_searchR(head->left,lab);

    if(RetVal==NULL)
        return head;
    return RetVal;
}
void ST_print(SmbTab st){
    BST_printR(st->BST);
    printf("\n");
}
static void BST_printR(BST* head){
    if(head==NULL)
        return;
    BST_printR(head->left);
    printf("%s,",head->lab);
    BST_printR(head->right);
    return;
}
static void ST_realloc(SmbTab st,int NewMax){
    st->BST=realloc(st->BST,NewMax);
    st->max=NewMax;
}

int ST_search_by_index(SmbTab st,int id,char str[30]){
    BST* RetVal;
    RetVal=ST_search_by_indexR(st->BST,id);
    if(RetVal==NULL)
        return 0;
    strcpy(str,RetVal->lab);
    return 1;
}
static BST* ST_search_by_indexR(BST* head,int id){
    BST* RetValR,*RetValL;
    if(head==NULL)
        return NULL;
    if(head->id==id)
        return head;

    RetValL=ST_search_by_indexR(head->left,id);
    RetValR=ST_search_by_indexR(head->right,id);

    if(RetValL==NULL)
        return RetValR;
    return RetValL;
}
int ST_getDim(SmbTab st){
    return st->usd;
}

void ST_select(SmbTab st,int pos,char* lab){
    BST* RetVal=NULL;
    pos++;
    RetVal=ST_selectR(st->BST,&pos);
    if(RetVal!=NULL){
        strcpy(lab,RetVal->lab);
    }
    else
        lab=NULL;
    return;
}
static BST* ST_selectR(BST* head,int *pos){
    BST* RetValR=NULL,*RetValL=NULL;
    if(head==NULL){
        return NULL;
    }
    RetValL=ST_selectR(head->left,pos);
    if(RetValL!=NULL)
        return RetValL;
    (*pos)--;
    if(*pos<=0)
        return head;
    RetValR=ST_selectR(head->right,pos);
    if(RetValR!=NULL)
        return RetValR;
    if(RetValL==NULL){
       return RetValR;
    }
    return RetValL;
}
int ST_get_Id(SmbTab st,char* lab){
    BST* res=NULL;
    res=BST_searchR(st->BST,lab);
    if(res!=NULL&&strcmp(lab,res->lab)==0)
        return res->id;
    else return -1;

}
