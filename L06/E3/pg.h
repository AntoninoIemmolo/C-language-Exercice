//#include "pg.c"
#include <stdio.h>
#include <string.h>
#include "eq.h"
typedef struct node NODE;
void PG_Ins(char* cod,char* nom1,char* nom2,int hp,int mg,int atk,int def,int mag,int spr);
void PG_FileRead(FILE* FPg);
void PG_Print(char *key);
NODE* PG_Pop(char* key);
NODE* PG_Find(char *key);
void PG_InvIns(char *key, char* NomeOgg);
void PG_InvPop(char *key, char* NomeOgg);
