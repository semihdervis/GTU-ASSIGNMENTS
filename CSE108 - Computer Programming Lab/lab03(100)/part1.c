#include <stdio.h>

void main() {
    int a, b, c, median;
    
    printf("Enter 3 integers: ");
    scanf("%d %d %d", &a, &b, &c);

    if(a < b){
        if(b < c) median = b;
        else if(a > c) median = a;
        else median = c;
    }

    else{
        if(b > c) median = b;
        else if(a < c) median = a;
        else median = c;
    }

    printf("Median number is %d\n", median);
}