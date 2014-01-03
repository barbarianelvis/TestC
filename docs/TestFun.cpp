#include <iostream>
#include <cstdlib>
using namespace std;

int main(){
	int sum = 0; 
	char str[] = "123456";
	int size = sizeof(str);
	 
	for (int i=size-2;i>=0;i--){
		sum = (str[size-i-2]-'0') + sum*10;
	}
	cout << sum << endl; 
	//itoa(num, str, 10); 
	//printf("The number num is %d and the string str is %s. \n" , num, str); 
	
	system("pause");
	return 0;
}
