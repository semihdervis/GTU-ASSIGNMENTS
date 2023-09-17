#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 10

typedef struct {
    int row;
    int col;
} Point;

typedef struct {
    char type;
    int value;
} Block;

typedef struct {
    Point* body;
    int length;
} Snake;

Block*** init_board() {
    Block*** board = (Block***)malloc(BOARD_SIZE * sizeof(Block**));
    for (int i = 0; i < BOARD_SIZE; i++) {
        board[i] = (Block**)malloc(BOARD_SIZE * sizeof(Block*));
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = (Block*)malloc(sizeof(Block));
            board[i][j]->type = 'e';
            board[i][j]->value = 0;
        }
    }

    // Randomly place an obstacle
    int obstacleRow = rand() % 10;
    int obstacleCol = rand() % 10;
    board[obstacleRow][obstacleCol]->type = 'o';
    board[obstacleRow][obstacleCol]->value = 1;

    // Randomly place a bait
    int baitRow, baitCol;
    do {
        baitRow = rand() % 10;
        baitCol = rand() % 10;
    } while (baitRow == obstacleRow && baitCol == obstacleCol);
    board[baitRow][baitCol]->type = 'b';
    board[baitRow][baitCol]->value = 0;

    return board;
}

void draw_board(Block*** board, Snake* snake) {
    // Draw top frame
    for (int i = 0; i < BOARD_SIZE + 2; i++) {
        printf("- ");
    }
    printf("\n");

    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("| "); // Left frame
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (snake->body[0].row == i && snake->body[0].col == j) {
                printf("O ");
                goto end;
            }
            // Check if snake body
            for (int k = 1; k < snake->length; k++) {
                if (snake->body[k].row == i && snake->body[k].col == j) {
                    printf("X ");
                    goto end;
                }
            }
            // Check if snake head
            if (board[i][j]->type == 'o')
                printf("%-2d", board[i][j]->value);
            else if (board[i][j]->type == 'b')
                printf(". ");
            else if (board[i][j]->type == 'e')
                printf("  ");
            end:
        }
        printf("|\n"); // Right frame
    }

    // Draw bottom frame
    for (int i = 0; i < BOARD_SIZE + 2; i++) {
        printf("- ");
    }
    printf("\n");
}

void move(Snake* snake) {
    char direction;
    printf("Enter direction: ");
    scanf(" %c", &direction);

    int headRow = snake->body[0].row;
    int headCol = snake->body[0].col;

    if (direction == 'w' && headRow > 0)
        snake->body[0].row--;
    else if (direction == 'a' && headCol > 0)
        snake->body[0].col--;
    else if (direction == 's' && headRow < BOARD_SIZE - 1)
        snake->body[0].row++;
    else if (direction == 'd' && headCol < BOARD_SIZE - 1)
        snake->body[0].col++;

}

int check_status(Snake* snake, Block*** board) {
    
    int hr = snake->body[0].row;
    int hc = snake->body[0].col;
    
    // Check if snake hit the wall
    if (hr < 0 || hc < 0 || hr > 9 || hc > 9) {
        return 0;
    }

    // Check if snake hit the obstacle
    if (board[hr][hc]->type == 'o') {

        // Check if obstacle is longer than snake
        if (board[hr][hc]->value > snake->length - 1) {
            return 0;
        }

        // Otherwise, remove obstacle from board
        else {
            board[hr][hc]->type = 'e';
            board[hr][hc]->value = 0;
        }
    }

    // Check if snake hit it's body
    for (int i = 1; i < snake->length; i++) {
        if (hr == snake->body[i].row && hc == snake->body[i].col) {
            return 0;
        }
    }



    return 1;
}

void update(Snake* snake, Block*** board, int* counter) {

    int hr = snake->body[0].row;
    int hc = snake->body[0].col;

    // If snake eat the bait
    if (board[hr][hc]->type == 'b') { 

        int flag;

        // Increase length of snake
        snake->length++;

        // Increase size of body
        snake->body = realloc(snake->body, snake->length * sizeof(Point));

        // Create random bait
        int br, bc;
        do {
            flag = 0;
            
            br = rand() % 10;
            bc = rand() % 10;

            // Check if random bait is on snake
            for (int i = 0; i < snake->length; i++) {
                if (br == snake->body[i].row && bc == snake->body[i].col) {
                    flag = 1;
                    break;
                }
            }

        } while (board[br][bc]->type != 'e' || flag);
        
        // Modify board after bait
        board[br][bc]->type = 'b';

        // Remove eaten bait from board
        board[hr][hc]->type = 'e';

    }

    // Create an obstacle in every five move
    if (*counter % 5 == 0) {
        int flag = 0;
        int or, oc;

        Point * obstacles = malloc(3 * sizeof(Point));
        //Point obstacles[3];

        // Count number of obstacles on board
        int numObstacle = 1;
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board[i][j]->type == 'o') {
                    // Save the position of obstacles
                    obstacles[numObstacle - 1].row = i;
                    obstacles[numObstacle - 1].col = j;

                    numObstacle++;
                }
            }
        }

        // If number of obstacles is less than 3, create an obstacle
        if (numObstacle <= 3) {

            // Create random obstacle on the board
            do {
                flag = 0;
                or = rand() % 10;
                oc = rand() % 10;

                // Check if random obstacle is on snake
                for (int i = 0; i < snake->length; i++) {
                    if (or == snake->body[i].row && oc == snake->body[i].col) {
                        flag = 1;
                        break;
                    }
                }

            } while (board[or][oc]->type != 'e' || flag);

            // Modify board after obstacle
            board[or][oc]->type = 'o';
            board[or][oc]->value++;
        }

        // If number of obstacles is 3, increment the value of one of them
        else {
            int ro = rand() % 3;
            board[obstacles[ro].row][obstacles[ro].col]->value++;
        } 

    }



    // Update snake's body
    for (int i = snake->length - 1; i > 0; i--) {
        snake->body[i].row = snake->body[i - 1].row;
        snake->body[i].col = snake->body[i - 1].col;
    }
}



void play(Block*** board) {
    srand(time(NULL));

    int len = 2;

    // initialize snake
    Snake snake;
    snake.body = malloc(sizeof(Point));
    snake.body[0].row = 0;
    snake.body[0].col = 0;
    snake.length = len;

    // Initialize counter 
    int counter = 0;


    draw_board(board, &snake);
    while (1) {
        counter++;
        move(&snake);
        if (check_status(&snake, board) == 0) {
            printf("Game over\n");
            break;
        }
        update(&snake, board, &counter);
        draw_board(board, &snake);
    }

    // Free memory
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            free(board[i][j]);
        }
        free(board[i]);
    }
    free(board);
    free(snake.body);
}

int main() {
    Block*** board = init_board();

    play(board);

    return 0;
}