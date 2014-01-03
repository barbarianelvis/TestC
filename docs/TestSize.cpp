#include <iostream>
#include <cstdlib>
using namespace std;

class Stack{
	private:
		int size;
		int top;
		int *array;
	public:
		
		Stack (int s){
			size = s;
			top = 0;
			array = new int[s];
		}
		
		void push(int item){
			if (top==size)
				cout << "Stack is full!" << endl;
			else{
				*(array+top)=item;
				top++;
			}
		}
		
		int pop(){
			if (top==0)
				cout << "Stack is empty!" << endl;
			else{
				top--;
				return *(array+top);
			}
		}
};

int main(){
	
	Stack stk(5);
	
	stk.push(10);
	stk.push(20);
	stk.push(30);
	stk.push(40);
	stk.push(50);
	stk.push(60);
	
	for (int i=0;i<6;i++)
		cout << stk.pop() << " ";
	
	/*int *p,a=1,b=2,*q;
	p =&a;
	q = &b;
	
	cout <<*p << endl;
	cout << q << endl;
	cout << &p<< endl;
	
	a=2;
	b=1;
	cout << p << endl;
	cout << *p << endl;
	cout << q << endl;
	cout << *q << endl; */
	
	/*int array[10] = {15,20,30,4,25,74,85,10,14,65};
	//int temp = 0;
	
	for (int i=1;i<10;i++){
		for (int j=0;j<i;j++){
			if (array[j]>array[i]){
				int temp = array[i];
				array[i]=array[j];
				array[j]= temp;
			}
		}
	}
	
	for (int k=0;k<10;k++)
		cout << array[k] << " ";
	*/
	
		
	system("pause");
    return 0;
    
} 
