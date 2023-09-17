#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define UP 'w'
#define LEFT 'a'
#define DOWN 's'
#define RIGHT 'd'

void draw_room(int n, int x, int y, int dx, int dy){  // Part 1
    for(int i = 0; i < 2 * n + 1; i++){
        printf("-");
    }
    printf("\n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n + 1; j++){
            printf("|");
            if(x - 1 == j && y - 1 == i) printf("C");  // Places the character
            else if(dx - 1 == j && dy - 1 == i) printf("D");  // Places the door
            else printf(" ");
        }
        printf("\n");
    }
    for(int i = 0; i < 2 * n + 1; i++){
        printf("-");
    }
    printf("\n");
}

int control_status(int x, int y, int dx, int dy){ // Part 3
    if(x == dx && y == dy) return 1;
    return 0;
}

void gameplay(){  // Part 2
    int n, x, y, dx, dy;
    do {
        printf("Please enter a number between 5 and 10: ");
        scanf("%d", &n);
        if(n < 5 || n > 10) {
            printf("Error: the number you entered is not between 5 and 10. Please try again.\n");
        }
    } while(n < 5 || n > 10);

    srand(time(NULL));  // Set the seed 
    do{
        x = (rand() % (n)) + 1;
        y = (rand() % (n)) + 1;
        dx = (rand() % (n)) + 1;
        dy = (rand() % (n)) + 1;
    } while(control_status(x, y, dx, dy));  // Prevents character and door from spawning in the same spot

    draw_room(n, x, y, dx, dy);
    int number_of_moves = 0;
    while(1){
        char move;
        printf("Enter your move: ");
        scanf(" %c", &move);
        switch(move){
            case UP:
                if(y == 1) printf("Error: Invalid direction\n");  // Prevent cursor from leaving the room
                else {
                    y--;
                    number_of_moves++;
                }
                break;
            case LEFT:
                if(x == 1) printf("Error: Invalid direction\n");  // Prevent cursor from leaving the room
                else {
                    x--;
                    number_of_moves++;
                }
                break;
            case DOWN:
                if(y == n) printf("Error: Invalid direction\n");  // Prevent cursor from leaving the room
                else {
                    y++;
                    number_of_moves++;
                }
                break;
            case RIGHT:
                if(x == n) printf("Error: Invalid direction\n");  // Prevent cursor from leaving the room
                else {
                    x++;
                    number_of_moves++;
                }
                break;
            default:
                printf("Error: Invalid direction\n");
        }
        if(control_status(x, y, dx, dy)){  // Checks if player win
            printf("Game Over!\n");
            printf("Your number of moves = %d\n", number_of_moves);
            return; 
        } 
        draw_room(n, x, y, dx, dy);
    }
}

void the_game(){ // Part 4
    while(1){
        char selection;
        printf("Welcome to the 2D puzzle game!\n1. New Game\n2. Help\n3. Exit\nSelect Operation: "); // Menu
        scanf(" %c", &selection);
        switch(selection){
            case '1': // New Game
                gameplay();
                break;
            case '2': // Help
                printf("The character is able to move one space in any of the four cardinal directions: up, down, left, and right. ");                           
                printf("Diagonal moves are not allowed. The user will input their desired move using the following keys: 'a' for ");
                printf("left, 'd' for right, 'w' for up, and 's' for down.\n");
                break;
            case '3': // Exit
                printf("Goodbye\n");
                return;
            default:
                printf("Error: Invalid selection\nPlease try again: ");
        }
    }
}

int main() {
    the_game();

    return 0;
}