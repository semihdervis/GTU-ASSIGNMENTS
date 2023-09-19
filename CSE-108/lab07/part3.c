#include <stdio.h>

void foo_min_max(int arr[], int n);

int main()
{
    int n;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements in the array:\n", n);
    for(int i=0; i<n; i++)
    {
        scanf("%d", &arr[i]);
    }

    foo_min_max(arr, n);
    return 0;
}

void foo_min_max(int arr[], int n)
{
    int i = 0;
    int min = arr[i];
    int max = arr[i];

    while(i < n)
    {
        if(arr[i] < min)
        {
            min = arr[i];
        }
        if(arr[i] > max)
        {
            max = arr[i];
        }
        i++;
    }

    printf("Minimum item in the array: %d\n", min);
    printf("Maximum item in the array: %d\n", max);
}
