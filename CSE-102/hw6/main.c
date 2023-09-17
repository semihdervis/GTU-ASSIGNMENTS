#include <stdio.h>
#include <stdlib.h>

void displayMenu() {
    printf("Welcome, please select an option to continue:\n");
    printf("1- File Operations\n");
    printf("2- Query products\n");
    printf("3- Check stock status\n");
    printf("4- Stock control by brand\n");
    printf("5- Export report\n");
}

void fileOperationsMenu() {
    printf("File Operations Submenu\n");
    printf("1. Add a new product\n");
    printf("2. Delete a product\n");
    printf("3. Update a product\n");
    printf("4. Add feature to products\n");
    printf("5. Add a new stock entry\n");
    printf("6. Delete a stock entry\n");
    printf("7. Update a stock entry\n");
    printf("8. Back to main menu\n");
}

// Write manuel strcpy function
void my_strcpy(char dest[], char src[]) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    } 
    dest[i] = '\0';
}

// Write manuel strcmp function
int my_strcmp(char s1[], char s2[]) {
    int i = 0;
    while (s1[i] != '\0' || s2[i] != '\0') {
        if (s1[i] != s2[i]) {   
            return 0;
            break;
        }
        i++;
    }
    return 1;
}


void fileOperations() {

    // Initialize product arrays
    char nameFeatures[10][20]; // Store features names
    int pid[100];
    char type[100];
    char name[100][20];
    char brand[100][20];
    double price[100];
    char features[100][10][20]; // Store additional features

    // Initialize product variables
    int numProducts = 0;
    int numFeatures = 0;
    int numAdditionalFeatures = 0;
    char c;
    int selection;
    int sPid;
    char sFeature[10];



    // Initialize stock arrays
    int sid[100];
    int s_pid[100];
    char branch[100][20];
    int stock[100];

    // Initialize stock variables
    int m = 0;
    int sSid;


    // Open products file
    FILE* fp = fopen("products.txt", "r");
    if (fp == NULL) {
        printf("Error opening file");
        return;
    }

    // Ignore first line
    while((c = fgetc(fp)) != '\n') {
        // Count number of features
        if (c == ',') {
            numFeatures++;
        }
    }
    numFeatures++;
    numAdditionalFeatures = numFeatures - 5;


    // Go back to beginning of file
    rewind(fp);

    // Count number of products
    while ((c = fgetc(fp)) != EOF) {
        if(c == '\n') {
            numProducts++;
        }
    }



    // Go back to beginning of file
    rewind(fp);

    // Read features names and store it to array
    for (int i = 0; i < numFeatures; i++) {
        if(i == numFeatures - 1){
            fscanf(fp, "%s", nameFeatures[i]);
            break;
        }
        fscanf(fp, "%[^,],", nameFeatures[i]);
    }


    // Go back to beginning of file
    rewind(fp);

    // Ignore first line
    while (fgetc(fp) != '\n');


    
    // Read products file
    int j = 0; // j also stands for number of products
    while (fscanf(fp, "%d,%c,%[^,],%[^,],%lf",  &pid[j], &type[j], name[j], brand[j], &price[j]) == 5) {
        //printf("%d %c %s %s %lf", pid[j], type[j], name[j], brand[j], price[j]);

        // Read additional features
        for (int i = 0; i < numAdditionalFeatures; i++) {

            // Read last feature (not parse comma)
            if (i == numAdditionalFeatures - 1) {
                fscanf(fp, "%s", features[j][i]);
                //printf(" %s", features[j][i]);
            }

            // Read other features (parse comma)
            else {
                fscanf(fp, ",%[^,],", features[j][i]);
                //printf(" %s", features[j][i]);
            }
        }
        //printf("\n");
        j++;
    }

    // Fill pid array with numbers
    for (int i = 0; i < 99; i++) {
        pid[i] = i + 1;
    }


    //----------------------------Read stocks file-----------------------------//
    // Open stock file
    FILE* fp2 = fopen("stocks.txt", "r");
    if (fp2 == NULL) {
        printf("Error opening file");
        return;
    }

    // Ignore first line
    while (fgetc(fp2) != '\n');

    // Fill arrays
    while (fscanf(fp2, "%d,%d,%[^,],%d", &sid[m], &s_pid[m], branch[m], &stock[m]) == 4) {
        m++;
    }

    // Fill sid array with numbers
    for (int i = 0; i < 100; i++) {
        sid[i] = i + 1;
    }
    //---------------------------End of Read stocks file-------------------------//


    
    while (1) {
        fileOperationsMenu();
        printf("Enter your selection: ");
        scanf("%d", &selection);
        switch (selection) {
            case 1:
                // --------------------------Add a product code block----------------------- //
                // Add a product
                printf("Enter");
                for(int i = 1; i < numFeatures; i++){
                    printf(" %s", nameFeatures[i]);
                    if(i == numFeatures - 1){
                        printf(" (with spaces between): ");
                    }
                }

                // Take user input for adding product
                scanf(" %c %s %s %lf", &type[j], name[j], brand[j], &price[j]);
                printf(" %c %s %s %lf", type[j], name[j], brand[j], price[j]);
                for (int i = 0; i < numAdditionalFeatures; i++) {
                    scanf(" %s", features[j][i]);
                }
                j++; // Increment index 



                // Print arrays to file
                fp = fopen("products.txt", "w");
                for (int i = 0; i < numFeatures; i++) {  // Write headers
                    if(i == numFeatures - 1){
                        fprintf(fp, "%s\n", nameFeatures[i]);
                        break;
                    }
                    fprintf(fp, "%s,", nameFeatures[i]);
                }

                for (int i = 0; i < j; i++) {  // Write data
                    fprintf(fp, "%d,%c,%s,%s,%.1lf", pid[i], type[i], name[i], brand[i], price[i]);
                    for (int k = 0; k < numAdditionalFeatures; k++) {
                        fprintf(fp, ",%s", features[i][k]);
                    }
                    fprintf(fp, "\n");
                }
                fclose(fp);
                // --------------------------End of add a product code block----------------------- //
                
                break;


            case 2:
                // --------------------------Delete a product code block--------------------------- //
                // Delete a product
                int delete_pid;
                printf("Enter pid to delete: ");
                scanf("%d", &delete_pid);
                for (int i = delete_pid - 1; i < j; i++) {
                    //pid[i] = pid[i + 1];
                    type[i] = type[i + 1];
                    my_strcpy(name[i], name[i + 1]);
                    my_strcpy(brand[i], brand[i + 1]);
                    price[i] = price[i + 1];
                    for (int k = 0; k < numAdditionalFeatures; k++) {
                        my_strcpy(features[i][k], features[i + 1][k]);
                    }
                }

                j--;

                
                // Print arrays to file
                fp = fopen("products.txt", "w");
                for (int i = 0; i < numFeatures; i++) {  // Write headers
                    if(i == numFeatures - 1){
                        fprintf(fp, "%s\n", nameFeatures[i]);
                        break;
                    }
                    fprintf(fp, "%s,", nameFeatures[i]);
                }

                for (int i = 0; i < j; i++) {  // Write data
                    fprintf(fp, "%d,%c,%s,%s,%.1lf", pid[i], type[i], name[i], brand[i], price[i]);
                    for (int k = 0; k < numAdditionalFeatures; k++) {
                        fprintf(fp, ",%s", features[i][k]);
                    }
                    fprintf(fp, "\n");
                }
                fclose(fp);
                // --------------------------End of delete a product code block----------------------- //
                break;

            case 3:
                // Update a product
                printf("Enter pid to update: ");
                scanf("%d", &sPid);
                printf("Enter a feature to update: ");
                scanf("%s", sFeature);
                printf("Enter new value: ");
                for (int i = 0; i < numFeatures; i++) {
                    if (my_strcmp(sFeature, nameFeatures[i])) {
                        if (i == 1) {
                            scanf("%c", &type[sPid - 1]);
                            break;                           
                        }
                        else if (i == 2) {
                            scanf("%s", name[sPid - 1]);
                            break;
                        }
                        else if (i == 3) {
                            scanf("%s", brand[sPid - 1]);
                            break;
                        }
                        else if (i == 4) {
                            scanf("%lf", &price[sPid - 1]);
                            break;
                        }
                        else {
                            scanf("%s", features[sPid - 1][i - 5]); 
                            break;
                        }
                    }
                }    

                // Print arrays to file
                fp = fopen("products.txt", "w");
                for (int i = 0; i < numFeatures; i++) {  // Write headers
                    if(i == numFeatures - 1){
                        fprintf(fp, "%s\n", nameFeatures[i]);
                        break;
                    }
                    fprintf(fp, "%s,", nameFeatures[i]);
                }

                for (int i = 0; i < j; i++) {  // Write data
                    fprintf(fp, "%d,%c,%s,%s,%.1lf", pid[i], type[i], name[i], brand[i], price[i]);
                    for (int k = 0; k < numAdditionalFeatures; k++) {
                        fprintf(fp, ",%s", features[i][k]);
                    }
                    fprintf(fp, "\n");
                }
                fclose(fp);

                break;

            // Add a feature
            case 4:
                printf("Enter feature name: ");
                scanf("%s", nameFeatures[numFeatures]);

                // Initialize all products as none
                for (int i = 0; i < j; i++) {
                    my_strcpy(features[i][numAdditionalFeatures], "none");
                }

                numFeatures++;  // Increment number of features
                numAdditionalFeatures++;
                
                // Print last added feature of products
                for (int i = 0; i < j; i++) {
                    printf(" %s", features[i][numAdditionalFeatures - 1]);
                }
                
                // Print arrays to file
                fp = fopen("products.txt", "w");
                for (int i = 0; i < numFeatures; i++) {  // Write headers
                    if(i == numFeatures - 1){
                        fprintf(fp, "%s\n", nameFeatures[i]);
                        break;
                    }
                    fprintf(fp, "%s,", nameFeatures[i]);
                }

                for (int i = 0; i < j; i++) {  // Write data
                    fprintf(fp, "%d,%c,%s,%s,%.1lf", pid[i], type[i], name[i], brand[i], price[i]);
                    for (int k = 0; k < numAdditionalFeatures; k++) {
                        fprintf(fp, ",%s", features[i][k]);
                    }
                    fprintf(fp, "\n");
                }
                fclose(fp);
                break;

            // Add a stock
            case 5:
                // Take user input to add stock
                printf("Enter pid branch current_stock (with spaces between): ");
                scanf("%d %s %d", &s_pid[m], branch[m], &stock[m]);
                printf("%d %s %d\n", s_pid[m], branch[m], stock[m]);
                m++;
                
                // Print arrays to file
                fp2 = fopen("stocks.txt", "w");
                fprintf(fp2, "sID,pID,Branch,Current_stock\n"); // Write headers
                for (int i = 0; i < m; i++) {
                    fprintf(fp2, "%d,%d,%s,%d\n", sid[i], s_pid[i], branch[i], stock[i]);
                }
                fclose(fp2);
                break;

            // Delete a stock
            case 6:
                // Take user input to delete stock
                printf("Enter sID to delete: ");
                scanf("%d", &sSid);
                for (int i = sSid - 1; i < m; i++) {
                    s_pid[i] = s_pid[i + 1];
                    my_strcpy(branch[i], branch[i + 1]);
                    stock[i] = stock[i + 1];
                }
                m--;

                // Print arrays to file
                fp2 = fopen("stocks.txt", "w");
                fprintf(fp2, "sID,pID,Branch,Current_stock\n"); // Write headers
                for (int i = 0; i < m; i++) {
                    fprintf(fp2, "%d,%d,%s,%d\n", sid[i], s_pid[i], branch[i], stock[i]);
                }
                fclose(fp2);
                break;

            // Update a stock
            case 7:
                printf("Enter sID to update: ");
                scanf("%d", &sSid);
                printf("Enter a feature to update: ");
                scanf("%s", sFeature);
                printf("Enter new value: ");
                if (my_strcmp(sFeature, "pID")) {
                    scanf("%d", &s_pid[sSid - 1]);
                }
                else if (my_strcmp(sFeature, "Branch")) {
                    scanf("%s", branch[sSid - 1]);
                }
                else if (my_strcmp(sFeature, "Current_stock")) {
                    scanf("%d", &stock[sSid - 1]);
                }

                // Print arrays to file
                fp2 = fopen("stocks.txt", "w");
                fprintf(fp2, "sID,pID,Branch,Current_stock\n"); // Write headers
                for (int i = 0; i < m; i++) {
                    fprintf(fp2, "%d,%d,%s,%d\n", sid[i], s_pid[i], branch[i], stock[i]);
                }
                fclose(fp2);

                break;

            case 8:
                printf("returning main menu\n");
                return;
        }
    }

    


    
    // Print arrays to terminal
    for (int i = 0; i < j; i++) {
        printf("%d %c %s %s %lf", pid[i], type[i], name[i], brand[i], price[i]);
        for (int k = 0; k < numFeatures; k++) {
            printf(" %s", features[i][k]);
        }
        printf("\n");
    }
}  

// Part 3
void searchProduct() {

    // Open products file
    FILE* fp = fopen("products.txt", "r");
    if (fp == NULL) {
        printf("Error opening file");
        return;
    }

    // Initialize feature variables
    char nameFeatures[10][20]; // Store features names
    int pid;
    char type;
    char name[20];
    char brand[20];
    double price;
    char features[20][20];

    // Initialize normal variables
    int choice;
    char c;
    int numFeatures = 0;
    int numAdditionalFeatures = 0;
    int j = 0;
    char sFeature[20];
    int k = 0;
    char sChar;
    double sDouble;
    char sString[20];

    // Ignore first line
    while((c = fgetc(fp)) != '\n') {
        // Count number of features
        if (c == ',') {
            numFeatures++;
        }
    }

    // Set the number of features
    numFeatures++;
    numAdditionalFeatures = numFeatures - 5;



    // Go back to beginning of file
    rewind(fp);

    // Read features names and store it to array
    for (int i = 0; i < numFeatures; i++) {
        if (i == numFeatures - 1) {
            fscanf(fp, "%s", nameFeatures[i]);
            break;
        }
        fscanf(fp, "%[^,],", nameFeatures[i]);
    }

    



    while (1) {
        // Print menu
        printf("1. List all products\n");
        printf("2. Filter products by brand, type, price, or a user-defined feature\n");
        printf("3. Back to main menu.\n");

        printf("Enter choice: ");
        scanf("%d", &choice);


        switch (choice) {
            // Print all products
            case 1:
                // Go back to beggining
                rewind(fp);

                // Ignore first line
                while (fgetc(fp) != '\n');

                // Read products file
                while (fscanf(fp, "%d,%c,%[^,],%[^,],%lf",  &pid, &type, name, brand, &price) == 5) {
                    printf("%d %c %s %s %lf", pid, type, name, brand, price);

                    // Read additional features
                    for (int i = 0; i < numAdditionalFeatures; i++) {

                        // Read last feature (not parse comma)
                        if (i == numAdditionalFeatures - 1) {
                            fscanf(fp, "%s", features[i]);
                            printf(" %s", features[i]);
                        }

                        // Read other features (parse comma)
                        else {
                            fscanf(fp, ",%[^,],", features[i]);
                            printf(" %s", features[i]);
                        }
                    }
                    printf("\n");
                }
                break;
            // Print filtered products
            case 2:
                // Take feature from user to filter 
                printf("Select the type of filter (");
                // Print feature names
                for (int i = 1; i < numFeatures; i++) {  // Write headers
                    printf("%s ", nameFeatures[i]);
                }
                printf(") : ");
                scanf("%s", sFeature);
                printf("Enter the filter value: ");
                // Take value from user to filter
                for (int i = 1; i <  numFeatures; i++) {
                    if (my_strcmp(sFeature, nameFeatures[i])) {
                        k = i;
                        if (k == 1) scanf(" %c", &sChar);
                        else if (k == 4) scanf("%lf", &sDouble);
                        else scanf("%s", sString);
                    }
                }
                

                // Go back to beggining
                rewind(fp);

                // Ignore first line
                while (fgetc(fp) != '\n');

                // Read products file
                while (fscanf(fp, "%d,%c,%[^,],%[^,],%lf",  &pid, &type, name, brand, &price) == 5) {
                    //printf("%d %c %s %s %lf", pid, type, name, brand, price);

                    // Read additional features
                    for (int i = 0; i < numAdditionalFeatures; i++) {

                        // Read last feature (not parse comma)
                        if (i == numAdditionalFeatures - 1) {
                            fscanf(fp, "%s", features[i]);
                            //printf(" %s", features[i]);
                        }

                        // Read other features (parse comma)
                        else {
                            fscanf(fp, ",%[^,],", features[i]);
                            //printf(" %s", features[i]);
                        }
                    }
                    //printf("\n");
                    if (k == 1) {
                        if (sChar == type) {
                            printf("%d %c %s %s %lf", pid, type, name, brand, price);
                            for (int i = 0; i < numAdditionalFeatures; i++) {
                                printf(" %s", features[i]);
                            }
                            printf("\n");
                        }
                    }
                    else if (k == 2) {
                        if (my_strcmp(sString, name)) {
                            printf("%d %c %s %s %lf", pid, type, name, brand, price);
                            for (int i = 0; i < numAdditionalFeatures; i++) {
                                printf(" %s", features[i]);
                            }
                            printf("\n");
                        }
                    }
                    else if (k == 3) {
                        if (my_strcmp(sString, brand)) {
                            printf("%d %c %s %s %lf", pid, type, name, brand, price);
                            for (int i = 0; i < numAdditionalFeatures; i++) {
                                printf(" %s", features[i]);
                            }
                            printf("\n");
                        }
                    }
                    else if (k == 4) {
                        if (sDouble == price)  {
                            printf("%d %c %s %s %lf", pid, type, name, brand, price);
                            for (int i = 0; i < numAdditionalFeatures; i++) {
                                printf(" %s", features[i]);
                            }
                            printf("\n");
                        }
                    }
                    else {
                        if (my_strcmp(sString, features[k - 5])) {
                            printf("%d %c %s %s %lf", pid, type, name, brand, price);
                            for (int i = 0; i < numAdditionalFeatures; i++) {
                                printf(" %s", features[i]);
                            }
                            printf("\n");
                        }
                    }
                }
                break;
            case 3:
                return;
        }
        
    }
}

void checkStock() {
    // Initialize stock arrays
    int sid;
    int s_pid;
    char branch[20];
    int stock;
    int choice;
    int sPid;
    char sBranch[20];

    while (1) {
        printf("1. Query stock of a given product in a specified branch\n");
        printf("2. List the stock of all products in a specified branch\n");
        printf("3. List out-of-stock products in a specified branch\n");
        printf("4. Return to the main menu\n");
        printf("Enter your choice: ");

        // Open stock file
        FILE* fp2 = fopen("stocks.txt", "r");
        if (fp2 == NULL) {
            printf("Error opening file");
            return;
        }

        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter pid: ");
                scanf("%d", &sPid);
                printf("Enter branch: ");
                scanf("%s", sBranch);
                break;
            case 2:
                printf("Enter branch: ");
                scanf("%s", sBranch);
                break;
            case 3:
                break;
            case 4:
                return;
        }

        // Ignore first line
        while (fgetc(fp2) != '\n');

        // Print filtered stocks
        while (fscanf(fp2, "%d,%d,%[^,],%d", &sid, &s_pid, branch, &stock) == 4) {
            if (choice == 1) {
                if (sPid == s_pid && my_strcmp(sBranch, branch)) {
                    printf("%d %d %s %d\n", sid, s_pid, branch, stock);
                }
            }  
            else if(choice == 2) {
                if (my_strcmp(sBranch, branch)) {
                    printf("%d %d %s %d\n", sid, s_pid, branch, stock);
                }
            }
            else if(choice == 3) {
                if (stock == 0) {
                    printf("%d %d %s %d\n", sid, s_pid, branch, stock);
                }
            }
        }
    }
}

void brandStockControl(double arr[][3], int* pLen) {
    // Declare variables
    char sBrand[20];
    double pid;
    double price;
    char type;
    char name[20];
    char brand[20];
    char c;
    int numFeatures = 0;
    int numAdditionalFeatures;
    char features[20][20];
    int len = 0;

    // Declare stock variables
    int sid;
    double s_pid;
    char branch[20];
    double stock;

    // Array to store pids and prices of selected brand
    double tempArr[20][2];

    // Open files
    FILE* fp = fopen("products.txt", "r");
    FILE* fp2 = fopen("stocks.txt", "r");

    // Ignore first line
    while((c = fgetc(fp)) != '\n') {
        // Count number of features
        if (c == ',') {
            numFeatures++;
        }
    }

    // Set the number of features
    numFeatures++;
    numAdditionalFeatures = numFeatures - 5;



    // Go back to beginning of file
    rewind(fp);


    
    // Ask user for brand
    printf("Enter brand: ");
    scanf("%s", sBrand);

    
    // Ignore first line
    while (fgetc(fp) != '\n');

    // Read products file
    while (fscanf(fp, "%lf,%c,%[^,],%[^,],%lf",  &pid, &type, name, brand, &price) == 5) {
        //printf("%d %c %s %s %lf", pid, type, name, brand, price);
        
        if (my_strcmp(sBrand, brand)) {
            tempArr[len][0] = pid;
            tempArr[len][1] = price;
            len++;
        }

        // Read additional features
        for (int i = 0; i < numAdditionalFeatures; i++) {

            // Read last feature (not parse comma)
            if (i == numAdditionalFeatures - 1) {
                fscanf(fp, "%s", features[i]);
                //printf(" %s", features[i]);
            }

            // Read other features (parse comma)
            else {
                fscanf(fp, ",%[^,],", features[i]);
                //printf(" %s", features[i]);
            }
        }
        //printf("\n");
    }

    // Check stock of selected brand


    // Read stocks file
    int m = 0;
    int k = 0;

    for (int i = 0; i < len; i++) {

        rewind(fp2);

        // Ignore first line
        while (fgetc(fp2) != '\n');

        while (fscanf(fp2, "%d,%lf,%[^,],%lf", &sid, &s_pid, branch, &stock) == 4) {
            if (tempArr[i][0] == s_pid) {
                arr[m][0] = tempArr[i][0];
                arr[m][1] = tempArr[i][1];
                arr[m][2] = stock;
                m++;
            }
        }
    }

    for (int i = 0; i < m; i++) {
        printf("%.0lf     %.2lf     %.0lf\n", arr[i][0], arr[i][1], arr[i][2]);
    }

    *pLen = m;

    fclose(fp);
    fclose(fp2);
}

double findMedian(double arr[], int len, double* min, double* max) {
    // Bubble sort the array in ascending order
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - i - 1; j++) {
            if (arr[j] > arr[j+1]) {
                double temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }

    *min = arr[0];
    *max = arr[len - 1];

    // Find the median
    if (len % 2 == 0) {
        // If the length is even, take the average of the middle two elements
        return (arr[len/2 - 1] + arr[len/2]) / 2.0;
    } else {
        // If the length is odd, take the middle element
        return arr[len/2];
    }
}

void stockReport(double arr[][3], int len) {

    double sort[20][20]; // array for sorting
    double res[20][4];
    int m = 0;
    int j = 0;
    double min, max, median;

    // Open report.txt 
    FILE* fp = fopen("report.txt", "w");
    if (fp == NULL) {
        printf("Error opening file");
        return;
    }

    for (int i = 0; i < len; i++) {
        sort[m][j] = arr[i][2];
        //printf("%lf.0\n", sort[m][j]);
        j++;
        if(arr[i][0] != arr[i+1][0]) {
            median = findMedian(sort[m], j, &min, &max);
            fprintf(fp, "%.0lf    %.2lf    %.2lf    %.2lf\n", arr[i][0], min, max, median);
            m++;
            j = 0;
            //printf("\n");
        }
    }

}

void main() {
    double arr[100][3];
    int len = 0;
    int choice;
    while (1) {
        displayMenu();
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                fileOperations();
                break;
            case 2:
                searchProduct();
                break;
            case 3:
                checkStock();
                break;
            case 4:
                brandStockControl(arr, &len);
                break;
            case 5:
                stockReport(arr, len);
                return;
        }
    }
}