#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for the exam paper
typedef struct ExamPaper {
    char studentName[50];
    int studentNumber;
    int score;
    struct ExamPaper* next;
} ExamPaper;


// Function to add a new exam paper to the stack
ExamPaper* push(ExamPaper* stack, char* studentName, int studentNumber, int score) {
    // Create a new exam paper
    ExamPaper* newExamPaper = (ExamPaper*)malloc(sizeof(ExamPaper));
    strcpy(newExamPaper->studentName, studentName);
    newExamPaper->studentNumber = studentNumber;
    newExamPaper->score = score;

    // Set the new exam paper as the top of the stack
    newExamPaper->next = stack;
    stack = newExamPaper;

    printf("Exam Paper Added: Student Name: %s, Student Number: %d, Score: %d\n",
           newExamPaper->studentName, newExamPaper->studentNumber, newExamPaper->score);

    return stack;
}

// Function to remove the most recently added exam paper from the stack and return it
ExamPaper* pop(ExamPaper* stack) {
    if (stack == NULL) {
        printf("Stack is empty.\n");
        return NULL;
    }

    // Remove the top exam paper from the stack
    ExamPaper* removedExamPaper = stack;
    stack = stack->next;

    printf("Last Added Exam Paper:\n");
    printf("- Student Name: %s, Student Number: %d, Score: %d\n",
           removedExamPaper->studentName, removedExamPaper->studentNumber, removedExamPaper->score);




    free(removedExamPaper);



    return stack;
}

// Function to check if the stack is empty or not
int isEmpty(ExamPaper* stack) {
    if (stack == NULL) {
        printf("Stack is empty.\n");
        return 1;
    } else {
        printf("Stack is not empty.\n");
        return 0;
    }
}

// Function to display the exam papers in the stack
void display(ExamPaper* stack) {
    if (stack == NULL) {
        printf("Exam Papers in the Stack: Stack is empty.\n");
        return;
    }

    printf("Exam Papers in the Stack:\n");
    ExamPaper* current = stack;
    while (current != NULL) {
        printf("- %s, Student Number: %d, Score: %d\n",
               current->studentName, current->studentNumber, current->score);
        current = current->next;
    }
}

int main() {
    ExamPaper* stack = NULL;
    printf("\n");

    stack = push(stack, "Zehra Bilici", 2022001, 90);
    // Call display() to see the exam papers in the stack
    display(stack);
    printf("\n");
    stack = push(stack, "Baris Ozcan", 2019002, 85);
    display(stack);
    printf("\n");
    stack = push(stack, "Mehmet Burak", 20180010, 95);
    display(stack);
    printf("\n");
    pop(stack);
    stack = stack->next;
    display(stack);
    printf("\n");
    // Call display() to see the updated exam papers in the stack

    isEmpty(stack);
    display(stack);

    printf("\n");
    return 0;
}
