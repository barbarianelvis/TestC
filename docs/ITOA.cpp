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
	if((sign=n)<0)//�����Ÿ� 
    	n=-n;//��n������� 
    i=0;
	do{
    	s[i++]=n%10+'0';//���U�@�Ӧr
	}while ((n/=10)>0);//�R���ӼƦr

	if(sign<0)
    	s[i++]='-';
	s[i]='\0';
	for(j=i;j>=0;j--)//�ͦ��Ƭ��f�A�f��X
    	printf("%c",s[j]);
}
