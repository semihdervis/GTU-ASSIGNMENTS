#include <stdio.h>
#include <stdlib.h>

int* createIntArray(int size) {
    int* arr = (int*)malloc(size * sizeof(int));

    printf("Enter %d integers: ", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    return arr;
}

void printArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    printf("\n");
    
    int size;
    printf("Enter the number of integers: ");
    scanf("%d", &size);

    int* array = createIntArray(size);

    int* cumSum = (int*)calloc(size, sizeof(int));

    cumSum[0] = array[0];  

    for (int i = 1; i < size; i++) {
        cumSum[i] = cumSum[i - 1] + array[i];  
    }

    printf("First array: ");
    printArray(array, size);

    printf("Second array (cumulative sum): ");
    printArray(cumSum, size);

    free(array);
    free(cumSum);

    printf("\n");
    return 0;
}
