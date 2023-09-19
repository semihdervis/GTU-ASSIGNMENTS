#include <stdio.h>

typedef struct {
    double mat[3][3];
    double det;
} matrix;

void print_matrix(matrix m) {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%8.4f ", m.mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void determinant_of_matrix(matrix* m) {
    double a = m->mat[0][0], b = m->mat[0][1], c = m->mat[0][2];
    double d = m->mat[1][0], e = m->mat[1][1], f = m->mat[1][2];
    double g = m->mat[2][0], h = m->mat[2][1], i = m->mat[2][2];
    m->det = a*(e*i - f*h) - b*(d*i - f*g) + c*(d*h - e*g);
}

void inverse_matrix(matrix* m, matrix* inv) {
    determinant_of_matrix(m);
    double det = m->det;
    if (det == 0) {
        printf("The matrix is not invertible.\n");
        return;
    }
    double a = m->mat[0][0], b = m->mat[0][1], c = m->mat[0][2];
    double d = m->mat[1][0], e = m->mat[1][1], f = m->mat[1][2];
    double g = m->mat[2][0], h = m->mat[2][1], i = m->mat[2][2];
    inv->mat[0][0] = (e*i - f*h) / det;
    inv->mat[0][1] = -(b*i - c*h) / det;
    inv->mat[0][2] = (b*f - c*e) / det;
    inv->mat[1][0] = -(d*i - f*g) / det;
    inv->mat[1][1] = (a*i - c*g) / det;
    inv->mat[1][2] = -(a*f - c*d) / det;
    inv->mat[2][0] = (d*h - e*g) / det;
    inv->mat[2][1] = -(a*h - b*g) / det;
    inv->mat[2][2] = (a*e - b*d) / det;
    inv->det = 1 / det;
}

int main() {
    matrix m = {{
        {1.0, 2.0, 3.0},
        {0.0, 1.0, 4.0},
        {5.0, 6.0, 0.0}
    }};
    matrix inv;
    printf("\nOriginal matrix:\n");
    print_matrix(m);
    inverse_matrix(&m, &inv);
    printf("Inverse matrix:\n");
    print_matrix(inv);
    return 0;
}
