#include <stdio.h>
#include <string.h>

typedef struct node {
    char name[20];
    int age;
    struct node* father;
    struct node* mother;
} node;

int fileExists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        fclose(file);
        return 1;  // File exists
    }
    return 0;  // File does not exist
}

int numFile() {
    char fileName[30];
    int counter = 1;
    do {
        sprintf(fileName, "Family%d.txt", counter);
        counter++;
    } while (fileExists(fileName));
    return counter - 1;
}

FILE* createFile(int num) {
    char fileName[30];
    sprintf(fileName, "Family%d.txt", num);
    FILE *file = fopen(fileName, "w");
    return file;
}

void addFamilyTree() {
    FILE* file = createFile(numFile());
    
    int choice;
    char name[50];
    int age;
    char motherName[50];
    char fatherName[50];
    
    while (1) {
        printf("Menu:\n");
        printf("1 - Add node\n");
        printf("2 - Save Family Tree\n");
        printf("3 - Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter the name of the person: ");
                scanf("%s", name);
                
                printf("Enter the age of the person: ");
                scanf("%d", &age);
                
                printf("Enter the name of the mother: ");
                scanf("%s", motherName);
                
                printf("Enter the name of the father: ");
                scanf("%s", fatherName);

                fprintf(file, "%s %d %s %s\n", name, age, motherName, fatherName);
                break;
                
            case 2:
                printf("Saving Family Tree...\n");
                fflush(file);
                break;
                
            case 3:
                printf("Exiting...\n");
                return;
                
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    fclose(file);   
}

void removeFamilyTree() {

    char fileName[30];

    printf("Enter the name of the txt file of the family tree: ");
    scanf("%s", fileName);

    if (remove(fileName) == 0) {
        printf("%s has been removed successfully...\n", fileName);
    }
    else {
        printf("Unable to delete the file.\n");
    }
}

int displayFiles() {
    char fileName[30];
    int counter = 1;
    for (int i = 1; i <= 10; i++) {
        sprintf(fileName, "Family%d.txt", i);
        if (fileExists(fileName)) {
            printf("%d-", counter);
            printf("%s\n", fileName);
            counter++;
        }
    }
    return counter;
}

void selectedFile(char file_name[], int num) {
    char fileName[30];
    int counter = 1;
    for (int i = 1; i <= 10; i++) {
        sprintf(fileName, "Family%d.txt", i);
        if (fileExists(fileName)) {
            if (counter == num) {
                FILE *file = fopen(fileName, "r");
                printf("%s has been selected...\n", fileName);
                strcpy(file_name, fileName);
                return;
            }
            counter++;
        }
    }
}

struct Person {
    char name[50];
    int age;
    char mother[50];
    char father[50];
};

struct Person people[100];
int count = 0;

void addPerson() {
    struct Person newPerson;
    printf("Enter name: ");
    scanf("%s", newPerson.name);
    printf("Enter age: ");
    scanf("%d", &newPerson.age);
    printf("Enter mother's name: ");
    scanf("%s", newPerson.mother);
    printf("Enter father's name: ");
    scanf("%s", newPerson.father);

    people[count] = newPerson;
    count++;
    printf("Person added successfully!\n");
}

void removePerson() {
    char name[50];
    printf("Enter the name of the person to remove: ");
    scanf("%s", name);

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(people[i].name, name) == 0) {
            for (int j = i; j < count - 1; j++) {
                people[j] = people[j + 1];
            }
            count--;
            found = 1;
            break;
        }
    }

    if (found) {
        printf("Person removed successfully!\n");
    } else {
        printf("Person not found.\n");
    }
}

void printNuclearFamily() {
    char name[50];
    printf("Enter the name of the person: ");
    scanf("%s", name);

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(people[i].name, name) == 0) {
            printf("Printing nuclear family of %s:\n", name);
            printf("Father: %s\n", people[i].father);
            printf("Mother: %s\n", people[i].mother);

            printf("Siblings: ");
            for (int j = 0; j < count; j++) {
                if (j != i && (strcmp(people[j].mother, people[i].mother) == 0 || strcmp(people[j].father, people[i].father) == 0)) {
                    printf("%s, ", people[j].name);
                }
            }
            printf("\n");

            printf("Children: ");
            for (int j = 0; j < count; j++) {
                if (strcmp(people[j].mother, name) == 0 || strcmp(people[j].father, name) == 0) {
                    printf("%s, ", people[j].name);
                }
            }
            printf("\n");

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Person not found.\n");
    }
}

void searchRelatives() {
    char name[50];
    printf("Enter the name of the person: ");
    scanf("%s", name);

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(people[i].name, name) == 0) {
            int choice;
            printf("Select type of relatives:\n");
            printf("1 - Parents\n");
            printf("2 - Spouse\n");
            printf("3 - Children\n");
            printf("4 - Grandparents\n");
            printf("5 - Cousins\n");
            printf("> ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    printf("Printing parents of %s:\n", name);
                    printf("Father: %s\n", people[i].father);
                    printf("Mother: %s\n", people[i].mother);
                    break;
                case 2:
                    printf("Printing spouse of %s:\n", name);
                    for (int j = 0; j < count; j++) {
                        if (strcmp(people[j].name, name) != 0 && (strcmp(people[j].mother, people[i].mother) == 0 || strcmp(people[j].father, people[i].father) == 0)) {
                            printf("Spouse: %s\n", people[j].name);
                            break;
                        }
                    }
                    break;
                case 3:
                    printf("Printing children of %s:\n", name);
                    for (int j = 0; j < count; j++) {
                        if (strcmp(people[j].mother, name) == 0 || strcmp(people[j].father, name) == 0) {
                            printf("%s\n", people[j].name);
                        }
                    }
                    break;
                case 4:
                    printf("Printing grandparents of %s:\n", name);
                    for (int j = 0; j < count; j++) {
                        if ((strcmp(people[j].mother, people[i].mother) == 0 || strcmp(people[j].father, people[i].father) == 0) &&
                            (strcmp(people[j].mother, people[i].father) != 0 && strcmp(people[j].father, people[i].mother) != 0)) {
                            printf("%s\n", people[j].name);
                        }
                    }
                    break;
                case 5:
                    printf("Printing cousins of %s:\n", name);
                    for (int j = 0; j < count; j++) {
                        if ((strcmp(people[j].mother, people[i].mother) == 0 || strcmp(people[j].father, people[i].father) == 0) &&
                            (strcmp(people[j].name, name) != 0)) {
                            printf("%s\n", people[j].name);
                        }
                    }
                    break;
                default:
                    printf("Invalid choice.\n");
                    break;
            }


            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Person not found.\n");
    }
}

int loadFamilyTree() {
    int choice;
    count = 0;

    displayFiles();
    scanf("%d", &choice);
    char fileName[50];

    node* family = NULL;
    selectedFile(fileName, choice);

    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    while (!feof(file)) {
        fscanf(file, "%s %d %s %s", people[count].name, &people[count].age, people[count].mother, people[count].father);
        count++;
    }

    fclose(file);

    do {
        printf("Select an operation:\n");
        printf("1 - Add new person\n");
        printf("2 - Remove a person\n");
        printf("3 - Print a Person's nuclear family\n");
        printf("4 - Search Relatives of Given Person\n");
        printf("5 - Return to the main menu\n");
        printf("> ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addPerson();
                break;
            case 2:
                removePerson();
                break;
            case 3:
                printNuclearFamily();
                break;
            case 4:
                searchRelatives();
                break;
            case 5:
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    } while (choice != 5);

    file = fopen(fileName, "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %d %s %s\n", people[i].name, people[i].age, people[i].mother, people[i].father);
    }

    fclose(file);

    return 0;
}


int main() {
    int choice;
    while (1) {
        printf("Family Tree System Menu:\n");
        printf("1-Add Family Tree\n");
        printf("2-Remove Family Tree\n");
        printf("3-Load Family Tree\n");
        printf("4-Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addFamilyTree();
                break;
            case 2:
                removeFamilyTree();
                break;
            case 3:
                loadFamilyTree();
                break;
            case 4:
                printf("Exiting...\n");
                return 0;                
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    
    return 0;
}