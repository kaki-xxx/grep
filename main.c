#include <stdio.h>
#include <stdlib.h>
#include "grep.h"

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: %s PATTERN [FILE]", argv[0]);
        exit(EXIT_FAILURE);
    }
    const char *pattern = argv[1];
    FILE *fp;
    if (argc == 3) {
        const char *filepath = argv[2];
        fp = fopen(filepath, "r");
        if (fp == NULL) {
            perror(filepath);
            exit(EXIT_FAILURE);
        }
    } else {
        fp = stdin;
    }
    grep(fp, pattern);
    return 0;
}
