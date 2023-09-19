#include <stdio.h>
#include <string.h>

#define MAX_LEN 1000 

int main() {
    char str[MAX_LEN];
    int freq[26] = {0}; 
    int count = 0; 
    
    printf("Enter a string: ");
    scanf("%s", str);
    
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] >= 'a' && str[i] <= 'z' && freq[str[i] - 'a'] == 0) {
            freq[str[i] - 'a']++; 
            count++; 
        }
    }
    
    for (int i = 0; i < 26; i++) {
        if (freq[i] != 0) {
            printf("remove: %c\n", 'a' + i);
        }
    }

    printf("minimum number of deletion: %d\n", count);
    
    return 0;
}