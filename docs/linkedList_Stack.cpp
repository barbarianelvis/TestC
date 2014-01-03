#include <iostream>
#include <cstdlib>
using namespace std;

typedef struct node{
 	int data;
 	struct node *next;
}node;

node *top = NULL;

static void push(int num);
static void pop();
static void display();
static int minimum(node *temp);
static node* reverse_recur(node *x,node *y);

int main(void)
{

	while(1){
  		int sel;
  		printf("[Stack]\t(1)push (2)pop (3)display (4)min (5)reverse >> ");
  		if(scanf("%d",&sel)==EOF) break;

  		int temp;
  		switch(sel){
   			case 1:
    			printf("push >> ");
    			scanf("%d",&temp);
    			push(temp);
    			break;

   			case 2:
    			pop();
    			break;
    		
   			case 3:
    			display();
    			break;
    			
    		case 4:
    			cout << minimum(top) << endl;
    			break;
    			
    		case 5:
    			top = reverse_recur(top, NULL);
    			break;

   			default:
    			printf("Wrong Selection.\n");
  		}
 	}
 //end
 	printf("Exit Program.\n");
 	return 0;
}

static void push(int num){

 	node *temp;

 	temp = (struct node *)malloc(sizeof(struct node));
 	temp->data = num;
 	temp->next = top;
 	top = temp;

}

static void pop(){

 	if(top!=NULL){
  		printf("pop : %d\n", top->data);
  		top = top->next;
 	}
 	else
  		printf("Stack Bottom.\n");
}

static void display(){
	node *ptr = top;

 	while(ptr){
  		printf("%d\n", ptr->data);
  		ptr = ptr->next;

 	}
}

static int minimum(node *temp){
	int min=10;
	while(temp->next!=NULL){
		if(temp->next->data <= min)
			min = temp->next->data;
		return min;
	}
}

static node* reverse_recur(node *x,node *y){
       if(x==NULL)return y;
       
       else{
           node *tmp;

           tmp = reverse_recur(x->next,x);
           x->next=y;
           return tmp;
    }
}
