#include <stdio.h>

int main() {
    int n;
    printf("Enter the filename: ");
    char filename[100];
    scanf("%s", filename);

    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Error opening the file!\n");
        return 1;
    }

    fscanf(fp, "%d", &n);

    int age[n];
    char occupation[n], team[n];
    float salary[n];

    for (int i = 0; i < n; i++) {
        fscanf(fp, "%d %c %f %c", &age[i], &occupation[i], &salary[i], &team[i]); // read data from file
    }
    fclose(fp);

    char selected_team;
    printf("Please select a team: ");
    scanf(" %c", &selected_team);

    int count = 0;
    float total_salary = 0.0;
    for (int i = 0; i < n; i++) {
        if (team[i] == selected_team) {
            count++;
            total_salary += salary[i];
        }
    }

    if (count > 0) {
        float avg_salary = total_salary / count;
        printf("Average salaries of fans of %c: %.1f\n", selected_team, avg_salary);
    }   
    else {  
        printf("There are no fans of %c in the database!\n", selected_team);
    }

    return 0;
}
