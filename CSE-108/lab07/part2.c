#include <stdio.h>
#include <string.h>

void apply_filter(char* s, char* rule);

char *strremove(char *str, const char *sub) {
    size_t len = strlen(sub);
    if (len > 0) {
        char *p = str;
        while ((p = strstr(p, sub)) != NULL) {
            memmove(p, p + len, strlen(p + len) + 1);
        }
    }
    return str;
}

int main() {
    char s[1000];
    char rule[100];
    printf("Enter the string s: ");
    fgets(s, 1000, stdin);
    printf("Enter the rule: ");
    fgets(rule, 100, stdin);
    apply_filter(s, rule);
    printf("Filtered text: %s\n", s);
    return 0;
}

void apply_filter(char* s, char* rule) {
    int slen = strlen(s);
    int rlen = strlen(rule);
    char c1;
    char c2;
    int flag = 0;
    sscanf(rule, "%c*%c", &c1, &c2); {
        printf("c1: %c\n", c1);
        printf("c2: %c\n", c2);
    }
    char w[20];
    while (sscanf(s, "%s", w) == 1) {
        flag = 0;
        for (int i = 0; i < strlen(w); i++) {
            if (w[i] == c1) {
                flag++;
                break;
            }
        }
        for (int i = 0; i < strlen(w); i++) {
            if (w[i] == c2) {
                flag++;
                break;
            }
        }
        strcpy(s, strremove(s, w));
    }
    if (flag == 2) {
        printf("The string is filtered\n");
        return;
    }
    
}
