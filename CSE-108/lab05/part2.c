#include <stdio.h>

int main() {
    int number, reversedNumber = 0, digitCount = 0;
    
    printf("\nEnter a number (3, 4, or 5): ");
    scanf("%d", &number);
    
    int temp = number;  // finds number of digit
    while (temp != 0) {
        digitCount++;
        temp /= 10;
    }
    
    if (digitCount < 3 || digitCount > 5) {  // error 
        printf("Invalid input. Number must have 3, 4, or 5 digits.\n");
        return 0;
    }
    
    while (number != 0) {  // reverse
        reversedNumber = reversedNumber * 10 + number % 10;
        number /= 10;
    }
    
    printf("Reversed number: %d\n\n", reversedNumber);  
    
    return 0;
}