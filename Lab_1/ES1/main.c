#include <stdio.h> 

char *cercaRegexp(char *src, char *regexp){
char *RetVal = NULL, SpeList[6] = {'.','[',']','^',(char)92,'\0'};
char exc_Vet[50];
int Dim_regexp=0,i=0,u=0,k=0,n=1;
Dim_regexp=0;
while(*(regexp+Dim_regexp)!='\0'||regexp==NULL){
	Dim_regexp = Dim_regexp + 1;
}
// Si assume che la lunghezza di regexp non sia superiore a 100 
char* PointDecStr[100];
char Dec_Mat[100][53]={'\0'};
while(*(regexp+i) != '\0'||regexp == NULL){
	switch((int)(*(regexp+i))){
		case ((int)'.'):{
			for(int j=0;j<26;j++){
				Dec_Mat[i][j]=(char)j+65;
				Dec_Mat[i][j+26]=(char)j+97;	
			}
			PointDecStr[u]=Dec_Mat[i];
			u = u + 1;
			i = i + 1;
			break;
		}
		case ((int)'['):{
			if(*(regexp+i+1) == '^'){	
				for(int j=0;j<26;j++){
					Dec_Mat[i][j]=(char)j+65;
					Dec_Mat[i][j+25]=(char)j+97;	
				}
				while(*(regexp+1+n)!=']'){
					for(int j=0;j<52;j++){
						if(Dec_Mat[i][j]==*(regexp+1+n)){
							if(j!=0)
							Dec_Mat[i][j]=Dec_Mat[i][j-1];
							else 
							Dec_Mat[i][j]=Dec_Mat[i][j+1];
						}
					n=n+1;
					}
				}
			}
			else{
				while(*(regexp+n)!=']'){
					Dec_Mat[i][n-1]=*(regexp+n);
					n=n+1;
				}
			}
			PointDecStr[u]=Dec_Mat[i];
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
					Dec_Mat[i][j]=(char)j+65;
				}
				Dec_Mat[i][49]='\0';
				u=u+1;
			}
			else{
				for(int j=0;j<25;j++){
					Dec_Mat[i][j]=(char)j+97;
				}
				PointDecStr[u]=Dec_Mat[i];
				u=u+1;
			}
			PointDecStr[u]=Dec_Mat[i];
			u=u+1;
			i = i + 2;
			break;
		}
		default:{
			Dec_Mat[i][0]=*(regexp+i);
			PointDecStr[u]=Dec_Mat[i];
			u=u+1;
			i = i + 1;
			break;
		}
	}
}
/*while(*src != '\0'){

}*/
return RetVal;
}

int main(int argi,char *argv[]){
	char src[17]="notovoroLotoCoto\0", regexp[11]="[abcn].oto\0";
	cercaRegexp(src, regexp);
	return 0;
}
