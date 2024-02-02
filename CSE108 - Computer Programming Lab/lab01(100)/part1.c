#include "stdio.h"

void main(){
    int num;
    printf("enter an integer value between 1 and 100: ");
    scanf("%d", &num);
    if(num % 3 == 0){
        if(num > 5 && num < 50){
            printf("FizzBuzz");
        }
        else{
            printf("Fizz");
        }
    }
    else{
        printf("Buzz");
    }
    printf("\n");
}