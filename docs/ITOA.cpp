#include <ctype.h>
#include <stdio.h>
void      itoa (int n,char s[]);
using namespace std

int main(void ){   
	int n;
	char s[100];
	printf("Input n:\n");
	scanf("%d",&n);
    printf("the string : \n");
    itoa (n,s);
	return 0;
}
//ATOI function
void itoa (int n,char s[]){
	int i,j,sign;
	if((sign=n)<0)//紀錄符號 
    	n=-n;//使n成正整數 
    i=0;
	do{
    	s[i++]=n%10+'0';//取下一個字
	}while ((n/=10)>0);//刪除該數字

	if(sign<0)
    	s[i++]='-';
	s[i]='\0';
	for(j=i;j>=0;j--)//生成數為逆，逆輸出
    	printf("%c",s[j]);
}
