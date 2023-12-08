#ifndef _STDIO
#define _STDIO
#include <stdio.h>
#endif

#ifndef _STRING
#define _STRING
#include <string.h>
#endif

#ifndef _STTDIO
#define _STDIO
#include <stdio.h>
#endif

#ifndef _STDLIB
#define _STDLIB
#include <stdlib.h>
#endif


typedef struct OGG* ogg;
void EQ_FileRead(FILE* FEq);
void EQ_GetName(ogg POgg,char* nome);
void EQ_Print(char* Name);
void EQ_Free(void);
ogg EQ_Find(char* Nome);
