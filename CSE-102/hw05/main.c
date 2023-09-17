#include <stdio.h>
#include <math.h>

// Functions for part1

// Convert to lowercase
char lowercase(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + 'a' - 'A';
    }
    return c;
}

void part1() {
    // Initialize variables
    char file_name[100], c, frequencies[26] = {0};
    int num = 0, k = 0;
    FILE* fp;

    // Get file name
    printf("Enter the file name: ");
    scanf("%s", file_name);

    // Open file    
    fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("Error opening the file!\n");
        return;
    }

    // Read file
    while ((c = fgetc(fp)) != EOF) {
        // Convert to lowercase
        c = lowercase(c);
        // Increment frequency
        if (c >= 'a' && c <= 'z') {
            frequencies[c - 'a']++;
        }
    }

    // Print frequencies
    for (int i = 0; i < 26; i++) {
        printf("%c: %d\n", 'a' + i, frequencies[i]);
    }
    fclose(fp);
}

// Functions for part2

// Enumarate colors
typedef enum Color {RED, GREEN, BLUE, YELLOW, ORANGE} Color;

// Define length-3 vectors for each color
double colors[][3] = {
    {1.0, 0.0, 0.0},   // RED
    {0.0, 1.0, 0.0},   // GREEN
    {0.0, 0.0, 1.0},   // BLUE
    {0.5, 0.5, 0.0},   // YELLOW
    {0.5, 0.4, 0.2}    // ORANGE
};

// Print color name from color enum
void get_color(Color color) {
    switch (color) {
        case RED:
            printf("RED");
            break;           
        case GREEN:
            printf("GREEN");
            break;            
        case BLUE:
            printf("BLUE");
            break;            
        case YELLOW:
            printf("YELLOW");
            break;            
        case ORANGE:
            printf("ORANGE");
            break;
        default:
            printf("Invalid color\n");
    }
}

// Return the distance between two vectors
double distance(double v1[], double v2[]) {
    return sqrt(pow(v1[0] - v2[0], 2) + pow(v1[1] - v2[1], 2) + pow(v1[2] - v2[2], 2));
}

// Mix the colors and return the closest color
Color mix(Color color1, Color color2) {
    double result[3];

    // Calculate average color values
    for (int i = 0; i < 3; i++) {
        result[i] = (colors[color1][i] + colors[color2][i]) / 2.0;
    }

    // Find closest color
    double min_distance = distance(result, colors[0]);
    Color closest = 0;
    for (int i = 1; i < 5; i++) {
        if (distance(result, colors[i]) < min_distance) {
            min_distance = distance(result, colors[i]);
            closest = i;
        }
    }

    return closest;
}

Color colorMixer(Color color1, Color color2, Color (*function)(Color, Color)) {
    return (*function)(color1, color2);
}

int part2() {
    char color1_char, color2_char;
    Color color1, color2, mixed_color;
    printf("Enter Color 1 (r,g,b,y,o): ");
    scanf(" %c", &color1_char);
    printf("Enter Color 2 (r,g,b,y,o): ");
    scanf(" %c", &color2_char);
    switch (color1_char) {
        case 'r':
            color1 = RED;
            break;
        case 'g':
            color1 = GREEN;
            break;
        case 'b':
            color1 = BLUE;
            break;
        case 'y':
            color1 = YELLOW;
            break;
        case 'o':
            color1 = ORANGE;
            break;
        default:
            printf("Invalid input for color 1\n");
            return 1;
    }
    switch (color2_char) {
        case 'r':
            color2 = RED;
            break;
        case 'g':
            color2 = GREEN;
            break;
        case 'b':
            color2 = BLUE;
            break;
        case 'y':
            color2 = YELLOW;
            break;
        case 'o':
            color2 = ORANGE;
            break;
        default:
            printf("Invalid input for color 2\n");
            return 1;
    }
    mixed_color = colorMixer(color1, color2, &mix);
    printf("Mixed Color: ");
    get_color(mixed_color);
    printf(" [%.1lf, %.1lf, %.1lf]\n", colors[mixed_color][0], colors[mixed_color][1], colors[mixed_color][2]);
    
}

// Functions for part3

// Print board to terminal
void print_board(char board[][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }   
}

// Check if player win
int check_win(char board[][3], char p) {

    // Check rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == p && board[i][1] == p && board[i][2] == p) {
            return 1;
        }
    }

    // Check columns
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == p && board[1][i] == p && board[2][i] == p) {
            return 1;
        }
    }

    // Check diagonals
    if (board[0][0] == p && board[1][1] == p && board[2][2] == p) return 1;
    if (board[2][0] == p && board[1][1] == p && board[0][2] == p) return 1;

    return 0;
}

// Check if board is full
int check_full(char board[][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '-') return 0;
        }
    }

    return 1;
}

void part3() {
    int row, col;
    char board[3][3], again;

    // Game loop
    do {

        // Reset board
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = '-';
            }
        }

        // Loops for player moves
        while (1) {
            // Player 1 move
            printf("Player 1 (X), enter your move (row, col): ");
            scanf("%d %d", &row, &col);
            while (board[row][col] != '-' || row < 0 || row > 2 || col < 0 || col > 2) {
                printf("Invalid move. Please enter again: ");
                scanf("%d %d", &row, &col);
            } 
            board[row][col] = 'X';
            print_board(board);

            // Check if board is full
            if (check_full(board)) {
                printf("Board is full. Game over!\n");
                break;
            }

            // Check if user win
            if(check_win(board, 'X')) {
                printf("Player 1 (X) wins!\n");
                break;
            }

            // Player 2 move
            printf("Player 2 (O), enter your move (row, col): ");
            scanf("%d %d", &row, &col);
            while (board[row][col] != '-' || row < 0 || row > 2 || col < 0 || col > 2) {
                printf("Invalid move. Please enter again: ");
                scanf("%d %d", &row, &col);
            }
            board[row][col] = 'O';

            print_board(board);

            // Check if user win
            if (check_win(board, 'O')) {
                printf("Player 2 (O) wins!\n");
                break;     
            }
        }

        // Ask if user wants to play again
        printf("Play again? (y/n): ");
        scanf(" %c", &again);

    } while (again == 'y');
}


int main() {
    printf("\n");
    part1();
    printf("\n");
    part2();
    printf("\n");
    part3();
    
    return 0;
}