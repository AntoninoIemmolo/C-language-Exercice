#include <stdio.h>

int main(){
	char str[90];
	scanf("%*s\n");
	fgets(str,90,stdin);
	printf("%s",str);
return 0;
}
