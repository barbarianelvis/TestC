#include <stdio.h>
#include <string.h>

int main() {
    struct Ball ball1 = {"red", 5.0};

    struct Ball ball2;
    strcpy(ball2.color, "green");
    ball2.radius = 10.0;
    
    printf("ball1: %s,\t%.2f\n", ball1.color, ball1.radius);
    printf("ball2: %s,\t%.2f\n", ball2.color, ball2.radius);  
	  
	system("pause");        
    return 0;
}
