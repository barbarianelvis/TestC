#include <iostream>
#include <cstring>
 
using namespace std;
 
void reverseStr(char* ch, char *temp) {
    if(ch==NULL)return;
    reverseStr( strtok( NULL , " " ),temp );
    cout << ch << " ";
    strcat(temp,ch);
 	strcat(temp," ");
}
 
int main() {
    char str[] = "how are you";
    char temp[20];
    reverseStr( strtok( str , " " ),temp );
  	puts(temp); 
    return 0;
}
