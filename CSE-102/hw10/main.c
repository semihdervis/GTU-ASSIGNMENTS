#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

typedef struct Book {
    char isbn[MAX_LENGTH];
    char title[MAX_LENGTH];
    char author[MAX_LENGTH];
    int publicationYear;
    int reservedStatus;
    struct Book* next;
} Book;

typedef struct Student {
    int id;
    char name[MAX_LENGTH];
    int numBooks;
    int borrowedBooks[MAX_LENGTH];
    struct Student* next;
} Student;

Book* bookList = NULL;
Student* studentList = NULL;

void reverseBookList() {
    Book* prev = NULL;
    Book* current = bookList;
    Book* next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    bookList = prev;

    printf("Book list reversed successfully.\n");
}

void addBook(char* isbn, char* title, char* author, int publicationYear, int method) {
    Book* book = (Book*)malloc(sizeof(Book));
    strcpy(book->isbn, isbn);
    strcpy(book->title, title);
    strcpy(book->author, author);
    book->publicationYear = publicationYear;
    book->reservedStatus = 0;
    book->next = NULL;

    if (bookList == NULL) {
        bookList = book;
    } else {
        Book* lastBook = bookList;
        while (lastBook->next != NULL) {
            lastBook = lastBook->next;
        }
        lastBook->next = book;
    }

    if (method == 1) {
        reverseBookList();
    }

    //printf("Book with ISBN %s added successfully.\n", isbn);
}

void deleteBook(char* isbn) {
    if (bookList == NULL) {
        printf("Book with ISBN %s not found.\n", isbn);
        return;
    }

    Book* book = bookList;
    Book* prevBook = NULL;

    while (book != NULL) {
        if (strcmp(book->isbn, isbn) == 0) {
            if (prevBook == NULL) {
                bookList = book->next;
            } else {
                prevBook->next = book->next;
            }
            free(book);
            printf("Book with ISBN %s deleted successfully.\n", isbn);
            return;
        }
        prevBook = book;
        book = book->next;
    }

    printf("Book with ISBN %s not found.\n", isbn);
}

void updateBook(char* isbn, char* feature, char* value) {
    if (bookList == NULL) {
        printf("Book with ISBN %s not found.\n", isbn);
        return;
    }

    Book* book = bookList;
    while (book != NULL) {
        if (strcmp(book->isbn, isbn) == 0) {
            if (strcmp(feature, "title") == 0) {
                strcpy(book->title, value);
            } else if (strcmp(feature, "author") == 0) {
                strcpy(book->author, value);
            } else if (strcmp(feature, "publication year") == 0) {
                book->publicationYear = atoi(value);
            } else {
                printf("Invalid feature. Please try again.\n");
                return;
            }
            printf("Book with ISBN %s updated successfully.\n", isbn);
            return;
        }
        book = book->next;
    }

    printf("Book with ISBN %s not found.\n", isbn);
}

void loadBooksFromFile() {
    FILE* file = fopen("books.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char line[MAX_LENGTH];
    fgets(line, sizeof(line), file); // Ignore the header line

    while (fgets(line, sizeof(line), file) != NULL) {
        char* token;
        token = strtok(line, ",");
        char isbn[MAX_LENGTH];
        strcpy(isbn, token);

        token = strtok(NULL, ",");
        char title[MAX_LENGTH];
        strcpy(title, token);

        token = strtok(NULL, ",");
        char author[MAX_LENGTH];
        strcpy(author, token);

        token = strtok(NULL, ",");
        int publicationYear = atoi(token);

        token = strtok(NULL, ",");
        int reservedStatus = atoi(token);

        addBook(isbn, title, author, publicationYear, 0); // Add book to the list (FIFO method)
        Book* book = bookList;
        while (book->next != NULL) {
            book = book->next;
        }
        book->reservedStatus = reservedStatus;
    }

    fclose(file);
}

void loadStudentsFromFile() {
    FILE* file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char line[MAX_LENGTH];
    fgets(line, sizeof(line), file); // Ignore the header line

    while (fgets(line, sizeof(line), file) != NULL) {
        char* token;
        token = strtok(line, ",");
        int id = atoi(token);

        token = strtok(NULL, ",");
        char name[MAX_LENGTH];
        strcpy(name, token);

        token = strtok(NULL, ",");
        int numBooks = atoi(token);

        Student* student = (Student*)malloc(sizeof(Student));
        student->id = id;
        strcpy(student->name, name);
        student->numBooks = numBooks;

        for (int i = 0; i < numBooks; i++) {
            token = strtok(NULL, ",");
            student->borrowedBooks[i] = atoi(token);
        }

        student->next = studentList;
        studentList = student;
    }

    fclose(file);
}

void displayBookList() {
    printf("\nBook List:\n");

    Book* book = bookList;
    while (book != NULL) {
        printf("ISBN: %s\n", book->isbn);
        printf("Title: %s\n", book->title);
        printf("Author: %s\n", book->author);
        printf("Publication Year: %d\n", book->publicationYear);
        printf("Reserved Status: %s\n", book->reservedStatus ? "Reserved" : "Available");
        printf("----------------------------\n");
        book = book->next;
    }
}

void displayStudentBorrowedBooks(int studentId) {
    Student* student = studentList;
    while (student != NULL) {
        if (student->id == studentId) {
            printf("\nBorrowed Books List (Student ID: %d)\n", student->id);

            for (int i = 0; i < student->numBooks; i++) {
                Book* book = bookList;
                while (book != NULL) {
                    if (atoi(book->isbn) == student->borrowedBooks[i]) {
                        printf("ISBN: %s\n", book->isbn);
                        printf("Title: %s\n", book->title);
                        printf("Author: %s\n", book->author);
                        printf("Publication Year: %d\n", book->publicationYear);
                        printf("Reserved Status: %s\n", book->reservedStatus ? "Reserved" : "Available");
                        printf("----------------------------\n");
                        break;
                    }
                    book = book->next;
                }
            }

            return;
        }
        student = student->next;
    }

    printf("Student with ID %d not found.\n", studentId);
}

void saveBooksToFile() {
    FILE* file = fopen("books.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "isbn,title,author,publicationYear,reservedStatus\n");

    Book* book = bookList;
    while (book != NULL) {
        fprintf(file, "%s,%s,%s,%d,%d\n", book->isbn, book->title, book->author, book->publicationYear, book->reservedStatus);
        book = book->next;
    }

    fclose(file);
}

void swapBooks(Book* book1, Book* book2) {
    char tempIsbn[13];
    char tempTitle[100];
    char tempAuthor[100];
    int tempPublicationYear;
    int tempReservedStatus;

    // Swap ISBN
    strcpy(tempIsbn, book1->isbn);
    strcpy(book1->isbn, book2->isbn);
    strcpy(book2->isbn, tempIsbn);

    // Swap Title
    strcpy(tempTitle, book1->title);
    strcpy(book1->title, book2->title);
    strcpy(book2->title, tempTitle);

    // Swap Author
    strcpy(tempAuthor, book1->author);
    strcpy(book1->author, book2->author);
    strcpy(book2->author, tempAuthor);

    // Swap Publication Year
    tempPublicationYear = book1->publicationYear;
    book1->publicationYear = book2->publicationYear;
    book2->publicationYear = tempPublicationYear;

    // Swap Reserved Status
    tempReservedStatus = book1->reservedStatus;
    book1->reservedStatus = book2->reservedStatus;
    book2->reservedStatus = tempReservedStatus;
}


void filterAndSortBooks(int filterChoice, char* filter, int sortChoice) {
    Book* filteredBooks = NULL;

    Book* book = bookList;
    while (book != NULL) {
        if ((filterChoice == 0 && strcmp(book->author, filter) == 0) ||
            (filterChoice == 1 && book->publicationYear == atoi(filter))) {
            Book* filteredBook = (Book*)malloc(sizeof(Book));
            strcpy(filteredBook->isbn, book->isbn);
            strcpy(filteredBook->title, book->title);
            strcpy(filteredBook->author, book->author);
            filteredBook->publicationYear = book->publicationYear;
            filteredBook->reservedStatus = book->reservedStatus;
            filteredBook->next = NULL;

            if (filteredBooks == NULL) {
                filteredBooks = filteredBook;
            } else {
                Book* lastBook = filteredBooks;
                while (lastBook->next != NULL) {
                    lastBook = lastBook->next;
                }
                lastBook->next = filteredBook;
            }
        }

        book = book->next;
    }

    if (filteredBooks == NULL) {
        printf("No books found matching the filter criteria.\n");
        return;
    }

    // Sort books
    if (sortChoice == 0) {
        // Sort by title
        for (Book* i = filteredBooks; i != NULL; i = i->next) {
            for (Book* j = i->next; j != NULL; j = j->next) {
                if (strcmp(i->title, j->title) > 0) {
                    swapBooks(i, j);
                }
            }
        }
    } else if (sortChoice == 1) {
        // Sort by author
        for (Book* i = filteredBooks; i != NULL; i = i->next) {
            for (Book* j = i->next; j != NULL; j = j->next) {
                if (strcmp(i->author, j->author) > 0) {
                    swapBooks(i, j);
                }
            }
        }
    } else if (sortChoice == 2) {
        // Sort by publication year
        for (Book* i = filteredBooks; i != NULL; i = i->next) {
            for (Book* j = i->next; j != NULL; j = j->next) {
                if (i->publicationYear > j->publicationYear) {
                    swapBooks(i, j);
                }
            }
        }
    }

    printf("\nFiltered and Sorted Book List:\n");

    Book* filteredBook = filteredBooks;
    while (filteredBook != NULL) {
        printf("ISBN: %s\n", filteredBook->isbn);
        printf("Title: %s\n", filteredBook->title);
        printf("Author: %s\n", filteredBook->author);
        printf("Publication Year: %d\n", filteredBook->publicationYear);
        printf("Reserved Status: %s\n", filteredBook->reservedStatus ? "Reserved" : "Available");
        printf("----------------------------\n");
        filteredBook = filteredBook->next;
    }

    // Free memory
    while (filteredBooks != NULL) {
        Book* temp = filteredBooks;
        filteredBooks = filteredBooks->next;
        free(temp);
    }
}

void searchBooks(int searchChoice, char* searchValue) {
    Book* searchResults = NULL;

    Book* book = bookList;
    while (book != NULL) {
        if ((searchChoice == 0 && strcmp(book->isbn, searchValue) == 0) ||
            (searchChoice == 1 && strcmp(book->author, searchValue) == 0) ||
            (searchChoice == 2 && strcmp(book->title, searchValue) == 0)) {
            Book* searchResult = (Book*)malloc(sizeof(Book));
            strcpy(searchResult->isbn, book->isbn);
            strcpy(searchResult->title, book->title);
            strcpy(searchResult->author, book->author);
            searchResult->publicationYear = book->publicationYear;
            searchResult->reservedStatus = book->reservedStatus;
            searchResult->next = NULL;

            if (searchResults == NULL) {
                searchResults = searchResult;
            } else {
                Book* lastBook = searchResults;
                while (lastBook->next != NULL) {
                    lastBook = lastBook->next;
                }
                lastBook->next = searchResult;
            }
        }

        book = book->next;
    }

    if (searchResults == NULL) {
        printf("No books found matching the search criteria.\n");
        return;
    }

    printf("\nSearch Results:\n");

    Book* searchResult = searchResults;
    while (searchResult != NULL) {
        printf("ISBN: %s\n", searchResult->isbn);
        printf("Title: %s\n", searchResult->title);
        printf("Author: %s\n", searchResult->author);
        printf("Publication Year: %d\n", searchResult->publicationYear);
        printf("Reserved Status: %s\n", searchResult->reservedStatus ? "Reserved" : "Available");
        printf("----------------------------\n");
        searchResult = searchResult->next;
    }

    // Free memory
    while (searchResults != NULL) {
        Book* temp = searchResults;
        searchResults = searchResults->next;
        free(temp);
    }
}

void borrowBook(int studentId, char* isbn) {
    Student* student = studentList;
    while (student != NULL) {
        if (student->id == studentId) {
            if (student->numBooks >= 5) {
                printf("Maximum limit reached. Cannot borrow more books.\n");
                return;
            }

            Book* book = bookList;
            while (book != NULL) {
                if (strcmp(book->isbn, isbn) == 0) {
                    if (book->reservedStatus) {
                        printf("Book with ISBN %s is already reserved.\n", isbn);
                        return;
                    }

                    book->reservedStatus = 1;
                    student->borrowedBooks[student->numBooks] = atoi(isbn);
                    student->numBooks++;
                    printf("Book with ISBN %s borrowed successfully by student with ID %d.\n", isbn, studentId);
                    return;
                }
                book = book->next;
            }

            printf("Book with ISBN %s not found.\n", isbn);
            return;
        }
        student = student->next;
    }

    printf("Student with ID %d not found.\n", studentId);
}

void returnBook(int studentId, char* isbn) {
    Student* student = studentList;
    while (student != NULL) {
        if (student->id == studentId) {
            for (int i = 0; i < student->numBooks; i++) {
                if (student->borrowedBooks[i] == atoi(isbn)) {
                    Book* book = bookList;
                    while (book != NULL) {
                        if (strcmp(book->isbn, isbn) == 0) {
                            book->reservedStatus = 0;
                            //free(student->borrowedBooks[i]);
                            student->numBooks--;

                            for (int j = i; j < student->numBooks; j++) {
                                student->borrowedBooks[j] = student->borrowedBooks[j + 1];
                            }

                            printf("Book with ISBN %s returned successfully by student with ID %d.\n", isbn, studentId);
                            return;
                        }
                        book = book->next;
                    }

                    printf("Book with ISBN %s not found.\n", isbn);
                    return;
                }
            }

            printf("Student with ID %d has not borrowed a book with ISBN %s.\n", studentId, isbn);
            return;
        }
        student = student->next;
    }

    printf("Student with ID %d not found.\n", studentId);
}

void saveStudentsToFile() {
    FILE* file = fopen("students.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "id,name,numBooks,isbn\n");

    Student* student = studentList;
    while (student != NULL) {
        fprintf(file, "%d,%s,%d", student->id, student->name, student->numBooks);
        for (int i = 0; i < student->numBooks; i++) {
            fprintf(file, ",%d", student->borrowedBooks[i]);
        }
        fprintf(file, "\n");
        student = student->next;
    }

    fclose(file);
}


int main() {
    loadBooksFromFile();
    loadStudentsFromFile();

    int choice;
    char isbn[MAX_LENGTH];
    char title[MAX_LENGTH];
    char author[MAX_LENGTH];
    int publicationYear;
    int method;
    char feature[MAX_LENGTH];
    char value[MAX_LENGTH];
    int filterChoice;
    char filter[MAX_LENGTH];
    int sortChoice;
    int searchChoice;
    char searchValue[MAX_LENGTH];
    int num;

    do {
        printf("\nLibrary Book Management System\n");
        printf("1. Display Book List\n");
        printf("2. Display Student's Borrowed Books List\n");
        printf("3. Add Book\n");
        printf("4. Delete Book\n");
        printf("5. Update Book\n");
        printf("6. Filter and Sort Books\n");
        printf("7. Reverse Book List\n");
        printf("8. Search Books\n");
        printf("9. Borrow Book\n");
        printf("10. Return Book\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayBookList();
                break;
            case 2:
                printf("Enter the student's ID: ");
                scanf("%d", &choice);
                displayStudentBorrowedBooks(choice);
                break;
            case 3:
                printf("Enter the book's ISBN number: ");
                scanf("%s", isbn);
                printf("Enter the book's title: ");
                scanf(" %[^\n]s", title);
                printf("Enter the book's author: ");
                scanf(" %[^\n]s", author);
                printf("Enter the book's publication year: ");
                scanf("%d", &publicationYear);
                printf("Enter the book management method (0 for FIFO, 1 for LIFO): ");
                scanf("%d", &method);
                addBook(isbn, title, author, publicationYear, method);
                break;
            case 4:
                printf("Enter the book's ISBN number: ");
                scanf("%s", isbn);
                deleteBook(isbn);
                break;
            case 5:
                printf("Enter the book's ISBN number: ");
                scanf("%s", isbn);
                printf("Enter the feature to be updated (title, author, or publication year): ");
                scanf(" %[^\n]s", feature);
                printf("Enter the new value for the feature: ");
                scanf(" %[^\n]s", value);
                updateBook(isbn, feature, value);
                break;
            case 6:
                printf("Filter books by (0 for author, 1 for publication year): ");
                scanf("%d", &filterChoice);
                printf("Enter the filter criteria: ");
                scanf(" %[^\n]s", filter);
                printf("Sort books by (0 for title, 1 for author, 2 for publication year): ");
                scanf("%d", &sortChoice);
                filterAndSortBooks(filterChoice, filter, sortChoice);
                break;
            case 7:
                reverseBookList();
                break;
            case 8:
                printf("Search books by (0 for ISBN number, 1 for author, 2 for title): ");
                scanf("%d", &searchChoice);
                printf("Enter the search value: ");
                scanf(" %[^\n]s", searchValue);
                searchBooks(searchChoice, searchValue);
                break;
            case 9:
                printf("Enter the book's ISBN number: ");
                scanf("%s", isbn);
                printf("Enter the student's ID: ");
                scanf("%d", &num);
                borrowBook(num, isbn);
                break;
            case 10:
                printf("Enter the book's ISBN number: ");
                scanf("%s", isbn);
                printf("Enter the student's ID: ");
                scanf("%d", &num);
                returnBook(num,isbn);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    saveBooksToFile();
    saveStudentsToFile();

    return 0;
}