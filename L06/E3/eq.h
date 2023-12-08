#include <stdio.h>
typedef struct OGG* ogg;
void EQ_FileRead(FILE* FEq);
void EQ_GetName(ogg POgg,char* nome);
void EQ_Print(char* Name);
void EQ_Free(void);
ogg EQ_Find(char* Nome);
