#include "stdio.h"

void main(){
    int x, y, max;
    double z;
    printf("enter two integers: ");
    scanf("%d %d", &x, &y);
    if(x < y) max = y;
    else max = x;
    z = ((double)x / (double)y) + ((double)max / (double)(x + y));
    printf("result: %lf\n", z);
}