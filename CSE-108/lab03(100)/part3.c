#include <stdio.h>

int main() {
    char operation;
    int num1, num2, result, answer;
    printf("\n");
    printf("Enter an arithmetic operation (+, -, *, /): ");
    scanf(" %c", &operation);
    
    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);
    
    switch (operation) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            result = num1 / num2;
            break;
        default:
            printf("Invalid operation.\n");
            return 0;
    }
    
    printf("Result: ");
    scanf("%d", &answer);
    
    if (answer == result) {
        printf("Bravo, correct answer!\n");
    } else {
        printf("Wrong answer, try again.\n");
    }
    printf("\n");
    
    return 0;
}