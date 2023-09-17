#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORD_SIZE 50
#define MAX_VECTOR_SIZE 300
#define THRESHOLD 26

// My isalpha function
int my_isalpha(char c) {
    if (c >= 'A' && c <= 'Z') return 1;
    else if (c >= 'a' && c <= 'z') return 1;
    else if (c  >= '0' && c <= '9') return 1;
    else return 0;
}

// My strcpy function
void my_strcpy(char * dest, char * src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
        if (i == MAX_WORD_SIZE) break;
    }
    dest[i] = '\0';
}

// My strlen function
int my_strlen(char * str) {
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}

char * my_strcat(char * dest, const char * src) {
    char * p = dest;
    while (*p != '\0') p++;
    while (*src != '\0') *p++ = *src++;
    *p = '\0';
    return dest;
}

// Delete punctuation
void delete_punctuation(char * str) {
    int i = 0;
    int j = 0;
    while (str[i] != '\0') {    
        if (my_isalpha(str[i])) {
            str[j] = str[i];
            j++;
        }
        i++;
    }
    str[j] = '\0';
    //printf("After deleting punctuation: %s\n", str);
    return;
}

int read_dict(const char * file_name, const char * word, double vect[]) {
    int num_words;
    int vector_size;
    char tWord[MAX_WORD_SIZE];
    FILE * fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("Error opening file");
        exit(1);
    }
    
    // Read number of words
    fscanf(fp, "num_word=%d", &num_words);

    // Read vector size
    fscanf(fp, ", vector_size=%d", &vector_size);

    // Scan dictionary
    while(fscanf(fp, "%s", tWord) != EOF) {	
        if (strcmp(tWord, word) == 0) {
            //printf("Word found\n");
            //printf("%s", tWord);
            for (int i = 0; i < vector_size; i++) {
                fscanf(fp, "%lf", &vect[i]);
            }
            //("\n");
            return vector_size;
        }
        else {
            fscanf(fp,"%*[^\n]\n");
        }
    }
    //printf("Word not found\n");
    return 0;
}

// Find the closest word in the dictionary
int find_closest(const char * word, char * closest) {
    int vector_size;
    int num_words;
    char tWord[MAX_WORD_SIZE];
    double sum;
    double tNum;
    double min;

    double vect[MAX_VECTOR_SIZE];
    read_dict("dictionary.txt", word, vect);

    // Open dictionary.txt
    FILE * fp = fopen("dictionary.txt", "r");
    if (fp == NULL) {
        printf("Error opening file");
        exit(1);
    }

    // Read number of words
    fscanf(fp, "num_word=%d", &num_words);

    // Read vector size
    fscanf(fp, ", vector_size=%d", &vector_size);

    // Check every vector
    min = 100; // This might cause errors be careful
    for (int i = 0; i < num_words; i++) {
        sum = 0;

        // Inner iteration
        fscanf(fp, "%s", tWord);
        for (int i = 0; i < vector_size; i++) {
            fscanf(fp, "%lf", &tNum);
            sum += (tNum - vect[i]) * (tNum - vect[i]);
        }
        // Set the minimum
        if (sum != 0 && sum < min) {
            min = sum;
            strcpy(closest, tWord);
        }
    }
    if (min < THRESHOLD) return 1;
    else return 0;
}


// Scan ignore file
int scan_ignore_file(const char * target) {
    char word[20];
    FILE * fp = fopen("ignore.txt", "r");
    if (fp == NULL) {
        printf("Cannot open ignore file\n");
        exit(1);
    }
    while(fscanf(fp, "%s", word) != EOF) {
        if (strcmp(word, target) == 0) return 1;
    }

    return 0;
}


// Count the given word in a file
int count_words(const char * target) {
    if (scan_ignore_file(target)) return 0; // If the word is in the ignore file, return 0
    int count = 0;
    char word[MAX_WORD_SIZE];
    FILE * fp = fopen("input.txt", "r");
    while (fscanf(fp, "%s", word) != EOF) {
        delete_punctuation(word);
        if (strcmp(word, target) == 0) {
            count++;
        }
    }
    //printf("The word %s occurs %d times\n", target, count);
    return count;
}

void occurrences(char input[][50], int word_count, int frequency[], char symbol[]) {
    for(int i = 0; i < word_count; i++) {
        int count = count_words(input[i]);
        if (count != 0) {
            frequency[i] = count;
            symbol[i] = '*';
            //printf("%s: %d\n", input[i], count);
        }
        else {
            double vect[MAX_VECTOR_SIZE];
            if (read_dict("dictionary.txt", input[i], vect) == 0) {
                frequency[i] = 0;
                symbol[i] = '-'; 
                continue;
            }
            char closest[MAX_WORD_SIZE];
            find_closest(input[i], closest);
            symbol[i] = '+';
            frequency[i] = count_words(closest);
            if (frequency[i] == 0) continue;
            sprintf(input[i], "%s->%s", input[i], closest);
        }
    }
}

// Print histogram if more than 1 words entered
int histogram(char input[][50], int word_count, int frequency[], char symbol[]) {
    // Find the max value in frequency
    int max = frequency[0];
    for (int i = 1; i < word_count; i++) {
        if (max < frequency[i]) max = frequency[i];
    }
    
    // Set the scale
    int scale = max / 20 + 1;
    printf("Scale: %d\n", scale);
    
    // Print * or + according to occurence and scale
    for (int i = 0; i < word_count; i++) {
        printf("%-25s: ", input[i]);
        if (frequency[i] == 0) printf("NO MATCHES");
        for (int j = 0; j < frequency[i] / scale; j++) {
            printf("%c", symbol[i]);
        }
        printf("\n");
    }

    return scale;
            
}

// Take user input and store it in an array
int read_line(char input[][50]) {
    char line[100];
    int word_count = 0;

    printf("Enter word(s): ");
    fgets(line, 100, stdin);

    // Scan each word from the input line
    int i = 0;
    while (line[i] != '\0' && word_count < 10) {
        char word[20];
        int j = 0;
        while (line[i] != '\0' && line[i] != ' ' && line[i] != '\n' && j < 19) {
            word[j] = line[i];
            i++;
            j++;
        }
        word[j] = '\0';  // Add null terminator to the word
        if (j > 0) {  // Add the word to the array if it is not empty
            strcpy(input[word_count], word);
            word_count++;
        }
        i++;  // Skip the space or newline character
    }

    return word_count;
}

int main() {
    char input[10][50];
    int word_count = read_line(input);
    
    if (word_count == 1) {
        char closest[MAX_WORD_SIZE];
        int numWord = count_words(input[0]);
        double vect[MAX_VECTOR_SIZE];

        if (count_words(input[0]) != 0) printf("%s appears in \"input.txt\" %d times.", input[0], numWord);
        
        else if (read_dict("dictionary.txt", input[0], vect) == 0) {
            printf("\"%s\" doesn't appear in \"input.txt\".", input[0]);
        }

        else {
            find_closest(input[0], closest);
            numWord = count_words(closest);

            if (numWord != 0) printf("\"%s\" doesn't appear in \"input.txt\" but \"%s\" appears %d times.", input[0], closest, numWord);
            else printf("\"%s\" doesn't appear in \"input.txt\".", input[0]);
        }
        printf("\n");
    }
    
    if (word_count > 1) {
        int frequency[20];
        char symbol[20];
        occurrences(input, word_count, frequency, symbol);
        histogram(input, word_count, frequency, symbol);
    }
    return 0;
}
