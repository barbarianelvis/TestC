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
        b++; 	//指到陣列ptr空白處 
    --b;		//回到陣列最後一項 

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
