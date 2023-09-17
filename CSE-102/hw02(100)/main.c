#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int factorial(int n) {
    int f = 1;
    for(int i = 1; i <= n; i++) f *= i;
    return f;
}

int number_of_digits(double num){
    int count = 0;
    int intNum = (int)num; // truncate decimal part
    while (intNum != 0) {
        count++;
        intNum /= 10;
    }
    return count;
}

void print_scientific_format(double num, int m, int n){
    int len = number_of_digits(num);
    while(fabs(num) >= 1) num /= 10;  
    while(fabs(num) < 0.1) num *= 10;
    num *= pow(10, m - n);
    printf("%.*lfe%d", n, num, len - (m - n));
}

void leap_year(){ // part 1
    int year;
    printf("Please enter a year: ");
    scanf("%d", &year);
    if(year % 4 == 0){
        if(year % 100 == 0){
            if(year % 400 == 0) printf("%d is a leap year", year);
            else printf("%d is not a leap year", year);
        }
        else printf("%d is a leap year", year);
    }
    else printf("%d is not a leap year", year);
    printf("\n\n");
}

void enhanced_calculator(){ // part 2
    char format;
    double result;
    int m, n;
    printf("Enter the format of output (S or I): ");
    scanf(" %c", &format);
    switch(format){
        case 'S':
        case 's':
            printf("Enter m and n values: ");
            scanf(" %d %d", &m, &n);
            if (n > m) {
                printf("Error: n > m.\n\n");
                return;
            }
            break;
        case 'I':
        case 'i':
            break;
        default:
            printf("Error: Invalid format\n");
            exit(0);
    }
    char operator;
    double operand1, operand2;
    printf("Enter the operation(+,-,/,*,%%,!,^): ");  
    scanf(" %c", &operator); 
    switch(operator){
        case '+':
            printf("Enter the first operand: ");
            scanf(" %lf", &operand1);
            printf("Enter the second operand: ");
            scanf(" %lf", &operand2);
            result = operand1 + operand2;
            break;
        case '-':
            printf("Enter the first operand: ");
            scanf(" %lf", &operand1);
            printf("Enter the second operand: ");
            scanf(" %lf", &operand2);
            result = operand1 - operand2;
            break;
        case '*':
            printf("Enter the first operand: ");
            scanf(" %lf", &operand1);
            printf("Enter the second operand: ");
            scanf(" %lf", &operand2);
            result = operand1 * operand2;
            break;
        case '/':
            printf("Enter the first operand: ");
            scanf(" %lf", &operand1);
            printf("Enter the second operand: ");
            scanf(" %lf", &operand2);
            if (operand2 == 0) {
                printf("Error: Division by zero.\n");
                exit(0);
            }
            result = operand1 / operand2;
            break;
        case '!':
            printf("Enter the operand: ");
            scanf(" %lf", &operand1);
            if (operand1 < 0) {
                printf("Error: Factorial of a negative number.\n");
                exit(0);
            }
            result = factorial(operand1);
            break;
        case '^':
            printf("Enter the first operand: ");
            scanf(" %lf", &operand1);
            printf("Enter the second operand: ");
            scanf(" %lf", &operand2);
            result = pow(operand1, operand2);
            break;
        case '%':
            printf("Enter the first operand: ");
            scanf(" %lf", &operand1);
            printf("Enter the second operand: ");
            scanf(" %lf", &operand2);
            result = fmod(operand1, operand2);
            break;
        default:
            printf("Invalid operator.\n");
            exit(0);
    }
    if(operator == '!') printf("%.0lf! = ", operand1);
    else printf("%g %c %g = ", operand1, operator, operand2);
    if(format == 's' || format == 'S') print_scientific_format(result, m, n);
    else printf("%.0lf", result);
    printf("\n\n");
}

void grade_calculator(){ // part 3
    double exam1, exam2, exam3, assignment1, assignment2;
    printf("Enter 3 exam grades of student: ");
    scanf(" %lf %lf %lf", &exam1, &exam2, &exam3);
    printf("Enter 2 assignment grades of student: ");
    scanf(" %lf %lf", &assignment1, &assignment2);
    double final_grade = (exam1 + exam2 + exam3) / 3 * 0.6 + (assignment1 + assignment2) / 2 * 0.4;
    printf("Final Grade: %lf ", final_grade);
    if(final_grade >= 60) printf("Passed!");
    else printf("Failed!");
    printf("\n\n");
}

void main(){
    printf("\n");
    leap_year();
    enhanced_calculator();
    grade_calculator();
    printf("\n");
}