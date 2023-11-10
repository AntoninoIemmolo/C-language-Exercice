#include <stdio.h>
int gcd(int a, int b);

int main(int argc,char* argv[]){
	int num1, num2, ris;
	printf("Inserire i 2 numeri:");
	scanf("%d %d",&num1,&num2);
	if(num1>num2) ris = gcd(num1,num2);
	else ris = gcd(num2,num1);
	printf("il risultato è: %d\n",ris);
	return 0;
}


int gcd(int a, int b){
	int r;
	if(a==b) return a;
	if(b%2==0){ 
		if(a%2==0) 
			r = 2*gcd(a/2,b/2);
		else
			r = gcd(a,b/2);
	}
	else if(a%2==0 && b%2!=0){ 
		if(a/2>b)
			r=gcd(a/2,b);
		else
			r=gcd(b,a/2);
	}			
	else
		if((a-b)/2>b)
			r = gcd((a-b)/2,b);
		else
			r = gcd(b,(a-b)/2);
	return r;
	
}
