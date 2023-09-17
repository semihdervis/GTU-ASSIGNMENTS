#include <stdio.h>
#include "util.h"

void gcd(){ // part 1
    printf("***------PART 1------***\n"); 
    int num1, num2;
    printf("First number: "); 
    scanf("%d", &num1);    
    printf("Second number: ");
    scanf("%d", &num2); 
    while(num2 > 0){       // calculates gcd with euclidean algorithm
        int r = num1 % num2;
        num1 = num2;
        num2 = r;
    }
    printf("GCD is: %d", num1);
}

void sum(){ // part 2
    printf("\n\n***------PART 2-------***\n");
    int num1, num2;
    printf("First number: ");
    scanf("%d", &num1);    
    printf("Second number: ");
    scanf("%d", &num2);    
    printf("\n%7d\n%7d\n+\n-------\n%7d", num1, num2, num1 + num2);
}

void mult(){ // part 3
    printf("\n\n***------PART 3------***\n");
    int num1, num2;
    printf("First number: ");
    scanf("%d", &num1);    
    printf("Second number: ");
    scanf("%d", &num2); 
    int number_of_digits, holder = num2;
    for(number_of_digits = 1; holder /= 10; number_of_digits++); // calculates the number of the digits of the second number
    holder = num2;
    printf("\n%9d\n%9d\n*\n---------\n", num1, num2);
    for(int j = 0; j < number_of_digits; j++){ 
        int digit = holder % 10;    // extracts each digit of second number
        holder /= 10; 
        printf("%*d\n", 9 - j, digit * num1); // prints each step of manual multiplication
    }
    if(number_of_digits != 1) printf("+\n---------\n%9d", num1 * num2);  
                                                                    
}

void check(){ // part 4
    printf("\n\n***------PART 4------***\n");
    printf("Enter an integer between 1 and 10: ");
    int num;
    scanf("%d", &num);
    if(num >= 1 && num <= 10){
        if(num <= 5) printf("The integer you entered is less than or equal to 5");
        else printf("The integer you entered is greater than 5");
    }
    else printf("Invalid input");
    printf("\n\n");
}
