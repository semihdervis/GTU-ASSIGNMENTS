#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 100

// struct definition for furniture items
typedef struct {
    char name[50];
    char color[20];
    float price;
    int serial_num;
    int quantity;
} Furniture;

// function prototypes
int load_database(Furniture db[]);
void write_database(Furniture db[], int num_items);
void print_item(Furniture item);
void print_database(Furniture db[], int num_items);
void add_item(Furniture db[], int *num_items);
void remove_item(Furniture db[], int *num_items);
void search_by_name(Furniture db[], int num_items, char search_name[]);
void search_by_color(Furniture db[], int num_items, char search_color[]);
void search_menu(Furniture db[], int num_items);

int main() {
    Furniture db[MAX_ITEMS];
    int num_items;

    // load the database from file
    num_items = load_database(db);

    int choice;
    do {
        printf("\nWelcome to the database of furniture shop\n");
        printf("1-See all furnitures\n");
        printf("2-Add a new furniture\n");
        printf("3-Remove furniture\n");
        printf("4-Search furniture\n");
        printf("5-Exit\n");
        printf("> ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                print_database(db, num_items);
                break;
            case 2:
                add_item(db, &num_items);
                write_database(db, num_items);
                break;
            case 3:
                remove_item(db, &num_items);
                write_database(db, num_items);
                break;
            case 4:
                search_menu(db, num_items);
                break;
            case 5:
                printf("Program terminated...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
                break;
        }
    } while (choice != 5);

    return 0;
}

// load the database from file
int load_database(Furniture db[]) {
    FILE *file;
    int num_items = 0;

    file = fopen("furniture_database.txt", "r");

    if (file) {
        while (fscanf(file, "%s %s %f %d %d", db[num_items].name, db[num_items].color, &db[num_items].price, &db[num_items].serial_num, &db[num_items].quantity) == 5) {
            num_items++;
        }
        fclose(file);
    } else {
        printf("Error: Could not open file for reading.\n");
    }

    return num_items;
}

// write the database to file
void write_database(Furniture db[], int num_items) {
    FILE *file;

    file = fopen("furniture_database.txt", "w");

    for (int i = 0; i < num_items; i++) {
        fprintf(file, "%s %s %.2f %d %d\n", db[i].name, db[i].color, db[i].price, db[i].serial_num, db[i].quantity);
    }

    fclose(file);
}

// print a single furniture item
void print_item(Furniture item) {
    printf("Name: %s\n", item.name);
    printf("Color: %s\n", item.color);
    printf("Price: $%.2f\n", item.price);
    printf("Serial Number: %06d\n", item.serial_num);
    printf("Quantity: %d\n", item.quantity);
    printf("\n");
}

void print_database(Furniture db[], int num_items) {
    for (int i = 0; i < num_items; i++) {
        print_item(db[i]);
    }
}

void add_item(Furniture db[], int *num_items) {
    Furniture new_item;
    printf("Please enter the properties of the new furniture (Name, Color, Price, Serial Number, Quantity): ");
    scanf("%s %s %f %d %d", new_item.name, new_item.color, &new_item.price, &new_item.serial_num, &new_item.quantity);
    db[*num_items] = new_item;
    (*num_items)++;
    printf("Following furniture is added to the database:\n");
    print_item(new_item);
}

void remove_item(Furniture db[], int *num_items) {
    int index;
    printf("Enter the index of the product you want to remove: ");
    scanf("%d", &index);
    if (index < 0 || index >= *num_items) {
        printf("Invalid index.\n");
    } else {
        Furniture removed_item = db[index];
        for (int i = index; i < *num_items - 1; i++) {
            db[i] = db[i+1];
        }
        (*num_items)--;
        printf("Following furniture is removed from the database:\n");
        print_item(removed_item);
    }
}

void recursive_search_by_name(Furniture db[], int num_items, char search_name[]) {
    if (num_items == 0) {
        return;
    }
    if (strcmp(db[0].name, search_name) == 0) {
        print_item(db[0]);
    }
    recursive_search_by_name(db + 1, num_items - 1, search_name);
}

void recursive_search_by_color(Furniture db[], int num_items, char search_color[]) {
    if (num_items == 0) {
        return;
    }
    if (strcmp(db[0].color, search_color) == 0) {
        print_item(db[0]);
    }
    recursive_search_by_color(db + 1, num_items - 1, search_color);
}

void search_menu(Furniture db[], int num_items) {
    int choice;
    char search_query[100];
    printf("Select a property to make search:\n");
    printf("1-Name\n");
    printf("2-Color\n");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            printf("Enter the name of the product: ");
            scanf("%s", search_query);
            printf("Results:\n");
            recursive_search_by_name(db, num_items, search_query);
            break;
        case 2:
            printf("Enter the color of the product: ");
            scanf("%s", search_query);
            printf("Results:\n");
            recursive_search_by_color(db, num_items, search_query);
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
}



