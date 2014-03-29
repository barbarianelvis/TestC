#include <iostream>
#include <cstring>
 
using namespace std;
 
void reverseStr(char* ch, char *temp) {
    if(ch==NULL)return;
    
    reverseStr( strtok( NULL , " " ),temp );  
	//Recursive method for reversing sentence.
    cout << ch << " ";
    strcat(temp,ch);
 	strcat(temp," ");
 	//puts(temp);
 	//cout << "\n";
}
 
int main() {
    char str[] = "how are you";
    char temp[20];
    reverseStr( strtok( str , " " ),temp );
  	puts(temp); 
    return 0;
}

/*char string[80];
  	strcpy (string,"these ");
  	strcat (string,"strings ");
  	strcat (string,"are ");
  	strcat (string,"concatenated.");
  	puts (string);*/
