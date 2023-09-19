#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int ID;
    int age;
    float gpa;
} Student;

float generateRandomGPA() {
    return (float)(rand() % 401) / 100.0;  // Generates random GPA between 0.00 and 4.00
}

float allocateStudentMemory(Student** students) {
    *students = (Student*)malloc(10000 * sizeof(Student));
    if (*students == NULL) {
        printf("Memory allocation failed.\n");
        return 0.0;
    }

    float totalGPA = 0.0;
    for (int i = 0; i < 10000; i++) {
        (*students)[i].ID = i + 1;
        (*students)[i].age = 18 + (rand() % 10);  // Generates random age between 18 and 27
        (*students)[i].gpa = generateRandomGPA();
        totalGPA += (*students)[i].gpa;
    }

    return totalGPA / 10000.0;
}

int main() {
    printf("\n");
    srand(time(NULL));  // Initialize random seed

    float totalAverageGPA = 0.0;
    for (int i = 0; i < 10000; i++) {
        Student* students;
        float averageGPA = allocateStudentMemory(&students);
        totalAverageGPA += averageGPA;
        free(students);
    }

    float overallAverageGPA = totalAverageGPA / 10000.0;
    printf("Average GPA of 10.000 x 10.000 students: %f\n", overallAverageGPA);

    printf("\n");
    return 0;
}
