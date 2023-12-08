#include "eq.h"

#ifndef _STRING
#define _STRING
#include <string.h>
#endif

#ifndef _STDIO
#define _STDIO
#include <stdio.h>
#endif

#ifndef _STDLIB
#define _STDLIB
#include <stdlib.h>
#endif

typedef struct node NODE;
void PG_Ins(char* cod,char* nom1,char* nom2,int hp,int mg,int atk,int def,int mag,int spr);
void PG_FileRead(FILE* FPg);
void PG_Print(char *key);
NODE* PG_Pop(char* key);
NODE* PG_Find(char *key);
void PG_InvIns(char *key, char* NomeOgg);
void PG_InvPop(char *key, char* NomeOgg);
void PG_Free(char* key);
