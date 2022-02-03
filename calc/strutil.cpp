#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "strutil.hpp"

void removeQuotes(char* str, char** dest) {
    int i;
    *dest = (char*)malloc(sizeof(char) * (strlen(str) - 1));

    for (i = 1; i < strlen(str) - 1; i++) {
        (*dest)[i - 1] = str[i];
    }
    (*dest)[i - 1] = '\0';
}

int getStrLen(char* str) {
    int i, counter = 0;
    for (i = 0; i < strlen(str); i++) {
        if (str[i] == '\\') {
            if (strlen(str) - 1 != i) {
                i++;
            }
        }

        counter++;
    }

    return counter;
}

char getChar(char* str, int* index) {
    char c = '\0';
    if (*index > strlen(str)) {
        printf("getChar(): index out of bounds\n");
        exit(EXIT_FAILURE);
    }

    if (str[*index] == '\\') {
        if (strlen(str) - (*index) > 1) {
            switch (str[(*index) + 1]) {
                case 'n':
                    c = '\n';
                    break;
                case '0':
                    c = '\0';
                    break;
                default: 
                    c = str[*index + 1];
                    break;
            }
        }
        (*index) += 2;
    } else {
        c = str[*index];
        (*index)++;
    }
    return c;
}

char* makeStr(char* str) {
    int i, counter = 0;
    char* str2 = (char*)malloc(sizeof(char) * (getStrLen(str) + 1));
    for (i = 0; i < strlen(str); ) {
        str2[counter++] = getChar(str, &i);
    }
    str2[counter] = '\0';
    return str2;
}