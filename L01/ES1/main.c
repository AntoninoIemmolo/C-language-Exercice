#include <stdio.h> 
#define MaxLen 100

char *cercaRegexp(char *src, char *regexp){
	char *RetVal = NULL, SpeList[6] = {'.','[',']','^',(char)92,'\0'};
	char exc_Vet[50];
	int Dim_regexp=0,i=0,u=0,k=0,n=1,Dim_src=0,flag=1;
	Dim_regexp=0;
	//trova la dimensione della regexp
	while(*(regexp+Dim_regexp)!='\0'||regexp==NULL){
		Dim_regexp = Dim_regexp + 1;
	}
	//trova la dimensione di src
	while(*(src+Dim_src)!='\0'||regexp==NULL){
		Dim_src =  Dim_src + 1;
	}
	// Si assume che la lunghezza di regexp non sia superiore a MaxLen
	
	//si iniziallizza la matrice Dec_Mat per evitare di dover inserire
	//il terminatore di riga.
	char Dec_Mat[MaxLen][53]={'\0'};
	//riempie la matrice Dec_Mat con le possibilità della regexp
	while(*(regexp+i) != '\0'||regexp == NULL){
		switch((int)(*(regexp+i))){
			case ((int)'.'):{
				for(int j=0;j<26;j++){
					Dec_Mat[u][j]=(char)j+65;
					Dec_Mat[u][j+26]=(char)j+97;	
				}
				u = u + 1;
				i = i + 1;
				break;
			}
			case ((int)'['):{
				if(*(regexp+i+1) == '^'){	
					for(int j=0;j<26;j++){
						Dec_Mat[u][j]=(char)j+65;
						Dec_Mat[u][j+25]=(char)j+97;	
					}
					while(*(regexp+1+n)!=']'){
						for(int j=0;j<52;j++){
							if(Dec_Mat[u][j]==*(regexp+1+n)){
								if(j!=0)
								Dec_Mat[u][j]=Dec_Mat[u][j-1];
								else 
								Dec_Mat[u][j]=Dec_Mat[u][j+1];
							}
						n=n+1;
						}
					}
				}
				else{
					while(*(regexp+n)!=']'){
						Dec_Mat[u][n-1]=*(regexp+n);
						n=n+1;
					}
				}
				i=i+n;
				u=u+1;
				n=1;
				break;
			}
			case ((int)']'):{
				i = i + 1;
				break;
			}
			case (92):{
				if(*(regexp+i+1) == 'a'){
					for(int j=0;j<25;j++){
						Dec_Mat[u][j]=(char)j+65;
					}
					Dec_Mat[u][49]='\0';
					u=u+1;
				}
				else{
					for(int j=0;j<25;j++){
						Dec_Mat[u][j]=(char)j+97;
					}
					u=u+1;
				}
				u=u+1;
				i = i + 2;
				break;
			}
			default:{
				Dec_Mat[u][0]=*(regexp+i);
				u=u+1;
				i = i + 1;
				break;
			}
		}
	}
	for(int j=0;j<Dim_src;j++){
		flag=0;
		for(int f=0;f<53&&!flag;f++){
			if(Dec_Mat[k][f]==src[j]){
				flag=1;
				k++;
			}
		}
		if(flag){
			if(Dec_Mat[k][0]=='\0') 
				return &(src[j-k+1]);
		}
		else k=0;
		}
	return NULL;
}

int main(int argi,char *argv[]){
	char src[17]="wotonotoLotoCoto\0", regexp[11]="[abcn]oto\0",*Point=NULL;
	Point = cercaRegexp(src, regexp);
	printf("%c\n",*Point);
	return 0;
}
