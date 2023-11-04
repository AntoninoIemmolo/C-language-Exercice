#include <stdio.h>
#include <stdlib.h>
#define MaxDati 7
int majority_ric(int* Vet,int N,int *Point,int Targ,int ReqOccur);
int majority( int *Vet, int N){
	int res=-1,Max=0,*Point;
	for (int i=0;i<N;i++){
		if(Max<Vet[i]){
			Max=Vet[i];
		}
	}
	Point=(int *)malloc(Max*sizeof(int));
	for (int i=0;i<Max;i++)
		Point[i]=0;
	if(Point==NULL) 
		printf("malloc failed");
	res = majority_ric(Vet,N,Point,Vet[0],N/2);
	return res;

}
int majority_ric(int* Vet,int N,int *Point,int Targ,int ReqOccur){
	int i=0,RetVal=-1;
	while(i<N && Vet[i]==Vet[i+1]) 
		i++;
	Point[Vet[i]] = Point[Vet[i]] + i + 1;
	if(Point[Vet[i]]>ReqOccur) 
		return Vet[i];
	if(i<N-1)
		RetVal=majority_ric(&Vet[i+1],N-i-1,Point,Vet[i+1],ReqOccur);
	return RetVal;
}

//main di prova
int main(int argn,char* argv[]){
	int Vet[MaxDati]={3, 3, 9, 4, 3, 5, 4},Resoult,N=MaxDati;
	Resoult=majority(Vet,N);
	printf("%d\n",Resoult);
	return 0;
}
