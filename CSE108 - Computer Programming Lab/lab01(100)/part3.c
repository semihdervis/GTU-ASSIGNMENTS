#include "stdio.h"

void main(){
    int age, exp, salary = 0;
    printf("enter your age: ");
    scanf("%d", &age);
    printf("enter years of experience: ");
    scanf("%d", &exp);
    if(age < 20){
        if(exp > 0 && exp < 10) salary = 10000;
        else printf("error!\n");
    }
    else if(age > 20 && age < 50){
        if(exp > 0 && exp < 10) salary = 15000;
        else salary = 20000;
    }
    else{
        if(exp > 0 && exp < 10) salary = 20000;
        else salary = 25000;
    }
    if(salary != 0) printf("your salary: %d\n", salary);
}