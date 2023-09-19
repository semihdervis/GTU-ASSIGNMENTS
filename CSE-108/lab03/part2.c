#include <stdio.h>
#include <string.h>

int main() {
    float score1, score2, score3, avg_score;
    char grade1, grade2, grade3;
    printf("\n");
    printf("Enter your scores: ");
    scanf("%f%f%f", &score1, &score2, &score3);

    avg_score = (score1 + score2 + score3) / 3.0;

    switch ((int)score1 / 10) {
    case 10:
    case 9:
        printf("Your letter grades are A+, ");

      break;
    case 8:
        printf("Your letter grades are A, ");

        break;
    case 7:
        printf("Your letter grades are B+, ");

      break;
    case 6:
        printf("Your letter grades are B, ");

      break;
    case 5:
        printf("Your letter grades are C, ");

      break;
    case 4:
        printf("Your letter grades are D, ");

      break;
    default:
        printf("Your letter grades are F, ");

  }

    switch ((int)score2 / 10) {
    case 10:
    case 9:
        printf("A+");

      break;
    case 8:
        printf("A");

        break;
    case 7:
        printf("B+");

      break;
    case 6:
        printf("B");

      break;
    case 5:
        printf("C");

      break;
    case 4:
        printf("D");

      break;
    default:
        printf("F");
    }

    switch ((int)score3 / 10) {
    case 10:
    case 9:
        printf(" and A+");

      break;
    case 8:
        printf(" and A");

        break;
    case 7:
        printf(" and B+");

      break;
    case 6:
        printf(" and B");

      break;
    case 5:
        printf(" and C");

      break;
    case 4:
        printf(" and D");

      break;
    default:
        printf(" and F");
    }

    printf(" with an %.1f average.\n",avg_score);
    printf("\n");

    return 0;
}