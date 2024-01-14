typedef struct grp* Graph;

Graph GR_init(int dim);
void GR_Load(Graph gr,char path[100],int flagMatList);
void GR_Print_All_ord(Graph gr);
int GR_Ad_Ver(Graph gr,char* lab1,char* lab2,char* lab3);
void GR_Gen_List(Graph gr);
void GR_free(Graph gr);

