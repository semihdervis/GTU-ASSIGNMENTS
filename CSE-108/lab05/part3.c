#include <stdio.h>

int decimalToBinary(int decimal) {  // conversion to binary
    int binary = 0;
    int remainder, factor = 1;

    while (decimal != 0) {
        remainder = decimal % 2;
        decimal /= 2;
        binary += remainder * factor;
        factor *= 10;
    }

    return binary;
}

int main() {
    int choice, decimal;

    do {
        printf("\nMenu:\n");  // menu
        printf("1. Convert a number to decimal, binary, octal, and hexadecimal\n");
        printf("2. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter a number: ");
                scanf("%d", &decimal);

                printf("Decimal equivalent: %d\n", decimal);
                printf("Binary equivalent: %d\n", decimalToBinary(decimal));
                printf("Octal equivalent: %o\n", decimal);
                printf("Hexadecimal equivalent: %X\n", decimal);

                break;

            case 2:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice! Please enter 1 or 2.\n");
        }
    } while (choice != 2);

    return 0;
}
