#include <stdio.h>

void displayMenu() {  // menu function
    printf("\nTemperature Conversion Menu\n");
    printf("1. Convert Celsius to Fahrenheit\n");
    printf("2. Convert Fahrenheit to Celsius\n");
    printf("3. Quit\n");
}

float getUserInput() {  // input function
    float temperature;
    printf("Enter the temperature value to convert: ");
    scanf("%f", &temperature);
    return temperature;
}

void convertTemperature(int choice, float temperature) {  // conversion
    float convertedTemperature;
    if (choice == 1) {
        convertedTemperature = (temperature * 9 / 5) + 32;
        printf("%.2f Celsius = %.2f Fahrenheit\n", temperature, convertedTemperature);
    }
    else {
        convertedTemperature = (temperature - 32) * 5 / 9;
        printf("%.2f Fahrenheit = %.2f Celsius\n", temperature, convertedTemperature);
    }
}

int main() {
    int choice;
    float temperature;

    do {
        displayMenu();
        printf("Enter your choice (1-3): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                temperature = getUserInput();
                convertTemperature(choice, temperature);
                break;
            case 2:
                temperature = getUserInput();
                convertTemperature(choice, temperature);
                break;
            case 3:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}
