#include <iostream>
#include <cstdlib>
#include <string.h>
using namespace std;
//String reverse
int main(){
	char str[10] = "1234567";
    char *a, *b, c;
    
    a = b = str;

    while (*b)
        b++; 	//����}�Cptr�ťճB 
    --b;		//�^��}�C�̫�@�� 

	while(b>a){
		c = *a;
		*a++ = *b;
		*b-- = c;
	}

    //Print out
    int i=0;
	b = str;    
    while(*b){
    	cout << str[i++];
    	b++;
    }
	 
}
