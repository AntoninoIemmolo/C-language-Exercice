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
	//Dynamimc allocation of Point array, free at line: 19
	Point=(int *)malloc(Max*sizeof(int));
	for (int i=0;i<Max;i++)
		Point[i]=0;
	if(Point==NULL) 
		printf("malloc failed");
	res = majority_ric(Vet,N,Point,Vet[0],N/2);
	free(Point;)
	return res;

}
int majority_ric(int* Vet,int N,int *Point,int Targ,int ReqOccur){
	//i variable rapresents the numbers of reading in Vet that this call has made
	//the minimum ammount of readinf for eeach call is set to 1
	int i=1,RetVal=-1;
	while(i<N && Vet[i-1]==Vet[i]) 
		i++;
	Point[Vet[i-1]] = Point[Vet[i-1]] + i;
	if(Point[Vet[i-1]]>ReqOccur) 
		return Vet[i-1];
	//if this recursive call hasn't reach the max
	if(i<N)
		RetVal=majority_ric(&Vet[i],N-i,Point,Vet[i],ReqOccur);
	return RetVal;
}

//main di prova
int main(int argn,char* argv[]){
	int Vet[MaxDati]={2, 3, 2, 2, 3, 2, 3},Resoult,N=MaxDati;
	Resoult=majority(Vet,N);
	printf("%d\n",Resoult);
	return 0;
}
