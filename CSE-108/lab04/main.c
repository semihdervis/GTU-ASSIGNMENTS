#include <stdio.h>

void write_shapes_to_file(char* filename)
{
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: could not open file '%s' for writing\n", filename);
        return;
    }

    char shape;
    int size;
    do {
        printf("Enter shape type (s for square, t for triangle, e to exit): ");
        scanf(" %c", &shape);

        if (shape == 'e') {
            break;
        } else if (shape != 's' && shape != 't') {
            printf("Error: invalid shape type '%c'\n", shape);
            continue;
        }

        printf("Enter size (between 3 and 10): ");
        scanf("%d", &size);
        if (size < 3 || size > 10) {
            printf("Error: invalid size %d\n", size);
            continue;
        }

        fprintf(fp, "%c,%d\n", shape, size);
    } while (1);

    fclose(fp);
}

void draw_square(int size)
{
    int i, j;
    for (i = 0; i < size + 2; i++) {
        for (j = 0; j < size + 2; j++) {
            if (i == 0 || i == size + 1 || j == 0 || j == size + 1) {
                printf("* ");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void draw_triangle(int size) {
    int i, j, k;

    for (i = 0; i < size; i++) {
        for (j = size - i; j > 0; j--) {
            printf("  ");
        }
        for (k = 0; k <= i; k++) {
            if (i == size - 1 || k == 0 || k == i) {
                printf("*   ");
            } else {
                printf("    ");
            }
        }
        printf("\n");
    }
    printf("\n");
}


int main()
{
    char choice;
    do {
        printf("Welcome to Shape Reader! Please make your choice to continue:\n");
        printf("1-) Generate a shape file\n");
        printf("2-) Read and draw a shape file\n");
        printf("3-) Terminate the program\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case '1':
                write_shapes_to_file("shapes.txt");
                break;
            case '2': {
                FILE* fp = fopen("shapes.txt", "r");
                if (fp == NULL) {
                    printf("Error: shapes.txt not found!\n");
                    break;
                }

                char shape;
                int size;
                while (fscanf(fp, "%c,%d\n", &shape, &size) == 2) {
                    switch (shape) {
                        case 's':
                            draw_square(size);
                            break;
                        case 't':
                            draw_triangle(size);
                            break;
                        default:
                            printf("Error: unknown shape type '%c'\n", shape);
                            break;
                    }
                }
                fclose(fp);
                break;
            }
            case '3':
                printf("Goodbye!\n");
                break;
            default:
                printf("Error: invalid choice '%c'\n", choice);
                break;
        }
    } while (choice != '3');

    return 0;
}


