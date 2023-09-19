#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Order {
    char* customerName;
    int orderID;
    char* items;
    time_t orderTime;
    struct Order* next;
} Order;

typedef struct LIFO {
    Order* top;
} LIFO;

typedef struct FIFO {
    Order* front;
    Order* rear;
} FIFO;

void enqueue(Order** list, char* customerName, int orderID, char* items, time_t orderTime) {
    Order* newOrder = (Order*)malloc(sizeof(Order));
    newOrder->customerName = strdup(customerName);
    newOrder->orderID = orderID;
    newOrder->items = strdup(items);
    newOrder->orderTime = orderTime;
    newOrder->next = NULL;
    
    if (*list == NULL) {
        *list = newOrder;
    } else {
        Order* current = *list;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newOrder;
    }
    
    printf("Order Added: Customer Name: %s, Order ID: %d, Items: %s, Order Time: %s",
           newOrder->customerName, newOrder->orderID, newOrder->items, ctime(&newOrder->orderTime));
}

Order* removeFirstOrder(Order** list) {
    if (*list == NULL) {
        printf("No orders in the list.\n");
        return NULL;
    }
    
    Order* removedOrder = *list;
    *list = (*list)->next;
    
    printf("Order Removed: Customer Name: %s, Order ID: %d, Items: %s, Order Time: %s\n",
           removedOrder->customerName, removedOrder->orderID, removedOrder->items, ctime(&removedOrder->orderTime));
    
    return removedOrder;
}


Order* dequeue(Order** list, time_t thresholdTime) {
    if (*list == NULL) {
        printf("No orders in the list.\n");
        return NULL;
    }

    removeFirstOrder(list);
    
    Order* current = *list;
    Order* prev = NULL;
    Order* removedOrders = NULL;

    
    while (current != NULL) {
        if (current->orderTime < thresholdTime) {
            if (prev == NULL) {
                *list = current->next;
            } else {
                prev->next = current->next;
            }
            
            current->next = removedOrders;
            removedOrders = current;
            current = prev != NULL ? prev->next : *list;
        } else {
            prev = current;
            current = current->next;
        }
    }
    
    while (removedOrders != NULL) {
        Order* temp = removedOrders;
        printf("Order Removed from Queue: Customer Name: %s, Order ID: %d, Items: %s, Order Time: %s\n",
               temp->customerName, temp->orderID, temp->items, ctime(&temp->orderTime));
        removedOrders = removedOrders->next;
        free(temp->customerName);
        free(temp->items);
        free(temp);
    }
    
    return *list;
}

void serializeLIFO(LIFO* stack, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    
    Order* current = stack->top;
    while (current != NULL) {
        fwrite(&current->orderID, sizeof(int), 1, file);
        fwrite(&current->orderTime, sizeof(time_t), 1, file);
        
        int nameLength = strlen(current->customerName) + 1;
        fwrite(&nameLength, sizeof(int), 1, file);
        fwrite(current->customerName, sizeof(char), nameLength, file);
        
        int itemsLength = strlen(current->items) + 1;
        fwrite(&itemsLength, sizeof(int), 1, file);
        fwrite(current->items, sizeof(char), itemsLength, file);
        
        current = current->next;
    }
    
    fclose(file);
    printf("LIFO data structure serialized to a binary file.\n");
}

LIFO* deserializeLIFO(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return NULL;
    }
    
    LIFO* stack = (LIFO*)malloc(sizeof(LIFO));
    stack->top = NULL;
    
    int orderID;
    time_t orderTime;
    int nameLength, itemsLength;
    
    while (fread(&orderID, sizeof(int), 1, file) == 1) {
        fread(&orderTime, sizeof(time_t), 1, file);
        
        fread(&nameLength, sizeof(int), 1, file);
        char* customerName = (char*)malloc(nameLength * sizeof(char));
        fread(customerName, sizeof(char), nameLength, file);
        
        fread(&itemsLength, sizeof(int), 1, file);
        char* items = (char*)malloc(itemsLength * sizeof(char));
        fread(items, sizeof(char), itemsLength, file);
        
        enqueue(&(stack->top), customerName, orderID, items, orderTime);
    }
    
    fclose(file);
    printf("LIFO data structure deserialized from a binary file.\n");
    
    return stack;
}

void serializeFIFO(FIFO* queue, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    
    Order* current = queue->front;
    while (current != NULL) {
        fwrite(&current->orderID, sizeof(int), 1, file);
        fwrite(&current->orderTime, sizeof(time_t), 1, file);
        
        int nameLength = strlen(current->customerName) + 1;
        fwrite(&nameLength, sizeof(int), 1, file);
        fwrite(current->customerName, sizeof(char), nameLength, file);
        
        int itemsLength = strlen(current->items) + 1;
        fwrite(&itemsLength, sizeof(int), 1, file);
        fwrite(current->items, sizeof(char), itemsLength, file);
        
        current = current->next;
    }
    
    fclose(file);
    printf("FIFO data structure serialized to a binary file.\n");
}

FIFO* deserializeFIFO(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return NULL;
    }
    
    FIFO* queue = (FIFO*)malloc(sizeof(FIFO));
    queue->front = NULL;
    queue->rear = NULL;
    
    int orderID;
    time_t orderTime;
    int nameLength, itemsLength;
    
    while (fread(&orderID, sizeof(int), 1, file) == 1) {
        fread(&orderTime, sizeof(time_t), 1, file);
        
        fread(&nameLength, sizeof(int), 1, file);
        char* customerName = (char*)malloc(nameLength * sizeof(char));
        fread(customerName, sizeof(char), nameLength, file);
        
        fread(&itemsLength, sizeof(int), 1, file);
        char* items = (char*)malloc(itemsLength * sizeof(char));
        fread(items, sizeof(char), itemsLength, file);
        
        enqueue(&(queue->rear), customerName, orderID, items, orderTime);
        if (queue->front == NULL) {
            queue->front = queue->rear;
        }
    }
    
    fclose(file);
    printf("FIFO data structure deserialized from a binary file.\n");
    
    return queue;
}

void displayOrders(Order* list) {
    printf("Order List:\n");
    Order* current = list;
    
    while (current != NULL) {
        printf("Customer Name: %s, Order ID: %d, Items: %s, Order Time: %s",
               current->customerName, current->orderID, current->items, ctime(&current->orderTime));
        current = current->next;
    }
}

int main() {
    Order* list = NULL;
    LIFO* stack = (LIFO*)malloc(sizeof(LIFO));
    stack->top = NULL;
    FIFO* queue = (FIFO*)malloc(sizeof(FIFO));
    queue->front = NULL;
    queue->rear = NULL;

    printf("\n");
    
    enqueue(&list, "Ali Yilmaz", 101, "Pizza, Salad, Ice Cream", time(NULL));
    enqueue(&list, "Ayse Demir", 102, "Steak, Mashed Potatoes, Salad", time(NULL));
    enqueue(&list, "Semih Dervis", 103, "Hambureger, Tomatoes, Onions", time(NULL));
    
    printf("\n");
    
    dequeue(&list, time(NULL));
    
    printf("\n");
    
    serializeLIFO(stack, "lifo_data.bin");
    deserializeLIFO("lifo_data.bin");
    printf("\n");
    displayOrders(list);
    
    printf("\n");
    
    serializeFIFO(queue, "fifo_data.bin");
    deserializeFIFO("fifo_data.bin");
    printf("\n");
    displayOrders(list);
    
    return 0;
}
