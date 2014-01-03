#include <ctype.h>
#include <stdio.h>
int atoi (char s[]);

int main(void ){   
	char s[10] = "789";
	printf("integer=%d\n",atoi(s));
	return 0;
}

// ATOI function
int atoi (char s[]){
	int i,n,sign;
	for(i=0;isspace(s[i]);i++)//¸õªÅ¥Õ²Å
    ;
	sign=(s[i]=='-')?-1:1;
	if(s[i]=='+'||s[i]=='-')//¸õ+-²Å
    	i++;
    	
	for(n=0;isdigit(s[i]);i++)
    	n=10*n+(s[i]-'0');
	
	return sign *n;
}
