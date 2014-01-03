#include <iostream>
#include <cstdlib>
using namespace std;

//queue class declaration
class Queue
{
      private:
              int size;
              int front,rear;
              int *buffer;
      public:
             Queue(int s)
             {
                 size=s;
                 buffer=new int[s];
                 front=0;
                 rear=0;
             }
             
             void enque(int item)
             {
                  if(full()!=true)
                  {
                      buffer[front]=item;
                      front=(front+1)%size;
                  }
                  else
                      cout<<"Queue is full!"<<endl;
             }
             int deque()
             {
                 if(empty()!=true)
                 {
                      int item;
                      item=buffer[rear];
                      rear=(rear+1)%size;
                      return item;
                 }
                 cout<<"Queue is empty!"<<endl;
             }
             int full()
             {
                 return (((front+1)%size)==rear);
             }
             int empty()
             {
                 return (rear==front);
             }
};

//execute
int main()
{
    Queue buff1(15);
    buff1.enque(52);
    buff1.enque(41);
    buff1.enque(3);
    buff1.enque(100);
    buff1.enque(88);
    for(int i=0;i<5;i++)
        cout<<buff1.deque()<<" ";
    cout<<endl;
    
    system("pause");
    return 0;
}
