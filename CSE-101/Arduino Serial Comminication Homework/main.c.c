#include "stdio.h"
#include "windows.h"
void main(){
    int num, sq, a;
    FILE *fp;
    fp = fopen("COM5", "w+");
    Sleep(2000);
    while (1) {
        printf("## WELCOME TO GTU ARDUINO LAB ##\n"
            "## STUDENT NAME: SEMIH DERVIS ##\n"
            "## PLEASE SELECT FROM THE FOLLOWING ##\n"
            "## MENU :##\n"
            "(1) TURN ON LED ON ARDUINO\n"
            "(2) TURN OFF LED ON ARDUINO\n"
            "(3) FLASH ARDUINO LED 3 TIMES\n"
            "(4) SEND A NUMBER TO ARDUINO TO COMPUTE SQUARE BY ARDUINO\n"
            "(5) Button press counter (bonus item)\n"
            "(0) EXIT\n"
            "PLEASE SELECT : ");
        scanf("%d", &num);
        fprintf(fp, "%d", num);
        fflush(fp);
        if (num == 3){
            fprintf(fp, "%d", 2);
            fflush(fp);
        }
        while (num == 4){
            printf("ENTER A NUMBER : ");
            scanf("%d", &sq);
            Sleep(1000);
            fprintf(fp, "%d", sq);
            Sleep(2000);
            fscanf(fp, "%d", &a);
            Sleep(1000);
            printf("SQUARE OF THE NUMBER IS : ");
            printf("%d\n", a);
            fflush(fp);            
        }
        if (num == 0){
            break;
        }
    }
    fclose(fp);
}