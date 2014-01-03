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
			
	system("pause");
    return 0; 
} 
