typedef struct SymbolTable *SmbTab;
SmbTab ST_init(int MaxDim);
int ST_search(SmbTab st,char lab[30]);
int ST_search_by_index(SmbTab st,int id,char str[30]);
int ST_insert(SmbTab st,char lab[30],char LabRet[30]);
void ST_print(SmbTab st);
int ST_getDim(SmbTab st);
void ST_select(SmbTab st,int pos,char* lab);
int ST_get_Id(SmbTab st,char* lab);
