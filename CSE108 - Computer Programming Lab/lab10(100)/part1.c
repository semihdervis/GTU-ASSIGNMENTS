#include <stdio.h>
#include <stdlib.h>

int* createIntArray(int size) {
    int* arr = (int*)malloc(size * sizeof(int));  

    printf("Enter the elements of the array: ");
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]); 
    }

    return arr;
}

int findMin(int* arr, int size) {
    int min = arr[0];  

    for (int i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];  
        }
    }

    return min;
}

int main() {
    printf("\n");
    
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);

    int* array = createIntArray(size);
    int min = findMin(array, size);

    printf("Min of the array elements: %d\n", min);

    free(array);  

    printf("\n");

    return 0;
}
