#include "stdio.h"

void main(){
    double weight, height;
    printf("\nenter weight: ");
    scanf("%lf", &weight);
    printf("enter height: ");
    scanf("%lf", &height);
    double bmi = weight / (height * height);
    printf("BMI = %lf, ", bmi);
    if(bmi < 18.5) printf("underweight");
    else if(bmi >= 18.5 && bmi <= 24.9) printf("average weight");
    else if(bmi >= 25 && bmi <= 29.9) printf("overweight");
    else printf("obese");
    printf("\n");
}