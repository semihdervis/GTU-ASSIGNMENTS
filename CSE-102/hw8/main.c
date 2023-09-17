#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int board[3][3];
} board;

void int_swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void initialize_board(board* b) {
    int k = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            b->board[i][j] = k;
            k++;
        }
    }
}

void shuffle_board(board* b) {
    for (int i = 2; i > 0; i--) {
        for (int j = 2; j > 0; j--) {
            int m = rand() % 3;
            int n = rand() % 3;
            int temp = b->board[i][j];
            b->board[i][j] = b->board[m][n];
            b->board[m][n] = temp;
        }
    }
}

void print_board(board* b) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (b->board[i][j] != 0) printf("%d ", b->board[i][j]);
            else printf("_ ");
        }
        printf("\n");
    }
}

void move(board* b, int num, char dir) {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (b->board[i][j] == num) {
                goto end;
            }
        }
    }
    end:

    if (dir == 'u' || dir == 'U') {
        if (i == 0 || b->board[i - 1][j] != 0) {
            printf("%d-%c is an illegal move!!! Make a legal move!!!\n\n", num, dir);
        }
        else {
            int_swap(&b->board[i][j], &b->board[i - 1][j]);
        }
    }
    else if (dir == 'd' || dir == 'D') {
        if (i == 2 || b->board[i + 1][j] != 0) {
            printf("%d-%c is an illegal move!!! Make a legal move!!!\n\n", num, dir);
        }
        else {
            int_swap(&b->board[i][j], &b->board[i + 1][j]);
        }
    }
    else if (dir == 'l' || dir == 'L') {
        if (j == 0 || b->board[i][j - 1] != 0) {
            printf("%d-%c is an illegal move!!! Make a legal move!!!\n\n", num, dir);
        }
        else {
            int_swap(&b->board[i][j], &b->board[i][j - 1]);
        }
    }
    else if (dir == 'r' || dir == 'R') {
        if (j == 2 || b->board[i][j + 1] != 0) {
            printf("%d-%c is an illegal move!!! Make a legal move!!!\n\n", num, dir);
        }
        else {
            int_swap(&b->board[i][j], &b->board[i][j + 1]);
        }
    }
}

int is_solved(board* b) {
    int k = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == 2 && j == 2 && b->board[i][j] == 0) return 1;
            else if (b->board[i][j] != k) {
                return 0;
            }
            k++;
        }
    }
}

void find_blank(board* b, int* i, int* j) {
    for (int k = 0; k < 3; k++) {
        for (int l = 0; l < 3; l++) {
            if (b->board[k][l] == 0) {
                *i = k;
                *j = l;
                return;
            }
        }
    }
}

int is_solvable(board* b) {
    int inversion_count = 0;
    int linear_board[9];
    int index = 0;

    // Convert 2D board array to 1D linear array
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            linear_board[index++] = b->board[row][col];
        }
    }

    // Calculate inversion count
    for (int i = 0; i < 8; i++) {
        for (int j = i + 1; j < 9; j++) {
            if (linear_board[j] && linear_board[i] && linear_board[i] > linear_board[j]) {
                inversion_count++;
            }
        }
    }

    // Check if inversion count is even
    return (inversion_count % 2 == 0);
}

int make_move(board* b, int prev) {
    // Find the location of the blank space (0)
    int blank_row = 0, blank_col = 0;
    find_blank(b, &blank_row, &blank_col);

    // Generate a random move that is valid
    int valid_moves[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int num_valid_moves = 0;
    int valid_move_indices[4] = {-1, -1, -1, -1};
    for (int i = 0; i < 4; i++) {
        int new_row = blank_row + valid_moves[i][0];
        int new_col = blank_col + valid_moves[i][1];
        if (new_row >= 0 && new_row < 3 && new_col >= 0 && new_col < 3) {
            if (b->board[new_row][new_col] == prev) continue;
            valid_move_indices[num_valid_moves] = i;
            num_valid_moves++;
        }
    }

    int random_valid_move_index = valid_move_indices[rand() % num_valid_moves];
    int new_row = blank_row + valid_moves[random_valid_move_index][0];
    int new_col = blank_col + valid_moves[random_valid_move_index][1];

    // Find direction of move
    char dir;
    int i;
    for (i = 0; i < 4; i++) {
        if (valid_moves[i][0] == valid_moves[random_valid_move_index][0] && valid_moves[i][1] == valid_moves[random_valid_move_index][1]) {
            break;
        }
    }

    switch (i) {
        case 0:
            dir = 'D';
            break;
        case 1:
            dir = 'U';
            break;
        case 2:
            dir = 'R';
            break;
        case 3:
            dir = 'L';
            break;
    }

    // Make the move
    int a = b->board[new_row][new_col];
    printf("Computer Move: %d-%c\n\n", a, dir);
    int_swap(&b->board[blank_row][blank_col], &b->board[new_row][new_col]);
    return a;
}

void make_solvable_board(board* b) {
    do {
        shuffle_board(b);
    } while (!is_solvable(b));
}

void print_to_file(board* b) {
    FILE* fp = fopen("board.txt", "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (b->board[i][j] != 0) fprintf(fp, "%d ", b->board[i][j]);
            else fprintf(fp, "_ ");
        }
        fprintf(fp, "\n");
    }

    fprintf(fp, "\n");
    fclose(fp);
}

int calculate_score(int count) {
    return 1000 - (count * 10);
}

int is_empty() {
    FILE* fp = fopen("best_score.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    if (getchar() == EOF) return 1;
    return 0;
}

void save_score(int count) {
    int score = calculate_score(count);

    FILE* fp = fopen("best_score.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    // Check if score is bigger then best score
    int best_score;
    fscanf(fp, "%d", &best_score);
    fclose(fp);
    if (is_empty() || score > best_score) {
        fp = fopen("best_score.txt", "w");
        if (fp == NULL) {
            printf("Error opening file!\n");
            exit(1);
        } 
        fprintf(fp, "%d", score);
        fclose(fp);
    }
}

void auto_solve(board* b) {
    int n;
    int prev;
    int i = 0;
    while (!is_solved(b)) {
        printf("\n%d\n", i++);
        n = make_move(b, prev);
        prev = n;
        printf("prev move: %d\n", prev);
        print_board(b);
        printf("\n");
    }
    printf("solved\n");
}

void auto_finish(board* b, int prev, int count) {
    if (is_solved(b)) {
        printf("Computer finished the game.\n\n");
        printf("Total number of computer moves: %d\n\n", count);
        save_score(count);
        return;
    }

    int n;
    n = make_move(b, prev);
    prev = n;
    print_board(b);
    print_to_file(b);  

    //printf("\ncount: %d\n", count);  // test     
    printf("\n");

    auto_finish(b, prev, ++count);
}

void manual_solve(board* b) {
    int count = 0;
    int number;
    char direction;
    while (!is_solved(b)) {
        printf("\n");
        printf("Enter your move (number-direction, e.g., 2-R): ");
        scanf("%d-%c", &number, &direction);
        printf("\n");
        move(b, number, direction);
        print_board(b);
        print_to_file(b);
        count++;
    }
    printf("Congratulations! You finished the game.\n\n");
    printf("Total number of moves: %d\n\n", count);
    save_score(count);
}

void display_best_score() {
    FILE* fp = fopen("best_score.txt", "r");
    if (fp == NULL) {
        printf("Error opening best score file!\n");
        exit(1);
    }
    int best_score;
    fscanf(fp, "%d", &best_score);
    fclose(fp);
    printf("The best score is %d...\n\n", best_score);
}

void clean_board_file() {
    // Clean up board.txt file
    FILE* fp = fopen("board.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    fclose(fp);
}

int main() {
    srand(time(NULL));
    board b;

    clean_board_file();

    // Make board
    initialize_board(&b);
    make_solvable_board(&b);

    int option;

    do {
        make_solvable_board(&b);
        //clean_board_file();
        printf("Welcome to the 8-Puzzle Game!\n");
        printf("Please select an option:\n");
        printf("1. Play game as a user\n");
        printf("2. Finish the game with PC\n");
        printf("3. Show the best score\n");
        printf("4. Exit\n");
        printf("> ");
        scanf("%d", &option);
        printf("\n");

        switch (option) {
            case 1:
                // Code to handle playing the game as a user
                clean_board_file();
                print_board(&b);
                manual_solve(&b);
                break;
            case 2:
                // Code to finish the game with PC
                clean_board_file();
                print_board(&b);
                print_to_file(&b);
                printf("\n");
                auto_finish(&b, 0, 0);
                //auto_solve(&b);
                break;
            case 3:
                // Code to show the best score
                display_best_score();
                break;
            case 4:
                printf("Exiting the program. Goodbye!\n\n");
                break;
            default:
                printf("Invalid option. Please select a valid option.\n");
        }
    } while (option != 4);

    return 0;
}

