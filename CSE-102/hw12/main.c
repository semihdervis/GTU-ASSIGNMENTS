#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Node { 
    void* data; 
    struct Node* next; 
} Node;

typedef struct {
    char type[20];
    int ivals[1];
    double svals[1];
} Asset1;

typedef struct {
    char type[20];
    double svals[2];
    int ivals[2];
} Asset2;

typedef struct {
    char type[20];
    char string1[50];
    char string2[50];
} Asset3;

typedef struct {
    char type[20];
    double value1;
    float value2;
    double value3;
} Asset4;

void fillLinkedList(struct Node** head) {
    srand(time(NULL));
    Node* current = NULL;
    Node* newNode = NULL;
    int numAssets = (rand() % 11) + 10;
    int assetType;
    for (int i = 0; i < numAssets; i++) {
        Node* newNode;
        assetType = rand() % 4;
        switch (assetType) {
            case 0: {
                newNode = (Node*)malloc(sizeof(Node));
                newNode->next = NULL;
                Asset1* a1 = (Asset1*)malloc(sizeof(Asset1));
                strcpy(a1->type, "Asset1");
                a1->ivals[0] = rand() % 100;
                a1->svals[0] = (double)rand() / RAND_MAX;
                newNode->data = a1;
                break;
            }
            case 1: {               
                newNode = (Node*)malloc(sizeof(Node));
                newNode->next = NULL;
                Asset2* a2 = (Asset2*)malloc(sizeof(Asset2));
                strcpy(a2->type, "Asset2");
                a2->ivals[0] = rand() % 100;
                a2->ivals[1] = rand() % 100;
                a2->svals[0] = (double)rand() / RAND_MAX;
                a2->svals[1] = (double)rand() / RAND_MAX;
                newNode->data = a2;
                break;
            }
            case 2: {
                newNode = (Node*)malloc(sizeof(Node));
                newNode->next = NULL;
                Asset3* a3 = (Asset3*)malloc(sizeof(Asset3));
                strcpy(a3->type, "Asset3");
                strcpy(a3->string1, "string1");
                strcpy(a3->string2, "string2");
                newNode->data = a3;
                break;
            }
            case 3: {
                newNode = (Node*)malloc(sizeof(Node));
                newNode->next = NULL;
                Asset4* a4 = (Asset4*)malloc(sizeof(Asset4));
                strcpy(a4->type, "Asset4");
                a4->value1 = (double)rand() / RAND_MAX;
                a4->value2 = (float)rand() / RAND_MAX;
                a4->value3 = (double)rand() / RAND_MAX;
                newNode->data = a4;
                break;
            }
        }
        if (current != NULL) {
            current->next = newNode;
        } 
        else {
            *head = newNode;
        }
        current = newNode;
    }
    if (current != NULL) {
        current->next = NULL;
    }
}

void serializeLinkedList(struct Node* head) {
    FILE* fp = fopen("linkedlist.bin", "wb");
    Node* current = head;
    while (current != NULL) {
        switch (((char*)current->data)[5]) {
            case '1': 
                fwrite(current->data, sizeof(Asset1), 1, fp);
                break;
            case '2': 
                fwrite(current->data, sizeof(Asset2), 1, fp);
                break;
            case '3': 
                fwrite(current->data, sizeof(Asset3), 1, fp);
                break;
            case '4': 
                fwrite(current->data, sizeof(Asset4), 1, fp);
                break;
        }
        current = current->next;
    }
    fclose(fp);
}

void deserializeLinkedList(struct Node** head) {
    FILE* fp = fopen("linkedlist.bin", "rb");
    Node* current = *head;
    char arr[6];
    while (current != NULL) {
        fread(arr, sizeof(char), 6, fp);
        fseek(fp, -6, SEEK_CUR);
        switch (arr[5]) {
            case '1': {   
                Asset1* a1 = (Asset1*)current->data;
                fread(a1, sizeof(Asset1), 1, fp);
                break;
            }
            case '2': {
                Asset2* a2 = (Asset2*)current->data;
                fread(a2, sizeof(Asset2), 1, fp);
                break;
            }
            case '3': {
                Asset3* a3 = (Asset3*)current->data;
                fread(a3, sizeof(Asset3), 1, fp);
                break;
            }
            case '4': {
                Asset4* a4 = (Asset4*)current->data;
                fread(a4, sizeof(Asset4), 1, fp);
                break;
            }
            default:
                printf("Error");
        }
        current = current->next;
    }
}

void printLinkedList(struct Node* head) {
    Node* current = head;
    int counter = 1;
    while (current != NULL) {
        printf("%d-) ", counter);
        switch (((char*)current->data)[5]) {
            case '1': {
                Asset1* a1 = (Asset1*)current->data;
                printf("%s %d %lf\n", a1->type, a1->ivals[0], a1->svals[0]);
                break;
            }
            case '2': {
                Asset2* a2 = (Asset2*)current->data;
                printf("%s %d %d %lf %lf\n", a2->type, a2->ivals[0], a2->ivals[1], a2->svals[0], a2->svals[1]);
                break;
            } 
            case '3': {
                Asset3* a3 = (Asset3*)current->data;
                printf("%s %s %s\n", a3->type, a3->string1, a3->string2);
                break;
            } 
            case '4': {
                Asset4* a4 = (Asset4*)current->data;
                printf("%s %lf %f %lf\n", a4->type, a4->value1, a4->value2, a4->value3);
                break;
            } 
        }
        current = current->next;
        counter++;
    }
}

void freeLinkedList(struct Node* head) {
    Node* current = head;
    Node* next = NULL;
    while (current != NULL) {
        next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    head = NULL;
    printf("\nLinked list freed\n\n");
}

int main() {
    struct Node* head = NULL;
    
    fillLinkedList(&head);

    printf("\nLinked list before serialization and deserialization:\n");
    printLinkedList(head);

    serializeLinkedList(head);

    deserializeLinkedList(&head);

    printf("\nLinked list after serialization and deserialization:\n");
    printLinkedList(head);

    freeLinkedList(head);
    
    return 0;
}