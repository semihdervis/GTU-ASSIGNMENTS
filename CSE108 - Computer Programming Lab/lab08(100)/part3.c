#include <stdio.h>

typedef struct {
    double a, b, c, d;
} third_order_polynomial;

typedef struct {
    double a, b, c, d;
    char constant;
    double value;
} integrated_polynomial;

double evaluate_polynomial(third_order_polynomial p, double x) {
    return p.a * x * x * x + p.b * x * x + p.c * x + p.d;
}

integrated_polynomial get_integral(third_order_polynomial p1, third_order_polynomial p2, int a, int b) {
    integrated_polynomial result;
    third_order_polynomial temp;
    double coefficient_a = p1.a * p2.a / 4;
    double coefficient_b = p1.a * p2.b / 3 + p1.b * p2.a / 3;
    double coefficient_c = p1.a * p2.c / 2 + p1.b * p2.b / 2 + p1.c * p2.a / 2;
    double coefficient_d = p1.a * p2.d + p1.b * p2.c + p1.c * p2.b + p1.d * p2.a;
    double constant = p1.d * p2.d;
    result.a = coefficient_a;
    result.b = coefficient_b;
    result.c = coefficient_c;
    result.d = coefficient_d;
    result.constant = 'K';
    temp.a = coefficient_a;
    temp.b = coefficient_b;
    temp.c = coefficient_c;
    temp.d = coefficient_d;
    result.value = evaluate_polynomial(temp, b) - evaluate_polynomial(temp, a);
    return result;
}

int main() {
    third_order_polynomial p1, p2;
    int a, b;
    printf("Enter the coefficients of the first polynomial (a, b, c, d): ");
    scanf("%lf %lf %lf %lf", &p1.a, &p1.b, &p1.c, &p1.d);
    printf("Enter the coefficients of the second polynomial (a, b, c, d): ");
    scanf("%lf %lf %lf %lf", &p2.a, &p2.b, &p2.c, &p2.d);
    printf("Enter the interval limits (a, b): ");
    scanf("%d %d", &a, &b);
    integrated_polynomial result = get_integral(p1, p2, a, b);
    printf("The integrated polynomial coefficients are: %lf %lf %lf %lf %c\n", result.a, result.b, result.c, result.d, result.constant);
    printf("The value of the integrated polynomial between [%d, %d] is %lf.\n", a, b, result.value);
    return 0;
}
