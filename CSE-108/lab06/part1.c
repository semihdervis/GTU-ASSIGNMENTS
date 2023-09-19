#include <stdio.h>

int read_inputs(int arr[]) {
    int num, i = 0;
    while (1) {
        printf("Enter: ");
        scanf("%d", &num);
        if (num == -100) break;
        arr[i] = num;
        i++;
    } 
    return i;
}

void label_inputs(int arr[], char labels[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) labels[i] = 'e';
        else labels[i] = 'o';
    }
}

void print_results(int arr[], char labels[], int size) {
    for(int i = 0; i < size; i++) {
        printf("%d %c\n", arr[i], labels[i]);
    }
}

int main() {
    int arr[100];
    char labels[100];
    int size = read_inputs(arr);
    label_inputs(arr, labels, size);
    print_results(arr, labels, size);
    return 0;
}
