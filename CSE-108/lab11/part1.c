#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to hold order details
typedef struct Order {
    char customerName[100];
    int orderID;
    char items[100];
    char orderTime[100];
    struct Order* next;
} Order;

// Function to enqueue (add) a new order to the linked list
Order* enqueue(Order* queue, char* customerName, int orderID, char* items, char* orderTime) {
    Order* newOrder = (Order*)malloc(sizeof(Order));
    strcpy(newOrder->customerName, customerName);
    newOrder->orderID = orderID;
    strcpy(newOrder->items, items);
    strcpy(newOrder->orderTime, orderTime);
    newOrder->next = NULL;

    if (queue == NULL) {
        return newOrder;
    } 
    else {
        Order* temp = queue;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newOrder;
        return queue;
    }
}

// Function to dequeue (remove) the oldest order from the linked list
Order* dequeue(Order* queue) {
    if (queue == NULL) {
        printf("Queue is empty.\n");
        return NULL;
    }

    Order* temp = queue;
    queue = queue->next;
    printf("Dequeued Order ID: %d\n", temp->orderID);
    free(temp);
    return queue;
}

// Function to display the linked list (orders) on the screen
void display(Order* queue) {
    if (queue == NULL) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Display Orders by Order Time:\n");
    Order* temp = queue;
    while (temp != NULL) {
        printf("- Order ID: %d, Customer Name: %s, Items: %s\n", temp->orderID, temp->customerName, temp->items);
        temp = temp->next;
    }
}

// Function to update the items in an existing order (defined by orderID)
void updateOrder(Order* queue, int orderID, char* newItems) {
    Order* temp = queue;
    while (temp != NULL) {
        if (temp->orderID == orderID) {
            strcpy(temp->items, newItems);
            printf("Updated Order: Order ID: %d, Customer Name: %s, Items: %s\n", temp->orderID, temp->customerName, temp->items);
            return;
        }
        temp = temp->next;
    }
    printf("Order ID %d not found.\n", orderID);
}

// Function to delete an order (defined by orderID)
Order* deleteOrder(Order* queue, int orderID) {
    if (queue == NULL) {
        printf("Queue is empty.\n");
        return NULL;
    }

    if (queue->orderID == orderID) {
        Order* temp = queue;
        queue = queue->next;
        printf("Deleted Order: Order ID: %d\n", temp->orderID);
        free(temp);
        return queue;
    }

    Order* prev = queue;
    Order* current = queue->next;
    while (current != NULL) {
        if (current->orderID == orderID) {
            prev->next = current->next;
            printf("Deleted Order: Order ID: %d\n", current->orderID);
            free(current);
            return queue;
        }
        prev = current;
        current = current->next;
    }

    printf("Order ID %d not found.\n", orderID);
    return queue;
}

int main() {
    Order* queue = NULL;
    printf("\n");
    // Enqueue Operation
    queue = enqueue(queue, "Baris Ozcan", 101, "Burger, Fries, Coke", "12:30 PM");
    printf("Enqueue Operation:\n");
    printf("Enqueued: Order ID: %d, Customer Name: %s, Items: %s\n", queue->orderID, queue->customerName, queue->items);
    display(queue);
    printf("\n");

    // Enqueue Operation
    queue = enqueue(queue, "Zehra Bilici", 102, "Pizza, Salad, Ice Cream", "1:45 PM");
    printf("Enqueue Operation:\n");
    printf("Enqueued: Order ID: %d, Customer Name: %s, Items: %s\n", queue->next->orderID, queue->next->customerName, queue->next->items);
    display(queue);
    printf("\n");

    // Enqueue Operation
    queue = enqueue(queue, "Mehmet Burak Koca", 103, "Steak, Mashed Potatoes, Salad", "2:15 PM");
    printf("Enqueue Operation:\n");
    printf("Enqueued: Order ID: %d, Customer Name: %s, Items: %s\n", queue->next->next->orderID, queue->next->next->customerName, queue->next->next->items);
    display(queue);
    printf("\n");

    // Dequeue Operation
    printf("Dequeue Operation:\n");
    queue = dequeue(queue);
    queue = dequeue(queue);
    display(queue);
    printf("\n");

    // Update Order
    printf("Update Order:\n");
    updateOrder(queue, 103, "Pizza, Salad, Coke");
    display(queue);
    printf("\n");

    // Delete Order
    printf("Delete Order:\n");
    queue = deleteOrder(queue, 103);
    display(queue);
    printf("\n");

    return 0;
}
