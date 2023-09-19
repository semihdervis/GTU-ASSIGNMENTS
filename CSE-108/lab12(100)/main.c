#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_GROUP_LENGTH 10
#define FILENAME "customers.txt"

typedef struct {
    char name[MAX_NAME_LENGTH];
    int age;
    char priorityGroup[MAX_GROUP_LENGTH];
    int priorityLevel;
} Customer;

typedef struct Node {
    Customer customer;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
} PriorityQueue;

void initializePriorityQueue(PriorityQueue* queue);
int isPriorityQueueEmpty(PriorityQueue* queue);
void insertCustomer(PriorityQueue* queue, Customer customer);
void removeCustomer(PriorityQueue* queue, const char* name);
void displayCustomers(PriorityQueue* queue);
void searchCustomer(PriorityQueue* queue, const char* name);
void changePriority(PriorityQueue* queue, const char* name, int newPriority);
void writeCustomersToFile(PriorityQueue* queue);
void readCustomersFromFile(PriorityQueue* queue);

int main() {
    PriorityQueue queue;
    initializePriorityQueue(&queue);
    readCustomersFromFile(&queue);

    int option;
    do {
        printf("\nWelcome to the ABC Bank\n");
        printf("1-Insert new customer\n");
        printf("2-Remove customer\n");
        printf("3-Display customers in order\n");
        printf("4-Search a customer\n");
        printf("5-Change priority settings\n");
        printf("6-Exit\n");
        printf("Please select an option: ");
        scanf("%d", &option);
        getchar(); // Clear input buffer

        switch (option) {
            case 1: {
                Customer newCustomer;
                printf("Please enter customer's Name: ");
                fgets(newCustomer.name, MAX_NAME_LENGTH, stdin);
                newCustomer.name[strcspn(newCustomer.name, "\n")] = '\0'; // Remove trailing newline character
                printf("Please enter customer's Age: ");
                scanf("%d", &newCustomer.age);
                getchar(); // Clear input buffer
                printf("Please enter customer's Priority Group: ");
                fgets(newCustomer.priorityGroup, MAX_GROUP_LENGTH, stdin);
                newCustomer.priorityGroup[strcspn(newCustomer.priorityGroup, "\n")] = '\0'; // Remove trailing newline character
                if (strcmp(newCustomer.priorityGroup, "VIP") == 0) 
                    newCustomer.priorityLevel = 4;             
                else if (strcmp(newCustomer.priorityGroup, "OD") == 0) 
                    newCustomer.priorityLevel = 3;               
                else if (strcmp(newCustomer.priorityGroup, "VETERAN") == 0) 
                    newCustomer.priorityLevel = 2;               
                else if (strcmp(newCustomer.priorityGroup, "NORMAL") == 0) 
                    newCustomer.priorityLevel = 1;
                insertCustomer(&queue, newCustomer);
                writeCustomersToFile(&queue);
                printf("Customer added successfully...\n");
                break;
            }
            case 2: {
                char name[MAX_NAME_LENGTH];
                printf("Please enter customer's Name: ");
                fgets(name, MAX_NAME_LENGTH, stdin);
                name[strcspn(name, "\n")] = '\0'; // Remove trailing newline character
                removeCustomer(&queue, name);
                writeCustomersToFile(&queue);
                printf("Customer removed successfully...\n");
                break;
            }
            case 3:
                printf("Customers:\n");
                displayCustomers(&queue);
                break;
            case 4: {
                char name[MAX_NAME_LENGTH];
                printf("Please enter customer's Name: ");
                fgets(name, MAX_NAME_LENGTH, stdin);
                name[strcspn(name, "\n")] = '\0'; // Remove trailing newline character
                searchCustomer(&queue, name);
                break;
            }
            case 5: {
                char name[MAX_NAME_LENGTH];
                int newPriority;
                printf("Please enter customer's Name: ");
                fgets(name, MAX_NAME_LENGTH, stdin);
                name[strcspn(name, "\n")] = '\0'; // Remove trailing newline character
                printf("Please enter new Priority Level: ");
                scanf("%d", &newPriority);
                getchar(); // Clear input buffer
                changePriority(&queue, name, newPriority);
                writeCustomersToFile(&queue);
                printf("Priority level changed successfully... New properties are following:\n");
                searchCustomer(&queue, name);
                break;
            }
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
    } while (option != 6);

    return 0;
}

void initializePriorityQueue(PriorityQueue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
}

int isPriorityQueueEmpty(PriorityQueue* queue) {
    return queue->front == NULL;
}

void insertCustomer(PriorityQueue* queue, Customer customer) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->customer = customer;
    newNode->next = NULL;

    if (isPriorityQueueEmpty(queue)) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        Node* current = queue->front;
        Node* prev = NULL;
        while (current != NULL && current->customer.priorityLevel >= newNode->customer.priorityLevel) {
            prev = current;
            current = current->next;
        }
        if (prev == NULL) {
            newNode->next = queue->front;
            queue->front = newNode;
        } else {
            prev->next = newNode;
            newNode->next = current;
            if (current == NULL) {
                queue->rear = newNode;
            }
        }
    }
}

void removeCustomer(PriorityQueue* queue, const char* name) {
    if (isPriorityQueueEmpty(queue)) {
        printf("Queue is empty. No customer to remove.\n");
        return;
    }

    Node* current = queue->front;
    Node* prev = NULL;
    while (current != NULL) {
        if (strcmp(current->customer.name, name) == 0) {
            if (prev == NULL) {
                queue->front = current->next;
                if (queue->front == NULL) {
                    queue->rear = NULL;
                }
            } else {
                prev->next = current->next;
                if (prev->next == NULL) {
                    queue->rear = prev;
                }
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("Customer with name '%s' not found.\n", name);
}

void displayCustomers(PriorityQueue* queue) {
    if (isPriorityQueueEmpty(queue)) {
        printf("No customers in the queue.\n");
        return;
    }

    int position = 1;
    Node* current = queue->front;
    while (current != NULL) {
        printf("%d. %s - Age: %d - Priority Group: %s - Priority Level: %d\n", position,
               current->customer.name, current->customer.age, current->customer.priorityGroup,
               current->customer.priorityLevel);
        current = current->next;
        position++;
    }
}

void searchCustomerHelper(Node* current, const char* name) {
    if (current == NULL) {
        printf("Customer with name '%s' not found.\n", name);
        return;
    }

    if (strcmp(current->customer.name, name) == 0) {
        printf("Found: %s - Age: %d - Priority Group: %s - Priority Level: %d\n",
               current->customer.name, current->customer.age, current->customer.priorityGroup,
               current->customer.priorityLevel);
        return;
    }

    searchCustomerHelper(current->next, name);
}

void searchCustomer(PriorityQueue* queue, const char* name) {
    searchCustomerHelper(queue->front, name);
}

void changePriority(PriorityQueue* queue, const char* name, int newPriority) {
    Node* current = queue->front;
    while (current != NULL) {
        if (strcmp(current->customer.name, name) == 0) {
            current->customer.priorityLevel = newPriority;
            return;
        }
        current = current->next;
    }

    printf("Customer with name '%s' not found.\n", name);
}

void writeCustomersToFile(PriorityQueue* queue) {
    FILE* file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    Node* current = queue->front;
    while (current != NULL) {
        fprintf(file, "%s,%d,%s,%d\n", current->customer.name, current->customer.age,
                current->customer.priorityGroup, current->customer.priorityLevel);
        current = current->next;
    }

    fclose(file);
}

void readCustomersFromFile(PriorityQueue* queue) {
    FILE* file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("File does not exist or cannot be opened.\n");
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        char* token;
        Customer customer;

        token = strtok(line, ",");
        strncpy(customer.name, token, MAX_NAME_LENGTH);
        token = strtok(NULL, ",");
        customer.age = atoi(token);
        token = strtok(NULL, ",");
        strncpy(customer.priorityGroup, token, MAX_GROUP_LENGTH);
        token = strtok(NULL, ",");
        customer.priorityLevel = atoi(token);

        insertCustomer(queue, customer);
    }

    fclose(file);
}
