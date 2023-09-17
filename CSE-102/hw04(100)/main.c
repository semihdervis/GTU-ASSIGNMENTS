#include "stdio.h"
#include "time.h"
#include "stdlib.h"

void print_menu(FILE* fp) {  // prints menu to user without their price
    char c;
    double num;
    int counter = 1;
    printf("Yemek Listesi:\n");
    while (fscanf(fp, "%c", &c) != EOF) {
        if (c =='\n') {
            if (counter != 1) printf("\n");  
            printf("%d. ", counter);  // prints order of the food in menu
            counter++;
        }
        else if ((c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') && counter != 1) {  // checks if they are letters
            printf("%c", c);
        }
        else;
    }
    printf("\n");
}

void print_current_time(FILE* fp) {  // prints current time to receipt
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    fprintf(fp, "%02d.%02d.%d/%02d:%02d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year+1900, tm.tm_hour, tm.tm_min);
}

double print_selected_line(FILE* fp1, int line, FILE* fp2, int services) {  // prints selected food and price to receipt
    int counter = 0;
    char c;
    double num;
    int noc = 0;
    fseek(fp1, 0, SEEK_SET); 
    if (services != 1) {
        fprintf(fp2, "%d* ", services);
    }
    while (fscanf(fp1, "%c", &c) != EOF) {
        if (c == '\n') {
            counter++;
        }
        if (counter == line) {
            if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') {  //checks if they are letters
                fprintf(fp2, "%c", c);
                noc++; 
            }
            else if (c == ' ') {
                if (services == 1) for(int i = 0; i < 26 - noc; i++) fprintf(fp2, " ");  // prints enough space to arrange prices
                else for(int i = 0; i < 23 - noc; i++) fprintf(fp2, " ");
                fscanf(fp1, "%lf", &num);
                fprintf(fp2, "%.2lf\n", num * services);
            }
            else;
        }
    }
    return num;
}

void take_order(FILE* menu, FILE* receipt) {  // takes order from user and creates receipt
    int product, num, a, repeat = 1;
    char c, stu;
    double sum = 0, discount = 0, vat;

    fprintf(receipt, "220104004021        ");
    print_current_time(receipt);
    fprintf(receipt, "------------------------------------\n");
    fprintf(receipt, "Product                 Price (TL)  \n");
    fprintf(receipt, "------------------------------------\n");
    while (1) {
        printf("Please choose a product (1-10): ");
        scanf("%d", &product);
        if (product == 0) break;  

        printf("How many servings do you want: ");
        scanf("%d", &num);
        if (num == 0) break; 

        sum += (double)num * print_selected_line(menu, product, receipt, num);
    }
    fprintf(receipt, "Total:                    %.2lf\n", sum);
    if (sum >= 150) {
        fprintf(receipt, "150 discount:             -%.2lf\n", (sum * 0.1));
        discount += (sum * 0.1);  
    }
    
    printf("Are you student? (Y/N): ");
    while (repeat) {
        scanf(" %c", &stu);
        switch (stu) {
            case 'Y':
            case 'y':
                fprintf(receipt, "Student discount:         -%.2lf\n", sum * (12.5 / 100.0)); // calculates and prints student discount
                discount += sum * (12.5 / 100.0); 
                repeat = 0;
                break; 
            case 'N':
            case 'n':
                repeat = 0;
                break;
            default:
                printf("Please enter a valid answer: ");
        }
    }
    fprintf(receipt, "------------------------------------\n");
    sum -= discount;  // subtract discounts from price
    fprintf(receipt, "Price:                    %.2lf\n", sum);
    vat = sum * (18.0 / 100.0);  // calculates VAT
    sum += vat;  // add VAT to price
    fprintf(receipt, "Price + VAT:              %.2lf\n", sum);
}

void print_file(FILE* fp) {  // prints all receipt to terminal
    fseek(fp, 0, SEEK_SET);
    char c;
    while (fscanf(fp, "%c", &c) != EOF) {
        printf("%c", c);
    }
}

void part1() {  // Part 1
    FILE* menu = fopen("menu.txt", "r");  // opens menu read only mode
    FILE* receipt = fopen("receipt.txt", "w+");  // opens receipt read and write mode

    if (menu == NULL || receipt == NULL) {
        printf("Error opening file\n");
        return;
    }
    print_menu(menu);
    take_order(menu, receipt);
    printf("\n");
    print_file(receipt);
    printf("\n");
    
    fclose(menu);
    fclose(receipt);
}

void name(int num) {  // prints names for selected number
    if (num == 1) printf("Stone");
    else if (num == 2) printf("Paper");
    else printf("Scissors");
}

void show_status(int my_choice, int his_choice) {  // prints his and my selection
    printf("You chose ");
    name(his_choice);
    printf(". I chose ");
    name(my_choice);
}

void part2() {  // Part 2
    int his_choice, my_choice;
    char again;
    do {
        printf("Please make a choice!\n");
        printf("1: Stone, 2: Paper, 3: Scissors\nEnter: ");
        scanf("%d", &his_choice);

        while (his_choice > 3 || his_choice < 1) { // checks if the user enter a valid input
            printf("Invalid choice. Enter again: ");
            scanf("%d", &his_choice);
        } 

        srand(time(NULL));
        my_choice = (rand() % 3) + 1;  // randomly choose 

        show_status(my_choice, his_choice);

        if (my_choice == his_choice + 1 || (his_choice == 3 && my_choice == 1)) printf(". You lost!");  // conditions for win or lose
        else if (my_choice == his_choice) printf(". It's a tie!");  
        else printf(". You won!");
        
        printf("\nDo you want to play again? (Y/N): ");
        scanf(" %c", &again);
        printf("\n");
    } while (again == 'y'); 
    printf("\n");
}

int main() {
    part1();
    part2();

    return 0;
}