#include <iostream>
#include <cstdlib>
using namespace std;
//Stack declaration 
class Stack{
      private:
              int top;
              int size;
              int *array;
      public:
             Stack(int s){
                 size=s;
                 array=new int[s]; //heap memory allocation 
                 top=0;
             }
             
             void push(int item){
                  if(top==size)
                  	cout<<"Stack is full!"<<endl;
                  else
                      *(array+top)=item;
                      top++;
             }
             int pop(){
                 if(top==0)
                     cout<<"Stack is empty!"<<endl;
                 else{
                     int item;
                     top--;
                     item=*(array+top);
                     return item;
                 }
             }
};
//Execute
int main(){
    Stack stk(5);
    stk.push(52);
    stk.push(41);
    stk.push(3);
    stk.push(100);

    for(int i=0;i<5;i++)
        cout<<stk.pop()<<" ";
    cout<<endl;
    
    system("pause");
    return 0;
}
